// KbcBmp.cpp : implementation file
//

#include "widget.h"
#include "KbcBmp.h"

//#include "../res/resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKbcBmp

IMPLEMENT_DYNCREATE(CKbcBmp, CView)

CKbcBmp::CKbcBmp()
{
}

CKbcBmp::~CKbcBmp()
{
}


BEGIN_MESSAGE_MAP(CKbcBmp, CView)
	//{{AFX_MSG_MAP(CKbcBmp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKbcBmp drawing

void CKbcBmp::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CKbcBmp diagnostics

#ifdef _DEBUG
void CKbcBmp::AssertValid() const
{
	CView::AssertValid();
}

void CKbcBmp::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKbcBmp message handlers

// 
void CKbcBmp::LoadBitmap(CString strFileName)
{
	m_picImg.Load(strFileName);

	m_nWidth		= m_picImg.m_Width;
	m_nHeight		= m_picImg.m_Height;
	m_nSliceWidth	= m_nWidth/4;
}

// CKbcBmpButton 에서 호출할 때 쓰는 함수.. 그림 네장이 연속적으로 붙은 것을 그려준다.nSeq에 따라..
void CKbcBmp::Draw(CDC *pDC,int nSeq,int nX,int nY,UINT nMask)
{
	UINT BLACK			= RGB(0,0,0);
	UINT WHITE			= RGB(255,255,255);
	UINT BMPWIDTH		= m_nWidth;
	UINT BMPHEIGHT		= m_nHeight;
	UINT MASK			= nMask;
	UINT SLICEWIDTH		= m_nSliceWidth;
	UINT INTERVAL		= SLICEWIDTH * nSeq;

	CDC					oriDC;
	CDC					srcDC;
	CDC					maskDC;
	CDC					memDC;
	CBitmap				oriBmp;
	CBitmap				srcBmp;
	CBitmap				maskBmp;	
	CBitmap				memBmp;
	CBitmap				*pOldoriDC;
	CBitmap				*pOldsrcDC;
	CBitmap				*pOldmaskDC;
	CBitmap				*pOldmemDC;


	// we draw whole button image to oriDC.	
	oriDC.CreateCompatibleDC(pDC);
	oriBmp.CreateCompatibleBitmap(pDC,m_nWidth,m_nHeight);
	pOldoriDC = oriDC.SelectObject(&oriBmp);
	m_picImg.Show(&oriDC,CRect(0,0,m_nWidth,m_nHeight));
	//////////////////////////////////////////////////////

	// then, copy 1/4 button image to srcDC.
	// if user wanna draw disable button, then copy fourth image of oriDC to srcDC.
	srcDC.CreateCompatibleDC(pDC);
	srcBmp.CreateCompatibleBitmap(pDC,SLICEWIDTH,BMPHEIGHT);
	pOldsrcDC = srcDC.SelectObject(&srcBmp);
	srcDC.BitBlt(0,0,SLICEWIDTH,BMPHEIGHT,&oriDC,INTERVAL,0,SRCCOPY);
	//////////////////////////////////////////////////////

	// make maskDC
	// mask image made by black and white.
	// black region is we wanna draw , white region is we don't wanna draw.
	maskDC.CreateCompatibleDC(pDC);
	maskBmp.CreateBitmap(SLICEWIDTH,BMPHEIGHT,1,1,NULL);
	pOldmaskDC = maskDC.SelectObject(&maskBmp);
	srcDC.SetBkColor(MASK);
	maskDC.BitBlt(0,0,SLICEWIDTH,BMPHEIGHT,&srcDC,0,0,SRCCOPY);
	//////////////////////////////////////////////////////////////

	// modify srcDC	image.
	// at this point, mask color of srcDC change to black color.
	srcDC.SetBkColor(BLACK);
	srcDC.SetTextColor(WHITE);
	srcDC.BitBlt(0,0,SLICEWIDTH,BMPHEIGHT,&maskDC,0,0,SRCAND);
	//////////////////////////////////////////////////////////////	

	// copy background to memDC
	memDC.CreateCompatibleDC(pDC);		
	memBmp.CreateCompatibleBitmap(pDC,SLICEWIDTH,BMPHEIGHT);
	pOldmemDC = memDC.SelectObject(&memBmp);
	memDC.BitBlt(0,0,SLICEWIDTH,BMPHEIGHT,pDC, nX, nY,SRCCOPY);
	//////////////////////////////////////////////////////////////	

	// Finally, draw makeDC with SRCAND(AND operation) and draw srcDC with SRCPAINT(OR operation).
	memDC.BitBlt(0,0,SLICEWIDTH,BMPHEIGHT,&maskDC,0,0,SRCAND);		
	memDC.BitBlt(0,0,SLICEWIDTH,BMPHEIGHT,&srcDC,0,0,SRCPAINT);
	//////////////////////////////////////////////////////////////
	 
	pDC->BitBlt( nX, nY,SLICEWIDTH,BMPHEIGHT,&memDC,0,0,SRCCOPY);	 
		

	oriDC.SelectObject(pOldoriDC);
	srcDC.SelectObject(pOldsrcDC);
	maskDC.SelectObject(pOldmaskDC);
	memDC.SelectObject(pOldmemDC);
}