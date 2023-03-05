/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\刘小兵\Gang.cpp
*********************************************************************/
#include <assert.h>
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Gang.h"
#include "MeTerrain/stdafx.h"
#include "GameMain.h"
#include "GlobalDef.h"
#include "UIMgr.h"
#include "FuncPerformanceLog.h"
#include "XmlStringLanguage.h"
#include "PlayerRole.h"
#include "..\PlayerMgr.h"
#include "Player.h"
#include "Gang.h"
#include "AddMember.h"
//#include "Guild.h"
#include "Group_Me.h"
#include "FriendDlg.h"
#include "ChatInfoBox.h"
#include "MessageBox.h"
#include "UIBase.h"
#include "Guild_Pic.h"
#include "Announce.h"
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
#include "Compound.h"
//#include "Alignment.h"
#include "Rename.h"
#include "DroitList.h"
#include "GlobalFunction.h"
#include "meui/ExpressionManager.h"
#include "Ui/InfoList.h"
#include "GuildDefine.h"
#include "GuildMessage.h"
#include "GuildAttribute.h"
#include "Announce.h"
#include "GameDefineChar.h"
#include "GuildConfig.h"
#include "CountryBaseInfo.h"
extern int g_nCharacterDBID;
extern GAME_STATE	g_GameState;

const unsigned char InvalidGuildFamilyId = 0;
//得到当前角色的堂会id
unsigned char GetMyGuildFamilyId(void)
{
	if (!theHeroGame.GetPlayerMgr()->GetMe())
	{
		return InvalidGuildFamilyId;
	}

	CGangMgr *pGangMgr = thePlayerRole.GetGangMgr();

	if (NULL == pGangMgr || pGangMgr->GetGuildID() == GuildDefine::InitID)
	{
		return InvalidGuildFamilyId;
	}

	GuildMember *pMember = pGangMgr->FindByDBId(theHeroGame.GetPlayerMgr()->GetMe()->GetID());
	if(NULL == pMember)
		return InvalidGuildFamilyId;

	return pMember->GetFamilyID();
}

//设置一个ControlGroup里所有控件的状态
void EnableControlGroup(ControlGroup *_pGroup_, bool bEnable_ = true)
{
	if(NULL == _pGroup_)
		return;

	size_t count = _pGroup_->GetControlSize();
	for(size_t i=0; i < count; ++i)
	{
		ControlObject *pControl = _pGroup_->GetControl(i);
		if(pControl != NULL)
		{
			pControl->SetEnable(bEnable_);
		}
	}
}

CUI_ID_FRAME_Gang s_CUI_ID_FRAME_Gang;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Gang, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Gang, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_ChenWeiOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Gang, ID_LIST_TeamNameOnListSelectChange )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Gang, ID_LISTIMG_SkillOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_LISTIMG_SkillOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_LISTIMG_SkillOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Gang, ID_LISTIMG_SkillOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_TeamNameOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_LvlOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_JobOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_ChenHaoOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_GongXianOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_PlaceOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Gang, ID_LIST_LvlOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Gang, ID_LIST_JobOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Gang, ID_LIST_WorkOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Gang, ID_LIST_PlaceOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_CorpsOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_CloseOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_HelpOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Gang, ID_LIST_GangListOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_WorkOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Gang, ID_LIST_ChenHaoOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Gang, ID_LIST_GongXianOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_TongOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Gang, ID_LIST_TongOnListSelectChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_CHECKBOX_ShowLeaveOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_AlignmentOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_DroitInfoOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_QuitOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_ResumeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_DISBANDOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_AttributeOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Gang, ID_LIST_ActivityOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Gang, ID_LIST_MEMBEROnListSelectChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_CHECKBOX_GuildOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_CHECKBOX_CountryOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_ActivityOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_LeavePositionOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_ZhuanRangOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_ReturnTongOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_ChangeTongNameOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_DelTongOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_ADDTongOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_ADDOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_AnnouncementOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_DelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_DelAssistantOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_AppointOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_Tong6OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_Tong5OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_Tong4OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_Tong3OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_Tong2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_Tong1OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_Tong25OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_Tong24OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_Tong23OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_Tong22OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_Tong21OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_AppointAssistantOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_FamilyCreateOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_FamilyRenameOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_FamilyChangeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_AppointTongOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_FamilyMasterOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_DeposeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_ZRFamilyOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_ZCFamilyOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gang, ID_BUTTON_ChangeZZOnButtonClick )

CUI_ID_FRAME_Gang::CUI_ID_FRAME_Gang()
{
	// Member
	m_pID_FRAME_Gang = NULL;
	m_pID_PICTURE_TitleBg = NULL;
	m_pID_TEXT_RenShu = NULL;
	m_pID_TEXT_Warxishu = NULL;
	m_pID_BUTTON_ChenWei = NULL;
	m_pID_TEXT_RongYuWenZi = NULL;
	m_pID_TEXT_Announcement = NULL;
	m_pID_LIST_TeamName = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_SkillWenZi = NULL;
	m_pID_LISTIMG_Skill = NULL;
	m_pID_BUTTON_TeamName = NULL;
	m_pID_BUTTON_Lvl = NULL;
	m_pID_BUTTON_Job = NULL;
	m_pID_BUTTON_ChenHao = NULL;
	m_pID_BUTTON_GongXian = NULL;
	m_pID_BUTTON_Place = NULL;
	m_pID_LIST_Lvl = NULL;
	m_pID_LIST_Job = NULL;
	m_pID_LIST_Work = NULL;
	m_pID_LIST_Place = NULL;
	m_pID_BUTTON_Corps = NULL;
	m_pID_PICTURE_20025 = NULL;
	m_pID_PICTURE_19542 = NULL;
	m_pID_PICTURE_1310 = NULL;
	m_pID_PICTURE_27419 = NULL;
	m_pID_BUTTON_Close = NULL;
	m_pID_BUTTON_Help = NULL;
	m_pID_TEXT_Gang = NULL;
	m_pID_LIST_GangList = NULL;
	m_pID_PICTURE_GuildNum = NULL;
	m_pID_BUTTON_Work = NULL;
	m_pID_LIST_ChenHao = NULL;
	m_pID_LIST_GongXian = NULL;
	m_pID_TEXT_GangLvl = NULL;
	m_pID_BUTTON_Tong = NULL;
	m_pID_PROGRESS_GuildNum = NULL;
	m_pID_LIST_Tong = NULL;
	m_pID_PICTURE_5505 = NULL;
	m_pID_TEXT_ArrowTeamName = NULL;
	m_pID_TEXT_ArrowLvl = NULL;
	m_pID_TEXT_ArrowJob = NULL;
	m_pID_TEXT_ArrowWork = NULL;
	m_pID_TEXT_ArrowTong = NULL;
	m_pID_TEXT_ArrowGongXian = NULL;
	m_pID_CHECKBOX_ShowLeave = NULL;
	m_pID_TEXT_TongZ = NULL;
	m_pID_TEXT_Wait = NULL;
	m_pID_BUTTON_Alignment = NULL;
	m_pID_BUTTON_DroitInfo = NULL;
	m_pID_BUTTON_Quit = NULL;
	m_pID_BUTTON_Resume = NULL;
	m_pID_BUTTON_DISBAND = NULL;
	m_pID_BUTTON_Attribute = NULL;
	m_pID_LIST_Activity = NULL;
	m_pID_LIST_MEMBER = NULL;
	m_pID_CHECKBOX_Guild = NULL;
	m_pID_CHECKBOX_Country = NULL;
	m_pID_BUTTON_Activity = NULL;
	m_pID_TEXT_ArrowActivity = NULL;
	m_pID_TEXT_SelfWork = NULL;
	m_pID_TEXT_SelfGongXian = NULL;
	m_pID_TEXT_SelfActivity = NULL;
	m_pID_TEXT_SelfTong = NULL;
	m_pID_BUTTON_LeavePosition = NULL;
	m_pID_BUTTON_ZhuanRang = NULL;
	m_pID_BUTTON_ChangeTongName = NULL;
	m_pID_BUTTON_DelTong = NULL;
	m_pID_BUTTON_ADDTong = NULL;
	m_pID_BUTTON_ADD = NULL;
	m_pID_BUTTON_Announcement = NULL;
	m_pID_BUTTON_Del = NULL;
	m_pID_BUTTON_DelAssistant = NULL;
	m_pID_BUTTON_Appoint = NULL;
	//m_pID_BUTTON_Tong6 = NULL;
	m_pID_BUTTON_Tong5 = NULL;
	m_pID_BUTTON_Tong4 = NULL;
	m_pID_BUTTON_Tong3 = NULL;
	m_pID_BUTTON_Tong2 = NULL;
	m_pID_BUTTON_Tong1 = NULL;
	m_pID_BUTTON_Tong25 = NULL;
	m_pID_BUTTON_Tong24 = NULL;
	m_pID_BUTTON_Tong23 = NULL;
	m_pID_BUTTON_Tong22 = NULL;
	m_pID_BUTTON_Tong21 = NULL;
	m_pID_BUTTON_AppointAssistant = NULL;
	m_pID_TEXT_LeaderName = NULL;
	m_pID_TEXT_RongYu = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_TEXT_Tip = NULL;
	m_pID_BUTTON_FamilyCreate = NULL;
	m_pID_BUTTON_FamilyRename = NULL;
	m_pID_BUTTON_FamilyChange = NULL;
	m_pID_BUTTON_AppointTong = NULL;
	m_pID_BUTTON_FamilyMaster = NULL;
	m_pID_BUTTON_Depose = NULL;

	m_pID_BUTTON_ZRFamily = NULL;
	m_pID_BUTTON_ZCFamily = NULL;
	m_pID_BUTTON_ChangeZZ = NULL;

	m_bShowOfflineMember = false;
	m_nAllMemberNum = 0;
	m_pID_LIST_Line= NULL;
	/*m_bMoveMember = true;
	m_bChangeFamilyName = true;*/
	//m_bShowFamilyNameButton = true;
	//m_bShowMoveMemberButton = true;
	m_bNeedRefresh = true;
	m_pMovedMember = NULL;
	InitAllSortFunc();
	ResetSortMember();
}

// Frame
bool CUI_ID_FRAME_Gang::OnFrameRun()
{
	if (IsNeedRefresh())
	{
		Refresh();
	}

	OnUpdateListShowHeight();

	return true;
}

void CUI_ID_FRAME_Gang::SetListAndScrollBarShowHeight(int nListHeight, int nScrollHeight)
{
	OnUpdateListShowHeight(nListHeight);
	
	if (_IsVisable())
	{
		if (m_pID_LIST_MEMBER->GetScrollBar())
		{
			m_pID_LIST_TeamName->SetScrollValue(nScrollHeight);
		}
	}
}

void CUI_ID_FRAME_Gang::GetListAndScrollBarShowHeight(int& nListHeight, int& nScrollHeight)
{
	if (_IsVisable())
	{
		nListHeight = m_pID_LIST_MEMBER->GetShowStartHeight();
		if (m_pID_LIST_MEMBER->GetScrollBar())
		{
			nScrollHeight = m_pID_LIST_MEMBER->GetScrollBar()->GetValue();
		}
	}
}

bool CUI_ID_FRAME_Gang::ID_BUTTON_ZRFamilyOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if(pGuild == NULL || pGuild->GetGuildID() == GuildDefine::InitID)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Info_GuildInfo, theXmlString.GetString(eText_Guild_HaveNoGuild) );
		return false;
	}
	int nFamilyNum = pGuild->GetFamilyNumber();
	if (nFamilyNum <=0)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Info_GuildInfo, theXmlString.GetString(eText_GuildHaveNoFamily) );
		return false;
	}
	//首先判断是否选择了某个成员
	if (!SetRemovedMember())
	{
		ShowSelectNothingMessage();
		return false;
	}

	switch (theHeroGame.GetPlayerMgr()->GetMe()->GetGangPosition())
	{
	case GuildDefine::Position_FamilyMaster:
		{
			unsigned char id = GetMyGuildFamilyId();
			if(InvalidGuildFamilyId == id)
				return false;

			MsgGuildMemberFamilyChangeReq msg;
			msg.nPlayerID = m_pMovedMember->GetID();
			msg.uchFamilyID = InvalidGuildFamilyId;
			GettheNetworkInput().SendMsg(&msg);
		}
		break;
	case GuildDefine::Position_ViceMaster:
	case GuildDefine::Position_Master:
		{
			SetOtherRejectButtonMenu(eKey_MoveMember);
			int nFamilyNum = pGuild->GetFamilyNumber();
			SetFamilyCtlGroup(nFamilyNum);
			m_ctlAnotherFmailyGroup.SetVisible(!m_ctlAnotherFmailyGroup.IsVisible());
		}
		break;
	default:
		//其他的不能够越级转入
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, theXmlString.GetString(eText_Guild_UnableTansferPositon) );
		return false;
	}

	return true;
}

