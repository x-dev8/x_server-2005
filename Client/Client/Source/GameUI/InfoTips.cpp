/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\InfoTips.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "InfoTips.h"
#include "PlayerRole.h"
#include "meui/ExpressionManager.h"
#include "GameSetting.h"
#include "GameMain.h"
#include "IntroductionManager.h"
#include "PlayerMgr.h"
#include "ChatMessageMgr.h"
#include "RelationMessage.h"
#include "baseProperty.h"
#include "Pet.h"
#include "MapConfig.h"
#include "CountryFunction.h"
#include "CampBattleMessage.h "
#include "TransferToNpc.h"
#include "AddFriend.h"
#include "Country.h"
#include "CountryResource.h"
#include "GuildResource.h"
#include "AutoAttackSet.h"
#include "MainMenu.h"
#include "Team.h"
#include "CountryBaseInfo.h"
#include "GuildBaseInfo.h"
#include "BasePropertyBGFrame.h"
#include "SuAnimalRecvie.h"
#include "ManualLevelUp.h"
#include "NewGuildGeneralBattleInfo.h"
#ifndef TIP_BUTTON_NUM
#define TIP_BUTTON_NUM		8
#endif


bool ProcessCountryQuestGYCallBack(const char bPressYesButton, void *pData)
{
	if (!bPressYesButton)
	{
		return false;
	}
	else
	{
		if(theHeroGame.GetPlayerMgr()->GetMe()->IsPrivateShopOpen())
		{
			//提示玩家
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eClient_FlyToMap_Stall));
			return true;
		}
		/*if (theHeroGame.GetPlayerMgr()->GetMe()->IsYabiaoState())
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( eText_YaBiao_Flytomap ));
			return true;
		}*/
		MsgCountryFlyMapReq msg;
		msg.uchType = CountryDefine::QuestType_King;
		GettheNetworkInput().SendMsg( &msg );
	}
	return true;
}
bool ProcessCountryQuestGTCallBack(const char bPressYesButton, void *pData)
{
	if (!bPressYesButton)
	{
		return false;
	}
	else
	{
		if(theHeroGame.GetPlayerMgr()->GetMe()->IsPrivateShopOpen())
		{
			//提示玩家
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eClient_FlyToMap_Stall));
			return true;
		}
		/*if (theHeroGame.GetPlayerMgr()->GetMe()->IsYabiaoState())
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( eText_YaBiao_Flytomap ));
			return true;
		}*/
		MsgCountryFlyMapReq msg;
		msg.uchType = CountryDefine::QuestType_General;
		GettheNetworkInput().SendMsg( &msg );
	}
	return true;
}
bool ProcessCountryQuestHLCallBack(const char bPressYesButton, void *pData)
{
	if (!bPressYesButton)
	{
		return false;
	}
	else
	{
		if(theHeroGame.GetPlayerMgr()->GetMe()->IsPrivateShopOpen())
		{
			//提示玩家
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eClient_FlyToMap_Stall));
			return true;
		}
		/*if (theHeroGame.GetPlayerMgr()->GetMe()->IsYabiaoState())
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( eText_YaBiao_Flytomap ));
			return true;
		}*/
		MsgCountryFlyMapReq msg;
		msg.uchType = CountryDefine::QuestType_CouncilorRight;
		GettheNetworkInput().SendMsg( &msg );
	}
	return true;
}
bool ProcessCountryQuestBSCallBack(const char bPressYesButton, void *pData)
{
	if (!bPressYesButton)
	{
		return false;
	}
	else
	{
		if(theHeroGame.GetPlayerMgr()->GetMe()->IsPrivateShopOpen())
		{
			//提示玩家
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eClient_FlyToMap_Stall));
			return true;
		}
		/*if (theHeroGame.GetPlayerMgr()->GetMe()->IsYabiaoState())
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( eText_YaBiao_Flytomap ));
			return true;
		}*/
		MsgCountryFlyMapReq msg;
		msg.uchType = CountryDefine::QuestType_CouncilorLeft;
		GettheNetworkInput().SendMsg( &msg );
	}
	return true;
}
bool ProcessFlyToPositionCallBack(const char bPressYesButton, void *pData)
{
	if (!bPressYesButton)
	{	
		thePlayerRole.SetFlyPosition(0,0,0,0);
		return false;
	}
	else
	{
		MsgFlyToPositionAck msg;
		unsigned int MapID=0;
		float X = 0;
		float Y = 0;
		thePlayerRole.GetFlyPosition(MapID,X,Y);
		if(MapID == 0)
		{
			//提示玩家 过期的召集令
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( eText_FlyToPosition_TimeOut ));
			return false;
		}
		else if(theHeroGame.GetPlayerMgr()->GetMe()->IsPrivateShopOpen())
		{
			//提示玩家
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eClient_FlyToMap_Stall));
			return true;
		}
		else if (theHeroGame.GetPlayerMgr()->GetMe()->IsYabiaoState())
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( eText_YaBiao_Flytomap ));
			return true;
		}
		msg.MapID = MapID;
		msg.Pos_X = X;
		msg.Pos_Y = Y;
		GettheNetworkInput().SendMsg( &msg );
		return true;
	}
}
CUI_ID_FRAME_InfoTips s_CUI_ID_FRAME_InfoTips;
MAP_FRAME_RUN( s_CUI_ID_FRAME_InfoTips, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_InfoTips, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_InfoTips, ID_BUTTON_Tips1OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_InfoTips, ID_BUTTON_Tips2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_InfoTips, ID_BUTTON_Tips3OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_InfoTips, ID_BUTTON_Tips4OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_InfoTips, ID_BUTTON_Tips5OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_InfoTips, ID_BUTTON_Tips6OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_InfoTips, ID_BUTTON_Tips7OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_InfoTips, ID_BUTTON_Tips8OnButtonClick )

CUI_ID_FRAME_InfoTips::CUI_ID_FRAME_InfoTips()
{
	// Member
	m_pID_FRAME_InfoTips = NULL;
	m_pID_BUTTON_Tips1 = NULL;
	m_pID_BUTTON_Tips2 = NULL;
	m_pID_BUTTON_Tips3 = NULL;
	m_pID_BUTTON_Tips4 = NULL;
	m_pID_BUTTON_Tips5 = NULL;
	m_pID_BUTTON_Tips6 = NULL;
	m_pID_BUTTON_Tips7 = NULL;
	m_pID_BUTTON_Tips8 = NULL;
}
// Frame
bool CUI_ID_FRAME_InfoTips::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_InfoTips::OnFrameRender()
{
	if( !IsVisable() )
		return true;
	
	for( std::vector<TipButton>::size_type i = 0; i < m_tipButtonsVec.size(); i++ )
	{
		if( !m_tipButtonsVec[i].bVisable )
			break;

        m_tipButtonsVec[i].pButton->GetRealRect( &m_tipButtonsVec[i].rect );
		ExpressionManager::GetInstance().DrawExpression( m_tipButtonsVec[i].picName, m_tipButtonsVec[i].rect );
	}

	return true;
}

void CUI_ID_FRAME_InfoTips::InitializeAtEnterWorld()
{
    SetVisable( true );
    ResetProperties();
    Refresh();
}

