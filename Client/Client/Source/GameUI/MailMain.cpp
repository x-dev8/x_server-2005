/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\MailMain.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "MailMain.h"
#include "MailReceive.h"

#include "PlayerRole.h"
#include "Pack.h"
#include "Create.h"
#include "NetworkInput.h"
#include "ScreenInfoManager.h"
#include "color_config.h"
#include "chatcheck.h"
#include "PlayerMgr.h"
#include "GameMain.h"
#include "Player.h"
#include "Meui/ExpressionManager.h"
#include "Pack.h"
#include "MailReceive2.h"
#include "Pet.h"
#include "XmlStringLanguage.h"
#include "ChatInfoBox.h"
#include "Common.h"
#include "PackItemEnableManager.h"

#pragma warning(disable:4482)

extern HWND g_hWnd;
extern CHeroGame  theHeroGame;

CUI_ID_FRAME_MailMain s_CUI_ID_FRAME_MailMain;
MAP_FRAME_RUN( s_CUI_ID_FRAME_MailMain, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_MailMain, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MailMain, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MailMain, ID_BUTTON_HelpOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_MailMain, ID_CHECKBOX_SendMailOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_MailMain, ID_CHECKBOX_ReceiveMailOnCheckBoxCheck )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_MailMain, ID_EDIT_MailTitleOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_MailMain, ID_EDIT_CopyTargetOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_MailMain, ID_EDIT_MailContentOnEditEnter )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_MailMain, ID_LISTIMG_MailItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_MailMain, ID_LISTIMG_MailItemOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MailMain, ID_LISTIMG_MailItemOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_MailMain, ID_LISTIMG_MailItemOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MailMain, ID_BUTTON_ResetOnButtonClick )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_MailMain, ID_COMBOBOX_SendTargetOnComboBoxChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MailMain, ID_BUTTON_SendOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_MailMain, ID_EDIT_JinOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_MailMain, ID_EDIT_YingOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_MailMain, ID_EDIT_TongOnEditEnter )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_MailMain, ID_COMBOBOX_CopyTargetOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_MailMain, ID_COMBOBOX_MailTitleOnComboBoxChange )
CUI_ID_FRAME_MailMain::CUI_ID_FRAME_MailMain()
{
	// Member
	ResetMembers();

    m_bagType = -1;  //用于存放背包类型
    m_nIndex  = -1;
	m_LogID = 0;
}

void CUI_ID_FRAME_MailMain::ResetMembers()
{
	m_pID_FRAME_MailMain = NULL;
	m_pID_PICTURE_Title = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Help = NULL;
	m_pID_PICTURE_BackGround = NULL;
	m_pID_CHECKBOX_SendMail = NULL;
	m_pID_CHECKBOX_ReceiveMail = NULL;
	m_pID_TEXT_SendTarget = NULL;
	m_pID_TEXT_CopyTarget = NULL;
	m_pID_TEXT_MailTitle = NULL;
	//m_pID_PICTURE_SendTarget = NULL;
	m_pID_PICTURE_MailTitle = NULL;
	m_pID_EDIT_MailTitle = NULL;
	m_pID_PICTURE_CopyTarget = NULL;
	m_pID_EDIT_CopyTarget = NULL;
	m_pID_PICTURE_MailContent = NULL;
	m_pID_EDIT_MailContent = NULL;
	m_pID_LISTIMG_MailItem = NULL;
	m_pID_TEXT_Cost = NULL;
	m_pID_BUTTON_Reset = NULL;
	m_pID_TEXT_MailItem = NULL;
	m_pID_COMBOBOX_SendTarget = NULL;
	m_pID_BUTTON_Send = NULL;
	m_pID_PICTURE_Jin = NULL;
	m_pID_EDIT_Jin = NULL;
	m_pID_PICTURE_Ying = NULL;
	m_pID_EDIT_Ying = NULL;
	m_pID_PICTURE_Tong = NULL;
	m_pID_EDIT_Tong = NULL;
	m_pID_TEXT_MailMoney = NULL;
	m_pID_PICTURE_JinPic = NULL;
	m_pID_PICTURE_YingPic = NULL;
	m_pID_PICTURE_TongPic = NULL;
	m_MailType = MailType_None;
	m_pID_COMBOBOX_CopyTarget = NULL;
	m_pID_COMBOBOX_MailTitle = NULL;
	m_pID_EDIT_SendTarget = NULL;
	m_LogID = 0;
}

