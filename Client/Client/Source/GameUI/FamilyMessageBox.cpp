/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (13)\FamilyMessageBox.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Family.h"
#include "FamilyDefine.h"
#include "FamilyMessage.h"
#include "NetworkInput.h"
#include "Create.h"
#include "FamilyConfig.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "ScreenInfoManager.h"
#include "ChatCheck.h"
#include "FamilyMessageBox.h"

extern HWND g_hWnd;

CUI_ID_FRAME_GUILD_FamilyMessageBox s_CUI_ID_FRAME_GUILD_FamilyMessageBox;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GUILD_FamilyMessageBox, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GUILD_FamilyMessageBox, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GUILD_FamilyMessageBox, ID_BUTTON_CREATEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GUILD_FamilyMessageBox, ID_BUTTON_closeOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GUILD_FamilyMessageBox, ID_TEXT_MessageOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GUILD_FamilyMessageBox, ID_BUTTON_AgreeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GUILD_FamilyMessageBox, ID_BUTTON_RefuseOnButtonClick )
CUI_ID_FRAME_GUILD_FamilyMessageBox::CUI_ID_FRAME_GUILD_FamilyMessageBox()
{
	// Member
	m_pID_FRAME_GUILD_FamilyMessageBox = NULL;
	m_pID_BUTTON_CREATE = NULL;
	m_pID_BUTTON_close = NULL;
	m_pID_TEXT_Info1 = NULL;
	m_pID_TEXT_FamilyName = NULL;
	m_pID_TEXT_Info2 = NULL;
	m_pID_TEXT_PlayerName = NULL;
	m_pID_TEXT_Info3 = NULL;
	m_pID_TEXT_Info4 = NULL;
	m_pID_TEXT_Message = NULL;
	m_pID_BUTTON_Agree = NULL;
	m_pID_BUTTON_Refuse = NULL;

}


bool CUI_ID_FRAME_GUILD_FamilyMessageBox::EditInputIsVisable()
{
	if ( m_pID_TEXT_Message == NULL )
	{
		return false;
	}
	return ( m_pID_TEXT_Message == theUiManager.GetFocus() );
}

void CUI_ID_FRAME_GUILD_FamilyMessageBox::HideAllCaption()
{
	m_pID_TEXT_Info3->SetVisable(false);
	m_pID_TEXT_Info4->SetVisable(false);
	m_pID_TEXT_Info1->SetVisable(false);
	m_pID_TEXT_Info2->SetVisable(false);
	m_pID_TEXT_FamilyName->SetVisable(false);
	m_pID_TEXT_PlayerName->SetVisable(false);
}

void CUI_ID_FRAME_GUILD_FamilyMessageBox::ShowAsModifyNote()
{
	this->SetVisable(true);
	if ( !m_pID_FRAME_GUILD_FamilyMessageBox )
		return;
	
	m_eVierwType = eVT_ModifyNote;
	HideAllCaption();
	m_pID_TEXT_Info4->SetVisable(true);
	m_pID_TEXT_Message->SetEnable(true);
	const FamilyConfig::FamilyWordsLenLimits& lenconfig = theFamilyConfig.GetFamilyWordsLenLimits();
	m_pID_TEXT_Message->SetMaxLength( lenconfig.GetNoteLenMax() );
	ShowOkCancelButton();
}

void CUI_ID_FRAME_GUILD_FamilyMessageBox::ShowAsRequestMsgSend()
{
	this->SetVisable(true);
	if ( !m_pID_FRAME_GUILD_FamilyMessageBox )
		return;
	
	m_eVierwType = eVT_RequestMsgSend;
	HideAllCaption();
	m_pID_TEXT_Info1->SetVisable(true);
	m_pID_TEXT_FamilyName->SetVisable(true);
	m_pID_TEXT_Info2->SetVisable(true);
	m_pID_TEXT_Message->SetEnable(true);
	const FamilyConfig::FamilyWordsLenLimits& lenconfig = theFamilyConfig.GetFamilyWordsLenLimits();
	m_pID_TEXT_Message->SetMaxLength( lenconfig.GetRequestMsgLenMax() );
	ShowOkCancelButton();
}

