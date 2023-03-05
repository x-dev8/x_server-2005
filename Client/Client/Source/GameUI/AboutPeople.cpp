/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (7)\AboutPeople.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ui/RbtnMenu.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "PlayerRole.h"
#include "GameMain.h"
#include "AboutPeople.h"
#include "XmlStringLanguage.h"
#include "GameDefineChar.h"
#include "color_config.h"

CUI_ID_FRAME_AboutPeople s_CUI_ID_FRAME_AboutPeople;

bool CUI_ID_FRAME_AboutPeople::s_Up = false;

MAP_FRAME_RUN( s_CUI_ID_FRAME_AboutPeople, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_AboutPeople, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AboutPeople, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AboutPeople, ID_BUTTON_CLOSEOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_AboutPeople, ID_LIST_TeamNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_AboutPeople, ID_LIST_PeopleNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_AboutPeople, ID_LIST_LVOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_AboutPeople, ID_LIST_JobOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_AboutPeople, ID_LIST_TeamEffectOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AboutPeople, ID_BUTTON_FriendOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AboutPeople, ID_BUTTON_FoeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AboutPeople, ID_BUTTON_TeamOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AboutPeople, ID_BUTTON_NameOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AboutPeople, ID_BUTTON_LVOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AboutPeople, ID_BUTTON_JobOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AboutPeople, ID_CHECKBOX_FriendOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AboutPeople, ID_CHECKBOX_FoeOnCheckBoxCheck )
CUI_ID_FRAME_AboutPeople::CUI_ID_FRAME_AboutPeople()
{
	// Member
	m_pID_FRAME_AboutPeople = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_LIST_TeamName = NULL;
	m_pID_LIST_PeopleName = NULL;
	m_pID_LIST_LV = NULL;
	m_pID_LIST_Job = NULL;
	m_pID_LIST_TeamEffect = NULL;
	m_pID_BUTTON_Team = NULL;
	m_pID_BUTTON_Name = NULL;
	m_pID_BUTTON_LV = NULL;
	m_pID_BUTTON_Job = NULL;
	m_pID_TEXT_Team = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_LV = NULL;
	m_pID_TEXT_Job = NULL;
	m_pID_CHECKBOX_Friend = NULL;
	m_pID_CHECKBOX_Foe = NULL;
}

// Frame
bool CUI_ID_FRAME_AboutPeople::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_AboutPeople::OnFrameRender()
{
	ControlScrollBar* pBar = m_pID_LIST_TeamEffect->GetScrollBar();
	if(pBar)
	{
		int nValue = pBar->GetValue();

		m_pID_LIST_TeamName->SetScrollValue(nValue);
		m_pID_LIST_PeopleName->SetScrollValue(nValue);
		m_pID_LIST_LV->SetScrollValue(nValue);
		m_pID_LIST_Job->SetScrollValue(nValue);
	}

	return true;
}
// Button
bool CUI_ID_FRAME_AboutPeople::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_AboutPeople )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_AboutPeople::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_AboutPeople )
		return false;
	return true;
}
// List
void CUI_ID_FRAME_AboutPeople::ID_LIST_TeamNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_AboutPeople )
		return;
}
// List
void CUI_ID_FRAME_AboutPeople::ID_LIST_PeopleNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_AboutPeople )
		return;
}
// List
void CUI_ID_FRAME_AboutPeople::ID_LIST_LVOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_AboutPeople )
		return;
}
// List
void CUI_ID_FRAME_AboutPeople::ID_LIST_JobOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_AboutPeople )
		return;
}
// List
void CUI_ID_FRAME_AboutPeople::ID_LIST_TeamEffectOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_AboutPeople )
		return;
}
// Button
bool CUI_ID_FRAME_AboutPeople::ID_BUTTON_FriendOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_AboutPeople )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_AboutPeople::ID_BUTTON_FoeOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_AboutPeople )
		return false;
	return true;
}

// Button
bool CUI_ID_FRAME_AboutPeople::ID_BUTTON_TeamOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_AboutPeople )
		return false;

	SortListByType(Sort_Team);
	return true;
}

// Button
bool CUI_ID_FRAME_AboutPeople::ID_BUTTON_NameOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_AboutPeople )
		return false;

	SortListByType(Sort_Name);
	return true;
}

// Button
bool CUI_ID_FRAME_AboutPeople::ID_BUTTON_LVOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_AboutPeople )
		return false;

	SortListByType(Sort_LV);
	return true;
}

