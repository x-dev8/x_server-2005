/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildMember.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GuildMember.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "../color_config.h"
#include "core/Name.h"
#include "PlayerRole.h"
#include "..\PlayerMgr.h"
#include "GuildMessage.h"
#include "NetworkInput.h"
#include "GameDefineChar.h"
#include "GuildBaseInfo.h"
#include "ScreenInfoManager.h"
#include "Common.h"
#include "GameMain.h"
#include "Player.h"
#include "AddMember.h"
#include "RbtnMenu.h"
extern int g_nCharacterDBID;
extern GAME_STATE	g_GameState;

CUI_ID_FRAME_GuildMember s_CUI_ID_FRAME_GuildMember;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GuildMember, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GuildMember, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_BUTTON_AppointOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_BUTTON_QuitOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_BUTTON_DelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_BUTTON_ZhuanRangOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_BUTTON_ADDOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_BUTTON_LeavePositionOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_CHECKBOX_ShowLeaveOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_BUTTON_TeamNameOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_BUTTON_WorkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_BUTTON_LvlOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_BUTTON_GongXianOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_BUTTON_ActivityOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_BUTTON_TongOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_BUTTON_JobOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_BUTTON_DeposeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_BUTTON_AppointAssistantOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_LIST_TeamNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_LIST_GongXianOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_LIST_ActivityOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_LIST_TongOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_LIST_WorkOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_LIST_JobOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_LIST_LvlOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_LIST_MEMBEROnListSelectChange )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_BUTTON_OnlineTimeOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildMember, ID_LIST_OnlineTimeOnListSelectChange )
CUI_ID_FRAME_GuildMember::CUI_ID_FRAME_GuildMember()
{
	// Member
	m_pID_FRAME_GuildMember = NULL;
	m_pID_BUTTON_Appoint = NULL;
	m_pID_BUTTON_Quit = NULL;
	m_pID_BUTTON_Del = NULL;
	m_pID_BUTTON_ZhuanRang = NULL;
	m_pID_BUTTON_ADD = NULL;
	m_pID_BUTTON_LeavePosition = NULL;
	m_pID_CHECKBOX_ShowLeave = NULL;
	m_pID_BUTTON_TeamName = NULL;
	m_pID_BUTTON_Work = NULL;
	m_pID_BUTTON_Lvl = NULL;
	m_pID_BUTTON_GongXian = NULL;
	m_pID_BUTTON_Activity = NULL;
	m_pID_BUTTON_Tong = NULL;
	m_pID_BUTTON_Job = NULL;
	m_pID_TEXT_ArrowJob = NULL;
	m_pID_TEXT_ArrowActivity = NULL;
	m_pID_TEXT_ArrowTong = NULL;
	m_pID_TEXT_ArrowWork = NULL;
	m_pID_TEXT_ArrowLvl = NULL;
	m_pID_TEXT_ArrowTeamName = NULL;
	m_pID_TEXT_ArrowGongXian = NULL;
	m_pID_LIST_TeamName = NULL;
	m_pID_LIST_GongXian = NULL;
	m_pID_LIST_Activity = NULL;
	m_pID_LIST_Tong = NULL;
	m_pID_LIST_Work = NULL;
	m_pID_LIST_Job = NULL;
	m_pID_LIST_Lvl = NULL;
	m_pID_LIST_MEMBER = NULL;

	m_pID_BUTTON_Depose = NULL;
	m_pID_BUTTON_AppointAssistant = NULL;

	m_pID_LIST_OnlineTime = NULL;
	m_pID_BUTTON_OnlineTime = NULL;
	m_pID_TEXT_OnlineTime = NULL;


	m_IsShowNonOnLinePlayer = true;
	m_IsNeedUpdate = true;

	InitAllSortFunc();
	ResetSortMember();
}
// Frame
bool CUI_ID_FRAME_GuildMember::OnFrameRun()
{
	OnUpdateListShowHeight();
	return true;
}
bool CUI_ID_FRAME_GuildMember::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_GuildMember::ID_BUTTON_AppointOnButtonClick( ControlObject* pSender )
{
	//功能上的操作的时候		
	//会弹出2个按钮来
	if ( !m_pID_FRAME_GuildMember )
		return false;
	m_pID_BUTTON_Depose->SetVisable(!m_pID_BUTTON_Depose->IsVisable());
	m_pID_BUTTON_AppointAssistant->SetVisable(!m_pID_BUTTON_AppointAssistant->IsVisable());
	return true;
}
void CUI_ID_FRAME_GuildMember::ClearButtonAppoint()
{
	m_pID_BUTTON_Depose->SetVisable(false);
	m_pID_BUTTON_AppointAssistant->SetVisable(false);
}
bool CUI_ID_FRAME_GuildMember::ID_BUTTON_DeposeOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildMember )
		return false;

	ClearButtonAppoint();

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
bool CUI_ID_FRAME_GuildMember::ID_BUTTON_AppointAssistantOnButtonClick( ControlObject* pSender ) //任命副帮主
{
	if ( !m_pID_FRAME_GuildMember )
		return false;
	ClearButtonAppoint();

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
// Button
bool CUI_ID_FRAME_GuildMember::ID_BUTTON_QuitOnButtonClick( ControlObject* pSender ) //离开公会
{
	if ( !m_pID_FRAME_GuildMember )
		return false;
	ClearButtonAppoint();
	s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eTextGuild_Leave_Check),"",CUI_ID_FRAME_MessageBox::eTypeYesNo,false,LeaveGuild);
	return true;
}
bool CUI_ID_FRAME_GuildMember::LeaveGuild(char m_ok,void *data)
{
	if (m_ok)
	{
		MsgLeaveGuildReq msg;
		GettheNetworkInput().SendMsg(&msg);

		s_CUI_ID_FRAME_GuildBaseInfo.SetVisable(false);

		// 自己离开公会, 在右下角提示
		char szInfo[MAX_PATH] = {0};
		MeSprintf( szInfo, MAX_PATH - 1, theXmlString.GetString(eText_SelfQuitGuildTip) );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Server_Others_Success, szInfo );
	}
	return true;
}
// Button
bool CUI_ID_FRAME_GuildMember::ID_BUTTON_DelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildMember )
		return false;

	ClearButtonAppoint();

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
bool CUI_ID_FRAME_GuildMember::GuildDelMemberCallBack(const char bPressYesButton, void *pData)
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
bool CUI_ID_FRAME_GuildMember::IsOperateOnMyself(int nId)
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
inline void CUI_ID_FRAME_GuildMember::ShowSelectNothingMessage()
{
	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_SelectNothing));
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, szText );
}
// Button
bool CUI_ID_FRAME_GuildMember::ID_BUTTON_ZhuanRangOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildMember )
		return false;

	ClearButtonAppoint();

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
	ShowTransferPositionInfo();
	char temp[64];
	MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eTextGang_ZhuanRang),m_pAcceptPositionMember->GetName());
	s_CUI_ID_FRAME_MessageBox.Show(temp,"",CUI_ID_FRAME_MessageBox::eTypeYesNo,false,ZhuanRang,(void*)m_pAcceptPositionMember,sizeof(GuildMember));
	return true;
}
bool CUI_ID_FRAME_GuildMember::ZhuanRang(char m_ok,void *data)
{
	if (m_ok&& static_cast<GuildMember* >(data) != NULL)
	{
		MsgGuildTransferPositionReq msg;
		msg.nPlayerID = static_cast<GuildMember* >(data)->GetID();
		GettheNetworkInput().SendMsg(&msg);
	}
	return true;
}
void CUI_ID_FRAME_GuildMember::ShowTransferPositionInfo()
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
}
inline void  CUI_ID_FRAME_GuildMember::ShowUnableTransferPositionWhenIsKingGuild()
{
	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_CanNotTransferPositionWhenIsKingGuild));
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, szText );
}
inline void CUI_ID_FRAME_GuildMember::ShowUnableTransferPosition()
{
	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_UnableTansferPositon));
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, szText );
}
bool CUI_ID_FRAME_GuildMember::CheckCanTransferPosition() const
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
// Button
bool CUI_ID_FRAME_GuildMember::ID_BUTTON_ADDOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildMember )
		return false;
	ClearButtonAppoint();
	s_CUI_ID_FRAME_ADD_MEMBER.SetFrameType(CUI_ID_FRAME_ADD_MEMBER::eFrameType_AddMember);
	s_CUI_ID_FRAME_ADD_MEMBER.SetVisable(true);
	return true;
}
// Button
bool CUI_ID_FRAME_GuildMember::ID_BUTTON_LeavePositionOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildMember )
		return false;
	ClearButtonAppoint();
	MsgGuildResignPositionReq msg;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}
