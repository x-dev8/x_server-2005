#pragma once
#include <Windows.h>
#include "Dxsdk/d3dx9.h"
#include "EffectHollywood.h"
class MexAnimCtrl;
class CMexEffectCtrl;
/*
	һ��instance���ڻ�������Ⱦһ�Σ�
	���е�instance������ͬ�����ԣ�����̳���ͬ���ԣ�
*/
class CModelEffect:public CBaseEffect
{
public:
	enum
	{
		//eMaxInstance = 16,
		eMaxInstance = 5,
	};

	enum
	{
		eActionStand,			// ԭ�ز���
		eActionFollow,			// ����
		eActionFollowPos,		// ��λ�ø���
		eActionTrace,			// ׷��
		eActionFall,			// ׹��
		eActionSpray,			// ԭ������
		eActionFollowSpray,		// �������ǵ�ԭ������
		eActionPointToNpc,		// ָ��Npc����Ч
		eActionSkillBarCollect,	// ���������ռ���Ч
		eActionFollowPoint,		// ָ����,���Ǹ߶�
		eActionPointAoe,		// ��aoe����
		eActionFollowCamera, //��������� add by yanli 2010-6-30
		eMaxAction,
	};
	enum
	{
		eTrackTypeLine,			// ֱ�߹켣
		eTrackTypeParabola,		// �����߹켣
		eTrackTypeGravity,		// �����켣
		//eTrackTypeLineXup,
		//eTrackTypeLineXdown,
		//eTrackTypeLineYup,
		//eTrackTypeLineYdown,
		//eTrackTypeLineZ,
		eMaxTrackType,
	};
	//enum
	//{
	//	eStartLocCenter,		// ��ʼλ��Ϊ����
	//	eStartLocRandom,		// ������
	//};

	struct Instance
	{
		//////////////////�����Ǵ������ļ���ȡ����
		int			nMode;
//		int			nModelID;				// ��Чģ�͵�ID
		int			nFrameID;				// ����֡���
		float		fFrameFactor;
		float		fAlpha;					// ��Ч�ĵ�ǰ͸��

		///////////////////////
		BOOL		bUpdateBornPos;			// ���³���λ��
		BOOL		bOutOfLookerView;		// Զ�����ǵ���Ұ
		float		fRot;					// ��ǰ��ת
		float		fRotCorrect;			// ��ǰ�Ƕȵ�����

		////////////////
		DWORD		dwBornTime;				// ����ʱ��
		DWORD		dwLife;					// ����
		BOOL		bVisible;				// �Ƿ�ɼ�
		DWORD		dwVisibleChangeTime;	// �Ƿ�ɼ������Ըı�ʱ��
		BOOL		bPlayOver;			// �Ƿ񲥷Ž���
		BOOL		bDead;					// �Ƿ��Ѿ�����

		///////////////////////
		DWORD		dwDeadTime;				// ����ʱ��
		DWORD		dwPlayOverTime;			// ���Ž���ʱ��
		DWORD		dwPlayOverRenderTime;	// ���Ž�����Ⱦʱ��
		//DWORD		dwDeadRenderTime;		// ������Ⱦʱ��
		int			nNumLoop;				// ѭ������
		BOOL		bLoopForever;			// һֱѭ��
		BOOL		bRotateTogether;		// һ����ת
		float		fScale;					// ��ǰ����
		float		fBornScale;				// ��������
		int			nBindWhere;				// ��Ч�������λ��
		int			nTargetBindWhere;		// ��ЧĿ����λ��

		//////////////////////////
		int			nAction;				// �������ͣ�������棬׷�ٵ�
		int			nActionTime;			// ����ִ��ʱ��
		BOOL		bDisapearAfterAction;	// action��ɺ��Ƿ���ʧ
		int			nTrackType;				// �켣����
		float		fParabolaHeight;		// �����߹켣�߶�
		float		fFallHeight;			// ׹��ĸ߶�
		float		fXOffset;
		float		fYOffset;
		float		fZOffset;
		float		fGroundZ;				// �����z
		// added, jiayi, [2009/10/19]
		BOOL		bOriginalSize;			// ԭʼ��С������������

        BOOL        bOriginalAlpha;         // Alpha�Ƿ��� pMaster ��Alpha���ı�

		//////////////////////////
		D3DXVECTOR3 vBornPos;				// ����ʱ��λ��
		D3DXVECTOR3 vTargetPos;				// Ŀ��λ��
		D3DXVECTOR3 vPos;					// ��ǰλ��
		//D3DXVECTOR3 vNormal;				// ��ǰ�ķ���λ��
		D3DXVECTOR3 vAxisOfZRotation;		// ��ֱ��ת��
		float		fRotZ;					// ��ֱ��ת�Ƕ�

