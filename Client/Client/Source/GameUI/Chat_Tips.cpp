/********************************************************************
Created by UIEditor.exe
FileName: E:\temp\Chat_Tips.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Chat_Tips.h"
#include "tstring.h"
#include "UIMgr.h"
#include "meui/ExpressionManager.h"
#include "ChatMessageMgr.h"
CUI_ID_FRAME_Chat_Tips s_CUI_ID_FRAME_Chat_Tips;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Chat_Tips, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Chat_Tips, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Chat_Tips, ID_BUTTON_TipsOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Chat_Tips, ID_LIST_TiplistOnListSelectChange )
CUI_ID_FRAME_Chat_Tips::CUI_ID_FRAME_Chat_Tips()
{
	// Member
	m_pID_FRAME_Chat_Tips = NULL;
	m_pID_PICTURE_6527 = NULL;
	m_pID_BUTTON_Tips = NULL;
	m_pID_LIST_Tiplist = NULL;

}
// Frame
bool CUI_ID_FRAME_Chat_Tips::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_Chat_Tips::OnFrameRender()
{
	RECT rcWindow;
	m_pID_BUTTON_Tips->GetRealRect(&rcWindow);

	ExpressionManager::GetInstance().DrawExpression("#1010",rcWindow);
	return true;
}
// Button
bool CUI_ID_FRAME_Chat_Tips::ID_BUTTON_TipsOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_Chat_Tips)
	{
		assert(false&&"ui error");
		return false;
	}

	assert(m_RemindPlayerList.size() > 0);
	if (m_RemindPlayerList.size() == 1)
	{
		chatMessageManage.ShowChatMessageFrame((*m_RemindPlayerList.begin()).c_str());
		m_RemindPlayerList.clear();
		SetVisable(false);
	}
	else
	{
		m_pID_LIST_Tiplist->SetVisable(true);
		m_pID_PICTURE_6527->SetVisable(true);
	}

	return true;
}
// List
void CUI_ID_FRAME_Chat_Tips::ID_LIST_TiplistOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}

// 装载UI
bool CUI_ID_FRAME_Chat_Tips::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Chat_Tips.MEUI",true );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Chat_Tips.MEUI]失败")
			return false;
	}
	// 		else if ( dwResult != 1/*文件版本号*/ )
	// 		{
	// 			MESSAGE_BOX("读取文件[Data\\UI\\Chat_Tips.MEUI]与源代码版本不一样")
	// 		}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Chat_Tips::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Chat_Tips, s_CUI_ID_FRAME_Chat_TipsOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Chat_Tips, s_CUI_ID_FRAME_Chat_TipsOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Chat_Tips, ID_BUTTON_Tips, s_CUI_ID_FRAME_Chat_TipsID_BUTTON_TipsOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Chat_Tips, ID_LIST_Tiplist, s_CUI_ID_FRAME_Chat_TipsID_LIST_TiplistOnListSelectChange );

	m_pID_FRAME_Chat_Tips = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Chat_Tips );
	m_pID_PICTURE_6527 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Chat_Tips, ID_PICTURE_6527 );
	m_pID_BUTTON_Tips = (ControlButton*)theUiManager.FindControl( ID_FRAME_Chat_Tips, ID_BUTTON_Tips );
	m_pID_LIST_Tiplist = (ControlList*)theUiManager.FindControl( ID_FRAME_Chat_Tips, ID_LIST_Tiplist );
	assert( m_pID_FRAME_Chat_Tips );
	assert( m_pID_PICTURE_6527 );
	assert( m_pID_BUTTON_Tips );
	assert( m_pID_LIST_Tiplist );

	m_pID_LIST_Tiplist->SetLBClickFun( ID_List_TiplistOnLBClick );

	m_pID_LIST_Tiplist->SetVisable(false);
	m_pID_PICTURE_6527->SetVisable(false);
	m_pID_FRAME_Chat_Tips->SetVisable(false);
	USE_SCRIPT ( eUI_OBJECT_ChatTip, m_pID_FRAME_Chat_Tips );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Chat_Tips::_UnLoadUI()
{
	CLOSE_SCRIPT( eUI_OBJECT_ChatTip );
	m_pID_FRAME_Chat_Tips = NULL;
	m_pID_LIST_Tiplist    = NULL;
	m_pID_PICTURE_6527    = NULL;
	m_pID_BUTTON_Tips     = NULL;
	m_pID_LIST_Tiplist    = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\Chat_Tips.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Chat_Tips::_IsVisable()
{
	if(!m_pID_FRAME_Chat_Tips)
		return false;

	return m_pID_FRAME_Chat_Tips->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Chat_Tips::_SetVisable( const bool bVisable )
{
	if(m_pID_FRAME_Chat_Tips)
		m_pID_FRAME_Chat_Tips->SetVisable( bVisable );
}

void CUI_ID_FRAME_Chat_Tips::AddRemindPlayer( const char* pPlayer,const char* pInfo)
{
	for (std::list<std::string>::iterator iter = m_RemindPlayerList.begin(); iter != m_RemindPlayerList.end(); ++iter)
	{
		if (*iter == pPlayer)
		{
			return;
		}			
	}

	m_RemindPlayerList.push_back(pPlayer);

	int nListWidth = m_pID_LIST_Tiplist->GetWidth();
	std::wstring strWide = Common::_tstring::toWideString(pInfo);
	int startCP = 0;
	int endCP = strWide.length();
	int width = ControlHelper::Get().GetTextWidth(strWide,
		m_pID_LIST_Tiplist->GetFontHDC(),
		startCP, endCP,m_pID_LIST_Tiplist, m_pID_LIST_Tiplist->GetFontIndex() );
	// 		if (pList->GetWidth() - 10 > pList->GetWidth())
	// 			listWidth = pList->GetWidth() - 10;
	if (width > nListWidth)
	{
		while (width > nListWidth)
		{
			--endCP;
			width = ControlHelper::Get().GetTextWidth(strWide,
				m_pID_LIST_Tiplist->GetFontHDC(),
				startCP, endCP,m_pID_LIST_Tiplist, m_pID_LIST_Tiplist->GetFontIndex() );
		}
		strWide.erase(strWide.begin()+(endCP-2),strWide.end());
		strWide += L"...";
	}
	ControlList::S_List stItem;
	stItem.m_bParseText = false;
	stItem.SetData( Common::_tstring::toNarrowString(strWide.c_str()).c_str() );
	m_pID_LIST_Tiplist->AddItem( &stItem );
}

void CUI_ID_FRAME_Chat_Tips::ID_List_TiplistOnLBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	int curSel = s_CUI_ID_FRAME_Chat_Tips.m_pID_LIST_Tiplist->GetCurSelIndex();
	std::list<std::string>::iterator iter = s_CUI_ID_FRAME_Chat_Tips.m_RemindPlayerList.begin();

	if (iter != s_CUI_ID_FRAME_Chat_Tips.m_RemindPlayerList.end())
	{
		int nTemp = curSel;
		while(nTemp != 0)
		{
			++iter;
			--nTemp;
		}
		if (iter != s_CUI_ID_FRAME_Chat_Tips.m_RemindPlayerList.end())
		{
			string playerName(*iter);//一定要使用这个变量把字串复制一份，ShowChatMessageFrame中可能会修改m_RemindPlayerList本身
			chatMessageManage.ShowChatMessageFrame(playerName.c_str());
		}
	}


}

void CUI_ID_FRAME_Chat_Tips::SetRemindVisable( const bool bVisable )
{
	m_pID_FRAME_Chat_Tips->SetVisable(bVisable);
	m_pID_LIST_Tiplist->SetVisable(false);
	m_pID_PICTURE_6527->SetVisable(false);
}

void CUI_ID_FRAME_Chat_Tips::Clear()
{
	m_RemindPlayerList.clear();
}

void CUI_ID_FRAME_Chat_Tips::RemoveRemindPlayer( const char* pPlayer )
{
	int index = 0;
	for (std::list<std::string>::iterator iter = m_RemindPlayerList.begin(); iter != m_RemindPlayerList.end(); ++iter,++index)
	{
		if (*iter == pPlayer)
		{
			m_RemindPlayerList.erase(iter);
			m_pID_LIST_Tiplist->RemoveListItem(index);
			if (m_RemindPlayerList.size() == 0)
			{
				SetVisable(false);
			}
			return;
		}			
	}
}


void CUI_ID_FRAME_Chat_Tips::SetTipListVisable( bool b )
{
	if(m_pID_LIST_Tiplist)
		m_pID_LIST_Tiplist->SetVisable(b);
	else
		assert(false&&"ui error");
}

void CUI_ID_FRAME_Chat_Tips::SetPicture6527( bool b )
{
	if(m_pID_PICTURE_6527)
		m_pID_PICTURE_6527->SetVisable(b);
	else
		assert(false&&"ui error");
}