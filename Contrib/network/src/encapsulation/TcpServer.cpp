#include "TcpServer.h"
#include "ErrorCode.h"

TcpServer::TcpServer( INetEvent& netevent):_netEvent(netevent)
{
	/*_netEvent = netevent;*/
	//memcpy(&_netEvent,&netevent,sizeof(INetEvent));

	_pListenSocket = network::Listener_create();
	
	_acceptNetClients.clear();
	RecvCritical = -1;
	SendCritical = -1;
	_UseCompress = false;
	_bService  = true;
}

TcpServer:: ~TcpServer()
{
	UnInit();
}

long TcpServer::Init( unsigned short port,int recv_size,int send_size, 
		  bool  UseCompress )/*= false,*/ 
		  //bool  bSelfControlNetwork /*= false*/,
		  //uint8 sendMessageEncryptMode /*= msgflag_normal*/,
		  //int8  sendCheckThreadNum/*=-1*/, int8 ioThreadNum/*=-1*/ )
{
	if (port == 65535)
	{
		return ER_InitFail;
	}

	if(!_pListenSocket||!_pListenSocket->Listen( port, 5 ) )
	{
		printf("Listen error!\n");
		return ER_InitFail;
	}
	if (recv_size <= 0 || send_size <= 0)
	{
		return ER_InitFail;
	}

	RecvCritical = recv_size;
	SendCritical = send_size;

	_UseCompress = UseCompress;

	return ER_Success;
}

void TcpServer::UnInit()
{
	if (_pListenSocket)
	{
		network::Listener_release(_pListenSocket);
		_pListenSocket =NULL;
	}

	if (!_acceptNetClients.empty())
	{
		NetClient* pNC = NULL;
		ItrNetClientContainer itr = _acceptNetClients.begin();
		while(itr != _acceptNetClients.end())
		{
			pNC = *itr;
			if (pNC)
			{	
				pNC->Close();
				delete pNC;
				pNC = NULL;
				itr = _acceptNetClients.erase(itr);
				continue;
			}
			itr++;
		}

		_acceptNetClients.clear();
	}
}

long TcpServer::RunLoop( unsigned long dwMilliseconds)
{
	return ER_Success;
}

long TcpServer::RunOnce( unsigned long dwMilliseconds)
{
	int iAccept = 0;
	const int iAcceptMax = 10;
	//���ܿͻ��˵�����
	while( _pListenSocket->CanAccept() && iAccept < iAcceptMax )
	{
		_Accept();
		iAccept ++;
	}

	_Update();
	_Receive();
	_Send();

	return ER_Success;
}

void TcpServer::CloseConnection( NetClient* pNetClient )
{//�����������,����ϲ���ʹ�õ�����,һ��Ҫreturn��ѽ��,����ע��,���ľ�����...
	ItrNetClientContainer itr = _acceptNetClients.find(pNetClient);
	if (itr == _acceptNetClients.end())
	{
		return;
	}
	_acceptNetClients.erase(itr);

	_netEvent.OnDisconnect(this,pNetClient,NULL);
	pNetClient->Close();
	delete pNetClient;
}

unsigned long TcpServer::GetConnectionCount()
{
	return _acceptNetClients.size();
}

long TcpServer::_BindPort( unsigned short port )
{
	if (!_pListenSocket)
	{
		_pListenSocket = network::Listener_create();
	}

	if (!_pListenSocket||!_pListenSocket->Listen(port,5))
	{
		return ER_Failed;
	}
	return ER_Success;
}

long TcpServer::_Accept()
{
	if (!_pListenSocket)
	{
		return ER_Failed;
	}

	Socketer *pS = _pListenSocket->Accept();
	if (!pS)
	{
		return ER_Failed;
	}

	//pS->SetRecvCritical(RecvCritical);
	//pS->SetSendCritical(SendCritical);

	if (_UseCompress)
	{
		pS->UseCompress();
	}

	NetClient* pNC = new NetClient;
	pNC->SetConnector(pS);

	if (!_netEvent.OnAccept(this,pNC))
	{
		pNC->Close();
		delete pNC;
		return ER_Failed;
	}

	_acceptNetClients.insert(pNC);

	return ER_Success;
}

void TcpServer::_Receive()
{
	NetClient* pNC = NULL;
	ItrNetClientContainer itr = _acceptNetClients.begin();

	while(itr != _acceptNetClients.end())
	{
		pNC = *itr;
		if (pNC&&!pNC->IsClose())
		{
			pNC->GetSocket()->CheckRecv();
			itr ++;
		}
		else
		{
			//ɾ�����Ժ��б������ʧЧ��,һ��ҪRETURN��,�´�ѭ���һ������
			CloseConnection(pNC);
			return;
		}
	}
}

void TcpServer::_Send()
{
	NetClient* pNC = NULL;
	ItrNetClientContainer itr = _acceptNetClients.begin();

	while(itr != _acceptNetClients.end())
	{
		pNC = *itr;
		if (pNC&&!pNC->IsClose())
		{
			pNC->GetSocket()->CheckSend();
			itr ++;
		}
		else
		{
			//ɾ�����Ժ��б������ʧЧ��,һ��ҪRETURN��,�´�ѭ���һ������
			CloseConnection(pNC);
			return;
		}
	}
}

long TcpServer::_Update()
{
	Msg* pMsg = NULL;
	NetClient* pNc = NULL;
	ItrNetClientContainer itr = _acceptNetClients.begin();	
	while(itr != _acceptNetClients.end())
	{
		pNc = *itr;
		if (!pNc)
		{
			itr = _acceptNetClients.erase(itr);
			continue;
		}
		while(pMsg = pNc->GetMsg())
		{
			_netEvent.OnMessageIncoming(this,pNc,pMsg->GetType(),pMsg);
		}
		itr++;
	}
	return ER_Success;
}