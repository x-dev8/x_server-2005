/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\CampBattleWorld.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "CampBattleWorld.h"
#include "PlayerRole.h"
CUI_ID_FRAME_CampBattleWorld s_CUI_ID_FRAME_CampBattleWorld;
MAP_FRAME_RUN( s_CUI_ID_FRAME_CampBattleWorld, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CampBattleWorld, OnFrameRender )
CUI_ID_FRAME_CampBattleWorld::CUI_ID_FRAME_CampBattleWorld()
{
// Member
m_pID_FRAME_CampBattleWorld = NULL;
m_pID_TEXT_WorldCountry = NULL;
m_pID_TEXT_EndTimeStep = NULL;
m_pID_TEXT_BeginTimeStep = NULL;

}
// Frame
bool CUI_ID_FRAME_CampBattleWorld::OnFrameRun()
{
	if(IsVisable())
	{
		//显示阶段 我们更改UI上的值
		std::string beginTime;
		std::string endTime;
		time_t now;
		time(&now);
		int States = m_TimeInfo.GetTimeInfo(beginTime,endTime,now);

		m_pID_TEXT_BeginTimeStep->SetText(beginTime.c_str());
		m_pID_TEXT_EndTimeStep->SetText(endTime.c_str());

		std::string strName;
		m_TimeInfo.GetInfoByCampBattleStates(States,strName);

	}
	return true;
}
bool CUI_ID_FRAME_CampBattleWorld::OnFrameRender()
{
	return true;
}

