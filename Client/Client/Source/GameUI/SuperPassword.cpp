/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\chixin.ni\桌面\密码\密码\SuperPassword.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SuperPassword.h"
#include "MessageDefine.h"
#include "ScreenInfoManager.h"
#include "XmlStringLanguage.h"
#include "MessageBox.h"
#include "color_config.h"
#include "NetworkInput.h"
#include "Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "TimeEx.h"
#include "Common.h"
#include "PasswordMessage.h"

static bool s_bPressEnter = false;

bool ClearPassword( const char bPressYesButton, void *pData )
{
	if(bPressYesButton && pData)
	{
		MsgClearSecondPasswordReq msg;
		::CopyMemory(&msg,pData,sizeof(MsgClearSecondPasswordReq));
		GettheNetworkInput().SendMsg( &msg );
	}
	return true;
}


CUI_ID_FRAME_SuperPassword s_CUI_ID_FRAME_SuperPassword;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SuperPassword, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SuperPassword, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SuperPassword, ID_EDIT_AddNameOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuperPassword, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuperPassword, ID_BUTTON_CancleOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuperPassword, ID_BUTTON_ForgetPasswordOnButtonClick )
CUI_ID_FRAME_SuperPassword::CUI_ID_FRAME_SuperPassword()
{
	// Member
	ResetMembers();
}

void CUI_ID_FRAME_SuperPassword::ResetMembers()
{
	m_pID_FRAME_SuperPassword = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_PICTURE_Wall = NULL;
	m_pID_EDIT_AddName = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancle = NULL;
	m_pID_BUTTON_ForgetPassword = NULL;
	m_pID_TEXT_UnLock = NULL;
	m_bHasChecked = false;
}
// Frame
bool CUI_ID_FRAME_SuperPassword::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_SuperPassword::OnFrameRender()
{
	if( s_bPressEnter )
	{
		ID_BUTTON_OKOnButtonClick(NULL);
		s_bPressEnter = false;
	}

	if( IsVisable() )
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

	TimeSpan leftTime(thePlayerRole.GetSecondPasswordUnlockTime());

	if( leftTime.GetTimeSpan() > 0 )
	{
		char buf[512] = {0};
		char szTime[512] = {0};

		int day = leftTime.GetDays();
		int hour = leftTime.GetHours();
		int minute = leftTime.GetMinutes();
		int second = leftTime.GetSeconds();

		if(day>0)
		{
			MeSprintf_s(szTime, sizeof(szTime)/sizeof(char) - 1, "%d%s%d%s%d%s%d%s",
				day, theXmlString.GetString(eText_Day),
				hour, theXmlString.GetString(eTimeUnit_Hour),
				minute, theXmlString.GetString(eTimeUnit_Minute),
				second, theXmlString.GetString(eTimeUnit_Second) );
		}
		else if(hour>0)
		{
			MeSprintf_s(szTime, sizeof(szTime)/sizeof(char) - 1, "%d%s%d%s%d%s",
				hour, theXmlString.GetString(eTimeUnit_Hour),
				minute, theXmlString.GetString(eTimeUnit_Minute),
				second, theXmlString.GetString(eTimeUnit_Second));
		}
		else if(minute>0)
		{
			MeSprintf_s(szTime, sizeof(szTime)/sizeof(char) - 1, "%d%s%d%s",
				minute, theXmlString.GetString(eTimeUnit_Minute),
				second, theXmlString.GetString(eTimeUnit_Second));
		}
		else if(second>0)
		{
			MeSprintf_s(szTime, sizeof(szTime)/sizeof(char) - 1, "%d%s",
				second, theXmlString.GetString(eTimeUnit_Second));
		}

		MeSprintf_s(buf, sizeof(szTime)/sizeof(char) - 1, theXmlString.GetString(eText_SecondPasswordUndoTime), szTime);

		*m_pID_TEXT_UnLock = buf;
	}
	else
	{
		*m_pID_TEXT_UnLock = theXmlString.GetString(eText_SecondPasswordUndoInfo);
	}

	return true;
}
// Edit
void CUI_ID_FRAME_SuperPassword::ID_EDIT_AddNameOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_SuperPassword)
		return;
}
// Button
bool CUI_ID_FRAME_SuperPassword::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_SuperPassword)
		return false;
	string sPassword = m_pID_EDIT_AddName->GetText();

	Reset();

	if(sPassword.size()<4||sPassword.size()>15)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Store_Password, theXmlString.GetString(eText_SecondPasswordSizeError) );
		return false;
	}

	//格式判断
	for(int i=0;i<sPassword.size();++i)
	{
		if((sPassword[i]>0&&sPassword[i]<48)
			||(sPassword[i]>57&&sPassword[i]<65)
			||(sPassword[i]>90&&sPassword[i]<97)
			||(sPassword[i]>122))
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Store_Password, theXmlString.GetString(eText_SecondPasswordStyleError) );
			return false;
		}
	}

	MsgCheckSecondPasswordAck Msg;

	//Msg.uchOperator = uchOperator;

	strncpy_s( Msg.szPassword, sizeof( Msg.szPassword ), sPassword.c_str(), sizeof( Msg.szPassword ) - 1 );

	GettheNetworkInput().SendMsg( &Msg );

	return true;
}
// Button
bool CUI_ID_FRAME_SuperPassword::ID_BUTTON_CancleOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_SuperPassword)
		return false;
	Reset();
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_SuperPassword::ID_BUTTON_ForgetPasswordOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_SuperPassword)
		return false;

	//int leftTime = thePlayerRole.GetSecondPasswordUnlockTime();
	//if( leftTime==0 )
	//{
		//出框
		//MsgClearSecondPasswordReq msg;
		//s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_SecondPasswordRelieve), theXmlString.GetString(eText_SecondPasswordRelieve),
		//	CUI_ID_FRAME_MessageBox::eTypeYesNo, false ,
		//	ClearPassword, &msg, sizeof(MsgClearSecondPasswordReq));


		MsgClearSecondPasswordReq msg;
		GettheNetworkInput().SendMsg( &msg );

	/*}
	else
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Store_Password, theXmlString.GetString(eText_SecondPasswordIsUndo) );
	}*/

	return true;
}

