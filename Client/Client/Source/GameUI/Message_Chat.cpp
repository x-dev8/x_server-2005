/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\Hero\Program\trunk\Bin\Client\Data\Ui\Message_Chat.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "UIMgr.h"
#include "Message_Chat.h"
#include "FaceDlg1.h"
#include "Create.h"
#include "ChatMessageMgr.h"
extern HWND g_hWnd;
#include "color_config.h"
#include "MiniChat.h"
#include "GameSetting.h"
#include "ChatHistory.h"
#include "XmlStringLanguage.h"
#include "Meui/ExpressionManager.h"
#include "tstring.h"
#include "ScreenInfoManager.h"
#include "chatcheck.h"
#include "PlayerRole.h"
#include "Dxsdk/dinput.h"
#include "Common.h"
#include "RelationMessage.h"
#include "RelationDefine.h"
#include "NetworkInput.h"
#include "AddFriend.h"
extern ChatMessageMgr chatMessageManage;
extern short GetKeyboardInput( int iKey );

MAP_FRAME_RUN_INDEX( chatMessageManage, OnFrameRunIndexedFrame )
MAP_FRAME_RENDER_INDEX( chatMessageManage, OnFrameRenderIndexedFrame)
MAP_BUTTON_CLICK_CALLBACK( chatMessageManage, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( chatMessageManage, ID_BUTTON_MinimizeOnButtonClick )
// MAP_LIST_SELECT_CHANGE_CALLBACK( chatMessageManage, ID_LIST_CharOnListSelectChange )
MAP_CHECK_BOX_CHECK_CALLBACK( chatMessageManage, ID_CHECKBOX_SaveOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( chatMessageManage, ID_BUTTON_ClearOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( chatMessageManage, ID_BUTTON_faceOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( chatMessageManage, ID_EDIT_INPUTOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( chatMessageManage, ID_BUTTON_HistoryOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( chatMessageManage, ID_BUTTON_EnterOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK(chatMessageManage , ID_BUTTON_AddFriendOnButtonClick )

CUI_ID_FRAME_Message_Chat::CUI_ID_FRAME_Message_Chat(int frameIndex)
{
	// Member
	m_pChatInfoBox = NULL;
	m_pID_TEXT_Target = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Minimize = NULL;
	m_pChatInfoText = NULL;
	m_pID_CHECKBOX_Save = NULL;
	m_pID_BUTTON_Clear = NULL;
	m_pID_BUTTON_face = NULL;
	m_pID_EDIT_INPUT = NULL;
	m_pID_BUTTON_History = NULL;
	m_pID_BUTTON_Enter = NULL;
	m_FrameIndex			= frameIndex;
	m_pObject				= NULL;
	m_pID_BUTTON_AddFriend = NULL;
	MeSprintf_s(szFrameID,sizeof(szFrameID)/sizeof(char) - 1,"%s%d",ID_FRAME_Message_Chat,frameIndex);

}
// Button
bool CUI_ID_FRAME_Message_Chat::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if( !m_pChatInfoBox )
		return false;
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_Message_Chat::ID_BUTTON_MinimizeOnButtonClick( ControlObject* pSender )
{
	if( !m_pChatInfoBox )
		return false;
	SetVisable(false);
	g_bMessageChat = false;
	s_CUI_ID_FRAME_MiniChat.AddMiniPlayerListName(m_szPrivateToName.c_str());
	return true;
}
// List
// void CUI_ID_FRAME_Message_Chat::ID_LIST_CharOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
// {
// 	if( !m_pChatInfoBox )
// 		return;
// }
// CheckBox
void CUI_ID_FRAME_Message_Chat::ID_CHECKBOX_SaveOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pChatInfoBox )
		return;
	if (*pbChecked)
	{
		GameSetting::Instance()->SetLevel(GameSetting::eGSC_SAVECHATMESSAGE,1);
	}
	else
	{
		GameSetting::Instance()->SetLevel(GameSetting::eGSC_SAVECHATMESSAGE,0);
	}
	chatMessageManage.RefreshSaveMessageCheckBox();
}
// Button
bool CUI_ID_FRAME_Message_Chat::ID_BUTTON_ClearOnButtonClick( ControlObject* pSender )
{
	if( !m_pChatInfoBox )
		return false;
	MessageInfoMgr::Instance()->SaveChatMessage(m_szPrivateToName.c_str());
	MessageInfoMgr::InfoList* pInfoList = MessageInfoMgr::Instance()->GetInfoList(m_szPrivateToName.c_str());
	if (pInfoList)
	{
		pInfoList->Reset();
	}
	m_pChatInfoText->Clear();
	return true;
}
// Edit
void CUI_ID_FRAME_Message_Chat::ID_EDIT_INPUTOnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pChatInfoBox )
		return;
	if( _bActiveInput )
	{
		SendMessage(szData);
		s_CUI_ID_FRAME_FACE.SetVisable( false );
		m_pID_EDIT_INPUT->SetActivate(true);
		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
		ChangeImmPos();

		m_bSendMsg = true;
	}

}
// Button
bool CUI_ID_FRAME_Message_Chat::ID_BUTTON_HistoryOnButtonClick( ControlObject* pSender )
{
	if( !m_pChatInfoBox )
		return false;
	s_CUI_ID_FRAME_ChatHistory.ShowHistoryChat(m_szPrivateToName.c_str());
	return true;
}
// Button
bool CUI_ID_FRAME_Message_Chat::ID_BUTTON_EnterOnButtonClick( ControlObject* pSender )
{
	if( !m_pChatInfoBox )
		return false;
	SendMessage(m_pID_EDIT_INPUT->GetText());
	m_pID_EDIT_INPUT->SetActivate(true);
	ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
	ChangeImmPos();
	return true;
}

bool CUI_ID_FRAME_Message_Chat::ID_BUTTON_AddFriendOnButtonClick(ControlObject* pSender)
{
    if( !m_pChatInfoBox )
        return false;

    s_CUI_ID_FRAME_AddFriend.SetFrameType( CUI_ID_FRAME_AddFriend::eFrameType_AddFriendFromRMenu );
    s_CUI_ID_FRAME_AddFriend.SetPrivateName( m_szPrivateToName.c_str() );
    s_CUI_ID_FRAME_AddFriend.SetVisable(true);
    return true;
}

static void OnVisibleChange( ControlObject* pUIObject )
{
	if (pUIObject && !pUIObject->IsVisable())
	{

		g_bMessageChat = false;
		ImmAssociateContext( g_hWnd, NULL );
	}

	if(!chatMessageManage.GetActiveMessageFrame())	
	{
		g_bMessageChat = false;
		ImmAssociateContext( g_hWnd, NULL );
	}
}

// 装载UI
bool CUI_ID_FRAME_Message_Chat::_LoadUI()
{
	m_pObject = theUiManager.AddFrameByIndex( "Data\\UI\\Message_Chat.MEUI" ,m_FrameIndex,false, UI_Render_LayerThree);
	if ( m_pObject == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Message_Chat.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Message_Chat::DoControlConnect()
{
	theUiManager.OnFrameRunIndexedFrame( szFrameID, chatMessageManageOnFrameRunIndexedFrame );
	theUiManager.OnFrameRenderIndexedFrame( szFrameID, chatMessageManageOnFrameRenderIndexedFrame );
	theUiManager.OnButtonClick( szFrameID, ID_BUTTON_CLOSE, chatMessageManageID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( szFrameID, ID_BUTTON_Minimize, chatMessageManageID_BUTTON_MinimizeOnButtonClick );
// 	theUiManager.OnListSelectChange( szFrameID, ID_LIST_Char, chatMessageManageID_LIST_CharOnListSelectChange );
	theUiManager.OnCheckBoxCheck( szFrameID, ID_CHECKBOX_Save, chatMessageManageID_CHECKBOX_SaveOnCheckBoxCheck );
	theUiManager.OnButtonClick( szFrameID, ID_BUTTON_Clear, chatMessageManageID_BUTTON_ClearOnButtonClick );
	theUiManager.OnButtonClick( szFrameID, ID_BUTTON_face, chatMessageManageID_BUTTON_faceOnButtonClick );
	theUiManager.OnEditEnter( szFrameID, ID_EDIT_Input, chatMessageManageID_EDIT_INPUTOnEditEnter );
	theUiManager.OnButtonClick( szFrameID, ID_BUTTON_History, chatMessageManageID_BUTTON_HistoryOnButtonClick );
	theUiManager.OnButtonClick( szFrameID, ID_BUTTON_Enter, chatMessageManageID_BUTTON_EnterOnButtonClick );
	theUiManager.OnButtonClick( szFrameID, ID_BUTTON_AddFriend, chatMessageManageID_BUTTON_AddFriendOnButtonClick);

	m_pChatInfoBox = (ControlFrame*)theUiManager.FindFrame( szFrameID );
	m_pID_TEXT_Target = (ControlText*)theUiManager.FindControl( szFrameID, ID_TEXT_Target );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( szFrameID, ID_BUTTON_CLOSE );
	m_pID_BUTTON_Minimize = (ControlButton*)theUiManager.FindControl( szFrameID, ID_BUTTON_Minimize );
	m_pChatInfoText = (ControlText*)theUiManager.FindControl( szFrameID, ID_TEXT_Char );
	m_pID_CHECKBOX_Save = (ControlCheckBox*)theUiManager.FindControl( szFrameID, ID_CHECKBOX_Save );
	m_pID_BUTTON_Clear = (ControlButton*)theUiManager.FindControl( szFrameID, ID_BUTTON_Clear );
	m_pID_BUTTON_face = (ControlButton*)theUiManager.FindControl( szFrameID, ID_BUTTON_face );
	m_pID_EDIT_INPUT = (ControlEdit*)theUiManager.FindControl( szFrameID, ID_EDIT_Input );
	m_pID_BUTTON_History = (ControlButton*)theUiManager.FindControl( szFrameID, ID_BUTTON_History );
	m_pID_BUTTON_Enter = (ControlButton*)theUiManager.FindControl( szFrameID, ID_BUTTON_Enter );
	m_pID_BUTTON_AddFriend = (ControlButton*)theUiManager.FindControl(szFrameID, ID_BUTTON_AddFriend);
	assert( m_pChatInfoBox );
	assert( m_pID_TEXT_Target );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_Minimize );
	assert( m_pChatInfoText );
	assert( m_pID_CHECKBOX_Save );
	assert( m_pID_BUTTON_Clear );
	assert( m_pID_BUTTON_face );
	assert( m_pID_EDIT_INPUT );
	assert( m_pID_BUTTON_History );
	assert( m_pID_BUTTON_Enter );
	assert( m_pID_BUTTON_AddFriend );

	m_pChatInfoBox->SetOnVisibleChangedFun(OnVisibleChange);

	InitialCommonChat();
	SetChatType( 0xffffffff );
	m_pID_EDIT_INPUT->SetForceNewLine( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Message_Chat::_UnLoadUI()
{
	m_pChatInfoBox = NULL;
	m_pID_TEXT_Target = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Minimize = NULL;
	m_pChatInfoText = NULL;
	m_pID_CHECKBOX_Save = NULL;
	m_pID_BUTTON_Clear = NULL;
	m_pID_BUTTON_face = NULL;
	m_pID_EDIT_INPUT = NULL;
	m_pID_BUTTON_History = NULL;
	m_pID_BUTTON_Enter = NULL;
	m_pID_BUTTON_AddFriend = NULL;
	return theUiManager.RemoveFrame( m_pObject );
}

bool CUI_ID_FRAME_Message_Chat::_IsVisable()
{
	if( !m_pChatInfoBox )
		return false;
	return m_pChatInfoBox->IsVisable();
}



// 设置是否可视
void CUI_ID_FRAME_Message_Chat::_SetVisable( const bool bVisable )
{
	if( !m_pChatInfoBox )
		return;
	m_pChatInfoBox->SetVisable( bVisable );
	if (bVisable)
	{
		theUiManager.ToTop(m_pChatInfoBox);
		SetEditFocus();
		Begin2Input();
		ChangeImmPos();
	}
	else
	{
		MessageInfoMgr::Instance()->SaveChatMessage(m_szPrivateToName.c_str());
		g_bMessageChat = false;
		ImmAssociateContext( g_hWnd, NULL );
	}
}

void CUI_ID_FRAME_Message_Chat::RefreshChatMessage()
{
	m_pChatInfoText->Clear();
	std::vector<MessageInfoMgr::MessageInfo*>* pList = &MessageInfoMgr::Instance()->GetInfoList(m_szPrivateToName.c_str())->messageList;
	if (pList)
	{
		for(std::vector<MessageInfoMgr::MessageInfo*>::iterator iter = pList->begin(); iter != pList->end();++iter)
		{
			MessageInfoMgr::MessageInfo* pInfo = *iter;
			D3DCOLOR NameCol = Color_Config.getColor(CC_MessageSelfName);
			D3DCOLOR WordCol = Color_Config.getColor(CC_MessageSelfWord);
			std::wstring wstrText = Common::_tstring::toWideString( pInfo->text.c_str() );
			if (pInfo->IsToMe)
			{
				NameCol = Color_Config.getColor(CC_MessageOtherName);
				WordCol = Color_Config.getColor(CC_MessageOtherWord);
			}
			std::string strNameAndDate;
			if (pInfo->IsToMe)
			{
				strNameAndDate = m_szPrivateToName;
			}
			else
			{
				strNameAndDate = thePlayerRole.GetName();
			}
// 			int npos = wstrText.find(Common::_tstring::toWideString( theXmlString.GetString(eClient_Chat_Begin) ) );
// 			std::string strNameAndDate =Common::_tstring::toNarrowString(wstrText.substr(0,npos).c_str());
			int nNameLength = strNameAndDate.length();
			for (int x = 0; x < 15 - nNameLength;++x)
			{
				strNameAndDate += ' ';
			}
			strNameAndDate += pInfo->GetTimeRecord();
			ShowTextInChatList(strNameAndDate.c_str(),NameCol);
			std::string temp = pInfo->text;//Common::_tstring::toNarrowString(wstrText.substr(npos + 1).c_str());
			ExpressionManager::GetInstance().AddExpressionAni(temp,3);
			ShowTextInChatList(temp.c_str(),WordCol,MsgChat::CHAT_TYPE_NORMAL,NULL,(char*)pInfo->items,pInfo->cntHyber);

		}
	}
	m_pChatInfoText->ScrollToTheLast();
}

void CUI_ID_FRAME_Message_Chat::SendMessage( const char* szData )
{
	if(CChatCheck::getInstance()->CheckStringInForbit(szData))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, theXmlString.GetString(eText_FilterCharInfo) );
		m_pID_EDIT_INPUT->SetText(""); 
		return;
	}
	int nChannel = MsgChat::CHAT_TYPE_MS;
	/*if (thePlayerRole.IsFriend(m_szPrivateToName.c_str()))
	{
		nChannel = MsgChat::CHAT_TYPE_PRIVATE;
	}*/
	string str = m_szPrivateToName;
	str += " ";
	str +=	szData;
	if( szData && strlen(szData) > 0 )
		SendChatMessage(nChannel,str.c_str());
}

void CUI_ID_FRAME_Message_Chat::SetSaveMessageStatus( bool isSaved )
{
	m_pID_CHECKBOX_Save->SetCheck(isSaved);
}

void CUI_ID_FRAME_Message_Chat::AddMyChatHistories( const char* szData )
{
	if (szData != NULL && szData[0] != '\0')
	{
		const char * pFind = strstr(szData," ");
		ChatHistory chis;
		chis.chatInfo = &pFind[1];
		for(int i = 0; i < ItemHyberCnt; ++i)
		{
			chis.hyberItemInfos.push_back(_HyberItemInfo[i]);
			chis.hyberItemIds.push_back(_HyberItemId[i]);
		}
		chis.nAddressHyberCnt = nAddressHyberCnt;
		chatHistories_.push_front(chis);

		if (chatHistories_.size() > LAST_INFO_MAX)
			chatHistories_.pop_back();

	}
}

void CUI_ID_FRAME_Message_Chat::Clear()
{
    if( !m_pChatInfoBox )
        return;

	m_pChatInfoText->Clear();
	m_bNeedMoveDown = true;
}
