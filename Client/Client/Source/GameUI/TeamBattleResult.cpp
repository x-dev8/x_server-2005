/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\chixin.ni\桌面\TeamBattleResult.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "TeamBattleResult.h"
#include "NetworkInput.h"
#include "XmlStringLanguage.h"
#include "ScreenInfoManager.h"
#include "../color_config.h"
#include "ShowScreenText.h"
#include "MessageBox.h"
#include "TeamBattleState.h"
#include "Player.h"
#include "GameMain.h"
#include "PlayerRole.h"
#include "TeamBattleState.h"
#include "MiniMapUI.h"
#include "XmlStringLanguage.h"
#include "ShowScreenText.h"
#include "TeamBattleRequest.h"
#include "Common.h"

CUI_ID_FRAME_TeamBattleResult s_CUI_ID_FRAME_TeamBattleResult;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TeamBattleResult, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TeamBattleResult, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_CHECKBOX_AllOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_CHECKBOX_SuiOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_BUTTON_helpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_BUTTON_PlayerNameOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_BUTTON_KillNumberOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_BUTTON_DamageOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_LIST_PlayerNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_LIST_KillNumberOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_LIST_DeathNumberOnListSelectChange )
//MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_LIST_DamageOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_BUTTON_DeathNumberOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_BUTTON_HealOnButtonClick )
//MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_LIST_HealOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_LIST_ResourceOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_BUTTON_ResourceOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_BUTTON_ExitOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_LIST_HonorOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_BUTTON_HonorOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_LIST_PlayerListOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TeamBattleResult, ID_LIST_PlayerIconOnListSelectChange )
CUI_ID_FRAME_TeamBattleResult::CUI_ID_FRAME_TeamBattleResult()
{
	// Member
	m_pID_FRAME_TeamBattleResult = NULL;
	m_pID_PICTURE_Di = NULL;
	m_pID_CHECKBOX_All = NULL;
	m_pID_CHECKBOX_Sui = NULL;
	m_pID_PICTURE_WallPaper = NULL;
	m_pID_PICTURE_TitleDi = NULL;
	m_pID_PICTURE_10248 = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_PICTURE_WallLeft2 = NULL;
	m_pID_PICTURE_WallRight2 = NULL;
	m_pID_PICTURE_WallLeft = NULL;
	m_pID_PICTURE_WallRight = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_help = NULL;
	m_pID_BUTTON_PlayerName = NULL;
	m_pID_BUTTON_KillNumber = NULL;
	m_pID_BUTTON_Damage = NULL;
	m_pID_LIST_PlayerName = NULL;
	m_pID_LIST_KillNumber = NULL;
	m_pID_LIST_DeathNumber = NULL;
	m_pID_TEXT_ArrowPlayerName = NULL;
	m_pID_TEXT_ArrowKillNumber = NULL;
// 	m_pID_TEXT_ArrowDamage = NULL;
// 	m_pID_LIST_Damage = NULL;
	m_pID_BUTTON_DeathNumber = NULL;
	m_pID_TEXT_ArrowDeathNumber = NULL;
// 	m_pID_BUTTON_Heal = NULL;
// 	m_pID_TEXT_ArrowHeal = NULL;
// 	m_pID_LIST_Heal = NULL;
	m_pID_LIST_Resource = NULL;
	m_pID_BUTTON_Resource = NULL;
	m_pID_TEXT_ArrowResource = NULL;
	m_pID_BUTTON_Exit = NULL;
	m_pID_LIST_Honor = NULL;
	m_pID_BUTTON_Honor = NULL;
	m_pID_TEXT_ArrowHonor = NULL;
	//m_pID_TEXT_CostTime = NULL;
	m_pID_LIST_PlayerList = NULL;
	m_pID_LIST_PlayerIcon = NULL;

}
// Frame
bool CUI_ID_FRAME_TeamBattleResult::OnFrameRun()
{
	if(thePlayerRole.IsTeamBattleInMap())
	{
		DWORD lefttime = s_CUI_ID_FRAME_MiniMap.GetEctypeMapTimeRemain();
		lefttime = lefttime - HQ_TimeGetTime();
		lefttime /= 1000;
		lefttime -= 120;

		if(m_worningTime2==0)
		{
			if(lefttime<1500)
			{
				++m_worningTime2;

				char str[260];
				for(int i=0;i<m_vecRecordInfoNoSort.size();++i)
				{
					if(m_vecRecordInfoNoSort[i].dwID == m_vecRecordInfo[0].dwID)
					{
						MeSprintf_s(str, sizeof(str)/sizeof(char) - 1, theXmlString.GetString(eText_TeamBattleNotify+i),m_vecRecordInfo[0].szName,m_vecRecordInfo[0].nIntegral);
						break;
					}
				}

				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Battle_SignUpSuccess, str );
			}
		}
		else if(m_worningTime2==1)
		{
			if(lefttime<1000)
			{
				++m_worningTime2;

				char str[260];
				for(int i=0;i<m_vecRecordInfoNoSort.size();++i)
				{
					if(m_vecRecordInfoNoSort[i].dwID == m_vecRecordInfo[0].dwID)
					{
						MeSprintf_s(str, sizeof(str)/sizeof(char) - 1, theXmlString.GetString(eText_TeamBattleNotify+i),m_vecRecordInfo[0].szName,m_vecRecordInfo[0].nIntegral);
						break;
					}
				}

				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Battle_SignUpSuccess, str );
			}
		}
		else if(m_worningTime2==2)
		{
			if(lefttime<600)
			{
				++m_worningTime2;

				char str[260];
				for(int i=0;i<m_vecRecordInfoNoSort.size();++i)
				{
					if(m_vecRecordInfoNoSort[i].dwID == m_vecRecordInfo[0].dwID)
					{
						MeSprintf_s(str, sizeof(str)/sizeof(char) - 1, theXmlString.GetString(eText_TeamBattleNotify+i),m_vecRecordInfo[0].szName,m_vecRecordInfo[0].nIntegral);
						break;
					}
				}

				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Battle_SignUpSuccess, str );
			}
		}

		if(lefttime<=60&&lefttime>0)
		{
			if(lefttime!=m_worningTime)
			{
				char str[256];
				MeSprintf_s(str,sizeof(str)/sizeof(char) - 1,theXmlString.GetString(eText_CampBattleLeftTime),lefttime,theXmlString.GetString(eTimeUnit_Second));
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Battle_SignUpSuccess, str );
			}

			m_worningTime = lefttime;
		}
	}
	else
	{
		SetVisable(false);
		m_worningTime = 0;
		m_worningTime2 = 0;
	}

	return true;
}
bool CUI_ID_FRAME_TeamBattleResult::OnFrameRender()
{
	RefreshTime();

	return true;
}
// CheckBox
void CUI_ID_FRAME_TeamBattleResult::ID_CHECKBOX_AllOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_TeamBattleResult)
		return;
	m_pID_CHECKBOX_All->SetCheck(true);
	m_pID_CHECKBOX_Sui->SetCheck(false);
	m_sel = 0;
	Refresh();
}
// CheckBox
void CUI_ID_FRAME_TeamBattleResult::ID_CHECKBOX_SuiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_TeamBattleResult)
		return;
	m_pID_CHECKBOX_All->SetCheck(false);
	m_pID_CHECKBOX_Sui->SetCheck(true);
	m_sel = 1;
	Refresh();

	MsgQueryTeamRecordReq msg;

	msg.ustMapID = s_CUI_ID_FRAME_TeamBattleRequest.m_SignInfo.ustMapID;

	GettheNetworkInput().SendMsg( &msg );
}
// Button
bool CUI_ID_FRAME_TeamBattleResult::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_TeamBattleResult)
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_TeamBattleResult::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_TeamBattleResult)
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_TeamBattleResult::ID_BUTTON_PlayerNameOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_TeamBattleResult)
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_TeamBattleResult::ID_BUTTON_KillNumberOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_TeamBattleResult)
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_TeamBattleResult::ID_BUTTON_DamageOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_TeamBattleResult)
		return false;
	return true;
}
// List
void CUI_ID_FRAME_TeamBattleResult::ID_LIST_PlayerNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_TeamBattleResult)
		return;
}
// List
void CUI_ID_FRAME_TeamBattleResult::ID_LIST_KillNumberOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_TeamBattleResult)
		return;
}
// List
void CUI_ID_FRAME_TeamBattleResult::ID_LIST_DeathNumberOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_TeamBattleResult)
		return;
}
// List
// void CUI_ID_FRAME_TeamBattleResult::ID_LIST_DamageOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
// {
// 	if(!m_pID_FRAME_TeamBattleResult)
// 		return;
// }
// Button
bool CUI_ID_FRAME_TeamBattleResult::ID_BUTTON_DeathNumberOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_TeamBattleResult)
		return false;
	return true;
}
// Button
// bool CUI_ID_FRAME_TeamBattleResult::ID_BUTTON_HealOnButtonClick( ControlObject* pSender )
// {
// 	if(!m_pID_FRAME_TeamBattleResult)
// 		return false;
// 	return true;
// }
// List
// void CUI_ID_FRAME_TeamBattleResult::ID_LIST_HealOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
// {
// 	if(!m_pID_FRAME_TeamBattleResult)
// 		return;
// }
// List
void CUI_ID_FRAME_TeamBattleResult::ID_LIST_ResourceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_TeamBattleResult)
		return;
}
// Button
bool CUI_ID_FRAME_TeamBattleResult::ID_BUTTON_ResourceOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_TeamBattleResult)
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_TeamBattleResult::ID_BUTTON_ExitOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_TeamBattleResult)
		return false;
	MsgLeaveBattleReq msg;
	msg.uchType = 2;
	GettheNetworkInput().SendMsg( &msg );

	SetVisable(false);
	s_CUI_ID_FRAME_TeamBattleState.SetVisable(false);
	s_CUI_ID_FRAME_TeamBattleResult.SetVisable(false);

	return true;
}
// List
void CUI_ID_FRAME_TeamBattleResult::ID_LIST_HonorOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_TeamBattleResult)
		return;
}
// Button
bool CUI_ID_FRAME_TeamBattleResult::ID_BUTTON_HonorOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_TeamBattleResult)
		return false;
	return true;
}
// List
void CUI_ID_FRAME_TeamBattleResult::ID_LIST_PlayerListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_TeamBattleResult)
		return;
}
void CUI_ID_FRAME_TeamBattleResult::ID_LIST_PlayerIconOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_TeamBattleResult)
		return;
}

