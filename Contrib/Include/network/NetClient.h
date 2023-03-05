#ifndef __NETMIDDLE_NETCLIENT_H__
#define __NETMIDDLE_NETCLIENT_H__

#pragma once

#pragma warning ( push, 0 )

//#include "../../network.h"
#include "network.h"
#include "Memory_Pool.h"

#pragma warning ( pop )

using namespace network;

class NetClient
{
public:
	virtual void Release();

	NetClient();
	virtual ~NetClient();

	/*IMeConnector*/Socketer* GetSocket() { return _pConnector;}  
	void          SetConnector( /*IMeConnector*/Socketer* pConnector );
	//IMeSocket*    GetSocket();
	//void          SetExtendData( const char* szExtData, char nSize );
	//std::string   GetExtendData(){return _szExtendData;};
	void          SetExtendData( long nExtendData ) { _nExtendData = nExtendData; }
	long          GetExtendIntData() const { return _nExtendData; }
	void          Close();
	virtual bool Send( Msg* pMessage ,void *adddata = 0, size_t addsize = 0);
	bool          IsClose();
	Msg *		  GetMsg (char *buf = 0, size_t bufsize = 0);	

protected:
	enum EConstDefine
	{
		CD_EXTENDDATA_SIZE = 64,
	};
	/*IMeConnector*/Socketer* _pConnector;

	union
	{
		char _szExtendData[CD_EXTENDDATA_SIZE];
		long _nExtendData;
	};
	//char _szExtendDataSize;
};

inline void NetClient::SetConnector( Socketer* pConnector)
{ 
	if ( !pConnector)
	{ return; }

	_pConnector = pConnector;
}


class NetClientEx : public NetClient, INHERIT_POOL( NetClientEx )
{
public:
	static NetClient* CreateInstance();
	virtual void Release();
};

#endif // __NETMIDDLE_NETCLIENT_H__