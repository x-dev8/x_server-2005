/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\ActivityList.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ActivityList.h"
#include "EventTimeTable.h"
#include "MeUi/ExpressionManager.h"
#include "GameMain.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "CrossMapPF.h"
#include "MeTerrain/stdafx.h"
#include "../color_config.h"
#include "XmlStringLanguage.h"
#include "PlayerRole.h"
#include "ChatInfoBox.h"
#include "UIMgr.h"
#include <time.h>
#include "Task_Track.h"
#include "ActivityTrack.h"
#include "ActivityMonthList.h"
#include "Common.h"
#include "Ui/InfoList.h"
#include "ActivityDay.h"
#include "LeaveExp.h"
extern CHeroGame* theApp;

enum EventStatus
{
	ES_Start,		// 进行中
	ES_Ready,		// 预备
	ES_Finish,		// 完成
	ES_Close,		// 关闭
	ES_Wait,		// 未开始
};

static void InitialChildList( ControlList* pLIST )
{
	pLIST->SetMsgHoldup(false);	//不接受消息
	pLIST->SetItemMaxCount( 100 );
	pLIST->HaveSelBar( false );	//没有绿色cur选中地图
	pLIST->SetCurSelIndex(-1);
	pLIST->SetDrawFlags(DT_CENTER|DT_NOCLIP);
}

static int GetEventStatus(const Event& content, const struct tm& nowtime)
{
	int status = 0;

	if (thePlayerRole.GetVariableValue(content.completeTimeVarIndex) == content.count)
	{
		status = ES_Finish;
	}
	else if (content.hour <= nowtime.tm_hour)
	{
		if (content.duration >= (nowtime.tm_hour * 60 + nowtime.tm_min) - (content.hour * 60 + content.minute))
			status = ES_Start;
		else
			status = ES_Close;
	}
	else if (content.endWeek != content.week && (content.endHour > nowtime.tm_hour || content.endHour == nowtime.tm_hour && content.endMinute >= nowtime.tm_min))
	{
		status = ES_Start;
	}
	else if ((content.hour * 60 + content.minute) - (nowtime.tm_hour * 60 + nowtime.tm_min) <= 60)
	{
		status = ES_Ready;
	}
	else
	{
		status = ES_Close;
	}
 
	if(content.periodTypeId == 2) //一周内某一天的活动
	{
		if(content.periodParameter != nowtime.tm_wday)
		{
          status = ES_Close; //不是当天的活动 则关闭
		}

	}
	return status;
}

bool SortByQulity(const Event* v1, const Event* v2)
{
	return v1->quality < v2->quality;
}

bool SortByPeriod(const Event* v1, const Event* v2)
{
	int w1 = v1->week;
	int w2 = v2->week;
	if (v1->isEveryday || v1->isHot)
		w1 = -1;
	else if (w1 == 0)
		w1 = 7;

	if (v2->isEveryday || v2->isHot)
		w2 = -1;
	else if (w2 == 0)
		w2 = 7;
	return w1 < w2;
}

bool SortByTime(const Event* v1, const Event* v2)
{
	DWORD dwTime1 = v1->hour * 60 + v1->minute;
	DWORD dwTime2 = v2->hour * 60 + v2->minute;

	return dwTime1 < dwTime2;
}

bool SortByName(const Event* v1, const Event* v2)
{
	return v1->name < v2->name;
}

bool SortByMap(const Event* v1, const Event* v2)
{
	return v1->mapName < v2->mapName;
}

bool SortByNeedLevel(const Event* v1, const Event* v2)
{
	return v1->needLevel < v2->needLevel;
}

bool SortByStatus(const Event* v1, const Event* v2)
{
	return GetEventStatus(*v1, s_CUI_ID_FRAME_ActivityList.GetNowtime()) > GetEventStatus(*v2, s_CUI_ID_FRAME_ActivityList.GetNowtime());
}

bool SortByCount(const Event* v1, const Event* v2)
{
	return thePlayerRole.GetVariableValue(v1->completeTimeVarIndex) < thePlayerRole.GetVariableValue(v2->completeTimeVarIndex);
}

static SortEventContents s_sortEvtContents;
static SortEventContents s_sortHotEvtContents;
static SortEventContents s_todayEvtContents;
static EventContents s_eventContents;
static std::vector<std::string> s_trackEventNames;

typedef bool (*EventSort)(const Event* v1, const Event* v2);
static EventSort s_eventSort = SortByQulity;
static int s_nGetResultIndex = 0;

static EventSort s_eventSort2 = SortByTime;
static int s_nGetResultIndex2 = 0;

static bool EventSortFunc(const Event* v1, const Event* v2)
{
	if (s_nGetResultIndex == 0)
		return s_eventSort(v1, v2);
	return s_eventSort(v2, v1);
}

static bool EventSortFunc2(const Event* v1, const Event* v2)
{
	if (s_nGetResultIndex2 == 0)
		return s_eventSort2(v1, v2);
	return s_eventSort2(v2, v1);
}

static void SetSortFunc(EventSort func, int upperSort)
{
	s_nGetResultIndex = upperSort;
	s_eventSort = func;
}

static void SetSortFunc2(EventSort func, int upperSort)
{
	s_nGetResultIndex2 = upperSort;
	s_eventSort2 = func;
}

static void UpdateTodayEvents()
{
	s_todayEvtContents.clear();

	{
		const EventContents& contents = EventManager::Instance().GetHotEventContents();
		for (int i = 0; i < contents.size(); ++i)
		{
			Event* content = const_cast<Event*>(&contents[i]);
			//s_todayEvtContents.push_back(content);
			if (content->country ==CountryDefine::Country_Init || content->country ==thePlayerRole.GetCountry())
			{
				s_todayEvtContents.push_back(content);
			}
		}
	}

	{
		const EventContents& contents = EventManager::Instance().GetEverydayEventContents();
		for (int i = 0; i < contents.size(); ++i)
		{
			Event* content = const_cast<Event*>(&contents[i]);
//			s_todayEvtContents.push_back(content);
			if (content->country ==CountryDefine::Country_Init || content->country ==thePlayerRole.GetCountry())
			{
				s_todayEvtContents.push_back(content);
			}
		}
	}
	{
		s_eventContents.clear();

		struct tm nowtime = s_CUI_ID_FRAME_ActivityList.GetNowtime();

		EventManager::Instance().GetMonthEventContents(nowtime, s_eventContents);

		for(int i=0;i<s_eventContents.size();++i)
		{
			if(s_eventContents[i].day == nowtime.tm_mday)
			{
				bool have = false;
				for(int j=0;j<s_todayEvtContents.size();++j)
				{
					if(s_todayEvtContents[j]->name == s_eventContents[i].name)
					{
						if(s_todayEvtContents[j]->endHour==s_eventContents[i].endHour
							&&s_todayEvtContents[j]->endMinute==s_eventContents[i].endMinute
							&&s_todayEvtContents[j]->duration==s_eventContents[i].duration)
						{
							have = true;
							break;
						}
					}
				}

				if(!have)
				{
					Event* content = const_cast<Event*>(&s_eventContents[i]);
					if (content->country ==CountryDefine::Country_Init || content->country ==thePlayerRole.GetCountry())
					{
						s_todayEvtContents.push_back(content);
					}
				}
			}
		}
	}
}

//------------------------------------------------------------------------------------------------

CUI_ID_FRAME_ActivityList s_CUI_ID_FRAME_ActivityList;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ActivityList, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ActivityList, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_BUTTON_HelpOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_BUTTON_ActivityLvlOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_BUTTON_ActivityTimeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_BUTTON_ActivityNameOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_BUTTON_ActivityMapOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_BUTTON_PlayerLvlOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_BUTTON_FinishOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_BUTTON_StateOnButtonClick )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_CHECKBOX_ActivityOnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_CHECKBOX_TaskOnCheckBoxCheck )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LISTIMG_EncouragementOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LISTIMG_EncouragementOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LISTIMG_EncouragementOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LISTIMG_EncouragementOnIconRButtonUp )
//MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LIST_ActivityLvlOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LIST_ActivityTimeOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LIST_ActivityNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LIST_ActivityMapOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LIST_PlayerLvlOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LIST_FinishOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LIST_StateOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LIST_ActivityListOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_BUTTON_ActivityDateOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LIST_ActivityDateOnListSelectChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_CHECKBOX_Show2HOnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_CHECKBOX_WeekTaskOnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_CHECKBOX_AllTaskOnCheckBoxCheck )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LISTIMG_RewardOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LISTIMG_RewardOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LISTIMG_RewardOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LISTIMG_RewardOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_BUTTON_ActivityTime2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_BUTTON_ActivityName2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_BUTTON_ActivityMap2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_BUTTON_PlayerLvl2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_BUTTON_Finish2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_BUTTON_Reward2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_BUTTON_ActivityDate2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_BUTTON_State2OnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LIST_ActivityList2OnListSelectChange )
//MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LISTIMG_Reward2OnIconDragOn )
//MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LISTIMG_Reward2OnIconLDBClick )
//MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LISTIMG_Reward2OnIconButtonClick )
//MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LISTIMG_Reward2OnIconRButtonUp )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_CHECKBOX_ActivityTrackOnCheckBoxCheck )
/*MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LIST_ActivityHotOnListSelectChange )*/
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LIST_ActivityHot2OnListSelectChange )
//MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LIST_ActivityTipOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_LIST_ActivityTip2OnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_BUTTON_DayOnButtonClick )
//////////////////////////////////////
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_CHECKBOX_EveryDayOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_CHECKBOX_CountryOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_CHECKBOX_EctypeOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_CHECKBOX_FamilyOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_CHECKBOX_WelfareOnCheckBoxCheck )

MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityList, ID_CHECKBOX_LeaveExpOnCheckBoxCheck )

