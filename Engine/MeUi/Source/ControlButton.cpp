#include "MeUi/ControlButton.h"
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Me3d/BaseGraphics.h"
#include "FuncPerformanceLog.h"
#include "LuaScript.h"
#include "Browser/Browser.h"
#include "MeFont/MeFontSystem.h" //##

extern HWND g_HelpHwnd;
extern const char* GetRootPath();

ControlButton::ControlButton(void)
{
	m_bLButtonDrag = false;
	m_bMouseMoveOn = false;
	m_pFunOnButtonClick = NULL;
	m_pFunOnLButtonDown = NULL;
	m_pFunOnLButtonUp = NULL;
	m_pFunOnMouseOn = NULL;
	//m_bShowTip = true;
	m_bIsPress = false;
	m_bMouseMove	=	true;

	_bIsShowTip = false;
	//
	m_strSound = UiManager::m_strButtonClickSound;
	m_strMoveOnSound = UiManager::m_strMoveOnSound;

	_luaTableName.clear();

	_funBtnClickName.clear();
	_funMouseOnName.clear();
	
}

ControlButton::~ControlButton(void)
{
}

void ControlButton::SetCaption(const char* strObjName)
{
	if( !strObjName )
	{
		m_strObjName.clear();
		return;
	}
	m_strObjName = strObjName;
	if (GetFrameFather())
	{
		GetFrameFather()->SetRedraw();
	}
}

extern DWORD g_dwColorTip0;
extern DWORD g_dwColorTip1;

void ControlButton::Render()
{
	if ( IsNeedRender() )
	{
		ControlObject::Render();
		
		if ( !m_bEnable )
		{
			S_ButtonData *pButtonData = (S_ButtonData*)m_pstData;
			SetPic( &pButtonData->m_stDisabledPic );

			m_nFontIndexCurr = m_nFontIndexDisabled;
			m_colFontCurr = pButtonData->m_colFontDisabled;
		}
		
		if ( m_strObjName.size() > 0 )
		{
			RECT rc = {0};
			GetRealRect( &rc );

			//##
  			FontSystem::DrawTextRGB( m_strObjName.c_str(), &rc, DT_VCENTER|DT_CENTER|DT_NOCLIP,
 								m_colFontCurr, m_nFontIndexCurr );

			std::wstring strObjName = Common::_tstring::toWideString( m_strObjName.c_str() );

					
// 			More::FloatRect fRc;
// 			RectToFloatRect( rc, &fRc );
// 			More::UIFontManager::GetInstance()->PrepareStringW( strObjName.c_str(), fRc, GetData()->m_nFontSize * GetSCALE(this), "c:/fzxh1jw.ttf", 
// 				m_colFontCurr, More::eFontSM_RightShadow, More::eFontRM_MM );
			//FontSystem::DrawTextRGB( m_strObjName.c_str(), &rc, DT_VCENTER|DT_CENTER,
			//					m_pstData->m_colFont, m_nFontIndex );
		}
		
		if ( m_pstData->m_szCaption[0] != 0 )
		{
			RECT rc;
			S_ButtonData *pButtonData = (S_ButtonData*)m_pstData;
			if ( pButtonData->m_stMoveOnPic.m_szPicName[0] == 0 &&
				pButtonData->m_stPressPic.m_szPicName[0] == 0 &&
				pButtonData->m_stBackPic.m_szPicName[0] == 0 )
			{
				GetRealRect( &rc );
				//FontSystem::DrawTextRGB( &rc, m_pstData->m_szCaption, m_pstData->m_colFont,
				//					m_nFontIndex, DT_VCENTER|DT_CENTER );
				FontSystem::DrawTextRGB( m_pstData->m_szCaption, &rc, DT_VCENTER|DT_CENTER|DT_NOCLIP,
									m_pstData->m_colFont, m_nFontIndex );

				std::wstring strObjName = Common::_tstring::toWideString( m_pstData->m_szCaption );		
// 				More::FloatRect fRc;
// 				RectToFloatRect( rc, &fRc );
// 				More::UIFontManager::GetInstance()->PrepareStringW( strObjName.c_str(), fRc, GetData()->m_nFontSize * GetSCALE(this), "fzxh1jw.ttf", 
// 					m_pstData->m_colFont, More::eFontSM_RightShadow, More::eFontRM_MM );
			}
			else
			{
				if ( 0/*m_bShowTip == true*/ && m_bMouseMoveOn == true )
				{
					m_bMouseMoveOn = PtInObject(theUiManager.m_ptMoust.x,
												theUiManager.m_ptMoust.y,false);

					//GetRealRect( &rc );
					
				//	UiDrawer::FillRect2D( rc, 0xcf000000 );
				//	FontSystem::DrawTextRGB( &rc, m_pstData->m_szCaption, m_pstData->m_colFont,
				///		m_nFontIndex, DT_VCENTER|DT_CENTER );
					//	UiDrawer::DrawRect2D( rc, 0xFF000000 );
					const int OFFSET_HEIGHT = 4;

					UINT nLength = strlen(m_pstData->m_szCaption);
					INT nWidth = m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this) *nLength/2;
					INT nHeight = m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this);
					rc.left = theUiManager.m_ptMoust.x-1;
					rc.top = theUiManager.m_ptMoust.y - m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this)
								- OFFSET_HEIGHT*2 - 2;
					if( rc.left < 0 )
						rc.left = 0;
					if( rc.top < 0 )
						rc.top = 0;
					if( rc.left > SCREEN_WIDTH - (nWidth+OFFSET_HEIGHT*2) )
						rc.left = SCREEN_WIDTH - (nWidth+OFFSET_HEIGHT*2);
					if( rc.top > SCREEN_HEIGHT - m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this) )
						rc.top = SCREEN_HEIGHT - m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this);
					rc.right = rc.left + nWidth + OFFSET_HEIGHT+1;
					rc.bottom = rc.top + nHeight + OFFSET_HEIGHT+1;
					RECT rcText = rc;
					rcText.left += OFFSET_HEIGHT;
					rcText.top += 1;

					UiDrawer::FillRect2D( rc, g_dwColorTip0 );
					//FontSystem::DrawTextRGB( &rcText, m_pstData->m_szCaption, /*m_pstData->m_colFont*/RGB(209,195,157),
					//			m_nFontIndex, /*DT_VCENTER|DT_CENTER*/0 );
					FontSystem::DrawTextRGB( m_pstData->m_szCaption, &rcText, DT_CENTER|DT_VCENTER|DT_NOCLIP,
											RGB(209,195,157), m_nFontIndex );
					UiDrawer::DrawRect2D( rc, g_dwColorTip1 );
					//
					//
					RECT rcF = rc;
					rcF.left += 1;
					rcF.top += 1;
					rcF.right -= 1;
					rcF.bottom -= 1;
					DWORD dwColorBottom = 0xFF929292;
					DWORD dwColorRight = 0xFF929292;
					DWORD dwColorLeft = 0xFF929292;
					DWORD dwColorTop = 0xFF929292;
					CBaseGraphics *g = GetDrawer();
					// 下
					g->DrawLine2D( rcF.left, rcF.bottom, rcF.right+1, rcF.bottom, dwColorBottom );
					// 右
					g->DrawLine2D( rcF.right, rcF.top, rcF.right, rcF.bottom, dwColorRight );
					// 左
					g->DrawLine2D( rcF.left, rcF.bottom, rcF.left, rcF.top, dwColorLeft );
					// 上
					g->DrawLine2D( rcF.left, rcF.top, rcF.right, rcF.top, dwColorTop );
				}
			}
		}
	}
}

