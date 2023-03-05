/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\MiniMap.cpp
*********************************************************************/
#include "MeTerrain/stdafx.h"
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ItemDetail.h"
#include "GameMain.h"
#include "ui/MiniMapUI.h"
#include "PlayerRole.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "ScreenInfoManager.h"
#include "MeAudio/MeAudio.h"
#include "Effect.h"
#include "Select.h"
#include "Login.h"
#include "Group_Me.h"
#include "ChatInfoBox.h"
#include "MessageBox.h"
#include "LoadMap.h"
#include "AllNpcList.h"
#include "XmlStringLanguage.h"
// #include "event_timeable_configure.h"
// #include "event_timeable.h"
#include "timecooling_configure.h"
#include "Main.h"
#include "include/MiniMap.h"
#include "color_config.h"
#include "core/Name.h"
#include "WorldMap.h"
#include "ui/ActivityList.h"
#include "ui/AllNpcList.h"
#include "ui/Protect.h"
#include "ExitGame.h"
#include "ui/Task_Track.h"
#include "ui/SystemSettingUI.h"
#include "ui/SystemSetting.h"
#include "ui/GameSetting.h"
#include "ui/GameSettingFunction.h"
#include "Cfg.h"
#include "CrossMapPF.h"
#include "UserData.h"
#include "PathDirection.h"
#include "ShopCenter.h"
#include "AutoAttackSet.h"
#include "WealthProtect.h"
#include "Common.h"
#include "CountryDefine.h"
#include "CountryFunction.h"
#include "Ui/Achivement.h"
#include "Ui/DoubleExp.h"
#include "ActivityDay.h"
#include "RankList.h"
#include "shortcutkey_configure.h"
//#include "MailMain.h"
#include "MailReceive.h"
#include "ui/AboutPeople.h"
#include "Ui/GoldTrade.h"
#include "Card.h"
#include "chat_list.h"
#include "SelectChannel.h"
#include "ui/QuestEntrust.h"
#define PSMOFFSET 5

extern CUI_ChatInfoBox s_CUI_ChatInfoBox;
extern BOOL g_bMouseMoveMode; //鼠标移动模式
extern BOOL g_bRenderUI;
extern int g_nMiniMapSight;
extern CHeroGame* theApp;

const float MINIMAP_MAX_ZOOM = 2.0f;
// 第几波提示剩余时间少于GAME_STAGE_LIMIT_TIME，m_pID_TEXT_NextTime颜色变红
const int GAME_STAGE_LIMIT_TIME = 10;
const int EFFECT_PLAY_MIN_LEVEL = 10;

bool	CUI_ID_FRAME_MiniMap::m_bTipActive = false;

CUI_ID_FRAME_MiniMap s_CUI_ID_FRAME_MiniMap;
extern void SetTipAndHotKey(ControlButton* pCtl, const char* szText, AN_Configure_ShortcutKey::ShortCutKey_Configure key);
extern void SetTipAndHotKey(ControlButton* pCtl, AN_Configure_ShortcutKey::ShortCutKey_Configure key);

MAP_FRAME_RUN( s_CUI_ID_FRAME_MiniMap, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_MiniMap, OnFrameRender )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_MiniMap, OnFrameRenderPostUI )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_MiniMap, OnFrameRenderNeedRedraw)
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_DirectOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_HelpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_NPCListOnButtonClick)
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_TrackOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_HideOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_AppearOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_ActivityOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_ProtectTimeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_MapSizeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_SystemSettingOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_ShopOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_AutoAttackOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_EmailOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_MapSizeSmallOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_AchivementOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_DoubleExpOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_SearchTeamOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_QuickEquipOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_RankOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_ActivityDayOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_MailOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_TEXT_MailOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_FuJinOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_TradeOnButtonClick )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_PlayerShowALLOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_PlayerShowAmityOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_PlayerHideALLOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_PlayerShowAntagonizeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_CardOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_TEXT_CardOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_TEXT_ShopOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_CHECKBOX_HideChatListOnClick)
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_ChannelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MiniMap, ID_BUTTON_OpenQuestEntrustOnButtonClick )
//静态变量
void On_PICTURE_WorldMapMouseOn( ControlObject* pSender )
{
    CUI_ID_FRAME_MiniMap::m_bTipActive = true;
}

void On_PICTURE_WorldMapMouseLeave( ControlObject* pSender )
{
	CUI_ID_FRAME_MiniMap::m_bTipActive = false;
}

bool CUI_ID_FRAME_MiniMap::frame_msg(UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed)
{
    guardfunc;
    switch(msg)
    {
    case WM_LBUTTONDOWN:
        {
            GetAdvancedMiniMap()->ProcessMinimapMouseDownL(LOWORD(lParam), HIWORD(lParam));
        }
        break;
    default:
        break;
    }
    return FALSE;
    unguard;
}

CUI_ID_FRAME_MiniMap::CUI_ID_FRAME_MiniMap()
{
	ResetMembers();

    m_GroupAllUI.Clear();


    m_bHaveNew_event = false;
    m_tmBegin_show_tip = 0;
    m_bIsNormal_state = false;
    m_bIsPress_state = false;
    m_tmBtn_raytime = 0;

    strLastTileName = "";
    strLastZoneName = "";

    m_bZoomIn = true;
    m_strMapName.clear();
    m_strAreaName.clear();
    m_dwCurEctypeId = 0;
    bIsOnButtonDisMount = false;
    bFullScreen = false;	//保存全屏值 假全屏
    m_nPing = 0;

    m_strServerName.clear();
    m_fZoomScale	= 1.0f;

    m_bLowSetting = false;
    m_bAutoRuning = false;
    m_dwEctypeMapEndTime = 0;

    m_dwStartGSTime = 0;
    m_GSDuration = 0;
    m_gameStage = -1;
    m_maxGameStage = 0;

    m_lastPFX = 0.0f;
    m_lastPFY = 0.0f;
    m_nMap = -1;

    m_pTodayActEff = NULL;
    m_bPlayTodayActEffect = false;

	m_dwStartSplash = 0;

	for (int i = 0 ; i < PSM_Max ; i++)
	{
		m_pPlayerShowBtn[i] = NULL;
	}
	m_pCurPlayerShowBtn = NULL;

	m_bPlayerShowModeOpen = false;
	m_nPlayerRenderFlag = CPlayerMgr::EPlayerRenderFlag::EPRF_ALL;
	m_bCompositor = false;

	ShowPlayerBtnPosX = 0;
	ShowPlayerBtnPosY = 0;
}

void CUI_ID_FRAME_MiniMap::ResetMembers()
{
	m_pID_FRAME_MiniMap = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Direct = NULL;
	m_pID_PICTURE_MiniMap = NULL;
	m_pID_PICTURE_Map = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_BUTTON_Help = NULL;
	m_pID_BUTTON_NPCList = NULL;
	m_pID_TEXT_PlayerPos = NULL;
//	m_pID_BUTTON_Track = NULL;
	m_pID_BUTTON_Hide = NULL;
	m_pID_BUTTON_Appear = NULL;
	m_pID_BUTTON_Activity = NULL;
    m_pID_BUTTON_ActivityDay = NULL;
	m_pID_BUTTON_ProtectTime = NULL;
	m_pID_BUTTON_MapSize = NULL;
	m_pID_BUTTON_SystemSetting = NULL;
 	m_pID_PICTURE_Green = NULL;
 	m_pID_PICTURE_Yellow = NULL;
 	m_pID_PICTURE_Red = NULL;
// 	m_pID_TEXT_PlaceTime = NULL;
 	m_pID_BUTTON_Shop = NULL;
// 
// 	m_pID_TEXT_NextTime = NULL;
	m_pID_BUTTON_AutoAttack = NULL;
	m_pID_BUTTON_Email = NULL;
	m_pID_PICTURE_Email = NULL;
	m_pID_TEXT_Email = NULL;
	m_pID_BUTTON_MapSizeSmall = NULL;
	m_pID_BUTTON_Achivement = NULL;
	m_pID_BUTTON_DoubleExp = NULL;
// 	m_pID_BUTTON_SearchTeam = NULL;	
// 	m_pID_BUTTON_QuickEquip = NULL;
	m_pID_BUTTON_Rank = NULL;
    m_pID_PICTURE_Effect = NULL;
	m_pID_BUTTON_Mail = NULL;
	m_pID_BUTTON_FuJin = NULL;
	m_pID_TEXT_Activity = NULL;
	m_pID_BUTTON_Trade = NULL;

	m_pID_BUTTON_PlayerShowALL = NULL;
	m_pID_BUTTON_PlayerShowAmity = NULL;
	m_pID_BUTTON_PlayerHideALL = NULL;
	m_pID_BUTTON_PlayerShowAntagonize = NULL;

	m_pID_BUTTON_Card = NULL;
	m_pID_TEXT_Card = NULL;
	m_pID_TEXT_Shop = NULL;

	m_pID_CHECKBOX_HideChatList = NULL;
	m_pID_TEXT_Channel = NULL;
	m_pID_BUTTON_Channel = NULL;
	m_pID_BUTTON_OpenQuestEntrust = NULL;
}

// Frame
bool CUI_ID_FRAME_MiniMap::OnFrameRun()
{
    guardfunc;
	if( !m_GroupAllUI.IsVisible() )
		return true;
	if( !GameState.bRenderMiniMap )
		return false;
	if( !s_CUI_ID_FRAME_LoadMap.IsMapLoaded() )
		return false;
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (pMe == NULL)
	{
		return false;
	}
	GetAdvancedMiniMap()->Run(pMe->GetPos().x,
		pMe->GetPos().y);
    RefreshGameStageTime();
	UpdateProtectTimeCountDown();
	UpdateEctypeMapTimeRemain();
	ProcessMailNotify();  //处理邮件通知
    return true;
    unguard;
}

bool CUI_ID_FRAME_MiniMap::OnFrameRender()
{
	guardfunc;
	if( !m_GroupAllUI.IsVisible() )
		return true;
	if( !GameState.bRenderMiniMap )
		return false;

	if( !s_CUI_ID_FRAME_LoadMap.IsMapLoaded() )
		return false;

	{
		//mInImap


		if( g_bRenderUI && theHeroGame.GetPlayerMgr()->GetMe() )
		{
			if ( GetAdvancedMiniMap())
				GetAdvancedMiniMap()->Render( 
				theHeroGame.GetPlayerMgr()->GetMe()->GetPos().x,
				theHeroGame.GetPlayerMgr()->GetMe()->GetPos().y);
		}

	}

    
	return true;
	unguard;
}

