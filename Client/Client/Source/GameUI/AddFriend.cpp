/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\AddFriend.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "AddFriend.h"
#include "GlobalDef.h"

#include "FuncPerformanceLog.h"
#include "create.h"
#include "chatcheck.h"
#include "XmlStringLanguage.h"
#include"MessageBox.h"
#include "core/Name.h"
#include "Gang.h"
#include "ChatInfoBox.h"
#include "FriendDlg.h"
#include "Pet.h"
#include "PlayerMgr.h"
#include "color_config.h"
#include "Player.h"
#include "ShowScreenText.h"
#include "Ui/InfoList.h"
#include "RelationMessage.h"
#include "GuildMessage.h"
#include "PlayerRole.h"
CUI_ID_FRAME_AddFriend s_CUI_ID_FRAME_AddFriend;
MAP_FRAME_RUN( s_CUI_ID_FRAME_AddFriend, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_AddFriend, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AddFriend, ID_EDIT_FriendNameOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AddFriend, ID_BUTTON_CLOSEOnButtonClick )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_AddFriend, ID_COMBOBOX_FriendClassOnComboBoxChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AddFriend, ID_BUTTON_TrueOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AddFriend, ID_BUTTON_CancelOnButtonClick )
CUI_ID_FRAME_AddFriend::CUI_ID_FRAME_AddFriend()
{
	// Member
	m_pID_FRAME_AddFriend = NULL;
	m_pID_TEXT_String = NULL;
	m_pID_EDIT_FriendName = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_COMBOBOX_FriendClass = NULL;
	m_pID_BUTTON_True = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_PICTURE_1 = NULL;
	m_pID_TEXT_Friend = NULL;
	m_pID_PICTURE_2 = NULL;

	meFrameType = eFrameType_AddFriend;
	m_nGroup = 0;
}
// Frame
bool CUI_ID_FRAME_AddFriend::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_AddFriend::OnFrameRender()
{
	return true;
}
// Edit
void CUI_ID_FRAME_AddFriend::ID_EDIT_FriendNameOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_AddFriend )
		return;
}
// Button
bool CUI_ID_FRAME_AddFriend::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_AddFriend )
		return false;
	return true;
}
// ComboBox
void CUI_ID_FRAME_AddFriend::ID_COMBOBOX_FriendClassOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_AddFriend )
		return;
	for (int nGroup = 0; nGroup < RelationDefine::GroupCount;++nGroup)
	{
		RelationGroup& group = thePlayerRole.GetFrdGroup(nGroup);
		if (group.IsEmpty())
		{
			continue;
		}
		if (0 == strcmp(group.GetName(),szData))
		{
			m_nGroup = nGroup;
			break;
		}
	}
}
// Button
bool CUI_ID_FRAME_AddFriend::ID_BUTTON_TrueOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_AddFriend )
		return false;

	switch (meFrameType)
	{
	case eFrameType_AddFriend:
		{
			if(strlen(m_pID_EDIT_FriendName->GetText()) == 0)
			{
				return true;
			}
			sendMsgAddFriend(m_pID_EDIT_FriendName->GetText(),RelationDefine::Friend,m_nGroup );
		}
		break;
	case eFrameType_AddFriendFromRMenu:
		{
			sendMsgAddFriend(m_szName.c_str() ,RelationDefine::Friend,m_nGroup);
		}
		break;
	case eFrameType_ChangeFriendToGroup:
		{
			sendMsgChangeFriendGroup(m_szName.c_str() ,m_nGroup);
		}
		break;
	case eFrameType_AddBlackFriend:
		{
			if(strlen(m_pID_EDIT_FriendName->GetText()) == 0)
			{
				return true;
			}
			sendMsgAddFriend(m_pID_EDIT_FriendName->GetText(), RelationDefine::BlackList ,-1);
		}
		break;
	}
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_AddFriend::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_AddFriend )
		return false;
	SetVisable(false);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_AddFriend::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\AddFriend.MEUI" , true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\AddFriend.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_AddFriend::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_AddFriend, s_CUI_ID_FRAME_AddFriendOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_AddFriend, s_CUI_ID_FRAME_AddFriendOnFrameRender );
	theUiManager.OnEditEnter( ID_FRAME_AddFriend, ID_EDIT_FriendName, s_CUI_ID_FRAME_AddFriendID_EDIT_FriendNameOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_AddFriend, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_AddFriendID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnComboBoxChange( ID_FRAME_AddFriend, ID_COMBOBOX_FriendClass, s_CUI_ID_FRAME_AddFriendID_COMBOBOX_FriendClassOnComboBoxChange );
	theUiManager.OnButtonClick( ID_FRAME_AddFriend, ID_BUTTON_True, s_CUI_ID_FRAME_AddFriendID_BUTTON_TrueOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_AddFriend, ID_BUTTON_Cancel, s_CUI_ID_FRAME_AddFriendID_BUTTON_CancelOnButtonClick );

	m_pID_FRAME_AddFriend = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_AddFriend );
	m_pID_TEXT_String = (ControlText*)theUiManager.FindControl( ID_FRAME_AddFriend, ID_TEXT_String );
	m_pID_EDIT_FriendName = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AddFriend, ID_EDIT_FriendName );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_AddFriend, ID_BUTTON_CLOSE );
	m_pID_COMBOBOX_FriendClass = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_AddFriend, ID_COMBOBOX_FriendClass );
	m_pID_BUTTON_True = (ControlButton*)theUiManager.FindControl( ID_FRAME_AddFriend, ID_BUTTON_True );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_AddFriend, ID_BUTTON_Cancel );
	m_pID_PICTURE_1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AddFriend, ID_PICTURE_1 );
	m_pID_TEXT_Friend = (ControlText*)theUiManager.FindControl( ID_FRAME_AddFriend, ID_TEXT_Friend );
	m_pID_PICTURE_2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AddFriend, ID_PICTURE_2 );

	assert( m_pID_FRAME_AddFriend );
	assert( m_pID_TEXT_String );
	assert( m_pID_EDIT_FriendName );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_COMBOBOX_FriendClass );
	assert( m_pID_BUTTON_True );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_PICTURE_1 );
	assert( m_pID_TEXT_Friend );
	assert( m_pID_PICTURE_2 );

	m_pID_FRAME_AddFriend->SetArrayMode(ArrayMode_Top);
	m_pID_COMBOBOX_FriendClass->GetEditInput().SetReadOnly(true);
	m_dwLastAddFriendReqTime = 0;
	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_AddFriend::_UnLoadUI()
{
	m_pID_FRAME_AddFriend = NULL;
	m_pID_TEXT_String = NULL;
	m_pID_EDIT_FriendName = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_COMBOBOX_FriendClass = NULL;
	m_pID_BUTTON_True = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_PICTURE_1 = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\AddFriend.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_AddFriend::_IsVisable()
{
	if ( !m_pID_FRAME_AddFriend )
		return false;
	return m_pID_FRAME_AddFriend->IsVisable();
}
extern HWND g_hWnd;
// 设置是否可视
void CUI_ID_FRAME_AddFriend::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_AddFriend )
		return ;
	m_pID_FRAME_AddFriend->SetVisable( bVisable );
	if( bVisable == true)
	{
		m_pID_COMBOBOX_FriendClass->SetVisable(false);
		m_pID_TEXT_Friend->SetVisable(false);
		m_pID_PICTURE_2->SetVisable(false);
		if (eFrameType_AddBlackFriend != meFrameType)
		{//添加box
			m_pID_COMBOBOX_FriendClass->SetVisable(true);
			m_pID_TEXT_Friend->SetVisable(true);
			ControlList& list = m_pID_COMBOBOX_FriendClass->GetListBox();
			list.Clear();
			for (int nGroup = 0; nGroup < RelationDefine::GroupCount;++nGroup)
			{
				RelationGroup& group = thePlayerRole.GetFrdGroup(nGroup);
				if (group.IsEmpty())
				{
					continue;
				}
				ControlList::S_List stItem;
				stItem.clear();
				stItem.SetData(group.GetName(),nGroup);
				stItem.SetMargin( 5 );
				list.AddItem(&stItem);
			}
			RelationGroup* group = &thePlayerRole.GetFrdGroup(m_nGroup);
			if (group->IsEmpty())
			{
				m_nGroup = 0;
				group = &thePlayerRole.GetFrdGroup(m_nGroup);
			}
			m_pID_COMBOBOX_FriendClass->GetEditInput().SetText(group->GetName());
			
		}
		m_pID_EDIT_FriendName->SetVisable(true);
		m_pID_EDIT_FriendName->SetText("");
		m_pID_PICTURE_1->SetVisable(true);
		switch (meFrameType)
		{
		case eFrameType_AddFriend:
			{
				m_pID_TEXT_String->SetText(theXmlString.GetString(eClient_AddFriend));
				m_pID_EDIT_FriendName->SetMaxLength(8);
				m_pID_PICTURE_2->SetVisable(true);
			}
			break;
		case eFrameType_AddFriendFromRMenu:
			{
				char cTemp[1024] = {0};
				MeSprintf_s(cTemp,1024,theXmlString.GetString(eText_AddFriendReq),m_szName.c_str());
				m_pID_TEXT_String->SetText(cTemp);
				m_pID_EDIT_FriendName->SetVisable(false);
				m_pID_PICTURE_1->SetVisable(false);
			}
			break;
		case eFrameType_ChangeFriendToGroup:
			{
				char cTemp[1024] = {0};
				MeSprintf_s(cTemp,1024,theXmlString.GetString(eFriend_ChangeFriendToGroup),m_szName.c_str());
				m_pID_TEXT_String->SetText(cTemp);
				m_pID_EDIT_FriendName->SetVisable(false);
				m_pID_PICTURE_1->SetVisable(false);
			}
			break;
		case eFrameType_AddBlackFriend:
			{
				m_pID_TEXT_String->SetText(theXmlString.GetString(eTextPlayer_AddBlackFriend));
				m_pID_EDIT_FriendName->SetMaxLength(8);
			}
			break;
		}
		if (m_pID_EDIT_FriendName->IsVisable())
		{
			theUiManager.SetFocus(m_pID_EDIT_FriendName);
			ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
		}
	}
	else
	{
		if (m_pID_EDIT_FriendName->IsVisable())
		{
			ImmAssociateContext( g_hWnd, NULL );
		}
	}
}

