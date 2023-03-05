/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\桌面\角色资料和其他信息界面\角色资料和其他信息界面\OtherInfo.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_OtherInfo
#define ID_FRAME_OtherInfo		"ID_FRAME_OtherInfo"
#endif  ID_FRAME_OtherInfo
#ifndef ID_EDIT_MSN
#define ID_EDIT_MSN		"ID_EDIT_MSN"
#endif  ID_EDIT_MSN
#ifndef ID_TEXT_ID
#define ID_TEXT_ID		"ID_TEXT_ID"
#endif  ID_TEXT_ID
#ifndef ID_TEXT_Family
#define ID_TEXT_Family		"ID_TEXT_Family"
#endif  ID_TEXT_Family
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_TEXT_Gang
#define ID_TEXT_Gang		"ID_TEXT_Gang"
#endif  ID_TEXT_Gang
#ifndef ID_TEXT_Spouse
#define ID_TEXT_Spouse		"ID_TEXT_Spouse"
#endif  ID_TEXT_Spouse
#ifndef ID_TEXT_BangGong
#define ID_TEXT_BangGong		"ID_TEXT_BangGong"
#endif  ID_TEXT_BangGong
#ifndef ID_TEXT_WeiWang
#define ID_TEXT_WeiWang		"ID_TEXT_WeiWang"
#endif  ID_TEXT_WeiWang
#ifndef ID_TEXT_TianFu
#define ID_TEXT_TianFu		"ID_TEXT_TianFu"
#endif  ID_TEXT_TianFu
#ifndef ID_TEXT_RongYu
#define ID_TEXT_RongYu		"ID_TEXT_RongYu"
#endif  ID_TEXT_RongYu
#ifndef ID_TEXT_PK
#define ID_TEXT_PK		"ID_TEXT_PK"
#endif  ID_TEXT_PK
#ifndef ID_TEXT_BattlefieldLevel
#define ID_TEXT_BattlefieldLevel		"ID_TEXT_BattlefieldLevel"
#endif  ID_TEXT_BattlefieldLevel
#ifndef ID_TEXT_BattlefieldIntegral
#define ID_TEXT_BattlefieldIntegral		"ID_TEXT_BattlefieldIntegral"
#endif  ID_TEXT_BattlefieldIntegral
#ifndef ID_TEXT_SurplusMaster
#define ID_TEXT_SurplusMaster		"ID_TEXT_SurplusMaster"
#endif  ID_TEXT_SurplusMaster
#ifndef ID_TEXT_AllMaster
#define ID_TEXT_AllMaster		"ID_TEXT_AllMaster"
#endif  ID_TEXT_AllMaster
#ifndef ID_TEXT_SurplusApprentice
#define ID_TEXT_SurplusApprentice		"ID_TEXT_SurplusApprentice"
#endif  ID_TEXT_SurplusApprentice
#ifndef ID_TEXT_AllApprentice
#define ID_TEXT_AllApprentice		"ID_TEXT_AllApprentice"
#endif  ID_TEXT_AllApprentice
#ifndef ID_TEXT_SurplusDoubleEXP
#define ID_TEXT_SurplusDoubleEXP		"ID_TEXT_SurplusDoubleEXP"
#endif  ID_TEXT_SurplusDoubleEXP
#ifndef ID_TEXT_PossessDoubleEXP
#define ID_TEXT_PossessDoubleEXP		"ID_TEXT_PossessDoubleEXP"
#endif  ID_TEXT_PossessDoubleEXP
#ifndef ID_TEXT_EspecialMoney
#define ID_TEXT_EspecialMoney		"ID_TEXT_EspecialMoney"
#endif  ID_TEXT_EspecialMoney
#ifndef ID_TEXT_MONEY
#define ID_TEXT_MONEY		"ID_TEXT_MONEY"
#endif  ID_TEXT_MONEY
#ifndef ID_TEXT_Yingyuanbao
#define ID_TEXT_Yingyuanbao		"ID_TEXT_Yingyuanbao"
#endif  ID_TEXT_Yingyuanbao
#ifndef ID_TEXT_Jinyuanbao
#define ID_TEXT_Jinyuanbao		"ID_TEXT_Jinyuanbao"
#endif  ID_TEXT_Jinyuanbao

