/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\gamesetting\GameSettingPlayer.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GameSetting.h"
#include "GameSettingPlayer.h"
#include "GameSettingUIBase.h"

CUI_ID_FRAME_GameSettingPlayer s_CUI_ID_FRAME_GameSettingPlayer;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GameSettingPlayer, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GameSettingPlayer, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamNameOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamHpOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamTitleOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamGuildOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamTongOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherNameOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherHpOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherTitleOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherGroupOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherTongOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherEffectOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherModelOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamEffectOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamModelOnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamInfoControlOnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherInfoControlOnCheckBoxCheck )

CUI_ID_FRAME_GameSettingPlayer::CUI_ID_FRAME_GameSettingPlayer()
{
	// Member
	m_pID_FRAME_GameSettingPlayer = NULL;
	m_pID_PICTURE_Wall1 = NULL;
	m_pID_PICTURE_Wall3 = NULL;
// 	m_pID_PICTURE_Wall2 = NULL;
// 	m_pID_PICTURE_Wall4 = NULL;
	m_pID_TEXT_TeamInfo = NULL;
	m_pID_TEXT_TeamName = NULL;
	m_pID_TEXT_TeamTong = NULL;
	m_pID_TEXT_TeamHp = NULL;
	m_pID_TEXT_TeamGuild = NULL;
	m_pID_TEXT_TeamTitle = NULL;
	m_pID_TEXT_OtherInfo = NULL;
	m_pID_TEXT_OtherName = NULL;
	m_pID_TEXT_OtherHp = NULL;
	m_pID_TEXT_OtherTitle = NULL;
	m_pID_TEXT_OtherGroup = NULL;
	m_pID_TEXT_OtherTong = NULL;
	m_pID_CHECKBOX_TeamName = NULL;
	m_pID_CHECKBOX_TeamHp = NULL;
	m_pID_CHECKBOX_TeamTitle = NULL;
	m_pID_CHECKBOX_TeamGuild = NULL;
	m_pID_CHECKBOX_TeamTong = NULL;
	m_pID_CHECKBOX_OtherName = NULL;
	m_pID_CHECKBOX_OtherHp = NULL;
	m_pID_CHECKBOX_OtherTitle = NULL;
	m_pID_CHECKBOX_OtherGroup = NULL;
	m_pID_CHECKBOX_OtherTong = NULL;
	m_pID_CHECKBOX_OtherEffect = NULL;
	m_pID_CHECKBOX_OtherModel = NULL;
	m_pID_CHECKBOX_TeamEffect = NULL;
	m_pID_CHECKBOX_TeamModel = NULL;
	m_pID_TEXT_OtherEffect = NULL;
	m_pID_TEXT_OtherModel = NULL;
	m_pID_TEXT_TeamEffect = NULL;
	m_pID_TEXT_TeamModel = NULL;
// 	m_pID_CHECKBOX_TeamInfoControl = NULL;
// 	m_pID_CHECKBOX_OtherInfoControl = NULL;

}
// Frame
bool CUI_ID_FRAME_GameSettingPlayer::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GameSettingPlayer::OnFrameRender()
{
	return true;
}
// CheckBox
void CUI_ID_FRAME_GameSettingPlayer::ID_CHECKBOX_TeamNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerName, (unsigned int)*pbChecked );
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerPetName, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckTeamInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingPlayer::ID_CHECKBOX_TeamHpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerHp, (unsigned int)*pbChecked );
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerPetHp, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckTeamInfoControl();
    //if( s_CUI_ID_FRAME_PkSet.IsVisable() )
    //    s_CUI_ID_FRAME_PkSet.RefreshHpMpUI();
}
// CheckBox
void CUI_ID_FRAME_GameSettingPlayer::ID_CHECKBOX_TeamTitleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerTitle, (unsigned int)*pbChecked );
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPetTitle, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckTeamInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingPlayer::ID_CHECKBOX_TeamGuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerGuild, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckTeamInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingPlayer::ID_CHECKBOX_TeamTongOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerTong, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckTeamInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingPlayer::ID_CHECKBOX_OtherNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerName, (unsigned int)*pbChecked );
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerPetName, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckOtherInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingPlayer::ID_CHECKBOX_OtherHpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerHp, (unsigned int)*pbChecked );
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerPetHp, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckOtherInfoControl();
    //if( s_CUI_ID_FRAME_PkSet.IsVisable() )
    //    s_CUI_ID_FRAME_PkSet.RefreshHpMpUI();
}
// CheckBox
void CUI_ID_FRAME_GameSettingPlayer::ID_CHECKBOX_OtherTitleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerTitle, (unsigned int)*pbChecked );
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPetTitle, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckOtherInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingPlayer::ID_CHECKBOX_OtherGroupOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerGuild, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckOtherInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingPlayer::ID_CHECKBOX_OtherTongOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerTong, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckOtherInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingPlayer::ID_CHECKBOX_OtherEffectOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerEffect, (unsigned int)*pbChecked );
    GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSettingPlayer::ID_CHECKBOX_OtherModelOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerModel, (unsigned int)*pbChecked );
    GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSettingPlayer::ID_CHECKBOX_TeamEffectOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerEffect, (unsigned int)*pbChecked );
    GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSettingPlayer::ID_CHECKBOX_TeamModelOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerModel, (unsigned int)*pbChecked );
    GameSetting::Instance()->CommitChanges();
}
// CheckBox
// void CUI_ID_FRAME_GameSettingPlayer::ID_CHECKBOX_TeamInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
//     ID_CHECKBOX_TeamNameOnCheckBoxCheck(NULL, pbChecked);
//     ID_CHECKBOX_TeamHpOnCheckBoxCheck(NULL, pbChecked);
//     ID_CHECKBOX_TeamTitleOnCheckBoxCheck(NULL, pbChecked);
//     ID_CHECKBOX_TeamGuildOnCheckBoxCheck(NULL, pbChecked);
//     ID_CHECKBOX_TeamTongOnCheckBoxCheck(NULL, pbChecked);
//     m_pID_CHECKBOX_TeamName->SetCheck(*pbChecked);
//     m_pID_CHECKBOX_TeamHp->SetCheck(*pbChecked);
//     m_pID_CHECKBOX_TeamTitle->SetCheck(*pbChecked);
//     m_pID_CHECKBOX_TeamGuild->SetCheck(*pbChecked);
//     m_pID_CHECKBOX_TeamTong->SetCheck(*pbChecked);
// }
// // CheckBox
// void CUI_ID_FRAME_GameSettingPlayer::ID_CHECKBOX_OtherInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
//     ID_CHECKBOX_OtherNameOnCheckBoxCheck(NULL, pbChecked);
//     ID_CHECKBOX_OtherHpOnCheckBoxCheck(NULL, pbChecked);
//     ID_CHECKBOX_OtherTitleOnCheckBoxCheck(NULL, pbChecked);
//     ID_CHECKBOX_OtherGroupOnCheckBoxCheck(NULL, pbChecked);
//     ID_CHECKBOX_OtherTongOnCheckBoxCheck(NULL, pbChecked);
//     m_pID_CHECKBOX_OtherName->SetCheck(*pbChecked);
//     m_pID_CHECKBOX_OtherHp->SetCheck(*pbChecked);
//     m_pID_CHECKBOX_OtherTitle->SetCheck(*pbChecked);
//     m_pID_CHECKBOX_OtherGroup->SetCheck(*pbChecked);
//     m_pID_CHECKBOX_OtherTong->SetCheck(*pbChecked);
// }
// 装载UI
bool CUI_ID_FRAME_GameSettingPlayer::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GameSettingPlayer.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GameSettingPlayer.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GameSettingPlayer::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GameSettingPlayer, s_CUI_ID_FRAME_GameSettingPlayerOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GameSettingPlayer, s_CUI_ID_FRAME_GameSettingPlayerOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamName, s_CUI_ID_FRAME_GameSettingPlayerID_CHECKBOX_TeamNameOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamHp, s_CUI_ID_FRAME_GameSettingPlayerID_CHECKBOX_TeamHpOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamTitle, s_CUI_ID_FRAME_GameSettingPlayerID_CHECKBOX_TeamTitleOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamGuild, s_CUI_ID_FRAME_GameSettingPlayerID_CHECKBOX_TeamGuildOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamTong, s_CUI_ID_FRAME_GameSettingPlayerID_CHECKBOX_TeamTongOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherName, s_CUI_ID_FRAME_GameSettingPlayerID_CHECKBOX_OtherNameOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherHp, s_CUI_ID_FRAME_GameSettingPlayerID_CHECKBOX_OtherHpOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherTitle, s_CUI_ID_FRAME_GameSettingPlayerID_CHECKBOX_OtherTitleOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherGroup, s_CUI_ID_FRAME_GameSettingPlayerID_CHECKBOX_OtherGroupOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherTong, s_CUI_ID_FRAME_GameSettingPlayerID_CHECKBOX_OtherTongOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherEffect, s_CUI_ID_FRAME_GameSettingPlayerID_CHECKBOX_OtherEffectOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherModel, s_CUI_ID_FRAME_GameSettingPlayerID_CHECKBOX_OtherModelOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamEffect, s_CUI_ID_FRAME_GameSettingPlayerID_CHECKBOX_TeamEffectOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamModel, s_CUI_ID_FRAME_GameSettingPlayerID_CHECKBOX_TeamModelOnCheckBoxCheck );
//     theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamInfoControl, s_CUI_ID_FRAME_GameSettingPlayerID_CHECKBOX_TeamInfoControlOnCheckBoxCheck );
//     theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherInfoControl, s_CUI_ID_FRAME_GameSettingPlayerID_CHECKBOX_OtherInfoControlOnCheckBoxCheck );

	m_pID_FRAME_GameSettingPlayer = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GameSettingPlayer );
	m_pID_PICTURE_Wall1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_PICTURE_Wall1 );
	m_pID_PICTURE_Wall3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_PICTURE_Wall3 );