// CheckBox
void CUI_ID_FRAME_GuildMember::ID_CHECKBOX_ShowLeaveOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_IsShowNonOnLinePlayer = m_pID_CHECKBOX_ShowLeave->IsChecked();
	SetGuildMemberInfo();
}
// Button
bool CUI_ID_FRAME_GuildMember::ID_BUTTON_TeamNameOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildMember )
		return false;

	SetSortFunc(ekey_name);
	return true;
}
// Button
bool CUI_ID_FRAME_GuildMember::ID_BUTTON_WorkOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildMember )
		return false;

	SetSortFunc(ekey_position);
	return true;
}
// Button
bool CUI_ID_FRAME_GuildMember::ID_BUTTON_LvlOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildMember )
		return false;

	SetSortFunc(ekey_level);
	return true;
}
// Button
bool CUI_ID_FRAME_GuildMember::ID_BUTTON_GongXianOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildMember )
		return false;

	SetSortFunc(ekey_offer);
	return true;
}
// Button
bool CUI_ID_FRAME_GuildMember::ID_BUTTON_ActivityOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildMember )
		return false;

	SetSortFunc(ekey_active);
	return true;
}
// Button
bool CUI_ID_FRAME_GuildMember::ID_BUTTON_TongOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_GuildMember::ID_BUTTON_JobOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildMember )
		return false;

	SetSortFunc(ekey_profession);
	return true;
}
bool CUI_ID_FRAME_GuildMember::ID_BUTTON_OnlineTimeOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildMember )
		return false;

	SetSortFunc(eKey_OnLineTime);
	return true;
}
// List
void CUI_ID_FRAME_GuildMember::ID_LIST_TeamNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_GuildMember::ID_LIST_GongXianOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_GuildMember::ID_LIST_ActivityOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_GuildMember::ID_LIST_TongOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_GuildMember::ID_LIST_WorkOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_GuildMember::ID_LIST_JobOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_GuildMember::ID_LIST_LvlOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_GuildMember::ID_LIST_MEMBEROnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
void CUI_ID_FRAME_GuildMember::ID_LIST_OnlineTimeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
	// 装载UI
