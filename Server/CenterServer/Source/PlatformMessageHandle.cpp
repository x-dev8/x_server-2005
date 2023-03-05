#include "CenterServer.h"
#include "GameServerManager.h"
#include "DataCenter.h"
#include "AvatarSystemSetting.h"
#include "ProcessCharInfo.h"
#include "TimeEx.h"
#include "ServerStatusManager.h"
#include "ExpStage.h"
#include "MySqlCommunication.h"
#include "TradeCenterInfo.h"
#include "ConsoleApplication.h"
#include "CharacterAttributeConfig.h"
#include "GuildManager.h"
#include "CountryManager.h"
#include "FamilyManager.h"
#include "CenterFamily.h"
#include "CountryConfig.h"
#include "MailManagerMain.h"
#include "XmlStringLanguage.h"
#include "QuestEntrust.h"
//void CenterServer::HandleAddPoint( uint32 clientId, Msg* pMsg )
//{
//    MsgPFAddPoints* pMessage = (MsgPFAddPoints*)pMsg;
//    CS2DBAccountPoints msg;
//    msg.identifyId2 = clientId;
//    msg.guid        = pMessage->info.guid;
//    memcpy_s( &msg.info, sizeof( msg.info ), &pMessage->info, sizeof(msg.info) );
//    SendMessageToDb( &msg );
//
//    LOG_MESSAGE( BILLINGOBJECT, LOG_PRIORITY_INFO, "收到冲值请求(%u:%u:%u:%s:%u:%u:%u:%u:%s:%s:%s:%s:%u:%u)",
//        pMessage->info.guid,
//        pMessage->info.gssid,
//        pMessage->info.typeId,
//        pMessage->info.typesn,
//        pMessage->info.points,
//        pMessage->info.discount,
//        pMessage->info.addamount,
//        pMessage->info.netincome,
//        pMessage->info.signstr,
//        pMessage->info.remark,
//        pMessage->info.userip,
//        pMessage->info.gateway,
//        pMessage->info.channel,
//        pMessage->info.paytime);
//
//    // test
//    //MsgPFAddPointsAck msgAck;
//    //msgAck.result = ER_Success;
//    //msgAck.guid   = pMessage->info.guid;
//    //msgAck.points = pMessage->info.points;
//    //memcpy( &msgAck.typesn, &pMessage->info.typesn, sizeof(msgAck.typesn) );
//    //CenterServer::GetInstance().SendMessageToPlatform( it->first, &msgAck );
//}

//void CenterServer::HandleGMKickPlayerReq( uint32 clientId, Msg* pMsg )
//{
//    MsgPFGmKickPlayerReq* pMessage = (MsgPFGmKickPlayerReq*)pMsg;
//
//    MsgPFGmKickPlayerAck msg;
//    msg.result      = ER_Success;
//    msg.accountGuid = pMessage->accountGuid;
//    msg.chardbId    = pMessage->chardbId;
//    strncpy_s( msg.charName, sizeof(msg.charName), pMessage->charName, sizeof(msg.charName)-1);
//    msg.time        = pMessage->time;
//
//    LOG_MESSAGE( PLATFORMOBJECT, LOG_PRIORITY_INFO, "recv kick req %u:%s:%u:%u", msg.accountGuid, msg.charName, msg.chardbId, msg.time );
//
//    ClientPeer* pClientPeer = NULL;
//    if ( pMessage->accountGuid != InvalidLogicNumber)
//    {
//        pClientPeer = theClientPeerManager.GetClientPeer( pMessage->accountGuid );
//    }
//
//    if ( NULL == pClientPeer && pMessage->chardbId != InvalidLogicNumber )
//    {
//        pClientPeer = theClientPeerManager.GetClientPeerByDBId( pMessage->accountGuid );
//    }
//    
//    if ( NULL == pClientPeer && strlen( pMessage->charName ) > 0 )
//    {
//        pClientPeer = theClientPeerManager.GetClientPeerByName( pMessage->charName );
//    }
//     
//    if ( NULL == pClientPeer)
//    {   
//        msg.result = ER_ClientPeerNotExist;
//        SendMessageToPlatform( &msg );
//        return;
//    }
//
//    theClientPeerManager.KickClientPeer( pClientPeer, S2SMsgKickChar::KR_Ban );
//    msg.result = ER_Success;
//    SendMessageToPlatform( clientId, &msg );
//
//    LOG_MESSAGE( PLATFORMOBJECT, LOG_PRIORITY_INFO, "process kick req %u:%s:%u:%u", msg.accountGuid, msg.charName, msg.chardbId, msg.time );
//    return;
//}

