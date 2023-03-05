/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\PopIntro3.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PopIntro3.h"
#include "NpcCoord.h"
#include "XmlStringLanguage.h"
#include "MeTerrain/stdafx.h"

CUI_ID_FRAME_PopIntro3 s_CUI_ID_FRAME_PopIntro3;
MAP_FRAME_RUN( s_CUI_ID_FRAME_PopIntro3, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PopIntro3, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PopIntro3, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PopIntro3, ID_BUTTON_OkOnButtonClick )
CUI_ID_FRAME_PopIntro3::CUI_ID_FRAME_PopIntro3()
{
	// Member
	m_pID_FRAME_PopIntro3 = NULL;
	m_pID_TEXT_Info = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Ok = NULL;
}
// Frame
bool CUI_ID_FRAME_PopIntro3::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_PopIntro3::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_PopIntro3::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}

// Button
bool CUI_ID_FRAME_PopIntro3::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{	
	if(m_strNpcName.length() <= 0)
		return true;

	CWorldTile *pCurrTile = CURRENTTILE;
	if(!pCurrTile)
		return true;

	NpcCoord::getInstance()->clickHyberToMiniMap(m_strNpcName.c_str(),pCurrTile->GetMapId());
	SetVisable(false);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_PopIntro3::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PopIntro3.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\PopIntro3.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_PopIntro3::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PopIntro3, s_CUI_ID_FRAME_PopIntro3OnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PopIntro3, s_CUI_ID_FRAME_PopIntro3OnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_PopIntro3, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_PopIntro3ID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PopIntro3, ID_BUTTON_Ok, s_CUI_ID_FRAME_PopIntro3ID_BUTTON_OkOnButtonClick );

	m_pID_FRAME_PopIntro3 = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PopIntro3 );
	m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_PopIntro3, ID_TEXT_Info );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_PopIntro3, ID_BUTTON_CLOSE );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_PopIntro3, ID_BUTTON_Ok );
	assert( m_pID_FRAME_PopIntro3 );
	assert( m_pID_TEXT_Info );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_Ok );
	
	m_strNpcName.clear();
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_PopIntro3::_UnLoadUI()
{
	m_strNpcName.clear(); 
	m_pID_FRAME_PopIntro3 = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\PopIntro3.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_PopIntro3::_IsVisable()
{
	if(!m_pID_FRAME_PopIntro3)
		return false;

	return m_pID_FRAME_PopIntro3->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_PopIntro3::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_PopIntro3)
		return;

	m_pID_FRAME_PopIntro3->SetVisable( bVisable );
}

void CUI_ID_FRAME_PopIntro3::ShowInfo(int nNpcName,int nStrindInfo)
{
	m_strNpcName = theXmlString.GetString(nNpcName);
	m_pID_TEXT_Info->SetText(theXmlString.GetString(nStrindInfo));
}
