/********************************************************************
Created by UIEditor.exe
FileName: D:\Tj\Client\UI\FriendDlg.cpp
*********************************************************************/
#include "MeTerrain/stdafx.h"
#include <assert.h>
#include "MeUi/UiManager.h"
//#include "MoreDB.h"
#include "FuncPerformanceLog.h"
#include "MsgBase.h"
//#include "friend_manager.h"
#include "FriendDlg.h"

#include "GameMain.h"
#include "AddFriend.h"
#include "UIBase.h"
#include "ChatInfoBox.h"
#include "../Player.h"
#include "PlayerMgr.h"
#include "ActionUI.h"
#include "FriendDlgRight.h"
#include "Group_Me.h"
#include "../color_config.h"
#include "XmlStringLanguage.h"
#include "MessageBox.h"
#include "GlobalDef.h"
// #include "PersonKiller.h"
// #include "Me3d/Me3d_World.h"
#include "SystemConfig.h"
// #include "Me3d/Me3d_World.h"
#include "../Sociality.h"
#include "chat_particular.h"
#include "ChatMessageMgr.h"
#include "RelationMessage.h"
#include "GameSetting.h"
//#include "RbtnMenu.h"
#include "Master.h"
#include "Search.h"
#include "Ui/Rename.h"
#include "Ui/Create.h"
#include "Ui/FriendView.h"
#include "MiniChat.h"
#include "MainMenu.h"
#include "ui/Editor.h"
#include "ui/Sprite.h"
#include "ScreenInfoManager.h"
#include "ChatCheck.h"

#define FRIEND_ONLINE 0xff00ff00
#define FRIEND_OUTLINE 0xff808080
#define FRIEND_ADDINFO 0xffffff00

//小精灵id号
const unsigned int SpriteFriendID = 0xffffffff;
static bool IsTheSprite(RelationDataToClient* pRelationData)
{
	if(NULL == pRelationData)
		return false;
	
	return SpriteFriendID == pRelationData->GetID();
}

const clock_t SENDMSG_INTERVAL_TIME	= 2*1000*60;

const char* g_gifFemalePortrait[CUI_ID_FRAME_Friend::m_nMaxFamalePortrait*2] = {
	"{#FIF0}"
	,"{#FIF1}"
	,"{#FIF2}"
	,"{#FIF3}"
	,"{#FIF4}"


	//以下是灰态图片
	,"{#FIFG0}"
	,"{#FIFG1}"
	,"{#FIFG2}"
	,"{#FIFG3}"
	,"{#FIFG4}"
};

const char* g_gifFemalePortraitChating[CUI_ID_FRAME_Friend::m_nMaxFamalePortrait] = {
	"{#FIFF0}"
	,"{#FIFF1}"
	,"{#FIFF2}"
	,"{#FIFF3}"
	,"{#FIFF4}"
};

const char* g_gifMalePortrait[CUI_ID_FRAME_Friend::m_nMaxMalePortrait*2] = {
	"{#FIM0}"
	,"{#FIM1}"
	,"{#FIM2}"
	,"{#FIM3}"
	,"{#FIM4}"


	//以下是灰态图片
	,"{#FIMG0}"
	,"{#FIMG1}"
	,"{#FIMG2}"
	,"{#FIMG3}"
	,"{#FIMG4}"
};

const char* g_gifMalePortraitChating[CUI_ID_FRAME_Friend::m_nMaxMalePortrait*2] = {
	"{#FIMM0}"
	,"{#FIMM1}"
	,"{#FIMM2}"
	,"{#FIMM3}"
	,"{#FIMM4}"
};

const char* g_gifFriendStar[CUI_ID_FRAME_Friend::m_nFriendStar] = {
	"{#FIS0}"
	,"{#FIS1}"
	,"{#FIS2}"
	,"{#FIS3}"
	,"{#FIS4}"
};

CUI_ID_FRAME_Friend s_CUI_ID_FRAME_Friend;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Friend, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Friend, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Friend, ID_LIST_FriendInfoOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Friend, ID_BUTTON_AddFriendOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Friend, ID_BUTTON_DelFriendOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Friend, ID_BUTTON_chatOnButtonClick)
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Friend, ID_BUTTON_AddheimingdanOnButtonClick )//zjj add


MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Friend, ID_CHECKBOX_LinShiHaoYouOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Friend, ID_BUTTON_SearchOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Friend, ID_BUTTON_AddingOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Friend, ID_BUTTON_AddingFriendOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Friend, ID_BUTTON_RenameOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Friend, ID_BUTTON_MoodOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Friend, ID_BUTTON_AddingClassOnButtonClick )

CUI_ID_FRAME_Friend::CUI_ID_FRAME_Friend()
{
	guardfunc;
	// SGuildMember
	m_pID_FRAME_Friend = NULL;
	m_pID_LIST_FriendInfo = NULL;
	m_pID_BUTTON_AddFriend = NULL;
// 	m_pID_BUTTON_DelFriend = NULL;
	m_pID_BUTTON_Remove = NULL;
 	m_pID_BUTTON_Addheimingdan = 0;
// 	_pMoveHei = NULL;
// 	_pRequestTeam = NULL;
	_pCheckFriend = NULL;	//好友列表
	_pCheckBlackList = NULL;	//黑名单列表
	_pCheckTeachers = NULL;	//师徒列表
	//_pCheckBrother = NULL;		//兄弟列表
	_pCheckChouren=NULL;//结婚
	showTpye = eSTP_HaveRelation;
	m_pID_CHECKBOX_LinShiHaoYou = NULL;
	m_pID_BUTTON_Search = NULL;

	_beginForSendMsgUpdateInfo = 0;
	m_pID_TEXT_Wait = NULL;
// 	m_pID_LIST_GuanXi = NULL;
	m_pID_BUTTON_Adding = NULL;
	m_pID_BUTTON_AddingFriend = NULL;
	m_pID_BUTTON_Rename = NULL;
	m_pID_PICTURE_Head = NULL;
	m_pID_TEXT_PeopleName = NULL;
	m_pID_TEXT_PeopleMood = NULL;

	m_pID_LIST_FriendHead = NULL;

	m_pID_TEXT_CloseIconID = NULL;
	m_pID_TEXT_OpenIconID = NULL;

// 	m_bWaitingServerUpdate = false;
	unguard;
	
}
CUI_ID_FRAME_Friend::~CUI_ID_FRAME_Friend()
{
	guardfunc;
	unguard;
}
// Frame
bool CUI_ID_FRAME_Friend::OnFrameRun()
{
	guardfunc;

	if( !IsVisable() )
		return false;

	if(m_bNeedRefresh)
	{
		Refresh();

		m_bNeedRefresh = false;
	}
	{
		int nStartIndex = m_pID_LIST_FriendInfo->GetShowStartHeight();
		m_pID_LIST_FriendStar->SetShowStartHeight(nStartIndex);
	}

// 	if( _beginForSendMsgUpdateInfo == 0 )
// 		return false;

// 	clock_t tmNow = clock();
// 	if( tmNow - _beginForSendMsgUpdateInfo > SENDMSG_INTERVAL_TIME )
// 	{
// 		sendUpdataFrdInfo();
// 		_beginForSendMsgUpdateInfo = clock();
// 	}
	return true;

	unguard;
}
bool CUI_ID_FRAME_Friend::OnFrameRender()
{
	guardfunc;
	return true;
	unguard;
}
// List
void CUI_ID_FRAME_Friend::ID_LIST_FriendInfoOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	guardfunc;
	s_CUI_ID_FRAME_RBTNMENU.SetVisable(false);
	s_CUI_ID_FRAME_FriendDlgRight.SetVisable(false);
	unguard;
}
void CUI_ID_FRAME_Friend::ID_List_OnRBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	guardfunc;
	if( pItem )
	{//这里打开右键菜单
		if (s_CUI_ID_FRAME_Friend.showTpye == eSTP_HaveRelation && pItem->m_nHiberarchy == 0)
		{
			s_CUI_ID_FRAME_FriendDlgRight.SetVisable(true);
			if( s_CUI_ID_FRAME_FriendDlgRight.GetFrame() )
				theUiManager.ToTop( s_CUI_ID_FRAME_FriendDlgRight.GetFrame() );
			return;
		}
		if(pItem->m_pData)
		{
			RelationDataToClient* pRelationData = (RelationDataToClient*)pItem->m_pData;
			{
				s_CUI_ID_FRAME_RBTNMENU.SetPrivateName( pRelationData->GetName() );
				if (s_CUI_ID_FRAME_Friend.showTpye == eSTP_HaveRelation )
				{
					if(IsTheSprite(pRelationData))
					{
						return;
					}

					s_CUI_ID_FRAME_RBTNMENU.SetShowType(CUI_ID_FRAME_RBTNMENU::eShow_FriendFriend);
				}
				else
				{
					s_CUI_ID_FRAME_RBTNMENU.SetShowType(CUI_ID_FRAME_RBTNMENU::eShow_FriendOther);
				}
				s_CUI_ID_FRAME_RBTNMENU.SetVisable(true,pRelationData->GetOnLine());
				s_CUI_ID_FRAME_RBTNMENU.SetPos( theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y );
				if( s_CUI_ID_FRAME_RBTNMENU.GetFrame() )
					theUiManager.ToTop( s_CUI_ID_FRAME_RBTNMENU.GetFrame() );
				if (thePlayerRole.IsTeamHeader())
				{
					s_CUI_ID_FRAME_RBTNMENU.SetDBID(thePlayerRole.GetTeamMemberId(pRelationData->GetName()));
				}
			}
		}
	}
	unguard;
}
void CUI_ID_FRAME_Friend::ID_CheckBox_Friend( ControlObject* pSender, bool* pbChecked )
{
	guardfunc;


		s_CUI_ID_FRAME_Friend._pCheckFriend->SetCheck(true);
		s_CUI_ID_FRAME_Friend._pCheckBlackList->SetCheck(false);
		if(s_CUI_ID_FRAME_Friend._pCheckTeachers != NULL)
		{
			s_CUI_ID_FRAME_Friend._pCheckTeachers->SetCheck(false);
		}
		//s_CUI_ID_FRAME_Friend._pCheckBrother->SetCheck(false);
		s_CUI_ID_FRAME_Friend._pCheckChouren->SetCheck(false);
		s_CUI_ID_FRAME_Friend.m_pID_CHECKBOX_LinShiHaoYou->SetCheck(false);

		s_CUI_ID_FRAME_Friend.showTpye = eSTP_HaveRelation;
	s_CUI_ID_FRAME_Friend.Refresh();
	s_CUI_ID_FRAME_Friend.m_pID_LIST_FriendInfo->SetVisable(true); 
// 	s_CUI_ID_FRAME_Friend.m_pID_LIST_Youhaodu->SetVisable(true); 
 	s_CUI_ID_FRAME_Friend.m_pID_LIST_FriendStar->SetVisable(true); 

	s_CUI_ID_FRAME_Friend.AdaptButtons(0);
	
	unguard;
}

