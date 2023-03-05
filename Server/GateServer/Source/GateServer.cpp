#include "GateServer.h"
#include "MessageDefine.h"
#include "Config.h"
#include "Helper.h"
#include "FuncPerformanceLog.h"
//#include "MeNetwork.h"
#include "ResourcePath.h"
#include "MapConfig.h"
//#include "NetApi.h"
#include "GameTime.h"
#include "application_config.h"
#include "CenterGameMessage.h"
#include "ConsoleApplication.h"
#include "ColorScreen.h"
#include "NetWorkParameterDefine.h"

void NotPushMessage( uint8 type, uint32 messageId, uint8 result, uint32 value )
{   
    if ( value != 0)
    {
        switch ( type )
        {
        case 0:
            { LogMessage::LogLogicError( "account[%u] recv NotPush %u:%u", value, result, messageId ); }
            break;
        case 1:
            { LogMessage::LogLogicError( "account[%u] send NotPush %u:%u", value, result, messageId ); }
            break;
        }
    }
    else
    {
        switch ( type )
        {
        case 0:
            { LogMessage::LogLogicError( "GameServer recv NotPush %u:%u", result, messageId ); }
            break;
        case 1:
            { LogMessage::LogLogicError( "GameServer send NotPush %u:%u", result, messageId ); }
            break;
        }
    }
}

//void RecvMessageCallBack( const SNetResult& sNetResult )
//{
//    LogMessage::LogSystemError( "Recv Net Info %u:%u:%u", sNetResult.result, sNetResult.messageType, sNetResult.messageLength );
//}

void SendMessageCallBack( uint32 result, uint32 watchMsgCount )
{
    if ( result == 0)
    {
        char	szDebugInfo[200];
        sprintf( szDebugInfo, "--->{%d}", watchMsgCount );
        OutputDebugString( szDebugInfo );
    }
    else
    {
        assert( false );
    }
}

CGateServer& GettheGateServer()
{
    static CGateServer s_theGateServer;
    return s_theGateServer;
}

CGateServer::CGateServer()
{
    m_dwLastUpdateLoginInfoTime = 0;
    m_nLastPingGameServerTime   = 0;
    m_nGameServerAckPingTime    = 0;
    m_pAllocClients             = NULL;
    m_pNormalClients            = NULL;
    m_pClientWaitClose          = NULL;
    m_pGateClients              = NULL;
    m_iOnlineNum                = 0;
    m_iOnlinePlayGameNum        = 0;
    m_psockClientListen         = NULL;
    _pGameServerConnector       = NULL;
    _revShutdownCommandTime     = 0;
    _revShutdownDelayTime       = 0;
    _bStopServer                = false;
    _bShowAllPlayerPos          = false;
    _pOwner                     = NULL;
    showFrameTime = false;

    xCheckDisConnectClientsTimer.StartTimer( HQ_TimeGetTime(), 5 * ONE_SEC);
}

CGateServer::~CGateServer()
{
    if( m_pAllocClients )
    { delete m_pAllocClients; }

    if( m_pNormalClients )
    { delete m_pNormalClients; }

    if( m_pClientWaitClose )
    { delete m_pClientWaitClose; }

    if( m_pGateClients )
    { delete m_pGateClients; }

    if( m_psockClientListen )
    {
        m_psockClientListen->Close();
        /*m_psockClientListen->Release();*/
		Listener_release(m_psockClientListen);
        m_psockClientListen = NULL;
    }

    if( _pGameServerConnector )
    {
        /*unsigned int nKey = _pGameServerConnector->GetKey();*/
        //_pGameServerConnector->Close();
		Socketer_release(_pGameServerConnector);
        /*GetMeNetwork().ReleaseMeConnector( nKey );*/
        _pGameServerConnector = NULL;
    }
    _pOwner                 = NULL;
}

int CGateServer::Init( ConsoleApplication* pOwner )
{
    _pOwner = pOwner;
    // ��ȡ�����ͼ��Ϣ��Դ
    if (!theMapConfig.LoadMapConfig( WORLDMAPCONFIG_FILEPATH ) )
    {
        LogMessage::LogSystemInfo("%s [Error]", WORLDMAPCONFIG_FILEPATH );
        return GSR_LoadWorldMapError;
    }
    else
    {
        LogMessage::LogSystemInfo( "Read %s [OK]", WORLDMAPCONFIG_FILEPATH );
    }

    // ��ʼ�������ͼ��Ϣ ��Ϊ��Ϣ֪ͨ
    if( !m_world.InitStages() )
    { return GSR_InitWorldMapError;}   

    m_psockClientListen = Listener_create();/*GetMeNetwork().CreateMeSocket();*/
    if ( !m_psockClientListen  )
    { return ret_socketstartuperror; }

    //_pGameServerConnector = Socketer_create();/*GetMeNetwork().CreateMeConnector();*/

    //if ( !_pGameServerConnector )
    //{ return ret_socketstartuperror; }

    if( /*!m_psockClientListen->Create( theCfg.nForClientGatePort ) || */!m_psockClientListen->Listen( theCfg.nForClientGatePort,eN_GateServer_ListenNum ) )
    { return ret_listenerror; }

    m_pAllocClients    = new CStaticArray<BaseCharacter*>( dr_worldMaxPlayers * 4 );
    m_pNormalClients   = new CStaticArray<BaseCharacter*>( dr_worldMaxCharacters  );
    m_pClientWaitClose = new CStaticArray<BaseCharacter*>( dr_worldMaxPlayers * 4 );
    m_pGateClients     = new CStaticArray<BaseCharacter*>( dr_worldMaxPlayers * 4 ); 

    if( !m_pAllocClients || !m_pNormalClients || !m_pClientWaitClose || !m_pGateClients )
    {
        if( m_pAllocClients )
        { delete m_pAllocClients; }

        if( m_pNormalClients )
        { delete m_pNormalClients; }

        if( m_pClientWaitClose )
        { delete m_pClientWaitClose; }

        if( m_pGateClients )
        { delete m_pGateClients; }

        return ret_allocerror;
    }

    if( !CreateGameServerConnectorSocket() )
    { return ret_gwsocketcreateerror; }

    m_iGameServerConnectStatus = gw_tryconnect;

   /* if (!GetMeNetwork().StartIoCompletionPort( 1, -1 ))
    { return ret_createiocerror; }*/

    return ret_succ;
}

bool CGateServer::CreateGameServerConnectorSocket()
{
	return true;
    //if( _pGameServerConnector->GetSocket()->Create() )
    //{
    //    IMeSocket* pSocket = GetMeNetwork().CreateMeSocket();
    //    //���ܸ��ϴε�socketһ��
    //    if( !_pGameServerConnector->CheckIsDifferentSocket() )
    //    {            
    //        if( !pSocket->Create( ))
    //        {
    //            pSocket->Release();
    //            _pGameServerConnector->GetSocket()->Close();
    //            return false;
    //        }
    //        else
    //        {
    //            _pGameServerConnector->GetSocket()->Close();
    //            _pGameServerConnector->SetSocket( pSocket );
    //            return true;
    //        }
    //    }
    //    return true;
    //}    
    //return false;
}

void CGateServer::TryConnectGameServer()
{
    if ( _bStopServer )
    { return; }

    if ( !_pGameServerConnector )
    {
        _pGameServerConnector = Socketer_create();/*GetMeNetwork().CreateMeConnector();*/
		_pGameServerConnector->SetFlagName("gss");
        return;
    }
	//if (!_pGameServerConnector->m_self)
	//{
	//	//Socketer_release(_pGameServerConnector);
	//	_pGameServerConnector = NULL;

	//	_pGameServerConnector = Socketer_create();
	//}

    switch( m_iGameServerConnectStatus )
    {
    case gw_tryconnect:
        {
            if( _pGameServerConnector->Connect(theCfg.szGameServerIP,theCfg.nGameServerPort)/*_pGameServerConnector->GetSocket()->ConnectAsync( theCfg.szGameServerIP,theCfg.nGameServerPort, 5 )  */)
            {   
                /*_pGameServerConnector->BuildKey();
                bool bResult = GetMeNetwork().RegisterMeConnector( _pGameServerConnector->GetKey(), _pGameServerConnector );
                if ( bResult )*/
                { 
                    /*unsigned long nResult = _pGameServerConnector->EnableIoCompletionPort( false );
                    if ( nResult != ER_Success )
                    {
                        LogMessage::LogSystemError( "TryConnectGameServer EnableIoCompletionPort Fail(0x%x)", nResult );
                        unsigned int nKey = _pGameServerConnector->GetKey();
                        _pGameServerConnector->Close();
                        GetMeNetwork().ReleaseMeConnector( nKey );
                        _pGameServerConnector = GetMeNetwork().CreateMeConnector();
                        return;
                    }*/

                    LogMessage::LogSystemInfo( "Connect GameServer Success" );
                    COLOR_MESSAGE( COLOR_GREEN, "[GateServer OK] \n" );
                    m_iGameServerConnectStatus = gw_normal;
                    m_nGameServerAckPingTime = HQ_TimeGetTime();

                   /* _pGameServerConnector->SetLowLevelCast   ( theCfg.gameLowLvlCast);
                    _pGameServerConnector->SetNormalLevelCast( theCfg.gameNormalLvlCast);

                    _pGameServerConnector->SetMaxQueueMsgNum ( IMeConnector::ET_InQueue,  theCfg.gameMaxCountIn );
                    _pGameServerConnector->SetMaxQueueMsgNum ( IMeConnector::ET_OutQueue, theCfg.gameMaxCountOut );*/
                }
               /* else
                {
                    m_iGameServerConnectStatus = gw_ReConnect;
                }*/
            }
            else
            {   
                Sleep(1000);
            }
        }
        break;
    case gw_ReConnect:
        {   
            //unsigned int nKey = _pGameServerConnector->GetKey();
            //_pGameServerConnector->Close();
            Socketer_release(_pGameServerConnector); //GetMeNetwork().CreateMeConnector();
			_pGameServerConnector= NULL;
            /*GetMeNetwork().ReleaseMeConnector( nKey );*/
			m_iGameServerConnectStatus = gw_tryconnect;
            //if ( !_pGameServerConnector )
            //{ return; }
            //CreateGameServerConnectorSocket();
            //m_iGameServerConnectStatus = gw_tryconnect;
            LogMessage::LogSystemInfo( "Begin ReConnect GameServer");
        }
        break;
    }
}

