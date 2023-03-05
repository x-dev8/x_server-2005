#include "TcpClient.h"
#include "ErrorCode.h"

TcpClient::TcpClient( INetEvent& netevent/*, INetwork& network = NetApi::NetworkIntance() */):_netEvent(netevent)
{
	_bReceive = false;            // 是否要收包
	memset(_ip,0,20);              // 连接的Ip
	_uPort = 0;               // 连接的端口
	_nConnectState = CS_TryConnect;       // 连接状态
}
TcpClient::~TcpClient()
{
	Reset();
}
std::string TcpClient::GetClientIp()
{
	char clientip[20];
	_pConnector->GetIP(clientip, sizeof(clientip));
	return clientip;
}

long TcpClient::Init( const char* ip, unsigned short port,unsigned short bindprot)
{
	if (!ip||port == 65535||port == 0)
	{
		return ER_InitFail;
	}
	memcpy(_ip,ip,strlen(ip));
	_uPort = port;
	_uBindPort = bindprot;

	_pConnector = network::Socketer_create();
	if (!_pConnector)
	{
		return ER_InitFail;
	}
	return ER_Success;
}

void TcpClient::Reset()
{
	if (_pConnector)
	{
		_pConnector->Close();
		_nConnectState = CS_TryConnect;
		_bReceive = false;
		network::Socketer_release(_pConnector);
		_pConnector = NULL;
	}
}

void TcpClient::TryConnect()
{
	if (!_pConnector)
	{
		_pConnector = network::Socketer_create();
	}

	if (_pConnector&&_pConnector->Connect(_ip,_uPort,_uBindPort))
	{
		_nConnectState = CS_Connected;
		_bReceive = true;
	}
}

long TcpClient::Send( Msg* pMessage, char* szAdditionData, int iAdditionDataSize)
{
	if (!pMessage)
	{
		return ER_Failed;
	}
	if (!_pConnector||_pConnector->IsClose())
	{
		_nConnectState = CS_TryConnect;
		_bReceive = true;
		Reset();
		return ER_Failed;
	}
	if (_pConnector->SendMsg(pMessage,szAdditionData,iAdditionDataSize))
	{
		return ER_Success;
	}
	return ER_Failed;
}

long TcpClient::Update()
{
	if (!_bReceive)
	{
		return ER_Success;
	}

	if (!_pConnector||_pConnector->IsClose())
	{
		_nConnectState = CS_TryConnect;
		_bReceive = true;
		Reset();
		return ER_Failed;
	}

	Msg* pMsg = NULL;
	while(pMsg = _pConnector->GetMsg())
	{
		_netEvent.OnMessageIncoming(NULL,this,pMsg->GetType(),pMsg);
	}
	return ER_Success;
}

bool TcpClient::_CreateSocket()
{
	_pConnector = network::Socketer_create();
	if (!_pConnector)
	{
		return false;
	}
	return true;
}

void  TcpClient::_Receive( /*char* szBuffer, unsigned long nBufferCount*/)
{
	if (!_pConnector||_pConnector->IsClose())
	{
		_nConnectState = CS_TryConnect;
		_bReceive = true;
		Reset();
		return;
	}

	if (_nConnectState == CS_Connected&&_bReceive)
	{
		_pConnector->CheckRecv();
	}
	/*return 0;*/
}

void TcpClient::_Send()
{
	if (!_pConnector||_pConnector->IsClose())
	{
		_nConnectState = CS_TryConnect;
		_bReceive = true;
		Reset();
		return;
	}

	if (_nConnectState == CS_Connected&&_bReceive)
	{
		_pConnector->CheckSend();
	}
}