bool CUI_ID_FRAME_Gang::ID_BUTTON_ZCFamilyOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if(pGuild == NULL || pGuild->GetGuildID() == GuildDefine::InitID)
	{
		return false;
	}

	//首先判断是否选择了某个成员
	if (!SetRemovedMember())
	{
		ShowSelectNothingMessage();
		return false;
	}
	switch (theHeroGame.GetPlayerMgr()->GetMe()->GetGangPosition())
	{
		case GuildDefine::Position_ViceMaster:
		case GuildDefine::Position_Master:
		case GuildDefine::Position_FamilyMaster:
			{
				MsgGuildMemberFamilyChangeReq msg;
				msg.nPlayerID = m_pMovedMember->GetID();
				msg.uchFamilyID = 0;	//0代表转出
				GettheNetworkInput().SendMsg(&msg);
			}
			break;
		default:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, theXmlString.GetString(eText_Guild_UnableTansferPositon) );
			break;
	}
	

	return true;
}

bool CUI_ID_FRAME_Gang::ID_BUTTON_ChangeZZOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	const GuildConfig::ChangeAimSetting &setting = theGuildConfig.GetChangeAimSetting();

	//cd条件暂时不判

	//金钱
	if(thePlayerRole.GetData(CPlayerRole::TYPE_JiaoZi) + thePlayerRole.GetData(CPlayerRole::TYPE_MONEY) < setting.GetChangeAimCost())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, 
										theXmlString.GetString(eText_Guild_Creed_Money_Failed));
		return false;
	}

	s_CUI_ID_FRAME_Announce.SetDlgType(CUI_ID_FRAME_Announce::E_Type_Creed);
	s_CUI_ID_FRAME_Announce.SetVisable(true);

	return true;
}

void CUI_ID_FRAME_Gang::OnUpdateListShowHeight()
{
	if (_IsVisable())
	{
		int nShowHeight = m_pID_LIST_MEMBER->GetShowStartHeight();
		m_pID_LIST_TeamName->SetShowStartHeight(nShowHeight);
		m_pID_LIST_Lvl->SetShowStartHeight(nShowHeight);
		m_pID_LIST_Job->SetShowStartHeight(nShowHeight);
		m_pID_LIST_Work->SetShowStartHeight(nShowHeight);
		m_pID_LIST_Tong->SetShowStartHeight(nShowHeight);
		m_pID_LIST_Activity->SetShowStartHeight(nShowHeight);
		m_pID_LIST_GongXian->SetShowStartHeight(nShowHeight);
	}
}

void CUI_ID_FRAME_Gang::OnUpdateListShowHeight(int nShowHeight)
{
	if (_IsVisable())
	{
		m_pID_LIST_MEMBER->SetShowStartHeight(nShowHeight);
		m_pID_LIST_TeamName->SetShowStartHeight(nShowHeight);
		m_pID_LIST_Lvl->SetShowStartHeight(nShowHeight);
		m_pID_LIST_Job->SetShowStartHeight(nShowHeight);
		m_pID_LIST_Work->SetShowStartHeight(nShowHeight);
		m_pID_LIST_Tong->SetShowStartHeight(nShowHeight);
		m_pID_LIST_Activity->SetShowStartHeight(nShowHeight);
		m_pID_LIST_GongXian->SetShowStartHeight(nShowHeight);
	}
}

bool CUI_ID_FRAME_Gang::OnFrameRender()
{
	return true;
}

// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_ChenWeiOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	return true;
}
// List
void CUI_ID_FRAME_Gang::ID_LIST_TeamNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Gang )
		return;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Gang::ID_LISTIMG_SkillOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	return false;
}
bool CUI_ID_FRAME_Gang::ID_LISTIMG_SkillOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	return false;
}
bool CUI_ID_FRAME_Gang::ID_LISTIMG_SkillOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	return false;
}
bool CUI_ID_FRAME_Gang::ID_LISTIMG_SkillOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	return false;
}

// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_ChenHaoOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	return true;
}

// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_PlaceOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	return true;
}
// List
void CUI_ID_FRAME_Gang::ID_LIST_LvlOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Gang )
		return;
}
// List
void CUI_ID_FRAME_Gang::ID_LIST_JobOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Gang )
		return;
}
// List
void CUI_ID_FRAME_Gang::ID_LIST_WorkOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Gang )
		return;
}
// List
void CUI_ID_FRAME_Gang::ID_LIST_PlaceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Gang )
		return;
}
// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_CorpsOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	return true;
}

#include "ui\Guild_Create.h"

// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_HelpOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	s_CUI_ID_FRAME_GUILD_CREATE.SetVisable(true);


	return true;
}
// List
void CUI_ID_FRAME_Gang::ID_LIST_GangListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Gang )
		return;
}

// List
void CUI_ID_FRAME_Gang::ID_LIST_ChenHaoOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Gang )
		return;
}
// List
void CUI_ID_FRAME_Gang::ID_LIST_GongXianOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Gang )
		return;
}

// List
void CUI_ID_FRAME_Gang::ID_LIST_TongOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Gang )
		return;
}

// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_AlignmentOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_DroitInfoOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	return true;
}
// Button
// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_ResumeOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_DISBANDOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_AttributeOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	s_CUI_ID_FRAME_GuildAttribute.SetVisable(!s_CUI_ID_FRAME_GuildAttribute.IsVisable());
	return true;
}
// List
void CUI_ID_FRAME_Gang::ID_LIST_ActivityOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Gang )
		return;
}
// List
void CUI_ID_FRAME_Gang::ID_LIST_MEMBEROnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Gang )
		return;
}



// Button
// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_ChangeTongNameOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_DelTongOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	return true;
}

// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_ADDTongOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_AnnouncementOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	s_CUI_ID_FRAME_Announce.SetGang(true);
	s_CUI_ID_FRAME_Announce.SetDlgType(CUI_ID_FRAME_Announce::E_Type_Announcement);
	s_CUI_ID_FRAME_Announce.SetVisable(true);
	return true;
}

// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_DelAssistantOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	return true;
}

// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_AppointTongOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	return true;
}