// 装载UI
bool CUI_ID_FRAME_CampBattleWorld::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CampBattleWorld.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CampBattleWorld.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_CampBattleWorld::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_CampBattleWorld, s_CUI_ID_FRAME_CampBattleWorldOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_CampBattleWorld, s_CUI_ID_FRAME_CampBattleWorldOnFrameRender );

	m_pID_FRAME_CampBattleWorld = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_CampBattleWorld );
	m_pID_TEXT_WorldCountry = (ControlText*)theUiManager.FindControl( ID_FRAME_CampBattleWorld, ID_TEXT_WorldCountry );
	m_pID_TEXT_EndTimeStep = (ControlText*)theUiManager.FindControl( ID_FRAME_CampBattleWorld, ID_TEXT_EndTimeStep );
	m_pID_TEXT_BeginTimeStep = (ControlText*)theUiManager.FindControl( ID_FRAME_CampBattleWorld, ID_TEXT_BeginTimeStep );
	assert( m_pID_FRAME_CampBattleWorld );
	assert( m_pID_TEXT_WorldCountry );
	assert( m_pID_TEXT_EndTimeStep );
	assert( m_pID_TEXT_BeginTimeStep );

	m_pID_FRAME_CampBattleWorld->SetFather(s_CUI_ID_FRAME_CampBattleBaseInfo.GetFrame());
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_CampBattleWorld::_UnLoadUI()
{
	m_pID_FRAME_CampBattleWorld = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\CampBattleWorld.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_CampBattleWorld::_IsVisable()
{
	return m_pID_FRAME_CampBattleWorld->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_CampBattleWorld::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_CampBattleWorld->SetVisable( bVisable );
}
void CUI_ID_FRAME_CampBattleWorld::OnInit()
{
	if(m_TimeInfo.IsEmpty()) 
	{
		//打开的时候未加载 就加载配置文件
		LoadFileConfig(CAMPWORLDBATTLE_FILEPATH);
		LoadCampClientInfo(CAMPBATTLECLIENTINFO_FILEPATH);
	}
}
void CUI_ID_FRAME_CampBattleWorld::LoadFileConfig(const char * FilePath)
{
	//加载配置文件到 m_TimeInfo里面去
	MeXmlDocument mKwameXmlDoc;
	if (!mKwameXmlDoc.LoadFile(FilePath)) return;
	MeXmlElement* pRoot = mKwameXmlDoc.FirstChildElement("WorldBattle");
	if(pRoot != NULL)
	{
		//读取野外战场的基本配置信息
		//1. 准备时间 开始时间 结束时间 3个阶段 进行读取
		MeXmlElement* pTimeSettings = pRoot->FirstChildElement( "TimeSettings" );
		if ( pTimeSettings == NULL )
			return;
		MeXmlElement* pTime = pTimeSettings->FirstChildElement( "TimeSetting" );
		while( pTime != NULL )
		{
			TimeSetting xSetting;
			MeXmlElement* pSignUp = pTime->FirstChildElement( "PrepareTime" );
			if ( pSignUp == NULL )
				return;

			int nValue = 0;	
			if ( pSignUp->Attribute( "DayOfWeek", &nValue ) == NULL )
				return;
			xSetting.SetDayOfWeek( nValue );

			if ( pSignUp->Attribute( "Hour", &nValue ) == NULL )
				return;
			xSetting.SetHour( nValue );

			if ( pSignUp->Attribute( "Minute", &nValue ) == NULL )
				return;
			xSetting.SetMinute( nValue );

			if ( pSignUp->Attribute( "KeepTime", &nValue ) == NULL )
				return;
			xSetting.SetKeepTime( nValue );
			m_TimeInfo.vecPrepareTimeSetting.push_back( xSetting );

			MeXmlElement* pPrepare = pTime->FirstChildElement( "FightTime" );
			if ( pPrepare == NULL )
				return;

			if ( pPrepare->Attribute( "DayOfWeek", &nValue ) == NULL )
				return;
			xSetting.SetDayOfWeek( nValue );

			if ( pPrepare->Attribute( "Hour", &nValue ) == NULL )
				return;
			xSetting.SetHour( nValue );

			if ( pPrepare->Attribute( "Minute", &nValue ) == NULL )
				return;
			xSetting.SetMinute( nValue );

			if ( pPrepare->Attribute( "KeepTime", &nValue ) == NULL )
				return;
			xSetting.SetKeepTime( nValue );
			m_TimeInfo.vecFightTimeSetting.push_back( xSetting );

			MeXmlElement* pEnter = pTime->FirstChildElement( "EndTime" );
			if ( pEnter == NULL )
				return;

			if ( pEnter->Attribute( "DayOfWeek", &nValue ) == NULL )
				return;
			xSetting.SetDayOfWeek( nValue );

			if ( pEnter->Attribute( "Hour", &nValue ) == NULL )
				return;
			xSetting.SetHour( nValue );

			if ( pEnter->Attribute( "Minute", &nValue ) == NULL )
				return;
			xSetting.SetMinute( nValue );

			if ( pEnter->Attribute( "KeepTime", &nValue ) == NULL )
				return;
			xSetting.SetKeepTime( nValue );
			m_TimeInfo.vecEndTimeSetting.push_back( xSetting );

			pTime = pTime->NextSiblingElement();
		}
	}
}
void CUI_ID_FRAME_CampBattleWorld::LoadCampClientInfo(const char * FilePath)
{
	//读取配置文件 客户端专用
	if ( FilePath == NULL || FilePath[ 0 ] == 0 )
		return;

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( FilePath, 1 ) )
		return;

	MeXmlElement* pRoot = xMeXml.FirstChildElement( "Camp" );
    if ( pRoot == NULL )
		return;

	MeXmlElement* pBattleSetting = pRoot->FirstChildElement( "CampWorldBattle");
	if ( pBattleSetting == NULL )
		return;

	MeXmlElement* pInfo = pBattleSetting->FirstChildElement( "Info");
	while(pInfo)
	{
		CampBattleInfo info;
		if ( pInfo->Attribute( "States", &info.States) == NULL )
			return;
		
		if ( pInfo->Attribute( "StrID", &info.StrID) == NULL )
			return;

		if ( pInfo->Attribute( "Sec", &info.Sec) == NULL )
			return;

		m_CampInfo.BattleInfo.insert(map<int,CampBattleInfo>::value_type(info.States,info));
		pInfo = pInfo->NextSiblingElement();
	}
	m_CampInfo.m_Setting = &m_TimeInfo;
}