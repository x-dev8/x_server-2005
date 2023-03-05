// UIEditorView.cpp : CUIEditorView 类的实现
//

#include "stdafx.h"
#include "UIEditor.h"

#include "UIEditorDoc.h"
#include "UIEditorView.h"
#include <mmsystem.h>
#include <assert.h>
#include "UIObjectDlg.h"
#include "PropertyDlg.h"
#include "PicMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SCREEN_WIDE 1024
#define SCREEN_HEIGHT 768

#define SCREEN_LEFT 0
#define SCREEN_TOP 0

// CUIEditorView

IMPLEMENT_DYNCREATE(CUIEditorView, CView)

BEGIN_MESSAGE_MAP(CUIEditorView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CUIEditorView 构造/销毁

CUIEditorView::CUIEditorView()
{
	m_rcSelect.m_rect.SetRect( 0,0, 100, 100 );
	m_rcSelect.m_nStyle = CRectTracker::hatchedBorder | CRectTracker::resizeOutside;
	m_bErase = false;
}

CUIEditorView::~CUIEditorView()
{
}

BOOL CUIEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CView::PreCreateWindow(cs);
}

// CUIEditorView 绘制
//#include "Frame.h"
void CUIEditorView::OnDraw(CDC* pDC )
{
	CUIEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	m_bErase = false;
	
	switch( g_enState )
	{
	case State_Dialog:
	case State_Control:
		{
			DrawDialog( pDC );
			if( theApp.m_enOperateType == Type_Normal && theUIObjectDlg.m_pstCurControl )
			{
				int nX,nY;
				int nFrameLeft, nFrameTop, nFrameRight, nFrameBottom;
				GetFramePos( &nFrameLeft, &nFrameTop, &nFrameRight, &nFrameBottom );
				RECT rc = { nFrameLeft, nFrameTop, nFrameRight, nFrameBottom };
				if ( theUIObjectDlg.m_pstDialog == theUIObjectDlg.m_pstCurControl )
				{
					rc.left =  SCREEN_LEFT; 
					rc.top = SCREEN_TOP;
					rc.right = SCREEN_WIDE;
					rc.bottom = SCREEN_HEIGHT;
				}
				//RECT rc = { 0,0,theUIObjectDlg.m_pstDialog->m_nWidth,theUIObjectDlg.m_pstDialog->m_nHeight };
				theUIObjectDlg.m_pstCurControl->GetPos( &nX, &nY, &rc );
				m_rcSelect.m_rect.left = nX;
				m_rcSelect.m_rect.top = nY;
				m_rcSelect.m_rect.right = nX+theUIObjectDlg.m_pstCurControl->m_nWidth;
				m_rcSelect.m_rect.bottom = nY+theUIObjectDlg.m_pstCurControl->m_nHeight;
				m_rcSelect.Draw( pDC );

				RECT rcClient = {0, 0, 0, 0};
				GetClientRect(&rcClient);
				pDC->MoveTo(CPoint(m_rcSelect.m_rect.left, rcClient.top));
				pDC->LineTo(CPoint(m_rcSelect.m_rect.left, rcClient.bottom));
				pDC->MoveTo(CPoint(rcClient.left, m_rcSelect.m_rect.top));
				pDC->LineTo(CPoint(rcClient.right, m_rcSelect.m_rect.top));
			}
		}
		break;
	case State_Pic:
		{
			pDoc->m_GraphicsData.Draw( pDC, 0, 0 );
		}
		break;
	default:
		assert( false );
		break;
	}
	//static int nDebugCount = 0;
	//char szDebugInfo[128];
	//sprintf( szDebugInfo, "OnDraw(..): RunCounst:%d \r\n", nDebugCount++ );
	//OutputDebugString( szDebugInfo );

	pDC->MoveTo(CPoint( SCREEN_WIDE, 0));
	pDC->LineTo(CPoint( SCREEN_WIDE, SCREEN_HEIGHT));
	pDC->MoveTo(CPoint( 0, SCREEN_HEIGHT));
	pDC->LineTo(CPoint( SCREEN_WIDE, SCREEN_HEIGHT));
}