void CUI_ID_FRAME_GUILD_FamilyMessageBox::ShowAsRequestMsgRev()
{
	this->SetVisable(true);
	if ( !m_pID_FRAME_GUILD_FamilyMessageBox )
		return;
	
	m_eVierwType = eVT_RequestMsgRev;
	HideAllCaption();
	m_pID_TEXT_PlayerName->SetVisable(true);
	m_pID_TEXT_Info3->SetVisable(true);
	m_pID_TEXT_Message->SetEnable(false);
	const FamilyConfig::FamilyWordsLenLimits& lenconfig = theFamilyConfig.GetFamilyWordsLenLimits();
	m_pID_TEXT_Message->SetMaxLength( lenconfig.GetRequestMsgLenMax() );
	ShowAcceptRefuseButton();
}

void CUI_ID_FRAME_GUILD_FamilyMessageBox::ShowOkCancelButton()
{
	m_pID_BUTTON_CREATE->SetVisable(true);
	m_pID_BUTTON_close->SetVisable(true);
	m_pID_BUTTON_Agree->SetVisable( false );
	m_pID_BUTTON_Refuse->SetVisable( false );
}

void CUI_ID_FRAME_GUILD_FamilyMessageBox::ShowAcceptRefuseButton()
{
	m_pID_BUTTON_CREATE->SetVisable(false);
	m_pID_BUTTON_close->SetVisable(false);
	m_pID_BUTTON_Agree->SetVisable( true );
	m_pID_BUTTON_Refuse->SetVisable( true );
}

void CUI_ID_FRAME_GUILD_FamilyMessageBox::SetRequestFamilyInfo( unsigned int familyId, const char* familyName )
{
	m_nFamilyID = familyId;
	m_szFamilyName = familyName;
	m_pID_TEXT_FamilyName->SetText( familyName );
}

void CUI_ID_FRAME_GUILD_FamilyMessageBox::SetRequestPlayerInfo( unsigned int playerDbid, const char* playerName, const char* note )
{
	m_nPlayerDBID = playerDbid;
	m_szPlayerName = playerName;
	m_szNote = note;
	m_pID_TEXT_PlayerName->SetText(playerName);
	m_pID_TEXT_Message->SetText( note );
}

