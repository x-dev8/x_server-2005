// PicEditorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UIEditor.h"
#include "PicEditorDlg.h"
#include <assert.h>
//#include "Frame.h"
#include "UIObjectDlg.h"

//CPicEditorDlg	thePicEditorDlg;
// CPicEditorDlg 对话框

IMPLEMENT_DYNAMIC(CPicEditorDlg, CDialog)
CPicEditorDlg::CPicEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPicEditorDlg::IDD, pParent)
	, m_nSelectionLeft(0)
	, m_nSelectionTop(0)
	, m_nSelectionRight(0)
	, m_nSelectionBottom(0)
	, m_nMarginsLeft(0)
	, m_nMarginsTop(0)
	, m_nMarginsRight(0)
	, m_nMarginsBottom(0)
{
	m_bInit = false;

	m_nSrcX = m_nSrcY = 0;
	m_rcPicClient.SetRectEmpty();
	m_nOffsetX = m_nOffsetY = 0;
	m_bErase = false;
	m_rcSelect.m_rect.SetRect( 0,0, SELECT_MIN_SIZE, SELECT_MIN_SIZE);
	m_rcSelect.m_sizeMin.SetSize(SELECT_MIN_SIZE,SELECT_MIN_SIZE);
	m_rcSelect.m_nStyle = CRectTracker::solidLine | CRectTracker::resizeOutside;
}

CPicEditorDlg::~CPicEditorDlg()
{
}

void CPicEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SELECTION_LEFT, m_nSelectionLeft);
	DDV_MinMaxInt(pDX, m_nSelectionLeft, 0, INT_MAX);
	DDX_Text(pDX, IDC_EDIT_SELECTION_TOP, m_nSelectionTop);
	DDV_MinMaxInt(pDX, m_nSelectionTop, 0, INT_MAX);
	DDX_Text(pDX, IDC_EDIT_SELECTION_RIGHT, m_nSelectionRight);
	DDV_MinMaxInt(pDX, m_nSelectionRight, 0, INT_MAX);
	DDX_Text(pDX, IDC_EDIT_SELECTION_BOTTOM, m_nSelectionBottom);
	DDV_MinMaxInt(pDX, m_nSelectionBottom, 0, INT_MAX);
	DDX_Text(pDX, IDC_EDIT_MARGINS_LEFT, m_nMarginsLeft);
	DDV_MinMaxInt(pDX, m_nMarginsLeft, 0, INT_MAX);
	DDX_Text(pDX, IDC_EDIT_MARGINS_TOP, m_nMarginsTop);
	DDV_MinMaxInt(pDX, m_nMarginsTop, 0, INT_MAX);
	DDX_Text(pDX, IDC_EDIT_MARGINS_RIGHT, m_nMarginsRight);
	DDV_MinMaxInt(pDX, m_nMarginsRight, 0, INT_MAX);
	DDX_Text(pDX, IDC_EDIT_MARGINS_BOTTOM, m_nMarginsBottom);
	DDV_MinMaxInt(pDX, m_nMarginsBottom, 0, INT_MAX);
	DDX_Control(pDX, IDC_COMBO_FILE_NAME, m_comboFileName);
	DDX_Control(pDX, IDC_STATIC_PIC, m_staticPic);
	DDX_Control(pDX, IDC_SCROLLBAR_H, m_barH);
	DDX_Control(pDX, IDC_SCROLLBAR_V, m_barV);
}