#ifndef ID_TEXT_WorldKillPlayer
#define ID_TEXT_WorldKillPlayer		"ID_TEXT_WorldKillPlayer"
#endif  ID_TEXT_WorldKillPlayer
#ifndef ID_TEXT_WeekKillPlayer
#define ID_TEXT_WeekKillPlayer		"ID_TEXT_WeekKillPlayer"
#endif  ID_TEXT_WeekKillPlayer


//#ifndef ID_TEXT_NowSkillExp
//#define ID_TEXT_NowSkillExp		"ID_TEXT_NowSkillExp"
//#endif	ID_TEXT_NowSkillExp

#ifndef ID_TEXT_Exploit
#define ID_TEXT_Exploit			"ID_TEXT_Exploit"
#endif	ID_TEXT_Exploit

#ifndef ID_TEXT_Country
#define ID_TEXT_Country		"ID_TEXT_Country"
#endif  ID_TEXT_Country
#ifndef ID_TEXT_Position
#define ID_TEXT_Position		"ID_TEXT_Position"
#endif  ID_TEXT_Position

class CUI_ID_FRAME_OtherInfo :public CUIBase
{
	// Member
private:	

	 ControlFrame*	m_pID_FRAME_OtherInfo;
	 ControlEdit*	m_pID_EDIT_MSN;
	 ControlText*	m_pID_TEXT_ID;
	 ControlText*	m_pID_TEXT_Family;
	 ControlText*	m_pID_TEXT_Name;
	 ControlText*	m_pID_TEXT_Gang;
	 ControlText*	m_pID_TEXT_Spouse;
	 ControlText*	m_pID_TEXT_BangGong;
	 ControlText*	m_pID_TEXT_WeiWang;
	 ControlText*	m_pID_TEXT_TianFu;
	 ControlText*	m_pID_TEXT_RongYu;
	 ControlText*	m_pID_TEXT_PK;
	 ControlText*	m_pID_TEXT_BattlefieldLevel;
	 ControlText*	m_pID_TEXT_BattlefieldIntegral;
	 ControlText*	m_pID_TEXT_SurplusMaster;
	 ControlText*	m_pID_TEXT_AllMaster;
	 ControlText*	m_pID_TEXT_SurplusApprentice;
	 ControlText*	m_pID_TEXT_AllApprentice;
	 ControlText*	m_pID_TEXT_SurplusDoubleEXP;
	 ControlText*	m_pID_TEXT_PossessDoubleEXP;
	 ControlText*	m_pID_TEXT_EspecialMoney;
	 ControlText*	m_pID_TEXT_MONEY;
	 ControlText*	m_pID_TEXT_Yingyuanbao;
	 ControlText*	m_pID_TEXT_Jinyuanbao;
	 //ControlText*	m_pID_TEXT_NowSkillExp;
	 ControlText*	m_pID_TEXT_Exploit;

	 ControlText*	m_pID_TEXT_WorldKillPlayer;
	 ControlText*	m_pID_TEXT_WeekKillPlayer;
	 ControlText*	m_pID_TEXT_Country;
	 ControlText*	m_pID_TEXT_Position;

public:	
	// Frame
	CUI_ID_FRAME_OtherInfo();
	~CUI_ID_FRAME_OtherInfo();
	void ResetMember();
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_EDIT_MSNOnEditEnter( ControlObject* pSender, const char* szData );

	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视
	void RefreshBaseInfo();
	void RefreshMoney();
	void SetKillPlayerSum(uint32 WorldNum,uint32 WeekNum);
	void SetCountryAndPosition();
private:	
};
extern CUI_ID_FRAME_OtherInfo s_CUI_ID_FRAME_OtherInfo;
