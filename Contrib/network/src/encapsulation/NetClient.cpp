#include "NetClient.h"

NetClient::NetClient(void)
{
	_pConnector = NULL;
}

NetClient::~NetClient(void)
{
	Release();
}

void NetClient::Release()
{
	if (_pConnector)
	{
		network::Socketer_release(_pConnector);
		_pConnector = NULL;
	}
}

void NetClient::Close()
{
	Release();
}

bool NetClient::IsClose()
{
	if (_pConnector)
		return _pConnector->IsClose();

	return true;
}

bool NetClient::Send( Msg* pMessage,void *adddata , size_t addsize )
{
	if (!pMessage||!_pConnector)
	{
		return false;
	}
	return _pConnector->SendMsg(pMessage,adddata,addsize);
}

Msg *NetClient::GetMsg (char *buf, size_t bufsize)
{
	if (_pConnector)
	{
		return _pConnector->GetMsg(buf,bufsize);
	}
	return NULL;
}