// Frame
bool CUI_ID_FRAME_MailMain::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_MailMain::OnFrameRender()
{
//     CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
//     if (!pMe )
//         return true;
// 
//     D3DXVECTOR3 vPos;
//     pMe->GetPos( &vPos.x, &vPos.y, &vPos.z );
//     if(IsOverDistance(vPos))
//         SetVisable(false);

	return true;
}
// Button
bool CUI_ID_FRAME_MailMain::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_MailMain)
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_MailMain::ID_BUTTON_HelpOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_MailMain)
		return false;
	return true;
}
// CheckBox
void CUI_ID_FRAME_MailMain::ID_CHECKBOX_SendMailOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_MailMain)
		return;

     //ToggleUI(MailType_Send);
}
// CheckBox
void CUI_ID_FRAME_MailMain::ID_CHECKBOX_ReceiveMailOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_MailMain)
		return;

      ToggleUI(MailType_Recieve);
}
// Edit
void CUI_ID_FRAME_MailMain::ID_EDIT_MailTitleOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_MailMain)
		return;
}
// Edit
void CUI_ID_FRAME_MailMain::ID_EDIT_CopyTargetOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_MailMain)
		return;
    OutputDebugString("xx");
}
// Edit
void CUI_ID_FRAME_MailMain::ID_EDIT_MailContentOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_MailMain)
		return;
}
// ListImg / ListEx
bool CUI_ID_FRAME_MailMain::ID_LISTIMG_MailItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!m_pID_FRAME_MailMain)
		return false;
    if(!pItemDrag )
        return false;

	if( !m_pID_FRAME_MailMain )
		return false;

    if(m_MailType != MailType_Send)
        return false;

    if(s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag,pSender))
    {
        if(!CheckValidItem(pItemDrag,BT_NormalItemBag))
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Receive, theXmlString.GetString(eText_MailItemNoSender) );
            return false;
        }

        int nIndex = m_nIndex;
        int nBagType = m_bagType;

        m_bagType = BT_NormalItemBag;


        m_nIndex = s_CUI_ID_FRAME_PACK.GetPackImageIndex(pItemDrag);
        if(m_nIndex == -1)
            return false;

        RefreshEnable(nBagType,nIndex,m_bagType,m_nIndex);
    }
    else if(s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag,pSender))
    {
        if(!CheckValidItem(pItemDrag,BT_MaterialBag))
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Receive, theXmlString.GetString(eText_MailItemNoSender) );
            return false;
        }

        int nIndex = m_nIndex;
        int nBagType = m_bagType;

        m_bagType = BT_MaterialBag;


        m_nIndex = s_CUI_ID_FRAME_PACK.GetMaterialImageIndex(pItemDrag);
        if(m_nIndex == -1)
            return false;

        RefreshEnable(nBagType,nIndex,m_bagType,m_nIndex);
    }
    else if(s_CUI_ID_FRAME_Pet.IsListImageByBagType(pSender))
    {
		return false; //先不让交易 lrt
        SMountItem *pMountItem = thePlayerRole.GetActivedMount();
        if(pMountItem&&pMountItem->baseInfo.guid == pItemDrag->m_pkIconInfo->GetOnlyId())
        {
           CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Receive, theXmlString.GetString(eText_MailItemNoSender) );
            return false;
        }

        int nIndex = m_nIndex;
        int nBagType = m_bagType;

        m_bagType = BT_MountBag;

        m_nIndex = s_CUI_ID_FRAME_Pet.GetMountIndexByGuid(pItemDrag->m_pkIconInfo->GetOnlyId() );
        if(m_nIndex == -1)
            return false;

        RefreshEnable(nBagType,nIndex,m_bagType,m_nIndex);
    }
    else
       return false;

    //设置图标
    m_pID_LISTIMG_MailItem->Clear();
    m_pID_LISTIMG_MailItem->SetItem(pItemDrag);
    m_pID_LISTIMG_MailItem->GetItemByIndex(0)->m_eEnable         = eIcon_Enable;

    theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);

    RefreshMailMoney();
	return false;
}
bool CUI_ID_FRAME_MailMain::ID_LISTIMG_MailItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_MailMain)
		return false;
	return false;
}
bool CUI_ID_FRAME_MailMain::ID_LISTIMG_MailItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_MailMain)
		return false;
	return false;
}
bool CUI_ID_FRAME_MailMain::ID_LISTIMG_MailItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_MailMain)
		return false;
    ClearImage(pItem);
    RefreshMailMoney();
	return false;
}
// Button
bool CUI_ID_FRAME_MailMain::ID_BUTTON_ResetOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_MailMain)
		return false;
    ClearControl();
    RefreshMailMoney();
	return true;
}
// ComboBox
void CUI_ID_FRAME_MailMain::ID_COMBOBOX_SendTargetOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_MailMain)
		return;
	
	std::string strCopyer = m_pID_COMBOBOX_SendTarget->GetEditInput().GetText();
	m_pID_EDIT_SendTarget->SetText(strCopyer.c_str());
    RefreshMailMoney();
}
// Button
bool SendMailEx(char BOK,void* data)
{
	if (BOK)
	{
		bool bSuccess = s_CUI_ID_FRAME_MailMain.SendMail();
		if(bSuccess)
		{
			s_CUI_ID_FRAME_MailMain.ClearMoney();
			s_CUI_ID_FRAME_MailMain.ClearItem();
			s_CUI_ID_FRAME_MailMain.m_bagType = -1;
		}
	}
  return true;
}

bool CUI_ID_FRAME_MailMain::ID_BUTTON_SendOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_MailMain)
		return false;
   
	//有抄送人 并且 有附件
	ControlIconDrag::S_ListImg *pImg = m_pID_LISTIMG_MailItem->GetItemByIndex(0);
	if (pImg && !pImg->IsNull() && strlen(m_pID_EDIT_CopyTarget->GetText())> 0   )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eClient_SendMailInfo), 
			                            "", CUI_ID_FRAME_MessageBox::eTypeYesNo, false,SendMailEx);
										
	}else
	{

		bool bSuccess = SendMail();
		if(bSuccess)
		{
			ClearMoney();
			ClearItem();
			m_bagType = -1;
		}
	}
	
		

	
								 
	return true;
}
// Edit
void CUI_ID_FRAME_MailMain::ID_EDIT_JinOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_MailMain)
		return;
}
// Edit
void CUI_ID_FRAME_MailMain::ID_EDIT_YingOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_MailMain)
		return;
}
// Edit
void CUI_ID_FRAME_MailMain::ID_EDIT_TongOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_MailMain)
		return;
}
void CUI_ID_FRAME_MailMain::ID_COMBOBOX_CopyTargetOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_MailMain)
		return;
    RefreshCopySender();
}
void CUI_ID_FRAME_MailMain::ID_COMBOBOX_MailTitleOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_MailMain)
		return;
	std::string strCopyer = m_pID_COMBOBOX_MailTitle->GetEditInput().GetText();
	m_pID_EDIT_MailTitle->SetText(strCopyer.c_str());
}

