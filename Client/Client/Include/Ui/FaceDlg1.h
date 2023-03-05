/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Work\HeroRuntime\Client\DATA\UI\FaceDlg1.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_FACE
#define ID_FRAME_FACE		"ID_FRAME_FACE"
#endif  ID_FRAME_FACE
#ifndef ID_PICTURE_BG
#define ID_PICTURE_BG		"ID_PICTURE_BG"
#endif  ID_PICTURE_BG
#ifndef ID_PICTURE_DECT
#define ID_PICTURE_DECT		"ID_PICTURE_DECT"
#endif  ID_PICTURE_DECT
#ifndef ID_BUTTON_left
#define ID_BUTTON_left		"ID_BUTTON_left"
#endif  ID_BUTTON_left
#ifndef ID_BUTTON_right
#define ID_BUTTON_right		"ID_BUTTON_right"
#endif  ID_BUTTON_right
#ifndef ID_TEXT_Page
#define ID_TEXT_Page		"ID_TEXT_Page"
#endif  ID_TEXT_Page

#include "UiBase.h"
class CUI_ID_FRAME_FACE :public CUIBase
{
public:
	CUI_ID_FRAME_FACE();
	// SGuildMember
private:	
	 ControlFrame*	m_pID_FRAME_FACE;
// 	 ControlPicture*	m_pID_PICTURE_BG;
	 ControlPicture*	m_pID_PICTURE_DECT;
	 ControlButton*	m_pID_BUTTON_left;
	 ControlButton*	m_pID_BUTTON_right;
	 ControlText*	m_pID_TEXT_Page;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_leftOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_rightOnButtonClick( ControlObject* pSender );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	static bool On_PICTURE_ExpressionRECTClick( ControlObject* pSender);
	static void On_PICTURE_ExpressionRECTMouseOn( ControlObject* pSender);
	static bool ChatMsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );
	bool MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

	void SetPos(int x,int y);
	int  GetAlignMode();
	void SetAlignMode( int i );
	void SetScreenPos(int x,int y);

	void SetTotalPage();
	void ShowPage();
	void RefreshPageEnable();

private:
	int m_nExpressionCount;
	int m_nCursorOn;
	int m_selectImgId;
	bool m_bEditWidgetActive;
	int	m_nCount;
	bool m_bNeedGetFontInfo;
	int m_nFontSize;
	int m_nFontIndex;
	float m_fFontScale;

	int m_curPage;
	int m_totalPage;
	int m_curPageOn;
};
extern bool g_bMessageChat;
extern CUI_ID_FRAME_FACE s_CUI_ID_FRAME_FACE;
