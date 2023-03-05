#pragma once
#include <windows.h>
#include "Dxsdk/d3dx9.h"
union MapPointer;
#include "ioxml/IOXMLObject.h"
class CTerrainShadowMgr:public IOXMLObject
{
public:
	bool loadXMLSettings(XMLElement *element);
	bool exportXMLSettings(ofstream &xmlFile  );
public:
	enum
	{
		eShadowRes = 3,
		eMaxShadow = 65535,
		eMaxShadowMap = 16
	};
	struct Shadow
	{
		bool bMask[eShadowRes][eShadowRes];
		DWORD dwDiffuse[eShadowRes][eShadowRes];
		int x, y;
		int nBlockX, nBlockY;
		int nMapID;
		int nTextureID;
		
		D3DXVECTOR3 p[4];
		D3DXVECTOR2 uv[4];
		DWORD dwFrame;
		Shadow();
	};

public:
	CTerrainShadowMgr(void);
	~CTerrainShadowMgr(void);

	BOOL	CreateShadowMap( int nWidth, int nHeight );
	bool	LoadShadowMap( const char* pszFileName );
	bool	SaveShadowMap( const char* pszFileName );
	// 注册一个新的地图Tile Shadow
	int		RegisterShadow( Shadow* pShadow );

	BOOL	PushShadow( int nShadowID );
	void	Clear();
	void	BeginRenderShadow();
	void	Render();
	Shadow*	GetShadow( int i );
	DWORD*  GetShadowBuffer( int i );
	Shadow*	GetShadow(int x, int y) ;		//取得X,Y 坐标的Shadow
	int*	GetShadowIDs() { return m_pnRenderShadowIDs; }
	int		GetShadowNumber() { return m_nShadowCount; }
	BOOL	DebugLog( const char* pszFileName );
	BOOL	MakeShadowMapName( int i, char szPath[], int nPathSize );

	int		GetShadowMapTextureID( int nShadowMapID );
	int		GetTextureSize() { return m_nShadowMapWidth; }
	bool	ReadFromMap( MapPointer InP, int InSize );
	
protected:
	int		m_nShadowCount;
	Shadow	*m_pShadows;//[eMaxShadow];

	int		m_nRenderShadowCount;
	int		*m_pnRenderShadowIDs;//[eMaxShadow];

	int		m_nShadowMapCount;
	int		m_nShadowMapWidth;
	int		m_nShadowMapHeight;
	DWORD*	m_pdwShadowMaps[eMaxShadowMap];
	int		m_nShadowMapTextureIDs[eMaxShadowMap];
	//POINT   m_posBlock[eMaxShadowMap];
	DWORD	m_dwShadowColor;

	DWORD	m_dwFrame;

};
//extern CTerrainShadowMgr* GetTerrainShadowMgr();