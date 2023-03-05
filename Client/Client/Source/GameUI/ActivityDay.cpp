/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\ActivityDay.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ActivityDay.h"
#include "Common.h"
#include "PlayerRole.h"
#include "NpcInfo.h"
#include "MeTerrain/stdafx.h"
#include "CommonChatFrame.h"
#include "XmlStringLanguage.h"
#include "color_config.h"
#include "ActivityTrack.h"
#include "ActivityMonthList.h"

CUI_ID_FRAME_ActivityDay s_CUI_ID_FRAME_ActivityDay;

MAP_FRAME_RUN( s_CUI_ID_FRAME_ActivityDay, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ActivityDay, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityDay, ID_BUTTON_CLOSEOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityDay, ID_CHECKBOX_ActivityOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityDay, ID_CHECKBOX_UnderGroundOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityDay, ID_CHECKBOX_CountryOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityDay, ID_CHECKBOX_GuildOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityDay, ID_CHECKBOX_MoneyOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityDay, ID_CHECKBOX_QuestOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityDay, ID_CHECKBOX_OfficialOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityDay, ID_BUTTON_WeekActivityOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityDay, ID_BUTTON_PageUpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityDay, ID_BUTTON_PageDownOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityDay, ID_BUTTON_LastOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityDay, ID_BUTTON_NextOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityDay, ID_BUTTON_ActivityTrackOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityDay, ID_CHECKBOX_ActivityDayOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityDay, ID_CHECKBOX_ActivityMonthOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityDay, ID_BUTTON_CKMOnButtonClick )
CUI_ID_FRAME_ActivityDay::CUI_ID_FRAME_ActivityDay()
{
    ResetMembers();
    m_eCurrentType = ActType_Activity;
    m_nCurrentPage = 0;
}

void CUI_ID_FRAME_ActivityDay::ResetMembers()
{
	m_pID_FRAME_ActivityDay = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_CHECKBOX_Activity = NULL;
	m_pID_CHECKBOX_UnderGround = NULL;
	m_pID_CHECKBOX_Country = NULL;
	m_pID_CHECKBOX_Guild = NULL;
	m_pID_CHECKBOX_Money = NULL;
	m_pID_CHECKBOX_Quest = NULL;
	m_pID_CHECKBOX_Official = NULL;
	m_pID_BUTTON_WeekActivity = NULL;
	m_pID_BUTTON_PageUp = NULL;
	m_pID_BUTTON_PageDown = NULL;
	m_pID_BUTTON_Last = NULL;
	m_pID_BUTTON_Next = NULL;
	m_pID_TEXT_Desc = NULL;
	m_pID_BUTTON_ActivityTrack = NULL;
	m_pID_CHECKBOX_ActivityDay = NULL;
	m_pID_CHECKBOX_ActivityMonth = NULL;
    m_pID_TEXT_Count = NULL;
    m_pID_TEXT_Desc = NULL;
    m_pID_TEXT_LV = NULL;
    m_pID_LISTIMG_Award = NULL;

	m_pID_TEXT_NPC = NULL;
	m_pID_TEXT_TIME = NULL;
	m_pID_TEXT_LX = NULL;
	m_pID_BUTTON_CKM = NULL;
    for( int i = 0; i < ACT_NUM_PERPAGE; ++i )
    {
        m_pID_TEXT_Name[i] = NULL;
        m_pID_TEXT_Time[i] = NULL;
    }

	for( int j = 0; j < ACT_NUM_QUALITY; ++j )
		m_pID_PICTURE_RecommendStar[j] = NULL;
}

// Frame
bool CUI_ID_FRAME_ActivityDay::OnFrameRun()
{
	return true;
}

bool CUI_ID_FRAME_ActivityDay::OnFrameRender()
{
	m_pID_PICTURE_ActPic[0]->Render();
	return true;
}

bool CUI_ID_FRAME_ActivityDay::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_ActivityDay )
		return false;
	return true;
}

// CheckBox
void CUI_ID_FRAME_ActivityDay::ID_CHECKBOX_ActivityOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_ActivityDay )
		return;

    m_eCurrentType = ActType_Activity;
    m_nCurrentPage = 0;
    Refresh();
}

void CUI_ID_FRAME_ActivityDay::ID_CHECKBOX_UnderGroundOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_ActivityDay )
		return;

    m_eCurrentType = ActType_Ectype;
    m_nCurrentPage = 0;
    Refresh();
}

void CUI_ID_FRAME_ActivityDay::ID_CHECKBOX_CountryOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_ActivityDay )
		return;

    m_eCurrentType = ActType_Country;
    m_nCurrentPage = 0;
    Refresh();
}

