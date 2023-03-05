/********************************************************************
	Created by UIEditor.exe
	FileName: E:\OnlineAward.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "OnlineAward.h"
#include "UIMgr.h"
#include "OnLineRewardConfig.h"
#include "XmlStringLanguage.h"
#include "PlayerRole.h"
#include "Common.h"
#include "OnlineReward.h"
#include "Cfg.h"


#define REWARDBOX_EFFECT_FILEPATH gCfg.m_strOnlineRewardFile.c_str()//"./data/ui/common/effectrewardbox.dds"
#define REWARDBOX_EFFECT_WIDTH gCfg.m_nOnlineRewardWidth
#define REWARDBOX_EFFECT_HEIGHT gCfg.m_nOnlineRewardHeight
#define REWARDBOX_EFFECT_ITEM_WIDTH gCfg.m_nOnlineRewardItemWidth
#define REWARDBOX_EFFECT_ITEM_HEIGHT gCfg.m_nOnlineRewardItemHeight
#define REWARDBOX_EFFECT_COLUMN gCfg.m_nOnlineRewardColumn
#define REWARDBOX_EFFECT_ROW gCfg.m_nOnlineRewardRow
#define REWARDBOX_EFFECT_TOTALTIME gCfg.m_nOnlineRewardTime

CUI_ID_FRAME_OnlineAward s_CUI_ID_FRAME_OnlineAward;
MAP_FRAME_RUN( s_CUI_ID_FRAME_OnlineAward, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_OnlineAward, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_OnlineAward, ID_BUTTON_GiftOnButtonClick )
CUI_ID_FRAME_OnlineAward::CUI_ID_FRAME_OnlineAward()
{
	// Member
	m_pID_FRAME_OnlineAward = NULL;
	m_pID_PICTURE_PageWall = NULL;
	m_pID_TEXT_Num = NULL;
	m_pID_BUTTON_Gift = NULL;
	m_pID_TEXT_Time = NULL;
	m_bRenderEffectBoxEffect = false;
	Reset();
}

void CUI_ID_FRAME_OnlineAward::InitializeAtEnterWorld()
{
	Reset();
	RECT rcSrc = { 0, 0, REWARDBOX_EFFECT_ITEM_WIDTH, REWARDBOX_EFFECT_ITEM_HEIGHT };
	m_kRewardBox.Initialize( REWARDBOX_EFFECT_FILEPATH, REWARDBOX_EFFECT_ROW, REWARDBOX_EFFECT_COLUMN, 
		gCfg.m_nOnlineRewardCount, rcSrc,  REWARDBOX_EFFECT_TOTALTIME );
}

void CUI_ID_FRAME_OnlineAward::Reset()
{
	m_dwNextAwardTime = 0;
	m_iNextAwardIndex = 0;
	m_iAwardDeltaTime = 0;//30000;	// 30��
    m_nLastFrameTimeLeft = 0;
}

bool CUI_ID_FRAME_OnlineAward::IsRunning() const
{
	// ��Ϊgift����������ʾ��������������ʾ�������ж�ĳ���ؼ�
	return m_pID_PICTURE_PageWall->IsVisable();
}

// Frame
bool CUI_ID_FRAME_OnlineAward::OnFrameRun()
{
	if( IsRunning() )
	{
		// ʣ��ʱ��
		int dwRemainTime = m_dwNextAwardTime - HQ_TimeGetTime();
		if( dwRemainTime > 0 )
		{
            // ������ʱ����жϣ�ʹÿ��ֻ����һ��         added by ZhuoMeng.Hu		[9/30/2010]
            if( m_nLastFrameTimeLeft )
            {
                if( m_nLastFrameTimeLeft - dwRemainTime < 1000 )
                    return true;
            }
            m_nLastFrameTimeLeft = dwRemainTime;

			int second = dwRemainTime * 1.f / 1000;
			int minute = second * 1.f / 60;
			int hour = minute * 1.f / 60;
			minute -= hour * 60;
			if( second * 1000 < dwRemainTime )
				++second;
			second -= hour * 3600 + minute * 60;

			char szTime[MAX_PATH] = {0};
			if( hour > 0 )
				MeSprintf_s(szTime, sizeof(szTime)/sizeof(char) - 1, "%d%s%d%s%d%s", hour, theXmlString.GetString(eTimeUnit_Hour), minute, theXmlString.GetString(eTimeUnit_Minute),
					second, theXmlString.GetString(eTimeUnit_Second));
			else if( minute > 0 )
				MeSprintf_s(szTime, sizeof(szTime)/sizeof(char) - 1, "%d%s%d%s", minute, theXmlString.GetString(eTimeUnit_Minute), second, theXmlString.GetString(eTimeUnit_Second));
			else
				MeSprintf_s(szTime, sizeof(szTime)/sizeof(char) - 1, "%d%s", second, theXmlString.GetString(eTimeUnit_Second));

			char szStr[MAX_PATH] = {0};
			MeSprintf_s(szStr, sizeof(szStr)/sizeof(char) - 1, theXmlString.GetString(eText_OnlineAward), m_iNextAwardIndex + 1 );
			m_pID_TEXT_Num->SetText(szStr);
			MeSprintf_s( szStr, sizeof( szStr ) / sizeof( char ) -1, "%s", szTime );
			m_pID_TEXT_Time->SetText( szStr );
		}
		else
		{
			// �����¸�����
            m_nLastFrameTimeLeft = 0;
			COnlineReward::Instance().SetCurrentStatus( COnlineReward::ORS_TIMEFINISH );
			COnlineReward::Instance().SetUpdateOnlineReward();
			SetVisable(false);
		}
	}
	return true;
}
bool CUI_ID_FRAME_OnlineAward::OnFrameRender()
{
	RenderRewardBoxEffect();
	return true;
}
// Button
bool CUI_ID_FRAME_OnlineAward::ID_BUTTON_GiftOnButtonClick( ControlObject* pSender )
{
	COnlineReward::Instance().SetCurrentStatus( COnlineReward::ORS_CLICKBOX );
	COnlineReward::Instance().SetUpdateOnlineReward();
	return true;
}

// װ��UI
bool CUI_ID_FRAME_OnlineAward::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\OnlineAward.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("��ȡ�ļ�[Data\\UI\\OnlineAward.MEUI]ʧ��")
		return false;
	}
	return DoControlConnect();
}
// �����ؼ�
bool CUI_ID_FRAME_OnlineAward::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_OnlineAward, s_CUI_ID_FRAME_OnlineAwardOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_OnlineAward, s_CUI_ID_FRAME_OnlineAwardOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_OnlineAward, ID_BUTTON_Gift, s_CUI_ID_FRAME_OnlineAwardID_BUTTON_GiftOnButtonClick );

	m_pID_FRAME_OnlineAward = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_OnlineAward );
	m_pID_PICTURE_PageWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_OnlineAward, ID_PICTURE_PageWall );
	m_pID_TEXT_Num = (ControlText*)theUiManager.FindControl( ID_FRAME_OnlineAward, ID_TEXT_Num );
	m_pID_BUTTON_Gift = (ControlButton*)theUiManager.FindControl( ID_FRAME_OnlineAward, ID_BUTTON_Gift );
	m_pID_TEXT_Time = (ControlText*)theUiManager.FindControl( ID_FRAME_OnlineAward, ID_TEXT_Time );
	assert( m_pID_FRAME_OnlineAward );
	assert( m_pID_PICTURE_PageWall );
	assert( m_pID_TEXT_Num );

	m_pID_FRAME_OnlineAward->enableEscKey( false );
	m_pID_FRAME_OnlineAward->SetOnEscResponseType(ControlFrame::EscResponse_SkipMe);

	USE_SCRIPT( eUI_OBJECT_OnlineAward, this );
	SetVisable(false);

	return true;
}
// ж��UI
bool CUI_ID_FRAME_OnlineAward::_UnLoadUI()
{
	CLOSE_SCRIPT( eUI_OBJECT_OnlineAward );

	m_pID_FRAME_OnlineAward = NULL;
	m_pID_PICTURE_PageWall = NULL;
	m_pID_TEXT_Num = NULL;
	m_pID_TEXT_Time = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\OnlineAward.MEUI" );
}
// �Ƿ����
bool CUI_ID_FRAME_OnlineAward::_IsVisable()
{
	if( !m_pID_FRAME_OnlineAward )
		return false;
	return m_pID_FRAME_OnlineAward->IsVisable();
}
// �����Ƿ����
void CUI_ID_FRAME_OnlineAward::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_OnlineAward )
		return;
	m_pID_FRAME_OnlineAward->SetVisable( bVisable );
	m_pID_PICTURE_PageWall->SetVisable( bVisable );
	m_pID_TEXT_Num->SetVisable( bVisable );
	m_pID_BUTTON_Gift->SetVisable( bVisable );	
	m_pID_TEXT_Time->SetVisable( bVisable );
	if( !bVisable )
		ShowRewardBoxEffect( false );
}

bool CUI_ID_FRAME_OnlineAward::SetNextAward( int time, int index )
{
	if( time < 0 || index < 0 || index >= theOnLineRewardConfig.GetMaxRewardCount() )
		return false;

	if( m_iNextAwardIndex == 0 || m_iNextAwardIndex != index )
	{
		m_dwNextAwardTime = time * 60000 + m_iAwardDeltaTime + HQ_TimeGetTime();	// ת�ɺ��룬��m_iAwardDeltaTimeʱ��
		m_iAwardDeltaTime = 0;
		m_iNextAwardIndex = index;
	}
	return true;
}

void CUI_ID_FRAME_OnlineAward::ShowOnlyRewardBox( bool bVisible )
{
	/** true��ֻ��ʾ��У�����ȫ�����أ�false������ȫ����
	*/
	if( bVisible )
	{
		SetVisable( true );
		m_pID_PICTURE_PageWall->SetVisable( false );
		m_pID_TEXT_Num->SetVisable( false );
		m_pID_TEXT_Time->SetVisable( false );
		m_pID_BUTTON_Gift->SetVisable( true );	
	}
	else
	{
		SetVisable( false );
	}
}

void CUI_ID_FRAME_OnlineAward::ShowRewardBoxEffect( bool bShow )
{
	m_bRenderEffectBoxEffect = bShow;
}

void CUI_ID_FRAME_OnlineAward::RenderRewardBoxEffect()
{
	if( !m_bRenderEffectBoxEffect )
		return;

	RECT rc;
	m_pID_BUTTON_Gift->GetRealRect( &rc );
	int nDeltaX = ( REWARDBOX_EFFECT_ITEM_WIDTH - rc.right + rc.left ) / 2;
	int nDeltaY = ( REWARDBOX_EFFECT_ITEM_HEIGHT - rc.bottom + rc.top ) / 2;
	rc.left -= nDeltaX;
	rc.right = rc.left + REWARDBOX_EFFECT_ITEM_WIDTH;
	rc.top -= nDeltaY;
	rc.bottom = rc.top + REWARDBOX_EFFECT_ITEM_HEIGHT;
	m_kRewardBox.Display( rc );


}