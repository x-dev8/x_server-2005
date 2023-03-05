/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\桌面\角色资料和其他信息界面\角色资料和其他信息界面\SelfInfo.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_SelfInfo
#define ID_FRAME_SelfInfo		"ID_FRAME_SelfInfo"
#endif  ID_FRAME_SelfInfo
#ifndef ID_BUTTON_Save
#define ID_BUTTON_Save		"ID_BUTTON_Save"
#endif  ID_BUTTON_Save
#ifndef ID_COMBOBOX_Sex
#define ID_COMBOBOX_Sex		"ID_COMBOBOX_Sex"
#endif  ID_COMBOBOX_Sex
#ifndef ID_EDIT_Age
#define ID_EDIT_Age		"ID_EDIT_Age"
#endif  ID_EDIT_Age
#ifndef ID_EDIT_City
#define ID_EDIT_City		"ID_EDIT_City"
#endif  ID_EDIT_City
#ifndef ID_EDIT_Job
#define ID_EDIT_Job		"ID_EDIT_Job"
#endif  ID_EDIT_Job
#ifndef ID_EDIT_QQ
#define ID_EDIT_QQ		"ID_EDIT_QQ"
#endif  ID_EDIT_QQ
#ifndef ID_EDIT_MSN
#define ID_EDIT_MSN		"ID_EDIT_MSN"
#endif  ID_EDIT_MSN
#ifndef ID_EDIT_Desc
#define ID_EDIT_Desc		"ID_EDIT_Desc"
#endif  ID_EDIT_Desc
#ifndef ID_CHECKBOX_Public
#define ID_CHECKBOX_Public		"ID_CHECKBOX_Public"
#endif  ID_CHECKBOX_Public
#ifndef ID_EDIT_Like
#define ID_EDIT_Like		"ID_EDIT_Like"
#endif  ID_EDIT_Like
#ifndef ID_EDIT_Mail
#define ID_EDIT_Mail		"ID_EDIT_Mail"
#endif  ID_EDIT_Mail
#ifndef ID_EDIT_Http
#define ID_EDIT_Http		"ID_EDIT_Http"
#endif  ID_EDIT_Http
#ifndef ID_EDIT_NickName
#define ID_EDIT_NickName		"ID_EDIT_NickName"
#endif  ID_EDIT_NickName
#ifndef ID_CHECKBOX_FriendOnly
#define ID_CHECKBOX_FriendOnly		"ID_CHECKBOX_FriendOnly"
#endif  ID_CHECKBOX_FriendOnly
#ifndef ID_CHECKBOX_Private
#define ID_CHECKBOX_Private		"ID_CHECKBOX_Private"
#endif  ID_CHECKBOX_Private
#ifndef ID_COMBOBOX_BirthMonth
#define ID_COMBOBOX_BirthMonth		"ID_COMBOBOX_BirthMonth"
#endif  ID_COMBOBOX_BirthMonth
#ifndef ID_COMBOBOX_BirthDay
#define ID_COMBOBOX_BirthDay		"ID_COMBOBOX_BirthDay"
#endif  ID_COMBOBOX_BirthDay
#ifndef ID_COMBOBOX_Province
#define ID_COMBOBOX_Province		"ID_COMBOBOX_Province"
#endif  ID_COMBOBOX_Province
#ifndef ID_COMBOBOX_Constellation
#define ID_COMBOBOX_Constellation		"ID_COMBOBOX_Constellation"
#endif  ID_COMBOBOX_Constellation
#ifndef ID_COMBOBOX_Animal
#define ID_COMBOBOX_Animal		"ID_COMBOBOX_Animal"
#endif  ID_COMBOBOX_Animal
#ifndef ID_PICTURE_Image01
#define ID_PICTURE_Image01		"ID_PICTURE_Image01"
#endif  ID_PICTURE_Image01
#ifndef ID_PICTURE_Image02
#define ID_PICTURE_Image02		"ID_PICTURE_Image02"
#endif  ID_PICTURE_Image02

class CUI_ID_FRAME_SelfInfo : public CUIBase
{
	// Member
private:	
	 ControlFrame*	m_pID_FRAME_SelfInfo;
	 ControlButton*	m_pID_BUTTON_Save;
	 ControlComboBox*	m_pID_COMBOBOX_Sex;
	 ControlEdit*	m_pID_EDIT_Age;
	 ControlEdit*	m_pID_EDIT_City;
	 ControlEdit*	m_pID_EDIT_Job;
	 ControlEdit*	m_pID_EDIT_QQ;
	 ControlEdit*	m_pID_EDIT_MSN;
	 ControlEdit*	m_pID_EDIT_Desc;
	 ControlCheckBox*	m_pID_CHECKBOX_Public;
	 ControlEdit*	m_pID_EDIT_Like;
	 ControlEdit*	m_pID_EDIT_Mail;
	 ControlEdit*	m_pID_EDIT_Http;
	 ControlEdit*	m_pID_EDIT_NickName;
	 ControlCheckBox*	m_pID_CHECKBOX_FriendOnly;
	 ControlCheckBox*	m_pID_CHECKBOX_Private;
	 ControlComboBox*	m_pID_COMBOBOX_BirthMonth;
	 ControlComboBox*	m_pID_COMBOBOX_BirthDay;
	 ControlComboBox*	m_pID_COMBOBOX_Province;
	 ControlComboBox*	m_pID_COMBOBOX_Constellation;
	 ControlComboBox*	m_pID_COMBOBOX_Animal;
	 ControlPicture*	m_pID_PICTURE_Image01;
	 ControlPicture*	m_pID_PICTURE_Image02;

public:	
	// Frame
	CUI_ID_FRAME_SelfInfo();
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_SaveOnButtonClick( ControlObject* pSender );
	void ID_COMBOBOX_SexOnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_EDIT_AgeOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_CityOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_JobOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_QQOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_MSNOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_DescOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_CHECKBOX_PublicOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_EDIT_LikeOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_MailOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_HttpOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_NickNameOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_CHECKBOX_FriendOnlyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_PrivateOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_COMBOBOX_BirthMonthOnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_COMBOBOX_BirthDayOnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_COMBOBOX_ProvinceOnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_COMBOBOX_ConstellationOnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_COMBOBOX_AnimalOnComboBoxChange( ControlObject* pSender, const char* szData );

	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视
	void InitSelfInfo();
	void RefreshInfo();
private:	
	struct Selfinfo
	{
		Selfinfo() { memset(this,0,sizeof(Selfinfo));}
		const char* m_name;
		int				 m_qq;
		int				m_sex;
		int				m_month;
		int				m_day;
		int				m_age;
		int				m_province;
		char*			m_city;
		char*			m_Job;
		char*           m_mail;
		char*           m_http;
		char*			m_like;
		char*			m_desc;
		int			m_constellation; //星座
		int			m_Animal;            //生肖
		unsigned int m_private;		  //资料公开程度
	};
	Selfinfo  m_selfinfo;   //个人信息资料

public:
	uint8 GetDayCount(uint8 m_month);
	void InitMonthComboBox(ControlComboBox* pBox);
	void InitDayComboBox(ControlComboBox *pBox,uint8 m_month);

	void InitSexComboBox(ControlComboBox *pBox);
	void InitAnimalComboBox(ControlComboBox *pBox);
	void InitCityComboBox(ControlComboBox *pBox);
	void InitConstellationComboBox(ControlComboBox *pBox);
	bool EditInputIsVisable();
};
extern CUI_ID_FRAME_SelfInfo s_CUI_ID_FRAME_SelfInfo;
