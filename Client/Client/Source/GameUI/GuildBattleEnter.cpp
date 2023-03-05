/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\guildcamp\GuildBattleEnter.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GuildBattleEnter.h"
#include "CampBattleMessage.h"
#include "NetworkInput.h"
#include "XmlStringLanguage.h"
#include "Common.h"
#include "PlayerRole.h"
#include "GameMain.h"
#include "PLayerMgr.h"
#include "Player.h"
#include "ScreenInfoManager.h"
#include "GameBattleMessage.h"
#include "GameBattleDefine.h"
CUI_ID_FRAME_GuildBattleEnter s_CUI_ID_FRAME_GuildBattleEnter;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GuildBattleEnter, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GuildBattleEnter, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattleEnter, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattleEnter, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattleEnter, ID_BUTTON_EnterOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattleEnter, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattleEnter, ID_BUTTON_FlyToMapOnButtonClick )
CUI_ID_FRAME_GuildBattleEnter::CUI_ID_FRAME_GuildBattleEnter()
{
	// Member
	m_pID_FRAME_GuildBattleEnter = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_TEXT_Name1 = NULL;
	m_pID_TEXT_Name2 = NULL;
	m_pID_TEXT_Text = NULL;
	m_pID_BUTTON_Enter = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_FlyToMap = NULL;
	IsGameBattle = false;

}
// Frame
bool CUI_ID_FRAME_GuildBattleEnter::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GuildBattleEnter::OnFrameRender()
{
	if (thePlayerRole.GetGameMapId() != m_nKingdomMapID&&m_nKingdomMapID != 0)
	{
		m_pID_BUTTON_FlyToMap->SetVisable(true);
		m_pID_BUTTON_Enter->SetVisable(false);
	}
	else
	{
		m_pID_BUTTON_Enter->SetVisable(true);	
		m_pID_BUTTON_FlyToMap->SetVisable(false);
	}
	return true;
}
// Button
bool CUI_ID_FRAME_GuildBattleEnter::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattleEnter )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_GuildBattleEnter::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattleEnter )
		return false;
	return true;
}

// 装载UI
bool CUI_ID_FRAME_GuildBattleEnter::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GuildBattleEnter.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GuildBattleEnter.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GuildBattleEnter::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GuildBattleEnter, s_CUI_ID_FRAME_GuildBattleEnterOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GuildBattleEnter, s_CUI_ID_FRAME_GuildBattleEnterOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattleEnter, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_GuildBattleEnterID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattleEnter, ID_BUTTON_HELP, s_CUI_ID_FRAME_GuildBattleEnterID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattleEnter, ID_BUTTON_Enter, s_CUI_ID_FRAME_GuildBattleEnterID_BUTTON_EnterOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattleEnter, ID_BUTTON_Cancel, s_CUI_ID_FRAME_GuildBattleEnterID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattleEnter, ID_BUTTON_FlyToMap, s_CUI_ID_FRAME_GuildBattleEnterID_BUTTON_FlyToMapOnButtonClick );

	m_pID_FRAME_GuildBattleEnter = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GuildBattleEnter );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattleEnter, ID_BUTTON_CLOSE );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattleEnter, ID_BUTTON_HELP );
	m_pID_TEXT_Name1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleEnter, ID_TEXT_Name1 );
	m_pID_TEXT_Name2 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleEnter, ID_TEXT_Name2 );
	m_pID_TEXT_Text = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleEnter, ID_TEXT_Text );
	m_pID_BUTTON_Enter = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattleEnter, ID_BUTTON_Enter );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattleEnter, ID_BUTTON_Cancel );
	m_pID_BUTTON_FlyToMap = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattleEnter, ID_BUTTON_FlyToMap );

	assert( m_pID_FRAME_GuildBattleEnter );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_TEXT_Name1 );
	assert( m_pID_TEXT_Name2 );
	assert( m_pID_TEXT_Text );
	assert( m_pID_BUTTON_Enter );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_FlyToMap );

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GuildBattleEnter::_UnLoadUI()
{
	m_pID_FRAME_GuildBattleEnter = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_TEXT_Name1 = NULL;
	m_pID_TEXT_Name2 = NULL;
	m_pID_TEXT_Text = NULL;
	m_pID_BUTTON_Enter = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_FlyToMap = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GuildBattleEnter.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GuildBattleEnter::_IsVisable()
{
	if ( !m_pID_FRAME_GuildBattleEnter )
		return false;
	return m_pID_FRAME_GuildBattleEnter->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GuildBattleEnter::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_GuildBattleEnter )
		return;
	if(!bVisable)
		IsGameBattle= false;
	m_pID_FRAME_GuildBattleEnter->SetVisable( bVisable );
}

//-------------------------------------------------------------------------------------------------------
void CUI_ID_FRAME_GuildBattleEnter::Refresh()
{
	s_CUI_ID_FRAME_GuildBattleEnter.SetVisable(true);

	if ( !m_pID_FRAME_GuildBattleEnter )
		return;

	m_pID_TEXT_Name1->SetText(thePlayerRole.GetGuildNameById(thePlayerRole.GetRedCampGuildId()));
	m_pID_TEXT_Name2->SetText(thePlayerRole.GetGuildNameById(thePlayerRole.GetBlueCampGuildId()));
	m_pID_TEXT_Text->SetText(theXmlString.GetString(eText_GuildCamp_EnterBattleFiled));
}

// Button
bool CUI_ID_FRAME_GuildBattleEnter::ID_BUTTON_EnterOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattleEnter )
		return false;

	//如果在队伍的话 不可以进入战场
	
	//if(thePlayerRole.GetGroupId() != -1)
	//{
	//	//提示玩家组队不可以进入战场
	//	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eClient_FlyToBattle_InTeam));
	//	return false;
	//}

	if(IsGameBattle)
	{
		MsgEnterGameBattleReq msg;
		msg.uchBattleType = GameBattleDefine::GameBattle_Type_GuildGeneral;
		GettheNetworkInput().SendMsg(&msg);
	}
	else
	{
		MsgEnterCampBattleReq msg;
		msg.uchBattleType = CampDefine::BattleTypeGuild;
		GettheNetworkInput().SendMsg(&msg);
	}

	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_GuildCamp_EnterBattleReq));
	_SetVisable(false);
	return true;
}
bool CUI_ID_FRAME_GuildBattleEnter::ID_BUTTON_FlyToMapOnButtonClick( ControlObject* pSender )
{
	//飞到战场的入口地图
	if ( !m_pID_FRAME_GuildBattleEnter )
		return false;

	//判断玩家是否在摆摊状态 是的话 不可以传送
	if(theHeroGame.GetPlayerMgr()->GetMe()->IsPrivateShopOpen())
	{
		//提示玩家
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eClient_FlyToMap_Stall));
		return true;
	}

	MsgFlytoKindom flyto;
	flyto.map_id = m_nKingdomMapID;
	flyto.map_x = m_fKingdomX;
	flyto.map_y = m_fKingdomY;
	GettheNetworkInput().SendMsg(&flyto);
	//SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_GuildBattleEnter::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildBattleEnter )
		return false;

	_SetVisable(false);
	return true;
}
void CUI_ID_FRAME_GuildBattleEnter::SetKingdomMapInfo(unsigned long mapid,float x,float y)
{
	m_nKingdomMapID = mapid;
	m_fKingdomX = x;
	m_fKingdomY = y;
}