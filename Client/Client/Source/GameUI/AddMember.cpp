/********************************************************************
Created by UIEditor.exe
	FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\AddMember.cpp
*********************************************************************/
#include <assert.h>
#include "GameMain.h"
#include "MeUi/UiManager.h"
#include "GlobalDef.h"
#include "AddMember.h"

#include "FuncPerformanceLog.h"
#include "create.h"
#include "chatcheck.h"
#include "XmlStringLanguage.h"
#include"MessageBox.h"
#include "core/Name.h"
#include "Gang.h"
#include "ChatInfoBox.h"
#include "FriendDlg.h"
// #include "corps.h"
#include "Pet.h"
#include "PlayerMgr.h"
#include "color_config.h"
#include "Player.h"
#include "ShowScreenText.h"
#include "Ui/InfoList.h"
#include "RelationMessage.h"
#include "FamilyMessage.h"
#include "GuildMessage.h"
#include "chatcheck.h"
#include "ScreenInfoManager.h"
CUI_ID_FRAME_ADD_MEMBER s_CUI_ID_FRAME_ADD_MEMBER;
//bool GuildEnsureChengWeiChangedCallback( const bool bPressYesButton, void *pData )
//{
//	if (bPressYesButton)
//	{
//		int * pdbId = (int*)pData;
//		//MsgExchangeGuildMemberTitle title;
//
//		if(!s_CUI_ID_FRAME_ADD_MEMBER.GetpIDEditAddName())
//			return false;
//
//		strncpy(title.szTitle, s_CUI_ID_FRAME_ADD_MEMBER.GetpIDEditAddName()->GetText(), sizeof(title.szTitle)-1);
//		title.nMemberDBId = * pdbId; 
//		GettheNetworkInput().SendMsg(&title);
//	}
//	return true;
//}

bool GuildEnsureCorpsChengWeiChangedCallback( const bool bPressYesButton, void *pData )
{
	if (bPressYesButton)
	{

	}
	return true;
}

MAP_FRAME_RUN( s_CUI_ID_FRAME_ADD_MEMBER, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ADD_MEMBER, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ADD_MEMBER, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ADD_MEMBER, ID_BUTTON_CancleOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_ADD_MEMBER, ID_EDIT_AddNameOnEditEnter )
//MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ADD_MEMBER, ID_LIST_ActivityListOnListSelectChange )
CUI_ID_FRAME_ADD_MEMBER::CUI_ID_FRAME_ADD_MEMBER()
{
	guardfunc;
	// SGuildMember
	m_pID_FRAME_ADD_MEMBER = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancle = NULL;
//	m_pID_PICTURE_15507 = NULL;
	m_pID_EDIT_AddName = NULL;
	//m_pID_LIST_ActivityList = NULL;
	unguard;

}
// Frame
bool CUI_ID_FRAME_ADD_MEMBER::OnFrameRun()
{
	guardfunc;
	return true;

	unguard;
}
bool CUI_ID_FRAME_ADD_MEMBER::OnFrameRender()
{
	guardfunc;
	return true;
	unguard;
}

// Button
bool CUI_ID_FRAME_ADD_MEMBER::ID_BUTTON_CancleOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	SetVisable(false);
	return true;
	unguard;
}
// Edit
void CUI_ID_FRAME_ADD_MEMBER::ID_EDIT_AddNameOnEditEnter( ControlObject* pSender, const char* szData )
{
	guardfunc;
	ID_BUTTON_OKOnButtonClick(m_pID_BUTTON_OK);
	unguard;
}
	// List
// 	void CUI_ID_FRAME_ADD_MEMBER::ID_LIST_ActivityListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
// 	{
// 		if (pItem)
// 		{
// 			m_pID_EDIT_AddName->SetText(pItem->m_szText);
// 		}
// 	}

// 装载UI
bool CUI_ID_FRAME_ADD_MEMBER::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\AddMember.meui", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\AddMember.UI]失败")
			return false;
	}
