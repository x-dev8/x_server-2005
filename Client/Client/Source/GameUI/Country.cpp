/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\国家界面\Country.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Country.h"
#include "UIMgr.h"
#include "CountryBroadcast.h"
#include "CountryQuestPost.h"
#include "CountryInput.h"
#include "CountryFunction.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "Gang.h"
#include "MiniMapUI.h"
#include "AllNpcList.h"
#include "CountryBattleKillNum.h"
#include "CampBattleMessage.h"
#include "ChangeCountryTip.h"
#include "Select.h"

using namespace CountryDefine;

#ifndef STR_MAXLEN
#define STR_MAXLEN	255
#endif

CUI_ID_FRAME_Country s_CUI_ID_FRAME_Country;

MAP_FRAME_RUN( s_CUI_ID_FRAME_Country, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Country, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Country, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Country, ID_BUTTON_PositionSet3OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Country, ID_BUTTON_PositionSet4OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Country, ID_BUTTON_PositionSet5OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Country, ID_BUTTON_PositionSet6OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Country, ID_BUTTON_PositionSet7OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Country, ID_BUTTON_CountryBroadcastNewOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Country, ID_BUTTON_CountryQusetPostOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Country, ID_BUTTON_CollectReasourceOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Country, ID_BUTTON_FreeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Country, ID_BUTTON_PrisonOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Country, ID_BUTTON_SilenceOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Country, ID_BUTTON_RenameOnButtonClick )

CUI_ID_FRAME_Country::CUI_ID_FRAME_Country()
{
	// Member
	m_pID_FRAME_Country = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_CountryTitle = NULL;
	m_pID_TEXT_PositionName1 = NULL;
	m_pID_TEXT_PositionName2 = NULL;
	m_pID_TEXT_PositionName3 = NULL;
	m_pID_TEXT_PositionName4 = NULL;
	m_pID_TEXT_PositionName5 = NULL;
	m_pID_TEXT_PositionName6 = NULL;
	m_pID_TEXT_PositionName7 = NULL;
	m_pID_BUTTON_PositionSet3 = NULL;
	m_pID_BUTTON_PositionSet4 = NULL;
	m_pID_BUTTON_PositionSet5 = NULL;
	m_pID_BUTTON_PositionSet6 = NULL;
	m_pID_BUTTON_PositionSet7 = NULL;
	m_pID_TEXT_CountryBroadcast = NULL;
	m_pID_TEXT_CountryQuset = NULL;
	m_pID_BUTTON_CountryBroadcastNew = NULL;
	m_pID_BUTTON_CountryQusetPost = NULL;
	m_pID_PICTURE_ResourceGold = NULL;
	m_pID_PICTURE_ResourceRock = NULL;
	m_pID_PICTURE_ResourceWood = NULL;
	m_pID_PICTURE_ResourceFood = NULL;
	m_pID_TEXT_ResourceGold = NULL;
	m_pID_TEXT_ResourceFood = NULL;
	m_pID_TEXT_ResourceRock = NULL;
	m_pID_TEXT_ResourceWood = NULL;
	m_pID_BUTTON_CollectReasource = NULL;
	m_pID_BUTTON_Free = NULL;
	m_pID_BUTTON_Prison = NULL;
	m_pID_BUTTON_Silence = NULL;
    m_pID_BUTTON_Rename = NULL;

	// 初始化
	ResetProperties();
}

// Frame
bool CUI_ID_FRAME_Country::OnFrameRun()
{
	guardfunc;
	if ( !m_pID_FRAME_Country )
	{
		assert( false && "ui error" );
		return false;
	}
	if( !IsVisable() )
		return false;

	return true;
	unguard;
}
bool CUI_ID_FRAME_Country::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_Country::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Country )
	{
		assert( false && "ui error" );
		return false;
	}
	SetVisable( false );
	return true;
}
// Button
bool CUI_ID_FRAME_Country::ID_BUTTON_PositionSet3OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Country )
	{
		assert( false && "ui error" );
		return false;
	}
    s_CUI_ID_FRAME_CountryInput.SetVisable( true );
	s_CUI_ID_FRAME_CountryInput.SetShowType( eShowType_AppointSiMa );
	return true;
}
// Button
bool CUI_ID_FRAME_Country::ID_BUTTON_PositionSet4OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Country )
	{
		assert( false && "ui error" );
		return false;
	}
    s_CUI_ID_FRAME_CountryInput.SetVisable( true );
	s_CUI_ID_FRAME_CountryInput.SetShowType( eShowType_AppointJiangJun );
	return true;
}
// Button
bool CUI_ID_FRAME_Country::ID_BUTTON_PositionSet5OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Country )
	{
		assert( false && "ui error" );
		return false;
	}
    s_CUI_ID_FRAME_CountryInput.SetVisable( true );
	s_CUI_ID_FRAME_CountryInput.SetShowType( eShowType_AppointChengXiang );
	return true;
}
// Button
bool CUI_ID_FRAME_Country::ID_BUTTON_PositionSet6OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Country )
	{
		assert( false && "ui error" );
		return false;
	}
    s_CUI_ID_FRAME_CountryInput.SetVisable( true );
	s_CUI_ID_FRAME_CountryInput.SetShowType( eShowType_AppointZuoJiangJun );
	return true;
}
// Button
bool CUI_ID_FRAME_Country::ID_BUTTON_PositionSet7OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Country )
	{
		assert( false && "ui error" );
		return false;
	}
    s_CUI_ID_FRAME_CountryInput.SetVisable( true );
	s_CUI_ID_FRAME_CountryInput.SetShowType( eShowType_AppointYouJiangJun );
	return true;
}
// Button
bool CUI_ID_FRAME_Country::ID_BUTTON_CountryBroadcastNewOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Country )
	{
		assert( false && "ui error" );
		return false;
	}
	s_CUI_ID_FRAME_CountryBroadcast.SetVisable( true );
	return true;
}
// Button
bool CUI_ID_FRAME_Country::ID_BUTTON_CountryQusetPostOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Country )
	{
		assert( false && "ui error" );
		return false;
	}
    s_CUI_ID_FRAME_CountryQuestPost.SetVisable( !s_CUI_ID_FRAME_CountryQuestPost.IsVisable() );
    s_CUI_ID_FRAME_CountryQuestPost.GetNewCountryRight( m_nCountryRight );
	return true;
}
// Button
bool CUI_ID_FRAME_Country::ID_BUTTON_CollectReasourceOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Country )
	{
		assert( false && "ui error" );
		return false;
	}
	// 给服务器发消息
	MsgCountryRequestRaiseReq msg;
	GettheNetworkInput().SendMsg( &msg );
	return true;
}
// Button
bool CUI_ID_FRAME_Country::ID_BUTTON_FreeOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Country )
	{
		assert( false && "ui error" );
		return false;
	}
    s_CUI_ID_FRAME_CountryInput.SetVisable( true );
	s_CUI_ID_FRAME_CountryInput.SetShowType( eShowType_SheMian );
	return true;
}
// Button
bool CUI_ID_FRAME_Country::ID_BUTTON_PrisonOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Country )
	{
		assert( false && "ui error" );
		return false;
	}
    s_CUI_ID_FRAME_CountryInput.SetVisable( true );
	s_CUI_ID_FRAME_CountryInput.SetShowType( eShowType_QiuJin );
	return true;
}
// Button
bool CUI_ID_FRAME_Country::ID_BUTTON_SilenceOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Country )
	{
		assert( false && "ui error" );
		return false;
	}
    s_CUI_ID_FRAME_CountryInput.SetVisable( true );
	s_CUI_ID_FRAME_CountryInput.SetShowType( eShowType_JinYan );
	return true;
}
// Button
bool CUI_ID_FRAME_Country::ID_BUTTON_RenameOnButtonClick( ControlObject* pSender )
{
    if ( !m_pID_FRAME_Country )
    {
        assert( false && "ui error" );
        return false;
    }
    s_CUI_ID_FRAME_CountryInput.SetVisable( true );
    s_CUI_ID_FRAME_CountryInput.SetShowType( eShowType_Rename );
    return true;
}

