
#include <assert.h>
#include "../Common/Tga.h"
#include <stdio.h>
#include "hr3d_include.h"
//#include "CHRTextureDX8.h"
#include "..\Common\mapsrc\HR3D_CTerrain.h"
#include "terrainshadow.h"
#include "../Engine/Include/HREngine.h"
#include "../../common/DataChunkWriter.h"
#include "FuncPerformanceLog.h"

#define MAP_TAG(x) (DWORD)(  (((DWORD)x&0x0000ff00)<<8)+(((DWORD)x&0x000000ff)<<24)+(((DWORD)x&0x00ff0000)>>8)+(((DWORD)x&0xff000000)>>24) )

CTerrainShadowMgr* GetTerrainShadowMgr()
{
	guardfunc;
	static CTerrainShadowMgr gs_TerrainShadowMgr;
	return &gs_TerrainShadowMgr;
	unguard;
}
CTerrainShadowMgr::Shadow::Shadow()
{
	guardfunc;
	memset( bMask, 0x00, sizeof( bMask ) );
	memset( dwDiffuse, 0x00, sizeof( dwDiffuse ) );
	
	nMapID = -1;
	nTextureID = -1;
	x = 0;
	y = 0;
	nBlockX = 0;
	nBlockY = 0;
	dwFrame = 0;
	unguard;
}
CTerrainShadowMgr::CTerrainShadowMgr(void):
IOXMLObject("CTerrainShadowMgr"),
m_nShadowCount(0),
m_nShadowMapCount(0),
m_nShadowMapWidth(256),
m_nShadowMapHeight(256),
m_nRenderShadowCount(0),
m_dwFrame(0),
m_pShadows(NULL),
m_pnRenderShadowIDs(NULL)
{
	guardfunc;
	for( int i = 0; i < eMaxShadowMap; i++ )
	{
		m_pdwShadowMaps[i] = NULL;
		m_nShadowMapTextureIDs[i] = -1;
	}
	m_pShadows = new Shadow[eMaxShadow];
	m_pnRenderShadowIDs	=	new int[eMaxShadow];
	m_dwShadowColor = 0x8F000000;
	unguard;
}

CTerrainShadowMgr::~CTerrainShadowMgr(void)
{
	guardfunc;
	if( m_pShadows )
	{
		delete []m_pShadows;
		m_pShadows = NULL;
	}

	if( m_pnRenderShadowIDs )
	{
		delete []m_pnRenderShadowIDs;
		m_pnRenderShadowIDs = NULL;
	}
	if( m_pShadows )
	{
		assert(false && "m_pShadows");
	}

	if( m_pnRenderShadowIDs )
	{
		assert(false && "m_pnRenderShadowIDs");
	}
	for( int i = 0; i < eMaxShadowMap; i++ )
	{
	
		if( m_pdwShadowMaps[i] )
		{
			assert( false && "m_pdwShadawMaps");
		//	delete []m_pdwShadowMaps[i];
		//	m_pdwShadowMaps[i] = NULL;
		}
		if( m_nShadowMapTextureIDs[i] != -1 )
		{
			assert( false && "m_nShadowMapTextureIDs 没有释放");
		//	UnregisterTexture( m_nShadowMapTextureIDs[i] );
		//	m_nShadowMapTextureIDs[i] = -1;
		}
	}
	unguard;
}

