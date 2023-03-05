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
		eMaxHitPoint		= 16,		// ���HitPoint����
		eMaxParticleEmitter = 32,		// ������ӷ���������
		eMaxRibbonEmitter	= 16,		// ��󵶹�����
		eMaxName			= 256,		// ������ֳ���
		eMaxTask			= 3,		// �����������
		eMaxTextureStage	= 2,		// �����ͼ����
		//   added 2004.08.06
		eMaxLight			= 32		// ���ƹ�����
		//eMaxMtlAnim			= 4,
	};
	enum
	{
		eLastHitPoint		= 1,
		eFirstHitPoint		= 1<<1
	};
	struct SPlayTask
	{
		char	szActionname[eMaxName];	// ��������
		DWORD	dwStartTime;
		DWORD	dwOneLoopTime;			// ����һ���ʱ��
		DWORD	dwLoopTimes;			// ���Ŵ���
		DWORD	dwTimeOut;				// ��ʱ��һ����ʱ���������
		DWORD	dwPlayMode;				// ����ģʽ
		int		nSingleFrameID;			// ��֡����ģʽ�£�����֡���
		int		nBlendFrame0;
		int		nBlendFrame1;
		float	fBlendFactor;
		BOOL	bUpperBody;				// �ж����ϰ����������°�����
		BOOL	bLoopPlay;				// �ж��Ƿ��Ǹ�ѭ������
		DWORD	dwNeedBlendingTime;		// ��Ҫ����һ����������Blending��ʱ��

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

	// ������Ӳ�λ����������������
	// ����ģ��
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

	//ʵ��ѭ���Ĵ���
	int				m_nLoopTimes;
	int				m_nHitPointCount;
	int				m_nNumPlayTask;

	// ��������
	IMex*			m_pMex;
	MexCfg*		m_pMexCfg;
	MexCfgAvatarSetting* m_pAvatarSetting;
	MexReplaceableTextureProj m_ReplaceableTextureProj;

	// ȫ��Ķ���
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