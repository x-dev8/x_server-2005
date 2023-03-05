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
    // �ж����е��ʼ�������
	// �������ʷ�
	int tailNeedMoney(0);
    MsgSendMailAck msgToClient; // �������ͻ�����Ϣ
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

    // ��Title��Content�ļ��
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

    // ����ϵ
    GameRelation* pRelation = pOwner->GetRelation(); // ���ѹ�ϵ
    if ( NULL == pRelation)
    { // û�й�ϵ���˲��ܷ��ʼ�(�ʼ�ֻ�ܷ������Լ��й�ϵ����)
        msgToClient.result = MsgSendMailAck::ER_TargetNotRelation;
        GettheServer().SendMsgToSingle( &msgToClient, pOwner );
        return;
    }

    // ���Ŀ��Ϸ���
    for ( int i=0; i<EM_TargetMaxCount; ++i )
    {
        SMail::SAddress& address = pMessage->targets[i];
        if ( i == 0 )
        { // ����Ҫ��To��һĿ��
            if ( InvalidLogicNumber == address.charDbId  )
            {
                msgToClient.result = MsgSendMailAck::ER_AddressError;
                GettheServer().SendMsgToSingle( &msgToClient, pOwner );
                return;
            }
        }
        else
        { // ���͵���
            if ( 0 == address.charDbId )
            { break;} // û��Ҫ���͵����޾�����
			tailNeedMoney += enumSendTextMail_NeedMoney;
        }

        // ���Ŀ��Ĺ�ϵ��
        if ( !pRelation->HaveRelation( address.charDbId, RelationDefine::Friend ) )
        {
            msgToClient.result = MsgSendMailAck::ER_TargetNotRelation;
            GettheServer().SendMsgToSingle( &msgToClient, pOwner );
            return;
        }

        // �����ͻ��˷�����������,���ܻ����˸�Э�鵼��û�н�����
        HelperFunc::CheckStringValid( address.addressName, sizeof(address.addressName));    

        GameRelation* pTargetRelation = theGameRelationManager.GetPlayerRelation( address.charDbId );
        if ( pTargetRelation == NULL || _stricmp( pTargetRelation->GetName(), address.addressName ) != 0 )
        { // ������Ч
            msgToClient.result = MsgSendMailAck::ER_TargetNameInvalid;
            GettheServer().SendMsgToSingle( &msgToClient, pOwner );
            return;
        }
    }

    bool bHaveItem = false;
    // ���Ǯ
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
   //     { // �Ƿ�Ǯ 
   //         msgToClient.result = MsgSendMailAck::ER_MoneyNotEnough;
   //         GettheServer().SendMsgToSingle( &msgToClient, pOwner );
   //         return;
   //     }

        if ( pMessage->money > EM_MoneySendMax)
        { // �Ƿ񳬳��ʼĵ����ֵ
            msgToClient.result = MsgSendMailAck::ER_MoneyTooMuch;
            GettheServer().SendMsgToSingle( &msgToClient, pOwner );
            return;
        }

        bHaveItem = true;
    }

    // ��鸽��
    if ( pMessage->itemBigId != 0 )
    {
		//����������ǲ����㹻
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
		// �и���
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
                { break; } // ��Ʒ���ݲ�����

                // ����
                if( pCharItem->IsLock() || pCharItem->IsBounded() )
                { break; }

                ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
                if ( NULL == pItemCommon)
                { break; } // ��Ʒ�������ò�����

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
                //{ break; }      // �����������ʼ�

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
                { break; }      // �����ĳ��ﲻ���ʼ�

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
	//�ı��ʼ�
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
    
    // ��������
    memcpy_s( &_cacheMail, sizeof(_cacheMail), pMessage, sizeof(_cacheMail));
    
    // ��ѯĿ�����Ч��
    GS2CSQueryMailCanSendReq msgToCenter;
    msgToCenter.charDbId     = pOwner->GetDBCharacterID();
    msgToCenter.isHaveItem = bHaveItem ? 1 : 0;
    memcpy_s( msgToCenter.targets, sizeof(msgToCenter.targets), pMessage->targets, sizeof(msgToCenter.targets) );
    GettheServer().SendMsgToCenterServer( &msgToCenter );

    // ��ʼ������
    _bHaveMailProcess = true;
}

