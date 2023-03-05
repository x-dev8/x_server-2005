/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\TradeRecord.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "TradeRecord.h"
#include "SystemStallage.h"
#include "tstring.h"

CUI_ID_FRAME_TradeRecord s_CUI_ID_FRAME_TradeRecord;

MAP_FRAME_RUN( s_CUI_ID_FRAME_TradeRecord, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TradeRecord, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TradeRecord, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TradeRecord, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TradeRecord, ID_BUTTON_ClearOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TradeRecord, ID_BUTTON_CancelOnButtonClick )

CUI_ID_FRAME_TradeRecord::CUI_ID_FRAME_TradeRecord()
{
    ResetMembers();	
}

void CUI_ID_FRAME_TradeRecord::ResetMembers()
{
    if( !IsUILoad() )
        return;

	m_pID_FRAME_TradeRecord = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_Clear = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_Record = NULL;
}

bool CUI_ID_FRAME_TradeRecord::OnFrameRun()
{
	return true;
}

bool CUI_ID_FRAME_TradeRecord::OnFrameRender()
{
	return true;
}

// Button
bool CUI_ID_FRAME_TradeRecord::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TradeRecord )
		return false;
	return true;
}

bool CUI_ID_FRAME_TradeRecord::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TradeRecord )
		return false;
	return true;
}

bool CUI_ID_FRAME_TradeRecord::ID_BUTTON_ClearOnButtonClick( ControlObject* pSender )
{
	if ( !IsUILoad() )
		return false;

    CSystemStallage::Instance()->ClearTradeRecord();
	return true;
}

bool CUI_ID_FRAME_TradeRecord::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !IsUILoad() )
		return false;

    SetVisable( false );
	return true;
}

// 装载UI
bool CUI_ID_FRAME_TradeRecord::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ShopRegiste.meui", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ShopRegiste.meui]失败")
		return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_TradeRecord::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TradeRecord, s_CUI_ID_FRAME_TradeRecordOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TradeRecord, s_CUI_ID_FRAME_TradeRecordOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_TradeRecord, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_TradeRecordID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TradeRecord, ID_BUTTON_HELP, s_CUI_ID_FRAME_TradeRecordID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TradeRecord, ID_BUTTON_Clear, s_CUI_ID_FRAME_TradeRecordID_BUTTON_ClearOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TradeRecord, ID_BUTTON_Cancel, s_CUI_ID_FRAME_TradeRecordID_BUTTON_CancelOnButtonClick );

	m_pID_FRAME_TradeRecord = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TradeRecord );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_TradeRecord, ID_BUTTON_CLOSE );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_TradeRecord, ID_BUTTON_HELP );
	m_pID_BUTTON_Clear = (ControlButton*)theUiManager.FindControl( ID_FRAME_TradeRecord, ID_BUTTON_Clear );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_TradeRecord, ID_BUTTON_Cancel );
	m_pID_TEXT_Record = (ControlText*)theUiManager.FindControl( ID_FRAME_TradeRecord, ID_TEXT_Record );

	assert( m_pID_FRAME_TradeRecord );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_Clear );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_TEXT_Record );

    m_pID_TEXT_Record->RemoveSyntaxFlag( eKeyItem );

	SetVisable( false );
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_TradeRecord::_UnLoadUI()
{
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\ShopRegiste.meui" );
}

// 是否可视
bool CUI_ID_FRAME_TradeRecord::_IsVisable()
{
	if ( !m_pID_FRAME_TradeRecord )
		return false;
	return m_pID_FRAME_TradeRecord->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_TradeRecord::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_TradeRecord )
		return;
	m_pID_FRAME_TradeRecord->SetVisable( bVisable );

    if( bVisable )
    {
        Refresh();
    }
}

void CUI_ID_FRAME_TradeRecord::Refresh()
{
    if( !IsUILoad() )
        return;

    m_pID_TEXT_Record->Clear();
    std::vector<std::string> strVec = CSystemStallage::Instance()->GetTradeRecord();
    std::vector<std::string>::iterator it = strVec.begin();
    for( ; it != strVec.end(); ++it )
    {
        std::wstring strWide = Common::_tstring::toWideString( it->c_str() );
        m_pID_TEXT_Record->AddNewLine( strWide.c_str() );
    }
}