// Button
bool CUI_ID_FRAME_AboutPeople::ID_BUTTON_JobOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_AboutPeople )
		return false;

	SortListByType(Sort_Job);
	return true;
}

// CheckBox
void CUI_ID_FRAME_AboutPeople::ID_CHECKBOX_FriendOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_AboutPeople )
		return;

	SetListType(List_Friend);
	ClearList();
	RefreshPlayerInfo();
}

// CheckBox
void CUI_ID_FRAME_AboutPeople::ID_CHECKBOX_FoeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_AboutPeople )
		return;

	SetListType(List_Enemy);
	ClearList();
	RefreshPlayerInfo();
}

// 装载UI
bool CUI_ID_FRAME_AboutPeople::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\AboutPeople.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\AboutPeople.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_AboutPeople::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_AboutPeople, s_CUI_ID_FRAME_AboutPeopleOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_AboutPeople, s_CUI_ID_FRAME_AboutPeopleOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_AboutPeople, ID_BUTTON_HELP, s_CUI_ID_FRAME_AboutPeopleID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_AboutPeople, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_AboutPeopleID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_AboutPeople, ID_LIST_TeamName, s_CUI_ID_FRAME_AboutPeopleID_LIST_TeamNameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_AboutPeople, ID_LIST_PeopleName, s_CUI_ID_FRAME_AboutPeopleID_LIST_PeopleNameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_AboutPeople, ID_LIST_LV, s_CUI_ID_FRAME_AboutPeopleID_LIST_LVOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_AboutPeople, ID_LIST_Job, s_CUI_ID_FRAME_AboutPeopleID_LIST_JobOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_AboutPeople, ID_LIST_TeamEffect, s_CUI_ID_FRAME_AboutPeopleID_LIST_TeamEffectOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_AboutPeople, ID_BUTTON_Team, s_CUI_ID_FRAME_AboutPeopleID_BUTTON_TeamOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_AboutPeople, ID_BUTTON_Name, s_CUI_ID_FRAME_AboutPeopleID_BUTTON_NameOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_AboutPeople, ID_BUTTON_LV, s_CUI_ID_FRAME_AboutPeopleID_BUTTON_LVOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_AboutPeople, ID_BUTTON_Job, s_CUI_ID_FRAME_AboutPeopleID_BUTTON_JobOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_AboutPeople, ID_CHECKBOX_Friend, s_CUI_ID_FRAME_AboutPeopleID_CHECKBOX_FriendOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_AboutPeople, ID_CHECKBOX_Foe, s_CUI_ID_FRAME_AboutPeopleID_CHECKBOX_FoeOnCheckBoxCheck );

	m_pID_FRAME_AboutPeople = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_AboutPeople );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_AboutPeople, ID_BUTTON_HELP );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_AboutPeople, ID_BUTTON_CLOSE );
	m_pID_LIST_TeamName = (ControlList*)theUiManager.FindControl( ID_FRAME_AboutPeople, ID_LIST_TeamName );
	m_pID_LIST_PeopleName = (ControlList*)theUiManager.FindControl( ID_FRAME_AboutPeople, ID_LIST_PeopleName );
	m_pID_LIST_LV = (ControlList*)theUiManager.FindControl( ID_FRAME_AboutPeople, ID_LIST_LV );
	m_pID_LIST_Job = (ControlList*)theUiManager.FindControl( ID_FRAME_AboutPeople, ID_LIST_Job );
	m_pID_LIST_TeamEffect = (ControlList*)theUiManager.FindControl( ID_FRAME_AboutPeople, ID_LIST_TeamEffect );
	m_pID_BUTTON_Team = (ControlButton*)theUiManager.FindControl( ID_FRAME_AboutPeople, ID_BUTTON_Team );
	m_pID_BUTTON_Name = (ControlButton*)theUiManager.FindControl( ID_FRAME_AboutPeople, ID_BUTTON_Name );
	m_pID_BUTTON_LV = (ControlButton*)theUiManager.FindControl( ID_FRAME_AboutPeople, ID_BUTTON_LV );
	m_pID_BUTTON_Job = (ControlButton*)theUiManager.FindControl( ID_FRAME_AboutPeople, ID_BUTTON_Job );
	m_pID_TEXT_Team = (ControlText*)theUiManager.FindControl( ID_FRAME_AboutPeople, ID_TEXT_Team );
	m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_AboutPeople, ID_TEXT_Name );
	m_pID_TEXT_LV = (ControlText*)theUiManager.FindControl( ID_FRAME_AboutPeople, ID_TEXT_LV );
	m_pID_TEXT_Job = (ControlText*)theUiManager.FindControl( ID_FRAME_AboutPeople, ID_TEXT_Job );
	m_pID_CHECKBOX_Friend = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AboutPeople, ID_CHECKBOX_Friend );
	m_pID_CHECKBOX_Foe = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AboutPeople, ID_CHECKBOX_Foe );

	assert( m_pID_FRAME_AboutPeople );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_LIST_TeamName );
	assert( m_pID_LIST_PeopleName );
	assert( m_pID_LIST_LV );
	assert( m_pID_LIST_Job );
	assert( m_pID_LIST_TeamEffect );
	assert( m_pID_BUTTON_Team );
	assert( m_pID_BUTTON_Name );
	assert( m_pID_BUTTON_LV );
	assert( m_pID_BUTTON_Job );
	assert( m_pID_TEXT_Team );
	assert( m_pID_TEXT_Name );
	assert( m_pID_TEXT_LV );
	assert( m_pID_TEXT_Job );
	assert( m_pID_CHECKBOX_Friend );
	assert( m_pID_CHECKBOX_Foe );


	m_pID_LIST_TeamEffect->SetRBClickFun(ID_List_OnRBClick);
	m_pID_LIST_Job->SetMsgHoldup(false);
	m_pID_LIST_LV->SetMsgHoldup(false);
	m_pID_LIST_TeamName->SetMsgHoldup(false);
	m_pID_LIST_PeopleName->SetMsgHoldup(false);

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_AboutPeople::_UnLoadUI()
{
	m_pID_FRAME_AboutPeople = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_LIST_TeamName = NULL;
	m_pID_LIST_PeopleName = NULL;
	m_pID_LIST_LV = NULL;
	m_pID_LIST_Job = NULL;
	m_pID_LIST_TeamEffect = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\AboutPeople.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_AboutPeople::_IsVisable()
{
	if ( !m_pID_FRAME_AboutPeople )
		return false;
	return m_pID_FRAME_AboutPeople->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_AboutPeople::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_AboutPeople )
		return;
	m_pID_FRAME_AboutPeople->SetVisable( bVisable );

	if(bVisable)
	{
		m_eSortType = Sort_None;
		s_Up = false;

		ClearList();
		InitialActivePlayerList();
		SetListType(List_Friend);

		SortListByType(Sort_LV);  //默认按等级排序
	}
}

