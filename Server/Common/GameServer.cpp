
// Common
//#include "MeNetwork.h"
#include "FuncPerformanceLog.h"
#include "TimeClock.h"
#include "Helper.h"
#include "Debuglog.h"
#include "application_config.h"
#include "ThreadBuffer.h"

// GameHead
#include "GameServer.h"
#include "ShareData.h"
#include "BaseCharacter.h"
#include "GameWorld.h"
#include "WaitReleaseChar.h"
#include "WaitReleaseStage.h"
#include "WaitReleaseConnect.h"
#include "GameTime.h"
#include "LoginStage.h"
#include "RunStatus.h"
#include "Configure.h"
#include "DatabaseConnectors.h"
#include "DropItemManager.h"
#include "ItemDetailConfig.h"
#include "GamePlayer.h"
#include "ConsoleApplication.h"
#include "GameParthFinder.h"
#include "ConfigReloader.h"
#include "GameBlockMap.h"
#include "LevelLimitGameManager.h"
#include "XmlStringLanguage.h"
#include "ColorScreen.h"
#include "LogEventService.h"
//LPCTSTR DLLPATH = "GameLogic.dll";

GameServer& GettheServer()
{
    static GameServer theServer(0, 20000);
    return theServer;
}

int g_GateServerNum = 0;

SProcessTime usetime[200] = {0};

bool g_bLoginConnectted;

GameServer::GameServer( DWORD dwAddress, WORD wPort ) : _GateServers( const_iMaxGate ), _ConnectCenterServerTcpClient( _CenterServerNetEvent/*,GetMeNetwork() */)
{
    m_dwLastUpdateLoginInfoTime = 0;
    m_dwAddress                 = dwAddress;
    m_dwAvgElapseTime           = 0; //平均一次游戏心跳处理的时间
    m_dwElapseTime              = 0; //一次游戏心跳处理的时间

    _pSocketGateServerListen    = NULL;
    //_pSocketGmToolListen        = NULL;

#ifndef _WITH_CENTERSERVER_
    m_pLoginListen    = Listener_create(); /*GetMeNetwork().CreateMeSocket()*/;
#endif
   
    _bPassCenterServerValidate = false;
    _revShutdownCommandTime    = 0;
    _revShutdownDelayTime      = 0;
    _pOwner                    = NULL;
}

GameServer::~GameServer()
{  
    _pOwner = NULL;
}

DWORD GameServer::Init( ConsoleApplication* pOwner )
{
    _pOwner = pOwner;
    GameTime::MyGetCurrentTime();
    DWORD dwInitTime = HQ_TimeGetTime();    

    _pSocketGateServerListen = Listener_create();/*GetMeNetwork().CreateMeSocket();*/
    if ( !_pSocketGateServerListen )
        return ERROR_FAILED_INIT_SERVER_SOCKET;

    //_pSocketGmToolListen = Listener_create();/*GetMeNetwork().CreateMeSocket();*/
    //if ( !_pSocketGmToolListen )
    //{
    //    goto FailProcess;
    //}

    if( /*!_pSocketGateServerListen->Create(g_Cfg.wListenGateServerPort) || */!_pSocketGateServerListen->Listen(g_Cfg.wListenGateServerPort,5) )
    {
        goto FailProcess;
    }

    //if( /*!_pSocketGmToolListen->Create(g_Cfg.wListenGmToolsPort) ||*/ !_pSocketGmToolListen->Listen(g_Cfg.wListenGmToolsPort,5) )
    //{
    //    goto FailProcess;
    //}

#ifndef _WITH_CENTERSERVER_
    if (/*!m_pLoginListen->Create(g_Cfg.wListenLoginServerPort) ||*/
        !m_pLoginListen->Listen(g_Cfg.wListenLoginServerPort,5) )
    {
        return ERROR_FAILED_LISTEN;
    }
#endif

    //if (!_pThunderListen->Create(DP_GameServerListenThunderPort) ||
    //    !_pThunderListen->Listen(5) )
    //{
    //    return ERROR_FAILED_LISTEN;
    //}

    //if( !m_pGMToolListen->Create(DP_GameServerListenManagerToolPort) ||
    //    !m_pGMToolListen->Listen(5) )
    //{
    //    return ERROR_FAILED_LISTEN;
    //}    

    /*GetMeNetwork().StartIoCompletionPort( 1, -1 );*/

    GettheDBCon().Init( /*g_Cfg.szAccountServerIP, g_Cfg.wAccountServerPort,*/
        g_Cfg.szDBServerIP, g_Cfg.iDBServerPort/*,
        g_Cfg.szLogServerIP, g_Cfg.iLogServerPort */);

	theLogEventService.Init(g_Cfg.szLogServerIp,g_Cfg.iLogServerPort,g_Cfg.dwServerID,g_Cfg.bOpenLogService);

    bool bConnectCenterServerTcpClientSelfInitNetwork = false;
    _ConnectCenterServerTcpClient.Init( g_Cfg.szCenterServerIP, g_Cfg.sCenterServerPort,0/*, bConnectCenterServerTcpClientSelfInitNetwork */);

    return ERROR_OK;

FailProcess:
    if ( _pSocketGateServerListen )
    {
        _pSocketGateServerListen->Close();
        /*_pSocketGateServerListen->Release();*/
		Listener_release(_pSocketGateServerListen);
        _pSocketGateServerListen = NULL;
    }

  //  if ( _pSocketGmToolListen )
  //  {
  //      _pSocketGmToolListen->Close();
  //      /*_pSocketGmToolListen->Release();*/
		//Listener_release(_pSocketGmToolListen);
  //      _pSocketGmToolListen = NULL;
  //  }
    return ERROR_FAILED_STARTUP;
}

DWORD GameServer::ShutDown()
{
    GettheDBCon().Shutdown();

    if ( _pSocketGateServerListen )
    {
        _pSocketGateServerListen->Close();
        /*_pSocketGateServerListen->Release();*/
		Listener_release(_pSocketGateServerListen);
        _pSocketGateServerListen = NULL;
    }

  //  if ( _pSocketGmToolListen )
  //  {
  //      _pSocketGmToolListen->Close();
  //      /*_pSocketGmToolListen->Release();*/
		//Listener_release(_pSocketGmToolListen);
  //      _pSocketGmToolListen = NULL;
  //  }

#ifndef _WITH_CENTERSERVER_
    if ( m_pLoginListen )
    {
		Listener_release(m_pLoginListen);
        /*m_pLoginListen->Release();*/
        m_pLoginListen->Close();
        m_pLoginListen = NULL;
    }
#endif

    // _pThunderListen->Close();
    //m_pGMToolListen->Close();

    // 关掉所有的GateServer
    //_StopSendMsgThread();
	//关闭图形验证码生产
	_StopGraphicCodeCheckThread();
	// 关闭寻路线程
	_StopParthFinderThread();
	// 关闭配置热重载线程
	_StopConfigReloaderThread();

	_StopPlayerMoveAnalysisThread();

    int iUsed,iSize;
    int iLoopUsed,iLoopSize;    
    /*IMeConnector*/Socketer *pGate,**ppGate;
    iUsed = _GateServers.GetUsed();
    iSize = _GateServers.GetSize();
    for( iLoopUsed = 0 , iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize  )
    {
        ppGate = _GateServers[ iLoopSize ];
        if( !ppGate || *ppGate == NULL)
            continue;

        pGate = *ppGate;
        ++ iLoopUsed;

		Socketer_release(pGate);
        /*GetMeNetwork().ReleaseMeConnector( pGate->GetKey() );*/
        _GateServers.Free( iLoopSize );
    }

   // while (!_GmConnectors.empty())
   // {
   //     /*IMeConnector*/Socketer* pConnector = *_GmConnectors.begin();
   //     if (pConnector != NULL)
   //     {
			//pConnector->Close();
			//Socketer_release(pConnector);
   //         /*GetMeNetwork().ReleaseMeConnector( pConnector->GetKey() );*/
   //         pConnector = NULL;
   //     }
   //     _GmConnectors.pop_front();
   // }

    if( _pSocketGateServerListen )
    {
        /*_pSocketGateServerListen->Release();*/
		Listener_release(_pSocketGateServerListen);
        _pSocketGateServerListen = NULL;
    }

  //  if(_pSocketGmToolListen)
  //  {
  //      /*_pSocketGmToolListen->Release();*/
		//Listener_release(_pSocketGmToolListen);
  //      _pSocketGmToolListen = NULL;
  //  }

#ifndef _WITH_CENTERSERVER_
    if (m_pLoginListen)
    {
		Listener_release(m_pLoginListen);
        /*m_pLoginListen->Release();*/
        m_pLoginListen = NULL;
    }
#endif

    //if(m_pGMToolListen)
    //{
    //    m_pGMToolListen->Release();
    //    m_pGMToolListen = NULL;    
    //}

    //if ( _pThunderListen )
    //{
    //    _pThunderListen->Close();
    //    _pThunderListen->Release();
    //    _pThunderListen = NULL;
    //}

    _ConnectCenterServerTcpClient.Release();

    thetheWaitReleaseConnect.UnInit();
	net_release();
    //GetMeNetwork().StopIoCompletionPort();
    //GetMeNetwork().SocketCleanUp();

    return ERROR_OK;
}