// 	m_pID_PICTURE_Wall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_PICTURE_Wall2 );
// 	m_pID_PICTURE_Wall4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_PICTURE_Wall4 );
	m_pID_TEXT_TeamInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_TEXT_TeamInfo );
	m_pID_TEXT_TeamName = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_TEXT_TeamName );
	m_pID_TEXT_TeamTong = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_TEXT_TeamTong );
	m_pID_TEXT_TeamHp = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_TEXT_TeamHp );
	m_pID_TEXT_TeamGuild = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_TEXT_TeamGuild );
	m_pID_TEXT_TeamTitle = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_TEXT_TeamTitle );
	m_pID_TEXT_OtherInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_TEXT_OtherInfo );
	m_pID_TEXT_OtherName = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_TEXT_OtherName );
	m_pID_TEXT_OtherHp = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_TEXT_OtherHp );
	m_pID_TEXT_OtherTitle = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_TEXT_OtherTitle );
	m_pID_TEXT_OtherGroup = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_TEXT_OtherGroup );
	m_pID_TEXT_OtherTong = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_TEXT_OtherTong );
	m_pID_CHECKBOX_TeamName = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamName );
	m_pID_CHECKBOX_TeamHp = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamHp );
	m_pID_CHECKBOX_TeamTitle = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamTitle );
	m_pID_CHECKBOX_TeamGuild = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamGuild );
	m_pID_CHECKBOX_TeamTong = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamTong );
	m_pID_CHECKBOX_OtherName = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherName );
	m_pID_CHECKBOX_OtherHp = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherHp );
	m_pID_CHECKBOX_OtherTitle = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherTitle );
	m_pID_CHECKBOX_OtherGroup = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherGroup );
	m_pID_CHECKBOX_OtherTong = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherTong );
	m_pID_CHECKBOX_OtherEffect = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherEffect );
	m_pID_CHECKBOX_OtherModel = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherModel );
	m_pID_CHECKBOX_TeamEffect = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamEffect );
	m_pID_CHECKBOX_TeamModel = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamModel );
	m_pID_TEXT_OtherEffect = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_TEXT_OtherEffect );
	m_pID_TEXT_OtherModel = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_TEXT_OtherModel );
	m_pID_TEXT_TeamEffect = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_TEXT_TeamEffect );
	m_pID_TEXT_TeamModel = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_TEXT_TeamModel );
