// Source\Platform_CreateCharacterPage.cpp : implementation file
//

#include "Platform_CreateCharacterPage.h"
#include "ItemDetail.h"
#include "GlobalDef.h"
// Platform_CreateCharacter dialog

IMPLEMENT_DYNAMIC(Platform_CreateCharacter, PageInterface)

Platform_CreateCharacter::Platform_CreateCharacter()
	: PageInterface(Platform_CreateCharacter::IDD)
{
    SetType(CreateCharacterPage);
}

Platform_CreateCharacter::~Platform_CreateCharacter()
{
}

void Platform_CreateCharacter::DoDataExchange(CDataExchange* pDX)
{
	PageInterface::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_PLATFROM_CREATEROLE_LEVEL, Combo_Level);
    DDX_Control(pDX, IDC_COMBO_PLATFROM_CREATEROLE_SEX, Combo_Sex);
    DDX_Control(pDX, IDC_COMBO_PLATFROM_CREATEROLE_GUOJIA, Combo_Country);
    DDX_Control(pDX, IDC_COMBO_PLATFROM_CREATEROLE_ITEMID, Combo_GiftItemId);
    DDX_Control(pDX, IDC_COMBO_PLATFROM_CREATEROLE_PROFESSION, Combo_Profession);
    DDX_Text(pDX, IDC_ED_PLATFROM_CREATEROLE_NAME, RoleName);
    DDV_MaxChars(pDX, RoleName, 32);
    DDX_Text(pDX, IDC_ED_PLATFROM_CREATEROLE_ACCOUNTID, AccoundId);
}

BOOL Platform_CreateCharacter::OnInitDialog()
{
    if( !PageInterface::OnInitDialog() )
        return FALSE;

    int level = 1;
    for (;level<=70;++level)
    {
        char buf[8];
        sprintf_s(buf,sizeof(buf),"%d",level);
        Combo_Level.AddString(buf);
    }
    Combo_Level.SetWindowText("70");

    Combo_Sex.AddString("ÄÐ");
    Combo_Sex.AddString("Å®");
    Combo_Sex.SetCurSel(0);

    Combo_Country.AddString("ÖÐ¹ú");
    Combo_Country.SetCurSel(0);

    Combo_Profession.AddString("êª");
    Combo_Profession.AddString("½£");
    Combo_Profession.AddString("Ç¹");
    Combo_Profession.AddString("Îè");
    Combo_Profession.AddString("µ¶");
    Combo_Profession.SetCurSel(0);

    AccoundId = 0;

    for (int i = 0;i<GettheItemDetail().GetItemCount();++i)
    {
        CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID(i);
        if (NULL != pItem && (pItem->ucItemType != CItemDetail::ITEMTYPE_WEAPON
            && pItem->ucItemType != CItemDetail::ITEMTYPE_ARMOUR
            && pItem->ucItemType != CItemDetail::ITEMTYPE_SKILL
            && pItem->ucItemType != CItemDetail::ITEMTYPE_STATUS
            && pItem->ucItemType != CItemDetail::ITEMTYPE_ACTION
            && pItem->ucItemType != CItemDetail::ITEMTYPE_TASK
            && pItem->ucItemType != CItemDetail::ITEMTYPE_GUILD))
        {
            Combo_GiftItemId.AddString(pItem->GetItemName());
        }
    }

    CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID(GIFT_ID);
    if (NULL != pItem)
    {
        Combo_GiftItemId.SetWindowText(pItem->GetItemName()); 
    }
    else
    {
        Combo_GiftItemId.SetCurSel(0);
    }
    UpdateData(FALSE);
    return TRUE;
}

BEGIN_MESSAGE_MAP(Platform_CreateCharacter, PageInterface)
    ON_BN_CLICKED(IDC_BTN_SEND_CREATEROLE, &Platform_CreateCharacter::OnBnClickedBtnSendCreateRole)
END_MESSAGE_MAP()

// Platform_CreateCharacter message handlers
void Platform_CreateCharacter::OnBnClickedBtnSendCreateRole()
{
    UpdateData();
    if (/*!Bot||Bot->_accountId == 0*/AccoundId == 0 || RoleName.IsEmpty())
    {
        MessageBox("ÇëÊäÈëÕÊºÅºÍ½ÇÉ«Ãû","Warning");
        return;
    }

    CString ItemName;
    Combo_GiftItemId.GetWindowText(ItemName);
    unsigned short GiftItemID = ErrorUnsignedShortID;
    CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByName(ItemName);
    if (NULL != pItem)
    {
        GiftItemID = pItem->ustItemID;
    }
    
    if (ErrorUnsignedShortID == GiftItemID)
    {
        Bot->ReqGMCreateRole(AccoundId,Combo_Sex.GetCurSel(),Combo_Profession.GetCurSel()
            ,RoleName,Combo_Level.GetCurSel()+1,Combo_Country.GetCurSel());
    }
    else
    {
        Bot->ReqGMCreateRole(AccoundId,Combo_Sex.GetCurSel(),Combo_Profession.GetCurSel()
            ,RoleName,Combo_Level.GetCurSel()+1,Combo_Country.GetCurSel(),GiftItemID);
    }
}