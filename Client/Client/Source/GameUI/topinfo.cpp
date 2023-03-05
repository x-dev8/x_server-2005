#include <assert.h>
#include "MeUi/UiManager.h"
#include "topinfo.h"
#include "../Cfg.h"
#include "MeUi/FontManager.h"
#include "FuncPerformanceLog.h"
#include "Me3d/BaseGraphics.h"
#include "MeFont/MeFont.h"
#include "XmlStringLanguage.h"
#include "TimeClock.h"
#include "GameMain.h"
#include "core/Name.h"
#include "MeFont/MeFontSystem.h"

CUI_ID_FRAME_BULL s_CUI_ID_FRAME_BULL;
MAP_FRAME_RUN( s_CUI_ID_FRAME_BULL, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_BULL, OnFrameRender )

#define	OFFSET_Y	200
extern GAME_STATE g_GameState;

CUI_ID_FRAME_BULL::CUI_ID_FRAME_BULL()
{
	guardfunc;
	// SGuildMember
	m_pID_FRAME_Bull = NULL;
	m_pID_PICTURE_WallPaper = NULL;

	m_dwStartTime = 0;
	m_dwLimitTime = 0;
	unguard;
}

// Frame
bool CUI_ID_FRAME_BULL::OnFrameRun()
{
	guardfunc;
	return true;
	unguard;
}
bool CUI_ID_FRAME_BULL::OnFrameRender()
{
	guardfunc;
	if ( m_ltMoveText.size() > 0 )
	{
		if( m_pID_FRAME_Bull )
			m_pID_FRAME_Bull->SetVisable( true );

		SMoveText* pMoveText;
		pMoveText = &m_ltMoveText.front();
		if ( pMoveText->m_nCount > 0 )
		{
			RECT picRC;
			m_pID_PICTURE_WallPaper->GetRealRect( &picRC );

			pMoveText->m_nY = picRC.top + ( m_pID_PICTURE_WallPaper->GetHeight()  - m_pID_FRAME_Bull->GetFontSize() ) / 2;
			//
			int nUseTime = HQ_TimeGetTime() - pMoveText->m_dwStartTime;
			int nMove = nUseTime*pMoveText->m_fMoveSpeed;
			pMoveText->m_nX = picRC.right - nMove;
			DWORD dwAlignMode = DT_LEFT;
			//
			if ( pMoveText->m_nX < picRC.left - pMoveText->m_fWidth )
			{
				pMoveText->m_nCount--;
				pMoveText->m_dwStartTime = HQ_TimeGetTime();								
			}

			RECT rc;
			rc.top = pMoveText->m_nY;
			rc.bottom = rc.top + m_pID_FRAME_Bull->GetFontSize();
			
			rc.left = max( pMoveText->m_nX, picRC.left );				
			if( rc.left == picRC.left )
				dwAlignMode = DT_RIGHT;
			rc.right = min( pMoveText->m_nX + pMoveText->m_fWidth, picRC.right );
			if( rc.right != picRC.right )
				dwAlignMode = DT_RIGHT;

			FontSystem::DrawTextDirect( pMoveText->m_strText.c_str(),
				&rc, dwAlignMode,
				pMoveText->m_dwColor,
				m_pID_FRAME_Bull->GetFontIndex(), true );
		}
		else
		{
			m_ltMoveText.pop_front();
			if ( m_ltMoveText.size() > 0 )
			{
				SMoveText* pMoveText;
				pMoveText = &m_ltMoveText.front();
				pMoveText->m_dwStartTime = HQ_TimeGetTime();
			}
		}
	}
	else
	{
		if( m_pID_FRAME_Bull )
			m_pID_FRAME_Bull->SetVisable( false );
	}


	return true;
	unguard;
}

// 装载UI
bool CUI_ID_FRAME_BULL::_LoadUI()
{
	guardfunc;
	//添加bull
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\bull.meui", true );
	if( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\bull.meui]失败")
			return false;
	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_BULL::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_Bull, s_CUI_ID_FRAME_BULLOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Bull, s_CUI_ID_FRAME_BULLOnFrameRender );

	m_pID_FRAME_Bull = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Bull );
	m_pID_PICTURE_WallPaper = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Bull, ID_PICTURE_WallPaper );

	m_pID_FRAME_Bull->SetVisable( false );

	m_pID_FRAME_Bull->SetMsgProcFun( MsgProc );
	m_pID_FRAME_Bull->SetMsgHoldup( false );

	return true;
	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_BULL::_UnLoadUI()
{
	guardfunc;

	m_pID_FRAME_Bull = NULL;
	m_pID_PICTURE_WallPaper = NULL;

	return theUiManager.RemoveFrame( "data\\ui\\bull.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_BULL::_IsVisable()
{
	guardfunc;
	if( !m_pID_FRAME_Bull )
		return false;
	return m_pID_FRAME_Bull->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_BULL::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pID_FRAME_Bull )
		return;
	m_pID_FRAME_Bull->SetVisable( bVisable );
	unguard;
}


void CUI_ID_FRAME_BULL::SetMoveText( const char *szText, int nCount )
{
	guardfunc;
	assert( szText );
	if( !szText )
	{
		return;
	}
	int nLen = strlen( szText );
	if ( nLen <= 0 )
		return;	
	SMoveText stMoveText;
	stMoveText.m_strText = szText;
	stMoveText.m_nCount = nCount;
	stMoveText.m_fWidth = (float)nLen * (float)m_pID_FRAME_Bull->GetFontSize() / 2.f;
	stMoveText.m_nX = SCREEN_WIDTH / 2;
	stMoveText.m_nY = OFFSET_Y;
	stMoveText.m_dwColor = 0xffff0000;
	stMoveText.m_fMoveSpeed = 0.05f;
	stMoveText.m_dwStartTime = HQ_TimeGetTime();
	m_ltMoveText.push_back( stMoveText );
	//
	SetVisable( true );
	unguard;
}

bool CUI_ID_FRAME_BULL::MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	return false;
}