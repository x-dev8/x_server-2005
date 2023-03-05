// Source\Platform_Broadcast.cpp : implementation file
//
#include "Platform_BroadcastPage.h"
// Platform_Broadcast dialog

IMPLEMENT_DYNAMIC(Platform_Broadcast, PageInterface)

Platform_Broadcast::Platform_Broadcast()
	: PageInterface(Platform_Broadcast::IDD)
    , BroadcastString(_T(""))
{
    SetType(ShutDownServerPage);
}

Platform_Broadcast::~Platform_Broadcast()
{
}

void Platform_Broadcast::DoDataExchange(CDataExchange* pDX)
{
    PageInterface::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ED_PLATFORM_MESSAGE, BroadcastString);
	DDV_MaxChars(pDX, BroadcastString, 511);
}


BEGIN_MESSAGE_MAP(Platform_Broadcast, PageInterface)
    ON_BN_CLICKED(IDC_BTN_PLATFROM_SENDBROADCAST, &Platform_Broadcast::OnBnClickedBtnPlatfromSendbroadcast)
END_MESSAGE_MAP()

BOOL Platform_Broadcast::OnInitDialog()
{
    if (!PageInterface::OnInitDialog())
        return FALSE;

    BroadcastString = "请输入广播信息";
    UpdateData(false);
    return TRUE;
}
// Platform_Broadcast message handlers

void Platform_Broadcast::OnBnClickedBtnPlatfromSendbroadcast()
{
    // TODO: Add your control notification handler code here
    UpdateData();
    if (NULL != Bot)
    {
        Bot->Broadcast(BroadcastString.GetBuffer());
        MessageBox("发送完毕!");
    }
//     OperationMsg Msg;
//     Msg.TestOperation = OperationMsg::EPO_BROADCAST;
//     if (Msg.SetString(BroadcastString.GetBuffer()) != 0)
//         PushPlatformWork(&Msg);
}
