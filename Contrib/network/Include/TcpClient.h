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
        ECD_ReconnectPlatformTimeInterval = 1000, // 1 秒
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
    INetEvent& _netEvent;            // 网络事件
    bool       _bReceive;            // 是否要收包
   // bool       _bSelfControlNetwork; // 是否类自身负责初始话全局 INetwork 的初始化和析构
    char       _ip[20];              // 连接的Ip
    uint16     _uPort;               // 连接的端口
    char       _nConnectState;       // 连接状态
	uint16     _uBindPort;           // 绑定本地的端口
    //uint32     _lastReconnectTime;   // 重连时间
    //uint8      _sendMessageEncryptMode; // 发出消息的加密方式
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
