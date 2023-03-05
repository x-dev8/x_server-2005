/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (22)\CrowdCarryMainMore.cpp
*********************************************************************/
#include <assert.h>
#include "Common.h"
#include "NetworkInput.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "GameMain.h"
#include "MeUi/UiManager.h"
#include "CrowdCarryMainMore.h"

CUI_ID_FRAME_CrowdCarryMainMore s_CUI_ID_FRAME_CrowdCarryMainMore;
MAP_FRAME_RUN( s_CUI_ID_FRAME_CrowdCarryMainMore, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CrowdCarryMainMore, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CrowdCarryMainMore, ID_BUTTON_LiveOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_CrowdCarryMainMore, ID_LIST_PlayerOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick01OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick02OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick03OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick04OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick05OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick06OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick07OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick08OnButtonClick )
CUI_ID_FRAME_CrowdCarryMainMore::CUI_ID_FRAME_CrowdCarryMainMore()
{
	// Member
	m_pID_FRAME_CrowdCarryMainMore = NULL;
	m_pID_TEXT_Amount = NULL;
	m_pID_BUTTON_Live = NULL;
	m_pID_TEXT_CZ = NULL;
	m_pID_LIST_Player = NULL;
	m_pID_TEXT_PetName = NULL;
	m_pID_BUTTON_Kick01 = NULL;
	m_pID_BUTTON_Kick02 = NULL;
	m_pID_BUTTON_Kick03 = NULL;
	m_pID_BUTTON_Kick04 = NULL;
	m_pID_BUTTON_Kick05 = NULL;
	m_pID_BUTTON_Kick06 = NULL;
	m_pID_BUTTON_Kick07 = NULL;
	m_pID_BUTTON_Kick08 = NULL;

}
// Frame
bool CUI_ID_FRAME_CrowdCarryMainMore::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_CrowdCarryMainMore::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_CrowdCarryMainMore::ID_BUTTON_LiveOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CrowdCarryMainMore )
		return false;
	return true;
}
// List
void CUI_ID_FRAME_CrowdCarryMainMore::ID_LIST_PlayerOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_CrowdCarryMainMore )
		return;
	int idx = ((ControlList*)pSender)->GetCurSelIndex();
	if ( idx == 0 )
	{
		ShowButton(0);
	}
	else if ( idx == 1 )
	{
		ShowButton(1);
	}
	else if ( idx == 2 )
	{
		ShowButton(2);
	}
	else if ( idx == 3 )
	{
		ShowButton(3);
	}
	else if ( idx == 4 )
	{
		ShowButton(4);
	}
	else if ( idx == 5 )
	{
		ShowButton(5);
	}
	else if ( idx == 6 )
	{
		ShowButton(6);
	}
	else if ( idx == 7 )
	{
		ShowButton(7);
	}
}
// Button
bool CUI_ID_FRAME_CrowdCarryMainMore::ID_BUTTON_Kick01OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CrowdCarryMainMore )
		return false;
	KickOffPassenger(0);
	return true;
}
// Button
bool CUI_ID_FRAME_CrowdCarryMainMore::ID_BUTTON_Kick02OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CrowdCarryMainMore )
		return false;
	KickOffPassenger(1);
	return true;
}
// Button
bool CUI_ID_FRAME_CrowdCarryMainMore::ID_BUTTON_Kick03OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CrowdCarryMainMore )
		return false;
	KickOffPassenger(2);
	return true;
}
// Button
bool CUI_ID_FRAME_CrowdCarryMainMore::ID_BUTTON_Kick04OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CrowdCarryMainMore )
		return false;
	KickOffPassenger(3);
	return true;
}
// Button
bool CUI_ID_FRAME_CrowdCarryMainMore::ID_BUTTON_Kick05OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CrowdCarryMainMore )
		return false;
	KickOffPassenger(4);
	return true;
}
// Button
bool CUI_ID_FRAME_CrowdCarryMainMore::ID_BUTTON_Kick06OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CrowdCarryMainMore )
		return false;
	KickOffPassenger(5);
	return true;
}
// Button
bool CUI_ID_FRAME_CrowdCarryMainMore::ID_BUTTON_Kick07OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CrowdCarryMainMore )
		return false;
	KickOffPassenger(6);
	return true;
}
// Button
bool CUI_ID_FRAME_CrowdCarryMainMore::ID_BUTTON_Kick08OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CrowdCarryMainMore )
		return false;
	KickOffPassenger(7);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_CrowdCarryMainMore::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CrowdCarryMainMore.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CrowdCarryMainMore.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_CrowdCarryMainMore::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_CrowdCarryMainMore, s_CUI_ID_FRAME_CrowdCarryMainMoreOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_CrowdCarryMainMore, s_CUI_ID_FRAME_CrowdCarryMainMoreOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Live, s_CUI_ID_FRAME_CrowdCarryMainMoreID_BUTTON_LiveOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_CrowdCarryMainMore, ID_LIST_Player, s_CUI_ID_FRAME_CrowdCarryMainMoreID_LIST_PlayerOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick01, s_CUI_ID_FRAME_CrowdCarryMainMoreID_BUTTON_Kick01OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick02, s_CUI_ID_FRAME_CrowdCarryMainMoreID_BUTTON_Kick02OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick03, s_CUI_ID_FRAME_CrowdCarryMainMoreID_BUTTON_Kick03OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick04, s_CUI_ID_FRAME_CrowdCarryMainMoreID_BUTTON_Kick04OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick05, s_CUI_ID_FRAME_CrowdCarryMainMoreID_BUTTON_Kick05OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick06, s_CUI_ID_FRAME_CrowdCarryMainMoreID_BUTTON_Kick06OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick07, s_CUI_ID_FRAME_CrowdCarryMainMoreID_BUTTON_Kick07OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick08, s_CUI_ID_FRAME_CrowdCarryMainMoreID_BUTTON_Kick08OnButtonClick );

	m_pID_FRAME_CrowdCarryMainMore = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_CrowdCarryMainMore );
	m_pID_TEXT_Amount = (ControlText*)theUiManager.FindControl( ID_FRAME_CrowdCarryMainMore, ID_TEXT_Amount );
	m_pID_BUTTON_Live = (ControlButton*)theUiManager.FindControl( ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Live );
	m_pID_TEXT_CZ = (ControlText*)theUiManager.FindControl( ID_FRAME_CrowdCarryMainMore, ID_TEXT_CZ );
	m_pID_LIST_Player = (ControlList*)theUiManager.FindControl( ID_FRAME_CrowdCarryMainMore, ID_LIST_Player );
	m_pID_TEXT_PetName = (ControlText*)theUiManager.FindControl( ID_FRAME_CrowdCarryMainMore, ID_TEXT_PetName );
	m_pID_BUTTON_Kick01 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick01 );
	m_pID_BUTTON_Kick02 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick02 );
	m_pID_BUTTON_Kick03 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick03 );
	m_pID_BUTTON_Kick04 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick04 );
	m_pID_BUTTON_Kick05 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick05 );
	m_pID_BUTTON_Kick06 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick06 );
	m_pID_BUTTON_Kick07 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick07 );
	m_pID_BUTTON_Kick08 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CrowdCarryMainMore, ID_BUTTON_Kick08 );

	assert( m_pID_FRAME_CrowdCarryMainMore );
	assert( m_pID_TEXT_Amount );
	assert( m_pID_BUTTON_Live );
	assert( m_pID_TEXT_CZ );
	assert( m_pID_LIST_Player );
	assert( m_pID_TEXT_PetName );
	assert( m_pID_BUTTON_Kick01 );
	assert( m_pID_BUTTON_Kick02 );
	assert( m_pID_BUTTON_Kick03 );
	assert( m_pID_BUTTON_Kick04 );
	assert( m_pID_BUTTON_Kick05 );
	assert( m_pID_BUTTON_Kick06 );
	assert( m_pID_BUTTON_Kick07 );
	assert( m_pID_BUTTON_Kick08 );

	m_pID_FRAME_CrowdCarryMainMore->SetAllVisableDlg(true); 

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_CrowdCarryMainMore::_UnLoadUI()
{
	m_pID_FRAME_CrowdCarryMainMore = NULL;
	m_pID_TEXT_Amount = NULL;
	m_pID_BUTTON_Live = NULL;
	m_pID_TEXT_CZ = NULL;
	m_pID_LIST_Player = NULL;
	m_pID_TEXT_PetName = NULL;
	m_pID_BUTTON_Kick01 = NULL;
	m_pID_BUTTON_Kick02 = NULL;
	m_pID_BUTTON_Kick03 = NULL;
	m_pID_BUTTON_Kick04 = NULL;
	m_pID_BUTTON_Kick05 = NULL;
	m_pID_BUTTON_Kick06 = NULL;
	m_pID_BUTTON_Kick07 = NULL;
	m_pID_BUTTON_Kick08 = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\CrowdCarryMainMore.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_CrowdCarryMainMore::_IsVisable()
{
	if ( !m_pID_FRAME_CrowdCarryMainMore )
		return false;
	return m_pID_FRAME_CrowdCarryMainMore->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_CrowdCarryMainMore::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_CrowdCarryMainMore )
		return;
	m_pID_FRAME_CrowdCarryMainMore->SetVisable( bVisable );

	if (!bVisable)
	{
		if (theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->GetMe())
		{
			theHeroGame.GetPlayerMgr()->GetMe()->SetCarrierDriver(-1);
		}
	}
}