bool CUI_ID_FRAME_MiniMap::OnFrameRenderPostUI()
{
    DisplayTodayActEffect();
    return true;
}

bool CUI_ID_FRAME_MiniMap::OnFrameRenderNeedRedraw()
{
    guardfunc;
    if( !m_GroupAllUI.IsVisible() )
        return true;
    if( !GameState.bRenderMiniMap )
        return false;
    if( !s_CUI_ID_FRAME_LoadMap.IsMapLoaded() )
        return false;

    {
        //mInImap


        if( g_bRenderUI && theHeroGame.GetPlayerMgr()->GetMe() )
        {
            if ( GetAdvancedMiniMap())
                GetAdvancedMiniMap()->RenderNeedRedraw( CAdvancedMiniMap::eMinMode,
                theHeroGame.GetPlayerMgr()->GetMe()->GetPos().x,
                theHeroGame.GetPlayerMgr()->GetMe()->GetPos().y);
        }

    }



    return true;
    unguard;
}
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_MapSizeSmallOnButtonClick( ControlObject* pSender )
{
	if(m_fZoomScale > 1.0f)
	{
		m_fZoomScale -= 0.5;
		s_CUI_ID_FRAME_LOGIN.SetSmallMapScale(m_fZoomScale);
	}
	return true;
}
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_AchivementOnButtonClick( ControlObject* pSender )
{
	//s_CUI_ID_FRAME_Achivement.SetVisable(!s_CUI_ID_FRAME_Achivement.IsVisable());
	return true;
}
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_DoubleExpOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_DuobleExp.SetVisable(!s_CUI_ID_FRAME_DuobleExp.IsVisable());
	return true;
}
// Button
// bool CUI_ID_FRAME_MiniMap::ID_BUTTON_SearchTeamOnButtonClick( ControlObject* pSender )
// {
// 	return true;
// }
// // Button
// bool CUI_ID_FRAME_MiniMap::ID_BUTTON_QuickEquipOnButtonClick( ControlObject* pSender )
// {
// 	return true;
// }
// Button
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_RankOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MiniMap )
		return false;
	s_CUI_ID_FRAME_RankList.SetVisable(!s_CUI_ID_FRAME_RankList.IsVisable());
	return true;
}
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_HideOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MiniMap )
		return false;

    m_pID_FRAME_MiniMap->SetMsgHoldup( false );
    m_GroupAllUI.SetVisible( !m_GroupAllUI.IsVisible() );
    m_pID_BUTTON_Hide->SetVisable(false);
    m_pID_BUTTON_Appear->SetVisable(true);

    m_pID_TEXT_Email->SetVisable(false);
	m_pID_TEXT_Card->SetVisable(false);
	m_pID_TEXT_Shop->SetVisable(false);
    //m_pID_BUTTON_Email->SetVisable(false);
    //m_pID_PICTURE_Email->SetVisable(false);
	m_pCurPlayerShowBtn->SetVisable(false);
	for (int i = 0 ; i < PSM_Max ; i++)
	{
		m_pPlayerShowBtn[i]->SetVisable(false);
	}
	m_bPlayerShowModeOpen = false;
    return true;
}
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_AppearOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MiniMap )
		return false;

    m_pID_FRAME_MiniMap->SetMsgHoldup( true );
    m_GroupAllUI.SetVisible( !m_GroupAllUI.IsVisible() );
    m_pID_BUTTON_Hide->SetVisable(true);
    m_pID_BUTTON_Appear->SetVisable(false);

    m_pID_TEXT_Email->SetVisable(m_bLastMailVisable);
	m_pID_TEXT_Card->SetVisable(m_bLastCardVisable);
	m_pID_TEXT_Shop->SetVisable(m_bLastShopVisable);
    //m_pID_BUTTON_Email->SetVisable(m_bLastMailVisable);
    //m_pID_PICTURE_Email->SetVisable(m_bLastMailVisable);
	m_pCurPlayerShowBtn->SetVisable(true);

    UpdatePing();
    return true;
}
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_ActivityOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MiniMap )
		return false;

    s_CUI_ID_FRAME_ActivityList.SetVisable( !s_CUI_ID_FRAME_ActivityList.IsVisable() );
    return true;
}

bool CUI_ID_FRAME_MiniMap::ID_BUTTON_ActivityDayOnButtonClick( ControlObject* pSender )
{
    if( !m_pID_FRAME_MiniMap )
        return false;

    if( !s_CUI_ID_FRAME_ActivityDay.IsVisable() )
        m_bPlayTodayActEffect = false;

    s_CUI_ID_FRAME_ActivityDay.SetVisable( !s_CUI_ID_FRAME_ActivityDay.IsVisable() );
    return true;
}

void CUI_ID_FRAME_MiniMap::SetMailSender(const char* pszMailSender)
{
    if(!pszMailSender)
        return;

    m_SenderMail = pszMailSender;
}


// Button
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_MapSizeOnButtonClick( ControlObject* pSender )
{
    guardfunc;
	if( !m_pID_FRAME_MiniMap )
		return false;

//     if(m_fZoomScale < MINIMAP_MAX_ZOOM && m_bZoomIn)
//     {//放大
//         m_fZoomScale += 0.5;
//         s_CUI_ID_FRAME_LOGIN.SetSmallMapScale(m_fZoomScale);
//     }
//     else
//         m_bZoomIn = false;
// 
//     if(m_fZoomScale > 1.0 && !m_bZoomIn)
//     {
//         m_fZoomScale = 1.0;
//         s_CUI_ID_FRAME_LOGIN.SetSmallMapScale(m_fZoomScale);
//         m_bZoomIn = true;
//     }
//     else
//         m_bZoomIn = true;

	if(m_fZoomScale < MINIMAP_MAX_ZOOM)
	{
		m_fZoomScale += 0.5;
		s_CUI_ID_FRAME_LOGIN.SetSmallMapScale(m_fZoomScale);
	}

    return true;
    unguard;
}

bool CUI_ID_FRAME_MiniMap::ID_BUTTON_NPCListOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MiniMap )
		return false;

    s_CUI_ID_FRAME_AllNpcList.SetVisable(!s_CUI_ID_FRAME_AllNpcList.IsVisable());
	s_CUI_ID_FRAME_AllNpcList.init();
    return true;
}

// bool CUI_ID_FRAME_MiniMap::ID_BUTTON_HelpOnButtonClick( ControlObject* pSender )
// {
//     guardfunc;
// 	if( !m_pID_FRAME_MiniMap )
// 		return false;
	//底层已经实现了，不再重复打开
//     startHelp();

//     return false;
//     unguard;
// }
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_ProtectTimeOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MiniMap )
		return false;

    s_CUI_ID_FRAME_Protect.SetVisable(true);
    return true;
}
// bool CUI_ID_FRAME_MiniMap::ID_BUTTON_TrackOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_MiniMap )
// 		return false;
// 
//     s_CUI_ID_FRAME_TRACK.SetVisable(!s_CUI_ID_FRAME_TRACK.IsVisable());
//     return true;
// }
 bool CUI_ID_FRAME_MiniMap::ID_BUTTON_ShopOnButtonClick( ControlObject* pSender )
 {
 	if( !m_pID_FRAME_MiniMap )
 		return false;
 
     s_CUI_ID_FRAME_ShopCenter.SetVisable(!s_CUI_ID_FRAME_ShopCenter.IsVisable());
     return true;
 }

bool CUI_ID_FRAME_MiniMap::ID_BUTTON_SystemSettingOnButtonClick( ControlObject* pSender )
{		
// 	if( !m_pID_FRAME_MiniMap )
// 		return false;
// 
//     bool bLow = m_bLowSetting;
//     if( m_bLowSetting )
//     {
//         SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_RENDER_DISTANCE, 300 );
//         SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_TERRAIN_DETAIL, 1 );
//         SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_SKY, 0 );
//         SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_WATER, 0 );
//         SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_GRASS, 1 );
//         SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_ADVANCE, 0 );
//         SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_BLOOM, 0 );
//         SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_SHADOW, 0 );
//         SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_LIGHTSHAFT, 0 );
//         SystemSetting::Instance()->CommitChanges();
//         s_CUI_ID_FRAME_Systemset.Refresh();
// 
//         GameSetting::Instance()->SetLevel( GameSetting::eGSC_SHOWPLAYERNUMBER, 0 );
//         s_CUI_ID_FRAME_GameSettingFunction.RefreshUI();
// 
// 
//     }
//     else
//     {
//         char szSetting[MAX_PATH] = {0};
//         MeSprintf_s(szSetting,sizeof(szSetting)/sizeof(char) - 1, "%s/Client/UserData/%s", GetRootPath(), SystemSetting::Instance()->GetCustomSettingFile() );
//         SystemSetting::Instance()->LoadSetting( szSetting );
//         SystemSetting::Instance()->CommitChanges();
//         MeSprintf_s( szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s%s", CUserData::Instance()->GetUserDataPath(), GameSetting::Instance()->GetCustomSettingDirectory() );
//         GameSetting::Instance()->LoadSetting( szSetting );
//         GameSetting::Instance()->CommitChanges();
//         s_CUI_ID_FRAME_Systemset.Refresh();
//         s_CUI_ID_FRAME_GameSettingFunction.RefreshUI();
// 
//     }
//     m_bLowSetting = !bLow;
//     if( m_bLowSetting )
//     {
//         m_pID_BUTTON_SystemSetting->setTip( theXmlString.GetString( eText_DefaultSetting ) );	
//     }
//     else
//     {
//         m_pID_BUTTON_SystemSetting->setTip( theXmlString.GetString( eText_LowSetting ) );
//     }
     return true;
}

// Button
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_AutoAttackOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MiniMap )
		return false;

    s_CUI_ID_FRAME_AutoAttackSet.SetVisable(!s_CUI_ID_FRAME_AutoAttackSet.IsVisable());
    return true;
}

