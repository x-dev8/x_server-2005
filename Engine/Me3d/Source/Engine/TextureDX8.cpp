#include "Me3d/Me3d.h"
#include "Me3d/Global.h"
#include "Me3d/Engine/Engine.h"
#include "Me3d/hrp.h"
#include "Me3d/Engine/texturedx8.h"
#include "Dxsdk/D3D9.h"
#include "Dxsdk/D3DX9Math.h"
//#include "config.h"
//#include "global.h"
//#include "FilePath.h"
//#include "jpeg\jpegimage.h"
//#include "p.h"
//#include "SystemConfig.h"
#include "FilePath.h"
#include <assert.h>
#include <stdio.h>
// #include "VirtualFileSystem/vfs.h"
#include "Me3d/Engine/EngineInstance.h"
#include "Me3d/Engine/TextureManagerInstance.h"
#include "FuncPerformanceLog.h"
#include "helper.h"
#include "Me3d/Platform.h"
//#include "Launcher/DataLauncher.h"
#include "../filepacket/packet_interface.h"
extern BOOL PostTextureLoadingReq( CHRTextureLoadingReq& req );

// extern FileIO::CVFS g_TextureVFS;


HRESULT HrCreateTextureFromFileInMemory ( 
	IRenderer* RI, LPCVOID pSrcData,
	UINT SrcDataSize, LPDIRECT3DTEXTURE9* ppTexture)
{
	guardfunc;
	HRESULT hr = S_OK;

	hr = D3DXCreateTextureFromFileInMemory( (LPDIRECT3DDEVICE9)RI->GetRealDevice(),
		pSrcData, SrcDataSize, ppTexture );
	if( hr != S_OK )
	{
		hr = D3DXCreateTextureFromFileInMemoryEx( (LPDIRECT3DDEVICE9)RI->GetRealDevice(),
			pSrcData, SrcDataSize,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DX_FROM_FILE,
			0,
			D3DFMT_UNKNOWN, 
			D3DPOOL_MANAGED,
			D3DX_DEFAULT ,
			D3DX_DEFAULT ,
			0, NULL,NULL, ppTexture
			);
		if(hr != S_OK )
		{
			OutputDebugString("Failed Create Texture; HRCreateTextureFromFileInMemory\n");
			INT i=hr;
		}
	}
	return hr;
	unguard;
}

HRESULT HrCreateTextureFromFile ( IRenderer* RI, LPCSTR pSrcFile, LPDIRECT3DTEXTURE9* ppTexture, BOOL bMipmapFromFile )
{
	guardfunc;

	HRESULT hr = S_FALSE;
	UINT uiMipmap = GetEngine()->GetTextureManager()->GetGlobalMipmap();
	if( bMipmapFromFile )
		uiMipmap = D3DX_FROM_FILE;
/*
	hr = D3DXCreateTextureFromFileEx( (LPDIRECT3DDEVICE9)RI->GetRealDevice(), 
		pSrcFile,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2, 
		uiMipmap, 0, 
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, 
		D3DX_DEFAULT , D3DX_DEFAULT , 0, NULL, NULL, ppTexture );
	if (hr != S_OK)
	{ */
		// 		FILE	* fp = fopen(pSrcFile,"rb");
		// 		if (fp)
		char * pData=NULL;size_t nSize;
		nSize=packet_namespace::LoadFile(pSrcFile,pData,0);
		if(nSize>0)
		{
			hr = D3DXCreateTextureFromFileInMemoryEx( (LPDIRECT3DDEVICE9)RI->GetRealDevice(), 
				pData,nSize,//fp->_ptr,fp->_cnt,
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT_NONPOW2, 
				uiMipmap, 0, 
				D3DFMT_UNKNOWN,
				D3DPOOL_MANAGED, 
				D3DX_DEFAULT , D3DX_DEFAULT , 0, NULL, NULL, ppTexture );
			if( hr != S_OK )
			{
			/*	hr = D3DXCreateTextureFromFile( (LPDIRECT3DDEVICE9)RI->GetRealDevice(),pSrcFile, ppTexture );
				if( hr != S_OK )
				{*/
					//	if (fp)
					{
						hr = D3DXCreateTextureFromFileInMemory( (LPDIRECT3DDEVICE9)RI->GetRealDevice(),pData,nSize,//fp->_ptr,fp->_cnt,
							ppTexture );
					}
					if( hr != S_OK )
					{
						char szBuffer[256] = {0};
						sprintf( szBuffer, "File:%s Failed Create Texture; HRCreateTextureFromFile\n", pSrcFile );
						OutputDebugString(szBuffer);

					}

			//	}
			}
			//	fclose(fp);
			delete [] pData;
		}
//	}
	return hr;
	unguard;
}


