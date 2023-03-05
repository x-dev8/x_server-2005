#include "CenterServer.h"
#include "NetEvent.h"
//#include "NetApi.h"
#include "GameServerManager.h"
#include "LoginServerManager.h"
#include "Config.h"
#include "application_config.h"
//#include "LoginQueue.h"
#include "ClientPeerManager.h"
#include "CenterDataBaseMessage.h"
#include "TeamManager.h"
#include "TimeEventManager.h"
//#include "AntiAddictionSystem.h"
#include "RelationManager.h"
#include "GameTime.h"
#include "PlatformMessageDefine.h"
#include "CenterItemDropManager.h"
#include "ServerStatusManager.h"
#include "AvatarSystemSetting.h"
#include "RelationConfig.h"
#include "ExpStage.h"
#include "MapConfig.h"
#include "DataCenter.h"
#include "MySqlCommunication.h"
#include "TradeCenterInfo.h"
#include "ConsoleApplication.h"
#include "MeNetworkCode.h"
#include "CountryManager.h"
#include "CharacterAttributeConfig.h"
#include "GuildManager.h"
#include "GlobalFunction.h"
#include "ConsignmentManager.h"
#include "FamilyManager.h"
#include "CenterFamily.h"
#include "LevelLimitCenterManager.h"
#include "NetWorkParameterDefine.h"
#include "ColorScreen.h"
#include "CenterTimeHandleManager.h"
#include "LogEventService.h"
#include "BroadCastManager.h"
//xuda #include "WantedManager.h"
#include "QuestEntrust.h"
#include "GameBattleDataManager.h"
#include "ConfigReloader.h"

CWorkThread CenterServer::g_MainLogicThread;
CWorkThread CenterServer::g_SqlServiceThread;
CWorkThread CenterServer::g_configReloaderThread;

CenterServer* CenterServer::pApplicationInstance = NULL;

void CenterServer::Main( void* pParam )
{
    theCenterServer.RunOnce();
}

void CenterServer::SqlMain( void* pParam)
{
    //theCenterServer.GetSqlService().RunOnce();
}
 
CenterServer::CenterServer() : _serviceForGameServer( _netevent/*, NetApi::NetworkIntance() */),
                             //_serviceForLoginServer( _netevent/*, NetApi::NetworkIntance()*/ ),
                             _databaseServerConnector( _netevent/*, NetApi::NetworkIntance() */),
							 _loginserverConnector(_netevent),
                             _lastStatisticsTime( 0 )
{
    memset( &gGameWorldStatistics, 0, sizeof(gGameWorldStatistics));
    _lastRunOnceTime = 0;
    _platformService        = NULL;
    _pToPlatformConnecter   = NULL;
    _connectPlatformStatus  = CPS_TryConnect;
    _lastReconnectTime      = 0;
    _revShutdownCommandTime = 0;
    _revShutdownDelayTime   = 0;
    bCommandCloseAllServer  = false;
    _pOwner                 = NULL;
}

CenterServer::CenterServer( const CenterServer& ) : _serviceForGameServer(_netevent/*, NetApi::NetworkIntance()*/),
                                                // _serviceForLoginServer(_netevent/*, NetApi::NetworkIntance()*/),
                                                 _nLastUpdateLoginInfoTime( HQ_TimeGetTime() ),
                                                 _databaseServerConnector(_netevent/*, NetApi::NetworkIntance()*/),
												 _loginserverConnector(_netevent),
                                                 _lastStatisticsTime( 0 )
                                                 
{
    memset( &gGameWorldStatistics, 0, sizeof(gGameWorldStatistics));    
    _lastRunOnceTime        = 0;
    _pToPlatformConnecter   = NULL;
    _connectPlatformStatus  = CPS_TryConnect;
    _lastReconnectTime      = 0;
    _revShutdownCommandTime = 0;
    _revShutdownDelayTime   = 0;
	_LoginServerPingTime = HQ_TimeGetTime();
}

CenterServer::~CenterServer()
{   
    if( _platformService )
    {
        _platformService->Close();
		network::Listener_release(_platformService);
        //_platformService->Release();
        _platformService = NULL;
    }

    ItrPlatformConnecterContainer it    = _platformConnecters.begin();
    ItrPlatformConnecterContainer itEnd = _platformConnecters.end();

    for (; it != itEnd; ++it)
    {
        /*IMeConnector*/Socketer* pConnetor = it->second;
        if ( pConnetor == NULL )
        { 
			network::Socketer_release(pConnetor);
			//pConnetor->Release();
		}
    }
    _platformConnecters.clear();

    if ( _pToPlatformConnecter )
    { 
		network::Socketer_release(_pToPlatformConnecter);
        /*_pToPlatformConnecter->Release();*/
        _pToPlatformConnecter = NULL;
    }
    _pOwner                   = NULL;
}

CenterServer& CenterServer::GetInstance()
{
    if ( !pApplicationInstance )
    { pApplicationInstance = new CenterServer; }

    return *pApplicationInstance;
}