void CUI_ID_FRAME_Friend::ID_CHECKBOX_LinShiHaoYouOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
    if(!m_pID_FRAME_Friend)
    {
        assert(false&&"ui error");
        return ;
    }
	s_CUI_ID_FRAME_Friend._pCheckFriend->SetCheck(false);
	s_CUI_ID_FRAME_Friend._pCheckBlackList->SetCheck(true);
	if(s_CUI_ID_FRAME_Friend._pCheckTeachers != NULL)
	{
		s_CUI_ID_FRAME_Friend._pCheckTeachers->SetCheck(false);
	}
	//s_CUI_ID_FRAME_Friend._pCheckBrother->SetCheck(false);
	s_CUI_ID_FRAME_Friend._pCheckChouren->SetCheck(false);
	s_CUI_ID_FRAME_Friend.m_pID_CHECKBOX_LinShiHaoYou->SetCheck(true);
	s_CUI_ID_FRAME_Friend.showTpye = eSTP_TempFriend;
	Refresh();
	s_CUI_ID_FRAME_Friend.AdaptButtons(2);
}


void CUI_ID_FRAME_Friend::ID_CheckBox_Blacklist( ControlObject* pSender, bool* pbChecked )
{
	guardfunc;
	// 	s_CUI_ID_FRAME_Friend._pMoveHei->SetVisable(true);


	s_CUI_ID_FRAME_Friend._pCheckFriend->SetCheck(false);
	s_CUI_ID_FRAME_Friend._pCheckBlackList->SetCheck(true);
	if(s_CUI_ID_FRAME_Friend._pCheckTeachers != NULL)
	{
		s_CUI_ID_FRAME_Friend._pCheckTeachers->SetCheck(false);
	}

	//s_CUI_ID_FRAME_Friend._pCheckBrother->SetCheck(false);
	s_CUI_ID_FRAME_Friend._pCheckChouren->SetCheck(false);
	s_CUI_ID_FRAME_Friend.m_pID_CHECKBOX_LinShiHaoYou->SetCheck(false);

	s_CUI_ID_FRAME_Friend.showTpye = eSTP_BlackList;
	s_CUI_ID_FRAME_Friend.Refresh();

	s_CUI_ID_FRAME_Friend.AdaptButtons(3);
	
	unguard;
}

void CUI_ID_FRAME_Friend::ID_CheckBox_Teachers( ControlObject* pSender, bool* pbChecked )
{
	guardfunc;
	// 	s_CUI_ID_FRAME_Friend._pMoveHei->SetVisable(true);

	//m_nShortIdx = 1;
	if( s_CUI_ID_FRAME_Friend._pCheckFriend && s_CUI_ID_FRAME_Friend._pCheckBlackList && 
		s_CUI_ID_FRAME_Friend._pCheckTeachers && s_CUI_ID_FRAME_Friend._pCheckChouren )
	{
		s_CUI_ID_FRAME_Friend._pCheckFriend->SetCheck(false);
		s_CUI_ID_FRAME_Friend._pCheckBlackList->SetCheck(false);
		//s_CUI_ID_FRAME_Friend._pCheckBrother->SetCheck(false);
		s_CUI_ID_FRAME_Friend._pCheckTeachers->SetCheck(true);
		s_CUI_ID_FRAME_Friend._pCheckChouren->SetCheck(false);
		s_CUI_ID_FRAME_Friend.m_pID_CHECKBOX_LinShiHaoYou->SetCheck(false);

		s_CUI_ID_FRAME_Friend.showTpye = eSTP_Teacher;
	}
	s_CUI_ID_FRAME_Friend.Refresh();
	unguard;
}
//zjj add for Chouren
void CUI_ID_FRAME_Friend::ID_CheckBox_Chouren( ControlObject* pSender, bool* pbChecked )
{
	guardfunc;
	// 	s_CUI_ID_FRAME_Friend._pMoveHei->SetVisable(true);

	//m_nShortIdx = 2;

	s_CUI_ID_FRAME_Friend._pCheckFriend->SetCheck(false);
	s_CUI_ID_FRAME_Friend._pCheckBlackList->SetCheck(false);
	if(s_CUI_ID_FRAME_Friend._pCheckTeachers != NULL)
	{
		s_CUI_ID_FRAME_Friend._pCheckTeachers->SetCheck(false);
	}
	//s_CUI_ID_FRAME_Friend._pCheckBrother->SetCheck(false);
	s_CUI_ID_FRAME_Friend._pCheckChouren->SetCheck(true);
	s_CUI_ID_FRAME_Friend.m_pID_CHECKBOX_LinShiHaoYou->SetCheck(false);

	s_CUI_ID_FRAME_Friend.showTpye = eSTP_VendettaList;
	s_CUI_ID_FRAME_Friend.Refresh();

	s_CUI_ID_FRAME_Friend.AdaptButtons(1);

	unguard;
}
bool CUI_ID_FRAME_Friend::ID_BUTTON_AddheimingdanOnButtonClick( ControlObject* pSender )
{
    if(!m_pID_FRAME_Friend)
    {
        assert(false&&"ui error");
        return false;
    }
	if(!s_CUI_ID_FRAME_AddFriend.IsVisable())
	{
		s_CUI_ID_FRAME_AddFriend.SetFrameType(CUI_ID_FRAME_AddFriend::eFrameType_AddBlackFriend);
		s_CUI_ID_FRAME_AddFriend.SetVisable(TRUE);
	}
	return true;
}
// Button
bool CUI_ID_FRAME_Friend::ID_BUTTON_AddFriendOnButtonClick( ControlObject* pSender )
{
    if(!m_pID_FRAME_Friend)
    {
        assert(false&&"ui error");
        return false;
    }
	if(!s_CUI_ID_FRAME_AddFriend.IsVisable())
	{
		assert (showTpye == eSTP_HaveRelation);
		{
			s_CUI_ID_FRAME_AddFriend.SetFrameType( CUI_ID_FRAME_AddFriend::eFrameType_AddFriend );
			s_CUI_ID_FRAME_AddFriend.SetVisable(TRUE);
		}
	}

	return true;	
}
// bool CUI_ID_FRAME_Friend::ID_BUTTON_DelFriendOnButtonClick( ControlObject* pSender )
// {
// }

//****************
bool CUI_ID_FRAME_Friend::sendReqDelGroup( const char bPressYesButton, void *pData )
{
	if (s_CUI_ID_FRAME_Friend.showTpye == eSTP_HaveRelation && bPressYesButton == 1 )
	{
		ControlList::S_List* pItem = s_CUI_ID_FRAME_Friend.m_pID_LIST_FriendInfo->GetCurSelItem();
		if (pItem && pItem->m_nHiberarchy == 0)
		{
			MsgRelationGroupChangeNameReq Req;
			Req.uchGroupID = pItem->m_nID;
			Req.szGroup[0] = '\0';
			GettheNetworkInput().SendMsg( &Req );
			return true;
		}
	}
	return false;
}


bool CUI_ID_FRAME_Friend::sendReqDelFriend( const char bPressYesButton, void *pData )
{
	guardfunc;

	if( bPressYesButton )
	{
		const char* szName = s_CUI_ID_FRAME_Friend.getDelName();
		if( NULL == szName )
			return false;

		MsgDeleteRelationReq msg;
		int nId = thePlayerRole.GetdbID( szName );
		if(nId)
			msg.nPlayerID = nId;
		if (s_CUI_ID_FRAME_Friend.showTpye == eSTP_HaveRelation)
		{
			msg.stRelation = RelationDefine::Friend;
		}
		else if (s_CUI_ID_FRAME_Friend.showTpye == eSTP_BlackList)
		{
			msg.stRelation = RelationDefine::BlackList;
		}
		else if (s_CUI_ID_FRAME_Friend.showTpye == eSTP_TempFriend)
		{
			msg.stRelation = RelationDefine::TempFriend;
		}
		else if(s_CUI_ID_FRAME_Friend.showTpye == eSTP_VendettaList)
		{
			msg.stRelation = RelationDefine::Vendetta;
		}
		GettheNetworkInput().SendMsg( &msg );
	}
	return true;
	unguard;
}
//zjj add*******************************************8

bool CUI_ID_FRAME_Friend::sendReqMoveBlackList(const char bPressYesButton, void *pData)
{
	guardfunc;

	//s_CUI_ID_FRAME_AddFriend.sendMsgAddFriend( addFrdName.c_str(), eSTP_BlackList );
	if( !s_CUI_ID_FRAME_Friend.GetFrame() )
		return false;

	if( bPressYesButton )
	{
		ControlList::S_List* pItem = s_CUI_ID_FRAME_Friend.m_pID_LIST_FriendInfo->GetCurSelItem();
		if (pItem && pItem->m_pData)
		{
			RelationDataToClient* pRelationData = (RelationDataToClient*)pItem->m_pData;
			s_CUI_ID_FRAME_AddFriend.sendMsgAddFriend(pRelationData->GetName(), RelationDefine::BlackList,-1 );	
		}
			
	}
	return true;
	unguard;

}
// Button
bool CUI_ID_FRAME_Friend::ID_BUTTON_AddingOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Friend )
		return false;
	if (showTpye == eSTP_HaveRelation)
	{
		s_CUI_ID_FRAME_Rename.SetType(CUI_ID_FRAME_Rename::eAddFriendGroup);
		s_CUI_ID_FRAME_Rename.SetVisable(true);

	}
	return true;
}
// Button
bool CUI_ID_FRAME_Friend::ID_BUTTON_AddingFriendOnButtonClick( ControlObject* pSender )
{
/*
	if ( !m_pID_FRAME_Friend )
		return false;
// 	assert(showTpye == eSTP_TempFriend);
// 	ControlList::S_List* pItem = m_pID_LIST_FriendInfo->GetCurSelItem();
// 	if (pItem && pItem->m_pData)
// 	{
// 		RelationDataToClient* pRelationData = (RelationDataToClient*)pItem->m_pData;
// 		s_CUI_ID_FRAME_AddFriend.SetPrivateName(pRelationData->GetName());
// 		s_CUI_ID_FRAME_AddFriend.SetFrameType(CUI_ID_FRAME_AddFriend::eFrameType_AddFriendFromRMenu);
// 		s_CUI_ID_FRAME_AddFriend.SetVisable(TRUE);
// 	}

	if (showTpye == eSTP_HaveRelation)
	{
		s_CUI_ID_FRAME_Rename.SetType(CUI_ID_FRAME_Rename::eAddFriendGroup);
		s_CUI_ID_FRAME_Rename.SetVisable(true);

	}
*/

	if(!m_pID_FRAME_Friend)
	{
		assert(false&&"ui error");
		return false;
	}
	if(!s_CUI_ID_FRAME_AddFriend.IsVisable())
	{
		assert (showTpye == eSTP_HaveRelation);
		{
			s_CUI_ID_FRAME_AddFriend.SetFrameType( CUI_ID_FRAME_AddFriend::eFrameType_AddFriend );
			s_CUI_ID_FRAME_AddFriend.SetVisable(TRUE);
		}
	}

	return true;
}
// Button
bool CUI_ID_FRAME_Friend::ID_BUTTON_RenameOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Friend )
		return false;
	if (showTpye == eSTP_HaveRelation)
	{
		ControlList::S_List *pItem =  s_CUI_ID_FRAME_Friend.m_pID_LIST_FriendInfo->GetCurSelItem();
		if(pItem && pItem->m_nHiberarchy != 0)
		{
			return false;
		}
		s_CUI_ID_FRAME_Rename.SetType(CUI_ID_FRAME_Rename::eChangeFriendGroup);
		s_CUI_ID_FRAME_Rename.SetVisable(true);

	}
	return true;
}

