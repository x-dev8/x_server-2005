/********************************************************************
	Created by UIEditor.exe
	FileName: D:\FullBag(13.10.181)\Data\Ui\AddGuildGeneralBattle.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "AddGuildGeneralBattle.h"
#include "PlayerRole.h"
#include "NetworkInput.h"
#include "Common.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "ScreenInfoManager.h"
#include "Create.h"
#include "GameBattleDefine.h"
#include "GameBattleMessage.h"
#include "TimeEx.h"
#include "GuildBaseInfo.h"

static const int MAX_ADDGUILDGENETALBATTLE_MAXPAGE = 7;

CUI_ID_FRAME_AddGuildGeneralBattle s_CUI_ID_FRAME_AddGuildGeneralBattle;
MAP_FRAME_RUN( s_CUI_ID_FRAME_AddGuildGeneralBattle, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_AddGuildGeneralBattle, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_EDIT_SelectNameOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_BUTTON_SelectOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_BUTTON_BackOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_BUTTON_NextOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_EDIT_InfoOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_EDIT_GuildMoneyJinOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_EDIT_GuildMoneyYinOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_EDIT_GuildMoneyTonOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_BUTTON_AddOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_BUTTON_CLOSEOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_EDIT_GuildMissionOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_EDIT_MoneyJinOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_EDIT_MoneyYinOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_EDIT_MoneyTonOnEditEnter )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_COMBOBOX_BeginTimeYearOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_COMBOBOX_BeginTimeMonthOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_COMBOBOX_BeginTimeDayOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_COMBOBOX_BeginTimeHourOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_COMBOBOX_BeginTimeMinOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_COMBOBOX_BeginTimeSecOnComboBoxChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_LIST_GuildNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_LIST_GuildPlayerSumOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_LIST_GuildLevelOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_LIST_GuildMasterNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_AddGuildGeneralBattle, ID_LIST_AllOnListSelectChange )
bool SortByGuildGeneralLevel(CGuildInfo* s1, CGuildInfo* s2)
{
	return s1->GetLevel() > s2->GetLevel();
}

CUI_ID_FRAME_AddGuildGeneralBattle::CUI_ID_FRAME_AddGuildGeneralBattle()
{
	// Member
	m_pID_FRAME_AddGuildGeneralBattle = NULL;
	m_pID_EDIT_SelectName = NULL;
	m_pID_BUTTON_Select = NULL;
	m_pID_TEXT_PageInfo = NULL;
	m_pID_BUTTON_Back = NULL;
	m_pID_BUTTON_Next = NULL;
	m_pID_EDIT_Info = NULL;
	m_pID_EDIT_GuildMoneyJin = NULL;
	m_pID_EDIT_GuildMoneyYin = NULL;
	m_pID_EDIT_GuildMoneyTon = NULL;
	m_pID_BUTTON_Add = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_EDIT_GuildMission = NULL;
	m_pID_EDIT_MoneyJin = NULL;
	m_pID_EDIT_MoneyYin = NULL;
	m_pID_EDIT_MoneyTon = NULL;
	m_pID_COMBOBOX_BeginTimeYear = NULL;
	m_pID_COMBOBOX_BeginTimeMonth = NULL;
	m_pID_COMBOBOX_BeginTimeDay = NULL;
	m_pID_COMBOBOX_BeginTimeHour = NULL;
	m_pID_COMBOBOX_BeginTimeMin = NULL;
	m_pID_COMBOBOX_BeginTimeSec = NULL;
	m_pID_LIST_GuildName=NULL;
	m_pID_LIST_GuildPlayerSum=NULL;
	m_pID_LIST_GuildLevel=NULL;
	m_pID_LIST_GuildMasterName=NULL;
	m_pID_LIST_All = NULL;
	
}
// Frame
bool CUI_ID_FRAME_AddGuildGeneralBattle::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_AddGuildGeneralBattle::OnFrameRender()
{
	UpdateGameGeneralBattleStepTime();
	return true;
}
// Edit
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_EDIT_SelectNameOnEditEnter( ControlObject* pSender, const char* szData )
{
}
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_LIST_GuildNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{

}
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_LIST_GuildPlayerSumOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{

}
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_LIST_GuildLevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{

}
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_LIST_GuildMasterNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{

}
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_LIST_AllOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// Button
bool CUI_ID_FRAME_AddGuildGeneralBattle::ID_BUTTON_SelectOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_AddGuildGeneralBattle )
		return false;
	std::string words = m_pID_EDIT_SelectName->GetText();
	if (!words.empty())
	{
		m_vctGuild.clear();
		if(theHeroGame.GetPlayerMgr()->GetMe())
		{
			int nAllGuild = thePlayerRole.GetGuildNum();
			for (int i = 0; i < nAllGuild; ++i)
			{
				if (!thePlayerRole.GetGuild(i) || thePlayerRole.GetGangMgr()->GetGuildID() == thePlayerRole.GetGuild(i)->GetID())
					continue;
				std::string GuildName = thePlayerRole.GetGuild(i)->GetName();
				size_t index = GuildName.find(words.c_str());
				if (index != std::string.npos)
				{
					m_vctGuild.push_back(thePlayerRole.GetGuild(i));
				}
			}
			std::sort(m_vctGuild.begin(), m_vctGuild.end(), SortByGuildGeneralLevel);
		}
		//数据设置完毕后
		ShowGuildInfoByPage();//显示数据
	}
	else
		OnInit();
	return true;
}
void CUI_ID_FRAME_AddGuildGeneralBattle::OnUpdateUiInfo()
{
	//更新UI上的当前数据 主要是公会的数据
	std::string words = m_pID_EDIT_SelectName->GetText();
	if (!words.empty())
	{
		m_vctGuild.clear();
		if(theHeroGame.GetPlayerMgr()->GetMe())
		{
			int nAllGuild = thePlayerRole.GetGuildNum();
			for (int i = 0; i < nAllGuild; ++i)
			{
				if (!thePlayerRole.GetGuild(i)  || thePlayerRole.GetGangMgr()->GetGuildID() == thePlayerRole.GetGuild(i)->GetID())
					continue;
				std::string GuildName = thePlayerRole.GetGuild(i)->GetName();
				size_t index = GuildName.find(words.c_str());
				if (index != std::string.npos)
				{
					m_vctGuild.push_back(thePlayerRole.GetGuild(i));
				}
			}
			std::sort(m_vctGuild.begin(), m_vctGuild.end(), SortByGuildGeneralLevel);
		}
	}
	ShowGuildInfoByPage();//显示数据
}
// Button
bool CUI_ID_FRAME_AddGuildGeneralBattle::ID_BUTTON_BackOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_AddGuildGeneralBattle)
		return false;
	int Page = m_NowPage - 1;
	ShowGuildInfoByPage(Page);
	return true;
}
// Button
bool CUI_ID_FRAME_AddGuildGeneralBattle::ID_BUTTON_NextOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_AddGuildGeneralBattle)
		return false;
	int Page = m_NowPage + 1;
	ShowGuildInfoByPage(Page);
	return true;
}
// Edit
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_EDIT_InfoOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Edit
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_EDIT_GuildMoneyJinOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Edit
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_EDIT_GuildMoneyYinOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Edit
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_EDIT_GuildMoneyTonOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Button
bool CUI_ID_FRAME_AddGuildGeneralBattle::ID_BUTTON_AddOnButtonClick( ControlObject* pSender )
{
	//将公会约战的约战信息发送出去
	if(!thePlayerRole.GetGangMgr())
	{
		//提示无公会
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildGeneral_NonGuild));
		return true;
	}
	if(!IfCanAddGameGeneralBattleByTime())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GameGeneralBattle_AddTimeError));
		return true;
	}
	MsgCampBattleNewDataReq msg;
	GameBattleDefine::GuildCampBattle add;
	//1.组织好时间
	time_t nowtime;
	time(&nowtime);
	nowtime +=theHeroGame.GetServerAndLocalOffsetTime();

	struct tm sysNowTime(*localtime(&nowtime));
	int Year = m_pID_COMBOBOX_BeginTimeYear->GetCurSelIndex()==0?sysNowTime.tm_year+1900:(sysNowTime.tm_year+1901);
	int Month = 	m_pID_COMBOBOX_BeginTimeMonth->GetCurSelIndex()+1;
	int Day =m_pID_COMBOBOX_BeginTimeDay->GetCurSelIndex()+1;
	int Hour =	m_pID_COMBOBOX_BeginTimeHour->GetCurSelIndex();
	int Min =m_pID_COMBOBOX_BeginTimeMin->GetCurSelIndex();
	int Sec =	m_pID_COMBOBOX_BeginTimeSec->GetCurSelIndex();
	TimeEx timeLog(Year,Month,Day ,Hour,Min,Sec);
	add.BeginTime = timeLog.GetTime();
	/*if(add.BeginTime < nowtime + GameBattleDefine::WaitBattleTime)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildGeneral_TimeError));
		return true;
	}*/
	add.ID = 0;
	add.SrcGuildID = thePlayerRole.GetGangMgr()->GetGuildID();
	add.GuildMissionSum = atoi(m_pID_EDIT_GuildMission->GetText());
	unsigned int Jin = atoi(m_pID_EDIT_GuildMoneyJin->GetText());
	unsigned int Yin = atoi(m_pID_EDIT_GuildMoneyYin->GetText());
	unsigned int Ton = atoi(m_pID_EDIT_GuildMoneyTon->GetText());
	add.GuildMoneySum =  thePlayerRole.GetMoneyFromGSC(Jin,Yin,Ton);
	Jin = atoi(m_pID_EDIT_MoneyJin->GetText());
	Yin = atoi(m_pID_EDIT_MoneyYin->GetText());
	Ton = atoi(m_pID_EDIT_MoneyTon->GetText());
	add.MoneySum =  thePlayerRole.GetMoneyFromGSC(Jin,Yin,Ton);
	//目标ID
	add.DestGuildID = 0;
	int select_index = m_pID_LIST_All->GetCurSelIndex();
	if(select_index < 0)
	{
		//提示无公会
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildGeneral_TargetGuildNon));
		return true;
	}
	ControlList::S_List* pItem =m_pID_LIST_GuildName->GetListItem(select_index);
	if(pItem) 
	{
		char * GuildName = pItem->m_szText;
		std::vector<CGuildInfo*>::iterator Iter = m_vctGuild.begin();
		for(;Iter != m_vctGuild.end();++Iter)
		{
			if(_strcmpi((*Iter)->GetName(),GuildName) == 0)
			{
				add.DestGuildID = (*Iter)->GetID();
				break;
			}
		}
	}
	msg.add = add;
	strcpy_s(msg.info,sizeof(msg.info)-1,m_pID_EDIT_Info->GetText());
	//对目前的条件进行过滤
	if(add.DestGuildID == 0)
	{
		//提示为选择出战的公会
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildGeneral_TargetGuildNon));
		return true;
	}
	else if(add.GuildMissionSum * 20 > thePlayerRole.GetGangMgr()->GetGuildMission())
	{
		//公会使命点超过
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildGeneral_MissionError));
		return true;
	}
	else if(add.GuildMoneySum * 20 > thePlayerRole.GetGangMgr()->GetGuildMoney())
	{
		//公会资金超过
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildGeneral_GuildMoneyError));
		return true;
	}
	else if(!thePlayerRole.PackHasEnoughMoney(add.MoneySum))
	{
		//金钱不足
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildGeneral_MoneyError));
		return true;
	}
	else if(thePlayerRole.GetGangMgr()->GetGuildMasterID() != thePlayerRole.GetDBID())
	{
		//不是会长
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildGeneral_NotMaster));
		return true;
	}
	else if(add.GuildMoneySum == 0 && add.GuildMissionSum ==0 && add.MoneySum == 0)
	{
		//不可以全部为0
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildGeneral_RewardError));
		return true;
	}
	else
	{
		GettheNetworkInput().SendMsg(&msg);
		OnInit();
		return true;
	}
	return true;
}
// Button
bool CUI_ID_FRAME_AddGuildGeneralBattle::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Edit
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_EDIT_GuildMissionOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Edit
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_EDIT_MoneyJinOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Edit
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_EDIT_MoneyYinOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Edit
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_EDIT_MoneyTonOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// ComboBox
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_COMBOBOX_BeginTimeYearOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	m_pID_COMBOBOX_BeginTimeDay->Clear();
	time_t nowtime;
	time(&nowtime);
	nowtime +=theHeroGame.GetServerAndLocalOffsetTime();
	struct tm sysNowTime(*localtime(&nowtime));	
	int Year = m_pID_COMBOBOX_BeginTimeYear->GetCurSelIndex()==0?sysNowTime.tm_year+1900:(sysNowTime.tm_year+1901);
	int Month = m_pID_COMBOBOX_BeginTimeMonth->GetCurSelIndex() +1;
	int MonthSum = 0;
	switch(Month)
	{
	case 2:
		MonthSum = (((Year%4==0&&Year%100!=0)||Year%400==0)?29:28);
		break;
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		MonthSum = 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		MonthSum =30;
		break;
	}
	ControlList::S_List	pItem;
	for(int i =1;i<=MonthSum;++i)
	{
		char In[8]={0};
		itoa(i,In,10);
		pItem.clear();
		pItem.SetData(In);
		m_pID_COMBOBOX_BeginTimeDay->AddItem(&pItem);
	}
}
// ComboBox
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_COMBOBOX_BeginTimeMonthOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	//当选择月的时候 我们设置当前月的天数
	m_pID_COMBOBOX_BeginTimeDay->Clear();
	time_t nowtime;
	time(&nowtime);
	nowtime +=theHeroGame.GetServerAndLocalOffsetTime();
	struct tm sysNowTime(*localtime(&nowtime));	
	int Year = m_pID_COMBOBOX_BeginTimeYear->GetCurSelIndex()==0?sysNowTime.tm_year+1900:(sysNowTime.tm_year+1901);
	int Month = m_pID_COMBOBOX_BeginTimeMonth->GetCurSelIndex() +1;
	int MonthSum = 0;
	switch(Month)
	{
	case 2:
		MonthSum = (((Year%4==0&&Year%100!=0)||Year%400==0)?29:28);
		break;
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		MonthSum = 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		MonthSum =30;
		break;
	}
	ControlList::S_List	pItem;
	for(int i =1;i<=MonthSum;++i)
	{
		char In[8]={0};
		itoa(i,In,10);
		pItem.clear();
		pItem.SetData(In);
		m_pID_COMBOBOX_BeginTimeDay->AddItem(&pItem);
	}
}
// ComboBox
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_COMBOBOX_BeginTimeDayOnComboBoxChange( ControlObject* pSender, const char* szData )
{
}
// ComboBox
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_COMBOBOX_BeginTimeHourOnComboBoxChange( ControlObject* pSender, const char* szData )
{
}
// ComboBox
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_COMBOBOX_BeginTimeMinOnComboBoxChange( ControlObject* pSender, const char* szData )
{
}
// ComboBox
void CUI_ID_FRAME_AddGuildGeneralBattle::ID_COMBOBOX_BeginTimeSecOnComboBoxChange( ControlObject* pSender, const char* szData )
{
}

