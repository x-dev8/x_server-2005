// TreeCtrlBT.cpp : implementation file
//

#include "stdafx.h"
#include "MyTreeCtrl.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlBT

MyTreeCtrl::MyTreeCtrl()
{
	m_bEnableRowLine  = true;
	m_bEnableRootBk   = true;
	m_nImageHeight    = 0;
	m_nImageWidth     = 0;
	m_nCellWidth	  = 4;
	m_clrTextNormal   = RGB(0,0,0);
	m_clrTextSelect	  = RGB( 0xff, 0xff, 0xff );
	m_clrRoot_from    = RGB( 0x80, 0xa0, 0xff );
	m_clrRoot_to      = RGB( 0x80, 0xa0, 0xff );

	m_hItemSelect     = NULL;
	m_hItemMouseMove  = NULL;
	m_pCurDrawItemMsg = NULL;

	m_ptOldMouse.x	  = -1;
	m_ptOldMouse.y    = -1;

	m_FontRoots.CreateFont(
		12,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_BOLD,                   // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,			   // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		PROOF_QUALITY,             // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("宋体") );              // lpszFacename

	m_FontChild.CreateFont(
		12,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                   // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,			   // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		PROOF_QUALITY,             // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("宋体") );              // lpszFacename
}

MyTreeCtrl::~MyTreeCtrl()
{
	RELEASE_GDI_RESOURCE(m_bmpBackgroud);
	RELEASE_GDI_RESOURCE(m_FontRoots);
	RELEASE_GDI_RESOURCE(m_FontChild);

	if ( m_ImageList.GetSafeHandle() )		m_ImageList.DeleteImageList();

	ITEMMSG_MAP::iterator item = m_itmemsg_map.begin();
	for ( ; item != m_itmemsg_map.end(); item++)
	{
		delete item->second;
	}
}

BEGIN_MESSAGE_MAP(MyTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CTreeCtrlBT)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlBT message handlers

void MyTreeCtrl::PreSubclassWindow() 
{
	SetItemHeight(25);
	m_nItemHeight = 25;	//保存单元项目高度

	CTreeCtrl::PreSubclassWindow();
}

void MyTreeCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CTreeCtrl::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
	Calculate();
}

void MyTreeCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	//CTreeCtrl::OnPaint();
	Calculate();

	//CDC *pDC = GetDC();

	CBitmap bitmap;	
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, m_rect.Width(), m_rect.Height());
	CBitmap *pOldBitmap = memDC.SelectObject(&bitmap);

	DrawBackgroudBitmap(&memDC);
	DrawItem(&memDC);

	dc.BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
}

void MyTreeCtrl::Calculate()
{
	GetClientRect(&m_rect);
	SCROLLINFO scroll_info;
	// Determine window portal to draw into taking into account
	// scrolling position
	if ( GetScrollInfo( SB_HORZ, &scroll_info, SIF_POS | SIF_RANGE ) )
	{
		m_h_offset = -scroll_info.nPos;
		m_h_size = max( scroll_info.nMax+1, m_rect.Width());
	}
	else
	{
		m_h_offset = m_rect.left;
		m_h_size = m_rect.Width();
	}
	if ( GetScrollInfo( SB_VERT, &scroll_info, SIF_POS | SIF_RANGE ) )
	{
		if ( scroll_info.nMin == 0 && scroll_info.nMax == 100) 
			scroll_info.nMax = 0;
		m_v_offset = -scroll_info.nPos * GetItemHeight();
		m_v_size = max( (scroll_info.nMax+2)*((int)GetItemHeight()+1), m_rect.Height() );
	}
	else
	{
		m_v_offset = m_rect.top;
		m_v_size = m_rect.Height();
	}
}

ITEM_MSG* MyTreeCtrl::GetItemMsg(HTREEITEM hItem)
{
	if ( !hItem )
	{
		return NULL;
	}

	ITEM_MSG* pItemMsg = NULL;

	ITEMMSG_MAP::iterator item = m_itmemsg_map.find(hItem);
	if ( item != m_itmemsg_map.end() )
	{
		pItemMsg = item->second;
	}

	return pItemMsg;
}