// Button
bool CUI_ID_FRAME_Friend::ID_BUTTON_MoodOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Friend )
		return false;
	//s_CUI_ID_FRAME_Rename.SetType(CUI_ID_FRAME_Rename::eChangeSignature);
	//s_CUI_ID_FRAME_Rename.SetVisable(true);

	s_CUI_ID_FRAME_Editor.SetVisable(true);

	return true;
}

// Button
bool CUI_ID_FRAME_Friend::ID_BUTTON_AddingClassOnButtonClick( ControlObject* pSender )
{
	ID_BUTTON_AddingOnButtonClick(NULL);

	return true;
}


// 装载UI
bool CUI_ID_FRAME_Friend::_LoadUI()
{
	guardfunc;
	s_CUI_ID_FRAME_Master.LoadUI();

	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\FriendDlg.meui", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\FriendDlg.UI]失败")
			return false;
	}
// 	else if ( dwResult != 14998/*文件版本号*/ )
// 	{
// 		MESSAGE_BOX("读取文件[Data\\UI\\FriendDlg.UI]与源代码版本不一样")
// 	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_Friend::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_Friend, s_CUI_ID_FRAME_FriendOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Friend, s_CUI_ID_FRAME_FriendOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_Friend, ID_LIST_FriendInfo, s_CUI_ID_FRAME_FriendID_LIST_FriendInfoOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_Friend, ID_BUTTON_AddFriend, s_CUI_ID_FRAME_FriendID_BUTTON_AddFriendOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_Friend, ID_BUTTON_DelFriend, s_CUI_ID_FRAME_FriendID_BUTTON_DelFriendOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_Friend, ID_BUTTON_chat, s_CUI_ID_FRAME_FriendID_BUTTON_chatOnButtonClick);
 	theUiManager.OnButtonClick( ID_FRAME_Friend, ID_BUTTON_Addheimingdan, s_CUI_ID_FRAME_FriendID_BUTTON_AddheimingdanOnButtonClick);//zjj add[2008.6.15]
	theUiManager.OnCheckBoxCheck( ID_FRAME_Friend, ID_CHECKBOX_LinShiHaoYou, s_CUI_ID_FRAME_FriendID_CHECKBOX_LinShiHaoYouOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_Friend, ID_BUTTON_Search, s_CUI_ID_FRAME_FriendID_BUTTON_SearchOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Friend, ID_BUTTON_Adding, s_CUI_ID_FRAME_FriendID_BUTTON_AddingOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Friend, ID_BUTTON_AddingFriend, s_CUI_ID_FRAME_FriendID_BUTTON_AddingFriendOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Friend, ID_BUTTON_Rename, s_CUI_ID_FRAME_FriendID_BUTTON_RenameOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Friend, ID_BUTTON_Mood, s_CUI_ID_FRAME_FriendID_BUTTON_MoodOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Friend, ID_BUTTON_AddingClass, s_CUI_ID_FRAME_FriendID_BUTTON_AddingClassOnButtonClick );
	
	m_pID_FRAME_Friend = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Friend );
	
// 	m_pID_LIST_Youhaodu = (ControlList*)theUiManager.FindControl( ID_FRAME_Friend, ID_LIST_Youhaodu );
 	
	m_pID_BUTTON_AddFriend = (ControlButton*)theUiManager.FindControl( ID_FRAME_Friend, ID_BUTTON_AddFriend );
// 	m_pID_BUTTON_DelFriend = (ControlButton*)theUiManager.FindControl( ID_FRAME_Friend, ID_BUTTON_DelFriend );
// 	_pSendInfo = (ControlButton*)theUiManager.FindControl( ID_FRAME_Friend, ID_BUTTON_chat);
// 	_pRequestTeam = (ControlButton*)theUiManager.FindControl( ID_FRAME_Friend, ID_BUTTON_team);
// 	_pMoveHei = (ControlButton*)theUiManager.FindControl( ID_FRAME_Friend, ID_BUTTON_MoveHei);
	// 	m_pID_LIST_GuanXi = (ControlList*)theUiManager.FindControl( ID_FRAME_Friend, ID_LIST_GuanXi );

	m_pID_CHECKBOX_LinShiHaoYou = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Friend, ID_CHECKBOX_LinShiHaoYou );
	_pCheckFriend = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Friend, ID_CHECKBOX_HaoYou );
	_pCheckBlackList = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Friend, ID_CHECKBOX_HeiMingDan );
// 	_pCheckTeachers = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Friend, ID_CHECKBOX_ShiTu );
	_pCheckChouren = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Friend, ID_CHECKBOX_Chouren);//zjj[7.2]

	m_pID_BUTTON_Adding = (ControlButton*)theUiManager.FindControl( ID_FRAME_Friend, ID_BUTTON_Adding );
	m_pID_BUTTON_Rename = (ControlButton*)theUiManager.FindControl( ID_FRAME_Friend, ID_BUTTON_Rename );
	m_pID_BUTTON_Addheimingdan = (ControlButton*)theUiManager.FindControl( ID_FRAME_Friend, ID_BUTTON_Addheimingdan );
	m_pID_BUTTON_AddingFriend = (ControlButton*)theUiManager.FindControl( ID_FRAME_Friend, ID_BUTTON_AddingFriend );
	m_pID_BUTTON_Search = (ControlButton*)theUiManager.FindControl( ID_FRAME_Friend, ID_BUTTON_Search );
	m_pID_BUTTON_Mood = (ControlButton*)theUiManager.FindControl( ID_FRAME_Friend, ID_BUTTON_Mood );
	m_pID_BUTTON_Remove = (ControlButton*)theUiManager.FindControl( ID_FRAME_Friend, ID_BUTTON_Remove );

	m_pID_PICTURE_Head = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Friend, ID_PICTURE_Head );
	m_pID_TEXT_PeopleName = (ControlText*)theUiManager.FindControl( ID_FRAME_Friend, ID_TEXT_PeopleName );
	m_pID_TEXT_PeopleMood = (ControlText*)theUiManager.FindControl( ID_FRAME_Friend, ID_TEXT_PeopleMood );

	m_pID_LIST_FriendInfo = (ControlList*)theUiManager.FindControl( ID_FRAME_Friend, ID_LIST_FriendInfo );
	m_pID_LIST_FriendHead = (ControlList*)theUiManager.FindControl( ID_FRAME_Friend, ID_LIST_FriendHead );
	m_pID_LIST_FriendStar = (ControlList*)theUiManager.FindControl( ID_FRAME_Friend, ID_LIST_FriendStar );

	m_pID_TEXT_CloseIconID = (ControlText*)theUiManager.FindControl( ID_FRAME_Friend, ID_TEXT_CloseIconID );
	m_pID_TEXT_OpenIconID = (ControlText*)theUiManager.FindControl( ID_FRAME_Friend, ID_TEXT_OpenIconID );

	m_pID_TEXT_Wait = (ControlText*)theUiManager.FindControl( ID_FRAME_Friend, ID_TEXT_Wait );
	m_pID_BUTTON_AddingClass = (ControlButton*)theUiManager.FindControl( ID_FRAME_Friend, ID_BUTTON_AddingClass );

// 	assert(_pSendInfo);
// 	assert(_pRequestTeam);
// 	assert( _pMoveHei );
// 	assert( _pCheckFriend );
// 	assert( _pCheckBlackList );
// 	assert( _pCheckTeachers );
// 	assert(_pCheckChouren);
// 	assert( m_pID_FRAME_Friend );
// 	assert( m_pID_LIST_FriendInfo );
// 	assert( m_pID_BUTTON_AddFriend );
// 	assert( m_pID_BUTTON_DelFriend );
// 	assert( m_pID_BUTTON_Remove );
// 	assert( m_pID_CHECKBOX_LinShiHaoYou );
// 	assert( m_pID_TEXT_Wait );

	assert( m_pID_BUTTON_Adding );
	assert( m_pID_BUTTON_AddingFriend );
	assert( m_pID_BUTTON_Rename );
	assert(m_pID_BUTTON_Addheimingdan);
	assert(m_pID_BUTTON_Search);
	assert(m_pID_BUTTON_Mood);
	assert(m_pID_BUTTON_Remove);

	assert( m_pID_PICTURE_Head );
	assert( m_pID_TEXT_PeopleName );
	assert( m_pID_TEXT_PeopleMood );

	assert(m_pID_LIST_FriendHead);
	assert(m_pID_LIST_FriendInfo);
	assert(m_pID_LIST_FriendStar);

	assert( m_pID_TEXT_CloseIconID );
	assert( m_pID_TEXT_OpenIconID );

// 	_pRequestTeam->SetButtonClickFun(ID_BUTTON_teamOnButtonClick);
// 	_pMoveHei->SetButtonClickFun(ID_BUTTON_moveHeiOnButtonClick);
	_pCheckFriend->SetCheckFun(ID_CheckBox_Friend);
	_pCheckFriend->SetCheck(true);
 	_pCheckBlackList->SetCheckFun(ID_CheckBox_Blacklist);
// 	_pCheckTeachers->SetCheckFun(ID_CheckBox_Teachers);
 	_pCheckChouren->SetCheckFun(ID_CheckBox_Chouren);

	m_pID_BUTTON_Remove->SetButtonClickFun(ID_BUTTON_RemoveOnButtonClick);

	if(m_pID_LIST_FriendInfo)
	{
		m_pID_LIST_FriendInfo->setShowTip();
		m_pID_LIST_FriendInfo->SetRBSelectEnable();
		m_pID_LIST_FriendInfo->SetRBClickFun( ID_List_OnRBClick );
		m_pID_LIST_FriendInfo->SetLDBClickFun( ID_List_OnLDBClick );
		m_pID_LIST_FriendInfo->SetOnCollapseFun( Friend_CollapseCallBackFun );
		m_pID_LIST_FriendInfo->SetOnlyLeafCanBeSelected(false);
		m_pID_LIST_FriendInfo->SetOnShowTipFun(Friend_ShowTipCallBackFun);
		m_pID_LIST_FriendStar->SetMsgHoldup(false);	//不接受消息
		m_pID_LIST_FriendStar->HaveSelBar( false );	//没有绿色cur选中地图
		m_pID_LIST_FriendStar->SetCurSelIndex(-1);
	}




	// 添加到控件组，方便管理
//	m_FriendCtrlGroup.AddControl( m_pID_BUTTON_AddFriend );
// 	m_FriendCtrlGroup.AddControl( m_pID_BUTTON_AddingFriend);
// 	m_FriendCtrlGroup.AddControl( m_pID_BUTTON_Mood);
// 	m_FriendCtrlGroup.AddControl(m_pID_BUTTON_Addheimingdan);
// 	m_FriendCtrlGroup.AddControl( m_pID_BUTTON_Search );
// // 	m_FriendCtrlGroup.AddControl( _pRequestTeam );
// 	m_FriendCtrlGroup.AddControl( _pSendInfo );
//  	m_FriendCtrlGroup.AddControl( m_pID_BUTTON_Remove );
// 	m_FriendCtrlGroup.AddControl(m_pID_BUTTON_Adding);
//	m_FriendCtrlGroup.AddControl(m_pID_BUTTON_Rename);
// 	m_FriendCtrlGroup.AddControl( _pMoveHei );

