///////////////////////////////////////////////////////////////////////////////
//
// StatusBarXP.cpp : implementation file
//
///////////////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include <afxwin.h>         // MFC 核心和标准组件
#include <afxext.h>         // MFC 扩展
#include <afxdisp.h>        // MFC 自动化类
#include <afxdtctl.h>		// Internet Explorer 4 公共控件的 MFC 支持
#include <afxcmn.h>			// Windows 公共控件的 MFC 支持

#include "StatusBarXP.h"
#include "Draw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
BOOL CStatusBarXP::SetIndicators (const UINT* lpIDArray, int nIDCount)
{
    if ( !CStatusBar::SetIndicators (lpIDArray, nIDCount) )
    {
        return false;
    }
    SendMessage (SB_SETMINHEIGHT, 20);

    for ( int i = 0; i < nIDCount; i++ )
    {
        UINT a, b;
        int c;

        GetPaneInfo (i, a, b, c);
        SetPaneInfo (i, a, b|SBPS_NOBORDERS, c);
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CStatusBarXP, CStatusBar)
    //{{AFX_MSG_MAP(CStatusBarXP)
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CStatusBarXP, CStatusBar);

///////////////////////////////////////////////////////////////////////////////
void CStatusBarXP::OnPaint ()
{
    Default();

    CClientDC cDC (this);
    CPenDC pen (cDC, ::GetSysColor (COLOR_3DSHADOW));
    CRect rcItem;

    cDC.SelectObject (::GetStockObject (NULL_BRUSH));

    for ( int i = 0; i < m_nCount; i++ )
    {
        GetItemRect (i, rcItem);
        cDC.Rectangle (rcItem); 
    }
}
