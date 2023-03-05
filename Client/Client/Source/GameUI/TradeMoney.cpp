/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\TradeMoney.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "TradeMoney.h"
#include "PlayerRole.h"
#include "Common.h"

CUI_ID_FRAME_TradeMoney s_CUI_ID_FRAME_TradeMoney;

MAP_FRAME_RUN( s_CUI_ID_FRAME_TradeMoney, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TradeMoney, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TradeMoney, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TradeMoney, ID_BUTTON_CancleOnButtonClick )

CUI_ID_FRAME_TradeMoney::CUI_ID_FRAME_TradeMoney()
{
    m_bCheckMoney = false;
    m_dwMaxMoney = 0;
    m_pData = NULL;
    ResetMembers();
}

void CUI_ID_FRAME_TradeMoney::ResetMembers()
{
    if( !IsUILoad() )
        return;

	m_pID_FRAME_TradeMoney = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_EDIT_Jin = NULL;
	m_pID_EDIT_Yin = NULL;
	m_pID_EDIT_Tong = NULL;
	m_pID_BUTTON_Cancle = NULL;
    m_pID_TEXT_Caption = NULL;
    m_pID_TEXT_Describe = NULL;
}

bool CUI_ID_FRAME_TradeMoney::EditInputIsVisable()
{
	if ( m_pID_EDIT_Jin == NULL || m_pID_EDIT_Yin == NULL || m_pID_EDIT_Tong == NULL )
	{
		return false;
	}
	return ( m_pID_EDIT_Jin == theUiManager.GetFocus() || m_pID_EDIT_Yin == theUiManager.GetFocus() || m_pID_EDIT_Tong == theUiManager.GetFocus() );
}

bool CUI_ID_FRAME_TradeMoney::OnFrameRun()
{
    if( IsVisable() && IsCheckEnable() )
    {
        // 放在EditChange回调里会死循环
        CheckMoney();
    }

	return true;
}

bool CUI_ID_FRAME_TradeMoney::OnFrameRender()
{
	return true;
}

bool CUI_ID_FRAME_TradeMoney::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TradeMoney )
		return false;

    DWORD dwMoney = GetMoney();
    if( m_pMoneyCallbackFun )
    {
        m_pMoneyCallbackFun( dwMoney, m_pData );
    }
    SetVisable( false );
	return true;
}

bool CUI_ID_FRAME_TradeMoney::ID_BUTTON_CancleOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TradeMoney )
		return false;

    SetVisable( false );
	return true;
}

// 装载UI
bool CUI_ID_FRAME_TradeMoney::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TradeMoney.MEUI", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\TradeMoney.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_TradeMoney::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TradeMoney, s_CUI_ID_FRAME_TradeMoneyOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TradeMoney, s_CUI_ID_FRAME_TradeMoneyOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_TradeMoney, ID_BUTTON_OK, s_CUI_ID_FRAME_TradeMoneyID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TradeMoney, ID_BUTTON_Cancle, s_CUI_ID_FRAME_TradeMoneyID_BUTTON_CancleOnButtonClick );

	m_pID_FRAME_TradeMoney = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TradeMoney );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_TradeMoney, ID_BUTTON_OK );
	m_pID_EDIT_Jin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_TradeMoney, ID_EDIT_Jin );
	m_pID_EDIT_Yin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_TradeMoney, ID_EDIT_Yin );
	m_pID_EDIT_Tong = (ControlEdit*)theUiManager.FindControl( ID_FRAME_TradeMoney, ID_EDIT_Tong );
	m_pID_BUTTON_Cancle = (ControlButton*)theUiManager.FindControl( ID_FRAME_TradeMoney, ID_BUTTON_Cancle );
    m_pID_TEXT_Caption = (ControlText*)theUiManager.FindControl( ID_FRAME_TradeMoney, ID_TEXT_Caption );
    m_pID_TEXT_Describe = (ControlText*)theUiManager.FindControl( ID_FRAME_TradeMoney, ID_TEXT_Describe );

	assert( m_pID_FRAME_TradeMoney );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_EDIT_Jin );
	assert( m_pID_EDIT_Yin );
	assert( m_pID_EDIT_Tong );
	assert( m_pID_BUTTON_Cancle );
    assert( m_pID_TEXT_Caption );
    assert( m_pID_TEXT_Describe );

    //	屏蔽默认的 ESC
    m_pID_FRAME_TradeMoney->enableEscKey( false );
    m_pID_FRAME_TradeMoney->SetOnEscResponseType( ControlFrame::EscResponse_SkipMe );

    m_pID_FRAME_TradeMoney->SetArrayMode( ArrayMode_Top );

    m_pID_EDIT_Jin->SetIsNumber( true );
    m_pID_EDIT_Yin->SetIsNumber( true );
    m_pID_EDIT_Tong->SetIsNumber( true );
    m_pID_EDIT_Jin->SetMaxLength( 5 );
    m_pID_EDIT_Yin->SetMaxLength( 2 );
    m_pID_EDIT_Tong->SetMaxLength( 2 );

    m_pID_EDIT_Jin->SetTextChangedFun( EditDataChange );
    m_pID_EDIT_Yin->SetTextChangedFun( EditDataChange );
    m_pID_EDIT_Tong->SetTextChangedFun( EditDataChange );

	_SetVisable( false );
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_TradeMoney::_UnLoadUI()
{
    SAFE_DELETE( m_pData );
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\TradeMoney.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_TradeMoney::_IsVisable()
{
	if ( !m_pID_FRAME_TradeMoney )
		return false;
	return m_pID_FRAME_TradeMoney->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_TradeMoney::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_TradeMoney )
		return;
	m_pID_FRAME_TradeMoney->SetVisable( bVisable );
}

