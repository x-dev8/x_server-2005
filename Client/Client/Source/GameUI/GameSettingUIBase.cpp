/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\gamesetting\GameSetting.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GameSettingUIBase.h"
#include "GameSettingFunction.h"
#include "GameSettingMouse.h"
#include "GameSettingPlayer.h"
#include "GameSettingScene.h"
#include "GameSettingSelf.h"
#include "GameSettingSound.h"
#include "GameSetting.h"
#include "SystemSetting.h"
#include "SystemSettingUI.h"
#include "UserData.h"
#include "XmlStringLanguage.h"
#include "GameSettingRefuse.h"
#include "GameSettingSell.h"
#include "GameSettingTab.h"
#include "SettingEffect.h"
#include "Common.h"

extern const char* GetRootPath();

CUI_ID_FRAME_GameSettingUIBase s_CUI_ID_FRAME_GameSettingUIBase;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GameSettingUIBase, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GameSettingUIBase, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingUIBase, ID_CHECKBOX_GameOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingUIBase, ID_CHECKBOX_SystemOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameSettingUIBase, ID_BUTTON_DefaultOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameSettingUIBase, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameSettingUIBase, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameSettingUIBase, ID_BUTTON_CloseOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameSettingUIBase, ID_BUTTON_HelpOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GameSettingUIBase, ID_LIST_SettingListOnListSelectChange )
CUI_ID_FRAME_GameSettingUIBase::CUI_ID_FRAME_GameSettingUIBase()
{
	// Member
	m_pID_FRAME_GameSettingUIBase = NULL;
	m_pID_CHECKBOX_Game = NULL;
	m_pID_CHECKBOX_System = NULL;
	//m_pID_PICTURE_TitleMiddle = NULL;
	m_pID_PICTURE_Title = NULL;
	m_pID_PICTURE_ListWall = NULL;
	m_pID_BUTTON_Default = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
// 	m_pID_PICTURE_TitleLeft = NULL;
// 	m_pID_PICTURE_TitleRight = NULL;
// 	m_pID_PICTURE_TitleLeftMiddle = NULL;
// 	m_pID_PICTURE_TitleRightMiddle = NULL;
	m_pID_BUTTON_Close = NULL;
	//m_pID_BUTTON_Help = NULL;
	m_pID_LIST_SettingList = NULL;
	memset( m_FrameGroup, 0, eGameSetting_Count * 4 );
}
// Frame
bool CUI_ID_FRAME_GameSettingUIBase::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GameSettingUIBase::OnFrameRender()
{
	return true;
}
// CheckBox
void CUI_ID_FRAME_GameSettingUIBase::ID_CHECKBOX_GameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
    m_SettingRadioGroup.ToggleRadio(m_pID_CHECKBOX_Game);
    m_shLastSelectTab = eSettingTab_Game;

	m_GroupGameSetting.SetVisible( true );
	//m_GroupSystemSetting.SetVisible( false );
	s_CUI_ID_FRAME_Systemset.SetVisable( false );
	//s_CUI_ID_FRAME_SettingEffect.SetVisable(false);
	if( m_pID_LIST_SettingList->GetCurSelIndex() == -1 )
		m_pID_LIST_SettingList->SetCurSelIndex( 0 );
	SetVisibleFrame( (eGameSettingUICategory)m_pID_LIST_SettingList->GetCurSelIndex() );
}
// CheckBox
void CUI_ID_FRAME_GameSettingUIBase::ID_CHECKBOX_SystemOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
    m_SettingRadioGroup.ToggleRadio(m_pID_CHECKBOX_System);
    m_shLastSelectTab = eSettingTab_Setting;

	m_GroupGameSetting.SetVisible( false );
	//s_CUI_ID_FRAME_Systemset.SetVisable( true );
	s_CUI_ID_FRAME_Systemset.SetVisable(true);
	SetVisibleFrame( eGameSetting_Count );
}
// Button
bool CUI_ID_FRAME_GameSettingUIBase::ID_BUTTON_DefaultOnButtonClick( ControlObject* pSender )
{
	GameSetting::Instance()->LoadSetting();
	GameSetting::Instance()->CommitChanges();
	RefreshUI();
	return true;
}
// Button
bool CUI_ID_FRAME_GameSettingUIBase::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	char szSetting[MAX_PATH] = {0};
	MeSprintf_s( szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s%s", CUserData::Instance()->GetUserDataPath(), GameSetting::Instance()->GetCustomSettingDirectory() );
	GameSetting::Instance()->SaveSetting( szSetting );

	//MeSprintf_s( szSetting, MAX_PATH, "%s%s", CUserData::Instance()->GetAccountDataPath(), SystemSetting::Instance()->GetCustomSettingFile() );	
	MeSprintf_s(szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s/Client/UserData/%s", GetRootPath(), SystemSetting::Instance()->GetCustomSettingFile() );
	SystemSetting::Instance()->SaveSetting( szSetting );

	SetVisable( false );
	return true;
}
// Button
bool CUI_ID_FRAME_GameSettingUIBase::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	char szSetting[MAX_PATH] = {0};
	MeSprintf_s( szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s%s", CUserData::Instance()->GetUserDataPath(), GameSetting::Instance()->GetCustomSettingDirectory() );
	GameSetting::Instance()->LoadSetting( szSetting );
	GameSetting::Instance()->CommitChanges();

	//MeSprintf_s( szSetting, MAX_PATH, "%s%s", CUserData::Instance()->GetAccountDataPath(), SystemSetting::Instance()->GetCustomSettingFile() );
	MeSprintf_s( szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s/Client/UserData/%s", GetRootPath(), SystemSetting::Instance()->GetCustomSettingFile() );
	SystemSetting::Instance()->LoadSetting( szSetting );
	SystemSetting::Instance()->CommitChanges();

	RefreshUI();
	SetVisable( false );
	return true;
}
// Button
bool CUI_ID_FRAME_GameSettingUIBase::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
	char szSetting[MAX_PATH] = {0};
	MeSprintf_s( szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s%s", CUserData::Instance()->GetUserDataPath(), GameSetting::Instance()->GetCustomSettingDirectory() );
	GameSetting::Instance()->LoadSetting( szSetting );
	GameSetting::Instance()->CommitChanges();

	//MeSprintf_s( szSetting, MAX_PATH, "%s%s", CUserData::Instance()->GetAccountDataPath(), SystemSetting::Instance()->GetCustomSettingFile() );
	MeSprintf_s( szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s/Client/UserData/%s", GetRootPath(), SystemSetting::Instance()->GetCustomSettingFile() );
	SystemSetting::Instance()->LoadSetting( szSetting );
	SystemSetting::Instance()->CommitChanges();

	RefreshUI();
	SetVisable( false );
	return true;
}
// Button
// bool CUI_ID_FRAME_GameSettingUIBase::ID_BUTTON_HelpOnButtonClick( ControlObject* pSender )
// {
// 	return true;
// }
// List
void CUI_ID_FRAME_GameSettingUIBase::ID_LIST_SettingListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	SetVisibleFrame( (eGameSettingUICategory)pItem->m_nID );
}

void CUI_ID_FRAME_GameSettingUIBase::SetVisibleFrame( eGameSettingUICategory eCat )
{
	for( int i = 0 ; i < eGameSetting_Count; ++ i )
	{
		if(m_FrameGroup[i])
		    m_FrameGroup[i]->SetVisable( false );
	}
    if( eCat >= 0 && eCat < eGameSetting_Count && m_FrameGroup[eCat] )
    {
        m_FrameGroup[eCat]->SetVisable( true );
        m_shLastSelectCategory = eCat;
    }
}

// 装载UI
bool CUI_ID_FRAME_GameSettingUIBase::_LoadUI()
{
	memset( m_FrameGroup, 0, eGameSetting_Count * 4 );
	s_CUI_ID_FRAME_GameSettingFunction.LoadUI();
	s_CUI_ID_FRAME_GameSettingFunction.SetVisable( false );
	s_CUI_ID_FRAME_GameSettingMouse.LoadUI();
	s_CUI_ID_FRAME_GameSettingMouse.SetVisable( false );
	s_CUI_ID_FRAME_GameSettingPlayer.LoadUI();
	s_CUI_ID_FRAME_GameSettingPlayer.SetVisable( false );
	s_CUI_ID_FRAME_GameSettingScene.LoadUI();
	s_CUI_ID_FRAME_GameSettingScene.SetVisable( false );
	s_CUI_ID_FRAME_GameSettingSelf.LoadUI();
	s_CUI_ID_FRAME_GameSettingSelf.SetVisable( false );
	s_CUI_ID_FRAME_GameSettingSound.LoadUI();
	s_CUI_ID_FRAME_GameSettingSound.SetVisable( false );
    s_CUI_ID_FRAME_GameSettingRefuse.LoadUI();
    s_CUI_ID_FRAME_GameSettingRefuse.SetVisable( false );
	//s_CUI_ID_FRAME_SettingEffect.LoadUI();
	//s_CUI_ID_FRAME_SettingEffect.SetVisable(false);
	s_CUI_ID_FRAME_Systemset.LoadUI();
	s_CUI_ID_FRAME_Systemset.SetVisable( false );
	s_CUI_ID_FRAME_GameSettingSell.LoadUI();
	s_CUI_ID_FRAME_GameSettingSell.SetVisable( false );
	//s_CUI_ID_FRAME_GameSettingTab.LoadUI();
	//s_CUI_ID_FRAME_GameSettingTab.SetVisable( false );
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GameSettingUIBase.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GameSetting.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GameSettingUIBase::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GameSettingUIBase, s_CUI_ID_FRAME_GameSettingUIBaseOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GameSettingUIBase, s_CUI_ID_FRAME_GameSettingUIBaseOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingUIBase, ID_CHECKBOX_Game, s_CUI_ID_FRAME_GameSettingUIBaseID_CHECKBOX_GameOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingUIBase, ID_CHECKBOX_System, s_CUI_ID_FRAME_GameSettingUIBaseID_CHECKBOX_SystemOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_GameSettingUIBase, ID_BUTTON_Default, s_CUI_ID_FRAME_GameSettingUIBaseID_BUTTON_DefaultOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GameSettingUIBase, ID_BUTTON_Ok, s_CUI_ID_FRAME_GameSettingUIBaseID_BUTTON_OkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GameSettingUIBase, ID_BUTTON_Cancel, s_CUI_ID_FRAME_GameSettingUIBaseID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GameSettingUIBase, ID_BUTTON_Close, s_CUI_ID_FRAME_GameSettingUIBaseID_BUTTON_CloseOnButtonClick );
//	theUiManager.OnButtonClick( ID_FRAME_GameSettingUIBase, ID_BUTTON_Help, s_CUI_ID_FRAME_GameSettingUIBaseID_BUTTON_HelpOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_GameSettingUIBase, ID_LIST_SettingList, s_CUI_ID_FRAME_GameSettingUIBaseID_LIST_SettingListOnListSelectChange );

	m_pID_FRAME_GameSettingUIBase = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GameSettingUIBase );
	m_pID_CHECKBOX_Game = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingUIBase, ID_CHECKBOX_Game );
	m_pID_CHECKBOX_System = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingUIBase, ID_CHECKBOX_System );
	//m_pID_PICTURE_TitleMiddle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingUIBase, ID_PICTURE_TitleMiddle );
	m_pID_PICTURE_Title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingUIBase, ID_PICTURE_Title );
	m_pID_PICTURE_ListWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingUIBase, ID_PICTURE_ListWall );
	m_pID_BUTTON_Default = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameSettingUIBase, ID_BUTTON_Default );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameSettingUIBase, ID_BUTTON_Ok );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameSettingUIBase, ID_BUTTON_Cancel );