void CenterServer::HandleGMBroadcastReq( uint32 clientId, Msg* pMsg )
{
    MsgPFGMBroadcastReq* pMessage = (MsgPFGMBroadcastReq*)pMsg;

    CS2GSGMBroatcastReq msg;
    strncpy_s( msg.content, CS2GSGMBroatcastReq::CD_ContentMaxSize, pMessage->content, CS2GSGMBroatcastReq::CD_ContentMaxSize - 1);
    theGameServerManager.SendMessageToGameServers( &msg );

    LOG_MESSAGE( PLATFORMOBJECT, LOG_PRIORITY_INFO, "recv systembull %s", msg.content);
}

//void CenterServer::HandleCreateCharReq( uint32 clientId, Msg* pMsg )
//{
//    MsgPFCreateCharReq* pMessage = (MsgPFCreateCharReq*)pMsg;
//
//    MsgPFCreateCharAck ackmsg;
//    ackmsg.result = ER_Success;
//
//    uint8 usArmsType = pMessage->profession;
//    uint16 nLevel    = pMessage->level == 0 ? 1 : pMessage->level;
//
//    // 人物信息
//    SArmsParamModulusCommon& gArmsParamModulusCommon = theDataCenter.GetArmsParamModulusCommon();
//    SArmsParamModulusExtend* pArmsParamModulusExtend = theDataCenter.GetArmsParamModulus(usArmsType);
//    SLevelAttribute* pLevelAttribute                 = theCharacterAttributeConfig.GetCharacterAttribute(usArmsType, nLevel);
//    if ( NULL == pArmsParamModulusExtend || NULL == pLevelAttribute)
//    { 
//        ackmsg.result = ER_Failed;
//        SendMessageToPlatform( clientId, &ackmsg );
//        return; 
//    }
//
//    DBMsgCreateHeroChar createMsg;
//    memset( &createMsg.charinfo.baseinfo, 0, sizeof( createMsg.charinfo.baseinfo ));
//
//    createMsg.accoundId                              = pMessage->guid;       // 帐号
//    createMsg.charinfo.visual.fModelPercent          = 1.0;                  // 模型大小
//    createMsg.charinfo.baseinfo.aptotic.ucSex        = pMessage->sex;        // 性别
//    createMsg.charinfo.baseinfo.aptotic.usProfession = pMessage->profession; // 职业
//
//    HelperFunc::SafeNCpy( createMsg.charinfo.baseinfo.aptotic.szYearName, "N/A", dr_MaxYearName );
//    createMsg.charinfo.baseinfo.aptotic.byYear  = 0;
//    createMsg.charinfo.baseinfo.aptotic.byMonth = pMessage->byMonth;
//    createMsg.charinfo.baseinfo.aptotic.byDay   = pMessage->byDay;
//
//    createMsg.charinfo.baseinfo.liveinfo.nHp               = 100 ;
//    createMsg.charinfo.baseinfo.liveinfo.nMp               = 1   ;
//    createMsg.charinfo.baseinfo.liveinfo.ustLevel          = nLevel; // 等级
//    createMsg.charinfo.baseinfo.liveinfo.dwExp             = 0;
//    createMsg.charinfo.baseinfo.liveinfo.dwExpNotUsed      = 0;
//    createMsg.charinfo.baseinfo.liveinfo.dwSkillExp        = 0;
//    createMsg.charinfo.baseinfo.liveinfo.dwSkillExpNotUsed = 0;
//    createMsg.charinfo.baseinfo.liveinfo.exploit           = 0;
//    createMsg.charinfo.baseinfo.liveinfo.reputation        = 0;
//    createMsg.charinfo.baseinfo.liveinfo.honour            = 0;
//    createMsg.charinfo.baseinfo.liveinfo.battleScore       = 0;
//    createMsg.charinfo.baseinfo.liveinfo.nRecipeSkillNum   = 0;
//	createMsg.charinfo.baseinfo.liveinfo.hero_id		   = INVALID_HERO_ID;
//    createMsg.charinfo.otherdata.bNewChar                  = true;
//
//    if ( pMessage->country == CountryDefine::Country_Init || pMessage->country >= CountryDefine::Country_Max )
//    { 
//        if ( theCenterCountryManager.GetWeakCountry() != CountryDefine::Country_Init )
//        {
//            pMessage->country = theCenterCountryManager.GetWeakCountry();
//        }
//        else
//        {
//            pMessage->country = ( rand() % CountryDefine::Country_DunHuang ) + 1; 
//        }
//    }
//
//    createMsg.charinfo.baseinfo.aptotic.ucCountry = pMessage->country;    // 国家
//    const CountryConfig::BornMapSetting* pSetting = theCountryConfig.GetBornMapSetting( pMessage->country );
//    if ( pSetting == NULL )
//    { 
//        ackmsg.result = ER_Failed;
//        SendMessageToPlatform( clientId, &ackmsg );
//        return; 
//    }
//
//    createMsg.charinfo.otherdata.sBornPos.dwMapID = pSetting->GetMapID();
//    createMsg.charinfo.otherdata.sBornPos.stX     = FloatToTile( pSetting->GetPosX() );
//    createMsg.charinfo.otherdata.sBornPos.stY     = FloatToTile( pSetting->GetPosY() );
//    //初始化float坐标
//    createMsg.charinfo.otherdata.sBornPos.vPos.x  = pSetting->GetPosX();
//    createMsg.charinfo.otherdata.sBornPos.vPos.y  = pSetting->GetPosY();
//
//    createMsg.charinfo.otherdata.pos.dwMapID      = pSetting->GetMapID();
//    createMsg.charinfo.otherdata.pos.stX          = FloatToTile( pSetting->GetPosX() );
//    createMsg.charinfo.otherdata.pos.stY          = FloatToTile( pSetting->GetPosY() );
//    //初始化float坐标
//    createMsg.charinfo.otherdata.pos.vPos.x       = pSetting->GetPosX();
//    createMsg.charinfo.otherdata.pos.vPos.y       = pSetting->GetPosY();
//
//    // 朝向
//    createMsg.charinfo.otherdata.fDirX            = pSetting->GetDirX();
//    createMsg.charinfo.otherdata.fDirY            = pSetting->GetDirY();
//
//    strncpy_s( createMsg.charinfo.baseinfo.aptotic.szCharacterName, sizeof(createMsg.charinfo.baseinfo.aptotic.szCharacterName), pMessage->charName, sizeof(createMsg.charinfo.baseinfo.aptotic.szCharacterName) - 1 );
//
//    CAvatarSystemSetting::SDefSetting* pVisualSetting = pMessage->sex == Sex_Male ? theAvatarSystemSetting->GetSettingMaleHairId() : theAvatarSystemSetting->GetSettingFemaleHairId();
//    CAvatarSystemSetting::SDefSetting* pFaceSetting = pMessage->sex == Sex_Male ? theAvatarSystemSetting->GetSettingMaleFaceId() : theAvatarSystemSetting->GetSettingFemaleFaceId();
//
//    if ( NULL == pFaceSetting || NULL == pVisualSetting)
//    {
//        ackmsg.result = ER_Failed;
//        SendMessageToPlatform( clientId, &ackmsg );
//        return;
//    }
//    
//    createMsg.charinfo.baseinfo.aptotic.ucHeadPic  = static_cast< unsigned char >( pFaceSetting->nCount <= 0 ? 0 : theRand.rand32() % pFaceSetting->nCount );
//    
//    
//    uint16 hairModelIndex = pVisualSetting->nCount <= 0 ? 0 : theRand.rand16() % pVisualSetting->nCount;
//    uint16 faceModelIndex = pFaceSetting->nCount <= 0 ? 0 : theRand.rand16() % pFaceSetting->nCount;
//
//    createMsg.charinfo.visual.hairId = pVisualSetting->SItems[ hairModelIndex ].stItem;
//    createMsg.charinfo.visual.faceId = pFaceSetting->SItems[ faceModelIndex ].stItem;
//
//    SCharItem& charItem = createMsg.charinfo.itemData.stPackItems[0];
//    charItem.itembaseinfo.ustItemID = pMessage->bagid;
//    charItem.itembaseinfo.stPacketIdx  = 0;
//    charItem.itembaseinfo.ustItemCount = 1;
//    charItem.itembaseinfo.nOnlyInt     = HelperFunc::CreateID();    
//    charItem.SetBounded( true );
//    charItem.itembaseinfo.n64UseTime = TimeEx::UNDEF_TIME;
//    charItem.itembaseinfo.nLeftTime  = TimeEx::UNDEF_TIME;
//
//    createMsg.charinfo.baseinfo.liveinfo.xMasterData.SetMasterLevel( 1 );
//    createMsg.withFlag |= DBMsgCreateHeroChar::EF_WithNormalBag;
//    createMsg.subMarker = clientId;
//    SendMessageToDb( &createMsg );
//
//    LOG_MESSAGE( PLATFORMOBJECT, LOG_PRIORITY_INFO, "recv createcharreq accountId[%ld:%s,%d,%d,%d]", pMessage->guid, createMsg.charinfo.baseinfo.aptotic.szCharacterName, pMessage->sex, pMessage->profession, pMessage->level );
//}
//