// 装载UI
bool CUI_ID_FRAME_TeamBattleResult::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TeamBattleResult.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\TeamBattleResult.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_TeamBattleResult::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TeamBattleResult, s_CUI_ID_FRAME_TeamBattleResultOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TeamBattleResult, s_CUI_ID_FRAME_TeamBattleResultOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_TeamBattleResult, ID_CHECKBOX_All, s_CUI_ID_FRAME_TeamBattleResultID_CHECKBOX_AllOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_TeamBattleResult, ID_CHECKBOX_Sui, s_CUI_ID_FRAME_TeamBattleResultID_CHECKBOX_SuiOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_TeamBattleResult, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_TeamBattleResultID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TeamBattleResult, ID_BUTTON_help, s_CUI_ID_FRAME_TeamBattleResultID_BUTTON_helpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TeamBattleResult, ID_BUTTON_PlayerName, s_CUI_ID_FRAME_TeamBattleResultID_BUTTON_PlayerNameOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TeamBattleResult, ID_BUTTON_KillNumber, s_CUI_ID_FRAME_TeamBattleResultID_BUTTON_KillNumberOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_TeamBattleResult, ID_BUTTON_Damage, s_CUI_ID_FRAME_TeamBattleResultID_BUTTON_DamageOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_TeamBattleResult, ID_LIST_PlayerName, s_CUI_ID_FRAME_TeamBattleResultID_LIST_PlayerNameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_TeamBattleResult, ID_LIST_KillNumber, s_CUI_ID_FRAME_TeamBattleResultID_LIST_KillNumberOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_TeamBattleResult, ID_LIST_DeathNumber, s_CUI_ID_FRAME_TeamBattleResultID_LIST_DeathNumberOnListSelectChange );
// 	theUiManager.OnListSelectChange( ID_FRAME_TeamBattleResult, ID_LIST_Damage, s_CUI_ID_FRAME_TeamBattleResultID_LIST_DamageOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_TeamBattleResult, ID_BUTTON_DeathNumber, s_CUI_ID_FRAME_TeamBattleResultID_BUTTON_DeathNumberOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_TeamBattleResult, ID_BUTTON_Heal, s_CUI_ID_FRAME_TeamBattleResultID_BUTTON_HealOnButtonClick );
// 	theUiManager.OnListSelectChange( ID_FRAME_TeamBattleResult, ID_LIST_Heal, s_CUI_ID_FRAME_TeamBattleResultID_LIST_HealOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_TeamBattleResult, ID_LIST_Resource, s_CUI_ID_FRAME_TeamBattleResultID_LIST_ResourceOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_TeamBattleResult, ID_BUTTON_Resource, s_CUI_ID_FRAME_TeamBattleResultID_BUTTON_ResourceOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TeamBattleResult, ID_BUTTON_Exit, s_CUI_ID_FRAME_TeamBattleResultID_BUTTON_ExitOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_TeamBattleResult, ID_LIST_Honor, s_CUI_ID_FRAME_TeamBattleResultID_LIST_HonorOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_TeamBattleResult, ID_BUTTON_Honor, s_CUI_ID_FRAME_TeamBattleResultID_BUTTON_HonorOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_TeamBattleResult, ID_LIST_PlayerList, s_CUI_ID_FRAME_TeamBattleResultID_LIST_PlayerListOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_TeamBattleResult, ID_LIST_PlayerIcon, s_CUI_ID_FRAME_TeamBattleResultID_LIST_PlayerIconOnListSelectChange );

	m_pID_FRAME_TeamBattleResult = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TeamBattleResult );
	m_pID_PICTURE_Di = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_PICTURE_Di );
	m_pID_CHECKBOX_All = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_CHECKBOX_All );
	m_pID_CHECKBOX_Sui = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_CHECKBOX_Sui );
	m_pID_PICTURE_WallPaper = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_PICTURE_WallPaper );
	m_pID_PICTURE_TitleDi = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_PICTURE_TitleDi );
	m_pID_PICTURE_10248 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_PICTURE_10248 );
	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_TEXT_Title );
	m_pID_PICTURE_WallLeft2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_PICTURE_WallLeft2 );
	m_pID_PICTURE_WallRight2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_PICTURE_WallRight2 );
	m_pID_PICTURE_WallLeft = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_PICTURE_WallLeft );
	m_pID_PICTURE_WallRight = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_PICTURE_WallRight );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_BUTTON_CLOSE );
	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_BUTTON_help );
	m_pID_BUTTON_PlayerName = (ControlButton*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_BUTTON_PlayerName );
	m_pID_BUTTON_KillNumber = (ControlButton*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_BUTTON_KillNumber );
	m_pID_BUTTON_Damage = (ControlButton*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_BUTTON_Damage );
	m_pID_LIST_PlayerName = (ControlList*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_LIST_PlayerName );
	m_pID_LIST_KillNumber = (ControlList*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_LIST_KillNumber );
	m_pID_LIST_DeathNumber = (ControlList*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_LIST_DeathNumber );
	m_pID_TEXT_ArrowPlayerName = (ControlText*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_TEXT_ArrowPlayerName );
	m_pID_TEXT_ArrowKillNumber = (ControlText*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_TEXT_ArrowKillNumber );
