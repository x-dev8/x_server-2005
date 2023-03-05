#ifndef _MEXanimctrl_h
#define _MEXanimctrl_h
/*
 *	MEX作为3d模型的基础，既有一些基本的特性和控制方法，
 *	MEX在游戏运行时，编辑工具，max输出插件中都要用到，
 *	需要一个抽象一个类来描述一个模型动画
 */
#include "Me3d/Include.h"
//#include "Me3d/MEX2.h"

#include "Me3d/AnimTimeLine.h"
//#include "Me3d/Model/stdcharskeleton.h"
#include "Me3d/Model/MexConfig.h"
#include "Me3d/Model/MexRes.h"
#include "Me3d/Engine/Engine.h"
#include "Me3d/Engine/TextureManagerInstance.h"
//#include "Me3d/Model/Avatar.h"
// #include "Me3d/Effect/BladeRibbon.h"

// 灯光层数据
struct LayerData 
{
	LayerData(): LightMapIndex(-1),nTextureID(-1) {}
	LayerData( BYTE LMIndex, float UOffset, float VOffset, float UScale, float VScale )
		:LightMapIndex(LMIndex)
		,LightMapUVOffset(UOffset, VOffset)
		,LightMapUVScale(UScale, VScale)
		,nTextureID(-1)
	{
	}

	BYTE				LightMapIndex;				// 光照图索引
	int					nTextureID;					// 全局贴图id
	Vector2				LightMapUVOffset;			// UV在光照图中偏移
	Vector2				LightMapUVScale;			// UV相对于光照图的缩放率
};
/*
*@int Chunk Index
*/
typedef std::map<int, LayerData*> LayerDataContainer;
typedef LayerDataContainer::iterator LayerDataContainerIter;
typedef LayerDataContainer::const_iterator LayerDataContainerConstIter;

// add [6/4/2008 whu]
namespace graphics
{
    class Material;
}

class AnimTimeLine;
class MexCfg;
class MexCfgSequence;
class Mex2;
class StdCharSkeleton;
class MtlAnim;
class MexAnimCtrl;
class MexAnimCtrlSkeleton
{
public:
	struct Bone : public MeCommonAllocObj<MexAnimCtrlSkeleton::Bone>
	{
		IMexBone* pBone;
		D3DXMATRIX	matFrame0Inv;
		D3DXMATRIX*	pMatrices;
	};
public:
	MexAnimCtrlSkeleton();
	~MexAnimCtrlSkeleton();
	BOOL	Create( IMexSkeleton* pSkeleton );
	void	Destroy();
	IMexSkeleton* m_pSkeleton;
	int		m_nNumBone;
	Bone*	m_pBones;
};

class CMexInstanceObject
{
	//public structures
public:
	struct InstanceVertexData
	{
		//D3DCOLOR color;
		float	x;
		float	y;
		float	z;
		float   rotation;
		float   scale;
		float	shadow;
	};
	//public functions
public:
	void SetTranslate( float fx, float fy, float fz	){m_data.x = fx;m_data.y = fy;m_data.z = fz;}
	void SetRotate( float rotation){m_data.rotation = rotation;}
	void SetScale( float scale ){m_data.scale = scale;}
	void SetShadow( float shadow ){ m_data.shadow = shadow; }
	InstanceVertexData& GetInstanceData() {return m_data;}
	//private members
private:
	InstanceVertexData m_data;

};
//--------------------------------------------------------
class MexAnimCtrl;
class Mex2GeoChunk;
class MexInstanceMan
{	
	//public static functions
public:
	static void GlobalInitialize(char* pszShaderFile);
	static void GlobalDestroy();
	static void BeginRender();
	static void EndRender();
	static void SetPlayerPos(D3DXVECTOR3* vPos);
	static void SetDynamicGrass(bool bEnable = true){ ms_bDynamicGrass = bEnable;}
    static void OnResetDevice();
    static void OnLostDevice();
	//private static members
private:
	static IDirect3DVertexDeclaration9 *ms_pVertexDeclHardware;
	static D3DXHANDLE ms_HandleTechnique;      // handle to the rendering technique
	static D3DVERTEXELEMENT9 ms_VertexElemHardware[8];
	static D3DXHANDLE ms_HandleWorld;
	static D3DXHANDLE ms_HandleView;
	static D3DXHANDLE ms_HandleProjection;
	static D3DXHANDLE ms_HandleTexture;
	static ID3DXEffect* ms_pEffect;
	static const int ms_nRenderObjectTotal = 10;
	static bool ms_bDynamicGrass;
	static LPDIRECT3DDEVICE9 ms_pd3dDevice;
	//public functions
public:
	//ctor
	MexInstanceMan();
	~MexInstanceMan();
	//enable instance, create the vb
	HRESULT EnableInstance(MexAnimCtrl* pkMexAnimCtrl, int nMaxInstance);
	//delete the vb
	void DisableInstance();
	//lock to write to the vb
	HRESULT Lock();
	//write a data to vb
	void AddInstance(CMexInstanceObject& instance);	
	//unlock vb
	HRESULT Unlock();
	//render
	void Render();

