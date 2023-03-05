#include "DatabaseConnectors.h"
#include "ShareData.h"
#include "BaseCharacter.h"
#include "Configure.h"
#include "MsgCutAndRebuild.h"
#include "FuncPerformanceLog.h"
#include "RunStatus.h"
#include "FileDB.h"
#include "YuanBaoHandle.h"
#include "XmlStringLanguage.h"
#include "ColorScreen.h"

DataBaseConnectors& GettheDBCon()
{
    static DataBaseConnectors theDBCon;
    return theDBCon;
}

bool g_bDBConnectted = false;
bool g_bAccountConnectted = false;
bool g_bLogConnectted = false;

DataBaseConnectors::DataBaseConnectors()
{
    _DatabaseServerConnector = NULL;
    //_AccountServerConnector  = NULL;
    //_LogServerConnector      = NULL;
    //m_nLastPingAccount       = 0;
    m_nLastPingChar          = 0;
    //m_nLastPingLog           = 0;
    //_nAccountServerPing      = 0;
    _nDatabaseServerPing     = 0;
   // m_nLogPing               = 0;
    m_bCharIsOK              = false;
}

DataBaseConnectors::~DataBaseConnectors()
{
    if( _DatabaseServerConnector )
    {
		Socketer_release(_DatabaseServerConnector);
        /*GetMeNetwork().ReleaseMeConnector( _DatabaseServerConnector->GetKey());*/
        _DatabaseServerConnector = NULL;
    }
  //  if( _AccountServerConnector )
  //  {
		//Socketer_release(_AccountServerConnector);
  //      /*GetMeNetwork().ReleaseMeConnector( _AccountServerConnector->GetKey());*/
  //      _AccountServerConnector = NULL;
  //  }
  //  if( _LogServerConnector )
  //  {
		//Socketer_release(_LogServerConnector);
  //      /*GetMeNetwork().ReleaseMeConnector( _LogServerConnector->GetKey());*/
  //      _LogServerConnector = NULL;
  //  }
}