void CUI_ID_FRAME_ActivityDay::ID_CHECKBOX_GuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_ActivityDay )
		return;

    m_eCurrentType = ActType_Guild;
    m_nCurrentPage = 0;
    Refresh();
}

void CUI_ID_FRAME_ActivityDay::ID_CHECKBOX_MoneyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_ActivityDay )
		return;

    m_eCurrentType = ActType_Salary;
    m_nCurrentPage = 0;
    Refresh();
}

void CUI_ID_FRAME_ActivityDay::ID_CHECKBOX_QuestOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_ActivityDay )
		return;

    m_eCurrentType = ActType_Task;
    m_nCurrentPage = 0;
    Refresh();
}

void CUI_ID_FRAME_ActivityDay::ID_CHECKBOX_OfficialOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_ActivityDay )
		return;
    // 待添加
}

bool CUI_ID_FRAME_ActivityDay::ID_BUTTON_WeekActivityOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_ActivityDay )
		return false;
	return true;
}

bool CUI_ID_FRAME_ActivityDay::ID_BUTTON_PageUpOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_ActivityDay )
		return false;
    
//     m_nCurrentPage--;
//     Refresh();
	return true;
}

bool CUI_ID_FRAME_ActivityDay::ID_BUTTON_PageDownOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_ActivityDay )
		return false;

//     m_nCurrentPage++;
//     Refresh();
	return true;
}

// Button
bool CUI_ID_FRAME_ActivityDay::ID_BUTTON_LastOnButtonClick( ControlObject* pSender )
{
	std::string strData;
	strData.clear();
	strData = m_pID_TEXT_Name[2]->GetText();
	int nIndex = GetCurrentActivity(strData.c_str(),m_todayVec);
	UpdateEventList(nIndex - 1,m_todayVec);
	return true;
}

// Button
bool CUI_ID_FRAME_ActivityDay::ID_BUTTON_NextOnButtonClick( ControlObject* pSender )
{
	std::string strData;
	strData.clear();
	strData = m_pID_TEXT_Name[2]->GetText();
	int nIndex = GetCurrentActivity(strData.c_str(),m_todayVec);
	UpdateEventList(nIndex + 1,m_todayVec);
	return true;
}

// Button
bool CUI_ID_FRAME_ActivityDay::ID_BUTTON_ActivityTrackOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_ActivityTrack.SetVisable(!s_CUI_ID_FRAME_ActivityTrack.IsVisable());
	return true;
}

// CheckBox
void CUI_ID_FRAME_ActivityDay::ID_CHECKBOX_ActivityDayOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{

}

// CheckBox
void CUI_ID_FRAME_ActivityDay::ID_CHECKBOX_ActivityMonthOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{

}

