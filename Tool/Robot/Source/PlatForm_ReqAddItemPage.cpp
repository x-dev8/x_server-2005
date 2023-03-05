// Source\PlatForm_ReqAddItem.cpp : implementation file
//

#include "PlatForm_ReqAddItemPage.h"
#include "ItemDetail.h"

// PlatForm_ReqAddItem dialog

IMPLEMENT_DYNAMIC(PlatForm_ReqAddItem, PageInterface)

PlatForm_ReqAddItem::PlatForm_ReqAddItem()
	: PageInterface(PlatForm_ReqAddItem::IDD)
{

}

PlatForm_ReqAddItem::~PlatForm_ReqAddItem()
{
}

void PlatForm_ReqAddItem::DoDataExchange(CDataExchange* pDX)
{
	PageInterface::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ED_PLATFORM_ADDITEM_SN, OrderFormID);
    DDX_Text(pDX, IDC_ED_PALTFORM_ADDITEM_ACCOUNT, AccountId);
    DDX_Text(pDX, IDC_ED_ITEMCOUNT, ItemCount);
    DDV_MinMaxShort(pDX,ItemCount,1,30);
    DDX_Control(pDX, IDC_COMBO_PLATFORM_ADDITEM, Combox_SelectItem);
}

BOOL PlatForm_ReqAddItem::OnInitDialog()
{
    if( !PageInterface::OnInitDialog())
        return FALSE;

    ItemCount = 1;
    AccountId = 0;
    OrderFormID = "";

    for (int i=0;i < GettheItemDetail().GetItemCount();++i)
    {
        CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID(i);
        if (NULL != pItem && (pItem->ucItemType != CItemDetail::ITEMTYPE_SKILL
            && pItem->ucItemType != CItemDetail::ITEMTYPE_STATUS
            && pItem->ucItemType != CItemDetail::ITEMTYPE_ACTION))
        {
            Combox_SelectItem.AddString(pItem->GetItemName());
        }
    }
    Combox_SelectItem.SetCurSel(0);

    UpdateData(FALSE);
    return TRUE;
}

void PlatForm_ReqAddItem::OnBnClickedBtnSendReqAddItem()
{
    UpdateData();
    if(OrderFormID.IsEmpty() || AccountId == 0)
    {
        MessageBox("账户Id 不能为0且订单号不能为空,请检查输入是否有误","warning");
        return;
    }

    if (NULL != Bot)
    {
        CString CurItemName;
        Combox_SelectItem.GetWindowText(CurItemName);
        CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByName(CurItemName);
        if (NULL == pItem)
        {
            MessageBox("没有找到道具，请检查选择的道具","Error");
            return;
        }
        Bot->ReqAddItem(OrderFormID.GetBuffer(),pItem->ustItemID,ItemCount,AccountId,false);
    }
}

BEGIN_MESSAGE_MAP(PlatForm_ReqAddItem, PageInterface)
    ON_BN_CLICKED(IDC_BTN_PLATFORM_REQADDITEM, &PlatForm_ReqAddItem::OnBnClickedBtnSendReqAddItem)
END_MESSAGE_MAP()


// PlatForm_ReqAddItem message handlers
