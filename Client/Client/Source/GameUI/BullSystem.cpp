/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\bullsys\BullSystem.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "BullSystem.h"
#include "MeTerrain/stdafx.h"
#include "MeUi/FontManager.h"
#include "FuncPerformanceLog.h"
#include "Me3d/BaseGraphics.h"
#include "MeFont/MeFont.h"
#include "XmlStringLanguage.h"
#include "TimeClock.h"
#include "core/Name.h"
#include "GameMain.h"
#include "Me3d/Engine/RendererDx.h"
#include "me3d/ShaderManager.h"
#include "MeTerrain/SwGlobal.h"
#include "wsRender.h"
#include "GameMain.h"
#include "wsCamera.h"
#include "Meui/ExpressionManager.h"
#include "MeFont/MeFontSystem.h"
#include "MeUtility/tstring.h"

extern GAME_STATE g_GameState;
CUI_ID_FRAME_BullSystem s_CUI_ID_FRAME_BullSystem;
MAP_FRAME_RUN( s_CUI_ID_FRAME_BullSystem, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_BullSystem, OnFrameRender )
CUI_ID_FRAME_BullSystem::CUI_ID_FRAME_BullSystem()
{
	// Member
	m_pID_FRAME_BullSystem = NULL;
	m_pID_PICTURE_WallPaper = NULL;
	m_dwStartTime = 0;
	m_dwLimitTime = 0;
}
// Frame
bool CUI_ID_FRAME_BullSystem::OnFrameRun()
{
	if(!IsVisable())
		return true;

	if (m_currMoveText.m_nCount > 0)
	{
		RECT picRC;
		m_pID_PICTURE_WallPaper->GetRealRect( &picRC );

		RECT rc;
		DWORD dwCurrTime = HQ_TimeGetTime();
		int nUseTime = dwCurrTime - m_currMoveText.m_dwStartTime;
		int nMove = nUseTime*m_currMoveText.m_fMoveSpeed;
		m_currMoveText.m_nX = picRC.right - nMove;

		rc.left = m_currMoveText.m_nX;
		rc.right = rc.left + (m_currMoveText.m_strText.size() + 2) * m_pID_FRAME_BullSystem->GetFontSize();
		rc.top = picRC.top;
		rc.bottom = rc.top + m_pID_PICTURE_WallPaper->GetHeight();

		if (m_currMoveText.m_nX - picRC.left < -m_currMoveText.m_fWidth)
		{
			m_currMoveText.m_dwStartTime = dwCurrTime;
			m_currMoveText.m_nCount--;
		}
	}
	else
	{
		if ( m_ltMoveText.size() > 0 )
		{
			m_currMoveText = m_ltMoveText.front();
			m_ltMoveText.pop_front();
			m_currMoveText.m_dwStartTime = HQ_TimeGetTime();
		}
		else
		{
			if( m_pID_FRAME_BullSystem )
				m_pID_FRAME_BullSystem->SetVisable( false );
		}
	}
	
	return true;
}
bool CUI_ID_FRAME_BullSystem::OnFrameRender()
{
	if (m_currMoveText.m_nCount > 0)
	{
		GetEngine()->GetRenderer()->EndScene();

		LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
		IRenderer* r = GetEngine()->GetRenderer();

		RECT picRC;
		m_pID_PICTURE_WallPaper->GetRealRect( &picRC );

		D3DVIEWPORT9 ViewPort;
		ViewPort.X = picRC.left;
		ViewPort.Y = picRC.top;
		ViewPort.Width = m_pID_PICTURE_WallPaper->GetWidth();
		ViewPort.Height = m_pID_PICTURE_WallPaper->GetHeight();
		ViewPort.MinZ = 0.0f;
		ViewPort.MaxZ = 1.0f;

		r->SetViewport( &ViewPort );
		r->BeginScene();
		r->Clear( 0L, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 255, 255, 255), 1.0f, 0L );

		{
			int nWidth = 0;
			//if(m_currMoveText.pInfo != NULL)
			//	nWidth = ShowExpression(m_currMoveText.pInfo,m_currMoveText.m_nX,picRC.top);  //显示表情

			RECT rc;
			rc.left = m_currMoveText.m_nX + nWidth;
			rc.right = rc.left + (m_currMoveText.m_strText.size() + 2) * m_pID_FRAME_BullSystem->GetFontSize();
			rc.top = picRC.top;
			rc.bottom = picRC.bottom;/*rc.top + FontSystem::GetFontHeight( m_pID_FRAME_BullSystem->GetFontIndex() );*//*m_pID_PICTURE_WallPaper->GetHeight();*/

			FontRender::EFontRenders eOldIdx = FontRender::EFR_FIRST;
			if( FontSystem::IsUseNewFont() )
			{
				eOldIdx = FontRender::getFontRender()->GetDefaultRendererIdx();
				FontRender::getFontRender()->SetDefaultRendererIdx( FontRender::EFR_THIRD );
				FontSystem::ClearRender( FontRender::EFR_THIRD );
			}

			FontSystem::DrawText( m_currMoveText.m_strText.c_str(),
				&rc, DT_LEFT | DT_VCENTER,
				m_currMoveText.m_dwColor,
				m_pID_FRAME_BullSystem->GetFontIndex(), true );

			if( FontSystem::IsUseNewFont() )
			{
				FontRender::getFontRender()->SetDefaultRendererIdx( eOldIdx );
				FontSystem::DoRender( FontRender::EFR_THIRD );
			}				
		}

		r->EndScene();

		getwsCamera()->ResetViewport();

		GetEngine()->GetRenderer()->BeginScene();
	}

	return true;
}

