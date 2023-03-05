/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\CountryResource.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "CountryResource.h"
#include "TradeMoney.h"
#include "PlayerRole.h"
#include "Country.h"

CUI_ID_FRAME_CountryResource s_CUI_ID_FRAME_CountryResource;

MAP_FRAME_RUN( s_CUI_ID_FRAME_CountryResource, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CountryResource, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CountryResource, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CountryResource, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CountryResource, ID_BUTTON_MoneyInputOnButtonClick )

CUI_ID_FRAME_CountryResource::CUI_ID_FRAME_CountryResource()
{
    m_dwMoney = 0;
	ResetMembers();
}

void CUI_ID_FRAME_CountryResource::ResetMembers()
{
	m_pID_FRAME_CountryResource = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_BUTTON_MoneyInput = NULL;
}

// Frame
bool CUI_ID_FRAME_CountryResource::OnFrameRun()
{
	return true;
}

bool CUI_ID_FRAME_CountryResource::OnFrameRender()
{
	return true;
}

// Button
bool CUI_ID_FRAME_CountryResource::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if ( !IsUILoad() )
		return false;

    if( m_dwMoney == 0 )
    {
        SetVisable( false );
        return false;
    }

    MsgCountryRaiseToPlayerAck msg;
    msg.nMoney = m_dwMoney;
    GettheNetworkInput().SendMsg( &msg );

    SetVisable( false );
	return true;
}
// Button
bool CUI_ID_FRAME_CountryResource::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !IsUILoad() )
		return false;

    SetVisable( false );
	return true;
}
// Button
bool CUI_ID_FRAME_CountryResource::ID_BUTTON_MoneyInputOnButtonClick( ControlObject* pSender )
{
	if ( !IsUILoad() )
		return false;

    if( !IsVisable() )
        return false;

   // unsigned int nMaxMoney = theCountryConfig.GetMaxRaiseMoney( thePlayerRole.GetLevel() );
   /* std::string strMoney;
    thePlayerRole.GetGSCStringFromMoney( nMaxMoney, strMoney );*/
    char szTemp[MAX_PATH] = {0};
    MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_MoneyInput_DonateLimit )/*, strMoney.c_str()*/ );
    s_CUI_ID_FRAME_TradeMoney.ShowMoneyInput( GetCountryDonateResult, theXmlString.GetString( eText_MoneyInput_CountryDonate ), szTemp /*,nMaxMoney*/ );

	return true;
}

// 装载UI
bool CUI_ID_FRAME_CountryResource::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CountryResource.MEUI", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CountryResource.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_CountryResource::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_CountryResource, s_CUI_ID_FRAME_CountryResourceOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_CountryResource, s_CUI_ID_FRAME_CountryResourceOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_CountryResource, ID_BUTTON_OK, s_CUI_ID_FRAME_CountryResourceID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CountryResource, ID_BUTTON_Cancel, s_CUI_ID_FRAME_CountryResourceID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CountryResource, ID_BUTTON_MoneyInput, s_CUI_ID_FRAME_CountryResourceID_BUTTON_MoneyInputOnButtonClick );

	m_pID_FRAME_CountryResource = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_CountryResource );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_CountryResource, ID_BUTTON_OK );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_CountryResource, ID_BUTTON_Cancel );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_CountryResource, ID_TEXT_Money );
	m_pID_BUTTON_MoneyInput = (ControlButton*)theUiManager.FindControl( ID_FRAME_CountryResource, ID_BUTTON_MoneyInput );

	assert( m_pID_FRAME_CountryResource );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_TEXT_Money );
	assert( m_pID_BUTTON_MoneyInput );

    m_pID_FRAME_CountryResource->enableEscKey( false );
    m_pID_FRAME_CountryResource->SetOnEscResponseType( ControlFrame::EscResponse_SkipMe );

	SetVisable( false );
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_CountryResource::_UnLoadUI()
{
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\CountryResource.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_CountryResource::_IsVisable()
{
	if ( !m_pID_FRAME_CountryResource )
		return false;
	return m_pID_FRAME_CountryResource->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_CountryResource::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_CountryResource )
		return;
	m_pID_FRAME_CountryResource->SetVisable( bVisable );
}

void CUI_ID_FRAME_CountryResource::ShowCountryDonate()
{
    if( IsVisable() )
        return;

    SetVisable( true );
    if( !IsUILoad() )
        return;

    SetMoney( 0 );
}

// 国家募捐金钱输入回调
bool CUI_ID_FRAME_CountryResource::GetCountryDonateResult( DWORD dwMoney, void* pData )
{
    s_CUI_ID_FRAME_CountryResource.SetMoney( dwMoney );
    return true;
}

void CUI_ID_FRAME_CountryResource::SetMoney( DWORD dwMoney )
{
    std::string strMoney;
    thePlayerRole.GetGSCStringFromMoney( dwMoney, strMoney );
    
    m_dwMoney = dwMoney;

    if( !IsUILoad() )
        return;

    m_pID_TEXT_Money->SetText( strMoney.c_str() );
}