void CUI_ID_FRAME_CrowdCarryMainMore::RefreshPassengerList( const std::vector<int32>& ls )
{
	m_passengers.clear();
	HideAllButtons();
	m_pID_LIST_Player->Clear();
	int count = (int)ls.size();
	m_iCurSetNum = count;
	char tmpStr[64] = {0};
	MeSprintf( tmpStr, sizeof(tmpStr), "%d/%d", m_iCurSetNum, m_iTotalSetNum );
	m_pID_TEXT_Amount->SetText( tmpStr );
	if ( count == 0 )
	{
		return;
	}
	
	ControlList::S_List	stItem;
	for ( int i = 0; i < count; i ++ )
	{
		CPlayer* player = theHeroGame.GetPlayerMgr()->FindByID( ls[i] );
		if ( player )
		{
			m_passengers.push_back( ls[i] );

			stItem.clear();
			stItem.SetData(player->GetName(), 0, NULL, 0xFFFFFFFF);
			stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
			m_pID_LIST_Player->AddItem(&stItem, NULL, false);
		}
	}
	
}

bool CUI_ID_FRAME_CrowdCarryMainMore::IsOnYourBoard( int id )
{
	int count = (int)m_passengers.size();
	for ( int i = 0; i < count; i ++ )
	{
		if ( m_passengers[i] == id )
		{
			return true;
		}
	}
	return false;
}