// 装载UI
bool CUI_ID_FRAME_SuperPassword::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SuperPassword.MEUI", false, UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SuperPassword.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SuperPassword::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SuperPassword, s_CUI_ID_FRAME_SuperPasswordOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SuperPassword, s_CUI_ID_FRAME_SuperPasswordOnFrameRender );
	theUiManager.OnEditEnter( ID_FRAME_SuperPassword, ID_EDIT_AddName, s_CUI_ID_FRAME_SuperPasswordID_EDIT_AddNameOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_SuperPassword, ID_BUTTON_OK, s_CUI_ID_FRAME_SuperPasswordID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuperPassword, ID_BUTTON_Cancle, s_CUI_ID_FRAME_SuperPasswordID_BUTTON_CancleOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuperPassword, ID_BUTTON_ForgetPassword, s_CUI_ID_FRAME_SuperPasswordID_BUTTON_ForgetPasswordOnButtonClick );

	m_pID_FRAME_SuperPassword = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SuperPassword );
	m_pID_TEXT_Msg = (ControlText*)theUiManager.FindControl( ID_FRAME_SuperPassword, ID_TEXT_Msg );
	m_pID_PICTURE_Wall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuperPassword, ID_PICTURE_Wall );
	m_pID_EDIT_AddName = (ControlEdit*)theUiManager.FindControl( ID_FRAME_SuperPassword, ID_EDIT_AddName );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuperPassword, ID_BUTTON_OK );
	m_pID_BUTTON_Cancle = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuperPassword, ID_BUTTON_Cancle );
	m_pID_BUTTON_ForgetPassword = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuperPassword, ID_BUTTON_ForgetPassword );
	m_pID_TEXT_UnLock = (ControlText*)theUiManager.FindControl( ID_FRAME_SuperPassword, ID_TEXT_UnLock );
	assert( m_pID_FRAME_SuperPassword );
	assert( m_pID_TEXT_Msg );
	assert( m_pID_PICTURE_Wall );
	assert( m_pID_EDIT_AddName );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancle );
	assert( m_pID_BUTTON_ForgetPassword );
	assert( m_pID_TEXT_UnLock );
	m_pID_FRAME_SuperPassword->SetMsgProcFun( frame_msg );

	SetVisable(false);

	m_pID_EDIT_AddName->SetMaxLength(15);

	USE_SCRIPT( eUI_OBJECT_SuperPassword, this );

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SuperPassword::_UnLoadUI()
{
	CLOSE_SCRIPT( eUI_OBJECT_SuperPassword );
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\SuperPassword.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SuperPassword::_IsVisable()
{
	if(!m_pID_FRAME_SuperPassword)
		return false;

	return m_pID_FRAME_SuperPassword->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SuperPassword::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_SuperPassword)
		return;
	m_pID_FRAME_SuperPassword->SetVisable( bVisable );
}

bool CUI_ID_FRAME_SuperPassword::Reset()
{
	if(!m_pID_FRAME_SuperPassword)
		return false;
	m_pID_EDIT_AddName->SetText("");

	return true;
}

ControlEdit* CUI_ID_FRAME_SuperPassword::GetEditAddName()
{
	if(!m_pID_FRAME_SuperPassword)
		return NULL;
	return m_pID_EDIT_AddName;
}
bool CUI_ID_FRAME_SuperPassword::EditInputIsVisable()
{
	guardfunc;
	if( !m_pID_FRAME_SuperPassword )
		return false;
	if( m_pID_EDIT_AddName )
	{
		if(theUiManager.GetFocus() == m_pID_EDIT_AddName)
			return true;
	}

	return FALSE;
	unguard;

}

bool CUI_ID_FRAME_SuperPassword::frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;
	if( !s_CUI_ID_FRAME_SuperPassword.IsVisable() )
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