CUI_ID_FRAME_ActivityList::CUI_ID_FRAME_ActivityList()
{
	// Member
	m_pID_FRAME_ActivityList = NULL;
// 	m_pID_PICTURE_TitleDi = NULL;
// 	m_pID_TEXT_Title = NULL;
// 	m_pID_PICTURE_TitleLeftMiddle = NULL;
// 	m_pID_PICTURE_TitleRightMiddle = NULL;
// 	m_pID_PICTURE_TitleLeft = NULL;
// 	m_pID_PICTURE_TitleRight = NULL;
	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_Help = NULL;
// 	m_pID_PICTURE_14866 = NULL;
	m_pID_TEXT_Time = NULL;
// 	m_pID_PICTURE_Wall1 = NULL;
// 	m_pID_PICTURE_Wall2 = NULL;
// 	m_pID_BUTTON_ActivityLvl = NULL;
	m_pID_BUTTON_ActivityTime = NULL;
	m_pID_BUTTON_ActivityName = NULL;
	m_pID_BUTTON_ActivityMap = NULL;
	m_pID_BUTTON_PlayerLvl = NULL;
	m_pID_BUTTON_Finish = NULL;
	m_pID_BUTTON_State = NULL;
	m_pID_TEXT_ActivityNameZ = NULL;
	m_pID_TEXT_PlayerLvlZ = NULL;
	m_pID_TEXT_ActivityTimeZ = NULL;
	m_pID_TEXT_ActivityNpcZ = NULL;
	m_pID_TEXT_ActivityInfo = NULL;
// 	m_pID_CHECKBOX_Activity = NULL;
// 	m_pID_CHECKBOX_Task = NULL;
	m_pID_TEXT_ActivityInfoZ = NULL;
	m_pID_TEXT_Encouragement = NULL;
	m_pID_LISTIMG_Encouragement = NULL;
	m_pID_TEXT_ActivityName = NULL;
	m_pID_TEXT_PlayerLvl = NULL;
	m_pID_TEXT_ActivityTime = NULL;
	m_pID_TEXT_ActivityNpc = NULL;
	//m_pID_LIST_ActivityLvl = NULL;
	m_pID_LIST_ActivityTime = NULL;
	m_pID_LIST_ActivityName = NULL;
	m_pID_LIST_ActivityMap = NULL;
	m_pID_LIST_PlayerLvl = NULL;
	m_pID_LIST_Finish = NULL;
	m_pID_LIST_State = NULL;
	m_pID_LIST_ActivityList = NULL;
	m_pID_BUTTON_ActivityDate = NULL;
	m_pID_LIST_ActivityDate = NULL;
	m_pID_CHECKBOX_Show2H = NULL;
// 	m_pID_CHECKBOX_WeekTask = NULL;
// 	m_pID_CHECKBOX_AllTask = NULL;
// 	m_pID_TEXT_ArrowActivityLvl = NULL;
	m_pID_TEXT_ArrowActivityDate = NULL;
	m_pID_TEXT_ArrowActivityTime = NULL;
	m_pID_TEXT_ArrowActivityName = NULL;
	m_pID_TEXT_ArrowActivityMap = NULL;
	m_pID_TEXT_ArrowPlayerLvl = NULL;
	m_pID_TEXT_ArrowFinish = NULL;
	m_pID_TEXT_ArrowState = NULL;
	m_pID_LISTIMG_Reward = NULL;
	m_pID_BUTTON_ActivityTime2 = NULL;
	m_pID_BUTTON_ActivityName2 = NULL;
	m_pID_BUTTON_ActivityMap2 = NULL;
	m_pID_BUTTON_PlayerLvl2 = NULL;
	m_pID_BUTTON_Finish2 = NULL;
	m_pID_BUTTON_Reward2 = NULL;
	m_pID_BUTTON_ActivityDate2 = NULL;
	m_pID_BUTTON_State2 = NULL;
	m_pID_LIST_ActivityList2 = NULL;
	//m_pID_LIST_ActivityTime2 = NULL;
	m_pID_LIST_ActivityName2 = NULL;
	m_pID_LIST_ActivityMap2 = NULL;
	m_pID_LIST_PlayerLvl2 = NULL;
	m_pID_LIST_Finish2 = NULL;
	m_pID_LIST_State2 = NULL;
	m_pID_LIST_ActivityDate2 = NULL;
	//m_pID_LISTIMG_Reward2 = NULL;
	m_pID_TEXT_ArrowActivityDate2 = NULL;
	m_pID_TEXT_ArrowActivityTime2 = NULL;
	m_pID_TEXT_ArrowActivityName2 = NULL;
	m_pID_TEXT_ArrowActivityMap2 = NULL;
	m_pID_TEXT_ArrowPlayerLvl2 = NULL;
	m_pID_TEXT_ArrowFinish2 = NULL;
	m_pID_TEXT_ArrowReward2 = NULL;
	m_pID_TEXT_ArrowState2 = NULL;
	m_pID_TEXT_21270 = NULL;
	m_pID_TEXT_212702 = NULL;
	m_pID_CHECKBOX_ActivityTrack = NULL;

	m_pID_LIST_ActivityType = NULL;
	//m_pID_LIST_ActivityType2 = NULL;


	serverAndLocalOffsetTime = 0;
   // m_pID_LIST_ActivityHot = NULL;
    m_pID_LIST_ActivityHot2 = NULL;
//    m_pID_LIST_ActivityTip = NULL;
    m_pID_LIST_ActivityTip2 = NULL;
	////////////////////////////
	m_pID_CHECKBOX_EveryDay = NULL;
	m_pID_CHECKBOX_Country = NULL;
	m_pID_CHECKBOX_Ectype = NULL;
	m_pID_CHECKBOX_Family = NULL;
	m_pID_CHECKBOX_Welfare = NULL;
	m_pID_LIST_ActivityStart = NULL;

	m_pID_CHECKBOX_LeaveExp = NULL;

	m_CurrentType = 1;

	memset(m_CheckCtrl,0,MAX_CHECKTAB_COUNT);
}

const SortEventContents& GetTodayEvtContents()
{
	return s_todayEvtContents;
}
// Frame
bool CUI_ID_FRAME_ActivityList::OnFrameRun()
{
	if(!IsVisable())
		return false;

	int nStartIndex = m_pID_LIST_ActivityList->GetShowStartHeight();
	m_pID_LIST_ActivityTime->SetShowStartHeight(nStartIndex);
	m_pID_LIST_ActivityName->SetShowStartHeight(nStartIndex);
	m_pID_LIST_ActivityMap->SetShowStartHeight(nStartIndex);
	m_pID_LIST_PlayerLvl->SetShowStartHeight(nStartIndex);
	m_pID_LIST_Finish->SetShowStartHeight(nStartIndex);
	m_pID_LIST_State->SetShowStartHeight(nStartIndex);
	m_pID_LIST_ActivityDate->SetShowStartHeight(nStartIndex);
	m_pID_LISTIMG_Reward->SetShowStartHeight(nStartIndex);
	m_pID_LIST_ActivityType->SetShowStartHeight(nStartIndex);
	

	nStartIndex = m_pID_LIST_ActivityList2->GetShowStartHeight();
	//m_pID_LIST_ActivityTime2->SetShowStartHeight(nStartIndex);
	m_pID_LIST_ActivityStart->SetShowStartHeight(nStartIndex);
	m_pID_LIST_ActivityName2->SetShowStartHeight(nStartIndex);
	m_pID_LIST_ActivityMap2->SetShowStartHeight(nStartIndex);
	m_pID_LIST_PlayerLvl2->SetShowStartHeight(nStartIndex);
	m_pID_LIST_Finish2->SetShowStartHeight(nStartIndex);
	m_pID_LIST_State2->SetShowStartHeight(nStartIndex);
	m_pID_LIST_ActivityDate2->SetShowStartHeight(nStartIndex);
	//m_pID_LISTIMG_Reward2->SetShowStartHeight(nStartIndex);
    m_pID_LIST_ActivityHot2->SetShowStartHeight(nStartIndex);
    m_pID_LIST_ActivityTip2->SetShowStartHeight(nStartIndex);
	//m_pID_LIST_ActivityType2->SetShowStartHeight(nStartIndex);

	return true;
}

void CUI_ID_FRAME_ActivityList::SetCheckStatus(ECheckControl EControl)
{
	ControlCheckBox* CheckArr[] = {m_pID_CHECKBOX_EveryDay,m_pID_CHECKBOX_Country,m_pID_CHECKBOX_Ectype,m_pID_CHECKBOX_Family,m_pID_CHECKBOX_Welfare};
	for (int i=0;i<sizeof(CheckArr)/sizeof(ControlCheckBox*);++i)
	{
		if (EControl == i)
		{
			CheckArr[i]->SetCheck(true);
		}
		else
			CheckArr[i]->SetCheck(false);
	}
}

bool CUI_ID_FRAME_ActivityList::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_ActivityList::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_ActivityList::ID_BUTTON_HelpOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
// bool CUI_ID_FRAME_ActivityList::ID_BUTTON_ActivityLvlOnButtonClick( ControlObject* pSender )
// {
// 	return true;
// }
// Button
bool CUI_ID_FRAME_ActivityList::ID_BUTTON_ActivityTimeOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ActivityList)
		return false;

	ShowSortArrow(ESTime);
	SetSortFunc(SortByTime, m_bArrow[ESTime]);
	m_pID_LIST_ActivityList->GetScrollBar()->SetValue(0);
	Refresh(m_CurrentType);
	return true;
}
// Button
bool CUI_ID_FRAME_ActivityList::ID_BUTTON_ActivityNameOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ActivityList)
		return false;

	ShowSortArrow(ESName);
	SetSortFunc(SortByName, m_bArrow[ESName]);
	m_pID_LIST_ActivityList->GetScrollBar()->SetValue(0);
	Refresh(m_CurrentType);
	return true;
}
// Button
bool CUI_ID_FRAME_ActivityList::ID_BUTTON_ActivityMapOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ActivityList)
		return false;

	ShowSortArrow(ESMap);
	SetSortFunc(SortByMap, m_bArrow[ESMap]);
	m_pID_LIST_ActivityList->GetScrollBar()->SetValue(0);
	Refresh(m_CurrentType);
	return true;
}
// Button
bool CUI_ID_FRAME_ActivityList::ID_BUTTON_PlayerLvlOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ActivityList)
		return false;

	ShowSortArrow(ESPlayerLvl);
	SetSortFunc(SortByNeedLevel, m_bArrow[ESPlayerLvl]);
	m_pID_LIST_ActivityList->GetScrollBar()->SetValue(0);
	Refresh(m_CurrentType);
	return true;
}
// Button
bool CUI_ID_FRAME_ActivityList::ID_BUTTON_FinishOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ActivityList)
		return false;

	ShowSortArrow(ESFinish);
	SetSortFunc(SortByCount, m_bArrow[ESFinish]);
	m_pID_LIST_ActivityList->GetScrollBar()->SetValue(0);
	Refresh(m_CurrentType);
	return true;
}
// Button
bool CUI_ID_FRAME_ActivityList::ID_BUTTON_StateOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ActivityList)
		return false;

	ShowSortArrow(ESState);
	SetSortFunc(SortByStatus, m_bArrow[ESState]);
	m_pID_LIST_ActivityList->GetScrollBar()->SetValue(0);
	Refresh(m_CurrentType);
	return true;
}
// Button
bool CUI_ID_FRAME_ActivityList::ID_BUTTON_ActivityDateOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ActivityList)
		return false;

	ShowSortArrow(ESDate);
	SetSortFunc(SortByPeriod, m_bArrow[ESDate]);
	m_pID_LIST_ActivityList->GetScrollBar()->SetValue(0);
	Refresh(m_CurrentType);
	return true;
}
// CheckBox
// void CUI_ID_FRAME_ActivityList::ID_CHECKBOX_ActivityOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	if(!m_pID_FRAME_ActivityList)
// 		return ;
// 
// 	m_pID_CHECKBOX_Activity->SetCheck(true);
// 	m_pID_CHECKBOX_Task->SetCheck(false);
// 	m_pID_CHECKBOX_WeekTask->SetCheck(false);
// 	m_pID_CHECKBOX_AllTask->SetCheck(false);
// 	Refresh();
// }
// // CheckBox
// void CUI_ID_FRAME_ActivityList::ID_CHECKBOX_TaskOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	if(!m_pID_FRAME_ActivityList)
// 		return ;
// 
// 	m_pID_CHECKBOX_Activity->SetCheck(false);
// 	m_pID_CHECKBOX_Task->SetCheck(true);
// 	m_pID_CHECKBOX_WeekTask->SetCheck(false);
// 	m_pID_CHECKBOX_AllTask->SetCheck(false);
// 	Refresh();
// }
// ListImg / ListEx
bool CUI_ID_FRAME_ActivityList::ID_LISTIMG_EncouragementOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																	 ControlIconDrag::S_ListImg* pItemDrag,
																	 ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_ActivityList::ID_LISTIMG_EncouragementOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ActivityList::ID_LISTIMG_EncouragementOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ActivityList::ID_LISTIMG_EncouragementOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// List