void ControlButton::SetMouseMove(bool bMove)
{
	m_bMouseMove = bMove;
	return;
}

bool ControlButton::OnMouseMove( UINT nFlags, const int nX, const int nY )
{
	if( m_bMouseMove == false ) 
		return false;
	if ( IsVisable() )
	{
		// tip在disable下也显示, [12/8/2010 zhangjiayi]		
		bool bPtInObject = PtInObject(nX, nY,false);
		if( bPtInObject )
		{
			if( _bIsShowTip )
			{
				theIconInfoMouseTip.SetDisplayInfo( &TipInfo,
					nX, nY, false,
					m_nFontIndex, m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this),
					m_pstData->m_colFont,
					false );
			}
		}

		if ( m_bEnable )
		{
			S_ButtonData *pButtonData = (S_ButtonData*)m_pstData;
			if ( bPtInObject == true )
			{
				if ( m_bLButtonDrag == false )
				{
					if (pButtonData->m_stMoveOnPic.m_szPicName[0] != 0)
						SetPic( &pButtonData->m_stMoveOnPic );

					m_nFontIndexCurr = m_nFontIndexMoveOn;
					m_colFontCurr = pButtonData->m_colFontMoveOn;
				}
				//SetCursor( LoadCursor(NULL, IDC_HAND) );
				if ( m_bMouseMoveOn == false )
				{
					theUiManager.PlaySound( m_strMoveOnSound );
				}
				m_bMouseMoveOn = true;

				//  add
				if( NULL != state.Get() && _funMouseOnName.length() > 0 && _luaTableName.length() > 0 )
				{
					try
					{
						LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
						if( table1Obj.IsTable() )
						{
							LuaFunction<void> function_( table1Obj[_funMouseOnName.c_str()] );
							function_();
						}
					}
					catch (LuaPlus::LuaException &e)
					{
						char szErr[256] = {0};
						_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funMouseOnName.c_str(), e.GetErrorMessage());
						print_error( szErr );
					}
				}
				else
				{
					if ( m_pFunOnMouseOn )
					{
						m_pFunOnMouseOn( this );
					}
				}
				//--

			}
			else
			{
				//if ( !m_bIsPress )
				if( m_bMouseMoveOn)
				{
					if ( m_pstData->m_stBackPic.m_szPicName[0] != 0 ||
						pButtonData->m_stMoveOnPic.m_szPicName[0] != 0 )
					{
						SetPic( &m_pstData->m_stBackPic );
					}

					m_nFontIndexCurr = m_nFontIndexNormal;
					m_colFontCurr = pButtonData->m_colFontNormal;
				}
				m_bMouseMoveOn = false;
			}
		}
		else
		{
			S_ButtonData *pButtonData = (S_ButtonData*)m_pstData;
			SetPic( &pButtonData->m_stDisabledPic );

			m_nFontIndexCurr = m_nFontIndexDisabled;
			m_colFontCurr = pButtonData->m_colFontDisabled;
		}
	}
	return false;
}

