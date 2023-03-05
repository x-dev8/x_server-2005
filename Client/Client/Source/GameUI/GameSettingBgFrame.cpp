/********************************************************************
	Created by UIEditor.exe
	FileName: E:\trunk\Bin\Client\Data\Ui\GameSettingBgFrame.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GameSettingBgFrame.h"
#include "customShortcutKey.h"
#include "GameSettingUI.h"
#include "SettingEffect.h"

CUI_ID_FRAME_GameSettingBgFrame s_CUI_ID_FRAME_GameSettingBgFrame;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GameSettingBgFrame, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GameSettingBgFrame, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameSettingBgFrame, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameSettingBgFrame, ID_BUTTON_CLOSEOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingBgFrame, ID_CHECKBOX_EffectOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingBgFrame, ID_CHECKBOX_GamePlayOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingBgFrame, ID_CHECKBOX_ShortcutKeyOnCheckBoxCheck )
CUI_ID_FRAME_GameSettingBgFrame::CUI_ID_FRAME_GameSettingBgFrame()
{
	// Member
	m_pID_FRAME_GameSettingBgFrame = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_CHECKBOX_Effect = NULL;
	m_pID_CHECKBOX_GamePlay = NULL;
	m_pID_CHECKBOX_ShortcutKey = NULL;
	m_pID_PICTURE_GamePlay = NULL;
	m_pID_PICTURE_ShortcutKey = NULL;
	m_pID_PICTURE_Effect = NULL;
}
// Frame
bool CUI_ID_FRAME_GameSettingBgFrame::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_GameSettingBgFrame::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_GameSettingBgFrame::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GameSettingBgFrame )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_GameSettingBgFrame::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GameSettingBgFrame )
		return false;
	return true;
}
// CheckBox
void CUI_ID_FRAME_GameSettingBgFrame::ID_CHECKBOX_EffectOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_GameSettingBgFrame )
		return;
	m_pID_CHECKBOX_Effect->SetCheck(true);
	m_pID_CHECKBOX_GamePlay->SetCheck(false);
	m_pID_CHECKBOX_ShortcutKey->SetCheck(false);
	s_CUI_ID_FRAME_SettingEffect.SetVisable(true);
	s_CUI_ID_FRAME_GameSetup.SetVisable(false);
	s_CUI_ID_FRAME_custom.SetVisable(false);
	m_pID_PICTURE_GamePlay->SetVisable(false);
	m_pID_PICTURE_ShortcutKey->SetVisable(false);
	m_pID_PICTURE_Effect->SetVisable(true);

}
// CheckBox
void CUI_ID_FRAME_GameSettingBgFrame::ID_CHECKBOX_GamePlayOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_GameSettingBgFrame )
		return;
	m_pID_CHECKBOX_Effect->SetCheck(false);
	m_pID_CHECKBOX_GamePlay->SetCheck(true);
	m_pID_CHECKBOX_ShortcutKey->SetCheck(false);
	s_CUI_ID_FRAME_SettingEffect.SetVisable(false);
	s_CUI_ID_FRAME_GameSetup.SetVisable(true);
	s_CUI_ID_FRAME_custom.SetVisable(false);
	m_pID_PICTURE_GamePlay->SetVisable(true);
	m_pID_PICTURE_ShortcutKey->SetVisable(false);
	m_pID_PICTURE_Effect->SetVisable(false);

}
// CheckBox
void CUI_ID_FRAME_GameSettingBgFrame::ID_CHECKBOX_ShortcutKeyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_GameSettingBgFrame )
		return;
	m_pID_CHECKBOX_Effect->SetCheck(false);
	m_pID_CHECKBOX_GamePlay->SetCheck(false);
	m_pID_CHECKBOX_ShortcutKey->SetCheck(true);
	s_CUI_ID_FRAME_SettingEffect.SetVisable(false);
	s_CUI_ID_FRAME_GameSetup.SetVisable(false);
	s_CUI_ID_FRAME_custom.SetVisable(true);
	m_pID_PICTURE_GamePlay->SetVisable(false);
	m_pID_PICTURE_ShortcutKey->SetVisable(true);
	m_pID_PICTURE_Effect->SetVisable(false);

}

// 装载UI
bool CUI_ID_FRAME_GameSettingBgFrame::_LoadUI()
{
	s_CUI_ID_FRAME_custom._LoadUI();
	s_CUI_ID_FRAME_SettingEffect._LoadUI();
	s_CUI_ID_FRAME_GameSetup._LoadUI();
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GameSettingBgFrame.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GameSettingBgFrame.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GameSettingBgFrame::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GameSettingBgFrame, s_CUI_ID_FRAME_GameSettingBgFrameOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GameSettingBgFrame, s_CUI_ID_FRAME_GameSettingBgFrameOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GameSettingBgFrame, ID_BUTTON_HELP, s_CUI_ID_FRAME_GameSettingBgFrameID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GameSettingBgFrame, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_GameSettingBgFrameID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingBgFrame, ID_CHECKBOX_Effect, s_CUI_ID_FRAME_GameSettingBgFrameID_CHECKBOX_EffectOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingBgFrame, ID_CHECKBOX_GamePlay, s_CUI_ID_FRAME_GameSettingBgFrameID_CHECKBOX_GamePlayOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingBgFrame, ID_CHECKBOX_ShortcutKey, s_CUI_ID_FRAME_GameSettingBgFrameID_CHECKBOX_ShortcutKeyOnCheckBoxCheck );

	m_pID_FRAME_GameSettingBgFrame = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GameSettingBgFrame );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameSettingBgFrame, ID_BUTTON_HELP );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameSettingBgFrame, ID_BUTTON_CLOSE );
	m_pID_CHECKBOX_Effect = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingBgFrame, ID_CHECKBOX_Effect );
	m_pID_CHECKBOX_GamePlay = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingBgFrame, ID_CHECKBOX_GamePlay );
	m_pID_CHECKBOX_ShortcutKey = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingBgFrame, ID_CHECKBOX_ShortcutKey );
	m_pID_PICTURE_GamePlay = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingBgFrame, ID_PICTURE_GamePlay );
	m_pID_PICTURE_ShortcutKey = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingBgFrame, ID_PICTURE_ShortcutKey );
	m_pID_PICTURE_Effect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingBgFrame, ID_PICTURE_Effect );

	assert( m_pID_FRAME_GameSettingBgFrame );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_CHECKBOX_Effect );
	assert( m_pID_CHECKBOX_GamePlay );
	assert( m_pID_CHECKBOX_ShortcutKey );
	assert( m_pID_PICTURE_GamePlay );
	assert( m_pID_PICTURE_ShortcutKey );
	assert( m_pID_PICTURE_Effect );
	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GameSettingBgFrame::_UnLoadUI()
{
	s_CUI_ID_FRAME_custom._UnLoadUI();
	s_CUI_ID_FRAME_SettingEffect._UnLoadUI();
	s_CUI_ID_FRAME_GameSetup._UnLoadUI();
	m_pID_FRAME_GameSettingBgFrame = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_CHECKBOX_Effect = NULL;
	m_pID_CHECKBOX_GamePlay = NULL;
	m_pID_CHECKBOX_ShortcutKey = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GameSettingBgFrame.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GameSettingBgFrame::_IsVisable()
{
	if ( !m_pID_FRAME_GameSettingBgFrame )
		return false;
	return m_pID_FRAME_GameSettingBgFrame->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GameSettingBgFrame::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_GameSettingBgFrame )
		return ;
	m_pID_FRAME_GameSettingBgFrame->SetVisable( bVisable );
	if (bVisable)
	{
		s_CUI_ID_FRAME_SettingEffect.SetVisable(true);
		s_CUI_ID_FRAME_GameSetup.SetVisable(false);
		s_CUI_ID_FRAME_custom.SetVisable(false);
		m_pID_PICTURE_GamePlay->SetVisable(false);
		m_pID_PICTURE_ShortcutKey->SetVisable(false);
		m_pID_PICTURE_Effect->SetVisable(true);
		m_pID_CHECKBOX_Effect->SetCheck(true);
		m_pID_CHECKBOX_GamePlay->SetCheck(false);
		m_pID_CHECKBOX_ShortcutKey->SetCheck(false);
	}
	
}
void CUI_ID_FRAME_GameSettingBgFrame::InitializeAtEnterWorld()
{
	SetVisable(false);
}