/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ChatMessageMgr.cpp
* Create: 	10/14/06
* Desc:		地图类
* Author:	yuanding
*
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "GameMain.h"
#include "ChatMessageMgr.h"
#include "Player.h"
#include "PlayerMgr.h"
// #include "WorldMapCfg.h"
#include "ItemDetail.h"
#include "ShowScreenText.h"
#include "PlayerRole.h"
#include "Message_Chat.h"
#include "Meui/ExpressionManager.h"
#include "XmlStringLanguage.h"
//#include "Chat_Tips.h"		//deleted by zhuomeng.hu		[9/14/2010]
#include "color_config.h"
#include "core/Name.h"
#include "MiniChat.h"
#include "GameSetting.h"
// #include "Tinyxml/tinyxml.h"
#include "UserData.h"
#include "Common.h"
#include "InfoTips.h"		//added by zhuomeng.hu		[9/14/2010]

extern CHeroGame* theApp;
extern CPlayerRole thePlayerRole;
ChatMessageMgr chatMessageManage;
ChatMessageMgr::ChatMessageMgr()
{
	Reset();
}

ChatMessageMgr::~ChatMessageMgr()
{
	Reset();
}

void ChatMessageMgr::Reset()
{
	for (int i = 0; i < mMessageFrameArr.size();++i)
	{
		mMessageFrameArr[i]->UnLoadUI();
		delete mMessageFrameArr[i];
	}
	mMessageFrameArr.clear();
	m_ActiveIndex = -1;
	g_bMessageChat = false;
}

bool ChatMessageMgr::OnFrameRunIndexedFrame( int index )
{
	assert(mMessageFrameArr.size() > index);
	return mMessageFrameArr[index]->OnFrameRun();
}

bool ChatMessageMgr::OnFrameRenderIndexedFrame( int index )
{
	assert(mMessageFrameArr.size() > index);
	return mMessageFrameArr[index]->OnFrameRender();

}

bool ChatMessageMgr::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);
	return mMessageFrameArr[m_ActiveIndex]->ID_BUTTON_CLOSEOnButtonClick(pSender);

}

bool ChatMessageMgr::ID_BUTTON_MinimizeOnButtonClick( ControlObject* pSender )
{
	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);
	return mMessageFrameArr[m_ActiveIndex]->ID_BUTTON_MinimizeOnButtonClick(pSender);
}

// void ChatMessageMgr::ID_LIST_CharOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
// {
// 	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);
// 	mMessageFrameArr[m_ActiveIndex]->ID_LIST_CharOnListSelectChange(pSender,pItem);
// }

void ChatMessageMgr::ID_CHECKBOX_SaveOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);
	mMessageFrameArr[m_ActiveIndex]->ID_CHECKBOX_SaveOnCheckBoxCheck(pSender,pbChecked);

}

bool ChatMessageMgr::ID_BUTTON_ClearOnButtonClick( ControlObject* pSender )
{
	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);
	return mMessageFrameArr[m_ActiveIndex]->ID_BUTTON_ClearOnButtonClick(pSender);

}

bool ChatMessageMgr::ID_BUTTON_faceOnButtonClick( ControlObject* pSender )
{
	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);
	return mMessageFrameArr[m_ActiveIndex]->ID_BUTTON_faceOnButtonClick(pSender);

}

void ChatMessageMgr::ID_EDIT_INPUTOnEditEnter( ControlObject* pSender, const char* szData )
{
	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);
	mMessageFrameArr[m_ActiveIndex]->ID_EDIT_INPUTOnEditEnter(pSender,szData);

}

bool ChatMessageMgr::ID_BUTTON_HistoryOnButtonClick( ControlObject* pSender )
{
	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);
	return mMessageFrameArr[m_ActiveIndex]->ID_BUTTON_HistoryOnButtonClick(pSender);

}

bool ChatMessageMgr::ID_BUTTON_EnterOnButtonClick( ControlObject* pSender )
{
	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);
	return mMessageFrameArr[m_ActiveIndex]->ID_BUTTON_EnterOnButtonClick(pSender);

}

