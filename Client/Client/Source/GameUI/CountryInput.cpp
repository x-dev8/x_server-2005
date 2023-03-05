/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\国家界面\CountryInput.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "CountryInput.h"
#include "Country.h"
#include "Create.h"
#include "XmlStringLanguage.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "CountryFunction.h"
#include "ChatCheck.h"
#include "tstring.h"
#include "CountryBaseInfo.h"
#define PLAYER_NAME_MAXLEN	8
#define COUNTRY_NAME_MAXLEN 2

extern HWND g_hWnd; 

CUI_ID_FRAME_CountryInput s_CUI_ID_FRAME_CountryInput;
MAP_FRAME_RUN( s_CUI_ID_FRAME_CountryInput, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CountryInput, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_CountryInput, ID_EDIT_CountryInputNameOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CountryInput, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CountryInput, ID_BUTTON_CancelOnButtonClick )
CUI_ID_FRAME_CountryInput::CUI_ID_FRAME_CountryInput()
{
	// Member
	m_pID_FRAME_CountryInput = NULL;
	m_pID_TEXT_CountryInputDesc = NULL;
	m_pID_EDIT_CountryInputName = NULL;
	m_pID_TEXT_CountryInputTips = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancel = NULL;

	ResetProperties();
}
// Frame
bool CUI_ID_FRAME_CountryInput::OnFrameRun()
{
	if ( !m_pID_FRAME_CountryInput )
	{
		assert( false && "ui error" );
		return false;
	}
	if( !IsVisable() )
		return false;

	return true;
}
bool CUI_ID_FRAME_CountryInput::OnFrameRender()
{
	return true;
}
// Edit
void CUI_ID_FRAME_CountryInput::ID_EDIT_CountryInputNameOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_CountryInput )
	{
		assert( false && "ui error" );
		return;
	}
}
// Button
bool CUI_ID_FRAME_CountryInput::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CountryInput )
	{
		assert( false && "ui error" );
		return false;
	}

	// 判断用途后，给服务器发消息
	m_strPlayerName = m_pID_EDIT_CountryInputName->GetText();

    // 改国号
    if( m_nShowType == CUI_ID_FRAME_Country::eShowType_Rename )
    {
        // 确保为2个汉字或其它字符，可能写得有点烂
        std::wstring strCountryName = Common::_tstring::toWideString( m_strPlayerName.c_str() );
        strCountryName = strCountryName.substr( 0, COUNTRY_NAME_MAXLEN );
        m_strPlayerName = Common::_tstring::toNarrowString( strCountryName.c_str() );

        // 非法字符检查
        if( CChatCheck::getInstance()->CheckStringInLow( m_strPlayerName.c_str() ) )
        {
            MsgChangeCountryNameReq changeNameMsg;
            MeSprintf_s( changeNameMsg.szName, sizeof( changeNameMsg.szName ), "%s", m_strPlayerName.c_str() );
            GettheNetworkInput().SendMsg( &changeNameMsg );
        }
        else
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_ChangeNameError ) );
        }
        ResetProperties();
        SetVisable( false );
        return true;
    }

	bool bCanAppoint = m_strPlayerName == "" ? false : true;
	//unsigned long playerID = 0;
	//if( bCanAppoint && ( m_nShowType != CUI_ID_FRAME_Country::eShowType_JinYan ) 
	//	&& ( m_nShowType != CUI_ID_FRAME_Country::eShowType_QiuJin ) && ( m_nShowType != CUI_ID_FRAME_Country::eShowType_SheMian ) )
	//{
	//	GuildMember* guildMember = thePlayerRole.GetGangMgr()->FindByName( m_strPlayerName.c_str() );
	//	if( !guildMember )
	//	{
	//		// 未找到玩家
	//		SetVisable( false );
	//		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Appoint_NotFound ) );
	//		return false;
	//	}
	//	else
	//	{
	//		if( guildMember->GetID() < 0 )
	//		{
	//			SetVisable( false );
	//			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Appoint_NotFound ) );
	//			return false;
	//		}
	//		playerID = ( unsigned long )guildMember->GetID();
	//	}
	//}
	MsgCountryOfficialAppointReq appointMsg;
	MsgCountryOfficialRecallReq dismissMsg;
	MsgCountryOperateToPlayerReq operateMsg;

	switch( m_nShowType )
	{
	case CUI_ID_FRAME_Country::eShowType_None:
		break;
		// 任命  罢免
	case CUI_ID_FRAME_Country::eShowType_AppointJiangJun:
		if( bCanAppoint )
		{
			appointMsg.uchPosition = Position_General;
            MeSprintf_s( appointMsg.szName, sizeof( appointMsg.szName ) / sizeof( char ) - 1, "%s", m_strPlayerName.c_str() );
			//appointMsg.nPlayerID = playerID;
			GettheNetworkInput().SendMsg( &appointMsg );
		}
		else
		{
			dismissMsg.uchPosition = Position_General;
			GettheNetworkInput().SendMsg( &dismissMsg );
		}
		break;
	case CUI_ID_FRAME_Country::eShowType_AppointSiMa:
		if( bCanAppoint )
		{
			appointMsg.uchPosition = Position_CouncilorLeft;
            MeSprintf_s( appointMsg.szName, sizeof( appointMsg.szName ) / sizeof( char ) - 1, "%s", m_strPlayerName.c_str() );
			//appointMsg.nPlayerID = playerID;
			GettheNetworkInput().SendMsg( &appointMsg );
		}
		else
		{
			dismissMsg.uchPosition = Position_CouncilorLeft;
			GettheNetworkInput().SendMsg( &dismissMsg );
		}
		break;
	case CUI_ID_FRAME_Country::eShowType_AppointChengXiang:
		if( bCanAppoint )
		{
			appointMsg.uchPosition = Position_CouncilorRight;
            MeSprintf_s( appointMsg.szName, sizeof( appointMsg.szName ) / sizeof( char ) - 1, "%s", m_strPlayerName.c_str() );
			//appointMsg.nPlayerID = playerID;
			GettheNetworkInput().SendMsg( &appointMsg );
		}
		else
		{
			dismissMsg.uchPosition = Position_CouncilorRight;
			GettheNetworkInput().SendMsg( &dismissMsg );
		}
		break;
	case CUI_ID_FRAME_Country::eShowType_AppointZuoJiangJun:
		if( bCanAppoint )
		{
			appointMsg.uchPosition = Position_CaptorLeft;
            MeSprintf_s( appointMsg.szName, sizeof( appointMsg.szName ) / sizeof( char ) - 1, "%s", m_strPlayerName.c_str() );
			//appointMsg.nPlayerID = playerID;
			GettheNetworkInput().SendMsg( &appointMsg );
		}
		else
		{
			dismissMsg.uchPosition = Position_CaptorLeft;
			GettheNetworkInput().SendMsg( &dismissMsg );
		}
		break;
	case CUI_ID_FRAME_Country::eShowType_AppointYouJiangJun:
		if( bCanAppoint )
		{
			appointMsg.uchPosition = Position_CaptorRight;
            MeSprintf_s( appointMsg.szName, sizeof( appointMsg.szName ) / sizeof( char ) - 1, "%s", m_strPlayerName.c_str() );
			//appointMsg.nPlayerID = playerID;
			GettheNetworkInput().SendMsg( &appointMsg );
		}
		else
		{
			dismissMsg.uchPosition = Position_CaptorRight;
			GettheNetworkInput().SendMsg( &dismissMsg );
		}
		break;
		// 禁言		囚禁	赦免
	case CUI_ID_FRAME_Country::eShowType_JinYan:
        {
            operateMsg.uchOperate = MsgCountryOperateToPlayerReq::Operate_BanSpeak;
            MeSprintf_s( operateMsg.szName, MaxNameLength - 1, "%s", m_strPlayerName.c_str() );
            GettheNetworkInput().SendMsg( &operateMsg );
        }
        break;
    case CUI_ID_FRAME_Country::eShowType_QiuJin:
        {
            operateMsg.uchOperate = MsgCountryOperateToPlayerReq::Operate_Chain;
            MeSprintf_s( operateMsg.szName, MaxNameLength - 1, "%s", m_strPlayerName.c_str() );
            GettheNetworkInput().SendMsg( &operateMsg );
        }
        break;
    case CUI_ID_FRAME_Country::eShowType_SheMian:
        {
            operateMsg.uchOperate = MsgCountryOperateToPlayerReq::Operate_Remit;
            MeSprintf_s( operateMsg.szName, MaxNameLength - 1, "%s", m_strPlayerName.c_str() );
            GettheNetworkInput().SendMsg( &operateMsg );
        }
        break;
	default:
		break;
	}


	ResetProperties();
	SetVisable( false );
	return true;
}
// Button
bool CUI_ID_FRAME_CountryInput::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CountryInput )
	{
		assert( false && "ui error" );
		return false;
	}
	ResetProperties();
	SetVisable( false );
	return true;
}

