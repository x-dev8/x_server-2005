/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\CountryQuest.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "CountryQuest.h"
#include "CountryBaseInfo.h"
#include "CountryMessage.h"
#include "ActivityTrack.h"
CUI_ID_FRAME_Quest s_CUI_ID_FRAME_Quest;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Quest, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Quest, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Quest, ID_BUTTON_GuoYunOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Quest, ID_BUTTON_GuoTanOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Quest, ID_BUTTON_HuLiangOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Quest, ID_BUTTON_BinShuOnButtonClick )
CUI_ID_FRAME_Quest::CUI_ID_FRAME_Quest()
{
	// Member
	m_pID_FRAME_Quest = NULL;
	m_pID_TEXT_QuestInfo = NULL;
	m_pID_TEXT_GuoYun = NULL;
	m_pID_TEXT_BinShu = NULL;
	m_pID_TEXT_GuoTan = NULL;
	m_pID_TEXT_HuLiang = NULL;
	m_pID_BUTTON_GuoYun = NULL;
	m_pID_BUTTON_GuoTan = NULL;
	m_pID_BUTTON_HuLiang = NULL;
	m_pID_BUTTON_BinShu = NULL;

}
// Frame
bool CUI_ID_FRAME_Quest::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_Quest::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_Quest::ID_BUTTON_GuoYunOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Quest )
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

	return true;
}
// Button
bool CUI_ID_FRAME_Quest::ID_BUTTON_GuoTanOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Quest )
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
	return true;
}
// Button
bool CUI_ID_FRAME_Quest::ID_BUTTON_HuLiangOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Quest )
	{
		assert( false && "ui error" );
		return false;
	}

	//给服务器发消息
	if( m_countryTaskVec.size() <= m_nPage * 4 + 2 )
		return false;

	MsgCountryQuestStatusChangeReq msg;
	msg.uchQuestType = m_countryTaskVec[ m_nPage * 4 + 3 ].taskType;
	GettheNetworkInput().SendMsg( &msg );
	return true;
}
// Button
bool CUI_ID_FRAME_Quest::ID_BUTTON_BinShuOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Quest )
	{
		assert( false && "ui error" );
		return false;
	}

	//给服务器发消息
	if( m_countryTaskVec.size() <= m_nPage * 4 + 3 )
		return false;

	MsgCountryQuestStatusChangeReq msg;
	msg.uchQuestType = m_countryTaskVec[ m_nPage * 4 + 2 ].taskType;
	GettheNetworkInput().SendMsg( &msg );

	return true;
}

	// 装载UI