// 装载UI
bool CUI_ID_FRAME_Country::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Country.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Country.MEUI]失败")
		return false;
	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_Country::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_Country, s_CUI_ID_FRAME_CountryOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Country, s_CUI_ID_FRAME_CountryOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Country, ID_BUTTON_Cancel, s_CUI_ID_FRAME_CountryID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Country, ID_BUTTON_PositionSet3, s_CUI_ID_FRAME_CountryID_BUTTON_PositionSet3OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Country, ID_BUTTON_PositionSet4, s_CUI_ID_FRAME_CountryID_BUTTON_PositionSet4OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Country, ID_BUTTON_PositionSet5, s_CUI_ID_FRAME_CountryID_BUTTON_PositionSet5OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Country, ID_BUTTON_PositionSet6, s_CUI_ID_FRAME_CountryID_BUTTON_PositionSet6OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Country, ID_BUTTON_PositionSet7, s_CUI_ID_FRAME_CountryID_BUTTON_PositionSet7OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Country, ID_BUTTON_CountryBroadcastNew, s_CUI_ID_FRAME_CountryID_BUTTON_CountryBroadcastNewOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Country, ID_BUTTON_CountryQusetPost, s_CUI_ID_FRAME_CountryID_BUTTON_CountryQusetPostOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Country, ID_BUTTON_CollectReasource, s_CUI_ID_FRAME_CountryID_BUTTON_CollectReasourceOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Country, ID_BUTTON_Free, s_CUI_ID_FRAME_CountryID_BUTTON_FreeOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Country, ID_BUTTON_Prison, s_CUI_ID_FRAME_CountryID_BUTTON_PrisonOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Country, ID_BUTTON_Silence, s_CUI_ID_FRAME_CountryID_BUTTON_SilenceOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_Country, ID_BUTTON_Rename, s_CUI_ID_FRAME_CountryID_BUTTON_RenameOnButtonClick );

	m_pID_FRAME_Country = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Country );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_Country, ID_BUTTON_Cancel );
	m_pID_TEXT_CountryTitle = (ControlText*)theUiManager.FindControl( ID_FRAME_Country, ID_TEXT_CountryTitle );
	m_pID_TEXT_PositionName1 = (ControlText*)theUiManager.FindControl( ID_FRAME_Country, ID_TEXT_PositionName1 );
	m_pID_TEXT_PositionName2 = (ControlText*)theUiManager.FindControl( ID_FRAME_Country, ID_TEXT_PositionName2 );
	m_pID_TEXT_PositionName3 = (ControlText*)theUiManager.FindControl( ID_FRAME_Country, ID_TEXT_PositionName3 );
	m_pID_TEXT_PositionName4 = (ControlText*)theUiManager.FindControl( ID_FRAME_Country, ID_TEXT_PositionName4 );
	m_pID_TEXT_PositionName5 = (ControlText*)theUiManager.FindControl( ID_FRAME_Country, ID_TEXT_PositionName5 );
	m_pID_TEXT_PositionName6 = (ControlText*)theUiManager.FindControl( ID_FRAME_Country, ID_TEXT_PositionName6 );
	m_pID_TEXT_PositionName7 = (ControlText*)theUiManager.FindControl( ID_FRAME_Country, ID_TEXT_PositionName7 );
	m_pID_BUTTON_PositionSet3 = (ControlButton*)theUiManager.FindControl( ID_FRAME_Country, ID_BUTTON_PositionSet3 );
	m_pID_BUTTON_PositionSet4 = (ControlButton*)theUiManager.FindControl( ID_FRAME_Country, ID_BUTTON_PositionSet4 );
	m_pID_BUTTON_PositionSet5 = (ControlButton*)theUiManager.FindControl( ID_FRAME_Country, ID_BUTTON_PositionSet5 );
	m_pID_BUTTON_PositionSet6 = (ControlButton*)theUiManager.FindControl( ID_FRAME_Country, ID_BUTTON_PositionSet6 );
	m_pID_BUTTON_PositionSet7 = (ControlButton*)theUiManager.FindControl( ID_FRAME_Country, ID_BUTTON_PositionSet7 );
	m_pID_TEXT_CountryBroadcast = (ControlText*)theUiManager.FindControl( ID_FRAME_Country, ID_TEXT_CountryBroadcast );
	m_pID_TEXT_CountryQuset = (ControlText*)theUiManager.FindControl( ID_FRAME_Country, ID_TEXT_CountryQuset );
	m_pID_BUTTON_CountryBroadcastNew = (ControlButton*)theUiManager.FindControl( ID_FRAME_Country, ID_BUTTON_CountryBroadcastNew );
	m_pID_BUTTON_CountryQusetPost = (ControlButton*)theUiManager.FindControl( ID_FRAME_Country, ID_BUTTON_CountryQusetPost );
	m_pID_PICTURE_ResourceGold = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Country, ID_PICTURE_ResourceGold );
	m_pID_PICTURE_ResourceRock = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Country, ID_PICTURE_ResourceRock );
	m_pID_PICTURE_ResourceWood = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Country, ID_PICTURE_ResourceWood );
	m_pID_PICTURE_ResourceFood = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Country, ID_PICTURE_ResourceFood );
	m_pID_TEXT_ResourceGold = (ControlText*)theUiManager.FindControl( ID_FRAME_Country, ID_TEXT_ResourceGold );
	m_pID_TEXT_ResourceFood = (ControlText*)theUiManager.FindControl( ID_FRAME_Country, ID_TEXT_ResourceFood );
	m_pID_TEXT_ResourceRock = (ControlText*)theUiManager.FindControl( ID_FRAME_Country, ID_TEXT_ResourceRock );
	m_pID_TEXT_ResourceWood = (ControlText*)theUiManager.FindControl( ID_FRAME_Country, ID_TEXT_ResourceWood );
	m_pID_BUTTON_CollectReasource = (ControlButton*)theUiManager.FindControl( ID_FRAME_Country, ID_BUTTON_CollectReasource );
	m_pID_BUTTON_Free = (ControlButton*)theUiManager.FindControl( ID_FRAME_Country, ID_BUTTON_Free );
	m_pID_BUTTON_Prison = (ControlButton*)theUiManager.FindControl( ID_FRAME_Country, ID_BUTTON_Prison );
	m_pID_BUTTON_Silence = (ControlButton*)theUiManager.FindControl( ID_FRAME_Country, ID_BUTTON_Silence );
    m_pID_BUTTON_Rename = (ControlButton*)theUiManager.FindControl( ID_FRAME_Country, ID_BUTTON_Rename );;

	assert( m_pID_FRAME_Country );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_TEXT_CountryTitle );
	assert( m_pID_TEXT_PositionName1 );
	assert( m_pID_TEXT_PositionName2 );
	assert( m_pID_TEXT_PositionName3 );
	assert( m_pID_TEXT_PositionName4 );
	assert( m_pID_TEXT_PositionName5 );
	assert( m_pID_TEXT_PositionName6 );
	assert( m_pID_TEXT_PositionName7 );
	assert( m_pID_BUTTON_PositionSet3 );
	assert( m_pID_BUTTON_PositionSet4 );
	assert( m_pID_BUTTON_PositionSet5 );
	assert( m_pID_BUTTON_PositionSet6 );
	assert( m_pID_BUTTON_PositionSet7 );
	assert( m_pID_TEXT_CountryBroadcast );
	assert( m_pID_TEXT_CountryQuset );
	assert( m_pID_BUTTON_CountryBroadcastNew );
	assert( m_pID_BUTTON_CountryQusetPost );
	assert( m_pID_PICTURE_ResourceGold );
	assert( m_pID_PICTURE_ResourceRock );
	assert( m_pID_PICTURE_ResourceWood );
	assert( m_pID_PICTURE_ResourceFood );
	assert( m_pID_TEXT_ResourceGold );
	assert( m_pID_TEXT_ResourceFood );
	assert( m_pID_TEXT_ResourceRock );
	assert( m_pID_TEXT_ResourceWood );
	assert( m_pID_BUTTON_CollectReasource );
	assert( m_pID_BUTTON_Free );
	assert( m_pID_BUTTON_Prison );
	assert( m_pID_BUTTON_Silence );
    assert( m_pID_BUTTON_Rename );
	
	m_pID_FRAME_Country->SetOnVisibleChangedFun( OnVisibleChange );
	ResetProperties();

    _SetVisable( false );

	return true;
	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_Country::_UnLoadUI()
{
	guardfunc;
	m_pID_FRAME_Country = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_CountryTitle = NULL;
	m_pID_TEXT_PositionName1 = NULL;
	m_pID_TEXT_PositionName2 = NULL;
	m_pID_TEXT_PositionName3 = NULL;
	m_pID_TEXT_PositionName4 = NULL;
	m_pID_TEXT_PositionName5 = NULL;
	m_pID_TEXT_PositionName6 = NULL;
	m_pID_TEXT_PositionName7 = NULL;
	m_pID_BUTTON_PositionSet3 = NULL;
	m_pID_BUTTON_PositionSet4 = NULL;
	m_pID_BUTTON_PositionSet5 = NULL;
	m_pID_BUTTON_PositionSet6 = NULL;
	m_pID_BUTTON_PositionSet7 = NULL;
	m_pID_TEXT_CountryBroadcast = NULL;
	m_pID_TEXT_CountryQuset = NULL;
	m_pID_BUTTON_CountryBroadcastNew = NULL;
	m_pID_BUTTON_CountryQusetPost = NULL;
	m_pID_PICTURE_ResourceGold = NULL;
	m_pID_PICTURE_ResourceRock = NULL;
	m_pID_PICTURE_ResourceWood = NULL;
	m_pID_PICTURE_ResourceFood = NULL;
	m_pID_TEXT_ResourceGold = NULL;
	m_pID_TEXT_ResourceFood = NULL;
	m_pID_TEXT_ResourceRock = NULL;
	m_pID_TEXT_ResourceWood = NULL;
	m_pID_BUTTON_CollectReasource = NULL;
	m_pID_BUTTON_Free = NULL;
	m_pID_BUTTON_Prison = NULL;
	m_pID_BUTTON_Silence = NULL;
    m_pID_BUTTON_Rename = NULL;

	return theUiManager.RemoveFrame( "Data\\UI\\Country.MEUI" );
	unguard;
}