	//render
	bool BeginMyRender(int nIndex,DWORD flag);
	void DoMyRender(int nIndex);
	//protected members
protected:
	struct InstanceRenderObject
	{
		IDirect3DTexture9* m_pTexture;
		Mex2GeoChunk* m_pGeoChunk;
		int m_nVertexCount;
		int m_nIndexCount;
	};
	bool m_bDynamicGrass;//grass collision test
// 	Mex2* m_mex;
	int m_nMaxInstance;
	int m_nCurrentInstance;
	CMexInstanceObject::InstanceVertexData *m_pIPos;
	IDirect3DVertexBuffer9 * m_pVBInstanceData;		
	InstanceRenderObject m_RenderObject[ms_nRenderObjectTotal];	
	
};

class MexAnimCtrl : public MeCommonAllocObj<MexAnimCtrl>
{
public:
	enum
	{
		eRenderState_None,
		eRenderState_eFadeIn,
		eRenderState_eFadeOut,
		eRenderState_Transparent,
	};
	enum
	{
		eNormalPlayTime = 0,
		eDefaultBlendingTime = 100,
		eMaxLoopTimes	= 0x7fffffff,
		eMaxTimeout		= 0x7fffffff,
		eMaxPlayTask	= 2,
	};
	enum
	{
		eNormalPlay,
		eHoldOnFirstFrame,
		eHoldOnLastFrame,
		eHoldOnHitFrame,
		eSingleFrame,
		eBlendFrame,
		eHideFrame
	};
	enum
	{
		eLeftHandAttachment,
		eRightHandAttachment,
		eMaxAttachment
	};
	enum
	{
		//eMaxBone			= 64,
		eMaxHitPoint		= 16,
		eMaxParticleEmitter = 16,
		eMaxRibbonEmitter	= 16,
		eMaxName			= 256,
		eMaxTask			= 3,
		eMaxTextureStage	= 2,
		//   added 2004.08.06
		eMaxLight			= 32
		//eMaxMtlAnim			= 4,
	};
	enum
	{
		eLastHitPoint		= 1,
		eFirstHitPoint		= 1<<1
	};
	struct SPlayTask
	{
		char	szActionname[eMaxName];	// 动作名称
		DWORD	dwStartTime;
		DWORD	dwOneLoopTime;			// 播放一遍的时间
		DWORD	dwLoopTimes;			// 播放次数
		DWORD	dwTimeOut;				// 超时，一旦超时，播放完成
		DWORD	dwPlayMode;				// 播放模式
		int		nSingleFrameID;			// 单帧播放模式下，播放帧编号
		int		nBlendFrame0;
		int		nBlendFrame1;
		float	fBlendFactor;
		BOOL	bUpperBody;				// 判断是上半身动作还是下半身动作
		BOOL	bLoopPlay;				// 判断是否是个循环动画
		DWORD	dwNeedBlendingTime;		// 需要和上一个动画进行Blending的时间
		BOOL	bWholeBodyAnim;			// 是否全身动作
		BOOL	bNormalAttack;			// 是否普通攻击动作

		//   added 2004.04.19
		IMex*		pMex;			
		MexCfg*		pMexCfg;
		SPlayTask()
		{
			memset( this, 0x00, sizeof( SPlayTask ) );
		};
	};

	enum
	{
		eSelfMtlAnim,
		eWeaponMtlAnim,
		eBodyMtlAnim,
		eMaxMtlAnim,
	};

public:
	virtual bool IsInThread() { return m_bIsInThread; }
	void SetInThread( bool bInThread ){ m_bIsInThread = bInThread; }
protected:
	bool m_bIsInThread;

public:
	static const int g_MaxBoneNum = 256;

public:
	MexAnimCtrl();
	virtual ~MexAnimCtrl();
	virtual void Destroy();
// 	//快速检查碰撞
	static inline bool IntersectQuick(MexAnimCtrl* pAnimCtrl, D3DXVECTOR3 *pvRay,D3DXVECTOR3 *pvDir);

