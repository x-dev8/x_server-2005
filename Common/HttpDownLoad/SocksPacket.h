#ifndef __SOCKSPACKET__H__INCLUDED__
#define __SOCKSPACKET__H__INCLUDED__

//��������
const DWORD	SOP_SEND_TIMEOUT= 120*1000;		
const DWORD	SOP_RECV_TIMEOUT= 120*1000;		
const UINT	SOP_BUFFER_SIZE	= 4096;			// ���ݽ��ջ�������С
const BYTE	BYTE_NULL		= 0x00;			// ���ֽ�
const WORD	WORD_NULL		= 0x0000;		// ����
const DWORD UNKNOWN_IP		= 0x00000001;	// �����IP��ַ,ָ��ҪSOCKS4A PROXY��������
const BYTE	AUTH_OK			= 0x00;

// SOCKS������
const UINT	SOCKS_TYPE_4	= 0x01;
const UINT	SOCKS_TYPE_4A	= 0x02;
const UINT	SOCKS_TYPE_5	= 0x03; 

// SOCKS�İ汾��
const BYTE	VER_SOCKS4		= 0x04;
const BYTE	VER_SOCKS4A		= 0x04;
const BYTE	VER_SOCKS5		= 0x05;
const BYTE	VER_SOCKSUNKNOWN= 0xFF;

//��֧�ֵ�����
const BYTE	CMD_CONNECT		= 0x01;
const BYTE	CMD_BIND		= 0x02;
const BYTE	CMD_UDP			= 0x03;	// (SOCKS5 ONLY)
const BYTE	CMD_UNKNOWN		= 0xFF;

/* SOCKS4(A)����(����ֵ) */
const BYTE	REP4_SUCCESS	= 90;
const BYTE	REP4_RESULT		= 90;
const BYTE	REP4_FAIL		= 91;
const BYTE	REP4_NOIDENTD	= 92;
const BYTE	REP4_BADID		= 93;

/* SOCKS5����(����ֵ) */
const BYTE	REP5_SUCCESS	= 0x00;
const BYTE	REP5_RESULT		= 0x00;
const BYTE	REP5_FAIL		= 0x01;
const BYTE	REP5_NOTALLOW	= 0x02;
const BYTE	REP5_NETUNREACH	= 0x03;
const BYTE	REP5_HOSTUNREACH= 0x04;
const BYTE	REP5_CONNREF	= 0x05;
const BYTE	REP5_TTLEXP		= 0x06;
const BYTE	REP5_BADCMD		= 0x07;
const BYTE	REP5_BADADDR	= 0x08;

// ��֤��ʽ(SOCKS5 ONLY)
const BYTE	AUTH_NONE		= 0x00;
const BYTE	AUTH_GSSAPI		= 0x01;
const BYTE	AUTH_PASSWD		= 0x02;
const BYTE	AUTH_CHAP		= 0x03;
const BYTE	AUTH_UNKNOWN	= 0xFF;

// ��ַ��ʽ(SOCKS5 ONLY)
const BYTE	ATYP_IPV4ADDR	= 0x01;
const BYTE	ATYP_HOSTNAME	= 0x03;
const BYTE	ATYP_IPV6ADDR	= 0x04;

// ��������
const UINT	PACKET_SOCKS4REQ			= 0x01;
const UINT	PACKET_SOCKS4AREQ			= 0x02;
const UINT	PACKET_SOCKS5AUTHREQ		= 0x03;
const UINT	PACKET_SOCKS5AUTHPASSWDREQ	= 0x04;
const UINT	PACKET_SOCKS5REQ			= 0x05;

const UINT	PACKET_SOCKS4REP			= 0x21;
const UINT	PACKET_SOCKS4AREP			= 0x22;
const UINT	PACKET_SOCKS5AUTHREP		= 0x23;
const UINT	PACKET_SOCKS5AUTHPASSWDREP	= 0x24;
const UINT	PACKET_SOCKS5REP			= 0x25;

const UINT	PACKET_SOCKS5UDP			= 0x41;


///////////////////////////////////////////////////////
//
//	SOCK4 Proxy
//
//////////////////////////////////////////////////////
typedef struct _tagSocks4Req
{
	BYTE	bVer;		// �汾�� 0x04
	BYTE	bCmd;		// ����
	WORD	wDestPort;	// Ŀ��˿�
	DWORD	dwDestIP;	// Ŀ��IP��ַ
	LPCSTR	pszUserID;	// �û�ID
	BYTE	bNULL;		// 0x00
}SOCKS4REQ,*PSOCKS4REQ;

typedef struct _tagSock4Rep
{
	BYTE	bVer;
	BYTE	bRep;		// 90-93
	WORD	wDestPort;
	DWORD	dwDestIP;
}SOCK4REP,SOCKS4AREP,*PSOCK4REP,*PSOCK4AREP;

///////////////////////////////////////////////////////
//
//	SOCK4A Proxy
//
//////////////////////////////////////////////////////

typedef struct _tagSocks4AReq
{
	BYTE	bVer;			// �汾�� 0x04
	BYTE	bCmd;			// ����
	WORD	wDestPort;		// Ŀ��˿�
	DWORD	dwDestIP;		// Ŀ�����IP��ַ 0x000000XX
	LPCSTR	pszUserID;		// �û�ID
	BYTE	bNULL1;			// �ָ���
	LPCSTR	pszDestHostName;// Ŀ���������
	BYTE	bNULL2;			// ����0x00
}SOCKS4AREQ,*PSOCKS4AREQ;

