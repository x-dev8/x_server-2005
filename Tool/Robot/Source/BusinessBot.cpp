#include "stdafx.h"
#include "BusinessBot.h"
#include "ItemDetail.h"

#define CHANGESTATETIMECONFINE (5 * (60 * 1000))
#define BarginItemNum   20
#define NoFindInList (-1)
CBusinessBot::CBusinessBot():
CurRunState(EBS_Idle),
ChangeStateTime(0),
IsNameDouble(ECNR_NameError),
LastShopTarget(NULL),
LastBusuinessTime(NULL),
LastBargainTime(NULL),
IdleTime(NULL),
CheckItemTime(NULL),
bOpenPrivateShop( false )
{
    ZeroMemory(TargetShopItem,sizeof(TargetShopItem));
    m_BotType = Bot_Business;
    //MsgBargainingNows.resize(ITEM_BAGMAX);
    ZeroMemory(BargainingList,sizeof(BargainingList));
    ZeroMemory(SelfBargainingList,sizeof(SelfBargainingList));
}

CBusinessBot::~CBusinessBot()
{

}

void CBusinessBot::think() // 每5分钟切换一种随机状态
{
    if (HQ_TimeGetTime() - ChangeStateTime >= CHANGESTATETIMECONFINE)
    {
        int RandState = rand()%2 == 0? EBS_ReqStallage:EBS_Stallageing;
        //int RandState = rand()%2?EBS_Stallageing:EBS_ReqBusiness;
        //if (RandState != _CurRunState)
        {
            CurRunState = RandState;
            //CurRunState = EBS_Stallageing;
        }
    }
}

void CBusinessBot::ReqMoney()
{
    if (GetBotMoney() > 3000)
    {
        return;
    }
    std::string strMoney;
    strMoney = "/self AddMoney 100000";
    MsgChat chat(MsgChat::CHAT_TYPE_NORMAL);
    chat.SetString(strMoney.c_str());
    SendMsg(&chat);
}

bool CBusinessBot::IsEmptyBag()
{
    for (int i = 0;i<ITEM_BAGMAX;++i)
    {
        if (m_pItemBag[i].itembaseinfo.ustItemID != ErrorUnsignedShortID)
        {
            return false;
        }
    }
    return true;
}

void CBusinessBot::InitPlayGame(UINT mapid )
{
    // 拿钱
    ReqMoney();
//     if ()
//     {
//     }
//     std::string Name = GetBotRoleName();
//     _IsNameDouble = CheckName(Name);
    
}

void CBusinessBot::ReqBusinessItem()
{
    //CheckSelfBag();
    /*
    3701	草果
    3702	当归
    3703	甘草
    3704	茯苓
    3705	紫草
    */
    char szChatItem[255];
    for (int ItemId = EREQ_StartItemId;ItemId<=EREQ_EndItemId;++ItemId)
    {
        ZeroMemory(szChatItem,sizeof(szChatItem));
        sprintf_s(szChatItem,sizeof(szChatItem)-1,"/CreateItem %d 1 0",ItemId);
        MsgChat ItemChat(MsgChat::CHAT_TYPE_NORMAL);
        ItemChat.SetString(szChatItem);
        SendMsg(&ItemChat);
    }
}

#define BUSUINESSTIME (1000)
#define MINUTE        (60*10000)
void CBusinessBot::PlayGame()
{
    if (HQ_TimeGetTime()-LastBusuinessTime<=BUSUINESSTIME)
    {
        return;
    }
    BaseRobot::PlayGame();

    if (!CheckSelfBag())
    {
        // 拿道具
        ReqBusinessItem();
    }

    LastBusuinessTime = HQ_TimeGetTime();
    switch (CurRunState)
    {
    case EBS_Stallageing:
        Stallage();
    	break;
    case EBS_ReqStallage:
        ReqQueryStallage();
        break;
    case EBS_EndStallage:
        UnStallage();
        break;
    case EBS_ReqBusiness:
        {
            // 找人，找不到人就随机移动
            bool MoveOk = false;
            PlayerInfo* player = GetTarget();
            if (player != NULL)
            {
                MoveOk = MoveToPoint(player->m_vPos);
            }
            else
            {
                Move();
            }

            // 如果在玩家附近的话,就开始请求交易
            if (MoveOk)
            {
                if (HQ_TimeGetTime() - LastBargainTime > 2*MINUTE)
                {
                    ClearTempList();
                    ReqBusiness(player->shPlayerID);
                }
                LastBargainTime = HQ_TimeGetTime();
            }
        }
        break;
    case EBS_Businessing:
        break;
    case EBS_SureBusiness:
        break;
    case EBS_Idle:
        {
            think();
//             if (_CurRunState != EBS_Stallageing)
//             {
//                 if (HQ_TimeGetTime() - IdleTime >= 3*MINUTE)
//                 {
//                     _CurRunState = EBS_Stallageing;
//                     IdleTime = HQ_TimeGetTime();
//                 }
//             }
        }
        break;
    }
}