DWORD GameServer::Startup()
{
    m_dwStartTime = HQ_TimeGetTime();
	//去掉多线程发送,因为网络库,以后看心情如果有需要修网络再改回来,BY VVX 2012.9.6
    //_StartSendMsgThread();
	//_StartGraphicCodeCheckThread();
	_StartParthFinderThread();
	_StartConfigReloaderThread();
	_StartPlayerMoveAnalysisThread();
    return ERROR_OK;
}

bool GameServer::SwitchGateServer( MsgSwitchGate* msg, int& nGateServerIndex )
{
    unsigned int nAllOnlineNum = 0;
    ItrGateInfoContainer itr = _GateServerInfos.begin();
    for (; itr != _GateServerInfos.end(); ++itr)
    {
        nAllOnlineNum += itr->second.nOnlineNum;
    }

    itr = _GateServerInfos.begin();
    for (; itr != _GateServerInfos.end(); ++itr)
    {
        //当某个Gate上的人数低于平均负载时
        if (itr->second.nOnlineNum <= nAllOnlineNum/_GateServerInfos.size())
        {
            msg->uGatePort = itr->second.nPort;
            strncpy_s( msg->szGateIP, itr->second.szIP, sizeof(msg->szGateIP) );
            strncpy_s( msg->szChannelName, g_Cfg.szGameServerName, sizeof(msg->szChannelName));
            nGateServerIndex = itr->first;
            return true;
        }
    }
    return false;
}

SLoginInfoBase* GameServer::GetLoginInfo( /*char* szSessionKey*/__int64 SessionKey )
{
    ItrLoginInfoContainer it = _loginInfos.find( SessionKey );
    if ( it != _loginInfos.end())
        return (&it->second);

    return NULL;
}

S2SSwitchGate* GameServer::GetLoginGateCacheInfo( /*char* szSessionKey */ __int64 SessionKey)
{
    ItrLoginGateCacheInfoContainer it = _loginGateCacheInfos.find( SessionKey );
    if ( it != _loginGateCacheInfos.end())
        return (&it->second);

    return NULL;
}

void GameServer::RemoveLoginGateCacheInfo( __int64 SessionKey/*char* SessionKey*/ )
{
    _loginGateCacheInfos.erase( SessionKey );
}

bool GameServer::AddLoginInfo( SLoginInfoBase& info )
{
    SLoginInfoBase* pLoginInfoBase = GetLoginInfo( info.Sessionkey );
    if ( pLoginInfoBase == NULL)
    { _loginInfos.insert(LoginInfoContainer::value_type( info.Sessionkey, info ));}
    else
    { (*pLoginInfoBase) = info; }
    return true;
}

bool GameServer::AddLoginGateCacheInfo( /*char* SessionKey*/__int64 SessionKey, S2SSwitchGate& info )
{
    S2SSwitchGate* pLoginGateCacheInfo = GetLoginGateCacheInfo( SessionKey );
    if ( pLoginGateCacheInfo == NULL)
    { _loginGateCacheInfos.insert( LoginGateCacheInfoContainer::value_type( SessionKey, info )); }
    else
    { (*pLoginGateCacheInfo) = info; }
    return true;
}

bool GameServer::_StartSendMsgThread()
{
    //设为线程优先级为高于标准
    return _sendthread.CreateThread(SendMsgThread, this, THREAD_PRIORITY_ABOVE_NORMAL);
}

void GameServer::_StopSendMsgThread()
{
    DWORD dwThreadID = _sendthread.GetThreadID();
    _sendthread.StopThreadAndWaitDead();
    if (dwThreadID != 0)
    {
        GettheThreadBuffer().ReleaseBuffer(dwThreadID);
    }
}

void GameServer::_AcceptAllConnect()
{
    //if( RunStatusDefine::RunStatus_Running == theRunStatus.GetStatus() )
    {    
        while( _pSocketGateServerListen->CanAccept() )
        {
            if( !OnAcceptGateServer() )
            { break; }
        }

#ifndef _WITH_CENTERSERVER_
        while (m_pLoginListen->CanAccept())
        {
            AcceptLoginServer();
        }
#endif

    }
}

void GameServer::_LoadDatabaseData()
{
    //暂时没有城战,以后会修改为和军团相关
    //     if(GettheDBCon().IsCharDBOK() && !CBattleField::GetInstance().IsHaveReferLoadReq())
    //     {
    //         CBattleField::GetInstance().LoadDataReq();
    //     }
    //     if (GettheDBCon().IsCharDBOK() && !GuildStakeArbiter::Instance().IsHaveReferReq())
    //     {
    //         GuildStakeArbiter::Instance().LoadDataReq();
    //     }

    //if(GettheDBCon().IsCharDBOK() && !CStudendandTeacher::Instance().IsLoad())
    //{
    //    CStudendandTeacher::Instance().LoadPublicMessageFromDb();
    //}
}

void GameServer::SendMsgThread(void* p)
{
    if (p != NULL)
    {
        GameServer* pServer = static_cast<GameServer*>(p);
        pServer->SendAllGateMsg();

#ifndef _WITH_CENTERSERVER_
        pServer->SendLoginServerMsg();
#endif  
    }
    static const int nSleepTime = 1; //g_Cfg.m_bSleepTime;
    Sleep( nSleepTime );
}