// 是否可视
bool CUI_ID_FRAME_Country::_IsVisable()
{
	guardfunc;
	if ( !m_pID_FRAME_Country )
	{
		assert( false && "ui error" );
		return false;
	}
		
	return m_pID_FRAME_Country->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_Country::_SetVisable( const bool bVisable )
{
	guardfunc;
	if ( !m_pID_FRAME_Country )
	{
		assert( false && "ui error" );
		return;
	}
	m_pID_FRAME_Country->SetVisable( bVisable );
	unguard;
}

void CUI_ID_FRAME_Country::OnVisibleChange( ControlObject* pUIObject )
{
	if( s_CUI_ID_FRAME_Country.IsVisable() )
	{
		s_CUI_ID_FRAME_Country.TryToUpdate();
	}
}
void CUI_ID_FRAME_Country::TryToUpdate()
{
	MsgQueryCountryInfoReq msg;
	GettheNetworkInput().SendMsg( &msg );
}

void CUI_ID_FRAME_Country::Refresh()
{
    if ( !m_pID_FRAME_Country )
        return;

	// 国名
	CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
	if( !pPlayerMgr )
		return;

	CPlayer* pPlayer = pPlayerMgr->GetMe();
	if( !pPlayer )
		return;

	//zhuxincong 9.13 修改GetCountryNameById函数为GetDefaultCountryNameById函数
    m_pID_TEXT_CountryTitle->SetText( CountryFunction::GetDefaultCountryNameById( pPlayer->GetRealCountry() ) );

	// 公告文本  金钱
	m_pID_TEXT_CountryBroadcast->SetText( m_strBroadcastText.c_str() );
	m_pID_TEXT_ResourceGold->SetText( m_strMoney.c_str() );

	// 官员
	for( int i = 0; i < Position_Max; i++ )
	{
		switch( i )
		{
		case Position_None:
			break;
		case Position_King:
			m_pID_TEXT_PositionName1->SetText( m_strOfficalName[ Position_King ].c_str() );
			break;
		case Position_Queen:
			m_pID_TEXT_PositionName2->SetText( m_strOfficalName[ Position_Queen ].c_str() );
			break;
		case Position_CouncilorLeft:
			m_pID_TEXT_PositionName3->SetText( m_strOfficalName[ Position_CouncilorLeft ].c_str() );
			break;
		case Position_General:
			m_pID_TEXT_PositionName4->SetText( m_strOfficalName[ Position_General ].c_str() );
			break;
		case Position_CouncilorRight:
			m_pID_TEXT_PositionName5->SetText( m_strOfficalName[ Position_CouncilorRight ].c_str() );
			break;
		case Position_CaptorLeft:
			m_pID_TEXT_PositionName6->SetText( m_strOfficalName[ Position_CaptorLeft ].c_str() );
			break;
		case Position_CaptorRight:
			m_pID_TEXT_PositionName7->SetText( m_strOfficalName[ Position_CaptorRight ].c_str() );
			break;
		default:
			break;
		}
	}

	// 国务
	for( int i = 0; i < QuestType_Max; i++ )
	{
		switch( i )
		{
		case QuestType_King:			// 国运任务
			m_strTaskText += theXmlString.GetString( eText_Country_Task_GuoYun ) + std::string( "      " );
			if( m_taskStatus[ QuestType_King ].uchCount )
				m_strTaskText += theXmlString.GetString( eText_Country_Task_Dbt ) + std::string( "\n" );
			else
				m_strTaskText += theXmlString.GetString( eText_Country_Task_NotDbt ) + std::string( "\n" );
			break;
		case QuestType_General:			// 出国任务
			m_strTaskText += theXmlString.GetString( eText_Country_Task_ChuGuo ) + std::string( "      " );
			if( m_taskStatus[ QuestType_General ].uchCount )
				m_strTaskText += theXmlString.GetString( eText_Country_Task_Dbt ) + std::string( "\n" );
			else
				m_strTaskText += theXmlString.GetString( eText_Country_Task_NotDbt ) + std::string( "\n" );
			break;
		case QuestType_CouncilorLeft:	// 天行任务
			m_strTaskText += theXmlString.GetString( eText_Country_Task_TianXing ) + std::string( "      " );
			if( m_taskStatus[ QuestType_CouncilorLeft ].uchCount )
				m_strTaskText += theXmlString.GetString( eText_Country_Task_Dbt ) + std::string( "\n" );
			else
				m_strTaskText += theXmlString.GetString( eText_Country_Task_NotDbt ) + std::string( "\n" );
			break;
		case QuestType_CouncilorRight:	// 探宝任务
			m_strTaskText += theXmlString.GetString( eText_Country_Task_TanBao ) + std::string( "      " );
			if( m_taskStatus[ QuestType_CouncilorRight ].uchCount )
				m_strTaskText += theXmlString.GetString( eText_Country_Task_Dbt ) + std::string( "\n" );
			else
				m_strTaskText += theXmlString.GetString( eText_Country_Task_NotDbt ) + std::string( "\n" );
			break;
		default:
			break;
		}
	}
	m_pID_TEXT_CountryQuset->SetText( m_strTaskText.c_str() );


// 身份权力
	// 公告发布权
	if( m_nCountryRight & Right_Placard )
		m_pID_BUTTON_CountryBroadcastNew->SetEnable( true );
	else
		m_pID_BUTTON_CountryBroadcastNew->SetEnable( false );

	// 任免权
	if( m_nCountryRight & Right_AppointKing )
	{
		// 国王的任免权
		m_pID_BUTTON_PositionSet3->SetEnable( true );
		m_pID_BUTTON_PositionSet4->SetEnable( true );
		m_pID_BUTTON_PositionSet5->SetEnable( true );
		m_pID_BUTTON_PositionSet6->SetEnable( false );
		m_pID_BUTTON_PositionSet7->SetEnable( false );
	}
	else if( m_nCountryRight & Right_AppointGeneral )
	{
		// 大将军的任免权
		m_pID_BUTTON_PositionSet3->SetEnable( false );
		m_pID_BUTTON_PositionSet4->SetEnable( false );
		m_pID_BUTTON_PositionSet5->SetEnable( false );
		m_pID_BUTTON_PositionSet6->SetEnable( true );
		m_pID_BUTTON_PositionSet7->SetEnable( true );
	}
	else
	{
		// 其他人无任免权
		m_pID_BUTTON_PositionSet3->SetEnable( false );
		m_pID_BUTTON_PositionSet4->SetEnable( false );
		m_pID_BUTTON_PositionSet5->SetEnable( false );
		m_pID_BUTTON_PositionSet6->SetEnable( false );
		m_pID_BUTTON_PositionSet7->SetEnable( false );
	}

	// 国务发布权
	//if( m_nCountryRight & ( Right_QuestKing | Right_QuestGeneral | Right_QuestCouncilorLeft | Right_QuestCouncilorRight ) )
	//	m_pID_BUTTON_CountryQusetPost->SetEnable( true );
	//else
	//	m_pID_BUTTON_CountryQusetPost->SetEnable( false );

    // 更改国号权
    if( m_nCountryRight & Right_ChangeName )
        m_pID_BUTTON_Rename->SetEnable( true );
    else
        m_pID_BUTTON_Rename->SetEnable( false );

	// 禁言权
	if( m_nCountryRight & Right_BanSpeak )
		m_pID_BUTTON_Silence->SetEnable( true );
	else
		m_pID_BUTTON_Silence->SetEnable( false );

	// 囚禁权
	if( m_nCountryRight & Right_Chain )
		m_pID_BUTTON_Prison->SetEnable( true );
	else
		m_pID_BUTTON_Prison->SetEnable( false );

	// 赦免权
	if( m_nCountryRight & Right_Remit )
		m_pID_BUTTON_Free->SetEnable( true );
	else
		m_pID_BUTTON_Free->SetEnable( false );

	// 募集权
	if( m_nCountryRight & Right_Raise )
		m_pID_BUTTON_CollectReasource->SetEnable( true );
	else
		m_pID_BUTTON_CollectReasource->SetEnable( false );
	
}

void CUI_ID_FRAME_Country::ResetProperties()
{
	m_strBroadcastText = "";
	m_strTaskText = "";
	m_strMoney = "";
	m_nMoney = 0;
	m_nCountryRight = 0;
	for( int i = 0; i < Position_Max; i++ )
		m_strOfficalName[ i ] = "";
	for( int i = 0; i < QuestType_Max; i++ )
	{
		m_taskStatus[ i ].uchCount = 0;
		m_taskStatus[ i ].nLeftTime = 0;
	}
}

void CUI_ID_FRAME_Country::RefreshCountryNameBelongs()
{
    if( IsUILoad() )
    {
        std::string str = CountryFunction::GetCountryNameById( thePlayerRole.GetCountry() );
        m_pID_TEXT_CountryTitle->SetText( str.c_str() );
    }

    DWORD dwColor = Color_Config.getColor( CC_Center_MapInfo );
    s_CUI_ID_FRAME_MiniMap.ShowMapName( dwColor );
    s_CUI_ID_FRAME_AllNpcList.RefreshMapList();
}


void CUI_ID_FRAME_Country::GetCountryDate(const MsgUpdateCountryDate* pMsg )
{
	if (!pMsg)
	{
		return;
	}

	switch (pMsg->chType)
	{
	case UpdateTribute:
		m_nTribute = pMsg->nValue;
		break;
	}
	Refresh();
}

// 以下为接收的服务器消息
void CUI_ID_FRAME_Country::GetCountryInfo( const MsgQueryCountryInfoAck* pMsg )
{
	if( !pMsg )
		return;

	ResetProperties();

	m_strBroadcastText = pMsg->szNotice;
	for( int i = 0; i < Position_Max; i++ )
		m_strOfficalName[ i ] = pMsg->szOfficial[ i ];


    // 金银铜
	m_nMoney = pMsg->nMoney;
    uint32 nCopper = m_nMoney % 100;
    uint32 nSiller = ( m_nMoney / 100 ) % 100;
    uint32 nGold = m_nMoney / 10000;
    char szMoney[ STR_MAXLEN ] = {0};
    MeSprintf_s( szMoney, STR_MAXLEN - 1, "%u{#83}", nCopper );
    m_strMoney = szMoney;
    if( nSiller )
    {
        MeSprintf_s( szMoney, STR_MAXLEN - 1, "%u{#82}%s", nSiller, m_strMoney.c_str() );
        m_strMoney = szMoney;
    }
    if( nGold )
    {
	    MeSprintf_s( szMoney, STR_MAXLEN - 1, "%u{#81}%s", nGold, m_strMoney.c_str() );
        m_strMoney = szMoney;
    }

	m_nCountryRight = pMsg->nCountryRight;
	for( int i = 0; i < QuestType_Max; i++ )
	{
		m_taskStatus[ i ].uchCount = pMsg->xQuestStatus[ i ].uchCount;
		m_taskStatus[ i ].nLeftTime = pMsg->xQuestStatus[ i ].nLeftTime;
	}

	Refresh();
}

void CUI_ID_FRAME_Country::GetRaiseResult( uint8 result )
{
	switch( result )
	{
	case MsgCountryRequestRaiseAck::ECD_Success:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Raise_Success ) );
		TryToUpdate();
		break;
	case MsgCountryRequestRaiseAck::ECD_NotRight:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Raise_NotRight ) );
		break;
	case MsgCountryRequestRaiseAck::ECD_TimeLimit:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Raise_TimeLimit ) );
		break;
	default:
		break;
	}
}