// 	m_pID_TEXT_ArrowDamage = (ControlText*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_TEXT_ArrowDamage );
// 	m_pID_LIST_Damage = (ControlList*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_LIST_Damage );
	m_pID_BUTTON_DeathNumber = (ControlButton*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_BUTTON_DeathNumber );
	m_pID_TEXT_ArrowDeathNumber = (ControlText*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_TEXT_ArrowDeathNumber );
// 	m_pID_BUTTON_Heal = (ControlButton*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_BUTTON_Heal );
// 	m_pID_TEXT_ArrowHeal = (ControlText*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_TEXT_ArrowHeal );
// 	m_pID_LIST_Heal = (ControlList*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_LIST_Heal );
	m_pID_LIST_Resource = (ControlList*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_LIST_Resource );
	m_pID_BUTTON_Resource = (ControlButton*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_BUTTON_Resource );
	m_pID_TEXT_ArrowResource = (ControlText*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_TEXT_ArrowResource );
	m_pID_BUTTON_Exit = (ControlButton*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_BUTTON_Exit );
	m_pID_LIST_Honor = (ControlList*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_LIST_Honor );
	m_pID_BUTTON_Honor = (ControlButton*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_BUTTON_Honor );
	m_pID_TEXT_ArrowHonor = (ControlText*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_TEXT_ArrowHonor );
	//m_pID_TEXT_CostTime = (ControlText*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_TEXT_CostTime );
	m_pID_LIST_PlayerList = (ControlList*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_LIST_PlayerList );
	m_pID_LIST_PlayerIcon = (ControlList*)theUiManager.FindControl( ID_FRAME_TeamBattleResult, ID_LIST_PlayerIcon );
