#include "PreventWallow.h"
#include "GameMain.h"
#include "ChatInfoBox.h"
#include "core/Name.h"
#include "Color_config.h"
#include "XmlStringLanguage.h"
#include "ShowScreenText.h"
#include "ui/Fcm.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "ui/PrivateShop.h"
#include "ScreenInfoManager.h"
#include "Common.h"


CPreventWallow::CPreventWallow( void )
{
	m_nStatus = enumAntiAddictionStateNormal;
	m_bNotRegister  = false;
}

void CPreventWallow::ClearInfo()
{
	m_bNotRegister = false;
}

void CPreventWallow::UpdatePreventWallow()
{
	if( !m_bNotRegister )
	{ return; }

	//static DWORD s_dwLastMessageTime = 0;
	//static DWORD s_dwMessageTime = 60000;// 1分钟提示一次。

	//DWORD dwCurrentTime = HQ_TimeGetTime();

	//if( dwCurrentTime - s_dwLastMessageTime >= s_dwMessageTime )
	{
//		s_dwLastMessageTime = dwCurrentTime;
		ShowText(theXmlString.GetString(eText_PreventWallow_Account));
	}
}

void CPreventWallow::ProcessWallowMsg( Msg* pMsg )
{
	MsgWallowAbout* pKMsg = ( MsgWallowAbout* )pMsg;

	if (!m_bNotRegister)
	{
		m_bNotRegister = true;
		UpdatePreventWallow();
	}
	int nOnlinetimeHour = pKMsg->nOnlineTime / 60;
	int nLimitHour = pKMsg->nLimitTime / 60;

	if( nOnlinetimeHour == 0 )
	{ return; }

	char acText[256] = {0};
	switch( pKMsg->nStatus )
	{
		// 健康。
	case enumAntiAddictionStateNormal:
		{
			MeSprintf_s( acText, 256, theXmlString.GetString( eText_AntiAddictionLess3Hour ), nOnlinetimeHour );
			ShowText( acText );
		}
		break;

		// 疲劳。
	case enumAntiAddictionStateTired:
		{
			if( pKMsg->nType == MsgWallowAbout::ENotifyType_StatusChange )// 第一次改变状态的时候。
			{
				 MeSprintf_s( acText, 256, theXmlString.GetString( eText_AntiAddiction3Hour ) , nLimitHour );
				 ShowText( acText );
			}
			else
			{
				ShowText( theXmlString.GetString( eText_AntiAddiction4to5Hour ) );
			}
		}
		break;

		// 不健康。
	case enumAntiAddictionStateRest:
		{
			MeSprintf_s( acText, 256, theXmlString.GetString( eText_AntiAddictionMoreThan5Hour ), nLimitHour ) ;
			ShowText( acText );
		}
		break;
	}

	m_nStatus = pKMsg->nStatus;
}

bool CPreventWallow::IsFCMNotHealthy( bool bShowMsg /*= true*/ )
{
	if( m_nStatus == enumAntiAddictionStateRest )
	{
		if( bShowMsg )
		{ 
			//GetShowScreenText()->AddInfo( theXmlString.GetString(eText_FCMOperateFailed), Color_Config.getColor( CC_Center_WarningErrorInfo ) ); 
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Addict_Protect, theXmlString.GetString(eText_FCMOperateFailed) );
		}
		return true;
	}
	return false;
}


void CPreventWallow::PrintDebugString( const char *inputstr )
{
	if( !inputstr )
		return;

	char str[MAX_PATH] = {0};
	TimeEx CurTime = TimeEx::GetCurrentTime();
	sprintf_s(str, sizeof(str)-1, "[DEBUG] %s: %02d:%02d:%02d", inputstr, CurTime.GetHour(), CurTime.GetMinute(), CurTime.GetSecond());
	s_CUI_ChatInfoBox.AddInfo( str, Color_Config.getColor( CC_CHAT_NORMAL ) );
}

void CPreventWallow::ShowText( const char* text )
{
	if( !text )
		return;

	//s_CUI_ChatInfoBox.AddInfo( text, Color_Config.getColor( CC_SystemPromp ) );
	//GetShowScreenText()->SetTile( text, Color_Config.getColor( CC_SystemPromp ), 10000 );
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Addict_Protect, text );
}

