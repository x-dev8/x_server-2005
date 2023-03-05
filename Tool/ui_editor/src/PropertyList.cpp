// PropertyList.cpp : implementation file
//

#include "stdafx.h"
#include "PropertyList.h"
#include <assert.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyList

CPropertyList::CPropertyList()
{
	m_bUpdate = false;
}

CPropertyList::~CPropertyList()
{
}


BEGIN_MESSAGE_MAP(CPropertyList, CListBox)
	//{{AFX_MSG_MAP(CPropertyList)
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(LBN_SELCHANGE, OnSelchange)
	ON_WM_LBUTTONUP()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_CBN_KILLFOCUS(IDC_PROPCMBBOX, OnKillfocusCmbBox)
	ON_CBN_SELCHANGE(IDC_PROPCMBBOX, OnSelchangeCmbBox)
	ON_EN_KILLFOCUS(IDC_PROPEDITBOX, OnKillfocusEditBox)
	ON_EN_CHANGE(IDC_PROPEDITBOX, OnChangeEditBox)
	ON_BN_CLICKED(IDC_PROPBTNCTRL, OnButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyList message handlers

BOOL CPropertyList::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CListBox::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~(LBS_OWNERDRAWVARIABLE | LBS_SORT);
	cs.style |= LBS_OWNERDRAWFIXED;

	m_bTracking = FALSE;
	m_nDivider = 0;
	m_bDivIsSet = FALSE;

	return TRUE;
}

void CPropertyList::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	lpMeasureItemStruct->itemHeight = 20; //pixels
}


void CPropertyList::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	CDC dc;
	dc.Attach(lpDIS->hDC);
	CRect rectFull = lpDIS->rcItem;
	CRect rect = rectFull;
	if (m_nDivider==0)
		m_nDivider = rect.Width() / 2;
	rect.left = m_nDivider;
	CRect rect2 = rectFull;
	rect2.right = rect.left - 1;
	UINT nIndex = lpDIS->itemID;

	if (nIndex != (UINT) -1)
	{
		//draw two rectangles, one for each row column
		dc.FillSolidRect(rect2,RGB(192,192,192));
		dc.DrawEdge(rect2,EDGE_SUNKEN,BF_BOTTOMRIGHT);
		dc.DrawEdge(rect,EDGE_SUNKEN,BF_BOTTOM);

		//get the CPropertyItem for the current row
		S_PropertyItem* pItem = (S_PropertyItem*)GetItemDataPtr(nIndex);
		if ( pItem )
		{
			//write the property name in the first rectangle
			dc.SetBkMode(TRANSPARENT);
			dc.DrawText(pItem->m_propName,CRect(rect2.left+3,rect2.top+3,
				rect2.right-3,rect2.bottom+3),
				DT_LEFT | DT_SINGLELINE);

			switch( pItem->m_nItemType )
			{
			case PIT_COLOR:
				{
					RECT	rcColor = rect;
					rcColor.right -= 25;
					rcColor.bottom -= 3;

					assert( pItem->m_pValue );

					dc.FillSolidRect(&rcColor, *(COLORREF*)pItem->m_pValue );
				}
				break;
			case PIT_COMBO:
				{
					dc.DrawText(((S_Combo*)pItem->m_pValue)->m_curValue,
								CRect(rect.left+3,rect.top+3,
								rect.right+3,rect.bottom+3),
								DT_LEFT | DT_SINGLELINE);
				}
				break;
			case PIT_BOOL:
				{
					CString	strBool = *(BOOL*)pItem->m_pValue == TRUE? "TRUT" : "FALSE";
					dc.DrawText(strBool,
								CRect(rect.left+3,rect.top+3,
								rect.right+3,rect.bottom+3),
								DT_LEFT | DT_SINGLELINE);
				}
				break;
			case PIT_DIALOG:
				{
					dc.DrawText("[DATA]",
						CRect(rect.left+3,rect.top+3,
						rect.right+3,rect.bottom+3),
						DT_LEFT | DT_SINGLELINE);
					//if ( ((CDialog*)pItem->m_pValue)->m_hWnd )
					//{
					//	CString	strName;
					//	((CDialog*)pItem->m_pValue)->GetWindowText(strName);
					//	dc.DrawText(strName,
					//		CRect(rect.left+3,rect.top+3,
					//		rect.right+3,rect.bottom+3),
					//		DT_LEFT | DT_SINGLELINE);
					//}
				}
				break;
			case PIT_NUM:
				{
					CString	strBool;
					strBool.Format("%d",*(int*)pItem->m_pValue);
					dc.DrawText(strBool,
								CRect(rect.left+3,rect.top+3,
								rect.right+3,rect.bottom+3),
								DT_LEFT | DT_SINGLELINE);
				}
				break;
			case PIT_COMMENTS:
				{
					RECT	rcColor = rect;
					rcColor.left -= 3;
					rcColor.bottom -= 2;

					if ( pItem->m_pValue )
					{
						rcColor.left = 0;
						dc.FillSolidRect(&rcColor, *(COLORREF*)pItem->m_pValue );

						dc.DrawText(pItem->m_propName,CRect(rect2.left+3,rect2.top+3,
									rect2.right-3,rect2.bottom+3),
									DT_LEFT | DT_SINGLELINE);
					}
					else
					{
						dc.FillSolidRect(&rcColor, RGB(192,192,192) );
					}
				}
				break;
			case PIT_FONT:
				{
					S_Font *pFont = (S_Font*)pItem->m_pValue;
					CString strText;
					strText.Format("%s(%d)",pFont->m_strName,pFont->m_nSize);
					COLORREF colLast = dc.SetTextColor( pFont->m_colColor );
					dc.DrawText( strText,CRect(rect.left+3,rect.top+3,
									rect.right+3,rect.bottom+3),
									DT_LEFT | DT_SINGLELINE);
					dc.SetTextColor( colLast );
				}
				break;
			case PIT_EDIT:
			case PIT_FILE:
				{
					dc.DrawText(*(CString*)pItem->m_pValue,CRect(rect.left+3,rect.top+3,
								rect.right+3,rect.bottom+3),
								DT_LEFT | DT_SINGLELINE);
				}
				break;
			default:
				{
					assert( false );
				}
				break;
			}
		}

	}
	dc.Detach();
}

