/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Work\HeroRuntime\CLIENT\UI\Shopping_InputBox.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_Shopping_InputBox
#define ID_Shopping_InputBox		"ID_Shopping_InputBox"
#endif  ID_Shopping_InputBox
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_UP
#define ID_BUTTON_UP		"ID_BUTTON_UP"
#endif  ID_BUTTON_UP
#ifndef ID_BUTTON_DOWN
#define ID_BUTTON_DOWN		"ID_BUTTON_DOWN"
#endif  ID_BUTTON_DOWN
#ifndef ID_EDIT_INPUT
#define ID_EDIT_INPUT		"ID_EDIT_INPUT"
#endif  ID_EDIT_INPUT
#ifndef ID_TEXT_Static0
#define ID_TEXT_Static0		"ID_TEXT_Static0"
#endif  ID_TEXT_Static0
#ifndef ID_TEXT_Static1
#define ID_TEXT_Static1		"ID_TEXT_Static1"
#endif  ID_TEXT_Static1
#ifndef ID_TEXT_ItemName
#define ID_TEXT_ItemName		"ID_TEXT_ItemName"
#endif  ID_TEXT_ItemName
#ifndef ID_TEXT_ItemPrice
#define ID_TEXT_ItemPrice		"ID_TEXT_ItemPrice"
#endif  ID_TEXT_ItemPrice
#ifndef ID_TEXT_15393
#define ID_TEXT_15393		"ID_TEXT_15393"
#endif  ID_TEXT_15393
#ifndef ID_BUTTON_Back
#define ID_BUTTON_Back		"ID_BUTTON_Back"
#endif  ID_BUTTON_Back
#ifndef ID_TEXT_Note
#define ID_TEXT_Note		"ID_TEXT_Note"
#endif  ID_TEXT_Note
#ifndef ID_TEXT_YinPiao
#define ID_TEXT_YinPiao		"ID_TEXT_YinPiao"
#endif  ID_TEXT_YinPiao
#include "UIBase.h"
class CUI_ID_Shopping_InputBox : public CUIBase
{
	// SGuildMember
public:
	CUI_ID_Shopping_InputBox();
private:	
	void ResetMembers();
	 ControlFrame*	m_pID_Shopping_InputBox;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_UP;
	 ControlButton*	m_pID_BUTTON_DOWN;
	 ControlEdit*	m_pID_EDIT_INPUT;
	 ControlText*	m_pID_TEXT_Static0;
	 ControlText*	m_pID_TEXT_Static1;
	 ControlText*	m_pID_TEXT_ItemName;
	 ControlText*	m_pID_TEXT_ItemPrice;
	 ControlText*	m_pID_TEXT_15393;
	 ControlButton*	m_pID_BUTTON_Back;
	 ControlText*	m_pID_TEXT_Note;
	 ControlText*	m_pID_TEXT_YinPiao;
	 class CShopCenterNode* m_pShopNode;

	 short			m_UseItem;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_UPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DOWNOnButtonClick( ControlObject* pSender );
	void ID_EDIT_INPUTOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_BackOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


private:
	bool EditInputIsVisable();

	static bool MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

};
extern CUI_ID_Shopping_InputBox s_CUI_ID_Shopping_InputBox;