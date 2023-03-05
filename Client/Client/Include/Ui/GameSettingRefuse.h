/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\请求拒绝\GameSettingRefuse.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GameSettingRefuse
#define ID_FRAME_GameSettingRefuse		"ID_FRAME_GameSettingRefuse"
#endif  ID_FRAME_GameSettingRefuse
#ifndef ID_PICTURE_Wall1
#define ID_PICTURE_Wall1		"ID_PICTURE_Wall1"
#endif  ID_PICTURE_Wall1
#ifndef ID_TEXT_Fight
#define ID_TEXT_Fight		"ID_TEXT_Fight"
#endif  ID_TEXT_Fight
#ifndef ID_TEXT_FightAddTeam
#define ID_TEXT_FightAddTeam		"ID_TEXT_FightAddTeam"
#endif  ID_TEXT_FightAddTeam
#ifndef ID_TEXT_FightAddFriend
#define ID_TEXT_FightAddFriend		"ID_TEXT_FightAddFriend"
#endif  ID_TEXT_FightAddFriend
#ifndef ID_TEXT_FightAddGang
#define ID_TEXT_FightAddGang		"ID_TEXT_FightAddGang"
#endif  ID_TEXT_FightAddGang
#ifndef ID_TEXT_FightPk
#define ID_TEXT_FightPk		"ID_TEXT_FightPk"
#endif  ID_TEXT_FightPk
#ifndef ID_TEXT_FightBargaining
#define ID_TEXT_FightBargaining		"ID_TEXT_FightBargaining"
#endif  ID_TEXT_FightBargaining
#ifndef ID_TEXT_FightHug
#define ID_TEXT_FightHug		"ID_TEXT_FightHug"
#endif  ID_TEXT_FightHug
#ifndef ID_CHECKBOX_FightAddFriend
#define ID_CHECKBOX_FightAddFriend		"ID_CHECKBOX_FightAddFriend"
#endif  ID_CHECKBOX_FightAddFriend
#ifndef ID_CHECKBOX_FightAddTeam
#define ID_CHECKBOX_FightAddTeam		"ID_CHECKBOX_FightAddTeam"
#endif  ID_CHECKBOX_FightAddTeam
#ifndef ID_CHECKBOX_FightAddGang
#define ID_CHECKBOX_FightAddGang		"ID_CHECKBOX_FightAddGang"
#endif  ID_CHECKBOX_FightAddGang
#ifndef ID_CHECKBOX_FightPk
#define ID_CHECKBOX_FightPk		"ID_CHECKBOX_FightPk"
#endif  ID_CHECKBOX_FightPk
#ifndef ID_CHECKBOX_FightBargaining
#define ID_CHECKBOX_FightBargaining		"ID_CHECKBOX_FightBargaining"
#endif  ID_CHECKBOX_FightBargaining
#ifndef ID_CHECKBOX_FightHug
#define ID_CHECKBOX_FightHug		"ID_CHECKBOX_FightHug"
#endif  ID_CHECKBOX_FightHug
#ifndef ID_PICTURE_Wall2
#define ID_PICTURE_Wall2		"ID_PICTURE_Wall2"
#endif  ID_PICTURE_Wall2
#ifndef ID_TEXT_Rest
#define ID_TEXT_Rest		"ID_TEXT_Rest"
#endif  ID_TEXT_Rest
#ifndef ID_TEXT_AddTeam
#define ID_TEXT_AddTeam		"ID_TEXT_AddTeam"
#endif  ID_TEXT_AddTeam
#ifndef ID_TEXT_AddFriend
#define ID_TEXT_AddFriend		"ID_TEXT_AddFriend"
#endif  ID_TEXT_AddFriend
#ifndef ID_TEXT_AddGang
#define ID_TEXT_AddGang		"ID_TEXT_AddGang"
#endif  ID_TEXT_AddGang
#ifndef ID_TEXT_Pk
#define ID_TEXT_Pk		"ID_TEXT_Pk"
#endif  ID_TEXT_Pk
#ifndef ID_TEXT_Bargaining
#define ID_TEXT_Bargaining		"ID_TEXT_Bargaining"
#endif  ID_TEXT_Bargaining
#ifndef ID_TEXT_Hug
#define ID_TEXT_Hug		"ID_TEXT_Hug"
#endif  ID_TEXT_Hug
#ifndef ID_CHECKBOX_AddFriend
#define ID_CHECKBOX_AddFriend		"ID_CHECKBOX_AddFriend"
#endif  ID_CHECKBOX_AddFriend
#ifndef ID_CHECKBOX_AddTeam
#define ID_CHECKBOX_AddTeam		"ID_CHECKBOX_AddTeam"
#endif  ID_CHECKBOX_AddTeam
#ifndef ID_CHECKBOX_AddGang
#define ID_CHECKBOX_AddGang		"ID_CHECKBOX_AddGang"
#endif  ID_CHECKBOX_AddGang
#ifndef ID_CHECKBOX_Pk
#define ID_CHECKBOX_Pk		"ID_CHECKBOX_Pk"
#endif  ID_CHECKBOX_Pk
#ifndef ID_CHECKBOX_Bargaining
#define ID_CHECKBOX_Bargaining		"ID_CHECKBOX_Bargaining"
#endif  ID_CHECKBOX_Bargaining
#ifndef ID_CHECKBOX_Hug
#define ID_CHECKBOX_Hug		"ID_CHECKBOX_Hug"
#endif  ID_CHECKBOX_Hug
#ifndef ID_CHECKBOX_FightAll
#define ID_CHECKBOX_FightAll		"ID_CHECKBOX_FightAll"
#endif  ID_CHECKBOX_FightAll
#ifndef ID_CHECKBOX_RestAll
#define ID_CHECKBOX_RestAll		"ID_CHECKBOX_RestAll"
#endif  ID_CHECKBOX_RestAll