void MyTreeCtrl::GradientFillRect( CDC *pDC, CRect &rect, COLORREF col_from, COLORREF col_to, bool vert_grad )
{
	TRIVERTEX        vert[2];
	GRADIENT_RECT    mesh;
	
	vert[0].x      = rect.left;
	vert[0].y      = rect.top;
	vert[0].Alpha  = 0x0000;
	vert[0].Blue   = GetBValue(col_from) << 8;
	vert[0].Green  = GetGValue(col_from) << 8;
	vert[0].Red    = GetRValue(col_from) << 8;
	
	vert[1].x      = rect.right;
	vert[1].y      = rect.bottom; 
	vert[1].Alpha  = 0x0000;
	vert[1].Blue   = GetBValue(col_to) << 8;
	vert[1].Green  = GetGValue(col_to) << 8;
	vert[1].Red    = GetRValue(col_to) << 8;
	
	mesh.UpperLeft  = 0;
	mesh.LowerRight = 1;
#if _MSC_VER >= 1300  // only VS7 and above has GradientFill as a pDC member
	pDC->GradientFill( vert, 2, &mesh, 1, vert_grad ? GRADIENT_FILL_RECT_V : 
	GRADIENT_FILL_RECT_H );
#else
	GradientFill( pDC->m_hDC, vert, 2, &mesh, 1, vert_grad ? GRADIENT_FILL_RECT_V : 
	GRADIENT_FILL_RECT_H );
#endif	
}

void MyTreeCtrl::DrawBackgroudBitmap(CDC* pDc)
{
	if ( m_bmpBackgroud.GetSafeHandle() )
	{
		BITMAP bitmap;
		m_bmpBackgroud.GetBitmap(&bitmap);
		CDC dctmp;
		
		dctmp.CreateCompatibleDC(NULL);
		CBitmap* pOldBitmap = dctmp.SelectObject( &m_bmpBackgroud ); 
		
		pDc->StretchBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(), &dctmp, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY );

		dctmp.SelectObject(pOldBitmap);
	}
	else
	{
		pDc->FillSolidRect( m_rect, pDc->GetBkColor() ); 
	}
}

