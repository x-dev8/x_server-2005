#include "Bargaining.h"
#include "ShareData.h"
#include "GameWorld.h"
#include "Configure.h"
#include "XmlStringLanguage.h"
//#include "LogFileObjectName.h"

#define MAX_BARGAINING_TIME (1000*60*5)    // 五分钟
 
BargainingManager& GetBargainingManager()
{
    static BargainingManager intance;
    return intance;
}

BargainingManager::BargainingManager()
{
}

BargainingManager::~BargainingManager()
{
}


bool BargainingManager::IsThePlayerBargainingNow( unsigned int nPlayerId )
{
    for ( ItRoomContainer it = m_lRooms.begin() ; it != m_lRooms.end(); ++it )
    {
        if ( it->nPlayer1 == nPlayerId || it->nPlayer2 == nPlayerId )
        {
            return true;
        }
    }
    return false;
}

bool BargainingManager::IsThePlayerBargainingNow( unsigned int nPlayer1Id, unsigned int nPlayer2Id )
{
    for ( ItRoomContainer it = m_lRooms.begin(); it != m_lRooms.end(); ++it)
    {
        if ( it->nPlayer1 == nPlayer1Id || it->nPlayer2 == nPlayer1Id ||
            it->nPlayer1 == nPlayer2Id || it->nPlayer2 == nPlayer2Id )
        {
            return true;
        }
    }
    return false;
}

bool BargainingManager::ThePlayerInSameRoom( const unsigned int nPlayer1Id,const unsigned int nPlayer2Id )
{
    for ( ItRoomContainer it = m_lRooms.begin(); it != m_lRooms.end(); ++it)
    {
        if ( ( it->nPlayer1 == nPlayer1Id && it->nPlayer2 == nPlayer2Id ) ||
            ( it->nPlayer1 == nPlayer2Id && it->nPlayer2 == nPlayer1Id ) )
        {
            return true;
        }
    }
    return false;
}

bool BargainingManager::AddRoom( unsigned int nPlayer1Id, unsigned int nPlayer2Id )
{
    if ( nPlayer1Id == nPlayer2Id )
        return false;

    if ( IsThePlayerBargainingNow(nPlayer1Id,nPlayer2Id) )
        return false;

    stRoom st;
    st.nPlayer1 = nPlayer1Id;
    st.nPlayer2 = nPlayer2Id;
    st.dwStartTime = HQ_TimeGetTime();
    m_lRooms.push_back(st);
    return true;
}

bool BargainingManager::DelRoom( unsigned int nPlayerId )
{
    for ( ItRoomContainer it = m_lRooms.begin(); it != m_lRooms.end(); ++it)
    {
        if ( it->nPlayer1 == nPlayerId || it->nPlayer2 == nPlayerId )
        {
            m_lRooms.erase(it);
            return true;
        }
    }
    return false;
}

