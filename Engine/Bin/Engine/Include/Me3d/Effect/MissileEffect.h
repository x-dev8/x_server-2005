#pragma once
#include <windows.h>
#include "Dxsdk/d3dx9.h"
#include <vector>
#include "EffectHollywood.h"
/*
	Missile 设计
	这是一种动画片中常见的导弹跟踪效果
	导弹由两部分构成
	1.模型
	2.尾部残影

	每一个Missile都有自己的飞行轨迹，
	画面上的表现是若干导弹散乱的散开，
	然后以优雅的曲线飞行轨迹追踪目标命中的过程

	飞行轨迹主要依靠尾部残影来表达，
	也可以通过导弹自身模型中带有的粒子或者条带来实现
*/
class CMexEffectCtrl;
class CMissileEffect:public CBaseEffect
{
public:
	enum
	{
		eSpace_PlaneFaceToUp,			// 朝天的平面，(0,0,1)方向，
		eSpace_PlaneFaceToPoint,		// 面朝着起点方向的平面
		eSpace_Sphere,					// 球体空间
		eSpace_Line,					// 线段空间
	};
	enum
	{
		ePoint_Average,					// 均匀分布
		ePoint_Random,					// 随机分布
	};
	enum
	{
		eAction_WaitStart,				// 等待开始
		eAction_FadeIn,					// 淡入
		eAction_Shoot,					// 发射状态,可以认为是飞行的第一种状态,
		eAction_Drop,					// 下落或者升起状态,可以认为是飞行的第二种状态
										// 有一种效果是从天降
		eAction_Hit,					// 命中了
		eAction_FadeOut,				// 淡出状态,命中后立即进入淡出状态
		eAction_Dead,					// 死亡状态，不需要再处理了
		eAction_Max,
	};

	enum
	{
		eBulletsBorn_SameTime,			// 同时诞生
		eBulletsBorn_OneByOne,			// 一个接一个诞生，
		eBulletsBorn_Random,			// 随机诞生
	};
	struct Texture
	{
		char	szPath[MAX_PATH];		// 路径
		int		nTextureId;				// 系统注册的纹理id
		Texture():nTextureId(-1){ memset( szPath, 0x00, MAX_PATH ); }
	};
	struct Space
	{
		int		nType;
		D3DXVECTOR3 vCenter;
		float	fRadius;
	};
	struct Action
	{
		BOOL	bActive;				// 是否是活动的状态，否则略过
		DWORD	dwStartTime;			// 开始时间
		DWORD	dwPeriod;				// 周期
		float	fSpeed;					// 速度
		float	fAcc;					// 加速度
		Action();
	};
	struct Bullet
	{
		CMexEffectCtrl* pEffectCtrl;	// 模型对象
		int		nFrameID;
		int		nAction;
		float	fAlpha;
		
		D3DXVECTOR3 vPos;

		D3DXVECTOR3 vShootStartPos;			// 起始位置
		D3DXVECTOR3 vShootEndPos;			// 目标位置
		D3DXVECTOR3 vShootDir;
		float		fShootDistance;
		D3DXVECTOR3 vDropStartPos;
		D3DXVECTOR3 vDropEndPos;
		float		fDropDistance;
		
		Action	actions[eAction_Max];	
		Bullet();
	};
	struct BaseAndRandom
	{
		float fBase;
		float fRandom;
		BaseAndRandom():fBase(0.0f),fRandom(0.0f){}
		float GetResult();
	};
	struct Params
	{
		BaseAndRandom WaitStart_Wait;
		BaseAndRandom WaitStart_Period;
		BaseAndRandom FadeIn_Period;
		BaseAndRandom Shoot_Period;
		BaseAndRandom Shoot_Speed;
		BaseAndRandom Drop_Period;
		BaseAndRandom Drop_Speed;
		BaseAndRandom Drop_Height;
		BaseAndRandom FadeOut_Period;
	};
public:
	CMissileEffect();

	virtual BOOL IsDead( DWORD dwTime );
	virtual void Update( DWORD dwTime, D3DXVECTOR3 vPos, float fDistance );
	virtual void Release();
	virtual void SetDead();
	//virtual void Cull( D3DXVECTOR3 vPos, float fDistance );
	BOOL		LoadSetting( const char* pszFilename );
	BOOL		Compile( const char* pszFilename, BYTE** ppbyBuffer, int* pnBufferSize );
	BOOL		LoadFromMemory( BYTE* pbyBuffer, int nBufferSize );
	void		Destroy();
	void		Start();
	void		Render();

	void		GetBaseAndRandom( const char* pszLine, float& fBase, float& fRandom );
	float		GetBaseAndRandomResult( BaseAndRandom& bar );
public:
	D3DXVECTOR3 m_vPos;
	IEffectHelper* m_pMaster;
	int			m_nAction;
	char		m_szHitSound[MAX_PATH];		// bullet命中时的音效
	char		m_szLaunchSound[MAX_PATH];	// bullet发射时的音效
	char		m_szHitEffect[MAX_PATH];	// 命中时调用的特效，

	DWORD		m_dwFirstHitTime;			// 第一枚bullet命中的确切时间，用来匹配的
											// 弹出服务器下发的上海，
	Space		m_ShootStartSpace;
	Space		m_ShootTargetSpace;
	Space		m_DropStartSpace;
	Space		m_DropTargetSpace;
protected:
	BOOL		m_bIsDead;
	DWORD		m_dwStartTime;
	DWORD		m_dwLife;
	float		m_fScale;
	

	int			m_nBulletBornType;			// bullet出生的方式
	DWORD		m_dwBulletBornTimeParam;	// 单个bullet的出生时间参数，
											// 根据不同的出生方式有不同的解释


	Params		m_params;

	

	BOOL		m_abActionActive[eAction_Max];

	char		m_szModel[MAX_PATH];		// 模型文件名
	int			m_nNumBullet;
	std::vector<Bullet>		m_bullets;

};