void GameServer::RunOneStep()
{
    DECLARE_TIME_TEST

	net_run();

#ifdef _WITH_CENTERSERVER_
	// 和 center的数据交换未完成之前 后面的都不处理
	RunCenterServerCommunication();
	if( theRunStatus.GetStatus() == RunStatusDefine::RunStatus_PrepareData)
	{
		return;
	}
#endif

    // 检查服务器是否 准备退出
    static unsigned long ulTime = HQ_TimeGetTime();

	uint32 frameTime = ulTime;

    BEGIN_TIME_TEST( "GameServer::RunOneStep[0]" )
    CheckForServerExit(); // 检查服务器是否退出状态
    _LoadDatabaseData();  // 请求db服务器数据 空的
    GameTime::MyGetCurrentTime();
    _AcceptAllConnect(); // 连接新玩家
    UpdateLoginInfo();   // Dispatch
    END_TIME_TEST( "GameServer::RunOneStep[0]" );

#ifdef USE_GMMANAGER
    // GmManager
    RecvGMMsg();         // GmTools
    RecvGMToolMsg();
    ProcessGMToolMsg();
    ProcessGMMsg();
#endif
    
#ifndef _WITH_CENTERSERVER_
    RecvLoginServerMsg();
    ProcessLoginServerMsg();
#endif

    BEGIN_TIME_TEST( "GameServer::RunOneStep[1]" );
    RecvAllGateMsg();
    ProcessGateMsg();

    END_TIME_TEST( "GameServer::RunOneStep[1]");

    BEGIN_TIME_TEST( "GameServer::RunOneStep[2]" );

    theLoginStage.Run();     // 登录场景的Run

	END_TIME_TEST_1( "GameServer::RunOneStep[2]",100 );

	BEGIN_TIME_TEST( "GameServer::RunOneStep[3]" );
	theGraphicCodeCheckCommunication.Update();	//图形验证码发送
	END_TIME_TEST_1( "GameServer::RunOneStep[3]",100 );

	BEGIN_TIME_TEST( "GameServer::RunOneStep[9]" );
	GetGameParthFinder().Update();	// 寻路更新
	END_TIME_TEST_1( "GameServer::RunOneStep[9]",100 );

	BEGIN_TIME_TEST( "GameServer::RunOneStep[10]" );
	theConfigReloader.Update();	// 配置热重载更新
	END_TIME_TEST_1( "GameServer::RunOneStep[10]",100 );

	BEGIN_TIME_TEST( "GameServer::RunOneStep[11]" );
    theGameWorld.Process();  // 游戏世界Run
	END_TIME_TEST_1( "GameServer::RunOneStep[11]",200 );
	//theLevelLimitGameManager.RunOnStep(ulTime);

    
    //BEGINFUNCPERLOG( "GameServer::RunOneStep[3]" );
    //// 是否是多线程发包
    //if (!g_Cfg.bMTSendMessage)
    //{
    //    SendAllGateMsg();
    //    SendLoginServerMsg();
    //}
    //ENDFUNCPERLOG( "GameServer::RunOneStep[3]" );
	//网络库设计,不能多线程调用同个SOCKET的操作,SO...
	SendAllGateMsg();

    BEGIN_TIME_TEST( "GameServer::RunOneStep[4]" );
    GettheDBCon().RunOneStep(); //数据库Run
	END_TIME_TEST_1( "GameServer::RunOneStep[4]",100);
	BEGIN_TIME_TEST( "GameServer::RunOneStep[5]" );
    GettheWaitReleaseChar().Run();

	END_TIME_TEST_1( "GameServer::RunOneStep[5]",100);
	BEGIN_TIME_TEST( "GameServer::RunOneStep[6]" );
    theCWaitReleaseStag.Run();

	END_TIME_TEST_1( "GameServer::RunOneStep[6]",100);
	BEGIN_TIME_TEST( "GameServer::RunOneStep[7]" );
    GettheWaitReleaseConnect().Run();
	END_TIME_TEST_1( "GameServer::RunOneStep[7]",100);
	BEGIN_TIME_TEST( "GameServer::RunOneStep[8]" );
	GetTheLoginStage().Run();
	END_TIME_TEST_1( "GameServer::RunOneStep[8]",100);
   // END_TIME_TEST( "GameServer::RunOneStep[4]" );

    //ItemDetail Reload
    if (theItemDetailConfig.CheckReload(ITEMDETAILDIRECTORY))
    {
        LOG_MESSAGE( CAPABILITYOBJECT, LOG_PRIORITY_INFO, "GameServer::ItemDetail Reload %ld s", HQ_TimeGetTime() );
    }

    // 测试
    if ( GameTime::IsPassCurrentTime( ulTime, 3000 ) )
    {
        LOG_MESSAGE( CAPABILITYOBJECT, LOG_PRIORITY_WARNING, "GameServer::RunOneStep %f s", (HQ_TimeGetTime()- ulTime) / 1000.f);
    }

    if ( GameWorld::bShowRunProcessInfo )
    {   
        LOG_MESSAGE( CAPABILITYOBJECT, LOG_PRIORITY_INFO, "GameServer::RunOneStep %f s", (HQ_TimeGetTime()- ulTime) / 1000.f);
        GameWorld::bShowRunProcessInfo = false; // 清除变量
    }

	//最后做日志
	theLogEventService.RunOneStep();

    ulTime = HQ_TimeGetTime();

    uint32 time = HQ_TimeGetTime() - frameTime;
    if ( time > 100 )
    { std::cout << "frame:elapse:" << time << std::endl; }
}

char* GameServer::GetFormatErrorString( DWORD dwError )
{
    static char szBuf[256] = {0};
    std::string strErrorResult;
    switch( dwError )
    {
    case ERROR_FAILED_SHUTDOWN:
        strErrorResult = "Failed shutdown.";
        break;
    case ERROR_FAILED_STARTUP:
        strErrorResult = "Failed startup.";
        break;
    case ERROR_FAILED_LISTEN:
        strErrorResult = "Failed listen.";
        break;
    case ERROR_FAILED_INIT_SERVER_SOCKET:
        strErrorResult = "Failed init server socket.";
        break;
    case ERROR_FAILED_INIT_CLIENT:
        strErrorResult = "Failed init client.";
        break;
    case ERROR_NOPLACE_FOR_CLIENT:
        strErrorResult = "No place for client.";
        break;
    case ERROR_FAILED_ACCEPT:
        strErrorResult = "Failed accept.";
        break;
    case ERROR_FAILED_ACK_ACCEPT:
        strErrorResult = "Failed ack accept.";
        break;
    default:
        strErrorResult = "Error Unknown.";
        break;
    }
    sprintf_s( szBuf, sizeof(szBuf)-1, "%s\n", strErrorResult.c_str() );
    return szBuf;
}

void GameServer::CheckForServerExit()
{
	DECLARE_TIME_TEST
    BEGIN_TIME_TEST( "CheckForServerExit[1]" );
    // 检查关服时间
    if ( _revShutdownCommandTime != 0 && GameTime::IsPassCurrentTime( _revShutdownCommandTime, _revShutdownDelayTime * ONE_SEC))
    { 
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "关服时间(%u:%u)到,开始关服...",_revShutdownCommandTime, _revShutdownDelayTime);
        theRunStatus.SetStatus( RunStatusDefine::RunStatus_PrepareStop ); 
        _revShutdownCommandTime = 0;
        _revShutdownDelayTime   = 0;
    }

    // 检查是否需要关服流程
    if( RunStatusDefine::RunStatus_PrepareStop != theRunStatus.GetStatus() )
    { return; }

    if( 0 == theRunTimeData.GetOnlinePlayer() /*&& 0 == _GateServers.GetUsed()*/ && GettheDBCon().IsAllMsgSendOver() )
    { // 所有在线角色都退出完毕
        theRunStatus.SetStatus( RunStatusDefine::RunStatus_GameThreadStopped );        
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "服务器全部角色安全下线 数据入库..." );
		COLOR_MESSAGE( COLOR_GREEN, "[服务器可以安全退出] \n" );
        return;
    }

	END_TIME_TEST_1( "CheckForServerExit[1]",10);

	BEGIN_TIME_TEST( "CheckForServerExit[2]" );

    BaseCharacter* pChar = NULL;

    int iUsed = theRunTimeData.theCharacters.GetUsed();
    int iSize = theRunTimeData.theCharacters.GetSize();
    for( int iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
    {
        if( theRunTimeData.theCharacters.IsUsed( iLoopSize ) )
        {
            pChar = theRunTimeData.GetCharacterByID(iLoopSize);
            if( !pChar )
            { continue; }

            if( pChar->IsPlayer() )
            { pChar->OnExit(NULL); }
        }
    }
	END_TIME_TEST_1( "CheckForServerExit[2]",10);
    //_StopSendMsgThread();
	BEGIN_TIME_TEST( "CheckForServerExit[3]" );
	_StopGraphicCodeCheckThread();

	_StopParthFinderThread();

	_StopConfigReloaderThread();

	_StopPlayerMoveAnalysisThread();

	END_TIME_TEST_1( "CheckForServerExit[3]",10);

    // 关掉所有的GateServer
	// 改为手动关闭服务器,没必要关闭gate连接 by vvx 2013.6.6
    //CloseAllGates();
	BEGIN_TIME_TEST( "CheckForServerExit[4]" );
//     while (!_GmConnectors.empty())
//     {
//         /*IMeConnector*/Socketer* pConnector = _GmConnectors.front();        
//         if ( pConnector!= NULL)
//         {
//             pConnector->Close();
//             /*pConnector->Release();*/
// 			Socketer_release(pConnector);
//         }
//         _GmConnectors.pop_front();
//     }
	END_TIME_TEST_1( "CheckForServerExit[4]",10);
}

void GameServer::CloseAllGates()
{
    /*IMeConnector*/Socketer* pGate = NULL, **ppGate = NULL;
    int iUsed = _GateServers.GetUsed();
    int iSize = _GateServers.GetSize();
    int iLoopUsed = 0;
    for( int iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
    {
        ppGate = _GateServers[ iLoopSize ];
        if( NULL == ppGate || NULL == *ppGate )
        { continue; }

        pGate = *ppGate;
        ++iLoopUsed;
		Socketer_release(pGate);
        /*GetMeNetwork().ReleaseMeConnector( pGate->GetKey() );*/
        pGate = NULL;
        _GateServers.Free( iLoopSize );
    }
}

void GameServer::RecvAllGateMsg()
{    
    int iLoopUsed = 0,iLoopSize = 0;
    /*IMeConnector*/Socketer *pGate = NULL, **ppGate = NULL;
    int iUsed = _GateServers.GetUsed();
    int iSize = _GateServers.GetSize();
    for( iLoopUsed = 0 , iLoopSize = 0; iLoopUsed < iUsed && iLoopSize < iSize ; iLoopSize ++ )
    {
        ppGate = _GateServers[ iLoopSize ];
        if( NULL == ppGate || NULL == *ppGate )
        { continue; }

        pGate = *ppGate;
        iLoopUsed ++;
		if (GameWorld::bCloseGate)
		{
			pGate->Close();
		}
        if( /*pGate->IsClosed()*/pGate->IsClose())
        {
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "GateServer Close Connection!");

            DeleteAllGateClient( iLoopSize );

            GettheWaitReleaseConnect().AddReleaseConnect(pGate);

            {
                CSALocker locker(_lockGateServer);
                _GateServers.Free( iLoopSize );
            }

            ItrGateInfoContainer itr = _GateServerInfos.find(iLoopSize);
            if (itr != _GateServerInfos.end())
            { _GateServerInfos.erase(itr); }
            g_GateServerNum --;
            continue;
        }

		pGate->CheckRecv();
        /*pGate->TryRecv2();        */

        if ( GameWorld::bShowRunProcessInfo )
        { LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "RecvAllGateMsg Gate[%d] In:-,Out:-", iLoopSize /*,pGate->GetInQueueSize(), pGate->GetOutQueueSize() */); }
    }
	GameWorld::bCloseGate = false;
}

