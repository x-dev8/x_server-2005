/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\家族(8)\家族\FamilyCreate.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "NetworkInput.h"
#include "FamilyMessage.h"
#include "FamilyCreate.h"
#include "FamilyLogo.h"
#include "Create.h"
#include "FamilyConfig.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "Common.h"
#include "ChatCheck.h"
#include "ScreenInfoManager.h"
#include "GameMain.h"

CUI_ID_FRAME_Family_Create s_CUI_ID_FRAME_Family_Create;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Family_Create, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Family_Create, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Family_Create, ID_BUTTON_helpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Family_Create, ID_BUTTON_CREATEOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_Family_Create, ID_EDIT_GUILDNAMEOnEditEnter )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_Family_Create, ID_COMBOBOX_FORCEOnComboBoxChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Family_Create, ID_CHECKBOX_MoOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Family_Create, ID_CHECKBOX_HuiOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Family_Create, ID_BUTTON_closeOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_Family_Create, ID_EDIT_CreedOnEditEnter )
CUI_ID_FRAME_Family_Create::CUI_ID_FRAME_Family_Create()
{
	// Member
	m_pID_FRAME_Family_Create = NULL;
	m_pID_PICTURE_14498 = NULL;
	m_pID_BUTTON_help = NULL;
	m_pID_BUTTON_CREATE = NULL;
	m_pID_PICTURE_14643 = NULL;
	m_pID_PICTURE_14644 = NULL;
	m_pID_PICTURE_4178 = NULL;
	m_pID_EDIT_GUILDNAME = NULL;
	m_pID_PICTURE_14642 = NULL;
	m_pID_COMBOBOX_FORCE = NULL;
	m_pID_CHECKBOX_Mo = NULL;
	m_pID_CHECKBOX_Hui = NULL;
	m_pID_TEXT_8819 = NULL;
	m_pID_TEXT_8820 = NULL;
	m_pID_TEXT_20021 = NULL;
	m_pID_TEXT_23295 = NULL;
	m_pID_TEXT_27540 = NULL;
	m_pID_TEXT_17832 = NULL;
	m_pID_BUTTON_close = NULL;
	m_pID_PICTURE_FrameHead = NULL;
	m_pID_TEXT_Tip = NULL;
	m_pID_TEXT_BangPaiZongZhi = NULL;
	m_pID_EDIT_Creed = NULL;

}
// Frame
bool CUI_ID_FRAME_Family_Create::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_Family_Create::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_Family_Create::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Family_Create )
		return false;
	return true;
}
// Button  创建
bool CUI_ID_FRAME_Family_Create::ID_BUTTON_CREATEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Family_Create )
		return false;

	std::wstring str = m_pID_EDIT_GUILDNAME->GetTextWString();
	unsigned int len = (unsigned int)str.length();
	//unsigned int len = (unsigned int)strlen( m_pID_EDIT_GUILDNAME->GetText() );
	const FamilyConfig::FamilyWordsLenLimits& lenconfig = theFamilyConfig.GetFamilyWordsLenLimits();
	if ( len < lenconfig.GetNameLenMin() || len > lenconfig.GetNameLenMax() )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_FamilyIncorrectName), "", 
			CUI_ID_FRAME_MessageBox::eTypeConfirm );
		return true;
	}

	//客户端预先判断是否含有非法字符
	if( CChatCheck::getInstance()->CheckStringInLow(m_Name.c_str()) == false )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, theXmlString.GetString(eText_FamilyErrorName) );
		return true;
	}

	if ( CChatCheck::getInstance()->CheckStringInLow( m_Aim.c_str() ) == false )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, theXmlString.GetString(eText_FamilyAimForbiddenWords) );
		return true;
	}


	s_CUI_ID_FRAME_FamilyLogo.SetVisable(true);
	this->SetVisable(false);
	SetFamilyName( m_pID_EDIT_GUILDNAME->GetText() );
	SetFamilyAim( m_pID_EDIT_Creed->GetText() );
	return true;
}
// Edit
void CUI_ID_FRAME_Family_Create::ID_EDIT_GUILDNAMEOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_Family_Create )
		return;
}
// ComboBox
void CUI_ID_FRAME_Family_Create::ID_COMBOBOX_FORCEOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_Family_Create )
		return;
}
// CheckBox
void CUI_ID_FRAME_Family_Create::ID_CHECKBOX_MoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Family_Create )
		return;
}
// CheckBox
void CUI_ID_FRAME_Family_Create::ID_CHECKBOX_HuiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Family_Create )
		return;
}
// Button  关闭
bool CUI_ID_FRAME_Family_Create::ID_BUTTON_closeOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Family_Create )
		return false;

	this->SetVisable(false);

	return true;
}
// Edit
void CUI_ID_FRAME_Family_Create::ID_EDIT_CreedOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_Family_Create )
		return;
}