// Button
bool CUI_ID_FRAME_InfoTips::ID_BUTTON_Tips1OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_InfoTips )
		return false;

    if( m_tipInformationVec.size() > 0 )
    {
        ShowTip( m_tipInformationVec[0] ); 
        if( m_tipButtonsVec.size() > 0 )
            DeleteTipInfo( 0 );
    }
	return true;
}
// Button
bool CUI_ID_FRAME_InfoTips::ID_BUTTON_Tips2OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_InfoTips )
		return false;

    if( m_tipInformationVec.size() > 1 )
    {
        ShowTip( m_tipInformationVec[1] );
        if( m_tipButtonsVec.size() > 1 )
            DeleteTipInfo( 1 );
    }
	return true;
}
// Button
bool CUI_ID_FRAME_InfoTips::ID_BUTTON_Tips3OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_InfoTips )
		return false;

    if( m_tipInformationVec.size() > 2 )
    {
        ShowTip( m_tipInformationVec[2] );
        if( m_tipButtonsVec.size() > 2 )
            DeleteTipInfo( 2 );
    }
	return true;
}
// Button
bool CUI_ID_FRAME_InfoTips::ID_BUTTON_Tips4OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_InfoTips )
		return false;
	
    if( m_tipInformationVec.size() > 3 )
    {
        ShowTip( m_tipInformationVec[3] );
        if( m_tipButtonsVec.size() > 3 )
            DeleteTipInfo( 3 );
    }
	return true;
}
// Button
bool CUI_ID_FRAME_InfoTips::ID_BUTTON_Tips5OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_InfoTips )
		return false;
	
    if( m_tipInformationVec.size() > 4 )
    {
        ShowTip( m_tipInformationVec[4] );
        if( m_tipButtonsVec.size() > 4 )
            DeleteTipInfo( 4 );
    }
	return true;
}
// Button
bool CUI_ID_FRAME_InfoTips::ID_BUTTON_Tips6OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_InfoTips )
		return false;
	
    if( m_tipInformationVec.size() > 5 )
    {
        ShowTip( m_tipInformationVec[5] );
        if( m_tipButtonsVec.size() > 5 )
            DeleteTipInfo( 5 );
    }
	return true;
}
// Button
bool CUI_ID_FRAME_InfoTips::ID_BUTTON_Tips7OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_InfoTips )
		return false;
	
    if( m_tipInformationVec.size() > 6 )
    {
        ShowTip( m_tipInformationVec[6] );
        if( m_tipButtonsVec.size() > 6 )
            DeleteTipInfo( 6 );
    }
	return true;
}
// Button
bool CUI_ID_FRAME_InfoTips::ID_BUTTON_Tips8OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_InfoTips )
		return false;
	
    if( m_tipInformationVec.size() > 7 )
    {
        ShowTip( m_tipInformationVec[7] );
        if( m_tipButtonsVec.size() > 7 )
            DeleteTipInfo( 7 );
    }
	return true;
}