void GameServer::SendAllGateMsg()
{    
    int iLoopUsed = 0, iLoopSize = 0;
    /*IMeConnector*/Socketer *pGate = NULL, **ppGate = NULL;
    int iUsed = _GateServers.GetUsed();
    int iSize = _GateServers.GetSize();
    for( iLoopUsed = 0 , iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; iLoopSize ++ )
    {
        ppGate = _GateServers[ iLoopSize ];
        if( !ppGate || *ppGate == NULL)
        { continue; }
        pGate = *ppGate;
        iLoopUsed ++;
        if( !pGate )
        { continue; }
		
		pGate->CheckSend();
		/*pGate->TrySend2( false );*/
    }
}

bool GameServer::OnAcceptGateServer()
{
    if ( theRunStatus.GetStatus() >= RunStatusDefine::RunStatus_GameThreadStopped )
    { return false; }

    if (_GateServers.GetUsed() >= const_iMaxGate)
    { return false; }

    //if (g_Cfg.logintype == ShareData::LVT_AccountServer)
    //{ // 数据库未正常连接
    //    if (!GettheDBCon().IsDBConnectted())
    //    {
    //        return false;
    //    }
    //}    

    /*IMeSocket*/Socketer* pSocket = NULL;/*GetMeNetwork().CreateMeSocket();*/
	pSocket = _pSocketGateServerListen->Accept( pSocket );
    if( !pSocket)
    {
        goto FailProcess;
    }

    int iID = 0;

    {
        CSALocker locker(_lockGateServer);
        iID = _GateServers.Malloc();
    }

    if( -1 == iID )
    {
        goto FailProcess;
    }

    /*IMeConnector* pGateServerConnector = GetMeNetwork().CreateMeConnector();
    if( !pGateServerConnector )
    {
        goto FailProcess;
    }
    pGateServerConnector->SetSocket( pSocket );
    pGateServerConnector->BuildKey();

    bool bRegisterResult = GetMeNetwork().RegisterMeConnector( pGateServerConnector->GetKey(), pGateServerConnector );
    if ( !bRegisterResult )
    {
        goto FailProcess;
    }

    pGateServerConnector->SetNormalLevelCast(20000);
    pGateServerConnector->SetLowLevelCast(10000);
    pGateServerConnector->SetMaxQueueMsgNum ( IMeConnector::ET_InQueue, -1 );
    pGateServerConnector->SetMaxQueueMsgNum ( IMeConnector::ET_OutQueue, -1 );
    unsigned long nResult = pGateServerConnector->EnableIoCompletionPort( false );
    if ( nResult != ER_Success )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "OnAcceptGateServer EnableIoCompletionPort Fail(%d)", nResult ); 
        goto FailProcess;
    }*/

    *_GateServers[ iID ] = pSocket/*pGateServerConnector*/;

    int iLoopUsed,iLoopSize;
    int iUsed = theRunTimeData.theCharacters.GetUsed();
    int iSize = theRunTimeData.theCharacters.GetSize();
    for( iLoopUsed = 0 , iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ;++ iLoopSize )
    {
        BaseCharacter *pChar = theRunTimeData.GetCharacterByID(iLoopSize);
        if (pChar != NULL)
        {
            pChar->SendSyncCharPosToGate( iID );
        }
    }

    ++ g_GateServerNum;
    theRunTimeData.OnUpdateBurthen();

    {
        SGateServerInfo info = {0};
        _GateServerInfos.insert( GateInfoContainer::value_type(iID, info));
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Accept GateServer [%d]", _GateServers.GetUsed() );

        // 发消息给gate 要求他注册自己
        MsgRegisterServerReq xReq;
		pSocket->SendMsg(&xReq);
        //pGateServerConnector->SendMsg( &xReq );
    }

    return true;
FailProcess:
    if ( pSocket )
    {
        pSocket->Close();
        /*pSocket->Release();*/
		Socketer_release(pSocket);
        pSocket = NULL;
    }

    if ( iID != -1 )
    {
        _GateServers.Free( iID );
    }

    /*if ( pGateServerConnector )
    {
        if ( !bRegisterResult )
        {
            pGateServerConnector->Close();
            pGateServerConnector->Release();
            pGateServerConnector = NULL;
        }
        else
        {
            GetMeNetwork().ReleaseMeConnector( pGateServerConnector->GetKey() );
        }
    }*/
    return false;
} 

//处理Gate传来的消息
void GameServer::ProcessGateMsg()
{
    /*IMeConnector*/Socketer* pGate=NULL, **ppGate = NULL;
    int iUsed = _GateServers.GetUsed();
    int iSize = _GateServers.GetSize();
    for(int iLoopUsed = 0, iLoopSize = 0; iLoopUsed < iUsed && iLoopSize < iSize; ++ iLoopSize)
    {
        ppGate = _GateServers[ iLoopSize ];
        if( !ppGate || *ppGate == NULL)
        { continue; }

        pGate = *ppGate;
        ++iLoopUsed;

        if ( pGate == NULL )
        { continue; }

        Msg* pMsg = NULL;

        GameTimerEx processGameMessageTime;
        processGameMessageTime.StartTimer( HQ_TimeGetTime(), 50 );
        while( !processGameMessageTime.DoneTimer( HQ_TimeGetTime() ) )
        { // 这个时候的pMsg 已经是合成后打消息
            pMsg = pGate->GetMsg();
            //pMsg = pGate->GetMsgEx();
            if ( pMsg == NULL )
            { break;  }

            switch ( pMsg->GetType() )
            {
            case MSG_PING:
                {
                    MsgPingMsg ping;
                    pGate->SendMsg(&ping);
                }
                break;
			case MSG_LOGININFO:
				{
					MsgLoginInfo* info = (MsgLoginInfo*)pMsg;
					SendCenterServerMsg( info );
				}
				break;
            case MSG_REGISTERSERVERACK:
                {
                    MsgRegisterServerAck* pAck = static_cast< MsgRegisterServerAck* >( pMsg );
                    pAck->nParentID     = g_Cfg.dwServerID;
                    if ( pAck->nParentID == CHARACTERSERVERID )
                    {
                        pAck->uchParentType = ServerDataDefine::Node_Character;
                    }
                    else
                    {
                        pAck->uchParentType = ServerDataDefine::Node_Game;
                    }
                    SendCenterServerMsg( pAck );
                }
                break;
            case MSG_SERVERSTATUSACK:
                {
                    MsgServerStatusAck* pAck = static_cast< MsgServerStatusAck* >( pMsg );
                    pAck->nParentID     = g_Cfg.dwServerID;
                    if ( pAck->nParentID == CHARACTERSERVERID )
                    {
                        pAck->uchParentType = ServerDataDefine::Node_Character;
                    }
                    else
                    {
                        pAck->uchParentType = ServerDataDefine::Node_Game;
                    }
                    SendCenterServerMsg( pAck );
                }
                break;
            case MSG_GATEINFO:
                { // Gate定时将IP及在线人数发送过来
                    MsgGateInfo* pGateInfo = (MsgGateInfo*)pMsg;
                    ItrGateInfoContainer itr = _GateServerInfos.find(iLoopSize);
                    if (itr != _GateServerInfos.end())
                    {
                        itr->second.nOnlineNum = pGateInfo->nOnlineNum;
                        strncpy_s(itr->second.szIP, sizeof(itr->second.szIP), pGateInfo->szGateIP, sizeof(itr->second.szIP)-1);
                        itr->second.nPort = pGateInfo->nGatePort;
                    }

                    // 把GameServer现在的情况发回去
                    MsgGWorldInfo GWorldInfo;
                    GWorldInfo.nOnlineNum = theRunTimeData.GetOnlinePlayer();
                    pGate->SendMsg(&GWorldInfo);
                }
                break;
            case MSG_SWITCHGATE:
                {       
                    int nNewGateIndex = 0;
                    bool bResult = SwitchGateServer((MsgSwitchGate*)pMsg, nNewGateIndex );
                    if ( bResult)
                    { pGate->SendMsg(pMsg); }
                }
                break;
            //case MSG_LOGININFO:
                //{                    
                    //MsgLoginInfo* pLoginInfo = (MsgLoginInfo*)pMsg;
                    //SLoginInfoBase info;
                    //strncpy(info.szIP, pLoginInfo->szIP, sizeof(info.szIP)-1);
                    //strncpy(info.szAccount, pLoginInfo->szAccount, sizeof(info.szAccount)-1);
                    //info.nAccountID = pLoginInfo->nAccountID;
                    //info.MessageCreateTime = HQ_TimeGetTime();

                    //ShareData::_loginInfos.insert(std::pair<__int64, SLoginInfoBase>(pLoginInfo->SessionKey, info));
                    //SendMsgToGates(pMsg);
                    //
                    //MsgSwitchGate switchgatemsg;
                    //SwitchGateServer(&switchgatemsg);
                    //SendMsgToLoginServer(&switchgatemsg);
                //}
                //break;
            case MSG_G2GW_ALLOCCLIENT:                
                {
                    Msg_G2GW_AllocClient* pMessage = (Msg_G2GW_AllocClient*)pMsg;
                    AllocNewGateClient( iLoopSize, pGate, pMsg->header.stID, pMessage->szUserName, pMessage->ip, pMessage->dwAccountID );
					//printf("10,keylogin:send allocclient:%d,\n",HQ_TimeGetTime());
                }
                break;
            case MSG_G2GW_DELETECLIENT:
                {
                    DeleteGateClient( pMsg->header.stID );
                }
                break;
            case MSG_OUT_OF_LONGIN_TIME:
                {
                    GettheServer().SendMsgToCenterServer(pMsg);
                }
                break;
            case MSG_GATEACKLOGININFO:
                {
                    MsgAckLoginInfo* pMessage = (MsgAckLoginInfo* )pMsg;

                    S2SSwitchGate* pS2SSwitchGate = GettheServer().GetLoginGateCacheInfo( pMessage->SessionKey );
                    if ( pS2SSwitchGate != NULL )
                    {   
                        GettheServer().SendMsgToCenterServer( pS2SSwitchGate );
                        RemoveLoginGateCacheInfo( pMessage->SessionKey );
						//printf("6,keylogin:character send to center switch gate:%d\n",HQ_TimeGetTime());
                    }
                    else
                    { // Log
                        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "没有找到此SessionKey[-] Account[%u] LoginGateCacheInfo"/*, pMessage->SessionKey */,pMessage->nAccountID); 
                    }
                }
                break;
            default:
                {
                    BaseCharacter* pChar = (BaseCharacter*)theRunTimeData.GetCharacterByID( pMsg->header.stID );
                    if( pChar && pChar->IsPlayer() )
                    {
                        pChar->GetControl()->Push2In( pMsg );
                    }
                }
                break;
            }
        }
    }
}

