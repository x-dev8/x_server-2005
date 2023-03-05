/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\PopIntro5.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_PopIntro5
#define ID_FRAME_PopIntro5		"ID_FRAME_PopIntro5"
#endif  ID_FRAME_PopIntro5
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_TEXT_Info
#define ID_TEXT_Info		"ID_TEXT_Info"
#endif  ID_TEXT_Info
#ifndef ID_LISTIMG_Equip
#define ID_LISTIMG_Equip		"ID_LISTIMG_Equip"
#endif  ID_LISTIMG_Equip
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_EquipName
#define ID_TEXT_EquipName		"ID_TEXT_EquipName"
#endif  ID_TEXT_EquipName

class CUI_ID_FRAME_PopIntro5 :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_PopIntro5();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_EquipOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_EquipOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_EquipOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_EquipOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
private:
	ControlFrame*	    m_pID_FRAME_PopIntro5;
	ControlButton*	    m_pID_BUTTON_Ok;
	ControlText*	    m_pID_TEXT_Info;
	ControlListImage*	m_pID_LISTIMG_Equip;
	ControlButton*	    m_pID_BUTTON_CLOSE;
	ControlText*	    m_pID_TEXT_EquipName;

public:
	void  ShowItemInfo(std::string &strInfo);

private:
    int                 m_nItemId;
};

extern CUI_ID_FRAME_PopIntro5 s_CUI_ID_FRAME_PopIntro5;