void CBusinessBot::ClearTempList()
{
    for (int i = 0;i<MaxTempBargainingList;++i)
    {
        BargainingList[i].itembaseinfo.ustItemID = ErrorUnsignedShortID;
    }
    for (int i = 0;i<MaxTempBargainingList;++i)
    {
        SelfBargainingList[i].itembaseinfo.ustItemID = ErrorUnsignedShortID;
    }
}
void CBusinessBot::ReqBusiness(short PlayerID)   // 发出交易请求
{
    //PlayerInfo* target = GetTarget();
//     if (NULL == target)
//     { return; }
    MsgQueryBargaining ReqBargaining;
    ReqBargaining.stTargetID = PlayerID;/*target->shPlayerID;*/
    ReqBargaining.enType = TYPE_QUERY_BARGAINING;
    SendMsg(&ReqBargaining);
}

void CBusinessBot::Stallage()   // 摆摊
{
    //UnStallage();
    // 先要移动道具
    if (bOpenPrivateShop)
    {
        return;
    }

    if (IsPrivateShopBagEmpty())
    {
        int k = 0;
        for (int i = 0;i <= BarginItemNum;++i,++k)
        {
            if(k >= ITEM_PRIVATE_SHOP_BAGMAX)
            {
                break;
            }

            if (m_pItemBag[i].itembaseinfo.useType != ErrorUnsignedShortID)
            {
                CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID(m_pItemBag[i].itembaseinfo.ustItemID);

                MsgMovePrivateShopItem Move;
                Move.ucItemBagType = BT_NormalItemBag;
                Move.dwPrice = 1;
                Move.enMoveType = MsgMovePrivateShopItem::Type_PackToPrivateShop;
                Move.ustSrcIndex = i;
                Move.ustDstIndex = k;
                Move.ucCount = m_pItemBag[i].itembaseinfo.ustItemCount;
                Move.nGuid = m_pItemBag[i].itembaseinfo.nOnlyInt;
                SendMsg(&Move);

                if (NULL != pItem)
                {
                    SPrivateShopItemInfo SelfItem;
                    SelfItem.chItemType = pItem->ucItemType;
                    SelfItem.dwPrice = 1;
                    SelfItem.nCount = m_pItemBag[i].itembaseinfo.ustItemCount;
                    SelfItem.nOnlyInt = m_pItemBag[i].itembaseinfo.nOnlyInt;
                    SetBotPrivateShopBag(&SelfItem,k);
                }
            }
        }
    }
    
    char buf[512];
    MsgTurnOnOffPrivateShop OpenPriveShop;
    OpenPriveShop.bTurnOn = true;
    OpenPriveShop.dwTargetId = GetBotDBID();
    sprintf_s(buf ,sizeof(OpenPriveShop.szShopInfo),"%s \'s shop",GetBotRoleName());
    OpenPriveShop.SetShopInfe(buf);
    SendMsg(&OpenPriveShop);
    //CurRunState = EBS_ReqBusiness;
}

PlayerInfo* CBusinessBot::GetTarget()
{
    short id = FindRandStallageList();
    
    for (PlayerInfoContainer::iterator itr = m_listPlayerList.begin();itr!=m_listPlayerList.end();++itr)
    {
        if ( CurRunState == EBS_ReqStallage && id != NoFindInList && id != itr->shPlayerID)
        {
            continue;
        }

        if (IsEnemyPlayer (*itr))
        {
            short result = CheckName(itr->szName);
            if (result != ECNR_NameError && result != IsNameDouble)
            {
                if (LastShopTarget != &(*itr))
                {
                    LastShopTarget = &(*itr);
                    return &(*itr);
                }
//                 target.dwCharacterID = itr->dwCharacterID;
//                 target.dwMapID    = itr->dwMapID;
//                 target.m_vPos     = itr->m_vPos;
//                 target.nHP        = itr->nHP;
//                 target.shCharType = itr->shCharType;
//                 target.shMonsterType = itr->shMonsterType;
//                 target.shPlayerID = itr->shPlayerID;
//                 strncpy_s(target.szName,sizeof(target.szName),itr->szName,sizeof(target.szName)-1);
            }
        }
        else if (itr->shCharType == Object_Player)
        {
            return &(*itr);
        }
    }
    return NULL;
}

