////////////////////////////////////////////////////////////////////////////////
//	Copyright (C) 2000-2001 Softelf Inc. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
//
//	Author	: Telan 
//	Date	: 2000-10-04
//	Purpose	: Encapsulate winsock2 functions to make it more easily used 
//	History	: 
//		1.0	: 2000-03-10 - First Edition of this source code ( called:FE_SOCKET )
//		2.0	: 2000-06-25 - Second Edition ( name changed to TE_SOCKET )
//						 - Add Error Control
//		3.0	: 2000-09-21 - Third Edition ( name changed to TE_SOCKET )
//						 - Change the errors' process mechanism
//						 - Add BufSocket Model
//						 - Add TE_ConnectEx(...)
//						 - Add TE_BSocketGetData(...) for specail usage
//		3.1 : 2000-10-04 - Add TE_AcceptEx(...)
//						 - Add TE_GetIP(...) to fix NT DNS resolve cache problem
//						 - Modify TE_ConnectEx
//						 - Fix several bugs in NetEvent process
//
//	Mailto	: telan@263.net ( Bugs' Report or Comments )
//	Notes	: This source code may be used in any form in any way you desire. It is
//			  provided "as is" without express or implied warranty. Use it at your own
//			  risk! The author accepts no liability for any damage/loss of business 
//			  that this product may cause.
//
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "TE_Socket.h"

//��Ҫws2_32.lib��
#pragma comment(lib,"ws2_32.lib")

//�������
static __declspec(thread) int _iThreadedErrorNo = 0;

// ��������
//��ȡ���һ�β����Ĵ������
int TE_GetLastError()
{
	return (_iThreadedErrorNo);
}

//���ô������
void TE_SetLastError(int iErrorCode)
{
	_iThreadedErrorNo = iErrorCode;
}

/////////////////////////////////////////////////////////////////////////
//		Winsock2 ����
/////////////////////////////////////////////////////////////////////////
//��ʼ��Winsock2��̬���ӿ�
int TE_InitLibrary()
{
	WSADATA         WSD;
	WORD wVersionRequired = MAKEWORD( TE_SOCKET_MAJOR_VERSION,TE_SOCKET_MINOR_VERSION );
	
	ZeroMemory(&WSD,sizeof(WSADATA));

	int nErrorNo = WSAStartup(wVersionRequired, &WSD);

	if ( SOCKET_SUCCESS != nErrorNo )
	{
		TE_SetLastError( nErrorNo );
		return ( SOCKET_ERROR );
	}

	if ( LOBYTE( WSD.wVersion ) != TE_SOCKET_MINOR_VERSION ||
		 HIBYTE( WSD.wVersion ) != TE_SOCKET_MAJOR_VERSION ) 
	{
		WSACleanup( );
		TE_SetLastError( WSAVERNOTSUPPORTED );
		return (SOCKET_ERROR); 
	}
 
	//�ɹ���ʼ��
	return (SOCKET_SUCCESS);
}


//�ͷ�Winsock2��̬���ӿ�
void TE_CleanupLibrary(void)
{
    WSACleanup();
}


//�����׽�������
int TE_SetSocketOption(SOCKET hSocket)
{

    int             iActivate = 1;

	//�����ַ����
    if (setsockopt(hSocket, SOL_SOCKET, SO_REUSEADDR, (const char *) &iActivate,sizeof(iActivate)) == SOCKET_ERROR )
    {
        TE_SetLastError( WSAGetLastError() );
        return (SOCKET_ERROR);
    }

	//  ���֧�֣�����KEEPALIVE���� (����������������������)
	//setsockopt(hSocket, SOL_SOCKET, SO_KEEPALIVE, (const char *) &iActivate,sizeof(iActivate));

	return (SOCKET_SUCCESS);
}

//���������ص�IO�������׽���
SOCKET TE_CreateSocket(int iAddressFamily /*= AF_INET*/, int iType/*= SOCK_STREAM*/,int iProtocol/*= 0*/)
{
	SOCKET hSocket = WSASocket(iAddressFamily, iType, iProtocol, NULL,0,WSA_FLAG_OVERLAPPED);
	if ( hSocket == INVALID_SOCKET )
	{
		TE_SetLastError( WSAGetLastError() );
		return (INVALID_SOCKET);
	}

	//�����׽���ѡ��
	if ( SOCKET_ERROR == TE_SetSocketOption(hSocket) )	//��������ʧ��
	{
		TE_CloseSocket(hSocket, TRUE);
		return (INVALID_SOCKET);
	}
	return (hSocket);
}


//�ر��׽���
void TE_CloseSocket(SOCKET hSocket, BOOL bHardClose)
{
	// ����Ҫ�������
	if (!bHardClose) // ���Źر� Graceful close
	{
		// ���ٷ������ݣ�����TCP�׽��֣������е����ݶ��������֮��
		// ������һ�� FIN ��֪ͨ���շ����������Ѿ�������ϡ�
		shutdown(hSocket, SD_SEND);

		// ���ջ������п��ܻ���δ���յ����ݣ��ڹر��׽���֮ǰӦ����
		// ��ȡ���������ݡ�
		int		iRecvResult;
		HANDLE	hSocketEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		char	szBuffer[256];
		do
		{
			if (hSocketEvent != NULL)
			{
				//ע�������¼�
				WSAEventSelect(hSocket, (WSAEVENT) hSocketEvent, FD_READ | FD_CLOSE);
				WSAWaitForMultipleEvents(1, &hSocketEvent, TRUE,TE_SHUTDOWN_RECV_TIMEOUT, TRUE);
				//��������¼�
				WSAEventSelect(hSocket, (WSAEVENT) hSocketEvent, 0);
			}
			ZeroMemory(szBuffer,256);
			iRecvResult = TE_RecvLL(hSocket, szBuffer, sizeof(szBuffer));
		} while (iRecvResult > 0);

		if (hSocketEvent != NULL)
			CloseHandle(hSocketEvent);

		//����������պͷ���
		shutdown(hSocket, SD_BOTH);
	}
	
	// �ر��׽���
	closesocket(hSocket);
}


