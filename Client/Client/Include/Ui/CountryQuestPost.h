/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\国家界面\CountryQuestPost.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "Country.h"
#include "CountryBaseInfo.h"
#ifndef ID_FRAME_CountryQuestPost
#define ID_FRAME_CountryQuestPost		"ID_FRAME_CountryQuestPost"
#endif  ID_FRAME_CountryQuestPost
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_TEXT_Command1
#define ID_TEXT_Command1		"ID_TEXT_Command1"
#endif  ID_TEXT_Command1
#ifndef ID_TEXT_Command2
#define ID_TEXT_Command2		"ID_TEXT_Command2"
#endif  ID_TEXT_Command2
#ifndef ID_TEXT_Command3
#define ID_TEXT_Command3		"ID_TEXT_Command3"
#endif  ID_TEXT_Command3
#ifndef ID_TEXT_Command4
#define ID_TEXT_Command4		"ID_TEXT_Command4"
#endif  ID_TEXT_Command4
#ifndef ID_TEXT_Commander1
#define ID_TEXT_Commander1		"ID_TEXT_Commander1"
#endif  ID_TEXT_Commander1
#ifndef ID_TEXT_Commander2
#define ID_TEXT_Commander2		"ID_TEXT_Commander2"
#endif  ID_TEXT_Commander2
#ifndef ID_TEXT_Commander3
#define ID_TEXT_Commander3		"ID_TEXT_Commander3"
#endif  ID_TEXT_Commander3
#ifndef ID_TEXT_Commander4
#define ID_TEXT_Commander4		"ID_TEXT_Commander4"
#endif  ID_TEXT_Commander4
#ifndef ID_TEXT_QuestDesc1
#define ID_TEXT_QuestDesc1		"ID_TEXT_QuestDesc1"
#endif  ID_TEXT_QuestDesc1
#ifndef ID_TEXT_QuestDesc2
#define ID_TEXT_QuestDesc2		"ID_TEXT_QuestDesc2"
#endif  ID_TEXT_QuestDesc2
#ifndef ID_TEXT_QuestDesc3
#define ID_TEXT_QuestDesc3		"ID_TEXT_QuestDesc3"
#endif  ID_TEXT_QuestDesc3
#ifndef ID_TEXT_QuestDesc4
#define ID_TEXT_QuestDesc4		"ID_TEXT_QuestDesc4"
#endif  ID_TEXT_QuestDesc4
#ifndef ID_BUTTON_Post1
#define ID_BUTTON_Post1		"ID_BUTTON_Post1"
#endif  ID_BUTTON_Post1
#ifndef ID_BUTTON_Post2
#define ID_BUTTON_Post2		"ID_BUTTON_Post2"
#endif  ID_BUTTON_Post2
#ifndef ID_BUTTON_Post3
#define ID_BUTTON_Post3		"ID_BUTTON_Post3"
#endif  ID_BUTTON_Post3
#ifndef ID_BUTTON_Post4
#define ID_BUTTON_Post4		"ID_BUTTON_Post4"
#endif  ID_BUTTON_Post4
#ifndef ID_BUTTON_TurnLeft
#define ID_BUTTON_TurnLeft		"ID_BUTTON_TurnLeft"
#endif  ID_BUTTON_TurnLeft
#ifndef ID_BUTTON_TurnRight
#define ID_BUTTON_TurnRight		"ID_BUTTON_TurnRight"
#endif  ID_BUTTON_TurnRight
#ifndef ID_TEXT_Page
#define ID_TEXT_Page		"ID_TEXT_Page"
#endif  ID_TEXT_Page


#include "UiBase.h"
class CUI_ID_FRAME_CountryQuestPost :public CUIBase
{
public:
	struct CountryTask
	{
		uint8 taskType;
		int nKeepTime;
		int requireRight;
		std::string strTaskName;
		std::string strPromulgator;
		std::string strDescribe;
	};
	
private:
	// Member
	 ControlFrame*	    m_pID_FRAME_CountryQuestPost;
	 ControlButton*	    m_pID_BUTTON_Cancel;
	 ControlText*	m_pID_TEXT_Command1;
	 ControlText*	m_pID_TEXT_Command2;
	 ControlText*	m_pID_TEXT_Command3;
	 ControlText*	m_pID_TEXT_Command4;
	 ControlText*	m_pID_TEXT_Commander1;
	 ControlText*	m_pID_TEXT_Commander2;
	 ControlText*	m_pID_TEXT_Commander3;
	 ControlText*	m_pID_TEXT_Commander4;
	 ControlText*	m_pID_TEXT_QuestDesc1;
	 ControlText*	m_pID_TEXT_QuestDesc2;
	 ControlText*	m_pID_TEXT_QuestDesc3;
	 ControlText*	m_pID_TEXT_QuestDesc4;
	 ControlButton*	m_pID_BUTTON_Post1;
	 ControlButton*	m_pID_BUTTON_Post2;
	 ControlButton*	m_pID_BUTTON_Post3;
	 ControlButton*	m_pID_BUTTON_Post4;
	 ControlButton*	m_pID_BUTTON_TurnLeft;
	 ControlButton*	m_pID_BUTTON_TurnRight;
	 ControlText*	m_pID_TEXT_Page;	 

public:	
	CUI_ID_FRAME_CountryQuestPost();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Post1OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Post2OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Post3OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Post4OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TurnLeftOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TurnRightOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
    virtual void InitializeAtEnterWorld();

public:
	void GetNewCountryRight( uint32 countryRight );
	void GetDistributeResult( uint8 result );
	void GetCountryTaskBeginInfo( const MsgTellCountryQuestStatus* pMsg );
	void GetCountryTaskEndInfo( uint8 result );

private:
	void InitTask();
	void UpdatePages();

private:
	std::vector<CountryTask>	m_countryTaskVec;
	int							m_nPage;
	uint32						m_nCountryRight;

};
extern CUI_ID_FRAME_CountryQuestPost s_CUI_ID_FRAME_CountryQuestPost;
