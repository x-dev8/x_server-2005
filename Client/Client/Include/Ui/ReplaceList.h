/********************************************************************
	Created by UIEditor.exe
	FileName: F:\project\Turbo\Bin\Client\Data\Ui\ReplaceList.h
*********************************************************************/

/*----------------------------------------------------------
desc	: 代工列表界面。
author	: zilong
version	: 1.0
date	: 2011-03-22
revision:
----------------------------------------------------------*/

#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_ReplaceList
#define ID_FRAME_ReplaceList		"ID_FRAME_ReplaceList"
#endif  ID_FRAME_ReplaceList
#ifndef ID_LIST_Name
#define ID_LIST_Name		"ID_LIST_Name"
#endif  ID_LIST_Name
#ifndef ID_BUTTON_Update
#define ID_BUTTON_Update		"ID_BUTTON_Update"
#endif  ID_BUTTON_Update
#ifndef ID_LIST_Lvl
#define ID_LIST_Lvl		"ID_LIST_Lvl"
#endif  ID_LIST_Lvl
#ifndef ID_LIST_Price
#define ID_LIST_Price		"ID_LIST_Price"
#endif  ID_LIST_Price
#ifndef ID_LIST_Replace
#define ID_LIST_Replace		"ID_LIST_Replace"
#endif  ID_LIST_Replace

#include "UIBase.h"
class CUI_ID_FRAME_ReplaceList: public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_ReplaceList();
	 ControlFrame*	m_pID_FRAME_ReplaceList;
	 ControlList*	m_pID_LIST_Name;
	 ControlButton*	m_pID_BUTTON_Update;
	 ControlList*	m_pID_LIST_Lvl;
	 ControlList*	m_pID_LIST_Price;
	 ControlList*	m_pID_LIST_Replace;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_UpdateOnButtonClick( ControlObject* pSender );
	void ID_LIST_LvlOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_PriceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ReplaceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

private:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视
};
extern CUI_ID_FRAME_ReplaceList s_CUI_ID_FRAME_ReplaceList;
