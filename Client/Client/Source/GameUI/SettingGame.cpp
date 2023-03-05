/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\SettingGame.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SettingGame.h"
#include "GameSetting.h"
#include "UserData.h"
#include "XmlStringLanguage.h"
#include "Common.h"
#include "NetworkInput.h"
#include "RelationMessage.h"
CUI_ID_FRAME_GameSet s_CUI_ID_FRAME_GameSet;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GameSet, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GameSet, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_BUTTON_DefaultOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_CHECKBOX_PlayerNameOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_CHECKBOX_SelfHPOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_CHECKBOX_PlayerGuildOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_CHECKBOX_OthersHPOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_CHECKBOX_MonsterNameOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_CHECKBOX_MonsterHPOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_CHECKBOX_RefuseFriendOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_CHECKBOX_RefuseTradeOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_CHECKBOX_RefuseBattleOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_CHECKBOX_RefuseTeamOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_CHECKBOX_RefuseGuildOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_CHECKBOX_CloseGuideOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_CHECKBOX_LockShortcutOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_CHECKBOX_CloseChatBubbleOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_BUTTON_CLOSEOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_CHECKBOX_RefuseStrangerMessaageOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_CHECKBOX_RefuseAllMessaageOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSet, ID_CHECKBOX_AutomatismOnCheckBoxCheck )
CUI_ID_FRAME_GameSet::CUI_ID_FRAME_GameSet()
{
	// Member
	m_pID_FRAME_GameSet = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Default = NULL;
	m_pID_CHECKBOX_PlayerName = NULL;
	m_pID_CHECKBOX_SelfHP = NULL;
	m_pID_CHECKBOX_PlayerGuild = NULL;
	m_pID_CHECKBOX_OthersHP = NULL;
	m_pID_CHECKBOX_MonsterName = NULL;
	m_pID_CHECKBOX_MonsterHP = NULL;
	m_pID_CHECKBOX_RefuseFriend = NULL;
	m_pID_CHECKBOX_RefuseTrade = NULL;
	m_pID_CHECKBOX_RefuseBattle = NULL;
	m_pID_CHECKBOX_RefuseTeam = NULL;
	m_pID_CHECKBOX_RefuseGuild = NULL;
	m_pID_CHECKBOX_CloseGuide = NULL;
	m_pID_CHECKBOX_LockShortcut = NULL;
	m_pID_CHECKBOX_CloseChatBubble = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_CHECKBOX_RefuseStrangerMessaage = NULL;
	m_pID_CHECKBOX_RefuseAllMessaage = NULL;
    m_pID_CHECKBOX_Automatism = NULL;

	m_bRefuseStrangerMessage = false;
	m_bRefuseAllMessage = false;
	m_bRefuseStrangerMessage_New = false;
	m_bRefuseAllMessage_New = false;

}
	// Frame
	bool CUI_ID_FRAME_GameSet::OnFrameRun()
	{
		return true;
	}
	bool CUI_ID_FRAME_GameSet::OnFrameRender()
	{
		return true;
	}
	// Button
	bool CUI_ID_FRAME_GameSet::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
	{
		char szSetting[MAX_PATH] = {0};
		MeSprintf_s( szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s%s", CUserData::Instance()->GetUserDataPath(), GameSetting::Instance()->GetCustomSettingDirectory() );
		GameSetting::Instance()->SaveSetting( szSetting );
		if (!m_bRefuseAllMessage_New && !m_bRefuseStrangerMessage_New)
		{
			if (m_bRefuseAllMessage != m_bRefuseAllMessage_New || m_bRefuseStrangerMessage != m_bRefuseStrangerMessage_New)
			{
				m_bRefuseAllMessage = m_bRefuseAllMessage_New;
				m_bRefuseStrangerMessage = m_bRefuseStrangerMessage_New;
				MsgSetReceiveStrangerReq req;
				req.ustMessageRefuse = RelationDefine::Refuse_None;
				GettheNetworkInput().SendMsg( &req );
				SetVisable(false);
				return true;
			}
		}

		if (m_bRefuseAllMessage != m_bRefuseAllMessage_New)
		{
			m_bRefuseAllMessage = m_bRefuseAllMessage_New;
			if (m_bRefuseAllMessage_New)
			{
				MsgSetReceiveStrangerReq req;
				req.ustMessageRefuse = RelationDefine::Refuse_AllPlayer;
				GettheNetworkInput().SendMsg( &req );
			}			
		}
		else if (m_bRefuseStrangerMessage != m_bRefuseStrangerMessage_New)
		{
			m_bRefuseStrangerMessage = m_bRefuseStrangerMessage_New;
			if (m_bRefuseStrangerMessage_New)
			{
				MsgSetReceiveStrangerReq req;
				req.ustMessageRefuse= RelationDefine::Refuse_Stranger;
				GettheNetworkInput().SendMsg( &req );
			}			
		}
		SetVisable(false);
		return true;
	}
	// Button
	bool CUI_ID_FRAME_GameSet::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
	{
		char szSetting[MAX_PATH] = {0};
		MeSprintf_s( szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s%s", CUserData::Instance()->GetUserDataPath(), GameSetting::Instance()->GetCustomSettingDirectory() );
		GameSetting::Instance()->LoadSetting( szSetting );
		GameSetting::Instance()->CommitChanges();
		SetVisable(false);
		return true;
	}
	// Button
	bool CUI_ID_FRAME_GameSet::ID_BUTTON_DefaultOnButtonClick( ControlObject* pSender )
	{
		GameSetting::Instance()->LoadSetting();
		GameSetting::Instance()->CommitChanges();
		RefreshUI();
		return true;
	}
	// CheckBox
	void CUI_ID_FRAME_GameSet::ID_CHECKBOX_PlayerNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_SHOWPLAYERNAME,  *pbChecked );
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerName,  *pbChecked );
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerName,  *pbChecked );
		GameSetting::Instance()->CommitChanges();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSet::ID_CHECKBOX_SelfHPOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfHp,  *pbChecked );
		GameSetting::Instance()->CommitChanges();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSet::ID_CHECKBOX_PlayerGuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfGuild,  *pbChecked );
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerGuild,  *pbChecked );
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerGuild,  *pbChecked );
		GameSetting::Instance()->CommitChanges();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSet::ID_CHECKBOX_OthersHPOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerHp,  *pbChecked );
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerHp,  *pbChecked );
		GameSetting::Instance()->CommitChanges();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSet::ID_CHECKBOX_MonsterNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_MonsterName,  *pbChecked );
		GameSetting::Instance()->CommitChanges();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSet::ID_CHECKBOX_MonsterHPOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_MonsterHp,  *pbChecked );
		GameSetting::Instance()->CommitChanges();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSet::ID_CHECKBOX_RefuseFriendOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseAddFriend,  *pbChecked );
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseAddFriendInFight,  *pbChecked );
		GameSetting::Instance()->CommitChanges();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSet::ID_CHECKBOX_RefuseTradeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseBargain,  *pbChecked );
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseBargainInFight,  *pbChecked );
		GameSetting::Instance()->CommitChanges();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSet::ID_CHECKBOX_RefuseBattleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseDuel,  *pbChecked );
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseDuelInFight,  *pbChecked );
		GameSetting::Instance()->CommitChanges();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSet::ID_CHECKBOX_RefuseTeamOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseAddTeam,  *pbChecked );
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseAddTeamInFight,  *pbChecked );
		GameSetting::Instance()->CommitChanges();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSet::ID_CHECKBOX_RefuseGuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseAddGang,  *pbChecked );
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseAddGangInFight,  *pbChecked );
		GameSetting::Instance()->CommitChanges();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSet::ID_CHECKBOX_CloseGuideOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_IntroductionEnable, !( *pbChecked ) );
		GameSetting::Instance()->CommitChanges();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSet::ID_CHECKBOX_LockShortcutOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		GameSetting::Instance()->SetLevel( GameSetting::eSSC_SKILLLOCK,  *pbChecked );
		GameSetting::Instance()->SetLevel( GameSetting::eSSC_SKILLLOCK2,  *pbChecked );
		GameSetting::Instance()->CommitChanges();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSet::ID_CHECKBOX_CloseChatBubbleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_ChatOther,  *pbChecked );
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_ChatSelf,  *pbChecked );
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_ChatTeam,  *pbChecked );
		GameSetting::Instance()->CommitChanges();
	}
	// Button
	bool CUI_ID_FRAME_GameSet::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
	{
		ID_BUTTON_CancelOnButtonClick(NULL);
		return true;
	}
	// CheckBox
	void CUI_ID_FRAME_GameSet::ID_CHECKBOX_RefuseStrangerMessaageOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		if (pbChecked)
		{
			m_bRefuseStrangerMessage_New = *pbChecked;
		}		
	}
	// CheckBox
	void CUI_ID_FRAME_GameSet::ID_CHECKBOX_RefuseAllMessaageOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		if (pbChecked)
		{
			m_bRefuseAllMessage_New = *pbChecked;
			if (m_bRefuseAllMessage_New)
			{
				m_bRefuseStrangerMessage_New = true;
				m_pID_CHECKBOX_RefuseStrangerMessaage->SetCheck(true);
				m_pID_CHECKBOX_RefuseStrangerMessaage->SetEnable(false);
			}
			else
			{
				m_pID_CHECKBOX_RefuseStrangerMessaage->SetCheck(true);
				m_pID_CHECKBOX_RefuseStrangerMessaage->SetEnable(true);
			}
			
		}		
	}

	// CheckBox
	void CUI_ID_FRAME_GameSet::ID_CHECKBOX_AutomatismOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		GameSetting::Instance()->SetLevel( GameSetting::eSSC_CLOSE_AUTO_SELECT,  *pbChecked );
		GameSetting::Instance()->CommitChanges();
	}

	// 装载UI