bool DataBaseConnectors::Init( /*char* szAccountServerIP,  int iAccountServerPort,*/
                               char* szDatabaseServerIP, int iDatabaseServerPort 
                               /*char* szLogServerIP,      int iLogServerPort */)
{   
    _DatabaseServerConnector = Socketer_create();/*GetMeNetwork().CreateMeConnector();*/
    if ( !_DatabaseServerConnector )
        return false;

    if ( !CreateDatabaseServerConnectorSocket())
        return false;

    //_AccountServerConnector  = Socketer_create();/*GetMeNetwork().CreateMeConnector();*/
    //if ( !_AccountServerConnector )
    //{
    //    goto FailProcess;
    //}

    //_LogServerConnector      = Socketer_create();/*GetMeNetwork().CreateMeConnector();*/
    //if ( !_LogServerConnector )
    //{
    //    goto FailProcess;
    //}
    
    in_addr sockAddr;
    HOSTENT * lphost;

    //memset(&sockAddr,0,sizeof(sockAddr));
    //sockAddr.s_addr=inet_addr(szAccountServerIP);
    //if(sockAddr.s_addr==INADDR_NONE)
    //{
    //    lphost = ::gethostbyname(szAccountServerIP);
    //    if(lphost!=NULL)
    //    {
    //        sockAddr.s_addr = ((IN_ADDR *)lphost->h_addr)->s_addr;
    //        strncpy_s(m_szAccountServerIP, sizeof( m_szAccountServerIP ), inet_ntoa(sockAddr), sizeof(m_szAccountServerIP)-1);
    //    }
    //    else
    //    {
    //        m_szAccountServerIP[0] = 0;//ip error!
    //        MessageBox( NULL,"Failed to resolve login server ip.","Error", MB_OK | MB_ICONERROR );
    //    }
    //}
    //else
    //{
    //    strncpy_s(m_szAccountServerIP, sizeof( m_szAccountServerIP ), szAccountServerIP, sizeof(m_szAccountServerIP)-1);
    //}
    
    memset(&sockAddr,0,sizeof(sockAddr));
    sockAddr.s_addr=inet_addr(szDatabaseServerIP);
    if(sockAddr.s_addr==INADDR_NONE)
    {
        lphost = ::gethostbyname(szDatabaseServerIP);
        if(lphost!=NULL)
        {
            sockAddr.s_addr = ((IN_ADDR *)lphost->h_addr)->s_addr;
            strncpy_s(m_szCharDBIP,  sizeof( m_szCharDBIP ), inet_ntoa(sockAddr), sizeof(m_szCharDBIP)-1);
        }
        else
        {
            m_szCharDBIP[0] = 0;//ip error!
            MessageBox( NULL,"Failed to resolve character database server ip.","Error", MB_OK | MB_ICONERROR );
        }
    }
    else
    {
        strncpy_s(m_szCharDBIP, sizeof( m_szCharDBIP ), szDatabaseServerIP, sizeof(m_szCharDBIP)-1);
    }

    //memset(&sockAddr,0,sizeof(sockAddr));
    //sockAddr.s_addr=inet_addr(szLogServerIP);
    //if(sockAddr.s_addr==INADDR_NONE)
    //{
    //    lphost = ::gethostbyname(szLogServerIP);
    //    if(lphost!=NULL)
    //    {
    //        sockAddr.s_addr = ((IN_ADDR *)lphost->h_addr)->s_addr;
    //        strncpy_s(m_szLogIP, sizeof( m_szLogIP ), inet_ntoa(sockAddr), sizeof(m_szLogIP)-1);
    //    }
    //    else
    //    {
    //        m_szLogIP[0] = 0;//ip error!
    //        MessageBox( NULL,"Failed to resolve Log server ip.","Error", MB_OK | MB_ICONERROR );
    //    }
    //}
    //else
    //{
    //    strncpy_s(m_szLogIP, sizeof( m_szLogIP ), szLogServerIP, sizeof(m_szLogIP)-1);
    //}
    //_iAccountServerPort            = iAccountServerPort;
    _iDatabaserServerPort          = iDatabaseServerPort;
    /*_iLogServerPort                = iLogServerPort;*/
    //_iAccountServerConnectorState  = CS_TryConnect;
    _iDatabaseServerConnectorState = CS_TryConnect;
    //_iLogServerConnectorState      = CS_TryConnect;
    return true;
FailProcess:
  //  if ( _AccountServerConnector )
  //  {
  //      /*_AccountServerConnector->Release();*/
		//Socketer_release(_AccountServerConnector);
  //      _AccountServerConnector = NULL;
  //  }

  //  if ( _LogServerConnector )
  //  {
  //      //_LogServerConnector->Release();
		//Socketer_release(_LogServerConnector);
  //      _LogServerConnector = NULL;
  //  }
    return false;
}

void DataBaseConnectors::Shutdown()
{
    if ( _DatabaseServerConnector )
    {
        _DatabaseServerConnector->Close();
        /*GetMeNetwork().ReleaseMeConnector( _DatabaseServerConnector->GetKey() );*/
		Socketer_release(_DatabaseServerConnector);
        _DatabaseServerConnector = NULL;
    }

  //  if ( _AccountServerConnector )
  //  {
  //      _AccountServerConnector->Close();
  //      /*GetMeNetwork().ReleaseMeConnector( _AccountServerConnector->GetKey());*/
		//Socketer_release(_AccountServerConnector);
  //      _AccountServerConnector = NULL;
  //  }
    
  //  if ( _LogServerConnector )
  //  {
  //      _LogServerConnector->Close();
  //      /*GetMeNetwork().ReleaseMeConnector( _LogServerConnector->GetKey() );*/
		//Socketer_release(_LogServerConnector);
  //      _LogServerConnector = NULL;
  //  }
}

