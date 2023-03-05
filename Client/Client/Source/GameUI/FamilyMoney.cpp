/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (13)\FamilyMoney.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "FamilyMessage.h"
#include "NetworkInput.h"
#include "PlayerRole.h"
#include "FamilyMoney.h"

CUI_ID_FRAME_GUILD_FamilyMoney s_CUI_ID_FRAME_GUILD_FamilyMoney;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GUILD_FamilyMoney, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GUILD_FamilyMoney, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GUILD_FamilyMoney, ID_BUTTON_CREATEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GUILD_FamilyMoney, ID_BUTTON_closeOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GUILD_FamilyMoney, ID_EDIT_JinOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GUILD_FamilyMoney, ID_EDIT_YinOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GUILD_FamilyMoney, ID_EDIT_TongOnEditEnter )
CUI_ID_FRAME_GUILD_FamilyMoney::CUI_ID_FRAME_GUILD_FamilyMoney()
{
	// Member
	m_pID_FRAME_GUILD_FamilyMoney = NULL;
	m_pID_BUTTON_CREATE = NULL;
	m_pID_BUTTON_close = NULL;
	m_pID_EDIT_Jin = NULL;
	m_pID_EDIT_Yin = NULL;
	m_pID_EDIT_Tong = NULL;

}

bool CUI_ID_FRAME_GUILD_FamilyMoney::EditInputIsVisable()
{
	if ( m_pID_EDIT_Jin == NULL || m_pID_EDIT_Yin == NULL || m_pID_EDIT_Tong == NULL )
	{
		return false;
	}
	return ( m_pID_EDIT_Jin == theUiManager.GetFocus() || m_pID_EDIT_Yin == theUiManager.GetFocus() || m_pID_EDIT_Tong == theUiManager.GetFocus() );
}

// Frame
bool CUI_ID_FRAME_GUILD_FamilyMoney::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_GUILD_FamilyMoney::OnFrameRender()
{
	return true;
}
// Button 确定
bool CUI_ID_FRAME_GUILD_FamilyMoney::ID_BUTTON_CREATEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GUILD_FamilyMoney )
		return false;
	std::string strJin = m_pID_EDIT_Jin->GetText();
	std::string strYin = m_pID_EDIT_Yin->GetText();
	std::string strTong = m_pID_EDIT_Tong->GetText();

	MsgFamilyDonateReq msg;
	msg.nMoney = 0;
	if ( !strJin.empty() )
	{
		msg.nMoney += unsigned int(10000 * atoi(strJin.c_str())) ;
	}
	if ( !strYin.empty() )
	{
		msg.nMoney += unsigned int(100 * atoi(strYin.c_str()));
	}
	if ( !strTong.empty() )
	{
		msg.nMoney += unsigned int(atoi(strTong.c_str()));
	}
	
	GettheNetworkInput().SendMsg(&msg);
	

	this->SetVisable(false);
	return true;
}
// Button 取消
bool CUI_ID_FRAME_GUILD_FamilyMoney::ID_BUTTON_closeOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GUILD_FamilyMoney )
		return false;
	this->SetVisable(false);
	return true;
}
// Edit
void CUI_ID_FRAME_GUILD_FamilyMoney::ID_EDIT_JinOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_GUILD_FamilyMoney )
		return;
	
}
// Edit
void CUI_ID_FRAME_GUILD_FamilyMoney::ID_EDIT_YinOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_GUILD_FamilyMoney )
		return;

}
// Edit
void CUI_ID_FRAME_GUILD_FamilyMoney::ID_EDIT_TongOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_GUILD_FamilyMoney )
		return;

}

void CUI_ID_FRAME_GUILD_FamilyMoney::CheckInput()
{
	std::string strJin = m_pID_EDIT_Jin->GetText();
	std::string strYin = m_pID_EDIT_Yin->GetText();
	std::string strTong = m_pID_EDIT_Tong->GetText();

	DWORD money = 0;
	if ( !strJin.empty() )
	{
		money += unsigned int(10000 * atoi(strJin.c_str())) ;
	}
	if ( !strYin.empty() )
	{
		money += unsigned int(100 * atoi(strYin.c_str()));
	}
	if ( !strTong.empty() )
	{
		money += unsigned int(atoi(strTong.c_str()));
	}

	DWORD dwSrcMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
	if ( money == 0 || money > dwSrcMoney )
	{
		m_pID_BUTTON_CREATE->SetEnable(false);
	}
	else
	{
		m_pID_BUTTON_CREATE->SetEnable(true);
	}
	
}

