/********************************************************************
Created by UIEditor.exe
FileName: D:\Client\UI\SelectAssignMode.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SelectAssignMode.h"
#include "FuncPerformanceLog.h"
#include "Group_Me.h"
#include "SelfRbtnMenu.h"
#include "NetworkInput.h"
#include "ChatInfoBox.h"
#include "PlayerRole.h"
#include "XmlStringLanguage.h"
#include "core/Name.h"

const clock_t	TM_CHANGE_ASSIGN_MODE_COLOD = 15*1000;

CUI_ID_FRAME_SelectAssignMode s_CUI_ID_FRAME_SelectAssignMode;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SelectAssignMode, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SelectAssignMode, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelectAssignMode, ID_BUTTON_FreedomOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelectAssignMode, ID_BUTTON_TeamOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelectAssignMode, ID_BUTTON_RandomOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelectAssignMode, ID_BUTTON_AssignOnButtonClick )
CUI_ID_FRAME_SelectAssignMode::CUI_ID_FRAME_SelectAssignMode()
{
	guardfunc;
	// SGuildMember
	m_pID_FRAME_SelectAssignMode = NULL;
	m_pID_BUTTON_Freedom = NULL;
	m_pID_BUTTON_Team = NULL;
	m_pID_BUTTON_Random = NULL;
	m_pID_BUTTON_Assign = NULL;

	tmChangeAssignModeStart = 0;

	m_pID_PIC_Tuan = NULL;
	m_pID_PIC_Dui = NULL;
	unguard;
}
// Frame
bool CUI_ID_FRAME_SelectAssignMode::OnFrameRun()
{
	guardfunc;
	return true;
	unguard;
}
bool CUI_ID_FRAME_SelectAssignMode::OnFrameRender()
{
	guardfunc;
	
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_SelectAssignMode::ID_BUTTON_FreedomOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_SelectAssignMode )
		return false;
	send_Change_AssignMode( AssignMode_FreeMode);
	SetVisable( false );
	s_CUI_ID_FRAME_SelfRBMenu.SetVisable( false );
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_SelectAssignMode::ID_BUTTON_TeamOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_SelectAssignMode )
		return false;
	send_Change_AssignMode( AssignMode_Team );
	SetVisable( false );
	s_CUI_ID_FRAME_SelfRBMenu.SetVisable( false );
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_SelectAssignMode::ID_BUTTON_RandomOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_SelectAssignMode )
		return false;
	send_Change_AssignMode( AssignMode_Random );
	SetVisable( false );
	s_CUI_ID_FRAME_SelfRBMenu.SetVisable( false );
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_SelectAssignMode::ID_BUTTON_AssignOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_SelectAssignMode )
		return false;
	send_Change_AssignMode( AssignMode_Assign );
	SetVisable( false );
	s_CUI_ID_FRAME_SelfRBMenu.SetVisable( false );
	return true;
	unguard;
}
void CUI_ID_FRAME_SelectAssignMode::send_Change_AssignMode( unsigned char mode)
{
	guardfunc;
	MsgReqChangeAssignMode msg;
	msg.AssignMode = mode;
	GettheNetworkInput().SendMsg( &msg );

	unguard;
}
// 装载UI
bool CUI_ID_FRAME_SelectAssignMode::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\SelectAssignMode.meui", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\SelectAssignMode.UI]失败")
			return false;
	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_SelectAssignMode::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_SelectAssignMode, s_CUI_ID_FRAME_SelectAssignModeOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SelectAssignMode, s_CUI_ID_FRAME_SelectAssignModeOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_SelectAssignMode, ID_BUTTON_Freedom, s_CUI_ID_FRAME_SelectAssignModeID_BUTTON_FreedomOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SelectAssignMode, ID_BUTTON_Team, s_CUI_ID_FRAME_SelectAssignModeID_BUTTON_TeamOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SelectAssignMode, ID_BUTTON_Random, s_CUI_ID_FRAME_SelectAssignModeID_BUTTON_RandomOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SelectAssignMode, ID_BUTTON_Assign, s_CUI_ID_FRAME_SelectAssignModeID_BUTTON_AssignOnButtonClick );

	m_pID_FRAME_SelectAssignMode = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SelectAssignMode );
	m_pID_BUTTON_Freedom = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelectAssignMode, ID_BUTTON_Freedom );
	m_pID_BUTTON_Team = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelectAssignMode, ID_BUTTON_Team );
	m_pID_BUTTON_Random = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelectAssignMode, ID_BUTTON_Random );
	m_pID_BUTTON_Assign = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelectAssignMode, ID_BUTTON_Assign );
	assert( m_pID_FRAME_SelectAssignMode );
	m_pID_FRAME_SelectAssignMode->SetVisable(false);
	assert( m_pID_BUTTON_Freedom );
	assert( m_pID_BUTTON_Team );
	assert( m_pID_BUTTON_Random );
	assert( m_pID_BUTTON_Assign );

	m_pID_PIC_Freedom = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SelectAssignMode, ID_PICTURE_Freedom );
	assert( m_pID_PIC_Freedom );
	m_pID_PIC_Team = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SelectAssignMode, ID_PICTURE_Team );
	assert( m_pID_PIC_Team );
	m_pID_PIC_Random = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SelectAssignMode, ID_PICTURE_Random );
	assert( m_pID_PIC_Random );
	m_pID_PIC_Assign = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SelectAssignMode, ID_PICTURE_Assign );
	assert( m_pID_PIC_Assign );

	m_pID_PIC_Tuan = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SelectAssignMode, ID_PICTURE_Tuan );
	m_pID_PIC_Dui = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SelectAssignMode, ID_PICTURE_Dui );

	return true;
	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_SelectAssignMode::_UnLoadUI()
{
	guardfunc;
	m_pID_FRAME_SelectAssignMode = NULL;
	m_pID_BUTTON_Freedom = NULL;
	m_pID_BUTTON_Team = NULL;
	m_pID_BUTTON_Random = NULL;
	m_pID_BUTTON_Assign = NULL;

	tmChangeAssignModeStart = 0;

	m_pID_PIC_Tuan = NULL;
	m_pID_PIC_Dui = NULL;
	return theUiManager.RemoveFrame( "data\\ui\\SelectAssignMode.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_SelectAssignMode::_IsVisable()
{
	guardfunc;
	if( !m_pID_FRAME_SelectAssignMode )
		return false;
	return m_pID_FRAME_SelectAssignMode->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_SelectAssignMode::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pID_FRAME_SelectAssignMode )
		return;
	m_pID_FRAME_SelectAssignMode->SetVisable( bVisable );

	m_pID_PIC_Freedom->SetVisable(false);	
	m_pID_PIC_Team->SetVisable(false);
	m_pID_PIC_Random->SetVisable(false);	
	m_pID_PIC_Assign->SetVisable(false);


	if( m_pID_PIC_Tuan && m_pID_PIC_Dui )
	{

		m_pID_PIC_Tuan->SetVisable( false );
		m_pID_PIC_Dui->SetVisable( false );
		if( thePlayerRole.m_bCorps )
			m_pID_PIC_Tuan->SetVisable( true );
		else
			m_pID_PIC_Dui->SetVisable( true );
	}


	switch( thePlayerRole.GetAssignMode() )
	{
	case AssignMode_FreeMode:
		m_pID_PIC_Freedom->SetVisable(true);
		break;
	case AssignMode_Team:
		m_pID_PIC_Team->SetVisable(true);
		break;
	case AssignMode_Random:
		m_pID_PIC_Random->SetVisable(true);
		break;
	case AssignMode_Assign:
		m_pID_PIC_Assign->SetVisable(true);
		break;
	}

	unguard;
}