// 	m_EnemyCtrlGroup.AddControl( m_pID_BUTTON_Remove );
// // 	m_EnemyCtrlGroup.AddControl( _pMoveHei );
// 	m_EnemyCtrlGroup.AddControl( m_pID_BUTTON_Search );

// 	m_BlackListCtrlGroup.AddControl( m_pID_BUTTON_Remove );
//  	m_BlackListCtrlGroup.AddControl( m_pID_BUTTON_Addheimingdan );
// 	m_BlackListCtrlGroup.AddControl( m_pID_BUTTON_Search );
// 
// 	m_TempFriendCtrlGroup.AddControl( m_pID_BUTTON_AddingFriend );
// // 	m_TempFriendCtrlGroup.AddControl( _pRequestTeam );
// 	m_TempFriendCtrlGroup.AddControl( m_pID_BUTTON_Search );
//  	m_TempFriendCtrlGroup.AddControl( m_pID_BUTTON_Remove );
// // 	m_TempFriendCtrlGroup.AddControl( _pMoveHei );

	m_CtrlTabGroup.AddPage( _pCheckFriend, &m_FriendCtrlGroup );
	//m_CtrlTabGroup.AddPage( _pCheckTeachers, &m_MasterCtrlGroup );
	m_CtrlTabGroup.AddPage( _pCheckChouren, &m_EnemyCtrlGroup );
	m_CtrlTabGroup.AddPage( _pCheckBlackList, &m_BlackListCtrlGroup );
	m_CtrlTabGroup.AddPage( m_pID_CHECKBOX_LinShiHaoYou, &m_TempFriendCtrlGroup );
	m_CtrlTabGroup.TogglePage( _pCheckFriend );

	if(m_pID_BUTTON_Mood)
	{
		m_pID_BUTTON_Mood->setTip(theXmlString.GetString(eText_Button_Tip_Mood));
		m_pID_BUTTON_Mood->SetShowTip();
	}
	if(m_pID_BUTTON_Addheimingdan)
	{
		m_pID_BUTTON_Addheimingdan->setTip(theXmlString.GetString(eText_Button_Tip_AddHeimingdan));
		m_pID_BUTTON_Addheimingdan->SetShowTip();
	}
	if(m_pID_BUTTON_Remove)
	{
		m_pID_BUTTON_Remove->setTip(theXmlString.GetString(eText_Button_Tip_RemoveFriend));
		m_pID_BUTTON_Remove->SetShowTip();
	}
	if(m_pID_BUTTON_AddingFriend)
	{
		m_pID_BUTTON_AddingFriend->setTip(theXmlString.GetString(eText_Button_Tip_AddFriend));
		m_pID_BUTTON_AddingFriend->SetShowTip();
	}
	if(m_pID_BUTTON_Search)
	{
		m_pID_BUTTON_Search->setTip(theXmlString.GetString(eText_Button_Tip_Search));
		m_pID_BUTTON_Search->SetShowTip();
	}
	if(m_pID_BUTTON_AddingClass)
	{
		m_pID_BUTTON_AddingClass->setTip(theXmlString.GetString(eText_Button_Tip_AddClass));
		m_pID_BUTTON_AddingClass->SetShowTip();
	}

	
	

// 	m_pID_LIST_FriendInfo->GetScrollBar()->SetUpdatePosFun((UpdateScrollBar));

// 	if( s_CUI_ID_FRAME_Master.GetFrame() )
// 		s_CUI_ID_FRAME_Master.GetFrame()->SetFather(m_pID_FRAME_Friend);
	s_CUI_ID_FRAME_Master.SetVisable(false);

	m_bNeedRefresh = true;
	m_pID_FRAME_Friend->SetVisable(false);
	return true;
	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_Friend::_UnLoadUI()
{
	guardfunc;
	s_CUI_ID_FRAME_Master.UnLoadUI();

	m_CtrlTabGroup.Clear();
	m_FriendCtrlGroup.Clear();
	m_MasterCtrlGroup.Clear();
	m_EnemyCtrlGroup.Clear();
	m_BlackListCtrlGroup.Clear();

	//RequestedPeople.clear();
	//m_mapFriendInfo.clear();
	//RequestedPeople.clear();
	m_pID_FRAME_Friend = NULL;
	m_pID_LIST_FriendInfo = NULL;
	m_pID_BUTTON_AddFriend = NULL;
// 	m_pID_BUTTON_DelFriend = NULL;
	m_pID_BUTTON_Remove = NULL;
 	m_pID_BUTTON_Addheimingdan = 0;
// 	_pMoveHei = NULL;
// 	_pRequestTeam = NULL;
	_pCheckFriend = NULL;	//好友列表
	_pCheckBlackList = NULL;	//黑名单列表
	_pCheckTeachers = NULL;	//师徒列表
	//_pCheckBrother = NULL;		//兄弟列表
	_pCheckChouren=NULL;//结婚
	m_pID_CHECKBOX_LinShiHaoYou = NULL;
	m_pID_BUTTON_Search = NULL;
	m_pID_TEXT_PeopleMood = NULL;

	m_pID_LIST_FriendHead = NULL;

	m_pID_TEXT_CloseIconID = NULL;
	m_pID_TEXT_OpenIconID = NULL;

	m_pID_TEXT_Wait = NULL;
	return theUiManager.RemoveFrame( "data\\ui\\FriendDlg.meui" );
	unguard;
}

// 是否可视
bool CUI_ID_FRAME_Friend::_IsVisable()
{
	guardfunc;
	if( m_pID_FRAME_Friend )
		return m_pID_FRAME_Friend->IsVisable();
	return false;
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_Friend::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pID_FRAME_Friend )
		return;
	m_pID_FRAME_Friend->SetVisable( bVisable );
	if( bVisable )
	{
		sendUpdataFrdInfo();
		_beginForSendMsgUpdateInfo = clock();
		Refresh();
	}
	else
	{
		// 关闭好友界面时，右键菜单也要隐藏
		s_CUI_ID_FRAME_FriendDlgRight.SetVisable(false);
		_beginForSendMsgUpdateInfo = 0;
	}

	if (bVisable)
	{
		s_CUI_ID_FRAME_MainMenu.SetNeedSpark(false, CUI_ID_FRAME_MainMenu::ekey_friend);
	}
	unguard;
}


void CUI_ID_FRAME_Friend::sendUpdataFrdInfo()
{
	guardfunc;

	if( !IsVisable() )
		return;

// 	m_bWaitingServerUpdate = true;

	MsgUpdateRelationReq msg;
	GettheNetworkInput().SendMsg(&msg);

	unguard;
}

void CUI_ID_FRAME_Friend::RefreshUI()
{
	if( m_pID_FRAME_Friend == NULL )
		return;

// 	_pRequestTeam->SetVisable( false );
// 		if( m_FriendCtrlGroup.IsVisible() /*|| m_MasterCtrlGroup.IsVisible()*/ || m_TempFriendCtrlGroup.IsVisible())
// 			_pRequestTeam->SetVisable( true );
}

void CUI_ID_FRAME_Friend::Refresh()
{
	guardfunc;
	if( !IsVisable() )
		return;

	s_CUI_ID_FRAME_FriendDlgRight.SetVisable(false);
	s_CUI_ID_FRAME_RBTNMENU.SetVisable(false);
	m_pID_TEXT_Wait->SetVisable(false);
	// 默认显示好友列表，隐藏师徒界面
	m_pID_LIST_FriendInfo->SetVisable(true);
	s_CUI_ID_FRAME_Master.SetVisable(false);
	m_pID_TEXT_PeopleName->SetText(thePlayerRole.GetName());
	m_pID_TEXT_PeopleMood->SetText(thePlayerRole.GetSignature());
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (pMe)
	{
		std::string portraitName = s_CUI_ID_FRAME_CREATE.GetPortraitName( pMe->GetSex(), pMe->GetPortraitId() );
		portraitName = "Data\\Ui\\" + portraitName;
		m_pID_PICTURE_Head->SetPicName( portraitName.c_str() );
	}

	switch( showTpye )
	{
	case eSTP_HaveRelation:	//说明list显示的是好友列表
		{
			showFriendList();
		}
		break;
	case eSTP_TempFriend:	//说明list显示的是好友列表
		{
			showTempFriendList();
		}
		break;
	case eSTP_Brother:	//说明list显示的是兄弟列表
		{
			showBrotherList();
		}
		break;
	case eSTP_Teacher:	//说明list显示的是师徒列表
		{
			showTeacherList();
		}
		break;
	case eSTP_BlackList:	//说明list显示的是黑名单列表
		{
			showBlackList();
		}
		break;
	case eSTP_Marriage:
		{
			showMarriageList();
		}
	case eSTP_VendettaList:
		{
			showChourenList();
		}
	}

	RefreshButtonStatus();

	unguard;
}

bool FriendlyCompare( RelationDataToClient*& a, RelationDataToClient*& b )
{
	return a->GetFriendly() > b->GetFriendly();
}

