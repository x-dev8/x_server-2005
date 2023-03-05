#include "MeUi/MeUi.h"
#include "MeUi/UiPicture.h"
#include "MeUi/ControlObject.h"
#include "FuncPerformanceLog.h"
#include "Me3d/Global.h"
#include "Dxsdk/ddraw.h"
#include "Dxsdk/d3d9types.h"
#include "../filepacket/packet_interface.h"
//#include "Launcher/DataLauncher.h"
#include "MeUi/UiRender.h"
#include "Me3d/Engine/Engine.h"
//FileIO::CVFS g_TextureVFS;
static const DWORD DDS_HEADER = MAKEFOURCC('D', 'D', 'S', ' ');

namespace UiDrawer
{
	funRegisterTexture		RegisterTexture = NULL;
//     funRegisterTextureFromFileMem RegisterTextureFromFileMem = NULL;
	funUnregisterTexture	UnregisterTexture = NULL;

	funBlt					Blt = NULL;
	funDrawRect2D			DrawRect2D = NULL;
//	funFillRect2D			FillRect2D = NULL;
	funFillRect2DEx			FillRect2DEx = NULL;
	funDrawProgressRect		DrawProgressRect = NULL;

	void FillRect2D( IN RECT& rect, DWORD dwColor )
	{
		FillRect2DEx( rect, dwColor, dwColor, dwColor, dwColor );
	}

	// added, jiayi, [2009/9/17]
	DWORD dwStartTime = 0;
	float fDuration = 0.f;
	DWORD dwColor = 0;
	bool  bFadeIn = true;
	bool  bStartFillFullScreen = false;
	int	  nColorFactor = 0;
	int	  nAlphaFactor = 0;
	void StartFillFullScreen( float fDur, bool bFIn /*= true*/, int nColorFac /*= 30*/, int nAlphaFac /*= 180*/ )
	{
		dwStartTime = HQ_TimeGetTime();
		fDuration = fDur;
		nColorFactor = nColorFac;
		nAlphaFactor = nAlphaFac;
		dwColor = 0;
		if( ( !bFIn && bStartFillFullScreen ) || bFIn ) // fade out
		{
			bFadeIn = bFIn;
			bStartFillFullScreen = true;
		}		
	}
	void StopFillFullScreen()
	{
		dwStartTime = 0;
		fDuration = 0.f;		
		bStartFillFullScreen = false;
	}
	void FillFullScreen( int nScreenWidth, int nScreenHeight, DWORD dwCurrentTime /*= HQ_TimeGetTime()*/ )
	{
		if( !bStartFillFullScreen )
			return;

		if( !bFadeIn && ( dwCurrentTime - dwStartTime > fDuration ) )
		{
			StopFillFullScreen();
			return;
		}

		DWORD dwAlpha = (min( float( dwCurrentTime - dwStartTime ), fDuration ) / fDuration) * nAlphaFactor;
		if( !bFadeIn )
			dwAlpha = 180 - dwAlpha;
		dwColor = D3DCOLOR_ARGB( dwAlpha, nColorFactor, nColorFactor, nColorFactor );
		RECT rc;
		rc.left = 0;
		rc.top = 0;
		rc.right = nScreenWidth;
		rc.bottom = nScreenHeight;
		FillRect2D( rc, dwColor );
	}
}



