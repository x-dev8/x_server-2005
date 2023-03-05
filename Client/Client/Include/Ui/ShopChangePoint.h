/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\ShopChangePoint.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_ShopChangePoint
#define ID_FRAME_ShopChangePoint		"ID_FRAME_ShopChangePoint"
#endif  ID_FRAME_ShopChangePoint
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_PICTURE_22476
#define ID_PICTURE_22476		"ID_PICTURE_22476"
#endif  ID_PICTURE_22476
#ifndef ID_PICTURE_28008
#define ID_PICTURE_28008		"ID_PICTURE_28008"
#endif  ID_PICTURE_28008
#ifndef ID_PICTURE_27628
#define ID_PICTURE_27628		"ID_PICTURE_27628"
#endif  ID_PICTURE_27628
#ifndef ID_PICTURE_20101
#define ID_PICTURE_20101		"ID_PICTURE_20101"
#endif  ID_PICTURE_20101
#ifndef ID_PICTURE_TitleWall
#define ID_PICTURE_TitleWall		"ID_PICTURE_TitleWall"
#endif  ID_PICTURE_TitleWall
#ifndef ID_TEXT_Point
#define ID_TEXT_Point		"ID_TEXT_Point"
#endif  ID_TEXT_Point
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title
#ifndef ID_BUTTON_Close
#define ID_BUTTON_Close		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_Close
#ifndef ID_BUTTON_Help
#define ID_BUTTON_Help		"ID_BUTTON_Help"
#endif  ID_BUTTON_Help
#ifndef ID_PICTURE_Wall3
#define ID_PICTURE_Wall3		"ID_PICTURE_Wall3"
#endif  ID_PICTURE_Wall3
#ifndef ID_EDIT_YuanBao
#define ID_EDIT_YuanBao		"ID_EDIT_YuanBao"
#endif  ID_EDIT_YuanBao
#ifndef ID_TEXT_Word
#define ID_TEXT_Word		"ID_TEXT_Word"
#endif  ID_TEXT_Word
#ifndef ID_TEXT_ChangeWord
#define ID_TEXT_ChangeWord		"ID_TEXT_ChangeWord"
#endif  ID_TEXT_ChangeWord
#ifndef ID_BUTTON_Up
#define ID_BUTTON_Up		"ID_BUTTON_Up"
#endif  ID_BUTTON_Up
#ifndef ID_BUTTON_Down
#define ID_BUTTON_Down		"ID_BUTTON_Down"
#endif  ID_BUTTON_Down
#ifndef ID_BUTTON_Max
#define ID_BUTTON_Max		"ID_BUTTON_Max"
#endif  ID_BUTTON_Max
#ifndef ID_TEXT_ChangeRate
#define ID_TEXT_ChangeRate		"ID_TEXT_ChangeRate"
#endif  ID_TEXT_ChangeRate
#ifndef ID_TEXT_Hold
#define ID_TEXT_Hold		"ID_TEXT_Hold"
#endif  ID_TEXT_Hold

#include "UiBase.h"
class CUI_ID_FRAME_ShopChangePoint :public CUIBase
{
	// Member
private:
	void ResetMembers();
	ControlFrame*	m_pID_FRAME_ShopChangePoint;
	ControlButton*	m_pID_BUTTON_Ok;
	ControlButton*	m_pID_BUTTON_Cancel;
	ControlPicture*	m_pID_PICTURE_22476;
	ControlPicture*	m_pID_PICTURE_28008;
	ControlPicture*	m_pID_PICTURE_27628;
	ControlPicture*	m_pID_PICTURE_20101;
	ControlPicture*	m_pID_PICTURE_TitleWall;
	ControlText*	m_pID_TEXT_Point;
	ControlText*	m_pID_TEXT_Title;
	ControlButton*	m_pID_BUTTON_Close;
	ControlButton*	m_pID_BUTTON_Help;
	ControlPicture*	m_pID_PICTURE_Wall3;
	ControlEdit*	m_pID_EDIT_YuanBao;
	ControlText*	m_pID_TEXT_Word;
	ControlText*	m_pID_TEXT_ChangeWord;
	ControlButton*	m_pID_BUTTON_Up;
	ControlButton*	m_pID_BUTTON_Down;
	ControlButton*	m_pID_BUTTON_Max;
	ControlText*	m_pID_TEXT_ChangeRate;
    ControlText*	m_pID_TEXT_Hold;

public:	
	CUI_ID_FRAME_ShopChangePoint();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HelpOnButtonClick( ControlObject* pSender );
	void ID_EDIT_YuanBaoOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_UpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DownOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_MaxOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	ControlFrame* GetFrame() { return m_pID_FRAME_ShopChangePoint; }
	static void EditDataChange( OUT ControlObject* pSender, OUT const char *szData );
	void SetMaxValue(int value) { m_nMaxValue = value; }
	void SetPoint(int point) { m_nPoint = point; }
	void YuanBao_SetNumberLimit(bool limit, int min, int max);
	void Point_SetText( const char* text );
	void Hold_SetText( const char* text );
private:
	int	m_nMaxValue;

	int m_nPoint;

	DWORD m_dwLastTime;
};
extern CUI_ID_FRAME_ShopChangePoint s_CUI_ID_FRAME_ShopChangePoint;
