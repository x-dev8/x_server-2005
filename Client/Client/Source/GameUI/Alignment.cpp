/********************************************************************
Created by UIEditor.exe
FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\Alignment.cpp
*********************************************************************/
#include <assert.h>
#include "GameMain.h"
#include "GlobalDef.h"
#include "UIMgr.h"
#include "MeUi/UiManager.h"
//#include "Alignment.h"
#include "XmlStringLanguage.h"
#include "PlayerRole.h"
#include "..\PlayerMgr.h"
#include "Player.h"
// #include "Guild_RbMenu.h"
#include "Gang.h"
#include "AddMember.h"
#include "Guild.h"
#include "Group_Me.h"
#include "FriendDlg.h"
#include "ChatInfoBox.h"
#include "MessageBox.h"
#include "UIBase.h"
// #include "help.h"
#include "Guild_Pic.h"
// #include "Guild_Exp_Allot.h"
#include "Announce.h"
// #include "Me3d/Me3d_World.h"
#include "SystemConfig.h"
#include "FuncPerformanceLog.h"
#include "NetworkInput.h"
#include "XmlStringLanguage.h"
#include "../color_config.h"
#include "core/Name.h"
#include "RbtnMenu.h"
#include "Target.h"
#include "Task.h"
#include "GroupPanel.h"
#include "ShowScreenText.h"
extern int g_nCharacterDBID;
const int g_nMinActionIntervel = 1800000;
bool SortByName(const GuildInfoEx* v1, const GuildInfoEx* v2)
{
	return strlen(v1->baseInfo.szName) < strlen(v2->baseInfo.szName);
}
bool SortByName_Rev(const GuildInfoEx* v1, const GuildInfoEx* v2)
{
	return strlen(v1->baseInfo.szName) > strlen(v2->baseInfo.szName);
}
bool SortByMasterName(const GuildInfoEx* v1, const GuildInfoEx* v2)
{	
	return strlen(v1->baseInfo.szMasterName) < strlen(v2->baseInfo.szMasterName);
}
bool SortByMasterName_Rev(const GuildInfoEx* v1, const GuildInfoEx* v2)
{
	return strlen(v1->baseInfo.szMasterName) > strlen(v2->baseInfo.szMasterName);
}
bool SortByNumber(const GuildInfoEx* v1, const GuildInfoEx* v2)
{
	return (v1->baseInfo.shMemberNumber) > (v2->baseInfo.shMemberNumber);
}
bool SortByNumber_Rev(const GuildInfoEx* v1, const GuildInfoEx* v2)
{
	return (v1->baseInfo.shMemberNumber) < (v2->baseInfo.shMemberNumber);
}
bool SortByLevel(const GuildInfoEx* v1, const GuildInfoEx* v2)
{
	return (v1->baseInfo.shLevel) > (v2->baseInfo.shLevel);
}
bool SortByLevel_Rev(const GuildInfoEx* v1, const GuildInfoEx* v2)
{
	return (v1->baseInfo.shLevel) < (v2->baseInfo.shLevel);
}