// void CUI_ID_FRAME_ActivityList::ID_LIST_ActivityLvlOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
// {
// }
// List
void CUI_ID_FRAME_ActivityList::ID_LIST_ActivityTimeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_ActivityList::ID_LIST_ActivityNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_ActivityList::ID_LIST_ActivityMapOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_ActivityList::ID_LIST_PlayerLvlOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_ActivityList::ID_LIST_FinishOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_ActivityList::ID_LIST_StateOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_ActivityList::ID_LIST_ActivityListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_ActivityList)
		return ;

	m_pCurrActivityList = m_pID_LIST_ActivityList;
	UpdateSelectedContent();
}
// List
void CUI_ID_FRAME_ActivityList::ID_LIST_ActivityDateOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// CheckBox
void CUI_ID_FRAME_ActivityList::ID_CHECKBOX_Show2HOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_ActivityList)
		return ;

	m_pID_LIST_ActivityList->GetScrollBar()->SetValue(0);
	Refresh(m_CurrentType);
}
// CheckBox
// void CUI_ID_FRAME_ActivityList::ID_CHECKBOX_WeekTaskOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	if(!m_pID_FRAME_ActivityList)
// 		return ;
// 
// 	m_pID_CHECKBOX_Activity->SetCheck(false);
// 	m_pID_CHECKBOX_Task->SetCheck(false);
// 	m_pID_CHECKBOX_WeekTask->SetCheck(true);
// 	m_pID_CHECKBOX_AllTask->SetCheck(false);
// 	Refresh();
// }
// // CheckBox
// void CUI_ID_FRAME_ActivityList::ID_CHECKBOX_AllTaskOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	if(!m_pID_FRAME_ActivityList)
// 		return ;
// 
// 	m_pID_CHECKBOX_Activity->SetCheck(false);
// 	m_pID_CHECKBOX_Task->SetCheck(false);
// 	m_pID_CHECKBOX_WeekTask->SetCheck(false);
// 	m_pID_CHECKBOX_AllTask->SetCheck(true);
// 	Refresh();
// }
// ListImg / ListEx
bool CUI_ID_FRAME_ActivityList::ID_LISTIMG_RewardOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_ActivityList::ID_LISTIMG_RewardOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ActivityList::ID_LISTIMG_RewardOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ActivityList::ID_LISTIMG_RewardOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// Button
bool CUI_ID_FRAME_ActivityList::ID_BUTTON_ActivityTime2OnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ActivityList)
		return false;

	ShowSortArrow2(ESTime);
	SetSortFunc2(SortByTime, m_bArrow2[ESTime]);
	m_pID_LIST_ActivityList2->GetScrollBar()->SetValue(0);
	Refresh(m_CurrentType);
	return true;
}
// Button
bool CUI_ID_FRAME_ActivityList::ID_BUTTON_ActivityName2OnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ActivityList)
		return false;

	ShowSortArrow2(ESName);
	SetSortFunc2(SortByName, m_bArrow2[ESName]);
	m_pID_LIST_ActivityList2->GetScrollBar()->SetValue(0);
	Refresh(m_CurrentType);
	return true;
}
// Button
bool CUI_ID_FRAME_ActivityList::ID_BUTTON_ActivityMap2OnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ActivityList)
		return false;

	ShowSortArrow2(ESMap);
	SetSortFunc2(SortByMap, m_bArrow2[ESMap]);
	m_pID_LIST_ActivityList2->GetScrollBar()->SetValue(0);
	Refresh(m_CurrentType);
	return true;
}
// Button
bool CUI_ID_FRAME_ActivityList::ID_BUTTON_PlayerLvl2OnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ActivityList)
		return false;

	ShowSortArrow2(ESPlayerLvl);
	SetSortFunc2(SortByNeedLevel, m_bArrow2[ESPlayerLvl]);
	m_pID_LIST_ActivityList2->GetScrollBar()->SetValue(0);
	Refresh(m_CurrentType);
	return true;
}
// Button
bool CUI_ID_FRAME_ActivityList::ID_BUTTON_Finish2OnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ActivityList)
		return false;

	ShowSortArrow2(ESFinish);
	SetSortFunc2(SortByCount, m_bArrow2[ESFinish]);
	m_pID_LIST_ActivityList2->GetScrollBar()->SetValue(0);
	Refresh(m_CurrentType);
	return true;
}
// Button
bool CUI_ID_FRAME_ActivityList::ID_BUTTON_Reward2OnButtonClick( ControlObject* pSender )
{
	return true;
}

// Button
void CUI_ID_FRAME_ActivityList::ID_CHECKBOX_EveryDayOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  )
{
	m_tabGroup.TogglePage( m_pID_CHECKBOX_EveryDay );
	Refresh(theEventManager.GetEventCategory()[0].id);
	s_CUI_ID_FRAME_LeaveExp.SetVisable(false);
}
// Button
void CUI_ID_FRAME_ActivityList::ID_CHECKBOX_CountryOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  )
{
	//SetCheckStatus(ECHECK_Country);
	m_tabGroup.TogglePage( m_pID_CHECKBOX_Country );
	Refresh(theEventManager.GetEventCategory()[1].id);
	s_CUI_ID_FRAME_LeaveExp.SetVisable(false);
}
// Button
void CUI_ID_FRAME_ActivityList::ID_CHECKBOX_EctypeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  )
{
	//SetCheckStatus(ECHECK_Ectype);
	m_tabGroup.TogglePage( m_pID_CHECKBOX_Ectype );
	Refresh(theEventManager.GetEventCategory()[2].id);
	s_CUI_ID_FRAME_LeaveExp.SetVisable(false);
}
// Button
void CUI_ID_FRAME_ActivityList::ID_CHECKBOX_FamilyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  )
{
	//SetCheckStatus(ECHECK_Family);
	m_tabGroup.TogglePage( m_pID_CHECKBOX_Family );
	Refresh(theEventManager.GetEventCategory()[3].id);
	s_CUI_ID_FRAME_LeaveExp.SetVisable(false);
}
// Button
void CUI_ID_FRAME_ActivityList::ID_CHECKBOX_WelfareOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  )
{
	//SetCheckStatus(ECHECK_Welfare);
	m_tabGroup.TogglePage( m_pID_CHECKBOX_Welfare );
	Refresh(theEventManager.GetEventCategory()[4].id);
	s_CUI_ID_FRAME_LeaveExp.SetVisable(false);
}
void CUI_ID_FRAME_ActivityList::ID_CHECKBOX_LeaveExpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  )
{
	//让其他面板隐藏
	m_tabGroup.TogglePage( m_pID_CHECKBOX_LeaveExp );
	s_CUI_ID_FRAME_LeaveExp.OnShow();
}
void CUI_ID_FRAME_ActivityList::ShowActionByType(int Type)
{
	if(Type == theEventManager.GetEventCategory()[0].id)
	{
		SetCheckStatus(ECHECK_EveryDay);
		m_tabGroup.TogglePage( m_pID_CHECKBOX_EveryDay );
		Refresh(theEventManager.GetEventCategory()[0].id);
	}
	else if(Type == theEventManager.GetEventCategory()[1].id)
	{
		SetCheckStatus(ECHECK_Country);
		m_tabGroup.TogglePage( m_pID_CHECKBOX_Country );
		Refresh(theEventManager.GetEventCategory()[1].id);
	}
	else if(Type == theEventManager.GetEventCategory()[2].id)
	{
		SetCheckStatus(ECHECK_Ectype);
		m_tabGroup.TogglePage( m_pID_CHECKBOX_Ectype );
		Refresh(theEventManager.GetEventCategory()[2].id);
	}
	else if(Type == theEventManager.GetEventCategory()[3].id)
	{
		SetCheckStatus(ECHECK_Family);
		m_tabGroup.TogglePage( m_pID_CHECKBOX_Family );
		Refresh(theEventManager.GetEventCategory()[3].id);
	}
	else if(Type == theEventManager.GetEventCategory()[4].id)
	{
		SetCheckStatus(ECHECK_Welfare);
		m_tabGroup.TogglePage( m_pID_CHECKBOX_Welfare );
		Refresh(theEventManager.GetEventCategory()[4].id);
	}
	s_CUI_ID_FRAME_LeaveExp.SetVisable(false);
}
// Button
bool CUI_ID_FRAME_ActivityList::ID_BUTTON_ActivityDate2OnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ActivityList)
		return false;

	ShowSortArrow2(ESDate);
	SetSortFunc2(SortByPeriod, m_bArrow2[ESDate]);
	m_pID_LIST_ActivityList2->GetScrollBar()->SetValue(0);
	Refresh();
	return true;
}
// Button
bool CUI_ID_FRAME_ActivityList::ID_BUTTON_State2OnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ActivityList)
		return false;

	ShowSortArrow2(ESState);
	SetSortFunc2(SortByStatus, m_bArrow2[ESState]);
	m_pID_LIST_ActivityList2->GetScrollBar()->SetValue(0);
	Refresh();
	return true;
}
// List
void CUI_ID_FRAME_ActivityList::ID_LIST_ActivityList2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_ActivityList)
		return ;

	m_pCurrActivityList = m_pID_LIST_ActivityList2;
	UpdateSelectedContent();
}
// ListImg / ListEx
//bool CUI_ID_FRAME_ActivityList::ID_LISTIMG_Reward2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
//															   ControlIconDrag::S_ListImg* pItemDrag,
//															   ControlIconDrag::S_ListImg* pItemSrc )
//{
//	return false;
//}
//bool CUI_ID_FRAME_ActivityList::ID_LISTIMG_Reward2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	return false;
//}
//bool CUI_ID_FRAME_ActivityList::ID_LISTIMG_Reward2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	return false;
//}
//bool CUI_ID_FRAME_ActivityList::ID_LISTIMG_Reward2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	return false;
//}
// CheckBox
void CUI_ID_FRAME_ActivityList::ID_CHECKBOX_ActivityTrackOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	//modified by zhuomeng.hu		[9/13/2010]
	s_CUI_ID_FRAME_ActivityTrack.SetVisable(/*s_CUI_ID_FRAME_ActivityTrack.GetTrackListItemCnt() > 0 && */*pbChecked);
}

// List
// void CUI_ID_FRAME_ActivityList::ID_LIST_ActivityHotOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
// {
// }
// List
void CUI_ID_FRAME_ActivityList::ID_LIST_ActivityHot2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}

// List
// void CUI_ID_FRAME_ActivityList::ID_LIST_ActivityTipOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
// {
// }
// List
void CUI_ID_FRAME_ActivityList::ID_LIST_ActivityTip2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// Button
bool CUI_ID_FRAME_ActivityList::ID_BUTTON_DayOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	s_CUI_ID_FRAME_ActivityMonthList.SetVisable(true);
	return true;
}

void CUI_ID_FRAME_ActivityList::InitializeAtEnterWorld()
{
    m_bShowTrak = true;			//added by zhuomeng.hu		[9/13/2010]
    for (int i = 0; i < eSortTypeTotal; ++i)
    {
        m_bArrow[i] = false;
    }
    for (int i = 0; i < eSortTypeTotal; ++i)
    {
        m_bArrow2[i] = false;
    }
    s_trackEventNames.clear();
    today = -1;

    s_eventSort = SortByQulity;
    s_nGetResultIndex = 0;

    s_eventSort2 = SortByTime;
    s_nGetResultIndex2 = 0;
	
}

