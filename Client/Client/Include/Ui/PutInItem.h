/********************************************************************
	Created by UIEditor.exe
	FileName: F:\project\Turbo\Bin\Client\Data\Ui\PutInItem.h
*********************************************************************/

/*----------------------------------------------------------
desc	: 代工物品放置界面。	
author	: zilong
version	: 1.0
date	: 2011-03-22
revision:
----------------------------------------------------------*/

#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_PutInItem
#define ID_FRAME_PutInItem		"ID_FRAME_PutInItem"
#endif  ID_FRAME_PutInItem
#ifndef ID_BUTTON_Ture
#define ID_BUTTON_Ture		"ID_BUTTON_Ture"
#endif  ID_BUTTON_Ture
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_LISTIMG_Item
#define ID_LISTIMG_Item		"ID_LISTIMG_Item"
#endif  ID_LISTIMG_Item
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title

#include "UIBase.h"
class CUI_ID_FRAME_PutInItem: public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_PutInItem();
	 ControlFrame*	m_pID_FRAME_PutInItem;
	 ControlButton*	m_pID_BUTTON_Ture;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlListImage*	m_pID_LISTIMG_Item;
	 ControlText*	m_pID_TEXT_Title;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_TureOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

private:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视
};
extern CUI_ID_FRAME_PutInItem s_CUI_ID_FRAME_PutInItem;