void MyTreeCtrl::DrawItem( CDC *pDC )
{
	// draw items
	HTREEITEM show_item,parent; //当前项句柄，以及它的父窗口句柄
	CRect rc_item;				//项的区域
	DWORD tree_style;			//树的类型
	int state;					//某一项的状态
	bool selected;				//True:表示是需要高亮	
	bool has_children;			//True:表示是不可以展开或者收缩
	
	show_item = GetFirstVisibleItem();//获取第一个可见项的句柄
	if ( show_item == NULL )
		return;
	
	tree_style = ::GetWindowLong( m_hWnd, GWL_STYLE ); //获取TREE的类型
	
	do
	{
		state = GetItemState( show_item, TVIF_STATE );//获取某一项的状态
		parent = GetParentItem( show_item );		  //获取某一项的父窗口句柄
		
		has_children = ItemHasChildren( show_item ) || parent == NULL;
		
		selected = (state & TVIS_SELECTED) && ((this == GetFocus()) || 
			(tree_style & TVS_SHOWSELALWAYS));
		
		if ( GetItemRect( show_item, rc_item, TRUE ) )//获取某一项的矩形区域
		{
			CRect rcclient;
			GetClientRect(rcclient);
			if (rc_item.top >= rcclient.bottom)
			{
				break;	//不可见的时候,就不需要再绘制
			}
			
			m_pCurDrawItemMsg = GetItemMsg(show_item);

			CRect rect;
			rect.top = rc_item.top;
			rect.bottom = rc_item.bottom-1;
			rect.right = m_h_size + m_h_offset;
			rect.left = m_h_offset;

			//绘制横线
			DrawRowLine(CPoint(rect.left,rect.bottom), CPoint(rect.right,rect.bottom), pDC);
						
			if ( has_children  )
			{	
				//绘制根节点背景
				if ( m_bEnableRootBk )
				{
                    Color_Font cf;	
                    if (m_mapColorFont.Lookup(show_item, cf))
                    {
                        if (cf.leftcolor != (COLORREF) -1)
                            GradientFillRect( pDC, rect, cf.rightcolor, cf.leftcolor, FALSE );
                    }
                    else
                    {
//                         if ( m_hItemMouseMove == show_item )
//                             GradientFillRect( pDC, rect, RGB(238,238,238), RGB(238,238,238), FALSE );
//                         else
                            GradientFillRect( pDC, rect, m_clrRoot_from, RGB(196,220,247), FALSE );
                    }
					
				}
				else if ( m_hItemMouseMove == show_item ) //热跟踪
				{
					GradientFillRect( pDC, rect, RGB(238,238,238), RGB(238,238,238), FALSE );
				}

				//绘制展开收缩
				DrawExpand(rc_item,state,pDC);
					
				//绘制项位图
				DrawItemBitmap(rc_item,show_item,pDC);
			}
			else
			{
				if ( selected )	//选中时候的子项背景
				{
					GradientFillRect( pDC, rect, RGB(11,111,222), RGB(11,111,222), FALSE );
				}
				else	//热跟踪
				{
					Color_Font cf;	
					if (m_mapColorFont.Lookup(show_item, cf))
					{
						if (cf.leftcolor != (COLORREF) -1)
						{
							GradientFillRect( pDC, rect, cf.rightcolor, cf.leftcolor, FALSE );
						}						
					}
					else
					{
						if ( m_hItemMouseMove == show_item )
						{
							GradientFillRect( pDC, rect, RGB(238,238,238), RGB(238,238,238), FALSE );
						}						
					}
				}

					
				//绘制项位图
				DrawItemBitmap(rc_item,show_item,pDC);	
			}
			
			//绘制文本
			DrawItemText(rc_item,show_item,selected,pDC);
		}
		
	} while ( (show_item = GetNextVisibleItem( show_item )) != NULL );
}

void MyTreeCtrl::DrawRowLine(CPoint ptBegin,CPoint ptEnd,CDC *pDc /* = NULL */)
{
	if ( !IsEnableRowLine() )
	{
		return;
	}
	
	if ( NULL == pDc)
	{
		CClientDC dc(this);
		pDc = &dc;
	}
	
	CPen pen(PS_SOLID, 1, RGB(235,235,235) );//RGB(235,235,235)
	CPen *pOldPen = pDc->SelectObject(&pen);
	pDc->MoveTo(ptBegin);
	pDc->LineTo(ptEnd);
	pDc->SelectObject(pOldPen);
	pen.DeleteObject();
}

void MyTreeCtrl::DrawExpand(CRect rect, int state, CDC *pDc /* = NULL */)
{
	if ( m_ImageList.m_hImageList == NULL || !m_ImageList.GetImageCount())
	{
		return;
	}
	
	if ( NULL == pDc)
	{
		CClientDC dc(this);
		pDc = &dc;
	}
	
	int nImage = 0;
	if ( state & TVIS_EXPANDED )	//展开
	{
		nImage = 1;
	}
	else	//收缩
	{
		nImage = 0;
	}
	
	CPoint point;
	point.x = rect.left - m_nImageWidth-m_nCellWidth;
	point.y = rect.top+(rect.Height()-m_nImageHeight)/2;
	
	m_ImageList.Draw(pDc,nImage, point, ILD_TRANSPARENT);
}

