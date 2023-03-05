/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\CampBattleGuildUnion.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "CampBattleGuildUnion.h"
#include "PlayerRole.h"
#include "CampBattleMessage.h"
#include "NetworkInput.h"
CUI_ID_FRAME_CampBattleGuildUnion s_CUI_ID_FRAME_CampBattleGuildUnion;
MAP_FRAME_RUN( s_CUI_ID_FRAME_CampBattleGuildUnion, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CampBattleGuildUnion, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_CampBattleGuildUnion, ID_LIST_GuildNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_CampBattleGuildUnion, ID_LIST_GuildStrongOnListSelectChange )
CUI_ID_FRAME_CampBattleGuildUnion::CUI_ID_FRAME_CampBattleGuildUnion()
{
	// Member
	m_pID_FRAME_CampBattleGuildUnion = NULL;
	m_pID_TEXT_UnionSum = NULL;
	m_pID_TEXT_BeginTimeStep = NULL;
	m_pID_TEXT_EndTimeStep = NULL;
	m_pID_LIST_GuildName = NULL;
	m_pID_LIST_GuildStrong = NULL;
	m_WorldBattleSum = 0;
}		
// Frame
bool CUI_ID_FRAME_CampBattleGuildUnion::OnFrameRun()
{
	if(IsVisable() && m_WorldBattleSum !=0)
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
bool CUI_ID_FRAME_CampBattleGuildUnion::OnFrameRender()
{
	return true;
}
// List
void CUI_ID_FRAME_CampBattleGuildUnion::ID_LIST_GuildNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_CampBattleGuildUnion::ID_LIST_GuildStrongOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}

// 装载UI
bool CUI_ID_FRAME_CampBattleGuildUnion::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CampBattleGuildUnion.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CampBattleGuildUnion.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_CampBattleGuildUnion::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_CampBattleGuildUnion, s_CUI_ID_FRAME_CampBattleGuildUnionOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_CampBattleGuildUnion, s_CUI_ID_FRAME_CampBattleGuildUnionOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_CampBattleGuildUnion, ID_LIST_GuildName, s_CUI_ID_FRAME_CampBattleGuildUnionID_LIST_GuildNameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_CampBattleGuildUnion, ID_LIST_GuildStrong, s_CUI_ID_FRAME_CampBattleGuildUnionID_LIST_GuildStrongOnListSelectChange );

	m_pID_FRAME_CampBattleGuildUnion = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_CampBattleGuildUnion );
	m_pID_TEXT_UnionSum = (ControlText*)theUiManager.FindControl( ID_FRAME_CampBattleGuildUnion, ID_TEXT_UnionSum );
	m_pID_TEXT_BeginTimeStep = (ControlText*)theUiManager.FindControl( ID_FRAME_CampBattleGuildUnion, ID_TEXT_BeginTimeStep );
	m_pID_TEXT_EndTimeStep = (ControlText*)theUiManager.FindControl( ID_FRAME_CampBattleGuildUnion, ID_TEXT_EndTimeStep );
	m_pID_LIST_GuildName = (ControlList*)theUiManager.FindControl( ID_FRAME_CampBattleGuildUnion, ID_LIST_GuildName );
	m_pID_LIST_GuildStrong = (ControlList*)theUiManager.FindControl( ID_FRAME_CampBattleGuildUnion, ID_LIST_GuildStrong );
	assert( m_pID_FRAME_CampBattleGuildUnion );
	assert( m_pID_TEXT_UnionSum );
	assert( m_pID_TEXT_BeginTimeStep );
	assert( m_pID_TEXT_EndTimeStep );
	assert( m_pID_LIST_GuildName );
	assert( m_pID_LIST_GuildStrong );

	m_pID_FRAME_CampBattleGuildUnion->SetFather(s_CUI_ID_FRAME_CampBattleBaseInfo.GetFrame());
	return true;
}
	// 卸载UI
bool CUI_ID_FRAME_CampBattleGuildUnion::_UnLoadUI()
{
	m_pID_FRAME_CampBattleGuildUnion = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\CampBattleGuildUnion.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_CampBattleGuildUnion::_IsVisable()
{
	return m_pID_FRAME_CampBattleGuildUnion->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_CampBattleGuildUnion::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_CampBattleGuildUnion->SetVisable( bVisable );
}
void CUI_ID_FRAME_CampBattleGuildUnion::OnInit()
{
	//发送命令获取当前轮数
	MsgGetGlobalDBBattleSumReq msg;
	GettheNetworkInput().SendMsg( &msg );
}
void CUI_ID_FRAME_CampBattleGuildUnion::SetGuildUnionSum(int BattleSum)
{
	if(m_WorldBattleSum == BattleSum) return;
	m_WorldBattleSum = BattleSum;
	LoadFileConfig(CAMPGUILDUNIONBATTLE_FILEPATH);
	LoadCampClientInfo(CAMPBATTLECLIENTINFO_FILEPATH);
}
void CUI_ID_FRAME_CampBattleGuildUnion::LoadFileConfig(const char * FilePath)
{
	//加载配置文件到 m_TimeInfo里面去
	//获取当前轮数
	if(m_WorldBattleSum == 0) return;
	//读取配置文件
	if ( FilePath == NULL || FilePath[ 0 ] == 0 )
		return;

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( FilePath, 1 ) )
    	return;

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    	return;

	MeXmlElement* pGuildUnionBattle = pRoot->FirstChildElement( "GuildUnionBattle" );
    if ( pGuildUnionBattle == NULL )
    	return;

	MeXmlElement* pBattleSettings = pGuildUnionBattle->FirstChildElement( "BattleSettings" );
    while ( pBattleSettings != NULL )
    {
		//读取配置
		int BattleSum = 0;
		if ( pBattleSettings->Attribute( "battlesum", &BattleSum ) == NULL )
			return;
		if(BattleSum != m_WorldBattleSum)
		{
			pBattleSettings = pBattleSettings->NextSiblingElement();
			continue;
		}
		 int nValue = 0;

		MeXmlElement* pTimeSettings = pBattleSettings->FirstChildElement( "TimeSettings" );
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
		pBattleSettings = pBattleSettings->NextSiblingElement();
	}
}
void CUI_ID_FRAME_CampBattleGuildUnion::LoadCampClientInfo(const char * FilePath)
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

	MeXmlElement* pBattleSetting = pRoot->FirstChildElement( "CampGuildUnionBattle");
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