void CGateServer::Shutdown()
{
    LogMessage::LogSystemInfo("GateServer�ر���");
    CloseAllClient();

    while( m_pClientWaitClose->GetUsed() > 0 )
    {
        CheckClientWaitClose( false );
        Sleep( 33 );
    }

    if ( _pGameServerConnector )
    {
        //_pGameServerConnector->Close();
        /*GetMeNetwork().ReleaseMeConnector( _pGameServerConnector->GetKey());*/
		Socketer_release(_pGameServerConnector);
        _pGameServerConnector = NULL;
    }

	net_release();
    /*GetMeNetwork().StopIoCompletionPort();*/

    if( m_pAllocClients )
    {
        delete m_pAllocClients;
        m_pAllocClients = NULL;
    }
    if( m_pNormalClients )
    {
        delete m_pNormalClients;
        m_pNormalClients = 0;
    }
    if( m_pClientWaitClose )
    {
        delete m_pClientWaitClose;
        m_pClientWaitClose = 0;
    }
    if( m_pGateClients )
    {
        delete m_pGateClients;
        m_pGateClients = 0;
    }

    if ( m_psockClientListen )
    {
        m_psockClientListen->Close();
        /*m_psockClientListen->Release();*/
		Listener_release(m_psockClientListen);
        m_psockClientListen = NULL;
    }

    //GetMeNetwork().SocketCleanUp();

    LogMessage::LogSystemInfo("GateServer�����ر�");
}

void CGateServer::RunOneStep()
{
    uint32 frameTime = HQ_TimeGetTime();
    DECLARE_TIME_TEST

	net_run();
    //////////////////////////////////////////////////////////////////////////
    if( gw_normal != m_iGameServerConnectStatus )
    {
        TryConnectGameServer();
        return;
    }    

    //////////////////////////////////////////////////////////////////////////
    // ÿһ�������߷�������ǰ��Gate��Ϣ
    TellWorldGateInfo();

    //////////////////////////////////////////////////////////////////////////
    BEGIN_TIME_TEST( "client accept" )    
    int iAccept = 0;
    const int iAcceptMax = 10;    
    while( /*m_psockClientListen->HasData()*/m_psockClientListen->CanAccept() && iAccept < iAcceptMax )
    { //���ܿͻ��˵�����
        if ( !AcceptNewClient())
        {   
            break;
        }
        iAccept ++;
    }
    END_TIME_TEST( "client accept" )

    //////////////////////////////////////////////////////////////////////////
    BEGIN_TIME_TEST( "gameserver recv" )    
    _pGameServerConnector->CheckRecv();
    END_TIME_TEST( "gameserver recv" )

    //////////////////////////////////////////////////////////////////////////
    //������������Ϣ���г��ȱ���
    //�ڶ��з��Ͳ���ʱ�����Ͽ�GAMESERVERȻ������
    if( _pGameServerConnector->IsClose() )
    {
        LogMessage::LogLogicError( "GameServer�Ͽ�����");
        m_iGameServerConnectStatus = gw_ReConnect;        
        CloseAllClient(); //�ر����еĿͻ���
        Sleep( 2000 );    //cold down
        /*_pGameServerConnector->Reset();*/
		Socketer_release(_pGameServerConnector);
		_pGameServerConnector = NULL;
        return;
    }

    //////////////////////////////////////////////////////////////////////////
    BEGIN_TIME_TEST( "gameserver process" )    
    uint32 count = 0;
    ProcessGameServerMessage(count); // ת����������Ϣ��Client    
    END_TIME_TEST_1( "gameserver process",60 )

    //////////////////////////////////////////////////////////////////////////
    //if( _pGameServerConnector->GetInQueueSize() >= theCfg.gameMaxCountIn )
    //{
    //    LogMessage::LogLogicError( "��Ϊ��Ϣ̫����GameServer in[%d]", _pGameServerConnector->GetOutQueueSize());        
    //    //m_iGameServerConnectStatus = gw_ReConnect;
    //    //CloseAllClient(); //�ر����еĿͻ���
    //    //Sleep( 2000 );    //cold down
    //    //_pGameServerConnector->Reset();
    //    //return;
    //}

	//////////////////////////////////////////////////////////////////////////
	BEGIN_TIME_TEST( "client resv" )
	RecvAllClientMsg(); // ���տͻ�����Ϣ������Ϣ
	END_TIME_TEST( "client resv" )

    //////////////////////////////////////////////////////////////////////////
    BEGIN_TIME_TEST( "client process" )    
    ProcessAllClientMsg(); // ת���ͻ�����Ϣ��GameServer
    END_TIME_TEST( "client process" )

    //////////////////////////////////////////////////////////////////////////
    BEGIN_TIME_TEST( "gameserver send" )    
    _pGameServerConnector->CheckSend();
    END_TIME_TEST( "gameserver send" )

    //////////////////////////////////////////////////////////////////////////
    BEGIN_TIME_TEST( "client pos" )    
	SendAllClientPackMsg(); // ���Ϳͻ������������Ϣ
    END_TIME_TEST_1( "client pos",50 )

    //////////////////////////////////////////////////////////////////////////
    BEGIN_TIME_TEST( "client send" )
    SendAllClientMsg(); // ���Ϳͻ�����Ϣ������Ϣ
    END_TIME_TEST( "client send" )
    //if( _pGameServerConnector->GetOutQueueSize() >= theCfg.gameMaxCountIn )
    //{
    //    LogMessage::LogLogicError( "��Ϣ̫����GameServer out[%d]", _pGameServerConnector->GetOutQueueSize());

    //    //m_iGameServerConnectStatus = gw_ReConnect;
    //    //CloseAllClient(); //�ر����еĿͻ���
    //    //Sleep( 2000 );    //cold down
    //    //_pGameServerConnector->Reset();
    //    //return;
    //}

    //////////////////////////////////////////////////////////////////////////    
    CheckClientWaitClose(); // ���µȴ�ɾ������

    //////////////////////////////////////////////////////////////////////////
    CheckForServerExit();

    //////////////////////////////////////////////////////////////////////////    
    UpdateTheLoginInfo();

    //////////////////////////////////////////////////////////////////////////    
    CheckDisConnectClients();

    // �ȼ���Log4cxx
    if ( _pOwner->GetReloadLog4cxx() )
    {
        if ( _pOwner->InitLogConfigure() )
        {
            std::cout << "Info:���¼���Gate-Log4cxx���" << std::endl;
            _pOwner->SetReloadLog4cxx(false);
        }
    }

    uint32 time = HQ_TimeGetTime() - frameTime;
    if ( time > 100 || showFrameTime )
    {
        std::cout << "frame:elapse:" << time << std::endl;
        showFrameTime = false;
    }
}