bool	CTerrainShadowMgr::LoadShadowMap( const char* pszFileName )
{
	guardfunc;
	Clear();
	
	FILE *f = fopen( pszFileName, "rb" );
	if( !f )
	{
		return false;
	}

	fread( &m_nShadowCount, sizeof(int), 1, f );
	if( m_nShadowCount == 0 )
	{
		fclose(f);
		return true;
	}

	Shadow *pShadowSaves = new Shadow[m_nShadowCount];

	fread( pShadowSaves, sizeof(Shadow)*m_nShadowCount, 1, f );

	for( int i = 0; i < m_nShadowCount; i++ )
	{	
		m_pShadows[i] = pShadowSaves[i];
		m_pShadows[i].p[0] = pShadowSaves[i].p[0]*TERSCALE;
		m_pShadows[i].p[1] = pShadowSaves[i].p[1]*TERSCALE;
		m_pShadows[i].p[2] = pShadowSaves[i].p[2]*TERSCALE;
		m_pShadows[i].p[3] = pShadowSaves[i].p[3]*TERSCALE;
	}
	CreateShadowMap( 256, 256 );
	
	int nMapCount = 0;
	fread( &nMapCount, sizeof(int), 1, f );
	for( int i=0; i<nMapCount+1; i++ )
	{	
		if( m_pdwShadowMaps[i] )
		{
			delete []m_pdwShadowMaps[i];
			m_pdwShadowMaps[i] = NULL;
		}

		m_pdwShadowMaps[i] = new DWORD[m_nShadowMapWidth*m_nShadowMapHeight];

		fread( m_pdwShadowMaps[i], sizeof(DWORD)*m_nShadowMapWidth*m_nShadowMapHeight, 1, f );
		char szPath[MAX_PATH] = {0};
		sprintf( szPath, "ShadowMap_%d", i );
		m_nShadowMapTextureIDs[i] = 
			GetHREngine()->GetTextureMgr()->RegisterTexture( 
			szPath, 
			m_nShadowMapWidth, 
			m_nShadowMapHeight,
			(BYTE*)m_pdwShadowMaps[i],
			D3DFMT_A8R8G8B8 );
		////CHRTextureDX8 *pTexture = new CHRTextureDX8;
		//IHRTexture* pTexture = GetHREngine()->GetTextureMgr()->CreateTexture();
		//pTexture->Create( szPath, m_nShadowMapWidth, m_nShadowMapHeight, D3DFMT_A8R8G8B8 );
		//pTexture->UpdateTexture( m_pdwShadowMaps[i], m_nShadowMapWidth, m_nShadowMapHeight, D3DFMT_A8R8G8B8 );
		////m_nShadowMapTextureIDs[i] = RegisterTexture( pTexture );
		//m_nShadowMapTextureIDs[i] = GetHREngine()->GetTextureMgr()->RegisterTexture( pTexture );
	}
	
	
	if( pShadowSaves )
	{	
		delete []pShadowSaves;
		pShadowSaves = NULL;
	}

	fclose( f );

	return true;
	unguard;
}

bool	CTerrainShadowMgr::SaveShadowMap( const char* pszFileName )
{	
	guardfunc;
	if( m_nShadowCount < 0 )
	{
		return false;
	}
/*	Tga tga;
	tga.CreateImage( m_nShadowMapWidth, m_nShadowMapHeight, 32 );*/
	FILE *f = fopen( pszFileName, "wb" );
	if( !f )
	{	
		return false;
	}
	
	if( m_nShadowCount == 0 )
	{
		fwrite( &m_nShadowCount, sizeof(int), 1, f );
	}
	else
	{
		Shadow *pShadowSaves = new Shadow[m_nShadowCount];
		for( int i = 0; i < m_nShadowCount; i++ )
		{	
			pShadowSaves[i] =  m_pShadows[i];
		}

		fwrite( &m_nShadowCount, sizeof(int), 1, f );
		fwrite( pShadowSaves, sizeof(Shadow)*m_nShadowCount, 1, f );

		int nTileResX = m_nShadowMapWidth/eShadowRes;
		int nTileRexY = m_nShadowMapHeight/eShadowRes;
		int nMapCount = m_nShadowCount/(nTileResX*nTileRexY);
		
		fwrite( &nMapCount, sizeof(int), 1, f );
		for( int i=0; i<nMapCount+1; i++ )
		{
			fwrite( m_pdwShadowMaps[i], sizeof(DWORD)*m_nShadowMapWidth*m_nShadowMapHeight, 1, f );
		}

		if( pShadowSaves )
		{
			delete []pShadowSaves;
			pShadowSaves = NULL;
		}
	}
	fclose( f );
/*
	for( int x=0; x<m_nShadowMapWidth; x++ )					
	{
		for( int y=0; y<m_nShadowMapWidth; y++ )					
		{
			DWORD *pBuffer = m_pdwShadowMaps[0];
			tga.SetPixel( x, y, pBuffer[y*m_nShadowMapWidth+x] );
		}
	}
	char szPath1[MAX_PATH] = {0};
	sprintf( szPath1, "C:\\ShadowMap_%d", 3 );
	tga.SaveToFile( szPath1 );
	tga.Destroy();	*/
	return true;
	unguard;
}

