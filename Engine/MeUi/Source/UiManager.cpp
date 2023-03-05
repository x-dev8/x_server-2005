#include "MeUi/MeUi.h"
#include <Windowsx.h>
#include <commctrl.h>
#include "MeUi/UiManager.h"
#include "MeUi/UiRender.h"
#include "FuncPerformanceLog.h"
#include "MeUi/Animation/SmartAnimation.h"

extern HWND g_hWnd;
extern const char* GetRootPath();
UiManager theUiManager;

void UiLogInfo( const char* szInfo )
{
	if( UiManager::m_pLogInfoFun )
		UiManager::m_pLogInfoFun( szInfo );
}

namespace irr
{
	UiManager*	UiManagerInstance()
	{
		return &theUiManager;
	}
}
//static std::vector< std::vector<UiManager::S_UI> > UiManager::m_vtUI;
//
std::string	UiManager::m_strButtonClickSound;
std::string	UiManager::m_strMoveOnSound;
std::string	UiManager::m_strCheckBoxSound;
std::string	UiManager::m_strIconDragSound;
std::string	UiManager::m_strListSound;
std::string	UiManager::m_strScrollBarSound;
std::string	UiManager::m_strCloseSound;
UiManager::funLogInfo UiManager::m_pLogInfoFun = NULL;
UiManager::funRButtonUp UiManager::m_pRButtonUpFun = NULL;
UiManager::funcCreateHelpWindow UiManager::m_pCreateHelpWindowFun = NULL;

UiManager::UiManager(void)
{
	m_pFocus = NULL;
	m_bDragFrame = false;
	m_bIsMouseInUI = false;
	m_pPlaySoundFun = NULL;	
	m_pFatherFocus	=	NULL;

	m_vtUI.resize(UI_Render_LayerMax);

	_luaTableName.clear();
	_funPlaySoundName.clear();
	_funLogInfoName.clear();
	m_vtNeedRelease.clear();

//     m_pCaptureObj = NULL;
	m_bJumpNextLButtonUp = false;
}

UiManager::~UiManager(void)
{
}
void UiManager::DestroyNeedRelease()
{
	for(UINT i=0; i<m_vtNeedRelease.size(); ++i)
	{
		delete m_vtNeedRelease[i];
	}
	m_vtNeedRelease.clear();
}
void UiManager::Destroy()
{
	//FontSystem::ReleaseFonts();

	for( int index = 0; index<m_vtUI.size(); ++index )
	{
		for( int n=0; n<m_vtUI[index].size(); n++ )
		{
			delete m_vtUI[index][n];
		}
		m_vtUI[index].clear();
	}
	for(UINT i=0; i<m_vtNeedRelease.size(); ++i)
	{
		delete m_vtNeedRelease[i];
	}
	m_vtNeedRelease.clear();

	//More::UIFontManager::Shutdown();
}
#ifdef _DEBUG
static DWORD g_debug_dwHRUIFrameMoveUseTime = 0;
static DWORD g_debug_dwHRUIRenderUseTime = 0;
static DWORD g_debug_dwHRUIMsgProcUseTime = 0;
#endif

void UiManager::FrameMove()
{
	MeScopeProfileUiManagerFun
	guardfunc;
	//TRUETIMEFUNC();
#ifdef _DEBUG
	// 使用时间
	g_debug_dwHRUIFrameMoveUseTime = HQ_TimeGetTime();
#endif
	if (theMouseManager.GetUICursor() == MouseManager::Type_PathFinding
		|| theMouseManager.GetUICursor() == MouseManager::Type_ChatHyper
		|| theMouseManager.GetUICursor() == MouseManager::Type_ChatPlayer
		|| theMouseManager.GetUICursor() == MouseManager::Type_LeftDrag
		)
	{
		theMouseManager.SetCanSetCursor(true);
		theMouseManager.SetUICursor(MouseManager::Type_Arrow);
	}

	for( int index = 0; index < m_vtUI.size(); ++index )
	{
		for( int n=0; n<m_vtUI[index].size(); n++ )
		{
			if( m_vtUI[index][n]->m_pUI )
				m_vtUI[index][n]->m_pUI->Run();
		}
	}
	theIconDragManager.Run();
	theControlPictureManager.Run();

// #ifdef _DEBUG
// 	g_debug_dwHRUIFrameMoveUseTime = HQ_TimeGetTime()-g_debug_dwHRUIFrameMoveUseTime;
// 	// reload
// 	static DWORD dwTime = HQ_TimeGetTime();
// 
// 	for( int index = 0; index < m_vtUI.size(); ++index )
// 	{
// 		if ( m_vtUI[index].size() > 0 &&
// 			GetAsyncKeyState(VK_LCONTROL) && 
// 			GetAsyncKeyState('R') &&
// 			GetAsyncKeyState('L') &&
// 			HQ_TimeGetTime() - dwTime > 250 )
// 		{
// 			char szMessage[128];
// 			sprintf( szMessage, "文件:%s", m_vtUI[index][0]->m_strFileName.c_str() );
// 			if ( MessageBox( NULL, szMessage, "是否重新载入UI", MB_YESNO ) == IDYES )
// 			{
// 				//ReAddTopFrame();
// 			}
// 			dwTime = HQ_TimeGetTime();
// 		}
// 	}
// #endif
	unguard;
}

void UiManager::RenderTips()
{
	MeScopeProfileUiManagerFun
	guardfunc;
	{
		//TRUETIMEBLOCK( "theIconInfoMouseTip.Render" );
		theIconInfoMouseTip.Render();
	}
	unguard;

}

void UiManager::Render()
{
	MeScopeProfileUiManagerFun
	guardfunc;
	//TRUETIMEFUNC();
#ifdef _DEBUG
	// 使用时间
	g_debug_dwHRUIRenderUseTime = HQ_TimeGetTime();
#endif

	bool bTopIsModal = false;
	int nRenderCount = 0;
	// added, jiayi, [2009/9/17]
	if( HasModalWindow( 2 ) )
		bTopIsModal = true;

	guard(UIRender);
	{
// 		More::UIFontManager::Init();
// 		// add temp font
// 		More::Font font( 24, 72, "c:/fzxh1jw.ttf" );
// 		const wchar_t* pwcString = L"开始游戏关闭结束登陆确定取消退出进入选择服务器";
// 		for( size_t i = 0 ; i < wcslen( pwcString ); ++ i )
// 		{
// 			font.AddFontCode( pwcString[i] );
// 		}
// 		More::UIFontManager::GetInstance()->AddFont( font );
	}
	for( int index = 0; index < m_vtUI.size(); ++index )
	{
		for( int n = m_vtUI[index].size() - 1; n >= 0; n-- )
		{
			if( m_vtUI[index][n]->m_pUI->IsNeedRender() && !m_vtUI[index][n]->m_pUI->GetFather() )/*&&
																								  m_vtUI[n].m_pUI->IsCovered() == false )*/
			{
				//if(m_vtUI[n].m_pUI->IsVisable())

				if( ( index == 2 ) && ( n == 0 ) && bTopIsModal )
					continue;

				m_vtUI[index][n]->m_pUI->Render();

				nRenderCount++;

				//if( nRenderCount > 4 ) break;
			}
		}
		// end of each frame, add font quad
		//More::UIFontManager::GetInstance()->UpdateGeometryPosition();
	}
	

	//char szBuf[256];
	//_snprintf( szBuf, 256, "nRenderCount = %d", nRenderCount );
	//OutputDebugString( szBuf );
	unguard;

	guard(UIIconDragRender);
	{
		//TRUETIMEBLOCK( "theIconDragManager.Render" );
		theIconDragManager.Render();
	}	
	unguard;

	UiDrawer::FillFullScreen( SCREEN_WIDTH, SCREEN_HEIGHT );

	if( bTopIsModal )
	{

		m_vtUI[2][0]->m_pUI->Render();
		nRenderCount++;
	}

	if (GetFocus() && GetFocus()->GetControlType() == Type_Edit)
	{
		if (!bTopIsModal || m_vtUI[2][0]->m_pUI ==  GetFocus()->GetFrameFather())
		{
			ControlEdit* pEdit = (ControlEdit*)(GetFocus());
			pEdit->DrawFlashBar();
		}
	}
	if (GetFocus() && ((GetFocus()->GetControlType() == Type_Edit) || (GetFocus()->GetControlType() == Type_Edit)))
	{
		if (!bTopIsModal || m_vtUI[2][0]->m_pUI ==  GetFocus()->GetFrameFather())
		{
			ControlText* pEdit = (ControlText*)(GetFocus());
			pEdit->DrawSelectTextForeGround();
		}		
	}

// #ifdef _DEBUG
// 	// 贴图
// 	static bool bShow = false;
// 	static DWORD dwTime = HQ_TimeGetTime();
// 	char szDebug[256];
// 	RECT rc;
// 	rc.left = 0;
// 	rc.right = 500;
// 	rc.top = 20;
// 	rc.bottom = rc.top + 20;
// 	COLORREF col = RGB(255,0,0);
// 	if ( GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState('D') && GetAsyncKeyState('B') &&
// 		HQ_TimeGetTime() - dwTime > 250 )
// 	{
// 		bShow = !bShow;
// 		dwTime = HQ_TimeGetTime();
// 	}
// 
// 	if (bShow)
// 	{
// 		// 界面Render使用时间
// 		g_debug_dwHRUIRenderUseTime = HQ_TimeGetTime()-g_debug_dwHRUIRenderUseTime;
// 		sprintf( szDebug, "界面使用时间:%d(总)=%d(Render)+%d(FrameMove)+%d(MsgProc)",
// 					g_debug_dwHRUIFrameMoveUseTime+g_debug_dwHRUIRenderUseTime+g_debug_dwHRUIMsgProcUseTime,
// 					g_debug_dwHRUIRenderUseTime,
// 					g_debug_dwHRUIFrameMoveUseTime,
// 					g_debug_dwHRUIMsgProcUseTime );
// 		rc.top+=20;
// 		rc.bottom+=20;
// 		//FontSystem::DrawTextRGB( &rc, szDebug, col );
// 		FontSystem::DrawTextRGB( szDebug, &rc, 0, col );
// 
// 		for( int index = 0; index < m_vtUI.size(); ++index )
// 		{
// 			for( int n=(int)m_vtUI[index].size()-1; n>=0; n-- )
// 			{
// 				assert( m_vtUI[index][n]->m_pUI->GetControlID()[0] != 0 );
// 				RECT rcControl;
// 				rcControl.left = 400;
// 				rcControl.right = 800;
// 				rcControl.top = n*20;
// 				rcControl.bottom = rcControl.top+20;
// 				if( m_vtUI[index][n]->m_pUI->IsVisable() )
// 				{
// 					//FontSystem::DrawTextRGB( &rcControl, m_vtUI[n].m_pUI->GetControlID(), col, 0, DT_RIGHT );
// 					FontSystem::DrawTextRGB( m_vtUI[index][n]->m_pUI->GetControlID(), &rcControl, DT_RIGHT, col);
// 				}
// 				else
// 				{
// 					//FontSystem::DrawTextRGB( &rcControl, m_vtUI[n].m_pUI->GetControlID(), RGB(255,255,255),
// 					//						0, DT_RIGHT );
// 					FontSystem::DrawTextRGB( m_vtUI[index][n]->m_pUI->GetControlID(), &rcControl, DT_RIGHT,
// 											RGB(255,255,255) );
// 				}
// 			}
// 			rc.top+=20;
// 			rc.bottom+=20;
// 			sprintf( szDebug, "X:%d  Y:%d", m_ptMoust.x, m_ptMoust.y );
// 			//FontSystem::DrawTextRGB( &rc, szDebug, col );
// 			FontSystem::DrawTextRGB( szDebug, &rc, 0, col );
// 
// 			rc.top+=20;
// 			rc.bottom+=20;
// 			int nSize = 0;
// 			for ( UINT n=0; n<theControlPictureManager.GetPicCount(); n++ )
// 			{
// 				ControlPictureManager::S_Pic *pPic = theControlPictureManager.GetPic(n);
// 				nSize += pPic->m_Pic.m_nWidth*pPic->m_Pic.m_nHeight*4;
// 			}
// 			sprintf( szDebug, "界面使用贴图数:%d   总共大小:%d(KB)", theControlPictureManager.GetPicCount(), nSize/1000 );
// 			//FontSystem::DrawTextRGB( &rc, szDebug, col );
// 			FontSystem::DrawTextRGB( szDebug, &rc, 0, col );
// 			for ( UINT n=0; n<theControlPictureManager.GetPicCount(); n++ )
// 			{
// 				rc.top+=20;
// 				rc.bottom+=20;
// 				ControlPictureManager::S_Pic *pPic = theControlPictureManager.GetPic(n);
// 				sprintf( szDebug, "    贴图名:%s(%dx%d)", pPic->m_strName.c_str(),
// 						pPic->m_Pic.m_nWidth, pPic->m_Pic.m_nHeight  );
// 				//FontSystem::DrawTextRGB( &rc, szDebug, col );
// 				FontSystem::DrawTextRGB( szDebug, &rc, 0, col );
// 			}
// 		}
// 	}
// #endif
	unguard;
}

