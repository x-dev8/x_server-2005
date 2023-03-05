/********************************************************************
Created by UIEditor.exe
FileName: E:\temp\ChatHistory.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ChatHistory.h"
#include "UIMgr.h"
#include "ChatMessageMgr.h"
//#include "FriendDlg.h"
#include "UserData.h"
#include "tstring.h"
#include "color_config.h"
#include "MeUi/ExpressionManager.h"
#include "XmlStringLanguage.h"
#include "MessageBox.h"
#include "PlayerRole.h"
#include "Common.h"

const int CHAT_NUMBER_PER_PAGE = 10;
// #include "MeTerrain/MapUtil.h"
typedef bool (*swFileOperation)(LPCTSTR strPath,void* point);
extern bool	EnumFile(LPCTSTR strPath,swFileOperation opt,void* point,bool isRecursive);

const char* s_SearchType[CUI_ID_FRAME_ChatHistory::SearchTypeTotal] =
{
	"名字",
	"内容"
};

CUI_ID_FRAME_ChatHistory s_CUI_ID_FRAME_ChatHistory;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ChatHistory, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ChatHistory, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChatHistory, ID_BUTTON_CLOSEOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChatHistory, ID_BUTTON_helpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChatHistory, ID_BUTTON_ExitOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ChatHistory, ID_LIST_FriendNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ChatHistory, ID_LIST_ChatListOnListSelectChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChatHistory, ID_CHECKBOX_FriendOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChatHistory, ID_CHECKBOX_StrangerOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChatHistory, ID_BUTTON_DeleteOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChatHistory, ID_BUTTON_LastPageOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChatHistory, ID_BUTTON_FirstPageOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChatHistory, ID_BUTTON_PageDownOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChatHistory, ID_BUTTON_PageUpOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_ChatHistory, ID_EDIT_SearchOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChatHistory, ID_BUTTON_NextOnButtonClick )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_ChatHistory, ID_COMBOBOX_SearchOnComboBoxChange )
CUI_ID_FRAME_ChatHistory::CUI_ID_FRAME_ChatHistory()
{
	// Member
	m_pID_FRAME_ChatHistory = NULL;
// 	m_pID_PICTURE_Di = NULL;
// 	m_pID_PICTURE_TitleDi = NULL;
// 	m_pID_PICTURE_title = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	//m_pID_BUTTON_help = NULL;
	// 	m_pID_BUTTON_Exit = NULL;
	//m_pID_TEXT_Title = NULL;
	m_pID_LIST_FriendName = NULL;
	m_pID_LIST_ChatList = NULL;
	// 	m_pID_TEXT_ChatPlayer = NULL;
	// 	m_pID_TEXT_ChatTime = NULL;
	// 	m_pID_TEXT_Detail = NULL;
	m_pID_CHECKBOX_Friend = NULL;
	m_pID_CHECKBOX_Stranger = NULL;
	// 	m_pID_TEXT_Chat2 = NULL;
	m_pID_BUTTON_Delete = NULL;
	// 	m_pID_TEXT_Chat = NULL;
	m_pID_BUTTON_LastPage = NULL;
	m_pID_BUTTON_FirstPage = NULL;
	m_pID_BUTTON_PageDown = NULL;
	m_pID_BUTTON_PageUp = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_EDIT_Search = NULL;
	m_pID_BUTTON_Next = NULL;
	m_pID_COMBOBOX_Search = NULL;

	m_currChatIndex = -1;
	m_SearchType = ChatContent;
	m_lastSearchIndex = -1;
}
// Frame
bool CUI_ID_FRAME_ChatHistory::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_ChatHistory::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_ChatHistory::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);

	return true;
}
// Button
// bool CUI_ID_FRAME_ChatHistory::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	return true;
// }
// Button
bool CUI_ID_FRAME_ChatHistory::ID_BUTTON_ExitOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);

	return true;
}
// List
void CUI_ID_FRAME_ChatHistory::ID_LIST_FriendNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_ChatHistory)
	{
		assert(false&&"ui error");
		return ;
	}

	int nSel = m_pID_LIST_FriendName->GetCurSelIndex();
	std::vector<std::string>* nameList = &m_goodFriendList;
	if (m_pID_CHECKBOX_Stranger->IsChecked())
	{
		nameList = &m_otherFriendList;
	}
	assert(nSel < nameList->size());
	m_currFriendName = (*nameList)[nSel];
	RefreshChatList();
}
// List
void CUI_ID_FRAME_ChatHistory::ID_LIST_ChatListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	// 		m_pID_TEXT_Chat->SetText(m_oldChatVec[m_pID_LIST_ChatList->GetCurSelIndex()].chatContent);
}
// CheckBox
void CUI_ID_FRAME_ChatHistory::ID_CHECKBOX_FriendOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_ChatHistory)
	{
		assert(false&&"ui error");
		return ;
	}

	int nCount = 0;
	RefreshFriendListUI(true);
	for (std::vector<std::string>::iterator iter = m_goodFriendList.begin(); iter != m_goodFriendList.end(); ++iter,++nCount)
	{
		if ((*iter) == m_currFriendName )
		{
			break;
		}

	}
	if (nCount < m_goodFriendList.size())
	{//Found
		m_pID_LIST_FriendName->SetCurSelIndex(nCount);
	}
	else
	{
		m_pID_LIST_FriendName->SetCurSelIndex(-1);
	}


}
// CheckBox
void CUI_ID_FRAME_ChatHistory::ID_CHECKBOX_StrangerOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_ChatHistory)
	{
		assert(false&&"ui error");
		return ;
	}

	int nCount = 0;
	RefreshFriendListUI(false);
	for (std::vector<std::string>::iterator iter = m_otherFriendList.begin(); iter != m_otherFriendList.end(); ++iter,++nCount)
	{
		if ((*iter) == m_currFriendName )
		{
			break;
		}

	}
	if (nCount < m_otherFriendList.size())
	{//Found
		m_pID_LIST_FriendName->SetCurSelIndex(nCount);
	}
	else
	{
		m_pID_LIST_FriendName->SetCurSelIndex(-1);
	}
}
// Button
bool CUI_ID_FRAME_ChatHistory::ID_BUTTON_DeleteOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_ChatHistory::ID_BUTTON_LastPageOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ChatHistory)
	{
		assert(false&&"ui error");
		return false;
	}

	if (m_oldChatVec.size() > 0)
	{
		int nIndex = ((m_oldChatVec.size() - 1)/CHAT_NUMBER_PER_PAGE)*CHAT_NUMBER_PER_PAGE;
		SetCurrChatIndex(nIndex);
	}
	return true;
}
// Button

bool CUI_ID_FRAME_ChatHistory::ID_BUTTON_FirstPageOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ChatHistory)
	{
		assert(false&&"ui error");
		return false;
	}

	SetCurrChatIndex(0);
	return true;
}
// Button
bool CUI_ID_FRAME_ChatHistory::ID_BUTTON_PageDownOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ChatHistory)
	{
		assert(false&&"ui error");
		return false;
	}

	SetCurrChatIndex(m_currChatIndex + CHAT_NUMBER_PER_PAGE);
	return true;
}
// Button
bool CUI_ID_FRAME_ChatHistory::ID_BUTTON_PageUpOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ChatHistory)
	{
		assert(false&&"ui error");
		return false;
	}

	int nIndex = (m_currChatIndex - CHAT_NUMBER_PER_PAGE);
	SetCurrChatIndex(nIndex);
	return true;
}
// Edit
void CUI_ID_FRAME_ChatHistory::ID_EDIT_SearchOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_ChatHistory)
	{
		assert(false&&"ui error");
		return ;
	}
	DoSearch();
}
// Button
bool CUI_ID_FRAME_ChatHistory::ID_BUTTON_NextOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ChatHistory)
	{
		assert(false&&"ui error");
		return false;
	}

	DoSearch();
	return true;
}
// ComboBox
void CUI_ID_FRAME_ChatHistory::ID_COMBOBOX_SearchOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_ChatHistory)
	{
		assert(false&&"ui error");
		return ;
	}

	for (int i = 0; i < SearchTypeTotal; ++i)
	{
		if(strcmp(szData,s_SearchType[i]) == 0)
		{
			m_SearchType = (eSearchType)i;
			return;
		}
	}
}

// 装载UI
bool CUI_ID_FRAME_ChatHistory::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ChatHistory.MEUI" ,false,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ChatHistory.MEUI]失败")
			return false;
	}
	// 		else if ( dwResult != 1/*文件版本号*/ )
	// 		{
	// 			MESSAGE_BOX("读取文件[Data\\UI\\ChatHistory.MEUI]与源代码版本不一样")
	// 		}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ChatHistory::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ChatHistory, s_CUI_ID_FRAME_ChatHistoryOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ChatHistory, s_CUI_ID_FRAME_ChatHistoryOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ChatHistory, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_ChatHistoryID_BUTTON_CLOSEOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_ChatHistory, ID_BUTTON_help, s_CUI_ID_FRAME_ChatHistoryID_BUTTON_helpOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_ChatHistory, ID_BUTTON_Exit, s_CUI_ID_FRAME_ChatHistoryID_BUTTON_ExitOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_ChatHistory, ID_LIST_FriendName, s_CUI_ID_FRAME_ChatHistoryID_LIST_FriendNameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_ChatHistory, ID_LIST_ChatList, s_CUI_ID_FRAME_ChatHistoryID_LIST_ChatListOnListSelectChange );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChatHistory, ID_CHECKBOX_Friend, s_CUI_ID_FRAME_ChatHistoryID_CHECKBOX_FriendOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChatHistory, ID_CHECKBOX_Stranger, s_CUI_ID_FRAME_ChatHistoryID_CHECKBOX_StrangerOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_ChatHistory, ID_BUTTON_Delete, s_CUI_ID_FRAME_ChatHistoryID_BUTTON_DeleteOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ChatHistory, ID_BUTTON_LastPage, s_CUI_ID_FRAME_ChatHistoryID_BUTTON_LastPageOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ChatHistory, ID_BUTTON_FirstPage, s_CUI_ID_FRAME_ChatHistoryID_BUTTON_FirstPageOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ChatHistory, ID_BUTTON_PageDown, s_CUI_ID_FRAME_ChatHistoryID_BUTTON_PageDownOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ChatHistory, ID_BUTTON_PageUp, s_CUI_ID_FRAME_ChatHistoryID_BUTTON_PageUpOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_ChatHistory, ID_EDIT_Search, s_CUI_ID_FRAME_ChatHistoryID_EDIT_SearchOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_ChatHistory, ID_BUTTON_Next, s_CUI_ID_FRAME_ChatHistoryID_BUTTON_NextOnButtonClick );
	theUiManager.OnComboBoxChange( ID_FRAME_ChatHistory, ID_COMBOBOX_Search, s_CUI_ID_FRAME_ChatHistoryID_COMBOBOX_SearchOnComboBoxChange );

	m_pID_FRAME_ChatHistory = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ChatHistory );