bool CGateServer::AcceptNewClient()
{
    // return false;

    if ( _bStopServer )
    { return false; }

#ifdef _DEBUG
    LogMessage::LogLogicInfo( "OneAcceptNewClient--", m_iOnlineNum, theCfg.playerMaxOnlineCount );
#endif
    //������������
    if( GetOnlineNum() >= theCfg.playerMaxOnlineCount )
    {
        LogMessage::LogSystemInfo( "GateServer Accept���� [%d] �Ѿ��ﵽ����[%d]", m_iOnlineNum, theCfg.playerMaxOnlineCount );
        LogMessage::LogLogicError( "GateServer Accept���� [%d] �Ѿ��ﵽ����[%d]", m_iOnlineNum, theCfg.playerMaxOnlineCount );
        return false;
    }

    // �ӳ����ٶ��й���
    float fUsed = (float)(m_pClientWaitClose->GetUsed()) / m_pClientWaitClose->GetSize();
    if( fUsed > WAITCLOSE_ALLOW_RATE )
    {
        LogMessage::LogSystemInfo( "�ӳ����ٶ��й��� Rate[%f:%f]", fUsed, WAITCLOSE_ALLOW_RATE );
        LogMessage::LogLogicError( "�ӳ����ٶ��й��� Rate[%f:%f]", fUsed, WAITCLOSE_ALLOW_RATE );
        return false;
    }

    /*IMeSocket*/Socketer* pSocket = NULL/*GetMeNetwork().CreateMeSocket()*/;
	pSocket = m_psockClientListen->Accept();
    if ( !pSocket )
    {        
        LogMessage::LogSystemError( "AcceptNewClient->CreateMeSocket Fail" );
        return false;
    }

    /*if( !m_psockClientListen->Accept( pSocket ) )
    {
        LogMessage::LogSystemError( "AcceptNewClient->Accept Fail" );

        if ( pSocket )
        {
            pSocket->Close();
            pSocket->Release();
        }
        return false;
    }*/

    // �����������IP�����������������Ͽ�
    //in_addr addr;
    std::string strIP;
	char chip[20];
	pSocket->GetIP(chip,20);
	strIP = chip;
    //pSocket->GetPeerName(addr);
    //strIP = inet_ntoa(addr);
    // LogMessage::LogSystemInfo( "Accept Socket %s", strIP.c_str());
    //std::map<string, unsigned int>::iterator it = theLoginInfo.find(strIP);
    //if (it == theLoginInfo.end() && strIP != "127.0.0.1")
    //{ // δ�������IP��ַ
    //    pSocket->Close();
    //    return false;
    //}

    GameObjectId iID = m_pAllocClients->Malloc();
    if ( InvalidGameObjectId == iID )
    {
        LogMessage::LogLogicError("AcceptNewClient->MallocLoopID Fail");
        if ( pSocket )
        {
            pSocket->Close();
            /*pSocket->Release();*/
			Socketer_release(pSocket);
        }
        return false;
    }

    *(*m_pAllocClients)[iID] = NULL;

    GamePlayer* pClient = new GamePlayer;
    if( !pClient )
    {
        LogMessage::LogLogicError( "AcceptNewClient->new GamePlayer Fail" );
        if ( pSocket )
        {
            //pSocket->Close();
            /*pSocket->Release();*/
			Socketer_release(pSocket);
        }

        if( InvalidGameObjectId != iID)
        {
            m_pAllocClients->Free(iID);
        }
		delete pClient;
        return false;
    }

    //IMeConnector* pConnector = GetMeNetwork().CreateMeConnector();
    //if ( !pConnector )
    //{
    //    if ( pSocket )
    //    {
    //        pSocket->Close();
    //        pSocket->Release();
    //    }

    //    if( InvalidGameObjectId != iID )
    //    {
    //        m_pAllocClients->Free( iID );
    //    }

    //    if( pClient )
    //    {
    //        delete pClient;
    //        pClient = NULL;
    //    }
    //    return false;
    //}

    //pConnector->SetOutMessageEncType( theCfg.gEncryptMode, true ); // �˺��������� EnableIoCompletionPort ֮ǰ
    //pConnector->SetSocket( pSocket );
    //pConnector->BuildKey();
    //pConnector->SetRecvMessageErrorCallBack( RecvMessageCallBack );
    //// pConnector->SetSendMessageErrorCallBack( SendMessageCallBack );
    //pConnector->SetNotPushMessageCallBack( NotPushMessage );
    //pConnector->SetSkipInQueueWhenReset( true );

    //bool bRegisterResult = GetMeNetwork().RegisterMeConnector( pConnector->GetKey(), pConnector );
    //if ( !bRegisterResult )
    //{
    //    LogMessage::LogLogicError( "AcceptNewClient->RegisterMeConnector Fail");

    //    if( InvalidGameObjectId != iID )
    //    {
    //        m_pAllocClients->Free( iID );
    //    }

    //    if( pClient )
    //    {
    //        delete pClient;
    //        pClient = NULL;
    //    }

    //    if ( pConnector )
    //    {
    //        pConnector->Close();
    //        pConnector->Release();
    //    }
    //    return false;
    //}

    //pConnector->SetMaxQueueMsgNum ( IMeConnector::ET_InQueue , theCfg.clientMaxCountIn  );
    //pConnector->SetMaxQueueMsgNum ( IMeConnector::ET_OutQueue, theCfg.clientMaxCountOut );
    //pConnector->SetNormalLevelCast( theCfg.clientLowLvlCast    );
    //pConnector->SetLowLevelCast   ( theCfg.clientNormalLvlCast );
    //unsigned long result = pConnector->EnableIoCompletionPort( false );
    //if ( ER_Success != result )
    //{
    //    LogMessage::LogLogicError( "CGateServer::AcceptNewClient->EnableIoCompletionPort Fail(%u %d)",result, iID);
    //    if( InvalidGameObjectId != iID )
    //    { m_pAllocClients->Free( iID ); }

    //    if( pClient )
    //    {
    //        delete pClient;
    //        pClient = NULL;
    //    }

    //    if ( pConnector )
    //    {
    //        pConnector->Close();
    //        GetMeNetwork().ReleaseMeConnector( pConnector->GetKey() );
    //    }
    //    return false;
    //}

    // ����GamePlayer��
	pSocket->UseDecrypt();
	//pSocket->UseEncrypt();
	//pSocket->UseCompress();
	//pSocket->SetFlagName("cls");
    pClient->SetConnector( pSocket/*pConnector*/ );

    pClient->m_strIP = strIP; //��������IP
    pClient->m_dwAcceptTime = HQ_TimeGetTime();

    *(*m_pAllocClients)[ iID ] = pClient;
    pClient->_iAllocId = iID;

    IncreaseOnlineNum();
    IncreaseOnlinePlayGameNum();

    return true;
}

bool CGateServer::SendAllocClient( GameObjectId iID, const char* szClientName, const char* ip, DWORD dwAccountID )
{   
    BaseCharacter** ppChar = (*m_pAllocClients)[iID];
    if( ppChar == NULL )
    { return false; }

    BaseCharacter* pChar = *ppChar;
    if ( pChar == NULL )
    { return false; }

    pChar->SetReqAllocTime( HQ_TimeGetTime() );

    Msg_G2GW_AllocClient alloc;
    alloc.header.stID = iID;
    alloc.dwAccountID = dwAccountID;
    strncpy_s( alloc.szUserName, sizeof( alloc.szUserName ), szClientName, sizeof( alloc.szUserName) - 1 );
    strncpy_s( alloc.ip        , sizeof( alloc.ip         ), ip          , sizeof( alloc.ip        ) - 1 );
    _pGameServerConnector->SendMsg( &alloc );

	TESTECHOSEND( dwAccountID, Msg_G2GW_AllocClient )
    return true;
}

void CGateServer::CloseAllClient()
{
    LogMessage::LogSystemInfo("GateServer�ر����пͻ���");

    int iLoopUsed,iLoopSize;
    int iUsed,iSize;

    BaseCharacter**ppChar = NULL,*pChar = NULL;

    iSize = m_pNormalClients->GetSize();
    iUsed = m_pNormalClients->GetUsed();
    for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ;  ++ iLoopSize )
    {
        ppChar = (*m_pNormalClients)[ iLoopSize ];
        if( !ppChar )
            continue;
        iLoopUsed ++;

        pChar = *ppChar;

        if( pChar->IsPlayer() )
        {
            AddToClientWaitClose( (GamePlayer*)pChar, __FUNCTION__, __LINE__ );
        }
        else
        {
            delete pChar;
        }
        m_pNormalClients->Free( iLoopSize );
    }

    iSize = m_pAllocClients->GetSize();
    iUsed = m_pAllocClients->GetUsed();
    for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ;  iLoopSize ++ )
    {
        ppChar = (*m_pAllocClients)[ iLoopSize ];
        if( !ppChar )
            continue;
        iLoopUsed ++;

        pChar = *ppChar;

        if( pChar->IsPlayer() )
        {
            AddToClientWaitClose( (GamePlayer*)pChar, __FUNCTION__, __LINE__ );
        }
        else
        {
            delete pChar;
        }
        m_pAllocClients->Free( iLoopSize );
    }    

    m_iOnlineNum = 0;
}

void CGateServer::ProcessGameServerMessage( uint32& count )
{ //����GameServer��������Ϣ
    unsigned int nTime = HQ_TimeGetTime();
    if ( GameTime::IsPassCurrentTime( nTime, m_nLastPingGameServerTime, const_iPingGameServerTime ) )
    {
        //��GameServer����Ping��Ϣ
        MsgPingMsg msgPing;
        _pGameServerConnector->SendMsg(&msgPing);
        m_nLastPingGameServerTime = nTime;
    }

    Msg* pMsg = NULL;
    GameTimerEx processGameMessageTime;
    processGameMessageTime.StartTimer( HQ_TimeGetTime(), 50 );

    // ʱ��Ƭ���˾�����
    while( !processGameMessageTime.DoneTimer( HQ_TimeGetTime() ) )
    {   
        pMsg = _pGameServerConnector->GetMsg();
        if ( pMsg == NULL )
        { break;  }

        MessageType dwType = pMsg->GetType();
        ++count;
        switch( dwType )
        {
        case S2S_SHUTDOWNSERVER:
            {
                uint32 curTime = HQ_TimeGetTime();
                S2SShutdownServer* pMessage = (S2SShutdownServer*)pMsg;
                SetShutdownTime( curTime, pMessage->delayTime - 1 );
                LogMessage::LogSystemInfo( "�յ�GameServer�ط�֪ͨ(%u:%u),��ʼ�ط��㲥...", curTime, pMessage->delayTime - 1 );
            }
            break;
        case MSG_PING:
            {// GameServer����������Ping
                m_nGameServerAckPingTime = HQ_TimeGetTime();
            }
            break;
        case MSG_REGISTERSERVERREQ:
            {
                // ����ע����Ϣ
                MsgRegisterServerAck xAck;
                xAck.uchType       = ServerDataDefine::Node_Gate;
                xAck.nID           = theCfg.nGateServerId;
                xAck.ustVersion    = theApplicationConfig.GetBuildVersion();
                sprintf_s( xAck.szName, sizeof( xAck.szName ) - 1, "GateServer-%s", theCfg.szGameServerName );
                _pGameServerConnector->SendMsg( &xAck );
            }
            break;
        case MSG_SERVERSTATUSREQ:
            {
                MsgServerStatusAck xAck;
                xAck.uchType = ServerDataDefine::Node_Gate;
                xAck.nID     = theCfg.nGateServerId;
                _pGameServerConnector->SendMsg( &xAck );
            }
            break;
        case MSG_PARTITIONLOGFILE:
            {
                PartitionLogFile();
            }
            break;
        case MSG_GW2G_RETALLOCCLIENT:
            {
                OnMsgAllocClientAck(pMsg);
            }
            break;
        case MSG_GW2G_SYNCCHARPOS:
            {
                OnMsgSyncCharPos(pMsg);
            }
            break;
        case MSG_GW2G_SYNCCHARINFO:
            {
                OnMsgSyncCharInfo(pMsg);
            }
            break;
        case MSG_GW2G_NPCEXIT:
            {
                OnMessageCharacterExit(pMsg);
            }
            break;
        case MSG_GW2G_CREATESTAGE:
            {
                OnMsgCreateStage( pMsg );
            }
            break;
        case MSG_GW2G_RELEASESTAGE:
            {
                OnMsgReleaseStage( pMsg );
            }
            break;
        case MSG_GWORLDINFO:
            {
                MsgGWorldInfo* info = (MsgGWorldInfo*)pMsg;
                m_nGameServerOnlineCount = info->nOnlineNum;
            }
            break;
        case MSG_LOGININFO:
            {
                MsgLoginInfo* info = (MsgLoginInfo*)pMsg;
                OnLoginInfo(info);
            }
            break;
        case MSG_DELLOGININFO:
            {
                MsgDelLoginInfo* pMessage = (MsgDelLoginInfo*)pMsg;
                OnDelLoginInfo( pMessage );
            }
            break;
		case MSG_ACK_RESULT:
			{
				MsgAckResult* pMessage = (MsgAckResult*)pMsg;
				if (pMessage&&pMessage->result == ER_SessionKeyOverTime)
				{
					ItrLoginInfoContainer it = _loginInfos.find( pMessage->value );

					if (it != _loginInfos.end())
					{
						SLoginInfo& rLoginInfo = it->second;
						_loginInfos.erase( it ); 
					}
				}
				
				//�ͻ��� ER_EnterWorldQueue
				DispatchToPlayer(pMsg); // ת�Ƶ��ͻ��Ķ�����
			}
			break;
        default:
            {
                DispatchToPlayer(pMsg); // ת�Ƶ��ͻ��Ķ�����
            }
            break;
        }
    }
}