// һ���Խ�������(�ص�IO)
int TE_RecvLL(SOCKET hSocket, char *pszBuffer, int iBufferSize)
{
	DWORD		dwRtxBytes = 0,
				dwRtxFlags = 0;
	WSABUF		WSABuff;

	//��ջ���
	ZeroMemory(&WSABuff,sizeof(WSABUF));

	WSABuff.len = iBufferSize;
	WSABuff.buf = pszBuffer;

	return ((WSARecv(hSocket, &WSABuff, 1, &dwRtxBytes, &dwRtxFlags,NULL, NULL) == SOCKET_SUCCESS) ? (int) dwRtxBytes : -WSAGetLastError());
}

// ��������(����ֱ���յ�����Ϊֹ)
int TE_RecvData(SOCKET hSocket, char *pszBuffer, int iBufferSize, DWORD dwTimeout)
{
	HANDLE hReadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	if (hReadEvent == NULL)
	{
		TE_SetLastError( (int)GetLastError() );
		return ( SOCKET_ERROR );
	}

	int		iRecvBytes = 0;
	DWORD	dwWaitResult ;
	for (;;)
	{
		// ע��FD_READ | FD_CLOSE �¼� 
		// (��Ϊ�����ڵȴ�FD_READ�¼��У��Է��ر��׽��֣�����Ҫ��עFD_CLOSE)
		if( WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, FD_READ | FD_CLOSE) == SOCKET_ERROR)
		{
			CloseHandle(hReadEvent);
			TE_SetLastError( WSAGetLastError() );
			return (SOCKET_ERROR);
		}
	
		// �ȵ�FD_READ | FD_CLOSE�¼��ķ���
		dwWaitResult = WSAWaitForMultipleEvents(1, &hReadEvent, TRUE,dwTimeout, TRUE);

		if (dwWaitResult != WSA_WAIT_EVENT_0)
		{
			// ����¼�
			WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, 0);
			CloseHandle(hReadEvent);
			TE_SetLastError( WSAGetLastError() );
			return (SOCKET_ERROR);
		}
		
		////////////////////////////////////////////////////////////// 
		///	ע�⣺��ʹ dwWaitResult == WSA_WAIT_EVENT0 ��ҲӦ�� 
		///			��һ����������Ƿ�������
		///////////////////////////////////////////////////////////////
		WSANETWORKEVENTS NetEvent;
		if(WSAEnumNetworkEvents(hSocket,(WSAEVENT)hReadEvent,&NetEvent) == SOCKET_ERROR)
		{
			// ����¼�
			WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, 0);
			CloseHandle(hReadEvent);
			TE_SetLastError( WSAGetLastError() );
			return (SOCKET_ERROR);
		}
		//�жϷ�����ʲô�¼� FD_READ �� FD_CLOSE	
		if( ( NetEvent.lNetworkEvents == FD_CLOSE ) ||
			 ( NetEvent.lNetworkEvents	== FD_READ && 
			   NetEvent.iErrorCode[FD_READ_BIT] !=0 ) )	// ��������
		{
			// ����¼�
			WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, 0);
			CloseHandle(hReadEvent);
			TE_SetLastError(WSAGetLastError() );
			return (SOCKET_ERROR);
		}
		////////////////////////////////////////////////////////////////
		// ����¼�
		WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, 0);
	
		// ��������
		if ((iRecvBytes = TE_RecvLL(hSocket, pszBuffer, iBufferSize)) >= 0)
			break;	// ����ѭ��

		int iErrorCode = -iRecvBytes;

		if ( iErrorCode != WSAEWOULDBLOCK )	//̫���δ����ص�����
		{
			CloseHandle(hReadEvent);
			TE_SetLastError( iErrorCode );
			return (SOCKET_ERROR);
		}

		//����ס��
		////////////////////////////////////////////////////////////////////////
		//  �����������,�͵ȴ�һ��ʱ�������,����CPU��ѯ�˷�ʱ��
		////////////////////////////////////////////////////////////////////////
		Sleep(TE_BLOCKED_SNDRCV_SLEEP);
    }

    CloseHandle(hReadEvent);
    return (iRecvBytes);
}


// ��������ֱ���ﵽ�涨�ĳ���(��������)��ʱ��û�����ݿɶ�ȡʱ
int TE_Recv(SOCKET hSocket, char *pszBuffer, int iBufferSize, DWORD dwTimeout)
{
	int	iRtxBytes	= 0;
	int iRtxCurrent	= 0;

	while (iRtxBytes < iBufferSize)
	{
		iRtxCurrent = TE_RecvData(hSocket, (pszBuffer + iRtxBytes),(iBufferSize - iRtxBytes), dwTimeout);

		if (iRtxCurrent < 0)	//û�����ݿɶ�ȡ
			return (iRtxBytes);

		iRtxBytes += iRtxCurrent;
	}

	return (iRtxBytes);
}


//һ���Է�������(�ص�IO)
int TE_SendLL(SOCKET hSocket, char const * pszBuffer, int iBufferSize)
{
	DWORD	dwRtxBytes = 0;
	WSABUF	WSABuff;

	ZeroMemory(&WSABuff,sizeof(WSABUF));
	WSABuff.len = iBufferSize;
	WSABuff.buf = (char *) pszBuffer;

	return ((WSASend(hSocket, &WSABuff, 1, &dwRtxBytes, 0,NULL, NULL) == SOCKET_SUCCESS) ? (int) dwRtxBytes : -WSAGetLastError());

}