void CTerrainShadowMgr::Clear()
{
	guardfunc;
	for( int i = 0; i < eMaxShadowMap; i++ )
	{
		if( m_pdwShadowMaps[i] )
		{
			delete []m_pdwShadowMaps[i];
			m_pdwShadowMaps[i] = NULL;
		}
		if( m_nShadowMapTextureIDs[i] != -1 )
		{
			//UnregisterTexture( m_nShadowMapTextureIDs[i] );
			GetHREngine()->GetTextureMgr()->UnRegisterTexture( m_nShadowMapTextureIDs[i] );
			m_nShadowMapTextureIDs[i] = -1;
		}
	}


	m_nShadowCount = 0;
	m_nShadowMapCount = 0;
	m_nShadowMapWidth = 0;
	m_nShadowMapHeight = 0;
	m_nRenderShadowCount = 0;
	unguard;
}

BOOL CTerrainShadowMgr::CreateShadowMap( int nWidth, int nHeight )
{
	guardfunc;
	m_nShadowMapWidth = nWidth;
	m_nShadowMapHeight = nHeight;
	
	return TRUE;
	unguard;
}
DWORD*  CTerrainShadowMgr::GetShadowBuffer( int i )
{
	guardfunc;
	if( i < 0 || i > m_nShadowMapCount )
		return NULL;
	return m_pdwShadowMaps[i];
	unguard;
}
CTerrainShadowMgr::Shadow* CTerrainShadowMgr::GetShadow(int x, int y) 
{
	guardfunc;
	for( int i = 0; i<m_nShadowCount; i++ )
	{
		if( m_pShadows[i].nBlockX == x && m_pShadows[i].nBlockY == y )
		{
			return &m_pShadows[i];
		}
	}
	return NULL;
	unguard;
}

CTerrainShadowMgr::Shadow* CTerrainShadowMgr::GetShadow( int i ) 
{
	guardfunc;
	if( i < 0 || i >= m_nShadowCount )
		return NULL;
	return &m_pShadows[i];
	unguard;
}

int CTerrainShadowMgr::RegisterShadow( Shadow* pShadow )
{
	guardfunc;
	if( m_nShadowCount >= eMaxShadow )
	{
		assert( false );
		return -1;
	}
	int nTileResX = m_nShadowMapWidth/eShadowRes;
	int nTileRexY = m_nShadowMapHeight/eShadowRes;
	float fHalfTextel = 0.5f/m_nShadowMapWidth;
	float fDeltaPerTile = 1.0f/m_nShadowMapWidth*eShadowRes;
	
	pShadow->nMapID = m_nShadowCount/(nTileResX*nTileRexY);
	if( pShadow->nMapID == 1 )
	{
		int i = 0;
		i++;
	}
	
	if( pShadow->nMapID >= m_nShadowMapCount )
		m_nShadowMapCount++;
	
	int nOffset = m_nShadowCount%(nTileResX*nTileRexY);
	
	// 在shadow中的位置，单位网格
	pShadow->x = nOffset%nTileResX;
	pShadow->y = nOffset/nTileResX;
	// 如果没有分配
	if( m_pdwShadowMaps[pShadow->nMapID] == NULL )
	{
		m_pdwShadowMaps[pShadow->nMapID] = new DWORD[m_nShadowMapWidth*m_nShadowMapHeight];
		memset( m_pdwShadowMaps[pShadow->nMapID], 0x00, m_nShadowMapWidth*m_nShadowMapHeight*sizeof(DWORD) );
	}

	pShadow->uv[0].x = pShadow->x*fDeltaPerTile+fHalfTextel;
	pShadow->uv[0].y = pShadow->y*fDeltaPerTile+fHalfTextel;

	pShadow->uv[1].x = (pShadow->x+1)*fDeltaPerTile-fHalfTextel;
	pShadow->uv[1].y = (pShadow->y)*fDeltaPerTile+fHalfTextel;

	pShadow->uv[2].x = (pShadow->x+1)*fDeltaPerTile-fHalfTextel;
	pShadow->uv[2].y = (pShadow->y+1)*fDeltaPerTile-fHalfTextel;

	pShadow->uv[3].x = (pShadow->x)*fDeltaPerTile+fHalfTextel;
	pShadow->uv[3].y = (pShadow->y+1)*fDeltaPerTile-fHalfTextel;


	for( int y = 0; y < eShadowRes; y++ )
	{
		for( int x = 0; x < eShadowRes; x++ )
		{
			DWORD* map = m_pdwShadowMaps[pShadow->nMapID];
			DWORD* dst = 
				&map[(pShadow->y*eShadowRes+y)*m_nShadowMapWidth+pShadow->x*eShadowRes+x];
			if( pShadow->bMask[y][x] )
				*dst = m_dwShadowColor;
			else
				*dst = 0x00000000;
				//*dst = 0x00000001;
			//*dst = pShadow->dwDiffuse[y][x];
		}
	}

	int nShadowID = m_nShadowCount;
	m_nShadowCount++;
	m_pShadows[nShadowID] = *pShadow;

	return nShadowID;
	unguard;
}

