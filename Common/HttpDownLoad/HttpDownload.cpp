////////////////////////////////////////////////////////////////////////////////
//	Copyright (C) 2000-2001 Softelf Inc. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
//
//	Author	: Telan 
//	Date	: 2000-10-04
//	Purpose	: Try to implement a Http Download Class that Support
//			  Resume Download,WWW Authorization,Proxy And Proxy
//			  Authorization,Redirect Support,Timeout Config,Retry
//			  Config,Notify Support,Job management.
//	TODO	: Job Management,Multi-Thread,Cookie Support
//	History	: 
//		1.0	: 2000-09-25 - Resume Download,Redirect Support,Proxy Support		
//		1.1	: 2000-09-26 - Timeout Config,Retry Config,Notify Support
//		1.2	: 2000-09-27 - WWW Authorization,Proxy Authorization
//		2.0 : 2000-10-04 - Change form using direct winsock to TE_Socket Functions
//						 - Add Socks-Proxy Support( socks4,socks4a,socks5 )
//						 - More Robust,More Extensible,More Wieldy 
//	Mailto	: telan@263.net ( Bugs' Report or Comments )
//	Notes	: This source code may be used in any form in any way you desire. It is
//			  provided "as is" without express or implied warranty.Use it at your own
//			  risk! The author accepts no liability for any damage/loss of business 
//			  that this product may cause.
//
////////////////////////////////////////////////////////////////////////////////
// HttpDownload.cpp: implementation of the CHttpDownload class.

#include <afxwin.h>         // MFC 核心组件和标准组件
#include "TE_Socket.h"
#include "SocksPacket.h"	// Socks Proxy Support
#include "HttpDownload.h"
#include "tstring.h"

#include <map>

 extern std::map<int, std::string>	m_mapStringSet;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//缓冲大小 10K
#define READ_BUFFER_SIZE (10*1024)

