/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\FriendDlgRight.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "FriendDlgRight.h"
#include "RbtnMenu.h"
#include "FriendDlg.h"
#include "SelfRbtnMenu.h"
#include "PetRbtnMenu.h"
#include "PlayerRole.h"
#include "ChatInfoBox.h"
#include "GameMain.h"
#include "PlayerMgr.h"
static bool RFriendMenuMsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	if ( !s_CUI_ID_FRAME_RBTNMENU.IsVisable() )
		return false;

	switch( msg ) 
	{
	case WM_KEYUP:
		{
			if( wParam == VK_ESCAPE )
			{
				s_CUI_ID_FRAME_FriendDlgRight.SetVisable(false);
				return true;
			}
		}
		break;
	}

	return false;
}

CUI_ID_FRAME_FriendDlgRight s_CUI_ID_FRAME_FriendDlgRight;
MAP_FRAME_RUN( s_CUI_ID_FRAME_FriendDlgRight, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_FriendDlgRight, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FriendDlgRight, ID_BUTTON_AddClassOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FriendDlgRight, ID_BUTTON_DelClassOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FriendDlgRight, ID_BUTTON_RenameClassOnButtonClick )
CUI_ID_FRAME_FriendDlgRight::CUI_ID_FRAME_FriendDlgRight()
{
	// Member
	m_pID_FRAME_FriendDlgRight = NULL;
	m_pID_BUTTON_AddClass = NULL;
	m_pID_BUTTON_DelClass = NULL;
	m_pID_BUTTON_RenameClass = NULL;

}
// Frame
bool CUI_ID_FRAME_FriendDlgRight::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_FriendDlgRight::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_FriendDlgRight::ID_BUTTON_AddClassOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_FriendDlgRight )
		return false;
	s_CUI_ID_FRAME_Friend.ID_BUTTON_AddingOnButtonClick(NULL);
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_FriendDlgRight::ID_BUTTON_DelClassOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_FriendDlgRight )
		return false;
	CUI_ID_FRAME_Friend::ID_BUTTON_RemoveOnButtonClick(NULL);
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_FriendDlgRight::ID_BUTTON_RenameClassOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_FriendDlgRight )
		return false;
	s_CUI_ID_FRAME_Friend.ID_BUTTON_RenameOnButtonClick(NULL);
	SetVisable(false);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_FriendDlgRight::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\FriendDlgRight.MEUI" , false, UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\FriendDlgRight.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_FriendDlgRight::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_FriendDlgRight, s_CUI_ID_FRAME_FriendDlgRightOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_FriendDlgRight, s_CUI_ID_FRAME_FriendDlgRightOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_FriendDlgRight, ID_BUTTON_AddClass, s_CUI_ID_FRAME_FriendDlgRightID_BUTTON_AddClassOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_FriendDlgRight, ID_BUTTON_DelClass, s_CUI_ID_FRAME_FriendDlgRightID_BUTTON_DelClassOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_FriendDlgRight, ID_BUTTON_RenameClass, s_CUI_ID_FRAME_FriendDlgRightID_BUTTON_RenameClassOnButtonClick );

	m_pID_FRAME_FriendDlgRight = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_FriendDlgRight );
	m_pID_BUTTON_AddClass = (ControlButton*)theUiManager.FindControl( ID_FRAME_FriendDlgRight, ID_BUTTON_AddClass );
	m_pID_BUTTON_DelClass = (ControlButton*)theUiManager.FindControl( ID_FRAME_FriendDlgRight, ID_BUTTON_DelClass );
	m_pID_BUTTON_RenameClass = (ControlButton*)theUiManager.FindControl( ID_FRAME_FriendDlgRight, ID_BUTTON_RenameClass );

	assert( m_pID_FRAME_FriendDlgRight );
	assert( m_pID_BUTTON_AddClass );
	assert( m_pID_BUTTON_DelClass );
	assert( m_pID_BUTTON_RenameClass );

	m_pID_FRAME_FriendDlgRight->SetMsgProcFun( RFriendMenuMsgProc );

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_FriendDlgRight::_UnLoadUI()
{
	m_pID_FRAME_FriendDlgRight = NULL;
	m_pID_BUTTON_AddClass = NULL;
	m_pID_BUTTON_DelClass = NULL;
	m_pID_BUTTON_RenameClass = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\FriendDlgRight.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_FriendDlgRight::_IsVisable()
{
	if ( !m_pID_FRAME_FriendDlgRight )
		return false;
	return m_pID_FRAME_FriendDlgRight->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_FriendDlgRight::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_FriendDlgRight )
		return ;
	m_pID_FRAME_FriendDlgRight->SetVisable( bVisable );

	if (!bVisable)
	{
		return;
	}

	{
		m_pID_FRAME_FriendDlgRight->SetActivate( bVisable );
		s_CUI_ID_FRAME_RBTNMENU.SetVisable(false);
		s_CUI_ID_FRAME_PetRBMenu.SetVisable(false);
		s_CUI_ID_FRAME_SelfRBMenu.SetVisable(false);
	}

	int x,y;
	x = theUiManager.m_ptMoust.x;
	y = theUiManager.m_ptMoust.y;
	m_pID_FRAME_FriendDlgRight->SetPos( x, y );
}
