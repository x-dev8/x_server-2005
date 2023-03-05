#include "stdafx.h"
#include "GmCommandRobot.h"
#include "PlatformMessageDefine.h"
#include "GameDefineBot.h"
#include "GameBot.h"
#include "ItemDetail.h"
#include "ScriptManager.h"
#include "Mutex.h"
//#include "LogFileObjectName.h"
#define SUCCESSED (0)

GmCommandRobot::GmCommandRobot():_dwUpdateTime(HQ_TimeGetTime())
{
    m_BotType = Bot_PlatformTest;
	//SetAccount("robot00001");
	//SetPassword("12345");
}

GmCommandRobot::~GmCommandRobot()
{

}

void GmCommandRobot::PlayGame()
{
    if (HQ_TimeGetTime() - _dwUpdateTime <= 1000)
    {
        return;
    }
    _dwUpdateTime = HQ_TimeGetTime();

     if (_workList.empty())
     {
         return;
     }

     OperationMsg work;
     {
         // 拷贝数据
         CSemiAutoIntLock  _lock;
         CSALocker lock(_lock);
         work = _workList.front();
         _workList.pop_front();
     }
     
//static short once = 0;
//    if (once != 0)
//    {
//        return;
//    }
//    once++;


    if (_HandleNum == OperationMsg::EPO_TOTALHANDLE)
    {
        return;
    }

    std::string FullPath = theBotDataCenter.ScriptFilePath;
    FullPath += theBotDataCenter.ScriptFileName;
    uint32 result = theScriptManager.LoadScript(FullPath.c_str());

    // for test
    //_HandleNum = theScriptManager.ScriptFunction<int>("GetPlatformOperation");//EPO_ADDITEM;//EPO_REQADDPOINT;
    //HandleNum = EPO_SHUTDOWNSERVERS;
    switch (work.TestOperation)
    {
    case OperationMsg::EPO_KICKPLAYER:
        {
            KickPlayer(work.szParm);
        }
    	break;
    case OperationMsg::EPO_BANPLAYERSPEAK:
        break;
    case OperationMsg::EPO_BROADCAST:
        {
            Broadcast(work.szParm);
            /*char szPubBuff[512] = {0};
            sprintf_s(szPubBuff,sizeof(szPubBuff),theBotDataCenter.GmCommondStr,GetAccount());
            Broadcast(szPubBuff);*/
        }
        break;
    case OperationMsg::EPO_UPDATEBANWOLDLIB:
        break;
    case OperationMsg::EPO_MOVEPLAYER2POINT:
        break;
    case OperationMsg::EPO_QUERYCHARACTER_ONLINE:
        break;
    case OperationMsg::EPO_QUERYCHARACTER:
        break;
    case OperationMsg::EPO_QUERTONG:
        break;
    case OperationMsg::EPO_OPENDOUBLE:
        break;
    case OperationMsg::EPO_KILLMONSTER:
        break;
    case OperationMsg::EPO_CREATEMONSTER:
        break;
    case OperationMsg::EPO_CHANGEROLEATT:
        break;
    case OperationMsg::EPO_CREATEITEM:
        break;
    case OperationMsg::EPO_CREATECHARACTER:
        ReqGMCreateRole();
        break;
    case OperationMsg::EPO_REQADDPOINT:
        {
            static int n = 10;
            char szCharBuf[10];
            ZeroMemory(szCharBuf,sizeof(szCharBuf));
            itoa(n++,szCharBuf,10);
            ReqPFAddPoints(szCharBuf);
            //SetSleep(1000);
        }
        break;
    case OperationMsg::EPO_CHANGECHARACTERNAME:
            ReqChangeCharacterName("Hero021","Hero5995");
        break;
    case OperationMsg::EPO_ADDITEM:
        {
            if (ER_Success == result)
            {
                theScriptManager.ScriptFunctionVoid("PlatformAddItem",this);
            }
            /*
            for (int n = 0;n<10;++n)
            {
                char buf[32];
                sprintf_s(buf,sizeof(buf),"%d",n+1); 
//                 GetConnector()->TryRecvThirdParty();
                ReqAddItem(buf,4000+n,1);
                SetSleep(2000);
            }
            */
        }
        break;
    case OperationMsg::EPO_RELOADTRADESHOP:
        ReqReloadTradeShop();
        break;
    case OperationMsg::EPO_SHUTDOWNSERVERS:
        {
            ReqShutdownServers(work.nParm[0]);
            /*if (ER_Success == result)
            {
                int rest = theScriptManager.ScriptFunction<int>("GetReqShutdownServerTime");
                ReqShutdownServers(rest);
            }*/
        }
        break;
    case OperationMsg::EPO_CHANGEMAPEXPRATE:
        ReqChangeMapEXPRate(work.nParm[0],work.fParm);
        break;
    default:
        break;
    }
}