// 装载UI
bool CUI_ID_FRAME_Gang::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Gang.MEUI", false, UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Gang.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Gang::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Gang, s_CUI_ID_FRAME_GangOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Gang, s_CUI_ID_FRAME_GangOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_ChenWei, s_CUI_ID_FRAME_GangID_BUTTON_ChenWeiOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Gang, ID_LIST_TeamName, s_CUI_ID_FRAME_GangID_LIST_TeamNameOnListSelectChange );
	theUiManager.OnIconDragOn( ID_FRAME_Gang, ID_LISTIMG_Skill, s_CUI_ID_FRAME_GangID_LISTIMG_SkillOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Gang, ID_LISTIMG_Skill, s_CUI_ID_FRAME_GangID_LISTIMG_SkillOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Gang, ID_LISTIMG_Skill, s_CUI_ID_FRAME_GangID_LISTIMG_SkillOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Gang, ID_LISTIMG_Skill, s_CUI_ID_FRAME_GangID_LISTIMG_SkillOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_TeamName, s_CUI_ID_FRAME_GangID_BUTTON_TeamNameOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Lvl, s_CUI_ID_FRAME_GangID_BUTTON_LvlOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Job, s_CUI_ID_FRAME_GangID_BUTTON_JobOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_ChenHao, s_CUI_ID_FRAME_GangID_BUTTON_ChenHaoOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_GongXian, s_CUI_ID_FRAME_GangID_BUTTON_GongXianOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Place, s_CUI_ID_FRAME_GangID_BUTTON_PlaceOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Gang, ID_LIST_Lvl, s_CUI_ID_FRAME_GangID_LIST_LvlOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Gang, ID_LIST_Job, s_CUI_ID_FRAME_GangID_LIST_JobOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Gang, ID_LIST_Work, s_CUI_ID_FRAME_GangID_LIST_WorkOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Gang, ID_LIST_Place, s_CUI_ID_FRAME_GangID_LIST_PlaceOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Corps, s_CUI_ID_FRAME_GangID_BUTTON_CorpsOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Close, s_CUI_ID_FRAME_GangID_BUTTON_CloseOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Help, s_CUI_ID_FRAME_GangID_BUTTON_HelpOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Gang, ID_LIST_GangList, s_CUI_ID_FRAME_GangID_LIST_GangListOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Work, s_CUI_ID_FRAME_GangID_BUTTON_WorkOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Gang, ID_LIST_ChenHao, s_CUI_ID_FRAME_GangID_LIST_ChenHaoOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Gang, ID_LIST_GongXian, s_CUI_ID_FRAME_GangID_LIST_GongXianOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Tong, s_CUI_ID_FRAME_GangID_BUTTON_TongOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Gang, ID_LIST_Tong, s_CUI_ID_FRAME_GangID_LIST_TongOnListSelectChange );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Gang, ID_CHECKBOX_ShowLeave, s_CUI_ID_FRAME_GangID_CHECKBOX_ShowLeaveOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Alignment, s_CUI_ID_FRAME_GangID_BUTTON_AlignmentOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_DroitInfo, s_CUI_ID_FRAME_GangID_BUTTON_DroitInfoOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Quit, s_CUI_ID_FRAME_GangID_BUTTON_QuitOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Resume, s_CUI_ID_FRAME_GangID_BUTTON_ResumeOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_DISBAND, s_CUI_ID_FRAME_GangID_BUTTON_DISBANDOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Attribute, s_CUI_ID_FRAME_GangID_BUTTON_AttributeOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Gang, ID_LIST_Activity, s_CUI_ID_FRAME_GangID_LIST_ActivityOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Gang, ID_LIST_MEMBER, s_CUI_ID_FRAME_GangID_LIST_MEMBEROnListSelectChange );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Gang, ID_CHECKBOX_Guild, s_CUI_ID_FRAME_GangID_CHECKBOX_GuildOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Gang, ID_CHECKBOX_Country, s_CUI_ID_FRAME_GangID_CHECKBOX_CountryOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Activity, s_CUI_ID_FRAME_GangID_BUTTON_ActivityOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_LeavePosition, s_CUI_ID_FRAME_GangID_BUTTON_LeavePositionOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_ZhuanRang, s_CUI_ID_FRAME_GangID_BUTTON_ZhuanRangOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_ReturnTong, s_CUI_ID_FRAME_GangID_BUTTON_ReturnTongOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_ChangeTongName, s_CUI_ID_FRAME_GangID_BUTTON_ChangeTongNameOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_DelTong, s_CUI_ID_FRAME_GangID_BUTTON_DelTongOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_ADDTong, s_CUI_ID_FRAME_GangID_BUTTON_ADDTongOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_ADD, s_CUI_ID_FRAME_GangID_BUTTON_ADDOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Announcement, s_CUI_ID_FRAME_GangID_BUTTON_AnnouncementOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Del, s_CUI_ID_FRAME_GangID_BUTTON_DelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_DelAssistant, s_CUI_ID_FRAME_GangID_BUTTON_DelAssistantOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Appoint, s_CUI_ID_FRAME_GangID_BUTTON_AppointOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Tong6, s_CUI_ID_FRAME_GangID_BUTTON_Tong6OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Tong5, s_CUI_ID_FRAME_GangID_BUTTON_Tong5OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Tong4, s_CUI_ID_FRAME_GangID_BUTTON_Tong4OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Tong3, s_CUI_ID_FRAME_GangID_BUTTON_Tong3OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Tong2, s_CUI_ID_FRAME_GangID_BUTTON_Tong2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Tong1, s_CUI_ID_FRAME_GangID_BUTTON_Tong1OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Tong25, s_CUI_ID_FRAME_GangID_BUTTON_Tong25OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Tong24, s_CUI_ID_FRAME_GangID_BUTTON_Tong24OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Tong23, s_CUI_ID_FRAME_GangID_BUTTON_Tong23OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Tong22, s_CUI_ID_FRAME_GangID_BUTTON_Tong22OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Tong21, s_CUI_ID_FRAME_GangID_BUTTON_Tong21OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_AppointAssistant, s_CUI_ID_FRAME_GangID_BUTTON_AppointAssistantOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_FamilyCreate, s_CUI_ID_FRAME_GangID_BUTTON_FamilyCreateOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_FamilyRename, s_CUI_ID_FRAME_GangID_BUTTON_FamilyRenameOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_FamilyChange, s_CUI_ID_FRAME_GangID_BUTTON_FamilyChangeOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_AppointTong, s_CUI_ID_FRAME_GangID_BUTTON_AppointTongOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_FamilyMaster, s_CUI_ID_FRAME_GangID_BUTTON_FamilyMasterOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_Depose, s_CUI_ID_FRAME_GangID_BUTTON_DeposeOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_ZRFamily, s_CUI_ID_FRAME_GangID_BUTTON_ZRFamilyOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_ZCFamily, s_CUI_ID_FRAME_GangID_BUTTON_ZCFamilyOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gang, ID_BUTTON_ChangeZZ, s_CUI_ID_FRAME_GangID_BUTTON_ChangeZZOnButtonClick );

	m_pID_FRAME_Gang = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Gang );
	m_pID_PICTURE_TitleBg = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gang, ID_PICTURE_TitleBg );
	m_pID_TEXT_RenShu = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_RenShu );
	m_pID_TEXT_Warxishu = (ControlText*)theUiManager.FindControl(ID_FRAME_Gang, ID_TEXT_Warxishu);
	m_pID_BUTTON_ChenWei = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_ChenWei );
	m_pID_TEXT_RongYuWenZi = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_RongYuWenZi );
	m_pID_TEXT_Announcement = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_Announcement );
	m_pID_LIST_TeamName = (ControlList*)theUiManager.FindControl( ID_FRAME_Gang, ID_LIST_TeamName );
	m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_Name );
	m_pID_TEXT_SkillWenZi = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_SkillWenZi );
	m_pID_LISTIMG_Skill = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Gang, ID_LISTIMG_Skill );
	m_pID_BUTTON_TeamName = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_TeamName );
	m_pID_BUTTON_Lvl = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Lvl );
	m_pID_BUTTON_Job = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Job );
	m_pID_BUTTON_ChenHao = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_ChenHao );
	m_pID_BUTTON_GongXian = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_GongXian );
	m_pID_BUTTON_Place = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Place );
	m_pID_LIST_Lvl = (ControlList*)theUiManager.FindControl( ID_FRAME_Gang, ID_LIST_Lvl );
	m_pID_LIST_Job = (ControlList*)theUiManager.FindControl( ID_FRAME_Gang, ID_LIST_Job );
	m_pID_LIST_Work = (ControlList*)theUiManager.FindControl( ID_FRAME_Gang, ID_LIST_Work );
	m_pID_LIST_Place = (ControlList*)theUiManager.FindControl( ID_FRAME_Gang, ID_LIST_Place );
	m_pID_BUTTON_Corps = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Corps );
	m_pID_PICTURE_20025 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gang, ID_PICTURE_20025 );
	m_pID_PICTURE_19542 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gang, ID_PICTURE_19542 );
	m_pID_PICTURE_1310 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gang, ID_PICTURE_1310 );
	m_pID_PICTURE_27419 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gang, ID_PICTURE_27419 );
	m_pID_BUTTON_Close = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Close );
	m_pID_BUTTON_Help = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Help );
	m_pID_TEXT_Gang = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_Gang );
	m_pID_LIST_GangList = (ControlList*)theUiManager.FindControl( ID_FRAME_Gang, ID_LIST_GangList );
	m_pID_PICTURE_GuildNum = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gang, ID_PICTURE_GuildNum );
	m_pID_BUTTON_Work = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Work );
	m_pID_LIST_ChenHao = (ControlList*)theUiManager.FindControl( ID_FRAME_Gang, ID_LIST_ChenHao );
	m_pID_LIST_GongXian = (ControlList*)theUiManager.FindControl( ID_FRAME_Gang, ID_LIST_GongXian );
	m_pID_TEXT_GangLvl = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_GangLvl );
	m_pID_BUTTON_Tong = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Tong );
	m_pID_PROGRESS_GuildNum = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Gang, ID_PROGRESS_GuildNum );
	m_pID_LIST_Tong = (ControlList*)theUiManager.FindControl( ID_FRAME_Gang, ID_LIST_Tong );
	m_pID_PICTURE_5505 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gang, ID_PICTURE_5505 );
	m_pID_TEXT_ArrowTeamName = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_ArrowTeamName );
	m_pID_TEXT_ArrowLvl = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_ArrowLvl );
	m_pID_TEXT_ArrowJob = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_ArrowJob );
	m_pID_TEXT_ArrowWork = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_ArrowWork );
	m_pID_TEXT_ArrowTong = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_ArrowTong );
	m_pID_TEXT_ArrowGongXian = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_ArrowGongXian );
	m_pID_CHECKBOX_ShowLeave = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Gang, ID_CHECKBOX_ShowLeave );
	m_pID_TEXT_TongZ = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_TongZ );
	m_pID_TEXT_Wait = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_Wait );
	m_pID_BUTTON_Alignment = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Alignment );
	m_pID_BUTTON_DroitInfo = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_DroitInfo );
	m_pID_BUTTON_Quit = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Quit );
	m_pID_BUTTON_Resume = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Resume );
	m_pID_BUTTON_DISBAND = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_DISBAND );
	m_pID_BUTTON_Attribute = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Attribute );
	m_pID_LIST_Activity = (ControlList*)theUiManager.FindControl( ID_FRAME_Gang, ID_LIST_Activity );
	m_pID_LIST_MEMBER = (ControlList*)theUiManager.FindControl( ID_FRAME_Gang, ID_LIST_MEMBER );
	m_pID_CHECKBOX_Guild = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Gang, ID_CHECKBOX_Guild );
	m_pID_CHECKBOX_Country = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Gang, ID_CHECKBOX_Country );
	m_pID_BUTTON_Activity = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Activity );
	m_pID_TEXT_ArrowActivity = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_ArrowActivity );
	m_pID_TEXT_SelfWork = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_SelfWork );
	m_pID_TEXT_SelfGongXian = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_SelfGongXian );
	m_pID_TEXT_SelfActivity = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_SelfActivity );
	m_pID_TEXT_SelfTong = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_SelfTong );
	m_pID_BUTTON_LeavePosition = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_LeavePosition );
	m_pID_BUTTON_ZhuanRang = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_ZhuanRang );
	//m_pID_BUTTON_ReturnTong = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_ReturnTong );
	m_pID_BUTTON_ChangeTongName = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_ChangeTongName );
	m_pID_BUTTON_DelTong = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_DelTong );
	m_pID_BUTTON_ADDTong = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_ADDTong );
	m_pID_BUTTON_ADD = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_ADD );
	m_pID_BUTTON_Announcement = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Announcement );
	m_pID_BUTTON_Del = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Del );
	m_pID_BUTTON_DelAssistant = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_DelAssistant );
	m_pID_BUTTON_Appoint = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Appoint );
	//m_pID_BUTTON_Tong6 = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Tong6 );
	m_pID_BUTTON_Tong5 = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Tong5 );
	m_pID_BUTTON_Tong4 = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Tong4 );
	m_pID_BUTTON_Tong3 = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Tong3 );
	m_pID_BUTTON_Tong2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Tong2 );
	m_pID_BUTTON_Tong1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Tong1 );
	m_pID_BUTTON_Tong25 = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Tong25 );
	m_pID_BUTTON_Tong24 = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Tong24 );
	m_pID_BUTTON_Tong23 = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Tong23 );
	m_pID_BUTTON_Tong22 = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Tong22 );
	m_pID_BUTTON_Tong21 = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Tong21 );
	m_pID_BUTTON_AppointAssistant = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_AppointAssistant );
	m_pID_TEXT_LeaderName = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_LeaderName );
	m_pID_TEXT_RongYu = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_RongYu );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_Money );
	m_pID_TEXT_Tip = (ControlText*)theUiManager.FindControl( ID_FRAME_Gang, ID_TEXT_Tip );
	m_pID_BUTTON_FamilyCreate = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_FamilyCreate );
	m_pID_BUTTON_FamilyRename = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_FamilyRename );
	m_pID_BUTTON_FamilyChange = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_FamilyChange );
	m_pID_BUTTON_AppointTong = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_AppointTong );
	m_pID_BUTTON_FamilyMaster = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_FamilyMaster );
	m_pID_BUTTON_Depose = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_Depose );
	m_pID_BUTTON_ZRFamily = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_ZRFamily );
	m_pID_BUTTON_ZCFamily = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_ZCFamily );
	m_pID_BUTTON_ChangeZZ = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gang, ID_BUTTON_ChangeZZ );
	m_pID_LIST_Line = (ControlList*)theUiManager.FindControl(ID_FRAME_Gang,ID_LIST_Line);
	//assert(m_pID_TEXT_Warxishu);
	//assert( m_pID_FRAME_Gang );
	//assert( m_pID_PICTURE_TitleBg );
	//assert( m_pID_TEXT_RenShu );
	//assert( m_pID_BUTTON_ChenWei );
	//assert( m_pID_TEXT_RongYuWenZi );
	//assert( m_pID_TEXT_Announcement );
	//assert( m_pID_LIST_TeamName );
	//assert( m_pID_TEXT_Name );
	//assert( m_pID_TEXT_SkillWenZi );
	//assert( m_pID_LISTIMG_Skill );
	//assert( m_pID_BUTTON_TeamName );
	//assert( m_pID_BUTTON_Lvl );
	//assert( m_pID_BUTTON_Job );
	//assert( m_pID_BUTTON_ChenHao );
	//assert( m_pID_BUTTON_GongXian );
	//assert( m_pID_BUTTON_Place );
	//assert( m_pID_LIST_Lvl );
	//assert( m_pID_LIST_Job );
	//assert( m_pID_LIST_Work );
	//assert( m_pID_LIST_Place );
	//assert( m_pID_BUTTON_Corps );
	//assert( m_pID_PICTURE_20025 );
	//assert( m_pID_PICTURE_19542 );
	//assert( m_pID_PICTURE_1310 );
	//assert( m_pID_PICTURE_27419 );
	//assert( m_pID_BUTTON_Close );
	//assert( m_pID_BUTTON_Help );
	//assert( m_pID_TEXT_Gang );
	//assert( m_pID_LIST_GangList );
	//assert( m_pID_PICTURE_GuildNum );
	//assert( m_pID_BUTTON_Work );
	//assert( m_pID_LIST_ChenHao );
	//assert( m_pID_LIST_GongXian );
	//assert( m_pID_TEXT_GangLvl );
	//assert( m_pID_BUTTON_Tong );
	//assert( m_pID_PROGRESS_GuildNum );
	//assert( m_pID_LIST_Tong );
	//assert( m_pID_PICTURE_5505 );
	//assert( m_pID_TEXT_ArrowTeamName );
	//assert( m_pID_TEXT_ArrowLvl );
	//assert( m_pID_TEXT_ArrowJob );
	//assert( m_pID_TEXT_ArrowWork );
	//assert( m_pID_TEXT_ArrowTong );
	//assert( m_pID_TEXT_ArrowGongXian );
	//assert( m_pID_CHECKBOX_ShowLeave );
	//assert( m_pID_TEXT_TongZ );
	//assert( m_pID_TEXT_Wait );
	//assert( m_pID_BUTTON_Alignment );
	//assert( m_pID_BUTTON_DroitInfo );
	//assert( m_pID_BUTTON_Quit );
	//assert( m_pID_BUTTON_Resume );
	//assert( m_pID_BUTTON_DISBAND );
	//assert( m_pID_BUTTON_Attribute );
	//assert( m_pID_LIST_Activity );
	//assert( m_pID_LIST_MEMBER );
	//assert( m_pID_CHECKBOX_Guild );
	//assert( m_pID_CHECKBOX_Country );
	//assert( m_pID_BUTTON_Activity );
	//assert( m_pID_TEXT_ArrowActivity );
	//assert( m_pID_TEXT_SelfWork );
	//assert( m_pID_TEXT_SelfGongXian );
	//assert( m_pID_TEXT_SelfActivity );
	//assert( m_pID_TEXT_SelfTong );
	//assert( m_pID_BUTTON_LeavePosition );
	//assert( m_pID_BUTTON_ZhuanRang );
	///*assert( m_pID_BUTTON_ReturnTong );*/
	//assert( m_pID_BUTTON_ChangeTongName );
	//assert( m_pID_BUTTON_DelTong );
	//assert( m_pID_BUTTON_ADDTong );
	//assert( m_pID_BUTTON_ADD );
	//assert( m_pID_BUTTON_Announcement );
	//assert( m_pID_BUTTON_Del );
	//assert( m_pID_BUTTON_DelAssistant );
	//assert( m_pID_BUTTON_Appoint );
	////assert( m_pID_BUTTON_Tong6 );
	//assert( m_pID_BUTTON_Tong5 );
	//assert( m_pID_BUTTON_Tong4 );
	//assert( m_pID_BUTTON_Tong3 );
	//assert( m_pID_BUTTON_Tong2 );
	//assert( m_pID_BUTTON_Tong1 );
	//assert( m_pID_BUTTON_AppointAssistant );
	//assert( m_pID_TEXT_LeaderName );
	//assert( m_pID_TEXT_RongYu );
	//assert( m_pID_TEXT_Money );
	//assert( m_pID_TEXT_Tip );
	//assert( m_pID_BUTTON_FamilyCreate );
	//assert( m_pID_BUTTON_FamilyRename );
	//assert( m_pID_BUTTON_FamilyChange );
	//assert( m_pID_BUTTON_AppointTong );
	//assert( m_pID_BUTTON_FamilyMaster );
	//assert( m_pID_BUTTON_Depose );
	
	SetGuildGroup();
	SetControlGroupForBangzhong();
	SetControlGroupForTangzhu();
	SetControlGroupForFubangzhu();
	SetControlGroupForBangzhu();
	SetControlGroupForAppoint();
	SetControlActiveGroup();
	SetControlGroupForFamilyChangeName();
	SetControlGroupTransferBangzhong();
	SetMainMenu();

	m_ctlGuildGroup.SetVisible(true);
	m_ctlActiveGroup.SetVisible(false);
	m_ctlBangzhongGroup.SetVisible(true);
	
	m_pID_LIST_MEMBER->SetRBClickFun(ID_List_OnRBClick);
	m_pID_LIST_MEMBER->SetLBtnDownFun(ID_List_OnLBClick);

	SetSkipAllMsg();

	InitArrowArray();
	return true;
}

