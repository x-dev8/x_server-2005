// HttpDownload.h: interface for the CHttpDownload class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTTPDOWNLOAD_H__11AB7F1F_62EA_47FC_8B2D_B2E3929E2861__INCLUDED_)
#define AFX_HTTPDOWNLOAD_H__11AB7F1F_62EA_47FC_8B2D_B2E3929E2861__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <TCHAR.H>
#include <string>

#include "DownLoad.h"
using std::string;



class CHttpDownload  :public IDownLoad
{
public:
	CHttpDownload();
	virtual ~CHttpDownload();

public:
	BOOL		Init();
	BOOL		ShutDown();
	// 静态函数，用于64编码、解码
	static int Base64Encode( LPCSTR lpszEncoding, CStringA& strEncoded );
	static int Base64Decode( LPCSTR lpszDecoding, CStringA& strDecoded );
	
	// 下载函数
	static UINT RunThread(LPVOID lpArg);

	DownLoadProc m_proc;
	void SetCallBackDownProc(const DownLoadProc proc)
	{
		m_proc = proc;
	}
	// DWONLOAD函数
	void SetAuthorization(LPCTSTR lpszUsername,LPCTSTR lpszPassword,BOOL bAuthorization = TRUE );
	void SetReferer(LPCTSTR lpszReferer);
	void SetUserAgent(LPCTSTR lpszUserAgent);
	void SetTimeout(DWORD dwSendTimeout,DWORD dwReceiveTimeout,DWORD dwConnectTimeout);
	void SetRetry(UINT nRetryType,UINT nRetryDelay=0,UINT nRetryMax = 0);
	void SetNotifyWnd(HWND hNotifyWnd,UINT nNotifyMsg,BOOL bNotify = TRUE );
	void SetProxy(LPCTSTR lpszProxyServer,USHORT nProxyPort,BOOL bProxy=TRUE,BOOL bProxyAuthorization = FALSE,LPCTSTR lpszProxyUsername = NULL,LPCTSTR lpszProxyPassword = NULL,UINT nProxyType = PROXY_HTTPGET);
	void StopDownload();
	BOOL ParseURL(LPCSTR lpszURL,CStringA& strServer,CStringA& strObject,USHORT& nPort);
	BOOL GetDownloadFileStatus(LPCTSTR lpszDownloadUrl,DWORD &dwFileSize,CTime &FileTime);
	UINT Download(LPCTSTR lpszDownloadUrl,LPCTSTR lpszSavePath, const char* pszCrc = NULL, UINT nFrom = 0, UINT nTo = 0, BOOL bForceDownload = FALSE);
	
	// 自动开启一个线程进行下载
	UINT Down(
		LPCSTR lpszDownloadUrl, 
		LPCSTR lpszSavePath, 
		UINT nFrom = 0, 
		UINT nTo = 0, 
		BOOL bForceDownload = FALSE
		);

	UINT DownloadEx(LPCSTR lpszDownloadUrl, 
		LPCTSTR lpszSavePath, 
		long &lLength, 
		char *pCookie, 
		char *pReferer, 
		long lFrom, 
		long lTo, 
		int nServerType);
	// 格式化请求文件下载字符串
	const char* FormatRequestHeader(char *pServer,char *pObject,long &Length,
		char* pCookie=NULL,char *pReferer=NULL,
		long nFrom=0,long nTo=0,
		int nServerType=0);
private:
	UINT	SendRequest(BOOL bHead = FALSE, UINT nFrom = 0, UINT nTo = 0);
	UINT	SendRequestEx(LPCTSTR lpszRequestHeader = NULL);
	BOOL	CreateSocket();
	void	CloseSocket();
	UINT	GetInfo(LPCSTR lpszHeader,DWORD& dwContentLength,DWORD& dwStatusCode,CTime& TimeLastModified);
	CTime	GetTime(LPCSTR lpszTime);

private:	
	
	// 下载参数
	// 待下载URL和本地保存路径
	CStringA		m_strDownloadUrl;
	CStringA		m_strSavePath;
	CStringA		m_strTempSavePath;//临时文件的路径

	// 停止下载
	BOOL		m_bStopDownload;

	// 强制重新下载(不管已有的文件是否与远程文件相同)
	BOOL		m_bForceDownload;

	// 是否支持断点续传
	BOOL		m_bSupportResume;

	// 文件以及下载大小
	DWORD		m_dwFileSize;				// 文件总的大小	
	DWORD		m_dwFileDownloadedSize;		// 文件总共已经下载的大小

	DWORD		m_dwDownloadSize;			// 本次需要下载的大小
	DWORD		m_dwDownloadedSize;			// 本次已经下载的大小

	DWORD		m_dwHeaderSize;				// 返回头的大小
	CStringA		m_strHeader;				// 保存头部信息

	// 文件日期(远程文件的信息)
	CTime		m_TimeLastModified;

	// Referer
	CStringA		m_strReferer;
	
	// UserAgent
	CStringA		m_strUserAgent;

	// 超时TIMEOUT	连接超时、发送超时、接收超时(单位：毫秒)
	DWORD		m_dwConnectTimeout;	
	DWORD		m_dwReceiveTimeout;
	DWORD		m_dwSendTimeout;

	// 重试机制
	UINT		m_nRetryType;	//重试类型(0:不重试 1:重试一定次数 2:总是重试)
	UINT		m_nRetryTimes;	//重试次数
	UINT		m_nRetryDelay;	//重试延迟(单位：毫秒)
	UINT		m_nRetryMax;    //重试的最大次数

	// 错误处理
	UINT		m_nErrorCount;	//错误次数
	CStringA		m_strError;		//错误信息

	// 向其他窗口发送消息
	BOOL		m_bNotify;			// 是否向外发送通知消息	
	HWND		m_hNotifyWnd;		// 被通知的窗口
	UINT		m_nNotifyMessage;	// 被通知的消息

	// 是否进行验证 : Request-Header: Authorization
	BOOL		m_bAuthorization;
	CStringA		m_strUsername;
	CStringA		m_strPassword;

	// 是否使用代理 
	BOOL		m_bProxy;
	CStringA		m_strProxyServer;
	USHORT		m_nProxyPort;
	UINT		m_nProxyType;
	
	// 代理是否需要验证: Request-Header: Proxy-Authorization
	BOOL		m_bProxyAuthorization;
	CStringA		m_strProxyUsername;
	CStringA		m_strProxyPassword;


	// 下载过程中所用的变量
	CStringA		m_strServer;
	CStringA		m_strObject;
	CStringA		m_strFileName;
	UINT		m_nFrom;
	UINT		m_nTo;
	USHORT		m_nPort;

	SOCKET		m_hSocket;	// 下载连接的SOCKET
	PBSD		m_pBSD;		// BufSocketData结构
	
	// 用于BASE64编码、解码
	static UINT		m_nBase64Mask[];
	static CStringA	m_strBase64TAB;

	// 请求字符串
	char m_requestheader[1024];

};

#endif // !defined(AFX_HTTPDOWNLOAD_H__11AB7F1F_62EA_47FC_8B2D_B2E3929E2861__INCLUDED_)