bool CUI_ID_FRAME_AddFriend::EditInputIsVisable()
{
	if( m_pID_EDIT_FriendName )
	{
		return (theUiManager.GetFocus() == m_pID_EDIT_FriendName);
	}
	return FALSE;
}

void CUI_ID_FRAME_AddFriend::sendMsgChangeFriendGroup( const char* name,int nGroup )
{
	if (name == NULL || strlen(name) == 0 || strcmp(name,thePlayerRole.GetFrdGroup(nGroup).GetName()) == 0)
	{
		return;
	}
	
	int nId = thePlayerRole.GetdbID(name);
	if (nId != -1)
	{
		MsgRelationGroupChangeReq msg;
		msg.uchGroupID = nGroup;
		msg.nPlayerID = nId;
		GettheNetworkInput().SendMsg( &msg );
	}
	

}

void CUI_ID_FRAME_AddFriend::sendMsgAddFriend( const char* name, RelationDefine::EConstDefine type ,int nGroup )
{
	if( strlen(name) == 0 )
	{
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString( eClient_Frddlg_AddNotLaw ) );
		SetVisable(false);
		return;
	}

    if( type == RelationDefine::Friend )
    {
		if( !thePlayerRole.CheckNewFriendName(name,false) )
		{
			SetVisable(false);
			return;
		}
        // 请求加好友有3秒CD
        if( HQ_TimeGetTime() - m_dwLastAddFriendReqTime < 3000 )
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString( eText_OperateFailedInCD ) );
            return;
        }
        m_dwLastAddFriendReqTime = HQ_TimeGetTime();

		/*char pTemp[1024] = {0};
		MeSprintf_s(pTemp, sizeof(pTemp)/sizeof(char) - 1, theXmlString.GetString(eText_AddFriendReq),name);
		s_CUI_ID_FRAME_InfoList. AddInfo(pTemp, Color_Config.getColor( CC_SystemPromp ));*/
	}
	else if (type == RelationDefine::BlackList)
	{
		if( !thePlayerRole.CheckNewBlackName(name) )
		{
			SetVisable(false);
			return;
		}
	}
	else if( type == RelationDefine::Teacher )
	{
		char szTemp[1024] = {0};
		MeSprintf_s(szTemp, sizeof(szTemp)/sizeof(char) - 1, theXmlString.GetString(eText_InviteTeacher),name);
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szTemp );
	}
	else if( type == RelationDefine::Student )
	{
		char szTemp[1024] = {0};
		MeSprintf_s(szTemp, sizeof(szTemp)/sizeof(char) - 1, theXmlString.GetString(eText_InviteStudent),name);
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szTemp );
	}

	MsgAddRelationReq msg;
	msg.uchGroupID = nGroup;
	msg.stRelation = type;
	strncpy(msg.szName, name, sizeof(msg.szName)-1);
	GettheNetworkInput().SendMsg( &msg );

}

void CUI_ID_FRAME_AddFriend::SetPrivateName( const char* szName )
{
	if (szName)
	{
		m_szName = szName;
	}
	else
	{
		m_szName.clear();
	}
}
