#include "FirendBot.h"

#define SAMESTRING (0)

FirendBot::FirendBot():RunTime(HQ_TimeGetTime())
{
    //InitRelation = 0,         // ��Чֵ
    //    TempFriend = 0x1,       // ��ʱ����
    //    Friend     = 0x2,       // ����
    //    Vendetta   = 0x4,       // ����
    //    BlackList  = 0x8,       // ������( ���������Ժͳ��˲��� )


    //    // 2����ϵ( ֻ���ں��ѵĻ����Ͻ���, ɾ��2����ϵ,���ѹ�ϵ��Ȼ���ڵ� )
    //    Marriage   = 0x100,     // ����
    //    Teacher    = 0x200,     // ʦ��( ��ʦǰ )
    //    Student    = 0x400,     // ͽ��( ��ʦǰ )
    //    Brother    = 0x800,     // ���

    //    // ��ʦ�Ժ�, ��Щ�����õĹ�ϵ
    //    Master     = 0x1000,    // ͽ�ܳ�ʦ�Ժ� ʦ���Ĺ�ϵ
    //    Prentice   = 0x2000,    // ͽ�ܳ�ʦ�Ժ� ͽ�ܵĹ�ϵ

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