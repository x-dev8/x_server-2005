/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\上线领奖\Ui\OnlineAward3.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "OnlineAward3.h"
#include "OnlineAward4.h"
#include "NetworkInput.h"
#include "XmlStringLanguage.h"
#include "Common.h"
#include "OnLineRewardConfig.h"

int CUI_ID_FRAME_OnlineAward3::s_nIndex = -1;

CUI_ID_FRAME_OnlineAward3 s_CUI_ID_FRAME_OnlineAward3;
MAP_FRAME_RUN( s_CUI_ID_FRAME_OnlineAward3, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_OnlineAward3, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_OnlineAward3, ID_BUTTON_OnlineAwardOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_OnlineAward3, ID_BUTTON_OnlineAward1OnButtonClick )
CUI_ID_FRAME_OnlineAward3::CUI_ID_FRAME_OnlineAward3()
{
	// Member
	m_pID_FRAME_OnlineAward3 = NULL;
	m_pID_BUTTON_OnlineAward = NULL;
	m_pID_BUTTON_OnlineAward1 = NULL;
	m_pID_TEXT_OnlineAward = NULL;
	m_pID_TEXT_OnlineAward_time = NULL;

}

// Frame
bool CUI_ID_FRAME_OnlineAward3::OnFrameRun()
{
	UpdateTime();
	return true;
}

bool CUI_ID_FRAME_OnlineAward3::OnFrameRender()
{
	return true;
}

// Button
bool CUI_ID_FRAME_OnlineAward3::ID_BUTTON_OnlineAwardOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_OnlineAward3)
		return false;
	if(s_nIndex == -1)
		return true;

	SendMsg(s_nIndex);
	return true;
}

