/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\Lottery\LotteryGame.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "LotteryGameUI.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "LotteryStatus.h"
#include "ItemDetail.h"
#include "LuckRewardConfig.h"
#include "NetworkInput.h"
#include "PlayerRole.h"
#include "XmlStringLanguage.h"
#include "ui/MessageBox.h"
#include "ShowScreenText.h"
#include "color_config.h"
#include "ui/UIMgr.h"
#include "ui/Pack.h"
#include "MeUi/IconManager.h"
#include "Cfg.h"
#include "PackItemEnableManager.h"


CUI_ID_FRAME_LotteryGame s_CUI_ID_FRAME_LotteryGame;
MAP_FRAME_RUN( s_CUI_ID_FRAME_LotteryGame, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_LotteryGame, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LotteryGame, ID_BUTTON_OpenOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LotteryGame, ID_BUTTON_StopOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LotteryGame, ID_BUTTON_GetAwardsOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_LotteryGame, ID_LISTIMG_ChestOnIconDragOn )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_LotteryGame, ID_LISTIMG_ChestOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_LotteryGame, ID_LISTIMG_KeyOnIconDragOn )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_LotteryGame, ID_LISTIMG_KeyOnIconRButtonUp )
DWORD CUI_ID_FRAME_LotteryGame::ms_dwFirstEndTime = 0;
CUI_ID_FRAME_LotteryGame::CUI_ID_FRAME_LotteryGame()
{
	// Member
	ResetMembers();

	RollSystemStatusBase* pkState = MeNew LotteryStatus< LOTTERYSTATUS_DEFAULT >;
	pkState->InitData();
	RollSystemStatusMan<RST_Lottery>::Instance()->AddState( pkState );

	pkState = MeNew LotteryStatus< LOTTERYSTATUS_ROLL_BEGIN >;
	pkState->InitData();
	RollSystemStatusMan<RST_Lottery>::Instance()->AddState( pkState );

	pkState = MeNew LotteryStatus< LOTTERYSTATUS_ROLL_END >;
	pkState->InitData();		
	LotteryStatus< LOTTERYSTATUS_ROLL_END >* pkEndState = dynamic_cast< LotteryStatus< LOTTERYSTATUS_ROLL_END >* >( pkState );
	pkEndState->SetPostUpdateFunc( PostUpdateInRollingEnd );
	RollSystemStatusMan<RST_Lottery>::Instance()->AddState( pkState );

	pkState = MeNew LotteryStatus< LOTTERYSTATUS_READYGET >;
	pkState->InitData();
	RollSystemStatusMan<RST_Lottery>::Instance()->AddState( pkState );
}