// 装载UI
bool CUI_ID_FRAME_CountryInput::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CountryInput.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CountryInput.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_CountryInput::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_CountryInput, s_CUI_ID_FRAME_CountryInputOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_CountryInput, s_CUI_ID_FRAME_CountryInputOnFrameRender );
	theUiManager.OnEditEnter( ID_FRAME_CountryInput, ID_EDIT_CountryInputName, s_CUI_ID_FRAME_CountryInputID_EDIT_CountryInputNameOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_CountryInput, ID_BUTTON_OK, s_CUI_ID_FRAME_CountryInputID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CountryInput, ID_BUTTON_Cancel, s_CUI_ID_FRAME_CountryInputID_BUTTON_CancelOnButtonClick );

	m_pID_FRAME_CountryInput = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_CountryInput );
	m_pID_TEXT_CountryInputDesc = (ControlText*)theUiManager.FindControl( ID_FRAME_CountryInput, ID_TEXT_CountryInputDesc );
	m_pID_EDIT_CountryInputName = (ControlEdit*)theUiManager.FindControl( ID_FRAME_CountryInput, ID_EDIT_CountryInputName );
	m_pID_TEXT_CountryInputTips = (ControlText*)theUiManager.FindControl( ID_FRAME_CountryInput, ID_TEXT_CountryInputTips );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_CountryInput, ID_BUTTON_OK );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_CountryInput, ID_BUTTON_Cancel );

	assert( m_pID_FRAME_CountryInput );
	assert( m_pID_TEXT_CountryInputDesc );
	assert( m_pID_EDIT_CountryInputName );
	assert( m_pID_TEXT_CountryInputTips );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancel );

	//	屏蔽默认的 ESC
	m_pID_FRAME_CountryInput->enableEscKey( false );
	m_pID_FRAME_CountryInput->SetOnEscResponseType( ControlFrame::EscResponse_SkipMe );

	//	模态		截获消息
	m_pID_FRAME_CountryInput->SetMsgProcFun( InputBox_MsgProc );
	m_pID_FRAME_CountryInput->SetArrayMode( ArrayMode_Top );
	
	m_pID_EDIT_CountryInputName->SetMaxLength( PLAYER_NAME_MAXLEN );

	//	输入法相关
	if( !s_CUI_ID_FRAME_CREATE.GetImeInstance() )
		s_CUI_ID_FRAME_CREATE.SetImeInstance( ImmGetContext( g_hWnd ) );
	ImmReleaseContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
	

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_CountryInput::_UnLoadUI()
{
	m_pID_FRAME_CountryInput = NULL;
	m_pID_TEXT_CountryInputDesc = NULL;
	m_pID_EDIT_CountryInputName = NULL;
	m_pID_TEXT_CountryInputTips = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancel = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\CountryInput.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_CountryInput::_IsVisable()
{
	if ( !m_pID_FRAME_CountryInput )
		return false;
	return m_pID_FRAME_CountryInput->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_CountryInput::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_CountryInput )
		return;
	m_pID_FRAME_CountryInput->SetVisable( bVisable );
	if( bVisable )
	{
		// 设置焦点	开启输入法
		m_pID_EDIT_CountryInputName->SetActivate( true );
		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
	}
	else
	{
		// 关闭输入法
		ImmAssociateContext( g_hWnd, NULL );
	}
}

