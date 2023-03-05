/********************************************************************
	Created by UIEditor.exe
	FileName: D:\Tj\Client\UI\SelfRbtnMenu.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SelfRbtnMenu.h"
#include "Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Group.h"
#include "SelectAssignMode.h"
#include "MessageBox.h"
#include "ChatInfoBox.h"
#include "color_config.h"
#include "RbtnMenu.h"
#include "XmlStringLanguage.h"
#include "PetRbtnMenu.h"
#include "ScreenInfoManager.h"
#include "FriendDlgRight.h"
#include "Team.h"
#include "ui/SuAnimalMenu.h"
#include "ui/Team.h"
CUI_ID_FRAME_SelfRBMenu s_CUI_ID_FRAME_SelfRBMenu;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SelfRBMenu, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SelfRBMenu, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelfRBMenu, ID_BUTTON_DisbandOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelfRBMenu, ID_BUTTON_GetoutOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelfRBMenu, ID_BUTTON_DisMountOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelfRBMenu, ID_BUTTON_AssignModeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelfRBMenu, ID_BUTTON_SelectQualityOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelfRBMenu, ID_BUTTON_FreeModeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelfRBMenu, ID_BUTTON_TeamModeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelfRBMenu, ID_BUTTON_LeaderModeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelfRBMenu, ID_BUTTON_EscOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelfRBMenu, ID_BUTTON_Quality2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelfRBMenu, ID_BUTTON_Quality3OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelfRBMenu, ID_BUTTON_Quality4OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelfRBMenu, ID_BUTTON_QuitOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelfRBMenu, ID_BUTTON_CloseOnButtonClick )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelfRBMenu, ID_BUTTON_CJDWOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelfRBMenu, ID_BUTTON_QXGSOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelfRBMenu, ID_BUTTON_ZDGSOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelfRBMenu, ID_BUTTON_ClearTeamMapOnButtonClick )


CUI_ID_FRAME_SelfRBMenu::CUI_ID_FRAME_SelfRBMenu()
{
	// SGuildMember
	ResetMembers();
}
void CUI_ID_FRAME_SelfRBMenu::ResetMembers()
{
	m_pID_FRAME_SelfRBMenu = NULL;
	m_pID_BUTTON_Disband = NULL;
	m_pID_BUTTON_Getout = NULL;
	m_pID_BUTTON_DisMount = NULL;
	m_pID_BUTTON_AssignMode = NULL;
	m_pID_BUTTON_SelectQuality = NULL;
	m_pID_BUTTON_FreeMode = NULL;
	m_pID_BUTTON_TeamMode = NULL;
	m_pID_BUTTON_LeaderMode = NULL;
	m_pID_BUTTON_Esc = NULL;
	m_pID_BUTTON_Quality2 = NULL;
	m_pID_BUTTON_Quality3 = NULL;
	m_pID_BUTTON_Quality4 = NULL;
	m_pID_BUTTON_Quit = NULL;
// 	m_pID_PICTURE_AssignLeft = NULL;
// 	m_pID_PICTURE_QualityLeft = NULL;
// 	m_pID_PICTURE_FreeMode = NULL;
// 	m_pID_PICTURE_TeamMode = NULL;
// 	m_pID_PICTURE_LeaderMode = NULL;
// 	m_pID_PICTURE_Quality2 = NULL;
// 	m_pID_PICTURE_Quality3 = NULL;
// 	m_pID_PICTURE_Quality4 = NULL;
	m_pID_BUTTON_Close = NULL;
	//m_pID_PICTURE_QualityLeft2 = NULL;
	m_pID_BUTTON_CJDW = NULL;
	m_pID_BUTTON_QXGS = NULL;
	m_pID_BUTTON_ZDGS = NULL;
	m_pID_BUTTON_ClearTeamMap = NULL;
    m_ucSelectAssignMode = AssignMode_Team;
}
// Frame
bool CUI_ID_FRAME_SelfRBMenu::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_SelfRBMenu::OnFrameRender()
{
	return true;
}

void CUI_ID_FRAME_SelfRBMenu::GetoutOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SelfRBMenu )
		return;
	ID_BUTTON_GetoutOnButtonClick(pSender);
}
// Button
bool CUI_ID_FRAME_SelfRBMenu::ID_BUTTON_DisbandOnButtonClick( ControlObject* pSender )
{//解散
	guardfunc;
	if( !m_pID_FRAME_SelfRBMenu )
		return false;
	s_CUI_ID_FRAME_Team.CheckChangeFollowState();
	MsgExitTeam msg;
	GettheNetworkInput().SendMsg( &msg );
	SetVisable( FALSE );
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_SelfRBMenu::ID_BUTTON_GetoutOnButtonClick( ControlObject* pSender )
{//离队
	if( !m_pID_FRAME_SelfRBMenu )
		return false;
	s_CUI_ID_FRAME_Team.CheckChangeFollowState();
	MsgExitTeam msg;
	GettheNetworkInput().SendMsg( &msg );
	SetVisable( FALSE );
	//s_CUI_ID_FRAME_Team.RefreshTeamInfo();
	s_CUI_ID_FRAME_Team.ClearAllTeamInfo();
	return true;
}

//////////////////////////////////////////////////////////////////////////
//下马
bool CUI_ID_FRAME_SelfRBMenu::ID_BUTTON_DisMountOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_SelfRBMenu )
		return false;
	if( theHeroGame.GetPlayerMgr()->GetMe() )
		theHeroGame.GetPlayerMgr()->GetMe()->DisMount();

	theHeroGame.GetPlayerMgr()->ChangeDrome( -1 );
	
	SetVisable(FALSE);
	return true;
	unguard;
}
// 分配模式
// Button
bool CUI_ID_FRAME_SelfRBMenu::ID_BUTTON_AssignModeOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SelfRBMenu )
		return false;
    bool bMeIsHeader = thePlayerRole.IsTeamHeader();
    if( bMeIsHeader )
    {
        if( !m_bShowAssignMode )
        {
            m_pID_BUTTON_FreeMode->SetVisable(true);
            m_pID_BUTTON_TeamMode->SetVisable(true);
            m_pID_BUTTON_LeaderMode->SetVisable(true);
            m_pID_BUTTON_Esc->SetVisable(true);
//             switch( thePlayerRole.GetAssignMode() )
//             {
//             case AssignMode_FreeMode:
//                 m_pID_PICTURE_FreeMode->SetVisable(true);
//                 m_pID_PICTURE_TeamMode->SetVisable(false);
//                 m_pID_PICTURE_LeaderMode->SetVisable(false);
//                 break;
//             case AssignMode_Team:
//                 m_pID_PICTURE_FreeMode->SetVisable(false);
//                 m_pID_PICTURE_TeamMode->SetVisable(true);
//                 m_pID_PICTURE_LeaderMode->SetVisable(false);
//                 break;
//             case AssignMode_Assign:
//                 m_pID_PICTURE_FreeMode->SetVisable(false);
//                 m_pID_PICTURE_TeamMode->SetVisable(false);
//                 m_pID_PICTURE_LeaderMode->SetVisable(true);
//                 break;
//             }
            m_bShowAssignMode = true;
//             m_pID_PICTURE_QualityLeft->SetVisable(true);
//             m_pID_PICTURE_QualityLeft2->SetVisable(true);
        }
        else
        {
            // 隐藏分配模式和需求品质子界面
            ID_BUTTON_QuitOnButtonClick(NULL);
            ID_BUTTON_EscOnButtonClick(NULL);
        }
    }
    else
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Item_Arrange, theXmlString.GetString( eText_Team_CannotChangeTeamMode ) );
    }
    return true;
}
// Button
bool CUI_ID_FRAME_SelfRBMenu::ID_BUTTON_FreeModeOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SelfRBMenu )
		return false;
    /*bool bMeIsHeader = thePlayerRole.IsTeamHeader();
    if( bMeIsHeader )
    {
        if( thePlayerRole.GetAssignMode() != AssignMode_FreeMode )
        {
            SetAssignMode(AssignMode_FreeMode);
        }
    }*/
	return true;
}
// Button
bool CUI_ID_FRAME_SelfRBMenu::ID_BUTTON_TeamModeOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SelfRBMenu )
		return false;
    bool bMeIsHeader = thePlayerRole.IsTeamHeader();
    if( bMeIsHeader )
    {
        if( m_ucSelectAssignMode == AssignMode_Team )
        {
            ShowSelectQualityButtons(!m_bShowSelectQuality);
        }
        else
        {
            m_ucSelectAssignMode = AssignMode_Team;
            ShowSelectQualityButtons(true);
        }
    }
    return true;
}
// Button
bool CUI_ID_FRAME_SelfRBMenu::ID_BUTTON_LeaderModeOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SelfRBMenu )
		return false;
    /*bool bMeIsHeader = thePlayerRole.IsTeamHeader();
    if( bMeIsHeader )
    {
        if( m_ucSelectAssignMode == AssignMode_Assign )
            ShowSelectQualityButtons(!m_bShowSelectQuality);
        else
        {
            m_ucSelectAssignMode = AssignMode_Assign;
            ShowSelectQualityButtons(true);
        }
    }*/
    return true;
}
// Button
bool CUI_ID_FRAME_SelfRBMenu::ID_BUTTON_EscOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SelfRBMenu )
		return false;
    m_pID_BUTTON_FreeMode->SetVisable(false);
    m_pID_BUTTON_TeamMode->SetVisable(false);
    m_pID_BUTTON_LeaderMode->SetVisable(false);
    m_pID_BUTTON_Esc->SetVisable(false);
