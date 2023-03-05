/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\RTX\TransferToNpc.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "TransferToNpc.h"

CUI_ID_FRAME_TransferToNpc s_CUI_ID_FRAME_TransferToNpc;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TransferToNpc, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TransferToNpc, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TransferToNpc, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TransferToNpc, ID_BUTTON_CancleOnButtonClick )
CUI_ID_FRAME_TransferToNpc::CUI_ID_FRAME_TransferToNpc()
{
	// Member
	m_pID_FRAME_TransferToNpc = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_PICTURE_FrameHead = NULL;
	m_pID_BUTTON_Cancle = NULL;
	m_pID_TEXT_Msg = NULL;
	InitMember();
}

void CUI_ID_FRAME_TransferToNpc::InitMember()
{
	m_nValue = 0;
	m_funcPressYes = NULL;
}
// Frame
bool CUI_ID_FRAME_TransferToNpc::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_TransferToNpc::OnFrameRender()
{
	return true;
}



// 装载UI
bool CUI_ID_FRAME_TransferToNpc::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TransferToNpc.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\TransferToNpc.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_TransferToNpc::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TransferToNpc, s_CUI_ID_FRAME_TransferToNpcOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TransferToNpc, s_CUI_ID_FRAME_TransferToNpcOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_TransferToNpc, ID_BUTTON_Ok, s_CUI_ID_FRAME_TransferToNpcID_BUTTON_OkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TransferToNpc, ID_BUTTON_Cancle, s_CUI_ID_FRAME_TransferToNpcID_BUTTON_CancleOnButtonClick );

	m_pID_FRAME_TransferToNpc = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TransferToNpc );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_TransferToNpc, ID_BUTTON_Ok );
	m_pID_PICTURE_FrameHead = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TransferToNpc, ID_PICTURE_FrameHead );
	m_pID_BUTTON_Cancle = (ControlButton*)theUiManager.FindControl( ID_FRAME_TransferToNpc, ID_BUTTON_Cancle );
	m_pID_TEXT_Msg = (ControlText*)theUiManager.FindControl( ID_FRAME_TransferToNpc, ID_TEXT_Msg );

	assert( m_pID_FRAME_TransferToNpc );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_PICTURE_FrameHead );
	assert( m_pID_BUTTON_Cancle );
	assert( m_pID_TEXT_Msg );

	SetVisable(false);
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_TransferToNpc::_UnLoadUI()
{
	m_pID_FRAME_TransferToNpc = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_PICTURE_FrameHead = NULL;
	m_pID_BUTTON_Cancle = NULL;
	m_pID_TEXT_Msg = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\TransferToNpc.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_TransferToNpc::_IsVisable()
{
	if ( !m_pID_FRAME_TransferToNpc )
		return false;
	return m_pID_FRAME_TransferToNpc->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_TransferToNpc::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_TransferToNpc )
		return;
	m_pID_FRAME_TransferToNpc->SetVisable( bVisable );
}

// Button
bool CUI_ID_FRAME_TransferToNpc::ID_BUTTON_CancleOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TransferToNpc )
		return false;

	_SetVisable(false);
	return true;
}

// Button
bool CUI_ID_FRAME_TransferToNpc::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TransferToNpc )
		return false;

	if (!m_funcPressYes)
	{
		return false;
	}
	
	m_funcPressYes(m_nValue);
	_SetVisable(false);
	return true;
}

inline void CUI_ID_FRAME_TransferToNpc::SetMemberValue(funcPressYes func, int nValue, const char* szText)
{
	m_funcPressYes = func;
	m_nValue = nValue;
	if (szText)
	{
		m_strShowMessage = szText;
	}
}

void CUI_ID_FRAME_TransferToNpc::Show(funcPressYes func, int nValue, const char* szText)
{
	s_CUI_ID_FRAME_TransferToNpc.SetVisable(true);
	SetMemberValue(func, nValue, szText);
	ShowInfo();
}

inline void CUI_ID_FRAME_TransferToNpc::ShowInfo()
{
	if (!m_pID_TEXT_Msg)
	{
		return;
	}
	
	m_pID_TEXT_Msg->SetText(m_strShowMessage);
}