// ��������
int TE_SendData(SOCKET hSocket, char const * pszBuffer, int iBufferSize, DWORD dwTimeout)
{

	HANDLE	hWriteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	if (hWriteEvent == NULL)
	{
		TE_SetLastError( (int)GetLastError() );
		return (SOCKET_ERROR);
	}

	int iSendBytes = 0;

	for (;;)
	{
		////////////////////////////////////////////////////////////////
		// �������ݳɹ�
		if ((iSendBytes = TE_SendLL(hSocket, pszBuffer, iBufferSize)) >= 0)
			break;

		int iErrorCode = -iSendBytes;

		if (iErrorCode != WSAEWOULDBLOCK)
		{
			CloseHandle(hWriteEvent);
			TE_SetLastError( WSAGetLastError() );
			return (SOCKET_ERROR);
		}

		
		///////////////////////////////////////////////////////////////////////////////
		//  ˯��һ��ʱ��
		///////////////////////////////////////////////////////////////////////////////
		Sleep(TE_BLOCKED_SNDRCV_SLEEP);


		// ע��FD_WRITE | FD_CLOSE �¼�
		if( WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, FD_WRITE|FD_CLOSE) == SOCKET_ERROR)
		{
			CloseHandle(hWriteEvent);
			TE_SetLastError( WSAGetLastError() );
			return (SOCKET_ERROR);
		}

		// �ȴ��¼�����
		DWORD dwWaitResult = WSAWaitForMultipleEvents(1, &hWriteEvent, TRUE,dwTimeout, TRUE);

		if (dwWaitResult != WSA_WAIT_EVENT_0)
		{
			// ��������¼�
			WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, 0);
			CloseHandle(hWriteEvent);
			TE_SetLastError( WSAGetLastError() );
			return (SOCKET_ERROR);
		}

		////////////////////////////////////////////////////////////// 
		///	ע�⣺��ʹ dwWaitResult == WSA_WAIT_EVENT0 ��ҲӦ�� 
		///			��һ����������Ƿ�������
		///////////////////////////////////////////////////////////////
		WSANETWORKEVENTS NetEvent;
		if(WSAEnumNetworkEvents(hSocket,(WSAEVENT)hWriteEvent,&NetEvent) == SOCKET_ERROR)
		{
  			// ��������¼�
			WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, 0);
			CloseHandle(hWriteEvent);
			TE_SetLastError( WSAGetLastError() );
			return (SOCKET_ERROR);
		}
		if( ( NetEvent.lNetworkEvents == FD_CLOSE ) ||
			 ( NetEvent.lNetworkEvents == FD_WRITE   &&
				NetEvent.iErrorCode[FD_WRITE_BIT] !=0 ) )	// ��������
		{
			// ��������¼�
			WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, 0);
			CloseHandle(hWriteEvent);
			TE_SetLastError( WSAGetLastError() );
			return (SOCKET_ERROR);
		}
		// ��������¼�
		WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, 0);
   }

    CloseHandle(hWriteEvent);
    return (iSendBytes);
}

//�������������ݻ�ʱ
int TE_Send(SOCKET hSocket, char const * pszBuffer, int iBufferSize, DWORD dwTimeout)
{

	int iRtxBytes	= 0;
	int iRtxCurrent = 0;

	while (iRtxBytes < iBufferSize)
	{
		iRtxCurrent = TE_SendData(hSocket, (pszBuffer + iRtxBytes),(iBufferSize - iRtxBytes), dwTimeout);
		if (iRtxCurrent < 0)
			return (iRtxBytes);

		iRtxBytes += iRtxCurrent;
	}
	return (iRtxBytes);
}

// ��������
int TE_Connect(SOCKET hSocket, const struct sockaddr * pSocketAddress, int iNameLen,DWORD dwTimeout)
{

	HANDLE hConnectEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	if (hConnectEvent == NULL)
	{
		TE_SetLastError( (int)GetLastError() );
		return (SOCKET_ERROR);
	}

	// ע��FD_CONNECT�¼�
	if( WSAEventSelect(hSocket, (WSAEVENT) hConnectEvent, FD_CONNECT) == SOCKET_ERROR)
	{
		CloseHandle(hConnectEvent);
		TE_SetLastError( WSAGetLastError() );
		return (SOCKET_ERROR);
	}

	int	iConnectResult = WSAConnect(hSocket, pSocketAddress, iNameLen, NULL, NULL, NULL, NULL);
	int	iConnectError  = WSAGetLastError();
	
	if ((iConnectResult == SOCKET_ERROR) && (iConnectError == WSAEWOULDBLOCK))
	{
		DWORD dwWaitResult = WSAWaitForMultipleEvents(1, &hConnectEvent, TRUE,dwTimeout, TRUE);
		
		if (dwWaitResult != WSA_WAIT_EVENT_0)
		{
			TE_SetLastError( WSAGetLastError() );
			iConnectResult = SOCKET_ERROR;
		}
		else
		{
			////////////////////////////////////////////////////////////// 
			///	ע�⣺��ʹ dwWaitResult == WSA_WAIT_EVENT0 ��ҲӦ�� 
			///			��һ����������Ƿ�������
			///////////////////////////////////////////////////////////////
			WSANETWORKEVENTS NetEvent;
			if(WSAEnumNetworkEvents(hSocket,(WSAEVENT)hConnectEvent,&NetEvent) == SOCKET_ERROR)
			{
				TE_SetLastError( WSAGetLastError() );
				iConnectResult = SOCKET_ERROR;
			}
			else if(NetEvent.iErrorCode[FD_CONNECT_BIT] !=0 )	// ��������
			{
				TE_SetLastError( NetEvent.iErrorCode[FD_CONNECT_BIT] );
				iConnectResult = SOCKET_ERROR;
			}
			else
				iConnectResult = SOCKET_SUCCESS;
			////////////////////////////////////////////////////////////////
		}
	}

	// ע�������¼�
	WSAEventSelect(hSocket, (WSAEVENT) hConnectEvent, 0);
	CloseHandle(hConnectEvent);
	return (iConnectResult);
}


