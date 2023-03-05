/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (13)\FamilyUI\FamilyLogo.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "FamilyLogo.h"
//#include "FamilyMessageBox.h"
#include "FamilyCreate.h"
#include "FamilyDefine.h"

#include "FamilyTenet.h"


CUI_ID_FRAME_FamilyLogo s_CUI_ID_FRAME_FamilyLogo;
MAP_FRAME_RUN( s_CUI_ID_FRAME_FamilyLogo, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_FamilyLogo, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FamilyLogo, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FamilyLogo, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FamilyLogo, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FamilyLogo, ID_BUTTON_SureOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo01OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo02OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo03OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo04OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo05OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo06OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo07OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo08OnCheckBoxCheck )
CUI_ID_FRAME_FamilyLogo::CUI_ID_FRAME_FamilyLogo()
{
	// Member
	m_pID_FRAME_FamilyLogo = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Sure = NULL;
	m_pID_CHECKBOX_Logo01 = NULL;
	m_pID_CHECKBOX_Logo02 = NULL;
	m_pID_CHECKBOX_Logo03 = NULL;
	m_pID_CHECKBOX_Logo04 = NULL;
	m_pID_CHECKBOX_Logo05 = NULL;
	m_pID_CHECKBOX_Logo06 = NULL;
	m_pID_CHECKBOX_Logo07 = NULL;
	m_pID_CHECKBOX_Logo08 = NULL;

}
// Frame
bool CUI_ID_FRAME_FamilyLogo::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_FamilyLogo::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_FamilyLogo::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_FamilyLogo )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_FamilyLogo::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_FamilyLogo )
		return false;
	return true;
}
// Button   取消
bool CUI_ID_FRAME_FamilyLogo::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_FamilyLogo )
		return false;
	s_CUI_ID_FRAME_FamilyLogo.SetVisable(false);
	return true;
}
// Button 确定
bool CUI_ID_FRAME_FamilyLogo::ID_BUTTON_SureOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_FamilyLogo )
		return false;
	//s_CUI_ID_FRAME_GUILD_FamilyTenet.SetVisable(true);
	s_CUI_ID_FRAME_Family_Create.RequestCreateFamily();
	//s_CUI_ID_FRAME_FamilyLogo.SetVisable(false);
	this->SetVisable(false);
	return true;
}
// CheckBox
void CUI_ID_FRAME_FamilyLogo::ID_CHECKBOX_Logo01OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_FamilyLogo )
		return;
	s_CUI_ID_FRAME_Family_Create.SetFamilyTotem( FamilyDefine::Totem_Human );
	m_pID_BUTTON_Sure->SetEnable(true);

	UncheckedAll();
	((ControlCheckBox*)pSender)->SetCheck(true);
}
// CheckBox
void CUI_ID_FRAME_FamilyLogo::ID_CHECKBOX_Logo02OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_FamilyLogo )
		return;
	s_CUI_ID_FRAME_Family_Create.SetFamilyTotem( FamilyDefine::Totem_Machine );
	m_pID_BUTTON_Sure->SetEnable(true);

	UncheckedAll();
	((ControlCheckBox*)pSender)->SetCheck(true);
}
// CheckBox
void CUI_ID_FRAME_FamilyLogo::ID_CHECKBOX_Logo03OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_FamilyLogo )
		return;
	s_CUI_ID_FRAME_Family_Create.SetFamilyTotem( FamilyDefine::Totem_Monster );
	m_pID_BUTTON_Sure->SetEnable(true);

	UncheckedAll();
	((ControlCheckBox*)pSender)->SetCheck(true);
}
// CheckBox
void CUI_ID_FRAME_FamilyLogo::ID_CHECKBOX_Logo04OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_FamilyLogo )
		return;
	s_CUI_ID_FRAME_Family_Create.SetFamilyTotem( FamilyDefine::Totem_Immortal );
	m_pID_BUTTON_Sure->SetEnable(true);

	UncheckedAll();
	((ControlCheckBox*)pSender)->SetCheck(true);
}
// CheckBox
void CUI_ID_FRAME_FamilyLogo::ID_CHECKBOX_Logo05OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_FamilyLogo )
		return;
	s_CUI_ID_FRAME_Family_Create.SetFamilyTotem( FamilyDefine::Totem_Ghost );
	m_pID_BUTTON_Sure->SetEnable(true);

	UncheckedAll();
	((ControlCheckBox*)pSender)->SetCheck(true);
}
// CheckBox
void CUI_ID_FRAME_FamilyLogo::ID_CHECKBOX_Logo06OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_FamilyLogo )
		return;
	s_CUI_ID_FRAME_Family_Create.SetFamilyTotem( FamilyDefine::Totem_Goblin );
	m_pID_BUTTON_Sure->SetEnable(true);

	UncheckedAll();
	((ControlCheckBox*)pSender)->SetCheck(true);
}
// CheckBox
void CUI_ID_FRAME_FamilyLogo::ID_CHECKBOX_Logo07OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_FamilyLogo )
		return;
	s_CUI_ID_FRAME_Family_Create.SetFamilyTotem( FamilyDefine::Totem_God );
	m_pID_BUTTON_Sure->SetEnable(true);

	UncheckedAll();
	((ControlCheckBox*)pSender)->SetCheck(true);
}
// CheckBox
void CUI_ID_FRAME_FamilyLogo::ID_CHECKBOX_Logo08OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_FamilyLogo )
		return;
	s_CUI_ID_FRAME_Family_Create.SetFamilyTotem( FamilyDefine::Totem_Demon );
	m_pID_BUTTON_Sure->SetEnable(true);

	UncheckedAll();
	((ControlCheckBox*)pSender)->SetCheck(true);
}

