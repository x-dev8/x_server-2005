///********************************************************************
//	Created by UIEditor.exe
//	FileName: E:\Work\HeroRuntime\CLIENT\UI\Shopping_MessageBox.h
//*********************************************************************/
//#pragma once
//#include "MeUi/MeUi.h"
//
//#ifndef ID_Shopping_MessageBox
//#define ID_Shopping_MessageBox		"ID_Shopping_MessageBox"
//#endif  ID_Shopping_MessageBox
//#ifndef ID_BUTTON_OK
//#define ID_BUTTON_OK		"ID_BUTTON_OK"
//#endif  ID_BUTTON_OK
//#ifndef ID_PICTURE_26801
//#define ID_PICTURE_26801		"ID_PICTURE_26801"
//#endif  ID_PICTURE_26801
//#ifndef ID_PICTURE_26802
//#define ID_PICTURE_26802		"ID_PICTURE_26802"
//#endif  ID_PICTURE_26802
//#ifndef ID_PICTURE_26803
//#define ID_PICTURE_26803		"ID_PICTURE_26803"
//#endif  ID_PICTURE_26803
//#ifndef ID_PICTURE_26804
//#define ID_PICTURE_26804		"ID_PICTURE_26804"
//#endif  ID_PICTURE_26804
//#ifndef ID_TEXT_Static0
//#define ID_TEXT_Static0		"ID_TEXT_Static0"
//#endif  ID_TEXT_Static0
//#ifndef ID_TEXT_Static1
//#define ID_TEXT_Static1		"ID_TEXT_Static1"
//#endif  ID_TEXT_Static1
//#ifndef ID_TEXT_ItemName
//#define ID_TEXT_ItemName		"ID_TEXT_ItemName"
//#endif  ID_TEXT_ItemName
//#ifndef ID_TEXT_ItemPrice
//#define ID_TEXT_ItemPrice		"ID_TEXT_ItemPrice"
//#endif  ID_TEXT_ItemPrice
//#ifndef ID_BUTTON_Back
//#define ID_BUTTON_Back		"ID_BUTTON_Back"
//#endif  ID_BUTTON_Back
//#ifndef ID_TEXT_Note
//#define ID_TEXT_Note		"ID_TEXT_Note"
//#endif  ID_TEXT_Note
//#ifndef ID_PICTURE_26805
//#define ID_PICTURE_26805		"ID_PICTURE_26805"
//#endif  ID_PICTURE_26805
//#ifndef ID_TEXT_YinPiao
//#define ID_TEXT_YinPiao		"ID_TEXT_YinPiao"
//#endif  ID_TEXT_YinPiao
//#include "UIBase.h"
//class CUI_ID_Shopping_MessageBox : public CUIBase
//{
//	// SGuildMember
//public:
//	CUI_ID_Shopping_MessageBox();
//private:
//	void ResetMembers();
//	short m_UseItem;
//	 ControlFrame*	m_pID_Shopping_MessageBox;
//	 ControlButton*	m_pID_BUTTON_OK;
//	 ControlPicture*	m_pID_PICTURE_26801;
//	 ControlPicture*	m_pID_PICTURE_26802;
//	 ControlPicture*	m_pID_PICTURE_26803;
//	 ControlPicture*	m_pID_PICTURE_26804;
//	 ControlText*	m_pID_TEXT_Static0;
//	 ControlText*	m_pID_TEXT_Static1;
//	 ControlText*	m_pID_TEXT_ItemName;
//	 ControlText*	m_pID_TEXT_ItemPrice;
//	 ControlButton*	m_pID_BUTTON_Back;
//	 ControlText*	m_pID_TEXT_Note;
//	 ControlPicture*	m_pID_PICTURE_26805;
//	 ControlText*	m_pID_TEXT_YinPiao;
//
//public:
//	// Frame
//	bool OnFrameRun();
//	bool OnFrameRender();
//	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
//	bool ID_BUTTON_BackOnButtonClick( ControlObject* pSender );
//
//	
//private:
//	virtual bool _LoadUI();				// 载入UI
//	bool DoControlConnect();	// 关连控件
//	virtual bool _UnLoadUI();			// 卸载UI
//	virtual bool _IsVisable();			// 是否可见
//	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
//public:
//
//
//	static bool MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );
//
//};
//extern CUI_ID_Shopping_MessageBox s_CUI_ID_Shopping_MessageBox;