void CUI_ID_FRAME_LotteryGame::ResetMembers()
{
	m_pID_FRAME_LotteryGame = NULL;
	m_pID_TEXT_LotteryName = NULL;
	m_pID_LISTIMG_Item1 = NULL;
	m_pID_LISTIMG_Item2 = NULL;
	m_pID_LISTIMG_Item3 = NULL;
	m_pID_LISTIMG_Item4 = NULL;
	m_pID_LISTIMG_Item5 = NULL;
	m_pID_LISTIMG_Item6 = NULL;
	m_pID_LISTIMG_Item7 = NULL;
	m_pID_LISTIMG_Item8 = NULL;
	m_pID_LISTIMG_Item9 = NULL;
	m_pID_LISTIMG_Item10 = NULL;
	m_pID_LISTIMG_Item11 = NULL;
	m_pID_LISTIMG_Item12 = NULL;
	m_pID_LISTIMG_Item13 = NULL;
	m_pID_LISTIMG_Item14 = NULL;
	m_pID_LISTIMG_Item15 = NULL;
	m_pID_LISTIMG_Item16 = NULL;
	m_pID_LISTIMG_Item17 = NULL;
	m_pID_LISTIMG_Item18 = NULL;
	m_pID_LISTIMG_Item19 = NULL;
	m_pID_LISTIMG_Item20 = NULL;
	m_pID_LISTIMG_Item21 = NULL;
	m_pID_LISTIMG_Item22 = NULL;
	m_pID_LISTIMG_Item23 = NULL;
	m_pID_LISTIMG_Item24 = NULL;
	m_pID_PICTURE_FinallyAward = NULL;
	m_pID_BUTTON_Open = NULL;
	m_pID_BUTTON_Stop = NULL;
	m_pID_BUTTON_GetAwards = NULL;
	m_pID_PICTURE_GetAwardLight = NULL;
	m_pID_LISTIMG_Chest = NULL;
	m_pID_LISTIMG_Key = NULL;
	m_pID_PICTURE_LotteryBackground1 = NULL;
	m_pID_PICTURE_LotteryBackground2 = NULL;
	m_pID_PICTURE_LotteryBackground3 = NULL;
	m_pID_PICTURE_LotteryBackground4 = NULL;
	m_pID_PICTURE_LotteryBackground5 = NULL;
	m_pID_PICTURE_LotteryBackground6 = NULL;
	m_pID_PICTURE_LotteryBackground7 = NULL;
}
// Frame
bool CUI_ID_FRAME_LotteryGame::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_LotteryGame::OnFrameRender()
{
	UpdatePicRect();
	if( RollSystemStatusMan<RST_Lottery>::Instance()->GetCurrentState() )
	{
		RollSystemStatusMan<RST_Lottery>::Instance()->GetCurrentState()->Update();
		RollSystemStatusMan<RST_Lottery>::Instance()->GetCurrentState()->Render();
		RenderMiddlePic();
	}
	if( m_pID_LISTIMG_Chest->GetNullItem() != -1 ||
		m_pID_LISTIMG_Key->GetNullItem() != -1 )
		m_pID_BUTTON_Open->SetEnable( false );
	else
		m_pID_BUTTON_Open->SetEnable( true );
	return true;
}	
// Button
bool CUI_ID_FRAME_LotteryGame::ID_BUTTON_OpenOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_LotteryGame)
		return false;
	m_pID_BUTTON_Open->SetVisable( false );
	m_pID_BUTTON_Stop->SetVisable( true );
	m_pID_BUTTON_Stop->SetEnable( true );
	m_pID_BUTTON_GetAwards->SetVisable( false );

	RollSystemStatusMan<RST_Lottery>::Instance()->ChangeState( LOTTERYSTATUS_ROLL_BEGIN );

	
	return true;
}
// Button
bool CUI_ID_FRAME_LotteryGame::ID_BUTTON_StopOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_LotteryGame)
		return false;
	m_pID_BUTTON_Open->SetVisable( false );

    //接到回的消息再改变状态
    m_pID_BUTTON_Stop->SetEnable( false );

	m_pID_BUTTON_GetAwards->SetVisable( true );
	// 使用之前存储的背包数据。这里需要保证在这之间没有任何改变这些变量的操作
	MsgTreasureBoxReq msg;
	msg.uchOperate = MsgTreasureBoxReq::ECD_Type_Luck;
	msg.ucBoxItemBagType = m_ucItemBagType;
	msg.nBoxGuid = m_nGuid;
	msg.stBoxIndex = m_stIndex;
	msg.ucKeyItemBagType = m_ucKeyBagType;
	msg.nKeyGuid = m_nKeyGuid;
	msg.stKeyIndex = m_stKeyIndex;
	GettheNetworkInput().SendMsg( &msg );
	return true;
}
// Button
bool CUI_ID_FRAME_LotteryGame::ID_BUTTON_GetAwardsOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_LotteryGame)
		return false;
	MsgTreasureBoxReq msg;
	msg.uchOperate = MsgTreasureBoxReq::ECD_Type_Receive;
	msg.ucBoxItemBagType = m_ucItemBagType;
	msg.nBoxGuid = m_nGuid;
	msg.stBoxIndex = m_stIndex;
	GettheNetworkInput().SendMsg( &msg );
	SetVisable( false );
	return true;
}
bool CUI_ID_FRAME_LotteryGame::ID_LISTIMG_ChestOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															ControlIconDrag::S_ListImg* pItemDrag,
															ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!m_pID_FRAME_LotteryGame)
		return false;
	return false;
}
bool CUI_ID_FRAME_LotteryGame::ID_LISTIMG_ChestOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_LotteryGame)
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_LotteryGame::ID_LISTIMG_KeyOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!m_pID_FRAME_LotteryGame)
		return false;
	return false;
}
bool CUI_ID_FRAME_LotteryGame::ID_LISTIMG_KeyOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_LotteryGame)
		return false;
	return false;
}