void MyTreeCtrl::DrawItemBitmap(CRect rect, HTREEITEM hItem, CDC *pDc /* = NULL */)
{
	if ( NULL == pDc)
	{
		CClientDC dc(this);
		pDc = &dc;
	}

	if ( m_pCurDrawItemMsg && m_pCurDrawItemMsg->ItemBitmap.GetSafeHandle() )
	{
		BITMAP bitmap;
		m_pCurDrawItemMsg->ItemBitmap.GetBitmap(&bitmap);
		
		CDC tmpdc;
		tmpdc.CreateCompatibleDC(pDc);		
		CBitmap *pOldBitmap = tmpdc.SelectObject(&m_pCurDrawItemMsg->ItemBitmap);
		
		int nXOriginDest = rect.left;									// 目标X偏移
		int nYOriginDest = rect.top+(rect.Height()-bitmap.bmHeight)/2;	// 目标Y偏移
		int nWidthDest	 = bitmap.bmWidth;								// 目标宽度
		int hHeightDest  = bitmap.bmHeight;								// 目标高度
		::TransparentBlt(pDc->m_hDC,nXOriginDest,nYOriginDest,nWidthDest,hHeightDest,
			tmpdc.m_hDC,0,0,bitmap.bmWidth,bitmap.bmHeight,RGB(255,255,255));
		tmpdc.SelectObject(pOldBitmap);
		
		tmpdc.DeleteDC();
	}
}

void MyTreeCtrl::DrawItemText(CRect rect, HTREEITEM hItem, bool bselected,CDC *pDc /* = NULL */)
{
	if ( NULL == pDc)
	{
		CClientDC dc(this);
		pDc = &dc;
	}

	if ( m_pCurDrawItemMsg&& m_pCurDrawItemMsg->ItemBitmap.GetSafeHandle() )
	{
		BITMAP bitmap;
		m_pCurDrawItemMsg->ItemBitmap.GetBitmap(&bitmap);
		
		int nwidth = bitmap.bmWidth+m_nCellWidth;
		rect.left += nwidth;
		rect.right+= nwidth;
	}
	
	CString strText = GetItemText( hItem );
	
	//这个方法太别扭.因为发现DrawText DT_VCENTER在vc6下无效
	CSize sz = pDc->GetTextExtent(strText);
	rect.DeflateRect( 0,1,0,1 );
	rect.top += (rect.Height()-sz.cy)/2;
	rect.right= m_rect.right;
	
	//设置字体
	CFont* pOldFont = NULL;
	HTREEITEM hParentItem = GetParentItem(hItem);
	if ( hParentItem )
	{
		pOldFont = pDc->SelectObject(&m_FontChild);
	}
	else
	{
		pOldFont = pDc->SelectObject(&m_FontRoots);
	}
	
	pDc->SetBkMode(TRANSPARENT);
	if ( bselected )
	{
		if ( IsEnableRootBk() )
		{
			pDc->SetTextColor( m_clrTextSelect );
		}
	}
	else
	{		
		pDc->SetTextColor( m_clrTextNormal );
	}

	pDc->DrawText(strText, rect, DT_LEFT|DT_TOP);
	
	pDc->SelectObject(pOldFont);
	pOldFont = NULL;
}


void MyTreeCtrl::DrawItemText_(CRect rect, HTREEITEM hItem, COLORREF bgcolor, CDC *pDc/* = NULL*/)
{
	if ( NULL == pDc)
	{
		CClientDC dc(this);
		pDc = &dc;
	}

	if ( m_pCurDrawItemMsg&& m_pCurDrawItemMsg->ItemBitmap.GetSafeHandle() )
	{
		BITMAP bitmap;
		m_pCurDrawItemMsg->ItemBitmap.GetBitmap(&bitmap);

		int nwidth = bitmap.bmWidth+m_nCellWidth;
		rect.left += nwidth;
		rect.right+= nwidth;
	}

	CString strText = GetItemText( hItem );

	//这个方法太别扭.因为发现DrawText DT_VCENTER在vc6下无效
	CSize sz = pDc->GetTextExtent(strText);
	rect.DeflateRect( 0,1,0,1 );
	rect.top += (rect.Height()-sz.cy)/2;
	rect.right= m_rect.right;

	//设置字体
	CFont* pOldFont = NULL;
	HTREEITEM hParentItem = GetParentItem(hItem);		
	pOldFont = pDc->SelectObject(&m_FontRoots);
	pDc->SetBkMode(TRANSPARENT);	
	pDc->SetTextColor( m_clrTextNormal );
	
	pDc->SetBkColor(bgcolor);

	pDc->DrawText(strText, rect, DT_LEFT|DT_TOP);

	pDc->SelectObject(pOldFont);
	pOldFont = NULL;
}

