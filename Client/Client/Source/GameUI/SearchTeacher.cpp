/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\刘小兵\SearchTeacher.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SearchTeacher.h"
#include "GlobalDef.h"
#include "RelationMessage.h"
#include "RelationDefine.h"
#include "Common.h"
#include "NetworkInput.h"
#include "PlayerRole.h"
#include "color_config.h"
#include "XmlStringLanguage.h"
#include "ScreenInfoManager.h"

CUI_ID_FRAME_SearchTeacher s_CUI_ID_FRAME_SearchTeacher;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SearchTeacher, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SearchTeacher, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SearchTeacher, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SearchTeacher, ID_BUTTON_SeekOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SearchTeacher, ID_BUTTON_ApplyOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SearchTeacher, ID_LIST_NameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SearchTeacher, ID_LIST_GuildOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SearchTeacher, ID_LIST_LevelOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SearchTeacher, ID_LIST_SelectOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SearchTeacher, ID_BUTTON_PageUpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SearchTeacher, ID_BUTTON_PageDownOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SearchTeacher, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SearchTeacher, ID_BUTTON_RecruitOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SearchTeacher, ID_BUTTON_DeleteOnButtonClick )

CUI_ID_FRAME_SearchTeacher::CUI_ID_FRAME_SearchTeacher()
{
	// Member
	m_pID_FRAME_SearchTeacher = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Seek = NULL;
	m_pID_BUTTON_Apply = NULL;
	m_pID_LIST_Name = NULL;
	m_pID_LIST_Guild = NULL;
	m_pID_LIST_Level = NULL;
	m_pID_LIST_Select = NULL;
	m_pID_BUTTON_PageUp = NULL;
	m_pID_BUTTON_PageDown = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Recruit = NULL;
	m_pID_BUTTON_Delete = NULL;
}
// Frame
bool CUI_ID_FRAME_SearchTeacher::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_SearchTeacher::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_SearchTeacher::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}

// List
void CUI_ID_FRAME_SearchTeacher::ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_SearchTeacher::ID_LIST_GuildOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_SearchTeacher::ID_LIST_LevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_SearchTeacher::ID_LIST_SelectOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}

