//#include "SqlService.h"
//#include "Config.h"
//#include "mysql++.h"
//#include "md5.h"
//#include "ClientPeerManager.h"
//#include "GameServerManager.h"
//#include "GameTime.h"
//#include "GlobalFunction.h"
//
//SqlService::SqlService() 
//{
//}
//
//SqlService::~SqlService()
//{
//}
//
//bool SqlService::GetOnlineQueryMessage( SqlMessage& rMessage )
//{
//	{
//		CSALocker lock(&_OnlineQuerysLock);
//		if ( _OnlineQuerys.empty())
//		{ return false;}
//
//		rMessage = _OnlineQuerys.front();
//		_OnlineQuerys.pop_front();
//	}
//	return true;
//}
//bool SqlService::GetKickQueryMessage( KickMessage& rMessage, bool isOverTime )
//{
//	CSALocker lock(&_KickQuerysLock);
//	if ( _KickQuerys.empty())
//	{ return false; }
//
//	if ( !isOverTime )
//	{ // 不是超时的 一手的
//		ItrKickMessageContainer it = _KickQuerys.begin();
//		for ( ; it != _KickQuerys.end(); ++it )
//		{
//			if ( it->second.bProcess == 0 )
//			{ // 如果还没有被处理 或者 已经拿走
//				it->second.bProcess = 1;
//				it->second.bAcceptTime = HQ_TimeGetTime();
//				rMessage = it->second;
//				return true;
//			}
//		}
//	}
//	else
//	{// 是超时的 一手的
//		ItrKickMessageContainer it = _KickQuerys.begin();
//		for ( ; it != _KickQuerys.end(); ++it )
//		{
//			if ( it->second.bProcess == 1 && GameTime::IsPassCurrentTime( it->second.bAcceptTime, 60 * 1000 ) )
//			{ // 如果还没有被处理 或者 已经拿走一分钟没有处理了
//				it->second.bAcceptTime = HQ_TimeGetTime();
//				rMessage = it->second;
//				return true;
//			}
//		}
//	}
//	return false;
//}
//
//
//void SqlService::PushResult( const SqlMessage& sqlMessage )
//{
//	//将此消息发给CenterLoginServer
//	GameServerPeer* pTargetGameServerPeer = theGameServerManager.GetCenterLoginServerPeer();
//	if ( NULL != pTargetGameServerPeer )
//	{ 
//		MsgCenterLoginOff sql;
//		sql.sql=sqlMessage;
//		pTargetGameServerPeer->Send( &sql );
//		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u] 发送 MsgCenterLoginOff 消息", sqlMessage.Guid );
//	}
//}
//#include "DBMessageDefine.h"
//#include "CenterServer.h"
//
//void SqlService::PushUserLoginOn( const SqlMessage& rOnlineMessage )
//{
//	CSALocker lock(&_OnlineQuerysLock);
//	_OnlineQuerys.push_back( rOnlineMessage );
//
//// 	ClientPeer* pClient = theClientPeerManager.GetClientPeer( rOnlineMessage.Guid );
//// 	if ( pClient != NULL)
//// 	{ // 旧号存在
//// 		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "account[%u:%s:%s] (GetOnlineQueryMessage) 异常 处理登陆居然还在", rOnlineMessage.Guid, pClient->GetLoginInfo().szAccount, pClient->GetLoginInfo().SessionKey );
//// 		uint32 nResult = theClientPeerManager.KickClientPeer( pClient, S2SMsgKickChar::KR_AccountRepeat );
//// 		if ( nResult != ER_Success )
//// 		{ // 有异常 马上删Online 防止卡号
//// 			theCenterServer.NotifyGLSAccountSafeOffLine( rOnlineMessage.Guid, pClient->GetLoginInfo().szAccount );
//// 			LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"account[%u:%s:%s] (GetOnlineQueryMessage) GetKick KR_AccountRepeat 异常[%d] ", rOnlineMessage.Guid, pClient->GetLoginInfo().szAccount,pClient->GetLoginInfo().SessionKey, nResult );
//// 		}
//// 		return;
//// 	}
//// 
//// 	//获取gateserver的信息
//// 	long lResult = theClientPeerManager.AddLoginClientPeer( rOnlineMessage.Guid, rOnlineMessage.Passport, (char *)rOnlineMessage.SessionKey, 
//// 		(char *)rOnlineMessage.sPassword, /*rOnlineMessage.Seed,*/ rOnlineMessage.isWallow );
//// 
//// 	if ( ER_Success != lResult )
//// 	{   
//// 		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING," 消费此登录用户失败 [%d][%s] Error[%d]",  rOnlineMessage.Guid,  rOnlineMessage.Passport, lResult);
//// 	}
//}
//
//void SqlService::PushUserKick( const KickMessage& sqlMessage )
//{
//	CSALocker lock(&_KickQuerysLock);
//	_KickQuerys.insert( KickMessageContainer::value_type( sqlMessage.nGuid, sqlMessage) );
//}
//
//void SqlService::_CheckKickQueryMessage()
//{
//	static uint32 lastRecordTime = 0;
//
//	// 一分钟一次
//	if ( !GameTime::IsPassCurrentTime( lastRecordTime, 60 * 1000) )
//	{ return; }    
//	lastRecordTime = HQ_TimeGetTime();
//
//	CSALocker lock(&_KickQuerysLock);
//	if ( _KickQuerys.empty())
//	{ return; }
//
//	ItrKickMessageContainer it = _KickQuerys.begin();
//	for ( ; it != _KickQuerys.end(); )
//	{
//		KickMessage& rKickMessage = it->second;
//		if ( rKickMessage.bProcess == 1 && GameTime::IsPassCurrentTime( rKickMessage.bAcceptTime, 60 * 1000 )  )
//		{ // 如果还没有被处理 有错 做纠正
//			LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s] kick timeout delete", rKickMessage.nGuid, rKickMessage.szPassport );
//			it = _KickQuerys.erase( it );
//			continue;
//		}
//		++it;
//	}
//}
//
//
//long SqlService::RunOnce()
//{
//	_CheckKickQueryMessage();
//	
//	return ER_Success;
//}
//#endif