void CUI_ID_FRAME_Gang::SetSkipAllMsg()
{
	if (_IsVisable())
	{
		m_pID_LIST_TeamName->SetSkipAllMsg(true);
		m_pID_LIST_Lvl->SetSkipAllMsg(true);
		m_pID_LIST_Job->SetSkipAllMsg(true);
		m_pID_LIST_Work->SetSkipAllMsg(true);
		m_pID_LIST_Tong->SetSkipAllMsg(true);
		m_pID_LIST_Activity->SetSkipAllMsg(true);
		m_pID_LIST_GongXian->SetSkipAllMsg(true);
	}
}

// 卸载UI
bool CUI_ID_FRAME_Gang::_UnLoadUI()
{
	m_pID_FRAME_Gang = NULL;
	m_pID_PICTURE_TitleBg = NULL;
	m_pID_TEXT_RenShu = NULL;
	m_pID_TEXT_Warxishu = NULL;
	m_pID_BUTTON_ChenWei = NULL;
	m_pID_TEXT_RongYuWenZi = NULL;
	m_pID_TEXT_Announcement = NULL;
	m_pID_LIST_TeamName = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_SkillWenZi = NULL;
	m_pID_LISTIMG_Skill = NULL;
	m_pID_BUTTON_TeamName = NULL;
	m_pID_BUTTON_Lvl = NULL;
	m_pID_BUTTON_Job = NULL;
	m_pID_BUTTON_ChenHao = NULL;
	m_pID_BUTTON_GongXian = NULL;
	m_pID_BUTTON_Place = NULL;
	m_pID_LIST_Lvl = NULL;
	m_pID_LIST_Job = NULL;
	m_pID_LIST_Work = NULL;
	m_pID_LIST_Place = NULL;
	m_pID_BUTTON_Corps = NULL;
	m_pID_PICTURE_20025 = NULL;
	m_pID_PICTURE_19542 = NULL;
	m_pID_PICTURE_1310 = NULL;
	m_pID_PICTURE_27419 = NULL;
	m_pID_BUTTON_Close = NULL;
	m_pID_BUTTON_Help = NULL;
	m_pID_TEXT_Gang = NULL;
	m_pID_LIST_GangList = NULL;
	m_pID_PICTURE_GuildNum = NULL;
	m_pID_BUTTON_Work = NULL;
	m_pID_LIST_ChenHao = NULL;
	m_pID_LIST_GongXian = NULL;
	m_pID_TEXT_GangLvl = NULL;
	m_pID_BUTTON_Tong = NULL;
	m_pID_PROGRESS_GuildNum = NULL;
	m_pID_LIST_Tong = NULL;
	m_pID_PICTURE_5505 = NULL;
	m_pID_TEXT_ArrowTeamName = NULL;
	m_pID_TEXT_ArrowLvl = NULL;
	m_pID_TEXT_ArrowJob = NULL;
	m_pID_TEXT_ArrowWork = NULL;
	m_pID_TEXT_ArrowTong = NULL;
	m_pID_TEXT_ArrowGongXian = NULL;
	m_pID_CHECKBOX_ShowLeave = NULL;
	m_pID_TEXT_TongZ = NULL;
	m_pID_TEXT_Wait = NULL;
	m_pID_BUTTON_Alignment = NULL;
	m_pID_BUTTON_DroitInfo = NULL;
	m_pID_BUTTON_Quit = NULL;
	m_pID_BUTTON_Resume = NULL;
	m_pID_BUTTON_DISBAND = NULL;
	m_pID_BUTTON_Attribute = NULL;
	m_pID_LIST_Activity = NULL;
	m_pID_LIST_MEMBER = NULL;
	m_pID_CHECKBOX_Guild = NULL;
	m_pID_CHECKBOX_Country = NULL;
	m_pID_BUTTON_Activity = NULL;
	m_pID_TEXT_ArrowActivity = NULL;
	m_pID_TEXT_SelfWork = NULL;
	m_pID_TEXT_SelfGongXian = NULL;
	m_pID_TEXT_SelfActivity = NULL;
	m_pID_TEXT_SelfTong = NULL;
	m_pID_BUTTON_LeavePosition = NULL;
	m_pID_BUTTON_ZhuanRang = NULL;
	/*m_pID_BUTTON_ReturnTong = NULL;*/
	m_pID_BUTTON_ChangeTongName = NULL;
	m_pID_BUTTON_DelTong = NULL;
	m_pID_BUTTON_ADDTong = NULL;
	m_pID_BUTTON_ADD = NULL;
	m_pID_BUTTON_Announcement = NULL;
	m_pID_BUTTON_Del = NULL;
	m_pID_BUTTON_DelAssistant = NULL;
	m_pID_BUTTON_Appoint = NULL;
	//m_pID_BUTTON_Tong6 = NULL;
	m_pID_BUTTON_Tong5 = NULL;
	m_pID_BUTTON_Tong4 = NULL;
	m_pID_BUTTON_Tong3 = NULL;
	m_pID_BUTTON_Tong2 = NULL;
	m_pID_BUTTON_Tong1 = NULL;
	m_pID_BUTTON_Tong25 = NULL;
	m_pID_BUTTON_Tong24 = NULL;
	m_pID_BUTTON_Tong23 = NULL;
	m_pID_BUTTON_Tong22 = NULL;
	m_pID_BUTTON_Tong21 = NULL;
	m_pID_BUTTON_AppointAssistant = NULL;
	m_pID_TEXT_LeaderName = NULL;
	m_pID_TEXT_RongYu = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_TEXT_Tip = NULL;
	m_pID_BUTTON_FamilyCreate = NULL;
	m_pID_BUTTON_FamilyRename = NULL;
	m_pID_BUTTON_FamilyChange = NULL;
	m_pID_BUTTON_AppointTong = NULL;
	m_pID_BUTTON_FamilyMaster = NULL;
	m_pID_BUTTON_Depose = NULL;
	m_pID_BUTTON_ZRFamily = NULL;
	m_pID_BUTTON_ZCFamily = NULL;
	m_pID_BUTTON_ChangeZZ = NULL;
	m_pID_LIST_Line = NULL;
	m_ctlGuildGroup.Clear();
	m_ctlBangzhongGroup.Clear();
	m_ctlTangzhuGroup.Clear();
	m_ctlFubangzhuGroup.Clear();
	m_ctlBangzhuGroup.Clear();
	m_ctlAppointGroup.Clear();
	m_ctlActiveGroup.Clear();
	m_ctlFmailyGroup.Clear();
	m_ctlAnotherFmailyGroup.Clear();

	return theUiManager.RemoveFrame( "Data\\UI\\Gang.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_Gang::_IsVisable()
{
	if ( !m_pID_FRAME_Gang )
		return false;
	return m_pID_FRAME_Gang->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_Gang::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_Gang )
		return;
	if (!thePlayerRole.GetGangMgr() || thePlayerRole.GetGangMgr()->GetGuildID() == GuildDefine::InitID)
	{
		//提示
		m_pID_FRAME_Gang->SetVisable(false);
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_FindGuildNpc),"",CUI_ID_FRAME_MessageBox::eTypeConfirm,false);
		return;
	}
	if (bVisable)
	{
		m_pID_CHECKBOX_ShowLeave->SetCheck(true);
		m_bShowOfflineMember = m_pID_CHECKBOX_ShowLeave->IsChecked();
		SetNeedRefresh(true);
		Refresh();
	}

	m_pID_FRAME_Gang->SetVisable( bVisable );
}

//-------------------------------------------------------------------------------------------------------
void CUI_ID_FRAME_Gang::SetTextWait(const char* pName)
{
	if(!pName)
		return;
	m_bWaitText = false;
	if (IsUILoad())
	{
		m_pID_TEXT_Wait->SetText(pName);
	}
}

void CUI_ID_FRAME_Gang::SetGuildGroup()
{
	m_ctlGuildGroup.Clear();
	m_ctlGuildGroup.AddControl(m_pID_TEXT_RenShu);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_Warxishu);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_ChenWei);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_RongYuWenZi);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_Announcement);
	m_ctlGuildGroup.AddControl(m_pID_LIST_TeamName);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_Name);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_SkillWenZi);
	m_ctlGuildGroup.AddControl(m_pID_LISTIMG_Skill);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_TeamName);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Lvl);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Job);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_ChenHao);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_GongXian);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Place);
	m_ctlGuildGroup.AddControl(m_pID_LIST_Lvl);
	m_ctlGuildGroup.AddControl(m_pID_LIST_Job);
	m_ctlGuildGroup.AddControl(m_pID_LIST_Work);
	m_ctlGuildGroup.AddControl(m_pID_LIST_Place);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Corps);
	m_ctlGuildGroup.AddControl(m_pID_PICTURE_20025);
	m_ctlGuildGroup.AddControl(m_pID_PICTURE_19542);
	m_ctlGuildGroup.AddControl(m_pID_PICTURE_1310);
	m_ctlGuildGroup.AddControl(m_pID_PICTURE_27419);
	//m_ctlGuildGroup.AddControl(m_pID_BUTTON_Close);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Help);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_Gang);
	m_ctlGuildGroup.AddControl(m_pID_LIST_GangList);
	m_ctlGuildGroup.AddControl(m_pID_PICTURE_GuildNum);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Work);
	m_ctlGuildGroup.AddControl(m_pID_LIST_ChenHao);
	m_ctlGuildGroup.AddControl(m_pID_LIST_GongXian);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_GangLvl);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Tong);
	m_ctlGuildGroup.AddControl(m_pID_PROGRESS_GuildNum);
	m_ctlGuildGroup.AddControl(m_pID_LIST_Tong);
	m_ctlGuildGroup.AddControl(m_pID_PICTURE_5505);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_ArrowTeamName);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_ArrowLvl);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_ArrowJob);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_ArrowWork);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_ArrowTong);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_ArrowGongXian);
	m_ctlGuildGroup.AddControl(m_pID_CHECKBOX_ShowLeave);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_TongZ);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_Wait);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Alignment);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_DroitInfo);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Quit);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Resume);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_DISBAND);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Attribute);
	m_ctlGuildGroup.AddControl(m_pID_LIST_Activity);
	m_ctlGuildGroup.AddControl(m_pID_LIST_MEMBER);
	//m_ctlGuildGroup.AddControl(m_pID_CHECKBOX_Guild);
	//m_ctlGuildGroup.AddControl(m_pID_CHECKBOX_Country);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Activity);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_ArrowActivity);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_SelfWork);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_SelfGongXian);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_SelfActivity);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_SelfTong);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_LeavePosition);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_ZhuanRang);
	//m_ctlGuildGroup.AddControl(m_pID_BUTTON_ReturnTong);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_ChangeTongName);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_DelTong);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_ADDTong);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_ADD);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Announcement);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Del);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_DelAssistant);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Appoint);
	//m_ctlGuildGroup.AddControl(m_pID_BUTTON_Tong6);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Tong5);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Tong4);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Tong3);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Tong2);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Tong1);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_AppointAssistant);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_LeaderName);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_RongYu);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_Money);
	m_ctlGuildGroup.AddControl(m_pID_TEXT_Tip);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_FamilyCreate);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_FamilyRename);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_FamilyChange);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_AppointTong);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_FamilyMaster);
	m_ctlGuildGroup.AddControl(m_pID_BUTTON_Depose);
}

void CUI_ID_FRAME_Gang::SetControlGroupForBangzhong()
{
	m_ctlBangzhongGroup.Clear();
	m_ctlBangzhongGroup.AddControl(m_pID_TEXT_Tip);
	m_ctlBangzhongGroup.AddControl(m_pID_BUTTON_Quit);
}

void CUI_ID_FRAME_Gang::SetControlGroupForTangzhu()
{
	m_ctlTangzhuGroup.Clear();
	m_ctlTangzhuGroup.AddControl(m_pID_TEXT_Tip);
	m_ctlTangzhuGroup.AddControl(m_pID_BUTTON_ADD);
	m_ctlTangzhuGroup.AddControl(m_pID_BUTTON_LeavePosition);
	m_ctlTangzhuGroup.AddControl(m_pID_BUTTON_ZhuanRang);
	m_ctlTangzhuGroup.AddControl(m_pID_BUTTON_ZRFamily);	//转入分堂
	m_ctlTangzhuGroup.AddControl(m_pID_BUTTON_ZCFamily);	//转入分堂
}