void CUI_ID_FRAME_AboutPeople::ID_List_OnRBClick(ControlObject* pSender, ControlList::S_List* pItem)
{
	int x,y;
	x = theUiManager.m_ptMoust.x;
	y = theUiManager.m_ptMoust.y;

	ControlList::S_List* item = s_CUI_ID_FRAME_AboutPeople.m_pID_LIST_PeopleName->GetListItem( s_CUI_ID_FRAME_AboutPeople.m_pID_LIST_TeamEffect->GetCurSelIndex() );
	if ( !item )
	{
		return;
	}
	
	//s_CUI_ID_FRAME_RBTNMENU.SetPlayerID( player->GetID() );
	s_CUI_ID_FRAME_RBTNMENU.SetPrivateName(  item->m_szText );
	s_CUI_ID_FRAME_RBTNMENU.SetVisable( true );
	s_CUI_ID_FRAME_RBTNMENU.SetPos( x, y );
	if( s_CUI_ID_FRAME_RBTNMENU.GetFrame() )
		theUiManager.ToTop( s_CUI_ID_FRAME_RBTNMENU.GetFrame() );
	theUiManager.Compositor();
}

void CUI_ID_FRAME_AboutPeople::ClearList()
{
	if(!m_pID_FRAME_AboutPeople)
		return;

	m_pID_LIST_TeamName->Clear();
	m_pID_LIST_PeopleName->Clear();
	m_pID_LIST_LV->Clear();
	m_pID_LIST_Job->Clear();
	m_pID_LIST_TeamEffect->Clear();
}

