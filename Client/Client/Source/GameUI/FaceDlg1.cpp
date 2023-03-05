/********************************************************************
Created by UIEditor.exe
FileName: E:\Work\HeroRuntime\Client\DATA\UI\FaceDlg1.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "FaceDlg1.h"
#include "GameMain.h"
#include "FuncPerformanceLog.h"
#include "ItemDetail.h"
#include "MeUi/ExpressionManager.h"
#include "Me3d/Engine/Engine.h"
#include "Me3d/Engine/RendererDx8.h"
#include "Me3d/Engine/EngineInstance.h"
#include "ChatInfoBox.h"
#include "Message_Chat.h"
#include "color_config.h"
#include "ui/MiniMapUI.h"
#include "ChatMessageMgr.h"
#include "MeUi/IconManager.h"
#include "MeFont/MeFontSystem.h"

#define PAGE_SIZE 50

extern bool g_bMessageChat		= false;
CUI_ID_FRAME_FACE s_CUI_ID_FRAME_FACE;
MAP_FRAME_RUN( s_CUI_ID_FRAME_FACE, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_FACE, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FACE, ID_BUTTON_leftOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FACE, ID_BUTTON_rightOnButtonClick )

CUI_ID_FRAME_FACE::CUI_ID_FRAME_FACE()
{
	guardfunc;
//	GuildMember
	m_pID_FRAME_FACE = NULL;
// 	m_pID_PICTURE_BG = NULL;
	m_pID_PICTURE_DECT = NULL;
	m_pID_BUTTON_left = NULL;
	m_pID_BUTTON_right = NULL;
	m_pID_TEXT_Page = NULL;

	m_nExpressionCount = -1;
	m_nCursorOn				= -1;
	m_bEditWidgetActive				= false;
	m_nCount = 0;
	m_nFontSize = 0;
	m_nFontIndex = 0;
	m_fFontScale = 1.f;
	m_bNeedGetFontInfo = true;

	m_curPage = 1;
	m_totalPage = 1;
	m_curPageOn = -1;

	unguard;
}
// Frame
bool CUI_ID_FRAME_FACE::OnFrameRun()
{
	guardfunc;
	if (m_nExpressionCount == -1)
	{
		/*std::vector<ExpressionManager::ExpressionData*>& expressionList = ExpressionManager::GetInstance().GetExpressionList();
		m_nExpressionCount = expressionList.size();
		if (m_nExpressionCount > 50)
		{
			m_nExpressionCount = 50;
		}*/

		std::vector<unsigned short>& expressionListIndex = ExpressionManager::GetInstance().GetChatExpressionListIndex();
		m_nExpressionCount = expressionListIndex.size();
	}
	return true;
	unguard;
}

