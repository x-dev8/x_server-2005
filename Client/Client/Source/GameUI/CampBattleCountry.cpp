/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\CampBattleCountry.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "CampBattleCountry.h"
#include "PlayerRole.h"
CUI_ID_FRAME_CampBattleCountry s_CUI_ID_FRAME_CampBattleCountry;
MAP_FRAME_RUN( s_CUI_ID_FRAME_CampBattleCountry, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CampBattleCountry, OnFrameRender )
CUI_ID_FRAME_CampBattleCountry::CUI_ID_FRAME_CampBattleCountry()
{
	// Member
	m_pID_FRAME_CampBattleCountry = NULL;
	m_pID_TEXT_GuildAName = NULL;
	m_pID_TEXT_GuildBName = NULL;
	m_pID_TEXT_GuildBStrong = NULL;
	m_pID_TEXT_GuildAStrong = NULL;
	m_pID_TEXT_BeginTimeStep = NULL;
	m_pID_TEXT_EndTimeStep = NULL;
}
// Frame
bool CUI_ID_FRAME_CampBattleCountry::OnFrameRun()
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
		//根据状态设置当前的Ui提示信息的标签
		std::string strName;
		m_TimeInfo.GetInfoByCampBattleStates(States,strName);
	}
	return true;
}
bool CUI_ID_FRAME_CampBattleCountry::OnFrameRender()
{
	return true;
}

