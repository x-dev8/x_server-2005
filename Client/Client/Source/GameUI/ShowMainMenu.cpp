/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\ShowMainMenu.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ShowMainMenu.h"
#include "MainMenu.h"
#include "ExMenu.h"
#include "AdditionFuncMenu.h"
#include "GamMenu.h"
#include "TaskMenu.h"

CUI_ID_FRAME_ShowMainMenu s_CUI_ID_FRAME_ShowMainMenu;

MAP_FRAME_RUN( s_CUI_ID_FRAME_ShowMainMenu, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ShowMainMenu, OnFrameRender )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShowMainMenu, ID_BUTTON_ShowOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShowMainMenu, ID_BUTTON_HideOnButtonClick )
CUI_ID_FRAME_ShowMainMenu::CUI_ID_FRAME_ShowMainMenu()
{
	// Member
	m_pID_FRAME_ShowMainMenu = NULL;
	m_pID_BUTTON_Show = NULL;
	m_pID_BUTTON_Hide = NULL;

	m_bShow = true;

}
CUI_ID_FRAME_ShowMainMenu::~CUI_ID_FRAME_ShowMainMenu()
{
}
// Frame
bool CUI_ID_FRAME_ShowMainMenu::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_ShowMainMenu::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_ShowMainMenu::ID_BUTTON_ShowOnButtonClick( ControlObject* pSender )
{
	ControlFrame* pmenuFrame = s_CUI_ID_FRAME_MainMenu.GetFrame();
	if ( !pmenuFrame )
		return false;
	if ( pmenuFrame->IsMoving() )
		return false;

	m_bShow = true;
	ShowButton();
	Refresh();
	return true;
}
// Button
bool CUI_ID_FRAME_ShowMainMenu::ID_BUTTON_HideOnButtonClick( ControlObject* pSender )
{
	ControlFrame* pmenuFrame = s_CUI_ID_FRAME_MainMenu.GetFrame();
	if ( !pmenuFrame )
		return false;
	if ( pmenuFrame->IsMoving() )
		return false;

	m_bShow = false;
	ShowButton();
	Refresh();
	return true;
}

// 装载UI
bool CUI_ID_FRAME_ShowMainMenu::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ShowMainMenu.meui", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ShowMainMenu.meui]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ShowMainMenu::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ShowMainMenu, s_CUI_ID_FRAME_ShowMainMenuOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ShowMainMenu, s_CUI_ID_FRAME_ShowMainMenuOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ShowMainMenu, ID_BUTTON_Show, s_CUI_ID_FRAME_ShowMainMenuID_BUTTON_ShowOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ShowMainMenu, ID_BUTTON_Hide, s_CUI_ID_FRAME_ShowMainMenuID_BUTTON_HideOnButtonClick );

	m_pID_FRAME_ShowMainMenu = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ShowMainMenu );
	m_pID_BUTTON_Show = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShowMainMenu, ID_BUTTON_Show );
	m_pID_BUTTON_Hide = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShowMainMenu, ID_BUTTON_Hide );
	assert( m_pID_FRAME_ShowMainMenu );
	assert( m_pID_BUTTON_Show );
	assert( m_pID_BUTTON_Hide );

	m_pID_BUTTON_Show->SetVisable(false);
	m_pID_BUTTON_Hide->SetVisable(false);

	m_pID_FRAME_ShowMainMenu->SetOnEscResponseType( ControlFrame::EscResponse_SkipMe );

	_SetVisable(false);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ShowMainMenu::_UnLoadUI()
{
	return theUiManager.RemoveFrame( "Data\\UI\\ShowMainMenu.meui" );
}
// 是否可视
bool CUI_ID_FRAME_ShowMainMenu::_IsVisable()
{
	if ( !m_pID_FRAME_ShowMainMenu )
		return false;
	return m_pID_FRAME_ShowMainMenu->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ShowMainMenu::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_ShowMainMenu )
		return;
	m_pID_FRAME_ShowMainMenu->SetVisable( bVisable );
}

void CUI_ID_FRAME_ShowMainMenu::InitializeAtEnterWorld()
{
	if ( !m_pID_FRAME_ShowMainMenu )
		return;

	m_bShow = true;
	_SetVisable(true);
	ShowButton();
	Refresh();
}

void CUI_ID_FRAME_ShowMainMenu::ShowButton()
{
	if ( !m_pID_FRAME_ShowMainMenu )
		return;

	m_pID_BUTTON_Show->SetVisable(!m_bShow);
	m_pID_BUTTON_Hide->SetVisable(m_bShow);
}

void CUI_ID_FRAME_ShowMainMenu::Refresh()
{
	RECT rc;
	ControlFrame* pmenuFrame = s_CUI_ID_FRAME_MainMenu.GetFrame();
	if ( !pmenuFrame )
		return;
	pmenuFrame->GetRealRect(&rc);

	int nMove = pmenuFrame->GetWidth() + 100;

	/*if ( pmenuFrame->IsMoving() )
		return;*/

	if (m_bShow)
	{
		if (rc.left > SCREEN_WIDTH)
			pmenuFrame->MoveTo(rc.left - nMove, rc.top);
		else
			pmenuFrame->MoveTo(rc.left, rc.top);
		pmenuFrame->SetRedraw();
	}
	else
	{
		pmenuFrame->MoveTo(rc.left + nMove, rc.top);
		pmenuFrame->SetRedraw();

		s_CUI_ID_FRAME_ExMenu.SetVisable( false );
		s_CUI_ID_FRAME_AdditionFuncMenu.SetVisable(false);
		s_CUI_ID_FRAME_GamMenu.SetVisable(false);
		s_CUI_ID_FRAME_TaskMenu.SetVisable(false);
	}
}