///********************************************************************
//Created by UIEditor.exe
//FileName: E:\Work\HeroRuntime\CLIENT\UI\Shopping_MessageBox.cpp
//*********************************************************************/
//#include <assert.h>
//#include "MeUi/UiManager.h"
//#include "Shopping_MessageBox.h"
//#include "NetworkInput.h"
//#include "ItemDetail.h"
//#include "ShopCenterSlk.h"
//#include "FuncPerformanceLog.h"
//#include "PlayerRole.h"
//
//#include "MessageBox.h"
//#include "core/Name.h"
//
//#include "XmlStringLanguage.h"
//#include "UIMgr.h"
//
//CUI_ID_Shopping_MessageBox s_CUI_ID_Shopping_MessageBox;
//MAP_FRAME_RUN( s_CUI_ID_Shopping_MessageBox, OnFrameRun )
//MAP_FRAME_RENDER( s_CUI_ID_Shopping_MessageBox, OnFrameRender )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_Shopping_MessageBox, ID_BUTTON_OKOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_Shopping_MessageBox, ID_BUTTON_BackOnButtonClick )
//CUI_ID_Shopping_MessageBox::CUI_ID_Shopping_MessageBox()
//{
//	// SGuildMember
//	ResetMembers();
//}
//
//void CUI_ID_Shopping_MessageBox::ResetMembers()
//{
//	m_pID_Shopping_MessageBox = NULL;
//	m_pID_BUTTON_OK = NULL;
//	m_pID_PICTURE_26801 = NULL;
//	m_pID_PICTURE_26802 = NULL;
//	m_pID_PICTURE_26803 = NULL;
//	m_pID_PICTURE_26804 = NULL;
//	m_pID_TEXT_Static0 = NULL;
//	m_pID_TEXT_Static1 = NULL;
//	m_pID_TEXT_ItemName = NULL;
//	m_pID_TEXT_ItemPrice = NULL;
//	m_pID_BUTTON_Back = NULL;
//	m_pID_TEXT_Note = NULL;
//	m_pID_PICTURE_26805 = NULL;
//	m_pID_TEXT_YinPiao = NULL;
//	m_UseItem = InvalidLogicNumber;
//}
//// Frame
//bool CUI_ID_Shopping_MessageBox::OnFrameRun()
//{
//	return true;
//}
//bool CUI_ID_Shopping_MessageBox::OnFrameRender()
//{
//	return true;
//}
//// Button
//bool CUI_ID_Shopping_MessageBox::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
//{
//	if( NULL == m_pID_Shopping_MessageBox )
//		return false;
//	MsgShopCenterBuy Buy;
//	Buy.ustItemId = m_UseItem;
//	Buy.ustCount = 1;
//	Buy.chType = ECD_ParentType_max;
//	GettheNetworkInput().SendMsg( &Buy );
//
//	SetVisable( FALSE );
//	return true;
//}
//// Button
//bool CUI_ID_Shopping_MessageBox::ID_BUTTON_BackOnButtonClick( ControlObject* pSender )
//{
//	if( NULL == m_pID_Shopping_MessageBox )
//		return false;
//	SetVisable( FALSE );
//	return true;
//}
//
//// 装载UI
//bool CUI_ID_Shopping_MessageBox::_LoadUI()
//{
//	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\Shopping_MessageBox.meui", true, UI_Render_LayerThree );
//	if ( dwResult == 0 )
//	{
//		MESSAGE_BOX("读取文件[UI\\Shopping_MessageBox.UI]失败")
//			return false;
//	}
//	return DoControlConnect();
//}
//// 关连控件
//bool CUI_ID_Shopping_MessageBox::DoControlConnect()
//{
//	theUiManager.OnFrameRun( ID_Shopping_MessageBox, s_CUI_ID_Shopping_MessageBoxOnFrameRun );
//	theUiManager.OnFrameRender( ID_Shopping_MessageBox, s_CUI_ID_Shopping_MessageBoxOnFrameRender );
//	theUiManager.OnButtonClick( ID_Shopping_MessageBox, ID_BUTTON_OK, s_CUI_ID_Shopping_MessageBoxID_BUTTON_OKOnButtonClick );
//	theUiManager.OnButtonClick( ID_Shopping_MessageBox, ID_BUTTON_Back, s_CUI_ID_Shopping_MessageBoxID_BUTTON_BackOnButtonClick );
//
//	m_pID_Shopping_MessageBox = (ControlFrame*)theUiManager.FindFrame( ID_Shopping_MessageBox );
//	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_Shopping_MessageBox, ID_BUTTON_OK );
//	m_pID_PICTURE_26801 = (ControlPicture*)theUiManager.FindControl( ID_Shopping_MessageBox, ID_PICTURE_26801 );
//	m_pID_PICTURE_26802 = (ControlPicture*)theUiManager.FindControl( ID_Shopping_MessageBox, ID_PICTURE_26802 );
//	m_pID_PICTURE_26803 = (ControlPicture*)theUiManager.FindControl( ID_Shopping_MessageBox, ID_PICTURE_26803 );
//	m_pID_PICTURE_26804 = (ControlPicture*)theUiManager.FindControl( ID_Shopping_MessageBox, ID_PICTURE_26804 );
//	m_pID_TEXT_Static0 = (ControlText*)theUiManager.FindControl( ID_Shopping_MessageBox, ID_TEXT_Static0 );
//	m_pID_TEXT_Static1 = (ControlText*)theUiManager.FindControl( ID_Shopping_MessageBox, ID_TEXT_Static1 );
//	m_pID_TEXT_ItemName = (ControlText*)theUiManager.FindControl( ID_Shopping_MessageBox, ID_TEXT_ItemName );
//	m_pID_TEXT_ItemPrice = (ControlText*)theUiManager.FindControl( ID_Shopping_MessageBox, ID_TEXT_ItemPrice );
//	m_pID_BUTTON_Back = (ControlButton*)theUiManager.FindControl( ID_Shopping_MessageBox, ID_BUTTON_Back );
//	m_pID_TEXT_Note = (ControlText*)theUiManager.FindControl( ID_Shopping_MessageBox, ID_TEXT_Note );
//	m_pID_PICTURE_26805 = (ControlPicture*)theUiManager.FindControl( ID_Shopping_MessageBox, ID_PICTURE_26805 );
//	m_pID_TEXT_YinPiao = (ControlText*)theUiManager.FindControl( ID_Shopping_MessageBox, ID_TEXT_YinPiao );
//	assert( m_pID_Shopping_MessageBox );
//	m_pID_Shopping_MessageBox->SetMsgProcFun( MsgProc );
//	assert( m_pID_BUTTON_OK );
//	assert( m_pID_PICTURE_26801 );
//	assert( m_pID_PICTURE_26802 );
//	assert( m_pID_PICTURE_26803 );
//	assert( m_pID_PICTURE_26804 );
//	assert( m_pID_TEXT_Static0 );
//	assert( m_pID_TEXT_Static1 );
//	assert( m_pID_TEXT_ItemName );
//	assert( m_pID_TEXT_ItemPrice );
//	assert( m_pID_BUTTON_Back );
//	assert( m_pID_TEXT_Note );
//	assert( m_pID_PICTURE_26805 );
//	assert( m_pID_TEXT_YinPiao );
//
//	USE_SCRIPT( eUI_OBJECT_Shop_MessageBox, this );
//	m_pID_Shopping_MessageBox->SetOnEscResponseType(ControlFrame::EscResponse_SkipMe);
//
//	SetVisable( false );
//	return true;
//}
//// 卸载UI
//bool CUI_ID_Shopping_MessageBox::_UnLoadUI()
//{
//	CLOSE_SCRIPT( eUI_OBJECT_Shop_MessageBox );
//	ResetMembers();
//	return theUiManager.RemoveFrame( "data\\ui\\Shopping_MessageBox.meui" );
//}
//// 是否可视
//bool CUI_ID_Shopping_MessageBox::_IsVisable()
//{
//	if( NULL == m_pID_Shopping_MessageBox )
//		return false;
//
//	return m_pID_Shopping_MessageBox->IsVisable();
//}
//// 设置是否可视
//void CUI_ID_Shopping_MessageBox::_SetVisable( const bool bVisable )
//{
//	if( NULL == m_pID_Shopping_MessageBox )
//		return;
//	m_pID_Shopping_MessageBox->SetVisable( bVisable );
//	if( bVisable )
//	{
//		theUiManager.ToTop( m_pID_Shopping_MessageBox );
//		theUiManager.Compositor();
//	}	
//	if( !bVisable )
//	{
//		m_UseItem = InvalidLogicNumber;
//	}
//}
//
//bool CUI_ID_Shopping_MessageBox::MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
//{
//	guardfunc;
//	if( !s_CUI_ID_Shopping_MessageBox.IsVisable() )
//		return false;
//
//	switch( msg ) 
//	{
//		case WM_KEYUP:
//			{
//				if( wParam == VK_ESCAPE )
//				{
//					return true;
//				}
//				else if( wParam == VK_RETURN )
//				{
//					s_CUI_ID_Shopping_MessageBox.ID_BUTTON_OKOnButtonClick(NULL);
//
//					return true;
//				}
//			}
//			break;
//	}
//
//	return false;
//	unguard;
//}