// 装载UI
bool CUI_ID_FRAME_MailMain::_LoadUI()
{
    s_CUI_ID_FRAME_MailReceive.LoadUI();
    s_CUI_ID_FRAME_MailReceive2.LoadUI();
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\MailMain.MEUI",false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\MailMain.MEUI]失败")
		return false;
	}

	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_MailMain::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_MailMain, s_CUI_ID_FRAME_MailMainOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_MailMain, s_CUI_ID_FRAME_MailMainOnFrameRender );
    theUiManager.OnButtonClick( ID_FRAME_MailMain, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_MailMainID_BUTTON_CLOSEOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MailMain, ID_BUTTON_Help, s_CUI_ID_FRAME_MailMainID_BUTTON_HelpOnButtonClick );
    theUiManager.OnCheckBoxCheck( ID_FRAME_MailMain, ID_CHECKBOX_SendMail, s_CUI_ID_FRAME_MailMainID_CHECKBOX_SendMailOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_MailMain, ID_CHECKBOX_ReceiveMail, s_CUI_ID_FRAME_MailMainID_CHECKBOX_ReceiveMailOnCheckBoxCheck );
    theUiManager.OnEditEnter( ID_FRAME_MailMain, ID_EDIT_MailTitle, s_CUI_ID_FRAME_MailMainID_EDIT_MailTitleOnEditEnter );
    theUiManager.OnEditEnter( ID_FRAME_MailMain, ID_EDIT_CopyTarget, s_CUI_ID_FRAME_MailMainID_EDIT_CopyTargetOnEditEnter );
    theUiManager.OnEditEnter( ID_FRAME_MailMain, ID_EDIT_MailContent, s_CUI_ID_FRAME_MailMainID_EDIT_MailContentOnEditEnter );
    theUiManager.OnIconDragOn( ID_FRAME_MailMain, ID_LISTIMG_MailItem, s_CUI_ID_FRAME_MailMainID_LISTIMG_MailItemOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_MailMain, ID_LISTIMG_MailItem, s_CUI_ID_FRAME_MailMainID_LISTIMG_MailItemOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_MailMain, ID_LISTIMG_MailItem, s_CUI_ID_FRAME_MailMainID_LISTIMG_MailItemOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_MailMain, ID_LISTIMG_MailItem, s_CUI_ID_FRAME_MailMainID_LISTIMG_MailItemOnIconRButtonUp );
    theUiManager.OnButtonClick( ID_FRAME_MailMain, ID_BUTTON_Reset, s_CUI_ID_FRAME_MailMainID_BUTTON_ResetOnButtonClick );
    theUiManager.OnComboBoxChange( ID_FRAME_MailMain, ID_COMBOBOX_SendTarget, s_CUI_ID_FRAME_MailMainID_COMBOBOX_SendTargetOnComboBoxChange );
    theUiManager.OnButtonClick( ID_FRAME_MailMain, ID_BUTTON_Send, s_CUI_ID_FRAME_MailMainID_BUTTON_SendOnButtonClick );
    theUiManager.OnEditEnter( ID_FRAME_MailMain, ID_EDIT_Jin, s_CUI_ID_FRAME_MailMainID_EDIT_JinOnEditEnter );
    theUiManager.OnEditEnter( ID_FRAME_MailMain, ID_EDIT_Ying, s_CUI_ID_FRAME_MailMainID_EDIT_YingOnEditEnter );
    theUiManager.OnEditEnter( ID_FRAME_MailMain, ID_EDIT_Tong, s_CUI_ID_FRAME_MailMainID_EDIT_TongOnEditEnter );
    theUiManager.OnComboBoxChange( ID_FRAME_MailMain, ID_COMBOBOX_CopyTarget, s_CUI_ID_FRAME_MailMainID_COMBOBOX_CopyTargetOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_MailMain, ID_COMBOBOX_MailTitle, s_CUI_ID_FRAME_MailMainID_COMBOBOX_MailTitleOnComboBoxChange );
	


    m_pID_FRAME_MailMain = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_MailMain );
	m_pID_PICTURE_Title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MailMain, ID_PICTURE_Title );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_MailMain, ID_BUTTON_CLOSE );
	m_pID_BUTTON_Help = (ControlButton*)theUiManager.FindControl( ID_FRAME_MailMain, ID_BUTTON_Help );
	m_pID_PICTURE_BackGround = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MailMain, ID_PICTURE_BackGround );
	m_pID_CHECKBOX_SendMail = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MailMain, ID_CHECKBOX_SendMail );
	m_pID_CHECKBOX_ReceiveMail = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MailMain, ID_CHECKBOX_ReceiveMail );
	m_pID_TEXT_SendTarget = (ControlText*)theUiManager.FindControl( ID_FRAME_MailMain, ID_TEXT_SendTarget );
	m_pID_TEXT_CopyTarget = (ControlText*)theUiManager.FindControl( ID_FRAME_MailMain, ID_TEXT_CopyTarget );
	m_pID_TEXT_MailTitle = (ControlText*)theUiManager.FindControl( ID_FRAME_MailMain, ID_TEXT_MailTitle );
	//m_pID_PICTURE_SendTarget = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MailMain, ID_PICTURE_SendTarget );
	m_pID_PICTURE_MailTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MailMain, ID_PICTURE_MailTitle );
	m_pID_EDIT_MailTitle = (ControlEdit*)theUiManager.FindControl( ID_FRAME_MailMain, ID_EDIT_MailTitle );
	m_pID_PICTURE_CopyTarget = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MailMain, ID_PICTURE_CopyTarget );
	m_pID_EDIT_CopyTarget = (ControlEdit*)theUiManager.FindControl( ID_FRAME_MailMain, ID_EDIT_CopyTarget );
	m_pID_PICTURE_MailContent = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MailMain, ID_PICTURE_MailContent );
	m_pID_EDIT_MailContent = (ControlEdit*)theUiManager.FindControl( ID_FRAME_MailMain, ID_EDIT_MailContent );
	m_pID_LISTIMG_MailItem = (ControlListImage*)theUiManager.FindControl( ID_FRAME_MailMain, ID_LISTIMG_MailItem );
	m_pID_TEXT_Cost = (ControlText*)theUiManager.FindControl( ID_FRAME_MailMain, ID_TEXT_Cost );
	m_pID_BUTTON_Reset = (ControlButton*)theUiManager.FindControl( ID_FRAME_MailMain, ID_BUTTON_Reset );
	m_pID_TEXT_MailItem = (ControlText*)theUiManager.FindControl( ID_FRAME_MailMain, ID_TEXT_MailItem );
	m_pID_COMBOBOX_SendTarget = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_MailMain, ID_COMBOBOX_SendTarget );
	m_pID_BUTTON_Send = (ControlButton*)theUiManager.FindControl( ID_FRAME_MailMain, ID_BUTTON_Send );
	m_pID_PICTURE_Jin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MailMain, ID_PICTURE_Jin );
	m_pID_EDIT_Jin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_MailMain, ID_EDIT_Jin );
	m_pID_PICTURE_Ying = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MailMain, ID_PICTURE_Ying );
	m_pID_EDIT_Ying = (ControlEdit*)theUiManager.FindControl( ID_FRAME_MailMain, ID_EDIT_Ying );
	m_pID_PICTURE_Tong = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MailMain, ID_PICTURE_Tong );
	m_pID_EDIT_Tong = (ControlEdit*)theUiManager.FindControl( ID_FRAME_MailMain, ID_EDIT_Tong );
	m_pID_TEXT_MailMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_MailMain, ID_TEXT_MailMoney );
	m_pID_PICTURE_JinPic = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MailMain, ID_PICTURE_JinPic );
	m_pID_PICTURE_YingPic = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MailMain, ID_PICTURE_YingPic );
	m_pID_PICTURE_TongPic = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MailMain, ID_PICTURE_TongPic );
	m_pID_COMBOBOX_CopyTarget = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_MailMain, ID_COMBOBOX_CopyTarget );
	m_pID_COMBOBOX_MailTitle = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_MailMain, ID_COMBOBOX_MailTitle );
	m_pID_EDIT_SendTarget = (ControlEdit*)theUiManager.FindControl( ID_FRAME_MailMain, ID_EDIT_SendTarget );

    assert( m_pID_FRAME_MailMain );
	assert( m_pID_PICTURE_Title );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_Help );
	assert( m_pID_PICTURE_BackGround );
	assert( m_pID_CHECKBOX_SendMail );
	assert( m_pID_CHECKBOX_ReceiveMail );
	assert( m_pID_TEXT_SendTarget );
	assert( m_pID_TEXT_CopyTarget );
	assert( m_pID_TEXT_MailTitle );
	//assert( m_pID_PICTURE_SendTarget );
	assert( m_pID_PICTURE_MailTitle );
	assert( m_pID_EDIT_MailTitle );
	assert( m_pID_PICTURE_CopyTarget );
	assert( m_pID_EDIT_CopyTarget );
	assert( m_pID_PICTURE_MailContent );
	assert( m_pID_EDIT_MailContent );
	assert( m_pID_LISTIMG_MailItem );
	assert( m_pID_TEXT_Cost );
	assert( m_pID_BUTTON_Reset );
	assert( m_pID_TEXT_MailItem );
	assert( m_pID_COMBOBOX_SendTarget );
	assert( m_pID_BUTTON_Send );
	assert( m_pID_PICTURE_Jin );
	assert( m_pID_EDIT_Jin );
	assert( m_pID_PICTURE_Ying );
	assert( m_pID_EDIT_Ying );
	assert( m_pID_PICTURE_Tong );
	assert( m_pID_EDIT_Tong );
	assert( m_pID_TEXT_MailMoney );
	assert( m_pID_PICTURE_JinPic );
	assert( m_pID_PICTURE_YingPic );
	assert( m_pID_PICTURE_TongPic );
	assert( m_pID_COMBOBOX_CopyTarget );
	assert( m_pID_COMBOBOX_MailTitle );
	assert( m_pID_EDIT_SendTarget );