void CUI_ID_FRAME_Country::GetReceiveMountResult( uint8 result )
{
	// 领取坐骑
	switch( result )
	{
	case MsgCountryReceiveMountAck::ECD_Success:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Mount_Success ) );
		TryToUpdate();
		break;
	case MsgCountryReceiveMountAck::ECD_NotRight:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Mount_NotRight ) );
		break;
	case MsgCountryReceiveMountAck::ECD_Alreadly:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Mount_Alreadly ) );
		break;
	case MsgCountryReceiveMountAck::ECD_NotHaveMount:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Mount_NotHave ) );
		break;
	case MsgCountryReceiveMountAck::ECD_MaxCount:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Mount_MaxCount ) );
		break;
	default:
		break;
	}
}

void CUI_ID_FRAME_Country::GetKillOfficialInfo( const MsgTellCountryKillPosition* pMsg )
{
	if( !pMsg )
		return;

	// 杀死国家官员
    std::string strCountryName1 = CountryFunction::GetCountryNameById( pMsg->uchKillerCountry );
    std::string strCountryName2 = CountryFunction::GetCountryNameById( pMsg->uchBeKilledCountry );
    std::string strPlayerPostion = CountryFunction::GetCountryOfficialNameById( pMsg->uchBeKilledPosition );

	char szKillInfo[ eMAX_TEMP_BUFF ];
	MeSprintf_s( szKillInfo, eMAX_TEMP_BUFF - 1, theXmlString.GetString( eText_Country_Kill_Offical ), 
		strCountryName1.c_str(), pMsg->szKillerName, strCountryName2.c_str(), strPlayerPostion.c_str(), pMsg->szBeKilledName );
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_OfficialBeKilled, szKillInfo );
}