// CUIEditorView 打印

BOOL CUIEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CUIEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印前添加额外的初始化
}

void CUIEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印后添加清除过程
}


// CUIEditorView 诊断

#ifdef _DEBUG
void CUIEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CUIEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUIEditorDoc* CUIEditorView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUIEditorDoc)));
	return (CUIEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CUIEditorView 消息处理程序

void CUIEditorView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	Invalidate();
}



BOOL CUIEditorView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch( g_enState )
	{
	case State_Dialog:
	case State_Control:
		{
			/*if ( theApp.m_enOperateType == Type_Normal && pWnd == this )
			{
				if ( m_rcSelect.SetCursor( pWnd, nHitTest ) )
				{
					return TRUE;
				}
			}*/
		}
		break;
	case State_Pic:
		break;
	default:
		assert( false );
		break;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}


void CUIEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	switch( g_enState )
	{
	case State_Dialog:
	case State_Control:
		{
			OnLButtonDownDialog(point);
		}
		break;
	case State_Pic:
		break;
	default:
		assert( false );
		break;
	}

	CView::OnLButtonDown(nFlags, point);
}

void CUIEditorView::DrawDialog( CDC* pDC )
{
	//CRect	rcDialog(0,0,800,600);
	CRect	rcDialog(SCREEN_LEFT,SCREEN_TOP,SCREEN_WIDE,SCREEN_HEIGHT);

	theUIObjectDlg.m_pstDialog->Render( pDC, rcDialog );

	int nFrameLeft, nFrameTop, nFrameRight, nFrameBottom;
	GetFramePos( &nFrameLeft, &nFrameTop, &nFrameRight, &nFrameBottom );
	rcDialog.SetRect( nFrameLeft, nFrameTop, nFrameRight, nFrameBottom );
	//rcDialog.SetRect( 0, 0, theUIObjectDlg.m_pstDialog->m_nWidth, theUIObjectDlg.m_pstDialog->m_nHeight );

	for( UINT n=0; n<theUIObjectDlg.m_vtControls.size(); n++ )
	{
		CBaseControl *pControl = theUIObjectDlg.m_vtControls[n].pControl;
		assert( pControl );
		pControl->OnSize();
		pControl->Render( pDC, rcDialog );
	}
}

BOOL CUIEditorView::OnEraseBkgnd(CDC* pDC)
{
	if ( m_bErase )
	{
		return FALSE;
	}
	else
	{
		return CView::OnEraseBkgnd(pDC);
	}
}

void CUIEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	static bool bLastState = false;
	bool bIsUpdate = false;
	//CRect	rcDialog(0,0,800,600);
	CRect	rcDialog(SCREEN_LEFT,SCREEN_TOP,SCREEN_WIDE,SCREEN_HEIGHT);
	theUIObjectDlg.m_pstDialog->MouseMove( point, rcDialog );

	int nFrameLeft, nFrameTop, nFrameRight, nFrameBottom;
	GetFramePos( &nFrameLeft, &nFrameTop, &nFrameRight, &nFrameBottom );
	rcDialog.SetRect( nFrameLeft, nFrameTop, nFrameRight, nFrameBottom );
	//rcDialog.SetRect( 0, 0, theUIObjectDlg.m_pstDialog->m_nWidth, theUIObjectDlg.m_pstDialog->m_nHeight );
	for( UINT n=0; n<theUIObjectDlg.m_vtControls.size(); n++ )
	{
		CBaseControl *pControl = theUIObjectDlg.m_vtControls[n].pControl;
		assert( pControl );
		if ( pControl->MouseMove( point, rcDialog ) == true )
		{
			bIsUpdate = true;
		}
	}
	if ( bLastState != bIsUpdate )
	{
		m_bErase = true;
		Invalidate();
	}
	bLastState = bIsUpdate;

	CView::OnMouseMove( nFlags, point );
}