BOOL CTerrainShadowMgr::DebugLog( const char* pszFileName )
{
	guardfunc;
	for( int i = 0; i < m_nShadowMapCount; i++ )	
	{
		Tga t;
		t.CreateImage( m_nShadowMapWidth, m_nShadowMapHeight, 32 );
		memcpy( t.GetARGBBuffer(), m_pdwShadowMaps[i], m_nShadowMapHeight*m_nShadowMapWidth*sizeof(DWORD) );
		char s[MAX_PATH];
		//sprintf( s, "d:\\shadow_%02ld.tga", i );
		MakeShadowMapName( i, s, MAX_PATH );
		if( !t.SaveToFile(s) )
		{
			assert( false );
		}
		t.Destroy();
	}
	return TRUE;
	unguard;
}
BOOL CTerrainShadowMgr::PushShadow( int nShadowID )
{
	guardfunc;
	if( m_nRenderShadowCount >= eMaxShadow ||
		nShadowID == -1 )	
	{
		assert( false );
		return FALSE;
	}
	m_pnRenderShadowIDs[m_nRenderShadowCount++] = nShadowID;
	return TRUE;
	unguard;
}
void CTerrainShadowMgr::BeginRenderShadow()
{
	guardfunc;
	m_nRenderShadowCount = 0;
	m_dwFrame++;
	unguard;
}
BOOL CTerrainShadowMgr::MakeShadowMapName( int i, char szPath[], int nPathSize )
{
	guardfunc;
	sprintf( szPath, "c:\\shadow_%02ld.tga", i );
	return TRUE;
	unguard;
}
int CTerrainShadowMgr::	GetShadowMapTextureID( int nShadowMapID )
{
	guardfunc;
	if( m_nShadowMapTextureIDs[nShadowMapID] == -1 )
	{
		char s[MAX_PATH];
		MakeShadowMapName( nShadowMapID, s, MAX_PATH );
		m_nShadowMapTextureIDs[nShadowMapID] = 
			GetHREngine()->GetTextureMgr()->RegisterTexture( s, false, 0, TRUE );
	}
	return m_nShadowMapTextureIDs[nShadowMapID];
	unguard;
}
void CTerrainShadowMgr::Render()
{
	guardfunc;
	//return;
//	m_nRenderShadowCount = 25;
	for( int i = 0; i < m_nRenderShadowCount; i++ )
	{
		int nShadowID = m_pnRenderShadowIDs[i];
		Shadow* pShadow = &m_pShadows[nShadowID];
		// 确保tile的shadow只渲染一次
		if( pShadow->dwFrame == m_dwFrame )
			continue;
		pShadow->dwFrame = m_dwFrame;
		if (pShadow->nMapID >= eMaxShadowMap || pShadow->nMapID < 0)
		{ 
			return;
		}
		if( m_nShadowMapTextureIDs[pShadow->nMapID] == -1 )
		{
			char s[MAX_PATH];
			MakeShadowMapName( pShadow->nMapID, s, MAX_PATH );
			m_nShadowMapTextureIDs[pShadow->nMapID] = 
				//RegisterTexture( s, false );
				GetHREngine()->GetTextureMgr()->RegisterTexture( s, false, 0, TRUE );
		}
		struct ShadowVertex
		{
			D3DXVECTOR3 p;
			DWORD color;
			D3DXVECTOR2 uv;
			
		};
		ShadowVertex v[4];
		v[0].p = pShadow->p[0];
		v[1].p = pShadow->p[1];
		v[2].p = pShadow->p[2];
		v[3].p = pShadow->p[3];
		v[0].color = 0xffffffff;
		v[1].color = 0xffffffff;
		v[2].color = 0xffffffff;
		v[3].color = 0xffffffff;
		v[0].uv = pShadow->uv[0];
		v[1].uv = pShadow->uv[1];
		v[2].uv = pShadow->uv[2];
		v[3].uv = pShadow->uv[3];
		short index[] = { 0, 2, 1, 3, 2, 0 };
		//short index[] = { 0, 1, 2, 2, 1, 3 };
		//PushSurface( 
		GetHREngine()->GetRenderer()->PushSurface(
			m_nShadowMapTextureIDs[pShadow->nMapID],
			-1,
			MDX2_SHADER,
			D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1,
			sizeof( ShadowVertex ),
			(BYTE*)v,
			4,
			(BYTE*)index,
			2, 
			eLightingDisable|eAlphaBlend );
		
	}
	m_nRenderShadowCount = 0;
	unguard;
}

