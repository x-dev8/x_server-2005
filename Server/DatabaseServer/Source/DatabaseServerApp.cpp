#include "DatabaseServerApp.h"
#include "DatabaseClient.h"
#include "DatabaseInterface.h"
#include "ClientListener.h"
#include "ResourcePath.h"
//#include "NetApi.h"
#include "Tinyxml/tinyxml.h"
#include "MySqlCommunication.h"
#include "RunStatus.h"
#include "FileDatabase.h"
#include "NetWorkParameterDefine.h"
#include "BillingManager.h"

DatabaseServerApp* GetDatabaseServerApp()
{
    static DatabaseServerApp instance;
    return &instance;
}

DatabaseServerApp::DatabaseServerApp():_DatabaseClient(100)
{
    m_bSleepTime           = false;
    useSqlType             = ST_MySql;
    revShutdownCommandTime = 0;
    revShutdownDelayTime   = 0;

	m_ClientListen = NULL;
	m_bAccountBilling = false;
}

DatabaseServerApp::~DatabaseServerApp()
{
	if (m_ClientListen)
	{
		m_ClientListen->Close();
		Listener_release(m_ClientListen);
		m_ClientListen = NULL;
	}
}

uint32 DatabaseServerApp::Init( const char* szConfigFilePath )
{
    //system("Pause");
   /* GetMeNetwork().SocketStartUp();
    GetMeNetwork().StartIoCompletionPort( 1, -1 );*/

    int eError = 0;
    bool bResult = LoadConfig( szConfigFilePath,eError );
    if ( !bResult )
    { return eError; }

    //HelperFunc::CreateOutputFolder( OUTPUT_DIRECTORY );

    //try
    //{
    //    LOG_CONFIGURE( strLogConfigFilePath.c_str() );
    //}
    //catch(ConfigureException&)
    //{   
    //    return 2;
    //}

    //初始化FileMapping
    uint32 result = theFileMappingCharSaveManager.Init();
    if ( result != ER_Success )
    { 
        std::cout << result <<"=theFileMappingCharSaveManager.Init() fail" << std::endl; 
        system("pause");
        return ER_Failed;
    }

    if ( useSqlType == ST_MSSql )
    {
        if( !GetDatabaseInterface()->Init() )
        { return 3; }
    }

    if ( ER_Success != theMysqlCommunication.Init( roleDbName,    roleHost,    roleDbPort,    roleUID,    rolePwd, 
        billingDbName, billingHost, billingDbPort, billingUID, billingPwd ) )
    { return ER_Failed; }

	if (!network::net_init(eN_DBServer_BigBufferSize,
						   eN_DBServer_BigBufferNum,
						   eN_DBServer_SmallBufferSize,
						   eN_DBServer_SmallBufferNum,
						   eN_DBServer_ListenNum,
						   eN_DBServer_SocketNum,
						   eN_DBServer_ThreadNum))
	{
		return 0;
	}

    /*ClientListener* pListener = new ClientListener;
    if ( NULL == pListener)
    { return ER_Failed;}*/
	m_ClientListen = Listener_create();
	if (!m_ClientListen)
	{
		return ER_Failed;
	}
	if (!m_ClientListen->Listen(m_wListenPort,5))
	{
		return ER_Failed;
	}

    //if( !pListener->Init() )
    //{
    //    delete pListener;
    //    return 4;
    //}

    //RegisterNode( pListener );
    return ER_Success;
}
void DatabaseServerApp::ShutDown()
{
    if ( useSqlType == ST_MSSql )
    { GetDatabaseInterface()->ShutDown();}

    theMysqlCommunication.ShutDown();

	if (m_ClientListen)
	{
		m_ClientListen->Close();
		Listener_release(m_ClientListen);
		m_ClientListen = NULL;
	}

	net_release();
    /*INetworkApp::ShutDown();
    GetMeNetwork().StopIoCompletionPort();
    GetMeNetwork().SocketCleanUp();*/

    std::string applicationName = APPLICATION_NAME;
#ifdef _DEBUG
    applicationName += "-Debug";
#endif
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "%s  Safely Exit", applicationName.c_str());
}

