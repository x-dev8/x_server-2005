#include "GamePlayer.h"
#include "ConsignmentMessage.h"
#include "Configure.h"
#include "RelationManager.h"
#include "XmlStringLanguage.h"

bool GamePlayer::ProcessConsignmentMessage( Msg* pMsg )
{
    DWORD dwType = pMsg->GetType();

    GAMESERVER_MESSAGE_MAPPING_BEGIN
        GAMESERVER_MESSAGE_HANDLE( CS2GS_CONSIGNMENTCOUNT, OnMsgConsignmentCount );
        GAMESERVER_MESSAGE_HANDLE( CS2GS_CONSIGNMENTOPERATEEND, OnCS2GSConsignmentOperate );
        GAMESERVER_MESSAGE_HANDLE( CS2GS_OPERATEMONEYACK, OnCS2GSOperateMoneyAck );
    
        GAMESERVER_MESSAGE_HANDLE( MSG_QUERYCONSIGNMENTLIST, OnMsgQueryConsignmentList );
        GAMESERVER_MESSAGE_HANDLE( MSG_OPERATEACCOUNTREQ, OnMsgOperateMoneyReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_CONSIGNMENTMONEYREQ, OnMsgConsignmentMoneyReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_CONSIGNMENTMONEYHISTROYREQ, OnMsgConsignmentMoneyHistroy );
        GAMESERVER_MESSAGE_HANDLE( MSG_CONSIGNMENTOPERATEREQ, OnMsgConsignmentOperateReq );
		//
		//GAMESERVER_MESSAGE_HANDLE( MSG_CONSIGNMENTITEMREQ, OnMsgConsignmentItemReq );
        
    GAMESERVER_MESSAGE_MAPPING_END
    return false;
}

void GamePlayer::OpenConsignmentMoneyWindow(bool bGetAll)
{
    // 向Center请求接受信息
    GS2CSOpenConsignmentMoneyWindow xOpen;
	xOpen.bGetAll = bGetAll;
    xOpen.nPlayerID = GetDBCharacterID();
    GettheServer().SendMsgToCenterServer( &xOpen );
}

void GamePlayer::OnMsgConsignmentCount( Msg* pMsg )
{
    CS2GSConsignmentAccount* pAccount = static_cast< CS2GSConsignmentAccount* >( pMsg );
    if ( pAccount == NULL )
    { return; }

    m_bIsWaitProcess = pAccount->bProcess;
    SetPlayerConsignmentAccount( pAccount->xAcount.GetRMBMoney(), pAccount->xAcount.GetGameMoney() );
}

void GamePlayer::OnCS2GSConsignmentOperate( Msg* pMsg )
{
    CS2GSConsignmentOperate* pAck = static_cast< CS2GSConsignmentOperate* >( pMsg );
    m_bIsWaitProcess = pAck->bProcess;
}

void GamePlayer::OnMsgQueryConsignmentList( Msg* pMsg )
{
    MsgQueryConsignmentList* pReq = static_cast< MsgQueryConsignmentList* >( pMsg );
    if ( pReq == NULL )
    { return; }

    if ( CheckPlayerConsignmentProcessing() )
    {
        return SendOperateAckToClient< MsgQueryConsignmentListAck >( MsgQueryConsignmentListAck::ECD_WaitProcess );
    }

    SetPlayerConsignmentProcessing();

    // 通知center请求列表
    GS2CSQueryConsignmentList xQuery;
    xQuery.nPlayerID = GetDBCharacterID();
    xQuery.uchConsignmentType = pReq->uchConsignmentType;
    xQuery.uchQueryType       = pReq->uchQueryType;
    xQuery.nCount             = pReq->nCount;
    GettheServer().SendMsgToCenterServer( &xQuery );
}