//     if(s_CUI_ID_FRAME_MailReceive.GetFrame())
//         s_CUI_ID_FRAME_MailReceive.GetFrame()->SetFather(m_pID_FRAME_MailMain);
// 
//     if(s_CUI_ID_FRAME_MailReceive2.m_pID_FRAME_MailReceive2)
//         s_CUI_ID_FRAME_MailReceive2.m_pID_FRAME_MailReceive2->SetFather(m_pID_FRAME_MailMain);


    SetVisable(false);
	
	for (int i = 0; i < MAX_OLD_TITLE_COUNT; ++i)
	{
		m_strOldTitle[i] = "";
	}
    m_TypeRadioGroup.Clear();
    m_TypeRadioGroup.AddRadio(m_pID_CHECKBOX_SendMail);
    m_TypeRadioGroup.AddRadio(m_pID_CHECKBOX_ReceiveMail);


    m_TypeGroup.Clear();
    m_TypeGroup.AddControl(m_pID_TEXT_SendTarget);
    m_TypeGroup.AddControl(m_pID_TEXT_CopyTarget);
    m_TypeGroup.AddControl(m_pID_TEXT_MailTitle);
   // m_TypeGroup.AddControl(m_pID_PICTURE_SendTarget);
    m_TypeGroup.AddControl(m_pID_PICTURE_MailTitle);
    m_TypeGroup.AddControl(m_pID_EDIT_MailTitle);
    m_TypeGroup.AddControl(m_pID_PICTURE_CopyTarget);
    m_TypeGroup.AddControl(m_pID_EDIT_CopyTarget);
    m_TypeGroup.AddControl(m_pID_PICTURE_MailContent);
    m_TypeGroup.AddControl(m_pID_EDIT_MailContent);
    m_TypeGroup.AddControl(m_pID_LISTIMG_MailItem);
    m_TypeGroup.AddControl(m_pID_TEXT_Cost);
    m_TypeGroup.AddControl(m_pID_BUTTON_Reset);
    m_TypeGroup.AddControl(m_pID_TEXT_MailItem);
    m_TypeGroup.AddControl(m_pID_COMBOBOX_SendTarget);
    m_TypeGroup.AddControl(m_pID_BUTTON_Send);
    m_TypeGroup.AddControl(m_pID_PICTURE_Jin);
    m_TypeGroup.AddControl(m_pID_EDIT_Jin);
    m_TypeGroup.AddControl(m_pID_PICTURE_Ying);
    m_TypeGroup.AddControl(m_pID_EDIT_Ying);
    m_TypeGroup.AddControl(m_pID_PICTURE_Tong);
    m_TypeGroup.AddControl(m_pID_EDIT_Tong);
    m_TypeGroup.AddControl(m_pID_TEXT_MailMoney);
    m_TypeGroup.AddControl(m_pID_PICTURE_JinPic);
    m_TypeGroup.AddControl(m_pID_PICTURE_YingPic);
    m_TypeGroup.AddControl(m_pID_PICTURE_TongPic);
    m_TypeGroup.AddControl(m_pID_COMBOBOX_CopyTarget);
	m_TypeGroup.AddControl(m_pID_COMBOBOX_MailTitle);
	m_TypeGroup.AddControl(m_pID_EDIT_SendTarget);

    m_TypeGroup.SetVisible(false);



    m_pID_EDIT_Jin->SetIsNumber(true);
    m_pID_EDIT_Jin->SetNumberLimit(true,0,200);

    m_pID_EDIT_Ying->SetIsNumber(true);
    m_pID_EDIT_Ying->SetNumberLimit(true,0,99);

    m_pID_EDIT_Tong->SetIsNumber(true);
    m_pID_EDIT_Tong->SetNumberLimit(true,0,99);
	

    ClearControl();

    if( !s_CUI_ID_FRAME_CREATE.GetImeInstance() )
        s_CUI_ID_FRAME_CREATE.SetImeInstance( ImmGetContext( g_hWnd ) );

    ImmReleaseContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );

    m_pID_EDIT_MailTitle->SetMaxLength(EMail::EM_TileMaxCount/2 - 6);
    m_pID_EDIT_MailContent->SetMaxLength(EMail::EM_MailContentMax/2 - 2);

    m_pID_EDIT_CopyTarget->SetTextChangedFun( EditDataChange );
	m_pID_EDIT_SendTarget->SetTextChangedFun( EditDataChange );
    m_pID_EDIT_Jin->SetTextChangedFun( EditDataChangeEx );
    m_pID_EDIT_Ying->SetTextChangedFun( EditDataChangeEx );
    m_pID_EDIT_Tong->SetTextChangedFun( EditDataChangeEx );
	m_pID_COMBOBOX_CopyTarget->GetEditInput().SetVisable(false);
	m_pID_COMBOBOX_MailTitle->GetEditInput().SetVisable(false);
	m_pID_COMBOBOX_SendTarget->GetEditInput().SetVisable(false);
    m_pID_FRAME_MailMain->SetOnVisibleChangedFun(OnVisibleChange);

    
	return true;
}
void CUI_ID_FRAME_MailMain::EditDataChangeEx( OUT ControlObject* pSender, OUT const char *szData )
{
	//注意:这里检测只针对数字，就是不会出现有零出现在一个数字的前面，单独零除外
	int len = strlen( szData );
	if ( len > 1 )
	{
		int idx = 0;
		for ( ; idx < len -1; idx ++ )
		{
			if ( szData[idx] != '0' )
			{
				break;
			}
		}
		if ( idx > 0 )//表明前面有不必要的0
		{
			ControlEdit* edit = (ControlEdit*)pSender;
			edit->SetText( &szData[idx] );//下次条件就不成立，不会造成无限递归
		}


	}
	s_CUI_ID_FRAME_MailMain.RefreshMailMoney();
}