bool CUI_ID_FRAME_GuildMember::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GuildMember.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GuildMember.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GuildMember::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GuildMember, s_CUI_ID_FRAME_GuildMemberOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GuildMember, s_CUI_ID_FRAME_GuildMemberOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GuildMember, ID_BUTTON_Appoint, s_CUI_ID_FRAME_GuildMemberID_BUTTON_AppointOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildMember, ID_BUTTON_Quit, s_CUI_ID_FRAME_GuildMemberID_BUTTON_QuitOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildMember, ID_BUTTON_Del, s_CUI_ID_FRAME_GuildMemberID_BUTTON_DelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildMember, ID_BUTTON_ZhuanRang, s_CUI_ID_FRAME_GuildMemberID_BUTTON_ZhuanRangOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildMember, ID_BUTTON_ADD, s_CUI_ID_FRAME_GuildMemberID_BUTTON_ADDOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildMember, ID_BUTTON_LeavePosition, s_CUI_ID_FRAME_GuildMemberID_BUTTON_LeavePositionOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GuildMember, ID_CHECKBOX_ShowLeave, s_CUI_ID_FRAME_GuildMemberID_CHECKBOX_ShowLeaveOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_GuildMember, ID_BUTTON_TeamName, s_CUI_ID_FRAME_GuildMemberID_BUTTON_TeamNameOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildMember, ID_BUTTON_Work, s_CUI_ID_FRAME_GuildMemberID_BUTTON_WorkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildMember, ID_BUTTON_Lvl, s_CUI_ID_FRAME_GuildMemberID_BUTTON_LvlOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildMember, ID_BUTTON_GongXian, s_CUI_ID_FRAME_GuildMemberID_BUTTON_GongXianOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildMember, ID_BUTTON_Activity, s_CUI_ID_FRAME_GuildMemberID_BUTTON_ActivityOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildMember, ID_BUTTON_Tong, s_CUI_ID_FRAME_GuildMemberID_BUTTON_TongOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildMember, ID_BUTTON_Job, s_CUI_ID_FRAME_GuildMemberID_BUTTON_JobOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildMember, ID_BUTTON_OnlineTime, s_CUI_ID_FRAME_GuildMemberID_BUTTON_OnlineTimeOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_GuildMember, ID_LIST_TeamName, s_CUI_ID_FRAME_GuildMemberID_LIST_TeamNameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildMember, ID_LIST_GongXian, s_CUI_ID_FRAME_GuildMemberID_LIST_GongXianOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildMember, ID_LIST_Activity, s_CUI_ID_FRAME_GuildMemberID_LIST_ActivityOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildMember, ID_LIST_Tong, s_CUI_ID_FRAME_GuildMemberID_LIST_TongOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildMember, ID_LIST_Work, s_CUI_ID_FRAME_GuildMemberID_LIST_WorkOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildMember, ID_LIST_Job, s_CUI_ID_FRAME_GuildMemberID_LIST_JobOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildMember, ID_LIST_Lvl, s_CUI_ID_FRAME_GuildMemberID_LIST_LvlOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildMember, ID_LIST_MEMBER, s_CUI_ID_FRAME_GuildMemberID_LIST_MEMBEROnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildMember, ID_LIST_OnlineTime, s_CUI_ID_FRAME_GuildMemberID_LIST_OnlineTimeOnListSelectChange);

	theUiManager.OnButtonClick( ID_FRAME_GuildMember, ID_BUTTON_Depose, s_CUI_ID_FRAME_GuildMemberID_BUTTON_DeposeOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildMember, ID_BUTTON_AppointAssistant, s_CUI_ID_FRAME_GuildMemberID_BUTTON_AppointAssistantOnButtonClick );


	m_pID_FRAME_GuildMember = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GuildMember );
	m_pID_BUTTON_Appoint = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_BUTTON_Appoint );
	m_pID_BUTTON_Quit = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_BUTTON_Quit );
	m_pID_BUTTON_Del = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_BUTTON_Del );
	m_pID_BUTTON_ZhuanRang = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_BUTTON_ZhuanRang );
	m_pID_BUTTON_ADD = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_BUTTON_ADD );
	m_pID_BUTTON_LeavePosition = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_BUTTON_LeavePosition );
	m_pID_CHECKBOX_ShowLeave = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_CHECKBOX_ShowLeave );
	m_pID_BUTTON_TeamName = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_BUTTON_TeamName );
	m_pID_BUTTON_Work = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_BUTTON_Work );
	m_pID_BUTTON_Lvl = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_BUTTON_Lvl );
	m_pID_BUTTON_GongXian = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_BUTTON_GongXian );
	m_pID_BUTTON_Activity = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_BUTTON_Activity );
	m_pID_BUTTON_Tong = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_BUTTON_Tong );
	m_pID_BUTTON_Job = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_BUTTON_Job );
	m_pID_TEXT_ArrowJob = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_TEXT_ArrowJob );
	m_pID_TEXT_ArrowActivity = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_TEXT_ArrowActivity );
	m_pID_TEXT_ArrowTong = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_TEXT_ArrowTong );
	m_pID_TEXT_ArrowWork = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_TEXT_ArrowWork );
	m_pID_TEXT_ArrowLvl = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_TEXT_ArrowLvl );
	m_pID_TEXT_ArrowTeamName = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_TEXT_ArrowTeamName );
	m_pID_TEXT_ArrowGongXian = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_TEXT_ArrowGongXian );
	m_pID_LIST_TeamName = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_LIST_TeamName );
	m_pID_LIST_GongXian = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_LIST_GongXian );
	m_pID_LIST_Activity = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_LIST_Activity );
	m_pID_LIST_Tong = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_LIST_Tong );
	m_pID_LIST_Work = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_LIST_Work );
	m_pID_LIST_Job = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_LIST_Job );
	m_pID_LIST_Lvl = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_LIST_Lvl );
	m_pID_LIST_MEMBER = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_LIST_MEMBER );

	m_pID_BUTTON_Depose = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_BUTTON_Depose );
	m_pID_BUTTON_Depose->SetVisable(false);
	m_pID_BUTTON_AppointAssistant = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_BUTTON_AppointAssistant );
	m_pID_BUTTON_AppointAssistant->SetVisable(false);

	m_pID_LIST_OnlineTime = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_LIST_OnlineTime );
	m_pID_TEXT_OnlineTime = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_TEXT_OnlineTime );
	m_pID_BUTTON_OnlineTime = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildMember, ID_BUTTON_OnlineTime );
	assert( m_pID_FRAME_GuildMember );
	assert( m_pID_BUTTON_Appoint );
	assert( m_pID_BUTTON_Quit );
	assert( m_pID_BUTTON_Del );
	assert( m_pID_BUTTON_ZhuanRang );
	assert( m_pID_BUTTON_ADD );
	assert( m_pID_BUTTON_LeavePosition );
	assert( m_pID_CHECKBOX_ShowLeave );
	assert( m_pID_BUTTON_TeamName );
	assert( m_pID_BUTTON_Work );
	assert( m_pID_BUTTON_Lvl );
	assert( m_pID_BUTTON_GongXian );
	assert( m_pID_BUTTON_Activity );
	assert( m_pID_BUTTON_Tong );
	assert( m_pID_BUTTON_Job );
	assert( m_pID_TEXT_ArrowJob );
	assert( m_pID_TEXT_ArrowActivity );
	assert( m_pID_TEXT_ArrowTong );
	assert( m_pID_TEXT_ArrowWork );
	assert( m_pID_TEXT_ArrowLvl );
	assert( m_pID_TEXT_ArrowTeamName );
	assert( m_pID_TEXT_ArrowGongXian );
	assert( m_pID_LIST_TeamName );
	assert( m_pID_LIST_GongXian );
	assert( m_pID_LIST_Activity );
	assert( m_pID_LIST_Tong );
	assert( m_pID_LIST_Work );
	assert( m_pID_LIST_Job );
	assert( m_pID_LIST_Lvl );
	assert( m_pID_LIST_MEMBER );
	assert( m_pID_BUTTON_Depose );
	assert( m_pID_BUTTON_AppointAssistant );
	assert( m_pID_LIST_OnlineTime );
	assert( m_pID_TEXT_OnlineTime );
	assert( m_pID_BUTTON_OnlineTime );


	InitArrowArray();
	SetSkipAllMsg();

	m_pID_LIST_MEMBER->SetRBClickFun(ID_List_OnRBClick);

	m_pID_FRAME_GuildMember->SetFather(s_CUI_ID_FRAME_GuildBaseInfo.GetFrame());
	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GuildMember::_UnLoadUI()
{
	m_pID_FRAME_GuildMember = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GuildMember.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GuildMember::_IsVisable()
{
	return m_pID_FRAME_GuildMember->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GuildMember::_SetVisable( const bool bVisable )
{
	if(bVisable)
		OnShow();
	m_pID_FRAME_GuildMember->SetVisable( bVisable );
	ClearButtonAppoint();
}
void CUI_ID_FRAME_GuildMember::OnShow()
{
	//让Ui显示
	if(m_IsNeedUpdate)
	{	
		//表示数据需要更新

		//1.辞去职务
		m_pID_BUTTON_LeavePosition->SetEnable(s_CUI_ID_FRAME_GuildBaseInfo.IsCanDoByRight(GuildDefine::Right_Resign));
		//2.转让职务
		m_pID_BUTTON_ZhuanRang->SetEnable(s_CUI_ID_FRAME_GuildBaseInfo.IsCanDoByRight(GuildDefine::Right_Transfer));
		//3.职务任免
		m_pID_BUTTON_Appoint->SetEnable(s_CUI_ID_FRAME_GuildBaseInfo.IsCanDoByRight(GuildDefine::Right_Assign));
		//4.军团邀请
		m_pID_BUTTON_ADD->SetEnable(s_CUI_ID_FRAME_GuildBaseInfo.IsCanDoByRight(GuildDefine::Right_Invite));
		//5.军团开除
		m_pID_BUTTON_Del->SetEnable(s_CUI_ID_FRAME_GuildBaseInfo.IsCanDoByRight(GuildDefine::Right_Kick));
		//6.离开军团
		m_pID_BUTTON_Quit->SetEnable(s_CUI_ID_FRAME_GuildBaseInfo.IsCanDoByRight(GuildDefine::Right_Leave));
		//7.是否显示离线玩家
		m_pID_CHECKBOX_ShowLeave->SetCheck(m_IsShowNonOnLinePlayer);
		//8.设置公会玩家列表框
		SetGuildMemberInfo();

		m_IsNeedUpdate = false;
	}
}
void CUI_ID_FRAME_GuildMember::OnUpdateUiInfo()
{
	m_IsNeedUpdate = true;
	if(!IsVisable())
		return;
	else
	{
		//更新Ui上的全部值
		OnShow();
	}
}
void CUI_ID_FRAME_GuildMember::InitArrowArray()
{
	m_pID_TEXT_Arrow[ekey_name] = m_pID_TEXT_ArrowTeamName;
	m_pID_TEXT_Arrow[ekey_level] = m_pID_TEXT_ArrowLvl;
	m_pID_TEXT_Arrow[ekey_profession] = m_pID_TEXT_ArrowJob;
	m_pID_TEXT_Arrow[ekey_position] = m_pID_TEXT_ArrowWork;
	m_pID_TEXT_Arrow[ekey_active] = m_pID_TEXT_ArrowActivity;
	m_pID_TEXT_Arrow[ekey_offer] = m_pID_TEXT_ArrowGongXian;
	m_pID_TEXT_Arrow[eKey_OnLineTime] = m_pID_TEXT_OnlineTime;
}
void CUI_ID_FRAME_GuildMember::SetSkipAllMsg()
{
	if (_IsVisable())
	{
		m_pID_LIST_TeamName->SetSkipAllMsg(true);
		m_pID_LIST_Lvl->SetSkipAllMsg(true);
		m_pID_LIST_Job->SetSkipAllMsg(true);
		m_pID_LIST_Work->SetSkipAllMsg(true);
		m_pID_LIST_Activity->SetSkipAllMsg(true);
		m_pID_LIST_GongXian->SetSkipAllMsg(true);
		m_pID_LIST_OnlineTime->SetSkipAllMsg(true);
	}
}
void CUI_ID_FRAME_GuildMember::ResetSortMember()
{
	for (int i = 0; i < ekey_max; ++i)
	{
		m_bArrow[i] = false;
		
	}
	m_key = ekey_name;
	m_bArrow[m_key] = true;
	m_currentSortFunc = m_funcSort[m_key];
}
void CUI_ID_FRAME_GuildMember::InitAllSortFunc()
{
	m_funcSort[ekey_name] = SortByName;
	m_funcSort[ekey_level] = SortByLevel;
	m_funcSort[ekey_profession] = SortByProfession;
	m_funcSort[ekey_position] = SortByPosition;
	m_funcSort[ekey_active] = SortByActive;
	m_funcSort[ekey_offer] = SortByOffer;
	m_funcSort[eKey_OnLineTime] = SortByOnlineTime;

	m_funcSortReverse[ekey_name] = SortByName_Reverse;
	m_funcSortReverse[ekey_level] = SortByLevel_Reverse;
	m_funcSortReverse[ekey_profession] = SortByProfession_Reverse;
	m_funcSortReverse[ekey_position] = SortByPosition_Reverse;
	m_funcSortReverse[ekey_active] = SortByActive_Reverse;
	m_funcSortReverse[ekey_offer] = SortByOffer_Reverse;
	m_funcSortReverse[eKey_OnLineTime] = SortByOnlineTime_Reverse;
}
void CUI_ID_FRAME_GuildMember::SetGuildMemberInfo()
{
	//将公会玩家的信息设置到UI上面去 包括排序
	ShowSortArrow();//设置text的状态
	SortAndRefresh();//列表排序
	SetAllList();//加载到List上去
}
void CUI_ID_FRAME_GuildMember::ShowSortArrow()
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
void CUI_ID_FRAME_GuildMember::SetAllList()
{
	ClearAllList();
	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if(pGuild == NULL || pGuild->GetGuildID() == GuildDefine::InitID)
		return;
	m_vctAllMember.clear();
	ShowOnlineMember();
	if (m_IsShowNonOnLinePlayer)
		ShowNonOnlineMember();
}
void CUI_ID_FRAME_GuildMember::ShowOnlineMember()
{
	//将在线玩家的数据加入到List
	vector<GuildMember*>& vecOnLine = s_CUI_ID_FRAME_GuildBaseInfo.GetGuildOnLineMember();
	if(vecOnLine.empty()) return;
	vector<GuildMember*>::iterator Iter = vecOnLine.begin();
	DWORD color = 0;
	for(;Iter != vecOnLine.end();++Iter)
	{
		m_vctAllMember.push_back(*Iter);
		AddToList((*Iter), color);
	}
}
void CUI_ID_FRAME_GuildMember::ShowNonOnlineMember()
{
	//将在线玩家的数据加入到List
	vector<GuildMember*>& vecNonOnLine = s_CUI_ID_FRAME_GuildBaseInfo.GetGuildNonOnLineMember();
	if(vecNonOnLine.empty()) return;
	vector<GuildMember*>::iterator Iter = vecNonOnLine.begin();
	DWORD color = Color_Config.getColor(CC_GUILD_OFFLINE);;
	for(;Iter != vecNonOnLine.end();++Iter)
	{
		m_vctAllMember.push_back(*Iter);
		AddToList((*Iter), color);
	}
}
void CUI_ID_FRAME_GuildMember::AddToList(GuildMember* pMember, DWORD color)//将一个公会成员的数据加入到List里面去
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

	//最后上线时间
	__int64 OnLineTime=pMember->GetOnLineTime();
	//将时间转换为数据
	if(OnLineTime == 0)
	{
		MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%s",theXmlString.GetString(eText_GuildMember_OnLineNull));
		stItem.SetData(szText, 0, NULL, color);
		stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		m_pID_LIST_OnlineTime->AddItem(&stItem, NULL, false);
		stItem.clear();
		memset(szText, 0, sizeof(szText));	
	}
	else
	{
		time_t logtime = OnLineTime;
		struct tm sysNowTime(*localtime(&logtime));	
		MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_GuildMember_OnLineTime),
			sysNowTime.tm_year+1900,sysNowTime.tm_mon+1,sysNowTime.tm_mday);
		stItem.SetData(szText, 0, NULL, color);
		stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		m_pID_LIST_OnlineTime->AddItem(&stItem, NULL, false);
		stItem.clear();
		memset(szText, 0, sizeof(szText));	
	}
}
const char* CUI_ID_FRAME_GuildMember::GetPositionByID(int nPosition) const 
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
const char* CUI_ID_FRAME_GuildMember::GetProfessionByID(int nProfessionID) const 
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
void CUI_ID_FRAME_GuildMember::ClearAllList()
{
	m_pID_LIST_MEMBER->Clear();
	m_pID_LIST_TeamName->Clear();
	m_pID_LIST_Lvl->Clear();
	m_pID_LIST_Job->Clear();
	m_pID_LIST_Work->Clear();
	//m_pID_LIST_Tong->Clear();
	m_pID_LIST_Activity->Clear();
	m_pID_LIST_GongXian->Clear();
	//m_pID_LIST_Line->Clear();
	m_pID_LIST_OnlineTime->Clear();
}

