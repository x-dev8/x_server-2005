/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\RTX\国王战\KingScoreTip.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Me3D/Global.h"
#include "KingScoreTip.h"
#include "PlayerRole.h"
#include "GuildBattle.h"
#include "CampCountryBattleConfig.h"
#include "CampBattleMessage.h"
#include "Common.h"
#include "XmlStringLanguage.h"
#include "KingScoreTipMin.h"
#include "MapConfig.h"
#include "MeTerrain/NiColor.h"
#include "MeTerrain/SwType.h"
#include "MeTerrain/HashTable.h"
#include "MeTerrain/MapFile.h"
#include "MeTerrain/MapUtil.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldTile.h"
const char* g_gifRedLiveStar[CUI_ID_FRAME_KingScoreTip::m_nMaxLive] = {
	"{#Nothing00}"
	,"{#Red01}"
	,"{#Red02}"
	,"{#Red03}"
	,"{#Red04}"
	,"{#Red05}"
};

const char* g_gifBlueLiveStar[CUI_ID_FRAME_KingScoreTip::m_nMaxLive] = {
	"{#Nothing00}"
	,"{#Blue01}"
	,"{#Blue02}"
	,"{#Blue03}"
	,"{#Blue04}"
	,"{#Blue05}"
};

CUI_ID_FRAME_KingScoreTip s_CUI_ID_FRAME_KingScoreTip;
MAP_FRAME_RUN( s_CUI_ID_FRAME_KingScoreTip, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_KingScoreTip, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_KingScoreTip, ID_BUTTON_MinonClick  )
CUI_ID_FRAME_KingScoreTip::CUI_ID_FRAME_KingScoreTip()
{
	// Member
	m_pID_FRAME_KingScoreTip = NULL;
	m_pID_PICTURE_King = NULL;
	m_pID_TEXT_Name1 = NULL;
	m_pID_TEXT_Name2 = NULL;
	m_pID_PROGRESS_FriendScore = NULL;
	m_pID_PROGRESS_EnemyScore = NULL;
	m_pID_TEXT_FriendScore = NULL;
	m_pID_TEXT_EnemyScore = NULL;
	m_pID_TEXT_Time = NULL;
	m_pID_Text_FriendStar = NULL;
	m_pID_Text_EnemyStar = NULL;
	m_pID_BUTTON_Min  = NULL;

	InitMember();
	/*InitCampData();*/
}

void CUI_ID_FRAME_KingScoreTip::InitCampData()
{
	//zhuxincong 这里注释掉，加载的是国王战争最后的结果
	//m_nMaxCount = theKingCampBattleConfig.GetEnterSetting().GetMaxEnterCount();
	m_nRedCount = m_nBlueCount = 0;
	//m_nMaxDeathCount = theKingCampBattleConfig.GetMaxDeathCount() + 1;

	//m_nRedMasterDeathCount = m_nMaxDeathCount;
	//m_nBlueMasterDeathCount = m_nMaxDeathCount;
}