void ControlPictureManager::S_Pic::RegisterTexture( IN const char* szName )
{
    if( !szName )
    {
        return;
    }

	char szPath[MAX_PATH] = {0};
    strcpy( szPath, szName );

    // 去扩展名
	String_Util::StripEXT( szPath );
    std::string strDDSPath = szPath;
    std::string strTGAPath = szPath;
    strDDSPath.append( ".dds" );
    strTGAPath.append( ".tga" );

    std::string strFullDDSPath, strFullTGAPath;
    GetLowerFullPath( strDDSPath.c_str(), strFullDDSPath );
    GetLowerFullPath( strTGAPath.c_str(), strFullTGAPath );
		
	//Open DDS
	BOOL bIsDDs = FALSE;
	f_Handle* pFile = packet_namespace::w_fopen( strFullDDSPath.c_str(), "rb" );
	if( pFile )
	{
		DWORD dwDDSHeader;
		packet_namespace::w_fread( &dwDDSHeader, sizeof( DWORD ), 1, pFile );
		if( dwDDSHeader == DDS_HEADER )
		{
 			//DDSURFACEDESC2 ddsd;
 			//fread(&ddsd, sizeof(DDSURFACEDESC2), 1, file);		
 			//m_nWidth = ddsd.dwWidth;
 			//m_nHeight = ddsd.dwHeight;
			bIsDDs = TRUE;
		}
		packet_namespace::w_fclose( pFile );		
	}

	if( szPath[0] != 0 )
	{		
		if( bIsDDs )
        {
			m_TextureId = UiDrawer::RegisterTexture( strFullDDSPath.c_str(), TRUE, false );
        }
		else
        {
			m_TextureId = UiDrawer::RegisterTexture( strFullTGAPath.c_str(), TRUE, false );
        }
	}
	else
	{
		#ifdef _DEBUG
		MESSAGE_BOX("图片文件名为空");
        #endif
	}
	if( m_TextureId == -1 )
	{
		#ifdef _DEBUG //lyh屏蔽日志
		MESSAGE_BOX(szPath);
		#endif
		m_TextureId = UiDrawer::RegisterTexture( "data\\UI\\Icon\\null.dds", TRUE, false );
	}
	if( m_TextureId != -1 )
	{
		IRenderer* r = GetEngine()->GetRenderer();
		LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)r->GetRealDevice();
		ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( m_TextureId );
		m_pd3dTexture = ( LPDIRECT3DTEXTURE9 )pTexture->GetData();
	}
}

void ControlPictureManager::S_Pic::UnregisterTexture()
{
	if ( m_pd3dTexture != NULL )
	{
		UiDrawer::UnregisterTexture( m_TextureId );
		m_pd3dTexture = NULL;
		m_TextureId = -1;
	}
//	MessageBox( NULL, "UnregisterTexture", "Release", MB_OK );
}

