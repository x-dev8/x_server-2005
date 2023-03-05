/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\家族(8)\家族\FamilyCreate.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_Family_Create
#define ID_FRAME_Family_Create		"ID_FRAME_Family_Create"
#endif  ID_FRAME_Family_Create
#ifndef ID_PICTURE_14498
#define ID_PICTURE_14498		"ID_PICTURE_14498"
#endif  ID_PICTURE_14498
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_BUTTON_CREATE
#define ID_BUTTON_CREATE		"ID_BUTTON_CREATE"
#endif  ID_BUTTON_CREATE
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
#ifndef ID_PICTURE_14642
#define ID_PICTURE_14642		"ID_PICTURE_14642"
#endif  ID_PICTURE_14642
#ifndef ID_COMBOBOX_FORCE
#define ID_COMBOBOX_FORCE		"ID_COMBOBOX_FORCE"
#endif  ID_COMBOBOX_FORCE
#ifndef ID_CHECKBOX_Mo
#define ID_CHECKBOX_Mo		"ID_CHECKBOX_Mo"
#endif  ID_CHECKBOX_Mo
#ifndef ID_CHECKBOX_Hui
#define ID_CHECKBOX_Hui		"ID_CHECKBOX_Hui"
#endif  ID_CHECKBOX_Hui
#ifndef ID_TEXT_8819
#define ID_TEXT_8819		"ID_TEXT_8819"
#endif  ID_TEXT_8819
#ifndef ID_TEXT_8820
#define ID_TEXT_8820		"ID_TEXT_8820"
#endif  ID_TEXT_8820
#ifndef ID_TEXT_20021
#define ID_TEXT_20021		"ID_TEXT_20021"
#endif  ID_TEXT_20021
#ifndef ID_TEXT_23295
#define ID_TEXT_23295		"ID_TEXT_23295"
#endif  ID_TEXT_23295
#ifndef ID_TEXT_27540
#define ID_TEXT_27540		"ID_TEXT_27540"
#endif  ID_TEXT_27540
#ifndef ID_TEXT_17832
#define ID_TEXT_17832		"ID_TEXT_17832"
#endif  ID_TEXT_17832
#ifndef ID_BUTTON_close
#define ID_BUTTON_close		"ID_BUTTON_close"
#endif  ID_BUTTON_close
#ifndef ID_PICTURE_FrameHead
#define ID_PICTURE_FrameHead		"ID_PICTURE_FrameHead"
#endif  ID_PICTURE_FrameHead
#ifndef ID_TEXT_Tip
#define ID_TEXT_Tip		"ID_TEXT_Tip"
#endif  ID_TEXT_Tip
#ifndef ID_TEXT_BangPaiZongZhi
#define ID_TEXT_BangPaiZongZhi		"ID_TEXT_BangPaiZongZhi"
#endif  ID_TEXT_BangPaiZongZhi
#ifndef ID_EDIT_Creed
#define ID_EDIT_Creed		"ID_EDIT_Creed"
#endif  ID_EDIT_Creed

#include "UIBase.h"

class CUI_ID_FRAME_Family_Create : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_Family_Create();
	 ControlFrame*	m_pID_FRAME_Family_Create;
	 ControlPicture*	m_pID_PICTURE_14498;
	 ControlButton*	m_pID_BUTTON_help;
	 ControlButton*	m_pID_BUTTON_CREATE;
	 ControlPicture*	m_pID_PICTURE_14643;
	 ControlPicture*	m_pID_PICTURE_14644;
	 ControlPicture*	m_pID_PICTURE_4178;
	 ControlEdit*	m_pID_EDIT_GUILDNAME;
	 ControlPicture*	m_pID_PICTURE_14642;
	 ControlComboBox*	m_pID_COMBOBOX_FORCE;
	 ControlCheckBox*	m_pID_CHECKBOX_Mo;
	 ControlCheckBox*	m_pID_CHECKBOX_Hui;
	 ControlText*	m_pID_TEXT_8819;
	 ControlText*	m_pID_TEXT_8820;
	 ControlText*	m_pID_TEXT_20021;
	 ControlText*	m_pID_TEXT_23295;
	 ControlText*	m_pID_TEXT_27540;
	 ControlText*	m_pID_TEXT_17832;
	 ControlButton*	m_pID_BUTTON_close;
	 ControlPicture*	m_pID_PICTURE_FrameHead;
	 ControlText*	m_pID_TEXT_Tip;
	 ControlText*	m_pID_TEXT_BangPaiZongZhi;
	 ControlEdit*	m_pID_EDIT_Creed;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CREATEOnButtonClick( ControlObject* pSender );
	void ID_EDIT_GUILDNAMEOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_COMBOBOX_FORCEOnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_CHECKBOX_MoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_HuiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_closeOnButtonClick( ControlObject* pSender );
	void ID_EDIT_CreedOnEditEnter( ControlObject* pSender, const char* szData );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视


public:
	bool    EditInputIsVisable();

	//游戏逻辑相关
public:
	void	RequestCreateFamily();		//请求创建家族
	void	SetFamilyName( const char* name );
	void	SetFamilyAim( const char* aim );
	void	SetFamilyTotem( unsigned char totem );
	void	ResetData();
private:	

	std::string		m_Name;				// 家族名字
	std::string		m_Aim;				// 家族宗旨
	unsigned char	m_nTotem;				// 家族图腾
};
extern CUI_ID_FRAME_Family_Create s_CUI_ID_FRAME_Family_Create;