void CenterServer::HandleServerStatusReq( uint32 clientId, Msg* pMsg )
{
    theServerStatusManager.SetClientID( clientId );
    theServerStatusManager.SetStatus( ServerDataDefine::ReqServerStatus );
    
    LOG_MESSAGE( PLATFORMOBJECT, LOG_PRIORITY_INFO, "Req ServerStatus" );
}

void CenterServer::HandleMsgPFAddItemReq ( uint32 clientId, Msg* pMsg )
{
    MsgPFAddItemReq* pMessage = (MsgPFAddItemReq*)pMsg;

    theMysqlCommunication.Push3PartyReqMessage( pMsg, clientId );
    LOG_MESSAGE( PLATFORMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s] Req AddItem[%u:%u]", pMessage->accountId, pMessage->item.sn, pMessage->item.itemType, pMessage->item.itemId );
}

void CenterServer::HandleMsgPFGMReloadTradeShop( uint32 clientId, Msg* pMsg )
{
	//by cloud
    //theTradeCenter.gbNeedReload = true;
    //LOG_MESSAGE( PLATFORMOBJECT, LOG_PRIORITY_INFO, "rec reload jinding shop xml" );
}

void CenterServer::HandleMsgPFGMShutdownServers( uint32 clientId, Msg* pMsg )
{ // 通知全服关闭
    MsgPFGMShutdownServersReq* pMessage = (MsgPFGMShutdownServersReq*)pMsg;
    
    // 国家
    theCenterCountryManager.SaveCountryData();    

    // 帮派
    theCenterGuildManager.SaveGuildInfo();

	// 家族
	theCenterFamilyManager.SaveFamilyInfo();
	//任务委托
	theCenterQuestEntrustManager.SaveToDatabase();
	theCenterQuestEntrustManager.StartSaveTimer(HQ_TimeGetTime() - QuestEntrustDefine::QuestEntrustSaveTime + 60);
	//关系
	//theCenterRelationManager.sa

    _revShutdownCommandTime = HQ_TimeGetTime();
    _revShutdownDelayTime   = pMessage->delayTime;

    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "收到平台关服通知(%u)s,开始全服关服流程...", pMessage->delayTime );

    S2SShutdownServer msg;
    msg.serverType  = ST_CenterServer;
    msg.delayTime   = pMessage->delayTime;
    theGameServerManager.SendMessageToGameServers( &msg );      // 发给游戏服务器
    theGameServerManager.SendMessageToCharacterServer( &msg );  // 发给角色服务器
    SendMessageToDb( &msg );                                    // 发给db
	SendMessageToLogin(&msg);									// 发给login server
}