/*
 *	UI消息入口.
 *	被UI处理返回[true]否则返回[flase]
 */
bool UiManager::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	MeScopeProfileUiManagerFun
	guardfunc;
#ifdef _DEBUG
	g_debug_dwHRUIMsgProcUseTime = HQ_TimeGetTime();
#endif
	UiManager::S_UI *pUI = NULL;

	bool bUse = false;

	if( m_vtUI.size() < 1 )
		return false;

	WCHAR wUnicode[2] = {0};
	if ( msg == WM_CHAR )
	{
		// 由于程序是非Unicode的,而UI需要Unicode,所以要进行转换
		//static bool bWaitHalfByte = false;
		//if ( ((lParam>>16)&0xFF) )
		//{
		//	wUnicode = wParam;
		//	bWaitHalfByte = false;
		//}
		//else
		//{
		//	static CHAR szByte[3];
		//	if ( bWaitHalfByte )
		//	{
		//		szByte[1] = (BYTE)wParam;
		//		szByte[2] = 0;
		//		MultiByteToWideChar( CP_ACP, 0, szByte, -1, &wUnicode, 1 );
		//		bWaitHalfByte = false;
		//	}
		//	else
		//	{
		//		szByte[0] = (BYTE)wParam;
		//		bWaitHalfByte = true;
		//	}
		//}
		static bool bWaitHalfByte = false;
		static CHAR szByte[3];
		if ( bWaitHalfByte == false )
		{
			szByte[0] = (BYTE)wParam;
			szByte[1] = 0;
			int ret = MultiByteToWideChar( CP_ACP, 0, szByte, -1, wUnicode, 2 );
			//if( ret != 2 )
			//{
			//	wUnicode[0] = 0;
			//	bWaitHalfByte = true;
			//}
			if (szByte[0]<0 || szByte[0]>127)
			{
				wUnicode[0] = 0;
				bWaitHalfByte = true;
			}
		}
		else
		{
			szByte[1] = (BYTE)wParam;
			szByte[2] = 0;
			MultiByteToWideChar( CP_ACP, 0, szByte, -1, wUnicode, 2 );
			bWaitHalfByte = false;
		}
	}
	if (msg == WM_LBUTTONUP && m_bJumpNextLButtonUp)
	{
		m_bJumpNextLButtonUp = false;
		return false;
	}

	if (WM_MOUSEMOVE == msg)
	{
		m_bIsMouseInUI = false;
	}
	for( int index = m_vtUI.size()-1; index >= UI_Render_LayerFirst; --index )
	{
		if ( m_vtUI[index].size() > 0 )
		{
			switch( msg )
			{
			case WM_MOUSEMOVE:
				{
					if( index == m_vtUI.size()-1 )
					{
						theIconInfoMouseTip.Clear();
					}

					m_ptMoust.x = GET_X_LPARAM(lParam);
					m_ptMoust.y = GET_Y_LPARAM(lParam);
					if ( theIconDragManager.OnMouseMove( (UINT)wParam,
														m_ptMoust.x,
														m_ptMoust.y ) == true )
					{
						bUse = true;
					}
					pUI = m_vtUI[index][0];
					if ( pUI->m_pUI->IsVisable() )
					{
						if ( pUI->m_pUI->OnMouseMove( (UINT)wParam,
							m_ptMoust.x, m_ptMoust.y ) == true )
						{
							bUse = true;
						}
						if( pUI->m_pUI->PtInObject(m_ptMoust.x,m_ptMoust.y,false) ||
							pUI->m_pUI->IsLButtonDrag() )
						{
							//if ( pUI->m_pUI->OnMouseMove( (UINT)wParam,
							//	m_ptMoust.x, m_ptMoust.y ) == true )
							//{
							//	bUse = true;
							//}

						}
						else 
						{
							if( pUI->m_pUI->OnMouseLeave() == true )
							{
								//bUse = true;
								//break;
							}
						}
					}

					if ( bUse == false &&
						pUI->m_pUI->GetArrayMode() != ArrayMode_Top && pUI->m_pUI->GetArrayMode() != ArrayMode_SingleModal)
					{
						for( UINT n=1; n<m_vtUI[index].size(); n++ )
						{
							pUI = m_vtUI[index][n];
							if ( pUI->m_pUI->IsVisable() )
							{
								//if ( pUI->m_pUI->PtInObject(m_ptMoust.x,m_ptMoust.y) )
								//{
								if( pUI->m_pUI->OnMouseMove( (UINT)wParam,
									m_ptMoust.x, m_ptMoust.y ) == true )
								{
									bUse = true;
									break;
								}
								else 
								{
									if( pUI->m_pUI->OnMouseLeave() == true )
									{
										//bUse = true;
										//break;
									}
								}
							}
						}
					}

					if ( m_bDragFrame )
					{
						Cover();
					}

					if ( HasModalWindow(index) == true )
					{
						bUse = true;
					}

					//
					for( UINT n=0; n<m_vtUI[index].size(); n++ )
					{
						if ( m_vtUI[index][n]->m_pUI->IsVisable() &&
							m_vtUI[index][n]->m_pUI->IsMsgHoldup() &&
							m_vtUI[index][n]->m_pUI->IsMouseInUI(m_ptMoust.x,m_ptMoust.y) )
						{
							m_bIsMouseInUI = true;
							break;
						}
					}

					//关联WINDOWS消息，mouseleave
					{
						TRACKMOUSEEVENT tme;
						tme.cbSize = sizeof(tme);
						tme.dwFlags = TME_LEAVE;
						tme.hwndTrack = g_hWnd;
						_TrackMouseEvent(&tme);
					}
				}
				break;
			case WM_MOUSEWHEEL:
				{
					if ( m_vtUI[index][0]->m_pUI->IsVisable() )
					{
						if ( m_vtUI[index][0]->m_pUI->OnMouseWheel( (int)wParam>0,
															m_ptMoust.x ,
															m_ptMoust.y ) == true )
						{
							bUse = true;
						}
					}	
					if ( HasModalWindow(index) == true )
					{
						bUse = true;
					}
				}
				break;
			case WM_LBUTTONDOWN:
				{
					if(m_vtUI[index][0]->m_pUI->GetArrayMode() != ArrayMode_Top && m_vtUI[index][0]->m_pUI->GetArrayMode() != ArrayMode_SingleModal )
					{
						m_bDragFrame = false;
						UpdataFrame( GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) );
					}
					if( m_vtUI[index].size() > 0 ) 
					{
                        // 鼠标输入的UI响应不再只判断最上层       modified by zhuomeng.hu		[3/9/2011]
                        for( int i = 0; i < m_vtUI[index].size(); ++i )
                        {
                            if ( m_vtUI[index][i]->m_pUI->IsVisable() )
                            {
                                bUse = m_vtUI[index][i]->m_pUI->OnLButtonDown( ( UINT )wParam, GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );
                                if( bUse )
                                {
                                    break;
                                }
                            }
                        }

						if( theIconDragManager.OnLButtonDown( (UINT)wParam,
							GET_X_LPARAM(lParam),
							GET_Y_LPARAM(lParam) ) == true )
						{
							bUse = true;
						}
						if ( HasModalWindow(index) == true )
						{
							bUse = true;
						}
						if ( bUse == true )
						{
							Compositor();
						}							
					}
				}
				break;
			case WM_RBUTTONDOWN:
				{
					if(m_vtUI[index][0]->m_pUI->GetArrayMode() != ArrayMode_Top && m_vtUI[index][0]->m_pUI->GetArrayMode() != ArrayMode_SingleModal)
					{
						UpdataFrame( GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) );
						bUse = theIconDragManager.OnRButtonDown( (UINT)wParam,
																GET_X_LPARAM(lParam),
																GET_Y_LPARAM(lParam) );
					}

                    // 鼠标输入的UI响应不再只判断最上层       modified by zhuomeng.hu		[3/9/2011]
                    for( int i = 0; i < m_vtUI[index].size(); ++i )
                    {
                        if ( m_vtUI[index][i]->m_pUI->IsVisable() )
                        {
						    bUse = m_vtUI[index][i]->m_pUI->OnRButtonDown( ( UINT )wParam, GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );
						    if( bUse )
                            {
                                break;
                            }
						}
					}

					if ( HasModalWindow(index) == true )
					{
						bUse = true;
					}

				}
				break;
			case WM_MOUSELEAVE:
			case WM_LBUTTONUP:
				{
                    if(m_vtUI[index][0]->m_pUI->GetArrayMode() != ArrayMode_Top && m_vtUI[index][0]->m_pUI->GetArrayMode() != ArrayMode_SingleModal)
                    {
                        m_bDragFrame = false;
						UpdataFrame( GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) );
                    }
                    if( m_vtUI[index].size() > 0 ) 
                    {
                        // 鼠标输入的UI响应不再只判断最上层       modified by zhuomeng.hu		[3/9/2011]
                        for( int i = 0; i < m_vtUI[index].size(); ++i )
                        {
                            if ( m_vtUI[index][i]->m_pUI->IsVisable() )
                            {
                                bUse = m_vtUI[index][i]->m_pUI->OnLButtonUp( ( UINT )wParam, GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );
                                if( bUse )
                                {
                                    break;
                                }
                            }
                        }

                        if ( HasModalWindow(index) )
                        {
                            bUse = true;
                        }
						else
						{
							if ( theIconDragManager.OnLButtonUp( (UINT)wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), bUse, index ) == true )
							{
								bUse = true;
							}
						}

                        if ( bUse == true )
                        {
                            Compositor();
                        }							
					}				
				}
				break;
			case WM_RBUTTONUP:
                {
					if (m_pRButtonUpFun)
					{
						bUse = m_pRButtonUpFun(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
						if (bUse)
						{
							bUse = false;
							break;
						}
					}
					theMouseManager.ForceSetCursor();
                    if(m_vtUI[index][0]->m_pUI->GetArrayMode() != ArrayMode_Top && m_vtUI[index][0]->m_pUI->GetArrayMode() != ArrayMode_SingleModal)
                    {
                        m_bDragFrame = false;
                        UpdataFrame( GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) );
                    }
                    
                    // 鼠标输入的UI响应不再只判断最上层       modified by zhuomeng.hu		[3/9/2011]
                    for( int i = 0; i < m_vtUI[index].size(); ++i )
                    {
                        if ( m_vtUI[index][i]->m_pUI->IsVisable() )
                        {
                            bUse = m_vtUI[index][i]->m_pUI->OnRButtonUp( ( UINT )wParam, GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );
                            if( bUse )
                            {
                                break;
                            }
                        }
                    }

                    if( theIconDragManager.OnRButtonUp( ( UINT )wParam, GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) ) == true )
                    {
                        bUse = true;
                    }
                    if ( HasModalWindow(index) == true )
                    {
                        bUse = true;
                    }
                    if ( bUse == true )
                    {
                        Compositor();
                    }
				}
				break;
			case WM_LBUTTONDBLCLK:
				{
 					if (m_vtUI[index][0]->m_pUI->GetArrayMode() != ArrayMode_Top && m_vtUI[index][0]->m_pUI->GetArrayMode() != ArrayMode_SingleModal)
					{
						UpdataFrame( GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) );
					}
					theIconDragManager.OnLButtonDBClick( (UINT)wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) );

                    // 鼠标输入的UI响应不再只判断最上层       modified by zhuomeng.hu		[3/9/2011]
                    for( int i = 0; i < m_vtUI[index].size(); ++i )
                    {
                        if ( m_vtUI[index][i]->m_pUI->IsVisable() )
                        {
                            bUse = m_vtUI[index][i]->m_pUI->OnLButtonDBClick( ( UINT )wParam, GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );
                            if( bUse )
                            {
                                break;
                            }
                        }
                    }

					if ( HasModalWindow(index) == true )
					{
						bUse = true;
					}
				}
				break;
			case WM_RBUTTONDBLCLK:
				{
					if(m_vtUI[index][0]->m_pUI->GetArrayMode() != ArrayMode_Top && m_vtUI[index][0]->m_pUI->GetArrayMode() != ArrayMode_SingleModal)
					{
						UpdataFrame( GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) );
					}
					theIconDragManager.OnRButtonDBClick( (UINT)wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) );

                    // 鼠标输入的UI响应不再只判断最上层       modified by zhuomeng.hu		[3/9/2011]
                    for( int i = 0; i < m_vtUI[index].size(); ++i )
                    {
                        if ( m_vtUI[index][i]->m_pUI->IsVisable() )
                        {
                            bUse = m_vtUI[index][i]->m_pUI->OnRButtonDBClick( ( UINT )wParam, GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );
                            if( bUse )
                            {
                                break;
                            }
                        }
                    }

					if ( HasModalWindow(index) == true )
					{
						bUse = true;
					}

				}
				break;
			case WM_KEYDOWN:
                {
                    bool isModal = HasModalWindow(index);
					if ( m_vtUI[index][0]->m_pUI->IsVisable() )
					{
						if ( m_vtUI[index][0]->m_pUI->OnKeyDown( (UINT)wParam ) == true )
						{
							bUse = true;
						}
					}
					if ( isModal && bUse )
					{
						return true;
					}
				}
				break;
			case WM_KEYUP:
                {
                    bool isModal = HasModalWindow(index);
					if ( m_vtUI[index][0]->m_pUI->IsVisable() )
					{
						if( m_vtUI[index][0]->m_pUI->OnKeyUp( (UINT)wParam ) == true )
						{
							bUse = true;
						}
					}
					if ( isModal && bUse )
					{
						return true;
					}
					
					Compositor();
				}
				break;
			case WM_CHAR:
				{
					if ( wUnicode[0] )
					{
						if ( m_vtUI[index][0]->m_pUI->IsVisable() )
						{
							if( m_vtUI[index][0]->m_pUI->OnChar( wUnicode[0] ) == true )
							{
								bUse = true;
							}
						}
					}

					if ( HasModalWindow(index) == true )
					{
						return true;
					}
				}
				break;
			}

			if( bUse )
			{
				break;
			}
		}
	}

	//bUse = false;
	bool bMsgProcUsed = false;

	//由于分层了 所以先处理完所有层次的ui的windows消息 然后再处理ui逻辑消息
	for( int index = m_vtUI.size()-1; index >= UI_Render_LayerFirst; --index )
	{
		for ( UINT n=0; n<m_vtUI[index].size(); n++ )
		{
			if ( !m_vtUI[index][n]->m_pUI )
				continue;  
			if ( m_vtUI[index][n]->m_pUI->MsgProc( msg, wParam, lParam, bUse ) == true )
			{
				bMsgProcUsed = true;
				break;
			}
			if ( (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP) &&
				m_vtUI[index][n]->m_pUI->IsVisable() &&
				m_vtUI[index][n]->m_pUI->IsMsgHoldup() &&
				m_vtUI[index][n]->m_pUI->PtInObject(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam),true) )
			{
				bMsgProcUsed = true;
				break;
			}
		}

		if( bMsgProcUsed )
		{
			break;
		}
	}

