#include "stdafx.h"
#include "WarBot.h"
#include "BotAppDataCenter.h"

CWarBot::CWarBot():_IsInWarField(false),
_PlayGameTime(0),
_ReqEnterBattleTime(0),
_ReqBattleFlagTime(0),
_NeedReqEnterBattle(true)
{
    SAreaInfo FlagPoint;
    FlagPoint.nMap = E_BattleMapID;
    FlagPoint.xPoint.x;
    FlagPoint.xPoint.y;
    _FlagPoints.push_back(FlagPoint);
    FlagPoint.xPoint.x;
    FlagPoint.xPoint.y;
    _FlagPoints.push_back(FlagPoint);
    FlagPoint.xPoint.x;
    FlagPoint.xPoint.y;
    _FlagPoints.push_back(FlagPoint);
    FlagPoint.xPoint.x;
    FlagPoint.xPoint.y;
    _FlagPoints.push_back(FlagPoint);
    m_BotType = Bot_WarBot;
}

CWarBot::~CWarBot()
{

}

void CWarBot::PlayGame()
{
    if (HQ_TimeGetTime() - _PlayGameTime < E_PlayGameSpaceTime)
        return;
    
    _PlayGameTime = HQ_TimeGetTime();

    //如果不在战场且去需要请求战场排队
    if (!_IsInWarField && _NeedReqEnterBattle)
    {
        if (HQ_TimeGetTime() - _ReqEnterBattleTime < E_ReqWarFieldQueueSpaceTime)
        {
            return;
        }

        _ReqEnterBattleTime = HQ_TimeGetTime();
        ReqWarFieldQueue();
        return;
    }

//     if (m_xAreaInfo.nMap == E_ErrorID)
//     {
//         AreaInfo* pAreaInfo = GetTargetArea();
//         if (NULL != pAreaInfo)
//         {
//             m_xAreaInfo.nMap = pAreaInfo->nMap;
//             m_xAreaInfo.xPoint.x = pAreaInfo->xPoint.x;
//             m_xAreaInfo.xPoint.y = pAreaInfo->xPoint.y;
//         }
//     }

    if (GetMapID() != E_BattleMapID)
    {
        Move();
        return;
    }

    if (HQ_TimeGetTime() - _ReqBattleFlagTime < E_ReqWarFlagSpaceTime)
    {
        ReqBattleOccupy();
        _ReqBattleFlagTime = HQ_TimeGetTime();
    }
    PlayAttack();
//     if( MoveToArea() )
//     {
//         m_xAreaInfo.nMap = -1;
//         m_xAreaInfo.xPoint.x = 0.0;
//         m_xAreaInfo.xPoint.y = 0.0;
//     }

    //
}

void CWarBot::PlayAttack()
{
    if (GetBotHP() <= 0)
    {
        return;
    }

    // 寻人
    if (m_shTargetID == EATI_InitAttackTargetId)
    {
        m_shTargetID = LockTarget();
        if (m_shTargetID != EATI_InitAttackTargetId)
        {
            //锁定怪物
            MsgLockTarget msg;
            msg.stWho = m_shTargetID;
            SendMsg(&msg);

            //清除随即要移动去的目标
            ClearMovePos();

            SetTipsInfo("锁定目标");
        }
    }

    // 开始攻击
    if (m_shTargetID != EATI_InitAttackTargetId)
    {
        PlayerInfo* pInfo = GetPlayer(m_shTargetID);
        if (NULL != pInfo)
        {
            if (!MoveToPoint(pInfo->m_vPos))
            {
                return;
            }
            AttackEnemy();
        }
    }
    Move();
}

void CWarBot::OnMsg_ExitSight( Msg* pMsg )
{
    MsgExitMySight* pExit = (MsgExitMySight*)pMsg;
    if (!_EnmityPlayerList.empty())
    {
        for (EnmityPlayerType::iterator itr = _EnmityPlayerList.begin();itr != _EnmityPlayerList.end();)
        {
            if (pExit->header.stID == itr->shPlayerID)
            {
                itr = _EnmityPlayerList.erase(itr);
                continue;
            }
            ++itr;
        }
    }

    BaseRobot::OnMsg_ExitSight(pMsg);
}

void CWarBot::OnMsg_PlayerMovingPos(Msg* pMsg)
{
    MsgPlayerMovingPos* pMove = (MsgPlayerMovingPos*)pMsg;

    if (!_EnmityPlayerList.empty())
    {
        for (EnmityPlayerType::iterator itr = _EnmityPlayerList.begin();itr != _EnmityPlayerList.end();)
        {
            if (pMove->header.stID == itr->shPlayerID)
            {
                itr = _EnmityPlayerList.erase(itr);
                continue;
            }
            ++itr;
        }
    }
    BaseRobot::OnMsg_PlayerMovingPos(pMsg);
}

