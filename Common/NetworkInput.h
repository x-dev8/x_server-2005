///********************************************************************
//    Filename:     NetworkInput.h
//    MaintenanceMan Mail: Luo_157@hotmail.com
//*********************************************************************/
//
//#pragma once
//
//#include "MeSocket.h"
//#include "MessageDefine.h"
//#include "MsgFromBuf.h"
//#include "ClientMsgQueue.h"
//#include "MeNetwork.h"
//
//class CNetworkInput
//{ // 网络处理模块
//public:
//    enum EConstDefine
//    {
//        EConstDefin_HostNameMaxSize = 200,
//    };
//
//public:
//	CNetworkInput();
//	~CNetworkInput();
//
//	void       ResetConnectted(){ m_bConnectted = false; }
//	bool       IsConnectted()   { return m_bConnectted;  }
//	bool       InitConnect( const char* szDstIP, unsigned short iPort = 20000 );	
//	bool       ConnectToServer( int iConnectTimeout = 16 ); // 16s
//    uint32     CreateToConnectGameServerSocket();
//	void       Close();
//    bool       IsClosed();
//    IMeSocket* GetSocketCtrl();
//    void       Reset();	
//    void       CheckSendReq();
//	bool       IsAllMsgSendOver();
//
//	int        RecvMsg( char* sBuf );
//	int        SendMsg( char* sBuf, short stSize );
//	int        SendMsg( Msg* pMsg );
//    int        GetCriticalError();
//
//private:
//	char		   m_szDst[ EConstDefin_HostNameMaxSize ];
//	unsigned short m_iPort;
//	bool		   m_bConnectted;
//	IMeConnector*  m_pConnector;		
//    uint32         _dwThreadId;
//};
//
//extern CNetworkInput& GettheNetworkInput();
//
////////////////////////////////////////////////////////////////////////////
//// inline
//inline int CNetworkInput::GetCriticalError()
//{ 
//    if( m_pConnector ) 
//    { return m_pConnector->GetCriticalError(); }
//    return -2;
//}
//
//inline IMeSocket* CNetworkInput::GetSocketCtrl()
//{
//    return m_pConnector->GetSocket();
//}
#pragma once
#include "network.h"
struct Msg;

using namespace network;
//class Socketer;
//网络处理模块
class CNetworkInput
{
	char m_szDst[ 200 ];
	int m_iPort;
	bool m_bConnectted;
	Socketer* m_pConnector;
public:
	CNetworkInput();
	~CNetworkInput(void);

	void Destroy ();

	//获取ip
	const char *GetIP(){ return m_szDst; }

	//获取端口
	int GetPort(){ return m_iPort; }

	void ResetConnectted(void){ m_bConnectted = false; }
	bool IsConnectted(void){ return m_bConnectted; }
	bool InitConnect( const char *szDstIP,int iPort = 20000 );

	bool ConnectToServer(bool islogin = true);
	void Close();
	int SendMsg( Msg*pMsg ,long msg_length = -1 /*bNoTimeSend = false*/);	
	Msg *GetMsg ();

	bool IsClosed(void);

	void CheckSendReq();
	void CheckRevReq();
};

extern CNetworkInput& GettheNetworkInput();