// 	m_pID_CHECKBOX_TeamInfoControl = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_TeamInfoControl );
// 	m_pID_CHECKBOX_OtherInfoControl = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingPlayer, ID_CHECKBOX_OtherInfoControl );

	assert( m_pID_FRAME_GameSettingPlayer );
	assert( m_pID_PICTURE_Wall1 );
	assert( m_pID_PICTURE_Wall3 );
// 	assert( m_pID_PICTURE_Wall2 );
// 	assert( m_pID_PICTURE_Wall4 );
	assert( m_pID_TEXT_TeamInfo );
	assert( m_pID_TEXT_TeamName );
	assert( m_pID_TEXT_TeamTong );
	assert( m_pID_TEXT_TeamHp );
	assert( m_pID_TEXT_TeamGuild );
	assert( m_pID_TEXT_TeamTitle );
	assert( m_pID_TEXT_OtherInfo );
	assert( m_pID_TEXT_OtherName );
	assert( m_pID_TEXT_OtherHp );
	assert( m_pID_TEXT_OtherTitle );
	assert( m_pID_TEXT_OtherGroup );
	assert( m_pID_TEXT_OtherTong );
	assert( m_pID_CHECKBOX_TeamName );
	assert( m_pID_CHECKBOX_TeamHp );
	assert( m_pID_CHECKBOX_TeamTitle );
	assert( m_pID_CHECKBOX_TeamGuild );
	assert( m_pID_CHECKBOX_TeamTong );
	assert( m_pID_CHECKBOX_OtherName );
	assert( m_pID_CHECKBOX_OtherHp );
	assert( m_pID_CHECKBOX_OtherTitle );
	assert( m_pID_CHECKBOX_OtherGroup );
	assert( m_pID_CHECKBOX_OtherTong );
	assert( m_pID_CHECKBOX_OtherEffect );
	assert( m_pID_CHECKBOX_OtherModel );
	assert( m_pID_CHECKBOX_TeamEffect );
	assert( m_pID_CHECKBOX_TeamModel );
	assert( m_pID_TEXT_OtherEffect );
	assert( m_pID_TEXT_OtherModel );
	assert( m_pID_TEXT_TeamEffect );
	assert( m_pID_TEXT_TeamModel );
