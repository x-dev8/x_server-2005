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
//	{ // ���ǳ�ʱ�� һ�ֵ�
//		ItrKickMessageContainer it = _KickQuerys.begin();
//		for ( ; it != _KickQuerys.end(); ++it )
//		{
//			if ( it->second.bProcess == 0 )
//			{ // �����û�б����� ���� �Ѿ�����
//				it->second.bProcess = 1;
//				it->second.bAcceptTime = HQ_TimeGetTime();
//				rMessage = it->second;
//				return true;
//			}
//		}
//	}
//	else
//	{// �ǳ�ʱ�� һ�ֵ�
//		ItrKickMessageContainer it = _KickQuerys.begin();
//		for ( ; it != _KickQuerys.end(); ++it )
//		{
//			if ( it->second.bProcess == 1 && GameTime::IsPassCurrentTime( it->second.bAcceptTime, 60 * 1000 ) )
//			{ // �����û�б����� ���� �Ѿ�����һ����û�д�����
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
//	//������Ϣ����CenterLoginServer
//	GameServerPeer* pTargetGameServerPeer = theGameServerManager.GetCenterLoginServerPeer();
//	if ( NULL != pTargetGameServerPeer )
//	{ 
//		MsgCenterLoginOff sql;
//		sql.sql=sqlMessage;
//		pTargetGameServerPeer->Send( &sql );
//		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u] ���� MsgCenterLoginOff ��Ϣ", sqlMessage.Guid );
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
//// 	{ // �ɺŴ���
//// 		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "account[%u:%s:%s] (GetOnlineQueryMessage) �쳣 �����½��Ȼ����", rOnlineMessage.Guid, pClient->GetLoginInfo().szAccount, pClient->GetLoginInfo().SessionKey );
//// 		uint32 nResult = theClientPeerManager.KickClientPeer( pClient, S2SMsgKickChar::KR_AccountRepeat );
//// 		if ( nResult != ER_Success )
//// 		{ // ���쳣 ����ɾOnline ��ֹ����
//// 			theCenterServer.NotifyGLSAccountSafeOffLine( rOnlineMessage.Guid, pClient->GetLoginInfo().szAccount );
//// 			LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"account[%u:%s:%s] (GetOnlineQueryMessage) GetKick KR_AccountRepeat �쳣[%d] ", rOnlineMessage.Guid, pClient->GetLoginInfo().szAccount,pClient->GetLoginInfo().SessionKey, nResult );
//// 		}
//// 		return;
//// 	}
//// 
//// 	//��ȡgateserver����Ϣ
//// 	long lResult = theClientPeerManager.AddLoginClientPeer( rOnlineMessage.Guid, rOnlineMessage.Passport, (char *)rOnlineMessage.SessionKey, 
//// 		(char *)rOnlineMessage.sPassword, /*rOnlineMessage.Seed,*/ rOnlineMessage.isWallow );
//// 
//// 	if ( ER_Success != lResult )
//// 	{   
//// 		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING," ���Ѵ˵�¼�û�ʧ�� [%d][%s] Error[%d]",  rOnlineMessage.Guid,  rOnlineMessage.Passport, lResult);
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
//	// һ����һ��
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
//		{ // �����û�б����� �д� ������
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