bool CGateServer::OnClientReConnect( Msg* pMessage, int nAllocClientIndex, GamePlayer* pClient )
{ // ��������
    MsgReConnect* pReConnect = static_cast<MsgReConnect*>( pMessage );

    //HelperFunc::CheckStringValid( pReConnect->szKey, sizeof( pReConnect->szKey ) );
    pClient->SetAccountID( pReConnect->nAccountId );
    pClient->SetSessionKey( pReConnect->SessionKey );

    // �ж��Ƿ�Ϸ�
    DisconnectClientContainerItr it = m_DisConnectClient.find( pReConnect->SessionKey );
    SDisconnectClient xDisconnectClient;

    bool bFindInLoop = false; // �Ƿ�����Gate Loop���ҵ���
    if ( it == m_DisConnectClient.end())
    { // û���ҵ���ɾ��
        // �п��ܷ�������IsClose�ȿͻ��˵���
        int iLoopUsed = 0;
        int iLoopSize = 0;
        int iSize = m_pGateClients->GetSize();
        int iUsed = m_pGateClients->GetUsed();
        BaseCharacter**ppChar = NULL,*pChar = NULL;
        GamePlayer* pDisConClient = NULL;
        for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ;  iLoopSize ++ )
        {
            ppChar = (*m_pGateClients)[ iLoopSize ];
            if( !ppChar )
            { continue; }

            iLoopUsed ++;
            pChar = *ppChar;
            if ( NULL == pChar || !pChar->IsPlayer() )
            { continue; }

            pDisConClient = static_cast<GamePlayer*>(pChar);

            if ( pDisConClient->GetAccountID() == pReConnect->nAccountId &&
                 /*stricmp( pDisConClient->GetSessionKey(), pReConnect->szKey)== 0 */
				 pDisConClient->GetSessionKey()==pReConnect->SessionKey )
            {
                xDisconnectClient.nAccountId      = pDisConClient->GetAccountID();
                xDisconnectClient.nDisconnectTime = pDisConClient->GetDisconnectTime();
                xDisconnectClient.nInGateClientsPos = iLoopSize;
                
                bFindInLoop = true;
                break;
            }
        }
        
        // �Ƿ���ѭ�����ҵ�
        if ( !bFindInLoop )
        {
            MsgReConnectAck msg;
            msg.nResult = MsgReConnectAck::ERR_Invalid1;
            pClient->SendMsg( &msg );
            m_pAllocClients->Free( nAllocClientIndex) ;
            AddToClientWaitClose( pClient, __FUNCTION__, __LINE__ );
            return false;
        }
    }
    else
    {
        xDisconnectClient = it->second;
    }
    
    // �ж��Ƿ������޵�λ��Info
    BaseCharacter **ppChar = NULL,*pChar = NULL;
    ppChar = (*m_pGateClients)[ xDisconnectClient.nInGateClientsPos ];
    if( NULL == ppChar )
    {
        MsgReConnectAck msg;
        msg.nResult = MsgReConnectAck::ERR_ErrorPos1;
        pClient->SendMsg( &msg );
        m_pAllocClients->Free( nAllocClientIndex) ;
        AddToClientWaitClose( pClient, __FUNCTION__, __LINE__ );
        return false;
    }

    pChar = *ppChar;
    if ( NULL == pChar || !pChar->IsPlayer())
    {
        MsgReConnectAck msg;
        msg.nResult = MsgReConnectAck::ERR_ErrorPos2;
        pClient->SendMsg( &msg );
        m_pAllocClients->Free( nAllocClientIndex) ;
        AddToClientWaitClose( pClient, __FUNCTION__, __LINE__ );
        return false;
    }

    GamePlayer* pDisConnectClient = static_cast<GamePlayer*>(pChar);
    if ( !bFindInLoop )
    { // ��Loop�ҵ��Ͳ����ж�
        if ( pDisConnectClient->GetAccountID() != pReConnect->nAccountId        ||
            /*strcmp( pDisConnectClient->GetSessionKey(), pReConnect->szKey ) != 0 */
			pDisConnectClient->GetSessionKey() != pReConnect->SessionKey
            /*pDisConnectClient->m_strIP != pClient->m_strIP*/ )
        {
            MsgReConnectAck msg;
            msg.nResult = MsgReConnectAck::ERR_Invalid2;
            pClient->SendMsg( &msg );
            m_pAllocClients->Free( nAllocClientIndex) ;
            AddToClientWaitClose( pClient, __FUNCTION__, __LINE__ );
            return false;
        }

        // ɾ��������¼
        m_DisConnectClient.erase( pReConnect->SessionKey );
    }

    m_pAllocClients->Free( nAllocClientIndex );

    // ɾ������
    IncreaseOnlineNum( -1 );
    IncreaseOnlinePlayGameNum( -1 );

    pDisConnectClient->SetConnector( pClient->GetConnector() );
    pDisConnectClient->m_dwDisConnectTime = 0;

    // ���н�pClient������
    ReleaseReconnectClient( pClient, true );

    MsgReConnectAck msg;
    msg.nResult = MsgReConnectAck::ERR_Success;
    pDisConnectClient->SendMsg( &msg );

    // ����Ϣ��GameServer
    pMessage->header.stID = pDisConnectClient->GetGameServerPlayerId();
    _pGameServerConnector->SendMsg( pMessage );
	return true;
}

void CGateServer::ProcessIsCloseInGateClient( GamePlayer* pGamePlayer, int nGateClientIndex )
{
    // �ж��Ƿ�����˳�����
    if ( pGamePlayer->HasSendClientExit() )
    { return; }

    if ( pGamePlayer->GetClientStatus() == GamePlayer::EStatusType_WaitSwitchGateCallBack ||
         pGamePlayer->GetClientStatus() == GamePlayer::EStatusType_GetSwitchGateCallBack )
    { // �з�����  GameServer�ȴ����˳���
        if ( !pGamePlayer->HasSendClientExit() )
        {
            pGamePlayer->SetHasSendClientExit();
            /*IMeConnector*/Socketer* pConnector = pGamePlayer->GetConnector();
            LogMessage::LogLogicInfo( "account[%d:%d] client disconnect-switchgate[-]", pGamePlayer->GetAccountID(), pGamePlayer->GetGameServerPlayerId() /*,pConnector->GetCriticalError()*/ );
        }
    }
    else if ( pGamePlayer->GetClientStatus() == GamePlayer::EStatusType_NormalExit)
    { // �����˳���Ķ��� ��MsgExit��Ϣ�ط�������
        if ( !pGamePlayer->HasSendClientExit() )
        {
            pGamePlayer->SetHasSendClientExit();
            /*IMeConnector*/Socketer* pConnector = pGamePlayer->GetConnector();
            LogMessage::LogLogicInfo( "account[%d:%d] client normal close[-]", pGamePlayer->GetAccountID(), pGamePlayer->GetGameServerPlayerId()/*, pConnector->GetCriticalError()*/ );
        }
    }
    else
    { // ��Ϸ�ж���
        // ���ö���ʱ��
        if ( 0 == pGamePlayer->m_dwDisConnectTime )
        { 
            pGamePlayer->SetDisconnectTime(); 

            SDisconnectClient disconnectInfo;
            disconnectInfo.nAccountId = pGamePlayer->GetAccountID();
            disconnectInfo.nDisconnectTime = pGamePlayer->GetDisconnectTime();
            disconnectInfo.nInGateClientsPos = nGateClientIndex;
            disconnectInfo.SessionKey = pGamePlayer->GetSessionKey();

            // ���������Ϣ����
            m_DisConnectClient.insert( DisconnectClientContainer::value_type( disconnectInfo.SessionKey, disconnectInfo) );
        }
        else
        { // �Ѿ����õĶ���ʱ��
            
            if ( GameTime::IsPassCurrentTime( pGamePlayer->GetDisconnectTime(), theCfg.netOfflineTime ) )
            { // ������ʱ��
                if ( !pGamePlayer->HasSendClientExit() )
                { // GameServer��֪������
                    GameObjectId iGameServerPlayerId = pGamePlayer->GetGameServerPlayerId();
                    /*IMeConnector*/Socketer* pConnector = pGamePlayer->GetConnector();

                    // �쳣�Ķ���
                    LogMessage::LogLogicError( "account[%d:%d] client disconnect-exception[-]", pGamePlayer->GetAccountID(), iGameServerPlayerId/*, pConnector->GetCriticalError()*/ );

                    SendClientExit( iGameServerPlayerId );

                    // ��¼�Ѿ�֪��������
                    pGamePlayer->SetHasSendClientExit();

                    // ɾ�����߼�¼
                    m_DisConnectClient.erase( pGamePlayer->GetSessionKey() );
                }
            }
        }
	}
}