// 装载UI
bool CUI_ID_FRAME_Family_Create::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\FamilyCreate.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\FamilyCreate.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}

static void UIFamilyCreate_OnVisibleChanged(ControlObject* pSender)
{
	if (pSender && !pSender->IsVisable())
		ImmAssociateContext( g_hWnd, NULL );
	else
		ImmAssociateContext( g_hWnd, ImmGetContext( g_hWnd ) );
}

// 关连控件
bool CUI_ID_FRAME_Family_Create::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Family_Create, s_CUI_ID_FRAME_Family_CreateOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Family_Create, s_CUI_ID_FRAME_Family_CreateOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Family_Create, ID_BUTTON_help, s_CUI_ID_FRAME_Family_CreateID_BUTTON_helpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Family_Create, ID_BUTTON_CREATE, s_CUI_ID_FRAME_Family_CreateID_BUTTON_CREATEOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_Family_Create, ID_EDIT_GUILDNAME, s_CUI_ID_FRAME_Family_CreateID_EDIT_GUILDNAMEOnEditEnter );
	theUiManager.OnComboBoxChange( ID_FRAME_Family_Create, ID_COMBOBOX_FORCE, s_CUI_ID_FRAME_Family_CreateID_COMBOBOX_FORCEOnComboBoxChange );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Family_Create, ID_CHECKBOX_Mo, s_CUI_ID_FRAME_Family_CreateID_CHECKBOX_MoOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Family_Create, ID_CHECKBOX_Hui, s_CUI_ID_FRAME_Family_CreateID_CHECKBOX_HuiOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_Family_Create, ID_BUTTON_close, s_CUI_ID_FRAME_Family_CreateID_BUTTON_closeOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_Family_Create, ID_EDIT_Creed, s_CUI_ID_FRAME_Family_CreateID_EDIT_CreedOnEditEnter );

	m_pID_FRAME_Family_Create = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Family_Create );
	m_pID_PICTURE_14498 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_PICTURE_14498 );
	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_BUTTON_help );
	m_pID_BUTTON_CREATE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_BUTTON_CREATE );
	m_pID_PICTURE_14643 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_PICTURE_14643 );
	m_pID_PICTURE_14644 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_PICTURE_14644 );
	m_pID_PICTURE_4178 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_PICTURE_4178 );
	m_pID_EDIT_GUILDNAME = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_EDIT_GUILDNAME );
	m_pID_PICTURE_14642 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_PICTURE_14642 );
	m_pID_COMBOBOX_FORCE = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_COMBOBOX_FORCE );
	m_pID_CHECKBOX_Mo = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_CHECKBOX_Mo );
	m_pID_CHECKBOX_Hui = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_CHECKBOX_Hui );
	m_pID_TEXT_8819 = (ControlText*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_TEXT_8819 );
	m_pID_TEXT_8820 = (ControlText*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_TEXT_8820 );
	m_pID_TEXT_20021 = (ControlText*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_TEXT_20021 );
	m_pID_TEXT_23295 = (ControlText*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_TEXT_23295 );
	m_pID_TEXT_27540 = (ControlText*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_TEXT_27540 );
	m_pID_TEXT_17832 = (ControlText*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_TEXT_17832 );
	m_pID_BUTTON_close = (ControlButton*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_BUTTON_close );
	m_pID_PICTURE_FrameHead = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_PICTURE_FrameHead );
	m_pID_TEXT_Tip = (ControlText*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_TEXT_Tip );
	m_pID_TEXT_BangPaiZongZhi = (ControlText*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_TEXT_BangPaiZongZhi );
	m_pID_EDIT_Creed = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Family_Create, ID_EDIT_Creed );

	assert( m_pID_FRAME_Family_Create );
	assert( m_pID_PICTURE_14498 );
	assert( m_pID_BUTTON_help );
	assert( m_pID_BUTTON_CREATE );
	assert( m_pID_PICTURE_14643 );
	assert( m_pID_PICTURE_14644 );
	assert( m_pID_PICTURE_4178 );
	assert( m_pID_EDIT_GUILDNAME );
	assert( m_pID_PICTURE_14642 );
	assert( m_pID_COMBOBOX_FORCE );
	assert( m_pID_CHECKBOX_Mo );
	assert( m_pID_CHECKBOX_Hui );
	assert( m_pID_TEXT_8819 );
	assert( m_pID_TEXT_8820 );
	assert( m_pID_TEXT_20021 );
	assert( m_pID_TEXT_23295 );
	assert( m_pID_TEXT_27540 );
	assert( m_pID_TEXT_17832 );
	assert( m_pID_BUTTON_close );
	assert( m_pID_PICTURE_FrameHead );
	assert( m_pID_TEXT_Tip );
	assert( m_pID_TEXT_BangPaiZongZhi );
	assert( m_pID_EDIT_Creed );


	//s_CUI_ID_FRAME_Family_Create->SetOnVisibleChangedFun(UIFamilyCreate_OnVisibleChanged);

	if( !s_CUI_ID_FRAME_CREATE.GetImeInstance() )
		s_CUI_ID_FRAME_CREATE.SetImeInstance( ImmGetContext( g_hWnd ) );

	ImmReleaseContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );

	const FamilyConfig::FamilyWordsLenLimits& lenconfig = theFamilyConfig.GetFamilyWordsLenLimits();

	m_pID_EDIT_GUILDNAME->SetMaxLength( lenconfig.GetNameLenMax() );
	m_pID_EDIT_Creed->SetMaxLength( lenconfig.GetAimLenMax() );		//设置家族宗旨最大输入长度


	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Family_Create::_UnLoadUI()
{
	m_pID_FRAME_Family_Create = NULL;
	m_pID_PICTURE_14498 = NULL;
	m_pID_BUTTON_help = NULL;
	m_pID_BUTTON_CREATE = NULL;
	m_pID_PICTURE_14643 = NULL;
	m_pID_PICTURE_14644 = NULL;
	m_pID_PICTURE_4178 = NULL;
	m_pID_EDIT_GUILDNAME = NULL;
	m_pID_PICTURE_14642 = NULL;
	m_pID_COMBOBOX_FORCE = NULL;
	m_pID_CHECKBOX_Mo = NULL;
	m_pID_CHECKBOX_Hui = NULL;
	m_pID_TEXT_8819 = NULL;
	m_pID_TEXT_8820 = NULL;
	m_pID_TEXT_20021 = NULL;
	m_pID_TEXT_23295 = NULL;
	m_pID_TEXT_27540 = NULL;
	m_pID_TEXT_17832 = NULL;
	m_pID_BUTTON_close = NULL;
	m_pID_PICTURE_FrameHead = NULL;
	m_pID_TEXT_Tip = NULL;
	m_pID_TEXT_BangPaiZongZhi = NULL;
	m_pID_EDIT_Creed = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\FamilyCreate.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Family_Create::_IsVisable()
{
	if ( !m_pID_FRAME_Family_Create )
		return false;
	return m_pID_FRAME_Family_Create->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Family_Create::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_Family_Create )
		return;

	if ( bVisable == true )
	{
		ResetData();
	}

	if( bVisable )
	{
		// 设置焦点	开启输入法
		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
		m_pID_EDIT_GUILDNAME->SetActivate( true );
		
	}
	else
	{
		// 关闭输入法
		ImmAssociateContext( g_hWnd, NULL );
	}

	m_pID_FRAME_Family_Create->SetVisable( bVisable );
}