bool ChatMessageMgr::ID_BUTTON_AddFriendOnButtonClick( ControlObject* pSender )
{
	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);
	return mMessageFrameArr[m_ActiveIndex]->ID_BUTTON_AddFriendOnButtonClick(pSender);
}

int ChatMessageMgr::GetFrameIndexByChildWidget( ControlObject* pSender )
{
	ControlObject* pFrame = pSender;
	while(pFrame->GetControlType() != Type_Frame)
	{
		pFrame = pFrame->GetFather();
	}
	assert(pFrame);
	g_bMessageChat = true;
	ControlFrame* pConFrame = (ControlFrame*) pFrame;
	return pConFrame->GetIndex();
}

CUI_ID_FRAME_Message_Chat* ChatMessageMgr::GetActiveMessageFrame()
{
	if (m_ActiveIndex < 0 || m_ActiveIndex > mMessageFrameArr.size())
	{
		return NULL;
	}
	return mMessageFrameArr[m_ActiveIndex];
}

void ChatMessageMgr::ShowChatMessageFrame( const char* pPlayerName )
{
	if (pPlayerName == NULL || pPlayerName[0] == '\0')
	{
		return;
	}
	CUI_ID_FRAME_Message_Chat* pChat = NULL;
	for (int i = 0; i < mMessageFrameArr.size(); ++i)
	{
		if (mMessageFrameArr[i]->m_szPrivateToName == pPlayerName)
		{
			pChat = mMessageFrameArr[i];
			m_ActiveIndex = i;
			break;
		}
	}
	if (pChat == NULL)
	{
		for (int i = 0; i < mMessageFrameArr.size(); ++i)
		{
			if (!mMessageFrameArr[i]->IsVisable())
			{
				pChat = mMessageFrameArr[i];
				m_ActiveIndex = i;
				break;
			}
		}		
		if (pChat == NULL)
		{
			int nIndex = mMessageFrameArr.size();
			pChat = MeNew CUI_ID_FRAME_Message_Chat(nIndex);
			pChat->LoadUI();
			if (0 == nIndex)
			{
				m_defaultRect = pChat->GetRealRect(); 
			}
			else
			{
				int x = m_defaultRect.left + (nIndex%10 + nIndex/10)*10;
				int y = m_defaultRect.top  + (nIndex%10)*10;
				pChat->SetPos(x,y);
			}
			m_ActiveIndex = nIndex;
			pChat->SetSaveMessageStatus(MessageInfoMgr::Instance()->IsNeedSave());
			mMessageFrameArr.push_back(pChat);
		}

		if (strcmp(pPlayerName, thePlayerRole.GetName()) != 0)
			pChat->m_szPrivateToName = pPlayerName;

        char text[MAX_PATH] = {0};
        sprintf(text, theXmlString.GetString(eText_TalkToPlayer), pPlayerName);
		pChat->m_pID_TEXT_Target->SetText(text);
		pChat->RefreshChatMessage();
	}
	pChat->SetVisable(true);
	//s_CUI_ID_FRAME_Chat_Tips.RemoveRemindPlayer(pPlayerName);		//deleted by zhuomeng.hu		[9/14/2010]
	s_CUI_ID_FRAME_MiniChat.RemoveRemindPlayer(pPlayerName);
}