bool ControlButton::OnLButtonDown( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		if ( m_bEnable )
		{
			if ( PtInObject(nX,nY,true) == true )
			{
				m_bLButtonDrag = true;
				SetPressPic();
				SetActivate();
				SetState(MouseDown);
				if (m_pFunOnLButtonDown)
					m_pFunOnLButtonDown(nX, nY);
				return m_bMsgHoldup;
			}
		}
	}
	return false;
}

bool ControlButton::OnLButtonUp( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		m_bLButtonDrag = false;
		if ( m_bEnable )
		{
			if ( PtInObject(nX,nY,true) == true )
			{
				if( GetState() != MouseDown )
					return false;

				SetState(MouseEnable);
				S_ButtonData *pButtonData = (S_ButtonData*)m_pstData;
				if ( pButtonData->m_stMoveOnPic.m_szPicName[0] != 0)
				{
					SetPic( &pButtonData->m_stMoveOnPic );
				}
				bool bResult = m_bMsgHoldup;
				ControlObject::PlaySound();
				SetNormalPic();
				OnButton();

				if (m_pFunOnLButtonUp)
					m_pFunOnLButtonUp(nX, nY);
				return bResult;
			}
		}
	}
	return false;
}

void ControlButton::SetPressPic()
{
	S_ButtonData *pButtonData = (S_ButtonData*)m_pstData;
	if ( pButtonData->m_stPressPic.m_szPicName[0] != 0 )
	{
		SetPic( &pButtonData->m_stPressPic );
	}
	m_bIsPress = true;

	m_nFontIndexCurr = m_nFontIndexPressed;
	m_colFontCurr = pButtonData->m_colFontPress;
}

void ControlButton::SetNormalPic()
{
	SetPic( &m_pstData->m_stBackPic );
	m_bIsPress = false;

	S_ButtonData *pButtonData = (S_ButtonData*)m_pstData;

	m_nFontIndexCurr = m_nFontIndexNormal;
	m_colFontCurr = pButtonData->m_colFontNormal;
}

void OpenHelp(const char* web)
{
	// 取消暂时关闭帮助界面
	//return;

	if (!g_HelpHwnd && theUiManager.m_pCreateHelpWindowFun)
	{
		g_HelpHwnd = theUiManager.m_pCreateHelpWindowFun();
	}

	if (g_HelpHwnd)
	{
		char fullname[MAX_PATH];
		if (strlen(web) == 0)
			sprintf( fullname, "%s/%s", GetRootPath(), "Data/Helper/helper.html" );
		else
			sprintf( fullname, "%s/%s", GetRootPath(), web );
		DisplayHTMLPage(g_HelpHwnd, fullname);
		ShowWindow( g_HelpHwnd, SW_SHOW );
	}
}