int CPropertyList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_bDivIsSet = FALSE;
	m_nDivider = 0;
	m_bTracking = FALSE;

	m_hCursorSize = AfxGetApp()->LoadStandardCursor(IDC_SIZEWE);
	m_hCursorArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);

	m_SSerif8Font.CreatePointFont(80,_T("MS Sans Serif"));

	return 0;
}

void CPropertyList::OnSelchange() 
{
	CRect rect;
	CString lBoxSelText;

	//m_curSel = GetCurSel();

	GetItemRect(m_curSel,rect);
	rect.left = m_nDivider;
	S_PropertyItem* pItem = (S_PropertyItem*)GetItemDataPtr(m_curSel);
	if ( !pItem )
		return;

	if (m_btnCtrl)
		m_btnCtrl.ShowWindow(SW_HIDE);

	switch( pItem->m_nItemType )
	{
	case PIT_BOOL:
		{
			m_nLastBox = 0;
			if (m_cmbBox)
			{
				m_cmbBox.MoveWindow(rect);
			}
			else
			{	
				rect.bottom += 100;
				m_cmbBox.Create(CBS_DROPDOWNLIST | CBS_NOINTEGRALHEIGHT | WS_VISIBLE | WS_CHILD | WS_BORDER,
					rect,this,IDC_PROPCMBBOX);
				m_cmbBox.SetFont(&m_SSerif8Font);
			}

			//add the choices for this particular property
			CString cmbItems = "TRUE|FALSE|";
			lBoxSelText = *(BOOL*)pItem->m_pValue == TRUE ? "TRUE" : "FALSE";

			m_cmbBox.ResetContent();
			int i,i2;
			i=0;

			while ((i2=cmbItems.Find('|',i)) != -1)
			{
				m_cmbBox.AddString(cmbItems.Mid(i,i2-i));
				i=i2+1;
			}

			m_cmbBox.ShowWindow(SW_SHOW);
			m_cmbBox.SetFocus();

			//jump to the property's current value in the combo box
			int j = m_cmbBox.FindStringExact(0,lBoxSelText);
			if (j != CB_ERR)
				m_cmbBox.SetCurSel(j);
			else
				m_cmbBox.SetCurSel(0);
		}
		break;
	case PIT_COMBO:
		{
			//display the combo box.  If the combo box has already been
			//created then simply move it to the new location, else create it
			m_nLastBox = 0;
			if (m_cmbBox)
			{
				m_cmbBox.MoveWindow(rect);
			}
			else
			{	
				rect.bottom += 200;
				m_cmbBox.Create(CBS_DROPDOWNLIST | CBS_NOINTEGRALHEIGHT | WS_VISIBLE | WS_CHILD | WS_BORDER,
								rect,this,IDC_PROPCMBBOX);
				m_cmbBox.SetFont(&m_SSerif8Font);
			}

			//add the choices for this particular property
			CString cmbItems = ((S_Combo*)pItem->m_pValue)->m_cmbItems;
			lBoxSelText = ((S_Combo*)pItem->m_pValue)->m_curValue;

			m_cmbBox.ResetContent();
			int i,i2;
			i=0;

			while ((i2=cmbItems.Find('|',i)) != -1)
			{
				m_cmbBox.AddString(cmbItems.Mid(i,i2-i));
				i=i2+1;
			}

			m_cmbBox.ShowWindow(SW_SHOW);
			m_cmbBox.SetFocus();

			//jump to the property's current value in the combo box
			int j = m_cmbBox.FindStringExact(0,lBoxSelText);
			if (j != CB_ERR)
				m_cmbBox.SetCurSel(j);
			else
				m_cmbBox.SetCurSel(0);
		}
		break;
	case PIT_NUM:
		{
			//display edit box
			m_nLastBox = 1;
			m_prevSel = m_curSel;
			rect.bottom -= 3;
			if (m_editBox)
			{
				m_editBox.MoveWindow(rect);
			}
			else
			{	
				m_editBox.Create( /*ES_NUMBER | */ES_LEFT | ES_AUTOHSCROLL | WS_VISIBLE | WS_CHILD | WS_BORDER,
					rect,this,IDC_PROPEDITBOX);
				m_editBox.SetFont(&m_SSerif8Font);
			}

			lBoxSelText.Format( "%d", *(int*)pItem->m_pValue );

			m_editBox.ShowWindow(SW_SHOW);
			m_editBox.SetFocus();
			//set the text in the edit box to the property's current value
			m_editBox.SetWindowText(lBoxSelText);
		}
		break;
	case PIT_EDIT:
		{
			//display edit box
			m_nLastBox = 1;
			m_prevSel = m_curSel;
			rect.bottom -= 3;
			if (m_editBox)
			{
				m_editBox.MoveWindow(rect);
			}
			else
			{	
				m_editBox.Create(ES_LEFT | ES_AUTOHSCROLL | WS_VISIBLE | WS_CHILD | WS_BORDER,
					rect,this,IDC_PROPEDITBOX);
				m_editBox.SetFont(&m_SSerif8Font);
			}

			lBoxSelText = *(CString*)pItem->m_pValue;

			m_editBox.ShowWindow(SW_SHOW);
			m_editBox.SetFocus();
			//set the text in the edit box to the property's current value
			m_editBox.SetWindowText(lBoxSelText);
		}
		break;
	case PIT_COMMENTS:
		break;
	default:
		DisplayButton(rect);
		break;
	}
}

