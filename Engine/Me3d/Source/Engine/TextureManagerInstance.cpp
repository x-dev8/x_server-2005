#include "Me3d/Me3d.h"
#include "Me3d/Engine/Engine.h"
#include "Me3d/Engine/TextureManagerInstance.h"
#include "Me3d/Engine/TextureDx8.h"
#include "Me3d/Global.h"
#include "FilePath.h"
#include "FuncPerformanceLog.h"
#include "helper.h"
#include "Me3d/hrp.h"
#include "MapStrToID.h"
// #include "VirtualFileSystem/vfs.h"
#include <assert.h>
#include <stdio.h>
#include "Dxsdk/D3D9.h"
#include "Dxsdk/D3DX9Math.h"
#include <process.h>
#include "../filepacket/packet_interface.h"
//#include "Launcher/DataLauncher.h"

//extern FileIO::CVFS g_TextureVFS;
extern char* GetFileName( const char* pszPath );
extern const char* GetRootPath();
static int gs_nSerialNo = 0;
static CRITICAL_SECTION gs_TextureLoadingCS;
static BOOL gs_bTextureMgrWillDestroy = FALSE;
static BOOL gs_bTextureLoadingThreadTerminated = FALSE;
static std::vector<CHRTextureLoadingReq> gs_TextureLoadingReqsCache;
static std::vector<CHRTextureLoadingReq> gs_TextureLoadingReqs;
static std::vector<CHRTextureLoadingReq> gs_TextureLoadingAcks;
BOOL	g_bUserTextureFinder = TRUE;
CMapStrToIDMgr g_TextureFinder;

static HANDLE s_hTextureLoadingEvent = NULL;

//////////////////////////////////////////////////////////////////////////
MexReplaceableTextureProj::MexReplaceableTextureProj():
m_bLoaded(FALSE)
{
	guardfunc;
	unguard;
}
MexReplaceableTextureProj::~MexReplaceableTextureProj()
{
	guardfunc;
	assert( m_bLoaded == FALSE );
	unguard;
}
void MexReplaceableTextureProj::SetTextureCount( int nTextureCount )
{
	guardfunc;
	m_vectorRenderTextureID.reserve( nTextureCount );
	m_vectorRenderTextureID.resize( nTextureCount );
	for( int nTexture = 0; nTexture < nTextureCount; nTexture++ )
		m_vectorRenderTextureID[nTexture] = -1;
	unguard;
}
BOOL MexReplaceableTextureProj::SetRenderTextureID( int nTexture, int nRenderTextureID )
{
	guardfunc;
	if( nTexture < 0 || nTexture >= m_vectorRenderTextureID.size() )
	{
		assert( false );
		return FALSE;
	}
	m_vectorRenderTextureID[nTexture] = nRenderTextureID;
	return TRUE;
	unguard;
}
short MexReplaceableTextureProj::GetRenderTextureID( int nTexture )
{
	guardfunc;
	if( nTexture < 0 || nTexture >= m_vectorRenderTextureID.size() )
	{
		//assert( false );
		return -1;
	}
	return m_vectorRenderTextureID[nTexture];
	unguard;
}
short	MexReplaceableTextureProj::RegisterTexture( const char* pszMexFilename, const char* pszTextureFilename, BOOL bMult )
{
	guardfunc;
	CFilePath path;

	path.Split( pszMexFilename );
	char szDir[MAX_PATH];
	sprintf( szDir, "%s%s", path.GetDrive(), path.GetDirectory() );

	path.Split( pszTextureFilename );
	short stTextureID = -1;
	if( pszTextureFilename[0] == 0 )
	{
		stTextureID = GetEngine()->GetTextureManager()->RegisterTexture( "data\\teamcolor03.tga", FALSE ,TRUE);
	}
	else
	{
		char szFilename[MAX_PATH] = {0};

		//pszTextureFilename

		if( GetEngine()->IsUseAbstractPath() )
		{
			stTextureID = GetEngine()->GetTextureManager()->RegisterTexture( 
				pszTextureFilename, bMult,TRUE );
		}
		else
		{
			sprintf( szFilename, "%s%s%s", szDir, path.GetFileName(), path.GetExt() );
			stTextureID = GetEngine()->GetTextureManager()->RegisterTexture( szFilename, bMult ,TRUE);
		}
	}
	return stTextureID;
	unguard;
}
void MexReplaceableTextureProj::UnRegisterTextures()
{
	guardfunc;
	for( int nTexture = 0; nTexture < m_vectorRenderTextureID.size(); nTexture++ )
	{
		int nRenderTextureID = m_vectorRenderTextureID[nTexture];
		if( nRenderTextureID != -1 )
		{
			if( GetEngine() && GetEngine()->GetTextureManager() )
				GetEngine()->GetTextureManager()->UnRegisterTexture( nRenderTextureID );
		}
	}
	m_vectorRenderTextureID.clear();
	unguard;
}