HRESULT HrCreateTextureFromFileInMemoryEx ( IRenderer *RI,
										 LPCVOID pSrcData, 
										 UINT SrcDataSize, 
										 DWORD nWidth, 
										 DWORD nHeight,
										 D3DFORMAT Format, D3DPOOL Pool, 
										 LPDIRECT3DTEXTURE9* ppTexture )
{
	guardfunc;
	HRESULT hr = S_OK;
	if( GetPlatform()->GetMemoryLvl() == eMemory_High )
	{
	//	OutputDebugString("Memory_High Managed");
		//HrCreateTextureFromFileInMemory( RI, pyBuffer, dwSize, &m_pd3dTexture );
		hr = D3DXCreateTextureFromFileInMemory( (LPDIRECT3DDEVICE9)RI->GetRealDevice(), 
				pSrcData,
				SrcDataSize, 
				ppTexture );
	}
	else
	{
		hr = D3DXCreateTextureFromFileInMemoryEx( (LPDIRECT3DDEVICE9)RI->GetRealDevice(), 
				pSrcData,
				SrcDataSize, 
				nWidth,
				nHeight, 
				D3DX_DEFAULT, 0, 
				Format, Pool, 
				D3DX_DEFAULT , D3DX_DEFAULT , 0, NULL, NULL, ppTexture );
	}

	if( hr != S_OK )
	{
		hr = D3DXCreateTextureFromFileInMemoryEx( (LPDIRECT3DDEVICE9)RI->GetRealDevice(), 
			pSrcData,
			SrcDataSize, 
			nWidth,
			nHeight, 
			D3DX_DEFAULT, 0, 
			Format, D3DPOOL_SYSTEMMEM, 
			D3DX_DEFAULT , D3DX_DEFAULT , 0, NULL, NULL, ppTexture );
		int i = hr;
	}



	return hr;

	unguard;
}

//HRESULT HrCreateTextureFromFileInMemory ( IRenderer *RI,
//										 LPCVOID pSrcData, 
//										 UINT SrcDataSize, 
//										 LPDIRECT3DTEXTURE9* ppTexture)
//{
//	guardfunc;
//	HRESULT hr = S_OK;
//
//	hr = D3DXCreateTextureFromFileInMemory( (LPDIRECT3DDEVICE9)RI->GetRealDevice(), 
//		pSrcData,
//		SrcDataSize, 
//		ppTexture );
//	if( hr != S_OK )
//	{
//		OutputDebugString("Failed Create Texture; HrCreateTextureFromFileInMemory");
//		INT i=hr;
//	}
//	return hr;
//	unguard;
//}


HRESULT HrCreateTextureFromFileEx( 								
								IRenderer *RI,
								LPCSTR pSrcFile, 
								DWORD nWidth, 
								DWORD nHeight,
								D3DFORMAT Format, D3DPOOL Pool, 
								LPDIRECT3DTEXTURE9* ppTexture
								)
{
	guardfunc;
	HRESULT hr = S_FALSE;
	char * pData=NULL;size_t nSize;
	nSize=packet_namespace::LoadFile(pSrcFile,pData,0);
	if(nSize>0)
	{
		hr= HrCreateTextureFromFileInMemoryEx ( RI,
			pData, 
			nSize, 
			nWidth, 
			nHeight,
			Format,  Pool, 
			 ppTexture );
	}

	delete [] pData;

	return hr;
	
	/*
	
	HRESULT hr = S_OK;
	hr = D3DXCreateTextureFromFileEx( (LPDIRECT3DDEVICE9)RI->GetRealDevice(), 
						pSrcFile,
						nWidth,
						nHeight, 
						D3DX_DEFAULT, 0, 
						Format, Pool, 
						D3DX_DEFAULT , D3DX_DEFAULT , 0, NULL, NULL, ppTexture );
	if( hr != S_OK )
	{
		hr = D3DXCreateTextureFromFileEx( (LPDIRECT3DDEVICE9)RI->GetRealDevice(), 
			pSrcFile,
			nWidth,
			nHeight, 
			D3DX_DEFAULT, 0, 
			Format, D3DPOOL_SYSTEMMEM, 
			D3DX_DEFAULT , D3DX_DEFAULT , 0, NULL, NULL, ppTexture );
	}
	return hr;*/
	unguard;
}
//
//HRESULT HrCreateTextureFromFile( IRenderer *RI,
//							    LPCSTR pSrcFile, 
//							    LPDIRECT3DTEXTURE9* ppTexture)
//{
//	guardfunc;
//	HRESULT hr = S_OK;
//	hr = D3DXCreateTextureFromFile( (LPDIRECT3DDEVICE9)RI->GetRealDevice(), pSrcFile, ppTexture );
//	{
//		if( hr != S_OK )
//		{
//			char szBuffer[256] = {0};
//			sprintf( szBuffer, "File:%s Failed Create Texture; HrCreateTextureFromFile", pSrcFile );
//				OutputDebugString(szBuffer);
//			OutputDebugString("Failed Create Texture; HrCreateTextureFromFile");
//			INT i=hr;
//		}
//	}
//	return hr;
//	unguard;
//}

