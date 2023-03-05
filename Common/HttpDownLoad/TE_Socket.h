#ifndef __TE__SOCKET__H__INCLUDED__
#define __TE__SOCKET__H__INCLUDED__


//������Ҫ��ͷ�ļ�	
#include <winsock2.h>			// Winsock2

//��
#define Min(a, b)               (((a) < (b)) ? (a): (b))
#define Max(a, b)               (((a) > (b)) ? (a): (b))
#define INext(i, n)             ((((i) + 1) < (n)) ? ((i) + 1): 0)
#define IPrev(i, n)             (((i) > 0) ? ((i) - 1): ((n) - 1))

// ��������
const int TE_SOCKET_BUFFER_SIZE			= 4096;// ������ȱʡ��С
const int TE_EOF						= 0x100;// ��Ч�����ַ�
const int SOCKET_SUCCESS				= 0;
const int TE_SOCKET_MAJOR_VERSION		= 2;
const int TE_SOCKET_MINOR_VERSION		= 2;

// ȱʡ��ʱ���� (��ʱ��λ������ )
const DWORD	TE_SHUTDOWN_RECV_TIMEOUT	= 4*1000;  // ���Źر�ʱ�ӳ�4��
const DWORD TE_BLOCKED_SNDRCV_SLEEP		= 100;	   // 100����(��������ʱ�ȴ�[˯��]ʱ��)
const DWORD TE_DEFAULT_TIMEOUT			= 120*1000;// 120�� ȱʡ��ʱ
const DWORD TE_CONNECT_TIMEOUT			= 120*1000;// 120�� ���ӳ�ʱ
const DWORD TE_SEND_TIMEOUT				= 120*1000;// 120�� ���ͳ�ʱ
const DWORD TE_RECV_TIMEOUT				= 120*1000;// 120�� ���ճ�ʱ 

// ���ݽṹ(������ѭ��ʹ��)
typedef struct _tagBufSocketData
{
    SOCKET			hSocket;			// SOCKET
    int             iBufferSize;		// ���ݻ����С
    char*           pszBuffer;			// ���ݻ���
    int             iBytesInBuffer;		// �������������ݳ���(�ֽ�)
    int             iReadIndex;			// ���Զ�ȡ����һ������λ��
    int             iBufferIndex;		// ����ʹ�õ���һ������λ��	
}BSD,*PBSD;

// ��ȡ�����ô���/�ڴ����������
int		TE_GetLastError(void);
void	TE_SetLastError(int iErrorCode);

// SOCKET���� (����Winsock2)
int		TE_InitLibrary();
void	TE_CleanupLibrary();
SOCKET	TE_CreateSocket(int iAddressFamily = AF_INET, 
						int iType	       = SOCK_STREAM, 
						int iProtocol	   = 0);
void	TE_CloseSocket(SOCKET hSocket, BOOL bHardClose = FALSE);
int     TE_SetSocketOption(SOCKET hSocket);
int     TE_RecvLL(SOCKET hSocket, char *pszBuffer, int iBufferSize);
int		TE_RecvData(SOCKET hSocket, char *pszBuffer, int iBufferSize, DWORD dwTimeout = TE_RECV_TIMEOUT);
int		TE_Recv(SOCKET hSocket, char *pszBuffer, int iBufferSize, DWORD dwTimeout = TE_RECV_TIMEOUT);
int     TE_SendLL(SOCKET hSocket, char const * pszBuffer, int iBufferSize);
int		TE_SendData(SOCKET hSocket, char const * pszBuffer, int iBufferSize, DWORD dwTimeout = TE_SEND_TIMEOUT);
int		TE_Send(SOCKET hSocket, char const * pszBuffer, int iBufferSize, DWORD dwTimeout = TE_SEND_TIMEOUT);
int		TE_Connect(SOCKET hSocket, const struct sockaddr * pSockName, int iNameLen,DWORD dwTimeout = TE_CONNECT_TIMEOUT);
int		TE_BindSocket(SOCKET hSocket, const struct sockaddr * SockName, int iNameLen);
int		TE_ListenSocket(SOCKET hSocket, int iConnections);
SOCKET	TE_Accept(SOCKET hSocket, struct sockaddr * pSockName, int *iNameLen,DWORD dwTimeout = TE_DEFAULT_TIMEOUT);
SOCKET	TE_AcceptEx(SOCKET hSocket, struct sockaddr * pSockName, int *iNameLen,HANDLE hEndEvent,DWORD dwTimeout = TE_DEFAULT_TIMEOUT);
int     TE_BlockSocket(SOCKET hSocket, BOOL bBlock);
int		TE_RecvDataFrom(SOCKET hSocket, struct sockaddr * pFrom, int iFromlen,
						char *pszBuffer, int iBufferSize, DWORD dwTimeout = TE_RECV_TIMEOUT);
int		TE_SendDataTo(SOCKET hSocket, const struct sockaddr * pTo,int iToLen,
					  char const * pszBuffer, int iBufferSize, DWORD dwTimeout = TE_RECV_TIMEOUT);

// ��չ����
int		TE_BindSocketEx(SOCKET hSocket,int nPort);
int		TE_ConnectEx(SOCKET hSocket, char const * pServer, int nPort,DWORD dwTimeout = TE_CONNECT_TIMEOUT,BOOL fFixNtDNS = FALSE);

// BufSocket����
PBSD	TE_BSocketAttach(SOCKET hSocket, int iBufferSize = TE_SOCKET_BUFFER_SIZE);
SOCKET	TE_BSocketDetach(PBSD pBSD,  BOOL bCloseSocket = FALSE);
int		TE_BSocketReadData(PBSD pBSD, DWORD dwTimeout = TE_RECV_TIMEOUT);
int		TE_BSocketGetChar(PBSD pBSD, DWORD dwTimeout = TE_RECV_TIMEOUT);
int		TE_BSocketGetString(PBSD pBSD, char *pszBuffer, int iBufferSize,int* iStatus, DWORD dwTimeout = TE_RECV_TIMEOUT);
int		TE_BSocketSendString(PBSD pBSD, const char *pszBuffer, DWORD dwTimeout = TE_SEND_TIMEOUT);
SOCKET	TE_BSocketGetAttachedSocket(PBSD pBSD);
int		TE_BSocketGetStringEx(PBSD pBSD, char *pszBuffer, int iBufferSize, int* iStatus, DWORD dwTimeout = TE_RECV_TIMEOUT);
int		TE_BSocketGetData(PBSD pBSD, char *pszBuffer, int iBufferSize,DWORD dwTimeout = TE_RECV_TIMEOUT);

// ����
DWORD	TE_GetIP(const char* name,BOOL fFixNtDNS  = FALSE); // Used to Fix NT DNS Problem

#endif	//__TE__SOCKET__H__INCLUDED__
