/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\CampBattleGuild.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "CampBattleGuild.h"
#include "PlayerRole.h"
CUI_ID_FRAME_CampBattleGuild s_CUI_ID_FRAME_CampBattleGuild;
MAP_FRAME_RUN( s_CUI_ID_FRAME_CampBattleGuild, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CampBattleGuild, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_CampBattleGuild, ID_LIST_GuildNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_CampBattleGuild, ID_LIST_GuildStrongOnListSelectChange )
CUI_ID_FRAME_CampBattleGuild::CUI_ID_FRAME_CampBattleGuild()
{
	// Member
	m_pID_FRAME_CampBattleGuild = NULL;
	m_pID_TEXT_BeginTimeStep = NULL;
	m_pID_TEXT_EndTimeStep = NULL;
	m_pID_LIST_GuildName = NULL;
	m_pID_LIST_GuildStrong = NULL;

}
// Frame
bool CUI_ID_FRAME_CampBattleGuild::OnFrameRun()
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
bool CUI_ID_FRAME_CampBattleGuild::OnFrameRender()
{
	return true;
}
// List
void CUI_ID_FRAME_CampBattleGuild::ID_LIST_GuildNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_CampBattleGuild::ID_LIST_GuildStrongOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// 装载UI
bool CUI_ID_FRAME_CampBattleGuild::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CampBattleGuild.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CampBattleGuild.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_CampBattleGuild::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_CampBattleGuild, s_CUI_ID_FRAME_CampBattleGuildOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_CampBattleGuild, s_CUI_ID_FRAME_CampBattleGuildOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_CampBattleGuild, ID_LIST_GuildName, s_CUI_ID_FRAME_CampBattleGuildID_LIST_GuildNameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_CampBattleGuild, ID_LIST_GuildStrong, s_CUI_ID_FRAME_CampBattleGuildID_LIST_GuildStrongOnListSelectChange );

	m_pID_FRAME_CampBattleGuild = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_CampBattleGuild );
	m_pID_TEXT_BeginTimeStep = (ControlText*)theUiManager.FindControl( ID_FRAME_CampBattleGuild, ID_TEXT_BeginTimeStep );
	m_pID_TEXT_EndTimeStep = (ControlText*)theUiManager.FindControl( ID_FRAME_CampBattleGuild, ID_TEXT_EndTimeStep );
	m_pID_LIST_GuildName = (ControlList*)theUiManager.FindControl( ID_FRAME_CampBattleGuild, ID_LIST_GuildName );
	m_pID_LIST_GuildStrong = (ControlList*)theUiManager.FindControl( ID_FRAME_CampBattleGuild, ID_LIST_GuildStrong );
	assert( m_pID_FRAME_CampBattleGuild );
	assert( m_pID_TEXT_BeginTimeStep );
	assert( m_pID_TEXT_EndTimeStep );
	assert( m_pID_LIST_GuildName );
	assert( m_pID_LIST_GuildStrong );

	m_pID_FRAME_CampBattleGuild->SetFather(s_CUI_ID_FRAME_CampBattleBaseInfo.GetFrame());
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_CampBattleGuild::_UnLoadUI()
{
	m_pID_FRAME_CampBattleGuild = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\CampBattleGuild.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_CampBattleGuild::_IsVisable()
{
	return m_pID_FRAME_CampBattleGuild->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_CampBattleGuild::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_CampBattleGuild->SetVisable( bVisable );
}
void CUI_ID_FRAME_CampBattleGuild::OnInit()
{
	if(m_TimeInfo.IsEmpty()) 
	{
		//打开的时候未加载 就加载配置文件
		LoadFileConfig(CAMPGUILDBATTLE_FILEPATH);
		LoadCampClientInfo(CAMPBATTLECLIENTINFO_FILEPATH);
	}
}
void CUI_ID_FRAME_CampBattleGuild::LoadFileConfig(const char * FilePath)
{
	//加载配置文件到 m_TimeInfo里面去
	//读取公会战的配置
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
void CUI_ID_FRAME_CampBattleGuild::LoadCampClientInfo(const char * FilePath)
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

	MeXmlElement* pBattleSetting = pRoot->FirstChildElement( "CampGuildBattle");
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