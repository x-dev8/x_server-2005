#if !defined(AFX_PROPERTYLIST_H__74205380_1B56_11D4_BC48_00105AA2186F__INCLUDED_)
#define AFX_PROPERTYLIST_H__74205380_1B56_11D4_BC48_00105AA2186F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertyList.h : header file
//
#include <vector>

//using namespace std;

#define IDC_PROPCMBBOX   712
#define IDC_PROPEDITBOX  713
#define IDC_PROPBTNCTRL  714

struct S_Combo
{
	void SetData( char* pCurValue, char* pItems )
	{
		m_curValue = pCurValue;
		m_cmbItems = pItems;
	}

	CString	m_curValue;
	CString	m_cmbItems;
};

struct S_Font
{
	void SetFont( char* szName, COLORREF col, int nSize )
	{
		m_strName = szName;
		m_colColor = col;
		m_nSize = nSize;
	}
	CString		m_strName;
	COLORREF	m_colColor;
	int			m_nSize;
};

enum E_ItemType
{
	PIT_COMBO = 0		// m_pValue: S_Combo*
	,PIT_BOOL			// m_pValue: BOOL*
	,PIT_EDIT			// m_pValue: CString*
	,PIT_NUM			// m_pValue: int*
	,PIT_COLOR			// m_pValue: COLORREF*
	,PIT_FONT			// m_pValue: S_Font*
	,PIT_FILE			// m_pValue: CString*
	,PIT_DIALOG			// m_pValue: CDialog*
	,PIT_COMMENTS		// m_pValue: NULL or COLORREF
};

struct S_PropertyItem
{
	S_PropertyItem()
	{
		m_pValue = NULL;
	}
	void SetItem( int nType, char* pName, void* pValue )
	{
		m_nItemType = nType;
		m_propName = pName;
		m_pValue = pValue;
	}

	int		m_nItemType;
	CString m_propName;
	void*	m_pValue;
};

/////////////////////////////////////////////////////////////////////////////
// CPropertyList window

class CPropertyList : public CListBox
{
public:
	typedef void (*UPDATEFUN)(void);

public:
	int	AddItem( S_PropertyItem* pItem );
//	bool	IsUpdate();
	void SetUpdateCallbackFun( UPDATEFUN p ){ m_pUpdateCallbackFun = p; }
	void UpdateCallback();

	afx_msg void OnSelchange();
	// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertyList)
	public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	// Generated message map functions

protected:
	//{{AFX_MSG(CPropertyList)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg void OnKillfocusCmbBox();
	afx_msg void OnSelchangeCmbBox();
	afx_msg void OnKillfocusEditBox();
	afx_msg void OnChangeEditBox();
	afx_msg void OnButton();

	DECLARE_MESSAGE_MAP()

	void InvertLine(CDC* pDC,CPoint ptFrom,CPoint ptTo);
	void DisplayButton(CRect region);

	CComboBox m_cmbBox;
	CEdit m_editBox;
	CButton m_btnCtrl;
	CFont m_SSerif8Font;
	
	int m_curSel,m_prevSel;
	int m_nDivider;
	int m_nDivTop;
	int m_nDivBtm;
	int m_nOldDivX;
	int m_nLastBox;
	BOOL m_bTracking;
	BOOL m_bDivIsSet;
	HCURSOR m_hCursorArrow;
	HCURSOR m_hCursorSize;

//	bool	m_bUpdate;

	std::vector<S_PropertyItem*>	m_vtpItem;

private:
	UPDATEFUN m_pUpdateCallbackFun;

	// Construction
public:
	CPropertyList();
	virtual ~CPropertyList();
	virtual void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYLIST_H__74205380_1B56_11D4_BC48_00105AA2186F__INCLUDED_)
