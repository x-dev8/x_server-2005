/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Work\HeroRuntime\Client\UI\Tips.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "UIBase.h"
#include "Tips.h"
#include "Me3d/BaseGraphics.h"
#include "FuncPerformanceLog.h"
#include "MeFont/MeFontSystem.h"
#include "MeFont/MeFontSystem.h"
#include "MeFont/MeFont.h"
#include "UIMgr.h"
CUI_ID_FRAME_Tips s_CUI_ID_FRAME_Tips;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Tips, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Tips, OnFrameRender )
CUI_ID_FRAME_Tips::CUI_ID_FRAME_Tips()
// :CUIBase(eUI_OBJECT_Tips)
{
	guardfunc;
	OutputDebugStr( "CUI_ID_FRAME_Tips");
	// SGuildMember
	m_pID_FRAME_Tips = NULL;
	unguard;

}


void CUI_ID_FRAME_Tips::SetText ( std::string szText )
{
	guardfunc;
	if( szText.size() > 0 )
	{
		m_szData = szText;
	}
	unguard;
}

// Frame
bool CUI_ID_FRAME_Tips::OnFrameRun()
{
	return true;
}

bool CUI_ID_FRAME_Tips::OnFrameRender()
{
	guardfunc;
	if( IsVisable() )
	{
		int nRow = 15;
		int nLen = 15;
		RECT m_rtFrame = {0};
		if( m_pID_FRAME_Tips )
		{
			m_szData = "dfasfdasfdas";

			m_pID_FRAME_Tips->GetRealRect( &m_rtFrame );
			int nIdx = m_szData.find("<br>");
			
			if( nIdx != -1 )
			{
				std::string szHeader = m_szData.substr( 0, nIdx );
				FontSystem::DrawText( szHeader.c_str(),
										m_rtFrame.left+15, m_rtFrame.top+nRow,
										DT_NOCLIP, 0xff00ff00 ); 
				nRow += nLen;
				GetDrawer()->DrawLine2D( m_rtFrame.left+15, m_rtFrame.top + nRow, 
					m_rtFrame.right - 20, m_rtFrame.top+ nRow, 0xffffff00 );
				nRow += nLen/2;
			}
			FontSystem::DrawText( m_szData.c_str(),
									m_rtFrame.left+15, m_rtFrame.top+nRow,
									DT_NOCLIP, 0xff00ff00 ); 
		}
	}
	return true;
	unguard;
}

// 装载UI
bool CUI_ID_FRAME_Tips::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\Tips.meui" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\Tips.UI]失败")
			return false;
	}
	return DoControlConnect();
	unguard;
}

// 关连控件
bool CUI_ID_FRAME_Tips::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_Tips, s_CUI_ID_FRAME_TipsOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Tips, s_CUI_ID_FRAME_TipsOnFrameRender );

	m_pID_FRAME_Tips = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Tips );
	assert( m_pID_FRAME_Tips );

	USE_SCRIPT( eUI_OBJECT_Tips, this );

	return true;
	unguard;
}

// 卸载UI
bool CUI_ID_FRAME_Tips::_UnLoadUI()
{
	guardfunc;
	CLOSE_SCRIPT( eUI_OBJECT_Tips );
	m_pID_FRAME_Tips = NULL;
	return theUiManager.RemoveFrame( "data\\ui\\Tips.meui" );
	unguard;
}

// 是否可视
bool CUI_ID_FRAME_Tips::_IsVisable()
{
	guardfunc;
	if( !m_pID_FRAME_Tips )
		return false;
	return m_pID_FRAME_Tips->IsVisable();
	unguard;
}

// 设置是否可视
void CUI_ID_FRAME_Tips::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pID_FRAME_Tips )
		return;
	m_pID_FRAME_Tips->SetVisable( bVisable );
	unguard;
}
