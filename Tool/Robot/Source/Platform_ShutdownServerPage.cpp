// Platform_ShutdownServer.cpp : implementation file
//


#include "Platform_ShutdownServerPage.h"

// Platform_ShutdownServer dialog

IMPLEMENT_DYNAMIC(Platform_ShutdownServer, CPropertyPage)

Platform_ShutdownServer::Platform_ShutdownServer()
	: PageInterface(Platform_ShutdownServer::IDD)
    , _ShutdownTime(0)
{
    SetType(ShutDownServerPage);
}

Platform_ShutdownServer::~Platform_ShutdownServer()
{
}

void Platform_ShutdownServer::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ED_SHUTDOWN_TIME, _ShutdownTime);
	DDV_MinMaxUInt(pDX, _ShutdownTime, 0, 99999999);
}


BEGIN_MESSAGE_MAP(Platform_ShutdownServer, CPropertyPage)
    ON_EN_CHANGE(IDC_ED_SHUTDOWN_TIME, &Platform_ShutdownServer::OnEnChangeEdShutdownTime)
    ON_BN_CLICKED(IDC_BTN_SEND_SD, &Platform_ShutdownServer::OnBnClickedBtnSendSd)
END_MESSAGE_MAP()


// Platform_ShutdownServer message handlers

void Platform_ShutdownServer::OnEnChangeEdShutdownTime()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CPropertyPage::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}

BOOL Platform_ShutdownServer::OnInitDialog()
{
    if (!PageInterface::OnInitDialog())
        return FALSE;

    _ShutdownTime = 10;
    UpdateData(false);
    return TRUE;
}

void Platform_ShutdownServer::OnBnClickedBtnSendSd()
{
    // TODO: Add your control notification handler code here
    UpdateData();
    if (Bot)
    {
        Bot->ReqShutdownServers(_ShutdownTime);
        MessageBox("·¢ËÍÍê±Ï!");
    }
//     OperationMsg Msg;
//     Msg.TestOperation = OperationMsg::EPO_SHUTDOWNSERVERS;
//     Msg.nParm[0] = _ShutdownTime;
//     PushPlatformWork(&Msg);
}