PlayerInfo* CWarBot::GetPlayer(short shID)
{
    if (_EnmityPlayerList.empty() || shID < 0)
    {
        return NULL;
    }
    EnmityPlayerType::iterator iter = find(_EnmityPlayerList.begin(), _EnmityPlayerList.end(), shID);
    if (iter != _EnmityPlayerList.end())
    {
        return &(*iter);
    }
    return NULL;
}

void CWarBot::OnMsg_PlayerMovingPosAndDir(Msg* pMsg)
{
    MsgPlayerMovingPosAndDir* pMove = (MsgPlayerMovingPosAndDir*)pMsg;

    if(pMove->header.stID != m_shPlayerId)
    {
        PlayerInfo* pInfo = GetPlayer(pMove->header.stID);
        if(pInfo != NULL)
        {
            pInfo->m_vPos.x = pMove->vPos.x;
            pInfo->m_vPos.y = pMove->vPos.y;
        }
    }

    BaseRobot::OnMsg_PlayerMovingPosAndDir(pMsg);
}

short CWarBot::LockTarget()
{
    short target = -1;
    if (_EnmityPlayerList.empty())
    {
        return target;
    }
    int Index = rand()%_EnmityPlayerList.size();
    return _EnmityPlayerList[Index].shPlayerID;
}

void CWarBot::OnMsg_PlayerEnterSight( Msg* pMsg )
{
    if (GetMapID() == E_BattleMapID)
    {
        MsgPlayerEnterMySight* pEnter = (MsgPlayerEnterMySight*)pMsg;
        if( pEnter != NULL && pEnter->stCharType == Object_Player
            && pEnter->influence != influence)
        {
            EnmityPlayerType::iterator itr = find (_EnmityPlayerList.begin(),
                _EnmityPlayerList.end(),pEnter->header.stID);
            if (itr == _EnmityPlayerList.end())
            {
                PlayerInfo info;
                info.dwCharacterID = pEnter->dwPlayerCharacterID;
                info.shPlayerID = pEnter->header.stID;
                info.shCharType = pEnter->stCharType;
                info.nHP = pEnter->nHp;
                info.m_vPos.x = pEnter->fX;
                info.m_vPos.y = pEnter->fY;
                info.influence = pEnter->influence;
                _EnmityPlayerList.push_back(info);

                ReqCharInfo(pEnter->header.stID);
            }
        }
    }
    
    BaseRobot::OnMsg_PlayerEnterSight(pMsg);
}

SAreaInfo* CWarBot::GetTargetArea()
{
    if(m_xAreaInfo.nMap == E_ErrorID)
    {
        int index = rand()%_FlagPoints.size();
        return &_FlagPoints[index];
    }
    return NULL;
}

void CWarBot::ReqWarFieldQueue()
{
    //MsgRequestEnterBattleQueue RegMsg;
    //RegMsg.which = rand()%2;
    //RegMsg.doorNum = rand()%12;
    //SendMsg(&RegMsg);
//     //BotReq BattleWait 0或者1(阵营),  0-11(排队房间）
//     std::string ReqMsg = ROBOT_REQUEST_COMMAND;
//     ReqMsg += "BattleWait ";
//     char buf[20] = {0};
//     itoa(rand()%2,buf,10);
//     ReqMsg += buf;
//     ReqMsg += " ";
//     memset(buf,0,sizeof(buf));
//     itoa(rand()%12,buf,10);
//     ReqMsg += buf;
// 
//     MsgChat BotMsg;
//     BotMsg.SetString(ReqMsg.c_str());
//     SendMsg(&BotMsg);    
}

// OnMsg
void CWarBot::SwitchMsg(Msg* pMsg)
{
    if (NULL == pMsg)
        return;

    switch (pMsg->GetType())
    {
    case MSG_ACK_BATTLE_QUEUENUM:
        OnMsgAckBattleQueueNum(pMsg);
    	break;
    case MSG_ACK_ENTER_BATTLEQUEUE:
        OnMsgAckEnterBattleQueue(pMsg);
        break;
    case MSG_NOTIFY_USER_ENTERBATTLE:
        OnMsgNotifyUserEnterBattle(pMsg);
        break;
    case MSG_INIT_USERBATTLE_DATA:
        OnMsgInitUserBattleData(pMsg);
        break;
    case MSG_NOTIFY_BATTLE_END:
        OnMsgNotifyBattleEnd(pMsg);
        break;
    case MSG_FRESH_RESOURCE_OCCUPTOWNER:
        OnMsgFreshBattleResourceOccuptOwnerChange(pMsg);
        break;
    default:
        break;
    }
    CFightBot::SwitchMsg(pMsg);
}

