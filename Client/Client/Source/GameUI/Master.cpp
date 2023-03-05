/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yangxiaoyong\桌面\师徒\Master.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Master.h"
#include "UIMgr.h"
#include "XmlStringLanguage.h"
#include "color_config.h"
#include "SystemConfig.h"
#include "MessageBox.h"
#include "NetworkInput.h"
#include "ShowScreenText.h"
#include "ChatInfoBox.h"
#include "AddMember.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "ChatMessageMgr.h"
#include "RbtnMenu.h"
#include "Common.h"
#include "FriendDlg.h"
#include "Ui/InfoList.h"
#include "RelationMessage.h"

CUI_ID_FRAME_Master s_CUI_ID_FRAME_Master;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Master, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Master, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Master, ID_LIST_MemberOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Master, ID_BUTTON_KickOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Master, ID_BUTTON_LeaveOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Master, ID_BUTTON_TeachOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Master, ID_BUTTON_ReportOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Master, ID_LIST_GuanXiOnListSelectChange )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Master, ID_BUTTON_ChooseStudentOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Master, ID_BUTTON_ChooseTeacherOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Master, ID_BUTTON_AddFriendOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Master, ID_BUTTON_TeamOnButtonClick )
CUI_ID_FRAME_Master::CUI_ID_FRAME_Master()
{
	// Member
	ResetMembers();
	Reset();
}
void CUI_ID_FRAME_Master::ResetMembers()
{
	m_pID_FRAME_Master = NULL;
	m_pID_TEXT_Point = NULL;
	m_pID_TEXT_Level = NULL;
	m_pID_PICTURE_MemberWall = NULL;
	m_pID_LIST_Member = NULL;
	m_pID_BUTTON_Kick = NULL;
	m_pID_BUTTON_Leave = NULL;
// 	m_pID_BUTTON_Teach = NULL;
// 	m_pID_BUTTON_Report = NULL;
	m_pID_LIST_GuanXi = NULL;
	m_pID_TEXT_Explain = NULL;
// 	m_pID_BUTTON_ChooseStudent = NULL;
// 	m_pID_BUTTON_ChooseTeacher = NULL;
	m_pID_TEXT_Explain2 = NULL;
}