bool CUI_ID_FRAME_MiniMap::ID_BUTTON_EmailOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MiniMap )
		return false;

	char szWord[256] = {0};
    MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_MailNewNotify),m_SenderMail.c_str());

    s_CUI_ID_FRAME_MessageBox.Show(szWord," ",CUI_ID_FRAME_MessageBox::eTypeYesNo,true,MailProcessPress);

    return true;
}

void CUI_ID_FRAME_MiniMap::ID_CHECKBOX_HideChatListOnClick(ControlObject* pSender, bool* pbChecked)
{
	if( !m_pID_FRAME_MiniMap )
		return;
	if(m_pID_CHECKBOX_HideChatList->IsChecked())
	{
		m_pID_CHECKBOX_HideChatList->SetCheck(true);
		s_CUI_ID_FRAME_chatInfoList.SetVisable(false);
		s_CUI_ID_FRAME_InfoList.SetVisable(false);
	}
	else
	{
		m_pID_CHECKBOX_HideChatList->SetCheck(false);
		s_CUI_ID_FRAME_chatInfoList.SetVisable(true);
		s_CUI_ID_FRAME_InfoList.SetVisable(true);
	}
}

void CUI_ID_FRAME_MiniMap::InitializeAtEnterWorld()
{
    if( !m_pID_FRAME_MiniMap )
        return;

    m_pID_FRAME_MiniMap->SetVisable( false );
    m_pID_BUTTON_Hide->SetVisable(true);
    m_pID_BUTTON_Appear->SetVisable(false);

    //初始化 小地图 缩放
    m_fZoomScale = s_CUI_ID_FRAME_LOGIN.GetSmallMapScale();
    //取[0,2] 之间
    m_fZoomScale = m_fZoomScale < 1.0f ? 1.0f : m_fZoomScale > MINIMAP_MAX_ZOOM ? MINIMAP_MAX_ZOOM : m_fZoomScale; 

    m_pID_FRAME_MiniMap->SetMsgProcFun(frame_msg);


    // 可隐藏所有ui

    m_GroupAllUI.AddControl( m_pID_PICTURE_Map);
    m_GroupAllUI.AddControl( m_pID_PICTURE_MiniMap);
    m_GroupAllUI.AddControl( m_pID_TEXT_Name);
    m_GroupAllUI.AddControl( m_pID_BUTTON_MapSize);
    m_GroupAllUI.AddControl( m_pID_TEXT_PlayerPos);
    m_GroupAllUI.AddControl( m_pID_BUTTON_NPCList);		
    m_GroupAllUI.AddControl( m_pID_BUTTON_Help);
    //    m_GroupAllUI.AddControl( m_pID_BUTTON_Track );
    m_GroupAllUI.AddControl( m_pID_BUTTON_Shop );
    m_GroupAllUI.AddControl( m_pID_BUTTON_Activity );
    m_GroupAllUI.AddControl( m_pID_BUTTON_ActivityDay );
    m_GroupAllUI.AddControl( m_pID_BUTTON_Direct );
    m_GroupAllUI.AddControl( m_pID_BUTTON_Cancel );
	m_GroupAllUI.AddControl( m_pID_BUTTON_SystemSetting );
    m_GroupAllUI.AddControl( m_pID_PICTURE_Red );
    m_GroupAllUI.AddControl( m_pID_PICTURE_Yellow );
    m_GroupAllUI.AddControl( m_pID_PICTURE_Green );
    m_GroupAllUI.AddControl( m_pID_BUTTON_AutoAttack);
    m_GroupAllUI.AddControl( m_pID_BUTTON_MapSizeSmall );
	m_GroupAllUI.AddControl( m_pID_BUTTON_Achivement );
	m_GroupAllUI.AddControl( m_pID_BUTTON_DoubleExp );
    // 	m_GroupAllUI.AddControl( m_pID_BUTTON_SearchTeam );
    // 	m_GroupAllUI.AddControl( m_pID_BUTTON_QuickEquip );
    m_GroupAllUI.AddControl( m_pID_BUTTON_Rank);	
	m_GroupAllUI.AddControl( m_pID_BUTTON_Mail);
	m_GroupAllUI.AddControl( m_pID_BUTTON_FuJin);
	m_GroupAllUI.AddControl( m_pID_BUTTON_Trade);
	m_GroupAllUI.AddControl( m_pID_BUTTON_Card );
	m_GroupAllUI.AddControl( m_pID_CHECKBOX_HideChatList );
	m_GroupAllUI.AddControl( m_pID_TEXT_Channel );
	m_GroupAllUI.AddControl( m_pID_BUTTON_Channel );
	m_GroupAllUI.AddControl( m_pID_BUTTON_OpenQuestEntrust);
	/*m_GroupAllUI.AddControl( m_pID_BUTTON_PlayerShowALL );
	m_GroupAllUI.AddControl( m_pID_BUTTON_PlayerShowAmity );
	m_GroupAllUI.AddControl( m_pID_BUTTON_PlayerHideALL );
	m_GroupAllUI.AddControl( m_pID_BUTTON_PlayerShowAntagonize );*/

    m_pID_PICTURE_Map->SetOnMouseOn(On_PICTURE_WorldMapMouseOn);
	m_pID_PICTURE_Map->SetOnMouseLeave(On_PICTURE_WorldMapMouseLeave);
    m_GroupAllUI.SetVisible( true );


    m_dwStartGSTime    = 0;
    m_bLastMailVisable = false;
	m_bLastCardVisable = false;
	m_bLastShopVisable = false;

    //m_pID_BUTTON_Email->SetVisable(m_bLastMailVisable);
    //m_pID_PICTURE_Email->SetVisable(m_bLastMailVisable);
    m_pID_TEXT_Email->SetVisable(false);
	m_pID_TEXT_Card->SetVisable(m_bLastCardVisable);
	m_pID_TEXT_Shop->SetVisable(m_bLastShopVisable);
	m_pID_TEXT_Activity->SetVisable(false);

    m_pID_BUTTON_SystemSetting->SetShowTip( true );

// #define SHOW_BUTTON_TIP(ui)	\
//     ui->SetShowTip(true);	\
//     ui->setTip(ui->GetData()->m_szCaption);

//     SHOW_BUTTON_TIP( m_pID_BUTTON_MapSize);
//     SHOW_BUTTON_TIP( m_pID_BUTTON_NPCList);		
//     SHOW_BUTTON_TIP( m_pID_BUTTON_Help);
    //    SHOW_BUTTON_TIP( m_pID_BUTTON_Track );
//     SHOW_BUTTON_TIP( m_pID_BUTTON_Shop );
//     SHOW_BUTTON_TIP( m_pID_BUTTON_Activity );
//     SHOW_BUTTON_TIP( m_pID_BUTTON_Direct );
//     SHOW_BUTTON_TIP( m_pID_BUTTON_Cancel );
//     SHOW_BUTTON_TIP( m_pID_BUTTON_AutoAttack);
//     SHOW_BUTTON_TIP( m_pID_BUTTON_MapSizeSmall );
// 	SHOW_BUTTON_TIP( m_pID_BUTTON_Achivement );
    // 	SHOW_BUTTON_TIP( m_pID_BUTTON_SearchTeam );
    // 	SHOW_BUTTON_TIP( m_pID_BUTTON_QuickEquip );
//     SHOW_BUTTON_TIP( m_pID_BUTTON_Rank);

    m_pID_TEXT_Email->SetMsgHoldup(false);
	m_pID_TEXT_Card->SetMsgHoldup(false);
	m_pID_TEXT_Shop->SetMsgHoldup(false);
    //m_pID_PICTURE_Email->SetMsgHoldup(false);

    if( thePlayerRole.GetLevel() >= EFFECT_PLAY_MIN_LEVEL && !s_CUI_ID_FRAME_ActivityDay.IsVisable() )
        m_bPlayTodayActEffect = true;
    else
        m_bPlayTodayActEffect = false;

	for (int i = 0 ; i < PSM_Max ; i++)
	{
		m_pPlayerShowBtn[i]->SetShowTip(true);
	}
}

// Button
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_MailOnButtonClick( ControlObject* pSender )
{
	//s_CUI_ID_FRAME_MailMain.SetVisable(!s_CUI_ID_FRAME_MailMain.IsVisable());
	s_CUI_ID_FRAME_MailReceive.SetVisable(!s_CUI_ID_FRAME_MailReceive.IsVisable());
	return true;
}

bool CUI_ID_FRAME_MiniMap::ID_TEXT_MailOnButtonClick( ControlObject* pSender )
{
	// 关闭新邮件提示
	m_bLastMailVisable = false;
	m_dwStartSplash = 0;
	m_pID_TEXT_Email->SetVisable(false);

	s_CUI_ID_FRAME_MailReceive.SetVisable(!s_CUI_ID_FRAME_MailReceive.IsVisable());
	return true;
}

// Button
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_FuJinOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_AboutPeople.SetVisable(!s_CUI_ID_FRAME_AboutPeople.IsVisable());

	return true;
}
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_TradeOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_GoldTrade.SetVisable(!s_CUI_ID_FRAME_GoldTrade.IsVisable());

	return true;
}

// Button
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_CardOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_CARD.SetVisable(!s_CUI_ID_FRAME_CARD.IsVisable());
	return true;
}

bool CUI_ID_FRAME_MiniMap::ID_TEXT_CardOnButtonClick( ControlObject* pSender )
{
	m_bLastCardVisable = false;
	m_pID_TEXT_Card->SetVisable(m_bLastCardVisable);

	s_CUI_ID_FRAME_CARD.SetVisable(!s_CUI_ID_FRAME_CARD.IsVisable());
	return true;
}

bool CUI_ID_FRAME_MiniMap::ID_TEXT_ShopOnButtonClick( ControlObject* pSender )
{
	m_bLastShopVisable = false;
	m_pID_TEXT_Shop->SetVisable(m_bLastShopVisable);

	 s_CUI_ID_FRAME_ShopCenter.SetVisable(!s_CUI_ID_FRAME_ShopCenter.IsVisable());
	return true;
}
// 装载UI
bool CUI_ID_FRAME_MiniMap::_LoadUI()
{
    guardfunc;
    DWORD dwResult = theUiManager.AddFrame( "data\\ui\\MiniMap.meui", true, UI_Render_LayerFirst );
    if ( dwResult == 0 )
    {
        MESSAGE_BOX("读取文件[UI\\MiniMap.UI]失败")
            return false;
    }
    return DoControlConnect();
    unguard;
}