bool CUI_ID_FRAME_TradeMoney::ShowMoneyInput( funCallbackFun fun, std::string strCaption, std::string strDescribe,
                                             DWORD dwMaxMoney, void* pData, unsigned int nDataLength )
{
    if( IsVisable() )
        return false;

    SetVisable( true );
    if( !IsUILoad() )
        return false;

    m_pMoneyCallbackFun = fun;
    SAFE_DELETE( m_pData );
    m_pData = MeDefaultNew BYTE[ nDataLength ];
    if( pData )
    {
        memcpy( m_pData, pData, nDataLength );
    }

    m_dwMaxMoney = dwMaxMoney;

    m_pID_TEXT_Caption->SetText( strCaption.c_str() );
    m_pID_TEXT_Describe->SetText( strDescribe.c_str() );

    m_pID_EDIT_Jin->SetText( 0 );
    m_pID_EDIT_Yin->SetText( 0 );
    m_pID_EDIT_Tong->SetText( 0 );
    m_pID_EDIT_Jin->SetActivate( true );

    return true;
}

void CUI_ID_FRAME_TradeMoney::EditDataChange( OUT ControlObject* pSender, OUT const char *szData )
{
    if( !s_CUI_ID_FRAME_TradeMoney.IsUILoad() )
        return;

	//去除前导0
	if ( szData && strlen(szData) > 0 )
	{
		int tmpVal = atoi(szData);
		char tmpStr[64] = {0};
		MeSprintf( tmpStr, sizeof(tmpStr) - 1, "%d", tmpVal );
		if ( strlen(szData) > strlen(tmpStr) )
		{
			((ControlEdit*)pSender)->SetText( tmpStr );
		}	
	}

    s_CUI_ID_FRAME_TradeMoney.SetCheckEnable( true );
}

void CUI_ID_FRAME_TradeMoney::SetCheckEnable( bool bEnable )
{
    m_bCheckMoney = bEnable;
}

bool CUI_ID_FRAME_TradeMoney::IsCheckEnable()
{
    return m_bCheckMoney;
}

void CUI_ID_FRAME_TradeMoney::CheckMoney()
{
    if( !IsUILoad() )
        return;

    // 如果超过携带上限则调整至最大钱数
    DWORD dwMoney = GetMoney();
    if( dwMoney > 0 )
    {
        if( !thePlayerRole.PackHasEnoughMoney( dwMoney ) )
        {
            DWORD dwMaxMoney = thePlayerRole.GetData( CPlayerRole::TYPE_MONEY );
            SetMoney( dwMaxMoney );
        }

        // 增加最大金钱的判断
        dwMoney = GetMoney();
        if( m_dwMaxMoney > 0 && dwMoney > m_dwMaxMoney )
        {
            SetMoney( m_dwMaxMoney );
        }
    }
    SetCheckEnable( false );
}

void CUI_ID_FRAME_TradeMoney::SetMoney( DWORD dwMoney )
{
    if( !IsUILoad() )
        return;

    int nGold( 0 ), nSilver( 0 ), nCopper( 0 );
    thePlayerRole.GetGSCFromMoney( dwMoney, nGold, nSilver, nCopper );

    char szMoney[MAX_PATH] = {0};
    MeSprintf_s( szMoney, sizeof( szMoney ) / sizeof( char ) - 1, "%d", nGold );
    m_pID_EDIT_Jin->SetText( szMoney );
    MeSprintf_s( szMoney, sizeof( szMoney ) / sizeof( char ) - 1, "%d", nSilver );
    m_pID_EDIT_Yin->SetText( szMoney );
    MeSprintf_s( szMoney, sizeof( szMoney ) / sizeof( char ) - 1, "%d", nCopper );
    m_pID_EDIT_Tong->SetText( szMoney );
}

DWORD CUI_ID_FRAME_TradeMoney::GetMoney()
{
    if( !IsUILoad() )
        return 0;

    int nGold = 0;
    if( m_pID_EDIT_Jin->GetText() != std::string( "" ) )
        nGold = atoi( m_pID_EDIT_Jin->GetText() );
    int nSilver = 0;
    if( m_pID_EDIT_Yin->GetText() != std::string( "" ) )
        nSilver = atoi( m_pID_EDIT_Yin->GetText() );
    int nCopper = 0;
    if( m_pID_EDIT_Tong->GetText() != std::string( "" ) )
        nCopper = atoi( m_pID_EDIT_Tong->GetText() );

    DWORD dwMoney = thePlayerRole.GetMoneyFromGSC( nGold, nSilver, nCopper );
    return dwMoney;
}
