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
	bool GetAreaInfo();		//�Ƿ���ָ���������
	void ClearAreaInfo() { m_xAreaInfo.nMap = -1; }
	//bool MoveToPoint(D3DXVECTOR3& xPos);
	bool AttackEnemy(); // ��ʼ����
	

	void PlayAttack();

	virtual void InitPlayGame(UINT mapid = 0);
	virtual GameObjectId LockTarget();
	virtual PlayerInfo* GetLockPlayerInfo(GameObjectId shID);

protected:
	int GetAttackSkill(DWORD &dwSpaceTime);
	void AddUseSkill(USHORT nSkillID, DWORD dwTime);		//���¼��ܵ�ʹ��ʱ��
	bool CanUseSkill(USHORT nSkillID);						//�жϼ����Ƿ������

	void InitEquipItem();									//��ʼ��װ��
	void InitAttackSkill();									//�ȵõ����п��Թ����ļ���
	void LearnXinFa( unsigned int nType = Enum_GiveId, unsigned int nXinFaLevel = 20, unsigned int nXinFaID = 0 ); // bRandom = trueʱ�����ѧϰ�ķ�

protected:
    GameObjectId m_shTargetID;
    DWORD m_dwLastEquipTime;					//luo.qin 3.23
    DWORD m_dwLockTargetTime;
    DWORD m_dwLastUseSkillTime;
	DWORD m_shAttackCount;
	int m_nSkillStep;

	DWORD m_dwLastFlyTime;

	map<USHORT, DWORD> m_mapUseSkill;
	vector<AttackSkill> m_vecAttackSkill;		//��Ź����ļ���

	DWORD m_ReqFlyTime;
protected:
	typedef map<USHORT, DWORD>::iterator mapiter;
    int AttackbotType;
};