void CUI_ID_FRAME_Master::Reset()
{
	m_eType = eMT_None;
	m_uchMasterLevel = 0;
	m_dwMasterValue = 0;
	m_dwMaxMasterValue = 0;
	m_dwExperience = 0;
	m_bNeedRefresh = true;
	m_bKickRelation = false;
}
// Frame
bool CUI_ID_FRAME_Master::OnFrameRun()
{
	if( !IsVisable() )
		return true;

	if( m_bNeedRefresh )
	{
		RefreshALL();
		m_bNeedRefresh = false;
	}
	return true;
}
bool CUI_ID_FRAME_Master::OnFrameRender()
{
	return true;
}
// List
void CUI_ID_FRAME_Master::ID_LIST_MemberOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_Master )
		return;
}
// Button
bool CUI_ID_FRAME_Master::ID_BUTTON_KickOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Master )
		return false;
	// 逐出师门
	if( m_eType != eMT_Teacher )
	{
		return false;
	}

	ControlList::S_List *pItem = m_pID_LIST_Member->GetCurSelItem();
	if(pItem)
	{
		std::string strKickName = pItem->m_szText;
		if( strKickName.length() == 0 )
		{
			assert(0);
			return false;
		}

		MsgDeleteRelationReq msg;
		int nId = thePlayerRole.GetdbID( strKickName.c_str() );
		if(nId)
			msg.nPlayerID = nId;
		msg.stRelation = RelationDefine::Student;

		char szTemp[256] = {0};
		int gold = 0, silver = 0,copper = 0;
		thePlayerRole.GetGSCFromMoney(theRelationConfig.GetRemovePrenticeCostMoney(),gold,silver,copper);
		MeSprintf_s( szTemp, sizeof(szTemp)/sizeof(char)-1, theXmlString.GetString(eText_ConfirmKickStudent), strKickName.c_str(), gold );
		s_CUI_ID_FRAME_MessageBox.Show( szTemp, "", CUI_ID_FRAME_MessageBox::eTypeYesNo,
			false, s_CUI_ID_FRAME_Master.sendReqKickAndLeaver, &msg, sizeof(MsgDeleteRelationReq) );
	}

	return true;
}
// Button
bool CUI_ID_FRAME_Master::ID_BUTTON_LeaveOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Master )
		return false;
	// 叛离师门
	if( m_eType != eMT_Student )
	{
		return false;
	}

	ControlList::S_List *pItem = m_pID_LIST_Member->GetListItem(0);
	if(pItem)
	{
		std::string strTeacherName = pItem->m_szText;
		if( strTeacherName.length() == 0 )
		{
			assert(0);
			return false;
		}

		MsgDeleteRelationReq msg;
		int nId = thePlayerRole.GetdbID( strTeacherName.c_str() );
		if(nId)
			msg.nPlayerID = nId;
		msg.stRelation = RelationDefine::Teacher;

		char szTemp[256] = {0};
		int gold = 0, silver = 0,copper = 0;
		thePlayerRole.GetGSCFromMoney(theRelationConfig.GetRemoveMasterCostMoney(),gold,silver,copper);
		MeSprintf_s( szTemp, sizeof(szTemp)/sizeof(char)-1, theXmlString.GetString(eText_ConfirmLeaveTeacher), gold );
		s_CUI_ID_FRAME_MessageBox.Show( szTemp, "", CUI_ID_FRAME_MessageBox::eTypeYesNo,
			false, s_CUI_ID_FRAME_Master.sendReqKickAndLeaver, &msg, sizeof(MsgDeleteRelationReq) );
	}
	return true;
}
// Button
//bool CUI_ID_FRAME_Master::ID_BUTTON_TeachOnButtonClick( ControlObject* pSender )
//{
//	if( !m_pID_FRAME_Master )
//		return false;
//	// 指点徒弟
//	if( m_eType != eMT_Teacher )
//	{
//		return false;
//	}
//
//	ControlList::S_List *pItem = m_pID_LIST_Member->GetCurSelItem();
//	if(pItem)
//	{
//		std::string strStudent = pItem->m_szText;
//		if( strStudent.length() == 0 )
//		{
//			assert(0);
//			return false;
//		}
//
//		int nId = thePlayerRole.GetdbID( strStudent.c_str() );
//		if( nId )
//		{
//			if( thePlayerRole.IsOnline(strStudent.c_str()) )	// 必须在线
//			{
//				MsgMasterReportReq msg;
//				msg.dwPrenticeID = nId;
//				GettheNetworkInput().SendMsg( &msg );
//			}
//			else
//			{
//				GetShowScreenText() ->AddInfo( theXmlString.GetString(eText_StudentNotOnline), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//				s_CUI_ID_FRAME_InfoList. AddInfo(theXmlString.GetString(eText_StudentNotOnline), Color_Config.getColor( CC_SystemPromp ));
//				return false;
//			}
//		}
//	}
//
//	return true;
//}
//// Button
//bool CUI_ID_FRAME_Master::ID_BUTTON_ReportOnButtonClick( ControlObject* pSender )
//{
//	if( !m_pID_FRAME_Master )
//		return false;
//	// 向师傅汇报
//	if( m_eType != eMT_Student )
//	{
//		return false;
//	}
//
//	ControlList::S_List *pItem = m_pID_LIST_Member->GetListItem(0);
//	if(pItem)
//	{
//		std::string strTeacher = pItem->m_szText;
//		if( strTeacher.length() == 0 )
//		{
//			assert(0);
//			return false;
//		}
//		if( thePlayerRole.IsOnline(strTeacher.c_str()) )	// 必须在线
//		{
//			MsgPrenticeReportReq msg;
//			GettheNetworkInput().SendMsg( &msg );
//		}
//		else
//		{
//			GetShowScreenText() ->AddInfo( theXmlString.GetString(eText_TeacherNotOnline), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//			s_CUI_ID_FRAME_InfoList. AddInfo(theXmlString.GetString(eText_TeacherNotOnline), Color_Config.getColor( CC_SystemPromp ));
//			return false;
//		}
//	}
//	return true;
//}
// List
void CUI_ID_FRAME_Master::ID_LIST_GuanXiOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_Master )
		return;
}
// Button
//bool CUI_ID_FRAME_Master::ID_BUTTON_ChooseStudentOnButtonClick( ControlObject* pSender )
//{
//	if( !m_pID_FRAME_Master )
//		return false;
//	return true;
//}
//// Button
//bool CUI_ID_FRAME_Master::ID_BUTTON_ChooseTeacherOnButtonClick( ControlObject* pSender )
//{
//	if( !m_pID_FRAME_Master )
//		return false;
//	return true;
//}
//// Button
//bool CUI_ID_FRAME_Master::ID_BUTTON_AddFriendOnButtonClick( ControlObject* pSender )
//{
//	if( !m_pID_FRAME_Master )
//		return false;
//	// 按钮执行短消息功能
//	ControlList::S_List *pItem = m_pID_LIST_Member->GetCurSelItem();
//	if(pItem)
//	{
//		std::string strPlayer = pItem->m_szText;
//		if( strPlayer.length() == 0 )
//		{
//			assert(0);
//			return false;
//		}
//		if( thePlayerRole.IsOnline(strPlayer.c_str()) )
//		{
//			chatMessageManage.ShowChatMessageFrame(strPlayer.c_str() );
//		}
//	}
//	return true;
//}
// Button
bool CUI_ID_FRAME_Master::ID_BUTTON_TeamOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Master )
		return false;
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if ( !pMe )
		return false;
	ControlList::S_List *pItem = m_pID_LIST_Member->GetCurSelItem();
	if(pItem)
	{
		std::string strPlayer = pItem->m_szText;
		if( strPlayer.length() == 0 )
		{
			assert(0);
			return false;
		}

		if( !thePlayerRole.IsOnline(strPlayer.c_str()) )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eMessageBox_InviterIsOffline) );
		}
		else
		{
			char szInfo[256] = {0};

			//发送组队申请
			MeSprintf_s( szInfo, sizeof(szInfo)/sizeof(char)-1, "%s ~%s_ %s", theXmlString.GetString(eUI_YouTo), strPlayer.c_str(), theXmlString.GetString(eUI_SendTeam));
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Invite_Team, szInfo );

			//if(thePlayerRole.GetCampType() != CampDefine::NoneCamp)
			//{
			//	//不可以创建队伍
			//	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eClient_CampBattle_Team));
			//	return true;
			//}

			MsgRequestTeam msg;
			msg.header.stID = pMe->GetID();
			msg.dwNewbieID = -1;
			msg.AssignMode = thePlayerRole.GetAssignMode();
			msg.AssignItemLevel = thePlayerRole.GetItemRollLevel();
			strncpy(msg.szNewbieName, strPlayer.c_str(), sizeof(msg.szNewbieName)-1);
			GettheNetworkInput().SendMsg(&msg);
		}
	}
	return true;
}

