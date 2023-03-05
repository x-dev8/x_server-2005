// Source\Platform_ChangePlayerNamePage.cpp : implementation file
//
#include "Platform_ChangePlayerNamePage.h"


// Platform_ChangePlayerName dialog

IMPLEMENT_DYNAMIC(Platform_ChangePlayerName, PageInterface)

Platform_ChangePlayerName::Platform_ChangePlayerName()
	: PageInterface(Platform_ChangePlayerName::IDD)
{
    SetType(ChangeCharacterNamePage);
}

Platform_ChangePlayerName::~Platform_ChangePlayerName()
{
}

void Platform_ChangePlayerName::DoDataExchange(CDataExchange* pDX)
{
	PageInterface::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ED_PLATFROM_CREATEROLE_NAME, TargetPlayerName);
    DDV_MaxChars(pDX, TargetPlayerName, 32);
    DDX_Text(pDX, IDC_ED_PLATFROM_CREATEROLE_NAME, NewPlayerName);
    DDV_MaxChars(pDX, NewPlayerName, 32);
}

BOOL Platform_ChangePlayerName::OnInitDialog()
{
    if (!PageInterface::OnInitDialog())
        return FALSE;
    TargetPlayerName = "玩家名";
    NewPlayerName = "新玩家名";
    UpdateData(FALSE);
    return TRUE;
}


BEGIN_MESSAGE_MAP(Platform_ChangePlayerName, PageInterface)
    ON_BN_CLICKED(IDC_BTN_SEND_CREATEROLE, &Platform_ChangePlayerName::OnBnClickedBtnSendChangeRoleName)
END_MESSAGE_MAP()

void Platform_ChangePlayerName::OnBnClickedBtnSendChangeRoleName()
{
    UpdateData();
    if (TargetPlayerName.IsEmpty()||NewPlayerName.IsEmpty())
    {
        MessageBox("请输入玩家名和新玩家名");
        return;
    }
    if ( NULL != Bot )
    {
        Bot->ReqChangeCharacterName(TargetPlayerName,NewPlayerName);
    }

}
// Platform_ChangePlayerName message handlers
