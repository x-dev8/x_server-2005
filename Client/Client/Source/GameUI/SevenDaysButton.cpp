/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\SevenDaysButton.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SevenDaysButton.h"
#include "PlayerRole.h"
#include "MessageDefine.h"
#include "NetworkInput.h"
#include "SevenDaysTask.h"
#include "SevenDays.h"

const time_t sevenDaysTime = (7 * 60 * 60 * 24);

CUI_ID_FRAME_SevenDaysButton s_CUI_ID_FRAME_SevenDaysButton;

MAP_FRAME_RUN( s_CUI_ID_FRAME_SevenDaysButton, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SevenDaysButton, OnFrameRender )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SevenDaysButton, ID_BUTTON_ShowOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SevenDaysButton, ID_TEXT_ShowOnButtonClick )
CUI_ID_FRAME_SevenDaysButton::CUI_ID_FRAME_SevenDaysButton()
{
	// Member
	m_pID_FRAME_SevenDaysButton = NULL;
	m_pID_BUTTON_Show = NULL;
	m_pID_TEXT_Show = NULL;

}
CUI_ID_FRAME_SevenDaysButton::~CUI_ID_FRAME_SevenDaysButton()
{
}
// Frame
bool CUI_ID_FRAME_SevenDaysButton::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_SevenDaysButton::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_SevenDaysButton::ID_BUTTON_ShowOnButtonClick( ControlObject* pSender )
{
	/*MsgAskSevenDaysData msg;
	GettheNetworkInput().SendMsg( &msg );*/
	s_CUI_ID_FRAME_SevenDays_Task.SetVisable( true );
	return true;
}

bool CUI_ID_FRAME_SevenDaysButton::ID_TEXT_ShowOnButtonClick( ControlObject* pSender )
{
	m_pID_TEXT_Show->SetVisable(false);
	/*MsgAskSevenDaysData msg;
	GettheNetworkInput().SendMsg( &msg );*/
	s_CUI_ID_FRAME_SevenDays_Task.SetVisable( true );
	return true;
}
// 装载UI
bool CUI_ID_FRAME_SevenDaysButton::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SevenDaysButton.meui", true, UI_Render_LayerFirst );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SevenDaysButton.meui]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SevenDaysButton::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SevenDaysButton, s_CUI_ID_FRAME_SevenDaysButtonOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SevenDaysButton, s_CUI_ID_FRAME_SevenDaysButtonOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_SevenDaysButton, ID_BUTTON_Show, s_CUI_ID_FRAME_SevenDaysButtonID_BUTTON_ShowOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SevenDaysButton, ID_TEXT_Show, s_CUI_ID_FRAME_SevenDaysButtonID_TEXT_ShowOnButtonClick );

	m_pID_FRAME_SevenDaysButton = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SevenDaysButton );
	m_pID_BUTTON_Show = (ControlButton*)theUiManager.FindControl( ID_FRAME_SevenDaysButton, ID_BUTTON_Show );
	m_pID_TEXT_Show = (ControlText*)theUiManager.FindControl( ID_FRAME_SevenDaysButton, ID_TEXT_Show );
	assert( m_pID_FRAME_SevenDaysButton );
	assert( m_pID_BUTTON_Show );
	assert( m_pID_TEXT_Show );

	m_pID_TEXT_Show->SetVisable(false);
	m_pID_TEXT_Show->SetMsgHoldup(false);

	m_pID_FRAME_SevenDaysButton->SetOnEscResponseType( ControlFrame::EscResponse_SkipMe );

	_SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SevenDaysButton::_UnLoadUI()
{
	return theUiManager.RemoveFrame( "Data\\UI\\SevenDaysButton.meui" );
}
// 是否可视
bool CUI_ID_FRAME_SevenDaysButton::_IsVisable()
{
	return m_pID_FRAME_SevenDaysButton->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SevenDaysButton::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_SevenDaysButton->SetVisable( bVisable );

	/*if (bVisable)
		m_pID_TEXT_Show->SetVisable(false);*/
}

void CUI_ID_FRAME_SevenDaysButton::InitializeAtEnterWorld()
{
	__time64_t startTime = thePlayerRole.GetCharInfo2().otherdataclient.sevenDayStartTime;

	__time64_t nowTime;
	_time64(&nowTime);

	//int nday = GetDayTime( startTime, nowTime );

	//if ( startTime == 0 /*|| nday > 7*/|| thePlayerRole.m_taskState[SevenDaysConfig::TD_SeventhDay] == 4 )
	//	SetVisable(false);
	//else
	//	SetVisable(true);
	SetVisable( false );

	m_pID_TEXT_Show->SetVisable(false);
}

void CUI_ID_FRAME_SevenDaysButton::SetShowText()
{
	if (!m_pID_TEXT_Show)
		return;
	m_pID_TEXT_Show->SetVisable(true);
}

int CUI_ID_FRAME_SevenDaysButton::GetDayTime( __time64_t startTime, __time64_t nowTime )
{
	if ( nowTime < startTime )
		return -1;

	TimeEx startTimeEx( startTime );
	TimeEx nowTimeEx( nowTime );

	TimeSpan span = TimeSpan( nowTime - startTime );
	__int64 ndays = span.GetDays();

	int startHour = startTimeEx.GetHour();
	int startMinute = startTimeEx.GetMinute();
	int startSecond = startTimeEx.GetSecond();

	int nowHour = nowTimeEx.GetHour();
	int nowMinute = nowTimeEx.GetMinute();
	int nowSecond = nowTimeEx.GetSecond();

	//如果现在的小时，分，秒比开始的小时，分，秒小，说明过了一天
	if ( ( nowHour*3600 + nowMinute*60 + nowSecond ) - ( startHour*3600 + startMinute*60 + startSecond) < 0 )
		ndays++;

	return ndays;
}