void CUI_ID_FRAME_Country::GetCountryTitleInfo( uint16 title )
{
    thePlayerRole.m_charinfo.baseinfo.liveinfo.nCountryTitle = title;
	m_nCountryRight = ( uint32 )GetCountryRightByTitle( ( unsigned short )title );
	s_CUI_ID_FRAME_CountryQuestPost.GetNewCountryRight( m_nCountryRight );
	TryToUpdate();
}

// 国家募捐回馈
void CUI_ID_FRAME_Country::TellCountryDonateResult( uint8 result )
{
    switch( result )
    {
    case MsgCountryRaiseTellPlayer::ECD_Success:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Donate_Success ) );
        s_CUI_ID_FRAME_Country.TryToUpdate();
        break;
    case MsgCountryRaiseTellPlayer::ECD_LevelLess:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Donate_LevelLess ) );
        break;
    case MsgCountryRaiseTellPlayer::ECD_NotEnoughMoney:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Donate_NotEnoughMoney ) );
        break;
    case MsgCountryRaiseTellPlayer::ECD_ErrorRaiseMoney:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Donate_ErrorRaiseMoney ) );
        break;
    case MsgCountryRaiseTellPlayer::ECD_NotRaiseTime:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Donate_NotRaiseTime ) );
        break;
    case MsgCountryRaiseTellPlayer::ECD_CountryMoneyMax:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Donate_CountryMoneyMax ) );
        break;
    }
}

