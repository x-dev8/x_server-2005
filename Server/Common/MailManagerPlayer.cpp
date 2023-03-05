#include "MailManagerPlayer.h"
#include "GamePlayer.h"
#include "TimeEx.h"
#include "XmlStringLanguage.h"
#include "LogEventService.h"

MailPlayerManager::MailPlayerManager()
{
    _bHaveMailProcess = false;
}

void MailPlayerManager::BeginSendMail( MsgSendMailReq* pMessage )
{
    // 判断所有的邮件合理性
	// 附件的邮费
	int tailNeedMoney(0);
    MsgSendMailAck msgToClient; // 回馈给客户端消息
    msgToClient.timeStamp = pMessage->timeStamp;
    msgToClient.bagType   = pMessage->bagType;
    msgToClient.bagIndex  = pMessage->bagIndex;
    msgToClient.itemBigId = pMessage->itemBigId;

    if ( _bHaveMailProcess )
    {
        msgToClient.result = MsgSendMailAck::ER_MailProcessing;
        GettheServer().SendMsgToSingle( &msgToClient, pOwner );
        return ;
    }

    // 对Title和Content的检查
    HelperFunc::CheckStringValid( pMessage->title, sizeof(pMessage->title)); 
    HelperFunc::CheckStringValid( pMessage->content, sizeof(pMessage->content)); 
    if ( strlen(pMessage->title) == 0)
    { 
        msgToClient.result = MsgSendMailAck::ER_TileInvalid;
        GettheServer().SendMsgToSingle( &msgToClient, pOwner );
        return;
    }
		
	if( (pMessage->itemBigId || pMessage->money) && pOwner->IsInProtectLockTime() )
	{
		msgToClient.result = MsgSendMailAck::ER_InProtectLockTime;
		GettheServer().SendMsgToSingle( &msgToClient, pOwner );
		return;
	}

    if ( strlen(pMessage->content) == 0)
    { 
        msgToClient.result = MsgSendMailAck::ER_ContentInvalid;
        GettheServer().SendMsgToSingle( &msgToClient, pOwner );
        return;
    }

    // 检查关系
    GameRelation* pRelation = pOwner->GetRelation(); // 好友关系
    if ( NULL == pRelation)
    { // 没有关系的人不能发邮件(邮件只能发给和自己有关系的人)
        msgToClient.result = MsgSendMailAck::ER_TargetNotRelation;
        GettheServer().SendMsgToSingle( &msgToClient, pOwner );
        return;
    }

    // 检查目标合法性
    for ( int i=0; i<EM_TargetMaxCount; ++i )
    {
        SMail::SAddress& address = pMessage->targets[i];
        if ( i == 0 )
        { // 必须要有To第一目标
            if ( InvalidLogicNumber == address.charDbId  )
            {
                msgToClient.result = MsgSendMailAck::ER_AddressError;
                GettheServer().SendMsgToSingle( &msgToClient, pOwner );
                return;
            }
        }
        else
        { // 抄送的人
            if ( 0 == address.charDbId )
            { break;} // 没有要抄送的人无就跳出
			tailNeedMoney += enumSendTextMail_NeedMoney;
        }

        // 检查目标的关系性
        if ( !pRelation->HaveRelation( address.charDbId, RelationDefine::Friend ) )
        {
            msgToClient.result = MsgSendMailAck::ER_TargetNotRelation;
            GettheServer().SendMsgToSingle( &msgToClient, pOwner );
            return;
        }

        // 纠正客户端发过来的名字,可能会有人改协议导致没有结束符
        HelperFunc::CheckStringValid( address.addressName, sizeof(address.addressName));    

        GameRelation* pTargetRelation = theGameRelationManager.GetPlayerRelation( address.charDbId );
        if ( pTargetRelation == NULL || _stricmp( pTargetRelation->GetName(), address.addressName ) != 0 )
        { // 名字无效
            msgToClient.result = MsgSendMailAck::ER_TargetNameInvalid;
            GettheServer().SendMsgToSingle( &msgToClient, pOwner );
            return;
        }
    }

    bool bHaveItem = false;
    // 检查钱
    if ( pMessage->money != 0 )
    {
		if(
			pOwner->GetJiaoZiMoney() < enumSendOtherMail_NeedMoney + tailNeedMoney
			|| pMessage->money > pOwner->GetMoney()
			)
		{
			msgToClient.result = MsgSendMailAck::ER_MoneyNotEnough;
            GettheServer().SendMsgToSingle( &msgToClient, pOwner );
            return;
		}

   //     if ( pOwner->GetMoney() < enumSendOtherMail_NeedMoney + tailNeedMoney
			//|| pMessage->money > pOwner->GetMoney() - enumSendOtherMail_NeedMoney - tailNeedMoney)
   //     { // 是否够钱 
   //         msgToClient.result = MsgSendMailAck::ER_MoneyNotEnough;
   //         GettheServer().SendMsgToSingle( &msgToClient, pOwner );
   //         return;
   //     }

        if ( pMessage->money > EM_MoneySendMax)
        { // 是否超出邮寄的最大值
            msgToClient.result = MsgSendMailAck::ER_MoneyTooMuch;
            GettheServer().SendMsgToSingle( &msgToClient, pOwner );
            return;
        }

        bHaveItem = true;
    }

    // 检查附件
    if ( pMessage->itemBigId != 0 )
    {
		//检测手续费是不是足够
		if(pOwner->GetJiaoZiMoney() < enumSendOtherMail_NeedMoney + tailNeedMoney)
		{
			msgToClient.result = MsgSendMailAck::ER_MoneyNotEnough;
			GettheServer().SendMsgToSingle( &msgToClient, pOwner );
			return;
		}

		/*if(pOwner->GetMoney() < enumSendOtherMail_NeedMoney + tailNeedMoney)
		{
			msgToClient.result = MsgSendMailAck::ER_MoneyNotEnough;
			GettheServer().SendMsgToSingle( &msgToClient, pOwner );
			return;
		}*/
		// 有附件
        bool bCheckPass = false;
        ItemBag* pItemBag = NULL;
        switch ( pMessage->bagType )
        {
        case BT_NormalItemBag:
            { pItemBag = &pOwner->_NormalItemBag; }
            break;
        case BT_MaterialBag:
            { pItemBag = &pOwner->_MaterialItemBag; }
            break;
        }

        switch ( pMessage->bagType )
        {
        case BT_NormalItemBag:
        case BT_MaterialBag:
            {
                SCharItem* pCharItem = pItemBag->GetItemByIndex( pMessage->bagIndex );
                if ( NULL == pCharItem || pCharItem->itembaseinfo.nOnlyInt != pMessage->itemBigId )
                { break; } // 物品数据不存在

                // 锁定
                if( pCharItem->IsLock() || pCharItem->IsBounded() )
                { break; }

                ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
                if ( NULL == pItemCommon)
                { break; } // 物品数据配置不存在

                if ( !pItemCommon->bIsCanTrade )
                { break; }

                bCheckPass = true;
            }
            break;
        case BT_MountBag:
            {
                //int iIndex = pOwner->_mountManager.GetMountIndexByGuid( pMessage->itemBigId );
                //if ( -1 == iIndex )
                //{ break; }

                //if ( iIndex == pOwner->_mountManager.GetActiveMountIndex())
                //{ break; }

                //SMountItem* pMountItem = pOwner->_mountManager.GetMountByIndex( iIndex );
                //if ( pMountItem == NULL || pMountItem->IsLock() )
                //{ break; }      // 加锁的马不能邮寄

                //bCheckPass = true;
            }
            break;
        case BT_PetBag:
            {
                int iIndex = pOwner->_petManager.GetPetIndexByGuid( pMessage->itemBigId );
                if ( -1 == iIndex )
                { break; }

                if ( iIndex == pOwner->_petManager.GetActivePetIndex())
                { break; }

                SPetItem* pPetItem = pOwner->_petManager.GetPetByIndex( iIndex );
                if ( pPetItem == NULL || pPetItem->IsLock() )
                { break; }      // 加锁的宠物不能邮寄

                bCheckPass = true;
            }
            break;
        default:
            break;
        }

        if ( !bCheckPass )
        {
            msgToClient.result = MsgSendMailAck::ER_AccessoryInvalid;
            GettheServer().SendMsgToSingle( &msgToClient, pOwner );
            return;
        }

        bHaveItem = true;
    }
	//文本邮件
	if(pMessage->itemBigId == 0 && pMessage->money == 0 )
	{
		if(pOwner->GetJiaoZiMoney() < enumSendTextMail_NeedMoney + tailNeedMoney)
		{
			msgToClient.result = MsgSendMailAck::ER_MoneyNotEnough;
			GettheServer().SendMsgToSingle( &msgToClient, pOwner );
			return;
		}

		/*if(pOwner->GetMoney() < enumSendTextMail_NeedMoney + tailNeedMoney)
		{
			msgToClient.result = MsgSendMailAck::ER_MoneyNotEnough;
			GettheServer().SendMsgToSingle( &msgToClient, pOwner );
			return;
		}*/
	}
    
    // 缓存数据
    memcpy_s( &_cacheMail, sizeof(_cacheMail), pMessage, sizeof(_cacheMail));
    
    // 查询目标的有效性
    GS2CSQueryMailCanSendReq msgToCenter;
    msgToCenter.charDbId     = pOwner->GetDBCharacterID();
    msgToCenter.isHaveItem = bHaveItem ? 1 : 0;
    memcpy_s( msgToCenter.targets, sizeof(msgToCenter.targets), pMessage->targets, sizeof(msgToCenter.targets) );
    GettheServer().SendMsgToCenterServer( &msgToCenter );

    // 开始处理发信
    _bHaveMailProcess = true;
}

