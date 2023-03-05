// source\Platform_ChangeMapRatePage.cpp : implementation file
//
#include "Platform_ChangeMapRatePage.h"
#include "MapConfig.h"

// Platform_ChangeMapRate dialog

IMPLEMENT_DYNAMIC(Platform_ChangeMapRate, PageInterface)

Platform_ChangeMapRate::Platform_ChangeMapRate()
	: PageInterface(Platform_ChangeMapRate::IDD)
    , Ed_FLoat_Rate(_T(""))
    , Slider_Float_Rate(0)
{
    SetType(ChangeMapRatePage);
}

Platform_ChangeMapRate::~Platform_ChangeMapRate()
{
}

void Platform_ChangeMapRate::DoDataExchange(CDataExchange* pDX)
{
    DDX_Text(pDX, IDC_ED_FLOAT_RATE, Ed_FLoat_Rate);
    DDX_Slider(pDX, IDC_SLIDER_FLOAT_RATE, Slider_Float_Rate);
    DDV_MinMaxInt(pDX, Slider_Float_Rate, 0, 100);
    DDX_Control(pDX, IDC_COMBO_CHANGEMAPID, Combo_ChangeMapId);
    PageInterface::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Platform_ChangeMapRate, PageInterface)
    ON_EN_CHANGE(IDC_ED_FLOAT_RATE, &Platform_ChangeMapRate::OnEnChangeEdFloatRate)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_FLOAT_RATE, &Platform_ChangeMapRate::OnNMReleasedcaptureSliderFloatRate)
    ON_BN_CLICKED(IDC_BTN_CHANG_RATE, &Platform_ChangeMapRate::OnBnClickedBtnChangRate)
END_MESSAGE_MAP()

BOOL Platform_ChangeMapRate::OnInitDialog()
{
   if (!PageInterface::OnInitDialog())
       return FALSE;

    Ed_FLoat_Rate = "0.0";
    CWnd * pWND = GetDlgItem(IDC_SLIDER_FLOAT_RATE);
    if (NULL != pWND)
    {
        CSliderCtrl* pW = (CSliderCtrl*)pWND;
        pW->SetRange(0,100,TRUE);
    }
    
//     if (Combo_ChangeMapId.GetSafeHwnd() == NULL)
//     {
//         //45,54,98,93,CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL | WS_TABSTOP
//         RECT rect;
//         rect.bottom = 45;
//         rect.left = 54;
//         rect.right = 98;
//         rect.top = 93;
//         if (!Combo_ChangeMapId.Create(CBS_DROPDOWNLIST | WS_VSCROLL ,rect,this,IDC_COMBO_CHANGEMAPID))
//         {
//             return FALSE;
//         }
//     }

//     CWnd * pWND_Combo = GetDlgItem(IDC_COMBO_CHANGEMAPID);
//     if (NULL != pWND_Combo)
//     {
//         CComboBox* pBox = (CComboBox*)pWND_Combo;
//         pBox->ModifyStyle( 0,CBS_DROPDOWN|CBS_DROPDOWNLIST|CBS_SIMPLE);
//         pBox->ModifyStyle( CBS_DROPDOWN,0);
//         for (int i=0;i<theMapConfig.MapDataCount();++i)
//         {
//             MapConfig::MapData *pMap = theMapConfig.GetMapDataByIndex(i);
//             if (NULL != pMap && NULL != pWND_Combo && !pMap->MapName.empty()&&pMap->MapName.compare("²âÊÔµØÍ¼") != 0)
//             {
//                 pBox->AddString(pMap->MapName.c_str());
//                 //::SendMessage(pWND_Combo->GetSafeHwnd(), CB_ADDSTRING, 0, (LPARAM)pMap->MapName.c_str());
//             }
//         }
//         pBox->SetCurSel(0);
//         //::SendMessage(pWND_Combo->GetSafeHwnd(), CB_SETCURSEL, 0, 0);
//         pBox->UpdateData();
//     }
    for (int i=0;i<theMapConfig.MapDataCount();++i)
    {
        MapConfig::MapData *pMap = theMapConfig.GetMapDataByIndex(i);
        if (NULL != pMap && !pMap->MapName.empty()&&pMap->MapName.compare("²âÊÔµØÍ¼") != 0)
        {
            Combo_ChangeMapId.AddString(pMap->MapName.c_str());
            //::SendMessage(pWND_Combo->GetSafeHwnd(), CB_ADDSTRING, 0, (LPARAM)pMap->MapName.c_str());
        }
    }
    Combo_ChangeMapId.SetCurSel(0);
    
    UpdateData(FALSE);
    return TRUE;
}
// Platform_ChangeMapRate message handlers

void Platform_ChangeMapRate::OnEnChangeEdFloatRate()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the PageInterface::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
    UpdateData();
    float TempValue = atof(Ed_FLoat_Rate.GetBuffer());
    Slider_Float_Rate = (int)TempValue;
    UpdateData(FALSE);
}

void Platform_ChangeMapRate::OnNMReleasedcaptureSliderFloatRate(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: Add your control notification handler code here
    UpdateData();
    float TempValue = 0.0;
    if (Slider_Float_Rate != 0)
    {
        TempValue = (float)Slider_Float_Rate;
    }
    char Buf[20];
    sprintf_s(Buf,sizeof(Buf),"%.0f",TempValue);
    Ed_FLoat_Rate = Buf;
    UpdateData(FALSE);
    *pResult = 0;
}

void Platform_ChangeMapRate::OnBnClickedBtnChangRate()
{
    // TODO: Add your control notification handler code here
    UpdateData();
//    OperationMsg Msg;
//    Msg.TestOperation = OperationMsg::EPO_CHANGEMAPEXPRATE;
   
    CString MapName;
    Combo_ChangeMapId.GetWindowText(MapName);
    MapConfig::MapData *pMap = theMapConfig.GetMapDataByName(MapName.GetBuffer());
    if (NULL == pMap)
    {
        return;
    }
    if (NULL != Bot)
    {
        Bot->ReqChangeMapEXPRate(pMap->Id,(float)Slider_Float_Rate / 10);
        MessageBox("·¢ËÍÍê±Ï!");
    }
//     Msg.nParm[0] = pMap->Id;
//     if (Slider_Float_Rate != 0)
//         Msg.fParm = (float)Slider_Float_Rate / 10;
//     else
//         Msg.fParm = 0;
//     PushPlatformWork(&Msg);
}