///////////////////////////////////////////////////////////
//
//	����ú�����Ŀ����Ϊ�˱���NT�¶�����������CACHE��ɵ�����
//
///////////////////////////////////////////////////////////
DWORD WINAPI DNSThread(  LPVOID pParam )
{
	DWORD dwIP = INADDR_NONE;
	PHOSTENT pHost = gethostbyname( (char *)pParam );
	if(pHost == NULL)
		return INADDR_NONE;
	dwIP = inet_addr( inet_ntoa(*(IN_ADDR *)*pHost->h_addr_list) );
	return dwIP;
}

DWORD TE_GetIP(const char* name,BOOL fFixNtDNS /* = FALSE*/) // Used to Fix NT DNS Problem
{
	DWORD dwIP = inet_addr(name);
	if( dwIP != INADDR_NONE )
		return dwIP;

	if( fFixNtDNS )
	{
		OSVERSIONINFO		osVersion;
		osVersion.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if( GetVersionEx(&osVersion) )
		{
			if(osVersion.dwPlatformId == VER_PLATFORM_WIN32_NT)
			{
				DWORD	dwThreadId = 0;
				HANDLE	hThread = CreateThread(NULL,0,DNSThread,(LPVOID)name,0,&dwThreadId);
				if( hThread != NULL)
				{
					WaitForSingleObject(hThread,INFINITE);
					if( GetExitCodeThread(hThread,&dwIP))
						return dwIP;
				}
			}
		}
	}

	PHOSTENT pHost = gethostbyname(name);
	if(pHost == NULL)
		return INADDR_NONE;
		
	dwIP = inet_addr( inet_ntoa(*(IN_ADDR *)*pHost->h_addr_list) );
	return dwIP;
}

// ��������(��չ����)
int TE_ConnectEx(SOCKET hSocket, char const * pszServer, int nPort,DWORD dwTimeout,BOOL fFixNtDNS /*= FALSE*/)
{
	/////////////////////////////////////////////////////////////////////////////
	SOCKADDR_IN sockAddr;
	ZeroMemory(&sockAddr,sizeof(sockAddr));

	sockAddr.sin_family			= AF_INET;
	sockAddr.sin_port			= htons((u_short)nPort);
	sockAddr.sin_addr.s_addr	= TE_GetIP(pszServer,fFixNtDNS);
	
	if (sockAddr.sin_addr.s_addr == INADDR_NONE)
	{
		TE_SetLastError( WSAGetLastError() );
		return (SOCKET_ERROR);
	}
	//////////////////////////////////////////////////////////////////////

	return TE_Connect(hSocket, (SOCKADDR *)&sockAddr,sizeof(sockAddr),dwTimeout);
}

// ���׽���
int TE_BindSocket(SOCKET hSocket, const struct sockaddr * SockName, int iNameLen)
{

	if (bind(hSocket, SockName, iNameLen) == SOCKET_ERROR)
	{
		TE_SetLastError( WSAGetLastError() );
		return (SOCKET_ERROR);
	}

	return (SOCKET_SUCCESS);
}

// ���׽���
int TE_BindSocketEx(SOCKET hSocket,int nPort)
{
	SOCKADDR_IN sockAddr;
	ZeroMemory(&sockAddr,sizeof(sockAddr));

	sockAddr.sin_family			= AF_INET;
	sockAddr.sin_addr.s_addr	= htonl(INADDR_ANY);
	sockAddr.sin_port			= htons((u_short)nPort);

	return TE_BindSocket(hSocket,(SOCKADDR *)&sockAddr, sizeof(sockAddr));
}


// �����׽���
int TE_ListenSocket(SOCKET hSocket, int iConnections)
{
	if(listen(hSocket, iConnections) == SOCKET_ERROR)
	{
		TE_SetLastError( WSAGetLastError() );
		return (SOCKET_ERROR);
	}
	
	return (SOCKET_SUCCESS);
}


// �����׽�������
SOCKET TE_Accept(SOCKET hSocket, struct sockaddr * pSocketAddress, int *iNameLen,DWORD dwTimeout)
{

	HANDLE hAcceptEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hAcceptEvent == NULL)
	{
		TE_SetLastError( (int)GetLastError() );
		return (INVALID_SOCKET);
	}

	// ע��FD_ACCEPT�¼�
	if( WSAEventSelect(hSocket, (WSAEVENT) hAcceptEvent, FD_ACCEPT) == SOCKET_ERROR)
	{
		CloseHandle(hAcceptEvent);
		TE_SetLastError( WSAGetLastError() );
		return (INVALID_SOCKET);
	}

	SOCKET hSocketAccept = WSAAccept(hSocket, pSocketAddress, iNameLen, NULL, 0);
	int	   iConnectError = WSAGetLastError();

	if ((hSocketAccept == INVALID_SOCKET) && (iConnectError == WSAEWOULDBLOCK))
	{

		// ����
		DWORD dwWaitResult = WSAWaitForMultipleEvents(1, &hAcceptEvent, TRUE,dwTimeout, TRUE);

		if (dwWaitResult == WSA_WAIT_EVENT_0)
		{
			////////////////////////////////////////////////////////////// 
			///	ע�⣺��ʹ dwWaitResult == WSA_WAIT_EVENT0 ��ҲӦ�� 
			///			��һ����������Ƿ�������
			///////////////////////////////////////////////////////////////
			WSANETWORKEVENTS NetEvent;
			if(WSAEnumNetworkEvents(hSocket,hAcceptEvent,&NetEvent) == SOCKET_ERROR)
				TE_SetLastError( WSAGetLastError() );
			else if(NetEvent.iErrorCode[FD_ACCEPT_BIT] !=0 )	// ��������
				TE_SetLastError( NetEvent.iErrorCode[FD_ACCEPT_BIT] );
			else
				hSocketAccept = WSAAccept(hSocket, pSocketAddress, iNameLen, NULL, 0);
		}
		else
			TE_SetLastError( WSAGetLastError() );
	}
	
	// ע�������¼�
	WSAEventSelect(hSocket, (WSAEVENT) hAcceptEvent, 0);
	CloseHandle(hAcceptEvent);

	if (hSocketAccept != INVALID_SOCKET)
	{
		// �����׽��ֵ�����Ϊ��ַ�����ò���Ϊ��������
		if (	(TE_BlockSocket(hSocketAccept, 0)  == SOCKET_ERROR ) ||
				(TE_SetSocketOption(hSocketAccept) == SOCKET_ERROR ) )
		{
			TE_CloseSocket(hSocketAccept,TRUE);
			return (INVALID_SOCKET);
		}
	}
	return (hSocketAccept);
}