BEGIN_MESSAGE_MAP(CPicEditorDlg, CDialog)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SELECTION_LEFT, OnDeltaposSpinSelectionLeft)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SELECTION_TOP, OnDeltaposSpinSelectionTop)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SELECTION_RIGHT, OnDeltaposSpinSelectionRight)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SELECTION_BOTTOM, OnDeltaposSpinSelectionBottom)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MARGINS_LEFT, OnDeltaposSpinMarginsLeft)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MARGINS_TOP, OnDeltaposSpinMarginsTop)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MARGINS_RIGHT, OnDeltaposSpinMarginsRight)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MARGINS_BOTTOM, OnDeltaposSpinMarginsBottom)
	ON_EN_CHANGE(IDC_EDIT_SELECTION_LEFT, OnEnChangeEditSelectionLeft)
	ON_EN_CHANGE(IDC_EDIT_SELECTION_TOP, OnEnChangeEditSelectionTop)
	ON_EN_CHANGE(IDC_EDIT_SELECTION_RIGHT, OnEnChangeEditSelectionRight)
	ON_EN_CHANGE(IDC_EDIT_SELECTION_BOTTOM, OnEnChangeEditSelectionBottom)
	ON_EN_CHANGE(IDC_EDIT_MARGINS_LEFT, OnEnChangeEditMarginsLeft)
	ON_EN_CHANGE(IDC_EDIT_MARGINS_TOP, OnEnChangeEditMarginsTop)
	ON_EN_CHANGE(IDC_EDIT_MARGINS_RIGHT, OnEnChangeEditMarginsRight)
	ON_EN_CHANGE(IDC_EDIT_MARGINS_BOTTOM, OnEnChangeEditMarginsBottom)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_FILE_NAME, OnCbnSelchangeComboFileName)
END_MESSAGE_MAP()


// CPicEditorDlg 消息处理程序


void CPicEditorDlg::OnDeltaposSpinSelectionLeft(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta == -1)
	{
		if( --m_nSelectionLeft < 0 ) m_nSelectionLeft=0;
	}
	else if (pNMUpDown->iDelta == 1)
	{
		m_nSelectionLeft++;
	}
	UpdateRect(true);
	UpdateData(FALSE);

	*pResult = 0;
}

void CPicEditorDlg::OnDeltaposSpinSelectionTop(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta == -1)
	{
		if( --m_nSelectionTop < 0 ) m_nSelectionTop=0;
	}
	else if (pNMUpDown->iDelta == 1)
	{
		m_nSelectionTop++;
	}
	UpdateRect(true);
	UpdateData(FALSE);
	*pResult = 0;
}

void CPicEditorDlg::OnDeltaposSpinSelectionRight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta == -1)
	{
		if( --m_nSelectionRight < 0 ) m_nSelectionRight=0;
	}
	else if (pNMUpDown->iDelta == 1)
	{
		m_nSelectionRight++;
	}
	UpdateRect(true);
	UpdateData(FALSE);
	*pResult = 0;
}

void CPicEditorDlg::OnDeltaposSpinSelectionBottom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta == -1)
	{
		if( --m_nSelectionBottom < 0 ) m_nSelectionBottom=0;
	}
	else if (pNMUpDown->iDelta == 1)
	{
		m_nSelectionBottom++;
	}
	UpdateRect(true);
	UpdateData(FALSE);
	*pResult = 0;
}

void CPicEditorDlg::OnDeltaposSpinMarginsLeft(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta == -1)
	{
		if( --m_nMarginsLeft < 0 ) m_nMarginsLeft=0;
	}
	else if (pNMUpDown->iDelta == 1)
	{
		m_nMarginsLeft++;
	}
	UpdateData(FALSE);
	*pResult = 0;
}

void CPicEditorDlg::OnDeltaposSpinMarginsTop(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta == -1)
	{
		if( --m_nMarginsTop < 0 ) m_nMarginsTop=0;
	}
	else if (pNMUpDown->iDelta == 1)
	{
		m_nMarginsTop++;
	}
	UpdateData(FALSE);
	*pResult = 0;
}

void CPicEditorDlg::OnDeltaposSpinMarginsRight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta == -1)
	{
		if( --m_nMarginsRight < 0 ) m_nMarginsRight=0;
	}
	else if (pNMUpDown->iDelta == 1)
	{
		m_nMarginsRight++;
	}
	UpdateData(FALSE);
	*pResult = 0;
}

void CPicEditorDlg::OnDeltaposSpinMarginsBottom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta == -1)
	{
		if( --m_nMarginsBottom < 0 ) m_nMarginsBottom=0;
	}
	else if (pNMUpDown->iDelta == 1)
	{
		m_nMarginsBottom++;
	}
	UpdateData(FALSE);
	*pResult = 0;
}

void CPicEditorDlg::OnEnChangeEditSelectionLeft()
{
	UpdateData(TRUE);
	UpdateRect(true);
}

void CPicEditorDlg::OnEnChangeEditSelectionTop()
{
	UpdateData(TRUE);
	UpdateRect(true);
}

