/********************************************************************
Created by UIEditor.exe
FileName: E:\3Guo_Client_11.23\Data\Ui\ManualLevelUp.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ManualLevelUp.h"
#include "PlayerRole.h"
#include "GlobalDef.h"
#include "XmlStringLanguage.h"
#include "Timestamp/Timestamp.h"
#include "ExpStage.h"
#include "Common.h"
#include "NetworkInput.h"
#include "MessageDefine.h"
#include "ScreenInfoManager.h"

CUI_ID_FRAME_ManualLevelUp s_CUI_ID_FRAME_ManualLevelUp;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ManualLevelUp, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ManualLevelUp, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ManualLevelUp, ID_BUTTON_LevelUpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ManualLevelUp, ID_BUTTON_ActiveOnButtonClick )
CUI_ID_FRAME_ManualLevelUp::CUI_ID_FRAME_ManualLevelUp()
{
	// Member
	m_pID_FRAME_ManualLevelUp = NULL;
	m_pID_BUTTON_LevelUp = NULL;
	m_pID_BUTTON_Active = NULL;
	m_pID_TEXT_CurrExp = NULL;
	m_pID_TEXT_LevelUpExp = NULL;
	m_pID_TEXT_WholeExp = NULL;
	m_pID_TEXT_LimitInfo = NULL;

	memset(&sllinfo,0,sizeof(sllinfo));
	isInit = false;
	ulCanTakeExp = 0;
	Max_level = 0;
}
// Frame
bool CUI_ID_FRAME_ManualLevelUp::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_ManualLevelUp::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_ManualLevelUp::ID_BUTTON_LevelUpOnButtonClick( ControlObject* pSender )
{
	int64 nCurExp = thePlayerRole.GetExpNotUsed();
	int64 nNeedExp = theExpStage.GetExpDistance( thePlayerRole.GetLevel() );
	if( nCurExp < nNeedExp )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_LevelUp_Belongs, theXmlString.GetString( eText_LevelUp_ExpNotEnough ) );
		return true;
	}

	MsgAckLevelUp msg;
	GettheNetworkInput().SendMsg( &msg );
	return true;
}
// Button
bool CUI_ID_FRAME_ManualLevelUp::ID_BUTTON_ActiveOnButtonClick( ControlObject* pSender )
{
	MsgAckActiveLimit msg;
	GettheNetworkInput().SendMsg( &msg );
	return true;
}

// 装载UI
bool CUI_ID_FRAME_ManualLevelUp::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ManualLevelUp.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ManualLevelUp.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ManualLevelUp::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ManualLevelUp, s_CUI_ID_FRAME_ManualLevelUpOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ManualLevelUp, s_CUI_ID_FRAME_ManualLevelUpOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ManualLevelUp, ID_BUTTON_LevelUp, s_CUI_ID_FRAME_ManualLevelUpID_BUTTON_LevelUpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ManualLevelUp, ID_BUTTON_Active, s_CUI_ID_FRAME_ManualLevelUpID_BUTTON_ActiveOnButtonClick );

	m_pID_FRAME_ManualLevelUp = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ManualLevelUp );
	m_pID_BUTTON_LevelUp = (ControlButton*)theUiManager.FindControl( ID_FRAME_ManualLevelUp, ID_BUTTON_LevelUp );
	m_pID_BUTTON_Active = (ControlButton*)theUiManager.FindControl( ID_FRAME_ManualLevelUp, ID_BUTTON_Active );
	m_pID_TEXT_CurrExp = (ControlText*)theUiManager.FindControl( ID_FRAME_ManualLevelUp, ID_TEXT_CurrExp );
	m_pID_TEXT_LevelUpExp = (ControlText*)theUiManager.FindControl( ID_FRAME_ManualLevelUp, ID_TEXT_LevelUpExp );
	m_pID_TEXT_WholeExp = (ControlText*)theUiManager.FindControl( ID_FRAME_ManualLevelUp, ID_TEXT_WholeExp );
	m_pID_TEXT_LimitInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_ManualLevelUp, ID_TEXT_LimitInfo );
	assert( m_pID_FRAME_ManualLevelUp );
	assert( m_pID_BUTTON_LevelUp );
	assert( m_pID_BUTTON_Active );
	assert( m_pID_TEXT_CurrExp );
	assert( m_pID_TEXT_LevelUpExp );
	assert( m_pID_TEXT_WholeExp );
	assert( m_pID_TEXT_LimitInfo );

	_SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ManualLevelUp::_UnLoadUI()
{
	m_pID_FRAME_ManualLevelUp = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\ManualLevelUp.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_ManualLevelUp::_IsVisable()
{
	return m_pID_FRAME_ManualLevelUp->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ManualLevelUp::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_ManualLevelUp->SetVisable( bVisable );
	if (bVisable)
	{
		s_CUI_ID_FRAME_ManualLevelUp.InitExpInfo();
		Refresh();
	}	
}

void CUI_ID_FRAME_ManualLevelUp::InitializeAtEnterWorld()
{
	if( !m_pID_FRAME_ManualLevelUp )
		return;

	_SetVisable( false );
}

void CUI_ID_FRAME_ManualLevelUp::InitLevelLimitData(SLevelLimitInfo* pLLInfo,short max_lv)
{
	//if (!pLLInfo)
	//{
	//	return;
	//}

	Max_level = max_lv;
	//memcpy(&sllinfo,pLLInfo,sizeof(sllinfo));
	isInit = true;
	Refresh();
}

void CUI_ID_FRAME_ManualLevelUp::InitExpInfo()
{
	ulCanTakeExp = 0;
	int curr_lv = thePlayerRole.GetLevel();
	if (curr_lv >= Max_level)
	{
		curr_lv = Max_level;
	}
	int nNewLevel = curr_lv + save_max_level_exp;
	//if ( nNewLevel >= Max_level )
	//{
	//	nNewLevel = Max_level;
	//}
	//升级所需未使用经验总和
	for ( int i = curr_lv; i < nNewLevel; ++i )
	{
		ulCanTakeExp += theExpStage.GetExpDistance(i);
	}
	//// 经验条   
	//int64 nCurExp = thePlayerRole.GetExpNotUsed();
	//int64 nNeedExp = theExpStage.GetExpDistance( thePlayerRole.GetLevel() );
	//if( nCurExp < 0 )
	//	nCurExp = 0;
	//__int64 nExpPercent = nCurExp * 1000 / nNeedExp;
	//s_CUI_ID_FRAME_CharacterExp.SetExpValue( nExpPercent );
	//char szExp[64] = {0};
	//MeSprintf_s( szExp, sizeof( szExp ) / sizeof( char ) - 1, "%I64u / %I64u" , nCurExp, nNeedExp );
	//s_CUI_ID_FRAME_CharacterExp.SetTextExp( szExp );

	//// 装备界面经验显示
	//s_CUI_ID_FRAME_BaseProperty.Refresh();

	//m_pID_PROGRESS_Exp->SetValue(nExpPercent);
	//m_pID_TEXT_EXP->SetText(szExp);
}

void CUI_ID_FRAME_ManualLevelUp::Refresh()
{
	if (!_IsVisable())
	{
		return;
	}
	m_pID_TEXT_CurrExp->Clear();
	m_pID_TEXT_LevelUpExp->Clear();
	m_pID_TEXT_WholeExp->Clear();
	m_pID_TEXT_LimitInfo->Clear();
	m_pID_BUTTON_Active->SetVisable(false);
	m_pID_BUTTON_LevelUp->SetVisable(false);

	//
	if (!isInit)
	{
		MsgAckLimitInfo msg;
		GettheNetworkInput().SendMsg( &msg );

		m_pID_TEXT_LimitInfo->SetText(theXmlString.GetString(eText_WaitLimitInfo));
	}
	/*else
	{
		switch (sllinfo.state)
		{
		case eLimitState_noActive:
			{
				char szInfo[128] = {0};
				MeSprintf_s( szInfo, sizeof( szInfo ) / sizeof( char ) - 1, theXmlString.GetString(eText_NoActiveLimit), sllinfo.level);
				m_pID_TEXT_LimitInfo->SetText(szInfo);
			}
			break;
		case eLimitState_Active:
			{
				char szInfo[128] = {0};
				MeSprintf_s( szInfo, sizeof( szInfo ) / sizeof( char ) - 1, theXmlString.GetString(eText_ActiveLimit), 
					sllinfo.level,sllinfo.active_name,theTimestamp.GetTimeByTimestamp(sllinfo.done_time));
				m_pID_TEXT_LimitInfo->SetText(szInfo);
			}
			break;
		case eLimitState_Done:
			m_pID_TEXT_LimitInfo->SetText(theXmlString.GetString(eText_DoneLimit));
			break;
		default:
			m_pID_TEXT_LimitInfo->SetText(theXmlString.GetString(eText_WaitLimitInfo));
			break;
		}
	}*/
	//
	int curr_lv = thePlayerRole.GetLevel();
	unsigned long curr_exp = thePlayerRole.GetExpNotUsed();
	unsigned long lvup_exp = theExpStage.GetExpDistance(curr_lv);

	char InfoExp[64] ={0};
	_i64toa_s(curr_exp,InfoExp,64,10);
	m_pID_TEXT_CurrExp->SetText(InfoExp);

	ZeroMemory(InfoExp,64);
	_i64toa_s(lvup_exp,InfoExp,64,10);
	m_pID_TEXT_LevelUpExp->SetText(InfoExp);

	ZeroMemory(InfoExp,64);
	_i64toa_s(ulCanTakeExp,InfoExp,64,10);
	m_pID_TEXT_WholeExp->SetText(InfoExp);

	m_pID_BUTTON_LevelUp->SetVisable(true);
	m_pID_BUTTON_LevelUp->SetEnable(true);
	if (curr_exp >= lvup_exp)
	{
		/*if (curr_lv >= sllinfo.level&&sllinfo.state == eLimitState_noActive)
		{
			m_pID_BUTTON_Active->SetVisable(true);
		}*/

		if (curr_lv >= Max_level/*sllinfo.level*/)
		{
			// 当前等级小于服务器最大等级, 才显示升级按钮
			m_pID_BUTTON_LevelUp->SetEnable(false);
		}
	}
	else
	{
		// 手动升级界面经验不够时, 升级按钮变灰
		m_pID_BUTTON_LevelUp->SetEnable(false);
	}
}

void CUI_ID_FRAME_ManualLevelUp::DoneLimit()
{
	sllinfo.state = eLimitState_Done;
	Refresh();
}