// 装载UI
bool CUI_ID_FRAME_ActivityList::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ActivityList.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ActivityList.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ActivityList::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ActivityList, s_CUI_ID_FRAME_ActivityListOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ActivityList, s_CUI_ID_FRAME_ActivityListOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ActivityList, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_ActivityListID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityList, ID_BUTTON_Help, s_CUI_ID_FRAME_ActivityListID_BUTTON_HelpOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_ActivityList, ID_BUTTON_ActivityLvl, s_CUI_ID_FRAME_ActivityListID_BUTTON_ActivityLvlOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityList, ID_BUTTON_ActivityTime, s_CUI_ID_FRAME_ActivityListID_BUTTON_ActivityTimeOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityList, ID_BUTTON_ActivityName, s_CUI_ID_FRAME_ActivityListID_BUTTON_ActivityNameOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityList, ID_BUTTON_ActivityMap, s_CUI_ID_FRAME_ActivityListID_BUTTON_ActivityMapOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityList, ID_BUTTON_PlayerLvl, s_CUI_ID_FRAME_ActivityListID_BUTTON_PlayerLvlOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityList, ID_BUTTON_Finish, s_CUI_ID_FRAME_ActivityListID_BUTTON_FinishOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityList, ID_BUTTON_State, s_CUI_ID_FRAME_ActivityListID_BUTTON_StateOnButtonClick );
// 	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityList, ID_CHECKBOX_Activity, s_CUI_ID_FRAME_ActivityListID_CHECKBOX_ActivityOnCheckBoxCheck );
// 	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityList, ID_CHECKBOX_Task, s_CUI_ID_FRAME_ActivityListID_CHECKBOX_TaskOnCheckBoxCheck );
	theUiManager.OnIconDragOn( ID_FRAME_ActivityList, ID_LISTIMG_Encouragement, s_CUI_ID_FRAME_ActivityListID_LISTIMG_EncouragementOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_ActivityList, ID_LISTIMG_Encouragement, s_CUI_ID_FRAME_ActivityListID_LISTIMG_EncouragementOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_ActivityList, ID_LISTIMG_Encouragement, s_CUI_ID_FRAME_ActivityListID_LISTIMG_EncouragementOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_ActivityList, ID_LISTIMG_Encouragement, s_CUI_ID_FRAME_ActivityListID_LISTIMG_EncouragementOnIconRButtonUp );
	//theUiManager.OnListSelectChange( ID_FRAME_ActivityList, ID_LIST_ActivityLvl, s_CUI_ID_FRAME_ActivityListID_LIST_ActivityLvlOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_ActivityList, ID_LIST_ActivityTime, s_CUI_ID_FRAME_ActivityListID_LIST_ActivityTimeOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_ActivityList, ID_LIST_ActivityName, s_CUI_ID_FRAME_ActivityListID_LIST_ActivityNameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_ActivityList, ID_LIST_ActivityMap, s_CUI_ID_FRAME_ActivityListID_LIST_ActivityMapOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_ActivityList, ID_LIST_PlayerLvl, s_CUI_ID_FRAME_ActivityListID_LIST_PlayerLvlOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_ActivityList, ID_LIST_Finish, s_CUI_ID_FRAME_ActivityListID_LIST_FinishOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_ActivityList, ID_LIST_State, s_CUI_ID_FRAME_ActivityListID_LIST_StateOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_ActivityList, ID_LIST_ActivityList, s_CUI_ID_FRAME_ActivityListID_LIST_ActivityListOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_ActivityList, ID_BUTTON_ActivityDate, s_CUI_ID_FRAME_ActivityListID_BUTTON_ActivityDateOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_ActivityList, ID_LIST_ActivityDate, s_CUI_ID_FRAME_ActivityListID_LIST_ActivityDateOnListSelectChange );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityList, ID_CHECKBOX_Show2H, s_CUI_ID_FRAME_ActivityListID_CHECKBOX_Show2HOnCheckBoxCheck );
// 	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityList, ID_CHECKBOX_WeekTask, s_CUI_ID_FRAME_ActivityListID_CHECKBOX_WeekTaskOnCheckBoxCheck );
// 	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityList, ID_CHECKBOX_AllTask, s_CUI_ID_FRAME_ActivityListID_CHECKBOX_AllTaskOnCheckBoxCheck );
    theUiManager.OnIconDragOn( ID_FRAME_ActivityList, ID_LISTIMG_Reward, s_CUI_ID_FRAME_ActivityListID_LISTIMG_RewardOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_ActivityList, ID_LISTIMG_Reward, s_CUI_ID_FRAME_ActivityListID_LISTIMG_RewardOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_ActivityList, ID_LISTIMG_Reward, s_CUI_ID_FRAME_ActivityListID_LISTIMG_RewardOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_ActivityList, ID_LISTIMG_Reward, s_CUI_ID_FRAME_ActivityListID_LISTIMG_RewardOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_ActivityList, ID_BUTTON_ActivityTime2, s_CUI_ID_FRAME_ActivityListID_BUTTON_ActivityTime2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityList, ID_BUTTON_ActivityName2, s_CUI_ID_FRAME_ActivityListID_BUTTON_ActivityName2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityList, ID_BUTTON_ActivityMap2, s_CUI_ID_FRAME_ActivityListID_BUTTON_ActivityMap2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityList, ID_BUTTON_PlayerLvl2, s_CUI_ID_FRAME_ActivityListID_BUTTON_PlayerLvl2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityList, ID_BUTTON_Finish2, s_CUI_ID_FRAME_ActivityListID_BUTTON_Finish2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityList, ID_BUTTON_Reward2, s_CUI_ID_FRAME_ActivityListID_BUTTON_Reward2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityList, ID_BUTTON_ActivityDate2, s_CUI_ID_FRAME_ActivityListID_BUTTON_ActivityDate2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityList, ID_BUTTON_State2, s_CUI_ID_FRAME_ActivityListID_BUTTON_State2OnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_ActivityList, ID_LIST_ActivityList2, s_CUI_ID_FRAME_ActivityListID_LIST_ActivityList2OnListSelectChange );
	//theUiManager.OnIconDragOn( ID_FRAME_ActivityList, ID_LISTIMG_Reward2, s_CUI_ID_FRAME_ActivityListID_LISTIMG_Reward2OnIconDragOn );
	//theUiManager.OnIconLDBClick( ID_FRAME_ActivityList, ID_LISTIMG_Reward2, s_CUI_ID_FRAME_ActivityListID_LISTIMG_Reward2OnIconLDBClick );
	//theUiManager.OnIconButtonClick( ID_FRAME_ActivityList, ID_LISTIMG_Reward2, s_CUI_ID_FRAME_ActivityListID_LISTIMG_Reward2OnIconButtonClick );
	//theUiManager.OnIconRButtonUp( ID_FRAME_ActivityList, ID_LISTIMG_Reward2, s_CUI_ID_FRAME_ActivityListID_LISTIMG_Reward2OnIconRButtonUp );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityList, ID_CHECKBOX_ActivityTrack, s_CUI_ID_FRAME_ActivityListID_CHECKBOX_ActivityTrackOnCheckBoxCheck );
  //  theUiManager.OnListSelectChange( ID_FRAME_ActivityList, ID_LIST_ActivityHot, s_CUI_ID_FRAME_ActivityListID_LIST_ActivityHotOnListSelectChange );
    theUiManager.OnListSelectChange( ID_FRAME_ActivityList, ID_LIST_ActivityHot2, s_CUI_ID_FRAME_ActivityListID_LIST_ActivityHot2OnListSelectChange );
//     theUiManager.OnListSelectChange( ID_FRAME_ActivityList, ID_LIST_ActivityTip, s_CUI_ID_FRAME_ActivityListID_LIST_ActivityTipOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_ActivityList, ID_LIST_ActivityTip2, s_CUI_ID_FRAME_ActivityListID_LIST_ActivityTip2OnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_ActivityList, ID_BUTTON_Day, s_CUI_ID_FRAME_ActivityListID_BUTTON_DayOnButtonClick );

	
	m_pID_FRAME_ActivityList = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ActivityList );

	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityList, ID_CHECKBOX_EveryDay, s_CUI_ID_FRAME_ActivityListID_CHECKBOX_EveryDayOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityList, ID_CHECKBOX_Country, s_CUI_ID_FRAME_ActivityListID_CHECKBOX_CountryOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityList, ID_CHECKBOX_Ectype, s_CUI_ID_FRAME_ActivityListID_CHECKBOX_EctypeOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityList, ID_CHECKBOX_Family, s_CUI_ID_FRAME_ActivityListID_CHECKBOX_FamilyOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityList, ID_CHECKBOX_Welfare, s_CUI_ID_FRAME_ActivityListID_CHECKBOX_WelfareOnCheckBoxCheck );

	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityList, ID_CHECKBOX_LeaveExp, s_CUI_ID_FRAME_ActivityListID_CHECKBOX_LeaveExpOnCheckBoxCheck );

// 	m_pID_PICTURE_TitleDi = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_PICTURE_TitleDi );
// 	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_Title );
// 	m_pID_PICTURE_TitleLeftMiddle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_PICTURE_TitleLeftMiddle );
// 	m_pID_PICTURE_TitleRightMiddle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_PICTURE_TitleRightMiddle );
// 	m_pID_PICTURE_TitleLeft = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_PICTURE_TitleLeft );
// 	m_pID_PICTURE_TitleRight = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_PICTURE_TitleRight );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_BUTTON_CLOSE );
// 	m_pID_BUTTON_Help = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_BUTTON_Help );
// 	m_pID_PICTURE_14866 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_PICTURE_14866 );
	m_pID_TEXT_Time = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_Time );
// 	m_pID_PICTURE_Wall1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_PICTURE_Wall1 );
// 	m_pID_PICTURE_Wall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_PICTURE_Wall2 );
// 	m_pID_BUTTON_ActivityLvl = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_BUTTON_ActivityLvl );
	m_pID_BUTTON_ActivityTime = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_BUTTON_ActivityTime );
	m_pID_BUTTON_ActivityName = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_BUTTON_ActivityName );
	m_pID_BUTTON_ActivityMap = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_BUTTON_ActivityMap );
	m_pID_BUTTON_PlayerLvl = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_BUTTON_PlayerLvl );
	m_pID_BUTTON_Finish = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_BUTTON_Finish );
	m_pID_BUTTON_State = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_BUTTON_State );
	m_pID_TEXT_ActivityNameZ = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ActivityNameZ );
	m_pID_TEXT_PlayerLvlZ = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_PlayerLvlZ );
	m_pID_TEXT_ActivityTimeZ = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ActivityTimeZ );
	m_pID_TEXT_ActivityNpcZ = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ActivityNpcZ );
	m_pID_TEXT_ActivityInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ActivityInfo );
// 	m_pID_CHECKBOX_Activity = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_CHECKBOX_Activity );
// 	m_pID_CHECKBOX_Task = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_CHECKBOX_Task );
	m_pID_TEXT_ActivityInfoZ = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ActivityInfoZ );
	m_pID_TEXT_Encouragement = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_Encouragement );
	m_pID_LISTIMG_Encouragement = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LISTIMG_Encouragement );
	m_pID_TEXT_ActivityName = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ActivityName );
	m_pID_TEXT_PlayerLvl = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_PlayerLvl );
	m_pID_TEXT_ActivityTime = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ActivityTime );
	m_pID_TEXT_ActivityNpc = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ActivityNpc );
	//m_pID_LIST_ActivityLvl = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_ActivityLvl );
	m_pID_LIST_ActivityTime = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_ActivityTime );
	m_pID_LIST_ActivityName = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_ActivityName );
	m_pID_LIST_ActivityMap = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_ActivityMap );
	m_pID_LIST_PlayerLvl = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_PlayerLvl );
	m_pID_LIST_Finish = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_Finish );
	m_pID_LIST_State = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_State );
	m_pID_LIST_ActivityList = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_ActivityList );
	m_pID_BUTTON_ActivityDate = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_BUTTON_ActivityDate );
	m_pID_LIST_ActivityDate = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_ActivityDate );
	m_pID_CHECKBOX_Show2H = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_CHECKBOX_Show2H );