// 	m_pID_PICTURE_Di = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_PICTURE_Di );
// 	m_pID_PICTURE_TitleDi = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_PICTURE_TitleDi );
// 	m_pID_PICTURE_title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_PICTURE_title );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_BUTTON_CLOSE );
// 	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_BUTTON_help );
// 	// 		m_pID_BUTTON_Exit = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_BUTTON_Exit );
// 	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_TEXT_Title );
	m_pID_LIST_FriendName = (ControlList*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_LIST_FriendName );
	m_pID_LIST_ChatList = (ControlList*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_LIST_ChatList );
	// 		m_pID_TEXT_ChatPlayer = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_TEXT_ChatPlayer );
	// 		m_pID_TEXT_ChatTime = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_TEXT_ChatTime );
	// 		m_pID_TEXT_Detail = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_TEXT_Detail );
	m_pID_CHECKBOX_Friend = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_CHECKBOX_Friend );
	m_pID_CHECKBOX_Stranger = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_CHECKBOX_Stranger );
	// 		m_pID_TEXT_Chat2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_TEXT_Chat2 );
	m_pID_BUTTON_Delete = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_BUTTON_Delete );
	// 		m_pID_TEXT_Chat = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_TEXT_Chat );
	m_pID_BUTTON_LastPage = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_BUTTON_LastPage );
	m_pID_BUTTON_FirstPage = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_BUTTON_FirstPage );
	m_pID_BUTTON_PageDown = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_BUTTON_PageDown );
	m_pID_BUTTON_PageUp = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_BUTTON_PageUp );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_TEXT_Page );
	m_pID_EDIT_Search = (ControlEdit*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_EDIT_Search );
	m_pID_BUTTON_Next = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_BUTTON_Next );
	m_pID_COMBOBOX_Search = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_ChatHistory, ID_COMBOBOX_Search );
