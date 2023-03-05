/********************************************************************
	Created by UIEditor.exe
	FileName: D:\FullBag(13.10.181)\Data\Ui\ShowThreeDay.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ShowThreeDay.h"
#include "ThreeDay.h"
#include "ThreeDayConfig.h"
#include "PlayerRole.h"
#include "OnlineReward.h"
#include "XmlStringLanguage.h"
#include "GameMain.h"
#include "PlayerMgr.h"
CUI_ID_FRAME_ShowThreeDay s_CUI_ID_FRAME_ShowThreeDay;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ShowThreeDay, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ShowThreeDay, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShowThreeDay, ID_TEXT_EffectOnButtonClick )
CUI_ID_FRAME_ShowThreeDay::CUI_ID_FRAME_ShowThreeDay()
{
	// Member
	m_pID_FRAME_ShowThreeDay = NULL;
	m_pID_TEXT_Time = NULL;
	m_pID_TEXT_Effect = NULL;
}
// Frame
bool CUI_ID_FRAME_ShowThreeDay::OnFrameRun()
{
	OnUpdate();
	return true;
}
bool CUI_ID_FRAME_ShowThreeDay::OnFrameRender()
{
	OnUpdateTime();
	return true;
}
bool CUI_ID_FRAME_ShowThreeDay::ID_TEXT_EffectOnButtonClick( ControlObject* pSender )
{
	if(s_CUI_ID_FRAME_ThreeDay.IsVisable())
		return true;
	SetVisable(false);//隐藏自己
	s_CUI_ID_FRAME_ThreeDay.SetVisable(true);
	return true;
}
void CUI_ID_FRAME_ShowThreeDay::InitializeAtEnterWorld()
{
}
// 装载UI
bool CUI_ID_FRAME_ShowThreeDay::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ShowThreeDay.MEUI",true,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ShowThreeDay.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ShowThreeDay::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ShowThreeDay, s_CUI_ID_FRAME_ShowThreeDayOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ShowThreeDay, s_CUI_ID_FRAME_ShowThreeDayOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ShowThreeDay, ID_TEXT_Effect, s_CUI_ID_FRAME_ShowThreeDayID_TEXT_EffectOnButtonClick );

	m_pID_FRAME_ShowThreeDay = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ShowThreeDay );
	m_pID_TEXT_Time = (ControlText*)theUiManager.FindControl( ID_FRAME_ShowThreeDay, ID_TEXT_Time );
	m_pID_TEXT_Effect = (ControlText*)theUiManager.FindControl( ID_FRAME_ShowThreeDay, ID_TEXT_Effect );
	assert( m_pID_FRAME_ShowThreeDay );
	assert( m_pID_TEXT_Time );
	assert( m_pID_TEXT_Effect );
	m_pID_TEXT_Effect->SetVisable(false);//特效隐藏
	m_pID_TEXT_Effect->SetMsgHoldup(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ShowThreeDay::_UnLoadUI()
{
	m_pID_FRAME_ShowThreeDay = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\ShowThreeDay.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_ShowThreeDay::_IsVisable()
{
	return m_pID_FRAME_ShowThreeDay->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ShowThreeDay::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_ShowThreeDay->SetVisable( bVisable );
}
void CUI_ID_FRAME_ShowThreeDay::OnUpdate()
{
	if( !theHeroGame.GetPlayerMgr()->GetMe())
	{
		SetVisable(false);
		return;
	}
	static unsigned int ShowThreeDayLogTime = 0;
	if(ShowThreeDayLogTime != 0 && HQ_TimeGetTime() - ShowThreeDayLogTime < 1000)
		return;//10秒更新一次
	ShowThreeDayLogTime = HQ_TimeGetTime();
	//开始处理UI是否需要显示
	const ThreeDayOnce* pInfo = ThreeDayConfig::Instance().GetNowDayThreeDayOnceInfo();
	if(!pInfo)
	{
		SetVisable(false);
		return;
	}
	//今天又奖励 是否已经领取过了
	if(thePlayerRole.GetCharInfo2().otherdataclient.nThreeDayValue & pInfo->nValue)
	{
		SetVisable(false);
		return;
	}
	//判断在线时间
	if(s_CUI_ID_FRAME_ThreeDay.IsVisable())
	{
		SetVisable(false);
		return;
	}
	SetVisable(true);
	if(!m_pID_FRAME_ShowThreeDay)
		return;
	unsigned int OnLineTime = COnlineReward::Instance().GetOnlineTime();
	if(OnLineTime< ThreeDayConfig::Instance().GetWriteTime())
	{
		//在线时间不足 我们显示时间倒计时
		m_pID_TEXT_Effect->SetVisable(false);
		m_pID_TEXT_Time->SetVisable(true);
	}
	else
	{
		//可以领取奖励 我们显示特效
		m_pID_TEXT_Time->SetText("");
		m_pID_TEXT_Time->SetVisable(false);
		m_pID_TEXT_Effect->SetVisable(true);
	}
}
void CUI_ID_FRAME_ShowThreeDay::OnUpdateTime()
{
	if(!theHeroGame.GetPlayerMgr()->GetMe())
		return;
 	int Time = ThreeDayConfig::Instance().GetWriteTime() - COnlineReward::Instance().GetOnlineTime();
	if(Time <0)
	{
		return;
	}
	unsigned int Min = (Time/1000)/60;
	unsigned int Sec = (Time/1000)%60;
	char Info[256];
	sprintf_s(Info,sizeof(Info)-1,theXmlString.GetString(eText_ThreeDay_Time),Min,Sec);
	m_pID_TEXT_Time->SetText(Info);
}