/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\PetRbtnMenu.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PetRbtnMenu.h"
#include "RbtnMenu.h"
#include "SelfRbtnMenu.h"
#include "Rename.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "FriendDlgRight.h"
CUI_ID_FRAME_PetRBMenu s_CUI_ID_FRAME_PetRBMenu;
MAP_FRAME_RUN( s_CUI_ID_FRAME_PetRBMenu, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PetRBMenu, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PetRBMenu, ID_BUTTON_ChangeNameOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PetRBMenu, ID_BUTTON_CloseOnButtonClick )
CUI_ID_FRAME_PetRBMenu::CUI_ID_FRAME_PetRBMenu()
{
	// Member
	m_pID_FRAME_PetRBMenu = NULL;
	m_pID_BUTTON_ChangeName = NULL;
	m_pID_BUTTON_Close = NULL;

}
// Frame
bool CUI_ID_FRAME_PetRBMenu::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_PetRBMenu::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_PetRBMenu::ID_BUTTON_ChangeNameOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PetRBMenu )
		return false;
	s_CUI_ID_FRAME_Rename.SetType(CUI_ID_FRAME_Rename::eChangePet);
	s_CUI_ID_FRAME_Rename.SetVisable(true);
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_PetRBMenu::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PetRBMenu )
		return false;
	SetVisable(false);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_PetRBMenu::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PetRbtnMenu.MEUI", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\PetRbtnMenu.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_PetRBMenu::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PetRBMenu, s_CUI_ID_FRAME_PetRBMenuOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PetRBMenu, s_CUI_ID_FRAME_PetRBMenuOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_PetRBMenu, ID_BUTTON_ChangeName, s_CUI_ID_FRAME_PetRBMenuID_BUTTON_ChangeNameOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetRBMenu, ID_BUTTON_Close, s_CUI_ID_FRAME_PetRBMenuID_BUTTON_CloseOnButtonClick );

	m_pID_FRAME_PetRBMenu = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PetRBMenu );
	m_pID_BUTTON_ChangeName = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetRBMenu, ID_BUTTON_ChangeName );
	m_pID_BUTTON_Close = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetRBMenu, ID_BUTTON_Close );
	assert( m_pID_FRAME_PetRBMenu );
	assert( m_pID_BUTTON_ChangeName );
	assert( m_pID_BUTTON_Close );


	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_PetRBMenu::_UnLoadUI()
{
	m_pID_FRAME_PetRBMenu = NULL;
	m_pID_BUTTON_ChangeName = NULL;
	m_pID_BUTTON_Close = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\PetRbtnMenu.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_PetRBMenu::_IsVisable()
{
	if( !m_pID_FRAME_PetRBMenu )
		return false;
	return m_pID_FRAME_PetRBMenu->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_PetRBMenu::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_PetRBMenu )
		return;
	m_pID_FRAME_PetRBMenu->SetVisable( bVisable );
	if( bVisable )
	{
		m_pID_FRAME_PetRBMenu->SetActivate( bVisable );
		s_CUI_ID_FRAME_RBTNMENU.SetVisable(false);
		s_CUI_ID_FRAME_SelfRBMenu.SetVisable(false);
 		s_CUI_ID_FRAME_FriendDlgRight.SetVisable(false);
	}
	else
		return;
	int x,y;
	x = theUiManager.m_ptMoust.x;
	y = theUiManager.m_ptMoust.y;
	m_pID_FRAME_PetRBMenu->SetPos( x, y );
}

void CUI_ID_FRAME_PetRBMenu::ChangePetName( const char* szName )
{
	if( !m_pID_FRAME_PetRBMenu )
		return;
	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if( !pMe ) return;
	CPlayer *pPetPlayer = theHeroGame.GetPlayerMgr()->FindByID( pMe->GetPetID() );
	if (!pPetPlayer)
	{
		return;
	}

}