void CUIEditorView::OnLButtonDownDialog( CPoint point )
{
	switch( theApp.m_enOperateType )
	{
	case Type_Normal:
		{
			RECT rcLast;
			m_rcSelect.GetTrueRect( &rcLast );

			bool bIsDialogHit = false;

			if ( theUIObjectDlg.m_pstDialog == theUIObjectDlg.m_pstCurControl )
			{
				if ( m_rcSelect.HitTest( point ) == CRectTracker::hitMiddle )
				{
					bIsDialogHit = true;
				}
			}

			if ( /*bIsDialogHit == false &&*/ m_rcSelect.Track(this, point ) )
			{
				if ( theUIObjectDlg.m_pstCurControl )
				{
					int nFrameLeft, nFrameTop, nFrameRight, nFrameBottom;
					GetFramePos( &nFrameLeft, &nFrameTop, &nFrameRight, &nFrameBottom );
					RECT rc = { nFrameLeft, nFrameTop, nFrameRight, nFrameBottom };

					if ( theUIObjectDlg.m_pstDialog == theUIObjectDlg.m_pstCurControl )
					{
						rc.left =  SCREEN_LEFT; 
						rc.top = SCREEN_TOP;
						rc.right = SCREEN_WIDE;
						rc.bottom = SCREEN_HEIGHT;
					}
					//RECT rc = { 0,0,theUIObjectDlg.m_pstDialog->m_nWidth,theUIObjectDlg.m_pstDialog->m_nHeight };
					theUIObjectDlg.m_pstCurControl->SetPos( m_rcSelect.m_rect.left, m_rcSelect.m_rect.top, &rc );
					theUIObjectDlg.m_pstCurControl->m_nWidth = m_rcSelect.m_rect.Width();
					theUIObjectDlg.m_pstCurControl->m_nHeight = m_rcSelect.m_rect.Height();

					theUIObjectDlg.m_pstCurControl->OnSize();

					thePropertyDlg.Invalidate();
					if ( rcLast.right < theUIObjectDlg.m_pstDialog->m_nWidth &&
						rcLast.bottom < theUIObjectDlg.m_pstDialog->m_nHeight &&
						m_rcSelect.m_rect.right < theUIObjectDlg.m_pstDialog->m_nWidth &&
						m_rcSelect.m_rect.bottom < theUIObjectDlg.m_pstDialog->m_nHeight &&
						!theUIObjectDlg.m_pstDialog->m_strPicName.IsEmpty() )
					{
						m_bErase = true;
					}
					Invalidate();
				}
				break;
			}
			bool bFoundCntrol = false;
			CRect rc;
			//RECT rcDialog = {0,0,theUIObjectDlg.m_pstDialog->m_nWidth,theUIObjectDlg.m_pstDialog->m_nHeight};
			int nFrameLeft, nFrameTop, nFrameRight, nFrameBottom;
			GetFramePos( &nFrameLeft, &nFrameTop, &nFrameRight, &nFrameBottom );
			RECT rcDialog = { nFrameLeft, nFrameTop, nFrameRight, nFrameBottom };
			int nX,nY;
			CBaseControl *pControl;
//			for( UINT n=0; n<theUIObjectDlg.m_vtControls.size(); n++ )
			for( int n=(int)theUIObjectDlg.m_vtControls.size()-1; n>=0; n-- )
			{
				pControl = theUIObjectDlg.m_vtControls[n].pControl;
				assert( pControl );
				pControl->GetPos( &nX, &nY, &rcDialog );
				rc.SetRect( nX, nY, nX + pControl->m_nWidth, nY + pControl->m_nHeight );
				if ( rc.PtInRect( point ) )
				{
					theUIObjectDlg.m_pstCurControl = pControl;
					g_enState = State_Control;
					bFoundCntrol = true;
					break;
				}
			}
			if ( bFoundCntrol == false )
			{
				pControl = theUIObjectDlg.m_pstDialog;
				assert( pControl );
				CRect	rcClientDialog(SCREEN_LEFT,SCREEN_TOP,SCREEN_WIDE,SCREEN_HEIGHT);
				pControl->GetPos( &nX, &nY, /*&rcDialog*/&rcClientDialog );
				rc.SetRect( nX, nY, nX+pControl->m_nWidth, nY+pControl->m_nHeight );
				if ( rc.PtInRect( point ) )
				{
					theUIObjectDlg.m_pstCurControl = pControl;
					g_enState = State_Dialog;
				}
				else
				{
					theUIObjectDlg.m_pstCurControl->Release();
					theUIObjectDlg.m_pstCurControl = NULL;
					theApp.m_enOperateType = Type_Normal;
				}
			}
			if ( theUIObjectDlg.m_pstCurControl )
			{
				thePropertyDlg.Clear();
				theUIObjectDlg.m_pstCurControl->AddToPropertyDlg();
				theUIObjectDlg.ShowSelItem( theUIObjectDlg.m_pstCurControl );
			}
			if ( !theUIObjectDlg.m_pstDialog->m_strPicName )
			{
				m_bErase = true;
			}
			Invalidate();
		}
		break;
	case Type_Button:
	case Type_CheckBox:
	case Type_Edit:
	case Type_Text:
	case Type_List:
	case Type_ListImg:
	case Type_ScrollBar:
	case Type_ScrollBarEx:
	case Type_ComboBox:
	case Type_Picture:
	case Type_Progress:
	case Type_Tab:
	case Type_ListEx:
	//case Type_Tree:
		{
			if( theUIObjectDlg.AddControl( theApp.m_enOperateType, point.x, point.y ) == true )
			{
				theApp.m_enOperateType = Type_Normal;
			}
		}
		break;
	default:
		assert(false);
		break;
	}
}