CUI_ID_FRAME_Alignment s_CUI_ID_FRAME_Alignment;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Alignment, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Alignment, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_LIST_GuildListOnListSelectChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_CHECKBOX_FriendOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_CHECKBOX_EnemyOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_BUTTON_InviteOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_EDIT_SearchOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_BUTTON_NextOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_BUTTON_helpOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_CHECKBOX_StrangerOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_BUTTON_GuildNameOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_BUTTON_GuildLeaderOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_BUTTON_NumberOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_LIST_GuildNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_LIST_GuildLeaderOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_LIST_LvlOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_BUTTON_EnemyOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_BUTTON_JieChuOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_BUTTON_YanHeOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_BUTTON_QiangZhiOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_LIST_NumberOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Alignment, ID_BUTTON_GuildLvlOnButtonClick )
CUI_ID_FRAME_Alignment::CUI_ID_FRAME_Alignment()
{
	// Member
	m_pID_FRAME_Alignment = NULL;
	m_pID_PICTURE_Di = NULL;
	m_pID_PICTURE_TitleDi = NULL;
	m_pID_PICTURE_WallPaper = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_LIST_GuildList = NULL;
	m_pID_CHECKBOX_Friend = NULL;
	m_pID_CHECKBOX_Enemy = NULL;
	m_pID_BUTTON_Invite = NULL;
	m_pID_EDIT_Search = NULL;
	m_pID_BUTTON_Next = NULL;
	m_pID_PICTURE_WallLeft2 = NULL;
	m_pID_PICTURE_WallRight2 = NULL;
	m_pID_PICTURE_WallLeft = NULL;
	m_pID_PICTURE_WallRight = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_help = NULL;
	m_pID_CHECKBOX_Stranger = NULL;
	m_pID_TEXT_G = NULL;
	m_pID_BUTTON_GuildName = NULL;
	m_pID_BUTTON_GuildLeader = NULL;
	m_pID_BUTTON_Number = NULL;
	m_pID_LIST_GuildName = NULL;
	m_pID_LIST_GuildLeader = NULL;
	m_pID_LIST_Lvl = NULL;
	m_pID_BUTTON_Enemy = NULL;
	m_pID_BUTTON_JieChu = NULL;
	m_pID_BUTTON_YanHe = NULL;
	m_pID_BUTTON_QiangZhi = NULL;
	m_pID_TEXT_ArrowGuildName = NULL;
	m_pID_TEXT_ArrowGuildLeader = NULL;
	m_pID_TEXT_ArrowNumber = NULL;
	m_pID_TEXT_Wait = NULL;
	m_pID_LIST_Number = NULL;
	m_pID_BUTTON_GuildLvl = NULL;
	m_pID_TEXT_ArrowGuildLvl = NULL;
	nRelationType = GR_NEUTRALISM;
	nSortType = ESLevel;
	m_nGangRight = GuildDefine::Position_Member;
	m_bWaitText = true;
}
// Frame
bool CUI_ID_FRAME_Alignment::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_Alignment::OnFrameRender()
{
	RefreshChildList();
	if(!s_CUI_Guild.IsNeedRefreshAlignment())
	{
		return true;
	}
	RefreshUI();
	return true;
}
// List
void CUI_ID_FRAME_Alignment::ID_LIST_GuildListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// CheckBox
void CUI_ID_FRAME_Alignment::ID_CHECKBOX_FriendOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_Alignment)
	{
		assert(false&&"ui error");
		return ;
	}

	if ( nRelationType != GR_LEAGUE || resultList.size() == 0)
	{
		nRelationType = GR_LEAGUE;
		//UpdateGuildList();
	}		
	m_pID_CHECKBOX_Friend->SetCheck(true);
	m_pID_CHECKBOX_Enemy->SetCheck(false);
	m_pID_CHECKBOX_Stranger->SetCheck(false);
	RefreshOptButton();

}
// CheckBox
void CUI_ID_FRAME_Alignment::ID_CHECKBOX_EnemyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_Alignment)
	{
		assert(false&&"ui error");
		return ;
	}

	if ( nRelationType != GR_ADVERSE || resultList.size() == 0)
	{
		nRelationType = GR_ADVERSE;
		//UpdateGuildList();
	}		
	m_pID_CHECKBOX_Friend->SetCheck(false);
	m_pID_CHECKBOX_Enemy->SetCheck(true);
	m_pID_CHECKBOX_Stranger->SetCheck(false);
	RefreshOptButton();

}
// Button
bool CUI_ID_FRAME_Alignment::ID_BUTTON_InviteOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_Alignment)
	{
		assert(false&&"ui error");
		return false;
	}

	int guildId = GetSelectDBId();
	if (-1 == guildId)
	{
		return false;
	}
	std::map<int,DWORD>::iterator iter = m_InviteTimeMap.find(guildId);
	DWORD currTime = HQ_TimeGetTime();
	if (iter != m_InviteTimeMap.end())
	{
		if (currTime - iter->second < g_nMinActionIntervel)
		{
			GetShowScreenText()->AddInfo( theXmlString.GetString(eOneInvitePerTenMinute), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
			return false;
		}
		else
		{
			iter->second = currTime;
		}
	}
	else
	{
		m_InviteTimeMap.insert(std::map<int,DWORD>::value_type(guildId,currTime));
	}
	//SendRelationChangeMsg(guildId,GR_LEAGUE);
	return true;
}

