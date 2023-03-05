#include "AccountServer.h"
#include "Config.h"
#include "helper.h"
#include "ClientSession.h"
#include "LoginServer.h"
#include "LogMessage.h"
#include "GLSService.h"
#include "Timestamp/Timestamp.h"

CAccountServer::CAccountServer(void)
{
	m_socketer = NULL;
	connect_state = ecs_tryconnect;

	ping_time = 0;
	check_ping_time = 0;
	_service = false;
	connect_time = 0;
}

CAccountServer::~CAccountServer(void)
{
	if (m_socketer)
	{
		Socketer_release(m_socketer);
		m_socketer = NULL;
	}
}

void CAccountServer::Run()
{
	if (TryConnectAccountServer() != ecs_connected)
	{
		return;
	}
	ReciveAccountMsg();
	ProcessAccountServerMsg();
	SendAccountMsg();
}
void CAccountServer::ProcessAccountServerMsg()
{
	if (!m_socketer)
	{
		return;
	}
#define MAX_MSG 30 //每帧最多处理30个account server过来的消息
	Msg* pMsg = NULL;
	int i = 0;
	while (pMsg = m_socketer->GetMsg())
	{
		++i;
		//if (_service)
		{
			switch(pMsg->GetType())
			{
			case eAccountMsg_CheckSucc:
				OnMsgCheckSucc(pMsg);
				break;
			case eAccountMsg_CheckFail:
				OnMsgCheckFail(pMsg);
				break;
			case eAccountMsg_ReqConnect:
				OnMsgReqAuth(pMsg);
				break;
			case eAccountMsg_BlockAccount:
				OnMsgBlockAccount(pMsg);
				break;
			case eAccountMsg_PwdCardReq:
				OnMsgPwdCardReq(pMsg);
				break;
			default:
				break;
			}
		}
		if (MAX_MSG <= i)
			break;
	}
}

char CAccountServer::TryConnectAccountServer()
{
	switch(connect_state)
	{
	case ecs_tryconnect:
		{
			//if (IsNeedReConnect())
			{
				_service = false;
				if (!m_socketer)
				{
					m_socketer = Socketer_create();
					if (!m_socketer)
					{
						break;
					}
				}

				unsigned long curr_time = HQ_TimeGetTime();
				if(m_socketer->Connect(theConfig.strAccountServerIp.c_str(),theConfig.ustAccountServerPort,theConfig.nBindAccountPort))
				{
					connect_state = ecs_connected;
					check_ping_time = curr_time;
					ping_time = check_ping_time;

					MsgAuthConnect msg;
					memcpy(msg.content.chKey,theConfig.strKey.c_str(),16);

					//strncpy_s( msg.content.chKey,sizeof(msg.content.chKey),theConfig.strKey.c_str(),sizeof(msg.content.chKey)-1);
					strncpy_s( msg.sign,sizeof(msg.sign),
						GetMsgMd5Sign((void*)&(msg.content),sizeof(MsgAuthConnect::SContent),(void*)theConfig.strKey.c_str(),16).c_str(),
						sizeof(msg.sign)-1);
					if (SendMsgToAccountServer(&msg))
					{
						printf("connect account server succ!\n");
					}
					else
						printf("connect account server false!\n");					
				}
				connect_time = curr_time;
			}
		}
		break;
	default:
		break;
	}
	return connect_state;
}

void CAccountServer::ReciveAccountMsg()
{
	if (!m_socketer||m_socketer->IsClose())
	{
		connect_state = ecs_tryconnect;
		_service = false;

		if (m_socketer)
		{
			Socketer_release(m_socketer);
			m_socketer = NULL;
		}
		return;
	}

	if (connect_state == ecs_connected)
	{
		m_socketer->CheckRecv();
	}
}
void CAccountServer::SendAccountMsg()
{
	if (!m_socketer||m_socketer->IsClose())
	{
		connect_state = ecs_tryconnect;
		_service = false;

		if (m_socketer)
		{
			Socketer_release(m_socketer);
			m_socketer = NULL;
		}
		return;
	}

	if (connect_state == ecs_connected)
	{
		m_socketer->CheckSend();
	}
}

bool CAccountServer::SendMsgToAccountServer(Msg* pMsg)
{
	if (connect_state != ecs_connected||pMsg == NULL||!m_socketer||m_socketer->IsClose())
	{
		return false;
	}
	return m_socketer->SendMsg(pMsg);
}

string CAccountServer::GetMsgMd5Sign(void* _input0,int _length0,void* _input1,int _length1)
{
	char content_buff[1024];
	memset(content_buff,0,1024);
	memcpy(content_buff,_input0,_length0);
	memcpy(content_buff+_length0,_input1,_length1);
	MD5 xMD5( content_buff ,_length1+_length0);
	std::string strConent = xMD5.toString();
	return strConent;
}

