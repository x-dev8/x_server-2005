#include "stdafx.h"
#include "FightBot.h"
/*
    T��ͷ�İ�̯
    H��ͷ�Ľ���
    
    T��ͷ�����İ�̯��˫����������
    H��ͷ����������H��ͷ˫�����ҵ�����
*/
#define MaxTempBargainingList 30

class CBusinessBot : public CFightBot
{
public:
    enum BusinessState
    {
        EBS_Stallageing = 0,
        EBS_EndStallage = 1,
        EBS_ReqBusiness = 2,
        EBS_Businessing = 3,
        EBS_SureBusiness = 4,
        EBS_ReqStallage = 5,
        EBS_Idle,
    };

    enum CheckNameResult
    {
        ECNR_Double = 0,
        ECNR_Single = 1,
        ECNR_NameError = -1,
    };

    enum ReqItemId
    {
        EREQ_StartItemId = 5701,
        EREQ_EndItemId = 5706,
    };
public:
    typedef std::vector<MsgBargainingNow> BargainList;

    CBusinessBot();
    ~CBusinessBot();

    void think(); // ÿ5�����л�һ�����״̬

    virtual void InitPlayGame(UINT mapid = 0);
    virtual void PlayGame();

    void ReqBusiness(short playerid);   // ������������

    void Stallage();   // ��̯
    void UnStallage();  // ȡ����̯
    void ReqQueryStallage(); // ��Ӧ��̯
    bool CheckSelfBag();
    PlayerInfo* GetTarget();
    void ReqBusinessItem();
    void ReqMoney();
    short FindStallageList(DWORD id);
    short FindRandStallageList();
public:
    virtual void SwitchMsg(Msg* pMsg);
    virtual void OnMsgTurnOnOffPrivateShop(Msg* pMsg);
    virtual void OnMsgRefeashPrivateShopItem(Msg* pMsg);
    virtual void OnMsgPrivateShopItemSell(Msg* pMsg);
    virtual void OnMsgAckBuyPrivateShopItem(Msg* pMsg);
    virtual void OnMsgAckBargaining(Msg* pMsg);
    virtual void OnMsgQueryBargaining(Msg* pMsg);
    virtual void OnMsgBargainingNow(Msg *pMsg);
    virtual void OnMsgAckResult(Msg* pMsg);
private:
    short CheckName(const std::string &TarageName); // �ж�����,˫��,����0  ����,����1 ���ִ��� ����-1
    void ClearTempList();
    bool IsEmptyBag();
private:
    short CurRunState;
    DWORD ChangeStateTime;
    DWORD LastBusuinessTime;
    DWORD CheckItemTime;
    short IsNameDouble;            
    bool bOpenPrivateShop;
    PlayerInfo* LastShopTarget;
    SPrivateShopItem TargetShopItem[ITEM_PRIVATE_SHOP_BAGMAX];
    typedef std::vector<GameCharID> OtherGamePlayerIdList;
    OtherGamePlayerIdList StallagePlayers;
    //BargainList MsgBargainingNows;

    SCharItem BargainingList[MaxTempBargainingList];
    SCharItem SelfBargainingList[MaxTempBargainingList];
    DWORD LastBargainTime;
    DWORD IdleTime;
};