void DatabaseServerApp::RecvAllClientMsg()
{
	int iLoopUsed =0,iLoopSize = 0;
	DatabaseClient **ppDC=NULL,*pDC = NULL;
	int iUsed = _DatabaseClient.GetUsed();
	int iSize = _DatabaseClient.GetSize();
	for (iLoopUsed = 0,iLoopSize = 0;iLoopUsed < iUsed&&iLoopSize < iSize;iLoopSize++)
	{
		ppDC = _DatabaseClient[iLoopSize];
		if (!ppDC||!*ppDC)
		{
			continue;
		}
		pDC = *ppDC;
		iLoopUsed++;
		if (!pDC->GetConnector()||pDC->GetConnector()->IsClose())
		{
			//这里要写一个延迟释放的脏标记，现在不安全 by qfwang
			//_DatabaseClient.Free(iLoopSize);
			//delete pDC;
			continue;
		}
		pDC->GetConnector()->CheckRecv();
	}
}

bool DatabaseServerApp::AcceptNewClient()
{
	if (!m_ClientListen||m_ClientListen->IsClose())
	{
		return false;
	}

	Socketer* pSocket = m_ClientListen->Accept();
	if (!pSocket)
	{
		LogMessage::LogSystemError("AcceptNewClient::Accept error");
		return false;
	}

	int iID = 0;
	iID = _DatabaseClient.Malloc();
	if (iID < 0)
	{
		LogMessage::LogSystemError("AcceptNewClient::Malloc error");
		if (pSocket)
		{
			Socketer_release(pSocket);
			pSocket = NULL;
		}
		return false;
	}

	DatabaseClient* pDC = new DatabaseClient;
	if (!pDC)
	{
		LogMessage::LogSystemError("AcceptNewClient::Malloc error");
		if (pSocket)
		{
			Socketer_release(pSocket);
			pSocket = NULL;
		}
		return false;
	}

	pDC->SetConnector(pSocket);
	pDC->SetId(iID);
	*_DatabaseClient[iID] = pDC;
	return true;
}

void DatabaseServerApp::ProcessClientMsg()
{
	int iLoopUsed =0,iLoopSize = 0;
	DatabaseClient **ppDC=NULL,*pDC = NULL;
	int iUsed = _DatabaseClient.GetUsed();
	int iSize = _DatabaseClient.GetSize();
	for (iLoopUsed = 0,iLoopSize = 0;iLoopUsed < iUsed&&iLoopSize < iSize;iLoopSize++)
	{
		ppDC = _DatabaseClient[iLoopSize];
		if (!ppDC||!*ppDC)
		{
			continue;
		}
		pDC = *ppDC;
		iLoopUsed++;
		if (!pDC->GetConnector()||pDC->GetConnector()->IsClose())
		{
			//这里要写一个延迟释放的脏标记，现在不安全 by qfwang
			//_DatabaseClient.Free(iLoopSize);
			//delete pDC;
			continue;
		}
		pDC->ProcessMsgs();
	}
}

void DatabaseServerApp::SendAllClientMsg()
{
	int iLoopUsed =0,iLoopSize = 0;
	DatabaseClient **ppDC=NULL,*pDC = NULL;
	int iUsed = _DatabaseClient.GetUsed();
	int iSize = _DatabaseClient.GetSize();
	for (iLoopUsed = 0,iLoopSize = 0;iLoopUsed < iUsed&&iLoopSize < iSize;iLoopSize++)
	{
		ppDC = _DatabaseClient[iLoopSize];
		if (!ppDC||!*ppDC)
		{
			continue;
		}
		pDC = *ppDC;
		iLoopUsed++;
		if (!pDC->GetConnector()||pDC->GetConnector()->IsClose())
		{
			//这里要写一个延迟释放的脏标记，现在不安全 by qfwang
			//_DatabaseClient.Free(iLoopSize);
			//delete pDC;
			continue;
		}
		pDC->GetConnector()->CheckSend();
	}
}

void DatabaseServerApp::RunOneStep()
{
	net_run();
	while(m_ClientListen->CanAccept())
	{
		if (!AcceptNewClient())
		{
			break;
		}
	}
	RecvAllClientMsg();

	ProcessClientMsg();

	SendAllClientMsg();

	//if (bOpenBillingService)
	{//billing server的服务
		theBillingManager.Run();
	}
}


