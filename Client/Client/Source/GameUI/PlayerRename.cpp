/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\PlayerRename.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PlayerRename.h"
#include "MessageDefine.h"
#include "Rename.h"
#include "Create.h"
#include "chatcheck.h"
#include "Ui\MessageBox.h"
#include "XmlStringLanguage.h"
#include "NetworkInput.h"
#include "XmlStringLanguage.h"
#include "color_config.h"
#include "ScreenInfoManager.h"

extern HWND g_hWnd;

CUI_ID_FRAME_PlayerRename s_CUI_ID_FRAME_PlayerRename;
MAP_FRAME_RUN( s_CUI_ID_FRAME_PlayerRename, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PlayerRename, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_PlayerRename, ID_EDIT_AddNameOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PlayerRename, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PlayerRename, ID_BUTTON_CancleOnButtonClick )
CUI_ID_FRAME_PlayerRename::CUI_ID_FRAME_PlayerRename()
{
    // Member
    m_pID_FRAME_PlayerRename = NULL;
    m_pID_TEXT_Msg = NULL;
    m_pID_PICTURE_Wall = NULL;
    m_pID_EDIT_AddName = NULL;
    m_pID_BUTTON_OK = NULL;
    m_pID_BUTTON_Cancle = NULL;

}
// Frame
bool CUI_ID_FRAME_PlayerRename::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_PlayerRename::OnFrameRender()
{
	return true;
}
// Edit
void CUI_ID_FRAME_PlayerRename::ID_EDIT_AddNameOnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_PlayerRename )
		return;
    ID_BUTTON_OKOnButtonClick(m_pID_BUTTON_OK);
}
// Button
bool CUI_ID_FRAME_PlayerRename::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PlayerRename )
		return false;
    const char* name = m_pID_EDIT_AddName->GetText();
    if( strlen(name) == 0 || CChatCheck::getInstance()->CheckStringInLow(name) == false)
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Player_Rename, theXmlString.GetString(eCreate_NameError) );
    else
    {
        SendMsg(name);
    }
    SetVisable(false);

	return true;
}
// Button
bool CUI_ID_FRAME_PlayerRename::ID_BUTTON_CancleOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PlayerRename )
		return false;
    SetVisable(false);
	return true;
}

static void ID_FRAME_PlayerRename_onVisibleChanged( ControlObject* pObject )
{
    if ( !pObject->IsVisable() )
    {
        ImmAssociateContext( g_hWnd, NULL );
    }
}


// 装载UI
bool CUI_ID_FRAME_PlayerRename::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PlayerRename.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\PlayerRename.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_PlayerRename::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PlayerRename, s_CUI_ID_FRAME_PlayerRenameOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PlayerRename, s_CUI_ID_FRAME_PlayerRenameOnFrameRender );
    theUiManager.OnEditEnter( ID_FRAME_PlayerRename, ID_EDIT_AddName, s_CUI_ID_FRAME_PlayerRenameID_EDIT_AddNameOnEditEnter );
    theUiManager.OnButtonClick( ID_FRAME_PlayerRename, ID_BUTTON_OK, s_CUI_ID_FRAME_PlayerRenameID_BUTTON_OKOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_PlayerRename, ID_BUTTON_Cancle, s_CUI_ID_FRAME_PlayerRenameID_BUTTON_CancleOnButtonClick );

	m_pID_FRAME_PlayerRename = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PlayerRename );
	m_pID_TEXT_Msg = (ControlText*)theUiManager.FindControl( ID_FRAME_PlayerRename, ID_TEXT_Msg );
	m_pID_PICTURE_Wall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PlayerRename, ID_PICTURE_Wall );
	m_pID_EDIT_AddName = (ControlEdit*)theUiManager.FindControl( ID_FRAME_PlayerRename, ID_EDIT_AddName );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_PlayerRename, ID_BUTTON_OK );
	m_pID_BUTTON_Cancle = (ControlButton*)theUiManager.FindControl( ID_FRAME_PlayerRename, ID_BUTTON_Cancle );
	assert( m_pID_FRAME_PlayerRename );
	assert( m_pID_TEXT_Msg );
	assert( m_pID_PICTURE_Wall );
	assert( m_pID_EDIT_AddName );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancle );

	m_pID_EDIT_AddName->SetMaxLength(8); //人物名字改为8个字符

    m_pID_FRAME_PlayerRename->SetOnVisibleChangedFun(ID_FRAME_PlayerRename_onVisibleChanged);
    SetVisable(false);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_PlayerRename::_UnLoadUI()
{
	m_pID_FRAME_PlayerRename = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_PICTURE_Wall = NULL;
	m_pID_EDIT_AddName = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancle = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\PlayerRename.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_PlayerRename::_IsVisable()
{
	if( !m_pID_FRAME_PlayerRename )
		return false;
	return m_pID_FRAME_PlayerRename->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_PlayerRename::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_PlayerRename )
		return;

	m_pID_FRAME_PlayerRename->SetVisable( bVisable );
    if (bVisable)
    {
        ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );

        theUiManager.SetFocus(m_pID_EDIT_AddName);

        m_pID_EDIT_AddName->SetText("");
    }
}

void CUI_ID_FRAME_PlayerRename::SendMsg(const char* pszName)
{
    if(!pszName||strlen(pszName) >= dr_MaxPlayerName)
        return;

    MsgChangeNameReq msg;
	sprintf_s(msg.name,sizeof(msg.name)/sizeof(char) - 1,"%s",pszName);
    GettheNetworkInput().SendMsg(&msg);
}

bool CUI_ID_FRAME_PlayerRename::CheckVaild(const char* pszName)
{
    if(!pszName)
        return false;

    return true;
}

void CUI_ID_FRAME_PlayerRename::Clear()
{
}

bool CUI_ID_FRAME_PlayerRename::EditInputIsVisable()
{
    if( m_pID_EDIT_AddName )
    {
        return (theUiManager.GetFocus() == m_pID_EDIT_AddName);
    }
    return false;
}