void GmCommandRobot::ReqChangeMapEXPRate(uint32 MapId,float Rate)
{
    MsgPFGMChangeMapExpRateReq Msg;
    Msg.mapConfigId = MapId;
    Msg.fExpRate = Rate;
    SendMsg(&Msg);
    //GetConnector()->TrySendThirdParty();
}

void GmCommandRobot::ReqShutdownServers(uint32 time)
{
    MsgPFGMShutdownServersReq ReqMsg;
    ReqMsg.delayTime = time;
    SendMsg(&ReqMsg);
   // GetConnector()->TrySendThirdParty();
}

void GmCommandRobot::ReqReloadTradeShop()
{
    MsgPFGMReloadTradeShop ReqMsg;
    SendMsg(&ReqMsg);
   // GetConnector()->TrySendThirdParty();
}

void GmCommandRobot::ReqAddItem(const std::string &sn,uint16 itemid,uint16 itemCount,uint32 accId,bool IsRandSn)
{
    if (sn.empty())
    {
        return;
    }
    MsgPFAddItemReq ReqMsg;
    uint32 accountId = 0;
    if (accId == 0)
    {
        char* account = GetAccount();
        if (NULL != account)
        {
            accountId = atoi(account);
        }
        if ( accountId == 0 )
        {
            return ;
        }
    }
    else
    {
        accountId = accId;
    }
    
    ReqMsg.accountId = accountId;
    ReqMsg.item.itemType = 0;
    ReqMsg.item.itemId = itemid;
    if (IsRandSn)
    {
        int tempsn = atoi(sn.c_str());
        tempsn += rand()%60000;
        if (tempsn < 1)
        {
            tempsn = rand()%60000;
        }
        sprintf_s(ReqMsg.item.sn,sizeof(ReqMsg.item.sn),"%d",tempsn);
    }
    else
    {
        strncpy_s(ReqMsg.item.sn,sizeof(ReqMsg.item.sn),sn.c_str(),sizeof(ReqMsg.item.sn)-1);
    }
    
    for (int n = 0;n < 10;++n)
    {
        ReqMsg.item.value[n] = 0;//n+1;
    }
    CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID(itemid);
    if (NULL != pItem)
    {
        /* 如果道具是技能,状态,动作,超链接,任务类型则不发送 */
        if (pItem->ucItemType == CItemDetail::ITEMTYPE_SKILL||
            pItem->ucItemType == CItemDetail::ITEMTYPE_STATUS||
            pItem->ucItemType == CItemDetail::ITEMTYPE_ACTION||
            pItem->ucItemType == CItemDetail::ITEMTYPE_TASK)
        {
            return;
        }
        ReqMsg.item.itemType = pItem->ucItemType;
        if (pItem->IsExclusive())
        {
            for (int n = 1;n <= itemCount;++n)
            {
                int tempsn = n;//atoi(sn.c_str());
                tempsn += rand()%60000;
                if (tempsn < 1)
                {
                    tempsn = rand()%60000;
                }
                sprintf_s(ReqMsg.item.sn,sizeof(ReqMsg.item.sn),"%d",tempsn);
                ReqMsg.item.itemCount = 1;
                SendMsg(&ReqMsg);
                //GetConnector()->TrySendThirdParty();
            }
        }
        else
        {
            ReqMsg.item.itemCount = itemCount;
            SendMsg(&ReqMsg);
            //GetConnector()->TrySendThirdParty();
        }
    }
    else
    {
        LOG_MESSAGE(LogObject,LOG_PRIORITY_DEBUG,"GmCommandRobot::ReqAddItem Function No Find Item %d",itemid);
    }
}

void GmCommandRobot::ReqChangeCharacterName(const char* OriginalityName,const char* szNewName)
{
    
}

void GmCommandRobot::OnMsgPFChangeCharacterNameAck(Msg *pMsg)
{

}