// Frame
bool CUI_ID_FRAME_KingScoreTip::OnFrameRun()
{
	RefreshTime();
	return true;
}
bool CUI_ID_FRAME_KingScoreTip::OnFrameRender()
{
	//当UI显示的时候 我们判断玩家是否在战场内 
	CWorldTile* pTile =CURRENTTILE;
	if (pTile && pTile->GetCanPk() != MapConfig::MapData::EPKM_Guild_PK)
	{
		_SetVisable(false);
	}
	return true;
}
bool CUI_ID_FRAME_KingScoreTip::ID_BUTTON_MinonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_KingScoreTip )
		return false;
	m_pID_FRAME_KingScoreTip->SetVisable(false);
	s_CUI_ID_FRAME_KingScoreMin.SetVisable(true);
	s_CUI_ID_FRAME_KingScoreMin.SetIsKingFight( true );
	return true;
}
// 装载UI
bool CUI_ID_FRAME_KingScoreTip::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\KingScoreTip.MEUI",true );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\KingScoreTip.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_KingScoreTip::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_KingScoreTip, s_CUI_ID_FRAME_KingScoreTipOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_KingScoreTip, s_CUI_ID_FRAME_KingScoreTipOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_KingScoreTip, ID_BUTTON_Min, s_CUI_ID_FRAME_KingScoreTipID_BUTTON_MinonClick );

	m_pID_FRAME_KingScoreTip = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_KingScoreTip );
	m_pID_PICTURE_King = (ControlPicture*)theUiManager.FindControl( ID_FRAME_KingScoreTip, ID_PICTURE_King );
	m_pID_TEXT_Name1 = (ControlText*)theUiManager.FindControl( ID_FRAME_KingScoreTip, ID_TEXT_Name1 );
	m_pID_TEXT_Name2 = (ControlText*)theUiManager.FindControl( ID_FRAME_KingScoreTip, ID_TEXT_Name2 );
	m_pID_PROGRESS_FriendScore = (ControlProgress*)theUiManager.FindControl( ID_FRAME_KingScoreTip, ID_PROGRESS_FriendScore );
	m_pID_PROGRESS_EnemyScore = (ControlProgress*)theUiManager.FindControl( ID_FRAME_KingScoreTip, ID_PROGRESS_EnemyScore );
	m_pID_TEXT_FriendScore = (ControlText*)theUiManager.FindControl( ID_FRAME_KingScoreTip, ID_TEXT_FriendScore );
	m_pID_TEXT_EnemyScore = (ControlText*)theUiManager.FindControl( ID_FRAME_KingScoreTip, ID_TEXT_EnemyScore );
	m_pID_TEXT_Time = (ControlText*)theUiManager.FindControl( ID_FRAME_KingScoreTip, ID_TEXT_Time );
	m_pID_Text_FriendStar = (ControlText*)theUiManager.FindControl( ID_FRAME_KingScoreTip, ID_Text_FriendStar );
	m_pID_Text_EnemyStar = (ControlText*)theUiManager.FindControl( ID_FRAME_KingScoreTip, ID_Text_EnemyStar );
	m_pID_BUTTON_Min = (ControlButton*)theUiManager.FindControl( ID_FRAME_KingScoreTip, ID_BUTTON_Min );

	assert( m_pID_FRAME_KingScoreTip );
	assert( m_pID_PICTURE_King );
	assert( m_pID_TEXT_Name1 );
	assert( m_pID_TEXT_Name2 );
	assert( m_pID_PROGRESS_FriendScore );
	assert( m_pID_PROGRESS_EnemyScore );
	assert( m_pID_TEXT_FriendScore );
	assert( m_pID_TEXT_EnemyScore );
	assert( m_pID_TEXT_Time );
	assert( m_pID_Text_FriendStar );
	assert( m_pID_Text_EnemyStar );
	assert (m_pID_BUTTON_Min);

	m_pID_FRAME_KingScoreTip->SetMsgHoldup(false);
	m_pID_TEXT_FriendScore->SetSkipAllMsg(true);
	m_pID_TEXT_EnemyScore->SetSkipAllMsg(true);
	m_pID_TEXT_Name1->SetSkipAllMsg(true);
	m_pID_TEXT_Name2->SetSkipAllMsg(true);
	m_pID_TEXT_Time->SetSkipAllMsg(true);
	m_pID_PROGRESS_FriendScore->SetSkipAllMsg(true);
	m_pID_PROGRESS_EnemyScore->SetSkipAllMsg(true);
	m_pID_Text_FriendStar->SetSkipAllMsg(true);
	m_pID_Text_EnemyStar->SetSkipAllMsg(true);

	m_pID_FRAME_KingScoreTip->SetOnEscResponseType(ControlFrame::EscResponse_SkipMe);

	char fullname[MAX_PATH] = {0};
	MeSprintf_s( fullname, sizeof( fullname ) / sizeof( char ) - 1, "%s\\data\\ui\\UIAni\\PlayerHp.2DAni", GetRootPath() );

	m_pID_PROGRESS_FriendScore->CreateAnimation(fullname);
	m_pID_PROGRESS_EnemyScore->CreateAnimation(fullname);
	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_KingScoreTip::_UnLoadUI()
{
	m_pID_FRAME_KingScoreTip = NULL;
	m_pID_PICTURE_King = NULL;
	m_pID_TEXT_Name1 = NULL;
	m_pID_TEXT_Name2 = NULL;
	m_pID_PROGRESS_FriendScore = NULL;
	m_pID_PROGRESS_EnemyScore = NULL;
	m_pID_TEXT_FriendScore = NULL;
	m_pID_TEXT_EnemyScore = NULL;
	m_pID_TEXT_Time = NULL;
	m_pID_Text_FriendStar = NULL;
	m_pID_Text_EnemyStar = NULL;
	m_pID_BUTTON_Min = NULL;

	return theUiManager.RemoveFrame( "Data\\UI\\KingScoreTip.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_KingScoreTip::_IsVisable()
{
	if ( !m_pID_FRAME_KingScoreTip )
		return false;
	return m_pID_FRAME_KingScoreTip->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_KingScoreTip::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_KingScoreTip )
		return;
	m_pID_FRAME_KingScoreTip->SetVisable( bVisable );
	/*if(s_CUI_ID_FRAME_KingScoreMin.IsVisable() == bVisable)
		s_CUI_ID_FRAME_KingScoreMin.SetVisable(!bVisable);*/
}

//------------------------------------------------------------------------------------
void CUI_ID_FRAME_KingScoreTip::SetShow()
{
	/*if (!_IsVisable())
	{
		s_CUI_ID_FRAME_KingScoreTip.SetVisable(true);
	}*/
	if ( !m_pID_FRAME_KingScoreTip )
	{
		s_CUI_ID_FRAME_KingScoreTip._LoadUI();
		return;
	}

	if (!(thePlayerRole.GetGangMgr()))
	{
		return;
	}

	char szText[128] = {0};

	m_pID_TEXT_Name1->SetText(thePlayerRole.GetGuildNameById(thePlayerRole.GetRedCampGuildId()));
	m_pID_PROGRESS_FriendScore->SetMaxValue(m_nMaxCount);
	m_pID_PROGRESS_FriendScore->SetValue(m_nRedCount);
	MeSprintf(szText, sizeof(szText)/sizeof(char) - 1, "%d", m_nRedCount);
	m_pID_TEXT_FriendScore->SetText(szText);
	int nRedLive = m_nMaxDeathCount - m_nRedMasterDeathCount;
	if (nRedLive >= 0 && nRedLive <m_nMaxLive)
	{
		m_pID_Text_FriendStar->SetText(g_gifRedLiveStar[m_nMaxDeathCount - m_nRedMasterDeathCount]);
	}

	m_pID_TEXT_Name2->SetText(thePlayerRole.GetGuildNameById(thePlayerRole.GetBlueCampGuildId()));
	m_pID_PROGRESS_EnemyScore->SetMaxValue(m_nMaxCount);
	m_pID_PROGRESS_EnemyScore->SetValue(m_nBlueCount);
	MeSprintf(szText, sizeof(szText)/sizeof(char) - 1, "%d", m_nBlueCount);
	m_pID_TEXT_EnemyScore->SetText(szText);
	int nBlueLive = m_nMaxDeathCount - m_nBlueMasterDeathCount;
	if (nBlueLive >= 0 && nBlueLive < m_nMaxLive)
	{
		m_pID_Text_EnemyStar->SetText(g_gifBlueLiveStar[m_nMaxDeathCount - m_nBlueMasterDeathCount]);
	}
}

void CUI_ID_FRAME_KingScoreTip::SetTime(DWORD nTime)
{
	m_nTotalTime = nTime;
	m_nStartTime = HQ_TimeGetTime();
}

void CUI_ID_FRAME_KingScoreTip::SetStringId(int nStringId)
{
	m_nStringId = nStringId;
}

void CUI_ID_FRAME_KingScoreTip::RefreshTime()
{
	CalaTime();
	//HMS = hour.minute.second
	TranslateTimeToHMS();
	ShowTime();
}

inline void CUI_ID_FRAME_KingScoreTip::CalaTime()
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

inline void CUI_ID_FRAME_KingScoreTip::TranslateTimeToHMS()
{
	int hour = m_nLastTime / 3600;
	int minute = (m_nLastTime - hour * 3600) / 60;
	int second = m_nLastTime % 60;
	MeSprintf_s(m_szTime, sizeof(m_szTime)/sizeof(char) - 1,/*"%s%d时%d分%d秒", */theXmlString.GetString(m_nStringId), hour, minute, second);
}

inline void CUI_ID_FRAME_KingScoreTip::ShowTime()
{
	m_pID_TEXT_Time->SetText(m_szTime);
}

void CUI_ID_FRAME_KingScoreTip::InitMember()
{
	m_nTotalTime = 0;
	m_nStartTime = 0;
	m_nLastTime = 0;
	m_nStringId = 0;
	memset(m_szTime, 0, sizeof(m_szTime));
}

void CUI_ID_FRAME_KingScoreTip::UpdateData(MsgTellCountryBattlePlayerCount* pMsg)
{
	if (!pMsg)
	{
		return;
	}
	
	m_nRedCount = pMsg->nRedCount;
	m_nBlueCount = pMsg->nBlueCount;
	m_nRedMasterDeathCount = pMsg->nRedMasterDeathCount;
	m_nBlueMasterDeathCount = pMsg->nBlueMasterDeathCount;

	SetShow();
}