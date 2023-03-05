/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\RTX\GuildResource.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GlobalDef.h"
#include "GuildResource.h"
#include "GuildMessage.h"
#include "NetworkInput.h"
#include "Common.h"
#include "core\Name.h"
#include "GuildConfig.h"
#include "PlayerRole.h"
#include "XmlStringLanguage.h"
#include "TradeMoney.h"

CUI_ID_FRAME_GuildResource s_CUI_ID_FRAME_GuildResource;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GuildResource, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GuildResource, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildResource, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildResource, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildResource, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildResource, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildResource, ID_BUTTON_MoneyInputOnButtonClick )
CUI_ID_FRAME_GuildResource::CUI_ID_FRAME_GuildResource()
{
	// Member
	m_dwMoney = 0;
	ResetMembers();
}

void CUI_ID_FRAME_GuildResource::ResetMembers()
{
	m_pID_FRAME_GuildResource = NULL;
	m_pID_PICTURE_Money = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_TipsText = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_BUTTON_MoneyInput = NULL;
	m_pID_TEXT_MoneyText = NULL;
}

// Frame
bool CUI_ID_FRAME_GuildResource::OnFrameRun()
{
	return true;
}

bool CUI_ID_FRAME_GuildResource::OnFrameRender()
{
	return true;
}

// Button
bool CUI_ID_FRAME_GuildResource::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildResource )
		return false;
	return true;
}

// Button
bool CUI_ID_FRAME_GuildResource::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildResource )
		return false;
	return true;
}

// Button
bool CUI_ID_FRAME_GuildResource::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildResource )
		return false;

	if( m_dwMoney == 0 )
	{
		SetVisable( false );
		return false;
	}

	MsgGuildDonateAck msg;
	msg.nMoney = m_dwMoney;
	GettheNetworkInput().SendMsg( &msg );

	SetVisable( false );
	return true;
}

// Button
bool CUI_ID_FRAME_GuildResource::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildResource )
		return false;

	_SetVisable(false);
	return true;
}

// Button
bool CUI_ID_FRAME_GuildResource::ID_BUTTON_MoneyInputOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildResource )
		return false;

	/*unsigned int nMaxMoney = theGuildConfig.GetDonateSetting().GetMaxDonateMoneyByLevel( thePlayerRole.GetLevel() );
	std::string strMoney;
	thePlayerRole.GetGSCStringFromMoney( nMaxMoney, strMoney );*/
	char szTemp[MAX_PATH] = {0};
	MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_MoneyInput_DonateLimit )/*, strMoney.c_str() */);
	s_CUI_ID_FRAME_TradeMoney.ShowMoneyInput( GetGuildDonateResult, theXmlString.GetString( eText_Guild_GuildDenote ), szTemp/*, nMaxMoney*/ );

	return true;
}

// 装载UI
bool CUI_ID_FRAME_GuildResource::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GuildResource.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GuildResource.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_GuildResource::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GuildResource, s_CUI_ID_FRAME_GuildResourceOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GuildResource, s_CUI_ID_FRAME_GuildResourceOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GuildResource, ID_BUTTON_HELP, s_CUI_ID_FRAME_GuildResourceID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildResource, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_GuildResourceID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildResource, ID_BUTTON_OK, s_CUI_ID_FRAME_GuildResourceID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildResource, ID_BUTTON_Cancel, s_CUI_ID_FRAME_GuildResourceID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildResource, ID_BUTTON_MoneyInput, s_CUI_ID_FRAME_GuildResourceID_BUTTON_MoneyInputOnButtonClick );

	m_pID_FRAME_GuildResource = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GuildResource );
	m_pID_PICTURE_Money = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GuildResource, ID_PICTURE_Money );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildResource, ID_BUTTON_HELP );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildResource, ID_BUTTON_CLOSE );
	m_pID_TEXT_TipsText = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildResource, ID_TEXT_TipsText );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildResource, ID_BUTTON_OK );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildResource, ID_BUTTON_Cancel );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildResource, ID_TEXT_Money );
	m_pID_BUTTON_MoneyInput = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildResource, ID_BUTTON_MoneyInput );
	m_pID_TEXT_MoneyText = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildResource, ID_TEXT_MoneyText );

	assert( m_pID_FRAME_GuildResource );
	assert( m_pID_PICTURE_Money );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_TipsText );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_TEXT_Money );
	assert( m_pID_BUTTON_MoneyInput );
	assert( m_pID_TEXT_MoneyText );

	SetVisable(false);
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_GuildResource::_UnLoadUI()
{
	m_pID_FRAME_GuildResource = NULL;
	m_pID_PICTURE_Money = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_TipsText = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_BUTTON_MoneyInput = NULL;
	m_pID_TEXT_MoneyText = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GuildResource.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_GuildResource::_IsVisable()
{
	if ( !m_pID_FRAME_GuildResource )
		return false;
	return m_pID_FRAME_GuildResource->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_GuildResource::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_GuildResource )
		return;
	m_pID_FRAME_GuildResource->SetVisable( bVisable );
}

bool CUI_ID_FRAME_GuildResource::GetGuildDonateResult( DWORD dwMoney, void* pData )
{
	s_CUI_ID_FRAME_GuildResource.SetMoney( dwMoney );
	return true;
}

void CUI_ID_FRAME_GuildResource::ShowGuildDonate()
{
	if( IsVisable() )
		return;

	SetVisable( true );
	if( !IsUILoad() )
		return;

	SetMoney( 0 );
}

void CUI_ID_FRAME_GuildResource::SetMoney( DWORD dwMoney )
{
	std::string strMoney;
	thePlayerRole.GetGSCStringFromMoney( dwMoney, strMoney );

	m_dwMoney = dwMoney;

	if( !IsUILoad() )
		return;

	m_pID_TEXT_Money->SetText( strMoney.c_str() );
}

