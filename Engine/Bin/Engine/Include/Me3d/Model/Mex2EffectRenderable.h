#ifndef _mex2_EffectRenderable_h
#define _mex2_EffectRenderable_h

#include "Me3d/Me3d.h"
#include "Me3d/Model/MexSkinMesh.h"
#include "Me3d/Engine/Engine.h"
#include "Me3d/Engine/Renderable.h"
#include "Mutex.h"
#include "Me3d/Model/MexConfig.h"
#include "FuncPerformanceLog.h"
#include "Me3d/Model/MexGeoChunk.h"

enum ECKFMex2ParticleEmitterFlag
{
	MEX2_PARTICLE_EMITTER_SQUIRT		=	1<<13,
	MEX2_PARTICLE_EMITTER_LINEEMITTER	=	1<<14,
	MEX2_PARTICLE_EMITTER_HEAD			=	1<<15,
	MEX2_PARTICLE_EMITTER_TAIL			=	1<<16,
	MEX2_PARTICLE_EMITTER_BOTH			=	1<<17,
	MEX2_PARTICLE_EMITTER_PARTICLEINMODELSPACE	=	1<<18,
	MEX2_PARTICLE_EMITTER_XYQUAD		=	1<<19,
	MEX2_PARTICLE_EMITTER_LOCKEMITTER	=	1<<20,
	MEX2_PARTICLE_EMITTER_TANGENT		=	1<<21,

};

// mex2 条带发射器 added 2003.10.06
#define MEX2_MAX_RIBBON_EDGE 64 //32 //刀光圆滑修改后拖尾太短，改成64

/*
 * 2012.7.2 wangshuai
 * 使用dwBlendMode
 */
struct Mex2RibbonEmitterSetting
{
	Vector vLines[2];
	char szParentBonename[MEX2_MAX_NAME];
	int nParentBoneId;
	int nTextureId;
	DWORD dwEdgePerSec;
	DWORD dwEdgeLifeSec;
	DWORD dwVertexAlpha;
	DWORD dwBlendMode;
};

struct Mex2RibbonEdge
{
	DWORD dwBornTime;
	BOOL bStart;
	DWORD dwStartTime;
	DWORD dwLife;
	float fU;			// fF在dwLife之内从0变为1
	//float fTU;
	Vector vPoint[2];
	//DWORD dwLastChangeTUTime;
	Mex2RibbonEdge():		dwBornTime(0),
								bStart(FALSE),
								dwStartTime(0x7fffffff),
								dwLife(0),
								fU(0.0f)
								//fTU(0.0f),
								//vPoint( 0, 0, 0 ),
								//dwLastChangeTUTime(0){};
								{}

};

struct SEmitterVertex
{
	SEmitterVertex()
	{
		color = 0;
		u = 0;
		v = 0;
	}
	D3DXVECTOR3 p;
	unsigned long color;
	float u, v;
};

class CEffectRenderable:public SortRenderable
{
public:
	virtual void DoRender( bool bPost );
 	virtual bool DoRender( SEmitterVertex* pBuffer ) = 0;
	virtual float			GetDisToCameraEye(float* pMatrices) ;
protected:
	D3DXVECTOR3		m_vCenter;

};

class	Mex2RibbonEmitter:public IMexRibbonEmitter, public MeCommonAllocObj<Mex2RibbonEmitter>, public CEffectRenderable
{
	friend Mex2;
public:
 	virtual bool DoRender( SEmitterVertex* pBuffer );

public:
	Mex2RibbonEmitter():	
        pSetting(NULL),
		nEdgeCount(0),
        nMaxEdgeCount(0),
        nLastFrameID(-1),
        pParentMex(NULL),
        pParentBone(NULL),
		dwLastGenEdgeTime(0),
		dwLastUpdateTime(0)
	{
		memset( m_szBindPartName, 0x00, MEX2_MAX_NAME );
		m_spRenderObject = MeNew MeParticleRibbonRenderObject;
	}
	virtual int GetTotalVerticesCount(bool bPost) {return (nEdgeCount-1)*4;}
	virtual int GetTotalFacesCount(bool bPost)  {return (nEdgeCount-1)*2;}

