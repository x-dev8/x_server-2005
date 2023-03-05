#pragma once

#include "Me3d/Me3d.h"
#include "Me3d/Engine/Renderer.h"
#include "Me3d/Engine/EngineInstance.h"
#include "Texture.h"
#include "Mutex.h"

//
//	ETextureFormat
//
enum ETextureFormat
{
	TEXF_P8			= 0x00,
	TEXF_RGBA7		= 0x01,
	TEXF_RGB16		= 0x02,
	TEXF_DXT1       = 0x03,
	TEXF_RGB8       = 0x04,
	TEXF_RGBA8      = 0x05,
	TEXF_NODATA		= 0x06,
	TEXF_DXT3		= 0x07,
	TEXF_DXT5		= 0x08,
	TEXF_L8			= 0x09,
	TEXF_G16		= 0x0a,
	TEXF_RRRGGGBBB	= 0x0b,
	TEXF_MAX		= 0xff
};

#define RELEASE_COM_OBJ(x)\
if (x != NULL)\
{ x->Release(); x = NULL; }\

class UncompressedTexture
{
public:
	UncompressedTexture() : Texture(0), Surface(0), DecompressedSucceed(0) {}
	~UncompressedTexture() { Destroy(); }

	HRESULT Create(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format)
	{
		LPDIRECT3DDEVICE9 RealDevice = (LPDIRECT3DDEVICE9) GetEngine()->GetRenderer()->GetRealDevice();
		assert(RealDevice != NULL);
		assert(Width > 0 && Height > 0);

		HRESULT hr = RealDevice->CreateTexture(Width, Height, Levels, Usage, Format, D3DPOOL_MANAGED, &Texture, NULL);
		if (FAILED(hr))
			return hr;

		hr = Texture->GetSurfaceLevel(0, &Surface);
		if (FAILED(hr))
		{
			Destroy();
			return hr;
		}

		return S_OK;
	}

	HRESULT DecompressCompressedTextureSurface(LPDIRECT3DTEXTURE9 Src, const RECT *SrcRect, DWORD Filter, D3DCOLOR ColorKey)
	{
		assert(Src != NULL);

		if (Texture == NULL)
			return S_FALSE;

		LPDIRECT3DSURFACE9 SrcSurface = NULL;
		HRESULT hr = Src->GetSurfaceLevel(0, &SrcSurface);
		if (FAILED(hr))
			return hr;

		hr = D3DXLoadSurfaceFromSurface(Surface, 0, 0, SrcSurface, 0, SrcRect, Filter, ColorKey);
		if (FAILED(hr))
		{
			Destroy();
			RELEASE_COM_OBJ(SrcSurface);
			return hr;
		}

		RELEASE_COM_OBJ(SrcSurface);
		DecompressedSucceed = true;		
		return S_OK;
	}

	LPDIRECT3DTEXTURE9 GetTexturePtr()
	{
		return DecompressedSucceed ? Texture : NULL;
	}

private:
	void Destroy()
	{
		RELEASE_COM_OBJ(Texture);
		RELEASE_COM_OBJ(Surface);
	}
	
	LPDIRECT3DTEXTURE9 Texture;
	LPDIRECT3DSURFACE9 Surface;
	BOOL DecompressedSucceed;
};

//
//  IsDXTC
//
inline BOOL IsDXTC( ETextureFormat Format )
{
	return ( (Format == TEXF_DXT1) || (Format == TEXF_DXT3) || (Format == TEXF_DXT5) );
}


//
//	GetBytesPerPixel
//
inline INT GetBytesPerPixel(DWORD Format,INT NumPixels)
{
	switch(Format)
	{
	case D3DFMT_DXT1:
		return NumPixels / 2;
	case D3DFMT_A8R8G8B8:
		return NumPixels * 4;
	case D3DFMT_DXT3:
	case D3DFMT_DXT5:
		return NumPixels;
	case D3DFMT_R8G8B8:
		return NumPixels * 3;
	};

	return 0;
}

//
//  CalculateTexelPointer
//
inline BYTE* CalculateTexelPointer(BYTE* Base,DWORD Format,INT Stride,INT X,INT Y)
{
	switch(Format)
	{
	case D3DFMT_DXT1:
		return Base + Stride * (Y / 4) + (X * 2);
	case D3DFMT_DXT3:
	case D3DFMT_DXT5:
		return Base + Stride * (Y / 4) + (X * 4);
	case D3DFMT_A8R8G8B8:
//	case D3DFMT_RGBA7:
		return Base + Stride * Y + X * 4;
	case D3DFMT_R8G8B8:
		return Base + Stride * Y + X * 3;
	//case TEXF_G16:
	//	return Base + Stride * Y + X * 2;
	//case TEXF_P8:
	//case TEXF_L8:
	//	return Base + Stride * Y + X;
	};

	return Base;
}