// 装载UI
bool CUI_ID_FRAME_InfoTips::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\InfoTips.MEUI", true );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\InfoTips.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_InfoTips::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_InfoTips, s_CUI_ID_FRAME_InfoTipsOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_InfoTips, s_CUI_ID_FRAME_InfoTipsOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_InfoTips, ID_BUTTON_Tips1, s_CUI_ID_FRAME_InfoTipsID_BUTTON_Tips1OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_InfoTips, ID_BUTTON_Tips2, s_CUI_ID_FRAME_InfoTipsID_BUTTON_Tips2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_InfoTips, ID_BUTTON_Tips3, s_CUI_ID_FRAME_InfoTipsID_BUTTON_Tips3OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_InfoTips, ID_BUTTON_Tips4, s_CUI_ID_FRAME_InfoTipsID_BUTTON_Tips4OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_InfoTips, ID_BUTTON_Tips5, s_CUI_ID_FRAME_InfoTipsID_BUTTON_Tips5OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_InfoTips, ID_BUTTON_Tips6, s_CUI_ID_FRAME_InfoTipsID_BUTTON_Tips6OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_InfoTips, ID_BUTTON_Tips7, s_CUI_ID_FRAME_InfoTipsID_BUTTON_Tips7OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_InfoTips, ID_BUTTON_Tips8, s_CUI_ID_FRAME_InfoTipsID_BUTTON_Tips8OnButtonClick );

	m_pID_FRAME_InfoTips = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_InfoTips );
	m_pID_BUTTON_Tips1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_InfoTips, ID_BUTTON_Tips1 );
	m_pID_BUTTON_Tips2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_InfoTips, ID_BUTTON_Tips2 );
	m_pID_BUTTON_Tips3 = (ControlButton*)theUiManager.FindControl( ID_FRAME_InfoTips, ID_BUTTON_Tips3 );
	m_pID_BUTTON_Tips4 = (ControlButton*)theUiManager.FindControl( ID_FRAME_InfoTips, ID_BUTTON_Tips4 );
	m_pID_BUTTON_Tips5 = (ControlButton*)theUiManager.FindControl( ID_FRAME_InfoTips, ID_BUTTON_Tips5 );
	m_pID_BUTTON_Tips6 = (ControlButton*)theUiManager.FindControl( ID_FRAME_InfoTips, ID_BUTTON_Tips6 );
	m_pID_BUTTON_Tips7 = (ControlButton*)theUiManager.FindControl( ID_FRAME_InfoTips, ID_BUTTON_Tips7 );
	m_pID_BUTTON_Tips8 = (ControlButton*)theUiManager.FindControl( ID_FRAME_InfoTips, ID_BUTTON_Tips8 );

	assert( m_pID_FRAME_InfoTips );
	assert( m_pID_BUTTON_Tips1 );
	assert( m_pID_BUTTON_Tips2 );
	assert( m_pID_BUTTON_Tips3 );
	assert( m_pID_BUTTON_Tips4 );
	assert( m_pID_BUTTON_Tips5 );
	assert( m_pID_BUTTON_Tips6 );
	assert( m_pID_BUTTON_Tips7 );
	assert( m_pID_BUTTON_Tips8 );

	ResetProperties();
    _SetVisable( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_InfoTips::_UnLoadUI()
{
	m_pID_FRAME_InfoTips = NULL;
	m_pID_BUTTON_Tips1 = NULL;
	m_pID_BUTTON_Tips2 = NULL;
	m_pID_BUTTON_Tips3 = NULL;
	m_pID_BUTTON_Tips4 = NULL;
	m_pID_BUTTON_Tips5 = NULL;
	m_pID_BUTTON_Tips6 = NULL;
	m_pID_BUTTON_Tips7 = NULL;
	m_pID_BUTTON_Tips8 = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\InfoTips.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_InfoTips::_IsVisable()
{
	if ( !m_pID_FRAME_InfoTips )
		return false;
	return m_pID_FRAME_InfoTips->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_InfoTips::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_InfoTips )
		return;

	m_pID_FRAME_InfoTips->SetVisable( bVisable );
}

void CUI_ID_FRAME_InfoTips::ShowTip( const TipInformation& tipInfo )
{
	Refresh();
	CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
	switch( tipInfo.usage )
	{
	case eButton_Usage_Raise:
        {
            ProcessCountryDonate();
        }
		break;
	case eButton_Usage_Convene:
		s_CUI_ID_FRAME_BaseInfo.ShowCountryConvene();
		//s_CUI_ID_FRAME_Country.ShowCountryConvene();
		break;
	case eButton_Usage_Help:
		if( tipInfo.otherListId > -1 )
		{
			UpdateHelpRemend();		// 同步
			CIntroductionManager::Instance()->ShowPopUpTip( tipInfo.otherListId );
		}
		break;
	case eButton_Usage_Friend:
		s_CUI_ID_FRAME_InfoTips.ProcessAddFriendReq((Msg*)tipInfo.pData);
		break;
	case eButton_Usage_Team:
		//if( pPlayerMgr )
		//	pPlayerMgr->OnMsgInquireInvitee( ( Msg* )tipInfo.pData );
		//这里剩下的都是申请入队的信息
		
		s_CUI_ID_FRAME_Team.m_pID_FRAME_Team->SetVisable(true);// SetVisable(true);
		s_CUI_ID_FRAME_Team.SetRequestView();
		for ( int i = 0; i < tipInfo.pDataSet.size(); i ++ )
		{
			s_CUI_ID_FRAME_Team.AddRequest(tipInfo.pDataSet[i]);
		}
		s_CUI_ID_FRAME_Team.RefreshPageInfo();
		
		
		break;
	case eButton_Usage_GuildInvite:
		if( pPlayerMgr )
			pPlayerMgr->OnMsgGuildReqInvite( ( Msg* )tipInfo.pData );
		break;
	case eButton_Usage_GuildTanHe:
		s_CUI_ID_FRAME_InfoTips.ProcessGuildTanHeReq((Msg*)tipInfo.pData);
		break;
	case eButton_Usage_GuildCamp:
		s_CUI_ID_FRAME_InfoTips.ProcessGuildCampReq((Msg*)tipInfo.pData);
		break;
	case eButton_Usage_KingCamp:
		s_CUI_ID_FRAME_InfoTips.ProcessKingCampReq((Msg*)tipInfo.pData);
		break;
	case eButton_Usage_GuildApplying:
		s_CUI_ID_FRAME_InfoTips.ProcessGuildApplyingReq((Msg*)tipInfo.pData);
		break;
	case eButton_Usage_GuildMasterConvene:
		s_CUI_ID_FRAME_InfoTips.ProcessGuildMasterConveneReq((Msg*)tipInfo.pData);
		break;
	case eButton_Usage_GuildRaise:
		s_CUI_ID_FRAME_InfoTips.ProcessGuildRaiseReq();
		break;
	case eButton_Usage_Chat:
		chatMessageManage.ShowChatMessageFrame( ( *( ( std::string* )tipInfo.pData ) ).c_str() );
		break;
	case eButton_Usage_PlayerLevelUp:
		{
			/*s_CUI_ID_FRAME_BaseProperty*//*s_CUI_ID_FRAME_BasePropertyBGFrame.SetVisable( true );*/ //lyh++ 不是人物属性面板，而是人物属性父亲面板打开
			s_CUI_ID_FRAME_ManualLevelUp._SetVisable(true);
			//s_CUI_ID_FRAME_BaseProperty.ResetLevelUpTip();
		}
		break;
	case eButton_Usage_PetLevelUp:
		s_CUI_ID_FRAME_Pet.SetVisable( true );
		break;
	case eButton_Usage_GuildSQ:
		s_CUI_ID_FRAME_GuildBaseInfo.ShowSQUI();
		break;
	case eButton_Usage_QuestFlyGY:
		s_CUI_ID_FRAME_MessageBox.Show(tipInfo.tipStr.c_str(),"", CUI_ID_FRAME_MessageBox::eTypeYesNo, false, ProcessCountryQuestGYCallBack);
		break;
	case eButton_Usage_QuestFlyGT:
		s_CUI_ID_FRAME_MessageBox.Show(tipInfo.tipStr.c_str(),"", CUI_ID_FRAME_MessageBox::eTypeYesNo, false, ProcessCountryQuestGTCallBack);
		break;
	case eButton_Usage_QuestFlyHL:
		s_CUI_ID_FRAME_MessageBox.Show(tipInfo.tipStr.c_str(),"", CUI_ID_FRAME_MessageBox::eTypeYesNo, false, ProcessCountryQuestHLCallBack);
		break;
	case eButton_Usage_QuestFlyBS:
		s_CUI_ID_FRAME_MessageBox.Show(tipInfo.tipStr.c_str(),"", CUI_ID_FRAME_MessageBox::eTypeYesNo, false, ProcessCountryQuestBSCallBack);
		break;
	case eButton_Usage_AddGuildGeneral:
		s_CUI_ID_FRAME_NewGuildGeneralBattleInfo.SetVisable( true );
		break;
	case eButton_Usage_FlyToPosition:
		s_CUI_ID_FRAME_MessageBox.Show(tipInfo.tipStr.c_str(),"", CUI_ID_FRAME_MessageBox::eTypeYesNo, false, ProcessFlyToPositionCallBack);
		break;
	default:
		break;
	}
}

void CUI_ID_FRAME_InfoTips::ResetProperties()
{
	m_tipButtonsVec.clear();
	TipButton tipBtn;
	for( int i = 0; i < TIP_BUTTON_NUM; i++ )
	{
		m_tipButtonsVec.push_back( tipBtn );
	}

	if( m_tipButtonsVec.size() == TIP_BUTTON_NUM )
	{
		m_tipButtonsVec[0].pButton = m_pID_BUTTON_Tips1;
		m_tipButtonsVec[1].pButton = m_pID_BUTTON_Tips2;
		m_tipButtonsVec[2].pButton = m_pID_BUTTON_Tips3;
		m_tipButtonsVec[3].pButton = m_pID_BUTTON_Tips4;
		m_tipButtonsVec[4].pButton = m_pID_BUTTON_Tips5;
		m_tipButtonsVec[5].pButton = m_pID_BUTTON_Tips6;
		m_tipButtonsVec[6].pButton = m_pID_BUTTON_Tips7;
		m_tipButtonsVec[7].pButton = m_pID_BUTTON_Tips8;
	}
	for( int i = 0; i < TIP_BUTTON_NUM; i++ )
		m_tipButtonsVec[i].pButton->GetRealRect( &m_tipButtonsVec[i].rect );

	std::vector<TipInformation>::size_type i = 0;
	for( ; i < m_tipInformationVec.size(); i++ )
		DeleteTipInfo( i );
	m_tipInformationVec.clear();
}

void CUI_ID_FRAME_InfoTips::Refresh()
{
	if( m_tipButtonsVec.size() != TIP_BUTTON_NUM || !IsUILoad() )
		return;

	// 初始设置
    for( int i = 0; i < TIP_BUTTON_NUM; i++ )
    {
        m_tipButtonsVec[i].bVisable = false;
        m_tipButtonsVec[i].pButton->SetVisable( false );
        m_tipButtonsVec[i].usage = eButton_Usage_None;
    }

	// 显示
    bool bFrameVisable = false;
	for( std::vector<TipInformation>::size_type i = 0; i < m_tipInformationVec.size(); i ++ )
	{
		if( i > TIP_BUTTON_NUM - 1 )
			break;

        bFrameVisable = true;
		m_tipButtonsVec[i].bVisable = true;
		m_tipButtonsVec[i].pButton->SetVisable( true );
		m_tipButtonsVec[i].usage = m_tipInformationVec[i].usage;
		SetBtnPic( i );
		if( m_tipInformationVec[i].tipStr.size() > 0 )
		{
			m_tipButtonsVec[i].pButton->SetShowTip( true );
			m_tipButtonsVec[i].pButton->setTip( m_tipInformationVec[i].tipStr.c_str() );
		}
		else
		{
			m_tipButtonsVec[i].pButton->SetShowTip( false );
		}
	}
    if( bFrameVisable )
        _SetVisable( true );
    else
        _SetVisable( false );
}

void CUI_ID_FRAME_InfoTips::SetBtnPic( int i )
{
	if( m_tipButtonsVec.size() <= i )
		return;

	// 对应ID参见 Expression.Config
	switch( m_tipButtonsVec[i].usage )
	{
	case eButton_Usage_Raise:
		m_tipButtonsVec[i].picName = "#1096";
		break;
	case eButton_Usage_Convene:
		m_tipButtonsVec[i].picName = "#1094";
		break;
	case eButton_Usage_Help:
		m_tipButtonsVec[i].picName = "#1090";
		break;
	case eButton_Usage_Friend:
		m_tipButtonsVec[i].picName = "#1093";
		break;
	case eButton_Usage_Team:
		m_tipButtonsVec[i].picName = "#1092";
		break;
	case eButton_Usage_GuildInvite:
		m_tipButtonsVec[i].picName = "#1099";
		break;
	case eButton_Usage_GuildTanHe:
		m_tipButtonsVec[i].picName = "#1099";
		break;
	case eButton_Usage_GuildCamp:
		m_tipButtonsVec[i].picName = "#Score00";
		break;
	case eButton_Usage_KingCamp:
		m_tipButtonsVec[i].picName = "#King00";
		break;
	case eButton_Usage_GuildApplying:
		m_tipButtonsVec[i].picName = "#1099";
		break;
	case eButton_Usage_GuildMasterConvene:
		m_tipButtonsVec[i].picName = "#1099";
		break;
	case eButton_Usage_GuildRaise:
		m_tipButtonsVec[i].picName = "#1099";
		break;
	case eButton_Usage_Chat:
		m_tipButtonsVec[i].picName = "#1089";
		break;
	case eButton_Usage_PlayerLevelUp:
		m_tipButtonsVec[i].picName = "#1097";
		break;
	case eButton_Usage_PetLevelUp:
		m_tipButtonsVec[i].picName = "#1098";
		break;
	case eButton_Usage_GuildSQ:
		m_tipButtonsVec[i].picName = "#3054";
		break;
	case eButton_Usage_QuestFlyGY:
		m_tipButtonsVec[i].picName = "#3055";
		break;
	case eButton_Usage_QuestFlyGT:
		m_tipButtonsVec[i].picName = "#3056";
		break;
	case eButton_Usage_QuestFlyHL:
		m_tipButtonsVec[i].picName = "#3057";
		break;
	case eButton_Usage_QuestFlyBS:
		m_tipButtonsVec[i].picName = "#3058";
		break;
	case eButton_Usage_AddGuildGeneral:
		m_tipButtonsVec[i].picName = "#3059";
		break;
	case eButton_Usage_FlyToPosition:
		m_tipButtonsVec[i].picName = "#3060";
		break;
	default:
		break;
	}
}

bool CUI_ID_FRAME_InfoTips::DeleteTipInfo( int index )
{
	if( m_tipInformationVec.size() <= index )
		return false;

	if( m_tipInformationVec[index].pData || m_tipInformationVec[index].pDataSet.size() > 0 )
	{
		switch( m_tipInformationVec[index].usage )
		{
		case eButton_Usage_Help:
			m_tipInformationVec[index].pData = 0;
			break;
		case eButton_Usage_Friend:
			delete ( MsgInviteRelationReq* )( m_tipInformationVec[index].pData );
			m_tipInformationVec[index].pData = 0;
			break;
		case eButton_Usage_Team:
			/*delete ( MsgInquireInvitee* )( m_tipInformationVec[index].pData );
			m_tipInformationVec[index].pData = 0;*/
			for ( int i = 0; i < m_tipInformationVec[index].pDataSet.size(); i ++ )
			{
				delete ( MsgInquireInvitee* )( m_tipInformationVec[index].pDataSet[i] );
			}
			m_tipInformationVec[index].pDataSet.clear();
			break;
		case eButton_Usage_GuildInvite:
			delete ( MsgInviteGuildReq* )( m_tipInformationVec[index].pData );
			m_tipInformationVec[index].pData = 0;
			break;
		case eButton_Usage_GuildTanHe:
			delete ( MsgGuildDelateAgreeReq* )( m_tipInformationVec[index].pData );
			m_tipInformationVec[index].pData = 0;
			break;
		case eButton_Usage_GuildCamp:
			delete ( MsgFlyToCampBattleReq* )( m_tipInformationVec[index].pData );
			m_tipInformationVec[index].pData = 0;
			break;
		case eButton_Usage_KingCamp:
			delete ( MsgFlyToCampBattleReq* )( m_tipInformationVec[index].pData );
			m_tipInformationVec[index].pData = 0;
			break;
		case eButton_Usage_GuildApplying:
			delete ( MsgRequestJoinGuildReq* )( m_tipInformationVec[index].pData );
			m_tipInformationVec[index].pData = 0;
			break;
		case eButton_Usage_GuildMasterConvene:
			delete ( MsgGuildConveneReq* )( m_tipInformationVec[index].pData );
			m_tipInformationVec[index].pData = 0;
			break;
		case eButton_Usage_GuildRaise:
			delete ( MsgGuildDonateReq* )( m_tipInformationVec[index].pData );
			m_tipInformationVec[index].pData = 0;
			break;
		case eButton_Usage_Chat:
			delete ( std::string* )( m_tipInformationVec[index].pData );
			m_tipInformationVec[index].pData = 0;
			break;
		default:
			assert( false && "Memory Leak in UI InfoTips !" );
			break;
		}
	}

	std::vector<TipInformation>::iterator it = m_tipInformationVec.begin();
	for( int i = 0; i < index; i++ )
	{
		if( it == m_tipInformationVec.end() )
			break;
		it++;
	}
	if( it == m_tipInformationVec.end() )
		return false;

	m_tipInformationVec.erase( it );
	Refresh();
	return true;
}

void CUI_ID_FRAME_InfoTips::DeleteTip( int index )
{
	if( m_tipInformationVec.size() <= 0 )
		return;

	std::vector<TipInformation>::iterator it = m_tipInformationVec.begin();
	for( std::vector<TipInformation>::size_type i = 0; i < m_tipInformationVec.size(); i++ )
	{
		if ( it->usage == index )
			break;
		it++;
	}

	if( it == m_tipInformationVec.end() )
		return;

	if( it->pData || it->pDataSet.size() > 0 )
	{
		switch( it->usage )
		{
		case eButton_Usage_Help:
			it->pData = 0;
			break;
		case eButton_Usage_Friend:
			delete ( MsgInviteRelationReq* )( it->pData );
			it->pData = 0;
			break;
		case eButton_Usage_Team:
			for ( int i = 0; i < it->pDataSet.size(); i ++ )
			{
				delete ( MsgInquireInvitee* )( it->pDataSet[i] );
			}
			it->pDataSet.clear();
			break;
		case eButton_Usage_GuildInvite:
			delete ( MsgInviteGuildReq* )( it->pData );
			it->pData = 0;
			break;
		case eButton_Usage_GuildTanHe:
			delete ( MsgGuildDelateAgreeReq* )( it->pData );
			it->pData = 0;
			break;
		case eButton_Usage_GuildCamp:
			delete ( MsgFlyToCampBattleReq* )( it->pData );
			it->pData = 0;
			break;
		case eButton_Usage_KingCamp:
			delete ( MsgFlyToCampBattleReq* )( it->pData );
			it->pData = 0;
			break;
		case eButton_Usage_GuildApplying:
			delete ( MsgRequestJoinGuildReq* )( it->pData );
			it->pData = 0;
			break;
		case eButton_Usage_GuildMasterConvene:
			delete ( MsgGuildConveneReq* )( it->pData );
			it->pData = 0;
			break;
		case eButton_Usage_GuildRaise:
			delete ( MsgGuildDonateReq* )( it->pData );
			it->pData = 0;
			break;
		case eButton_Usage_Chat:
			delete ( std::string* )( it->pData );
			it->pData = 0;
			break;
		default:
			break;
		}
	}

	m_tipInformationVec.erase( it );
	Refresh();
}
// 以下为接收添加 泡泡 消息
void CUI_ID_FRAME_InfoTips::AddRaiseTip()
{
	// 募捐
	int nLevel = thePlayerRole.GetLevel();
	if( nLevel < theCountryConfig.GetMinRaiseLevel() )
		return;

	if( theCountryConfig.GetMaxRaiseIndex( nLevel ) < 1 )
		return;

	std::vector<TipInformation>::iterator it = m_tipInformationVec.begin();
	for( ; it != m_tipInformationVec.end(); it++ )
	{
		if( it->usage ==  eButton_Usage_Raise )
			return;
	}
	TipInformation tipInfo;
	tipInfo.usage = eButton_Usage_Raise;
	tipInfo.tipStr = theXmlString.GetString( eText_InfoTip_Raise );
	m_tipInformationVec.push_back( tipInfo );
	Refresh();
}

//帮会捐赠
void CUI_ID_FRAME_InfoTips::AddGuildDonateTip()
{
	TipInformation tipInfo;
	tipInfo.usage = eButton_Usage_GuildRaise;
	tipInfo.tipStr = theXmlString.GetString(eText_InfoTip_GuildRaise);
	m_tipInformationVec.push_back(tipInfo);
	Refresh();
}

void CUI_ID_FRAME_InfoTips::AddConveneTip( uint32 officialId )
{
	// 召集
	if( officialId == Position_General )
		return;

	// 等级限制
	if( thePlayerRole.GetLevel() < theCountryConfig.GetMinConveneLevel() )
		return;

	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, theXmlString.GetString( eText_CountryConvene_Distribute ) );

	std::vector<TipInformation>::iterator it = m_tipInformationVec.begin();
	for( ; it != m_tipInformationVec.end(); it++ )
	{
		if( it->usage ==  eButton_Usage_Convene )
			return;
	}
	TipInformation tipInfo;
	tipInfo.usage = eButton_Usage_Convene;
	tipInfo.tipStr = theXmlString.GetString( eText_InfoTip_Convene );
	m_tipInformationVec.push_back( tipInfo );
	Refresh();
}

