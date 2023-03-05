/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\Guild_Info.cpp
*********************************************************************/
#include <assert.h>
#include "..\..\MEUI\UIManager.h"
#include "Guild_Info.h"
#include "Guild_Announce.h"
#include "Guild_Member.h"
#include "..\..\Common\FuncPerformanceLog.h"
namespace UI_ID_FRAME_Guild_Info
{
	// Member
	CHR_UI_Frame*	m_pID_FRAME_Guild_Info = NULL;
	CHR_UI_Text*	m_pID_TEXT_Name = NULL;
	CHR_UI_Text*	m_pID_TEXT_Level = NULL;
	CHR_UI_Text*	m_pID_TEXT_PlayerNum = NULL;
	CHR_UI_Edit*	m_pID_EDIT_Info = NULL;
	CHR_UI_Progress*	m_pID_PROGRESS_Exp = NULL;
	CHR_UI_Button*	m_pID_BUTTON_Member = NULL;
	CHR_UI_Button*	m_pID_BUTTON_Announce = NULL;
	CHR_UI_Button*	m_pID_BUTTON_Mgr = NULL;
	CHR_UI_Button*	m_pID_BUTTON_CLOSE = NULL;

	// Frame
	bool ID_FRAME_Guild_InfoOnFrameRun()
	{
		return true;
	}
	bool ID_FRAME_Guild_InfoOnFrameRender()
	{
		return true;
	}
	// Edit
	void ID_EDIT_InfoOnEditEnter( CHR_UI_Object* pSender, const char* szData )
	{
	}
	// Button
	bool ID_BUTTON_MemberOnButtonClick( CHR_UI_Object* pSender )
	{
		guardfunc;
		UI_ID_FRAME_Guild_Member::SetVisable( true );
		return true;
		unguard;
	}
	// Button
	bool ID_BUTTON_AnnounceOnButtonClick( CHR_UI_Object* pSender )
	{
		guardfunc;
		UI_ID_FRAME_Guild_Announce::SetVisable( true );
		return true;
		unguard;
	}
	// Button
	bool ID_BUTTON_MgrOnButtonClick( CHR_UI_Object* pSender )
	{
		return true;
	}
	// Button
	bool ID_BUTTON_CLOSEOnButtonClick( CHR_UI_Object* pSender )
	{
		return false;
	}