// 装载UI
bool CUI_ID_FRAME_SearchTeacher::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SearchTeacher.MEUI", false, UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SearchTeacher.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_SearchTeacher::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SearchTeacher, s_CUI_ID_FRAME_SearchTeacherOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SearchTeacher, s_CUI_ID_FRAME_SearchTeacherOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_SearchTeacher, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SearchTeacherID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SearchTeacher, ID_BUTTON_Seek, s_CUI_ID_FRAME_SearchTeacherID_BUTTON_SeekOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SearchTeacher, ID_BUTTON_Apply, s_CUI_ID_FRAME_SearchTeacherID_BUTTON_ApplyOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_SearchTeacher, ID_LIST_Name, s_CUI_ID_FRAME_SearchTeacherID_LIST_NameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_SearchTeacher, ID_LIST_Guild, s_CUI_ID_FRAME_SearchTeacherID_LIST_GuildOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_SearchTeacher, ID_LIST_Level, s_CUI_ID_FRAME_SearchTeacherID_LIST_LevelOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_SearchTeacher, ID_LIST_Select, s_CUI_ID_FRAME_SearchTeacherID_LIST_SelectOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_SearchTeacher, ID_BUTTON_PageUp, s_CUI_ID_FRAME_SearchTeacherID_BUTTON_PageUpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SearchTeacher, ID_BUTTON_PageDown, s_CUI_ID_FRAME_SearchTeacherID_BUTTON_PageDownOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SearchTeacher, ID_BUTTON_Cancel, s_CUI_ID_FRAME_SearchTeacherID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SearchTeacher, ID_BUTTON_Recruit, s_CUI_ID_FRAME_SearchTeacherID_BUTTON_RecruitOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SearchTeacher, ID_BUTTON_Delete, s_CUI_ID_FRAME_SearchTeacherID_BUTTON_DeleteOnButtonClick );

	m_pID_FRAME_SearchTeacher = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SearchTeacher );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SearchTeacher, ID_BUTTON_CLOSE );
	m_pID_BUTTON_Seek = (ControlButton*)theUiManager.FindControl( ID_FRAME_SearchTeacher, ID_BUTTON_Seek );
	m_pID_BUTTON_Apply = (ControlButton*)theUiManager.FindControl( ID_FRAME_SearchTeacher, ID_BUTTON_Apply );
	m_pID_LIST_Name = (ControlList*)theUiManager.FindControl( ID_FRAME_SearchTeacher, ID_LIST_Name );
	m_pID_LIST_Guild = (ControlList*)theUiManager.FindControl( ID_FRAME_SearchTeacher, ID_LIST_Guild );
	m_pID_LIST_Level = (ControlList*)theUiManager.FindControl( ID_FRAME_SearchTeacher, ID_LIST_Level );
	m_pID_LIST_Select = (ControlList*)theUiManager.FindControl( ID_FRAME_SearchTeacher, ID_LIST_Select );
	m_pID_BUTTON_PageUp = (ControlButton*)theUiManager.FindControl( ID_FRAME_SearchTeacher, ID_BUTTON_PageUp );
	m_pID_BUTTON_PageDown = (ControlButton*)theUiManager.FindControl( ID_FRAME_SearchTeacher, ID_BUTTON_PageDown );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_SearchTeacher, ID_TEXT_Page );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_SearchTeacher, ID_BUTTON_Cancel );
	m_pID_BUTTON_Recruit = (ControlButton*)theUiManager.FindControl( ID_FRAME_SearchTeacher, ID_BUTTON_Recruit );
	m_pID_BUTTON_Delete = (ControlButton*)theUiManager.FindControl( ID_FRAME_SearchTeacher, ID_BUTTON_Delete );

	assert( m_pID_FRAME_SearchTeacher );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_Seek );
	assert( m_pID_BUTTON_Apply );
	assert( m_pID_LIST_Name );
	assert( m_pID_LIST_Guild );
	assert( m_pID_LIST_Level );
	assert( m_pID_LIST_Select );
	assert( m_pID_BUTTON_PageUp );
	assert( m_pID_BUTTON_PageDown );
	assert( m_pID_TEXT_Page );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_Recruit );
	assert( m_pID_BUTTON_Delete );
	return true;
}
	// 卸载UI
