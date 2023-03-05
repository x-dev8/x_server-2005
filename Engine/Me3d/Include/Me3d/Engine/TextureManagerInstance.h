#pragma once

#include "TextureManager.h"
#include "Texture.h"
#include "TextureDx8.h"

class MexReplaceableTextureProj:public IReplaceableTextureProj
{
public:
	MexReplaceableTextureProj();
	~MexReplaceableTextureProj();
	void SetTextureCount( int nTextureCount );
	int  GetTextureCount(){ return m_vectorRenderTextureID.size(); }
	BOOL SetRenderTextureID( int nTexture, int nRenderTextureID );
	short  GetRenderTextureID( int nTexture );
	static short	 RegisterTexture( const char* pszMexFilename, const char* pszTextureFilename, BOOL bMult = false );
	void UnRegisterTextures();
	void Loaded( BOOL bLoaded ){ m_bLoaded = bLoaded; }
	BOOL IsLoaded(){ return m_bLoaded; }
	BOOL ReplaceTexture( short shTextureID, const char* pszMexFilename, const char* pszTextureFilename, BOOL bMult = false );	// ±à¼­Æ÷Ê¹ÓÃ£¬Ìæ»»Ìì¿ÕºÐÌùÍ¼
protected:
	BOOL m_bLoaded;
	std::vector<short> m_vectorRenderTextureID;

};
class CHRTextureLoadingReq : public MeCommonAllocObj<CHRTextureLoadingReq>
{
public:
	CHRTextureLoadingReq();
public:
	int		m_nSerialNo;
	BOOL	m_bMipmapFromFile;
	int		m_nTextureID;	
	char	m_szFileName[MAX_PATH];
	LPDIRECT3DTEXTURE9 m_pD3DTexture;
};
class CHRTextureLoadingMgr
{

};

class CHRTextureManagerInstance:public ITextureManager
{
public:
	enum
	{
		//eMaxTexture = 8192,
		eMaxTexture = 8192,
	};
public:
	CHRTextureManagerInstance();
	~CHRTextureManagerInstance();
	void		Destroy();

	short		RegisterTexture(const char* pName, 								
								BOOL bMultiThreadLoading,
								BOOL bIsDelayDestroy,
								BOOL bMipmapFromFile = FALSE );

// 	short		RegisterTextureFromFileMem(const char *name, 
//                                 LPVOID pSrcData,
//                                 UINT uLength,
// 								BOOL bWarning, 
// 								BOOL bUsepWhenExist,
// 								BOOL bMultiThreadLoading,
// 								BOOL bIsDelayDestroy = FALSE );

// 	short		RegisterTextureToMem( const char* pszFilename, 
// 										DWORD dwWidth, DWORD dwHeight, 
// 										DWORD dwFormat = D3DFMT_A8R8G8B8, BYTE* byBuffer = NULL,
// 										DWORD dwSize = 0, DWORD dwPool = D3DPOOL_MANAGED );

// 	short		RegisterTerrainAlpha( const char* pszFilename, 
// 										DWORD dwWidth, DWORD dwHeight, 
// 										DWORD dwFormat = D3DFMT_A8R8G8B8, BYTE* byBuffer = NULL,
// 										DWORD dwSize = 0, DWORD dwPool = D3DPOOL_MANAGED, BOOL bFromFile = FALSE );

	short		RegisterTexture( ITexture* pTexture );
	short		RegisterTexture( 
								const char* name, 
								DWORD dwWidth, 
								DWORD dwHeight, 
								BYTE* pbyBuffer,
								DWORD dwFormat, 
								DWORD dwPool /*= D3DPOOL_MANAGED*/);
	BOOL		UnRegisterTexture( short stTextureId );
	BOOL		StartTextureLoadingThread();
	void		CloseTextureLoadingThread();
	void		ProcessTextureLoadingThread();

	ITexture* GetTexture( short shId );
	ITexture* CreateTexture();
	DWORD		GetUsedVideoMemorySize()	{ return m_dwUsedVideoMemorySize; }
    void		FrameClear();

    virtual void* getTextureData( int texId, void* listenter );

    virtual ITexture* GetTextureNoLock( short shId );
	virtual bool		TryLockTextureManager();
	virtual bool		LockTextureManager();
	virtual void		UnLockTextureManager();

	UINT GetGlobalMipmap() const{ return m_uiMipmapLevel; }
	void SetGlobalMipmap( UINT uiValue ){ m_uiMipmapLevel = uiValue; }
public:
	int			FindTexture( const char* pszName );
protected:
	int					m_nDefTextureID;
	static ITexture*	m_textures[eMaxTexture];
	DWORD				m_dwUsedVideoMemorySize;

	INT					m_nMinTexture;
	bool				m_bDelayQueue[eMaxTexture];
	UINT				m_uiMipmapLevel;
};