// 装载UI
bool CUI_ID_FRAME_GUILD_FamilyMoney::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\FamilyMoney.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\FamilyMoney.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}

// on edit text change
void OnJinTextChanged( ControlObject* pSender, const char *szData )
{
	s_CUI_ID_FRAME_GUILD_FamilyMoney.CheckInput();
}

void OnYinTextChanged( ControlObject* pSender, const char *szData )
{
	s_CUI_ID_FRAME_GUILD_FamilyMoney.CheckInput();
}

void OnTongTextChanged( ControlObject* pSender, const char *szData )
{
	s_CUI_ID_FRAME_GUILD_FamilyMoney.CheckInput();
}

// 关连控件
bool CUI_ID_FRAME_GUILD_FamilyMoney::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GUILD_FamilyMoney, s_CUI_ID_FRAME_GUILD_FamilyMoneyOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GUILD_FamilyMoney, s_CUI_ID_FRAME_GUILD_FamilyMoneyOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GUILD_FamilyMoney, ID_BUTTON_CREATE, s_CUI_ID_FRAME_GUILD_FamilyMoneyID_BUTTON_CREATEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GUILD_FamilyMoney, ID_BUTTON_close, s_CUI_ID_FRAME_GUILD_FamilyMoneyID_BUTTON_closeOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_GUILD_FamilyMoney, ID_EDIT_Jin, s_CUI_ID_FRAME_GUILD_FamilyMoneyID_EDIT_JinOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_GUILD_FamilyMoney, ID_EDIT_Yin, s_CUI_ID_FRAME_GUILD_FamilyMoneyID_EDIT_YinOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_GUILD_FamilyMoney, ID_EDIT_Tong, s_CUI_ID_FRAME_GUILD_FamilyMoneyID_EDIT_TongOnEditEnter );

	m_pID_FRAME_GUILD_FamilyMoney = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GUILD_FamilyMoney );
	m_pID_BUTTON_CREATE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyMoney, ID_BUTTON_CREATE );
	m_pID_BUTTON_close = (ControlButton*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyMoney, ID_BUTTON_close );
	m_pID_EDIT_Jin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyMoney, ID_EDIT_Jin );
	m_pID_EDIT_Yin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyMoney, ID_EDIT_Yin );
	m_pID_EDIT_Tong = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GUILD_FamilyMoney, ID_EDIT_Tong );

	assert( m_pID_FRAME_GUILD_FamilyMoney );
	assert( m_pID_BUTTON_CREATE );
	assert( m_pID_BUTTON_close );
	assert( m_pID_EDIT_Jin );
	assert( m_pID_EDIT_Yin );
	assert( m_pID_EDIT_Tong );

	m_pID_EDIT_Jin->SetIsNumber( true );
	m_pID_EDIT_Yin->SetIsNumber( true );
	m_pID_EDIT_Tong->SetIsNumber( true );
	m_pID_EDIT_Jin->SetMaxLength( 5 );
	m_pID_EDIT_Yin->SetMaxLength( 2 );
	m_pID_EDIT_Tong->SetMaxLength( 2 );

	m_pID_EDIT_Jin->SetTextChangedFun(OnJinTextChanged);
	m_pID_EDIT_Yin->SetTextChangedFun(OnYinTextChanged);
	m_pID_EDIT_Tong->SetTextChangedFun(OnTongTextChanged);

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GUILD_FamilyMoney::_UnLoadUI()
{
	m_pID_FRAME_GUILD_FamilyMoney = NULL;
	m_pID_BUTTON_CREATE = NULL;
	m_pID_BUTTON_close = NULL;
	m_pID_EDIT_Jin = NULL;
	m_pID_EDIT_Yin = NULL;
	m_pID_EDIT_Tong = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\FamilyMoney.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GUILD_FamilyMoney::_IsVisable()
{
	if ( !m_pID_FRAME_GUILD_FamilyMoney )
		return false;
	return m_pID_FRAME_GUILD_FamilyMoney->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GUILD_FamilyMoney::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_GUILD_FamilyMoney )
		return;
	m_pID_FRAME_GUILD_FamilyMoney->SetVisable( bVisable );
	if ( bVisable )
	{
		m_pID_EDIT_Jin->SetText( "" );
		m_pID_EDIT_Yin->SetText( "" );
		m_pID_EDIT_Tong->SetText( "" );

		m_pID_EDIT_Tong->SetActivate(true);

		m_pID_BUTTON_CREATE->SetEnable(false);
	}
	
}
