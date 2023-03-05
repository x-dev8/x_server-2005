/********************************************************************
Created by UIEditor.exe
FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\Announce.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Announce.h"
#include "create.h"
#include"MessageBox.h"
#include "core/Name.h"
#include "MessageDefine.h"
#include "NetworkInput.h"
//#include "Guild.h"
#include "PlayerRole.h"
#include "UIMgr.h"
#include "Common.h"
#include "GuildDefine.h"
#include "XmlStringLanguage.h"
#include "chatcheck.h"
#include "ScreenInfoManager.h"

extern HWND g_hWnd;

CUI_ID_FRAME_Announce s_CUI_ID_FRAME_Announce;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Announce, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Announce, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_Announce, ID_EDIT_InfoOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Announce, ID_BUTTON_CancelOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Announce, ID_BUTTON_CLOSEOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Announce, ID_BUTTON_helpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Announce, ID_BUTTON_SaveOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Announce, ID_BUTTON_RestartOnButtonClick )
CUI_ID_FRAME_Announce::CUI_ID_FRAME_Announce()
{
	// Member
	m_pID_FRAME_Announce = NULL;
	m_pID_EDIT_Info = NULL;
	m_pID_BUTTON_Cancel = NULL;
// 	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
	m_pID_BUTTON_Save = NULL;
	m_pID_BUTTON_Restart = NULL;
	m_bGang = true;
	m_MaxLength = 0;
}
// Frame
bool CUI_ID_FRAME_Announce::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_Announce::OnFrameRender()
{
	/*int length= strlen(m_pID_EDIT_Info->GetText());
	if((m_LogLength != length || m_LogLength ==m_MaxLength ) && m_MaxLength <= length && E_Type_Announcement == m_dlgType)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, theXmlString.GetString( eText_GuildGG) );
		m_LogLength = length;
		return true;
	}*/
	if(E_Type_Announcement == m_dlgType)
	{
		int length= strlen(m_pID_EDIT_Info->GetText());
		while(m_MaxLength <= length)
		{
			m_pID_EDIT_Info->DelByte(true);
			length= strlen(m_pID_EDIT_Info->GetText());
		}
	}
	return true;
}
// Edit
void CUI_ID_FRAME_Announce::ID_EDIT_InfoOnEditEnter( ControlObject* pSender, const char* szData )
{
	m_pID_EDIT_Info->SetActivate(true);
}
// Button
bool CUI_ID_FRAME_Announce::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	return true;
}
// Button
// bool CUI_ID_FRAME_Announce::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
// {
// 	SetVisable(false);
// 	return true;+
// }
// // Button
// bool CUI_ID_FRAME_Announce::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	return true;
// }
// Button
bool CUI_ID_FRAME_Announce::ID_BUTTON_SaveOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_Announce)
	{
		assert(false&&"ui error");
		return false;
	}
	bool bIsForbit_1	= CChatCheck::getInstance()->CheckStringInLow(m_pID_EDIT_Info->GetText());
	if (!bIsForbit_1)
	{	
		//含有非法字符
		if(E_Type_Announcement == m_dlgType)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, theXmlString.GetString( eText_FamilyNoteForbiddenWords) );
		}
		else if(E_Type_Creed == m_dlgType)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, theXmlString.GetString( eTextGuild_CreedForbindText) );
		}
		return false;
	}
	if(m_pID_EDIT_Info != NULL)
	{
		//判断字符的长度
		int length= strlen(m_pID_EDIT_Info->GetText());
		if(m_MaxLength <= length && E_Type_Announcement == m_dlgType)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, theXmlString.GetString( eText_GuildGG) );
			return false;
		}
		SendMsg_ChangeGuild(m_pID_EDIT_Info->GetText());
	}
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_Announce::ID_BUTTON_RestartOnButtonClick( ControlObject* pSender )
{
	m_pID_EDIT_Info->SetText("");
	return true;
}

// 装载UI
bool CUI_ID_FRAME_Announce::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Announce.MEUI" , false, UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Announce.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Announce::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Announce, s_CUI_ID_FRAME_AnnounceOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Announce, s_CUI_ID_FRAME_AnnounceOnFrameRender );
	theUiManager.OnEditEnter( ID_FRAME_Announce, ID_EDIT_Info, s_CUI_ID_FRAME_AnnounceID_EDIT_InfoOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_Announce, ID_BUTTON_Cancel, s_CUI_ID_FRAME_AnnounceID_BUTTON_CancelOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_Announce, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_AnnounceID_BUTTON_CLOSEOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_Announce, ID_BUTTON_help, s_CUI_ID_FRAME_AnnounceID_BUTTON_helpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Announce, ID_BUTTON_Save, s_CUI_ID_FRAME_AnnounceID_BUTTON_SaveOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Announce, ID_BUTTON_Restart, s_CUI_ID_FRAME_AnnounceID_BUTTON_RestartOnButtonClick );

	m_pID_FRAME_Announce = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Announce );
	m_pID_EDIT_Info = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Announce, ID_EDIT_Info );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_Announce, ID_BUTTON_Cancel );