void CUI_ID_FRAME_Gang::SetControlGroupForFubangzhu()
{
	m_ctlFubangzhuGroup.Clear();
	m_ctlFubangzhuGroup.AddControl(m_pID_TEXT_Tip);
	m_ctlFubangzhuGroup.AddControl(m_pID_BUTTON_ADD);
	m_ctlFubangzhuGroup.AddControl(m_pID_BUTTON_Del);
	m_ctlFubangzhuGroup.AddControl(m_pID_BUTTON_LeavePosition);
	m_ctlFubangzhuGroup.AddControl(m_pID_BUTTON_ZhuanRang);
	m_ctlFubangzhuGroup.AddControl(m_pID_BUTTON_ZRFamily);	//转入分堂
	m_ctlFubangzhuGroup.AddControl(m_pID_BUTTON_ZCFamily);	//转入分堂
}

void CUI_ID_FRAME_Gang::SetControlGroupForBangzhu()
{
	m_ctlBangzhuGroup.Clear();
	m_ctlBangzhuGroup.AddControl(m_pID_BUTTON_Announcement);
	m_ctlBangzhuGroup.AddControl(m_pID_BUTTON_FamilyCreate);
	m_ctlBangzhuGroup.AddControl(m_pID_BUTTON_FamilyRename);
	m_ctlBangzhuGroup.AddControl(m_pID_BUTTON_FamilyChange);
	m_ctlBangzhuGroup.AddControl(m_pID_BUTTON_ADD);
	m_ctlBangzhuGroup.AddControl(m_pID_BUTTON_Del);
	m_ctlBangzhuGroup.AddControl(m_pID_BUTTON_Appoint);
	m_ctlBangzhuGroup.AddControl(m_pID_BUTTON_ZhuanRang);
	m_ctlBangzhuGroup.AddControl(m_pID_BUTTON_ZRFamily);	//转入分堂
	m_ctlBangzhuGroup.AddControl(m_pID_BUTTON_ZCFamily);	//转入分堂
	m_ctlBangzhuGroup.AddControl(m_pID_BUTTON_ChangeZZ);	//修改宗旨
//	m_ctlBangzhuGroup.AddControl(m_pID_BUTTON_LeavePosition);
}

void CUI_ID_FRAME_Gang::SetMainMenu()
{
	m_mainMenu.Clear();
	m_mainMenu.AddControl(m_pID_BUTTON_Announcement);
	m_mainMenu.AddControl(m_pID_BUTTON_FamilyCreate);
	m_mainMenu.AddControl(m_pID_BUTTON_FamilyRename);
	m_mainMenu.AddControl(m_pID_BUTTON_FamilyChange);
	m_mainMenu.AddControl(m_pID_BUTTON_ADD);
	m_mainMenu.AddControl(m_pID_BUTTON_Del);
	m_mainMenu.AddControl(m_pID_BUTTON_Appoint);
	m_mainMenu.AddControl(m_pID_BUTTON_ZhuanRang);
	m_mainMenu.AddControl(m_pID_BUTTON_ZRFamily);	//转入分堂
	m_mainMenu.AddControl(m_pID_BUTTON_ZCFamily);	//转入分堂
	m_mainMenu.AddControl(m_pID_BUTTON_ChangeZZ);	//修改宗旨
	m_mainMenu.AddControl(m_pID_BUTTON_Quit);
	m_mainMenu.AddControl(m_pID_BUTTON_LeavePosition);
}

void CUI_ID_FRAME_Gang::SetControlGroupForAppoint()
{
	m_ctlAppointGroup.Clear();
	m_ctlAppointGroup.AddControl(m_pID_BUTTON_AppointAssistant);
	m_ctlAppointGroup.AddControl(m_pID_BUTTON_FamilyMaster);
	m_ctlAppointGroup.AddControl(m_pID_BUTTON_Depose);
}

void CUI_ID_FRAME_Gang::SetControlGroupForFamilyChangeName()
{
	m_vctFamilyAll.clear();
	m_vctFamilyAll.push_back(m_pID_BUTTON_Tong1);
	m_vctFamilyAll.push_back(m_pID_BUTTON_Tong2);
	m_vctFamilyAll.push_back(m_pID_BUTTON_Tong3);
	m_vctFamilyAll.push_back(m_pID_BUTTON_Tong4);
	m_vctFamilyAll.push_back(m_pID_BUTTON_Tong5);
	//m_vctFamilyAll.push_back(m_pID_BUTTON_Tong6);
}

void CUI_ID_FRAME_Gang::SetControlGroupTransferBangzhong()
{
	m_vctTransferBangzhongAll.clear();
	m_vctTransferBangzhongAll.push_back(m_pID_BUTTON_Tong21);
	m_vctTransferBangzhongAll.push_back(m_pID_BUTTON_Tong22);
	m_vctTransferBangzhongAll.push_back(m_pID_BUTTON_Tong23);
	m_vctTransferBangzhongAll.push_back(m_pID_BUTTON_Tong24);
	m_vctTransferBangzhongAll.push_back(m_pID_BUTTON_Tong25);
}

void CUI_ID_FRAME_Gang::SetControlActiveGroup()
{
	m_ctlActiveGroup.Clear();
	m_ctlActiveGroup.AddControl(m_pID_TEXT_Tip);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_ADD);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_Del);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_LeavePosition);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_Quit);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_ZhuanRang);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_Announcement);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_FamilyCreate);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_FamilyRename);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_FamilyChange);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_Appoint);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_AppointAssistant);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_FamilyMaster);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_Depose);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_Tong1);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_Tong2);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_Tong3);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_Tong4);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_Tong5);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_Tong21);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_Tong22);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_Tong23);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_Tong24);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_Tong25);
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_ZRFamily);	//转入分堂
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_ZCFamily);	//转入分堂
	m_ctlActiveGroup.AddControl(m_pID_BUTTON_ChangeZZ);	//修改宗旨
	//m_ctlActiveGroup.AddControl(m_pID_TEXT_Warxishu);
}

void CUI_ID_FRAME_Gang::ClearAllList()
{
	m_pID_LIST_MEMBER->Clear();
	m_pID_LIST_TeamName->Clear();
	m_pID_LIST_Lvl->Clear();
	m_pID_LIST_Job->Clear();
	m_pID_LIST_Work->Clear();
	m_pID_LIST_Tong->Clear();
	m_pID_LIST_Activity->Clear();
	m_pID_LIST_GongXian->Clear();
	m_pID_LIST_Line->Clear();
}

#include "ui\GuildApply.h"
bool CUI_ID_FRAME_Gang::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
// 	if( !m_pID_FRAME_Gang )
// 		return false;
// 	SetVisable(false);

	s_CUI_ID_FRAME_GuildApply.SetVisable(true);

	return true;
}

void CUI_ID_FRAME_Gang::Refresh()
{
	StoreAllMember();

	ShowSortArrow();

	SortAndRefresh();

	/*SetBoolState();	*/

	SetCtlText();	

	SetButtonState();

	SetAllList();

	SetNeedRefresh(false);
	
	m_pID_CHECKBOX_ShowLeave->SetCheck(m_pID_CHECKBOX_ShowLeave->IsChecked());
	
}

void CUI_ID_FRAME_Gang::SetAllList()
{
	ClearAllList();
	
	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if(pGuild == NULL || pGuild->GetGuildID() == GuildDefine::InitID)
	{
		return;
	}
	
	if (!m_bShowOfflineMember)
	{
		ShowOnlineMember();
	}
	else
	{
		ShowAllMember();
	}
}

bool SortByGreatFamily(GuildMember* s1, GuildMember* s2)
{
	return s1->GetFamilyID() < s2->GetFamilyID();
}


enum eFamilyID
{
	eKey_FirstFamily = 1,
	eKey_SecondFamily,
	eKey_ThirdFamily,
	eKey_FourthFamily,
	eKey_FifthFamily,
};

void CUI_ID_FRAME_Gang::StoreAllMember()
{
	ResetMember();

	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if(pGuild == NULL || pGuild->GetGuildID() == GuildDefine::InitID)
	{
		return;
	}

	m_nAllMemberNum = pGuild->GetMemberCount();
	for (int i = 0; i < m_nAllMemberNum; ++i)
	{
		if (pGuild->GetMember(i)->GetPosition() == GuildDefine::Position_Master)
		{
			m_pMaster = pGuild->GetMember(i);
			continue;
		}
		if (pGuild->GetMember(i)->GetPosition() == GuildDefine::Position_ViceMaster)
		{
			m_pViceMaster = pGuild->GetMember(i);
			continue;
		}
		if (pGuild->GetMember(i)->GetPosition() == GuildDefine::Position_FamilyMaster)
		{
			m_vctFamilyMaster.push_back(pGuild->GetMember(i));
			continue;
		}
		if (pGuild->GetMember(i)->GetFamilyID() == eKey_FirstFamily)
		{
			m_vctFirstFamilyMember.push_back(pGuild->GetMember(i));
			continue;
		}
		m_vctOtherMember.push_back(pGuild->GetMember(i));
	}
	//std::sort(m_vctFamilyMaster.begin(), m_vctFamilyMaster.end(), SortByGreatFamily);
}

void CUI_ID_FRAME_Gang::ShowOnlineMember()
{
	m_vctAllMember.clear();
	AddOnlineMember();
}

void CUI_ID_FRAME_Gang::ShowAllMember()
{
	m_vctAllMember.clear();
	AddOnlineMember();
	AddOfflineMember();
}

void CUI_ID_FRAME_Gang::AddOnlineMember()
{
	for (std::vector<GuildMember*>::iterator iter = m_vctOnLineMember.begin(); iter != m_vctOnLineMember.end(); ++iter)
	{
		DWORD color = 0;
		if ((*iter))
		{
			if ((*iter)->GetFamilyID() == eKey_FirstFamily)
			{
				color = Color_Config.getColor(CC_OrangeName);
			}

			m_vctAllMember.push_back((*iter));
			AddToList((*iter), color);
		}
	}
}

void CUI_ID_FRAME_Gang::AddOfflineMember()
{
	for (std::vector<GuildMember*>::iterator iter = m_vctOffLineMember.begin(); iter != m_vctOffLineMember.end(); ++iter)
	{
		DWORD color = Color_Config.getColor(CC_GUILD_OFFLINE);;
		if ((*iter))
		{
			m_vctAllMember.push_back((*iter));
			AddToList((*iter), color);
		}
	}
}

//void CUI_ID_FRAME_Gang::ShowOnlyOnlineMember()
//{
//	m_vctAllMember.clear();
//	if (m_pMaster && m_pMaster->GetOnLine())
//	{
//		DWORD color = 0;
//		if (m_pMaster->GetFamilyID() == eKey_FirstFamily)
//		{
//			color = Color_Config.getColor(CC_OrangeName);
//		}
//		
//		m_vctAllMember.push_back(m_pMaster);
//		AddToList(m_pMaster, color);
//	}
//
//	if (m_pViceMaster && m_pViceMaster->GetOnLine())
//	{
//		DWORD color = 0;
//		if (m_pViceMaster->GetFamilyID() == eKey_FirstFamily)
//		{
//			color = Color_Config.getColor(CC_OrangeName);
//		}
//
//		m_vctAllMember.push_back(m_pViceMaster);
//		AddToList(m_pViceMaster, color);
//	}
//	
//	for (std::vector<GuildMember*>::iterator iter = m_vctFamilyMaster.begin(); iter != m_vctFamilyMaster.end(); ++iter)
//	{
//		if (!(*iter)->GetOnLine())
//		{
//			continue;
//		}
//		DWORD color = 0;
//		if ((*iter)->GetFamilyID() == eKey_FirstFamily)
//		{
//			color = Color_Config.getColor(CC_OrangeName);
//		}
//
//		m_vctAllMember.push_back(*iter);
//		AddToList((*iter), color);
//	}
//	
//	for (std::vector<GuildMember*>::iterator iter = m_vctFirstFamilyMember.begin(); iter != m_vctFirstFamilyMember.end(); ++iter)
//	{
//		if (!(*iter)->GetOnLine())
//		{
//			continue;
//		}
//		m_vctAllMember.push_back(*iter);
//		AddToList((*iter), Color_Config.getColor(CC_OrangeName));
//	}
//	
//	for (std::vector<GuildMember*>::iterator iter = m_vctOtherMember.begin(); iter != m_vctOtherMember.end(); ++iter)
//	{
//		if (!(*iter)->GetOnLine())
//		{
//			continue;
//		}
//		m_vctAllMember.push_back(*iter);
//		AddToList((*iter));
//	}
//}

