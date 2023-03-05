#include "Me3d/include.h"
//#include "Me3d/MEX2.h"
// #include "slkreader\slkreader.h"
#include "Me3d/Model/MexConfig.h"
//#include "Stdcharskeleton.h"
#include "Me3d/MoreAction.h"
#include "Me3d/Model/MexRes.h"
#include "Me3d/Engine/Engine.h"
#include "FuncPerformanceLog.h"
#include "Me3d/Md5Manager.h"
//#include "XmlStringLanguage.h"
#include "Me3d/Model/Mex2.h"
#include "Me3d/Model/BowStringBindingConfig.h"
//#include "ModelConfig.h"
#include "../filepacket/packet_interface.h"

///#include "launcher/DataLauncher.h"
#include "tstring.h"
CRITICAL_SECTION gs_MexResMgrIDCS;
CRITICAL_SECTION gs_MexResMgrFileCS;


void LockMexResMgrIDCS()
{
	DWORD nThread = GetCurrentThreadId();
	while(!TryEnterCriticalSection(&gs_MexResMgrIDCS))
	{
		Sleep(1);
	}
}

void LockMexResMgrFileCS()
{
	DWORD nThread = GetCurrentThreadId();
	while(!TryEnterCriticalSection(&gs_MexResMgrFileCS))
	{
		Sleep(1);
	}
}

static MexResMgr gs_MexResMgr;
#define EXTERNAL_BASE 100000000
MexResMgr* GetMexResMgr()
{
	guardfunc;
	return &gs_MexResMgr;
	unguard;
}
MexResMgr::Record::Record()
{
	guardfunc;
	nId = -1;
	szFilename[0] = 0;

	m_uiRefCount = 0;
	unguard;
}
MexResMgr::Record::~Record()
{
	guardfunc;
	//if( m_uiRefCount != 0 /*&& nId != DEFINE_MEX_ID*/ )
	//{
	//	assert( false );
	//}
	//assert( m_uiRefCount == 0 );
	//assert( res.pMex == NULL );
	//assert( res.pMexCfg == NULL );
	unguard;
}
void MexResMgr::Record::Release()
{
	guardfunc;
// 	if( m_uiRefCount == 0 )
// 	{
// 	//	assert( false );
// 	}
// 
// 	m_uiRefCount--;

// 	if( m_uiRefCount < 0 )
// 	{
// 		int i=0;
// 		m_uiRefCount = 0;
// 	}

	if( GetRefCount() == 0 )
	{
		{
			guard( flagdeleteRes );
			if( res.pMex )
			{
				guard(flagdeleteResMex);
				res.pMex->FlagDestroying();
				unguard;
			}
			res.bDestroying = TRUE;
			unguard;
		}

		
	}
	unguard;
}
//////////////////////////////////////////////////////////////////////
MexResMgr::MexResMgr():
m_pfnLoadingCallBack(NULL),
m_dwExternalBase(EXTERNAL_BASE)
{
	guardfunc;
	InitializeCriticalSection( &gs_MexResMgrIDCS );
	InitializeCriticalSection( &gs_MexResMgrFileCS );
	unguard;
};
MexResMgr::~MexResMgr()
{
	guardfunc;
	DeleteCriticalSection( &gs_MexResMgrIDCS );
	DeleteCriticalSection( &gs_MexResMgrFileCS );
	unguard;
}

/////////////////////////////
// MexResMgr::Record* MexResMgr::FindEffectInCache( const char* pszFilename )
// {
// 	if( !pszFilename )
// 	{
// 		return NULL;
// 	}
// 	//strstr()
// 	//static const char szEffDir[] = "Data\\DATA\\Mex\\Magic"; //commented out, jiayi, [09.04.07]
// 	static const char szEffDir[] = "Data\\Magic";//added, jiayi, [09.04.07]
// 	int nLen = strlen( szEffDir );
// 	// 看看是否是特效
// 	if( strnicmp( pszFilename, szEffDir, nLen ) != 0 )
// 		return NULL;
// 	BOOL bHit = FALSE;
// 	for( int i = 0; i < m_EffectCache.size(); i++ )
// 	{
// 		if( stricmp( pszFilename, m_EffectCache[i]->szFilename ) == 0 )
// 		{
// 			bHit = TRUE;
// 			return m_EffectCache[i];
// 			//break;
// 		}
// 	}
// 	return NULL;
// }


////////////////////////////
MexResMgr::Record* MexResMgr::CreateModel( const char* pszFilename, bool bKeepCloneMemory/* = true*/, bool bKeepOldData /*= false*/ )
{
	guardfunc;
//	CSALocker locker(this);
// 	while (!TryEnterCriticalSection( &gs_MexResMgrCS ))
// 	{
// 		Sleep(1);
// 	}
	int nId = GetIdByName(pszFilename);
// 	std::map<int,Record*>::iterator iter = m_RecordMgr.begin();
// 	for (; iter != m_RecordMgr.end(); ++iter)
// 	{
// 		if( stricmp( pszFilename, iter->second->szFilename ) == 0 )
// 		{
// 			nId = iter->first;
// 			break;
// 		}
// 	}
// 	std::vector<Record*> vectorRecord;
// 	m_RecordMgr.GetObjects( &vectorRecord );
// 	int nId = -1;
// 	for( int i = 0; i < vectorRecord.size(); i++ )
// 	{
// 		if( stricmp( pszFilename, vectorRecord[i]->szFilename ) == 0 )
// 		{
// 			nId = vectorRecord[i]->nId;
// 			break;
// 		}
// 	}
	if( nId == -1 )
	{
		nId = AddExternalFile( pszFilename );
	}           
	MexResMgr::Record* pRecord = CreateModel( nId, bKeepCloneMemory, bKeepOldData );
	//LeaveCriticalSection( &gs_MexResMgrCS );
	return pRecord;
	unguard;
}

