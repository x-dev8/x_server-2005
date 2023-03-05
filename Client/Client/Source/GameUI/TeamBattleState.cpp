/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\chixin.ni\桌面\TeamBattleState.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "TeamBattleState.h"
#include "TeamBattleResult.h"
#include "Player.h"
#include "GameMain.h"
#include "PlayerRole.h"
#include "XmlStringLanguage.h"
#include "Common.h"

CUI_ID_FRAME_TeamBattleState s_CUI_ID_FRAME_TeamBattleState;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TeamBattleState, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TeamBattleState, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TeamBattleState, ID_BUTTON_ShowStateOnButtonClick )
CUI_ID_FRAME_TeamBattleState::CUI_ID_FRAME_TeamBattleState()
{
	// Member
	m_pID_FRAME_TeamBattleState = NULL;
	m_pID_PICTURE_Tang = NULL;
	m_pID_TEXT_Tang = NULL;
	m_pID_BUTTON_ShowState = NULL;

}
// Frame
bool CUI_ID_FRAME_TeamBattleState::OnFrameRun()
{
	if(!thePlayerRole.IsTeamBattleInMap())
	{
		SetVisable(false);
	}
	else
	{
		SetVisable(true);
	}

	return true;
}
bool CUI_ID_FRAME_TeamBattleState::OnFrameRender()
{

	return true;
}
// Button
bool CUI_ID_FRAME_TeamBattleState::ID_BUTTON_ShowStateOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_TeamBattleState)
		return false;
	bool bVisable = s_CUI_ID_FRAME_TeamBattleResult.IsVisable();
	s_CUI_ID_FRAME_TeamBattleResult.SetVisable(!bVisable);

	return true;
}

// 装载UI
bool CUI_ID_FRAME_TeamBattleState::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TeamBattleState.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\TeamBattleState.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_TeamBattleState::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TeamBattleState, s_CUI_ID_FRAME_TeamBattleStateOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TeamBattleState, s_CUI_ID_FRAME_TeamBattleStateOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_TeamBattleState, ID_BUTTON_ShowState, s_CUI_ID_FRAME_TeamBattleStateID_BUTTON_ShowStateOnButtonClick );

	m_pID_FRAME_TeamBattleState = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TeamBattleState );
	m_pID_PICTURE_Tang = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TeamBattleState, ID_PICTURE_Tang );
	m_pID_TEXT_Tang = (ControlText*)theUiManager.FindControl( ID_FRAME_TeamBattleState, ID_TEXT_Tang );
	m_pID_BUTTON_ShowState = (ControlButton*)theUiManager.FindControl( ID_FRAME_TeamBattleState, ID_BUTTON_ShowState );
	assert( m_pID_FRAME_TeamBattleState );
	assert( m_pID_PICTURE_Tang );
	assert( m_pID_TEXT_Tang );
	assert( m_pID_BUTTON_ShowState );

	m_Rank = 0;

	SetVisable(false);

	Refresh();

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_TeamBattleState::_UnLoadUI()
{
	m_pID_FRAME_TeamBattleState = NULL;
	m_pID_PICTURE_Tang = NULL;
	m_pID_TEXT_Tang = NULL;
	m_pID_BUTTON_ShowState = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\TeamBattleState.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_TeamBattleState::_IsVisable()
{
	if(!m_pID_FRAME_TeamBattleState)
		return false;

	return m_pID_FRAME_TeamBattleState->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_TeamBattleState::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_TeamBattleState)
		return;

	m_pID_FRAME_TeamBattleState->SetVisable( bVisable );
}

void CUI_ID_FRAME_TeamBattleState::OnRecord( MsgTellBattleRecord* pRecord )
{
	for(int i=0;i<6;++i)
	{
		if(pRecord->xRecord[i].dwID == thePlayerRole.GetGroupId() )
		{
			m_Info = pRecord->xRecord[i];
		}
	}

	Refresh();

	SetVisable(true);
}

void CUI_ID_FRAME_TeamBattleState::Refresh()
{
	char chr[256];
	MeSprintf_s(chr,sizeof(chr)/sizeof(char) - 1,theXmlString.GetString( eText_TeamBattleResource ), m_Rank,m_Info.nIntegral,m_Info.nDeathCount);
	
	*m_pID_TEXT_Tang = chr;
}