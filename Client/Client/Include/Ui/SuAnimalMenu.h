/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\桌面\SuAnimalMenu.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GlobalDef.h"
#include "UIBase.h"

#ifndef ID_FRAME_SuAnimalMenu
#define ID_FRAME_SuAnimalMenu		"ID_FRAME_SuAnimalMenu"
#endif  ID_FRAME_SuAnimalMenu
#ifndef ID_BUTTON_Look
#define ID_BUTTON_Look		"ID_BUTTON_Look"
#endif  ID_BUTTON_Look
#ifndef ID_BUTTON_XiuXi
#define ID_BUTTON_XiuXi		"ID_BUTTON_XiuXi"
#endif  ID_BUTTON_XiuXi
#ifndef ID_BUTTON_Cure
#define ID_BUTTON_Cure		"ID_BUTTON_Cure"
#endif  ID_BUTTON_Cure
#ifndef ID_BUTTON_Feed
#define ID_BUTTON_Feed		"ID_BUTTON_Feed"
#endif  ID_BUTTON_Feed

class CUI_ID_FRAME_SuAnimalMenu:public CUIBase
{
	// Member
private:	
	 
	 ControlFrame*	m_pID_FRAME_SuAnimalMenu;
	 ControlButton*	m_pID_BUTTON_Look;
	 ControlButton*	m_pID_BUTTON_XiuXi;
	 ControlButton*	m_pID_BUTTON_Cure;
	 ControlButton*	m_pID_BUTTON_Feed;

public:	
	// Frame
	CUI_ID_FRAME_SuAnimalMenu();
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_LookOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_XiuXiOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CureOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FeedOnButtonClick( ControlObject* pSender );

	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视
	void UseItem(unsigned char ucValue);    //喂养、治疗等
	void SetCurrentPetIndex(const char *m_name);
	uint8	 GetCurrentPetIndex() { return m_CurrentPetIndex;}
	void SetPlayerID(GameObjectId m_playerID); //查看其他玩家的宠物
	GameObjectId GetPlayerID() { return m_OtherPlayerID;}
	ControlButton *GetXiuXiBtn();
	ControlButton *GetCureBtn();
	ControlButton *GetFeedBtn();
	void SetLookOtherPet(bool isLook) { m_IsLookOtherPet = isLook;}
private:	
	uint8 m_CurrentPetIndex;   //查看自身的宠物

	GameObjectId   m_OtherPlayerID;   //其他玩家的动态ID  
	bool m_IsLookOtherPet;                   //查看其它人的宠物
};
extern CUI_ID_FRAME_SuAnimalMenu s_CUI_ID_FRAME_SuAnimalMenu;