void GameServer::UpdateLoginInfo()
{
    // 刷新时间为1分钟 刷新时间还没有到
    if ( !GameTime::IsPassCurrentTime( m_dwLastUpdateLoginInfoTime, ECD_LoginInfoUpdateFrequency  ))
    { return; }

    ItrLoginInfoContainer it = _loginInfos.begin();
    for ( ; it != _loginInfos.end();  )
    { // 设定允许IP连接的时间为十分钟
        SLoginInfoBase& rLoginInfoBase = it->second;
        if ( GameTime::IsPassCurrentTime( rLoginInfoBase.LoginTime, ECD_LoginInfoKeepTime) )
        { // 保留时间过了
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"删除过期SesstionKey[-] AccountId[%d] AccountName[%s] Time[%u:%u:%u]",
                /*rLoginInfoBase.Sessionkey, */rLoginInfoBase.nAccountID, rLoginInfoBase.szAccount, 
                HQ_TimeGetTime(), rLoginInfoBase.LoginTime, rLoginInfoBase.LoginTime + ECD_LoginInfoKeepTime);

            it = _loginInfos.erase(it);
            continue;
        }
        ++it;
    }
    m_dwLastUpdateLoginInfoTime = HQ_TimeGetTime();
}

void GameServer::RemoveLoginInfo( __int64 SessionKey/*char* szSessionKey*/ )
{
    _loginInfos.erase( SessionKey );
}

void GameServer::AllocNewGateClient( uint16 stGateID, /*IMeConnector*/Socketer* pGate,GameObjectId stID, const std::string& strAccountName, const std::string& ip, DWORD dwAccountID )
{
    // 控制在线人数
    MsgAllocClientAck retAlloc;
    retAlloc.header.stID = stID;
    retAlloc.stIDGW      = -1;
    if( theRunTimeData.GetOnlinePlayer() >= g_Cfg.iOnlineMax )
    { // 不能在分配了
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING,"Out of OnlineMax[%d],Currect OnlinePlayer[%u] EnterWorldOnlinePlayer[%d]", g_Cfg.iOnlineMax, theRunTimeData.GetOnlinePlayer(), theRunTimeData.GetEnterWorldOnlinePlayer());
        pGate->SendMsg( &retAlloc );
        return;
    }

    GameObjectId stIDGW = theRunTimeData.CreateObject( Object_Player );
    if( -1 == stIDGW )
    {
        pGate->SendMsg( &retAlloc );
        return;
    }

    GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetCharacterByID( stIDGW );
    if ( pPlayer!= NULL && pPlayer->IsPlayer() )
    {
        pPlayer->SetGateID( stGateID );
        pPlayer->SetIp(ip);
        pPlayer->SetAccount(strAccountName.c_str());
        pPlayer->SetAccountID( dwAccountID );
        bool bResult = theLoginStage.Enter( stIDGW );
        if ( !bResult)
        {
            if ( stIDGW != -1 )
            { theRunTimeData.ReleaseObject( stIDGW, __FILE__, __LINE__ ); }

            stIDGW = -1;
        }
    }

    retAlloc.stIDGW = stIDGW;
    pGate->SendMsg( &retAlloc );

    //if (g_Cfg.logintype == ShareData::LVT_1)
    //{
    //    MsgTellLS_GS_OK tellls;
    //    tellls.header.stID = stID;
    //    tellls.stGwId = stIDGW;
    //  strncpy_s( tellls.szUserName, strAccountName.c_str(), dr_MaxUserName );
    //    SendMsgToLoginServer(&tellls);
    //}
}

void GameServer::DeleteGateClient( GameObjectId stID )
{
    BaseCharacter* pChar = (BaseCharacter*)theRunTimeData.GetCharacterByID( stID );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    //删除角色
   // pChar->Log( "Exit By DeleteGateClient" );
	 pChar->Log( theXmlString.GetString(eServerLog_DeleRole) );
    pChar->CriticalError(__FUNCTION__, __FILE__, __LINE__);
}

void GameServer::DeleteAllGateClient( uint16 stGateID )
{
    int iLoopSize= 0,iLoopUsed = 0;
    BaseCharacter* pChar = NULL;
    int iUsed = theRunTimeData.theCharacters.GetUsed();
    int iSize = theRunTimeData.theCharacters.GetSize();
    for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
    {
        if ( !theRunTimeData.theCharacters.IsUsed( iLoopSize ) )
        { continue; }

        pChar = (BaseCharacter*)theRunTimeData.GetCharacterByID( iLoopSize );
        if ( pChar == NULL || !pChar->IsPlayer() )
        { continue; }

        //关闭角色
        if( ( (GamePlayer*)pChar)->GetGateID() == stGateID )    
        {
            //pChar->Log( "Exit By DeleteAllGateClient" );
			 pChar->Log( theXmlString.GetString(eServerLog_DeleAllGataClient) );
            pChar->CriticalError(__FUNCTION__, __FILE__, __LINE__);
        }
    }
}

void GameServer::SendMsgToSingle( Msg* pMsg, BaseCharacter* pSendTarget )
{
    if ( pSendTarget == NULL || !pSendTarget->IsPlayer() )
    { return; }
	
    GateMsgAdditionalData gateadd;
    gateadd.cSendRange = sendrange_single;
    gateadd.data.single.stSendTarget = pSendTarget->GetID();
    GamePlayer *pPlayer = (GamePlayer *)pSendTarget;
    SendMsgToGate( pMsg, pPlayer->GetGateID(), &gateadd );
}