// 关连控件
bool CUI_ID_FRAME_MiniMap::DoControlConnect()
{
    guardfunc;
    theUiManager.OnFrameRun( ID_FRAME_MiniMap, s_CUI_ID_FRAME_MiniMapOnFrameRun );
    theUiManager.OnFrameRender( ID_FRAME_MiniMap, s_CUI_ID_FRAME_MiniMapOnFrameRender, true );
    theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_MapSize, s_CUI_ID_FRAME_MiniMapID_BUTTON_MapSizeOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_Hide, s_CUI_ID_FRAME_MiniMapID_BUTTON_HideOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_Appear, s_CUI_ID_FRAME_MiniMapID_BUTTON_AppearOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_NPClist, s_CUI_ID_FRAME_MiniMapID_BUTTON_NPCListOnButtonClick );
//     theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_Help,s_CUI_ID_FRAME_MiniMapID_BUTTON_HelpOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_Activity, s_CUI_ID_FRAME_MiniMapID_BUTTON_ActivityOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_Direct, s_CUI_ID_FRAME_MiniMapID_BUTTON_DirectOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_Cancel, s_CUI_ID_FRAME_MiniMapID_BUTTON_CancelOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_ProtectTime, s_CUI_ID_FRAME_MiniMapID_BUTTON_ProtectTimeOnButtonClick );
//     theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_Track, s_CUI_ID_FRAME_MiniMapID_BUTTON_TrackOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_SystemSetting, s_CUI_ID_FRAME_MiniMapID_BUTTON_SystemSettingOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_Shop, s_CUI_ID_FRAME_MiniMapID_BUTTON_ShopOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_AutoAttack, s_CUI_ID_FRAME_MiniMapID_BUTTON_AutoAttackOnButtonClick );

    theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_Email, s_CUI_ID_FRAME_MiniMapID_BUTTON_EmailOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_TEXT_Email, s_CUI_ID_FRAME_MiniMapID_TEXT_MailOnButtonClick );
	
	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_MapSizeSmall, s_CUI_ID_FRAME_MiniMapID_BUTTON_MapSizeSmallOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_Achivement, s_CUI_ID_FRAME_MiniMapID_BUTTON_AchivementOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_DoubleExp, s_CUI_ID_FRAME_MiniMapID_BUTTON_DoubleExpOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_SearchTeam, s_CUI_ID_FRAME_MiniMapID_BUTTON_SearchTeamOnButtonClick );	
//	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_QuickEquip, s_CUI_ID_FRAME_MiniMapID_BUTTON_QuickEquipOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_Rank, s_CUI_ID_FRAME_MiniMapID_BUTTON_RankOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_ActivityDay, s_CUI_ID_FRAME_MiniMapID_BUTTON_ActivityDayOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_Mail, s_CUI_ID_FRAME_MiniMapID_BUTTON_MailOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_FuJin, s_CUI_ID_FRAME_MiniMapID_BUTTON_FuJinOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_Trade, s_CUI_ID_FRAME_MiniMapID_BUTTON_TradeOnButtonClick );

	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_PlayerShowALL, s_CUI_ID_FRAME_MiniMapID_BUTTON_PlayerShowALLOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_PlayerShowAmity, s_CUI_ID_FRAME_MiniMapID_BUTTON_PlayerShowAmityOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_PlayerHideALL, s_CUI_ID_FRAME_MiniMapID_BUTTON_PlayerHideALLOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_PlayerShowAntagonize, s_CUI_ID_FRAME_MiniMapID_BUTTON_PlayerShowAntagonizeOnButtonClick );

	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_Card, s_CUI_ID_FRAME_MiniMapID_BUTTON_CardOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_TEXT_Card, s_CUI_ID_FRAME_MiniMapID_TEXT_CardOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_TEXT_Shop, s_CUI_ID_FRAME_MiniMapID_TEXT_ShopOnButtonClick );

	theUiManager.OnCheckBoxCheck( ID_FRAME_MiniMap, ID_CHECKBOX_HideChatList, s_CUI_ID_FRAME_MiniMapID_CHECKBOX_HideChatListOnClick);
	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_Channel, s_CUI_ID_FRAME_MiniMapID_BUTTON_ChannelOnButtonClick );

	theUiManager.OnButtonClick( ID_FRAME_MiniMap, ID_BUTTON_OpenQuestEntrust, s_CUI_ID_FRAME_MiniMapID_BUTTON_OpenQuestEntrustOnButtonClick );
	

    m_pID_FRAME_MiniMap = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_MiniMap );
    m_pID_PICTURE_MiniMap = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_PICTURE_MiniMap );
    m_pID_PICTURE_Map = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_PICTURE_Map );
    m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_TEXT_Name );
    m_pID_BUTTON_MapSize = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_MapSize );
    m_pID_BUTTON_Hide = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_Hide );
    m_pID_BUTTON_Appear = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_Appear );
    m_pID_TEXT_PlayerPos = (ControlText*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_TEXT_PlayerPos );
    m_pID_BUTTON_NPCList = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_NPClist );
    m_pID_BUTTON_Help = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_Help );
    m_pID_BUTTON_Activity = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_Activity );
    m_pID_BUTTON_ProtectTime = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_ProtectTime );
    //     m_pID_BUTTON_Track = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_Track );
    m_pID_BUTTON_Shop = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_Shop );
    m_pID_BUTTON_SystemSetting = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_SystemSetting );
    m_pID_PICTURE_Red = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_PICTURE_Red );
    m_pID_PICTURE_Yellow = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_PICTURE_Yellow );
    m_pID_PICTURE_Green = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_PICTURE_Green );
    //     m_pID_TEXT_PlaceTime = (ControlText*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_TEXT_PlaceTime );
    m_pID_BUTTON_Direct = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_Direct );
    m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_Cancel );
    //    m_pID_TEXT_NextTime = (ControlText*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_TEXT_NextTime );
    m_pID_BUTTON_AutoAttack = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_AutoAttack );
    m_pID_BUTTON_Email = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_Email );
    m_pID_PICTURE_Email = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_PICTURE_Email );
	m_pID_TEXT_Email = (ControlText*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_TEXT_Email );
	m_pID_BUTTON_MapSizeSmall = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_MapSizeSmall );
	m_pID_BUTTON_Achivement = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_Achivement );
	m_pID_BUTTON_DoubleExp = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_DoubleExp );
// 	m_pID_BUTTON_SearchTeam = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_SearchTeam );
// 	m_pID_BUTTON_QuickEquip = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_QuickEquip );
	m_pID_BUTTON_Rank = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_Rank );
    m_pID_BUTTON_ActivityDay = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_ActivityDay );
    m_pID_PICTURE_Effect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_PICTURE_Effect );
	m_pID_BUTTON_Mail = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_Mail );
	m_pID_BUTTON_FuJin = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_FuJin );
	m_pID_BUTTON_Trade = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_Trade );
	m_pID_TEXT_Activity = (ControlText*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_TEXT_Activity );

	m_pID_BUTTON_PlayerShowALL = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_PlayerShowALL );
	m_pID_BUTTON_PlayerShowAmity = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_PlayerShowAmity );
	m_pID_BUTTON_PlayerHideALL = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_PlayerHideALL );
	m_pID_BUTTON_PlayerShowAntagonize = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_PlayerShowAntagonize );
	m_pID_BUTTON_Card = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_Card );
	m_pID_TEXT_Card = (ControlText*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_TEXT_Card );
	m_pID_TEXT_Shop = (ControlText*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_TEXT_Shop );

	m_pID_CHECKBOX_HideChatList = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_CHECKBOX_HideChatList);
	m_pID_TEXT_Channel = (ControlText*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_TEXT_Channel );
	m_pID_BUTTON_Channel = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_Channel );

	m_pID_BUTTON_OpenQuestEntrust  = (ControlButton*)theUiManager.FindControl( ID_FRAME_MiniMap, ID_BUTTON_OpenQuestEntrust );

//     assert( m_pID_FRAME_MiniMap );
//     assert( m_pID_PICTURE_Map );
//     assert( m_pID_TEXT_Name );
//     assert( m_pID_BUTTON_MapSize );
//     assert( m_pID_BUTTON_Hide );
//     assert( m_pID_BUTTON_NPCList );
//     assert(m_pID_BUTTON_Help);
//     assert( m_pID_BUTTON_ProtectTime );
    assert( m_pID_PICTURE_Red );
    assert( m_pID_PICTURE_Yellow );
    assert( m_pID_PICTURE_Green );
    //     assert( m_pID_TEXT_PlaceTime );
    //     assert( m_pID_BUTTON_Direct );
//     assert( m_pID_BUTTON_Cancel );
//     assert( m_pID_BUTTON_AutoAttack);
//     assert( m_pID_BUTTON_Email );
//     assert( m_pID_PICTURE_Email );
//     assert( m_pID_TEXT_Email);
	assert( m_pID_BUTTON_MapSizeSmall );
	assert( m_pID_BUTTON_Achivement );
	assert( m_pID_BUTTON_DoubleExp );