void CUI_ID_FRAME_GuildMember::SortAndRefresh()
{
	if (!m_currentSortFunc)
	{
		return;
	}
	//获取在线 和不在线的玩家 并且对集合进行排序
	vector<GuildMember*>& vecOnLine = s_CUI_ID_FRAME_GuildBaseInfo.GetGuildOnLineMember();
	vector<GuildMember*>& vecNonOnLine = s_CUI_ID_FRAME_GuildBaseInfo.GetGuildNonOnLineMember();
	std::stable_sort(vecOnLine.begin(), vecOnLine.end(), m_currentSortFunc);
	std::stable_sort(vecNonOnLine.begin(), vecNonOnLine.end(), m_currentSortFunc);
}
bool CUI_ID_FRAME_GuildMember::SortByName(GuildMember* lhs, GuildMember* rhs)
{
	  return strlen(lhs->GetName()) < strlen(rhs->GetName());
}

bool CUI_ID_FRAME_GuildMember::SortByLevel(GuildMember* lhs, GuildMember* rhs)
{
	return lhs->GetLevel() < rhs->GetLevel();
}

bool CUI_ID_FRAME_GuildMember::SortByProfession( GuildMember* lhs, GuildMember* rhs )
{
	return lhs->GetProfession() < rhs->GetProfession();
}

