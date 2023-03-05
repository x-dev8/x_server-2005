/*
Author:
	Mehdi Mousavi

Email:
	mehdi_mousavi@hotmail.com
	webmaster@modemmania.com

Date of release:
	24th of December 2009

Description:
	The initial idea of doing this code has been put into my mind when my love asked me
	to go to a clinic in order to check out my heart. You know, doctors have got some
	sort of plotters that plots the information obtained from the heart on a piece of
	paper as a histogram. The idea has been dropped into my mind there!

Dedicated to:
	My love, Cindy

Modifiy by:
    jialiang li

Copyright & disclaimer:
	Permission is granted to distribute *unmodified* version of this source code.
	You are entitled to use CHistogramCtrl for both commercial and/or educational
	purposes as far as you keep these comments intact. Please feel free to post
	any additions to the author.
*/

// #include "stdafx.h"
// #include "histogram.h"
#include "HistogramCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistogramCtrl

CHistogramCtrl::CHistogramCtrl()
{
	m_nFirstLinePos = 13;

	m_pMemDC = NULL;
	//m_pList = NULL;
	m_uSpeed = IDLE;

	m_crBackGround = RGB(0, 0, 0);
	m_crGrids = RGB(0, 130, 66);

	SetSafePen(1, RGB(0, 255, 0));
    SetUnSafePen(1,RGB(255, 0, 0));

	SetRange(1, 100);

    LastPos.SetPoint(0,0);
}

CHistogramCtrl::~CHistogramCtrl()
{
	if(m_pMemDC)
		delete m_pMemDC;

// 	if(m_pList)
// 		delete m_pList;
}


BEGIN_MESSAGE_MAP(CHistogramCtrl, CWnd)
	//{{AFX_MSG_MAP(CHistogramCtrl)
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CHistogramCtrl message handlers
#pragma warning( push, 0  )

BOOL CHistogramCtrl::Create(DWORD dwStyle, /*const RECT &rect,*/ CWnd *pParentWnd,UINT DrawDlgId, UINT uID)
{
	//Postcondition:
	//	Creates a window within the "rect" region of the client screen
	//	Returns TRUE if the function creates the control successfully
	//	or FALSE if it fails.
    if (NULL == pParentWnd)
        return FALSE;
    CRect rect;
    CWnd* DrawDlg = pParentWnd->GetDlgItem(DrawDlgId);
    if (NULL == DrawDlg)
        return FALSE;

    DrawDlg->GetWindowRect(rect);
    pParentWnd->ScreenToClient(rect);

	BOOL bRet = CWnd::CreateEx(WS_EX_CLIENTEDGE, 
								AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW),
								NULL,
								dwStyle,
								rect.left,
								rect.top,
								rect.right - rect.left,
								rect.bottom - rect.top,
								pParentWnd->GetSafeHwnd(),
								(HMENU)uID);

	if(!bRet)
		return FALSE;

	m_pMemDC = new CDC;
	if(!m_pMemDC)
		return FALSE;

// 	m_pList = new CList<UINT, UINT&>;
// 	if(!m_pList)
// 		return FALSE;

	GetClientRect(m_rcClient);

	if(!InvalidateCtrl())
		return FALSE;

	SetSpeed(CHistogramCtrl::NORMAL_SPEED);
	
	return TRUE;
}

#pragma warning( pop )

void CHistogramCtrl::SetRange(UINT uLower, UINT uUpper)
{
	ASSERT(uLower && uUpper && uLower < uUpper);
    if (uLower > uUpper)
        return;
	//Postcondition:
	//	Sets the upper and lower (limits) range
	m_uUpper = uUpper - uLower + 1;
	m_uLower = 1;
	m_uOffset = uLower - 1;
}

