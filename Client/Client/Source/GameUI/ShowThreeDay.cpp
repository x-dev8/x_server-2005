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
	SetVisable(false);//�����Լ�
	s_CUI_ID_FRAME_ThreeDay.SetVisable(true);
	return true;
}
void CUI_ID_FRAME_ShowThreeDay::InitializeAtEnterWorld()
{
}
// װ��UI
bool CUI_ID_FRAME_ShowThreeDay::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ShowThreeDay.MEUI",true,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("��ȡ�ļ�[Data\\UI\\ShowThreeDay.MEUI]ʧ��")
		return false;
	}
	return DoControlConnect();
}
// �����ؼ�
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
	m_pID_TEXT_Effect->SetVisable(false);//��Ч����
	m_pID_TEXT_Effect->SetMsgHoldup(false);
	return true;
}
// ж��UI
bool CUI_ID_FRAME_ShowThreeDay::_UnLoadUI()
{
	m_pID_FRAME_ShowThreeDay = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\ShowThreeDay.MEUI" );
}
// �Ƿ����
bool CUI_ID_FRAME_ShowThreeDay::_IsVisable()
{
	return m_pID_FRAME_ShowThreeDay->IsVisable();
}
// �����Ƿ����
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
		return;//10�����һ��
	ShowThreeDayLogTime = HQ_TimeGetTime();
	//��ʼ����UI�Ƿ���Ҫ��ʾ
	const ThreeDayOnce* pInfo = ThreeDayConfig::Instance().GetNowDayThreeDayOnceInfo();
	if(!pInfo)
	{
		SetVisable(false);
		return;
	}
	//�����ֽ��� �Ƿ��Ѿ���ȡ����
	if(thePlayerRole.GetCharInfo2().otherdataclient.nThreeDayValue & pInfo->nValue)
	{
		SetVisable(false);
		return;
	}
	//�ж�����ʱ��
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
		//����ʱ�䲻�� ������ʾʱ�䵹��ʱ
		m_pID_TEXT_Effect->SetVisable(false);
		m_pID_TEXT_Time->SetVisable(true);
	}
	else
	{
		//������ȡ���� ������ʾ��Ч
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