/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (13)\FamilyUI\Family.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_Family
#define ID_FRAME_Family		"ID_FRAME_Family"
#endif  ID_FRAME_Family
#ifndef ID_LIST_FamilyName
#define ID_LIST_FamilyName		"ID_LIST_FamilyName"
#endif  ID_LIST_FamilyName
#ifndef ID_PICTURE_Logo
#define ID_PICTURE_Logo		"ID_PICTURE_Logo"
#endif  ID_PICTURE_Logo
#ifndef ID_LIST_Profession
#define ID_LIST_Profession		"ID_LIST_Profession"
#endif  ID_LIST_Profession
#ifndef ID_LIST_Contribute
#define ID_LIST_Contribute		"ID_LIST_Contribute"
#endif  ID_LIST_Contribute
#ifndef ID_LIST_Level
#define ID_LIST_Level		"ID_LIST_Level"
#endif  ID_LIST_Level
#ifndef ID_TEXT_FamilyName
#define ID_TEXT_FamilyName		"ID_TEXT_FamilyName"
#endif  ID_TEXT_FamilyName
#ifndef ID_TEXT_ZuZhang
#define ID_TEXT_ZuZhang		"ID_TEXT_ZuZhang"
#endif  ID_TEXT_ZuZhang
#ifndef ID_TEXT_FamilyLevel
#define ID_TEXT_FamilyLevel		"ID_TEXT_FamilyLevel"
#endif  ID_TEXT_FamilyLevel
#ifndef ID_TEXT_Amount
#define ID_TEXT_Amount		"ID_TEXT_Amount"
#endif  ID_TEXT_Amount
#ifndef ID_TEXT_FanRongDu
#define ID_TEXT_FanRongDu		"ID_TEXT_FanRongDu"
#endif  ID_TEXT_FanRongDu
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_TEXT_Affiche
#define ID_TEXT_Affiche		"ID_TEXT_Affiche"
#endif  ID_TEXT_Affiche
#ifndef ID_TEXT_FamilyInfo
#define ID_TEXT_FamilyInfo		"ID_TEXT_FamilyInfo"
#endif  ID_TEXT_FamilyInfo
#ifndef ID_BUTTON_Expel
#define ID_BUTTON_Expel		"ID_BUTTON_Expel"
#endif  ID_BUTTON_Expel
#ifndef ID_BUTTON_Attorn
#define ID_BUTTON_Attorn		"ID_BUTTON_Attorn"
#endif  ID_BUTTON_Attorn
#ifndef ID_BUTTON_Exit
#define ID_BUTTON_Exit		"ID_BUTTON_Exit"
#endif  ID_BUTTON_Exit
#ifndef ID_BUTTON_Affiche
#define ID_BUTTON_Affiche		"ID_BUTTON_Affiche"
#endif  ID_BUTTON_Affiche
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_Upgrade
#define ID_BUTTON_Upgrade		"ID_BUTTON_Upgrade"
#endif  ID_BUTTON_Upgrade
#ifndef ID_BUTTON_Contribute
#define ID_BUTTON_Contribute		"ID_BUTTON_Contribute"
#endif  ID_BUTTON_Contribute
#ifndef ID_LIST_Name
#define ID_LIST_Name		"ID_LIST_Name"
#endif  ID_LIST_Name
#ifndef ID_LIST_ZhiWu
#define ID_LIST_ZhiWu		"ID_LIST_ZhiWu"
#endif  ID_LIST_ZhiWu
#ifndef ID_LIST_Line
#define ID_LIST_Line		"ID_LIST_Line"
#endif  ID_LIST_Line

#ifndef ID_BUTTON_AddZY
#define ID_BUTTON_AddZY		"ID_BUTTON_AddZY"
#endif  ID_BUTTON_AddZY
#ifndef ID_BUTTON_ChangeZZ
#define ID_BUTTON_ChangeZZ		"ID_BUTTON_ChangeZZ"
#endif  ID_BUTTON_ChangeZZ

#include "UIBase.h"
#include "FamilyDefine.h"

class CUI_ID_FRAME_Family : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_Family();
	 ControlFrame*	m_pID_FRAME_Family;
	 ControlList*	m_pID_LIST_FamilyName;
	 ControlPicture*	m_pID_PICTURE_Logo;
	 ControlList*	m_pID_LIST_Profession;
	 ControlList*	m_pID_LIST_Contribute;
	 ControlList*	m_pID_LIST_Level;
	 ControlList*	m_pID_LIST_Name;
	 ControlText*	m_pID_TEXT_FamilyName;
	 ControlText*	m_pID_TEXT_ZuZhang;
	 ControlText*	m_pID_TEXT_FamilyLevel;
	 ControlText*	m_pID_TEXT_Amount;
	 ControlText*	m_pID_TEXT_FanRongDu;
	 ControlText*	m_pID_TEXT_Money;
	 ControlText*	m_pID_TEXT_Affiche;
	 ControlText*	m_pID_TEXT_FamilyInfo;
	 ControlButton*	m_pID_BUTTON_Expel;
	 ControlButton*	m_pID_BUTTON_Attorn;
	 ControlButton*	m_pID_BUTTON_Exit;
	 ControlButton*	m_pID_BUTTON_Affiche;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_Upgrade;
	 ControlButton*	m_pID_BUTTON_Contribute;
	 ControlList*	m_pID_LIST_ZhiWu;
	 ControlList*	m_pID_LIST_Line;

	 ControlButton*	m_pID_BUTTON_AddZY;
	 ControlButton*	m_pID_BUTTON_ChangeZZ;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_FamilyNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ProfessionOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ContributeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_LevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_ExpelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AttornOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ExitOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AfficheOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_UpgradeOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ContributeOnButtonClick( ControlObject* pSender );
	void ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ZhiWuOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_LineOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	bool ID_BUTTON_AddZYOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ChangeZZOnButtonClick( ControlObject* pSender );

public:
	void SetButtonsEnable( bool bval );
	void ClearAllValues();			//清除内容
	void AddToList( const char* name, const char* level, const char* profession, const char* money, const char* position, const char* line, DWORD clr );
	void InitialValues();
	void RefreshValues();

	void DoAttornMemeber();			//踢出成员
	

public:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:	
	std::vector<FamilyDefine::FamilyMember> m_vecFamilyMembers;
};
extern CUI_ID_FRAME_Family s_CUI_ID_FRAME_Family;
