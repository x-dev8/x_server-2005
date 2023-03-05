/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\法宝资源\法宝\法宝\TalismanRenovate.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "GlobalDef.h"

#ifndef ID_FRAME_TalismanRenovate
#define ID_FRAME_TalismanRenovate		"ID_FRAME_TalismanRenovate"
#endif  ID_FRAME_TalismanRenovate
#ifndef ID_LISTIMG_TalismanIcon
#define ID_LISTIMG_TalismanIcon		"ID_LISTIMG_TalismanIcon"
#endif  ID_LISTIMG_TalismanIcon
#ifndef ID_TEXT_TalismanName
#define ID_TEXT_TalismanName		"ID_TEXT_TalismanName"
#endif  ID_TEXT_TalismanName
#ifndef ID_TEXT_TalismanLv
#define ID_TEXT_TalismanLv		"ID_TEXT_TalismanLv"
#endif  ID_TEXT_TalismanLv
#ifndef ID_LISTIMG_Genre
#define ID_LISTIMG_Genre		"ID_LISTIMG_Genre"
#endif  ID_LISTIMG_Genre
#ifndef ID_LISTIMG_MaterialIcon
#define ID_LISTIMG_MaterialIcon		"ID_LISTIMG_MaterialIcon"
#endif  ID_LISTIMG_MaterialIcon
#ifndef ID_TEXT_MaterialName
#define ID_TEXT_MaterialName		"ID_TEXT_MaterialName"
#endif  ID_TEXT_MaterialName
#ifndef ID_TEXT_Moment
#define ID_TEXT_Moment		"ID_TEXT_Moment"
#endif  ID_TEXT_Moment
#ifndef ID_BUTTON_Return
#define ID_BUTTON_Return		"ID_BUTTON_Return"
#endif  ID_BUTTON_Return
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP

class CUI_ID_FRAME_TalismanRenovate  : public CUIBase
{
	// Member
public:
	 CUI_ID_FRAME_TalismanRenovate();
private:	
	 ControlFrame*	m_pID_FRAME_TalismanRenovate;
	 ControlListImage*	m_pID_LISTIMG_TalismanIcon;
	 ControlText*	m_pID_TEXT_TalismanName;
	 ControlText*	m_pID_TEXT_TalismanLv;
	 ControlListImage*	m_pID_LISTIMG_Genre;
	 ControlListImage*	m_pID_LISTIMG_MaterialIcon;
	 ControlText*	m_pID_TEXT_MaterialName;
	 ControlText*	m_pID_TEXT_Moment;
	 ControlButton*	m_pID_BUTTON_Return;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_HELP;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_TalismanIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_TalismanIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_TalismanIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_TalismanIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_GenreOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_GenreOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_GenreOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_GenreOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_ReturnOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:
	void UpdateTaliInfo(SCharItem *pItem);
	void UpdateMaterialInfo(unsigned short usItemId,int nCount);
};
extern CUI_ID_FRAME_TalismanRenovate s_CUI_ID_FRAME_TalismanRenovate;