bool CUI_ID_FRAME_GameSet::_LoadUI()
	{
		DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SettingGame.MEUI" , false, UI_Render_LayerThree);
		if ( dwResult == 0 )
		{
			MESSAGE_BOX("读取文件[Data\\UI\\SettingGame.MEUI]失败")
			return false;
		}
		return DoControlConnect();
	}
	// 关连控件
	bool CUI_ID_FRAME_GameSet::DoControlConnect()
	{
		theUiManager.OnFrameRun( ID_FRAME_GameSet, s_CUI_ID_FRAME_GameSetOnFrameRun );
		theUiManager.OnFrameRender( ID_FRAME_GameSet, s_CUI_ID_FRAME_GameSetOnFrameRender );
theUiManager.OnButtonClick( ID_FRAME_GameSet, ID_BUTTON_OK, s_CUI_ID_FRAME_GameSetID_BUTTON_OKOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_GameSet, ID_BUTTON_Cancel, s_CUI_ID_FRAME_GameSetID_BUTTON_CancelOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_GameSet, ID_BUTTON_Default, s_CUI_ID_FRAME_GameSetID_BUTTON_DefaultOnButtonClick );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_PlayerName, s_CUI_ID_FRAME_GameSetID_CHECKBOX_PlayerNameOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_SelfHP, s_CUI_ID_FRAME_GameSetID_CHECKBOX_SelfHPOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_PlayerGuild, s_CUI_ID_FRAME_GameSetID_CHECKBOX_PlayerGuildOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_OthersHP, s_CUI_ID_FRAME_GameSetID_CHECKBOX_OthersHPOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_MonsterName, s_CUI_ID_FRAME_GameSetID_CHECKBOX_MonsterNameOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_MonsterHP, s_CUI_ID_FRAME_GameSetID_CHECKBOX_MonsterHPOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_RefuseFriend, s_CUI_ID_FRAME_GameSetID_CHECKBOX_RefuseFriendOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_RefuseTrade, s_CUI_ID_FRAME_GameSetID_CHECKBOX_RefuseTradeOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_RefuseBattle, s_CUI_ID_FRAME_GameSetID_CHECKBOX_RefuseBattleOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_RefuseTeam, s_CUI_ID_FRAME_GameSetID_CHECKBOX_RefuseTeamOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_RefuseGuild, s_CUI_ID_FRAME_GameSetID_CHECKBOX_RefuseGuildOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_CloseGuide, s_CUI_ID_FRAME_GameSetID_CHECKBOX_CloseGuideOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_LockShortcut, s_CUI_ID_FRAME_GameSetID_CHECKBOX_LockShortcutOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_CloseChatBubble, s_CUI_ID_FRAME_GameSetID_CHECKBOX_CloseChatBubbleOnCheckBoxCheck );
theUiManager.OnButtonClick( ID_FRAME_GameSet, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_GameSetID_BUTTON_CLOSEOnButtonClick );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_RefuseStrangerMessaage, s_CUI_ID_FRAME_GameSetID_CHECKBOX_RefuseStrangerMessaageOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_RefuseAllMessaage, s_CUI_ID_FRAME_GameSetID_CHECKBOX_RefuseAllMessaageOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_Automatism, s_CUI_ID_FRAME_GameSetID_CHECKBOX_AutomatismOnCheckBoxCheck );

		m_pID_FRAME_GameSet = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GameSet );
		m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameSet, ID_BUTTON_OK );
		m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameSet, ID_BUTTON_Cancel );
		m_pID_BUTTON_Default = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameSet, ID_BUTTON_Default );
		m_pID_CHECKBOX_PlayerName = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_PlayerName );
		m_pID_CHECKBOX_SelfHP = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_SelfHP );
		m_pID_CHECKBOX_PlayerGuild = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_PlayerGuild );
		m_pID_CHECKBOX_OthersHP = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_OthersHP );
		m_pID_CHECKBOX_MonsterName = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_MonsterName );
		m_pID_CHECKBOX_MonsterHP = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_MonsterHP );
		m_pID_CHECKBOX_RefuseFriend = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_RefuseFriend );
		m_pID_CHECKBOX_RefuseTrade = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_RefuseTrade );
		m_pID_CHECKBOX_RefuseBattle = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_RefuseBattle );
		m_pID_CHECKBOX_RefuseTeam = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_RefuseTeam );
		m_pID_CHECKBOX_RefuseGuild = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_RefuseGuild );
		m_pID_CHECKBOX_CloseGuide = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_CloseGuide );
		m_pID_CHECKBOX_LockShortcut = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_LockShortcut );
		m_pID_CHECKBOX_CloseChatBubble = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_CloseChatBubble );
		m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameSet, ID_BUTTON_CLOSE );
		m_pID_CHECKBOX_RefuseStrangerMessaage = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_RefuseStrangerMessaage );
		m_pID_CHECKBOX_RefuseAllMessaage = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_RefuseAllMessaage );
        m_pID_CHECKBOX_Automatism = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_Automatism );

		assert( m_pID_FRAME_GameSet );
		assert( m_pID_BUTTON_OK );
		assert( m_pID_BUTTON_Cancel );
		assert( m_pID_BUTTON_Default );
		assert( m_pID_CHECKBOX_PlayerName );
		assert( m_pID_CHECKBOX_SelfHP );
		assert( m_pID_CHECKBOX_PlayerGuild );
		assert( m_pID_CHECKBOX_OthersHP );
		assert( m_pID_CHECKBOX_MonsterName );
		assert( m_pID_CHECKBOX_MonsterHP );
		assert( m_pID_CHECKBOX_RefuseFriend );
		assert( m_pID_CHECKBOX_RefuseTrade );
		assert( m_pID_CHECKBOX_RefuseBattle );
		assert( m_pID_CHECKBOX_RefuseTeam );
		assert( m_pID_CHECKBOX_RefuseGuild );
		assert( m_pID_CHECKBOX_CloseGuide );
		assert( m_pID_CHECKBOX_LockShortcut );
		assert( m_pID_CHECKBOX_CloseChatBubble );
		assert( m_pID_BUTTON_CLOSE );
		assert( m_pID_CHECKBOX_RefuseStrangerMessaage );
		assert( m_pID_CHECKBOX_RefuseAllMessaage );
        assert( m_pID_CHECKBOX_Automatism );

		return true;
	}
	// 卸载UI
