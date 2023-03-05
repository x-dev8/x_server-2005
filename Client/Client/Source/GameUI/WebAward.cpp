///********************************************************************
//	Created by UIEditor.exe
//	FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\WebAward.cpp
//*********************************************************************/
//#include <assert.h>
//#include "MeUi/UiManager.h"
//#include "WebAward.h"
//#include "ui/Pack.h"
//#include "PlayerRole.h"
//#include "NetworkInput.h"
//#include "Core/Name.h"
//#include "XmlStringLanguage.h"
//#include "GameMain.h"
//#include "PlayerMgr.h"
//#include "Player.h"
//#include "UIBase.h"
//#include "MeUI/ExpressionManager.h"
//#include "color_config.h"
//#include "ShowScreenText.h"
//#include "MessageDefine.h"
//#include "ui/MessageBox.h"
//#include "ui/Create.h"
//#include "PackItemEnableManager.h"
//
//CUI_ID_FRAME_WebAward s_CUI_ID_FRAME_WebAward;
//MAP_FRAME_RUN( s_CUI_ID_FRAME_WebAward, OnFrameRun )
//MAP_FRAME_RENDER( s_CUI_ID_FRAME_WebAward, OnFrameRender )
//MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_WebAward, ID_EDIT_PlayerNameOnEditEnter )
//MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_WebAward, ID_EDIT_PhoneOnEditEnter )
//MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_WebAward, ID_EDIT_EmailOnEditEnter )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_WebAward, ID_BUTTON_CLOSEOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_WebAward, ID_BUTTON_ResetOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_WebAward, ID_BUTTON_RegisterOnButtonClick )
//MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_WebAward, ID_EDIT_CardOnEditEnter )
//MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_WebAward, ID_LISTIMG_ItemOnIconDragOn )
//MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_WebAward, ID_LISTIMG_ItemOnIconLDBClick )
//MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_WebAward, ID_LISTIMG_ItemOnIconButtonClick )
//MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_WebAward, ID_LISTIMG_ItemOnIconRButtonUp )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_WebAward, ID_BUTTON_WebOnButtonClick )
//// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_WebAward, ID_CHECKBOX_AgreeOnCheckBoxCheck )
//// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_WebAward, ID_BUTTON_Agreement2OnButtonClick )
//CUI_ID_FRAME_WebAward::CUI_ID_FRAME_WebAward()
//{
//	// Member
//	ResetMembers();
//}
//
//void CUI_ID_FRAME_WebAward::ResetMembers()
//{
//	m_pID_FRAME_WebAward = NULL;
//	m_pID_PICTURE_BackGround = NULL;
//	m_pID_TEXT_PlayerName = NULL;
//	m_pID_PICTURE_PlayerName = NULL;
//	m_pID_EDIT_PlayerName = NULL;
//	m_pID_TEXT_PhoneZ = NULL;
//	m_pID_PICTURE_Phone = NULL;
//	m_pID_EDIT_Phone = NULL;
//	m_pID_TEXT_Email = NULL;
//	m_pID_PICTURE_Email = NULL;
//	m_pID_EDIT_Email = NULL;
//	m_pID_BUTTON_CLOSE = NULL;
//	m_pID_BUTTON_Reset = NULL;
//	m_pID_BUTTON_Register = NULL;
//	m_pID_TEXT_Card = NULL;
//	m_pID_PICTURE_Card = NULL;
//	m_pID_EDIT_Card = NULL;
//	m_pID_PICTURE_PlayerNameExplain = NULL;
//	m_pID_PICTURE_EmailExplain = NULL;
//	m_pID_PICTURE_CardExplain = NULL;
//	m_pID_PICTURE_PhoneExplain = NULL;
//	m_pID_LISTIMG_Item = NULL;
//	m_pID_TEXT_TakeTip = NULL;
//	m_pID_TEXT_23244 = NULL;
//	m_pID_BUTTON_Web = NULL;
//	m_pID_TEXT_Alarm = NULL;
//// 	m_pID_CHECKBOX_Agree = NULL;
//// 	m_pID_BUTTON_Agreement2 = NULL;
//
//	m_bNeedUpdate = false;
//
//	m_moveStarItemBagIndex = -1;
//	m_moveStarItemEnable = true;
//}
//// Frame
//bool CUI_ID_FRAME_WebAward::OnFrameRun()
//{
//	if (!m_bNeedUpdate)
//	{
//		return false;
//	}
//
//	m_bNeedUpdate = false;
//	RefreshAllBagEnable();
//	m_pID_BUTTON_Register->SetEnable( m_moveStarItemBagIndex != -1 );
//	return true;
//}
//bool CUI_ID_FRAME_WebAward::OnFrameRender()
//{
//	if( IsVisable() )
//	{
//		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
//		if ( pMe )
//		{
//			float fMeX,fMeY,fMeZ;			
//			pMe->GetPos( &fMeX, &fMeY, &fMeZ );
//			float dist = pMe->GetDistToTarget( m_vVisiblePos.x, m_vVisiblePos.y );			
//			if( dist > 12.0f )
//			{
//				SetVisable(false);
//			}
//		}
//	}
//	return true;
//}
//// Edit
//void CUI_ID_FRAME_WebAward::ID_EDIT_PlayerNameOnEditEnter( ControlObject* pSender, const char* szData )
//{
//	if (!m_pID_FRAME_WebAward)
//		return;
//	OnTab();
//}
//// Edit
//void CUI_ID_FRAME_WebAward::ID_EDIT_PhoneOnEditEnter( ControlObject* pSender, const char* szData )
//{
//	if (!m_pID_FRAME_WebAward)
//		return;
//	OnTab();
//}
//// Edit
//void CUI_ID_FRAME_WebAward::ID_EDIT_EmailOnEditEnter( ControlObject* pSender, const char* szData )
//{
//	if (!m_pID_FRAME_WebAward)
//		return;
//	OnTab();
//}
//// Button
//bool CUI_ID_FRAME_WebAward::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
//{
//	if (!m_pID_FRAME_WebAward)
//		return false;
//	return true;
//}
//// Button
//bool CUI_ID_FRAME_WebAward::ID_BUTTON_ResetOnButtonClick( ControlObject* pSender )
//{
//	if (!m_pID_FRAME_WebAward)
//		return false;
//	ClearInfo();
//	return true;
//}
//// Button
//bool CUI_ID_FRAME_WebAward::ID_BUTTON_RegisterOnButtonClick( ControlObject* pSender )
//{
//	if (!m_pID_FRAME_WebAward)
//		return false;
//	MsgMoneyItemExchangeReq ItemExchange;
//	const char* pPlayerName = m_pID_EDIT_PlayerName->GetText();
//	if (pPlayerName == NULL || pPlayerName[0] == '\0')
//	{
//		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRealAward_NameEmpty) );
//		return false;
//	}
//	strcpy_s(ItemExchange.linkman,17,pPlayerName);
//
//	const char* pPhoneNumber = m_pID_EDIT_Phone->GetText();
//	if (pPhoneNumber == NULL || pPhoneNumber[0] == '\0')
//	{
//		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRealAward_PhoneEmpty) );
//		return false;
//	}
//	strcpy_s(ItemExchange.telephone,13,pPhoneNumber);
//
//	const char* pEmail = m_pID_EDIT_Email->GetText();
//	if (pEmail == NULL || pEmail[0] == '\0')
//	{
//		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRealAward_EmailEmpty) );
//		return false;
//	}
//	else
//	{
//		if ((strstr(pEmail,"@") == NULL )
//			||(strstr(pEmail,".") == NULL ))
//		{
//			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRealAward_EmailFormatError) );
//			return false;
//		}
//// 			else if (strlen(pEmail) > 50)
//// 			{
//// 				UI_MessageBox::Show( theXmlString.GetString(eTextGuild_Disband_Error) );
//// 				return false;
//// 			}
//		
//	}
//	strcpy_s(ItemExchange.email,50,pEmail);
//	
//	const char* pIdCard = m_pID_EDIT_Card->GetText();
//	if (pIdCard == NULL || pIdCard[0] == '\0')
//	{
//		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRealAward_CardEmpty) );
//		return false;
//	}
//	else
//	{
//		if ((strlen(pIdCard) != 15) && (strlen(pIdCard) != 18) )
//		{
//			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRealAward_CardLengthError) );
//			return false;
//		}			
//	}
//	strcpy_s(ItemExchange.identityCard,19,pIdCard);
//
//	SCharItem equip;
//	if (!thePlayerRole.m_bag.GetItem(m_moveStarItemBagIndex, &equip))
//		return false;
//
//	ItemExchange.index = m_moveStarItemBagIndex;
//	ItemExchange.itemguid = equip.itembaseinfo.nOnlyInt;
//	GettheNetworkInput().SendMsg( &ItemExchange );
//
//	ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID(equip.itembaseinfo.ustItemID);
//	if (pItem)
//	{
//		char cTemp[1024];
//		sprintf_s(cTemp,1024,theXmlString.GetString(eRealAward_Congratulation),pItem->GetItemName());
//		m_pID_TEXT_23244->SetText(cTemp);
//	}
//	m_pID_BUTTON_Reset->SetEnable(false);
//	m_pID_BUTTON_Register->SetEnable(false);
//	return true;
//}
//// Edit
//void CUI_ID_FRAME_WebAward::ID_EDIT_CardOnEditEnter( ControlObject* pSender, const char* szData )
//{
//	if (!m_pID_FRAME_WebAward)
//		return;
//	ID_BUTTON_RegisterOnButtonClick(NULL);
//}
//// ListImg / ListEx
//bool CUI_ID_FRAME_WebAward::ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
//										ControlIconDrag::S_ListImg* pItemDrag,
//										ControlIconDrag::S_ListImg* pItemSrc )
//{
//	if( !m_pID_FRAME_WebAward )
//		return false;
//	if (pItemSrc && pItemSrc->IsNull() == false)
//		return false;
//
//	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
//	if( pItemCommon && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_REALAWARD )
//	{
//		ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
//		if( !pImageSender )
//			return false;
//
//		// 包裹里
//		if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pImageSender) )
//		{		
//			SetRealAwardItem(pItemDrag);
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}	
//	return false;
//}
//bool CUI_ID_FRAME_WebAward::ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	if (!m_pID_FRAME_WebAward)
//		return false;
//	return false;
//}
//bool CUI_ID_FRAME_WebAward::ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	if (!m_pID_FRAME_WebAward)
//		return false;
//	return false;
//}
//bool CUI_ID_FRAME_WebAward::ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	if (!m_pID_FRAME_WebAward)
//		return false;
//	SetRealAwardItemBagIndex(-1, true);
//	m_pID_LISTIMG_Item->Clear();
//	return false;
//}
//// Button
//bool CUI_ID_FRAME_WebAward::ID_BUTTON_WebOnButtonClick( ControlObject* pSender )
//{
//	return false;
//	if (!m_pID_FRAME_WebAward)
//		return false;
//	ShellExecute( NULL, "open", "http://event.tolez.com/ws/prize/", NULL, NULL, 0 );
//	SetVisable(false);
//	return true;
//}
//// CheckBox
////void CUI_ID_FRAME_WebAward::ID_CHECKBOX_AgreeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
////{
////	if (!m_pID_FRAME_WebAward)
////		return;
////}
////// Button
////bool CUI_ID_FRAME_WebAward::ID_BUTTON_Agreement2OnButtonClick( ControlObject* pSender )
////{
////	if (!m_pID_FRAME_WebAward)
////		return false;
////	return true;
////}
//
//// 装载UI
//bool CUI_ID_FRAME_WebAward::_LoadUI()
//{
//	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\WebAward.MEUI" , false, UI_Render_LayerThree);
//	if ( dwResult == 0 )
//	{
//		MESSAGE_BOX("读取文件[Data\\UI\\WebAward.MEUI]失败")
//		return false;
//	}
//	return DoControlConnect();
//}
//// 关连控件
//bool CUI_ID_FRAME_WebAward::DoControlConnect()
//{
//	theUiManager.OnFrameRun( ID_FRAME_WebAward, s_CUI_ID_FRAME_WebAwardOnFrameRun );
//	theUiManager.OnFrameRender( ID_FRAME_WebAward, s_CUI_ID_FRAME_WebAwardOnFrameRender );
//	theUiManager.OnEditEnter( ID_FRAME_WebAward, ID_EDIT_PlayerName, s_CUI_ID_FRAME_WebAwardID_EDIT_PlayerNameOnEditEnter );
//	theUiManager.OnEditEnter( ID_FRAME_WebAward, ID_EDIT_Phone, s_CUI_ID_FRAME_WebAwardID_EDIT_PhoneOnEditEnter );
//	theUiManager.OnEditEnter( ID_FRAME_WebAward, ID_EDIT_Email, s_CUI_ID_FRAME_WebAwardID_EDIT_EmailOnEditEnter );
//	theUiManager.OnButtonClick( ID_FRAME_WebAward, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_WebAwardID_BUTTON_CLOSEOnButtonClick );
//	theUiManager.OnButtonClick( ID_FRAME_WebAward, ID_BUTTON_Reset, s_CUI_ID_FRAME_WebAwardID_BUTTON_ResetOnButtonClick );
//	theUiManager.OnButtonClick( ID_FRAME_WebAward, ID_BUTTON_Register, s_CUI_ID_FRAME_WebAwardID_BUTTON_RegisterOnButtonClick );
//	theUiManager.OnEditEnter( ID_FRAME_WebAward, ID_EDIT_Card, s_CUI_ID_FRAME_WebAwardID_EDIT_CardOnEditEnter );
//	theUiManager.OnIconDragOn( ID_FRAME_WebAward, ID_LISTIMG_Item, s_CUI_ID_FRAME_WebAwardID_LISTIMG_ItemOnIconDragOn );
//	theUiManager.OnIconLDBClick( ID_FRAME_WebAward, ID_LISTIMG_Item, s_CUI_ID_FRAME_WebAwardID_LISTIMG_ItemOnIconLDBClick );
//	theUiManager.OnIconButtonClick( ID_FRAME_WebAward, ID_LISTIMG_Item, s_CUI_ID_FRAME_WebAwardID_LISTIMG_ItemOnIconButtonClick );
//	theUiManager.OnIconRButtonUp( ID_FRAME_WebAward, ID_LISTIMG_Item, s_CUI_ID_FRAME_WebAwardID_LISTIMG_ItemOnIconRButtonUp );
//	theUiManager.OnButtonClick( ID_FRAME_WebAward, ID_BUTTON_Web, s_CUI_ID_FRAME_WebAwardID_BUTTON_WebOnButtonClick );
//	//theUiManager.OnCheckBoxCheck( ID_FRAME_WebAward, ID_CHECKBOX_Agree, s_CUI_ID_FRAME_WebAwardID_CHECKBOX_AgreeOnCheckBoxCheck );
//	//theUiManager.OnButtonClick( ID_FRAME_WebAward, ID_BUTTON_Agreement2, s_CUI_ID_FRAME_WebAwardID_BUTTON_Agreement2OnButtonClick );
//
//	m_pID_FRAME_WebAward = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_WebAward );
//	m_pID_PICTURE_BackGround = (ControlPicture*)theUiManager.FindControl( ID_FRAME_WebAward, ID_PICTURE_BackGround );
//	m_pID_TEXT_PlayerName = (ControlText*)theUiManager.FindControl( ID_FRAME_WebAward, ID_TEXT_PlayerName );
//	m_pID_PICTURE_PlayerName = (ControlPicture*)theUiManager.FindControl( ID_FRAME_WebAward, ID_PICTURE_PlayerName );
//	m_pID_EDIT_PlayerName = (ControlEdit*)theUiManager.FindControl( ID_FRAME_WebAward, ID_EDIT_PlayerName );
//	m_pID_TEXT_PhoneZ = (ControlText*)theUiManager.FindControl( ID_FRAME_WebAward, ID_TEXT_PhoneZ );
//	m_pID_PICTURE_Phone = (ControlPicture*)theUiManager.FindControl( ID_FRAME_WebAward, ID_PICTURE_Phone );
//	m_pID_EDIT_Phone = (ControlEdit*)theUiManager.FindControl( ID_FRAME_WebAward, ID_EDIT_Phone );
//	m_pID_TEXT_Email = (ControlText*)theUiManager.FindControl( ID_FRAME_WebAward, ID_TEXT_Email );
//	m_pID_PICTURE_Email = (ControlPicture*)theUiManager.FindControl( ID_FRAME_WebAward, ID_PICTURE_Email );
//	m_pID_EDIT_Email = (ControlEdit*)theUiManager.FindControl( ID_FRAME_WebAward, ID_EDIT_Email );
//	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_WebAward, ID_BUTTON_CLOSE );
//	m_pID_BUTTON_Reset = (ControlButton*)theUiManager.FindControl( ID_FRAME_WebAward, ID_BUTTON_Reset );
//	m_pID_BUTTON_Register = (ControlButton*)theUiManager.FindControl( ID_FRAME_WebAward, ID_BUTTON_Register );
//	m_pID_TEXT_Card = (ControlText*)theUiManager.FindControl( ID_FRAME_WebAward, ID_TEXT_Card );
//	m_pID_PICTURE_Card = (ControlPicture*)theUiManager.FindControl( ID_FRAME_WebAward, ID_PICTURE_Card );
//	m_pID_EDIT_Card = (ControlEdit*)theUiManager.FindControl( ID_FRAME_WebAward, ID_EDIT_Card );
//	m_pID_PICTURE_PlayerNameExplain = (ControlPicture*)theUiManager.FindControl( ID_FRAME_WebAward, ID_PICTURE_PlayerNameExplain );
//	m_pID_PICTURE_EmailExplain = (ControlPicture*)theUiManager.FindControl( ID_FRAME_WebAward, ID_PICTURE_EmailExplain );
//	m_pID_PICTURE_CardExplain = (ControlPicture*)theUiManager.FindControl( ID_FRAME_WebAward, ID_PICTURE_CardExplain );
//	m_pID_PICTURE_PhoneExplain = (ControlPicture*)theUiManager.FindControl( ID_FRAME_WebAward, ID_PICTURE_PhoneExplain );
//	m_pID_LISTIMG_Item = (ControlListImage*)theUiManager.FindControl( ID_FRAME_WebAward, ID_LISTIMG_Item );
//	m_pID_TEXT_TakeTip = (ControlText*)theUiManager.FindControl( ID_FRAME_WebAward, ID_TEXT_TakeTip );
//	m_pID_TEXT_23244 = (ControlText*)theUiManager.FindControl( ID_FRAME_WebAward, ID_TEXT_23244 );
//	m_pID_BUTTON_Web = (ControlButton*)theUiManager.FindControl( ID_FRAME_WebAward, ID_BUTTON_Web );
//	m_pID_TEXT_Alarm = (ControlText*)theUiManager.FindControl( ID_FRAME_WebAward, ID_TEXT_Alarm );
//	//m_pID_CHECKBOX_Agree = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_WebAward, ID_CHECKBOX_Agree );
//	//m_pID_BUTTON_Agreement2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_WebAward, ID_BUTTON_Agreement2 );
//	assert( m_pID_FRAME_WebAward );
//	assert( m_pID_PICTURE_BackGround );
//	assert( m_pID_TEXT_PlayerName );
//	assert( m_pID_PICTURE_PlayerName );
//	assert( m_pID_EDIT_PlayerName );
//	assert( m_pID_TEXT_PhoneZ );
//	assert( m_pID_PICTURE_Phone );
//	assert( m_pID_EDIT_Phone );
//	assert( m_pID_TEXT_Email );
//	assert( m_pID_PICTURE_Email );
//	assert( m_pID_EDIT_Email );
//	assert( m_pID_BUTTON_CLOSE );
//	assert( m_pID_BUTTON_Reset );
//	assert( m_pID_BUTTON_Register );
//	assert( m_pID_TEXT_Card );
//	assert( m_pID_PICTURE_Card );
//	assert( m_pID_EDIT_Card );
//	assert( m_pID_PICTURE_PlayerNameExplain );
//	assert( m_pID_PICTURE_EmailExplain );
//	assert( m_pID_PICTURE_CardExplain );
//	assert( m_pID_PICTURE_PhoneExplain );
//	assert( m_pID_LISTIMG_Item );
//	assert( m_pID_TEXT_TakeTip );
//	assert( m_pID_TEXT_23244 );
//	assert( m_pID_BUTTON_Web );
//	assert( m_pID_TEXT_Alarm );
//// 	assert( m_pID_CHECKBOX_Agree );
//// 	assert( m_pID_BUTTON_Agreement2 );
//
//
//
//	m_AwardInfoCtrlGroup.AddControl( m_pID_BUTTON_Web );
//	m_AwardInfoCtrlGroup.AddControl( m_pID_TEXT_23244 );
//
//	m_AddressCtrlGroup.AddControl( m_pID_TEXT_PlayerName );
//	m_AddressCtrlGroup.AddControl( m_pID_PICTURE_PlayerName );
//	m_AddressCtrlGroup.AddControl( m_pID_EDIT_PlayerName );
//	m_AddressCtrlGroup.AddControl( m_pID_TEXT_PhoneZ );
//	m_AddressCtrlGroup.AddControl( m_pID_PICTURE_Phone );
//	m_AddressCtrlGroup.AddControl( m_pID_EDIT_Phone );
//	m_AddressCtrlGroup.AddControl( m_pID_TEXT_Email );
//	m_AddressCtrlGroup.AddControl( m_pID_PICTURE_Email );
//	m_AddressCtrlGroup.AddControl( m_pID_EDIT_Email );
//	m_AddressCtrlGroup.AddControl( m_pID_BUTTON_Reset );
//	m_AddressCtrlGroup.AddControl( m_pID_BUTTON_Register );
//	m_AddressCtrlGroup.AddControl( m_pID_TEXT_Card );
//	m_AddressCtrlGroup.AddControl( m_pID_PICTURE_Card );
//	m_AddressCtrlGroup.AddControl( m_pID_EDIT_Card );
//	m_AddressCtrlGroup.AddControl( m_pID_LISTIMG_Item );
//	m_AddressCtrlGroup.AddControl( m_pID_PICTURE_PlayerNameExplain );
//	m_AddressCtrlGroup.AddControl( m_pID_PICTURE_EmailExplain );
//	m_AddressCtrlGroup.AddControl( m_pID_PICTURE_CardExplain );
//	m_AddressCtrlGroup.AddControl( m_pID_PICTURE_PhoneExplain );
//	m_AddressCtrlGroup.AddControl( m_pID_TEXT_TakeTip );
//
//	m_pID_FRAME_WebAward->SetOnVisibleChangedFun(OnVisibleChanged);
//	m_pID_FRAME_WebAward->SetOnTab( OnTab );
//
//	m_pID_EDIT_PlayerName->SetMaxLength(4);
//	m_pID_EDIT_Phone->SetMaxLength(12);
//	m_pID_EDIT_Phone->SetIsNumber(true);
//	m_pID_EDIT_Card->SetMaxLength(18);
//// 		m_pID_EDIT_Card->SetIsNumber(true);
//	m_pID_EDIT_Email->SetMaxLength(50);
//
//	SetVisable(false);
//	return true;
//}
//// 卸载UI
//bool CUI_ID_FRAME_WebAward::_UnLoadUI()
//{
//	m_AwardInfoCtrlGroup.Clear();
//	m_AddressCtrlGroup.Clear();
//	ResetMembers();
//	return theUiManager.RemoveFrame( "Data\\UI\\WebAward.MEUI" );
//}
//// 是否可视
//bool CUI_ID_FRAME_WebAward::_IsVisable()
//{
//	if (!m_pID_FRAME_WebAward)
//		return false;
//	return m_pID_FRAME_WebAward->IsVisable();
//}
//// 设置是否可视
//void CUI_ID_FRAME_WebAward::_SetVisable( const bool bVisable )
//{
//	if( !m_pID_FRAME_WebAward )
//		return;
//	m_pID_FRAME_WebAward->SetVisable( bVisable );
//	if (bVisable)
//	{
//		m_AwardInfoCtrlGroup.SetVisible(false);
//		m_AddressCtrlGroup.SetVisible(true);
//		m_pID_BUTTON_Reset->SetEnable(true);
//		m_pID_BUTTON_Register->SetEnable(true);
//		theUiManager.SetFocus(m_pID_EDIT_PlayerName);
//		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
//	}
//	else
//	{
//		ImmAssociateContext( g_hWnd, NULL );
//	}
//	
//}
//
//void CUI_ID_FRAME_WebAward::SetRealAwardItem( ControlIconDrag::S_ListImg* pItem )
//{
//	int moveStarItemBagIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItem );
//	if (moveStarItemBagIndex != -1)
//	{
//		ControlIconDrag::S_ListImg item = *pItem;
//		item.m_eEnable = eIcon_Enable;
//		m_pID_LISTIMG_Item->SetItem(&item, 0);
//
//		SetRealAwardItemBagIndex(moveStarItemBagIndex, false);
//
//	}
//
//}
//
//void CUI_ID_FRAME_WebAward::SetRealAwardItemBagIndex( int index, bool enable )
//{
//	if (m_moveStarItemBagIndex != -1)
//	{
//        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
//        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_moveStarItemBagIndex, true );
//	}
//
//	m_moveStarItemBagIndex = index;
//	m_moveStarItemEnable = enable;
//	m_bNeedUpdate = true;
//
//	if( m_moveStarItemBagIndex != -1 )
//	{
//        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
//        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_moveStarItemBagIndex, true );
//	}
//
//}
//
//void CUI_ID_FRAME_WebAward::ClearInfo()
//{
//	SetRealAwardItemBagIndex(-1, true);
//
//	m_pID_EDIT_PlayerName->SetText("");
//	m_pID_EDIT_Phone->SetText("");
//	m_pID_EDIT_Email->SetText("");
//	m_pID_EDIT_Card->SetText("");
//	m_pID_LISTIMG_Item->Clear();
//
//	m_bNeedUpdate = false;
//
//}
//
//void CUI_ID_FRAME_WebAward::OnVisibleChanged( ControlObject* pSender )
//{
//	s_CUI_ID_FRAME_WebAward.m_bNeedUpdate = false;
//	s_CUI_ID_FRAME_WebAward.ClearInfo();
//
//}
//
//void CUI_ID_FRAME_WebAward::SetOkVisible()
//{
//	if( !m_pID_FRAME_WebAward )
//		return;
//	if (!IsVisable())
//	{
//		SetVisable(true);
//	}
//	m_pID_EDIT_PlayerName->SetText("");
//	m_pID_EDIT_Phone->SetText("");
//	m_pID_EDIT_Email->SetText("");
//	m_pID_EDIT_Card->SetText("");
//	m_AwardInfoCtrlGroup.SetVisible(true);
//	m_AddressCtrlGroup.SetVisible(false);
//}
//
//void CUI_ID_FRAME_WebAward::RefreshAllBagEnable()
//{
//	if( m_moveStarItemBagIndex != -1 )
//	{
//        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
//        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_moveStarItemBagIndex, true );
//	}
//
//}
//
//bool CUI_ID_FRAME_WebAward::EditInputIsVisable()
//{
//	guardfunc;
//	if (m_pID_FRAME_WebAward)
//	{
//		return (theUiManager.GetFocus() == m_pID_EDIT_PlayerName)
//			||(theUiManager.GetFocus() == m_pID_EDIT_Phone)
//			||(theUiManager.GetFocus() == m_pID_EDIT_Email)
//			||(theUiManager.GetFocus() == m_pID_EDIT_Card)
//			;
//	}
//	return false;
//	unguard;
//
//}
//
//void CUI_ID_FRAME_WebAward::OnTab()
//{
//	guardfunc;
//	if( theUiManager.GetFocus() == s_CUI_ID_FRAME_WebAward.m_pID_EDIT_PlayerName )
//	{
//		theUiManager.SetFocus( s_CUI_ID_FRAME_WebAward.m_pID_EDIT_Phone );
//		s_CUI_ID_FRAME_WebAward.m_pID_EDIT_Phone->SelectAllContext();
//	}
//	else if( theUiManager.GetFocus() == s_CUI_ID_FRAME_WebAward.m_pID_EDIT_Phone )
//	{
//		theUiManager.SetFocus( s_CUI_ID_FRAME_WebAward.m_pID_EDIT_Email );
//		s_CUI_ID_FRAME_WebAward.m_pID_EDIT_Email->SelectAllContext();
//	}
//	else if( theUiManager.GetFocus() == s_CUI_ID_FRAME_WebAward.m_pID_EDIT_Email )
//	{
//		theUiManager.SetFocus( s_CUI_ID_FRAME_WebAward.m_pID_EDIT_Card );
//		s_CUI_ID_FRAME_WebAward.m_pID_EDIT_Card->SelectAllContext();
//	}
//	else if( theUiManager.GetFocus() == s_CUI_ID_FRAME_WebAward.m_pID_EDIT_Card )
//	{
//		theUiManager.SetFocus( s_CUI_ID_FRAME_WebAward.m_pID_EDIT_PlayerName );
//		s_CUI_ID_FRAME_WebAward.m_pID_EDIT_PlayerName->SelectAllContext();
//	}
//	unguard;
//
//}