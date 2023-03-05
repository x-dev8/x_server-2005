/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\RTX\国王战\KingBattleEnter.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "KingBattleEnter.h"
#include "CampBattleMessage.h"
#include "NetworkInput.h"
#include "XmlStringLanguage.h"
#include "Common.h"
#include "PlayerRole.h"
#include "GameMain.h"
#include "PLayerMgr.h"
#include "Player.h"
#include "ScreenInfoManager.h"
CUI_ID_FRAME_KingBattleEnter s_CUI_ID_FRAME_KingBattleEnter;
MAP_FRAME_RUN( s_CUI_ID_FRAME_KingBattleEnter, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_KingBattleEnter, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_KingBattleEnter, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_KingBattleEnter, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_KingBattleEnter, ID_BUTTON_EnterOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_KingBattleEnter, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_KingBattleEnter, ID_BUTTON_EnterKindomOnButtonClick )
CUI_ID_FRAME_KingBattleEnter::CUI_ID_FRAME_KingBattleEnter()
{
	// Member
	m_pID_FRAME_KingBattleEnter = NULL;
	m_pID_TEXT_Name1 = NULL;
	m_pID_TEXT_Name2 = NULL;
	m_pID_TEXT_Introduce = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Enter = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_EnterKindom = NULL;
}
// Frame
bool CUI_ID_FRAME_KingBattleEnter::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_KingBattleEnter::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_KingBattleEnter::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_KingBattleEnter )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_KingBattleEnter::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_KingBattleEnter )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_KingBattleEnter::ID_BUTTON_EnterKindomOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_KingBattleEnter )
		return false;

	//判断玩家是否在摆摊状态 是的话 不可以传送
	if(theHeroGame.GetPlayerMgr()->GetMe()->IsPrivateShopOpen())
	{
		//提示玩家
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eClient_FlyToMap_Stall));
		return true;
	}

	MsgFlytoKindom flyto;
	flyto.map_id = m_nKingdomMapID;
	flyto.map_x = m_fKingdomX;
	flyto.map_y = m_fKingdomY;
	GettheNetworkInput().SendMsg(&flyto);
	SetVisable(false);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_KingBattleEnter::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\KingBattleEnter.MEUI",true);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\KingBattleEnter.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_KingBattleEnter::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_KingBattleEnter, s_CUI_ID_FRAME_KingBattleEnterOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_KingBattleEnter, s_CUI_ID_FRAME_KingBattleEnterOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_KingBattleEnter, ID_BUTTON_HELP, s_CUI_ID_FRAME_KingBattleEnterID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_KingBattleEnter, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_KingBattleEnterID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_KingBattleEnter, ID_BUTTON_Enter, s_CUI_ID_FRAME_KingBattleEnterID_BUTTON_EnterOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_KingBattleEnter, ID_BUTTON_Cancel, s_CUI_ID_FRAME_KingBattleEnterID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_KingBattleEnter, ID_BUTTON_EnterKindom, s_CUI_ID_FRAME_KingBattleEnterID_BUTTON_EnterKindomOnButtonClick );

	m_pID_FRAME_KingBattleEnter = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_KingBattleEnter );
	m_pID_TEXT_Name1 = (ControlText*)theUiManager.FindControl( ID_FRAME_KingBattleEnter, ID_TEXT_Name1 );
	m_pID_TEXT_Name2 = (ControlText*)theUiManager.FindControl( ID_FRAME_KingBattleEnter, ID_TEXT_Name2 );
	m_pID_TEXT_Introduce = (ControlText*)theUiManager.FindControl( ID_FRAME_KingBattleEnter, ID_TEXT_Introduce );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_KingBattleEnter, ID_BUTTON_HELP );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_KingBattleEnter, ID_BUTTON_CLOSE );
	m_pID_BUTTON_Enter = (ControlButton*)theUiManager.FindControl( ID_FRAME_KingBattleEnter, ID_BUTTON_Enter );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_KingBattleEnter, ID_BUTTON_Cancel );
	m_pID_BUTTON_EnterKindom = (ControlButton*)theUiManager.FindControl( ID_FRAME_KingBattleEnter, ID_BUTTON_EnterKindom );

	assert( m_pID_FRAME_KingBattleEnter );
	assert( m_pID_TEXT_Name1 );
	assert( m_pID_TEXT_Name2 );
	assert( m_pID_TEXT_Introduce );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_Enter );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_EnterKindom );

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_KingBattleEnter::_UnLoadUI()
{
	m_pID_FRAME_KingBattleEnter = NULL;
	m_pID_TEXT_Name1 = NULL;
	m_pID_TEXT_Name2 = NULL;
	m_pID_TEXT_Introduce = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Enter = NULL;
	m_pID_BUTTON_Cancel = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\KingBattleEnter.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_KingBattleEnter::_IsVisable()
{
	if ( !m_pID_FRAME_KingBattleEnter )
		return false;
	return m_pID_FRAME_KingBattleEnter->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_KingBattleEnter::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_KingBattleEnter )
		return;

	m_pID_FRAME_KingBattleEnter->SetVisable( bVisable );
	if (bVisable)
	{
		Refresh();
	}
}

//-------------------------------------------------------------------------------------------------------
void CUI_ID_FRAME_KingBattleEnter::Refresh()
{
	//s_CUI_ID_FRAME_KingBattleEnter.SetVisable(true);

	if ( !m_pID_FRAME_KingBattleEnter )
		return;

	m_pID_BUTTON_Enter->SetVisable(false);
	m_pID_BUTTON_EnterKindom->SetVisable(false);

	m_pID_TEXT_Name1->SetText(thePlayerRole.GetGuildNameById(thePlayerRole.GetRedCampGuildId()));
	m_pID_TEXT_Name2->SetText(thePlayerRole.GetGuildNameById(thePlayerRole.GetBlueCampGuildId()));
	m_pID_TEXT_Introduce->SetText(theXmlString.GetString(eText_KingCamp_EnterBattleInfo));

	m_pID_BUTTON_EnterKindom->SetVisable(true);

	/*if (thePlayerRole.GetGameMapId() != m_nKingdomMapID&&m_nKingdomMapID != 0)
	{
		m_pID_BUTTON_EnterKindom->SetVisable(true);
	}
	else
	{
		m_pID_BUTTON_Enter->SetVisable(true);		
	}*/
}

// Button
bool CUI_ID_FRAME_KingBattleEnter::ID_BUTTON_EnterOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_KingBattleEnter )
		return false;

	/*MsgEnterCampBattleReq msg;
	msg.uchBattleType = CampDefine::BattleTypeKing;
	GettheNetworkInput().SendMsg(&msg);

	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_KingCamp_EnterBattleReq));*/
	_SetVisable(false);
	return true;
}

// Button
bool CUI_ID_FRAME_KingBattleEnter::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_KingBattleEnter )
		return false;

	_SetVisable(false);
	return true;
}

void CUI_ID_FRAME_KingBattleEnter::SetKingdomMapInfo(unsigned long mapid,float x,float y)
{
	m_nKingdomMapID = mapid;
	m_fKingdomX = x;
	m_fKingdomY = y;
}