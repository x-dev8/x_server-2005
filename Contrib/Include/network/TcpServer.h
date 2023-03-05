#ifndef __NETMIDDLE_TCPSERVER_H__
#define __NETMIDDLE_TCPSERVER_H__

#pragma once

#pragma warning ( push, 0 )

//#include "../../network.h"
#include "network.h"
#include <set>
#include "msgbase.h"
#include "NetEventInterface.h"

#pragma warning ( pop )

using namespace network;

class NetClient;
class INetEvent;

const int nPerMaxAcceptCount           = 10;     // ÿ��Update����Accept����
const int nPerNetClientMaxMessageCount = 10000;  // ÿ�����������Խ�����Ϣ����
const int nPerNetClientReceiveRate     = 3000;   // ÿ�����ӵķ�������
/*
* ע�� ���յ���NetClient�ϲ㲻������� _pNetClient->Close() �� delete _pNetClient
 **/
class TcpServer
{
public:
    TcpServer( INetEvent& netevent/*, INetwork& network = NetApi::NetworkIntance() */);

    virtual ~TcpServer();

    virtual long Init( unsigned short port,int recv_size,int send_size,
                       bool  UseCompress = false
                       /*, bool  bSelfControlNetwork = false,
                       unsigned char sendMessageEncryptMode = msgflag_normal,
                       char  sendCheckThreadNum=-1, char ioThreadNum=-1*/);

    virtual void UnInit();
    
    virtual long RunLoop( unsigned long dwMilliseconds = 10 );
    virtual long RunOnce( unsigned long dwMilliseconds = 0);

    bool IsService() { return _bService; }

    void CloseConnection( NetClient* pNetClient );

    unsigned long GetConnectionCount(); 

protected:
    long _BindPort( unsigned short port );

    long _Accept();
    void _Receive();
    void _Send();

    virtual long _Update();

private:
    typedef std::set<NetClient*> NetClientContainer;
    typedef NetClientContainer::iterator   ItrNetClientContainer;
    NetClientContainer _acceptNetClients;

    /*INetwork& _network;*/

    /*IMeSocket*/Listener* _pListenSocket;

    INetEvent& _netEvent;

   // bool  _bUseIocp;
   // bool  _bSelfControlNetwork;
   // uint8 _sendMessageEncryptMode; // ������Ϣ�ļ��ܷ�ʽ

    unsigned long _nErrorMessage;

    bool _bService;
	//unsigned short port_;
	int RecvCritical;
	int SendCritical;
	bool _UseCompress;

#ifdef _USE_MULTI_THREAD_SERVER
    CSemiAutoIntLock acceptLock_;
#endif
};

#ifdef _USE_MULTI_THREAD_SERVER
#define AUTOLOCK( object ) CSALocker locker(object)
#else
#define AUTOLOCK( object ) 
#endif

#endif // __NETMIDDLE_TCPSERVER_H__