bool CUI_ID_FRAME_CountryInput::EditInputIsVisable()
{
	if( m_pID_FRAME_CountryInput )
		return ( theUiManager.GetFocus() == m_pID_EDIT_CountryInputName );
	return false;
}

bool CUI_ID_FRAME_CountryInput::InputBox_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;
	if( !s_CUI_ID_FRAME_CountryInput.IsVisable() )
		return false;

	switch( msg ) 
	{		
	case WM_KEYUP:
		{
			if( wParam == VK_ESCAPE )
			{
				s_CUI_ID_FRAME_CountryInput.ID_BUTTON_CancelOnButtonClick( NULL );
				return true;
			}
			else if( wParam == VK_RETURN )
			{
				s_CUI_ID_FRAME_CountryInput.ID_BUTTON_OKOnButtonClick( NULL );
				return true;
			}
		}
		break;
	}
	return false;
	unguard;
}

void CUI_ID_FRAME_CountryInput::SetShowType( int showType )
{
	if ( !m_pID_FRAME_CountryInput )
		return;

	m_nShowType = showType;
	switch( m_nShowType )
	{
	case CUI_ID_FRAME_Country::eShowType_None:
		break;
	case CUI_ID_FRAME_Country::eShowType_AppointJiangJun:
		m_strDescribe = theXmlString.GetString( eText_Country_AppointDaJiangJun );
		m_strTips = theXmlString.GetString( eText_Country_Tips );
		break;
	case CUI_ID_FRAME_Country::eShowType_AppointSiMa:
		m_strDescribe = theXmlString.GetString( eText_Country_AppointSiMa );
		m_strTips = theXmlString.GetString( eText_Country_Tips );
		break;
	case CUI_ID_FRAME_Country::eShowType_AppointChengXiang:
		m_strDescribe = theXmlString.GetString( eText_Country_AppointChengXiang );
		m_strTips = theXmlString.GetString( eText_Country_Tips );
		break;
	case CUI_ID_FRAME_Country::eShowType_AppointZuoJiangJun:
		m_strDescribe = theXmlString.GetString( eText_Country_AppointZuoJiangJun );
		m_strTips = theXmlString.GetString( eText_Country_Tips );
		break;
	case CUI_ID_FRAME_Country::eShowType_AppointYouJiangJun:
		m_strDescribe = theXmlString.GetString( eText_Country_AppointYouJiangJun );
		m_strTips = theXmlString.GetString( eText_Country_Tips );
		break;
	case CUI_ID_FRAME_Country::eShowType_JinYan:
		m_strDescribe = theXmlString.GetString( eText_Country_Silence );
		m_strTips = ""; //theXmlString.GetString( eText_Country_CountLeft );
		break;
	case CUI_ID_FRAME_Country::eShowType_QiuJin:
		m_strDescribe = theXmlString.GetString( eText_Country_Prison );
		m_strTips = ""; //theXmlString.GetString( eText_Country_CountLeft );
		break;
	case CUI_ID_FRAME_Country::eShowType_SheMian:
		m_strDescribe = theXmlString.GetString( eText_Country_Free );
		m_strTips = ""; //theXmlString.GetString( eText_Country_CountLeft );
		break;
    case CUI_ID_FRAME_Country::eShowType_Rename:
        m_strDescribe = theXmlString.GetString( eText_Country_PleaseInputName );
        m_strTips = theXmlString.GetString( eText_Country_ChangeNameTip );
        break;
	default:
		break;
	}

    if( showType == CUI_ID_FRAME_Country::eShowType_Rename )
        m_pID_EDIT_CountryInputName->SetMaxLength( COUNTRY_NAME_MAXLEN );
    else
        m_pID_EDIT_CountryInputName->SetMaxLength( PLAYER_NAME_MAXLEN );

	m_pID_TEXT_CountryInputDesc->SetText( m_strDescribe.c_str() );
	m_pID_EDIT_CountryInputName->SetText( "" );
	m_pID_TEXT_CountryInputTips->SetText( m_strTips.c_str() );
}