// 	m_pID_CHECKBOX_WeekTask = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_CHECKBOX_WeekTask );
// 	m_pID_CHECKBOX_AllTask = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_CHECKBOX_AllTask );
// 	m_pID_TEXT_ArrowActivityLvl = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ArrowActivityLvl );
	m_pID_TEXT_ArrowActivityDate = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ArrowActivityDate );
	m_pID_TEXT_ArrowActivityTime = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ArrowActivityTime );
	m_pID_TEXT_ArrowActivityName = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ArrowActivityName );
	m_pID_TEXT_ArrowActivityMap = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ArrowActivityMap );
	m_pID_TEXT_ArrowPlayerLvl = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ArrowPlayerLvl );
	m_pID_TEXT_ArrowFinish = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ArrowFinish );
	m_pID_TEXT_ArrowState = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ArrowState );
	m_pID_LISTIMG_Reward = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LISTIMG_Reward );
	m_pID_BUTTON_ActivityTime2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_BUTTON_ActivityTime2 );
	m_pID_BUTTON_ActivityName2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_BUTTON_ActivityName2 );
	m_pID_BUTTON_ActivityMap2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_BUTTON_ActivityMap2 );
	m_pID_BUTTON_PlayerLvl2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_BUTTON_PlayerLvl2 );
	m_pID_BUTTON_Finish2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_BUTTON_Finish2 );
	m_pID_BUTTON_Reward2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_BUTTON_Reward2 );
	m_pID_BUTTON_ActivityDate2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_BUTTON_ActivityDate2 );
	m_pID_BUTTON_State2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_BUTTON_State2 );
	m_pID_LIST_ActivityList2 = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_ActivityList2 );
	//m_pID_LIST_ActivityTime2 = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_ActivityTime2 );
	m_pID_LIST_ActivityName2 = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_ActivityName2 );

    m_pID_LIST_ActivityStart = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_ActivityStart );

	m_pID_LIST_ActivityMap2 = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_ActivityMap2 );
	m_pID_LIST_PlayerLvl2 = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_PlayerLvl2 );
	m_pID_LIST_Finish2 = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_Finish2 );
	m_pID_LIST_State2 = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_State2 );
	m_pID_LIST_ActivityDate2 = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_ActivityDate2 );
	//m_pID_LISTIMG_Reward2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LISTIMG_Reward2 );
	m_pID_TEXT_ArrowActivityDate2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ArrowActivityDate2 );
	m_pID_TEXT_ArrowActivityTime2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ArrowActivityTime2 );
	m_pID_TEXT_ArrowActivityName2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ArrowActivityName2 );
	m_pID_TEXT_ArrowActivityMap2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ArrowActivityMap2 );
	m_pID_TEXT_ArrowPlayerLvl2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ArrowPlayerLvl2 );
	m_pID_TEXT_ArrowFinish2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ArrowFinish2 );
	m_pID_TEXT_ArrowReward2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ArrowReward2 );
	m_pID_TEXT_ArrowState2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_ArrowState2 );
	m_pID_TEXT_21270 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_21270 );
	m_pID_TEXT_212702 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_TEXT_212702 );
	m_pID_CHECKBOX_ActivityTrack = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_CHECKBOX_ActivityTrack );
  //  m_pID_LIST_ActivityHot = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_ActivityHot );
    m_pID_LIST_ActivityHot2 = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_ActivityHot2 );
//    m_pID_LIST_ActivityTip = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_ActivityTip );
    m_pID_LIST_ActivityTip2 = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_ActivityTip2 );

	m_pID_LIST_ActivityType		= (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_ActivityType );
	//m_pID_LIST_ActivityType2	= (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_LIST_ActivityType2 );

	m_pID_CHECKBOX_EveryDay = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_CHECKBOX_EveryDay );
	m_pID_CHECKBOX_Country = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_CHECKBOX_Country );
	m_pID_CHECKBOX_Ectype = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_CHECKBOX_Ectype );
	m_pID_CHECKBOX_Family = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_CHECKBOX_Family );
	m_pID_CHECKBOX_Welfare = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_CHECKBOX_Welfare );
	m_pID_CHECKBOX_LeaveExp = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityList, ID_CHECKBOX_LeaveExp );
	
	assert( m_pID_CHECKBOX_EveryDay );
	assert( m_pID_CHECKBOX_Country );
	assert( m_pID_CHECKBOX_Ectype );
	assert( m_pID_CHECKBOX_Family );
	assert( m_pID_CHECKBOX_Welfare );
	assert( m_pID_CHECKBOX_LeaveExp );
	m_tabGroup.Clear();
	m_listGroup.Clear();

	m_tabGroup.AddPage( m_pID_CHECKBOX_EveryDay, &m_listGroup );
	m_tabGroup.AddPage( m_pID_CHECKBOX_Country, &m_listGroup );
	m_tabGroup.AddPage( m_pID_CHECKBOX_Ectype, &m_listGroup );
	m_tabGroup.AddPage( m_pID_CHECKBOX_Family, &m_listGroup );
	m_tabGroup.AddPage( m_pID_CHECKBOX_Welfare, &m_listGroup );
	m_tabGroup.AddPage( m_pID_CHECKBOX_LeaveExp, &m_listGroup );

	m_CheckCtrl[0] = m_pID_CHECKBOX_EveryDay;
	m_CheckCtrl[1] = m_pID_CHECKBOX_Country;
	m_CheckCtrl[2] = m_pID_CHECKBOX_Ectype;
	m_CheckCtrl[3] = m_pID_CHECKBOX_Family;
	m_CheckCtrl[4] = m_pID_CHECKBOX_Welfare;
	

   // assert( m_pID_LIST_ActivityHot );
    assert( m_pID_LIST_ActivityHot2 );
  //  assert(m_pID_LIST_ActivityTip);
    assert(m_pID_LIST_ActivityTip2);

	assert( m_pID_LIST_ActivityType );
	//assert( m_pID_LIST_ActivityType2 );

    m_pID_CHECKBOX_ActivityTrack->SetCheck(true);
    
    m_pCurrActivityList = m_pID_LIST_ActivityList;

	//m_pID_TEXT_Arrow[ESLvl] = m_pID_TEXT_ArrowActivityLvl;
	m_pID_TEXT_Arrow[ESDate] = m_pID_TEXT_ArrowActivityDate;
	m_pID_TEXT_Arrow[ESTime] = m_pID_TEXT_ArrowActivityTime;
	m_pID_TEXT_Arrow[ESName] = m_pID_TEXT_ArrowActivityName;
	m_pID_TEXT_Arrow[ESMap] = m_pID_TEXT_ArrowActivityMap;
	m_pID_TEXT_Arrow[ESPlayerLvl] = m_pID_TEXT_ArrowPlayerLvl;
	m_pID_TEXT_Arrow[ESFinish] = m_pID_TEXT_ArrowFinish;
	m_pID_TEXT_Arrow[ESState] = m_pID_TEXT_ArrowState;

	m_pID_TEXT_Arrow2[ESDate] = m_pID_TEXT_ArrowActivityDate2;
	m_pID_TEXT_Arrow2[ESTime] = m_pID_TEXT_ArrowActivityTime2;
	m_pID_TEXT_Arrow2[ESName] = m_pID_TEXT_ArrowActivityName2;
	m_pID_TEXT_Arrow2[ESMap] = m_pID_TEXT_ArrowActivityMap2;
	m_pID_TEXT_Arrow2[ESPlayerLvl] = m_pID_TEXT_ArrowPlayerLvl2;
	m_pID_TEXT_Arrow2[ESFinish] = m_pID_TEXT_ArrowFinish2;
	m_pID_TEXT_Arrow2[ESState] = m_pID_TEXT_ArrowState2;

	//InitialChildList( m_pID_LIST_ActivityLvl );
	InitialChildList( m_pID_LIST_ActivityTime );
	InitialChildList( m_pID_LIST_ActivityName );
	InitialChildList( m_pID_LIST_ActivityMap );
	InitialChildList( m_pID_LIST_PlayerLvl );
	InitialChildList( m_pID_LIST_Finish );
	InitialChildList( m_pID_LIST_State );
	InitialChildList( m_pID_LIST_ActivityDate );

	//InitialChildList( m_pID_LIST_ActivityTime2 );
	InitialChildList( m_pID_LIST_ActivityName2 );
	InitialChildList(m_pID_LIST_ActivityStart);
	InitialChildList( m_pID_LIST_ActivityMap2 );
	InitialChildList( m_pID_LIST_PlayerLvl2 );
	InitialChildList( m_pID_LIST_Finish2 );
	InitialChildList( m_pID_LIST_State2 );
	InitialChildList( m_pID_LIST_ActivityDate2 );

  //  InitialChildList(m_pID_LIST_ActivityHot);
    InitialChildList(m_pID_LIST_ActivityHot2);
    //InitialChildList(m_pID_LIST_ActivityTip);
    InitialChildList(m_pID_LIST_ActivityTip2);

//     m_pID_LIST_ActivityTip->SetMsgHoldup(true);
//     m_pID_LIST_ActivityTip->setShowTip();
    m_pID_LIST_ActivityTip2->SetMsgHoldup(true);
    m_pID_LIST_ActivityTip2->setShowTip();

	m_pID_LIST_ActivityList->SetLDBClickFun(ID_LIST_ActivityListOnListLDBClick);
	m_pID_LIST_ActivityList2->SetLDBClickFun(ID_LIST_ActivityListOnListLDBClick);

	m_pID_LISTIMG_Encouragement->SetCanbePick(false);
	m_pID_LISTIMG_Encouragement->ShowPressEffect(false);

    m_pID_LISTIMG_Reward->SetCanbePick(false);
    m_pID_LISTIMG_Reward->ShowPressEffect(false);
	m_pID_LISTIMG_Reward->SetMsgHoldup(false);	//不接受消息

	//m_pID_LISTIMG_Reward2->SetCanbePick(false);
	//m_pID_LISTIMG_Reward2->ShowPressEffect(false);
	//m_pID_LISTIMG_Reward2->SetMsgHoldup(false);	//不接受消息
	m_pID_CHECKBOX_ActivityTrack->SetCheck( true );