#ifdef _DEBUG
		g_debug_dwHRUIMsgProcUseTime = HQ_TimeGetTime() - g_debug_dwHRUIMsgProcUseTime;
#endif

	return bUse || bMsgProcUsed;

	unguard;
}

ControlObject* UiManager::ToTop( IN const ControlObject* pObject, ControlObject* pObjectPos, int toIndex )
{
	MeScopeProfileUiManagerFun
	assert( pObject );

	if (theUiManager.GetFocus() && theUiManager.GetFocus()->GetControlType() == Type_Edit &&
		theUiManager.GetFocus()->GetFather() != pObject)
		return NULL;

	ControlObject *pLastObject = NULL;

	int nPos = 0;

	bool bUse = false;

	for( int index = 0; index < m_vtUI.size(); ++index )
	{
		if( pObjectPos != NULL )
		{
			for ( UINT n=0; n<m_vtUI[index].size(); n++ )
			{
				if( m_vtUI[index][n]->m_pUI == pObjectPos )
				{
					nPos = n;
					break;
				}
			}
		}
		for ( UINT n=1; n<m_vtUI[index].size(); n++ )
		{
			if ( m_vtUI[index][n]->m_pUI == pObject )
			{
				if( pObjectPos == NULL )
				{
					pLastObject = m_vtUI[index][toIndex]->m_pUI;
					S_UI* stUI = m_vtUI[index][n];
					for (int i = n; i > toIndex; --i)
					{
						m_vtUI[index][i] = m_vtUI[index][i - 1] ;
					}
					m_vtUI[index][toIndex] = stUI;
// 					S_UI* stUI = m_vtUI[index][toIndex];
// 					m_vtUI[index][toIndex] = m_vtUI[index][n];
// 					m_vtUI[index][n] = stUI;
					bUse = true;

					break;
				}
				else if( nPos < n)
				{
					//pLastObject = m_vtUI[index][nPos].m_pUI;
					S_UI* stUI = m_vtUI[index][n];
					for (int i = n; i > nPos; --i)
					{
						m_vtUI[index][i] = m_vtUI[index][i - 1] ;
					}
					m_vtUI[index][nPos] = stUI;
// 					S_UI* stUI = m_vtUI[index][nPos];
// 					m_vtUI[index][nPos] = m_vtUI[index][n];
// 					m_vtUI[index][n] = stUI;
					bUse = true;

					break;
				}
			}
		}

		if( bUse )
		{
			return pLastObject;
		}
	}

	return pLastObject;
}