bool ChatMessageMgr::AddChatMessage( const char* pPlayerName,const std::string& str, const D3DCOLOR col , const UINT nType , char *szToName , 
									char* itemData , int cntHyber, int nBagType /*= BT_All*/  )
{
	CUI_ID_FRAME_Message_Chat* pChat = NULL;
	bool isToMe = false;
	if ( theApp->GetPlayerMgr()->GetMe() && 
		Common::_tstring::toWideString( theApp->GetPlayerMgr()->GetMe()->GetName() ) == 
		Common::_tstring::toWideString( szToName ) )
		isToMe = true;

	std::string chatName;
	D3DCOLOR NameCol = Color_Config.getColor(CC_MessageSelfName);
	D3DCOLOR WordCol = Color_Config.getColor(CC_MessageSelfWord);
	if (isToMe)
	{
		chatName = pPlayerName;
		NameCol = Color_Config.getColor(CC_MessageOtherName);
		WordCol = Color_Config.getColor(CC_MessageOtherWord);
	}
	else
	{
		chatName = szToName;
	}

// 	std::string localStr = pPlayerName;
// 	localStr += ' ';
// 	localStr += str;
// 	std::wstring wstr = Common::_tstring::toWideString( str.c_str() );
// 	int nBeginPos = wstr.find( Common::_tstring::toWideString ( theXmlString.GetString(eClient_Chat_Begin) ), 0);
// 	if (nBeginPos >0)
// 	{
// 		localStr += Common::_tstring::toNarrowString( (wchar_t*)&wstr.c_str()[nBeginPos] );
// 	}
	MessageInfoMgr::MessageInfo* pHisInfo = MessageInfoMgr::Instance()->AddInfoMap(chatName.c_str(),isToMe,str.c_str(),cntHyber,itemData);
	for (int i = 0; i < mMessageFrameArr.size(); ++i)
	{		
		if ((mMessageFrameArr[i]->m_szPrivateToName == szToName || mMessageFrameArr[i]->m_szPrivateToName == pPlayerName))
		{
			pChat = mMessageFrameArr[i];
			m_ActiveIndex = i;
			std::string strNameAndDate = pPlayerName;
			int nNameLength = strNameAndDate.length();
			for (int x = 0; x < 15 - nNameLength;++x)
			{
				strNameAndDate += ' ';
			}
			strNameAndDate += pHisInfo->GetTimeRecord();
			pChat->ShowTextInChatList(strNameAndDate.c_str(),NameCol);
// 			localStr = Common::_tstring::toNarrowString( (wchar_t*)&wstr.c_str()[nBeginPos + 1] );
			std::string localStr = str;
			ExpressionManager::GetInstance().AddExpressionAni(localStr,3);
			pChat->ShowTextInChatList(localStr.c_str(),WordCol,nType,szToName,itemData,cntHyber, nBagType);
			break;
		}
	}
	if (pChat && pChat->IsVisable())
	{
		return true;
	}
	if (isToMe )
	{//别人对我说的消息才会闪烁提醒
		if (s_CUI_ID_FRAME_MiniChat.IsMiniChatPlayer(pPlayerName))
		{
			s_CUI_ID_FRAME_MiniChat.AddRemindPlayer(pPlayerName);
		}
		else if (MsgChat::CHAT_TYPE_MS == nType)
		{
			//modified by zhuomeng.hu		[9/14/2010]
			//s_CUI_ID_FRAME_Chat_Tips.AddRemindPlayer(pPlayerName,localStr.c_str());
			//s_CUI_ID_FRAME_Chat_Tips.SetRemindVisable(true);
			s_CUI_ID_FRAME_InfoTips.AddMiniChatTip( std::string( pPlayerName ) );
		}

	}

	return false;
}

BOOL ChatMessageMgr::EditInputIsVisable()
{
	for (int i = 0; i < mMessageFrameArr.size(); ++i)
	{
		if (mMessageFrameArr[i]->EditInputIsVisable())
		{
			g_bMessageChat = true;
			m_ActiveIndex = i;
			return TRUE;
		}
	}
	return FALSE;
}

void ChatMessageMgr::RefreshSaveMessageCheckBox()
{
	for (int i = 0; i < mMessageFrameArr.size(); ++i)
	{
		mMessageFrameArr[i]->SetSaveMessageStatus(MessageInfoMgr::Instance()->IsNeedSave());
	}
}

void ChatMessageMgr::Hide()
{
	for (int i = 0; i < mMessageFrameArr.size(); ++i)
	{
		mMessageFrameArr[i]->SetVisable(false);
	}

}

void ChatMessageMgr::Clear()
{
	for (int i = 0; i < mMessageFrameArr.size(); ++i)
	{
		mMessageFrameArr[i]->Clear();

		// 每次清理的时候，重置下所有的FreeTip
		mMessageFrameArr[i]->ResetAllFreeTip();
	}
	//s_CUI_ID_FRAME_Chat_Tips.Clear();
	s_CUI_ID_FRAME_MiniChat.Clear();
	MessageInfoMgr::Instance()->Reset();

}