unsigned char BargainingManager::BargainingNow( BaseCharacter* pSend, BaseCharacter* pRec, MsgBargainingNow* pBargainingNow )
{
    if ( !pSend || !pRec || !pSend->IsPlayer() || !pRec->IsPlayer() || !pBargainingNow)
    { return MsgAckBargaining::ACK_UNKNOWERROR; }

    const int nSendId = pSend->GetID();
    const int nRecId  = pRec->GetID();
        
    if ( IsComplete_First(nSendId)|| IsComplete_Last(nSendId) )
    { // 如果已经确认了,则双方都要重新确认
        SetComplete_First( nSendId, false );
        SetComplete_First( nRecId, false );
        SetComplete_Last( nSendId, false );
        SetComplete_Last( nRecId, false );

        MsgAckBargaining msg;
        msg.enType = TYPE_RE_COMPLETION;
        GettheServer().SendMsgToSingle( &msg, pSend );
        GettheServer().SendMsgToSingle( &msg, pRec );
    }

    stRoom* pRoom = GetRoom( nSendId );
    if ( pRoom == NULL )
    { return MsgAckBargaining::ACK_NOTINBARGAIN; }

    bool bIsPlayer1Send = false;
    if ( pRoom->nPlayer1 == nSendId )
    { bIsPlayer1Send = true; }

    unsigned short ustItemID = 0;       // 在前面有判断 这里其实可以不做判断了
    __int64 nGuid = 0;
    
    switch( pBargainingNow->type ) 
    {
    case MsgBargainingNow::TypeItem:
        {
            switch ( pBargainingNow->item.ucItemBagType )
            {
            case BT_NormalItemBag:
            case BT_MaterialBag:
                {
                    SCharItem xItem;
                    pBargainingNow->item.GetItemData( (void*)&xItem, sizeof(SCharItem) );
                    if ( xItem.itembaseinfo.nOnlyInt <= 0 )
                    { return MsgAckBargaining::ACK_ERRORITEM; }
                    ustItemID = xItem.itembaseinfo.ustItemID;
                    nGuid     = xItem.itembaseinfo.nOnlyInt;
                    CItemDetail::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( ustItemID );
                    if ( pItemCommon == NULL )
                    { return MsgAckBargaining::ACK_UNKNOWERROR; }

                    if ( !pItemCommon->bIsCanTrade )
                    { return MsgAckBargaining::ACK_CANNOTBARGAIN; }
                }
                break;
            case BT_MountBag:
                {
                    SMountItem xMountItem;
                    pBargainingNow->item.GetItemData( (void*)&xMountItem, sizeof(SMountItem) );
                    if ( xMountItem.baseInfo.guid <= 0 )
                    { return MsgAckBargaining::ACK_ERRORITEM; }
                    CItemDetail::SDrome* pDrome = GettheItemDetail().GetDromeByID( xMountItem.baseInfo.id );
                    if ( pDrome == NULL ) 
                    { return MsgAckBargaining::ACK_UNKNOWERROR; }
                }
                break;
            default:
                break;
            }

            ItrRoomItemContainer itGoodsBegin;
            ItrRoomItemContainer itGoodsEnd;
            if ( bIsPlayer1Send )
            {
                itGoodsBegin = pRoom->m_lPlayer1Goods.begin();
                itGoodsEnd = pRoom->m_lPlayer1Goods.end();
            }
            else
            {
                itGoodsBegin = pRoom->m_lPlayer2Goods.begin();
                itGoodsEnd = pRoom->m_lPlayer2Goods.end();
            }

            // 做一些校验,把服务器的物品信息重新设置保存在消息里( 这个消息要发给对方看的 ),否则可能造成欺骗
            GamePlayer *pSendPlayer = (GamePlayer*) pSend;
            switch ( pBargainingNow->item.ucItemBagType )
            {
            case BT_NormalItemBag:
            case BT_MaterialBag:
                {
                    SCharItem* pCharItem = NULL;
                    if ( pBargainingNow->item.ucItemBagType == BT_NormalItemBag )
                    {
                        pCharItem = pSendPlayer->_NormalItemBag.GetItemByIndex( pBargainingNow->item.nIndex );
                    }
                    else
                    {
                        pCharItem = pSendPlayer->_MaterialItemBag.GetItemByIndex( pBargainingNow->item.nIndex );
                    }

                    if ( pCharItem == NULL || pCharItem->itembaseinfo.ustItemID != ustItemID || pCharItem->itembaseinfo.nOnlyInt != nGuid )
                    { return MsgAckBargaining::ACK_ERRORITEM; }

                    if ( pCharItem->IsLock() )
                    { return MsgAckBargaining::ACK_ITEMLOCK; }

                    if ( !pBargainingNow->item.SetItemData( (void*)pCharItem, sizeof( SCharItem ) ) )
                    { return MsgAckBargaining::ACK_DATAERROR; }
                }
            	break;
            case BT_MountBag:
                { //在上面做判断
                    SMountItem* pMountItem = pSendPlayer->_mountManager.GetMountByIndex( pBargainingNow->item.nIndex );
                    if ( pMountItem == NULL ) 
                    { return MsgAckBargaining::ACK_NOTHISGOODS; }

                    SMountItem xMountItem;
                    if ( !pBargainingNow->item.GetItemData( (void*)&xMountItem, sizeof(SMountItem) ) )
                    { return MsgAckBargaining::ACK_DATAERROR; }
                    if ( pMountItem->baseInfo.id != xMountItem.baseInfo.id || pMountItem->baseInfo.guid != xMountItem.baseInfo.guid )
                    { return MsgAckBargaining::ACK_ERRORITEM; }

                    if ( pMountItem->IsLock() )
                    { return MsgAckBargaining::ACK_ITEMLOCK; }

                    if ( pBargainingNow->item.nIndex == pSendPlayer->_mountManager.GetActiveMountIndex() )
                    { return MsgAckBargaining::ACK_ACTIVEMOUNT; }

                    if ( !pBargainingNow->item.SetItemData( ( void* )pMountItem, sizeof( SMountItem ) ) )
                    { return MsgAckBargaining::ACK_DATAERROR; }
                }
                break;
            default:
                return MsgAckBargaining::ACK_UNKNOWERROR;
                break;
            }

            if ( !pBargainingNow->item.bGetDown )
            { // 放上
                // 是否有相同的物品
                ItrRoomItemContainer itGoods;
                for ( itGoods = itGoodsBegin; itGoods != itGoodsEnd; ++ itGoods)
                {
                    if ( pBargainingNow->item.ucItemBagType == itGoods->ucItemBagType )
                    {
                        if ( pBargainingNow->item.nIndex == itGoods->index )
                            return MsgAckBargaining::ACK_ALREADYBARGAIN;   // 索引相同

                        if ( pBargainingNow->item.ucItemBagType == BT_MountBag )
                        {
                            SMountItem* pClientMount = ( SMountItem* ) pBargainingNow->item.szItemData;
                            SMountItem* pServerMount = ( SMountItem* )itGoods->szItemData;
                            if ( pClientMount->baseInfo.guid == pServerMount->baseInfo.guid )
                            { return MsgAckBargaining::ACK_ALREADYBARGAIN; }

                        }
                        else if (pBargainingNow->item.ucItemBagType == BT_NormalItemBag || pBargainingNow->item.ucItemBagType == BT_MaterialBag )
                        {
                            SCharItem* pClientItem = ( SCharItem* ) pBargainingNow->item.szItemData;
                            SCharItem* pServerItem = ( SCharItem* ) itGoods->szItemData;
                            if ( pClientItem->itembaseinfo.nOnlyInt == pServerItem->itembaseinfo.nOnlyInt )
                            { return MsgAckBargaining::ACK_ALREADYBARGAIN; }
                        }
                    }
                }

                // 将交易物品信息保存
                stRoom::stItem stItem;
                stItem.ucItemBagType = pBargainingNow->item.ucItemBagType;    
                if ( !pBargainingNow->item.GetItemData( ( void* )&stItem.szItemData, sizeof( stItem.szItemData ) ) )
                { return MsgAckBargaining::ACK_DATAERROR; }
                stItem.index         = pBargainingNow->item.nIndex;
                if ( bIsPlayer1Send )
                {
                    pRoom->m_lPlayer1Goods.push_back(stItem);
                }
                else
                {
                    pRoom->m_lPlayer2Goods.push_back(stItem);
                }
                return MsgAckBargaining::ACK_SUCCESSORAGREE;
            }
            else
            { // 拿下来
                ItrRoomItemContainer itGoods;
                for ( itGoods=itGoodsBegin; itGoods != itGoodsEnd; ++itGoods )      //  拿下来也要判断是guid
                {
                    if ( pBargainingNow->item.ucItemBagType == itGoods->ucItemBagType && pBargainingNow->item.nIndex == itGoods->index )
                    {
                        if ( pBargainingNow->item.ucItemBagType == BT_MountBag )
                        {
                            SMountItem* pClientMount = ( SMountItem* ) pBargainingNow->item.szItemData;
                            SMountItem* pServerMount = ( SMountItem* )itGoods->szItemData;
                            if ( pClientMount->baseInfo.guid != pServerMount->baseInfo.guid )
                            { return MsgAckBargaining::ACK_ERRORITEM; }

                            if ( !pBargainingNow->item.SetItemData( itGoods->szItemData, sizeof( SMountItem ) ) )      // 发给对方的都要以服务器为准
                            { return MsgAckBargaining::ACK_DATAERROR; }
                        }
                        else if (pBargainingNow->item.ucItemBagType == BT_NormalItemBag || pBargainingNow->item.ucItemBagType == BT_MaterialBag )
                        {
                            SCharItem* pClientItem = ( SCharItem* ) pBargainingNow->item.szItemData;
                            SCharItem* pServerItem = ( SCharItem* ) itGoods->szItemData;
                            if ( pClientItem->itembaseinfo.nOnlyInt != pServerItem->itembaseinfo.nOnlyInt )
                            { return MsgAckBargaining::ACK_ERRORITEM; }
                            
                            if ( !pBargainingNow->item.SetItemData( itGoods->szItemData, sizeof( SCharItem ) ) )       // 发给对方的都要以服务器为准
                            { return MsgAckBargaining::ACK_DATAERROR; }
                        }
                        else
                        { return MsgAckBargaining::ACK_UNKNOWERROR; }


                        if ( bIsPlayer1Send )
                        {
                            pRoom->m_lPlayer1Goods.erase(itGoods);
                        }
                        else
                        {
                            pRoom->m_lPlayer2Goods.erase(itGoods);
                        }
                        return MsgAckBargaining::ACK_SUCCESSORAGREE;
                    }
                }
                return MsgAckBargaining::ACK_NOTINBARGAIN;
            }
        }
        break;
    case MsgBargainingNow::TypeMoney:
        {
            DWORD dwMoney = pBargainingNow->dwMoney;
      
            if ( bIsPlayer1Send )
            {
                pRoom->dwPlayer1Money = dwMoney;
            }
            else
            {
                pRoom->dwPlayer2Money = dwMoney;
            }
            return MsgAckBargaining::ACK_SUCCESSORAGREE;
        }
        break;
    case MsgBargainingNow::TypeRMB:
        {
            DWORD dwRMB = pBargainingNow->dwRMB;
            if ( bIsPlayer1Send )
            {
                pRoom->dwPlayer1RMB = dwRMB;
            }
            else
            {
                pRoom->dwPlayer2RMB = dwRMB;
            }
            return MsgAckBargaining::ACK_SUCCESSORAGREE;
        }
        break;
    default:
        return MsgAckBargaining::ACK_UNKNOWERROR;
    }
    return MsgAckBargaining::ACK_UNKNOWERROR;
}