void DatabaseServerApp::Update()
{
    if ( useSqlType == ST_MSSql )
    { GetDatabaseInterface()->Update(); }

    theMysqlCommunication.Update();

    /*INetworkApp::Update();*/
	RunOneStep();

    CheckForServerExit();
}

bool DatabaseServerApp::LoadConfig( const char* szConfigFilePath, int& nResultError  )
{
    bool bResult = InitNetSetting();
    if ( !bResult )
    { 
        nResultError = 1;
        return false; 
    }

    TiXmlDocument doc;
    if ( !doc.LoadFile( szConfigFilePath ) )
    { 
        nResultError = 10;
        return false; 
    }

    int    nValue      = 0;
    double dValue      = 0.0f;
    const char* szTemp = NULL;

    TiXmlElement* pProject = doc.FirstChildElement("Project");
    if ( !pProject )
    { return false; }

    szTemp = pProject->Attribute("Name");
    if ( !szTemp )
    { return false; }
    m_strDatabaseName = szTemp;

    TiXmlElement* pSetting = pProject->FirstChildElement("Setting");
    if ( !pSetting)
    { return false; }

    TiXmlElement* pLogic = pSetting->FirstChildElement("Logic");
    if ( !pLogic )
    { return false; }

    szTemp = pLogic->Attribute("LogConfigFile");
    if ( !szTemp)
    { return false; }

    strLogConfigFilePath = szTemp;

    pLogic->Attribute("EnterWorldConfine", &nValue );
    m_dwEnterWorldConfine = nValue;

    pLogic->Attribute("RoleSaveConfine", &nValue );
    m_RoleSaveMax = nValue;

    pLogic->Attribute("OtherSaveConfine", &nValue );
    m_OtherSaveMax = nValue;

	pLogic->Attribute("UseCancelDel", &nValue );
	m_bUseCancelDel = nValue;

    TiXmlElement* pSleep = pSetting->FirstChildElement("Sleep");
    if ( pSleep != NULL )
    {
        pSleep->Attribute( "Time", &nValue );
        m_bSleepTime = nValue;
    }
	
	return true;
}

