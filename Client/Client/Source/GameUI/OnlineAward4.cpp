/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\上线领奖\Ui\OnlineAward4.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "OnlineAward4.h"
#include "OnlineAward3.h"
#include "XmlStringLanguage.h"
#include "Common.h"
#include "OnLineRewardConfig.h"

CUI_ID_FRAME_OnlineAward4 s_CUI_ID_FRAME_OnlineAward4;
MAP_FRAME_RUN( s_CUI_ID_FRAME_OnlineAward4, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_OnlineAward4, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_OnlineAward4, ID_BUTTON_OnlineAward_addOnButtonClick )
CUI_ID_FRAME_OnlineAward4::CUI_ID_FRAME_OnlineAward4()
{
	// Member
	m_pID_FRAME_OnlineAward4 = NULL;
	m_pID_PICTURE_7206 = NULL;
	m_pID_BUTTON_OnlineAward_add = NULL;
	m_pID_TEXT_OnlineAward_addtime = NULL;

}
// Frame
bool CUI_ID_FRAME_OnlineAward4::OnFrameRun()
{
	UpdateTime();
	return true;
}
bool CUI_ID_FRAME_OnlineAward4::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_OnlineAward4::ID_BUTTON_OnlineAward_addOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_OnlineAward4)
		return false;
	SetVisable(false);
	s_CUI_ID_FRAME_OnlineAward3.SetVisable(true);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_OnlineAward4::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\OnlineAward4.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\OnlineAward4.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_OnlineAward4::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_OnlineAward4, s_CUI_ID_FRAME_OnlineAward4OnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_OnlineAward4, s_CUI_ID_FRAME_OnlineAward4OnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_OnlineAward4, ID_BUTTON_OnlineAward_add, s_CUI_ID_FRAME_OnlineAward4ID_BUTTON_OnlineAward_addOnButtonClick );

	m_pID_FRAME_OnlineAward4 = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_OnlineAward4 );
	m_pID_PICTURE_7206 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_OnlineAward4, ID_PICTURE_7206 );
	m_pID_BUTTON_OnlineAward_add = (ControlButton*)theUiManager.FindControl( ID_FRAME_OnlineAward4, ID_BUTTON_OnlineAward_add );
	m_pID_TEXT_OnlineAward_addtime = (ControlText*)theUiManager.FindControl( ID_FRAME_OnlineAward4, ID_TEXT_OnlineAward_addtime );
	assert( m_pID_FRAME_OnlineAward4 );
	assert( m_pID_PICTURE_7206 );
	assert( m_pID_BUTTON_OnlineAward_add );
	assert( m_pID_TEXT_OnlineAward_addtime );

	m_pID_FRAME_OnlineAward4->enableEscKey( false );
	m_pID_FRAME_OnlineAward4->SetOnEscResponseType(ControlFrame::EscResponse_SkipMe);

	SetVisable(false);

	m_LeftTime = 0;
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_OnlineAward4::_UnLoadUI()
{
	m_pID_FRAME_OnlineAward4 = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\OnlineAward4.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_OnlineAward4::_IsVisable()
{
	if(!m_pID_FRAME_OnlineAward4)
		return false;

	return m_pID_FRAME_OnlineAward4->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_OnlineAward4::_SetVisable( const bool bVisable )
{
	if(m_pID_FRAME_OnlineAward4)
	   m_pID_FRAME_OnlineAward4->SetVisable( bVisable );

	if(!bVisable)
		m_LeftTime = 0;
}

void CUI_ID_FRAME_OnlineAward4::SetLeftTime(unsigned long nTime)
{
	m_LeftTime = nTime;
}

void CUI_ID_FRAME_OnlineAward4::UpdateTime()
{
// 	if(!IsVisable())
// 		return;
// 
// 	if(m_LeftTime <= 0)
// 		return;
// 
// 	unsigned long ulLeftTime = (timeGetTime() - m_LeftTime)/1000;
// 
// 	const OnLineReward *pReward = theOnLineRewardConfig.GetTurnReward(CUI_ID_FRAME_OnlineAward3::s_nIndex + 1);
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
// 		++CUI_ID_FRAME_OnlineAward3::s_nIndex;  //到计时结束，自动进入下一个奖品时间
// 		s_CUI_ID_FRAME_OnlineAward3.SetEnableOnlineAward(true);
// 		if(IsVisable())
// 		{
// 			SetVisable(false);
// 			s_CUI_ID_FRAME_OnlineAward3.SetVisable(true);
// 		}
// 	}
// 
// 	ShowTime(nLeftTime);
}

void CUI_ID_FRAME_OnlineAward4::ShowTime(unsigned long nTime)
{
	if(!m_pID_FRAME_OnlineAward4)
		return;

	char szTime[128] = {0};
	int nHour = nTime/3600;
	int nMin = (nTime - nHour * 3600)/60;
	int nSecond = nTime - nHour * 3600 - nMin * 60;
	if(nHour > 0)
		MeSprintf_s(szTime,sizeof(szTime)/sizeof(char) - 1,"%d%s%d%s%d%s",
		nHour,theXmlString.GetString(eTimeUnit_Hour),nMin,theXmlString.GetString(eTimeUnit_Minute)
		,nSecond,theXmlString.GetString(eTimeUnit_Second));
	else if(nMin > 0)
		MeSprintf_s(szTime,sizeof(szTime)/sizeof(char) - 1,"%d%s%d%s",nMin,theXmlString.GetString(eTimeUnit_Minute)
		,nSecond,theXmlString.GetString(eTimeUnit_Second));
	else if(nSecond >= 0)
		MeSprintf_s(szTime,sizeof(szTime)/sizeof(char) - 1,"%d%s",nSecond,theXmlString.GetString(eTimeUnit_Second));

	m_pID_TEXT_OnlineAward_addtime->SetText(szTime);
}