void ControlButton::OnButton(void)
{
	if( NULL != state.Get() && _luaTableName.length() > 0 && _funBtnClickName.length() > 0 )
	{
		try
		{
			LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
			if( table1Obj.IsTable() )
			{
				LuaFunction<void> function_( table1Obj[_funBtnClickName.c_str()] );
				function_();
			}
		}
		catch (LuaPlus::LuaException &e)
		{
			char szErr[256] = {0};
			_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funBtnClickName.c_str(), e.GetErrorMessage());
			print_error( szErr );
		}
	}
	else
	{
		if ( m_pFunOnButtonClick )
		{
			m_pFunOnButtonClick( this );

			if ( m_pFather && strcmp( m_pstData->m_szID, "ID_BUTTON_CLOSE" ) == 0 &&
				m_pFather->IsVisable() )
			{
				m_pFather->SetVisable( false );
			}
			else if ( stricmp( m_pstData->m_szID, "ID_BUTTON_Help" ) == 0 )
			{
				OpenHelp(m_pstData->m_szCaption);
			}
			return;
		}
	}

	if ( m_pFather && strcmp( m_pstData->m_szID, "ID_BUTTON_CLOSE" ) == 0 )
	{
		m_pFather->SetVisable( false );
	}
	else if ( stricmp( m_pstData->m_szID, "ID_BUTTON_Help" ) == 0 )
	{
		OpenHelp(m_pstData->m_szCaption);
	}
#ifdef _DEBUG
	else if ( m_debug_bHasWarning )
	{
		
		char szDebug[128];
		char szFatherID[128] = "";
		if ( m_pFather )
		{
			strcpy( szFatherID, m_pFather->GetControlID() );
		}
		sprintf(szDebug,"[%s]::[%s] OnButton(void) not defend!!\r\n", szFatherID, GetControlID() );
		//OutputDebugString(szDebug);
	}
#endif
}

bool ControlButton::OnKeyDown( UINT nChar )
{
	//if ( IsVisable() && nChar == VK_RETURN && IsActivated() )
	//{
	//	SetPressPic();
	//	OnButton();
	//	return true;
	//}
	return false;
}

bool ControlButton::OnKeyUp( UINT nChar )
{
	if ( IsVisable() && IsEnable() && nChar == VK_RETURN && IsActivated() )
	{
		SetNormalPic();
		return true;
	}
	return false;
}

void ControlButton::Create( IN const char* szCaption, IN const RECT* pRect,
						   IN funOnButtonClick pCallbackFun )
{
	assert( szCaption );
	assert( pRect );
	ReleaseUI();
	S_ButtonData *pButton = MeNew S_ButtonData;
	m_bNeedRelease = true;
	pButton->m_nType = Type_Button;
	strcpy( pButton->m_szCaption , szCaption );
	sprintf( pButton->m_szID, "ID_BUTTON_AUTO_%d", rand() );
	pButton->m_rcRealSize = *pRect;
	InitUIData( NULL, pButton );

	m_pFunOnButtonClick = pCallbackFun;
}

int ControlButton::CreateFont(char* szFont, int nFontSize, COLORREF& col, BOOL isBold)
{
	col |= 0xff000000;
	if ( col == 0xffffffff )
	{
		col = 0xffe6e6e6;
	}

	int nFontIndex = -1;
	//	m_nFontIndex = theFontManager.CreateFont( pData->m_szFont, pData->m_nFontSize );
	if ( strlen(szFont) > 0 && nFontSize > 0 )
	{
		//		m_nFontIndex = FontSystem::CreateFont( pData->m_szFont, pData->m_nFontSize );
		nFontIndex = FontSystem::CreateFont( szFont,
			nFontSize*ControlObjectGetREAL_SCALE(this),
			0,
			/*isBold ? FW_BOLD :*/ FW_NORMAL,
			1,
			FALSE,
			DEFAULT_CHARSET,
			OUT_TT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_DONTCARE,
			&m_hDC );
	}

	return nFontIndex;
}

void ControlButton::InitUIData( IN ControlObject* pFather, IN S_BaseData* pData )
{
	ControlObject::InitUIData( pFather, pData );
	if ( strcmp( m_pstData->m_szID, "ID_BUTTON_CLOSE" ) == 0 )
	{
		m_strSound = UiManager::m_strCloseSound;
	}

	S_ButtonData *pButtonData = (S_ButtonData*)m_pstData;
	m_strObjName = pButtonData->m_szText;

	m_nFontIndexNormal = CreateFont(pButtonData->m_szFontNormal,
		pButtonData->m_nFontSizeNormal ,
		pButtonData->m_colFontNormal,
		pButtonData->m_isFontBoldNormal);
	m_nFontIndexMoveOn = m_nFontIndexNormal;
	m_nFontIndexPressed = m_nFontIndexNormal;
	m_nFontIndexDisabled = m_nFontIndexNormal;

	m_nFontIndexCurr = m_nFontIndexNormal;
	m_colFontCurr = pButtonData->m_colFontNormal;
	
	SetShowTips();
}