void CUI_ID_FRAME_Friend::showFriendList()
{
	if(NULL == m_pID_LIST_FriendInfo || NULL == m_pID_LIST_FriendHead || NULL == m_pID_LIST_FriendStar)
		return;

	guardfunc;
	if( !m_pID_FRAME_Friend )
		return;

	vector<RelationDataToClient*> vecFriendInfo;

	m_CtrlTabGroup.TogglePage( _pCheckFriend );

	m_pID_LIST_FriendInfo->BeginUpdate();
	m_pID_LIST_FriendInfo->Clear();
	m_pID_LIST_FriendHead->Clear();
 	m_pID_LIST_FriendStar->Clear();
// 	m_pID_LIST_GuanXi->Clear();
	m_pID_LIST_FriendInfo->SetCurSelIndex(-1);
// 	m_pID_LIST_GuanXi->SetCurSelIndex(-1);
	m_pID_LIST_FriendInfo->GetScrollBar()->SetValue(0);

	//定制的controllist的收起展开图标ID
	const char *pCloseIconID = NULL;
	if(m_pID_TEXT_CloseIconID != NULL)
	{
		pCloseIconID = m_pID_TEXT_CloseIconID->GetText();
	}
	const char *pOpenIconID = NULL;
	if(m_pID_TEXT_OpenIconID != NULL)
	{
		pOpenIconID = m_pID_TEXT_OpenIconID->GetText();
	}

	//std::map<int, RelationDataToClient>::iterator iter;
	ControlList::S_List	stItem;
	int i=0;
	int headWidth = 0;
	if(m_pID_LIST_FriendHead)
		headWidth = m_pID_LIST_FriendHead->GetWidth();

	for (int nGroup = 0; nGroup < RelationDefine::GroupCount;++nGroup)
	{
		std::map<int, RelationDataToClient>::iterator itermap = thePlayerRole.GetMapFriendInfo().begin();
		RelationGroup& group = thePlayerRole.GetFrdGroup(nGroup);
		if (group.IsEmpty())
		{
			continue;
		}
		stItem.clear();
		stItem.m_nHiberarchy = 0;
		stItem.m_bCollapse = false;
		stItem.SetData(group.GetName(),nGroup);
		ControlList::S_List* pGroupItem = m_pID_LIST_FriendInfo->AddItem( &stItem,NULL, false);
		int nOnlineCount = 0;

		//在默认的好友组里增加一个默认的朋友信息（小精灵）
		{
			//if(0 == nGroup)
			//{
			//	//构造小精灵数据
			//	static RelationDataToClient friendData;
			//	friendData.SetID(SpriteFriendID);
			//	std::string multLine = theXmlString.GetString(eText_friend_sprite_name);
			//	//multLine += "\n多行";
			//	friendData.SetName(multLine.c_str());
			//	friendData.SetHeadPic(1);
			//	friendData.SetSex(Sex_Male);
			//	friendData.SetOnLine(true);
			//	friendData.SetSignature(theXmlString.GetString(eText_friend_sprite_content));
			//	friendData.SetGroupID(0);

			//	stItem.clear();
			//	//stItem.SetMargin(headWidth);
			//	//SetTipForFriend(&friendData, stItem);
			//	stItem.m_nHiberarchy = 1;
			//	AddToList(&friendData, stItem, Color_Config.getColor(CC_FRIEND_ONLINE));
			//	++nOnlineCount;
			//}
		}

		vecFriendInfo.clear();
		for(; itermap != thePlayerRole.GetMapFriendInfo().end(); ++itermap)
		{
			RelationDataToClient *pFriendData = &itermap->second;
			if (pFriendData->GetGroupID() ==  nGroup &&  (pFriendData->HaveRelation(RelationDefine::Friend)))
			{
				vecFriendInfo.push_back(pFriendData);
			}
		}
		std::sort(vecFriendInfo.begin(), vecFriendInfo.end(), FriendlyCompare);

		std::vector<RelationDataToClient*>::iterator iter = vecFriendInfo.begin();
		
		for(iter = vecFriendInfo.begin(); iter != vecFriendInfo.end(); ++iter)
		{
			stItem.clear();
			//stItem.SetMargin(headWidth);

			RelationDataToClient *pFriendData = (*iter);
			if( pFriendData->GetOnLine() )
			{
				//SetTipForFriend(pFriendData,stItem);
				stItem.m_nHiberarchy = 1;
				AddToList(pFriendData,stItem,Color_Config.getColor(CC_FRIEND_ONLINE));
				++nOnlineCount;
			}
		}
		for( iter = vecFriendInfo.begin(); iter != vecFriendInfo.end(); ++iter )
		{
			stItem.clear();
			//stItem.SetMargin(headWidth);

			RelationDataToClient *pFriendData = (*iter);
			if(!pFriendData->GetOnLine())
			{
				SetTipForFriend(pFriendData,stItem);
				stItem.m_nHiberarchy = 1;
				AddToList(pFriendData,stItem,Color_Config.getColor(CC_FRIEND_OFFLINE));
			}
		}
		char cTemp[128] = {0};

		//if(0 == nGroup) //默认组+1 为了保存在线gm
		//MeSprintf_s(cTemp,128,"%s(%d/%d)",group.GetName(),nOnlineCount,vecFriendInfo.size() + 1);
		//else
        MeSprintf_s(cTemp,128,"%s(%d/%d)",group.GetName(),nOnlineCount,vecFriendInfo.size());

		strncpy( pGroupItem->m_szText, cTemp, sizeof(pGroupItem->m_szText) - 1 );
		m_pID_LIST_FriendInfo->ParseText(pGroupItem,NULL);
		
	}

	m_pID_LIST_FriendInfo->EndUpdate();

	RefreshFriendStar();

	unguard;
}

void CUI_ID_FRAME_Friend::showTempFriendList()
{
	guardfunc;
	if( !m_pID_FRAME_Friend )
		return;

	m_CtrlTabGroup.TogglePage( m_pID_CHECKBOX_LinShiHaoYou );

	m_pID_LIST_FriendInfo->Clear();
	m_pID_LIST_FriendStar->Clear();
	if(m_pID_LIST_FriendHead)
		m_pID_LIST_FriendHead->Clear();

	m_pID_LIST_FriendInfo->SetCurSelIndex(-1);

	std::map<int, RelationDataToClient>::iterator iter;
	ControlList::S_List	stItem;




	for(iter = thePlayerRole.GetMapFriendInfo().begin(); iter != thePlayerRole.GetMapFriendInfo().end(); ++iter)
	{
		stItem.clear();
		if( /*iter->second.GetOnline() &&  */( iter->second.HaveRelation(RelationDefine::TempFriend)) )
		{
			RelationDataToClient &friendData = iter->second;
			SetTipForOther(&friendData,stItem);

			DWORD dwColor = 0xffffffff;

			if(friendData.GetOnLine())
			    dwColor = Color_Config.getColor(CC_FRIEND_ONLINE);
			else
			    dwColor = Color_Config.getColor(CC_FRIEND_OFFLINE);

			//名字
			AddToList(&friendData,stItem,dwColor);
		}
	}

// 	m_pID_LIST_FriendStar->SetVisable(false);
// 	m_pID_LIST_Youhaodu->SetVisable(false);

	RefreshFriendStar();

	unguard;

}


void CUI_ID_FRAME_Friend::showBrotherList() 
{
	guardfunc;
	m_pID_LIST_FriendInfo->Clear();
	m_pID_LIST_FriendStar->Clear();
	m_pID_LIST_FriendInfo->SetCurSelIndex(-1);

	std::map<int, RelationDataToClient>::iterator iter;
	ControlList::S_List	stItem;

	for(iter = thePlayerRole.GetMapFriendInfo().begin(); iter != thePlayerRole.GetMapFriendInfo().end(); ++iter)
	{
		if( iter->second.GetOnLine() && (iter->second.HaveRelation(RelationDefine::Brother)))
		{
			RelationDataToClient &friendData = iter->second;
			SetTipForOther(&friendData,stItem);

			AddToList(&friendData,stItem,Color_Config.GetPkNameColor(PKMode_Fight/*iter->second.GetPKMode() */));
		}
	}
	for( iter = thePlayerRole.GetMapFriendInfo().begin(); iter != thePlayerRole.GetMapFriendInfo().end(); ++iter )
	{
//sbw_modify_binaryflag			if( !iter->second.GetOnline() && iter->second._eSType == eSTP_Brother )
		if( !iter->second.GetOnLine() && (iter->second.HaveRelation(RelationDefine::Brother)))
		{
            RelationDataToClient &friendData = iter->second;
			SetTipForOther(&friendData,stItem);

			AddToList(&friendData,stItem,Color_Config.getColor(CC_FRIEND_OFFLINE));
		}
	}
 	m_pID_LIST_FriendStar->SetVisable(false);
// 	m_pID_LIST_Youhaodu->SetVisable(false);
	unguard;
}
void CUI_ID_FRAME_Friend::showTeacherList() 
{
	guardfunc;
	m_CtrlTabGroup.TogglePage( _pCheckTeachers );
	//m_pID_LIST_FriendInfo->Clear();
	//m_pID_LIST_FriendInfo->SetCurSelIndex(-1);
	m_pID_LIST_FriendInfo->SetVisable(false);

	s_CUI_ID_FRAME_Master.SetVisable(true);
	unguard;
}
void CUI_ID_FRAME_Friend::showBlackList() 
{
	guardfunc;
	m_CtrlTabGroup.TogglePage( _pCheckBlackList );
	m_pID_LIST_FriendInfo->Clear();
	m_pID_LIST_FriendStar->Clear();
	if(m_pID_LIST_FriendHead)
		m_pID_LIST_FriendHead->Clear();

	m_pID_LIST_FriendInfo->SetCurSelIndex(-1);

	std::map<int, RelationDataToClient>::iterator iter;
	ControlList::S_List	stItem;


	for( iter = thePlayerRole.GetMapFriendInfo().begin(); iter != thePlayerRole.GetMapFriendInfo().end(); ++iter)
	{

		if( iter->second.GetOnLine() && (iter->second.HaveRelation(RelationDefine::BlackList)))
		{
			RelationDataToClient &friendData = iter->second;
			SetTipForOther(&friendData,stItem);

			AddToList(&friendData,stItem,Color_Config.GetPkNameColor(PKMode_Fight/*iter->second.GetPKMode() */));

		}
	}
	
	for( iter = thePlayerRole.GetMapFriendInfo().begin(); iter != thePlayerRole.GetMapFriendInfo().end(); ++iter )
	{
		if( !iter->second.GetOnLine() && (iter->second.HaveRelation(RelationDefine::BlackList)))
		{
            RelationDataToClient &friendData = iter->second;
			SetTipForOther(&friendData,stItem);

			AddToList(&friendData,stItem,Color_Config.getColor(CC_FRIEND_OFFLINE));
		}
	}
// 	m_pID_LIST_FriendStar->SetVisable(false);
// 	m_pID_LIST_Youhaodu->SetVisable(false);
	RefreshFriendStar();

	unguard;
}
//zjj add[7.2]
void CUI_ID_FRAME_Friend::showMarriageList()
{
	m_CtrlTabGroup.TogglePage( _pCheckChouren );
	m_pID_LIST_FriendInfo->Clear();
	m_pID_LIST_FriendStar->Clear();
	m_pID_LIST_FriendInfo->SetCurSelIndex(-1);
	std::map<int, RelationDataToClient>::iterator iter;
	ControlList::S_List	stItem;

	for(iter = thePlayerRole.GetMapFriendInfo().begin(); iter != thePlayerRole.GetMapFriendInfo().end(); ++iter)
	{
		if( iter->second.GetOnLine() && (iter->second.HaveRelation(RelationDefine::Marriage)))
		{
			RelationDataToClient &friendData = iter->second;
			SetTipForOther(&friendData,stItem);

			AddToList(&friendData,stItem,Color_Config.GetPkNameColor(PKMode_Fight/*iter->second.GetPKMode() */));
		}
	}
	for( iter = thePlayerRole.GetMapFriendInfo().begin(); iter != thePlayerRole.GetMapFriendInfo().end(); ++iter )
	{
		//sbw_modify_binaryflag 	if( !iter->second.GetOnline() && (iter->second._eSType == eSTP_Teacher || iter->second._eSType == eSTP_Student) )
		if( !iter->second.GetOnLine() && (iter->second.HaveRelation(RelationDefine::Marriage)) )
		{
            RelationDataToClient &friendData = iter->second;
			SetTipForOther(&friendData,stItem);

			AddToList(&friendData,stItem,Color_Config.getColor(CC_FRIEND_OFFLINE));
		}
	}
}
void CUI_ID_FRAME_Friend::showChourenList()
{
	guardfunc;
	m_CtrlTabGroup.TogglePage( _pCheckChouren );
	m_pID_LIST_FriendInfo->Clear();
	m_pID_LIST_FriendStar->Clear();
	if(m_pID_LIST_FriendHead)
		m_pID_LIST_FriendHead->Clear();

	m_pID_LIST_FriendInfo->SetCurSelIndex(-1);
	std::map<int, RelationDataToClient>::iterator iter;
	ControlList::S_List	stItem;

	for(iter = thePlayerRole.GetMapFriendInfo().begin(); iter != thePlayerRole.GetMapFriendInfo().end(); ++iter)
	{
		//sbw_modify_binaryflag				if( iter->second.GetOnline() && (iter->second._eSType == eSTP_Teacher || iter->second._eSType == eSTP_Student) )
		if( iter->second.GetOnLine() && (iter->second.HaveRelation(RelationDefine::Vendetta)))
		{
			RelationDataToClient &friendData = iter->second;
			SetTipForOther(&friendData,stItem);

			AddToList(&friendData,stItem,Color_Config.GetPkNameColor(PKMode_Fight/*iter->second.GetPKMode() */));
		}
	}
	for( iter = thePlayerRole.GetMapFriendInfo().begin(); iter != thePlayerRole.GetMapFriendInfo().end(); ++iter )
	{
		//sbw_modify_binaryflag 	if( !iter->second.GetOnline() && (iter->second._eSType == eSTP_Teacher || iter->second._eSType == eSTP_Student) )
		if( !iter->second.GetOnLine() && (iter->second.HaveRelation(RelationDefine::Vendetta)) )
		{
            RelationDataToClient &friendData = iter->second;
			SetTipForOther(&friendData,stItem);

			AddToList(&friendData,stItem,Color_Config.getColor(CC_FRIEND_OFFLINE));
		}
	}

	RefreshFriendStar();

	unguard;
}

