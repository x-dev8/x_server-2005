/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\GroupPanel.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GroupPanel.h"
#include "GroupPanel_CityPlayer.h"
#include "GroupPanel_NearPlayer.h"
#include "GroupPanel_Team.h"
#include "Task.h"
#include "Compound.h"
#include "Gang.h"
CUI_ID_FRAME_GroupPanel s_CUI_ID_FRAME_GroupPanel;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GroupPanel, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GroupPanel, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GroupPanel, ID_CHECKBOX_FujinOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GroupPanel, ID_CHECKBOX_XunzhaoOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GroupPanel, ID_CHECKBOX_TongchenOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GroupPanel, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GroupPanel, ID_BUTTON_helpOnButtonClick )
CUI_ID_FRAME_GroupPanel::CUI_ID_FRAME_GroupPanel()
{
	// Member
	m_pID_FRAME_GroupPanel = NULL;
	m_pID_PICTURE_Di = NULL;
	m_pID_PICTURE_Title = NULL;
	m_pID_PICTURE_Fenge = NULL;
	m_pID_CHECKBOX_Fujin = NULL;
	m_pID_CHECKBOX_Xunzhao = NULL;
	m_pID_CHECKBOX_Tongchen = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_help = NULL;

}
// Frame
bool CUI_ID_FRAME_GroupPanel::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GroupPanel::OnFrameRender()
{
	return true;
}
// CheckBox
void CUI_ID_FRAME_GroupPanel::ID_CHECKBOX_FujinOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_GroupPanel)
		return;
	m_optionGroup.ToggleRadio(m_pID_CHECKBOX_Fujin);
	OnVisibleChanged(0);
}
// CheckBox
void CUI_ID_FRAME_GroupPanel::ID_CHECKBOX_XunzhaoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_GroupPanel)
		return;
	m_optionGroup.ToggleRadio(m_pID_CHECKBOX_Xunzhao);
	OnVisibleChanged(0);
}
// CheckBox
void CUI_ID_FRAME_GroupPanel::ID_CHECKBOX_TongchenOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_GroupPanel)
		return;
	m_optionGroup.ToggleRadio(m_pID_CHECKBOX_Tongchen);
	OnVisibleChanged(0);
}
// Button
bool CUI_ID_FRAME_GroupPanel::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GroupPanel)
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_GroupPanel::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GroupPanel)
		return false;
	return true;
}

// 装载UI
bool CUI_ID_FRAME_GroupPanel::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GroupPanel.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GroupPanel.MEUI]失败")
			return false;
	}

	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GroupPanel::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GroupPanel, s_CUI_ID_FRAME_GroupPanelOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GroupPanel, s_CUI_ID_FRAME_GroupPanelOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GroupPanel, ID_CHECKBOX_Fujin, s_CUI_ID_FRAME_GroupPanelID_CHECKBOX_FujinOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GroupPanel, ID_CHECKBOX_Xunzhao, s_CUI_ID_FRAME_GroupPanelID_CHECKBOX_XunzhaoOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GroupPanel, ID_CHECKBOX_Tongchen, s_CUI_ID_FRAME_GroupPanelID_CHECKBOX_TongchenOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_GroupPanel, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_GroupPanelID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GroupPanel, ID_BUTTON_help, s_CUI_ID_FRAME_GroupPanelID_BUTTON_helpOnButtonClick );

	m_pID_FRAME_GroupPanel = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GroupPanel );
	m_pID_PICTURE_Di = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GroupPanel, ID_PICTURE_Di );
	m_pID_PICTURE_Title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GroupPanel, ID_PICTURE_Title );
	m_pID_PICTURE_Fenge = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GroupPanel, ID_PICTURE_Fenge );
	m_pID_CHECKBOX_Fujin = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GroupPanel, ID_CHECKBOX_Fujin );
	m_pID_CHECKBOX_Xunzhao = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GroupPanel, ID_CHECKBOX_Xunzhao );
	m_pID_CHECKBOX_Tongchen = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GroupPanel, ID_CHECKBOX_Tongchen );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GroupPanel, ID_BUTTON_CLOSE );
	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_GroupPanel, ID_BUTTON_help );
	assert( m_pID_FRAME_GroupPanel );
	assert( m_pID_PICTURE_Di );
	assert( m_pID_PICTURE_Title );
	assert( m_pID_PICTURE_Fenge );
	assert( m_pID_CHECKBOX_Fujin );
	assert( m_pID_CHECKBOX_Xunzhao );
	assert( m_pID_CHECKBOX_Tongchen );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_help );

	m_pID_FRAME_GroupPanel->SetOnVisibleChangedFun(OnVisibleChanged);

	m_optionGroup.AddRadio(m_pID_CHECKBOX_Fujin);
	m_optionGroup.AddRadio(m_pID_CHECKBOX_Xunzhao);
	m_optionGroup.AddRadio(m_pID_CHECKBOX_Tongchen);
	m_optionGroup.ToggleRadio(m_pID_CHECKBOX_Fujin);

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GroupPanel::_UnLoadUI()
{
	m_optionGroup.Clear();
	m_pID_FRAME_GroupPanel = NULL;
	m_pID_PICTURE_Di = NULL;
	m_pID_PICTURE_Title = NULL;
	m_pID_PICTURE_Fenge = NULL;
	m_pID_CHECKBOX_Fujin = NULL;
	m_pID_CHECKBOX_Xunzhao = NULL;
	m_pID_CHECKBOX_Tongchen = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_help = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GroupPanel.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GroupPanel::_IsVisable()
{
    if(!m_pID_FRAME_GroupPanel)
        return false;

	return m_pID_FRAME_GroupPanel->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GroupPanel::_SetVisable( const bool bVisable )
{
    if(!m_pID_FRAME_GroupPanel)
        return;

	m_pID_FRAME_GroupPanel->SetVisable( bVisable );
}

void CUI_ID_FRAME_GroupPanel::OnVisibleChanged(ControlObject* pUIObject)
{
	s_CUI_ID_FRAME_GroupPanel_NearPlayer.SetVisable(false);
	if (s_CUI_ID_FRAME_GroupPanel.m_optionGroup.GetSelectRadio() == s_CUI_ID_FRAME_GroupPanel.m_pID_CHECKBOX_Fujin)
		s_CUI_ID_FRAME_GroupPanel_NearPlayer.SetVisable(s_CUI_ID_FRAME_GroupPanel.IsVisable());
}