void CBusinessBot::ReqQueryStallage() // 响应摆摊
{
    // 查找目标
    PlayerInfo* Target = GetTarget();
    if (NULL == Target)
    {
        Move();
        return;
    }
    // 请求查看摆摊
    MsgQueryPrivateShopItem QueryItem; 
    QueryItem.dwTargetId = Target->shPlayerID;
    SendMsg(&QueryItem);
    // 检查背包是否满了,满了就清空
    if (CheckSelfBag())
    {
        ClearNormalBagItem();
    }
}

void CBusinessBot::OnMsgAckResult(Msg* pMsg)
{
    MsgAckResult* Result = (MsgAckResult*)pMsg;
    switch(Result->result)
    {
    case ER_InProtectLockTime:
    case ER_LessPrivateShopLevel:
    case ER_ActiveMountCanNotTrade:
        {
            ReqLvlUp(60);
        }
    case ER_PrivateShopItemError:
        bOpenPrivateShop = false;
        return;
    }
    BaseRobot::OnMsgAckResult(pMsg);
}

short CBusinessBot::CheckName(const std::string &TarageName) // 判断名字,双数,返回0  单数,返回1 名字错误 返回-1
{
    std::string::size_type NumStringPos = TarageName.find(".");
    if (NumStringPos == std::string::npos)
    {
        return ECNR_NameError;
    }
    bool bNum = true;
    std::string NumString = TarageName.substr(NumStringPos+1,TarageName.size());
    for (int i = 0;i<NumString.size();++i)
    {
        if ( NumString.at(i) < 0 && NumString.at(i) > 9 )
        {
            bNum = false;
            break;
        }
    }
    if (!bNum)
    {
        return ECNR_NameError;
    }
    int num = atoi(NumString.c_str());

    return num%2 == 0?ECNR_Double:ECNR_Single;
}

void CBusinessBot::OnMsgAckBargaining(Msg* pMsg)
{
    MsgAckBargaining* pBargaining = (MsgAckBargaining*)pMsg;
    /*
    switch (pBargaining->enResult)
    {
    case :
    break;
    case MsgAckBargaining::ACK_UNKNOWERROR:
    break;
    case MsgAckBargaining::ACK_BARGAININGNOW:
    break;
    case MsgAckBargaining::ACK_UNAGREE:
    break;
    case MsgAckBargaining::ACK_NOTHISGOODS:
    break;
    case MsgAckBargaining::ACK_NOTSPACE:
    break;
    case MsgAckBargaining::ACK_NOENOUGHMONEY:
    break;
    case MsgAckBargaining::ACK_TIMEOUT:
    break;
    case MsgAckBargaining::ACK_INBLACKLIST:
    break;
    }
    */
    if (pBargaining->enResult == MsgAckBargaining::ACK_SUCCESSORAGREE)
    {//交易成功
        for (int i = 0;i<MaxTempBargainingList;++i)
        {
            if (SelfBargainingList[i].itembaseinfo.ustItemID != ErrorUnsignedShortID)
            {
                for (int k = 0;k < BarginItemNum;++k)
                {
                    if(m_pItemBag[k].itembaseinfo.ustItemID == SelfBargainingList[i].itembaseinfo.ustItemID 
                        && m_pItemBag[k].itembaseinfo.nOnlyInt == SelfBargainingList[i].itembaseinfo.nOnlyInt )
                    {
                        m_pItemBag[k].itembaseinfo.ustItemID = ErrorUnsignedShortID;
                    }
                }
            }
        }

        for (int i = 0;i<MaxTempBargainingList;++i)
        {
            if (BargainingList[i].itembaseinfo.ustItemID != ErrorUnsignedShortID)
            {
                int BagId = GetNullItemIndex();
                memcpy_s(&m_pItemBag[BagId],sizeof(SCharItem),&BargainingList[i],sizeof(SCharItem));
            }
        }
        
        return;
    }
    else if (pBargaining->enType == TYPE_RE_COMPLETION)
    {//重新确
        MsgQueryBargaining QueryAgreeBargaining;
        QueryAgreeBargaining.enType = TYPE_AGREE_COMPLETION_FIRST;
        QueryAgreeBargaining.header.stID = GetBotShortId();
        SendMsg(&QueryAgreeBargaining);
        return;
    }
    ClearTempList();    
}

