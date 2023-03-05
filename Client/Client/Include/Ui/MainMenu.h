/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\桌面\功能菜单\MainMenu.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "PlaneEffect.h"
#include "shortcutkey_configure.h"
#include "UIBase.h"

#ifndef ID_FRAME_MainMenu
#define ID_FRAME_MainMenu		"ID_FRAME_MainMenu"
#endif  ID_FRAME_MainMenu
#ifndef ID_BUTTON_Other
#define ID_BUTTON_Other		"ID_BUTTON_Other"
#endif  ID_BUTTON_Other
#ifndef ID_BUTTON_State
#define ID_BUTTON_State		"ID_BUTTON_State"
#endif  ID_BUTTON_State
#ifndef ID_BUTTON_Skill
#define ID_BUTTON_Skill		"ID_BUTTON_Skill"
#endif  ID_BUTTON_Skill
#ifndef ID_BUTTON_Task
#define ID_BUTTON_Task		"ID_BUTTON_Task"
#endif  ID_BUTTON_Task
#ifndef ID_BUTTON_Pack
#define ID_BUTTON_Pack		"ID_BUTTON_Pack"
#endif  ID_BUTTON_Pack
#ifndef ID_BUTTON_Group
#define ID_BUTTON_Group		"ID_BUTTON_Group"
#endif  ID_BUTTON_Group
#ifndef ID_BUTTON_System
#define ID_BUTTON_System		"ID_BUTTON_System"
#endif  ID_BUTTON_System
#ifndef ID_BUTTON_ConcealMain
#define ID_BUTTON_ConcealMain		"ID_BUTTON_ConcealMain"
#endif  ID_BUTTON_ConcealMain
#ifndef ID_PROGRESS_Friend
#define ID_PROGRESS_Friend		"ID_PROGRESS_Friend"
#endif  ID_PROGRESS_Friend
#ifndef ID_PROGRESS_Achivement
#define ID_PROGRESS_Achivement		"ID_PROGRESS_Achivement"
#endif  ID_PROGRESS_Achivement
#ifndef ID_PROGRESS_State
#define ID_PROGRESS_State		"ID_PROGRESS_State"
#endif  ID_PROGRESS_State
#ifndef ID_PROGRESS_Skill
#define ID_PROGRESS_Skill		"ID_PROGRESS_Skill"
#endif  ID_PROGRESS_Skill
#ifndef ID_PROGRESS_Pet
#define ID_PROGRESS_Pet		"ID_PROGRESS_Pet"
#endif  ID_PROGRESS_Pet
#ifndef ID_PROGRESS_Country
#define ID_PROGRESS_Country		"ID_PROGRESS_Country"
#endif  ID_PROGRESS_Country
#ifndef ID_PROGRESS_Task
#define ID_PROGRESS_Task		"ID_PROGRESS_Task"
#endif  ID_PROGRESS_Task
#ifndef ID_PROGRESS_Pack
#define ID_PROGRESS_Pack		"ID_PROGRESS_Pack"
#endif  ID_PROGRESS_Pack
#ifndef ID_PROGRESS_Guild
#define ID_PROGRESS_Guild		"ID_PROGRESS_Guild"
#endif  ID_PROGRESS_Guild
#ifndef ID_PROGRESS_System
#define ID_PROGRESS_System		"ID_PROGRESS_System"
#endif  ID_PROGRESS_System
#ifndef ID_BUTTON_SuAnimal
#define ID_BUTTON_SuAnimal		"ID_BUTTON_SuAnimal"
#endif  ID_BUTTON_SuAnimal
#ifndef ID_BUTTON_Gam
#define ID_BUTTON_Gam		"ID_BUTTON_Gam"
#endif  ID_BUTTON_Gam
#ifndef ID_TEXT_State
#define ID_TEXT_State		"ID_TEXT_State"
#endif  ID_TEXT_State
#ifndef ID_TEXT_Pack
#define ID_TEXT_Pack		"ID_TEXT_Pack"
#endif  ID_TEXT_Pack
#ifndef ID_TEXT_Skill
#define ID_TEXT_Skill		"ID_TEXT_Skill"
#endif  ID_TEXT_Skill
#ifndef ID_TEXT_SuAnimal
#define ID_TEXT_SuAnimal		"ID_TEXT_SuAnimal"
#endif  ID_TEXT_SuAnimal
#ifndef ID_TEXT_Task
#define ID_TEXT_Task		"ID_TEXT_Task"
#endif  ID_TEXT_Task
#ifndef ID_TEXT_Gam
#define ID_TEXT_Gam		"ID_TEXT_Gam"
#endif  ID_TEXT_Gam
#ifndef ID_TEXT_Other
#define ID_TEXT_Other		"ID_TEXT_Other"
#endif  ID_TEXT_Other
#ifndef ID_TEXT_System
#define ID_TEXT_System		"ID_TEXT_System"
#endif  ID_TEXT_System
#ifndef ID_BUTTON_OnMount
#define ID_BUTTON_OnMount		"ID_BUTTON_OnMount"
#endif  ID_BUTTON_OnMount
#ifndef ID_TEXT_OnMount
#define ID_TEXT_OnMount		"ID_TEXT_OnMount"
#endif  ID_TEXT_OnMount
#ifndef ID_BUTTON_PlayerPoint
#define ID_BUTTON_PlayerPoint	"ID_BUTTON_PlayerPoint"
#endif	ID_BUTTON_PlayerPoint
#ifndef ID_BUTTON_SuAnimalPoint
#define ID_BUTTON_SuAnimalPoint	"ID_BUTTON_SuAnimalPoint"
#endif	ID_BUTTON_SuAnimalPoint
#ifndef ID_BUTTON_MountPoint
#define ID_BUTTON_MountPoint	"ID_BUTTON_MountPoint"
#endif	ID_BUTTON_MountPoint
#ifndef ID_BUTTON_AdditionFunc
#define ID_BUTTON_AdditionFunc	"ID_BUTTON_AdditionFunc"
#endif	ID_BUTTON_AdditionFunc
#ifndef ID_TEXT_SuAnimalPoint
#define ID_TEXT_SuAnimalPoint	"ID_TEXT_SuAnimalPoint"
#endif	ID_TEXT_SuAnimalPoint
#ifndef ID_TEXT_MountPoint
#define ID_TEXT_MountPoint	"ID_TEXT_MountPoint"
#endif	ID_TEXT_MountPoint
#ifndef ID_TEXT_PlayerPoint
#define ID_TEXT_PlayerPoint	"ID_TEXT_PlayerPoint"
#endif	ID_TEXT_PlayerPoint

