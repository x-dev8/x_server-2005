/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\chixin.ni\桌面\密码\密码\SuperPasswordRegister.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SuperPasswordRegister.h"
#include "MessageDefine.h"
#include "ScreenInfoManager.h"
#include "XmlStringLanguage.h"
#include "MessageBox.h"
#include "color_config.h"
#include "NetworkInput.h"
#include "Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "PasswordMessage.h"

static bool s_bPressEnter = false;

CUI_ID_FRAME_SuperPasswordRegister s_CUI_ID_FRAME_SuperPasswordRegister;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SuperPasswordRegister, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SuperPasswordRegister, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SuperPasswordRegister, ID_EDIT_AddNameOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuperPasswordRegister, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuperPasswordRegister, ID_BUTTON_CancleOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SuperPasswordRegister, ID_EDIT_AddName2OnEditEnter )
CUI_ID_FRAME_SuperPasswordRegister::CUI_ID_FRAME_SuperPasswordRegister()
{
	// Member
	ResetMembers();
}

void CUI_ID_FRAME_SuperPasswordRegister::ResetMembers()
{
	m_pID_FRAME_SuperPasswordRegister = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_PICTURE_Wall = NULL;
	m_pID_EDIT_AddName = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancle = NULL;
	m_pID_TEXT_Msg2 = NULL;
	m_pID_PICTURE_Wall2 = NULL;
	m_pID_EDIT_AddName2 = NULL;
	m_pID_PICTURE_Tip = NULL;

}
// Frame
bool CUI_ID_FRAME_SuperPasswordRegister::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_SuperPasswordRegister::OnFrameRender()
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
			if( dist > 7.0f )
			{
				SetVisable( false );
			}
		}
	}

	return true;
}
// Edit
void CUI_ID_FRAME_SuperPasswordRegister::ID_EDIT_AddNameOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_SuperPasswordRegister)
		return;
}
// Button
bool CUI_ID_FRAME_SuperPasswordRegister::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_SuperPasswordRegister)
		return false;
	string sPassword1 = m_pID_EDIT_AddName->GetText();
	string sPassword2 = m_pID_EDIT_AddName2->GetText();

	Reset();

	if(sPassword1.size()<4||sPassword1.size()>15)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Store_Password, theXmlString.GetString(eText_SecondPasswordSizeError) );
		return false;
	}

	//格式判断
	for(int i=0;i<sPassword1.size();++i)
	{
		if((sPassword1[i]>0&&sPassword1[i]<48)
			||(sPassword1[i]>57&&sPassword1[i]<65)
			||(sPassword1[i]>90&&sPassword1[i]<97)
			||(sPassword1[i]>122))
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Store_Password, theXmlString.GetString(eText_SecondPasswordStyleError) );
			return false;
		}
	}

	if(sPassword1!=sPassword2)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Store_Password, theXmlString.GetString(eText_SecondPasswordDiffer) );
		return false;
	}

	MsgSetSecondPasswordReq Msg;

	strncpy_s( Msg.szPassword, sizeof( Msg.szPassword ), sPassword1.c_str(), sizeof( Msg.szPassword ) - 1 );

	GettheNetworkInput().SendMsg( &Msg );

	return true;
}
// Button
bool CUI_ID_FRAME_SuperPasswordRegister::ID_BUTTON_CancleOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_SuperPasswordRegister)
		return false;
	Reset();
	SetVisable(false);
	return true;
}
// Edit
void CUI_ID_FRAME_SuperPasswordRegister::ID_EDIT_AddName2OnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_SuperPasswordRegister)
		return;
}