void CPicEditorDlg::OnEnChangeEditSelectionRight()
{
	UpdateData(TRUE);
	UpdateRect(true);
}

void CPicEditorDlg::OnEnChangeEditSelectionBottom()
{
	UpdateData(TRUE);
	UpdateRect(true);
}

void CPicEditorDlg::OnEnChangeEditMarginsLeft()
{
	UpdateData(TRUE);
	Invalidate();
}

void CPicEditorDlg::OnEnChangeEditMarginsTop()
{
	UpdateData(TRUE);
	Invalidate();
}

void CPicEditorDlg::OnEnChangeEditMarginsRight()
{
	UpdateData(TRUE);
	Invalidate();
}

void CPicEditorDlg::OnEnChangeEditMarginsBottom()
{
	UpdateData(TRUE);
	Invalidate();
}

BOOL CPicEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bInit = true;

	// 检查是否是已存在的文件
	if ( g_stPath[0] != 0 )
	{
		char szDefinePath[128] = "";
		char szCommonPath[128] = "";
		sprintf( szDefinePath, "%s\\%s\\*.tga", g_stPath, g_stFileName );
		sprintf( szCommonPath, "%s\\Common\\*.tga", g_stPath );
		FindPic( szDefinePath, g_stFileName );
		FindPic( szCommonPath, "Common" );
	}
	else
	{
		MessageBox( "请先保存文件!", "有错误", MB_ICONWARNING );
	}

	m_barV.ShowWindow(false);
	m_barH.ShowWindow(false);

	if ( m_Tga.IsValid() )
	{
		CRect myRect;
		::GetWindowRect( m_hWnd, &myRect);
		RefeashUI( myRect.Width(), myRect.Height() );
		UpdateRect(false);
	}
	else if ( !m_strCurSelFileName.IsEmpty() )
	{
		SetCurSelPicName( m_strCurSelFileName );
	}

	m_nLastSrcX = m_nSrcX;
	m_nLastSrcY = m_nSrcY;
	m_rcLastPicClient = m_rcPicClient;
	m_nLastOffsetX = m_nOffsetX;
	m_nLastOffsetY = m_nOffsetY;
	m_rcLastSelect = m_rcSelect;
	m_strLastCurSelFileName = m_strCurSelFileName;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常：OCX 属性页应返回 FALSE
}

void CPicEditorDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	dc.BitBlt(m_nOffsetX,m_nOffsetY,
				m_rcPicClient.Width(),m_rcPicClient.Height(),
				&m_dcMem,
				m_nSrcX, m_nSrcY,
				SRCCOPY);
	m_bErase = false;

	m_rcSelect.Draw( GetDlgItem(IDC_STATIC_PIC)->GetDC() );
	CBrush	brush( RGB(0,255,0) );
	GetDlgItem(IDC_STATIC_PIC)->GetDC()->FrameRect( m_rcSelect.m_rect, &brush );

	CRect rcLeft,rcTop,rcRight,rcBottom;
	rcLeft.SetRect( m_rcSelect.m_rect.left,
					m_rcSelect.m_rect.top,
					m_rcSelect.m_rect.left+m_nMarginsLeft,
					m_rcSelect.m_rect.bottom );
	rcTop.SetRect( m_rcSelect.m_rect.left,
					m_rcSelect.m_rect.top,
					m_rcSelect.m_rect.right,
					m_rcSelect.m_rect.top+m_nMarginsTop );
	rcRight.SetRect( m_rcSelect.m_rect.right-m_nMarginsRight,
					m_rcSelect.m_rect.top,
					m_rcSelect.m_rect.right,
					m_rcSelect.m_rect.bottom );
	rcBottom.SetRect( m_rcSelect.m_rect.left,
					m_rcSelect.m_rect.bottom-m_nMarginsBottom,
					m_rcSelect.m_rect.right,
					m_rcSelect.m_rect.bottom );
	GetDlgItem(IDC_STATIC_PIC)->GetDC()->FrameRect( rcLeft, &brush );
	GetDlgItem(IDC_STATIC_PIC)->GetDC()->FrameRect( rcTop, &brush );
	GetDlgItem(IDC_STATIC_PIC)->GetDC()->FrameRect( rcRight, &brush );
	GetDlgItem(IDC_STATIC_PIC)->GetDC()->FrameRect( rcBottom, &brush );
}

void CPicEditorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	LButtonDownRect( point );

	CDialog::OnLButtonDown(nFlags, point);
}


bool CPicEditorDlg::LoadPic( HBITMAP hBitmap )
{
	if ( !hBitmap )
	{
		assert( hBitmap );
		return false;
	}
	m_nSrcX = m_nSrcY = 0;
//	BITMAP	bmInfo;
//	GetObject( m_hBitmap, sizeof(BITMAP), &bmInfo );
	SelectObject(m_dcMem, hBitmap );

	CRect myRect;
	::GetWindowRect( m_hWnd, &myRect);
	RefeashUI( myRect.Width(), myRect.Height() );
	return true;
}


void CPicEditorDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	switch (nSBCode)
	{
	case SB_TOP:
		m_nSrcY = 0;
		break;
	case SB_BOTTOM:
		m_nSrcY = INT_MAX;
		break;
	case SB_THUMBTRACK:
		m_nSrcY = nPos;
		break;
	case SB_PAGEUP:
		m_nSrcY -= 50;
		if ( m_nSrcY < 0 )
		{
			m_nSrcY =0; 
		}
		break;
	case SB_PAGEDOWN:
		m_nSrcY += 50;
		if ( m_nSrcY > m_rcPicClient.Height() )
		{
			m_nSrcY = m_rcPicClient.Height();
		}
		break;
	}
	static int nLast = 0;
	m_rcSelect.m_rect.OffsetRect( 0, nLast-m_nSrcY);
	nLast = m_nSrcY;

	m_barV.SetScrollPos(m_nSrcY);
	m_bErase = true;
	InvalidateRect( &m_rcPicClient );

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CPicEditorDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	switch (nSBCode)
	{
	case SB_TOP:
		m_nSrcX = 0;
		break;
	case SB_BOTTOM:
		m_nSrcX = INT_MAX;
		break;
	case SB_THUMBTRACK:
		m_nSrcX = nPos;
		break;
	case SB_PAGELEFT:
		m_nSrcX -= 50;
		if ( m_nSrcX < 0 )
		{
			m_nSrcX =0; 
		}
		break;
	case SB_PAGERIGHT:
		m_nSrcX += 50;
		if ( m_nSrcX > m_rcPicClient.Width() )
		{
			m_nSrcX = m_rcPicClient.Width();
		}
		break;
	}
	static int nLast = 0;
	m_rcSelect.m_rect.OffsetRect( nLast-m_nSrcX, 0 );
	nLast = m_nSrcX;

	m_barH.SetScrollPos( m_nSrcX );
	m_bErase = true;
	InvalidateRect( &m_rcPicClient );

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL CPicEditorDlg::OnEraseBkgnd(CDC* pDC)
{
	if ( m_bErase )
	{
		return FALSE;
	}
	else
	{
		return CDialog::OnEraseBkgnd(pDC);
	}
}

void CPicEditorDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此添加消息处理程序代码
	if ( m_bInit )
	{
		RefeashUI( cx, cy );
	}
}


void CPicEditorDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此添加消息处理程序代码
	m_bInit = false;
}

