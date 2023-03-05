/********************************************************************
Created by UIEditor.exe
FileName: F:\workspace\ShenWang\Hero\Program\trunk\Client\Bin\Data\Ui\HideGroupMe.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "HideGroupMe.h"
#include "Group_Me.h"

CUI_ID_FRAME_HideGroupMe s_CUI_ID_FRAME_HideGroupMe;
MAP_FRAME_RUN( s_CUI_ID_FRAME_HideGroupMe, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_HideGroupMe, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_HideGroupMe, ID_BUTTON_HideOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_HideGroupMe, ID_BUTTON_AppearOnButtonClick )
CUI_ID_FRAME_HideGroupMe::CUI_ID_FRAME_HideGroupMe()
{
	// Member
	m_pID_FRAME_HideGroupMe = NULL;
	m_pID_BUTTON_Hide = NULL;
	m_pID_BUTTON_Appear = NULL;

}
// Frame
bool CUI_ID_FRAME_HideGroupMe::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_HideGroupMe::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_HideGroupMe::ID_BUTTON_HideOnButtonClick( ControlObject* pSender )
{
	if( s_CUI_ID_FRAME_Group_Me.GetFrame() )
		s_CUI_ID_FRAME_Group_Me.GetFrame()->SetVisable(!s_CUI_ID_FRAME_Group_Me.GetFrame()->IsVisable());
	m_pID_BUTTON_Hide->SetVisable(false);
	m_pID_BUTTON_Appear->SetVisable(true);
	return true;
}
// Button
bool CUI_ID_FRAME_HideGroupMe::ID_BUTTON_AppearOnButtonClick( ControlObject* pSender )
{
	if( s_CUI_ID_FRAME_Group_Me.GetFrame() )
		s_CUI_ID_FRAME_Group_Me.GetFrame()->SetVisable(!s_CUI_ID_FRAME_Group_Me.GetFrame()->IsVisable());
	m_pID_BUTTON_Hide->SetVisable(true);
	m_pID_BUTTON_Appear->SetVisable(false);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_HideGroupMe::_LoadUI()
{
// 	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\HideGroupMe.MEUI", true, UI_Render_LayerThree );
// 	if ( dwResult == 0 )
// 	{
// 		MESSAGE_BOX("读取文件[Data\\UI\\HideGroupMe.MEUI]失败")
// 			return false;
// 	}
// 	return DoControlConnect();
	return true;
}
// 关连控件
bool CUI_ID_FRAME_HideGroupMe::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_HideGroupMe, s_CUI_ID_FRAME_HideGroupMeOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_HideGroupMe, s_CUI_ID_FRAME_HideGroupMeOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_HideGroupMe, ID_BUTTON_Hide, s_CUI_ID_FRAME_HideGroupMeID_BUTTON_HideOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_HideGroupMe, ID_BUTTON_Appear, s_CUI_ID_FRAME_HideGroupMeID_BUTTON_AppearOnButtonClick );

	m_pID_FRAME_HideGroupMe = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_HideGroupMe );
	m_pID_BUTTON_Hide = (ControlButton*)theUiManager.FindControl( ID_FRAME_HideGroupMe, ID_BUTTON_Hide );
	m_pID_BUTTON_Appear = (ControlButton*)theUiManager.FindControl( ID_FRAME_HideGroupMe, ID_BUTTON_Appear );
	assert( m_pID_FRAME_HideGroupMe );
	assert( m_pID_BUTTON_Hide );

	m_pID_BUTTON_Hide->SetVisable(true);
	m_pID_BUTTON_Appear->SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_HideGroupMe::_UnLoadUI()
{
 	m_pID_FRAME_HideGroupMe = NULL;
// 	return theUiManager.RemoveFrame( "Data\\UI\\HideGroupMe.MEUI" );
	return true;
}
// 是否可视
bool CUI_ID_FRAME_HideGroupMe::_IsVisable()
{
	if( !m_pID_FRAME_HideGroupMe) 
		return false;
	return m_pID_FRAME_HideGroupMe->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_HideGroupMe::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_HideGroupMe )
		return;
	m_pID_FRAME_HideGroupMe->SetVisable( bVisable );
}
