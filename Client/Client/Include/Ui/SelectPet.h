/********************************************************************
	Created by UIEditor.exe
	FileName: F:\project\Turbo\Bin\Client\Data\Ui\SelectPet.h
*********************************************************************/

/*----------------------------------------------------------
desc	: 宠物选择界面。
author	: zilong
version	: 1.0
date	: 2011-03-22
revision:
----------------------------------------------------------*/

#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_SelectPet
#define ID_FRAME_SelectPet		"ID_FRAME_SelectPet"
#endif  ID_FRAME_SelectPet
#ifndef ID_BUTTON_Select
#define ID_BUTTON_Select		"ID_BUTTON_Select"
#endif  ID_BUTTON_Select
#ifndef ID_LIST_PetName
#define ID_LIST_PetName		"ID_LIST_PetName"
#endif  ID_LIST_PetName
#ifndef ID_BUTTON_Seek
#define ID_BUTTON_Seek		"ID_BUTTON_Seek"
#endif  ID_BUTTON_Seek
#ifndef ID_BUTTON_CallBack
#define ID_BUTTON_CallBack		"ID_BUTTON_CallBack"
#endif  ID_BUTTON_CallBack

#include "UIBase.h"
class CUI_ID_FRAME_SelectPet: public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_SelectPet();
	 ControlFrame*	m_pID_FRAME_SelectPet;
	 ControlButton*	m_pID_BUTTON_Select;
	 ControlList*	m_pID_LIST_PetName;
	 ControlButton*	m_pID_BUTTON_Seek;
	 ControlButton*	m_pID_BUTTON_CallBack;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_SelectOnButtonClick( ControlObject* pSender );
	void ID_LIST_PetNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_SeekOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CallBackOnButtonClick( ControlObject* pSender );

	void Refresh( bool bKeepSelect = false );

	void RefreshButtonStatus(void);
	void RefreshButtonStatusForBargaining();

	void EnableSelect( bool bEnable );

private:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视

private:
	bool m_bEnableSelect;
};
extern CUI_ID_FRAME_SelectPet s_CUI_ID_FRAME_SelectPet;