//void CUI_ID_FRAME_Gang::ShowAllMember()
//{
//	m_vctAllMember.clear();
//	if (m_pMaster)
//	{
//		m_vctAllMember.push_back(m_pMaster);
//		DWORD color = 0;
//		if (m_pMaster->GetFamilyID() == eKey_FirstFamily)
//		{
//			color = Color_Config.getColor(CC_OrangeName);
//		}
//		if (!m_pMaster->GetOnLine())
//		{
//			color = Color_Config.getColor(CC_GUILD_OFFLINE);
//		}
//		
//		AddToList(m_pMaster, color);
//	}
//
//	if (m_pViceMaster)
//	{
//		m_vctAllMember.push_back(m_pViceMaster);
//		DWORD color = 0;
//		if (m_pViceMaster->GetFamilyID() == eKey_FirstFamily)
//		{
//			color = Color_Config.getColor(CC_OrangeName);
//		}
//		if (!m_pViceMaster->GetOnLine())
//		{
//			color = Color_Config.getColor(CC_GUILD_OFFLINE);
//		}
//
//		AddToList(m_pViceMaster, color);
//	}
//
//	for (std::vector<GuildMember*>::iterator iter = m_vctFamilyMaster.begin(); iter != m_vctFamilyMaster.end(); ++iter)
//	{
//		m_vctAllMember.push_back(*iter);
//		DWORD color = 0;
//		if ((*iter)->GetFamilyID() == eKey_FirstFamily)
//		{
//			color = Color_Config.getColor(CC_OrangeName);
//		}
//		if (!(*iter)->GetOnLine())
//		{
//			color = Color_Config.getColor(CC_GUILD_OFFLINE);
//		}
//
//		AddToList((*iter), color);
//	}
//
//	for (std::vector<GuildMember*>::iterator iter = m_vctFirstFamilyMember.begin(); iter != m_vctFirstFamilyMember.end(); ++iter)
//	{
//		m_vctAllMember.push_back(*iter);
//		DWORD color = Color_Config.getColor(CC_OrangeName);
//		if (!(*iter)->GetOnLine())
//		{
//			color = Color_Config.getColor(CC_GUILD_OFFLINE);
//		}
//		
//		AddToList((*iter), color);
//	}
//
//	for (std::vector<GuildMember*>::iterator iter = m_vctOtherMember.begin(); iter != m_vctOtherMember.end(); ++iter)
//	{
//		m_vctAllMember.push_back(*iter);
//		DWORD color = 0;
//		if (!(*iter)->GetOnLine())
//		{
//			color = Color_Config.getColor(CC_GUILD_OFFLINE);
//		}
//		
//		AddToList((*iter), color);
//	}	
//}

void CUI_ID_FRAME_Gang::AddToList(GuildMember* pMember, DWORD color)
{
	ControlList::S_List	stItem;
	char szText[128] = {0};
	stItem.SetData( "" );
	m_pID_LIST_MEMBER->AddItem(&stItem, NULL, false);
	stItem.clear();
	
	//名字
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%s", pMember->GetName());
	stItem.SetData(szText, 0, NULL, color);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_TeamName->AddItem(&stItem, NULL, false);
	stItem.clear();
	memset(szText, 0, sizeof(szText));

	//等级
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d", pMember->GetLevel());
	stItem.SetData(szText, 0, NULL, color);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Lvl->AddItem(&stItem, NULL, false);
	stItem.clear();
	memset(szText, 0, sizeof(szText));

	//职业
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%s", GetProfessionByID(pMember->GetProfession()));
	stItem.SetData(szText, 0, NULL, color);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Job->AddItem(&stItem, NULL, false);
	stItem.clear();
	memset(szText, 0, sizeof(szText));

	//职位
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%s", GetPositionByID(pMember->GetPosition()));
	stItem.SetData(szText, 0, NULL, color);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Work->AddItem(&stItem, NULL, false);
	stItem.clear();
	memset(szText, 0, sizeof(szText));

	//家族
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%s", GetFamilyName(pMember->GetFamilyID()));
	stItem.SetData(szText, 0, NULL, color);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Tong->AddItem(&stItem, NULL, false);
	stItem.clear();
	memset(szText, 0, sizeof(szText));

	//活跃度
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d", pMember->GetActivity());
	stItem.SetData(szText, 0, NULL, color);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Activity->AddItem(&stItem, NULL, false);
	stItem.clear();
	memset(szText, 0, sizeof(szText));

	//帮贡
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d", pMember->GetOffer());
	stItem.SetData(szText, 0, NULL, color);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_GongXian->AddItem(&stItem, NULL, false);
	stItem.clear();
	memset(szText, 0, sizeof(szText));
	//分线
	//MeSprintf_s(szText,sizeof(szText),"%s",);
	stItem.SetData("1线", 0,NULL,color);  //此处因为服务器的分线功能还没有添加，所以暂时写死。等服务器功能加好之后另行更改。
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Line->AddItem(&stItem,NULL,false);
	
}

void CUI_ID_FRAME_Gang::ID_CHECKBOX_ShowLeaveOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Gang )
		return;
	
	if (!*pbChecked)
	{
		m_bShowOfflineMember = false;
	}
	else
	{
		m_bShowOfflineMember = true;
	}

	SetNeedRefresh(true);
}

void CUI_ID_FRAME_Gang::SetButtonState()
{
	if (!theHeroGame.GetPlayerMgr()->GetMe())
	{
		return;
	}

	m_pID_CHECKBOX_Guild->SetCheck(true);

/*
	m_ctlActiveGroup.SetVisible(false);

	if (!thePlayerRole.GetGangMgr() || thePlayerRole.GetGangMgr()->GetGuildID() == GuildDefine::InitID)
	{
		return;
	}

	switch (theHeroGame.GetPlayerMgr()->GetMe()->GetGangPosition())
	{
	case GuildDefine::Position_Member:
		{
			m_ctlBangzhongGroup.SetVisible(true);
		}
		break;
	case GuildDefine::Position_FamilyMaster:
		{
			m_ctlTangzhuGroup.SetVisible(true);
		}
		break;
	case GuildDefine::Position_ViceMaster:
		{
			m_ctlFubangzhuGroup.SetVisible(true);
		}
		break;
	case GuildDefine::Position_Master:
		{
			m_ctlBangzhuGroup.SetVisible(true);
		}
		break;
	}
*/

	m_ctlActiveGroup.SetVisible(false);
	m_mainMenu.SetVisible(true);	
	EnableControlGroup(&m_mainMenu, false);
	if (!thePlayerRole.GetGangMgr() || thePlayerRole.GetGangMgr()->GetGuildID() == GuildDefine::InitID)
	{
		return;
	}

	switch (theHeroGame.GetPlayerMgr()->GetMe()->GetGangPosition())
	{
	case GuildDefine::Position_Member:
		{
			EnableControlGroup(&m_ctlBangzhongGroup);
		}
		break;
	case GuildDefine::Position_FamilyMaster:
		{
			EnableControlGroup(&m_ctlTangzhuGroup);
		}
		break;
	case GuildDefine::Position_ViceMaster:
		{
			EnableControlGroup(&m_ctlFubangzhuGroup);
		}
		break;
	case GuildDefine::Position_Master:
		{
			EnableControlGroup(&m_ctlBangzhuGroup);
		}
		break;
	}

}

void CUI_ID_FRAME_Gang::ResetCtlText()
{
	m_pID_TEXT_Announcement->Clear();
	m_pID_TEXT_Name->Clear();
	m_pID_TEXT_GangLvl->Clear();
	m_pID_TEXT_RenShu->Clear();
	m_pID_TEXT_Warxishu->Clear();
	m_pID_TEXT_SelfWork->Clear();
	m_pID_TEXT_SelfGongXian->Clear();
	m_pID_TEXT_SelfActivity->Clear();
	m_pID_TEXT_SelfTong->Clear();
	m_pID_TEXT_Tip->Clear();
}

void CUI_ID_FRAME_Gang::SetCtlText()
{
	ResetCtlText();
	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if(pGuild == NULL || pGuild->GetGuildID() == GuildDefine::InitID)
	{
		return;
	}

	if(m_pID_TEXT_Announcement)
	{
		//m_pID_TEXT_Announcement->SetText(pGuild->GetGuildAim());
		m_pID_TEXT_Announcement->SetText(pGuild->GetGuildNotice());
	}
	GuildMember* pMe = pGuild->FindByDBId(g_nCharacterDBID);
	if (!pMe)
	{
		return;
	}

	m_pID_TEXT_Name->SetText(pGuild->GetGuildName());
	m_pID_TEXT_GangLvl->SetText(pGuild->GetGuildLevel());
	
	char szText[128] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d/%d", pGuild->GetMemberOnlineCount(), pGuild->GetMemberCount());

	m_pID_TEXT_RenShu->SetText(szText);
	m_pID_TEXT_SelfWork->SetText(GetPositionByID(pMe->GetPosition()));
	m_pID_TEXT_SelfGongXian->SetText(pMe->GetOffer());
	m_pID_TEXT_SelfActivity->SetText(pMe->GetActivity());
	m_pID_TEXT_SelfTong->SetText(GetFamilyName(pMe->GetFamilyID()));

	/*
	*	Author 2012-10-29 zhuxincong
	*	DESC: 帮派实力显示
	*/

	m_nAllMemberNum = pGuild->GetMemberCount();
	unsigned int nTotalLevel = 0; 
	for (int i = 0; i < m_nAllMemberNum; ++i)
	{

		nTotalLevel += pGuild->GetMember(i)->GetLevel();
	}
	//（帮会总人数等级和/帮会最大人数）*（0+帮会等级*系数）
	const GuildConfig::StrengthSetting& xSetting = theGuildConfig.GetStrengthSetting();
	const GuildConfig::LevelSetting* pSetting = theGuildConfig.GetLevelSetting( pGuild->GetGuildLevel() );
	int fStrength = ( static_cast< float >( nTotalLevel ) /  pSetting->GetMaxCount() ) * ( xSetting.GetBaseModulus() + static_cast< float >( pGuild->GetGuildLevel() ) * xSetting.GetExtendModulus() );
	
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,"%d",fStrength);
	m_pID_TEXT_Warxishu->SetText(szText);

}

bool CUI_ID_FRAME_Gang::CheckIsKingGuild() const
{
	if (theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->GetCountryTitle() == CountryDefine::Title_King)
	{
		return true;
	}

	return false;
}

bool CUI_ID_FRAME_Gang::CheckCanTransferPosition() const
{
	if (!m_pAcceptPositionMember)
	{
		return false;
	}

	if (!theHeroGame.GetPlayerMgr()->GetMe())
	{
		return false;
	}
	
	int nMyPosition = theHeroGame.GetPlayerMgr()->GetMe()->GetGangPosition();
	int nMemberPosition = m_pAcceptPositionMember->GetPosition();
	if (nMyPosition - nMemberPosition == 1)
	{
		return true;
	}
	
	return false;
}

void CUI_ID_FRAME_Gang::ShowTransferPositionInfo()
{
	if (!(theHeroGame.GetPlayerMgr()) || !(theHeroGame.GetPlayerMgr()->GetMe()) || !m_pAcceptPositionMember)
	{
		return;
	}

	int nMyPosition = theHeroGame.GetPlayerMgr()->GetMe()->GetGangPosition();
	char szText[256] = {0};
	switch (nMyPosition)
	{
	case GuildDefine::Position_Master:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_TransferPosition_Master), theHeroGame.GetPlayerMgr()->GetMe()->GetName(), m_pAcceptPositionMember->GetName(), m_pAcceptPositionMember->GetName());
		}
		break;
	case GuildDefine::Position_ViceMaster:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_TransferPosition_ViceMaster), theHeroGame.GetPlayerMgr()->GetMe()->GetName(), m_pAcceptPositionMember->GetName(), m_pAcceptPositionMember->GetName());
		}
		break;
	case GuildDefine::Position_FamilyMaster:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_TransferPosition_FamilyMaster), theHeroGame.GetPlayerMgr()->GetMe()->GetName(), m_pAcceptPositionMember->GetName(), m_pAcceptPositionMember->GetName());
		}
		break;
	default:
		break;
	}

	CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Guild_Belongs, szText);
	//CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Info_GuildInfo, szText);
}

bool CUI_ID_FRAME_Gang::ZhuanRang(char m_ok,void *data)
{
	if (m_ok&& static_cast<GuildMember* >(data) != NULL)
	{
		MsgGuildTransferPositionReq msg;
		msg.nPlayerID = static_cast<GuildMember* >(data)->GetID();
		GettheNetworkInput().SendMsg(&msg);
	}
	return true;
}
//职位转让
bool CUI_ID_FRAME_Gang::ID_BUTTON_ZhuanRangOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	int nIndex = m_pID_LIST_MEMBER->GetCurSelIndex();
	if (nIndex == -1 || nIndex >= m_vctAllMember.size())
	{
		ShowSelectNothingMessage();
		return false;
	}
	
	m_pAcceptPositionMember = m_vctAllMember[nIndex];

	if (!CheckCanTransferPosition())
	{
		ShowUnableTransferPosition();
		return false;
	}
