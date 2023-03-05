/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Work\Run\Client\UI\Guild_Create.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "Guild_Pic.h"

#ifndef ID_FRAME_GUILD_CREATE
#define ID_FRAME_GUILD_CREATE		"ID_FRAME_GUILD_CREATE"
#endif  ID_FRAME_GUILD_CREATE
#ifndef ID_PICTURE_14498
#define ID_PICTURE_14498		"ID_PICTURE_14498"
#endif  ID_PICTURE_14498
#ifndef ID_BUTTON_close
#define ID_BUTTON_close		"ID_BUTTON_close"
#endif  ID_BUTTON_close
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_BUTTON_CREATE
#define ID_BUTTON_CREATE		"ID_BUTTON_CREATE"
#endif  ID_BUTTON_CREATE
#ifndef ID_PICTURE_14642
#define ID_PICTURE_14642		"ID_PICTURE_14642"
#endif  ID_PICTURE_14642
#ifndef ID_PICTURE_14643
#define ID_PICTURE_14643		"ID_PICTURE_14643"
#endif  ID_PICTURE_14643
#ifndef ID_PICTURE_14644
#define ID_PICTURE_14644		"ID_PICTURE_14644"
#endif  ID_PICTURE_14644
#ifndef ID_PICTURE_4178
#define ID_PICTURE_4178		"ID_PICTURE_4178"
#endif  ID_PICTURE_4178
#ifndef ID_EDIT_GUILDNAME
#define ID_EDIT_GUILDNAME		"ID_EDIT_GUILDNAME"
#endif  ID_EDIT_GUILDNAME
#ifndef ID_PICTURE_4179
#define ID_PICTURE_4179		"ID_PICTURE_4179"
#endif  ID_PICTURE_4179
#ifndef ID_COMBOBOX_FORCE
#define ID_COMBOBOX_FORCE		"ID_COMBOBOX_FORCE"
#endif  ID_COMBOBOX_FORCE
#ifndef ID_CHECKBOX_Hui
#define ID_CHECKBOX_Hui		"ID_CHECKBOX_Hui"
#endif  ID_CHECKBOX_Hui
#ifndef ID_CHECKBOX_Mo
#define ID_CHECKBOX_Mo		"ID_CHECKBOX_Mo"
#endif  ID_CHECKBOX_Mo 
#ifndef ID_EDIT_Creed
#define ID_EDIT_Creed		"ID_EDIT_Creed"
#endif  ID_EDIT_Creed

#include "UiBase.h"
class CUI_ID_FRAME_GUILD_CREATE :public CUIBase
{
	// SGuildMember
public:
    CUI_ID_FRAME_GUILD_CREATE();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_closeOnButtonClick( ControlObject* pSender );
	//bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CREATEOnButtonClick( ControlObject* pSender );
	void ID_EDIT_GUILDNAMEOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_GUILD_CREEDOnEditEnter(ControlObject* pSender, const char* szData);
	void ID_COMBOBOX_FORCEOnComboBoxChange( ControlObject* pSender, const char* szData );
    void ID_CHECKBOX_MoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked );
    void ID_CHECKBOX_HuiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

    bool EditInputIsVisable();

    int GetNpcID(){return m_nNpcID;}
    void  SetNpcId(int nId){m_nNpcID = nId;}

private:
    ControlFrame*	m_pID_FRAME_GUILD_CREATE;
    ControlPicture*	m_pID_PICTURE_14498;
    ControlButton*	m_pID_BUTTON_close;
    //ControlButton*	m_pID_BUTTON_help;
    ControlButton*	m_pID_BUTTON_CREATE;
    ControlPicture*	m_pID_PICTURE_14642;
    ControlPicture*	m_pID_PICTURE_14643;
    ControlPicture*	m_pID_PICTURE_14644;
    ControlPicture*	m_pID_PICTURE_4178;
    ControlEdit*	m_pID_EDIT_GUILDNAME;
    //ControlPicture*	m_pID_PICTURE_4179;
    ControlComboBox*	m_pID_COMBOBOX_FORCE;

    ControlCheckBox* m_pID_CHECKBOX_Mo;
    ControlCheckBox* m_pID_CHECKBOX_Hui;
    int m_nNpcID;

	ControlEdit*	m_pID_EDIT_Creed;
};

extern CUI_ID_FRAME_GUILD_CREATE s_CUI_ID_FRAME_GUILD_CREATE;
