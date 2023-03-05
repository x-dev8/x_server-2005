#include "IdleBot.h"

#define SENDPINGTIME (1000)
#define YANGZHOUMAP_ID 11
#define NEED_MOVE TRUE
#define HUAINANMAP_ID  (3)
#define FISHPOSX        (224)
#define FISHPOSY        (142)
#define FishToolId      (100)

OnlineBot::OnlineBot():m_PingTime(0),m_PlayGame(false)
,ReqRandFlyTime(HQ_TimeGetTime())
,RunTime(HQ_TimeGetTime())
,UseFishItemTime(0)
,IsSendMoveOnce(false)
,IsClear(false)
{
    m_BotType = Bot_Online;
}

OnlineBot::~OnlineBot()
{

}

void OnlineBot::PlayGame()
{
//     if (HQ_TimeGetTime() - m_PingTime >= SENDPINGTIME)
//     {
//         MsgPingMsg pingmsg;
//         m_PingTime = HQ_TimeGetTime();
//         pingmsg.dwTime = HQ_TimeGetTime();
//         SendMsg(&pingmsg);
//     }
    if (!m_PlayGame)
    {
        m_PlayGame = true;
        SetTipsInfo("游戏中..");
    }
//     if (GetBotState() != State_Play)
//     {
//         SetBotState(State_Play);
//         SetTipsInfo("游戏中..");
//     }

//     if (HQ_TimeGetTime() - ReqRandFlyTime >= (2*(60*SENDPINGTIME)))
//     {
//         if (GetMapID() == YANGZHOUMAP_ID)
//         {
// //             LoadRandFlyMap();
// //             RandFly();
//         }
//         ReqRandFlyTime = HQ_TimeGetTime();
//     }
    //CBot::PlayGame();
//     if (NEED_MOVE)
//     {
//         Move();
//     }
    if (HQ_TimeGetTime() - RunTime >= 10*SENDPINGTIME)
    {
        short shOperation =rand()%EP_TOTAL;
        switch(shOperation)
        {
        case EP_FISH:
            GetFish();
            break;
        case EP_CHANGENAME:
            {
                std::string BotName = GetBotRoleName();
                std::string BotNameHead = BotName.substr(0,BotName.find("."));
                char NewName[dr_MaxPlayerName];
                memset(NewName,0,sizeof(NewName));
                if (BotNameHead.compare("T") == 0)
                {
                    sprintf_s(NewName,dr_MaxNameString,"H.%s",m_szBotName);
                }
                else
                {
                    sprintf_s(NewName,dr_MaxNameString,"T.%s",m_szBotName);
                }
                ReqChangeCharacterName(NewName);
            }
            break;
        default:
            break;
        }
        
        RunTime = HQ_TimeGetTime();
    }
}

int OnlineBot::GetFishToolIndexInBag()
{
    for (int i = 0;i < ITEM_BAGMAX;++i)
    {
        if (m_pItemBag[i].itembaseinfo.ustItemID == FishToolId)
        {
            return i;
        }
    }
    return ErrorUnsignedShortID;
}

void OnlineBot::ReqChangeCharacterName(char* szNewName)
{
    int NewStringLegth = strlen(szNewName);
    if (NULL == szNewName|| NewStringLegth == 0 || NewStringLegth > dr_MaxNameString)
    {
        return;
    }

    MsgChangeNameReq ReqName;
    strncpy_s(ReqName.name,sizeof(ReqName.name),szNewName,dr_MaxNameString);
    SendMsg(&ReqName);
}

void OnlineBot::SwitchMsg(Msg* pMsg)
{
    if (NULL == pMsg)
    {
        return;
    }

    switch(pMsg->GetType())
    {
    case MSG_BEKICK:
        OnMsgNotifyBeKick(pMsg);
        break;
     default:
         BaseRobot::SwitchMsg(pMsg);
    }
}