HRESULT HrCreateTexture( IRenderer *RI,
						UINT Width, UINT Height, UINT MipLevels, 
						DWORD Usage, 
						D3DFORMAT Format, D3DPOOL Pool, 
						LPDIRECT3DTEXTURE9* ppTexture)
{
	guardfunc;	
	HRESULT hr = S_OK;
	hr = D3DXCreateTexture( (LPDIRECT3DDEVICE9)RI->GetRealDevice(), Width, Height, MipLevels, Usage, 
		Format, Pool, ppTexture );
	if(hr != S_OK )
	{
		D3DXCreateTexture( (LPDIRECT3DDEVICE9)RI->GetRealDevice(), Width, Height, MipLevels, Usage, 
			Format, D3DPOOL_SYSTEMMEM, ppTexture );
	}
	return hr;		
	unguard;
}

DWORD GetVideoSize( DWORD dwWidth, DWORD dwHeight, DWORD dwFormat )
{
	guardfunc;
	switch( dwFormat )
	{
	case D3DFMT_X8R8G8B8:
	case D3DFMT_A8R8G8B8:
		return dwWidth*dwHeight*sizeof(DWORD);
		break;
	case D3DFMT_A1R5G5B5:
	case D3DFMT_R5G6B5:
		return dwWidth*dwHeight*sizeof(WORD);
		break;
	case D3DFMT_A8:
		return dwWidth*dwHeight*sizeof(BYTE);
	}
	return 0;
	unguard;
}

TextureDx8::TextureDx8()
{
	guardfunc;
	m_nRefCount = 0;	
	m_pd3dTexture = 0;
	m_stVideoWidth = 0;
	m_stVideoHeight = 0;
	m_byBPP = 0;
	//m_pszFilename = NULL;
	//m_pszName = NULL;
	m_shTextureID = -1;

	m_szFilename[0] = 0;
	m_szName[0] = 0;
	m_bLoaded = FALSE;
	m_nSerialNo = -1;
	m_bDelayDestroy = FALSE;
	m_dwBornTime = 0;
	unguard;
}


void TextureDx8::SetDelayDestroy( BOOL bDelay)
{
	m_bDelayDestroy = bDelay;
}

TextureDx8::~TextureDx8()
{	
	guardfunc;
	//if( m_pszFilename )
	//{
	//	delete[] m_pszFilename;
	//	m_pszFilename = NULL;
	//}
	//if( m_pszName )
	//{
	//	delete[] m_pszName;
	//	m_pszName = NULL;
	//}
//	assert( m_nRefCount == 0 && "texture ref count is not 0" );

    removeAllTextureListener();

	if( m_pd3dTexture )
	{
		m_pd3dTexture->Release();
		m_pd3dTexture = NULL;
		//g_CKFSys.m_dwTextureVideoSize -= m_nVideoWidth*m_nVideoHeight*m_nBPP;
	}

	unguard;	
}
BOOL TextureDx8::Release()
{
	guardfunc;
	//DecRef();
	if( GetRef() <= 0 )
	{
		delete this;
		return TRUE;
	}

	return FALSE;
	unguard;
}
void TextureDx8::AddRef()
{ 
	guardfunc;
	m_nRefCount++; 
	unguard;
}