// 装载UI
bool CUI_ID_FRAME_SuperPasswordRegister::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SuperPasswordRegister.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SuperPasswordRegister.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SuperPasswordRegister::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SuperPasswordRegister, s_CUI_ID_FRAME_SuperPasswordRegisterOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SuperPasswordRegister, s_CUI_ID_FRAME_SuperPasswordRegisterOnFrameRender );
	theUiManager.OnEditEnter( ID_FRAME_SuperPasswordRegister, ID_EDIT_AddName, s_CUI_ID_FRAME_SuperPasswordRegisterID_EDIT_AddNameOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_SuperPasswordRegister, ID_BUTTON_OK, s_CUI_ID_FRAME_SuperPasswordRegisterID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuperPasswordRegister, ID_BUTTON_Cancle, s_CUI_ID_FRAME_SuperPasswordRegisterID_BUTTON_CancleOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_SuperPasswordRegister, ID_EDIT_AddName2, s_CUI_ID_FRAME_SuperPasswordRegisterID_EDIT_AddName2OnEditEnter );

	m_pID_FRAME_SuperPasswordRegister = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SuperPasswordRegister );
	m_pID_TEXT_Msg = (ControlText*)theUiManager.FindControl( ID_FRAME_SuperPasswordRegister, ID_TEXT_Msg );
	m_pID_PICTURE_Wall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuperPasswordRegister, ID_PICTURE_Wall );
	m_pID_EDIT_AddName = (ControlEdit*)theUiManager.FindControl( ID_FRAME_SuperPasswordRegister, ID_EDIT_AddName );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuperPasswordRegister, ID_BUTTON_OK );
	m_pID_BUTTON_Cancle = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuperPasswordRegister, ID_BUTTON_Cancle );
	m_pID_TEXT_Msg2 = (ControlText*)theUiManager.FindControl( ID_FRAME_SuperPasswordRegister, ID_TEXT_Msg2 );
	m_pID_PICTURE_Wall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuperPasswordRegister, ID_PICTURE_Wall2 );
	m_pID_EDIT_AddName2 = (ControlEdit*)theUiManager.FindControl( ID_FRAME_SuperPasswordRegister, ID_EDIT_AddName2 );
	m_pID_PICTURE_Tip = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuperPasswordRegister, ID_PICTURE_Tip );
	assert( m_pID_FRAME_SuperPasswordRegister );
	assert( m_pID_TEXT_Msg );
	assert( m_pID_PICTURE_Wall );
	assert( m_pID_EDIT_AddName );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancle );
	assert( m_pID_TEXT_Msg2 );
	assert( m_pID_PICTURE_Wall2 );
	assert( m_pID_EDIT_AddName2 );
	assert( m_pID_PICTURE_Tip );

	m_pID_FRAME_SuperPasswordRegister->SetMsgProcFun( frame_msg );

	SetVisable(false);

	m_pID_EDIT_AddName->SetMaxLength(15);
	m_pID_EDIT_AddName2->SetMaxLength(15);

	USE_SCRIPT( eUI_OBJECT_SuperPasswordRegister, this );

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SuperPasswordRegister::_UnLoadUI()
{
	CLOSE_SCRIPT( eUI_OBJECT_SuperPasswordRegister );
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\SuperPasswordRegister.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SuperPasswordRegister::_IsVisable()
{
	if(!m_pID_FRAME_SuperPasswordRegister)
	return false;

	return m_pID_FRAME_SuperPasswordRegister->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SuperPasswordRegister::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_SuperPasswordRegister)
		return;
	m_pID_FRAME_SuperPasswordRegister->SetVisable( bVisable );
}


bool CUI_ID_FRAME_SuperPasswordRegister::Reset()
{
	if(!m_pID_FRAME_SuperPasswordRegister)
		return false;

	m_pID_EDIT_AddName->SetText("");
	m_pID_EDIT_AddName2->SetText("");

	return true;
}

ControlEdit* CUI_ID_FRAME_SuperPasswordRegister::GetEDIT_AddName2()
{
	if( !m_pID_FRAME_SuperPasswordRegister )
		return NULL;
	return m_pID_EDIT_AddName2;
}

ControlEdit* CUI_ID_FRAME_SuperPasswordRegister::GetEDIT_AddName()
{
	if( !m_pID_FRAME_SuperPasswordRegister )
		return NULL;
	return m_pID_EDIT_AddName;
}
bool CUI_ID_FRAME_SuperPasswordRegister::EditInputIsVisable()
{
	guardfunc;
	if( !m_pID_FRAME_SuperPasswordRegister )
		return false;
	if( m_pID_EDIT_AddName )
	{
		if(theUiManager.GetFocus() == m_pID_EDIT_AddName)
			return true;
	}
	if( m_pID_EDIT_AddName2 )
	{
		if(theUiManager.GetFocus() == m_pID_EDIT_AddName2)
			return true;
	}

	return FALSE;
	unguard;

}

bool CUI_ID_FRAME_SuperPasswordRegister::frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;
	if( !s_CUI_ID_FRAME_SuperPasswordRegister.IsVisable() )
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

	unguard;
}