void CUI_ID_FRAME_AboutPeople::AddToList( const char* teamName, const char* playerName, const char* level, const char* professional, const DWORD clr )
{
	if ( !teamName || !playerName || !level || !professional )
	{
		return;
	}

	ControlList::S_List	stItem;

	//队伍名称
	DWORD dwColor = 0xffffffff;
	if(strcmp(teamName,theXmlString.GetString(eText_NearPlayerNoTeam)) == 0)
		dwColor = Color_Config.getColor(CC_NearPlayerNoTeam);
	else
		dwColor = Color_Config.getColor(CC_NearPlayerTeam);

	stItem.SetData(teamName, 0, NULL, dwColor);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_TeamName->AddItem(&stItem, NULL, false);
	stItem.clear();

	//玩家昵称
	stItem.SetData(playerName, 0, NULL, clr);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_PeopleName->AddItem(&stItem, NULL, false);
	stItem.clear();

	//等级
	stItem.SetData(level, 0, NULL, clr);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_LV->AddItem(&stItem, NULL, false);
	stItem.clear();

	//职业
	stItem.SetData(professional, 0, NULL, clr);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Job->AddItem(&stItem, NULL, false);
	stItem.clear();

	//选择效果列表，不显示内容
	stItem.SetData(" ", 0, NULL, clr);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_TeamEffect->AddItem(&stItem, NULL, false);
	stItem.clear();
}

void CUI_ID_FRAME_AboutPeople::InitialActivePlayerList()
{
	m_vecSet.clear();
	std::map< GameObjectId, CPlayer* > mapPlayers = theHeroGame.GetPlayerMgr()->m_mapPlayers;
	for ( std::map< GameObjectId, CPlayer* >::iterator it = mapPlayers.begin(); it != mapPlayers.end(); it ++ )
	{
		if ( it->second->GetCharType() != Object_Player   
			|| it->second == theHeroGame.GetPlayerMgr()->GetMe() )
		{
			continue;
		}

		m_vecSet.push_back(it->second);
	}
}

const char* CUI_ID_FRAME_AboutPeople::GetMPTypeString( int nProfession )
{
	switch( nProfession )
	{
	case EArmType_Warrior:
		return theXmlString.GetString( eProfession_Warrior );
		break;
	case EArmType_Mage:
		return theXmlString.GetString( eProfession_Mage );
		break;
	case EArmType_Taoist:
		return theXmlString.GetString( eProfession_Taoist );
		break;
	case EArmType_Assassin:
		return theXmlString.GetString( eProfession_Assassin );
		break;
	case EArmType_Hunter:
		return theXmlString.GetString( eProfession_Hunter );
		break;
	case EArmType_Sniper:
		return theXmlString.GetString( eProfession_Hunter );//TODO以后加个火枪字符串上去
		break;
	}
	return theXmlString.GetString( eProfession_Unknown );
}

void CUI_ID_FRAME_AboutPeople::SetListType(ListType eType)
{
	m_eType = eType;
	if(!m_pID_FRAME_AboutPeople)
		return;

	m_pID_CHECKBOX_Foe->SetCheck(false);
	m_pID_CHECKBOX_Friend->SetCheck(false);

	switch(m_eType)
	{
	case List_Friend:
		m_pID_CHECKBOX_Friend->SetCheck(true);
		break;
	case List_Enemy:
		{
			m_pID_CHECKBOX_Foe->SetCheck(true);
		}
		break;
	default:
		break;
	}
}

void CUI_ID_FRAME_AboutPeople::RefreshPlayerInfo()
{
	if(!m_pID_FRAME_AboutPeople)
		return;

	m_pID_LIST_TeamEffect->SetScrollValue(0);
	for (int i = 0;i < m_vecSet.size();++i)
	{
		CPlayer* pPlayer = m_vecSet[i];
		if(!pPlayer)
			continue;

		if(!IsCanShow(m_eType,pPlayer))
			continue;

		std::string teamName = "";
		std::string playerName = "";
		std::string playerLvl = "";
		std::string playerPro = "";
		//TeamInfo* tInfo = thePlayerRole.GetTeamInfo(it->second->GetTeamId());
		uint32 teamId = pPlayer->GetTeamId();
		if ( teamId == 0 )	//无teamid,表明没有队伍
		{
			teamName = theXmlString.GetString(eText_NearPlayerNoTeam);
		}
		else
		{
			teamName = theXmlString.GetString(eText_NearPlayerTeam);
		}
		playerName = pPlayer->GetName();

		char strLvl[64] = {0};
		sprintf( strLvl, "%d", (int)pPlayer->GetLevel() );
		playerLvl = strLvl;

		playerPro = this->GetMPTypeString(pPlayer->GetProfession());
		this->AddToList( teamName.c_str(), playerName.c_str(), playerLvl.c_str(), playerPro.c_str(), 0xFFFFFFFF );
	}
}

bool CUI_ID_FRAME_AboutPeople::IsCanShow(ListType eType,CPlayer* pPlayer)
{
	if(eType == List_None || !pPlayer)
		return false;

	if(eType == List_Friend && IsEnemy(pPlayer))
		return false;

	if(eType == List_Enemy && !IsEnemy(pPlayer))
		return false;

	return true;
}