void CUI_ID_FRAME_CrowdCarryMainMore::ShowButton( int i )
{
	HideAllButtons();
	if ( i == 0 )
	{
		m_pID_BUTTON_Kick01->SetVisable(true);
	}
	else if ( i == 1 )
	{
		m_pID_BUTTON_Kick02->SetVisable(true);
	}
	else if ( i == 2 )
	{
		m_pID_BUTTON_Kick03->SetVisable(true);
	}
	else if ( i == 3 )
	{
		m_pID_BUTTON_Kick04->SetVisable(true);
	}
	else if ( i == 4 )
	{
		m_pID_BUTTON_Kick05->SetVisable(true);
	}
	else if ( i == 5 )
	{
		m_pID_BUTTON_Kick06->SetVisable(true);
	}
	else if ( i == 6 )
	{
		m_pID_BUTTON_Kick07->SetVisable(true);
	}
	else if ( i == 7 )
	{
		m_pID_BUTTON_Kick08->SetVisable(true);
	}
}

void CUI_ID_FRAME_CrowdCarryMainMore::HideAllButtons()
{
	m_pID_BUTTON_Kick01->SetVisable(false);
	m_pID_BUTTON_Kick02->SetVisable(false);
	m_pID_BUTTON_Kick03->SetVisable(false);
	m_pID_BUTTON_Kick04->SetVisable(false);
	m_pID_BUTTON_Kick05->SetVisable(false);
	m_pID_BUTTON_Kick06->SetVisable(false);
	m_pID_BUTTON_Kick07->SetVisable(false);
	m_pID_BUTTON_Kick08->SetVisable(false);
}

void CUI_ID_FRAME_CrowdCarryMainMore::KickOffPassenger( int i )
{
	if ( m_passengers.size() > i )
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
		if ( pMe )
		{
			//MsgReqGotOffDrome msg;
			//msg.driverId = pMe->GetID();	//自己是驾驶员，踢人下去
			//msg.riderId = m_passengers[i];
			//GettheNetworkInput().SendMsg(&msg);
			MsgRiderOffDrome msg;
			msg.driverId = pMe->GetID();
			msg.riderId = m_passengers[i];
			GettheNetworkInput().SendMsg(&msg);
		}
	}
}