ControlObject* UiManager::ToBottom( IN const ControlObject* pObject )
{
	MeScopeProfileUiManagerFun
	assert( pObject );
	ControlFrame *pLastObject = NULL;
	bool bUse = false;

	for( int index = 0; index < m_vtUI.size(); ++index )
	{
		int nLastIndex = m_vtUI[index].size()-1;
		for ( int n=0; n<nLastIndex; n++ )
		{
			if ( m_vtUI[index][n]->m_pUI == pObject )
			{
				pLastObject = m_vtUI[index][nLastIndex]->m_pUI;
				S_UI* stUI = m_vtUI[index][n];
				for (int i = n; i < nLastIndex; ++i)
				{
					m_vtUI[index][i] = m_vtUI[index][i + 1] ;
				}
				m_vtUI[index][nLastIndex] = stUI;
// 				S_UI* stUI = m_vtUI[index][nLastIndex];
// 				m_vtUI[index][nLastIndex] = m_vtUI[index][n];
// 				m_vtUI[index][n] = stUI;
				bUse = true;

				break;
			}
		}

		if( bUse )
		{
			return pLastObject;
		}
	}
	return pLastObject;
}

bool UiManager::AddFrame( IN ControlFrame* pObject, bool bAllVisable, UI_Render_Layer layer)
{
	MeScopeProfileUiManagerFun
	guard(UiManager::AddFrame);

	S_UI* stUI = MeNew S_UI;
	stUI->m_pUI = pObject;
	stUI->m_bNeedRelease = false;
	
	if( layer >= UI_Render_LayerMax )
		return false;

	InsertNewFrame(layer, stUI);

	unguard;
	return true;
}

//DWORD UiManager::ReAddTopFrame()
//{
//	if( m_vtUI.size() <= 0 )
//		return 0;
//	std::string strFileName = m_vtUI[0].m_strFileName;
//	RemoveFrame( strFileName.c_str() );
//	return AddFrame( strFileName.c_str() );
//}
//void UiManager::AddFrame_XML( const char* fileName, bool bAllVisable, UI_Render_Layer layer )
//{
//	guardfunc;
//	RemoveFrame( fileName );
//
//	MeXmlDocument	doc;
//	if( !doc.LoadFile(fileName) )
//	{
//		assert(false && "Login.cpp::LoadConfigXml 读取文件不错");
//		return;
//	}
//	MeXmlElement* lpRootUI = m_MeXmlDoc.FirstChildElement("UI");
//	if(lpRootUI )
//	{
//		MeXmlElement* lpFrame = lpRootUI->FirstChildElement("Frame");
//		if( lpFrame )
//		{
//			
//		}
//	}
//	unguard;
//}

DWORD UiManager::AddFrame( IN const char* szFileName, bool bAllVisable, UI_Render_Layer layer )
{
    guard(UiManager::AddFrame);
	if( !szFileName )
		return 0;

	char fullname[MAX_PATH];
	if( szFileName[1] == ':' )
	{
		strcpy( fullname, szFileName  );
	}
	else
		sprintf( fullname, "%s\\%s", GetRootPath(), szFileName );

	RemoveFrame( fullname );
	S_UI* stUI = MeNew S_UI;
	stUI->m_strFileName = fullname;
	stUI->m_pUI = MeNew ControlFrame;
	DWORD dwCreatedDate = 0;


	ControlFrame *pFrame = (ControlFrame*)stUI->m_pUI;

	dwCreatedDate = pFrame->LoadUIFormFile(fullname);

	pFrame->SetVisable(true);

	if(bAllVisable)//为真 说明是 小地图 Main 角色信息 这样的dlg 进来了
		stUI->m_pUI->SetAllVisableDlg();

	if( dwCreatedDate == 0 )
	{
		delete stUI;
		return 0;
	}

	if( layer >= UI_Render_LayerMax )
		return 0;

	InsertNewFrame(layer, stUI);
	return dwCreatedDate;

	unguard;
}

DWORD UiManager::AddFrame(IN const char* szZipFileName,IN const char* szFileName, bool bAllVisable, UI_Render_Layer layer)
{
	guard(UiManager::AddFrame);
	if( !szFileName || !szZipFileName )
		return 0;

	char fullname[MAX_PATH];
	if( szFileName[1] == ':' )
	{
		strcpy( fullname, szFileName  );
	}
	else
		sprintf( fullname, "%s\\%s", GetRootPath(), szFileName );

	char zipfullname[MAX_PATH];
	if( szZipFileName[1] == ':' )
	{
		strcpy( zipfullname, szZipFileName  );
	}
	else
		sprintf( zipfullname, "%s\\%s", GetRootPath(), szZipFileName );

	RemoveFrame( fullname );
	S_UI* stUI = MeNew S_UI;
	stUI->m_strFileName = fullname;
	stUI->m_pUI = MeNew ControlFrame;
	DWORD dwCreatedDate = 0;

	ControlFrame *pFrame = (ControlFrame*)stUI->m_pUI;

	dwCreatedDate = pFrame->LoadUIFormUnit(zipfullname,fullname );

	pFrame->SetVisable(true);

	if(bAllVisable)//为真 说明是 小地图 Main 角色信息 这样的dlg 进来了
		stUI->m_pUI->SetAllVisableDlg();

	if( dwCreatedDate == 0 )
	{
		delete stUI;
		return 0;
	}

	if( layer >= UI_Render_LayerMax )
		return 0;

	InsertNewFrame(layer, stUI);
	return dwCreatedDate;

	unguard;
}

bool UiManager::ReSetWindowPosNoAllVisable() //lyh++
{

	for( int index = m_vtUI.size() - 1; index >= 0; --index )
	{
		for( int n=0; n<m_vtUI[index].size(); ++n)
		{
			if(m_vtUI[index][n]->m_pUI->GetAllVisableDlg())
				continue;


			//if(m_vtUI[index][n]->m_pUI->IsVisable()) //不管可不可见全部重新设置一遍
			{		
				RECT _Pos;
				if (m_vtUI[index][n]->m_pUI->GetFather())
				{	
					m_vtUI[index][n]->m_pUI->GetFather()->GetRealRect(&_Pos);
				}else
				{
					m_vtUI[index][n]->m_pUI->GetRealRect(&_Pos);
				}
					
				    if (_Pos.left < 0)
					{
                        _Pos.left = 0;
					}

					if (_Pos.left > SCREEN_WIDTH - (_Pos.right - _Pos.left))
					{
						_Pos.left = SCREEN_WIDTH - (_Pos.right - _Pos.left);
					}

					if (_Pos.top < 0)
					{
						_Pos.top= 0;
					}

					if (_Pos.top > SCREEN_HEIGHT -(_Pos.bottom - _Pos.top) )
					{
						_Pos.top = SCREEN_HEIGHT -(_Pos.bottom - _Pos.top);
					}

					if (m_vtUI[index][n]->m_pUI->GetFather())
					{	
						m_vtUI[index][n]->m_pUI->GetFather()->SetPos(_Pos.left,_Pos.top);
					}else
					{
						m_vtUI[index][n]->m_pUI->SetPos(_Pos.left,_Pos.top);
					}

					

				
				
			}

		}


	}



	//if( x < 0 )
	//{
	//	x = 0;
	//}
	//if( x > SCREEN_WIDTH-m_nWidth )
	//{
	//	x = SCREEN_WIDTH-m_nWidth;
	//}
	//if( y < 0 )
	//{
	//	y = 0;
	//}
	//if( y > SCREEN_HEIGHT-m_nHeight )
	//{
	//	y = SCREEN_HEIGHT-m_nHeight;
	//}
	////SetPos( x, y );
	//if (m_pFather)
	//	m_pFather->SetPos( x, y );
	//else
	//	SetPos(x, y);


	return true;
}