long CenterServer::Init( ConsoleApplication* pOwner )
{   
    _pOwner = pOwner;
    // ע���Լ�
    ServerData xData;
    xData.SetParentNodeType( ServerDataDefine::Node_Root );
    xData.SetParentID( 0 );
    xData.SetNodeType( ServerDataDefine::Node_Center );
    xData.SetID( 0 );
    xData.SetName( "CenterServer" );
    xData.SetVersion( static_cast< unsigned short >( theApplicationConfig.GetBuildVersion() ) );
    theServerStatusManager.RegisterServer( xData );

    theAvatarSystemSetting;

    // ����һ������������ֵ
    uint32 nResult = theCharacterAttributeConfig.LoadLevelBaseSecondAttribute( CHARACTERBASESECONDATTRIBUTE_FILEPATH );
    if ( RESULT_FAILED(nResult) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",CHARACTERBASESECONDATTRIBUTE_FILEPATH);
        return nResult;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [OK]",CHARACTERBASESECONDATTRIBUTE_FILEPATH);
    }

    nResult = theDataCenter.LoadArmsParamModulus( PARAMMODULUS_FILEPATH );
    if ( RESULT_FAILED(nResult) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",PARAMMODULUS_FILEPATH);
        return nResult;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]",PARAMMODULUS_FILEPATH);
    }

    if( !theExpStage.LoadFromConfig( EXPSTAGE_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",EXPSTAGE_FILEPATH);
        return ER_InitFail;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,EXPSTAGE_FILEPATH);
    }

    if( !theRelationConfig.LoadRelationConfig( RELATIONCONFIG_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",RELATIONCONFIG_FILEPATH);
        return ER_InitFail;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,RELATIONCONFIG_FILEPATH);
    }

    bool bResult = theMapConfig.LoadMapConfig( WORLDMAPCONFIG_FILEPATH );
    CHECK_RETURN( !bResult, ER_InitFail );

    if (!theTradeCenter.LoadResourceConfig( SHOPCENTER_FILEPATH ))
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ",SHOPCENTER_FILEPATH );
        return false;
    }
    else
    {
		theTradeCenter.OnReloadFinished();
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,SHOPCENTER_FILEPATH);
    }

    //bResult = GetTimeEventManager().Load( TIMESCRIPTSLK_FILEPATH );
    //CHECK_RETURN( !bResult, ER_InitFail );
    
    Config& config = Config::GetInstance();

    nResult = theGameServerManager.Init();
    CHECK_RETURN( nResult != ER_Success, ER_InitFail );

    nResult = LoginServerManager::GetInstance().Init();
    CHECK_RETURN( nResult != ER_Success, ER_InitFail );
    
//#ifndef __NEW_LOGIN__
//    nResult = _serviceForLoginServer.Init( config.usListentPortForLoginServer,1024*64,1024*128 /*false, false, msgflag_normal, 1, -1*/ );
//    CHECK_RETURN( nResult != ER_Success, ER_InitFail );
//#endif

    nResult = _serviceForGameServer.Init( config.usListenPortForGameServer,1024*64,1024*128/*false, false, msgflag_normal, 1, -1 */);
    CHECK_RETURN( nResult != ER_Success, ER_InitFail );

    nResult = _databaseServerConnector.Init( config.szDatabaseServerIP , config.usDatabaseServerPort);
    CHECK_RETURN( nResult != ER_Success, ER_InitFail );

	nResult = _loginserverConnector.Init(config.szLoginServerIP,config.usLoginServerPort);
	CHECK_RETURN(nResult != ER_Success,ER_InitFail);

    // ����iocp�����߳�
  /*  bResult = NetApi::NetworkIntance().StartIoCompletionPort( 1, -1 );
    CHECK_RETURN( !bResult, ERNC_SocketStartIOCPError );*/
    
    // Listenƽ̨
	_platformService = network::Listener_create(); /*GetMeNetwork().CreateMeSocket();*/
    CHECK_RETURN( _platformService == NULL, ER_InitFail );

    if(/* !_platformService->Create( config.listentPortForPlatform ) || */!_platformService->Listen(config.listentPortForPlatform,5) )
    {
		 LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ","Listenƽ̨");
		return ER_InitFail;
	}

	if (config.LogServerService)
	{
		theLogEventService.Init(config.LogServerHost,config.LogServerPort,config.server_id,config.LogServerService);
	}
    // ����ƽ̨
	//_pToPlatformConnecter = network::Socketer_create();/*GetMeNetwork().CreateMeConnector();*/
 //   if ( !_pToPlatformConnecter )
 //   { return ER_InitFail; }

    // ��mysqlͨѶ�߳�
    if ( ER_Success != theMysqlCommunication.Init( config.roleDbName          , config.roleHost          , config.roleDbPort      , config.roleUID           , config.rolePwd          ,
                                                   //config.billingDbName       , config.billingHost       , config.billingDbPort   , config.billingUID        , config.billingPwd       ,
                                                   config.platformDbName      , config.platformHost      , config.platformDbPort  , config.platformUID       , config.platformPwd      
                                                   //config.strPlatformRPCDbName, config.strPlatformRPCHost, config.nPlatformRPCPort, config.strPlatformRPCUser, config.strPlatformRPCPwd 
												   ) )
    {
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ","��mysqlͨѶ�߳�");
		return ER_InitFail; 
	}

    // �������߼��߳�
    bResult = CenterServer::g_MainLogicThread.CreateThread( CenterServer::Main );
    CHECK_RETURN( !bResult, ER_CreateWorkThreadFail);

	// �����ȼ����߳�
	bResult = CenterServer::g_configReloaderThread.CreateThread( ConfigReloader::ConfigReloaderThreadFunc, &theConfigReloader );
	CHECK_RETURN( !bResult, ER_CreateWorkThreadFail);

#ifdef __NEW_LOGIN__
    //nResult = _serviceSql.Init();    
    //CHECK_RETURN( nResult, ER_SqlServiceFail);
    
    /*bResult = CenterServer::g_SqlServiceThread.CreateThread( CenterServer::SqlMain );
    CHECK_RETURN( !bResult, ER_SqlServiceFail );*/
#endif

    RecordTime::SaveRecordTime( _dwPartitionLogTile );      // ��Ϸ�������� �ָ�LOG�ļ�ʱ��
    //_dwPartitionLogTile = 0;
    return nResult;
}