// 	m_pID_TEXT_ActivityNpc->SetHyberClickFun(ID_TEXT_ActivityNpc_HyberClick);

	m_pID_LIST_ActivityType->SetMsgHoldup(false);	//不接受消息
	m_pID_LIST_ActivityType->HaveSelBar( false );	//没有绿色cur选中地图
	m_pID_LIST_ActivityType->SetCurSelIndex(-1);
	m_pID_LIST_ActivityType->SetDrawFlags(DT_CENTER|DT_NOCLIP);

	//m_pID_LIST_ActivityType2->SetMsgHoldup(false);	//不接受消息
	//m_pID_LIST_ActivityType2->HaveSelBar( false );	//没有绿色cur选中地图
	//m_pID_LIST_ActivityType2->SetCurSelIndex(-1);
	//m_pID_LIST_ActivityType2->SetDrawFlags(DT_CENTER|DT_NOCLIP);

	_SetVisable( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ActivityList::_UnLoadUI()
{
	m_pID_FRAME_ActivityList = NULL;

//     m_pID_PICTURE_TitleDi = NULL;
//     m_pID_TEXT_Title = NULL;
//     m_pID_PICTURE_TitleLeftMiddle = NULL;
//     m_pID_PICTURE_TitleRightMiddle = NULL;
//     m_pID_PICTURE_TitleLeft = NULL;
//     m_pID_PICTURE_TitleRight = NULL;
    m_pID_BUTTON_CLOSE = NULL;
//     m_pID_BUTTON_Help = NULL;
//     m_pID_PICTURE_14866 = NULL;
    m_pID_TEXT_Time = NULL;
//     m_pID_PICTURE_Wall1 = NULL;
//     m_pID_PICTURE_Wall2 = NULL;
//     m_pID_BUTTON_ActivityLvl = NULL;
    m_pID_BUTTON_ActivityTime = NULL;
    m_pID_BUTTON_ActivityName = NULL;
    m_pID_BUTTON_ActivityMap = NULL;
    m_pID_BUTTON_PlayerLvl = NULL;
    m_pID_BUTTON_Finish = NULL;
    m_pID_BUTTON_State = NULL;
    m_pID_TEXT_ActivityNameZ = NULL;
    m_pID_TEXT_PlayerLvlZ = NULL;
    m_pID_TEXT_ActivityTimeZ = NULL;
    m_pID_TEXT_ActivityNpcZ = NULL;
    m_pID_TEXT_ActivityInfo = NULL;
//     m_pID_CHECKBOX_Activity = NULL;
//     m_pID_CHECKBOX_Task = NULL;
    m_pID_TEXT_ActivityInfoZ = NULL;
    m_pID_TEXT_Encouragement = NULL;
    m_pID_LISTIMG_Encouragement = NULL;
    m_pID_TEXT_ActivityName = NULL;
    m_pID_TEXT_PlayerLvl = NULL;
    m_pID_TEXT_ActivityTime = NULL;
    m_pID_TEXT_ActivityNpc = NULL;
    //m_pID_LIST_ActivityLvl = NULL;
    m_pID_LIST_ActivityTime = NULL;
    m_pID_LIST_ActivityName  = NULL;
    m_pID_LIST_ActivityMap = NULL;
    m_pID_LIST_PlayerLvl = NULL;
    m_pID_LIST_Finish = NULL;
    m_pID_LIST_State = NULL;
    m_pID_LIST_ActivityList = NULL;
    m_pID_BUTTON_ActivityDate = NULL;
    m_pID_LIST_ActivityDate = NULL;
    m_pID_CHECKBOX_Show2H = NULL;
//     m_pID_CHECKBOX_WeekTask = NULL;
//     m_pID_CHECKBOX_AllTask = NULL;
//     m_pID_TEXT_ArrowActivityLvl = NULL;
    m_pID_TEXT_ArrowActivityDate = NULL;
    m_pID_TEXT_ArrowActivityTime = NULL;
    m_pID_TEXT_ArrowActivityName = NULL;
    m_pID_TEXT_ArrowActivityMap = NULL;
    m_pID_TEXT_ArrowPlayerLvl = NULL;
    m_pID_TEXT_ArrowFinish = NULL;
    m_pID_TEXT_ArrowState = NULL;
    m_pID_LISTIMG_Reward  = NULL;
    m_pID_BUTTON_ActivityTime2 = NULL;
    m_pID_BUTTON_ActivityName2 = NULL;
    m_pID_BUTTON_ActivityMap2 = NULL;
    m_pID_BUTTON_PlayerLvl2 = NULL;
    m_pID_BUTTON_Finish2 = NULL;
    m_pID_BUTTON_Reward2 = NULL;
    m_pID_BUTTON_ActivityDate2 = NULL;
    m_pID_BUTTON_State2 = NULL;
    m_pID_LIST_ActivityList2 = NULL;
    //m_pID_LIST_ActivityTime2 = NULL;
    m_pID_LIST_ActivityName2 = NULL;
	m_pID_LIST_ActivityStart = NULL;
    m_pID_LIST_ActivityMap2 = NULL;
    m_pID_LIST_PlayerLvl2 = NULL;
    m_pID_LIST_Finish2 = NULL;
    m_pID_LIST_State2 = NULL;
    m_pID_LIST_ActivityDate2 = NULL;
    //m_pID_LISTIMG_Reward2 = NULL;
    m_pID_TEXT_ArrowActivityDate2 = NULL;
    m_pID_TEXT_ArrowActivityTime2 = NULL;
    m_pID_TEXT_ArrowActivityName2 = NULL;
    m_pID_TEXT_ArrowActivityMap2 = NULL;
    m_pID_TEXT_ArrowPlayerLvl2 = NULL;
    m_pID_TEXT_ArrowFinish2 = NULL;
    m_pID_TEXT_ArrowReward2 = NULL;
    m_pID_TEXT_ArrowState2 = NULL;
    m_pID_TEXT_21270 = NULL;
    m_pID_TEXT_212702 = NULL;
    m_pID_CHECKBOX_ActivityTrack = NULL;
  //  m_pID_LIST_ActivityHot = NULL;
    m_pID_LIST_ActivityHot2 = NULL;
//     m_pID_LIST_ActivityTip = NULL;
    m_pID_LIST_ActivityTip2 = NULL;

	m_pID_LIST_ActivityType = NULL;
	//m_pID_LIST_ActivityType2= NULL;

	m_pID_CHECKBOX_EveryDay = NULL;
	m_pID_CHECKBOX_Country = NULL;
	m_pID_CHECKBOX_Ectype = NULL;
	m_pID_CHECKBOX_Family = NULL;
	m_pID_CHECKBOX_Welfare = NULL;
	m_pID_CHECKBOX_LeaveExp = NULL;

	return theUiManager.RemoveFrame( "Data\\UI\\ActivityList.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_ActivityList::_IsVisable()
{
	if( !m_pID_FRAME_ActivityList )
		return false;
	return m_pID_FRAME_ActivityList->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ActivityList::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_ActivityList )
		return;
	m_pID_FRAME_ActivityList->SetVisable( bVisable );

	if (bVisable)
	{
		Refresh(m_CurrentType);
		if(m_pID_CHECKBOX_LeaveExp->IsChecked())
		{
			s_CUI_ID_FRAME_LeaveExp.OnShow();
		}
	}
}

void CUI_ID_FRAME_ActivityList::Refresh(int type)
{
	//m_pID_LIST_ActivityLvl->Clear();
	m_pID_LIST_ActivityTime->Clear();
	m_pID_LIST_ActivityName->Clear();
	m_pID_LIST_ActivityMap->Clear();
	m_pID_LIST_PlayerLvl->Clear();
	m_pID_LIST_Finish->Clear();
	m_pID_LIST_State->Clear();
	m_pID_LIST_ActivityList->Clear();
	m_pID_LIST_ActivityDate->Clear();
	s_sortEvtContents.clear();
	m_pID_LISTIMG_Reward->Clear();
	//m_pID_LIST_ActivityTime2->Clear();
	m_pID_LIST_ActivityName2->Clear();
	m_pID_LIST_ActivityStart->Clear();
	m_pID_LIST_ActivityMap2->Clear();
	m_pID_LIST_PlayerLvl2->Clear();
	m_pID_LIST_Finish2->Clear();
	m_pID_LIST_State2->Clear();
	m_pID_LIST_ActivityList2->Clear();
	m_pID_LIST_ActivityDate2->Clear();
	s_sortHotEvtContents.clear();
    //m_pID_LISTIMG_Reward2->Clear();

   // m_pID_LIST_ActivityHot->Clear();
    m_pID_LIST_ActivityHot2->Clear();
//     m_pID_LIST_ActivityTip->Clear();
    m_pID_LIST_ActivityTip2->Clear();

	m_pID_LIST_ActivityType->Clear();
	//m_pID_LIST_ActivityType2->Clear();
	m_CurrentType = type;
	{
		const EventContents& contents = EventManager::Instance().GetHotEventContents();
		for (int i = 0; i < contents.size(); ++i)
		{
			Event* content = const_cast<Event*>(&contents[i]);
			if (/*content->needLevel > thePlayerRole.GetLevel() ||*/ 
				(content->country!=CountryDefine::Country_Init && content->country!=thePlayerRole.GetCountry()) ||
				content->category!=type)
				continue;

			if (m_pID_CHECKBOX_Show2H->IsChecked())
			{
				if (GetEventStatus(*content, nowtime) == ES_Start ||
					GetEventStatus(*content, nowtime) == ES_Ready)
					s_sortEvtContents.push_back(content);
			}
			else
				s_sortEvtContents.push_back(content);
		}
	}

	{
		const EventContents& contents = EventManager::Instance().GetEverydayEventContents();
		for (int i = 0; i < contents.size(); ++i)
		{
			Event* content = const_cast<Event*>(&contents[i]);
			if (/*content->needLevel > thePlayerRole.GetLevel() || */
				(content->country != CountryDefine::Country_Init && content->country!=thePlayerRole.GetCountry()) ||
				content->category != type)
				continue;

			if (m_pID_CHECKBOX_Show2H->IsChecked())
			{
				if (GetEventStatus(*content, nowtime) == ES_Start ||
					GetEventStatus(*content, nowtime) == ES_Ready)
					s_sortHotEvtContents.push_back(content);
			}
			else
				s_sortHotEvtContents.push_back(content);
		}
	}

	{
		s_eventContents.clear();

		EventManager::Instance().GetMonthEventContents(nowtime, s_eventContents);

		struct tm nowtime = s_CUI_ID_FRAME_ActivityList.GetNowtime();

		for(int i=0;i<s_eventContents.size();++i)
		{
			if (/*s_eventContents[i].needLevel > thePlayerRole.GetLevel() || */
				(s_eventContents[i].country!=CountryDefine::Country_Init && s_eventContents[i].country!=thePlayerRole.GetCountry()) ||
				s_eventContents[i].category != type)
				continue;
			if(/*s_eventContents[i].day == nowtime.tm_mday*/1)
			{
				bool have = false;
				for(int j=0;j<s_sortHotEvtContents.size();++j)
				{
					if(s_sortHotEvtContents[j]->name == s_eventContents[i].name)
					{
						/*if(s_sortHotEvtContents[j]->endHour==s_eventContents[i].endHour
							&&s_sortHotEvtContents[j]->endMinute==s_eventContents[i].endMinute
							&&s_sortHotEvtContents[j]->duration==s_eventContents[i].duration)*/
						{
							have = true;
							break;
						}
					}
				}

				if(!have)
				{
					Event* content = const_cast<Event*>(&s_eventContents[i]);
					s_sortHotEvtContents.push_back(content);
				}
			}
		}
	}

	char buf[128];

	std::sort(s_sortEvtContents.begin(), s_sortEvtContents.end(), EventSortFunc);
	if( 5 == m_CurrentType )
		std::sort(s_sortHotEvtContents.begin(), s_sortHotEvtContents.end(), SortByPeriod);

	for (int i = 0; i < s_sortEvtContents.size(); ++i)
	{
		const Event& content = *s_sortEvtContents[i];

		ControlList::S_List	stItem;

		stItem.SetData( "" );
		m_pID_LIST_ActivityList->AddItem( &stItem,NULL, false);

		// period
		stItem.SetData( content.period.c_str() );
		m_pID_LIST_ActivityDate->AddItem(&stItem,NULL, false);

		// time
		MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, "%02d:%02d - %02d:%02d", content.hour, content.minute, content.endHour, content.endMinute);
		stItem.SetData( buf );
		m_pID_LIST_ActivityTime->AddItem(&stItem,NULL, false);

		// name
		stItem.SetData( content.name.c_str() );
		m_pID_LIST_ActivityName->AddItem(&stItem,NULL, false);


		// ActivityTypeStr
		const char* tempAc = EventManager::Instance().GetActivityTypeStr( content.mActivityType );
		if ( tempAc )
		{
			stItem.SetData( tempAc );
			m_pID_LIST_ActivityType->AddItem(&stItem, false);
		}
		else
		{
			stItem.SetData( "" );
			m_pID_LIST_ActivityType->AddItem(&stItem, false);
		}

		// map
		stItem.SetData( content.mapName.c_str() );
		m_pID_LIST_ActivityMap->AddItem(&stItem,NULL, false);

		// player level
		MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, "%d", content.needLevel);
		if (content.needLevel > thePlayerRole.GetLevel())
			stItem.SetData( buf, 0, 0, D3DCOLOR_XRGB(255,0,0) );
		else
			stItem.SetData( buf );
		m_pID_LIST_PlayerLvl->AddItem(&stItem,NULL, false);

		// count
		if (content.count == -1)
		{
			stItem.SetData( "" );
			m_pID_LIST_Finish->AddItem(&stItem,NULL, false);
		}
		else
		{
			MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, "%d/%d", thePlayerRole.GetVariableValue(content.completeTimeVarIndex), content.count);
			stItem.SetData( buf );
			m_pID_LIST_Finish->AddItem(&stItem,NULL, false);
		}

		// status
		int status = GetEventStatus(content, nowtime);
		if (status == ES_Start) // 进行中
			stItem.SetData( "{#1026}" );
		else if (status == ES_Close) // 关闭
			stItem.SetData( "{#1029}" );
		else if (status == ES_Finish) // 完成
			stItem.SetData( "{#1028}" );
		else if (status == ES_Ready)
			stItem.SetData( "{#1027}" );
		else // 未开始
			stItem.SetData( "" );
		m_pID_LIST_State->AddItem(&stItem,NULL, false);

        // reward
        int nRowItemCount = m_pID_LISTIMG_Reward->GetRowItemCnt();
        for (int j = 0; j < content.rewards.size(); ++j)
        {
            ControlIconDrag::S_ListImg stImgItem;
            stImgItem.SetData( content.rewards[j].id, content.rewards[j].count, eIcon_Enable, true );
            stImgItem.m_pkIconInfo->SetUsableEffEnable( false );
            m_pID_LISTIMG_Reward->SetItem(&stImgItem, i*nRowItemCount+j);
        }

        if(content.isPivot)
          stItem.SetData("{#1021}");
        else
          stItem.SetData("");
      //  m_pID_LIST_ActivityHot->AddItem(&stItem,NULL,false);

        if(content.isPivot)
        {
            stItem.SetData("");
//             S_BaseData* pData = m_pID_LIST_ActivityTip->GetData();
//             if(pData != NULL)
//             {
//                 stItem.setIsOnline(true);
//                 stItem.setTip(pData->m_szCaption);
//             }
        }

       // m_pID_LIST_ActivityTip->AddItem(&stItem,NULL,false);
	}

	for (int i = 0; i < s_sortHotEvtContents.size(); ++i)
	{
		const Event& content = *s_sortHotEvtContents[i];

		ControlList::S_List	stItem;

		stItem.SetData( "" );
		m_pID_LIST_ActivityList2->AddItem( &stItem,NULL, false);

		// period
		stItem.SetData( content.period.c_str() );
		m_pID_LIST_ActivityDate2->AddItem(&stItem,NULL, false);

		// time		
		/*
		 * Author: 2012-9-17 17:03:25 liaojie
		 * Desc:   根据需求修改活动面板显示内容
		 */
		/*MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, "%02d:%02d - %02d:%02d", content.hour, content.minute, content.endHour, content.endMinute);
		stItem.SetData( buf );
		m_pID_LIST_ActivityTime2->AddItem(&stItem,NULL, false);*/

		// name
		stItem.SetData( content.name.c_str() );
		m_pID_LIST_ActivityName2->AddItem(&stItem,NULL, false);


		// 插入星级
		const char* gStarStr[] = {
			"{#SSSS0}",
			"{#SSSS1}",
			"{#SSSS2}",
			"{#SSSS3}",
			"{#SSSS4}"
		};

		if ( content.quality >= 1 && content.quality <= 5 )
		{
			stItem.SetData( gStarStr[content.quality - 1] );
			m_pID_LIST_ActivityStart->AddItem( &stItem, NULL, false);
		}
		else
		{
			// 防止策划填错了，加个空的在里面
			ControlList::S_List	temp;
			temp.SetData("");
			m_pID_LIST_ActivityStart->AddItem( &temp, NULL, false);
		}
		

		// ActivityTypeStr
		/*
		 * Author: 2012-9-17 17:04:33 liaojie
		 * Desc:   根据需求修改活动面板显示内容
		 */
		/*const char* tempAc = EventManager::Instance().GetActivityTypeStr( content.mActivityType );
		if ( tempAc )
		{
			stItem.SetData( tempAc );
			m_pID_LIST_ActivityType2->AddItem(&stItem, false);
		}
		else
		{
			stItem.SetData( "" );
			m_pID_LIST_ActivityType2->AddItem(&stItem, false);
		}*/

		// map
		//名字中 发现 有: 则去掉该
		size_t pos = 0;
		if(pos = content.mapName.find(":") != std::string::npos)
		{
			std::string _subStr = content.mapName.substr(pos+2);
			stItem.SetData( _subStr.c_str() );
		}else
		{
          stItem.SetData( content.mapName.c_str() );
		}
		
		m_pID_LIST_ActivityMap2->AddItem(&stItem,NULL, false);

		// player level
		MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, "%d", content.needLevel);
		if (content.needLevel > thePlayerRole.GetLevel())
			stItem.SetData( buf, 0, 0, D3DCOLOR_XRGB(255,0,0) );
		else
			stItem.SetData( buf );
		m_pID_LIST_PlayerLvl2->AddItem(&stItem,NULL, false);

		// count
		if (content.count == -1)
		{
			stItem.SetData( "" );
			m_pID_LIST_Finish2->AddItem(&stItem,NULL, false);
		}
		else
		{
			MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, "%d/%d", thePlayerRole.GetVariableValue(content.completeTimeVarIndex), content.count);
			stItem.SetData( buf );
			m_pID_LIST_Finish2->AddItem(&stItem,NULL, false);
		}

		// status
		int status = GetEventStatus(content, nowtime);
		if (status == ES_Start) // 进行中
			stItem.SetData( "{#1026}" );
		else if (status == ES_Close) // 关闭
			stItem.SetData( "{#1029}" );
		else if (status == ES_Finish) // 完成
			stItem.SetData( "{#1028}" );
		else if (status == ES_Ready)
			stItem.SetData( "{#1027}" );
		else // 未开始
			stItem.SetData( "" );
		m_pID_LIST_State2->AddItem(&stItem,NULL, false);

		// reward	根据需求修改活动面板
		/*int nRowItemCount = m_pID_LISTIMG_Reward2->GetRowItemCnt();
		for (int j = 0; j < content.rewards.size(); ++j)
		{
			ControlIconDrag::S_ListImg stImgItem;
			stImgItem.SetData( content.rewards[j].id, content.rewards[j].count, eIcon_Enable, true );
            stImgItem.m_pkIconInfo->SetUsableEffEnable( false );
			m_pID_LISTIMG_Reward2->SetItem(&stImgItem, i*nRowItemCount+j);
		}*/

        if(content.isPivot)
           stItem.SetData("{#1021}");
        else
            stItem.SetData("");
        m_pID_LIST_ActivityHot2->AddItem(&stItem,NULL,false);

        if(content.isPivot)
        {
            stItem.SetData("");
            S_BaseData* pData = m_pID_LIST_ActivityTip2->GetData();
            if(pData != NULL)
            {
                stItem.setTip(pData->m_szCaption);
                stItem.setIsOnline(true);
            }
        }
        m_pID_LIST_ActivityTip2->AddItem(&stItem,NULL,false);
	}

	_updateEventStatus();

	UpdateSelectedContent();
}

