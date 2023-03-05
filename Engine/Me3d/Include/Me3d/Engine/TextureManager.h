#pragma once
class ITexture;
// ¿ÉÌæ»»ÌùÍ¼·½°¸
class IReplaceableTextureProj
{
public:
	virtual void SetTextureCount( int nTextureCount ) = 0;
	virtual int  GetTextureCount() = 0;
	virtual BOOL SetRenderTextureID( int nTexture, int nRenderTextureID ) = 0;
	virtual short  GetRenderTextureID( int nTexture ) = 0;
};



class ITextureManager
{
public:
	virtual ~ITextureManager(){}

	virtual short	RegisterTexture( const char *name,BOOL bMultiThreadLoading, BOOL bIsDelayDestroy, BOOL bMipmapFromFile = FALSE) = 0;
// 	virtual short	RegisterTextureFromFileMem( const char *name, void* pSrcData, unsigned int uLength, BOOL bWarning, BOOL bUsepWhenExist, BOOL bMultiThreadLoading, BOOL bIsDelayDestroy = FALSE ) = 0;

// 	virtual short	RegisterTextureToMem( const char* pszFilename, DWORD dwWidth, 
// 		DWORD dwHeight, DWORD dwFormat, BYTE *byBuffer = NULL, DWORD dwSize = 0, DWORD dwPool = 1) = 0;

// 	virtual short	RegisterTerrainAlpha( const char* pszFilename, DWORD dwWidth, 
// 		DWORD dwHeight, DWORD dwFormat, BYTE *byBuffer, DWORD dwSize, DWORD dwPool,BOOL bFromFile = FALSE ) = 0;

	virtual short	RegisterTexture( ITexture* pTexture ) = 0;
	virtual BOOL	UnRegisterTexture( short shId ) = 0;
	virtual short	RegisterTexture( const char* name, DWORD dwWidth, 
		DWORD dwHeight, BYTE* pbyBuffer, DWORD dwFormat, DWORD dwPool /*= D3DPOOL_MANAGED*/) = 0;
	
	virtual ITexture* GetTexture( short shId ) = 0;
	virtual ITexture* CreateTexture() = 0;
	virtual DWORD	GetUsedVideoMemorySize() = 0;
	virtual BOOL	StartTextureLoadingThread() = 0;
	virtual void	CloseTextureLoadingThread() = 0;
	virtual void	ProcessTextureLoadingThread() = 0;

	virtual void	FrameClear() = 0;
    virtual void*   getTextureData( int texId, void* listenter ) = 0;
    virtual ITexture* GetTextureNoLock( short shId ) = 0;
	virtual bool		TryLockTextureManager() = 0;
	virtual bool		LockTextureManager() = 0;
	virtual void		UnLockTextureManager() = 0;

	virtual UINT GetGlobalMipmap() const = 0;
	virtual void SetGlobalMipmap( UINT uiValue ) = 0;
};