bool BargainingManager::IsComplete_First( const unsigned int nPlayerId )
{
    for ( std::list<stRoom>::iterator it = m_lRooms.begin(); it != m_lRooms.end(); ++it )
    {
        if ( it->nPlayer1 == nPlayerId )
        {
            return it->bPlayer1Complete_First;
        }
        else if ( it->nPlayer2 == nPlayerId )
        {
            return it->bPlayer2Complete_First;
        }// End if
    }// End for
    return false;
}

bool BargainingManager::SetComplete_First( const int nPlayerId, bool bComplete )
{
    for (std::list<stRoom>::iterator it = m_lRooms.begin(); it != m_lRooms.end(); ++it )
    {
        if ( it->nPlayer1 == nPlayerId )
        {
            it->bPlayer1Complete_First = bComplete;
            return it->bPlayer2Complete_First;
        }
        else if ( it->nPlayer2 == nPlayerId )
        {
            it->bPlayer2Complete_First = bComplete;
            return it->bPlayer1Complete_First;
        }// End if
    }// End for
    return false;
}

bool BargainingManager::IsComplete_Last( const unsigned int nPlayerId )
{
    for ( std::list<stRoom>::iterator it = m_lRooms.begin(); it != m_lRooms.end(); ++it )
    {
        if ( it->nPlayer1 == nPlayerId )
        {
            return it->bPlayer1Complete_Last;
        }
        else if ( it->nPlayer2 == nPlayerId )
        {
            return it->bPlayer2Complete_Last;
        }// End if
    }// End for
    return false;
}