// 装载UI
bool CUI_ID_FRAME_BullSystem::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\BullSystem.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\BullSystem.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_BullSystem::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_BullSystem, s_CUI_ID_FRAME_BullSystemOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_BullSystem, s_CUI_ID_FRAME_BullSystemOnFrameRender );

	m_pID_FRAME_BullSystem = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_BullSystem );
	m_pID_PICTURE_WallPaper = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BullSystem, ID_PICTURE_WallPaper );
	assert( m_pID_FRAME_BullSystem );
	assert( m_pID_PICTURE_WallPaper );
	m_pID_FRAME_BullSystem->SetVisable( false );
	//m_pID_FRAME_BullSystem->SetMsgHoldup( false );
	m_pID_FRAME_BullSystem->SetMsgProcFun( MsgProc );
	USE_SCRIPT( eUI_OBJECT_BullSystem, this );
	m_pID_FRAME_BullSystem->SetOnEscResponseType(ControlFrame::EscResponse_SkipMe);
	m_currMoveText.m_nCount = 0;
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_BullSystem::_UnLoadUI()
{
	m_pID_FRAME_BullSystem = NULL;
	m_pID_PICTURE_WallPaper = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\BullSystem.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_BullSystem::_IsVisable()
{
	if( !m_pID_FRAME_BullSystem )
		return false;
	return m_pID_FRAME_BullSystem->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_BullSystem::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_BullSystem )
		return;
	m_pID_FRAME_BullSystem->SetVisable( bVisable );
}