bool	CTerrainShadowMgr::ReadFromMap( HR3D_MapPointer InP, int InSize )
{
	guardfunc;
	Clear();
	int nNumber = *InP.i++;
	InSize = InSize - sizeof(int);
	if( nNumber > 0)
	{
		CreateShadowMap( 256, 256 );

		HR3D_MapPointer p(InP.p);

		while( p.c < InP.c+InSize )
		{
			switch( MAP_TAG( *p.dw ) )
			{
				case 'Sha0'://terrain point
				{
					p.dw++;
					int size = *p.i++;
					m_nShadowCount = nNumber;
					HR3D_MapPointer s(p.c);
					{
						for( int i = 0; i< nNumber; i++)				
						{
							Shadow shadow;// = GetShadow(i);
							//pShadow->
							memcpy( &shadow, s.byte, sizeof(CTerrainShadowMgr::Shadow) );
							m_pShadows[i] = shadow;
							m_pShadows[i].p[0] = shadow.p[0]*TERSCALE;
							m_pShadows[i].p[1] = shadow.p[1]*TERSCALE;
							m_pShadows[i].p[2] = shadow.p[2]*TERSCALE;
							m_pShadows[i].p[3] = shadow.p[3]*TERSCALE;	
							s.byte+=sizeof(CTerrainShadowMgr::Shadow);
						}			
	
					}
					p.c += size; 
					break;
				}
				case 'sfil':
				{
					p.dw++;
					int size = *p.i++;

					HR3D_MapPointer s(p.c);
					{
						int nTexCount = *s.i++;
						int nWidth	  = *s.i++;
						m_nShadowMapCount = nTexCount;
						m_nShadowMapWidth = m_nShadowMapHeight = nWidth;
						
						for( int i=0; i<nTexCount; i++ )				
						{
							if( m_pdwShadowMaps[i] )
							{
								delete []m_pdwShadowMaps[i];
								m_pdwShadowMaps[i] = NULL;
							}	
							m_pdwShadowMaps[i] = new DWORD[nWidth*nWidth];
							memset( m_pdwShadowMaps[i], 0x00, m_nShadowMapWidth*m_nShadowMapHeight*sizeof(DWORD) );
							memcpy( m_pdwShadowMaps[i], s.dw, sizeof(DWORD)*m_nShadowMapWidth*m_nShadowMapHeight );
							char szPath[MAX_PATH] = {0};
							sprintf(szPath, "ShadowMap_%d", i );

							m_nShadowMapTextureIDs[i] = 
								GetHREngine()->GetTextureMgr()->RegisterTexture( szPath,
								m_nShadowMapWidth, 
								m_nShadowMapHeight, 
								(BYTE*)m_pdwShadowMaps[i],
								D3DFMT_A8R8G8B8 );
							//IHRTexture* pTexture = GetHREngine()->GetTextureMgr()->CreateTexture();
							//pTexture->Create( szPath, m_nShadowMapWidth, m_nShadowMapHeight, D3DFMT_A8R8G8B8 );
							//pTexture->UpdateTexture( m_pdwShadowMaps[i], m_nShadowMapWidth, m_nShadowMapHeight, D3DFMT_A8R8G8B8  );
							////m_nShadowMapTextureIDs[i] = RegisterTexture( pTexture );
							//m_nShadowMapTextureIDs[i] = GetHREngine()->GetTextureMgr()->RegisterTexture( pTexture );
							s.dw+=nWidth*nWidth;
						}	
					}
					p.c += size; 
					break;
				}
				default:
				{
					p.dw++;
					int size = *p.i++;
					p.c += size; 
					break;
				}			
			}
		}
	}
	return true;
	unguard;
}