void CBusinessBot::SwitchMsg(Msg* pMsg)
{
    if(NULL == pMsg)
        return;
    switch(pMsg->GetType())
    {
//     case :
//         break;
//     case :
//         break;
     case MSG_BARGAININGNOW:
        OnMsgBargainingNow(pMsg);
        break;
     case MSG_QUERYBARGAINING:
         OnMsgQueryBargaining(pMsg);
         break;
    case MSG_ACKBARGAINING:
        OnMsgAckBargaining(pMsg);
        break;
    case MSG_PRIVATE_SHOP_ITEM_SELL:
        OnMsgPrivateShopItemSell(pMsg);
        break;
    case MSG_ACK_BUY_PRIVATE_SHOP_ITEM:
        OnMsgAckBuyPrivateShopItem(pMsg);
        break;
    case MSG_REFEASH_PRIVATE_SHOP_ITEM:
        OnMsgRefeashPrivateShopItem(pMsg);
        break;
    case MSG_TURN_ON_OFF_PRIVATE_SHOP:
        OnMsgTurnOnOffPrivateShop(pMsg);
        break;
    default:
        CFightBot::SwitchMsg(pMsg);
        break;
    }
}

void CBusinessBot::OnMsgBargainingNow(Msg *pMsg)
{
    MsgBargainingNow* pNow = (MsgBargainingNow*)pMsg;
    //对方放的东西
    if (!pNow->item.bGetDown)
    {
        memcpy_s(&BargainingList[pNow->item.nIndex],sizeof(SCharItem),pNow->item.szItemData,sizeof(SCharItem));
    }
    else
    {
        BargainingList[pNow->item.nIndex].itembaseinfo.ustItemID = ErrorUnsignedShortID;
    }
   
    //MsgBargainingNows[pNow->item.nIndex] = *pNow;
}

void CBusinessBot::OnMsgQueryBargaining(Msg* pMsg)
{
    MsgQueryBargaining* pQueryBargain = (MsgQueryBargaining*) pMsg;
    CurRunState = EBS_Businessing;
    if (pQueryBargain->enType == TYPE_QUERY_BARGAINING)
    {
        MsgAckBargaining AckMsg;
        AckMsg.enType = TYPE_ACK_BARGAINING;
        AckMsg.stTargetID = pQueryBargain->stTargetID;
        AckMsg.header.stID = GetBotShortId();
        AckMsg.enResult = MsgAckBargaining::ACK_SUCCESSORAGREE;
        SendMsg(&AckMsg);
    }
    else if (TYPE_AGREE_COMPLETION_FIRST == pQueryBargain->enType)
    {
        MsgAckBargaining SecondAgree;
        SecondAgree.enType = TYPE_AGREE_COMPLETION_LAST;
        SecondAgree.stTargetID = pQueryBargain->stTargetID;
        SendMsg(&SecondAgree);
        // 双方确认之后,就交易成功
    }
    else if (pQueryBargain->enType == TYPE_BEGIN_BARGAINING)
    {
        MsgBargainingNow BarNow;
        if (pQueryBargain->stTargetID == GetBotShortId())
        {
            BarNow.type = MsgBargainingNow::TypeMoney;
            BarNow.SetMoney(2);
            SendMsg(&BarNow);
            BarNow.type = MsgBargainingNow::TypeItem;
            for (int i = 0;i<=ITEM_BAGMAX;++i)
            {//
                if (m_pItemBag[i].itembaseinfo.ustItemID != ErrorUnsignedShortID)
                {
                    BarNow.SetItemData(&m_pItemBag[i],BT_NormalItemBag,sizeof(SCharItem),i,false);
                }
                SendMsg(&BarNow);
            }
            MsgQueryBargaining QueryAgreeBargaining;
            QueryAgreeBargaining.enType = TYPE_AGREE_COMPLETION_FIRST;
            QueryAgreeBargaining.header.stID = GetBotShortId();
        }
        else
        {
            BarNow.header.stID = GetBotShortId();
            BarNow.type = MsgBargainingNow::TypeMoney;
            BarNow.SetMoney(2);
            SendMsg(&BarNow);
            BarNow.type = MsgBargainingNow::TypeItem;

            for (int i = 0,k = 0;i < BarginItemNum ;++i)
            {//
                if (m_pItemBag[i].itembaseinfo.ustItemID != ErrorUnsignedShortID)
                {
                    BarNow.SetItemData(&m_pItemBag[i],BT_NormalItemBag,sizeof(SCharItem),i,false);
                    SendMsg(&BarNow);
                    memcpy_s(&SelfBargainingList[k++],sizeof(SelfBargainingList),&m_pItemBag[i],sizeof(SCharItem));
                }
                if (k>=MaxTempBargainingList)
                {
                    break;
                }
            }
            MsgQueryBargaining QueryAgreeBargaining;
            QueryAgreeBargaining.enType = TYPE_AGREE_COMPLETION_FIRST;
            QueryAgreeBargaining.header.stID = GetBotShortId();
            SendMsg(&QueryAgreeBargaining);
        }
    }

}

