/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	TextureNavigationWnd.h
* Date: 	07/03/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_DLG_TEXTURENAVIGATIONWND_H__
#define _UI_DLG_TEXTURENAVIGATIONWND_H__

class CxImage;
class CToolWorld;
struct HelperObject;
////////////////////////////////////////////////////////////////////////////////
class CTextureNavigationWnd : public CStatic
{
public:	
					CTextureNavigationWnd();
					~CTextureNavigationWnd();

	void			Init(UINT nID, CToolWorld* pParentWnd);
	void			Reset();
	bool			SetTextureName( const char* textureName );
	bool			SetTexture( const char* path, const char* textureName );
	void			Draw( CPaintDC *pDC, CRect& rect );
	
	void			UpdateMinimap();
	void			ShowGrid( bool isShowGrid = true );
	void			ShowReachable( bool isShowGrid = true );
	bool			IsShowGrid() const { return m_isShowGrid; };
	bool			IsShowReachable() const { return m_isShowReachable; };
	
protected:
	void			UpdateCurrTile(  );
	bool			DrawGrid( CPaintDC* pDC );
	bool			DrawBgnd( CPaintDC* pDC, CRect& rect );
	bool			DrawCamera( CPaintDC* pDC, CRect& rect );
	
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void	OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void	OnPaint();
public:
	bool			m_isShowGrid;
	bool			m_isShowReachable;
	bool			m_hasTexture;

	Vector		m_cameraDir;

	Vector		m_centerPos;
	
	CWorldTile*		m_curTile;
	sInt32			m_curTileObjCount;

	TCHAR			m_textureName[MAX_PATH];
	CToolWorld*		m_pParentWnd;
	CxImage			m_image;
	flt32			m_heightScale;
	flt32			m_sizeScale;
	CRect			m_showArea;
	CRect			m_tileArea;

#ifdef ST_EDITOR_UI
	NiNodePtr		m_flagModel;
	NiNodePtr		GetFlagModel();
#endif
	HelperObject*	m_flagModel;
	HelperObject*	GetFlagModel();
};





#endif	// _UI_DLG_TEXTURENAVIGATIONWND_H__

