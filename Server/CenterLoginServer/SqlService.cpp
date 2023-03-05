//#include "SqlService.h"
//#include "Config.h"
//#include "mysql++.h"
//#include "md5.h"
//#include "logmgr.h"
//#include "LogFileObjectNameEx.h"
//#include "centerserver.h"
////#include "ClientPeerManager.h"
////#include "GameServerManager.h"
//#include "GameTime.h"
//#include "GlobalFunction.h"
//
//SqlService::SqlService() : _ConnectState(SS_TryConnect),
//                           _LastUpdateTime(0),_pMysqlConnect( NULL ),
//                           g_OnceTime(0),_bEnableService(true),_LastPingTime(0),_bHaveClearInvalidData( false ),
//                           g_bOpenShowSelect( false ), g_MaxTime(0)
//{
//    InterlockedExchange(&_getOnlineQueryFlag, 1);
//}
//
//SqlService::~SqlService()
//{   
//    if ( _pMysqlConnect )
//    { delete _pMysqlConnect;}
//}
//
//*
//数据层只负责 读取 插入数据
//逻辑在主逻辑线程去做，主线程是指centerServer类中的线程
//*/
//long SqlService::RunOnce()
//{
//    if (!_bEnableService)
//    {
//        Sleep(1000);
//        return ER_Failed;
//    }
//
//    static unsigned long unTime = HQ_TimeGetTime() ;
//
//    // 尝试连接
//    if ( _GetServiceState() != SS_Connected)
//    { _TryConnectToSqlDb();}
//
//    if ( _GetServiceState() != SS_Connected )
//    { return ER_Failed; }
//
//    // 每n分钟尝试从数据库取数据
//    if ( GameTime::IsPassCurrentTime( _LastUpdateTime, Config::GetInstance().QueryTime ) )
//    {
//        if ( !_bHaveClearInvalidData )
//        {
//            _ClearInvalidTableData();
//            _bHaveClearInvalidData = true;
//        }
//        
//        if ( g_bOpenShowSelect )
//        { 
//            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "_GetOnlineQueryFromTable");
//        }
//        
//		if ( _getOnlineQueryFlag > 0 )
//        {
//            _GetOnlineQueryFromTable();
//            InterlockedExchange(&_getOnlineQueryFlag, 0);
//        }
//
//        _GetKickQueryFromTable();
//        
//        _LastUpdateTime = HQ_TimeGetTime();
//    }
//
//    // 处理被逻辑层处理过的在线表结果数据
//    _ProcessReuslt(); 
//
//    _CheckKickQueryMessage();
//
//    _CheckState();
//
//    static const int nSleepTime = 1; //Config::GetInstance().m_bSleepTime;
//    Sleep( nSleepTime );
//
//    g_OnceTime = HQ_TimeGetTime() - unTime;
//    if ( g_OnceTime > g_MaxTime  )
//    {
//        g_MaxTime = g_OnceTime;
//    }
//    return ER_Success;
//}
//
//void SqlService::_TryConnectToSqlDb()
//{   
//    if ( _pMysqlConnect == NULL )
//    {
//        _pMysqlConnect = new mysqlpp::Connection();
//        if ( _pMysqlConnect == NULL )
//        { return;}
//    }
//
//    switch ( _GetServiceState() )
//    {
//    case SS_TryConnect:
//    case SS_ReConnected:
//        {
//            try
//            {
//                _pMysqlConnect->disconnect();
//                _pMysqlConnect->set_option(new mysqlpp::MultiStatementsOption(true));
//				printf("%s %s %s %s %d \n", Config::GetInstance().DateBaseName , Config::GetInstance().DateBaseIp
//					,Config::GetInstance().DateBaseUser , Config::GetInstance().DateBasePassword
//					,Config::GetInstance().DateBasePort);
//                bool ConnectOk = _pMysqlConnect->connect( 
//                    Config::GetInstance().DateBaseName , Config::GetInstance().DateBaseIp
//                    ,Config::GetInstance().DateBaseUser , Config::GetInstance().DateBasePassword
//                    ,Config::GetInstance().DateBasePort );
//        
//                if ( !ConnectOk)
//                {
//                    Sleep(1000);
//                    if ( _GetServiceState() == SS_TryConnect )
//                    { LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Connect MySql [Error]"); }
//                    else
//                    { LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"ReConnect MySql [Error]"); }
//                    
//                    return;
//                }
//
//                if ( _GetServiceState() == SS_TryConnect)
//                { LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_INFO,"Connect MySql [Ok]"); }
//                else
//                { LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_INFO,"ReConnect MySql [Ok]"); }
//
//                //设置mysql超时为24小时
//                mysqlpp::Query query =_pMysqlConnect->query("set interactive_timeout = 24*3600");
//                query.execute();
//
//                _ConnectState = SS_Connected;
//            }
//            catch (exception& er)
//            {   
//                if ( _GetServiceState() == SS_TryConnect )
//                { LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Connect MySql Error:%s !",er.what()); }
//                else
//                { LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"ReConnect MySql Error:%s !",er.what()); }
//            }
//        }
//        break;
//    }
//}
//
//void SqlService::_ClearInvalidTableData()
//{
//    const int bufferSize = 256;
//    char insertSql[bufferSize] = {0};
//    sprintf_s(insertSql,sizeof(insertSql)-1,"truncate table `online`; ");
//    LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "服务器启动%s", insertSql );
//
//    char delSql[bufferSize] = {0};
//    sprintf_s(delSql,sizeof(delSql)-1,"truncate table `kick_table`; ");        
//    LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "服务器启动%s", delSql    );
//
//    try
//    {
//        mysqlpp::Query query1 = _pMysqlConnect->query();
//        mysqlpp::Query query2 = _pMysqlConnect->query();
//        mysqlpp::Query query3 = _pMysqlConnect->query();
//        query1<<insertSql;
//        query1.execute();
//        query2<<delSql;
//        query2.execute();
//    }
//    catch (exception& er)
//    {
//        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"_ClearInvalidTableData Error:%s",er.what());
//    }
//}
//
//bool SqlService::_GetOnlineQueryFromTable()
//{
//    // 更新最后一次更新时间
//    //CheckLoginOutTime();
//
//    int curGuid = 0;
//    try 
//    {
//        char sqlBuf[512] = {0};
//        sprintf_s(sqlBuf,sizeof(sqlBuf)-1,"select * from online where status = %d order by state_time desc limit %d;", AS_Already_Login, Config::GetInstance().unOnceUpdateAccount);
//        mysqlpp::Query _MysqlQuery = _pMysqlConnect->query(sqlBuf);
//        mysqlpp::StoreQueryResult res = _MysqlQuery.store();
//
//        if (!res.empty())
//        {
//            for (int i = 0; i < res.num_rows();++i )
//            {
//                SqlMessage table;
//                table.Clear();
//                table.Guid  = res[i]["guid"];
//                curGuid     = table.Guid;
//                //strncpy_s(table.GLSId,sizeof(table.GLSId),res[i]["glsid"],sizeof(table.GLSId)-1);
//                strncpy_s(table.Passport,sizeof(table.Passport),res[i]["passport"],sizeof(table.Passport)-1);
//                strncpy_s(table.sPassword,sizeof(table.sPassword),res[i]["spassword"],sizeof(table.sPassword)-1);
//				strncpy_s(table.SessionKey,sizeof(table.SessionKey),res[i]["session"],sizeof(table.SessionKey)-1);
//                table.AccountLevel  = res[i]["accountlevel"];
//                //strncpy_s(table.Seed,sizeof(table.Seed),res[i]["seed"],sizeof(table.Seed)-1);
//                //strncpy_s(table.Token,sizeof(table.Token),res[i]["token"],sizeof(table.Token)-1);
//                if (stricmp(res[i]["ipport"],"NULL")!=0)
//                {
//                    strncpy_s(table.IpPort,sizeof(table.IpPort),res[i]["ipport"],sizeof(table.IpPort)-1);
//                }
//                table.Status            = res[i]["status"];
//                table.State_Time        = res[i]["state_time"];
//                table.MessageCreateTime = HQ_TimeGetTime();
//#pragma warning( push )
//#pragma warning( disable : 4244 )
//                table.isWallow          = mysqlpp::sql_smallint(res[i]["is_wallow"]);
//#pragma warning( pop )
//                {
//                    CSALocker lock(&_OnlineQuerysLock);
//                    _OnlineQuerys.push_back(table);
//                }
//            }
//        }
//
//        res.clear();
//    }
//    catch(exception &er)
//    {
//        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"_GetOnlineQueryFromTable Error!Guid=%d Error:%s",curGuid,er.what());
//    }
//
//    {
//        CSALocker lock(&_OnlineQuerysLock);
//        ItrSqlMessageContainer it    = _OnlineQuerys.begin();
//        ItrSqlMessageContainer itEnd = _OnlineQuerys.end();
//        for ( ; it!=itEnd; ++it )
//        {//更新对应的账户
//            char szSql[256] = {0};
//            sprintf_s(szSql,sizeof(szSql)-1,"update online set status=%d where guid=%d;", AS_Center_Process, it->Guid );
//            LOG_MESSAGE(SQLOBJECT,LOG_PRIORITY_DEBUG,szSql);
//            try
//            {
//                mysqlpp::Query query = _pMysqlConnect->query();
//                query << szSql;
//                query.execute();
//
//                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG,"开始处理账号[%s] Guid[%d] 登陆", it->Passport, it->Guid );
//            }
//            catch (exception& er)
//            {
//                LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"update online sqlMessage error!Guid:%d Error:%s",it->Guid, er.what());
//            }
//        }
//    }
//    
//    return true;
//}
//
//void SqlService::_ProcessReuslt()
//{
//    SqlMessageContainer sqlMessages;
//
//    {
//        CSALocker lock(&_ResultsLock);
//        if ( _Results.empty() )
//        { return; }
//        sqlMessages = _Results;
//        _Results.clear();
//    } 
//    
//    char szSql[1024] = {0};
//    ItrSqlMessageContainer it = sqlMessages.begin();
//    for ( ; it != sqlMessages.end(); ++it)
//    {
//        SqlMessage& sqlMessage = *it;
//        memset( szSql, 0, sizeof(szSql));
//
//        switch ( sqlMessage.nMessageId )
//        {
//        case SqlMessage::ESM_CanLogin:
//            {
//                int nLen = strlen (sqlMessage.IpPort);
//                if (nLen == 0)
//                { return; }
//
//                sprintf_s( szSql, sizeof(szSql)-1,"update online set status=%d,ipport='%s',state_time=%d where guid=%d;", AS_CanLogin_Game, sqlMessage.IpPort, GreenwichTime::GetTime(), sqlMessage.Guid);
//                LOG_MESSAGE( SQLOBJECT,LOG_PRIORITY_DEBUG,szSql);
//                try
//                {
//                    mysqlpp::Query query = _pMysqlConnect->query();
//                    query<<szSql;
//                    query.execute();
//                }
//                catch (exception& er)
//                {
//                    LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"%s Error:%s", szSql, er.what() );
//                    break;
//                }
//                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"account[%u:%s] 可以登录[%d]", sqlMessage.Guid, sqlMessage.Passport, AS_CanLogin_Game );
//            }
//            break;
//        case SqlMessage::ESM_ProcessLoginAllowTimeOver:
//            {
//                sprintf_s( szSql, sizeof(szSql)-1,"update online set status=%d where guid=%d and status=%d;", AS_LoginAllowTimeOver, sqlMessage.Guid, AS_Center_Process);
//                LOG_MESSAGE(SQLOBJECT,LOG_PRIORITY_DEBUG,szSql);
//                try
//                {
//                    mysqlpp::Query query = _pMysqlConnect->query();
//                    query<<szSql;
//                    query.execute();
//                }
//                catch (exception& er)
//                {
//                    LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"%s Error:%s", szSql, er.what() );
//                    break;
//                }
//                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"账号Guid[%d] 登陆消费超时 Status[%d]", sqlMessage.Guid, AS_LoginAllowTimeOver );
//            }
//            break;
//        case SqlMessage::ESM_NotGameServerService:
//            {
//                sprintf_s( szSql, sizeof(szSql)-1,"update online set status=%d where guid=%d and status=%d;", AS_NotGameServerService, sqlMessage.Guid, AS_Center_Process);
//                LOG_MESSAGE(SQLOBJECT,LOG_PRIORITY_DEBUG,szSql);
//                try
//                {
//                    mysqlpp::Query query = _pMysqlConnect->query();
//                    query<<szSql;
//                    query.execute();
//                }
//                catch (exception& er)
//                {
//                    LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"%s Error:%s", szSql,  er.what() );
//                    break;
//                }
//                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"账号Guid[%d] 没有可以用的GateServer Status[%d]", sqlMessage.Guid, AS_NotGameServerService );
//            }
//            break;
//        case SqlMessage::ESM_PlayerInGame:
//            {
//                sprintf_s( szSql, sizeof(szSql)-1,"update online set status = %d ,state_time = %d where online.guid = %d",  AS_Already_InGame, GreenwichTime::GetTime(), sqlMessage.Guid);
//                LOG_MESSAGE(SQLOBJECT,LOG_PRIORITY_DEBUG,szSql);
//                try
//                {
//                    mysqlpp::Query query = _pMysqlConnect->query();
//                    query<<szSql;
//                    query.execute();
//                }
//                catch (exception& er)
//                {
//                    LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"update online set status = %d Error:%s,Guild:%d", sqlMessage.Status, er.what(), sqlMessage.Guid);
//                    break;
//                }
//
//                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s] 在游戏中[%d]", sqlMessage.Guid, sqlMessage.Passport, AS_Already_InGame );
//            }
//            break;
//        case SqlMessage::ESM_PlayerExitGame:
//            { 
//                try
//                {
//                    char insertSql[512] = {0};
//                    if ( sqlMessage.State_Time != 0 )
//                    {
//                        mysqlpp::Query query1 = _pMysqlConnect->query();
//                        sprintf_s( insertSql, sizeof(insertSql)-1, "insert into `block` (`passport`,`expire_time`) values('%s',%d); ",sqlMessage.Passport, GreenwichTime::GetTime() + sqlMessage.State_Time / 1000);
//                        query1<<insertSql;
//                        query1.execute();
//                    }
//
//                    // 先删online表
//                    sprintf_s( szSql, sizeof(szSql)-1, "delete from `online` where guid=%d and status!=%d;",sqlMessage.Guid,AS_Already_Login );
//                    mysqlpp::Query query2 = _pMysqlConnect->query();
//                    query2.execute( szSql );
//                    query2.reset();
//                    LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u] ESM_PlayerExitGame delete from `online` where guid=%u;", sqlMessage.Guid,sqlMessage.Guid  );
//
//                    // 再删kick表
//                    sprintf_s( szSql,sizeof(szSql)-1,"delete from `kick_table` where passport='%s';", sqlMessage.Passport );
//                    query2.execute( szSql );
//                    query2.reset();                    
//
//                    // 在删内存
//                    {                
//                        CSALocker lock(&_KickQuerysLock);
//                        _KickQuerys.erase( sqlMessage.Guid );
//                    }
//                }
//                catch (exception& er)
//                {
//                    LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"%s error!Guid:%d   Error:%s", szSql, sqlMessage.Guid,er.what());
//                    break;
//                }
//            }
//            break;
//        case SqlMessage::ESM_ClientConnectGateOverTime:
//            {  
//                try
//                {
//                    mysqlpp::Query query = _pMysqlConnect->query();
//
//                    sprintf_s(szSql,sizeof(szSql)-1,"delete from `online` where guid=%u and status!=%d;", sqlMessage.Guid,AS_Already_Login );
//                    LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u] ESM_ClientConnectGateOverTime delete from `online` where guid=%u", sqlMessage.Guid,sqlMessage.Guid );
//                    query.execute( szSql );
//                    query.reset();
//
//                    sprintf_s(szSql,sizeof(szSql)-1,"delete from `kick_table` where passport='%s';",sqlMessage.Passport);
//                    query.execute( szSql );
//                    query.reset();
//                }
//                catch (exception& er)
//                {
//                    LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"%s error!Guid:%d Error:%s", szSql, sqlMessage.Guid,er.what());
//                    break;
//                }
//
//                {                
//                    CSALocker lock(&_KickQuerysLock);
//                    _KickQuerys.erase( sqlMessage.Guid);
//                }
//
//                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"account[%u:%s] 连接GateServer超时", sqlMessage.Guid, sqlMessage.Passport );
//            }
//            break;
//        case SqlMessage::ESM_GameWorldNotReady:
//            {
//                const int bufferSize = 1024;
//                char insertSql[bufferSize] = {0};
//                sprintf_s(insertSql,sizeof(insertSql)-1,"insert into `block` (`passport`,`expire_time`) values('%s',%d); ",sqlMessage.Passport, GreenwichTime::GetTime() + Config::GetInstance().BlockAccountTime);
//                LOG_MESSAGE(SQLOBJECT,LOG_PRIORITY_DEBUG,insertSql);
//
//                char delSql[bufferSize] = {0};
//                sprintf_s(delSql,sizeof(delSql)-1,"delete from `online` where passport = '%s'; ",sqlMessage.Passport);
//                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "account[%u] ESM_GameWorldNotReady delete from `online` where guid=%u", sqlMessage.Guid,sqlMessage.Guid  );
//
//                try
//                {
//                    mysqlpp::Query query1 = _pMysqlConnect->query();
//                    mysqlpp::Query query2 = _pMysqlConnect->query();
//                    query1<<insertSql;
//                    query1.execute();
//                    query2<<delSql;
//                    query2.execute();
//                }
//                catch (exception& er)
//                {
//                    LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"处理游戏世界还没有准备好 ESM_GameWorldNotReady Error:%s,Passport:%s",er.what(),sqlMessage.Passport);
//                    break;
//                }
//
//                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"处理游戏世界还没有准备好 通知 mysql 数据表 账号Guid[%s] block 一会",sqlMessage.Passport );
//            }
//            break;
//        case SqlMessage::ESM_KickInValid:
//            {
//                const int bufferSize = 256;
//                char delkickSql[bufferSize] = {0};
//                sprintf_s(delkickSql,sizeof(delkickSql)-1,"delete from `kick_table` where passport = '%s';",sqlMessage.Passport);
//                try
//                {
//                    mysqlpp::Query query = _pMysqlConnect->query();
//                    query.execute( delkickSql );
//                }
//                catch (exception& er)
//                {
//                    LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"ESM_KickInValid Error:%s,Passport:%s",er.what(),sqlMessage.Passport);
//                    break;
//                }
//
//                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"account[%u:%s] 从 kick_table 中删除无效Kick", sqlMessage.Guid, sqlMessage.Passport );
//
//                {                
//                    CSALocker lock(&_KickQuerysLock);
//                    _KickQuerys.erase( sqlMessage.Guid);
//                }
//            }
//            break;
//        case SqlMessage::ESM_KickSuccess:
//            {
//                const int bufferSize = 256;
//                char insertSql[bufferSize] = {0};
//                sprintf_s(insertSql,sizeof(insertSql)-1,"insert into `block` (`passport`,`expire_time`) values('%s',%d); ",sqlMessage.Passport, GreenwichTime::GetTime()+Config::GetInstance().BlockAccountTime);
//                LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_DEBUG, "%s [入block时候时间%d]", insertSql, GreenwichTime::GetTime() );
//
//                char delSql[bufferSize] = {0};
//                sprintf_s(delSql,sizeof(delSql)-1,"delete from `online` where passport = '%s'; ",sqlMessage.Passport);
//                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u] ESM_KickSuccess delete from `online` where guid=%u", sqlMessage.Guid,sqlMessage.Guid );
//
//                char delkickSql[bufferSize] = {0};
//                sprintf_s(delkickSql,sizeof(delkickSql)-1,"delete from `kick_table` where passport = '%s';",sqlMessage.Passport );
//                LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_DEBUG, delkickSql );
//
//                try
//                {
//                    mysqlpp::Query query1 = _pMysqlConnect->query();
//                    mysqlpp::Query query2 = _pMysqlConnect->query();
//                    mysqlpp::Query query3 = _pMysqlConnect->query();
//                    query1<<insertSql;
//                    query1.execute();
//                    query2<<delSql;
//                    query2.execute();
//                    query3<<delkickSql;
//                    query3.execute();
//                }
//                catch (exception& er)
//                {
//                    LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"ESM_KickSuccess Error:%s,Passport:%s",er.what(),sqlMessage.Passport);
//                    break;
//                }
//
//                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"account[%u:%s] 从 kick_table 中删除", sqlMessage.Guid, sqlMessage.Passport );
//
//                {                
//                    CSALocker lock(&_KickQuerysLock);
//                    _KickQuerys.erase( sqlMessage.Guid);
//                }
//            }
//            break;
//		case SqlMessage::ESM_OfflineStall:
//			{
//				sprintf_s( szSql, sizeof(szSql)-1,"update online set status = %d ,state_time = %d where online.guid = %d",  AS_OfflineStall, GreenwichTime::GetTime(), sqlMessage.Guid);
//				LOG_MESSAGE(SQLOBJECT,LOG_PRIORITY_DEBUG,szSql);
//				try
//				{
//					mysqlpp::Query query = _pMysqlConnect->query();
//					query<<szSql;
//					query.execute();
//				}
//				catch (exception& er)
//				{
//					LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"update online set status = %d Error:%s,Guild:%d", sqlMessage.Status, er.what(), sqlMessage.Guid);
//					break;
//				}
//
//				LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s] 在游戏中[%d]", sqlMessage.Guid, sqlMessage.Passport, AS_OfflineStall );
//			}
//			break;
//        }
//    }
//}
//
//bool SqlService::_GetKickQueryFromTable()
//{
//    bool result = false;
//    mysqlpp::UseQueryResult res;
//    char szSql[256] = { 0 };
//    sprintf_s(szSql,sizeof(szSql)-1,"select `guid`, `passport` from kick_table;");    
//    try
//    {
//        mysqlpp::Query query = _pMysqlConnect->query(szSql);
//        mysqlpp::StoreQueryResult res = query.store();
//        if (!res.empty())
//        {
//            for (int i = 0;i<res.num_rows();++i)
//            {
//                KickMessage kick;
//                kick.nGuid    = res[i]["guid"];
//                kick.bProcess = 0;
//                strncpy_s (kick.szPassport,sizeof( kick.szPassport ), res[i]["passport"], sizeof(kick.szPassport) - 1 );
//                {
//					CSALocker lock(&_KickQuerysLock);
//					
//					MsgCenterKick sql;
//					sql.sql=kick;
//					theCenterLoginServer.SendMsgToCenterServer(&sql);
//					
//                  //  _KickQuerys.insert( KickMessageContainer::value_type( kick.nGuid, kick) );
//                }
//                 
//            }
//            result = true;
//        }
//        else
//            result = false;
//    }
//    catch (exception& er)
//    {
//        LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"Kick Error:%s",er.what());
//        return false;
//    }
//
//    return result;
//}
//
//bool SqlService::GetOnlineQueryMessage( SqlMessage& rMessage )
//{
//    {
//        CSALocker lock(&_OnlineQuerysLock);
//        if ( _OnlineQuerys.empty())
//        { return false;}
//
//        rMessage = _OnlineQuerys.front();
//        _OnlineQuerys.pop_front();
//    }
//    return true;
//}
//
//bool SqlService::GetKickQueryMessage( KickMessage& rMessage, bool isOverTime )
//{
//    CSALocker lock(&_KickQuerysLock);
//    if ( _KickQuerys.empty())
//    { return false; }
//
//    if ( !isOverTime )
//    { // 不是超时的 一手的
//        ItrKickMessageContainer it = _KickQuerys.begin();
//        for ( ; it != _KickQuerys.end(); ++it )
//        {
//            if ( it->second.bProcess == 0 )
//            { // 如果还没有被处理 或者 已经拿走
//                it->second.bProcess = 1;
//                it->second.bAcceptTime = HQ_TimeGetTime();
//                rMessage = it->second;
//                return true;
//            }
//        }
//    }
//    else
//    {// 是超时的 一手的
//        ItrKickMessageContainer it = _KickQuerys.begin();
//        for ( ; it != _KickQuerys.end(); ++it )
//        {
//            if ( it->second.bProcess == 1 && GameTime::IsPassCurrentTime( it->second.bAcceptTime, 60 * 1000 ) )
//            { // 如果还没有被处理 或者 已经拿走一分钟没有处理了
//                it->second.bAcceptTime = HQ_TimeGetTime();
//                rMessage = it->second;
//                return true;
//            }
//        }
//    }
//    return false;
//}
//
//void SqlService::_CheckKickQueryMessage()
//{
//    static uint32 lastRecordTime = 0;
//
//    // 一分钟一次
//    if ( !GameTime::IsPassCurrentTime( lastRecordTime, 60 * 1000) )
//    { return; }    
//    lastRecordTime = HQ_TimeGetTime();
//
//    CSALocker lock(&_KickQuerysLock);
//    if ( _KickQuerys.empty())
//    { return; }
//
//    ItrKickMessageContainer it = _KickQuerys.begin();
//    for ( ; it != _KickQuerys.end(); )
//    {
//        KickMessage& rKickMessage = it->second;
//        if ( rKickMessage.bProcess == 1 && GameTime::IsPassCurrentTime( rKickMessage.bAcceptTime, 60 * 1000 )  )
//        { // 如果还没有被处理 有错 做纠正
//            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s] kick timeout delete", rKickMessage.nGuid, rKickMessage.szPassport );
//            it = _KickQuerys.erase( it );
//            continue;
//        }
//        ++it;
//    }
//}
//
//void SqlService::PushResult( const SqlMessage& sqlMessage )
//{
//    CSALocker lock(&_ResultsLock);
//    _Results.push_back( sqlMessage );
//}
//
//bool SqlService::_CheckState()
//{
//    if (!_pMysqlConnect->connected())
//    {
//        _ConnectState = SS_ReConnected;
//        return false;
//    }
//
//    //5分钟PING一次
//    if ( GameTime::IsPassCurrentTime( _LastPingTime, 5*60*1000 ) )
//    {
//        _LastPingTime = HQ_TimeGetTime();
//
//        if (!_pMysqlConnect->ping())
//        {
//            _ConnectState = SS_ReConnected;
//            return false;
//        }
//    }
//    return true;
//}
//
//void SqlService::EnableService()
//{ 
//    if ( !_bEnableService)
//    {
//        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "CenterServer就绪开始 gls 模块服务");
//    }
//    _bEnableService = true;
//}
////bool ProcessRunningRequery(SqlMessage &OnlineTable_);
////bool SqlService::ProcessRunningRequery(SqlMessage &OnlineTable_)
////{
////    //检查请求登录的时间是否超时
////    if (HQ_TimeGetTime() - OnlineTable_.MessageCreateTime >= Config::GetInstance().OutOfLoginTime)
////    {
////        SendKickAccountResult(OnlineTable_.Passport,OnlineTable_.Guid);
////        _HaveProcessOnlineQueryCount++;
////        return true;
////    }
////    //取出Online表
////    /*SqlMessage OnlineTable_ = _OnlineQuerys.front();*/
////    //处理玩家登录
////    //1.检查密码
////    if (!HelperFunc::CheckToken(OnlineTable_.sPassword,OnlineTable_.Seed,OnlineTable_.Token))
////    {
////        //添加到block表
////        _KickResults.push_back(OnlineTable_);
////        _HaveProcessOnlineQueryCount++;
////        return true;
////    }
////    //获取gateserver的信息
////    long lResult = 0;
////#ifdef __NEW_LOGIN__
////	lResult = ClientPeerManager::GetInstance().OnClientPeerLogin( OnlineTable_.Guid,
////            OnlineTable_.Passport , OnlineTable_.Token,OnlineTable_.sPassword ,OnlineTable_.Seed);
////#else
////
////#endif
////    //
////    if ( RESULT_FAILED(lResult) )
////    {
////        if (lResult == ER_ThisAccountHaveInPlayer)
////        {
////            //已经在游戏中的玩家，踢出，让这2个玩家都不能5分钟内都不能登录
////            //AddAccountToBlockLisk(OnlineTable_.Passport,GetGreenwichTime()+Config::GetInstance().BlockAccountTime);
////            _KickResults.push_back(OnlineTable_);
////            _HaveProcessOnlineQueryCount++;
////            return true;
////        }
////        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"用户请求登陆失败 [%d][%s] Error[%d]", OnlineTable_.Guid,  OnlineTable_.Passport , lResult);
////        return false;
////    }
////
////
////    //sprintf_s(OnlineTable_.IpPort,sizeof(OnlineTable_.IpPort),"%s,%d",);
////    //把结果放到result中
////    Lock();
////    _OnlineResults.push_back(OnlineTable_);
////    Unlock();
////    return true;
////}
//
//
//// bool SqlService::SendKickAccountResult(int guid,char* account)
//// {
////     //从游戏中踢出一个用户
////     ClientPeerManager::GetInstance().KickClientPeer(ClientPeerManager::GetInstance().GetClientPeer(guid));
//// 
////     //插入到踢人处理完的容器
////     SqlMessage sqlMessage;
////     sqlMessage.Guid = guid;
////     strncpy_s(sqlMessage.Passport,account,sizeof(sqlMessage.Passport));
////     _KickResults.push_back(sqlMessage);
////     return true;
//// }
//
////void CheckLoginOutTime();
////void SqlService::CheckLoginOutTime()
////{
////    if (_OnlineResults.empty())
////        return;
////
////    for (ItrSqlMessageContainer itr = _OnlineResults.begin();itr != _OnlineResults.end();)
////    {
////        if (HQ_TimeGetTime() - itr->State_Time >= Config::GetInstance().OutOfLoginTime)
////        {
////            //删除online表
////            SendKickAccountResult(itr->Passport,itr->Guid);
////            itr = _OnlineResults.erase(itr);
////            _HaveProcessOnlineQueryCount++;
////            continue;
////        }
////        ++itr;
////    }
////}