void CUI_ID_FRAME_InfoTips::AddGuildMasterConvene(Msg *pMsg_)
{
	if( !pMsg_ )
		return;

	std::vector<TipInformation>::iterator it = m_tipInformationVec.begin();

	TipInformation tipInfo;
	tipInfo.usage = eButton_Usage_GuildMasterConvene;
	MsgGuildConveneReq* pMsg = new MsgGuildConveneReq;
	*pMsg = *((MsgGuildConveneReq*)pMsg_);
	tipInfo.pData = (void*)pMsg;
	tipInfo.tipStr = theXmlString.GetString(eText_InfoTip_GuildMasterConvene);
	m_tipInformationVec.push_back(tipInfo);
	Refresh();
}

void CUI_ID_FRAME_InfoTips::UpdateHelpRemend()
{
	// 帮助
	if( false == GameSetting::Instance()->GetLevel( GameSetting::eGSC_IntroductionEnable ) )
		return;
	
	std::list<CIntroductionManager::SIntroductionBase*>& IntroStack = CIntroductionManager::Instance()->GetIntroStack();
	std::list<CIntroductionManager::SIntroductionBase*>::iterator listIt = IntroStack.begin();
	std::vector<TipInformation>::iterator vecIt;
	int nIndex( 0 );

	for( ; listIt != IntroStack.end(); listIt++ )
	{
		if( CIntroductionManager::ePopUpIntro != ( *listIt )->GetIntroductionType() )
			continue;

		vecIt = m_tipInformationVec.begin();
		for( ; vecIt != m_tipInformationVec.end(); vecIt++ )
		{
			if( vecIt->usage != eButton_Usage_Help )
				continue;
			if( ( CIntroductionManager::SIntroductionBase* )vecIt->pData == *listIt )
			{
				vecIt->otherListId = nIndex;
				break;
			}
		}
		if( vecIt == m_tipInformationVec.end() )
		{
			TipInformation tipInfo;
			tipInfo.usage = eButton_Usage_Help;
			tipInfo.pData = ( void* )( *listIt );
			tipInfo.otherListId = nIndex;
			CIntroductionManager::SPopUpIntro* pPopUp = ( CIntroductionManager::SPopUpIntro* )( *listIt );
			tipInfo.tipStr = theXmlString.GetString( pPopUp->nTitleStringId );
			m_tipInformationVec.push_back( tipInfo );
		}
		nIndex++;
	}
	
	Refresh();
}