// �����׽�������(�����ж�)
SOCKET	TE_AcceptEx(SOCKET hSocket, struct sockaddr * pSockName, int *iNameLen,HANDLE hEndEvent,DWORD dwTimeout /*= TE_DEFAULT_TIMEOUT*/)
{
	if( hEndEvent == NULL)
		return TE_Accept(hSocket,pSockName,iNameLen,dwTimeout);

	HANDLE	hAcceptEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hAcceptEvent == NULL)
	{
		TE_SetLastError( (int)GetLastError() );
		return (INVALID_SOCKET);
	}

	WSAEVENT hEvent[2]; 
	hEvent[0] = (WSAEVENT)hAcceptEvent;
	hEvent[1] = (WSAEVENT)hEndEvent;

	// ע��FD_ACCEPT�¼�
	if( WSAEventSelect(hSocket, (WSAEVENT) hAcceptEvent, FD_ACCEPT) == SOCKET_ERROR)
	{
		CloseHandle(hAcceptEvent);
		TE_SetLastError( WSAGetLastError() );
		return (INVALID_SOCKET);
	}

	SOCKET hSocketAccept = WSAAccept(hSocket, pSockName, iNameLen, NULL, 0);
	int	   iConnectError = WSAGetLastError();

	if ((hSocketAccept == INVALID_SOCKET) && (iConnectError == WSAEWOULDBLOCK))
	{
		// ����
		DWORD dwWaitResult = WSAWaitForMultipleEvents(2, hEvent, FALSE,dwTimeout, TRUE);
		if (dwWaitResult == WSA_WAIT_EVENT_0)
		{
			////////////////////////////////////////////////////////////// 
			///	ע�⣺��ʹ dwWaitResult == WSA_WAIT_EVENT0 ��ҲӦ�� 
			///			��һ����������Ƿ�������
			///////////////////////////////////////////////////////////////
			WSANETWORKEVENTS NetEvent;
			if(WSAEnumNetworkEvents(hSocket,hAcceptEvent,&NetEvent) == SOCKET_ERROR)
				TE_SetLastError( WSAGetLastError() );
			else if(NetEvent.iErrorCode[FD_ACCEPT_BIT] !=0 )	// ��������
				TE_SetLastError( NetEvent.iErrorCode[FD_ACCEPT_BIT] );
			else
				hSocketAccept = WSAAccept(hSocket, pSockName, iNameLen, NULL, 0);
		}
		else
			TE_SetLastError( WSAGetLastError() );
	}
	
	// ע�������¼�
	WSAEventSelect(hSocket, (WSAEVENT) hAcceptEvent, 0);
	CloseHandle(hAcceptEvent);

	if (hSocketAccept != INVALID_SOCKET)
	{
		// �����׽��ֵ�����Ϊ��ַ�����ò���Ϊ��������
		if (	(TE_BlockSocket(hSocketAccept, 0) < 0) ||
				(TE_SetSocketOption(hSocketAccept) < 0) )
		{
			TE_CloseSocket(hSocketAccept,TRUE);
			return (INVALID_SOCKET);
	
		}
	}
	return (hSocketAccept);

}

// �����׽����Ƿ�Ϊ������
int      TE_BlockSocket(SOCKET hSocket, BOOL bBlock)
{
	u_long  IoctlLong = (bBlock) ? 0 : 1;

	if (ioctlsocket(hSocket, FIONBIO, &IoctlLong) == SOCKET_ERROR)
	{
		TE_SetLastError( WSAGetLastError() );
		return (SOCKET_ERROR);
    }

	return (SOCKET_SUCCESS);

}

// ���ݱ����պ���
int TE_RecvDataFrom( SOCKET hSocket, struct sockaddr * pFrom, int iFromlen,
					 char *pszBuffer, int iBufferSize, DWORD dwTimeout)
{
	HANDLE hReadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hReadEvent == NULL)
	{
		TE_SetLastError((int)GetLastError() );
		return (SOCKET_ERROR);
	}

	DWORD		dwRtxBytes = 0,
				dwRtxFlags = 0;
	WSABUF		WSABuff;

	ZeroMemory(&WSABuff,sizeof(WSABUF));
	WSABuff.len = iBufferSize;
	WSABuff.buf = pszBuffer;

	for (;;)
	{
		// ע��FD_READ�¼�
		if( WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, FD_READ) == SOCKET_ERROR)
		{
			CloseHandle(hReadEvent);
			TE_SetLastError(  WSAGetLastError() );
			return (SOCKET_ERROR);
		}
		DWORD dwWaitResult = WSAWaitForMultipleEvents(1, &hReadEvent, TRUE,	dwTimeout, TRUE);

		if( dwWaitResult != WSA_WAIT_EVENT_0 )
		{
			// ע���¼�
			WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, 0);
			CloseHandle(hReadEvent);
			TE_SetLastError( WSAGetLastError());
			return (SOCKET_ERROR);
		}

		////////////////////////////////////////////////////////////// 
		///	ע�⣺��ʹ dwWaitResult == WSA_WAIT_EVENT0 ��ҲӦ�� 
		///			��һ����������Ƿ�������
		///////////////////////////////////////////////////////////////
		WSANETWORKEVENTS NetEvent;
		if(WSAEnumNetworkEvents(hSocket,(WSAEVENT)hReadEvent,&NetEvent) == SOCKET_ERROR)
		{
			// ע���¼�
			WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, 0);
			CloseHandle(hReadEvent);
			TE_SetLastError( WSAGetLastError() );
			return (SOCKET_ERROR);
		}
		if(NetEvent.iErrorCode[FD_READ_BIT] !=0 )	// ��������
		{
			// ע���¼�
			WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, 0);
			CloseHandle(hReadEvent);
			TE_SetLastError(NetEvent.iErrorCode[FD_READ_BIT]);
			return (SOCKET_ERROR);
		}
		////////////////////////////////////////////////////////////////
		// ע���¼�
		WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, 0);

		int FromLen = iFromlen;
		if ( WSARecvFrom(hSocket, &WSABuff, 1, &dwRtxBytes, &dwRtxFlags,pFrom, &FromLen, NULL, NULL) == SOCKET_SUCCESS )
			break;

		if ( WSAGetLastError() != WSAEWOULDBLOCK)
		{
			CloseHandle(hReadEvent);
			TE_SetLastError( WSAGetLastError() );
			return (SOCKET_ERROR);
		}

		///////////////////////////////////////////////////////////////////////////
		//	˯��һ��ʱ��
		//////////////////////////////////////////////////////////////////////////
		Sleep(TE_BLOCKED_SNDRCV_SLEEP);
	}
	CloseHandle(hReadEvent);
	return ((int) dwRtxBytes);
}