long CenterServer::RunOnce()
{ 
	network::net_run();

    if ( _lastRunOnceTime = 0 )
    { _lastRunOnceTime = HQ_TimeGetTime();}

	//uint32 temp_time = HQ_TimeGetTime();
	//uint32 temp_cost = HQ_TimeGetTime() - temp_time;
	//printf("cost temp time:%d\n",temp_cost);

    uint32 costTime = HQ_TimeGetTime() - _lastRunOnceTime;
    _lastRunOnceTime = HQ_TimeGetTime();

	//printf("cost all time:%d\n ",costTime);

	//temp_time = HQ_TimeGetTime();
	//
    RunDatabaseServerCommunication();
	//
	//temp_cost = HQ_TimeGetTime() - temp_time;
	//printf("RunDatabaseServerCommunication cost temp time:%d\n",temp_cost);

	//temp_time = HQ_TimeGetTime();
	//��login server��������
	PingLoginServer();

	RunLoginServerCommunication();
	//
	//temp_cost = HQ_TimeGetTime() - temp_time;
	//printf("RunLoginServerCommunication cost temp time:%d\n",temp_cost);

	//temp_time = HQ_TimeGetTime();
	//
    _serviceForGameServer.RunOnce();
	//temp_cost = HQ_TimeGetTime() - temp_time;
	//printf("_serviceForGameServer cost temp time:%d\n",temp_cost);

//#ifndef __NEW_LOGIN__
//    _serviceForLoginServer.RunOnce();
//#endif

	//temp_time = HQ_TimeGetTime();
	//
    theMysqlCommunication.Update();
	//
	//temp_cost = HQ_TimeGetTime() - temp_time;
	//printf("theMysqlCommunication cost temp time:%d\n",temp_cost);

    TryToConnectPlatform();

	//temp_time = HQ_TimeGetTime();
    // ƽ̨accept
    _PlatformAcceptRun();

    // ƽ̨������Ϣ����
    _RecvPlatformMessageRun();

    // ƽ̨��Ϣ��ȡ
    _ProcessPlatformMessageRun();

    _UpdateLoginInfo();
    //
	//temp_cost = HQ_TimeGetTime() - temp_time;
	//printf("_UpdateLoginInfo cost temp time:%d\n",temp_cost);
//#ifdef __NEW_LOGIN__
//    ClientPeerManager::GetInstance().ProcessLoginClieetPeers();
//
//    _ProcessSqlMessage();
//#endif
	//temp_time = HQ_TimeGetTime();
	ClientPeerManager::GetInstance().ProcessLoginClieetPeers();
	//temp_cost = HQ_TimeGetTime() - temp_time;
	//printf("ProcessLoginClieetPeers cost temp time:%d\n",temp_cost);

    /*
    if ( Config::GetInstance().isOpenAntiAddictionSystem)
    { GetAntiAddictionSystem().Update();}    
    */

	//temp_time = HQ_TimeGetTime();
    if(_databaseServerConnector.GetConnectState() == TcpClient::CS_Connected )
    {
        //
    }
	//temp_cost = HQ_TimeGetTime() - temp_time;
	//printf("_databaseServerConnector cost temp time:%d\n",temp_cost);

	//temp_time = HQ_TimeGetTime();
    // ��Ʒ��ֵ���Զ��洢
    theCenterItemDropManager.RunUpdate( HQ_TimeGetTime() );

    // ����
    theCenterCountryManager.RunUpdate( HQ_TimeGetTime() );

    // ����
    theConsignmentManager.RunUpdate( HQ_TimeGetTime() );

    // �Ȱѹ�ϵ����
    theCenterRelationManager.RunUpdate( HQ_TimeGetTime() );

    // ����
    theCenterGuildManager.RunUpdate( HQ_TimeGetTime() );

	// ����
	theCenterFamilyManager.RunUpdate( HQ_TimeGetTime() );

    // ϵͳ����
    theCenterSysVarManager.RunUpdate( HQ_TimeGetTime() );

	//
	theCenterTimeHandleManager.Update(HQ_TimeGetTime() );

    // TokenCenter::Instance().AutoRestore();

    theCenterTeamManager.RunTeamManagerUpdate( HQ_TimeGetTime(), TeamDefine::SendToAllGame );

    theServerStatusManager.RunUpdate( HQ_TimeGetTime() );

	theBroadCastManager.RunUpdate( HQ_TimeGetTime() );

	//ͨ����
	//xuda theCenterWantedManager.RunUpdate( HQ_TimeGetTime() );

	//����ί��
	theCenterQuestEntrustManager.RunUpdate( HQ_TimeGetTime() );

	theCenterCampBattleDataManager.RunUpdate( HQ_TimeGetTime() );

    GetTimeEventManager().Update( costTime );

	//temp_cost = HQ_TimeGetTime() - temp_time;
	//printf("GetTimeEventManager cost temp time:%d\n",temp_cost);
//
	//temp_time = HQ_TimeGetTime();
    // ƽ̨����Ϣ����
    _SendPlatformMessageRun();

    // ���
    theClientPeerManager.Update();

	// ���������ظ���
	theConfigReloader.Update();

    if (theTradeCenter.CheckReloaded())
    {
		S2SUpdateTradeShopConfig msg;
		msg.Clone( (uint8*)theTradeCenter.gszFileBuffer, theTradeCenter.gnFileBufferSize, false );
		theGameServerManager.SendMessageToGameServers( &msg ,CHARACTERSERVERID);
    }
    
	// �ȼ���ӡ
	//theLevelLimitCenterManager.RunUpdate(HQ_TimeGetTime());

    _Statistics();

    CheckForServerExit();

	//temp_cost = HQ_TimeGetTime() - temp_time;
	//printf("CheckForServerExit cost temp time:%d\n",temp_cost);
	//printf("over\n");
    // PartitionLogFile();             // ����Log�ļ������ڷֿ�
	//�������־
	theLogEventService.RunOneStep();
    /*NetApi::*/Sleep( 1 );
    return ER_Success;
}

void CenterServer::UnInit()
{
    // Config::GetInstance().Save();

    theGameServerManager.UnInit();
    LoginServerManager::GetInstance().UnInit();

    _serviceForGameServer.UnInit();

//#ifndef __NEW_LOGIN__
//    _serviceForLoginServer.UnInit();
//#endif
    // �ر�sql�����߳�
    CenterServer::g_SqlServiceThread.StopThreadAndWaitDead();

    // �ر��߼��߳�
    CenterServer::g_MainLogicThread.StopThreadAndWaitDead();
    
    /*NetApi::NetworkIntance().StopIoCompletionPort();
    NetApi::NetworkIntance().SocketCleanUp(); */
	network::net_release();
}

void CenterServer::CloseConnection( EServerType st, NetClient* pNetClient )
{
    switch ( st )
    {
    case ST_GameServer:
        _serviceForGameServer.CloseConnection( pNetClient );
        break;    
//#ifndef __NEW_LOGIN__
//    case ST_LoginServer:
//        _serviceForLoginServer.CloseConnection( pNetClient );
//        break;
//#endif
    default:
        // ToLog( false && "Unknown Server Type");
        break;
    }
}