//没有国家之说，所以去掉判断
// 	if (CheckIsKingGuild())
// 	{
// 		ShowUnableTransferPositionWhenIsKingGuild();
// 		return false;
// 	}

	ShowTransferPositionInfo();
	char temp[64];
	MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eTextGang_ZhuanRang),m_pAcceptPositionMember->GetName());
	s_CUI_ID_FRAME_MessageBox.Show(temp,"",CUI_ID_FRAME_MessageBox::eTypeYesNo,false,ZhuanRang,(void*)m_pAcceptPositionMember,sizeof(GuildMember));
	return true;
}

//创建家族
bool CUI_ID_FRAME_Gang::ID_BUTTON_FamilyCreateOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	s_CUI_ID_FRAME_ADD_MEMBER.SetFrameType(CUI_ID_FRAME_ADD_MEMBER::eFrameType_CreateFamily);
	s_CUI_ID_FRAME_ADD_MEMBER.SetVisable(true);
	return true;
}

bool CUI_ID_FRAME_Gang::LeaveGuild(char m_ok,void *data)
{
	if (m_ok)
	{
		MsgLeaveGuildReq msg;
		GettheNetworkInput().SendMsg(&msg);

		s_CUI_ID_FRAME_Gang.SetVisable(false);

		// 自己离开公会, 在右下角提示
		char szInfo[MAX_PATH] = {0};
		MeSprintf( szInfo, MAX_PATH - 1, theXmlString.GetString(eText_SelfQuitGuildTip) );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Server_Others_Success, szInfo );
	}
	return true;
}
//离开帮会
bool CUI_ID_FRAME_Gang::ID_BUTTON_QuitOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eTextGuild_Leave_Check),"",CUI_ID_FRAME_MessageBox::eTypeYesNo,false,LeaveGuild);
	return true;
}

//辞去职务
bool CUI_ID_FRAME_Gang::ID_BUTTON_LeavePositionOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	MsgGuildResignPositionReq msg;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

//任命副帮主
bool CUI_ID_FRAME_Gang::ID_BUTTON_AppointAssistantOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	int nIndex = m_pID_LIST_MEMBER->GetCurSelIndex();
	if (nIndex == -1 || nIndex >= m_vctAllMember.size())
	{
		ShowSelectNothingMessage();
		return false;
	}

	if (IsOperateOnMyself(m_vctAllMember[nIndex]->GetID()))
	{
		return false;
	}

	/*m_bShowAppointButton = true;*/
	MsgGuildAssignPositionReq msg;
	msg.nPlayerID = m_vctAllMember[nIndex]->GetID();
	msg.uchPosition = GuildDefine::Position_ViceMaster;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

bool CUI_ID_FRAME_Gang::IsOperateOnMyself(int nId)
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

//任命家族长
bool CUI_ID_FRAME_Gang::ID_BUTTON_FamilyMasterOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	int nIndex = m_pID_LIST_MEMBER->GetCurSelIndex();
	if (nIndex == -1 || nIndex >= m_vctAllMember.size())
	{
		ShowSelectNothingMessage();
		return false;
	}

	if (IsOperateOnMyself(m_vctAllMember[nIndex]->GetID()))
	{
		return false;
	}

	//m_bShowAppointButton = true;
	MsgGuildAssignPositionReq msg;
	msg.nPlayerID = m_vctAllMember[nIndex]->GetID();
	msg.uchPosition = GuildDefine::Position_FamilyMaster;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

//免职
bool CUI_ID_FRAME_Gang::ID_BUTTON_DeposeOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	int nIndex = m_pID_LIST_MEMBER->GetCurSelIndex();
	if (nIndex == -1 || nIndex >= m_vctAllMember.size())
	{
		ShowSelectNothingMessage();
		return false;
	}

	if (IsOperateOnMyself(m_vctAllMember[nIndex]->GetID()))
	{
		return false;
	}

	/*m_bShowAppointButton = true;*/
	MsgGuildAssignPositionReq msg;
	msg.nPlayerID = m_vctAllMember[nIndex]->GetID();
	msg.uchPosition = GuildDefine::Position_Member;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

//邀请入帮
bool CUI_ID_FRAME_Gang::ID_BUTTON_ADDOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	s_CUI_ID_FRAME_ADD_MEMBER.SetFrameType(CUI_ID_FRAME_ADD_MEMBER::eFrameType_AddMember);
	s_CUI_ID_FRAME_ADD_MEMBER.SetVisable(true);
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool CUI_ID_FRAME_Gang::GuildDelMemberCallBack(const char bPressYesButton, void *pData)
{
	if (!pData)
	{
		return false;
	}
	
	if (!bPressYesButton)
	{
		return false;
	}
	
	unsigned int* nId = (unsigned int *)pData;

	if (IsOperateOnMyself(*nId))
	{
		return false;
	}

	MsgKickGuildReq msg;
	msg.nPlayerID = *nId;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

// 帮会开除
bool CUI_ID_FRAME_Gang::ID_BUTTON_DelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	int nIndex = m_pID_LIST_MEMBER->GetCurSelIndex();
	if (nIndex == -1 || nIndex >= m_vctAllMember.size())
	{
		ShowSelectNothingMessage();
		return false;
	}

	unsigned int nId = m_vctAllMember[nIndex]->GetID();
	char szText[256];
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_DelMember), m_vctAllMember[nIndex]->GetName());
	s_CUI_ID_FRAME_MessageBox.Show(szText, theXmlString.GetString(eText_Guild_DelMemberTile), CUI_ID_FRAME_MessageBox::eTypeYesNo, false,
		GuildDelMemberCallBack, &nId, sizeof(nId));

	return true;
}

//家族改名
bool CUI_ID_FRAME_Gang::ID_BUTTON_FamilyRenameOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	SetOtherRejectButtonMenu(eKey_ChangeFamilyName);
	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if(pGuild == NULL || pGuild->GetGuildID() == GuildDefine::InitID)
	{
		return false;
	}
	
	int nFamilyNum = pGuild->GetFamilyNumber();
	if (nFamilyNum <=0)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Info_GuildInfo, theXmlString.GetString(eText_GuildHaveNoFamily) );
		return false;
	}
	
	SetFamilyCtlGroup(nFamilyNum);
	m_ctlFmailyGroup.SetVisible(!m_ctlFmailyGroup.IsVisible());
	return true;
}

void CUI_ID_FRAME_Gang::SetFamilyCtlGroup(int nNum)
{
	if (nNum < 0 || nNum > m_vctFamilyAll.size())
	{
		return;
	}
	
	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if(pGuild == NULL || pGuild->GetGuildID() == GuildDefine::InitID)
	{
		return;
	}

	m_ctlFmailyGroup.Clear();
	m_ctlAnotherFmailyGroup.Clear();
	for (int i = 0; i < nNum; ++i)
	{
		if (m_vctFamilyAll[i])
		{
			m_vctFamilyAll[i]->SetCaption(pGuild->GetFamilyName(i + 1));
			m_ctlFmailyGroup.AddControl(m_vctFamilyAll[i]);
		}

		if (m_vctTransferBangzhongAll[i])
		{
			m_vctTransferBangzhongAll[i]->SetCaption(pGuild->GetFamilyName(i + 1));
			m_ctlAnotherFmailyGroup.AddControl(m_vctTransferBangzhongAll[i]);
		}
		
	}
}

inline void CUI_ID_FRAME_Gang::ShowSelectNothingMessage()
{
	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_SelectNothing));
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, szText );
}

inline void  CUI_ID_FRAME_Gang::ShowUnableTransferPositionWhenIsKingGuild()
{
	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_CanNotTransferPositionWhenIsKingGuild));
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, szText );
}

inline void CUI_ID_FRAME_Gang::ShowUnableTransferPosition()
{
	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_UnableTansferPositon));
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, szText );
}

//家族5
bool CUI_ID_FRAME_Gang::ID_BUTTON_Tong5OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	
	s_CUI_ID_FRAME_ADD_MEMBER.SetFrameType(CUI_ID_FRAME_ADD_MEMBER::eFrameType_ChangeFifthFamilyName);
	s_CUI_ID_FRAME_ADD_MEMBER.SetVisable(true);
	return true;
}

//家族4
bool CUI_ID_FRAME_Gang::ID_BUTTON_Tong4OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	s_CUI_ID_FRAME_ADD_MEMBER.SetFrameType(CUI_ID_FRAME_ADD_MEMBER::eFrameType_ChangeFourthFamilyName);
	s_CUI_ID_FRAME_ADD_MEMBER.SetVisable(true);
	return true;
}

//家族3
bool CUI_ID_FRAME_Gang::ID_BUTTON_Tong3OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;
	
	s_CUI_ID_FRAME_ADD_MEMBER.SetFrameType(CUI_ID_FRAME_ADD_MEMBER::eFrameType_ChangeThirdFamilyName);
	s_CUI_ID_FRAME_ADD_MEMBER.SetVisable(true);		return true;
}

//家族2
bool CUI_ID_FRAME_Gang::ID_BUTTON_Tong2OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	s_CUI_ID_FRAME_ADD_MEMBER.SetFrameType(CUI_ID_FRAME_ADD_MEMBER::eFrameType_ChangeSecFamilyName);
	s_CUI_ID_FRAME_ADD_MEMBER.SetVisable(true);	return true;
}

//家族1
bool CUI_ID_FRAME_Gang::ID_BUTTON_Tong1OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	s_CUI_ID_FRAME_ADD_MEMBER.SetFrameType(CUI_ID_FRAME_ADD_MEMBER::eFrameType_ChangeFirstFamilyName);
	s_CUI_ID_FRAME_ADD_MEMBER.SetVisable(true);	return true;
}

//转移帮众
bool CUI_ID_FRAME_Gang::ID_BUTTON_Tong25OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	if (!SetRemovedMember())
	{
		ShowSelectNothingMessage();
		return false;
	}

	MsgGuildMemberFamilyChangeReq msg;
	msg.nPlayerID = m_pMovedMember->GetID();
	msg.uchFamilyID = eKey_FifthFamily;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

//转移帮众
bool CUI_ID_FRAME_Gang::ID_BUTTON_Tong24OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	if (!SetRemovedMember())
	{
		ShowSelectNothingMessage();
		return false;
	}

	MsgGuildMemberFamilyChangeReq msg;
	msg.nPlayerID = m_pMovedMember->GetID();
	msg.uchFamilyID = eKey_FourthFamily;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

//转移帮众
bool CUI_ID_FRAME_Gang::ID_BUTTON_Tong23OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	if (!SetRemovedMember())
	{
		ShowSelectNothingMessage();
		return false;
	}

	MsgGuildMemberFamilyChangeReq msg;
	msg.nPlayerID = m_pMovedMember->GetID();
	msg.uchFamilyID = eKey_ThirdFamily;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

//转移帮众
bool CUI_ID_FRAME_Gang::ID_BUTTON_Tong22OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	if (!SetRemovedMember())
	{
		ShowSelectNothingMessage();
		return false;
	}

	MsgGuildMemberFamilyChangeReq msg;
	msg.nPlayerID = m_pMovedMember->GetID();
	msg.uchFamilyID = eKey_SecondFamily;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

//转移帮众
bool CUI_ID_FRAME_Gang::ID_BUTTON_Tong21OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	if (!SetRemovedMember())
	{
		ShowSelectNothingMessage();
		return false;
	}

	MsgGuildMemberFamilyChangeReq msg;
	msg.nPlayerID = m_pMovedMember->GetID();
	msg.uchFamilyID = eKey_FirstFamily;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

//改名
void CUI_ID_FRAME_Gang::ChangeFamilyName( const char* pName )
{
	if (pName && pName[0] != '\0')
	{
		CGangMgr* theGuild = thePlayerRole.GetGangMgr();
		if(theGuild == NULL)
		{
			return ;
		}

		GuildMember* member = theGuild->FindByDBId(g_nCharacterDBID);
		if (member)
		{
			MsgGuildFamilyChangeReq msgModifyTong;
			strcpy(msgModifyTong.szName, pName);
			msgModifyTong.uchFamilyID = member->GetFamilyID();
			GettheNetworkInput().SendMsg(&msgModifyTong);
		}
	}
}

//国家
void CUI_ID_FRAME_Gang::ID_CHECKBOX_CountryOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Gang )
		return;

	m_pID_CHECKBOX_Guild->SetCheck(false);
	m_ctlGuildGroup.SetVisible(false);
	//s_CUI_ID_FRAME_Country.SetVisable(true);
	s_CUI_ID_FRAME_BaseInfo.SetVisable(true);
}

// 帮会
void CUI_ID_FRAME_Gang::ID_CHECKBOX_GuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Gang )
		return;
	
	m_pID_CHECKBOX_Country->SetCheck(true);
	m_ctlGuildGroup.SetVisible(true);
	Refresh();
	//s_CUI_ID_FRAME_Country.SetVisable(false);
	s_CUI_ID_FRAME_BaseInfo.SetVisable(false);
}