void CUI_ID_FRAME_BullSystem::SetMoveText( const char *szText, int nCount, DWORD dwColor, const bool bPushFront/* = false*/ )
{
    if( !IsUILoad() )
        SetVisable( true );

	if( !m_pID_FRAME_BullSystem )
		return;

	assert( szText );
	if( !szText )
	{
		return;
	}
	int nLen = strlen( szText );
	if ( nLen <= 0 )
		return;	

	std::string parStr(szText);
	int nAmount = 0;
	ExpressionManager::GetInstance().AddExpressionAni(parStr);
	if(parStr.at(0) == '{')
	{
		int n = parStr.find('}');
		if(n != -1)
		{
			nAmount = n - 1;
		}
	}

	char szTempText[1024];
	memset(szTempText,0,1024);
	int nIndex = 0;
	for (int i = 0 + nAmount; i < nLen /*+ nAmount*/; ++i)
	{
		if (nIndex > 1022)
		{
			assert(0);
			break;
		}
		if (szText[i] != '_' && szText[i] != '~')
		{
			szTempText[nIndex++] = szText[i];
		}		
	}
	// 	RECT rc;
	// 	m_pID_FRAME_TOPINFO->GetRealRect( &rc );

    if(!m_pID_FRAME_BullSystem)
        return;

	SMoveText stMoveText;
	stMoveText.m_strText = szTempText;
	stMoveText.m_nCount = nCount;
	if( FontSystem::IsUseNewFont() )
	{
		std::wstring tempWString = Common::_tstring::toWideString(szTempText);
		stMoveText.m_fWidth = FontSystem::GetTextWidth(m_pID_FRAME_BullSystem->GetFontIndex(), tempWString, 0, tempWString.length(), false) + 50/*前面gif的长度*/;
	}
	else
		stMoveText.m_fWidth = (float)nLen * (float)m_pID_FRAME_BullSystem->GetFontSize() / 2.f;
	stMoveText.m_nX = m_pID_PICTURE_WallPaper->GetWidth();
	stMoveText.m_nY = 200;
	stMoveText.m_dwColor = /*0xffffD940*/dwColor;
	stMoveText.m_fMoveSpeed = 0.05f;
	stMoveText.m_dwStartTime = HQ_TimeGetTime();
	if(nAmount <= 0)
		stMoveText.pInfo = NULL;
	else
	{
		std::string str = parStr.substr(1,nAmount);
	   stMoveText.pInfo  = ExpressionManager::GetInstance().GetExpressionInfo(str);
	}
	
	if( !bPushFront )
		m_ltMoveText.push_back( stMoveText );
	else
	{
		// 插在队列最前面
		m_ltMoveText.push_front(stMoveText);
	}

	if (m_currMoveText.m_nCount == 0)
	{
		m_currMoveText = m_ltMoveText.front();
		m_ltMoveText.pop_front();
	}
	//
	SetVisable( true );
}
bool CUI_ID_FRAME_BullSystem::MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	if ( (bMsgUsed == true && WM_MOUSEMOVE != msg) || g_GameState != G_MAIN )
		return false;	

	switch( msg ) 
	{	
	case WM_KEYUP:
		{	
			switch( wParam )
			{
			case VK_ESCAPE:
				{						
					if ( s_CUI_ID_FRAME_BullSystem.m_ltMoveText.size() > 0 )
					{
						if( s_CUI_ID_FRAME_BullSystem.m_pID_FRAME_BullSystem )
							s_CUI_ID_FRAME_BullSystem.m_pID_FRAME_BullSystem->SetVisable( true );
					}
					return false;					
				}
				break;			
			}


		}break;
	}
	return false;
}

int  CUI_ID_FRAME_BullSystem::ShowExpression(ExpressionManager::ExpressionData *pInfo,int nLeft,int nTop)
{
	if(!pInfo)
		return 0;

	int nTexture = pInfo->GetTextureId();
	if (nTexture == -1)
	{
		return 0;
	}

	RECT rcDst;
	rcDst.left   = nLeft;
	rcDst.right  = rcDst.left +  pInfo->m_nWidth *  ControlObject::GetSCALE(NULL);

	rcDst.top    = nTop;
	rcDst.bottom = rcDst.top + pInfo->m_nHeight *  ControlObject::GetSCALE(NULL);

	ExpressionManager::GetInstance().DrawExpression(pInfo,rcDst);

	return pInfo->m_nWidth * ControlObject::GetSCALE(NULL); 	
}

void CUI_ID_FRAME_BullSystem::InitializeAtEnterWorld()
{
	m_ltMoveText.clear();
	m_currMoveText.Reset();
}