void CPropertyList::DisplayButton(CRect region)
{
	//displays a button if the property is a file/color/font chooser
	m_nLastBox = 2;
	m_prevSel = m_curSel;

	if (region.Width() > 25)
		region.left = region.right - 25;
	region.bottom -= 3;

	if (m_btnCtrl)
		m_btnCtrl.MoveWindow(region);
	else
	{	
		m_btnCtrl.Create("...",BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
						region,this,IDC_PROPBTNCTRL);
		m_btnCtrl.SetFont(&m_SSerif8Font);
	}

	m_btnCtrl.ShowWindow(SW_SHOW);
	m_btnCtrl.SetFocus();
}

void CPropertyList::OnKillFocus(CWnd* pNewWnd) 
{
	//m_btnCtrl.ShowWindow(SW_HIDE);

	CListBox::OnKillFocus(pNewWnd);
}

void CPropertyList::OnKillfocusCmbBox() 
{
	m_cmbBox.ShowWindow(SW_HIDE);

	Invalidate();
}

void CPropertyList::OnKillfocusEditBox()
{
	m_editBox.ShowWindow(SW_HIDE);

	m_bUpdate = true;

	Invalidate();
}

void CPropertyList::OnSelchangeCmbBox()
{
	CString selStr;
	if (m_cmbBox)
	{
		m_cmbBox.GetLBText(m_cmbBox.GetCurSel(),selStr);
		S_PropertyItem* pItem = (S_PropertyItem*) GetItemDataPtr(m_curSel);
		if ( pItem )
		{
			switch( pItem->m_nItemType )
			{
			case PIT_COMBO:
				*(CString*)pItem->m_pValue = selStr;
				break;
			case PIT_BOOL:
				*(BOOL*)pItem->m_pValue = selStr == "TRUE" ? TRUE : FALSE;
				break;
			default:
				assert( false );
				break;
			}
		}
	}

	m_bUpdate = true;
}

