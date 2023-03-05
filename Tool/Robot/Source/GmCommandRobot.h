
#ifndef _GMCOMMANDROBOT_
#define _GMCOMMANDROBOT_
#include "GameDefineBot.h"
#include "Bot.h"
#define GIFT_ID (971)
class GmCommandRobot:public BaseRobot
{
    // GM 指令
    /*
    1,	踢角色
    2,	禁言,解禁
    3,	发公告
    4,	在线更新过滤词库
    5,	移动角色坐标
    6,	查询角色是否在线,返回其所在地图和位置
    7,	查询角色信息（属性,金钱,金锭,金票,等级,装备,背包,技能,仓库,坐骑）[无论角色是否在线,如果不在线,返回数据库中的信息]
    8,	查询帮会信息
    9,	查询物品（输入物品id,返回物品属性等）
    10,	打开双倍经验
    11,	杀死怪物
    12,	召唤怪物
    13,	改变角色属性（等级,经验,技能）
    14,	生成道具给某角色
    */
    enum ERoleAttribute
    {
        ERA_LEVEL = 0,
        ERA_EXP,
        ERA_SKILL,
    };

public:

public:
    GmCommandRobot();
    ~GmCommandRobot();
    
    virtual void SendMsg(Msg* pMsg);
    virtual void PlayGame();
//    void SwitchMsg(MsgThirdParty* pMsg);
 //   virtual void ProcessMsgs();
    virtual void Update();
public:// proess Run
    void PushWork(OperationMsg* work);
    virtual void KickPlayer(const char* PlayerName);
    virtual void BanSpeak(const char* PlayerName,DWORD Time);
    virtual void Broadcast(std::string BullString);
    virtual void UpdateBanWoldLib();
    virtual void MovePlayer2Point(const char* PlayerName,int mapid,int x,int y);
    virtual void QueryCharacterOnlineInfo(const PlayerInfo* PlayerName);
    virtual void QueryCharacterInfo(const PlayerInfo* PlayerName);
    virtual void QueryTongInfo(const PlayerInfo* PlayerName);
    virtual void OpenDoubleExperience(bool IsOpen);
    virtual void KillMonster(int Target);
    virtual void CreateMonster(int nMonsterIndex,int nMonsterNumber);
    virtual void ChangeRoleAttribute(ERoleAttribute AttributeType,int nValue);
    virtual void CreateItem(int ItemId,int num);
    virtual void ReqGMCreateRole();
    virtual void ReqGMCreateRole(uint32 guid,uint8 sex,uint8 profession,
        const int8 *charName,uint16 level,uint8 country = 0,uint16  bagid = GIFT_ID);

    virtual void ReqPFAddPoints(const char* szPointSN );
    virtual void ReqPFAddPoints(const char *szPointSN ,uint32 addamount,uint16 discount,
        uint32 guid,uint32 gssid,uint8 typeId,uint32 points,uint32 netincome,
        uint32 paytime,uint8 channel,const int8 *remark,const int8 *signstr);

    virtual void ReqChangeCharacterName(const char* OriginalityName,const char* szNewName);
    virtual void ReqAddItem(const std::string &sn,uint16 itemid,uint16 itemCount,uint32 accId = 0,bool IsRandSn = true);
    virtual void ReqShutdownServers(uint32 time);
    virtual void ReqReloadTradeShop();
    // 改变地图经验
    virtual void ReqChangeMapEXPRate(uint32 MapId,float Rate);
public:// proess MsgThirdParty Message
    virtual void OnGMKickPlayer_ACK(Msg *pMsg);
    virtual void OnGMBanChat_ACK(Msg *pMsg);
    virtual void OnGMGetPlayerMapInfo_ACK(Msg *pMsg);
    virtual void OnGMGetOrganizeInfo_ACK(Msg *pMsg);
    virtual void OnGMGetItemInfo_ACK(Msg *pMsg);
    virtual void OnGMChangePlayerInfo_ACK(Msg *pMsg);
    virtual void OnGMCreateItemToPlayer_ACK(Msg *pMsg);
    virtual void OnGmGMMovePlayer_ACK(Msg *pMsg);
    virtual void OnMsgPFCreateCharAck(Msg *pMsg);
    virtual void OnMsgPFAddPointsAck(Msg *pMsg);
    virtual void OnMsgPFAddItemAck(Msg* pMsg);
    virtual void OnMsgPFChangeCharacterNameAck(Msg *pMsg);
protected:
private:
    DWORD _dwUpdateTime;
    int _HandleNum;

    std::list<OperationMsg> _workList;
};
#endif