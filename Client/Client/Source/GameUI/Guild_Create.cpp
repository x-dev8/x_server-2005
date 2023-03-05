/********************************************************************
Created by UIEditor.exe
FileName: E:\Work\Run\Client\UI\Guild_Create.cpp
*********************************************************************/
#include <assert.h>
#include "GameMain.h"
#include "MeUi/UiManager.h"
#include "GlobalDef.h"
#include "UIMgr.h"
#include "FuncPerformanceLog.h"
#include "XmlStringLanguage.h"
#include "create.h"
#include "Guild_Create.h"
#include "ChatInfoBox.h"
#include "chatcheck.h"
#include "core/Name.h"
#include "color_config.h"
#include "Ui/InfoList.h"

CUI_ID_FRAME_GUILD_CREATE s_CUI_ID_FRAME_GUILD_CREATE;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GUILD_CREATE, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GUILD_CREATE, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GUILD_CREATE, ID_BUTTON_closeOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GUILD_CREATE, ID_BUTTON_helpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GUILD_CREATE, ID_BUTTON_CREATEOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GUILD_CREATE, ID_EDIT_GUILDNAMEOnEditEnter )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_GUILD_CREATE, ID_COMBOBOX_FORCEOnComboBoxChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GUILD_CREATE, ID_CHECKBOX_MoOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GUILD_CREATE, ID_CHECKBOX_HuiOnCheckBoxCheck )
MAP_EDIT_ENTER_CALLBACK(s_CUI_ID_FRAME_GUILD_CREATE,ID_EDIT_GUILD_CREEDOnEditEnter)
CUI_ID_FRAME_GUILD_CREATE::CUI_ID_FRAME_GUILD_CREATE()
{
	guardfunc;
	// SGuildMember
	m_pID_FRAME_GUILD_CREATE = NULL;
	m_pID_PICTURE_14498 = NULL;
	m_pID_BUTTON_close = NULL;
	//m_pID_BUTTON_help = NULL;
	m_pID_BUTTON_CREATE = NULL;
	m_pID_PICTURE_14642 = NULL;
	m_pID_PICTURE_14643 = NULL;
	m_pID_PICTURE_14644 = NULL;
	m_pID_PICTURE_4178 = NULL;
	m_pID_EDIT_GUILDNAME = NULL;
//	m_pID_PICTURE_4179 = NULL;
	m_pID_COMBOBOX_FORCE = NULL;
    m_pID_CHECKBOX_Mo = NULL;
    m_pID_CHECKBOX_Hui = NULL;
	m_pID_EDIT_Creed = NULL;

	m_nNpcID = -1;
	unguard;

}
// Frame
bool CUI_ID_FRAME_GUILD_CREATE::OnFrameRun()
{
	guardfunc;
	return true;
	unguard;
}
bool CUI_ID_FRAME_GUILD_CREATE::OnFrameRender()
{
	guardfunc;
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_GUILD_CREATE::ID_BUTTON_closeOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_GUILD_CREATE )
		return false;
    SetVisable(false);
	return true;
	unguard;
}
// Button
// bool CUI_ID_FRAME_GUILD_CREATE::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	guardfunc;
// 	if( !m_pID_FRAME_GUILD_CREATE )
// 		return false;
// 	return true;
// 	unguard;
// }