//     m_pID_PICTURE_FreeMode->SetVisable(false);
//     m_pID_PICTURE_TeamMode->SetVisable(false);
//     m_pID_PICTURE_LeaderMode->SetVisable(false);
//     m_pID_PICTURE_QualityLeft->SetVisable(false);
//     m_pID_PICTURE_QualityLeft2->SetVisable(false);
    m_bShowAssignMode = false;
	return true;
}
// 物品需求品质
// Button
bool CUI_ID_FRAME_SelfRBMenu::ID_BUTTON_SelectQualityOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SelfRBMenu )
		return false;
    return true;
}

// Button
bool CUI_ID_FRAME_SelfRBMenu::ID_BUTTON_Quality2OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SelfRBMenu )
		return false;
    bool bMeIsHeader = thePlayerRole.IsTeamHeader();
    if( bMeIsHeader )
    {
        CheckSetAssignMode();
        if( thePlayerRole.GetItemRollLevel() != eIL_Choiceness )
        {
            SetQuality(eIL_Choiceness);
        }
    }
	return true;
}
// Button
bool CUI_ID_FRAME_SelfRBMenu::ID_BUTTON_Quality3OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SelfRBMenu )
		return false;
    bool bMeIsHeader = thePlayerRole.IsTeamHeader();
    if( bMeIsHeader )
    {
        CheckSetAssignMode();
        if( thePlayerRole.GetItemRollLevel() != eIL_Polish )
        {
            SetQuality(eIL_Polish);
        }
    }
	return true;
}
// Button
bool CUI_ID_FRAME_SelfRBMenu::ID_BUTTON_Quality4OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SelfRBMenu )
		return false;
    bool bMeIsHeader = thePlayerRole.IsTeamHeader();
    if( bMeIsHeader )
    {
        CheckSetAssignMode();
        if( thePlayerRole.GetItemRollLevel() != eIL_Nonsuch )
        {
            SetQuality(eIL_Nonsuch);
        }
    }
	return true;
}
// Button
bool CUI_ID_FRAME_SelfRBMenu::ID_BUTTON_QuitOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SelfRBMenu )
		return false;
    m_pID_BUTTON_Quality2->SetVisable(false);
    m_pID_BUTTON_Quality3->SetVisable(false);
    m_pID_BUTTON_Quality4->SetVisable(false);
    m_pID_BUTTON_Quit->SetVisable(false);