void CenterServer::AddLoginInfo( __int64 nSessionKey, const SLoginInfoBase& lis )
{
    _loginInfos[nSessionKey] = lis;
}

void CenterServer::PingLoginServer()
{
	static unsigned long dwtimetemp = HQ_TimeGetTime();
	if (_loginserverConnector.GetConnectState() == TcpClient::CS_Connected)
	{
		if(_lastRunOnceTime - _LoginServerPingTime >= eS2S_OverTime)
		{
			/*_loginserverConnector.SetConnectState(TcpClient::CS_TryConnect);*/
			_loginserverConnector.Reset();
		}
		else
		{
			if (_lastRunOnceTime - dwtimetemp > eS2S_PingTime)
			{
				dwtimetemp = _lastRunOnceTime;
				MsgPingServer msg;
				if (_loginserverConnector.Send(&msg) != 0)
				{
					_loginserverConnector.SetConnectState(TcpClient::CS_TryConnect);
				}
				//printf("pingmsg:1,center server send to login server:%d\n",HQ_TimeGetTime());
			}
		}
	}
}

void CenterServer::RunLoginServerCommunication()
{
	if ( _loginserverConnector.GetConnectState() != TcpClient::CS_Connected )
	{
		_loginserverConnector.TryConnect();
		if ( _loginserverConnector.GetConnectState() == TcpClient::CS_Connected )
		{
			SetLoginServerPingTime(HQ_TimeGetTime());
			//MsgRegisterServerReq xReq;
			//_databaseServerConnector.Send( &xReq );     // ����ϢҪDataBase ע�ᵽCenterServer��

			//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Connect DBServer[%s:%d] Success!", _databaseServerConnector.GetIP().c_str(), _databaseServerConnector.GetPort());
		}
	}

	if ( _loginserverConnector.GetConnectState() == TcpClient::CS_Connected )
	{	
		_loginserverConnector._Receive();
		long result = _loginserverConnector.Update(); 
		if ( result!=ER_Success)
		{
			// ToLog( false );
		}
		_loginserverConnector._Send();
	}
}

void CenterServer::RunDatabaseServerCommunication()
{
    if ( _databaseServerConnector.GetConnectState() != TcpClient::CS_Connected )
    {
        _databaseServerConnector.TryConnect();
        if ( _databaseServerConnector.GetConnectState() == TcpClient::CS_Connected )
        {
            //CS2DBRegiseterDBServerInfoReq msg;
            //strncpy_s( msg.szDBServerName, "DBServer", sizeof(msg.szDBServerName)-1);
            //msg.btReset   = CS2DBRegiseterDBServerInfoReq::ROT_REPLACE;
            //msg.nServerId = Config::GetInstance().CenterServerId;
            //SendMessageToDb( &msg );
            //theGameWorld.ProcessGameStageOp();
            //theRunTimeData.OnUpdateBurthen();

            MsgRegisterServerReq xReq;
            _databaseServerConnector.Send( &xReq );     // ����ϢҪDataBase ע�ᵽCenterServer��

            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Connect DBServer[%s:%d] Success!", _databaseServerConnector.GetIP().c_str(), _databaseServerConnector.GetPort());
        }
    }

    if ( _databaseServerConnector.GetConnectState() == TcpClient::CS_Connected )
    {
		_databaseServerConnector._Receive();
        long result = _databaseServerConnector.Update(); 
        if ( result!=ER_Success)
        {
            // ToLog( false );
        }
		_databaseServerConnector._Send();
    }
}

uint32 CenterServer::SendMessageToLogin( Msg* pMessage )
{
	CHECK_RETURN( pMessage==NULL, ER_NullPointer );
	if ( _loginserverConnector.GetConnectState() == TcpClient::CS_Connected  )
	{ return _loginserverConnector.Send( pMessage ); }

	return ER_Failed;
}

uint32 CenterServer::SendMessageToDb( Msg* pMessage )
{
    CHECK_RETURN( pMessage==NULL, ER_NullPointer );
    if ( _databaseServerConnector.GetConnectState() == TcpClient::CS_Connected  )
    { return _databaseServerConnector.Send( pMessage ); }

    return ER_Failed;
}

uint32 CenterServer::SendMessageToPlatform( uint32 platformId, Msg* pMessage )
{
    ItrPlatformConnecterContainer it = _platformConnecters.find( platformId );
    
    if ( it == _platformConnecters.end())
    { return ER_Failed; }

    /*IMeConnector*/Socketer* pConnector = it->second;
    if ( pConnector == NULL )
    { return ER_Failed; }
    pConnector->SendMsg( pMessage );

    return ER_Success;
}

uint32 CenterServer::SendMessageToPlatform( Msg* pMessage )
{
    if ( _pToPlatformConnecter == NULL||_pToPlatformConnecter->IsClose())
    { return ER_Failed; }
    _pToPlatformConnecter->SendMsg( pMessage );

    return ER_Success;
}

void CenterServer::_UpdateLoginInfo()
{
    if ( GameTime::IsPassCurrentTime( _nLastUpdateLoginInfoTime, LOGININFO_UPDATETIME_INTERVAL ) )
    {
        ItrLoginInfoContainer itr = _loginInfos.begin();
        while (itr != _loginInfos.end())
        {
            //�趨����IP���ӵ�ʱ��Ϊʮ����
            if ( GameTime::IsPassCurrentTime( itr->second.LoginTime, ALLOW_CONNECT_GATESERVER_TIME ) )
            {
                itr = _loginInfos.erase(itr);
                continue;
            }
             ++itr;
        }
        _nLastUpdateLoginInfoTime = HQ_TimeGetTime();
    }
}

