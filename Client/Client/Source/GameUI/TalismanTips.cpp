/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\����\������Դ\����\����\TalismanTips.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "TalismanTips.h"

CUI_ID_FRAME_TalismanTips s_CUI_ID_FRAME_TalismanTips;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TalismanTips, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TalismanTips, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TalismanTips, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TalismanTips, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TalismanTips, ID_BUTTON_ConfirmOnButtonClick )
CUI_ID_FRAME_TalismanTips::CUI_ID_FRAME_TalismanTips()
{
	// Member
	m_pID_FRAME_TalismanTips = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_TEXT_Remark = NULL;
	m_pID_TEXT_Attribute = NULL;
	m_pID_BUTTON_Confirm = NULL;

}
// Frame
bool CUI_ID_FRAME_TalismanTips::OnFrameRun()
{
	//ÿ֡�����߼����£���Ҫ���жϽ����Ƿ�ɼ�������������
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_TalismanTips::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_TalismanTips::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TalismanTips )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_TalismanTips::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TalismanTips )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_TalismanTips::ID_BUTTON_ConfirmOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TalismanTips )
		return false;
	return true;
}

// װ��UI
bool CUI_ID_FRAME_TalismanTips::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TalismanTips.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("��ȡ�ļ�[Data\\UI\\TalismanTips.MEUI]ʧ��")
		return false;
	}
	return DoControlConnect();
}
// �����ؼ�
bool CUI_ID_FRAME_TalismanTips::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TalismanTips, s_CUI_ID_FRAME_TalismanTipsOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TalismanTips, s_CUI_ID_FRAME_TalismanTipsOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_TalismanTips, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_TalismanTipsID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TalismanTips, ID_BUTTON_HELP, s_CUI_ID_FRAME_TalismanTipsID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TalismanTips, ID_BUTTON_Confirm, s_CUI_ID_FRAME_TalismanTipsID_BUTTON_ConfirmOnButtonClick );

	m_pID_FRAME_TalismanTips = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TalismanTips );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_TalismanTips, ID_BUTTON_CLOSE );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_TalismanTips, ID_BUTTON_HELP );
	m_pID_TEXT_Remark = (ControlText*)theUiManager.FindControl( ID_FRAME_TalismanTips, ID_TEXT_Remark );
	m_pID_TEXT_Attribute = (ControlText*)theUiManager.FindControl( ID_FRAME_TalismanTips, ID_TEXT_Attribute );
	m_pID_BUTTON_Confirm = (ControlButton*)theUiManager.FindControl( ID_FRAME_TalismanTips, ID_BUTTON_Confirm );

	assert( m_pID_FRAME_TalismanTips );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_TEXT_Remark );
	assert( m_pID_TEXT_Attribute );
	assert( m_pID_BUTTON_Confirm );

	SetVisable(false);
	return true;
}
// ж��UI
bool CUI_ID_FRAME_TalismanTips::_UnLoadUI()
{
	m_pID_FRAME_TalismanTips = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_TEXT_Remark = NULL;
	m_pID_TEXT_Attribute = NULL;
	m_pID_BUTTON_Confirm = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\TalismanTips.MEUI" );
}
// �Ƿ����
bool CUI_ID_FRAME_TalismanTips::_IsVisable()
{
	if ( !m_pID_FRAME_TalismanTips )
		return false;
	return m_pID_FRAME_TalismanTips->IsVisable();
}

// �����Ƿ����
void CUI_ID_FRAME_TalismanTips::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_TalismanTips )
		return;

	m_pID_FRAME_TalismanTips->SetVisable( bVisable );
}