bool UiManager::HideAllDlgNoAllVisable()
{
	
	for( int index = m_vtUI.size() - 1; index >= 0; --index )
	{
		for( int n=0; n<m_vtUI[index].size(); ++n)
		{
			if(m_vtUI[index][n]->m_pUI->GetAllVisableDlg())
				continue;
			if(m_vtUI[index][n]->m_pUI->IsVisable())
			{	

				if (m_vtUI[index][n]->m_pUI->GetOnEscResponseType() == ControlFrame::EscResponse_SkipMe)
				{
					continue;
				}
				
						if (m_vtUI[index][n]->m_pUI->GetFather())
							m_vtUI[index][n]->m_pUI->GetFather()->SetVisable(false);
						else
				       m_vtUI[index][n]->m_pUI->SetVisable(false);			
			}
			
		}

		
	}
	//ImmAssociateContext( g_hWnd, NULL );
	return true;

}
bool UiManager::HideDlg()
{
	bool bUse = false;
	for( int index = m_vtUI.size() - 1; index >= 0; --index )
	{
		for( int n=0; n<m_vtUI[index].size(); ++n)
		{
			if(m_vtUI[index][n]->m_pUI->GetAllVisableDlg())
				continue;
			if(m_vtUI[index][n]->m_pUI->IsVisable())
			{
				//bUse = true;
				switch (m_vtUI[index][n]->m_pUI->GetOnEscResponseType())
				{
				case ControlFrame::EscResponse_SkipMe:
					{
						break;
					}
				case ControlFrame::EscResponse_SkipAll:
					{
						return false;
					}
				default:
					{
						if (m_vtUI[index][n]->m_pUI->GetFather())
							m_vtUI[index][n]->m_pUI->GetFather()->SetVisable(false);
						else
							m_vtUI[index][n]->m_pUI->SetVisable(false);
						ImmAssociateContext( g_hWnd, NULL );
						return true;
					}
					break;
				}
			}
		}

// 		if( bUse )
// 		{
// 			return true;
// 		}
	}
	return false;
}

bool UiManager::RemoveFrame( IN const char* szFileName )
{
	MeScopeProfileUiManagerFun
	guard(__FUNCDNAME__);

	if( !szFileName )
		return false;

	char fullname[MAX_PATH];
	if( szFileName[1] == ':' )
	{
		strcpy( fullname, szFileName  );
	}
	else
		sprintf( fullname, "%s\\%s", GetRootPath(), szFileName );

	bool bDel = false;
	for( int index = 0; index < m_vtUI.size(); ++index )
	{
		std::vector<S_UI*>::iterator iter = m_vtUI[index].begin();
		for( ; iter != m_vtUI[index].end(); ++iter )
		{
			if( (*iter)->m_strFileName == fullname )
			{
				if(m_pFocus &&  (m_pFocus->GetFrameFather() == (*iter)->m_pUI ))
					SetFocus(NULL);

				RemoveFrameLayout(dynamic_cast<ControlFrame*>((*iter)->m_pUI));

				delete (*iter);
				m_vtUI[index].erase( iter );
				bDel = true;
				break;
// 				m_vtNeedRelease.push_back((*iter));
			}
		}
		if (bDel)
		{
			break;
		}
	}

	if (bDel)
	{
		Compositor();
		return true;
	}
	return false;
	unguard;
}

bool UiManager::RemoveFrame( IN const ControlFrame* pObject )
{
	guard(__FUNCDNAME__);

	bool bDel = false;
	assert( pObject );
	for( int index = 0; index < m_vtUI.size(); ++index )
	{
		std::vector<S_UI*>::iterator iter = m_vtUI[index].begin();
		for( ; iter != m_vtUI[index].end(); ++iter )
		{
			if( (*iter)->m_pUI == pObject )
			{
				if(m_pFocus &&  (m_pFocus->GetFrameFather() == (*iter)->m_pUI ))
					SetFocus(NULL);

				RemoveFrameLayout(dynamic_cast<ControlFrame*>((*iter)->m_pUI));

				delete (*iter);
				m_vtUI[index].erase( iter );
// 				m_vtNeedRelease.push_back(*iter);
				break;
			}
		}
		if (bDel)
		{
			break;
		}
	}

	if (bDel)
	{
		Compositor();
		return true;
	}

	return false;
	unguard;
}

bool UiManager::OnFrameRun( IN const char *szFrameID, IN ControlFrame::funRun pFun )
{
	assert( szFrameID );
	assert( pFun );

	ControlObject *pUI = FindFrame( szFrameID );
	if ( pUI && pUI->GetControlType() == Type_Frame )
	{
		ControlFrame* pFrame = (ControlFrame*)pUI;
		pFrame->SetRunFun( pFun );
		return true;
	}
#ifdef _DEBUG
	char szError[128];
	sprintf( szError, "找不到指定框架:%s", szFrameID );
	MESSAGE_BOX( szError )
#endif
	return false;
}

bool UiManager::OnFrameRender( IN const char *szFrameID,
								IN ControlFrame::funRender pFun,
							   const bool bBeforeRender )
{
	assert( szFrameID );
	assert( pFun );

	ControlObject *pUI = FindFrame( szFrameID );
	if ( pUI && pUI->GetControlType() == Type_Frame )
	{
		ControlFrame* pFrame = (ControlFrame*)pUI;
		pFrame->SetRenderFun( pFun, bBeforeRender );
		return true;
	}
#ifdef _DEBUG
	char szError[128];
	sprintf( szError, "找不到指定框架:%s", szFrameID );
	MESSAGE_BOX( szError )
#endif
		return false;
}

bool UiManager::OnButtonClick( IN const char *szFrameID, IN const char *szControlID,
								IN ControlButton::funOnButtonClick pFun )
{
	assert( szFrameID );
	assert( szControlID );
	assert( pFun );

	ControlObject *pUI = FindControl( szFrameID, szControlID );
	if ( pUI != NULL )
	{
		if ( pUI->GetControlType() == Type_Button )
		{
			ControlButton *pButton = (ControlButton *) pUI;
			pButton->SetButtonClickFun( pFun );
			return true;
		}
		else if ( pUI->GetControlType() == Type_Picture )
		{
			ControlPicture *pPic = (ControlPicture *) pUI;
			pPic->SetButtonClickFun( pFun );
			return true;
		}
		else if ( pUI->GetControlType() == Type_Text )
		{
			ControlText *pText = (ControlText *) pUI;
			pText->SetButtonClickFun( pFun );
			return true;
		}
	}
#ifdef _DEBUG
	char szError[128];
	sprintf( szError, "找不到指定控件:%s->%s", szFrameID, szControlID );
	MESSAGE_BOX( szError )
#endif
	return false;
}

bool UiManager::OnButtonMouseMove( IN const char *szFrameID, IN const char *szControlID,
								  IN ControlButton::funOnMouseOn pFun )
{
	assert( szFrameID );
	assert( szControlID );
	assert( pFun );

	ControlObject *pUI = FindControl( szFrameID, szControlID );
	if ( pUI && pUI->GetControlType() == Type_Button )
	{
		ControlButton* pButton = (ControlButton*)pUI;
		pButton->SetButtonMouseOnFun( pFun );
		return true;
	}
#ifdef _DEBUG
	char szError[128];
	sprintf( szError, "找不到指定控件:%s->%s", szFrameID, szControlID );
	MESSAGE_BOX( szError )
#endif
	return false;
}

bool UiManager::OnCheckBoxCheck( IN const char *szFrameID, IN const char *szControlID,
									IN ControlCheckBox::funOnCheck pFun )
{
	assert( szFrameID );
	assert( szControlID );
	assert( pFun );

	ControlObject *pUI = FindControl( szFrameID, szControlID );
	if ( pUI && pUI->GetControlType() == Type_CheckBox )
	{
		ControlCheckBox* pCheckBox = (ControlCheckBox*)pUI;
		pCheckBox->SetCheckFun( pFun );
		return true;
	}
#ifdef _DEBUG
	char szError[128];
	sprintf( szError, "找不到指定控件:%s->%s", szFrameID, szControlID );
	MESSAGE_BOX( szError )
#endif
	return false;
}

bool UiManager::OnListSelectChange( IN const char *szFrameID, IN const char *szControlID,
										IN ControlList::funSelectChange pFun )
{
	assert( szFrameID );
	assert( szControlID );
	assert( pFun );

	ControlObject *pUI = FindControl( szFrameID, szControlID );
	if ( pUI && pUI->GetControlType() == Type_List )
	{
		ControlList* pList = (ControlList*)pUI;
		pList->SetSelectChangeFun( pFun );
		return true;
	}
#ifdef _DEBUG
	char szError[128];
	sprintf( szError, "找不到指定控件:%s->%s", szFrameID, szControlID );
	MESSAGE_BOX( szError )
#endif
	return false;
}

bool UiManager::OnListLDBClick( IN const char *szFrameID, IN const char *szControlID,
								IN ControlList::funMouseClick pFun )
{
	assert( szFrameID );
	assert( szControlID );
	assert( pFun );

	ControlObject *pUI = FindControl( szFrameID, szControlID );
	if ( pUI && pUI->GetControlType() == Type_List )
	{
		ControlList* pList = (ControlList*)pUI;
		pList->SetLDBClickFun( pFun );
		return true;
	}
#ifdef _DEBUG
	char szError[128];
	sprintf( szError, "找不到指定控件:%s->%s", szFrameID, szControlID );
	MESSAGE_BOX( szError )
#endif
		return false;
}

bool UiManager::OnEditEnter( IN const char *szFrameID, IN const char *szControlID,
								IN ControlEdit::funOnEnter pFun )
{
	assert( szFrameID );
	assert( szControlID );
	assert( pFun );

	ControlObject *pUI = FindControl( szFrameID, szControlID );
	if ( pUI && pUI->GetControlType() == Type_Edit )
	{
		ControlEdit* pEdit = (ControlEdit*)pUI;
		pEdit->SetEnterFun( pFun );
		return true;
	}
#ifdef _DEBUG
	char szError[128];
	sprintf( szError, "找不到指定控件:%s->%s", szFrameID, szControlID );
	MESSAGE_BOX( szError )
#endif
	return false;
}

bool UiManager::OnComboBoxChange( IN const char *szFrameID, IN const char *szControlID,
									IN ControlComboBox::funOnChange pFun )
{
	assert( szFrameID );
	assert( szControlID );
	assert( pFun );

	ControlObject *pUI = FindControl( szFrameID, szControlID );
	if ( pUI && pUI->GetControlType() == Type_ComboBox )
	{
		ControlComboBox* pComboBox = (ControlComboBox*)pUI;
		pComboBox->SetChangeFun( pFun );
		return true;
	}
#ifdef _DEBUG
	char szError[128];
	sprintf( szError, "找不到指定控件:%s->%s", szFrameID, szControlID );
	MESSAGE_BOX( szError )
#endif
		return false;
}

