#pragma once
#include <windows.h>
#include <MeFoundation/MeFoundationPCH.h>
#include <MeFoundation/MeLoopThreadProcedure.h>


class IMex;
class MexCfg;
class CPlayerAnim;
class CWSModelEffect;
class CPlayer;

namespace LoopLoadType
{
	enum
	{
		ePlayerEquip,
		eModelEffect,
		eMonsterModel,
		eMount = eMonsterModel,
		ePlayerName,
		eReqCount
	};
}


class Mex2WithMexReq : public MeLoopThreadReq
{
public:
	virtual void Destroy();
	virtual bool ProcessInThread( bool bFailed = false );
};
class PlayerEquipReq : public Mex2WithMexReq
{
public:
	CPlayerAnim* m_pAnim;
	CPlayer* m_pPlayer;			// 用CPlayer指针判断加载后是否有效
	int		m_nType;
	char	m_szSkin[MAX_PATH];
	INT		m_nSpecularTexID;
	PlayerEquipReq()
	{
		m_nType = -1;
		m_nSpecularTexID = -1;
		m_nObjectType = LoopLoadType::ePlayerEquip;
		m_pPlayer = NULL;
		m_pAnim = NULL;
		ZeroMemory( m_szSkin, sizeof(m_szSkin) );
	}
	virtual ~PlayerEquipReq();
	virtual void Process();
	bool ProcessInThread( bool bFailed = false );
};

class ModelEffectReq : public Mex2WithMexReq
{
public:
	CWSModelEffect* m_pModelEffect; 
	ModelEffectReq():m_pModelEffect(NULL)
	{
		m_nObjectType = LoopLoadType::eModelEffect;
	}

	virtual void Process();
};

class MonsterModelReq : public Mex2WithMexReq
{
public:
	CPlayerAnim*	m_pAnim;
	CPlayer*		m_pPlayer;			// 用CPlayer指针判断加载后是否有效
	char			m_szSkin[MAX_PATH];
	MonsterModelReq():m_pAnim(NULL)
	{
		m_nObjectType = LoopLoadType::eMonsterModel;
		ZeroMemory( m_szSkin, sizeof(m_szSkin) );
	}
	virtual ~MonsterModelReq();
	virtual void Process();
	virtual bool ProcessInThread( bool bFailed = false );
};

class MountReq : public MonsterModelReq
{
public:
	bool m_bPlayEffect;
	int  m_nDromeId;
	MountReq() : m_bPlayEffect(true), m_nDromeId(-1)
	{
		m_nObjectType = LoopLoadType::eMount;
	}

	virtual void Process();
};

class PlayerNameReq : public MeLoopThreadReq
{
public:
	CPlayer* m_pPlayer;
	PlayerNameReq() : m_pPlayer( 0 )
	{
		m_nObjectType = LoopLoadType::ePlayerName;
	}
	virtual ~PlayerNameReq();
	virtual void Destroy(){}
	virtual void Process();
	virtual bool ProcessInThread( bool bFailed = false ){ return true; }
};