#include "UiBase.h"
class CUI_ID_FRAME_GameSettingRefuse :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_GameSettingRefuse();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_FightAddFriendOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_FightAddTeamOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_FightAddGangOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_FightPkOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_FightBargainingOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_FightHugOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_AddFriendOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_AddTeamOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_AddGangOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_PkOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_BargainingOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_HugOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
// 	void ID_CHECKBOX_FightAllOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
// 	void ID_CHECKBOX_RestAllOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

    void RefreshUI();

    ControlFrame* GetFrame(){return m_pID_FRAME_GameSettingRefuse;}
protected:
    void CheckAllInFight();
    void CheckAllInRest();

private:
    ControlFrame*	m_pID_FRAME_GameSettingRefuse;
    ControlPicture*	m_pID_PICTURE_Wall1;
    ControlText*	m_pID_TEXT_Fight;
    ControlText*	m_pID_TEXT_FightAddTeam;
    ControlText*	m_pID_TEXT_FightAddFriend;
    ControlText*	m_pID_TEXT_FightAddGang;
    ControlText*	m_pID_TEXT_FightPk;
    ControlText*	m_pID_TEXT_FightBargaining;
    ControlText*	m_pID_TEXT_FightHug;
    ControlCheckBox*	m_pID_CHECKBOX_FightAddFriend;
    ControlCheckBox*	m_pID_CHECKBOX_FightAddTeam;
    ControlCheckBox*	m_pID_CHECKBOX_FightAddGang;
    ControlCheckBox*	m_pID_CHECKBOX_FightPk;
    ControlCheckBox*	m_pID_CHECKBOX_FightBargaining;
    ControlCheckBox*	m_pID_CHECKBOX_FightHug;
    ControlPicture*	m_pID_PICTURE_Wall2;
    ControlText*	m_pID_TEXT_Rest;
    ControlText*	m_pID_TEXT_AddTeam;
    ControlText*	m_pID_TEXT_AddFriend;
    ControlText*	m_pID_TEXT_AddGang;
    ControlText*	m_pID_TEXT_Pk;
    ControlText*	m_pID_TEXT_Bargaining;
    ControlText*	m_pID_TEXT_Hug;
    ControlCheckBox*	m_pID_CHECKBOX_AddFriend;
    ControlCheckBox*	m_pID_CHECKBOX_AddTeam;
    ControlCheckBox*	m_pID_CHECKBOX_AddGang;
    ControlCheckBox*	m_pID_CHECKBOX_Pk;
    ControlCheckBox*	m_pID_CHECKBOX_Bargaining;
    ControlCheckBox*	m_pID_CHECKBOX_Hug;
//     ControlCheckBox*	m_pID_CHECKBOX_FightAll;
//     ControlCheckBox*	m_pID_CHECKBOX_RestAll;
};
extern CUI_ID_FRAME_GameSettingRefuse s_CUI_ID_FRAME_GameSettingRefuse;