bool CUI_ID_FRAME_GuildMember::SortByPosition( GuildMember* lhs, GuildMember* rhs )
{
	return lhs->GetPosition() < rhs->GetPosition();
}
bool CUI_ID_FRAME_GuildMember::SortByActive( GuildMember* lhs, GuildMember* rhs )
{
	return lhs->GetActivity() < rhs->GetActivity();
}

bool CUI_ID_FRAME_GuildMember::SortByOffer( GuildMember* lhs, GuildMember* rhs )
{
	return lhs->GetOffer() < rhs->GetOffer();
}
bool CUI_ID_FRAME_GuildMember::SortByOnlineTime(GuildMember* lhs, GuildMember* rhs)
{
	return lhs->GetOnLineTime() < rhs->GetOnLineTime();
}
bool CUI_ID_FRAME_GuildMember::SortByName_Reverse(GuildMember* lhs, GuildMember* rhs)
{
	return strlen(lhs->GetName()) > strlen(rhs->GetName());
}

bool CUI_ID_FRAME_GuildMember::SortByLevel_Reverse(GuildMember* lhs, GuildMember* rhs)
{
	return lhs->GetLevel() > rhs->GetLevel();
}

bool CUI_ID_FRAME_GuildMember::SortByProfession_Reverse( GuildMember* lhs, GuildMember* rhs )
{
	return lhs->GetProfession() > rhs->GetProfession();
}