bool CUI_ID_FRAME_SearchTeacher::_UnLoadUI()
{
	m_pID_FRAME_SearchTeacher = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\SearchTeacher.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SearchTeacher::_IsVisable()
{
	return m_pID_FRAME_SearchTeacher->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SearchTeacher::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_SearchTeacher->SetVisable( bVisable );
}

//-----------------------------------------------------------------------------------------------------------------
const int ConstListNumber = 20;
void CUI_ID_FRAME_SearchTeacher::OnShowSearchResult(Msg * pMsg_)
{
	SetVisable(true);
	MsgRegisterRelationList* pMsg = (MsgRegisterRelationList*)pMsg_;
	if (pMsg->ustRelation == RelationDefine::Teacher)
	{
		//查找师傅
		m_pID_BUTTON_Apply->SetVisable(true);
		m_pID_BUTTON_Recruit->SetVisable(false);
	}

	if (pMsg->ustRelation == RelationDefine::Student)
	{
		//查找徒弟
		m_pID_BUTTON_Apply->SetVisable(false);
		m_pID_BUTTON_Recruit->SetVisable(true);
	}
	m_pID_BUTTON_Delete->SetVisable(false);
	
	ResetState();

	m_nCurrentPageIndex = 1;
	m_nPlayerNumber = pMsg->ustCount;
	m_vctRelationAttribute.resize(m_nPlayerNumber);
	for (int i = 0; i < m_nPlayerNumber; ++i)
	{
		m_vctRelationAttribute[i] = pMsg->xAttribute[i];
	}
	
	ShowAttributeList();
}

void CUI_ID_FRAME_SearchTeacher::ShowAttributeList()
{
	RefreshButtonState();
	ClearList();
	ShowList();
}

void CUI_ID_FRAME_SearchTeacher::ShowList()
{
	int nStart = (m_nCurrentPageIndex - 1) *  ConstListNumber;
	int nEnd = m_nCurrentPageIndex * ConstListNumber;
	ControlList::S_List	stItem;
	for (int i = nStart; i < nEnd && i < m_nPlayerNumber; ++i)
	{
		stItem.SetData( "" );
		m_pID_LIST_Select->AddItem(&stItem);
		stItem.clear();
		DWORD col = Color_Config.GetPkNameColor( PKMode_Normal);
		if (!m_vctRelationAttribute[i].GetOnLine())
		{
			col = 0;
		}

		//------------------------------name
		char szPlayerName[RelationDefine::MaxNameLength] = {0};
		MeSprintf_s(szPlayerName, sizeof(szPlayerName)/sizeof(char) - 1, "%s", m_vctRelationAttribute[i].GetName());
		stItem.SetData(szPlayerName, 0, NULL, col);
		stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		m_pID_LIST_Name->AddItem(&stItem);
		stItem.clear();
		//------------------------------guild
		const CGuildInfo* pGuildInfo = thePlayerRole.GetGuildById(m_vctRelationAttribute[i].GetGuildID());
		if (pGuildInfo)
		{
			char szGuildName[128] = {0};
			if (m_vctRelationAttribute[i].GetGuildID() != 0)
			{
				MeSprintf_s(szGuildName, sizeof(szGuildName)/sizeof(char) - 1, "%s", pGuildInfo->GetName());
			}

			stItem.SetData(szGuildName, 0, NULL, col);
			stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
			m_pID_LIST_Guild->AddItem(&stItem);
			stItem.clear();
		}
		//------------------------------level
		char szLevel[128] = {0};
		MeSprintf_s(szLevel, sizeof(szLevel)/sizeof(char) - 1, "%d", m_vctRelationAttribute[i].GetLevel());
		stItem.SetData(szLevel, 0, NULL, col);
		stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		m_pID_LIST_Level->AddItem(&stItem);
		stItem.clear();
	}	
}

void CUI_ID_FRAME_SearchTeacher::ResetState()
{
	m_pID_BUTTON_PageUp->SetEnable(false);
	m_pID_BUTTON_PageDown->SetEnable(false);
	m_nCurrentPageIndex = 1;
	m_nPlayerNumber = 0;
	m_vctRelationAttribute.clear();
}

void CUI_ID_FRAME_SearchTeacher::ClearList()
{
	m_pID_LIST_Name->Clear();
	m_pID_LIST_Guild->Clear();
	m_pID_LIST_Level->Clear();
	m_pID_LIST_Select->Clear();
}

//申请拜师
bool CUI_ID_FRAME_SearchTeacher::ID_BUTTON_ApplyOnButtonClick( ControlObject* pSender )
{
	int nSelectIndex = m_pID_LIST_Select->GetCurSelIndex();//CurSel从0开始
	int nPlayerIndex = (m_nCurrentPageIndex - 1) * ConstListNumber + nSelectIndex;
	if (nSelectIndex == -1 || nPlayerIndex >= m_nPlayerNumber)
	{
		return true;
	}

	if (m_vctRelationAttribute[nPlayerIndex].GetID() == thePlayerRole.GetDBID())
	{
		ShowOperateOnMyself();
		return false;
	}

	MsgAddRelationReq msg;
	msg.stRelation = RelationDefine::Teacher;
	strncpy(msg.szName, m_vctRelationAttribute[nPlayerIndex].GetName(), sizeof(msg.szName)-1);
	GettheNetworkInput().SendMsg( &msg );
	ShowMessageSending();
	return true;	
}

//招收徒弟
bool CUI_ID_FRAME_SearchTeacher::ID_BUTTON_RecruitOnButtonClick( ControlObject* pSender )
{
	int nSelectIndex = m_pID_LIST_Select->GetCurSelIndex();//CurSel从0开始
	int nPlayerIndex = (m_nCurrentPageIndex - 1) * ConstListNumber + nSelectIndex;
	if (nSelectIndex == -1 || nPlayerIndex >= m_nPlayerNumber)
	{
		return true;
	}

	if (m_vctRelationAttribute[nPlayerIndex].GetID() == thePlayerRole.GetDBID())
	{
		ShowOperateOnMyself();
		return false;
	}

	MsgAddRelationReq msg;
	msg.stRelation = RelationDefine::Student;
	strncpy(msg.szName, m_vctRelationAttribute[nPlayerIndex].GetName(), sizeof(msg.szName)-1);
	GettheNetworkInput().SendMsg( &msg );
	ShowMessageSending();
	return true;
}

//关闭
bool CUI_ID_FRAME_SearchTeacher::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	return true;
}

