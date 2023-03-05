// BugReporter-NewView.h : interface of the CBugReporterNewView class
//


#pragma once


class CBugReporterNewView : public CView
{
protected: // create from serialization only
	CBugReporterNewView();
	DECLARE_DYNCREATE(CBugReporterNewView)

// Attributes
public:
	CBugReporterNewDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CBugReporterNewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BugReporter-NewView.cpp
inline CBugReporterNewDoc* CBugReporterNewView::GetDocument() const
   { return reinterpret_cast<CBugReporterNewDoc*>(m_pDocument); }
#endif

