/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\TaskMenu.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "TaskMenu.h"
#include "MainMenu.h"
#include "Task.h"
#include "ActivityList.h"
#include "QuestEntrust.h"
#include "HuntingQuest.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"

CUI_ID_FRAME_TaskMenu s_CUI_ID_FRAME_TaskMenu;

extern void SetTipAndHotKey(ControlButton* pCtl, const char* szText, AN_Configure_ShortcutKey::ShortCutKey_Configure key);
extern void SetTipAndHotKey(ControlButton* pCtl, AN_Configure_ShortcutKey::ShortCutKey_Configure key);

MAP_FRAME_RUN( s_CUI_ID_FRAME_TaskMenu, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TaskMenu, OnFrameRender )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskMenu, ID_BUTTON_TaskOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskMenu, ID_BUTTON_ActivityOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskMenu, ID_BUTTON_EntrustOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskMenu, ID_BUTTON_HuntingOnButtonClick )

CUI_ID_FRAME_TaskMenu::CUI_ID_FRAME_TaskMenu()
{
	// Member
	m_pID_FRAME_TaskMenu = NULL;
	m_pID_BUTTON_Task = NULL;
	m_pID_BUTTON_Activity = NULL;
	m_pID_BUTTON_Entrust = NULL;
	m_pID_BUTTON_Hunting = NULL;

}
CUI_ID_FRAME_TaskMenu::~CUI_ID_FRAME_TaskMenu()
{
}
// Frame
bool CUI_ID_FRAME_TaskMenu::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_TaskMenu::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_TaskMenu::ID_BUTTON_TaskOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TaskMenu )
		return false;

	s_CUI_ID_FRAME_Task.SetVisable( !s_CUI_ID_FRAME_Task.IsVisable() );
	return true;
}
// Button
bool CUI_ID_FRAME_TaskMenu::ID_BUTTON_ActivityOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TaskMenu )
		return false;

	s_CUI_ID_FRAME_ActivityList.SetVisable( !s_CUI_ID_FRAME_ActivityList.IsVisable() );
	return true;
}
// Button
bool CUI_ID_FRAME_TaskMenu::ID_BUTTON_EntrustOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TaskMenu )
		return false;

	s_CUI_ID_FRAME_QuestEntrust.SetVisable( !s_CUI_ID_FRAME_QuestEntrust.IsVisable() );
	return true;
}

// Button
bool CUI_ID_FRAME_TaskMenu::ID_BUTTON_HuntingOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TaskMenu )
		return false;

	s_CUI_ID_FRAME_Hunting.SetVisable( !s_CUI_ID_FRAME_Hunting.IsVisable() );
	if( theHeroGame.GetPlayerMgr()->GetMe() )
	{
		s_CUI_ID_FRAME_Hunting.SetVisiblePosition( *(Vector*)&theHeroGame.GetPlayerMgr()->GetMe()->GetPos() );
	}	
	return true;
}


// 装载UI
bool CUI_ID_FRAME_TaskMenu::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TaskMenu.meui",true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\TaskMenu.meui]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_TaskMenu::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TaskMenu, s_CUI_ID_FRAME_TaskMenuOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TaskMenu, s_CUI_ID_FRAME_TaskMenuOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_TaskMenu, ID_BUTTON_Task, s_CUI_ID_FRAME_TaskMenuID_BUTTON_TaskOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TaskMenu, ID_BUTTON_Activity, s_CUI_ID_FRAME_TaskMenuID_BUTTON_ActivityOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TaskMenu, ID_BUTTON_Entrust, s_CUI_ID_FRAME_TaskMenuID_BUTTON_EntrustOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TaskMenu, ID_BUTTON_Hunting, s_CUI_ID_FRAME_TaskMenuID_BUTTON_HuntingOnButtonClick );

	m_pID_FRAME_TaskMenu = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TaskMenu );
	m_pID_BUTTON_Task = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaskMenu, ID_BUTTON_Task );
	m_pID_BUTTON_Activity = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaskMenu, ID_BUTTON_Activity );
	m_pID_BUTTON_Entrust = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaskMenu, ID_BUTTON_Entrust );
	m_pID_BUTTON_Hunting = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaskMenu, ID_BUTTON_Hunting );

	assert( m_pID_FRAME_TaskMenu );
	assert( m_pID_BUTTON_Task );
	assert( m_pID_BUTTON_Activity );
	assert( m_pID_BUTTON_Entrust );
	assert( m_pID_BUTTON_Hunting );

	_SetVisable(false);
	m_pID_FRAME_TaskMenu->SetFadeInorFadeOut(true);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_TaskMenu::_UnLoadUI()
{
	return theUiManager.RemoveFrame( "Data\\UI\\TaskMenu.meui" );
}
// 是否可视
bool CUI_ID_FRAME_TaskMenu::_IsVisable()
{
	if ( !m_pID_FRAME_TaskMenu )
		return false;
	return m_pID_FRAME_TaskMenu->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_TaskMenu::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_TaskMenu )
		return;
	m_pID_FRAME_TaskMenu->SetVisable( bVisable );

	if(bVisable)
		RefreshHotKey();
}

void CUI_ID_FRAME_TaskMenu::RefreshHotKey()
{
	if ( !m_pID_FRAME_TaskMenu )
		return;

	SetTipAndHotKey(m_pID_BUTTON_Task, AN_Configure_ShortcutKey::AN_SCKC_uiTask);
	SetTipAndHotKey(m_pID_BUTTON_Activity, AN_Configure_ShortcutKey::AN_SCKC_openEvent);
}