bool UiManager::OnTextHyberClick( IN const char *szFrameID, IN const char *szControlID,
								  IN ControlText::funHyberClick pFun)
{
	assert( szFrameID );
	assert( szControlID );
	assert( pFun );

	ControlObject *pUI = FindControl( szFrameID, szControlID );
	if(pUI && pUI->GetControlType() == Type_Text)
	{
		ControlText* pText = (ControlText*)pUI;
		pText->SetHyberClickFun( pFun );
		return true;
	}
#ifdef _DEBUG
	char szError[128] = {0};
	sprintf( szError, "找不到指定控件:%s->%s", szFrameID, szControlID);
	MESSAGE_BOX( szError);
#endif
	return false;
}
bool UiManager::OnIconDragOn( IN const char *szFrameID, IN const char *szControlID,
								IN ControlIconDrag::funDragOn pFun )
{
	assert( szFrameID );
	assert( szControlID );
	assert( pFun );

	ControlObject *pUI = FindControl( szFrameID, szControlID );
	if ( pUI )
	{
		if ( pUI->GetControlType() == Type_ListImg ||
			pUI->GetControlType() == Type_ListEx )
		{
			ControlIconDrag* pIcon = (ControlIconDrag*)pUI;
			pIcon->SetDragOnFun( pFun );
			return true;
		}
	}
#ifdef _DEBUG
	char szError[128];
	sprintf( szError, "找不到指定控件:%s->%s", szFrameID, szControlID );
	MESSAGE_BOX( szError )
#endif
	return false;
}

bool UiManager::OnIconDisableDragOn( IN const char *szFrameID, IN const char *szControlID,
								IN ControlIconDrag::funDragOn pFun )
{
	assert( szFrameID );
	assert( szControlID );
	assert( pFun );

	ControlObject *pUI = FindControl( szFrameID, szControlID );
	if ( pUI )
	{
		if ( pUI->GetControlType() == Type_ListImg ||
			pUI->GetControlType() == Type_ListEx )
		{
			ControlIconDrag* pIcon = (ControlIconDrag*)pUI;
			pIcon->SetDragDisableOnFun( pFun );
			return true;
		}
	}
#ifdef _DEBUG
	char szError[128];
	sprintf( szError, "找不到指定控件:%s->%s", szFrameID, szControlID );
	MESSAGE_BOX( szError )
#endif
	return false;
}

bool UiManager::OnIconDisableDragOut( IN const char *szFrameID, IN const char *szControlID,
								IN ControlIconDrag::funDragOut pFun )
{
	assert( szFrameID );
	assert( szControlID );
	assert( pFun );

	ControlObject *pUI = FindControl( szFrameID, szControlID );
	if ( pUI )
	{
		if ( pUI->GetControlType() == Type_ListImg ||
			pUI->GetControlType() == Type_ListEx )
		{
			ControlIconDrag* pIcon = (ControlIconDrag*)pUI;
			pIcon->SetDragDisableOutFun( pFun );
			return true;
		}
	}
#ifdef _DEBUG
	char szError[128];
	sprintf( szError, "找不到指定控件:%s->%s", szFrameID, szControlID );
	MESSAGE_BOX( szError )
#endif
	return false;
}
//bool UiManager::OnIconDragOff( IN const char *szFrameID, IN const char *szControlID,
//								IN ControlIconDrag::funDragOff pFun )
//{
//	assert( szFrameID );
//	assert( szControlID );
//	assert( pFun );
//
//	ControlObject *pUI = FindControl( szFrameID, szControlID );
//	if ( pUI )
//	{
//		if ( pUI->GetControlType() == Type_ListImg ||
//			pUI->GetControlType() == Type_ListEx )
//		{
//			ControlIconDrag* pIcon = (ControlIconDrag*)pUI;
//			pIcon->SetDragOffFun( pFun );
//			return true;
//		}
//	}
//#ifdef _DEBUG
//	char szError[128];
//	sprintf( szError, "找不到指定控件:%s->%s", szFrameID, szControlID );
//	MESSAGE_BOX( szError )
//#endif
//		return false;
//}

bool UiManager::OnIconLDBClick( IN const char *szFrameID, IN const char *szControlID,
									IN ControlIconDrag::funLDBClick pFun )
{
	assert( szFrameID );
	assert( szControlID );
	assert( pFun );

	ControlObject *pUI = FindControl( szFrameID, szControlID );
	if ( pUI )
	{
		if ( pUI->GetControlType() == Type_ListImg ||
			pUI->GetControlType() == Type_ListEx )
		{
			ControlIconDrag* pIcon = (ControlIconDrag*)pUI;
			pIcon->SetLDBClickFun( pFun );
			return true;
		}
	}
#ifdef _DEBUG
	char szError[128];
	sprintf( szError, "找不到指定控件:%s->%s", szFrameID, szControlID );
	MESSAGE_BOX( szError )
#endif
		return false;
}

bool UiManager::OnIconButtonClick( IN const char *szFrameID, IN const char *szControlID,
								IN ControlIconDrag::funOnButtonClick pFun )
{
	assert( szFrameID );
	assert( szControlID );
	assert( pFun );

	ControlObject *pUI = FindControl( szFrameID, szControlID );
	if ( pUI )
	{
		if ( pUI->GetControlType() == Type_ListImg ||
			pUI->GetControlType() == Type_ListEx )
		{
			ControlIconDrag* pIcon = (ControlIconDrag*)pUI;
			pIcon->SetButtonClickFun( pFun );
			return true;
		}
	}
#ifdef _DEBUG
	char szError[128];
	sprintf( szError, "找不到指定控件:%s->%s", szFrameID, szControlID );
	MESSAGE_BOX( szError )
#endif
	return false;
}

bool UiManager::OnIconRButtonUp( IN const char *szFrameID, IN const char *szControlID,
									IN ControlIconDrag::funRButtonUp pFun )
{
	assert( szFrameID );
	assert( szControlID );
	assert( pFun );

	ControlObject *pUI = FindControl( szFrameID, szControlID );
	if ( pUI )
	{
		if ( pUI->GetControlType() == Type_ListImg ||
			pUI->GetControlType() == Type_ListEx )
		{
			ControlIconDrag* pIcon = (ControlIconDrag*)pUI;
			pIcon->SetRButtonUpFun( pFun );
			return true;
		}
	}
#ifdef _DEBUG
	char szError[128];
	sprintf( szError, "找不到指定控件:%s->%s", szFrameID, szControlID );
	MESSAGE_BOX( szError )
#endif
	return false;
}

bool UiManager::OnScrollBarUpdatePos( IN const char *szFrameID, IN const char *szControlID,
										IN ControlScrollBar::funUpdatePos pFun )
{
	assert( szFrameID );
	assert( szControlID );
	assert( pFun );

	ControlObject *pUI = FindControl( szFrameID, szControlID );
	if ( pUI && pUI->GetControlType() == Type_ScrollBar )
	{
		ControlScrollBar* pScrollBar = (ControlScrollBar*)pUI;
		pScrollBar->SetUpdatePosFun( pFun );
		return true;
	}
#ifdef _DEBUG
	char szError[128];
	sprintf( szError, "找不到指定控件:%s->%s", szFrameID, szControlID );
	MESSAGE_BOX( szError )
#endif
		return false;
}

bool UiManager::OnScrollBarExUpdatePos( IN const char *szFrameID, IN const char *szControlID,
										IN ControlScrollBar::funUpdatePos pFun )
{
	assert( szFrameID );
	assert( szControlID );
	assert( pFun );

	ControlObject *pUI = FindControl( szFrameID, szControlID );
	if ( pUI && pUI->GetControlType() == Type_ScrollBarEx )
	{
		ControlScrollBarEx* pScrollBarEx = (ControlScrollBarEx*)pUI;
		pScrollBarEx->SetUpdatePosFun( pFun );
		return true;
	}
#ifdef _DEBUG
	char szError[128];
	sprintf( szError, "找不到指定控件:%s->%s", szFrameID, szControlID );
	MESSAGE_BOX( szError )
#endif
	return false;
}

ControlObject* UiManager::FindControl( IN const char *szFrameID, IN const char *szControlID )
{
	std::vector< std::vector<S_UI*> >& vtUI = theUiManager.getUIVec();
	for( int index = 0; index < vtUI.size(); ++index )
	{
		for( int n=0; n<vtUI[index].size(); n++ )
		{

			if ( vtUI[index][n] && vtUI[index][n]->m_pUI && strcmp( vtUI[index][n]->m_pUI->GetControlID(), szFrameID ) == 0 )
			{
				return vtUI[index][n]->m_pUI->FindControl( szControlID );
			}
		}
		//for( int n=0; n<vtUI[index].size(); n++ )
		//{
		//	ControlObject* pControl = NULL;
		//	pControl = vtUI[index][n]->m_pUI->FindControl( szControlID, szFrameID );
		//	if ( pControl )
		//	{
		//		return pControl;
		//	}
		//}
	}

	char szError[128];
	sprintf( szError, "找不到指定控件:%s->%s", szFrameID, szControlID );
	MESSAGE_BOX( szError );
	return NULL;
}