void CUIEditorView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch( nChar )
	{
	case VK_DELETE:
		{
			if ( MessageBox( "确定要移除所选定的控件?", "确认", MB_YESNO ) == IDYES )
			{
				if ( theUIObjectDlg.RemoveSelControl() == false )
				{
					MessageBox( "请先选定要移除的控件", "失败", MB_OK );
				}
			}
		}
		break;
	default:
		break;
	}

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CUIEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if ( theUIObjectDlg.m_pstCurControl )
	{
		switch(nChar)
		{
		case VK_LEFT:
			{
				//RECT rc = { 0,0,theUIObjectDlg.m_pstDialog->m_nWidth,theUIObjectDlg.m_pstDialog->m_nHeight };
				int nFrameLeft, nFrameTop, nFrameRight, nFrameBottom;
				GetFramePos( &nFrameLeft, &nFrameTop, &nFrameRight, &nFrameBottom );
				RECT rc = { nFrameLeft, nFrameTop, nFrameRight, nFrameBottom };

				if ( theUIObjectDlg.m_pstDialog == theUIObjectDlg.m_pstCurControl )
				{
					rc.left =  SCREEN_LEFT; 
					rc.top = SCREEN_TOP;
					rc.right = SCREEN_WIDE;
					rc.bottom = SCREEN_HEIGHT;
				}

				m_rcSelect.m_rect.left--;
				theUIObjectDlg.m_pstCurControl->SetPos( m_rcSelect.m_rect.left, m_rcSelect.m_rect.top, &rc );
				if( !theUIObjectDlg.m_pstDialog->m_strPicName.IsEmpty() )
				{
					m_bErase = true;
				}
				thePropertyDlg.Invalidate();
				Invalidate();
			}
			break;
		case VK_RIGHT:
			{
				//RECT rc = { 0,0,theUIObjectDlg.m_pstDialog->m_nWidth,theUIObjectDlg.m_pstDialog->m_nHeight };
				int nFrameLeft, nFrameTop, nFrameRight, nFrameBottom;
				GetFramePos( &nFrameLeft, &nFrameTop, &nFrameRight, &nFrameBottom );
				RECT rc = { nFrameLeft, nFrameTop, nFrameRight, nFrameBottom };

				if ( theUIObjectDlg.m_pstDialog == theUIObjectDlg.m_pstCurControl )
				{
					rc.left =  SCREEN_LEFT; 
					rc.top = SCREEN_TOP;
					rc.right = SCREEN_WIDE;
					rc.bottom = SCREEN_HEIGHT;
				}

				m_rcSelect.m_rect.left++;
				theUIObjectDlg.m_pstCurControl->SetPos( m_rcSelect.m_rect.left, m_rcSelect.m_rect.top, &rc );
				if( !theUIObjectDlg.m_pstDialog->m_strPicName.IsEmpty() )
				{
					m_bErase = true;
				}
				thePropertyDlg.Invalidate();
				Invalidate();
			}
			break;
		case VK_UP:
			{
				//RECT rc = { 0,0,theUIObjectDlg.m_pstDialog->m_nWidth,theUIObjectDlg.m_pstDialog->m_nHeight };
				int nFrameLeft, nFrameTop, nFrameRight, nFrameBottom;
				GetFramePos( &nFrameLeft, &nFrameTop, &nFrameRight, &nFrameBottom );
				RECT rc = { nFrameLeft, nFrameTop, nFrameRight, nFrameBottom };

				if ( theUIObjectDlg.m_pstDialog == theUIObjectDlg.m_pstCurControl )
				{
					rc.left =  SCREEN_LEFT; 
					rc.top = SCREEN_TOP;
					rc.right = SCREEN_WIDE;
					rc.bottom = SCREEN_HEIGHT;
				}

				m_rcSelect.m_rect.top--;
				theUIObjectDlg.m_pstCurControl->SetPos( m_rcSelect.m_rect.left, m_rcSelect.m_rect.top, &rc );
				if( !theUIObjectDlg.m_pstDialog->m_strPicName.IsEmpty() )
				{
					m_bErase = true;
				}
				thePropertyDlg.Invalidate();
				Invalidate();
			}
			break;
		case VK_DOWN:
			{
				//RECT rc = { 0,0,theUIObjectDlg.m_pstDialog->m_nWidth,theUIObjectDlg.m_pstDialog->m_nHeight };
				int nFrameLeft, nFrameTop, nFrameRight, nFrameBottom;
				GetFramePos( &nFrameLeft, &nFrameTop, &nFrameRight, &nFrameBottom );
				RECT rc = { nFrameLeft, nFrameTop, nFrameRight, nFrameBottom };

				if ( theUIObjectDlg.m_pstDialog == theUIObjectDlg.m_pstCurControl )
				{
					rc.left =  SCREEN_LEFT; 
					rc.top = SCREEN_TOP;
					rc.right = SCREEN_WIDE;
					rc.bottom = SCREEN_HEIGHT;
				}

				m_rcSelect.m_rect.top++;
				theUIObjectDlg.m_pstCurControl->SetPos( m_rcSelect.m_rect.left, m_rcSelect.m_rect.top, &rc );
				if( !theUIObjectDlg.m_pstDialog->m_strPicName.IsEmpty() )
				{
					m_bErase = true;
				}
				thePropertyDlg.Invalidate();
				Invalidate();
			}
			break;
		default:
			break;
		}
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CUIEditorView::GetFramePos( int* pLeft, int* pTop, int* pRight, int* pBottom )
{
	assert( pLeft && pTop && pRight && pBottom );

	switch ( theUIObjectDlg.m_pstDialog->GetAlignMode( &theUIObjectDlg.m_pstDialog->m_comboAlign ) )
	{
	case AlignMode_LeftTop:
		*pLeft = theUIObjectDlg.m_pstDialog->m_nOffsetX;
		*pRight = *pLeft + theUIObjectDlg.m_pstDialog->m_nWidth;
		*pTop = theUIObjectDlg.m_pstDialog->m_nOffsetY;
		*pBottom = *pTop + theUIObjectDlg.m_pstDialog->m_nHeight;
		break;
	case AlignMode_RightTop:
		*pLeft = SCREEN_WIDE + theUIObjectDlg.m_pstDialog->m_nOffsetX;
		*pRight = *pLeft + theUIObjectDlg.m_pstDialog->m_nWidth;
		*pTop = theUIObjectDlg.m_pstDialog->m_nOffsetY;
		*pBottom = *pTop + theUIObjectDlg.m_pstDialog->m_nHeight;
		break;
	case AlignMode_LeftBottom:
		*pLeft = theUIObjectDlg.m_pstDialog->m_nOffsetX;
		*pRight = *pLeft + theUIObjectDlg.m_pstDialog->m_nWidth;
		*pTop = SCREEN_HEIGHT + theUIObjectDlg.m_pstDialog->m_nOffsetY;
		*pBottom = *pTop + theUIObjectDlg.m_pstDialog->m_nHeight;
		break;
	case AlignMode_RightBottom:
		*pLeft = SCREEN_WIDE + theUIObjectDlg.m_pstDialog->m_nOffsetX;
		*pRight = *pLeft + theUIObjectDlg.m_pstDialog->m_nWidth;
		*pTop = SCREEN_HEIGHT + theUIObjectDlg.m_pstDialog->m_nOffsetY;
		*pBottom = *pTop + theUIObjectDlg.m_pstDialog->m_nHeight;
		break;
	case AlignMode_Middle:
		*pLeft = ( SCREEN_WIDE - SCREEN_LEFT ) / 2 + theUIObjectDlg.m_pstDialog->m_nOffsetX;
		*pRight = *pLeft + theUIObjectDlg.m_pstDialog->m_nWidth;
		*pTop = ( SCREEN_HEIGHT - SCREEN_TOP ) / 2 + theUIObjectDlg.m_pstDialog->m_nOffsetY;
		*pBottom = *pTop + theUIObjectDlg.m_pstDialog->m_nHeight;
		break;
	case AlignMode_LeftMiddle:
		*pLeft = theUIObjectDlg.m_pstDialog->m_nOffsetX;
		*pRight = *pLeft + theUIObjectDlg.m_pstDialog->m_nWidth;
		*pTop = ( SCREEN_HEIGHT - SCREEN_TOP ) / 2 + theUIObjectDlg.m_pstDialog->m_nOffsetY;
		*pBottom = *pTop + theUIObjectDlg.m_pstDialog->m_nHeight;
		break;
	case AlignMode_TopMiddle:
		*pLeft = ( SCREEN_WIDE - SCREEN_LEFT ) / 2 + theUIObjectDlg.m_pstDialog->m_nOffsetX;
		*pRight = *pLeft + theUIObjectDlg.m_pstDialog->m_nWidth;
		*pTop = theUIObjectDlg.m_pstDialog->m_nOffsetY;
		*pBottom = *pTop + theUIObjectDlg.m_pstDialog->m_nHeight;
		break;
	case AlignMode_RightMiddle:
		*pLeft = SCREEN_WIDE + theUIObjectDlg.m_pstDialog->m_nOffsetX;
		*pRight = *pLeft + theUIObjectDlg.m_pstDialog->m_nWidth;
		*pTop = ( SCREEN_HEIGHT - SCREEN_TOP ) / 2 + theUIObjectDlg.m_pstDialog->m_nOffsetY;
		*pBottom = *pTop + theUIObjectDlg.m_pstDialog->m_nHeight;
		break;
	case AlignMode_BottomMiddle:
		*pLeft = ( SCREEN_WIDE - SCREEN_LEFT ) / 2 + theUIObjectDlg.m_pstDialog->m_nOffsetX;
		*pRight = *pLeft + theUIObjectDlg.m_pstDialog->m_nWidth;
		*pTop = SCREEN_HEIGHT + theUIObjectDlg.m_pstDialog->m_nOffsetY;
		*pBottom = *pTop + theUIObjectDlg.m_pstDialog->m_nHeight;
		break;
	default:
		break;
	}
}