BOOL CHistogramCtrl::InvalidateCtrl()
{
	//Postcondition:
	//	Paints the entire client area of the control
	//	Returns TRUE if it's done successfuly or FALSE if it fails

	CClientDC dc(this);

	if(m_pMemDC->GetSafeHdc())
		return FALSE;

	if(!m_pMemDC->CreateCompatibleDC(&dc))
		return FALSE;

	CBitmap bmp;
	if(!bmp.CreateCompatibleBitmap(&dc, m_rcClient.Width(), m_rcClient.Height()))
		return FALSE;

	if(!m_pMemDC->SelectObject(bmp))
		return FALSE;

	//Set the background color of the control
	CBrush bkBrush;
	if(!bkBrush.CreateSolidBrush(m_crBackGround))
		return FALSE;
	
	m_pMemDC->FillRect(m_rcClient, &bkBrush);

	//Select a specified pen to the device context to draw background lines
	CPen bkLinesPen;
	if(!bkLinesPen.CreatePen(PS_SOLID, 1, m_crGrids))
		return FALSE;

	if(!m_pMemDC->SelectObject(bkLinesPen))
		return FALSE;

	//Draw background lines
	for(register int i = m_rcClient.left - 1; i < m_rcClient.right; i += 13)
	{
		m_pMemDC->MoveTo(i, m_rcClient.top);
		m_pMemDC->LineTo(i, m_rcClient.bottom);
	}

	for(register int j = m_rcClient.top - 1; j < m_rcClient.bottom; j += 13)
	{
		m_pMemDC->MoveTo(m_rcClient.left, j);
		m_pMemDC->LineTo(m_rcClient.right, j);
	}

	m_yPreviousPos = m_yPos = m_rcClient.bottom + 1;

	InvalidateRect(m_rcClient);

	return TRUE;
}

void CHistogramCtrl::OnPaint() 
{
	CPaintDC dc(this);

	if(m_pMemDC->GetSafeHdc())
		dc.BitBlt(0, 0, m_rcClient.Width(), m_rcClient.Height(), m_pMemDC, 0, 0, SRCCOPY);
}

void CHistogramCtrl::DrawLine()
{
	//Postcondition:
	//	Draws the histogram within the client area of the control

	if(!m_pMemDC->GetSafeHdc())
		return;

	CRect bkRect(m_rcClient.right - 3, m_rcClient.top, m_rcClient.right, m_rcClient.bottom);

	CBrush bkBrush;
	bkBrush.CreateSolidBrush(m_crBackGround);
	m_pMemDC->FillRect(bkRect, &bkBrush);

	m_pMemDC->BitBlt(0, 0, m_rcClient.Width(), m_rcClient.Height(), m_pMemDC, 3, 0, SRCCOPY);

	CPen myPen;
	myPen.CreatePen(PS_SOLID, 1, m_crGrids);
	m_pMemDC->SelectObject(myPen);

	m_nFirstLinePos -= 3;
	if(m_nFirstLinePos < 0)
		m_nFirstLinePos += 13;

	int nX = m_rcClient.right - ((m_rcClient.right - m_nFirstLinePos) % 13) - 1;
	m_pMemDC->MoveTo(nX, m_rcClient.top);
	m_pMemDC->LineTo(nX, m_rcClient.bottom);


	for(register int j = m_rcClient.top - 1; j < m_rcClient.bottom; j += 13)
	{
		m_pMemDC->MoveTo(bkRect.left - 3, j);
		m_pMemDC->LineTo(bkRect.right, j);
	}

	UINT uAverage = GetAverage();
	TRACE("uAverage: %u\r\n", uAverage);
	if(uAverage)
    {
        long Pos = (uAverage * m_rcClient.bottom / m_uUpper);
        if (m_rcClient.bottom >= Pos)
        {
            m_yPos = m_rcClient.bottom - Pos;
        }
        else
        {
            m_yPos = m_rcClient.top + 1;
        }
		// m_yPos = m_rcClient.bottom - (uAverage * m_rcClient.bottom / m_uUpper);
    }

	if(m_yPreviousPos == (unsigned)m_rcClient.bottom + 1)
		m_yPreviousPos = m_yPos;

    if (uAverage <= m_uUpper)
    {
        m_pMemDC->SelectObject(m_SafeColorPen);
        m_pMemDC->MoveTo(m_rcClient.right - 11 - 3, m_yPreviousPos);
        m_pMemDC->LineTo(m_rcClient.right - 11, m_yPos);
    }
    else
    {
        m_pMemDC->SelectObject(m_UnSafeColorPen);
        if (LastPos.x == 0 && LastPos.y == 0)
        {
            m_pMemDC->MoveTo(m_rcClient.right - 11 - 3 , m_yPreviousPos );
            m_pMemDC->LineTo(m_rcClient.right - 11, m_yPreviousPos );
        }
        else
        {
            m_pMemDC->MoveTo(LastPos.x , LastPos.y );
            m_pMemDC->LineTo( m_rcClient.right - 11, m_rcClient.top + 1 );
            m_yPreviousPos = m_rcClient.top + 1;
        }
    }
	
	m_yPreviousPos = m_yPos;

    LastPos.x = m_rcClient.right - 11 - 3;
    LastPos.y = m_yPreviousPos;
	Invalidate();
}