void MailPlayerManager::SendValidMailToCS()
{
	//发送邮件扣除的手续费
	int systemSubMoney(0);
    GS2CSSendMailReq msg; // 投递给CenterServer
    msg.accountId = pOwner->GetAccountID();
    msg.charDbId  = pOwner->GetDBCharacterID();

    MsgSendMailAck msgToClient; // 回馈给客户端消息
    msgToClient.timeStamp = _cacheMail.timeStamp;
    msgToClient.bagType   = _cacheMail.bagType;
    msgToClient.bagIndex  = _cacheMail.bagIndex;
    msgToClient.itemBigId = _cacheMail.itemBigId;

   

    // 检查目标合法性
    for ( int i=0; i<EM_TargetMaxCount; ++i )
    {
        SMail::SAddress& address = _cacheMail.targets[i];

        if ( address.charDbId == 0)
        { break; }
		if(i > 0)
		{
			systemSubMoney += enumSendTextMail_NeedMoney;
		}
        memcpy_s( &msg.mail.owners[EM_ToIndex+i], sizeof(SMail::SAddress), &address, sizeof(SMail::SAddress) );
    }
	if( _cacheMail.money != 0 || _cacheMail.itemBigId != 0)
	{
		systemSubMoney += enumSendOtherMail_NeedMoney;
	}
	else
	{
		systemSubMoney += enumSendTextMail_NeedMoney;
	}

	// 检查钱
	if ( _cacheMail.money != 0 )
	{
		if ( pOwner->GetJiaoZiMoney() < systemSubMoney || _cacheMail.money > pOwner->GetMoney())
		{ // 是否够钱 
			msgToClient.result = MsgSendMailAck::ER_MoneyNotEnough;
			GettheServer().SendMsgToSingle( &msgToClient, pOwner );
			return;
		}

		//if ( pOwner->GetMoney() < systemSubMoney || _cacheMail.money > pOwner->GetMoney() - systemSubMoney)
		//{ // 是否够钱 
		//	msgToClient.result = MsgSendMailAck::ER_MoneyNotEnough;
		//	GettheServer().SendMsgToSingle( &msgToClient, pOwner );
		//	return;
		//}

		if ( _cacheMail.money > EM_MoneySendMax)
		{ // 是否超出邮寄的最大值
			msgToClient.result = MsgSendMailAck::ER_MoneyTooMuch;
			GettheServer().SendMsgToSingle( &msgToClient, pOwner );
			return;
		}
	}

    // 目标
    msg.mail.owners[EM_FromIndex].charDbId = pOwner->GetDBCharacterID();
    strncpy_s( msg.mail.owners[EM_FromIndex].addressName, EM_AddressNameSize, pOwner->GetCharName(), EM_AddressNameSize - 1);

    // 检查附件
	unsigned short ItemID = 0;
		int64 ItemGUID = 0;
		int   ItemCnt = 0;
    if ( _cacheMail.itemBigId != 0 )
    { 
		if(pOwner->GetJiaoZiMoney() < systemSubMoney)
		{
			msgToClient.result = MsgSendMailAck::ER_MoneyNotEnough;
			GettheServer().SendMsgToSingle( &msgToClient, pOwner );
			return;
		}
		/*if(pOwner->GetMoney() < systemSubMoney)
		{
			msgToClient.result = MsgSendMailAck::ER_MoneyNotEnough;
			GettheServer().SendMsgToSingle( &msgToClient, pOwner );
			return;
		}*/
		// 有附件
        bool bCheckPass = false;
        ItemBag* pItemBag = NULL;
        switch ( _cacheMail.bagType )
        {
        case BT_NormalItemBag:
            { pItemBag = &pOwner->_NormalItemBag; }
            break;
        case BT_MaterialBag:
            { pItemBag = &pOwner->_MaterialItemBag; }
            break;
        }

        switch ( _cacheMail.bagType )
        {
        case BT_NormalItemBag:
        case BT_MaterialBag:
            {
                SCharItem* pCharItem = pItemBag->GetItemByIndex( _cacheMail.bagIndex );
                if ( NULL == pCharItem || pCharItem->itembaseinfo.nOnlyInt != _cacheMail.itemBigId )
                { break; } // 物品数据不存在

                ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
                if ( NULL == pItemCommon)
                { break; } // 物品数据配置不存在

                // 给发给CenterServer的协议赋值
                msg.mail.accessory.type = SMail::EAT_Item;
                memcpy_s( msg.mail.accessory.content, sizeof(msg.mail.accessory.content), pCharItem, sizeof(SCharItem) );

                uint16 itemCount = pCharItem->itembaseinfo.ustItemCount;
                // 扣物品
				ItemID = pCharItem->GetItemID();
				ItemGUID = pCharItem->GetItemGuid();
				ItemCnt = itemCount;
				//LYH日志添加
				ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(ItemID);
				if(_pitem)
				theLogEventService.LogItemConsume(pOwner->GetAccountID(),pOwner->GetDBCharacterID(),ItemID,ItemCnt,ItemGUID,
				0,eItemLogInfo_ItemConsume_Mail,pOwner->GetCharName(),_pitem->GetItemName());
                if ( pItemBag->PopItem( _cacheMail.bagIndex, itemCount) != ierr_Success )
                { break; }

                bCheckPass = true;
            }
            break;
        case BT_MountBag:
            {
                SMountItem* pMountItem = pOwner->_mountManager.GetMountByGuid( _cacheMail.itemBigId );
                if ( NULL == pMountItem )
                { break; } // 坐骑数据不存在

                // 给发给CenterServer的协议赋值
                msg.mail.accessory.type = SMail::EAT_Mount;
                memcpy_s( msg.mail.accessory.content, sizeof(msg.mail.accessory.content), pMountItem, sizeof(SMountItem) );

                // 扣马
				ItemID = pMountItem->GetMountID();
				ItemGUID = pMountItem->GetMountGuid();
				ItemCnt = 1;
				//LYH日志添加
				ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(ItemID);
				if(_pitem)
				theLogEventService.LogItemConsume(pOwner->GetAccountID(),pOwner->GetDBCharacterID(),ItemID,ItemCnt,ItemGUID,
				0,eItemLogInfo_ItemConsume_Mail,pOwner->GetCharName(),_pitem->GetItemName());
                bool bActiveIndex = false;
                if ( ER_Success != pOwner->_mountManager.PopMountByBigId( _cacheMail.itemBigId, bActiveIndex ))
                { break; }

                if ( bActiveIndex )
                { // 重新算马属性
                }

                bCheckPass = true;
            }
            break;
        case BT_PetBag:
            {
                SPetItem* pPetItem = pOwner->_petManager.GetPetByGuid( _cacheMail.itemBigId );
                if ( NULL == pPetItem )
                { break; } // 宠物数据不存在

                // 给发给CenterServer的协议赋值
                msg.mail.accessory.type = SMail::EAT_Pet;
                memcpy_s( msg.mail.accessory.content, sizeof(msg.mail.accessory.content), pPetItem, sizeof(SPetItem) );

                // 扣宠物
                bool bActiveIndex = false;
                if ( ER_Success != pOwner->_petManager.PopPetByBigId( _cacheMail.itemBigId, bActiveIndex ))
                { break; }

                if ( bActiveIndex )
                { // 重新算属性
                }

                bCheckPass = true;
            }
            break;
        default:
            break;
        }

        if ( !bCheckPass )
        {
            msgToClient.result = MsgSendMailAck::ER_AccessoryInvalid;
            GettheServer().SendMsgToSingle( &msgToClient, pOwner );
            return;
        }
    }

    // 扣钱 
    if ( _cacheMail.money != 0 )
    { pOwner->OperateMoney( EOT_Sub, _cacheMail.money, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_MailCache ); }
	//扣手续费
	pOwner->OperateJiaoZi( EOT_Sub, systemSubMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_SendMail );

    msg.mail.type  = SMail::EMT_Player;
    msg.mail.state = SMail::EMS_NotOpen;
    msg.mail.money = _cacheMail.money;
    // 赋值发信人位置
    msg.mail.owners[EM_FromIndex].charDbId = pOwner->GetDBCharacterID();
    strncpy_s( msg.mail.owners[EM_FromIndex].addressName, EM_AddressNameSize, pOwner->GetCharName(), EM_AddressNameSize - 1);
    strncpy_s( msg.mail.title,   sizeof(msg.mail.title),   _cacheMail.title,   sizeof(msg.mail.title) - 1   );
    strncpy_s( msg.mail.content, sizeof(msg.mail.content), _cacheMail.content, sizeof(msg.mail.content) - 1 );    
    msg.mail.sendTime = TimeEx::GetNowTime();        
    GettheServer().SendMsgToCenterServer( &msg );

    //pOwner->Log("发邮件 title[%s] money[%u] accessory[%u:%I64u]", msg.mail.title, msg.mail.money, msg.mail.accessory.type, _cacheMail.itemBigId );
	//LYH日志添加 邮件
//     ItemDefine::SItemCommon *pCommon = GettheItemDetail().GetItemByID(ItemID);
// 	if(pCommon)
// 	{
// 		if(theLogEventService.LogMail(pOwner->GetAccountID(),pOwner->GetDBCharacterID(),msg.mail.owners[EM_ToIndex].charDbId,msg.mail.title,msg.mail.content,
// 			ItemID,ItemCnt,msg.mail.money,ItemGUID,pOwner->GetCharName(),msg.mail.owners[EM_ToIndex].addressName,pCommon->GetItemName()))
// 		{
// 			pOwner->Log(theXmlString.GetString(eServerLog_SendMail), msg.mail.title, msg.mail.money, msg.mail.accessory.type, _cacheMail.itemBigId );
// 		}
// 	}else
// 	{
// 		if(theLogEventService.LogMail(pOwner->GetAccountID(),pOwner->GetDBCharacterID(),msg.mail.owners[EM_ToIndex].charDbId,msg.mail.title,msg.mail.content,
// 			ItemID,ItemCnt,msg.mail.money,ItemGUID,pOwner->GetCharName(),msg.mail.owners[EM_ToIndex].addressName,"NULL"))
// 		{
// 			pOwner->Log(theXmlString.GetString(eServerLog_SendMail), msg.mail.title, msg.mail.money, msg.mail.accessory.type, _cacheMail.itemBigId );
// 		}
// 	}


    msgToClient.result       = ER_Success;
    msgToClient.timeStamp    = _cacheMail.timeStamp;
    msgToClient.currentMoney = pOwner->GetMoney();
    msgToClient.bagType      = _cacheMail.bagType;
    msgToClient.bagIndex     = _cacheMail.bagIndex;
    msgToClient.itemBigId    = _cacheMail.itemBigId;
    GettheServer().SendMsgToSingle( &msgToClient, pOwner );
    return;
}

void MailPlayerManager::SendInValidMailToClient( CS2GSQueryMailCanSendAck* pMessage )
{
    MsgSendMailAck msgToClient; // 回馈给客户端消息
    msgToClient.result    = pMessage->result;
    msgToClient.timeStamp = _cacheMail.timeStamp;
    msgToClient.bagType   = _cacheMail.bagType;
    msgToClient.bagIndex  = _cacheMail.bagIndex;
    msgToClient.itemBigId = _cacheMail.itemBigId;
    GettheServer().SendMsgToSingle( &msgToClient, pOwner );
}

void MailPlayerManager::EndSendValidMail()
{
    if ( _bHaveMailProcess )
    { _bHaveMailProcess = false; }

    return;
}