// 以下为国家召集的功能
void CUI_ID_FRAME_Country::GetConveneResult( uint8 result )
{
	switch( result )
	{
	case MsgCountryConveneResult::ECD_Success:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_CountryConvene_Success ) );
		TryToUpdate();
		break;
	case MsgCountryConveneResult::ECD_NotRight:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_CountryConvene_NotRight ) );
		break;
	case MsgCountryConveneResult::ECD_TimeLimit:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_CountryConvene_TimeLimit ) );
		break;
	case MsgCountryConveneResult::ECD_NotEnoughMoney:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_CountryConvene_NotEnoughMoney ) );
		break;
	default:
		break;
	}
}
void CUI_ID_FRAME_Country::ShowCountryConvene()
{
	s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_CountryConvene_YesOrNo ), "", CUI_ID_FRAME_MessageBox::eTypeYesNo,
		false, ProcessConveneReply );
}

bool CUI_ID_FRAME_Country::ProcessConveneReply( const char bYesPress, void *pData )
{
	if( bYesPress )
	{
		MsgCountryConveneAck msg;
		GettheNetworkInput().SendMsg( &msg );
		return true;
	}
	return true;
}

void CUI_ID_FRAME_Country::GetBattleSignUpResult( uint8 result )
{
    switch( result )
    {
    case CampDefine::SignUp_Success:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
            theXmlString.GetString( eText_CountryBattle_SignUp_Success ) );
        break;
    case CampDefine::SignUp_NotSignUpStatus:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
            theXmlString.GetString( eText_CountryBattle_SignUp_NotTime ) );
        break;
    case CampDefine::SignUp_MustGuildMaster:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
            theXmlString.GetString( eText_CountryBattle_SignUp_MustMaster ) );
        break;
    case CampDefine::SignUp_GuildLevelLess:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
            theXmlString.GetString( eText_CountryBattle_SignUp_LevelLess ) );
        break;
    case CampDefine::SignUp_GuildMemberLess:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
            theXmlString.GetString( eText_CountryBattle_SignUp_MemberLess ) );
        break;
    case CampDefine::SignUp_GuildStrengthLess:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
            theXmlString.GetString( eText_CountryBattle_SignUp_StrengthLess ) );
        break;
	case CampDefine::SignUp_GuildUnionBattleSumError:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
				theXmlString.GetString( eText_SignUp_GuildUnionBattleSumError ) );
		}
		break;
	case CampDefine::SignUp_GuildUnionBattleNone:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
				theXmlString.GetString( eText_SignUp_GuildUnionBattleNone ) );
		}
		break;
	case CampDefine::SignUp_GuildBattleFull:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
				theXmlString.GetString( eText_SignUp_GuildBattleFull ) );
		}
		break;
    case CampDefine::SignUp_NotEnoughGuildMoney:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
            theXmlString.GetString( eText_CountryBattle_SignUp_MoreMoney ) );
        break;
    case CampDefine::SignUp_AlreadySignUp:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
            theXmlString.GetString( eText_CountryBattle_SignUp_Already ) );
        break;
    case CampDefine::SignUp_CanNotSignUp:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
            theXmlString.GetString( eText_CountryBattle_SignUp_CanNot ) );
        break;
    default:
        break;
    }
}

void CUI_ID_FRAME_Country::TellCountryBattleSignUp( uint8 nType, uint32 nTime )
{
    // 报名持续时间
    char szTemp[MAX_PATH] = {0};
    std::string strBattleName = CountryFunction::GetCountryBattleNameByType( nType );
    std::string strTime = CountryFunction::GetTimeStringBySeconds( ( DWORD )nTime * 1000 );
    MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_SignUp ), strBattleName.c_str(), strTime.c_str() );
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast, szTemp );
}

void CUI_ID_FRAME_Country::TellGuildCountryBattleQualify( uint8 nBattleType, uint32 nGuildID )
{
    // 公会获得进入战场资格
    const CGuildInfo* pGuildInfo = thePlayerRole.GetGuildById( nGuildID );
    if( !pGuildInfo )
        return;
    
    char szTemp[MAX_PATH] = {0};
    std::string strBattleName = CountryFunction::GetCountryBattleNameByType( nBattleType );
    MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_GuildOwnRight ), pGuildInfo->GetName(), strBattleName.c_str() );
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Bull_System, szTemp);
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_GuildCamp_Message, szTemp);
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ShiTu_Belongs_Success, szTemp);
}

void CUI_ID_FRAME_Country::TellCountryBattleEnterBegin( uint8 nBattleType, uint32 nTime )
{
    // 开始进入
    char szTemp[MAX_PATH] = {0};
    std::string strBattleName = CountryFunction::GetCountryBattleNameByType( nBattleType );
    std::string strTime = CountryFunction::GetTimeStringBySeconds( ( DWORD )nTime * 1000 );
    MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_Open ), strBattleName.c_str(), strTime.c_str() );
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast, szTemp );
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp );
}

void CUI_ID_FRAME_Country::TellCountryBattleBegin( uint8 nBattleType, uint32 nTime )
{
    // 战斗开始
    char szTemp[MAX_PATH] = {0};
    std::string strBattleName = CountryFunction::GetCountryBattleNameByType( nBattleType );
    std::string strTime = CountryFunction::GetTimeStringBySeconds( ( DWORD )nTime * 1000 );
    MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_BattleBegin ), strBattleName.c_str(), strTime.c_str() );
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast, szTemp );
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp );
}