// bool CUI_ID_FRAME_Friend::ID_BUTTON_chatOnButtonClick( ControlObject* pSender )
// {
// 	guardfunc;
// 	if( m_pID_LIST_FriendInfo->GetCurSelItem() )
// 	{
// 		std::string strName = m_pID_LIST_FriendInfo->GetCurSelItem()->m_szText;
// 		if( thePlayerRole.IsOnline(strName.c_str()) )
// 		{
// 			if( strName.length() > 0 )
// 			{
// 				chatMessageManage.ShowChatMessageFrame(strName.c_str() );
// 			}
// 		}
// 	}
// 	return true;
// 	unguard;
// }
//
bool CUI_ID_FRAME_Friend::ID_BUTTON_moveHeiOnButtonClick( ControlObject* pSender )
{
	guardfunc;

	int nIndex = s_CUI_ID_FRAME_Friend.m_pID_LIST_FriendInfo->GetCurSelIndex();

	ControlList::S_List* pItem = s_CUI_ID_FRAME_Friend.m_pID_LIST_FriendInfo->GetCurSelItem();
	if( pItem && pItem->m_pData )
	{
		RelationDataToClient* pRelationData = (RelationDataToClient*)pItem->m_pData;
		s_CUI_ID_FRAME_Friend.setDelName( pRelationData->GetName());

		char szTemp[256] = { 0 };
		sprintf( szTemp, theXmlString.GetString(eMessageBox_ReqMoveBlackList), pRelationData->GetName() );
		s_CUI_ID_FRAME_MessageBox.Show( szTemp, "", CUI_ID_FRAME_MessageBox::eTypeYesNo,
			false, s_CUI_ID_FRAME_Friend.sendReqMoveBlackList);
	}

	return true;
	unguard;
}
bool CUI_ID_FRAME_Friend::ID_BUTTON_teamOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( s_CUI_ID_FRAME_Friend.m_pID_LIST_FriendInfo->GetCurSelItem() )
	{
		std::string strName = s_CUI_ID_FRAME_Friend.m_pID_LIST_FriendInfo->GetCurSelItem()->m_szText;

		std::string addFrdName = strName;//.substr(0, nOff);

		{

			CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
			if ( !pMe )
				return false;

			char szInfo[128] = {0};

			//s_CUI_ID_FRAME_Friend.pushRequestPeople( addFrdName.c_str() );
			//您向 发送组队申请
			MeSprintf_s( szInfo, sizeof(szInfo)/sizeof(char)-1, "%s ~%s_ %s", theXmlString.GetString(eUI_YouTo), addFrdName.c_str(), theXmlString.GetString(eUI_SendTeam));
			s_CUI_ChatInfoBox.AddInfo( szInfo, Color_Config.getColor( CC_CHAT_TEAM ) );

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
			strncpy(msg.szNewbieName, addFrdName.c_str(), sizeof(msg.szNewbieName)-1);
			GettheNetworkInput().SendMsg(&msg);
		}
	}
	else
	{

	}
	return true;
	unguard;
}

bool CUI_ID_FRAME_Friend::ID_BUTTON_RemoveOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	//删除好友 向serverGUI 发请求删除好友的消息
	ControlList::S_List *pItem =  s_CUI_ID_FRAME_Friend.m_pID_LIST_FriendInfo->GetCurSelItem();
	if (pItem)
	{
		if (s_CUI_ID_FRAME_Friend.showTpye == eSTP_HaveRelation && pItem->m_nHiberarchy == 0 )
		{
			if (pItem->m_nID == 0)
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs,theXmlString.GetString( eFriend_Error_DefaultGroup) );
			}
			else
			{
				char szTemp[128] = { 0 };
				sprintf( szTemp, theXmlString.GetString(eFriend_Warning_DeleteGroup)/*, pItem->m_szText*/);
				s_CUI_ID_FRAME_MessageBox.Show( szTemp, "", CUI_ID_FRAME_MessageBox::eTypeYesNo,
					false, s_CUI_ID_FRAME_Friend.sendReqDelGroup );
			}
		}
		else
		{
			if(pItem->m_pData)
			{
				RelationDataToClient* pRelationData = (RelationDataToClient*)pItem->m_pData;
				if(IsTheSprite(pRelationData))
				{
					//提示

					return false;
				}

				s_CUI_ID_FRAME_Friend.setDelName( pRelationData->GetName());
				char szTemp[128] = { 0 };
				sprintf( szTemp, theXmlString.GetString(eText_Client_IsDel_Friend), pRelationData->GetName());
				s_CUI_ID_FRAME_MessageBox.Show( szTemp, "", CUI_ID_FRAME_MessageBox::eTypeYesNo,
					false, s_CUI_ID_FRAME_Friend.sendReqDelFriend );
			}
		}
	}
	return true;
	unguard;
}

void CUI_ID_FRAME_Friend::ID_List_OnLDBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	{
		if (s_CUI_ID_FRAME_Friend.showTpye == eSTP_HaveRelation)
		{
			ControlList::S_List *pItem =  s_CUI_ID_FRAME_Friend.m_pID_LIST_FriendInfo->GetCurSelItem();
			if(pItem->m_nHiberarchy == 1 && pItem->m_pData)
			{
				RelationDataToClient* pRelationData = (RelationDataToClient*)pItem->m_pData;
				if(SpriteFriendID == pRelationData->GetID())
				{//lyh小精灵
					chatMessageManage.ShowChatMessageFrame(pRelationData->GetName() );
				}
				else
				{
					if (pRelationData->GetOnLine())
					{
						chatMessageManage.ShowChatMessageFrame(pRelationData->GetName() );
					}
				}
			}
		}
	}
	theUiManager.SetJumpNextLButtonUp(true);

}

//bool CUI_ID_FRAME_Friend::ID_BUTTON_PrivateOnButtonClick( ControlObject* pSender )
//{
//	guardfunc;
//	if( m_pID_LIST_FriendInfo->GetCurSelItem() )
//	{
//		std::string strName = m_pID_LIST_FriendInfo->GetCurSelItem()->m_szText;
//		if( strcmp(thePlayerRole.GetName(), strName.c_str()) == 0 )
//			return false;
//
//		s_CUI_ChatInfoBox.Begin2Secret( strName.c_str() );	
//	}
//	return true;
//	unguard;
//
//}

bool CUI_ID_FRAME_Friend::ID_BUTTON_SearchOnButtonClick(ControlObject* pSender)
{
	guardfunc
	s_CUI_ID_FRAME_Search.SetVisable(true);
	return true;
	unguard
}

void CUI_ID_FRAME_Friend::GetSexProfessionString( RelationDataToClient &friendData, std::string &strSex, string &strProfession )
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

const char* CUI_ID_FRAME_Friend::GetPortraitGif( RelationDataToClient *friendData )
{
	if ( friendData->HaveRelation(RelationDefine::TempFriend) ) //临时好友
	{
		if (s_CUI_ID_FRAME_MiniChat.IsRemindPlayer(friendData->GetName()))
		{
			return "{#MMMM1}";
		}
		else if (friendData->GetOnLine())
		{
			return "{#MMMM0}";
		}
		else
		{
			return "{#MMMM2}";
		}
	}

	if (friendData->GetSex() == Sex_Male)
	{
		if (s_CUI_ID_FRAME_MiniChat.IsRemindPlayer(friendData->GetName()))
		{
			return g_gifMalePortraitChating[friendData->GetHeadPic()];
		}
		else if (friendData->GetOnLine())
		{
			return g_gifMalePortrait[friendData->GetHeadPic()];
		}
		else
		{
			return g_gifMalePortrait[friendData->GetHeadPic() +m_nMaxMalePortrait];
		}
	}
	else
	{
		if (s_CUI_ID_FRAME_MiniChat.IsRemindPlayer(friendData->GetName()))
		{
			return g_gifFemalePortraitChating[friendData->GetHeadPic()];
		}
		else if (friendData->GetOnLine())
		{
			return g_gifFemalePortrait[friendData->GetHeadPic()];
		}
		else
		{
			return g_gifFemalePortrait[friendData->GetHeadPic() +m_nMaxFamalePortrait];
		}

	}
}