	virtual 	BOOL	Render( float fTransparent, LayerDataContainer* pMeshContainer = NULL,
		int* pVertexCount = NULL, int* pFaceCount = NULL, int* pSubmodelCount = NULL,
		BOOL bIsHairHelmetAlphaTest = FALSE, BOOL bRenderShadow = FALSE ,
		BOOL bRenderParticleEmitters = TRUE, BOOL bOverUI = FALSE, BOOL bRenderDecal = TRUE );

	virtual		void	Render2( MtlAnim* pMtlAnim = NULL );
// 	virtual		void	FastRender( float fTransparent );
//	virtual		void	Render3();
	BOOL		RenderSubset( int nSubset, float fAlpha, LayerData* pLayerData = NULL, int* pVertexCount=NULL, int* pFaceCount=NULL, DWORD dwFlagEx = 0,
        BOOL bRenderShadow=FALSE );
// 	void		FastRenderSubset( int nSubset, IRenderer* pRenderer, float fAlhpa );
	void		RenderSubsetShadow( int nSubset, IRenderer* pRenderer );
	void		RenderShadow( void );
	void		RenderWithShader( float fTransparent );


	virtual		BOOL	Update( DWORD dwTime, MeMatrix* pMatrix, BOOL bUpdateComponent = TRUE );	// 返回动画更新后是否切换成task里下一个动画
	virtual		bool	UpdateComponents( DWORD dwTime, MeMatrix* pMatrix );

	virtual		void	UpdateBody( float x, 
									float y, 
									float z,				// 位置
									float fScaleX,			// 缩放
									float fScaleY,			// 缩放
									float fScaleZ,			// 缩放
									float fUpperBodyRot,	// 上半身朝向
									float fLowerBodyRot,	// 下半身朝向,
									MexCfgSequence* pSeqUpperBody,
									float fUpperBodyFactor,
									BOOL bUpperBodyBlending,
									MexCfgSequence* pSeqLowerBody,
									float fLowerBodyFactor,
									BOOL bLowerBodyBlending );

	void	UpdateBodySpineBonePosOffset( float x, 
										float y, 
										float z,				// 位置
										float fScaleX,			// 缩放
										float fScaleY,			// 缩放
										float fScaleZ,			// 缩放
										float fUpperBodyRot,	// 上半身朝向
										float fLowerBodyRot,	// 下半身朝向,
										MexCfgSequence* pSeqUpperBody,
										float fUpperBodyFactor,
										BOOL bUpperBodyBlending,
										MexCfgSequence* pSeqLowerBody,
										float fLowerBodyFactor,
										BOOL bLowerBodyBlending );

	void	UpdateTransform();	            // 仅用于静态模型，把local顶点和normal转换为世界坐标并保存，用于渲染使用
	void	UpdateBillboardBBox();          // added, jiayi, [2009.4.20], 用于billboard更新bbox
	// UpdateComponents更新每个bone的代码挪到这里，先更新父骨骼，再更新子骨骼
	BOOL	UpdateComponentBone( int boneId, bool* vecUpdateState, MeMatrix* pMatrix, BOOL bUpdateChild = TRUE );
	// UpdateBody更新每个bone的代码挪到这里，先更新父骨骼，再更新子骨骼
	BOOL	UpdateBodyBone( int boneId,
							bool* vecUpdateState,
							const MeMatrix* pmatUpperBody,
							const MeMatrix* pmatLowerBody,
							float fUpperBodyFactor,
							BOOL bUpperBodyBlending,
							float fTargetUpperBodyFrame,
							float fLowerBodyFactor,
							BOOL bLowerBodyBlending,
							float fTargetLowerBodyFrame,
							BOOL bUpdateChild = TRUE );


// 	MexInstanceMan* GetInstanceMan() {return &m_InstanceMan;}
	virtual		void	OnNextPlayTask(){}
	virtual		void	OnHitPoint( AnimTimeLine::SKey* pKey, DWORD dwFlag = 0 ){}


	virtual		BOOL	LoadFromFile( const char* pszFilename ){ return TRUE; }

public:
	// 修改为虚函数 [3/26/2011 zhangjiayi]
	virtual IMex*	GetMex(){ return m_pMex; }
	MexCfg*	GetMexCfg(){ return m_pMexCfg; }
	void		SetMexCfg( MexCfg* pMexCfg ){ m_pMexCfg = pMexCfg; }
	void		DeleteMexCfg() { if(m_pMexCfg) delete m_pMexCfg; m_pMexCfg = NULL;}	// 因为clone的数据只保存一份MexCfg,所以只销毁ResMgr里的，需要在destroy前调用
	MeMatrix* GetMatrices(){ return m_amatBoneInWorldSpace; }
	MeMatrix* GetBoneMatrices(){ return m_amatBoneInModelSpace; }
	MeMatrix* GetSrcBoneMatrices(){ return m_matSrcBones; }