//     m_pID_PICTURE_Quality2->SetVisable(false);
//     m_pID_PICTURE_Quality3->SetVisable(false);
//     m_pID_PICTURE_Quality4->SetVisable(false);
    m_bShowSelectQuality = false;
	return true;
}
// Button
bool CUI_ID_FRAME_SelfRBMenu::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SelfRBMenu )
		return false;
    SetVisable(false);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_SelfRBMenu::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\SelfRbtnMenu.meui", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SelfRbtnMenu.UI]失败")
		return false;
	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_SelfRBMenu::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_SelfRBMenu, s_CUI_ID_FRAME_SelfRBMenuOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SelfRBMenu, s_CUI_ID_FRAME_SelfRBMenuOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_SelfRBMenu, ID_BUTTON_Disband, s_CUI_ID_FRAME_SelfRBMenuID_BUTTON_DisbandOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SelfRBMenu, ID_BUTTON_Getout, s_CUI_ID_FRAME_SelfRBMenuID_BUTTON_GetoutOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SelfRBMenu, ID_BUTTON_DisMount, s_CUI_ID_FRAME_SelfRBMenuID_BUTTON_DisMountOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_SelfRBMenu, ID_BUTTON_AssignMode, s_CUI_ID_FRAME_SelfRBMenuID_BUTTON_AssignModeOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_SelfRBMenu, ID_BUTTON_SelectQuality, s_CUI_ID_FRAME_SelfRBMenuID_BUTTON_SelectQualityOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_SelfRBMenu, ID_BUTTON_FreeMode, s_CUI_ID_FRAME_SelfRBMenuID_BUTTON_FreeModeOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_SelfRBMenu, ID_BUTTON_TeamMode, s_CUI_ID_FRAME_SelfRBMenuID_BUTTON_TeamModeOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_SelfRBMenu, ID_BUTTON_LeaderMode, s_CUI_ID_FRAME_SelfRBMenuID_BUTTON_LeaderModeOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_SelfRBMenu, ID_BUTTON_Esc, s_CUI_ID_FRAME_SelfRBMenuID_BUTTON_EscOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_SelfRBMenu, ID_BUTTON_Quality2, s_CUI_ID_FRAME_SelfRBMenuID_BUTTON_Quality2OnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_SelfRBMenu, ID_BUTTON_Quality3, s_CUI_ID_FRAME_SelfRBMenuID_BUTTON_Quality3OnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_SelfRBMenu, ID_BUTTON_Quality4, s_CUI_ID_FRAME_SelfRBMenuID_BUTTON_Quality4OnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_SelfRBMenu, ID_BUTTON_Quit, s_CUI_ID_FRAME_SelfRBMenuID_BUTTON_QuitOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_SelfRBMenu, ID_BUTTON_Close, s_CUI_ID_FRAME_SelfRBMenuID_BUTTON_CloseOnButtonClick );

	theUiManager.OnButtonClick( ID_FRAME_SelfRBMenu, ID_BUTTON_CJDW, s_CUI_ID_FRAME_SelfRBMenuID_BUTTON_CJDWOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SelfRBMenu, ID_BUTTON_QXGS, s_CUI_ID_FRAME_SelfRBMenuID_BUTTON_QXGSOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SelfRBMenu, ID_BUTTON_ZDGS, s_CUI_ID_FRAME_SelfRBMenuID_BUTTON_ZDGSOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SelfRBMenu, ID_BUTTON_ClearTeamMap, s_CUI_ID_FRAME_SelfRBMenuID_BUTTON_ClearTeamMapOnButtonClick );
	

	m_pID_FRAME_SelfRBMenu = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SelfRBMenu );
	m_pID_BUTTON_Disband = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_BUTTON_Disband );
	m_pID_BUTTON_Getout = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_BUTTON_Getout );
	m_pID_BUTTON_DisMount = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_BUTTON_DisMount );
	m_pID_BUTTON_AssignMode = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_BUTTON_AssignMode );
	m_pID_BUTTON_SelectQuality = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_BUTTON_SelectQuality );
	m_pID_BUTTON_FreeMode = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_BUTTON_FreeMode );
	m_pID_BUTTON_TeamMode = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_BUTTON_TeamMode );
	m_pID_BUTTON_LeaderMode = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_BUTTON_LeaderMode );
	m_pID_BUTTON_Esc = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_BUTTON_Esc );
	m_pID_BUTTON_Quality2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_BUTTON_Quality2 );
	m_pID_BUTTON_Quality3 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_BUTTON_Quality3 );
	m_pID_BUTTON_Quality4 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_BUTTON_Quality4 );
	m_pID_BUTTON_Quit = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_BUTTON_Quit );