bool BargainingManager::SetComplete_Last( const int nPlayerId, bool bComplete )
{
    for ( std::list<stRoom>::iterator it = m_lRooms.begin(); it != m_lRooms.end(); ++it )
    {
        if ( it->nPlayer1 == nPlayerId )
        {
            it->bPlayer1Complete_Last = bComplete;
            return it->bPlayer2Complete_Last;
        }
        else if ( it->nPlayer2 == nPlayerId )
        {
            it->bPlayer2Complete_Last = bComplete;
            return it->bPlayer1Complete_Last;
        }// End if
    }// End for
    return false;
}

BargainingManager::stRoom* BargainingManager::GetRoom( const unsigned int nPlayerId )
{
    for ( std::list<stRoom>::iterator it = m_lRooms.begin(); it != m_lRooms.end(); ++it )
    {
        if ( it->nPlayer1 == nPlayerId || it->nPlayer2 == nPlayerId )
        {
            return &(*it);
        }
    }
    return NULL;
}

bool BargainingManager::ExChange( GamePlayer* pPlayer1, GamePlayer* pPlayer2 )
{
    if ( !pPlayer1 || !pPlayer2 )
        return false;

    if ( !IsComplete_Last( pPlayer1->GetID() ) || !IsComplete_Last( pPlayer2->GetID() ))
        return false;

    if ( !ThePlayerInSameRoom( pPlayer1->GetID(), pPlayer2->GetID() ) )
        return false;

    stRoom* pRoom = GetRoom( pPlayer1->GetID() );
    if ( pRoom == NULL )
    { return false; }

    if ( pRoom->m_lPlayer1Goods.empty() && pRoom->m_lPlayer2Goods.empty() && 
        pRoom->dwPlayer1Money == 0 && pRoom->dwPlayer2Money == 0 && 
        pRoom->dwPlayer1RMB == 0 && pRoom->dwPlayer2RMB == 0)
    {
        return false;
    }


    if ( pRoom->nPlayer1 != pPlayer1->GetID() )
    {
        GamePlayer* pTemp = pPlayer1;
        pPlayer1 = pPlayer2;
        pPlayer2 = pTemp;
    }

    std::list<stRoom::stItem>::iterator it;
    // Player1的背包
    for ( it = pRoom->m_lPlayer1Goods.begin(); it != pRoom->m_lPlayer1Goods.end(); ++it )
    {
        SCharItem* pCharItem = NULL;
        if ( it->ucItemBagType == BT_NormalItemBag )
        {
            pCharItem = pPlayer1->_NormalItemBag.GetItemByIndex( it->index );
            if( pCharItem == NULL )
            { return false; }
        }
        else if ( it->ucItemBagType == BT_MaterialBag )
        {
            pCharItem = pPlayer1->_MaterialItemBag.GetItemByIndex( it->index );
            if ( pCharItem == NULL )
            { return false; }
        }
        else if ( it->ucItemBagType == BT_MountBag )
        {
            SMountItem* pMountItem = pPlayer1->_mountManager.GetMountByIndex( it->index );
            if ( pMountItem == NULL )
            { return false; }

            if ( it->index == pPlayer1->_mountManager.GetActiveMountIndex() )
            { return false; }

            SMountItem* pRoomMount = ( SMountItem* )it->szItemData;
            if ( pRoomMount == NULL || pRoomMount->baseInfo.guid != pMountItem->baseInfo.guid )
            { return false; }

            if ( pMountItem->IsLock() || pRoomMount->IsLock() )
            { return false; }
        }

        if ( it->ucItemBagType == BT_NormalItemBag || it->ucItemBagType == BT_MaterialBag )
        {
            SCharItem* pRoomItem = (SCharItem*) it->szItemData;
            if ( pCharItem == NULL || pRoomItem == NULL || pCharItem->itembaseinfo.ustItemID != pRoomItem->itembaseinfo.ustItemID || pCharItem->itembaseinfo.nOnlyInt != pRoomItem->itembaseinfo.nOnlyInt )
            { return false; }
            if ( pCharItem->itembaseinfo.ustItemCount < pRoomItem->itembaseinfo.ustItemCount )
            { return false; }
            if ( pCharItem->itembaseinfo.value1 != pRoomItem->itembaseinfo.value1 || pCharItem->itembaseinfo.value2 != pRoomItem->itembaseinfo.value2 )
            { return false; }
            //加锁物品不能交易
            if( pCharItem->IsLock() || pCharItem->IsBounded() )
            { return false; }
            if( pCharItem->IsOverdue() )
            { return false; }
        }
    }
    // Player2的背包
    for ( it = pRoom->m_lPlayer2Goods.begin(); it != pRoom->m_lPlayer2Goods.end(); ++it )
    {
        SCharItem* pCharItem = NULL;
        if ( it->ucItemBagType == BT_NormalItemBag )
        {
            pCharItem = pPlayer2->_NormalItemBag.GetItemByIndex( it->index );
            if ( pCharItem == NULL )
            { return false; }
        }
        else if ( it->ucItemBagType == BT_MaterialBag )
        {
            pCharItem = pPlayer2->_MaterialItemBag.GetItemByIndex( it->index );
            if ( pCharItem == NULL )
            { return false; }
        }
        else if ( it->ucItemBagType == BT_MountBag )
        {
            SMountItem* pMountItem = pPlayer2->_mountManager.GetMountByIndex( it->index );
            if ( pMountItem == NULL ) 
            { return false; }

            if ( it->index == pPlayer2->_mountManager.GetActiveMountIndex() )
            { return false; }

            SMountItem* pRoomMount = ( SMountItem* )it->szItemData;
            if ( pRoomMount == NULL || pRoomMount->baseInfo.guid != pMountItem->baseInfo.guid )
            { return false; }

            if ( pMountItem->IsLock() || pRoomMount->IsLock() )
            { return false; }   // 物品加锁不能交易
        }

        if ( it->ucItemBagType == BT_NormalItemBag || it->ucItemBagType == BT_MaterialBag )
        {
            SCharItem* pRoomItem = (SCharItem*) it->szItemData;

            if ( pCharItem == NULL || pRoomItem == NULL || pCharItem->itembaseinfo.ustItemID != pRoomItem->itembaseinfo.ustItemID || pCharItem->itembaseinfo.nOnlyInt != pRoomItem->itembaseinfo.nOnlyInt )
            { return false; }
            if ( pCharItem->itembaseinfo.ustItemCount < pRoomItem->itembaseinfo.ustItemCount )
            { return false; }
            if ( pCharItem->itembaseinfo.value1 != pRoomItem->itembaseinfo.value1 || pCharItem->itembaseinfo.value2 != pRoomItem->itembaseinfo.value2 )
            { return false; }
            //加锁物品不能交易
            if( pCharItem->IsLock() || pCharItem->IsBounded() )
            { return false; }
            if( pCharItem->IsOverdue() )
            { return false; }
        }
    }
   
    if ( !IsCanExChange( pRoom, pPlayer1, pPlayer2 ) )
    { return false; }

    char szLog[256] = { 0 };
    sprintf_s( szLog, sizeof( szLog ) - 1, theXmlString.GetString(eLog_info_2slk_9), pPlayer1->GetCharName(), pPlayer2->GetCharName() );
    pPlayer1->Log( szLog );
    pPlayer2->Log( szLog );
    // ----- 移除
    // Player1
    pPlayer1->OperateMoney( EOT_Sub, pRoom->dwPlayer1Money );
    pPlayer1->OperateJinDing( EOT_Sub, pRoom->dwPlayer1RMB );
    for ( it = pRoom->m_lPlayer1Goods.begin(); it != pRoom->m_lPlayer1Goods.end(); ++it )
    {
        if ( it->ucItemBagType == BT_NormalItemBag )
        {
            SCharItem* pCharItem = (SCharItem*) it->szItemData;
            int nIndex = -1;
            pPlayer1->_NormalItemBag.PopItemByOnlyBigId( pCharItem->itembaseinfo.nOnlyInt, pCharItem->itembaseinfo.ustItemCount, nIndex );
        } 
        else if (it->ucItemBagType == BT_MaterialBag )
        {
            SCharItem* pCharItem = (SCharItem*) it->szItemData;
            int nIndex = -1;
            pPlayer1->_MaterialItemBag.PopItemByOnlyBigId( pCharItem->itembaseinfo.nOnlyInt, pCharItem->itembaseinfo.ustItemCount, nIndex );
        }
        else if ( it->ucItemBagType == BT_MountBag )
        {
            bool bActiveMount = false;
            SMountItem* pMountItem = (SMountItem*) it->szItemData;
            if ( pMountItem->baseInfo.guid != 0 )
            {
                pPlayer1->_mountManager.PopMountByBigId( pMountItem->baseInfo.guid, bActiveMount );

                char szID[60] = { 0 };
                sprintf_s( szLog, sizeof(szLog)-1, theXmlString.GetString(eLog_info_2slk_11), pMountItem->baseInfo.szName, BigInt2String(pMountItem->baseInfo.guid, szID), 1);
                pPlayer1->Log( szLog );
            }
        }
        //
        if ( it->ucItemBagType == BT_NormalItemBag || it->ucItemBagType == BT_MaterialBag )
        {
            SCharItem* pCharItem = (SCharItem*) it->szItemData;

            CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID(pCharItem->itembaseinfo.ustItemID);

            if (pItem != NULL)
            {
                char szID[60] = { 0 };
                sprintf_s( szLog, sizeof(szLog)-1, theXmlString.GetString(eLog_info_2slk_11), pItem->GetItemName(), BigInt2String(pCharItem->itembaseinfo.nOnlyInt, szID), pCharItem->itembaseinfo.ustItemCount);
                pPlayer1->Log( szLog );
            }
        }
    }

    // Player2
    pPlayer2->OperateMoney( EOT_Sub, pRoom->dwPlayer2Money );
    pPlayer2->OperateJinDing( EOT_Sub, pRoom->dwPlayer2RMB );
    for ( it = pRoom->m_lPlayer2Goods.begin(); it!=pRoom->m_lPlayer2Goods.end(); ++it )
    {
        if ( it->ucItemBagType == BT_NormalItemBag )
        {
            SCharItem* pCharItem = (SCharItem*) it->szItemData;
            int nIndex = -1;
            pPlayer2->_NormalItemBag.PopItemByOnlyBigId( pCharItem->itembaseinfo.nOnlyInt, pCharItem->itembaseinfo.ustItemCount, nIndex );
        }
        else if (it->ucItemBagType == BT_MaterialBag )
        {
            SCharItem* pCharItem = (SCharItem*) it->szItemData;
            int nIndex = -1;
            pPlayer2->_MaterialItemBag.PopItemByOnlyBigId( pCharItem->itembaseinfo.nOnlyInt, pCharItem->itembaseinfo.ustItemCount, nIndex );
        }
        else if ( it->ucItemBagType == BT_MountBag )
        {
            bool bActive = false;
            SMountItem* pMountItem = (SMountItem*) it->szItemData;
            if ( pMountItem->baseInfo.guid != 0 )
            {
                pPlayer2->_mountManager.PopMountByBigId( pMountItem->baseInfo.guid, bActive );

                char szID[60] = { 0 };
                sprintf_s( szLog, sizeof(szLog)-1, theXmlString.GetString(eLog_info_2slk_11), pMountItem->baseInfo.szName, BigInt2String(pMountItem->baseInfo.guid, szID), 1);
                pPlayer2->Log( szLog );
            }
        }
        //
        if ( it->ucItemBagType == BT_NormalItemBag || it->ucItemBagType == BT_MaterialBag )
        {
            SCharItem* pCharItem = (SCharItem*) it->szItemData;

            CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID(pCharItem->itembaseinfo.ustItemID);
            if (pItem != NULL)
            {
                char szID[60] = { 0 };
                sprintf_s( szLog, sizeof(szLog)-1, theXmlString.GetString(eLog_info_2slk_11), pItem->GetItemName(), BigInt2String(pCharItem->itembaseinfo.nOnlyInt, szID), pCharItem->itembaseinfo.ustItemCount);
                pPlayer2->Log( szLog );
            }
        }
    }

    // ----- 添加
    // Player1
    pPlayer1->OperateMoney( EOT_Add, pRoom->dwPlayer2Money );
    pPlayer1->OperateJinDing( EOT_Add, pRoom->dwPlayer2RMB );
    for ( it = pRoom->m_lPlayer2Goods.begin(); it != pRoom->m_lPlayer2Goods.end(); ++it )
    {
        if ( it->ucItemBagType == BT_NormalItemBag || it->ucItemBagType == BT_MaterialBag )
        {
            SCharItem* pCharItem = (SCharItem*) it->szItemData;

            unsigned short ustCount = pCharItem->itembaseinfo.ustItemCount;

            int nResult = ierr_unknown;
            if ( it->ucItemBagType == BT_NormalItemBag )
            {
                nResult = pPlayer1->_NormalItemBag.PushItem( *pCharItem, ustCount );
            }
            else if ( it->ucItemBagType == BT_MaterialBag )
            {
                nResult = pPlayer1->_MaterialItemBag.PushItem( *pCharItem, ustCount );
            }

            CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID(pCharItem->itembaseinfo.ustItemID);
            if ( pItem != NULL )
            {
                char szID[60] = { 0 };
                
                if ( nResult != ierr_Success )
                {
                    pPlayer1->Log( theXmlString.GetString(eLog_info_2slk_13), pItem->GetItemName(),BigInt2String(pCharItem->itembaseinfo.nOnlyInt, szID), ustCount );
                }
                else
                {
                    pPlayer1->Log( theXmlString.GetString(eLog_info_2slk_14), pItem->GetItemName(),BigInt2String(pCharItem->itembaseinfo.nOnlyInt, szID), ustCount );
                }
            }
        }
        else if ( it->ucItemBagType == BT_MountBag )
        {
            SMountItem* pMountItem = (SMountItem*) it->szItemData; 
            if ( pMountItem->baseInfo.guid != 0 )
            {
                pPlayer1->_mountManager.PushMount( *pMountItem );

                char szID[60] = { 0 };
                pPlayer1->Log( theXmlString.GetString(eLog_info_2slk_14), pMountItem->baseInfo.szName, BigInt2String(pMountItem->baseInfo.guid, szID), 1 );
            }
        }
    }
    // Player2
    pPlayer2->OperateMoney( EOT_Add, pRoom->dwPlayer1Money );
    pPlayer2->OperateJinDing( EOT_Add, pRoom->dwPlayer1RMB );
    for ( it = pRoom->m_lPlayer1Goods.begin(); it != pRoom->m_lPlayer1Goods.end(); ++it )
    {
        if ( it->ucItemBagType == BT_NormalItemBag || it->ucItemBagType == BT_MaterialBag )
        {
            SCharItem* pCharItem = (SCharItem*) it->szItemData;

            unsigned short ustCount = pCharItem->itembaseinfo.ustItemCount;
            int nResult = ierr_unknown;
            if ( it->ucItemBagType == BT_NormalItemBag )
            {
                nResult = pPlayer2->_NormalItemBag.PushItem( *pCharItem, ustCount );
            }
            else if ( it->ucItemBagType == BT_MaterialBag )
            {
                nResult = pPlayer2->_MaterialItemBag.PushItem( *pCharItem, ustCount );
            }
            CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID(pCharItem->itembaseinfo.ustItemID);

            if ( pItem != NULL )
            {
                char szID[60] = { 0 };
                if ( nResult != ierr_Success )
                {
                    pPlayer2->Log( theXmlString.GetString(eLog_info_2slk_13), pItem->GetItemName(),BigInt2String(pCharItem->itembaseinfo.nOnlyInt, szID),ustCount );
                }
                else
                {
                    pPlayer2->Log( theXmlString.GetString(eLog_info_2slk_14), pItem->GetItemName(),BigInt2String(pCharItem->itembaseinfo.nOnlyInt, szID), ustCount );
                }
            }
        }
        else if ( it->ucItemBagType == BT_MountBag )
        {
            SMountItem* pMountItem = (SMountItem*) it->szItemData; 
            if ( pMountItem->baseInfo.guid != 0 )
            {
                pPlayer2->_mountManager.PushMount( *pMountItem );
                char szID[60] = { 0 };
                pPlayer2->Log( theXmlString.GetString(eLog_info_2slk_14), pMountItem->baseInfo.szName, BigInt2String(pMountItem->baseInfo.guid, szID), 1 );
            }
        }
    }// End for
    //
    sprintf_s( szLog, sizeof( szLog ) - 1, theXmlString.GetString(eLog_info_2slk_17),pPlayer1->GetCharName(), pPlayer2->GetCharName() );
    pPlayer1->Log( szLog );
    pPlayer2->Log( szLog );

    pRoom->dwPlayer1Money = 0;
    pRoom->dwPlayer2Money = 0;
    pRoom->m_lPlayer1Goods.clear();
    pRoom->m_lPlayer2Goods.clear();
    return true;
}

