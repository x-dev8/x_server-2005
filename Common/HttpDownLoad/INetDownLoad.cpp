

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类


#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT


#include "INetDownLoad.h"

#include <atlbase.h>
#include <string>
#include "CRC32.h"
#include "tstring.h"

using Common::_tstring;

BOOL CINetDownLoad::Init()
{
	//Generate GUID to avoid overwritting previously saved web pages
	GUID guid;
	::CoCreateGuid(&guid);

	
	m_hINet = ::InternetOpen("HOT Download", INTERNET_OPEN_TYPE_DIRECT,
		NULL, NULL, 0);
	if(m_hINet == NULL)
		return FALSE;

	return TRUE;
}



DWORD CINetDownLoad::GetContentLength( HINTERNET hFile )
{
	DWORD		dwBuffSize = sizeof (DWORD) ;
	DWORD		cbContLen = 0;
	if ( !::HttpQueryInfo (
		hFile
		, HTTP_QUERY_CONTENT_LENGTH		// Reads the 'content-length' header
		| HTTP_QUERY_FLAG_NUMBER
		, static_cast<void *> (&cbContLen)
		, &dwBuffSize					// Buffer size (byte)
		, NULL							// Does not use a header index
		)
		) 
	{
		if ( ::GetLastError () == ERROR_HTTP_HEADER_NOT_FOUND )
			return 0;
	}
	return cbContLen;
}


HANDLE hComplete;

UINT CINetDownLoad::Download(LPCTSTR lpszDownloadUrl,
							 LPCTSTR lpszSavePath, 
							 const char* pszCrc,
							 UINT nFrom, 
							 UINT nTo,
							 BOOL bForceDownload)
{
Start:
	//Init();
	m_dwFileDownloadedSize = 0;
	m_dwCurFileSize = 0;
	const int MAX_BUFFER_SIZE = 65535;
	unsigned long nCurrSize = 0;
	unsigned long nBeginSize = 0;
	BYTE szBuffer[MAX_BUFFER_SIZE];
	//Download Web Page using WININET
	BOOL bReadSucess = TRUE;
	CString strDownLoadURL;
	strDownLoadURL = lpszDownloadUrl;
	strDownLoadURL.MakeLower();
	strDownLoadURL.Replace(_T('\\'), _T('/'));

	//HINTERNET hFile = ::InternetOpenUrl(m_hINet, strDownLoadURL.GetBuffer(), NULL, 0, 0, 0); 
	HINTERNET hFile =::InternetOpenUrl(m_hINet,strDownLoadURL.GetBuffer(),"",-1L,INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE,0);
	if(hFile == NULL)
		return DOWNLOAD_RESULT_FAIL;

	unsigned char   dBuf[MAX_PATH*4] = {0};   
	DWORD   dwBufSize0=sizeof(dBuf);   
	::HttpQueryInfo(hFile,HTTP_QUERY_STATUS_CODE   |   HTTP_QUERY_FLAG_NUMBER,dBuf,&dwBufSize0,NULL); 

	if (dBuf[0] != ERROR_RING2SEG_MUST_BE_MOVABLE && dBuf[0] != ERROR_FILENAME_EXCED_RANGE)
	{
		return DOWNLOAD_RESULT_FAIL;
	}

    ::SetFileAttributes(lpszSavePath, FILE_ATTRIBUTE_NORMAL);
    remove(CStringA(lpszSavePath).GetBuffer());
	CFile fileDown;
	if(! fileDown.Open( lpszSavePath,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite|CFile::shareDenyWrite) )
		return DOWNLOAD_RESULT_FAIL;	

	DWORD dwLength = GetContentLength( hFile );
	m_dwCurFileSize = dwLength;
	//BYTE *pbBuffer = new BYTE[dwLength+1];
	while(true)
	{
		BOOL bRet = ::InternetReadFile(hFile, &szBuffer, MAX_BUFFER_SIZE, &nCurrSize);

		if (bRet)
		{
			m_dwFileDownloadedSize+=nCurrSize;
			// 将数据写入文件
			fileDown.Write(szBuffer,nCurrSize);

			if(m_proc)
			{
				(*m_proc)( dwLength, m_dwFileDownloadedSize );
			}
		}

		if(!bRet || nCurrSize <= 0)
		{
			//if (nCurrSize <= 0)
			//{
			//	fileDown.Close();
			//}
			break;
		}
	}

	//if (pszCrc == NULL)
	//{
		if (fileDown.GetLength() != dwLength)
		{
			fileDown.Close();
			goto Start;
			//return DOWNLOAD_RESULT_FAIL;
		}
	//}
	//else
	//{
	//	fileDown.Close();
	//	::Crypto::CCRC32 crc;
	//	_tstring strCRC;
	//	strCRC.Format("%d", crc.GetFileCRC32(lpszSavePath));
	//	if (strCRC != pszCrc)
	//	{
	//		goto Start;
	//		//return DOWNLOAD_RESULT_FAIL;
	//	}
	//	//dwCrc
	//}

	//FILE* pf = fopen( szSaveFile.c_str(), "wb+" );
	//if( pf !=NULL )
	//{
	//	fwrite( (void*)pbBuffer, dwLength, 1, pf );
	//	fclose( pf );
	//}
	//delete []pbBuffer;
	//pbBuffer = NULL;

	return DOWNLOAD_RESULT_SUCCESS;
}

//CINetDownLoad* GetINetDownLoad()
//{
//	static CINetDownLoad DownLoad;
//	return &DownLoad;
//}