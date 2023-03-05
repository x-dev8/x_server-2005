#include "MeUi/MeUi.h"
#include "MeUi/MouseManager.h"
#include "MeUi/UiPicture.h"
#include "MeUi/UiManager.h"
#include "FuncPerformanceLog.h"

#define CURSOR_SIZE	32

MouseManager theMouseManager;

extern const WCHAR* GetFullName(const WCHAR* filename);

MouseManager::MouseManager(void)
{
	m_bSetCursor = FALSE;
	m_bCanSet = true;
}

MouseManager::~MouseManager(void)
{
}

void MouseManager::Render()
{
 //   POINT ptMouse;
 //   extern HWND g_hWnd;
 //   GetCursorPos( &ptMouse );
 //   ScreenToClient( g_hWnd, &ptMouse );

	//static DWORD dwLastTime = 0;
	//if ( HQ_TimeGetTime() - dwLastTime >= 50 )
	//{
	//	dwLastTime = HQ_TimeGetTime();
	//	//
	//	if( ++m_nCurFrame > 16 )
	//		m_nCurFrame = 0;
	//	//
	//	m_rcSrc.left	= m_nCurFrame%4*CURSOR_SIZE;
	//	m_rcSrc.top		= m_nCurFrame/4*CURSOR_SIZE;
	//	m_rcSrc.right	= m_rcSrc.left + CURSOR_SIZE;
	//	m_rcSrc.bottom	= m_rcSrc.top + CURSOR_SIZE;
	//} 
	//m_rcDst.left	= ptMouse.x;
	//m_rcDst.top		= ptMouse.y;
	//m_rcDst.right	= m_rcDst.left + CURSOR_SIZE;
	//m_rcDst.bottom	= m_rcDst.top + CURSOR_SIZE;
	//theControlPictureManager.BitBlt( &m_nCursorPicId[m_enCurCursor],
	//						m_strCursorName[m_enCurCursor].c_str(),
	//						&m_rcDst, &m_rcSrc );

	static HCURSOR hCursor = NULL;
	if ( theUiManager.IsMouseInUI() )
	{
		if( hCursor != m_hCursor[m_enUICursor] )
		{
			hCursor = m_hCursor[m_enUICursor];
			m_bSetCursor = TRUE;
		}
	}
	else
	{
		if( hCursor != m_hCursor[m_enCurCursor] )
		{
			hCursor = m_hCursor[m_enCurCursor];
			m_bSetCursor = TRUE;
		}
	}
	if ( hCursor && m_bSetCursor )
	{
		m_bSetCursor = FALSE;
		::SetCursor( hCursor );
	}

}

void MouseManager::SetCursor( const E_CursorType enType )
{
	if (m_bCanSet)
		m_enCurCursor = enType;
}

void MouseManager::SetUICursor( const E_CursorType enType )
{
	if (m_bCanSet)
		m_enUICursor = enType;
}

void MouseManager::LoadCursor()
{
	m_hCursor[Type_Arrow] = LoadCursorFromFileW( GetFullName(L"Cursor\\Arrow.ani") );
	m_hCursor[Type_Rotate] = LoadCursorFromFileW( GetFullName(L"Cursor\\CameraRotate.ani" ) );
	m_hCursor[Type_Wait] = LoadCursorFromFileW( GetFullName(L"Cursor\\Wait.ani" ) );
	m_hCursor[Type_LockTarget] = LoadCursorFromFileW( GetFullName(L"Cursor\\LockTarget.ani" ) );
	m_hCursor[Type_Attack] = LoadCursorFromFileW( GetFullName(L"Cursor\\Attack.ani" ) );
	m_hCursor[Type_Dialog] = LoadCursorFromFileW( GetFullName(L"Cursor\\Dialog.ani" ) );
	m_hCursor[Type_Shop] = LoadCursorFromFileW( GetFullName(L"Cursor\\Shop.ani" ) );
	m_hCursor[Type_Pick] = LoadCursorFromFileW( GetFullName(L"Cursor\\Pick.ani" ) );
	m_hCursor[Type_Group] = LoadCursorFromFileW( GetFullName(L"Cursor\\Group.ani" ) );
	m_hCursor[Type_CollectHerb] = LoadCursorFromFileW( GetFullName(L"Cursor\\CollectHerb.ani" ) );
	m_hCursor[Type_CollectMine] = LoadCursorFromFileW( GetFullName(L"Cursor\\CollectMine.ani" ) );
	m_hCursor[Type_CollectWood] = LoadCursorFromFileW( GetFullName(L"Cursor\\CollectWood.ani" ) );
	m_hCursor[Type_LockItem] = LoadCursorFromFileW( GetFullName(L"Cursor\\LockItem.ani" ) );
	m_hCursor[Type_UnLockItem] = LoadCursorFromFileW( GetFullName(L"Cursor\\UnLockItem.ani" ) );
	m_hCursor[Type_UseItem] = LoadCursorFromFileW( GetFullName(L"Cursor\\UseItem.ani" ) );
	m_hCursor[Type_PathFinding] = LoadCursorFromFileW( GetFullName(L"Cursor\\PathFinding.ani" ) );
	m_hCursor[Type_Destroy] = m_hCursor[Type_Pick];
	m_hCursor[Type_Split] = m_hCursor[Type_Pick];
	m_hCursor[Type_Repair] = LoadCursorFromFileW( GetFullName(L"Cursor\\Repair.ani" ) );
	m_hCursor[Type_LeftDrag] = LoadCursorFromFileW( GetFullName(L"Cursor\\LeftDrag.ani" ) );
	m_hCursor[Type_CollectMount] = LoadCursorFromFileW( GetFullName(L"Cursor\\CollectMount.ani" ) );
    m_hCursor[Type_MoveFollowMouse] = m_hCursor[Type_PathFinding];
    m_hCursor[Type_PickItem] = LoadCursorFromFileW( GetFullName(L"Cursor\\PickItem.ani" ) );
    m_hCursor[Type_NpcItem] = LoadCursorFromFileW( GetFullName(L"Cursor\\NPCpick.ani" ) );
	m_hCursor[Type_MoveWindow] = LoadCursorFromFileW( GetFullName(L"Cursor\\Move.ani" ) );
    m_hCursor[Type_ChatHyper] = LoadCursorFromFileW( GetFullName(L"Cursor\\ChatHyper.ani" ) );
    m_hCursor[Type_ChatPlayer] = LoadCursorFromFileW( GetFullName(L"Cursor\\ChatPlayer.ani" ) );
    m_hCursor[Type_CastBomb] = LoadCursorFromFileW( GetFullName(L"Cursor\\CastBomb.ani" ) );
	m_hCursor[Type_CheckUp] = LoadCursorFromFileW( GetFullName(L"Cursor\\CheckUp.ani" ) );
	m_hCursor[Type_Decompose] = LoadCursorFromFileW( GetFullName(L"Cursor\\Decompose.ani" ) );
}