void GmCommandRobot::ReqPFAddPoints(const char* szPointSN )
{
    if (NULL == szPointSN)
    {
        return;
    }

    /*MsgPFAddPoints ReqMsg;
    ReqMsg.info.addamount = 100;
    ReqMsg.info.discount = 10;
    ReqMsg.info.guid = 5656;
    ReqMsg.info.gssid = 1;
    ReqMsg.info.typeId = 1;
    ReqMsg.info.points = 56;
    ReqMsg.info.netincome = 20;
    ReqMsg.info.paytime = 6000;
    ReqMsg.info.channel = 2;
    strncpy_s (ReqMsg.info.remark ,sizeof(ReqMsg.info.remark),"TestMark",sizeof(ReqMsg.info.remark)-1);
    strncpy_s (ReqMsg.info.gateway,sizeof(ReqMsg.info.gateway),"53002",sizeof(ReqMsg.info.gateway)-1);
    strncpy_s (ReqMsg.info.userip,sizeof(ReqMsg.info.userip),"172.20.25.3",sizeof(ReqMsg.info.userip)-1);
    strncpy_s(ReqMsg.info.typesn,sizeof(ReqMsg.info.typesn),szPointSN,sizeof(ReqMsg.info.typesn)-1);
    strncpy_s(ReqMsg.info.signstr,sizeof(ReqMsg.info.signstr),"for test", sizeof(ReqMsg.info.signstr)-1);
    SendMsg(&ReqMsg);*/
    //GetConnector()->TrySendThirdParty();
}

void GmCommandRobot::ReqPFAddPoints(const char *szPointSN ,uint32 addamount,uint16 discount,
                                    uint32 guid,uint32 gssid,uint8 typeId ,uint32 points,uint32 netincome,
                                    uint32 paytime,uint8 channel,const int8 *remark,const int8 *signstr)
{
    if (NULL == szPointSN)
    {
        return;
    }

   // MsgPFAddPoints ReqMsg;
   // ReqMsg.info.addamount = addamount;
   // ReqMsg.info.discount = discount;
   // ReqMsg.info.guid = guid;
   // ReqMsg.info.gssid = gssid;
   // ReqMsg.info.typeId = typeId;
   // ReqMsg.info.points = points;
   // ReqMsg.info.netincome = netincome;
   // ReqMsg.info.paytime = paytime;
   // ReqMsg.info.channel = channel;

   // if (remark != NULL)
   // {
   //     strncpy_s (ReqMsg.info.remark ,sizeof(ReqMsg.info.remark),remark,sizeof(ReqMsg.info.remark)-1);
   // }

   // struct hostent *phost = ::gethostbyname("");
   // if (NULL != phost)
   // {
   //     char * paddr = inet_ntoa(*((struct in_addr*)*phost->h_addr_list) );
   //     OutputDebugStringA( paddr );
   // }
   // uint16 localport = 0;
   // sockaddr_in localaddr;
   // memset(&localaddr,0,sizeof(sockaddr_in));
   // int iSize;
   // iSize = sizeof( localaddr );
   // // getpeername 是远端 socket 没有连接获取会失败
   ///* if(SUCCESSED == getsockname( GetConnector()->GetSocket()->GetSockfd(),(sockaddr*)&localaddr,&iSize ) )
   // {
   //     localport = ntohs(localaddr.sin_port);
   //     sprintf_s (ReqMsg.info.gateway,sizeof(ReqMsg.info.gateway),"%d",localport,sizeof(ReqMsg.info.gateway)-1);
   //     strncpy_s (ReqMsg.info.userip,sizeof(ReqMsg.info.userip),inet_ntoa(localaddr.sin_addr),sizeof(ReqMsg.info.userip)-1);
   // }
   // else
   //     return;*/

   // strncpy_s(ReqMsg.info.typesn,sizeof(ReqMsg.info.typesn),szPointSN,sizeof(ReqMsg.info.typesn)-1);
   // if (NULL!=signstr)
   // {
   //     strncpy_s(ReqMsg.info.signstr,sizeof(ReqMsg.info.signstr),signstr, sizeof(ReqMsg.info.signstr)-1);
   // }
   // 
   // SendMsg(&ReqMsg);
    //GetConnector()->TrySendThirdParty();
}