void ChatMessageMgr::Refresh()
{
	for (int i = 0; i < mMessageFrameArr.size(); ++i)
	{
		if (!mMessageFrameArr[i]->IsVisable())
		{
			mMessageFrameArr[i]->RefreshChatMessage();
			break;
		}
	}		

}

void ChatMessageMgr::SetActiveChatFrameByEdit( ControlEdit* pID_EDIT_INPUT )
{
	m_ActiveIndex = GetFrameIndexByChildWidget(pID_EDIT_INPUT);
}

bool ChatMessageMgr::IsPtInCloseBtn( int nMouseX, int nMouseY )
{
	//for (int i = 0; i < mMessageFrameArr.size(); ++i)
	//{
	//	/*if (mMessageFrameArr[i]->m_FreeTip.PtInCloseBtn(nMouseX,nMouseY))
	//	{
	//		mMessageFrameArr[i]->m_FreeTip.ShowItemTip( false );
	//		return true;
	//	}*/

	//	// ======================================================
	//	// newADD 这里可能有问题，暂时先抄原来的逻辑
	///*	for ( int idx = 0; idx < MAX_FREETIP_COUNT; ++idx )
	//	{
	//		if ( mMessageFrameArr[i]->m_AllFreeTip[idx].PtInCloseBtn( nMouseX, nMouseY ) )
	//		{
	//			mMessageFrameArr[i]->m_AllFreeTip[idx].ShowItemTip( false );
	//		}
	//	}*/
	//	return true;
	//}

	return false;
}

MessageInfoMgr::MessageInfo* MessageInfoMgr::AddInfoMap( const char* pPlayerName,bool isToMe,const char* pInfo,int cntHyber /*= 0*/,char* itemData /*= NULL*/ )
{

	InfoList* pList = NULL;
	std::map<std::string, InfoList*>::iterator iter = m_InfoMap.find(pPlayerName);
	if (iter == m_InfoMap.end())
	{
		pList = MeNew InfoList;
		m_InfoMap.insert(make_pair(pPlayerName,pList));
	}
	else
	{
		pList = (*iter).second;
	}
	MessageInfo * pNewInfo = MeNew MessageInfo;
	pNewInfo->IsToMe = isToMe;
	pNewInfo->text = pInfo;
	GetLocalTime(&pNewInfo->time);
	pNewInfo->cntHyber = cntHyber;
	if (cntHyber > 0)
	{
		SCharItem* pItem = (SCharItem*)itemData;
		pNewInfo->items = new SCharItem[cntHyber];
		for (int i = 0 ; i < cntHyber;++i)
		{
			pNewInfo->items[i] = pItem[i];
		}
	}
	pList->messageList.push_back(pNewInfo);
	return pNewInfo;
}

MessageInfoMgr::~MessageInfoMgr()
{
	Reset();
}

MessageInfoMgr::InfoList* MessageInfoMgr::GetInfoList( const char* pPlayerName )
{
	std::map<std::string, InfoList*>::iterator iter = m_InfoMap.find(pPlayerName);
	if (iter != m_InfoMap.end())
	{
		return (*iter).second;
	}
	return NULL;
}

bool MessageInfoMgr::IsNeedSave()
{
	return GameSetting::Instance()->GetLevel(GameSetting::eGSC_SAVECHATMESSAGE) ==0 ? false:true;
}

void MessageInfoMgr::SaveChatMessage( const char* pPlayerName )
{
	if (!IsNeedSave())
	{
		return; 
	}
	InfoList* pInfoList = GetInfoList(pPlayerName);
	SaveInfoList(pInfoList,pPlayerName);
	return;
}

MessageInfoMgr::MessageInfoMgr()
{
	char saveFileName[MAX_PATH] = {0};
	MeSprintf_s(saveFileName,sizeof(saveFileName)/sizeof(char) - 1,"%s\\MessageHistory",CUserData::Instance()->GetUserDataPath());
// 	sprintf(saveFileName,"%s\\MessageHistory",GetRootPath());
	WIN32_FIND_DATAA data;
	HANDLE hFind = FindFirstFileA(saveFileName,&data);
	bool bFind = (hFind != INVALID_HANDLE_VALUE);
	if (!bFind)
	{
		CreateDirectoryA(saveFileName,NULL);
	}

}

