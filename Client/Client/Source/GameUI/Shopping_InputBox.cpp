/********************************************************************
Created by UIEditor.exe
FileName: E:\Work\HeroRuntime\CLIENT\UI\Shopping_InputBox.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Shopping_InputBox.h"
#include "NetworkInput.h"
#include "ItemDetail.h"
#include "ShopCenterSlk.h"
#include "FuncPerformanceLog.h"
#include "PlayerRole.h"

#include "MessageBox.h"
#include "core/Name.h"
#include "XmlStringLanguage.h"
#include "UIMgr.h"

CUI_ID_Shopping_InputBox s_CUI_ID_Shopping_InputBox;
MAP_FRAME_RUN( s_CUI_ID_Shopping_InputBox, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_Shopping_InputBox, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_Shopping_InputBox, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_Shopping_InputBox, ID_BUTTON_UPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_Shopping_InputBox, ID_BUTTON_DOWNOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_Shopping_InputBox, ID_EDIT_INPUTOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_Shopping_InputBox, ID_BUTTON_BackOnButtonClick )
CUI_ID_Shopping_InputBox::CUI_ID_Shopping_InputBox()
{
	// SGuildMember
	ResetMembers();
}
void CUI_ID_Shopping_InputBox::ResetMembers()
{
	m_pID_Shopping_InputBox = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_UP = NULL;
	m_pID_BUTTON_DOWN = NULL;
	m_pID_EDIT_INPUT = NULL;
	m_pID_TEXT_Static0 = NULL;
	m_pID_TEXT_Static1 = NULL;
	m_pID_TEXT_ItemName = NULL;
	m_pID_TEXT_ItemPrice = NULL;
	m_pID_TEXT_15393 = NULL;
	m_pID_BUTTON_Back = NULL;
	m_pID_TEXT_Note = NULL;
	m_pID_TEXT_YinPiao = NULL;

	m_pShopNode = NULL;
}
// Frame
bool CUI_ID_Shopping_InputBox::OnFrameRun()
{
	return true;
}
bool CUI_ID_Shopping_InputBox::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_Shopping_InputBox::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if( NULL == m_pID_Shopping_InputBox )
		return false;
	if( m_pShopNode == NULL )
	{
		return false;
	}
	int nCnt = atoi( m_pID_EDIT_INPUT->GetText() );
	if( nCnt <= 0 || nCnt > 99 )
		return false;

	int nPrice = m_pShopNode->Price*nCnt ;
	int nPrice2 = m_pShopNode->Price2*nCnt;

	nPrice = nPrice*thePlayerRole.m_nShopCenterOffSell;
	nPrice2 = nPrice2*thePlayerRole.m_nShopCenterOffSell;

	nPrice = nPrice/100;
	nPrice2 = nPrice2/100;

	SetVisable( FALSE );
	m_pShopNode = NULL;
	return true;
}
// Button
bool CUI_ID_Shopping_InputBox::ID_BUTTON_UPOnButtonClick( ControlObject* pSender )
{
	if( NULL == m_pID_Shopping_InputBox )
		return false;
	INT nCnt = atoi( m_pID_EDIT_INPUT->GetText() );
	if(nCnt >= 99)
		return true;
	nCnt ++;
	m_pID_EDIT_INPUT->SetText( nCnt );
	return true;
}

// Button
bool CUI_ID_Shopping_InputBox::ID_BUTTON_DOWNOnButtonClick( ControlObject* pSender )
{
	if( NULL == m_pID_Shopping_InputBox )
		return false;
	INT nCnt = atoi( m_pID_EDIT_INPUT->GetText() );
	if(nCnt<=0)
		return true;
	nCnt --;
	m_pID_EDIT_INPUT->SetText( nCnt );
	return true;
}
// Edit
void CUI_ID_Shopping_InputBox::ID_EDIT_INPUTOnEditEnter( ControlObject* pSender, const char* szData )
{
	if( NULL == m_pID_Shopping_InputBox )
		return;
}
// Button
bool CUI_ID_Shopping_InputBox::ID_BUTTON_BackOnButtonClick( ControlObject* pSender )
{
	if( NULL == m_pID_Shopping_InputBox )
		return false;
	guardfunc;
	m_UseItem = InvalidLogicNumber;
	m_pShopNode = NULL;
	SetVisable( FALSE );
	unguard;
	return true;
}

// 装载UI
bool CUI_ID_Shopping_InputBox::_LoadUI()
{
	
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\Shopping_InputBox.meui", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\Shopping_InputBox.UI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_Shopping_InputBox::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_Shopping_InputBox, s_CUI_ID_Shopping_InputBoxOnFrameRun );
	theUiManager.OnFrameRender( ID_Shopping_InputBox, s_CUI_ID_Shopping_InputBoxOnFrameRender );
	theUiManager.OnButtonClick( ID_Shopping_InputBox, ID_BUTTON_OK, s_CUI_ID_Shopping_InputBoxID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_Shopping_InputBox, ID_BUTTON_UP, s_CUI_ID_Shopping_InputBoxID_BUTTON_UPOnButtonClick );
	theUiManager.OnButtonClick( ID_Shopping_InputBox, ID_BUTTON_DOWN, s_CUI_ID_Shopping_InputBoxID_BUTTON_DOWNOnButtonClick );
	theUiManager.OnEditEnter( ID_Shopping_InputBox, ID_EDIT_INPUT, s_CUI_ID_Shopping_InputBoxID_EDIT_INPUTOnEditEnter );
	theUiManager.OnButtonClick( ID_Shopping_InputBox, ID_BUTTON_Back, s_CUI_ID_Shopping_InputBoxID_BUTTON_BackOnButtonClick );

	m_pID_Shopping_InputBox = (ControlFrame*)theUiManager.FindFrame( ID_Shopping_InputBox );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_Shopping_InputBox, ID_BUTTON_OK );
	m_pID_BUTTON_UP = (ControlButton*)theUiManager.FindControl( ID_Shopping_InputBox, ID_BUTTON_UP );
	m_pID_BUTTON_DOWN = (ControlButton*)theUiManager.FindControl( ID_Shopping_InputBox, ID_BUTTON_DOWN );
	m_pID_EDIT_INPUT = (ControlEdit*)theUiManager.FindControl( ID_Shopping_InputBox, ID_EDIT_INPUT );
	m_pID_TEXT_Static0 = (ControlText*)theUiManager.FindControl( ID_Shopping_InputBox, ID_TEXT_Static0 );
	m_pID_TEXT_Static1 = (ControlText*)theUiManager.FindControl( ID_Shopping_InputBox, ID_TEXT_Static1 );
	m_pID_TEXT_ItemName = (ControlText*)theUiManager.FindControl( ID_Shopping_InputBox, ID_TEXT_ItemName );
	m_pID_TEXT_ItemPrice = (ControlText*)theUiManager.FindControl( ID_Shopping_InputBox, ID_TEXT_ItemPrice );
	m_pID_TEXT_15393 = (ControlText*)theUiManager.FindControl( ID_Shopping_InputBox, ID_TEXT_15393 );
	m_pID_BUTTON_Back = (ControlButton*)theUiManager.FindControl( ID_Shopping_InputBox, ID_BUTTON_Back );
	m_pID_TEXT_Note = (ControlText*)theUiManager.FindControl( ID_Shopping_InputBox, ID_TEXT_Note );
	m_pID_TEXT_YinPiao = (ControlText*)theUiManager.FindControl( ID_Shopping_InputBox, ID_TEXT_YinPiao );
	assert( m_pID_Shopping_InputBox );
	m_pID_Shopping_InputBox->SetMsgProcFun( MsgProc );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_UP );
	assert( m_pID_BUTTON_DOWN );
	assert( m_pID_EDIT_INPUT );
	assert( m_pID_TEXT_Static0 );
	assert( m_pID_TEXT_Static1 );
	assert( m_pID_TEXT_ItemName );
	assert( m_pID_TEXT_ItemPrice );
	assert( m_pID_TEXT_15393 );
	assert( m_pID_BUTTON_Back );
	assert( m_pID_TEXT_Note );
	assert( m_pID_TEXT_YinPiao );
	SetVisable( false );
	m_pID_EDIT_INPUT->SetIsNumber( true );
	m_pID_EDIT_INPUT->SetMaxLength( 2 );

	USE_SCRIPT( eUI_OBJECT_Shop_InputBox, this );
	m_pID_Shopping_InputBox->SetOnEscResponseType(ControlFrame::EscResponse_SkipMe);
	return true;
}
// 卸载UI
bool CUI_ID_Shopping_InputBox::_UnLoadUI()
{
	CLOSE_SCRIPT( eUI_OBJECT_Shop_InputBox );
	ResetMembers();
	return theUiManager.RemoveFrame( "data\\ui\\Shopping_InputBox.meui" );
}
// 是否可视
bool CUI_ID_Shopping_InputBox::_IsVisable()
{
	if( NULL == m_pID_Shopping_InputBox )
		return false;
	return m_pID_Shopping_InputBox->IsVisable();
}
// 设置是否可视
void CUI_ID_Shopping_InputBox::_SetVisable( const bool bVisable )
{
	if( !m_pID_Shopping_InputBox )
		return;
	m_pID_Shopping_InputBox->SetVisable( bVisable );
	if( bVisable )
	{
		m_pID_EDIT_INPUT->SetText( 1 );
		theUiManager.SetFocus( m_pID_EDIT_INPUT );
		theUiManager.ToTop( m_pID_Shopping_InputBox );
		theUiManager.Compositor();
	}	
	if( !bVisable )
	{
		m_UseItem = InvalidLogicNumber;
		m_pShopNode = NULL;
	}
}
bool CUI_ID_Shopping_InputBox::EditInputIsVisable()
{
	guardfunc;
	if( m_pID_EDIT_INPUT )
	{
		return (theUiManager.GetFocus() == m_pID_EDIT_INPUT);
	}
	return FALSE;
	unguard;
}

bool CUI_ID_Shopping_InputBox::MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;
	if( !s_CUI_ID_Shopping_InputBox.IsVisable() )
		return false;

	switch( msg ) 
	{
	case WM_KEYUP:
		{
			if( wParam == VK_ESCAPE )
			{
				return true;
			}
			if( wParam == VK_RETURN )
			{
				s_CUI_ID_Shopping_InputBox.ID_BUTTON_OKOnButtonClick(NULL);
				return true;
			}
		}
		break;
	}

	return false;
	unguard;
}