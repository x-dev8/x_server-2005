/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\ShowScriptGif.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ShowScriptGif.h"
#include "UIMgr.h"

int g_iShowScriptGifCountDown = 4000;
CUI_ID_FRAME_ShowScriptGif s_CUI_ID_FRAME_ShowScriptGif;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ShowScriptGif, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ShowScriptGif, OnFrameRender )
CUI_ID_FRAME_ShowScriptGif::CUI_ID_FRAME_ShowScriptGif()
{
	// Member
	m_pID_FRAME_ShowScriptGif = NULL;
	m_pID_PICTURE_ScriptGif = NULL;

}
// Frame
bool CUI_ID_FRAME_ShowScriptGif::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_ShowScriptGif::OnFrameRender()
{
	if( HQ_TimeGetTime() >= m_dwCloseTime )
		SetVisable( false );
	return true;
}

// 装载UI
bool CUI_ID_FRAME_ShowScriptGif::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ShowScriptGif.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ShowScriptGif.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ShowScriptGif::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ShowScriptGif, s_CUI_ID_FRAME_ShowScriptGifOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ShowScriptGif, s_CUI_ID_FRAME_ShowScriptGifOnFrameRender );

	m_pID_FRAME_ShowScriptGif = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ShowScriptGif );
	m_pID_PICTURE_ScriptGif = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShowScriptGif, ID_PICTURE_ScriptGif );
	assert( m_pID_FRAME_ShowScriptGif );
	assert( m_pID_PICTURE_ScriptGif );
	USE_SCRIPT( eUI_OBJECT_ShowScriptGif, this );
	
	m_dwCloseTime = 0;
	SetVisable( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ShowScriptGif::_UnLoadUI()
{
	CLOSE_SCRIPT( eUI_OBJECT_ShowScriptGif );

	m_pID_FRAME_ShowScriptGif = NULL;
	m_pID_PICTURE_ScriptGif = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\ShowScriptGif.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_ShowScriptGif::_IsVisable()
{
	if( !m_pID_FRAME_ShowScriptGif )
		return false;
	return m_pID_FRAME_ShowScriptGif->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ShowScriptGif::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_ShowScriptGif )
		return;
	m_pID_FRAME_ShowScriptGif->SetVisable( bVisable );
	if( bVisable )
	{
		m_dwCloseTime = HQ_TimeGetTime() + g_iShowScriptGifCountDown;
	}
}