void MailPlayerManager::SendValidMailToCS()
{
	//�����ʼ��۳���������
	int systemSubMoney(0);
    GS2CSSendMailReq msg; // Ͷ�ݸ�CenterServer
    msg.accountId = pOwner->GetAccountID();
    msg.charDbId  = pOwner->GetDBCharacterID();

    MsgSendMailAck msgToClient; // �������ͻ�����Ϣ
    msgToClient.timeStamp = _cacheMail.timeStamp;
    msgToClient.bagType   = _cacheMail.bagType;
    msgToClient.bagIndex  = _cacheMail.bagIndex;
    msgToClient.itemBigId = _cacheMail.itemBigId;

   

    // ���Ŀ��Ϸ���
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

	// ���Ǯ
	if ( _cacheMail.money != 0 )
	{
		if ( pOwner->GetJiaoZiMoney() < systemSubMoney || _cacheMail.money > pOwner->GetMoney())
		{ // �Ƿ�Ǯ 
			msgToClient.result = MsgSendMailAck::ER_MoneyNotEnough;
			GettheServer().SendMsgToSingle( &msgToClient, pOwner );
			return;
		}

		//if ( pOwner->GetMoney() < systemSubMoney || _cacheMail.money > pOwner->GetMoney() - systemSubMoney)
		//{ // �Ƿ�Ǯ 
		//	msgToClient.result = MsgSendMailAck::ER_MoneyNotEnough;
		//	GettheServer().SendMsgToSingle( &msgToClient, pOwner );
		//	return;
		//}

		if ( _cacheMail.money > EM_MoneySendMax)
		{ // �Ƿ񳬳��ʼĵ����ֵ
			msgToClient.result = MsgSendMailAck::ER_MoneyTooMuch;
			GettheServer().SendMsgToSingle( &msgToClient, pOwner );
			return;
		}
	}

    // Ŀ��
    msg.mail.owners[EM_FromIndex].charDbId = pOwner->GetDBCharacterID();
    strncpy_s( msg.mail.owners[EM_FromIndex].addressName, EM_AddressNameSize, pOwner->GetCharName(), EM_AddressNameSize - 1);

    // ��鸽��
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
		// �и���
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
                { break; } // ��Ʒ���ݲ�����

                ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
                if ( NULL == pItemCommon)
                { break; } // ��Ʒ�������ò�����

                // ������CenterServer��Э�鸳ֵ
                msg.mail.accessory.type = SMail::EAT_Item;
                memcpy_s( msg.mail.accessory.content, sizeof(msg.mail.accessory.content), pCharItem, sizeof(SCharItem) );

                uint16 itemCount = pCharItem->itembaseinfo.ustItemCount;
                // ����Ʒ
				ItemID = pCharItem->GetItemID();
				ItemGUID = pCharItem->GetItemGuid();
				ItemCnt = itemCount;
				//LYH��־���
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
                { break; } // �������ݲ�����

                // ������CenterServer��Э�鸳ֵ
                msg.mail.accessory.type = SMail::EAT_Mount;
                memcpy_s( msg.mail.accessory.content, sizeof(msg.mail.accessory.content), pMountItem, sizeof(SMountItem) );

                // ����
				ItemID = pMountItem->GetMountID();
				ItemGUID = pMountItem->GetMountGuid();
				ItemCnt = 1;
				//LYH��־���
				ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(ItemID);
				if(_pitem)
				theLogEventService.LogItemConsume(pOwner->GetAccountID(),pOwner->GetDBCharacterID(),ItemID,ItemCnt,ItemGUID,
				0,eItemLogInfo_ItemConsume_Mail,pOwner->GetCharName(),_pitem->GetItemName());
                bool bActiveIndex = false;
                if ( ER_Success != pOwner->_mountManager.PopMountByBigId( _cacheMail.itemBigId, bActiveIndex ))
                { break; }

                if ( bActiveIndex )
                { // ������������
                }

                bCheckPass = true;
            }
            break;
        case BT_PetBag:
            {
                SPetItem* pPetItem = pOwner->_petManager.GetPetByGuid( _cacheMail.itemBigId );
                if ( NULL == pPetItem )
                { break; } // �������ݲ�����

                // ������CenterServer��Э�鸳ֵ
                msg.mail.accessory.type = SMail::EAT_Pet;
                memcpy_s( msg.mail.accessory.content, sizeof(msg.mail.accessory.content), pPetItem, sizeof(SPetItem) );

                // �۳���
                bool bActiveIndex = false;
                if ( ER_Success != pOwner->_petManager.PopPetByBigId( _cacheMail.itemBigId, bActiveIndex ))
                { break; }

                if ( bActiveIndex )
                { // ����������
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

    // ��Ǯ 
    if ( _cacheMail.money != 0 )
    { pOwner->OperateMoney( EOT_Sub, _cacheMail.money, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_MailCache ); }
	//��������
	pOwner->OperateJiaoZi( EOT_Sub, systemSubMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_SendMail );

    msg.mail.type  = SMail::EMT_Player;
    msg.mail.state = SMail::EMS_NotOpen;
    msg.mail.money = _cacheMail.money;
    // ��ֵ������λ��
    msg.mail.owners[EM_FromIndex].charDbId = pOwner->GetDBCharacterID();
    strncpy_s( msg.mail.owners[EM_FromIndex].addressName, EM_AddressNameSize, pOwner->GetCharName(), EM_AddressNameSize - 1);
    strncpy_s( msg.mail.title,   sizeof(msg.mail.title),   _cacheMail.title,   sizeof(msg.mail.title) - 1   );
    strncpy_s( msg.mail.content, sizeof(msg.mail.content), _cacheMail.content, sizeof(msg.mail.content) - 1 );    
    msg.mail.sendTime = TimeEx::GetNowTime();        
    GettheServer().SendMsgToCenterServer( &msg );

    //pOwner->Log("���ʼ� title[%s] money[%u] accessory[%u:%I64u]", msg.mail.title, msg.mail.money, msg.mail.accessory.type, _cacheMail.itemBigId );
	//LYH��־��� �ʼ�
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
    MsgSendMailAck msgToClient; // �������ͻ�����Ϣ
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