// 	assert( m_pID_FRAME_ChatHistory );
// 	assert( m_pID_PICTURE_Di );
// 	assert( m_pID_PICTURE_TitleDi );
// 	assert( m_pID_PICTURE_title );
// 	assert( m_pID_BUTTON_CLOSE );
// 	assert( m_pID_BUTTON_help );
// 	// 		assert( m_pID_BUTTON_Exit );
// 	assert( m_pID_TEXT_Title );
// 	assert( m_pID_LIST_FriendName );
// 	assert( m_pID_LIST_ChatList );
// 	// 		assert( m_pID_TEXT_ChatPlayer );
// 	// 		assert( m_pID_TEXT_ChatTime );
// 	// 		assert( m_pID_TEXT_Detail );
// 	assert( m_pID_CHECKBOX_Friend );
// 	assert( m_pID_CHECKBOX_Stranger );
// 	// 		assert( m_pID_TEXT_Chat2 );
// 	assert( m_pID_BUTTON_Delete );
// 	// 		assert( m_pID_TEXT_Chat );
// 	assert( m_pID_BUTTON_LastPage );
// 	assert( m_pID_BUTTON_FirstPage );
// 	assert( m_pID_BUTTON_PageDown );
// 	assert( m_pID_BUTTON_PageUp );
// 	assert( m_pID_TEXT_Page );
// 	assert( m_pID_EDIT_Search );
// 	assert( m_pID_BUTTON_Next );
// 	assert( m_pID_COMBOBOX_Search );

	USE_SCRIPT( eUI_OBJECT_ChatHistory, this );

	SetVisable(false);
	m_pID_LIST_ChatList->SetMsgHoldup(false);	//不接受消息
	m_pID_LIST_ChatList->SetItemMaxCount( 100 );
	// 		m_pID_LIST_ChatList->HaveSelBar( false );	//没有绿色cur选中地图
	m_pID_LIST_ChatList->SetCurSelIndex(-1);

	ControlList::S_List stItem;
	for (int i = 0; i < SearchTypeTotal; ++i)
	{
		stItem.SetData( s_SearchType[i] );
		stItem.SetMargin( 5 );
		m_pID_COMBOBOX_Search->GetListBox().AddItem( &stItem,NULL, false);
	}
	m_pID_COMBOBOX_Search->GetEditInput().SetText(s_SearchType[m_SearchType]);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ChatHistory::_UnLoadUI()
{
	CLOSE_SCRIPT( eUI_OBJECT_ChatHistory );
	m_pID_FRAME_ChatHistory = NULL;
//	m_pID_PICTURE_Di = NULL;
	//m_pID_PICTURE_TitleDi = NULL;
	//m_pID_PICTURE_title = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	//m_pID_BUTTON_help = NULL;
	// 	m_pID_BUTTON_Exit = NULL;
	//m_pID_TEXT_Title = NULL;
	m_pID_LIST_FriendName = NULL;
	m_pID_LIST_ChatList = NULL;
	// 	m_pID_TEXT_ChatPlayer = NULL;
	// 	m_pID_TEXT_ChatTime = NULL;
	// 	m_pID_TEXT_Detail = NULL;
	m_pID_CHECKBOX_Friend = NULL;
	m_pID_CHECKBOX_Stranger = NULL;
	// 	m_pID_TEXT_Chat2 = NULL;
	m_pID_BUTTON_Delete = NULL;
	// 	m_pID_TEXT_Chat = NULL;
	m_pID_BUTTON_LastPage = NULL;
	m_pID_BUTTON_FirstPage = NULL;
	m_pID_BUTTON_PageDown = NULL;
	m_pID_BUTTON_PageUp = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_EDIT_Search = NULL;
	m_pID_BUTTON_Next = NULL;
	m_pID_COMBOBOX_Search = NULL;

	return theUiManager.RemoveFrame( "Data\\UI\\ChatHistory.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_ChatHistory::_IsVisable()
{
    if(!m_pID_FRAME_ChatHistory)
        return false;

	return m_pID_FRAME_ChatHistory->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ChatHistory::_SetVisable( const bool bVisable )
{
    if(!m_pID_FRAME_ChatHistory)
        return ;

	if (bVisable)
	{
		theUiManager.ToTop( m_pID_FRAME_ChatHistory );
		RefreshPageButtonStatus();
	}
	m_pID_FRAME_ChatHistory->SetVisable( bVisable );
}

void CUI_ID_FRAME_ChatHistory::ShowHistoryChat( const char* pPlayer )
{

	SetVisable(true);
	if (pPlayer)
	{
		m_currFriendName = pPlayer;
	}
	else
	{
		m_currFriendName.clear();
	}
	{
		RefreshFriendName();
	}
	bool bFound = false;
	if (pPlayer)
	{
		for (std::vector<std::string>::iterator iter = m_goodFriendList.begin(); iter != m_goodFriendList.end(); ++iter)
		{
			if ((*iter) == pPlayer )
			{
				bFound = true;
				RefreshFriendListUI(true);
				break;
			}

		}
		if (!bFound)
		{
			for (std::vector<std::string>::iterator iter = m_otherFriendList.begin(); iter != m_otherFriendList.end(); ++iter)
			{
				if ((*iter) == pPlayer )
				{
					bFound = true;
					RefreshFriendListUI(false);
					break;
				}

			}
		}
		if (!bFound)
		{
			m_otherFriendList.push_back(pPlayer);
		}
	}


	if (!bFound)
	{
		RefreshFriendListUI(false);
	}


}
void RetriveFileName( LPCTSTR strPath,void* point )
{
	const char* pos  =  strstr( strPath, _T(".txt")); 
	if(!pos ||  (strlen(strPath) - 4 != pos - strPath )) 
	{
		return;
	}
	int slashPos = pos - strPath;
	while(strPath[slashPos]!= '\\' && strPath[slashPos]!= '/')
	{
		--slashPos;
		if (slashPos == 0)
		{
			assert(0);
			return;
		}
	}
	std::string playerName = &strPath[slashPos + 1];
	playerName.erase(playerName.begin() + (pos - &strPath[slashPos + 1]),playerName.end());
// 	bool bFound = 0;
	for (std::vector<std::string>::iterator iter = s_CUI_ID_FRAME_ChatHistory.m_goodFriendList.begin(); iter != s_CUI_ID_FRAME_ChatHistory.m_goodFriendList.end(); ++iter)
	{
		if (*iter == playerName)
		{
			return;
		}			
	}
	s_CUI_ID_FRAME_ChatHistory.m_otherFriendList.push_back(playerName);
	// 		int playerId = s_CUI_ID_FRAME_Friend.GetFriendID(playerName.c_str());
	// 		if (playerId != 0)
	// 		{
	// 			s_CUI_ID_FRAME_ChatHistory.m_goodFriendList.push_back(playerName);
	// 		}
	// 		else
	// 		{
	// 			s_CUI_ID_FRAME_ChatHistory.m_otherFriendList.push_back(playerName);
	// 
	// 		}

}
void CUI_ID_FRAME_ChatHistory::RefreshFriendName()
{
	m_goodFriendList.clear();
	m_otherFriendList.clear();
	std::map<int, RelationDataToClient>& friendMap = thePlayerRole.GetMapFriendInfo();
	std::map<int, RelationDataToClient>::iterator iter = friendMap.begin();
	for( ; iter != friendMap.end(); ++iter)
	{
		if ((iter->second.HaveRelation(RelationDefine::Friend) && !iter->second.HaveRelation(RelationDefine::Marriage | RelationDefine::Teacher | RelationDefine::Student | RelationDefine::Brother)))
		{
			m_goodFriendList.push_back((*iter).second.GetName());			
		}
	}
	char saveFileName[MAX_PATH] = {0};
	MeSprintf_s(saveFileName,sizeof(saveFileName)/sizeof(char) - 1,"%s\\MessageHistory",CUserData::Instance()->GetUserDataPath());
	EnumFile( saveFileName,(swFileOperation)RetriveFileName,this,true );		
}

void CUI_ID_FRAME_ChatHistory::RefreshFriendListUI( bool isFriend )
{
	m_pID_CHECKBOX_Friend->SetCheck(isFriend);
	m_pID_CHECKBOX_Stranger->SetCheck(!isFriend);

	m_pID_LIST_FriendName->Clear();
	std::vector<std::string>* nameList = &m_goodFriendList;
	if (!isFriend)
	{
		nameList = &m_otherFriendList;
	}
	int selectIndex = 0;
	int nCount = 0;
	for (std::vector<std::string>::iterator iter = nameList->begin(); iter != nameList->end(); ++iter,++nCount)
	{
		if ((*iter) == m_currFriendName)
		{
			selectIndex = nCount;
		}
		ControlList::S_List stItem;
		stItem.SetData( (*iter).c_str());
		m_pID_LIST_FriendName->AddItem(&stItem);

	}
	m_pID_LIST_FriendName->SetCurSelIndex(selectIndex);

	if (m_currFriendName.size() == 0 && nameList->size() != 0)
	{
		m_currFriendName = (*nameList)[selectIndex];
	}
	RefreshChatList();

}

void CUI_ID_FRAME_ChatHistory::RefreshChatList()
{
	m_oldChatVec.clear();
	m_pID_LIST_ChatList->Clear();
	m_pID_TEXT_Page->Clear();
	char saveFileName[MAX_PATH] = {0};
	MeSprintf_s(saveFileName,sizeof(saveFileName)/sizeof(char) - 1,"%s\\MessageHistory\\%s.txt",CUserData::Instance()->GetUserDataPath(),m_currFriendName.c_str());
	FILE* fileHandle = fopen(saveFileName,"rt");
	if (fileHandle)
	{
		while( 1)
		{
			historyChatMessage msg;
			int contentLength = 0;
			int nTemp = 0;
			fscanf(fileHandle,"%s %d %d ",msg.dateTime,&nTemp,&contentLength);
			if (feof( fileHandle ))
			{
				break;
			}
// 			int nameLength = strlen(msg.playerName);
// 			for (int i = nameLength; i < 17; ++i)
// 			{
// 				msg.playerName[i] = ' ';
// 			}
// 			msg.playerName[17] = '\0';
//  			fseek(fileHandle,1,SEEK_CUR);
			msg.isToMe = nTemp;
 			fread(msg.chatContent,sizeof(char),contentLength,fileHandle);
			msg.chatContent[contentLength] = '\0';
			char lineEnd;
			fscanf(fileHandle,"%c",&lineEnd);
			if (lineEnd != '\n')
			{
				assert(0);
				m_oldChatVec.clear();
				break;
			}
			m_oldChatVec.push_back(msg);

		}
		fclose(fileHandle);
	}

	if (MessageInfoMgr::Instance()->IsNeedSave())
	{
		MessageInfoMgr::InfoList* pList = MessageInfoMgr::Instance()->GetInfoList(m_currFriendName.c_str());
		if (pList)
		{
			for (int i = pList->mSavedIndex; i < pList->messageList.size();++i)
			{
				historyChatMessage msg;
				MessageInfoMgr::MessageInfo* pInfo = pList->messageList[i];
				_fillDateTime(msg, pInfo->time);
				_FillChatContent(msg,pInfo->text.c_str());
				msg.isToMe = pInfo->IsToMe;
				m_oldChatVec.push_back(msg);
			}
		}
	}

	if(m_oldChatVec.size() > 0)
	{
		int nIndex = ((m_oldChatVec.size() - 1)/CHAT_NUMBER_PER_PAGE)*CHAT_NUMBER_PER_PAGE;
		SetCurrChatIndex(nIndex);
	}
	else
	{
		RefreshPageButtonStatus();
	}
	// 			m_pID_LIST_ChatList->SetCurSelIndex(m_currChatIndex);
	// 			m_pID_TEXT_Chat->SetText(m_oldChatVec[m_currChatIndex].chatContent);
}

int CUI_ID_FRAME_ChatHistory::AddChatMessage( historyChatMessage &msg )
{
	int nOldItemCnt = m_pID_LIST_ChatList->GetListItemCnt();
	std::string strListStr;// =  msg.playerName;
	if (msg.isToMe)
	{
		strListStr = m_currFriendName;
	}
	else
	{
		strListStr = thePlayerRole.GetName();
	}
	int nCount = strListStr.size();
	for (int i = nCount; i < 18; ++i)
	{
		strListStr += " ";
	}
	char cShowDateTime[cDateTimeLength];
	strcpy_s(cShowDateTime,cDateTimeLength,msg.dateTime);
	for(int i = 0 ; i < strlen(cShowDateTime);++i)
	{
		if (cShowDateTime[i] == ',')
		{
			cShowDateTime[i] = ' ';
			break;
		}
	}
	strListStr += cShowDateTime;
	// 		nListStr += msg.chatContent;

	D3DCOLOR NameCol = Color_Config.getColor(CC_MessageSelfName);
	D3DCOLOR WordCol = Color_Config.getColor(CC_MessageSelfWord);
	std::wstring wstrText = Common::_tstring::toWideString( strListStr.c_str() );
	if (std::wstring::npos != wstrText.find( Common::_tstring::toWideString( m_currFriendName.c_str() ).c_str() ) )
	{
		NameCol = Color_Config.getColor(CC_MessageOtherName);
		WordCol = Color_Config.getColor(CC_MessageOtherWord);
	}
	ControlList::S_List stItem;
	stItem.SetData( strListStr.c_str(),0,0,NameCol );
	m_pID_LIST_ChatList->AddItem( &stItem );

// 	D3DCOLOR col = Color_Config.getColor(CC_CHAT_TEAM);
// 	if (-1 != nListStr.find(m_currFriendName.c_str()))
// 	{
// 		col = Color_Config.getColor(CC_CHAT_PERSONAL);
// 	}
	std::string str(msg.chatContent);
	ShowTextInHistoryChatList(str,WordCol);
	return m_pID_LIST_ChatList->GetListItemCnt() - nOldItemCnt;
}

void CUI_ID_FRAME_ChatHistory::_fillDateTime( historyChatMessage &msg, SYSTEMTIME &time )
{
	sprintf(msg.dateTime,"%4d-%2d-%2d,%2d:%2d:%2d",time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond);
	int nStrLength = strlen(msg.dateTime);
	for (int i = 0 ; i < nStrLength; ++i)
	{
		if (msg.dateTime[i] == ' ')
		{
			msg.dateTime[i] = '0';
		}
	}
	for(int i = nStrLength; i < cDateTimeLength - 1; ++i)
	{
		msg.dateTime[i] = ' ';
	}
	msg.dateTime[cDateTimeLength - 1] = '\0';
}

// void CUI_ID_FRAME_ChatHistory::_FillPlayerName( historyChatMessage &msg, const char * nameBegin , int nCount )
// {
// 	for(int i = 0; i < 17; ++i)
// 	{
// 		if (i < nCount)
// 		{
// 			msg.playerName[i] = nameBegin[i];
// 		}
// 		else
// 		{
// 			msg.playerName[i] = ' ';
// 		}
// 
// 	}
// 	msg.playerName[17] = '\0';
// }

void CUI_ID_FRAME_ChatHistory::_FillChatContent( historyChatMessage &msg, const char * contentStr )
{
	strcpy(msg.chatContent,contentStr);
// 	wstring wsContent = Common::_tstring::toWideString( contentStr );
// 	int nPos = wsContent.find(Common::_tstring::toWideString(theXmlString.GetString(eClient_Chat_Begin)));
// 	if (nPos != std::string::npos)
// 	{
// 		string strName = Common::_tstring::toNarrowString(wsContent.substr(0,nPos).c_str());
// 		int nNameCharCount = strName.length(); 
// 		_FillPlayerName(msg, contentStr,nNameCharCount);
// 		strcpy(msg.chatContent,&contentStr[nNameCharCount + strlen(theXmlString.GetString(eClient_Chat_Begin))]);
// 	}
}

void CUI_ID_FRAME_ChatHistory::ShowTextInHistoryChatList( std::string& str, const D3DCOLOR col)
{
	if ( str.size() > 0 && m_pID_LIST_ChatList )
	{

		ExpressionManager::GetInstance().AddExpressionAni(str);
		ControlList::S_List	stItem;
		stItem.UseSelColor = false;

		if( m_pID_LIST_ChatList->GetFontSize() == 0 )
			return;

		std::wstring strWide = Common::_tstring::toWideString(str.c_str());
		int startCP = 0;
		int endCP = strWide.length();
		int width = ControlHelper::Get().GetTextWidth(strWide,
			m_pID_LIST_ChatList->GetFontHDC(),
			startCP, endCP,m_pID_LIST_ChatList, m_pID_LIST_ChatList->GetFontIndex() );
		int listWidth = m_pID_LIST_ChatList->GetWidth();
		while (width > listWidth)
		{
			--endCP;
			width = ControlHelper::Get().GetTextWidth(strWide,
				m_pID_LIST_ChatList->GetFontHDC(),
				startCP, endCP,m_pID_LIST_ChatList, m_pID_LIST_ChatList->GetFontIndex() );
		}


		int nWidthByte = endCP;

		if ( (int)strWide.size() > 	nWidthByte )
		{

			//-----------------------------------------------------------------

			guard(add_2_25);

			std::string line = Common::_tstring::toNarrowString(strWide.substr(0, nWidthByte).c_str());
			int nPreFix = line.rfind("{");
			int nPostFix = line.rfind("}");
			if (nPreFix > nPostFix)//表情发生了错行
			{
				std::wstring nextline = &strWide[nWidthByte];
				int nPostFix = nextline.find(L"}");
				if (nPostFix != -1 && nPreFix != 0)
				{
					line += Common::_tstring::toNarrowString(nextline.substr(0, nPostFix + 1).c_str());
					nWidthByte += nPostFix + 1;
				}
			}
			//-------------------这里真正添加数据 和 调用递归-----------------
			{
				stItem.SetData( line.c_str() , 0, NULL, col );
				ControlList::S_List* pAdd = m_pID_LIST_ChatList->AddItem( &stItem );
// 				m_pID_LIST_ChatList->ParseText(pAdd );

				ShowTextInHistoryChatList( Common::_tstring::toNarrowString(&strWide[nWidthByte]),col);
			}

			unguard;

		}
		else
		{
			guard(add_2_26);

			stItem.SetData( str.c_str() , 0, NULL, col );

			ControlList::S_List* pAdd = m_pID_LIST_ChatList->AddItem( &stItem );
// 			m_pID_LIST_ChatList->ParseText(pAdd );

			unguard;

		}

	}

}

void CUI_ID_FRAME_ChatHistory::RefreshPageButtonStatus()
{
	m_pID_BUTTON_LastPage->SetEnable(false);
	m_pID_BUTTON_FirstPage->SetEnable(false);
	m_pID_BUTTON_PageDown->SetEnable(false);
	m_pID_BUTTON_PageUp->SetEnable(false);
	if (GetHistoryChatVec().size() > 0)
	{
		if (GetHistoryChatVec().size() - m_currChatIndex > CHAT_NUMBER_PER_PAGE)
		{
			m_pID_BUTTON_LastPage->SetEnable(true);
			m_pID_BUTTON_PageDown->SetEnable(true);
		}
		if (m_currChatIndex >= CHAT_NUMBER_PER_PAGE)
		{
			m_pID_BUTTON_FirstPage->SetEnable(true);
			m_pID_BUTTON_PageUp->SetEnable(true);
		}
	}
}
int messageRow[CHAT_NUMBER_PER_PAGE];
void CUI_ID_FRAME_ChatHistory::SetCurrChatIndex( int val )
{
	m_currChatIndex = val;
	memset(messageRow,0,sizeof(int)*CHAT_NUMBER_PER_PAGE);
	char cTemp[32];
	sprintf(cTemp,"%d/%d",m_currChatIndex/CHAT_NUMBER_PER_PAGE + 1,(m_oldChatVec.size() + CHAT_NUMBER_PER_PAGE - 1)/CHAT_NUMBER_PER_PAGE );
	m_pID_TEXT_Page->SetText(cTemp);
	RefreshPageButtonStatus();
	m_pID_LIST_ChatList->Clear();
	int nIndex = 0;
	for (oldChatVec::iterator iter = m_oldChatVec.begin() + m_currChatIndex; 
		(nIndex< CHAT_NUMBER_PER_PAGE) && (iter != m_oldChatVec.end());
		++iter,++nIndex)
	{
		messageRow[nIndex] = AddChatMessage(*iter) ;
	}
	SetLastSearchIndex(m_lastSearchIndex);
}

void CUI_ID_FRAME_ChatHistory::DoSearch()
{
	const char* pFoundText = m_pID_EDIT_Search->GetText();
	if (!pFoundText || pFoundText[0] == '\0')
	{
		return;
	}
	if (m_SearchType == ChatName)
	{
		// 			nameSearchResult.m_bGoodFriend = true;
		// 			nameSearchResult.m_index		= 0;
		DoNameSearch(pFoundText);
	}
	else
	{
		DoContentSearch(pFoundText);
	}
}

void CUI_ID_FRAME_ChatHistory::DoNameSearch(const char* pName)
{
	bool isFriend =  m_pID_CHECKBOX_Friend->IsChecked();

	std::vector<std::string>* nameList = &m_goodFriendList;
	if (!isFriend)
	{
		nameList = &m_otherFriendList;
	}

	bool nFoundCurr = false;
	bool bFound = false;
	for (std::vector<std::string>::iterator iter = nameList->begin() ; iter != nameList->end(); ++iter)
	{
		if (nFoundCurr)
		{
			if (-1 != (*iter).find(pName))
			{
				m_currFriendName = (*iter);
				bFound = true;
				break;
			}
		}
		else
		{
			if (*iter == m_currFriendName)
			{
				nFoundCurr = true;
			}
		}
	}
	if (bFound)
	{//found
		RefreshFriendListUI(isFriend);
	}
	else
	{
		isFriend = !isFriend;
		std::vector<std::string>* nameList = &m_goodFriendList;
		if (!isFriend)
		{
			nameList = &m_otherFriendList;
		}
		bool bFound = false;
		for (std::vector<std::string>::iterator iter = nameList->begin() ; iter != nameList->end(); ++iter)
		{
			{
				if (-1 != (*iter).find(pName))
				{
					m_currFriendName = (*iter);
					bFound = true;
					break;
				}
			}
		}
		if (bFound)
		{//found
			RefreshFriendListUI(isFriend);
		}
		else
		{
			isFriend = !isFriend;
			std::vector<std::string>* nameList = &m_goodFriendList;
			if (!isFriend)
			{
				nameList = &m_otherFriendList;
			}
// 			int nCount = 0;
			bool bFound = false;
			for (std::vector<std::string>::iterator iter = nameList->begin() ; iter != nameList->end(); ++iter)
			{
				if (-1 != (*iter).find(pName))
				{
					m_currFriendName = (*iter);
					bFound = true;
					break;
				}
				if (*iter == m_currFriendName)
				{
					break;
				}
			}
			if (bFound)
			{//found
				RefreshFriendListUI(isFriend);
			}
			else
			{
				s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eUI_sCanNotFindString));
			}
		}
	}
}

void CUI_ID_FRAME_ChatHistory::DoContentSearch(const char* pFoundText)
{
	if (m_oldChatVec.size() == 0)
	{
		return;
	}
	if (m_lastSearchString != pFoundText || m_lastSearchIndex == -1 || m_lastSearchIndex < m_currChatIndex || m_currChatIndex - m_lastSearchIndex > CHAT_NUMBER_PER_PAGE)
	{
		m_lastSearchString = pFoundText;
		m_lastSearchIndex = m_currChatIndex;
	}
	int nCount = 1;
	for (oldChatVec::iterator iter = m_oldChatVec.begin() + m_lastSearchIndex + 1; iter != m_oldChatVec.end() ;++iter,++nCount)
	{
		if (strstr((*iter).chatContent,pFoundText))
		{
			m_lastSearchIndex = m_lastSearchIndex + nCount;
			int nIndex = ((m_lastSearchIndex - 1) /CHAT_NUMBER_PER_PAGE)*CHAT_NUMBER_PER_PAGE;
			SetCurrChatIndex(nIndex);
			return;
		}
	}
	nCount = 0;
	for (oldChatVec::iterator iter = m_oldChatVec.begin(); iter != m_oldChatVec.begin() + m_lastSearchIndex + 1;++iter,++nCount)
	{
		if (strstr((*iter).chatContent,pFoundText))
		{
			m_lastSearchIndex = nCount;
			int nIndex = ((m_lastSearchIndex - 1)/CHAT_NUMBER_PER_PAGE)*CHAT_NUMBER_PER_PAGE;
			SetCurrChatIndex(nIndex);
			return;
		}
	}
	{
		SetLastSearchIndex(-1);
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eUI_sCanNotFindString));
	}

}

