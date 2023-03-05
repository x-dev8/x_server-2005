/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\MiniChat.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "MiniChat.h"
#include "tstring.h"
#include "UIMgr.h"
#include "meui/ExpressionManager.h"
#include "ChatMessageMgr.h"
#include "FriendDlg.h"
const int nMaxRemindRow = 20;
CUI_ID_FRAME_MiniChat s_CUI_ID_FRAME_MiniChat;
MAP_FRAME_RUN( s_CUI_ID_FRAME_MiniChat, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_MiniChat, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_MiniChat, ID_LIST_ListOnListSelectChange )
CUI_ID_FRAME_MiniChat::CUI_ID_FRAME_MiniChat()
{
	// Member
	m_pID_FRAME_MiniChat = NULL;
	m_pID_LIST_List = NULL;

}
// Frame
bool CUI_ID_FRAME_MiniChat::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_MiniChat::OnFrameRender()
{
// 	int nStartIndex = m_pID_LIST_List->GetStartIndex();
// 	std::list<std::string>::iterator iter = m_MiniPlayerList.begin();
// 	int nTemp = nStartIndex;
// 	while(nTemp != 0)
// 	{
// 		++iter;
// 		--nTemp;
// 	}
// 	nTemp = 0;
// 	for (; iter != m_MiniPlayerList.end(); ++iter)
// 	{
// 		if (IsRemindPlayer((*iter).c_str()))
// 		{
// 			RECT rcWindow;
// 			m_pID_LIST_List->GetRealRect(&rcWindow);
// 			int nRowHeight = m_pID_LIST_List->GetListItemHeight();
// 
// 			rcWindow.top += nTemp*nRowHeight;
// 			rcWindow.bottom = rcWindow.top + nRowHeight;
// 
// 			rcWindow.right = rcWindow.left;
// 			rcWindow.left -= nRowHeight;
// 
// 			ExpressionManager::GetInstance().DrawExpression("#1010",rcWindow);
// 		}
// 		++nTemp;
// 		if (nTemp >= nMaxRemindRow)
// 		{
// 			break;
// 		}
// 	}
	return true;
}
// List
void CUI_ID_FRAME_MiniChat::ID_LIST_ListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_MiniChat )
		return;
}

// 装载UI
bool CUI_ID_FRAME_MiniChat::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\MiniChat.MEUI", true, UI_Render_LayerFirst );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\MiniChat.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_MiniChat::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_MiniChat, s_CUI_ID_FRAME_MiniChatOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_MiniChat, s_CUI_ID_FRAME_MiniChatOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_MiniChat, ID_LIST_List, s_CUI_ID_FRAME_MiniChatID_LIST_ListOnListSelectChange );

	m_pID_FRAME_MiniChat = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_MiniChat );
	m_pID_LIST_List = (ControlList*)theUiManager.FindControl( ID_FRAME_MiniChat, ID_LIST_List );
	assert( m_pID_FRAME_MiniChat );
	assert( m_pID_LIST_List );

	m_pID_LIST_List->SetLBtnDownFun( ID_List_MinilistOnLBClick );
	m_pID_LIST_List->SetHeight(0);
	m_pID_LIST_List->SetCurSelIndex(-1);
	m_pID_LIST_List->SetAutoSetCurIndex( false );
// 	m_pID_LIST_List->SetDrawFlags(DT_CENTER);

	SetVisable(false);

	USE_SCRIPT( eUI_OBJECT_MiniChat, this );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_MiniChat::_UnLoadUI()
{
	CLOSE_SCRIPT( eUI_OBJECT_MiniChat );
	m_pID_FRAME_MiniChat = NULL;
	m_pID_LIST_List = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\MiniChat.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_MiniChat::_IsVisable()
{
	if( !m_pID_FRAME_MiniChat )
		return false;
	return m_pID_FRAME_MiniChat->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_MiniChat::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_MiniChat )
		return;
	m_pID_FRAME_MiniChat->SetVisable( bVisable );
}

void CUI_ID_FRAME_MiniChat::AddMiniPlayerListName( const char* pPlayer )
{
	if (pPlayer && strlen(pPlayer) == 0)
		return;

	if (IsMiniChatPlayer(pPlayer))
	{
		return;
	}
	
    if( !IsUILoad() )
        SetVisable( true );

	m_MiniPlayerList.push_back(pPlayer);

	char szItem[128] = {0};
	const char* pPortrait = s_CUI_ID_FRAME_Friend.GetPortraitGifFromName(pPlayer);
	MeSprintf_s( szItem, sizeof(szItem)/sizeof(char) - 1, "%s%s", pPortrait,pPlayer );
	ControlList::S_List stItem;
	stItem.SetData( szItem, 0);
	stItem.SetMargin(5);
	m_pID_LIST_List->AddItem(&stItem,NULL, false);


// 	int nListWidth = m_pID_LIST_List->GetWidth();
// 	std::wstring strWide = Common::_tstring::toWideString(pPlayer);
// 	int startCP = 0;
// 	int endCP = strWide.length();
// 	int width = ControlHelper::Get().GetTextWidth(strWide,
// 		m_pID_LIST_List->GetFontHDC(),
// 		startCP, endCP,m_pID_LIST_List, m_pID_LIST_List->GetFontIndex() );
// 	if (width > nListWidth)
// 	{
// 		while (width > nListWidth)
// 		{
// 			--endCP;
// 			width = ControlHelper::Get().GetTextWidth(strWide,
// 				m_pID_LIST_List->GetFontHDC(),
// 				startCP, endCP,m_pID_LIST_List, m_pID_LIST_List->GetFontIndex() );
// 		}
// 		strWide.erase(strWide.begin()+(endCP-2),strWide.end());
// 		strWide += L"...";
// 	}
// 	stItem.SetData( Common::_tstring::toNarrowString(strWide.c_str()).c_str() );
// 	m_pID_LIST_List->AddItem(&stItem);

	RefrestListHeight();
}