	Vector	 GetUpperBodyRootBonePos(){ return m_vUpperBodyRootBonePos;	}
	Vector	 GetLowerBodyRootBonePos(){ return m_vLowerBodyRootBonePos; }

	//获取脊椎骨骼的偏移位置
	BOOL		UpdateSpineBonePosOffset( DWORD dwTime, MeMatrix* pMatrix );	// 返回下半身是否动画结束
	Vector	GetSpineBonePosOffset(){ return m_vSpineBonePosOffset; }

	Vector	GetBoneWorldPos( int nBoneId, BOOL *bRetOk = NULL );        // bRetOk返回是否正确获得
	D3DXMATRIX	GetBoneMatrices( int nBoneId, BOOL *bRetOk = NULL );    // bRetOk返回是否正确获得
	void		SetFrameID( int nFrameID )
	{ 
		if (GetFrameCount() > 0 && nFrameID >= 0)
		{
			m_nFrameId = nFrameID%GetFrameCount(); 
		}
	}
	int			GetFrameId(){ return m_nFrameId; }
	int			GetFrameCount();
//	void		SetUpperBodyFactor( float fFactor );
	void		SetEffectAnim( BOOL bEffectAnim );
	void		SetMex( IMex* pMex, MexCfg* pMexCfg ,const char* pszSkin = NULL);

	BOOL		PlayAnimByName( const char* pszActionname, DWORD dwOneLoopTime, BOOL bLoopPlay = TRUE );
	BOOL		PlayAnim( SPlayTask* pTask );
	BOOL		PlayAnim( int nStartFrameID, int nEndFrameID, DWORD dwOneLoopTime );
	MexCfgSequence* GetTmpSequence(){ return &m_TmpSequence; }

	void		PushAnim( SPlayTask* pTask );
	void		ClearAnims();
	void		ClearUpperBodyAnims();
	void		ClearLowerBodyAnims();
	void		ResetPlayTask( SPlayTask* pTask );
	DWORD		GetAnimTimeLength( const char* pszActionname );
	void		PushUpperBodyAnim( SPlayTask* pTask );
	void		PushLowerBodyAnim( SPlayTask* pTask );


	// 精确时间控制接口
	void		SetPeriod();
	//AnimTimeLine* GetTimeLine(){ return &m_timeLine; }
	
	// 更换搭接部位，比如武器，防具
	// 更换模型
	virtual void	ReleaseLastModel();

	/*BOOL	ChangePartModel( int nPartId, int nModelId, const char* szSkin = DEFAULT_AVATARSETTING_NAME, int nSpecular = -1, short stStar = 0 );*/
	virtual BOOL	ChangeModel( int nModelId , BOOL bIsTerrainModel,const char* pszSkin = NULL, BOOL bKeepOldData = FALSE);
	//BOOL	ChangeCloneModel( int nModelId );

	//   added 2004.09.15
	void	SetHairColor( DWORD r, DWORD g, DWORD b );


	BOOL	AttachModelToBone( int nModelID,const char* pszBoneName );

	//   added 2004.06.15
	void SetPosition( float x, float y, float z ){ m_vPosition = Vector( x, y, z ); }
	void SetPosition( Vector& kPos){ m_vPosition = kPos; }
	Vector GetPosition(){ return m_vPosition; }
	void SetRotationZ( float theta ){ m_fZRotTheta = theta; }
	void SetRotationY( float theta ){ m_fYRotTheta = theta;	}
	void SetRotationX( float theta ){ m_fXRotTheta = theta;	}
	void GetRotation(float& fX, float& fY, float& fZ){ fX = m_fXRotTheta; fY = m_fYRotTheta; fZ = m_fZRotTheta; }
	void SetScale( float scale ){ m_fScaleX = scale; m_fScaleY = scale; m_fScaleZ = scale;  }
	void SetScaleXYZ( float scale_x, float scale_y, float scale_z ){ m_fScaleX = scale_x; m_fScaleY = scale_y; m_fScaleZ = scale_z; }
	float GetScale(){return m_fScaleZ;}	// 要兼容老接口，则只返回Z的scale
	void GetScaleXYZ( float& scale_x, float& scale_y, float& scale_z){ scale_x = m_fScaleX; scale_y = m_fScaleY; scale_z = m_fScaleZ; }
	void CalcTransformMatrix( float x, float y, float z, float rot, float scaleX, float scaleY, float scaleZ, MeMatrix* pmatTransform );
	void CalcTransformMatrix( MeMatrix* pmatTransform );
	//   added 2004.06.15
	void UpdateByParam( DWORD dwTime );
	//   added 2004.06.29
// 	BOOL	IntersectVRay( Vector* pvStart, Vector* pvHit );
	//   added 2004.09.16
// 	BOOL	IntersectRay( Vector* pvStart, Vector* pvDir, Vector* pvHit );
// 	// jiayi added [09.03.24]
	bool	IntersectRayQuick(Vector* pvStart, Vector* pvDir);
	//   added 2004.07.01
	void EnableAllEffects( BOOL bEnable );
	//  
	//void EnableRenderMesh( BOOL bEnable ){ m_bRenderMesh = bEnable; }

