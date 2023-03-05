#if !defined(AFX_HISTOGRAMCTRL_H__A1446DDE_3456_47A9_BA8E_D4F048F3325A__INCLUDED_)
#define AFX_HISTOGRAMCTRL_H__A1446DDE_3456_47A9_BA8E_D4F048F3325A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HistogramCtrl.h : header file
//

#include "AfxTempl.h"
#include <afxwin.h>
/////////////////////////////////////////////////////////////////////////////
// CHistogramCtrl window
#include <list>

class CHistogramCtrl : public CWnd
{
// Construction
public:
	CHistogramCtrl();

// Attributes
public:
	typedef enum {LOW_SPEED = 3000, NORMAL_SPEED = 1000, HIGH_SPEED = 500, IDLE = 0} SPEED;

// Operations
public:
	BOOL Create(DWORD dwStyle, CWnd *pParentWnd,UINT DrawDlgId, UINT uID = 12345);
	void SetRange(UINT uLower, UINT uUpper);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistogramCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL SetGridsColor(COLORREF cr);
	BOOL SetBkColor(COLORREF cr);
	void SetSafePen(int nWidth, COLORREF crColor);   // 用于画不超出的值
    void SetUnSafePen(int nWidth, COLORREF crColor); // 用于画超出上线的值
	CHistogramCtrl::SPEED SetSpeed(CHistogramCtrl::SPEED uSpeed);
	bool SetPos(UINT uPos);
	virtual ~CHistogramCtrl();

    void Draw(UINT uPos);
    void Reset();
	// Generated message map functions
protected:
	//{{AFX_MSG(CHistogramCtrl)
	afx_msg void OnPaint();
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	enum SPEED m_uSpeed;
	UINT m_yPos;
	UINT m_yPreviousPos;
	UINT m_uOffset;

	void DrawLine();
	BOOL InvalidateCtrl();
	UINT GetAverage();

	CDC *m_pMemDC;

	UINT m_uLower;
	UINT m_uUpper;

	CRect m_rcClient;
	CPen m_SafeColorPen;
    CPen m_UnSafeColorPen;

	int m_nFirstLinePos;

	COLORREF m_crBackGround;
	COLORREF m_crGrids;

    CPoint LastPos;
	//CList<UINT, UINT&> *m_pList;
    std::list<UINT> m_pList;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTOGRAMCTRL_H__A1446DDE_3456_47A9_BA8E_D4F048F3325A__INCLUDED_)