// 	m_pID_PICTURE_TitleLeft = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingUIBase, ID_PICTURE_TitleLeft );
// 	m_pID_PICTURE_TitleRight = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingUIBase, ID_PICTURE_TitleRight );
// 	m_pID_PICTURE_TitleLeftMiddle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingUIBase, ID_PICTURE_TitleLeftMiddle );
// 	m_pID_PICTURE_TitleRightMiddle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingUIBase, ID_PICTURE_TitleRightMiddle );
	m_pID_BUTTON_Close = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameSettingUIBase, ID_BUTTON_Close );
//	m_pID_BUTTON_Help = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameSettingUIBase, ID_BUTTON_Help );
	m_pID_LIST_SettingList = (ControlList*)theUiManager.FindControl( ID_FRAME_GameSettingUIBase, ID_LIST_SettingList );
	assert( m_pID_FRAME_GameSettingUIBase );
	assert( m_pID_CHECKBOX_Game );
	assert( m_pID_CHECKBOX_System );
	//assert( m_pID_PICTURE_TitleMiddle );
	assert( m_pID_PICTURE_Title );
	assert( m_pID_PICTURE_ListWall );
	assert( m_pID_BUTTON_Default );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_BUTTON_Cancel );
// 	assert( m_pID_PICTURE_TitleLeft );
// 	assert( m_pID_PICTURE_TitleRight );
// 	assert( m_pID_PICTURE_TitleLeftMiddle );
// 	assert( m_pID_PICTURE_TitleRightMiddle );
	assert( m_pID_BUTTON_Close );