//转移帮众
bool CUI_ID_FRAME_Gang::ID_BUTTON_FamilyChangeOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;


	SetOtherRejectButtonMenu(eKey_MoveMember);
	
	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if(pGuild == NULL || pGuild->GetGuildID() == GuildDefine::InitID)
	{
		return false;
	}
	
	int nFamilyNum = pGuild->GetFamilyNumber();
	SetFamilyCtlGroup(nFamilyNum);
	m_ctlAnotherFmailyGroup.SetVisible(!m_ctlAnotherFmailyGroup.IsVisible());
	return true;
}

bool CUI_ID_FRAME_Gang::SetRemovedMember()
{
	if (!m_pID_FRAME_Gang || !m_pID_LIST_MEMBER)
	{
		return false;
	}
	
	int nIndex = m_pID_LIST_MEMBER->GetCurSelIndex();
	if (nIndex == -1 || nIndex >= m_vctAllMember.size())
	{
		return false;
	}

	m_pMovedMember = m_vctAllMember[nIndex];
	return true;
}

//官员任免
bool CUI_ID_FRAME_Gang::ID_BUTTON_AppointOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	m_ctlAppointGroup.SetVisible(!m_ctlAppointGroup.IsVisible());
	
	SetOtherRejectButtonMenu(eKey_Appoint);
	return true;
}

void CUI_ID_FRAME_Gang::ResetMember()
{
	m_pMaster = NULL;
	m_pViceMaster = NULL;
	m_vctFamilyMaster.clear();
	m_vctFirstFamilyMember.clear();
	m_vctOtherMember.clear();
	m_vctOnLineMember.clear();
	m_vctOffLineMember.clear();
}

//inline void CUI_ID_FRAME_Gang::SetBoolState()
//{
//	m_bShowAppointButton = true;
//}

void CUI_ID_FRAME_Gang::ID_List_OnRBClick(ControlObject* pSender, ControlList::S_List* pItem)
{
	if(pItem)
	{
		GuildMember* pSelMember = s_CUI_ID_FRAME_Gang.GetCurSelMember();
		s_CUI_ID_FRAME_RBTNMENU.SetPrivateName(pSelMember->GetName());
		s_CUI_ID_FRAME_RBTNMENU.SetShowType(CUI_ID_FRAME_RBTNMENU::eShow_Gang);
		s_CUI_ID_FRAME_RBTNMENU.SetVisable(true);
		s_CUI_ID_FRAME_RBTNMENU.SetPos(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y);
		if (s_CUI_ID_FRAME_RBTNMENU.GetFrame())
			theUiManager.ToTop(s_CUI_ID_FRAME_RBTNMENU.GetFrame());
	}
}

GuildMember* CUI_ID_FRAME_Gang::GetCurSelMember()
{
	if (!m_pID_LIST_MEMBER)
	{
		return NULL;
	}
	int nIndex = m_pID_LIST_MEMBER->GetCurSelIndex();
	if (nIndex < 0 || nIndex > m_nAllMemberNum)
	{
		return NULL;
	}
	
	return m_vctAllMember[nIndex];
}

void CUI_ID_FRAME_Gang::ID_List_OnLBClick(ControlObject* pSender, ControlList::S_List* pItem)
{
	s_CUI_ID_FRAME_RBTNMENU.SetVisable(false);
}

const char* CUI_ID_FRAME_Gang::GetProfessionByID(int nProfessionID) const 
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

const char* CUI_ID_FRAME_Gang::GetPositionByID(int nPosition) const 
{
	switch (nPosition)
	{
	case GuildDefine::Position_Member:
		return theXmlString.GetString(eText_Guild_Bangzhong);
	case GuildDefine::Position_FamilyMaster:
		return theXmlString.GetString(eText_Guild_Tangzhu);
	case GuildDefine::Position_ViceMaster:
		return theXmlString.GetString(eText_Guild_ViceMaster);
	case GuildDefine::Position_Master:
		return theXmlString.GetString(eText_Guild_Master);
	default:
		return "";
	}
}

const char* CUI_ID_FRAME_Gang::GetFamilyName(int nFaimilyId) 
{
	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if(pGuild == NULL || pGuild->GetGuildID() == GuildDefine::InitID)
	{
		return "";
	}

	return pGuild->GetFamilyName(nFaimilyId);
}

void CUI_ID_FRAME_Gang::SetOtherRejectButtonMenu(eKey_RejectMenu key)
{
	switch (key)
	{
	case eKey_ChangeFamilyName:
		{
			m_ctlAppointGroup.SetVisible(false);
			m_ctlAnotherFmailyGroup.SetVisible(false);
		}
		break;
	case eKey_MoveMember:
		{
			m_ctlAppointGroup.SetVisible(false);
			m_ctlFmailyGroup.SetVisible(false);
		}
		break;
	case eKey_Appoint:
		{
			m_ctlFmailyGroup.SetVisible(false);
			m_ctlAnotherFmailyGroup.SetVisible(false);
		}
		break;
	default:
		break;
	}
}

void CUI_ID_FRAME_Gang::InitAllSortFunc()
{
	m_funcSort[ekey_name] = SortByName;
	m_funcSort[ekey_level] = SortByLevel;
	m_funcSort[ekey_profession] = SortByProfession;
	m_funcSort[ekey_position] = SortByPosition;
	m_funcSort[ekey_family] = SortByFamily;
	m_funcSort[ekey_active] = SortByActive;
	m_funcSort[ekey_offer] = SortByOffer;

	m_funcSortReverse[ekey_name] = SortByName_Reverse;
	m_funcSortReverse[ekey_level] = SortByLevel_Reverse;
	m_funcSortReverse[ekey_profession] = SortByProfession_Reverse;
	m_funcSortReverse[ekey_position] = SortByPosition_Reverse;
	m_funcSortReverse[ekey_family] = SortByFamily_Reverse;
	m_funcSortReverse[ekey_active] = SortByActive_Reverse;
	m_funcSortReverse[ekey_offer] = SortByOffer_Reverse;
}

bool CUI_ID_FRAME_Gang::SortByName(GuildMember* lhs, GuildMember* rhs)
{
	  return strlen(lhs->GetName()) < strlen(rhs->GetName());
}

bool CUI_ID_FRAME_Gang::SortByLevel(GuildMember* lhs, GuildMember* rhs)
{
	return lhs->GetLevel() < rhs->GetLevel();
}

bool CUI_ID_FRAME_Gang::SortByProfession( GuildMember* lhs, GuildMember* rhs )
{
	return lhs->GetProfession() < rhs->GetProfession();
}

bool CUI_ID_FRAME_Gang::SortByPosition( GuildMember* lhs, GuildMember* rhs )
{
	return lhs->GetPosition() < rhs->GetPosition();
}

bool CUI_ID_FRAME_Gang::SortByFamily( GuildMember* lhs, GuildMember* rhs )
{
	return lhs->GetFamilyID() < rhs->GetFamilyID();
}

bool CUI_ID_FRAME_Gang::SortByActive( GuildMember* lhs, GuildMember* rhs )
{
	return lhs->GetActivity() < rhs->GetActivity();
}

bool CUI_ID_FRAME_Gang::SortByOffer( GuildMember* lhs, GuildMember* rhs )
{
	return lhs->GetOffer() < rhs->GetOffer();
}

//reverse
bool CUI_ID_FRAME_Gang::SortByName_Reverse(GuildMember* lhs, GuildMember* rhs)
{
	return strlen(lhs->GetName()) > strlen(rhs->GetName());
}

bool CUI_ID_FRAME_Gang::SortByLevel_Reverse(GuildMember* lhs, GuildMember* rhs)
{
	return lhs->GetLevel() > rhs->GetLevel();
}

bool CUI_ID_FRAME_Gang::SortByProfession_Reverse( GuildMember* lhs, GuildMember* rhs )
{
	return lhs->GetProfession() > rhs->GetProfession();
}

bool CUI_ID_FRAME_Gang::SortByPosition_Reverse( GuildMember* lhs, GuildMember* rhs )
{
	return lhs->GetPosition() > rhs->GetPosition();
}

bool CUI_ID_FRAME_Gang::SortByFamily_Reverse( GuildMember* lhs, GuildMember* rhs )
{
	return lhs->GetFamilyID() > rhs->GetFamilyID();
}

bool CUI_ID_FRAME_Gang::SortByActive_Reverse( GuildMember* lhs, GuildMember* rhs )
{
	return lhs->GetActivity() > rhs->GetActivity();
}

bool CUI_ID_FRAME_Gang::SortByOffer_Reverse( GuildMember* lhs, GuildMember* rhs )
{
	return lhs->GetOffer() > rhs->GetOffer();
}

void CUI_ID_FRAME_Gang::ShowSortArrow()
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

void CUI_ID_FRAME_Gang::ResetSortMember()
{
	for (int i = 0; i < ekey_max; ++i)
	{
		m_bArrow[i] = false;
		
	}
	m_key = ekey_name;
	m_bArrow[m_key] = true;
	m_currentSortFunc = m_funcSort[m_key];
}

void CUI_ID_FRAME_Gang::InitArrowArray()
{
	m_pID_TEXT_Arrow[ekey_name] = m_pID_TEXT_ArrowTeamName;
	m_pID_TEXT_Arrow[ekey_level] = m_pID_TEXT_ArrowLvl;
	m_pID_TEXT_Arrow[ekey_profession] = m_pID_TEXT_ArrowJob;
	m_pID_TEXT_Arrow[ekey_position] = m_pID_TEXT_ArrowWork;
	m_pID_TEXT_Arrow[ekey_family] = m_pID_TEXT_ArrowTong;
	m_pID_TEXT_Arrow[ekey_active] = m_pID_TEXT_ArrowActivity;
	m_pID_TEXT_Arrow[ekey_offer] = m_pID_TEXT_ArrowGongXian;
}

void CUI_ID_FRAME_Gang::SetSortFunc(SortType ekey)
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
	Refresh();
}

void CUI_ID_FRAME_Gang::SortAndRefresh()
{
	if (!m_currentSortFunc)
	{
		return;
	}
	StoreSortedData();
	std::stable_sort(m_vctOnLineMember.begin(), m_vctOnLineMember.end(), m_currentSortFunc);
	std::stable_sort(m_vctOffLineMember.begin(), m_vctOffLineMember.end(), m_currentSortFunc);

	//StoreSortedData();
}

void CUI_ID_FRAME_Gang::StoreSortedData()
{
	if (m_pMaster)
	{
		if (m_pMaster->GetOnLine())
		{
			m_vctOnLineMember.push_back(m_pMaster);
		}
		else
		{
			m_vctOffLineMember.push_back(m_pMaster);
		}
	}

	if (m_pViceMaster)
	{
		if (m_pViceMaster->GetOnLine())
		{
			m_vctOnLineMember.push_back(m_pViceMaster);
		}
		else
		{
			m_vctOffLineMember.push_back(m_pViceMaster);
		}
	}

	for (std::vector<GuildMember*>::iterator iter = m_vctFamilyMaster.begin(); iter != m_vctFamilyMaster.end(); ++iter)
	{
		if ((*iter)->GetOnLine())
		{
			m_vctOnLineMember.push_back(*iter);
		}
		else
		{
			m_vctOffLineMember.push_back(*iter);
		}
	}

	for (std::vector<GuildMember*>::iterator iter = m_vctFirstFamilyMember.begin(); iter != m_vctFirstFamilyMember.end(); ++iter)
	{
		if ((*iter)->GetOnLine())
		{
			m_vctOnLineMember.push_back(*iter);
		}
		else
		{
			m_vctOffLineMember.push_back(*iter);
		}
	}

	for (std::vector<GuildMember*>::iterator iter = m_vctOtherMember.begin(); iter != m_vctOtherMember.end(); ++iter)
	{
		if ((*iter)->GetOnLine())
		{
			m_vctOnLineMember.push_back(*iter);
		}
		else
		{
			m_vctOffLineMember.push_back(*iter);
		}
	}
}

// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_TeamNameOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	SetSortFunc(ekey_name);
	return true;
}

// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_LvlOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	SetSortFunc(ekey_level);
	return true;
}

// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_JobOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	SetSortFunc(ekey_profession);
	return true;
}
// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_WorkOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	SetSortFunc(ekey_position);
	return true;
}
// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_TongOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	SetSortFunc(ekey_family);
	return true;
}
// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_ActivityOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	SetSortFunc(ekey_active);
	return true;
}
// Button
bool CUI_ID_FRAME_Gang::ID_BUTTON_GongXianOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gang )
		return false;

	SetSortFunc(ekey_offer);
	return true;
}

bool CUI_ID_FRAME_Gang::GuildDonateProcess(DWORD dwMoney, void* pData)
{
	MsgGuildDonateAck msg;
	msg.nMoney = dwMoney;
	if (msg.nMoney > thePlayerRole.GetData(CPlayerRole::TYPE_MONEY))
	{
		ShowNotEnoughMoney();
		return false;
	}

	GettheNetworkInput().SendMsg( &msg );
	return true;
}

void CUI_ID_FRAME_Gang::ShowNotEnoughMoney()
{
	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_GuildDenoteMoneyNotEnough));
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, szText );
}