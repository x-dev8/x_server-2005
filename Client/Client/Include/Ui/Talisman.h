/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\法宝资源\法宝\法宝\Talisman.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "GlobalDef.h"
#include "ItemDetail.h"

#ifndef ID_FRAME_Talisman
#define ID_FRAME_Talisman		"ID_FRAME_Talisman"
#endif  ID_FRAME_Talisman
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_PICTURE_Yingxiang
#define ID_PICTURE_Yingxiang		"ID_PICTURE_Yingxiang"
#endif  ID_PICTURE_Yingxiang
#ifndef ID_BUTTON_Right
#define ID_BUTTON_Right		"ID_BUTTON_Right"
#endif  ID_BUTTON_Right
#ifndef ID_BUTTON_Left
#define ID_BUTTON_Left		"ID_BUTTON_Left"
#endif  ID_BUTTON_Left
#ifndef ID_TEXT_Generation
#define ID_TEXT_Generation		"ID_TEXT_Generation"
#endif  ID_TEXT_Generation
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_LISTIMG_Item
#define ID_LISTIMG_Item		"ID_LISTIMG_Item"
#endif  ID_LISTIMG_Item
#ifndef ID_TEXT_Item
#define ID_TEXT_Item		"ID_TEXT_Item"
#endif  ID_TEXT_Item
#ifndef ID_TEXT_Item2
#define ID_TEXT_Item2		"ID_TEXT_Item2"
#endif  ID_TEXT_Item2
#ifndef ID_PROGRESS_32378
#define ID_PROGRESS_32378		"ID_PROGRESS_32378"
#endif  ID_PROGRESS_32378
#ifndef ID_TEXT_ItemIntroduce
#define ID_TEXT_ItemIntroduce		"ID_TEXT_ItemIntroduce"
#endif  ID_TEXT_ItemIntroduce
#ifndef ID_LIST_TalismanList
#define ID_LIST_TalismanList		"ID_LIST_TalismanList"
#endif  ID_LIST_TalismanList
#ifndef ID_LISTIMG_Genre
#define ID_LISTIMG_Genre		"ID_LISTIMG_Genre"
#endif  ID_LISTIMG_Genre
#ifndef ID_TEXT_Moment
#define ID_TEXT_Moment		"ID_TEXT_Moment"
#endif  ID_TEXT_Moment
#ifndef ID_TEXT_Attribute
#define ID_TEXT_Attribute		"ID_TEXT_Attribute"
#endif  ID_TEXT_Attribute

class CUI_ID_FRAME_Talisman : public CUIBase
{
	// Member
public:
	 CUI_ID_FRAME_Talisman();
private:	
	 ControlFrame*	m_pID_FRAME_Talisman;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlPicture*	m_pID_PICTURE_Yingxiang;
	 ControlButton*	m_pID_BUTTON_Right;
	 ControlButton*	m_pID_BUTTON_Left;
	 ControlText*	m_pID_TEXT_Generation;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlListImage*	m_pID_LISTIMG_Item;
	 ControlText*	m_pID_TEXT_Item;
	 ControlText*	m_pID_TEXT_Item2;
	 ControlProgress*	m_pID_PROGRESS_32378;
	 ControlText*	m_pID_TEXT_ItemIntroduce;
	 ControlList*	m_pID_LIST_TalismanList;
	 ControlListImage*	m_pID_LISTIMG_Genre;
	 ControlText*	m_pID_TEXT_Moment;
	 ControlText*	m_pID_TEXT_Attribute;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RightOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LeftOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_LIST_TalismanListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_LISTIMG_GenreOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_GenreOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_GenreOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_GenreOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:	
	void UpdateTalisman(SCharItem *pItem);
	void UpdateBaseInfo(SCharItem *pItem);
	void UpdateExp(SCharItem *pItem);
	void UpdateSkillDesc(ItemDefine::SItemSkill* pSkill);
	void UpdateRebuldInfo(SCharItem *pItem);
	bool IsTalismanList(ControlListImage *pSender);
};
extern CUI_ID_FRAME_Talisman s_CUI_ID_FRAME_Talisman;
