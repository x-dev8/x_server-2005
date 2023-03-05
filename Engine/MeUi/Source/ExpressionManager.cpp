#include "MeUi/ExpressionManager.h"
#include "MeUi/UiPicture.h"
#include "MeUi/FontManager.h"
#include "MeUi/ControlObject.h"
#include "FuncPerformanceLog.h"
//#include "XmlStringLanguage.h"
#include "MeUi/UiManager.h"
#include "FilePath.h"
#include "Me3d/BaseGraphics.h"
#include <assert.h>
#include "Me3d/Engine/Engine.h"
#include "Me3d/Engine/RendererDx8.h"
#include "Me3d/Engine/EngineInstance.h"

//#include "core/core.h"
#include "TimeEx.h"
#include "CxImage/ximage.h"
#include "RapidXml/MeRapidXml.h"
#include "tstring.h"
#include "../filepacket/packet_interface.h"
//#include "Launcher/DataLauncher.h"
extern const char* GetFullName(const char* filename);

#define ChatExpression_BeginID 10000
#define ChatExpression_EndID 20000

ExpressionManager::ExpressionManager()
{
	LoadFromSlk();
	m_dwCurrentFrameTime = 0;
}

bool ExpressionManager::LoadFromSlk()
{
	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile("..\\Data\\Config\\Expression.config", 1))
	{
		return false;
	}
	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if ( NULL == pRoot ) return false;


	MeXmlElement* pExpressions = pRoot->FirstChildElement("Expressions");
	if ( NULL == pExpressions ) return false;

	MeXmlElement* pExpression = pExpressions->FirstChildElement("Expression");
	while (pExpression != NULL)
	{
		std::string strPath = pExpression->Attribute("FilePath");

		int nExpressionId = 0;
		pExpression->Attribute("Id",&nExpressionId);

		Common::_tstring name;
		name.fromUTF8(pExpression->Attribute("Name"));
		std::string strTip	= name;
		std::string strExpressionShortKey = pExpression->Attribute("Shortcut1");
		strTip.insert(0,strExpressionShortKey.c_str());
		const char* pFullName = GetFullName(strPath.c_str());
		// get group id
		
		const char*	pszGroupName = pExpression->Attribute("Group");
		ExpressionData* pInfo = MeNew ExpressionData( pFullName, strTip.c_str(), pszGroupName);
		int nUseInChat = false;
		if (pExpression->Attribute("UseInChat",&nUseInChat))
		{
			pInfo->m_bUseInChat = nUseInChat;
		}
		m_expressionList.push_back(pInfo);
		m_expressionSets.insert(ExpressionInfos::value_type(strExpressionShortKey,pInfo));

		if (nExpressionId >= ChatExpression_BeginID && nExpressionId <= ChatExpression_EndID)
		{
			m_expressionListIndex.push_back(m_expressionList.size() - 1);
		}

		int nCount = 2;
		char temp[128];
		while(1)
		{
			sprintf_s(temp,"ExpreShortCut%d",nCount++);
			if (!pExpression->Attribute(temp))
			{
				break;
			}
			strExpressionShortKey = pExpression->Attribute(temp);
			if( strExpressionShortKey.length() == 0)
			{
				break;
			}
			m_expressionSets.insert(ExpressionInfos::value_type(strExpressionShortKey,pInfo));
		}
		pExpression = pExpression->NextSiblingElement();
	}
	return true;
}

ExpressionManager::~ExpressionManager()
{
	for(std::vector<ExpressionData*>::iterator iter = m_expressionList.begin(); iter != m_expressionList.end(); ++iter)
	{
		delete (*iter);
	}
}

void ExpressionManager::AddFrameInfo( ExpressionData* pData )
{
	if( !pData || !pData->m_pImage )
		return;

	if( pData->m_strGroupName.compare( "" ) == 0 )//空
		return;

	long totalFrame = pData->m_pImage->GetNumFrames();
	m_mapSyncFrame[pData->m_strGroupName].lFrame = 0;	
	m_mapSyncFrame[pData->m_strGroupName].dwDelayTime = pData->m_pImage->GetFrameDelay();
	m_mapSyncFrame[pData->m_strGroupName].lTotalFrame = totalFrame;	
	m_mapSyncFrame[pData->m_strGroupName].bRender = false;
	m_mapSyncFrame[pData->m_strGroupName].dwLastTime = 0;
}