// 装载UI
bool CUI_ID_FRAME_Master::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Master.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Master.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Master::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Master, s_CUI_ID_FRAME_MasterOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Master, s_CUI_ID_FRAME_MasterOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_Master, ID_LIST_Member, s_CUI_ID_FRAME_MasterID_LIST_MemberOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_Master, ID_BUTTON_Kick, s_CUI_ID_FRAME_MasterID_BUTTON_KickOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Master, ID_BUTTON_Leave, s_CUI_ID_FRAME_MasterID_BUTTON_LeaveOnButtonClick );
	/*theUiManager.OnButtonClick( ID_FRAME_Master, ID_BUTTON_Teach, s_CUI_ID_FRAME_MasterID_BUTTON_TeachOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Master, ID_BUTTON_Report, s_CUI_ID_FRAME_MasterID_BUTTON_ReportOnButtonClick );*/
	theUiManager.OnListSelectChange( ID_FRAME_Master, ID_LIST_GuanXi, s_CUI_ID_FRAME_MasterID_LIST_GuanXiOnListSelectChange );
// 	theUiManager.OnButtonClick( ID_FRAME_Master, ID_BUTTON_ChooseStudent, s_CUI_ID_FRAME_MasterID_BUTTON_ChooseStudentOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_Master, ID_BUTTON_ChooseTeacher, s_CUI_ID_FRAME_MasterID_BUTTON_ChooseTeacherOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_Master, ID_BUTTON_AddFriend, s_CUI_ID_FRAME_MasterID_BUTTON_AddFriendOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Master, ID_BUTTON_Team, s_CUI_ID_FRAME_MasterID_BUTTON_TeamOnButtonClick );

	m_pID_FRAME_Master = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Master );
	m_pID_TEXT_Point = (ControlText*)theUiManager.FindControl( ID_FRAME_Master, ID_TEXT_Point );
	m_pID_TEXT_Level = (ControlText*)theUiManager.FindControl( ID_FRAME_Master, ID_TEXT_Level );
	m_pID_PICTURE_MemberWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Master, ID_PICTURE_MemberWall );
	m_pID_LIST_Member = (ControlList*)theUiManager.FindControl( ID_FRAME_Master, ID_LIST_Member );
	m_pID_BUTTON_Kick = (ControlButton*)theUiManager.FindControl( ID_FRAME_Master, ID_BUTTON_Kick );
	m_pID_BUTTON_Leave = (ControlButton*)theUiManager.FindControl( ID_FRAME_Master, ID_BUTTON_Leave );