// 	assert( m_pID_FRAME_TeamBattleResult );
// 	assert( m_pID_PICTURE_Di );
// 	assert( m_pID_CHECKBOX_All );
// 	assert( m_pID_CHECKBOX_Sui );
// 	assert( m_pID_PICTURE_WallPaper );
// 	assert( m_pID_PICTURE_TitleDi );
// 	assert( m_pID_PICTURE_10248 );
// 	assert( m_pID_TEXT_Title );
// 	assert( m_pID_PICTURE_WallLeft2 );
// 	assert( m_pID_PICTURE_WallRight2 );
// 	assert( m_pID_PICTURE_WallLeft );
// 	assert( m_pID_PICTURE_WallRight );
// 	assert( m_pID_BUTTON_CLOSE );
// 	assert( m_pID_BUTTON_help );
// 	assert( m_pID_BUTTON_PlayerName );
// 	assert( m_pID_BUTTON_KillNumber );
// 	assert( m_pID_BUTTON_Damage );
// 	assert( m_pID_LIST_PlayerName );
// 	assert( m_pID_LIST_KillNumber );
// 	assert( m_pID_LIST_DeathNumber );
// 	assert( m_pID_TEXT_ArrowPlayerName );
// 	assert( m_pID_TEXT_ArrowKillNumber );
// 	assert( m_pID_TEXT_ArrowDamage );
// 	assert( m_pID_LIST_Damage );
// 	assert( m_pID_BUTTON_DeathNumber );
// 	assert( m_pID_TEXT_ArrowDeathNumber );
// 	assert( m_pID_BUTTON_Heal );
// 	assert( m_pID_TEXT_ArrowHeal );
// 	assert( m_pID_LIST_Heal );
// 	assert( m_pID_LIST_Resource );
// 	assert( m_pID_BUTTON_Resource );
// 	assert( m_pID_TEXT_ArrowResource );
// 	assert( m_pID_BUTTON_Exit );
// 	assert( m_pID_LIST_Honor );
// 	assert( m_pID_BUTTON_Honor );
// 	assert( m_pID_TEXT_ArrowHonor );
// 	assert( m_pID_TEXT_CostTime );
// 	assert( m_pID_LIST_PlayerList );
// 	assert( m_pID_LIST_PlayerIcon );
	
	SetVisable(false);

	m_pID_LIST_PlayerName->HaveSelBar(false);
	m_pID_LIST_KillNumber->HaveSelBar(false);
	m_pID_LIST_DeathNumber->HaveSelBar(false);
	m_pID_LIST_Resource->HaveSelBar(false);
	m_pID_LIST_Honor->HaveSelBar(false);

	m_pID_LIST_PlayerName->SetDrawFlags(DT_CENTER|DT_NOCLIP);
	m_pID_LIST_KillNumber->SetDrawFlags(DT_CENTER|DT_NOCLIP);
	m_pID_LIST_DeathNumber->SetDrawFlags(DT_CENTER|DT_NOCLIP);
	m_pID_LIST_Resource->SetDrawFlags(DT_CENTER|DT_NOCLIP);
	m_pID_LIST_Honor->SetDrawFlags(DT_CENTER|DT_NOCLIP);

	m_BeginTime = 0;
	m_EndTime = 0;
	m_end = false;

	m_worningTime = 0;
	m_worningTime2 = 0;

	m_sel = 0;
		 
	m_pID_CHECKBOX_All->SetCheck(true);
	m_pID_CHECKBOX_Sui->SetCheck(false);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_TeamBattleResult::_UnLoadUI()
{
	m_pID_FRAME_TeamBattleResult = NULL;
	m_pID_PICTURE_Di = NULL;
	m_pID_PICTURE_TitleDi = NULL;
	m_pID_PICTURE_10248 = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_PICTURE_WallLeft2 = NULL;
	m_pID_PICTURE_WallRight2 = NULL;
	m_pID_PICTURE_WallLeft = NULL;
	m_pID_PICTURE_WallRight = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_help = NULL;
	m_pID_BUTTON_PlayerName = NULL;
	m_pID_BUTTON_KillNumber = NULL;
	m_pID_BUTTON_Damage = NULL;
	m_pID_LIST_PlayerName = NULL;
	m_pID_LIST_KillNumber = NULL;
	m_pID_LIST_DeathNumber = NULL;
	m_pID_TEXT_ArrowPlayerName = NULL;
	m_pID_TEXT_ArrowKillNumber = NULL;
// 	m_pID_TEXT_ArrowDamage = NULL;
// 	m_pID_LIST_Damage = NULL;
	m_pID_BUTTON_DeathNumber = NULL;
	m_pID_TEXT_ArrowDeathNumber = NULL;
// 	m_pID_BUTTON_Heal = NULL;
// 	m_pID_TEXT_ArrowHeal = NULL;
// 	m_pID_LIST_Heal = NULL;
	m_pID_LIST_Resource = NULL;
	m_pID_BUTTON_Resource = NULL;
	m_pID_TEXT_ArrowResource = NULL;
	m_pID_BUTTON_Exit = NULL;
	m_pID_LIST_Honor = NULL;
	m_pID_BUTTON_Honor = NULL;
	m_pID_TEXT_ArrowHonor = NULL;
	//m_pID_TEXT_CostTime = NULL;
	m_pID_LIST_PlayerList = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\TeamBattleResult.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_TeamBattleResult::_IsVisable()
{
	if(!m_pID_FRAME_TeamBattleResult)
		return false;

	return m_pID_FRAME_TeamBattleResult->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_TeamBattleResult::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_TeamBattleResult)
		return;

	m_pID_FRAME_TeamBattleResult->SetVisable( bVisable );

	if(bVisable)
	{
		MsgQueryTeamRecordReq msg;

		msg.ustMapID = s_CUI_ID_FRAME_TeamBattleRequest.m_SignInfo.ustMapID;

		GettheNetworkInput().SendMsg( &msg );
	}
}