// 	m_pID_PICTURE_AssignLeft = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_PICTURE_AssignLeft );
// 	m_pID_PICTURE_QualityLeft = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_PICTURE_QualityLeft );
// 	m_pID_PICTURE_FreeMode = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_PICTURE_FreeMode );
// 	m_pID_PICTURE_TeamMode = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_PICTURE_TeamMode );
// 	m_pID_PICTURE_LeaderMode = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_PICTURE_LeaderMode );
// 	m_pID_PICTURE_Quality2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_PICTURE_Quality2 );
// 	m_pID_PICTURE_Quality3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_PICTURE_Quality3 );
// 	m_pID_PICTURE_Quality4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_PICTURE_Quality4 );
	m_pID_BUTTON_Close = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_BUTTON_Close );
//	m_pID_PICTURE_QualityLeft2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_PICTURE_QualityLeft2 );
	m_pID_BUTTON_CJDW = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_BUTTON_CJDW );
	m_pID_BUTTON_QXGS = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_BUTTON_QXGS );
	m_pID_BUTTON_ZDGS = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_BUTTON_ZDGS );
	m_pID_BUTTON_ClearTeamMap= (ControlButton*)theUiManager.FindControl( ID_FRAME_SelfRBMenu, ID_BUTTON_ClearTeamMap );

	m_pID_BUTTON_FreeMode->SetEnable(false);
	m_pID_BUTTON_LeaderMode->SetEnable(false);

	assert( m_pID_FRAME_SelfRBMenu );
	assert( m_pID_BUTTON_Disband );
	assert( m_pID_BUTTON_Getout );
	assert( m_pID_BUTTON_FreeMode );
	assert( m_pID_BUTTON_TeamMode );
	assert( m_pID_BUTTON_LeaderMode );
	assert( m_pID_BUTTON_Esc );
	assert( m_pID_BUTTON_Quality2 );
	assert( m_pID_BUTTON_Quality3 );
	assert( m_pID_BUTTON_Quality4 );
	assert( m_pID_BUTTON_Quit );
// 	assert( m_pID_PICTURE_AssignLeft );
// 	assert( m_pID_PICTURE_QualityLeft );
// 	assert( m_pID_PICTURE_FreeMode );
// 	assert( m_pID_PICTURE_TeamMode );
// 	assert( m_pID_PICTURE_LeaderMode );
// 	assert( m_pID_PICTURE_Quality2 );
// 	assert( m_pID_PICTURE_Quality3 );
// 	assert( m_pID_PICTURE_Quality4 );
	assert( m_pID_BUTTON_Close );
