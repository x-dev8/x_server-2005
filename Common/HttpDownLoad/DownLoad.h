#pragma once

#include <windows.h>
// �ṹ����
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

// ��������
// ȱʡ��ʱ����
const DWORD DOWNLOAD_CONNECT_TIMEOUT= 10*1000;// 10��
const DWORD DOWNLOAD_SEND_TIMEOUT	= 10*1000;// 10��
const DWORD DOWNLOAD_RECV_TIMEOUT	= 10*1000;// 10��

// ���ؽ��
const UINT	DOWNLOAD_RESULT_SUCCESS	= 0;	// �ɹ�
const UINT	DOWNLOAD_RESULT_SAMEAS	= 1;	// Ҫ���ص��ļ��Ѿ����ڲ�����Զ���ļ�һ�£���������
const UINT	DOWNLOAD_RESULT_STOP	= 2;	// ��;ֹͣ(�û��ж�)
const UINT	DOWNLOAD_RESULT_FAIL	= 3;	// ����ʧ��

// ��������
const UINT SENDREQUEST_SUCCESS	= 0; // �ɹ�
const UINT SENDREQUEST_ERROR	= 1; // һ��������󣬿�������
const UINT SENDREQUEST_STOP		= 2; // ��;ֹͣ(�û��ж�) (��������)
const UINT SENDREQUEST_FAIL		= 3; // ʧ�� (��������)	 

// ��Ϣ
const WPARAM	MSG_INTERNET_STATUS	= (WPARAM)1;
const WPARAM	MSG_DOWNLOAD_STATUS = (WPARAM)2;
const WPARAM	MSG_DOWNLOAD_RESULT = (WPARAM)3;
const WPARAM	MSG_DOWNLOADED		= (WPARAM)4;
const WPARAM	MSG_DOWNLOAD_MAX	= (WPARAM)32; //�������ɹ�����

//����״̬
const UINT		STATUS_TYPE_FILENAME			= 1;
const UINT		STATUS_TYPE_FILESIZE			= 2;
const UINT		STATUS_TYPE_FILEDOWNLOADEDSIZE	= 3;
const UINT		STATUS_TYPE_ERROR_COUNT			= 4;
const UINT		STATUS_TYPE_ERROR_CODE			= 5;
const UINT		STATUS_TYPE_ERROR_STRING		= 6;

// �������
const UINT RETRY_TYPE_NONE	= 0;
const UINT RETRY_TYPE_TIMES	= 1;
const UINT RETRY_TYPE_ALWAYS= 2;
//ȱʡ�����Դ���
const UINT DEFAULT_RETRY_MAX= 10; 

// ȱʡ�˿ں�
const USHORT DEFAULT_HTTP_PORT = 80;
const USHORT DEFAULT_HTTPS_PORT= 443;
const USHORT DEFAULT_FTP_PORT  = 21;
const USHORT DEFAULT_SOCKS_PORT= 1080;


// HTTP STATUS CODE����
const UINT	HTTP_OK			= 0;
const UINT	HTTP_ERROR		= 1;
const UINT	HTTP_REDIRECT	= 2;
const UINT	HTTP_FAIL		= 3;

// PROXY������
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


	//�û��Զ������ؽ��Ȼص�������ʽ
	typedef void (*DownLoadProc)(unsigned int nFileSize, unsigned int nCurrDownLoadSize); 

	virtual void SetCallBackDownProc(const DownLoadProc proc){}
};