void TextureDx8::DecRef()
{ 
	guardfunc;
	m_nRefCount--; 
//	assert( m_nRefCount >= 0 && "texture dec ref, ref count < 0" );
	unguard;
}

void TextureDx8::SetFilename( const char* pszFilename )
{
	guardfunc;
	//strcpy( m_szFilename, pszFilename );
	//if( m_pszFilename )
	//{
	//	delete[] m_pszFilename;
	//	m_pszFilename = NULL;
	//}
	int nLen = min(MAX_PATH,strlen( pszFilename )+1);
	//m_pszFilename = MeDefaultNew char[nLen+1];
	memset( m_szFilename, 0x00, nLen );
	strcpy( m_szFilename, pszFilename );
	unguard;
}

const char* TextureDx8::GetFilename()
{
	guardfunc;
	return m_szFilename;
	unguard;
}
void TextureDx8::SetName( const char* pszName )
{
	guardfunc;
	if( !pszName )
	{
		assert( false );
		return;
	}
	//if( m_pszName )
	//{
	//	delete[] m_pszName;
	//	m_pszName = NULL;
	//}
	//m_pszName = MeDefaultNew char[nLen];
	//memcpy( m_pszName, pszName)
	strncpy( m_szName, pszName, eTextueName-1 );
	unguard;
}
void* TextureDx8::GetData()//{ return m_pd3dTexture; }
{
	guardfunc;
	if( m_bLoaded )
		return m_pd3dTexture;
	return NULL;
	unguard;
}
//BOOL TextureDx8::CreateFromMem( const char* pszFilename, DWORD dwWidth, DWORD dwHeight, DWORD dwFormat )
//{
////	strcpy( m_pszFilename, pszFilename );
//	//SetFilename( pszFilename );
//	//SetName( pszFilename );
//	//LPDIRECT3DDEVICE9 pDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
//
//	//HRESULT hr = 0;
//	//if( FAILED( pDevice->CreateTexture( dwWidth, dwHeight, 0, 0, (D3DFORMAT)dwFormat, D3DPOOL_MANAGED, &m_pd3dTexture ) ) )
//	//{
//	//	return false;
//	//}
//	//AddRef();
//	Create(pszFilename, dwWidth, dwHeight, dwFormat );
//
//	return true;
//}