// ���ݱ��������ݱ�
int TE_SendDataTo(SOCKET hSocket, const struct sockaddr * pTo,int iToLen,
				  char const * pszBuffer, int iBufferSize, DWORD dwTimeout)
{
	HANDLE hWriteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hWriteEvent == NULL)
	{
		TE_SetLastError( (int)GetLastError() );
		return (SOCKET_ERROR);
	}

	DWORD	dwRtxBytes = 0,
            dwRtxFlags = 0;
	WSABUF	WSABuff;

	ZeroMemory(&WSABuff,sizeof(WSABUF));
	WSABuff.len = iBufferSize;
	WSABuff.buf = (char *) pszBuffer;

	for (;;)
	{
		if (WSASendTo( hSocket, &WSABuff, 1, &dwRtxBytes, dwRtxFlags,pTo, iToLen, NULL, NULL) == SOCKET_SUCCESS)
			break;

		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			CloseHandle(hWriteEvent);
			TE_SetLastError(  WSAGetLastError() );
			return (SOCKET_ERROR);
		}

		//////////////////////////////////////////////////////////////////////////
		//	˯��һ��ʱ��
		/////////////////////////////////////////////////////////////////////////
		Sleep(TE_BLOCKED_SNDRCV_SLEEP);

		// ע��FD_WRITE�¼�  
		if( WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, FD_WRITE) == SOCKET_ERROR)
		{
			CloseHandle(hWriteEvent);
			TE_SetLastError( WSAGetLastError() );
			return (SOCKET_ERROR);
		}
		DWORD dwWaitResult = WSAWaitForMultipleEvents(1, &hWriteEvent, TRUE,dwTimeout, TRUE);
		
		if( dwWaitResult != WSA_WAIT_EVENT_0 )
		{
			// ע���¼�
			WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, 0);
			CloseHandle(hWriteEvent);
			TE_SetLastError(  WSAGetLastError() );
			return (SOCKET_ERROR);
		}

		////////////////////////////////////////////////////////////// 
		///	ע�⣺��ʹ dwWaitResult == WSA_WAIT_EVENT0 ��ҲӦ�� 
		///			��һ����������Ƿ�������
		///////////////////////////////////////////////////////////////
		WSANETWORKEVENTS NetEvent;
		if(WSAEnumNetworkEvents(hSocket,(WSAEVENT)hWriteEvent,&NetEvent) == SOCKET_ERROR)
		{
			// ע���¼�
			WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, 0);
			CloseHandle(hWriteEvent);
			TE_SetLastError(  WSAGetLastError() );
			return (SOCKET_ERROR);
		}
		if(NetEvent.iErrorCode[FD_WRITE_BIT] !=0 )	// ��������
		{
			// ע���¼�
			WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, 0);
			CloseHandle(hWriteEvent);
			TE_SetLastError(NetEvent.iErrorCode[FD_WRITE_BIT]);
			return (SOCKET_ERROR);
		}
		////////////////////////////////////////////////////////////////
		// ע���¼�
		WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, 0);
	}

	CloseHandle(hWriteEvent);
	return ((int) dwRtxBytes);
}



////////////////////////////////////////////////////////////////////////////////
//
//	BSocket����
//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//		����: ���׽���
//		����: 
//				hSocket		-- SOCKET(�����׽���)
//				iBufferSize	-- ����������(ȱʡΪTE_SOCKET_BUFFER_SIZE)
//		����: 
//				�ṹָ��(ʧ��ʱΪNULL)
//
////////////////////////////////////////////////////////////////////////////////
PBSD TE_BSocketAttach(SOCKET hSocket, int iBufferSize /* = TE_SOCKET_BUFFER_SIZE */ )
{

	if( hSocket == INVALID_SOCKET)
		return NULL;

	// �����ڴ�
	PBSD pBSD = (PBSD) malloc(sizeof(BSD));

	if (pBSD == NULL)
		return NULL;

	char *pszBuffer = (char *) malloc(iBufferSize);

	if (pszBuffer == NULL)
	{
		free(pBSD);
		return NULL;
	}

	// ���ýṹ��Ա
	ZeroMemory(pBSD,sizeof(BSD));
	ZeroMemory(pszBuffer,iBufferSize);

	pBSD->hSocket			= hSocket;
	pBSD->iBufferSize		= iBufferSize;
	pBSD->pszBuffer			= pszBuffer;
	pBSD->iBytesInBuffer	= 0;
	pBSD->iReadIndex		= 0;
	pBSD->iBufferIndex		= 0;

	return pBSD;
}

