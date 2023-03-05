/********************************************************************
Created by UIEditor.exe
FileName: F:\Hero\Program\trunk\Bin\Client\Data\Ui\LuckGame.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "LuckGameUI.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "ItemDetail.h"
#include "LuckRewardConfig.h"
#include "NetworkInput.h"
#include "PlayerRole.h"
#include "XmlStringLanguage.h"
#include "ui/MessageBox.h"
#include "ScreenInfoManager.h"
#include "color_config.h"
#include "ui/UIMgr.h"
#include "Common.h"

#define SHOWMISSIONTEXT(c, t) if( c == t )\
								m_pID_PICTURE_MissionText##c->SetVisable(true);

DWORD CUI_ID_FRAME_LuckGame::ms_dwFirstEndTime = 0;
CUI_ID_FRAME_LuckGame s_CUI_ID_FRAME_LuckGame;
MAP_FRAME_RUN( s_CUI_ID_FRAME_LuckGame, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_LuckGame, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LuckGame, ID_BUTTON_BeginOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LuckGame, ID_BUTTON_StopOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LuckGame, ID_BUTTON_CLOSEOnButtonClick )
CUI_ID_FRAME_LuckGame::CUI_ID_FRAME_LuckGame()
{
	// Member
	ResetMembers();

	m_bNewBegin = true;
	// 这里初始化状态数据, 在loadui里面重置
	RollSystemStatusBase* pkState = MeNew LGState< LGS_DEFAULT >;
	pkState->InitData();
	RollSystemStatusMan<RST_LuckyGame>::Instance()->AddState( pkState );

	pkState = MeNew LGState< LGS_ROLLING_BEGIN >;
	pkState->InitData();
	RollSystemStatusMan<RST_LuckyGame>::Instance()->AddState( pkState );

	pkState = MeNew LGState< LGS_ROLLING_END >;
	pkState->InitData();	
	LGState< LGS_ROLLING_END >* pkEndState = dynamic_cast< LGState< LGS_ROLLING_END >* >( pkState );
	pkEndState->SetPostUpdateFunc( PostUpdateInRollingEnd );
	RollSystemStatusMan<RST_LuckyGame>::Instance()->AddState( pkState );

	pkState = MeNew LGState< LGS_NEXTMISSION >;
	pkState->InitData();
	RollSystemStatusMan<RST_LuckyGame>::Instance()->AddState( pkState );

	pkState = MeNew LGState< LGS_LOST >;
	pkState->InitData();
	RollSystemStatusMan<RST_LuckyGame>::Instance()->AddState( pkState );

	pkState = MeNew LGState< LGS_HALF >;
	pkState->InitData();
	RollSystemStatusMan<RST_LuckyGame>::Instance()->AddState( pkState );

	pkState = MeNew LGState< LGS_DOUBLE >;
	pkState->InitData();
	RollSystemStatusMan<RST_LuckyGame>::Instance()->AddState( pkState );

	pkState = MeNew LGState< LGS_FRONT >;
	pkState->InitData();
	RollSystemStatusMan<RST_LuckyGame>::Instance()->AddState( pkState );

	pkState = MeNew LGState< LGS_STAY >;
	pkState->InitData();
	RollSystemStatusMan<RST_LuckyGame>::Instance()->AddState( pkState );

	pkState = MeNew LGState< LGS_JUMP >;
	pkState->InitData();
	RollSystemStatusMan<RST_LuckyGame>::Instance()->AddState( pkState );
}

void CUI_ID_FRAME_LuckGame::ResetMembers()
{
	m_pID_FRAME_LuckGame = NULL;
	m_pID_PICTURE_Background = NULL;
	m_pID_PICTURE_Light = NULL;
	m_pID_PICTURE_Dice = NULL;
	m_pID_BUTTON_Begin = NULL;
	m_pID_BUTTON_Stop = NULL;
	m_pID_PICTURE_Unknown = NULL;
	m_pID_PICTURE_Fire = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_PICTURE_MissionText1 = NULL;
	m_pID_PICTURE_MissionText2 = NULL;
	m_pID_PICTURE_MissionText3 = NULL;
	m_pID_PICTURE_MissionText4 = NULL;
	m_pID_PICTURE_MissionText5 = NULL;
	m_pID_PICTURE_MissionText6 = NULL;
	m_pID_PICTURE_MissionText7 = NULL;
	m_pID_PICTURE_MissionText8 = NULL;
	m_pID_PICTURE_MissionText9 = NULL;
	m_pID_PICTURE_MissionText10 = NULL;
	m_pID_PICTURE_MissionText11 = NULL;
	m_pID_PICTURE_MissionText12 = NULL;
	m_pID_PICTURE_MissionText13 = NULL;
	m_pID_PICTURE_MissionText14 = NULL;
	m_pID_PICTURE_MissionText15 = NULL;
}
// Frame
bool CUI_ID_FRAME_LuckGame::OnFrameRun()
{
	return true;
}
void CUI_ID_FRAME_LuckGame::UpdatePicRect()
{
	for( unsigned int i = 0 ; i < LGS_COUNT ; ++ i )
	{
		RollSystemStatusBase* pkState = RollSystemStatusMan<RST_LuckyGame>::Instance()->GetState( i );
		if( pkState )
		{			
			RECT rc;
			m_pID_PICTURE_Background->GetRealRect( &rc );			
			pkState->SetPicRect( LGPR_BG, rc );
			m_pID_PICTURE_Light->GetRealRect( &rc );
			pkState->SetPicRect( LGPR_LIGHT, rc );
			m_pID_PICTURE_Dice->GetRealRect( &rc );
			pkState->SetPicRect( LGPR_DICE, rc );	
			m_pID_PICTURE_Fire->GetRealRect( &rc );
			pkState->SetPicRect( LGPR_FIRE, rc );
			m_pID_PICTURE_Unknown->GetRealRect( &rc );
			pkState->SetPicRect( LGPR_MIDDLEDICE, rc );
		}
	}
	
}
bool CUI_ID_FRAME_LuckGame::OnFrameRender()
{
	UpdatePicRect();
	if( RollSystemStatusMan<RST_LuckyGame>::Instance()->GetCurrentState() )
	{
		RollSystemStatusMan<RST_LuckyGame>::Instance()->GetCurrentState()->Update();
		RollSystemStatusMan<RST_LuckyGame>::Instance()->GetCurrentState()->Render();
	}
	if( m_ucCurrentLevel == theLuckRewardConfig.GetMaxLevel() )
	{
		m_pID_BUTTON_Begin->SetEnable( false );
		m_pID_BUTTON_Stop->SetEnable( false );
		EnableGetAward( true );
		m_bNewBegin = false;
	}
	return true;
}

// Button
bool CUI_ID_FRAME_LuckGame::ID_BUTTON_BeginOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_LuckGame )
		return false;
	if(!( ( thePlayerRole.GetMeTeamInfo() == 0 ) || thePlayerRole.IsTeamHeader() ) )
		return true;
	m_pID_BUTTON_Begin->SetVisable( false );
	m_pID_BUTTON_CLOSE->SetEnable( false );
	m_pID_BUTTON_Stop->SetVisable( true );
	MsgLuckRewardReq msg;
	msg.uchType = MsgLuckRewardReq::ECD_Start;
	GettheNetworkInput().SendMsg( &msg );
	return true;
}
// Button
bool CUI_ID_FRAME_LuckGame::ID_BUTTON_StopOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_LuckGame )
		return false;
	if(!( ( thePlayerRole.GetMeTeamInfo() == 0 ) || thePlayerRole.IsTeamHeader() ) )
		return true;
    // 在回复消息的时候再置这个值
	MsgLuckRewardReq msg;
	msg.uchType = MsgLuckRewardReq::ECD_Luck;
	GettheNetworkInput().SendMsg( &msg );
	return true;
}
// Button
bool CUI_ID_FRAME_LuckGame::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_LuckGame )
		return false;
	if(!( ( thePlayerRole.GetMeTeamInfo() == 0 ) || thePlayerRole.IsTeamHeader() ) )
		return false;
	MsgLuckRewardReq msg;
	msg.uchType = MsgLuckRewardReq::ECD_Close;
	GettheNetworkInput().SendMsg( &msg );
	return true;
}

// 装载UI
bool CUI_ID_FRAME_LuckGame::_LoadUI()
{
	s_CUI_ID_FRAME_LuckAward.LoadUI();
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\LuckGame.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\LuckGame.MEUI]失败")
			return false;
	}
	ms_dwFirstEndTime = 0;	
	m_ucCurrentLevel = 0;
	m_bNewBegin = true;
	m_GroupMissionTexts.Clear();
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_LuckGame::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_LuckGame, s_CUI_ID_FRAME_LuckGameOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_LuckGame, s_CUI_ID_FRAME_LuckGameOnFrameRender, true );
	theUiManager.OnButtonClick( ID_FRAME_LuckGame, ID_BUTTON_Begin, s_CUI_ID_FRAME_LuckGameID_BUTTON_BeginOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_LuckGame, ID_BUTTON_Stop, s_CUI_ID_FRAME_LuckGameID_BUTTON_StopOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_LuckGame, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_LuckGameID_BUTTON_CLOSEOnButtonClick );

	m_pID_FRAME_LuckGame = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_LuckGame );
	m_pID_PICTURE_Background = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_Background );
	m_pID_PICTURE_Light = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_Light );
	m_pID_PICTURE_Dice = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_Dice );
	m_pID_BUTTON_Begin = (ControlButton*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_BUTTON_Begin );
	m_pID_BUTTON_Stop = (ControlButton*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_BUTTON_Stop );
	m_pID_PICTURE_Unknown = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_Unknown );
	m_pID_PICTURE_Fire = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_Fire );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_BUTTON_CLOSE );
	m_pID_PICTURE_MissionText1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_MissionText1 );
	m_pID_PICTURE_MissionText2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_MissionText2 );
	m_pID_PICTURE_MissionText3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_MissionText3 );
	m_pID_PICTURE_MissionText4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_MissionText4 );
	m_pID_PICTURE_MissionText5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_MissionText5 );
	m_pID_PICTURE_MissionText6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_MissionText6 );
	m_pID_PICTURE_MissionText7 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_MissionText7 );
	m_pID_PICTURE_MissionText8 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_MissionText8 );
	m_pID_PICTURE_MissionText9 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_MissionText9 );
	m_pID_PICTURE_MissionText10 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_MissionText10 );
	m_pID_PICTURE_MissionText11 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_MissionText11 );
	m_pID_PICTURE_MissionText12 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_MissionText12 );
	m_pID_PICTURE_MissionText13 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_MissionText13 );
	m_pID_PICTURE_MissionText14 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_MissionText14 );
	m_pID_PICTURE_MissionText15 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckGame, ID_PICTURE_MissionText15 );
	assert( m_pID_FRAME_LuckGame );
	assert( m_pID_PICTURE_Background );
	assert( m_pID_PICTURE_Light );
	assert( m_pID_PICTURE_Dice );
	assert( m_pID_BUTTON_Begin );
	assert( m_pID_BUTTON_Stop );
	assert( m_pID_PICTURE_Unknown );
	assert( m_pID_PICTURE_Fire );
	assert( m_pID_BUTTON_CLOSE );
	m_pID_PICTURE_Unknown->SetVisable( false );
	m_pID_PICTURE_Fire->SetVisable( false );
	m_pID_PICTURE_Background->SetVisable( false );
	m_pID_PICTURE_Light->SetVisable( false );
	m_pID_PICTURE_Dice->SetVisable( false );
	m_pID_BUTTON_Stop->SetVisable( false );
	m_pID_FRAME_LuckGame->SetOnVisibleChangedFun( OnVisibleChanged );
	m_ucReward = 0;	
	m_uiRewardListBeginIndex = 0;
	m_aRewardIds.clear();
	ConfigSound();
	SetVisable( false );
	m_pID_FRAME_LuckGame->enableEscKey( false );
	USE_SCRIPT( eUI_OBJECT_LuckyGame, this );
	m_pID_FRAME_LuckGame->SetOnEscResponseType(ControlFrame::EscResponse_SkipMe);

	m_GroupMissionTexts.AddControl( m_pID_PICTURE_MissionText1 );
	m_GroupMissionTexts.AddControl( m_pID_PICTURE_MissionText2 );
	m_GroupMissionTexts.AddControl( m_pID_PICTURE_MissionText3 );
	m_GroupMissionTexts.AddControl( m_pID_PICTURE_MissionText4 );
	m_GroupMissionTexts.AddControl( m_pID_PICTURE_MissionText5 );
	m_GroupMissionTexts.AddControl( m_pID_PICTURE_MissionText6 );
	m_GroupMissionTexts.AddControl( m_pID_PICTURE_MissionText7 );
	m_GroupMissionTexts.AddControl( m_pID_PICTURE_MissionText8 );
	m_GroupMissionTexts.AddControl( m_pID_PICTURE_MissionText9 );
	m_GroupMissionTexts.AddControl( m_pID_PICTURE_MissionText10 );
	m_GroupMissionTexts.AddControl( m_pID_PICTURE_MissionText11 );
	m_GroupMissionTexts.AddControl( m_pID_PICTURE_MissionText12 );
	m_GroupMissionTexts.AddControl( m_pID_PICTURE_MissionText13 );
	m_GroupMissionTexts.AddControl( m_pID_PICTURE_MissionText14 );
	m_GroupMissionTexts.AddControl( m_pID_PICTURE_MissionText15 );
	m_GroupMissionTexts.SetVisible( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_LuckGame::_UnLoadUI()
{
	s_CUI_ID_FRAME_LuckAward.UnLoadUI();
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\LuckGame.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_LuckGame::_IsVisable()
{
	if( !m_pID_FRAME_LuckGame )
		return false;
	return m_pID_FRAME_LuckGame->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_LuckGame::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_LuckGame )
		return;

	m_pID_FRAME_LuckGame->SetVisable( bVisable );
}
void CUI_ID_FRAME_LuckGame::PostUpdateInRollingEnd()
{
	DWORD dwCurrent = HQ_TimeGetTime();
	if( ms_dwFirstEndTime == 0 )
		ms_dwFirstEndTime = dwCurrent;
	if( dwCurrent - ms_dwFirstEndTime >= 1500 )
	{
		s_CUI_ID_FRAME_LuckGame.m_bNewBegin = false;
		// 这个根据服务器发来的信息切换不同状态
		if( s_CUI_ID_FRAME_LuckGame.GetStateTypeByRewardType() == LGS_COUNT )
			return;
		RollSystemStatusMan<RST_LuckyGame>::Instance()->ChangeState( s_CUI_ID_FRAME_LuckGame.GetStateTypeByRewardType() );
		char acHint[255] = {0};		
		switch( s_CUI_ID_FRAME_LuckGame.GetStateTypeByRewardType() )
		{
		case LGS_HALF:
			MeSprintf_s( acHint, sizeof(acHint)/sizeof(char) - 1, "%s", theXmlString.GetString( eLuckGame_Half ) );			
			s_CUI_ID_FRAME_LuckGame.m_pID_BUTTON_CLOSE->SetVisable( true );
			s_CUI_ID_FRAME_LuckGame.m_pID_BUTTON_CLOSE->SetEnable( true );
			break;
		case LGS_DOUBLE:
			MeSprintf_s( acHint, sizeof(acHint)/sizeof(char) - 1, "%s", theXmlString.GetString( eLuckGame_Double ) );			
			s_CUI_ID_FRAME_LuckGame.m_pID_BUTTON_CLOSE->SetVisable( true );
			s_CUI_ID_FRAME_LuckGame.m_pID_BUTTON_CLOSE->SetEnable( true );
			break;			
		case LGS_LOST:
			MeSprintf_s( acHint, sizeof(acHint)/sizeof(char) - 1, "%s", theXmlString.GetString( eLuckGame_Lost ) );			
			s_CUI_ID_FRAME_LuckGame.m_pID_BUTTON_CLOSE->SetVisable( true );
			s_CUI_ID_FRAME_LuckGame.m_pID_BUTTON_CLOSE->SetEnable( true );
			break;
		case LGS_FRONT:
			MeSprintf_s( acHint, sizeof(acHint)/sizeof(char) - 1, "%s", theXmlString.GetString( eLuckGame_Front ) );			
			s_CUI_ID_FRAME_LuckGame.m_pID_BUTTON_CLOSE->SetVisable( true );
			s_CUI_ID_FRAME_LuckGame.m_pID_BUTTON_CLOSE->SetEnable( true );
			break;
		case LGS_STAY:
			MeSprintf_s( acHint, sizeof(acHint)/sizeof(char) - 1, "%s", theXmlString.GetString( eLuckGame_Stay ) );			
			s_CUI_ID_FRAME_LuckGame.m_pID_BUTTON_CLOSE->SetVisable( true );
			s_CUI_ID_FRAME_LuckGame.m_pID_BUTTON_CLOSE->SetEnable( true );
			break;
		case LGS_NEXTMISSION:
			MeSprintf_s( acHint, sizeof(acHint)/sizeof(char) - 1, "%s", theXmlString.GetString( eLuckGame_NextMission ) );			
			s_CUI_ID_FRAME_LuckGame.m_pID_BUTTON_CLOSE->SetVisable( true );
			s_CUI_ID_FRAME_LuckGame.m_pID_BUTTON_CLOSE->SetEnable( true );
			break;
		case LGS_JUMP:
			MeSprintf_s( acHint, sizeof(acHint)/sizeof(char) - 1, "%s", theXmlString.GetString( eLuckGame_Jump ) );			
			s_CUI_ID_FRAME_LuckGame.m_pID_BUTTON_CLOSE->SetVisable( true );
			s_CUI_ID_FRAME_LuckGame.m_pID_BUTTON_CLOSE->SetEnable( true );
			break;
		}
		if( acHint[0] != '\0' )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, acHint );
		
	}
		
}
void CUI_ID_FRAME_LuckGame::ResetButtonEnableState()
{
	bool bEnable = false;
	if( ( thePlayerRole.GetMeTeamInfo() == 0 ) || thePlayerRole.IsTeamHeader() )
		bEnable = true;
}
void CUI_ID_FRAME_LuckGame::ResetButtonState()
{	
	m_pID_BUTTON_Stop->SetVisable( false );
	m_pID_BUTTON_Begin->SetVisable( true );
	m_pID_BUTTON_CLOSE->SetEnable( true );
	m_pID_BUTTON_Stop->SetEnable( true );
	m_pID_BUTTON_Begin->SetEnable( true );
	EnableGetAward( true );
	m_pID_BUTTON_CLOSE->SetEnable( true );
}
void CUI_ID_FRAME_LuckGame::OnVisibleChanged( ControlObject* pSender )
{
	if( s_CUI_ID_FRAME_LuckGame.IsVisable() )
	{
		s_CUI_ID_FRAME_LuckGame.m_bNewBegin = true;
		s_CUI_ID_FRAME_LuckGame.ResetButtonState();
		RollSystemStatusMan<RST_LuckyGame>::Instance()->ChangeState( LGS_DEFAULT );
		s_CUI_ID_FRAME_LuckGame.m_uiRewardListBeginIndex = 0;
		s_CUI_ID_FRAME_LuckGame.m_ucReward = 0;		
		ms_dwFirstEndTime = 0;
	}
}
void CUI_ID_FRAME_LuckGame::ConfigSound()
{
	std::string strBase = SwGlobal::GetWorld()->GetAppDataCharDir();
	// 色子声音
	std::string strDiceSound = strBase;
	strDiceSound +="/data/audio/ui/dice.wav";
	// 火
	std::string strFire = strBase;
	strFire += "/data/audio/ui/fire.wav";
	for( unsigned int i = 0 ; i < LGS_COUNT ; ++ i )
	{
		RollSystemStatusBase* pkState = RollSystemStatusMan<RST_LuckyGame>::Instance()->GetState( i );
		if( pkState )
		{			
			pkState->SetUVSound( LGSD_DICE, strDiceSound.c_str() );
			pkState->SetUVSound( LGSD_FIRE, strFire.c_str() );
		}
	}

	// 过关声音
	std::string strNextMission = strBase;
	strNextMission += "/data/audio/ui/nextmission.wav";
	RollSystemStatusBase* pkState = RollSystemStatusMan<RST_LuckyGame>::Instance()->GetState( LGS_NEXTMISSION );
	if( pkState )
		pkState->SetUVSound( LGSD_BG, strNextMission.c_str() );
	
}
void CUI_ID_FRAME_LuckGame::StartRoll()
{
	RollSystemStatusMan<RST_LuckyGame>::Instance()->ChangeState( LGS_ROLLING_BEGIN );
}
void CUI_ID_FRAME_LuckGame::SetRewardResult( unsigned char ucReward )
{
	s_CUI_ID_FRAME_LuckAward.SetRewardType( ucReward );
	m_ucReward = ucReward;
}
void CUI_ID_FRAME_LuckGame::AddReward( const RewardData& data )
{
	s_CUI_ID_FRAME_LuckAward.AddReward( data );
}
unsigned int CUI_ID_FRAME_LuckGame::GetStateTypeByRewardType()
{
	switch( m_ucReward )
	{
	case ECD_RandType_Leave:
		return LGS_LOST;
		break;
	case ECD_RandType_Half:
		return LGS_HALF;
		break;
	case ECD_RandType_Double:
		return LGS_DOUBLE;
		break;
	case ECD_RandType_Front:
		return LGS_FRONT;
		break;
	case ECD_RandType_Stay:
		return LGS_STAY;
		break;
	case ECD_RandType_Next:
		return LGS_NEXTMISSION;
		break;
	case ECD_RandType_Jump:
		return LGS_JUMP;
		break;
	}
	return LGS_COUNT;
}
void CUI_ID_FRAME_LuckGame::RefreshRewardList()
{
	s_CUI_ID_FRAME_LuckAward.RefreshRewardList();
}
void CUI_ID_FRAME_LuckGame::UpdateResultByResult()
{
	// 执行这个的时候意味着队长已经点击了‘停止’
	// 所以现在要切换状态到LGS_ROLLING_END
	RollSystemStatusMan<RST_LuckyGame>::Instance()->ChangeState( LGS_ROLLING_END );
	// 并且设置最终结果
	unsigned int uiTargetAnimState = 0;
	switch( m_ucReward )
	{
	case ECD_RandType_Leave:
		uiTargetAnimState = 2;
		break;
	case ECD_RandType_Half:		
	case ECD_RandType_Double:		
	case ECD_RandType_Front:		
	case ECD_RandType_Stay:
	case ECD_RandType_Jump:
		uiTargetAnimState = 1;
		break;
	case ECD_RandType_Next:
		uiTargetAnimState = 0;
		break;	
	}
	RollSystemStatusMan<RST_LuckyGame>::Instance()->GetState( LGS_ROLLING_END )->SetTargetDiceAnimState( uiTargetAnimState );
}
void CUI_ID_FRAME_LuckGame::EnableGetAward( bool bEnable )
{
}
void CUI_ID_FRAME_LuckGame::ShowMissionText( int n )
{
	if( !m_pID_FRAME_LuckGame )
		return;

	m_GroupMissionTexts.SetVisible( false );
	SHOWMISSIONTEXT( 1, n );
	SHOWMISSIONTEXT( 2, n );
	SHOWMISSIONTEXT( 3, n );
	SHOWMISSIONTEXT( 4, n );
	SHOWMISSIONTEXT( 5, n );
	SHOWMISSIONTEXT( 6, n );
	SHOWMISSIONTEXT( 7, n );
	SHOWMISSIONTEXT( 8, n );
	SHOWMISSIONTEXT( 9, n );
	SHOWMISSIONTEXT( 10, n );
	SHOWMISSIONTEXT( 11, n );
	SHOWMISSIONTEXT( 12, n );
	SHOWMISSIONTEXT( 13, n );
	SHOWMISSIONTEXT( 14, n );
	SHOWMISSIONTEXT( 15, n );
}
bool CUI_ID_FRAME_LuckGame::GetAwardsFunc( const bool bPressYesButton, void *pData )
{
	if( bPressYesButton )
	{
		s_CUI_ID_FRAME_LuckGame.SendGetMessageToServer();
	}
	return true;
}
void CUI_ID_FRAME_LuckGame::SendGetMessageToServer()
{
	MsgLuckRewardReq msg;
	msg.uchType = MsgLuckRewardReq::ECD_Close;
	GettheNetworkInput().SendMsg( &msg );		
}

void CUI_ID_FRAME_LuckGame::SetButtonBeginVisable(bool bVisval)
{
    if(!m_pID_FRAME_LuckGame)
        return;

    m_pID_BUTTON_Begin->SetVisable(bVisval);
}

void CUI_ID_FRAME_LuckGame::SetButtonStopVisable(bool bVisable)
{
    if(!m_pID_FRAME_LuckGame)
        return;

    m_pID_BUTTON_Stop->SetVisable(bVisable);
}

void CUI_ID_FRAME_LuckGame::SetButtonBeginEnable(bool bEnable)
{
    if(!m_pID_FRAME_LuckGame)
        return;

    m_pID_BUTTON_Begin->SetEnable(bEnable);
}

void CUI_ID_FRAME_LuckGame::SetButtonStopEnable(bool bEnable)
{
    if(!m_pID_FRAME_LuckGame)
        return;

    m_pID_BUTTON_Stop->SetEnable(bEnable);
}
