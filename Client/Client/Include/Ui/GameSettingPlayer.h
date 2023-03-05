/********************************************************************
	Created by UIEditor.exe
	FileName: D:\My Documents\桌面\gamesetting\GameSettingPlayer.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GameSettingPlayer
#define ID_FRAME_GameSettingPlayer		"ID_FRAME_GameSettingPlayer"
#endif  ID_FRAME_GameSettingPlayer
#ifndef ID_PICTURE_Wall1
#define ID_PICTURE_Wall1		"ID_PICTURE_Wall1"
#endif  ID_PICTURE_Wall1
#ifndef ID_PICTURE_Wall3
#define ID_PICTURE_Wall3		"ID_PICTURE_Wall3"
#endif  ID_PICTURE_Wall3
#ifndef ID_PICTURE_Wall2
#define ID_PICTURE_Wall2		"ID_PICTURE_Wall2"
#endif  ID_PICTURE_Wall2
#ifndef ID_PICTURE_Wall4
#define ID_PICTURE_Wall4		"ID_PICTURE_Wall4"
#endif  ID_PICTURE_Wall4
#ifndef ID_TEXT_TeamInfo
#define ID_TEXT_TeamInfo		"ID_TEXT_TeamInfo"
#endif  ID_TEXT_TeamInfo
#ifndef ID_TEXT_TeamName
#define ID_TEXT_TeamName		"ID_TEXT_TeamName"
#endif  ID_TEXT_TeamName
#ifndef ID_TEXT_TeamTong
#define ID_TEXT_TeamTong		"ID_TEXT_TeamTong"
#endif  ID_TEXT_TeamTong
#ifndef ID_TEXT_TeamHp
#define ID_TEXT_TeamHp		"ID_TEXT_TeamHp"
#endif  ID_TEXT_TeamHp
#ifndef ID_TEXT_TeamGuild
#define ID_TEXT_TeamGuild		"ID_TEXT_TeamGuild"
#endif  ID_TEXT_TeamGuild
#ifndef ID_TEXT_TeamTitle
#define ID_TEXT_TeamTitle		"ID_TEXT_TeamTitle"
#endif  ID_TEXT_TeamTitle
#ifndef ID_TEXT_OtherInfo
#define ID_TEXT_OtherInfo		"ID_TEXT_OtherInfo"
#endif  ID_TEXT_OtherInfo
#ifndef ID_TEXT_OtherName
#define ID_TEXT_OtherName		"ID_TEXT_OtherName"
#endif  ID_TEXT_OtherName
#ifndef ID_TEXT_OtherHp
#define ID_TEXT_OtherHp		"ID_TEXT_OtherHp"
#endif  ID_TEXT_OtherHp
#ifndef ID_TEXT_OtherTitle
#define ID_TEXT_OtherTitle		"ID_TEXT_OtherTitle"
#endif  ID_TEXT_OtherTitle
#ifndef ID_TEXT_OtherGroup
#define ID_TEXT_OtherGroup		"ID_TEXT_OtherGroup"
#endif  ID_TEXT_OtherGroup
#ifndef ID_TEXT_OtherTong
#define ID_TEXT_OtherTong		"ID_TEXT_OtherTong"
#endif  ID_TEXT_OtherTong
#ifndef ID_CHECKBOX_TeamName
#define ID_CHECKBOX_TeamName		"ID_CHECKBOX_TeamName"
#endif  ID_CHECKBOX_TeamName
#ifndef ID_CHECKBOX_TeamHp
#define ID_CHECKBOX_TeamHp		"ID_CHECKBOX_TeamHp"
#endif  ID_CHECKBOX_TeamHp
#ifndef ID_CHECKBOX_TeamTitle
#define ID_CHECKBOX_TeamTitle		"ID_CHECKBOX_TeamTitle"
#endif  ID_CHECKBOX_TeamTitle
#ifndef ID_CHECKBOX_TeamGuild
#define ID_CHECKBOX_TeamGuild		"ID_CHECKBOX_TeamGuild"
#endif  ID_CHECKBOX_TeamGuild
#ifndef ID_CHECKBOX_TeamTong
#define ID_CHECKBOX_TeamTong		"ID_CHECKBOX_TeamTong"
#endif  ID_CHECKBOX_TeamTong
#ifndef ID_CHECKBOX_OtherName
#define ID_CHECKBOX_OtherName		"ID_CHECKBOX_OtherName"
#endif  ID_CHECKBOX_OtherName
#ifndef ID_CHECKBOX_OtherHp
#define ID_CHECKBOX_OtherHp		"ID_CHECKBOX_OtherHp"
#endif  ID_CHECKBOX_OtherHp
#ifndef ID_CHECKBOX_OtherTitle
#define ID_CHECKBOX_OtherTitle		"ID_CHECKBOX_OtherTitle"
#endif  ID_CHECKBOX_OtherTitle
#ifndef ID_CHECKBOX_OtherGroup
#define ID_CHECKBOX_OtherGroup		"ID_CHECKBOX_OtherGroup"
#endif  ID_CHECKBOX_OtherGroup
#ifndef ID_CHECKBOX_OtherTong
#define ID_CHECKBOX_OtherTong		"ID_CHECKBOX_OtherTong"
#endif  ID_CHECKBOX_OtherTong
#ifndef ID_CHECKBOX_OtherEffect
#define ID_CHECKBOX_OtherEffect		"ID_CHECKBOX_OtherEffect"
#endif  ID_CHECKBOX_OtherEffect
#ifndef ID_CHECKBOX_OtherModel
#define ID_CHECKBOX_OtherModel		"ID_CHECKBOX_OtherModel"
#endif  ID_CHECKBOX_OtherModel
#ifndef ID_CHECKBOX_TeamEffect
#define ID_CHECKBOX_TeamEffect		"ID_CHECKBOX_TeamEffect"
#endif  ID_CHECKBOX_TeamEffect
#ifndef ID_CHECKBOX_TeamModel
#define ID_CHECKBOX_TeamModel		"ID_CHECKBOX_TeamModel"
#endif  ID_CHECKBOX_TeamModel
#ifndef ID_TEXT_OtherEffect
#define ID_TEXT_OtherEffect		"ID_TEXT_OtherEffect"
#endif  ID_TEXT_OtherEffect
#ifndef ID_TEXT_OtherModel
#define ID_TEXT_OtherModel		"ID_TEXT_OtherModel"
#endif  ID_TEXT_OtherModel
#ifndef ID_TEXT_TeamEffect
#define ID_TEXT_TeamEffect		"ID_TEXT_TeamEffect"
#endif  ID_TEXT_TeamEffect
#ifndef ID_TEXT_TeamModel
#define ID_TEXT_TeamModel		"ID_TEXT_TeamModel"
#endif  ID_TEXT_TeamModel
#ifndef ID_CHECKBOX_TeamInfoControl
#define ID_CHECKBOX_TeamInfoControl		"ID_CHECKBOX_TeamInfoControl"
#endif  ID_CHECKBOX_TeamInfoControl
#ifndef ID_CHECKBOX_OtherInfoControl
#define ID_CHECKBOX_OtherInfoControl		"ID_CHECKBOX_OtherInfoControl"
#endif  ID_CHECKBOX_OtherInfoControl

#include "UiBase.h"
class CUI_ID_FRAME_GameSettingPlayer :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_GameSettingPlayer();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_TeamNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_TeamHpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_TeamTitleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_TeamGuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_TeamTongOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_OtherNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_OtherHpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_OtherTitleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_OtherGroupOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_OtherTongOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_OtherEffectOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_OtherModelOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_TeamEffectOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_TeamModelOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
// 	void ID_CHECKBOX_TeamInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
// 	void ID_CHECKBOX_OtherInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	void RefreshUI();
    virtual bool _IsVisable();			// 是否可见
	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
    virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


    ControlFrame* GetFrame(){return m_pID_FRAME_GameSettingPlayer;}

private:
    void CheckTeamInfoControl();
    void CheckOtherInfoControl();

private:
    ControlFrame*	m_pID_FRAME_GameSettingPlayer;
    ControlPicture*	m_pID_PICTURE_Wall1;
    ControlPicture*	m_pID_PICTURE_Wall3;
//     ControlPicture*	m_pID_PICTURE_Wall2;
//     ControlPicture*	m_pID_PICTURE_Wall4;
    ControlText*	m_pID_TEXT_TeamInfo;
    ControlText*	m_pID_TEXT_TeamName;
    ControlText*	m_pID_TEXT_TeamTong;
    ControlText*	m_pID_TEXT_TeamHp;
    ControlText*	m_pID_TEXT_TeamGuild;
    ControlText*	m_pID_TEXT_TeamTitle;
    ControlText*	m_pID_TEXT_OtherInfo;
    ControlText*	m_pID_TEXT_OtherName;
    ControlText*	m_pID_TEXT_OtherHp;
    ControlText*	m_pID_TEXT_OtherTitle;
    ControlText*	m_pID_TEXT_OtherGroup;
    ControlText*	m_pID_TEXT_OtherTong;
    ControlCheckBox*	m_pID_CHECKBOX_TeamName;
    ControlCheckBox*	m_pID_CHECKBOX_TeamHp;
    ControlCheckBox*	m_pID_CHECKBOX_TeamTitle;
    ControlCheckBox*	m_pID_CHECKBOX_TeamGuild;
    ControlCheckBox*	m_pID_CHECKBOX_TeamTong;
    ControlCheckBox*	m_pID_CHECKBOX_OtherName;
    ControlCheckBox*	m_pID_CHECKBOX_OtherHp;
    ControlCheckBox*	m_pID_CHECKBOX_OtherTitle;
    ControlCheckBox*	m_pID_CHECKBOX_OtherGroup;
    ControlCheckBox*	m_pID_CHECKBOX_OtherTong;
    ControlCheckBox*	m_pID_CHECKBOX_OtherEffect;
    ControlCheckBox*	m_pID_CHECKBOX_OtherModel;
    ControlCheckBox*	m_pID_CHECKBOX_TeamEffect;
    ControlCheckBox*	m_pID_CHECKBOX_TeamModel;
    ControlText*	m_pID_TEXT_OtherEffect;
    ControlText*	m_pID_TEXT_OtherModel;
    ControlText*	m_pID_TEXT_TeamEffect;
    ControlText*	m_pID_TEXT_TeamModel;
//     ControlCheckBox*	m_pID_CHECKBOX_TeamInfoControl;
//     ControlCheckBox*	m_pID_CHECKBOX_OtherInfoControl;
};
extern CUI_ID_FRAME_GameSettingPlayer s_CUI_ID_FRAME_GameSettingPlayer;