bool CUI_ID_FRAME_GameSet::_UnLoadUI()
	{
		m_pID_FRAME_GameSet = NULL;
		return theUiManager.RemoveFrame( "Data\\UI\\SettingGame.MEUI" );
	}
	// 是否可视
	bool CUI_ID_FRAME_GameSet::_IsVisable()
	{
		return m_pID_FRAME_GameSet->IsVisable();
	}
	// 设置是否可视
	void CUI_ID_FRAME_GameSet::_SetVisable( const bool bVisable )
	{
		m_pID_FRAME_GameSet->SetVisable( bVisable );
		if (bVisable)
		{
			RefreshUI();
		}		
	}

	void CUI_ID_FRAME_GameSet::RefreshUI()
	{
		if(!m_pID_FRAME_GameSet)
			return;

		for( int i = 0 ; i < GameSetting::eGSC_TOTAL ; ++ i )
		{
			int nValue = (int)GameSetting::Instance()->GetLevel( (GameSetting::eGameSettingCategory)i );
			switch( i )
			{	

			case GameSetting::eGSC_SHOWPLAYERNAME:
				m_pID_CHECKBOX_PlayerName->SetCheck( nValue );
				break;
			case GameSetting::eGSC_SelfHp:
				m_pID_CHECKBOX_SelfHP->SetCheck( nValue );
				break;
			case GameSetting::eGSC_SelfGuild:
				m_pID_CHECKBOX_PlayerGuild->SetCheck( nValue );
				break;
			case GameSetting::eGSC_OtherPlayerHp:
				m_pID_CHECKBOX_OthersHP->SetCheck( nValue );
				break;
			case GameSetting::eGSC_MonsterName:
				m_pID_CHECKBOX_MonsterName->SetCheck( nValue );
				break;
			case GameSetting::eGSC_MonsterHp:
				m_pID_CHECKBOX_MonsterHP->SetCheck( nValue );
				break;
			case GameSetting::eGSC_RefuseAddFriend:
				m_pID_CHECKBOX_RefuseFriend->SetCheck( nValue );
				break;
			case GameSetting::eGSC_RefuseBargain:
				m_pID_CHECKBOX_RefuseTrade->SetCheck( nValue );
				break;
			case GameSetting::eGSC_RefuseDuel:
				m_pID_CHECKBOX_RefuseBattle->SetCheck( nValue );
				break;
			case GameSetting::eGSC_RefuseAddTeam:
				m_pID_CHECKBOX_RefuseTeam->SetCheck( nValue );
				break;
			case GameSetting::eGSC_RefuseAddGang:
				m_pID_CHECKBOX_RefuseGuild->SetCheck( nValue );
				break;
			case GameSetting::eGSC_IntroductionEnable:
				m_pID_CHECKBOX_CloseGuide->SetCheck( !nValue );
				break;
			case GameSetting::eSSC_SKILLLOCK:
				m_pID_CHECKBOX_LockShortcut->SetCheck( nValue );
				break;
			case GameSetting::eGSC_ChatOther:
				m_pID_CHECKBOX_CloseChatBubble->SetCheck( nValue );
				break;
			case GameSetting::eSSC_CLOSE_AUTO_SELECT:
				m_pID_CHECKBOX_Automatism->SetCheck( nValue );
				break;
			default:
				break;
			}
		}
		m_pID_CHECKBOX_RefuseAllMessaage->SetCheck(m_bRefuseAllMessage);
		if (m_bRefuseAllMessage)
		{
			m_pID_CHECKBOX_RefuseStrangerMessaage->SetCheck(true);
			m_pID_CHECKBOX_RefuseStrangerMessaage->SetEnable(false);
		}
		else
		{
			m_pID_CHECKBOX_RefuseStrangerMessaage->SetCheck(m_bRefuseStrangerMessage);
			m_pID_CHECKBOX_RefuseStrangerMessaage->SetEnable(true);
		}
		
	}

	void CUI_ID_FRAME_GameSet::SetRefuseStrangerMessage( bool val )
	{
		m_bRefuseStrangerMessage = val;
		if (IsUILoad())
		{
			m_pID_CHECKBOX_RefuseStrangerMessaage->SetCheck(m_bRefuseStrangerMessage);
			
		}		
	}

	void CUI_ID_FRAME_GameSet::SetRefuseAllMessage( bool val )
	{
		m_bRefuseAllMessage = val;
		if (m_bRefuseAllMessage)
		{
			m_bRefuseStrangerMessage = true;
		}
		if (IsUILoad())
		{
			m_pID_CHECKBOX_RefuseAllMessaage->SetCheck(m_bRefuseAllMessage);
			if (m_bRefuseAllMessage)
			{
				m_pID_CHECKBOX_RefuseStrangerMessaage->SetCheck(true);
				m_pID_CHECKBOX_RefuseStrangerMessaage->SetEnable(false);
			}
			else
			{
				m_pID_CHECKBOX_RefuseStrangerMessaage->SetEnable(true);
			}
		}		
	}