void GamePlayer::OnMsgOperateMoneyReq( Msg* pMsg )
{
    MsgOperateMoneyReq* pReq = static_cast< MsgOperateMoneyReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    if ( pReq->nGameMoney == 0 && pReq->nRMBMoney == 0 )
    { 
		//lyh++  如果客户端发送操寄售行存入操作都为0 ，则说明是请求现有的存入数据。
		MsgShowConsignmentAccount xShow;
		xShow.nRMBMoney  = m_nRMBMoney;
		xShow.nGameMoney = m_nGameMoney;
		SendMessageToClient( &xShow );
		return; 
	
	}

    if ( IsInProtectLockTime() )
    { return SendOperateAckToClient< MsgOperateMoneyAck >( MsgOperateMoneyAck::ECD_InProtectLockTime ); }

    if ( CheckPlayerConsignmentProcessing() )
    {
        return SendOperateAckToClient< MsgOperateMoneyAck >( MsgOperateMoneyAck::ECD_WaitProcess );
    }

    switch( pReq->uchOperate )
    {
    case ConsignmentDefine::Operate_Save:
        {
            if ( pReq->nGameMoney != 0 )
            {
                if ( m_nGameMoney + pReq->nGameMoney > ConsignmentDefine::MaxAccountGameMoney )
                {
                    return SendOperateAckToClient< MsgOperateMoneyAck >( MsgOperateMoneyAck::ECD_TooMuchMoney );
                }

                if ( pReq->nGameMoney > GetMoney() )
                {
                    return SendOperateAckToClient< MsgOperateMoneyAck >( MsgOperateMoneyAck::ECD_NotEnoughMoney );
                }
            }

            if ( pReq->nRMBMoney != 0 )
            {
                if ( m_nRMBMoney + pReq->nRMBMoney > ConsignmentDefine::MaxAccountRMB )
                {
                    return SendOperateAckToClient< MsgOperateMoneyAck >( MsgOperateMoneyAck::ECD_TooMuchJinDing );
                }

                if ( pReq->nRMBMoney > /*GetJinDing()*/GetJinPiao() ) //存钱判断绑金 lrt
                {
                    return SendOperateAckToClient< MsgOperateMoneyAck >( MsgOperateMoneyAck::ECD_NotEnoughJinDing );
                }
            }

            // 先扣金币和金锭
            OperateMoney( EOT_Sub, pReq->nGameMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_Consignment );
            //OperateJinDing( EOT_Sub, pReq->nRMBMoney, __FUNCTION__, __LINE__ );
			OperateJinPiao( EOT_Sub, pReq->nRMBMoney, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Consignment); //寄售存钱改成绑金 lrt
        }
        break;
    case ConsignmentDefine::Operate_TakeOut:
        {
            if ( pReq->nGameMoney != 0 )
            {
                if ( GetMoney() + pReq->nGameMoney > g_Cfg.m_nMoneyMax )
                {
                    return SendOperateAckToClient< MsgOperateMoneyAck >( MsgOperateMoneyAck::ECD_TooMuchMoney );
                }

                if ( pReq->nGameMoney > m_nGameMoney  )
                {
                    return SendOperateAckToClient< MsgOperateMoneyAck >( MsgOperateMoneyAck::ECD_NotEnoughMoney );
                }
            }
    
            if ( pReq->nRMBMoney != 0 )
            {
                if ( pReq->nRMBMoney > m_nRMBMoney )
                {
                    return SendOperateAckToClient< MsgOperateMoneyAck >( MsgOperateMoneyAck::ECD_NotEnoughJinDing );
                }
            }
        }
        break;
    default:
        return;
    }

    SetPlayerConsignmentProcessing();

    Log( theXmlString.GetString(eServerLog_GetOrSaveMoney), GetCharName(), GetDBCharacterID(), pReq->uchOperate, pReq->nRMBMoney, pReq->nGameMoney );
	// Log( "玩家[%s][%u]请求存取钱[%d]操作 金锭[%u]游戏币[%u], 发送给DB处理", GetCharName(), GetDBCharacterID(), pReq->uchOperate, pReq->nRMBMoney, pReq->nGameMoney );

    // 通知CenterServer
    GS2CSOperateMoneyReq xOperate;
    xOperate.nPlayerID  = GetDBCharacterID();
    xOperate.uchOperate = pReq->uchOperate;
    xOperate.nRMBMoney  = pReq->nRMBMoney;
    xOperate.nGameMoney = pReq->nGameMoney;
    GettheServer().SendMsgToCenterServer( &xOperate );
}

void GamePlayer::OnCS2GSOperateMoneyAck( Msg* pMsg )
{
    CS2GSOperateMoneyAck* pAck = static_cast< CS2GSOperateMoneyAck* >( pMsg );
    if ( pAck == NULL )
    { return; }

    switch( pAck->uchOperate )
    {
    case ConsignmentDefine::Operate_TakeOut:
        {
            if ( pAck->nGameMoney != 0 )
            {
                OperateMoney( EOT_Add, pAck->nGameMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_Consignment );
            }

            if ( pAck->nRMBMoney != 0 )
            {
                //OperateJinDing( EOT_Add, pAck->nRMBMoney, __FUNCTION__, __LINE__ );
				OperateJinPiao( EOT_Add, pAck->nRMBMoney, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Consignment); //寄售取钱改成绑金 lrt 服务器只要改存取2处
            }
        }
        break;
    default:
        break;
    }

    SetPlayerConsignmentAccount( pAck->xAccount.GetRMBMoney(), pAck->xAccount.GetGameMoney() );
    m_bIsWaitProcess = false;
}