void CBusinessBot::OnMsgPrivateShopItemSell(Msg* pMsg)
{
    // 移除自己商店的道具
    MsgPrivateShopItemSell* Sell = (MsgPrivateShopItemSell*)pMsg;
    SetBotMoney(Sell->dwCurMoney);
    if (Sell->ucItemBagType == BT_NormalItemBag)
    {
        SPrivateShopItemInfo* pSelfShop = GetBotPrivateShopBag();
        pSelfShop[Sell->ustIndex].chItemType = ShopItemType_None;
        m_pItemBag[Sell->ucItemIndex].itembaseinfo.ustItemID = ErrorUnsignedShortID;
        SetBotMoney(Sell->dwCurMoney);
    }
}

void CBusinessBot::OnMsgAckBuyPrivateShopItem(Msg* pMsg)
{
    // 买到东西以后
    MsgAckBuyPrivateShopItem* shopitem = (MsgAckBuyPrivateShopItem*)pMsg;
    if (shopitem->enResult ==MsgAckBuyPrivateShopItem::Result_Success)
    {
         if (shopitem->ucItemBagType == BT_NormalItemBag)
         {
             //SPrivateShopItem::GetShopItemData(m_pItemBag[shopitem->ustDstIndex].itembaseinfo,shopitem->ustSrcIndex)
             if (TargetShopItem[shopitem->ustSrcIndex].chItemType != ShopItemType_None)
             {
                 TargetShopItem[shopitem->ustSrcIndex].GetShopItemData(&m_pItemBag[shopitem->ustDstIndex],sizeof(SCharItem));
                 TargetShopItem[shopitem->ustSrcIndex].chItemType = ShopItemType_None;
                 SPrivateShopItemInfo* pPrivateShop = GetBotPrivateShopBag();
                 if (NULL != pPrivateShop)
                 {
                    pPrivateShop[shopitem->ustSrcIndex].chItemType = ShopItemType_None;
                 }
             }
         }
    }
}

void CBusinessBot::OnMsgRefeashPrivateShopItem(Msg* pMsg)
{
    MsgRefeashPrivateShopItem* res = (MsgRefeashPrivateShopItem*)pMsg;
    memcpy_s(TargetShopItem,sizeof(TargetShopItem),res->stItem,sizeof(res->stItem));
    for (int i = 0;i < ITEM_PRIVATE_SHOP_BAGMAX;++i)
    {
        if (TargetShopItem[i].chItemType != ShopItemType_None)
        {
            SCharItem buyItem;
            TargetShopItem[i].GetShopItemData(&buyItem,sizeof(SCharItem));
            if (buyItem.itembaseinfo.ustItemID != ErrorUnsignedShortID)
            {
                MsgQueryBuyPrivateShopItem BuyShop;
                BuyShop.header.stID = GetBotShortId();
                BuyShop.ustSrcIndex = buyItem.itembaseinfo.ustItemID;
                BuyShop.ustDstIndex = GetNullItemIndex();
                BuyShop.dwTargetId = res->header.stID;
                
                BuyShop.stShopItemInfo.chItemType = TargetShopItem[i].chItemType;
                BuyShop.stShopItemInfo.dwPrice = TargetShopItem[i].dwPrice;
                BuyShop.stShopItemInfo.nOnlyInt = buyItem.itembaseinfo.nOnlyInt;
                BuyShop.stShopItemInfo.nCount = buyItem.itembaseinfo.ustItemCount;
                SendMsg(&BuyShop);
            }
        }
    }
}

