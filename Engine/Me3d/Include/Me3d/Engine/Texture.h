#pragma once

#include "MeRTLibs.h"
#include "Renderer.h"
class ITexture;

/** ÌùÍ¼¼àÌýÆ÷¡£
*/
class ITextureListener
{
public:
    /** Íê³É¼ÓÔØÌùÍ¼
    */
    virtual void loadFinished( ITexture* tex ) = 0;
};

typedef std::list< ITextureListener* > TextureListeners;

class ITexture
{
public:
    enum
    {
        eTextueName = 128
    };

protected:
    char m_szName[eTextueName];

public:
	virtual ~ITexture(){};
	virtual BOOL	CreateFromFile( const char* pszFilename, BOOL bUsepWhenExist, BOOL bMultiThreadLoading, BOOL bMipmapFromFile ) = 0;
	virtual BOOL	Create( const char* pszName, 
		DWORD dwWidth, DWORD dwHeight, 
		DWORD dwFormat, BYTE *pyBuffer, 
		DWORD dwSize, DWORD dwPool,
		BOOL bFromFile = FALSE) = 0;

    virtual BOOL	CreateFromFileInMem( const char* name, void* pSrcData, unsigned int nLength, BOOL bUsepWhenExist, BOOL bMultiThreadLoading ) = 0;

//	virtual BOOL	CreateFromMem( const char* pszFilename, DWORD dwWidth, DWORD dwHeight, DWORD dwFormat ) = 0;

	virtual BOOL	UpdateTexture( BYTE* pbyBuffer, int nWidth, int nHeight, DWORD dwFormat ) = 0;
	virtual BOOL	UpdateTextureToRect( BYTE* pbyBuffer, int nWidth, int nHeight, DWORD dwFormat, INT nX, INT nY ) = 0;
	virtual void	AddRef() = 0;
	virtual void	DecRef() = 0;
	virtual int		GetRef() = 0;
	virtual void	SetTextureID( short shID ) = 0;
	virtual short	GetTextureID() = 0;
	virtual const char* GetFilename() = 0;
	virtual void	SetName( const char* pszName ) = 0;
	const char* GetName() { return m_szName; }
	virtual void*	GetData() = 0;
	virtual BOOL	Release() = 0;

	virtual	void	SetDelayDestroy(BOOL bDelay) = 0;
	virtual BOOL	IsDelayDestory()	 = 0;

	virtual	void	SetBornTime(DWORD dwTime)	 = 0;
	virtual DWORD	GetBornTime()				 = 0;	
	virtual	DWORD	SetLOD(int nLod) = 0;	


	//virtual BOOL CreateFromMemory( BYTE*)
    
    /** Ìí¼Ó¼àÌýÆ÷
    */
    virtual void addTextureListener( ITextureListener* listener ) = 0;

    /** É¾³ý¼àÌýÆ÷
    */
    virtual void removeTextureListener( ITextureListener* listener ) = 0;

    /** É¾³ýËùÓÐ¼àÌýÆ÷
    */
    virtual void removeAllTextureListener() = 0;

    /** µÃµ½ËùÓÐ¼àÌýÆ÷
    */
    virtual TextureListeners& getTextureListeners() = 0;
};
