/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\BgFrame.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "BgFrame.h"
#include "NpcTaskDialogBox.h"

CUI_ID_FRAME_BgFrame s_CUI_ID_FRAME_BgFrame;
MAP_FRAME_RUN( s_CUI_ID_FRAME_BgFrame, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_BgFrame, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BgFrame, ID_BUTTON_EXITOnButtonClick )
CUI_ID_FRAME_BgFrame::CUI_ID_FRAME_BgFrame()
{
	// Member
	m_pID_FRAME_BgFrame = NULL;
	m_pID_PICTURE_NpcHead = NULL;
	m_pID_PICTURE_BgHead = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_BUTTON_EXIT = NULL;

}

// Frame
bool CUI_ID_FRAME_BgFrame::OnFrameRun()
{
	return true;
}

bool CUI_ID_FRAME_BgFrame::OnFrameRender()
{
	//m_pID_PICTURE_NpcHead->Render();
	return true;
}

// Button
bool CUI_ID_FRAME_BgFrame::ID_BUTTON_EXITOnButtonClick( ControlObject* pSender )
{
	s_CUI_NpcTaskDialogBox.ID_BUTTON_EXITOnButtonClick(pSender);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_BgFrame::_LoadUI()
{
	//s_CUI_NpcTaskDialogBox.LoadUI();
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\BgFrame.MEUI", false,  UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\BgFrame.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_BgFrame::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_BgFrame, s_CUI_ID_FRAME_BgFrameOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_BgFrame, s_CUI_ID_FRAME_BgFrameOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_BgFrame, ID_BUTTON_EXIT, s_CUI_ID_FRAME_BgFrameID_BUTTON_EXITOnButtonClick );

	m_pID_FRAME_BgFrame = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_BgFrame );
	m_pID_PICTURE_NpcHead = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BgFrame, ID_PICTURE_NpcHead );
	m_pID_PICTURE_BgHead = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BgFrame, ID_PICTURE_BgHead );
	m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_BgFrame, ID_TEXT_Name );
	m_pID_BUTTON_EXIT = (ControlButton*)theUiManager.FindControl( ID_FRAME_BgFrame, ID_BUTTON_EXIT );
	assert( m_pID_FRAME_BgFrame );
	assert( m_pID_PICTURE_NpcHead );
	assert( m_pID_PICTURE_BgHead );
	assert( m_pID_TEXT_Name );
	assert( m_pID_BUTTON_EXIT );

	SetVisable(false);
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_BgFrame::_UnLoadUI()
{
	s_CUI_NpcTaskDialogBox.UnLoadUI();
	m_pID_FRAME_BgFrame = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\BgFrame.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_BgFrame::_IsVisable()
{
	if(!m_pID_FRAME_BgFrame)
		return false;

	return m_pID_FRAME_BgFrame->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_BgFrame::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_BgFrame)
		return;

	m_pID_FRAME_BgFrame->SetVisable( bVisable );
}

void CUI_ID_FRAME_BgFrame::SetNpcName(const char *pszName)
{
	if(!m_pID_FRAME_BgFrame)
		return;

	if(!pszName)
		return;

	m_pID_TEXT_Name->SetText(pszName);
}

void CUI_ID_FRAME_BgFrame::SetPicPath(const char *pszPic,bool bVisable)
{
	if(!m_pID_FRAME_BgFrame)
		return;

	m_pID_PICTURE_NpcHead->SetVisable(bVisable);
	if(!pszPic)
		return;

	m_pID_PICTURE_NpcHead->SetPicName(pszPic);
	m_pID_FRAME_BgFrame->GetFrameFather()->SetRedraw();
}

void CUI_ID_FRAME_BgFrame::InitializeAtEnterWorld()
{
	SetVisable(false);
}