void CUI_ID_FRAME_InfoTips::AddFriendInviteTip( Msg *pMsg_ )
{
	// 好友
	if(!pMsg_)
		return;
	
	//if there are already friend relation, then do not show tip
	MsgTellAddRelation* pMsg = (MsgTellAddRelation*)pMsg_;

	std::map<int, RelationDataToClient>::iterator iter;
	std::map<int, RelationDataToClient>& mapFriendInfo = thePlayerRole.GetMapFriendInfo();
	int nPlayerId = thePlayerRole.GetdbID(pMsg->szName);
	iter = mapFriendInfo.find(nPlayerId);
	if(iter != mapFriendInfo.end() && (iter->second.HaveRelation(RelationDefine::Friend)))
	{
		return;
	}
	// 判断是否拒绝添加好友
	bool bInFight = false;
	if( theHeroGame.GetPlayerMgr()->GetMe() )
		bInFight = theHeroGame.GetPlayerMgr()->GetMe()->HasFightFlag(eFighting);
	bool bRefuseInFight = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_RefuseAddFriendInFight );
	bool bRefuse = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_RefuseAddFriend );
	if( (bInFight && bRefuseInFight) || (!bInFight && bRefuse) )
	{				
		return;
	}
	
	//添加好友直接弹出messagebox
	ProcessAddFriendReq(pMsg_);
	/*TipInformation tipInfo;
	tipInfo.usage = eButton_Usage_Friend;
	MsgTellAddRelation* pTemp = new MsgTellAddRelation();
	*pTemp = *( ( MsgTellAddRelation* )pMsg_ );
	tipInfo.pData = ( void* )pTemp;
	tipInfo.tipStr = theXmlString.GetString( eText_InfoTip_FriendInvite );
	m_tipInformationVec.push_back( tipInfo );
	Refresh();*/
}

void CUI_ID_FRAME_InfoTips::ProcessCountryDonate()
{
    s_CUI_ID_FRAME_CountryResource.ShowCountryDonate();
}