//	assert( m_pID_BUTTON_Help );
	assert( m_pID_LIST_SettingList );


	m_FrameGroup[eGameSetting_Function] =  &s_CUI_ID_FRAME_GameSettingFunction;
	m_FrameGroup[eGameSetting_Mouse] = &s_CUI_ID_FRAME_GameSettingMouse ;
	m_FrameGroup[eGameSetting_Player] = &s_CUI_ID_FRAME_GameSettingPlayer ;
	m_FrameGroup[eGameSetting_Scene] = &s_CUI_ID_FRAME_GameSettingScene ;
	m_FrameGroup[eGameSetting_Self] = &s_CUI_ID_FRAME_GameSettingSelf ;
	m_FrameGroup[eGameSetting_Sound] = &s_CUI_ID_FRAME_GameSettingSound ;
	m_FrameGroup[eGameSetting_Refuse] = &s_CUI_ID_FRAME_GameSettingRefuse;
	m_FrameGroup[eGameSetting_Sell] = &s_CUI_ID_FRAME_GameSettingSell;
//     if(s_CUI_ID_FRAME_GameSettingFunction.GetFrame())
//     {
//         /*s_CUI_ID_FRAME_GameSettingFunction.m_pID_FRAME_GameSettingFunction*/
//         s_CUI_ID_FRAME_GameSettingFunction.GetFrame()->SetFather( m_pID_FRAME_GameSettingUIBase);	
//     }
//     if(s_CUI_ID_FRAME_GameSettingMouse.GetFrame())
//     {
// 	    s_CUI_ID_FRAME_GameSettingMouse.GetFrame()->SetFather( m_pID_FRAME_GameSettingUIBase);
//     }
// 	
//     if(s_CUI_ID_FRAME_GameSettingPlayer.GetFrame())
//     {
//         s_CUI_ID_FRAME_GameSettingPlayer.GetFrame()->SetFather( m_pID_FRAME_GameSettingUIBase);
//     }
// 
// 
//     if(s_CUI_ID_FRAME_GameSettingScene.GetFrame())
//     {
//         s_CUI_ID_FRAME_GameSettingScene.GetFrame()->SetFather( m_pID_FRAME_GameSettingUIBase);
//      }
// 	
//     if(s_CUI_ID_FRAME_GameSettingSelf.GetFrame())
//     {
//         s_CUI_ID_FRAME_GameSettingSelf.GetFrame()->SetFather( m_pID_FRAME_GameSettingUIBase);	
//     }
// 
//     if(s_CUI_ID_FRAME_GameSettingSound.GetFrame())
//     {
//         s_CUI_ID_FRAME_GameSettingSound.GetFrame()->SetFather( m_pID_FRAME_GameSettingUIBase );
//     }
// 
//     if(s_CUI_ID_FRAME_GameSettingRefuse.GetFrame())
//     {
//         s_CUI_ID_FRAME_GameSettingRefuse.GetFrame()->SetFather( m_pID_FRAME_GameSettingUIBase );
//     }
// 
//     if(s_CUI_ID_FRAME_GameSettingSell.GetFrame())
//     {
//         s_CUI_ID_FRAME_GameSettingSell.GetFrame()->SetFather( m_pID_FRAME_GameSettingUIBase );
//     }
// 
// 	if( s_CUI_ID_FRAME_Systemset.GetFrame() )
// 		s_CUI_ID_FRAME_Systemset.GetFrame()->SetFather( m_pID_FRAME_GameSettingUIBase );

	m_GroupGameSetting.AddControl( m_pID_LIST_SettingList );
	m_GroupGameSetting.AddControl( m_pID_PICTURE_ListWall );