void MyTreeCtrl::EnableRowLine(BOOL bEnable /* = TRUE  */)
{
	m_bEnableRowLine = bEnable;
}

BOOL MyTreeCtrl::IsEnableRowLine()
{
	return m_bEnableRowLine;
}

void MyTreeCtrl::EnableRootBk(BOOL bEnable /* = TRUE  */)
{
	m_bEnableRootBk = bEnable;
}

BOOL MyTreeCtrl::IsEnableRootBk()
{
	return m_bEnableRootBk;
}

BOOL MyTreeCtrl::SetBackgroudBitmap(UINT nID )
{
	return m_bmpBackgroud.LoadBitmap(nID);
}

BOOL MyTreeCtrl::SetBackgroudBitmap(LPCTSTR lpszRecourceName)
{
	return m_bmpBackgroud.LoadBitmap(lpszRecourceName);
}

void MyTreeCtrl::SetItemBitmap(HTREEITEM hItem,UINT nIdBitmap)
{
	if ( !hItem )
	{
		return;
	}
	ITEM_MSG* pItemMsg = GetItemMsg(hItem);	
	if ( !pItemMsg )
	{
		return;
	}

	if ( pItemMsg->ItemBitmap.GetSafeHandle() )
	{
		pItemMsg->ItemBitmap.DeleteObject();
	}
	
	if ( 0 != nIdBitmap )
	{
		pItemMsg->ItemBitmap.LoadBitmap(nIdBitmap);
	}

}

void MyTreeCtrl::SetItemBitmap(HTREEITEM hItem, LPCTSTR lpszBitmap)
{
	if ( !hItem )
	{
		return;
	}
	ITEM_MSG* pItemMsg = GetItemMsg(hItem);	
	if ( !pItemMsg )
	{
		return;
	}
	
	if ( pItemMsg->ItemBitmap.GetSafeHandle() )
	{
		pItemMsg->ItemBitmap.DeleteObject();
	}
	
	CFileFind fileFind;
	if ( fileFind.FindFile(lpszBitmap) )
	{
		pItemMsg->ItemBitmap.LoadBitmap(lpszBitmap);
	}
}


/************************************************************************/

/* 函数功能: 设置展开收缩的图表

  /* 函数参数: 
		UINT	  nIdExpand			展开时候的图标,比如 " - "
		UINT      nIdCollapse       收缩时候的图标,比如 " + "
		COLORREF  crTransparent		位图透明色
		
		  /* 函数说明:
		  两个位图的透明色必须相同,大小必须相同
		  
/************************************************************************/
void MyTreeCtrl::SetExpandBitmap(UINT nIdExpand, UINT nIdCollapse, COLORREF crTransparent /* = RGB */)
{
	CBitmap bmpExpand,bmpCollapse;
	bmpExpand.LoadBitmap(nIdExpand);
	bmpCollapse.LoadBitmap(nIdCollapse);
	if ( !bmpExpand.GetSafeHandle() || !bmpCollapse.GetSafeHandle() )
	{
		return;
	}
	
	//保存位图高度//宽度,在绘制的时候居中
	BITMAP	bitmapExpand,bitmapCollapse;
	bmpExpand.GetBitmap(&bitmapExpand);
	bmpCollapse.GetBitmap(&bitmapCollapse);
	if ( (bitmapExpand.bmWidth  != bitmapCollapse.bmWidth) || 
		(bitmapExpand.bmHeight != bitmapCollapse.bmHeight) )
	{
		return;
	}
	m_nImageWidth  = bitmapExpand.bmWidth;
	m_nImageHeight = bitmapExpand.bmHeight;
	
	//创建CImageList
	m_ImageList.Create(11,11,ILC_COLOR24|ILC_MASK,0,2);
	m_ImageList.Add(&bmpExpand,crTransparent);
	m_ImageList.Add(&bmpCollapse,crTransparent);
	
	
	bmpExpand.DeleteObject();
	bmpCollapse.DeleteObject();
}

