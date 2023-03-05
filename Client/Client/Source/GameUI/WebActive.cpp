/********************************************************************
	Created by UIEditor.exe
	FileName: E:\sg_pro\3Guo_Branch\FullClient\Data\Ui\WebActive.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "WebActive.h"
#include "GameMain.h"
#include "Browser/Browser.h"
#include "Cfg.h"
extern GAME_STATE	g_GameState;
extern HWND g_HelpHwnd;

CUI_ID_FRAME_WebActive s_CUI_ID_FRAME_WebActive;

MAP_FRAME_RUN( s_CUI_ID_FRAME_WebActive, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_WebActive, OnFrameRender )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_WebActive, ID_BUTTON_BTOPENOnButtonClick )
CUI_ID_FRAME_WebActive::CUI_ID_FRAME_WebActive()
{
	// Member
	m_pID_FRAME_WebActive = NULL;
	m_pID_BUTTON_BTOPEN = NULL;

}
CUI_ID_FRAME_WebActive::~CUI_ID_FRAME_WebActive()
{
}
// Frame
bool CUI_ID_FRAME_WebActive::OnFrameRun()
{


	return true;
}
bool CUI_ID_FRAME_WebActive::OnFrameRender()
{
	return true;
}
// Button

bool CUI_ID_FRAME_WebActive::ID_BUTTON_BTOPENOnButtonClick( ControlObject* pSender )
{

	if (NULL == g_HelpHwnd)
	{
		g_HelpHwnd = theHeroGame.CreateHelpWindow();
	}

	if (g_HelpHwnd)
	{
		char fullname[MAX_PATH] = {0};
		//sprintf( fullname, "%s/%s", GetRootPath(),gCfg.m_szHelpPagePath );

		DisplayHTMLPage(g_HelpHwnd,gCfg.m_szHelpPagePath);
		// 			ShowWindow( g_HelpHwnd, SW_HIDE );
		ShowWindow( g_HelpHwnd, SW_SHOW );
	}


	return true;
}

// 装载UI
bool CUI_ID_FRAME_WebActive::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\WebActive.meui" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\WebActive.meui]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_WebActive::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_WebActive, s_CUI_ID_FRAME_WebActiveOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_WebActive, s_CUI_ID_FRAME_WebActiveOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_WebActive, ID_BUTTON_BTOPEN, s_CUI_ID_FRAME_WebActiveID_BUTTON_BTOPENOnButtonClick );

	m_pID_FRAME_WebActive = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_WebActive );
	m_pID_BUTTON_BTOPEN = (ControlButton*)theUiManager.FindControl( ID_FRAME_WebActive, ID_BUTTON_BTOPEN );
	assert( m_pID_FRAME_WebActive );
	assert( m_pID_BUTTON_BTOPEN );
	m_pID_FRAME_WebActive->SetOnEscResponseType( ControlFrame::EscResponse_SkipMe );
	

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_WebActive::_UnLoadUI()
{
	return theUiManager.RemoveFrame( "Data\\UI\\WebActive.meui" );
}
// 是否可视
bool CUI_ID_FRAME_WebActive::_IsVisable()
{
	return m_pID_FRAME_WebActive->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_WebActive::_SetVisable( const bool bVisable )
{

		if(bVisable && gCfg.m_szHelpPagePath[0])
		{
			m_pID_FRAME_WebActive->SetVisable( true );
			m_pID_BUTTON_BTOPEN->SetVisable(true);
		}else
		{
			m_pID_FRAME_WebActive->SetVisable( false );
			m_pID_BUTTON_BTOPEN->SetVisable(false);
		}
		  


}