//	assert( m_pID_BUTTON_SearchTeam );	
//	assert( m_pID_BUTTON_QuickEquip );
	assert( m_pID_BUTTON_Rank );
    assert( m_pID_BUTTON_ActivityDay );
    assert( m_pID_PICTURE_Effect );
	assert( m_pID_BUTTON_Mail );
	assert( m_pID_BUTTON_FuJin );
	assert( m_pID_TEXT_Activity );

	assert( m_pID_BUTTON_PlayerShowALL );
	assert( m_pID_BUTTON_PlayerShowAmity );
	assert( m_pID_BUTTON_PlayerHideALL );
	assert( m_pID_BUTTON_PlayerShowAntagonize );

	assert( m_pID_BUTTON_Card );
	assert( m_pID_TEXT_Card );
	assert( m_pID_TEXT_Shop );
	assert (m_pID_CHECKBOX_HideChatList);
	assert( m_pID_TEXT_Channel );
	assert( m_pID_BUTTON_Channel );

	assert(m_pID_BUTTON_OpenQuestEntrust);

	m_pID_FRAME_MiniMap->SetRenderNeedRedraw( s_CUI_ID_FRAME_MiniMapOnFrameRenderNeedRedraw, true );
    m_pID_FRAME_MiniMap->SetRenderFun( s_CUI_ID_FRAME_MiniMapOnFrameRenderPostUI, false );
    CreateTodayActEffect();

	SetTipAndHotKey(m_pID_BUTTON_NPCList, AN_Configure_ShortcutKey::AN_SCKC_openAreaMap);
	SetTipAndHotKey(m_pID_BUTTON_ActivityDay, AN_Configure_ShortcutKey::AN_SCKC_openEvent);
	SetTipAndHotKey(m_pID_BUTTON_Shop, AN_Configure_ShortcutKey::AN_SCKC_uiShopCenter);
	SetTipAndHotKey(m_pID_BUTTON_Trade, AN_Configure_ShortcutKey::AN_SCK_GoldTrade);

// 	SetTipAndHotKey(m_pID_BUTTON_Rank, theXmlString.GetString(eText_UITip_HotKey_RankList), AN_Configure_ShortcutKey::AN_SCKC_uiRank);
// 	SetTipAndHotKey(m_pID_BUTTON_Achivement, theXmlString.GetString(eText_UITip_HotKey_Achievement), AN_Configure_ShortcutKey::AN_SCKC_uiAchivement);
// 	SetTipAndHotKey(m_pID_BUTTON_AutoAttack, theXmlString.GetString(eText_UITip_HotKey_FightAssist),AN_Configure_ShortcutKey::AN_SCKC_uiAutoAttack);

	if(m_pID_BUTTON_Mail)
	{
		m_pID_BUTTON_Mail->setTip(m_pID_BUTTON_Mail->GetRealCaption());
		m_pID_BUTTON_Mail->SetShowTip();
	}
	if(m_pID_BUTTON_FuJin)
	{
		m_pID_BUTTON_FuJin->setTip(m_pID_BUTTON_FuJin->GetRealCaption());
		m_pID_BUTTON_FuJin->SetShowTip();
	}
	if(m_pID_BUTTON_MapSizeSmall)
	{
		m_pID_BUTTON_MapSizeSmall->setTip(m_pID_BUTTON_MapSizeSmall->GetRealCaption());
		m_pID_BUTTON_MapSizeSmall->SetShowTip();
	}
	if(m_pID_BUTTON_MapSize)
	{
		m_pID_BUTTON_MapSize->setTip(m_pID_BUTTON_MapSize->GetRealCaption());
		m_pID_BUTTON_MapSize->SetShowTip();
	}
	if(m_pID_BUTTON_Direct)
	{
		m_pID_BUTTON_Direct->setTip(m_pID_BUTTON_Direct->GetRealCaption());
		m_pID_BUTTON_Direct->SetShowTip();
	}
	if(m_pID_BUTTON_SystemSetting)
	{
		m_pID_BUTTON_SystemSetting->setTip(m_pID_BUTTON_SystemSetting->GetRealCaption());
		m_pID_BUTTON_SystemSetting->SetShowTip();
	}
	if(m_pID_BUTTON_Help)
	{
		m_pID_BUTTON_Help->setTip(m_pID_BUTTON_Help->GetRealCaption());
		m_pID_BUTTON_Help->SetShowTip();
	}

	if(m_pID_BUTTON_AutoAttack)
	{
		m_pID_BUTTON_AutoAttack->setTip(m_pID_BUTTON_AutoAttack->GetRealCaption());
		m_pID_BUTTON_AutoAttack->SetShowTip();
	}
	if(m_pID_BUTTON_Rank)
	{
		m_pID_BUTTON_Rank->setTip(m_pID_BUTTON_Rank->GetRealCaption());
		m_pID_BUTTON_Rank->SetShowTip();
	}
	if(m_pID_BUTTON_Activity)
	{
		m_pID_BUTTON_Activity->setTip(m_pID_BUTTON_Activity->GetRealCaption());
		m_pID_BUTTON_Activity->SetShowTip();
	}
	if(m_pID_BUTTON_Shop)
	{
		m_pID_BUTTON_Shop->setTip(m_pID_BUTTON_Shop->GetRealCaption());
		m_pID_BUTTON_Shop->SetShowTip();
	}
	if (m_pID_BUTTON_Card)
	{
		m_pID_BUTTON_Card->setTip(m_pID_BUTTON_Card->GetRealCaption());
		m_pID_BUTTON_Card->SetShowTip();
	}
	if (m_pID_CHECKBOX_HideChatList)
	{
		m_pID_CHECKBOX_HideChatList->SetShowTip();
	}

	m_pPlayerShowBtn[ PSM_ShowAll ] = m_pID_BUTTON_PlayerShowALL;
	m_pID_BUTTON_PlayerShowALL->setTip( theXmlString.GetString( eText_ShowAllPlayer ) );
	m_pID_BUTTON_PlayerShowALL->SetVisable(true);

	m_pPlayerShowBtn[ PSM_HideAll ] = m_pID_BUTTON_PlayerHideALL;
	m_pID_BUTTON_PlayerHideALL->setTip( theXmlString.GetString( eText_HideAllPlayer ) );
	m_pID_BUTTON_PlayerHideALL->SetVisable(false);

	m_pPlayerShowBtn[ PSM_ShowAmity ] = m_pID_BUTTON_PlayerShowAmity;
	m_pID_BUTTON_PlayerShowAmity->setTip( theXmlString.GetString( eText_ShowAmityPlayer ) );
	m_pID_BUTTON_PlayerShowAmity->SetVisable(false);

	m_pPlayerShowBtn[PSM_ShowAntagonize] = m_pID_BUTTON_PlayerShowAntagonize;
	m_pID_BUTTON_PlayerShowAntagonize->setTip( theXmlString.GetString( eText_ShowAntagonizePlayer ) );
	m_pID_BUTTON_PlayerShowAntagonize->SetVisable(false);


	m_pCurPlayerShowBtn = m_pID_BUTTON_PlayerShowALL;
	m_bPlayerShowModeOpen = false;
	m_nPlayerRenderFlag = CPlayerMgr::EPlayerRenderFlag::EPRF_ALL;

	RECT rcList;

	//记录初始位置。
	m_pPlayerShowBtn[ PSM_ShowAll ]->GetRealRect(&rcList);
	ShowPlayerBtnPosX = rcList.left;
	ShowPlayerBtnPosY = rcList.top;

	//第一次排序
	m_bCompositor = true;
	compositor();
	m_bCompositor = false;

    _SetVisable( false );

    return true;
    unguard;
}

// 卸载UI
bool CUI_ID_FRAME_MiniMap::_UnLoadUI()
{
    guardfunc;
    m_GroupAllUI.Clear();
    m_pID_FRAME_MiniMap = NULL;

    if( m_pTodayActEff )
    {
        delete m_pTodayActEff;
        m_pTodayActEff = NULL;
    }

	ResetMembers();
    return theUiManager.RemoveFrame( "data\\ui\\MiniMap.meui" );
    unguard;
}
// 是否可视
bool CUI_ID_FRAME_MiniMap::_IsVisable()
{
    guardfunc;
    if( !m_pID_FRAME_MiniMap )
        return false;
    return m_pID_FRAME_MiniMap->IsVisable();
    unguard;
}
// 设置是否可视
void CUI_ID_FRAME_MiniMap::_SetVisable( const bool bVisable )
{
    guardfunc;
    if( !m_pID_FRAME_MiniMap )
        return;
    m_pID_FRAME_MiniMap->SetVisable( bVisable );
    if( bVisable )
        UpdatePing();
    unguard;
}

bool CUI_ID_FRAME_MiniMap::ID_BUTTON_DirectOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MiniMap )
		return false;

	if (m_nMap == -1)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_MiniMapFindPath, theXmlString.GetString(eText_No_PF_Target) );
        return false;
    }
    CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(m_nMap);
    if (NULL == pTile)
    {
        return false;
    }
    if ((m_lastPFX < 0.f )|| (m_lastPFX > pTile->GetWidth() - 1) || (m_lastPFY < 0.f) || (m_lastPFY > pTile->GetDepth() - 1))
    {
        return false;
    }
    CWorldTile* pCurrTile = CURRENTTILE;
    assert(pCurrTile);
	if (pCurrTile != pTile)
	{//取本国地图
		m_nMap = gCfg.GetMyCountryMapId(m_nMap,theHeroGame.GetPlayerMgr()->GetMe()->GetRealCountry());
		pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(m_nMap);
	}
    if (pCurrTile == pTile)
    {
        theHeroGame.GetPlayerMgr()->MoveRoleTo(m_lastPFX,m_lastPFY,true,false);
    }
    else if( theHeroGame.GetPlayerMgr()->GetMe() )
    {//跨地图寻路
        float x,y;
        theHeroGame.GetPlayerMgr()->GetMe()->GetPos(&x,&y,NULL);
        bool bRet = CrossMapPF::Instance()->CrossMapFindPath(pCurrTile->GetMapId(),x,y,pTile->GetMapId(),m_lastPFX,m_lastPFY);
        if (!bRet)
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_MiniMapFindPath, theXmlString.GetString(eText_CannotCrossMapPathFindAddress) );
        }
    }
    SetAutoRuning(true);
    return true;
}

bool CUI_ID_FRAME_MiniMap::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MiniMap )
		return false;

   CPathDirection::Instance()->Reset();
    CrossMapPF::Instance()->Reset();
    CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();

    if (pMe)
    {
        pMe->SetMoving(FALSE);
    }

    return true;

}


// void CUI_ID_FRAME_MiniMap::startHelp()
// {
//     s_CUI_ID_FRAME_ExitGame.ID_BUTTON_helpOnButtonClick(NULL);
// }

void CUI_ID_FRAME_MiniMap::SetButtonToCustom()
{
	m_bLowSetting = true;
	if (m_pID_BUTTON_SystemSetting)
	{
		m_pID_BUTTON_SystemSetting->setTip( theXmlString.GetString( eText_DefaultSetting ) );
	}
}