// 	else if ( dwResult != 28301/*文件版本号*/ )
// 	{
// 		MESSAGE_BOX("读取文件[UI\\Guild_Add.UI]与源代码版本不一样")
// 	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_ADD_MEMBER::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_ADD_MEMBER, s_CUI_ID_FRAME_ADD_MEMBEROnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ADD_MEMBER, s_CUI_ID_FRAME_ADD_MEMBEROnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ADD_MEMBER, ID_BUTTON_OK, s_CUI_ID_FRAME_ADD_MEMBERID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ADD_MEMBER, ID_BUTTON_Cancle, s_CUI_ID_FRAME_ADD_MEMBERID_BUTTON_CancleOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_ADD_MEMBER, ID_EDIT_AddName, s_CUI_ID_FRAME_ADD_MEMBERID_EDIT_AddNameOnEditEnter );
//theUiManager.OnListSelectChange( ID_FRAME_ADD_MEMBER, ID_LIST_ActivityList, s_CUI_ID_FRAME_ADD_MEMBERID_LIST_ActivityListOnListSelectChange );

	m_pID_FRAME_ADD_MEMBER = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ADD_MEMBER );
	m_pID_TEXT_Msg = (ControlText*)theUiManager.FindControl( ID_FRAME_ADD_MEMBER, ID_TEXT_Msg );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_ADD_MEMBER, ID_BUTTON_OK );
	m_pID_BUTTON_Cancle = (ControlButton*)theUiManager.FindControl( ID_FRAME_ADD_MEMBER, ID_BUTTON_Cancle );
	//m_pID_PICTURE_15507 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ADD_MEMBER, ID_PICTURE_15507 );
	m_pID_EDIT_AddName = (ControlEdit*)theUiManager.FindControl( ID_FRAME_ADD_MEMBER, ID_EDIT_AddName );
		//m_pID_LIST_ActivityList = (ControlList*)theUiManager.FindControl( ID_FRAME_ADD_MEMBER, ID_LIST_ActivityList );
	assert( m_pID_FRAME_ADD_MEMBER );
	assert( m_pID_TEXT_Msg );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancle );
	//assert( m_pID_PICTURE_15507 );
	assert( m_pID_EDIT_AddName );
	//	assert( m_pID_LIST_ActivityList );




	m_pID_FRAME_ADD_MEMBER->SetArrayMode(ArrayMode_Top);


	if( !s_CUI_ID_FRAME_CREATE.GetImeInstance() )
		s_CUI_ID_FRAME_CREATE.SetImeInstance( ImmGetContext( g_hWnd ) );

	ImmReleaseContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );


	return true;
	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_ADD_MEMBER::_UnLoadUI()
{
	guardfunc;
	CLOSE_SCRIPT( eUI_OBJECT_GuildAdd );
	m_pID_FRAME_ADD_MEMBER = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancle = NULL;
	//m_pID_PICTURE_15507 = NULL;
	m_pID_EDIT_AddName = NULL;
	//m_pID_LIST_ActivityList = NULL;
		return theUiManager.RemoveFrame( "Data\\UI\\AddMember.MEUI" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_ADD_MEMBER::_IsVisable()
{
	guardfunc;
	if( !m_pID_FRAME_ADD_MEMBER )
		return false;
	return m_pID_FRAME_ADD_MEMBER->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_ADD_MEMBER::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pID_FRAME_ADD_MEMBER )
		return;
	m_pID_FRAME_ADD_MEMBER->SetVisable( bVisable );

	if( bVisable == true)
	{
		m_pID_EDIT_AddName->SetText("");
		switch (meFrameType)
		{
		case eFrameType_AddMember:
			{
				m_pID_TEXT_Msg->SetText(theXmlString.GetString(eTextPlayer_AddGang));
				m_pID_EDIT_AddName->SetMaxLength(8);
			}
			break;
		case eFrameType_CreateFamily:
			{
				m_pID_TEXT_Msg->SetText(theXmlString.GetString(eText_Guild_CreateFamily));
				m_pID_EDIT_AddName->SetMaxLength(6);
			}
			break;
		case eFrameType_AddFamilyMember:
			{
				m_pID_TEXT_Msg->SetText(theXmlString.GetString(eText_FamilyInputName));
				m_pID_EDIT_AddName->SetMaxLength(8);
			}
			break;
		case eFrameType_ChangeFirstFamilyName:
		case eFrameType_ChangeSecFamilyName:
		case eFrameType_ChangeThirdFamilyName:
		case eFrameType_ChangeFourthFamilyName:
		case eFrameType_ChangeFifthFamilyName:
			{
				m_pID_TEXT_Msg->SetText(theXmlString.GetString(eText_Guild_ChangeFamilyName));
				m_pID_EDIT_AddName->SetMaxLength(6);
			}
			break;
		}

// 		std::map< short, CPlayer* >& playArr = theHeroGame.GetPlayerMgr()->m_mapPlayers;
// 		std::map<short, CPlayer*>::iterator it, end = playArr.end();
// 		for( it = playArr.begin(); it != end; ++it )
// 		{
// 			if (it->second && it->second != theHeroGame.GetPlayerMgr()->GetMe() &&
// 				it->second->IsPlayer() && it->second->GetName() &&
// 				!it->second->m_cFightStatus.IsHide())
// 			{
// 				if (meFrameType == eFrameType_AddMember && thePlayerRole.GetGangMgr()->FindByName(it->second->GetName()))
// 				{
// 					continue;
// 				}
// 				if (meFrameType == eFrameType_AddFriend && !thePlayerRole.CanAddFriend(it->second->GetName()))
// 				{
// 					continue;
// 				}
// 
// 				ControlList::S_List	stItem;
// 				stItem.SetData(it->second->GetName());
// 
// 				//m_pID_LIST_ActivityList->AddItem(&stItem);
// 			}
// 		}
		//m_pID_LIST_ActivityList->SetCurSelIndex(-1);
		theUiManager.SetFocus(m_pID_EDIT_AddName);
		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
	}
	else
	{
		ImmAssociateContext( g_hWnd, NULL );
	}
	unguard;
}

bool CUI_ID_FRAME_ADD_MEMBER::EditInputIsVisable()
{
	guardfunc;
	if( m_pID_EDIT_AddName )
	{
		return (theUiManager.GetFocus() == m_pID_EDIT_AddName);
	}
	return FALSE;
	unguard;
}


ControlEdit* CUI_ID_FRAME_ADD_MEMBER::GetpIDEditAddName()
{
	if(m_pID_EDIT_AddName)
		return m_pID_EDIT_AddName;
	else
		assert(false&&"ui error");

	return NULL;
}

//----------------------------------------------------------------------------------------------------------------------
// Button
bool CUI_ID_FRAME_ADD_MEMBER::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if(!m_pID_FRAME_ADD_MEMBER)
		return false;

	if(strlen(m_pID_EDIT_AddName->GetText()) == 0)
	{
		return true;
	}
	bool bIsForbit_1= CChatCheck::getInstance()->CheckStringInLow(m_pID_EDIT_AddName->GetText());
	if (!bIsForbit_1)
	{//含有非法字符
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, theXmlString.GetString(eClient_Frddlg_AddNotLaw) );
		return false;
	}
	switch (meFrameType)
	{
	case eFrameType_AddMember:
		{
			MsgInviteGuildReq msg;
			strncpy(msg.szPlayerName, m_pID_EDIT_AddName->GetText(), sizeof(msg.szPlayerName)-1);
			GettheNetworkInput().SendMsg(&msg);
		}
		break;
	case eFrameType_CreateFamily:
		{
			MsgGuildCreateFamilyReq msg;
			strncpy(msg.szName, m_pID_EDIT_AddName->GetText(), sizeof(msg.szName) - 1);
			GettheNetworkInput().SendMsg(&msg);
		}
		break;
	case eFrameType_ChangeFirstFamilyName:
		{
			MsgGuildFamilyChangeReq msg;
			strcpy(msg.szName, m_pID_EDIT_AddName->GetText());
			msg.uchFamilyID = eKey_FirstFamily;
			GettheNetworkInput().SendMsg(&msg);
		}
		break;
	case eFrameType_ChangeSecFamilyName:
		{
			MsgGuildFamilyChangeReq msg;
			strcpy(msg.szName, m_pID_EDIT_AddName->GetText());
			msg.uchFamilyID = eKey_SecondFamily;
			GettheNetworkInput().SendMsg(&msg);
		}
		break;
	case eFrameType_ChangeThirdFamilyName:
		{
			MsgGuildFamilyChangeReq msg;
			strcpy(msg.szName, m_pID_EDIT_AddName->GetText());
			msg.uchFamilyID = eKey_ThirdFamily;
			GettheNetworkInput().SendMsg(&msg);
		}
		break;
	case eFrameType_ChangeFourthFamilyName:
		{
			MsgGuildFamilyChangeReq msg;
			strcpy(msg.szName, m_pID_EDIT_AddName->GetText());
			msg.uchFamilyID = eKey_FourthFamily;
			GettheNetworkInput().SendMsg(&msg);
		}
		break;
	case eFrameType_ChangeFifthFamilyName:
		{
			MsgGuildFamilyChangeReq msg;
			strcpy(msg.szName, m_pID_EDIT_AddName->GetText());
			msg.uchFamilyID = eKey_FifthFamily;
			GettheNetworkInput().SendMsg(&msg);
		}
		break;
	case eFrameType_AddFamilyMember:
		{
			MsgInviteFamilyReq msg;
			MeSprintf( msg.szPlayerName, sizeof(msg.szPlayerName) - 1, m_pID_EDIT_AddName->GetText() );
			GettheNetworkInput().SendMsg(&msg);
		}
		break;
	}
	//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Info_GuildInfo, theXmlString.GetString(eText_GuildSendMessageSuccess) );
	SetVisable(false);
	return true;
	unguard;
}