void CenterServer::_ProcessSqlMessage()
{    
	//KickMessage rKickMessage;

 //   // �ʺ���������� һ��
 //   while ( _serviceSql.GetKickQueryMessage(rKickMessage, false ) )
 //   {   
 //       ClientPeer* pClient = theClientPeerManager.GetClientPeer( rKickMessage.nGuid );
 //       if ( pClient != NULL)
 //       { // �ɺŴ���
 //           LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s:%s] GetKick KR_AccountRepeat", rKickMessage.nGuid, pClient->GetLoginInfo().szAccount,pClient->GetLoginInfo().SessionKey );

 //           uint32 nResult = theClientPeerManager.KickClientPeer( pClient, S2SMsgKickChar::KR_AccountRepeat );
 //           if ( nResult != ER_Success )
 //           { // ���쳣 ����ɾOnline ��ֹ����
 //               theCenterServer.NotifyGLSAccountSafeOffLine( rKickMessage.nGuid, pClient->GetLoginInfo().szAccount );
 //               LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"account[%u:%s:%s] GetKick KR_AccountRepeat �쳣[%d] ", rKickMessage.nGuid, pClient->GetLoginInfo().szAccount,pClient->GetLoginInfo().SessionKey, nResult );
 //           }            
 //       }
 //       else
 //       { // ���ڵ�¼���� �������ٵ�¼��ѡ�˷�����
 //           if ( theClientPeerManager.GetClientPeerFromLoginQueue( rKickMessage.nGuid ))
 //           { NotifyGLSValidKick( rKickMessage.nGuid, rKickMessage.szPassport); } // �����LoginCache������
 //           else
 //           { NotifyGLSPlayerExit( rKickMessage.nGuid, rKickMessage.szPassport ); }
 //       }
 //   }

 //   // �ʺ���������� һ��û�гɹ� ��ʱ�Ĵ���
 //   //while ( _serviceSql.GetKickQueryMessage(rKickMessage, true ) )
 //   //{   
 //   //    ClientPeer* pClient = theClientPeerManager.GetClientPeer( rKickMessage.nGuid );
 //   //    if ( pClient != NULL)
 //   //    { // �ɺŴ���
 //   //        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s:%s] GetKick KR_AccountRepeat ����", rKickMessage.nGuid, pClient->GetLoginInfo().szAccount,pClient->GetLoginInfo().SessionKey );

 //   //        uint32 nResult =  theClientPeerManager.KickClientPeer( pClient, S2SMsgKickChar::KR_AccountRepeat );
 //   //        if ( nResult != ER_Success )
 //   //        { // ���쳣 ����ɾOnline ��ֹ����
 //   //            theCenterServer.NotifyGLSAccountSafeOffLine( rKickMessage.nGuid, pClient->GetLoginInfo().szAccount );
 //   //            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"account[%u:%s:%s] GetKick KR_AccountRepeat ���� �쳣[%d] ", rKickMessage.nGuid, pClient->GetLoginInfo().szAccount,pClient->GetLoginInfo().SessionKey, nResult );
 //   //        }
 //   //    }
 //   //}
 //   
 //   // ��sql���߼��ŵ�������
 //   SqlMessage rOnlineMessage;
 //   while ( _serviceSql.GetOnlineQueryMessage(rOnlineMessage) )
 //   {
 //       ClientPeer* pClient = theClientPeerManager.GetClientPeer( rOnlineMessage.Guid );
 //       if ( pClient != NULL)
 //       { // �ɺŴ���
 //           LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "account[%u:%s:%s] (GetOnlineQueryMessage) �쳣 �����½��Ȼ����", rOnlineMessage.Guid, pClient->GetLoginInfo().szAccount, pClient->GetLoginInfo().SessionKey );
 //           uint32 nResult = theClientPeerManager.KickClientPeer( pClient, S2SMsgKickChar::KR_AccountRepeat );
 //           if ( nResult != ER_Success )
 //           { // ���쳣 ����ɾOnline ��ֹ����
 //               theCenterServer.NotifyGLSAccountSafeOffLine( rOnlineMessage.Guid, pClient->GetLoginInfo().szAccount );
 //               LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"account[%u:%s:%s] (GetOnlineQueryMessage) GetKick KR_AccountRepeat �쳣[%d] ", rOnlineMessage.Guid, pClient->GetLoginInfo().szAccount,pClient->GetLoginInfo().SessionKey, nResult );
 //           }
 //           return;
 //       }

 //       //��ȡgateserver����Ϣ
 //       long lResult = theClientPeerManager.AddLoginClientPeer( rOnlineMessage.Guid, rOnlineMessage.Passport, rOnlineMessage.SessionKey, 
 //                                                                rOnlineMessage.sPassword, /*rOnlineMessage.Seed,*/ rOnlineMessage.isWallow );
 //       
 //       if ( ER_Success != lResult )
 //       {   
 //           LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING," ���Ѵ˵�¼�û�ʧ�� [%d][%s] Error[%d]",  rOnlineMessage.Guid,  rOnlineMessage.Passport, lResult);
 //       }
 //   }
}

void CenterServer::NotifyGLSAccountSafeOffLine( unsigned long accountId, const char* accountName )
{
    /*SqlMessage sqlMessage;
    sqlMessage.nMessageId = SqlMessage::ESM_KickSuccess;
    sqlMessage.Guid       = accountId;
    strncpy_s (sqlMessage.Passport, sizeof( sqlMessage.Passport ), accountName, sizeof( sqlMessage.Passport ) - 1 );*/
    //_serviceSql.PushResult( sqlMessage );
}

void CenterServer::NotifyGLSValidKick( unsigned long accountId, const char* accountName )
{
   /* SqlMessage sqlMessage;
    sqlMessage.nMessageId = SqlMessage::ESM_KickInValid;
    sqlMessage.Guid       = accountId;
    strncpy_s (sqlMessage.Passport, sizeof( sqlMessage.Passport ), accountName, sizeof( sqlMessage.Passport ) - 1 );*/
   // _serviceSql.PushResult( sqlMessage );
}

void CenterServer::NotifyGLSPlayerExit( unsigned long accountId, const char* accountName, uint32 blockTime )
{
	if (blockTime == 0)
	{
		return;
	}
	MsgS2SBlockAccount _block;
	strncpy_s (_block.name, sizeof( _block.name ), accountName, sizeof(_block.name) - 1);
	_block.blocktime = blockTime;
	_block.guid = accountId;
	_loginserverConnector.Send(&_block);
    //GetSqlService().PushResult( sqlMessage );
}

