/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\国家界面\CountryQuestPost.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "CountryQuestPost.h"
#include "Common.h"
#include "tstring.h"
#include "TimeEx.h"
#include "ActivityTrack.h"
#include "BullSystem.h"

using namespace Common;

#ifndef STR_MAXLEN
#define STR_MAXLEN		255
#endif
#define COUNTRY_CONFIG_PATH		"..\\Data\\Config\\Country.config"

CUI_ID_FRAME_CountryQuestPost s_CUI_ID_FRAME_CountryQuestPost;

MAP_FRAME_RUN( s_CUI_ID_FRAME_CountryQuestPost, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CountryQuestPost, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CountryQuestPost, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CountryQuestPost, ID_BUTTON_Post1OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CountryQuestPost, ID_BUTTON_Post2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CountryQuestPost, ID_BUTTON_Post3OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CountryQuestPost, ID_BUTTON_Post4OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CountryQuestPost, ID_BUTTON_TurnLeftOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CountryQuestPost, ID_BUTTON_TurnRightOnButtonClick )

CUI_ID_FRAME_CountryQuestPost::CUI_ID_FRAME_CountryQuestPost()
{
	// Member
	m_pID_FRAME_CountryQuestPost = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_Command1 = NULL;
	m_pID_TEXT_Command2 = NULL;
	m_pID_TEXT_Command3 = NULL;
	m_pID_TEXT_Command4 = NULL;
	m_pID_TEXT_Commander1 = NULL;
	m_pID_TEXT_Commander2 = NULL;
	m_pID_TEXT_Commander3 = NULL;
	m_pID_TEXT_Commander4 = NULL;
	m_pID_TEXT_QuestDesc1 = NULL;
	m_pID_TEXT_QuestDesc2 = NULL;
	m_pID_TEXT_QuestDesc3 = NULL;
	m_pID_TEXT_QuestDesc4 = NULL;
	m_pID_BUTTON_Post1 = NULL;
	m_pID_BUTTON_Post2 = NULL;
	m_pID_BUTTON_Post3 = NULL;
	m_pID_BUTTON_Post4 = NULL;
	m_pID_BUTTON_TurnLeft = NULL;
	m_pID_BUTTON_TurnRight = NULL;
	m_pID_TEXT_Page = NULL;
}
// Frame
bool CUI_ID_FRAME_CountryQuestPost::OnFrameRun()
{
	if ( !m_pID_FRAME_CountryQuestPost )
	{
		assert( false && "ui error" );
		return false;
	}
	if( !IsVisable() )
		return false;

	return true;
}
bool CUI_ID_FRAME_CountryQuestPost::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_CountryQuestPost::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CountryQuestPost )
	{
		assert( false && "ui error" );
		return false;
	}
	SetVisable( false );
	return true;
}
// Button
bool CUI_ID_FRAME_CountryQuestPost::ID_BUTTON_Post1OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CountryQuestPost )
	{
		assert( false && "ui error" );
		return false;
	}

	//给服务器发消息
	if( m_countryTaskVec.size() <= m_nPage * 4 )
		return false;

	MsgCountryQuestStatusChangeReq msg;
	msg.uchQuestType = m_countryTaskVec[ m_nPage * 4 ].taskType;
	GettheNetworkInput().SendMsg( &msg );

	SetVisable( false );
	return true;
}
// Button
bool CUI_ID_FRAME_CountryQuestPost::ID_BUTTON_Post2OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CountryQuestPost )
	{
		assert( false && "ui error" );
		return false;
	}

	//给服务器发消息
	if( m_countryTaskVec.size() <= m_nPage * 4 + 1 )
		return false;

	MsgCountryQuestStatusChangeReq msg;
	msg.uchQuestType = m_countryTaskVec[ m_nPage * 4 + 1 ].taskType;
	GettheNetworkInput().SendMsg( &msg );

	SetVisable( false );
	return true;
}
// Button
bool CUI_ID_FRAME_CountryQuestPost::ID_BUTTON_Post3OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CountryQuestPost )
	{
		assert( false && "ui error" );
		return false;
	}

	//给服务器发消息
	if( m_countryTaskVec.size() <= m_nPage * 4 + 2 )
		return false;

	MsgCountryQuestStatusChangeReq msg;
	msg.uchQuestType = m_countryTaskVec[ m_nPage * 4 + 2 ].taskType;
	GettheNetworkInput().SendMsg( &msg );

	SetVisable( false );
	return true;
}
// Button
bool CUI_ID_FRAME_CountryQuestPost::ID_BUTTON_Post4OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CountryQuestPost )
	{
		assert( false && "ui error" );
		return false;
	}

	//给服务器发消息
	if( m_countryTaskVec.size() <= m_nPage * 4 + 3 )
		return false;

	MsgCountryQuestStatusChangeReq msg;
	msg.uchQuestType = m_countryTaskVec[ m_nPage * 4 + 3 ].taskType;
	GettheNetworkInput().SendMsg( &msg );

	SetVisable( false );
	return true;
}
// Button
bool CUI_ID_FRAME_CountryQuestPost::ID_BUTTON_TurnLeftOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CountryQuestPost )
	{
		assert( false && "ui error" );
		return false;
	}
	m_nPage--;
	UpdatePages();
	return true;
}
// Button
bool CUI_ID_FRAME_CountryQuestPost::ID_BUTTON_TurnRightOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CountryQuestPost )
	{
		assert( false && "ui error" );
		return false;
	}
	m_nPage++;
	UpdatePages();
	return true;
}

