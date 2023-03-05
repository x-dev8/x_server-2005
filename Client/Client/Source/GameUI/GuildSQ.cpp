/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildSQ.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GuildSQ.h"
#include "GuildBaseInfo.h"
#include "common.h"
#include "PlayerRole.h"
#include "core/Name.h"
#include "XmlStringLanguage.h"
#include "NetworkInput.h"
#include "ScreenInfoManager.h"

extern int g_nCharacterDBID;
CUI_ID_FRAME_GuildSQ s_CUI_ID_FRAME_GuildSQ;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GuildSQ, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GuildSQ, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildSQ, ID_BUTTON_IndexOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildSQ, ID_BUTTON_ProfessionOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildSQ, ID_BUTTON_LevelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildSQ, ID_BUTTON_NameOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildSQ, ID_LIST_IndexOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildSQ, ID_LIST_ProfessionOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildSQ, ID_LIST_LevelOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildSQ, ID_LIST_NameOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildSQ, ID_BUTTON_AcceptOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildSQ, ID_BUTTON_RefuseOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildSQ, ID_LIST_MEMBEROnListSelectChange )
CUI_ID_FRAME_GuildSQ::CUI_ID_FRAME_GuildSQ()
{
	// Member
	m_pID_FRAME_GuildSQ = NULL;
	m_pID_BUTTON_Index = NULL;
	m_pID_BUTTON_Profession = NULL;
	m_pID_BUTTON_Level = NULL;
	m_pID_BUTTON_Name = NULL;
	m_pID_TEXT_Index = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_Level = NULL;
	m_pID_TEXT_Profession = NULL;
	m_pID_LIST_Index = NULL;
	m_pID_LIST_Profession = NULL;
	m_pID_LIST_Level = NULL;
	m_pID_LIST_Name = NULL;
	m_pID_BUTTON_Accept = NULL;
	m_pID_BUTTON_Refuse = NULL;
	m_pID_LIST_MEMBER = NULL;
	ClearGuildMemberInfo();

	m_IsNeedUpdate = true;

	InitAllSortFunc();
	ResetSortMember();
	InitAllSortFunc();
}
// Frame
bool CUI_ID_FRAME_GuildSQ::OnFrameRun()
{
	OnUpdateUiInfo();
	return true;
}
bool CUI_ID_FRAME_GuildSQ::OnFrameRender()
{
	return true;
}
void CUI_ID_FRAME_GuildSQ::ID_LIST_MEMBEROnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}