	//   added 2004.11.20
	Vector GetMin(){ return m_vMin; }
	Vector GetMax(){ return m_vMax; }
	Vector	GetCenter(){ return m_vCenter; }
	float		GetRadius(){ return m_fRadius; }
	void	BuildBBox();
	Vector	GetWorldMin() {return m_vWorldMin;}
	Vector GetWorldMax() {return m_vWorldMax;}

	virtual void	UpdateLocalBBox();
	void	UpdateWorldBBox( MeMatrix* pMatrix );
	void	BuildWorldBBox();	// 根据UpdateWorldBBoxByChunk结果，计算BBox
	bool	UpdateWorldBBoxByChunk( MeMatrix* pMatrix ,IRenderable* pRenderable);
	Box* GetWorldBBox(){ return &m_worldBBox; }
	void	LimitLocalBBox( float fMinRadius, float fMaxRadius, float fMinHeight, float fMaxHeight );
	void	NeedLimitLocalBBox( BOOL b ){ m_bNeedLimitLocalBBox = b; }

	static void		SetGameTime( DWORD dwTime );
	static DWORD	GetGameTime();

	BOOL	CloseAvatarSetting( MexCfgAvatarSetting* pSetting );
	BOOL	ChangeAvatarSetting( const char* pszName );
	MexCfgAvatarSetting* GetAvatarSetting(){ return m_pAvatarSetting; }
	void	SetAvatarSetting( MexCfgAvatarSetting* pSetting ){ m_pAvatarSetting = pSetting; }
	IReplaceableTextureProj* GetReplaceableTextureProj(){ return &m_ReplaceableTextureProj; }

	int	GetMaxLightCount(){ return 0; }
	IMexLight* GetMexLight( int nLight ){ return NULL;/*return m_pLights[nLight];*/ }

	bool			IsSelect()	{return m_bSelect;}
	void			SetSelect(bool bSel ) {	m_bSelect = bSel;	}

	void			SetSubsetDisplayFlag( int nSubset, bool bDisplay );
	void			SetRenderFlag(DWORD dwFlag)			{ m_dwRenderFlag = dwFlag; }
	
	//int		GetFrameID(){ return m_nFrameId; }
	SPlayTask*		GetPlayTask( int nTask );//{ return &m_vectorPlayTask[nTask]; }
	D3DLIGHT9*		GetEnvLight(){ return &m_EnvLight; }
	void			SetEnvLight( D3DLIGHT9* pLight ){ m_EnvLight = *pLight; }
	void			EnableEnvLight( BOOL bEnable ){ m_bHasEnvLight = bEnable; }
	BOOL			HasEnvLight(){ return m_bHasEnvLight; }
	int				GetStartFrameID(){ return m_nStartFrameId; }
	int				GetEndFrameId() {return m_nEndFrameId;}
	int				GetHitPointFrameID(){ return m_nHitPointFrameID; }
	void			NeedInitUpperBodyAndLowerBody();
	BOOL			InitUpperBodyAndLowerBody();

	BOOL			IsUpperBodyAndLowerBodyMode();
	void			CancelUpperBodyAndLowerBodyMode();

	INT				GetModelID() { return m_nModelId; }

	void			SetUpperRot( float fRot );
	void			SetLowerRot( float fRot );

	BOOL			IsUpdateComponents();

	AnimTimeLine*	GetUpperBodyAnimTimeLine();
	AnimTimeLine*	GetLowerBodyAnimTimeLine();

	void			SetUpperBodyFactor( float fFactor );
	void			NotUseTexture() { m_bNotTexture = TRUE; }
	void			UseTexture() { m_bNotTexture = FALSE; }

	// 获取当前上半身正在播放的动画
	const char*		GetCurUpperAnim();
	int				GetCurUpperAnimType();

	// 获取当前下半身正在播放的动画
	const char*		GetCurLowerAnim();
	int				GetCurLowerAnimType();

