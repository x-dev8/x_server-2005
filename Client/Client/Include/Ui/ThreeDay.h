/********************************************************************
	Created by UIEditor.exe
	FileName: D:\FullBag(13.10.181)\Data\Ui\ThreeDay.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#ifndef ID_FRAME_ThreeDay
#define ID_FRAME_ThreeDay		"ID_FRAME_ThreeDay"
#endif  ID_FRAME_ThreeDay
#ifndef ID_BUTTON_GetAward
#define ID_BUTTON_GetAward		"ID_BUTTON_GetAward"
#endif  ID_BUTTON_GetAward
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_LISTIMG_20626
#define ID_LISTIMG_20626		"ID_LISTIMG_20626"
#endif  ID_LISTIMG_20626

class CUI_ID_FRAME_ThreeDay : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_ThreeDay();
	 ControlFrame*	m_pID_FRAME_ThreeDay;
	 ControlButton*	m_pID_BUTTON_GetAward;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlListImage*	m_pID_LISTIMG_20626;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_GetAwardOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_20626OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_20626OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_20626OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_20626OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
private:
	void OnShow();
};
extern CUI_ID_FRAME_ThreeDay s_CUI_ID_FRAME_ThreeDay;