// 	if( s_CUI_ID_FRAME_Systemset.GetFrame() )
// 		m_GroupSystemSetting.AddControl( s_CUI_ID_FRAME_Systemset.GetFrame() );

    m_SettingRadioGroup.AddRadio(m_pID_CHECKBOX_Game);
    m_SettingRadioGroup.AddRadio(m_pID_CHECKBOX_System);
    m_SettingRadioGroup.ToggleRadio(m_pID_CHECKBOX_Game);

	m_FrameName[eGameSetting_Self] = theXmlString.GetString( eGameSettingList_Self );
	m_FrameName[eGameSetting_Player] = theXmlString.GetString( eGameSettingList_Player );
	m_FrameName[eGameSetting_Scene] = theXmlString.GetString( eGameSettingList_Npc );
	m_FrameName[eGameSetting_Function] = theXmlString.GetString( eGameSettingList_Function );
	m_FrameName[eGameSetting_Mouse] = theXmlString.GetString( eGameSettingList_Mouse );
	m_FrameName[eGameSetting_Sound] = theXmlString.GetString( eGameSettingList_Sound );
	m_FrameName[eGameSetting_Refuse] = theXmlString.GetString( eGameSettingList_Refuse );
	m_FrameName[eGameSetting_Sell] = theXmlString.GetString( eGameSettingList_Sell );
	//m_FrameName[eGameSetting_Tab] = theXmlString.GetString( eGameSettingList_Tab );

    m_shLastSelectTab = eSettingTab_Game;
    m_shLastSelectCategory = eGameSetting_Self;


	FillFrameList();

	RefreshUI();

	SetVisibleFrame( eGameSetting_Count );
	m_pID_FRAME_GameSettingUIBase->SetMsgProcFun( frame_msg );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GameSettingUIBase::_UnLoadUI()
{
	m_GroupGameSetting.Clear();
 	m_GroupSystemSetting.Clear();
    m_SettingRadioGroup.Clear();
	s_CUI_ID_FRAME_GameSettingFunction.UnLoadUI();
	s_CUI_ID_FRAME_GameSettingMouse.UnLoadUI();
	s_CUI_ID_FRAME_GameSettingPlayer.UnLoadUI();
	s_CUI_ID_FRAME_GameSettingScene.UnLoadUI();
	s_CUI_ID_FRAME_GameSettingSelf.UnLoadUI();
	s_CUI_ID_FRAME_GameSettingSound.UnLoadUI();
    s_CUI_ID_FRAME_GameSettingRefuse.UnLoadUI();
	//s_CUI_ID_FRAME_Systemset.UnLoadUI();
	//s_CUI_ID_FRAME_SettingEffect.UnLoadUI();
	s_CUI_ID_FRAME_GameSettingSell.UnLoadUI();
	s_CUI_ID_FRAME_Systemset.UnLoadUI();
	//s_CUI_ID_FRAME_GameSettingTab.UnLoadUI();
	m_pID_FRAME_GameSettingUIBase = NULL;
	memset( m_FrameGroup, 0, eGameSetting_Count * 4 );

	return theUiManager.RemoveFrame( "Data\\UI\\GameSettingUIBase.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GameSettingUIBase::_IsVisable()
{
    if(!m_pID_FRAME_GameSettingUIBase)
        return false;
	return m_pID_FRAME_GameSettingUIBase->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GameSettingUIBase::_SetVisable( const bool bVisable )
{
	if (NULL == m_pID_FRAME_GameSettingUIBase)
	{
		return;
	}
	
	m_pID_FRAME_GameSettingUIBase->SetVisable( bVisable );
	if( bVisable )
	{
		bool bCheck = true;
        if( m_shLastSelectTab == eSettingTab_Game )
        {
		    ID_CHECKBOX_GameOnCheckBoxCheck( 0, &bCheck );
        }
        else
        {
            ID_CHECKBOX_SystemOnCheckBoxCheck( 0, &bCheck );
        }
	}
}

void CUI_ID_FRAME_GameSettingUIBase::FillFrameList()
{
	m_pID_LIST_SettingList->Clear();
	for( int i = 0 ; i < eGameSetting_Count; ++ i )
	{
		ControlList::S_List stItem;
		stItem.clear();
	    stItem.SetData( m_FrameName[i].c_str(), i );
		m_pID_LIST_SettingList->AddItem( &stItem );
	}
}
void CUI_ID_FRAME_GameSettingUIBase::RefreshUI()
{
	s_CUI_ID_FRAME_Systemset.Refresh();
	//s_CUI_ID_FRAME_SettingEffect.Refresh();
	s_CUI_ID_FRAME_GameSettingFunction.RefreshUI();
	s_CUI_ID_FRAME_GameSettingMouse.RefreshUI();
	s_CUI_ID_FRAME_GameSettingPlayer.RefreshUI();
	s_CUI_ID_FRAME_GameSettingScene.RefreshUI();
	s_CUI_ID_FRAME_GameSettingSelf.RefreshUI();
	s_CUI_ID_FRAME_GameSettingSound.RefreshUI();
    s_CUI_ID_FRAME_GameSettingRefuse.RefreshUI();
	s_CUI_ID_FRAME_GameSettingSell.RefreshUI();
	//s_CUI_ID_FRAME_GameSettingTab.RefreshUI();
}
bool CUI_ID_FRAME_GameSettingUIBase::frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	if( !s_CUI_ID_FRAME_Systemset.IsVisable() )
		return false;
	switch( msg ) 
	{		
	case WM_LBUTTONDOWN:
		{
			if( bMsgUsed )
				s_CUI_ID_FRAME_Systemset.SCROLLBAREX_allset_SetValue( 5 );
		}
		break;
	}

	return false;

}