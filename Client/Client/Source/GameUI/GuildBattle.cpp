/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\RTX\帮会战界面\GuildBattle.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GuildBattle.h"
#include "CampBattleMessage.h"
#include "NetworkInput.h"
#include "core/Name.h"
#include "XmlStringLanguage.h "
#include "Common.h"
#include "PlayerRole.h"
#include "Group_Me.h"

CUI_ID_FRAME_GuildBattle s_CUI_ID_FRAME_GuildBattle;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GuildBattle, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GuildBattle, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_BUTTON_Rank1OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_BUTTON_Name1OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_BUTTON_Level1OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_BUTTON_Job1OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_BUTTON_Kill1OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_BUTTON_Death1OnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_LIST_Rank1OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_LIST_Name1OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_LIST_Level1OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_LIST_Job1OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_LIST_Kill1OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_LIST_Death1OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_LIST_GuildBattle1OnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_BUTTON_Rank2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_BUTTON_Name2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_BUTTON_Level2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_BUTTON_Job2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_BUTTON_Kill2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_BUTTON_Death2OnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_LIST_Rank2OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_LIST_Name2OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_LIST_Level2OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_LIST_Job2OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_LIST_Kill2OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_LIST_Death2OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_LIST_GuildBattle2OnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_BUTTON_LeaveOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattle, ID_BUTTON_CancelOnButtonClick )
CUI_ID_FRAME_GuildBattle::CUI_ID_FRAME_GuildBattle()
{
	// Member
	m_pID_FRAME_GuildBattle = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_Rank1 = NULL;
	m_pID_BUTTON_Name1 = NULL;
	m_pID_BUTTON_Level1 = NULL;
	m_pID_BUTTON_Job1 = NULL;
	m_pID_BUTTON_Kill1 = NULL;
	m_pID_BUTTON_Death1 = NULL;
	m_pID_LIST_Rank1 = NULL;
	m_pID_LIST_Name1 = NULL;
	m_pID_LIST_Level1 = NULL;
	m_pID_LIST_Job1 = NULL;
	m_pID_LIST_Kill1 = NULL;
	m_pID_LIST_Death1 = NULL;
	m_pID_LIST_GuildBattle1 = NULL;
	m_pID_TEXT_ArrowLevel1 = NULL;
	m_pID_TEXT_ArrowKill1 = NULL;
	m_pID_TEXT_ArrowDeath1 = NULL;
	m_pID_TEXT_GuildName1 = NULL;
	m_pID_TEXT_Player1 = NULL;
	m_pID_TEXT_Score1 = NULL;
	m_pID_BUTTON_Rank2 = NULL;
	m_pID_BUTTON_Name2 = NULL;
	m_pID_BUTTON_Level2 = NULL;
	m_pID_BUTTON_Job2 = NULL;
	m_pID_BUTTON_Kill2 = NULL;
	m_pID_BUTTON_Death2 = NULL;
	m_pID_TEXT_ArrowLevel2 = NULL;
	m_pID_TEXT_ArrowKill2 = NULL;
	m_pID_TEXT_ArrowDeath2 = NULL;
	m_pID_LIST_Rank2 = NULL;
	m_pID_LIST_Name2 = NULL;
	m_pID_LIST_Level2 = NULL;
	m_pID_LIST_Job2 = NULL;
	m_pID_LIST_Kill2 = NULL;
	m_pID_LIST_Death2 = NULL;
	m_pID_LIST_GuildBattle2 = NULL;
	m_pID_TEXT_GuildName2 = NULL;
	m_pID_TEXT_Player2 = NULL;
	m_pID_TEXT_Score2 = NULL;
	m_pID_BUTTON_Leave = NULL;
	m_pID_BUTTON_Cancel = NULL;	
}

// Frame
bool CUI_ID_FRAME_GuildBattle::OnFrameRun()
{
	int nSelLastListShowHeight = 0;
	int nSelLastScrollBarShowHeight = 0;

	int nOtherLastListShowHeight = 0;
	int nOtherLastScrollBarShowHeight = 0;

	GetSelfListAndScrollBarShowHeight(nSelLastListShowHeight, nSelLastScrollBarShowHeight);
	GetOtherListAndScrollBarShowHeight(nOtherLastListShowHeight, nOtherLastScrollBarShowHeight);

	Refresh();

	SetSelfListAndScrollBarShowHeight(nSelLastListShowHeight, nSelLastScrollBarShowHeight);
	SetOtherListAndScrollBarShowHeight(nOtherLastListShowHeight, nOtherLastScrollBarShowHeight);	

	return true;
}

void CUI_ID_FRAME_GuildBattle::GetSelfListAndScrollBarShowHeight(int& nListHeight, int& nScrollBarHeight)
{
	if (!_IsVisable())
	{
		return;
	}

	nListHeight = m_pID_LIST_GuildBattle1->GetShowStartHeight();
	if (m_pID_LIST_GuildBattle1->GetScrollBar())
	{
		nScrollBarHeight = m_pID_LIST_GuildBattle1->GetScrollBar()->GetValue();
	}
}