void GameServer::SendMsgToView( Msg *pMsg, GameObjectId playerId, bool bExceptMe )
{ // 发消息给视野内的玩家
    GateMsgAdditionalData gateadd;
    if ( bExceptMe )
        gateadd.cSendRange = sendrange_viewexceptme;
    else
        gateadd.cSendRange = sendrange_view;
    gateadd.data.view.stSendTarget = playerId;
    SendMsgToGates( pMsg, &gateadd );
}

void GameServer::SendMsgToRegion( Msg *pMsg, GameObjectId playerId )
{ // 发消息给地域内的玩家
    GateMsgAdditionalData gateadd;
    gateadd.cSendRange = sendrange_region;
    gateadd.data.view.stSendTarget = playerId;
    SendMsgToGates( pMsg, &gateadd );
}

void GameServer::SendMsgToArea( Msg *pMsg, DWORD dwMapId, int nX, int nY )
{ // 发消息给区域内的玩家
    GateMsgAdditionalData gateadd;
    gateadd.cSendRange = sendrange_area;
    gateadd.data.area.dwMapId = dwMapId;
    gateadd.data.area.stAreaX = nX;
    gateadd.data.area.stAreaY = nY;
    SendMsgToGates( pMsg, &gateadd );
}

void GameServer::SendMsgToStage( Msg *pMsg, DWORD dwMapId )
{ // 发消息给本场景内的玩家    
    GateMsgAdditionalData gateadd;
    gateadd.cSendRange = sendrange_stage;
    gateadd.data.stage.dwMapId = dwMapId;
    SendMsgToGates( pMsg, &gateadd );
}

void GameServer::SendMsgToWorld( Msg* pMsg, bool bToCenterServer )
{ // 发消息给服务器的每一个玩家
    GateMsgAdditionalData gateadd;
    gateadd.cSendRange = sendrange_world;
    SendMsgToGates( pMsg, &gateadd );

    if ( bToCenterServer )
    {   
        S2STransmit msg;
        msg.ucSessionType  = S2STransmit::SESSIONT_World;
        msg.targetData.server.id = g_Cfg.dwServerID;
        bool bResult = msg.StorageMessage( pMsg );
        if ( !bResult)
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "SendMsgToWorld SendMessage Remote[%d,%d]转发消息太长了", pMsg->GetLength(), pMsg->GetType());
            return;
        }
        SendMsgToCenterServer( &msg );
    }
}

void GameServer::SendMsgToCountry( Msg* pMessage, TCountryId uchCountryId, bool bToCenter, uint16 ustLevel, uint16 stExceptID )
{ // 发消息给服务器的每一个玩家
    GateMsgAdditionalData gateadd;
    gateadd.cSendRange              = sendrange_country;
    gateadd.data.country.country    = uchCountryId;
    gateadd.data.country.ustlevel   = ustLevel;
    gateadd.data.country.stExceptID = stExceptID;
    SendMsgToGates( pMessage, &gateadd );
    if ( bToCenter )
    {   
        S2STransmit msg;
        msg.ucSessionType  = S2STransmit::SESSIONT_Country;
        msg.targetData.country.countryId = uchCountryId;
        bool bResult = msg.StorageMessage( pMessage );
        if ( !bResult)
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "SendMsgToCountry SendMessage Remote[%d,%d]转发消息太长了", pMessage->GetLength(), pMessage->GetType());
            return;
        }
        SendMsgToCenterServer( &msg );
    }
}

//void GameServer::SendMsgToLoginServer(Msg *pMsg)
//{
//    if (_pLoginServerConnector != NULL)
//    {
//        _pLoginServerConnector->SendMsg(pMsg);
//    }
//}

long GameServer::SendMsgToCenterServer( Msg* pMessage, void* pData )
{
    if ( !pData)
        return _ConnectCenterServerTcpClient.Send( pMessage );
    else
        return _ConnectCenterServerTcpClient.Send( pMessage, (char*)pData, strlen((char*)pData) );
}


bool GameServer::SendMsgToSingleRemote( unsigned long sourceDbId, Msg* pMessage, unsigned long nDbId, const char* szCharacterName, bool bDirect /*= true  */)
{   
    S2STransmit msg;
    msg.identifyId             = sourceDbId;
    msg.header.stID          = pMessage->header.stID;
    msg.ucSessionType        = S2STransmit::SESSTONT_Single;
    msg.directToClient       = bDirect ? 1 : 0;
    msg.targetData.character.uDbId = nDbId;
    strncpy_s( msg.targetData.character.szName, szCharacterName, sizeof(msg.targetData.character.szName) - 1);
    bool bResult = msg.StorageMessage( pMessage );
    if ( !bResult)
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "SendMsgToSingleRemote SendMessage Remote[%d,%d]转发消息太长了", 
            pMessage->GetLength(), pMessage->GetType());
        return false;
    }
    SendMsgToCenterServer( &msg );
    return true;
}

bool GameServer::SendMsgToAllServer( Msg* pMessage, unsigned int ServerId, bool bExceptMe )
{
    S2STransmit msg;
    msg.identifyId     = 0;
    msg.header.stID          = pMessage->header.stID;
    msg.ucSessionType        = S2STransmit::SESSIONT_Server;
    msg.targetData.server.id = ServerId;
    msg.targetData.server.exceptMe = bExceptMe ? 1 : 0;
    bool bResult = msg.StorageMessage( pMessage );
    if ( !bResult)
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "SendMsgToSingleRemote SendMessage Remote[%d,%d]转发消息太长了", 
            pMessage->GetLength(), pMessage->GetType());
        return false;
    }
    SendMsgToCenterServer( &msg );
    return true;
}

bool GameServer::SendMsgToTeamRemote(Msg* pMessage, S2STransmit::STeam& xTeam, bool bDirect /*= true */)
{   
    S2STransmit msg;
    msg.ucSessionType  = S2STransmit::SESSIONT_Team;
    msg.directToClient = bDirect ? 1 : 0;
    msg.targetData.team      = xTeam;
    bool bResult = msg.StorageMessage( pMessage );
    if ( !bResult)
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "SendMsgToTeamRemote SendMessage Remote[%d,%d]转发消息太长了", pMessage->GetLength(), pMessage->GetType());
        return false;
    }
    SendMsgToCenterServer( &msg );
    return true;
}

bool GameServer::SendMsgToOrganizeRemote(Msg* pMessage, unsigned int Guild, bool bDirect /*= true*/ )
{
    S2STransmit msg;
    msg.ucSessionType = S2STransmit::SESSIONT_Guild;
    msg.directToClient = bDirect ? 1 : 0;
    msg.targetData.guild.id = Guild;
    bool bResult = msg.StorageMessage( pMessage );
    if ( !bResult)
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "SendMsgToOrganizeRemote SendMessage Remote[%d,%d]转发消息太长了", 
            pMessage->GetLength(), pMessage->GetType());
        return false;
    }
    SendMsgToCenterServer( &msg );
    return true;
}

/*IMeConnector*/Socketer* GameServer::GetGate( short stGateID )
{
    /*IMeConnector*/Socketer** ppGate = _GateServers[ stGateID ];

    if( NULL == ppGate || NULL == *ppGate )
    { return 0; }

    return *ppGate;
}

void GameServer::SendMsgToGate( Msg *pMsg,int iGate, GateMsgAdditionalData* pData )
{   
    /*IMeConnector*/Socketer* pGateConnecter = GetGate( iGate );
    if( pGateConnecter == NULL  )
    { return; }

    if ( pData )
    { pGateConnecter->SendMsg( pMsg,/*IMeConnector::ECT_Normal,0,*/(char*)pData,sizeof(*pData) ); }
    else
    { pGateConnecter->SendMsg( pMsg ); }
}

void GameServer::SendMsgToGates( Msg *pMsg, GateMsgAdditionalData* pData )
{   
    // 发给所有的Gate
    int iUsed = _GateServers.GetUsed();
    int iSize = _GateServers.GetSize();

    int iLoopUsed, iLoopSize;
    /*IMeConnector*/Socketer* pGateConnecter, **ppGate;

    for( iLoopUsed = 0, iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize)
    {
        ppGate = _GateServers[ iLoopSize ];
        if( !ppGate || *ppGate == NULL)
            continue;

        pGateConnecter = *ppGate;

        if ( pGateConnecter == NULL )
            continue;

        iLoopUsed ++;

        if ( !pGateConnecter)
            continue;

        if ( pData )
            pGateConnecter->SendMsg( pMsg,(char*)pData,sizeof(*pData) );
        else
            pGateConnecter->SendMsg( pMsg );
    }
}