//	assert( m_pID_PICTURE_QualityLeft2 );

	assert( m_pID_BUTTON_CJDW );
	assert( m_pID_BUTTON_QXGS );
	assert( m_pID_BUTTON_ZDGS );
	assert(m_pID_BUTTON_ClearTeamMap);
	SetVisable(false);
	return true;
	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_SelfRBMenu::_UnLoadUI()
{
	guardfunc;
	ResetMembers();
	return theUiManager.RemoveFrame( "data\\ui\\SelfRbtnMenu.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_SelfRBMenu::_IsVisable()
{
	guardfunc;
	if( !m_pID_FRAME_SelfRBMenu )
		return false;
	return m_pID_FRAME_SelfRBMenu->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_SelfRBMenu::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pID_FRAME_SelfRBMenu )
		return;
	m_pID_FRAME_SelfRBMenu->SetVisable( bVisable );
	if( bVisable )
	{
		m_pID_FRAME_SelfRBMenu->SetActivate( bVisable );
		s_CUI_ID_FRAME_RBTNMENU.SetVisable(false);
		s_CUI_ID_FRAME_PetRBMenu.SetVisable(false);
 		s_CUI_ID_FRAME_FriendDlgRight.SetVisable(false);
		s_CUI_ID_FRAME_SuAnimalMenu.SetVisable(false);

		m_pID_BUTTON_CJDW->SetVisable(true);			//创建队伍
		m_pID_BUTTON_AssignMode->SetVisable(true);		//分配模式
		m_pID_BUTTON_ZDGS->SetVisable(true);			//组队跟随
		m_pID_BUTTON_QXGS->SetVisable(true);			//取消跟随
		m_pID_BUTTON_Getout->SetVisable(true);			//离队
		m_pID_BUTTON_Close->SetVisable(true);			//关闭
		m_pID_BUTTON_ClearTeamMap->SetVisable(true);

		if ( thePlayerRole.GetTeamInfo().size() == 0 ) //没有队伍
		{
			m_pID_BUTTON_CJDW->SetEnable(true);			//创建队伍
			m_pID_BUTTON_AssignMode->SetEnable(false);		//分配模式
			m_pID_BUTTON_ZDGS->SetEnable(false);			//组队跟随
			m_pID_BUTTON_QXGS->SetEnable(false);			//取消跟随
			m_pID_BUTTON_Getout->SetEnable(false);			//离队
			m_pID_BUTTON_Close->SetEnable(true);			//关闭
			m_pID_BUTTON_ClearTeamMap->SetEnable(false);
		}
		else if ( thePlayerRole.IsTeamHeader() ) //队长
		{
			m_pID_BUTTON_CJDW->SetEnable(false);			//创建队伍
			m_pID_BUTTON_AssignMode->SetEnable(true);		//分配模式
			m_pID_BUTTON_ClearTeamMap->SetEnable(true);

			int teamFollowCount = s_CUI_ID_FRAME_Team.GetTeamFollowCount();

			if ( teamFollowCount == 0 )
			{
				m_pID_BUTTON_QXGS->SetEnable( false );
			}
			else if ( teamFollowCount > 0 )
			{
				m_pID_BUTTON_QXGS->SetEnable( true );
			}

			//当队伍里面的人全部处于跟随状态的时候，跟随按钮无效
			if ( teamFollowCount == int(thePlayerRole.GetTeamInfo().size()) - 1 )
			{
				m_pID_BUTTON_ZDGS->SetEnable(false);
			}
			else
			{
				m_pID_BUTTON_ZDGS->SetEnable(true);
			}

			m_pID_BUTTON_Getout->SetEnable(true);			//离队
			m_pID_BUTTON_Close->SetEnable(true);			//关闭
		}
		else	//普通队员
		{
			m_pID_BUTTON_CJDW->SetEnable(false);			//创建队伍
			m_pID_BUTTON_AssignMode->SetEnable(true);		//分配模式
			m_pID_BUTTON_ZDGS->SetEnable(false);			//组队跟随
			m_pID_BUTTON_ClearTeamMap->SetEnable(false);
			if ( s_CUI_ID_FRAME_Team.GetTeamFollowID() >= 0 )
			{
				m_pID_BUTTON_QXGS->SetEnable(true);			//取消跟随
			}
			else
			{
				m_pID_BUTTON_QXGS->SetEnable(false);
			}
			m_pID_BUTTON_Getout->SetEnable(true);			//离队
			m_pID_BUTTON_Close->SetEnable(true);			//关闭
		}

	}
	else
		return;

	int x,y;
	x = theUiManager.m_ptMoust.x;
	y = theUiManager.m_ptMoust.y;
	m_pID_FRAME_SelfRBMenu->SetPos( x, y );

    m_bShowAssignMode = false;
    m_bShowSelectQuality = false;
	m_pID_BUTTON_Disband->SetVisable(false);
	m_pID_BUTTON_DisMount->SetVisable(false);
	//m_pID_BUTTON_Getout->SetVisable(false);
	//m_pID_BUTTON_AssignMode->SetVisable( false );
    m_pID_BUTTON_AssignMode->SetShowTip(false);
    //m_pID_BUTTON_SelectQuality->SetVisable( false );
    m_pID_BUTTON_SelectQuality->SetShowTip(false);
    m_pID_BUTTON_FreeMode->SetVisable( false );
    m_pID_BUTTON_TeamMode->SetVisable( false );
    m_pID_BUTTON_LeaderMode->SetVisable( false );
    //m_pID_BUTTON_Esc->SetVisable( false );
    m_pID_BUTTON_Quality2->SetVisable( false );
    m_pID_BUTTON_Quality3->SetVisable( false );
    m_pID_BUTTON_Quality4->SetVisable( false );
    m_pID_BUTTON_Quit->SetVisable( false );
//     m_pID_PICTURE_AssignLeft->SetVisable( false );
//         m_pID_PICTURE_QualityLeft->SetVisable( false );
//         m_pID_PICTURE_FreeMode->SetVisable( false );
//         m_pID_PICTURE_TeamMode->SetVisable( false );
//         m_pID_PICTURE_LeaderMode->SetVisable( false );
//         m_pID_PICTURE_Quality2->SetVisable( false );
//         m_pID_PICTURE_Quality3->SetVisable( false );
//         m_pID_PICTURE_Quality4->SetVisable( false );
    m_pID_BUTTON_Close->SetVisable(false);
   // m_pID_PICTURE_QualityLeft2->SetVisable(false);

	if( thePlayerRole.GetTeamMemberNum() > 0 )
	{
		RECT rc;
		m_pID_BUTTON_AssignMode->GetRealRect( &rc );

		bool bMeIsHeader = thePlayerRole.IsTeamHeader();
//         m_pID_PICTURE_AssignLeft->SetVisable( true );
//         if( bMeIsHeader )
//         {
//             m_pID_PICTURE_AssignLeft->SetEnable(true);
//         }
//         else
//         {
//             m_pID_PICTURE_AssignLeft->SetEnable(false);
//         }

        //分配模式
        UpdateAssignModeButton();
        m_pID_BUTTON_AssignMode->SetVisable( true );
        m_pID_BUTTON_AssignMode->SetShowTip(true);

		m_pID_BUTTON_Getout->SetVisable(true);
        m_pID_BUTTON_Close->SetVisable(true);
	}

	unguard;
}

void CUI_ID_FRAME_SelfRBMenu::SetAssignMode( unsigned char ucMode )
{
    MsgReqChangeAssignMode kMsg;
    kMsg.AssignMode = ucMode;
    GettheNetworkInput().SendMsg( &kMsg );
}

void CUI_ID_FRAME_SelfRBMenu::SetQuality( unsigned char ucQuality )
{
    MsgChangeAssignItemLevelReq kMsg;
    kMsg.chAssignItemLevel = ucQuality;
    GettheNetworkInput().SendMsg( &kMsg );
}

void CUI_ID_FRAME_SelfRBMenu::UpdateAssignMode()
{
	if( !m_pID_FRAME_SelfRBMenu )
		return;
    ID_BUTTON_EscOnButtonClick(NULL);
    ID_BUTTON_QuitOnButtonClick(NULL);
    UpdateAssignModeButton();
}

void CUI_ID_FRAME_SelfRBMenu::UpdateSelectQuality()
{
	if( !m_pID_FRAME_SelfRBMenu )
		return;
   ID_BUTTON_EscOnButtonClick(NULL);
    ID_BUTTON_QuitOnButtonClick(NULL);
    UpdateSelectQualityButton();
}

void CUI_ID_FRAME_SelfRBMenu::UpdateAssignModeButton()
{
    switch( thePlayerRole.GetAssignMode() )
    {
    case AssignMode_FreeMode:
        //m_pID_BUTTON_AssignMode->SetCaption(theXmlString.GetString(eText_TeamAssignMode_Free));
        break;
    case AssignMode_Team:
        //m_pID_BUTTON_AssignMode->SetCaption(theXmlString.GetString(eText_TeamAssignMode_Team));
        break;
    case AssignMode_Assign:
        //m_pID_BUTTON_AssignMode->SetCaption(theXmlString.GetString(eText_TeamAssignMode_Assign));
        break;
    }
	BOOL bIsTeamHeader = thePlayerRole.IsTeamHeader();
	if (!bIsTeamHeader)
	{
		m_pID_BUTTON_AssignMode->SetEnable(false);
	}
    // 更新Tips
    UpdateAssignModeTips();
}

void CUI_ID_FRAME_SelfRBMenu::UpdateSelectQualityButton()
{
    switch( thePlayerRole.GetItemRollLevel() )
    {
    case eIL_Choiceness:
        {
            DWORD color = S_IconInfoHero::GetQualityColor( eIL_Choiceness );
            SetSelectQualityCaptionColor(theXmlString.GetString(ePreItemText_LiangPin), color);
        }
        break;
    case eIL_Polish:
        {
            DWORD color = S_IconInfoHero::GetQualityColor( eIL_Polish );
            SetSelectQualityCaptionColor(theXmlString.GetString(ePreItemText_JingPin), color);
        }
        break;
    case eIL_Nonsuch:
        {
            DWORD color = S_IconInfoHero::GetQualityColor( eIL_Nonsuch );
            SetSelectQualityCaptionColor(theXmlString.GetString(ePreItemText_JiPin), color);
        }
        break;
    }
    // 更新Tips
    UpdateAssignModeTips();
}

void CUI_ID_FRAME_SelfRBMenu::SetSelectQualityCaptionColor( const char* szCaption, DWORD color )
{
    S_ButtonData *pButtonData = (S_ButtonData*)m_pID_BUTTON_SelectQuality->GetData();
    pButtonData->m_colFontNormal = color;
    pButtonData->m_colFontMoveOn = color;
    pButtonData->m_colFontPress = color;
    pButtonData->m_colFontDisabled = color;
    m_pID_BUTTON_SelectQuality->setFontCurrentColor(color);

    m_pID_BUTTON_SelectQuality->SetCaption(szCaption);
}

void CUI_ID_FRAME_SelfRBMenu::CheckSetAssignMode()
{
    if( thePlayerRole.GetAssignMode() != m_ucSelectAssignMode )
    {
        SetAssignMode(m_ucSelectAssignMode);
    }
}

void CUI_ID_FRAME_SelfRBMenu::UpdateAssignModeTips()
{
    const char *pStrQuality = NULL;
    DWORD color = 0;
    switch( thePlayerRole.GetItemRollLevel() )
    {
    case eIL_Choiceness:
        color = S_IconInfoHero::GetQualityColor( eIL_Choiceness );
        pStrQuality = theXmlString.GetString(ePreItemText_LiangPin);
        break;
    case eIL_Polish:
        color = S_IconInfoHero::GetQualityColor( eIL_Polish );
        pStrQuality = theXmlString.GetString(ePreItemText_JingPin);
        break;
    case eIL_Nonsuch:
        color = S_IconInfoHero::GetQualityColor( eIL_Nonsuch );
        pStrQuality = theXmlString.GetString(ePreItemText_JiPin);
        break;
    }

    switch( thePlayerRole.GetAssignMode() )
    {
    case AssignMode_FreeMode:
        m_pID_BUTTON_AssignMode->setTip(theXmlString.GetString(eText_TeamModeTips_FreeMode));
        break;
    case AssignMode_Team:
        {
            char text[MAX_PATH] = {0};
            char quality[MAX_PATH] = {0};
            sprintf(quality, "<#%8X>%s",color, pStrQuality);
            sprintf(text, theXmlString.GetString(eText_TeamModeTips_TeamMode), quality);
            m_pID_BUTTON_AssignMode->setTip(text);
        }
        break;
    case AssignMode_Assign:
        {
            char text[MAX_PATH] = {0};
            char quality[MAX_PATH] = {0};
            sprintf(quality, "<#%8X>%s",color, pStrQuality);
            sprintf(text, theXmlString.GetString(eText_TeamModeTips_AssignMode), quality);
            m_pID_BUTTON_AssignMode->setTip(text);
        }
        break;
    }
}

void CUI_ID_FRAME_SelfRBMenu::ShowSelectQualityButtons( bool bshow )
{
    bool bMeIsHeader = thePlayerRole.IsTeamHeader();
    if( bMeIsHeader )
    {
        if( bshow )
        {
            m_pID_BUTTON_Quality2->SetVisable(true);
            m_pID_BUTTON_Quality3->SetVisable(true);
            m_pID_BUTTON_Quality4->SetVisable(true);
            m_pID_BUTTON_Quit->SetVisable(true);
            short shQuality = eIL_Choiceness;
            if( thePlayerRole.GetAssignMode() == m_ucSelectAssignMode )
            {
                shQuality = thePlayerRole.GetItemRollLevel();
            }
//             switch( shQuality )
//             {
//             case eIL_Choiceness:
//                 m_pID_PICTURE_Quality2->SetVisable(true);
//                 m_pID_PICTURE_Quality3->SetVisable(false);
//                 m_pID_PICTURE_Quality4->SetVisable(false);
//                 break;
//             case eIL_Polish:
//                 m_pID_PICTURE_Quality2->SetVisable(false);
//                 m_pID_PICTURE_Quality3->SetVisable(true);
//                 m_pID_PICTURE_Quality4->SetVisable(false);
//                 break;
//             case eIL_Nonsuch:
//                 m_pID_PICTURE_Quality2->SetVisable(false);
//                 m_pID_PICTURE_Quality3->SetVisable(false);
//                 m_pID_PICTURE_Quality4->SetVisable(true);
//                 break;
//             }
            // 修正位置
            if( m_ucSelectAssignMode == AssignMode_Team )
            {
                RECT rect;
                RECT rect1;
                int iPosY; 
                m_pID_BUTTON_TeamMode->GetRealRect(&rect);
                iPosY = rect.top + 2;
                m_pID_BUTTON_Quality2->GetRealRect(&rect1);
                m_pID_BUTTON_Quality2->SetYPos(iPosY);
               // m_pID_PICTURE_Quality2->SetYPos(iPosY+4);
                iPosY += rect1.bottom - rect1.top;
                m_pID_BUTTON_Quality3->GetRealRect(&rect1);
                m_pID_BUTTON_Quality3->SetYPos(iPosY);
                //m_pID_PICTURE_Quality3->SetYPos(iPosY+4);
                iPosY += rect1.bottom - rect1.top;
                m_pID_BUTTON_Quality4->GetRealRect(&rect1);
                m_pID_BUTTON_Quality4->SetYPos(iPosY);
               // m_pID_PICTURE_Quality4->SetYPos(iPosY+4);
                iPosY += rect1.bottom - rect1.top;
            }
            else if( m_ucSelectAssignMode == AssignMode_Assign )
            {
                RECT rect;
                RECT rect1;
                int iPosY; 
                m_pID_BUTTON_LeaderMode->GetRealRect(&rect);
                iPosY = rect.top;
                m_pID_BUTTON_Quality2->GetRealRect(&rect1);
                m_pID_BUTTON_Quality2->SetYPos(iPosY);
//                 m_pID_PICTURE_Quality2->SetYPos(iPosY+4);
                iPosY += rect1.bottom - rect1.top;
                m_pID_BUTTON_Quality3->GetRealRect(&rect1);
                m_pID_BUTTON_Quality3->SetYPos(iPosY);
              //  m_pID_PICTURE_Quality3->SetYPos(iPosY+4);
                iPosY += rect1.bottom - rect1.top;
                m_pID_BUTTON_Quality4->GetRealRect(&rect1);
                m_pID_BUTTON_Quality4->SetYPos(iPosY);
               // m_pID_PICTURE_Quality4->SetYPos(iPosY+4);
                iPosY += rect1.bottom - rect1.top;
            }
            m_bShowSelectQuality = true;
        }
        else
        {
            ID_BUTTON_QuitOnButtonClick(NULL);
        }
    }
    else
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Item_Arrange, theXmlString.GetString( eText_Team_CannotChangeQuality ) );
    }
}