// 	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Announce, ID_BUTTON_CLOSE );
// 	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_Announce, ID_BUTTON_help );
	m_pID_BUTTON_Save = (ControlButton*)theUiManager.FindControl( ID_FRAME_Announce, ID_BUTTON_Save );
	m_pID_BUTTON_Restart = (ControlButton*)theUiManager.FindControl( ID_FRAME_Announce, ID_BUTTON_Restart );
	m_pID_TEXT_Msg = (ControlText*)theUiManager.FindControl( ID_FRAME_Announce, ID_TEXT_Msg);
	assert( m_pID_FRAME_Announce );
	assert( m_pID_EDIT_Info );
	assert( m_pID_BUTTON_Cancel );
// 	assert( m_pID_BUTTON_CLOSE );
// 	assert( m_pID_BUTTON_help );
	assert( m_pID_BUTTON_Save );
	assert( m_pID_BUTTON_Restart );

	USE_SCRIPT( eUI_OBJECT_Announce, this );

	//m_pID_EDIT_Info->SetMaxLength(GuildDefine::MaxNoticeLength );
	if( !s_CUI_ID_FRAME_CREATE.GetImeInstance() )
		s_CUI_ID_FRAME_CREATE.SetImeInstance( ImmGetContext( g_hWnd ) );

	ImmReleaseContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );

	//m_pID_EDIT_Info->SetMaxLength(GuildDefine::MaxNoticeLength / 2 - 1);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Announce::_UnLoadUI()
{
	CLOSE_SCRIPT( eUI_OBJECT_Announce );
	m_pID_FRAME_Announce = NULL;
	m_pID_EDIT_Info = NULL;
	m_pID_BUTTON_Cancel = NULL;
//	m_pID_BUTTON_CLOSE = NULL;
//	m_pID_BUTTON_help = NULL;
	m_pID_BUTTON_Save = NULL;
	m_pID_BUTTON_Restart = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\Announce.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Announce::_IsVisable()
{
	if( !m_pID_FRAME_Announce )
		return false;
	return m_pID_FRAME_Announce->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Announce::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_Announce )
		return;
	m_pID_FRAME_Announce->SetVisable( bVisable );
	if( bVisable == true)
	{
		theUiManager.SetFocus(m_pID_EDIT_Info);
		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
		CGangMgr* pGMM = thePlayerRole.GetGangMgr();
		/*m_pID_EDIT_Info->SetText(pGMM->GetGuildIntro());*/

		Refresh();
	}
	else
	{
		ImmAssociateContext( g_hWnd, NULL );
	}
}

bool CUI_ID_FRAME_Announce::EditInputIsVisable()
{
	guardfunc;
	if( m_pID_EDIT_Info )
	{
		return (theUiManager.GetFocus() == m_pID_EDIT_Info);
	}
	return FALSE;
	unguard;

}

void CUI_ID_FRAME_Announce::Refresh(void)
{
	const char *pTitle = NULL;
	int maxLen = 0;
	const char *pContent = NULL;

	if(E_Type_Announcement == m_dlgType)
	{
		pTitle = theXmlString.GetString(eText_Guild_Announcement);
		maxLen = GuildDefine::MaxNoticeLength - 1;

		CGangMgr* pGuild = thePlayerRole.GetGangMgr();
		if(pGuild != NULL)
		{
			pContent = pGuild->GetGuildNotice();
		}
	}
	else if(E_Type_Creed == m_dlgType)
	{
		pTitle = theXmlString.GetString(eText_Guild_Creed);
		maxLen = GuildDefine::MaxAimLength - 1;

		CGangMgr* pGuild = thePlayerRole.GetGangMgr();
		if(pGuild != NULL)
		{
			pContent = pGuild->GetGuildAim();
		}
	}

	if(m_pID_TEXT_Msg)
	{
		if(pTitle != NULL)
			m_pID_TEXT_Msg->SetText(pTitle);
		else
			m_pID_TEXT_Msg->Clear();
	}

	if(m_pID_EDIT_Info)
	{
		m_pID_EDIT_Info->SetText("");
		m_pID_EDIT_Info->SetMaxLength(maxLen);
		m_MaxLength = maxLen;
		if(pContent != NULL)
		{
			m_pID_EDIT_Info->SetText(pContent);
		}
	}
}

void CUI_ID_FRAME_Announce::SendMsg_ChangeGuild(const char *content_)
{
	assert(content_ != NULL);
	if(NULL == content_)
		return;

	if(E_Type_Announcement == m_dlgType)
	{
		SendMsg_ChangeGuildAnnouncement(content_);
	}
	else if(E_Type_Creed == m_dlgType)
	{
		SendMsg_ChangeGuildCreed(content_);
	}
}

bool SendMsg_ChangeGuildAnnouncement(const char *content_)
{
	assert(content_ != NULL);
	if(NULL == content_)
		return false;

	MsgGuildNoticeChangeReq info;
	MeSprintf_s(info.szNotice, sizeof(info.szNotice)/sizeof(char) - 1, "%s", content_);
	GettheNetworkInput().SendMsg(&info);

	return true;
}

bool SendMsg_ChangeGuildCreed(const char *content_)
{
	assert(content_ != NULL);
	if(NULL == content_)
		return false;

	MsgChangeGuildAimReq info;
	MeSprintf_s(info.szAim, sizeof(info.szAim)/sizeof(char) - 1, "%s", content_);
	GettheNetworkInput().SendMsg(&info);

	return true;
}