void CUI_ID_FRAME_GuildBattle::GetOtherListAndScrollBarShowHeight(int& nListHeight, int& nScrollBarHeight)
{
	if (!_IsVisable())
	{
		return;
	}

	nListHeight = m_pID_LIST_GuildBattle2->GetShowStartHeight();
	if (m_pID_LIST_GuildBattle2->GetScrollBar())
	{
		nScrollBarHeight = m_pID_LIST_GuildBattle2->GetScrollBar()->GetValue();
	}
}

void CUI_ID_FRAME_GuildBattle::SetSelfListAndScrollBarShowHeight(int& nListHeight, int& nScrollBarHeight)
{
	if (!_IsVisable())
	{
		return;
	}

	m_pID_LIST_Rank1->SetShowStartHeight(nListHeight);
	m_pID_LIST_Name1->SetShowStartHeight(nListHeight);
	m_pID_LIST_Level1->SetShowStartHeight(nListHeight);
	m_pID_LIST_Job1->SetShowStartHeight(nListHeight);
	m_pID_LIST_Kill1->SetShowStartHeight(nListHeight);
	m_pID_LIST_Death1->SetShowStartHeight(nListHeight);
	m_pID_LIST_GuildBattle1->SetScrollValue(nScrollBarHeight);
}

void CUI_ID_FRAME_GuildBattle::SetOtherListAndScrollBarShowHeight(int& nListHeight, int& nScrollBarHeight)
{
	if (!_IsVisable())
	{
		return;
	}

	m_pID_LIST_Rank2->SetShowStartHeight(nListHeight);
	m_pID_LIST_Name2->SetShowStartHeight(nListHeight);
	m_pID_LIST_Level2->SetShowStartHeight(nListHeight);
	m_pID_LIST_Job2->SetShowStartHeight(nListHeight);
	m_pID_LIST_Kill2->SetShowStartHeight(nListHeight);
	m_pID_LIST_Death2->SetShowStartHeight(nListHeight);
	m_pID_LIST_GuildBattle2->SetScrollValue(nScrollBarHeight);
}

bool CUI_ID_FRAME_GuildBattle::OnFrameRender()
{
	return true;
}

// Button
bool CUI_ID_FRAME_GuildBattle::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattle )
		return false;
	return true;
}

// Button
bool CUI_ID_FRAME_GuildBattle::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattle )
		return false;
	return true;
}

// Button
bool CUI_ID_FRAME_GuildBattle::ID_BUTTON_Rank1OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattle )
		return false;
	return true;
}

// Button
bool CUI_ID_FRAME_GuildBattle::ID_BUTTON_Name1OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattle )
		return false;
	return true;
}

// Button
bool CUI_ID_FRAME_GuildBattle::ID_BUTTON_Job1OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattle )
		return false;
	return true;
}

// List
void CUI_ID_FRAME_GuildBattle::ID_LIST_Rank1OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_GuildBattle )
		return;
}
// List
void CUI_ID_FRAME_GuildBattle::ID_LIST_Name1OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_GuildBattle )
		return;
}

// List
void CUI_ID_FRAME_GuildBattle::ID_LIST_Level1OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_GuildBattle )
		return;
}

// List
void CUI_ID_FRAME_GuildBattle::ID_LIST_Job1OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_GuildBattle )
		return;
}

// List
void CUI_ID_FRAME_GuildBattle::ID_LIST_Kill1OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_GuildBattle )
		return;
}

// List
void CUI_ID_FRAME_GuildBattle::ID_LIST_Death1OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_GuildBattle )
		return;
}
// List
void CUI_ID_FRAME_GuildBattle::ID_LIST_GuildBattle1OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_GuildBattle )
		return;
}
// Button
bool CUI_ID_FRAME_GuildBattle::ID_BUTTON_Rank2OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattle )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_GuildBattle::ID_BUTTON_Name2OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattle )
		return false;
	return true;
}

// Button
bool CUI_ID_FRAME_GuildBattle::ID_BUTTON_Job2OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattle )
		return false;
	return true;
}

// List
void CUI_ID_FRAME_GuildBattle::ID_LIST_Rank2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_GuildBattle )
		return;
}
// List
void CUI_ID_FRAME_GuildBattle::ID_LIST_Name2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_GuildBattle )
		return;
}
// List
void CUI_ID_FRAME_GuildBattle::ID_LIST_Level2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_GuildBattle )
		return;
}
// List
void CUI_ID_FRAME_GuildBattle::ID_LIST_Job2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_GuildBattle )
		return;
}
// List
void CUI_ID_FRAME_GuildBattle::ID_LIST_Kill2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_GuildBattle )
		return;
}
// List
void CUI_ID_FRAME_GuildBattle::ID_LIST_Death2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_GuildBattle )
		return;
}
// List
void CUI_ID_FRAME_GuildBattle::ID_LIST_GuildBattle2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_GuildBattle )
		return;
}