void GmCommandRobot::OnMsgPFAddPointsAck(Msg *pMsg)
{
    /*MsgPFAddPointsAck* pAckMsg = (MsgPFAddPointsAck*)pMsg;*/
}
/*
void GmCommandRobot::SwitchMsg(Msg* pMsg)
{
    if (NULL == pMsg)
    {
        return;
    }
    switch(pMsg->type)
    {
    case PFMSG_GMKICKPLAYER_ACK:
        OnGMKickPlayer_ACK(pMsg);
        break;
    case PFMSG_GMBANCHAT_ACK:
        OnGMBanChat_ACK(pMsg);
        break;
    case PFMSG_GMMOVEPLAYER_ACK:
        OnGmGMMovePlayer_ACK(pMsg);
        break;
    case PFMSG_GMGETPLAYERMAPINFO_ACK:
        OnGMGetPlayerMapInfo_ACK(pMsg);
        break;
    case PFMSG_GMGETORGANIZEINFO_ACK:
        OnGMGetOrganizeInfo_ACK(pMsg);
        break;
    case PFMSG_GMGETITEMINFO_ACK:
        OnGMGetItemInfo_ACK(pMsg);
        break;
    case PFMSG_GMCHANGEPLAYERINFO_ACK:
        OnGMChangePlayerInfo_ACK(pMsg);
        break;
    case PFMSG_GMCREATEITEMTOPLAYER_ACK:
        OnGMCreateItemToPlayer_ACK(pMsg);
        break;
    case PFMSG_CREATECHAR_ACK:
        OnMsgPFCreateCharAck(pMsg);
        break;
    case PFMSG_ADDITEM_ACK:
        OnMsgPFAddItemAck(pMsg);
        break;
    default:
        break;
    }
}
*/
void GmCommandRobot::OnMsgPFAddItemAck(Msg* pMsg)
{
    MsgPFAddItemAck* pMsgPFAddItemAck = static_cast<MsgPFAddItemAck*>(pMsg);
    if (pMsgPFAddItemAck->result != MsgPFAddItemAck::ER_Success)
    {
        LOG_MESSAGE(LogObject,LOG_PRIORITY_DEBUG,"MsgPFAddItemAck Result = %d ",pMsgPFAddItemAck->result);
        return;
    }
}

void GmCommandRobot::ReqGMCreateRole()
{
    //MsgPFCreateCharReq CreateMsg;
    //CreateMsg.guid = 21;
    //CreateMsg.sex  = rand() % Sex_Max;
    //CreateMsg.profession = rand()%EArmType_MaxSize;
    //CreateMsg.country    = 0;
    //strncpy_s(CreateMsg.charName,sizeof(CreateMsg.charName),"Hero021",7);
    //CreateMsg.level      = 40;
    //CreateMsg.bagid      = 971;
    //SendMsg(&CreateMsg);
    //GetConnector()->TrySendThirdParty();
}

void GmCommandRobot::ReqGMCreateRole(uint32 guid,uint8 sex,uint8 profession,const int8 *charName,uint16 level,uint8 country,uint16  bagid)
{
    /*MsgPFCreateCharReq CreateMsg;
    CreateMsg.guid = guid;
    if (sex >= Sex_Max || sex < Sex_Male)
    {
        return;
    }
    CreateMsg.sex  = sex;
    if (profession >= EArmType_MaxSize || profession < EArmType_Warrior)
    {
        return;
    }
    CreateMsg.profession = profession;
    CreateMsg.country    = country;
    if (NULL == charName || strlen(charName) >= sizeof(CreateMsg.charName))
    {
        return;
    }
    strncpy_s(CreateMsg.charName,sizeof(CreateMsg.charName),"Hero021",7);
    CreateMsg.level      = level;
    CreateMsg.bagid      = bagid;
    SendMsg(&CreateMsg);*/
    //GetConnector()->TrySendThirdParty();
}

void GmCommandRobot::OnGmGMMovePlayer_ACK(Msg *pMsg)
{

}

void GmCommandRobot::OnGMKickPlayer_ACK(Msg *pMsg)
{
    //MsgPFGmKickPlayerAck* pMsg = (MsgPFGmKickPlayerAck*)pMsg;

}

void GmCommandRobot::OnGMBanChat_ACK(Msg *pMsg)
{

}

void GmCommandRobot::OnGMGetPlayerMapInfo_ACK(Msg *pMsg)
{

}

void GmCommandRobot::OnGMGetOrganizeInfo_ACK(Msg *pMsg)
{

}

void GmCommandRobot::OnGMGetItemInfo_ACK(Msg *pMsg)
{

}

void GmCommandRobot::OnGMChangePlayerInfo_ACK(Msg *pMsg)
{

}

void GmCommandRobot::OnGMCreateItemToPlayer_ACK(Msg *pMsg)
{

}