void CUI_ID_FRAME_CountryInput::ResetProperties()
{
	m_nShowType = CUI_ID_FRAME_Country::eShowType_None;
	m_strDescribe = "";
	m_strTips = "";
	m_strPlayerName = "";
}

// 以下为接收的服务器消息
void CUI_ID_FRAME_CountryInput::GetAppointResult( const MsgCountryOfficialAppointAck* pMsg )
{
	if( !pMsg )
		return;
	//pMsg->uchPosition;		//职位
	//pMsg->nPlayerID;			//玩家ID

	switch( pMsg->uchResult )
	{
	case MsgCountryOfficialAppointAck::ECD_Success:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Appoint_Success ) );
		s_CUI_ID_FRAME_BaseInfo.TryToUpdate();
		//s_CUI_ID_FRAME_Country.TryToUpdate();
		break;
	case MsgCountryOfficialAppointAck::ECD_NotRight:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Appoint_NotRight ) );
		break;
	case MsgCountryOfficialAppointAck::ECD_NotCountryMember:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Appoint_NotCountryMember ) );
		break;
	case MsgCountryOfficialAppointAck::ECD_NotOnline:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Appoint_NotOnline ) );
		break;
	case MsgCountryOfficialAppointAck::ECD_LevelLess:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Appoint_LevelLess ) );
		break;
	case MsgCountryOfficialAppointAck::ECD_Already:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Appoint_Already ) );
		break;
	case MsgCountryOfficialAppointAck::ECD_NOGuild:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Appoint_NoGuild ) );
		break;	
	case MsgCountryOfficialAppointAck::ECD_NoItem:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Appoint_NoItem ) );
		break;	

	default:
		break;
	}
}

