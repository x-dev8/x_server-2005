/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\GroupPanel_Team.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GroupPanel_Team.h"
#include "GroupPanel.h"

CUI_ID_FRAME_GroupPanel_Team s_CUI_ID_FRAME_GroupPanel_Team;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GroupPanel_Team, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GroupPanel_Team, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GroupPanel_Team, ID_LIST_PlayerOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GroupPanel_Team, ID_BUTTON_JiaruOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GroupPanel_Team, ID_BUTTON_TuichuOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GroupPanel_Team, ID_LIST_TeamPlayerOnListSelectChange )
CUI_ID_FRAME_GroupPanel_Team::CUI_ID_FRAME_GroupPanel_Team()
{
	// Member
	m_pID_FRAME_GroupPanel_Team = NULL;
	m_pID_LIST_Player = NULL;
	m_pID_BUTTON_Jiaru = NULL;
	m_pID_BUTTON_Tuichu = NULL;
	m_pID_LIST_TeamPlayer = NULL;
	m_pID_TEXT_TeamName = NULL;
	m_pID_TEXT_Leader = NULL;
	m_pID_TEXT_LeaderLvl = NULL;
	m_pID_PICTURE_Henxian = NULL;
	m_pID_PICTURE_Henxian2 = NULL;
	m_pID_TEXT_TeamMate = NULL;
	m_pID_TEXT_TeamMateLvl = NULL;
	m_pID_TEXT_TeamMateJob = NULL;
	m_pID_TEXT_TeamNum = NULL;

}
// Frame
bool CUI_ID_FRAME_GroupPanel_Team::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GroupPanel_Team::OnFrameRender()
{
	return true;
}
// List
void CUI_ID_FRAME_GroupPanel_Team::ID_LIST_PlayerOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_GroupPanel_Team)
		return;
}
// Button
bool CUI_ID_FRAME_GroupPanel_Team::ID_BUTTON_JiaruOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GroupPanel_Team)
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_GroupPanel_Team::ID_BUTTON_TuichuOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GroupPanel_Team)
		return false;
	return true;
}
// List
void CUI_ID_FRAME_GroupPanel_Team::ID_LIST_TeamPlayerOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_GroupPanel_Team)
		return;
}

static void GP_OnVisibleChanged(ControlObject* pSender)
{
	if (!pSender->IsVisable() && pSender->GetFather() && pSender->GetFather()->IsVisable() && 
		s_CUI_ID_FRAME_GroupPanel.GetGroupSelect() == s_CUI_ID_FRAME_GroupPanel.GetCheckBoxXunZhao())
		pSender->SetVisable(true);
}

// 装载UI
bool CUI_ID_FRAME_GroupPanel_Team::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GroupPanel_Team.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GroupPanel_Team.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GroupPanel_Team::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GroupPanel_Team, s_CUI_ID_FRAME_GroupPanel_TeamOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GroupPanel_Team, s_CUI_ID_FRAME_GroupPanel_TeamOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_GroupPanel_Team, ID_LIST_Player, s_CUI_ID_FRAME_GroupPanel_TeamID_LIST_PlayerOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_GroupPanel_Team, ID_BUTTON_Jiaru, s_CUI_ID_FRAME_GroupPanel_TeamID_BUTTON_JiaruOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GroupPanel_Team, ID_BUTTON_Tuichu, s_CUI_ID_FRAME_GroupPanel_TeamID_BUTTON_TuichuOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_GroupPanel_Team, ID_LIST_TeamPlayer, s_CUI_ID_FRAME_GroupPanel_TeamID_LIST_TeamPlayerOnListSelectChange );

	m_pID_FRAME_GroupPanel_Team = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GroupPanel_Team );
	m_pID_LIST_Player = (ControlList*)theUiManager.FindControl( ID_FRAME_GroupPanel_Team, ID_LIST_Player );
	m_pID_BUTTON_Jiaru = (ControlButton*)theUiManager.FindControl( ID_FRAME_GroupPanel_Team, ID_BUTTON_Jiaru );
	m_pID_BUTTON_Tuichu = (ControlButton*)theUiManager.FindControl( ID_FRAME_GroupPanel_Team, ID_BUTTON_Tuichu );
	m_pID_LIST_TeamPlayer = (ControlList*)theUiManager.FindControl( ID_FRAME_GroupPanel_Team, ID_LIST_TeamPlayer );
	m_pID_TEXT_TeamName = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_Team, ID_TEXT_TeamName );
	m_pID_TEXT_Leader = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_Team, ID_TEXT_Leader );
	m_pID_TEXT_LeaderLvl = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_Team, ID_TEXT_LeaderLvl );
	m_pID_PICTURE_Henxian = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GroupPanel_Team, ID_PICTURE_Henxian );
	m_pID_PICTURE_Henxian2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GroupPanel_Team, ID_PICTURE_Henxian2 );
	m_pID_TEXT_TeamMate = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_Team, ID_TEXT_TeamMate );
	m_pID_TEXT_TeamMateLvl = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_Team, ID_TEXT_TeamMateLvl );
	m_pID_TEXT_TeamMateJob = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_Team, ID_TEXT_TeamMateJob );
	m_pID_TEXT_TeamNum = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_Team, ID_TEXT_TeamNum );
	assert( m_pID_FRAME_GroupPanel_Team );
	assert( m_pID_LIST_Player );
	assert( m_pID_BUTTON_Jiaru );
	assert( m_pID_BUTTON_Tuichu );
	assert( m_pID_LIST_TeamPlayer );
	assert( m_pID_TEXT_TeamName );
	assert( m_pID_TEXT_Leader );
	assert( m_pID_TEXT_LeaderLvl );
	assert( m_pID_PICTURE_Henxian );
	assert( m_pID_PICTURE_Henxian2 );
	assert( m_pID_TEXT_TeamMate );
	assert( m_pID_TEXT_TeamMateLvl );
	assert( m_pID_TEXT_TeamMateJob );
	assert( m_pID_TEXT_TeamNum );

	m_pID_FRAME_GroupPanel_Team->SetMsgHoldup(false);
	m_pID_FRAME_GroupPanel_Team->enableEscKey(false);
	m_pID_FRAME_GroupPanel_Team->SetOnVisibleChangedFun(GP_OnVisibleChanged);

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GroupPanel_Team::_UnLoadUI()
{
	m_pID_FRAME_GroupPanel_Team = NULL;
	m_pID_LIST_Player = NULL;
	m_pID_BUTTON_Jiaru = NULL;
	m_pID_BUTTON_Tuichu = NULL;
	m_pID_LIST_TeamPlayer = NULL;
	m_pID_TEXT_TeamName = NULL;
	m_pID_TEXT_Leader = NULL;
	m_pID_TEXT_LeaderLvl = NULL;
	m_pID_PICTURE_Henxian = NULL;
	m_pID_PICTURE_Henxian2 = NULL;
	m_pID_TEXT_TeamMate = NULL;
	m_pID_TEXT_TeamMateLvl = NULL;
	m_pID_TEXT_TeamMateJob = NULL;
	m_pID_TEXT_TeamNum = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GroupPanel_Team.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GroupPanel_Team::_IsVisable()
{
    if(!m_pID_FRAME_GroupPanel_Team)
        return false;

	return m_pID_FRAME_GroupPanel_Team->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GroupPanel_Team::_SetVisable( const bool bVisable )
{
    if(m_pID_FRAME_GroupPanel_Team)
	m_pID_FRAME_GroupPanel_Team->SetVisable( bVisable );
}