// 装载UI
bool CUI_ID_FRAME_CampBattleCountry::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CampBattleCountry.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CampBattleCountry.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_CampBattleCountry::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_CampBattleCountry, s_CUI_ID_FRAME_CampBattleCountryOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_CampBattleCountry, s_CUI_ID_FRAME_CampBattleCountryOnFrameRender );

	m_pID_FRAME_CampBattleCountry = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_CampBattleCountry );
	m_pID_TEXT_GuildAName = (ControlText*)theUiManager.FindControl( ID_FRAME_CampBattleCountry, ID_TEXT_GuildAName );
	m_pID_TEXT_GuildBName = (ControlText*)theUiManager.FindControl( ID_FRAME_CampBattleCountry, ID_TEXT_GuildBName );
	m_pID_TEXT_GuildBStrong = (ControlText*)theUiManager.FindControl( ID_FRAME_CampBattleCountry, ID_TEXT_GuildBStrong );
	m_pID_TEXT_GuildAStrong = (ControlText*)theUiManager.FindControl( ID_FRAME_CampBattleCountry, ID_TEXT_GuildAStrong );
	m_pID_TEXT_BeginTimeStep = (ControlText*)theUiManager.FindControl( ID_FRAME_CampBattleCountry, ID_TEXT_BeginTimeStep );
	m_pID_TEXT_EndTimeStep = (ControlText*)theUiManager.FindControl( ID_FRAME_CampBattleCountry, ID_TEXT_EndTimeStep );
	assert( m_pID_FRAME_CampBattleCountry );
	assert( m_pID_TEXT_GuildAName );
	assert( m_pID_TEXT_GuildBName );
	assert( m_pID_TEXT_GuildBStrong );
	assert( m_pID_TEXT_GuildAStrong );
	assert( m_pID_TEXT_BeginTimeStep );
	assert( m_pID_TEXT_EndTimeStep );

	m_pID_FRAME_CampBattleCountry->SetFather(s_CUI_ID_FRAME_CampBattleBaseInfo.GetFrame());
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_CampBattleCountry::_UnLoadUI()
{
	m_pID_FRAME_CampBattleCountry = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\CampBattleCountry.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_CampBattleCountry::_IsVisable()
{
	return m_pID_FRAME_CampBattleCountry->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_CampBattleCountry::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_CampBattleCountry->SetVisable( bVisable );
}
void CUI_ID_FRAME_CampBattleCountry::OnInit()
{
	if(m_TimeInfo.IsEmpty()) 
	{
		//打开的时候未加载 就加载配置文件
		LoadFileConfig(CAMPKINGBATTLE_FILEPATH);
		LoadCampClientInfo(CAMPBATTLECLIENTINFO_FILEPATH);
	}
}
void CUI_ID_FRAME_CampBattleCountry::LoadCampClientInfo(const char * FilePath)
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

	MeXmlElement* pBattleSetting = pRoot->FirstChildElement( "CampCountryBattle");
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
void CUI_ID_FRAME_CampBattleCountry::LoadFileConfig(const char * FilePath)
{
	//加载配置文件到 m_TimeInfo里面去 加载国王战的配置文件 
	if ( FilePath == NULL || FilePath[ 0 ] == 0 )
		return;

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( FilePath, 1 ) )
		return;

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
		return;

    MeXmlElement* pBattleSetting = pRoot->FirstChildElement( "BattleSettings" );
	while (pBattleSetting)
	{
		int nValue = 0;
		if ( pBattleSetting->Attribute( "CountryId", &nValue ) == NULL )
			return;

		if(nValue != thePlayerRole.GetCountry())
		{
			pBattleSetting = pBattleSetting->NextSiblingElement("BattleSettings");
			continue;
		}
		
		//获取自己国家的国王战的时间设置
		nValue = 0;
		
		MeXmlElement* pTimeSettings = pBattleSetting->FirstChildElement( "TimeSettings" );
		if ( pTimeSettings == NULL )
			return;

		MeXmlElement* pTime = pTimeSettings->FirstChildElement( "TimeSetting" );
		while( pTime != NULL )
		{
			TimeSetting xSetting;

			// 报名时间
			MeXmlElement* pSignUp = pTime->FirstChildElement( "SignUpTime" );
			if ( pSignUp == NULL )
				return;

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

			m_TimeInfo.vecSignUpTimeSetting.push_back( xSetting );

			// 准备时间
			MeXmlElement* pPrepare = pTime->FirstChildElement( "PrepareTime" );
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

			m_TimeInfo.vecPrepareTimeSetting.push_back( xSetting );

			// 进入时间
			MeXmlElement* pEnter = pTime->FirstChildElement( "EnterTime" );
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

			m_TimeInfo.vecEnterTimeSetting.push_back( xSetting );

			// 战斗时间
			MeXmlElement* pFight = pTime->FirstChildElement( "FightTime" );
			if ( pFight == NULL )
				return;

			if ( pFight->Attribute( "DayOfWeek", &nValue ) == NULL )
				return;
			xSetting.SetDayOfWeek( nValue );

			if ( pFight->Attribute( "Hour", &nValue ) == NULL )
				return;
			xSetting.SetHour( nValue );

			if ( pFight->Attribute( "Minute", &nValue ) == NULL )
				return;
			xSetting.SetMinute( nValue );

			if ( pFight->Attribute( "KeepTime", &nValue ) == NULL )
				return;
			xSetting.SetKeepTime( nValue );

			m_TimeInfo.vecFightTimeSetting.push_back( xSetting );

			// 结束时间
			MeXmlElement* pEnd = pTime->FirstChildElement( "EndTime" );
			if ( pEnd == NULL )
				return;

			if ( pEnd->Attribute( "DayOfWeek", &nValue ) == NULL )
				return;
			xSetting.SetDayOfWeek( nValue );

			if ( pEnd->Attribute( "Hour", &nValue ) == NULL )
				return;
			xSetting.SetHour( nValue );

			if ( pEnd->Attribute( "Minute", &nValue ) == NULL )
				return;
			xSetting.SetMinute( nValue );

			if ( pEnd->Attribute( "KeepTime", &nValue ) == NULL )
				return;
			xSetting.SetKeepTime( nValue );

			m_TimeInfo.vecEndTimeSetting.push_back( xSetting );

			pTime = pTime->NextSiblingElement();
		}
		pBattleSetting = pBattleSetting->NextSiblingElement();
	}
}
