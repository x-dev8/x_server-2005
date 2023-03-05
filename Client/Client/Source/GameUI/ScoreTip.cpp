/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\guildcamp\ScoreTip.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ScoreTip.h"
#include "PlayerRole.h"
#include "GuildBattle.h"
#include "CampGuildBattleConfig.h"
#include "Common.h"
#include "XmlStringLanguage.h"
#include "GuildBattleInfo.h"
#include "KingScoreTipMin.h"

CUI_ID_FRAME_ScoreTip s_CUI_ID_FRAME_ScoreTip;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ScoreTip, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ScoreTip, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ScoreTip, ID_BUTTON_ShowBattleInfoOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ScoreTip, ID_BUTTON_MinOnButtonClick )
CUI_ID_FRAME_ScoreTip::CUI_ID_FRAME_ScoreTip()
{
	// Member
	m_pID_FRAME_ScoreTip = NULL;
	m_pID_TEXT_FriendScore = NULL;
	m_pID_TEXT_EnemyScore = NULL;
	m_pID_TEXT_Name1 = NULL;
	m_pID_TEXT_Name2 = NULL;
	m_pID_TEXT_Time = NULL;
	m_pID_BUTTON_ShowBattleInfo = NULL;
	m_pID_BUTTON_Min = NULL;

	InitMember();
}
// Frame
bool CUI_ID_FRAME_ScoreTip::OnFrameRun()
{
	if ( IsVisable() )
		RefreshTime();
	return true;
}
bool CUI_ID_FRAME_ScoreTip::OnFrameRender()
{
	return true;
}

// Button
bool CUI_ID_FRAME_ScoreTip::ID_BUTTON_ShowBattleInfoOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_GuildBattleInfo.SetVisable(!s_CUI_ID_FRAME_GuildBattleInfo.IsVisable());
	return true;
}

// Button
bool CUI_ID_FRAME_ScoreTip::ID_BUTTON_MinOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_ScoreTip )
		return false;
	m_pID_FRAME_ScoreTip->SetVisable(false);
	s_CUI_ID_FRAME_KingScoreMin.SetVisable(true);
	s_CUI_ID_FRAME_KingScoreMin.SetIsKingFight( false );
	return true;
}


// 装载UI
bool CUI_ID_FRAME_ScoreTip::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ScoreTip.MEUI", true);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ScoreTip.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ScoreTip::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ScoreTip, s_CUI_ID_FRAME_ScoreTipOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ScoreTip, s_CUI_ID_FRAME_ScoreTipOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ScoreTip, ID_BUTTON_ShowBattleInfo, s_CUI_ID_FRAME_ScoreTipID_BUTTON_ShowBattleInfoOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ScoreTip, ID_BUTTON_Min, s_CUI_ID_FRAME_ScoreTipID_BUTTON_MinOnButtonClick );

	m_pID_FRAME_ScoreTip = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ScoreTip );
	m_pID_TEXT_FriendScore = (ControlText*)theUiManager.FindControl( ID_FRAME_ScoreTip, ID_TEXT_FriendScore );
	m_pID_TEXT_EnemyScore = (ControlText*)theUiManager.FindControl( ID_FRAME_ScoreTip, ID_TEXT_EnemyScore );
	m_pID_TEXT_Name1 = (ControlText*)theUiManager.FindControl( ID_FRAME_ScoreTip, ID_TEXT_Name1 );
	m_pID_TEXT_Name2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ScoreTip, ID_TEXT_Name2 );
	m_pID_TEXT_Time = (ControlText*)theUiManager.FindControl( ID_FRAME_ScoreTip, ID_TEXT_Time );
	m_pID_BUTTON_ShowBattleInfo = (ControlButton*)theUiManager.FindControl( ID_FRAME_ScoreTip, ID_BUTTON_ShowBattleInfo );
	m_pID_BUTTON_Min = (ControlButton*)theUiManager.FindControl( ID_FRAME_ScoreTip, ID_BUTTON_Min );

	assert( m_pID_FRAME_ScoreTip );
	assert( m_pID_TEXT_FriendScore );
	assert( m_pID_TEXT_EnemyScore );
	assert( m_pID_TEXT_Name1 );
	assert( m_pID_TEXT_Name2 );
	assert( m_pID_TEXT_Time );
	assert( m_pID_BUTTON_ShowBattleInfo );
	assert( m_pID_BUTTON_Min );

	m_pID_FRAME_ScoreTip->SetMsgHoldup(false);
	m_pID_TEXT_FriendScore->SetSkipAllMsg(true);
	m_pID_TEXT_EnemyScore->SetSkipAllMsg(true);
	m_pID_TEXT_Name1->SetSkipAllMsg(true);
	m_pID_TEXT_Name2->SetSkipAllMsg(true);
	m_pID_TEXT_Time->SetSkipAllMsg(true);

	m_pID_FRAME_ScoreTip->SetOnEscResponseType(ControlFrame::EscResponse_SkipMe);

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ScoreTip::_UnLoadUI()
{
	m_pID_FRAME_ScoreTip = NULL;
	m_pID_TEXT_FriendScore = NULL;
	m_pID_TEXT_EnemyScore = NULL;
	m_pID_TEXT_Name1 = NULL;
	m_pID_TEXT_Name2 = NULL;
	m_pID_TEXT_Time = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\ScoreTip.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_ScoreTip::_IsVisable()
{
	if ( !m_pID_FRAME_ScoreTip )
		return false;
	return m_pID_FRAME_ScoreTip->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ScoreTip::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_ScoreTip )
		return;
	m_pID_FRAME_ScoreTip->SetVisable( bVisable );
	if (bVisable)
	{
		SetShow();
	}
}

