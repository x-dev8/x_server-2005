// Platform_ShutdownServer.cpp : implementation file
//

#include "stdafx.h"
#include "PageInterface.h"


// Platform_ShutdownServer dialog

IMPLEMENT_DYNAMIC(PageInterface, CPropertyPage)


PageInterface::PageInterface(int value)
:CPropertyPage(value)
,Bot(NULL)
{

}

PageInterface::~PageInterface()
{
    Bot = NULL;
}

void PageInterface::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PageInterface, CPropertyPage)
    ON_EN_CHANGE(IDC_ED_SHUTDOWN_TIME, &PageInterface::OnEnChangeEdShutdownTime)
END_MESSAGE_MAP()


// Platform_ShutdownServer message handlers

void PageInterface::OnEnChangeEdShutdownTime()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CPropertyPage::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}

BOOL PageInterface::OnInitDialog()
{
    return CPropertyPage::OnInitDialog();
}
