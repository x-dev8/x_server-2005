/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\chixin.ni\桌面\密码\密码\SuperPasswordReset.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SuperPasswordReset.h"
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

CUI_ID_FRAME_SuperPasswordReset s_CUI_ID_FRAME_SuperPasswordReset;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SuperPasswordReset, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SuperPasswordReset, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SuperPasswordReset, ID_EDIT_AddNameOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuperPasswordReset, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuperPasswordReset, ID_BUTTON_CancleOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SuperPasswordReset, ID_EDIT_AddName2OnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SuperPasswordReset, ID_EDIT_AddName3OnEditEnter )
CUI_ID_FRAME_SuperPasswordReset::CUI_ID_FRAME_SuperPasswordReset()
{
	// Member
	ResetMembers();
}

void CUI_ID_FRAME_SuperPasswordReset::ResetMembers()
{
	m_pID_FRAME_SuperPasswordReset = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_PICTURE_Wall = NULL;
	m_pID_EDIT_AddName = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancle = NULL;
	m_pID_TEXT_Msg2 = NULL;
	m_pID_PICTURE_Wall2 = NULL;
	m_pID_EDIT_AddName2 = NULL;
	m_pID_TEXT_Msg3 = NULL;
	m_pID_PICTURE_Wall3 = NULL;
	m_pID_EDIT_AddName3 = NULL;

	for (int i = 0 ; i < 3 ; i++)
	{
		AddNameArray[i] = NULL;
	}
}
// Frame
bool CUI_ID_FRAME_SuperPasswordReset::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_SuperPasswordReset::OnFrameRender()
{
	if( s_bPressEnter )
	{
		ID_BUTTON_OKOnButtonClick(NULL);
		s_bPressEnter = false;
	}

	if( IsVisable() && (m_vVisiblePos.x!=0||m_vVisiblePos.y!=0))
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
void CUI_ID_FRAME_SuperPasswordReset::ID_EDIT_AddNameOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_SuperPasswordReset)
		return;
}
// Button
bool CUI_ID_FRAME_SuperPasswordReset::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_SuperPasswordReset)
		return false;
	string sOldPassword = m_pID_EDIT_AddName->GetText();
	string sNewPassword2 = m_pID_EDIT_AddName2->GetText();
	string sNewPassword1 = m_pID_EDIT_AddName3->GetText();

	Reset();

	//长度判断
	if(sOldPassword.size()<4||sOldPassword.size()>15
		||sNewPassword1.size()<4||sNewPassword1.size()>15)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Store_Password, theXmlString.GetString(eText_SecondPasswordSizeError) );
		return false;
	}

	//格式判断
	for(int i=0;i<sOldPassword.size();++i)
	{
		if((sOldPassword[i]>0&&sOldPassword[i]<48)
			||(sOldPassword[i]>57&&sOldPassword[i]<65)
			||(sOldPassword[i]>90&&sOldPassword[i]<97)
			||(sOldPassword[i]>122))
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Store_Password, theXmlString.GetString(eText_SecondPasswordStyleError) );
			return false;
		}
	}

	for(int i=0;i<sNewPassword1.size();++i)
	{
		if((sNewPassword1[i]>0&&sNewPassword1[i]<48)
			||(sNewPassword1[i]>57&&sNewPassword1[i]<65)
			||(sNewPassword1[i]>90&&sNewPassword1[i]<97)
			||(sNewPassword1[i]>122))
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Store_Password, theXmlString.GetString(eText_SecondPasswordStyleError) );
			return false;
		}
	}
	
	//匹配判断
	if( sNewPassword1 != sNewPassword2 )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Store_Password, theXmlString.GetString(eText_SecondPasswordDiffer) );
		return false;
	}

	MsgReSetSecondPasswordReq Msg;

	strncpy_s( Msg.szOldPassword, sizeof( Msg.szOldPassword ), sOldPassword.c_str(),sizeof( Msg.szOldPassword ) - 1 );
	strncpy_s( Msg.szNewPassword, sizeof( Msg.szNewPassword ), sNewPassword1.c_str(),sizeof( Msg.szNewPassword ) - 1 );

	GettheNetworkInput().SendMsg( &Msg );

	return true;
}
// Button
bool CUI_ID_FRAME_SuperPasswordReset::ID_BUTTON_CancleOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_SuperPasswordReset)
		return false;
	Reset();
	SetVisable(false);
	return true;
}
// Edit
void CUI_ID_FRAME_SuperPasswordReset::ID_EDIT_AddName2OnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_SuperPasswordReset)
		return;
}
// Edit
void CUI_ID_FRAME_SuperPasswordReset::ID_EDIT_AddName3OnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_SuperPasswordReset)
		return;
}