void CAccountServer::OnMsgCheckSucc(Msg* pMsg)
{
	MsgCheckAccountSucc* pSucc = (MsgCheckAccountSucc*)pMsg;
	if (!pSucc)
	{
		return;
	}
	CClientSession* pClient = theCenterLoginServer.GetClientById(pSucc->header.stID);
	if (!pClient)
	{
		return;
	}
	static char account_name[17];
	memset(account_name,0,17);
	strncpy_s( account_name,sizeof(account_name),pSucc->content.account_name,sizeof(pSucc->content.account_name)-1);
	//LogMessage::LogSystemError("account[%s] malloc[%d] Succ[%s]", pClient->GetAccount(),pSucc->header.stID,pSucc->content.account_name);
	if (!theCenterLoginServer.CheckAccountResult(pClient,account_name))
	{
		LogMessage::LogSystemError("check error!account[%s] Malloc[%d] Name[%s]", pClient->GetAccount(),pSucc->header.stID,account_name);
		return;
	}
	if (!theCenterLoginServer.AddClientByAccountID(pSucc->content.account_id,pClient))
	{
		return;
	}
	//todo:发送成功协议给CENTER SERVER,返回了以后再给client发送
	pClient->SetSessionKey(HelperFunc::CreateID());
	MsgLoginInfo msg;
	msg.nAccountID = pClient->GetAccountId();
	strncpy_s( msg.szIP,       sizeof(msg.szIP ),    pClient->GetIP(),        sizeof(msg.szIP)-1)       ;
	strncpy_s( msg.szMac,       sizeof(msg.szMac ),    pClient->GetMacAdress(),        sizeof(msg.szMac)-1)       ;
	strncpy_s( msg.szAccount,       sizeof(msg.szAccount ),    pClient->GetAccount(),        sizeof(msg.szAccount)-1)       ;
	msg.isWallow = pSucc->content.is_wallow;
	msg.SessionKey = pClient->GetSessionKey();
	theCenterLoginServer.SendMsgToAllServer(&msg);
	//LogMessage::LogSystemError("account[%s] id[%u]", pClient->GetAccount(),pSucc->content.account_id);
	//printf("1,keylogin:send login info to center server:%d\n",HQ_TimeGetTime());
}

void CAccountServer::OnMsgCheckFail(Msg* pMsg)
{
	MsgCheckFail* pFail = (MsgCheckFail*)pMsg;
	if (!pFail)
	{
		return;
	}
	CClientSession* pClient = theCenterLoginServer.GetClientById(pFail->header.stID);
	if (!pClient)
	{
		return;
	}
	MsgAckLogin msg;
	msg.stErrorCode = MsgAckLogin::error_invaliduserorpass;

	switch(pFail->content.result)
	{
	case eFail_NoAccount:
		{
			msg.stErrorCode = MsgAckLogin::ret_invalidusername;
		}
		break;
	case eFail_PWDSError:
		{
			msg.stErrorCode = MsgAckLogin::ret_invalidpassword;
		}
		break;
	case eFail_NoActive:
		{
			msg.stErrorCode = MsgAckLogin::ret_noactive;
		}
		break;
	case eFail_SecondPwdsError:
		{
			msg.stErrorCode = MsgAckLogin::ret_secondpwderror;
		}
		break;
	case eFail_PwdCardChect:
		{
			msg.stErrorCode = MsgAckLogin::ret_PwdCardError;
		}
		break;
	case eFail_NoServer:
	case eFail_UnKown:
	default:
		break;
	}
	pClient->SendMsg(&msg);
}

void CAccountServer::OnMsgReqAuth(Msg* pMsg)
{
	MsgReqConnect* pReq = (MsgReqConnect*)pMsg;
	if (!pReq)
	{
		return;
	}
	_service = atoi(&pReq->content.result);
	printf("auth result:%d\n",_service);
}
void CAccountServer::OnMsgPwdCardReq(Msg* pMsg)
{
	//接收到运营发送来玩家需要验证密保卡的数据
	MsgPwdCardReq* pReq = (MsgPwdCardReq*)pMsg;
	if(!pReq)
		return;
	CClientSession* pClient = theCenterLoginServer.GetClientById(pReq->header.stID);
	if (!pClient)
		return;
	// 记录一把
	pClient->SetPwdCardData(pReq->PwdCardSerialNumber,pReq->A,pReq->B,pReq->C);

	MsgPassWordCardReq msg;
	strcpy_s(msg.PwdCardSerialNumber,PwdCardSerialLength,pReq->PwdCardSerialNumber);
	strcpy_s(msg.A,PwdCardLength,pReq->A);
	strcpy_s(msg.B,PwdCardLength,pReq->B);
	strcpy_s(msg.C,PwdCardLength,pReq->C);
	pClient->SendMsg(&msg);
}
void CAccountServer::OnMsgBlockAccount(Msg* pMsg)
{
	MsgBlockAccount* pBlock = (MsgBlockAccount*)pMsg;
	if (!pBlock)
	{
		return;
	}
	GLSService::SBlockInfo* pBlockInfo = new GLSService::SBlockInfo;
	pBlockInfo->begintime = theTimestamp.GetTimestamp();
	pBlockInfo->blocktime = pBlock->content.blocktime;
	pBlockInfo->guid = pBlock->content.account_id;
	strncpy_s( pBlockInfo->name, sizeof( pBlockInfo->name ), pBlock->content.account_name, sizeof(pBlockInfo->name) - 1 );
	theGLSService.AddNewBlockInfoPublic(pBlockInfo);
}

bool CAccountServer::IsNeedReConnect()
{
	if (connect_state != ecs_connected)
	{
		if (HQ_TimeGetTime() - connect_time >= 3000)
		{
			return true;
		}
		else
			return false;
	}
	return false;
}