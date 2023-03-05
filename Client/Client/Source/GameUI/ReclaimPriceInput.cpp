/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\ReclaimPriceInput.cpp
*********************************************************************/

#include <assert.h>
#include "MeUi/UiManager.h"
#include "ReclaimPriceInput.h"
#include "PlayerRole.h"

CUI_ID_FRAME_Reclaim s_CUI_ID_FRAME_Reclaim;

MAP_FRAME_RUN( s_CUI_ID_FRAME_Reclaim, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Reclaim, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Reclaim, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Reclaim, ID_BUTTON_UpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Reclaim, ID_BUTTON_DownOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Reclaim, ID_BUTTON_MaxOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Reclaim, ID_BUTTON_CancleOnButtonClick )

CUI_ID_FRAME_Reclaim::CUI_ID_FRAME_Reclaim()
: m_nItemMaxNum( 99 )
{
	ResetMembers();
    m_pfCallBackFun = NULL;
    m_pData = NULL;
}

CUI_ID_FRAME_Reclaim::~CUI_ID_FRAME_Reclaim()
{
    SAFE_DELETE( m_pData );
    m_pData = NULL;
    m_pfCallBackFun = NULL;
}

void CUI_ID_FRAME_Reclaim::ResetMembers()
{
	m_pID_FRAME_Reclaim = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_TEXT_TotalPrice = NULL;
	m_pID_EDIT_Number = NULL;
	m_pID_BUTTON_Up = NULL;
	m_pID_BUTTON_Down = NULL;
	m_pID_BUTTON_Max = NULL;
	m_pID_BUTTON_Cancle = NULL;
	m_pID_EDIT_Jin = NULL;
	m_pID_EDIT_Yin = NULL;
	m_pID_EDIT_Tong = NULL;
}

bool CUI_ID_FRAME_Reclaim::OnFrameRun()
{
	return true;
}

bool CUI_ID_FRAME_Reclaim::OnFrameRender()
{
	return true;
}

bool CUI_ID_FRAME_Reclaim::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if ( !IsUILoad() )
		return false;

    if( !m_pfCallBackFun )
    {
        SetVisable( false );
        return false;
    }

    m_pfCallBackFun( GetPrice(), GetCount(), m_pData );
    SetVisable( false );
	return true;
}

// Button
bool CUI_ID_FRAME_Reclaim::ID_BUTTON_CancleOnButtonClick( ControlObject* pSender )
{
    if ( !IsUILoad() )
        return false;

    SetVisable( false );
    return true;
}

// Button
bool CUI_ID_FRAME_Reclaim::ID_BUTTON_UpOnButtonClick( ControlObject* pSender )
{
	if ( !IsUILoad() )
		return false;

    int nCount = 0;
    const char* pNumber = m_pID_EDIT_Number->GetText();
    if( strlen( pNumber ) > 0 )
    {
        nCount = atoi( pNumber );
    }
    ++nCount;
    SetCount( nCount );

	return true;
}
// Button
bool CUI_ID_FRAME_Reclaim::ID_BUTTON_DownOnButtonClick( ControlObject* pSender )
{
	if ( !IsUILoad() )
		return false;

    int nCount = 0;
    const char* pNumber = m_pID_EDIT_Number->GetText();
    if( strlen( pNumber ) > 0 )
    {
        nCount = atoi( pNumber );
    }
    --nCount;
    SetCount( nCount );

	return true;
}
// Button
bool CUI_ID_FRAME_Reclaim::ID_BUTTON_MaxOnButtonClick( ControlObject* pSender )
{
	if ( !IsUILoad() )
		return false;

    SetCount( m_nItemMaxNum );
	return true;
}

