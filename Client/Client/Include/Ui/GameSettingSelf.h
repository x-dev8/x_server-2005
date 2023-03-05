/********************************************************************
	Created by UIEditor.exe
	FileName: D:\My Documents\桌面\gamesetting\GameSettingSelf.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GameSettingSelf
#define ID_FRAME_GameSettingSelf		"ID_FRAME_GameSettingSelf"
#endif  ID_FRAME_GameSettingSelf
#ifndef ID_PICTURE_Wall1
#define ID_PICTURE_Wall1		"ID_PICTURE_Wall1"
#endif  ID_PICTURE_Wall1
#ifndef ID_PICTURE_Wall2
#define ID_PICTURE_Wall2		"ID_PICTURE_Wall2"
#endif  ID_PICTURE_Wall2
#ifndef ID_TEXT_TeamInfo
#define ID_TEXT_TeamInfo		"ID_TEXT_TeamInfo"
#endif  ID_TEXT_TeamInfo
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_TEXT_Tong
#define ID_TEXT_Tong		"ID_TEXT_Tong"
#endif  ID_TEXT_Tong
#ifndef ID_TEXT_Hp
#define ID_TEXT_Hp		"ID_TEXT_Hp"
#endif  ID_TEXT_Hp
#ifndef ID_TEXT_Guild
#define ID_TEXT_Guild		"ID_TEXT_Guild"
#endif  ID_TEXT_Guild
#ifndef ID_TEXT_Mp
#define ID_TEXT_Mp		"ID_TEXT_Mp"
#endif  ID_TEXT_Mp
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title
#ifndef ID_CHECKBOX_Name
#define ID_CHECKBOX_Name		"ID_CHECKBOX_Name"
#endif  ID_CHECKBOX_Name
#ifndef ID_CHECKBOX_TeamHp
#define ID_CHECKBOX_TeamHp		"ID_CHECKBOX_TeamHp"
#endif  ID_CHECKBOX_TeamHp
#ifndef ID_CHECKBOX_Mp
#define ID_CHECKBOX_Mp		"ID_CHECKBOX_Mp"
#endif  ID_CHECKBOX_Mp
#ifndef ID_CHECKBOX_Guild
#define ID_CHECKBOX_Guild		"ID_CHECKBOX_Guild"
#endif  ID_CHECKBOX_Guild
#ifndef ID_CHECKBOX_Tong
#define ID_CHECKBOX_Tong		"ID_CHECKBOX_Tong"
#endif  ID_CHECKBOX_Tong
#ifndef ID_CHECKBOX_Title
#define ID_CHECKBOX_Title		"ID_CHECKBOX_Title"
#endif  ID_CHECKBOX_Title
#ifndef ID_TEXT_Effect
#define ID_TEXT_Effect		"ID_TEXT_Effect"
#endif  ID_TEXT_Effect
#ifndef ID_CHECKBOX_Effect
#define ID_CHECKBOX_Effect		"ID_CHECKBOX_Effect"
#endif  ID_CHECKBOX_Effect
#ifndef ID_CHECKBOX_SelfControl
#define ID_CHECKBOX_SelfControl		"ID_CHECKBOX_SelfControl"
#endif  ID_CHECKBOX_SelfControl

#include "UiBase.h"
class CUI_ID_FRAME_GameSettingSelf :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_GameSettingSelf();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_NameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_TeamHpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_MpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_GuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_TongOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_TitleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_EffectOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
//	void ID_CHECKBOX_SelfControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

    void RefreshUI();

    ControlFrame* GetFrame(){return m_pID_FRAME_GameSettingSelf;}
private:

    void CheckSelfControl();

private:
    ControlFrame*	m_pID_FRAME_GameSettingSelf;
    ControlPicture*	m_pID_PICTURE_Wall1;
    //ControlPicture*	m_pID_PICTURE_Wall2;
    ControlText*	m_pID_TEXT_TeamInfo;
    ControlText*	m_pID_TEXT_Name;
    ControlText*	m_pID_TEXT_Tong;
    ControlText*	m_pID_TEXT_Hp;
    ControlText*	m_pID_TEXT_Guild;
    ControlText*	m_pID_TEXT_Mp;
    ControlText*	m_pID_TEXT_Title;
    ControlCheckBox*	m_pID_CHECKBOX_Name;
    ControlCheckBox*	m_pID_CHECKBOX_TeamHp;
    ControlCheckBox*	m_pID_CHECKBOX_Mp;
    ControlCheckBox*	m_pID_CHECKBOX_Guild;
    ControlCheckBox*	m_pID_CHECKBOX_Tong;
    ControlCheckBox*	m_pID_CHECKBOX_Title;
    ControlText*	m_pID_TEXT_Effect;
    ControlCheckBox*	m_pID_CHECKBOX_Effect;
    //ControlCheckBox*	m_pID_CHECKBOX_SelfControl;
};
extern CUI_ID_FRAME_GameSettingSelf s_CUI_ID_FRAME_GameSettingSelf;