void CBusinessBot::OnMsgTurnOnOffPrivateShop(Msg* pMsg)
{
    MsgTurnOnOffPrivateShop* pIsOpShop = (MsgTurnOnOffPrivateShop*)pMsg;
    if (pIsOpShop->dwTargetId == GetBotShortId())
    {
        // 修改机器人的状态
        if (!pIsOpShop->bTurnOn)
        {
            CurRunState = EBS_Idle;
            bOpenPrivateShop = false;
            CanControl = true;
        }
        else
        {
            bOpenPrivateShop = true;
            CanControl = false;
        }
        return;
    }
    // 视野内有玩家摆摊，记录别人的状态
    if (FindStallageList(pIsOpShop->dwTargetId) == NoFindInList)
    {
        StallagePlayers.push_back(pIsOpShop->dwTargetId);
    }    
}

short CBusinessBot::FindRandStallageList()
{
    if (StallagePlayers.empty())
    {
        return NoFindInList;
    }
    if (StallagePlayers.size() == 1)
    {
        return *StallagePlayers.begin();
    }

    int index = rand()%StallagePlayers.size();
    return StallagePlayers[index];
}

short CBusinessBot::FindStallageList(DWORD id)
{
    if (StallagePlayers.empty())
    {
        return NoFindInList;
    }
    for (OtherGamePlayerIdList::iterator itr = StallagePlayers.begin();itr != StallagePlayers.end();++itr)
    {
        if (*itr == id)
        {
            return *itr;
        }
    }
    return NoFindInList;
}

// 检查背包之是否有道具，如果满了，就情况，重新请求
bool CBusinessBot::CheckSelfBag()  
{
    /*
    3701	草果
    3702	当归
    3703	甘草
    3704	茯苓
    3705	紫草
    */
    if (HQ_TimeGetTime() - CheckItemTime >= 2*MINUTE)
    {
        int EmpeyBagNum = 0;
        int JiaoYiDaoJuShu = 0;
        for (int i = 0;i<= ITEM_BAGMAX;++i)
        {
            if (m_pItemBag[i].itembaseinfo.ustItemID == ErrorUnsignedShortID)
            {
                EmpeyBagNum++;
            }
            else if (m_pItemBag[i].itembaseinfo.ustItemID >= EREQ_StartItemId||
                m_pItemBag[i].itembaseinfo.ustItemID <= EREQ_EndItemId)
            {
                JiaoYiDaoJuShu++;
            }
        }
        if (JiaoYiDaoJuShu < 5)
        {
            CheckItemTime = HQ_TimeGetTime();
            return false;
        }

        if (EmpeyBagNum <= 85 )
        {
            ClearNormalBagItem();
        }
        CheckItemTime = HQ_TimeGetTime();
    }
    
    
    return true;
}

void CBusinessBot::UnStallage()
{
    for (int PrivateIndex = 0,ItemBagIndex = 0;PrivateIndex<=ITEM_PRIVATE_SHOP_BAGMAX;++PrivateIndex,++ItemBagIndex)
    {
        SPrivateShopItemInfo* pPrivate = GetBotPrivateShopBag();
        if (NULL != pPrivate)
        {
            if (pPrivate[PrivateIndex].chItemType != ShopItemType_None)
            {
                //CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID(m_pItemBag[ItemBagIndex].itembaseinfo.ustItemID);
                
                MsgMovePrivateShopItem Move;
                Move.dwPrice = 1;
                Move.enMoveType = MsgMovePrivateShopItem::Type_PrivateShopToPack;
                Move.ustSrcIndex = PrivateIndex;
                Move.ustDstIndex = ItemBagIndex;
                Move.ucCount = m_pItemBag[PrivateIndex].itembaseinfo.ustItemCount;
                Move.nGuid = m_pItemBag[PrivateIndex].itembaseinfo.nOnlyInt;
                SendMsg(&Move);
                pPrivate[PrivateIndex].chItemType = ShopItemType_None;
            }
        }        
    }
    MsgTurnOnOffPrivateShop OpenPriveShop;
    OpenPriveShop.bTurnOn = false;
    SendMsg(&OpenPriveShop);
    CurRunState = EBS_Idle;
//     int k = 0;
//     for (int i = 0;i<=ITEM_BAGMAX;++i,++k)
//     {
//         if (m_pItemBag[i].itembaseinfo.useType != ErrorUnsignedShortID)
//         {
//             MsgMovePrivateShopItem Move;
//             Move.dwPrice = 1;
//             Move.enMoveType = BT_NormalItemBag;
//             Move.ustSrcIndex = i;
//             Move.ustDstIndex = k;
//             Move.ucCount = m_pItemBag[i].itembaseinfo.ustItemCount;
//             Move.nGuid = m_pItemBag[i].itembaseinfo.nOnlyInt;
//             SendMsg(&Move);
//         }
//     }
}