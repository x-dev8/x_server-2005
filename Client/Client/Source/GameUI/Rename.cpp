/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\Rename.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Rename.h"
#include "MeUi/UiManager.h"
#include "GlobalDef.h"
#include "UIMgr.h"
#include "FuncPerformanceLog.h"
#include "create.h"
#include "AddMember.h"
#include "chatcheck.h"
#include "XmlStringLanguage.h"
#include"MessageBox.h"
#include "core/Name.h"
#include "Pet.h"
#include "Gang.h"
#include "PetRbtnMenu.h"
#include "Create.h"
#include "ui/ChatSet.h"
#include "ChangeEquip.h"
#include "ui/FriendDlg.h"
#include "PlayerRole.h"
#include "SystemStallage.h"
#include "SuAnimal.h"
#include "ScreenInfoManager.h"
#include "ui/GuildBaseInfo.h"
extern HWND g_hWnd;

CUI_ID_FRAME_Rename s_CUI_ID_FRAME_Rename;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Rename, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Rename, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_Rename, ID_EDIT_AddNameOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Rename, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Rename, ID_BUTTON_CancleOnButtonClick )
CUI_ID_FRAME_Rename::CUI_ID_FRAME_Rename()
{
	// Member
	m_pID_FRAME_Rename = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_PICTURE_Wall = NULL;
	m_pID_EDIT_AddName = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancle = NULL;

	eType = 0;
}
// Frame
bool CUI_ID_FRAME_Rename::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_Rename::OnFrameRender()
{
	return true;
}
// Edit
void CUI_ID_FRAME_Rename::ID_EDIT_AddNameOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_Rename)
		return;
	ID_BUTTON_OKOnButtonClick(m_pID_BUTTON_OK);
}
// Button
bool CUI_ID_FRAME_Rename::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_Rename)
		return false;
	const char* name = m_pID_EDIT_AddName->GetText();
	if( strlen(name) == 0 || CChatCheck::getInstance()->CheckStringInLow(name) == false || CChatCheck::getInstance()->CheckStringInForbit(name) )
	{
		int nStringId = eCreate_NameError;
		if (eType == eChangeSignature || eType == eChangeFriendTag || eType ==eChangeStallName)
		{
			nStringId = eText_WordError;
		}
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( nStringId ));
	}
	else
	{
		if (eType == eChangeHorse)
		{
			s_CUI_ID_FRAME_Pet.ChangePetName(name);
		}
		else if (eType == eChangeTong)
		{
			//s_CUI_ID_FRAME_Gang.ChangeFamilyName(name);
			s_CUI_ID_FRAME_GuildBaseInfo.ChangeFamilyName(name);
		}
		else if (eType == eChangeSignature)
		{
			s_CUI_ID_FRAME_Friend.ChangeSignature(name);
		}
		else if (eType == eChangeFriendGroup)
		{
			if(thePlayerRole.GetGroupIndex(name) != -1)
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs,theXmlString.GetString( eFriend_Error_GroupRepeat) );
				m_pID_EDIT_AddName->SetText("");
				return true;
			}
			else
			{
				s_CUI_ID_FRAME_Friend.ChangeFriendGroupName(name);
			}
		}
		else if (eType == eAddFriendGroup)
		{
			if(thePlayerRole.GetGroupIndex(name) != -1)
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString( eFriend_Error_GroupRepeat ) );
				m_pID_EDIT_AddName->SetText("");
				return true;
			}
			else
			{
				s_CUI_ID_FRAME_Friend.AddFriendGroup(name);
			}
		}
		else if (eType == eChangeFriendTag)
		{
			s_CUI_ID_FRAME_Friend.ChangeFriendTag(name);
		}
		else if( eType == eChangeChatChannel )
		{
			s_CUI_ID_FRAME_ChatSet.AddChannel( name );
		}
        else if( eType == eChangeStallName )
        {
            CSystemStallage::Instance()->TellStallageName( name );
        }
		else if( eType == eChangeSuAnimal )
		{
			s_CUI_ID_FRAME_SuAnimal.ChangePetName(name);
		}
		else
		{
			s_CUI_ID_FRAME_PetRBMenu.ChangePetName(name);
		}
	}
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_Rename::ID_BUTTON_CancleOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_Rename)
		return false;
	SetVisable(false);
	return true;
}

static void ID_FRAME_Rename_onVisibleChanged( ControlObject* pObject )
{
	if ( !pObject->IsVisable() )
	{
		ImmAssociateContext( g_hWnd, NULL );
	}
}