// 装载UI
bool CUI_ID_FRAME_Reclaim::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Reclaim.MEUI", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Reclaim.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Reclaim::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Reclaim, s_CUI_ID_FRAME_ReclaimOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Reclaim, s_CUI_ID_FRAME_ReclaimOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Reclaim, ID_BUTTON_OK, s_CUI_ID_FRAME_ReclaimID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Reclaim, ID_BUTTON_Up, s_CUI_ID_FRAME_ReclaimID_BUTTON_UpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Reclaim, ID_BUTTON_Down, s_CUI_ID_FRAME_ReclaimID_BUTTON_DownOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Reclaim, ID_BUTTON_Max, s_CUI_ID_FRAME_ReclaimID_BUTTON_MaxOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Reclaim, ID_BUTTON_Cancle, s_CUI_ID_FRAME_ReclaimID_BUTTON_CancleOnButtonClick );

	m_pID_FRAME_Reclaim = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Reclaim );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_Reclaim, ID_BUTTON_OK );
	m_pID_TEXT_TotalPrice = (ControlText*)theUiManager.FindControl( ID_FRAME_Reclaim, ID_TEXT_TotalPrice );
	m_pID_EDIT_Number = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Reclaim, ID_EDIT_Number );
	m_pID_BUTTON_Up = (ControlButton*)theUiManager.FindControl( ID_FRAME_Reclaim, ID_BUTTON_Up );
	m_pID_BUTTON_Down = (ControlButton*)theUiManager.FindControl( ID_FRAME_Reclaim, ID_BUTTON_Down );
	m_pID_BUTTON_Max = (ControlButton*)theUiManager.FindControl( ID_FRAME_Reclaim, ID_BUTTON_Max );
	m_pID_BUTTON_Cancle = (ControlButton*)theUiManager.FindControl( ID_FRAME_Reclaim, ID_BUTTON_Cancle );
	m_pID_EDIT_Jin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Reclaim, ID_EDIT_Jin );
	m_pID_EDIT_Yin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Reclaim, ID_EDIT_Yin );
	m_pID_EDIT_Tong = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Reclaim, ID_EDIT_Tong );

	assert( m_pID_FRAME_Reclaim );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_TEXT_TotalPrice );
	assert( m_pID_EDIT_Number );
	assert( m_pID_BUTTON_Up );
	assert( m_pID_BUTTON_Down );
	assert( m_pID_BUTTON_Max );
	assert( m_pID_BUTTON_Cancle );
	assert( m_pID_EDIT_Jin );
	assert( m_pID_EDIT_Yin );
	assert( m_pID_EDIT_Tong );

    m_pID_FRAME_Reclaim->SetMsgProcFun( InputBox_MsgProc );

    m_pID_EDIT_Jin->SetIsNumber( true );
    m_pID_EDIT_Jin->SetTextChangedFun( EditDataChange );
    m_pID_EDIT_Jin->SetMaxLength( 4 );
    m_pID_EDIT_Yin->SetIsNumber( true );
    m_pID_EDIT_Yin->SetTextChangedFun( EditDataChange );
    m_pID_EDIT_Yin->SetMaxLength( 2 );
    m_pID_EDIT_Tong->SetIsNumber( true );
    m_pID_EDIT_Tong->SetTextChangedFun( EditDataChange );
    m_pID_EDIT_Tong->SetMaxLength( 2 );
    m_pID_EDIT_Number->SetNumberLimit( true, 0, m_nItemMaxNum );
    m_pID_EDIT_Number->SetTextChangedFun( EditDataChange );

    m_pID_EDIT_Number->SetText( 1 );
    m_pID_BUTTON_Down->SetEnable( false );
    m_pID_BUTTON_Up->SetEnable( true );

	SetVisable( false );
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_Reclaim::_UnLoadUI()
{
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\Reclaim.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_Reclaim::_IsVisable()
{
	if ( !m_pID_FRAME_Reclaim )
		return false;
	return m_pID_FRAME_Reclaim->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_Reclaim::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_Reclaim )
		return;
	m_pID_FRAME_Reclaim->SetVisable( bVisable );
}

DWORD CUI_ID_FRAME_Reclaim::GetPrice()
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
    DWORD dwPrice = thePlayerRole.GetMoneyFromGSC( nGold, nSilver, nCopper );

    return dwPrice;
}

void CUI_ID_FRAME_Reclaim::SetPrice( DWORD dwPrice )
{
    if( !IsUILoad() )
        return;

    int nGold( 0 ), nSilver( 0 ), nCopper( 0 );
    thePlayerRole.GetGSCFromMoney( dwPrice, nGold, nSilver, nCopper );

    m_pID_EDIT_Jin->SetText( nGold );
    m_pID_EDIT_Yin->SetText( nSilver );
    m_pID_EDIT_Tong->SetText( nCopper );
}

