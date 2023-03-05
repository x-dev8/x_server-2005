/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (13)\FamilyUI\FamilyTenet.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "FamilyCreate.h"
#include "Create.h"
#include "FamilyConfig.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "FamilyMessage.h"
#include "Common.h"
#include "NetworkInput.h"
#include "SystemFamily.h"
#include "FamilyTenet.h"

extern HWND g_hWnd;

CUI_ID_FRAME_GUILD_FamilyTenet s_CUI_ID_FRAME_GUILD_FamilyTenet;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GUILD_FamilyTenet, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GUILD_FamilyTenet, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GUILD_FamilyTenet, ID_BUTTON_CREATEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GUILD_FamilyTenet, ID_BUTTON_closeOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GUILD_FamilyTenet, ID_EDIT_ZongZhiOnEditEnter )
CUI_ID_FRAME_GUILD_FamilyTenet::CUI_ID_FRAME_GUILD_FamilyTenet()
{
	// Member
	m_pID_FRAME_GUILD_FamilyTenet = NULL;
	m_pID_BUTTON_CREATE = NULL;
	m_pID_BUTTON_close = NULL;
	m_pID_TEXT_JiaZuZongZhi = NULL;
	m_pID_EDIT_ZongZhi = NULL;

}
// Frame
bool CUI_ID_FRAME_GUILD_FamilyTenet::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_GUILD_FamilyTenet::OnFrameRender()
{
	return true;
}
// Button   创建 修改
bool CUI_ID_FRAME_GUILD_FamilyTenet::ID_BUTTON_CREATEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GUILD_FamilyTenet )
		return false;

	//unsigned int len = (unsigned int)strlen( m_pID_EDIT_ZongZhi->GetText() );
	//const FamilyConfig::FamilyWordsLenLimits& lenconfig = theFamilyConfig.GetFamilyWordsLenLimits();
	//if ( len < lenconfig.GetAimLenMin() || len > lenconfig.GetAimLenMax() )
	//{
	//	s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_FamilyAimLenIncorrect), "",
	//		CUI_ID_FRAME_MessageBox::eTypeConfirm );
	//	return true;
	//}

	//s_CUI_ID_FRAME_Family_Create.SetFamilyAim( m_pID_EDIT_ZongZhi->GetText() );
	//s_CUI_ID_FRAME_Family_Create.RequestCreateFamily();

	//std::wstring str = m_pID_EDIT_GUILDNAME->GetTextWString();
	//unsigned int len = (unsigned int)str.length();
	
	szNewAim = m_pID_EDIT_ZongZhi->GetText();

	MsgFamilyAimReq msg;
	
	MeSprintf( msg.szAim, sizeof(msg.szAim) - 1, m_pID_EDIT_ZongZhi->GetText() );
	GettheNetworkInput().SendMsg(&msg);

	this->SetVisable(false);
	return true;
}
// Button   取消
bool CUI_ID_FRAME_GUILD_FamilyTenet::ID_BUTTON_closeOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GUILD_FamilyTenet )
		return false;
	this->SetVisable(false);
	return true;
}
// Edit
void CUI_ID_FRAME_GUILD_FamilyTenet::ID_EDIT_ZongZhiOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_GUILD_FamilyTenet )
		return;
}

void CUI_ID_FRAME_GUILD_FamilyTenet::UpdateAim()
{
	CSystemFamily::Instance()->GetFamilyInfo()->SetFamilyAim( szNewAim.c_str() );
}

// 装载UI
bool CUI_ID_FRAME_GUILD_FamilyTenet::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\FamilyTenet.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\FamilyTenet.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}

static void UIFamilyTenet_OnVisibleChanged(ControlObject* pSender)
{
	if (pSender && !pSender->IsVisable())
		ImmAssociateContext( g_hWnd, NULL );
}

// 关连控件
bool CUI_ID_FRAME_GUILD_FamilyTenet::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GUILD_FamilyTenet, s_CUI_ID_FRAME_GUILD_FamilyTenetOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GUILD_FamilyTenet, s_CUI_ID_FRAME_GUILD_FamilyTenetOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GUILD_FamilyTenet, ID_BUTTON_CREATE, s_CUI_ID_FRAME_GUILD_FamilyTenetID_BUTTON_CREATEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GUILD_FamilyTenet, ID_BUTTON_close, s_CUI_ID_FRAME_GUILD_FamilyTenetID_BUTTON_closeOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_GUILD_FamilyTenet, ID_EDIT_ZongZhi, s_CUI_ID_FRAME_GUILD_FamilyTenetID_EDIT_ZongZhiOnEditEnter );

	m_pID_FRAME_GUILD_FamilyTenet = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GUILD_FamilyTenet );
	m_pID_BUTTON_CREATE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyTenet, ID_BUTTON_CREATE );
	m_pID_BUTTON_close = (ControlButton*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyTenet, ID_BUTTON_close );
	m_pID_TEXT_JiaZuZongZhi = (ControlText*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyTenet, ID_TEXT_JiaZuZongZhi );
	m_pID_EDIT_ZongZhi = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyTenet, ID_EDIT_ZongZhi );

	assert( m_pID_FRAME_GUILD_FamilyTenet );
	assert( m_pID_BUTTON_CREATE );
	assert( m_pID_BUTTON_close );
	assert( m_pID_TEXT_JiaZuZongZhi );
	assert( m_pID_EDIT_ZongZhi );

	m_pID_FRAME_GUILD_FamilyTenet->SetOnVisibleChangedFun(UIFamilyTenet_OnVisibleChanged);

	if( !s_CUI_ID_FRAME_CREATE.GetImeInstance() )
		s_CUI_ID_FRAME_CREATE.SetImeInstance( ImmGetContext( g_hWnd ) );

	ImmReleaseContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GUILD_FamilyTenet::_UnLoadUI()
{
	m_pID_FRAME_GUILD_FamilyTenet = NULL;
	m_pID_BUTTON_CREATE = NULL;
	m_pID_BUTTON_close = NULL;
	m_pID_TEXT_JiaZuZongZhi = NULL;
	m_pID_EDIT_ZongZhi = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\FamilyTenet.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GUILD_FamilyTenet::_IsVisable()
{
	if ( !m_pID_FRAME_GUILD_FamilyTenet )
		return false;
	return m_pID_FRAME_GUILD_FamilyTenet->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GUILD_FamilyTenet::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_GUILD_FamilyTenet )
		return;
	m_pID_FRAME_GUILD_FamilyTenet->SetVisable( bVisable );

	if( bVisable )
	{
		// 设置焦点	开启输入法
		m_pID_EDIT_ZongZhi->SetActivate( true );
		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );

		const FamilyConfig::FamilyWordsLenLimits& lenconfig = theFamilyConfig.GetFamilyWordsLenLimits();
		m_pID_EDIT_ZongZhi->SetMaxLength( lenconfig.GetAimLenMax() );
		m_pID_EDIT_ZongZhi->SetText( CSystemFamily::Instance()->GetFamilyInfo()->GetFamilyAim() );
	}
	else
	{
		// 关闭输入法
		ImmAssociateContext( g_hWnd, NULL );
	}
}

bool CUI_ID_FRAME_GUILD_FamilyTenet::EditInputIsVisable()
{
	if ( m_pID_EDIT_ZongZhi == NULL )
	{
		return false;
	}

	return ( m_pID_EDIT_ZongZhi == theUiManager.GetFocus() );
	
}