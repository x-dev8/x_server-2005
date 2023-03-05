// Source\Platform_AddPointsPage.cpp : implementation file
//

#include "stdafx.h"
#include "Platform_AddPointsPage.h"


// Platform_AddPoints dialog

IMPLEMENT_DYNAMIC(Platform_AddPoints, CPropertyPage)

Platform_AddPoints::Platform_AddPoints()
	: PageInterface(Platform_AddPoints::IDD)
    , typesn(_T(""))
    , guid(0)
    , signstr(_T(""))
    , remark(_T(""))
    , paytime(0)
    , gssid(0)
    , discount(0)
    , netincome(0)
    , channel(0)
    , addamount(0)
    , points(0)
{
    SetType(AddPointsPage);
}

Platform_AddPoints::~Platform_AddPoints()
{

}

void Platform_AddPoints::DoDataExchange(CDataExchange* pDX)
{
    PageInterface::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ED_TYPESN, typesn);
    DDV_MaxChars(pDX, typesn, 31);
    DDX_Text(pDX, IDC_ED_GUID, guid);
    DDX_Text(pDX, IDC_ED_SIGNSTR, signstr);
    DDV_MaxChars(pDX, signstr, 32);
    DDX_Text(pDX, IDC_ED_REMARK, remark);
    DDV_MaxChars(pDX, remark, 32);
    DDX_Text(pDX, IDC_ED_PAYTIME, paytime);
    DDX_Text(pDX, IDC_ED_GSSID, gssid);
    DDX_Text(pDX, IDC_ED_DISCOUNT, discount);
    DDV_MinMaxInt(pDX, discount, 0, USHRT_MAX);
    DDX_Text(pDX, IDC_ED_NETINCOME, netincome);
    DDX_Text(pDX, IDC_ED_CHANNEL, channel);
    DDX_Control(pDX, IDC_COMBO_ADDPOINT_TYPEID, comboTypeId);
    DDX_Text(pDX, IDC_ED_ADDAMOUNT, addamount);
    DDX_Text(pDX, IDC_ED_POINTS, points);
}

BOOL Platform_AddPoints::OnInitDialog()
{
    if (!PageInterface::OnInitDialog())
        return FALSE;

    comboTypeId.AddString("paycard");
    comboTypeId.AddString("paynet");
    comboTypeId.AddString("esales");

    comboTypeId.SetCurSel(0);

    discount = 0;

    UpdateData(FALSE);
    return TRUE;
}

BEGIN_MESSAGE_MAP(Platform_AddPoints, CPropertyPage)
    ON_BN_CLICKED(IDC_BTN_SENDADDPOINT, &Platform_AddPoints::OnBnClickedBtnSendaddpoint)
END_MESSAGE_MAP()


// Platform_AddPoints message handlers

void Platform_AddPoints::OnBnClickedBtnSendaddpoint()
{
    // TODO: Add your control notification handler code here
    UpdateData();
    if ( typesn.IsEmpty() )
        return;

    if (NULL != Bot)
    {
        Bot->ReqPFAddPoints(typesn,addamount,discount,guid,gssid
            ,comboTypeId.GetCurSel(),points,netincome,paytime,channel,remark,signstr);
        MessageBox("·¢ËÍÍê±Ï!");
    }
}
