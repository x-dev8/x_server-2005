/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\AskPresent.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "AskPresent.h"
#include "Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "MessageDefine.h"
#include "ScreenInfoManager.h"
#include "NetworkInput.h"

static bool s_bPressEnter = false;
CUI_ID_FRAME_AskPresent s_CUI_ID_FRAME_AskPresent;
MAP_FRAME_RUN( s_CUI_ID_FRAME_AskPresent, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_AskPresent, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AskPresent, ID_EDIT_SNOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AskPresent, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AskPresent, ID_BUTTON_CancelOnButtonClick )
CUI_ID_FRAME_AskPresent::CUI_ID_FRAME_AskPresent()
{
	// Member
	m_pID_FRAME_AskPresent = NULL;
	m_pID_EDIT_SN = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancel = NULL;

}
// Frame
bool CUI_ID_FRAME_AskPresent::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_AskPresent::OnFrameRender()
{
	if( s_bPressEnter )
	{
		ID_BUTTON_OKOnButtonClick(NULL);
		s_bPressEnter = false;
	}

	if( IsVisable() && (m_vVisiblePos.x!=0||m_vVisiblePos.y!=0) )
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if ( pMe )
		{
			float fMeX,fMeY,fMeZ;			
			pMe->GetPos( &fMeX, &fMeY, &fMeZ );
			float dist = pMe->GetDistToTarget( m_vVisiblePos.x, m_vVisiblePos.y );			
			if( dist > 12.0f )
			{
				SetVisable( false );
			}
		}
	}
	return true;
}
// Edit
void CUI_ID_FRAME_AskPresent::ID_EDIT_SNOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Button
bool CUI_ID_FRAME_AskPresent::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_EDIT_SN)
		return false;
	std::string str = m_pID_EDIT_SN->GetText();

	if(str.length() == 0||str.length() > 32)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Store_Password, theXmlString.GetString(eText_AskPresent_LengthError) );
		return false;
	}

	MsgAskForPresent msg;
	strncpy_s( msg.sn, sizeof( msg.sn ), str.c_str(), sizeof( msg.sn ) - 1 );

	GettheNetworkInput().SendMsg( &msg );

	Reset();

	//ImmAssociateContext( g_hWnd, NULL );
	SetVisable(false);

	return true;
}
// Button
bool CUI_ID_FRAME_AskPresent::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	Reset();
	SetVisable(false);
	return true;
}

	// 装载UI
bool CUI_ID_FRAME_AskPresent::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\AskPresent.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\AskPresent.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_AskPresent::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_AskPresent, s_CUI_ID_FRAME_AskPresentOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_AskPresent, s_CUI_ID_FRAME_AskPresentOnFrameRender );
theUiManager.OnEditEnter( ID_FRAME_AskPresent, ID_EDIT_SN, s_CUI_ID_FRAME_AskPresentID_EDIT_SNOnEditEnter );
theUiManager.OnButtonClick( ID_FRAME_AskPresent, ID_BUTTON_OK, s_CUI_ID_FRAME_AskPresentID_BUTTON_OKOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_AskPresent, ID_BUTTON_Cancel, s_CUI_ID_FRAME_AskPresentID_BUTTON_CancelOnButtonClick );

	m_pID_FRAME_AskPresent = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_AskPresent );
	m_pID_EDIT_SN = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AskPresent, ID_EDIT_SN );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_AskPresent, ID_BUTTON_OK );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_AskPresent, ID_BUTTON_Cancel );
	assert( m_pID_FRAME_AskPresent );
	assert( m_pID_EDIT_SN );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancel );

	m_pID_FRAME_AskPresent->SetMsgProcFun( FrameMsg );
	m_pID_EDIT_SN->SetMaxLength(32);

	return true;
}
	// 卸载UI
bool CUI_ID_FRAME_AskPresent::_UnLoadUI()
{
	m_pID_FRAME_AskPresent = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\AskPresent.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_AskPresent::_IsVisable()
{
	return m_pID_FRAME_AskPresent->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_AskPresent::_SetVisable( const bool bVisable )
{
	ImmAssociateContext( g_hWnd, NULL );
	m_pID_FRAME_AskPresent->SetVisable( bVisable );
}

void CUI_ID_FRAME_AskPresent::Reset()
{
	if (!m_pID_EDIT_SN)
		return;

	m_pID_EDIT_SN->SetText("");
}

ControlEdit* CUI_ID_FRAME_AskPresent::GetEDIT_AddName()
{
	if (!m_pID_FRAME_AskPresent)
		return NULL;

	return m_pID_EDIT_SN;
}

bool CUI_ID_FRAME_AskPresent::FrameMsg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	if( !s_CUI_ID_FRAME_AskPresent.IsVisable() )
		return false;

	if ( bMsgUsed == true )
		return false;

	if( msg == WM_KEYDOWN )
	{
		if( wParam == VK_RETURN )
		{
			s_bPressEnter = true;
			return true;
		}
	}

	return false;
}

bool CUI_ID_FRAME_AskPresent::EditInputIsVisable()
{
	if (!m_pID_FRAME_AskPresent)
		return false;

	if( m_pID_EDIT_SN )
	{
		if(theUiManager.GetFocus() == m_pID_EDIT_SN)
			return true;
	}

	return false;
}