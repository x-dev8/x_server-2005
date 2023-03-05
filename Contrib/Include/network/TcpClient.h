#ifndef __NETMIDDLE_TCPCLIENT_H__
#define __NETMIDDLE_TCPCLIENT_H__

#pragma once

#pragma warning ( push, 0 )
#include "MeRTLibsServer.h"
#include "FuncPerformanceLog.h"
#include "Helper.h"
#include "Mutex.h"
//#include "MeNetwork.h"
#include "NetEventInterface.h"
#include "MsgBase.h"
//#include "NetApi.h"
#pragma warning ( pop )

const unsigned int TCPCLIENT_LOWLEVELCAST         = 10000;
const unsigned int TCPCLIENT_NORMALLEVELCAST      = 20000;
const int          TCPCLIENT_MAXQUEUEMESSAGECOUNT = -1;

const unsigned long MAX_RECEIVEBUFFER_CACHE = 1024 * 100;

class TcpClient : public NetClient
{
public:
    enum EConnectState
    {
        CS_TryConnect,
        CS_ReConnect,
        CS_Connected,
    };

    enum EConstDefine
    {
        ECD_ReconnectPlatformTimeInterval = 1000, // 1 ��
    };

    TcpClient( INetEvent& netevent/*, INetwork& network = NetApi::NetworkIntance() */);
    virtual ~TcpClient();

    std::string    GetClientIp();
   /* int            GetInQueueSize();    
    int            GetOutQueueSize();*/
    char           GetConnectState()                     { return _nConnectState; }
    void           SetConnectState( char cConnectState ) { _nConnectState = cConnectState;}
    std::string    GetIP()                               { return _ip; }
    unsigned short GetPort()                             { return _uPort; }
	unsigned short GetBindPort()                         { return _uBindPort;}

    // GameMessage Client
    long       Init( const char* ip, unsigned short port,unsigned short bindprot = 0/*, bool bSelfControlNetwork = false, uint8 sendMessageEncryptMode = msgflag_normal */);
    void       Reset();
    /*IMeSocket*/Socketer* GetSocket();
    void       TryConnect();
    long       Send( Msg* pMessage, char* szAdditionData = NULL, int iAdditionDataSize = 0);
    long       Update();
    void       StopReceive() { _bReceive = false; }
	void  _Receive( /*char* szBuffer, unsigned long nBufferCount = MAX_RECEIVEBUFFER_CACHE*/);
	void  _Send();

protected:
    bool _CreateSocket();    

private:
    //INetwork&  _network;             // network
    INetEvent& _netEvent;            // �����¼�
    bool       _bReceive;            // �Ƿ�Ҫ�հ�
   // bool       _bSelfControlNetwork; // �Ƿ����������ʼ��ȫ�� INetwork �ĳ�ʼ��������
    char       _ip[20];              // ���ӵ�Ip
    uint16     _uPort;               // ���ӵĶ˿�
    char       _nConnectState;       // ����״̬
	uint16     _uBindPort;           // �󶨱��صĶ˿�
    //uint32     _lastReconnectTime;   // ����ʱ��
    //uint8      _sendMessageEncryptMode; // ������Ϣ�ļ��ܷ�ʽ
};

inline /*IMeSocket*/Socketer* TcpClient::GetSocket()
{
    if ( _pConnector==NULL )
        return NULL;

    return _pConnector/*->GetSocket()*/;
}

//inline int TcpClient::GetInQueueSize()
//{
//    if ( _pConnector==NULL )
//        return NULL;
//
//    return _pConnector->GetInQueueSize();
//}
//
//inline int TcpClient::GetOutQueueSize()
//{
//    if ( _pConnector==NULL )
//        return NULL;
//
//    return _pConnector->GetOutQueueSize();
//}

#endif // __NETMIDDLE_TCPCLIENT_H__