void CPropertyList::OnChangeEditBox()
{
	CString newStr;
	m_editBox.GetWindowText(newStr);
	
	S_PropertyItem* pItem = (S_PropertyItem*) GetItemDataPtr(m_curSel);
	if ( pItem )
	{
		switch( pItem->m_nItemType )
		{
		case PIT_NUM:
			{
				*(int*)pItem->m_pValue = atoi( newStr.GetBuffer() );
			}
			break;
		case PIT_EDIT:
			{
				*(CString*)pItem->m_pValue = newStr;
			}
			break;
		default:
			assert( false );
			break;
		}

	}

}

void CPropertyList::OnButton()
{
	S_PropertyItem* pItem = (S_PropertyItem*) GetItemDataPtr(m_curSel);
	if ( !pItem )
		return;

	//display the appropriate common dialog depending on what type
	//of chooser is associated with the property
	switch( pItem->m_nItemType )
	{
	case PIT_COLOR:
		{
			CColorDialog ClrDlg( *(COLORREF*)pItem->m_pValue );


			if (IDOK == ClrDlg.DoModal())
			{
				COLORREF selClr = ClrDlg.GetColor();
				*(COLORREF*)pItem->m_pValue = selClr;
				Invalidate();

				m_bUpdate = true;
			}
		}
		break;
	case PIT_DIALOG:
		{
			if( IDOK == ((CDialog*)pItem->m_pValue)->DoModal() )
			{
				m_btnCtrl.ShowWindow(SW_HIDE);

				m_bUpdate = true;
			}
		}
		break;
	case PIT_FILE:
		{
			CString SelectedFile; 
			CString Filter("Lua Files (*.lua)|*.lua||");

			CFileDialog FileDlg(TRUE, NULL, NULL, NULL,
				Filter);

			CString currPath = *(CString*)pItem->m_pValue;
			FileDlg.m_ofn.lpstrTitle = "Select file";
			if (currPath.GetLength() > 0)
				FileDlg.m_ofn.lpstrInitialDir = currPath.Left(
				currPath.GetLength() - currPath.ReverseFind('\\'));

			if(IDOK == FileDlg.DoModal())
			{
				SelectedFile = FileDlg.GetPathName();
				int nOff = SelectedFile.Find( "lua" );
				SelectedFile.Delete( 0, nOff );

				m_btnCtrl.ShowWindow(SW_HIDE);


				*(CString*)pItem->m_pValue = SelectedFile;
				Invalidate();

				m_bUpdate = true;
			}
		}
		break;
	case PIT_FONT:
		{
			S_Font *pFont = (S_Font*)pItem->m_pValue;

			LOGFONT lf;
			memset(&lf, 0, sizeof(LOGFONT));
			strcpy(lf.lfFaceName, pFont->m_strName);
			lf.lfHeight = -MulDiv(pFont->m_nSize, GetDC()->GetDeviceCaps(LOGPIXELSY), 72);
			CFontDialog FontDlg( &lf, CF_EFFECTS | CF_SCREENFONTS,NULL, this );
			FontDlg.m_cf.rgbColors = pFont->m_colColor;

			if(IDOK == FontDlg.DoModal())
			{
				pFont->m_strName = FontDlg.GetFaceName();
				pFont->m_nSize = FontDlg.GetSize()/10;
				pFont->m_colColor = FontDlg.GetColor();

				m_btnCtrl.ShowWindow(SW_HIDE);
				Invalidate();
				m_bUpdate = true;
			}
		}
		break;
	}
}