// Button
bool CUI_ID_FRAME_GuildBattle::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattle )
		return false;

	_SetVisable(false);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_GuildBattle::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GuildBattle.MEUI", false, UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GuildBattle.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GuildBattle::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GuildBattle, s_CUI_ID_FRAME_GuildBattleOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GuildBattle, s_CUI_ID_FRAME_GuildBattleOnFrameRender);
	theUiManager.OnButtonClick( ID_FRAME_GuildBattle, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_GuildBattleID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattle, ID_BUTTON_HELP, s_CUI_ID_FRAME_GuildBattleID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattle, ID_BUTTON_Rank1, s_CUI_ID_FRAME_GuildBattleID_BUTTON_Rank1OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattle, ID_BUTTON_Name1, s_CUI_ID_FRAME_GuildBattleID_BUTTON_Name1OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattle, ID_BUTTON_Level1, s_CUI_ID_FRAME_GuildBattleID_BUTTON_Level1OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattle, ID_BUTTON_Job1, s_CUI_ID_FRAME_GuildBattleID_BUTTON_Job1OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattle, ID_BUTTON_Kill1, s_CUI_ID_FRAME_GuildBattleID_BUTTON_Kill1OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattle, ID_BUTTON_Death1, s_CUI_ID_FRAME_GuildBattleID_BUTTON_Death1OnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_GuildBattle, ID_LIST_Rank1, s_CUI_ID_FRAME_GuildBattleID_LIST_Rank1OnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildBattle, ID_LIST_Name1, s_CUI_ID_FRAME_GuildBattleID_LIST_Name1OnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildBattle, ID_LIST_Level1, s_CUI_ID_FRAME_GuildBattleID_LIST_Level1OnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildBattle, ID_LIST_Job1, s_CUI_ID_FRAME_GuildBattleID_LIST_Job1OnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildBattle, ID_LIST_Kill1, s_CUI_ID_FRAME_GuildBattleID_LIST_Kill1OnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildBattle, ID_LIST_Death1, s_CUI_ID_FRAME_GuildBattleID_LIST_Death1OnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildBattle, ID_LIST_GuildBattle1, s_CUI_ID_FRAME_GuildBattleID_LIST_GuildBattle1OnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattle, ID_BUTTON_Rank2, s_CUI_ID_FRAME_GuildBattleID_BUTTON_Rank2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattle, ID_BUTTON_Name2, s_CUI_ID_FRAME_GuildBattleID_BUTTON_Name2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattle, ID_BUTTON_Level2, s_CUI_ID_FRAME_GuildBattleID_BUTTON_Level2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattle, ID_BUTTON_Job2, s_CUI_ID_FRAME_GuildBattleID_BUTTON_Job2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattle, ID_BUTTON_Kill2, s_CUI_ID_FRAME_GuildBattleID_BUTTON_Kill2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattle, ID_BUTTON_Death2, s_CUI_ID_FRAME_GuildBattleID_BUTTON_Death2OnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_GuildBattle, ID_LIST_Rank2, s_CUI_ID_FRAME_GuildBattleID_LIST_Rank2OnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildBattle, ID_LIST_Name2, s_CUI_ID_FRAME_GuildBattleID_LIST_Name2OnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildBattle, ID_LIST_Level2, s_CUI_ID_FRAME_GuildBattleID_LIST_Level2OnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildBattle, ID_LIST_Job2, s_CUI_ID_FRAME_GuildBattleID_LIST_Job2OnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildBattle, ID_LIST_Kill2, s_CUI_ID_FRAME_GuildBattleID_LIST_Kill2OnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildBattle, ID_LIST_Death2, s_CUI_ID_FRAME_GuildBattleID_LIST_Death2OnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildBattle, ID_LIST_GuildBattle2, s_CUI_ID_FRAME_GuildBattleID_LIST_GuildBattle2OnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattle, ID_BUTTON_Leave, s_CUI_ID_FRAME_GuildBattleID_BUTTON_LeaveOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattle, ID_BUTTON_Cancel, s_CUI_ID_FRAME_GuildBattleID_BUTTON_CancelOnButtonClick );

	m_pID_FRAME_GuildBattle = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GuildBattle );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_BUTTON_CLOSE );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_BUTTON_HELP );
	m_pID_BUTTON_Rank1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_BUTTON_Rank1 );
	m_pID_BUTTON_Name1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_BUTTON_Name1 );
	m_pID_BUTTON_Level1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_BUTTON_Level1 );
	m_pID_BUTTON_Job1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_BUTTON_Job1 );
	m_pID_BUTTON_Kill1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_BUTTON_Kill1 );
	m_pID_BUTTON_Death1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_BUTTON_Death1 );
	m_pID_LIST_Rank1 = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_LIST_Rank1 );
	m_pID_LIST_Name1 = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_LIST_Name1 );
	m_pID_LIST_Level1 = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_LIST_Level1 );
	m_pID_LIST_Job1 = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_LIST_Job1 );
	m_pID_LIST_Kill1 = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_LIST_Kill1 );
	m_pID_LIST_Death1 = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_LIST_Death1 );
	m_pID_LIST_GuildBattle1 = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_LIST_GuildBattle1 );
	m_pID_TEXT_ArrowLevel1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_TEXT_ArrowLevel1 );
	m_pID_TEXT_ArrowKill1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_TEXT_ArrowKill1 );
	m_pID_TEXT_ArrowDeath1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_TEXT_ArrowDeath1 );
	m_pID_TEXT_GuildName1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_TEXT_GuildName1 );
	m_pID_TEXT_Player1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_TEXT_Player1 );
	m_pID_TEXT_Score1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_TEXT_Score1 );
	m_pID_BUTTON_Rank2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_BUTTON_Rank2 );
	m_pID_BUTTON_Name2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_BUTTON_Name2 );
	m_pID_BUTTON_Level2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_BUTTON_Level2 );
	m_pID_BUTTON_Job2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_BUTTON_Job2 );
	m_pID_BUTTON_Kill2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_BUTTON_Kill2 );
	m_pID_BUTTON_Death2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_BUTTON_Death2 );
	m_pID_TEXT_ArrowLevel2 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_TEXT_ArrowLevel2 );
	m_pID_TEXT_ArrowKill2 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_TEXT_ArrowKill2 );
	m_pID_TEXT_ArrowDeath2 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_TEXT_ArrowDeath2 );
	m_pID_LIST_Rank2 = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_LIST_Rank2 );
	m_pID_LIST_Name2 = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_LIST_Name2 );
	m_pID_LIST_Level2 = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_LIST_Level2 );
	m_pID_LIST_Job2 = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_LIST_Job2 );
	m_pID_LIST_Kill2 = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_LIST_Kill2 );
	m_pID_LIST_Death2 = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_LIST_Death2 );
	m_pID_LIST_GuildBattle2 = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_LIST_GuildBattle2 );
	m_pID_TEXT_GuildName2 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_TEXT_GuildName2 );
	m_pID_TEXT_Player2 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_TEXT_Player2 );
	m_pID_TEXT_Score2 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_TEXT_Score2 );
	m_pID_BUTTON_Leave = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_BUTTON_Leave );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattle, ID_BUTTON_Cancel );

	assert( m_pID_FRAME_GuildBattle );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_Rank1 );
	assert( m_pID_BUTTON_Name1 );
	assert( m_pID_BUTTON_Level1 );
	assert( m_pID_BUTTON_Job1 );
	assert( m_pID_BUTTON_Kill1 );
	assert( m_pID_BUTTON_Death1 );
	assert( m_pID_LIST_Rank1 );
	assert( m_pID_LIST_Name1 );
	assert( m_pID_LIST_Level1 );
	assert( m_pID_LIST_Job1 );
	assert( m_pID_LIST_Kill1 );
	assert( m_pID_LIST_Death1 );
	assert( m_pID_LIST_GuildBattle1 );
	assert( m_pID_TEXT_ArrowLevel1 );
	assert( m_pID_TEXT_ArrowKill1 );
	assert( m_pID_TEXT_ArrowDeath1 );
	assert( m_pID_TEXT_GuildName1 );
	assert( m_pID_TEXT_Player1 );
	assert( m_pID_TEXT_Score1 );
	assert( m_pID_BUTTON_Rank2 );
	assert( m_pID_BUTTON_Name2 );
	assert( m_pID_BUTTON_Level2 );
	assert( m_pID_BUTTON_Job2 );
	assert( m_pID_BUTTON_Kill2 );
	assert( m_pID_BUTTON_Death2 );
	assert( m_pID_TEXT_ArrowLevel2 );
	assert( m_pID_TEXT_ArrowKill2 );
	assert( m_pID_TEXT_ArrowDeath2 );
	assert( m_pID_LIST_Rank2 );
	assert( m_pID_LIST_Name2 );
	assert( m_pID_LIST_Level2 );
	assert( m_pID_LIST_Job2 );
	assert( m_pID_LIST_Kill2 );
	assert( m_pID_LIST_Death2 );
	assert( m_pID_LIST_GuildBattle2 );
	assert( m_pID_TEXT_GuildName2 );
	assert( m_pID_TEXT_Player2 );
	assert( m_pID_TEXT_Score2 );
	assert( m_pID_BUTTON_Leave );
	assert( m_pID_BUTTON_Cancel );

	m_arraySelfListCtl[eList_big] = m_pID_LIST_GuildBattle1;
	m_arraySelfListCtl[eList_rank] = m_pID_LIST_Rank1;
	m_arraySelfListCtl[eList_name] = m_pID_LIST_Name1;
	m_arraySelfListCtl[eList_level] = m_pID_LIST_Level1;
	m_arraySelfListCtl[eList_job] = m_pID_LIST_Job1;
	m_arraySelfListCtl[eList_kill] = m_pID_LIST_Kill1;
	m_arraySelfListCtl[eList_death] = m_pID_LIST_Death1;

	m_arrayEnemyListCtl[eList_big] = m_pID_LIST_GuildBattle2;
	m_arrayEnemyListCtl[eList_rank] = m_pID_LIST_Rank2;
	m_arrayEnemyListCtl[eList_name] = m_pID_LIST_Name2;
	m_arrayEnemyListCtl[eList_level] = m_pID_LIST_Level2;
	m_arrayEnemyListCtl[eList_job] = m_pID_LIST_Job2;
	m_arrayEnemyListCtl[eList_kill] = m_pID_LIST_Kill2;
	m_arrayEnemyListCtl[eList_death] = m_pID_LIST_Death2;

	m_arraySelfTextCtl[ekey_Level] = m_pID_TEXT_ArrowLevel1;
	m_arraySelfTextCtl[ekey_kill] = m_pID_TEXT_ArrowKill1;
	m_arraySelfTextCtl[ekey_death] = m_pID_TEXT_ArrowDeath1;

	m_arrayEnemyTextCtl[ekey_Level] = m_pID_TEXT_ArrowLevel2;
	m_arrayEnemyTextCtl[ekey_kill] = m_pID_TEXT_ArrowKill2;
	m_arrayEnemyTextCtl[ekey_death] = m_pID_TEXT_ArrowDeath2;

	m_ourData.InitListCtl(m_arraySelfListCtl);
	m_otherData.InitListCtl(m_arrayEnemyListCtl);

	m_ourData.InitArrowArray(m_arraySelfTextCtl);	
	m_otherData.InitArrowArray(m_arrayEnemyTextCtl);

	SetVisable(false);
	return true;
}
// 卸载UI