//-----------------------------------------------------------------------------------------------------------------------------------------
//帮会战req
void ProcessGuildCampReqCallBack(int nMapId)
{
	MsgFlyToCampBattleAck msg;
	msg.nMapID = nMapId;
	GettheNetworkInput().SendMsg(&msg);
}

void CUI_ID_FRAME_InfoTips::ProcessGuildCampReq(Msg *pMsg_)//帮会战
{
	if (!pMsg_)
	{
		return;
	}

	MsgFlyToCampBattleReq* pMsg = (MsgFlyToCampBattleReq*)pMsg_;
	if (pMsg->uchBattleType != CampDefine::BattleTypeGuild || pMsg->uchBattleType != CampDefine::BattleTypeGuildUnion)
	{
		return;
	}
	s_CUI_ID_FRAME_TransferToNpc.Show(ProcessGuildCampReqCallBack, pMsg->nMapID, theXmlString.GetString(eText_GuildCamp_FlyToNpc));
}

//---------------------------------------------------------------------------------------------------------------
//king battle
void ProcessKingCampReqCallBack(int nMapId)
{
	MsgFlyToCampBattleAck msg;
	msg.nMapID = nMapId;
	GettheNetworkInput().SendMsg(&msg);
}

void CUI_ID_FRAME_InfoTips::ProcessKingCampReq(Msg *pMsg_)//帮会战
{
	if (!pMsg_)
	{
		return;
	}

	MsgFlyToCampBattleReq* pMsg = (MsgFlyToCampBattleReq*)pMsg_;
	if (pMsg->uchBattleType != CampDefine::BattleTypeKing)
	{
		return;
	}

	s_CUI_ID_FRAME_TransferToNpc.Show(ProcessKingCampReqCallBack, pMsg->nMapID, theXmlString.GetString(eText_KingCamp_FlyToNpc));
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//帮会捐赠
void CUI_ID_FRAME_InfoTips::ProcessGuildRaiseReq()
{
	s_CUI_ID_FRAME_GuildResource.ShowGuildDonate();	
}

//-----------------------------------------------------------------------------------------------------------------------------------------
//帮主召集令
bool ProcessGuildMasterConveneCallBack(const char bPressYesButton, void *pData)
{
	if (!bPressYesButton)
	{
		return false;
	}
	else
	{
		MsgGuildConveneAck msg;
		GettheNetworkInput().SendMsg( &msg );
	}

	return true;
}

void CUI_ID_FRAME_InfoTips::ProcessGuildMasterConveneReq(Msg *pMsg_)//帮主召集令
{
	guardfunc;
	if (!pMsg_)
	{
		return;
	}

	MsgGuildConveneReq* pMsg = (MsgGuildConveneReq*)pMsg_;

	int id = EctypeId2MapId(pMsg->nMapID);
	MapConfig::MapData* pMap = theMapConfig.GetMapDataById(id);
	if (!pMap)
	{
		return;
	}

	std::string strMapName = pMap->MapName;
	int nCountry = pMap->CountryID;
	std::string strCountry = CountryFunction::GetCountryNameById(nCountry);

	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_GuildMasterConvene), strCountry.c_str(),  strMapName.c_str());
	s_CUI_ID_FRAME_MessageBox.Show(szText, theXmlString.GetString(eText_InfoTip_GuildMasterConvene), CUI_ID_FRAME_MessageBox::eTypeYesNo, false, ProcessGuildMasterConveneCallBack);
}

//-----------------------------------------------------------------------------------------------------------------------------------------
//帮会申请
bool ProcessGuildApplyingCallBack(const char bPressYesButton, void *pData)
{
	guardfunc;
	if(!pData)
	{
		return false;
	}

	if (bPressYesButton == CUI_ID_FRAME_MessageBox::eTypeExternal)
	{
		MsgWantPeek msg;
		msg.stTargetID = *((int*)pData);
		msg.type = MsgWantPeek::EPT_Char;
		GettheNetworkInput().SendMsg(&msg);
	}
	else
	{
		MsgRequestJoinGuildAck msg;
		msg.nPlayerID = *((int*)pData);
		msg.bAgreeJoin = bPressYesButton;
		GettheNetworkInput().SendMsg( &msg );
	}

	return true;
}

void CUI_ID_FRAME_InfoTips::ProcessGuildApplyingReq(Msg *pMsg_)
{
	//公会申请处理
	guardfunc;
	if (!pMsg_)
	{
		return;
	}
	MsgRequestJoinGuildReq* pMsg = (MsgRequestJoinGuildReq*)pMsg_;
	return;
	//1.获取公会申请的一条数据 并且加载到Ui上面去 并且弹出图标提示玩家


	char szContent[256] = {0};
	char szName[256] = {0}; 
	MeSprintf_s( szContent, sizeof(szContent)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_ApplyJoinGuild), pMsg->szName );

	s_CUI_ID_FRAME_MessageBox.Show( szContent, theXmlString.GetString(eText_InfoTip_ApplyGuild), CUI_ID_FRAME_MessageBox::eTypeAcceptReject/*eTypeYesNoSeek*/, false, ProcessGuildApplyingCallBack, &(pMsg->nPlayerID), sizeof(unsigned int));
}

//-----------------------------------------------------------------------------------------------------------------------------------------
//加好友邀请
bool ProcessAddFriendReqCallBack(const char bPressYesButton, void *pData)
{
	guardfunc;
	if (!pData)
	{
		return false;
	}

	char* szName = (char*)pData;
	
	if( bPressYesButton == CUI_ID_FRAME_MessageBox::eTypeYes)
	{
		s_CUI_ID_FRAME_AddFriend.SetFrameType( CUI_ID_FRAME_AddFriend::eFrameType_AddFriendFromRMenu );
		s_CUI_ID_FRAME_AddFriend.SetPrivateName(szName);
		s_CUI_ID_FRAME_AddFriend.SetVisable(true);
		return true;
	}
	else if (bPressYesButton == CUI_ID_FRAME_MessageBox::eTypeExternal)
	{
		MsgAddRelationReq msg;
		strncpy(msg.szName, szName, sizeof(msg.szName));
		msg.stRelation = RelationDefine::BlackList;
		GettheNetworkInput().SendMsg( &msg );
		return true;
	}

	return false;
	unguard;
}

void CUI_ID_FRAME_InfoTips::ProcessAddFriendReq(Msg *pMsg_)
{
	guardfunc;
	if (!pMsg_)
	{
		return;
	}
	MsgTellAddRelation* pMsg = (MsgTellAddRelation*)pMsg_;

	char szContent[256] = {0};
	char szName[256] = {0}; 
	MeSprintf_s( szContent, sizeof(szContent)/sizeof(char) - 1,theXmlString.GetString(eInviteAddFriend), pMsg->szName );

	strncpy(szName, pMsg->szName, sizeof(szName));
	s_CUI_ID_FRAME_MessageBox.Show( szContent, theXmlString.GetString(eInviteAddFriendCaption), CUI_ID_FRAME_MessageBox::eTypeYesNoSeek, false, ProcessAddFriendReqCallBack, szName, sizeof(szName));
}

