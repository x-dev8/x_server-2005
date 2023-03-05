// BugReporter-NewView.cpp : implementation of the CBugReporterNewView class
//

#include "stdafx.h"
#include "BugReporter-New.h"

#include "BugReporter-NewDoc.h"
#include "BugReporter-NewView.h"
#include "BugReporter.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBugReporterNewView

IMPLEMENT_DYNCREATE(CBugReporterNewView, CView)

BEGIN_MESSAGE_MAP(CBugReporterNewView, CView)
	// Standard printing commands
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CBugReporterNewView construction/destruction

CBugReporterNewView::CBugReporterNewView()
{
	// TODO: add construction code here

}

CBugReporterNewView::~CBugReporterNewView()
{
}

BOOL CBugReporterNewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CBugReporterNewView drawing

void CBugReporterNewView::OnDraw(CDC* /*pDC*/)
{
	CBugReporterNewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

// CBugReporterNewView diagnostics

#ifdef _DEBUG
void CBugReporterNewView::AssertValid() const
{
	CView::AssertValid();
}

void CBugReporterNewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBugReporterNewDoc* CBugReporterNewView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBugReporterNewDoc)));
	return (CBugReporterNewDoc*)m_pDocument;
}
#endif //_DEBUG


// CBugReporterNewView message handlers
int CBugReporterNewView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
// 	if (CView::OnCreate(lpCreateStruct) == -1)
// 		return -1;
	CBugReporter dlg;
	dlg.DoModal();
	::TerminateProcess( ::GetCurrentProcess(), 0 );
	return 0;
}