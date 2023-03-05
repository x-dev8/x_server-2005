/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\DoubleExp.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "MessageDefine.h"

#ifndef ID_FRAME_DuobleExp
#define ID_FRAME_DuobleExp		"ID_FRAME_DuobleExp"
#endif  ID_FRAME_DuobleExp
#ifndef ID_PICTURE_System
#define ID_PICTURE_System		"ID_PICTURE_System"
#endif  ID_PICTURE_System
#ifndef ID_PICTURE_Item1
#define ID_PICTURE_Item1		"ID_PICTURE_Item1"
#endif  ID_PICTURE_Item1
#ifndef ID_PICTURE_Total
#define ID_PICTURE_Total		"ID_PICTURE_Total"
#endif  ID_PICTURE_Total
#ifndef ID_PICTURE_Item2
#define ID_PICTURE_Item2		"ID_PICTURE_Item2"
#endif  ID_PICTURE_Item2
#ifndef ID_PICTURE_Icon
#define ID_PICTURE_Icon		"ID_PICTURE_Icon"
#endif  ID_PICTURE_Icon
#ifndef ID_PICTURE_NumBg1
#define ID_PICTURE_NumBg1		"ID_PICTURE_NumBg1"
#endif  ID_PICTURE_NumBg1
#ifndef ID_PICTURE_NumBg2
#define ID_PICTURE_NumBg2		"ID_PICTURE_NumBg2"
#endif  ID_PICTURE_NumBg2
#ifndef ID_PICTURE_NumBg3
#define ID_PICTURE_NumBg3		"ID_PICTURE_NumBg3"
#endif  ID_PICTURE_NumBg3
#ifndef ID_PICTURE_Minute1
#define ID_PICTURE_Minute1		"ID_PICTURE_Minute1"
#endif  ID_PICTURE_Minute1
#ifndef ID_PICTURE_Minute2
#define ID_PICTURE_Minute2		"ID_PICTURE_Minute2"
#endif  ID_PICTURE_Minute2
#ifndef ID_PICTURE_Minute3
#define ID_PICTURE_Minute3		"ID_PICTURE_Minute3"
#endif  ID_PICTURE_Minute3
#ifndef ID_TEXT_Tip
#define ID_TEXT_Tip		"ID_TEXT_Tip"
#endif  ID_TEXT_Tip
#ifndef ID_TEXT_Time1
#define ID_TEXT_Time1		"ID_TEXT_Time1"
#endif  ID_TEXT_Time1
#ifndef ID_TEXT_Time2
#define ID_TEXT_Time2		"ID_TEXT_Time2"
#endif  ID_TEXT_Time2
#ifndef ID_TEXT_Time3
#define ID_TEXT_Time3		"ID_TEXT_Time3"
#endif  ID_TEXT_Time3
#ifndef ID_LISTIMG_Item
#define ID_LISTIMG_Item		"ID_LISTIMG_Item"
#endif  ID_LISTIMG_Item
#ifndef ID_BUTTON_Buy
#define ID_BUTTON_Buy		"ID_BUTTON_Buy"
#endif  ID_BUTTON_Buy
#ifndef ID_BUTTON_Start
#define ID_BUTTON_Start		"ID_BUTTON_Start"
#endif  ID_BUTTON_Start
#ifndef ID_BUTTON_Stop
#define ID_BUTTON_Stop		"ID_BUTTON_Stop"
#endif  ID_BUTTON_Stop
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP

#include "UIBase.h"
class CUI_ID_FRAME_DuobleExp : public CUIBase
{
public:
	CUI_ID_FRAME_DuobleExp();
	// Member
private:	
	 ControlFrame*	m_pID_FRAME_DuobleExp;
	 ControlPicture*	m_pID_PICTURE_System;
	 ControlPicture*	m_pID_PICTURE_Item1;
	 ControlPicture*	m_pID_PICTURE_Total;
	 ControlPicture*	m_pID_PICTURE_Item2;
	 ControlPicture*	m_pID_PICTURE_Icon;
	 ControlPicture*	m_pID_PICTURE_NumBg1;
	 ControlPicture*	m_pID_PICTURE_NumBg2;
	 ControlPicture*	m_pID_PICTURE_NumBg3;
	 ControlPicture*	m_pID_PICTURE_Minute1;
	 ControlPicture*	m_pID_PICTURE_Minute2;
	 ControlPicture*	m_pID_PICTURE_Minute3;
	 ControlText*	m_pID_TEXT_Tip;
	 ControlText*	m_pID_TEXT_Time1;
	 ControlText*	m_pID_TEXT_Time2;
	 ControlText*	m_pID_TEXT_Time3;
	 ControlListImage*	m_pID_LISTIMG_Item;
	 ControlButton*	m_pID_BUTTON_Buy;
	 ControlButton*	m_pID_BUTTON_Start;
	 ControlButton*	m_pID_BUTTON_Stop;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_HELP;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_BuyOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_StartOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_StopOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );

	void OnMsgDoubleExp(Msg* pMsg);
protected:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视

	void RefreshDoubleExp();
	bool m_bState;
	uint32  nLastRefreshTime;      
	uint32  nLastUIUpdateTime;      
private:	
};
extern CUI_ID_FRAME_DuobleExp s_CUI_ID_FRAME_DuobleExp;
