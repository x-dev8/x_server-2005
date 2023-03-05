#include "DatabaseClient.h"
#include "DatabaseServerApp.h"
#include "helper.h"
#include "DatabaseInterface.h"
#include "MySqlCommunication.h"
#include "DBMessageDefine.h"
#include "CenterDataBaseMessage.h"
#include "application_config.h"
#include "CenterGameMessage.h"
#include "RunStatus.h"
#include "GameTimer.h"

DatabaseClient::DatabaseClient()
{
	m_pConnector = NULL;
	client_id = -1;
}

DatabaseClient::~DatabaseClient()
{
}

void DatabaseClient::SetConnector(Socketer* ps,bool breleaseold)
{
	if (breleaseold)
	{
		ReleaseConnector();
	}
	m_pConnector = ps;
}

void DatabaseClient::SendToClient(Msg* pMsg)
{
	if (!m_pConnector||!pMsg||m_pConnector->IsClose())
	{
		return;
	}
	m_pConnector->SendMsg(pMsg);
}

void DatabaseClient::ProcessMsgs()
{

    GameTimerEx processGameMessageTime;
    processGameMessageTime.StartTimer( HQ_TimeGetTime(), 50 );
    Msg* pMsg = NULL;
    while( !processGameMessageTime.DoneTimer( HQ_TimeGetTime() ) )
    {
        pMsg = GetConnector()->GetMsg();
        if ( pMsg == NULL )
        { break; }

        switch( pMsg->GetType() )
        {
		case MSG_PING:
			{ // Ping消息直接回
				MsgPingMsg msgPing;
				theMysqlCommunication.PushAckMessage( &msgPing, GetId() );
			}
			break;
		case S2S_SHUTDOWNSERVER:	// 收到center的关服命令
            {
                S2SShutdownServer* pMessage = (S2SShutdownServer*)pMsg;
                GetDatabaseServerApp()->revShutdownCommandTime = HQ_TimeGetTime();
                GetDatabaseServerApp()->revShutdownDelayTime   = pMessage->delayTime;

                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"收到关服指令 等待连接它的所有关闭");
            }
            break;
        case MSG_REGISTERSERVERREQ: // center 让我注册服务器
            {
                MsgRegisterServerAck xAck;
                
                xAck.uchParentType = ServerDataDefine::Node_Center;
                xAck.nParentID     = 0;
                xAck.uchType       = ServerDataDefine::Node_Database;
                xAck.nID           = 0;
                xAck.ustVersion    = static_cast< uint16 >( theApplicationConfig.GetBuildVersion() );
                strncpy_s( xAck.szName, sizeof( xAck.szName ), "DataBase-MySql", sizeof( xAck.szName ) - 1 );
                theMysqlCommunication.PushAckMessage( &xAck, GetId() );
            }
            break;
        case MSG_SERVERSTATUSREQ:	// center 让我发送状态结构
            {
                MsgServerStatusAck xAck;
                xAck.uchParentType = ServerDataDefine::Node_Center;
                xAck.nParentID     = 0;
                xAck.uchType       = ServerDataDefine::Node_Database;
                xAck.nID           = 0;
                theMysqlCommunication.PushAckMessage( &xAck, GetId() );
            }
            break;
        case MSG_PARTITIONLOGFILE:	// 应该是要切换日志文件的
            {
                PartitionLogFile();
            }
            break;
        case  GS2DB_REQ_INIT_DATA:
            {}
            break;

        default:
            {	// only use mysql 1
                bool bUseMysql = true;
                if ( GetDatabaseServerApp()->useSqlType == DatabaseServerApp::ST_MSSql )
                {
                    BOOL bResult = GetDatabaseInterface()->PushMessage( pMsg, GetId());
                    if ( !bResult )
                    { LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "PushMessage Fail MessageId[%d] Size[%d]", pMsg->GetType(), pMsg->GetLength());}
                }
				// only use mysql 0
                else
                {
                    uint32 result = theMysqlCommunication.PushReqMessage( pMsg, GetId() );
                    if ( RESULT_FAILED(result) )
                    { LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "PushReqMessage Fail MessageId[%d] Size[%d]", pMsg->GetType(), pMsg->GetLength());}
                }
            }
            break;
        }
    }
}

void DatabaseClient::OnRegister()
{
}

void DatabaseClient::OnUnRegister()
{
}

void DatabaseClient::PartitionLogFile()
{
    SYSTEMTIME xSystem;
    ::GetLocalTime( &xSystem );

    //LOG_MESSAGE( SYSTEMOBJECT,      LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LOG_MESSAGE( BILLINGOBJECT,     LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LOG_MESSAGE( SQLOBJECT,         LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
}

void DatabaseClient::ReleaseConnector()
{
	if (m_pConnector)
	{
		m_pConnector->Close();
		Socketer_release(m_pConnector);
		m_pConnector = NULL;
	}
}