bool CUI_ID_FRAME_Quest::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CountryQuest.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CountryQuest.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Quest::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Quest, s_CUI_ID_FRAME_QuestOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Quest, s_CUI_ID_FRAME_QuestOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Quest, ID_BUTTON_GuoYun, s_CUI_ID_FRAME_QuestID_BUTTON_GuoYunOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Quest, ID_BUTTON_GuoTan, s_CUI_ID_FRAME_QuestID_BUTTON_GuoTanOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Quest, ID_BUTTON_HuLiang, s_CUI_ID_FRAME_QuestID_BUTTON_HuLiangOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Quest, ID_BUTTON_BinShu, s_CUI_ID_FRAME_QuestID_BUTTON_BinShuOnButtonClick );

	m_pID_FRAME_Quest = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Quest );
	m_pID_TEXT_QuestInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_Quest, ID_TEXT_QuestInfo );
	m_pID_TEXT_GuoYun = (ControlText*)theUiManager.FindControl( ID_FRAME_Quest, ID_TEXT_GuoYun );
	m_pID_TEXT_BinShu = (ControlText*)theUiManager.FindControl( ID_FRAME_Quest, ID_TEXT_BinShu );
	m_pID_TEXT_GuoTan = (ControlText*)theUiManager.FindControl( ID_FRAME_Quest, ID_TEXT_GuoTan );
	m_pID_TEXT_HuLiang = (ControlText*)theUiManager.FindControl( ID_FRAME_Quest, ID_TEXT_HuLiang );
	m_pID_BUTTON_GuoYun = (ControlButton*)theUiManager.FindControl( ID_FRAME_Quest, ID_BUTTON_GuoYun );
	m_pID_BUTTON_GuoTan = (ControlButton*)theUiManager.FindControl( ID_FRAME_Quest, ID_BUTTON_GuoTan );
	m_pID_BUTTON_HuLiang = (ControlButton*)theUiManager.FindControl( ID_FRAME_Quest, ID_BUTTON_HuLiang );
	m_pID_BUTTON_BinShu = (ControlButton*)theUiManager.FindControl( ID_FRAME_Quest, ID_BUTTON_BinShu );
	assert( m_pID_FRAME_Quest );
	assert( m_pID_TEXT_QuestInfo );
	assert( m_pID_TEXT_GuoYun );
	assert( m_pID_TEXT_BinShu );
	assert( m_pID_TEXT_GuoTan );
	assert( m_pID_TEXT_HuLiang );
	assert( m_pID_BUTTON_GuoYun );
	assert( m_pID_BUTTON_GuoTan );
	assert( m_pID_BUTTON_HuLiang );
	assert( m_pID_BUTTON_BinShu );
	m_pID_FRAME_Quest->SetFather(s_CUI_ID_FRAME_BaseInfo.GetFrame());
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Quest::_UnLoadUI()
{
	m_pID_FRAME_Quest = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\CountryQuest.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Quest::_IsVisable()
{
	return m_pID_FRAME_Quest->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Quest::_SetVisable( const bool bVisable )
{
	if(bVisable)
		OnInitUIInfo();
	m_pID_FRAME_Quest->SetVisable( bVisable );
}
void CUI_ID_FRAME_Quest::OnInitUIInfo()
{
	//国家任务信息处理
	//任务状态
	// 国务信息
	m_strTaskText = "";
	for( int i = 0; i < QuestType_Max; i++ )
	{
		switch( i )
		{
		case QuestType_King:			// 国运任务
			m_strTaskText += theXmlString.GetString( eText_Country_Task_GuoYun ) + std::string( "      " );
			if( s_CUI_ID_FRAME_BaseInfo.m_taskStatus[ QuestType_King ].uchCount )
				m_strTaskText += theXmlString.GetString( eText_Country_Task_Dbt ) + std::string( "\n" );
			else
				m_strTaskText += theXmlString.GetString( eText_Country_Task_NotDbt ) + std::string( "\n" );
			break;
		case QuestType_General:			// 出国任务
			m_strTaskText += theXmlString.GetString( eText_Country_Task_ChuGuo ) + std::string( "      " );
			if( s_CUI_ID_FRAME_BaseInfo.m_taskStatus[ QuestType_General ].uchCount )
				m_strTaskText += theXmlString.GetString( eText_Country_Task_Dbt ) + std::string( "\n" );
			else
				m_strTaskText += theXmlString.GetString( eText_Country_Task_NotDbt ) + std::string( "\n" );
			break;
		case QuestType_CouncilorLeft:	// 天行任务
			m_strTaskText += theXmlString.GetString( eText_Country_Task_TianXing ) + std::string( "      " );
			if( s_CUI_ID_FRAME_BaseInfo.m_taskStatus[ QuestType_CouncilorLeft ].uchCount )
				m_strTaskText += theXmlString.GetString( eText_Country_Task_Dbt ) + std::string( "\n" );
			else
				m_strTaskText += theXmlString.GetString( eText_Country_Task_NotDbt ) + std::string( "\n" );
			break;
		case QuestType_CouncilorRight:	// 探宝任务
			m_strTaskText += theXmlString.GetString( eText_Country_Task_TanBao ) + std::string( "      " );
			if( s_CUI_ID_FRAME_BaseInfo.m_taskStatus[ QuestType_CouncilorRight ].uchCount )
				m_strTaskText += theXmlString.GetString( eText_Country_Task_Dbt ) + std::string( "\n" );
			else
				m_strTaskText += theXmlString.GetString( eText_Country_Task_NotDbt ) + std::string( "\n" );
			break;
		default:
			break;
		}
	}
	m_pID_TEXT_QuestInfo->SetText( m_strTaskText.c_str() );
	
	UpdatePages();
}
void CUI_ID_FRAME_Quest::InitializeAtEnterWorld()
{
    InitTask();
}
void CUI_ID_FRAME_Quest::InitTask()
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
void CUI_ID_FRAME_Quest::UpdatePages()
{
    if ( !m_pID_FRAME_Quest )
        return;

	// 缺省值
	m_pID_TEXT_GuoYun->SetText( "" );
	m_pID_BUTTON_GuoYun->SetEnable( false );

	m_pID_TEXT_GuoTan->SetText( "" );
	m_pID_BUTTON_GuoTan->SetEnable( false );

	m_pID_TEXT_HuLiang->SetText( "" );
	m_pID_BUTTON_HuLiang->SetEnable( false );

	m_pID_TEXT_BinShu->SetText( "" );
	m_pID_BUTTON_BinShu->SetEnable( false );

	// 任务
	if( m_countryTaskVec.size() > m_nPage * 4 + 3 )
	{
		m_pID_TEXT_BinShu->SetText( m_countryTaskVec[ m_nPage * 4 + 3 ].strDescribe.c_str() );
		// 判定身份
		if( s_CUI_ID_FRAME_BaseInfo.m_nCountryRight & m_countryTaskVec[ m_nPage * 4 + 3 ].requireRight 
			&& s_CUI_ID_FRAME_BaseInfo.m_taskStatus[ QuestType_CouncilorRight ].uchCount ==0
			)
		{

			m_pID_BUTTON_HuLiang->SetEnable( true );
		}
		else
			m_pID_BUTTON_HuLiang->SetEnable( false );
	}
	else
	{
		m_pID_BUTTON_BinShu->SetEnable( false );
	}

	if( m_countryTaskVec.size() > m_nPage * 4 + 2 )
	{
		m_pID_TEXT_HuLiang->SetText( m_countryTaskVec[ m_nPage * 4 + 2 ].strDescribe.c_str() ); 
		// 判定身份
		if( s_CUI_ID_FRAME_BaseInfo.m_nCountryRight & m_countryTaskVec[ m_nPage * 4 + 2 ].requireRight 
			&& s_CUI_ID_FRAME_BaseInfo.m_taskStatus[ QuestType_CouncilorLeft ].uchCount ==0
			)
			m_pID_BUTTON_BinShu->SetEnable( true );
		else
			m_pID_BUTTON_BinShu->SetEnable( false );
	}
	else
	{
		m_pID_BUTTON_HuLiang->SetEnable( false );
	}

	if( m_countryTaskVec.size() > m_nPage * 4 + 1 )
	{
		m_pID_TEXT_GuoTan->SetText( m_countryTaskVec[ m_nPage * 4 + 1 ].strDescribe.c_str() );
		// 判定身份
		if( s_CUI_ID_FRAME_BaseInfo.m_nCountryRight & m_countryTaskVec[ m_nPage * 4 + 1 ].requireRight 
			&& s_CUI_ID_FRAME_BaseInfo.m_taskStatus[ QuestType_General ].uchCount ==0
			)
			m_pID_BUTTON_GuoTan->SetEnable( true );
		else
			m_pID_BUTTON_GuoTan->SetEnable( false ); 
	}
	else
	{
		m_pID_BUTTON_GuoTan->SetEnable( false );
	}

	if( m_countryTaskVec.size() > m_nPage * 4 )
	{
		m_pID_TEXT_GuoYun->SetText( m_countryTaskVec[ m_nPage * 4 ].strDescribe.c_str() ); 
		// 判定身份
		if( s_CUI_ID_FRAME_BaseInfo.m_nCountryRight & m_countryTaskVec[ m_nPage * 4 ].requireRight 
			&& s_CUI_ID_FRAME_BaseInfo.m_taskStatus[ QuestType_King ].uchCount ==0
			)
			m_pID_BUTTON_GuoYun->SetEnable( true );
		else
			m_pID_BUTTON_GuoYun->SetEnable( false );
	}
	else
	{
		m_pID_BUTTON_GuoYun->SetEnable( false );
	}
}
void CUI_ID_FRAME_Quest::GetNewCountryRight( uint32 countryRight )
{
	UpdatePages();
}
void CUI_ID_FRAME_Quest::GetDistributeResult( uint8 result )
{
	switch( result )
	{
	case MsgCountryQuestStatusChangeAck::ECD_Success:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, theXmlString.GetString( eText_Country_Task_Success ) );
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
void CUI_ID_FRAME_Quest::GetCountryTaskBeginInfo( const MsgTellCountryQuestStatus* pMsg )
{
	if( !pMsg )
		return;
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

void CUI_ID_FRAME_Quest::GetCountryTaskEndInfo( uint8 result )
{
	s_CUI_ID_FRAME_BaseInfo.TryToUpdate();
	std::vector<CountryTask>::size_type i = 0;
	for( ; i < m_countryTaskVec.size(); i++ )
	{
		if( m_countryTaskVec[i].taskType == result )
			if( !s_CUI_ID_FRAME_ActivityTrack.DelSpecialActivity( m_countryTaskVec[i].strTaskName ) )
				return;
	}
}
