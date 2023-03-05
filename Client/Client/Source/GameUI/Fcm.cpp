/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Hero\Program\trunk\Client\Bin\Data\Ui\Fcm.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Fcm.h"
#include "UIMgr.h"
#include "XmlStringLanguage.h"
#include "PreventWallow.h"

CUI_ID_FRAME_Fcm s_CUI_ID_FRAME_Fcm;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Fcm, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Fcm, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Fcm, ID_BUTTON_CLOSEOnButtonClick )
CUI_ID_FRAME_Fcm::CUI_ID_FRAME_Fcm()
{
	// Member
	m_pID_FRAME_Fcm = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Msg = NULL;

}
// Frame
bool CUI_ID_FRAME_Fcm::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_Fcm::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_Fcm::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Fcm )
		return false;
	//CPreventWallow::Instance().SetShowFCMNotHealthyFrame(false);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_Fcm::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Fcm.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Fcm.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Fcm::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Fcm, s_CUI_ID_FRAME_FcmOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Fcm, s_CUI_ID_FRAME_FcmOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Fcm, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_FcmID_BUTTON_CLOSEOnButtonClick );

	m_pID_FRAME_Fcm = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Fcm );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Fcm, ID_BUTTON_CLOSE );
	m_pID_TEXT_Msg = (ControlText*)theUiManager.FindControl( ID_FRAME_Fcm, ID_TEXT_Msg );
	assert( m_pID_FRAME_Fcm );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_Msg );

	m_pID_TEXT_Msg->SetText(theXmlString.GetString(eText_AntiAddictionMoreThan5Hour));

	USE_SCRIPT( eUI_OBJECT_FCM, this );
	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Fcm::_UnLoadUI()
{
	m_pID_FRAME_Fcm = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Msg = NULL;

	CLOSE_SCRIPT( eUI_OBJECT_FCM );
	return theUiManager.RemoveFrame( "Data\\UI\\Fcm.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Fcm::_IsVisable()
{
	if( !m_pID_FRAME_Fcm )
		return false;
	return m_pID_FRAME_Fcm->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Fcm::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_Fcm )
		return;
	m_pID_FRAME_Fcm->SetVisable( bVisable );
}