// 卸载UI
bool CUI_ID_FRAME_MailMain::_UnLoadUI()
{
    //s_CUI_ID_FRAME_MailReceive.UnLoadUI();
    //s_CUI_ID_FRAME_MailReceive2.UnLoadUI();
    m_pID_FRAME_MailMain = NULL;
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\MailMain.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_MailMain::_IsVisable()
{
    if(!m_pID_FRAME_MailMain)
        return false;
	return m_pID_FRAME_MailMain->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_MailMain::_SetVisable( const bool bVisable )
{
    if(m_pID_FRAME_MailMain)
    {
	    m_pID_FRAME_MailMain->SetVisable( bVisable );
        if(bVisable)
        {
            //ToggleUI(MailType_Recieve);
			ToggleUI(MailType_Send);
            theUiManager.ToTop(m_pID_FRAME_MailMain);
            ImmAssociateContext(g_hWnd,s_CUI_ID_FRAME_CREATE.GetImeInstance());
            SetButMailState(true);
        }
        else
        {
            RefreshEnable(m_bagType,m_nIndex,0,-1);
            ImmAssociateContext(g_hWnd,NULL);
        }
    }
}

void CUI_ID_FRAME_MailMain::ToggleUI(MailType type)
{
// 	if(!IsVisable())
// 		SetVisable(true);
	if(NULL == m_pID_FRAME_MailMain)
		return;

    switch(type)
    {
    case MailType_Recieve:
        {
            RefreshEnable(m_bagType,m_nIndex,0,-1);
            s_CUI_ID_FRAME_MailReceive.SetVisable(true);
            m_TypeGroup.SetVisible(false);
            m_TypeRadioGroup.ToggleRadio(m_pID_CHECKBOX_ReceiveMail);
        }
        break;
    case MailType_Send:
        {
            m_bagType = -1;
            m_nIndex = -1;
            s_CUI_ID_FRAME_MailReceive.SetVisable(false);
            m_TypeGroup.SetVisible(true);
            ClearMoney();
            ClearItem();
            m_TypeRadioGroup.ToggleRadio(m_pID_CHECKBOX_SendMail);
            InitData();

            s_CUI_ID_FRAME_PACK.SetVisable(true);
			ResetWindowPosition(m_pID_FRAME_MailMain,s_CUI_ID_FRAME_PACK.GetFrame());

            RefreshMailMoney();
        }
        break;
    default:
        assert(0&&"邮件类型错误");
        break;
    }
    m_MailType = type;
}

void CUI_ID_FRAME_MailMain::InitData()
{
    m_pID_COMBOBOX_SendTarget->GetListBox().Clear();
    m_pID_COMBOBOX_SendTarget->GetListBox().SetCurSelIndex(-1);

    m_pID_COMBOBOX_CopyTarget->GetListBox().Clear();
    m_pID_COMBOBOX_CopyTarget->GetListBox().SetCurSelIndex(-1);

	m_pID_COMBOBOX_MailTitle->GetListBox().Clear();
	m_pID_COMBOBOX_MailTitle->GetListBox().SetCurSelIndex(-1);

    std::map<int, RelationDataToClient> mapSet = thePlayerRole.GetMapFriendInfo();
    std::map<int, RelationDataToClient>::iterator it = mapSet.begin();
    std::map<int, RelationDataToClient>::iterator itEnd = mapSet.end();
    for (;it != itEnd;++it)
    {
		if(it->second.HaveRelation(RelationDefine::Friend))
        {
            ControlList::S_List stItem;
            stItem.SetData(it->second.GetName());
            m_pID_COMBOBOX_SendTarget->GetListBox().AddItem(&stItem);
            m_pID_COMBOBOX_CopyTarget->GetListBox().AddItem(&stItem);
        }
    }
	
	for (int i = 0; i < MAX_OLD_TITLE_COUNT; ++i)
	{
		if (m_strOldTitle[i] != "")
		{
			ControlList::S_List stItem;
			stItem.SetData(m_strOldTitle[i].c_str());
			m_pID_COMBOBOX_MailTitle->GetListBox().AddItem(&stItem);
		}
	}
	
    if(m_pID_COMBOBOX_SendTarget->GetListBox().GetListItemCnt() > 0)
    {
          m_pID_COMBOBOX_SendTarget->GetListBox().SetCurSelIndex(0);
          ControlList::S_List *pStList = m_pID_COMBOBOX_SendTarget->GetListBox().GetListItem(0);
          if(pStList)
              m_pID_COMBOBOX_SendTarget->GetEditInput().SetText(pStList->m_szText);
    }
}

bool CUI_ID_FRAME_MailMain::EditInputIsVisable()
{
    if(m_pID_EDIT_MailTitle&&theUiManager.GetFocus() == m_pID_EDIT_MailTitle)    
        return true;

    if(m_pID_EDIT_CopyTarget&&theUiManager.GetFocus() == m_pID_EDIT_CopyTarget)
        return true;

	if(m_pID_EDIT_SendTarget&&theUiManager.GetFocus() == m_pID_EDIT_SendTarget)
		return true;

    if(m_pID_EDIT_MailContent&&theUiManager.GetFocus() == m_pID_EDIT_MailContent)
        return true;
        
    return false;
}

void CUI_ID_FRAME_MailMain::ClearControl()
{
    m_pID_EDIT_MailTitle->SetText("");
    m_pID_EDIT_CopyTarget->SetText("");
    m_pID_EDIT_MailContent->SetText("");
	m_pID_EDIT_SendTarget->SetText("");
    ClearMoney();
    ClearItem();
}

void CUI_ID_FRAME_MailMain::ClearMoney()
{
    m_pID_EDIT_Jin->SetText(0);
    m_pID_EDIT_Ying->SetText(0);
    m_pID_EDIT_Tong->SetText(0);
}

void CUI_ID_FRAME_MailMain::ClearItem()
{
    m_pID_LISTIMG_MailItem->Clear();
    RefreshEnable(m_bagType,m_nIndex,0,-1);
	m_bagType = -1;
}
void CUI_ID_FRAME_MailMain::AddOldTitle(const char* strTitle)
{
	for (int i = MAX_OLD_TITLE_COUNT - 1; i > 0; i--)
	{
		m_strOldTitle[i] = m_strOldTitle[i - 1];
	}
	m_strOldTitle[0] = strTitle;
}

bool CUI_ID_FRAME_MailMain::SendMail()
{
	
    MsgSendMailReq msg;

    //获得标题
    if(!GetMailTitle(msg.title,sizeof(msg.title)/sizeof(int8) - 1))
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Receive, theXmlString.GetString(eText_MailTitleError) );
        return false;
    }

    //获得送信人地址
    if(!GetMailSender(msg.targets,EM_TargetMaxCount))
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Receive, theXmlString.GetString(eText_MailSenderError) );
        return false;
    }

    //正文
    if(!GetMailContext(msg.content,sizeof(msg.content)/sizeof(uint8) - 1))
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Receive, theXmlString.GetString(eText_MailContentError) );
        return false;
    }
    
    //设置钱
    if(!GetMoney(msg.money))
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Receive, theXmlString.GetString(eText_MailMoneyNoEnough) );
        return false;    //钱不够
    }

    //物品物件
    if(m_bagType != -1)
    {
        msg.bagType = m_bagType;
         if(!GetMailItem(msg.bagType,msg.bagIndex,msg.itemBigId))
         {
              CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Receive, theXmlString.GetString(eText_MailItemError) );
              return false;
         }
    }        
	AddOldTitle(msg.title);
    //时间戳
    msg.timeStamp = HQ_TimeGetTime();

    GettheNetworkInput().SendMsg(&msg);
	m_pID_COMBOBOX_MailTitle->GetListBox().Clear();
	m_pID_COMBOBOX_MailTitle->GetListBox().SetCurSelIndex(-1);
	
	for (int i = 0; i < MAX_OLD_TITLE_COUNT; ++i)
	{
		if (m_strOldTitle[i] != "")
		{
			ControlList::S_List stItem;
			stItem.SetData(m_strOldTitle[i].c_str());
			m_pID_COMBOBOX_MailTitle->GetListBox().AddItem(&stItem);
		}
	}
    SetButMailState(false);
    return true;
}

