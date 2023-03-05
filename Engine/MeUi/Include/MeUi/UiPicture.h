
#pragma once

#include "MeRTLibs.h"
#include "Dxsdk/d3d9types.h"
#include "Dxsdk/d3d9.h"
#include "Singleton.h"
namespace UiDrawer
{
	typedef short (*funRegisterTexture)( IN const char *name, BOOL bWarning, bool bUseBlp );
	typedef short (*funRegisterTextureFromFileMem)( IN const char *name, void* pSrcData, unsigned int nLength, BOOL bWarning, bool bUseBlp );
	typedef void (*funUnregisterTexture)( short stTextureId );
	typedef void (*funBlt)( LPDIRECT3DTEXTURE9 pd3dTexture, LPRECT lpDestRect, LPRECT lpSrcRect,
		int nSrcWidth, int nSrcHeight, float z, DWORD dwColor, DWORD dwFlag );
	typedef void (*funDrawRect2D)( IN RECT& rect, DWORD dwColor );
	//	typedef void (*funFillRect2D)( IN RECT& rect, DWORD dwColor );
	typedef void (*funFillRect2DEx)( IN RECT& rect, DWORD col1,DWORD col2,DWORD col3,DWORD col4 );
	typedef void (*funDrawProgressRect)( int x, int y, int size, int nDegree );

	extern funRegisterTexture		RegisterTexture;
// 	extern funRegisterTextureFromFileMem RegisterTextureFromFileMem;
	extern funUnregisterTexture		UnregisterTexture;
	extern funBlt					Blt;
	extern funDrawRect2D			DrawRect2D;
	//	extern funFillRect2D			FillRect2D;
	extern funFillRect2DEx			FillRect2DEx;
	extern funDrawProgressRect		DrawProgressRect;
	//
	void FillRect2D( IN RECT& rect, DWORD dwColor );

	// added, jiayi, [2009/9/17]
	extern DWORD dwStartTime;		
	extern float fDuration;
	extern DWORD dwColor;
	extern bool	 bFadeIn;
	extern bool  bStartFillFullScreen;
	extern int	 nColorFactor;
	extern int   nAlphaFactor;
	void StartFillFullScreen( float fDur, bool bFIn = true, int nColorFac = 30, int nAlphaFac = 180 );
	void StopFillFullScreen();
	void FillFullScreen( int nScreenWidth, int nScreenHeight, DWORD dwCurrentTime = HQ_TimeGetTime() );
}




//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class ControlPictureManager : public Singleton<ControlPictureManager>
{
public:
	struct S_Pic
	{
		int				m_nId;
		std::string		m_strName;
		int				m_TextureId;
		int				m_RefCount;
		LPDIRECT3DTEXTURE9		m_pd3dTexture;
		DWORD			m_dwLastUseTime;
		void	RegisterTexture( IN const char* szName );
		void	UnregisterTexture();
		S_Pic()
		{
			m_nId = -1;
			m_TextureId = -1;
			m_pd3dTexture = NULL;
			m_RefCount = 0;
		}
	private:
		bool	TestPower( int nNum );		// 检验是否是2的幂次方
// 		struct TargaHeader
// 		{
// 			BYTE IDLength;
// 			BYTE ColormapType;
// 			BYTE ImageType;
// 			BYTE ColormapSpecification[5];
// 			WORD XOrigin;
// 			WORD YOrigin;
// 			WORD ImageWidth;
// 			WORD ImageHeight;
// 			BYTE PixelDepth;
// 			BYTE ImageDescriptor;
// 		};
	};

public:
	void	Run();

	S_Pic*  RetrievePic( int& nPicId,const char* pszFilename);
	unsigned long	BitBlt( IN OUT int* pPicId, IN const char* szFileName,
		IN RECT* pDstRc, IN RECT* pSrcRc = NULL,
		D3DCOLOR col = 0xffffffff, const float fZ = 0.0f,
		DWORD _renderFlag = 0 );
	unsigned long	BitBlt2( LPDIRECT3DTEXTURE9 pd3dTexture,
		IN RECT* pDstRc, IN RECT* pSrcRc = NULL,
		D3DCOLOR col = 0xffffffff, const float fZ = 0.0f,
		DWORD _renderFlag = 0 );
	void	Release();
	ControlPictureManager::S_Pic* RegisterTexture( IN OUT int* pPicId, IN const char* szFileName );
	void	UnregisterTexture( IN const char* szFileName );
	void	UnregisterTexture( LPDIRECT3DTEXTURE9 pd3dTexture );
	void	UnregisterTexture( int nPicId );

	void	EnableLoadImage(bool b) { m_bEnableLoadImage = b; }
	bool	ControlPictureManager::RenderNineGrid
		( 
		int& nPicId,
		const char* pszFilename,
		unsigned int uiTotalWidth,
		unsigned int uiTotalHeight,
		unsigned int uiGridWidth,
		unsigned int uiGridHeight,
		RECT* pDstRc, 
		D3DCOLOR kCol = 0xffffffff,
		const float fZ = 0.f,
		DWORD dwRenderFlag = 0
		);

#ifdef _DEBUG
	UINT	GetPicCount(){ return (UINT)m_vtPic.size(); }
	S_Pic*	GetPic( const UINT nIndex );
#endif

private:	
	std::list<S_Pic>	m_vtPic;
	std::map<int ,S_Pic*>		m_PicMap;
	DWORD	m_dwLastPicId;
	bool	m_bEnableLoadImage;

public:
	ControlPictureManager(void);
	~ControlPictureManager(void);
};

#define theControlPictureManager (*ControlPictureManager::Instance())