// ����ͻ�����Ϣ
void CGateServer::ProcessAllClientMsg()
{
    BaseCharacter** ppChar = NULL, *pChar = NULL;
    GamePlayer* pClient = NULL;

    int iSize = m_pAllocClients->GetSize();
    int iUsed = m_pAllocClients->GetUsed();
    int iLoopUsed,iLoopSize;
    for( iLoopUsed = 0, iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
    {
        if ( !m_pAllocClients->IsUsed(iLoopSize) )
        { continue; }

        ppChar = (*m_pAllocClients)[iLoopSize];
        if( !ppChar )
        { continue; }

        ++iLoopUsed;

        pChar = *ppChar;
        if( !pChar )
        { continue; }

        pClient = (GamePlayer*)pChar;
        if ( !pClient )
        { continue; }

        /*IMeConnector*/Socketer* pConnector = pClient->GetConnector();
        if ( !pConnector )
        { continue; }

        // �Ƿ��Ѿ�����
        if (pConnector->IsClose())
        {
            m_pAllocClients->Free(iLoopSize);
            AddToClientWaitClose( pClient, __FUNCTION__, __LINE__);
            continue;
        }

#ifndef _DEBUG
        if ( pClient->m_dwAcceptTime != 0 && GameTime::IsPassCurrentTime( pClient->m_dwAcceptTime, const_iSendAllocTimeOut ) )
        {
            LogMessage::LogLogicError("account AllocClient[%d] const_iSendAllocTimeOut [%u:%u]", iLoopSize, pClient->m_dwAcceptTime, const_iSendAllocTimeOut);
            m_pAllocClients->Free(iLoopSize);
            AddToClientWaitClose( pClient , __FUNCTION__, __LINE__ );
            continue;
        }
#endif
        if (!pChar->IsPlayer() || pClient->m_bIsSendConnectInfo)
        { continue; }

        Msg* pMsg = NULL;
        while ( pMsg = pConnector->GetMsg() )
        {   
            if ( pClient->GetGameServerPlayerId() == InvalidGameObjectId )
            { //�����δͨ��GameServer����ID,��ֻ��������ID��������Ϣ
                if (pMsg->GetType() == MSG_ALLOCGWID)
                {
					//printf("9,keylogin:client allocid:%d\n",HQ_TimeGetTime());
                    MsgAllocGWID* pMessage = (MsgAllocGWID*)pMsg;
					
					TESTECHORECV( pMessage->nAccountID, MsgAllocGWID )

                    LogMessage::LogLogicDebug( "account[%u] [%u] MsgAllocGWID", pMessage->nAccountID,pClient->GetReqAllocTime() );

                    if ( 0 != pClient->GetReqAllocTime())
                    { return; }
                    pClient->SetAccountID( pMessage->nAccountID );
                    std::string ip /*= NetApi::GetPeerIP(pConnector->GetSocket())*/;
					char ipch[20];
					pConnector->GetIP(ipch,20);
					ip = ipch;

                    SLoginInfo* pLoginInfo = GetLoginInfo( pMessage->nAccountID );
                    if ( NULL == pLoginInfo )
                    {
                        m_pAllocClients->Free( iLoopSize) ;
                        AddToClientWaitClose( pClient, __FUNCTION__, __LINE__ );
                        LogMessage::LogLogicError("account[%u] �Ƿ������û�! IP[%s]",pMessage->nAccountID,ip.c_str()); 

						/*MsgGateTellClientReAsk msg;
						pClient->SendMsg( &msg );*/
                        break;
                    }

                    //if ( /*false*/strcmp(pLoginInfo->szSessionKey,pMessage->SessionKey)!=0 /*!HelperFunc::CheckToken( pLoginInfo->szPassword, pLoginInfo->szSeed, pMessage->SessionKey)*/ )
					if (pLoginInfo->SessionKey != pMessage->SessionKey)					
                    {
                        m_pAllocClients->Free(iLoopSize);
                        AddToClientWaitClose( pClient, __FUNCTION__, __LINE__);
                        LogMessage::LogLogicError("account[%u] Token Check Error! IP[%s]",pMessage->nAccountID,ip.c_str());
                        break;
                    }
                    else
                    { //��¼�ɹ�
                        pLoginInfo->isConnected = true;
                    }

                    pClient->SetSessionKey( pMessage->SessionKey );
                    pClient->m_bIsSendConnectInfo = true;
                    /*IMeConnector::SOption option;
                    option.value = pClient->GetAccountID();
                    pClient->GetConnector()->SetOption( option );*/

                    SendAllocClient(pClient->_iAllocId, pMessage->szAccount, ip.c_str(), pMessage->nAccountID );
                    break;
                }
                else if ( pMsg->GetType() == MSG_RECONNECT )
                { // ��������
                   if( OnClientReConnect( pMsg, iLoopSize, pClient ))
						pClient->m_bIsSendConnectInfo = true;
                    break;
                }
				else if ( pMsg->GetType() == MSG_LOGININFO )
				{ // 
					//MsgLoginInfo* pLoginMsg = static_cast< MsgLoginInfo* >( pMsg );
					//// �����IP�Ѿ������б��У������ʱ�� ������� ����������ڴ�IP��������
					//ItrLoginInfoContainer it = _loginInfos.find( pLoginMsg->nAccountID );
					//if ( it != _loginInfos.end())
					//{
					//	it->second.recordTime = HQ_TimeGetTime();       //����ʱ��
					//	//strncpy_s(it->second.szSeed,       pLoginMsg->Seed ,        sizeof(it->second.szSeed)-1     );
					//	strncpy_s(it->second.szPassword,   pLoginMsg->Password,     sizeof(it->second.szPassword)-1 );
					//	strncpy_s(it->second.szSessionKey, pLoginMsg->SessionKey, sizeof(it->second.szSessionKey)-1 );
					//}
					//else
					//{
					//	SLoginInfo info;
					//	strncpy_s(info.szPassword,   pLoginMsg->Password ,   sizeof(info.szPassword)-1);
					//	//strncpy_s(info.szSeed,       pLoginMsg->Seed ,       sizeof(info.szSeed)-1 );
					//	strncpy_s(info.szSessionKey, pLoginMsg->SessionKey , sizeof(info.szSessionKey)-1 );

					//	info.recordTime = HQ_TimeGetTime();
					//	_loginInfos.insert( LoginInfoContainer::value_type( pLoginMsg->nAccountID,info));
					//}

					//_pGameServerConnector->SendMsg( pMsg );
					break;
				}
				else if (pMsg->GetType() == MSG_PING)
				{
					MsgPingMsg* pPing = (MsgPingMsg *)pMsg;
					//ֻ�ǰѷ��͹�������Ϣ�ͻ�ȥ
					pClient->SendMsg( pPing );
					pClient->SetPingTime(HQ_TimeGetTime());
					pMsg = pConnector->GetMsg();
				}
				else if (pMsg->GetType() == MSG_EXIT)
				{
					pClient->SetClientStatus( GamePlayer::EStatusType_NormalExit );
				}
            }
        }
    }

    iSize = m_pGateClients->GetSize();
    iUsed = m_pGateClients->GetUsed();
    for( iLoopUsed = 0, iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; iLoopSize ++ )
    {
        ppChar = (*m_pGateClients)[ iLoopSize ];
        if( !ppChar )
        { continue; }
        iLoopUsed ++;

        pChar = *ppChar;
        if ( NULL == pChar )
        { continue; }

        if( !pChar->IsPlayer() )
        { continue; }

        pClient = (GamePlayer*)pChar;
        /*IMeConnector*/Socketer* pConnector = pClient->GetConnector();
        if ( NULL == pConnector)
        { continue; }

        if ( pConnector->IsClose())
        { // �Զ˹ر�
            ProcessIsCloseInGateClient( pClient, iLoopSize );
            continue;
        }

        //if (pConnector->GetInQueueSize() > const_iSingleClientMaxMsgCount)
        //{ continue; }
        //if( pConnector->GetRecvRate() > 3000 )
        //{ //����ͻ��˷�����ϢƵ�ʹ���
        //}
        //pConnector->TryRecv2();

        // ��pingʱ��
#ifdef _DEBUG
        int32 overTime = const_iPingOverTime * 12;
#else
        int32 overTime = const_iPingOverTime;
#endif
        if( !pConnector->IsClose() && GameTime::IsPassCurrentTime( pClient->GetPingTime(), overTime ) )
        { // ��ʱ��û��Ping����Ϊ�ÿͻ����Ѷ���            
            if( !pClient->HasSendClientExit() )
            { // û�з��͹��˳���Ϣ
                if ( pClient->GetClientStatus() == GamePlayer::EStatusType_None )
                {
                    LogMessage::LogLogicInfo("account[%d:%d] ping-excetion��ʱdiconnect", pClient->GetAccountID(), pClient->GetGameServerPlayerId() ); // �ر�����
                    SendClientExit( pClient->GetGameServerPlayerId() );
                }
                else
                {
                    LogMessage::LogLogicInfo("account[%d:%d] ping-switchgate��ʱdiconnect", pClient->GetAccountID(), pClient->GetGameServerPlayerId() ); // �ر�����
                }
                pClient->SetHasSendClientExit();
            }            
            pConnector->Close();
            continue;
        }

        // �Ƿ��GamePlayer Pointer�Ƿ���Ч ��Ϣ�Ĵ���ѭ���жԴ����GamePlayer�������
        bool bClientValid = true; 
        Msg* pMsg = pConnector->GetMsg();
        while (pMsg != NULL)
        {
            MessageType dwType = pMsg->GetType();

#ifdef _DEBUG
            static MessageType debugType = 0;
            if ( dwType == debugType )
            { int a = 0; }
#endif
            switch ( dwType )
            {
            case MSG_PING:
                {   
                    MsgPingMsg* pPing = (MsgPingMsg *)pMsg;
                    //ֻ�ǰѷ��͹�������Ϣ�ͻ�ȥ
                    pClient->SendMsg( pPing );
                    pClient->SetPingTime(HQ_TimeGetTime());
                    pMsg = pConnector->GetMsg();
                    continue;
                }
                break;
            case MSG_LOGIN:
                {   
                    in_addr addr;
                    memset(&addr, 0, sizeof(addr));
                    MsgLogin* pMsgLogin = (MsgLogin*)pMsg;
                    //if( pClient->GetConnector()->GetSocket()->GetPeerName(addr) )
                    //{
                    //    strncpy_s(pMsgLogin->szIP, inet_ntoa(addr), sizeof(pMsgLogin->szIP)-1);
                    //}
					pClient->GetConnector()->GetIP(pMsgLogin->szIP,20);
                    pMsgLogin->header.stID = pClient->GetGameServerPlayerId();
                }
                break;
            case MSG_GETCHARACTER: 
                { //��ȡ��ɫ��Ϣ
					//printf("12,keylogin:get character:%d\n",HQ_TimeGetTime());
                    MsgGetCharacter* get = (MsgGetCharacter*)pMsg;
					TESTECHORECV( pClient->GetAccountID(), MsgGetCharacter )
                }
                break;
            case MSG_PLAYERMOVINGPOSTOSERVER://���߷���������ƶ�����Ϣ
                {
                    MsgPlayerMovingPosToServer* p = static_cast<MsgPlayerMovingPosToServer*>(pMsg);
                    pChar->SetFloatX(p->vPos.x);
                    pChar->SetFloatY(p->vPos.y);
                }
                break;
            case MSG_PLAYERMOVINGPOSANDDIRTOSERVER:
                {
                    MsgPlayerMovingPosAndDirToServer* p = static_cast<MsgPlayerMovingPosAndDirToServer*>(pMsg);
                    pChar->SetFloatX(p->vPos.x);
                    pChar->SetFloatY(p->vPos.y);
                }
                break;
            case MSG_PLAYERPOSTOSERVER:
                {
                    MsgPlayerPosToServer* p = static_cast<MsgPlayerPosToServer*>(pMsg);
                    pChar->SetFloatX(p->vPos.x);
                    pChar->SetFloatY(p->vPos.y);
                }
                break;
            case MSG_PLAYERPOSANDDIRTOSERVER:
                {
                    MsgPlayerPosAndDirToServer* p = static_cast<MsgPlayerPosAndDirToServer*>(pMsg);
                    pChar->SetFloatX(p->vPos.x);
                    pChar->SetFloatY(p->vPos.y);
                }
                break;
            case MSG_ACK_SWITCHGATE:
                {
                    pClient->SetClientStatus( GamePlayer::EStatusType_GetSwitchGateCallBack );                    
                    LogMessage::LogLogicDebug( "account[%d:%d] MSG_ACK_SWITCHGATE",pClient->GetAccountID(), pClient->GetGameServerPlayerId() );
                }
                break;
            case MSG_EXIT:
                {
                    pClient->SetClientStatus( GamePlayer::EStatusType_NormalExit );
                    LogMessage::LogLogicInfo( "account[%d:%d] ExitGame",pClient->GetAccountID(), pClient->GetGameServerPlayerId() );
                }
                break;
            }

            if ( !bClientValid )
            { break; }

            // ������Ϣ
            switch ( dwType )
            {
            case MSG_G2GW_ALLOCCLIENT:
            case MSG_G2GW_DELETECLIENT:
            case MSG_REGISTERSERVERACK:
            case MSG_SERVERSTATUSACK:
            case MSG_GATEINFO:
            case MSG_LOGININFO:
            case MSG_OUT_OF_LONGIN_TIME:
            case MSG_GATEACKLOGININFO:
                {
                    LogMessage::LogLogicError( "revc invalid message[%d][%u:%u:%u]", dwType, pClient->GetAccountID(), pClient->GetGameServerPlayerId(),iLoopSize );
                    pMsg = pConnector->GetMsg();
                    continue;
                }
                break;
            }

            pMsg->header.stID = pClient->GetGameServerPlayerId();
            _pGameServerConnector->SendMsg( pMsg );

            pMsg = pConnector->GetMsg();
        } // End While Msg
    }
}

void CGateServer::TellWorldGateInfo()
{
    static DWORD dwTime = HQ_TimeGetTime();

    //ÿ����֪ͨһ��
    if ( GameTime::IsPassCurrentTime( dwTime, 1000 ) )
    {
        MsgGateInfo info;
        strncpy_s( info.szGateIP, sizeof( info.szGateIP ), theCfg.szForClientIP, sizeof( info.szGateIP ) - 1 );
        info.nOnlineNum = m_iOnlineNum;
        info.nGatePort = theCfg.nForClientGatePort;
        _pGameServerConnector->SendMsg( &info );
        dwTime = HQ_TimeGetTime();
    }
}

void CGateServer::UpdateTheLoginInfo()
{ // ˢ��ʱ��Ϊ1����
    if ( !GameTime::IsPassCurrentTime( m_dwLastUpdateLoginInfoTime, 1000 * 10 ) )
    { return; }

    ItrLoginInfoContainer it = _loginInfos.begin();
    while (it != _loginInfos.end())
    {
        SLoginInfo& rLoginInfo = it->second;
        if ( GameTime::IsPassCurrentTime( rLoginInfo.recordTime, theCfg.dwConnectOverTime ) )
        {   
            if ( !rLoginInfo.isConnected )
            { // û������
                MsgConnectGateOverTime msg;                    
                msg.accountId = it->first;
                //strncpy_s( msg.szSessionKey, sizeof(msg.szSessionKey), rLoginInfo.szSessionKey, sizeof(msg.szSessionKey)-1 );
				msg.Sessionkey = rLoginInfo.SessionKey;
                _pGameServerConnector->SendMsg( &msg );
            }

            it = _loginInfos.erase( it );
            continue;
        }
        ++it;
    }
    m_dwLastUpdateLoginInfoTime = HQ_TimeGetTime();
}

//�������пͻ�����Ϣ
void CGateServer::SendAllClientMsg()
{
    int iLoopUsed=0, iLoopSize=0;
     
    BaseCharacter**ppChar = NULL,*pChar = NULL;
    GamePlayer* pClient = NULL;
    int iSize = 0;
    int iUsed = 0;

    iSize = m_pAllocClients->GetSize();
    iUsed = m_pAllocClients->GetUsed();
    for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
    {
        if (!m_pAllocClients->IsUsed(iLoopSize))
        { continue; }

        ppChar = (*m_pAllocClients)[iLoopSize];
        if( !ppChar )
        { continue; }

        ++iLoopUsed;

        pChar = *ppChar;
        if( !pChar )
        { continue; }

        pClient = (GamePlayer*)pChar;
        if ( !pClient )
        { continue; }

        /*IMeConnector*/Socketer* pConnector = pClient->GetConnector();
        if ( !pConnector )
        { continue; }

        pConnector->CheckSend();
    }
}

void CGateServer::RecvAllClientMsg()
{
	int iLoopUsed=0, iLoopSize=0;

	BaseCharacter**ppChar = NULL,*pChar = NULL;
	GamePlayer* pClient = NULL;
	int iSize = 0;
	int iUsed = 0;

	iSize = m_pAllocClients->GetSize();
	iUsed = m_pAllocClients->GetUsed();
	for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
	{
		if (!m_pAllocClients->IsUsed(iLoopSize))
		{ continue; }

		ppChar = (*m_pAllocClients)[iLoopSize];
		if( !ppChar )
		{ continue; }

		++iLoopUsed;

		pChar = *ppChar;
		if( !pChar )
		{ continue; }

		pClient = (GamePlayer*)pChar;
		if ( !pClient )
		{ continue; }

		/*IMeConnector*/Socketer* pConnector = pClient->GetConnector();
		if ( !pConnector )
		{ continue; }
		pConnector->CheckRecv();
	}
}


void CGateServer::OnMsgAllocClientAck( Msg *pMsg )
{
	//printf("11,keylogin:alloc client ok:%d\n",HQ_TimeGetTime());
    MsgAllocClientAck* pRet = (MsgAllocClientAck *)pMsg;
	MsgLoginWait msg;
	/*msg.stQueuePos=pRet->stIDGW;*/
    BaseCharacter** ppChar = (*m_pAllocClients)[ pRet->header.stID ];
    if( !ppChar )
    {
        // �����ڣ���ʾ��һ�GameAllocId��û�л���֮ǰ�Ͷ��߻����뿪��Ϸ��
        SendClientExit( pRet->stIDGW );
        return;
    }

    BaseCharacter* pChar   = *ppChar;
    GamePlayer*    pClient = (GamePlayer*)pChar;

	TESTECHORECV( pClient->GetAccountID(), MsgAllocClientAck )

    //û�з���ɹ�
    if( InvalidGameObjectId == pRet->stIDGW )
    {
        pClient->SendMsg(&msg);
		LogMessage::LogLogicError("GameServer �����������ɫʧ�� Msg_GW2G_RetAllocClient stIDGW[%d]", pRet->stIDGW);
        m_pAllocClients->Free( pRet->header.stID );
        AddToClientWaitClose( pClient, __FUNCTION__, __LINE__ );
        return;
    }

    m_pAllocClients->Free( pRet->header.stID );

    GameObjectId iID = m_pNormalClients->Malloc( pRet->stIDGW );
    if( InvalidGameObjectId == iID )
    {
        pClient->SendMsg(&msg);
		LogMessage::LogLogicError("GateServer NormalClients�����ɫʧ�� GameServerClientID[%d]", pRet->stIDGW );
        SendClientExit( pRet->stIDGW );
        AddToClientWaitClose( pClient, __FUNCTION__, __LINE__ );
        return;
    }

    GameObjectId iClientID = m_pGateClients->Malloc();
    if( InvalidGameObjectId == iClientID )
    {
        pClient->SendMsg(&msg);
		LogMessage::LogLogicError("GateServer GateClients�����ɫʧ�� GameServerClientID[%d]", pRet->stIDGW );                
        SendClientExit( pRet->stIDGW );
        m_pNormalClients->Free( iID );
        AddToClientWaitClose( pClient, __FUNCTION__, __LINE__ );
        return;
    }

    LogMessage::LogLogicDebug( "account[%u ] MsgAllocClientAck Success WaitAllocQueueId[%d] GateServerClientId[%d] GameServerPlayerId[%d]", 
        pClient->GetAccountID(),pRet->header.stID, iClientID,pRet->stIDGW);

    *(*m_pGateClients)[ iClientID ] = pChar;
    pClient->SetGateServerPlayerId( iClientID );

    //��ֵ
    *((*m_pNormalClients)[ pRet->stIDGW ]) = pChar;
    pClient->SetGameServerPlayerId( pRet->stIDGW );
    pClient->m_dwAcceptTime = 0;
	msg.getcharacter =true;
    pClient->SendMsg(&msg);
	return;
}

void CGateServer::OnMsgCreateStage( Msg *pMsg )
{
    MsgGW2GCreateStage *pMsgCreateStage = (MsgGW2GCreateStage*)pMsg;
    uint32 result = m_world.CreateStage( pMsgCreateStage->dwMapId, pMsgCreateStage->dwEctypeId );
    if ( result == ER_Success )
    { LogMessage::LogLogicInfo( "CreateStage success[0x%x:0x%x] [%u]",pMsgCreateStage->dwMapId, pMsgCreateStage->dwEctypeId, result ); }
    else
    { LogMessage::LogLogicInfo( "CreateStage fail[0x%x:0x%x] [%u]",pMsgCreateStage->dwMapId, pMsgCreateStage->dwEctypeId, result ); }
}

void CGateServer::OnMsgReleaseStage( Msg *pMsg )
{
    MsgGW2GReleaseStage *pMsgReleaseStage = (MsgGW2GReleaseStage*)pMsg;
    m_world.ReleaseStage( pMsgReleaseStage->dwEctypeId );
}


void CGateServer::OnMsgSyncCharInfo( Msg *pMsg )
{
    Msg_GW2GSyncCharInfo* pSync = static_cast< Msg_GW2GSyncCharInfo* >( pMsg );
    BaseCharacter** ppChar = NULL;
    BaseCharacter* pChar = NULL;

    ppChar = (*m_pNormalClients)[ pSync->header.stID ];
    if( !ppChar )
    { // ������
        //�����µ�NPC
        if( InvalidGameObjectId == m_pNormalClients->Malloc( pSync->header.stID ) )
        {
            LogMessage::LogLogicError("OnMsgSyncCharPos Malloc[%d]ʧ��", pSync->header.stID );
            return;
        }

        pChar = new BaseCharacter;
        if( !pChar )
        {
            LogMessage::LogLogicError( "OnMsgSyncCharPos new BaseCharacter Fail");
            m_pNormalClients->Free( pSync->header.stID );
            return;
        }
        *(*m_pNormalClients)[ pSync->header.stID ] = pChar;
    }    
    else
    {
        pChar = *ppChar;
    }

    // ʵ�ʵĿͻ��˲ż��뵽������
    if( pChar->IsPlayer() )
    {
        GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
        pPlayer->SetCountryId( pSync->uchCountryID );
        pPlayer->SetLevel( pSync->ustLevel );
    }
}

void CGateServer::OnMsgSyncCharPos( Msg *pMsg )
{
    Msg_GW2G_SyncCharPos *pSync = (Msg_GW2G_SyncCharPos*) pMsg;

    BaseCharacter** ppChar = NULL;
    BaseCharacter* pChar = NULL;

    ppChar = (*m_pNormalClients)[ pSync->header.stID ];
    if( !ppChar )
    { // ������
        //�����µ�NPC
        if( InvalidGameObjectId == m_pNormalClients->Malloc( pSync->header.stID ) )
        {
            LogMessage::LogLogicError("OnMsgSyncCharPos Malloc[%d]ʧ��", pSync->header.stID );
            return;
        }

        pChar = new BaseCharacter;
        if( !pChar )
        {
            LogMessage::LogLogicError( "OnMsgSyncCharPos new BaseCharacter Fail");
            m_pNormalClients->Free( pSync->header.stID );
            return;
        }
        *(*m_pNormalClients)[ pSync->header.stID ] = pChar;
    }    
    else
    {
        pChar = *ppChar;
    }

    // ʵ�ʵĿͻ��˲ż��뵽������
    if( pChar->IsPlayer() )
    {
        if ( pChar->GetStageID() != pSync->dwMapID || pChar->GetCurrentTileId() != pSync->stAreaID )
        {
            //��������
            //ȥ�����������е�Ӱ��
            m_world.RemoveFromTile( pSync->header.stID,pChar->GetStageID(),pChar->GetCurrentTileId() );

            //���������м���Ӱ��
            short stCurArea = m_world.AddToTile( pSync->header.stID,
                pSync->dwMapID, pSync->stAreaID );
            pChar->SetCurrentTileId( stCurArea );
        }
    }
    else
    {
        pChar->SetCurrentTileId( pSync->stAreaID );
    }
    pChar->SetStageID( pSync->dwMapID );
}

void CGateServer::OnMessageCharacterExit( Msg* pMsg )
{
    // �п��ܵ��� ��Alloc�׶���ҾͶ����˵��˳�
    BaseCharacter** ppChar = (*m_pNormalClients)[ pMsg->header.stID ];
    if( NULL == ppChar )
    { return; }

    BaseCharacter* pChar = *ppChar;
    if ( NULL == pChar)
    { return; }

    if( pChar->IsPlayer() )
    {
        GamePlayer* pGamePlayer = (GamePlayer*)pChar;
        LogMessage::LogLogicInfo( "account[%u:%u] GameNotifyGate CharExit", pGamePlayer->GetAccountID(), pGamePlayer->GetGameServerPlayerId());
        AddToClientWaitClose( pGamePlayer, __FUNCTION__, __LINE__ );
    }
    else
    {
        delete pChar;
    }
    m_pNormalClients->Free( pMsg->header.stID );
}

void CGateServer::DispatchToPlayer( Msg *pMsg )
{
    GateMsgAdditionalData* pAdd = (GateMsgAdditionalData *)(((char*)pMsg) + pMsg->GetLength() - sizeof( GateMsgAdditionalData ));

    pMsg->header.stLength -= sizeof( GateMsgAdditionalData ); // �ѿ�

    switch( pAdd->cSendRange )
    { // ������Ϣ����
    case sendrange_single:
        {
            DispatchToSingle( pAdd->data.single.stSendTarget, pMsg );
        }
        break;
    case sendrange_view:
        {
            DispatchToView( pAdd->data.view.stSendTarget, pMsg, false );
        }
        break;
    case sendrange_viewexceptme:
        {
            DispatchToView( pAdd->data.view.stSendTarget, pMsg, true );
        }
        break;
    case sendrange_area:
        {
            DispatchToArea( pAdd->data.area.dwMapId, pAdd->data.area.stAreaX, pAdd->data.area.stAreaY, pMsg );
        }
        break;
    case sendrange_region:
        {
            DispatchToRegion( pAdd->data.view.stSendTarget, pMsg );
        }
        break;
    case sendrange_stage:
        {
            DispatchToStage( pAdd->data.stage.dwMapId, pMsg );
        }
        break;
    case sendrange_world:
        {
			/*if (pMsg->GetType() == MSG_CHAT)
			{
				int n =0;
				n++;
			}*/
            DispatchToWorld( pMsg );
        }
        break;
    case sendrange_country:
        {
            DispatchToCountry( pMsg, pAdd->data.country.country, pAdd->data.country.ustlevel, pAdd->data.country.stExceptID );
        }
        break;
    }
}

void CGateServer::DispatchToSingle( GameObjectId stID, Msg *pMsg )
{
    BaseCharacter **ppChar = NULL,*pChar = NULL;
    ppChar = (*m_pNormalClients)[ stID ];
    if( !ppChar )
    { return; }

    pChar = *ppChar;
    if( !pChar->IsPlayer() )
    { return; }

    GamePlayer* pClient = (GamePlayer *)pChar;
    pClient->SendMsg( pMsg );
}

void CGateServer::DispatchToView( GameObjectId stID,Msg *pMsg,bool bExceptMe )
{
    m_world.SendMsgToView( stID,pMsg,bExceptMe );
}

void CGateServer::DispatchToRegion( GameObjectId stID, Msg *pMsg )
{
    m_world.SendMsgToRegion( stID, pMsg );
}

void CGateServer::DispatchToArea( DWORD dwMapId, int nX, int nY, Msg* pMsg )
{
    m_world.SendMsgToArea( dwMapId, nX, nY, pMsg );
}

void CGateServer::DispatchToStage( DWORD dwMapId,Msg *pMsg )
{
    m_world.SendMsgToStage( dwMapId,pMsg );
}

void CGateServer::DispatchToWorld( Msg *pMsg )
{
    m_world.SendMsgToWorld( pMsg );
}

void CGateServer::DispatchToCountry( Msg* pMsg, TCountryId country, uint16 ustLevel, uint16 stExceptID )
{
    m_world.SendMsgToCountry( pMsg, country, ustLevel, stExceptID );
}

//����½�ɹ��Ŀͻ��˼����������ӵ�TCP�ĵ�ַ�б�
void CGateServer::OnLoginInfo( MsgLoginInfo* pMsg )
{
    // �����IP�Ѿ������б��У������ʱ�� ������� ����������ڴ�IP��������
    ItrLoginInfoContainer it = _loginInfos.find( pMsg->nAccountID );

    if ( it != _loginInfos.end())
    {
        it->second.recordTime = HQ_TimeGetTime();       //����ʱ��
       //strncpy_s(it->second.szSeed,       pMsg->Seed ,        sizeof(it->second.szSeed)-1     );
       // strncpy_s(it->second.szPassword,   pMsg->Password,     sizeof(it->second.szPassword)-1 );
		it->second.SessionKey = pMsg->SessionKey;
        //strncpy_s(it->second.szSessionKey, pMsg->SessionKey, sizeof(it->second.szSessionKey)-1 );
    }
    else
    {
        SLoginInfo info;
        //strncpy_s(info.szPassword,   pMsg->Password ,   sizeof(info.szPassword)-1);
        //strncpy_s(info.szSeed,       pMsg->Seed ,       sizeof(info.szSeed)-1 );
        //strncpy_s(info.szSessionKey, pMsg->SessionKey , sizeof(info.szSessionKey)-1 );
		info.SessionKey = pMsg->SessionKey;

        info.recordTime = HQ_TimeGetTime();
        _loginInfos.insert( LoginInfoContainer::value_type( pMsg->nAccountID,info));
    }

	//printf("5,keylogin:gate recv login info back character server:%d\n",HQ_TimeGetTime());

    MsgAckLoginInfo msg;
    msg.nAccountID = pMsg->nAccountID;
    //strncpy_s( msg.SessionKey, sizeof(msg.SessionKey), pMsg->SessionKey ,sizeof(msg.SessionKey)-1);
	msg.SessionKey = pMsg->SessionKey;
    _pGameServerConnector->SendMsg( &msg );
}

void CGateServer::OnDelLoginInfo( MsgDelLoginInfo* pMsg )
{   
    ItrLoginInfoContainer it = _loginInfos.find( pMsg->accountId );

    if (it != _loginInfos.end())
    {
        SLoginInfo& rLoginInfo = it->second;
        //if ( stricmp( rLoginInfo.szSessionKey, pMsg->szSessionKey ) == 0)
		if(rLoginInfo.SessionKey == pMsg->SessionKey)
        { 
            LogMessage::LogLogicInfo("ɾ�� SessionKey[-] �����ص�¼"/*, pMsg->SessionKey */);
            _loginInfos.erase( it ); 
        }
    }
}

BaseCharacter* CGateServer::GetChar( GameObjectId stID )
{
    BaseCharacter** ppChar = NULL;
    BaseCharacter* pChar = NULL;
    ppChar = (*m_pNormalClients)[ stID ];
    if( !ppChar )
    { return 0; }
    pChar = *ppChar;
    return pChar;
}

void CGateServer::ReleaseReconnectClient( GamePlayer* pClient, bool bConnectHaveToOther /*= false*/ )
{
    if ( bConnectHaveToOther )
    { pClient->SetConnector( NULL, false ); }

    if ( pClient )
    { delete pClient; }
}

void CGateServer::AddToClientWaitClose( GamePlayer* pClient, char* szFun, int nLine )
{
    if ( !pClient )
    { return; }

    IncreaseOnlineNum( -1 );
    //LogMessage::LogLogicInfo("account[%u:%u:%u:-] AddToClientWaitClose(%s:%d)", pClient->GetAccountID(), pClient->GetGameServerPlayerId(), pClient->GetGateServerPlayerId(),/*pClient->GetSessionKey(),*/ szFun, nLine );

    // ȥ�������е�Ӱ��
    if( -1 != pClient->GetCurrentTileId() && InvalidGameObjectId != pClient->GetGameServerPlayerId() )
    {
        m_world.RemoveFromTile( pClient->GetGameServerPlayerId(), pClient->GetStageID(),pClient->GetCurrentTileId() );
    }

    if ( InvalidGameObjectId != pClient->GetGameServerPlayerId())
    {
        m_pNormalClients->Free(pClient->GetGameServerPlayerId());
    }

    // ���뵽�ȴ�����
    GameObjectId iID = m_pClientWaitClose->Malloc();
    if( InvalidGameObjectId == iID )
    {
        LogMessage::LogLogicError( "account[%u:%d:%d]m_pClientWaitClose->Malloc() Fail", pClient->GetAccountID(), pClient->GetGateServerPlayerId(), pClient->GetGameServerPlayerId());
        delete pClient;
    }
    else
    {
        *(*m_pClientWaitClose)[ iID ] = pClient;
    }
    return;
}

void CGateServer::CheckClientWaitClose( bool bWait )
{
    // ��������رյ�socket�Ƿ�ر����
    BaseCharacter** ppChar  = NULL;
    BaseCharacter*  pChar   = NULL;
    GamePlayer*     pClient = NULL;

    int iSize = m_pClientWaitClose->GetSize();
    int iUsed = m_pClientWaitClose->GetUsed();

    int iLoopUsed,iLoopSize;
    for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ;  ++iLoopSize )
    {
        ppChar = (*m_pClientWaitClose)[ iLoopSize ];
        if(  NULL == ppChar )
        { continue; }

        ++iLoopUsed;

        pChar = *ppChar;
        if( NULL == pChar)
        { continue; }

        if ( !pChar->IsPlayer() )
        {
            LogMessage::LogLogicError( "CheckClientWaitClose ���в�����ҵĽ�ɫ");
            continue;
        }

        pClient = ( GamePlayer*)pChar;

        Socketer* pConnector =  pClient->GetConnector();
        if ( NULL == pConnector )
        { continue; }

        // �ͷż���
        if( pClient->IncFreeCount()           // �����������
           /* && pConnector->IsAllMsgSendOver()*/ // ��Ϣ�Ƿ���
            && ( pClient->GetClientStatus() != GamePlayer::EStatusType_WaitSwitchGateCallBack || pClient->IsWaitAckSwitchGateTimeOut()) || !bWait ) 	
        {// �ͻ��˲��ڷ����з�״̬ ���� �ڵ���ʱ�䳬ʱ ���� ����Ҫ��
            IncreaseOnlinePlayGameNum( -1);
//             LogMessage::LogLogicInfo("account[%u] Out[-] ReleasePlayer Inc[%d] GetGateServerPlayerId[%d] GameServerPlayerId[%d]",  
//                                                                 pClient->GetAccountID(), /*pConnector->GetOutQueueSize(),*/ pClient->GetIncFreeCount(), 
//                                                                 pClient->GetGateServerPlayerId(), pClient->GetGameServerPlayerId());
            pConnector->Close();

            // ɾ��
            m_pGateClients->Free( pClient->GetGateServerPlayerId() );
            
            // ɾ��������¼�����
            m_DisConnectClient.erase( pClient->GetSessionKey() );

            m_pClientWaitClose->Free( iLoopSize );
            delete pClient;
        }
    }
}