int BargainingManager::GetBargainingerId( const unsigned int nPlayerId )
{ // 得到交易对像的ID,如失败反回-1
    ItRoomContainer it = m_lRooms.begin();
    for ( ; it != m_lRooms.end(); ++it )
    {
        if ( it->nPlayer1 == nPlayerId )
        {
            return it->nPlayer2;
        }
        else if( it->nPlayer2 == nPlayerId )
        {
            return it->nPlayer1;
        }
    }
    return -1;
}

void BargainingManager::UpDateBargaining()
{
    ItRoomContainer it = m_lRooms.begin();
    for ( ; it != m_lRooms.end(); ++it )
    {   
        if ( GameTime::IsPassCurrentTime( it->dwStartTime, MAX_BARGAINING_TIME ) )
        {
            MsgAckBargaining msg;
            msg.enType = TYPE_BARGAININGING;
            msg.enResult = MsgAckBargaining::ACK_TIMEOUT;
            BaseCharacter* pChar1 = theRunTimeData.GetCharacterByID( it->nPlayer1 );
            BaseCharacter* pChar2 = theRunTimeData.GetCharacterByID( it->nPlayer2 );
            if (pChar1)
            {
                GettheServer().SendMsgToSingle( &msg, pChar1 );
            }
            if (pChar2)
            {
                GettheServer().SendMsgToSingle( &msg, pChar2 );
            }
            m_lRooms.erase(it);
            return;
        }
    }
}