S_ButtonData::S_Pic* ControlButton::getMouseMovePic()
{
	S_ButtonData *pButtonData = (S_ButtonData*)m_pstData;
	return &pButtonData->m_stMoveOnPic;
}
S_ButtonData::S_Pic* ControlButton::getMousePressPic()
{
	S_ButtonData *pButtonData = (S_ButtonData*)m_pstData;
	return &pButtonData->m_stPressPic;
}
S_ButtonData::S_Pic* ControlButton::getDisabledPic()
{
	S_ButtonData *pButtonData = (S_ButtonData*)m_pstData;
	return &pButtonData->m_stDisabledPic;
}
S_ButtonData::S_Pic* ControlButton::getBgPic()
{
	S_ButtonData *pButtonData = (S_ButtonData*)m_pstData;
	return &pButtonData->m_stBackPic;

}

void ControlButton::setMouseMovePic( S_ButtonData::S_Pic* pic )
{
	S_ButtonData *pButtonData = (S_ButtonData*)m_pstData;
	pButtonData->m_stMoveOnPic = *pic;
}
void ControlButton::setMousePressPic( S_ButtonData::S_Pic* pic )
{
	S_ButtonData *pButtonData = (S_ButtonData*)m_pstData;
	pButtonData->m_stPressPic = *pic;
}
void ControlButton::setDisabledPic( S_ButtonData::S_Pic* pic )
{
	S_ButtonData *pButtonData = (S_ButtonData*)m_pstData;
	pButtonData->m_stDisabledPic = *pic;
}
void ControlButton::setBgPic( S_ButtonData::S_Pic* pic )
{
	S_ButtonData *pButtonData = (S_ButtonData*)m_pstData;
	pButtonData->m_stBackPic = *pic;

}

void ControlButton::SetEnable( bool b )
{
	if (m_bEnable == b)
		return;

	m_bEnable = b;
	if ( m_bEnable )
	{
		SetNormalPic();
	}
	else
	{
		S_ButtonData *pButtonData = (S_ButtonData*)m_pstData;
		SetPic( &pButtonData->m_stDisabledPic );

		m_nFontIndexCurr = m_nFontIndexDisabled;
		m_colFontCurr = pButtonData->m_colFontDisabled;
	}
}

void ControlButton::SetButtonClickFun( void* pFun )
{
	m_pFunOnButtonClick = (funOnButtonClick)pFun;
}

void ControlButton::SetLButtonDownFun( funOnLButtonDown pFun )
{
	m_pFunOnLButtonDown = pFun;
}

void ControlButton::SetLButtonUpFun( funOnLButtonUp pFun )
{
	m_pFunOnLButtonUp = pFun;
}

void ControlButton::SetButtonClickFun_2lua( const char* luaTable, const char* funName )
{
	_luaTableName = luaTable;
	_funBtnClickName = funName;
}
void ControlButton::SetButtonMouseOnFun_2lua( const char* luaTable, const char* funName )
{
	_luaTableName = luaTable;
	_funMouseOnName = funName;
}
void ControlButton::SetButtonMouseOnFun( IN funOnMouseOn pFun)
{
	m_pFunOnMouseOn = pFun;
}
void ControlButton::setTip(const char* data)
{
	guardfunc;
	if( NULL == data )
		return;
		
	TipInfo.SetInfo( data, DT_LEFT | DT_VCENTER );	
	unguard;
}

void ControlButton::ResetDevice()
{
	ControlObject::ResetDevice();

	S_ButtonData *pButtonData = (S_ButtonData*)m_pstData;
	m_nFontIndexNormal = CreateFont(pButtonData->m_szFontNormal,
		pButtonData->m_nFontSizeNormal,
		pButtonData->m_colFontNormal,
		pButtonData->m_isFontBoldNormal);
	m_nFontIndexMoveOn = m_nFontIndexNormal;
	m_nFontIndexPressed = m_nFontIndexNormal;
	m_nFontIndexDisabled = m_nFontIndexNormal;

	if (m_pstPic == &pButtonData->m_stPressPic)
	{
		m_nFontIndexCurr = m_nFontIndexPressed;
	}
	else if (m_pstPic == &pButtonData->m_stMoveOnPic)
	{
		m_nFontIndexCurr = m_nFontIndexMoveOn;
	}
	else if (m_pstPic == &pButtonData->m_stDisabledPic)
	{
		m_nFontIndexCurr = m_nFontIndexDisabled;
	}
	else
	{
		m_nFontIndexCurr = m_nFontIndexNormal;
	}
}

void ControlButton::SetShowTips()
{
	if (strlen(m_pstData->m_szTips) != 0)
	{
		_bIsShowTip = true;
		setTip(m_pstData->m_szTips);
	}
}