void GmCommandRobot::OnMsgPFCreateCharAck(Msg *pMsg)
{
    /*MsgPFCreateCharAck* pAck = (MsgPFCreateCharAck*)pMsg;
    if(pAck->result == 0)
    {

    }*/
}


void GmCommandRobot::KickPlayer(const char* PlayerName)
{
    //MsgPFGmKickPlayerReq ReqMsg;
    //ReqMsg.accountGuid = 5656; 
    //ReqMsg.chardbId = 1;
    //strncpy_s(ReqMsg.charName,sizeof(ReqMsg.charName),PlayerName,sizeof(ReqMsg.charName)-1);
    //ReqMsg.time = 10;
    //SendMsg(&ReqMsg);
}

void GmCommandRobot::BanSpeak(const char* PlayerName,DWORD Time)
{

}

void GmCommandRobot::Broadcast(std::string BullString)
{
    if ( BullString.empty() || BullString.size() >= MsgPFGMBroadcastReq::CD_ContentMaxSize)
    {
        return;
    }
    MsgPFGMBroadcastReq ReqMsg;
    ZeroMemory(ReqMsg.content,sizeof(ReqMsg.content));
    strncpy_s(ReqMsg.content,sizeof(ReqMsg.content),BullString.c_str(),sizeof(ReqMsg.content)-1 );
    SendMsg(&ReqMsg);
    //GetConnector()->TrySendThirdParty();
}

void GmCommandRobot::Update()
{
   __super::Update();	
    if (!IsConnectted())
    {
   //     SetNoteType(NT_ConnectNode);
        return;
    }

    if (dw_SleepTime != 0 && HQ_TimeGetTime() - dw_SleepCurTime >= dw_SleepTime)
    {
        dw_SleepTime = 0;
    }
    if (dw_SleepTime != 0)
    {
        return;
    }

    if (NULL != GetConnector())
    {
    //    GetConnector()->TryRecvThirdParty();
        PlayGame();
   //     GetConnector()->TrySendThirdParty();
    }
}

// void GmCommandRobot::ProcessMsgs()
// {
//   /  if ( !GetConnector() )
//         return;
// 
//     MsgThirdParty* pMsg = GetConnector()->GetMsgThirdParty();
//     while( pMsg )
//     {
//         if(pMsg->length < sizeof(MsgThirdParty))
//         {
//             DebugLogout("%s %d消息长度小于Msg结构大小 长度:%d", GetBotRoleName(), pMsg->type, pMsg->length);
//             continue;
//         }
//         SwitchMsg(pMsg);
// 
//         if ( !GetConnector() )
//             break;
//         pMsg = GetConnector()->GetMsgThirdParty();
//     }*/
// 
//     //CBot::ProcessMsgs();
// }


void GmCommandRobot::SendMsg(Msg* pMsg)
{
    //if ( !GetConnector() )
    //    return;

    //if(GetConnector()->SendMsgThirdParty(pMsg) == -1)
    //{
    //    Close();
    //    //LOG_MESSAGE(LogObject, LOG_PRIORITY_INFO, "Send MsgThirdParty Error");

    //    if (m_FirstSendPackage)
    //    {
    //        ShowPackTime = HQ_TimeGetTime();
    //        m_FirstSendPackage = false;
    //    }
    //}
}

void GmCommandRobot::UpdateBanWoldLib()
{

}

void GmCommandRobot::MovePlayer2Point(const char* PlayerName,int mapid,int x,int y)
{

}

void GmCommandRobot::QueryCharacterOnlineInfo(const PlayerInfo* PlayerName)
{

}

void GmCommandRobot::QueryCharacterInfo(const PlayerInfo* PlayerName)
{

}

void GmCommandRobot::QueryTongInfo(const PlayerInfo* PlayerName)
{

}

void GmCommandRobot::OpenDoubleExperience(bool IsOpen)
{

}

void GmCommandRobot::KillMonster(int Target)
{

}

void GmCommandRobot::CreateMonster(int nMonsterIndex,int nMonsterNumber)
{

}

void GmCommandRobot::ChangeRoleAttribute(ERoleAttribute AttributeType,int nValue)
{

}

void GmCommandRobot::CreateItem(int ItemId,int num)
{

}

void GmCommandRobot::PushWork(OperationMsg* work)
{
    if (NULL == work)
    {
        return;
    }
    OperationMsg tempwork;
    tempwork = *work;
    CSemiAutoIntLock  _lock;
    CSALocker lock(_lock);
    _workList.push_back(tempwork);
}
