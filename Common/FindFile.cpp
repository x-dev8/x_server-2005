#include "FindFile.h"
#include "FuncPerformanceLog.h"

CFindFile::CFindFile(void)
{
	guardfunc;
	m_pFoundInfo = NULL;
	m_pNextInfo = NULL;
	m_hContext = NULL;
	m_chDirSeparator = '\\';
	unguard;
}

CFindFile::~CFindFile(void)
{
	guardfunc;
	Close();
	unguard;
}

void CFindFile::CloseContext()
{
	guardfunc;
	FindClose(m_hContext);
	return;
	unguard;
}

BOOL CFindFile::FindFile(LPCSTR pstrName /* = NULL */,
						 DWORD dwUnused /* = 0 */)
{
	guardfunc;
	Close();
	m_pNextInfo = new WIN32_FIND_DATA;

	if (pstrName == NULL)
		pstrName = _T("*.*");

	WIN32_FIND_DATA *pFindData = (WIN32_FIND_DATA *)m_pNextInfo;

	lstrcpyn(pFindData->cFileName, pstrName,sizeof(pFindData->cFileName) );

	m_hContext = ::FindFirstFile(pstrName, (WIN32_FIND_DATA*) m_pNextInfo);

	if (m_hContext == INVALID_HANDLE_VALUE)
	{
		DWORD dwTemp = ::GetLastError();
		Close();
		return FALSE;
	}

	char *pstrRoot = m_strRoot;
	LPCTSTR pstr = _tfullpath(pstrRoot, pstrName, _MAX_PATH);

	// passed name isn't a valid path but was found by the API
	if (pstr == NULL)
	{
	//	m_strRoot
		Close();
		::SetLastError(ERROR_INVALID_NAME);
		return FALSE;
	}
	else
	{
		// find the last forward or backward whack
		char* pstrBack  = _tcsrchr(pstrRoot, '\\');
		char* pstrFront = _tcsrchr(pstrRoot, '/');

		if (pstrFront != NULL || pstrBack != NULL)
		{
			if (pstrFront == NULL)
				pstrFront = pstrRoot;
			if (pstrBack == NULL)
				pstrBack = pstrRoot;

			// from the start to the last whack is the root

			if (pstrFront >= pstrBack)
				*pstrFront = '\0';
			else
				*pstrBack = '\0';
		}
	//	m_strRoot.ReleaseBuffer(-1);
	}

	return TRUE;
	unguard;
}

BOOL CFindFile::FindNextFile()
{
	guardfunc;

	if (m_hContext == NULL)
		return FALSE;
	if (m_pFoundInfo == NULL)
		m_pFoundInfo = new WIN32_FIND_DATA;

//	ASSERT_VALID(this);

	void* pTemp = m_pFoundInfo;
	m_pFoundInfo = m_pNextInfo;
	m_pNextInfo = pTemp;

	return ::FindNextFile(m_hContext, (LPWIN32_FIND_DATA) m_pNextInfo);
	unguard;
}
	
BOOL CFindFile::IsDots() const
{
	guardfunc;
	// return TRUE if the file name is "." or ".." and
	// the file is a directory

	BOOL bResult = FALSE;
	if (m_pFoundInfo != NULL && IsDirectory())
	{
		LPWIN32_FIND_DATA pFindData = (LPWIN32_FIND_DATA) m_pFoundInfo;
		if (pFindData->cFileName[0] == '.')
		{
			if (pFindData->cFileName[1] == '\0' ||
				(pFindData->cFileName[1] == '.' &&
				pFindData->cFileName[2] == '\0'))
			{
				bResult = TRUE;
			}
		}
	}

	return bResult;
	unguard;
}

string CFindFile::GetFileName() const
{
	guardfunc;
	string ret;

	if (m_pFoundInfo != NULL)
		ret = ((LPWIN32_FIND_DATA) m_pFoundInfo)->cFileName;
	return ret;
	unguard;
}

string CFindFile::GetFilePath() const
{
	guardfunc;
	string strResult = m_strRoot;
	LPCTSTR pszResult;
	LPCTSTR pchLast;
	pszResult = strResult.c_str();
	pchLast = _tcsdec( pszResult, pszResult+strResult.size() );
	if ((*pchLast != _T('\\')) && (*pchLast != _T('/')))
	strResult += m_chDirSeparator;
	strResult += GetFileName();
	return strResult;
	unguard;
}

string CFindFile::GetFileTitleName() const
{
	guardfunc;
	string strFullName = GetFileName();
	string strResult;
	char szPath[MAX_PATH] = {0};
	_tsplitpath(strFullName.c_str(), NULL, NULL, szPath, NULL);
	strResult = szPath;
	return strResult;
	unguard;
}

string CFindFile::GetFileURL() const
{
	guardfunc;
	string strResult("file://");
	strResult += GetFilePath();
	return strResult;
	unguard;
}

string CFindFile::GetRoot() const
{
	guardfunc;
	return m_strRoot;
	unguard;
}

void CFindFile::Close()
{
	guardfunc;
	if (m_pFoundInfo != NULL)
	{
		delete m_pFoundInfo;
		m_pFoundInfo = NULL;
	}

	if (m_pNextInfo != NULL)
	{
		delete m_pNextInfo;
		m_pNextInfo = NULL;
	}

	if (m_hContext != NULL && m_hContext != INVALID_HANDLE_VALUE)
	{
		CloseContext();
		m_hContext = NULL;
	}
	unguard;
}

BOOL CFindFile::IsDirectory() const
{
	guardfunc;
	return MatchesMask(FILE_ATTRIBUTE_DIRECTORY);
	unguard;
}


BOOL CFindFile::MatchesMask(DWORD dwMask) const
{
	guardfunc;
	if (m_pFoundInfo != NULL)
		return (!!(((LPWIN32_FIND_DATA) m_pFoundInfo)->dwFileAttributes & dwMask));
	else
		return FALSE;
	unguard;
}



