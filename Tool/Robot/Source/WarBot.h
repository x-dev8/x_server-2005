#pragma once

#ifndef __WARBOTDEFINE__
#define __WARBOTDEFINE__
#include "FightBot.h"

class CWarBot:public CFightBot
{
public:
     
    enum WarBotConstValue
    {
        E_ErrorID = -1,
        E_BattleMapID = 102,
        E_SecondTime = 1000,
        E_PlayGameSpaceTime = E_SecondTime,
        E_ReqWarFieldQueueSpaceTime = 5*E_SecondTime,
        E_ReqWarFlagSpaceTime = 10*E_SecondTime,//ReqBattleFlagTime
    };

public:
    
    CWarBot();
    ~CWarBot();

    virtual void PlayGame();

    void ReqWarFieldQueue();

    SAreaInfo* GetTargetArea();

    void PlayAttack();
    //
    void ReqBattleOccupy();
    void ReqBattleWait();

    PlayerInfo* GetPlayer(short shID);
    short LockTarget();
    void ReqBattleBegin();
    // OnMsg
    virtual void SwitchMsg(Msg* pMsg);

    void OnMsgAckBattleQueueNum(Msg* pMsg);
    void OnMsgAckEnterBattleQueue(Msg* pMsg);
    void OnMsgNotifyUserEnterBattle(Msg* pMsg);
    void OnMsgInitUserBattleData(Msg* pMsg);
    void OnMsgNotifyBattleEnd(Msg* pMsg);
    void OnMsgFreshBattleResourceOccuptOwnerChange(Msg* pMsg);

    void OnMsgChangeMap( Msg* pMessage );
    void OnMsg_AckCharInfo( Msg* pMsg );
    void OnMsg_PlayerEnterSight( Msg* pMsg );
    void OnMsg_PlayerMovingPos(Msg* pMsg);
    void OnMsg_PlayerMovingPosAndDir(Msg* pMsg);
    void OnMsg_ExitSight( Msg* pMsg );
protected:
private:
    bool _NeedReqEnterBattle;
    bool _IsInWarField;
    uint32 _PlayGameTime;
    uint32 _ReqEnterBattleTime;
    uint32 _ReqBattleFlagTime;
    // m_xAreaInfo curpoint
    typedef std::vector<PlayerInfo> EnmityPlayerType;
    EnmityPlayerType        _EnmityPlayerList;
    std::vector<SAreaInfo>   _FlagPoints;
};

#endif