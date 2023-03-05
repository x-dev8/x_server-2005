/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\gamesetting\GameSettingMouse.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GameSetting.h"
#include "GameSettingMouse.h"
#include "wsCamera.h"
#include "GameSettingUIBase.h"

CUI_ID_FRAME_GameSettingMouse s_CUI_ID_FRAME_GameSettingMouse;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GameSettingMouse, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GameSettingMouse, OnFrameRender )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_GameSettingMouse, ID_SCROLLBAREX_MouseAgilityOnScrollBarExUpdatePos )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_GameSettingMouse, ID_SCROLLBAREX_MouseOnCameraOnScrollBarExUpdatePos )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingMouse, ID_CHECKBOX_AutoMouseOnCheckBoxCheck )
CUI_ID_FRAME_GameSettingMouse::CUI_ID_FRAME_GameSettingMouse()
{
	// Member
	m_pID_FRAME_GameSettingMouse = NULL;
	m_pID_TEXT_MouseAgility = NULL;
	m_pID_TEXT_MouseOnCamera = NULL;
	m_pID_SCROLLBAREX_MouseAgility = NULL;
	m_pID_SCROLLBAREX_MouseOnCamera = NULL;
	m_pID_TEXT_AutoMouse = NULL;
	m_pID_CHECKBOX_AutoMouse = NULL;
	m_pID_TEXT_AutoMouseEx = NULL;
	MouseSpeed = 0;
	CameraRotateSpeed = 0;

}
// Frame
bool CUI_ID_FRAME_GameSettingMouse::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GameSettingMouse::OnFrameRender()
{
	return true;
}
// ScrollBarEx
void CUI_ID_FRAME_GameSettingMouse::ID_SCROLLBAREX_MouseAgilityOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	// 4 - 20
	MouseSpeed = n / 10 + 4;
	SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)(INT_PTR)(MouseSpeed), 0);
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_MOUSESPEED,  MouseSpeed );
	GameSetting::Instance()->CommitChanges();
}
// ScrollBarEx
void CUI_ID_FRAME_GameSettingMouse::ID_SCROLLBAREX_MouseOnCameraOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	CameraRotateSpeed = n / 8 + 20;
	getwsCamera()->SetCameraRotateZSpeed( (float)CameraRotateSpeed/180*D3DX_PI*0.001f );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_CAMERAROTATESPEED,  n );
	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSettingMouse::ID_CHECKBOX_AutoMouseOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_AUTOMOUSE,  *pbChecked );
	GameSetting::Instance()->CommitChanges();
}

// 装载UI
bool CUI_ID_FRAME_GameSettingMouse::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GameSettingMouse.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GameSettingMouse.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GameSettingMouse::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GameSettingMouse, s_CUI_ID_FRAME_GameSettingMouseOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GameSettingMouse, s_CUI_ID_FRAME_GameSettingMouseOnFrameRender );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_GameSettingMouse, ID_SCROLLBAREX_MouseAgility, s_CUI_ID_FRAME_GameSettingMouseID_SCROLLBAREX_MouseAgilityOnScrollBarExUpdatePos );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_GameSettingMouse, ID_SCROLLBAREX_MouseOnCamera, s_CUI_ID_FRAME_GameSettingMouseID_SCROLLBAREX_MouseOnCameraOnScrollBarExUpdatePos );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingMouse, ID_CHECKBOX_AutoMouse, s_CUI_ID_FRAME_GameSettingMouseID_CHECKBOX_AutoMouseOnCheckBoxCheck );

	m_pID_FRAME_GameSettingMouse = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GameSettingMouse );
	m_pID_TEXT_MouseAgility = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingMouse, ID_TEXT_MouseAgility );
	m_pID_TEXT_MouseOnCamera = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingMouse, ID_TEXT_MouseOnCamera );
	m_pID_SCROLLBAREX_MouseAgility = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_GameSettingMouse, ID_SCROLLBAREX_MouseAgility );
	m_pID_SCROLLBAREX_MouseOnCamera = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_GameSettingMouse, ID_SCROLLBAREX_MouseOnCamera );
	m_pID_TEXT_AutoMouse = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingMouse, ID_TEXT_AutoMouse );
	m_pID_CHECKBOX_AutoMouse = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingMouse, ID_CHECKBOX_AutoMouse );
	m_pID_TEXT_AutoMouseEx = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingMouse, ID_TEXT_AutoMouseEx );
	assert( m_pID_FRAME_GameSettingMouse );
	assert( m_pID_TEXT_MouseAgility );
	assert( m_pID_TEXT_MouseOnCamera );
	assert( m_pID_SCROLLBAREX_MouseAgility );
	assert( m_pID_SCROLLBAREX_MouseOnCamera );
	assert( m_pID_TEXT_AutoMouse );
	assert( m_pID_CHECKBOX_AutoMouse );
	assert( m_pID_TEXT_AutoMouseEx );
	m_pID_FRAME_GameSettingMouse->SetMsgHoldup(false);
	GetFrame()->SetFather(s_CUI_ID_FRAME_GameSettingUIBase.GetFrame());
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GameSettingMouse::_UnLoadUI()
{
	m_pID_FRAME_GameSettingMouse = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GameSettingMouse.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GameSettingMouse::_IsVisable()
{
	if( !m_pID_FRAME_GameSettingMouse )
		return false;
	return m_pID_FRAME_GameSettingMouse->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GameSettingMouse::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_GameSettingMouse )
		return;
	m_pID_FRAME_GameSettingMouse->SetVisable( bVisable );
	if (bVisable)
	{
		RefreshUI();
	}
}
void CUI_ID_FRAME_GameSettingMouse::RefreshUI()
{
    if(!m_pID_FRAME_GameSettingMouse)
        return;

	for( int i = 0 ; i < GameSetting::eGSC_TOTAL ; ++ i )
	{
		int nValue = (int)GameSetting::Instance()->GetLevel( (GameSetting::eGameSettingCategory)i );
		switch( i )
		{	
		case GameSetting::eGSC_AUTOMOUSE:
			m_pID_CHECKBOX_AutoMouse->SetCheck( nValue );
			break;		
		case GameSetting::eGSC_MOUSESPEED:
			m_pID_SCROLLBAREX_MouseAgility->SetMaxValue(160);

			if (nValue - 4 <= 0)
				nValue = 0;
			else
				nValue = (nValue - 4) * 10;

			m_pID_SCROLLBAREX_MouseAgility->SetValue( nValue );
			break;
		case GameSetting::eGSC_CAMERAROTATESPEED:
			m_pID_SCROLLBAREX_MouseOnCamera->SetValue( nValue );
			break;
		default:
			break;
		}
	}
}