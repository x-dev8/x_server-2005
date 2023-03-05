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
	// ��̬����������64���롢����
	static int Base64Encode( LPCSTR lpszEncoding, CStringA& strEncoded );
	static int Base64Decode( LPCSTR lpszDecoding, CStringA& strDecoded );
	
	// ���غ���
	static UINT RunThread(LPVOID lpArg);

	DownLoadProc m_proc;
	void SetCallBackDownProc(const DownLoadProc proc)
	{
		m_proc = proc;
	}
	// DWONLOAD����
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
	
	// �Զ�����һ���߳̽�������
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
	// ��ʽ�������ļ������ַ���
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
	
	// ���ز���
	// ������URL�ͱ��ر���·��
	CStringA		m_strDownloadUrl;
	CStringA		m_strSavePath;
	CStringA		m_strTempSavePath;//��ʱ�ļ���·��

	// ֹͣ����
	BOOL		m_bStopDownload;

	// ǿ����������(�������е��ļ��Ƿ���Զ���ļ���ͬ)
	BOOL		m_bForceDownload;

	// �Ƿ�֧�ֶϵ�����
	BOOL		m_bSupportResume;

	// �ļ��Լ����ش�С
	DWORD		m_dwFileSize;				// �ļ��ܵĴ�С	
	DWORD		m_dwFileDownloadedSize;		// �ļ��ܹ��Ѿ����صĴ�С

	DWORD		m_dwDownloadSize;			// ������Ҫ���صĴ�С
	DWORD		m_dwDownloadedSize;			// �����Ѿ����صĴ�С

	DWORD		m_dwHeaderSize;				// ����ͷ�Ĵ�С
	CStringA		m_strHeader;				// ����ͷ����Ϣ

	// �ļ�����(Զ���ļ�����Ϣ)
	CTime		m_TimeLastModified;

	// Referer
	CStringA		m_strReferer;
	
	// UserAgent
	CStringA		m_strUserAgent;

	// ��ʱTIMEOUT	���ӳ�ʱ�����ͳ�ʱ�����ճ�ʱ(��λ������)
	DWORD		m_dwConnectTimeout;	
	DWORD		m_dwReceiveTimeout;
	DWORD		m_dwSendTimeout;

	// ���Ի���
	UINT		m_nRetryType;	//��������(0:������ 1:����һ������ 2:��������)
	UINT		m_nRetryTimes;	//���Դ���
	UINT		m_nRetryDelay;	//�����ӳ�(��λ������)
	UINT		m_nRetryMax;    //���Ե�������

	// ������
	UINT		m_nErrorCount;	//�������
	CStringA		m_strError;		//������Ϣ

	// ���������ڷ�����Ϣ
	BOOL		m_bNotify;			// �Ƿ����ⷢ��֪ͨ��Ϣ	
	HWND		m_hNotifyWnd;		// ��֪ͨ�Ĵ���
	UINT		m_nNotifyMessage;	// ��֪ͨ����Ϣ

	// �Ƿ������֤ : Request-Header: Authorization
	BOOL		m_bAuthorization;
	CStringA		m_strUsername;
	CStringA		m_strPassword;

	// �Ƿ�ʹ�ô��� 
	BOOL		m_bProxy;
	CStringA		m_strProxyServer;
	USHORT		m_nProxyPort;
	UINT		m_nProxyType;
	
	// �����Ƿ���Ҫ��֤: Request-Header: Proxy-Authorization
	BOOL		m_bProxyAuthorization;
	CStringA		m_strProxyUsername;
	CStringA		m_strProxyPassword;


	// ���ع��������õı���
	CStringA		m_strServer;
	CStringA		m_strObject;
	CStringA		m_strFileName;
	UINT		m_nFrom;
	UINT		m_nTo;
	USHORT		m_nPort;

	SOCKET		m_hSocket;	// �������ӵ�SOCKET
	PBSD		m_pBSD;		// BufSocketData�ṹ
	
	// ����BASE64���롢����
	static UINT		m_nBase64Mask[];
	static CStringA	m_strBase64TAB;

	// �����ַ���
	char m_requestheader[1024];

};

#endif // !defined(AFX_HTTPDOWNLOAD_H__11AB7F1F_62EA_47FC_8B2D_B2E3929E2861__INCLUDED_)