// 	m_pID_BUTTON_Teach = (ControlButton*)theUiManager.FindControl( ID_FRAME_Master, ID_BUTTON_Teach );
// 	m_pID_BUTTON_Report = (ControlButton*)theUiManager.FindControl( ID_FRAME_Master, ID_BUTTON_Report );
	m_pID_LIST_GuanXi = (ControlList*)theUiManager.FindControl( ID_FRAME_Master, ID_LIST_GuanXi );
	m_pID_TEXT_Explain = (ControlText*)theUiManager.FindControl( ID_FRAME_Master, ID_TEXT_Explain );
// 	m_pID_BUTTON_ChooseStudent = (ControlButton*)theUiManager.FindControl( ID_FRAME_Master, ID_BUTTON_ChooseStudent );
// 	m_pID_BUTTON_ChooseTeacher = (ControlButton*)theUiManager.FindControl( ID_FRAME_Master, ID_BUTTON_ChooseTeacher );
// 	m_pID_BUTTON_AddFriend = (ControlButton*)theUiManager.FindControl( ID_FRAME_Master, ID_BUTTON_AddFriend );
	m_pID_BUTTON_Team = (ControlButton*)theUiManager.FindControl( ID_FRAME_Master, ID_BUTTON_Team );
	m_pID_TEXT_Explain2 = (ControlText*)theUiManager.FindControl( ID_FRAME_Master, ID_TEXT_Explain2 );

// 	assert( m_pID_FRAME_Master );
// 	assert( m_pID_TEXT_Point );
// 	assert( m_pID_TEXT_Level );
// 	assert( m_pID_PICTURE_MemberWall );
// 	assert( m_pID_LIST_Member );
// 	assert( m_pID_BUTTON_Kick );
// 	assert( m_pID_BUTTON_Leave );
// 	assert( m_pID_BUTTON_Teach );
// 	assert( m_pID_BUTTON_Report );
// 	assert( m_pID_LIST_GuanXi );
// 	assert( m_pID_TEXT_Explain );
// 	assert( m_pID_BUTTON_ChooseStudent );
// 	assert( m_pID_BUTTON_ChooseTeacher );
// 	assert( m_pID_BUTTON_AddFriend );
// 	assert( m_pID_BUTTON_Team );
// 	assert( m_pID_TEXT_Explain2 );

	m_pID_FRAME_Master->SetMsgHoldup(false);

	m_pID_LIST_Member->setShowTip();
	m_pID_LIST_Member->SetRBSelectEnable();
	m_pID_LIST_Member->SetRBClickFun( ID_List_OnRBClick );
	m_pID_LIST_Member->SetLDBClickFun( ID_List_OnLDBClick );

	m_pID_LIST_GuanXi->SetMsgHoldup(false);	//不接受消息
	m_pID_LIST_GuanXi->HaveSelBar( false );	//没有绿色cur选中地图
	m_pID_LIST_GuanXi->SetCurSelIndex(-1);

	// 可寻路NPC