void CUI_ID_FRAME_GuildBattle::SetSkipAllMsg()
{
	if (_IsVisable())
	{
		m_pID_LIST_Rank1->SetSkipAllMsg(true);
		m_pID_LIST_Name1->SetSkipAllMsg(true);
		m_pID_LIST_Level1->SetSkipAllMsg(true);
		m_pID_LIST_Job1->SetSkipAllMsg(true);
		m_pID_LIST_Kill1->SetSkipAllMsg(true);
		m_pID_LIST_Death1->SetSkipAllMsg(true);

		m_pID_LIST_Rank2->SetSkipAllMsg(true);
		m_pID_LIST_Name2->SetSkipAllMsg(true);
		m_pID_LIST_Level2->SetSkipAllMsg(true);
		m_pID_LIST_Job2->SetSkipAllMsg(true);
		m_pID_LIST_Kill2->SetSkipAllMsg(true);
		m_pID_LIST_Death2->SetSkipAllMsg(true);
	}
}

bool CUI_ID_FRAME_GuildBattle::_UnLoadUI()
{
	m_pID_FRAME_GuildBattle = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_Rank1 = NULL;
	m_pID_BUTTON_Name1 = NULL;
	m_pID_BUTTON_Level1 = NULL;
	m_pID_BUTTON_Job1 = NULL;
	m_pID_BUTTON_Kill1 = NULL;
	m_pID_BUTTON_Death1 = NULL;
	m_pID_LIST_Rank1 = NULL;
	m_pID_LIST_Name1 = NULL;
	m_pID_LIST_Level1 = NULL;
	m_pID_LIST_Job1 = NULL;
	m_pID_LIST_Kill1 = NULL;
	m_pID_LIST_Death1 = NULL;
	m_pID_LIST_GuildBattle1 = NULL;
	m_pID_TEXT_ArrowLevel1 = NULL;
	m_pID_TEXT_ArrowKill1 = NULL;
	m_pID_TEXT_ArrowDeath1 = NULL;
	m_pID_TEXT_GuildName1 = NULL;
	m_pID_TEXT_Player1 = NULL;
	m_pID_TEXT_Score1 = NULL;
	m_pID_BUTTON_Rank2 = NULL;
	m_pID_BUTTON_Name2 = NULL;
	m_pID_BUTTON_Level2 = NULL;
	m_pID_BUTTON_Job2 = NULL;
	m_pID_BUTTON_Kill2 = NULL;
	m_pID_BUTTON_Death2 = NULL;
	m_pID_TEXT_ArrowLevel2 = NULL;
	m_pID_TEXT_ArrowKill2 = NULL;
	m_pID_TEXT_ArrowDeath2 = NULL;
	m_pID_LIST_Rank2 = NULL;
	m_pID_LIST_Name2 = NULL;
	m_pID_LIST_Level2 = NULL;
	m_pID_LIST_Job2 = NULL;
	m_pID_LIST_Kill2 = NULL;
	m_pID_LIST_Death2 = NULL;
	m_pID_LIST_GuildBattle2 = NULL;
	m_pID_TEXT_GuildName2 = NULL;
	m_pID_TEXT_Player2 = NULL;
	m_pID_TEXT_Score2 = NULL;
	m_pID_BUTTON_Leave = NULL;
	m_pID_BUTTON_Cancel = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GuildBattle.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GuildBattle::_IsVisable()
{
	if ( !m_pID_FRAME_GuildBattle )
		return false;
	return m_pID_FRAME_GuildBattle->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_GuildBattle::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_GuildBattle )
		return;

	m_pID_FRAME_GuildBattle->SetVisable( bVisable );
	if (bVisable)
	{
		m_ourData.ResetSortTypeAndArrowShow();
		m_otherData.ResetSortTypeAndArrowShow();
		AckInfo();
	}
}