bool DatabaseServerApp::InitNetSetting()
{
    TiXmlDocument doc;
    if (!doc.LoadFile( NETSETTING_FILEPATH ))
    { return false; }

    int    nValue      = 0;
    double dValue      = 0.0f;
    const char* szTemp = NULL;

    TiXmlElement* pProject = doc.FirstChildElement("Project");
    if ( !pProject )
    { return false; }

    TiXmlElement* pSetting = pProject->FirstChildElement("Setting");
    if ( !pSetting)
    { return false; }

    TiXmlElement* pDatabase = pSetting->FirstChildElement("Database");
    if ( !pDatabase )
    { return false; }

    TiXmlElement* pListenPort = pDatabase->FirstChildElement("ListenPort");
    if ( !pListenPort )
    { return false; }

    pListenPort->Attribute("AllServer", &nValue );
    m_wListenPort = nValue;

    std::string strHost;

    TiXmlElement* pGameDB = pDatabase->FirstChildElement("GameDB");
    if ( !pGameDB )
    { return false; }

    szTemp = pGameDB->Attribute("Host");
    if ( !szTemp )
    { return false; }

    strHost = /*NetApi::GetHostByName*/(szTemp);
    if ( strHost.empty())
    { return false; }
    roleHost = strHost;

    pGameDB->Attribute("Port", &nValue);
    roleDbPort = nValue;

    szTemp = pGameDB->Attribute("User");
    if ( !szTemp )
    { return false; }
    roleUID = szTemp;

    szTemp = pGameDB->Attribute("Password");
    if ( !szTemp )
    { return false; }
    rolePwd = szTemp;

    szTemp = pGameDB->Attribute("Name");
    if ( !szTemp )
    { return false; }
    roleDbName = szTemp;

    TiXmlElement* pBillingDB = pDatabase->FirstChildElement("BillingDB");
    if ( !pBillingDB )
    { return false; }

    szTemp = pBillingDB->Attribute("Host");
    if ( !szTemp )
    { return false; }

    strHost = /*NetApi::GetHostByName*/(szTemp);
    if ( strHost.empty())
    { return false; }
    billingHost = strHost;

    pBillingDB->Attribute("Port", &nValue);
    billingDbPort = nValue;

    szTemp = pBillingDB->Attribute("User");
    if ( !szTemp )
    { return false; }
    billingUID = szTemp;

    szTemp = pBillingDB->Attribute("Password");
    if ( !szTemp )
    { return false; }
    billingPwd = szTemp;

    szTemp = pBillingDB->Attribute("Name");
    if ( !szTemp )
    { return false; }
    billingDbName = szTemp;

	pBillingDB->Attribute("AccountBilling", &nValue );
	m_bAccountBilling = nValue;

	TiXmlElement* pBillingServer = pDatabase->FirstChildElement("BillingServer");
	if ( !pBillingServer )
	{ return false; }

	szTemp = pBillingServer->Attribute("Host");
	if ( !szTemp )
	{ return false; }

	strHost = szTemp;
	if ( strHost.empty())
	{ return false; }
	strBillingServerIp = strHost;

	pBillingServer->Attribute("Port", &nValue);
	ustBillingServerPort = nValue;

	pBillingServer->Attribute("BindPort", &nValue);
	nBindBillingServerPort = nValue;
	if (nBindBillingServerPort < 0)
	{
		nBindBillingServerPort = 0;
	}

	pBillingServer->Attribute("service", &nValue);
	bOpenBillingService = nValue;

	szTemp = pBillingServer->Attribute("Key");
	if ( !szTemp )
	{ return false; }
	strKey = szTemp;

	//积分
	TiXmlElement* pBillingScore = pDatabase->FirstChildElement("BillingScore");
	if ( !pBillingScore )
	{ return false; }

	szTemp = pBillingScore->Attribute("Host");
	if ( !szTemp )
	{ return false; }

	strHost = szTemp;
	if ( strHost.empty())
	{ return false; }
	strBillingScoreServerIp = strHost;

	pBillingScore->Attribute("Port", &nValue);
	ustBillingScoreServerPort = nValue;

	pBillingScore->Attribute("BindPort", &nValue);
	nBindBillingScoreServerPort = nValue;
	if (nBindBillingScoreServerPort < 0)
	{
		nBindBillingScoreServerPort = 0;
	}

	pBillingScore->Attribute("service", &nValue);
	bOpenBillingScoreService = nValue;

	szTemp = pBillingScore->Attribute("Key");
	if ( !szTemp )
	{ return false; }
	strKeyScore = szTemp;

    return true;
}

void DatabaseServerApp::CheckForServerExit()
{
    if ( theDbRunStatus.GetStatus() != DbRunStatus::RunStatus_PrepareStop && revShutdownCommandTime != 0/* && GetNodeSize() <= 1*/)
    { // 所有的连接都断了。开始关服。 服务器本身也是一个Node所以没连接的时候至少是1
        theDbRunStatus.SetStatus( DbRunStatus::RunStatus_PrepareStop );
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"关服指令 所以服务器已经关闭 开始准备关闭DatabaseServer");
        revShutdownCommandTime = 0;
    }
}

void DatabaseServerApp::SendMsgToAllClient(Msg* pMsg)
{
	if (!pMsg)
	{
		return;
	}
	int iLoopUsed =0,iLoopSize = 0;
	DatabaseClient **ppDC=NULL,*pDC = NULL;
	int iUsed = _DatabaseClient.GetUsed();
	int iSize = _DatabaseClient.GetSize();
	for (iLoopUsed = 0,iLoopSize = 0;iLoopUsed < iUsed&&iLoopSize < iSize;iLoopSize++)
	{
		ppDC = _DatabaseClient[iLoopSize];
		if (!ppDC||!*ppDC)
		{
			continue;
		}
		pDC = *ppDC;
		iLoopUsed++;
		if (!pDC->GetConnector()||pDC->GetConnector()->IsClose())
		{
			continue;
		}
		pDC->SendToClient(pMsg);
	}
}