bool BargainingManager::IsCanExChange( stRoom* pRoom, GamePlayer* pPlayer1, GamePlayer* pPlayer2 )
{
    if ( pRoom == NULL || pPlayer1 == NULL || pPlayer2 == NULL )
    { return false;  }
    
    // 检查是否有足够的钱, 并且不能超过背包的最大数量
    if ( pRoom->dwPlayer1Money > pPlayer1->GetMoney() || ( pRoom->dwPlayer1Money + pPlayer2->GetMoney() > g_Cfg.m_nMoneyMax ) )
    { return false; }

    if ( pRoom->dwPlayer2Money > pPlayer2->GetMoney() || ( pRoom->dwPlayer2Money + pPlayer1->GetMoney() > g_Cfg.m_nMoneyMax ) )
    { return false; }

    if ( pRoom->dwPlayer1RMB > pPlayer1->GetJinDing() )
    { return false; }

    if ( pRoom->dwPlayer2RMB > pPlayer2->GetJinDing() )
    { return false; }

    //检查包裹空间是否足够, 交易的物品大于背包数量
    int nNormalCount1 = 0;
    int nMaterialCount1 = 0;
    int nMountCount1 = 0;
    for ( std::list<stRoom::stItem>::iterator iter = pRoom->m_lPlayer1Goods.begin(); iter != pRoom->m_lPlayer1Goods.end(); ++iter )
    {
        if ( iter->ucItemBagType == BT_NormalItemBag )
        {
            ++nNormalCount1;
        }
        else if ( iter->ucItemBagType == BT_MaterialBag )
        {
            ++nMaterialCount1;
        }
        else if ( iter->ucItemBagType == BT_MountBag )
        {
            ++nMountCount1;
        }
    }

    int nNormalCount2 = 0;
    int nMaterialCount2 = 0;
    int nMountCount2 = 0;
    for ( std::list<stRoom::stItem>::iterator iter = pRoom->m_lPlayer2Goods.begin(); iter != pRoom->m_lPlayer2Goods.end(); ++iter )
    {
        if ( iter->ucItemBagType == BT_NormalItemBag )
        {
            ++nNormalCount2;
        }
        else if ( iter->ucItemBagType == BT_MaterialBag )
        {
            ++nMaterialCount2;
        }
        else if ( iter->ucItemBagType == BT_MountBag )
        {
            ++nMountCount2;
        }
    }

    // 普通背包可能会有叠加的物品,popitem的时候可能还占用格子,所以不能用 nNormalCount2 和 nNormalCount1 相差来计算
    if ( ( nNormalCount1 > pPlayer2->_NormalItemBag.GetItemEmptyCount() ) || 
         ( nNormalCount2 > pPlayer1->_NormalItemBag.GetItemEmptyCount() ) )
    {
        return false;
    }

    if ( ( nMaterialCount1 > pPlayer2->_MaterialItemBag.GetItemEmptyCount() ) ||
        ( nMaterialCount2  > pPlayer1->_MaterialItemBag.GetItemEmptyCount() ) )
    {
        return false;
    }

    if ( (nMountCount1 > nMountCount2 && (nMountCount1 - nMountCount2) > pPlayer2->_mountManager.GetMountEmptyCount()) ||
        (nMountCount2 > nMountCount1 && (nMountCount2 - nMountCount1) > pPlayer1->_mountManager.GetMountEmptyCount()) )
    {
        return false;
    }

    return true;
}