// 	m_pID_TEXT_Explain->SetHyberClickFun(HyberClickInfo);
	m_pID_TEXT_Explain->SetColUrl(Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)));

	Reset();
	GetFrame()->SetFather(s_CUI_ID_FRAME_Friend.GetFrame());
	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Master::_UnLoadUI()
{
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\Master.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Master::_IsVisable()
{
	if( !m_pID_FRAME_Master )
		return false;
	return m_pID_FRAME_Master->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Master::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_Master )
		return;
	m_pID_FRAME_Master->SetVisable( bVisable );
	if( bVisable && m_bNeedRefresh )
	{
		RefreshALL();
	}
}

void CUI_ID_FRAME_Master::RefreshALL()
{
	if( !m_pID_FRAME_Master )
		return;

	ClearAll();
	Refresh();
	m_bNeedRefresh = false;
}

void CUI_ID_FRAME_Master::ClearAll()
{
	m_pID_TEXT_Point->SetText("");
	m_pID_TEXT_Level->SetText("");
	m_pID_LIST_Member->Clear();
	m_pID_LIST_GuanXi->Clear();
	m_pID_TEXT_Explain->SetText("");
	m_pID_LIST_Member->SetCurSelIndex(-1);
	m_pID_LIST_GuanXi->SetCurSelIndex(-1);
	m_pID_LIST_Member->GetScrollBar()->SetValue(0);
	// 师傅按钮
	m_pID_BUTTON_Kick->SetVisable(false);
// 	m_pID_BUTTON_Teach->SetVisable(false);
// 	m_pID_BUTTON_ChooseStudent->SetVisable(false);

	// 徒弟按钮
	m_pID_BUTTON_Leave->SetVisable(false);
// 	m_pID_BUTTON_Report->SetVisable(false);
// 	m_pID_BUTTON_ChooseTeacher->SetVisable(false);

	m_pID_TEXT_Explain2->SetText("");
}

void CUI_ID_FRAME_Master::Refresh()
{
	m_eType = eMT_None;

	char szText[256] = {0};
	bool bHasStudent = false;
	bool bHasTeacher = false;
	bool bCanGetStudent = thePlayerRole.IsCanReceivePrentice();
	// 是否创建师门
	if( bCanGetStudent )
	{
		// 搜寻徒弟列表
		bHasStudent = RetreiveMemberList(false);
		if( bHasStudent )
		{
			m_eType = eMT_Teacher;
		}

		m_pID_BUTTON_Kick->SetVisable(true);
// 		m_pID_BUTTON_Teach->SetVisable(true);
		m_pID_TEXT_Explain2->SetText(theXmlString.GetString(eText_TeachDesc));

		// 师门等级，威望值
		m_uchMasterLevel = thePlayerRole.GetMasterLevel();
		m_dwMasterValue = thePlayerRole.GetMasterValue();
		m_dwExperience = 0;
		const MasterInfo* pMasterInfo = theRelationConfig.GetMasterInfo(m_uchMasterLevel);
		if( pMasterInfo )
		{
			// 威望值
			m_dwMaxMasterValue = pMasterInfo->GetMaxMasterValue();
			char szbuf[128] = {0};
			MeSprintf_s(szbuf, sizeof(szbuf)/sizeof(char) -1, "%u/%u", m_dwMasterValue, m_dwMaxMasterValue);
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) -1, theXmlString.GetString(eText_WeiWang), szbuf);
			m_pID_TEXT_Point->SetText(szText);

			// 师门等级
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) -1, theXmlString.GetString(eText_TeacherLevel), m_uchMasterLevel);
			m_pID_TEXT_Level->SetText(szText);
		}
		else
		{
			assert(0&&"Friendly.config表获取不到师傅等级对应数据");
		}
	}
	else
	{
		// 搜寻师傅
		bHasTeacher = RetreiveMemberList(true);
		if( bHasTeacher )
		{
			m_eType = eMT_Student;
			m_pID_BUTTON_Leave->SetVisable(true);
// 			m_pID_BUTTON_Report->SetVisable(true);
			m_pID_TEXT_Explain2->SetText(theXmlString.GetString(eText_ReportDesc));

			// 获取历练值
			m_uchMasterLevel = 0;
			m_dwMasterValue = 0;
			m_dwExperience = thePlayerRole.GetStudentExperience();
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) -1, theXmlString.GetString(eText_LiLian), m_dwExperience);
			m_pID_TEXT_Point->SetText(szText);
		}
	}
	if( !bHasTeacher && !bHasStudent )
	{
		if( bCanGetStudent )	// 创建师门但未收徒
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) -1, theXmlString.GetString(eText_NoStudent));
			m_pID_TEXT_Explain->SetText(szText);
		}