	BOOL	Read( Mex2Pointer inP, int nSize );
	BOOL	Bind( Mex2* pMex );

	//////////////////////////////////////////////////////////////////////////
	// 虚函数
	const char* GetName(){ return ""; }
	const char* GetBindPartName(){ return m_szBindPartName; }
	void	Update( int nTime, int nFrameID, float* pfMatrices, float* pfmatModel, BOOL bSmooth = FALSE );
	void	Render( float* pfMatrix, short stTextureId, float fAlpha, BOOL bInterp, bool bOverUI );
	void	RenderNormal( float* pfMatrix, short stTextureID, float fAlpha );
	int		GetParentBoneID(){ return pSetting->nParentBoneId; }
	int		GetLocalTextureID(){ return pSetting->nTextureId; }
	void	GetPoint( float* pfPoint );
	IMexRibbonEmitter* Clone();
	void	Release(){ delete this; }
	void	Clear(){
		nEdgeCount = 0;
	}
	void	Reset()
	{
		vLastEdgePos = Vector::ZERO;
		qLastEdgeQuat = Quaternion(0,0,0,0);
	}
// 	static bool createBuffers();
// 	static void destroyBuffers();

private:	
// 	static LPDIRECT3DVERTEXBUFFER9 m_pVB;
// 	static LPDIRECT3DINDEXBUFFER9 m_pIB;
protected:

	Mex2RibbonEmitterSetting *pSetting;
	char	m_szBindPartName[MEX2_MAX_NAME];;
	int		nEdgeCount;
	int		nMaxEdgeCount;
	//Mex2RibbonEdge edgeHead;
	Mex2RibbonEdge edges[MEX2_MAX_RIBBON_EDGE];
	//Vector ControlPoints0[MEX2_MAX_RIBBON_EDGE];
	//Vector ControlPoints1[MEX2_MAX_RIBBON_EDGE];
	
	int				nLastFrameID;
	Mex2*		pParentMex;
	//Mex2Bone*	pParentBone;
	IMexBone*		pParentBone;
	//float	fUOffset, fVOffset;
	DWORD	dwLastGenEdgeTime;
	DWORD	dwLastUpdateTime;
	Quaternion qLastEdgeQuat;	// 上条边的旋转
	Vector	vLastEdgePos;		// 上条边的位置

	

	
	BOOL	IsEdgeDead( Mex2RibbonEdge* pEdge, int nTime );
	void	GenEdge( Mex2RibbonEdge* pEdge, int nTime, MeMatrix* pParentTransform );
	BOOL	AddNewEdge( Mex2RibbonEdge* pEdge );
	void	UpdateEdge( Mex2RibbonEdge* pEdge, int nTime, MeMatrix* pmatModel = NULL );
	
	void	MakeARenderEdge( Mex2RibbonEdge* pEdge, SEmitterVertex* vertex );


	//   added 2003.12.12
	//void	Render2(  );

};
struct Mex2RibbonEmitters:public IMexRibbonEmitters, public MeCommonAllocObj<Mex2RibbonEmitters>
{
	friend Mex2;
public:
	BOOL	Read( Mex2Pointer inP, int nSize );
	BOOL	Bind( Mex2* pMex );
	//////////////////////////////////////////////////////////////////////////
	// 虚函数
	int		GetEmitterCount(){ return vectorRibbonEmitter.size(); }
	IMexRibbonEmitter* GetEmitter( int i ){ return &vectorRibbonEmitter[i]; }
protected:
	std::vector<Mex2RibbonEmitter> vectorRibbonEmitter;
	//void	Update( int nTime, MeMatrix* pmatModel );
	//void	Render();

};