struct LessByResource 
{
	bool operator()(const MsgTellBattleRecord::RecordInfo& v1, const MsgTellBattleRecord::RecordInfo& v2)
	{
		if (v1.nIntegral > v2.nIntegral)
			return true;
		else if (v1.nIntegral == v2.nIntegral)
			return v1.nDeathCount < v2.nDeathCount;
		return false;
	}
};

void CUI_ID_FRAME_TeamBattleResult::OnRecord( MsgTellBattleRecord* pRecord )
{
	if( pRecord->uchStatus == MsgTellBattleRecord::Status_Fighting )
	{
	}
	else if( pRecord->uchStatus == MsgTellBattleRecord::Status_FightEnd )
	{
		SetVisable(true);

		m_EndTime = HQ_TimeGetTime();

		SetEnd( true );
	}

	m_vecRecordInfo.clear();
	m_vecRecordInfoNoSort.clear();

	for(int i=0;i<6;++i)
	{
		if( pRecord->xRecord[i].dwID==0 )
			break;

		m_vecRecordInfo.push_back(pRecord->xRecord[i]);
		m_vecRecordInfoNoSort.push_back(pRecord->xRecord[i]);
	}

	//排序
	std::sort(m_vecRecordInfo.begin(), m_vecRecordInfo.end(), LessByResource());

	for(int i=0;i<m_vecRecordInfo.size();++i)
	{
		if(m_vecRecordInfo[i].dwID == thePlayerRole.GetGroupId())
		{
			s_CUI_ID_FRAME_TeamBattleState.SetRank(i+1);
			break;
		}
	}
	
	Refresh();
}