//		else if( thePlayerRole.GetLevel() >= theRelationConfig.GetPrenticeLimit().GetMaxLevel() )	// 超过最高拜师等级
//		{
//			m_pID_TEXT_Explain->SetText(theXmlString.GetString(eText_NeedCreateShiMen));
//			m_pID_BUTTON_Kick->SetVisable(true);
//// 			m_pID_BUTTON_Teach->SetVisable(true);
//			m_pID_TEXT_Explain2->SetText(theXmlString.GetString(eText_TeachDesc));
//		}
		else					// 可以拜师
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) -1, theXmlString.GetString(eText_NoTeacher));
			m_pID_TEXT_Explain->SetText(szText);
			m_pID_BUTTON_Leave->SetVisable(true);
// 			m_pID_BUTTON_Report->SetVisable(true);
			m_pID_TEXT_Explain2->SetText(theXmlString.GetString(eText_ReportDesc));
		}
	}
}

bool CUI_ID_FRAME_Master::RetreiveMemberList(bool bFindTeacher)
{
	bool bGet = false;

	std::map<int, RelationDataToClient>::iterator iter;
	ControlList::S_List	stItem;
	std::string strSex;
	std::string strPK;
	std::string strProfession;
	char szTip[128] = {0};
	// 在线
	for(iter = thePlayerRole.GetMapFriendInfo().begin(); iter != thePlayerRole.GetMapFriendInfo().end(); ++iter)
	{
		if( iter->second.GetOnLine() && 
			( (bFindTeacher && iter->second.HaveRelation(RelationDefine::Teacher)) || (!bFindTeacher && iter->second.HaveRelation(RelationDefine::Student)) )
		  )
		{
			RelationDataToClient &friendData = iter->second;
			GetSexProfessionString(friendData, strSex, strProfession);

			_snprintf( szTip, sizeof(szTip)/sizeof(char) -1, theXmlString.GetString(eTip_Client_FriendListInfo), iter->second.GetName(),
				strSex.c_str(), (int)iter->second.GetLevel(), strProfession.c_str() );
			stItem.clear();
			stItem.setTip( szTip, DT_LEFT );
			stItem.setIsOnline(true);

			DWORD col = Color_Config.GetPkNameColor(PKMode_Fight/*iter->second.GetPKMode()*/);
			stItem.SetData( (iter->second).GetName(), 0, NULL, col );
			m_pID_LIST_Member->AddItem(&stItem,NULL, false);

			// 关系
			ControlList::S_List	stItemGuanXi;
			stItemGuanXi.SetData( "" );

			if(friendData.HaveRelation(RelationDefine::Marriage))
			{
				stItemGuanXi.SetData( "{#1201}" );
			}
			else if(friendData.HaveRelation(RelationDefine::Teacher))
			{
				stItemGuanXi.SetData( "{#1202}" );
			}
			else if(friendData.HaveRelation(RelationDefine::Student))
			{
				stItemGuanXi.SetData( "{#1203}" );
			}
			else if(friendData.HaveRelation(RelationDefine::Brother))
			{
				stItemGuanXi.SetData( "{#1204}" );
			}
			m_pID_LIST_GuanXi->AddItem( &stItemGuanXi,NULL, false);

			bGet = true;
		}
	}
	// 离线
	for( iter = thePlayerRole.GetMapFriendInfo().begin(); iter != thePlayerRole.GetMapFriendInfo().end(); ++iter )
	{
		if( !iter->second.GetOnLine() && 
			( (bFindTeacher && iter->second.HaveRelation(RelationDefine::Teacher)) || (!bFindTeacher && iter->second.HaveRelation(RelationDefine::Student)) )
			)
		{
			stItem.clear();
			stItem.SetData( (iter->second).GetName(),  0, NULL, Color_Config.getColor(CC_FRIEND_OFFLINE) );
			m_pID_LIST_Member->AddItem(&stItem,NULL, false);

			// 关系
			ControlList::S_List	stItemGuanXi;
			stItemGuanXi.SetData( "" );

			RelationDataToClient &friendData = iter->second;
			if(friendData.HaveRelation(RelationDefine::Marriage))
			{
				stItemGuanXi.SetData( "{#1201}" );
			}
			else if(friendData.HaveRelation(RelationDefine::Teacher))
			{
				stItemGuanXi.SetData( "{#1202}" );
			}
			else if(friendData.HaveRelation(RelationDefine::Student))
			{
				stItemGuanXi.SetData( "{#1203}" );
			}
			else if(friendData.HaveRelation(RelationDefine::Brother))
			{
				stItemGuanXi.SetData( "{#1204}" );
			}
			m_pID_LIST_GuanXi->AddItem( &stItemGuanXi,NULL, false);

			bGet = true;
		}
	}
	return bGet;
}