void CenterServer::HandleMsgPFGMChangeMapExpRateReq( uint32 clientId, Msg* pMsg )
{ // 通知全服地图经验修正
    MsgPFGMChangeMapExpRateReq* pMessage = (MsgPFGMChangeMapExpRateReq*)pMsg;
    
    S2SChangeMapExpRate msg;
    msg.mapConfigId = pMessage->mapConfigId;
    msg.fExpRate    = pMessage->fExpRate;
    theGameServerManager.SendMessageToGameServers( &msg );      // 发给游戏服务器
}

void CenterServer::HandleMsgPFGMOPChatOnOff( uint32 clientId, Msg* pMsg )
{
    MsgPFGMOPChatOnOff* pMessage = (MsgPFGMOPChatOnOff*)pMsg;

    CS2GSOpRecordChatOnOff msg;
    msg.isOpen = pMessage->isOpen;    
    theGameServerManager.SendMessageToGameServers( &msg );
}

void CenterServer::PlatFormMsgGMBroadcastReq ( Msg* pMsg )
{
	if (!pMsg)
	{
		return;
	}

	MsgPFGMBroadcastReq* pMessage = (MsgPFGMBroadcastReq*)pMsg;

	CS2GSGMBroatcastReq msg;
	strncpy_s( msg.content, CS2GSGMBroatcastReq::CD_ContentMaxSize, pMessage->content, CS2GSGMBroatcastReq::CD_ContentMaxSize - 1);
	theGameServerManager.SendMessageToGameServers( &msg );

	LOG_MESSAGE( PLATFORMOBJECT, LOG_PRIORITY_INFO, "recv systembull %s", msg.content);
}