//////////////////////////////////
MexResMgr::Record*	MexResMgr::AddZeroRefModel( int nModelId, IMex* pMex, MexCfg* pMexCfg )
{
	guardfunc;
	Record* pRecord = GetRecord( nModelId );
	return pRecord;
	unguard;
}

///////////////////////////////
MexResMgr::Record* MexResMgr::CreateModel( int nModelId, bool bKeepCloneMemory/* = true*/, bool bKeepOldData /*= false*/ )
{
	guardfunc;
//	CSALocker locker(this);
	// 根据id查找记录
// 	while (!TryEnterCriticalSection( &gs_MexResMgrCS ))
// 	{
// 		Sleep(1);
// 	}
	Record* pRecord = GetRecord( nModelId );
	
	if( !pRecord )
	{
		//LeaveCriticalSection( &gs_MexResMgrCS );
		return NULL;
	}
	pRecord->IncRefCount( bKeepOldData );
	// 存在，但是没有任何引用
// 	Res* pRes = &pRecord->res;
// 	{
// 		if( pRes->pMex )
// 		{
// 			//pRecord->dwBornTime =HQ_TimeGetTime();
// 			pRes->m_uiRefCount++;
// 			return pRecord;
// 		}
// 	}
// 	if( pRes->m_uiRefCount == 0 &&
// 		pRes->pMex == NULL )
// 	{
// 		//pRes->m_uiRefCount++;
// 		//if( pRes-> == )
// 		assert( pRes->pMex == NULL );
// 		assert( pRes->pMexCfg == NULL );
// 
// 
// 	}
// 	pRecord->m_uiRefCount++;
	
	//LeaveCriticalSection( &gs_MexResMgrCS );
	return pRecord;
	unguard;
}

///////////////////////////////
void MexResMgr::LogError(const char* szFormat, ...)
{
	guardfunc;
#ifdef _DEBUG
 // _DEBUG
	//char szDate[256] = {0};
	char szBuf[MAX_PATH] = {0};
	char szLog[MAX_PATH] = {0};

	//转换参数
	va_list vl;
	va_start(vl, szFormat);
	int cnt = vsnprintf(szBuf, sizeof(szBuf)-1, szFormat, vl);
	va_end(vl);

	_snprintf(szLog, sizeof(szLog)-1, "%s\n", szBuf);

	//char szFile[MAX_PATH] = {0};
	//char szRange[256] = {0};
	////DWORD dwLogID = g_dwMovePathLogID;
	//_mkdir("移动路径记录");
	//_snprintf(szFile, sizeof(szFile)-1, "移动路径记录\\%s", szDate);
	//_mkdir(szFile);
	//_snprintf(szFile, sizeof(szFile)-1, "%s\\%d", szFile, dwLogID);
	//_mkdir(szFile);
	//_snprintf(szFile, sizeof(szFile)-1, "ErrorLog\\%s.log", szFile, "RoleMovePath" );

	FILE* fLog = NULL;
	fLog = fopen( "MexRes.log", "at" );

	if( fLog != NULL )
	{
		fwrite( szLog, strlen(szLog), 1, fLog );
		fclose( fLog );
	}
	#endif
	unguard;
}

/////////////////////////
// void MexResMgr::Clear()
// {
// 	guardfunc;
// 	static DWORD dwLastTick = 0;
// 	if( HQ_TimeGetTime() - dwLastTick < 3000 )
// 	{	
// 		return;
// 	}
// 	dwLastTick = HQ_TimeGetTime();
// 	//for( int i=0; i< m_LiftCache.size(); i++ )
// 	//{
// 	//	if( m_LiftCache[i] != -1 )
// 	//	{
// 	//		Record* r = m_RecordMgr.Find( m_LiftCache[i] );
// 	//		if( r )
// 	//		{
// 	//			if( ( HQ_TimeGetTime() - r->dwBornTime ) > 120000 )
// 	//			{
// 	//				r->LiftType = MexResMgr::eMexAction_Common;
// 	//				r->Release();
// 	//			//	r->LiftType = MexResMgr::eMexAction_LiftForm;
// 	//			//	m_LiftCache[i] = -1;
// 	//			}
// 	//		}
// 	//		else
// 	//		{
// 	//			m_LiftCache[i] = -1;
// 	//		}
// 	//	}
// 	//}
// 	unguard;
// }

////////////////////////
// added by ZhuoMeng.Hu		[10/15/2010]
void MexResMgr::DumpRecordCount()
{
    unsigned int nCount( 0 ); 
    std::map<std::string, Record*>::iterator iter = m_mapRecords.begin();
    for(; iter != m_mapRecords.end(); ++iter )
    {
        Record* pRecord = iter->second;
        if( pRecord )
        {
            if( pRecord->res.pMex )
                ++nCount;
        }
    }
    char szBuf[256] = {0};
    _snprintf( szBuf, 255, "%s\t = %u\n", "MexRecord Count", nCount );
    OutputDebugString( szBuf );
}