bool DataBaseConnectors::CreateDatabaseServerConnectorSocket()
{
    if ( !_DatabaseServerConnector )
        return false;

    //if(_DatabaseServerConnector->GetSocket()->Create())
    //{   
    //    if(!_DatabaseServerConnector->CheckIsDifferentSocket())
    //    { // 这次Create的和上次的一样
    //        IMeSocket* pSocket = GetMeNetwork().CreateMeSocket();
    //        if(!pSocket->Create())
    //        {
    //            pSocket->Release();
    //            _DatabaseServerConnector->GetSocket()->Close();
    //            return false;
    //        }
    //        else
    //        {
    //            _DatabaseServerConnector->GetSocket()->Close();
    //            _DatabaseServerConnector->SetSocket( pSocket );
    //            return true;
    //        }
    //    }
    //    return true;
    //}
    return true;
}

void DataBaseConnectors::TryConnectToDatabaseServer()
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
        break;
    }
    if ( !_DatabaseServerConnector)
    {
        _DatabaseServerConnector = Socketer_create();/*GetMeNetwork().CreateMeConnector()*/;
        return;
    }

    switch( _iDatabaseServerConnectorState )
    {
    case CS_TryConnect:
        {
            _connectTime.StartTimer( HQ_TimeGetTime(), ECD_ConnectIntervalTime );
            if ( !_connectTime.DoneTimer( HQ_TimeGetTime() ))
            { return; }

            if(_DatabaseServerConnector->Connect( m_szCharDBIP,_iDatabaserServerPort/*, 5 */))
            {   
               /* _DatabaseServerConnector->BuildKey();
                bool bResult = GetMeNetwork().RegisterMeConnector( _DatabaseServerConnector->GetKey(), _DatabaseServerConnector );
                if ( bResult )*/
                {   
                    /*unsigned long nResult = _DatabaseServerConnector->EnableIoCompletionPort( false );
                    if ( ER_Success != nResult)
                    {
                        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"TryConnectToDatabaseServer EnableIoCompletionPort Fail(%u)", nResult);
                        unsigned int nKey = _DatabaseServerConnector->GetKey();
                        _DatabaseServerConnector->Close();
                        GetMeNetwork().ReleaseMeConnector( nKey );
                        _DatabaseServerConnector = GetMeNetwork().CreateMeConnector();
                        return;
                    }*/
                    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Connect DatabaseServer Success" );
                    _iDatabaseServerConnectorState = CS_Connectted;
                    _nDatabaseServerPing = HQ_TimeGetTime();
                    // 连接成功
                    //_DatabaseServerConnector->SetMaxQueueMsgNum ( IMeConnector::ET_InQueue, -1 );
                    //_DatabaseServerConnector->SetMaxQueueMsgNum ( IMeConnector::ET_OutQueue, -1 );
                    g_bDBConnectted = true;
                    //将备份队列导入文件
                    //BackupSaveCharToFile();

                    //CSaveCharBackFile loader;
                    //loader.LoadMsgFromFile();

                    MsgReqInitData msg;
                    SendMsgToDatabaseServer( &msg  );
                }
              /*  else
                {
                    _iDatabaseServerConnectorState = CS_ReConnect;
                }*/
            }
            else
            {
                g_bDBConnectted = false;
            }
        }
        break;
    case CS_ReConnect:
        {   
            _DatabaseServerConnector->Close();
            /*GetMeNetwork().ReleaseMeConnector( _DatabaseServerConnector->GetKey() );*/
			Socketer_release(_DatabaseServerConnector);
            _DatabaseServerConnector = Socketer_create();/*GetMeNetwork().CreateMeConnector();*/
            if ( !_DatabaseServerConnector )
            { return; }

            CreateDatabaseServerConnectorSocket();
            _iDatabaseServerConnectorState = CS_TryConnect;
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Begin ReConnect DatabaseServer");
        }
        break;
    }

    //if( pSocket->Connect( m_szCharDBIP,_iDatabaserServerPort,0 ) )
    //{
 //       _DatabaseServerConnector->BuildKey();
 //       bool bRegisterResult = GetMeNetwork().RegisterMeConnector( _DatabaseServerConnector->GetKey(), _DatabaseServerConnector );
 //       if ( !bRegisterResult )
 //       {
 //           _DatabaseServerConnector->Close();
 //           LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "TryConnectToDatabaseServer->RegisterMeConnector Fail" );
 //       }
 //       else
 //       {  
 //           LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Connect DatabaseServer Success" );
    //        _iDatabaseServerConnectorState = CS_Connectted;
 //           _nDatabaseServerPing = HQ_TimeGetTime();
    //        //连接成功
 //           _DatabaseServerConnector->EnableIoCompletionPort( false );        
    //        g_bDBConnectted = true;
 //           //将备份队列导入文件
    //        //BackupSaveCharToFile();

    //        //CSaveCharBackFile loader;
    //        //loader.LoadMsgFromFile();
 //       }
    //}
    //else
    //{
    //    if( pSocket->IsClosed() )
    //    {
    //        pSocket->Create();
    //    }
    //    g_bDBConnectted = false;
    //    //将备份队列导入文件
    //    //BackupSaveCharToFile();
    //}
}