//----------------------------------------------------------------------------------------------------
void CUI_ID_FRAME_GuildBattle::AckInfo()
{
	MsgCampBattlePlayerReq msg;
	msg.uchReqType = MsgCampBattlePlayerReq::TypeAllCamp;
	GettheNetworkInput().SendMsg(&msg);
}

void CUI_ID_FRAME_GuildBattle::InitBattleInfo(int nCount, const xPlayer* pXplayer)
{
	if (nCount == 0)
	{
		return;
	}
	
	Clear();

	m_vctTotalBattlePlayer.resize(nCount);
	for (int i = 0; i < nCount; ++i)
	{
		m_vctTotalBattlePlayer[i] = pXplayer[i];
	}
	
	InitBothData();
	SetText();
}

void CUI_ID_FRAME_GuildBattle::Clear()
{
	m_ourData.Clear();
	m_otherData.Clear();
	m_vctTotalBattlePlayer.clear();
	m_vctOurBattlePlayer.clear();
	m_vctOtherBattlePlayer.clear();
}

inline bool IsMyGuildFightCamp(unsigned char nType)
{	
	return CampDefine::GetBaseFightCamp(nType) == thePlayerRole.GetInfluence();
}

void CUI_ID_FRAME_GuildBattle::InitBothData()
{
	for (int i = 0; i < m_vctTotalBattlePlayer.size(); ++i)
	{
		if (IsMyGuildFightCamp(m_vctTotalBattlePlayer[i].GetFightCamp()))
		{
			m_vctOurBattlePlayer.push_back(&m_vctTotalBattlePlayer[i]);
		}
		else
		{
			m_vctOtherBattlePlayer.push_back(&m_vctTotalBattlePlayer[i]);
		}
	}

	SortAndStoreInfo(m_vctOurBattlePlayer, m_ourData);
	SortAndStoreInfo(m_vctOtherBattlePlayer, m_otherData);
}