bool CTerrainShadowMgr::loadXMLSettings(XMLElement *element)
{
	guardfunc;
	return true;
	unguard;
}

bool CTerrainShadowMgr::exportXMLSettings(ofstream &xmlFile  )
{
	guardfunc;
	if(	!xmlFile.is_open() )
		return false;
	int result = 1;

	xmlFile << "	<CTerrainShadowMgr Number = "
			<< '"'	<< m_nShadowCount 	<<'"'<<">" <<endl;
	if( m_nShadowCount )
	{
		//////////////////////////////////////////////////////////////////////////
		// ShadowStructs
		for( int i = 0; i < m_nShadowCount; i++ )
		{
			xmlFile << "			<ShadowStructs>"
					<<m_pShadows[i].nBlockX
					<<m_pShadows[i].nBlockY
					<<m_pShadows[i].nMapID
					<<m_pShadows[i].nTextureID
					<<m_pShadows[i].x
					<<m_pShadows[i].y
					<<m_pShadows[i].dwFrame;
			for( int nX = 0; nX <eShadowRes; nX++ )
			{
				for( int nY = 0; nY <eShadowRes; nY++ )
				{
					xmlFile << (m_pShadows[i].dwDiffuse[nX][nY]);
					xmlFile << (m_pShadows[i].bMask[nX][nY]);
				}
			}
			for(int nX = 0; nX<4; nX++ )
			{
				xmlFile << m_pShadows[i].p[nX].x << m_pShadows[i].p[nX].y << m_pShadows[i].p[nX].z;
				xmlFile << m_pShadows[i].uv[nX].x << m_pShadows[i].uv[nX].y;
			}	
			xmlFile	<< "			</ShadowStructs>"<<endl;
		}
		//////////////////////////////////////////////////////////////////////////
		//	Texture Number
		int nTileResX = m_nShadowMapWidth/eShadowRes;
		int nTileRexY = m_nShadowMapHeight/eShadowRes;
		int nMapCount = m_nShadowCount/(nTileResX*nTileRexY);
		xmlFile << "				<Texture TextureCount ="<<'"' << nMapCount+1 << '"'
				<<	" Aplha = " << '"' << m_dwShadowColor << '"'
				<<	" TextureWidth = " << '"' << m_nShadowMapWidth << '"'
				<<	" TextureHeight = " << '"' << m_nShadowMapHeight << '"'
				<<	">" <<endl;
		for(int  i=0; i<nMapCount+1; i++ )
		{
		//	char *pData = (char*)m_pdwShadowMaps[i];
		//	xmlFile.write( pData, sizeof(DWORD)*m_nShadowMapWidth*m_nShadowMapHeight );
		}
		xmlFile<< "				   </Texture>" <<endl;
	}
	
		//xmlFile << "<>"
	xmlFile << "	</CTerrainShadowMgr>" <<endl;


	return true;
	unguard;
}