//void DataBaseConnectors::TryConnectToAccountServer()
//{
//    /*IMeSocket* pSocket = _AccountServerConnector->GetSocket();*/
//    if( _AccountServerConnector->Connect( m_szAccountServerIP,_iAccountServerPort) )
//    {
//        /*_AccountServerConnector->BuildKey();
//        bool bRegisterResult = GetMeNetwork().RegisterMeConnector( _AccountServerConnector->GetKey(), _AccountServerConnector );
//        if ( !bRegisterResult )
//        {
//            _AccountServerConnector->Close();
//            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "TryConnectToAccountServer->RegisterMeConnector Fail" );
//        }
//        else*/
//        {
//            _iAccountServerConnectorState = CS_Connectted;
//            _nAccountServerPing = HQ_TimeGetTime();
//            //连接成功
//            //_AccountServerConnector->EnableIoCompletionPort( false );
//            g_bAccountConnectted = true;
//
//            //发送ServerID
//            MsgServerID serverid;
//            serverid.dwServerID = g_Cfg.dwServerID;
//            _AccountServerConnector->SendMsg( &serverid );
//        }
//    }
//    else
//    {
//        if(!_AccountServerConnector)
//        {
//			_AccountServerConnector = Socketer_create();
//        }
//        g_bAccountConnectted = false;
//    }
//}

//void DataBaseConnectors::TryConnectToLogServer()
//{
//    /*IMeSocket* pSocket = _LogServerConnector->GetSocket();*/
//    if( _LogServerConnector->Connect( m_szLogIP,_iLogServerPort) )
//    {
//        /*_LogServerConnector->BuildKey();
//        bool bRegisterResult = GetMeNetwork().RegisterMeConnector( _LogServerConnector->GetKey(), _LogServerConnector );
//        if ( !bRegisterResult )
//        {
//            _LogServerConnector->Close();
//            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "TryConnectToLogServer->RegisterMeConnector Fail" );
//        }
//        else*/
//        {
//            _iLogServerConnectorState = CS_Connectted;
//            m_nLogPing = HQ_TimeGetTime();
//            //连接成功
//            //_LogServerConnector->EnableIoCompletionPort( false );
//            g_bLogConnectted = true;
//
//            //发送ServerID
//            MsgServerID serverid;
//            serverid.dwServerID = g_Cfg.dwServerID;
//            _LogServerConnector->SendMsg( &serverid, 0 );
//        }
//    }
//    else
//    {
//        if( !_LogServerConnector )
//        {
//            _LogServerConnector = Socketer_create();
//        }
//        g_bLogConnectted = false;
//    }
//}