void MexResMgr::ClearDestroyingRes(BOOL bDelay/*=TRUE*/, BOOL bIsTool /*= FALSE*/)
{
	MeScopeProfileMexResFun
	guardfunc;
//	CSALocker locker(this);
	if (!TryEnterCriticalSection( &gs_MexResMgrFileCS ))
	{
		return;
	}
    if( 0 )
    {
        DumpRecordCount();
    }
	BeginGuard

	// 每帧只删除一个模型数据 [11/3/2010 zhangjiayi]
	bool bDeleted = false;

	static DWORD dwLastTime = 0;
	DWORD dwCurTime = HQ_TimeGetTime();
	static DWORD s_dwKeepTime = 60000;
	
	if( bIsTool || (!bIsTool && dwCurTime - dwLastTime > s_dwKeepTime ))
	{
		dwLastTime = dwCurTime;
        std::map<std::string, Record*>::iterator iter = m_mapRecords.begin();
		for(; iter != m_mapRecords.end(); ++iter )
		{
			Record* pRecord = iter->second;

			if( pRecord->res.bDestroying )
			{
				if( pRecord->GetRefCount() > 0 )
				{
					pRecord->res.bDestroying = FALSE;
					pRecord->res.dwStartDestroyTime = dwCurTime;
					pRecord->res.bStartDestroying = FALSE;
				}

				if( pRecord->GetRefCount() == 0 )
				{
					if( pRecord->res.bStartDestroying )
					{
						if( ( !bDelay || (bDelay && dwCurTime - pRecord->res.dwStartDestroyTime > s_dwKeepTime/*600000*/) ) && !bDeleted )	// 保留10分钟有点长，为了节省内存，改为保留1分钟
						{
							guard(deleteRes);
							if( pRecord->res.pMex )
							{
								guard(deleteResMex);
								pRecord->res.pMex->Release();
								delete pRecord->res.pMex;
								pRecord->res.pMex = NULL;

								bDeleted = true;
								dwLastTime = 0;
								unguard;
							}

							if( pRecord->res.pMexCfg )
							{
								guard(deleteResMexCfg);
								delete pRecord->res.pMexCfg;
								pRecord->res.pMexCfg = NULL;
								unguard;
							}

							unguard;

							pRecord->res.bDestroying = FALSE;
							pRecord->res.dwStartDestroyTime = dwCurTime;
							pRecord->res.bStartDestroying = FALSE;
						}
					}
					else
					{
						pRecord->res.bStartDestroying = TRUE;
						pRecord->res.dwStartDestroyTime = dwCurTime;
					}
				}
			}
			else
			{
				pRecord->res.dwStartDestroyTime = dwCurTime;
			}
		}
	}
	EndGuard
	LeaveCriticalSection( &gs_MexResMgrFileCS );
	unguard;
}

/////////////////////////////
void MexResMgr::DestroyModel( int nModelId )
{
	guardfunc;
	Record* r = GetRecord( nModelId );
	if( !r )
	{
		return;
	}
	r->DecRefCount();
// 	r->Release();

	unguard;

}

void MexResMgr::Destroy()
{
	guardfunc;
//	CSALocker locker(this);
	LockMexResMgrIDCS();
	LockMexResMgrFileCS();
	BeginGuard
	if( m_mapRecords.size() > 0 )
	{
#ifdef _DEBUG
		FILE* fp = fopen( ".\\Log\\Resource.log", "w" );
		bool bWritten = false;
#endif
        std::map<std::string, Record*>::iterator iter = m_mapRecords.begin();
        for(; iter != m_mapRecords.end(); ++iter )
        {
            Record* pRecord = iter->second;
			if( pRecord->GetRefCount() > 0 )
			{
#ifdef _DEBUG
				if( fp )
				{
					bWritten = true;
					fprintf( fp, "[模型文件]\n%s\n未释放,引用次数%ld.\n", 
						pRecord->szFilename,
						pRecord->GetRefCount() );
				}
#endif

				// 销毁时需要把所有内存都释放掉，[QL]
				if( pRecord->res.pMex )
				{
					pRecord->res.pMex->Release();
					delete pRecord->res.pMex;
					pRecord->res.pMex = NULL;
				}

				if( pRecord->res.pMexCfg )
				{
					delete pRecord->res.pMexCfg;
					pRecord->res.pMexCfg = NULL;
				}

			}
			else
			{
				//
				if( pRecord->res.pMex )
				{
					pRecord->res.pMex->Release();
					delete pRecord->res.pMex;
					pRecord->res.pMex = NULL;
				}

				if( pRecord->res.pMexCfg )
				{
					delete pRecord->res.pMexCfg;
					pRecord->res.pMexCfg = NULL;
				}

			}
			Record* pSource = GetRecord( pRecord->nId );
			if( pSource && pSource == pRecord )
			{
				m_RecordMgr.erase( pRecord->nId );
			}
			delete pRecord;
			pRecord = NULL;
		}
#ifdef _DEBUG
		if( fp )
		{
			fclose( fp );
		}
		// added, jiayi, [2009/6/25]
		if( !bWritten )//未写，删
		{
			DeleteFile(".\\Log\\Resource.log");
		}
#endif
	}
	m_mapRecords.clear();

	std::map<int,Record*>::iterator iter = m_RecordMgr.begin();
	for (; iter != m_RecordMgr.end(); ++iter)
	{
		Record* pRecord = iter->second;
		if( pRecord )//pRecord->m_uiRefCount == 0 /*&& !pRecord->res.bDestroying*/ )
		{
			if( pRecord->res.pMex )
			{
				pRecord->res.pMex->Release();
				delete pRecord->res.pMex;
				pRecord->res.pMex = NULL;
			}

			if( pRecord->res.pMexCfg )
			{
				delete pRecord->res.pMexCfg;
				pRecord->res.pMexCfg = NULL;
			}


			pRecord->res.bDestroying = FALSE;
			pRecord->res.dwStartDestroyTime = HQ_TimeGetTime();
			pRecord->res.bStartDestroying = FALSE;
		}
		delete pRecord;
	}
	m_RecordMgr.clear();
	EndGuard
	LeaveCriticalSection( &gs_MexResMgrFileCS );
	LeaveCriticalSection( &gs_MexResMgrIDCS );
	unguard;
}
BOOL MexResMgr::LoadFromDirectory( const char* pszDir )
{
	guardfunc;
	char szCommand[1024];
	char szListFile[256] = "filelist.txt";
	sprintf( szCommand, 
		"dir %s\\*%s /s /b  > %s", 
		pszDir, 
		".mex",
		szListFile );
	system( szCommand );

	FILE* fp = fopen( szListFile, "r" );
	if( !fp )
	{
		sprintf( szCommand, 
			"dir %s\\*%s /s /b  > %s", 
			pszDir, 
			".MEX2",
			szListFile );
		system( szCommand );
		fp = fopen( szListFile, "r" );
	}
	if( fp )
	{
		// 去掉全局路径名+字符'\\'
		int nSkipLength = strlen( pszDir )+1;
		char s[MAX_PATH];
		int id = 1;
		while( fgets( s, 256, fp ) )
		{

			int nLength = strlen( s );
			if( s[nLength-1] == '\n' )
				s[nLength-1] = 0;
			AddExternalFile( &s[nSkipLength] );
		}
		fclose( fp );
	}		
	return TRUE;
	unguard;
}