static bool GreatKillCount(xPlayer* lhs, xPlayer* rhs)
{
	return lhs->GetTotalKillCount() > rhs->GetTotalKillCount();
}

static bool LessDeathCount(xPlayer* lhs, xPlayer* rhs)
{
	return lhs->GetTotalDeathCount() < rhs->GetTotalDeathCount();
}

//sort按照杀敌数排列，杀敌数相同时，按照被杀数
void CUI_ID_FRAME_GuildBattle::SortAndStoreInfo(std::vector<xPlayer*>& vctBattlePlayer, BattleData& battleData)
{
	if (vctBattlePlayer.empty())
	{
		return;
	}
	
	std::vector<xPlayer*> tempArray;
	std::vector<xPlayer*> sortArray;
	sortArray.resize(vctBattlePlayer.size());
	std::sort(vctBattlePlayer.begin(), vctBattlePlayer.end(), GreatKillCount);

	sortArray[0] = vctBattlePlayer[0];
	int nCount = 0;

	std::vector<xPlayer*>::iterator iter = vctBattlePlayer.begin();
	iter += 1;
	for (; iter != vctBattlePlayer.end(); ++iter)
	{
		if ((*iter)->GetTotalKillCount() != sortArray[nCount]->GetTotalKillCount())
		{
			std::sort(&sortArray[0], &sortArray[nCount], LessDeathCount);
			for (int i = 0; i <= nCount; ++i)
			{
				tempArray.push_back(sortArray[i]);
			}

			sortArray[0] = *iter;
			nCount = 0;
		}
		else
		{
			++nCount;
			sortArray[nCount] = *iter;
		}
	}

	for (int i = 0; i <= nCount; ++i)
	{
		tempArray.push_back(sortArray[i]);
	}

	for (int i = 0; i < tempArray.size(); ++i)
	{
		battleData.push_back(Data(i + 1, tempArray[i]));
	}

	battleData.SetNeedRefresh(true);
}

std::string GetProfessionByID(int nProfessionID)
{
	std::string str;
	switch(nProfessionID)
	{
	case EArmType_Warrior:
		str = theXmlString.GetString(eProfession_Warrior);
		break;
	case EArmType_Assassin:
		str = theXmlString.GetString( eProfession_Assassin );
		break;
	case EArmType_Mage:
		str = theXmlString.GetString( eProfession_Mage );
		break;
	case  EArmType_Taoist:
		str = theXmlString.GetString( eProfession_Taoist );
		break;
	case EArmType_Hunter:
		str = theXmlString.GetString( eProfession_Hunter );
		break;
	default:
		break;
	}

	return str.c_str();
}

void BattleData ::ClearList()
{
	for (int i = 0; i < eList_max; ++i)
	{
		m_pListCtl[i]->Clear();
	}	
}

void BattleData ::AddDataToList()
{
	for (std::vector<Data>::const_iterator iter = m_xData.begin(); iter != m_xData.end(); ++iter)
	{
		AddToListHelp(&(*iter), 0);
	}
}

