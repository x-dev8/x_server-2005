#pragma once
#include <Windows.h>
#include "Dxsdk/d3dx9.h"
#include "EffectHollywood.h"
class MexAnimCtrl;
class CMexEffectCtrl;
/*
	一个instance会在画面上渲染一次，
	所有的instance具有相同的特性，都会继承相同属性，
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
		eActionStand,			// 原地不动
		eActionFollow,			// 跟随
		eActionFollowPos,		// 仅位置跟随
		eActionTrace,			// 追踪
		eActionFall,			// 坠落
		eActionSpray,			// 原地喷射
		eActionFollowSpray,		// 跟随主角的原地喷射
		eActionPointToNpc,		// 指向Npc的特效
		eActionSkillBarCollect,	// 技能条的收集特效
		eActionFollowPoint,		// 指向技能,考虑高度
		eActionPointAoe,		// 点aoe技能
		eActionFollowCamera, //跟随摄像机 add by yanli 2010-6-30
		eMaxAction,
	};
	enum
	{
		eTrackTypeLine,			// 直线轨迹
		eTrackTypeParabola,		// 抛物线轨迹
		eTrackTypeGravity,		// 重力轨迹
		//eTrackTypeLineXup,
		//eTrackTypeLineXdown,
		//eTrackTypeLineYup,
		//eTrackTypeLineYdown,
		//eTrackTypeLineZ,
		eMaxTrackType,
	};
	//enum
	//{
	//	eStartLocCenter,		// 初始位置为中心
	//	eStartLocRandom,		// 以中心
	//};

	struct Instance
	{
		//////////////////下面是从配置文件读取配置
		int			nMode;
//		int			nModelID;				// 特效模型的ID
		int			nFrameID;				// 动画帧编号
		float		fFrameFactor;
		float		fAlpha;					// 特效的当前透明

		///////////////////////
		BOOL		bUpdateBornPos;			// 更新出生位置
		BOOL		bOutOfLookerView;		// 远离主角的视野
		float		fRot;					// 当前旋转
		float		fRotCorrect;			// 当前角度的修正

		////////////////
		DWORD		dwBornTime;				// 出生时间
		DWORD		dwLife;					// 生命
		BOOL		bVisible;				// 是否可见
		DWORD		dwVisibleChangeTime;	// 是否可见的属性改变时间
		BOOL		bPlayOver;			// 是否播放结束
		BOOL		bDead;					// 是否已经死亡

		///////////////////////
		DWORD		dwDeadTime;				// 死亡时间
		DWORD		dwPlayOverTime;			// 播放结束时间
		DWORD		dwPlayOverRenderTime;	// 播放结束渲染时间
		//DWORD		dwDeadRenderTime;		// 死亡渲染时间
		int			nNumLoop;				// 循环次数
		BOOL		bLoopForever;			// 一直循环
		BOOL		bRotateTogether;		// 一起旋转
		float		fScale;					// 当前缩放
		float		fBornScale;				// 出生缩放
		int			nBindWhere;				// 特效出发点绑定位置
		int			nTargetBindWhere;		// 特效目标点绑定位置

		//////////////////////////
		int			nAction;				// 动作类型，比如跟随，追踪等
		int			nActionTime;			// 动作执行时间
		BOOL		bDisapearAfterAction;	// action完成后是否消失
		int			nTrackType;				// 轨迹类型
		float		fParabolaHeight;		// 抛物线轨迹高度
		float		fFallHeight;			// 坠落的高度
		float		fXOffset;
		float		fYOffset;
		float		fZOffset;
		float		fGroundZ;				// 地面的z
		// added, jiayi, [2009/10/19]
		BOOL		bOriginalSize;			// 原始大小，不进行缩放

        BOOL        bOriginalAlpha;         // Alpha是否不随 pMaster 的Alpha而改变

		//////////////////////////
		D3DXVECTOR3 vBornPos;				// 诞生时的位置
		D3DXVECTOR3 vTargetPos;				// 目标位置
		D3DXVECTOR3 vPos;					// 当前位置
		//D3DXVECTOR3 vNormal;				// 当前的法线位置
		D3DXVECTOR3 vAxisOfZRotation;		// 垂直旋转轴
		float		fRotZ;					// 垂直旋转角度

		/////////////////////////
		IEffectHelper* pMaster;				// 出发的位置
		IEffectHelper* pTarget;				// 目标的位置
		CMexEffectCtrl* pEffectCtrl;

		int			nCarryNumber;			// 携带的数字，命中时出现
		char		szModel[MAX_PATH];		// 模型文件
		// added, jiayi, [2009/6/2]
		float		fDelay;					// 技能播放延迟时间

        // 抛物线轨迹特效                   added by zhuomeng.hu		[3/4/2011]
        D3DXVECTOR3 vTargetGroundPos;       // 目标地表位置
        float       fParabolaTime;          // 抛物线经历总时间，单位秒
        float       fParabolaAngle;         // 初速度与水平面夹角
        float       fRotX;                  // 本地坐标系中绕X轴旋转的夹角
        float       fZVelocity0;            // Z轴方向的初速度，方向向上
        float       fZAcceleration;         // Z轴方向的加速度，方向向下
        char		szHitEffect[MAX_PATH];  // 轨迹落地时需要播放的特效路径

        typedef void ( *FunParabolaEndCallBack )( const char* pEffectName, D3DXVECTOR3 vPos );
        FunParabolaEndCallBack pParabolaEndFun; // 轨迹落地回调
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
	int			m_nCameraShakeType;			//摄象机的振动类型
	float		m_fMaxShakeWaveRange;		//震波影响最弱的范围
	float		m_fMinShakeWaveRange;		//震波影响最强的范围
	float		m_fMaxShakeRange;			//最大振幅
	float		m_fMinShakeRange;			//最小振幅
	DWORD		m_dwShakeKeepTime;			//震动维持时间
	DWORD		m_dwShakeStartTime;			//震动开始时间
	bool		m_isDead;
	int			m_nEffectQuoterId;
};