//--------------------------------------------------------------------------------------------------------------------
//帮会弹劾
bool ProcessGuildTanHeReqCallBack(const char bPressYesButton, void *pData)
{
	guardfunc;
	if(bPressYesButton == CUI_ID_FRAME_MessageBox::eTypeYes)
	{
		MsgGuildDelateAgreeAck msg;
		msg.bAgreeDelate = true;
		GettheNetworkInput().SendMsg(&msg);
		char szText[256] = {0};
		MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_AgreeTanHe));
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, szText );
		return true;
	}

	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_DisagreeTanHe));
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, szText );
	return false;
	unguard;
}

void CUI_ID_FRAME_InfoTips::ProcessGuildTanHeReq(Msg *pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	MsgGuildDelateAgreeReq* pMsg = (MsgGuildDelateAgreeReq*)pMsg_;
	
	if (!thePlayerRole.GetGangMgr())
	{
		return;
	}
	
	GuildMember* pGuildMember = thePlayerRole.GetGangMgr()->FindByDBId(pMsg->nPlayerID);
	if (!pGuildMember)
	{
		return;
	}
	
	char szContent[256] = {0};
	MeSprintf_s( szContent, sizeof(szContent)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_FaQiTanHe), pGuildMember->GetName());
	s_CUI_ID_FRAME_MessageBox.Show( szContent, theXmlString.GetString(eText_InfoTip_GuildTanHe), CUI_ID_FRAME_MessageBox::eTypeYesNo, false, ProcessGuildTanHeReqCallBack);
}

//-----------------------------------------------------------------------------------------------------------------------------------------
void CUI_ID_FRAME_InfoTips::AddTeamInviteTip( Msg *pMsg )
{
	// 组队
	if( !pMsg )
		return;

	if( thePlayerRole.GetTeamInfo().size() > 0 && thePlayerRole.IsTeamHeader() )
	{
		//队长接收组队申请是需要等待的,但是如果处于申请界面就直接显示了
		if ( s_CUI_ID_FRAME_Team.IsVisable() && s_CUI_ID_FRAME_Team.IsRequestView() )
		{
			s_CUI_ID_FRAME_Team.AddRequest(pMsg);
			return;
		}
	}
	else
	{
		//组队邀请，是立即弹出框提示玩家
		CPlayerMgr* playerMgr = theHeroGame.GetPlayerMgr();
		if ( playerMgr )
		{
			playerMgr->OnMsgInquireInvitee( pMsg );
		}
		return;
	}

	std::vector<TipInformation>::iterator it = m_tipInformationVec.begin();
	for( ; it != m_tipInformationVec.end(); it++ )
	{
		if( it->usage != eButton_Usage_Team )
			continue;

		//先不在这里检查重复性，因为没有意义了，统一到后面检查
		//if( ( ( MsgInquireInvitee* )pMsg )->dwReqID == ( ( MsgInquireInvitee* )it->pData )->dwReqID )
		//{
		//	*( MsgInquireInvitee* )( it->pData ) = *( MsgInquireInvitee* )pMsg;
		//	return;
		//}
		MsgInquireInvitee* pInvite = new MsgInquireInvitee();
		*pInvite = *( ( MsgInquireInvitee* )pMsg );
		it->pDataSet.push_back(pInvite);
		return;
	}
	if(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())
	{
		s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().ProcessTeam(pMsg);
		return;
	}

	TipInformation tipInfo;
	tipInfo.usage = eButton_Usage_Team;
	MsgInquireInvitee* pInvite = new MsgInquireInvitee();
	*pInvite = *( ( MsgInquireInvitee* )pMsg );
	//tipInfo.pData = ( void* )pInvite;
	tipInfo.pDataSet.push_back(pInvite);
	tipInfo.tipStr = theXmlString.GetString( eText_InfoTip_TeamInvite );
	m_tipInformationVec.push_back( tipInfo );
	Refresh();
}

//帮会邀请
void CUI_ID_FRAME_InfoTips::AddGuildInviteTip( Msg *pMsg )
{
	if( !pMsg )
		return;

	std::vector<TipInformation>::iterator it = m_tipInformationVec.begin();

	TipInformation tipInfo;
	tipInfo.usage = eButton_Usage_GuildInvite;
	MsgInviteJoinGuildReq* pInvite = new MsgInviteJoinGuildReq;
	*pInvite = *((MsgInviteJoinGuildReq*)pMsg);
	tipInfo.pData = (void*)pInvite;
	tipInfo.tipStr = theXmlString.GetString(eText_InfoTip_GuildInvite);
	m_tipInformationVec.push_back(tipInfo);
	Refresh();
}

//申请加入帮派
void CUI_ID_FRAME_InfoTips::AddGuildApplyingTip(Msg *pMsg_)
{
	if(!pMsg_)
		return;
	
	std::vector<TipInformation>::iterator it = m_tipInformationVec.begin();

	TipInformation tipInfo;
	tipInfo.usage = eButton_Usage_GuildApplying;
	MsgRequestJoinGuildReq* pMsg = new MsgRequestJoinGuildReq;
	*pMsg = *((MsgRequestJoinGuildReq*)pMsg_);
	tipInfo.pData = (void*)pMsg;
	tipInfo.tipStr = theXmlString.GetString(eText_InfoTip_ApplyGuild);
	m_tipInformationVec.push_back(tipInfo);
	Refresh();
}

void CUI_ID_FRAME_InfoTips::DeleteGuildCampTip()
{
	for (std::vector<TipInformation>::iterator iter = m_tipInformationVec.begin(); iter != m_tipInformationVec.end();)
	{
		if (iter->pData)
		{
			switch (iter->usage)
			{
			case eButton_Usage_GuildCamp:
				{
					delete (MsgFlyToCampBattleReq*)(iter->pData);
					iter->pData = 0;
					iter = m_tipInformationVec.erase(iter);
					continue;
				}
				break;
			default:
				break;
			}
		}
		++iter;
	}
	
	Refresh();
}

void CUI_ID_FRAME_InfoTips::DeleteKingCampTip()
{
	for (std::vector<TipInformation>::iterator iter = m_tipInformationVec.begin(); iter != m_tipInformationVec.end();)
	{
		if (iter->pData)
		{
			switch (iter->usage)
			{
			case eButton_Usage_KingCamp:
				{
					delete (MsgFlyToCampBattleReq*)(iter->pData);
					iter->pData = 0;
					iter = m_tipInformationVec.erase(iter);
					continue;
				}
				break;
			default:
				break;
			}
		}
		++iter;
	}

	Refresh();
}

//帮会战
void CUI_ID_FRAME_InfoTips::AddGuildCampTip(Msg *pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	TipInformation tipInfo;

	tipInfo.usage = eButton_Usage_GuildCamp;
	MsgFlyToCampBattleReq* pMsg = new MsgFlyToCampBattleReq;
	*pMsg = *((MsgFlyToCampBattleReq*)pMsg_);

	tipInfo.pData = (void*)pMsg;
	tipInfo.tipStr = theXmlString.GetString(eText_GuildCamp_Tip);
	m_tipInformationVec.push_back(tipInfo);

	Refresh();		
}

//帮会战
void CUI_ID_FRAME_InfoTips::AddKingCampTip(Msg *pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	TipInformation tipInfo;

	tipInfo.usage = eButton_Usage_KingCamp;
	MsgFlyToCampBattleReq* pMsg = new MsgFlyToCampBattleReq;
	*pMsg = *((MsgFlyToCampBattleReq*)pMsg_);

	tipInfo.pData = (void*)pMsg;
	tipInfo.tipStr = theXmlString.GetString(eText_KingCamp_Tip);
	m_tipInformationVec.push_back(tipInfo);

	Refresh();		
}