void CUI_ID_FRAME_MiniMap::ShowMapName(DWORD col)
{
	if (SwGlobal::GetWorld() && SwGlobal::GetWorld()->GetWorldBuffer()
		&& SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile())
	{
		std::string strFullMapName;
		CWorldTile* pCurrTile = CURRENTTILE;
		if (pCurrTile)
		{
			//if (pCurrTile->GetCountry() != 0 && pCurrTile->GetMapType() == 0)
			//{
			//	std::string strCountryName = CountryFunction::GetCountryNameById(pCurrTile->GetCountry());
			//	strFullMapName = strCountryName + ":" + m_strAreaName;
			//}
			//else
			//{
			//	strFullMapName = pCurrTile->GetTileName();
			//}

			/*std::string str = s_CUI_ID_FRAME_SelectChannel.GetChannelName();
			if ( str.length() > 0 )
			{
				strFullMapName += "（";
				strFullMapName += str;
				strFullMapName += "）";
			}*/
            strFullMapName = pCurrTile->GetTileName();
		}
		if (strFullMapName != m_pID_TEXT_Name->GetText())
		{
			m_pID_TEXT_Name->SetText(strFullMapName.c_str(),col);
		}
	}

	ShowChannelName();
}


//
void CUI_ID_FRAME_MiniMap::Refeash()
{
    guardfunc;
	DWORD time_cost = HQ_TimeGetTime();

    std::string strZoneName;
    std::string strBackMusic;
	RECT rect = {0, 0, 0, 0};
    guard(test1);
    CWorldTile* tile = CURRENTTILE;
    if (!tile)
    {
        return;
    }
    DWORD col = Color_Config.getColor(CC_Center_MapInfo);
    const char* strColor = tile->GetMapNameColor();
    if (strColor && strColor[0] != '\0')
    {
        sscanf(strColor,"%x",&col);
    }
	CWorldChunk* chunk = NULL;
	if( theApp->GetPlayerMgr()->GetMe() )
	{
		float fx,fy;
		theApp->GetPlayerMgr()->GetMe()->GetPos(&fx,&fy,NULL);
		chunk = tile->GetChunkFromPos(fx,fy);
	}
#if _DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\n s_CUI_ID_FRAME_MiniMap 11111111111111111 %d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif
    const char* pAliasName = tile->GetTileName();
    if( pAliasName )
    {
        m_strAreaName = pAliasName;
    }
    strBackMusic.clear();
    if (chunk&& chunk->GetZoneId()!= RES_INVALID_ID)
    {
        CResMgr* resMgr = tile->GetCResMgr();
        if( resMgr->GetZoneRes(chunk->GetZoneId()) )
        {
            const char* pZoneName = resMgr->GetZoneRes(chunk->GetZoneId())->GetName();
            if ( pZoneName )
            {
                strZoneName = pZoneName;
            }
            const char* pMusicName = resMgr->GetZoneRes(chunk->GetZoneId())->GetMuiscPath();
            if ( pMusicName )
                strBackMusic = pMusicName;

			const RECT* pRect = resMgr->GetZoneRes(chunk->GetZoneId())->GetFontRect();
			if (pRect)
			{
				rect.left = pRect->left;
				rect.top = pRect->top;
				rect.right = pRect->right;
				rect.bottom = pRect->bottom;
			}
        }
    }
#if _DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\n s_CUI_ID_FRAME_MiniMap 222222222222222222 %d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif
    if (strLastZoneName != strZoneName || (strLastTileName != m_strAreaName))
    {
        strLastZoneName = strZoneName;			
        if( !(strcmp( s_CUI_ID_FRAME_MessageBox.GetTextCaption(), theXmlString.GetString( eText_NowLoadingGameData ) ) == 0 &&
            s_CUI_ID_FRAME_MessageBox.IsVisable()) )
        {
			if (rect.left != 0 && rect.right != 0 && rect.top != 0 && rect.bottom != 0)
			{
				CScreenInfoManager::Instance()->ShowRegionName(&rect);
			}
			else
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_Name, strZoneName.c_str() );
			}
        }
#if _DEBUG
		time_cost = HQ_TimeGetTime() - time_cost;
		if(time_cost > 20)
		{
			char cOutputString[2048];
			MeSprintf_s( cOutputString, 2048, "\n s_CUI_ID_FRAME_MiniMap 3333SetBigTileSetBigTileSetBigTile3333333333333333333 %d\n", time_cost );
			OutputDebugStr(cOutputString);
		}
		time_cost = HQ_TimeGetTime();
#endif

        // Music
        if ( !strBackMusic.empty() )
        {
            string strFullPath(CWorld::GetAppDataCharDir());
            strFullPath += '\\';
            strFullPath += strBackMusic.c_str();
            GMusic.PlayMusic( strFullPath.c_str(), TRUE, TRUE );
        }
        else
        {
            GMusic.StopMusic( );
        }
    }
#if _DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\n s_CUI_ID_FRAME_MiniMap 33333333333333333333333 %d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif
    if ( strLastTileName != m_strAreaName )
    {
        strLastTileName = m_strAreaName;
        ShowMapName(col);
    }
    unguard;

    guard(Refeash0);
    CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
    if( pMe )
    {
        char szPos[128] = {0};
        sprintf( szPos, "%d  %d", (INT)(pMe->GetPos().x), 
            (INT)(pMe->GetPos().y)
            );
        if( m_pID_TEXT_PlayerPos )
            *m_pID_TEXT_PlayerPos  = szPos;
    }
#if _DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\n s_CUI_ID_FRAME_MiniMap 44444444444444444444444 %d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

    unguard;
    unguard;
}

void CUI_ID_FRAME_MiniMap::update()
{
    guardfunc;

    unguard;
}
void CUI_ID_FRAME_MiniMap::setBtnRay()
{
    guardfunc;
    if( m_tmBtn_raytime > 0 )
    {
        clock_t tmNow = clock();
        if( tmNow - m_tmBtn_raytime > g_TimeCooling_Config.getTimeCooling(TCC_MINIMAP_EVENTBTN_RAY) )
        {
            if( m_bIsNormal_state )
            {
                m_bIsPress_state = !m_bIsPress_state;
                m_bIsNormal_state = !m_bIsNormal_state;
            }
            else
            {
                m_bIsPress_state = !m_bIsPress_state;
                m_bIsNormal_state = !m_bIsNormal_state;
            }

            m_tmBtn_raytime = tmNow;
        }
    }
    unguard;
}
void CUI_ID_FRAME_MiniMap::SetServerName(const char* name)
{
    m_strServerName = name;
}

void CUI_ID_FRAME_MiniMap::SetAutoRuning( bool val )
{
    if( !m_pID_FRAME_MiniMap )
        return;

    m_bAutoRuning = val;
    if (m_bAutoRuning)
    {
        m_pID_BUTTON_Direct->SetEnable(false);
        m_pID_BUTTON_Cancel->SetEnable(true);
    }
    else
    {
        m_pID_BUTTON_Direct->SetEnable(true);
        m_pID_BUTTON_Cancel->SetEnable(false);
    }

}

void CUI_ID_FRAME_MiniMap::ShowGameStageTime(int stage, int maxStage, int duration)
{
    m_dwStartGSTime = HQ_TimeGetTime();
    m_GSDuration = duration * 1000;
    m_gameStage = stage;
    m_maxGameStage = maxStage;
}

void CUI_ID_FRAME_MiniMap::RefreshGameStageTime()
{
//     DWORD dwCurrTime = HQ_TimeGetTime();
//     if (dwCurrTime - m_dwStartGSTime > m_GSDuration)
//     {
//         m_gameStage = -1;
//        m_pID_TEXT_NextTime->SetVisable(false);
//         return;
//     }
//     int remainTime = (m_GSDuration + m_dwStartGSTime - dwCurrTime) / 1000;	// 秒
// 	char buf[256] = {0};
// 	char str_time[256] = {0};
//     int hour = remainTime / 3600;
//     int minute = (remainTime - hour * 3600) / 60;
//     int second = remainTime - hour * 3600 - minute * 60;
//     sprintf_s(str_time, sizeof(str_time)-1, "%02d:%02d:%02d", hour, minute, second);
//     sprintf_s(buf, sizeof(buf)-1, theXmlString.GetString(eClient_GameStageNextTime), m_gameStage, m_maxGameStage, str_time);
//     if (remainTime < GAME_STAGE_LIMIT_TIME)
//         m_pID_TEXT_NextTime->SetText(buf, D3DCOLOR_XRGB(255,0,0));
//     else
//         m_pID_TEXT_NextTime->SetText(buf);
//     m_pID_TEXT_NextTime->SetVisable(true);
}

//函数变量
float CUI_ID_FRAME_MiniMap::GetZoomScale()
{
    guardfunc;
    return m_fZoomScale;
    unguard;
}

void CUI_ID_FRAME_MiniMap::SetLastPFPoint( float mapX,float mapY,int nMapId )
{
    m_lastPFX = mapX;
    m_lastPFY = mapY;
    m_nMap    = nMapId;
    SetAutoRuning(true);
}

void CUI_ID_FRAME_MiniMap::ResetEctypeMapTimeRemain()
{
    m_dwEctypeMapEndTime = 0;
//     m_pID_TEXT_PlaceTime->SetText("");
//     m_pID_TEXT_PlaceTime->SetVisable(false);
}

void CUI_ID_FRAME_MiniMap::SetEctypeMapTimeRemain( DWORD time )
{
    m_dwEctypeMapEndTime = time*1000 + HQ_TimeGetTime();
   // m_pID_TEXT_PlaceTime->SetVisable(true);
    UpdateEctypeMapTimeRemain();
}