struct Mex2Particle : public MeCommonAllocObj<Mex2Particle>
{
    DWORD   dwBornTime;         // 出生时间
    DWORD   dwLife;             // 生命
    Vector  vBornPos;           // 出生时的位置
    Vector  vPos;               // 位置，相对于模型坐标系的，
    Vector  vPosWorld;          // 位置，模型坐标系经过变换以后的结果
    Vector  vDynamicPos;        // 动态运动方向
    float   fSpeed;             // 速率
    Vector  vDir;               // 运动方向
    Vector  vDirWorld;
    float   fScale;             // 缩放
    float   fScaleRandomRate;   // 缩放倍数，每个粒子产生时会随机一个缩放倍数，作为 fScale 的系数   added by zhuomeng.hu		[2/14/2011]
    DWORD   dwColor;
    int     nCellId;            // 贴图cell编号
    int     nCellOffset;        // 贴图Cell偏移，用以产生随机第一帧        added by zhuomeng.hu		[3/10/2011]
    int     nRepeatTimes;       // 贴图动画已经循环播放的次数
    DWORD   dwLastUpdateTime;   // 上次更新时间
//  float   fLerpT;             // Slerp(a, b, t)的参数t，用于shader;
//  char    cSegmentColorIndex;
    float   fRanAngle;          // 随即的旋转角度		        added by ZhuoMeng.Hu        [8/5/2010]
    float   fTailLength;        // 粒子尾的长度改为可变值       added by zhuomeng.hu		[2/18/2011]

};

struct Mex2ParticleEmitterSetting
{
	DWORD		dwFlag;
	char		szName[MEX2_MAX_NAME];	// 80 byte
	int			nParentBoneId;	// 跟随骨骼运动
	Vector	vPivot;		// 原始位置

	// 发射器选项
	int			nCount;			// 粒子数目
	float		fSpeed;			// 粒子创建时的初始速度
	float		fVariation;		// speed变化振幅
	float		fConeAngle;		// 喷射cone的夹角
	float		fGravity;		// 重力
	// 时间选项
	float		fLifeSpan;		// 生命
	float		fEmissionRate;	// 每秒钟创建粒子数目
	float		fWidth;			
	float		fHeight;		// 发射器面板的大小
	// 贴图选项
	DWORD		dwBlendMode;	// 混合模式
	int			nRow;
	int			nCol;			// 贴图材质的网格数

	// 粒子选项
	// head, tail说明
	// head是一个正方形的billboard
	// tile是一个长方形billboard，沿着粒子的运动方向，长度=fTailLength
	DWORD		dwPart;
	float		fTailLength;	// 拖尾长度
	float		fMiddleTime;	// 生命的middle key，相对时间

	int			nSegmentColor[3][3];	// start/middle/end, multiply粒子颜色
	int			nAlpha[3];				// start/middle/end
	float		fParticleScaling[3];	// start/middle/end
	DWORD		dwUVAnimFps;			// uv动画的播放速率
	DWORD		dwLifeSpanHeadUVAnim[3];	// start/middle/end
	DWORD		dwDecayHeadUVAnim[3];		// start/middle/end
	DWORD		dwLifeSpanTailUVAnim[3];		// start/middle/end
	DWORD		dwDecayTailUVAnim[3];	// start/middle/end
	int			nTextureId;				// 贴图id
	int			nPriorityPlane;			// 优先级平面
};

struct Mex2ParticleEmitterSetting2:public Mex2ParticleEmitterSetting
{
	Vector vPlaneNormal;
	Vector vPlaneXAxis;
	Vector vPlaneYAxis;
	Mex2ParticleEmitterSetting2();
};

// added by zhuomeng.hu		[2/12/2011]
struct Mex2ParticleEmitterSetting3 : public Mex2ParticleEmitterSetting2
{
    Mex2ParticleEmitterSetting3();
    const Mex2ParticleEmitterSetting3& operator =( const Mex2ParticleEmitterSetting2& emtSetting );