////////////////////////////////////////////////////////////////////////////
//
//		����: �⿪�׽���
//		����: 
//				pBSD				--	BufSocketData�ṹָ��
//				bCloseSocket		--	�Ƿ��ڽ⿪�׽���ͬʱ�ر��׽���(ȱʡΪFALSE)
//		����: 
//				��bCloseSocketΪFALSE,���ؽ⿪���׽���
//				��bCloseSocketΪTRUE ,����INVALID_SOCKET
//
///////////////////////////////////////////////////////////////////////////
SOCKET TE_BSocketDetach(PBSD pBSD, BOOL bCloseSocket /* = FALSE */ )
{
	SOCKET		 hSocket = pBSD->hSocket;

	// �ͷ��ڴ�
	free(pBSD->pszBuffer);
	free(pBSD);

	// �Ƿ�ر��׽���
	if (bCloseSocket)
	{
		TE_CloseSocket(hSocket);
		return (INVALID_SOCKET);
	}
	return (hSocket);
}


////////////////////////////////////////////////////////////////////
//
//		����: �ӻ�������ȡ����
//		����: 
//				pBSD		 -- BufSocketData�ṹָ��
//				dwTimeOut	 -- ���ճ�ʱ(ȱʡΪTE_RECV_TIMEOUT)	
//		����: 
//				 0	---	�ɹ� (SOCKET_SUCCESS)
//				-1	---	ʧ�� (SOCKET_ERROR)	
//
////////////////////////////////////////////////////////////////////
int TE_BSocketReadData(PBSD pBSD, DWORD dwTimeout /* = TE_RECV_TIMEOUT */ )
{
	// ���㻺������������
	int	iMaxRead = pBSD->iBufferSize - pBSD->iBytesInBuffer;
	char  *pszBuffer = (char *) malloc(iMaxRead + 1);

	if (pszBuffer == NULL)
		return (SOCKET_ERROR);
	
	// ���
	ZeroMemory(pszBuffer,iMaxRead+1);

	// ��������
	int iReadedBytes = TE_RecvData(pBSD->hSocket, pszBuffer, iMaxRead, dwTimeout);

	if (iReadedBytes > 0)
	{
		int iHeadSize = Min(pBSD->iBufferSize - pBSD->iBufferIndex, iReadedBytes);

		if (iHeadSize > 0)
			memcpy(pBSD->pszBuffer + pBSD->iBufferIndex, pszBuffer, iHeadSize);

		pBSD->iBufferIndex += iHeadSize;

		if (pBSD->iBufferIndex == pBSD->iBufferSize)
			pBSD->iBufferIndex = 0;

		int iBackSize = iReadedBytes - iHeadSize;

		if (iBackSize > 0)
			memcpy(pBSD->pszBuffer + pBSD->iBufferIndex, pszBuffer + iHeadSize, iBackSize);

		pBSD->iBufferIndex += iBackSize;
		pBSD->iBytesInBuffer += iReadedBytes;
	}

	free(pszBuffer);
	return (iReadedBytes);
}


////////////////////////////////////////////////////////////////////
//
//		����: �ӻ�������ȡһ���ַ�
//		����: 
//				pBSD		 -- BufSocketData�ṹָ��
//				dwTimeOut -- ���ճ�ʱ(ȱʡΪTE_RECV_TIMEOUT)	
//		����: 
//				һ���ַ�(����ʱ����TE_EOF)
//
////////////////////////////////////////////////////////////////////
int TE_BSocketGetChar(PBSD pBSD, DWORD dwTimeout /* = TE_RECV_TIMEOUT */ )
{
	if ((pBSD->iBytesInBuffer == 0) && (TE_BSocketReadData(pBSD, dwTimeout) <= 0))
		return (TE_EOF);

	int iChar =( (int) pBSD->pszBuffer[pBSD->iReadIndex]) & 0x000000ff;

	pBSD->iReadIndex = INext(pBSD->iReadIndex, pBSD->iBufferSize);

	--pBSD->iBytesInBuffer;

	return (iChar);
}