// 装载UI
bool CUI_ID_FRAME_AddGuildGeneralBattle::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\AddGuildGeneralBattle.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\AddGuildGeneralBattle.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_AddGuildGeneralBattle::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_AddGuildGeneralBattle, s_CUI_ID_FRAME_AddGuildGeneralBattleOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_AddGuildGeneralBattle, s_CUI_ID_FRAME_AddGuildGeneralBattleOnFrameRender );
	theUiManager.OnEditEnter( ID_FRAME_AddGuildGeneralBattle, ID_EDIT_SelectName, s_CUI_ID_FRAME_AddGuildGeneralBattleID_EDIT_SelectNameOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_AddGuildGeneralBattle, ID_BUTTON_Select, s_CUI_ID_FRAME_AddGuildGeneralBattleID_BUTTON_SelectOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_AddGuildGeneralBattle, ID_BUTTON_Back, s_CUI_ID_FRAME_AddGuildGeneralBattleID_BUTTON_BackOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_AddGuildGeneralBattle, ID_BUTTON_Next, s_CUI_ID_FRAME_AddGuildGeneralBattleID_BUTTON_NextOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_AddGuildGeneralBattle, ID_EDIT_Info, s_CUI_ID_FRAME_AddGuildGeneralBattleID_EDIT_InfoOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_AddGuildGeneralBattle, ID_EDIT_GuildMoneyJin, s_CUI_ID_FRAME_AddGuildGeneralBattleID_EDIT_GuildMoneyJinOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_AddGuildGeneralBattle, ID_EDIT_GuildMoneyYin, s_CUI_ID_FRAME_AddGuildGeneralBattleID_EDIT_GuildMoneyYinOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_AddGuildGeneralBattle, ID_EDIT_GuildMoneyTon, s_CUI_ID_FRAME_AddGuildGeneralBattleID_EDIT_GuildMoneyTonOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_AddGuildGeneralBattle, ID_BUTTON_Add, s_CUI_ID_FRAME_AddGuildGeneralBattleID_BUTTON_AddOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_AddGuildGeneralBattle, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_AddGuildGeneralBattleID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_AddGuildGeneralBattle, ID_EDIT_GuildMission, s_CUI_ID_FRAME_AddGuildGeneralBattleID_EDIT_GuildMissionOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_AddGuildGeneralBattle, ID_EDIT_MoneyJin, s_CUI_ID_FRAME_AddGuildGeneralBattleID_EDIT_MoneyJinOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_AddGuildGeneralBattle, ID_EDIT_MoneyYin, s_CUI_ID_FRAME_AddGuildGeneralBattleID_EDIT_MoneyYinOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_AddGuildGeneralBattle, ID_EDIT_MoneyTon, s_CUI_ID_FRAME_AddGuildGeneralBattleID_EDIT_MoneyTonOnEditEnter );
	theUiManager.OnComboBoxChange( ID_FRAME_AddGuildGeneralBattle, ID_COMBOBOX_BeginTimeYear, s_CUI_ID_FRAME_AddGuildGeneralBattleID_COMBOBOX_BeginTimeYearOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_AddGuildGeneralBattle, ID_COMBOBOX_BeginTimeMonth, s_CUI_ID_FRAME_AddGuildGeneralBattleID_COMBOBOX_BeginTimeMonthOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_AddGuildGeneralBattle, ID_COMBOBOX_BeginTimeDay, s_CUI_ID_FRAME_AddGuildGeneralBattleID_COMBOBOX_BeginTimeDayOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_AddGuildGeneralBattle, ID_COMBOBOX_BeginTimeHour, s_CUI_ID_FRAME_AddGuildGeneralBattleID_COMBOBOX_BeginTimeHourOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_AddGuildGeneralBattle, ID_COMBOBOX_BeginTimeMin, s_CUI_ID_FRAME_AddGuildGeneralBattleID_COMBOBOX_BeginTimeMinOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_AddGuildGeneralBattle, ID_COMBOBOX_BeginTimeSec, s_CUI_ID_FRAME_AddGuildGeneralBattleID_COMBOBOX_BeginTimeSecOnComboBoxChange );
	theUiManager.OnListSelectChange(ID_FRAME_AddGuildGeneralBattle,ID_LIST_GuildName,s_CUI_ID_FRAME_AddGuildGeneralBattleID_LIST_GuildNameOnListSelectChange);
	theUiManager.OnListSelectChange(ID_FRAME_AddGuildGeneralBattle,ID_LIST_GuildPlayerSum,s_CUI_ID_FRAME_AddGuildGeneralBattleID_LIST_GuildPlayerSumOnListSelectChange);
	theUiManager.OnListSelectChange(ID_FRAME_AddGuildGeneralBattle,ID_LIST_GuildLevel,s_CUI_ID_FRAME_AddGuildGeneralBattleID_LIST_GuildLevelOnListSelectChange);
	theUiManager.OnListSelectChange(ID_FRAME_AddGuildGeneralBattle,ID_LIST_GuildMasterName,s_CUI_ID_FRAME_AddGuildGeneralBattleID_LIST_GuildMasterNameOnListSelectChange);
	theUiManager.OnListSelectChange(ID_FRAME_AddGuildGeneralBattle,ID_LIST_All,s_CUI_ID_FRAME_AddGuildGeneralBattleID_LIST_AllOnListSelectChange);


	m_pID_FRAME_AddGuildGeneralBattle = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_AddGuildGeneralBattle );
	m_pID_EDIT_SelectName = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_EDIT_SelectName );
	m_pID_BUTTON_Select = (ControlButton*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_BUTTON_Select );
	m_pID_TEXT_PageInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_TEXT_PageInfo );
	m_pID_BUTTON_Back = (ControlButton*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_BUTTON_Back );
	m_pID_BUTTON_Next = (ControlButton*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_BUTTON_Next );
	m_pID_EDIT_Info = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_EDIT_Info );
	m_pID_EDIT_GuildMoneyJin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_EDIT_GuildMoneyJin );
	m_pID_EDIT_GuildMoneyYin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_EDIT_GuildMoneyYin );
	m_pID_EDIT_GuildMoneyTon = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_EDIT_GuildMoneyTon );
	m_pID_BUTTON_Add = (ControlButton*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_BUTTON_Add );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_BUTTON_CLOSE );
	m_pID_EDIT_GuildMission = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_EDIT_GuildMission );
	m_pID_EDIT_MoneyJin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_EDIT_MoneyJin );
	m_pID_EDIT_MoneyYin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_EDIT_MoneyYin );
	m_pID_EDIT_MoneyTon = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_EDIT_MoneyTon );
	m_pID_COMBOBOX_BeginTimeYear = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_COMBOBOX_BeginTimeYear );
	m_pID_COMBOBOX_BeginTimeMonth = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_COMBOBOX_BeginTimeMonth );
	m_pID_COMBOBOX_BeginTimeDay = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_COMBOBOX_BeginTimeDay );
	m_pID_COMBOBOX_BeginTimeHour = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_COMBOBOX_BeginTimeHour );
	m_pID_COMBOBOX_BeginTimeMin = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_COMBOBOX_BeginTimeMin );
	m_pID_COMBOBOX_BeginTimeSec = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_COMBOBOX_BeginTimeSec );
	m_pID_LIST_GuildName = (ControlList*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_LIST_GuildName );
	m_pID_LIST_GuildPlayerSum = (ControlList*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_LIST_GuildPlayerSum );
	m_pID_LIST_GuildLevel = (ControlList*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_LIST_GuildLevel );
	m_pID_LIST_GuildMasterName = (ControlList*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_LIST_GuildMasterName );
	m_pID_LIST_All= (ControlList*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_LIST_All );
	m_pID_TEXT_EndTimeStep = (ControlText*)theUiManager.FindControl( ID_FRAME_AddGuildGeneralBattle, ID_TEXT_EndTimeStep );


	assert( m_pID_FRAME_AddGuildGeneralBattle );
	assert( m_pID_EDIT_SelectName );
	assert( m_pID_BUTTON_Select );
	assert( m_pID_TEXT_PageInfo );
	assert( m_pID_BUTTON_Back );
	assert( m_pID_BUTTON_Next );
	assert( m_pID_EDIT_Info );
	assert( m_pID_EDIT_GuildMoneyJin );
	assert( m_pID_EDIT_GuildMoneyYin );
	assert( m_pID_EDIT_GuildMoneyTon );
	assert( m_pID_BUTTON_Add );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_EDIT_GuildMission );
	assert( m_pID_EDIT_MoneyJin );
	assert( m_pID_EDIT_MoneyYin );
	assert( m_pID_EDIT_MoneyTon );
	assert( m_pID_COMBOBOX_BeginTimeYear );
	assert( m_pID_COMBOBOX_BeginTimeMonth );
	assert( m_pID_COMBOBOX_BeginTimeDay );
	assert( m_pID_COMBOBOX_BeginTimeHour );
	assert( m_pID_COMBOBOX_BeginTimeMin );
	assert( m_pID_COMBOBOX_BeginTimeSec );
	assert( m_pID_LIST_GuildName );
	assert( m_pID_LIST_GuildPlayerSum );
	assert( m_pID_LIST_GuildLevel );
	assert( m_pID_LIST_GuildMasterName );
	assert( m_pID_LIST_All );
	assert(m_pID_TEXT_EndTimeStep);

	m_pID_FRAME_AddGuildGeneralBattle->SetFather(s_CUI_ID_FRAME_GuildBaseInfo.GetFrame());
	m_pID_FRAME_AddGuildGeneralBattle->SetVisable( false );

	m_pID_EDIT_SelectName->SetMaxLength( GuildDefine::MaxNameLength );
	m_pID_EDIT_Info->SetMaxLength(64);
	m_pID_EDIT_GuildMoneyJin->SetMaxLength( 7 );
	m_pID_EDIT_GuildMoneyYin->SetMaxLength( 2 );
	m_pID_EDIT_GuildMoneyTon->SetMaxLength( 2 );
	m_pID_EDIT_MoneyJin->SetMaxLength( 7 );
	m_pID_EDIT_MoneyYin->SetMaxLength( 2 );
	m_pID_EDIT_MoneyTon->SetMaxLength( 2 );
	m_pID_EDIT_GuildMission->SetMaxLength( 7 );

	if( !s_CUI_ID_FRAME_CREATE.GetImeInstance() )
		s_CUI_ID_FRAME_CREATE.SetImeInstance( ImmGetContext( g_hWnd ) );
	return true;
}
	// 卸载UI
