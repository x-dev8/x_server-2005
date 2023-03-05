///////////////////////////////////////////////////////////////////
//
// class:       SkyBox
///////////////////////////////////////////////////////////////////


#ifndef __ST_SKYBOX_HEADERFILE__
#define __ST_SKYBOX_HEADERFILE__

#include "Me3d\skybox.h"
// #include "Scene/DayLightAnim.h"

class CSTSkyBox : public CSkyBox
{
public:
	CSTSkyBox();
	~CSTSkyBox();
	void Release();
	void RenderSkyBox(D3DXVECTOR3& vPos, const char* pszSkyboxPath = 0);
	void RenderSkyBoxWithZ( D3DXVECTOR3& vPos, const char* pszSkyboxPath = 0 );
	void RenderSkyItem(D3DXVECTOR3 vPos);

	MexAnimCtrl * GetSkybox() const { return m_pSkybox; }
	void SetSkybox(MexAnimCtrl * val) { m_pSkybox = val; }
	void SetSkybox(const char* pszSkyboxPath);

protected://yd add
	MexAnimCtrl *	m_pSkybox;
	MexAnimCtrl *m_pSrcSkybox;
	MexAnimCtrl *m_pDestSkybox;
	INT				m_nSkyBoxModelID;

// 	std::map<std::string, DayLightAnim*>				m_mapDayLightAnim;
	std::map<std::string, MexAnimCtrl*>					m_SkyBoxBuf;

	void				FastAlphaRenderSky( 
		MexAnimCtrl *SrcSkybox, 
		MexAnimCtrl *DestSkybox,
		Vector& vPos, 
		FLOAT fCurAlpha,
		FLOAT fMaxDestAlpha = 1.0f, 
		FLOAT fMaxSrcAlpha  = 1.0f );

	FLOAT				m_fSkyBoxAlpha;
// 	class DayLightAnim*		m_pDayLightAnim;
// 	class CDayLightChange		*m_pLightChange;
	FLOAT				GetSkyBoxScale( void );
	FLOAT				GetSkyBoxHeight( );
	MexAnimCtrl*		FindSkyBox( const char* szPath  );
	INT					GetSkyBoxModelID( void );

	BOOL				ClearDayLightAnim();
	BOOL				LoadDayNightAnim( char *szFile );	
	virtual	void		RestoreFog();
};

CSTSkyBox* GetSTSkyBox();

#endif //__ST_SKYBOX_HEADERFILE__