void BattleData::AddToListHelp(const Data* pData, DWORD color) const
{
	if (!pData)
	{
		return;
	}
	
	ControlList::S_List stItem;
	char szText[128] = {0};
	stItem.SetData( "" );
	m_pListCtl[eList_big]->AddItem(&stItem, NULL, false);
	stItem.clear();

	//Rank
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d", pData->m_nRank);
	stItem.SetData(szText, 0, NULL, color);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pListCtl[eList_rank]->AddItem(&stItem, NULL, false);
	stItem.clear();
	memset(szText, 0, sizeof(szText));

	//Name
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%s", pData->m_pValue->GetName());
	stItem.SetData(szText, 0, NULL, color);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pListCtl[eList_name]->AddItem(&stItem, NULL, false);
	stItem.clear();
	memset(szText, 0, sizeof(szText));

	//Level
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d", pData->m_pValue->GetLevel());
	stItem.SetData(szText, 0, NULL, color);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pListCtl[eList_level]->AddItem(&stItem, NULL, false);
	stItem.clear();
	memset(szText, 0, sizeof(szText));

	//Job
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%s", GetProfessionByID(pData->m_pValue->GetProfession()).c_str());
	stItem.SetData(szText, 0, NULL, color);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pListCtl[eList_job]->AddItem(&stItem, NULL, false);
	stItem.clear();
	memset(szText, 0, sizeof(szText));

	//Kill
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d", pData->m_pValue->GetTotalKillCount());
	stItem.SetData(szText, 0, NULL, color);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pListCtl[eList_kill]->AddItem(&stItem, NULL, false);
	stItem.clear();
	memset(szText, 0, sizeof(szText));

	//Death
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d", pData->m_pValue->GetTotalDeathCount());
	stItem.SetData(szText, 0, NULL, color);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pListCtl[eList_death]->AddItem(&stItem, NULL, false);
	stItem.clear();
	memset(szText, 0, sizeof(szText));
}

// Button
bool CUI_ID_FRAME_GuildBattle::ID_BUTTON_Level1OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattle )
		return false;

	m_ourData.SetSortFunc(ekey_Level);
	return true;
}

// Button
bool CUI_ID_FRAME_GuildBattle::ID_BUTTON_Kill1OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattle )
		return false;

	m_ourData.SetSortFunc(ekey_kill);
	return true;
}

// Button
bool CUI_ID_FRAME_GuildBattle::ID_BUTTON_Death1OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattle )
		return false;

	m_ourData.SetSortFunc(ekey_death);
	return true;
}

// Button
bool CUI_ID_FRAME_GuildBattle::ID_BUTTON_Level2OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattle )
		return false;

	m_otherData.SetSortFunc(ekey_Level);
	return true;
}

// Button
bool CUI_ID_FRAME_GuildBattle::ID_BUTTON_Kill2OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattle )
		return false;

	m_otherData.SetSortFunc(ekey_kill);
	return true;
}
// Button
bool CUI_ID_FRAME_GuildBattle::ID_BUTTON_Death2OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattle )
		return false;

	m_otherData.SetSortFunc(ekey_death);
	return true;
}

bool BattleData::SortByLevel_Greater(const Data& lhs, const Data& rhs)
{
	return lhs.m_pValue->GetLevel() > rhs.m_pValue->GetLevel();
}

bool BattleData::SortByKill_Greater(const Data& lhs, const Data& rhs)
{
	return lhs.m_pValue->GetTotalKillCount() > rhs.m_pValue->GetTotalKillCount();
}

bool BattleData::SortByDeath_Greater(const Data& lhs, const Data& rhs)
{
	return lhs.m_pValue->GetTotalDeathCount() > rhs.m_pValue->GetTotalDeathCount();
}

bool BattleData::SortByLevel_Less(const Data& lhs, const Data& rhs)
{
	return lhs.m_pValue->GetLevel() < rhs.m_pValue->GetLevel();
}

bool BattleData::SortByKill_Less(const Data& lhs, const Data& rhs)
{
	return lhs.m_pValue->GetTotalKillCount() < rhs.m_pValue->GetTotalKillCount();
}

bool BattleData::SortByDeath_Less(const Data& lhs, const Data& rhs)
{
	return lhs.m_pValue->GetTotalDeathCount() < rhs.m_pValue->GetTotalDeathCount();
}

void BattleData::Sort()
{
	std::stable_sort(m_xData.begin(), m_xData.end(), m_currentSortFunc);
}

void BattleData::InitArrowArray(ControlText** pCtl)
{
	m_pID_TEXT_Arrow[ekey_Level] = pCtl[ekey_Level];
	m_pID_TEXT_Arrow[ekey_kill] = pCtl[ekey_kill];
	m_pID_TEXT_Arrow[ekey_death] = pCtl[ekey_death];
}

void BattleData::SetSortFunc(eSortType sortType)
{
	if (sortType < 0 || sortType >= ekey_max)
	{
		return;
	}

	m_key = sortType;
	m_bArrow[m_key] = !m_bArrow[m_key];
	if (m_bArrow[m_key])
	{
		m_currentSortFunc = m_funcSort[m_key];
	}
	else
	{
		m_currentSortFunc = m_funcSortReverse[m_key];
	}

	SetNeedRefresh(true);
}

void BattleData::InitSortFunc()
{
	m_funcSort[ekey_Level] = SortByLevel_Greater;
	m_funcSort[ekey_kill] = SortByKill_Greater;
	m_funcSort[ekey_death] = SortByDeath_Greater;

	m_funcSortReverse[ekey_Level] = SortByLevel_Less;
	m_funcSortReverse[ekey_kill] = SortByKill_Less;
	m_funcSortReverse[ekey_death] = SortByDeath_Less;
}