void CenterServer::PlatFormMsgSendMailReq ( Msg* pMsg )
{
	if (!pMsg)
	{
		return;
	}
	MsgPFSendMail* pMail = (MsgPFSendMail*)pMsg;
	if (!pMail)
	{
		return;
	}
	if (pMail->itemcount > 0 && pMail->itemid > 0)
	{//有附件物品则要往game server请求生成物品信息
		MsgPFSendmailReq mailinfo;
		mailinfo.characterid = pMail->characterid;
		mailinfo.money = pMail->money;
		mailinfo.itemid = pMail->itemid;
		mailinfo.itemcount = pMail->itemcount;
		strncpy_s(mailinfo.charactername,sizeof(mailinfo.charactername),pMail->charactername,sizeof(mailinfo.charactername) -1);
		strncpy_s(mailinfo.content,sizeof(mailinfo.content),pMail->content,sizeof(mailinfo.content) -1);
		strncpy_s(mailinfo.title,sizeof(mailinfo.title),pMail->title,sizeof(mailinfo.title) -1);
		//发给character server叫他生成物品信息,相对来说character server的逻辑压力不大
		theGameServerManager.SendMessageToCharacterServer(&mailinfo);
	}
	else
	{
		GS2CSSendMailReq xReq;
		xReq.charDbId = RelationDefine::InitID;

		xReq.mail.type  = SMail::EMT_System;
		xReq.mail.state = SMail::EMS_NotOpen;
		xReq.mail.sendTime = TimeEx::GetNowTime();
		xReq.mail.money = pMail->money;
		// 发信人
		xReq.mail.owners[EM_FromIndex].charDbId = 0;
		sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );

		// 收件人	
		xReq.mail.owners[EM_ToIndex].charDbId = pMail->characterid;
		HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName, pMail->charactername, sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );

		//内容
		sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,pMail->content );

		//标题
		sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, pMail->title );

		xReq.mail.accessory.type = SMail::EAT_None;//2是坐骑,1是物品
		theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
	}
}

void CenterServer::PlatFormMsgGMOPChatOnOf( Msg* pMsg )
{
	MsgPFGMOPChatOnOff* pMessage = (MsgPFGMOPChatOnOff*)pMsg;

	CS2GSOpRecordChatOnOff msg;
	msg.isOpen = pMessage->isOpen;
	theGameServerManager.SendMessageToGameServers( &msg );
}

void CenterServer::PlatFormMsgShutDownServers( Msg* pMsg )
{
	MsgPFGMShutdownServersReq* pMessage = (MsgPFGMShutdownServersReq*)pMsg;
	if (!pMessage)
	{
		return;
	}
	// 国家
	theCenterCountryManager.SaveCountryData();    

	// 帮派
	theCenterGuildManager.SaveGuildInfo();

	// 家族
	theCenterFamilyManager.SaveFamilyInfo();

	_revShutdownCommandTime = HQ_TimeGetTime();
	_revShutdownDelayTime   = pMessage->delayTime;

	LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "收到平台关服通知(%u)s,开始全服关服流程...", pMessage->delayTime );

	S2SShutdownServer msg;
	msg.serverType  = ST_CenterServer;
	msg.delayTime   = pMessage->delayTime;
	theGameServerManager.SendMessageToGameServers( &msg );      // 发给游戏服务器
	theGameServerManager.SendMessageToCharacterServer( &msg );  // 发给角色服务器
	SendMessageToDb( &msg );                                    // 发给db
	SendMessageToLogin(&msg);									// 发给login server
}