void CUI_ID_FRAME_ChatHistory::SetLastSearchIndex( int val )
{
	m_lastSearchIndex = val;
	if (-1 == m_lastSearchIndex || m_lastSearchIndex < m_currChatIndex || m_currChatIndex - m_currChatIndex > CHAT_NUMBER_PER_PAGE)
	{
		m_pID_LIST_ChatList->SetCurSelIndex(-1);
		return;
	}
	int nLineCount = 0;
	int nChatIndexInThisPage = val%CHAT_NUMBER_PER_PAGE;
	for (int i = 0; i < nChatIndexInThisPage;++i)
	{
		nLineCount += messageRow[i];
	}
	const char* pFoundText = m_pID_EDIT_Search->GetText();
	bool bFound = false;
	for (int i = nLineCount + 1; i < nLineCount + messageRow[nChatIndexInThisPage]; ++i)
	{
		if (strstr(m_pID_LIST_ChatList->GetListItem(i)->m_szText,pFoundText))
		{
			m_pID_LIST_ChatList->SetCurSelIndex(i);
			bFound = true;
			break;
		}

	}
	if(!bFound)//如果字串跨行只能加亮第一行了
		m_pID_LIST_ChatList->SetCurSelIndex(nLineCount + 1);
}

BOOL CUI_ID_FRAME_ChatHistory::EditInputIsVisable()
{
	if( m_pID_EDIT_Search )
	{
		bool bRet = (theUiManager.GetFocus() ==m_pID_EDIT_Search);
		return bRet;

	}
	return FALSE;

}