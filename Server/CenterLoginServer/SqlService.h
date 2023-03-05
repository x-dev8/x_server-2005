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
//    enum EServiceStatus
//    {
//        SS_TryConnect,
//        SS_Connected,
//        SS_ReConnected,
//    };
//
//    enum AccountState
//    {
//        AS_Already_Login          = 1, // 1 --- 登陆进来，dbcenter可以处理
//        AS_Center_Process         = 2, // 2 --- dbcenter拿到这个用户
//        AS_CanLogin_Game          = 3, // 3 --- dbcenter处理完毕，client端可以登录游戏服务器
//        AS_Already_InGame         = 4, // 4 --- 用户已在game server中
//        AS_LoginAllowTimeOver     = 5, // 5 --- 登录请求超时
//        AS_NotGameServerService   = 6, // 6
//		AS_OfflineStall			  = 7, // 7 --- 离线摆摊
//    };
//
//public:
//    SqlService();
//    ~SqlService();
//    
//    long  RunOnce();
//
//    void  EnableService(); // 开始服务
//    bool  IsEnableService(){ return _bEnableService; }
//
//    void  EnableOnlineQueryFlag();
//
//    bool  GetOnlineQueryMessage( SqlMessage& rMessage );
//    bool  GetKickQueryMessage( KickMessage& rMessage, bool isOverTime = false );
//    
//    void  PushResult( const SqlMessage& sqlMessage );
//
//protected:
//    SqlService& operator=( SqlService& ){}
//
//    void _TryConnectToSqlDb(); // 尝试连接sql
//    bool _CheckState();        // 检查SqlService运行情况
//    int  _GetServiceState(){ return _ConnectState; }
//
//    void _ProcessReuslt();
//
//    void _ClearInvalidTableData();   // 服务器重启 清除上次残余数据
//    bool _GetOnlineQueryFromTable(); // 获得OnlineQuery数据从mysql数据表Online
//    bool _GetKickQueryFromTable();   // 获得KickQuery数据从mysql数据表kick_table
//
//    void  _CheckKickQueryMessage();
//
//private:
//    int _ConnectState;                   // 连接的状态
//    mysqlpp::Connection* _pMysqlConnect; // 和mysql 的连接
//    unsigned long        _LastUpdateTime;
//                       
//    volatile long        _getOnlineQueryFlag; // 取数据flag
//    SqlMessageContainer  _OnlineQuerys;       // online表查询数据
//    CSemiAutoIntLock     _OnlineQuerysLock;
//                       
//    KickMessageContainer  _KickQuerys;    // kick表查询数据
//    CSemiAutoIntLock      _KickQuerysLock;
//                       
//    SqlMessageContainer  _Results;        // 结果消息数据
//    CSemiAutoIntLock     _ResultsLock;
//                       
//    volatile bool        _bEnableService; // 是否开始服务
//    unsigned long        _LastPingTime;
//    bool                 _bHaveClearInvalidData; // 是否启动服务器清空数据
//                       
//public:                
//    bool                 g_bOpenShowSelect;
//    unsigned long        g_OnceTime; // 从得到mysql query请求 到处理好 回给mysql的时间 可能有多线程的信息不准确，不过无所谓了
//    unsigned long        g_MaxTime;
//};
//
////////////////////////////////////////////////////////////////////////////
//// inline 
//inline void SqlService::EnableOnlineQueryFlag()
//{
//    InterlockedExchange(&_getOnlineQueryFlag, 1);
//}
//
//#endif // __CENTERSERVER_SQLSERVICE_H__