///////////////////////////////////////////////////////////////////////////
// GM端口监听
///////////////////////////////////////////////////////////////////////////
//void GameServer::RecvGMMsg()
//{
//    if(_GmConnectors.empty())
//        return;
//
//    for (std::list</*IMeConnector*/Socketer*>::iterator itr = _GmConnectors.begin(); itr != _GmConnectors.end();
//        itr ++)
//    {
//        /*IMeConnector*/Socketer* pCon = *itr;
//        if (pCon != NULL && !pCon->IsClose())
//        {
//            //char szBuff[500] = {0};
//            //if (pCon->GetSocket()->Recv(szBuff, sizeof(szBuff)) > 0)
//            //{
//            //    theGameWorld.ProcGMCommand(szBuff);
//            //}
//        }
//    }
//
//    ////每个Sock每次不得超过2000个消息，否则暂时不接收
//    //if(m_pGMSock->GetInQueueSize() > 2000)
//    //{
//    //    return;
//    //}
//
//    //if( !m_pGMSock->IsUseIoCompletionPort() )
//    //{
//    //    if( m_pGMSock->GetSocket()->HasData() )
//    //    {
//    //        m_pGMSock->TryRecv();
//    //    }
//    //}
//}
//
//void GameServer::SendGMMsg( Msg *pMsg )
//{
//    if(_GmConnectors.empty())
//        return;
//
//    GMConnectorContainer::iterator itr = _GmConnectors.begin();
//    for (; itr != _GmConnectors.end(); ++itr )
//    {
//        /*IMeConnector*/Socketer* pCon = *itr;
//        if (pCon != NULL && !pCon->IsClose())
//        {
//            pCon->SendMsg( pMsg );
//            pCon->CheckSend( );
//        }
//    }
//}	

long GameServer::SendCenterServerMsg( Msg* pMessage )
{
    _ConnectCenterServerTcpClient.Send( pMessage );
    return ER_Success;
}

//void GameServer::SendGMMsg(const char* szData, size_t size)
//{
//    if(_GmConnectors.empty())
//    {
//        return;
//    }
//
//    for (std::list</*IMeConnector*/Socketer*>::iterator itr = _GmConnectors.begin();
//        itr != _GmConnectors.end();
//        itr ++)
//    {
//        /*IMeConnector*/Socketer* pCon = *itr;
//        if (pCon != NULL && !pCon->IsClose())
//        {
//            //pCon->GetSocket()->Send(const_cast<char*>(szData), size);
//        }
//    }
//}

void GameServer::TellClients( const char* string, ... )
{
    if( !string )
    { return; }

    va_list	va;
    char data[1024];
    va_start( va, string );
    wvnsprintf(data, sizeof(data)-1, string, va );
    va_end( va );

    MsgChat chat(MsgChat::CHAT_TYPE_GAMEPROMPT);
    chat.SetString( data );
    GettheServer().SendMsgToWorld( &chat, false );
}

//void GameServer::ProcessGMMsg()
//{
//    if(_GmConnectors.empty())
//        return;
//
//    GMConnectorContainer::iterator itr = _GmConnectors.begin();
//    for ( ;itr != _GmConnectors.end(); )
//    {   
//        /*IMeConnector*/Socketer* pCon = *itr;
//        if ( pCon!= NULL && pCon->IsClose() )
//        {
//            // OnConnectLost
//            /*pCon->Release();*/
//			Socketer_release(pCon);
//            *itr = NULL;
//            itr = _GmConnectors.erase( itr );
//            continue;
//        }
//
//        if (pCon != NULL && !pCon->IsClose())
//        {
//            Msg *pMsg;
//            while( pMsg = pCon->GetMsg() )
//            {
//                DWORD dwType = pMsg->GetType();
//                if (MSG_GMCOMMAND == dwType)
//                {
//                    MsgGMCommand* pGMCommand = (MsgGMCommand*)pMsg;
//                    theGameWorld.ProcGMCommand(pGMCommand->szCommand);
//                }
//            }
//        }
//
//        ++itr;
//    }
//}

//bool GameServer::AcceptGmTools()
//{
//    /*IMeSocket*/Socketer* pSocket = NULL/*GetMeNetwork().CreateMeSocket()*/;
//
//	pSocket = _pSocketGmToolListen->Accept( pSocket );
//    if( !pSocket )
//    {
//        goto FailProcess;
//    }
//
//    /*IMeConnector* pGmToolConnector = GetMeNetwork().CreateMeConnector();
//
//    if(!pGmToolConnector)
//    {
//        goto FailProcess;
//    }
//
//    pGmToolConnector->SetSocket(pSocket);
//    pGmToolConnector->BuildKey();
//    bool bRegisterResult = GetMeNetwork().RegisterMeConnector( pGmToolConnector->GetKey(), pGmToolConnector );
//    if ( !bRegisterResult )
//    {
//        goto FailProcess;
//    }
//
//    pGmToolConnector->SetNormalLevelCast(5000);
//    pGmToolConnector->SetLowLevelCast(2500);
//    pGmToolConnector->SetMaxQueueMsgNum ( IMeConnector::ET_InQueue, -1 );
//    pGmToolConnector->SetMaxQueueMsgNum ( IMeConnector::ET_OutQueue, -1 );*/
//
//   /* in_addr pInaddr;
//    char gmhostip[64] = {0};*/
//
//    //if (pGmToolConnector->GetSocket()->GetPeerName(pInaddr) != false)
//    {
//        //strncpy(gmhostip, inet_ntoa(pInaddr), sizeof(gmhostip)-1);
//        //if (!cGMToolPassIpList::Instance().IsIpPass(gmhostip))
//        //{
//        //goto FailProcess;
//        //}
//    }
//
//    _GmConnectors.push_back(pSocket);
//
//    return true;
//
//FailProcess:
//    if ( pSocket )
//    {
//        pSocket->Close();
//        /*pSocket->Release();*/
//		Socketer_release(pSocket);
//        pSocket = NULL;
//    }
//
//    /*if ( pGmToolConnector )
//    {
//        if ( !bRegisterResult )
//        {
//            pGmToolConnector->Close();
//            pGmToolConnector->Release();
//            pGmToolConnector = NULL;
//        }
//        else
//        {
//            GetMeNetwork().ReleaseMeConnector( pGmToolConnector->GetKey());
//        }
//    }*/
//    return false;
//}

//void GameServer::RecvLoginServerMsg()
//{
//    if(_pLoginServerConnector == NULL)
//    { return; }
//
//    if( _pLoginServerConnector->IsClose() )
//    {   
//        /*GetMeNetwork().ReleaseMeConnector( _pLoginServerConnector->GetKey());        */
//		Socketer_release(_pLoginServerConnector);
//        _pLoginServerConnector = NULL;
//        g_bLoginConnectted = false;
//        return;
//    }
//
//	_pLoginServerConnector->CheckRecv();
//    //_pLoginServerConnector->TryRecv2();
//}

//void GameServer::SendLoginServerMsg()
//{
//    if(_pLoginServerConnector == NULL)
//    { return; }
//
//	_pLoginServerConnector->CheckSend();
//    /*_pLoginServerConnector->TrySend2( false );*/
//}