// 	assert( m_pID_CHECKBOX_TeamInfoControl );
// 	assert( m_pID_CHECKBOX_OtherInfoControl );
	m_pID_FRAME_GameSettingPlayer->SetMsgHoldup(false);
	GetFrame()->SetFather(s_CUI_ID_FRAME_GameSettingUIBase.GetFrame());
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GameSettingPlayer::_UnLoadUI()
{
	m_pID_FRAME_GameSettingPlayer = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GameSettingPlayer.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GameSettingPlayer::_IsVisable()
{
	if( !m_pID_FRAME_GameSettingPlayer )
		return false;
	return m_pID_FRAME_GameSettingPlayer->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GameSettingPlayer::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_GameSettingPlayer )
		return;
	m_pID_FRAME_GameSettingPlayer->SetVisable( bVisable );
	if (bVisable)
	{
		RefreshUI();
	}
}
void CUI_ID_FRAME_GameSettingPlayer::RefreshUI()
{
    if(!m_pID_FRAME_GameSettingPlayer)
        return;

	for( int i = 0 ; i < GameSetting::eGSC_TOTAL ; ++ i )
	{
		bool bValue = ( bool )GameSetting::Instance()->GetLevel( (GameSetting::eGameSettingCategory)i );
		switch( i )
		{			
		case GameSetting::eGSC_TeamPlayerName:
			m_pID_CHECKBOX_TeamName->SetCheck( bValue );
			break;
		case GameSetting::eGSC_TeamPlayerHp:
			m_pID_CHECKBOX_TeamHp->SetCheck( bValue );
			break;
		case GameSetting::eGSC_TeamPlayerTitle:	
			m_pID_CHECKBOX_TeamTitle->SetCheck( bValue );
			break;
		case GameSetting::eGSC_TeamPlayerGuild:
			m_pID_CHECKBOX_TeamGuild->SetCheck( bValue );
			break;
		case GameSetting::eGSC_TeamPlayerTong:	
			m_pID_CHECKBOX_TeamTong->SetCheck( bValue );
			break;
		case GameSetting::eGSC_OtherPlayerName:	
			m_pID_CHECKBOX_OtherName->SetCheck( bValue );
			break;
		case GameSetting::eGSC_OtherPlayerHp:	
			m_pID_CHECKBOX_OtherHp->SetCheck( bValue );
			break;
		case GameSetting::eGSC_OtherPlayerTitle:
			m_pID_CHECKBOX_OtherTitle->SetCheck( bValue );
			break;
		case GameSetting::eGSC_OtherPlayerGuild:
			m_pID_CHECKBOX_OtherGroup->SetCheck( bValue );
			break;
		case GameSetting::eGSC_OtherPlayerTong:
			m_pID_CHECKBOX_OtherTong->SetCheck( bValue );
			break;
        case GameSetting::eGSC_OtherPlayerEffect:
            m_pID_CHECKBOX_OtherEffect->SetCheck( bValue );
            break;
        case GameSetting::eGSC_OtherPlayerModel:
            m_pID_CHECKBOX_OtherModel->SetCheck( bValue );
            break;
        case GameSetting::eGSC_TeamPlayerEffect:
            m_pID_CHECKBOX_TeamEffect->SetCheck( bValue );
            break;
        case GameSetting::eGSC_TeamPlayerModel:
            m_pID_CHECKBOX_TeamModel->SetCheck( bValue );
            break;
		default:
			break;
		}
	}
    CheckTeamInfoControl();
    CheckOtherInfoControl();
}