void CUI_ID_FRAME_CountryInput::GetDismissResult( const MsgCountryOfficialRecallAck* pMsg )
{
	if( !pMsg )
		return;
	//pMsg->uchPosition;		//职位

	switch( pMsg->uchResult )
	{
	case MsgCountryOfficialRecallAck::ECD_Success:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Dismiss_Success ) );
		s_CUI_ID_FRAME_BaseInfo.TryToUpdate();
		//s_CUI_ID_FRAME_Country.TryToUpdate();
		break;
	case MsgCountryOfficialRecallAck::ECD_NotRight:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Dismiss_NotRight ) );
		break;
	case MsgCountryOfficialRecallAck::ECD_DelSuccess:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Dismiss_Del ) );
		s_CUI_ID_FRAME_BaseInfo.TryToUpdate();
		break;
	default:
		break;
	}
}

void CUI_ID_FRAME_CountryInput::GetOperateResult( const MsgCountryOperateToPlayerAck* pMsg )
{
	if( !pMsg )
		return;

	switch( pMsg->uchResult )
	{
	case MsgCountryOperateToPlayerAck::ECD_Success:
		switch( pMsg->uchOperate )
		{
		case MsgCountryOperateToPlayerReq::Operate_BanSpeak:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Slience_Success ) );
			break;
		case MsgCountryOperateToPlayerReq::Operate_Chain:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Prison_Success ) );
			break;
		case MsgCountryOperateToPlayerReq::Operate_Remit:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Free_Success ) );
			break;
		default:
			break;
		}
		s_CUI_ID_FRAME_BaseInfo.TryToUpdate();
		//s_CUI_ID_FRAME_Country.TryToUpdate();
		break;
	case MsgCountryOperateToPlayerAck::ECD_NotRight:
		switch( pMsg->uchOperate )
		{
		case MsgCountryOperateToPlayerReq::Operate_BanSpeak:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Slience_NotRight ) );
			break;
		case MsgCountryOperateToPlayerReq::Operate_Chain:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Prison_NotRight ) );
			break;
		case MsgCountryOperateToPlayerReq::Operate_Remit:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Free_NotRight ) );
			break;
		default:
			break;
		}
		break;
	case MsgCountryOperateToPlayerAck::ECD_TimeLimit:
		switch( pMsg->uchOperate )
		{
		case MsgCountryOperateToPlayerReq::Operate_BanSpeak:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Slience_TimeLimit ) );
			break;
		case MsgCountryOperateToPlayerReq::Operate_Chain:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Prison_TimeLimit ) );
			break;
		case MsgCountryOperateToPlayerReq::Operate_Remit:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Free_TimeLimit ) );
			break;
		default:
			break;
		}
		break;
	case MsgCountryOperateToPlayerAck::ECD_NotEnoughMoney:
		switch( pMsg->uchOperate )
		{
		case MsgCountryOperateToPlayerReq::Operate_BanSpeak:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Slience_NotEnoughMoney ) );
			break;
		case MsgCountryOperateToPlayerReq::Operate_Chain:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Prison_NotEnoughMoney ) );
			break;
		case MsgCountryOperateToPlayerReq::Operate_Remit:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Free_NotEnoughMoney ) );
			break;
		default:
			break;
		}
		break;
	case MsgCountryOperateToPlayerAck::ECD_NotOnLine:
		switch( pMsg->uchOperate )
		{
		case MsgCountryOperateToPlayerReq::Operate_BanSpeak:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Slience_NotOnLine ) );
			break;
		case MsgCountryOperateToPlayerReq::Operate_Chain:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Prison_NotOnLine ) );
			break;
		case MsgCountryOperateToPlayerReq::Operate_Remit:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Free_NotOnLine ) );
			break;
		default:
			break;
		}
		break;
	case MsgCountryOperateToPlayerAck::ECD_NotSameCountry:
		switch( pMsg->uchOperate )
		{
		case MsgCountryOperateToPlayerReq::Operate_BanSpeak:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Slience_NotSameCountry ) );
			break;
		case MsgCountryOperateToPlayerReq::Operate_Chain:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Prison_NotSameCountry ) );
			break;
		case MsgCountryOperateToPlayerReq::Operate_Remit:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Free_NotSameCountry ) );
			break;
		default:
			break;
		}
		break;
    case MsgCountryOperateToPlayerAck::ECD_NeedNotRemit:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Free_NeedNotRemit ) );
        }
        break;
	case MsgCountryOperateToPlayerAck::ECD_CountryBattle:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Battle_None ) );
			//弹MessageBox
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_Country_Battle_None));
		}
		break;
	default:
		break;
	}
}