// Button
bool CUI_ID_FRAME_ActivityDay::ID_BUTTON_CKMOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_ActivityDay )
		return false;

	s_CUI_ID_FRAME_ActivityMonthList.SetVisable(true);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_ActivityDay::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ActivityDay.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ActivityDay.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_ActivityDay::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ActivityDay, s_CUI_ID_FRAME_ActivityDayOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ActivityDay, s_CUI_ID_FRAME_ActivityDayOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ActivityDay, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_ActivityDayID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityDay, ID_CHECKBOX_Activity, s_CUI_ID_FRAME_ActivityDayID_CHECKBOX_ActivityOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityDay, ID_CHECKBOX_UnderGround, s_CUI_ID_FRAME_ActivityDayID_CHECKBOX_UnderGroundOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityDay, ID_CHECKBOX_Country, s_CUI_ID_FRAME_ActivityDayID_CHECKBOX_CountryOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityDay, ID_CHECKBOX_Guild, s_CUI_ID_FRAME_ActivityDayID_CHECKBOX_GuildOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityDay, ID_CHECKBOX_Money, s_CUI_ID_FRAME_ActivityDayID_CHECKBOX_MoneyOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityDay, ID_CHECKBOX_Quest, s_CUI_ID_FRAME_ActivityDayID_CHECKBOX_QuestOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityDay, ID_CHECKBOX_Official, s_CUI_ID_FRAME_ActivityDayID_CHECKBOX_OfficialOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_ActivityDay, ID_BUTTON_WeekActivity, s_CUI_ID_FRAME_ActivityDayID_BUTTON_WeekActivityOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityDay, ID_BUTTON_PageUp, s_CUI_ID_FRAME_ActivityDayID_BUTTON_PageUpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityDay, ID_BUTTON_PageDown, s_CUI_ID_FRAME_ActivityDayID_BUTTON_PageDownOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityDay, ID_BUTTON_Last, s_CUI_ID_FRAME_ActivityDayID_BUTTON_LastOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityDay, ID_BUTTON_Next, s_CUI_ID_FRAME_ActivityDayID_BUTTON_NextOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_ActivityDay, ID_BUTTON_ActivityTrack, s_CUI_ID_FRAME_ActivityDayID_BUTTON_ActivityTrackOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityDay, ID_CHECKBOX_ActivityDay, s_CUI_ID_FRAME_ActivityDayID_CHECKBOX_ActivityDayOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityDay, ID_CHECKBOX_ActivityMonth, s_CUI_ID_FRAME_ActivityDayID_CHECKBOX_ActivityMonthOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_ActivityDay, ID_BUTTON_CKM, s_CUI_ID_FRAME_ActivityDayID_BUTTON_CKMOnButtonClick );

	m_pID_FRAME_ActivityDay = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ActivityDay );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_BUTTON_CLOSE );
	m_pID_TEXT_Desc = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_TEXT_Desc1 );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_TEXT_Page );
	m_pID_LISTIMG_Award = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_LISTIMG_Award1 );
	m_pID_TEXT_Name[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_TEXT_Name1 );
	m_pID_TEXT_Name[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_TEXT_Name2 );
	m_pID_TEXT_Name[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_TEXT_Name3 );
	m_pID_TEXT_Name[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_TEXT_Name4 );
	m_pID_TEXT_Name[4] = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_TEXT_Name5 );
	m_pID_PICTURE_ActPic[0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityDay ,ID_PICTURE_Item1);
	m_pID_PICTURE_ActPic[1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityDay ,ID_PICTURE_Item2);
	m_pID_PICTURE_ActPic[2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityDay ,ID_PICTURE_Item3);
	m_pID_PICTURE_ActPic[3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityDay ,ID_PICTURE_Item4);
	m_pID_PICTURE_ActPic[4] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityDay ,ID_PICTURE_Item5);
	m_pID_TEXT_Time[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_TEXT_Time1 );
	m_pID_TEXT_Time[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_TEXT_Time2 );
	m_pID_TEXT_Time[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_TEXT_Time3 );
	m_pID_TEXT_Time[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_TEXT_Time4 );
	m_pID_TEXT_Time[4] = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_TEXT_Time5 );

	m_pID_CHECKBOX_Activity = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_CHECKBOX_Activity );
	m_pID_CHECKBOX_UnderGround = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_CHECKBOX_UnderGround );
	m_pID_CHECKBOX_Country = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_CHECKBOX_Country );
	m_pID_CHECKBOX_Guild = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_CHECKBOX_Guild );
	m_pID_CHECKBOX_Money = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_CHECKBOX_Money );
	m_pID_CHECKBOX_Quest = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_CHECKBOX_Quest );
	m_pID_CHECKBOX_Official = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_CHECKBOX_Official );
	m_pID_TEXT_Count = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_TEXT_Count1 );

	m_pID_PICTURE_RecommendStar[0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_PICTURE_Recommend1Star1 );
	m_pID_PICTURE_RecommendStar[1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_PICTURE_Recommend1Star2 );
	m_pID_PICTURE_RecommendStar[2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_PICTURE_Recommend1Star3 );
	m_pID_PICTURE_RecommendStar[3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_PICTURE_Recommend1Star4 );
	m_pID_PICTURE_RecommendStar[4] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_PICTURE_Recommend1Star5 );
	m_pID_BUTTON_WeekActivity = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_BUTTON_WeekActivity );
	m_pID_BUTTON_PageUp = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_BUTTON_PageUp );
	m_pID_BUTTON_PageDown = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_BUTTON_PageDown );
    m_pID_TEXT_LV = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_TEXT_LV0 );
	m_pID_BUTTON_Last = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_BUTTON_Last );
	m_pID_BUTTON_Next = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_BUTTON_Next );
	m_pID_BUTTON_ActivityTrack = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_BUTTON_ActivityTrack );
	m_pID_CHECKBOX_ActivityDay = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_CHECKBOX_ActivityDay );
	m_pID_CHECKBOX_ActivityMonth = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_CHECKBOX_ActivityMonth );

	m_pID_TEXT_NPC = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_TEXT_NPC );
	m_pID_TEXT_TIME = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_TEXT_TIME );
	m_pID_TEXT_LX = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_TEXT_LX );
	m_pID_BUTTON_CKM = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityDay, ID_BUTTON_CKM );
	
	assert( m_pID_FRAME_ActivityDay );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_Page );
	assert( m_pID_CHECKBOX_Activity );
	assert( m_pID_CHECKBOX_UnderGround );
	assert( m_pID_CHECKBOX_Country );
	assert( m_pID_CHECKBOX_Guild );
	assert( m_pID_CHECKBOX_Money );
	assert( m_pID_CHECKBOX_Quest );
	assert( m_pID_CHECKBOX_Official );
	assert( m_pID_BUTTON_WeekActivity );
	assert( m_pID_BUTTON_PageUp );
	assert( m_pID_BUTTON_PageDown );
	assert( m_pID_BUTTON_Last );
	assert( m_pID_BUTTON_Next );
	assert( m_pID_BUTTON_ActivityTrack );
	assert( m_pID_CHECKBOX_ActivityDay );
	assert( m_pID_CHECKBOX_ActivityMonth );
    assert( m_pID_TEXT_Count );
    assert( m_pID_TEXT_Desc );
	assert( m_pID_LISTIMG_Award );
	assert( m_pID_TEXT_LV );

	assert( m_pID_TEXT_NPC );
	assert( m_pID_TEXT_TIME );
	assert( m_pID_TEXT_LX );
	assert( m_pID_BUTTON_CKM );

    for( int i = 0; i < ACT_NUM_PERPAGE; ++i )
    {
        assert( m_pID_TEXT_Name[i] );
        assert( m_pID_TEXT_Time[i] );
    }

	for( int j = 0; j < ACT_NUM_QUALITY; ++j )
	{
		assert( m_pID_PICTURE_RecommendStar[j] );
	}

	for ( int i = 0; i < ACT_NUM_QUALITY; i ++ )
	{
		m_pID_PICTURE_ActPic[i]->SetButtonClickFun(ActivetyEvent);
	}
	

    m_pID_LISTIMG_Award->SetCanbePick( false );

    m_pID_FRAME_ActivityDay->SetOnVisibleChangedFun( OnVisibleChange );
    m_pID_CHECKBOX_Official->SetEnable( false );
    
	_SetVisable( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ActivityDay::_UnLoadUI()
{
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\ActivityDay.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_ActivityDay::_IsVisable()
{
	if ( !m_pID_FRAME_ActivityDay )
		return false;
	return m_pID_FRAME_ActivityDay->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_ActivityDay::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_ActivityDay )
		return;
	m_pID_FRAME_ActivityDay->SetVisable( bVisable );
}

void CUI_ID_FRAME_ActivityDay::OnVisibleChange( ControlObject* pUIObject )
{
    if( s_CUI_ID_FRAME_ActivityDay.IsVisable() )
    {
        s_CUI_ID_FRAME_ActivityDay.UpdateCurrentAct();
        s_CUI_ID_FRAME_ActivityDay.Refresh();
    }
}

void CUI_ID_FRAME_ActivityDay::Refresh()
{
    if( m_eCurrentType <= ActType_None || m_eCurrentType >= ActType_Max )
        m_eCurrentType = ActType_Activity;
    
    std::vector<Event> actVec = GetListByCategory( m_eCurrentType );
    int nSize = actVec.size();
    if( m_nCurrentPage < 0 )
        m_nCurrentPage = 0;
    if( nSize <= m_nCurrentPage * ACT_NUM_PERPAGE && m_nCurrentPage > 0 )
        m_nCurrentPage = 0;

    if( !IsUILoad() )
        return;

    // CheckBox相关
    m_pID_CHECKBOX_Activity->SetCheck( false );
    m_pID_CHECKBOX_UnderGround->SetCheck( false );
    m_pID_CHECKBOX_Country->SetCheck( false );
    m_pID_CHECKBOX_Guild->SetCheck( false );
    m_pID_CHECKBOX_Money->SetCheck( false );
    m_pID_CHECKBOX_Quest->SetCheck( false );

    switch( m_eCurrentType )
    {
    case ActType_Activity:
        m_pID_CHECKBOX_Activity->SetCheck( true );
        break;
    case ActType_Ectype:
        m_pID_CHECKBOX_UnderGround->SetCheck( true );
        break;
    case ActType_Country:
        m_pID_CHECKBOX_Country->SetCheck( true );
        break;
    case ActType_Guild:
        m_pID_CHECKBOX_Guild->SetCheck( true );
        break;
    case ActType_Task:
        m_pID_CHECKBOX_Quest->SetCheck( true );
        break;
    case ActType_Salary:
        m_pID_CHECKBOX_Money->SetCheck( true );
        break;
    default:
        break;
    }

//     // 翻页相关
//     if( nSize > ( m_nCurrentPage + 1 ) * ACT_NUM_PERPAGE )
//         m_pID_BUTTON_PageDown->SetEnable( true );
//     else
//         m_pID_BUTTON_PageDown->SetEnable( false );
// 
//     
//     if( m_nCurrentPage > 0 )
//         m_pID_BUTTON_PageUp->SetEnable( true );
//     else
//         m_pID_BUTTON_PageUp->SetEnable( false );
// 
//     int nTotalPage( 1 );
//     if( nSize > 0 )
//         nTotalPage = ( nSize - 1 ) / ACT_NUM_PERPAGE + 1;
//     char szTmp[MAX_PATH] = {0};
//     MeSprintf_s( szTmp, MAX_PATH - 1, "%d / %d", m_nCurrentPage + 1, nTotalPage );
//     m_pID_TEXT_Page->SetText( szTmp );

//     // 显示内容
//     for( int i = m_nCurrentPage * ACT_NUM_PERPAGE; i < m_nCurrentPage * ACT_NUM_PERPAGE + ACT_NUM_PERPAGE; ++i )
//     {
//         int nGroup = i - m_nCurrentPage * ACT_NUM_PERPAGE;
//         if( i < 0 || i >= nSize )
//             continue;
//         
//         // 活动名
//         m_pID_TEXT_Name[nGroup]->SetText( actVec[i].name );
// 
//         // 新增等级显示		[12/17/2010]
//         MeSprintf_s( szTmp, MAX_PATH - 1, theXmlString.GetString( eClient_PlayerTip_Level ), actVec[i].needLevel );
//         DWORD dwLvlColor;
//         if( thePlayerRole.GetLevel() >= actVec[i].needLevel )
//         {
//             dwLvlColor = Color_Config.getColor( CC_ActivityDay_LevelReach );
//         }
//         else
//         {
//             dwLvlColor = Color_Config.getColor( CC_ActivityDay_LevelNotReach );
//         }
//         m_pID_TEXT_LV->SetText( szTmp, dwLvlColor );
// 
//         // 次数
//         if( !actVec[i].totalCount.empty() )
//         {
//             m_pID_TEXT_Count->SetText( actVec[i].totalCount );
//         }
//         else
//         {
//             m_pID_TEXT_Count->SetText( "" );
//         }
// 
//         // 开放时间
//         if( !actVec[i].openTime.empty() )
//         {
//             m_pID_TEXT_Time[nGroup]->SetText( actVec[i].openTime );
//         }
//         else
//         {
//             m_pID_TEXT_Time[nGroup]->SetText( "" );
//         }
// 
//         // 简述
//         if( !actVec[i].formulation.empty() )
//         {
//             m_pID_TEXT_Desc->SetText( actVec[i].formulation );
//         }
//         else
//         {
//             m_pID_TEXT_Desc->SetText( "" );
//         }
// 
//         // 奖励
//         int nAwardCountLimit = m_pID_LISTIMG_Award->GetRowItemCnt();
//         m_pID_LISTIMG_Award->Clear();
//         for( int j = 0; j < actVec[i].rewards.size(); ++j )
//         {
//             if( j >= nAwardCountLimit )
//                 break;
// 
//             ControlIconDrag::S_ListImg stImgItem;
//             stImgItem.SetData( actVec[i].rewards[j].id, actVec[i].rewards[j].count, eIcon_Enable, true );
//             stImgItem.m_pkIconInfo->SetUsableEffEnable( false );
//             m_pID_LISTIMG_Award->SetItem( &stImgItem, j );
//         }
// 
//         // 推荐度
//         for( int j = 0; j < ACT_NUM_QUALITY; ++j )
//         {
//             if( actVec[i].quality == j + 1 )
//                 m_pID_PICTURE_RecommendStar[j]->SetVisable( true );
//             else
//                 m_pID_PICTURE_RecommendStar[j]->SetVisable( false );
//         }
//     }

	int nIndex = GetCurrentActivity(NULL,m_todayVec);
	UpdateEventList(nIndex,m_todayVec);
}

void CUI_ID_FRAME_ActivityDay::ClassifyActivities( const std::vector<Event*>& eventVec )
{
    m_activityVec.clear();
    m_ectypeVec.clear();
    m_countryVec.clear();
    m_guildVec.clear();
    m_taskVec.clear();
    m_salaryVec.clear();
    m_todayVec.clear();
    std::vector<Event*>::const_iterator _it = eventVec.begin();
    for( ; _it != eventVec.end(); ++_it )
    {
		Event* pEvent = *_it;
		if(pEvent)
		    m_todayVec.push_back(*pEvent);
        
		switch( ( *_it )->category )
        {
        case ActType_Activity:
            AddEventToList( *_it, m_activityVec );
            break;
        case ActType_Ectype:
            AddEventToList( *_it, m_ectypeVec );
            break;
        case ActType_Country:
            AddEventToList( *_it, m_countryVec );
            break;
        case ActType_Guild:
            AddEventToList( *_it, m_guildVec );
            break;
        case ActType_Task:
            AddEventToList( *_it, m_taskVec );
            break;
        case ActType_Salary:
            AddEventToList( *_it, m_salaryVec );
            break;
        default:
            break;
        }
    }
}

void CUI_ID_FRAME_ActivityDay::AddEventToList( Event* pEvent, std::vector<Event>& actVec )
{
    if( !pEvent )
        return;

    // 判断当前是否有同名活动
    bool _bSameEvent = false;
    std::vector<Event>::iterator _it = actVec.begin();
    std::vector<Event>::iterator _sameIt;
    for( ; _it != actVec.end(); ++_it )
    {
        if( pEvent->name == _it->name )
        {
            _bSameEvent = true;
            _sameIt = _it;
            break;
        }
    }

    // 不同则增加活动，相同则检查次数和简介
    if( !_bSameEvent )
    {
        actVec.push_back( *pEvent );
    }
    else
    {
        if( !pEvent->totalCount.empty() )
            _sameIt->totalCount = pEvent->totalCount;
        if( !pEvent->formulation.empty() )
            _sameIt->formulation = pEvent->formulation;
    }
}

bool CUI_ID_FRAME_ActivityDay::SortByNeedLevel( const Event& v1, const Event& v2 )
{
    return v1.needLevel < v2.needLevel;
}

void CUI_ID_FRAME_ActivityDay::UpdateCurrentAct()
{
    // 刷出人物等级满足活动条件的今日活动
    m_curActivityVec.clear();
    m_curEctypeVec.clear();
    m_curCountryVec.clear();
    m_curGuildVec.clear();
    m_curTaskVec.clear();
    m_curSalaryVec.clear();
    //struct tm nowtime = s_CUI_ID_FRAME_ActivityList.GetNowtime();

    // 策划修改，现在又显示所有等级的了		[12/17/2010]
    std::vector<Event>::iterator _it = m_activityVec.begin();
    for( ; _it != m_activityVec.end(); ++_it )
    {
        //if( thePlayerRole.GetLevel() >= _it->needLevel ) // nowtime.tm_hour * 60 + nowtime.tm_min <= _it->endHour * 60 + _it->endMinute 
            m_curActivityVec.push_back( *_it );
    }
    for( _it = m_ectypeVec.begin(); _it != m_ectypeVec.end(); ++_it )
    {
        //if( thePlayerRole.GetLevel() >= _it->needLevel )
            m_curEctypeVec.push_back( *_it );
    }
    for( _it = m_countryVec.begin(); _it != m_countryVec.end(); ++_it )
    {
        //if( thePlayerRole.GetLevel() >= _it->needLevel )
            m_curCountryVec.push_back( *_it );
    }
    for( _it = m_guildVec.begin(); _it != m_guildVec.end(); ++_it )
    {
        //if( thePlayerRole.GetLevel() >= _it->needLevel )
            m_curGuildVec.push_back( *_it );
    }
    for( _it = m_taskVec.begin(); _it != m_taskVec.end(); ++_it )
    {
        //if( thePlayerRole.GetLevel() >= _it->needLevel )
            m_curTaskVec.push_back( *_it );
    }
    for( _it = m_salaryVec.begin(); _it != m_salaryVec.end(); ++_it )
    {
        //if( thePlayerRole.GetLevel() >= _it->needLevel )
            m_curSalaryVec.push_back( *_it );
    }

    // 按需要等级排序
    std::sort( m_curActivityVec.begin(), m_curActivityVec.end(), CUI_ID_FRAME_ActivityDay::SortByNeedLevel );
    std::sort( m_curEctypeVec.begin(), m_curEctypeVec.end(), CUI_ID_FRAME_ActivityDay::SortByNeedLevel );
    std::sort( m_curCountryVec.begin(), m_curCountryVec.end(), CUI_ID_FRAME_ActivityDay::SortByNeedLevel );
    std::sort( m_curGuildVec.begin(), m_curGuildVec.end(), CUI_ID_FRAME_ActivityDay::SortByNeedLevel );
    std::sort( m_curTaskVec.begin(), m_curTaskVec.end(), CUI_ID_FRAME_ActivityDay::SortByNeedLevel );
    std::sort( m_curSalaryVec.begin(), m_curSalaryVec.end(), CUI_ID_FRAME_ActivityDay::SortByNeedLevel );
}

const std::vector<Event>& CUI_ID_FRAME_ActivityDay::GetListByCategory( TodayActType eType )
{
    switch( eType )
    {
    case ActType_Activity:
        return m_curActivityVec;
        break;
    case ActType_Ectype:
        return m_curEctypeVec;
        break;
    case ActType_Country:
        return m_curCountryVec;
        break;
    case ActType_Guild:
        return m_curGuildVec;
        break;
    case ActType_Task:
        return m_curTaskVec;
        break;
    case ActType_Salary:
        return m_curSalaryVec;
        break;
    default:
        break;
    }
    return m_curActivityVec;
}

void CUI_ID_FRAME_ActivityDay::GoButtonClickById( int nId )
{
    std::vector<Event> actVec = GetListByCategory( m_eCurrentType );
    int _nActIndex = m_nCurrentPage * ACT_NUM_PERPAGE + nId;
    if( _nActIndex >= actVec.size() )
        return;
    int nNpcId = actVec[_nActIndex].npcId;
    if( nNpcId < 0 )
        return;

    NpcInfo::Npc* pNpc = NpcInfo::Instance().GetNpcByStaticId( nNpcId );
    if( !pNpc )
        return;
    CWorld* pWorld = SwGlobal::GetWorld();
    if( !pWorld )
        return;
    CWorldBuffer* pWorldBuf = pWorld->GetWorldBuffer();
    if( !pWorldBuf )
        return;
   
    CWorldTile*	pWorldTile = pWorldBuf->GetTileFromMapId( pNpc->mapId );
    if( !pWorldTile )
        return;

    std::string _strTileName = pWorldTile->GetTileName();
    char szNpcInfo[MAX_PATH] = {0};
    MeSprintf_s( szNpcInfo, MAX_PATH - 1, "%s %d %d", _strTileName.c_str(), ( int )pNpc->x, ( int )pNpc->y );
    std::string _strFindPath = szNpcInfo;
    CommonChatFrame::Task_HyberOtherClick( NULL, _strFindPath, 0 );
}

bool CUI_ID_FRAME_ActivityDay::ShowAndPitchByName( int nCategory, const char* pEvenName )
{
    UpdateCurrentAct();

    // 各种出错
    if( nCategory <= ActType_None || nCategory >= ActType_Max )
        return false;

    if( !pEvenName )
        return false;

    std::string strEvenName = pEvenName;
    if( strEvenName.empty() )
        return false;

    std::vector<Event> actVec = GetListByCategory( ( TodayActType )nCategory );
    if( actVec.empty() )
        return false;

	// 是否找到
    int nFindIndex = -1;
    std::vector<Event>::size_type n = 0;
    for( ; n < actVec.size(); ++n )
    {
        if( actVec[n].name == strEvenName )
        {
            nFindIndex = n;
            break;
        }
    }

    if( nFindIndex < 0 || nFindIndex >= actVec.size() )
        return false;
    
    // 找到则刷新
    SetVisable( true );
    m_eCurrentType = ( TodayActType )nCategory;
    m_nCurrentPage = nFindIndex / ACT_NUM_PERPAGE;
    Refresh();

	int nIndex = GetCurrentActivity(pEvenName,m_todayVec);
	UpdateEventList(nIndex,m_todayVec);
    return true;
}

int  CUI_ID_FRAME_ActivityDay::GetCurrentActivity(const char* pEventName,const std::vector<Event>& actVec)
{
	int nIndex = -1;
	//有名字更具名字找
	if(!pEventName)
	{
		int nTotalDay = 24 * 60;
        SYSTEMTIME tm;
		GetLocalTime(&tm);
		int nNow = tm.wHour * 60 + tm.wMinute;

		for (int i = 0;i < actVec.size();++i)
		{
			const Event* pInfo = &actVec[i];
			int nHour = pInfo->hour;
			int nMin = pInfo->minute;
			int nTotal = nHour * 60 + nMin;

			if(abs(nTotal - nNow) < nTotalDay)
			{
				nTotalDay = nTotal;
				nIndex = i;
			}
		}
	}
	else
	{
		for (int i = 0;i < actVec.size();++i)
		{
			if(actVec[i].name.compare(pEventName) == 0)
			{
				nIndex = i;
				break;
			}
		}
	}
	return nIndex;
}

void CUI_ID_FRAME_ActivityDay::UpdateEventList(int nIndex,const std::vector<Event>& actVec)
{
	if(!m_pID_FRAME_ActivityDay)
		return;

	if(nIndex < 0 || nIndex >= actVec.size())
		return;

	for (int i = 0;i < ACT_NUM_PERPAGE;++i)
	{
		m_pID_TEXT_Time[i]->SetVisable(false);
		m_pID_TEXT_Name[i]->SetVisable(false);
		m_pID_PICTURE_ActPic[i]->SetVisable(false);
	}
	
	//中间活动
	SetEventName(actVec[nIndex],2);
	//设置活动信息
	SetEventInfo(actVec[nIndex]);

	//左侧活动
	if(nIndex - 1 >= 0 && nIndex - 1 < actVec.size())
		SetEventName(actVec[nIndex - 1],1);
	if(nIndex - 2 >= 0 && nIndex - 2 < actVec.size())
		SetEventName(actVec[nIndex - 2],0);

	//右侧活动
	if(nIndex + 1 >= 0 && nIndex + 1 < actVec.size())
		SetEventName(actVec[nIndex + 1],3);

	if(nIndex + 2 >= 0 && nIndex + 2 < actVec.size())
		SetEventName(actVec[nIndex + 2],4);
}

void CUI_ID_FRAME_ActivityDay::SetEventName(const Event& InfoEvent,int nIndex)
{
	if(!m_pID_FRAME_ActivityDay)
		return;

	if(nIndex < 0 || nIndex >= ACT_NUM_PERPAGE)
		return;

	//设置时间
	if(m_pID_TEXT_Time[nIndex])
	{
		m_pID_TEXT_Time[nIndex]->SetText(InfoEvent.openTime);
		m_pID_TEXT_Time[nIndex]->SetVisable(true);
	}

	//设置图片
	if(m_pID_PICTURE_ActPic[nIndex])
	{
		m_pID_PICTURE_ActPic[nIndex]->SetPicName(InfoEvent.picPath.c_str());
		m_pID_PICTURE_ActPic[nIndex]->SetVisable(true);		
	}

	//设置名称
	if(m_pID_TEXT_Name[nIndex])
	{
		m_pID_TEXT_Name[nIndex]->SetText(InfoEvent.name);
		m_pID_TEXT_Name[nIndex]->SetVisable(true);
	}
}

void CUI_ID_FRAME_ActivityDay::SetEventInfo(const Event& InfoEvent)
{
	if(!m_pID_FRAME_ActivityDay)
		return;


	//信息描述
	if( !InfoEvent.formulation.empty() )
	{
		m_pID_TEXT_Desc->SetText( InfoEvent.formulation );
	}
	else
	{
		m_pID_TEXT_Desc->SetText( "" );
	}

	//设置等级
	char szInfo[256] = {0};
	MeSprintf_s( szInfo, sizeof(szInfo), theXmlString.GetString( eClient_PlayerTip_Level ), InfoEvent.needLevel );
	DWORD dwLvlColor;
	if( thePlayerRole.GetLevel() >= InfoEvent.needLevel )
	{
		dwLvlColor = Color_Config.getColor( CC_ActivityDay_LevelReach );
	}
	else
	{
		dwLvlColor = Color_Config.getColor( CC_ActivityDay_LevelNotReach );
	}

	m_pID_TEXT_LV->SetText(szInfo,dwLvlColor);

	// 次数
	if( !InfoEvent.totalCount.empty() )
	{
		m_pID_TEXT_Count->SetText( InfoEvent.totalCount );
	}
	else
	{
		m_pID_TEXT_Count->SetText( "" );
	}

	// 奖励
	int nAwardCountLimit = m_pID_LISTIMG_Award->GetRowItemCnt();
	m_pID_LISTIMG_Award->Clear();
	for( int j = 0; j < InfoEvent.rewards.size(); ++j )
	{
		if( j >= nAwardCountLimit )
			break;

		ControlIconDrag::S_ListImg stImgItem;
		stImgItem.SetData( InfoEvent.rewards[j].id, InfoEvent.rewards[j].count, eIcon_Enable, true );
		stImgItem.m_pkIconInfo->SetUsableEffEnable( false );
		m_pID_LISTIMG_Award->SetItem( &stImgItem, j );
	}

	// 推荐度
	for( int j = 0; j < ACT_NUM_QUALITY; ++j )
	{
		if( InfoEvent.quality == j + 1 )
			m_pID_PICTURE_RecommendStar[j]->SetVisable( true );
		else
			m_pID_PICTURE_RecommendStar[j]->SetVisable( false );
	}
}

bool CUI_ID_FRAME_ActivityDay::ActivetyEvent( ControlObject* pSender )
{
	//int idx = -1;
	//for ( int i = 0; i < ACT_NUM_PERPAGE; i ++ )
	//{
	//	if ( pSender == s_CUI_ID_FRAME_ActivityDay.m_pID_PICTURE_ActPic[i] )
	//	{
	//		idx = i;
	//		break;
	//	}
	//}
	//if ( idx >= 0 && idx < s_CUI_ID_FRAME_ActivityDay.m_todayVec.size() )
	//{
	//	//m_pID_TEXT_LX			//活动类型
	//	//m_pID_TEXT_TIME		//活动时间
	//	//ID_TEXT_LV0			//活动等级
	//	//ID_TEXT_Count1		//活动次数
	//	//ID_TEXT_NPC			//活动npc
	//}
	//
	
	
	return true;
}