// Button
bool CUI_ID_FRAME_SelfRBMenu::ID_BUTTON_CJDWOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SelfRBMenu )
		return false;

	//战场中不可以创建队伍
	//if(thePlayerRole.GetCampType() != CampDefine::NoneCamp)
	//{
	//	//不可以创建队伍
	//	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eClient_CampBattle_Team));
	//	return true;
	//}

	MsgCreateTeam msg;
	sprintf( msg.szTeamName, "%s", "testTeam" );
	msg.AssignMode = thePlayerRole.GetAssignMode();
	msg.AssignItemLevel = thePlayerRole.GetItemRollLevel();
	GettheNetworkInput().SendMsg(&msg);

	SetVisable(false);
	s_CUI_ID_FRAME_Team.SetCurrentView();
	s_CUI_ID_FRAME_Team.SetVisable(true);
	return true;
}
// Button
bool CUI_ID_FRAME_SelfRBMenu::ID_BUTTON_QXGSOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SelfRBMenu )
		return false;

	if ( s_CUI_ID_FRAME_Team.GetTeamFollowID() >= 0 )
	{
		//这个只有队友才会处理
		s_CUI_ID_FRAME_Team.SetTeamFollowID( -1 );
		SetVisable(false);
	}

	
	if ( thePlayerRole.IsTeamHeader() )
	{
		MsgHeaderCancelTeamFollow msg;
		GettheNetworkInput().SendMsg(&msg);
	}
	else
	{
		MsgCancelTeamFollow msg;
		GettheNetworkInput().SendMsg(&msg);
	}

	SetVisable(false);

	return true;
}
// Button
bool CUI_ID_FRAME_SelfRBMenu::ID_BUTTON_ZDGSOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SelfRBMenu )
		return false;
	MsgReqTeamFollow msg;
	GettheNetworkInput().SendMsg(&msg);

	SetVisable(false);
	return true;
}
bool CUI_ID_FRAME_SelfRBMenu::ID_BUTTON_ClearTeamMapOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SelfRBMenu )
		return false;
	s_CUI_ID_FRAME_Team.ClearAllTeamMutiMap();
	SetVisable(false);
	return true;
}