void CUI_ID_FRAME_TeamBattleResult::OnTeamRecord( MsgQueryTeamRecordAck* pRecord )
{
	m_vecTeamRecordInfo.clear();

	for(int i=0;i<pRecord->nCount;++i)
	{
		m_vecTeamRecordInfo.push_back(pRecord->xRecord[i]);
	}

	Refresh();
}

void CUI_ID_FRAME_TeamBattleResult::Refresh()
{
	char buf[128];
	ControlList::S_List	stItem;

	m_pID_LIST_PlayerList->Clear();
	m_pID_LIST_PlayerName->Clear();
	m_pID_LIST_KillNumber->Clear();
	m_pID_LIST_DeathNumber->Clear();
	m_pID_LIST_Resource->Clear();
	m_pID_LIST_Honor->Clear();
	m_pID_LIST_PlayerIcon->Clear();

	if(m_sel == 0)
	{
		for(int i=0;i<m_vecRecordInfo.size();++i)
		{
			stItem.SetData("");
			m_pID_LIST_PlayerList->AddItem(&stItem,NULL, false);

			MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, theXmlString.GetString(eText_TeamBattleName),m_vecRecordInfo[i].szName);
			stItem.SetData( buf );
			m_pID_LIST_PlayerName->AddItem(&stItem,NULL, false);

			MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1,"%d",m_vecRecordInfo[i].nKillCount);
			stItem.SetData( buf );
			m_pID_LIST_KillNumber->AddItem(&stItem,NULL, false);

			MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1,"%d",m_vecRecordInfo[i].nDeathCount);
			stItem.SetData( buf );
			m_pID_LIST_DeathNumber->AddItem(&stItem,NULL, false);

			MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1,"%d",m_vecRecordInfo[i].nIntegral);
			stItem.SetData( buf );
			m_pID_LIST_Resource->AddItem(&stItem,NULL, false);

			for(int j=0;j<m_vecRecordInfoNoSort.size();++j)
			{
				if(m_vecRecordInfoNoSort[j].dwID == m_vecRecordInfo[i].dwID)
				{
					//根据J
					MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1,"{#202%d}",j);
					stItem.SetData(buf);
					m_pID_LIST_PlayerIcon->AddItem(&stItem,NULL, false);
				}
			}

			if(m_end)
			{
				MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1,"%d",i+1);
				stItem.SetData( buf );
				m_pID_LIST_Honor->AddItem(&stItem,NULL, false);
			}

		}
	}
	else
	{
		for(int i=0;i<m_vecTeamRecordInfo.size();++i)
		{
			stItem.SetData("");
			m_pID_LIST_PlayerList->AddItem(&stItem,NULL, false);

			MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, m_vecTeamRecordInfo[i].szName);
			stItem.SetData( buf );
			m_pID_LIST_PlayerName->AddItem(&stItem,NULL, false);

			MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1,"%d",m_vecTeamRecordInfo[i].nKillCount);
			stItem.SetData( buf );
			m_pID_LIST_KillNumber->AddItem(&stItem,NULL, false);

			MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1,"%d",m_vecTeamRecordInfo[i].nDeathCount);
			stItem.SetData( buf );
			m_pID_LIST_DeathNumber->AddItem(&stItem,NULL, false);

			MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1,"%d",m_vecTeamRecordInfo[i].nIntegral);
			stItem.SetData( buf );
			m_pID_LIST_Resource->AddItem(&stItem,NULL, false);

			if(m_end)
			{
				for(int j=0;j<m_vecRecordInfo.size();++j)
				{
					if( thePlayerRole.GetGroupId()==m_vecRecordInfo[j].dwID )
					{
						MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1,"%d",j+1);
						stItem.SetData( buf );
						m_pID_LIST_Honor->AddItem(&stItem,NULL, false);
					}
				}
			}
		}
	}

	RefreshTime();
}

void CUI_ID_FRAME_TeamBattleResult::SetBeginTime()
{
	m_BeginTime = HQ_TimeGetTime();
	m_end = false;
}

void CUI_ID_FRAME_TeamBattleResult::RefreshTime()
{
	int dwTime=0;
	if(m_EndTime==0)
	{
		dwTime = HQ_TimeGetTime() - m_BeginTime;
	}
	else
	{
		dwTime = m_EndTime - m_BeginTime;
	}

	char timestr[256];
	char timeshow[256];

    dwTime /= 1000;
    int second = 0, minute = 0, hour = 0;
    second = dwTime % 60;
    minute = (int)(dwTime / 60);
    hour = minute / 60;
    minute -= hour * 60;
    MeSprintf_s(timestr,sizeof(timestr)/sizeof(char) - 1, "%02d:%02d:%02d", hour, minute, second);
	MeSprintf_s(timeshow, sizeof(timeshow)/sizeof(char) - 1, theXmlString.GetString(eText_TeamBattleCostTime),timestr);
	//*m_pID_TEXT_CostTime = timeshow;
}
