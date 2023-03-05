#include "DownLoad.h"
#include <wininet.h>

//// ���ؽ��
//const UINT	INet_DOWNLOAD_RESULT_SUCCESS	= 0;	// �ɹ�
//const UINT	INet_DOWNLOAD_RESULT_SAMEAS	= 1;	// Ҫ���ص��ļ��Ѿ����ڲ�����Զ���ļ�һ�£���������
//const UINT	INet_DOWNLOAD_RESULT_STOP	= 2;	// ��;ֹͣ(�û��ж�)
//const UINT	INet_DOWNLOAD_RESULT_FAIL	= 3;	// ����ʧ��

class CINetDownLoad :public IDownLoad
{
public:
	HINTERNET m_hINet;
	DWORD	  m_dwFileDownloadedSize;
	DWORD	  m_dwCurFileSize;


	DownLoadProc m_proc;

	CINetDownLoad()
	{
		m_dwFileDownloadedSize = 0;
		m_dwCurFileSize = 0;
		m_proc = NULL;		
	}

	BOOL Init();
	UINT Download(LPCTSTR lpszDownloadUrl,LPCTSTR lpszSavePath, const char* pszCrc = NULL, UINT nFrom = 0, UINT nTo = 0, BOOL bForceDownload = FALSE);

	DWORD GetContentLength( HINTERNET hFile );
	BOOL ShutDown()
	{
		InternetCloseHandle( m_hINet );
		CoUninitialize();
		return true;
	}
	void SetCallBackDownProc(const DownLoadProc proc)
	{
		m_proc = proc;
	}
};