		/////////////////////////
		IEffectHelper* pMaster;				// ������λ��
		IEffectHelper* pTarget;				// Ŀ���λ��
		CMexEffectCtrl* pEffectCtrl;

		int			nCarryNumber;			// Я�������֣�����ʱ����
		char		szModel[MAX_PATH];		// ģ���ļ�
		// added, jiayi, [2009/6/2]
		float		fDelay;					// ���ܲ����ӳ�ʱ��

        // �����߹켣��Ч                   added by zhuomeng.hu		[3/4/2011]
        D3DXVECTOR3 vTargetGroundPos;       // Ŀ��ر�λ��
        float       fParabolaTime;          // �����߾�����ʱ�䣬��λ��
        float       fParabolaAngle;         // ���ٶ���ˮƽ��н�
        float       fRotX;                  // ��������ϵ����X����ת�ļн�
        float       fZVelocity0;            // Z�᷽��ĳ��ٶȣ���������
        float       fZAcceleration;         // Z�᷽��ļ��ٶȣ���������
        char		szHitEffect[MAX_PATH];  // �켣���ʱ��Ҫ���ŵ���Ч·��

        typedef void ( *FunParabolaEndCallBack )( const char* pEffectName, D3DXVECTOR3 vPos );
        FunParabolaEndCallBack pParabolaEndFun; // �켣��ػص�
        void SetParabolaEndCallBack( FunParabolaEndCallBack pFun );

		Instance();
	};

public:
	CModelEffect(void);

public:
	virtual ~CModelEffect(void);

public:
	virtual BOOL IsDead( DWORD dwTime );
	virtual void Update( DWORD dwTime, D3DXVECTOR3 vPos, float fDistance );
	virtual void Render();
	virtual void Release();
	virtual BOOL LoadSetting( const char* pszFilename, BOOL bMilti  = false);
	static BOOL Compile( const char* pszFilename, BYTE** ppbyBuffer, int* pnBufferSize );
	//virtual void Cull( D3DXVECTOR3 vPos, float fDistance );

	BOOL	LoadFromMemory( BYTE* pbyBuffer, int nBufferSize );
	void	Start();
	virtual void	TryStart();
	void	SetDead();
	BOOL	IsInstanceDead( DWORD dwTime, Instance* pInstance );
	BOOL	IsInstancePlayOver( DWORD dwTime, Instance* pInstance );
	void	UpdateInstance( DWORD dwTime, Instance* pInstance );
	Instance* AllocInstance();
	Instance* GetInstance( int nInst );
	//virtual BOOL ConvertToBin( const char* pszFilename, BYTE** ppbyBuffer, int* pnBufferSize );
	//virtual BOOL LoadSetting( BYTE* pbyBuffer, int nBufferSize );
	//virtual BOOL LoadInstanceSetting( Instance* pInst, BYTE* pbyBuffer, int nBufferSize );

	void SetEffectQuoter( IEffectQuoter* pEffectQuoter );

public:
	char*		GetSound(bool isMale)
	{
		if (isMale)
		{
			return m_szMaleSound;
		}
		return m_szFemaleSound;
	}
	char		m_szModel[MAX_PATH];
	char		m_szMaleSound[MAX_PATH];
	char		m_szFemaleSound[MAX_PATH];
	DWORD		m_dwBornTime;
	DWORD		m_dwLife;
	DWORD		m_dwFlyTime;
	int			m_nTerminateMode;
	int			m_nOneLoopTime;
	int			m_nNumInstance;
	int			m_nMaxInstance;
	Instance	m_InstTemplate;
	Instance	m_Instances[eMaxInstance];
	DWORD		m_dwDelay;
	float		m_fRadius;
	float		m_fScale;
	BOOL		m_bMexLoaded;
	int			m_nCameraShakeType;			//�������������
	float		m_fMaxShakeWaveRange;		//��Ӱ�������ķ�Χ
	float		m_fMinShakeWaveRange;		//��Ӱ����ǿ�ķ�Χ
	float		m_fMaxShakeRange;			//������
	float		m_fMinShakeRange;			//��С���
	DWORD		m_dwShakeKeepTime;			//��ά��ʱ��
	DWORD		m_dwShakeStartTime;			//�𶯿�ʼʱ��
	bool		m_isDead;
	int			m_nEffectQuoterId;
};