void CUI_ID_FRAME_Country::TellCountryBattleResult( uint8 nBattleType, uint8 nWinType, uint32 nGuildID )
{
    // 国家战场结果
    const CGuildInfo* pGuildInfo = thePlayerRole.GetGuildById( nGuildID );
    if( !pGuildInfo )
        return;

    char szTemp[MAX_PATH] = {0};
	char szTemp1[MAX_PATH] = {0};
    std::string strBattleName = CountryFunction::GetCountryBattleNameByType( nBattleType );
    switch( nWinType )
    {
    case BattleWin_FistTime:
        {
            MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryKing_ApplySuccess ), pGuildInfo->GetName() );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast, szTemp );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_GuildCamp_Message, szTemp);
        }
        break;
    case BattleWin_Guard:
        {
            MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_GuardSuccess ),
                strBattleName.c_str(), pGuildInfo->GetName() );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast, szTemp );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_GuildCamp_Message, szTemp);

			MeSprintf_s(szTemp1,sizeof(szTemp1)/ sizeof(char) - 1,theXmlString.GetString(eText_CountryBattle_QuitCountryWar));
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_FindPathFailed, szTemp1);
        }
        break;
    case BattleWin_Challenge:
        {
            MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_ChallengeSuccess ),
                strBattleName.c_str(), pGuildInfo->GetName() );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast, szTemp );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_GuildCamp_Message, szTemp);

			MeSprintf_s(szTemp1,sizeof(szTemp1)/ sizeof(char) - 1,theXmlString.GetString(eText_CountryBattle_QuitCountryWar));
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_FindPathFailed, szTemp1);
        }
        break;
    default:
        break;
    }
}

//void CUI_ID_FRAME_Country::TellEnterCountryBattle( uint8 nBattleType, uint8 nResult )
//{
//    // 进入战场报错
//    char szErrorDes[MAX_PATH] = {0};
//    std::string strBattleName = CountryFunction::GetCountryBattleNameByType( nBattleType );
//    if( strBattleName.empty() )
//        return;
//
//    switch( nResult )
//    {
//    case MsgEnterCountryBattleAck::ECD_NotEnterTime:
//        MeSprintf_s( szErrorDes, sizeof( szErrorDes ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_EnterNotTime ), strBattleName.c_str() );
//        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Battle_Failed, szErrorDes );
//        break;
//    case MsgEnterCountryBattleAck::ECD_NotSignUpGuild:
//        MeSprintf_s( szErrorDes, sizeof( szErrorDes ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_EnterNotGuild ), strBattleName.c_str() );
//        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Battle_Failed, szErrorDes );
//        break;
//    case MsgEnterCountryBattleAck::ECD_StageNotOpen:
//        MeSprintf_s( szErrorDes, sizeof( szErrorDes ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_NotCreate ), strBattleName.c_str() );
//        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Battle_Failed, szErrorDes );
//        break;
//    default:
//        break;
//    }
//}

//void CUI_ID_FRAME_Country::TellCountryBattleQuery( uint8 nBattleType, uint8 nResult, uint32 nGuildID )
//{
//    // 改为脚本实现
//}

void CUI_ID_FRAME_Country::TellBetrayCountry( uint8 nCountry, uint8 nPlayerId )
{
    // 叛国通告
    char szTemp[MAX_PATH] = {0};
    CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
    if( !pPlayerMgr )
        return;
    CPlayer* pPlayer = pPlayerMgr->FindByID( nPlayerId );
    if( !pPlayer )
        return;
	int old_counrty = thePlayerRole.GetCountry();//老国家的 ID
    pPlayer->SetRealCountry( nCountry );
    if( pPlayerMgr->GetMe() == pPlayer )
    {
        thePlayerRole.SetCountry( nCountry );
       /* if( thePlayerRole.IsInWeakCountry()&&nCountry != CountryDefine::Country_Init)
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, theXmlString.GetString( eText_Country_BeWeak ) );
        }
		else if( thePlayerRole.IsInStrongCountry()&&nCountry != CountryDefine::Country_Init)
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, theXmlString.GetString( eText_Country_BeStrong ) );
        }*/
        thePlayerRole.UpdateActiveQuestState();
        RefreshCountryNameBelongs();


		//lyh 添加下面几行，加入国家只让主角自己提示 不同步给其他玩家。
		std::string strCountry = "";
		if (old_counrty == CountryDefine::Country_Init)
		{
			strCountry = CountryFunction::GetDefaultCountryNameById( nCountry );
			theCountryTipInstance.AddTips(nCountry);
		}
		else if(old_counrty != thePlayerRole.GetCountry())
		{
			strCountry = CountryFunction::GetDefaultCountryNameById( nCountry );//zhuxincong 9.13 修改GetCountryNameById函数为GetDefaultCountryNameById函数
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBetray_Broadcast ), pPlayer->GetName(), strCountry.c_str() );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp );
			

		}
		std::string strWindowName = s_CUI_ID_FRAME_Select.m_strWindowText+" " + CountryFunction::GetDefaultCountryNameById( nCountry );
		theHeroGame.SetWindowText( strWindowName.c_str() );

    }

	//if (old_counrty == CountryDefine::Country_Init)
	//{
	//	//std::string strCountry = CountryFunction::GetDefaultCountryNameById( nCountry );//zhuxincong 9.13 修改GetCountryNameById函数为GetDefaultCountryNameById函数
	//	//MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryChange ), strCountry.c_str() );
	//	//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp );
	//	theCountryTipInstance.AddTips(nCountry);
	//	//theCountryTipInstance.Render();
	//}
	//else if(old_counrty != thePlayerRole.GetCountry())
	//{
	//	std::string strCountry = CountryFunction::GetDefaultCountryNameById( nCountry );//zhuxincong 9.13 修改GetCountryNameById函数为GetDefaultCountryNameById函数
	//	MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBetray_Broadcast ), pPlayer->GetName(), strCountry.c_str() );
	//	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp );
	//}
}

