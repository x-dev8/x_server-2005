#include "stdafx.h"
#include "DromeBot.h"

#define OPERATION_SPACE (60*1000)
#define MAX_DROMENUM 2
DromeBot::DromeBot():
OperationTime(HQ_TimeGetTime())
{
    m_BotType = Bot_Brome;
}

DromeBot::~DromeBot()
{

}

void DromeBot::GetDrome()
{
    if (SDromes.size() >= MAX_DROMENUM)
        return;

    MsgChat msg( MsgChat::CHAT_TYPE_NORMAL );

    char szMsg[dr_MaxChatString] = {0};

    //std::string command = ROBOT_REQUEST_COMMAND;
    int DromeId = rand()%58;
    DromeId += 700;
    _snprintf( szMsg, dr_MaxChatString - 1, "/AddMount %d",DromeId);

    msg.SetString(szMsg);
    SendMsg( &msg );
}

void DromeBot::RemoveDrome(int Drome)
{
    if (Drome < 0||Drome >= SDromes.size() || SDromes.empty())
    {
        return;
    }
    
    int Index = 0;

    for (ItrSDromeContainer itr = SDromes.begin();itr != SDromes.end();++itr)
    {
        if (Index == Drome)
        {
            SDromes.erase(itr);
            return;
        }
        Index++;
    }
}

SMountItem* DromeBot::FindMountByGuid(__int64 FindGuid)
{
    if (FindGuid <= 0)
    {
        return NULL;
    }
    for (ItrSDromeContainer itr = SDromes.begin();itr != SDromes.end();++itr)
    {
        if (itr->baseInfo.guid == FindGuid)
        {
            return &(*itr);
        }
    }

    return NULL;
}

SMountItem* DromeBot::FindMountByIndex(int Index)
{
    if (Index < 0 || Index >= SDromes.size())
    {
        return NULL;
    }

    int i = 0;
    for (ItrSDromeContainer itr = SDromes.begin();itr != SDromes.end();++itr,++i)
    {
        if (i == Index)
        {
            return &(*itr);
        }
    }

    return NULL;
}

void DromeBot::PlayGame()
{
    RandOperationDrome();
    CAttackBot::PlayGame();
}

void DromeBot::RandOperationDrome()
{
    if (HQ_TimeGetTime() - OperationTime < OPERATION_SPACE / 2)
    {
        return;
    }

    OperationTime = HQ_TimeGetTime();

    if (SDromes.empty())
    {
        GetDrome();
        return;
    }

    MsgChangeDrome changedrome;
    changedrome.header.stID = GetBotShortId();

    int operation = rand()%EDO_TotalOperation;
    switch(operation)
    {
    case EDO_Active:
        {
            changedrome.ucOpType = MsgChangeDrome::EOT_Active;
            changedrome.nIndex   = rand()%SDromes.size();
            SendMsg(&changedrome);
        }
        break;
    case EDO_Drop:
        {
            changedrome.ucOpType = MsgChangeDrome::EOT_Discard;
            changedrome.nIndex = rand()%SDromes.size();
            SendMsg(&changedrome);
        }
        break;
    case EDO_GetDrome:
        GetDrome();
        break;
    case EDO_UnActive:
        {
            changedrome.ucOpType = MsgChangeDrome::EOT_UnActive;
            changedrome.nIndex   = rand()%SDromes.size();
            SendMsg(&changedrome);
        }
        break;
    default:
        break;
    }
}

void DromeBot::OnMsgAckEnterWorld( Msg* pMsg )
{
    CAttackBot::OnMsgAckEnterWorld( pMsg );
    SDromes.clear();
    if (NULL != m_BromeItems)
    {
        for (int i= 0 ; i < ITEM_MOUNT_MAXCOUNT ; ++i)
        {
            if (m_BromeItems[i].baseInfo.id == 0)
            {
                break;
            }
            SMountItem* pSMountItem = FindMountByGuid(m_BromeItems[i].baseInfo.guid);
            if (NULL == pSMountItem)
                SDromes.push_back(m_BromeItems[i]);
            else
                *pSMountItem = m_BromeItems[i];
        }
    }
}


void DromeBot::InitPlayGame()
{
    BaseRobot::InitPlayGame();
}

void DromeBot::OnMsgGetMount(Msg* pMsg)
{
    MsgGetMount* pGetMsg = (MsgGetMount*) pMsg;
    if (pGetMsg->usResult == ER_Success)
    {
        for (int i= 0 ; i < ITEM_MOUNT_MAXCOUNT ; ++i)
        {
            if (pGetMsg->mount.baseInfo.id == 0)
            {
                break;
            }
            SMountItem* pSMountItem = FindMountByGuid(pGetMsg->mount.baseInfo.guid);
            if (pSMountItem == NULL)
                SDromes.push_back(pGetMsg->mount);
            else
                *pSMountItem = pGetMsg->mount;
        }
    }
}

void DromeBot::SwitchMsg(Msg* pMsg)
{
    if (NULL == pMsg)
        return;

    switch(pMsg->GetType())
    {
    case MSG_GETMOUNT:
        OnMsgGetMount(pMsg);
        break;
    case MSG_ACK_RESULT:
        OnMsgAckResult(pMsg);
        break;
    case MSG_CHANGEDROME:
        OnMsgChangeDrome(pMsg);
        break;
    case MSG_ACKENTERWORLD:
        OnMsgAckEnterWorld(pMsg);
        break;
    }
     BaseRobot::SwitchMsg(pMsg);
}

void DromeBot::OnMsgAckResult(Msg* pMsg)
{
    MsgAckResult* result = (MsgAckResult*)pMsg;
    switch(result->result)
    {
    case ER_InFightNotActiveMount:
    case ER_InDeadNotActiveMount:
    case ER_IndexOutOfRange:
    case ER_NullPointer:
    case ER_InMountConfigNotExist:
    case ER_Failed:
    case ER_MountTakeLevelNotEnough:
    case ER_NotEnoughEnjoyment:
        return;
    }

    BaseRobot::OnMsgAckResult(pMsg);
}

void DromeBot::OnMsgChangeDrome( Msg* Msg)
{
    MsgChangeDrome* pResult = (MsgChangeDrome*)Msg;
    switch(pResult->ucOpType)
    {
    case MsgChangeDrome::EOT_Discard:
        {
            RemoveDrome(pResult->nIndex);
        }
        break;

    default:
        break;
    }
}