//发送消息
void DataBaseConnectors::SendMsg( Msg *pMsg,unsigned short ustLifeCode )
{
    if (pMsg == NULL)
        return;

    DBMsg *pDBMsg = (DBMsg *)pMsg;
    pDBMsg->ustLifeCode = ustLifeCode;

    DWORD dwType = pMsg->GetType();

    switch(dwType)
    {
    case DBMSG_LOG:
        //SendMsgToLogServer( pDBMsg );
        break;
    case DBMSG_LOGIN:
    case DBMSG_OFFLINE:
    case DBMSG_ACCOUNTSTATE:
        //SendMsgToAccountServer( pDBMsg );
        break;
    default:
        SendMsgToDatabaseServer( pDBMsg );
        break;
    }
}

void DataBaseConnectors::DispatchToPlayer( Msg *pMsg )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( pMsg->header.stID );
    if( NULL == pChar || !pChar->IsPlayer() )
    {
        //做处理
        goto msghander_quit;
    }
    
    //转发到玩家    
    ((NetControl*)pChar->GetControl())->Push2In( pMsg );
    return;

msghander_quit:
    OnDBMsgHandlerMiss( (DBMsg*)pMsg );
}


//将收到得消息转发给角色
void DataBaseConnectors::DispatchMsgToPlayers( void )
{
    Msg* pMsg = NULL;
    //if( CS_Connectted == _iAccountServerConnectorState )
    //{
    //    while( pMsg = _AccountServerConnector->GetMsg() )
    //    {
    //        if(MSG_PING == pMsg->GetType())
    //        {
    //            _nAccountServerPing = HQ_TimeGetTime();
    //            continue;
    //        }
    //        DispatchToPlayer( pMsg );
    //    }
    //}

    //if( CS_Connectted == _iLogServerConnectorState )
    //{
    //    while( pMsg = _LogServerConnector->GetMsg() )
    //    {
    //        if(MSG_PING == pMsg->GetType())
    //        {
    //            m_nLogPing = HQ_TimeGetTime();
    //            continue;
    //        }
    //    }
    //}

    if( CS_Connectted == _iDatabaseServerConnectorState )
    {
        while( pMsg = _DatabaseServerConnector->GetMsg() )
        {
            if( MSG_PING == pMsg->GetType())
            {
                _nDatabaseServerPing = HQ_TimeGetTime();
                m_bCharIsOK = true;
            }
            else if (DBMSG_ACK_ACCOUNT_BILLING == pMsg->GetType())
            { 
                DBMsgAckAccountBilling* pMessage = (DBMsgAckAccountBilling*)pMsg;
                BaseCharacter* pChar = theRunTimeData.GetCharacterByAccountID( pMessage->guid );
                if ( pChar == NULL || !pChar->IsPlayer())
                { return; }

                GamePlayer* pGamePlayer = (GamePlayer* )pChar;
                pGamePlayer->OnMsgAckJinDing( pMsg );
            }
            else if (DBMSG_ACKOPERSUCC == pMsg->GetType())
            { // 返回保存操作成功消息
                DBAckOperSucc* pAck = (DBAckOperSucc*)pMsg;
                BaseCharacter* pChar = (BaseCharacter*)theRunTimeData.GetCharacterByID( pAck->header.stID );
                if( pChar && pChar->IsPlayer() )
                {
                    GamePlayer* pGamePlayer = (GamePlayer*)pChar;
                    if ( pGamePlayer && pGamePlayer->IsWantSwitchGameWaitSaveInfoOk())
                    {
                        pGamePlayer->SendClientSwitchGateInfo();
                    }
                    else
                    {
                        //GettheFileDB().OnDBMsg(pAck);
                        //GettheYuanBaoHandle().OnDBMsg(pAck);
                    }
                }
            }
			else if(DB2DB_CashResult == pMsg->GetType())
			{
				DB2DBCashResult* pCashResult = (DB2DBCashResult*)pMsg;
				if (!pCashResult||pCashResult->result != eDB2DBCashResult_succ)
				{
					return;
				}
				GamePlayer* pPlayer = theRunTimeData.GetCharacterByAccountID(pCashResult->account_id);
				if (pPlayer)
				{
					MsgRMBGoldChange xChange;
					xChange.header.stID = pPlayer->GetID();
					xChange.jinDing     = pCashResult->all_money;
					xChange.jinPiao     = pPlayer->GetJinPiao();
					/*xChange.jifen		= pPlayer->GetConsumeScore();*/
					pPlayer->SendMessageToClient( &xChange );

					pPlayer->OperateJinDing( EOT_Set, pCashResult->all_money, __FUNCTION__, __LINE__,ePlayerMoneySourceType_Cache,false);

					//操作玩家充值 我们还需要处理 玩家是否为首充
					//xuda pCashResult->account_yuanbao_states
					//将这个属性 发送到客户端去 有客户端去处理
					if(pCashResult->account_yuanbao_states != pPlayer->GetYuanBaoStates() || pPlayer->GetYuanBaoTotle() != pCashResult->account_yuanbao_totle)
					{
						//发送到客户端去 更新UI的状态
						MsgUpdateYuanBaoData msg;
						msg.dwAccountYuanBaoTotle = pCashResult->account_yuanbao_totle;
						msg.dwAccountYuanBaoStates = pCashResult->account_yuanbao_states;
						pPlayer->SendMessageToClient(&msg);
						pPlayer->SetYuanBaoStates(pCashResult->account_yuanbao_states);
						pPlayer->SetYuanBaoTotle(pCashResult->account_yuanbao_totle);
					}	
				}
				
			}
			else if (DB2DB_ConsumeScoreResult == pMsg->GetType())
			{
				DB2DBConsumeScoreResult* pConsumeScoreResult = (DB2DBConsumeScoreResult*)pMsg;
				if (!pConsumeScoreResult||pConsumeScoreResult->result != eDB2DBCashResult_succ)
				{
					return;
				}
				GamePlayer* pPlayer = theRunTimeData.GetCharacterByAccountID(pConsumeScoreResult->account_id);
				if (pPlayer)
				{
					//MsgRMBConsumeScore xChange;
					//xChange.header.stID = pPlayer->GetID();
					////xChange.jinDing     = pPlayer->GetJinDing();
					////xChange.jinPiao     = pPlayer->GetJinPiao();
					//xChange.jifen		= pConsumeScoreResult->money;
					//pPlayer->SendMessageToClient( &xChange );

					pPlayer->OperateConsumeScore( EOT_Set, pConsumeScoreResult->all_money, __FUNCTION__, __LINE__,ePlayerMoneySourceType_Cache,false);
				}
			}
            else
            {
                DispatchToPlayer(pMsg);
            }
        }
    }
}