void CUI_ID_FRAME_GameSettingPlayer::CheckTeamInfoControl()
{
//     if( m_pID_CHECKBOX_TeamName->IsChecked()
//         && m_pID_CHECKBOX_TeamHp->IsChecked()
//         && m_pID_CHECKBOX_TeamTitle->IsChecked()
//         && m_pID_CHECKBOX_TeamGuild->IsChecked()
//         && m_pID_CHECKBOX_TeamTong->IsChecked() )
//         m_pID_CHECKBOX_TeamInfoControl->SetCheck(true);
//     else
//         m_pID_CHECKBOX_TeamInfoControl->SetCheck(false);
}

void CUI_ID_FRAME_GameSettingPlayer::CheckOtherInfoControl()
{
//     if( m_pID_CHECKBOX_OtherName->IsChecked()
//         && m_pID_CHECKBOX_OtherHp->IsChecked()
//         && m_pID_CHECKBOX_OtherTitle->IsChecked()
//         && m_pID_CHECKBOX_OtherGroup->IsChecked()
//         && m_pID_CHECKBOX_OtherTong->IsChecked() )
//         m_pID_CHECKBOX_OtherInfoControl->SetCheck(true);
//     else
//         m_pID_CHECKBOX_OtherInfoControl->SetCheck(false);
}