// void CUI_ID_FRAME_Friend::UpdateScrollBar( OUT ControlObject* pSender, int n )
// {
// 	int i=0;
// 	int t=0;
// 
// 	vector<RelationDataToClient> vecFriendInfo;
// 	
// // 	s_CUI_ID_FRAME_Friend.m_pID_LIST_GuanXi->Clear();
// // 	s_CUI_ID_FRAME_Friend.m_pID_LIST_GuanXi->SetCurSelIndex(-1);
// 
// 	std::map<int, RelationDataToClient>::iterator itermap = thePlayerRole.GetMapFriendInfo().begin();
// 
// 	if(s_CUI_ID_FRAME_Friend.GetShowType() == eSTP_HaveRelation)
// 	{
// 		for(; itermap != thePlayerRole.GetMapFriendInfo().end(); ++itermap)
// 		{
// 			vecFriendInfo.push_back(itermap->second);
// 		}
// 	}
// 
// 	std::sort(vecFriendInfo.begin(), vecFriendInfo.end(), FriendlyCompare);
// 
// 	std::vector<RelationDataToClient>::iterator iter = vecFriendInfo.begin();
// 
// 	for( t=0; iter != vecFriendInfo.end(); ++iter)
// 	{
// 		if( iter->GetOnLine() && (iter->HaveRelation(RelationDefine::Friend)/* && !iter->HaveHigherRelation()*/) )
// 		{
// 			++t;
// 
// 			if(t<=n)
// 				continue;
// 
// 			RelationDataToClient &friendData = (*iter);
// 			
// 
// 			ControlList::S_List	stItem;
// 			stItem.SetData( "" );
// 
// 			if(friendData.HaveRelation(RelationDefine::Marriage))
// 			{
// 				stItem.SetData( "{#1201}" );
// 			}
// 			else if(friendData.HaveRelation(RelationDefine::Teacher))
// 			{
// 				stItem.SetData( "{#1202}" );
// 			}
// 			else if(friendData.HaveRelation(RelationDefine::Student))
// 			{
// 				stItem.SetData( "{#1203}" );
// 			}
// 			else if(friendData.HaveRelation(RelationDefine::Brother))
// 			{
// 				stItem.SetData( "{#1204}" );
// 			}
// 			else if(friendData.HaveRelation(RelationDefine::Master))
// 			{
// 				// 记名师傅
// 			}
// 			else if(friendData.HaveRelation(RelationDefine::Prentice))
// 			{
// 				// 记名徒弟
// 			}
// // 			s_CUI_ID_FRAME_Friend.m_pID_LIST_GuanXi->AddItem( &stItem,NULL, false);
// 
// 			++i;
// 		}
// 	}
// 
// 	iter = vecFriendInfo.begin();
// 
// 	for( ; iter != vecFriendInfo.end(); ++iter )
// 	{
// 		if( !iter->GetOnLine() && (iter->HaveRelation(RelationDefine::Friend)/* && !iter->HaveHigherRelation()*/)  )
// 		{
// 			++t;
// 
// 			if(t<=n)
// 				continue;
// 
// 			RelationDataToClient &friendData = (*iter);
// 
// 
// 			ControlList::S_List	stItem;
// 			stItem.SetData( "" );
// 
// 			if(friendData.HaveRelation(RelationDefine::Marriage))
// 			{
// 				stItem.SetData( "{#1201}" );
// 			}
// 			else if(friendData.HaveRelation(RelationDefine::Teacher))
// 			{
// 				stItem.SetData( "{#1202}" );
// 			}
// 			else if(friendData.HaveRelation(RelationDefine::Student))
// 			{
// 				stItem.SetData( "{#1203}" );
// 			}
// 			else if(friendData.HaveRelation(RelationDefine::Brother))
// 			{
// 				stItem.SetData( "{#1204}" );
// 			}
// 			else if(friendData.HaveRelation(RelationDefine::Master))
// 			{
// 				// 记名师傅
// 			}
// 			else if(friendData.HaveRelation(RelationDefine::Prentice))
// 			{
// 				// 记名徒弟
// 			}
// // 			s_CUI_ID_FRAME_Friend.m_pID_LIST_GuanXi->AddItem( &stItem,NULL, false);
// 
// 			++i;
// 		}
// 	}
// }

 void CUI_ID_FRAME_Friend::SetTextWait()
 {
  	if(m_pID_TEXT_Wait)
  		m_pID_TEXT_Wait->SetText(theXmlString.GetString(eText_WaitingServerUpdate));
  	else
  		assert(false&&"ui error");
 }

 
 void CUI_ID_FRAME_Friend::ChangeSignature(const char* pName)
 {
	 if (pName)
	 {
		 MsgChangeSignatureReq Req;
		 strcpy_s(Req.szSignature,RelationDefine::MaxSignLength,pName);
		 GettheNetworkInput().SendMsg( &Req );
		 thePlayerRole.SetSignature(pName);
		 m_pID_TEXT_PeopleMood->SetText(pName);
	 }
	
}

 void CUI_ID_FRAME_Friend::ChangeFriendGroupName(const char* pName)
 {

	 if (pName && showTpye == eSTP_HaveRelation)
	 {
		 ControlList::S_List *pItem =  s_CUI_ID_FRAME_Friend.m_pID_LIST_FriendInfo->GetCurSelItem();
		 if(pItem && pItem->m_nHiberarchy == 0)
		 {
			 MsgRelationGroupChangeNameReq Req;
			 Req.uchGroupID = pItem->m_nID;
			 strcpy_s(Req.szGroup,RelationDefine::GroupLength,pName);
			 GettheNetworkInput().SendMsg( &Req );
		 }
	 }
 }

 void CUI_ID_FRAME_Friend::AddFriendGroup(const char* pName)
 {
	 if(!m_pID_FRAME_Friend)
		 return;

	 if (thePlayerRole.GetFriendGroupCount() >= RelationDefine::GroupCount)
	 {
		 CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs,theXmlString.GetString(eText_Friend_AddGroupMax) );
		 return;
	 }

	 if (pName)
	 {
		 // 非法字符检查
		 if ( !CChatCheck::getInstance()->CheckStringInLow( pName ) )
		 {
			 CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString( eText_InputHaveForbiddenWord ) );
			 return;
		 }

		 MsgRelationGroupAddReq Req;
		 strcpy_s(Req.szGroup,RelationDefine::GroupLength,pName);
		 GettheNetworkInput().SendMsg( &Req );
	 }

 }

 void CUI_ID_FRAME_Friend::ChangeFriendTag(const char* pName)
 {
	 if (pName)
	 {
		 ControlList::S_List *pItem =  s_CUI_ID_FRAME_Friend.m_pID_LIST_FriendInfo->GetCurSelItem();
		 if(pItem  && pItem->m_pData)
		 {
			 if (showTpye == eSTP_HaveRelation && pItem->m_nHiberarchy == 0)
			 {
				 return;
			 }
			 RelationDataToClient* pRelationData = (RelationDataToClient*)pItem->m_pData;
			 MsgRelationRemarkChangeReq Req;
			 Req.nPlayerID = pRelationData->GetID();
			 strcpy_s(Req.szRemark,RelationDefine::ReMarkLength,pName);
			 GettheNetworkInput().SendMsg( &Req );
			 pRelationData->SetRemark(pName);
		 }
	 }
 }

void CUI_ID_FRAME_Friend::AdaptButtons( int idx )
{
#define BUTTON_GAP 2
	if ( idx == 0 ) //我的好友
	{
		RECT rc;
		RECT rcSelf;
		_pCheckFriend->GetRealRect(&rc);		//好友列表

		m_pID_LIST_FriendInfo->GetRealRect(&rcSelf);
		m_pID_LIST_FriendInfo->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
		m_pID_LIST_FriendStar->GetRealRect(&rcSelf);
		m_pID_LIST_FriendStar->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
		m_pID_LIST_FriendHead->GetRealRect(&rcSelf);
		m_pID_LIST_FriendHead->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );

		m_pID_LIST_FriendInfo->GetRealRect(&rc);
		_pCheckChouren->GetRealRect(&rcSelf); //仇人人选
		_pCheckChouren->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );

		_pCheckChouren->GetRealRect(&rc); 
		m_pID_CHECKBOX_LinShiHaoYou->GetRealRect(&rcSelf);
		m_pID_CHECKBOX_LinShiHaoYou->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );

		m_pID_CHECKBOX_LinShiHaoYou->GetRealRect(&rc);
		_pCheckBlackList->GetRealRect(&rcSelf);//黑名单列表
		_pCheckBlackList->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );

	}
	else if ( idx == 1 ) //仇人
	{
		RECT rc;
		RECT rcSelf;
		_pCheckFriend->GetRealRect(&rc);		//好友列表

		_pCheckChouren->GetRealRect(&rcSelf); //仇人人选
		_pCheckChouren->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
		_pCheckChouren->GetRealRect(&rc); 

		m_pID_LIST_FriendInfo->GetRealRect(&rcSelf);
		m_pID_LIST_FriendInfo->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
		m_pID_LIST_FriendStar->GetRealRect(&rcSelf);
		m_pID_LIST_FriendStar->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
		m_pID_LIST_FriendHead->GetRealRect(&rcSelf);
		m_pID_LIST_FriendHead->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
		m_pID_LIST_FriendInfo->GetRealRect(&rc);

		m_pID_CHECKBOX_LinShiHaoYou->GetRealRect(&rcSelf);
		m_pID_CHECKBOX_LinShiHaoYou->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
		m_pID_CHECKBOX_LinShiHaoYou->GetRealRect(&rc);

		_pCheckBlackList->GetRealRect(&rcSelf);//黑名单列表
		_pCheckBlackList->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
	}
	else if ( idx == 2 ) //临时好友
	{
		RECT rc;
		RECT rcSelf;
		_pCheckFriend->GetRealRect(&rc);		//好友列表

		_pCheckChouren->GetRealRect(&rcSelf); //仇人人选
		_pCheckChouren->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
		_pCheckChouren->GetRealRect(&rc); 

		m_pID_CHECKBOX_LinShiHaoYou->GetRealRect(&rcSelf);
		m_pID_CHECKBOX_LinShiHaoYou->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
		m_pID_CHECKBOX_LinShiHaoYou->GetRealRect(&rc);

		m_pID_LIST_FriendInfo->GetRealRect(&rcSelf);
		m_pID_LIST_FriendInfo->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
		m_pID_LIST_FriendStar->GetRealRect(&rcSelf);
		m_pID_LIST_FriendStar->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
		m_pID_LIST_FriendHead->GetRealRect(&rcSelf);
		m_pID_LIST_FriendHead->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
		m_pID_LIST_FriendInfo->GetRealRect(&rc);

		_pCheckBlackList->GetRealRect(&rcSelf);//黑名单列表
		_pCheckBlackList->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
	}
	else if ( idx == 3 ) //黑名单
	{
		RECT rc;
		RECT rcSelf;
		_pCheckFriend->GetRealRect(&rc);		//好友列表

		_pCheckChouren->GetRealRect(&rcSelf); //仇人人选
		_pCheckChouren->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
		_pCheckChouren->GetRealRect(&rc); 

		m_pID_CHECKBOX_LinShiHaoYou->GetRealRect(&rcSelf);
		m_pID_CHECKBOX_LinShiHaoYou->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
		m_pID_CHECKBOX_LinShiHaoYou->GetRealRect(&rc);

		_pCheckBlackList->GetRealRect(&rcSelf);//黑名单列表
		_pCheckBlackList->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
		_pCheckBlackList->GetRealRect(&rc);

		m_pID_LIST_FriendInfo->GetRealRect(&rcSelf);
		m_pID_LIST_FriendInfo->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
		m_pID_LIST_FriendStar->GetRealRect(&rcSelf);
		m_pID_LIST_FriendStar->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
		m_pID_LIST_FriendHead->GetRealRect(&rcSelf);
		m_pID_LIST_FriendHead->SetPos( rcSelf.left, rc.bottom + BUTTON_GAP );
		m_pID_LIST_FriendInfo->GetRealRect(&rc);

	}
}

 void CUI_ID_FRAME_Friend::RefreshFriendStar()
 {
	 m_pID_LIST_FriendStar->BeginUpdate();
	 m_pID_LIST_FriendHead->Clear();
	 m_pID_LIST_FriendStar->Clear();

 /*
	 unsigned short relationType = RelationDefine::InitRelation;
	 switch(showTpye)
	 {
	 case eSTP_HaveRelation:
		 relationType = RelationDefine::Friend;
		 break;
	 case eSTP_TempFriend:
		 relationType = RelationDefine::TempFriend;
		 break;
	 case eSTP_VendettaList:
		 relationType = RelationDefine::Vendetta;
		 break;
	 case eSTP_BlackList:
		 relationType = RelationDefine::BlackList;
		 break;
	 }
 */

	 ControlList::S_List stItem;
	 bool bInsert = false;
	 for (int i = 0; i < m_pID_LIST_FriendInfo->GetListItemCnt(); ++i)
	 {
		 ControlList::S_List* pItem = m_pID_LIST_FriendInfo->GetListItem(i);
		 //目前只有好友界面是支持分组的
		 if(eSTP_HaveRelation == showTpye)
		 {
			 if (pItem->m_nHiberarchy != 1 || pItem->m_pData == NULL)
			 {
				 stItem.clear();
				 stItem.SetData("");
				 m_pID_LIST_FriendHead->AddItem(&stItem, NULL, false);
				 m_pID_LIST_FriendStar->AddItem(&stItem,NULL, false);
				 continue;
			 }
		 }

		 RelationDataToClient* pFriendData = (RelationDataToClient*)pItem->m_pData;
// 		 if(relationType != pFriendData->GetRelation())
// 		 {
// 			 continue;
// 		 } 

		 /*
		 bInsert = !bInsert;
		 if(!bInsert)
		 {
			 continue;
		 }
		 */

		 DWORD dwColor = 0xffffffff;
		 if( pFriendData->GetOnLine())
			 dwColor = Color_Config.getColor(CC_FRIEND_ONLINE);
		 else
			 dwColor = Color_Config.getColor(CC_FRIEND_OFFLINE);

		 //设置头像
		 stItem.clear();
		 stItem.SetData(GetPortraitGif(pFriendData), 0, NULL, dwColor);
		 m_pID_LIST_FriendHead->AddItem(&stItem, NULL, false);
// 		 stItem.clear();
// 		 stItem.SetData("", 0);
// 		 m_pID_LIST_FriendHead->AddItem(&stItem, NULL, false);

		 //设置等级
		 stItem.clear();
		 //char szItem[128] = {0};
		 //sprintf(szItem, "%d级", pFriendData->GetLevel());
		 //去掉这个好友度显示
		 //MeSprintf( szItem, sizeof(szItem), "好友度:%d", pFriendData->GetFriendly() );
		 //stItem.SetData(szItem, 0, NULL, dwColor);
		 //m_pID_LIST_FriendStar->AddItem(&stItem,NULL, false);
// 		 stItem.clear();
// 		 stItem.SetData("", 0);
// 		 m_pID_LIST_FriendStar->AddItem(&stItem,NULL, false); 
	 }

	 m_pID_LIST_FriendStar->EndUpdate();

 }

 void CUI_ID_FRAME_Friend::Friend_CollapseCallBackFun( ControlObject* pSender, ControlList::S_List* pItem )
 {
	 if( !s_CUI_ID_FRAME_Friend.GetFrame() )
		 return;

	 s_CUI_ID_FRAME_Friend.RefreshFriendStar();

 }