void ExpressionManager::ToNextFrame()
{
	std::map< std::string, FrameInfo >::iterator iter = m_mapSyncFrame.begin();	
	for( ; iter != m_mapSyncFrame.end(); ++ iter )
	{
		if( (*iter).second.lFrame >= ( (*iter).second.lTotalFrame - 1 ) )// last frame
			(*iter).second.lFrame = 0;
		else
		{
			if( m_dwCurrentFrameTime - (*iter).second.dwLastTime > 
				10 * max(1, (*iter).second.dwDelayTime ) )
			{
				(*iter).second.lFrame ++;	
				(*iter).second.bRender = true;
				(*iter).second.dwLastTime = m_dwCurrentFrameTime;
			}
			else
			{
				(*iter).second.bRender = false;
			}
		}

	}
}

//int ExpressionManager::AddExpressionAni(  std::string& strValue ,int nMaxExpression)
//{
//	const char *imageLeft = "{";
//	const char *imageRight = "}";
//
//	int nCount = 0;
//	for(ExpressionInfos::iterator iter = m_expressionSets.begin(); iter != m_expressionSets.end();++iter)
//	{
//		const std::string& key = (*iter).first;
//		int pos = 0;
//		while ( (pos = strValue.find(key.c_str(), pos)) != std::string::npos )
//		{
//			int leftPos = strValue.rfind(imageLeft,pos) ;
//			if (leftPos != string::npos  )
//			{
//				int rightPos = strValue.rfind(imageRight,pos) ;
//				if (rightPos == string::npos || leftPos > rightPos )
//				{
//					pos += key.length();
//					continue;
//				}
//			}
//			
//			if (nCount >= nMaxExpression)
//			{
//				strValue.erase(pos, key.length());
//			}
//			else
//			{
//				int hl = strlen(imageLeft);
//				int hr = strlen(imageRight);
//				int end = pos + key.length();
//
//				std::string token;
//				if (pos - hl >= 0)
//					token = strValue.substr(pos - hl, hl);
//				if (token != imageLeft)
//				{
//					strValue.insert(pos, imageLeft);
//					end += strlen(imageLeft);
//				}
//				token = "";
//				if (end + hr < strValue.length())
//					token = strValue.substr(end, hr);
//				if (token != imageRight)
//					strValue.insert(end, imageRight);
//
//				pos = end + hr;
//
//			}
//			++nCount;
//		}
//	}
//	return nCount;
//}

//------------------------------------------------------------------------------------------modify by yanli 2010-9-2
int ExpressionManager::AddExpressionAni(std::string& strValue ,int nMaxExpression,bool bUseInChat)
{
	int nCount = 0;
	std::map<int, std::string> key_count;
	//第一遍就将需要删除的删掉
	for(ExpressionInfos::iterator iter = m_expressionSets.begin(); iter != m_expressionSets.end();++iter)
	{
		std::string key = (*iter).first;
		int pos = 0;
		while ((pos = strValue.find(key.c_str(), pos)) != std::string::npos)
		{
			if (!bUseInChat || (*iter).second->m_bUseInChat)
			{
				++nCount;
				key_count[pos] = key;
			}
			pos += key.size();
		}
	}

	int nDiff = nCount - nMaxExpression;
	if (nDiff > 0)
	{
		std::vector<int> vcPosition;
		for (std::map<int, std::string>::reverse_iterator map_it = key_count.rbegin(); map_it != key_count.rend(); ++map_it)
		{
			strValue.erase(map_it->first, (map_it->second).size());
			vcPosition.push_back(map_it->first);
			if (--nDiff <= 0)
			{
				break;
			}
		}

		for (std::vector<int>::iterator it = vcPosition.begin(); it != vcPosition.end(); ++it)
		{
			key_count.erase(*it);
		}
	}

	const std::string imageLeft = "{";
	const std::string imageRight = "}";
	int hl = imageLeft.size();
	int hr = imageRight.size();

	size_t size = strValue.size();
	for (std::map<int, std::string>::reverse_iterator map_it = key_count.rbegin(); map_it != key_count.rend(); ++map_it)
	{
		if (strValue.substr(map_it->first + (map_it->second).size(), hr) != imageRight)
		{
			strValue.insert(map_it->first + (map_it->second).size(), imageRight);
		}

		if (strValue.substr(map_it->first - hl >=0 ? map_it->first - hl : 0, hl) != imageLeft)
		{
			strValue.insert(map_it->first, imageLeft);
		}
	}

	return nCount;
}