void CUI_ID_FRAME_MiniMap::UpdateEctypeMapTimeRemain()
{
//     if( m_dwEctypeMapEndTime > HQ_TimeGetTime() )
//     {
//         DWORD dwRemainTime = m_dwEctypeMapEndTime - HQ_TimeGetTime();
//         dwRemainTime /= 1000;
//         char str[MAX_PATH] = {0};
//         char timestr[MAX_PATH] = {0};
//         int second = 0, minute = 0, hour = 0;
//         second = dwRemainTime % 60;
//         minute = (int)(dwRemainTime / 60);
//         hour = minute / 60;
//         minute -= hour * 60;
//         sprintf(timestr, "%02d:%02d:%02d", hour, minute, second);
//         sprintf(str, theXmlString.GetString(eClient_EctypeMap_Countdown), timestr);
//        m_pID_TEXT_PlaceTime->SetText(str);
//     }
//     else if( m_pID_TEXT_PlaceTime->IsVisable() )
//     {
//         m_pID_TEXT_PlaceTime->SetVisable(false);
//     }
}

void CUI_ID_FRAME_MiniMap::SetPing( int ping )
{
    m_nPing = ping;
    if( IsVisable() )
        UpdatePing();
}

void CUI_ID_FRAME_MiniMap::UpdatePing()
{
    if( !IsVisable() )
        return;
    char szTextArea[64],szTextServer[64];
    memset(szTextArea,0,sizeof(szTextArea));
    memset(szTextServer,0,sizeof(szTextServer));
    sprintf(szTextArea,theXmlString.GetString(eText_Area), CUserData::Instance()->GetArea());
    sprintf(szTextServer,theXmlString.GetString(eText_ServerName),CUserData::Instance()->GetServer());


    if( m_nPing > gCfg.m_PingBadMin )
    {
        // 网络延时:差
        if( m_GroupAllUI.IsVisible() )
        {
            m_pID_PICTURE_Red->SetVisable(true);
            m_pID_PICTURE_Yellow->SetVisable(false);
            m_pID_PICTURE_Green->SetVisable(false);
        }
        char tips[MAX_PATH] = {0};
        char tips_color[MAX_PATH] = {0};
        sprintf(tips,theXmlString.GetString(eText_Ping),m_nPing);

		int nFps = theApp->GetAppFps();
		char fps[128] = {0};
		sprintf_s(fps, sizeof(fps) - 1, theXmlString.GetString(eText_Ping_FPS), nFps );

        sprintf(tips_color,"%s\n%s\n%s\n<#%8X>%s",szTextArea,szTextServer,fps,gCfg.m_PingBadColor,tips);
        m_pID_PICTURE_Red->setTip(tips_color,DT_LEFT);
        m_pID_PICTURE_Red->setShowTip();
    }
    else if( m_nPing > gCfg.m_PingNormalMin )
    {
        // 网络延时:中
        if( m_GroupAllUI.IsVisible() )
        {
            m_pID_PICTURE_Red->SetVisable(false);
            m_pID_PICTURE_Yellow->SetVisable(true);
            m_pID_PICTURE_Green->SetVisable(false);
        }
        char tips[MAX_PATH] = {0};
        char tips_color[MAX_PATH] = {0};
        sprintf(tips,theXmlString.GetString(eText_Ping),m_nPing);

		int nFps = theApp->GetAppFps();
		char fps[128] = {0};
		sprintf_s(fps, sizeof(fps) - 1, theXmlString.GetString(eText_Ping_FPS), nFps );

        sprintf(tips_color,"%s\n%s\n%s\n<#%8X>%s",szTextArea,szTextServer,fps,gCfg.m_PingNormalColor,tips);
        m_pID_PICTURE_Yellow->setTip(tips_color,DT_LEFT);
        m_pID_PICTURE_Yellow->setShowTip();
    }
    else
    {
        // 网络延时:好
        if( m_GroupAllUI.IsVisible() )
        {
            m_pID_PICTURE_Red->SetVisable(false);
            m_pID_PICTURE_Yellow->SetVisable(false);
            m_pID_PICTURE_Green->SetVisable(true);
        }
        char tips[MAX_PATH] = {0};
        char tips_color[MAX_PATH] = {0};
        sprintf(tips,theXmlString.GetString(eText_Ping),m_nPing);

		int nFps = theApp->GetAppFps();
		char fps[128] = {0};
		sprintf_s(fps, sizeof(fps) - 1, theXmlString.GetString(eText_Ping_FPS), nFps );

        sprintf(tips_color,"%s\n%s\n%s\n<#%8X>%s",szTextArea,szTextServer,fps,gCfg.m_PingGoodColor,tips);
        m_pID_PICTURE_Green->setTip(tips_color,DT_LEFT);
        m_pID_PICTURE_Green->setShowTip();
    }
}

bool CUI_ID_FRAME_MiniMap::ResetZoneInfo()
{
    strLastTileName = "";
    strLastZoneName = "";
    return true;
}

void CUI_ID_FRAME_MiniMap::UpdateProtectTimeCountDown()
{
    DWORD dwEndTime = CWealthProtect::Instance().GetProtectEndingTime();
    if( dwEndTime > HQ_TimeGetTime() )
    {
        DWORD dwRemainTime = dwEndTime - HQ_TimeGetTime();
        int iRemainSecond = (int)ceil(dwRemainTime*1.f / 1000);
        if( iRemainSecond > 0 )
        {
            int iRemainMinute = iRemainSecond / 60;
            iRemainSecond -= iRemainMinute * 60;
            char szText[MAX_PATH] = {0};
            char szTime[MAX_PATH] = {0};
            sprintf( szTime, "%02d:%02d", iRemainMinute, iRemainSecond );
            sprintf( szText, theXmlString.GetString(eText_ProtectTime), szTime );
            m_pID_BUTTON_ProtectTime->SetCaption(szText);
        }
        else
        {
            // 小于1秒，显示1秒
            char szText[MAX_PATH] = {0};
            char szTime[MAX_PATH] = {0};
            strcpy( szTime, "00:01" );
            sprintf( szText, theXmlString.GetString(eText_ProtectTime), szTime );
            m_pID_BUTTON_ProtectTime->SetCaption(szText);
        }
        m_pID_BUTTON_ProtectTime->SetVisable(true);
    }
    else
        m_pID_BUTTON_ProtectTime->SetVisable(false);
}

void CUI_ID_FRAME_MiniMap::ProcessMailNotify()
{
    if (m_bSplash)
    {
        m_dwStartSplash = HQ_TimeGetTime();
        SetTipInMail(true);
        m_bSplash = false;

		m_bLastMailVisable = true;
    }

	//有未读邮件就提示
	if (thePlayerRole.IsHaveNewMail())
		m_pID_TEXT_Email->SetVisable(true);
	else
		m_pID_TEXT_Email->SetVisable(false);

    if (!m_dwStartSplash)
        return;

	// 改为新邮件一直提示, 直到已读
    //DWORD dwElapse = HQ_TimeGetTime() - m_dwStartSplash;
    //if( dwElapse < 10000)
    //    m_bLastMailVisable = true;
    //else
    //{
    //   m_bLastMailVisable = false;
    //   m_dwStartSplash = 0;
    //}

    m_pID_TEXT_Email->SetVisable(m_bLastMailVisable);
    //m_pID_PICTURE_Email->SetVisable(m_bLastMailVisable);
}

void CUI_ID_FRAME_MiniMap::SetSplashTime(DWORD dwValue)
{
    m_bLastMailVisable = true;
    m_dwStartSplash = dwValue;
}

void CUI_ID_FRAME_MiniMap::SetTipInMail(bool bVisable)
{
	if( !m_pID_FRAME_MiniMap || !m_pID_BUTTON_Email )
		return;
    //m_pID_BUTTON_Email->SetVisable(bVisable);
}

ControlText* CUI_ID_FRAME_MiniMap::GetTEXT_PlayerPos()
{
	if( !m_pID_FRAME_MiniMap || !m_pID_TEXT_PlayerPos )
		return NULL;
	return m_pID_TEXT_PlayerPos;
}

ControlButton* CUI_ID_FRAME_MiniMap::GetBUTTON_Activity()
{
	if( !m_pID_FRAME_MiniMap || !m_pID_BUTTON_Activity )
		return NULL;
	return m_pID_BUTTON_Activity;
}

ControlButton* CUI_ID_FRAME_MiniMap::GetBUTTON_NPCList()
{
	if( !m_pID_FRAME_MiniMap || !m_pID_BUTTON_NPCList )
		return NULL;
	return m_pID_BUTTON_NPCList;
}

ControlButton* CUI_ID_FRAME_MiniMap::GetBUTTON_Track()
{
	//if( !m_pID_FRAME_MiniMap || !m_pID_BUTTON_Track )
		return NULL;
	//return m_pID_BUTTON_Track;
}

ControlButton* CUI_ID_FRAME_MiniMap::GetBUTTON_Shop()
{
	if( !m_pID_FRAME_MiniMap || !m_pID_BUTTON_Shop )
		return NULL;
	return m_pID_BUTTON_Shop;
}

ControlButton* CUI_ID_FRAME_MiniMap::GetBUTTON_AutoAttack()
{
	if( !m_pID_FRAME_MiniMap || !m_pID_BUTTON_AutoAttack )
		return NULL;
	return m_pID_BUTTON_AutoAttack;
}

ControlPicture* CUI_ID_FRAME_MiniMap::GetPICTURE_Map()
{
	if( !m_pID_FRAME_MiniMap || !m_pID_PICTURE_Map )
		return NULL;
	return m_pID_PICTURE_Map;
}	DWORD CUI_ID_FRAME_MiniMap::GetEctypeMapTimeRemain()	{		return m_dwEctypeMapEndTime;	}


bool CUI_ID_FRAME_MiniMap::MailProcessPress(const char bPressYesButton,void *pData)
{
    if( bPressYesButton )
    {
        CWorldTile* pCurrTile = CURRENTTILE;
        assert(pCurrTile);
        if(!pCurrTile)
            return true;

        const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord("飞鸽传书",pCurrTile->GetMapId());
        if(!pInfo)
        {
            int nMapID = s_CUI_ID_FRAME_MiniMap.GetMapID();
            if(nMapID == -1)  //刚上线的时候mapID为-1
               nMapID = pCurrTile->GetMapId();

            CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(nMapID);
            if (!pTile)        
                return true;

            //跨地图
            pInfo = NpcCoord::getInstance()->getNpcCoord("飞鸽传书",2);//2代表长安
            if(!pInfo)
            {
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_MiniMapFindPath, theXmlString.GetString(eText_CannotCrossMapPathFindAddress) );
                return true;
            }


            if( theHeroGame.GetPlayerMgr()->GetMe() )
            {
                float x,y;
                theHeroGame.GetPlayerMgr()->GetMe()->GetPos(&x,&y,NULL);
                bool bRet = CrossMapPF::Instance()->CrossMapFindPath(pCurrTile->GetMapId(),x,y,2,pInfo->_mapX,pInfo->_mapY);   //2代表长安
                if (!bRet)
                {
                    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_MiniMapFindPath, theXmlString.GetString(eText_CannotCrossMapPathFindAddress) );
                }
            }

            return true;
        }

        //本地图
        if (pInfo->_bPFPossible)
        {
            theHeroGame.GetPlayerMgr()->MoveRoleToNPC(pInfo);
            return true;
        }
    }
    return true;
}