    float fLifeSpanMax;     // 生命随机最大值，仅当此值大于 fLifeSpan 有效
    float fScaleRateMin;    // 大小缩放比例最小随机值，仅当此值小于 fScaleRateMin 有效
    float fScaleRateMax;    // 大小缩放比例最大随机值，仅当此值大于 fScaleRateMax 有效
    bool  bContraryColor;   // 粒子顶点是否反色
};

// added by zhuomeng.hu		[2/18/2011]
struct Mex2ParticleEmitterSetting4 : public Mex2ParticleEmitterSetting3
{
    Mex2ParticleEmitterSetting4();
    const Mex2ParticleEmitterSetting4& operator =( const Mex2ParticleEmitterSetting3& emtSetting );

    bool  bAngleChangeByCone;       // 粒子是否会随发射方向的不同而旋转
    bool  bTailLengthChange;        // 粒子尾的长度是否会变化
    float fTailLengthChange[3];     // 粒子尾的长度变化值
};

class  Mex2ParticleEmitter:public IMexParticleEmitter, public MeCommonAllocObj<Mex2ParticleEmitter>, public CEffectRenderable
{
	friend class Mex2ParticleEmitters;
	friend class Mex2;

public:
    virtual bool DoRender( SEmitterVertex* pBuffer);
	virtual int GetTotalVerticesCount(bool bPost) {return m_nAliveNumPart*4;}
	virtual int GetTotalFacesCount(bool bPost)  {return m_nAliveNumPart*2;}

public:
	Mex2ParticleEmitter();
	~Mex2ParticleEmitter();
	void	Read(Mex2Pointer inP,int inSize);
	void	Read2(Mex2Pointer inP,int inSize, DWORD version);
    void	Read3( Mex2Pointer inP, int inSize, DWORD version );    //added by zhuomeng.hu		[2/12/2011]
    void	Read4( Mex2Pointer inP, int inSize, DWORD version );    //added by zhuomeng.hu		[2/18/2011]
	// 虚函数
	const char* GetName(){ return "" ; }
	const char* GetBindPartName(){ return m_szBindPartName; }

	void	Update( int nTime, float fScale, float* pfMatrices, float* pfmatModel  ,int nFrameId );
	void	Render( int nTime, short stTextureId, float fAlpha, bool bOverUI );
	int		GetLocalTextureID(){ return setting.nTextureId; }//setting->nTextureId; }
	virtual void SetLocalTextureID(int texid) { setting.nTextureId = texid; }
	void	SetActive( BOOL bActive ){ m_bIsActive = bActive; }
	void	SetPlaySpeed( float fPlaySpeed ){ m_fPlaySpeed = fPlaySpeed; }
	IMexParticleEmitter* Clone();
	void	Release();
	void	SetParentBoneID( int nBoneId ){ setting.nParentBoneId = nBoneId; }
	int		GetParentBoneID(){ return setting.nParentBoneId; }

	/*
	 * 为模型查看器增加接口, 用于修改粒子发射器的参数
	 * 2012.5.29 wangshuai
	 */
	Mex2ParticleEmitterSetting4 * GetSetting() { return &setting; }
	void SetBindPartName(const char *szBindPart);
	BOOL & UseTimeBasedCell() { return m_bUseTimeBasedCell; }
	int & TimeBasedCellLoopTimes() { return m_nSeqLoopTimes; }
	BOOL & RotateParticle() { return m_bRotateParticle; }
	int & Rotate360DegreeCostTime() { return m_nRotate360DegreeCostTime; }
	BOOL & RandomDir() { return m_bRandomDir; }
	BOOL & RotNotFollowEmitter() { return m_bNoSelfRotate; }
	BOOL & UVRandomFirstCell() { return m_bUVRandomFirstCell; }
	BOOL & XYQuadLaydownInWorld() { return m_bXYInWorldSpace; }

	void SetSrcMex( IMex* pMex )
	{ 
		if( !pMex )
			return;
		Mex2* pMex2 = (Mex2*)( pMex );
		if( !pMex2 )
			return;

		pSrcMex = pMex2; 
	}