ControlObject* UiManager::FindFrame( IN const char *szFrameID )
{
	std::vector< std::vector<S_UI*> >& vtUI = theUiManager.getUIVec();

	for( int index = 0; index < vtUI.size(); ++index )
	{
		for( int n=0; n<vtUI[index].size(); n++ )
		{
			if ( vtUI[index][n]->m_pUI && // added, jiayi, [2010/2/3]
				strcmp( vtUI[index][n]->m_pUI->GetControlID(), szFrameID ) == 0 )
			{
				return vtUI[index][n]->m_pUI;
			}
		}
		//for( int n=0; n<vtUI[index].size(); n++ )
		//{
		//	ControlObject* pFrame = NULL;
		//	pFrame = vtUI[index][n]->m_pUI->FindFrame( szFrameID );
		//	if ( pFrame && pFrame->GetControlType() == Type_Frame )
		//	{
		//		return pFrame;
		//	}
		//}
	}

	//char szError[128];
	//sprintf( szError, "找不到指定MEUI:%s", szFrameID );
	//MESSAGE_BOX( szError );
	return NULL;
}
ControlObject* UiManager::CreateWidget( S_BaseData* sBaseData, ControlObject* pFather)
{
	if(!sBaseData)
		return NULL;
	ControlObject *pUIObject = NULL;
	switch(sBaseData->m_nType)
	{
	case Type_Button:
		pUIObject = MeNew ControlButton;
		break;
	case Type_CheckBox:
		pUIObject = MeNew ControlCheckBox;
		break;
	case Type_Edit:
		pUIObject = MeNew ControlEdit;
		break;
	case Type_Text:
		pUIObject = MeNew ControlText;
		break;
	case Type_List:
		pUIObject = MeNew ControlList;
		break;
	case Type_ListImg:
		pUIObject = MeNew ControlListImage;
		break;
	case Type_ScrollBar:
		pUIObject = MeNew ControlScrollBar;
		break;
	case Type_ScrollBarEx:
		pUIObject = MeNew ControlScrollBarEx;
		break;
	case Type_ComboBox:
		pUIObject = MeNew ControlComboBox;
		break;
	case Type_Picture:
		pUIObject = MeNew ControlPicture;
		break;
	case Type_Progress:
		pUIObject = MeNew ControlProgress;
		break;
	case Type_Tab:
		pUIObject = MeNew ControlTab;
		break;
	case Type_ListEx:
		pUIObject = MeNew ControlListEx;
		break;
	default:
		MESSAGE_BOX("类型超出!")
			break;
	}
	pUIObject->InitUIData(pFather, sBaseData);
	pUIObject->m_bNeedRelease = true;
	if ( theUiManager.m_pFocus == NULL && pUIObject->UseFocus() )
	{
		pUIObject->SetActivate();
	}
	if(pFather)
		dynamic_cast<ControlFrame*>(pFather)->AppendChild(pUIObject);

	return pUIObject;
}
void UiManager::UpdataFrame( const int nX, const int nY )
{
	for( int index = 0; index < m_vtUI.size(); ++index )
	{
		for ( UINT n=0 ;n<m_vtUI[index].size(); n++ )
		{
			if ( m_vtUI[index][n]->m_pUI->IsVisable() &&
				m_vtUI[index][n]->m_pUI->PtInObject(nX,nY,false) )
			{
				if (m_vtUI[index][n]->m_pUI->GetFather())
				{
					for ( UINT y=0 ;y<m_vtUI[index].size(); y++ )
					{
						if ( m_vtUI[index][y]->m_pUI->IsVisable() &&
							m_vtUI[index][y]->m_pUI == m_vtUI[index][n]->m_pUI->GetFather() )
						{
							n = y;
							break;
						}
					}
				}
				if ( n != 0 )
				{
					S_UI* stUI = m_vtUI[index][n];
					for (int i = n; i > 0; --i)
					{
						m_vtUI[index][i] = m_vtUI[index][i - 1] ;
					}
					m_vtUI[index][0] = stUI;
// 					S_UI stUI = m_vtUI[index][0];
// 					m_vtUI[index][0] = m_vtUI[index][n];
// 					m_vtUI[index][n] = stUI;
				}
				Compositor();
				break;
			}
		}
	}
}

void UiManager::ReDrawAllFrame()
{
	for( int index = 0; index < m_vtUI.size(); ++index )
	{
		for( int n=0; n<(int)m_vtUI[index].size(); n++ )
		{
			m_vtUI[index][n]->m_pUI->SetRedraw();
		}
	}
}

void UiManager::SetUIAdjustScale( float fScale )
{
	ControlObject::SetAdjustSCALE(fScale);
	RestoreDeviceObjects();
}

void UiManager::InsertNewFrame( UI_Render_Layer layer, S_UI* stUI )
{
	m_vtUI[layer].push_back(stUI);
	//新加载的ui出现在同层次ui的最上面
	for (int i = m_vtUI[layer].size() - 1; i > 0; --i)
	{
		m_vtUI[layer][i] = m_vtUI[layer][i - 1];
	}
	m_vtUI[layer][0] = ( stUI );

	Compositor();
}
// 排序
void UiManager::Compositor()
{
	guardfunc;

	int cntFirst = 0;
	int cntHasUI = 0;
	for( int index = 0; index < m_vtUI.size(); ++index )
	{
		if ( m_vtUI[index].size() == 0 )
			break;
		for( int n=0; n<(int)m_vtUI[index].size(); n++ )
		{
			if(m_vtUI[index][n]->m_pUI == NULL) 
				continue;
			if ( m_vtUI[index][n]->m_pUI->IsNeedRender() )
			{
				if ( m_vtUI[index][n]->m_pUI->GetArrayMode() == ArrayMode_Top || m_vtUI[index][n]->m_pUI->GetArrayMode() == ArrayMode_SingleModal )
				{
					S_UI* stUI = m_vtUI[index][n];
					for (int m = n; m > 0 ; --m)
					{
						m_vtUI[index][m] = m_vtUI[index][m - 1];
					}
					m_vtUI[index][0] = stUI;

					break;
				}
				else if ( m_vtUI[index][n]->m_pUI->GetArrayMode() == ArrayMode_Bottom )
				{
					S_UI* stUI = m_vtUI[index][n];
					for ( int m= n; m < (int)m_vtUI[index].size() -1; ++m )
					{
							m_vtUI[index][m] = m_vtUI[index][m + 1];
					}
					m_vtUI[index][m_vtUI[index].size() -1] = stUI;
					break;
				}
			}
		}

		if ( m_vtUI[index][0]->m_pUI && m_vtUI[index][0]->m_pUI->GetFather())
		{
			for ( UINT y=0 ;y<m_vtUI[index].size(); y++ )
			{
				if ( m_vtUI[index][y]->m_pUI->IsVisable() &&
					m_vtUI[index][y]->m_pUI == m_vtUI[index][0]->m_pUI->GetFather() )
				{
					S_UI* stUI = m_vtUI[index][0];
					m_vtUI[index][0] = m_vtUI[index][y];
					m_vtUI[index][y] = stUI;
					break;
				}
			}
		}

		if( m_vtUI[index][0]->m_pUI )
		{
			++cntHasUI;

			if ( m_vtUI[index][0]->m_pUI->IsNeedRender() == false )
			{
				for ( UINT n=1; n<m_vtUI[index].size(); n++ )
				{
					if ( m_vtUI[index][n]->m_pUI->IsNeedRender() == true )
					{
						S_UI* stUI = m_vtUI[index][0];
						m_vtUI[index][0] = m_vtUI[index][n];
						m_vtUI[index][n] = stUI;
						break;
					}
				}
			}

			if ( m_pFocus && !m_vtUI[index][0]->m_pUI->IsChild( m_pFocus ) )
			{
				++cntFirst;
			}
		}

	}

	// 是否失去焦点
	if ( cntFirst == cntHasUI )
	{
// 		if(m_pFocus && m_pFocus->CanLostFocusPassive())
		{
			SetFocus(NULL);
		}
	}

	Cover();
	unguard;
}

void UiManager::Cover()
{
	guardfunc;
	for( int index = 0; index < m_vtUI.size(); ++index )
	{
		if ( m_vtUI[index].size() > 0 )
		{
			// 计算覆盖关系
			if( m_vtUI[index][0]->m_pUI )
			{
				m_vtUI[index][0]->m_pUI->SetCovered( false );
				for ( UINT n=1; n<m_vtUI[index].size(); n++ )
				{
					if ( m_vtUI[index][n]->m_pUI )
					{
						m_vtUI[index][n]->m_pUI->SetCovered( false );
						for ( UINT m=0; m<n; m++ )
						{
							if( m_vtUI[index][n]->m_pUI )
							{
								if( m_vtUI[index][n]->m_pUI->IsBeCovered( m_vtUI[index][m]->m_pUI ) == true )
								{
									m_vtUI[index][n]->m_pUI->SetCovered( true );
									break;
								}
							}

						}
					}

				}
			}

		}
	}
	unguard;
}

//void UiManager::InitDeviceObjects( IN UiDrawer::funRegisterTexture pRegisterTexture,
//								   IN UiDrawer::funUnregisterTexture pUnregisterTexture,
//								   IN UiDrawer::funBlt pBlt,
//								   IN UiDrawer::funDrawRect2D pDrawRect2D,
//								   IN UiDrawer::funFillRect2DEx pFillRect2D,
//								   IN UiDrawer::funDrawProgressRect pDrawProgressRect,
//								   IN FontSystem::funCreateFont pCreateFont,
//								   IN FontSystem::funReleaseFonts pReleaseFonts,
//								   IN FontSystem::funDrawTextARGB pDrawTextARGB,
//								   IN FontSystem::funDrawTextARGBEx pDrawTextARGBEx )
//{
//	guardfunc;
//	UiDrawer::RegisterTexture = pRegisterTexture;
//	UiDrawer::UnregisterTexture = pUnregisterTexture;
//	UiDrawer::Blt = pBlt;
//	UiDrawer::DrawRect2D = pDrawRect2D;
//	UiDrawer::FillRect2DEx = pFillRect2D;
//	UiDrawer::DrawProgressRect = pDrawProgressRect;
//	FontSystem::CreateFont = pCreateFont;
//	FontSystem::ReleaseFonts = pReleaseFonts;
//	FontSystem::DrawTextARGB = pDrawTextARGB;
//	FontSystem::DrawTextARGBEx = pDrawTextARGBEx;
//
//	FontSystem::CreateFont( "文鼎中隶简", 12 );
//	unguard;
//}
void UiManager::InitDeviceObjects( IN UiDrawer::funRegisterTexture pRegisterTexture,
//                                    IN UiDrawer::funRegisterTextureFromFileMem pRegisterTextureFromFileMem,
								   IN UiDrawer::funUnregisterTexture pUnregisterTexture,
								   IN UiDrawer::funBlt pBlt,
								   IN UiDrawer::funDrawRect2D pDrawRect2D,
								   IN UiDrawer::funFillRect2DEx pFillRect2D,
								   IN UiDrawer::funDrawProgressRect pDrawProgressRect )
{
	guardfunc;
	UiDrawer::RegisterTexture = pRegisterTexture;
//     UiDrawer::RegisterTextureFromFileMem = pRegisterTextureFromFileMem;
	UiDrawer::UnregisterTexture = pUnregisterTexture;
	UiDrawer::Blt = pBlt;
	UiDrawer::DrawRect2D = pDrawRect2D;
	UiDrawer::FillRect2DEx = pFillRect2D;
	UiDrawer::DrawProgressRect = pDrawProgressRect;
	unguard;
}