	// 仅供编辑器使用，游戏中请不要乱用
	void			SetAni(BOOL bAni) {m_bAni = bAni;};
	// 仅供编辑器使用，游戏中请不要乱用
	void			RefreshParticleEmitters(IMex *pSourceMex = NULL);

	BOOL			IsAni()		{ return m_bAni; }
	BOOL			HasEmitter() { return m_HasEmitter;	}

	BOOL			IsLowerBodyBlending();
	BOOL			IsUpperBodyBlending();

	float			GetUpperBodyFactor();
	float			GetLowerBodyFactor();

	void			UpdateAsComponent( DWORD dwTime, MexAnimCtrl* pBindAnim, int nBindBoneID, float* pfHelperMatrixInit,int nBoneIndex = 0 );
    // 作为有骨骼动画的部件更新
    void            UpdateAsAnimComponent(DWORD dwTime, MexAnimCtrl* pBindAnim, int nBindBoneID, float* pfHelperMatrixInit,int nBoneIndex = 0 );

	void			UpdateFollowParent( DWORD dwTime, MexAnimCtrl *pParent, const char *szBindBone);

	void			UpdateEffects( DWORD dwTime, float* pfBonesForEffect, float* pfMatrix );
	
	void			IAmComponent(){ m_bIsComponent = TRUE; }
	BOOL			IsComponent(){ return m_bIsComponent; }

// 	void			ApplyBladeRibbon();
// 	void			ClearBladeRibbon();

// 	BOOL			CloneAndMirrorX( MexAnimCtrl* pMexAnim );
	BOOL			Clone( MexAnimCtrl* pMexAnim, BOOL IsTerrainModel=FALSE );
	void			MirrorX( BOOL b ){ m_bMirrorX = b; }
	BOOL			IsMirrorX(){ return m_bMirrorX; }

	void			UseSkinMesh( BOOL b ){ m_bUseSkinMesh = b; }
	BOOL			IsUseSkinMesh(){ return m_bUseSkinMesh; }

	
	// added, jiayi, [2009.4.23]
	const MeMatrix& GetModelMatrix(){ return m_matModel; }

	// added, jiayi, [2009.4.20]
	void			SetUpdatedBillboardBBox( bool bUpdated ){ m_bUpdatedBillboardBBox = bUpdated; }

	SPlayTask*		GetCurrLowerBodyPlayTask() { return &m_LowerBodyPlayTask[0]; }
    SPlayTask*		GetLowerBodyPlayTask(int nIndex) { if( nIndex >= 0 && nIndex < 2 ) return &m_LowerBodyPlayTask[nIndex]; else return NULL; }

public:
	int				PartOffset;
	bool			m_bRenderFirstPart;
	BOOL			m_bUseSkinMesh;
	// 上半身的动画播放进度
	float			m_fUpperBodyFactor;

	// 下半身的动画播放进度
	float			m_fLowerBodyFactor;

	INT				m_SpecularTexID;

	// 加速上半身的动画播放
	DWORD			FastPlayUpperAnim( float fSpeedX );

	// 上半身的动画是否播放完毕
	BOOL			IsUpperAnimPlayOver();
	void			ResetUpperAnimPlayOver() {m_bUpperBodyPlayOver = FALSE;}
    void            ForceUpperAnimPlayOver() {m_bUpperBodyPlayOver = TRUE;}

	BOOL			IsUpperAnimHitPointPlayOver();

    IReplaceableTextureProj *m_pUseTextureProj;
	MexReplaceableTextureProj *m_pUseShimmerGrayTextureProj;
    IReplaceableTextureProj *m_pUseLuminanceTexProj;

    graphics::Material*        m_pMaterial;

	float*	GetTransform(){ return (float*)&m_matTransform; }
	inline void	SetTransform( float* pMatrix );

	virtual void	ApplyBladeRibbon(){}

	virtual void EnableChildrenUpdateAndRender( bool enabled );

	BOOL			IsUpperBodyPlayingComAnim();

protected:
	virtual BOOL _ChangeModel( IMex* pMex, MexCfg* pMexCfg,const char* pszSkin = NULL);
	virtual void CheckWeaponDisplay(){}

	bool m_bRenderRibbon;
	// 动画数据
	IMex*			m_pMex;
	MeMatrix		m_matTransform;
	MexCfg*		m_pMexCfg; 
	MexCfgAvatarSetting* m_pAvatarSetting;

	MexReplaceableTextureProj m_ReplaceableTextureProj;
	MexReplaceableTextureProj m_LuminanceTextureProj;

