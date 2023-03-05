/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\国家界面\CountryBroadcast.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "CountryBroadcast.h"
#include "Create.h"
#include "CountryBaseInfo.h"
#define BROADCAST_MAXLEN	50
extern HWND g_hWnd;

CUI_ID_FRAME_CountryBroadcast s_CUI_ID_FRAME_CountryBroadcast;
MAP_FRAME_RUN( s_CUI_ID_FRAME_CountryBroadcast, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CountryBroadcast, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CountryBroadcast, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CountryBroadcast, ID_BUTTON_OKOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_CountryBroadcast, ID_EDIT_BroadcastTextOnEditEnter )
CUI_ID_FRAME_CountryBroadcast::CUI_ID_FRAME_CountryBroadcast()
{
	// Member
	m_pID_FRAME_CountryBroadcast = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_Tips = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_EDIT_BroadcastText = NULL;

}
// Frame
bool CUI_ID_FRAME_CountryBroadcast::OnFrameRun()
{
	if ( !m_pID_FRAME_CountryBroadcast )
	{
		assert( false && "ui error" );
		return false;
	}
	if( !IsVisable() )
		return false;

	return true;
}
bool CUI_ID_FRAME_CountryBroadcast::OnFrameRender()
{
	int length= strlen(m_pID_EDIT_BroadcastText->GetText());
	while(MaxNoticeLength <= length)
	{
		m_pID_EDIT_BroadcastText->DelByte(true);
		length= strlen(m_pID_EDIT_BroadcastText->GetText());
	}
	return true;
}
// Button
bool CUI_ID_FRAME_CountryBroadcast::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CountryBroadcast )
	{
		assert( false && "ui error" );
		return false;
	}
	SetVisable( false );
	return true;
}
// Button
bool CUI_ID_FRAME_CountryBroadcast::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CountryBroadcast )
	{
		assert( false && "ui error" );
		return false;
	}

	//给服务器发消息
	if(MaxNoticeLength <= strlen(m_pID_EDIT_BroadcastText->GetText()))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_CountryGG) );
		return false;
	}
	m_strBroadcast = m_pID_EDIT_BroadcastText->GetText();
	MsgCountryNoticeChangeReq msg;
	MeSprintf_s( msg.szNotice, MaxNoticeLength - 1, "%s", m_strBroadcast.c_str() );
	GettheNetworkInput().SendMsg( &msg );

	SetVisable( false );
	return true;
}
// Edit
void CUI_ID_FRAME_CountryBroadcast::ID_EDIT_BroadcastTextOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_CountryBroadcast )
	{
		assert( false && "ui error" );
		return;
	}
}

// 装载UI
bool CUI_ID_FRAME_CountryBroadcast::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CountryBroadcast.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CountryBroadcast.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_CountryBroadcast::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_CountryBroadcast, s_CUI_ID_FRAME_CountryBroadcastOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_CountryBroadcast, s_CUI_ID_FRAME_CountryBroadcastOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_CountryBroadcast, ID_BUTTON_Cancel, s_CUI_ID_FRAME_CountryBroadcastID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CountryBroadcast, ID_BUTTON_OK, s_CUI_ID_FRAME_CountryBroadcastID_BUTTON_OKOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_CountryBroadcast, ID_EDIT_BroadcastText, s_CUI_ID_FRAME_CountryBroadcastID_EDIT_BroadcastTextOnEditEnter );

	m_pID_FRAME_CountryBroadcast = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_CountryBroadcast );
	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_CountryBroadcast, ID_TEXT_Title );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_CountryBroadcast, ID_BUTTON_Cancel );
	m_pID_TEXT_Tips = (ControlText*)theUiManager.FindControl( ID_FRAME_CountryBroadcast, ID_TEXT_Tips );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_CountryBroadcast, ID_BUTTON_OK );
	m_pID_EDIT_BroadcastText = (ControlEdit*)theUiManager.FindControl( ID_FRAME_CountryBroadcast, ID_EDIT_BroadcastText );

	assert( m_pID_FRAME_CountryBroadcast );
	assert( m_pID_TEXT_Title );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_TEXT_Tips );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_EDIT_BroadcastText );

	//	模态
	//m_pID_FRAME_CountryBroadcast->SetMsgProcFun( InputBox_MsgProc );
	m_pID_FRAME_CountryBroadcast->SetArrayMode( ArrayMode_Top );

	//	输入法相关
	if( !s_CUI_ID_FRAME_CREATE.GetImeInstance() )
		s_CUI_ID_FRAME_CREATE.SetImeInstance( ImmGetContext( g_hWnd ) );
	ImmReleaseContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );

	m_strBroadcast.clear();
	m_pID_EDIT_BroadcastText->SetMaxLength( BROADCAST_MAXLEN );
	m_pID_EDIT_BroadcastText->SetText( "" );

	SetVisable( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_CountryBroadcast::_UnLoadUI()
{
	m_pID_FRAME_CountryBroadcast = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_Tips = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_EDIT_BroadcastText = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\CountryBroadcast.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_CountryBroadcast::_IsVisable()
{
	if ( !m_pID_FRAME_CountryBroadcast )
		return false;
	return m_pID_FRAME_CountryBroadcast->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_CountryBroadcast::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_CountryBroadcast )
		return;
	m_pID_FRAME_CountryBroadcast->SetVisable( bVisable );

	if( bVisable )
	{
		// 设置焦点	开启输入法
		m_pID_EDIT_BroadcastText->SetActivate( true );
		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
	}
	else
	{
		// 关闭输入法
		ImmAssociateContext( g_hWnd, NULL );
	}
}

bool CUI_ID_FRAME_CountryBroadcast::EditInputIsVisable()
{
	if( m_pID_FRAME_CountryBroadcast )
		return ( theUiManager.GetFocus() == m_pID_EDIT_BroadcastText );
	return false;
}

// 以下为接收的服务器消息
void CUI_ID_FRAME_CountryBroadcast::GetBroadcastResult( uint8 result )
{
	switch( result )
	{
	case MsgCountryNoticeChangeAck::ECD_Success:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Broadcast_Success ) );
		s_CUI_ID_FRAME_BaseInfo.TryToUpdate();
		//s_CUI_ID_FRAME_Country.TryToUpdate();
		break;
	case MsgCountryNoticeChangeAck::ECD_NotRight:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Broadcast_NotRight ) );
		break;
	case MsgCountryNoticeChangeAck::ECD_TimeLimit:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Broadcast_TimeLimit ) );
		break;
	case MsgCountryNoticeChangeAck::ECD_NotEnoughMoney:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Broadcast_NotEnoughMoney ) );
		break;
	default:
		break;
	}
}