BOOL TextureDx8::Create( const char* pszName, DWORD dwWidth, DWORD dwHeight, DWORD dwFormat, BYTE *pyBuffer, DWORD dwSize, DWORD dwPool, BOOL bFromFile )
{
	guardfunc;
	IRenderer* RI = GetEngine()->GetRenderer();
	assert( m_nRefCount == 0 && "this texture ref count is not 0 when u create" );

	//pd3dDevice->CreateTexture( dwWidth, dwHeight, 0, 0, (D3DFORMAT)dwFormat, D3DPOOL_MANAGED, &m_pd3dTexture );
	if( !bFromFile )
	{
		if( pyBuffer == NULL )
		{
			//优化，寻找不需要lock的贴图 只用一份copy，
			//D3DPOOL_MANAGED 比较消耗内存，因为有内存备份以供应Lock
			//D3DPOOL_DEFAULT   将在显存中创建帖图，它是不能被LockRect的； 
			//		只能通过CopyRects（）和UpdateTexture（）来更新。设备Reset()的时候必须被释放。
			//		渲染的效率最高，但使用起来最麻烦。   
			//D3DPOOL_MANAGED   在显存中创建帖图，在内存中也创建了一个备份，
			//					可以被LockRect，修改的是内存中的位图。系统会自动更新显存中的位图。
			//					设备Reset()的时候不必须被释放。   
			//D3DPOOL_SYSTEMMEM   只在内存中创建贴图，不在显存中创建。
			//						可以被LockRect设备Reset()的时候不必须被释放。渲染的效率最低。 
			HrCreateTexture( RI, dwWidth, dwHeight, 1, 0, 
				(D3DFORMAT)dwFormat, (D3DPOOL)dwPool, &m_pd3dTexture );
			
		}
		else
		{
		//	HrCreateTextureFromFileInMemoryEx( RI, pyBuffer, dwSize, dwWidth, dwHeight,
		//		(D3DFORMAT)dwFormat, D3DPOOL_MANAGED, &m_pd3dTexture );
		
		//	HrCreateTextureFromFileInMemory( RI, pyBuffer, dwSize, &m_pd3dTexture );
			//return TRUE;
			HrCreateTextureFromFileInMemoryEx( RI, pyBuffer, dwSize, 
				dwWidth, dwHeight, (D3DFORMAT)dwFormat, (D3DPOOL)dwPool, &m_pd3dTexture );
		}
	}
	else
	{
		char szFileName[MAX_PATH];
		HelperFunc::SafeNCpy( szFileName, pszName, MAX_PATH );

		CFilePath path;
		path.Split( szFileName );

		char szDDSFile[MAX_PATH] = {0};
		
		//sprintf( szDDSFile, "%s", szFileName );
		if( HrCreateTextureFromFileEx( RI, szFileName, dwWidth, dwHeight, (D3DFORMAT)dwFormat, (D3DPOOL)dwPool, &m_pd3dTexture )
			!= S_OK )
		{
			return FALSE;
		}

	}
	//assert( m_pd3dTexture != NULL && "Me3d texture create failed," );
	if( !m_pd3dTexture )
	{
		OutputDebugString("Fail::[TextureDx8.cpp.Create. Me3d texture create failed]");
	}

	m_stVideoWidth = dwWidth;
	m_stVideoHeight = dwHeight;

	switch( dwFormat )
	{
	case D3DFMT_A8R8G8B8:
		m_byBPP = sizeof( DWORD );
		break;
	case D3DFMT_A1R5G5B5:
		m_byBPP = sizeof( WORD );
		break;
	case D3DFMT_A8:
		m_byBPP = sizeof(BYTE);
		break;
	case D3DFMT_DXT3:
	case D3DFMT_DXT5:
		m_byBPP = sizeof( BYTE );
		break;
// 	default:
// 		assert( false && "Me3d texture create failed, unknown format" );
	}
	SetFilename( pszName );	
	SetName( pszName );
	// 计数器增加
	AddRef();
	m_bLoaded = TRUE;
	//g_CKFSys.m_dwTextureVideoSize += m_nVideoWidth*m_nVideoHeight*m_nBPP;
	return TRUE;
	unguard;
}

BOOL TextureDx8::CreateFromMemory( const char* pszFilename )
{
	guardfunc;
	IRenderer* RI = GetEngine()->GetRenderer();
	HRESULT hr = S_OK;
// 	if( g_TextureVFS.IsOpen() )
// 	{		
// 		size_t size = 0;
// 		if (!g_TextureVFS.GetUnitLength(pszFilename, size))
// 		{
// 			return FALSE;
// 		}
// 		BYTE *pbyMemory = MeDefaultNew unsigned char[size];
// 		if (!g_TextureVFS.GetUnit(pszFilename, pbyMemory, size))
// 		{
// 			delete[] pbyMemory;
// 			pbyMemory = NULL;
// 			return FALSE;
// 		}
// 
// 		if( pbyMemory )
// 		{
// 			if( FAILED( hr = HrCreateTextureFromFileInMemory( RI, pbyMemory, 
// 				size, &m_pd3dTexture ) ) )
// 			{
// 				delete []pbyMemory;
// 				pbyMemory = NULL;
// 				return FALSE;
// 			}
// 		}
// 		delete []pbyMemory;
// 		pbyMemory = NULL;
// 	}
// 	else
	{
		return FALSE;
	}
	return TRUE;
	unguard;
}

