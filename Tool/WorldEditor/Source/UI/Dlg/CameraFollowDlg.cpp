#include "stdafx.h"
#include "CameraFollowDlg.h"

IMPLEMENT_DYNAMIC(CCameraFollowDialog, CDialog)

BEGIN_MESSAGE_MAP(CCameraFollowDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CCameraFollowDialog::OnBnClickedOk)
END_MESSAGE_MAP()

CCameraFollowDialog::CCameraFollowDialog(CWnd *lpParent /* = NULL */) : CDialog(CCameraFollowDialog::IDD, lpParent)
{

}

CCameraFollowDialog::~CCameraFollowDialog()
{

}

BOOL CCameraFollowDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}

void CCameraFollowDialog::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CAMERA_FOLLOW_MEX, mInputMex);
}

void CCameraFollowDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (!mInputMex.IsEmpty())
		g_render->SetCameraFollowMex(mInputMex);

	OnOK();
}