	static void SetMaxPartNum( int nNum ){ ms_nMaxPartNum = nNum; }
	static int GetMaxPartNum() { return ms_nMaxPartNum; }
protected:
	static int ms_nMaxPartNum;

protected:

	DWORD	dwVersion;
	BOOL	bReleased;
	
	//Mex2ParticleEmitterSetting*	setting;
	Mex2ParticleEmitterSetting4 setting;
	Mex2* pSrcMex;
	//
	Vector	vPos;

	float	m_fScale;
	int		m_nTime;
	float	m_fPlaySpeed;

	Vector vPlaneNormal;
	Vector	vPlaneXAxis;
	Vector vPlaneYAxis;
	//Vector vCameraSpaceUp;
	//Vector vCameraSpaceRight;
	Vector vPlaneViewUp;
	Vector vPlaneViewRight;
	DWORD	dwLastUpdateTime;
	DWORD	dwLastGenPartsTime;
	int		m_nNumPart;
	int		m_nAliveNumPart;
	Mex2Particle*		particles;//[MEX2_EMITTER_MAX_PARTICLE];
	BOOL	m_bIsActive;
	BOOL	m_bSquirtted;
	char	m_szBindPartName[MEX2_MAX_NAME];;
	BOOL	m_bUseTimeBasedCell;
	int		m_nSeqLoopTimes;
	
	BOOL	m_bRandomDir;		    // 产生的粒子贴图是否随即方向                added by ZhuoMeng.Hu		[8/5/2010]
    BOOL    m_bNoSelfRotate;        // 粒子是否跟随发射器的变换而旋转增加开关    added by zhuomeng.hu		[1/30/2011]
    BOOL    m_bUVRandomFirstCell;   // 粒子的UV动画是否随机产生第一帧            added by zhuomeng.hu		[3/10/2011]
    BOOL    m_bXYInWorldSpace;      // 粒子的XYQuad模式下，在世界坐标系中放平    added by zhuomeng.hu		[3/17/2011]
	int		m_nRotate360DegreeCostTime;
	BOOL	m_bRotateParticle;
	// added, jiayi, [2010/6/9]
	// render传入的alpha，这里记录下
	float	m_fRenderAlpha;

	BOOL	IsParticleDead( Mex2Particle* pParticle, int nTime );
	void	GenParticle( Mex2Particle* pParticle, int nTime );
	void	UpdateParticle( Mex2Particle* pParticle, int nTime, float* pfMatrices, MeMatrix* pmatModel = NULL );
	void	GenDirection( Vector* axis, float fAngle, Vector* dir );
	void	MakeARenderParticle( Mex2Particle* pParticle, SEmitterVertex* vertex, float fAlpha );

	void	Reset();
	
	//   added 2004.07.01
	//void	SetActive( BOOL b ){ m_bIsActive = b; }

// private:	
// 	static LPDIRECT3DVERTEXBUFFER9 m_pVB;
// 	static LPDIRECT3DINDEXBUFFER9 m_pIB;
};

class Mex2ParticleEmitters:public IMexParticleEmitters, public MeCommonAllocObj<Mex2ParticleEmitters>
{
	friend Mex2;
public:
	void	Read(Mex2Pointer inP,int inSize, DWORD version);
	void	Bind( Mex2* pMex );

	int		GetEmitterCount(){ return vectorParticleEmitter.size(); }
	IMexParticleEmitter* GetEmitter( int i ){ return vectorParticleEmitter[i]; }

	virtual void   AppendEmitter(IMexParticleEmitter *e) { vectorParticleEmitter.push_back(dynamic_cast<Mex2ParticleEmitter *> (e)); }
	
protected:
	std::vector<Mex2ParticleEmitter*> vectorParticleEmitter;
	
	//void	Update( int nTime );
	//void	Render( int nTime );
	//   added 2004.07.16
	
};

#endif