#pragma  once

#include "Me3d/include.h"
#include "Me3d/AnimTimeLine.h"
//#include "Me3d/Model/stdcharskeleton.h"
#include "Me3d/Model/MexConfig.h"
#include "Me3d/Model/MexRes.h"
#include "Me3d/engine/Engine.h"
#include "Me3d/Engine/TextureManagerInstance.h"
//#include "Me3d/Model/Avatar.h"

class AnimTimeLine;
class MexCfg;
class MexCfgSequence;
class Mex2;
class CStdCharSkeleton;
class MtlAnim;
class MexAnimCtrl;
class MexAnimCtrlSkeleton;

class CMexEffectCtrl : public MeCommonAllocObj<CMexEffectCtrl>
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
		eMaxHitPoint		= 16,		// 最大HitPoint数量
		eMaxParticleEmitter = 32,		// 最大粒子发射器数量
		eMaxRibbonEmitter	= 16,		// 最大刀光数量
		eMaxName			= 256,		// 最大名字长度
		eMaxTask			= 3,		// 最大任务数量
		eMaxTextureStage	= 2,		// 最大贴图层数
		//   added 2004.08.06
		eMaxLight			= 32		// 最大灯光数量
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
	CMexEffectCtrl();
	~CMexEffectCtrl();
	void	Destroy();

	virtual		void	Render3( float fTransparent );
	void		RenderSubset( int nSubset, IRenderer* pRenderer, float fAlpha );
	virtual		void	UpdateComponents( DWORD dwTime, MeMatrix* pMatrix );
public:
	IMex*		GetMex(){ return m_pMex; }
	MexCfg*	GetMexCfg(){ return m_pMexCfg; }
	void		SetMexCfg( MexCfg* pMexCfg ){ m_pMexCfg = pMexCfg; }
	MeMatrix* GetMatrices(){ return m_matrices; }
	MeMatrix* GetBoneMatrices(){ return m_matBones; }
	MeMatrix* GetSrcBoneMatrices(){ return m_matSrcBones; }

	void		SetFrameID( int nFrameID ){ m_nFrameId = nFrameID; }
	int			GetFrameId(){ return m_nFrameId; }
	int			GetFrameCount();

	void		SetMex( IMex* pMex, MexCfg* pMexCfg );
	//   added 2004.06.03
	BOOL		PlayAnim( const char* pszActionname, DWORD dwOneLoopTime );
	BOOL		PlayAnim( SPlayTask* pTask );
	BOOL		PlayAnim( int nStartFrameID, int nEndFrameID, DWORD dwOneLoopTime );
	MexCfgSequence* GetTmpSequence(){ return &m_TmpSequence; }

	void		ClearAnims();
	DWORD		GetAnimTimeLength( const char* pszActionname );

	BOOL	ChangeAvatarSetting( const char* pszName );
	BOOL	CloseAvatarSetting( MexCfgAvatarSetting* pSetting );
	void	PushAnim( SPlayTask* pTask );
	void	ResetPlayTask( SPlayTask* pTask );

	// 更换搭接部位，比如武器，防具
	// 更换模型
	BOOL	ChangeModel( IMex* pMex, MexCfg* pMexCfg );
	void	ReleaseLastModel();

	BOOL	ChangePartModel( int nPartId, int nModelId );
	BOOL	ChangeModel( int nModelId );

	void SetPosition( float x, float y, float z ){ m_vPosition = Vector( x, y, z ); }
	Vector GetPosition(){ return m_vPosition; }
	void SetRotationZ( float theta ){ m_fRotTheta = theta; }
	void SetRotationX( float theta ){ m_fXRotTheta = theta; }
	void SetRotation( float theta, D3DXVECTOR3& vAxis, MeMatrix* pmatTransform );

	void SetScale( float scale ){ m_fScale = scale; }
	void SetParticleEmitterPlaySpeed( float fPlaySpeed );
	void CalcTransformMatrix( float x, float y, float z, float rot, float scale, MeMatrix* pmatTransform );
	void CalcTransformMatrix( MeMatrix* pmatTransform );
	void CalcTransformMatrix( MeMatrix* pmatTransform, float fRot, D3DXVECTOR3& vAxis );
protected:
	AnimTimeLine	m_timeLine;
	int				m_nStartFrameId;
	int				m_nEndFrameId;
	int				m_nFrameId;
	int				m_nLastFrameID;
	int				m_nFrameCount;
	DWORD			m_dwOneLoopTime;

	//实际循环的次数
	int				m_nLoopTimes;
	int				m_nHitPointCount;
	int				m_nNumPlayTask;

	// 动画数据
	IMex*			m_pMex;
	MexCfg*		m_pMexCfg;
	MexCfgAvatarSetting* m_pAvatarSetting;
	MexReplaceableTextureProj m_ReplaceableTextureProj;

	// 全身的动作
	MexCfgSequence* m_pSequence;
	MexCfgSequence m_TmpSequence;
	IMexParticleEmitter* m_pParticleEmitters[eMaxParticleEmitter];
	IMexRibbonEmitter* m_pRibbonEmitters[eMaxRibbonEmitter];

	MeMatrix*		m_matrices;
	MeMatrix*		m_matBones;
	MeMatrix*		m_matSrcBones;

	MeMatrix		m_matModel;
	MeMatrix		m_matModelInv;

	SPlayTask		m_PlayTasks[eMaxPlayTask+1];

	Vector		m_vPosition;
	float			m_fRotTheta;
	float			m_fXRotTheta;
	float			m_fScale;

	BOOL			m_bEnableRibbonEmitter;
	BOOL			m_bEnableParticleEmitter;

	int				m_nModelId;
};