//void DataBaseConnectors::SendMsgToAccountServer( Msg *pMsg )
//{
//    if( CS_Connectted != _iAccountServerConnectorState )
//    {
//        DWORD dwType = pMsg->GetType();
//        //
//        if (DBMSG_LOGIN == dwType)
//        {
//            //角色必须有登录超时判定
//        }
//        else if (DBMSG_OFFLINE == dwType)
//        {
//        }
//    }
//    else
//    {
//        if ( _AccountServerConnector )
//            _AccountServerConnector->SendMsg( pMsg );
//    }
//}

//void DataBaseConnectors::SendMsgToLogServer( Msg *pMsg )
//{
//    if( CS_Connectted == _iLogServerConnectorState && _LogServerConnector)
//    {
//        _LogServerConnector->SendMsg( pMsg );
//    }
//}

void DataBaseConnectors::SendMsgToDatabaseServer( Msg *pMsg )
{
    //将DBMSG_SAVECHAR放到备份队列中
    //if (DBMSG_SAVECHARACTER == pMsg->GetType())
    //{
    //    m_backSaveChar.BackupMsg( (DBMsg*)pMsg );
    //}
    //
    if( CS_Connectted != _iDatabaseServerConnectorState )
    {
        //处理
    }
    else
    {
        if ( _DatabaseServerConnector )
        {
            _DatabaseServerConnector->SendMsg( pMsg );
            //_DatabaseServerConnector->CheckSend( );
        }
    }
}