bool CUI_ID_FRAME_FACE::OnFrameRender()
{	
	guardfunc;
	std::vector<ExpressionManager::ExpressionData*>& expressionList = ExpressionManager::GetInstance().GetExpressionList();
	std::vector<unsigned short>& expressionListIndex = ExpressionManager::GetInstance().GetChatExpressionListIndex();
	RECT rcWindow;
	m_pID_PICTURE_DECT->GetRealRect(&rcWindow);

	int nStart = ( m_curPage - 1 ) * PAGE_SIZE;
	if ( nStart < 0 )
		nStart = 0;

	for (/*int i = 0; i < m_nExpressionCount;++i*/int i = nStart, j = 0; i < m_nExpressionCount && j < PAGE_SIZE; i++, j++)
	{
		RECT dstRc = {rcWindow.left + 40*(/*i*/j%10)*ControlObject::GetSCALE(m_pID_FRAME_FACE),rcWindow.top + 40*(/*i*/j/10)*ControlObject::GetSCALE(m_pID_FRAME_FACE),rcWindow.left + 40*(/*i*/j%10 + 1)*ControlObject::GetSCALE(m_pID_FRAME_FACE),rcWindow.top + 40*(/*i*/j/10 +1)*ControlObject::GetSCALE(m_pID_FRAME_FACE)};
		ExpressionManager::GetInstance().DrawExpression(expressionList[/*i*/expressionListIndex[i]],dstRc);
		if (m_nCursorOn == i)
		{
			RECT rcSrc = {0,0,40,40};
			GetDrawer()->Blt(m_selectImgId,&dstRc,&rcSrc,40,40,0,0xFFFFFFFF,0);
		}
	}
	if(m_nCursorOn != -1 && m_curPageOn < PAGE_SIZE)
	{
		if(!m_pID_PICTURE_DECT->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
		{
			m_nCursorOn = -1;
			m_curPageOn = -1;
		}
		else 
		{
			if( m_bNeedGetFontInfo && s_CUI_ID_FRAME_MiniMap.GetTEXT_PlayerPos() )	// 渲表情tips为什么要依赖小地图控件获取字体数据，需要修正
			{
				m_bNeedGetFontInfo = false;
				m_nFontSize = s_CUI_ID_FRAME_MiniMap.GetTEXT_PlayerPos()->GetFontSize();
				m_nFontIndex = s_CUI_ID_FRAME_MiniMap.GetTEXT_PlayerPos()->GetFontIndex();
				m_fFontScale = ControlObject::GetREAL_SCALE(s_CUI_ID_FRAME_MiniMap.GetTEXT_PlayerPos());
			}
			ExpressionManager::ExpressionData* pData = expressionList[/*m_nCursorOn*/expressionListIndex[m_nCursorOn]];

			const int OFFSET_HEIGHT = 4;
			UINT nLength = strlen(pData->m_Tip.c_str());
			INT nWidth = m_nFontSize * m_fFontScale * nLength / 2;
			INT nHeight = m_nFontSize * m_fFontScale;
			RECT rc;
			rc.left = theUiManager.m_ptMoust.x-1;
			rc.top = theUiManager.m_ptMoust.y - m_nFontSize * m_fFontScale - OFFSET_HEIGHT*2 - 2;
			if( rc.left < 0 )
				rc.left = 0;
			if( rc.top < 0 )
				rc.top = 0;
			if( rc.left > SCREEN_WIDTH - (nWidth+OFFSET_HEIGHT*2) )
				rc.left = SCREEN_WIDTH - (nWidth+OFFSET_HEIGHT*2);
			if( rc.top > SCREEN_HEIGHT - m_nFontSize * m_fFontScale )
				rc.top = SCREEN_HEIGHT - m_nFontSize * m_fFontScale;
			rc.right = rc.left + nWidth + OFFSET_HEIGHT+1;
			rc.bottom = rc.top + nHeight + OFFSET_HEIGHT+1;
			RECT rcText = rc;
			rcText.left += OFFSET_HEIGHT;
			rcText.top += 1;
			static int s_NineGridePic = -1;
			theControlPictureManager.RenderNineGrid(
				s_NineGridePic,
				TIP_FRAME_FILENAME,
				TIP_FRAME_TOTALWIDTH,
				TIP_FRAME_TOTALHEIGHT,
				TIP_FRAME_GRIDWIDTH,
				TIP_FRAME_GRIDHEIGHT,
				&rc
				);


			UiDrawer::FillRect2D( rc, 0xC8000000 );

			FontRender::EFontRenders eOldIdx = FontRender::EFR_FIRST;
			if( FontSystem::IsUseNewFont() )
			{
				eOldIdx = FontRender::getFontRender()->GetDefaultRendererIdx();
				FontRender::getFontRender()->SetDefaultRendererIdx( FontRender::EFR_THIRD );
				FontSystem::ClearRender( FontRender::EFR_THIRD );
			}
			//FontSystem::DrawTextRGB( &rcText, m_pstData->m_szCaption, /*m_pstData->m_colFont*/RGB(209,195,157),
			//			m_nFontIndex, /*DT_VCENTER|DT_CENTER*/0 );
			FontSystem::DrawTextRGB( pData->m_Tip.c_str(), &rcText, DT_CENTER|DT_VCENTER|DT_NOCLIP,
				Color_Config.getColor(CC_MINIMAP_TIP), m_nFontIndex );

			if( FontSystem::IsUseNewFont() )
			{
				FontRender::getFontRender()->SetDefaultRendererIdx( eOldIdx );
				FontSystem::DoRender( FontRender::EFR_THIRD );
			}	

			
// 			UiDrawer::DrawRect2D( rc, 0xFF000000 );
// 			//
// 			//
// 			RECT rcF = rc;
// 			rcF.left += 1;
// 			rcF.top += 1;
// 			rcF.right -= 1;
// 			rcF.bottom -= 1;
// 			DWORD dwColorBottom = 0xFF929292;
// 			DWORD dwColorRight = 0xFF929292;
// 			DWORD dwColorLeft = 0xFF929292;
// 			DWORD dwColorTop = 0xFF929292;
// 			CBaseGraphics *g = GetDrawer();
// 			// 下
// 			g->DrawLine2D( rcF.left, rcF.bottom, rcF.right+1, rcF.bottom, dwColorBottom );
// 			// 右
// 			g->DrawLine2D( rcF.right, rcF.top, rcF.right, rcF.bottom, dwColorRight );
// 			// 左
// 			g->DrawLine2D( rcF.left, rcF.bottom, rcF.left, rcF.top, dwColorLeft );
// 			// 上
// 			g->DrawLine2D( rcF.left, rcF.top, rcF.right, rcF.top, dwColorTop );



// 			int nLength = strlen( pData->m_Tip.c_str() )*6+4;
// 			int nTipX = theUiManager.m_ptMoust.x;
// 			int nTipY = theUiManager.m_ptMoust.y-32;
// 
// 			// modifed, jiayi, [2009/8/27]
// 			RECT rcText;
// 			rcText.left = nTipX;
// 			rcText.top = nTipY;
// 			rcText.right = rcText.left + nLength;
// 			rcText.bottom = nTipY + nLength;
// 
// 			FontSystem::DrawText( pData->m_Tip.c_str(), &rcText, 0,
// 				Color_Config.getColor(CC_MINIMAP_TIP),
// 				UI_ID_FRAME_MiniMap::m_pID_TEXT_PlayerPos->GetFontIndex() );
		}
	}
	if (IsVisable() && m_bEditWidgetActive)
	{
		CommonChatFrame* pActive = CommonChatFrame::GetActiveChatFrame();
		pActive->Begin2Input();
		pActive->SetEditFocus();
	}
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_FACE::ID_BUTTON_leftOnButtonClick( ControlObject* pSender )
{
	if ( m_curPage > 1 )
	{
		m_curPage--;
		ShowPage();
		RefreshPageEnable();
	}
	return true;
}
// Button
bool CUI_ID_FRAME_FACE::ID_BUTTON_rightOnButtonClick( ControlObject* pSender )
{
	if ( m_curPage < m_totalPage )
	{
		m_curPage++;
		ShowPage();
		RefreshPageEnable();
	}
	return true;
}

// 装载UI
bool CUI_ID_FRAME_FACE::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\FaceDlg1.meui", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\FaceDlg1.UI]失败")
		return false;
	}
