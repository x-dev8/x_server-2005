// Source\Platfrom_KickPlayerPage.cpp : implementation file
//

#include "stdafx.h"
#include "Platfrom_KickPlayerPage.h"


// Platfrom_KickPlayer dialog

IMPLEMENT_DYNAMIC(Platfrom_KickPlayer, PageInterface)

Platfrom_KickPlayer::Platfrom_KickPlayer()
	: PageInterface(Platfrom_KickPlayer::IDD)
    , KickPlayerName(_T(""))
{
    SetType(KickPlayerPage);
}

Platfrom_KickPlayer::~Platfrom_KickPlayer()
{
}

BOOL Platfrom_KickPlayer::OnInitDialog()
{
    if (!PageInterface::OnInitDialog())
        return FALSE;

    KickPlayerName = "ÇëÊäÈëÍæ¼ÒÃû×Ö";
    UpdateData(FALSE);
    return TRUE;
}

void Platfrom_KickPlayer::DoDataExchange(CDataExchange* pDX)
{
    PageInterface::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ED_KICKPLAYERNAME, KickPlayerName);
	DDV_MaxChars(pDX, KickPlayerName, 32);
}


BEGIN_MESSAGE_MAP(Platfrom_KickPlayer, PageInterface)
    ON_BN_CLICKED(IDC_BTN_KICK, &Platfrom_KickPlayer::OnBnClickedBtnKick)
END_MESSAGE_MAP()


// Platfrom_KickPlayer message handlers

void Platfrom_KickPlayer::OnBnClickedBtnKick()
{
    // TODO: Add your control notification handler code here
    UpdateData();
    if (NULL != Bot && !KickPlayerName.IsEmpty())
    {
        Bot->KickPlayer(KickPlayerName.GetBuffer());
    }
//     OperationMsg Msg;
//     Msg.TestOperation = OperationMsg::EPO_KICKPLAYER;
//     if (Msg.SetString(KickPlayerName.GetBuffer()) != 0)
//         PushPlatformWork(&Msg);
}