void CUI_ID_FRAME_MiniMap::CreateTodayActEffect()
{
    if( m_pTodayActEff )
    {
        delete m_pTodayActEff;
        m_pTodayActEff = NULL;
    }

    m_pTodayActEff = new CPlaneEffect;
    std::string strPicPath = GetRootPath();
    strPicPath += "\\Data\\Ui\\Common\\ActivityDayEffect.dds";
    RECT rcFirst;
    rcFirst.left = 0;
    rcFirst.top = 0;
    rcFirst.right = 90;
    rcFirst.bottom = 100;
    if( m_pTodayActEff )
        m_pTodayActEff->Initialize( strPicPath, 6, 5, 30, rcFirst, 1000 );
}

void CUI_ID_FRAME_MiniMap::UpdateByLevelUp()
{
    // 升到10级播今日指引特效
    if( thePlayerRole.GetLevel() == EFFECT_PLAY_MIN_LEVEL && !s_CUI_ID_FRAME_ActivityDay.IsVisable() )
        m_bPlayTodayActEffect = true;
}

void CUI_ID_FRAME_MiniMap::DisplayTodayActEffect()
{
    if( !IsUILoad() || !IsVisable() )
        return;
    if( !m_pID_BUTTON_ActivityDay->IsVisable() || !m_pID_BUTTON_ActivityDay->IsEnable() )
        return;

    if( !m_bPlayTodayActEffect || !m_pTodayActEff )
        return;

    RECT rcDest;
    m_pID_PICTURE_Effect->GetRealRect( &rcDest );
    m_pTodayActEff->Display( rcDest );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Button //显示所有
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_PlayerShowALLOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MiniMap )
		return false;

	SetRenderPlayerFlag(CPlayerMgr::EPlayerRenderFlag::EPRF_ALL);
	SetPlayerModeOpenOrClose(pSender);

	return true;
}
// Button//显示友好的
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_PlayerShowAmityOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MiniMap )
		return false;

	SetRenderPlayerFlag( CPlayerMgr::EPlayerRenderFlag::EPRF_ME |
		CPlayerMgr::EPlayerRenderFlag::EPRF_TEAM |
		CPlayerMgr::EPlayerRenderFlag::EPRF_NPC | 
		CPlayerMgr::EPlayerRenderFlag::EPRF_MONSTER | 
		CPlayerMgr::EPlayerRenderFlag::EPRF_AMITY);

	SetPlayerModeOpenOrClose(pSender);

	return true;
}
// Button //显示主角自己
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_PlayerHideALLOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MiniMap )
		return false;

	SetRenderPlayerFlag( CPlayerMgr::EPlayerRenderFlag::EPRF_ME | 
		CPlayerMgr::EPlayerRenderFlag::EPRF_TEAM | 
		CPlayerMgr::EPlayerRenderFlag::EPRF_NPC |
		CPlayerMgr::EPlayerRenderFlag::EPRF_MONSTER);
	SetPlayerModeOpenOrClose(pSender);

	return true;
}
// Button //显示敌对的
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_PlayerShowAntagonizeOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MiniMap )
		return false;

	SetRenderPlayerFlag( CPlayerMgr::EPlayerRenderFlag::EPRF_ME | 
		CPlayerMgr::EPlayerRenderFlag::EPRF_TEAM | 
		CPlayerMgr::EPlayerRenderFlag::EPRF_NPC | 
		CPlayerMgr::EPlayerRenderFlag::EPRF_MONSTER | 
		CPlayerMgr::EPlayerRenderFlag::EPRF_ANTAGONIZE);

	SetPlayerModeOpenOrClose(pSender);

	return true;
}

void  CUI_ID_FRAME_MiniMap::SetPlayerModeOpenOrClose(ControlObject* pSender)
{
	if(!pSender) return;
	if(!m_pCurPlayerShowBtn) return;

	RECT rcList;
	m_pCurPlayerShowBtn->GetRealRect(&rcList);
	ShowPlayerBtnPosX = rcList.left;
	ShowPlayerBtnPosY = rcList.top;

	theHeroGame.GetPlayerMgr()->SetPlayerRenderFlag(GetRenderPlayerFlag());

	if (pSender == m_pCurPlayerShowBtn)
	{

		m_bCompositor = false;
		if(m_bPlayerShowModeOpen) //展开状态则关闭
		{ 
			for (int i = 0 ; i < PSM_Max ; i++)
			{
				m_pPlayerShowBtn[i]->SetVisable(false);
			}
		}
		else
		{
			for (int i = 0 ; i < PSM_Max ; i++)
			{
				m_pPlayerShowBtn[i]->SetVisable(true);
			}
		}
		m_bPlayerShowModeOpen = !m_bPlayerShowModeOpen;
		m_pCurPlayerShowBtn->SetVisable(true); //当前显示的按钮打开

	}else
	{
		m_bCompositor = true;
		m_bPlayerShowModeOpen = false;
		m_pCurPlayerShowBtn = (ControlButton*)pSender;
		for (int i = 0 ; i < PSM_Max ; i++)
		{
			m_pPlayerShowBtn[i]->SetVisable(false);
		}

		m_pCurPlayerShowBtn->SetVisable(true); //当前显示的按钮打开
		compositor();
		m_bCompositor = false;
	
	}
}

extern GAME_STATE	g_GameState;
void  CUI_ID_FRAME_MiniMap::compositor(bool IsChangeCurShowBtn) //排序
{
	if( !m_pID_FRAME_MiniMap )
		return;

	if(!m_bCompositor)
		return;

	m_pCurPlayerShowBtn->SetPos(ShowPlayerBtnPosX,ShowPlayerBtnPosY);
	this->m_pID_FRAME_MiniMap->SetRedraw();

	RECT rcList;
	m_pCurPlayerShowBtn->GetRealRect(&rcList);
	int _Height = rcList.bottom - rcList.top; 

	int Index = 1;
	int CurMode = 0;
	for (int i = 0 ; i < PSM_Max ; i++)
	{
		if(m_pPlayerShowBtn[i] == m_pCurPlayerShowBtn)
		{
			CurMode = i;
			continue;
		}

		m_pPlayerShowBtn[i]->SetPos(ShowPlayerBtnPosX,ShowPlayerBtnPosY + (_Height + PSMOFFSET)* Index );
		m_pPlayerShowBtn[i]->SetVisable(false);

		Index++;
	}

	if( g_GameState == G_MAIN )
	{
		if (m_pCurPlayerShowBtn == m_pPlayerShowBtn[PSM_HideAll])
		{
			GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerEffect,0 );
			GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerModel, 0 );
			GameSetting::Instance()->CommitChanges();
		}
		else
		{
			GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerEffect,1 );
			GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerModel, 1 );
			GameSetting::Instance()->CommitChanges();
		}
	}
		

	m_bCompositor = false;

	switch(CurMode)
	{
	case PSM_ShowAll:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PKMode_Change, theXmlString.GetString(eClient_PlayerHideMode1) );
		break;
	case PSM_HideAll:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PKMode_Change, theXmlString.GetString(eClient_PlayerHideMode2) );
		break;
	case PSM_ShowAmity:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PKMode_Change, theXmlString.GetString(eClient_PlayerHideMode3) );
		break;
	case PSM_ShowAntagonize:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PKMode_Change, theXmlString.GetString(eClient_PlayerHideMode4) );
		break;
	}
}

void CUI_ID_FRAME_MiniMap::SetCardTextShow(bool bshow)
{
	if (!m_pID_TEXT_Card)
		return;
	m_bLastCardVisable = bshow;

	if (m_GroupAllUI.IsVisible())
		m_pID_TEXT_Card->SetVisable(m_bLastCardVisable);
}

void CUI_ID_FRAME_MiniMap::SetShopTextShow(bool bshow)
{
	if (!m_pID_TEXT_Shop)
		return;
	m_bLastShopVisable = bshow;

	if (m_GroupAllUI.IsVisible())
		m_pID_TEXT_Shop->SetVisable(m_bLastShopVisable);
}

// Button
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_OpenQuestEntrustOnButtonClick ( ControlObject* pSender )
{
	s_CUI_ID_FRAME_QuestEntrust.SetVisable(!s_CUI_ID_FRAME_QuestEntrust.IsVisable());
	return true;
}
bool CUI_ID_FRAME_MiniMap::ID_BUTTON_ChannelOnButtonClick( ControlObject* pSender )
{
	std::string str = s_CUI_ID_FRAME_SelectChannel.GetChannelName();
	if ( str.length() <= 0 )
		return true;

	if ( thePlayerRole.IsDie() )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_eChangeChannelRet_Dead), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true );
		return true;
	}

	if( theHeroGame.GetPlayerMgr()->GetMe() )
	{
		if ( theHeroGame.GetPlayerMgr()->GetMe()->HasFightFlag(eFighting) )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_eChangeChannelRet_Fight), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true );
			return true;
		}
	}

	s_CUI_ID_FRAME_SelectChannel.SetChannelInfoOpen( true );
	s_CUI_ID_FRAME_SelectChannel.SetVisable( true );

	return true;
}

void CUI_ID_FRAME_MiniMap::ShowChannelName()
{
	if ( !m_pID_TEXT_Channel )
		return;

	m_pID_TEXT_Channel->SetText("");

	std::string str = s_CUI_ID_FRAME_SelectChannel.GetChannelName();

	m_pID_TEXT_Channel->SetText( str );
}