void CenterServer::_Statistics()
{
    if ( _lastStatisticsTime == 0)
    { _lastStatisticsTime = HQ_TimeGetTime();}

    if ( !GameTime::IsPassCurrentTime( _lastStatisticsTime, ECD_StatisticsTimeInterval ) )
    { return; }

    _lastStatisticsTime = HQ_TimeGetTime();

	if (!theGameServerManager.LogOnlineInfo(gGameWorldStatistics.loginClientPeer, gGameWorldStatistics.activeExitClientPeer, gGameWorldStatistics.kicklExitClientPeer,
		ClientPeerManager::GetInstance().ClientPeerSize()))
	{
		LOG_MESSAGE( STATISTICSOBJECT, LOG_PRIORITY_INFO,"��¼����\t%u\t�����˳�����\t%u\t�����˳�����\t%u\t��������������\t%u",
			gGameWorldStatistics.loginClientPeer, gGameWorldStatistics.activeExitClientPeer, gGameWorldStatistics.kicklExitClientPeer,
			ClientPeerManager::GetInstance().ClientPeerSize());

		memset( &gGameWorldStatistics, 0, sizeof(gGameWorldStatistics));

		theGameServerManager.Statistics();
	}    
}

void CenterServer::_PlatformAcceptRun()
{
    BEGINFUNCPERLOG( "platform accept" );
    int iAccept = 0;
    const int iAcceptMax = 10;    
    while( _platformService->/*HasData*/CanAccept() && iAccept < iAcceptMax )
    { //���ܿͻ��˵�����
        if ( !_AcceptPlatform())
        { break; }
        ++iAccept;
    }
    ENDFUNCPERLOG( "platform accept" );
}

bool CenterServer::_AcceptPlatform()
{
    if (_platformConnecters.size() >= ECD_MaxPlatformCount)
    { return false; }
    
    /*IMeSocket* pSocket = GetMeNetwork().CreateMeSocket();
    if ( !pSocket )
    { return false; }*/

	Socketer* pSocket = _platformService->Accept();
	if ( !pSocket )
	{ return false; }
    /*if( !_platformService->Accept( pSocket ) )
    { goto FailProcess; }*/
    
    /*IMeConnector* pPlatformConnector = GetMeNetwork().CreateMeConnector();
    if( !pPlatformConnector )
    { goto FailProcess;}

    pPlatformConnector->SetSocket( pSocket );
    pPlatformConnector->SetNormalLevelCast( 20000 );
    pPlatformConnector->SetLowLevelCast(10000);
    pPlatformConnector->SetMaxQueueMsgNum( IMeConnector::ET_InQueue, -1 );
    pPlatformConnector->SetMaxQueueMsgNum( IMeConnector::ET_OutQueue, -1 );*/
    _platformConnecters.insert( PlatformConnecterContainer::value_type( _GetPlatClientID(),pSocket/*pPlatformConnector*/ ));
    
    return true;

FailProcess:
    if ( pSocket )
    {
        pSocket->Close();
		network::Socketer_release(pSocket);
        //pSocket->Release();
        pSocket = NULL;
    }

    //if ( pPlatformConnector )
    //{
    //    pPlatformConnector->Close();
    //    pPlatformConnector->Release();
    //    pPlatformConnector = NULL;
    //}
    return false;
}

void CenterServer::_RecvPlatformMessageRun()
{   
    // Listen
    if( !_platformConnecters.empty())
    {   
        ItrPlatformConnecterContainer it    = _platformConnecters.begin();
        ItrPlatformConnecterContainer itEnd = _platformConnecters.end();

        for (; it != itEnd; )
        {
            /*IMeConnector*/Socketer* pConnetor = it->second;
            if ( pConnetor == NULL )
            {
                it = _platformConnecters.erase( it );
                continue;
            }

            if( pConnetor->IsClose() )
            {
				network::Socketer_release(pConnetor);
                //pConnetor->Release();

                it = _platformConnecters.erase( it );
                continue;
            }

            /*pConnetor->TryRecvThirdParty();*/
			pConnetor->CheckRecv();
            ++it;
        }
    }
    
    // connect
    switch ( _connectPlatformStatus )
    {
    case CPS_Normal:
        {
            
            if(!_pToPlatformConnecter||_pToPlatformConnecter->IsClose() )
            {
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "��Platform �Ͽ�����");
                _connectPlatformStatus = CPS_ReConnect;
                //_pToPlatformConnecter->Reset();
                return;
            }

			_pToPlatformConnecter->CheckRecv();

            /*if(  _pToPlatformConnecter->GetInQueueSize() >= 90000 || _pToPlatformConnecter->GetOutQueueSize() >= 90000)
            {
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "��Ϊ��Ϣ̫����Platform�Ͽ�����, in[%d] out[%d]", _pToPlatformConnecter->GetInQueueSize(), _pToPlatformConnecter->GetOutQueueSize());
                
                _connectPlatformStatus = CPS_ReConnect;
                _pToPlatformConnecter->Reset();
                return;
            }*/
        }
        break;
    }
}