void CUI_ID_FRAME_FamilyLogo::UncheckedAll()
{
	m_pID_CHECKBOX_Logo01->SetCheck(false);
	m_pID_CHECKBOX_Logo02->SetCheck(false);
	m_pID_CHECKBOX_Logo03->SetCheck(false);
	m_pID_CHECKBOX_Logo04->SetCheck(false);
	m_pID_CHECKBOX_Logo05->SetCheck(false);
	m_pID_CHECKBOX_Logo06->SetCheck(false);
	m_pID_CHECKBOX_Logo07->SetCheck(false);
	m_pID_CHECKBOX_Logo08->SetCheck(false);
}

// 装载UI
bool CUI_ID_FRAME_FamilyLogo::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\FamilyLogo.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\FamilyLogo.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_FamilyLogo::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_FamilyLogo, s_CUI_ID_FRAME_FamilyLogoOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_FamilyLogo, s_CUI_ID_FRAME_FamilyLogoOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_FamilyLogo, ID_BUTTON_HELP, s_CUI_ID_FRAME_FamilyLogoID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_FamilyLogo, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_FamilyLogoID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_FamilyLogo, ID_BUTTON_Cancel, s_CUI_ID_FRAME_FamilyLogoID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_FamilyLogo, ID_BUTTON_Sure, s_CUI_ID_FRAME_FamilyLogoID_BUTTON_SureOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo01, s_CUI_ID_FRAME_FamilyLogoID_CHECKBOX_Logo01OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo02, s_CUI_ID_FRAME_FamilyLogoID_CHECKBOX_Logo02OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo03, s_CUI_ID_FRAME_FamilyLogoID_CHECKBOX_Logo03OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo04, s_CUI_ID_FRAME_FamilyLogoID_CHECKBOX_Logo04OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo05, s_CUI_ID_FRAME_FamilyLogoID_CHECKBOX_Logo05OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo06, s_CUI_ID_FRAME_FamilyLogoID_CHECKBOX_Logo06OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo07, s_CUI_ID_FRAME_FamilyLogoID_CHECKBOX_Logo07OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo08, s_CUI_ID_FRAME_FamilyLogoID_CHECKBOX_Logo08OnCheckBoxCheck );

	m_pID_FRAME_FamilyLogo = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_FamilyLogo );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_FamilyLogo, ID_BUTTON_HELP );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_FamilyLogo, ID_BUTTON_CLOSE );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_FamilyLogo, ID_BUTTON_Cancel );
	m_pID_BUTTON_Sure = (ControlButton*)theUiManager.FindControl( ID_FRAME_FamilyLogo, ID_BUTTON_Sure );
	m_pID_CHECKBOX_Logo01 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo01 );
	m_pID_CHECKBOX_Logo02 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo02 );
	m_pID_CHECKBOX_Logo03 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo03 );
	m_pID_CHECKBOX_Logo04 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo04 );
	m_pID_CHECKBOX_Logo05 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo05 );
	m_pID_CHECKBOX_Logo06 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo06 );
	m_pID_CHECKBOX_Logo07 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo07 );
	m_pID_CHECKBOX_Logo08 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_FamilyLogo, ID_CHECKBOX_Logo08 );

	assert( m_pID_FRAME_FamilyLogo );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_Sure );
	assert( m_pID_CHECKBOX_Logo01 );
	assert( m_pID_CHECKBOX_Logo02 );
	assert( m_pID_CHECKBOX_Logo03 );
	assert( m_pID_CHECKBOX_Logo04 );
	assert( m_pID_CHECKBOX_Logo05 );
	assert( m_pID_CHECKBOX_Logo06 );
	assert( m_pID_CHECKBOX_Logo07 );
	assert( m_pID_CHECKBOX_Logo08 );

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_FamilyLogo::_UnLoadUI()
{
	m_pID_FRAME_FamilyLogo = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Sure = NULL;
	m_pID_CHECKBOX_Logo01 = NULL;
	m_pID_CHECKBOX_Logo02 = NULL;
	m_pID_CHECKBOX_Logo03 = NULL;
	m_pID_CHECKBOX_Logo04 = NULL;
	m_pID_CHECKBOX_Logo05 = NULL;
	m_pID_CHECKBOX_Logo06 = NULL;
	m_pID_CHECKBOX_Logo07 = NULL;
	m_pID_CHECKBOX_Logo08 = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\FamilyLogo.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_FamilyLogo::_IsVisable()
{
	if ( !m_pID_FRAME_FamilyLogo )
		return false;
	return m_pID_FRAME_FamilyLogo->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_FamilyLogo::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_FamilyLogo )
		return;
	m_pID_FRAME_FamilyLogo->SetVisable( bVisable );
	if ( bVisable )
	{
		m_pID_BUTTON_Sure->SetEnable(false);  //必须选择了图腾后才可以进行下一步
		UncheckedAll();
	}
	
}