BOOL MexResMgr::AddFile( const char* pszFilename, int nId, const char* pszHeadPicture, bool bRemoveWhenChangeMap /*= true*/ )
{
	if( nId < 0 )
	{
		assert( false );
		return FALSE;
	}
	std::string _temp = pszFilename;
  if(_temp.find("18") != string::npos)
	{
		int i =1;
	}
	Record* pRecord = MeNew Record;
	strcpy( pRecord->szFilename, pszFilename );
	pRecord->nId = nId;
	pRecord->headPicture = pszHeadPicture;
	pRecord->bRemoveWhenChangeMap = bRemoveWhenChangeMap;
	pRecord->res.dwStartDestroyTime = HQ_TimeGetTime();

	LockMexResMgrIDCS();
	BeginGuard
	m_RecordMgr.insert(std::map<int,Record*>::value_type( nId, pRecord )) ;
	EndGuard
	LeaveCriticalSection( &gs_MexResMgrIDCS );

    std::string strFile = pszFilename;
    // strFile相同，但model.config里配的nId不同，会造成m_RecordMgr比m_mapRecords个数多
	LockMexResMgrFileCS();
	BeginGuard
	m_mapRecords.insert( std::map<std::string, Record*>::value_type( strFile, pRecord) );
	EndGuard
	LeaveCriticalSection( &gs_MexResMgrFileCS );
	return TRUE;
	unguard;
}
int	MexResMgr::AddExternalFile( const char* pszFilename )
{
	guardfunc;	
//	CSALocker locker(this);

    if ( ::GetFileAttributes(pszFilename) == FILE_ATTRIBUTE_DIRECTORY )
    {
        return -1;
    }

    if (Md5Manager::Instance().IsMD5Validate())
    {
        if ( !Md5Manager::Instance().ValidateMD5( pszFilename ) )
        {
            Md5Manager::Instance().SetMD5CheckRetMap(FALSE);
            std::string error = "Failed: Loading the file ";
            error = error + Md5Manager::Instance().getErrorFilename() + "!";;
            ::MessageBox(NULL, error.c_str(), "Error", MB_OK|MB_ICONERROR);
            return -1;
        }
    }

	std::string strLowerRelativePath;
	GetLowerRelativePath( pszFilename, strLowerRelativePath );

// 	while (!TryEnterCriticalSection( &gs_MexResMgrCS ))
// 	{
// 		Sleep(1);
// 	}
    int oldModelId = GetIdByName( strLowerRelativePath.c_str() );
    if( oldModelId != -1 )
	{
		//LeaveCriticalSection( &gs_MexResMgrCS );
        return oldModelId;
	}
////	char 	_strlwr(pszFilename);
//	Record* pFound = (Record*)m_Finder.GetDstByName( pszFilename );
//	if(  pFound )
//	{
//		//if( pFound->IsTimeCtlDie() )
//		{
//			//重生
//			//pFound->dwBornTime = HQ_TimeGetTime();
//		}
//		return pFound->nId;
//	}

    // 用小写的文件名
	if( AddFile( strLowerRelativePath.c_str(), m_dwExternalBase ) )
	{
		//BOOL bIsEffect = FALSE;

		//static const char szEffDir[] = "data\\MEX\\magic";
		//int nLen = strlen( szEffDir );


		// 看看是否是特效
		//if( strnicmp( pszFilename, szEffDir, nLen ) == 0 )


		////if( strstr( pszFile, szEffDir ) )
		////{
		////	bIsEffect = TRUE;
		////}



		//pFound = GetRecord( m_dwExternalBase );
		//if( bIsEffect )
		//{
		//	//出生
		////	pFound->SetLiftType(MexResMgr::eMexAction_LiftForm);
		////	pFound->dwBornTime = HQ_TimeGetTime();
		//}
		//m_Finder.Register( pszFilename, pFound );
		int nId = m_dwExternalBase++;
		
		//LeaveCriticalSection( &gs_MexResMgrCS );
		return nId;
	}

	//LeaveCriticalSection( &gs_MexResMgrCS );
	return -1;
	unguard;
}
BOOL MexResMgr::LoadFromSlk( const char* pszFilename )
{
	guardfunc;
	////return TRUE;
	//CSlkReader r;
	//if( !r.ReadFromFile( (char*)pszFilename ) )
	//{
	//	assert(false);
	//	return FALSE;
	//}

	//int nLine = 2;
	//int iRet;
	//while( CSlkReader::ret_readover != ( iRet = r.GotoNextLine( nLine++ ) ) )
	//{
	//	if( CSlkReader::ret_nothisline == iRet )
	//		continue;
	//	//Record record;
	//	CSlkReader::SField* field;
	//	field = r.GetFieldOfLine( 2 );
	//	if( !field )
	//		continue;
	//	DWORD dwId = field->data.iValue;
	//	field = r.GetFieldOfLine( 3 );
	//	if( !field )
	//		continue;
	//	char szFilename[MAX_PATH];
	//	strcpy( szFilename, field->data.szValue );

 //       std::string headPicture("Data/Ui/HeadPicture/unkown_t.dds");
 //       field = r.GetFieldOfLine( 4 );
 //       if (field)
 //       {
 //           headPicture = field->data.szValue;
 //       }

	//	AddFile( szFilename, dwId, headPicture.c_str() );
	//	if( m_pfnLoadingCallBack )
	//	{
	//		m_pfnLoadingCallBack( szFilename );
	//	}
	//}

//     char pszFullPath[MAX_PATH];
//     sprintf(pszFullPath, "%s\\%s", GetRootPath(), pszFilename);
//     if( !theModelConfig.LoadModelConfig(pszFullPath) )
//     {
//         assert(false && "Model.config读取文件出错");
//         return FALSE;
//     }
//     ModelConfig::modeliter iter;
//     if( theModelConfig.m_mapModelData.size() > 0 )
//     {
//         for(iter = theModelConfig.m_mapModelData.begin(); iter != theModelConfig.m_mapModelData.end(); ++iter)
//         {
//             AddFile( iter->second.FilePath.c_str(), iter->first, iter->second.HeadPicture.c_str(), false );
//             if( m_pfnLoadingCallBack )
//             {
//                 m_pfnLoadingCallBack( iter->second.FilePath.c_str() );
//             }
//         }
//     }

	return TRUE;
	unguard;
}