// 装载UI
bool CUI_ID_FRAME_CountryQuestPost::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CountryQuestPost.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CountryQuestPost.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_CountryQuestPost::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_CountryQuestPost, s_CUI_ID_FRAME_CountryQuestPostOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_CountryQuestPost, s_CUI_ID_FRAME_CountryQuestPostOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_CountryQuestPost, ID_BUTTON_Cancel, s_CUI_ID_FRAME_CountryQuestPostID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CountryQuestPost, ID_BUTTON_Post1, s_CUI_ID_FRAME_CountryQuestPostID_BUTTON_Post1OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CountryQuestPost, ID_BUTTON_Post2, s_CUI_ID_FRAME_CountryQuestPostID_BUTTON_Post2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CountryQuestPost, ID_BUTTON_Post3, s_CUI_ID_FRAME_CountryQuestPostID_BUTTON_Post3OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CountryQuestPost, ID_BUTTON_Post4, s_CUI_ID_FRAME_CountryQuestPostID_BUTTON_Post4OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CountryQuestPost, ID_BUTTON_TurnLeft, s_CUI_ID_FRAME_CountryQuestPostID_BUTTON_TurnLeftOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CountryQuestPost, ID_BUTTON_TurnRight, s_CUI_ID_FRAME_CountryQuestPostID_BUTTON_TurnRightOnButtonClick );

	m_pID_FRAME_CountryQuestPost = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_CountryQuestPost );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_BUTTON_Cancel );
	m_pID_TEXT_Command1 = (ControlText*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_TEXT_Command1 );
	m_pID_TEXT_Command2 = (ControlText*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_TEXT_Command2 );
	m_pID_TEXT_Command3 = (ControlText*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_TEXT_Command3 );
	m_pID_TEXT_Command4 = (ControlText*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_TEXT_Command4 );
	m_pID_TEXT_Commander1 = (ControlText*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_TEXT_Commander1 );
	m_pID_TEXT_Commander2 = (ControlText*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_TEXT_Commander2 );
	m_pID_TEXT_Commander3 = (ControlText*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_TEXT_Commander3 );
	m_pID_TEXT_Commander4 = (ControlText*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_TEXT_Commander4 );
	m_pID_TEXT_QuestDesc1 = (ControlText*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_TEXT_QuestDesc1 );
	m_pID_TEXT_QuestDesc2 = (ControlText*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_TEXT_QuestDesc2 );
	m_pID_TEXT_QuestDesc3 = (ControlText*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_TEXT_QuestDesc3 );
	m_pID_TEXT_QuestDesc4 = (ControlText*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_TEXT_QuestDesc4 );
	m_pID_BUTTON_Post1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_BUTTON_Post1 );
	m_pID_BUTTON_Post2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_BUTTON_Post2 );
	m_pID_BUTTON_Post3 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_BUTTON_Post3 );
	m_pID_BUTTON_Post4 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_BUTTON_Post4 );
	m_pID_BUTTON_TurnLeft = (ControlButton*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_BUTTON_TurnLeft );
	m_pID_BUTTON_TurnRight = (ControlButton*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_BUTTON_TurnRight );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_CountryQuestPost, ID_TEXT_Page );
	
	assert( m_pID_FRAME_CountryQuestPost );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_TEXT_Command1 );
	assert( m_pID_TEXT_Command2 );
	assert( m_pID_TEXT_Command3 );
	assert( m_pID_TEXT_Command4 );
	assert( m_pID_TEXT_Commander1 );
	assert( m_pID_TEXT_Commander2 );
	assert( m_pID_TEXT_Commander3 );
	assert( m_pID_TEXT_Commander4 );
	assert( m_pID_TEXT_QuestDesc1 );
	assert( m_pID_TEXT_QuestDesc2 );
	assert( m_pID_TEXT_QuestDesc3 );
	assert( m_pID_TEXT_QuestDesc4 );
	assert( m_pID_BUTTON_Post1 );
	assert( m_pID_BUTTON_Post2 );
	assert( m_pID_BUTTON_Post3 );
	assert( m_pID_BUTTON_Post4 );
	assert( m_pID_BUTTON_TurnLeft );
	assert( m_pID_BUTTON_TurnRight );
	assert( m_pID_TEXT_Page );
	
	m_nCountryRight = Right_None;
	m_nPage = 0;
	UpdatePages();

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_CountryQuestPost::_UnLoadUI()
{
	m_pID_FRAME_CountryQuestPost = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_Command1 = NULL;
	m_pID_TEXT_Command2 = NULL;
	m_pID_TEXT_Command3 = NULL;
	m_pID_TEXT_Command4 = NULL;
	m_pID_TEXT_Commander1 = NULL;
	m_pID_TEXT_Commander2 = NULL;
	m_pID_TEXT_Commander3 = NULL;
	m_pID_TEXT_Commander4 = NULL;
	m_pID_TEXT_QuestDesc1 = NULL;
	m_pID_TEXT_QuestDesc2 = NULL;
	m_pID_TEXT_QuestDesc3 = NULL;
	m_pID_TEXT_QuestDesc4 = NULL;
	m_pID_BUTTON_Post1 = NULL;
	m_pID_BUTTON_Post2 = NULL;
	m_pID_BUTTON_Post3 = NULL;
	m_pID_BUTTON_Post4 = NULL;
	m_pID_BUTTON_TurnLeft = NULL;
	m_pID_BUTTON_TurnRight = NULL;
	m_pID_TEXT_Page = NULL;
	
	return theUiManager.RemoveFrame( "Data\\UI\\CountryQuestPost.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_CountryQuestPost::_IsVisable()
{
	if ( !m_pID_FRAME_CountryQuestPost )
		return false;
	return m_pID_FRAME_CountryQuestPost->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_CountryQuestPost::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_CountryQuestPost )
		return;

	if( m_pID_FRAME_CountryQuestPost->IsVisable() && bVisable )
	{
		// 找不到置顶的接口，故采用笨办法
		m_pID_FRAME_CountryQuestPost->SetVisable( false );
		m_pID_FRAME_CountryQuestPost->SetVisable( true );
	}

	m_pID_FRAME_CountryQuestPost->SetVisable( bVisable );
}

void CUI_ID_FRAME_CountryQuestPost::InitializeAtEnterWorld()
{
    InitTask();
}

void CUI_ID_FRAME_CountryQuestPost::InitTask()
{
	m_countryTaskVec.clear();
	CountryTask task;
	for( unsigned int i = QuestType_None + 1; i < QuestType_Max; i++ )
	{
		const CountryConfig::QuestSetting* pSetting = theCountryConfig.GetQuestSetting( i );
		if ( pSetting == NULL )
			continue;

		task.taskType = pSetting->GetType();
		task.requireRight = GetQuestRightByType( task.taskType );
		task.nKeepTime = pSetting->GetKeepTime() / 60;
		task.strTaskName = pSetting->GetName();
		task.strPromulgator = pSetting->GetPosition();
		task.strDescribe = pSetting->GetDescription();

		m_countryTaskVec.push_back( task );
	}
}

void CUI_ID_FRAME_CountryQuestPost::UpdatePages()
{
    if ( !m_pID_FRAME_CountryQuestPost )
        return;

	// 左右键
	if( m_nPage == 0 )
		m_pID_BUTTON_TurnLeft->SetEnable( false );
	else
		m_pID_BUTTON_TurnLeft->SetEnable( true );

	if( m_nPage < ( m_countryTaskVec.size() - 1 ) / 4 )
		m_pID_BUTTON_TurnRight->SetEnable( true );
	else
		m_pID_BUTTON_TurnRight->SetEnable( false );

	// 页码
	char page[ STR_MAXLEN ];
	MeSprintf_s( page, STR_MAXLEN - 1, "%d", m_nPage + 1 );
	char pages[ STR_MAXLEN ];
	MeSprintf_s( pages, STR_MAXLEN - 1, "%d", ( m_countryTaskVec.size() - 1 ) / 4 + 1 );
	m_pID_TEXT_Page->SetText( ( std::string( page ) + " / " + std::string( pages ) ).c_str() );

	// 缺省值
	m_pID_TEXT_Command1->SetText( "" );
	m_pID_TEXT_Commander1->SetText( "" );
	m_pID_TEXT_QuestDesc1->SetText( "" );
	m_pID_BUTTON_Post1->SetEnable( false );
	m_pID_TEXT_Command2->SetText( "" );
	m_pID_TEXT_Commander2->SetText( "" );
	m_pID_TEXT_QuestDesc2->SetText( "" );
	m_pID_BUTTON_Post2->SetEnable( false );
	m_pID_TEXT_Command3->SetText( "" );
	m_pID_TEXT_Commander3->SetText( "" );
	m_pID_TEXT_QuestDesc3->SetText( "" );
	m_pID_BUTTON_Post3->SetEnable( false );
	m_pID_TEXT_Command4->SetText( "" );
	m_pID_TEXT_Commander4->SetText( "" );
	m_pID_TEXT_QuestDesc4->SetText( "" );
	m_pID_BUTTON_Post4->SetEnable( false );

	// 任务
	if( m_countryTaskVec.size() > m_nPage * 4 + 3 )
	{
		m_pID_TEXT_Command4->SetText( m_countryTaskVec[ m_nPage * 4 + 3 ].strTaskName.c_str() );
		m_pID_TEXT_Commander4->SetText( m_countryTaskVec[ m_nPage * 4 + 3 ].strPromulgator.c_str() );
		m_pID_TEXT_QuestDesc4->SetText( m_countryTaskVec[ m_nPage * 4 + 3 ].strDescribe.c_str() );
		// 判定身份
		if( m_nCountryRight & m_countryTaskVec[ m_nPage * 4 + 3 ].requireRight )
			m_pID_BUTTON_Post4->SetEnable( true );
		else
			m_pID_BUTTON_Post4->SetEnable( false );
	}
	else
	{
		m_pID_BUTTON_Post4->SetEnable( false );
	}

	if( m_countryTaskVec.size() > m_nPage * 4 + 2 )
	{
		m_pID_TEXT_Command3->SetText( m_countryTaskVec[ m_nPage * 4 + 2 ].strTaskName.c_str() );
		m_pID_TEXT_Commander3->SetText( m_countryTaskVec[ m_nPage * 4 + 2 ].strPromulgator.c_str() );
		m_pID_TEXT_QuestDesc3->SetText( m_countryTaskVec[ m_nPage * 4 + 2 ].strDescribe.c_str() ); 
		// 判定身份
		if( m_nCountryRight & m_countryTaskVec[ m_nPage * 4 + 2 ].requireRight )
			m_pID_BUTTON_Post3->SetEnable( true );
		else
			m_pID_BUTTON_Post3->SetEnable( false );
	}
	else
	{
		m_pID_BUTTON_Post3->SetEnable( false );
	}

	if( m_countryTaskVec.size() > m_nPage * 4 + 1 )
	{
		m_pID_TEXT_Command2->SetText( m_countryTaskVec[ m_nPage * 4 + 1 ].strTaskName.c_str() );
		m_pID_TEXT_Commander2->SetText( m_countryTaskVec[ m_nPage * 4 + 1 ].strPromulgator.c_str() );
		m_pID_TEXT_QuestDesc2->SetText( m_countryTaskVec[ m_nPage * 4 + 1 ].strDescribe.c_str() );
		// 判定身份
		if( m_nCountryRight & m_countryTaskVec[ m_nPage * 4 + 1 ].requireRight )
			m_pID_BUTTON_Post2->SetEnable( true );
		else
			m_pID_BUTTON_Post2->SetEnable( false );
	}
	else
	{
		m_pID_BUTTON_Post2->SetEnable( false );
	}

	if( m_countryTaskVec.size() > m_nPage * 4 )
	{
		m_pID_TEXT_Command1->SetText( m_countryTaskVec[ m_nPage * 4 ].strTaskName.c_str() );
		m_pID_TEXT_Commander1->SetText( m_countryTaskVec[ m_nPage * 4 ].strPromulgator.c_str() );
		m_pID_TEXT_QuestDesc1->SetText( m_countryTaskVec[ m_nPage * 4 ].strDescribe.c_str() ); 
		// 判定身份
		if( m_nCountryRight & m_countryTaskVec[ m_nPage * 4 ].requireRight )
			m_pID_BUTTON_Post1->SetEnable( true );
		else
			m_pID_BUTTON_Post1->SetEnable( false );
	}
	else
	{
		m_pID_BUTTON_Post1->SetEnable( false );
	}
}

void CUI_ID_FRAME_CountryQuestPost::GetNewCountryRight( uint32 countryRight )
{
	m_nCountryRight = countryRight;
	UpdatePages();
}

// 以下为接收的服务器消息
void CUI_ID_FRAME_CountryQuestPost::GetDistributeResult( uint8 result )
{
	switch( result )
	{
	case MsgCountryQuestStatusChangeAck::ECD_Success:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, theXmlString.GetString( eText_Country_Task_Success ) );
		//s_CUI_ID_FRAME_Country.TryToUpdate();
		s_CUI_ID_FRAME_BaseInfo.TryToUpdate();
		break;
	case MsgCountryQuestStatusChangeAck::ECD_NotRight:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Task_NotRight ) );
		break;
	case MsgCountryQuestStatusChangeAck::ECD_Already:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Task_Already ) );
		break;
	case MsgCountryQuestStatusChangeAck::ECD_NotEnoughMoney:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Task_NotEnoughMoney ) );
		break;
	default:
		break;
	}
}