// 	else if ( dwResult != 1140/*文件版本号*/ )
// 	{
// 		MESSAGE_BOX("读取文件[UI\\FaceDlg1.UI]与源代码版本不一样")
// 	}
	return DoControlConnect();
	unguard;
}

bool CUI_ID_FRAME_FACE::ChatMsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed)
{
		return s_CUI_ID_FRAME_FACE.MsgProc(msg, wParam, lParam, bMsgUsed);
}

// 关连控件
bool CUI_ID_FRAME_FACE::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_FACE, s_CUI_ID_FRAME_FACEOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_FACE, s_CUI_ID_FRAME_FACEOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_FACE, ID_BUTTON_left, s_CUI_ID_FRAME_FACEID_BUTTON_leftOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_FACE, ID_BUTTON_right, s_CUI_ID_FRAME_FACEID_BUTTON_rightOnButtonClick );

	m_pID_FRAME_FACE = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_FACE );
// 		m_pID_PICTURE_BG = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FACE, ID_PICTURE_BG );
	m_pID_PICTURE_DECT = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FACE, ID_PICTURE_DECT );
	m_pID_BUTTON_left = (ControlButton*)theUiManager.FindControl( ID_FRAME_FACE, ID_BUTTON_left );
	m_pID_BUTTON_right = (ControlButton*)theUiManager.FindControl( ID_FRAME_FACE, ID_BUTTON_right );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_FACE, ID_TEXT_Page );
	assert( m_pID_FRAME_FACE );