MexResMgr::Record* MexResMgr::GetRecord( DWORD nModelId)
{
	guardfunc;
	LockMexResMgrIDCS();
	MexResMgr::Record* pRecord = 0;
	BeginGuard
	std::map<int,Record*>::iterator iter = m_RecordMgr.find( nModelId );
	if (iter == m_RecordMgr.end())
	{
		LeaveCriticalSection( &gs_MexResMgrIDCS );
		return NULL;
	}
	pRecord = iter->second;
	EndGuard
	LeaveCriticalSection( &gs_MexResMgrIDCS );
	return pRecord;
	unguard;
}
IMex* MexResMgr::GetModel( DWORD dwModelId )
{
	guardfunc;
	Record* r = GetRecord( dwModelId );
	if( !r )
		return NULL;
	return r->res.pMex;
	unguard;
}

// IRenderable* MexResMgr::GetCharEquipChunk( int nPartId, DWORD dwModelId )
// {
// 	guardfunc;
// 	if( nPartId < 0 || nPartId >= CStdCharSkeleton::eMaxPart )
// 		return NULL;
// 	Record* pRecord = GetRecord( dwModelId );
// 	if( !pRecord )
// 		return NULL;
// 	if( !pRecord->res.pMex )
// 		return NULL;
// 	return pRecord->res.pMex->GetGeometry()->GetChunk(nPartId);
// 
// 	//return NULL;
// 	unguard;
// }
// BOOL MexResMgr::CreateActionTree( HWND hTree )
// {
// 	guardfunc;
// 	TVINSERTSTRUCT	is;
// 	ZeroMemory(&is,sizeof(TVINSERTSTRUCT));
// 
// 	is.item.mask = TVIF_TEXT | TVIF_PARAM;
// 	is.item.lParam = 0;
// 	is.item.pszText = "ArabianNights Actions";
// 	is.hParent = NULL;
// 
// 	HTREEITEM  hRoot = TreeView_InsertItem(hTree,&is);
// 	HTREEITEM	hparent,hchild = hRoot ;
// 
// 	//for(DWORD j=0;j<g_mapActionRecord.size();++j)
// 	std::map<DWORD, MoreAction::SRecord>::iterator it;
// 	int j = 0;
// 	for( it = MoreAction::g_mapActionRecord.begin(); 
// 		it != MoreAction::g_mapActionRecord.end(); it++, j++ )
// 	{
// 		MoreAction::SRecord* pRecord = &it->second;
// 		//   added 2004.06.09
// 		if( m_pfnLoadingCallBack )
// 		{
// 			//char s[MAX_PATH];
// 			//sprintf( s, "Creating Action Tree %s.", pRecord->szName );
// 			m_pfnLoadingCallBack( pRecord->szName );
// 		}
// 		if( 1 )
// 		{	
// 			//char* p = m_vectorRecord[j].szFilename;
// 			//m_pszCurFilename = pRecord->szName;
// 			char* p = pRecord->szName;
// 			char tempstr[MAX_PATH] = {0};
// 			char	str2[MAX_PATH] = {0};
// 
// 			hparent = hRoot;
// 
// 			while(*p != 0x00)
// 			{
// 				int n=0;
// 
// 				while(*p != '\\' && *p != 0x00 ) tempstr[n++] = *p++;
// 
// 				tempstr[n] = 0x00;
// 
// 				if(*p == 0x00)
// 					break;
// 
// 				p++;
// 
// 
// 				BOOL found = false;
// 				hchild = TreeView_GetChild(hTree,hparent);
// 				while(hchild && !found)
// 				{
// 					TVITEM item;
// 					str2[0] = 0x00;
// 
// 					item.mask = TVIF_TEXT;
// 					item.hItem = hchild;
// 					item.pszText = str2;
// 					item.cchTextMax = MAX_PATH;
// 
// 					TreeView_GetItem(hTree,&item);
// 
// 					if(!stricmp(tempstr,str2))
// 						found = true;
// 					else
// 						hchild = TreeView_GetNextSibling(hTree,hchild);
// 				}
// 
// 				if(!found)
// 				{
// 					is.item.lParam = 0;
// 					is.item.pszText = tempstr;
// 					is.hParent = hparent;
// 
// 					hchild = hparent = TreeView_InsertItem(hTree,&is);
// 				}
// 
// 				hparent = hchild;
// 			}
// 
// 			is.item.lParam = (LPARAM)pRecord;
// 			is.item.pszText = tempstr;
// 			is.hParent = hchild;
// 
// 			HTREEITEM hItem = TreeView_InsertItem(hTree,&is);
// 		}
// 	}
// 	return TRUE;
// 	unguard;
// }
// BOOL MexResMgr::CreateTree( HWND hTree )
// {
// 	guardfunc;
// 	TVINSERTSTRUCT	is;
// 	ZeroMemory(&is,sizeof(TVINSERTSTRUCT));
// 	
// 	is.item.mask = TVIF_TEXT | TVIF_PARAM;
// 	is.item.lParam = 0;
// 	is.item.pszText = "所有模型动画";
// 	is.hParent = NULL;
// 	
// 	HTREEITEM  hRoot = TreeView_InsertItem(hTree,&is);
// 	HTREEITEM	hparent,hchild = hRoot ;
// 	
// 	std::map<int,Record*>::iterator iter = m_RecordMgr.begin();
// 	for (; iter != m_RecordMgr.end(); ++iter)
// 	{
// 		char* p = iter->second->szFilename;
// 
// 		char tempstr[MAX_PATH] = {0};
// 		char	str2[MAX_PATH] = {0};
// 
// 		hparent = hRoot;
// 
// 		while(*p != 0x00)
// 		{
// 			int n=0;
// 
// 			while(*p != '\\' && *p != 0x00 ) tempstr[n++] = *p++;
// 
// 			tempstr[n] = 0x00;
// 
// 			if(*p == 0x00)
// 				break;
// 
// 			p++;
// 
// 
// 			BOOL found = false;
// 			hchild = TreeView_GetChild(hTree,hparent);
// 			while(hchild && !found)
// 			{
// 				TVITEM item;
// 				str2[0] = 0x00;
// 
// 				item.mask = TVIF_TEXT;
// 				item.hItem = hchild;
// 				item.pszText = str2;
// 				item.cchTextMax = MAX_PATH;
// 
// 				TreeView_GetItem(hTree,&item);
// 
// 				if(!stricmp(tempstr,str2))
// 					found = true;
// 				else
// 					hchild = TreeView_GetNextSibling(hTree,hchild);
// 			}
// 
// 			if(!found)
// 			{
// 				is.item.lParam = 0;
// 				is.item.pszText = tempstr;
// 				is.hParent = hparent;
// 
// 				hchild = hparent = TreeView_InsertItem(hTree,&is);
// 			}
// 
// 			hparent = hchild;
// 		}
// 
// 		//is.item.lParam = m_vectorRecord[j].dwId;
// 		is.item.lParam = iter->first;
// 		is.item.pszText = tempstr;
// 		is.hParent = hchild;
// 
// 		HTREEITEM hItem = TreeView_InsertItem(hTree,&is);
// 	}
// 	return TRUE;
// 	unguard;
// }
const char* MexResMgr::GetModelFilename( DWORD dwModelId )
{
	guardfunc;
	Record* r = GetRecord( dwModelId );
	if( !r )
		return NULL;
	return r->szFilename;
	unguard;
}


