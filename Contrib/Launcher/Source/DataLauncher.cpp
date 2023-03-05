#include "MeRTLibs.h"
#include <string>
#include "ILoadData.h"
#include "Log4cpp/log4cpp_logger.h"
#define ERROR_INFO_LOG	"ErrorInfo.log"
bool g_DirectReadInPackage = false;
#define _IOYOURBUF      0x0100

FILE *swFileOpen( 
						const char *filename,
						const char *mode 
						)
{
	std::string  str(mode);
	if (std::string::npos != str.find("r"))
	{
		FILE* fp = NULL;
		if (g_DirectReadInPackage)
		{
			if(!Launcher::GetLoadDataInstance()->GetFileHandle(filename,fp))
			{
				if (!fp)
				{
					char temp[2048];
					sprintf_s(temp,2048,"%s从数据包打开失败！",filename);
					LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, temp);
				}
				fp = fopen(filename,mode);
			}
		}
		else
		{
			fp = fopen(filename,mode);
			if (!fp)
			{
				if(!Launcher::GetLoadDataInstance()->GetFileHandle(filename,fp))
				{
					char temp[2048];
					sprintf_s(temp,2048,"%s从数据包打开失败！",filename);
					LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, temp);
				}
			}
		}
		return fp;
	}
	else
	{
		return fopen(filename,mode);
	}

}
errno_t swFileOpen_s(FILE** ppFile,
							const char *filename,
							const char *mode 
							)
{
	std::string  str(mode);
	if (std::string::npos != str.find("r"))
	{
		errno_t nRet = EINVAL;
		if (g_DirectReadInPackage)
		{
			if(Launcher::GetLoadDataInstance()->GetFileHandle(filename,*ppFile))
				return 0;	
			else
			{
				char temp[2048];
				sprintf_s(temp,2048,"%s从数据包打开失败！",filename);
				LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, temp);

				return fopen_s(ppFile,filename,mode);
			}
		}
		else
		{
			nRet = fopen_s(ppFile,filename,mode);
			if (*ppFile == NULL)
			{
				if(Launcher::GetLoadDataInstance()->GetFileHandle(filename,*ppFile))
					return 0;	
				else
				{
					char temp[2048];
					sprintf_s(temp,2048,"%s从数据包打开失败！",filename);
					LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, temp);
				}
			}
		}
		return nRet;
	}
	else
	{
		return fopen_s(ppFile,filename,mode);
	}
}
int swFileClose( 
					   FILE *stream 
					   )
{
	if (Launcher::GetLoadDataInstance()->IsInMap(stream))
	{
		Launcher::GetLoadDataInstance()->Close(stream);
		return 0;
	}
	else
	{
		if (stream && (stream)->_flag & (_IOYOURBUF))
		{
			delete [] stream->_base;
		}
	}
	return fclose(stream);
}
struct SFindResult 
{
	void*		m_pHandleFromPackage;
	void*		m_pHandleFromDisk;
	std::string m_FindFileName;
};
// std::vector<SFindResult*> resultArr;
void* swFindFirstFile( const char * lpFileName, void* lpFindFileData )
{
	char temp[MAX_PATH];
	strcpy(temp,lpFileName);
	char* pStar = strstr(temp,"*");
	if (pStar)
	{
		WIN32_FIND_DATA* pData = (WIN32_FIND_DATA*)lpFindFileData;
		int nStarIndex = pStar - temp;
		temp[nStarIndex] = '\0';
		std::string retStr;
		void * pHandleFromPkg = Launcher::GetLoadDataInstance()->FindFirst(temp,&temp[nStarIndex + 1],retStr);
		if (pHandleFromPkg)
		{
			SFindResult* pFindResult = new SFindResult;
// 			resultArr.push_back(pFindResult);
			pFindResult->m_pHandleFromDisk = NULL;
			pFindResult->m_pHandleFromPackage = pHandleFromPkg;
			pFindResult->m_FindFileName = lpFileName;
			int npos = retStr.rfind('\\');
			strcpy(pData->cFileName,&retStr.c_str()[npos + 1]);
			return pFindResult;
		}
		else if(!g_DirectReadInPackage)
		{
			void* pHandleFromDisk = FindFirstFile(lpFileName,pData);
			if (pHandleFromDisk != INVALID_HANDLE_VALUE)
			{
				SFindResult* pFindResult = new SFindResult;
// 				resultArr.push_back(pFindResult);
				pFindResult->m_pHandleFromDisk = pHandleFromDisk;
				pFindResult->m_pHandleFromPackage = NULL;
				return pFindResult;
			}
		}
	}
	return INVALID_HANDLE_VALUE;
	
}