//---------------------------------------------------------------------------
extern HWND g_hWnd;
#include <atlimage.h>
void ExpressionManager::TestRender()
{
	std::vector<ExpressionData*>::iterator iter = m_expressionList.begin();
	ExpressionData* pInfo = (*(iter + 33));
	RECT rcDst = {0,0,40,40};
	DrawExpression(pInfo, rcDst);
	// 	UiDrawer::Blt((*iter)->m_textureId,&rcDst,&rcSrc,pImage->GetWidth(),pImage->GetHeight(),0,0xffffffff,0);
// 	img.Create(pImage->GetWidth(),pImage->GetHeight(),32);
// 	pImage->Draw(img.GetDC(),rcSrc);
// 	img.Draw(::GetDC(g_hWnd),rcDst,rcSrc);
// 	img.ReleaseDC();
	return;

}
// void xxxx()
// {
// 	DWORD ns[3]={0,1,2};
// 	// compute the number of shift for each mask
// 	// dword aligned width for 32 bit image
// 	long effwidth4 = head.biWidth * 4;
// 	long y4,y3,x4,x3;
// 	BYTE *p=info.pImage;
// 	// scan the buffer in reverse direction to avoid reallocations
// 	for (long y=head.biHeight-1; y>=0; y--){
// 		y4=effwidth4*y;
// 		y3=info.dwEffWidth*y;
// 		for (long x=head.biWidth-1; x>=0; x--){
// 			x4 = 4*x+y4;
// 			x3 = 3*x+y3;
// 			p[  x3]=src[ns[2]+x4];
// 			p[1+x3]=src[ns[1]+x4];
// 			p[2+x3]=src[ns[0]+x4];
// 		}
// 	}
// 
// }
void ExpressionManager::DrawExpression(ExpressionData* pInfo, RECT& rcDst, float fZ /*= 0*/ )
{
	if (!pInfo)
	{
		return ;
	}

	DWORD dwColor = 0xffffffff;
	if (pInfo->m_nImageType == CXIMAGE_FORMAT_TGA)
	{
		IRenderer* r = GetEngine()->GetRenderer();
		LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)r->GetRealDevice();
		ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( pInfo->GetTextureId() );
		if( pTexture != NULL )
		{
			LPDIRECT3DTEXTURE9 pd3dTexture = (LPDIRECT3DTEXTURE9)pTexture->GetData();
			RECT rcSrc = {0,0,pInfo->m_nWidth,pInfo->m_nHeight};
			theControlPictureManager.BitBlt2(pd3dTexture,&rcDst,&rcSrc,dwColor,fZ);
		}

// 		RECT rcSrc = {0,0,pInfo->m_nWidth,pInfo->m_nHeight};
// 		typedef struct 
// 		{
// 			D3DXVECTOR4 p;
// 			DWORD color;
// 			float u, v;
// 		} UVVertex2D;
// 
// 		UVVertex2D vertex[4];
// 
// 		LPRECT lpDestRect = &rcDst;
// 		LPRECT lpSrcRect = &rcSrc;
// 		int nSrcWidth = pInfo->m_nWidth;
// 		int nSrcHeight = pInfo->m_nHeight;
// 		float z = fZ;
// 		DWORD dwColor = 0xffffffff;
// 		DWORD dwFlag = 0;
// 
// 		vertex[0].p = D3DXVECTOR4( ( lpDestRect->left - 0.5 ), (lpDestRect->bottom+0.5), z, 1 );
// 		vertex[0].u = (float)(lpSrcRect->left+0.5f)/nSrcWidth;
// 		vertex[0].v = (float)(lpSrcRect->bottom-0.5f)/nSrcHeight;
// 		vertex[0].color = dwColor;
// 
// 		vertex[1].p = D3DXVECTOR4( (lpDestRect->left-0.5), (lpDestRect->top-0.5), z, 1 );
// 		vertex[1].u = (float)(lpSrcRect->left+0.5f)/nSrcWidth;;
// 		vertex[1].v = (float)(lpSrcRect->top+0.5f)/nSrcHeight;
// 		vertex[1].color = dwColor;
// 
// 		vertex[2].p = D3DXVECTOR4( (lpDestRect->right+0.5), (lpDestRect->bottom+0.5), z, 1 );
// 		vertex[2].u = (float)(lpSrcRect->right-0.5f)/nSrcWidth;
// 		vertex[2].v = (float)(lpSrcRect->bottom-0.5f)/nSrcHeight;
// 		vertex[2].color = dwColor;
// 
// 		vertex[3].p = D3DXVECTOR4( (lpDestRect->right+0.5), (lpDestRect->top-0.5), z, 1 );
// 		vertex[3].u = (float)(lpSrcRect->right-0.5f)/nSrcWidth;
// 		vertex[3].v = (float)(lpSrcRect->top+0.5f)/nSrcHeight;
// 		vertex[3].color = dwColor;
// 
// 		IRenderer* r = GetEngine()->GetRenderer();
// 		LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)r->GetRealDevice();
// 		ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( pInfo->m_textureId );
// 		if( pTexture != NULL )
// 		{
// 			LPDIRECT3DTEXTURE9 pd3dTexture = (LPDIRECT3DTEXTURE9)pTexture->GetData();
// 			r->SetTexture(0, pd3dTexture);
// 		}
// 
// 		r->SetVertexShader(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);
// 		r->SetRenderState(D3DRS_LIGHTING, FALSE);
// 		r->SetRenderState(D3DRS_FOGENABLE, FALSE);
// 		r->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
// 		r->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
// 		r->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
// 		r->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
// 		r->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE );
// 
// 		r->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE);
// 		r->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
// 		r->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
// 		r->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
// 		r->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
// 		r->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
// 
// 		r->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
// 		r->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
// 		r->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
// 
// 		float bias = -2.5f;
// 		r->SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, *((DWORD*)&bias));
// 
// 		r->Commit();
// 
// 		pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, &vertex, sizeof(UVVertex2D) );
		return;
	}
	int nTexture = pInfo->GetTextureId();
	if (nTexture == -1)
	{
		return;
	}
	CxImage* pImage = pInfo->m_pImage;
	UpdateExpression(pInfo);

	RECT rcSrc = {0,0,pImage->GetWidth(),pImage->GetHeight()};
	ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock(nTexture);
	if( pTexture )
	{
		LPDIRECT3DTEXTURE9 pD3dTexture = (LPDIRECT3DTEXTURE9)pTexture->GetData();
		if( pD3dTexture )
			theControlPictureManager.BitBlt2(pD3dTexture,&rcDst,&rcSrc,dwColor,fZ);
		// 	GetDrawer()->Blt(pInfo->m_textureId,&rcDst,&rcSrc,&rcDst,pImage->GetWidth(),pImage->GetHeight(),fZ,0xffffffff,0);
	}	
}