void CenterServer::PlatFormMsgModifyError( Msg* pMsg )
{
	MsgPFModifyError* pError = (MsgPFModifyError*)pMsg;
	if (!pError)
	{
		return;
	}
	MsgPlatformError msg;
	msg._result = pError->result;
	
	theGameServerManager.SendMsgToSingleRemote(InvalidLogicNumber,&msg,pError->characterid);
}

void CenterServer::PlatFormBanAccount(Msg* pMsg)
{
	MsgPFBlockAccount* pBlock = (MsgPFBlockAccount*)pMsg;
	if (!pBlock)
	{
		return;
	}
	//就在这里了...封ip的操作只让运营平台来做
// 	if ( pBlock->_type == MsgPFBlockAccount::OT_BlockIP )
// 	{
// 		
// 	}
	if(pBlock->blocktime == 0)
	{
		MsgS2SBlockAccount _block;
		strncpy_s (_block.name, sizeof( _block.name ), pBlock->name, sizeof(_block.name) - 1);
		_block.blocktime = 0;
		_block.guid = pBlock->accountid;
		_loginserverConnector.Send(&_block);
	}
	else
	{
		NotifyGLSPlayerExit(pBlock->accountid,pBlock->name,pBlock->blocktime);
	}
	

	//主要用来触发踢掉在线的
	S2SMsgKickChar msg;
	msg.time        = 0;							//这里就不给GAME SERVER锁定时间了,上面直接发送给login server写了
	msg.dwAccountID = pBlock->accountid;
	msg.usReason    = S2SMsgKickChar::KR_Ban;
	msg.uchFailAck = S2SMsgKickChar::ECD_AckCount;  //这个值表示不用给回应了
	theGameServerManager.SendMessageToGameServers( &msg );
	theGameServerManager.SendMessageToCharacterServer( &msg );
}

void CenterServer::PlatFormBanMacAdress( Msg* pMsg )
{
	MsgPFBlockMac* pBlockMac = (MsgPFBlockMac*)pMsg;
	if (!pBlockMac)
	{
		return;
	}
	MsgS2SBlockMac _blockMac;
	strncpy_s (_blockMac.scMac, sizeof( _blockMac.scMac ), pBlockMac->cMac, sizeof(_blockMac.scMac) - 1);
	_blockMac.blocktime = pBlockMac->blocktime;
	_loginserverConnector.Send(&_blockMac);

	//同时还要提玩家下线
	std::vector<ClientPeer*>* pVecClients = theClientPeerManager.GetClientPeerByMac(_blockMac.scMac);
	if (!pVecClients)	return;

	for ( int i = 0; i < pVecClients->size(); ++i )
	{
		ClientPeer* pClient = pVecClients->at(i);
		if (pClient)
		{
			S2SMsgKickChar msg;
			msg.dwAccountID= pClient->GetAccountId();
			msg.time       = 0;							    //这里就不给GAME SERVER锁定时间了,上面直接发送给login server写了
			msg.usReason   = S2SMsgKickChar::KR_Ban;
			msg.uchFailAck = S2SMsgKickChar::ECD_AckCount;  //这个值表示不用给回应了
			theGameServerManager.SendMessageToGameServers( &msg );
			theGameServerManager.SendMessageToCharacterServer( &msg );
		}
		
	}
	
}
void CenterServer::PlatFormEpistarPointAck( Msg* pMsg )
{
	MsgPFEpistarPointACK* pAck = (MsgPFEpistarPointACK*)pMsg;
	if (!pAck)
	{
		return;
	}
	//删除这个角色的特定物品
	MsgCS2GSCharRemoveItembyId msg;
	msg.characterid        = pAck->characterid;
	msg.nItemId			   = pAck->nItemId;
	theGameServerManager.SendMessageToGameServers( &msg );

}