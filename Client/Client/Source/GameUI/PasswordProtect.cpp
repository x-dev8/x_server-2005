/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\策划文档\密保卡界面\PasswordProtect.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PasswordProtect.h"
#include "ui/Login.h"
#include "XmlStringLanguage.h"
#include "GameMain.h"
#include "ui/MessageBox.h"
#include "Common.h"

int GetAscii(const char c);
extern CHeroGame	theHeroGame;
extern GAME_STATE	g_GameState;

CUI_ID_FRAME_PasswordProtect s_CUI_ID_FRAME_PasswordProtect;
MAP_FRAME_RUN( s_CUI_ID_FRAME_PasswordProtect, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PasswordProtect, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_PasswordProtect, ID_EDIT_AddNameOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PasswordProtect, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PasswordProtect, ID_BUTTON_CancleOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_PasswordProtect, ID_EDIT_AddName2OnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_PasswordProtect, ID_EDIT_AddName3OnEditEnter )
CUI_ID_FRAME_PasswordProtect::CUI_ID_FRAME_PasswordProtect()
{
	// Member
	m_pID_FRAME_PasswordProtect = NULL;
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
	m_pID_TEXT_Title = NULL;
	m_pID_PICTURE_TitleWall = NULL;
	//m_pID_PICTURE_Title = NULL;
	m_fCountDown = 0.f;
}
// Frame
bool CUI_ID_FRAME_PasswordProtect::OnFrameRun()
{
	if( IsVisable() )
	{
		if(strlen(m_pID_EDIT_AddName->GetText()) == 0
			|| strlen(m_pID_EDIT_AddName2->GetText()) == 0 
			|| strlen(m_pID_EDIT_AddName3->GetText()) == 0 )
			m_pID_BUTTON_OK->SetEnable(false);
		else
			m_pID_BUTTON_OK->SetEnable(true);

		// 倒计时结束后自动关闭
		m_fCountDown -= theHeroGame.GetFrameElapsedTime();
		if( m_fCountDown <= 0 )
		{
			s_CUI_ID_FRAME_MessageBox.closeAll(true);
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_LoginPwdProtectTimeOut), "", 
				CUI_ID_FRAME_MessageBox::eTypeConfirm, true );

			SetVisable(false);
		}
	}
	return true;
}
bool CUI_ID_FRAME_PasswordProtect::OnFrameRender()
{
	return true;
}
// Edit
void CUI_ID_FRAME_PasswordProtect::ID_EDIT_AddNameOnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_PasswordProtect ) 
		return;
}
// Button
bool CUI_ID_FRAME_PasswordProtect::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PasswordProtect ) 
		return false;
	if(strlen(m_pID_EDIT_AddName->GetText()) == 0
		|| strlen(m_pID_EDIT_AddName2->GetText()) == 0 
		|| strlen(m_pID_EDIT_AddName3->GetText()) == 0 )
		return true;

	char temp[16] = {0};
	std::string strPwdResult = "";
	strncpy(temp, m_pID_EDIT_AddName->GetText(), 2);
	strPwdResult = temp;
	strncpy(temp, m_pID_EDIT_AddName2->GetText(), 2);
	strPwdResult += temp;
	strncpy(temp, m_pID_EDIT_AddName3->GetText(), 2);
	strPwdResult += temp;

	// 继续登录
	s_CUI_ID_FRAME_LOGIN.FinishEnterPwdProtect(strPwdResult);

	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_PasswordProtect::ID_BUTTON_CancleOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PasswordProtect ) 
		return false;
	s_CUI_ID_FRAME_LOGIN.CancelLoginFromPwdProtect();

	SetVisable(false);
	return true;
}
// Edit
void CUI_ID_FRAME_PasswordProtect::ID_EDIT_AddName2OnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_PasswordProtect ) 
		return;
}
// Edit
void CUI_ID_FRAME_PasswordProtect::ID_EDIT_AddName3OnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_PasswordProtect ) 
		return;
}

