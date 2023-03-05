/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildUnionBattleEnter.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GuildUnionBattleEnter.h"
#include "CampBattleMessage.h"
#include "NetworkInput.h"
#include "PlayerRole.h"
#include "XmlStringLanguage.h"
#include "Common.h"
CUI_ID_FRAME_GuildUnionBattleEnter s_CUI_ID_FRAME_GuildUnionBattleEnter;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GuildUnionBattleEnter, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GuildUnionBattleEnter, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildUnionBattleEnter, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildUnionBattleEnter, ID_BUTTON_EnterGuildUnionOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildUnionBattleEnter, ID_BUTTON_EnterOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildUnionBattleEnter, ID_BUTTON_CLOSEOnButtonClick )
CUI_ID_FRAME_GuildUnionBattleEnter::CUI_ID_FRAME_GuildUnionBattleEnter()
{
	// Member
	m_pID_FRAME_GuildUnionBattleEnter = NULL;
	m_pID_TEXT_Name1 = NULL;
	m_pID_TEXT_Name2 = NULL;
	m_pID_TEXT_Introduce = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_EnterGuildUnion = NULL;
	m_pID_BUTTON_Enter = NULL;
	m_pID_BUTTON_CLOSE = NULL;
}
// Frame
bool CUI_ID_FRAME_GuildUnionBattleEnter::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GuildUnionBattleEnter::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_GuildUnionBattleEnter::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildUnionBattleEnter )
		return false;
	_SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_GuildUnionBattleEnter::ID_BUTTON_EnterGuildUnionOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildUnionBattleEnter )
		return false;
	
	MsgEnterCampBattleReq msg;
	msg.uchBattleType = CampDefine::BattleTypeGuildUnion;
	GettheNetworkInput().SendMsg(&msg);

	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Camp_GuildUnionBattleResult));
	_SetVisable(false);

	return true;
}
// Button
bool CUI_ID_FRAME_GuildUnionBattleEnter::ID_BUTTON_EnterOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildUnionBattleEnter )
		return false;

	//传送到主城
	MsgFlytoKindom flyto;
	flyto.map_id = m_nKingdomMapID;
	flyto.map_x = m_fKingdomX;
	flyto.map_y = m_fKingdomY;
	GettheNetworkInput().SendMsg(&flyto);

	return true;
}
// Button
bool CUI_ID_FRAME_GuildUnionBattleEnter::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildUnionBattleEnter )
		return false;
	return true;
}

// 装载UI
bool CUI_ID_FRAME_GuildUnionBattleEnter::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GuildUnionBattleEnter.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GuildUnionBattleEnter.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GuildUnionBattleEnter::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GuildUnionBattleEnter, s_CUI_ID_FRAME_GuildUnionBattleEnterOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GuildUnionBattleEnter, s_CUI_ID_FRAME_GuildUnionBattleEnterOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GuildUnionBattleEnter, ID_BUTTON_Cancel, s_CUI_ID_FRAME_GuildUnionBattleEnterID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildUnionBattleEnter, ID_BUTTON_EnterGuildUnion, s_CUI_ID_FRAME_GuildUnionBattleEnterID_BUTTON_EnterGuildUnionOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildUnionBattleEnter, ID_BUTTON_Enter, s_CUI_ID_FRAME_GuildUnionBattleEnterID_BUTTON_EnterOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildUnionBattleEnter, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_GuildUnionBattleEnterID_BUTTON_CLOSEOnButtonClick );

	m_pID_FRAME_GuildUnionBattleEnter = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GuildUnionBattleEnter );
	m_pID_TEXT_Name1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildUnionBattleEnter, ID_TEXT_Name1 );
	m_pID_TEXT_Name2 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildUnionBattleEnter, ID_TEXT_Name2 );
	m_pID_TEXT_Introduce = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildUnionBattleEnter, ID_TEXT_Introduce );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildUnionBattleEnter, ID_BUTTON_Cancel );
	m_pID_BUTTON_EnterGuildUnion = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildUnionBattleEnter, ID_BUTTON_EnterGuildUnion );
	m_pID_BUTTON_Enter = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildUnionBattleEnter, ID_BUTTON_Enter );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildUnionBattleEnter, ID_BUTTON_CLOSE );
	assert( m_pID_FRAME_GuildUnionBattleEnter );
	assert( m_pID_TEXT_Name1 );
	assert( m_pID_TEXT_Name2 );
	assert( m_pID_TEXT_Introduce );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_EnterGuildUnion );
	assert( m_pID_BUTTON_Enter );
	assert( m_pID_BUTTON_CLOSE );

	SetVisable(false);

	return true;
}
	// 卸载UI
bool CUI_ID_FRAME_GuildUnionBattleEnter::_UnLoadUI()
{
	m_pID_FRAME_GuildUnionBattleEnter = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GuildUnionBattleEnter.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GuildUnionBattleEnter::_IsVisable()
{
	return m_pID_FRAME_GuildUnionBattleEnter->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GuildUnionBattleEnter::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_GuildUnionBattleEnter )
		return;

	m_pID_FRAME_GuildUnionBattleEnter->SetVisable( bVisable );

	if (bVisable)
	{
		Refresh();
	}
}
void CUI_ID_FRAME_GuildUnionBattleEnter::Refresh()
{
	if ( !m_pID_FRAME_GuildUnionBattleEnter )
		return;

	m_pID_BUTTON_Enter->SetVisable(false);
	m_pID_BUTTON_EnterGuildUnion->SetVisable(false);

	m_pID_TEXT_Name1->SetText(thePlayerRole.GetGuildNameById(thePlayerRole.GetRedCampGuildId()));
	m_pID_TEXT_Name2->SetText(thePlayerRole.GetGuildNameById(thePlayerRole.GetBlueCampGuildId()));
	m_pID_TEXT_Introduce->SetText(theXmlString.GetString(eText_GuildUnionCamp_EnterBattleInfo));

	if (thePlayerRole.GetGameMapId() == m_nKingdomMapID && m_nKingdomMapID != 0)
	{
		m_pID_BUTTON_EnterGuildUnion->SetVisable(true);
	}
	else
	{
		m_pID_BUTTON_Enter->SetVisable(true);		
	}
}
void CUI_ID_FRAME_GuildUnionBattleEnter::SetKingdomMapInfo(unsigned long mapid,float x,float y)
{
	m_nKingdomMapID = mapid;
	m_fKingdomX = x;
	m_fKingdomY = y;
}