bool CUI_ID_FRAME_AddGuildGeneralBattle::_UnLoadUI()
{
	m_pID_FRAME_AddGuildGeneralBattle = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\AddGuildGeneralBattle.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_AddGuildGeneralBattle::_IsVisable()
{
	return m_pID_FRAME_AddGuildGeneralBattle->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_AddGuildGeneralBattle::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_AddGuildGeneralBattle)
		return;
	if(bVisable)
	{
		OnInit();
		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
	}
	else
	{
		ImmAssociateContext( g_hWnd, NULL );
	}

	m_pID_FRAME_AddGuildGeneralBattle->SetVisable( bVisable );
}
void CUI_ID_FRAME_AddGuildGeneralBattle::OnInit()
{
	//当UI打开的时候 我们怎么处理
	//让UI恢复到初始化状态
	//1.搜索栏清空
	m_pID_EDIT_SelectName->SetText("");
	//2.从新加载所有公会
	m_vctGuild.clear();
	if ((theHeroGame.GetPlayerMgr()->GetMe()))
	{
		int nAllGuild = thePlayerRole.GetGuildNum();
		for (int i = 0; i < nAllGuild; ++i)
		{
			if (!thePlayerRole.GetGuild(i)  || thePlayerRole.GetGangMgr()->GetGuildID() == thePlayerRole.GetGuild(i)->GetID())
				continue;
			m_vctGuild.push_back(thePlayerRole.GetGuild(i));
		}
		std::sort(m_vctGuild.begin(), m_vctGuild.end(), SortByGuildGeneralLevel);
	}
	SetBeginTimeComBox();
	//3.公会数据加载到集合里面去了 我们应该讲数据显示到列表栏上面去了
	ShowGuildInfoByPage();
	//4.设置UI上按钮和时间的倒计时
	UpdateGameGeneralBattleStepTime();
}
bool CUI_ID_FRAME_AddGuildGeneralBattle::IfCanAddGameGeneralBattleByTime()
{
	time_t EndTime = thePlayerRole.GetBeginGameGeneralBattleTime();
	time_t nowtime;
	time(&nowtime);
	nowtime +=theHeroGame.GetServerAndLocalOffsetTime();
	if(nowtime >= EndTime)
		return true;
	else
		return false;
}
void CUI_ID_FRAME_AddGuildGeneralBattle::UpdateGameGeneralBattleStepTime()
{
	time_t EndTime = thePlayerRole.GetBeginGameGeneralBattleTime();
	time_t nowtime;
	time(&nowtime);
	nowtime +=theHeroGame.GetServerAndLocalOffsetTime();
	if(nowtime >= EndTime)
	{
		m_pID_BUTTON_Add->SetEnable(true);
		m_pID_TEXT_EndTimeStep->SetText("");
		m_pID_TEXT_EndTimeStep->SetVisable(false);
	}
	else
	{
		m_pID_BUTTON_Add->SetEnable(false);
		m_pID_TEXT_EndTimeStep->SetVisable(true);
		int SpanTime = difftime(EndTime,nowtime);
		int Hour = SpanTime/3600;
		int Min = (SpanTime%3600)/60;
		int Sec = SpanTime%60;
		char szText[256];
		MeSprintf_s(szText, sizeof(szText)/sizeof(char)-1,theXmlString.GetString(eText_GameGeneralBattle_BeginTimeStep),Hour,Min,Sec);
		m_pID_TEXT_EndTimeStep->SetText(szText);
	}
}
void CUI_ID_FRAME_AddGuildGeneralBattle::UpdateAllGuild()
{
	if(!IsVisable())
		return;
	//更新UI面板上全部的值
	m_vctGuild.clear();
	std::string words = m_pID_EDIT_SelectName->GetText();
	if(theHeroGame.GetPlayerMgr()->GetMe())
	{
		if (!words.empty())
		{		
			int nAllGuild = thePlayerRole.GetGuildNum();
			for (int i = 0; i < nAllGuild; ++i)
			{
				if (!thePlayerRole.GetGuild(i) || thePlayerRole.GetGangMgr()->GetGuildID() == thePlayerRole.GetGuild(i)->GetID())
					continue;
				std::string GuildName = thePlayerRole.GetGuild(i)->GetName();
				size_t index = GuildName.find(words.c_str());
				if (index != std::string.npos)
				{
					m_vctGuild.push_back(thePlayerRole.GetGuild(i));
				}
			}
			std::sort(m_vctGuild.begin(), m_vctGuild.end(), SortByGuildGeneralLevel);
		}
		else
		{
			int nAllGuild = thePlayerRole.GetGuildNum();
			for (int i = 0; i < nAllGuild; ++i)
			{
				if (!thePlayerRole.GetGuild(i)  || thePlayerRole.GetGangMgr()->GetGuildID() == thePlayerRole.GetGuild(i)->GetID())
					continue;
				m_vctGuild.push_back(thePlayerRole.GetGuild(i));
			}
			std::sort(m_vctGuild.begin(), m_vctGuild.end(), SortByGuildGeneralLevel);
		}
	}
	ShowGuildInfoByPage(m_NowPage);	
}
void CUI_ID_FRAME_AddGuildGeneralBattle::ShowGuildInfoByPage(int Page)//用于翻页 或者初始化
{
	//1.设置Ui的状态 上一页 下一页
	m_pID_BUTTON_Back->SetEnable(false);
	m_pID_BUTTON_Next->SetEnable(false);
	m_pID_TEXT_PageInfo->SetText("0/0");
	//2.清空列表上的数据
	m_pID_LIST_GuildName->Clear();
	m_pID_LIST_GuildPlayerSum->Clear();
	m_pID_LIST_GuildLevel->Clear();
	m_pID_LIST_GuildMasterName->Clear();
	m_pID_LIST_All->Clear();
	//3.获取当前新的数据进行设置
	if(m_vctGuild.empty()) return;
	int GuildSum = m_vctGuild.size();
	int MaxPage =  GuildSum%MAX_ADDGUILDGENETALBATTLE_MAXPAGE==0?(GuildSum/MAX_ADDGUILDGENETALBATTLE_MAXPAGE):(GuildSum/MAX_ADDGUILDGENETALBATTLE_MAXPAGE +1);//总页数
	if(Page > MaxPage)
		Page = MaxPage;
	if(Page<1)
		Page = 1;
	m_NowPage = Page;//记录当前页数
	//4.页数数据设置到UI上面去
	char szPageNum[256];
	MeSprintf_s(szPageNum, sizeof(szPageNum)/sizeof(char)-1,"%d/%d",Page,MaxPage);
	m_pID_TEXT_PageInfo->SetText(szPageNum);
	//5.根据上一页 下一页 设置按钮的状态
	if(MaxPage == 1)
	{
		m_pID_BUTTON_Back->SetEnable(false);
		m_pID_BUTTON_Next->SetEnable(false);
	}
	else if(Page == 1)
	{
		m_pID_BUTTON_Back->SetEnable(false);
		m_pID_BUTTON_Next->SetEnable(true);
	}
	else if(Page == MaxPage)
	{
		m_pID_BUTTON_Back->SetEnable(true);
		m_pID_BUTTON_Next->SetEnable(false);
	}
	else
	{
		m_pID_BUTTON_Back->SetEnable(true);
		m_pID_BUTTON_Next->SetEnable(true);
	}
	//6.将集合里指定范围的数据设置到UI上面去
	int nStart = (Page - 1) *  MAX_ADDGUILDGENETALBATTLE_MAXPAGE;
	int nEnd = Page * MAX_ADDGUILDGENETALBATTLE_MAXPAGE;
	for (int i = nStart; i < m_vctGuild.size() && i < nEnd; ++i)
	{
		if(!m_vctGuild[i])
			continue;
		char str_name[64] = {0};
		char str_level[64] ={0};
		char str_num[64] ={0};
		char str_MasterName[64] ={0};
		MeSprintf_s(str_name, sizeof(str_name)/sizeof(char) - 1, "%s", m_vctGuild[i]->GetName());//名字
		MeSprintf_s(str_level,sizeof(str_level)/sizeof(char)-1,"%d",m_vctGuild[i]->GetLevel());//等级
		MeSprintf_s(str_num,sizeof(str_num)/sizeof(char)-1,"%d",m_vctGuild[i]->GetMemberNum());//人数
		MeSprintf_s(str_MasterName,sizeof(str_MasterName)/sizeof(char)-1,"%s",m_vctGuild[i]->GetMasterName() );//帮主
		AddToList(str_name,str_level,str_num,str_MasterName);
	}
}
void CUI_ID_FRAME_AddGuildGeneralBattle::OnShow()
{
	s_CUI_ID_FRAME_AddGuildGeneralBattle.SetVisable(true);
}
void CUI_ID_FRAME_AddGuildGeneralBattle::AddToList(const char* m_GuildName,const char *level,const char* num,const char*Mastername)
{
	ControlList::S_List	pItem;
	pItem.SetData(m_GuildName, 0, NULL, 0);
	pItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_LEFT);
	m_pID_LIST_GuildName->AddItem(&pItem,NULL,false);

	pItem.clear();
	pItem.SetData(level);
	pItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_GuildLevel->AddItem(&pItem,NULL,false);

	pItem.clear();
	pItem.SetData(num);
	pItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_GuildPlayerSum->AddItem(&pItem,NULL,false);

	pItem.clear();
	pItem.SetData(Mastername);
	pItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_GuildMasterName->AddItem(&pItem,NULL,false);	

	pItem.clear();
	pItem.SetData("");
	pItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_All->AddItem(&pItem,NULL,false);
}
void CUI_ID_FRAME_AddGuildGeneralBattle::SetBeginTimeComBox()
{
	m_pID_COMBOBOX_BeginTimeYear->Clear();
	m_pID_COMBOBOX_BeginTimeMonth->Clear();
	m_pID_COMBOBOX_BeginTimeDay->Clear();
	m_pID_COMBOBOX_BeginTimeHour->Clear();
	m_pID_COMBOBOX_BeginTimeMin->Clear();
	m_pID_COMBOBOX_BeginTimeSec->Clear();
	//设置好时间限制的项
	time_t nowtime;
	time(&nowtime);
	nowtime +=theHeroGame.GetServerAndLocalOffsetTime();
	struct tm sysNowTime(*localtime(&nowtime));	
	//处理时间函数
	ControlList::S_List	pItem;
	//年 今年和明年
	char In[8]={0};
	itoa(sysNowTime.tm_year+1900,In,10);
	pItem.clear();
	pItem.SetData(In);
	m_pID_COMBOBOX_BeginTimeYear->AddItem(&pItem);
	memset(In,0,sizeof(In));
	itoa(sysNowTime.tm_year+1901,In,10);
	pItem.clear();
	pItem.SetData(In);
	m_pID_COMBOBOX_BeginTimeYear->AddItem(&pItem);
	//月 12个月
	int Year = sysNowTime.tm_year+1900;
	int Month = sysNowTime.tm_mon+1;
	int MonthSum = 0;
	switch(Month)
	{
	case 2:
		MonthSum = (((Year%4==0&&Year%100!=0)||Year%400==0)?29:28);
		break;
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		MonthSum = 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		MonthSum =30;
		break;
	}
	for(int i =1;i<=12;++i)
	{
		char In[8]={0};
		itoa(i,In,10);
		pItem.clear();
		pItem.SetData(In);
		m_pID_COMBOBOX_BeginTimeMonth->AddItem(&pItem);
	}
	//天 1-31天
	for(int i =1;i<=MonthSum;++i)
	{
		char In[8]={0};
		itoa(i,In,10);
		pItem.clear();
		pItem.SetData(In);
		m_pID_COMBOBOX_BeginTimeDay->AddItem(&pItem);
	}
	//小时 
	for(int i =0;i<24;++i)
	{
		char In[8]={0};
		itoa(i,In,10);
		pItem.clear();
		pItem.SetData(In);
		m_pID_COMBOBOX_BeginTimeHour->AddItem(&pItem);
	}
	//分钟
	for(int i =0;i<=59;++i)
	{
		char In[8]={0};
		itoa(i,In,10);
		pItem.clear();
		pItem.SetData(In);
		m_pID_COMBOBOX_BeginTimeMin->AddItem(&pItem);
	}
	//秒
	for(int i =0;i<=59;++i)
	{
		char In[8]={0};
		itoa(i,In,10);
		pItem.clear();
		pItem.SetData(In);
		m_pID_COMBOBOX_BeginTimeSec->AddItem(&pItem);
	}
	//设置默认值
	time_t BeginTime = nowtime+ 660 + GameBattleDefine::WaiteAddMsgBattleTime;
	int Day =sysNowTime.tm_mday;
	int Hour =sysNowTime.tm_hour;
	int Min =sysNowTime.tm_min;
	int Sec =sysNowTime.tm_sec;

	struct tm sysBeginTime(*localtime(&BeginTime));
	int nYear = sysBeginTime.tm_year+1900;
	int nMonth = sysBeginTime.tm_mon+1;
	int nDay =sysBeginTime.tm_mday;
	int nHour =sysBeginTime.tm_hour;
	int nMin =sysBeginTime.tm_min;
	int nSec =sysBeginTime.tm_sec;

	if(Year == nYear)
		m_pID_COMBOBOX_BeginTimeYear->SetCurSelIndex(0);
	else
		m_pID_COMBOBOX_BeginTimeYear->SetCurSelIndex(1);

	m_pID_COMBOBOX_BeginTimeMonth->SetCurSelIndex(nMonth-1);
	m_pID_COMBOBOX_BeginTimeDay->SetCurSelIndex(nDay -1);
	m_pID_COMBOBOX_BeginTimeHour->SetCurSelIndex(nHour);
	m_pID_COMBOBOX_BeginTimeMin->SetCurSelIndex(nMin);
	m_pID_COMBOBOX_BeginTimeSec->SetCurSelIndex(nSec);

}
bool CUI_ID_FRAME_AddGuildGeneralBattle::EditInputIsVisable()
{
	if (!m_pID_FRAME_AddGuildGeneralBattle)
		return false;

	if(theUiManager.GetFocus())
	{
		if(theUiManager.GetFocus() == m_pID_EDIT_SelectName || 
			theUiManager.GetFocus() ==m_pID_EDIT_GuildMoneyJin ||
			theUiManager.GetFocus() ==m_pID_EDIT_GuildMoneyYin ||
			theUiManager.GetFocus() ==m_pID_EDIT_GuildMoneyTon ||
			theUiManager.GetFocus() ==m_pID_EDIT_GuildMission ||
			theUiManager.GetFocus() ==m_pID_EDIT_MoneyJin ||
			theUiManager.GetFocus() ==m_pID_EDIT_MoneyYin ||
			theUiManager.GetFocus() ==m_pID_EDIT_Info||
			theUiManager.GetFocus() ==m_pID_EDIT_MoneyTon)
			return true;
	}

	return false;
}