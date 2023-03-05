/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	TextureWindow.h
* Date: 	03/14/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_DLG_TEXTUREWINDOW_H__
#define _UI_DLG_TEXTUREWINDOW_H__


class CTextureWindow : public CWnd
{
public:
					CTextureWindow();
					~CTextureWindow();
	
	void			Create( CWnd *parentWnd, RECT& rect );
	void			EnableUpdate( bool bEnable );
	void			UpdateScrollSizes();
	void			HighlightCurTexture( CDC *pDC = NULL );
	void			SetDisplaySize( int iSize );
	void			SelectTexture( LPCTSTR pszTexture, BOOL bAllowRedraw = TRUE );

protected:
	//{{AFX_MSG(CTextureWindow)
	afx_msg void	OnPaint();
	afx_msg void	OnSize(UINT nType, int cx, int cy);
	afx_msg void	OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void	OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void	OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void	OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void	OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void	OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL	OnMouseWheel(UINT nFlags, short zDelta, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	int				m_totalX;
	int				m_totalY;
	int				m_displaySize;
	
	CRect			m_rectHighlight;

};




#endif	// _UI_DLG_TEXTUREWINDOW_H__

