/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildCampBattle.h
*********************************************************************/
//用于控制公会中玩家的战场状态的
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "GuildDefine.h"
#ifndef ID_FRAME_CampBattle
#define ID_FRAME_CampBattle		"ID_FRAME_CampBattle"
#endif  ID_FRAME_CampBattle
#ifndef ID_LIST_CampBattleType
#define ID_LIST_CampBattleType		"ID_LIST_CampBattleType"
#endif  ID_LIST_CampBattleType
#ifndef ID_LIST_Exites
#define ID_LIST_Exites		"ID_LIST_Exites"
#endif  ID_LIST_Exites
#ifndef ID_BUTTON_Add
#define ID_BUTTON_Add		"ID_BUTTON_Add"
#endif  ID_BUTTON_Add
#ifndef ID_BUTTON_Del
#define ID_BUTTON_Del		"ID_BUTTON_Del"
#endif  ID_BUTTON_Del
#ifndef ID_LIST_None
#define ID_LIST_None		"ID_LIST_None"
#endif  ID_LIST_None

class CUI_ID_FRAME_CampBattle:public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_CampBattle();
	 ControlFrame*	m_pID_FRAME_CampBattle;
	 ControlList*	m_pID_LIST_CampBattleType;
	 ControlList*	m_pID_LIST_Exites;
	 ControlButton*	m_pID_BUTTON_Add;
	 ControlButton*	m_pID_BUTTON_Del;
	 ControlList*	m_pID_LIST_None;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_CampBattleTypeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ExitesOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_AddOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DelOnButtonClick( ControlObject* pSender );
	void ID_LIST_NoneOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	void OnUpdateMemberInfo();
private:
	void OnShow();

	void SetCampBattleType();

	void OnSelectCampBattleType();

	bool IsCanAddToCampBattle(GuildMember* pMember,unsigned int Value);

	void OnAddToCampBattle();
	void OnDelToCampBattle();
private:
	vector<int>			m_ExitesIndexToID;
	vector<int>			m_NonIndexToID;
};
extern CUI_ID_FRAME_CampBattle s_CUI_ID_FRAME_CampBattle;