int CUI_ID_FRAME_Reclaim::GetCount()
{
    if( !IsUILoad() )
        return 0;

    int nCount = 0;
    if( m_pID_EDIT_Number->GetText() != std::string( "" ) )
        nCount = atoi( m_pID_EDIT_Number->GetText() );

    return nCount;
}

void CUI_ID_FRAME_Reclaim::SetCount( int nCount )
{
    if( !IsUILoad() )
        return;

    int nCurCount = 0;
    const char* pNumber = m_pID_EDIT_Number->GetText();
    if( strlen( pNumber ) > 0 )
    {
        nCurCount = atoi( pNumber );
    }
    if( nCurCount != nCount && nCount > 0 && nCount <= m_nItemMaxNum )
    {
        m_pID_EDIT_Number->SetText( nCount );
        if( nCount == 1 )
        {
            m_pID_BUTTON_Down->SetEnable( false );
            m_pID_BUTTON_Up->SetEnable( true );
        }
        else if( nCount == m_nItemMaxNum )
        {
            m_pID_BUTTON_Down->SetEnable( true );
            m_pID_BUTTON_Up->SetEnable( false );
        }
        else
        {
            m_pID_BUTTON_Down->SetEnable( true );
            m_pID_BUTTON_Up->SetEnable( true );
        }
    }
}

bool CUI_ID_FRAME_Reclaim::EditInputIsVisable()
{
    if( !m_pID_EDIT_Jin || !m_pID_EDIT_Yin || !m_pID_EDIT_Tong || !m_pID_EDIT_Number )
        return false;

    return ( m_pID_EDIT_Jin == theUiManager.GetFocus()
        || m_pID_EDIT_Yin == theUiManager.GetFocus()
        || m_pID_EDIT_Tong == theUiManager.GetFocus()
        || m_pID_EDIT_Number == theUiManager.GetFocus() );
}

void CUI_ID_FRAME_Reclaim::SetTotalPriceString( const std::string& strPrice )
{
    if( !IsUILoad() )
        return;

    m_pID_TEXT_TotalPrice->SetText( strPrice.c_str() );
}

void CUI_ID_FRAME_Reclaim::EditDataChange( OUT ControlObject* pSender, OUT const char *szData )
{
    DWORD dwPrice = s_CUI_ID_FRAME_Reclaim.GetPrice();
    int nCount = s_CUI_ID_FRAME_Reclaim.GetCount();
    DWORD dwTotalPrice = dwPrice * nCount;

    std::string strTotalPrice = "";
    thePlayerRole.GetGSCStringFromMoney( dwTotalPrice, strTotalPrice );
    s_CUI_ID_FRAME_Reclaim.SetTotalPriceString( strTotalPrice );
}

void CUI_ID_FRAME_Reclaim::Show( funCallbackFun func, void* pData, unsigned int uiDataLength )
{
    m_pfCallBackFun = func;
    SAFE_DELETE( m_pData );
    m_pData = MeDefaultNew BYTE[ uiDataLength ];
    if( pData )
    {
        memcpy( m_pData, pData, uiDataLength );
    }

    SetVisable( true );
    SetPrice( 0 );
    SetCount( 1 );

    if( !IsUILoad() )
        return;

    theUiManager.SetFocus( m_pID_EDIT_Jin );
    theUiManager.ToTop( m_pID_FRAME_Reclaim );
}

bool CUI_ID_FRAME_Reclaim::InputBox_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
    if( !s_CUI_ID_FRAME_Reclaim.IsVisable() )
        return false;

    switch( msg ) 
    {		
    case WM_KEYUP:
        {
            if( wParam == VK_ESCAPE )
            {
                s_CUI_ID_FRAME_Reclaim.ID_BUTTON_CancleOnButtonClick( NULL );
                return true;
            }
            else if( wParam == VK_RETURN )
            {
                s_CUI_ID_FRAME_Reclaim.ID_BUTTON_OKOnButtonClick( NULL );
                return true;
            }
        }
        break;
    }
    return false;
}