//帮会弹劾
void CUI_ID_FRAME_InfoTips::AddGuildTanHeTip(Msg *pMsg_)
{
	if (!pMsg_)
	{
		return;
	}
	
	TipInformation tipInfo;

	tipInfo.usage = eButton_Usage_GuildTanHe;
	MsgGuildDelateAgreeReq* pMsg = new MsgGuildDelateAgreeReq;
	*pMsg = *((MsgGuildDelateAgreeReq*)pMsg_);
	
	tipInfo.pData = (void*)pMsg;
	tipInfo.tipStr = theXmlString.GetString(eText_InfoTip_GuildTanHe);
	m_tipInformationVec.push_back(tipInfo);
	
	Refresh();		
}

void CUI_ID_FRAME_InfoTips::AddMiniChatTip( std::string strName )
{
	// 单聊
	if( strName.size() < 1 )
		return;

	std::vector<TipInformation>::iterator it = m_tipInformationVec.begin();
	for( ; it != m_tipInformationVec.end(); it++ )
	{
		if( it->usage != eButton_Usage_Chat )
			continue;

		if( *( ( std::string* )it->pData ) == strName )
			return;
	}
	TipInformation tipInfo;
	tipInfo.usage = eButton_Usage_Chat;
	std::string* pString = new std::string();
	*pString = strName;
	tipInfo.pData = ( void* )pString;
	tipInfo.tipStr = theXmlString.GetString( eText_InfoTip_FriendChat );
	m_tipInformationVec.push_back( tipInfo );
	Refresh();

	s_CUI_ID_FRAME_MainMenu.CheckNeedSparkFriend();
}

void CUI_ID_FRAME_InfoTips::AddPlayerLevelUpTip()
{
	// 人物升级
	std::vector<TipInformation>::iterator it = m_tipInformationVec.begin();
	for( ; it != m_tipInformationVec.end(); it++ )
	{
		if( it->usage == eButton_Usage_PlayerLevelUp )
			return;
	}
	TipInformation tipInfo;
	tipInfo.usage = eButton_Usage_PlayerLevelUp;
	tipInfo.tipStr = theXmlString.GetString( eText_InfoTip_PlayerLevelUp );
	m_tipInformationVec.push_back( tipInfo );
	Refresh();
}

void CUI_ID_FRAME_InfoTips::AddpetLevelUpTip()
{
	// 宠物升级
	std::vector<TipInformation>::iterator it = m_tipInformationVec.begin();
	for( ; it != m_tipInformationVec.end(); it++ )
	{
		if( it->usage == eButton_Usage_PetLevelUp )
			return;
	}
	TipInformation tipInfo;
	tipInfo.usage = eButton_Usage_PetLevelUp;
	tipInfo.tipStr = theXmlString.GetString( eText_InfoTip_PetLevelUp );
	m_tipInformationVec.push_back( tipInfo );
	Refresh();
}
void CUI_ID_FRAME_InfoTips::AddSQInfo()
{
	std::vector<TipInformation>::iterator it = m_tipInformationVec.begin();
	for( ; it != m_tipInformationVec.end(); it++ )
	{
		if( it->usage == eButton_Usage_GuildSQ )
			return;
	}
	TipInformation tipInfo;
	tipInfo.usage = eButton_Usage_GuildSQ;
	tipInfo.tipStr = theXmlString.GetString( eText_GuildSQ );
	m_tipInformationVec.push_back( tipInfo );
	Refresh();
}
void CUI_ID_FRAME_InfoTips::AddGuildGeneralInfo()
{
	std::vector<TipInformation>::iterator it = m_tipInformationVec.begin();
	for( ; it != m_tipInformationVec.end(); it++ )
	{
		if( it->usage == eButton_Usage_AddGuildGeneral )
			return;
	}
	TipInformation tipInfo;
	tipInfo.usage = eButton_Usage_AddGuildGeneral;
	tipInfo.tipStr = theXmlString.GetString( eText_AddGuildGeneralTip );
	m_tipInformationVec.push_back( tipInfo );
	Refresh();
}
void CUI_ID_FRAME_InfoTips::AddFlyToPosition()
{
	std::vector<TipInformation>::iterator it = m_tipInformationVec.begin();
	for( ; it != m_tipInformationVec.end(); it++ )
	{
		if( it->usage == eButton_Usage_FlyToPosition )
			return;
	}
	TipInformation tipInfo;
	tipInfo.usage = eButton_Usage_FlyToPosition;
	if(thePlayerRole.GetLogType() == 1)
		tipInfo.tipStr = theXmlString.GetString( eText_FlyToPositionTip_Guild );
	else if(thePlayerRole.GetLogType() == 2)
		tipInfo.tipStr = theXmlString.GetString( eText_FlyToPositionTip_Country );
	m_tipInformationVec.push_back( tipInfo );
	Refresh();
}
void CUI_ID_FRAME_InfoTips::ADdQuestFlyGY()
{
	std::vector<TipInformation>::iterator it = m_tipInformationVec.begin();
	for( ; it != m_tipInformationVec.end(); it++ )
	{
		if( it->usage == eButton_Usage_QuestFlyGY )
			return;
	}
	TipInformation tipInfo;
	tipInfo.usage = eButton_Usage_QuestFlyGY;
	tipInfo.tipStr = theXmlString.GetString( eText_CountryInfoGY );
	m_tipInformationVec.push_back( tipInfo );
	Refresh();
}
void CUI_ID_FRAME_InfoTips::ADdQuestFlyHL()
{
	std::vector<TipInformation>::iterator it = m_tipInformationVec.begin();
	for( ; it != m_tipInformationVec.end(); it++ )
	{
		if( it->usage == eButton_Usage_QuestFlyHL )
			return;
	}
	TipInformation tipInfo;
	tipInfo.usage = eButton_Usage_QuestFlyHL;
	tipInfo.tipStr = theXmlString.GetString( eText_CountryInfoHL );
	m_tipInformationVec.push_back( tipInfo );
	Refresh();
}
void CUI_ID_FRAME_InfoTips::ADdQuestFlyGT()
{
	std::vector<TipInformation>::iterator it = m_tipInformationVec.begin();
	for( ; it != m_tipInformationVec.end(); it++ )
	{
		if( it->usage == eButton_Usage_QuestFlyGT )
			return;
	}
	TipInformation tipInfo;
	tipInfo.usage = eButton_Usage_QuestFlyGT;
	tipInfo.tipStr = theXmlString.GetString( eText_CountryInfoGT );
	m_tipInformationVec.push_back( tipInfo );
	Refresh();
}
void CUI_ID_FRAME_InfoTips::ADdQuestFlyBS()
{
	std::vector<TipInformation>::iterator it = m_tipInformationVec.begin();
	for( ; it != m_tipInformationVec.end(); it++ )
	{
		if( it->usage == eButton_Usage_QuestFlyBS )
			return;
	}
	TipInformation tipInfo;
	tipInfo.usage = eButton_Usage_QuestFlyBS;
	tipInfo.tipStr = theXmlString.GetString( eText_CountryInfoBS );
	m_tipInformationVec.push_back( tipInfo );
	Refresh();
}
//-----------------------------------------------------------------------------------------------------------------------------------------