// Button
bool CUI_ID_FRAME_GUILD_CREATE::ID_BUTTON_CREATEOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_GUILD_CREATE )
		return false;
	int nLen = wcslen(m_pID_EDIT_GUILDNAME->GetTextW());

	//公会名称做字符检查
	bool bIsInLow		= CChatCheck::getInstance()->CheckStringInLow(m_pID_EDIT_GUILDNAME->GetText());
	bool bIsForbit_1	= CChatCheck::getInstance()->CheckStringInLow(m_pID_EDIT_Creed->GetText());
	if (!bIsInLow )//屏蔽字
	{
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, theXmlString.GetString( eTextGuild_Create_Error_Name_Check ) );
		return	false;
	}
	if (!bIsForbit_1)
	{//帮派宗旨中含有非法字符
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, theXmlString.GetString( eTextGuild_CreedForbindText ) );
		return false;
	}
	if( nLen <= 0)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, theXmlString.GetString( eTextGuild_Create_Error_Name_None ) );
		return false;
	}
	else if( nLen > GuildDefine::MaxNameLength /2 )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, theXmlString.GetString( eTextGuild_Create_Error_Name_Length ) );
		return false;  
	}

    if(strchr(m_pID_EDIT_GUILDNAME->GetText(), ' ') != NULL)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, theXmlString.GetString( eTextGuild_Create_Error_Name_Check ) );
        return false;
    }

	std::string stNameInLow[2] ={"'",","};

	if(strstr(m_pID_EDIT_GUILDNAME->GetText(), stNameInLow[0].c_str()) != NULL)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, theXmlString.GetString( eTextGuild_Create_Error_Name_Check ) );
		return false;
	}
	if(strstr(m_pID_EDIT_GUILDNAME->GetText(), stNameInLow[1].c_str()) != NULL)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, theXmlString.GetString( eTextGuild_Create_Error_Name_Check ) );
		return false;
	}

	MsgCreateGuildReq create;
	memset(create.szName, 0, GuildDefine::MaxNameLength);
	strncpy(create.szName, m_pID_EDIT_GUILDNAME->GetText(), GuildDefine::MaxNameLength - 1);
	if(m_pID_EDIT_Creed)
	{
		strncpy(create.szAim, m_pID_EDIT_Creed->GetText(), GuildDefine::MaxAimLength - 1);
	}
	GettheNetworkInput().SendMsg( &create );
	SetVisable(false);
	return true;
	unguard;
}
void CUI_ID_FRAME_GUILD_CREATE::ID_EDIT_GUILD_CREEDOnEditEnter(ControlObject* pSender, const char* szData)
{
	if (m_pID_FRAME_GUILD_CREATE)
	{
		m_pID_EDIT_Creed->SetActivate(true);
	}
}
// Edit
void CUI_ID_FRAME_GUILD_CREATE::ID_EDIT_GUILDNAMEOnEditEnter( ControlObject* pSender, const char* szData )
{
	guardfunc;
	if( !m_pID_FRAME_GUILD_CREATE )
		return;
	ID_BUTTON_CREATEOnButtonClick(m_pID_BUTTON_CREATE);
	unguard;
}
// ComboBox
void CUI_ID_FRAME_GUILD_CREATE::ID_COMBOBOX_FORCEOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	guardfunc;
	if( !m_pID_FRAME_GUILD_CREATE )
		return;
	unguard;
}

void CUI_ID_FRAME_GUILD_CREATE::ID_CHECKBOX_MoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
    guardfunc;
	if( !m_pID_FRAME_GUILD_CREATE )
		return;
    if(*pbChecked)
    {
        m_pID_CHECKBOX_Hui->SetCheck(false);
    }
    unguard;
}
void CUI_ID_FRAME_GUILD_CREATE::ID_CHECKBOX_HuiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  )
{
    guardfunc;
	if( !m_pID_FRAME_GUILD_CREATE )
		return;
    if(*pbChecked)
    {
        m_pID_CHECKBOX_Mo->SetCheck(false);
    }
    unguard;
}