class TextureDx8:public ITexture,public CSemiAutoIntLock, public MeCommonAllocObj<TextureDx8>
{
public:
	TextureDx8();
	virtual ~TextureDx8();
	void	AddRef();
	void	DecRef();
	int		GetRef(){ return m_nRefCount; }
	void	SetTextureID( short shID ){ m_shTextureID = shID; }
	short	GetTextureID(){ return m_shTextureID; }
	const char*	GetFilename();
	void	SetName( const char* pszName );
	//const char* GetName(){ return m_szName; }
	BOOL	CreateFromFile( const char* pszFilename, BOOL bUsepWhenExist, BOOL bMultiThreadLoading, BOOL bMipmapFromFile );
    BOOL	CreateFromFileInMem( const char* name, void* pSrcData, unsigned int nLength, BOOL bUsepWhenExist, BOOL bMultiThreadLoading );
//	BOOL	CreateFromMem( const char* pszFilename, DWORD dwWidth, DWORD dwHeight, DWORD dwFormat = D3DFMT_A8R8G8B8 );

	BOOL	Create( const char* pszName, DWORD dwWidth, DWORD dwHeight, DWORD dwFormat, BYTE *pyBuffer = NULL, DWORD dwSize = 0, DWORD dwPool = D3DPOOL_MANAGED,BOOL bFromFile = FALSE);
	BOOL	UpdateTexture( BYTE* pbyBuffer, int nWidth, int nHeight, DWORD dwFormat );
	BOOL	UpdateTextureToRect( BYTE* pbyBuffer, int nWidth, int nHeight, DWORD dwFormat, INT nX, INT nY );
	void*	GetData();//{ return m_pd3dTexture; }
	BOOL	Release();
	virtual	DWORD	SetLOD(int nLod) ;	


    /** Ìí¼Ó¼àÌýÆ÷
    */
    virtual void addTextureListener( ITextureListener* listener )
    {
        if ( listener )
            _texListeners.push_back( listener );
    }

    /** É¾³ý¼àÌýÆ÷
    */
    virtual void removeTextureListener( ITextureListener* listener )
    {
        TextureListeners::iterator it = std::find( _texListeners.begin(), _texListeners.end(), listener );
        if ( it != _texListeners.end() )
        {
            delete *it;
            _texListeners.erase( it );
        }
    }

    /** É¾³ýËùÓÐ¼àÌýÆ÷
    */
    virtual void removeAllTextureListener()
    {
        TextureListeners::iterator it, end = _texListeners.end();
        for ( it = _texListeners.begin(); it != end; ++it )
        {
            delete *it;
        }
        _texListeners.clear();
    }

    /** µÃµ½ËùÓÐ¼àÌýÆ÷
    */
    virtual TextureListeners& getTextureListeners()
    {
        return _texListeners;
    }

    

public:
	//////////////////////////////////////////////////////////////////////////
	void	SetFilename( const char* pszFilename );

	void	SetDelayDestroy(BOOL bDelay);
	BOOL	IsDelayDestory() { return m_bDelayDestroy; }

	LPDIRECT3DTEXTURE9 GetTexture();
	LPDIRECT3DTEXTURE9* GetD3DTexture(){ return &m_pd3dTexture; }
	void	SetSerialNo( int nSerialNo ){ m_nSerialNo = nSerialNo; }
	int		GetSerialNo(){ return m_nSerialNo; }
	void	SetBornTime(DWORD dwTime)	{ m_dwBornTime = dwTime; }
	DWORD	GetBornTime()				{	return m_dwBornTime; }
private:
	BOOL	CreateFromMemory( const char* pszFilename );
public:
	int					m_nSerialNo;
	int					m_nRefCount;

	char				m_szFilename[MAX_PATH];
	//char				m_szName[eTextueName];

	LPDIRECT3DTEXTURE9	m_pd3dTexture;

	short				m_stVideoWidth;
	short				m_stVideoHeight;
	BYTE				m_byBPP;
	short				m_shTextureID;
	bool				m_bLoaded;

	BOOL				m_bDelayDestroy;
	DWORD				m_dwBornTime;

    TextureListeners   _texListeners;

};

HRESULT HrCreateTextureFromFileInMemory ( 
	IRenderer* RI, LPCVOID pSrcData,
	UINT SrcDataSize, LPDIRECT3DTEXTURE9* ppTexture);
HRESULT HrCreateTextureFromFile ( IRenderer* RI, LPCSTR pSrcFile, LPDIRECT3DTEXTURE9* ppTexture, BOOL bMipmapFromFile);