void CUI_ID_FRAME_Master::GetSexProfessionString( RelationDataToClient &friendData, std::string &strSex, string &strProfession )
{
	switch( friendData.GetSex() )
	{
	case Sex_Male:
		strSex = theXmlString.GetString(eClient_AddInfo_2slk_132);
		break;
	case Sex_Female:
		strSex = theXmlString.GetString(eClient_AddInfo_2slk_133);
		break;
	case Sex_Max:
		strSex = theXmlString.GetString(eProfession_Unknown);
		break;
	}
	strProfession = theXmlString.GetString(eProfession_Unknown);
	if (friendData.GetProfession() != EArmType_MaxSize)
	{
		CProfessionInfo* pInfo = GetSystemConfig()->GetProessionInfoFromID(friendData.GetProfession());
		if (pInfo)
		{
			strProfession = pInfo->m_strProShow.c_str();
		}
	}
}

bool CUI_ID_FRAME_Master::sendReqKickAndLeaver( const char bPressYesButton, void *pData )
{
	if( bPressYesButton && pData )
	{
		s_CUI_ID_FRAME_Master.SetKickRelation(true);
		MsgDeleteRelationReq* msg = (MsgDeleteRelationReq*)pData;
		GettheNetworkInput().SendMsg( msg );
	}
	return true;
}

void CUI_ID_FRAME_Master::ID_List_OnLDBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
// 	if( s_CUI_ID_FRAME_Master.GetFrame() )
// 		s_CUI_ID_FRAME_Master.ID_BUTTON_AddFriendOnButtonClick(NULL);
	theUiManager.SetJumpNextLButtonUp(true);
}

void CUI_ID_FRAME_Master::ID_List_OnRBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( pItem && thePlayerRole.IsOnline( pItem->m_szText ))
	{	
		//这里打开右键菜单
		s_CUI_ID_FRAME_RBTNMENU.SetPrivateName( pItem->m_szText );
		s_CUI_ID_FRAME_RBTNMENU.SetVisable(true);
		s_CUI_ID_FRAME_RBTNMENU.SetPos( theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y );
		if( s_CUI_ID_FRAME_RBTNMENU.GetFrame() )
			theUiManager.ToTop( s_CUI_ID_FRAME_RBTNMENU.GetFrame() );
	}
}

void CUI_ID_FRAME_Master::HyberClickInfo( ControlObject* pSender, const char* szName )
{
	if (szName)
	{
		NpcCoord::getInstance()->clickHyberToMiniMap(szName);
	}		
}
