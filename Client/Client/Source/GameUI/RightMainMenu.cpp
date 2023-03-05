/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\RightMainMenu.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "RightMainMenu.h"
#include "ActivityList.h"

CUI_ID_FRAME_RightMainMenu s_CUI_ID_FRAME_RightMainMenu;
MAP_FRAME_RUN( s_CUI_ID_FRAME_RightMainMenu, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_RightMainMenu, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RightMainMenu, ID_BUTTON_HideOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RightMainMenu, ID_BUTTON_AppearOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RightMainMenu, ID_BUTTON_ShopOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RightMainMenu, ID_BUTTON_ActivityListOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RightMainMenu, ID_BUTTON_TaxisOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RightMainMenu, ID_BUTTON_TitleOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RightMainMenu, ID_BUTTON_RichesOnButtonClick )
CUI_ID_FRAME_RightMainMenu::CUI_ID_FRAME_RightMainMenu()
{
	// Member
	m_pID_FRAME_RightMainMenu = NULL;
	m_pID_BUTTON_Hide = NULL;
	m_pID_BUTTON_Appear = NULL;
	m_pID_BUTTON_Shop = NULL;
	m_pID_BUTTON_ActivityList = NULL;
	m_pID_BUTTON_Taxis = NULL;
	m_pID_BUTTON_Title = NULL;
	m_pID_BUTTON_Riches = NULL;

}
// Frame
bool CUI_ID_FRAME_RightMainMenu::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_RightMainMenu::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_RightMainMenu::ID_BUTTON_HideOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RightMainMenu )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_RightMainMenu::ID_BUTTON_AppearOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RightMainMenu )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_RightMainMenu::ID_BUTTON_ShopOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RightMainMenu )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_RightMainMenu::ID_BUTTON_ActivityListOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RightMainMenu )
		return false;
	s_CUI_ID_FRAME_ActivityList.SetVisable(!s_CUI_ID_FRAME_ActivityList.IsVisable());
	return true;
}
// Button
bool CUI_ID_FRAME_RightMainMenu::ID_BUTTON_TaxisOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RightMainMenu )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_RightMainMenu::ID_BUTTON_TitleOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RightMainMenu )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_RightMainMenu::ID_BUTTON_RichesOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RightMainMenu )
		return false;
	return true;
}

// 装载UI
bool CUI_ID_FRAME_RightMainMenu::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\RightMainMenu.MEUI", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\RightMainMenu.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_RightMainMenu::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_RightMainMenu, s_CUI_ID_FRAME_RightMainMenuOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_RightMainMenu, s_CUI_ID_FRAME_RightMainMenuOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_RightMainMenu, ID_BUTTON_Hide, s_CUI_ID_FRAME_RightMainMenuID_BUTTON_HideOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RightMainMenu, ID_BUTTON_Appear, s_CUI_ID_FRAME_RightMainMenuID_BUTTON_AppearOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RightMainMenu, ID_BUTTON_Shop, s_CUI_ID_FRAME_RightMainMenuID_BUTTON_ShopOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RightMainMenu, ID_BUTTON_ActivityList, s_CUI_ID_FRAME_RightMainMenuID_BUTTON_ActivityListOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RightMainMenu, ID_BUTTON_Taxis, s_CUI_ID_FRAME_RightMainMenuID_BUTTON_TaxisOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RightMainMenu, ID_BUTTON_Title, s_CUI_ID_FRAME_RightMainMenuID_BUTTON_TitleOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RightMainMenu, ID_BUTTON_Riches, s_CUI_ID_FRAME_RightMainMenuID_BUTTON_RichesOnButtonClick );

	m_pID_FRAME_RightMainMenu = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_RightMainMenu );
	m_pID_BUTTON_Hide = (ControlButton*)theUiManager.FindControl( ID_FRAME_RightMainMenu, ID_BUTTON_Hide );
	m_pID_BUTTON_Appear = (ControlButton*)theUiManager.FindControl( ID_FRAME_RightMainMenu, ID_BUTTON_Appear );
	m_pID_BUTTON_Shop = (ControlButton*)theUiManager.FindControl( ID_FRAME_RightMainMenu, ID_BUTTON_Shop );
	m_pID_BUTTON_ActivityList = (ControlButton*)theUiManager.FindControl( ID_FRAME_RightMainMenu, ID_BUTTON_ActivityList );
	m_pID_BUTTON_Taxis = (ControlButton*)theUiManager.FindControl( ID_FRAME_RightMainMenu, ID_BUTTON_Taxis );
	m_pID_BUTTON_Title = (ControlButton*)theUiManager.FindControl( ID_FRAME_RightMainMenu, ID_BUTTON_Title );
	m_pID_BUTTON_Riches = (ControlButton*)theUiManager.FindControl( ID_FRAME_RightMainMenu, ID_BUTTON_Riches );
	assert( m_pID_FRAME_RightMainMenu );
	assert( m_pID_BUTTON_Hide );
	assert( m_pID_BUTTON_Appear );
	assert( m_pID_BUTTON_Shop );
	assert( m_pID_BUTTON_ActivityList );
	assert( m_pID_BUTTON_Taxis );
	assert( m_pID_BUTTON_Title );
	assert( m_pID_BUTTON_Riches );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_RightMainMenu::_UnLoadUI()
{
	m_pID_FRAME_RightMainMenu = NULL;
	m_pID_BUTTON_Hide = NULL;
	m_pID_BUTTON_Appear = NULL;
	m_pID_BUTTON_Shop = NULL;
	m_pID_BUTTON_ActivityList = NULL;
	m_pID_BUTTON_Taxis = NULL;
	m_pID_BUTTON_Title = NULL;
	m_pID_BUTTON_Riches = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\RightMainMenu.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_RightMainMenu::_IsVisable()
{
	if( !m_pID_FRAME_RightMainMenu )
		return false;
	return m_pID_FRAME_RightMainMenu->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_RightMainMenu::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_RightMainMenu )
		return;
	m_pID_FRAME_RightMainMenu->SetVisable( bVisable );
}
