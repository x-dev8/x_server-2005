#include "stdafx.h"
#include "FightBot.h"
/*
    T开头的摆摊
    H开头的交易
    
    T开头单数的摆摊，双数的请求交易
    H开头单数的请求，H开头双数的找单数的
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

    void think(); // 每5分钟切换一种随机状态

    virtual void InitPlayGame(UINT mapid = 0);
    virtual void PlayGame();

    void ReqBusiness(short playerid);   // 发出交易请求

    void Stallage();   // 摆摊
    void UnStallage();  // 取消摆摊
    void ReqQueryStallage(); // 响应摆摊
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
    short CheckName(const std::string &TarageName); // 判断名字,双数,返回0  单数,返回1 名字错误 返回-1
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