int MexResMgr::GetIdByName( const char* pszFilename )
{
	guardfunc;
	//Record* pFound = m_Finder.GetDstByName( pszFilename );
	//if( !pFound )
	//	return -1;
	//return pFound->nId;
	//std::vector<Record*> vectorRecord;
	//m_RecordMgr.GetObjects( &vectorRecord );
	//
    // 把m_Records改成map
	//for( int i = 0; i < m_mapRecords.size(); i++ )
	//{
	//	//if( !vectorRecord[i]->szFilename )
	//	//	continue;
	//	if( stricmp( m_mapRecords[i]->szFilename, pszFilename ) == 0 )
	//		return m_mapRecords[i]->nId;
	//}	
    char szBuffer[MAX_PATH] = {0};
    char *pszFile = NULL;

    strncpy( szBuffer, pszFilename, MAX_PATH-1 );
    pszFile = _strlwr(szBuffer);

    std::map<std::string, Record*>::iterator It;
	LockMexResMgrFileCS();
    It = m_mapRecords.find( pszFile );
    if( It != m_mapRecords.end() )
    {
		int nId = It->second->nId;
		LeaveCriticalSection( &gs_MexResMgrFileCS );
        return nId;
    }
	LeaveCriticalSection( &gs_MexResMgrFileCS );

	
	return -1;
	unguard;

}

BOOL MexResMgr::ReallocMexAnimData( int nModelId, int nFrameCount )
{
	Record* record = GetRecord( nModelId );
	if( !record )
		return FALSE;

	return ((Mex2*)record->res.pMex)->ReallocAnimationFrameCount(nFrameCount);
}

BOOL MexResMgr::CombineMexAnimData( int nModelId, int nCombineModelId, BOOL bReleaseCombineMex /*= TRUE*/ )
{
	Record* record = GetRecord( nModelId );
	if( !record )
		return FALSE;
	Record* combine_record = GetRecord( nCombineModelId );
	if( !combine_record )
		return FALSE;

	int nFrameOffset = 0;
	if(((Mex2*)record->res.pMex)->CombineAnimationFromModel(combine_record->res.pMex, nFrameOffset))
	{
		//把record里动画序列合并到combine_record里，并修正combine_record里动画序列（加上偏移量nFrameOffset）
		if( combine_record->res.pMexCfg->CombineCommonSequences(record->res.pMexCfg, nFrameOffset) )
		{
			if( bReleaseCombineMex )
			{
				combine_record->res.pMex->Release();
				delete combine_record->res.pMex;
				combine_record->res.pMex = NULL;

                //if( combine_record->res.pMexCfg )
                //{
                //    delete combine_record->res.pMexCfg;
                //    combine_record->res.pMexCfg = NULL;
                //}
			}
			return TRUE;
		}
	}
	return FALSE;
}

void MexResMgr::BuildKeyFrameTimeList( int nModelId )
{
	Record* record = GetRecord( nModelId );
	if( !record )
		return;

	((Mex2*)record->res.pMex)->BuildKeyFrameTimeList();
}
BOOL MexResMgr::PreloadModel( int nModelId )
{
	guardfunc;
	// 根据id查找记录
	Record* pRecord = GetRecord( nModelId );
	if( !pRecord )
	{
		return NULL;
	}

	// 存在，但是没有任何引用
	Res* pRes = &pRecord->res;
	if( pRes->pMex )
	{
		// 已加载
		// 清除删除标志
		pRecord->res.bDestroying = FALSE;
		pRecord->res.bStartDestroying = FALSE;
		return TRUE;
	}

	guard(MexResMgr::PreloadModel::Res);
	if( pRecord->GetRefCount() == 0 &&
		pRes->pMex == NULL )
	{
		assert( pRes->pMexCfg == NULL );
		pRecord->LoadRes();
	}
	unguard;
	return TRUE;
	unguard;
}