BOOL TextureDx8::CreateFromFile( const char* pszFilename, BOOL bUsepWhenExist, BOOL bMultiThreadLoading, BOOL bMipmapFromFile )
{
	guardfunc;
	
	IRenderer* RI = GetEngine()->GetRenderer();

	if( pszFilename == NULL )
		return FALSE;

	char szFileName[MAX_PATH] = {0};
	HelperFunc::SafeNCpy( szFileName, pszFilename, MAX_PATH );
	//guard(test0);
	CFilePath path;
	path.Split( szFileName );
	if( bUsepWhenExist )
	{
// 		char s[MAX_PATH];
// 		int nLen = strlen( pszFilename );
// 		if( nLen <= 4 )
// 			sprintf( s, "%s.hrp", pszFilename );
// 		else
// 		{
// 			strcpy( s, pszFilename );
// 			strcpy( &s[nLen-4], ".hrp" );
// 		}
// 
// 		FILE* fp = fopen( s, "rb" );
// 		BOOL bHrpExist = TRUE;
// 
// 		if( !fp )
// 		{	
// 			bHrpExist = FALSE;
// 			if( g_TextureVFS.UnitIsExist(s) )
// 			{
// 				bHrpExist = TRUE;	
// 			}				
// 		}
// 
// 		if( fp )
// 			fclose( fp );
// 		if( bHrpExist )
// 		{
// 			OutputDebugString("P 文件未处理");
// 			return FALSE;
// 		}
	}

	char szDDSFileName[MAX_PATH] = {0};
	int nLen = strlen( szFileName );
	if( nLen <= 4 )
		sprintf( szDDSFileName, "%s.dds", pszFilename );
	else
	{
		guard(test0);
		HelperFunc::SafeNCpy( szDDSFileName, pszFilename, MAX_PATH );
		strcpy( &szDDSFileName[nLen-4], ".dds" );
		unguard;
	}

	if( bMultiThreadLoading &&
		GetEngine()->IsUseTextureMultiThreadLoading() )
	{

		if( _stricmp( path.GetExt(), ".tga" ) != 0 &&
			_stricmp( path.GetExt(), ".jpg" ) != 0 &&
			_stricmp( path.GetExt(), ".bmp" ) != 0 &&
			_stricmp( path.GetExt(), ".dds" ) != 0 )
		{
			//assert( false && "TextureDx8, only create tga, jpg format textures" );
			return FALSE;
		}

		if( !CFilePath::IsExist( szDDSFileName ) && !CFilePath::IsExist( szFileName ) )
		{
			return FALSE;
		}
		CHRTextureLoadingReq req;
		req.m_nSerialNo = m_nSerialNo;
		req.m_nTextureID = m_shTextureID;
		req.m_bMipmapFromFile = bMipmapFromFile;
		HelperFunc::SafeNCpy( req.m_szFileName, pszFilename, MAX_PATH );
		PostTextureLoadingReq( req );
	}
	else
	{	//
		
		assert( m_nRefCount == 0 && "this texture ref count is not 0 when u create" );

		if( !m_bLoaded )
		{
			HRESULT hr = 0;
			BOOL bSucess = FALSE;
			if( CFilePath::IsExist( szDDSFileName )  )
			{
				if( FAILED( hr = HrCreateTextureFromFile( RI, szDDSFileName, &m_pd3dTexture, bMipmapFromFile ) ) )
					return FALSE;
				bSucess = TRUE;
			}
			if( CFilePath::IsExist( szFileName ) && !bSucess )
			{
				if( FAILED( hr = HrCreateTextureFromFile(	RI, szFileName, &m_pd3dTexture, bMipmapFromFile ) ) )
					return FALSE;
				bSucess = TRUE;
			}
// 			if( g_TextureVFS.UnitIsExist(szDDSFileName) && !bSucess )
// 			{
// 				if( !CreateFromMemory( szDDSFileName ) )
// 					return FALSE;
// 				bSucess = TRUE;
// 			}
// 			if( g_TextureVFS.UnitIsExist(szFileName) && !bSucess )
// 			{
// 				if( !CreateFromMemory( szFileName ) )
// 					return FALSE;
// 				bSucess = TRUE;
// 			}
			if( !bSucess )
				return FALSE;
			m_bLoaded = TRUE;
		}
	}
	
	//unguard;

	SetFilename( szFileName );
// 	// 计数器增加
// 	AddRef();

	//D3DSURFACE_DESC desc;
	//m_pd3dTexture->GetLevelDesc( 0, &desc );
	//m_nVideoWidth = desc.Width;
	//m_nVideoHeight = desc.Height;
	//m_nBPP = sizeof( DWORD );

	//g_CKFSys.m_dwTextureVideoSize += m_nVideoWidth*m_nVideoHeight*m_nBPP*2;

	//m_bLoaded = TRUE;
	return TRUE;
	unguard;
}