void OnlineBot::OnMsgNotifyBeKick(Msg* pMsg)
{
    MsgNotifyBeKick* pMsgNotifyBeKick = static_cast<MsgNotifyBeKick*>(pMsg);
    switch (pMsgNotifyBeKick->kickType)
    {
    case MsgNotifyBeKick::EKT_ChangeNameKick: // 改名被踢        
        break;
    case MsgNotifyBeKick::EKT_AccountKick: // 被其他账号踢
        break;
    case MsgNotifyBeKick::EKT_GraphicCodeErrorKick: // 验证错误被踢
        break;
    case MsgNotifyBeKick::EKT_Ban:  // GM
        break;
    case MsgNotifyBeKick::EKT_SystemKick: // 系统被踢
        break;
    case MsgNotifyBeKick::EKT_GraphicCodeTimeOut: // 验证码超时
        break;
    case MsgNotifyBeKick::EKT_Hook: // 使用外挂
        break;
    case MsgNotifyBeKick::EKT_None: // None 默认值
        break;
    }
}

void OnlineBot::GetFish()
{
    if ( GetBotLevel() < 60 )
    {
        ReqLvlUp(60);
        return;
    }

    if (GetMapID() != HUAINANMAP_ID)
    {
        FlyToMap(HUAINANMAP_ID,FISHPOSX,FISHPOSY);
        return;
    }
    
    if (IsNormalBagFull())
    {
        ClearNormalBagItem();
        return;
    }

    if (IsMaterialBagFull())
    {
        ClearMaterialBagItem();
        IsClear = true;
        return;
    }

    D3DXVECTOR3 Pos;
    Pos.x = FISHPOSX;
    Pos.y = FISHPOSY;
    Pos.z = 0;
    if (MoveToPoint(Pos))
    {
        int Index = GetFishToolIndexInBag();
        if (Index == ErrorUnsignedShortID)
        {
            //请求item
            char MsgStrBuf[512];
            ZeroMemory(MsgStrBuf,sizeof(MsgStrBuf));
            sprintf_s(MsgStrBuf,sizeof(MsgStrBuf),"/createitem %d 1 0",FishToolId);
            MsgChat MsgStr(MsgChat::CHAT_TYPE_NORMAL);
            MsgStr.SetString(MsgStrBuf);
            SendMsg(&MsgStr);
            return;
        }
        
        if (HQ_TimeGetTime() - UseFishItemTime >= 3 * 60 * SENDPINGTIME )
        {
            MsgUseGoods UseItem;
            UseItem.nRemainValue = 0;
            UseItem.stDstChar = GetBotShortId();
            UseItem.stSrcChar = GetBotShortId();
            UseItem.stItemCount = 1;
            UseItem.ucItemBagType = BT_NormalItemBag;
            UseItem.ustItemIndex = Index;
            SendMsg(&UseItem);
            UseFishItemTime = HQ_TimeGetTime();
            SetTipsInfo("捕鱼中");
            //IsSendMoveOnce = false;
        }
    }
}

void OnlineBot::InitPlayGame(UINT mapid)
{
    //CBot::InitPlayGame();

    //请求装备
    if (InitGetItem()) { return; }

    //请求等级
    if(m_CharInfo.baseinfo.liveinfo.ustLevel < 60)
    {
        ReqLvlUp(60);
        return;
    }

    if (m_nMoveStep < 1000)
    {
        m_nMoveStep = 1000;// 1秒的移动间隔
    }
}

void OnlineBot::SetAreaInfo(SAreaInfo *pAreaInfo)
{
    if (pAreaInfo  != NULL)
    {
        m_xAreaInfo.nMap = pAreaInfo->nMap;
        m_xAreaInfo.xPoint.x = pAreaInfo->xPoint.x;
        m_xAreaInfo.xPoint.y = pAreaInfo->xPoint.y;
        m_xAreaInfo.nRadius = pAreaInfo->nRadius;
    }		
}