	// 上半身的动作
	MexCfgSequence*	m_pSeqUpperBody;
	int					m_nUpperBodyAnimType;

	// 下半身的动作
	MexCfgSequence*	m_pSeqLowerBody;
	int					m_nLowerBodyAnimType;

	int				m_nUpperBodyRootBoneID;	// 上半身根节点
	int				m_nBipBoneID;			// 模型的中心点

	Vector		m_vMin;
	Vector		m_vMax;
	Box		m_worldBBox;
	Vector		m_vCenter;				// 中心点的世界坐标
	float			m_fRadius;				// 模型半径
	Vector		m_vWorldMin;			// 世界坐标的最小坐标
	Vector		m_vWorldMax;			// 世界坐标的最大坐标

protected:
	//instance
// 	MexInstanceMan m_InstanceMan;
	BOOL			m_bIsComponent;
//	FLOAT			m_fAlpha;
	BOOL			m_bNotTexture;
	BOOL			m_bHasEnvLight;
	D3DLIGHT9		m_EnvLight;
	DWORD			m_dwRenderFlag;
	
	//AnimTimeLine	m_timeLine;
	//上半身的动画时间
	AnimTimeLine	m_UpperBodyAnimTimeLine;
	AnimTimeLine	m_LowerBodyAnimTimeLine;

	int				m_nStartFrameId;
	int				m_nEndFrameId;
	int				m_nHitPointFrameID;
	int				m_nFrameId;
	int				m_nLastFrameID;
	int				m_nFrameCount;
	DWORD			m_dwOneLoopTime;
	//实际循环的次数
	int				m_nLoopTimes;
	int				m_nHitPointCount;

	int				m_nNumPlayTask;

	int				m_nNumUpperBodyPlayTask;
	int				m_nNumLowerBodyPlayTask;

	/// 上半身的动画任务
	SPlayTask		m_UpperBodyPlayTask[eMaxPlayTask+1];
	/// 下半身的动画任务
	SPlayTask		m_LowerBodyPlayTask[eMaxPlayTask+1];

	/// 以前全身的动画任务
	SPlayTask		m_PlayTasks[eMaxPlayTask+1];


	D3DMATERIAL9	m_Mtl;

	/// 全身的动作
	//MexCfgSequence* m_pSequence;

	MexCfgSequence m_TmpSequence;

	BOOL			m_bNeedLimitLocalBBox;

	DWORD				m_dwHairColor[3];

	IMexParticleEmitter* m_pParticleEmitters[eMaxParticleEmitter];
	IMexRibbonEmitter* m_pRibbonEmitters[eMaxRibbonEmitter];

	MeMatrix*		m_amatBoneInWorldSpace;
	MeMatrix*		m_amatBoneInModelSpace;
	MeMatrix*		m_matSrcBones;
	//   added 2004.06.29
	MeMatrix		m_matModel;
	MeMatrix		m_matModelInv;

	//   added 2004.06.14
	Vector		m_vPosition;
	float			m_fZRotTheta; // 模型相对Z的旋转
	float			m_fYRotTheta; // 模型相对Y的旋转
	float			m_fXRotTheta; // 模型相对X的旋转
	float			m_fScaleX;
	float			m_fScaleY;
	float			m_fScaleZ;
	float			m_fFigureScale; // 表格中填写的模型自身缩放比

	// 保存上一帧模型位置，旋转和缩放数据
	Vector		m_vPrePosition;
	Vector		m_vPreRotation;
	Vector		m_vPreScale;
	MeMatrix		m_vPreTransformMatrix;

	BOOL			m_bMirrorX;

	BOOL			m_bEnableRibbonEmitter;
	BOOL			m_bEnableParticleEmitter;

	BOOL			m_HasEmitter;
	bool			m_HasBillboard;// added, jiayi, [2009.4.20]
	bool			m_bUpdatedBillboardBBox;

	int				m_nModelId;
	static DWORD	m_dwGameTime;

	std::vector<bool> m_vectorBodyBoneFlag;

	// editor
	bool			m_bSelect;

	Vector		m_vUpperBodyRootBonePos;
	Vector		m_vLowerBodyRootBonePos;
	Vector		m_vSpineBonePosOffset;
	float			m_fCurUpperBodyFrame;
	float			m_fCurLowerBodyFrame;

	// 上下半身的旋转朝向
	float			m_fUpperBodyRot;
	float			m_fLowerBodyRot;

	//
	BOOL			m_bUpperBodyPlayOver;
	BOOL			m_bLowerBodyIdle;
	BOOL			m_bUpperBodyIdle;