void MessageInfoMgr::SaveInfoList( InfoList* pInfoList ,const char* pPlayerName)
{
	if (!IsNeedSave())
	{
		return; 
	}
	if (!pInfoList || pInfoList->mSavedIndex == pInfoList->messageList.size())
	{
		return;
	}
	char saveFileName[MAX_PATH] = {0};
 	MeSprintf_s(saveFileName,sizeof(saveFileName)/sizeof(char) - 1,"%s\\MessageHistory\\%s.txt",CUserData::Instance()->GetUserDataPath(),pPlayerName);
// 	sprintf(saveFileName,"%s\\MessageHistory\\%s.txt",GetRootPath(),pPlayerName);
	FILE* fileHandle = fopen(saveFileName,"a+t");
	if (fileHandle == NULL)
	{
		assert(0);
		return;
	}
	for (int i = pInfoList->mSavedIndex; i < pInfoList->messageList.size(); ++i)
	{
		MessageInfo* pInfo = pInfoList->messageList[i];
		const char* timeStr = pInfo->GetDateTimeRecord();
		fwrite(timeStr,sizeof(char),strlen(timeStr),fileHandle);
		

// 		std::wstring wsText = Common::_tstring::toWideString(pInfo->text.c_str());
// 		std::wstring wsChatBegin = Common::_tstring::toWideString(theXmlString.GetString(eClient_Chat_Begin));
// 		int nColonPos = wsText.find(wsChatBegin, 0);
// 		wsText = wsText.substr(nColonPos + wsChatBegin.length());
// 		std::string strContent = Common::_tstring::toNarrowString(wsText.c_str());
		char cIsToMe_ContentLength[8];
// 		int nColonPos = pInfo->text.find(theXmlString.GetString(eClient_Chat_Begin), 0);
		sprintf(cIsToMe_ContentLength," %d %d ",pInfo->IsToMe,pInfo->text.length());
		fwrite(cIsToMe_ContentLength,sizeof(char),strlen(cIsToMe_ContentLength),fileHandle);

		fwrite(pInfo->text.c_str(),sizeof(char),pInfo->text.size(),fileHandle);
		fwrite("\n",sizeof(char),1,fileHandle);
	}
	pInfoList->mSavedIndex = pInfoList->messageList.size();
	fclose(fileHandle);
}


void MessageInfoMgr::Reset()
{
	std::map<std::string, InfoList*>::iterator iter = m_InfoMap.begin();
	while (iter != m_InfoMap.end())
	{
		InfoList* pList = (*iter).second;
		SaveInfoList(pList,(*iter).first.c_str());
		pList->Reset();
		delete pList;
		++iter;
	}
	m_InfoMap.clear();
}

MessageInfoMgr::MessageInfo::~MessageInfo()
{
	if (cntHyber > 0)
	{
		delete [] items;
	}

}

const char* MessageInfoMgr::MessageInfo::GetDateTimeRecord()
{
	static char localStr[MAX_PATH] = {0};
	sprintf(localStr,"%4d-%2d-%2d,%2d:%2d:%2d",time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond);
	int length = strlen(localStr);
	for (int i = 0 ; i < length; ++i)
	{
		if (localStr[i] == ' ')
		{
			localStr[i] = '0';
		}
	}
	return localStr;
}

const char* MessageInfoMgr::MessageInfo::GetTimeRecord()
{
	static char localStr[MAX_PATH] = {0};
	sprintf(localStr,"%2d:%2d:%2d",time.wHour,time.wMinute,time.wSecond);
	int length = strlen(localStr);
	for (int i = 0 ; i < length; ++i)
	{
		if (localStr[i] == ' ')
		{
			localStr[i] = '0';
		}
	}
	return localStr;

}
void MessageInfoMgr::InfoList::Reset()
{
	for (int i = 0; i < messageList.size(); ++i)
	{
		delete messageList[i];
	}
	messageList.clear();
	mSavedIndex = 0;
}