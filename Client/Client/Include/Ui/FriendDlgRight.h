/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\FriendDlgRight.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "RelationDefine.h"
#ifndef ID_FRAME_FriendDlgRight
#define ID_FRAME_FriendDlgRight		"ID_FRAME_FriendDlgRight"
#endif  ID_FRAME_FriendDlgRight
#ifndef ID_BUTTON_AddClass
#define ID_BUTTON_AddClass		"ID_BUTTON_AddClass"
#endif  ID_BUTTON_AddClass
#ifndef ID_BUTTON_DelClass
#define ID_BUTTON_DelClass		"ID_BUTTON_DelClass"
#endif  ID_BUTTON_DelClass
#ifndef ID_BUTTON_RenameClass
#define ID_BUTTON_RenameClass		"ID_BUTTON_RenameClass"
#endif  ID_BUTTON_RenameClass

#include "UiBase.h"
class CUI_ID_FRAME_FriendDlgRight :public CUIBase
{
	// Member
private:	
	ControlFrame*	m_pID_FRAME_FriendDlgRight;
	ControlButton*	m_pID_BUTTON_AddClass;
	ControlButton*	m_pID_BUTTON_DelClass;
	ControlButton*	m_pID_BUTTON_RenameClass;

public:	
	CUI_ID_FRAME_FriendDlgRight();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_AddClassOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DelClassOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RenameClassOnButtonClick( ControlObject* pSender );

	ControlFrame* GetFrame() const { return m_pID_FRAME_FriendDlgRight; }
private:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视
};
extern CUI_ID_FRAME_FriendDlgRight s_CUI_ID_FRAME_FriendDlgRight;