bool CUI_ID_FRAME_MailMain::CheckValidItem(ControlIconDrag::S_ListImg *pImg,int nBagType)
{
    if(!pImg)
        return false;

    //从背包中获得物品
    SCharItem cItem;
    __int64 nGuid = pImg->m_pkIconInfo->GetOnlyId();

    if(nBagType == BT_NormalItemBag)
    {
        if(!thePlayerRole.m_bag.GetItemByOnlyeID(nGuid,&cItem))
            return false;
    }
    else if(nBagType == BT_MaterialBag)
    {
        if(!thePlayerRole.m_bagMaterial.GetItemByOnlyeID(nGuid,&cItem))
            return false;
    }
    else
        return false;

    //---------------任务物品不能交易-----------------
    ItemDefine::SItemCommon *pItemDetail =  GettheItemDetail().GetItemByID(cItem.itembaseinfo.ustItemID);
    if(!pItemDetail)
        return false;

    if(pItemDetail->ucItemType == ItemDefine::ITEMTYPE_TASK)
        return false;

    if(!pItemDetail->bIsCanTrade)  //禁止交易,直接绑定在人身上
        return false;

   //装备后绑定,绑定物品不能交易
	if (/*pItemDetail->bIsCanBound&&*/cItem.IsBounded())
       return false;

   //锁定物品不能交易
   if(cItem.IsLock())
       return false;

    return true;
}

void CUI_ID_FRAME_MailMain::ClearImage(ControlIconDrag::S_ListImg *pImg)
{
    if(!pImg)
        return;

    RefreshEnable(m_bagType,m_nIndex,0,-1);
    
    int nIndex = m_pID_LISTIMG_MailItem->GetItemIndex(pImg);
    if(nIndex != -1)
    {
        m_pID_LISTIMG_MailItem->Clear();
        m_bagType = -1;
    }
}

void CUI_ID_FRAME_MailMain::TranslateMail(uint32 mailId)
{
	SMail* pMail = 0;
	for(int i =0;i<thePlayerRole.GetCurrentMailSize();++i)
	{
		pMail = thePlayerRole.ReadMail(i);
		if(!pMail)
			continue;
		if(pMail->id == mailId)
			break;
	}
	if (!pMail)
		return;

	ToggleUI(MailType_Send);

	ClearControl();
	InitData();

    if(thePlayerRole.IsHaveItemInMail(mailId) && pMail->state != SMail::EMS_HaveGetItem)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Receive, theXmlString.GetString(eText_MailHasItem) );
        return;
    }

    if(thePlayerRole.IsHaveMoneyInMail(mailId))
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Receive, theXmlString.GetString(eText_MailHasMoney) );
        return;
    }

    /*ToggleUI(MailType_Send);
    
    ClearControl();
    InitData();*/

    const char* pszText = theXmlString.GetString(eText_MailTranslate);
    std::string strTitle;
    strTitle.clear();
    strTitle = pszText;
    strTitle += thePlayerRole.GetMailTitle(mailId);

    m_pID_EDIT_MailTitle->SetText(strTitle.c_str());

    strTitle.clear();

    strTitle = thePlayerRole.GetMailContent(mailId);
    m_pID_EDIT_MailContent->SetText(strTitle.c_str());
}

void CUI_ID_FRAME_MailMain::ResponseMail(uint32 mailId)
{
    ToggleUI(MailType_Send);

    ClearControl();
    InitData();

    const char* pszText = theXmlString.GetString(eText_MailResponce);
    std::string strTitle;
    strTitle.clear();
    strTitle = pszText;
    strTitle += thePlayerRole.GetMailTitle(mailId);

    m_pID_EDIT_MailTitle->SetText(strTitle.c_str());
	//m_pID_TEXT_SendTarget->SetText(thePlayerRole.GetMailSender(mailId));
    m_pID_COMBOBOX_SendTarget->GetEditInput().SetText(thePlayerRole.GetMailSender(mailId));
	ID_COMBOBOX_SendTargetOnComboBoxChange(NULL,NULL);
}


