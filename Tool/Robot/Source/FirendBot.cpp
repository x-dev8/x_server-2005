#include "FirendBot.h"

#define SAMESTRING (0)

FirendBot::FirendBot():RunTime(HQ_TimeGetTime())
{
    //InitRelation = 0,         // 无效值
    //    TempFriend = 0x1,       // 临时好友
    //    Friend     = 0x2,       // 好友
    //    Vendetta   = 0x4,       // 仇人
    //    BlackList  = 0x8,       // 黑名单( 黑名单可以和仇人并存 )


    //    // 2级关系( 只能在好友的基础上建立, 删除2级关系,好友关系仍然存在的 )
    //    Marriage   = 0x100,     // 夫妻
    //    Teacher    = 0x200,     // 师傅( 出师前 )
    //    Student    = 0x400,     // 徒弟( 出师前 )
    //    Brother    = 0x800,     // 结拜

    //    // 出师以后, 这些是永久的关系
    //    Master     = 0x1000,    // 徒弟出师以后 师傅的关系
    //    Prentice   = 0x2000,    // 徒弟出师以后 徒弟的关系

    //Relation[0] = Relation_TempFriend;
    //Relation[1] = Relation_Friend;
    //Relation[2] = Relation_BlackList;
    //Relation[3] = Relation_Vendetta;
    //Relation[4] = Relation_Marriage;
    //Relation[5] = Relation_Teacher;
    //Relation[6] = Relation_Student;
    //Relation[7] = Relation_Brother;

}

FirendBot::~FirendBot()
{

}

void FirendBot::RandReqFirend()
{
    PlayerInfo* pPlayerInfo = RandPlayer();
    if (NULL == pPlayerInfo)
    {
        Move();
        return;
    }
    if (stricmp(pPlayerInfo->szName,"") == SAMESTRING)
    {
        MsgQueryCharInfo query;
        query.stChar = pPlayerInfo->shPlayerID;
        SendMsg(&query);
        SetSleep(2000);
        return;
    }
    ReqAddFirend(pPlayerInfo->szName);
    SetSleep(2000);
}

void FirendBot::PlayGame()
{
    if (HQ_TimeGetTime() - RunTime <= 1000 * 10)
    {
        Move();
        return;
    }
    RunTime = HQ_TimeGetTime();
    //MsgReqAddFriend
    //MsgReqDelFriend
    int operation = rand()%2;
    if (operation)
    {
        RandReqFirend();
    }
    else
    {
        if (Relations.empty())
        {
            RandReqFirend();
            return;
        }

        RelationDataToClient* pRelationDataToClient = RandFirend();
        if (NULL == pRelationDataToClient)
        {
            Move();
            return;
        }
        ReqDelFirend(pRelationDataToClient);
        SetSleep(2000);
    }
    Move();
}

void FirendBot::ReqAddFirend(const char* playerName)
{
    if (NULL == playerName)
    {
        return;
    }
    
    for (ItrRelation itr = Relations.begin();itr != Relations.end();++itr)
    {
        //if (stricmp(itr->second.GetPlayerName(),playerName) == SAMESTRING)
        //{
        //    return;
        //}
    }
//MsgReqAddFriend ReqMsg;
//int num = rand()%RELATION_NUM;
//ReqMsg.stRelation = Relation[num];
//strncpy_s(ReqMsg.szName,sizeof(ReqMsg.szName),playerName,sizeof(ReqMsg.szName)-1);
//SendMsg(&ReqMsg);
}

void FirendBot::ReqDelFirend(const RelationDataToClient * pPlayerInfo)
{
// if (NULL == pPlayerInfo)
// {
//    return;
// }
// 
// ItrRelation itr = Relations.find(pPlayerInfo->GetPlayerID());
// if (itr == Relations.end())
// {
//    return;
// }
// 
// MsgReqDelFriend DelMsg;
// DelMsg.nFriendID = pPlayerInfo->GetPlayerID();
// DelMsg.stRelation = pPlayerInfo->GetRelation();
// SendMsg(&DelMsg);
}

RelationDataToClient* FirendBot::RandFirend()
{
    if (Relations.empty())
    {
        return NULL;
    }
    int Num = rand()%Relations.size();
    ItrRelation itr = Relations.begin();
    for (int i = 0;i < Num;++i)
    {
        ++itr;
        if (itr == Relations.end())
        {
            return NULL;
        }
    }
    if (itr != Relations.end())
    {
        return &(itr->second);
    }
    return NULL;
}

void FirendBot::SwitchMsg(Msg* pMsg)
{
// 	switch (pMsg->GetType())
// 	{
// 	case MSG_FRIEND_ONLINE:
// 	   OnMsgFriendOnline(pMsg);
// 		break;
// 	case MSG_FRIEND_OUTLINE:
// 	   OnMsgFriendOutLine(pMsg);
// 	   break;
// 	case MSG_ACK_UPDATE_FRIENDINFO:
// 	   OnMsgAckUpdateFriendInfo(pMsg);
// 	   break;
// 	}
    BaseRobot::SwitchMsg(pMsg);
}

void FirendBot::OnMsgFriendOnline(Msg* pMsg)
{
    //MsgFriendOnline* pMsgFriendOnline = (MsgFriendOnline*)pMsg;
    //ItrRelation itr = Relations.find(pMsgFriendOnline->nFriendID);
    //if (itr != Relations.end())
    //{
    //    itr->second.SetFloatX(pMsgFriendOnline->xOnLine.GetFloatX());
    //    itr->second.SetFloatY(pMsgFriendOnline->xOnLine.GetFloatY());
    //    itr->second.SetMapID(pMsgFriendOnline->xOnLine.GetMapID());
    //    itr->second.SetOnline(true);
    //    itr->second.SetPKValue(pMsgFriendOnline->xOnLine.GetPKValue());
    //    itr->second.SetLevel(pMsgFriendOnline->xOnLine.GetLevel());
    //}
}

void FirendBot::OnMsgFriendOutLine(Msg* pMsg)
{
    //MsgFriendOutLine* pMsgFriendOutline = (MsgFriendOutLine*)pMsg;
    //ItrRelation itr = Relations.find(pMsgFriendOutline->nFriendID);
    //if (itr != Relations.end())
    //{
    //    itr->second.SetOnline(false);
    //}
}

void FirendBot::OnMsgAckUpdateFriendInfo(Msg* pMsg)
{
    //MsgAckUpdateFriendInfo* pMsgAckUpdateFriendInfo = (MsgAckUpdateFriendInfo*)pMsg;
    //for (int i = 0;i < pMsgAckUpdateFriendInfo->ustCount;++i)
    //{
    //    ItrRelation itr = Relations.find(pMsgAckUpdateFriendInfo->xFriendInfo[i].nFriendID);
    //    if (itr != Relations.end())
    //    {
    //        itr->second.SetFloatX(pMsgAckUpdateFriendInfo->xFriendInfo[i].xOnLine.GetFloatX());
    //        itr->second.SetFloatY(pMsgAckUpdateFriendInfo->xFriendInfo[i].xOnLine.GetFloatY());
    //        itr->second.SetMapID(pMsgAckUpdateFriendInfo->xFriendInfo[i].xOnLine.GetMapID());
    //        itr->second.SetOnline(true);
    //        itr->second.SetPKValue(pMsgAckUpdateFriendInfo->xFriendInfo[i].xOnLine.GetPKValue());
    //        itr->second.SetLevel(pMsgAckUpdateFriendInfo->xFriendInfo[i].xOnLine.GetLevel());
    //    }
    //}
}