	// 装载UI
	bool LoadUI()
	{
		guardfunc;
		DWORD dwResult = theHRUIMgr.AddFrame( "UI\\Guild_Info.UI" );
		if ( dwResult == 0 )
		{
			MESSAGE_BOX("读取文件[UI\\Guild_Info.UI]失败")
			return false;
		}
		else if ( dwResult != 102448/*文件版本号*/ )
		{
			MESSAGE_BOX("读取文件[UI\\Guild_Info.UI]与源代码版本不一样")
		}
		return DoControlConnect();
		unguard;
	}
	// 关连控件
	bool DoControlConnect()
	{
		guardfunc;
		theHRUIMgr.OnFrameRun( ID_FRAME_Guild_Info, ID_FRAME_Guild_InfoOnFrameRun );
		theHRUIMgr.OnFrameRender( ID_FRAME_Guild_Info, ID_FRAME_Guild_InfoOnFrameRender );
		theHRUIMgr.OnEditEnter( ID_FRAME_Guild_Info, ID_EDIT_Info, ID_EDIT_InfoOnEditEnter );
		theHRUIMgr.OnButtonClick( ID_FRAME_Guild_Info, ID_BUTTON_Member, ID_BUTTON_MemberOnButtonClick );
		theHRUIMgr.OnButtonClick( ID_FRAME_Guild_Info, ID_BUTTON_Announce, ID_BUTTON_AnnounceOnButtonClick );
		theHRUIMgr.OnButtonClick( ID_FRAME_Guild_Info, ID_BUTTON_Mgr, ID_BUTTON_MgrOnButtonClick );
		theHRUIMgr.OnButtonClick( ID_FRAME_Guild_Info, ID_BUTTON_CLOSE, ID_BUTTON_CLOSEOnButtonClick );

		m_pID_FRAME_Guild_Info = (CHR_UI_Frame*)theHRUIMgr.FindFrame( ID_FRAME_Guild_Info );
		m_pID_TEXT_Name = (CHR_UI_Text*)theHRUIMgr.FindControl( ID_FRAME_Guild_Info, ID_TEXT_Name );
		m_pID_TEXT_Level = (CHR_UI_Text*)theHRUIMgr.FindControl( ID_FRAME_Guild_Info, ID_TEXT_Level );
		m_pID_TEXT_PlayerNum = (CHR_UI_Text*)theHRUIMgr.FindControl( ID_FRAME_Guild_Info, ID_TEXT_PlayerNum );
		m_pID_EDIT_Info = (CHR_UI_Edit*)theHRUIMgr.FindControl( ID_FRAME_Guild_Info, ID_EDIT_Info );
		m_pID_PROGRESS_Exp = (CHR_UI_Progress*)theHRUIMgr.FindControl( ID_FRAME_Guild_Info, ID_PROGRESS_Exp );
		m_pID_BUTTON_Member = (CHR_UI_Button*)theHRUIMgr.FindControl( ID_FRAME_Guild_Info, ID_BUTTON_Member );
		m_pID_BUTTON_Announce = (CHR_UI_Button*)theHRUIMgr.FindControl( ID_FRAME_Guild_Info, ID_BUTTON_Announce );
		m_pID_BUTTON_Mgr = (CHR_UI_Button*)theHRUIMgr.FindControl( ID_FRAME_Guild_Info, ID_BUTTON_Mgr );
		m_pID_BUTTON_CLOSE = (CHR_UI_Button*)theHRUIMgr.FindControl( ID_FRAME_Guild_Info, ID_BUTTON_CLOSE );
		assert( m_pID_FRAME_Guild_Info );
		assert( m_pID_TEXT_Name );
		assert( m_pID_TEXT_Level );
		assert( m_pID_TEXT_PlayerNum );
		assert( m_pID_EDIT_Info );
		assert( m_pID_PROGRESS_Exp );
		assert( m_pID_BUTTON_Member );
		assert( m_pID_BUTTON_Announce );
		assert( m_pID_BUTTON_Mgr );
		assert( m_pID_BUTTON_CLOSE );
		return true;
		unguard;
	}
	// 卸载UI
	bool UnLoadUI()
	{
		guardfunc;
		return theHRUIMgr.RemoveFrame( "UI\\Guild_Info.UI" );
		unguard;
	}
	// 是否可视
	bool IsVisable()
	{
		guardfunc;
		return m_pID_FRAME_Guild_Info->IsVisable();
		unguard;
	}
	// 设置是否可视
	void SetVisable( const bool bVisable )
	{
		guardfunc;
		m_pID_FRAME_Guild_Info->SetVisable( bVisable );
		if ( bVisable == true )
		{
			RECT rc={0,0,0,0};
			bool bHaveVisable = true;
			if ( UI_ID_FRAME_Guild_Announce::IsVisable() == true )
			{
				UI_ID_FRAME_Guild_Announce::m_pID_FRAME_Guild_Announce->GetRealRect( &rc );
				UI_ID_FRAME_Guild_Announce::SetVisable( false );
			}
			else if ( UI_ID_FRAME_Guild_Member::IsVisable() == true )
			{
				UI_ID_FRAME_Guild_Member::m_pID_FRAME_Guild_Member->GetRealRect( &rc );
				UI_ID_FRAME_Guild_Member::SetVisable( false );
			}
			else
			{
				bHaveVisable = false;
			}
			if ( bHaveVisable )
			{
				m_pID_FRAME_Guild_Info->SetPos( rc.left, rc.top );
			}
		}
		unguard;
	}
}