BOOL TextureDx8::CreateFromFileInMem( const char* name, void* pSrcData, unsigned int nLength, BOOL bUsepWhenExist, BOOL bMultiThreadLoading )
{
	guardfunc;

	IRenderer* RI = GetEngine()->GetRenderer();
	assert( m_nRefCount == 0 && "this texture ref count is not 0 when u create" );

	if( !m_bLoaded )
	{
		HRESULT hr = 0;
		BOOL bSucess = FALSE;

        hr = HrCreateTextureFromFileInMemory(RI, pSrcData, nLength, &m_pd3dTexture);
		if (FAILED(hr))
			return FALSE;

		m_bLoaded = TRUE;
	}

	SetFilename( name );
// 	// 计数器增加
// 	AddRef();

	return TRUE;
	unguard;
}

LPDIRECT3DTEXTURE9 TextureDx8::GetTexture()
{
	guardfunc;
	return m_pd3dTexture;
	unguard;
}

BOOL TextureDx8::UpdateTextureToRect( BYTE* pbyBuffer, int nWidth, int nHeight, DWORD dwFormat, INT nX, INT nY )
{
	guardfunc;
	////	return FALSE;
	//if( m_pd3dTexture == 0 )
	//	return FALSE;
	//D3DSURFACE_DESC desc;
	//if( m_pd3dTexture )
	//	m_pd3dTexture->GetLevelDesc( 0, &desc );
	//if( desc.Format != dwFormat )
	//	return FALSE;
	//if( nWidth > desc.Width ||
	//	nHeight > desc.Height )
	//	return FALSE;
	//BYTE* pbySrc = pbyBuffer;

	//D3DLOCKED_RECT rect;
	////RECT Rect;
	//RECT LockRect;
	//SetRect( &LockRect, nX, nY, nX + nWidth, nY + nHeight );
	//
	//if( FAILED( m_pd3dTexture->LockRect( 0, &rect, &LockRect, 0 ) ) )
	//{
	//	return FALSE;
	//}

	//BYTE* p = (BYTE*)rect.pBits;
	//if( p == 0 )
	//{
	//	return FALSE;
	//}

	//int nStride = GetBytesPerPixel( dwFormat, nWidth );
	//nStride *= 4;
	//if( rect.Pitch == nStride )
	//{
	//	guard(test1);
	//	memcpy( p, pbySrc, nStride*nHeight );
	//	unguard;
	//}
	//else
	//{
	//	for( int y = 0; y < nHeight/4; y++ )
	//	{
	//		memcpy( p, &pbySrc[y*nStride], nStride );
	//		p += rect.Pitch;
	//	}
	//}
	//m_pd3dTexture->UnlockRect(0);

	return TRUE;
	unguard;
}

BOOL TextureDx8::UpdateTexture( BYTE* pbyBuffer, int nWidth, int nHeight, DWORD dwFormat )
{
	guardfunc;
//	return FALSE;
	if( m_pd3dTexture == 0 )
		return FALSE;
	D3DSURFACE_DESC desc;
	if( m_pd3dTexture )
		m_pd3dTexture->GetLevelDesc( 0, &desc );
	if( desc.Format != D3DFMT_A8R8G8B8 &&
		desc.Format != D3DFMT_A1R5G5B5 &&
		desc.Format != D3DFMT_A8 )
		return FALSE;
	if( desc.Format != dwFormat )
		return FALSE;
	if( nWidth > desc.Width ||
		nHeight > desc.Height )
		return FALSE;
	BYTE* pbySrc = pbyBuffer;
	
	D3DLOCKED_RECT rect;
	if( FAILED( m_pd3dTexture->LockRect( 0, &rect, 0, 0 ) ) )
	{
		return FALSE;
	}

	BYTE* p = (BYTE*)rect.pBits;
	if( p == 0 )
	{
		return FALSE;
	}

	int nStride = GetBytesPerPixel( (ETextureFormat)dwFormat, nWidth);

	if( rect.Pitch == nStride )
	{
		guard(test1);
		memcpy( p, pbySrc, nStride*nHeight );
		unguard;
	}
	else
	{
		for( int y = 0; y < nHeight; y++ )
		{
			memcpy( p, &pbySrc[y*nStride], nStride );
			p += rect.Pitch;
		}
	}
	m_pd3dTexture->UnlockRect(0);
	
	return TRUE;
	unguard;
}

DWORD TextureDx8::SetLOD( int nLod )
{
	guardfunc;
	if( m_bLoaded && m_pd3dTexture->GetLOD()!= nLod)
		return m_pd3dTexture->SetLOD(nLod);
	return -1;
	unguard;

}