///////////////////////////////////////////////////////
//
//	SOCK5 Proxy
//
//////////////////////////////////////////////////////
// Auth-Request
typedef struct _tagSocks5AuthReq
{
	BYTE	bVer;
	BYTE	bNAuth;
	LPCSTR	pszAuth;
}SOCKS5AUTHREQ,*PSOCKS5AUTHREQ;

// Auth-Reply
typedef struct _tagSocks5AuthRep
{
	BYTE	bVer;
	BYTE	bAuth;
}SOCKS5AUTHREP,*PSOCKS5AUTHREP;

// USERNAME/PASSWORD��֤ - Request
typedef struct _tagSocks5AuthPasswdReq
{
	BYTE	bVer;
	BYTE	bUserNameLen;
	LPCSTR	pszUserName;
	BYTE	bPasswdLen;
	LPCSTR	pszPasswd;
}SOCKS5AUTHPASSWDREQ,*PSOCKS5AUTHPASSWDREQ;

// USERNAME/PASSWORD��֤ - Reply
typedef struct _tagSocks5AuthPasswdRep
{
	BYTE	bVer;
	BYTE	bStatus;
}SOCKS5AUTHPASSWDREP,*PSOCKS5AUTHPASSWDREP;
 
// Request
typedef struct _tagSocks5Req
{
	BYTE	bVer;
	BYTE	bCmd;
	BYTE	bRsv;
	BYTE	bAtyp;
	LPCSTR	pszDestAddr;	// ���ֽ��ǳ���,������������,û�н�����NULL��(03)
	WORD	wDestPort;
}SOCKS5REQ,*PSOCKS5REQ;

// Reply
typedef struct _tagSocks5Rep
{
	BYTE	bVer;
	BYTE	bRep;
	BYTE	bRsv;
	BYTE	bAtyp;
	LPSTR	pszBindAddr;
	WORD	wBindPort;
}SOCKS5REP,*PSOCKS5REP;


// UDP (Socks5 ONLY)
typedef struct _tagSocks5UDP
{
	WORD	wRsv;
	BYTE	bFrag;
	BYTE	bAtyp;
	LPSTR	pszDestAddr;
	WORD	wDestPort;
	LPSTR	pszData;
}SOCKS5UDP,*PSOCKS5UDP;

// ��������
// Request-Packet (TCP ONLY)
typedef union _tagSocksReqPacket
{
	SOCKS4REQ				socks4Req;
	SOCKS4AREQ				socks4aReq;
	SOCKS5AUTHREQ			socks5AuthReq;
	SOCKS5AUTHPASSWDREQ		socks5AuthPasswdReq;
	SOCKS5REQ				socks5Req;
}SOCKSREQPACKET,*PSOCKSREQPACKET;

// Reply-Packet (TCP ONLY)
typedef union _tagSocksRepPacket
{
	SOCK4REP				socks4Rep;
	SOCKS4AREP				socks4aRep;
	SOCKS5AUTHREP			socks5AuthRep;
	SOCKS5AUTHPASSWDREP		socks5AuthPasswdRep;
	SOCKS5REP				socks5Rep;
}SOCKSREPPACKET,*PSOCKSREPPACKET;

// Request-Reply UDP Packet (UDP ONLY)
typedef union _tagSocksUDPPacket
{
	SOCKS5UDP				socks5UDP;
}SOCKSUDPPACKET,*PSOCKSUDPPACKET;


//���� (SOP: Socks Packet)
// ����
int SOP_PacketSize(PSOCKSREQPACKET pPacket,UINT nPacketType);
int SOP_Pack(char *pszDest,PSOCKSREQPACKET pPacket,UINT nPacketType);
int SOP_SendPacket(SOCKET hSocket,PSOCKSREQPACKET pPacket,UINT nPacketType,DWORD dwTimeout = SOP_SEND_TIMEOUT);
int SOP_SendSocks4Req(SOCKET hSocket,BYTE bCmd,WORD wDestPort,DWORD dwDestIP,const char * pszUserID  = NULL ,DWORD dwTimeout  = SOP_SEND_TIMEOUT );
int SOP_SendSocks4aReq(SOCKET hSocket,BYTE bCmd,WORD wDestPort,const char* pszDestHostName,const char * pszUserID  = NULL ,DWORD dwTimeout  = SOP_SEND_TIMEOUT );
int SOP_SendSocks5AuthReq(SOCKET hSocket,BYTE bNAuth,const char* pszAuth,DWORD dwTimeout  = SOP_SEND_TIMEOUT );
int SOP_SendSocks5AuthPasswdReq(SOCKET hSocket,const char* pszUserName,const char * pszPassword,DWORD dwTimeout  = SOP_SEND_TIMEOUT );
int SOP_SendSocks5Req(SOCKET hSocket,BYTE bCmd,BYTE bAtyp,const char * pszDestAddr,WORD wDestPort,DWORD dwTimeout  = SOP_SEND_TIMEOUT );
// ����
int SOP_RecvPacket(PBSD pBSD,PSOCKSREPPACKET pPacket,UINT nPacketType,DWORD dwTimeout = SOP_RECV_TIMEOUT);
// ����
BOOL SOP_IsSocksOK( PSOCKSREPPACKET pPacket,UINT nPacketType );

#endif //__SOCKSPACKET__H__INCLUDED__