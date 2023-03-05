/********************************************************************
Created by UIEditor.exe
FileName: E:\3Guo_Client_12.27\3Guo_Client_12.27\Data\Ui\AdditionFuncMenu.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_AdditionFuncMenu
#define ID_FRAME_AdditionFuncMenu		"ID_FRAME_AdditionFuncMenu"
#endif  ID_FRAME_AdditionFuncMenu
#ifndef ID_BUTTON_Star
#define ID_BUTTON_Star		"ID_BUTTON_Star"
#endif  ID_BUTTON_Star
#ifndef ID_BUTTON_GemUp
#define ID_BUTTON_GemUp		"ID_BUTTON_GemUp"
#endif  ID_BUTTON_GemUp
#ifndef ID_BUTTON_Gem
#define ID_BUTTON_Gem		"ID_BUTTON_Gem"
#endif  ID_BUTTON_Gem
#ifndef ID_BUTTON_Hole
#define ID_BUTTON_Hole		"ID_BUTTON_Hole"
#endif	ID_BUTTON_Hole
#ifndef ID_BUTTON_TransferStar
#define ID_BUTTON_TransferStar		"ID_BUTTON_TransferStar"
#endif  ID_BUTTON_TransferStar
#ifndef ID_BUTTON_UNBond
#define ID_BUTTON_UNBond		"ID_BUTTON_UNBond"
#endif  ID_BUTTON_UNBond
#ifndef ID_BUTTON_GemRemove
#define ID_BUTTON_GemRemove		"ID_BUTTON_GemRemove"
#endif  ID_BUTTON_GemRemove


class CUI_ID_FRAME_AdditionFuncMenu:public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_AdditionFuncMenu();
	ControlFrame*	m_pID_FRAME_AdditionFuncMenu;
	ControlButton*	m_pID_BUTTON_Star;
	ControlButton*	m_pID_BUTTON_GemUp;
	ControlButton*	m_pID_BUTTON_Gem;
	ControlButton*  m_pID_BUTTON_Hole;
	ControlButton*	m_pID_BUTTON_TransferStar;
	ControlButton*	m_pID_BUTTON_UNBond;
	ControlButton*	m_pID_BUTTON_GemRemove;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_StarOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_GemUpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_GemOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HoleOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TransferStarOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_UNBondOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_GemRemoveOnButtonClick( ControlObject* pSender );

	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视
};
extern CUI_ID_FRAME_AdditionFuncMenu s_CUI_ID_FRAME_AdditionFuncMenu;