void CUI_ID_FRAME_Country::TellBetrayCountryResult( uint8 nResult )
{
    // 叛国结果
    switch( nResult )
    {
    case MsgCountryChangeAck::ECD_Success:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Success, theXmlString.GetString( eText_CountryBetray_Success ) );
        break;
    case MsgCountryChangeAck::ECD_HaveTeam:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_NoTeam ) );
        break;
    case MsgCountryChangeAck::ECD_HaveGuild:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_NoGuild ) );
        break;
    case MsgCountryChangeAck::ECD_SameCountry:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_NoSameCountry ) );
        break;
    case MsgCountryChangeAck::ECD_ErrorCountry:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_ErrorCountry ) );
        break;
    case MsgCountryChangeAck::ECD_NotEnoughMoney:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_NoMoney ) );
        break;
    case MsgCountryChangeAck::ECD_HaveMarriage:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_NoMarry ) );
        break;
    case MsgCountryChangeAck::ECD_HaveStudent:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_NoStudent ) );
        break;
    case MsgCountryChangeAck::ECD_HaveTeacher:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_NoTeacher ) );
        break;
    case MsgCountryChangeAck::ECD_TimeLimit:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_OncePerWeek ) );
        break;
	/*case MsgCountryChangeAck::ECD_Config:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_config ) );
		break;*/
	case MsgCountryChangeAck::ECD_HaveOff:
		 CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_Office ) );
		break;
	case MsgCountryChangeAck::ECD_Item:
		 CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_Item ) );
		break;
	case MsgCountryChangeAck::ECD_MaxLevel:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_MaxLevel ) );
		break;
	case MsgCountryChangeAck::ECD_MinLevel:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_MinLeve ) );
		break;
	case MsgCountryChangeAck::ECD_QuestStates:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_QuestState ) );
		break;
    default:
        break;
    }
}

void CUI_ID_FRAME_Country::TellCountryBattleReplace( uint8 nBattleType )
{
    // 战场报名被顶
    std::string strBattleName = CountryFunction::GetCountryBattleNameByType( nBattleType );
    char szTemp[MAX_PATH] = {0};
    MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_SignUpBeReplaced ), strBattleName.c_str() );
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Battle_Failed, szTemp );
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp );
}

void CUI_ID_FRAME_Country::TellCountryWeak( uint8 nWeakCountry )
{
    // 弱国任务
    /*if( nWeakCountry == thePlayerRole.GetCountry()&&nWeakCountry != CountryDefine::Country_Init)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, theXmlString.GetString( eText_Country_BeWeak ) );
    }*/
    thePlayerRole.SetWeakCountry( nWeakCountry );
    thePlayerRole.UpdateActiveQuestState();
	/*
	 *	Author 2012-9-22 zhuxincong
	 *	DESC: 国家逻辑中因为0为无国籍的判断，而在弱国判断中0为弱国.
			那么在国家逻辑中，玩家加入国家后就不会再次回到0，那么我就全部注释掉了。
	 */
	return;
}
void CUI_ID_FRAME_Country::TellCountryStrong( uint8 nStrongCountry )
{
	//设置本国为强国
	/*if( nStrongCountry == thePlayerRole.GetCountry()&&nStrongCountry != CountryDefine::Country_Init)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, theXmlString.GetString( eText_Country_BeStrong ) );
    }*/
    thePlayerRole.SetStrongCountry( nStrongCountry );
    thePlayerRole.UpdateActiveQuestState();
	return;
}
void CUI_ID_FRAME_Country::TellCountryNameChange( uint8 nCountryId, char* szName, char* szKingName )
{
    // 更改国号
    CountryFunction::Instance()->UpdateCountryName( nCountryId, szName );
    RefreshCountryNameBelongs();

    if( thePlayerRole.GetCountry() == nCountryId )
    {
        char szTemp[MAX_PATH] = {0};
        MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_Country_KingChangeName ), szKingName, szName );
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_ChangeName, szTemp );
    }
}

void CUI_ID_FRAME_Country::TellCountryNameInit( char* szName )
{
    // 获取国号
    for( int i = Country_Init + 1; i < CountryDefine::Country_Max; ++i )
    {
        CountryFunction::Instance()->UpdateCountryName( i, szName + i * CountryDefine::MaxCountryLength );
    }
    RefreshCountryNameBelongs();
}

void CUI_ID_FRAME_Country::TellChangeCountryNameResult( int nResult )
{
    // 改国号回馈
    switch( nResult )
    {
    case MsgChangeCountryNameAck::ECD_Success:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_ChangeNameSuccess ) );
        break;
    case MsgChangeCountryNameAck::ECD_NotHaveRight:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_ChangeNameNoRight ) );
        break;
    case MsgChangeCountryNameAck::ECD_ChangeOnce:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_ChangeNameOnce ) );
        break;
    case MsgChangeCountryNameAck::ECD_ErrorName:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_ChangeNameError ) );
        break;
    default:
        break;
    }
}

void CUI_ID_FRAME_Country::TellCountryWarStatus( int nStatus )
{
    // 屠城战
    switch( nStatus )
    {
    case CountryDefine::WarStatusPrepare:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast,
                theXmlString.GetString( eText_CountryWar_WillBegin ) );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate,
                theXmlString.GetString( eText_CountryWar_WillBegin ) );
        }
        break;
    case CountryDefine::WarStatusFight:
        {
            s_CUI_ID_FRAME_HolyShit.SetCountryBattleShow( true );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast,
                theXmlString.GetString( eText_CountryWar_Begin ) );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate,
                theXmlString.GetString( eText_CountryWar_Begin ) );
        }
        break;
    case CountryDefine::WarStatusEnd:
        {
            s_CUI_ID_FRAME_HolyShit.SetCountryBattleShow( false );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast, theXmlString.GetString( eText_CountryWar_End ) );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, theXmlString.GetString( eText_CountryWar_End ) );
        }
        break;
    default:
        break;
    }
}

void CUI_ID_FRAME_Country::TellPlayerRaiseResult( const char* pName, int nMoney )
{
    // 广播募捐
    if( !pName || nMoney <= 0 )
        return;

    int nGold( 0 ), nSilver( 0 ), nCopper( 0 );
    thePlayerRole.GetGSCFromMoney( nMoney, nGold, nSilver, nCopper );

    std::stringstream str;
    if( nGold > 0 )
        str << nGold << theXmlString.GetString( eText_Money_Gold );
    if( nSilver > 0 )
        str << nSilver << theXmlString.GetString( eText_Money_Silver );
    if( nCopper > 0 || ( nGold == 0 && nSilver == 0 ) )
        str << nCopper << theXmlString.GetString( eText_Money_Copper );
    std::string strMoney = str.str();

    char szTemp[MAX_PATH] = {0};
    MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryRise_Broadcast ), pName, strMoney.c_str() );
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryRaise_Broadcast, szTemp );
}