/************************************************************************/

/* 函数功能: 插入新的一项

  /* 函数参数: 
		HTREEITEM hParent			父节点句柄
		LPCTSTR	  lpszItem			插入项文本
		UINT      nIdBitmap			插入项位图
		COLORREF  crTransparent		位图透明色
		
		  /* 函数说明:
		  返回插入项的句柄
		  
/************************************************************************/
HTREEITEM MyTreeCtrl::InsertItemEx(HTREEITEM hParent, LPCTSTR lpszItem, UINT nIdBitmap /* = 0 */,COLORREF crTransparent /* = RGB */)
{	
	HTREEITEM hItem = InsertItem(lpszItem,0,1,hParent);
	
	
	ITEM_MSG *pItemMsg = new ITEM_MSG;
	
	pItemMsg->hItem = hItem;
	
	if ( 0 != nIdBitmap)
	{
		pItemMsg->ItemBitmap.LoadBitmap(nIdBitmap);
	}

	if (pItemMsg->ItemBitmap.GetSafeHandle())
	{	
		pItemMsg->crTransparent = crTransparent;
	}
	
	ITEMMSG_MAP::iterator item = m_itmemsg_map.find(hItem);
	if ( item == m_itmemsg_map.end() )
	{
		m_itmemsg_map[hItem] = pItemMsg;
	}
	else
	{
		item->second = pItemMsg;
	}
	
	
	return hItem;
}

HTREEITEM MyTreeCtrl::InsertItemEx(HTREEITEM hParent, LPCTSTR lpszItem, LPCTSTR lpszBitmap,COLORREF crTransparent /* = RGB */)
{
	HTREEITEM hItem = InsertItem(lpszItem,0,1,hParent);
	
	CFileFind fileFind;
	if ( fileFind.FindFile(lpszBitmap) )
	{
		ITEM_MSG *pItemMsg = new ITEM_MSG;
		
		pItemMsg->hItem = hItem;
		
		pItemMsg->ItemBitmap.LoadBitmap(lpszBitmap);
		if (pItemMsg->ItemBitmap.GetSafeHandle())
		{	
			pItemMsg->crTransparent = crTransparent;
		}
		
		ITEMMSG_MAP::iterator item = m_itmemsg_map.find(hItem);
		if ( item == m_itmemsg_map.end() )
		{
			m_itmemsg_map[hItem] = pItemMsg;
		}
		else
		{
			item->second = pItemMsg;
		}
	}
	
	fileFind.Close();
	
	return hItem;	
}

/************************************************************************/

/* 函数功能: 获得鼠标当前选中的项，一般响应鼠标消息时 使用

  没有选中某一项时，返回NULL
	  
/************************************************************************/
HTREEITEM MyTreeCtrl::GetCursorItem()
{
	CPoint pos;
	GetCursorPos(&pos);
	ScreenToClient(&pos);

	UINT nFlags;
	HTREEITEM hTreeItem = HitTest(pos, &nFlags);

	if (hTreeItem == NULL)
	{
		return NULL;
	}

	Select(hTreeItem, TVGN_CARET);
	SelectItem(hTreeItem);
	
	return hTreeItem;
}

/************************************************************************/