// Button
bool CUI_ID_FRAME_GuildSQ::ID_BUTTON_IndexOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildSQ )
		return false;

	SetSortFunc(ekey_id);
	return true;
}
// Button
bool CUI_ID_FRAME_GuildSQ::ID_BUTTON_ProfessionOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildSQ )
		return false;

	SetSortFunc(ekey_profession);
	return true;
}
// Button
bool CUI_ID_FRAME_GuildSQ::ID_BUTTON_LevelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildSQ )
		return false;

	SetSortFunc(ekey_level);
	return true;
}
// Button
bool CUI_ID_FRAME_GuildSQ::ID_BUTTON_NameOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildSQ )
		return false;

	SetSortFunc(ekey_name);
	return true;
}
// List
void CUI_ID_FRAME_GuildSQ::ID_LIST_IndexOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_GuildSQ::ID_LIST_ProfessionOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_GuildSQ::ID_LIST_LevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_GuildSQ::ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// Button
bool CUI_ID_FRAME_GuildSQ::ID_BUTTON_AcceptOnButtonClick( ControlObject* pSender )
{
	//玩家同意申请
	int nIndex = m_pID_LIST_MEMBER->GetCurSelIndex();
	if (nIndex == -1 || nIndex >= m_MemberList.size())
	{
		ShowSelectNothingMessage();
		return false;
	}
	if (IsOperateOnMyself(m_MemberList[nIndex].ID))
	{
		return false;
	}

	MsgRequestJoinGuildAck msg;
	msg.nPlayerID =m_MemberList[nIndex].ID;
	msg.bAgreeJoin = true;
	GettheNetworkInput().SendMsg( &msg );
	return true;
}
inline void CUI_ID_FRAME_GuildSQ::ShowSelectNothingMessage()
{
	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_SelectNothing));
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, szText );
}
bool CUI_ID_FRAME_GuildSQ::IsOperateOnMyself(int nId)
{
	if (nId != g_nCharacterDBID)
	{
		return false;
	}
	
	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_UnableAppointMyself));
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, szText );
	
	return true;
}
// Button
bool CUI_ID_FRAME_GuildSQ::ID_BUTTON_RefuseOnButtonClick( ControlObject* pSender )
{
	//玩家拒绝申请
	int nIndex = m_pID_LIST_MEMBER->GetCurSelIndex();
	if (nIndex == -1 || nIndex >= m_MemberList.size())
	{
		ShowSelectNothingMessage();
		return false;
	}
	if (IsOperateOnMyself(m_MemberList[nIndex].ID))
	{
		return false;
	}
	MsgRequestJoinGuildAck msg;
	msg.nPlayerID = m_MemberList[nIndex].ID;
	msg.bAgreeJoin = false;
	GettheNetworkInput().SendMsg( &msg );
	return true;
}
// 装载UI
bool CUI_ID_FRAME_GuildSQ::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GuildSQ.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GuildSQ.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GuildSQ::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GuildSQ, s_CUI_ID_FRAME_GuildSQOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GuildSQ, s_CUI_ID_FRAME_GuildSQOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GuildSQ, ID_BUTTON_Index, s_CUI_ID_FRAME_GuildSQID_BUTTON_IndexOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildSQ, ID_BUTTON_Profession, s_CUI_ID_FRAME_GuildSQID_BUTTON_ProfessionOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildSQ, ID_BUTTON_Level, s_CUI_ID_FRAME_GuildSQID_BUTTON_LevelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildSQ, ID_BUTTON_Name, s_CUI_ID_FRAME_GuildSQID_BUTTON_NameOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_GuildSQ, ID_LIST_Index, s_CUI_ID_FRAME_GuildSQID_LIST_IndexOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildSQ, ID_LIST_Profession, s_CUI_ID_FRAME_GuildSQID_LIST_ProfessionOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildSQ, ID_LIST_Level, s_CUI_ID_FRAME_GuildSQID_LIST_LevelOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildSQ, ID_LIST_Name, s_CUI_ID_FRAME_GuildSQID_LIST_NameOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_GuildSQ, ID_BUTTON_Accept, s_CUI_ID_FRAME_GuildSQID_BUTTON_AcceptOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildSQ, ID_BUTTON_Refuse, s_CUI_ID_FRAME_GuildSQID_BUTTON_RefuseOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_GuildSQ, ID_LIST_MEMBER, s_CUI_ID_FRAME_GuildSQID_LIST_MEMBEROnListSelectChange );

	m_pID_FRAME_GuildSQ = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GuildSQ );
	m_pID_BUTTON_Index = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildSQ, ID_BUTTON_Index );
	m_pID_BUTTON_Profession = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildSQ, ID_BUTTON_Profession );
	m_pID_BUTTON_Level = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildSQ, ID_BUTTON_Level );
	m_pID_BUTTON_Name = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildSQ, ID_BUTTON_Name );
	m_pID_TEXT_Index = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildSQ, ID_TEXT_Index );
	m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildSQ, ID_TEXT_Name );
	m_pID_TEXT_Level = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildSQ, ID_TEXT_Level );
	m_pID_TEXT_Profession = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildSQ, ID_TEXT_Profession );
	m_pID_LIST_Index = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildSQ, ID_LIST_Index );
	m_pID_LIST_Profession = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildSQ, ID_LIST_Profession );
	m_pID_LIST_Level = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildSQ, ID_LIST_Level );
	m_pID_LIST_Name = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildSQ, ID_LIST_Name );
	m_pID_BUTTON_Accept = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildSQ, ID_BUTTON_Accept );
	m_pID_BUTTON_Refuse = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildSQ, ID_BUTTON_Refuse );
	m_pID_LIST_MEMBER = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildSQ, ID_LIST_MEMBER );
	assert( m_pID_FRAME_GuildSQ );
	assert( m_pID_BUTTON_Index );
	assert( m_pID_BUTTON_Profession );
	assert( m_pID_BUTTON_Level );
	assert( m_pID_BUTTON_Name );
	assert( m_pID_TEXT_Index );
	assert( m_pID_TEXT_Name );
	assert( m_pID_TEXT_Level );
	assert( m_pID_TEXT_Profession );
	assert( m_pID_LIST_Index );
	assert( m_pID_LIST_Profession );
	assert( m_pID_LIST_Level );
	assert( m_pID_LIST_Name );
	assert( m_pID_BUTTON_Accept );
	assert( m_pID_BUTTON_Refuse );
	assert( m_pID_LIST_MEMBER );

	InitArrowArray();
	SetSkipAllMsg();

	m_pID_FRAME_GuildSQ->SetFather(s_CUI_ID_FRAME_GuildBaseInfo.GetFrame());

	SetVisable(false);
	return true;
}
	// 卸载UI