void CPicEditorDlg::RefeashUI( int nWidth, int nHeight )
{
	CRect myRect,rcOk,rcCancel;

	::GetWindowRect( m_hWnd, &myRect);
	::GetWindowRect( GetDlgItem(IDC_STATIC_PIC)->m_hWnd, &m_rcPicClient );
	::GetWindowRect( GetDlgItem(IDOK)->m_hWnd, &rcOk );
	::GetWindowRect( GetDlgItem(IDCANCEL)->m_hWnd, &rcCancel );

	int nBW = rcOk.Width();
	int nBH = rcOk.Height();
	rcOk.left = myRect.right - BUTTON_OK_X;
	rcOk.right = rcOk.left + nBW;
	rcOk.top = myRect.bottom - BUTTON_OK_Y;
	rcOk.bottom = rcOk.top + nBH;
	ScreenToClient( &rcOk );
	GetDlgItem(IDOK)->MoveWindow( rcOk.left, rcOk.top,
								rcOk.Width(), rcOk.Height() );

	rcCancel.left = myRect.right - BUTTON_CANCEL_X;
	rcCancel.right = rcCancel.left + nBW;
	rcCancel.top = myRect.bottom - BUTTON_CANCEL_Y;
	rcCancel.bottom = rcCancel.top + nBH;
	ScreenToClient( &rcCancel );
	GetDlgItem(IDCANCEL)->MoveWindow( rcCancel.left, rcCancel.top,
									rcCancel.Width(), rcCancel.Height() );

	m_rcPicClient.right = m_rcPicClient.left + (nWidth - (m_rcPicClient.left-myRect.left) - PIC_RIGHT_BOARD );
	m_rcPicClient.bottom = m_rcPicClient.top + (nHeight - (m_rcPicClient.top-myRect.top) - PIC_BOTTOM_BOARD );
	ScreenToClient( &m_rcPicClient );
	GetDlgItem(IDC_STATIC_PIC)->MoveWindow( m_rcPicClient.left, m_rcPicClient.top,
											m_rcPicClient.Width(), m_rcPicClient.Height() );


	m_nOffsetX = m_rcPicClient.left;
	m_nOffsetY = m_rcPicClient.top;

	m_barV.MoveWindow( m_nOffsetX+m_rcPicClient.Width(),
						m_nOffsetY,
						18,
						m_rcPicClient.Height() );
	m_barH.MoveWindow( m_nOffsetX,
						m_nOffsetY+ m_rcPicClient.Height(),
						m_rcPicClient.Width(),
						18);

	SCROLLINFO	horz, vert;

	horz.cbSize = sizeof(SCROLLINFO);
	horz.fMask = SIF_ALL;
	horz.nMin = 0;
	horz.nMax = m_Tga.GetWidth()-m_rcPicClient.Width();
	horz.nPage= 0;
	horz.nPos = 0;
	horz.nTrackPos=0;
	if( m_Tga.GetWidth() <= m_rcPicClient.Width() )
	{
//		if( ( m_rcPicClient.Width() - m_Tga.GetWidth() ) ==0 )
			m_nOffsetX = m_rcPicClient.left;
//		else
//			m_nOffsetX = m_rcPicClient.left + ((m_rcPicClient.Width()-m_Tga.GetWidth())/2);
		m_barV.MoveWindow(m_nOffsetX+m_Tga.GetWidth(),m_nOffsetY,18,m_rcPicClient.Height());
		m_barH.ShowWindow(false);
	}
	else
	{
		m_barH.ShowWindow(true);
	}
	m_barH.SetScrollInfo(&horz);
	vert.cbSize = sizeof(SCROLLINFO);
	vert.fMask = SIF_ALL;
	vert.nMin = 0;
	vert.nMax = m_Tga.GetHeight()-m_rcPicClient.Height();
	vert.nPage = 0;
	vert.nTrackPos=0;
	if( m_Tga.GetHeight() <= m_rcPicClient.Height() )
	{
//		if( (m_rcPicClient.Height() - m_Tga.GetHeight() ) ==0 )
			m_nOffsetY = m_rcPicClient.top;
//		else
//			m_nOffsetY = m_rcPicClient.top + ((m_rcPicClient.Height() - m_Tga.GetHeight())/2);
		m_barH.MoveWindow( m_nOffsetX,
							m_nOffsetY + m_Tga.GetHeight(),
							m_rcPicClient.Width(),
							18 );
		m_barV.ShowWindow( false );
	}
	else
	{
		m_barV.ShowWindow( true );
	}
	m_barV.SetScrollInfo( &vert );

	Invalidate();
}