bool CHistogramCtrl::SetPos(UINT uPos)
{
	uPos -= m_uOffset;
	ASSERT(/*uPos <= m_uUpper &&*/ uPos >= m_uLower);
    if ( uPos < m_uLower )
        return false;
	//Postcondition:
	//	Adds the specified point to a list, so that we
	//	would be able to draw the histogram within the
	//	specified intervals.
	//m_pList->AddHead(uPos);
    m_pList.push_back(uPos);
    return true;
}

void CHistogramCtrl::Draw(UINT uPos) 
{
    if ( SetPos(uPos) )
	    DrawLine();
}

CHistogramCtrl::SPEED CHistogramCtrl::SetSpeed(enum SPEED uSpeed)
{
	enum SPEED oldSpeed = m_uSpeed;
	m_uSpeed = uSpeed;

	KillTimer(0);

	if(uSpeed != CHistogramCtrl::IDLE)
		SetTimer(0, m_uSpeed, NULL);

	return oldSpeed;
}

void CHistogramCtrl::SetSafePen(int nWidth, COLORREF crColor)
{
	m_SafeColorPen.DeleteObject();
	m_SafeColorPen.CreatePen(PS_SOLID, nWidth, crColor);
}

void CHistogramCtrl::SetUnSafePen(int nWidth, COLORREF crColor)
{
    m_UnSafeColorPen.DeleteObject();
    m_UnSafeColorPen.CreatePen(PS_SOLID,nWidth,crColor);
}

BOOL CHistogramCtrl::SetBkColor(COLORREF cr)
{
	BOOL bRet = FALSE;
	enum SPEED oldSpeed = SetSpeed(CHistogramCtrl::IDLE);

	m_crBackGround = cr;

	CClientDC dc(this);

	int oldPos = m_nFirstLinePos;
	m_nFirstLinePos = 13;
	if(m_pMemDC->DeleteDC())
		if(InvalidateCtrl())
			bRet = TRUE;

	if(!bRet)
		m_nFirstLinePos = oldPos;

	SetSpeed(oldSpeed);

	return bRet;
}

BOOL CHistogramCtrl::SetGridsColor(COLORREF cr)
{
	BOOL bRet = FALSE;
	enum SPEED oldSpeed = SetSpeed(CHistogramCtrl::IDLE);

	m_crGrids = cr;

	CClientDC dc(this);

	int oldPos = m_nFirstLinePos;
	m_nFirstLinePos = 13;
	if(m_pMemDC->DeleteDC())
		if(InvalidateCtrl())
			bRet = TRUE;

	if(!bRet)
		m_nFirstLinePos = oldPos;

	SetSpeed(oldSpeed);

	return bRet;
}

UINT CHistogramCtrl::GetAverage()
{
	UINT uCounter = 0, uSum = 0;
	while(!m_pList.empty())
	{
		//uSum += m_pList->RemoveTail();
        uSum += *m_pList.begin();
        m_pList.erase(m_pList.begin());
		uCounter++;
	}

	return uCounter ? uSum / uCounter : 0;
}

void CHistogramCtrl::Reset()
{
    BOOL bRet = FALSE;
    enum SPEED oldSpeed = SetSpeed(CHistogramCtrl::IDLE);

    CClientDC dc(this);

    int oldPos = m_nFirstLinePos;
    m_nFirstLinePos = 13;



    if(m_pMemDC->DeleteDC())
        if(InvalidateCtrl())
            bRet = TRUE;

    if(!bRet)
        m_nFirstLinePos = oldPos;

    SetSpeed(oldSpeed);
}