void BattleData::Refresh()
{
	ClearList();
	Sort();
	AddDataToList();
	ShowSortArrow();
}

void BattleData::ShowSortArrow()
{
	if (m_key < 0 || m_key >= ekey_max)
	{
		return;
	}

	for (int i = 0; i < ekey_max; ++i)
	{
		m_pID_TEXT_Arrow[i]->SetVisable( false);
	}

	m_pID_TEXT_Arrow[m_key]->SetVisable(true);

	if (!m_bArrow[m_key])
	{
		m_pID_TEXT_Arrow[m_key]->SetText("{#204}");
	}
	else
	{
		m_pID_TEXT_Arrow[m_key]->SetText("{#203}");
	}
}

void BattleData::Init()
{
	SetNeedRefresh(false);
	InitSortFunc();
	ResetSortTypeAndArrowShow();
}

void BattleData::ResetSortTypeAndArrowShow()
{
	m_key = ekey_kill;
	for (int i = 0; i < ekey_max; ++i)
	{
		m_bArrow[i] = false;
	}
	m_currentSortFunc = m_funcSort[ekey_kill];
}

void BattleData::InitListCtl(ControlList** pList)
{
	if (!pList)
	{
		return;
	}

	m_pListCtl[eList_big] = pList[eList_big];
	m_pListCtl[eList_rank] = pList[eList_rank];
	m_pListCtl[eList_name] = pList[eList_name];
	m_pListCtl[eList_level] = pList[eList_level];
	m_pListCtl[eList_job] = pList[eList_job];
	m_pListCtl[eList_kill] = pList[eList_kill];
	m_pListCtl[eList_death] = pList[eList_death];
}

void BattleData::Clear()
{
	ClearList();
	m_xData.clear();
}

void CUI_ID_FRAME_GuildBattle::Refresh()
{
	if (!_IsVisable())
	{
		return;
	}
	
	if (m_ourData.GetNeedRefresh())
	{
		m_ourData.Refresh();
		m_ourData.SetNeedRefresh(false);
	}

	if (m_otherData.GetNeedRefresh())
	{
		m_otherData.Refresh();
		m_otherData.SetNeedRefresh(false);
	}
}

void CUI_ID_FRAME_GuildBattle::SetNeedRefresh()
{
	m_ourData.SetNeedRefresh(true);
	m_otherData.SetNeedRefresh(true);
}

//离开战场
bool CUI_ID_FRAME_GuildBattle::ID_BUTTON_LeaveOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattle )
		return false;

	MsgLeaveCampBattleReq msg;
	GettheNetworkInput().SendMsg(&msg);
	_SetVisable(false);
	s_CUI_ID_FRAME_Group_Me.SetGuildBattleButtonVisable(false);
	return true;
}

void CUI_ID_FRAME_GuildBattle::SetText()
{
	if ( !m_pID_FRAME_GuildBattle )
		return;
	
	if (!_IsVisable())
	{
		return;
	}

	if (!(thePlayerRole.GetGangMgr()))
	{
		return;
	}
	
	m_pID_TEXT_Player1->SetText(m_ourData.GetMemberCount());
	m_pID_TEXT_Player2->SetText(m_otherData.GetMemberCount());

	SetGuildName();
	RefreshScore();
}

void CUI_ID_FRAME_GuildBattle::SetGuildName()
{
	if (!_IsVisable())
	{
		return;
	}

	if (thePlayerRole.GetInfluence() == CampDefine::BaseCampRed)
	{
		m_pID_TEXT_GuildName1->SetText(thePlayerRole.GetGuildNameById(thePlayerRole.GetRedCampGuildId()));
		m_pID_TEXT_GuildName2->SetText(thePlayerRole.GetGuildNameById(thePlayerRole.GetBlueCampGuildId()));
		/*m_pID_TEXT_Player1->SetText(thePlayerRole.GetGuildNameById(thePlayerRole.GetBlueCampGuildId()));*/
	}
	else if (thePlayerRole.GetInfluence() == CampDefine::BaseCampBlue)
	{
		m_pID_TEXT_GuildName1->SetText(thePlayerRole.GetGuildNameById(thePlayerRole.GetBlueCampGuildId()));
		m_pID_TEXT_GuildName2->SetText(thePlayerRole.GetGuildNameById(thePlayerRole.GetRedCampGuildId()));
		/*m_pID_TEXT_Player2->SetText(thePlayerRole.GetGuildNameById(thePlayerRole.GetRedCampGuildId()));*/
	}
}

void CUI_ID_FRAME_GuildBattle::RefreshScore()
{
	if (!_IsVisable())
	{
		return;
	}

	if (thePlayerRole.GetInfluence() == CampDefine::BaseCampRed)
	{
		m_pID_TEXT_Score1->SetText(thePlayerRole.GetRedCampResource());
		m_pID_TEXT_Score2->SetText(thePlayerRole.GetBlueCampResource());
	}
	else if (thePlayerRole.GetInfluence() == CampDefine::BaseCampBlue)
	{
		m_pID_TEXT_Score1->SetText(thePlayerRole.GetBlueCampResource());
		m_pID_TEXT_Score2->SetText(thePlayerRole.GetBlueCampResource());
	}
}