// 		assert( m_pID_PICTURE_BG );
	assert( m_pID_PICTURE_DECT );
	assert( m_pID_BUTTON_left );
	assert( m_pID_BUTTON_right );
	assert( m_pID_TEXT_Page );

	m_pID_PICTURE_DECT->SetButtonClickFun(On_PICTURE_ExpressionRECTClick);
	m_pID_PICTURE_DECT->SetOnMouseOn(On_PICTURE_ExpressionRECTMouseOn);

	char fullpath[MAX_PATH] = {0};
	sprintf( fullpath, "%s\\Data\\Ui\\Icon\\IconSelectFrame.dds", GetRootPath() );
	ITextureManager* pMgr = GetEngine()->GetTextureManager();
	m_selectImgId = pMgr->RegisterTexture(fullpath,FALSE,FALSE);
	m_bEditWidgetActive = true;

	SetVisable( false );
	m_pID_FRAME_FACE->SetMsgProcFun(ChatMsgProc);
	return true;
	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_FACE::_UnLoadUI()
{
	guardfunc;
	m_pID_FRAME_FACE = NULL;
	return theUiManager.RemoveFrame( "data\\ui\\FaceDlg1.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_FACE::_IsVisable()
{
	guardfunc;
	if(!m_pID_FRAME_FACE)
		return false;

	return m_pID_FRAME_FACE->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_FACE::_SetVisable( const bool bVisable )
{
	guardfunc;
	if(!m_pID_FRAME_FACE)
		return ;

	if ( bVisable )
	{
		//top
		theUiManager.ToTop( m_pID_FRAME_FACE );
		m_bEditWidgetActive = false;

		SetTotalPage();
		ShowPage();
		RefreshPageEnable();
	}
	else
	{
		{
			m_nCount = 0;
		}
		m_nCursorOn = -1;
		m_curPageOn = -1;
	}
    if(m_pID_FRAME_FACE)
	    m_pID_FRAME_FACE->SetVisable( bVisable );
	unguard;
}

bool CUI_ID_FRAME_FACE::On_PICTURE_ExpressionRECTClick( ControlObject* pSender )
{
	if(!pSender->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
	{
		return false;
	}
	int nClicked = -1;
	RECT rect;
	s_CUI_ID_FRAME_FACE.m_pID_PICTURE_DECT->GetRealRect(&rect);
	int nDeltaX = (theUiManager.m_ptMoust.x - rect.left);
	int nDeltaY = (theUiManager.m_ptMoust.y - rect.top);
	float fScale = ControlObject::GetSCALE(s_CUI_ID_FRAME_FACE.m_pID_FRAME_FACE) ;
	if (nDeltaX > 400*fScale|| nDeltaY > 200*fScale)
	{
		return false;
	}

	int nStart = ( s_CUI_ID_FRAME_FACE.m_curPage - 1 ) * PAGE_SIZE;
	if ( nStart < 0 )
		nStart = 0;

	nClicked = nDeltaX/(int)(fScale*40 )+ (nDeltaY/(int)(fScale*40 ))*10 + nStart;
	if (nClicked >= s_CUI_ID_FRAME_FACE.m_nExpressionCount)
	{
		return false;
	}
// 	if (s_CUI_ID_FRAME_FACE.m_nCount >= 3)
// 	{
// 		return false;
// 	}
	std::vector<ExpressionManager::ExpressionData*>& expressionList = ExpressionManager::GetInstance().GetExpressionList();
	std::vector<unsigned short>& expressionListIndex = ExpressionManager::GetInstance().GetChatExpressionListIndex();
	ExpressionManager::ExpressionData* pData = expressionList[/*nClicked*/expressionListIndex[nClicked]];
	std::string currString = CommonChatFrame::GetActiveChatFrame()->GetEditText();
	int nCount = ExpressionManager::GetInstance().AddExpressionAni(currString,3);
	if (nCount < 3)
	{
		CommonChatFrame::GetActiveChatFrame()->addText(ExpressionManager::GetInstance().GetExpressionKeyFromInfo(pData));
	}
	s_CUI_ID_FRAME_FACE.m_bEditWidgetActive = true;
// 	++s_CUI_ID_FRAME_FACE.m_nCount;
	return true;

}

void CUI_ID_FRAME_FACE::On_PICTURE_ExpressionRECTMouseOn( ControlObject* pSender )
{
// 	if(!pSender->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
// 	{
// 		s_CUI_ID_FRAME_FACE.m_nCursorOn = -1;
// 		return ;
// 	}
	float fScale = ControlObject::GetSCALE(s_CUI_ID_FRAME_FACE.m_pID_FRAME_FACE) ;
	RECT rect;
	s_CUI_ID_FRAME_FACE.m_pID_PICTURE_DECT->GetRealRect(&rect);
	int nDeltaX = (theUiManager.m_ptMoust.x - rect.left);
	int nDeltaY = (theUiManager.m_ptMoust.y - rect.top);
	if (nDeltaX > 400*fScale || nDeltaY > 200*fScale)
	{
		s_CUI_ID_FRAME_FACE.m_nCursorOn = -1;
		s_CUI_ID_FRAME_FACE.m_curPageOn = -1;
		return ;
	}

	int nStart = ( s_CUI_ID_FRAME_FACE.m_curPage - 1 ) * PAGE_SIZE;
	if ( nStart < 0 )
		nStart = 0;

	s_CUI_ID_FRAME_FACE.m_nCursorOn = nDeltaX/((int)(fScale*40 )) + (nDeltaY/((int)(fScale*40 )) )*10 + nStart;
	s_CUI_ID_FRAME_FACE.m_curPageOn = nDeltaX/((int)(fScale*40 )) + (nDeltaY/((int)(fScale*40 )) )*10;

	if (s_CUI_ID_FRAME_FACE.m_nCursorOn >= s_CUI_ID_FRAME_FACE.m_nExpressionCount)
	{
		s_CUI_ID_FRAME_FACE.m_nCursorOn = -1;
		s_CUI_ID_FRAME_FACE.m_curPageOn = -1;
	}
}
extern GAME_STATE g_GameState;
bool CUI_ID_FRAME_FACE::MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	if ( (bMsgUsed == true && WM_MOUSEMOVE != msg) || g_GameState != G_MAIN )
		return false;	

	if( !IsVisable() )
		return false;

	switch( msg ) 
	{
	case WM_KEYUP:
		{			
			if ( wParam == VK_RETURN )
			{
				if (IsVisable())
				{
					SetVisable(false);
					return CommonChatFrame::GetActiveChatFrame()->ID_BUTTON_EnterOnButtonClick(NULL);
				}
			}
		}break;
	}
	return false;
}

void CUI_ID_FRAME_FACE::SetScreenPos(int x,int y)
{
	if(m_pID_FRAME_FACE)
		m_pID_FRAME_FACE->SetScreenPos(x,y);
	else	
		assert(false&&"ui error");
}

void CUI_ID_FRAME_FACE::SetPos(int x,int y)
{
	if(m_pID_FRAME_FACE)
		m_pID_FRAME_FACE->SetPos(x,y);
	else	
		assert(false&&"ui error");
}

int CUI_ID_FRAME_FACE::GetAlignMode()
{
	if(m_pID_FRAME_FACE)
		return m_pID_FRAME_FACE->GetData()->m_nAlignMode;
	else	
		assert(false&&"ui error");

	return 0;
}

void CUI_ID_FRAME_FACE::SetAlignMode( int i )
{
	if(m_pID_FRAME_FACE)
		m_pID_FRAME_FACE->GetData()->m_nAlignMode = i;
	else	
		assert(false&&"ui error");
}

void CUI_ID_FRAME_FACE::SetTotalPage()
{
	int nsize = 0;
	int nsurplus = 0;

	std::vector<unsigned short>& expressionListIndex = ExpressionManager::GetInstance().GetChatExpressionListIndex();
	int nCount = expressionListIndex.size();

	nsize = nCount;

	nsurplus = nsize % PAGE_SIZE;
	m_totalPage = nsize / PAGE_SIZE + ( nsurplus > 0 ? 1 : 0 );
	if ( m_totalPage == 0 )
		m_totalPage = 1;

	m_curPage = 1;
}

void CUI_ID_FRAME_FACE::ShowPage()
{
	if ( !m_pID_TEXT_Page )
		return;

	char buf[24] = {0};
	sprintf_s( buf, sizeof(buf) - 1, "%d/%d", m_curPage, m_totalPage );
	m_pID_TEXT_Page->SetText( buf );
}

void CUI_ID_FRAME_FACE::RefreshPageEnable()
{
	if ( !m_pID_BUTTON_left || !m_pID_BUTTON_right )
		return;

	m_pID_BUTTON_left->SetEnable( true );
	m_pID_BUTTON_right->SetEnable( true );

	if (  m_curPage <= 1 )
		m_pID_BUTTON_left->SetEnable( false );

	if ( m_curPage >= m_totalPage )
		m_pID_BUTTON_right->SetEnable( false );
}