void CPropertyList::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bTracking)
	{
		//if columns were being resized then this indicates
		//that mouse is up so resizing is done.  Need to redraw
		//columns to reflect their new widths.
		
		m_bTracking = FALSE;
		//if mouse was captured then release it
		if (GetCapture()==this)
			::ReleaseCapture();

		::ClipCursor(NULL);

		CClientDC dc(this);
		InvertLine(&dc,CPoint(point.x,m_nDivTop),CPoint(point.x,m_nDivBtm));
		//set the divider position to the new value
		m_nDivider = point.x;

		//redraw
		Invalidate();
	}
	else
	{
		BOOL loc;
		int i = ItemFromPoint(point,loc);
		m_curSel = i;
		CListBox::OnLButtonUp(nFlags, point);
	}
}

void CPropertyList::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if ((point.x>=m_nDivider-5) && (point.x<=m_nDivider+5))
	{
		//if mouse clicked on divider line, then start resizing

		::SetCursor(m_hCursorSize);

		CRect windowRect;
		GetWindowRect(windowRect);
		windowRect.left += 10; windowRect.right -= 10;
		//do not let mouse leave the list box boundary
		::ClipCursor(windowRect);
		
		if (m_cmbBox)
			m_cmbBox.ShowWindow(SW_HIDE);
		if (m_editBox)
			m_editBox.ShowWindow(SW_HIDE);

		CRect clientRect;
		GetClientRect(clientRect);

		m_bTracking = TRUE;
		m_nDivTop = clientRect.top;
		m_nDivBtm = clientRect.bottom;
		m_nOldDivX = point.x;

		CClientDC dc(this);
		InvertLine(&dc,CPoint(m_nOldDivX,m_nDivTop),CPoint(m_nOldDivX,m_nDivBtm));

		//capture the mouse
		SetCapture();
	}
	else
	{
		m_bTracking = FALSE;
		CListBox::OnLButtonDown(nFlags, point);
	}
}

void CPropertyList::OnMouseMove(UINT nFlags, CPoint point) 
{	
	if (m_bTracking)
	{
		//move divider line to the mouse pos. if columns are
		//currently being resized
		CClientDC dc(this);
		//remove old divider line
		InvertLine(&dc,CPoint(m_nOldDivX,m_nDivTop),CPoint(m_nOldDivX,m_nDivBtm));
		//draw new divider line
		InvertLine(&dc,CPoint(point.x,m_nDivTop),CPoint(point.x,m_nDivBtm));
		m_nOldDivX = point.x;
	}
	else if ((point.x >= m_nDivider-5) && (point.x <= m_nDivider+5))
		//set the cursor to a sizing cursor if the cursor is over the row divider
		::SetCursor(m_hCursorSize);
	else
		CListBox::OnMouseMove(nFlags, point);
}

void CPropertyList::InvertLine(CDC* pDC,CPoint ptFrom,CPoint ptTo)
{
	int nOldMode = pDC->SetROP2(R2_NOT);
	
	pDC->MoveTo(ptFrom);
	pDC->LineTo(ptTo);

	pDC->SetROP2(nOldMode);
}

void CPropertyList::PreSubclassWindow() 
{
	m_bDivIsSet = FALSE;
	m_nDivider = 0;
	m_bTracking = FALSE;
	m_curSel = 1;

	m_hCursorSize = AfxGetApp()->LoadStandardCursor(IDC_SIZEWE);
	m_hCursorArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);

	m_SSerif8Font.CreatePointFont(80,_T("MS Sans Serif"));
}

int CPropertyList::AddItem( S_PropertyItem* pItem )
{
	m_vtpItem.push_back( pItem );

	int nIndex = AddString(_T(""));
	SetItemDataPtr(nIndex, pItem );
	return nIndex;
}

bool CPropertyList::IsUpdate()
{
	bool bIsUpdate = m_bUpdate;
	if ( m_bUpdate == true )
	{
		m_bUpdate = false;
	}
	return bIsUpdate;
}



void CPropertyList::DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (m_btnCtrl)
		m_btnCtrl.ShowWindow(SW_HIDE);

	CListBox::DeleteItem(lpDeleteItemStruct);
}