bool swFindNextFile( void* hFindFile, void* lpFindFileData )
{
	SFindResult* pFindResult = (SFindResult*)hFindFile;
	WIN32_FIND_DATA* pData = (WIN32_FIND_DATA*)lpFindFileData;
	if (pFindResult->m_pHandleFromPackage)
	{
		std::string retStr;
		if (Launcher::GetLoadDataInstance()->FindNext(pFindResult->m_pHandleFromPackage,retStr))
		{
			int npos = retStr.rfind('\\');
			strcpy(pData->cFileName,&retStr.c_str()[npos + 1]);
			return true;
		}
		else
		{
			Launcher::GetLoadDataInstance()->FindClose(pFindResult->m_pHandleFromPackage);
			if (!g_DirectReadInPackage)
			{
				pFindResult->m_pHandleFromPackage = NULL;
				void* pHandleFromDisk = FindFirstFile(pFindResult->m_FindFileName.c_str(),pData);
				if (pHandleFromDisk != INVALID_HANDLE_VALUE)
				{
					pFindResult->m_pHandleFromDisk = pHandleFromDisk;
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		assert(pFindResult->m_pHandleFromDisk != INVALID_HANDLE_VALUE);
		return (FindNextFile(pFindResult->m_pHandleFromDisk,pData));

	}
}

bool swFindClose( void* pHandle )
{
	SFindResult* pFindResult = (SFindResult*)pHandle;
	if (pFindResult->m_pHandleFromDisk)
	{
		FindClose(pFindResult->m_pHandleFromDisk);
	}
	delete pFindResult;
	return true;

}

long swGetFileSize( FILE* pFile )
{
	if (pFile && pFile->_cnt != 0&& ((pFile)->_flag & (_IOYOURBUF)))
	{
		return pFile->_cnt;
	}
	else
	{
		return ftell(pFile);
	}

}

int swFileSeek(  FILE * pFile,  long _Offset,  int _Origin )
{
	if (pFile)
	{
		if((pFile)->_flag & (_IOYOURBUF))
		{
			int nCntBak = pFile->_cnt;
			char *_ptr = pFile->_ptr; 
			int nRet = fseek(pFile,_Offset,_Origin);
			pFile->_cnt = nCntBak;
			pFile->_ptr = _ptr;
			return nRet;
		}
		else
		{
			return fseek(pFile,_Offset,_Origin);
		}
	}
	return 0;
}

void swRewind( FILE* pFile )
{
	if (pFile)
	{
		if((pFile)->_flag & (_IOYOURBUF))
		{
			int nCntBak = pFile->_cnt;
			char *_ptr = pFile->_ptr; 
			rewind(pFile);
			pFile->_cnt = nCntBak;
			pFile->_ptr = _ptr;
		}
		else
		{
			rewind(pFile);
		}
	}
}

void SetFlushTmpToDisk( bool bValue )
{
	{
		Launcher::GetLoadDataInstance()->SetFlushTmpToDisk(bValue);
	}

}

bool swIsFileExist( const char* lpFileName )
{
	if (NULL == lpFileName)
	{
		return false;
	}
	std::string temp(lpFileName);
	return Launcher::GetLoadDataInstance()->IsFileExist(temp);
}