void CUI_ID_FRAME_CountryInput::GetBeOperatedInfo( uint8 operateType )
{
	switch( operateType )
	{
	case MsgCountryOperateToPlayerReq::Operate_BanSpeak:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, theXmlString.GetString( eText_Country_Operate_Slience ) );
		break;
	case MsgCountryOperateToPlayerReq::Operate_Chain:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, theXmlString.GetString( eText_Country_Operate_Prison ) );
		break;
	case MsgCountryOperateToPlayerReq::Operate_Remit:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, theXmlString.GetString( eText_Country_Operate_Free ) );
		break;
	default:
		break;
	}
}

void CUI_ID_FRAME_CountryInput::GetBeAppointInfo( const MsgCountryTellAppoint* pMsg )
{
	if( !pMsg )
		return;
    std::string strPostion = CountryFunction::GetCountryOfficialNameById( pMsg->uchPosition );
	if(pMsg->uchPosition == Position_Queen && thePlayerRole.GetSex() == Sex_Male)
		strPostion=   theXmlString.GetString( eText_CountryPos_QueenMale );//亲王
	char szBeAppoint[ eMAX_TEMP_BUFF ] = {0};
	switch( pMsg->uchType )
	{
	case MsgCountryTellAppoint::ECD_Appoint:
		MeSprintf_s( szBeAppoint, eMAX_TEMP_BUFF - 1, theXmlString.GetString( eText_Country_Appoint_BeAppoint ), strPostion.c_str() );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szBeAppoint );
        thePlayerRole.m_charinfo.baseinfo.liveinfo.nCountryTitle = GetCountryTitleByPosition( pMsg->uchPosition );
		break;
	case MsgCountryTellAppoint::ECD_Recall:
		MeSprintf_s( szBeAppoint, eMAX_TEMP_BUFF - 1, theXmlString.GetString( eText_Country_Appoint_BeDismiss ), strPostion.c_str() );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szBeAppoint );
        thePlayerRole.m_charinfo.baseinfo.liveinfo.nCountryTitle = Title_None;
		break;
	default:
		break;
	}
	s_CUI_ID_FRAME_BaseInfo.TryToUpdate();
	//s_CUI_ID_FRAME_Country.TryToUpdate();
}

void CUI_ID_FRAME_CountryInput::GetPlayerBeOperatedInfo( MsgTellOperateToCountry* pMsg )
{
    if( !pMsg )
        return;

    char szOperateBuf[ eMAX_TEMP_BUFF ] = {0};
    switch( pMsg->uchOperate )
    {
    case MsgCountryOperateToPlayerReq::Operate_BanSpeak:
        MeSprintf_s( szOperateBuf, sizeof( szOperateBuf ) / sizeof( char ) - 1, theXmlString.GetString( eText_Country_PlayerBeSilence ), pMsg->szName );
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szOperateBuf );
        break;
    case MsgCountryOperateToPlayerReq::Operate_Chain:
        MeSprintf_s( szOperateBuf, sizeof( szOperateBuf ) / sizeof( char ) - 1, theXmlString.GetString( eText_Country_PlayerBePrison ), pMsg->szName );
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szOperateBuf );
        break;
    case MsgCountryOperateToPlayerReq::Operate_Remit:
        MeSprintf_s( szOperateBuf, sizeof( szOperateBuf ) / sizeof( char ) - 1, theXmlString.GetString( eText_Country_PlayerBeFree ), pMsg->szName );
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szOperateBuf );
        break;
    default:
        break;
    }
}