// 装载UI
bool CUI_ID_FRAME_Rename::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Rename.MEUI",true,UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Rename.MEUI]失败")
		return false;
	}
	else if ( dwResult != 1/*文件版本号*/ )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Rename.MEUI]与源代码版本不一样")
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Rename::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Rename, s_CUI_ID_FRAME_RenameOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Rename, s_CUI_ID_FRAME_RenameOnFrameRender );
	theUiManager.OnEditEnter( ID_FRAME_Rename, ID_EDIT_AddName, s_CUI_ID_FRAME_RenameID_EDIT_AddNameOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_Rename, ID_BUTTON_OK, s_CUI_ID_FRAME_RenameID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Rename, ID_BUTTON_Cancle, s_CUI_ID_FRAME_RenameID_BUTTON_CancleOnButtonClick );

	m_pID_FRAME_Rename = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Rename );
	m_pID_TEXT_Msg = (ControlText*)theUiManager.FindControl( ID_FRAME_Rename, ID_TEXT_Msg );
	m_pID_PICTURE_Wall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Rename, ID_PICTURE_Wall );
	m_pID_EDIT_AddName = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Rename, ID_EDIT_AddName );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_Rename, ID_BUTTON_OK );
	m_pID_BUTTON_Cancle = (ControlButton*)theUiManager.FindControl( ID_FRAME_Rename, ID_BUTTON_Cancle );
	assert( m_pID_FRAME_Rename );
	assert( m_pID_TEXT_Msg );
	assert( m_pID_PICTURE_Wall );
	assert( m_pID_EDIT_AddName );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancle );

	m_pID_FRAME_Rename->SetOnVisibleChangedFun(ID_FRAME_Rename_onVisibleChanged);
	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Rename::_UnLoadUI()
{
	m_pID_FRAME_Rename = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_PICTURE_Wall = NULL;
	m_pID_EDIT_AddName = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancle = NULL;

	eType = 0;
	return theUiManager.RemoveFrame( "Data\\UI\\Rename.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Rename::_IsVisable()
{
    if(!m_pID_FRAME_Rename)
        return false;

	return m_pID_FRAME_Rename->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Rename::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_Rename )
		return;
	m_pID_FRAME_Rename->SetVisable( bVisable );
	if (bVisable)
	{
		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );

		theUiManager.SetFocus(m_pID_EDIT_AddName);

		m_pID_EDIT_AddName->SetText("");
		m_pID_EDIT_AddName->SetMaxLength(4);
		switch (eType)
		{
		case eChangeHorse:
			m_pID_TEXT_Msg->SetText(theXmlString.GetString(eText_ChangeHorseName));
			break;
		case eChangePet:
			m_pID_TEXT_Msg->SetText(theXmlString.GetString(eText_ChangePetName));
			break;
		case eChangeTong:
			m_pID_TEXT_Msg->SetText(theXmlString.GetString(eTextTong_ModifyName));
			break;
		case eChangeSignature:
			m_pID_TEXT_Msg->SetText(theXmlString.GetString(eFriend_MySignature));
			m_pID_EDIT_AddName->SetMaxLength(10);
			break;
		case eChangeFriendGroup:
			m_pID_TEXT_Msg->SetText(theXmlString.GetString(eFriend_GroupName));
			break;
		case eAddFriendGroup:
			m_pID_TEXT_Msg->SetText(theXmlString.GetString(eFriend_GroupName));
			break;
		case eChangeFriendTag:
			m_pID_TEXT_Msg->SetText(theXmlString.GetString(eFriend_FriendTag));
			m_pID_EDIT_AddName->SetMaxLength(10);
			break;
		case eChangeChatChannel:
			m_pID_TEXT_Msg->SetText( theXmlString.GetString( eText_NewChannel ) );
			break;
        case eChangeStallName:
            m_pID_EDIT_AddName->SetMaxLength( 11 );
            m_pID_TEXT_Msg->SetText( theXmlString.GetString( eText_Stallage_ChangeName ) );
            break;
		case eChangeSuAnimal:
			m_pID_TEXT_Msg->SetText(theXmlString.GetString(eText_ChangeMountName));
			break;
		}
	}
}

bool CUI_ID_FRAME_Rename::EditInputIsVisable()
{
	guardfunc;
	if( !m_pID_FRAME_Rename )
		return false;

	if( m_pID_EDIT_AddName )
	{
		return (theUiManager.GetFocus() == m_pID_EDIT_AddName);
	}
	return FALSE;
	unguard;

}