// 装载UI
bool CUI_ID_FRAME_GUILD_CREATE::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\Guild_Create.meui", false, UI_Render_LayerSecond );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\Guild_Create.UI]失败")
			return false;
	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_GUILD_CREATE::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_GUILD_CREATE, s_CUI_ID_FRAME_GUILD_CREATEOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GUILD_CREATE, s_CUI_ID_FRAME_GUILD_CREATEOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GUILD_CREATE, ID_BUTTON_close, s_CUI_ID_FRAME_GUILD_CREATEID_BUTTON_closeOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_GUILD_CREATE, ID_BUTTON_help, s_CUI_ID_FRAME_GUILD_CREATEID_BUTTON_helpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GUILD_CREATE, ID_BUTTON_CREATE, s_CUI_ID_FRAME_GUILD_CREATEID_BUTTON_CREATEOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_GUILD_CREATE, ID_EDIT_GUILDNAME, s_CUI_ID_FRAME_GUILD_CREATEID_EDIT_GUILDNAMEOnEditEnter );
	theUiManager.OnComboBoxChange( ID_FRAME_GUILD_CREATE, ID_COMBOBOX_FORCE, s_CUI_ID_FRAME_GUILD_CREATEID_COMBOBOX_FORCEOnComboBoxChange );
    theUiManager.OnCheckBoxCheck( ID_FRAME_GUILD_CREATE, ID_CHECKBOX_Mo, s_CUI_ID_FRAME_GUILD_CREATEID_CHECKBOX_MoOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_GUILD_CREATE, ID_CHECKBOX_Hui, s_CUI_ID_FRAME_GUILD_CREATEID_CHECKBOX_HuiOnCheckBoxCheck );

	m_pID_FRAME_GUILD_CREATE = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GUILD_CREATE );
	m_pID_PICTURE_14498 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GUILD_CREATE, ID_PICTURE_14498 );
	m_pID_BUTTON_close = (ControlButton*)theUiManager.FindControl( ID_FRAME_GUILD_CREATE, ID_BUTTON_close );
	//m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_GUILD_CREATE, ID_BUTTON_help );
	m_pID_BUTTON_CREATE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GUILD_CREATE, ID_BUTTON_CREATE );
	m_pID_PICTURE_14642 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GUILD_CREATE, ID_PICTURE_14642 );
	m_pID_PICTURE_14643 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GUILD_CREATE, ID_PICTURE_14643 );
	m_pID_PICTURE_14644 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GUILD_CREATE, ID_PICTURE_14644 );
	m_pID_PICTURE_4178 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GUILD_CREATE, ID_PICTURE_4178 );
	m_pID_EDIT_GUILDNAME = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GUILD_CREATE, ID_EDIT_GUILDNAME );
	//m_pID_PICTURE_4179 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GUILD_CREATE, ID_PICTURE_4179 );
	m_pID_COMBOBOX_FORCE = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_GUILD_CREATE, ID_COMBOBOX_FORCE );
    m_pID_CHECKBOX_Mo = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GUILD_CREATE, ID_CHECKBOX_Mo );
    m_pID_CHECKBOX_Hui = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GUILD_CREATE, ID_CHECKBOX_Hui );
	m_pID_EDIT_Creed = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GUILD_CREATE, ID_EDIT_Creed );

	assert( m_pID_FRAME_GUILD_CREATE );
	m_pID_FRAME_GUILD_CREATE->SetVisable( false );
	assert( m_pID_PICTURE_14498 );
	assert( m_pID_BUTTON_close );
	//assert( m_pID_BUTTON_help );
	assert( m_pID_BUTTON_CREATE );
	assert( m_pID_PICTURE_14642 );
	assert( m_pID_PICTURE_14643 );
	assert( m_pID_PICTURE_14644 );
	assert( m_pID_PICTURE_4178 );
	assert( m_pID_EDIT_GUILDNAME );
	assert( m_pID_COMBOBOX_FORCE );
    assert( m_pID_CHECKBOX_Mo );
    assert( m_pID_CHECKBOX_Mo );
	assert( m_pID_EDIT_Creed );

	USE_SCRIPT( eUI_OBJECT_GuildCreate, this );

	if( !s_CUI_ID_FRAME_CREATE.GetImeInstance() )
		s_CUI_ID_FRAME_CREATE.SetImeInstance( ImmGetContext( g_hWnd ) );

	ImmReleaseContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );

    m_pID_EDIT_GUILDNAME->SetMaxLength( GuildDefine::MaxNameLength /4 );
	m_pID_EDIT_Creed->SetMaxLength(GuildDefine::MaxNoticeLength -1);
	return true;
	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_GUILD_CREATE::_UnLoadUI()
{
	guardfunc;
	CLOSE_SCRIPT( eUI_OBJECT_GuildCreate );
	m_pID_FRAME_GUILD_CREATE = NULL;
	m_pID_PICTURE_14498 = NULL;
	m_pID_BUTTON_close = NULL;
	//m_pID_BUTTON_help = NULL;
	m_pID_BUTTON_CREATE = NULL;
	m_pID_PICTURE_14642 = NULL;
	m_pID_PICTURE_14643 = NULL;
	m_pID_PICTURE_14644 = NULL;
	m_pID_PICTURE_4178 = NULL;
	m_pID_EDIT_GUILDNAME = NULL;
	//m_pID_PICTURE_4179 = NULL;
	m_pID_COMBOBOX_FORCE = NULL;
	m_pID_CHECKBOX_Mo = NULL;
	m_pID_CHECKBOX_Hui = NULL;
	m_pID_EDIT_Creed = NULL;
	return theUiManager.RemoveFrame( "data\\ui\\Guild_Create.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_GUILD_CREATE::_IsVisable()
{
	guardfunc;
	if( !m_pID_FRAME_GUILD_CREATE )
		return false;
	return m_pID_FRAME_GUILD_CREATE->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_GUILD_CREATE::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pID_FRAME_GUILD_CREATE )
		return;
	m_pID_FRAME_GUILD_CREATE->SetVisable( bVisable );
	m_pID_EDIT_GUILDNAME->SetText("");

	if( bVisable == true)
	{
		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
		m_pID_EDIT_GUILDNAME->SetActivate( true );
	}
	else
		ImmAssociateContext( g_hWnd, NULL );
	unguard;
}

bool CUI_ID_FRAME_GUILD_CREATE::EditInputIsVisable()
{
	guardfunc;
	if(m_pID_EDIT_Creed && m_pID_EDIT_GUILDNAME )
	{
		return (theUiManager.GetFocus() == m_pID_EDIT_Creed|| theUiManager.GetFocus() == m_pID_EDIT_GUILDNAME);
	}
	return FALSE;
	unguard;
}