//上一页
bool CUI_ID_FRAME_SearchTeacher::ID_BUTTON_PageUpOnButtonClick( ControlObject* pSender )
{
	m_nCurrentPageIndex -= 1;
	RefreshButtonState();
	ShowAttributeList();
	return true;
}
//下一页
bool CUI_ID_FRAME_SearchTeacher::ID_BUTTON_PageDownOnButtonClick( ControlObject* pSender )
{
	m_nCurrentPageIndex += 1;
	RefreshButtonState();
	ShowAttributeList();
	return true;
}

void CUI_ID_FRAME_SearchTeacher::RefreshButtonState()
{
	if (m_nCurrentPageIndex * ConstListNumber < m_nPlayerNumber)
	{
		m_pID_BUTTON_PageDown->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_PageDown->SetEnable(false);
	}

	if (m_nCurrentPageIndex > 1)
	{
		m_pID_BUTTON_PageUp->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_PageUp->SetEnable(false);
	}

	char szPageNum[256];
// 	std::string strStart = "第 ";
// 	std::string strEnd = " 页";
	MeSprintf_s(szPageNum, sizeof(szPageNum)/sizeof(char) - 1, "%d/%d", m_nCurrentPageIndex, (max(0,m_nPlayerNumber - 1))/ConstListNumber + 1);
	m_pID_TEXT_Page->SetText(szPageNum);
}

//查看详情
bool CUI_ID_FRAME_SearchTeacher::ID_BUTTON_SeekOnButtonClick( ControlObject* pSender )
{
	int nSelectIndex = m_pID_LIST_Select->GetCurSelIndex();//CurSel从0开始
	int nPlayerIndex = (m_nCurrentPageIndex - 1) * ConstListNumber + nSelectIndex;
	if (nSelectIndex == -1 || nPlayerIndex >= m_nPlayerNumber)
	{
		return true;
	}
	
	MsgWantPeek msg;
	msg.type = MsgWantPeek::EPT_Char;
	msg.stTargetID = m_vctRelationAttribute[nPlayerIndex].GetID();
	GettheNetworkInput().SendMsg( &msg );
	return true;
}

//删除徒弟 
bool CUI_ID_FRAME_SearchTeacher::ID_BUTTON_DeleteOnButtonClick( ControlObject* pSender )
{
	int nSelectIndex = m_pID_LIST_Select->GetCurSelIndex();//CurSel从0开始
	int nPlayerIndex = (m_nCurrentPageIndex - 1) * ConstListNumber + nSelectIndex;
	if (nSelectIndex == -1 || nPlayerIndex >= m_nPlayerNumber)
	{
		return true;
	}

	MsgDeleteRelationReq msg;
	msg.stRelation = RelationDefine::Student;
	msg.nPlayerID = m_vctRelationAttribute[nPlayerIndex].GetID();
	GettheNetworkInput().SendMsg( &msg );
	ShowMessageSending();
	return true;
}

//显示徒弟
void CUI_ID_FRAME_SearchTeacher::ShowMyStudentList()
{
	SetVisable(true);
	m_pID_BUTTON_Apply->SetVisable(false);
	m_pID_BUTTON_Recruit->SetVisable(false);
	m_pID_BUTTON_Delete->SetVisable(true);
	
	ClearList();
	ResetState();
	//store data
	std::map<int, RelationDataToClient>& friendMap = thePlayerRole.GetMapFriendInfo();
	std::map<int, RelationDataToClient>::iterator iter = friendMap.begin();
	for( ; iter != friendMap.end(); ++iter)
	{
		if (iter->second.HaveRelation(RelationDefine::Friend))
		{
			m_vctRelationAttribute.push_back(iter->second);
		}
	}

	m_nCurrentPageIndex = 1;
	m_nPlayerNumber = m_vctRelationAttribute.size();
	
	ShowAttributeList();	
}

void CUI_ID_FRAME_SearchTeacher::ShowMessageSending()
{
	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_ApplyMessageSending));
	CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Teacher_Belongs, szText);
}	

void CUI_ID_FRAME_SearchTeacher::ShowOperateOnMyself()
{
	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_UnableAppointMyself));
	CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Teacher_Belongs, szText);
}