////////////////////////////////////////////////////////////////////////////
//
//		����: �ӻ�������ȡһ��(ע�⣬��β�Ļس�����0x0D,0x0A��������������)
//		����: 
//				pBSD		 -- BufSocketData�ṹָ��
//				pszBuffer	 -- ���ջ�����
//				iBufferSize	 -- �����С
//				iStatus		 -- ״̬ (0:����,1:���岻��,-1:����)
//				dwTimeOut	 -- ���ճ�ʱ(ȱʡΪTE_RECV_TIMEOUT)	
//		����: 
//				 0	---	�ɹ� (SOCKET_SUCCESS)
//				-1	---	ʧ�� (SOCKET_ERROR)	
//
////////////////////////////////////////////////////////////////////////////
int TE_BSocketGetString(PBSD pBSD, char *pszBuffer, int iBufferSize, int* iStatus, DWORD dwTimeout /* = TE_RECV_TIMEOUT */ )
{
	
	*iStatus = 1;		//���峤�Ȳ���

	int ii,iChar;
	for (ii = 0; ii < (iBufferSize - 1);)
	{
		iChar = TE_BSocketGetChar(pBSD, dwTimeout);
		if (iChar == TE_EOF)
		{
			*iStatus = (-1) ;
			return SOCKET_ERROR;
		}

		if (iChar == 0x0D)	// �س�����
		{
			iChar = TE_BSocketGetChar(pBSD, dwTimeout);
			if (iChar == TE_EOF)
			{
				*iStatus = (-1);
				return (SOCKET_ERROR);
			}

			if (iChar == 0x0A)	// ����
			{
				*iStatus = 0;	//�������
				break;
			}
			else
				pszBuffer[ii++] = 0x0D;
		}
		else
			pszBuffer[ii++] = (char) iChar;
	}
	pszBuffer[ii] = '\0';

	return (SOCKET_SUCCESS);
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//		����: �ӻ�������ȡһ��(����������0x0A)(ע�⣬��β�Ļس����в�����������)
//		����: 
//				pBSD		-- BufSocketData�ṹָ��
//				pszBuffer	 -- ���ջ�����
//				iBufferSize	 -- �����С
//				iStatus		-- ״̬ (0:����,1:���岻��,-1:����)
//				dwTimeOut	-- ���ճ�ʱ(ȱʡΪTE_RECV_TIMEOUT)	
//		����: 
//				 0	---	�ɹ� (SOCKET_SUCCESS)
//				-1	---	ʧ�� (SOCKET_ERROR)	
//
//////////////////////////////////////////////////////////////////////////////////////////
int TE_BSocketGetStringEx(PBSD pBSD, char *pszBuffer, int iBufferSize, int* iStatus, DWORD dwTimeout /* = TE_RECV_TIMEOUT */ )
{
	
	*iStatus = 1;		//���峤�Ȳ���

	int ii,iChar;
	int LastChar = TE_EOF;
	for (ii = 0; ii < (iBufferSize - 1);)
	{
		iChar = TE_BSocketGetChar(pBSD, dwTimeout);

		if (iChar == TE_EOF)
		{
			*iStatus = (-1) ;
			return SOCKET_ERROR;
		}

		if (iChar == 0x0A)	// ���з���
		{
			*iStatus = 0;	//�������
			if (LastChar == 0x0D)
				ii-- ;	
			break;
		}
		else
			pszBuffer[ii++] = (char) iChar;

		LastChar = iChar;
			
	}
	pszBuffer[ii] = '\0';

	return (SOCKET_SUCCESS);
}



////////////////////////////////////////////////////////////////////
//
//		����: ����һ�� : �Զ��������ϡ��س����з�(0x0D,0x0A)��
//		����: 
//				pBSD		-- BufSocketData�ṹָ��
//				pszBuffer	-- �������ַ���
//				dwTimeOut	-- ���ͳ�ʱ(ȱʡΪTE_SEND_TIMEOUT)	
//		����: 
//				 0	---	�ɹ� (SOCKET_SUCCESS)
//				-1	---	ʧ�� (SOCKET_ERROR)	
//
////////////////////////////////////////////////////////////////////
int TE_BSocketSendString(PBSD pBSD, const char *pszBuffer, DWORD dwTimeout /* = TE_SEND_TIMEOUT */ )
{

	char *pszSendBuffer = (char *) malloc(strlen(pszBuffer) + 3);

	if (pszSendBuffer == NULL)
		return (SOCKET_ERROR);

	ZeroMemory( pszSendBuffer,strlen(pszBuffer) + 3);
	_snprintf(pszSendBuffer, strlen(pszBuffer) + 3, "%s\r\n", pszBuffer);

	int iSendLength = strlen(pszSendBuffer);
	if (TE_Send(pBSD->hSocket, pszSendBuffer, iSendLength, dwTimeout) != iSendLength)
	{
        free(pszSendBuffer);
		return (SOCKET_ERROR);
    }
	free(pszSendBuffer);
	return (iSendLength);
}


////////////////////////////////////////////////////////////////////
//
//		����: ��ȡ�׽���
//		����: 
//				pBSD -- BufSocketData�ṹָ��
//		����: 
//				��˽ṹ����һ���SOCKET	
//
////////////////////////////////////////////////////////////////////
SOCKET TE_BSocketGetAttachedSocket(PBSD pBSD)
{
	return (pBSD->hSocket);
}

////////////////////////////////////////////////////////////////////
//
//		����: �ӻ�������ȡһ������������
//		����: 
//				pBSD		 -- BufSocketData�ṹָ��
//				pszBuffer	 -- ���ջ�����
//				iBufferSize	 -- �����С
//				dwTimeOut	 -- ���ճ�ʱ(ȱʡΪTE_RECV_TIMEOUT)	
//		����: 
//				�������ݵ��ֽ���
////////////////////////////////////////////////////////////////////
int TE_BSocketGetData(PBSD pBSD, char *pszBuffer, int iBufferSize,DWORD dwTimeout /*= TE_RECV_TIMEOUT*/)
{
	int iReadBytes	 = 0;
	int iHeadSize,iBackSize;

	if ((pBSD->iBytesInBuffer == 0) && (TE_BSocketReadData(pBSD, dwTimeout) <= 0))
		return 0; 

	if( pBSD->iBytesInBuffer < iBufferSize ) // ���ݲ�����
	{
		iHeadSize = Min( pBSD->iBufferSize - pBSD->iReadIndex ,pBSD->iBytesInBuffer );
		memcpy(pszBuffer+iReadBytes,pBSD->pszBuffer+pBSD->iReadIndex,iHeadSize);
			
		pBSD->iReadIndex += iHeadSize;
		if( pBSD->iReadIndex == pBSD->iBufferSize )
			pBSD->iReadIndex = 0;

		iReadBytes += iHeadSize;
		iBackSize = pBSD->iBytesInBuffer - iHeadSize;
			
		if( iBackSize > 0)
			memcpy(pszBuffer+iReadBytes,pBSD->pszBuffer+pBSD->iReadIndex,iBackSize);

		iReadBytes			 += iBackSize;
		pBSD->iReadIndex	 += iBackSize;
		pBSD->iBytesInBuffer = 0; // ����ȫ������
	}
	else // ��ε������㹻����
	{
		iHeadSize = Min( pBSD->iBufferSize - pBSD->iReadIndex,iBufferSize - iReadBytes );
		memcpy(pszBuffer+iReadBytes,pBSD->pszBuffer+pBSD->iReadIndex,iHeadSize);
			
		pBSD->iReadIndex += iHeadSize;
		if( pBSD->iReadIndex == pBSD->iBufferSize )
			pBSD->iReadIndex = 0;

		iReadBytes += iHeadSize;
		iBackSize = iBufferSize - iReadBytes;

		if( iBackSize > 0)
			memcpy(pszBuffer+iReadBytes,pBSD->pszBuffer+pBSD->iReadIndex,iBackSize);

		iReadBytes			 += iBackSize;
		pBSD->iReadIndex	 += iBackSize;
		pBSD->iBytesInBuffer -= (iHeadSize+iBackSize);
	}
	return iReadBytes;
}