void CUI_ID_FRAME_ActivityList::UpdateSelectedContent()
{
	m_pID_LISTIMG_Encouragement->Clear();
	m_pID_TEXT_ActivityName->SetText("");
	m_pID_TEXT_PlayerLvl->SetText("");
	m_pID_TEXT_ActivityTime->SetText("");
	m_pID_TEXT_ActivityNpc->SetText("");
	m_pID_TEXT_ActivityInfo->SetText("");

	Event* pContent = 0;
	int index = m_pCurrActivityList->GetCurSelIndex();
	if (m_pCurrActivityList == m_pID_LIST_ActivityList)
	{
		if (index == -1 || s_sortEvtContents.empty())
			return;

		pContent = s_sortEvtContents[index];
	}
	else
	{
		if (index == -1 || s_sortHotEvtContents.empty())
			return;

		pContent = s_sortHotEvtContents[index];
	}

	const Event& content = *pContent;

	m_pID_TEXT_ActivityName->SetText(content.name);

	// level
	char buf[128];
	MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, "%d", content.needLevel);
	if (content.needLevel > thePlayerRole.GetLevel())
		m_pID_TEXT_PlayerLvl->SetText( buf, D3DCOLOR_XRGB(255,0,0) );
	else
		m_pID_TEXT_PlayerLvl->SetText( buf );

	// time
	MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, "%02d:%02d - %02d:%02d", content.hour, content.minute, content.endHour, content.endMinute);
	m_pID_TEXT_ActivityTime->SetText(buf);

	// npc
	std::string npc = content.npc;
	const NpcCoordInfo *pNpcInfo = NpcCoord::getInstance()->/*getNpcCoordInPrimaryMap*/getNpcCoord(content.npcId);
	if (pNpcInfo)
	{
		char cTip[256] = {0};
		CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(pNpcInfo->_mapId);
		if (pTile)
		{
			sprintf(cTip,"%s(%d,%d)",pTile->GetTileName(),(int)pNpcInfo->_pfMapX,(int)pNpcInfo->_pfMapY);
			m_pID_TEXT_ActivityNpc->setTip(cTip);
			m_pID_TEXT_ActivityNpc->setShowTip(true);
		}
	}
	NpcCoord::getInstance()->addNpcHyber(npc);
	m_pID_TEXT_ActivityNpc->SetColUrl(Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)));
	m_pID_TEXT_ActivityNpc->SetText(npc);

	// description
	m_pID_TEXT_ActivityInfo->SetText(content.description);

	for (int i = 0; i < content.rewards.size(); ++i)
	{
		ControlIconDrag::S_ListImg stItem;
		stItem.SetData( content.rewards[i].id, content.rewards[i].count, eIcon_Enable, true );
		m_pID_LISTIMG_Encouragement->SetItem(&stItem);
	}
}

static void AddTrack(int index, const Event& content, const std::map<std::string, int>& collapseStatus)
{
	char buf[128];
	ControlList::S_List	stItem;

	std::string str;
	str = content.name;
	stItem.m_nHiberarchy = 0;
	std::map<std::string, int>::const_iterator it = collapseStatus.find(str);
	if (it != collapseStatus.end())
		stItem.m_bCollapse = it->second;
	stItem.SetData( str.c_str(), 0, 0, Color_Config.getColor(CC_TASK_NAME) );
	//s_CUI_ID_FRAME_TRACK.m_pID_LIST_Activity->AddItem(&stItem,NULL, false);
	s_CUI_ID_FRAME_ActivityTrack.TrackAddItem(&stItem, false);

	if (!content.npc.empty())
	{
		const NpcCoordInfo *pNpcInfo = NpcCoord::getInstance()->/*getNpcCoordInPrimaryMap*/getNpcCoord(content.npcId);
		if (pNpcInfo)
		{
			char cTip[256] = {0};
			CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(pNpcInfo->_mapId);
			if (pTile)
			{
				sprintf(cTip,"%s(%d,%d)",pTile->GetTileName(),(int)pNpcInfo->_pfMapX,(int)pNpcInfo->_pfMapY);
				stItem.setTip( cTip );
				stItem._bOnline = true;
				stItem.m_nHiberarchy = 1;
				str = "<" + content.npc + ">";
				MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, theXmlString.GetString(eText_FindNpc), str.c_str());
				stItem.SetData( buf, index );
				stItem.SetHyberOtherColor( Color_Config.getColor(CC_PathFindLinker) );

				s_CUI_ID_FRAME_ActivityTrack.TrackAddItem(&stItem, false);
			}
		}
	}

	MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, "%s %02d:%02d - %02d:%02d", theXmlString.GetString(eText_Time), content.hour, content.minute, content.endHour, content.endMinute);
	stItem.clear();
	stItem.m_nHiberarchy = 1;
	stItem.SetData( buf );
	s_CUI_ID_FRAME_ActivityTrack.TrackAddItem(&stItem, false);
}

void CUI_ID_FRAME_ActivityList::Update()
{
	UpdateNowTime();

	if (nowtime.tm_yday != today)
	{
		today = nowtime.tm_yday;
		EventManager::Instance().Load("..\\Data\\Config\\Event.config", nowtime);
		UpdateTodayEvents();
        s_CUI_ID_FRAME_ActivityDay.ClassifyActivities( s_todayEvtContents );
	}

	static int preMinute = -1;
	if (preMinute == nowtime.tm_min)
		return;

	preMinute = nowtime.tm_min;

	_broadcast();
	_update();

    if( !m_pID_FRAME_ActivityList )
        return;

    if ( !m_pID_CHECKBOX_ActivityTrack->IsChecked() )
        s_CUI_ID_FRAME_ActivityTrack.SetVisable( false );
}

