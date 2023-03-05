#include "stdafx.h"
#include "AttackBot.h"

#define RELATION_NUM (8)
class FirendBot:public CAttackBot
{
public:
    FirendBot();
    ~FirendBot();


    virtual void PlayGame();

    virtual void SwitchMsg(Msg* pMsg);

    RelationDataToClient* RandFirend();
    void ReqAddFirend(const char* playerName);
    void ReqDelFirend(const RelationDataToClient * pPlayerInfo);
    void RandReqFirend();
public: // ProessFirend
    virtual void OnMsgFriendOnline(Msg* pMsg);

    virtual void OnMsgFriendOutLine(Msg* pMsg);
    
    virtual void OnMsgAckUpdateFriendInfo(Msg* pMsg);
protected:
private:
    int Relation[RELATION_NUM];
    DWORD RunTime;
};