// 检验是否是2的幂次方
bool ControlPictureManager::S_Pic::TestPower( int nNum )
{
	if ( nNum == 1 )
	{
		return false;
	}
	int nCount = 0;
	do
	{
		if ( (nNum&1) == 1 )
		{
			if ( ++nCount > 1 )
			{
				return false;
			}
		}
	} while( (nNum>>=1) > 0 );
	if ( nCount == 1 )
	{
		return true;
	}
	return false;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
ControlPictureManager::ControlPictureManager(void)
{
	m_dwLastPicId = 0;
	m_bEnableLoadImage = false;
}
ControlPictureManager::~ControlPictureManager(void)
{
}

void ControlPictureManager::Release()
{
	for (std::list<S_Pic>::iterator iter = m_vtPic.begin(); iter != m_vtPic.end();++iter)
	{
		(*iter).UnregisterTexture();
	}
	m_vtPic.clear();
	m_PicMap.clear();
}

ControlPictureManager::S_Pic* ControlPictureManager::RetrievePic( int& nPicId,const char* pszFilename )
{
	S_Pic *pPic = NULL;
	if (nPicId != -1)
	{
		std::map<int ,S_Pic*>::iterator iter = m_PicMap.find(nPicId);
		if (iter != m_PicMap.end())
		{
			return iter->second;
		}
	}
// 	for( UINT n=0; n<m_vtPic.size(); n++ )
// 	{
// 		pPic = &m_vtPic[n];
// 		if ( pPic->m_nId == nPicId )
// 		{
// 			pPic->m_dwLastUseTime = HQ_TimeGetTime();
// 			nIndex = n;
// 			break;
// 		}
// 	}
	if (pszFilename)
	{
		for (std::list<S_Pic>::iterator iter = m_vtPic.begin(); iter != m_vtPic.end();++iter)
		{
			S_Pic *pTmpPic = &(*iter);
			if ( pTmpPic->m_strName == pszFilename )
			{
				pTmpPic->m_dwLastUseTime = HQ_TimeGetTime();
				nPicId = pTmpPic->m_nId;
				pPic = pTmpPic;
				break;
			}
		}
		if ( pPic == NULL )
		{
			S_Pic stPic;
			stPic.RegisterTexture( pszFilename );
			if ( stPic.m_TextureId != -1 )
			{
				stPic.m_strName = pszFilename;
				stPic.m_nId = m_dwLastPicId++;
				nPicId = stPic.m_nId;
				stPic.m_dwLastUseTime = HQ_TimeGetTime();
				m_vtPic.push_back( stPic );
				pPic = &m_vtPic.back();
				m_PicMap.insert(make_pair(pPic->m_nId,pPic));
			}
		}
	}
	return pPic;
}

void ControlPictureManager::Run()
{
	guardfunc;
	//for( std::vector<S_Pic>::iterator it = m_vtPic.begin();
	//		it != m_vtPic.end(); it++ )
	//{
	//	if ( HQ_TimeGetTime() - it->m_dwLastUseTime > 60000 )
	//	{
	//		it->UnregisterTexture();
	//		m_vtPic.erase(it);
	//		break;
	//	}
	//}
	unguard;
}

bool ControlPictureManager::RenderNineGrid( 
	int& pnPicId,
	const char* pszFilename,
	unsigned int uiTotalWidth,
	unsigned int uiTotalHeight,
	unsigned int uiGridWidth,
	unsigned int uiGridHeight,
	RECT* pDstRc, 
	D3DCOLOR kCol /* = 0xffffffff */, 
	const float fZ /* = 0.f */,
	DWORD dwRenderFlag /* = 0 */
	)
{
	assert( pszFilename );
	S_Pic* pPic = RetrievePic(pnPicId,pszFilename);
	if (NULL == pPic)
	{
		return false;
	}
	///////////////////////////////////////
	//left top
	///////////////////////////////////////
	RECT rcDst;
	RECT rcSrc;
	rcDst.left = pDstRc->left;
	rcDst.right = pDstRc->left + uiGridWidth;
	rcDst.top = pDstRc->top;
	rcDst.bottom = pDstRc->top + uiGridHeight;
	rcSrc.left = 0;
	rcSrc.right = uiGridWidth;
	rcSrc.top = 0;
	rcSrc.bottom = uiGridHeight;
	D3DSURFACE_DESC texDesc;
	if(!pPic->m_pd3dTexture || pPic->m_pd3dTexture->GetLevelDesc( 0, &texDesc ) != D3D_OK )
		return false;
	UiDrawer::Blt( pPic->m_pd3dTexture,
		&rcDst, &rcSrc,
		texDesc.Width, texDesc.Height,
		fZ, kCol, dwRenderFlag );
	///////////////////////////////////////
	//middle top
	///////////////////////////////////////	
	rcDst.left = pDstRc->left + uiGridWidth /*+ 1*/;
	rcDst.right = pDstRc->right - uiGridWidth;
	rcDst.top = pDstRc->top;
	rcDst.bottom = pDstRc->top + uiGridHeight;
	rcSrc.left = uiGridWidth;
	rcSrc.right = /*uiTotalWidth - uiGridWidth*/uiGridWidth /*+ 1*/;
	rcSrc.top = 0;
	rcSrc.bottom = uiGridHeight;
	UiDrawer::Blt( pPic->m_pd3dTexture,
		&rcDst, &rcSrc,
		texDesc.Width, texDesc.Height,
		fZ, kCol, dwRenderFlag );
	///////////////////////////////////////
	//right top
	///////////////////////////////////////	
	rcDst.left = pDstRc->right - uiGridWidth /*+ 1*/;
	rcDst.right = pDstRc->right;
	rcDst.top = pDstRc->top;
	rcDst.bottom = pDstRc->top + uiGridHeight;
	rcSrc.left = uiTotalWidth - uiGridWidth;
	rcSrc.right = uiTotalWidth;
	rcSrc.top = 0;
	rcSrc.bottom = uiGridHeight;
	UiDrawer::Blt( pPic->m_pd3dTexture,
		&rcDst, &rcSrc,
		texDesc.Width, texDesc.Height,
		fZ, kCol, dwRenderFlag );
	///////////////////////////////////////
	//left middle
	///////////////////////////////////////	
	rcDst.left = pDstRc->left;
	rcDst.right = pDstRc->left + uiGridWidth;
	rcDst.top = pDstRc->top + uiGridHeight /*+ 1*/;
	rcDst.bottom = pDstRc->bottom - uiGridHeight;
	rcSrc.left = 0;
	rcSrc.right = uiGridWidth;
	rcSrc.top = uiGridHeight;
	rcSrc.bottom = /*uiTotalHeight - uiGridHeight*/uiGridHeight /*+ 1*/;
	UiDrawer::Blt( pPic->m_pd3dTexture,
		&rcDst, &rcSrc,
		texDesc.Width, texDesc.Height,
		fZ, kCol, dwRenderFlag );
	///////////////////////////////////////
	//left bottom
	///////////////////////////////////////	
	rcDst.left = pDstRc->left;
	rcDst.right = pDstRc->left + uiGridWidth;
	rcDst.top = pDstRc->bottom - uiGridHeight /*+ 1*/;
	rcDst.bottom = pDstRc->bottom;
	rcSrc.left = 0;
	rcSrc.right = uiGridWidth;
	rcSrc.top = uiTotalHeight - uiGridHeight;
	rcSrc.bottom = uiTotalHeight;
	UiDrawer::Blt( pPic->m_pd3dTexture,
		&rcDst, &rcSrc,
		texDesc.Width, texDesc.Height,
		fZ, kCol, dwRenderFlag );
	///////////////////////////////////////
	//middle middle
	///////////////////////////////////////	
	rcDst.left = pDstRc->left + uiGridWidth /*+ 1*/;
	rcDst.right = pDstRc->right - uiGridWidth;
	rcDst.top = pDstRc->top + uiGridHeight /*+ 1*/;
	rcDst.bottom = pDstRc->bottom - uiGridHeight;
	rcSrc.left = uiGridWidth;
	rcSrc.right = /*uiTotalWidth - uiGridWidth*/uiGridWidth /*+ 1*/;
	rcSrc.top = uiGridHeight;
	rcSrc.bottom = /*uiTotalHeight - uiGridHeight*/uiGridHeight /*+ 1*/;
	UiDrawer::Blt( pPic->m_pd3dTexture,
		&rcDst, &rcSrc,
		texDesc.Width, texDesc.Height,
		fZ, kCol, dwRenderFlag );
	///////////////////////////////////////
	//right middle
	///////////////////////////////////////	
	rcDst.left = pDstRc->right - uiGridWidth /*+ 1*/;
	rcDst.right = pDstRc->right;
	rcDst.top = pDstRc->top + uiGridHeight /*+ 1*/;
	rcDst.bottom = pDstRc->bottom - uiGridHeight;
	rcSrc.left = uiTotalWidth - uiGridWidth;
	rcSrc.right = uiTotalWidth;
	rcSrc.top = uiGridHeight;
	rcSrc.bottom = /*uiTotalHeight - uiGridHeight*/uiGridHeight /*+ 1*/;
	UiDrawer::Blt( pPic->m_pd3dTexture,
		&rcDst, &rcSrc,
		texDesc.Width, texDesc.Height,
		fZ, kCol, dwRenderFlag );

	///////////////////////////////////////
	//right bottom
	///////////////////////////////////////	
	rcDst.left = pDstRc->right - uiGridWidth /*+ 1*/;
	rcDst.right = pDstRc->right;
	rcDst.top = pDstRc->bottom - uiGridHeight /*+ 1*/;
	rcDst.bottom = pDstRc->bottom;
	rcSrc.left = uiTotalWidth - uiGridWidth;
	rcSrc.right = uiTotalWidth;
	rcSrc.top = uiTotalHeight - uiGridHeight;
	rcSrc.bottom = uiTotalHeight;
	UiDrawer::Blt( pPic->m_pd3dTexture,
		&rcDst, &rcSrc,
		texDesc.Width, texDesc.Height,
		fZ, kCol, dwRenderFlag );
	///////////////////////////////////////
	//bottom middle
	///////////////////////////////////////	
	rcDst.left = pDstRc->left + uiGridWidth /*+ 1*/;
	rcDst.right = pDstRc->right - uiGridWidth;
	rcDst.top = pDstRc->bottom - uiGridHeight /*+ 1*/;
	rcDst.bottom = pDstRc->bottom;
	rcSrc.left = uiGridWidth;
	rcSrc.right = /*uiTotalWidth - uiGridWidth*/uiGridWidth /*+ 1*/;
	rcSrc.top = uiTotalHeight - uiGridHeight;
	rcSrc.bottom = uiTotalHeight;
	UiDrawer::Blt( pPic->m_pd3dTexture,
		&rcDst, &rcSrc,
		texDesc.Width, texDesc.Height,
		fZ, kCol, dwRenderFlag );
	return true;
}


unsigned long ControlPictureManager::BitBlt2( LPDIRECT3DTEXTURE9 pd3dTexture,  IN RECT* pDstRc, IN RECT* pSrcRc /*= NULL*/, D3DCOLOR col /*= 0xffffffff*/, const float fZ /*= 0.0f*/, DWORD _renderFlag /*= 0 */ )
{
	if ( pSrcRc ) 
	{
		if (g_uiRenderCurrFrame && g_uiRenderCurrFrame->isQueueingEnabled())
		{
			return g_uiRenderCurrFrame->addQuad(*pDstRc,pd3dTexture,*pSrcRc,col);
		}
		else
		{
			D3DSURFACE_DESC texDesc;
			if(!pd3dTexture || pd3dTexture->GetLevelDesc( 0, &texDesc ) != D3D_OK )
				return -1;
			UiDrawer::Blt( pd3dTexture,
				pDstRc, pSrcRc,
				texDesc.Width, texDesc.Height,
				fZ, col, _renderFlag );
		}
	}
	else 
	{
		D3DSURFACE_DESC texDesc;
		if(!pd3dTexture ||  pd3dTexture->GetLevelDesc( 0, &texDesc ) != D3D_OK )
			return false;
		RECT rcSrc ={0,0,texDesc.Width,texDesc.Height};
		if (g_uiRenderCurrFrame && g_uiRenderCurrFrame->isQueueingEnabled())
		{
			return g_uiRenderCurrFrame->addQuad(*pDstRc,pd3dTexture,rcSrc,col);
		}
		else
		{
			UiDrawer::Blt( pd3dTexture,
				pDstRc, &rcSrc,
				texDesc.Width, texDesc.Height,
				fZ, col, _renderFlag );
		}
	}
	return -1;
}

 unsigned long ControlPictureManager::BitBlt( IN OUT int* pPicId, IN const char* szFileName,
							 IN RECT* pDstRc, IN RECT* pSrcRc,
							 D3DCOLOR col, const float fZ,
                             DWORD _renderFlag )
{
// 	assert( pPicId && szFileName );
	S_Pic *pPic = RetrievePic(*pPicId,szFileName);
	if (pPic == NULL)
	{
		return -1;
	}
	return BitBlt2(pPic->m_pd3dTexture,pDstRc,pSrcRc,col,fZ,_renderFlag);
}

ControlPictureManager::S_Pic* ControlPictureManager::RegisterTexture( IN OUT int* pPicId, IN const char* szFileName )
{
// 	if (!m_bEnableLoadImage)
// 		return NULL;

	assert( pPicId && szFileName );
	ControlPictureManager::S_Pic* pRet = RetrievePic(*pPicId,szFileName);
	if (pRet)
	{
		++pRet->m_RefCount;
	}
	return pRet;
}

void ControlPictureManager::UnregisterTexture( IN const char* szFileName )
{
	for( std::list<S_Pic>::iterator it = m_vtPic.begin();
		it != m_vtPic.end(); ++it )
	{
		if ( it->m_strName == szFileName )
		{
			--it->m_RefCount;
			if (0 == it->m_RefCount)
			{
				it->UnregisterTexture();
				m_PicMap.erase(it->m_nId);
				m_vtPic.erase(it);
			}
			return;
		}
	}
}
void ControlPictureManager::UnregisterTexture( LPDIRECT3DTEXTURE9 pd3dTexture )
{
	for( std::list<S_Pic>::iterator it = m_vtPic.begin();
		it != m_vtPic.end(); ++it )
	{
		if ( it->m_pd3dTexture == pd3dTexture )
		{
			--it->m_RefCount;
			if (0 == it->m_RefCount)
			{
				it->UnregisterTexture();
				m_PicMap.erase(it->m_nId);
				m_vtPic.erase(it);
			}
			return;
		}
	}

}
void ControlPictureManager::UnregisterTexture( int nPicId )
{
	for( std::list<S_Pic>::iterator it = m_vtPic.begin();
		it != m_vtPic.end(); ++it )
	{
		if ( it->m_nId == nPicId )
		{
			--it->m_RefCount;
			if (0 == it->m_RefCount)
			{
				it->UnregisterTexture();
				m_PicMap.erase(it->m_nId);
				m_vtPic.erase(it);
			}
			return;
		}
	}

}

// #ifdef _DEBUG
// ControlPictureManager::S_Pic* ControlPictureManager::GetPic( const UINT nIndex )
// {
// 	assert( nIndex >=0 && nIndex < m_vtPic.size() );
// 	return &m_vtPic[nIndex];
// }
// #endif