//void GameServer::ProcessLoginServerMsg()
//{
//    if(_pLoginServerConnector == NULL)
//    {
//        static DWORD dwTime = 0;
//        //每秒记录一次
//        if (HQ_TimeGetTime() - dwTime > 1000)
//        {
//            dwTime = HQ_TimeGetTime();
//            DebugLogout("[GameServer] LoginServer断开连接");
//        }
//        return;
//    }
//
//    Msg *pMsg;
//    while( pMsg = _pLoginServerConnector->GetMsg() )
//    {
//        DWORD dwType = pMsg->GetType();
//        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "[GameServer] LoginServer消息 %d", dwType);
//        if(MSG_PING == dwType)
//        {
//            MsgPingMsg ping;
//            SendMsgToLoginServer(&ping);
//        }
//        else if(dwType == MSG_LOGININFO)
//        {
//            /*MsgLoginInfo* pLoginInfo = (MsgLoginInfo*)pMsg;
//
//            SLoginInfoBase info;
//            strncpy(info.szIP, pLoginInfo->szIP, sizeof(info.szIP)-1);
//            info.nAccountID = pLoginInfo->nAccountID;
//            info.MessageCreateTime = HQ_TimeGetTime();
//            strncpy(info.szAccount, pLoginInfo->szAccount, sizeof(info.szAccount)-1);
//
//            GettheServer().AddLoginInfo( info );
//            SendMsgToGates(pMsg);
//
//            MsgSwitchGate switchgatemsg;
//            SwitchGateServer(&switchgatemsg);
//            switchgatemsg.header.stID = pLoginInfo->header.stID;
//            GetErrorLog()->logString("[GameServer] SendLoginInfo To LoginServer IP: %s, Port: %d \n", switchgatemsg.szGateIP, switchgatemsg.uGatePort);
//
//            SendMsgToLoginServer(&switchgatemsg);*/
//
//            //if (g_Cfg.logintype == ShareData::LoginValidateType::LVT_17173Interface)
//            //{
//            //    DBMsgAckAccountState check;
//            //    check.header.stID = pLoginInfo->header.stID;
//            //    check.dwAccountID = pLoginInfo->nAccountID;
//            //    check.shState = 1;
//            //    check.shRet = 1;
//
//            //    GamePlayer* player = (GamePlayer*)theRunTimeData.GetCharacterByID(pLoginInfo->header.stID);
//            //    if (player)
//            //    {
//            //        player->ProcessMsg(&check);
//            //    }
//            //}
//        }
//        if(DBMSG_ACK_ACCOUNTSTATE == dwType)
//        {
//            DBMsgAckAccountState* pstate = (DBMsgAckAccountState*)pMsg;
//            if (pstate)
//            {
//                GamePlayer* player = (GamePlayer*)theRunTimeData.GetCharacterByID(pstate->header.stID);
//                if (player)
//                {
//                    player->m_dbinfo.dwAccountID = pstate->dwAccountID;
//                    player->ProcessMsg(pMsg);
//                }
//            }
//        }
//    }
//
//    //MsgGWBurthen msg;
//    //msg.nCurrOnline = theRunTimeData.GetOnlinePlayer();
//    //msg.nMaxOnline = g_Cfg.iOnlineMax;
//    //SendMsgToLoginServer(&msg);
//}

//bool GameServer::AcceptLoginServer()
//{
//    /*IMeSocket*/Socketer* pSocket = NULL;/*GetMeNetwork().CreateMeSocket();*/
//	pSocket = m_pLoginListen->Accept( pSocket );
//    if( !pSocket )
//    {
//        goto FailProcess;
//    }
//
//    /*IMeConnector* pLoginConnector = GetMeNetwork().CreateMeConnector();
//
//    if(!pLoginConnector)
//    {
//        goto FailProcess;
//    }
//
//    pLoginConnector->SetSocket(pSocket);
//    pLoginConnector->BuildKey();
//
//    bool bRegisterResult = GetMeNetwork().RegisterMeConnector( pLoginConnector->GetKey(), pLoginConnector );
//    if ( !bRegisterResult )
//    {
//        goto FailProcess;
//    }
//
//    pLoginConnector->SetNormalLevelCast(5000);
//    pLoginConnector->SetLowLevelCast(2500);
//
//    pLoginConnector->SetMaxQueueMsgNum ( IMeConnector::ET_InQueue, -1 );
//    pLoginConnector->SetMaxQueueMsgNum ( IMeConnector::ET_OutQueue, -1 );
//
//    unsigned long result = pLoginConnector->EnableIoCompletionPort( false );
//    if ( result != ER_Success )
//    {   
//        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "AcceptLoginServer->EnableIoCompletionPort Fail(0x%x)",result);
//        return false;
//    }*/
//
//    _pLoginServerConnector = pSocket/*pLoginConnector*/;
//
//    g_bLoginConnectted = true;
//
//   /* in_addr pInaddr;
//    char ip[64] = {0};
//    if (pLoginConnector->GetSocket()->GetPeerName(pInaddr) != false)
//    {
//        strncpy_s(ip, sizeof( ip ), inet_ntoa(pInaddr), sizeof(ip)-1);
//    }*/
//
//    return true;
//
//FailProcess:
//    if ( pSocket )
//    {
//        pSocket->Close();
//		Socketer_release(pSocket);
//        /*pSocket->Release();*/
//        pSocket = NULL;
//    }
//
//    /*if ( pLoginConnector )
//    {
//        if ( !bRegisterResult )
//        {
//            pLoginConnector->Release();
//            pLoginConnector = NULL;
//        }
//        else
//        {
//            GetMeNetwork().ReleaseMeConnector( pLoginConnector->GetKey() );
//            pLoginConnector = NULL;
//        }
//    }*/
//    _pLoginServerConnector = NULL;
//    return false;
//}

void GameServer::RunCenterServerCommunication()
{
    if ( _ConnectCenterServerTcpClient.GetConnectState() != TcpClient::CS_Connected )
    {
        // 停服状态
        switch ( theRunStatus.GetStatus() )
        {
        case RunStatusDefine::RunStatus_PrepareStop:
        case RunStatusDefine::RunStatus_GameThreadStopped:
        case RunStatusDefine::RunStatus_DBThreadStopped:
            return;
            break;
        default:
            break;;
        }

        _ConnectCenterServerTcpClient.TryConnect();
        if ( _ConnectCenterServerTcpClient.GetConnectState() == TcpClient::CS_Connected )
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Connect CenterServer[%s:%d] Success! ServerId[%u]", _ConnectCenterServerTcpClient.GetIP().c_str(), 
                _ConnectCenterServerTcpClient.GetPort(), g_Cfg.dwServerID);
        }		
    }
	if(_ConnectCenterServerTcpClient.GetConnectState() == TcpClient::CS_Connected )
	{
		_ConnectCenterServerTcpClient._Receive();
		_ConnectCenterServerTcpClient.Update();
		_ConnectCenterServerTcpClient._Send();

		static DWORD time_ = 0;
		if (timeGetTime() - time_ > 5000)
		{
			CS2GSPing msg;
			_ConnectCenterServerTcpClient.Send(&msg);

			if (!IsCenterServerValidate())
			{
				GS2CSRegiseterGameServerInfoReq msg;            
				msg.SetLevel(level_high); //在这里设置中等优先级
				strncpy_s( msg.szGameServerName, g_Cfg.szGameServerName, sizeof(msg.szGameServerName));
				msg.btReset   = GS2CSRegiseterGameServerInfoReq::ROT_LOOP;
				msg.nServerId = g_Cfg.dwServerID;
				SendCenterServerMsg( &msg );
			}
			
			theRunTimeData.OnUpdateBurthen();//发送人数信息
			time_ = timeGetTime();
		}
	}
}

void GameServer::NotifyMainConsoleThread()
{
    if ( _pOwner )
    { _pOwner->SetExitFlag(); }
}

bool GameServer::_StartGraphicCodeCheckThread()
{
	return _GraphicCodeCheckThread.CreateThread( GraphicCodeCheckCommunication::CheckThreadFunc, &theGraphicCodeCheckCommunication );
}

void GameServer::_StopGraphicCodeCheckThread()
{
	DWORD dwThreadID = _GraphicCodeCheckThread.GetThreadID();
	_GraphicCodeCheckThread.StopThreadAndWaitDead();
	if (dwThreadID != 0)
	{
		GettheThreadBuffer().ReleaseBuffer(dwThreadID);
	}
}

bool GameServer::_StartParthFinderThread()
{
	return _ParthFinderThread.CreateThread( GameParthFinder::ParthFinderThreadFunc, &GetGameParthFinder() );
}

void GameServer::_StopParthFinderThread()
{
	DWORD dwThreadID = _ParthFinderThread.GetThreadID();
	_ParthFinderThread.StopThreadAndWaitDead();
	if (dwThreadID != 0)
	{
		GettheThreadBuffer().ReleaseBuffer(dwThreadID);
	}
}

bool GameServer::_StartConfigReloaderThread()
{
	return _configReloaderThread.CreateThread( ConfigReloader::ConfigReloaderThreadFunc, &theConfigReloader );
}

void GameServer::_StopConfigReloaderThread()
{
	DWORD dwThreadID = _configReloaderThread.GetThreadID();
	_configReloaderThread.StopThreadAndWaitDead();
	if (dwThreadID != 0)
	{
		GettheThreadBuffer().ReleaseBuffer(dwThreadID);
	}
}

bool GameServer::_StartPlayerMoveAnalysisThread()
{
	return _playerMoveAnalysisThread.CreateThread( PlayerMoveAnalysis::PlayerMoveAnalysisThreadFunc, &GetPlayerMoveAnalysis() );
}

void GameServer::_StopPlayerMoveAnalysisThread()
{
	DWORD dwThreadID = _playerMoveAnalysisThread.GetThreadID();
	_playerMoveAnalysisThread.StopThreadAndWaitDead();
	if (dwThreadID != 0)
	{
		GettheThreadBuffer().ReleaseBuffer(dwThreadID);
	}
}
