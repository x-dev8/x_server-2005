///********************************************************************
//    Filename:    SqlService.h
//    MaintenanceMan Mail: debugcommand@hotmail.com
//	此结构用来与平台帐号认证的交互,平台进行帐号认证以后
//	CENTER SERVER定期获得认证数据,加入到BUFF用,来验证连接是否合法
//	BY VVX 2012.11.22
//*********************************************************************/
//
//#ifndef __CENTERSERVER_SQLSERVICE_H__
//#define __CENTERSERVER_SQLSERVICE_H__
//
//#pragma once
//
//#include "MeRTLibsServer.h"
//#include "WorkThread.h"
//#include "mysql++.h"
//#include "Mutex.h"
//#include "CenterGameMessage.h"
//
//
//
//typedef std::list<SqlMessage>         SqlMessageContainer;
//typedef SqlMessageContainer::iterator ItrSqlMessageContainer;
//
//typedef std::map<unsigned int, KickMessage> KickMessageContainer;
//typedef KickMessageContainer::iterator      ItrKickMessageContainer;
//
//class SqlService
//{
//public:
//	SqlService();
//	~SqlService();
//	long  RunOnce();
//
//	void  PushResult( const SqlMessage& sqlMessage );
//	void  PushUserKick( const KickMessage& sqlMessage );
//	void  PushUserLoginOn( const SqlMessage& rOnlineMessage );
//
//	bool  GetOnlineQueryMessage( SqlMessage& rMessage );
//	bool  GetKickQueryMessage( KickMessage& rMessage, bool isOverTime = false );
//	void  _CheckKickQueryMessage();
//
//	//SqlMessageContainer  _OnlineQuerys;       // online表查询数据
//	//CSemiAutoIntLock     _OnlineQuerysLock;
//
//	KickMessageContainer  _KickQuerys;    // kick表查询数据
//	CSemiAutoIntLock      _KickQuerysLock;
//};
//
//#endif
//
//#endif // __CENTERSERVER_SQLSERVICE_H__