void UiManager::SetPlaySoundFun( funPlaySound pFun )
{
	m_pPlaySoundFun = pFun;
}

void UiManager::SetRButtonUp( funRButtonUp pFun )
{
	m_pRButtonUpFun = pFun;
}

void UiManager::SetCreateHelpWindowFun( funcCreateHelpWindow pFun )
{
	m_pCreateHelpWindowFun = pFun;
}

bool UiManager::PlaySound( std::string& strFileName )
{
	guardfunc;
	if( NULL != state.Get() && _luaTableName.length() > 0 && _funPlaySoundName.length() > 0 )
	{
		try
		{
			LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
			if( table1Obj.IsTable() )
			{
				LuaFunction<void> function_( table1Obj[_funPlaySoundName.c_str()] );
				function_( strFileName.c_str() );
			}
		}
		catch (LuaPlus::LuaException &e)
		{
			char szErr[256] = {0};
			_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funPlaySoundName.c_str(), e.GetErrorMessage());
			print_error( szErr );
		}
	}
	else
	{
		if ( m_pPlaySoundFun )
		{
			return m_pPlaySoundFun( strFileName.c_str(), NULL,false);
		}
	}
	unguard;
	return false;
}

void UiManager::InvalidateDeviceObjects()
{
	//	FontSystem::ReleaseFonts();

	for( int index = 0; index < m_vtUI.size(); ++index )
	{
		for( int n = m_vtUI[index].size() - 1; n >= 0; n-- )
		{
			m_vtUI[index][n]->m_pUI->LostDevice();
		}
	}

	theControlPictureManager.Release();
}

void UiManager::RestoreDeviceObjects()
{
//	FontSystem::ReleaseFonts();
	//	FontSystem::CreateFont( "宋体", 12 );

	for( int index = 0; index < m_vtUI.size(); ++index )
	{
		for( int n = m_vtUI[index].size() - 1; n >= 0; n-- )
		{
			m_vtUI[index][n]->m_pUI->ResetDevice();
		}
	}
}

bool UiManager::HasModalWindow(int layer)
{
	//for( int index = 0; index < m_vtUI.size(); ++index )
	//{

	if( layer >= m_vtUI.size() )
		return false;

	ControlFrame *p_ui = m_vtUI[layer][0]->m_pUI;
	if ( m_vtUI[layer].size() > 0 && p_ui && p_ui->GetControlType() == Type_Frame )
	{
		if (p_ui->IsNeedRender())
		{
			if ( p_ui->GetArrayMode() == ArrayMode_Top )
			{
				return true;
			}
		}
		else
		{
			if ( p_ui->GetArrayMode() == ArrayMode_SingleModal )
			{
				return true;
			}
		}
		
	}
	return false;
}

ControlObject* UiManager::GetFrameFocus()
{
	m_pFatherFocus = NULL;
	for( int index = m_vtUI.size() - 1; index >= 0; --index )
	{
		if( m_vtUI[index].size() > 0 )
		{
			m_pFatherFocus = m_vtUI[index][0]->m_pUI;
		}

		if( m_pFatherFocus )
		{
			break;
		}
	}
	return m_pFatherFocus;
}
void UiManager::SetFocus(ControlObject* pObj)
{
	if (m_pFocus)
		m_pFocus->FocusOut();

	m_pFocus = pObj;

	if (m_pFocus)
		m_pFocus->FocusIn();
}
bool UiManager::isInUI( int x, int y )
{
	for( int index = 0; index < m_vtUI.size(); ++index )
	{
		for ( int n=0 ;n<m_vtUI[index].size(); ++n )
		{
			if ( m_vtUI[index][n]->m_pUI->IsMouseInUI( x, y) )
			{
				return true;
			}
		}
	}
	return false;
}
void UiManager::SetPlaySoundFun_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funPlaySoundName = funName;
	unguard;
}
void UiManager::SetLogInfoFun_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funLogInfoName = funName;
	unguard;
}

ControlFrame* UiManager::AddFrameByIndex( IN const char* szFileName,int index, bool bAllVisable /*= false*/, UI_Render_Layer layer /*= UI_Render_LayerFirst */ )
{
	guard(UiManager::AddFrameByIndex);
	if( !szFileName )
		return 0;

	char fullname[MAX_PATH];
	if( szFileName[1] == ':' )
	{
		strcpy( fullname, szFileName  );
	}
	else
		sprintf( fullname, "%s\\%s", GetRootPath(), szFileName );

	S_UI* stUI = MeNew S_UI;
 	stUI->m_strFileName = fullname;
	stUI->m_pUI = MeNew ControlFrame;
	DWORD dwCreatedDate = 0;


	ControlFrame *pFrame = (ControlFrame*)stUI->m_pUI;

	dwCreatedDate = pFrame->LoadUIFormFile(fullname,NULL,index);

	pFrame->SetVisable(true);

	if(bAllVisable)//为真 说明是 小地图 Main 角色信息 这样的dlg 进来了
		stUI->m_pUI->SetAllVisableDlg();

	if( dwCreatedDate == 0 )
	{
		delete stUI;
		return 0;
	}

	if( layer >= UI_Render_LayerMax )
		return 0;

	InsertNewFrame(layer, stUI);
	return stUI->m_pUI;

	unguard;

}

bool UiManager::OnFrameRunIndexedFrame( IN const char *szFrameID, IN ControlFrame::funRunIndexedFrame pFunIndexedFrame )
{
	assert( szFrameID );
	assert( pFunIndexedFrame );

	ControlObject *pUI = FindFrame( szFrameID );
	if ( pUI && pUI->GetControlType() == Type_Frame )
	{
		ControlFrame* pFrame = (ControlFrame*)pUI;
		pFrame->SetIndexedFrameRunFun( pFunIndexedFrame );
		return true;
	}
#ifdef _DEBUG
	char szError[128];
	sprintf( szError, "找不到指定框架:%s", szFrameID );
	MESSAGE_BOX( szError )
#endif
		return false;

}

bool UiManager::OnFrameRenderIndexedFrame( IN const char *szFrameID, IN ControlFrame::funRenderIndexedFrame pFunIndexedFrame, const bool bBeforeRender /*= false */ )
{
	assert( szFrameID );
	assert( pFunIndexedFrame );

	ControlObject *pUI = FindFrame( szFrameID );
	if ( pUI && pUI->GetControlType() == Type_Frame )
	{
		ControlFrame* pFrame = (ControlFrame*)pUI;
		pFrame->SetIndexedFrameRenderFun( pFunIndexedFrame, bBeforeRender );
		return true;
	}
#ifdef _DEBUG
	char szError[128];
	sprintf( szError, "找不到指定框架:%s", szFrameID );
	MESSAGE_BOX( szError )
#endif
		return false;

}

void UiManager::SetFrameLayout(int nLayoutIndex, ControlFrame* pFrame)
{
	if (!pFrame)
		return;

	RemoveFrameLayout(pFrame);

	std::pair< std::map<ControlFrame*, int>::iterator, bool > res =
		m_FrameLayoutIndexSet.insert(std::make_pair(pFrame, nLayoutIndex));
	if (res.second)
		m_LayoutIndexFrameSet.insert(std::make_pair(nLayoutIndex, pFrame));
}

void UiManager::RemoveFrameLayout(ControlFrame* pFrame)
{
	if (!pFrame)
		return;

	std::map<ControlFrame*, int>::iterator it = m_FrameLayoutIndexSet.find(pFrame);
	if (it != m_FrameLayoutIndexSet.end())
	{
		std::multimap<int, ControlFrame*>::iterator it2 = m_LayoutIndexFrameSet.find(it->second);
		size_t n = m_LayoutIndexFrameSet.count(it->second);
		for (size_t i = 0; i < n; ++i, ++it2)
		{
			if (it2->second == pFrame)
			{
				m_LayoutIndexFrameSet.erase(it2);
				break;
			}
		}

		m_FrameLayoutIndexSet.erase(it);
	}
}

void UiManager::ShowFrame(ControlFrame* pFrame)
{
	if (!pFrame)
		return;

	std::map<ControlFrame*, int>::iterator it = m_FrameLayoutIndexSet.find(pFrame);
	if (it != m_FrameLayoutIndexSet.end())
	{
		std::multimap<int, ControlFrame*>::iterator it2, end2 = m_LayoutIndexFrameSet.end();
		for (it2 = m_LayoutIndexFrameSet.begin(); it2 != end2; ++it2)
		{
			if (it2->first != it->second)
				it2->second->SetVisable(false);
		}
	}
}


UiManager::S_UI::S_UI()
{
	m_pUI = NULL;
	m_bNeedRelease = true;
}

UiManager::S_UI::~S_UI()
{
	Release();
}