void CUI_ID_FRAME_MiniChat::ID_List_MinilistOnLBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	int curSel = s_CUI_ID_FRAME_MiniChat.m_pID_LIST_List->GetCurSelIndex();
	std::list<std::string>::iterator iter = s_CUI_ID_FRAME_MiniChat.m_MiniPlayerList.begin();
	if (iter == s_CUI_ID_FRAME_MiniChat.m_MiniPlayerList.end())
		return;

	int nTemp = curSel;
	while(nTemp != 0)
	{
		++iter;
		--nTemp;
	}


	for (std::list<std::string>::iterator iterRemind = s_CUI_ID_FRAME_MiniChat.m_MiniRemindPlayerList.begin(); iterRemind != s_CUI_ID_FRAME_MiniChat.m_MiniRemindPlayerList.end();++iterRemind)
	{
		if (*iterRemind == *iter)
		{
			s_CUI_ID_FRAME_MiniChat.m_MiniRemindPlayerList.erase(iterRemind);
			break;
		}
		
	}
	chatMessageManage.ShowChatMessageFrame((*iter).c_str());
}

void CUI_ID_FRAME_MiniChat::RefrestListHeight()
{
	int nRowHeight = m_pID_LIST_List->GetListItemHeight();
	int nRowCount = min(nMaxRemindRow,m_MiniPlayerList.size());
	m_pID_LIST_List->SetHeight(nRowHeight*nRowCount);
	if (s_CUI_ID_FRAME_MiniChat.m_MiniPlayerList.size() == 0)
	{
		s_CUI_ID_FRAME_MiniChat.SetVisable(false);
	}
	else
	{
		s_CUI_ID_FRAME_MiniChat.SetVisable(true);
	}
	m_pID_LIST_List->SetCurSelIndex(-1);
}

void CUI_ID_FRAME_MiniChat::AddRemindPlayer( const char* pPlayer )
{
	assert(IsMiniChatPlayer(pPlayer));
	if (IsRemindPlayer(pPlayer))
	{
		return;
	}
	m_MiniRemindPlayerList.push_back(pPlayer);
	int nCount = 0;
	for (std::list<std::string>::iterator iter = m_MiniPlayerList.begin(); iter != m_MiniPlayerList.end(); ++iter,++nCount)
	{
		if (*iter == pPlayer)
		{
			break;
		}
	}
	assert(nCount < m_pID_LIST_List->GetListItemCnt());

	ControlList::S_List* pList = m_pID_LIST_List->GetListItem(nCount);
	char szItem[128] = {0};
	const char* pPortrait = s_CUI_ID_FRAME_Friend.GetPortraitGifFromName(pPlayer);
	MeSprintf_s( szItem, sizeof(szItem)/sizeof(char) - 1, "%s%s", pPortrait,pPlayer );
	strncpy( pList->m_szText, szItem, sizeof(pList->m_szText) - 1 );
	m_pID_LIST_List->ParseText(pList,NULL);
	m_pID_FRAME_MiniChat->SetRedraw();

	if (s_CUI_ID_FRAME_Friend.IsVisable())
	{
		s_CUI_ID_FRAME_Friend.NeedRefresh();
	}
}

bool CUI_ID_FRAME_MiniChat::IsRemindPlayer(const char* pPlayer)
{
	for (std::list<std::string>::iterator iter = m_MiniRemindPlayerList.begin(); iter != m_MiniRemindPlayerList.end(); ++iter)
	{
		if (*iter == pPlayer)
		{
			return true;
		}			
	}
	return false;
}

bool CUI_ID_FRAME_MiniChat::IsMiniChatPlayer( const char* pPlayer )
{
	for (std::list<std::string>::iterator iter = m_MiniPlayerList.begin(); iter != m_MiniPlayerList.end(); ++iter)
	{
		if (*iter == pPlayer)
		{
			return true;
		}			
	}
	return false;

}

bool CUI_ID_FRAME_MiniChat::RemoveRemindPlayer( const char* pPlayer )
{
	int nCount = 0;
	for (std::list<std::string>::iterator iter = m_MiniPlayerList.begin(); iter != m_MiniPlayerList.end(); ++iter,++nCount)
	{
		if (*iter == pPlayer)
		{

			for (std::list<std::string>::iterator iterRemind = s_CUI_ID_FRAME_MiniChat.m_MiniRemindPlayerList.begin(); iterRemind != s_CUI_ID_FRAME_MiniChat.m_MiniRemindPlayerList.end();++iterRemind)
			{
				if (*iterRemind == pPlayer)
				{
					s_CUI_ID_FRAME_MiniChat.m_MiniRemindPlayerList.erase(iterRemind);
					if (s_CUI_ID_FRAME_Friend.IsVisable())
					{//消除Friend里面的闪动状态
						s_CUI_ID_FRAME_Friend.NeedRefresh();
					}
					break;
				}

			}
			s_CUI_ID_FRAME_MiniChat.m_MiniPlayerList.erase(iter);
			s_CUI_ID_FRAME_MiniChat.m_pID_LIST_List->RemoveListItem(nCount);
			s_CUI_ID_FRAME_MiniChat.RefrestListHeight();
			return true;
		}
	}
	return false;
}

void CUI_ID_FRAME_MiniChat::Clear()
{
	m_MiniPlayerList.clear();
	m_MiniRemindPlayerList.clear();
}