void CUI_ID_FRAME_ActivityList::_updateEventStatus()
{
	for (int i = 0; i < s_sortEvtContents.size(); ++i)
	{
		const Event& content = *s_sortEvtContents[i];

		DWORD dwColor = Color_Config.getColor(CC_Activity_Default);

		// status
		int status = GetEventStatus(content, nowtime);
		if (status == ES_Start) // 进行中
		{
			strcpy(m_pID_LIST_State->GetListItem(i)->m_szText, "{#1026}");
			dwColor = Color_Config.getColor(CC_Activity_Start);
		}
		else if (status == ES_Close) // 关闭
		{
			strcpy(m_pID_LIST_State->GetListItem(i)->m_szText, "{#1029}");
			dwColor = Color_Config.getColor(CC_Activity_Close);
		}
		else if (status == ES_Finish) // 完成
		{
			strcpy(m_pID_LIST_State->GetListItem(i)->m_szText, "{#1028}");
			dwColor = Color_Config.getColor(CC_Activity_Finish);
		}
		else if (status == ES_Ready) // 预备
		{
			strcpy(m_pID_LIST_State->GetListItem(i)->m_szText, "{#1027}");
			dwColor = Color_Config.getColor(CC_Activity_Ready);
		}
		else // 未开始
		{
			strcpy(m_pID_LIST_State->GetListItem(i)->m_szText, "");
			dwColor = Color_Config.getColor(CC_Activity_NoStart);
		}
		if (0==dwColor)
		{
			dwColor = 0xffffffff;
		}
		m_pID_LIST_State->ParseText(m_pID_LIST_State->GetListItem(i),NULL);

		m_pID_LIST_ActivityList->GetListItem(i)->setColor(dwColor );
		m_pID_LIST_ActivityDate->GetListItem(i)->setColor(dwColor);
		m_pID_LIST_ActivityTime->GetListItem(i)->setColor(dwColor);
		m_pID_LIST_ActivityName->GetListItem(i)->setColor(dwColor);
		m_pID_LIST_ActivityMap->GetListItem(i)->setColor(dwColor);
		if (content.needLevel > thePlayerRole.GetLevel() &&  status == ES_Start)
			m_pID_LIST_PlayerLvl->GetListItem(i)->setColor(D3DCOLOR_XRGB(255, 0, 0));
		else
			m_pID_LIST_PlayerLvl->GetListItem(i)->setColor(dwColor);
		m_pID_LIST_Finish->GetListItem(i)->setColor(dwColor);
	}

	for (int i = 0; i < s_sortHotEvtContents.size(); ++i)
	{
		const Event& content = *s_sortHotEvtContents[i];

		DWORD dwColor = Color_Config.getColor(CC_Activity_Default);

		// status
		int status = GetEventStatus(content, nowtime);
       

		if (status == ES_Start) // 进行中
		{
			strcpy(m_pID_LIST_State2->GetListItem(i)->m_szText, "{#1026}");
			dwColor = Color_Config.getColor(CC_Activity_Start);
		}
		else if (status == ES_Close) // 关闭
		{
			strcpy(m_pID_LIST_State2->GetListItem(i)->m_szText, "{#1029}");
			dwColor = Color_Config.getColor(CC_Activity_Close);
		}
		else if (status == ES_Finish) // 完成
		{
			strcpy(m_pID_LIST_State2->GetListItem(i)->m_szText, "{#1028}");
			dwColor = Color_Config.getColor(CC_Activity_Finish);
		}
		else if (status == ES_Ready) // 预备
		{
			strcpy(m_pID_LIST_State2->GetListItem(i)->m_szText, "{#1027}");
			dwColor = Color_Config.getColor(CC_Activity_Ready);
		}
		else // 未开始
		{
			strcpy(m_pID_LIST_State2->GetListItem(i)->m_szText, "");
			dwColor = Color_Config.getColor(CC_Activity_NoStart);
		}
		m_pID_LIST_State2->ParseText(m_pID_LIST_State2->GetListItem(i),NULL);

		m_pID_LIST_ActivityList2->GetListItem(i)->setColor(dwColor );
		m_pID_LIST_ActivityDate2->GetListItem(i)->setColor(dwColor);
		//m_pID_LIST_ActivityTime2->GetListItem(i)->setColor(dwColor);
		m_pID_LIST_ActivityName2->GetListItem(i)->setColor(dwColor);
		m_pID_LIST_ActivityStart->GetListItem(i)->setColor(dwColor);
		m_pID_LIST_ActivityMap2->GetListItem(i)->setColor(dwColor);
		if (content.needLevel > thePlayerRole.GetLevel() &&  status == ES_Start)
			m_pID_LIST_PlayerLvl2->GetListItem(i)->setColor(D3DCOLOR_XRGB(255, 0, 0));
		else
			m_pID_LIST_PlayerLvl2->GetListItem(i)->setColor(dwColor);
		m_pID_LIST_Finish2->GetListItem(i)->setColor(dwColor);
	}
}

void CUI_ID_FRAME_ActivityList::_update()
{
	if (IsVisable())
	{
		_updateEventStatus();
	}

	std::map<std::string, int> collapseStatus;
	for (int i = 0; i < s_CUI_ID_FRAME_ActivityTrack.GetTrackListItemCnt(); ++i)
	{
		ControlList::S_List* pItem = s_CUI_ID_FRAME_ActivityTrack.GetTrackListItem(i);
		if (pItem && pItem->m_nHiberarchy == 0)
			collapseStatus[pItem->m_szText] = pItem->m_bCollapse;
	}

	std::vector<std::string> trackEventNames;
	//s_CUI_ID_FRAME_TRACK.m_pID_LIST_Activity->Clear(false);
	s_CUI_ID_FRAME_ActivityTrack.TrackClear(false);

	//added by zhuomeng.hu		[9/7/2010]
	s_CUI_ID_FRAME_ActivityTrack.RefreshAllSpecial();
	if( !m_bShowTrak )
		return;

	for (int i = 0; i < s_todayEvtContents.size(); ++i)
	{
		const Event& content = *s_todayEvtContents[i];

		if (content.duration == 1439)
			continue;

		if ((content.country!=CountryDefine::Country_Init && content.country!=thePlayerRole.GetCountry()))
			continue;


		// status
		int status = GetEventStatus(content, nowtime);
		if (status == ES_Start /*&& content.needLevel <= thePlayerRole.GetLevel()*/)
		{
			AddTrack(i, content, collapseStatus);
			trackEventNames.push_back(content.name);
		}
	}

	s_trackEventNames = trackEventNames;

	if (s_CUI_ID_FRAME_ActivityTrack.GetTrackListItemCnt() - s_CUI_ID_FRAME_ActivityTrack.GetTrackStartIndex() < 
		s_CUI_ID_FRAME_ActivityTrack.GetTrackItemShowCount())
	{
		s_CUI_ID_FRAME_ActivityTrack.SetShowStartHeight(0);
		s_CUI_ID_FRAME_ActivityTrack.SetTrackScrollValue(0);
	}

    if(m_pID_CHECKBOX_ActivityTrack&&s_CUI_ID_FRAME_ActivityTrack.IsExistListTrack())
	s_CUI_ID_FRAME_ActivityTrack.SetVisable(/*s_CUI_ID_FRAME_ActivityTrack.GetTrackListItemCnt() > 0 &&*/
		m_pID_CHECKBOX_ActivityTrack->IsChecked());			//modified by zhuomeng.hu		[9/13/2010]
}

void CUI_ID_FRAME_ActivityList::ID_LIST_ActivityListOnListLDBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	int nIndex = s_CUI_ID_FRAME_ActivityList.m_pCurrActivityList->GetCurSelIndex();
	if (s_CUI_ID_FRAME_ActivityList.m_pCurrActivityList == s_CUI_ID_FRAME_ActivityList.m_pID_LIST_ActivityList)
	{
		if (nIndex == -1 || nIndex >= s_sortEvtContents.size())
			return;

		const Event& content = *s_sortEvtContents[nIndex];
		NpcCoord::getInstance()->clickHyberToMiniMap(content.npc.c_str());

	}
	else
	{
		if (nIndex == -1 || nIndex >= s_sortHotEvtContents.size())
			return;

		const Event& content = *s_sortHotEvtContents[nIndex];
		NpcCoord::getInstance()->clickHyberToMiniMap(content.npc.c_str());
	}
}

void CUI_ID_FRAME_ActivityList::MoveToTarget(int nIndex)
{
// 	if( !m_pID_FRAME_ActivityList )
// 		return;
	if (nIndex == -1 || nIndex >= s_todayEvtContents.size())
		return;

	const Event& content = *s_todayEvtContents[nIndex];
	NpcCoord::getInstance()->clickHyberToMiniMap(content.npc.c_str());
}

void CUI_ID_FRAME_ActivityList::ID_TEXT_ActivityNpc_HyberClick( ControlObject* pSender, const char* szData )
{
	NpcCoord::getInstance()->clickHyberToMiniMap(szData);
}

void CUI_ID_FRAME_ActivityList::UpdateNowTime()
{
	if (_abs64(serverAndLocalOffsetTime) > 100000)
		serverAndLocalOffsetTime = 0;
	__time64_t ltime;
	_time64(&ltime);
	//ltime += serverAndLocalOffsetTime;
	_localtime64_s(&nowtime, &ltime);

	static int preSec = nowtime.tm_sec;
	if (preSec != nowtime.tm_sec)
	{
		preSec = nowtime.tm_sec;

        char buf[128];

        MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, "%02d:%02d:%02d", nowtime.tm_hour, nowtime.tm_min, nowtime.tm_sec);
        if( s_CUI_ID_FRAME_ActivityTrack.IsVisable() )
            s_CUI_ID_FRAME_ActivityTrack.SetTextTime( buf );

		if( s_CUI_ID_FRAME_ActivityMonthList.IsVisable() )
			s_CUI_ID_FRAME_ActivityMonthList.SetTextTime( buf );

        if( m_pID_FRAME_ActivityList )
		    m_pID_TEXT_Time->SetText( buf );
	}
}

void CUI_ID_FRAME_ActivityList::_broadcast()
{
	for (int i = 0; i < s_todayEvtContents.size(); ++i)
	{
		const Event& content = *s_todayEvtContents[i];

		for (int b = 0; b < content.broadcast.size(); ++b)
		{
			long dwTime1 = content.hour * 60 + content.minute;
			long dwTime2 = nowtime.tm_hour * 60 + nowtime.tm_min;
			if (dwTime2 - dwTime1 == content.broadcast[b].offsetTime)
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Activity_Broadcast, content.broadcast[b].content );
			}
		}
	}
}

void CUI_ID_FRAME_ActivityList::ShowSortArrow(int eType)
{
	for (int i = 0; i < eSortTypeTotal; ++i)
	{
		m_pID_TEXT_Arrow[i]->SetVisable( false);
	}
	m_pID_TEXT_Arrow[eType]->SetVisable(true);
	m_bArrow[eType] = !m_bArrow[eType];
	if (m_bArrow[eType])
	{
		m_pID_TEXT_Arrow[eType]->SetText("{#204}");
	}
	else
	{
		m_pID_TEXT_Arrow[eType]->SetText("{#203}");
	}

}

void CUI_ID_FRAME_ActivityList::ShowSortArrow2(int eType)
{
	for (int i = 0; i < eSortTypeTotal; ++i)
	{
		m_pID_TEXT_Arrow2[i]->SetVisable( false);
	}
	m_pID_TEXT_Arrow2[eType]->SetVisable(true);
	m_bArrow2[eType] = !m_bArrow2[eType];
	if (m_bArrow2[eType])
	{
		m_pID_TEXT_Arrow2[eType]->SetText("{#204}");
	}
	else
	{
		m_pID_TEXT_Arrow2[eType]->SetText("{#203}");
	}

}

void CUI_ID_FRAME_ActivityList::RefreshEvents()
{
	_update();
}

void CUI_ID_FRAME_ActivityList::SetTrackShow( bool bShow )
{
	m_bShowTrak = bShow;
	_update();
}