void MexResMgr::RemoveUnusedModelWhenChangeMap()
{
	guardfunc;
//	CSALocker locker(this);
	LockMexResMgrIDCS();
	LockMexResMgrFileCS();

	BeginGuard
	DWORD dwCurTime = HQ_TimeGetTime();

	if( m_mapRecords.size() > 0 )
	{
		std::map<std::string, Record*>::iterator it = m_mapRecords.begin();
		while( it != m_mapRecords.end() )
		{
			Record* pRecord = it->second;
            // pRecord不应该为空
            if( !pRecord )
            {
                ++it;
                continue;
            }

			if( pRecord->GetRefCount() == 0 /*&& !pRecord->res.bDestroying*/ )
			{
				guard(deleteRes);
				if( pRecord->res.pMex )
				{
					guard(deleteResMex);
					pRecord->res.pMex->Release();
					delete pRecord->res.pMex;
					pRecord->res.pMex = NULL;
					unguard;
				}

				if( pRecord->res.pMexCfg )
				{
					guard(deleteResMexCfg);
					delete pRecord->res.pMexCfg;
					pRecord->res.pMexCfg = NULL;
					unguard;
				}

				unguard;

				pRecord->res.bDestroying = FALSE;
				pRecord->res.dwStartDestroyTime = dwCurTime;
				pRecord->res.bStartDestroying = FALSE;

//                 if( pRecord->bRemoveWhenChangeMap )
//                 {
//                     Record* pSource = GetRecord( pRecord->nId );
//                     if( pSource && pSource == pRecord )
// 					{
//                         m_RecordMgr.erase( pRecord->nId );
// 					}
//                     delete pRecord;
//                     pRecord = NULL;
//                     it = m_mapRecords.erase(it);
//                 }
//                 else
//                     ++it;
			}
//             else
                ++it;
		}
	}
	// 删除m_mapRecords中没有，但m_RecordMgr有的Record，只有文件名相同但model ID不同才会这样
	std::vector<int> vecDelRecords;
	std::map<int,Record*>::iterator iter = m_RecordMgr.begin();
	for (; iter != m_RecordMgr.end(); ++iter)
	{
		Record* pRecord = iter->second;
		if( pRecord && pRecord->GetRefCount() == 0 /*&& !pRecord->res.bDestroying*/ )
		{
			guard(deleteRes);
			if( pRecord->res.pMex )
			{
				guard(deleteResMex);
				pRecord->res.pMex->Release();
				delete pRecord->res.pMex;
				pRecord->res.pMex = NULL;
				unguard;
			}

			if( pRecord->res.pMexCfg )
			{
				guard(deleteResMexCfg);
				delete pRecord->res.pMexCfg;
				pRecord->res.pMexCfg = NULL;
				unguard;
			}

			unguard;

			pRecord->res.bDestroying = FALSE;
			pRecord->res.dwStartDestroyTime = dwCurTime;
			pRecord->res.bStartDestroying = FALSE;

// 			if( pRecord->bRemoveWhenChangeMap )
// 			{
// 				vecDelRecords.push_back(pRecord->nId);
// 				delete pRecord;
// 				pRecord = NULL;
// 			}
		}
	}

	for(int i=0; i<vecDelRecords.size(); ++i)
	{
		m_RecordMgr.erase(vecDelRecords[i]);
	}
	EndGuard
	LeaveCriticalSection( &gs_MexResMgrFileCS );
	LeaveCriticalSection( &gs_MexResMgrIDCS );
	unguard;
}

int MexResMgr::Record::GetCfgFrameCount()
{
	if( !res.pMex )
		return 0;

	IMex* pMex = res.pMex;
	int nFrameCount = 0;
	if( pMex->GetSkeleton() )
	{
		IMexBone* pBone = pMex->GetSkeleton()->GetBone(0);
		if( pBone )
		{
			nFrameCount = pBone->GetFrameCount();
		}
	}
	return nFrameCount;
}

void MexResMgr::Record::IncRefCount( bool bKeepOldData /*= false*/ )
{
	InterlockedIncrement( (LONG*)&m_uiRefCount );
	if (GetRefCount() > 0 )
	{
		if (res.pMex == NULL)
		{
			LoadRes( bKeepOldData );
		}
		else
		{
			res.bDestroying = FALSE;
			res.bStartDestroying = FALSE;
		}

	}
}

void MexResMgr::Record::DecRefCount()
{
	if (m_uiRefCount != 0)
	{
		InterlockedDecrement( (LONG*)&m_uiRefCount );
	}
	if (GetRefCount() == 0)
	{
		Release();
	}
}