void CUI_ID_FRAME_CountryQuestPost::GetCountryTaskBeginInfo( const MsgTellCountryQuestStatus* pMsg )
{
	if( !pMsg )
		return;
	/*
	 *	Author 2012-11-21 zhuxincong
	 *	DESC: 现在的情况是国家为0的活动面板也是可以接受到其他国家的任务
	 */
	
	//s_CUI_ID_FRAME_Country.TryToUpdate();
	s_CUI_ID_FRAME_BaseInfo.TryToUpdate();
	for( int index = 0; index < pMsg->nCount; index++ )
	{
		std::vector<CountryTask>::size_type i = 0;
		for( ; i < m_countryTaskVec.size(); i++ )
		{
			if( pMsg->xQuest[ index ].uchType == m_countryTaskVec[i].taskType )
			{
				// 加至活动列表
				SpecialActivity activity;
				activity.bVisable = true;
				activity.strName = m_countryTaskVec[i].strTaskName;

				ControlList::S_List	stItem;
				stItem.m_nHiberarchy = 0;
				stItem.m_bCollapse = false;
				stItem.SetData( m_countryTaskVec[i].strTaskName.c_str(), 0, 0, Color_Config.getColor( CC_TASK_NAME ) );
				activity.itemVec.push_back( stItem );
				
				stItem.clear();
				TimeEx time( pMsg->xQuest[ index ].n64StartTime );
				int beginHour = time.GetHour();
				int beginMinute = time.GetMinute();
				int endHour = ( beginHour + ( beginMinute + m_countryTaskVec[i].nKeepTime ) / 60 ) % 24;
				int endMinute = ( beginMinute + m_countryTaskVec[i].nKeepTime ) % 60;
				char szBuf[ eMAX_TEMP_BUFF ];
				MeSprintf_s( szBuf, eMAX_TEMP_BUFF - 1, "%s %02d:%02d - %02d:%02d", theXmlString.GetString( eText_Time ), 
					beginHour, beginMinute, endHour, endMinute );
				stItem.m_nHiberarchy = 1;
				stItem.SetData( szBuf );
				activity.itemVec.push_back( stItem );
				if( (!s_CUI_ID_FRAME_ActivityTrack.AddSpecialActivity( &activity )) )
					return;

				// 加至系统公告
				MeSprintf_s( szBuf, eMAX_TEMP_BUFF - 1, "%s%s", m_countryTaskVec[i].strTaskName.c_str(), 
					theXmlString.GetString( eText_Country_Task_BullBegin ) );
				if( pMsg->xQuest[ index ].bNeedNotice )
                    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szBuf );
			}
		}
	}
}

void CUI_ID_FRAME_CountryQuestPost::GetCountryTaskEndInfo( uint8 result )
{
	//s_CUI_ID_FRAME_Country.TryToUpdate();
	s_CUI_ID_FRAME_BaseInfo.TryToUpdate();
	std::vector<CountryTask>::size_type i = 0;
	for( ; i < m_countryTaskVec.size(); i++ )
	{
		if( m_countryTaskVec[i].taskType == result )
			if( !s_CUI_ID_FRAME_ActivityTrack.DelSpecialActivity( m_countryTaskVec[i].strTaskName ) )
				return;
	}
}