bool CUI_ID_FRAME_Family_Create::EditInputIsVisable()
{
	if ( m_pID_EDIT_GUILDNAME == NULL || m_pID_EDIT_Creed == NULL )
	{
		return false;
	}
	return ( m_pID_EDIT_GUILDNAME == theUiManager.GetFocus() || m_pID_EDIT_Creed == theUiManager.GetFocus() );
}

void CUI_ID_FRAME_Family_Create::RequestCreateFamily()
{
	if ( /*m_Aim.empty() ||*/ m_Name.empty() || m_nTotem > FamilyDefine::Totem_Demon )
	{
		return;
	}
	

	MsgCreateFamilyReq msg;
	msg.nTotem = m_nTotem;
	MeSprintf( msg.szAim, sizeof(msg.szAim) - 1, m_Aim.c_str() );
	MeSprintf( msg.szName, sizeof(msg.szName) - 1, m_Name.c_str() );
	GettheNetworkInput().SendMsg( &msg );
}
void CUI_ID_FRAME_Family_Create::SetFamilyName( const char* name )
{
	if ( name != NULL )
	{
		m_Name = name;
	}

}
void CUI_ID_FRAME_Family_Create::SetFamilyAim( const char* aim )
{
	if ( aim != NULL )
	{
		m_Aim = aim;
	}

}
void CUI_ID_FRAME_Family_Create::SetFamilyTotem( unsigned char totem )
{
	m_nTotem = totem;
}

void  CUI_ID_FRAME_Family_Create::ResetData()
{
	m_pID_EDIT_GUILDNAME->SetText("");
	m_pID_EDIT_Creed->SetText("");
	m_Name = "";
	m_Aim = "";
	m_nTotem = -1;
}