/* 函数功能: 设置某一项是否可以编辑修改  

  bEdit = true  设置可编辑
  bEdit = false 设置不可编辑

  返回CEdit指针， 失败返回NULL
	  
/************************************************************************/
CEdit* MyTreeCtrl::SetItemCanEdit(HTREEITEM hItem, bool bEdit)
{
	if (hItem == NULL)
	{
		return NULL;
	}

	DWORD dwStyles = GetWindowLong(m_hWnd,GWL_STYLE);

	if (bEdit)	//设置可编辑
	{		
		
		dwStyles |= TVS_EDITLABELS;		
		SetWindowLong(m_hWnd, GWL_STYLE, dwStyles);
		
		return this->EditLabel(hItem);
	}
	else		//取消可编辑
	{				
		dwStyles ^= TVS_EDITLABELS;	
		SetWindowLong(m_hWnd, GWL_STYLE, dwStyles);
	}		
	
	return NULL;
}

/************************************************************************/

/* 函数功能: 展开或者收缩节点  

  hRoot == NULL 对所有节点
  hRoot != NULL 对指定节点
  bExpand 收缩 = TRUE	  
/************************************************************************/
void MyTreeCtrl::ExpandAllTreeNodes(HTREEITEM hRoot, BOOL bExpand)
{
	UINT nCode = bExpand ? TVE_EXPAND : TVE_COLLAPSE;
	
	if (hRoot == NULL)
	{
		// 可能有多个根节点
		hRoot = GetRootItem();
		while (hRoot != NULL)
		{
			ExpandAllTreeNodes(hRoot, bExpand);
			hRoot = GetNextItem(hRoot, TVGN_NEXT);
		}

		return;
	}
	
	HTREEITEM hSon = NULL;
	Expand(hRoot,nCode);  
	
	// 遍历子节点
	hSon = GetNextItem(hRoot,TVGN_CHILD);
	while (hSon != NULL)
	{	
		ExpandAllTreeNodes(hSon, bExpand);		
		hSon = GetNextItem(hSon,TVGN_NEXT);
	}
}

/************************************************************************/
/* 函数功能: 查找某一项  

  lpszRoot  指定父节点名称
  lpszNode 指定需要查找节点
/************************************************************************/
HTREEITEM MyTreeCtrl::FindNodeItem(LPCTSTR lpszRoot, LPCTSTR lpszNode)
{	
	HTREEITEM hRoot = GetRootItem();	

	if (lpszRoot[0] == 0)
	{		
		return FindNodeItemNode(hRoot, lpszNode);
	}

	hRoot = FindNodeItemNode(hRoot, lpszRoot);
	if (hRoot == NULL)
	{
		return NULL;
	}

	HTREEITEM hChild = GetNextItem(hRoot, TVGN_CHILD);		 
	return FindNodeItemNode(hChild, lpszNode);		
}

/************************************************************************/
/* 函数功能: 设置文本颜色 
/************************************************************************/
void MyTreeCtrl::SetItemBgColor(HTREEITEM hItem, COLORREF leftcolor, COLORREF rightcolor)
{
	Color_Font cf;	
	
	cf.leftcolor = leftcolor;
	cf.rightcolor = rightcolor;
	m_mapColorFont[hItem] = cf;
}

void MyTreeCtrl::ClearAllItemBgColor()
{
	m_mapColorFont.RemoveAll();
}

HTREEITEM MyTreeCtrl::FindNodeItemNode(HTREEITEM hItem, LPCTSTR lpszNode)
{			
	//先判断兄弟节点
	while (hItem != NULL)
	{
		CString strItem = GetItemText(hItem);	
		if (strItem == lpszNode)
		{
			return hItem;
		}
	
		//遍历子节点
		HTREEITEM hChild = GetNextItem(hItem, TVGN_CHILD);		
		HTREEITEM hResult = FindNodeItemNode(hChild, lpszNode);
		if (hResult != NULL)
		{
			return hResult;
		}		

		hItem = GetNextItem(hItem, TVGN_NEXT);
	}

	return NULL;
}


void MyTreeCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CTreeCtrl::OnMouseMove(nFlags, point);

	m_ptOldMouse = point;
	HTREEITEM hItem = HitTest(point);
	if ( hItem != NULL && hItem != m_hItemMouseMove )
	{
		m_hItemMouseMove = hItem;
		Invalidate(FALSE);
	}
}