BOOL MexReplaceableTextureProj::ReplaceTexture( short shTextureID, const char* pszMexFilename, const char* pszTextureFilename, BOOL bMult /*= false */ )
{
	if( NULL == pszMexFilename || NULL == pszTextureFilename )
		return FALSE;

	if( shTextureID >= m_vectorRenderTextureID.size() )
		return FALSE;

	int shOldRenderTextureID = m_vectorRenderTextureID[shTextureID];
	int shNewRenderTextureID = RegisterTexture(pszMexFilename, pszTextureFilename, bMult);
	if( shNewRenderTextureID != -1 )
	{
		if( shOldRenderTextureID != -1 )
		{
			if( GetEngine() && GetEngine()->GetTextureManager() )
				GetEngine()->GetTextureManager()->UnRegisterTexture( shOldRenderTextureID );
		}
		m_vectorRenderTextureID[shTextureID] = shNewRenderTextureID;
		return TRUE;
	}
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////
BOOL PostTextureLoadingReq( CHRTextureLoadingReq& req )
{
	guardfunc;
	gs_TextureLoadingReqsCache.push_back(req);
// 	EnterCriticalSection( &gs_TextureLoadingCS );
// 	gs_TextureLoadingReqs.push_back( req );
// 	LeaveCriticalSection( &gs_TextureLoadingCS );
	return TRUE;
	unguard;
}
BOOL PostTextureLoadingAck( CHRTextureLoadingReq& req )
{
	guardfunc;
	EnterCriticalSection( &gs_TextureLoadingCS );
	gs_TextureLoadingAcks.push_back( req );
	LeaveCriticalSection( &gs_TextureLoadingCS );
	return TRUE;
	unguard;
}

BOOL CreateFromMemory( const char* pszFilename, LPDIRECT3DTEXTURE9* ppD3DTexture )
{
//	FileIO::CVFSUnit unit;
	guardfunc;
	IRenderer* RI = GetEngine()->GetRenderer();
	HRESULT hr = S_OK;
	size_t size = 0;
// 	if( g_TextureVFS.IsOpen() )
// 	{
// 		if (!g_TextureVFS.GetUnitLength(pszFilename, size))
// 		{
// 			return false;
// 		}
// 		void *pData = MeDefaultNew unsigned char[size];
// 		if (!g_TextureVFS.GetUnit(pszFilename, pData, size))
// 		{
// 			delete []pData;
// 			pData = NULL;
// 			return FALSE;
// 		}
// 		// = (void*)unit.GetData();
// 		if( pData )
// 		{
// 			if( FAILED( hr = HrCreateTextureFromFileInMemory( RI, pData, 
// 				size, ppD3DTexture ) ) )
// 			{
// 				delete []pData;
// 				pData = NULL;
// 				return FALSE;
// 			}		
// 		}
// 		else
// 		{
// 			delete []pData;
// 			pData = NULL;
// 			return FALSE;
// 		}
// 		delete []pData;
// 		pData = NULL;
// 	}
// 	else
	{
		return FALSE;
	}
	return TRUE;
	unguard;
}

BOOL CreateTextureFromReq( IRenderer* RI, CHRTextureLoadingReq* pReq )
{
	guardfunc;
	char szFileName[MAX_PATH] = {0};
	HelperFunc::SafeNCpy( szFileName, pReq->m_szFileName, MAX_PATH );

	CFilePath path;
	path.Split( szFileName );

	BOOL bLoaded = FALSE;
	if( !bLoaded )
	{

		if( _stricmp( path.GetExt(), ".tga" ) != 0 &&
			_stricmp( path.GetExt(), ".jpg" ) != 0 &&
			_stricmp( path.GetExt(), ".bmp" ) != 0 &&
			_stricmp( path.GetExt(), ".dds" ) != 0 )
		{
			//assert( false && "TextureDx8, only create tga, jpg format textures" );
			return FALSE;
		}
		
		BOOL bDDSExist = FALSE;
		HRESULT hr = 0;
		{
			//先创建DDSFile				
			char szDDSFileName[MAX_PATH];
			int nLen = strlen( szFileName );
			if( nLen <= 4 )
				sprintf( szDDSFileName, "%s.dds", szFileName );
			else
			{
				strcpy( szDDSFileName, szFileName );
				strcpy( &szDDSFileName[nLen-4], ".dds" );
			}
			//if( CFilePath::IsExist( szDDSFileName )
			//	|| g_TextureVFS.UnitIsExist(szDDSFileName)
			//	|| g_TextureVFS.UnitIsExist(szFileName) )

			//{
			//	bDDSExist = TRUE;
			//}
			//else 
			//	return FALSE;	
			// 如果dds也创建失败了
			if( FAILED( hr = HrCreateTextureFromFile( RI, szDDSFileName, &pReq->m_pD3DTexture, pReq->m_bMipmapFromFile ) ) )
			{	
				// 如果创建失败
				if( FAILED( hr = HrCreateTextureFromFile( RI, szFileName, &pReq->m_pD3DTexture, pReq->m_bMipmapFromFile ) ) )
				{
					if( !CreateFromMemory( szFileName, &pReq->m_pD3DTexture  ) )
					{
						if( !CreateFromMemory( szDDSFileName, &pReq->m_pD3DTexture ) )
						{
							return FALSE;
						}
					}
				}

			}
		}
	}
	return TRUE;
	unguard;
}

void TextureLoadingThread(void* p)
{
	guardfunc;
//	LPDIRECT3DDEVICE9 pD3DDevice = (LPDIRECT3DDEVICE9)p;
	IRenderer* RI = GetEngine()->GetRenderer();
	// 当主线程要结束了
	while( !gs_bTextureMgrWillDestroy )
	{
		CHRTextureLoadingReq req;
		BOOL bHasReq = FALSE;
		EnterCriticalSection( &gs_TextureLoadingCS );
		if( gs_TextureLoadingReqs.size() > 0 )
		{
			bHasReq = TRUE;
			req = gs_TextureLoadingReqs[0];
			gs_TextureLoadingReqs.erase( gs_TextureLoadingReqs.begin() );
		}
		LeaveCriticalSection( &gs_TextureLoadingCS );
		if( bHasReq )
		{
			if( CreateTextureFromReq( RI, &req ) )
			{
				PostTextureLoadingAck( req );
			}
		}
		else
		{
			WaitForSingleObject( s_hTextureLoadingEvent, INFINITE );
		}
		
	}
	// 这个线程结束了
	gs_bTextureLoadingThreadTerminated = TRUE;
	unguard;
}
CHRTextureLoadingReq::CHRTextureLoadingReq():
m_nSerialNo(-1),
m_bMipmapFromFile(TRUE),
m_nTextureID(-1),
m_pD3DTexture(NULL)
{
	guardfunc;
	m_szFileName[0] = 0;
	unguard;
}
ITexture* CHRTextureManagerInstance::m_textures[CHRTextureManagerInstance::eMaxTexture];
BOOL CHRTextureManagerInstance::StartTextureLoadingThread()
{
	guardfunc;
	gs_bTextureMgrWillDestroy = FALSE;
	gs_bTextureLoadingThreadTerminated = FALSE;
	//InitializeCriticalSection( &gs_TextureLoadingCS );
	_beginthread( TextureLoadingThread, NULL, GetEngine()->GetRenderer()->GetRealDevice() );
	s_hTextureLoadingEvent = ::CreateEvent( 
		NULL,         // default security attributes
		FALSE,         // auto-reset event
		FALSE,         // initial state is signaled
		NULL  // object name
		); 
	return TRUE;
	unguard;
}
void CHRTextureManagerInstance::CloseTextureLoadingThread()
{
	guardfunc;
	// 告知纹理加载线程，管理器要关闭了
	gs_bTextureMgrWillDestroy = TRUE;
	SetEvent(s_hTextureLoadingEvent);
	while( !gs_bTextureLoadingThreadTerminated )
		Sleep( 1 );

	LockTextureManager();
	gs_TextureLoadingReqsCache.clear();
	// 清除请求队列
	gs_TextureLoadingReqs.clear();
	// 清除已经完成的队列,此时还未被管理器取走,所以可以直接释放
	for( int nLeft = 0; nLeft < gs_TextureLoadingAcks.size(); nLeft++ )
	{
		CHRTextureLoadingReq* pReq = &gs_TextureLoadingAcks[nLeft];
		if( pReq->m_pD3DTexture )
			pReq->m_pD3DTexture->Release();
	}
	gs_TextureLoadingAcks.clear();
	UnLockTextureManager();

	CloseHandle( s_hTextureLoadingEvent );

	//DeleteCriticalSection( &gs_TextureLoadingCS );
	unguard;
}
void CHRTextureManagerInstance::ProcessTextureLoadingThread()
{
	guardfunc;
	MeScopeProfileTextureManagerFun
	if (!TryLockTextureManager())
	{
		return;
	}
	BeginGuard
	for (std::vector<CHRTextureLoadingReq>::iterator iter = gs_TextureLoadingReqsCache.begin();iter != gs_TextureLoadingReqsCache.end();++iter)
	{
		gs_TextureLoadingReqs.push_back(*iter);
	}
	if( !gs_TextureLoadingReqs.empty() )
		::SetEvent( s_hTextureLoadingEvent );

	gs_TextureLoadingReqsCache.clear();
	for( int nLeft = 0; nLeft < gs_TextureLoadingAcks.size(); nLeft++ )
	{
		CHRTextureLoadingReq* pReq = &gs_TextureLoadingAcks[nLeft];
		int nTextureID = pReq->m_nTextureID;
		TextureDx8* pTexture = (TextureDx8*)GetTexture( nTextureID );
		if( !pTexture )
		{
			if( pReq->m_pD3DTexture )
				pReq->m_pD3DTexture->Release();
			continue;
		}
		if( pTexture->GetSerialNo() != -1 &&
			pTexture->GetSerialNo() == pReq->m_nSerialNo  )
		{
			pTexture->m_pd3dTexture = pReq->m_pD3DTexture;
			pTexture->m_bLoaded = TRUE;
		}
		else
		{
			if( pReq->m_pD3DTexture )
				pReq->m_pD3DTexture->Release();
        }

        TextureListeners texListeners = pTexture->getTextureListeners();
        TextureListeners::iterator it, end = texListeners.end();
        for ( it = texListeners.begin(); it != end; ++it )
        {
            (*it)->loadFinished( pTexture);
        }
	}
	gs_TextureLoadingAcks.clear();

	EndGuard
	//Sleep( 1 );
	UnLockTextureManager();
	unguard;
}

BOOL CHRTextureManagerInstance::UnRegisterTexture( short stTextureId )
{
	guardfunc;
	LockTextureManager();
// 	EnterCriticalSection( &gs_TextureLoadingCS );
	BOOL bResult = FALSE;
	if( stTextureId < 0 || stTextureId >= eMaxTexture )
	{
		//assert( false && "texture mgr, unregister texture's id out of range" );
		goto exit_fun;
	}

	if( stTextureId > eMaxTexture && stTextureId < m_nMinTexture )
	{
		m_nMinTexture = stTextureId; 
	}
	
	ITexture* pTexture = m_textures[stTextureId];
	
	if( !pTexture )
	{
	//	assert( false && "texture mgr, unregister texture's slot is NULL" );
		goto exit_fun;
	}

	pTexture->DecRef();
	/**
	流程是：
	如果ref==1，则需要进入准备卸载队列，如果延迟卸载，则减引用，进入轮循过程；
	如果ref!=1，则执行Release，减引用，如果<=0了，则进行删除。
	*/

	if(pTexture->GetRef() == 0)
	{//进入释放队列或者马上释放
		if( pTexture->IsDelayDestory() )
		{
			if( m_bDelayQueue[stTextureId] )
			{
				assert(0);
				goto exit_fun;
			}
			m_bDelayQueue[stTextureId] = true;
		}
	}

	if (!pTexture->IsDelayDestory())
	{
		std::string strTempTexName = pTexture->GetName();
		if( pTexture->Release() )
		{
			if( g_TextureFinder.GetDstByName( strTempTexName.c_str() ) )
				g_TextureFinder.UnRegister( strTempTexName.c_str() );

			m_textures[stTextureId] = NULL;
		}
	}
	bResult = TRUE;
exit_fun:
	UnLockTextureManager();
	return bResult;
	unguard;
}

ITexture* CHRTextureManagerInstance::GetTexture( short stTextureId )
{
	guardfunc;
// 	EnterCriticalSection( &gs_TextureLoadingCS );
	LockTextureManager();
	ITexture* pTexture = NULL;
	if( stTextureId >= 0 && stTextureId < eMaxTexture )
	{
		pTexture = m_textures[stTextureId];
	}
	UnLockTextureManager();
	return pTexture;
	unguard;
}

VOID	CHRTextureManagerInstance::FrameClear()
{
	guardfunc;
	MeScopeProfileTextureManagerFun
	if (!TryLockTextureManager())
	{
		return;
	}
	BeginGuard
	static DWORD dwLastTick = 0;
	static DWORD s_dwCheckTime = 3000;
	static DWORD s_dwKeepTime = 120000;
	if( HQ_TimeGetTime() - dwLastTick < s_dwCheckTime )
	{	
		UnLockTextureManager();
		return;
	}
	dwLastTick = HQ_TimeGetTime();

	for( INT i =0; i<eMaxTexture; i++ )
	{
		if( m_bDelayQueue[i] )
		{	
			ITexture* pTexture = m_textures[i];
			//FindTexture()
			if( pTexture && pTexture->IsDelayDestory() )
			{
				if( ( HQ_TimeGetTime() - pTexture->GetBornTime() ) > s_dwKeepTime )
				{
					pTexture->SetDelayDestroy( FALSE );
					UnRegisterTexture(i);
					m_bDelayQueue[i] = false;
					//pTexture->SetDelayDestroy( TRUE );
				}
			}
		}
	}
	EndGuard
	UnLockTextureManager();

	unguard;
}

ITexture* CHRTextureManagerInstance::CreateTexture()
{
	guardfunc;
	LockTextureManager();
	TextureDx8* pTexture = MeNew TextureDx8;
	pTexture->SetSerialNo( gs_nSerialNo++ );
	//pTexture->Set = HQ_TimeGetTime();

	UnLockTextureManager();
	return pTexture;
	unguard;
}


// short	CHRTextureManagerInstance::RegisterTerrainAlpha( const char* pszFilename, 
// 													DWORD dwWidth, DWORD dwHeight, DWORD dwFormat,
// 													BYTE *byBuffer, DWORD dwSize, DWORD dwPool,BOOL bFromFile )
// {
// 	guardfunc;
// 	EnterCriticalSection( &gs_TextureLoadingCS );
// 	short stIndex = -1;
// 	int nEmptySlotId = -1;
// 	for( int i = eMaxTexture; i < eTerrainTexture; i++ )
// 	{
// 		if( !m_textures[i] )
// 		{
// 			// 第一个空的id
// 			if( nEmptySlotId == -1 )
// 			{
// 				nEmptySlotId = i;
// 			}
// 
// 			continue;
// 		}
// 	}
// 	// 如果空间已满
// 	if( nEmptySlotId == -1 )
// 	{
// 		assert( false && "not enough texture id to use" );
// 		goto exit_fun;
// 	}
// //	goto exit_fun;
// 	ITexture* pTexture = CreateTexture();//MeNew TextureDx8;
// 	if( pTexture->Create( pszFilename, dwWidth, dwHeight, dwFormat, byBuffer, dwSize, dwPool, bFromFile ) )
// 	{
// 		m_textures[nEmptySlotId] = pTexture;
// 		stIndex = nEmptySlotId;
// 
// 		m_nMinTexture = stIndex;
// 
// 		goto exit_fun;
// 	}
// 
// 	delete pTexture;
// 	pTexture = NULL;
// //	return -1;
// exit_fun:
// 	LeaveCriticalSection( &gs_TextureLoadingCS );
// 	return stIndex;
// 	unguard;
// }

// short	CHRTextureManagerInstance::RegisterTextureToMem( const char* pszFilename, 
// 													DWORD dwWidth, DWORD dwHeight, DWORD dwFormat,
// 													BYTE *byBuffer, DWORD dwSize, DWORD dwPool )
// {
// 	guardfunc;
// 	EnterCriticalSection( &gs_TextureLoadingCS );
// 	short stIndex = -1;
// 	int nEmptySlotId = -1;
// 	for( int i = 0; i < eMaxTexture; i++ )
// 	{
// 		if( !m_textures[i] )
// 		{
// 			// 第一个空的id
// 			if( nEmptySlotId == -1 )
// 			{
// 				nEmptySlotId = i;
// 			}
// 
// 			continue;
// 		}
// 
// 		if( m_textures[i] )
// 		{
// 			if( m_textures[i]->GetName() )
// 			{
// 				if( _stricmp( pszFilename, m_textures[i]->GetName()  ) == 0 )
// 				{
// 					assert( m_textures[i]->GetRef() > 0 );
// 					// 增加计数器
// 					m_textures[i]->AddRef();
// 					stIndex = i;
// 					goto exit_fun;
// 				}
// 			}
// 		}
// 	}
// 	// 如果空间已满
// 	if( nEmptySlotId == -1 )
// 	{
// 		assert( false && "not enough texture id to use" );
// 		goto exit_fun;
// 	}
// 	ITexture* pTexture = CreateTexture();//MeNew TextureDx8;
// 	if( pTexture->Create( pszFilename, dwWidth, dwHeight, dwFormat, byBuffer, dwSize, dwPool ) )
// 	{
// 		m_textures[nEmptySlotId] = pTexture;
// 		stIndex = nEmptySlotId;
// 
// 		goto exit_fun;
// 	}
// 
// 	delete pTexture;
// 	pTexture = NULL;
// exit_fun:
// 	LeaveCriticalSection( &gs_TextureLoadingCS );
// 	return stIndex;
// 	unguard;
// }


short CHRTextureManagerInstance::RegisterTexture( ITexture* pTexture )
{
	guardfunc;
	if( pTexture == NULL )
	{
		assert( false && "Me3d texture create failed, null texture" );
		return -1;
	}
	LockTextureManager();
	int stIndex = FindTexture( pTexture->GetName() );
	if( stIndex == -1 )
	{
		for( int i = 0; i < eMaxTexture; i++ )
		{
			if( !m_textures[i] )
			{
				// 第一个空的id
				stIndex = i;
				break;
			}
		}
		// 如果空间已满
		if( stIndex == -1 )
		{
			assert( false && "not enough texture id to use" );
		}
		else
		{
			m_textures[stIndex] = pTexture;
			g_TextureFinder.Register( pTexture->GetName(), pTexture );
		}
	}
	if (stIndex != -1)
	{
		// modified, [10/13/2010 zhangjiayi]
// 		if (m_bDelayQueue[stIndex])
// 		{
// 			m_bDelayQueue[stIndex] = false;
// 		}
// 		else
// 		{
// 			m_textures[stIndex]->AddRef();
// 		}
		m_bDelayQueue[stIndex] = false;
		m_textures[stIndex]->AddRef();
	}
	UnLockTextureManager();
	return stIndex;
	unguard;
}
int CHRTextureManagerInstance::FindTexture( const char* pszName )
{
	guardfunc;
	LockTextureManager();
	int nTex = -1;
	
	ITexture* pFound = (ITexture*) g_TextureFinder.GetDstByName( pszName );
	if( pFound )
		nTex = pFound->GetTextureID();
	
	UnLockTextureManager();
	
	return nTex;
	unguard;
}

short CHRTextureManagerInstance::RegisterTexture(
	const char* pName,
	BOOL bMultiThreadLoading,
	BOOL bIsDelayDestroy,
	BOOL bMipmapFromFile /*= FALSE*/ )
{
	guardfunc;
	if( !pName )
    {
		return -1;
    }

    std::string strFullPath;
    GetLowerFullPath( pName, strFullPath );

	//bMultiThreadLoading = TRUE;
// 	EnterCriticalSection( &gs_TextureLoadingCS );
	LockTextureManager();

	CFilePath path;
	path.Split( strFullPath.c_str() );
	const char* pszName = path.GetFileName();

	short stIndex = FindTexture( pszName );

	if( stIndex == -1 )
	{
		for( int i = 0; i < eMaxTexture; i++ )
		{
			ITexture* tex = m_textures[i];
			if( tex == NULL )
			{
				// 第一个空的id
				stIndex = i;
				break;
			}
// 			if( tex->GetName() )
// 			{
// 				if( _stricmp( pszName, tex->GetName() ) == 0 )
// 				{
// 					assert( tex->GetRef() > 0 );
// 					// 增加计数器
// 					tex->AddRef();
// 					stIndex = i;
// 					goto exit_fun;
// 				}
// 			}
		}
		// 如果空间已满
		if( stIndex == -1 )
		{
			assert( false && "not enough texture id to use" );
		}
		else
		{
			// added, jiayi, [2009/11/12]
			char szFileName[MAX_PATH] = {0};
			HelperFunc::SafeNCpy( szFileName, strFullPath.c_str(), MAX_PATH );	
			CFilePath fullpath;
			fullpath.Split( szFileName );
			char szDDSFileName[MAX_PATH] = {0};
			int nLen = strlen( szFileName );
			if( nLen <= 4 )
				sprintf_s( szDDSFileName, MAX_PATH-1, "%s.dds", strFullPath.c_str() );
			else
			{	
				HelperFunc::SafeNCpy( szDDSFileName, strFullPath.c_str(), MAX_PATH );
				strcpy( &szDDSFileName[nLen-4], ".dds" );	
			}

			if( !packet_namespace::IsOpen( szDDSFileName ) && !packet_namespace::IsOpen( szFileName ) )
			{
				stIndex = -1;
			}
			else
			{

				ITexture* pTexture = CreateTexture();

				pTexture->SetTextureID( stIndex );
				pTexture->SetDelayDestroy( bIsDelayDestroy );

				if( pTexture->CreateFromFile( strFullPath.c_str(), 0, bMultiThreadLoading, bMipmapFromFile ) )	
				{
					m_textures[stIndex] = pTexture;
					pTexture->SetName( pszName );
					g_TextureFinder.Register( pszName, pTexture );
				}
				else
				{
					delete pTexture;
					pTexture = NULL;
					stIndex = -1;
				}
			}
		}
	}
	if( stIndex != -1 )
	{
		// modified, [10/13/2010 zhangjiayi]
// 		if (m_bDelayQueue[stIndex])
// 		{
// 			m_bDelayQueue[stIndex] = false;
// 		}
// 		else
// 		{
// 			m_textures[stIndex]->AddRef();
// 		}
		m_bDelayQueue[stIndex] = false;
		m_textures[stIndex]->AddRef();
		m_textures[stIndex]->SetDelayDestroy( bIsDelayDestroy );
		m_textures[stIndex]->SetBornTime(HQ_TimeGetTime());
	}
	UnLockTextureManager();

	return stIndex;
	unguard;
}

// short CHRTextureManagerInstance::RegisterTextureFromFileMem(const char *name, 
//                             LPVOID pSrcData,
//                             UINT uLength,
// 							BOOL bWarning, 
// 							BOOL bUsepWhenExist,
// 							BOOL bMultiThreadLoading,
// 							BOOL bIsDelayDestroy)
// {
// 	guardfunc;
// 	
// 	//bMultiThreadLoading = TRUE;
// 	EnterCriticalSection( &gs_TextureLoadingCS );
// 	short stIndex = -1;
// 	int nEmptySlotId = -1;
// 	int nFound = FindTexture(name);
// 	if( nFound != -1 )
// 	{
// 		m_textures[nFound]->AddRef();
// 		m_textures[nFound]->SetDelayDestroy( bIsDelayDestroy );
// 		m_textures[nFound]->SetBornTime(HQ_TimeGetTime());
// 		stIndex = nFound;
// 		goto exit_fun;
// 	}
// 
// 	for( int i = 0; i < eMaxTexture; i++ )
// 	{
// 		if( m_textures[i] == NULL )
// 		{
// 			// 第一个空的id
// 			if( nEmptySlotId == -1 )
// 			{
// 				nEmptySlotId = i;
// 			}
// 			continue;
// 		}
// 
// 		if( m_textures[i] )
// 		{
// 			if( m_textures[i]->GetName() )
// 			{
// 				if( _stricmp( name, m_textures[i]->GetName() ) == 0 )
// 				{
// 					assert( m_textures[i]->GetRef() > 0 );
// 					// 增加计数器
// 					m_textures[i]->AddRef();
// 					stIndex = i;
// 					goto exit_fun;
// 				}
// 			}
// 
// 
// 		}
// 
// 	}
// 	// 如果空间已满
// 	if( nEmptySlotId == -1 )
// 	{
// 		assert( false && "not enough texture id to use" );
// 		goto exit_fun;
// 	}
// 
// 	ITexture* pTexture = CreateTexture();
// 	pTexture->SetTextureID( nEmptySlotId );
// 	pTexture->SetDelayDestroy( bIsDelayDestroy );
// 
// 	if( pTexture->CreateFromFileInMem( name, pSrcData, uLength, bUsepWhenExist, bMultiThreadLoading ) )	
// 	{
// 		m_textures[nEmptySlotId] = pTexture;
// 		pTexture->SetBornTime( HQ_TimeGetTime() );
// 
// 		pTexture->SetName(name);
// 		stIndex = nEmptySlotId;
// 		g_TextureFinder.Register( name, pTexture );
// 		goto exit_fun;
// 	}
// 
// 	delete pTexture;
// 	pTexture = NULL;
// exit_fun:
// 	LeaveCriticalSection( &gs_TextureLoadingCS );
// 	return stIndex;
// 	unguard;
// }

short CHRTextureManagerInstance::RegisterTexture( const char* name, 
											 DWORD dwWidth, DWORD dwHeight, 
											 BYTE* pbyBuffer, DWORD dwFormat, 
											 DWORD dwPool
											 )
{
	guardfunc;
// 	EnterCriticalSection( &gs_TextureLoadingCS );
	LockTextureManager();
	short stIndex = FindTexture(name);
	if (stIndex != -1)
	{
		assert(0 && "已经存在同名的贴图，不能再用此名字创建！");
		return -1;
	}
	ITexture* pTexture = CreateTexture();
	if( pTexture )
	{
		if( pTexture->Create( name, dwWidth, dwHeight, dwFormat, pbyBuffer,dwHeight*dwWidth, dwPool  ) )
		{
// 			if(  pbyBuffer)
// 			{
// 				if( !pTexture->UpdateTexture( pbyBuffer, dwWidth, dwHeight, dwFormat ) )
// 				{
// 					pTexture->Release();
// 					goto exit_fun;
// 				}
// 			}

			stIndex = RegisterTexture( pTexture );
		}
		if( stIndex == -1 )
		{
			pTexture->Release();
		}
	}
// exit_fun:
	UnLockTextureManager();
	return stIndex;
	unguard;
}

CHRTextureManagerInstance::CHRTextureManagerInstance():
m_dwUsedVideoMemorySize(0),
m_nMinTexture(eMaxTexture)
{
	guardfunc;
	for( int i = 0; i < eMaxTexture; i++ )
	{
		m_textures[i] = NULL;
		m_bDelayQueue[i] = false;
	}
	m_nDefTextureID = -1;
	InitializeCriticalSection( &gs_TextureLoadingCS );

	m_uiMipmapLevel = D3DX_FROM_FILE;

	
//	m_bIsDelayDestroy = FALSE;
	unguard;
}

CHRTextureManagerInstance::~CHRTextureManagerInstance()
{
	guardfunc;
	Destroy();
	DeleteCriticalSection( &gs_TextureLoadingCS );
	unguard;
}

void CHRTextureManagerInstance::Destroy()
{
	
	guardfunc;
	LockTextureManager();
// 	EnterCriticalSection( &gs_TextureLoadingCS );
	BOOL bSkipWarning = FALSE;
	
	for( int i = 0; i < eMaxTexture; i++ )
	{
		while( m_textures[i]  )
		{
			// 否则死循环 [10/28/2010 zhangjiayi]
			m_textures[i]->SetDelayDestroy( FALSE );
			UnRegisterTexture( i );
		}		
	}
	g_TextureFinder.Destroy();
	UnLockTextureManager();
	unguard;
}

void* CHRTextureManagerInstance::getTextureData( int texId, void* listenter )
{
    guardfunc
	LockTextureManager();
    ITexture* pHRTexture = GetTexture( texId );
    void* data = NULL;
    if ( pHRTexture )
    {
        pHRTexture->addTextureListener( (ITextureListener*)listenter );
        data = pHRTexture->GetData();
        if ( data )
        {
             // 贴图已经加载完成不需要监听器
            pHRTexture->removeAllTextureListener();
        }
    }
	UnLockTextureManager();
    return data;
    unguard
}

ITexture* CHRTextureManagerInstance::GetTextureNoLock( short stTextureId )
{
    guardfunc;
    ITexture* pTexture = NULL;
    if( stTextureId >= 0 && stTextureId < eMaxTexture )
    {
        pTexture = m_textures[stTextureId];
    }
    return pTexture;
    unguard;
}

bool CHRTextureManagerInstance::LockTextureManager()
{
	DWORD nThread = GetCurrentThreadId();
	while (!TryEnterCriticalSection( &gs_TextureLoadingCS ))
	{
		Sleep(1);
	}
	return true;
}

void CHRTextureManagerInstance::UnLockTextureManager()
{
	LeaveCriticalSection( &gs_TextureLoadingCS );
}

bool CHRTextureManagerInstance::TryLockTextureManager()
{
	return TryEnterCriticalSection( &gs_TextureLoadingCS );
}