void ExpressionManager::DrawExpression( const std::string& str, RECT& rcDst, float fZ /*= 0*/ )
{
	DrawExpression(GetExpressionInfo(str),rcDst, fZ );
}

const char* ExpressionManager::GetExpressionKeyFromInfo( ExpressionData* pInfo )
{
	for(ExpressionInfos::iterator iter = m_expressionSets.begin(); iter != m_expressionSets.end();++iter)
	{
		if ((*iter).second == pInfo)
		{
			return (*iter).first.c_str();
		}
	}
	assert(0);
	return NULL;
}

ExpressionManager& ExpressionManager::GetInstance()
{
	return *Instance();
}

void ExpressionManager::UpdateExpression( ExpressionData* pInfo )
{

	CxImage* pImage = pInfo->m_pImage;
	if( !pImage )
		return;
	RECT rcSrc = {0,0,pImage->GetWidth(),pImage->GetHeight()};
	bool bRenderGif = false;
	bool bHaveGroup = false;
	if( pInfo->m_strGroupName.compare( "" ) == 0 )
	{
		if( m_dwCurrentFrameTime - pInfo->dTime > 10*max(1,pImage->GetFrameDelay()) )
			bRenderGif = true;
	}
	else // have group
	{
		bRenderGif = m_mapSyncFrame[pInfo->m_strGroupName].bRender;
		bHaveGroup = true;
	}
	if( /*m_dwCurrentFrameTime - m_dwLastFrameTime > 10*max(1,pImage->GetFrameDelay())*/ bRenderGif )
	{		
		ITextureManager* pMgr = GetEngine()->GetTextureManager();
		ITexture* pX8Texture = GetEngine()->GetTextureManager()->GetTextureNoLock(pInfo->m_X8textureId);
		if( !pX8Texture )
			return;
		LPDIRECT3DTEXTURE9 pX8D3dTexture = (LPDIRECT3DTEXTURE9)pX8Texture->GetData();
		// added, jiayi, [2010/3/8]
		if( !pX8D3dTexture )
			return;
		{
			D3DLOCKED_RECT rect;
			if( !FAILED( pX8D3dTexture->LockRect( 0, &rect, 0, 0 ) ) )
			{
				int* p = (int*)rect.pBits;
				memset(p,0,pImage->GetWidth()* pImage->GetHeight()*4);
				pX8D3dTexture->UnlockRect(0);
			}

		}
		pInfo->dTime = m_dwCurrentFrameTime;
		long m = pImage->GetNumFrames();
		long n = 0;
		if( bHaveGroup )
			n = m_mapSyncFrame[pInfo->m_strGroupName].lFrame;
		else
			n = pImage->GetFrame() + 1;

		if (n>=m) n=0;
		if (pImage->GetFrame(n))
			pImage->Copy(*pImage->GetFrame(n));
		pImage->SetFrame(n);
		IDirect3DSurface9* pSurface = NULL; 
		pX8D3dTexture->GetSurfaceLevel(0,&pSurface);
		HDC hdc;
		pSurface->GetDC(&hdc);
		pImage->Draw2(hdc,rcSrc);
		pSurface->ReleaseDC(hdc);
		pSurface->Release();
		{
			D3DLOCKED_RECT X8rect;
			if( !FAILED( pX8D3dTexture->LockRect( 0, &X8rect, 0, 0 ) ) )
			{
				ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock(pInfo->GetTextureId());
				LPDIRECT3DTEXTURE9 pD3dTexture = (LPDIRECT3DTEXTURE9)pTexture->GetData();
				D3DLOCKED_RECT rect;
				if( !FAILED( pD3dTexture->LockRect( 0, &rect, 0, 0 ) ) )
				{
					int* p = (int*)X8rect.pBits;
					int* Desp = (int*)rect.pBits;
					if( p != 0 )
					{
						for (int y = 0; y < pImage->GetHeight();++y)
						{
							for(int x = 0; x < pImage->GetWidth();++x)
							{
								int nIndex = x + y* pImage->GetWidth();
								if (p[nIndex] == 0)
								{
									Desp[nIndex] = 0x00FFFFFF & p[nIndex] ;
								}
								else
								{
									Desp[nIndex] = 0xFF000000 | p[nIndex];
								}
							}
						}
					}
					pD3dTexture->UnlockRect(0);
				}
				pX8D3dTexture->UnlockRect(0);
			}

		}
	}
}
ExpressionManager::ExpressionData::ExpressionData( const char* pFullName,const char* pTip, const char* pszGroupName /*= 0*/ )
:m_textureId(-1)
,m_X8textureId(-1)
, m_nImageType(CXIMAGE_FORMAT_UNKNOWN)
, m_pImage(NULL)
,m_nHeight(0)
,m_nWidth(0)
,m_bUseInChat(false)
{
// 	_strlwr(pFullName);
	m_Tip = pTip;
	if( pszGroupName )
		m_strGroupName = pszGroupName;
	if (pFullName)
	{
		m_strFullPath =  pFullName;
	}
}

