/********************************************************************
	created:	2004/06/16
	created:	16:6:2004   10:16
	filename: 	e:\UIEditor\PicEditorDlg.h
	file path:	e:\UIEditor
	file base:	PicEditorDlg
	file ext:	h
	author:		WitSun
	
	purpose:	PicEditorDlg
*********************************************************************/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "TgaCore.h"

#include "MenuXp/ComboBoxXP.h"

// CPicEditorDlg 对话框
#define PIC_RIGHT_BOARD		26
#define PIC_BOTTOM_BOARD	53
#define BUTTON_OK_X			164
#define BUTTON_OK_Y			31
#define BUTTON_CANCEL_X		86
#define BUTTON_CANCEL_Y		31

#define SELECT_MIN_SIZE		10

class CPicEditorDlg : public CDialog
{
	DECLARE_DYNAMIC(CPicEditorDlg)

public:
	void	SetPicStruct( const S_BaseData::S_Pic* pstPic );
	void	SetCurSelPicName( const char* pstrName );
	void	SetFrameRect( const RECT* prc );
	void	SetClientRect( const RECT* prc );

	char*	GetCurSelPicName(){ return m_strCurSelFileName.GetBuffer(); }
	RECT	GetFrameRect();
	RECT	GetClientRect();

private:
	void	ShowPic( const char* pstrName );
	bool	LoadPic( HBITMAP hBitmap );
	void	RefeashUI( int nWidth, int nHeight );
	void	LButtonDownRect( CPoint point );
	void	RectClip( CRect* pSrc, CRect* pDst, int nMinSize = 0 );
	void	UpdateRect( bool bToRect = true );
	void	FindPic( const char* szFilePath, const char* szPath );

private:
	bool	m_bInit;
	int		m_nSrcX, m_nSrcY;
	CDC		m_dcMem;
	CRect	m_rcPicClient;
	int		m_nOffsetX, m_nOffsetY;
	bool	m_bErase;
	CGraphicsFileData	m_Tga;
	CRectTracker		m_rcSelect;
	CString				m_strCurSelFileName;

private:
	int m_nSelectionLeft;
	int m_nSelectionTop;
	int m_nSelectionRight;
	int m_nSelectionBottom;
	int m_nMarginsLeft;
	int m_nMarginsTop;
	int m_nMarginsRight;
	int m_nMarginsBottom;
	CComboBoxXP m_comboFileName;
	CStatic m_staticPic;
	CScrollBar m_barH;
	CScrollBar m_barV;

private:
	int		m_nLastSrcX, m_nLastSrcY;
	CRect	m_rcLastPicClient;
	int		m_nLastOffsetX, m_nLastOffsetY;
	CRectTracker		m_rcLastSelect;
	CString				m_strLastCurSelFileName;

public:
	afx_msg void OnDeltaposSpinSelectionLeft(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinSelectionTop(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinSelectionRight(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinSelectionBottom(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMarginsLeft(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMarginsTop(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMarginsRight(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMarginsBottom(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditSelectionLeft();
	afx_msg void OnEnChangeEditSelectionTop();
	afx_msg void OnEnChangeEditSelectionRight();
	afx_msg void OnEnChangeEditSelectionBottom();
	afx_msg void OnEnChangeEditMarginsLeft();
	afx_msg void OnEnChangeEditMarginsTop();
	afx_msg void OnEnChangeEditMarginsRight();
	afx_msg void OnEnChangeEditMarginsBottom();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	CPicEditorDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPicEditorDlg();
	enum { IDD = IDD_DIALOG_PIC_EDITOR };
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnCbnSelchangeComboFileName();
};

//extern CPicEditorDlg	thePicEditorDlg;