// Button
bool CUI_ID_FRAME_OnlineAward3::ID_BUTTON_OnlineAward1OnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_OnlineAward3)
		return false;
	SetVisable(false);
	s_CUI_ID_FRAME_OnlineAward4.SetVisable(true);
	s_CUI_ID_FRAME_OnlineAward4.SetLeftTime(m_dwBeginTime);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_OnlineAward3::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\OnlineAward3.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\OnlineAward3.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_OnlineAward3::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_OnlineAward3, s_CUI_ID_FRAME_OnlineAward3OnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_OnlineAward3, s_CUI_ID_FRAME_OnlineAward3OnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_OnlineAward3, ID_BUTTON_OnlineAward, s_CUI_ID_FRAME_OnlineAward3ID_BUTTON_OnlineAwardOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_OnlineAward3, ID_BUTTON_OnlineAward1, s_CUI_ID_FRAME_OnlineAward3ID_BUTTON_OnlineAward1OnButtonClick );

	m_pID_FRAME_OnlineAward3 = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_OnlineAward3 );
	m_pID_BUTTON_OnlineAward = (ControlButton*)theUiManager.FindControl( ID_FRAME_OnlineAward3, ID_BUTTON_OnlineAward );
	m_pID_BUTTON_OnlineAward1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_OnlineAward3, ID_BUTTON_OnlineAward1 );
	m_pID_TEXT_OnlineAward = (ControlText*)theUiManager.FindControl( ID_FRAME_OnlineAward3, ID_TEXT_OnlineAward );
	m_pID_TEXT_OnlineAward_time = (ControlText*)theUiManager.FindControl( ID_FRAME_OnlineAward3, ID_TEXT_OnlineAward_time );
	assert( m_pID_FRAME_OnlineAward3 );
	assert( m_pID_BUTTON_OnlineAward );
	assert( m_pID_BUTTON_OnlineAward1 );
	assert( m_pID_TEXT_OnlineAward );
	assert( m_pID_TEXT_OnlineAward_time );

	m_pID_FRAME_OnlineAward3->enableEscKey( false );
	m_pID_FRAME_OnlineAward3->SetOnEscResponseType(ControlFrame::EscResponse_SkipMe);

	Clear();
	SetVisable(false);
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_OnlineAward3::_UnLoadUI()
{
	m_pID_FRAME_OnlineAward3 = NULL;
	m_pID_BUTTON_OnlineAward = NULL;
	m_pID_BUTTON_OnlineAward1 = NULL;
	m_pID_TEXT_OnlineAward = NULL;
	m_pID_TEXT_OnlineAward_time = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\OnlineAward3.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_OnlineAward3::_IsVisable()
{
	if(!m_pID_FRAME_OnlineAward3)
		return false;

	return m_pID_FRAME_OnlineAward3->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_OnlineAward3::_SetVisable( const bool bVisable )
{
	if(m_pID_FRAME_OnlineAward3)
	   m_pID_FRAME_OnlineAward3->SetVisable( bVisable );
}

void CUI_ID_FRAME_OnlineAward3::SendMsg(int nIndex)
{
// 	MsgOnLineRewardReq msg;
// 	msg.nIndex = nIndex;
// 	msg.uchType = MsgOnLineRewardReq::Type_TurnOnLine;
// 	GettheNetworkInput().SendMsg(&msg);
}

void CUI_ID_FRAME_OnlineAward3::StartTime()
{
	if(!m_pID_FRAME_OnlineAward3)
		return;

	SetVisable(true);
	Clear();

	m_dwBeginTime = timeGetTime();

	m_pID_BUTTON_OnlineAward->SetEnable(false);
}

void CUI_ID_FRAME_OnlineAward3::UpdateTime()
{
// 	if(!IsVisable())
// 		return;
// 
// 	if(m_dwBeginTime <= 0)
// 		return;
// 
// 	unsigned long ulLeftTime = (timeGetTime() - m_dwBeginTime)/1000;
// 	const OnLineReward *pReward = theOnLineRewardConfig.GetTurnReward(s_nIndex + 1);
// 	if(!pReward)
// 	{
// 		ShowTime(0);
// 		return;
// 	}
// 
// 	int nLeftTime = pReward->GetOnLineTime() * 60 - ulLeftTime;
// 	if(nLeftTime <= 0)
// 	{
// 		nLeftTime = 0;
// 		++s_nIndex;  //到计时结束，自动进入下一个奖品时间
// 		m_pID_BUTTON_OnlineAward->SetEnable(true);
// 	}
// 
// 	ShowTime(nLeftTime);
}

int CUI_ID_FRAME_OnlineAward3::GetGiftIndex(unsigned long ulTime)
{
	int nIndex = -1;
// 	unsigned short usMaxCount = theOnLineRewardConfig.GetMaxTurnCount();  //获得最大数量
// 
// 	for (int i = usMaxCount - 1;i >= 0;--i)
// 	{
// 		const OnLineReward * pReward = theOnLineRewardConfig.GetTurnReward(i);
// 		if(!pReward)
// 			return nIndex;
// 
// 		unsigned int LineTime = pReward->GetOnLineTime();
// 		if(ulTime > LineTime * 60)
// 		{
// 			nIndex = i;
// 			break;
// 		}
// 	}
	
	return nIndex;
}

void CUI_ID_FRAME_OnlineAward3::Clear()
{
	s_nIndex = -1;
	m_dwBeginTime = 0;
}

bool CUI_ID_FRAME_OnlineAward3::IsMaxValue(int nIndex)
{
	//return theOnLineRewardConfig.GetMaxTurnCount() - 1 <= nIndex;
	return false;
}

void CUI_ID_FRAME_OnlineAward3::ProcessResult()
{
	if(!m_pID_FRAME_OnlineAward3)
		return;

	m_pID_BUTTON_OnlineAward->SetEnable(false);

	if(IsMaxValue(s_nIndex))
	{
		SetVisable(false);
		s_CUI_ID_FRAME_OnlineAward4.SetVisable(false);
	}
}

void CUI_ID_FRAME_OnlineAward3::ShowTime(unsigned long ulTime)
{
	char szTime[128] = {0};
	int nHour = ulTime/3600;
	int nMin = (ulTime - nHour * 3600)/60;
	int nSecond = ulTime - nHour * 3600 - nMin * 60;
	if(nHour > 0)
		MeSprintf_s(szTime,sizeof(szTime)/sizeof(char) - 1,"%d%s%d%s%d%s",
		nHour,theXmlString.GetString(eTimeUnit_Hour),nMin,theXmlString.GetString(eTimeUnit_Minute)
		,nSecond,theXmlString.GetString(eTimeUnit_Second));
	else if(nMin > 0)
		MeSprintf_s(szTime,sizeof(szTime)/sizeof(char) - 1,"%d%s%d%s",nMin,theXmlString.GetString(eTimeUnit_Minute)
		,nSecond,theXmlString.GetString(eTimeUnit_Second));
	else if(nSecond >= 0)
		MeSprintf_s(szTime,sizeof(szTime)/sizeof(char) - 1,"%d%s",nSecond,theXmlString.GetString(eTimeUnit_Second));

	m_pID_TEXT_OnlineAward_time->SetText(szTime);
}

void CUI_ID_FRAME_OnlineAward3::SetEnableOnlineAward(bool bValue)
{
	if(!m_pID_FRAME_OnlineAward3)
		return;

	m_pID_BUTTON_OnlineAward->SetEnable(bValue);
}