ExpressionManager::ExpressionData::~ExpressionData()
{
	if (GetEngine())
	{
		ITextureManager* pMgr = GetEngine()->GetTextureManager();
		if (m_textureId != -1)
		{
			pMgr->UnRegisterTexture(m_textureId);
		}
		if (m_X8textureId != -1)
		{
			pMgr->UnRegisterTexture(m_X8textureId);
		}
	}
	if (m_pImage)
	{
		delete m_pImage;
	}
}

int ExpressionManager::ExpressionData::GetTextureId()
{
	if (m_textureId == -1)
	{
		ITextureManager* pMgr = GetEngine()->GetTextureManager();
		if (strstr(m_strFullPath.c_str(),".tga"))
		{
			m_textureId = pMgr->RegisterTexture(m_strFullPath.c_str(),false,TRUE);
//			SetFlushTmpToDisk(true);
			if (m_textureId != -1)
			{
			//	f_Handle* fp = fopen(m_strFullPath.c_str(),"rb");
				char * pData=NULL;size_t nSize;
				nSize=packet_namespace::LoadFile(m_strFullPath.c_str(),pData,0);
				if(nSize>0)
			//	if( fp  )
				{
//					m_pImage = MeDefaultNew CxImage(fp,CXIMAGE_FORMAT_TGA);
					m_pImage = MeDefaultNew CxImage((byte *)pData,nSize,CXIMAGE_FORMAT_TGA);
					m_nImageType = CXIMAGE_FORMAT_TGA;
					m_nWidth = m_pImage->GetWidth();
					m_nHeight = m_pImage->GetHeight();
//					fclose(fp);
//					SetFlushTmpToDisk(false);
				}
				delete pData;
			}
//			SetFlushTmpToDisk(false);
		}
		else
		{
//			SetFlushTmpToDisk(true);
			m_pImage = NULL;
		//	FILE* fp = fopen(m_strFullPath.c_str(),"rb");
		//	if( fp )
			char * pData=NULL;size_t nSize;
			nSize=packet_namespace::LoadFile(m_strFullPath.c_str(),pData,0);
			if(nSize>0)
			{
				m_pImage = MeDefaultNew CxImage((byte *)pData,nSize,CXIMAGE_FORMAT_GIF);
				dTime = ::GetTickCount();
				if (m_pImage)
				{
					m_nImageType = CXIMAGE_FORMAT_GIF;
					m_nWidth = m_pImage->GetWidth();
					m_nHeight = m_pImage->GetHeight();

					if (!m_pImage->GetRetreiveAllFrames())
					{
						m_pImage->SetRetreiveAllFrames(true);
						m_pImage->SetFrame(m_pImage->GetNumFrames()-1);
					//_fseek_nolock(fp,0,SEEK_SET);
					//	m_pImage->Decode(fp, CXIMAGE_FORMAT_GIF);
						m_pImage->Decode((byte *)pData,nSize,CXIMAGE_FORMAT_GIF);

					}
					delete [] pData;
			//		fclose(fp);
//					SetFlushTmpToDisk(false);
					m_textureId = pMgr->RegisterTexture(m_strFullPath.c_str(),m_pImage->GetWidth(),m_pImage->GetHeight(),NULL,D3DFMT_A8R8G8B8,1);
					char X8FullName[MAX_PATH];
					sprintf(X8FullName,"%sX8",m_strFullPath.c_str());
					m_X8textureId = pMgr->RegisterTexture(X8FullName,m_pImage->GetWidth(),m_pImage->GetHeight(),NULL,D3DFMT_X8R8G8B8,1);
				}
			}
//			SetFlushTmpToDisk(false);
		}
		ExpressionManager::Instance()->AddFrameInfo( this );

	}
	return m_textureId;
}

void CExpressionUpdater::Update()
{
	for (std::list<ExpressionManager::ExpressionData*>::iterator iter = m_ActiveExpr.begin(); iter != m_ActiveExpr.end();++iter)
	{
		ExpressionManager::Instance()->UpdateExpression(*iter);
	}
}

void CExpressionUpdater::AddExpress( ExpressionManager::ExpressionData* pData )
{
	if (pData->m_nImageType == CXIMAGE_FORMAT_GIF)
	{
		bool bFound = false;
		for (std::list<ExpressionManager::ExpressionData*>::iterator iter = m_ActiveExpr.begin(); iter != m_ActiveExpr.end();++iter)
		{
			if ((*iter) == pData)
			{
				bFound = true;
				break;
			}
		}
		if (!bFound)
		{
			m_ActiveExpr.push_back(pData);
		}
	}
}

CExpressionUpdater::CExpressionUpdater()
{

}

CExpressionUpdater::~CExpressionUpdater()
{

}