BOOL CPicEditorDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ( pWnd == this )
	{
		if ( m_rcSelect.SetCursor( GetDlgItem(IDC_STATIC_PIC), nHitTest) )
		{
			return TRUE;
		}
	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CPicEditorDlg::LButtonDownRect( CPoint point )
{
	CRect rectSave;
	int nW,nH;
	CRect rcClient;
	m_rcSelect.GetTrueRect(rectSave);
	GetDlgItem(IDC_STATIC_PIC)->GetWindowRect(&rcClient);
	ScreenToClient( &rcClient );
	nW = rectSave.Width();
	nH = rectSave.Height();
	rectSave.left += rcClient.left;
	rectSave.top += rcClient.top;
	rectSave.right = rectSave.left + nW;
	rectSave.bottom = rectSave.top + nH;
	point.x -= rcClient.left;
	point.y -= rcClient.top;
	if ( m_rcSelect.Track(GetDlgItem(IDC_STATIC_PIC), point ) )
	{
		CRect	rc(0,0,m_Tga.GetWidth(),m_Tga.GetHeight());
		rc -= CPoint(m_nSrcX,m_nSrcY);
		RectClip( &m_rcSelect.m_rect, &rc, SELECT_MIN_SIZE );

		InvalidateRect( rectSave );

		UpdateRect(false);
	}
}


void CPicEditorDlg::RectClip( CRect* pSrc, CRect* pDst, int nMinSize)
{
	assert( pSrc );
	assert( pDst );

	// Left
	if ( pSrc->left < pDst->left )
	{
		pSrc->left = pDst->left;
		if( pSrc->Width() < nMinSize )
		{
			pSrc->right = pDst->left+nMinSize;
		}
	}
	// Right
	if ( pSrc->right > pDst->right )
	{
		pSrc->right = pDst->right;
		if ( pSrc->Width() < nMinSize )
		{
			pSrc->left = pDst->right-nMinSize;
		}
	}
	// Top
	if ( pSrc->top < pDst->top )
	{
		pSrc->top = pDst->top;
		if ( pSrc->Height() < nMinSize )
		{
			pSrc->bottom = pDst->top+nMinSize;
		}
	}
	// Bottom
	if ( pSrc->bottom > pDst->bottom )
	{
		pSrc->bottom = pDst->bottom;
		if ( pSrc->Height() < nMinSize )
		{
			pSrc->top = pDst->bottom-nMinSize;
		}
	}
}

void CPicEditorDlg::OnBnClickedOk()
{
	OnOK();
}

void CPicEditorDlg::OnBnClickedCancel()
{
	m_nSrcX = m_nLastSrcX;
	m_nSrcY = m_nLastSrcY;
	m_rcPicClient = m_rcLastPicClient;
	m_nOffsetX = m_nLastOffsetX;
	m_nOffsetY = m_nLastOffsetY;
	m_rcSelect = m_rcLastSelect;
	m_strCurSelFileName = m_strLastCurSelFileName;

	OnCancel();
}

void CPicEditorDlg::UpdateRect( bool bToRect )
{
	if ( bToRect == true )
	{
		if ( m_nSelectionLeft-m_nSrcX < 0 )
		{
			m_nSelectionLeft = m_nSrcX;
		}
		if ( m_nSelectionTop-m_nSrcY < 0  )
		{
			m_nSelectionTop = m_nSrcY;
		}
		if ( m_nSelectionRight-m_nSrcX > m_Tga.GetWidth() )
		{
			m_nSelectionRight = m_Tga.GetWidth() + m_nSrcX;
		}
		if ( m_nSelectionBottom-m_nSrcY > m_Tga.GetHeight() )
		{
			m_nSelectionBottom = m_Tga.GetHeight() + m_nSrcY;
		}

		m_rcSelect.m_rect.left = m_nSelectionLeft-m_nSrcX;
		m_rcSelect.m_rect.top = m_nSelectionTop-m_nSrcY;
		m_rcSelect.m_rect.right = m_nSelectionRight-m_nSrcX;
		m_rcSelect.m_rect.bottom = m_nSelectionBottom-m_nSrcY;

		Invalidate();
	}
	else
	{
		m_nSelectionLeft = m_rcSelect.m_rect.left+m_nSrcX;
		m_nSelectionTop = m_rcSelect.m_rect.top+m_nSrcY;
		m_nSelectionRight = m_rcSelect.m_rect.right+m_nSrcX;
		m_nSelectionBottom = m_rcSelect.m_rect.bottom+m_nSrcY;
	}
	UpdateData(FALSE);
}

void CPicEditorDlg::ShowPic( const char* pstrName )
{
	CClientDC	dc(this);
	m_dcMem.DeleteDC();
	m_dcMem.CreateCompatibleDC( &dc );
	m_Tga.LoadTGAFile( pstrName );
	LoadPic( m_Tga.GetBitmap() );

	UpdateRect(false);
}


void CPicEditorDlg::OnCbnSelchangeComboFileName()
{
	// TODO: 在此添加控件通知处理程序代码
	int nCurSel = m_comboFileName.GetCurSel();
	m_comboFileName.GetLBText( nCurSel, m_strCurSelFileName );
	if ( m_strCurSelFileName.IsEmpty() )
	{
		m_dcMem.DeleteDC();
		Invalidate();
	}
	else
	{
		ShowPic( m_strCurSelFileName.GetBuffer() );
	}
}

void CPicEditorDlg::SetCurSelPicName( const char* pstrName )
{
	m_strCurSelFileName = pstrName;
	if ( m_bInit == true )
	{
		ShowPic( pstrName );
	}
}

RECT CPicEditorDlg::GetFrameRect()
{
	RECT	rc;
	rc.left = m_rcSelect.m_rect.left + m_nSrcX;
	rc.top = m_rcSelect.m_rect.top + m_nSrcY;
	rc.right = m_rcSelect.m_rect.right + m_nSrcX;
	rc.bottom = m_rcSelect.m_rect.bottom + m_nSrcY;
	return rc;
}

RECT CPicEditorDlg::GetClientRect()
{
	RECT	rc;
	rc.left = m_rcSelect.m_rect.left + m_nSrcX;
	rc.top = m_rcSelect.m_rect.top + m_nSrcY;
	rc.right = m_rcSelect.m_rect.right + m_nSrcX;
	rc.bottom = m_rcSelect.m_rect.bottom + m_nSrcY;

	rc.left += m_nMarginsLeft;
	rc.top += m_nMarginsTop;
	rc.right -= m_nMarginsRight;
	rc.bottom -= m_nMarginsBottom;

	return rc;
}


void CPicEditorDlg::SetPicStruct( const S_BaseData::S_Pic* pstPic )
{
	SetCurSelPicName( pstPic->m_szPicName );
	SetFrameRect( &pstPic->m_rcFrame );
	SetClientRect( &pstPic->m_rcClient );
}

void CPicEditorDlg::SetFrameRect( const RECT* prc )
{
	assert( prc );
	m_rcSelect.m_rect = *prc;
	m_rcSelect.m_rect.left -= m_nSrcX;
	m_rcSelect.m_rect.top -= m_nSrcY;
	m_rcSelect.m_rect.right -= m_nSrcX;
	m_rcSelect.m_rect.bottom -= m_nSrcY;

	m_nSelectionLeft = m_rcSelect.m_rect.left;
	m_nSelectionTop = m_rcSelect.m_rect.top;
	m_nSelectionRight = m_rcSelect.m_rect.right;
	m_nSelectionBottom = m_rcSelect.m_rect.bottom;

	if ( m_bInit )
	{
		UpdateData(FALSE);
	}
}

void CPicEditorDlg::SetClientRect( const RECT* prc )
{
	assert( prc );
	m_nMarginsLeft = prc->left - m_rcSelect.m_rect.left;
	m_nMarginsTop = prc->top - m_rcSelect.m_rect.top;
	m_nMarginsRight = m_rcSelect.m_rect.right - prc->right;
	m_nMarginsBottom = m_rcSelect.m_rect.bottom - prc->bottom;

	if ( m_bInit )
	{
		UpdateData(FALSE);
	}
}

void CPicEditorDlg::FindPic( const char* szFilePath, const char* szPath )
{
	CFileFind finder;
	BOOL bWorking = finder.FindFile(szFilePath);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots() || finder.IsDirectory())
			continue;
		CString szFileName;
		szFileName.Format( "%s\\%s", szPath, finder.GetFileName()  );
		theUIObjectDlg.AddPictuer( szFileName );
	}
	finder.Close();

	m_comboFileName.ResetContent();
	m_comboFileName.AddString("");
	for( UINT n=0; n<theUIObjectDlg.GetPictureCount(); n++ )
	{
		m_comboFileName.AddString( theUIObjectDlg.GetPicture(n) );
	}
	m_comboFileName.SelectString(0, m_strCurSelFileName );
}