class CUI_ID_FRAME_MainMenu:public CUIBase
{
	// Member
public:	
	// Frame
	CUI_ID_FRAME_MainMenu();
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OtherOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_StateOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SkillOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TaskOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PackOnButtonClick( ControlObject* pSender );
	
	bool ID_BUTTON_GroupOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SystemOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ConcealMainOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SuAnimalOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_GamOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OnMountOnButtonClick(ControlObject* pSender);
	bool ID_BUTTON_PlayerPointOnButtonClick(ControlObject* pSender);
	bool ID_BUTTON_SuAnimalPointOnButtonClick(ControlObject* pSender);
	bool ID_BUTTON_MountPointOnButtonClick(ControlObject* pSender);
	bool ID_BUTTON_AdditionFuncOnButtonClick(ControlObject* pSender);
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void SetButGroupNormalPic();
	void SetButGroupPressPic();
	void SetButtonSpark(ControlButton*);
	 ControlFrame*	m_pID_FRAME_MainMenu;
	 ControlButton*	m_pID_BUTTON_Other;
	 ControlButton*	m_pID_BUTTON_State;
	 ControlButton*	m_pID_BUTTON_Skill;
	 ControlButton*	m_pID_BUTTON_Task;
	 ControlButton*	m_pID_BUTTON_Pack;
	 ControlButton*	m_pID_BUTTON_Group;
	 ControlButton*	m_pID_BUTTON_System;
	 ControlButton* m_pID_BUTTON_OnMount;
	 ControlButton*	m_pID_BUTTON_ConcealMain;
	 ControlButton* m_pID_BUTTON_PlayerPoint;
	 ControlButton* m_pID_BUTTON_SuAnimalPoint;
	 ControlButton* m_pID_BUTTON_MountPoint;
	 ControlProgress*	m_pID_PROGRESS_Friend;
	 ControlProgress*	m_pID_PROGRESS_Achivement;
	 ControlProgress*	m_pID_PROGRESS_State;
	 ControlProgress*	m_pID_PROGRESS_Skill;
	 ControlProgress*	m_pID_PROGRESS_Pet;
	 ControlProgress*	m_pID_PROGRESS_Country;
	 ControlProgress*	m_pID_PROGRESS_Task;
	 ControlProgress*	m_pID_PROGRESS_Pack;
	 ControlProgress*	m_pID_PROGRESS_Guild;
	 ControlProgress*	m_pID_PROGRESS_System;
	 ControlButton*	m_pID_BUTTON_SuAnimal;
	 ControlButton*	m_pID_BUTTON_Gam;
	 ControlButton* m_pID_BUTTON_AdditionFunc;
	 ControlText*	m_pID_TEXT_State;
	 ControlText*	m_pID_TEXT_Pack;
	 ControlText*	m_pID_TEXT_Skill;
	 ControlText*	m_pID_TEXT_SuAnimal;
	 ControlText*	m_pID_TEXT_Task;
	 ControlText*	m_pID_TEXT_Gam;
	 ControlText*	m_pID_TEXT_Other;
	 ControlText*	m_pID_TEXT_System;
	 ControlText*   m_pID_TEXT_OnMount;
	 ControlText*	m_pID_TEXT_PlayerPoint;
	 ControlText*	m_pID_TEXT_SuAnimalPoint;
	 ControlText*	m_pID_TEXT_MountPoint;

public:
	enum eKeySpark
	{
		ekey_baseProperty,
		ekey_skill,
		ekey_pet,
		ekey_country,
		ekey_task,
		ekey_bag,
		ekey_friend,
		ekey_guild,
		ekey_achivement,
		ekey_system,		
		ekey_max
	};

public:
	void refreshHotKey();
	// 设置按钮的图片，默认为正常情况下的图片，false为按下时的图片
	bool SetBtnPicture(	AN_Configure_ShortcutKey::ShortCutKey_Configure Key_Value= AN_Configure_ShortcutKey::AN_SCKC_uiBaseProperty,bool m_statu = true);
	void SetNeedSpark(bool, eKeySpark);
	void CheckNeedSparkBaseProperty();
	void CheckNeedSparkPack(uint8);
	void CheckNeedSparkAchivement();
	void CheckNeedSparkFriend();
	void SetSuanimalState(bool bValue);
	void SetOnMountPressPic();
	void SetOnMountNormalPic(); 
private:
	void RefreshSpark();
	void ShowButtonSpark(int);
	ControlProgress* m_xEffectSrray[ekey_max];
	void InitEffectAttr();
public:
	void SetBasePropertyHighLight();
	void SetPackHighLight();
	void SetSkillHighLight( bool bVisable );
	void SetSuAnimalHighLight();
	void SetTaskHighLight();
	void SetGamHighLight();
	void SetOtherHighLight();
	void SetSystemHighLight();
	void SetOnMountHighLight();

	ControlFrame* GetFrame() {return m_pID_FRAME_MainMenu;}

};
extern CUI_ID_FRAME_MainMenu s_CUI_ID_FRAME_MainMenu;