bool CUI_ID_FRAME_AboutPeople::IsEnemy(CPlayer *pPlayer)
{
	if(!pPlayer)
		return false;

	//黑名单中不加
	if(thePlayerRole.isFrdInBlackList(pPlayer->GetCharacterID()))
		return true;

	//仇人
	if(thePlayerRole.isChouRen(pPlayer->GetName()))
		return true;

	//PK值大于0
	/*if(pPlayer->GetPKKillValue() > 0)
		return true;*/

	return false;
}

bool CUI_ID_FRAME_AboutPeople::SortByName(CPlayer* pPlayer1,CPlayer* pPlayer2)
{
	if(s_Up)
	{
		if(strcmp(pPlayer1->GetName(),pPlayer2->GetName()) > 0)
			return true;
	}
	else
	{
		if(strcmp(pPlayer1->GetName(),pPlayer2->GetName()) < 0)
			return true;
	}

	return false;
}

bool CUI_ID_FRAME_AboutPeople::SortByTeam(CPlayer* pPlayer1,CPlayer* pPlayer2)
{
	if(s_Up)
	{
		if(pPlayer1->GetTeamId() > pPlayer2->GetTeamId())
			return true;
	}
	else
	{
		if(pPlayer1->GetTeamId() < pPlayer2->GetTeamId())
			return true;
	}

	return false;
}

bool CUI_ID_FRAME_AboutPeople::SortByLV(CPlayer* pPlayer1,CPlayer* pPlayer2)
{
	if(s_Up)
	{
		if(pPlayer1->GetLevel() > pPlayer2->GetLevel())
			return true;
	}
	else
	{
		if(pPlayer1->GetLevel() < pPlayer2->GetLevel())
			return true;
	}

	return false;
}

bool CUI_ID_FRAME_AboutPeople::SortByJob(CPlayer* pPlayer1,CPlayer* pPlayer2)
{
	if(s_Up)
	{
		if(pPlayer1->GetProfession() > pPlayer2->GetProfession())
			return true;
	}
	else
	{
		if(pPlayer1->GetProfession() < pPlayer2->GetProfession())
			return true;
	}

	return false;
}

void CUI_ID_FRAME_AboutPeople::SortListByType(SortType eType)
{
	if(m_eSortType == eType)
		s_Up = !s_Up;
	else
		s_Up = false;
	
	m_eSortType = eType;

	switch(eType)
	{
	case Sort_None:
		{
			//std::sort(m_vecSet.begin(),m_vecSet.end(),SortByName);
		}
		break;
	case Sort_Name:
		{
			std::sort(m_vecSet.begin(),m_vecSet.end(),SortByName);

		}
		break;
	case Sort_Team:
		{
			std::sort(m_vecSet.begin(),m_vecSet.end(),SortByTeam);

		}
		break;
	case Sort_LV:
		{
			std::sort(m_vecSet.begin(),m_vecSet.end(),SortByLV);

		}
		break;
	case Sort_Job:
		{
			std::sort(m_vecSet.begin(),m_vecSet.end(),SortByJob);

		}
		break;
	default:
		break;
	}

	ClearList();
	RefreshPlayerInfo();
	SetSortTypeInUi(m_eSortType);
}

void CUI_ID_FRAME_AboutPeople::SetSortTypeInUi(SortType eType)
{
	m_pID_TEXT_Name->Clear();
	m_pID_TEXT_Team->Clear();
	m_pID_TEXT_LV->Clear();
	m_pID_TEXT_Job->Clear();
	switch(eType)
	{
	case Sort_None:
		{

		}
		break;
	case Sort_Name:
		{
			if(s_Up)
				m_pID_TEXT_Name->SetText("{#203}");
			else
				m_pID_TEXT_Name->SetText("{#204}");
		}
		break;
	case Sort_Team:
		{
			if(s_Up)
				m_pID_TEXT_Team->SetText("{#203}");
			else
				m_pID_TEXT_Team->SetText("{#204}");
		}
		break;
	case Sort_LV:
		{
			if(s_Up)
				m_pID_TEXT_LV->SetText("{#203}");
			else
				m_pID_TEXT_LV->SetText("{#204}");
		}
		break;
	case Sort_Job:
		{
			if(s_Up)
				m_pID_TEXT_Job->SetText("{#203}");
			else
				m_pID_TEXT_Job->SetText("{#204}");
		}
		break;
	}
}