void CenterServer::_SendPlatformMessageRun()
{
    // Listen
    if( !_platformConnecters.empty())
    {
        ItrPlatformConnecterContainer it    = _platformConnecters.begin();
        ItrPlatformConnecterContainer itEnd = _platformConnecters.end();

        for (; it != itEnd; ++it)
        {
            /*IMeConnector*/Socketer* pConnetor = it->second;
            if ( pConnetor == NULL)
            { continue;}

            if ( !pConnetor->IsClose() )
            { /*pConnetor->TrySendThirdParty();*/
				pConnetor->CheckSend();
			}
        }
    }

    // connect
    switch ( _connectPlatformStatus )
    {
    case CPS_Normal:
        {
            if( !_pToPlatformConnecter->IsClose() )
            { _pToPlatformConnecter->CheckSend(); }
            else
            {
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "��Platform �Ͽ����� 1");
                _connectPlatformStatus = CPS_ReConnect;
                /*_pToPlatformConnecter->Reset();*/
            }
        }
        break;
    }
}
#define MAX_PLATFORM_MSG_COUNT 30 //ÿ֡����30��ƽ̨��Э��
void CenterServer::_ProcessPlatformMessageRun()
{
    // Listen
    if( !_platformConnecters.empty())
    {
        ItrPlatformConnecterContainer it    = _platformConnecters.begin();
        ItrPlatformConnecterContainer itEnd = _platformConnecters.end();
        for(; it != itEnd; ++it)
        {   
            /*IMeConnector*/Socketer* pConnetor = it->second;
            if ( pConnetor == NULL )
            { continue; }

            uint32 clientId = it->first;
            Msg* pMsg = NULL;

            while( pMsg = pConnetor->GetMsg() )
            {
                MessageType type = pMsg->GetType();

                PLATFORM_MESSAGE_MAPPING_BEGIN
                    //PLATFORM_MESSAGE_HANDLE( clientId, PFMSG_ADDPOINTS,            HandleAddPoint                   );
                    //PLATFORM_MESSAGE_HANDLE( clientId, PFMSG_GMKICKPLAYER_REQ,     HandleGMKickPlayerReq            );
                    PLATFORM_MESSAGE_HANDLE( clientId, PFMSG_GMBROADCAST_REQ,      HandleGMBroadcastReq             );
                    //PLATFORM_MESSAGE_HANDLE( clientId, PFMSG_CREATECHAR_REQ,       HandleCreateCharReq              );
                    PLATFORM_MESSAGE_HANDLE( clientId, PFMSG_SERVERSTATUS_REQ,     HandleServerStatusReq            );
                    PLATFORM_MESSAGE_HANDLE( clientId, PFMSG_ADDITEM_REQ,          HandleMsgPFAddItemReq            );
                    PLATFORM_MESSAGE_HANDLE( clientId, PFMSG_RELOADTRADESHOP_REQ,  HandleMsgPFGMReloadTradeShop     );
                    PLATFORM_MESSAGE_HANDLE( clientId, PFMSG_SHUTDOWNSERVERS_REQ,  HandleMsgPFGMShutdownServers     );
                    PLATFORM_MESSAGE_HANDLE( clientId, PFMSG_CHANGEMAPEXPRATE_REQ, HandleMsgPFGMChangeMapExpRateReq );
                    PLATFORM_MESSAGE_HANDLE( clientId, PFMSG_GMOPCHATONOFF,        HandleMsgPFGMOPChatOnOff         );
                PLATFORM_MESSAGE_MAPPING_END
            }
        }
    }

	//ƽ̨������
	if (_pToPlatformConnecter&&!_pToPlatformConnecter->IsClose())
	{
		int i = 0;
		Msg* pPlatformMsg = NULL;
		while(pPlatformMsg = _pToPlatformConnecter->GetMsg())
		{
			switch(pPlatformMsg->GetType())
			{
			case PFMSG_GMBROADCAST_REQ:
				{
					PlatFormMsgGMBroadcastReq(pPlatformMsg);
				}
				break;
			case PFMSG_SENDMAIL:
				{
					PlatFormMsgSendMailReq(pPlatformMsg);
				}
				break;
			case PFMSG_GMOPCHATONOFF:
				{
					PlatFormMsgGMOPChatOnOf(pPlatformMsg);
				}
				break;
			case PFMSG_SHUTDOWNSERVERS_REQ:
				{
					PlatFormMsgShutDownServers(pPlatformMsg);
				}
				break;
			case PFMSG_MODIFY_ERROR:
				{
					PlatFormMsgModifyError(pPlatformMsg);
				}
				break;
			case PFMSG_BANACCOUNT:
				{
					PlatFormBanAccount(pPlatformMsg);
				}
				break;
			case PFMSG_BANMACADRESS:
				{
					PlatFormBanMacAdress(pPlatformMsg);
				}
				break;
			case PFMSG_ACK_EPISTARPOINT://���յ�platform�ķ�����Ԫ��ɹ���Ϣ
				{
					PlatFormEpistarPointAck(pPlatformMsg);
				}
				break;
			default:
				break;
			}
			i++;
			if (i >= MAX_PLATFORM_MSG_COUNT)
			{
				break;
			}
		}
	}	
    // Connect
    //MsgThirdParty* pMsg = NULL;
    //while( pMsg = _pToPlatformConnecter->GetMsgThirdParty() )
    //{
    //    MessageType messageType = pMsg->type;

    //    switch ( messageType )
    //    {
    //    case PFMSG_INFOQUERY_ACK:
    //        {
    //            MsgPFInfoQueryAck* pMessage = (MsgPFInfoQueryAck*)pMsg;                

    //            CS2GSDrawFromPlatformAck msg;
    //            msg.drawType = pMessage->querType;
    //            msg.result   = pMessage->result;
    //            msg.guid     = pMessage->guid;
    //            theGameServerManager.SendMsgToSingleByAccountId( &msg, pMessage->guid );
    //        }
    //        break;
    //    //case PFMSG_JINPIAO_ACK:
    //    //    {
    //    //        MsgPFJinPiaoAck* pMessage = (MsgPFJinPiaoAck*)pMsg;
    //    //        
    //    //        CS2GSDrawFromPlatformAck msg;
    //    //        msg.drawType = GS2CSDrawFromPlatformQuery::CT_JinPiaoCard;
    //    //        msg.result = pMessage->result;
    //    //        msg.guid   = pMessage->guid;
    //    //        msg.value  = pMessage->points;
    //    //        theGameServerManager.SendMsgToSingleByAccountId( &msg, pMessage->guid );
    //    //    }
    //    //    break;
    //    //case PFMSG_POINT_ACK:
    //    //    {
    //    //        MsgPFPointAck* pMessage = (MsgPFPointAck*)pMsg;
    //    //        
    //    //        CS2GSDrawFromPlatformAck msg;
    //    //        msg.drawType = GS2CSDrawFromPlatformQuery::CT_BackPoints;
    //    //        msg.result = pMessage->result;
    //    //        msg.guid   = pMessage->guid;
    //    //        msg.value  = pMessage->points;
    //    //        theGameServerManager.SendMsgToSingleByAccountId( &msg, pMessage->guid );
    //    //    }
    //    //    break;
    //    //case PFMSG_ITEMACK:
    //    //    {
    //    //        MsgPFItemAck* pMessage = (MsgPFItemAck*)pMsg;                

    //    //        CS2GSDrawFromPlatformAck msg;
    //    //        msg.drawType = GS2CSDrawFromPlatformQuery::CT_XinShouItem;
    //    //        msg.result = pMessage->result;
    //    //        msg.guid   = pMessage->guid;
    //    //        theGameServerManager.SendMsgToSingleByAccountId( &msg, pMessage->guid );
    //    //    }
    //    //    break;
    //    default:
    //        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "Platform����Ļذ� δ֪Id[%d]", messageType );
    //        break;
    //    }
    //}
}