bool CUI_ID_FRAME_MailMain::GetMailTitle(char* pszTitle, int nByte)
{
    if(!pszTitle)
        return false;

    //判断邮件标题
    const char *pszText = m_pID_EDIT_MailTitle->GetText();

    std::string strTrim(pszText);
    int nLen  = strTrim.length(); //判断长度
    if(nLen <= 0|| nLen >= nByte)
        return false;

    basic_string<char>::size_type nPos;
    nPos = strTrim.find_first_not_of(" ");
    if(nPos == basic_string<char>::npos)
        return false;

	bool bValue =  CChatCheck::getInstance()->CheckStringInLow(pszText);
	if(!bValue)
	{
		//s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_MailTitleError ));
		return false;
	}
	/*
	 * Author: 2012-10-12 17:09:01 liaojie
	 * Desc:   这个检测很坑爹
	 */
    /*bool bIsInLow = CChatCheck::getInstance()->CheckStringInLow(pszText);
    if (!bIsInLow)
        return	false;*/
	//char *pszText = const_cast<char*>(m_pID_TEXT_Message->GetText());
	std::string strChat = CChatCheck::getInstance()->CheckStringInLowMark( const_cast<char*>(pszText), '*');

    MeSprintf_s(pszTitle,nByte,"%s",strChat.c_str());

    return true;
}

bool CUI_ID_FRAME_MailMain::GetMailContext(char* pszContext,int nByte)
{
    //判断邮件正文
    const char* pszText = m_pID_EDIT_MailContent->GetText();
    if(strlen(pszText) >= nByte || strlen(pszText) <= 0)
        return false;

    bool bIsInLow = CChatCheck::getInstance()->CheckStringInLow(pszText);
    if (!bIsInLow)
        return	false;
    
    bool bValue =  CChatCheck::getInstance()->CheckStringInForbit(pszText);
    if(bValue)
        return false;

    MeSprintf_s(pszContext,nByte,"%s",pszText);
    return true;
}


bool CUI_ID_FRAME_MailMain::GetMoney(uint32 &uMoney,bool bNeed/* = false*/)
{
    //判断金币数量
    //金币寄送上线 200J
    std::string strJin,strYin,strTong;
    strJin.clear();
    strYin.clear();
    strTong.clear();

    strJin  = m_pID_EDIT_Jin->GetText();
    strYin  = m_pID_EDIT_Ying->GetText();
    strTong = m_pID_EDIT_Tong->GetText(); 

    int nMoneyJin = 0,nMoneyYin = 0,nMoneyTong = 0;
    if(strJin.empty())
    {
        nMoneyJin = 0;
    }
    else if(sscanf_s(strJin.c_str(),"%d",&nMoneyJin) != 1)
        return false;

    if(strYin.empty())
    {
        nMoneyYin = 0;
    }
    else if(sscanf_s(strYin.c_str(),"%d",&nMoneyYin) != 1)
        return false;

    if(strTong.empty())
    {
        nMoneyTong = 0;
    }
    else if(sscanf_s(strTong.c_str(),"%d",&nMoneyTong) != 1)
        return false;

    DWORD nMoneyTotal = thePlayerRole.GetMoneyFromGSC(nMoneyJin, nMoneyYin, nMoneyTong);
    if(bNeed)
    {
        uMoney = nMoneyTotal;
        return true;
    }

    if(nMoneyTotal > EM_MoneySendMax)  //超过200J不能发
        return false;

    //判断剩余数量是否能发送邮件
    DWORD dwMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
    if(dwMoney - nMoneyTotal < 10)  //邮资不够,每个邮资为10铜
        return false;

    uMoney = nMoneyTotal;
    return true;
}

bool CUI_ID_FRAME_MailMain::GetMailItem(uint8 bagType,uint16 &bagIndex,__int64 &itemBigId)
{
    if(m_pID_LISTIMG_MailItem->GetItemCnt() <= 0) //无附件
        return true;

    ControlIconDrag::S_ListImg *pImg = m_pID_LISTIMG_MailItem->GetItemByIndex(0);
    if(!pImg)
        return false;

    if(bagType == BT_NormalItemBag)
    {
        SCharItem sItem;

        if(!thePlayerRole.m_bag.GetItemByOnlyeID(pImg->m_pkIconInfo->GetOnlyId(),&sItem))
            return false;

        bagIndex = m_nIndex;

        itemBigId = sItem.GetItemGuid();
        return true;
    }
    else if(bagType == BT_MaterialBag)
    {
        SCharItem sItem;

        if (!thePlayerRole.m_bagMaterial.GetItemByOnlyeID(pImg->m_pkIconInfo->GetOnlyId(),&sItem))
            return false;

        bagIndex = m_nIndex;

        itemBigId = sItem.GetItemGuid();
        return true;
    }
    else if(bagType == BT_MountBag)
    {

        bagIndex = m_nIndex;

        itemBigId = pImg->m_pkIconInfo->GetOnlyId();

        return true;
    }
    
    assert(0&&"类型出错");
    return false;
}

bool CUI_ID_FRAME_MailMain::GetMailSender(SMail::SAddress *pAddress,int nCount)
{
    MeSprintf_s(pAddress[EM_FromIndex].addressName,sizeof(pAddress[EM_FromIndex].addressName)/sizeof(char) - 1,
        "%s",m_pID_EDIT_SendTarget->GetText());

    pAddress[EM_FromIndex].charDbId = thePlayerRole.GetdbID(pAddress[EM_FromIndex].addressName);

    std::string strCopySender = m_pID_EDIT_CopyTarget->GetText();

    if(strCopySender.empty())
        return true;

    for (int i = EM_ToIndex; i <= EM_OtherSendMaxCount;++i)
    {
        std::string::size_type nPos = strCopySender.find(";");
        if(nPos == std::string::npos)
             break;

        std::string str = strCopySender.substr(0,nPos);
        strCopySender = strCopySender.substr(nPos + 1,strCopySender.length());

        MeSprintf_s(pAddress[i].addressName,sizeof(pAddress[i].addressName)/sizeof(char) - 1,
            "%s",str.c_str());

        pAddress[i].charDbId = thePlayerRole.GetdbID(pAddress[i].addressName);

    }
    return true;
}