void CUI_ID_FRAME_Friend::Friend_ShowTipCallBackFun( ControlObject* pSender, ControlList::S_List* pItem )
{
	if (s_CUI_ID_FRAME_Friend.showTpye == eSTP_HaveRelation && pItem->m_nHiberarchy == 0 || pItem->m_pData == NULL)
	{
		return;
	}

	RelationDataToClient *pFriendData = (RelationDataToClient*)pItem->m_pData;
    if(IsTheSprite(pFriendData))
	{//如果是小精灵
		s_CUI_ID_FRAME_Sprite.SetVisable(true);
		s_CUI_ID_FRAME_Sprite.ResetFramePos();
		return;
	}

	s_CUI_ID_FRAME_FriendView.SetVisable(true);
	s_CUI_ID_FRAME_FriendView.Refresh(pFriendData);
	RECT rcFriendDlg;
	s_CUI_ID_FRAME_Friend.m_pID_FRAME_Friend->GetRealRect(&rcFriendDlg);

	RECT rcFriendView;
	s_CUI_ID_FRAME_FriendView.GetFrame()->GetRealRect(&rcFriendView);
	int nWidth = rcFriendView.right - rcFriendView.left;
	int nHeight = rcFriendView.bottom - rcFriendView.top;

	RECT rcFriendViewNew;
	if (rcFriendDlg.left < nWidth)
	{
		rcFriendViewNew.left = rcFriendDlg.right; 
	}
	else
	{
		rcFriendViewNew.left = rcFriendDlg.left - nWidth; 
	}
	rcFriendViewNew.top = theUiManager.m_ptMoust.y;
	if (rcFriendViewNew.top + nHeight > rcFriendDlg.bottom)
	{
		rcFriendViewNew.top = rcFriendDlg.bottom - nHeight;
	}
	s_CUI_ID_FRAME_FriendView.GetFrame()->SetPos(rcFriendViewNew.left,rcFriendViewNew.top);
}

 void CUI_ID_FRAME_Friend::SetTipForFriend( RelationDataToClient *pFriendData,ControlList::S_List&stItem )
 {
	 return;
	 char szTip[256] = {0};
	 std::string strSex;
	 string strProfession ;
	 GetSexProfessionString(*pFriendData, strSex, strProfession);
	 int level = theRelationConfig.GetFriendLevel(pFriendData->GetFriendly());

	 if( level >= theRelationConfig.GetMaxFriendLevel() )
	 {
		 level = theRelationConfig.GetMaxFriendLevel()-1;
	 }
	 const LevelInfo* levelinfo = theRelationConfig.GetLevelInfo(level+1);
	 const LevelInfo* levelinfo2 = theRelationConfig.GetLevelInfo(level);
	 unsigned int usMax = 0,usCur = 0;

	 if( levelinfo&&levelinfo2 )
	 {
		 usMax = levelinfo->GetFriendly() - levelinfo2->GetFriendly();
		 usCur = pFriendData->GetFriendly() - levelinfo2->GetFriendly();
	 }

	 MeSprintf_s( szTip, sizeof(szTip)/sizeof(char) - 1, theXmlString.GetString(eClient_Frddlg_Fiendly), pFriendData->GetName(),
		 strSex.c_str(),(int)pFriendData->GetLevel(), strProfession.c_str(),usCur,usMax,pFriendData->GetFriendly());
	 stItem.setTip( szTip, DT_LEFT );
	 stItem.setIsOnline(true);
 }

 void CUI_ID_FRAME_Friend::SetTipForOther( RelationDataToClient *pFriendData,ControlList::S_List&stItem )
 {
	 return;
	 char szTip[256] = {0};
	 std::string strSex;
	 string strProfession ;
	 GetSexProfessionString(*pFriendData, strSex, strProfession);
	 MeSprintf_s( szTip, sizeof(szTip)/sizeof(char) - 1, theXmlString.GetString(eTip_Client_FriendListInfo), pFriendData->GetName(),strSex.c_str(),(int)pFriendData->GetLevel(), 
		 strProfession.c_str() );
	 stItem.setTip( szTip, DT_LEFT );
	 stItem.setIsOnline(true);

 }

 void CUI_ID_FRAME_Friend::AddToList( RelationDataToClient *pFriendData,ControlList::S_List&stItem,DWORD col )
 {
 /*
	 //名字
	 char szItem[128] = {0};
	 const char* pPortrait = GetPortraitGif(pFriendData);
	 MeSprintf_s( szItem, sizeof(szItem)/sizeof(char) - 1, "%s%s", pPortrait,pFriendData->GetName() );
	 stItem.SetData( szItem, 0, pFriendData, col );
	 m_pID_LIST_FriendInfo->AddItem(&stItem,NULL, false);
 */

	 //设置名字
	 //stItem.Clear();
	 stItem.SetData(pFriendData->GetName(), 0, pFriendData, col);
	 m_pID_LIST_FriendInfo->AddItem(&stItem,NULL, false);

 /*
	 //设置心情
	 //stItem.Clear();
	 stItem.SetData(pFriendData->GetSignature(), 0, pFriendData, col);
	 m_pID_LIST_FriendInfo->AddItem(&stItem,NULL, false);
 */
 }


 const char* CUI_ID_FRAME_Friend::GetPortraitGifFromName( const char* pPlayerName )
 {
	 if (NULL == pPlayerName)
	 {
		 return NULL;
	 }
	 int dbId = thePlayerRole.GetdbID(pPlayerName);
	 if (dbId == -1)
	 {
		 if (s_CUI_ID_FRAME_MiniChat.IsRemindPlayer(pPlayerName))
		 {
			 return "{#MMMM1}";
		 }
		 else
		 {
			 return "{#MMMM0}";
		 }
	 }
	 else
	 {
		 RelationDataToClient* pFriendData = &thePlayerRole.GetMapFriendInfo().find(dbId)->second;
		 return GetPortraitGif(pFriendData);
	 }
 }

 bool CUI_ID_FRAME_Friend::IsShowTypeFriend(void)
 {
	 return eSTP_HaveRelation == showTpye;
 }

 void CUI_ID_FRAME_Friend::RefreshButtonStatus(void)
 {
 /*
	 switch(showTpye)
	 {
	 case eSTP_HaveRelation:  // 好友
		 m_pID_BUTTON_Mood->SetEnable(true);
		 m_pID_BUTTON_Addheimingdan->SetEnable(false);
		 m_pID_BUTTON_Remove->SetEnable(true);
		 m_pID_BUTTON_AddingFriend->SetEnable(true);
		 m_pID_BUTTON_Search->SetEnable(true);
		 break;
	 case eSTP_BlackList:	// 黑名单
		 m_pID_BUTTON_Mood->SetEnable(false);
		 m_pID_BUTTON_Addheimingdan->SetEnable(true);
		 m_pID_BUTTON_Remove->SetEnable(false);
		 m_pID_BUTTON_AddingFriend->SetEnable(false);
		 m_pID_BUTTON_Search->SetEnable(false);
		 break;
	 case eSTP_VendettaList:     // 仇人
		 m_pID_BUTTON_Mood->SetEnable(false);
		 m_pID_BUTTON_Addheimingdan->SetEnable(false);
		 m_pID_BUTTON_Remove->SetEnable(true);
		 m_pID_BUTTON_AddingFriend->SetEnable(false);
		 m_pID_BUTTON_Search->SetEnable(false);
		 break;
	 case eSTP_TempFriend:        // 临时好友
		 m_pID_BUTTON_Mood->SetEnable(false);
		 m_pID_BUTTON_Addheimingdan->SetEnable(false);
		 m_pID_BUTTON_Remove->SetEnable(true);
		 m_pID_BUTTON_AddingFriend->SetEnable(true);
		 m_pID_BUTTON_Search->SetEnable(true);
		 break;
	 default:
		 m_pID_BUTTON_Mood->SetEnable(false);
		 m_pID_BUTTON_Addheimingdan->SetEnable(false);
		 m_pID_BUTTON_Remove->SetEnable(false);
		 m_pID_BUTTON_AddingFriend->SetEnable(false);
		 m_pID_BUTTON_Search->SetEnable(false);
	 }
 */

	 m_pID_BUTTON_Mood->SetEnable(true);
	 m_pID_BUTTON_Addheimingdan->SetEnable(true);
	 m_pID_BUTTON_Remove->SetEnable(true);
	 m_pID_BUTTON_AddingFriend->SetEnable(true);
	 m_pID_BUTTON_Search->SetEnable(true);
 }