// 装载UI
bool CUI_ID_FRAME_PasswordProtect::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PasswordProtect.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\PasswordProtect.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_PasswordProtect::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PasswordProtect, s_CUI_ID_FRAME_PasswordProtectOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PasswordProtect, s_CUI_ID_FRAME_PasswordProtectOnFrameRender );
	theUiManager.OnEditEnter( ID_FRAME_PasswordProtect, ID_EDIT_AddName, s_CUI_ID_FRAME_PasswordProtectID_EDIT_AddNameOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_PasswordProtect, ID_BUTTON_OK, s_CUI_ID_FRAME_PasswordProtectID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PasswordProtect, ID_BUTTON_Cancle, s_CUI_ID_FRAME_PasswordProtectID_BUTTON_CancleOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_PasswordProtect, ID_EDIT_AddName2, s_CUI_ID_FRAME_PasswordProtectID_EDIT_AddName2OnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_PasswordProtect, ID_EDIT_AddName3, s_CUI_ID_FRAME_PasswordProtectID_EDIT_AddName3OnEditEnter );

	m_pID_FRAME_PasswordProtect = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PasswordProtect );
	m_pID_TEXT_Msg = (ControlText*)theUiManager.FindControl( ID_FRAME_PasswordProtect, ID_TEXT_Msg );
	m_pID_PICTURE_Wall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PasswordProtect, ID_PICTURE_Wall );
	m_pID_EDIT_AddName = (ControlEdit*)theUiManager.FindControl( ID_FRAME_PasswordProtect, ID_EDIT_AddName );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_PasswordProtect, ID_BUTTON_OK );
	m_pID_BUTTON_Cancle = (ControlButton*)theUiManager.FindControl( ID_FRAME_PasswordProtect, ID_BUTTON_Cancle );
	m_pID_TEXT_Msg2 = (ControlText*)theUiManager.FindControl( ID_FRAME_PasswordProtect, ID_TEXT_Msg2 );
	m_pID_PICTURE_Wall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PasswordProtect, ID_PICTURE_Wall2 );
	m_pID_EDIT_AddName2 = (ControlEdit*)theUiManager.FindControl( ID_FRAME_PasswordProtect, ID_EDIT_AddName2 );
	m_pID_TEXT_Msg3 = (ControlText*)theUiManager.FindControl( ID_FRAME_PasswordProtect, ID_TEXT_Msg3 );
	m_pID_PICTURE_Wall3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PasswordProtect, ID_PICTURE_Wall3 );
	m_pID_EDIT_AddName3 = (ControlEdit*)theUiManager.FindControl( ID_FRAME_PasswordProtect, ID_EDIT_AddName3 );
	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_PasswordProtect, ID_TEXT_Title );
	m_pID_PICTURE_TitleWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PasswordProtect, ID_PICTURE_TitleWall );
	//m_pID_PICTURE_Title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PasswordProtect, ID_PICTURE_Title );
	assert( m_pID_FRAME_PasswordProtect );
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
	assert( m_pID_TEXT_Title );
	assert( m_pID_PICTURE_TitleWall );
	//assert( m_pID_PICTURE_Title );

	m_pID_EDIT_AddName->SetMaxLength(2);
	m_pID_EDIT_AddName2->SetMaxLength(2);
	m_pID_EDIT_AddName3->SetMaxLength(2);

	m_pID_FRAME_PasswordProtect->SetArrayMode( ArrayMode_Top );
	m_pID_FRAME_PasswordProtect->SetMsgProcFun( frame_msg );

	m_fCountDown = 0.f;

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_PasswordProtect::_UnLoadUI()
{
	m_pID_FRAME_PasswordProtect = NULL;
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
	m_pID_TEXT_Title = NULL;
	m_pID_PICTURE_TitleWall = NULL;
	//m_pID_PICTURE_Title = NULL;

	return theUiManager.RemoveFrame( "Data\\UI\\PasswordProtect.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_PasswordProtect::_IsVisable()
{
	if( !m_pID_FRAME_PasswordProtect ) 
		return false;
	return m_pID_FRAME_PasswordProtect->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_PasswordProtect::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_PasswordProtect )
		return;

	if( bVisable )
	{
		m_fCountDown = 60.f;

		m_pID_BUTTON_OK->SetEnable(false);
		*m_pID_TEXT_Msg = "";
		*m_pID_TEXT_Msg2 = "";
		*m_pID_TEXT_Msg3 = "";
		*m_pID_EDIT_AddName = "";
		*m_pID_EDIT_AddName2 = "";
		*m_pID_EDIT_AddName3 = "";

		if( s_CUI_ID_FRAME_LOGIN.GetPasswordProcLength() != 6 )
		{
#ifdef _DEBUG
			assert( false && "密保卡信息错误！");
#endif
			return;
		}

		char p;
		int iAscii;
		char r;
		std::string strPwdProtectResult = "";
		for( int i=0; i<6; ++i )
		{
			p = s_CUI_ID_FRAME_LOGIN.GetPasswordChar(i);
			iAscii = GetAscii(p);
			if( iAscii < 0 )
			{
#ifdef _DEBUG
				assert( false && "密保卡信息错误2！");
#endif
				return;
			}
			iAscii %= 10;
			switch( i )
			{
			case 0:
			case 2:
			case 4:
				r = 'A' + iAscii;
				break;
			case 1:
			case 3:
			case 5:
				r = '0' + iAscii;
				break;
			}
			strPwdProtectResult += r;
		}
		char text[256] = {0};
		char c, d;
		c = strPwdProtectResult[0];
		d = strPwdProtectResult[1];
		MeSprintf_s(text, sizeof(text)/sizeof(char) - 1, theXmlString.GetString(eText_PasswordProtectString), c, d );
		*m_pID_TEXT_Msg = text;

		c = strPwdProtectResult[2];
		d = strPwdProtectResult[3];
		MeSprintf_s(text, sizeof(text)/sizeof(char) - 1, theXmlString.GetString(eText_PasswordProtectString), c, d );
		*m_pID_TEXT_Msg2 = text;

		c = strPwdProtectResult[4];
		d = strPwdProtectResult[5];
		MeSprintf_s(text, sizeof(text)/sizeof(char) - 1, theXmlString.GetString(eText_PasswordProtectString), c, d );
		*m_pID_TEXT_Msg3 = text;

		theUiManager.SetFocus(m_pID_EDIT_AddName);

		if (s_CUI_ID_FRAME_LOGIN.GetHandle())
		{
			TerminateThread( s_CUI_ID_FRAME_LOGIN.GetHandle(), 0 );
			CloseHandle( s_CUI_ID_FRAME_LOGIN.GetHandle() );
            s_CUI_ID_FRAME_LOGIN.SetHandle(NULL);
		}
	}

	m_pID_FRAME_PasswordProtect->SetVisable( bVisable );
}

bool CUI_ID_FRAME_PasswordProtect::frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	if ( g_GameState != G_LOGIN )
		return false;

	if( !s_CUI_ID_FRAME_PasswordProtect.IsVisable() )
		return false;

	switch( msg ) 
	{
	case WM_KEYUP:
		{
			if(wParam == VK_RETURN)
			{
				if( s_CUI_ID_FRAME_PasswordProtect.m_pID_BUTTON_OK->IsEnable() )
					s_CUI_ID_FRAME_PasswordProtect.ID_BUTTON_OKOnButtonClick( NULL );
				return true;
			}
		}
		break;
	default:
		break;
	}
	return false;
}

int GetAscii(const char c)
{
	if( c >= '0' && c <= '9' )
		return c - '0' + 48;

	if( c >= 'A' && c <= 'Z' )
		return c - 'A' + 65;

	if( c >= 'a' && c <= 'z' )
		return c - 'a' + 97;

	return -1;
}