void CUI_ID_FRAME_MailMain::SetButMailState(bool bEnable)
{
	if(!m_pID_FRAME_MailMain)
		return;
    m_pID_BUTTON_Send->SetEnable(bEnable);
    m_pID_BUTTON_Reset->SetEnable(bEnable);
}
void CUI_ID_FRAME_MailMain::RefreshEnable(int nOldBagType,int nOldIndex,int nNewBagType,int nNewIndex)
{
    if(nOldBagType == BT_NormalItemBag)
    {
        if(nOldIndex != -1)
        {
            // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
			m_LogID = 0;
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, nOldIndex, true );
			theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
        }
    }
    else if(nOldBagType == BT_MaterialBag)
    {
        if(nOldIndex != -1)
        {
            // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
			m_LogID = 0;
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, nOldIndex, true );
			theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
        }
    }
    // 坐骑的灰亮统一管理，等以后有了邮寄系统再调试         deleted by zhuomeng.hu		[12/27/2010]
    //else if(nOldBagType == BT_MountBag)
    //{
    //    if(nOldIndex != -1)
    //        s_CUI_ID_FRAME_Pet.RefreshEnable(nOldIndex,(bool)eIcon_Enable);
    //}

    if(nNewBagType == BT_NormalItemBag)
    {
        if(nNewIndex != -1)
        {
            // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
			m_LogID = thePlayerRole.m_bag.GetCharItemFromIdx(nNewIndex)->GetItemGuid();
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, nNewIndex, true );
			theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
        }
    }
    else if(nNewBagType == BT_MaterialBag)
    {
        if(nNewIndex != -1)
        {
            // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
			m_LogID = thePlayerRole.m_bagMaterial.GetCharItemFromIdx(nNewIndex)->GetItemGuid();
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, nNewIndex, true );
			theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
        }
    }
    //else if(nNewBagType == BT_MountBag)
    //{
    //    if(nNewIndex != -1)
    //        s_CUI_ID_FRAME_Pet.RefreshEnable(nNewIndex,(bool)eIcon_Disable);
    //}
	
}


void CUI_ID_FRAME_MailMain::SetVisiblePosition(const D3DXVECTOR3 &vPos)
{
    m_vVisualPos.x = vPos.x;
    m_vVisualPos.y = vPos.y;
    m_vVisualPos.z = vPos.z;
}

bool CUI_ID_FRAME_MailMain::IsOverDistance(const D3DXVECTOR3& vCurPos)
{
    float xoff = vCurPos.x - m_vVisualPos.x;
    float yoff = vCurPos.y - m_vVisualPos.y;
    float fDist = sqrtf( xoff*xoff + yoff*yoff );
    return (fDist > 12.0f);
}

void CUI_ID_FRAME_MailMain::RefreshMailMoney()
{
    if(!m_pID_FRAME_MailMain)
        return;

    DWORD dwMoney = 0,mailMoney = 0;
    bool bHasItem = false;

    if(GetMoney(mailMoney,true))
    {
        if(mailMoney > 0)
        {
             bHasItem = true;
        }
        else
        {
            ControlIconDrag::S_ListImg *pImg = m_pID_LISTIMG_MailItem->GetItemByIndex(0);
            if(pImg)
			{
				int itemID = pImg->m_pkIconInfo->GetItemId(); 
				if (thePlayerRole.m_bag.IsHaveItemById(itemID) || thePlayerRole.m_bagMaterial.IsHaveItemById(itemID))
				{
					bHasItem = true;
				}	
			}
        }
    }
    if(bHasItem)
        dwMoney += 5 * 100;  //附件邮资

    int nCount = 0;
    if(!bHasItem&&m_pID_EDIT_SendTarget->GetText() != "")
        ++nCount;

    std::string strCopyer = m_pID_EDIT_CopyTarget->GetText();
    for (int i = EM_ToIndex; i < EM_OtherSendMaxCount;++i)
    {
        std::string::size_type nPos = strCopyer.find(";");
        if(nPos == std::string::npos)
            break;

        std::string str = strCopyer.substr(0,nPos);
        strCopyer = strCopyer.substr(nPos + 1,strCopyer.length());

        ++nCount;
    }

    dwMoney += nCount * 49;  //文本邮资

    int silver = dwMoney / 100;
    int copper = dwMoney - silver * 100;

    std::stringstream str;
    str <<theXmlString.GetString(eText_MailSendNeedMoney);

	std::string MoneyStr="";
	thePlayerRole.GetGSCStringFromJiaoZi(dwMoney,MoneyStr);
    /*if(silver > 0)
        str << silver << "{#82}";
            
    if(copper > 0)
       str << copper << "{#83}";*/

	str<<MoneyStr;

     m_pID_TEXT_Cost->SetText(str.str().c_str());
}


bool CUI_ID_FRAME_MailMain::IsHaveFocus()
{
    if(!IsVisable())
        return false;

    ControlObject* pObject = theUiManager.GetFocus();
    if(!pObject)
        return false;

    if(pObject == m_pID_EDIT_MailTitle 
        || pObject == m_pID_EDIT_CopyTarget
		|| pObject == m_pID_EDIT_SendTarget
        || pObject == m_pID_EDIT_MailContent)
        return true;

    return false;
}

void CUI_ID_FRAME_MailMain::RefreshCopySender()
{
    if(!m_pID_FRAME_MailMain)
        return;
    std::string strCopyer = m_pID_EDIT_CopyTarget->GetText();
	/*if (!strCopyer.empty())
	{
		 strCopyer += ";";
	}*/
    strCopyer += m_pID_COMBOBOX_CopyTarget->GetEditInput().GetText();
	strCopyer += ";";
  
    m_pID_EDIT_CopyTarget->SetText(strCopyer.c_str());
}

void CUI_ID_FRAME_MailMain::EditDataChange( OUT ControlObject* pSender, OUT const char *szData )
{
    s_CUI_ID_FRAME_MailMain.RefreshMailMoney();
}

void CUI_ID_FRAME_MailMain::OnVisibleChange( ControlObject* pUIObject )
{
    s_CUI_ID_FRAME_MailMain.ClearItem();
}

bool CUI_ID_FRAME_MailMain::IsPackItemBeUsing( __int64 nGuid )
{
    if( !IsVisable() || nGuid <= 0 )
        return false;

    // 此处没有保存Guid，且NEXT中暂时无邮寄系统，等待以后添加
	//判断当前物品是否放置在Ui上面
	if(m_LogID == nGuid)
		return true;
    return false;
}