// 装载UI
bool CUI_ID_FRAME_SuperPasswordReset::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SuperPasswordReset.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SuperPasswordReset.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SuperPasswordReset::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SuperPasswordReset, s_CUI_ID_FRAME_SuperPasswordResetOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SuperPasswordReset, s_CUI_ID_FRAME_SuperPasswordResetOnFrameRender );
	theUiManager.OnEditEnter( ID_FRAME_SuperPasswordReset, ID_EDIT_AddName, s_CUI_ID_FRAME_SuperPasswordResetID_EDIT_AddNameOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_SuperPasswordReset, ID_BUTTON_OK, s_CUI_ID_FRAME_SuperPasswordResetID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuperPasswordReset, ID_BUTTON_Cancle, s_CUI_ID_FRAME_SuperPasswordResetID_BUTTON_CancleOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_SuperPasswordReset, ID_EDIT_AddName2, s_CUI_ID_FRAME_SuperPasswordResetID_EDIT_AddName2OnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_SuperPasswordReset, ID_EDIT_AddName3, s_CUI_ID_FRAME_SuperPasswordResetID_EDIT_AddName3OnEditEnter );

	m_pID_FRAME_SuperPasswordReset = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SuperPasswordReset );
	m_pID_TEXT_Msg = (ControlText*)theUiManager.FindControl( ID_FRAME_SuperPasswordReset, ID_TEXT_Msg );
	m_pID_PICTURE_Wall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuperPasswordReset, ID_PICTURE_Wall );
	m_pID_EDIT_AddName = (ControlEdit*)theUiManager.FindControl( ID_FRAME_SuperPasswordReset, ID_EDIT_AddName );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuperPasswordReset, ID_BUTTON_OK );
	m_pID_BUTTON_Cancle = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuperPasswordReset, ID_BUTTON_Cancle );
	m_pID_TEXT_Msg2 = (ControlText*)theUiManager.FindControl( ID_FRAME_SuperPasswordReset, ID_TEXT_Msg2 );
	m_pID_PICTURE_Wall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuperPasswordReset, ID_PICTURE_Wall2 );
	m_pID_EDIT_AddName2 = (ControlEdit*)theUiManager.FindControl( ID_FRAME_SuperPasswordReset, ID_EDIT_AddName2 );
	m_pID_TEXT_Msg3 = (ControlText*)theUiManager.FindControl( ID_FRAME_SuperPasswordReset, ID_TEXT_Msg3 );
	m_pID_PICTURE_Wall3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuperPasswordReset, ID_PICTURE_Wall3 );
	m_pID_EDIT_AddName3 = (ControlEdit*)theUiManager.FindControl( ID_FRAME_SuperPasswordReset, ID_EDIT_AddName3 );
	assert( m_pID_FRAME_SuperPasswordReset );
	assert( m_pID_TEXT_Msg );
	assert( m_pID_PICTURE_Wall );
	assert( m_pID_EDIT_AddName );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancle );
	assert( m_pID_TEXT_Msg2 );
	assert( m_pID_PICTURE_Wall2 );
	assert( m_pID_EDIT_AddName2 );
	assert( m_pID_TEXT_Msg3 );
	assert( m_pID_PICTURE_Wall3 );
	assert( m_pID_EDIT_AddName3 );

	m_pID_FRAME_SuperPasswordReset->SetMsgProcFun( frame_msg );

	SetVisable(false);

	m_pID_EDIT_AddName->SetMaxLength(15);
	m_pID_EDIT_AddName2->SetMaxLength(15);
	m_pID_EDIT_AddName3->SetMaxLength(15);

	AddNameArray[0] = m_pID_EDIT_AddName;
	AddNameArray[1] = m_pID_EDIT_AddName2;
	AddNameArray[2] = m_pID_EDIT_AddName3;


	USE_SCRIPT( eUI_OBJECT_SuperPasswordReset, this );

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SuperPasswordReset::_UnLoadUI()
{
	CLOSE_SCRIPT( eUI_OBJECT_SuperPasswordReset );
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\SuperPasswordReset.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SuperPasswordReset::_IsVisable()
{
	if(m_pID_FRAME_SuperPasswordReset)
		return m_pID_FRAME_SuperPasswordReset->IsVisable();

	return false;
}
// 设置是否可视
void CUI_ID_FRAME_SuperPasswordReset::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_SuperPasswordReset)
		return;

	m_pID_FRAME_SuperPasswordReset->SetVisable( bVisable );
}

bool CUI_ID_FRAME_SuperPasswordReset::Reset()
{
	if(!m_pID_FRAME_SuperPasswordReset)
		return false;
	m_pID_EDIT_AddName->SetText("");
	m_pID_EDIT_AddName2->SetText("");
	m_pID_EDIT_AddName3->SetText("");

	return true;
}

ControlEdit* CUI_ID_FRAME_SuperPasswordReset::GetID_EDIT_AddName3()
{
	if(!m_pID_FRAME_SuperPasswordReset)
		return NULL;
	return m_pID_EDIT_AddName3;
}
bool CUI_ID_FRAME_SuperPasswordReset::EditInputIsVisable()
{
	guardfunc;
	if(!m_pID_FRAME_SuperPasswordReset)
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
	if( m_pID_EDIT_AddName3 )
	{
		if(theUiManager.GetFocus() == m_pID_EDIT_AddName3)
			return true;
	}

	return FALSE;
	unguard;

}

bool CUI_ID_FRAME_SuperPasswordReset::frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;
	if( !s_CUI_ID_FRAME_SuperPasswordReset.IsVisable() )
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