bool CUI_ID_FRAME_GuildSQ::_UnLoadUI()
{
	m_pID_FRAME_GuildSQ = NULL;
	ClearGuildMemberInfo();
	return theUiManager.RemoveFrame( "Data\\UI\\GuildSQ.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GuildSQ::_IsVisable()
{
	return m_pID_FRAME_GuildSQ->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GuildSQ::_SetVisable( const bool bVisable )
{
	if(bVisable)
		OnShow();
	m_pID_FRAME_GuildSQ->SetVisable( bVisable );
}
void CUI_ID_FRAME_GuildSQ::OnUpdateUiInfo()
{
	if(!IsVisable())
		return;
	else
	{
		//更新Ui上的全部值
		OnShow();
	}
}
void CUI_ID_FRAME_GuildSQ::OnShow()
{
	//当Ui显示的时候
	if(m_IsNeedUpdate)
	{
		//更新UI上的数据
		SetGuildMemberInfo();
		m_IsNeedUpdate = false;
	}
}
void CUI_ID_FRAME_GuildSQ::AddGuildMember(GuildSQInfo& pGuildMember)
{	
	//添加一个申请 保存到客户端
	m_MemberList.push_back(pGuildMember);
	m_IsNeedUpdate = true;
}
void CUI_ID_FRAME_GuildSQ::DelGuildMember(uint32 ID)
{
	//移除数据
	if(m_MemberList.empty()) return;
	vector<GuildSQInfo>::iterator Iter =m_MemberList.begin();
	for(;Iter != m_MemberList.end();++Iter)
	{
		if(Iter->ID == ID)
		{
			m_MemberList.erase(Iter);
			m_IsNeedUpdate = true;
			return;
		}
	}
}
void CUI_ID_FRAME_GuildSQ::ClearGuildMemberInfo()
{
	if(m_MemberList.empty()) return;
	m_MemberList.clear();
	m_IsNeedUpdate = true;
}
void CUI_ID_FRAME_GuildSQ::AddGuildMenberList(GuildSQInfo* pGuildMember,uint32 Num)
{
	for(size_t i =0;i<Num;++i)
	{
		m_MemberList.push_back(pGuildMember[i]);
	}
	m_IsNeedUpdate = true;
}
void CUI_ID_FRAME_GuildSQ::SetSortFunc(SortType ekey)
{
	if (ekey < 0 || ekey >= ekey_max)
	{
		return;
	}

	m_key = ekey;
	m_bArrow[m_key] = !m_bArrow[m_key];
	if (m_bArrow[m_key])
	{
		m_currentSortFunc = m_funcSort[m_key];
	}
	else
	{
		m_currentSortFunc = m_funcSortReverse[m_key];
	}
	SetGuildMemberInfo();
}

bool CUI_ID_FRAME_GuildSQ::SortByID(GuildSQInfo lhs, GuildSQInfo rhs)
{
	return lhs.ID< rhs.ID;
}
bool CUI_ID_FRAME_GuildSQ::SortByName(GuildSQInfo lhs, GuildSQInfo rhs)
{
	return strlen(lhs.Name) < strlen(rhs.Name);
}

bool CUI_ID_FRAME_GuildSQ::SortByLevel(GuildSQInfo lhs, GuildSQInfo rhs)
{
	return lhs.Level < rhs.Level;
}

bool CUI_ID_FRAME_GuildSQ::SortByProfession( GuildSQInfo lhs, GuildSQInfo rhs )
{
	return lhs.Profession < rhs.Profession;
}

bool CUI_ID_FRAME_GuildSQ::SortByID_Reverse(GuildSQInfo lhs, GuildSQInfo rhs)
{
	  return lhs.ID < rhs.ID;
}
bool CUI_ID_FRAME_GuildSQ::SortByName_Reverse(GuildSQInfo lhs, GuildSQInfo rhs)
{
	return strlen(lhs.Name) > strlen(rhs.Name);
}

bool CUI_ID_FRAME_GuildSQ::SortByLevel_Reverse(GuildSQInfo lhs, GuildSQInfo rhs)
{
	return lhs.Level > rhs.Level;
}

bool CUI_ID_FRAME_GuildSQ::SortByProfession_Reverse( GuildSQInfo lhs, GuildSQInfo rhs )
{
	return lhs.Profession > rhs.Profession;
}
void CUI_ID_FRAME_GuildSQ::ShowSortArrow()
{
	if (m_key < 0 || m_key >= ekey_max)
	{
		return;
	}
	for (int i = 0; i < ekey_max; ++i)
	{
		m_pID_TEXT_Arrow[i]->SetVisable( false);
	}
	m_pID_TEXT_Arrow[m_key]->SetVisable(true);
	
	if (!m_bArrow[m_key])
	{
		m_pID_TEXT_Arrow[m_key]->SetText("{#204}");
	}
	else
	{
		m_pID_TEXT_Arrow[m_key]->SetText("{#203}");
	}
}
void CUI_ID_FRAME_GuildSQ::SetGuildMemberInfo()
{
	//将公会玩家的信息设置到UI上面去 包括排序
	ShowSortArrow();//设置text的状态
	SortAndRefresh();//列表排序
	SetAllList();//加载到List上去
}
void CUI_ID_FRAME_GuildSQ::SortAndRefresh()
{
	if (!m_currentSortFunc)
	{
		return;
	}
	//获取在线 和不在线的玩家 并且对集合进行排序
	std::stable_sort(m_MemberList.begin(), m_MemberList.end(), m_currentSortFunc);
}
void CUI_ID_FRAME_GuildSQ::SetAllList()
{
	ClearAllList();
	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if(pGuild == NULL || pGuild->GetGuildID() == GuildDefine::InitID)
		return;
	if(m_MemberList.empty()) return;
	vector<GuildSQInfo>::iterator Iter = m_MemberList.begin();
	DWORD color = 0;
	for(;Iter != m_MemberList.end();++Iter)
	{
		AddToList(*Iter, color);
	}
}
void CUI_ID_FRAME_GuildSQ::InitArrowArray()
{
	m_pID_TEXT_Arrow[ekey_id] = m_pID_TEXT_Index;
	m_pID_TEXT_Arrow[ekey_name] = m_pID_TEXT_Name;
	m_pID_TEXT_Arrow[ekey_level] = m_pID_TEXT_Level;
	m_pID_TEXT_Arrow[ekey_profession] = m_pID_TEXT_Profession;
}
void CUI_ID_FRAME_GuildSQ::SetSkipAllMsg()
{
	if (_IsVisable())
	{
		m_pID_LIST_Index->SetSkipAllMsg(true);
		m_pID_LIST_Profession->SetSkipAllMsg(true);
		m_pID_LIST_Level->SetSkipAllMsg(true);
		m_pID_LIST_Name->SetSkipAllMsg(true);
	}
}
void CUI_ID_FRAME_GuildSQ::ResetSortMember()
{
	for (int i = 0; i < ekey_max; ++i)
	{
		m_bArrow[i] = false;
		
	}
	m_key = ekey_name;
	m_bArrow[m_key] = true;
	m_currentSortFunc = m_funcSort[m_key];
}
void CUI_ID_FRAME_GuildSQ::ClearAllList()
{
	m_pID_LIST_MEMBER->Clear();
	m_pID_LIST_Index->Clear();
	m_pID_LIST_Profession->Clear();
	m_pID_LIST_Level->Clear();
	m_pID_LIST_Name->Clear();
}
void CUI_ID_FRAME_GuildSQ::AddToList(GuildSQInfo& pMember, DWORD color)//将一个公会成员的数据加入到List里面去
{
	ControlList::S_List	stItem;
	char szText[128] = {0};
	stItem.SetData( "" );
	m_pID_LIST_MEMBER->AddItem(&stItem, NULL, false);
	stItem.clear();
	
	//ID
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d", pMember.ID);
	stItem.SetData(szText, 0, NULL, color);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Index->AddItem(&stItem, NULL, false);
	stItem.clear();
	memset(szText, 0, sizeof(szText));

	//名字
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%s", pMember.Name);
	stItem.SetData(szText, 0, NULL, color);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Name->AddItem(&stItem, NULL, false);
	stItem.clear();
	memset(szText, 0, sizeof(szText));

	//等级
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d", pMember.Level);
	stItem.SetData(szText, 0, NULL, color);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Level->AddItem(&stItem, NULL, false);
	stItem.clear();
	memset(szText, 0, sizeof(szText));

	//职业
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%s", GetProfessionByID(pMember.Profession));
	stItem.SetData(szText, 0, NULL, color);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Profession->AddItem(&stItem, NULL, false);
	stItem.clear();
	memset(szText, 0, sizeof(szText));
}
const char* CUI_ID_FRAME_GuildSQ::GetProfessionByID(int nProfessionID) const 
{
	switch(nProfessionID)
	{
	case EArmType_Warrior:
		return theXmlString.GetString(eProfession_Warrior);
	case EArmType_Assassin:
		return theXmlString.GetString( eProfession_Assassin );
	case EArmType_Mage:
		return theXmlString.GetString( eProfession_Mage );
	case  EArmType_Taoist:
		return theXmlString.GetString( eProfession_Taoist );
	case EArmType_Hunter:
		return theXmlString.GetString( eProfession_Hunter );
	default:
		return "";
	}
}
void CUI_ID_FRAME_GuildSQ::InitAllSortFunc()
{
	m_funcSort[ekey_name] = SortByName;
	m_funcSort[ekey_level] = SortByLevel;
	m_funcSort[ekey_profession] = SortByProfession;
	m_funcSort[ekey_id] = SortByID;


	m_funcSortReverse[ekey_name] = SortByName_Reverse;
	m_funcSortReverse[ekey_level] = SortByLevel_Reverse;
	m_funcSortReverse[ekey_profession] = SortByProfession_Reverse;
	m_funcSortReverse[ekey_id] = SortByID_Reverse;
}