// 装载UI
bool CUI_ID_FRAME_LotteryGame::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\LotteryGame.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\LotteryGame.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_LotteryGame::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_LotteryGame, s_CUI_ID_FRAME_LotteryGameOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_LotteryGame, s_CUI_ID_FRAME_LotteryGameOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_LotteryGame, ID_BUTTON_Open, s_CUI_ID_FRAME_LotteryGameID_BUTTON_OpenOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_LotteryGame, ID_BUTTON_Stop, s_CUI_ID_FRAME_LotteryGameID_BUTTON_StopOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_LotteryGame, ID_BUTTON_GetAwards, s_CUI_ID_FRAME_LotteryGameID_BUTTON_GetAwardsOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_LotteryGame, ID_LISTIMG_Chest, s_CUI_ID_FRAME_LotteryGameID_LISTIMG_ChestOnIconDragOn );
	theUiManager.OnIconRButtonUp( ID_FRAME_LotteryGame, ID_LISTIMG_Chest, s_CUI_ID_FRAME_LotteryGameID_LISTIMG_ChestOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_LotteryGame, ID_LISTIMG_Key, s_CUI_ID_FRAME_LotteryGameID_LISTIMG_KeyOnIconDragOn );
	theUiManager.OnIconRButtonUp( ID_FRAME_LotteryGame, ID_LISTIMG_Key, s_CUI_ID_FRAME_LotteryGameID_LISTIMG_KeyOnIconRButtonUp );

	m_pID_FRAME_LotteryGame = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_LotteryGame );
	m_pID_TEXT_LotteryName = (ControlText*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_TEXT_LotteryName );
	m_pID_LISTIMG_Item1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item1 );
	m_pID_LISTIMG_Item2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item2 );
	m_pID_LISTIMG_Item3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item3 );
	m_pID_LISTIMG_Item4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item4 );
	m_pID_LISTIMG_Item5 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item5 );
	m_pID_LISTIMG_Item6 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item6 );
	m_pID_LISTIMG_Item7 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item7 );
	m_pID_LISTIMG_Item8 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item8 );
	m_pID_LISTIMG_Item9 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item9 );
	m_pID_LISTIMG_Item10 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item10 );
	m_pID_LISTIMG_Item11 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item11 );
	m_pID_LISTIMG_Item12 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item12 );
	m_pID_LISTIMG_Item13 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item13 );
	m_pID_LISTIMG_Item14 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item14 );
	m_pID_LISTIMG_Item15 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item15 );
	m_pID_LISTIMG_Item16 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item16 );
	m_pID_LISTIMG_Item17 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item17 );
	m_pID_LISTIMG_Item18 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item18 );
	m_pID_LISTIMG_Item19 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item19 );
	m_pID_LISTIMG_Item20 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item20 );
	m_pID_LISTIMG_Item21 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item21 );
	m_pID_LISTIMG_Item22 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item22 );
	m_pID_LISTIMG_Item23 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item23 );
	m_pID_LISTIMG_Item24 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Item24 );
	m_pID_PICTURE_FinallyAward = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_PICTURE_FinallyAward );
	m_pID_BUTTON_Open = (ControlButton*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_BUTTON_Open );
	m_pID_BUTTON_Stop = (ControlButton*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_BUTTON_Stop );
	m_pID_BUTTON_GetAwards = (ControlButton*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_BUTTON_GetAwards );
	m_pID_LISTIMG_Chest = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Chest );
	m_pID_LISTIMG_Key = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_LISTIMG_Key );
	m_pID_PICTURE_LotteryBackground1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_PICTURE_LotteryBackground1 );
	m_pID_PICTURE_LotteryBackground2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_PICTURE_LotteryBackground2 );
	m_pID_PICTURE_LotteryBackground3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_PICTURE_LotteryBackground3 );
	m_pID_PICTURE_LotteryBackground4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_PICTURE_LotteryBackground4 );
	m_pID_PICTURE_LotteryBackground5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_PICTURE_LotteryBackground5 );
	m_pID_PICTURE_LotteryBackground6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_PICTURE_LotteryBackground6 );
	m_pID_PICTURE_LotteryBackground7 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LotteryGame, ID_PICTURE_LotteryBackground7 );
	assert( m_pID_FRAME_LotteryGame );
	assert( m_pID_TEXT_LotteryName );
	assert( m_pID_LISTIMG_Item1 );
	assert( m_pID_LISTIMG_Item2 );
	assert( m_pID_LISTIMG_Item3 );
	assert( m_pID_LISTIMG_Item4 );
	assert( m_pID_LISTIMG_Item5 );
	assert( m_pID_LISTIMG_Item6 );
	assert( m_pID_LISTIMG_Item7 );
	assert( m_pID_LISTIMG_Item8 );
	assert( m_pID_LISTIMG_Item9 );
	assert( m_pID_LISTIMG_Item10 );
	assert( m_pID_LISTIMG_Item11 );
	assert( m_pID_LISTIMG_Item12 );
	assert( m_pID_LISTIMG_Item13 );
	assert( m_pID_LISTIMG_Item14 );
	assert( m_pID_LISTIMG_Item15 );
	assert( m_pID_LISTIMG_Item16 );
	assert( m_pID_LISTIMG_Item17 );
	assert( m_pID_LISTIMG_Item18 );
	assert( m_pID_LISTIMG_Item19 );
	assert( m_pID_LISTIMG_Item20 );
	assert( m_pID_LISTIMG_Item21 );
	assert( m_pID_LISTIMG_Item22 );
	assert( m_pID_LISTIMG_Item23 );
	assert( m_pID_LISTIMG_Item24 );
	assert( m_pID_PICTURE_FinallyAward );
	assert( m_pID_BUTTON_Open );
	assert( m_pID_BUTTON_Stop );
	assert( m_pID_BUTTON_GetAwards );
	assert( m_pID_LISTIMG_Chest );
	assert( m_pID_LISTIMG_Key );	
	memset( m_apBackground, 0, sizeof( m_apBackground ) );
	m_apBackground[0] = m_pID_PICTURE_LotteryBackground1;
	m_apBackground[1] = m_pID_PICTURE_LotteryBackground2;
	m_apBackground[2] = m_pID_PICTURE_LotteryBackground3;
	m_apBackground[3] = m_pID_PICTURE_LotteryBackground4;
	m_apBackground[4] = m_pID_PICTURE_LotteryBackground5;
	m_apBackground[5] = m_pID_PICTURE_LotteryBackground6;
	m_apBackground[6] = m_pID_PICTURE_LotteryBackground7;

	memset( m_apRewardControl, 0, sizeof( m_apRewardControl ) );
	m_apRewardControl[0] = m_pID_LISTIMG_Item1;
	m_apRewardControl[1] = m_pID_LISTIMG_Item2;
	m_apRewardControl[2] = m_pID_LISTIMG_Item3;
	m_apRewardControl[3] = m_pID_LISTIMG_Item4;
	m_apRewardControl[4] = m_pID_LISTIMG_Item5;
	m_apRewardControl[5] = m_pID_LISTIMG_Item6;
	m_apRewardControl[6] = m_pID_LISTIMG_Item7;
	m_apRewardControl[7] = m_pID_LISTIMG_Item8;
	m_apRewardControl[8] = m_pID_LISTIMG_Item9;
	m_apRewardControl[9] = m_pID_LISTIMG_Item10;
	m_apRewardControl[10] = m_pID_LISTIMG_Item11;
	m_apRewardControl[11] = m_pID_LISTIMG_Item12;
	m_apRewardControl[12] = m_pID_LISTIMG_Item13;
	m_apRewardControl[13] = m_pID_LISTIMG_Item14;
	m_apRewardControl[14] = m_pID_LISTIMG_Item15;
	m_apRewardControl[15] = m_pID_LISTIMG_Item16;
	m_apRewardControl[16] = m_pID_LISTIMG_Item17;
	m_apRewardControl[17] = m_pID_LISTIMG_Item18;
	m_apRewardControl[18] = m_pID_LISTIMG_Item19;
	m_apRewardControl[19] = m_pID_LISTIMG_Item20;
	m_apRewardControl[20] = m_pID_LISTIMG_Item21;
	m_apRewardControl[21] = m_pID_LISTIMG_Item22;
	m_apRewardControl[22] = m_pID_LISTIMG_Item23;
	m_apRewardControl[23] = m_pID_LISTIMG_Item24;	
	for( int i = 0 ; i < ECD_Max_TreasureCount ; ++ i )
	{
		if( m_apRewardControl[i] )
			m_apRewardControl[i]->SetEnableDrag( false );
	}

	m_uchOperate = -1;
	m_ucItemBagType = -1; // 背包类型
	m_stIndex = -1;       // 背包索引
	m_nGuid = -1;         // 物品guid
	m_uchLevel = -1;      // 宝箱等级
	m_nResultIndex = -1;  // 最终索引
	m_ucKeyBagType = -1;
	m_stKeyIndex = -1;
	m_nKeyGuid = -1;

	ConfigSound();

	SetVisable( false );
	SetCurrentBg( 0 );
	m_pID_FRAME_LotteryGame->SetOnVisibleChangedFun( OnVisibleChanged );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_LotteryGame::_UnLoadUI()
{
	ResetMembers();
	memset( m_apBackground, 0, sizeof( m_apBackground ) );
	memset( m_apRewardControl, 0, sizeof( m_apRewardControl ) );
	return theUiManager.RemoveFrame( "Data\\UI\\LotteryGame.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_LotteryGame::_IsVisable()
{
    if(!m_pID_FRAME_LotteryGame)
        return false;

	return m_pID_FRAME_LotteryGame->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_LotteryGame::_SetVisable( const bool bVisable )
{   
    if(!m_pID_FRAME_LotteryGame)
        return;

	ResetButtonState();
	m_pID_FRAME_LotteryGame->SetVisable( bVisable );
}
void CUI_ID_FRAME_LotteryGame::PostUpdateInRollingEnd()
{
	DWORD dwCurrent = HQ_TimeGetTime();
	if( ms_dwFirstEndTime == 0 )
		ms_dwFirstEndTime = dwCurrent;
	if( dwCurrent - ms_dwFirstEndTime >= 1500 )
	{
		RollSystemStatusMan<RST_Lottery>::Instance()->ChangeState( LOTTERYSTATUS_READYGET );
		s_CUI_ID_FRAME_LotteryGame.m_pID_BUTTON_GetAwards->SetVisable( true );
	}
}
void CUI_ID_FRAME_LotteryGame::UpdatePicRect()
{
	RECT rc, rc1;
	m_pID_LISTIMG_Item1->GetRealRect( &rc );
	m_pID_LISTIMG_Item2->GetRealRect( &rc1 );
	int nGap = rc1.left - rc.right;
	for( unsigned int i = 0 ; i < LOTTERYSTATUS_COUNT ; ++ i )
	{
		RollSystemStatusBase* pkState = RollSystemStatusMan<RST_Lottery>::Instance()->GetState( i );		
		if( pkState )
		{						
			pkState->SetPicRect( LOTTERYGPR_DICE, rc, nGap );
		}
	}
}
void CUI_ID_FRAME_LotteryGame::OnVisibleChanged( ControlObject* pSender )
{	
	if( !s_CUI_ID_FRAME_LotteryGame.IsVisable() )
	{
		s_CUI_ID_FRAME_LotteryGame.SetBoxValue( -1, -1, -1 );
		s_CUI_ID_FRAME_LotteryGame.SetKeyValue( -1, -1, -1 );
	}
}
void CUI_ID_FRAME_LotteryGame::ConfigSound()
{
	std::string strBase = SwGlobal::GetWorld()->GetAppDataCharDir();
	// 色子声音
	std::string strDiceSound = strBase;
	strDiceSound +="/data/audio/ui/dice.wav";	
	for( unsigned int i = 0 ; i < LOTTERYSTATUS_COUNT ; ++ i )
	{
		RollSystemStatusBase* pkState = RollSystemStatusMan<RST_Lottery>::Instance()->GetState( i );
		if( pkState )
		{			
			pkState->SetUVSound( LOTTERYGS_DICE, strDiceSound.c_str() );			
		}
	}
}
void CUI_ID_FRAME_LotteryGame::SendGetMessageToServer()
{

}
void CUI_ID_FRAME_LotteryGame::ResetButtonState()
{
	if( m_uchOperate == MsgShowTreasureBox::ECD_Type_Receive )
	{
		m_pID_BUTTON_GetAwards->SetVisable( true );
		m_pID_BUTTON_Open->SetVisable( false );
		m_pID_BUTTON_Stop->SetVisable( false );
	}
	else if( m_uchOperate == MsgShowTreasureBox::ECD_Type_Init )
	{
		m_pID_BUTTON_GetAwards->SetVisable( false );
		m_pID_BUTTON_Open->SetVisable( true );
		m_pID_BUTTON_Stop->SetVisable( false );
	}
	
}
void CUI_ID_FRAME_LotteryGame::SetCurrentBg( int nIndex )
{
    if(!m_pID_FRAME_LotteryGame)
        return;

	for( int i = 0 ; i < ECD_Max_BoxLevel ; ++ i )
	{
		if( m_apBackground[i] )
			m_apBackground[i]->SetVisable( false );
	}
	if( nIndex < 0 )
		return;
	nIndex = min( nIndex, ECD_Max_BoxLevel - 1 );
	if( m_apBackground[nIndex] )
		m_apBackground[nIndex]->SetVisable( true );
}
void CUI_ID_FRAME_LotteryGame::UpdateRewards()
{
    if(!m_pID_FRAME_LotteryGame)
        return;

	m_pID_LISTIMG_Chest->Clear();
	m_pID_LISTIMG_Key->Clear();
	m_pID_TEXT_LotteryName->SetText("");

	for( int i = 0 ; i < ECD_Max_TreasureCount; ++ i )
	{	
		if( m_apRewardControl[i] )
			m_apRewardControl[i]->Clear();
	}
	// 获得目标宝箱的item id
	unsigned short usNewId = 0;
	CItemBag2* pBag = 0;
	if( m_ucItemBagType == BT_NormalItemBag )
		pBag = &thePlayerRole.m_bag;
	else if( m_ucItemBagType == BT_MaterialBag )
		pBag = &thePlayerRole.m_bagMaterial;
	SCharItem kItem;
	if( !pBag )
		return;

	if( !pBag->GetItemByOnlyeID( m_nGuid, &kItem ) )
		return;

	//根据Box ItemId获取箱子名称
	std::map<unsigned short, std::string>::iterator iter_box = gCfg.m_mapLotteryBox.find( kItem.itembaseinfo.ustItemID );
	if( iter_box != gCfg.m_mapLotteryBox.end() )
	{
		std::string strBoxName = iter_box->second;
		m_pID_TEXT_LotteryName->SetText(strBoxName);
	}

	usNewId = kItem.itembaseinfo.ustItemID;
	ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( kItem.itembaseinfo.ustItemID );
	if( pCommon && pCommon->ucItemType == ItemDefine::ITEMTYPE_TREASUREBOX )
	{
		ItemDefine::SItemTreasureBox* pBox = ( ItemDefine::SItemTreasureBox* )pCommon;
		if( pBox && pBox->uchBoxType == ItemDefine::SItemTreasureBox::BoxType_Luck )
			usNewId = pBox->ustNewItemID;
	}

	for( int i = 0 ; i < ECD_Max_TreasureCount; ++ i )
	{
		const TreasureData* pData = theTreasureBoxConfig.GetTreasureData( m_uchLevel, usNewId, i );
		if( !pData )
			continue;
		ControlListImage::S_ListImg kImg;
		kImg.SetData( pData->GetItemID(), pData->GetCount(), eIcon_Enable, true );
		if( m_apRewardControl[i] )
			m_apRewardControl[i]->SetItem( &kImg );
	}
	
	if( m_uchOperate == MsgShowTreasureBox::ECD_Type_Receive )
	{
		RollSystemStatusMan<RST_Lottery>::Instance()->ChangeState( LOTTERYSTATUS_READYGET );
		RollSystemStatusMan<RST_Lottery>::Instance()->GetState( LOTTERYSTATUS_READYGET )->SetCurrentDiceAnimState( m_nResultIndex );
	}
	else if( m_uchOperate == MsgShowTreasureBox::ECD_Type_Init )
	{
		RollSystemStatusMan<RST_Lottery>::Instance()->ChangeState( LOTTERYSTATUS_DEFAULT );
	}
}
void CUI_ID_FRAME_LotteryGame::ChangeBoxItemId( unsigned char ucBagtype, short stIndex, __int64 nGuid, short stNewId )
{
    if(!m_pID_FRAME_LotteryGame)
        return;

	unsigned short usNewId = 0;
	CItemBag2* pBag = 0;
	if( ucBagtype == BT_NormalItemBag )
		pBag = &thePlayerRole.m_bag;
	else if( ucBagtype == BT_MaterialBag )
		pBag = &thePlayerRole.m_bagMaterial;
	SCharItem kItem;
	if( !pBag )
		return;
	if( pBag->GetItem( stIndex, &kItem ) )
	{
		if( kItem.itembaseinfo.nOnlyInt != nGuid )
			if( !pBag->GetItemByOnlyeID( nGuid, &kItem ) )
				return;//没有这个guid的物品
	}
	SCharItem* pItem = pBag->GetCharItemFromIdx( pBag->GetItemIndexByGUID( nGuid ) );
	if( !pItem )
		return;
	pItem->itembaseinfo.ustItemID = stNewId;
	if( ucBagtype == BT_NormalItemBag )
		s_CUI_ID_FRAME_PACK.RefreshNormalPackByIndex( pBag->GetItemIndexByGUID( nGuid ) );
	else if( ucBagtype == BT_MaterialBag )
		s_CUI_ID_FRAME_PACK.RefreshMaterialPackByIndex( pBag->GetItemIndexByGUID( nGuid ) );
	
}

void CUI_ID_FRAME_LotteryGame::SetTargetResultIndex( unsigned char ucTargetIndex )
{
    if(!m_pID_FRAME_LotteryGame)
        return;

	RollSystemStatusMan<RST_Lottery>::Instance()->ChangeState( LOTTERYSTATUS_ROLL_END );
	RollSystemStatusMan<RST_Lottery>::Instance()->GetState( LOTTERYSTATUS_ROLL_END )->SetTargetDiceAnimState( ucTargetIndex );
}
void CUI_ID_FRAME_LotteryGame::UpdateBoxNKeyUI()
{
    if(!m_pID_FRAME_LotteryGame)
        return;

	if( m_uchOperate == MsgShowTreasureBox::ECD_Type_Receive )
		return;

	// 将box和key的icon放在ui上

	CItemBag2* pBag = 0;
	if( m_ucItemBagType == BT_NormalItemBag )
	{
		pBag = &thePlayerRole.m_bag;
	}
	else if( m_ucItemBagType == BT_MaterialBag )
	{
		pBag = &thePlayerRole.m_bagMaterial;
	}
	SCharItem kBoxItem;
	if( !pBag )
		return;
	if( !pBag->GetItemByOnlyeID( m_nGuid, &kBoxItem ) )
		return;

	ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( kBoxItem.itembaseinfo.ustItemID );
	ItemDefine::SItemTreasureBox* pBox = 0;
	ItemDefine::SItemTreasureBox* pLuckBox = 0;
	if( pCommon && pCommon->ucItemType == ItemDefine::ITEMTYPE_TREASUREBOX )
	{
		pLuckBox = ( ItemDefine::SItemTreasureBox* )pCommon;
		if( !pLuckBox || pLuckBox->uchBoxType != ItemDefine::SItemTreasureBox::BoxType_Luck )
			return;	
		pCommon = GettheItemDetail().GetItemByID( pLuckBox->ustNewItemID );
		if( pCommon && pCommon->ucItemType == ItemDefine::ITEMTYPE_TREASUREBOX )
		{
			pBox = ( ItemDefine::SItemTreasureBox* )pCommon;
			if( !pBox || pBox->uchBoxType != ItemDefine::SItemTreasureBox::BoxType_Receive )
				return;
		}
	}

	ControlListImage::S_ListImg kImg;
	kImg.SetData( kBoxItem.itembaseinfo.ustItemID, 1 );
	m_pID_LISTIMG_Chest->SetItem( &kImg );

    // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
    CPackItemEnableManager::Instance()->RefreshBagItemEnable( pBag, pBag->GetItemIndexByGUID( m_nGuid ), true );

	// find key in pack
	for( int i = 0 ; i < pBag->GetNowBagSize() ; ++ i )
	{
		SCharItem* pItem = pBag->GetCharItemFromIdx( i );
		if( !pItem )
			continue;
		pCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
		if( pCommon && pCommon->ucItemType == ItemDefine::ITEMTYPE_TREASUREBOX )
		{
			ItemDefine::SItemTreasureBox* pKey= ( ItemDefine::SItemTreasureBox* )pCommon;
			if( !pKey || pKey->uchBoxType != ItemDefine::SItemTreasureBox::BoxType_BoxKey )
				continue;
			//是key，判断等级，以及箱子对应钥匙ID
			if( pKey->uchLevel == pBox->uchLevel && pLuckBox->ustCorrItemID == pItem->itembaseinfo.ustItemID )
			{
				// 就是这个
				kImg.SetData( pItem->itembaseinfo.ustItemID, 1 );
				m_pID_LISTIMG_Key->SetItem( &kImg );

                // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
                CPackItemEnableManager::Instance()->RefreshBagItemEnable( pBag, i, true );

				SetKeyValue( m_ucItemBagType, i, pItem->itembaseinfo.nOnlyInt );
				break;
			}
		}
	}

}

void CUI_ID_FRAME_LotteryGame::SetKeyValue( unsigned char ucBagType, short stIndex, __int64 nGuid )
{
    if(!m_pID_FRAME_LotteryGame)
        return;

	CItemBag2* pBag = 0;
	if( m_ucKeyBagType == BT_NormalItemBag )
	{
		pBag = &thePlayerRole.m_bag;
	}
	else if( m_ucKeyBagType == BT_MaterialBag )
	{
		pBag = &thePlayerRole.m_bagMaterial;
	}
	if( pBag )
	{
		// 恢复enable状态
		int nKeyIndex = pBag->GetItemIndexByGUID( m_nKeyGuid );
		if( nKeyIndex != -1 )
		{
            m_nKeyGuid = 0;

            // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( pBag, nKeyIndex, true );
		}
	}		

	m_ucKeyBagType = ucBagType;
	m_stKeyIndex = stIndex;
	m_nKeyGuid = nGuid;
}

void CUI_ID_FRAME_LotteryGame::SetBoxValue( unsigned char ucBagType, short stIndex, __int64 nGuid )
{
    if(!m_pID_FRAME_LotteryGame)
        return;

	CItemBag2* pBag = 0;
	if( m_ucItemBagType == BT_NormalItemBag )
	{
		pBag = &thePlayerRole.m_bag;
	}
	else if( m_ucItemBagType == BT_MaterialBag )
	{
		pBag = &thePlayerRole.m_bagMaterial;
	}
	if( pBag )
	{
		// 恢复enable状态
		int nBoxIndex = pBag->GetItemIndexByGUID( m_nGuid );
		if( nBoxIndex != -1 )
		{
            m_nGuid = 0;
            // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( pBag, nBoxIndex, true );
		}
	}		

	m_ucItemBagType = ucBagType;
	m_stIndex = stIndex;
	m_nGuid = nGuid;
}
void CUI_ID_FRAME_LotteryGame::RefreshBoxNKeyIndexByGuid()
{
    if(!m_pID_FRAME_LotteryGame)
        return;

	//根据之前记录的guid更新包裹中的enable状态
	CItemBag2* pBag = 0;
	ControlListImage* pImgCtrl = 0;
	if( m_ucItemBagType == BT_NormalItemBag )
	{
		pBag = &thePlayerRole.m_bag;
		pImgCtrl = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag);
	}
	else if( m_ucItemBagType == BT_MaterialBag )
	{
		pBag = &thePlayerRole.m_bagMaterial;
		pImgCtrl = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag);
	}
	if( pBag )
	{
		int nBoxIndex = pBag->GetItemIndexByGUID( m_nGuid );
		if( nBoxIndex != -1 )
		{
			m_stIndex = nBoxIndex;

            // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( pBag, nBoxIndex, true );
		}
		nBoxIndex = pBag->GetItemIndexByGUID( m_nKeyGuid );
		if( nBoxIndex != -1 )
		{
			m_stKeyIndex = nBoxIndex;

            // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( pBag, nBoxIndex, true );
		}
	}
}
void CUI_ID_FRAME_LotteryGame::RenderMiddlePic()
{
	if( RollSystemStatusMan<RST_Lottery>::Instance()->GetCurrentState() )
	{
		unsigned int uiCurrentAnim = RollSystemStatusMan<RST_Lottery>::Instance()->GetCurrentState()->GetCurrentDiceAnimState();
		if( uiCurrentAnim < 0 || uiCurrentAnim >= ECD_Max_TreasureCount )
			return;
		if( m_apRewardControl[uiCurrentAnim] )
		{
			ControlListImage::S_ListImg* pkList = m_apRewardControl[uiCurrentAnim]->GetItem( 0, 0 );
			if( !pkList )
				return;
			unsigned short usId = pkList->m_pkIconInfo->GetItemId();
			if( usId == InvalidLogicNumber )
				return;
			const IconManager::IconInfo* iconInfo = IconManager::Get().GetIconInfo(usId);
			if( !iconInfo )
				return;
			int nImageId = -1;
			RECT rcSrc, rcImage;
			// 源
			rcSrc.left = iconInfo->column * iconInfo->iconSize;
			rcSrc.right = rcSrc.left + iconInfo->iconSize;
			rcSrc.top = iconInfo->row * iconInfo->iconSize;
			rcSrc.bottom = rcSrc.top + iconInfo->iconSize;
			// 目标
			if( m_pID_PICTURE_FinallyAward )
				m_pID_PICTURE_FinallyAward->GetRealRect( &rcImage );
			// render
			theControlPictureManager.BitBlt( &nImageId,
				iconInfo->image.c_str(),
				&rcImage, &rcSrc, 0xffffffff );
		}
	}
}

void CUI_ID_FRAME_LotteryGame::SetButtonStopVisable(bool bVisable)
{
    if(!m_pID_FRAME_LotteryGame)
        return;

    m_pID_BUTTON_Stop->SetVisable(bVisable);
}

void CUI_ID_FRAME_LotteryGame::SetButtonStopEnable(bool bEnable)
{
    if(!m_pID_FRAME_LotteryGame)
        return;

   m_pID_BUTTON_Stop->SetEnable(bEnable);
}

void CUI_ID_FRAME_LotteryGame::OnMsgShowTreasureBox( MsgShowTreasureBox* pMsg )
{
	if(!m_pID_FRAME_LotteryGame || !pMsg)
		return;

	m_uchOperate = pMsg->uchOperate;
	SetBoxValue( pMsg->ucItemBagType, pMsg->stIndex, pMsg->nGuid );
	SetKeyValue( -1, -1, -1 );
	m_uchLevel = pMsg->uchLevel;		
	SetCurrentBg( pMsg->uchLevel - 1 );
	m_nResultIndex = pMsg->nResultIndex;
	UpdateRewards();
	UpdateBoxNKeyUI();
	SetVisable( true );
}

void CUI_ID_FRAME_LotteryGame::OnMsgTreasureBoxResult( MsgTreasureBoxResult* pMsg )
{
	if(!m_pID_FRAME_LotteryGame || !pMsg)
		return;

	SetButtonStopVisable(false);
	SetButtonStopEnable(true);
	ChangeBoxItemId( pMsg->ucItemBagType, pMsg->stIndex, pMsg->nGuid, pMsg->nNewItemID );
	SetTargetResultIndex( pMsg->uchResultIndex );
}

bool CUI_ID_FRAME_LotteryGame::IsPackItemBeUsing( __int64 nGuid )
{
    if( !IsVisable() || nGuid <= 0 )
        return false;

    if( m_nGuid == nGuid || m_nKeyGuid == nGuid )
    {
        return true;
    }
    return false;
}