void DataBaseConnectors::OnDBMsgHandlerMiss( DBMsg *pDBMsg )
{
    if (DBMSG_ACKLOGIN == pDBMsg->GetType())
    {
        DBMsgAckLogin2 *pAckMsg = ( DBMsgAckLogin2* )pDBMsg;

        //没有登录成功，不处理
        if( MsgAckLogin::ret_succ == pAckMsg->stRet )
        {
            DBMsgOffline2 msgOffline;

            msgOffline.dwAccountID = pAckMsg->dwAccountID;

            SendMsg( &msgOffline,pAckMsg->ustLifeCode );
        }
    }
    else if (DBMSG_KICKCHAR == pDBMsg->GetType())
    {
        S2SMsgKickChar* kick = (S2SMsgKickChar*)pDBMsg;
        GamePlayer* pPlayer = theRunTimeData.GetCharacterByAccountID( kick->dwAccountID );
        if(pPlayer)
        {
            pPlayer->TellClient( theXmlString.GetString(eClient_AddInfo_2slk_71));
            pPlayer->Log( "Exit By %s", theXmlString.GetString(eClient_AddInfo_2slk_71) );
            pPlayer->OnExit(NULL);
        }
    }
    else if ( DB2GS_ACK_INIT_DATA == pDBMsg->GetType() )
    {
    }
}