void GamePlayer::OnMsgConsignmentMoneyReq( Msg* pMsg )
{
    MsgConsignmentMoneyReq* pReq = static_cast< MsgConsignmentMoneyReq* >( pMsg );
    if ( pReq == NULL ||pReq->xConsignment.GetPrice() <= 0)
    { return; }

    pReq->xConsignment.SetSellPlayerID( GetDBCharacterID() );

    if ( CheckPlayerConsignmentProcessing() )
    {
        return SendOperateAckToClient< MsgConsignmentMoneyAck >( MsgConsignmentMoneyAck::ECD_WaitProcess );
    }

    if ( pReq->xConsignment.GetCount() < ConsignmentDefine::MinSellRMBCount )
    {
        return SendOperateAckToClient< MsgConsignmentMoneyAck >( MsgConsignmentMoneyAck::ECD_ConsignmentCountLimit );
    }

    unsigned int nCostValue = 0;
    switch ( pReq->xConsignment.GetType() )
    {
    case ConsignmentDefine::Consignment_SellRMB:
        {
            nCostValue = ConsignmentDefine::GetConsignmentCost( pReq->xConsignment.GetCount() );
            if ( pReq->xConsignment.GetCount() + nCostValue > m_nRMBMoney )
            {
                return SendOperateAckToClient< MsgConsignmentMoneyAck >( MsgConsignmentMoneyAck::ECD_NotEnoughjinDing );
            }
        }
        break;
    case ConsignmentDefine::Consignment_BuyRMB:
        {
            unsigned int nBuyValue = pReq->xConsignment.GetCount() * pReq->xConsignment.GetPrice();
            nCostValue = ConsignmentDefine::GetConsignmentCost( nBuyValue );
            if ( nBuyValue + nCostValue > m_nGameMoney )
            {
                return SendOperateAckToClient< MsgConsignmentMoneyAck >( MsgConsignmentMoneyAck::ECD_NotEnoughMoney );
            }
        }
        break;
    default:
        return;
    }

    if ( pReq->xConsignment.GetBuyPlayerID() != ConsignmentDefine::NoneID )
    {
        RelationDataToServer* pData = m_pRelation->GetRelationData( pReq->xConsignment.GetBuyPlayerID() );
        if ( pData == NULL || !pData->HaveRelation( RelationDefine::Friend ) )
        {
            return SendOperateAckToClient< MsgConsignmentMoneyAck >( MsgConsignmentMoneyAck::ECD_MustFriend );
        }
    }

    SetPlayerConsignmentProcessing();

  //  Log( "玩家[%s][%u]请求寄售[%d]操作 单价[%u]数量[%u], 发送给Center处理", 
		Log( theXmlString.GetString(eServerLog_JiShou), 
        GetCharName(), GetDBCharacterID(), pReq->xConsignment.GetType(), pReq->xConsignment.GetPrice(), pReq->xConsignment.GetCount() );

    // 通知CenterServer
    GS2CSConsignmentMoneyReq xReq;
    xReq.nPlayerID    = GetDBCharacterID();
    xReq.xConsignment = pReq->xConsignment;
    xReq.nCostValue   = nCostValue;
    GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::OnMsgConsignmentMoneyHistroy( Msg* pMsg )
{
    if ( CheckPlayerConsignmentProcessing() )
    {
        return SendOperateAckToClient< MsgConsignmentMoneyHistroyAck >( MsgConsignmentMoneyHistroyAck::ECD_WaitProcess );
    }

    SetPlayerConsignmentProcessing();

    GS2CSConsignmentMoneyHistroyReq xReq;
    xReq.nPlayerID = GetDBCharacterID();
    GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::OnMsgConsignmentOperateReq( Msg* pMsg )
{
    MsgConsignmentOperateReq* pReq = static_cast< MsgConsignmentOperateReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    if ( CheckPlayerConsignmentProcessing() )
    {
        return SendOperateAckToClient< MsgConsignmentOperateAck >( MsgConsignmentOperateAck::ECD_WaitProcess );
    }

    switch ( pReq->uchOperate )
    {
    case ConsignmentDefine::Operate_Buy:
        break;
    case ConsignmentDefine::Operate_Sell:
        break;
    case ConsignmentDefine::Operate_Cancel:
        break;
    default:
        return;
    }

    SetPlayerConsignmentProcessing();

    // 跳到CenterServer处理
    GS2CSConsignmentOperateReq xReq;
    xReq.nPlayerID          = GetDBCharacterID();
    xReq.uchOperate         = pReq->uchOperate;
    xReq.n64ConsignmentID   = pReq->n64ConsignmentID;
    xReq.uchConsignmentType = pReq->uchConsignmentType;
    GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::InitPlayerConsignment()
{
    m_nRMBMoney = 0;
    m_nGameMoney = 0;

    m_bIsWaitProcess = false;
    m_dwLastOperateTime = 0;
}

void GamePlayer::SetPlayerConsignmentProcessing()
{
    m_bIsWaitProcess = true;
    m_dwLastOperateTime = HQ_TimeGetTime();
}

bool GamePlayer::CheckPlayerConsignmentProcessing()
{
    if ( m_bIsWaitProcess )
    { return true; }

    if ( !GameTime::IsPassCurrentTime( m_dwLastOperateTime, ConsignmentDefine::OperateSpaceTime ) )
    { return true; }

    return false;
}

void GamePlayer::SetPlayerConsignmentAccount( uint32 nRMBMoney, uint32 nGameMoney )
{
    m_nRMBMoney  = nRMBMoney;
    m_nGameMoney = nGameMoney;

    MsgShowConsignmentAccount xShow;
    xShow.nRMBMoney  = m_nRMBMoney;
    xShow.nGameMoney = m_nGameMoney;
    SendMessageToClient( &xShow );
}

//void GamePlayer::OnMsgConsignmentItemReq(Msg* pMessage)
//{
//	MsgConsignmentItemReq* pReq = static_cast<MsgConsignmentItemReq*>(pMessage);
//	if ( pReq == NULL )
//	{ return; }
//
//	pReq->xConsignment.SetSellPlayerID( GetDBCharacterID() );
//
//	if ( CheckPlayerConsignmentProcessing() )
//	{
//		return SendOperateAckToClient< MsgConsignmentItemAck >( MsgConsignmentItemAck::ECD_WaitProcess );
//	}
//
//	/*if ( pReq->xConsignment.GetCount() < ConsignmentDefine::MinSellRMBCount )
//	{
//		return SendOperateAckToClient< MsgConsignmentMoneyAck >( MsgConsignmentMoneyAck::ECD_ConsignmentCountLimit );
//	}*/
//
//	unsigned int nCostValue = 0;
//	switch ( pReq->xConsignment.GetType() )
//	{
//	case ConsignmentDefine::Consignment_SellItem:
//		{
//			SCharItem* pSellItem = (SCharItem*)pReq->xConsignment.GetData();
//			if (GetItemCount(pSellItem->GetItemID()) < pReq->xConsignment.GetCount())
//			{
//				return SendOperateAckToClient< MsgConsignmentItemAck >( MsgConsignmentItemAck::ECD_NoEnoughItem );
//			}
//		}
//		break;
//	case ConsignmentDefine::Consignment_BuyItem:
//		{
//			unsigned int nBuyValue = pReq->xConsignment.GetCount() * pReq->xConsignment.GetPrice();
//			nCostValue = ConsignmentDefine::GetConsignmentCost( nBuyValue );
//			if ( nCostValue+nBuyValue > m_nGameMoney )
//			{
//				return SendOperateAckToClient< MsgConsignmentItemAck >( MsgConsignmentItemAck::ECD_NotEnoughMoney );
//			}
//		}
//		break;
//	default:
//		return;
//	}
//
//	if ( pReq->xConsignment.GetBuyPlayerID() != ConsignmentDefine::NoneID )
//	{
//		RelationDataToServer* pData = m_pRelation->GetRelationData( pReq->xConsignment.GetBuyPlayerID() );
//		if ( pData == NULL || !pData->HaveRelation( RelationDefine::Friend ) )
//		{
//			return SendOperateAckToClient< MsgConsignmentItemAck >( MsgConsignmentItemAck::ECD_MustFriend );
//		}
//	}
//
//	SetPlayerConsignmentProcessing();
//
//	Log( "玩家[%s][%u]请求寄售[%d]操作 单价[%u]数量[%u], 发送给Center处理", 
//		GetCharName(), GetDBCharacterID(), pReq->xConsignment.GetType(), pReq->xConsignment.GetPrice(), pReq->xConsignment.GetCount() );
//
//	// 通知CenterServer
//	GS2CSConsignmentItemReq xReq;
//	xReq.nPlayerID    = GetDBCharacterID();
//	xReq.xConsignment = pReq->xConsignment;
//	xReq.nCostValue   = nCostValue;
//	GettheServer().SendMsgToCenterServer( &xReq );
//}