void CGateServer::SendClientExit( GameObjectId iID )
{
    MsgGateNotifyGameDeleteClient del;
    del.header.stID = iID;
    _pGameServerConnector->SendMsg( &del );
}

void CGateServer::SendAllClientPackMsg()
{
    BaseCharacter** ppChar = NULL,*pChar = NULL;
    GamePlayer* pClient = NULL;

    int iSize = m_pGateClients->GetSize();
    int iUsed = m_pGateClients->GetUsed();
    int iLoopUsed = 0;
    for( int iLoopSize = 0; iLoopUsed<iUsed && iLoopSize<iSize; ++iLoopSize)
    {
        ppChar = (*m_pGateClients)[ iLoopSize ];
        if( !ppChar )
        { continue; }

        ++iLoopUsed;

        pChar = *ppChar;
        if( !pChar->IsPlayer() )
        { continue; }

        pClient = (GamePlayer*)pChar;
        pClient->SendPackage();

        // ��һ�α��� ��TrySend2������ѭ����
        /*IMeConnector*/Socketer* pConnector = pClient->GetConnector();
        if ( !pConnector)
        { continue; }
        pConnector->CheckSend( );
    }
}

void CGateServer::OnAddFirstList( Msg* pMsg )
{

}

void CGateServer::OnRemoveFirstList( Msg* pMsg )
{

}