bool CUI_ID_FRAME_GuildMember::SortByPosition_Reverse( GuildMember* lhs, GuildMember* rhs )
{
	return lhs->GetPosition() > rhs->GetPosition();
}

bool CUI_ID_FRAME_GuildMember::SortByActive_Reverse( GuildMember* lhs, GuildMember* rhs )
{
	return lhs->GetActivity() > rhs->GetActivity();
}

bool CUI_ID_FRAME_GuildMember::SortByOffer_Reverse( GuildMember* lhs, GuildMember* rhs )
{
	return lhs->GetOffer() > rhs->GetOffer();
}
bool CUI_ID_FRAME_GuildMember::SortByOnlineTime_Reverse(GuildMember* lhs, GuildMember* rhs)
{
	return lhs->GetOnLineTime() > rhs->GetOnLineTime();
}
void CUI_ID_FRAME_GuildMember::SetSortFunc(SortType ekey)
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

void CUI_ID_FRAME_GuildMember::OnUpdateListShowHeight()
{
	if (!m_pID_LIST_MEMBER || !m_pID_LIST_TeamName || !m_pID_LIST_Lvl
		|| !m_pID_LIST_Job || !m_pID_LIST_Work || !m_pID_LIST_Activity || !m_pID_LIST_GongXian || !m_pID_LIST_OnlineTime)
		return;

	int nStartIndex = m_pID_LIST_MEMBER->GetShowStartHeight();
	m_pID_LIST_TeamName->SetShowStartHeight(nStartIndex);
	m_pID_LIST_Lvl->SetShowStartHeight(nStartIndex);
	m_pID_LIST_Job->SetShowStartHeight(nStartIndex);
	m_pID_LIST_Work->SetShowStartHeight(nStartIndex);
	m_pID_LIST_Activity->SetShowStartHeight(nStartIndex);
	m_pID_LIST_GongXian->SetShowStartHeight(nStartIndex);
	m_pID_LIST_OnlineTime->SetShowStartHeight(nStartIndex);
}

void CUI_ID_FRAME_GuildMember::ID_List_OnRBClick(ControlObject* pSender, ControlList::S_List* pItem)
{
	int x,y;
	x = theUiManager.m_ptMoust.x;
	y = theUiManager.m_ptMoust.y;

	ControlList::S_List* item = s_CUI_ID_FRAME_GuildMember.m_pID_LIST_TeamName->GetListItem( s_CUI_ID_FRAME_GuildMember.m_pID_LIST_MEMBER->GetCurSelIndex() );
	if ( !item || strlen( item->m_szText ) <= 0 )
		return;

	if ( strcmp( thePlayerRole.GetName(), item->m_szText) == 0 )
		return;

	s_CUI_ID_FRAME_RBTNMENU.SetPrivateName(  item->m_szText );
	s_CUI_ID_FRAME_RBTNMENU.SetVisable( true );
	s_CUI_ID_FRAME_RBTNMENU.SetPos( x, y );
	if( s_CUI_ID_FRAME_RBTNMENU.GetFrame() )
		theUiManager.ToTop( s_CUI_ID_FRAME_RBTNMENU.GetFrame() );
	theUiManager.Compositor();
}