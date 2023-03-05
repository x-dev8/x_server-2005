#pragma once

#include <windows.h>
// 结构定义
typedef struct _tagDownloadStatus
{
	UINT	nStatusType;
	DWORD	dwFileSize;
	DWORD	dwFileDownloadedSize;
	CStringA strFileName;
	//	UINT	nErrorCount;	
	//	CStringA strError;
	//	DWORD	dwErrorCode;
}DOWNLOADSTATUS,*PDOWNLOADSTATUS;

// 常量定义
// 缺省超时参数
const DWORD DOWNLOAD_CONNECT_TIMEOUT= 10*1000;// 10秒
const DWORD DOWNLOAD_SEND_TIMEOUT	= 10*1000;// 10秒
const DWORD DOWNLOAD_RECV_TIMEOUT	= 10*1000;// 10秒

// 下载结果
const UINT	DOWNLOAD_RESULT_SUCCESS	= 0;	// 成功
const UINT	DOWNLOAD_RESULT_SAMEAS	= 1;	// 要下载的文件已经存在并且与远程文件一致，不用下载
const UINT	DOWNLOAD_RESULT_STOP	= 2;	// 中途停止(用户中断)
const UINT	DOWNLOAD_RESULT_FAIL	= 3;	// 下载失败

// 发送请求
const UINT SENDREQUEST_SUCCESS	= 0; // 成功
const UINT SENDREQUEST_ERROR	= 1; // 一般网络错误，可以重试
const UINT SENDREQUEST_STOP		= 2; // 中途停止(用户中断) (不用重试)
const UINT SENDREQUEST_FAIL		= 3; // 失败 (不用重试)	 

// 消息
const WPARAM	MSG_INTERNET_STATUS	= (WPARAM)1;
const WPARAM	MSG_DOWNLOAD_STATUS = (WPARAM)2;
const WPARAM	MSG_DOWNLOAD_RESULT = (WPARAM)3;
const WPARAM	MSG_DOWNLOADED		= (WPARAM)4;
const WPARAM	MSG_DOWNLOAD_MAX	= (WPARAM)32; //保留最大可供扩充

//下载状态
const UINT		STATUS_TYPE_FILENAME			= 1;
const UINT		STATUS_TYPE_FILESIZE			= 2;
const UINT		STATUS_TYPE_FILEDOWNLOADEDSIZE	= 3;
const UINT		STATUS_TYPE_ERROR_COUNT			= 4;
const UINT		STATUS_TYPE_ERROR_CODE			= 5;
const UINT		STATUS_TYPE_ERROR_STRING		= 6;

// 重试类别
const UINT RETRY_TYPE_NONE	= 0;
const UINT RETRY_TYPE_TIMES	= 1;
const UINT RETRY_TYPE_ALWAYS= 2;
//缺省的重试次数
const UINT DEFAULT_RETRY_MAX= 10; 

// 缺省端口号
const USHORT DEFAULT_HTTP_PORT = 80;
const USHORT DEFAULT_HTTPS_PORT= 443;
const USHORT DEFAULT_FTP_PORT  = 21;
const USHORT DEFAULT_SOCKS_PORT= 1080;


// HTTP STATUS CODE分类
const UINT	HTTP_OK			= 0;
const UINT	HTTP_ERROR		= 1;
const UINT	HTTP_REDIRECT	= 2;
const UINT	HTTP_FAIL		= 3;

// PROXY的类型
const UINT	PROXY_NONE			= 0;
const UINT	PROXY_HTTPGET		= 1;
const UINT	PROXY_HTTPCONNECT	= 2;
const UINT	PROXY_SOCKS4		= 3;
const UINT	PROXY_SOCKS4A		= 4;
const UINT	PROXY_SOCKS5		= 5;


class IDownLoad
{
public:
	virtual BOOL Init() = 0;
	virtual BOOL ShutDown() = 0;
	virtual UINT Download( LPCTSTR lpszDownloadUrl,LPCTSTR lpszSavePath, const char* pszCrc = NULL, 
		UINT nFrom = 0, UINT nTo = 0, 
		BOOL bForceDownload = FALSE ) = 0;

	virtual void SetTimeout(DWORD dwSendTimeout,DWORD dwReceiveTimeout,DWORD dwConnectTimeout){}
	virtual void SetRetry(UINT nRetryType,UINT nRetryDelay=0,UINT nRetryMax = 0){}
	virtual void SetNotifyWnd(HWND hNotifyWnd,UINT nNotifyMsg,BOOL bNotify = TRUE ){}


	//用户自定义下载进度回调函数格式
	typedef void (*DownLoadProc)(unsigned int nFileSize, unsigned int nCurrDownLoadSize); 

	virtual void SetCallBackDownProc(const DownLoadProc proc){}
};