///********************************************************************
//    Filename:    SqlService.h
//    MaintenanceMan Mail: debugcommand@hotmail.com
//	�˽ṹ������ƽ̨�ʺ���֤�Ľ���,ƽ̨�����ʺ���֤�Ժ�
//	CENTER SERVER���ڻ����֤����,���뵽BUFF��,����֤�����Ƿ�Ϸ�
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
//	//SqlMessageContainer  _OnlineQuerys;       // online���ѯ����
//	//CSemiAutoIntLock     _OnlineQuerysLock;
//
//	KickMessageContainer  _KickQuerys;    // kick���ѯ����
//	CSemiAutoIntLock      _KickQuerysLock;
//};
//
//#endif
//
//#endif // __CENTERSERVER_SQLSERVICE_H__