//------------------------------------------------------------------------------------
void CUI_ID_FRAME_ScoreTip::SetShow()
{
	if (!_IsVisable())
	{
		//s_CUI_ID_FRAME_ScoreTip.SetVisable(true);
		return;
	}

	if (!(thePlayerRole.GetGangMgr()))
	{
		return;
	}
	
	m_pID_TEXT_Name1->SetText(thePlayerRole.GetGuildNameById(thePlayerRole.GetRedCampGuildId()));
	char szText[128] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d/%d", thePlayerRole.GetRedCampResource(), theCampGuildBattleConfig.GetResourceSetting().GetMaxResource());
	m_pID_TEXT_FriendScore->SetText(szText);

	m_pID_TEXT_Name2->SetText(thePlayerRole.GetGuildNameById(thePlayerRole.GetBlueCampGuildId()));
	memset(szText, 0, sizeof(szText));
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d/%d", thePlayerRole.GetBlueCampResource(), theCampGuildBattleConfig.GetResourceSetting().GetMaxResource());
	m_pID_TEXT_EnemyScore->SetText(szText);

	s_CUI_ID_FRAME_GuildBattle.RefreshScore();
}

void CUI_ID_FRAME_ScoreTip::SetTime(DWORD nTime)
{
	m_nTotalTime = nTime;
	m_nStartTime = HQ_TimeGetTime();
}

void CUI_ID_FRAME_ScoreTip::SetStringId(int nStringId)
{
	m_nStringId = nStringId;
}

void CUI_ID_FRAME_ScoreTip::RefreshTime()
{
	CalaTime();
	//HMS = hour.minute.second
	TranslateTimeToHMS();
	ShowTime();
}

inline void CUI_ID_FRAME_ScoreTip::CalaTime()
{
	DWORD nCurrentTime = HQ_TimeGetTime();
	int timeGone =  (nCurrentTime - m_nStartTime) / 1000;
	if (timeGone >= m_nTotalTime)
	{
		m_nLastTime = 0;
	}
	else
	{
		m_nLastTime = m_nTotalTime - timeGone;
	}
}

inline void CUI_ID_FRAME_ScoreTip::TranslateTimeToHMS()
{
	int hour = m_nLastTime / 3600;
	int minute = (m_nLastTime - hour * 3600) / 60;
	int second = m_nLastTime % 60;
	MeSprintf_s(m_szTime, sizeof(m_szTime)/sizeof(char) - 1,/*"%s%d时%d分%d秒", */theXmlString.GetString(m_nStringId), hour, minute, second);
}

inline void CUI_ID_FRAME_ScoreTip::ShowTime()
{
	m_pID_TEXT_Time->SetText(m_szTime);
}

void CUI_ID_FRAME_ScoreTip::InitMember()
{
	m_nTotalTime = 0;
	m_nStartTime = 0;
	m_nLastTime = 0;
	m_nStringId = 0;
	memset(m_szTime, 0, sizeof(m_szTime));
}