// 用于BASE64编码、解码的常量
CStringA CHttpDownload::m_strBase64TAB = _T( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" );
UINT	CHttpDownload::m_nBase64Mask[]= { 0, 1, 3, 7, 15, 31, 63, 127, 255 };

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHttpDownload::CHttpDownload()
{
	m_strDownloadUrl	= _T("");
	m_strSavePath		= _T("");
	m_strTempSavePath	= _T("");

	m_nFrom				= 0;
	m_nTo				= 0;

	// 停止下载
	m_bStopDownload		= FALSE;

	// 强制重新下载(不管已有的文件是否与远程文件相同)
	m_bForceDownload	= FALSE;

	// 是否支持断点续传(假定不支持)
	m_bSupportResume	= FALSE;

	// 文件以及下载大小
	m_dwFileSize			= 0;	// 文件总的大小	
	m_dwFileDownloadedSize	= 0;	// 文件总共已经下载的大小

	m_dwDownloadSize	= 0;		// 本次Request需要下载的大小
	m_dwDownloadedSize	= 0;		// 本次Request已经下载的大小

	m_dwHeaderSize		= 0;		// HTTP协议头的长度
	m_strHeader			= _T("");	// HTTP协议头

	// Referer
	m_strReferer		= _T("");
	
	// UserAgent
	m_strUserAgent		= _T("HttpDownload/2.0");

	// 超时TIMEOUT	连接超时、发送超时、接收超时(单位：毫秒)
	m_dwConnectTimeout	= DOWNLOAD_CONNECT_TIMEOUT;	
	m_dwReceiveTimeout	= DOWNLOAD_RECV_TIMEOUT;
	m_dwSendTimeout		= DOWNLOAD_SEND_TIMEOUT;

	// 重试机制
	m_nRetryType		= RETRY_TYPE_NONE;	//重试类型(0:不重试 1:重试一定次数 2:总是重试)
	m_nRetryTimes		= 0;				//重试次数
	m_nRetryDelay		= 0;				//重试延迟(单位：毫秒)
	m_nRetryMax			= 0;				//重试最大次数

	// 错误处理
	m_nErrorCount		= 0;			//错误次数
	m_strError			= _T("");		//错误信息

	// 向其他窗口发送消息
	m_bNotify			= FALSE;			// 是否向外发送通知消息	
	m_hNotifyWnd		= NULL;		// 被通知的窗口
	m_nNotifyMessage	= 0;	// 被通知的消息

	// 是否进行验证 : Request-Header: Authorization
	m_bAuthorization	= FALSE;
	m_strUsername		= _T("");
	m_strPassword		= _T("");

	// 是否使用代理 
	m_bProxy			= FALSE;
	m_strProxyServer	= _T("");
	m_nProxyPort		= 0;
	m_nProxyType		= PROXY_NONE;
	
	// 代理是否需要验证: Request-Header: Proxy-Authorization
	m_bProxyAuthorization = FALSE;
	m_strProxyUsername 	= _T("");
	m_strProxyPassword	= _T("");

	// 下载过程中所用的变量
	m_strServer			= _T("");
	m_strObject			= _T("");
	m_strFileName		= _T("");
	m_nPort				= DEFAULT_HTTP_PORT ;
	
	// SOCKET 和 BufSocket
	m_hSocket			= INVALID_SOCKET;
	m_pBSD				= NULL;

	m_proc				=NULL;
}

// 析构函数
CHttpDownload::~CHttpDownload()
{
	CloseSocket();
}

BOOL CHttpDownload::Init()
{
	return TRUE;
}

BOOL CHttpDownload::ShutDown()
{
	return TRUE;
}

UINT CHttpDownload::RunThread(LPVOID lpArg)
{
	CHttpDownload * pDown = (CHttpDownload*)lpArg;

	return pDown->Download(CString(pDown->m_strDownloadUrl), CString(pDown->m_strSavePath), NULL, pDown->m_nFrom, pDown->m_nTo);
}

// 创建SOCKET
BOOL CHttpDownload::CreateSocket()
{
	CloseSocket();

	m_hSocket = TE_CreateSocket(AF_INET,SOCK_STREAM,0);
	if (m_hSocket == INVALID_SOCKET)
		return FALSE;
	
	m_pBSD = TE_BSocketAttach(m_hSocket,READ_BUFFER_SIZE);
	if( m_pBSD == NULL )
		return FALSE;

	return TRUE;
}

// 关闭SOCKET
void CHttpDownload::CloseSocket()
{
	if( m_pBSD != NULL )
	{
		TE_BSocketDetach(m_pBSD,FALSE);
		m_pBSD = NULL;
	}
	
	if (m_hSocket != INVALID_SOCKET)
	{
		TE_CloseSocket(m_hSocket,TRUE);
		m_hSocket = INVALID_SOCKET;
	}
}

UINT CHttpDownload::Down(LPCSTR lpszDownloadUrl, LPCSTR lpszSavePath, UINT nFrom /* = 0 */, UINT nTo /* = 0 */, BOOL bForceDownload /* = FALSE  */)
{
	m_strDownloadUrl = lpszDownloadUrl;
	m_strSavePath = lpszSavePath;
	m_nFrom = nFrom;
	m_nTo = nTo;
	m_bForceDownload = bForceDownload;

	if(!AfxBeginThread(RunThread, this))
	{
		return E_FAIL;
	}

	return S_OK;
}

// 下载入口
UINT CHttpDownload::Download(LPCTSTR lpszDownloadUrl,
							 LPCTSTR lpszSavePath, 
							 const char* pszCrc, 
							 UINT nFrom /* = 0 */, 
							 UINT nTo /* = 0 */, 
							 BOOL bForceDownload /* = FALSE */
							 )
{
	m_bStopDownload	  = FALSE;
	m_bForceDownload  = bForceDownload;
	m_nRetryTimes	  = 0;
	
	// 检验要下载的URL是否为空
	m_strDownloadUrl = lpszDownloadUrl;
	m_strDownloadUrl.MakeLower();
	m_strDownloadUrl.Replace(_T('\\'), _T('/'));
	m_strDownloadUrl.TrimLeft();
	m_strDownloadUrl.TrimRight();
	if( m_strDownloadUrl.IsEmpty() )
		return DOWNLOAD_RESULT_FAIL;

	// 检验要下载的URL是否有效
	if ( !ParseURL(m_strDownloadUrl, m_strServer, m_strObject, m_nPort))
	{
		// 在前面加上"http://"再试
		m_strDownloadUrl = _T("http://") + m_strDownloadUrl;
		if ( !ParseURL(m_strDownloadUrl,m_strServer, m_strObject, m_nPort) )
		{
			TRACE(_T("Failed to parse the URL: %s\n"), m_strDownloadUrl);
			return DOWNLOAD_RESULT_FAIL;
		}
	}

    //将URL转换成UTF8编码再发送
    m_strObject = _tUTF8CHAR(m_strObject.GetBuffer());

	// 检查本地保存路径
	m_strSavePath =  lpszSavePath;
	m_strSavePath.TrimLeft();
	m_strSavePath.TrimRight();
	if( m_strSavePath.IsEmpty() )
		return DOWNLOAD_RESULT_FAIL;
	m_strTempSavePath =  m_strSavePath;
	m_strTempSavePath += ".temp";

	m_dwDownloadedSize		= 0;
	m_dwFileDownloadedSize	= 0;
	m_dwFileSize			= 0;
	m_dwDownloadSize		= 0;

	BOOL bSendOnce = TRUE;		// 用于控制向hWndNotify窗口发送消息
	
ReDownload:
	UINT nRequestRet = SendRequest(FALSE, nFrom, nTo);
	switch(nRequestRet)
	{
	case SENDREQUEST_SUCCESS:
		break;
	case SENDREQUEST_STOP:
		return DOWNLOAD_RESULT_STOP;
		break;
	case SENDREQUEST_FAIL:
		return DOWNLOAD_RESULT_FAIL;
		break;
	case SENDREQUEST_ERROR:
		// 是否应该停止下载
		if (m_bStopDownload)
			return DOWNLOAD_RESULT_STOP;

		switch( m_nRetryType )
		{
		case RETRY_TYPE_NONE:
			return DOWNLOAD_RESULT_FAIL;
			break;
		case RETRY_TYPE_ALWAYS:
			if( m_nRetryDelay > 0 )
				Sleep(m_nRetryDelay);
			goto ReDownload;
			break;
		case RETRY_TYPE_TIMES:
			if( m_nRetryTimes > m_nRetryMax )
				return DOWNLOAD_RESULT_FAIL;
			m_nRetryTimes++;
		
			if( m_nRetryDelay > 0 )
				Sleep( m_nRetryDelay );
			goto ReDownload;
			break;
		default:
			return DOWNLOAD_RESULT_FAIL;
			break;
		}
		break;
	default:
		return DOWNLOAD_RESULT_FAIL;
		break;
	}

	if (m_dwDownloadSize == 0 /*|| m_dwHeaderSize == 0*/)
		return DOWNLOAD_RESULT_FAIL;

	if( !m_bForceDownload ) // 非强制下载，不检查Last-Modified
	{
		CFileStatus fileStatus;
		if (CFile::GetStatus(CString(m_strSavePath),fileStatus))
		{
			// 可能会存在1秒的误差
			if (( fileStatus.m_mtime - m_TimeLastModified <=2 && m_TimeLastModified-fileStatus.m_mtime<=2 ) && (DWORD)fileStatus.m_size == m_dwFileSize )
				return DOWNLOAD_RESULT_SAMEAS;
		}
	}
	CFile fileDown;
	if(! fileDown.Open(CString(m_strSavePath),CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite|CFile::shareDenyWrite) )
		return DOWNLOAD_RESULT_FAIL;	

	// 应该判断一下是否支持断点续传
	if( m_bSupportResume )
	{
		try
		{
			fileDown.SeekToEnd();
		}
		catch(CFileException* e)                                         
		{
		  e->Delete();
		  return DOWNLOAD_RESULT_FAIL;
		}	
	}

	// 获取的文件名
	//m_strFileName = m_strSavePath.Right(m_strSavePath.GetLength()-m_strSavePath.ReverseFind('\\')-1);
	int nSlash = m_strObject.ReverseFind(_T('/'));
	if (nSlash == -1)
		nSlash = m_strObject.ReverseFind(_T('\\'));
	if (nSlash != -1 && m_strObject.GetLength() > 1)
		m_strFileName = m_strObject.Right(m_strObject.GetLength() - nSlash - 1);
	else
		m_strFileName = m_strObject;

	if( bSendOnce && m_bNotify )
	{
		DOWNLOADSTATUS DownloadStatus;
		
		DownloadStatus.dwFileSize  = m_dwFileSize;
		DownloadStatus.strFileName = m_strFileName;
		DownloadStatus.dwFileDownloadedSize  = m_dwFileDownloadedSize;

		DownloadStatus.nStatusType = STATUS_TYPE_FILESIZE;
		::SendMessage(m_hNotifyWnd,m_nNotifyMessage,MSG_DOWNLOAD_STATUS,(LPARAM)&DownloadStatus);	

		DownloadStatus.nStatusType = STATUS_TYPE_FILENAME;
		::SendMessage(m_hNotifyWnd,m_nNotifyMessage,MSG_DOWNLOAD_STATUS,(LPARAM)&DownloadStatus);	
	
		DownloadStatus.nStatusType = STATUS_TYPE_FILEDOWNLOADEDSIZE;
		::SendMessage(m_hNotifyWnd,m_nNotifyMessage,MSG_DOWNLOAD_STATUS,(LPARAM)&DownloadStatus);	
		
		bSendOnce = FALSE;
	}

	m_dwDownloadedSize = 0;
	// 现在开始读取数据
	char szReadBuf[READ_BUFFER_SIZE+1];

	do
	{
		// 是否应该停止下载
		if (m_bStopDownload)
			return DOWNLOAD_RESULT_STOP;
		
		ZeroMemory(szReadBuf,READ_BUFFER_SIZE+1);
		int nRet = TE_BSocketGetData(m_pBSD,szReadBuf,READ_BUFFER_SIZE,m_dwReceiveTimeout);
		if (nRet <= 0)
		{
			fileDown.Close();
			m_nErrorCount++;
			goto ReDownload; //再次发送请求
		}

		// 将数据写入文件
		try
		{
			fileDown.Write(szReadBuf,nRet);
		}
		catch(CFileException* e)
		{
			e->Delete();
			fileDown.Close();
			goto ReDownload;
		}

		m_dwDownloadedSize		+= nRet;
		m_dwFileDownloadedSize	+= nRet;

		// 通知消息
		if( m_bNotify )
		{
			DOWNLOADSTATUS DownloadStatus;
			DownloadStatus.nStatusType			= STATUS_TYPE_FILEDOWNLOADEDSIZE;
			DownloadStatus.dwFileDownloadedSize = m_dwFileDownloadedSize;
			DownloadStatus.dwFileSize			= m_dwFileSize;
			DownloadStatus.strFileName			= m_strFileName;
			::SendMessage(m_hNotifyWnd,m_nNotifyMessage,MSG_DOWNLOAD_STATUS,(LPARAM)&DownloadStatus);	
		}
		
		if(m_proc)
		{
			(*m_proc)( m_dwFileSize, m_dwFileDownloadedSize+nFrom );
		}

	}while(m_dwDownloadedSize < m_dwDownloadSize);

	// 关闭文件
	fileDown.Close();
	
	//关闭SOCKET
	CloseSocket();

	// 文件改名
	//首先将已有的文件删除
/*	try
	{
		CFile::Remove(CString(m_strSavePath));
	}
	catch(CFileException *e)
	{
		e->Delete();
	}

	//再将新下载的文件改名
	try
	{
		CFile::Rename(CString(m_strTempSavePath),CString(m_strSavePath));
	}
	catch(CFileException *e)
	{
		e->Delete();
	}*/
	//再将新下载的文件的时间改回去
	CFileStatus fileStatus;
	CFile::GetStatus(CString(m_strSavePath),fileStatus);
	fileStatus.m_mtime = m_TimeLastModified;
	SetFileAttributesW(CStringW(m_strSavePath).GetBuffer(), FILE_ATTRIBUTE_NORMAL);
	CFile::SetStatus(CString(m_strSavePath),fileStatus);
	
	// 不再进行其他操作
	//m_bStopDownload = TRUE;

	::SendMessage(m_hNotifyWnd, m_nNotifyMessage, MSG_DOWNLOADED, 0);

	return DOWNLOAD_RESULT_SUCCESS;
}

UINT CHttpDownload::DownloadEx(LPCSTR lpszDownloadUrl, 
							   LPCTSTR lpszSavePath, 
							   long &lLength, 
							   char *pCookie, 
							   char *pReferer, 
							   long lFrom, 
							   long lTo, 
							   int nServerType
							   )
{
	LPCSTR lpszRequestHeader;

	if(!ParseURL(lpszDownloadUrl, m_strServer, m_strObject, m_nPort))
	{
		AfxMessageBox(_T(m_mapStringSet[31].c_str()));
		return DOWNLOAD_RESULT_FAIL;
	}
	lpszRequestHeader = FormatRequestHeader(m_strServer.GetBuffer(0), m_strObject.GetBuffer(0), 
		lLength, pCookie, pReferer,
		lFrom, lTo, nServerType);
	
	return DOWNLOAD_RESULT_SUCCESS;
}

const char *CHttpDownload::FormatRequestHeader(char *pServer,
											   char *pObject,
											   long &Length, 
											   char* pCookie/* =NULL */,
											   char *pReferer/* =NULL */, 
											   long nFrom/* =0 */,
											   long nTo/* =0 */, 
											   int nServerType/* =0 */
											   )
{
	int m_port = 80;
	char szPort[10];
	char szTemp[20];
	sprintf(szPort,"%d",m_port);
	memset(m_requestheader,'\0',1024);
	
	///第1行:方法,请求的路径,版本
	strcat(m_requestheader,"GET ");
	strcat(m_requestheader,pObject);
	strcat(m_requestheader," HTTP/1.1");
    strcat(m_requestheader,"\r\n");
	
	///第2行:主机
    strcat(m_requestheader,"Host:");
	strcat(m_requestheader,pServer);
    strcat(m_requestheader,"\r\n");
	
	///第3行:
	if(pReferer != NULL)
	{
		strcat(m_requestheader,"Referer:");
		strcat(m_requestheader,pReferer);
		strcat(m_requestheader,"\r\n");		
	}
	
	///第4行:接收的数据类型
    strcat(m_requestheader,"Accept:*/*");
    strcat(m_requestheader,"\r\n");
	
	///第5行:浏览器类型
    strcat(m_requestheader,"User-Agent:Mozilla/4.0 (compatible; MSIE 5.00; Windows 98)");
    strcat(m_requestheader,"\r\n");
	
	///第6行:连接设置,保持
	strcat(m_requestheader,"Connection:Keep-Alive");
	strcat(m_requestheader,"\r\n");
	
	///第7行:Cookie.
	if(pCookie != NULL)
	{
		strcat(m_requestheader,"Set Cookie:0");
		strcat(m_requestheader,pCookie);
		strcat(m_requestheader,"\r\n");
	}
	
	///第8行:请求的数据起始字节位置(断点续传的关键)
	if(nFrom > 0)
	{
		strcat(m_requestheader,"Range: bytes=");
		_ltoa(nFrom,szTemp,10);
		strcat(m_requestheader,szTemp);
		strcat(m_requestheader,"-");
		if(nTo > nFrom)
		{
			_ltoa(nTo,szTemp,10);
			strcat(m_requestheader,szTemp);
		}
		strcat(m_requestheader,"\r\n");
	}
	
	///最后一行:空行
	strcat(m_requestheader,"\r\n");
	
	///返回结果
	Length=strlen(m_requestheader);
	return m_requestheader;
}

// 发送请求
// 重定向的时候要加上Referer
UINT CHttpDownload::SendRequest(BOOL bHead /* = FALSE */, 
								UINT nFrom /* = 0 */, 
								UINT nTo /* = 0 */
								)
{
	CStringA strVerb;
	if( bHead )
		strVerb = _T("HEAD ");
	else
		strVerb = _T("GET ");

	while (TRUE)
	{
		CStringA			strSend,strAuth,strAddr,strHeader;
		BYTE			bAuth,bAtyp;
		DWORD			dwIP;
		SOCKSREPPACKET	pack;
	
		int				iStatus,nRet;;
		char			szReadBuf[1025];
		DWORD			dwContentLength,dwStatusCode;


		m_dwFileDownloadedSize = 0;
		m_dwDownloadSize	   = 0;

		///////////////////////////////////////
		// 目前的版本中，此信息并没有用
		m_strHeader		= _T("");
		m_dwHeaderSize	= 0;
		//////////////////////////////////////
		if (!CreateSocket())
			return SENDREQUEST_FAIL;
	
		if (m_bStopDownload)
			return SENDREQUEST_STOP;

		switch( m_nProxyType )
		{
		case PROXY_NONE:
			if( TE_ConnectEx(m_hSocket,m_strServer,m_nPort,m_dwConnectTimeout,TRUE) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;
			break;
		case PROXY_HTTPGET:
			if( TE_ConnectEx(m_hSocket,m_strProxyServer,m_nProxyPort,m_dwConnectTimeout,TRUE) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;
			break;
		case PROXY_SOCKS4A:
			dwIP = TE_GetIP(m_strServer,TRUE);
			if( dwIP == INADDR_NONE )
			{
				if( TE_ConnectEx(m_hSocket,m_strProxyServer,m_nProxyPort,m_dwConnectTimeout,TRUE) == SOCKET_ERROR )
					return SENDREQUEST_ERROR;
				
				if( SOP_SendSocks4aReq(m_hSocket,CMD_CONNECT,m_nPort,m_strServer,m_strProxyUsername,m_dwSendTimeout) == SOCKET_ERROR )
					return SENDREQUEST_ERROR;

				ZeroMemory(&pack,sizeof(SOCKSREPPACKET));
				if( SOP_RecvPacket(m_pBSD,&pack,PACKET_SOCKS4AREP,m_dwReceiveTimeout) == SOCKET_ERROR )
					return SENDREQUEST_ERROR;

				if( !SOP_IsSocksOK(&pack,PACKET_SOCKS4AREP) )
					return SENDREQUEST_ERROR;

				break;// NOTICE:如果本地能够解析域名，可以使用SOCKS4 Proxy
			}
		case PROXY_SOCKS4:
			// 必须要得到Proxy Server的IP地址(不能为域名)
			dwIP = TE_GetIP(m_strServer,TRUE);
			if( dwIP == INADDR_NONE )
				return SENDREQUEST_ERROR;
			if( TE_ConnectEx(m_hSocket,m_strProxyServer,m_nProxyPort,m_dwConnectTimeout,TRUE) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;
			if( SOP_SendSocks4Req(m_hSocket,CMD_CONNECT,m_nPort,dwIP,m_strProxyUsername,m_dwSendTimeout) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;
		
			ZeroMemory(&pack,sizeof(SOCKSREPPACKET));
			if( SOP_RecvPacket(m_pBSD,&pack,PACKET_SOCKS4REP,m_dwReceiveTimeout) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;
			
			if( !SOP_IsSocksOK(&pack,PACKET_SOCKS4REP) )
				return SENDREQUEST_ERROR;
			break;
		case PROXY_SOCKS5:
			if( TE_ConnectEx(m_hSocket,m_strProxyServer,m_nProxyPort,m_dwConnectTimeout,TRUE) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;

			if( m_bProxyAuthorization )
			{
				strAuth =  _T("");
				char c	= (char)AUTH_NONE;
				strAuth += c;
				c 		= (char)AUTH_PASSWD;
				strAuth += c;
				
			}
			else
			{
				char c	= (char)AUTH_NONE;
				strAuth =  _T("");
				strAuth += c;
			}
			bAuth =(BYTE)strAuth.GetLength();
			
			if( SOP_SendSocks5AuthReq(m_hSocket,bAuth,strAuth,m_dwSendTimeout) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;

			ZeroMemory(&pack,sizeof(SOCKSREPPACKET));
			if( SOP_RecvPacket(m_pBSD,&pack,PACKET_SOCKS5AUTHREP,m_dwReceiveTimeout) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;

			if( !SOP_IsSocksOK(&pack,PACKET_SOCKS5AUTHREP) )
				return SENDREQUEST_ERROR;

			switch( pack.socks5AuthRep.bAuth )
			{
			case AUTH_NONE:
				break;
			case AUTH_PASSWD:
				if( !m_bProxyAuthorization )
					return SENDREQUEST_FAIL;
				if( SOP_SendSocks5AuthPasswdReq(m_hSocket,m_strProxyUsername,m_strProxyPassword,m_dwSendTimeout) == SOCKET_ERROR )
					return SENDREQUEST_ERROR;

				ZeroMemory(&pack,sizeof(SOCKSREPPACKET));
				if( SOP_RecvPacket(m_pBSD,&pack,PACKET_SOCKS5AUTHPASSWDREP,m_dwReceiveTimeout) == SOCKET_ERROR )
					return SENDREQUEST_ERROR;

				if( !SOP_IsSocksOK(&pack,PACKET_SOCKS5AUTHPASSWDREP) )
					return SENDREQUEST_ERROR;
				break;
			case AUTH_GSSAPI:
			case AUTH_CHAP:
			case AUTH_UNKNOWN:
			default:
				return SENDREQUEST_FAIL;
				break;
			}

			dwIP = TE_GetIP(m_strServer,TRUE);
			if( dwIP != INADDR_NONE )
			{
				bAtyp = ATYP_IPV4ADDR;
				strAddr = _T("");
				// 转换字节序
				dwIP = htonl(dwIP);
				strAddr += (char)( (dwIP>>24) &0x000000ff); 
				strAddr += (char)( (dwIP>>16) &0x000000ff); 
				strAddr += (char)( (dwIP>>8 ) &0x000000ff); 
				strAddr += (char)( dwIP &0x000000ff); 

			}
			else
			{
				bAtyp = ATYP_HOSTNAME;
				char c = (char)m_strServer.GetLength();
				strAddr  = _T("");
				strAddr += c;
				strAddr += m_strServer;
			}
			if( SOP_SendSocks5Req(m_hSocket,CMD_CONNECT,bAtyp,strAddr,m_nPort,m_dwSendTimeout) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;

			ZeroMemory(&pack,sizeof(SOCKSREPPACKET));
			if( SOP_RecvPacket(m_pBSD,&pack,PACKET_SOCKS5REP,m_dwReceiveTimeout) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;

			if( !SOP_IsSocksOK(&pack,PACKET_SOCKS5REP) )
				return SENDREQUEST_ERROR;

			break;
		case PROXY_HTTPCONNECT:
		default:
			return SENDREQUEST_FAIL;
			break;
		}

		if (m_bStopDownload)
			return SENDREQUEST_STOP;
	
		if( m_nProxyType == PROXY_HTTPGET )
		{
			strSend  = strVerb  + m_strDownloadUrl + " HTTP/1.1\r\n";
			if( m_bProxyAuthorization )
			{
				strAuth = _T("");
				Base64Encode(m_strProxyUsername+":"+m_strProxyPassword,strAuth);
				strSend += "Proxy-Authorization: Basic "+strAuth+"\r\n";
			}
		}
		else	// No Proxy or not a HTTP_GET Proxy
			strSend  = strVerb  + m_strObject + " HTTP/1.1\r\n";
		
		if( m_bAuthorization )
		{
			strAuth = _T("");
			Base64Encode(m_strUsername+":"+m_strPassword,strAuth);
			strSend += "Authorization: Basic "+strAuth+"\r\n";
		}

		strSend += "Host: " + m_strServer + "\r\n";
		strSend += "Accept: */*\r\n";
		strSend += "Pragma: no-cache\r\n"; 
		strSend += "Cache-Control: no-cache\r\n";
		strSend += "User-Agent: "+m_strUserAgent+"\r\n";
		if( !m_strReferer.IsEmpty() )
			strSend += "Referer: "+m_strReferer+"\r\n";
		strSend += "Connection: close\r\n";

		// 查看文件已经下载的长度
		CFileStatus fileDownStatus;
		CStringA		strRange;
		strRange.Empty();

		if(nFrom >= 0)
		{
			strRange.Format("Range: bytes=%d-", nFrom);
			CStringA strTemp1;
			if(nTo > nFrom)
			{
				strTemp1.Format("%d", nTo);
				strRange += strTemp1;
			}
			strRange += "\r\n";
		}
		else if (CFile::GetStatus(CString(m_strTempSavePath),fileDownStatus) && !m_bForceDownload )
		{
			m_dwFileDownloadedSize = static_cast<DWORD>(fileDownStatus.m_size);
			if (m_dwFileDownloadedSize > 0)
			{
				strRange.Format("Range: bytes=%d-\r\n",m_dwFileDownloadedSize );
			}
		}

		strSend += strRange;
		//必须要加一个空行，否则Http服务器将不会应答
		strSend += "\r\n";

		//发送请求
		nRet = TE_Send(m_hSocket,strSend,strSend.GetLength(),m_dwSendTimeout);
		if( nRet < strSend.GetLength() )
		{
			if ( TE_GetLastError() == WSAETIMEDOUT)	// 超时
				continue;
			else	// 其他错误，可能是网络断了，等待一段时间后重试
				return SENDREQUEST_ERROR;
		}

		if (m_bStopDownload)
			return SENDREQUEST_STOP;

		strHeader.Empty();
		while( TRUE )
		{
			ZeroMemory(szReadBuf,1025);
			if( TE_BSocketGetStringEx(m_pBSD,szReadBuf,1024,&iStatus,m_dwReceiveTimeout) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;
			
			if( szReadBuf[0] == '\0' ) // We have encountered "\r\n\r\n"
				break; 

			strHeader += szReadBuf;
			if( iStatus == 0)
				strHeader += "\r\n";
		}
		
		///////////////////////////////////////
		// 目前的版本中，此信息并没有用
		m_strHeader		= strHeader;
		m_dwHeaderSize	= m_strHeader.GetLength();
		//////////////////////////////////////
				
		nRet = GetInfo(strHeader,dwContentLength,dwStatusCode,m_TimeLastModified);
		switch ( nRet )
		{
		case HTTP_FAIL:
			return SENDREQUEST_FAIL;
			break;
		case HTTP_ERROR:
			return SENDREQUEST_ERROR;
			break;
		case HTTP_REDIRECT:
			continue;
			break;
		case HTTP_OK:
			m_dwDownloadSize = dwContentLength;
			// 应该判断一下服务器是否支持断点续传
			if( strRange.IsEmpty() )
				m_dwFileSize = dwContentLength; // 整个文件的长度
			else
			{
				if ( dwStatusCode == 206 )	//支持断点续传
				{
					m_dwFileSize = m_dwFileDownloadedSize +dwContentLength;
					m_bSupportResume = TRUE;
				}
				else						//不支持断点续传
				{
					m_bSupportResume = FALSE;
					m_dwFileDownloadedSize	= 0; //不支持断点续传，此值要设为0
					m_dwFileSize = dwContentLength;
				}
			}
			return SENDREQUEST_SUCCESS;
			break;
		default:
			return SENDREQUEST_FAIL;
			break;
		}

	}// WHILE LOOP

	return SENDREQUEST_SUCCESS;
}

UINT CHttpDownload::SendRequestEx(LPCTSTR lpszRequestHeader /* = NULL */)
{
	if(!lpszRequestHeader)
	{
		return SENDREQUEST_FAIL;
	}
	
	while (TRUE) 
	{
		CStringA			strSend,strAuth,strAddr,strHeader;
		BYTE			bAuth,bAtyp;
		DWORD			dwIP;
		SOCKSREPPACKET	pack;
		
		int				iStatus,nRet;;
		char			szReadBuf[1025];
		DWORD			dwContentLength,dwStatusCode;
		
		
		m_dwFileDownloadedSize = 0;
		m_dwDownloadSize	   = 0;
		
		if (!CreateSocket())
			return SENDREQUEST_FAIL;
	
		if (m_bStopDownload)
			return SENDREQUEST_STOP;

		switch( m_nProxyType )
		{
		case PROXY_NONE:
			if( TE_ConnectEx(m_hSocket,m_strServer,m_nPort,m_dwConnectTimeout,TRUE) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;
			break;
		case PROXY_HTTPGET:
			if( TE_ConnectEx(m_hSocket,m_strProxyServer,m_nProxyPort,m_dwConnectTimeout,TRUE) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;
			break;
		case PROXY_SOCKS4A:
			dwIP = TE_GetIP(m_strServer,TRUE);
			if( dwIP == INADDR_NONE )
			{
				if( TE_ConnectEx(m_hSocket,m_strProxyServer,m_nProxyPort,m_dwConnectTimeout,TRUE) == SOCKET_ERROR )
					return SENDREQUEST_ERROR;
				
				if( SOP_SendSocks4aReq(m_hSocket,CMD_CONNECT,m_nPort,m_strServer,m_strProxyUsername,m_dwSendTimeout) == SOCKET_ERROR )
					return SENDREQUEST_ERROR;

				ZeroMemory(&pack,sizeof(SOCKSREPPACKET));
				if( SOP_RecvPacket(m_pBSD,&pack,PACKET_SOCKS4AREP,m_dwReceiveTimeout) == SOCKET_ERROR )
					return SENDREQUEST_ERROR;

				if( !SOP_IsSocksOK(&pack,PACKET_SOCKS4AREP) )
					return SENDREQUEST_ERROR;

				break;// NOTICE:如果本地能够解析域名，可以使用SOCKS4 Proxy
			}
		case PROXY_SOCKS4:
			// 必须要得到Proxy Server的IP地址(不能为域名)
			dwIP = TE_GetIP(m_strServer,TRUE);
			if( dwIP == INADDR_NONE )
				return SENDREQUEST_ERROR;
			if( TE_ConnectEx(m_hSocket,m_strProxyServer,m_nProxyPort,m_dwConnectTimeout,TRUE) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;
			if( SOP_SendSocks4Req(m_hSocket,CMD_CONNECT,m_nPort,dwIP,m_strProxyUsername,m_dwSendTimeout) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;
		
			ZeroMemory(&pack,sizeof(SOCKSREPPACKET));
			if( SOP_RecvPacket(m_pBSD,&pack,PACKET_SOCKS4REP,m_dwReceiveTimeout) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;
			
			if( !SOP_IsSocksOK(&pack,PACKET_SOCKS4REP) )
				return SENDREQUEST_ERROR;
			break;
		case PROXY_SOCKS5:
			if( TE_ConnectEx(m_hSocket,m_strProxyServer,m_nProxyPort,m_dwConnectTimeout,TRUE) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;

			if( m_bProxyAuthorization )
			{
				strAuth =  _T("");
				char c	= (char)AUTH_NONE;
				strAuth += c;
				c 		= (char)AUTH_PASSWD;
				strAuth += c;
				
			}
			else
			{
				char c	= (char)AUTH_NONE;
				strAuth =  _T("");
				strAuth += c;
			}
			bAuth =(BYTE)strAuth.GetLength();
			
			if( SOP_SendSocks5AuthReq(m_hSocket,bAuth,strAuth,m_dwSendTimeout) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;

			ZeroMemory(&pack,sizeof(SOCKSREPPACKET));
			if( SOP_RecvPacket(m_pBSD,&pack,PACKET_SOCKS5AUTHREP,m_dwReceiveTimeout) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;

			if( !SOP_IsSocksOK(&pack,PACKET_SOCKS5AUTHREP) )
				return SENDREQUEST_ERROR;

			switch( pack.socks5AuthRep.bAuth )
			{
			case AUTH_NONE:
				break;
			case AUTH_PASSWD:
				if( !m_bProxyAuthorization )
					return SENDREQUEST_FAIL;
				if( SOP_SendSocks5AuthPasswdReq(m_hSocket,m_strProxyUsername,m_strProxyPassword,m_dwSendTimeout) == SOCKET_ERROR )
					return SENDREQUEST_ERROR;

				ZeroMemory(&pack,sizeof(SOCKSREPPACKET));
				if( SOP_RecvPacket(m_pBSD,&pack,PACKET_SOCKS5AUTHPASSWDREP,m_dwReceiveTimeout) == SOCKET_ERROR )
					return SENDREQUEST_ERROR;

				if( !SOP_IsSocksOK(&pack,PACKET_SOCKS5AUTHPASSWDREP) )
					return SENDREQUEST_ERROR;
				break;
			case AUTH_GSSAPI:
			case AUTH_CHAP:
			case AUTH_UNKNOWN:
			default:
				return SENDREQUEST_FAIL;
				break;
			}

			dwIP = TE_GetIP(m_strServer,TRUE);
			if( dwIP != INADDR_NONE )
			{
				bAtyp = ATYP_IPV4ADDR;
				strAddr = _T("");
				// 转换字节序
				dwIP = htonl(dwIP);
				strAddr += (char)( (dwIP>>24) &0x000000ff); 
				strAddr += (char)( (dwIP>>16) &0x000000ff); 
				strAddr += (char)( (dwIP>>8 ) &0x000000ff); 
				strAddr += (char)( dwIP &0x000000ff); 

			}
			else
			{
				bAtyp = ATYP_HOSTNAME;
				char c = (char)m_strServer.GetLength();
				strAddr  = _T("");
				strAddr += c;
				strAddr += m_strServer;
			}
			if( SOP_SendSocks5Req(m_hSocket,CMD_CONNECT,bAtyp,strAddr,m_nPort,m_dwSendTimeout) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;

			ZeroMemory(&pack,sizeof(SOCKSREPPACKET));
			if( SOP_RecvPacket(m_pBSD,&pack,PACKET_SOCKS5REP,m_dwReceiveTimeout) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;

			if( !SOP_IsSocksOK(&pack,PACKET_SOCKS5REP) )
				return SENDREQUEST_ERROR;

			break;
		case PROXY_HTTPCONNECT:
		default:
			return SENDREQUEST_FAIL;
			break;
		}

		if (m_bStopDownload)
			return SENDREQUEST_STOP;
	
		if( m_nProxyType == PROXY_HTTPGET )
		{
			strSend  = "GET "  + m_strDownloadUrl + " HTTP/1.1\r\n";
			if( m_bProxyAuthorization )
			{
				strAuth = _T("");
				Base64Encode(m_strProxyUsername+":"+m_strProxyPassword,strAuth);
				strSend += "Proxy-Authorization: Basic "+strAuth+"\r\n";
			}
		}
		else	// No Proxy or not a HTTP_GET Proxy
			strSend  = "HEAD "  + m_strObject + " HTTP/1.1\r\n";
		
		if( m_bAuthorization )
		{
			strAuth = _T("");
			Base64Encode(m_strUsername+":"+m_strPassword,strAuth);
			strSend += "Authorization: Basic "+strAuth+"\r\n";
		}

		strSend += "Host: " + m_strServer + "\r\n";
		strSend += "Accept: */*\r\n";
		strSend += "Pragma: no-cache\r\n"; 
		strSend += "Cache-Control: no-cache\r\n";
		strSend += "User-Agent: "+m_strUserAgent+"\r\n";
		if( !m_strReferer.IsEmpty() )
			strSend += "Referer: "+m_strReferer+"\r\n";
		strSend += "Connection: close\r\n";

		// 查看文件已经下载的长度
		CFileStatus fileDownStatus;
		CStringA		strRange;
		strRange.Empty();
		if (CFile::GetStatus(CString(m_strTempSavePath),fileDownStatus) && !m_bForceDownload )
		{
			m_dwFileDownloadedSize = static_cast<DWORD>(fileDownStatus.m_size);
			if (m_dwFileDownloadedSize > 0)
			{
				strRange.Format("Range: bytes=%d-\r\n",m_dwFileDownloadedSize );
			}
		}
		strSend += strRange;
		//必须要加一个空行，否则Http服务器将不会应答
		strSend += _T("\r\n");

		//发送请求
		nRet = TE_Send(m_hSocket,strSend,strSend.GetLength(),m_dwSendTimeout);
		if( nRet < strSend.GetLength() )
		{
			if ( TE_GetLastError() == WSAETIMEDOUT)	// 超时
				continue;
			else	// 其他错误，可能是网络断了，等待一段时间后重试
				return SENDREQUEST_ERROR;
		}

		if (m_bStopDownload)
			return SENDREQUEST_STOP;

		strHeader.Empty();
		while( TRUE )
		{
			ZeroMemory(szReadBuf,1025);
			if( TE_BSocketGetStringEx(m_pBSD,szReadBuf,1024,&iStatus,m_dwReceiveTimeout) == SOCKET_ERROR )
				return SENDREQUEST_ERROR;
			
			if( szReadBuf[0] == '\0' ) // We have encountered "\r\n\r\n"
				break; 

			strHeader += szReadBuf;
			if( iStatus == 0)
				strHeader += "\r\n";
		}
		
		///////////////////////////////////////
		// 目前的版本中，此信息并没有用
		m_strHeader		= strHeader;
		m_dwHeaderSize	= m_strHeader.GetLength();
		//////////////////////////////////////
				
		nRet = GetInfo(strHeader,dwContentLength,dwStatusCode,m_TimeLastModified);
		switch ( nRet )
		{
		case HTTP_FAIL:
			return SENDREQUEST_FAIL;
			break;
		case HTTP_ERROR:
			return SENDREQUEST_ERROR;
			break;
		case HTTP_REDIRECT:
			continue;
			break;
		case HTTP_OK:
			m_dwDownloadSize = dwContentLength;
			// 应该判断一下服务器是否支持断点续传
			if( strRange.IsEmpty() )
				m_dwFileSize = dwContentLength; // 整个文件的长度
			else
			{
				if ( dwStatusCode == 206 )	//支持断点续传
				{
					m_dwFileSize = m_dwFileDownloadedSize +dwContentLength;
					m_bSupportResume = TRUE;
				}
				else						//不支持断点续传
				{
					m_bSupportResume = FALSE;
					m_dwFileDownloadedSize	= 0; //不支持断点续传，此值要设为0
					m_dwFileSize = dwContentLength;
				}
			}
			return SENDREQUEST_SUCCESS;
			break;
		default:
			return SENDREQUEST_FAIL;
			break;
		}
	}
	
	return SENDREQUEST_SUCCESS;
}

// 设置代理及代理认证方式
void CHttpDownload::SetProxy(LPCTSTR lpszProxyServer, USHORT nProxyPort, BOOL bProxy, BOOL bProxyAuthorization, LPCTSTR lpszProxyUsername, LPCTSTR lpszProxyPassword,UINT nProxyType /*= PROXY_HTTPGET*/)
{
	if( bProxy && lpszProxyServer != NULL)
	{
		m_bProxy			= TRUE;
		m_strProxyServer	= lpszProxyServer;
		m_nProxyPort		= nProxyPort;
		m_nProxyType		= nProxyType;

		if( bProxyAuthorization && lpszProxyUsername != NULL)
		{
			m_bProxyAuthorization	= TRUE;
			m_strProxyUsername		= lpszProxyUsername;
			m_strProxyPassword		= lpszProxyPassword;
		}
		else
		{
			m_bProxyAuthorization	= FALSE;
			m_strProxyUsername		= _T("");
			m_strProxyPassword		= _T("");
		}
	}
	else
	{
		m_bProxy				= FALSE;
		m_bProxyAuthorization	= FALSE;
		m_nProxyPort			= 0;
		m_nProxyType			= PROXY_NONE;
		m_strProxyServer		= _T("");
		m_strProxyUsername		= _T("");
		m_strProxyPassword		= _T("");
	}
}


// 设置WWW认证信息
void CHttpDownload::SetAuthorization(LPCTSTR lpszUsername, LPCTSTR lpszPassword, BOOL bAuthorization)
{
	if( bAuthorization && lpszUsername != NULL )
	{
		m_bAuthorization = TRUE;
		m_strUsername	 = lpszUsername;
		m_strPassword	 = lpszPassword;
	}
	else
	{
		m_bAuthorization = FALSE;
		m_strUsername	 = _T("");
		m_strPassword	 = _T("");
	}
}

// 设置是否需要发送消息给调用窗口
void CHttpDownload::SetNotifyWnd(HWND hNotifyWnd, UINT nNotifyMsg, BOOL bNotify)
{
	if( bNotify && (hNotifyWnd != NULL) && ::IsWindow(hNotifyWnd) )
	{
		m_bNotify	 = TRUE;
		m_hNotifyWnd = hNotifyWnd;
		m_nNotifyMessage = nNotifyMsg;
	}
	else
	{
		m_bNotify	 = FALSE;
		m_hNotifyWnd = NULL;
		m_nNotifyMessage = 0;
	}
}

// 设置超时
void CHttpDownload::SetTimeout(DWORD dwSendTimeout, DWORD dwReceiveTimeout, DWORD dwConnectTimeout)
{
	if( dwSendTimeout > 0 )
		m_dwSendTimeout = dwSendTimeout;
	
	if( dwReceiveTimeout > 0 )
		m_dwReceiveTimeout = dwReceiveTimeout;

	if( dwConnectTimeout > 0 )
		m_dwConnectTimeout = dwConnectTimeout;


}

// 设置UserAgent
void CHttpDownload::SetUserAgent(LPCTSTR lpszUserAgent)
{
	m_strUserAgent = lpszUserAgent;	
	if( m_strUserAgent.IsEmpty())
		m_strUserAgent = _T("HttpDownload/2.0");
}

// 设置Referer
void CHttpDownload::SetReferer(LPCTSTR lpszReferer)
{
	if( lpszReferer != NULL )
		m_strReferer = lpszReferer;
	else
		m_strReferer = _T("");
}

// 设置重试的机制
// nRetryType = 0  不重试					RETRY_TYPE_NONE
// nRetryType = 1  重试一定次数				RETRY_TYPE_TIMES
// nRetryType = 2  永远重试(可能陷入死循环)	RETRY_TYPE_ALWAYS
void CHttpDownload::SetRetry(UINT nRetryType, UINT nRetryDelay, UINT nRetryMax)
{
	m_nRetryType  = nRetryType;
	m_nRetryDelay = nRetryDelay;
	m_nRetryMax	  = nRetryMax;
	
	// 检查一下m_nRetryMax,如果为0，设为缺省值
	if( (RETRY_TYPE_TIMES == m_nRetryType) && (0 == m_nRetryMax) )
		m_nRetryMax = DEFAULT_RETRY_MAX;
}

// 获取下载文件的状态
BOOL CHttpDownload::GetDownloadFileStatus(LPCTSTR lpszDownloadUrl, DWORD &dwFileSize, CTime &FileTime)
{
	// 检验要下载的URL是否为空
	m_strDownloadUrl = lpszDownloadUrl;
	m_strDownloadUrl.TrimLeft();
	m_strDownloadUrl.TrimRight();
	if( m_strDownloadUrl.IsEmpty() )
		return FALSE;

	// 检验要下载的URL是否有效
	if ( !ParseURL(m_strDownloadUrl, m_strServer, m_strObject, m_nPort))
	{
		// 在前面加上"http://"再试
		m_strDownloadUrl = _T("http://") + m_strDownloadUrl;
		if ( !ParseURL(m_strDownloadUrl, m_strServer, m_strObject, m_nPort) )
		{
			TRACE(_T("Failed to parse the URL: %s\n"), m_strDownloadUrl);
			return FALSE;
		}
	}

	m_strTempSavePath	= "|";
	m_bStopDownload		= FALSE;

	if ( SendRequest(TRUE) !=  SENDREQUEST_SUCCESS )
		return FALSE;

	dwFileSize  = m_dwDownloadSize;
	FileTime	= m_TimeLastModified;

	return TRUE;
}


// 从URL里面拆分出Server和Object来
BOOL CHttpDownload::ParseURL(LPCSTR lpszURL, CStringA &strServer, CStringA &strObject,USHORT& nPort)
{
	CStringA strURL(lpszURL);
	strURL.TrimLeft();
	strURL.TrimRight();
	strURL.Replace(" ", "%20");
	// 清除数据
	strServer = _T("");
	strObject = _T("");
	nPort	  = 0;

	int nPos = strURL.Find("://");
	if( nPos == -1 )
		return FALSE;

	// 进一步验证是否为http://
	CStringA strTemp = strURL.Left( nPos+strlen("://") );
	strTemp.MakeLower();
	if( strTemp.Compare("http://") != 0 )
		return FALSE;

	strURL = strURL.Mid( strTemp.GetLength() );
	nPos = strURL.Find(_T('/'));
	if ( nPos == -1 )
		return FALSE;

	strObject = strURL.Mid(nPos);
	strTemp   = strURL.Left(nPos);
	
	///////////////////////////////////////////////////////////////
	/// 注意：并没有考虑URL中有用户名和口令的情形和最后有#的情形
	/// 例如：http://abc@def:www.yahoo.com:81/index.html#link1
	/// 
	//////////////////////////////////////////////////////////////

	// 查找是否有端口号
	nPos = strTemp.Find(":");
	if( nPos == -1 )
	{
		strServer = strTemp;
		nPort	  = DEFAULT_HTTP_PORT;
	}
	else
	{
		strServer = strTemp.Left( nPos );
		strTemp	  = strTemp.Mid( nPos+1 );
		nPort	  = (USHORT)atoi(strTemp);
	}
	return TRUE;
}

// 从返回到头里获得必要的信息
UINT CHttpDownload::GetInfo(LPCSTR lpszHeader, DWORD &dwContentLength, DWORD &dwStatusCode, CTime &TimeLastModified)
{
	dwContentLength = 0;
	dwStatusCode	= 0;
	TimeLastModified= CTime::GetCurrentTime();

	CStringA strHeader = lpszHeader;
	strHeader.MakeLower();

	//拆分出HTTP应答的头信息的第一行
	int nPos = strHeader.Find("\r\n");
	if (nPos == -1)
		return HTTP_FAIL;
	CStringA strFirstLine = strHeader.Left(nPos);

	// 获得返回码: Status Code
	strFirstLine.TrimLeft();
	strFirstLine.TrimRight();
	nPos = strFirstLine.Find(' ');
	if( nPos == -1 )
		return HTTP_FAIL;
	strFirstLine = strFirstLine.Mid(nPos+1);
	nPos = strFirstLine.Find(' ');
	if( nPos == -1 )
		return HTTP_FAIL;
	strFirstLine = strFirstLine.Left(nPos);
	dwStatusCode = (DWORD)atoi(strFirstLine);
	
	// 检查返回码
	if( dwStatusCode >= 300 && dwStatusCode < 400 ) //首先检测一下服务器的应答是否为重定向
	{
		nPos = strHeader.Find("location:");
		if (nPos == -1)
			return HTTP_FAIL;

		CStringA strRedirectFileName = strHeader.Mid(nPos + strlen("location:"));
		nPos = strRedirectFileName.Find("\r\n");
		if (nPos == -1)
			return HTTP_FAIL;

		strRedirectFileName = strRedirectFileName.Left(nPos);
		strRedirectFileName.TrimLeft();
		strRedirectFileName.TrimRight();
		
		// 设置Referer
		m_strReferer = m_strDownloadUrl;

		// 判断是否重定向到其他的服务器
		nPos = strRedirectFileName.Find("http://");
		if( nPos != -1 )
		{
			m_strDownloadUrl = strRedirectFileName;
			// 检验要下载的URL是否有效
			if ( !ParseURL(m_strDownloadUrl, m_strServer, m_strObject, m_nPort))
				return HTTP_FAIL;
			return HTTP_REDIRECT;
		}

		// 重定向到本服务器的其他地方
		strRedirectFileName.Replace("\\", "/");
		
		// 是相对于根目录
		if( strRedirectFileName[0] == '/' )
		{
			m_strObject = strRedirectFileName;
			return HTTP_REDIRECT;
		}
		
		// 是相对当前目录
		int nParentDirCount = 0;
		nPos = strRedirectFileName.Find("../");
		while (nPos != -1)
		{
			strRedirectFileName = strRedirectFileName.Mid(nPos+3);
			nParentDirCount++;
			nPos = strRedirectFileName.Find("../");
		}
		for (int i=0; i<=nParentDirCount; i++)
		{
			nPos = m_strDownloadUrl.ReverseFind('/');
			if (nPos != -1)
				m_strDownloadUrl = m_strDownloadUrl.Left(nPos);
		}
		m_strDownloadUrl = m_strDownloadUrl+_T("/")+strRedirectFileName;

		if ( !ParseURL(m_strDownloadUrl, m_strServer, m_strObject, m_nPort))
			return HTTP_FAIL;
		return HTTP_REDIRECT;
	}

	// 服务器错误，可以重试
	if( dwStatusCode >=500 )
		return HTTP_ERROR;

	// 客户端错误，重试无用
	if( dwStatusCode >=400 && dwStatusCode <500 )
		return HTTP_FAIL;
		
	// 获取ContentLength
	nPos = strHeader.Find("content-length:");
	if (nPos == -1)
		return HTTP_FAIL;

	CStringA strDownFileLen = strHeader.Mid(nPos + strlen("content-length:"));	
	nPos = strDownFileLen.Find("\r\n");
	if (nPos == -1)
		return HTTP_FAIL;

	strDownFileLen = strDownFileLen.Left(nPos);	
	strDownFileLen.TrimLeft();
	strDownFileLen.TrimRight();

	// Content-Length:
	dwContentLength = (DWORD) atoi(strDownFileLen);

	// 获取Last-Modified:
	nPos = strHeader.Find("last-modified:");
	if (nPos != -1)
	{
		CStringA strTime = strHeader.Mid(nPos + strlen("last-modified:"));
		nPos = strTime.Find("\r\n");
		if (nPos != -1)
		{
			strTime = strTime.Left(nPos);
			strTime.TrimLeft();
			strTime.TrimRight();
			TimeLastModified = GetTime(strTime);
		}
	}
	return HTTP_OK;
}

// 将字符串转化成时间
CTime CHttpDownload::GetTime(LPCSTR lpszTime)
{
	int nDay,nMonth,nYear,nHour,nMinute,nSecond;

	CStringA strTime = lpszTime;
	int nPos = strTime.Find(_T(','));
	if (nPos != -1)
	{
		strTime = strTime.Mid(nPos+1);
		strTime.TrimLeft();

		CStringA strDay,strMonth,strYear,strHour,strMinute,strSecond;
		CStringA strAllMonth = _T("jan,feb,mar,apr,may,jan,jul,aug,sep,oct,nov,dec");
		strDay = strTime.Left(2);
		nDay = atoi(strDay);
		strMonth = strTime.Mid(3,3);
		strMonth.MakeLower();
		nPos = strAllMonth.Find(strMonth);
		if (nPos != -1)
		{
			strMonth.Format("%d", ((nPos/4)+1));
			nMonth = atoi(strMonth);
		}
		else
			nMonth = 1;
		strTime = strTime.Mid(6);
		strTime.TrimLeft();
		nPos = strTime.FindOneOf(" \t");
		if (nPos != -1)
		{
			strYear = strTime.Left(nPos);
			nYear = atoi(strYear);
		}
		else
			nYear = 2000;
		strTime = strTime.Mid(nPos+1);
		strHour = strTime.Left(2);
		nHour = atoi(strHour);
		strMinute = strTime.Mid(3,2);
		nMinute = atoi(strMinute);
		strSecond = strTime.Mid(6,2);
		nSecond = atoi(strSecond);
	}
	
	CTime time(nYear,nMonth,nDay,nHour,nMinute,nSecond);
	return time;
}


// 停止下载
void CHttpDownload::StopDownload()
{
	m_bStopDownload = TRUE;
}


// STATIC BASE64解码
int CHttpDownload::Base64Decode(LPCSTR lpszDecoding, CStringA &strDecoded)
{
	int nIndex =0;
	int nDigit;
    int nDecode[ 256 ];
	int nSize;
	int nNumBits = 6;

	if( lpszDecoding == NULL )
		return 0;
	
	if( ( nSize = strlen(lpszDecoding) ) == 0 )
		return 0;

	// Build Decode Table
	for( int i = 0; i < 256; i++ ) 
		nDecode[i] = -2; // Illegal digit
	for(int i=0; i < 64; i++ )
	{
		nDecode[ m_strBase64TAB[ i ] ] = i;
		nDecode[ '=' ] = -1; 
    }

	// Clear the output buffer
	strDecoded = _T("");
	long lBitsStorage  =0;
	int nBitsRemaining = 0;
	int nScratch = 0;
	UCHAR c;
	
    int i;
	// Decode the Input
	for( nIndex = 0, i = 0; nIndex < nSize; nIndex++ )
	{
		c = lpszDecoding[ nIndex ];

		// 忽略所有不合法的字符
		if( c> 0x7F)
			continue;

		nDigit = nDecode[c];
		if( nDigit >= 0 ) 
		{
			lBitsStorage = (lBitsStorage << nNumBits) | (nDigit & 0x3F);
			nBitsRemaining += nNumBits;
			while( nBitsRemaining > 7 ) 
			{
				nScratch = lBitsStorage >> (nBitsRemaining - 8);
				strDecoded += (char)(nScratch & 0xFF);
				i++;
				nBitsRemaining -= 8;
			}
		}
    }	

	return strDecoded.GetLength();


}

// STATIC BASE64编码
int CHttpDownload::Base64Encode(LPCSTR lpszEncoding, CStringA &strEncoded)
{
	int nDigit;
	int nNumBits = 6;
	int nIndex = 0;
	int nInputSize;

	strEncoded = _T( "" );
	if( lpszEncoding == NULL )
		return 0;

	if( ( nInputSize = strlen(lpszEncoding) ) == 0 )
		return 0;

	int nBitsRemaining = 0;
	long lBitsStorage	=0;
	long lScratch		=0;
	int nBits;
	UCHAR c;

	while( nNumBits > 0 )
	{
		while( ( nBitsRemaining < nNumBits ) &&  ( nIndex < nInputSize ) ) 
		{
			c = lpszEncoding[ nIndex++ ];
			lBitsStorage <<= 8;
			lBitsStorage |= (c & 0xff);
			nBitsRemaining += 8;
		}
		if( nBitsRemaining < nNumBits ) 
		{
			lScratch = lBitsStorage << ( nNumBits - nBitsRemaining );
			nBits    = nBitsRemaining;
			nBitsRemaining = 0;
		}	 
		else 
		{
			lScratch = lBitsStorage >> ( nBitsRemaining - nNumBits );
			nBits	 = nNumBits;
			nBitsRemaining -= nNumBits;
		}
		nDigit = (int)(lScratch & m_nBase64Mask[nNumBits]);
		nNumBits = nBits;
		if( nNumBits <=0 )
			break;
		
		strEncoded += m_strBase64TAB[ nDigit ];
	}
	// Pad with '=' as per RFC 1521
	while( strEncoded.GetLength() % 4 != 0 )
		strEncoded += '=';

	return strEncoded.GetLength();

}