void CWarBot::OnMsgAckBattleQueueNum(Msg* pMsg)
{
    MsgAckBattleQueueNum* pMsgAckBattleQueueNum = (MsgAckBattleQueueNum*)pMsg;
    
}

void CWarBot::OnMsgAckEnterBattleQueue(Msg* pMsg)
{
    MsgAckEnterBattleQueue* pMsgAckEnterBattleQueue = (MsgAckEnterBattleQueue*)pMsg;
    switch(pMsgAckEnterBattleQueue->result)
    {
    case MsgAckEnterBattleQueue::enumEnterBattle_NotStart:
        ReqBattleBegin();
        break;
    case MsgAckEnterBattleQueue::enumEnterBattle_Success:
        _NeedReqEnterBattle = false;
        break;
    default:
        {
            LOG_MESSAGE(LogObject,LOG_PRIORITY_DEBUG,"请求进入 %d 阵营 %d 营失败",
                pMsgAckEnterBattleQueue->which , pMsgAckEnterBattleQueue->doorNum);
        }
        break;
    }
}

void CWarBot::ReqBattleBegin()
{
    //    BotReq BattleSign  5(轮数）, 5(单位时间增加分数），3000(最大分数), 30(副本时间，分钟)
    char buf[BotAppDataCenter::BuffSize];
    sprintf_s(buf,BotAppDataCenter::BuffSize,"%sBattleSign %d %d %d,%d",ROBOT_REQUEST_COMMAND,5,5,3000,30);
    
    MsgChat ReqStr;
    ReqStr.SetString(buf);
    SendMsg(&ReqStr);
}

void CWarBot::OnMsgNotifyUserEnterBattle(Msg* pMsg)
{
    MsgNotifyUserEnterBattle* pMsgNotifyUserEnterBattle = (MsgNotifyUserEnterBattle*)pMsg;
    pMsgNotifyUserEnterBattle->isEnter = 1;
    SendMsg(pMsgNotifyUserEnterBattle);

//     std::string Reqstring;
//     Reqstring += ROBOT_REQUEST_COMMAND;
//     Reqstring += "BattleEnter";
//     MsgChat ReqMsg;
//     ReqMsg.SetString(Reqstring.c_str());
//     SendMsg(&ReqMsg);
}

void CWarBot::OnMsgInitUserBattleData(Msg* pMsg)
{
    MsgInitUserBattleData* pMsgInitUserBattleData = (MsgInitUserBattleData*)pMsg;
    influence = pMsgInitUserBattleData->influence;
}

void CWarBot::OnMsgNotifyBattleEnd(Msg* pMsg)
{
    MsgNotifyBattleEnd* pMsgNotifyBattleEnd = (MsgNotifyBattleEnd*)pMsg;

}

void CWarBot::OnMsgFreshBattleResourceOccuptOwnerChange(Msg* pMsg)
{
    MsgFreshBattleResourceOccuptOwnerChange* pFBROOCMsg = (MsgFreshBattleResourceOccuptOwnerChange*)pMsg;

}

void CWarBot::OnMsgChangeMap( Msg* pMessage )
{
    MsgChangeMap *pMsgChangeMap = (MsgChangeMap*)pMessage;
    //如果是从战场出来,需要重新请求
    if (GetMapID() == E_BattleMapID && pMsgChangeMap->dwMapId != E_BattleMapID)
    {
        _NeedReqEnterBattle = true;
    }
    if (pMsgChangeMap->dwMapId == E_BattleMapID && !_IsInWarField)
        _IsInWarField = true;
    else
        _IsInWarField = false;

    CAttackBot::OnMsgChangeMap(pMessage);
}

void CWarBot::OnMsg_AckCharInfo( Msg* pMsg )
{
    MsgAckCharInfo* pMsgAckCharInfo = (MsgAckCharInfo*)pMsg;
    EnmityPlayerType::iterator itr = find(_EnmityPlayerList.begin(),_EnmityPlayerList.end()
        ,pMsgAckCharInfo->header.stID);
    if (itr != _EnmityPlayerList.end())
    {
        strncpy_s(itr->szName,dr_MaxPlayerName,pMsgAckCharInfo->szDisplayName,dr_MaxPlayerName);
        //itr->nHP = pMsgAckCharInfo->nHp;
    }
    CAttackBot::OnMsg_AckCharInfo(pMsg);
}

void CWarBot::ReqBattleOccupy()
{
    //占领旗子
    //BotReq BattleOccupy 0-4 (旗子索引)
    std::string Reqstring = ROBOT_REQUEST_COMMAND;
    Reqstring += "BattleOccupy ";
    char buf[20] = {0};
    itoa(rand()%5,buf,10);
    Reqstring += buf;
    MsgChat ReqMsg;
    ReqMsg.SetString(Reqstring.c_str());
    SendMsg(&ReqMsg);
}