	// 上半身做完动作后的Blending
	BOOL			m_bUpperBodyBackBlending;
	DWORD			m_dwUpperBodyStartBackBlendingTime;

	BOOL			m_bUpperBodyBlending;
	DWORD			m_dwUpperBodyStartBlendingTime;
	DWORD			m_dwUpperBodyBlendingStep;

	// 下半身做完动作后的Blending
	BOOL			m_bLowerBodyBackBlending;
	DWORD			m_dwLowerBodyStartBackBlendingTime;

	BOOL			m_bLowerBodyBlending;
	DWORD			m_dwLowerBodyStartBlendingTime;
	DWORD			m_dwLowerBodyBlendingStep;

	BOOL			m_bUpperBodyAndLowerBodyMode; //是否上下身类型的动画

	BOOL			m_bNeedInitUpperBodyAndLowerBody; //是否要初始化上下半身

	BOOL			m_bUpdateComponents;

	BOOL			IsIdleSequence( MexCfgSequence* pSequence );
	BOOL			IsComSequence( MexCfgSequence* pSequence );

	BOOL			m_bEffectAnim;
	float			m_fCurBodyFrame;

	BOOL			m_bAni;
	BOOL			m_bIsTerrainModel;		// 是否是terrain上的模型

	DWORD			m_dwLightTrackDeadTime;
	FLOAT			m_fLightTrackAlpha;

    // 每个人物保存一份和骨骼数对应的位置和旋转数据，解决blend过程中切动画
	BOOL			m_bBodyLastBlend;	// 上次动画切换前是否blend状态
    struct BlendTransQuatsData
    {
        Vector kLastBlendTrans;
        Quaternion kLastBlendQuats;
    };
    std::vector<BlendTransQuatsData> m_vctBlendTransQuats;  // vector个数由骨骼数决定

protected:
	BOOL			m_bCanBlending;
    BOOL			m_bUpperBodyPlayingComAnim;
	BOOL			m_bPlayingWholeBodyAnim;

    virtual bool attachChild( const std::string name, MexAnimCtrl* pChild );
    virtual void detachAndDestroyChild( const std::string& name );
    virtual void detachAndDestroyAllChild();
    virtual void detachAllChild();
    virtual MexAnimCtrl* detachChild( const std::string& name );
    virtual MexAnimCtrl* getChild( const std::string& name );

    virtual void updateChildren( DWORD dwTime, const MeMatrix* pParentMatrix );
    virtual void renderChildren( float fTransparent );
	void			SetTerrainModel(BOOL bModel){m_bIsTerrainModel = bModel;};

	BOOL			IsUpperWholeBodyAnim() { return m_bPlayingWholeBodyAnim; }
protected:
    typedef std::map< std::string, MexAnimCtrl* > MexAnimCtrlChildrenSet;
    MexAnimCtrlChildrenSet _mexChildren;

    bool _enableChildren; /// 是否更新孩子和渲染孩子。

	bool			IsNeedCalcTransformMatrix();

public:
	bool GetBindingBowString() const { return m_bBindingBowString; }
	void SetBindingBowString(bool val) { m_bBindingBowString = val; }
protected://为了弓弦绑定
	bool			m_bBindingBowString;
	bool			m_bNeedCheckBindingBowString;
	int				weaponModelId;
	// 新关键帧相关
protected:
	float*	GetKeyFrameBlendedMatrices( IMexBone* pBone, float t, float fKeyTime0, float fKeyTime1, int nFps, BOOL bIsLastBlend = FALSE, Vector* pLastBlendTrans = NULL, Quaternion* pLastBlendQuats = NULL );
	BOOL	CanGetBoneMatricesBackupAtTime(float time, int boneid);
	void	SetBoneMatricesAtTime(float time, int boneid, const float* mat);
	BOOL	CanGetBoneMatricesAtTargetTime(float time, int boneid);
	void	SetBoneMatricesAtTargetTime(float time, int boneid, const float* mat);

	int*			m_pKeyTimeOfBoneMatrices;		// m_amatBoneMatricesFromKeyTime对应的动作帧
	MeMatrix*		m_amatBoneMatricesFromKeyTime;	// GetMatricesFromKeyTime返回值备份

	// GetKeyFrameBlendedMatrices里用于保存KeyTime1父骨骼矩阵，优化效率
	int*			m_pTargetKeyTimeOfBoneMatrices;		// m_amatBoneMatricesFromKeyTime对应的动作帧
	MeMatrix*		m_amatBoneMatricesTargetKeyTime;	// GetMatricesFromKeyTime返回值备份
};

#include "MexAnimCtrl.inl"

#endif