void MexResMgr::Record::LoadRes( bool bKeepOldData /*= false*/ )
{
	res.pMex = GetEngine()->CreateMex();
	res.pMexCfg = MeNew MexCfg;

	char szFullFilename[MAX_PATH] = {0};
	const char *pszRootPath = GetRootPath();
	if (szFilename[1] == ':')
		strcpy(szFullFilename, szFilename);
	else
		sprintf(szFullFilename, "%s\\%s", pszRootPath, szFilename);

	BOOL bOK = FALSE;
	guard(MexResMgr::CreateModel::Load);
	if (!res.pMex)
		return;

	DWORD dwFlag = 0;
	res.pMex->SetKeepOldData( bKeepOldData );
	bOK = res.pMex->LoadFromFile( szFullFilename, dwFlag, false );

	guard(MexResMgr::CreateModel::OK);
	if (!bOK)
	{
		res.pMex->Release();
		delete res.pMex;
		res.pMex = NULL;
		if (res.pMexCfg != NULL)
		{
			delete res.pMexCfg;
			res.pMexCfg = NULL;
		}

		char temp[MAX_PATH] = {0};
		sprintf_s(temp, MAX_PATH, "模型加载失败: %s\n", szFullFilename);
		OutputDebugString(temp);
		return;
	}

	char s[MAX_PATH]  = {0};
	Common::_tstring strAniFileName( szFilename );
	strAniFileName.Replace( Common::_tstring( ".mex" ), Common::_tstring( ".ani" ) );

	char szFullPath[MAX_PATH]  = {0};
	if (strlen(pszRootPath) > 0)
		sprintf_s( szFullPath, MAX_PATH - 1, "%s\\%s", pszRootPath, strAniFileName.c_str() );			
	else
		strcpy( szFullPath, strAniFileName.c_str() );

	if (!res.pMexCfg->LoadFromFile(szFullPath))
	{
		MexCfgSequence* sequence = MeNew MexCfgSequence;
		sequence->m_spAnimName.SetString( "none" );
		sequence->m_npStartFrameId.SetNumber( res.pMex->GetSequence()->GetStartFrameID() );
		sequence->m_npEndFrameId.SetNumber( res.pMex->GetSequence()->GetEndFrameID() );
		sequence->m_npHasLightTrack.SetNumber( 1 );
		res.pMexCfg->m_sequences.m_vectorSequence.push_back( sequence );
	}

	int nVectorSequenceSize = res.pMexCfg->m_sequences.m_vectorSequence.size();
	for (int i = 0; i < nVectorSequenceSize; i++)
	{
		MexCfgSequence* sequence = res.pMexCfg->m_sequences.m_vectorSequence[i];

		int nFrameCount = 0;
		int nStartFrameID = sequence->m_npStartFrameId.GetNumber(); //动作的开始帧数
		int nEndFrameID = sequence->m_npEndFrameId.GetNumber(); //动作的结束帧数

		if (res.pMex->GetSkeleton())
		{
			IMexBone* pBone = res.pMex->GetSkeleton()->GetBone(0);
			if (pBone)
			{
				nFrameCount = pBone->GetFrameCount();
			}
		}

		if (nStartFrameID > nFrameCount - 1)
		{
			assert( "Very Terrible Error!!!!!!!!" && false );
			nStartFrameID = nFrameCount - 1;
		}

		if (nStartFrameID < 0)
		{
			assert( "Very Terrible Error!!!!!!!!" && false );
			nStartFrameID = 0;
		}

		if (nEndFrameID > nFrameCount - 1)
		{
			assert( "Very Terrible Error!!!!!!!!" && false );
			nEndFrameID = nFrameCount - 1;
		}

		if (nEndFrameID < 0)
		{
			assert( "Very Terrible Error!!!!!!!!" && false );
			nEndFrameID = 0;
		}

		if (nStartFrameID > nEndFrameID)
		{
			assert( "Very Terrible Error!!!!!!!!" && false );
			nStartFrameID = nEndFrameID;
		}

		sequence->m_npStartFrameId.SetNumber( nStartFrameID );
		sequence->m_npEndFrameId.SetNumber( nEndFrameID );
	}

	IMexGeometry* pGeomtry = res.pMex->GetGeometry();
	IMexTextures* pTextures = res.pMex->GetTextures();

	MexCfgAvatarSetting* pSetting = res.pMexCfg->m_AvatarSettings.FindByName( DEFAULT_AVATARSETTING_NAME );
	if (pGeomtry)
	{
		DWORD dwFlag = eMexCfg_SubsetVisible;
		for( int nSubset = 0; nSubset < pGeomtry->GetChunkCount(); nSubset++  )
		{
			pSetting->m_vectorSubsetFlag.push_back( dwFlag );	
		}
	}
	if (pTextures)
	{
		for( int nTexture = 0; nTexture < pTextures->GetTextureCount(); nTexture++ )
		{
			MexCfgAvatarSetting::ReplaceableTexture rt;
			strcpy( rt.szFileName, pTextures->GetTexture(nTexture)->GetName() );
			pSetting->m_vectorReplaceableTexture.push_back( rt );
		}

	}
	sprintf( s, "%s.bowstring", szFullFilename );
	CBowStringBindingMgr::Instance()->LoadBindingListFromFile(nId,s);
	unguard;
}
void MexResMgr::OnDeviceLost()
{
	LockMexResMgrIDCS();
	BeginGuard
	std::map<int,Record*>::iterator iter = m_RecordMgr.begin();
	for (; iter != m_RecordMgr.end(); ++iter)
	{
		Record* pRecord = iter->second;
		if (pRecord->res.pMex)
		{
			pRecord->res.pMex->OnDeviceLost();
		}
	}
	EndGuard
	LeaveCriticalSection( &gs_MexResMgrIDCS );
}

void MexResMgr::OnDeviceReset()
{
	LockMexResMgrIDCS();
	BeginGuard
	std::map<int,Record*>::iterator iter = m_RecordMgr.begin();
	for (; iter != m_RecordMgr.end(); ++iter)
	{
		Record* pRecord = iter->second;
		if (pRecord->res.pMex)
		{
			pRecord->res.pMex->OnDeviceReset();
		}
	}
	EndGuard
	LeaveCriticalSection( &gs_MexResMgrIDCS );
}

bool MexResMgr::TryLock()
{
	if( TryEnterCriticalSection( &gs_MexResMgrIDCS ) )
		if( TryEnterCriticalSection( &gs_MexResMgrFileCS ) )
			return true;
		else
			LeaveCriticalSection( &gs_MexResMgrIDCS );

	return false;		
}

void MexResMgr::UnLock()
{
	LeaveCriticalSection( &gs_MexResMgrFileCS );
	LeaveCriticalSection( &gs_MexResMgrIDCS );
}