uint32 CenterServer::_GetPlatClientID()
{
    uint32 nID = theRand.rand32()%1000000 + 1000000;
    while( _platformConnecters.find(nID) != _platformConnecters.end() )
    { nID = theRand.rand32()%1000000 + 1000000;}
    return nID;
}

void CenterServer::TryToConnectPlatform()
{
	if (!theConfig.platform_need)
	{
		return;
	}

    if ( !_pToPlatformConnecter )
    {
		_pToPlatformConnecter = network::Socketer_create();        
    }

    switch( _connectPlatformStatus )
    {
    case CPS_TryConnect:
        {   
            // ��ҪƵ��Connect
			if ( _lastReconnectTime != 0 && !GameTime::IsPassCurrentTime( _lastReconnectTime, ECD_ReconnectPlatformTimeInterval ) )
			{ return; }

			if( _pToPlatformConnecter->Connect( theConfig.platformIp, theConfig.platformPort) )
			{
				LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Connect Platform[%s:%d] Success", theConfig.platformIp, theConfig.platformPort );
				_connectPlatformStatus = CPS_Normal;
				/*_pToPlatformConnecter->SetMaxQueueMsgNum( IMeConnector::ET_InQueue, -1 );
				_pToPlatformConnecter->SetMaxQueueMsgNum( IMeConnector::ET_OutQueue, -1 );*/
				_lastReconnectTime = 0;

				MsgC2PTellServerid msg;
				msg.server_id = theConfig.server_id;
				_pToPlatformConnecter->SendMsg(&msg);
			}
			else
			{ // ����ʧ��
				_lastReconnectTime = HQ_TimeGetTime();
			}
        }
        break;
    case CPS_ReConnect:
        {  
            CreateToConnectPlatformSocket();
            _connectPlatformStatus = CPS_TryConnect;
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Begin ReConnect Platform");
        }
        break;
    }
}

uint32 CenterServer::CreateToConnectPlatformSocket()
{
	if (_pToPlatformConnecter)
	{
		_pToPlatformConnecter->Close();
		Socketer_release(_pToPlatformConnecter);
		_pToPlatformConnecter = NULL;
	}
    //if( _pToPlatformConnecter->GetSocket()->Create() )
    //{
    //    IMeSocket* pSocket = GetMeNetwork().CreateMeSocket();
    //    //���ܸ��ϴε�socketһ��
    //    if( !_pToPlatformConnecter->CheckIsDifferentSocket() )
    //    {            
    //        if( !pSocket->Create( ))
    //        {
    //            pSocket->Release();
    //            _pToPlatformConnecter->GetSocket()->Close();
    //            return ER_Failed;
    //        }
    //        else
    //        {
    //            _pToPlatformConnecter->GetSocket()->Close();
    //            _pToPlatformConnecter->SetSocket( pSocket );
    //            return ER_Success;
    //        }
    //    }
    //    return ER_Success;
    //}    
    return ER_Failed;
}

void CenterServer::CheckForServerExit()
{
    if ( bCommandCloseAllServer )
    {
        MsgPFGMShutdownServersReq msg;
        msg.delayTime = 60;
        HandleMsgPFGMShutdownServers( 0, &msg );
        bCommandCloseAllServer = false;
    }

    // ���ط�ʱ��
    if ( _revShutdownCommandTime != 0 && GameTime::IsPassCurrentTime( _revShutdownCommandTime, ( _revShutdownDelayTime + 5 ) * ONE_SEC ))
    { 
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "�ط�ʱ��(%u:%u)��,��ʼ�ط�...",_revShutdownCommandTime, _revShutdownDelayTime);
        _pOwner->SetExitFlag();
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "���������԰�ȫ�˳�");
        _revShutdownCommandTime = 0;
        _revShutdownDelayTime   = 0;
		COLOR_MESSAGE( COLOR_GREEN, "[���������԰�ȫ�˳�] \n" );
    }
}

void CenterServer::PartitionLogFile()
{
    SYSTEMTIME xSystem;
    ::GetLocalTime( &xSystem );

    if ( !RecordTime::CheckRecordTime( _dwPartitionLogTile, xSystem.wYear, xSystem.wMonth, xSystem.wDay ) )
    { return; }
    RecordTime::SaveRecordTime( _dwPartitionLogTile, xSystem.wYear, xSystem.wMonth, xSystem.wDay );

    // ���ڸı�, �л�Log�ļ�, ��֪ͨ����������

    //LOG_MESSAGE( SYSTEMOBJECT,      LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LOG_MESSAGE( STATISTICSOBJECT,  LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LOG_MESSAGE( BILLINGOBJECT,     LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LOG_MESSAGE( PLATFORMOBJECT,    LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LOG_MESSAGE( MAILOBJECT,        LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LOG_MESSAGE( AUCTIONOBJECT,     LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LOG_MESSAGE( SQLOBJECT,         LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );

    // ������Ϣ�����з�����
    MsgPartitionLogFile xPartitonLogFile;
    theGameServerManager.SendMessageToGameServers( &xPartitonLogFile );
    theGameServerManager.SendMessageToCharacterServer( &xPartitonLogFile );
    theCenterServer.SendMessageToDb( &xPartitonLogFile );
}