// Frame
bool CUI_ID_FRAME_GUILD_FamilyMessageBox::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_GUILD_FamilyMessageBox::OnFrameRender()
{
	return true;
}
// Button 确定
bool CUI_ID_FRAME_GUILD_FamilyMessageBox::ID_BUTTON_CREATEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GUILD_FamilyMessageBox )
		return false;

	int len = _mbslen((const unsigned char*)m_pID_TEXT_Message->GetText());
	//unsigned int len = (unsigned int)strlen( m_pID_TEXT_Message->GetText() );
	const FamilyConfig::FamilyWordsLenLimits& lenconfig = theFamilyConfig.GetFamilyWordsLenLimits();


	if ( m_eVierwType == eVT_ModifyNote )
	{
		if ( len < lenconfig.GetNoteLenMin() || len > lenconfig.GetNoteLenMax() )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_FamilyNoteLenIncorrect), "", 
				CUI_ID_FRAME_MessageBox::eTypeConfirm );
			return true;
		}

		//客户端预先判断是否含有非法字符
		/*
		 * Author: 2012-10-12 14:06:33 liaojie
		 * Desc:   原来的判断很蛋疼，修改一下，直接替换非法字符
		 */
		char *pszText = const_cast<char*>(m_pID_TEXT_Message->GetText());
		std::string strChat = CChatCheck::getInstance()->CheckStringInLowMark( pszText, '*');
		/*if( CChatCheck::getInstance()->CheckStringInLow(m_pID_TEXT_Message->GetText()) == false )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, theXmlString.GetString(eText_FamilyNoteForbiddenWords) );
			return true;
		}*/

		s_CUI_ID_FRAME_Family.m_pID_TEXT_Affiche->SetText(strChat.c_str());
		MsgFamilyNoticeReq msg;
		sprintf_s( msg.szNotice, FamilyDefine::MaxFamilyNoticeLen - 1, "%s", m_pID_TEXT_Message->GetText() );
		GettheNetworkInput().SendMsg(&msg);
	}
	else if ( m_eVierwType == eVT_RequestMsgSend )
	{
		if ( len < lenconfig.GetRequestMsgLenMin() || len > lenconfig.GetRequestMsgLenMax() )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_FamilyRequestMsg), "",
				CUI_ID_FRAME_MessageBox::eTypeConfirm );
			return true;
		}
		MsgJoinFamilyReq msg;
		msg.nFamilyID = m_nFamilyID;
		sprintf_s( msg.szNote, FamilyDefine::MaxRequestNoteLen - 1, "%s", m_pID_TEXT_Message->GetText() );
		GettheNetworkInput().SendMsg(&msg);

		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			theXmlString.GetString(eText_FamilyJoinSucess) );
	}
	else if ( m_eVierwType == eVT_RequestMsgRev )	//族长收到申请确定
	{
		MsgRequestJoinFamilyAck msg;
		msg.bAgreeJoin = true;
		msg.nPlayerID = m_nPlayerDBID;
		GettheNetworkInput().SendMsg(&msg);
	}
	
	
	
	this->SetVisable(false);
	return true;
}
// Button 取消
bool CUI_ID_FRAME_GUILD_FamilyMessageBox::ID_BUTTON_closeOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GUILD_FamilyMessageBox )
		return false;

	if ( m_eVierwType == eVT_RequestMsgRev )
	{
		MsgRequestJoinFamilyAck msg;
		msg.bAgreeJoin = false;
		msg.nPlayerID = m_nPlayerDBID;
		GettheNetworkInput().SendMsg(&msg);
	}
	

	this->SetVisable(false);
	return true;
}

// Button
bool CUI_ID_FRAME_GUILD_FamilyMessageBox::ID_BUTTON_AgreeOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GUILD_FamilyMessageBox )
		return false;
	ID_BUTTON_CREATEOnButtonClick(pSender);
	return true;
}
// Button
bool CUI_ID_FRAME_GUILD_FamilyMessageBox::ID_BUTTON_RefuseOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GUILD_FamilyMessageBox )
		return false;
	ID_BUTTON_closeOnButtonClick(pSender);
	return true;
}

// Edit
void CUI_ID_FRAME_GUILD_FamilyMessageBox::ID_TEXT_MessageOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_GUILD_FamilyMessageBox )
		return;
}

// 装载UI
bool CUI_ID_FRAME_GUILD_FamilyMessageBox::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\FamilyMessageBox.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\FamilyMessageBox.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}

static void UIFamilyMessageBox_OnVisibleChanged(ControlObject* pSender)
{
	if (pSender && !pSender->IsVisable())
		ImmAssociateContext( g_hWnd, NULL );
}