void DataBaseConnectors::RunOneStep()
{
    usetime[50].szFunctionName = "DataBaseConnectors::TryConnectToAccountServer";
    __int64 funtime = HelperFunc::GetCPUTime();
    unsigned int nTime = HQ_TimeGetTime(); 

#ifndef _WITH_CENTERSERVER_ 
    if( CS_TryConnect == _iAccountServerConnectorState )
    {
        TryConnectToAccountServer();
    }
    else
    {
        if(nTime - m_nLastPingAccount > 10000)
        {
            MsgPingMsg msgPing;
            SendMsgToAccountServer(&msgPing);
            m_nLastPingAccount = nTime;
        }

        _AccountServerConnector->TrySend2( false );

        if( _AccountServerConnector->IsClosed() 
            && RunStatus::RunStatus_GameThreadStopped != gServerStatus._runstatus  )
        {
            //因为启用FileDB,所以当DBGate断开连接时，可以不用把所有玩家踢掉了。
            //GettheServer().OnDBConBroken();
            _iAccountServerConnectorState = CS_ReConnect;            
        }

        //服务器长时间没有返回ping，认为与服务器连接断开，准备重连
        if(HQ_TimeGetTime() - _nAccountServerPing > 10000)
        {
            _iAccountServerConnectorState = CS_ReConnect;   
        }
    }
    usetime[50].nTime += (HelperFunc::GetCPUTime() - funtime);
    
    usetime[51].szFunctionName = "DataBaseConnectors::TryConnectToLogServer";
    funtime = HelperFunc::GetCPUTime();
    if( CS_TryConnect == _iLogServerConnectorState )
    {
        TryConnectToLogServer();
    }
    else
    {
        if(nTime - m_nLastPingLog > 10000)
        {
            MsgPingMsg msgPing;
            SendMsgToLogServer(&msgPing);
            m_nLastPingLog = nTime;
        }
        _LogServerConnector->TrySend2( false );
        if( _LogServerConnector->IsClosed() 
            && RunStatus::RunStatus_GameThreadStopped != gServerStatus._runstatus  )
        {
            //因为启用FileDB,所以当DBGate断开连接时，可以不用把所有玩家踢掉了。
            //GettheServer().OnDBConBroken();
            _iLogServerConnectorState = CS_ReConnect;            
        }

        //服务器长时间没有返回ping，认为与服务器连接断开，准备重连
        if(HQ_TimeGetTime() - m_nLogPing > 10000)
        {
            _iLogServerConnectorState = CS_ReConnect;   
        }
    }

    usetime[51].nTime += (HelperFunc::GetCPUTime() - funtime);
#endif

    usetime[52].szFunctionName = "DataBaseConnectors::TryConnectToDatabaseServer";
    funtime = HelperFunc::GetCPUTime();

    if( CS_Connectted != _iDatabaseServerConnectorState )
    {
        TryConnectToDatabaseServer();
    }
    else
    {   
        // GettheYuanBaoHandle().SendToDBInfo();
        if(nTime - m_nLastPingChar > 10000)
        {
            //MsgPingMsg msgPing;
            //SendMsgToDatabaseServer(&msgPing);
            m_nLastPingChar = nTime;
        }

		_DatabaseServerConnector->CheckRecv();
        _DatabaseServerConnector->CheckSend( );

        if( _DatabaseServerConnector->IsClose() )
        {
            //启用FileDB后与DB断开连接可以不用踢人了
            //GettheServer().OnDBConBroken();
            _iDatabaseServerConnectorState = CS_ReConnect;
        }

#ifndef _DEBUG
        //if(HQ_TimeGetTime() - _nDatabaseServerPing > CD_iPingDatabaseServerTime)
        //{
        //_iDatabaseServerConnectorState = CS_ReConnect;   
        //}
#endif
    }
    usetime[52].nTime += (HelperFunc::GetCPUTime() - funtime);


    usetime[53].szFunctionName = "DataBaseConnectors::DispatchMsgToPlayers";
    funtime = HelperFunc::GetCPUTime();

    DispatchMsgToPlayers();

    usetime[53].nTime += (HelperFunc::GetCPUTime() - funtime);

    // 确认发送队列为空，SaveChar备份队列为空 保证全部数据入库 服务器关闭
    if( RunStatusDefine::RunStatus_GameThreadStopped == theRunStatus.GetStatus() )
    {    
        theRunStatus.SetStatus( RunStatusDefine::RunStatus_DBThreadStopped );
        GettheServer().NotifyMainConsoleThread();
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "服务器可以安全退出" );
		COLOR_MESSAGE( COLOR_GREEN, "[服务器可以安全退出] \n" );
    }
}

//void DataBaseConnectors::BackupSaveCharToFile( void )
//{
//    CSaveCharBackFile saver;
//    //保存m_backSaveChar中的消息
//    char szBuf[ MSGCANCUTMAXSIZE ];
//    DBMsgSaveCharacter *pSave = (DBMsgSaveCharacter *)szBuf;
//    while( m_backSaveChar.PopMsg( szBuf ) )
//    {
//        if( pSave->GetType() != DBMSG_SAVECHARACTER 
//            || pSave->GetLength() != sizeof( DBMsgSaveCharacter ) )
//        {
//            // ToLog( false );
//            continue;
//        }
//        saver.SaveMsgToFile( pSave );
//    }
//}

bool DataBaseConnectors::IsDBConnectted()
{
#ifndef _WITH_CENTERSERVER_
    if( ( CS_Connectted == _iAccountServerConnectorState ) && ( CS_Connectted == _iDatabaseServerConnectorState ) )
        return true;
#else
    if( CS_Connectted == _iDatabaseServerConnectorState )
        return true;
#endif
    
    return false;
}

bool DataBaseConnectors::IsAllMsgSendOver()
{   
    return true/*_DatabaseServerConnector->IsAllMsgSendOver()*/;
}