CGateServer::SLoginInfo* CGateServer::GetLoginInfo( unsigned long accountId )
{
    ItrLoginInfoContainer it = _loginInfos.find( accountId );
    if ( it != _loginInfos.end())
    { return &it->second; }

    return NULL;
}

void CGateServer::CheckForServerExit()
{ // ����Ƿ��ڹرշ�����
    if ( _revShutdownCommandTime != 0 && GameTime::IsPassCurrentTime( _revShutdownCommandTime, _revShutdownDelayTime * ONE_SEC ))
    {
        LogMessage::LogSystemInfo( "�ط�ʱ��(%u:%u)��,��ʼ�ط�...", _revShutdownCommandTime, _revShutdownDelayTime );
        _pOwner->SetExitFlag();
        CloseAllClient();
        LogMessage::LogSystemInfo( "���������԰�ȫ�˳�" );
        _revShutdownCommandTime = 0;
        _revShutdownDelayTime   = 0;
        _bStopServer            = true;
		COLOR_MESSAGE( COLOR_GREEN, "[���������԰�ȫ�˳�] \n" );
    }
}

void CGateServer::PartitionLogFile()
{
    SYSTEMTIME xSystem;
    ::GetLocalTime( &xSystem );

    //LogMessage::LogSystemInfo( "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LogMessage::LogLogicInfo( "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LogMessage::LogCapabilityInfo( "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
}

void CGateServer::ShowDebugInfo()
{
    if ( _bShowAllPlayerPos )
    {
        m_world.ShowAllPlayerPos();
        _bShowAllPlayerPos = false;
    }
}

void CGateServer::CheckDisConnectClients()
{   
    if ( !xCheckDisConnectClientsTimer.DoneTimer( HQ_TimeGetTime() ))
    { return; }

    DisconnectClientContainerItr it = m_DisConnectClient.begin();
    DisconnectClientContainerItr itEnd = m_DisConnectClient.end();
    for ( ; it!=itEnd; ++it )
    {
        SDisconnectClient& xDisconnectClient = it->second;


#ifdef _DEBUG
        static const uint32 time = theCfg.netOfflineTime * 2;
#else
        static const uint32 time = theCfg.netOfflineTime;
#endif

        if ( GameTime::IsPassCurrentTime( xDisconnectClient.nDisconnectTime, time ))
        { 
            int a = 0;
        }
    }
}