// 关连控件
bool CUI_ID_FRAME_GUILD_FamilyMessageBox::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GUILD_FamilyMessageBox, s_CUI_ID_FRAME_GUILD_FamilyMessageBoxOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GUILD_FamilyMessageBox, s_CUI_ID_FRAME_GUILD_FamilyMessageBoxOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GUILD_FamilyMessageBox, ID_BUTTON_CREATE, s_CUI_ID_FRAME_GUILD_FamilyMessageBoxID_BUTTON_CREATEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GUILD_FamilyMessageBox, ID_BUTTON_close, s_CUI_ID_FRAME_GUILD_FamilyMessageBoxID_BUTTON_closeOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_GUILD_FamilyMessageBox, ID_TEXT_Message, s_CUI_ID_FRAME_GUILD_FamilyMessageBoxID_TEXT_MessageOnEditEnter );

	theUiManager.OnButtonClick( ID_FRAME_GUILD_FamilyMessageBox, ID_BUTTON_Agree, s_CUI_ID_FRAME_GUILD_FamilyMessageBoxID_BUTTON_AgreeOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GUILD_FamilyMessageBox, ID_BUTTON_Refuse, s_CUI_ID_FRAME_GUILD_FamilyMessageBoxID_BUTTON_RefuseOnButtonClick );

	m_pID_FRAME_GUILD_FamilyMessageBox = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GUILD_FamilyMessageBox );
	m_pID_BUTTON_CREATE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyMessageBox, ID_BUTTON_CREATE );
	m_pID_BUTTON_close = (ControlButton*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyMessageBox, ID_BUTTON_close );
	m_pID_TEXT_Info1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyMessageBox, ID_TEXT_Info1 );
	m_pID_TEXT_FamilyName = (ControlText*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyMessageBox, ID_TEXT_FamilyName );
	m_pID_TEXT_Info2 = (ControlText*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyMessageBox, ID_TEXT_Info2 );
	m_pID_TEXT_PlayerName = (ControlText*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyMessageBox, ID_TEXT_PlayerName );
	m_pID_TEXT_Info3 = (ControlText*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyMessageBox, ID_TEXT_Info3 );
	m_pID_TEXT_Info4 = (ControlText*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyMessageBox, ID_TEXT_Info4 );
	m_pID_TEXT_Message = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyMessageBox, ID_TEXT_Message );

	m_pID_BUTTON_Agree = (ControlButton*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyMessageBox, ID_BUTTON_Agree );
	m_pID_BUTTON_Refuse = (ControlButton*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyMessageBox, ID_BUTTON_Refuse );

	assert( m_pID_FRAME_GUILD_FamilyMessageBox );
	assert( m_pID_BUTTON_CREATE );
	assert( m_pID_BUTTON_close );
	assert( m_pID_TEXT_Info1 );
	assert( m_pID_TEXT_FamilyName );
	assert( m_pID_TEXT_Info2 );
	assert( m_pID_TEXT_PlayerName );
	assert( m_pID_TEXT_Info3 );
	assert( m_pID_TEXT_Info4 );
	assert( m_pID_TEXT_Message );

	assert( m_pID_BUTTON_Agree );
	assert( m_pID_BUTTON_Refuse );

	m_pID_FRAME_GUILD_FamilyMessageBox->SetOnVisibleChangedFun(UIFamilyMessageBox_OnVisibleChanged);

	if( !s_CUI_ID_FRAME_CREATE.GetImeInstance() )
		s_CUI_ID_FRAME_CREATE.SetImeInstance( ImmGetContext( g_hWnd ) );

	ImmReleaseContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GUILD_FamilyMessageBox::_UnLoadUI()
{
	m_pID_FRAME_GUILD_FamilyMessageBox = NULL;
	m_pID_BUTTON_CREATE = NULL;
	m_pID_BUTTON_close = NULL;
	m_pID_TEXT_Info1 = NULL;
	m_pID_TEXT_FamilyName = NULL;
	m_pID_TEXT_Info2 = NULL;
	m_pID_TEXT_PlayerName = NULL;
	m_pID_TEXT_Info3 = NULL;
	m_pID_TEXT_Info4 = NULL;
	m_pID_TEXT_Message = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\FamilyMessageBox.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GUILD_FamilyMessageBox::_IsVisable()
{
	if ( !m_pID_FRAME_GUILD_FamilyMessageBox )
		return false;
	return m_pID_FRAME_GUILD_FamilyMessageBox->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GUILD_FamilyMessageBox::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_GUILD_FamilyMessageBox )
		return;
	m_pID_FRAME_GUILD_FamilyMessageBox->SetVisable( bVisable );
	m_pID_TEXT_Message->SetText("");
	if( bVisable )
	{
		// 设置焦点	开启输入法
		m_pID_TEXT_Message->SetActivate( true );
		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
	}
	else
	{
		// 关闭输入法
		ImmAssociateContext( g_hWnd, NULL );
	}
}
