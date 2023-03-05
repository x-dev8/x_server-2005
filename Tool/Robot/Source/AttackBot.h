#pragma once
#include "Bot.h"

enum enumLXinFaType
{
	Enum_GiveId,
	Enum_RandId,
	Enum_NoRand,
};
struct AttackSkill
{
    AttackSkill()
    {
        Clear();
    }

    void Clear()
    {
        shID = 1000;
        dwSpaceTime = 0;
        Level = 1;
    }

    bool operator ==  (const unsigned short& second)
    {
        return shID == second;
    }

	USHORT shID;
	DWORD dwSpaceTime;
    USHORT Level;
};

class CAttackBot : public BaseRobot
{
public:
    enum AttType
    {
        EAT_TestEctypeType = 0,
        EAT_NormalType = 1,
    };
    enum AttackTargetId
    {
        EATI_InitAttackTargetId = -1,
    };

    CAttackBot(void);
    CAttackBot(int AttackbotType);
    virtual ~CAttackBot(void);

    virtual void PlayGame();
    virtual void OnMsgSeeAttack3( Msg* pMsg );
	
	void SetAreaInfo(SAreaInfo *pAreaInfo);
	bool GetAreaInfo();		//是否有指定打怪区域
	void ClearAreaInfo() { m_xAreaInfo.nMap = -1; }
	//bool MoveToPoint(D3DXVECTOR3& xPos);
	bool AttackEnemy(); // 开始攻击
	

	void PlayAttack();

	virtual void InitPlayGame(UINT mapid = 0);
	virtual GameObjectId LockTarget();
	virtual PlayerInfo* GetLockPlayerInfo(GameObjectId shID);

protected:
	int GetAttackSkill(DWORD &dwSpaceTime);
	void AddUseSkill(USHORT nSkillID, DWORD dwTime);		//更新技能的使用时间
	bool CanUseSkill(USHORT nSkillID);						//判断技能是否可以用

	void InitEquipItem();									//初始化装备
	void InitAttackSkill();									//先得到所有可以攻击的技能
	void LearnXinFa( unsigned int nType = Enum_GiveId, unsigned int nXinFaLevel = 20, unsigned int nXinFaID = 0 ); // bRandom = true时，随机学习心法

protected:
    GameObjectId m_shTargetID;
    DWORD m_dwLastEquipTime;					//luo.qin 3.23
    DWORD m_dwLockTargetTime;
    DWORD m_dwLastUseSkillTime;
	DWORD m_shAttackCount;
	int m_nSkillStep;

	DWORD m_dwLastFlyTime;

	map<USHORT, DWORD> m_mapUseSkill;
	vector<AttackSkill> m_vecAttackSkill;		//存放攻击的技能

	DWORD m_ReqFlyTime;
protected:
	typedef map<USHORT, DWORD>::iterator mapiter;
    int AttackbotType;
};
