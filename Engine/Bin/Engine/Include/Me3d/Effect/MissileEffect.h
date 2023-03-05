#pragma once
#include <windows.h>
#include "Dxsdk/d3dx9.h"
#include <vector>
#include "EffectHollywood.h"
/*
	Missile ���
	����һ�ֶ���Ƭ�г����ĵ�������Ч��
	�����������ֹ���
	1.ģ��
	2.β����Ӱ

	ÿһ��Missile�����Լ��ķ��й켣��
	�����ϵı��������ɵ���ɢ�ҵ�ɢ����
	Ȼ�������ŵ����߷��й켣׷��Ŀ�����еĹ���

	���й켣��Ҫ����β����Ӱ����
	Ҳ����ͨ����������ģ���д��е����ӻ���������ʵ��
*/
class CMexEffectCtrl;
class CMissileEffect:public CBaseEffect
{
public:
	enum
	{
		eSpace_PlaneFaceToUp,			// �����ƽ�棬(0,0,1)����
		eSpace_PlaneFaceToPoint,		// �泯����㷽���ƽ��
		eSpace_Sphere,					// ����ռ�
		eSpace_Line,					// �߶οռ�
	};
	enum
	{
		ePoint_Average,					// ���ȷֲ�
		ePoint_Random,					// ����ֲ�
	};
	enum
	{
		eAction_WaitStart,				// �ȴ���ʼ
		eAction_FadeIn,					// ����
		eAction_Shoot,					// ����״̬,������Ϊ�Ƿ��еĵ�һ��״̬,
		eAction_Drop,					// �����������״̬,������Ϊ�Ƿ��еĵڶ���״̬
										// ��һ��Ч���Ǵ��콵
		eAction_Hit,					// ������
		eAction_FadeOut,				// ����״̬,���к��������뵭��״̬
		eAction_Dead,					// ����״̬������Ҫ�ٴ�����
		eAction_Max,
	};

	enum
	{
		eBulletsBorn_SameTime,			// ͬʱ����
		eBulletsBorn_OneByOne,			// һ����һ��������
		eBulletsBorn_Random,			// �������
	};
	struct Texture
	{
		char	szPath[MAX_PATH];		// ·��
		int		nTextureId;				// ϵͳע�������id
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
		BOOL	bActive;				// �Ƿ��ǻ��״̬�������Թ�
		DWORD	dwStartTime;			// ��ʼʱ��
		DWORD	dwPeriod;				// ����
		float	fSpeed;					// �ٶ�
		float	fAcc;					// ���ٶ�
		Action();
	};
	struct Bullet
	{
		CMexEffectCtrl* pEffectCtrl;	// ģ�Ͷ���
		int		nFrameID;
		int		nAction;
		float	fAlpha;
		
		D3DXVECTOR3 vPos;

		D3DXVECTOR3 vShootStartPos;			// ��ʼλ��
		D3DXVECTOR3 vShootEndPos;			// Ŀ��λ��
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
	char		m_szHitSound[MAX_PATH];		// bullet����ʱ����Ч
	char		m_szLaunchSound[MAX_PATH];	// bullet����ʱ����Ч
	char		m_szHitEffect[MAX_PATH];	// ����ʱ���õ���Ч��

	DWORD		m_dwFirstHitTime;			// ��һöbullet���е�ȷ��ʱ�䣬����ƥ���
											// �����������·����Ϻ���
	Space		m_ShootStartSpace;
	Space		m_ShootTargetSpace;
	Space		m_DropStartSpace;
	Space		m_DropTargetSpace;
protected:
	BOOL		m_bIsDead;
	DWORD		m_dwStartTime;
	DWORD		m_dwLife;
	float		m_fScale;
	

	int			m_nBulletBornType;			// bullet�����ķ�ʽ
	DWORD		m_dwBulletBornTimeParam;	// ����bullet�ĳ���ʱ�������
											// ���ݲ�ͬ�ĳ�����ʽ�в�ͬ�Ľ���


	Params		m_params;

	

	BOOL		m_abActionActive[eAction_Max];

	char		m_szModel[MAX_PATH];		// ģ���ļ���
	int			m_nNumBullet;
	std::vector<Bullet>		m_bullets;

};
