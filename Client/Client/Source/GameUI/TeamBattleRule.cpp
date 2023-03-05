/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\chixin.ni\桌面\TeamBattleRule.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "TeamBattleRule.h"
#include "TeamBattleRequest.h"
#include "GameMain.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "XmlStringLanguage.h"
#include "ShowScreenText.h"
#include "../color_config.h"
#include "ShowScreenText.h"
#include "MessageBox.h"

CUI_ID_FRAME_TeamBattleRule s_CUI_ID_FRAME_TeamBattleRule;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TeamBattleRule, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TeamBattleRule, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TeamBattleRule, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TeamBattleRule, ID_BUTTON_TeamOnButtonClick )
CUI_ID_FRAME_TeamBattleRule::CUI_ID_FRAME_TeamBattleRule()
{
	// Member
	m_pID_FRAME_TeamBattleRule = NULL;
	m_pID_PICTURE_BackWall = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Team = NULL;
	m_pID_TEXT_Rule = NULL;

}
// Frame
bool CUI_ID_FRAME_TeamBattleRule::OnFrameRun()
{
	if( IsVisable() )
	{
		if(thePlayerRole.IsTeamBattleInMap())
		{
			SetVisable(false);
		}

		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if ( pMe )
		{
			float fMeX,fMeY,fMeZ;			
			pMe->GetPos( &fMeX, &fMeY, &fMeZ );
			float dist = pMe->GetDistToTarget( m_vVisiblePos.x, m_vVisiblePos.y );			
			if( dist > 7.0f )
			{
				SetVisable( false );
			}
		}
	}
	return true;
}
bool CUI_ID_FRAME_TeamBattleRule::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_TeamBattleRule::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_TeamBattleRule )
		return false;
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_TeamBattleRule::ID_BUTTON_TeamOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_TeamBattleRule )
		return false;
	s_CUI_ID_FRAME_TeamBattleRequest.SetVisable(true);

	SetVisable(false);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_TeamBattleRule::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TeamBattleRule.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\TeamBattleRule.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_TeamBattleRule::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TeamBattleRule, s_CUI_ID_FRAME_TeamBattleRuleOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TeamBattleRule, s_CUI_ID_FRAME_TeamBattleRuleOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_TeamBattleRule, ID_BUTTON_Cancel, s_CUI_ID_FRAME_TeamBattleRuleID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TeamBattleRule, ID_BUTTON_Team, s_CUI_ID_FRAME_TeamBattleRuleID_BUTTON_TeamOnButtonClick );

	m_pID_FRAME_TeamBattleRule = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TeamBattleRule );
	m_pID_PICTURE_BackWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TeamBattleRule, ID_PICTURE_BackWall );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_TeamBattleRule, ID_BUTTON_Cancel );
	m_pID_BUTTON_Team = (ControlButton*)theUiManager.FindControl( ID_FRAME_TeamBattleRule, ID_BUTTON_Team );
	m_pID_TEXT_Rule = (ControlText*)theUiManager.FindControl( ID_FRAME_TeamBattleRule, ID_TEXT_Rule );
	assert( m_pID_FRAME_TeamBattleRule );
	assert( m_pID_PICTURE_BackWall );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_Team );
	assert( m_pID_TEXT_Rule );
	SetVisable(false);

	*m_pID_TEXT_Rule = theXmlString.GetString( eText_TeamBattleRule );

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_TeamBattleRule::_UnLoadUI()
{
	m_pID_FRAME_TeamBattleRule = NULL;
	m_pID_PICTURE_BackWall = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Team = NULL;
	m_pID_TEXT_Rule = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\TeamBattleRule.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_TeamBattleRule::_IsVisable()
{
	if( !m_pID_FRAME_TeamBattleRule )
		return false;
	return m_pID_FRAME_TeamBattleRule->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_TeamBattleRule::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_TeamBattleRule )
		return;
	m_pID_FRAME_TeamBattleRule->SetVisable( bVisable );
}
