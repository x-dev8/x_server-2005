#include "MailManagerMain.h"
#include "MySqlCommunication.h"
#include "GameServerManager.h"
#include "LogEventService.h"
MailSystemManager& MailSystemManager::Instance()
{
    static MailSystemManager mailManager;
    return mailManager;
}

MailSystemManager::MailSystemManager()
{

}

MailSystemManager::~MailSystemManager()
{

}

void MailSystemManager::OnGS2CSMailListReq( GS2CSMailListReq* pMessage, uint32 serverId )
{
    theMysqlCommunication.PushReqMessage( pMessage, 0 ); // 在数据库中操作
}

void MailSystemManager::OnCS2GSMailListAck( CS2GSMailListAck* pMessage )
{
    theGameServerManager.SendMsgToSingle( pMessage, pMessage->charDbId );
}

void MailSystemManager::OnGS2CSQueryMailCanSendReq( GS2CSQueryMailCanSendReq* pMessage, uint32 serverId )
{
    theMysqlCommunication.PushReqMessage( pMessage, 0 ); // 在数据库中操作
}

void MailSystemManager::OnCS2GSQueryMailCanSendAck( CS2GSQueryMailCanSendAck* pMessage )
{
    theGameServerManager.SendMsgToSingle( pMessage, pMessage->charDbId );
}

void MailSystemManager::OnGS2CSSendMailReq( GS2CSSendMailReq* pMessage, uint32 serverId )
{
	//在此写log 包含玩家和系统的所有信息
	uint16  ustItemID = 0;
	uint16  ustItemCnt= 0;
	__int64 nOnlyInt  = 0;
	char    szName[ dr_MaxPlayerName ] ="通过ID查找"; 

	switch ( pMessage->mail.accessory.type )
	{
	//case SMail::EAT_None:
	case SMail::EAT_Item:
		{
			SCharItem* pCharItem = (SCharItem*)pMessage->mail.accessory.content;
			ustItemID = pCharItem->GetItemID();
			nOnlyInt  = pCharItem->GetItemGuid();
			ustItemCnt= pCharItem->GetItemCount();
		}
		break;
	case SMail::EAT_Mount:
		{
			SMountItem* pMountItem = (SMountItem*)pMessage->mail.accessory.content;
			ustItemID = pMountItem->GetMountID();
			nOnlyInt  = pMountItem->GetMountGuid();
			ustItemCnt= 1;
			//strncpy_s( szName, sizeof( szName ), pMountItem->GetMountName(), sizeof( szName ) - 1 );
		}
		break;
	case SMail::EAT_Pet:
		{
			SPetItem* pPetItem = (SPetItem*)pMessage->mail.accessory.content;
			ustItemID = pPetItem->baseInfo.itemId;
			nOnlyInt  = pPetItem->GetPetGuid();
			ustItemCnt= 1;
			//strncpy_s( szName, sizeof( szName ), pPetItem->GetPetName(), sizeof( szName ) - 1 );
		}
		break;
	}
	theLogEventService.LogMail(pMessage->accountId,pMessage->charDbId,
		pMessage->mail.owners[EM_ToIndex].charDbId,pMessage->mail.title,pMessage->mail.content,
		ustItemID,ustItemCnt,pMessage->mail.money,nOnlyInt,(char*)pMessage->mail.owners[EM_FromIndex].addressName,
		(char*)pMessage->mail.owners[EM_ToIndex].addressName,szName);

    theMysqlCommunication.PushReqMessage( pMessage, 0 ); // 在数据库中操作
}

void MailSystemManager::OnCS2GSSendMailAck( CS2GSSendMailAck* pMessage )
{
    if ( pMessage->result == ER_Success)
    { // 通知收信人有邮件
        MsgNotifyMail msg;
        strncpy_s( msg.fromAddressName, sizeof(msg.fromAddressName), pMessage->mail.owners[EM_FromIndex].addressName, sizeof(msg.fromAddressName) - 1);
        for ( int i=EM_ToIndex; i<EM_OwnerMaxCount; ++i )
        {   
            uint32 charDbId = pMessage->mail.owners[i].charDbId;
            if ( charDbId == 0 )
            { break; }

            theGameServerManager.SendMsgToSingleRemote( InvalidLogicNumber, &msg, charDbId, "", true );
        }
    }
    else
    {
        switch ( pMessage->mail.accessory.type )
        {
        case SMail::EAT_None:
            {
                LOG_MESSAGE( MAILOBJECT, LOG_PRIORITY_INFO, "account[%u:%u:%s] 添加邮件[%s] 金[%u] 失败 r[%u]", 
                    pMessage->accountId, pMessage->mail.owners[EM_FromIndex].charDbId, pMessage->mail.owners[EM_FromIndex].addressName, pMessage->mail.title,pMessage->mail.money, pMessage->result );
            }
            break;
        case SMail::EAT_Item:
            {
                SCharItem* pCharItem = (SCharItem*)pMessage->mail.accessory.content;
                LOG_MESSAGE( MAILOBJECT, LOG_PRIORITY_INFO, "account[%u:%u:%s] 添加邮件[%s] 金[%u] 物品[%I64u] 失败 r[%u]", 
                    pMessage->accountId, pMessage->mail.owners[EM_FromIndex].charDbId, pMessage->mail.owners[EM_FromIndex].addressName, pMessage->mail.title,pMessage->mail.money, pCharItem->itembaseinfo.nOnlyInt, pMessage->result );
            }
            break;
        case SMail::EAT_Mount:
            {
                SMountItem* pMountItem = (SMountItem*)pMessage->mail.accessory.content;
                LOG_MESSAGE( MAILOBJECT, LOG_PRIORITY_INFO, "account[%u:%u:%s] 添加邮件[%s] 金[%u] 马[%I64u] 失败 r[%u]", 
                    pMessage->accountId, pMessage->mail.owners[EM_FromIndex].charDbId, pMessage->mail.owners[EM_FromIndex].addressName, pMessage->mail.title,pMessage->mail.money, pMountItem->baseInfo.guid, pMessage->result );
            }
            break;
        case SMail::EAT_Pet:
            {
                SPetItem* pPetItem = (SPetItem*)pMessage->mail.accessory.content;
                LOG_MESSAGE( MAILOBJECT, LOG_PRIORITY_INFO, "account[%u:%u:%s] 添加邮件[%s] 金[%u] 宠物[%I64u] 失败 r[%u]", 
                    pMessage->accountId, pMessage->mail.owners[EM_FromIndex].charDbId, pMessage->mail.owners[EM_FromIndex].addressName, pMessage->mail.title,pMessage->mail.money, pPetItem->baseInfo.guid, pMessage->result );
            }
            break;
        }

        theGameServerManager.SendMsgToSingle( pMessage, pMessage->charDbId );
    }
}

void MailSystemManager::OnGS2CSOpMailReq( GS2CSOpMailReq* pMessage, uint32 serverId )
{
    theMysqlCommunication.PushReqMessage( pMessage, 0 ); // 在数据库中操作
}

void MailSystemManager::OnCS2GSOpMailAck( CS2GSOpMailAck* pMessage )
{
    theGameServerManager.SendMsgToSingle( pMessage, pMessage->charDbId );
}