// Edit
void CUI_ID_FRAME_Alignment::ID_EDIT_SearchOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Button
bool CUI_ID_FRAME_Alignment::ID_BUTTON_NextOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_Alignment::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_Alignment::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
{
	return true;
}
// CheckBox
void CUI_ID_FRAME_Alignment::ID_CHECKBOX_StrangerOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_Alignment)
	{
		assert(false&&"ui error");
		return ;
	}

	if ( nRelationType != GR_NEUTRALISM || resultList.size() == 0)
	{
		nRelationType = GR_NEUTRALISM;
		//UpdateGuildList();
	}		
	m_pID_CHECKBOX_Friend->SetCheck(false);
	m_pID_CHECKBOX_Enemy->SetCheck(false);
	m_pID_CHECKBOX_Stranger->SetCheck(true);
	RefreshOptButton();

}
// Button
bool CUI_ID_FRAME_Alignment::ID_BUTTON_GuildNameOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_Alignment)
	{
		assert(false&&"ui error");
		return false;
	}

	nSortType = ESName;
	ShowSortArrow(ESName);
	UpdateGuildListUI();

	return true;
}
// Button
bool CUI_ID_FRAME_Alignment::ID_BUTTON_GuildLeaderOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_Alignment)
	{
		assert(false&&"ui error");
		return false;
	}

	nSortType = ESLeader;
	ShowSortArrow(ESLeader);
	UpdateGuildListUI();
	return true;
}
// Button
bool CUI_ID_FRAME_Alignment::ID_BUTTON_NumberOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_Alignment)
	{
		assert(false&&"ui error");
		return false;
	}

	nSortType = ESNumber;
	ShowSortArrow(ESNumber);
	UpdateGuildListUI();
	return true;
}
// Button
bool CUI_ID_FRAME_Alignment::ID_BUTTON_GuildLvlOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_Alignment)
	{
		assert(false&&"ui error");
		return false;
	}

	nSortType = ESLevel;
	ShowSortArrow(ESLevel);
	UpdateGuildListUI();
	return true;
}
// List
void CUI_ID_FRAME_Alignment::ID_LIST_GuildNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_Alignment::ID_LIST_GuildLeaderOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_Alignment::ID_LIST_NumberOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// Button
bool CUI_ID_FRAME_Alignment::ID_BUTTON_EnemyOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_Alignment)
	{
		assert(false&&"ui error");
		return false;
	}

	setGuildRelation(GR_ADVERSE);
	return true;
}
// Button
bool CUI_ID_FRAME_Alignment::ID_BUTTON_JieChuOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_Alignment)
	{
		assert(false&&"ui error");
		return false;
	}

	setGuildRelation(GR_NEUTRALISM);
	return true;
}
// Button
bool CUI_ID_FRAME_Alignment::ID_BUTTON_YanHeOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_Alignment)
	{
		assert(false&&"ui error");
		return false;
	}

	int guildId = GetSelectDBId();
	if (-1 == guildId)
	{
		return false;
	}
	std::map<int,DWORD>::iterator iter = m_PeaceTimeMap.find(guildId);
	DWORD currTime = HQ_TimeGetTime();
	if (iter != m_PeaceTimeMap.end())
	{
		if (currTime - iter->second < g_nMinActionIntervel)
		{
			GetShowScreenText()->AddInfo( theXmlString.GetString(eOneDisadversePerTenMinute), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
			return false;
		}
		else
		{
			iter->second = currTime;
		}
	}
	else
	{
		m_PeaceTimeMap.insert(std::map<int,DWORD>::value_type(guildId,currTime));
	}
	//SendRelationChangeMsg(guildId,GR_NEUTRALISM);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_Alignment::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Alignment.MEUI"  ,false, UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Alignment.MEUI]失败")
			return false;
	}
	else if ( dwResult != 1/*文件版本号*/ )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Alignment.MEUI]与源代码版本不一样")
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Alignment::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Alignment, s_CUI_ID_FRAME_AlignmentOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Alignment, s_CUI_ID_FRAME_AlignmentOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_Alignment, ID_LIST_GuildList, s_CUI_ID_FRAME_AlignmentID_LIST_GuildListOnListSelectChange );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Alignment, ID_CHECKBOX_Friend, s_CUI_ID_FRAME_AlignmentID_CHECKBOX_FriendOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Alignment, ID_CHECKBOX_Enemy, s_CUI_ID_FRAME_AlignmentID_CHECKBOX_EnemyOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_Alignment, ID_BUTTON_Invite, s_CUI_ID_FRAME_AlignmentID_BUTTON_InviteOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_Alignment, ID_EDIT_Search, s_CUI_ID_FRAME_AlignmentID_EDIT_SearchOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_Alignment, ID_BUTTON_Next, s_CUI_ID_FRAME_AlignmentID_BUTTON_NextOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Alignment, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_AlignmentID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Alignment, ID_BUTTON_help, s_CUI_ID_FRAME_AlignmentID_BUTTON_helpOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Alignment, ID_CHECKBOX_Stranger, s_CUI_ID_FRAME_AlignmentID_CHECKBOX_StrangerOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_Alignment, ID_BUTTON_GuildName, s_CUI_ID_FRAME_AlignmentID_BUTTON_GuildNameOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Alignment, ID_BUTTON_GuildLeader, s_CUI_ID_FRAME_AlignmentID_BUTTON_GuildLeaderOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Alignment, ID_BUTTON_Number, s_CUI_ID_FRAME_AlignmentID_BUTTON_NumberOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Alignment, ID_LIST_GuildName, s_CUI_ID_FRAME_AlignmentID_LIST_GuildNameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Alignment, ID_LIST_GuildLeader, s_CUI_ID_FRAME_AlignmentID_LIST_GuildLeaderOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Alignment, ID_LIST_Lvl, s_CUI_ID_FRAME_AlignmentID_LIST_LvlOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_Alignment, ID_BUTTON_Enemy, s_CUI_ID_FRAME_AlignmentID_BUTTON_EnemyOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Alignment, ID_BUTTON_JieChu, s_CUI_ID_FRAME_AlignmentID_BUTTON_JieChuOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Alignment, ID_BUTTON_YanHe, s_CUI_ID_FRAME_AlignmentID_BUTTON_YanHeOnButtonClick );
	/*theUiManager.OnButtonClick( ID_FRAME_Alignment, ID_BUTTON_QiangZhi, s_CUI_ID_FRAME_AlignmentID_BUTTON_QiangZhiOnButtonClick );*/
	theUiManager.OnListSelectChange( ID_FRAME_Alignment, ID_LIST_Number, s_CUI_ID_FRAME_AlignmentID_LIST_NumberOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_Alignment, ID_BUTTON_GuildLvl, s_CUI_ID_FRAME_AlignmentID_BUTTON_GuildLvlOnButtonClick );

	m_pID_FRAME_Alignment = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Alignment );
	m_pID_PICTURE_Di = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Alignment, ID_PICTURE_Di );
	m_pID_PICTURE_TitleDi = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Alignment, ID_PICTURE_TitleDi );
	m_pID_PICTURE_WallPaper = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Alignment, ID_PICTURE_WallPaper );
	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_Alignment, ID_TEXT_Title );
	m_pID_LIST_GuildList = (ControlList*)theUiManager.FindControl( ID_FRAME_Alignment, ID_LIST_GuildList );
	m_pID_CHECKBOX_Friend = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Alignment, ID_CHECKBOX_Friend );
	m_pID_CHECKBOX_Enemy = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Alignment, ID_CHECKBOX_Enemy );
	m_pID_BUTTON_Invite = (ControlButton*)theUiManager.FindControl( ID_FRAME_Alignment, ID_BUTTON_Invite );
	m_pID_EDIT_Search = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Alignment, ID_EDIT_Search );
	m_pID_BUTTON_Next = (ControlButton*)theUiManager.FindControl( ID_FRAME_Alignment, ID_BUTTON_Next );
	m_pID_PICTURE_WallLeft2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Alignment, ID_PICTURE_WallLeft2 );
	m_pID_PICTURE_WallRight2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Alignment, ID_PICTURE_WallRight2 );
	m_pID_PICTURE_WallLeft = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Alignment, ID_PICTURE_WallLeft );
	m_pID_PICTURE_WallRight = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Alignment, ID_PICTURE_WallRight );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Alignment, ID_BUTTON_CLOSE );
	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_Alignment, ID_BUTTON_help );
	m_pID_CHECKBOX_Stranger = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Alignment, ID_CHECKBOX_Stranger );
	m_pID_TEXT_G = (ControlText*)theUiManager.FindControl( ID_FRAME_Alignment, ID_TEXT_G );
	m_pID_BUTTON_GuildName = (ControlButton*)theUiManager.FindControl( ID_FRAME_Alignment, ID_BUTTON_GuildName );
	m_pID_BUTTON_GuildLeader = (ControlButton*)theUiManager.FindControl( ID_FRAME_Alignment, ID_BUTTON_GuildLeader );
	m_pID_BUTTON_Number = (ControlButton*)theUiManager.FindControl( ID_FRAME_Alignment, ID_BUTTON_Number );
	m_pID_LIST_GuildName = (ControlList*)theUiManager.FindControl( ID_FRAME_Alignment, ID_LIST_GuildName );
	m_pID_LIST_GuildLeader = (ControlList*)theUiManager.FindControl( ID_FRAME_Alignment, ID_LIST_GuildLeader );
	m_pID_LIST_Lvl = (ControlList*)theUiManager.FindControl( ID_FRAME_Alignment, ID_LIST_Lvl );
	m_pID_BUTTON_Enemy = (ControlButton*)theUiManager.FindControl( ID_FRAME_Alignment, ID_BUTTON_Enemy );
	m_pID_BUTTON_JieChu = (ControlButton*)theUiManager.FindControl( ID_FRAME_Alignment, ID_BUTTON_JieChu );
	m_pID_BUTTON_YanHe = (ControlButton*)theUiManager.FindControl( ID_FRAME_Alignment, ID_BUTTON_YanHe );
	m_pID_BUTTON_QiangZhi = (ControlButton*)theUiManager.FindControl( ID_FRAME_Alignment, ID_BUTTON_QiangZhi );
	m_pID_TEXT_ArrowGuildName = (ControlText*)theUiManager.FindControl( ID_FRAME_Alignment, ID_TEXT_ArrowGuildName );
	m_pID_TEXT_ArrowGuildLeader = (ControlText*)theUiManager.FindControl( ID_FRAME_Alignment, ID_TEXT_ArrowGuildLeader );
	m_pID_TEXT_ArrowNumber = (ControlText*)theUiManager.FindControl( ID_FRAME_Alignment, ID_TEXT_ArrowNumber );
	m_pID_TEXT_Wait = (ControlText*)theUiManager.FindControl( ID_FRAME_Alignment, ID_TEXT_Wait );
	m_pID_LIST_Number = (ControlList*)theUiManager.FindControl( ID_FRAME_Alignment, ID_LIST_Number );
	m_pID_BUTTON_GuildLvl = (ControlButton*)theUiManager.FindControl( ID_FRAME_Alignment, ID_BUTTON_GuildLvl );
	m_pID_TEXT_ArrowGuildLvl = (ControlText*)theUiManager.FindControl( ID_FRAME_Alignment, ID_TEXT_ArrowGuildLvl );
	assert( m_pID_FRAME_Alignment );
	assert( m_pID_PICTURE_Di );
	assert( m_pID_PICTURE_TitleDi );
	assert( m_pID_PICTURE_WallPaper );
	assert( m_pID_TEXT_Title );
	assert( m_pID_LIST_GuildList );
	assert( m_pID_CHECKBOX_Friend );
	assert( m_pID_CHECKBOX_Enemy );
	assert( m_pID_BUTTON_Invite );
	assert( m_pID_EDIT_Search );
	assert( m_pID_BUTTON_Next );
	assert( m_pID_PICTURE_WallLeft2 );
	assert( m_pID_PICTURE_WallRight2 );
	assert( m_pID_PICTURE_WallLeft );
	assert( m_pID_PICTURE_WallRight );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_help );
	assert( m_pID_CHECKBOX_Stranger );
	assert( m_pID_TEXT_G );
	assert( m_pID_BUTTON_GuildName );
	assert( m_pID_BUTTON_GuildLeader );
	assert( m_pID_BUTTON_Number );
	assert( m_pID_LIST_GuildName );
	assert( m_pID_LIST_GuildLeader );
	assert( m_pID_LIST_Lvl );
	assert( m_pID_BUTTON_Enemy );
	assert( m_pID_BUTTON_JieChu );
	assert( m_pID_BUTTON_YanHe );
	assert( m_pID_BUTTON_QiangZhi );
	assert( m_pID_TEXT_ArrowGuildName );
	assert( m_pID_TEXT_ArrowGuildLeader );
	assert( m_pID_TEXT_ArrowNumber );
	assert( m_pID_TEXT_Wait );
	assert( m_pID_LIST_Number );
	assert( m_pID_BUTTON_GuildLvl );
	assert( m_pID_TEXT_ArrowGuildLvl );
	USE_SCRIPT( eUI_OBJECT_DlgAlignment, this );

	m_pID_TEXT_Arrow[ESName] = m_pID_TEXT_ArrowGuildName;
	m_pID_TEXT_Arrow[ESLeader] = m_pID_TEXT_ArrowGuildLeader;
	m_pID_TEXT_Arrow[ESNumber] = m_pID_TEXT_ArrowNumber;
	m_pID_TEXT_Arrow[ESLevel] = m_pID_TEXT_ArrowGuildLvl;
	for (int i = 0; i < eSortTypeTotal; ++i)
	{
		m_bArrow[i] = false;
	}

	m_pID_LIST_GuildList->SetItemMaxCount(10000);
	InitialChildList(m_pID_LIST_GuildName);
	InitialChildList(m_pID_LIST_GuildLeader);
	InitialChildList(m_pID_LIST_Number);
	InitialChildList(m_pID_LIST_Lvl);
	// 		m_pID_LIST_GuildList->SetRBSelectEnable();
	m_pID_CHECKBOX_Stranger->SetCheck(true);
	if (m_bWaitText)
	{
		m_pID_TEXT_Wait->SetText(theXmlString.GetString(eText_WaitingServerUpdate));
	}

	// 		m_pID_BUTTON_QiangZhi->SetShowTip(true);
	// 		m_pID_BUTTON_QiangZhi->setTip(m_pID_BUTTON_QiangZhi->GetData()->m_szCaption);

	m_PeaceTimeMap.clear();
	nRelationType = GR_NEUTRALISM;

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Alignment::_UnLoadUI()
{
	CLOSE_SCRIPT ( eUI_OBJECT_DlgAlignment );
	m_pID_FRAME_Alignment = NULL;
	m_pID_PICTURE_Di = NULL;
	m_pID_PICTURE_TitleDi = NULL;
	m_pID_PICTURE_WallPaper = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_LIST_GuildList = NULL;
	m_pID_CHECKBOX_Friend = NULL;
	m_pID_CHECKBOX_Enemy = NULL;
	m_pID_BUTTON_Invite = NULL;
	m_pID_EDIT_Search = NULL;
	m_pID_BUTTON_Next = NULL;
	m_pID_PICTURE_WallLeft2 = NULL;
	m_pID_PICTURE_WallRight2 = NULL;
	m_pID_PICTURE_WallLeft = NULL;
	m_pID_PICTURE_WallRight = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_help = NULL;
	m_pID_CHECKBOX_Stranger = NULL;
	m_pID_TEXT_G = NULL;
	m_pID_BUTTON_GuildName = NULL;
	m_pID_BUTTON_GuildLeader = NULL;
	m_pID_BUTTON_Number = NULL;
	m_pID_LIST_GuildName = NULL;
	m_pID_LIST_GuildLeader = NULL;
	m_pID_LIST_Lvl = NULL;
	m_pID_BUTTON_Enemy = NULL;
	m_pID_BUTTON_JieChu = NULL;
	m_pID_BUTTON_YanHe = NULL;
	m_pID_BUTTON_QiangZhi = NULL;
	m_pID_TEXT_ArrowGuildName = NULL;
	m_pID_TEXT_ArrowGuildLeader = NULL;
	m_pID_TEXT_ArrowNumber = NULL;
	m_pID_TEXT_Wait = NULL;
	m_pID_LIST_Number = NULL;
	m_pID_BUTTON_GuildLvl = NULL;
	m_pID_TEXT_ArrowGuildLvl = NULL;
	m_bWaitText = true;
	return theUiManager.RemoveFrame( "Data\\UI\\Alignment.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Alignment::_IsVisable()
{
	if( !m_pID_FRAME_Alignment )
		return false;
	return m_pID_FRAME_Alignment->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Alignment::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_Alignment )
		return;
	m_pID_FRAME_Alignment->SetVisable( bVisable );
	if( bVisable )
	{
		RefreshUI();
		return;
	}
}

void CUI_ID_FRAME_Alignment::InitialChildList( ControlList* m_p_LIST )
{
	m_p_LIST->SetMsgHoldup(false);	//不接受消息
	m_p_LIST->SetItemMaxCount( 10000 );
	m_p_LIST->HaveSelBar( false );	//没有绿色cur选中地图
	m_p_LIST->SetCurSelIndex(-1);
	m_p_LIST->SetDrawFlags(DT_CENTER|DT_NOCLIP);

}

void CUI_ID_FRAME_Alignment::RefreshChildList()
{
	int nStartIndex = m_pID_LIST_GuildList->GetStartIndex();
	(m_pID_LIST_GuildName)->SetStartIndex(nStartIndex);
	(m_pID_LIST_GuildLeader)->SetStartIndex(nStartIndex);
	(m_pID_LIST_Number)->SetStartIndex(nStartIndex);
	(m_pID_LIST_Lvl)->SetStartIndex(nStartIndex);

}

void CUI_ID_FRAME_Alignment::FillMemberList( void* pVoid, DWORD dwColor )
{
	char szMemberNumber[256] = {0};
	GuildInfoEx* pGuild = (GuildInfoEx*)pVoid;
	ControlList::S_List	stItem;

	stItem.SetData(pGuild->baseInfo.szName,0,NULL,dwColor);
	m_pID_LIST_GuildName->AddItem(&stItem,false);
	stItem.SetData(pGuild->baseInfo.szMasterName,0,NULL,dwColor);
	m_pID_LIST_GuildLeader->AddItem(&stItem,false);
	itoa(pGuild->baseInfo.shMemberNumber, szMemberNumber, 10);
	stItem.SetData( szMemberNumber, 0, NULL, dwColor );
	m_pID_LIST_Number->AddItem(&stItem,false);
	itoa(pGuild->baseInfo.shLevel, szMemberNumber, 10);
	stItem.SetData( szMemberNumber, 0, NULL, dwColor );
	m_pID_LIST_Lvl->AddItem(&stItem,false);
	stItem.SetData( "", 0, NULL, dwColor );
	m_pID_LIST_GuildList->AddItem( &stItem, false );
}

void CUI_ID_FRAME_Alignment::GetMemberListCurSelName()
{
	int selIndex = m_pID_LIST_GuildList->GetCurSelIndex();
	if (selIndex != -1 && selIndex < m_pID_LIST_GuildList->GetListItemCnt())
	{
		m_strName = m_pID_LIST_GuildName->GetListItem(selIndex)->m_szText;
	}

}

int CUI_ID_FRAME_Alignment::GetSelectDBId()
{
	GetMemberListCurSelName();
	GuildInfoEx* pGuild = thePlayerRole.getGuild(m_strName);
	if (pGuild)
	{
		return pGuild->baseInfo.id;
	}

	return -1;
}

//void CUI_ID_FRAME_Alignment::UpdateGuildList()
//{
//	resultList.clear();
//	if (nRelationType != GR_NEUTRALISM)
//	{
//		/*SGangRelationInfoDB* guildRelationInfos = thePlayerRole.GetGangMgr()->m_GangInfo.m_guildRelation;*/
//		//
//		// 通过显示类型从工会关系列表中找出相应关系类型的的数据，没有中立情况。
//		//
//		//for (int i = 0; i < dr_MaxGuildRelationCount; ++i)
//		//{
//		//	if (guildRelationInfos[i].corpsId == 0)
//		//	{
//		//		break;
//		//	}
//		//	if( guildRelationInfos[i].relation == nRelationType)
//		//	{
//		//		GuildInfoEx* pGuild = thePlayerRole.getGuild(guildRelationInfos[i].corpsId);
//		//		if (pGuild)
//		//		{
//		//			resultList.push_back(pGuild);
//		//		}
//		//	}
//
//		//}
//	}
//	else
//	{
//		CPlayerRole::GuildListType* guildList;
//		thePlayerRole.getGuildList(&guildList);
//		for (CPlayerRole::GuildListType::iterator iter = guildList->begin();iter != guildList->end();++iter)
//		{
//			if (!IsExistRelation((*iter).baseInfo.id) && ((*iter).baseInfo.id != thePlayerRole.GetGangMgr()->m_GangInfo.m_nID))
//			{
//				resultList.push_back(&(*iter));
//			}
//
//		}
//
//	}
//	UpdateGuildListUI();
//}

//bool CUI_ID_FRAME_Alignment::IsExistRelation( int id )
//{
//	SGangRelationInfoDB* guildRelationInfos = thePlayerRole.GetGangMgr()->m_GangInfo.m_guildRelation;
//
//	for (int i = 0; i < dr_MaxGuildRelationCount; ++i)
//	{
//		if (guildRelationInfos[i].corpsId == 0)
//		{
//			return false;
//		}
//		if( guildRelationInfos[i].corpsId == id)
//		{
//			return true;
//		}
//
//	}
//	return false;
//
//}

void CUI_ID_FRAME_Alignment::UpdateGuildListUI()
{
	DWORD col = 0;
	switch(nRelationType)
	{
	case GR_NEUTRALISM:
		col = Color_Config.getColor(CC_PlayerNormal);
		break;

	case GR_LEAGUE:
		col = Color_Config.getColor(CC_PlayerLeague);
		break;

	case GR_ADVERSE:
		col = Color_Config.getColor(CC_PlayerEnemy);
		break;
	default:
		assert(0);
	}
	switch(nSortType)
	{
	case ESName:
		{
			if (m_bArrow[ESName])
			{
				resultList.sort(SortByName);
			}
			else
			{
				resultList.sort(SortByName_Rev);
			}
		}
		break;
	case ESLeader:
		{
			if (m_bArrow[ESLeader])
			{
				resultList.sort(SortByMasterName);
			}
			else
			{
				resultList.sort(SortByMasterName_Rev);
			}
		}
		break;
	case ESNumber:
		{
			if (m_bArrow[ESNumber])
			{
				resultList.sort(SortByNumber);
			}
			else
			{
				resultList.sort(SortByNumber_Rev);
			}
		}
		break;
	case ESLevel:
		{
			if (m_bArrow[ESLevel])
			{
				resultList.sort(SortByLevel);
			}
			else
			{
				resultList.sort(SortByLevel_Rev);
			}
		}
		break;
	default:
		assert(0);
	}
	m_pID_LIST_GuildList->BeginUpdate();
	m_pID_LIST_GuildName->BeginUpdate();
	m_pID_LIST_GuildLeader->BeginUpdate();
	m_pID_LIST_Number->BeginUpdate();
	m_pID_LIST_Lvl->BeginUpdate();
	m_pID_LIST_GuildName->Clear();
	m_pID_LIST_GuildList->Clear();
	m_pID_LIST_GuildLeader->Clear();
	m_pID_LIST_Number->Clear();
	m_pID_LIST_Lvl->Clear();
	for(std::list<GuildInfoEx*>::iterator iter = resultList.begin(); iter != resultList.end();++iter)
	{
		FillMemberList((*iter),col);
	}
	m_pID_LIST_GuildName->EndUpdate();
	m_pID_LIST_GuildLeader->EndUpdate();
	m_pID_LIST_Number->EndUpdate();
	m_pID_LIST_Lvl->EndUpdate();
	m_pID_LIST_GuildList->EndUpdate();
	if (m_pID_LIST_GuildList->GetCurSelIndex() >= m_pID_LIST_GuildList->GetListItemCnt())
	{
		m_pID_LIST_GuildList->SetCurSelIndex(m_pID_LIST_GuildList->GetListItemCnt() - 1);
	}
	// 		m_pID_LIST_GuildList->SetCurSelIndex(0);

}

//bool CUI_ID_FRAME_Alignment::ID_BUTTON_QiangZhiOnButtonClick( ControlObject* pSender )
//{
//	int nGuildId = GetSelectDBId();
//	if (-1 == nGuildId)
//	{
//		return false;
//	}
//	int Index;
//	__int64 nItemGuid;
//	if (!IsClearRuptureItemExist(&Index,&nItemGuid))
//	{
//		GetShowScreenText()->AddInfo( theXmlString.GetString(eClient_ClearRupture_NoItem), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//		return false;
//	}
//	//MsgReqGuildChangeRelation msg;
//	msg.nGuildId = nGuildId;
//	msg.cRelationValue = GR_NEUTRALISM;
//	msg.stItemIndex = Index;
//	msg.nItemGuid = nItemGuid;
//	GettheNetworkInput().SendMsg( &msg );
//	return true;
//}

bool CUI_ID_FRAME_Alignment::IsClearRuptureItemExist(int* pIndex,__int64* pnItemGuid)
{
	for (int i  = 0; i < thePlayerRole.m_bag.GetNowBagSize(); ++i)
	{
		if (thePlayerRole.m_bag.IsHaveItem(i))
		{
			SCharItem stItem;
			thePlayerRole.m_bag.GetItem(i,&stItem);
			CItemDetail::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
			if (pItemCommon && pItemCommon->ucItemType == CItemDetail::ITEMTYPE_GUILD)
			{
				CItemDetail::SItemGuild* pItemGuild = (CItemDetail::SItemGuild*)pItemCommon;
				if (pItemGuild->uchType == CItemDetail::SItemGuild::ECD_ClearRupture)
				{
					if (pIndex)
					{
						*pIndex = i;
					}
					if (pnItemGuid)
					{
						*pnItemGuid = stItem.itembaseinfo.nOnlyInt;
					}
					return true;
				}
			}
		}
	}
	return false;
}

void CUI_ID_FRAME_Alignment::setGuildRelation( char relation )
{
	guardfunc;
	GetMemberListCurSelName();
	assert(m_strName != thePlayerRole.GetGangMgr()->GetGangName());
	GuildInfoEx* guildInfo = NULL;
	if ( 
		( guildInfo = thePlayerRole.getGuild( m_strName ) ) )
	{
		//SendRelationChangeMsg(guildInfo->baseInfo.id, relation);
	}
	unguard;

}

//void CUI_ID_FRAME_Alignment::SendRelationChangeMsg( unsigned int nGuildId, char relation )
//{
//	MsgReqGuildChangeRelation msg;
//	msg.nGuildId = nGuildId;
//	msg.cRelationValue = relation;
//	GettheNetworkInput().SendMsg( &msg );
//}

void CUI_ID_FRAME_Alignment::RefreshOptButton()
{
	m_pID_BUTTON_YanHe->SetEnable( false );
	m_pID_BUTTON_JieChu->SetEnable( false );
	m_pID_BUTTON_Enemy->SetEnable( false );
	m_pID_BUTTON_Invite->SetEnable(false);
	m_pID_BUTTON_QiangZhi->SetEnable(false);
	if (m_nGangRight == GuildDefine::Position_Master || m_nGangRight == GuildDefine::Position_ViceMaster)
	{
		switch (nRelationType)
		{
		case GR_NEUTRALISM:
			m_pID_BUTTON_Enemy->SetEnable(true);
			m_pID_BUTTON_Invite->SetEnable(true);
			break;

		case GR_LEAGUE:
			m_pID_BUTTON_JieChu->SetEnable( true);
			break;

		case GR_ADVERSE:
			m_pID_BUTTON_YanHe->SetEnable(true);
			if(IsClearRuptureItemExist())
			{
				m_pID_BUTTON_QiangZhi->SetEnable(true);
			}
			break;
		default:
			assert(0);
		}
	}
}

void CUI_ID_FRAME_Alignment::RefreshUI()
{
	s_CUI_Guild.SetNeedRefreshAlignment(false);
	CGangMgr* theGuild = thePlayerRole.GetGangMgr();
	if(theGuild == NULL)
	{
		return ;
	}

	if(theGuild->m_GangInfo.GetID() == GuildDefine::InitID)
	{
		return;
	}
	GuildMember* pJieyi = theGuild->FindByDBId(g_nCharacterDBID);
	if (pJieyi)
	{
		m_nGangRight = pJieyi->GetPosition() ;
	}
	// modifed, [9/28/2009 jiayi]
	//UpdateGuildList();
	RefreshOptButton();
}

void CUI_ID_FRAME_Alignment::ShowSortArrow( int eType )
{
	for (int i = 0; i < eSortTypeTotal; ++i)
	{
		m_pID_TEXT_Arrow[i]->SetVisable( false);
	}
	m_pID_TEXT_Arrow[eType]->SetVisable(true);
	m_bArrow[eType] = !m_bArrow[eType];
	if (m_bArrow[eType])
	{
		m_pID_TEXT_Arrow[eType]->SetText("{#203}");
	}
	else
	{
		m_pID_TEXT_Arrow[eType]->SetText("{#204}");
	}
}

void CUI_ID_FRAME_Alignment::ID_LIST_LvlOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{

}

void CUI_ID_FRAME_Alignment::SetTextWait(const char* chr)
{
	m_bWaitText = false;
	if (IsUILoad())
	{
		m_pID_TEXT_Wait->SetText(chr);
	}
}
