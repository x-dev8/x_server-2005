/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\CountryQuest.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"
struct MsgTellCountryQuestStatus;
#ifndef ID_FRAME_Quest
#define ID_FRAME_Quest		"ID_FRAME_Quest"
#endif  ID_FRAME_Quest
#ifndef ID_TEXT_QuestInfo
#define ID_TEXT_QuestInfo		"ID_TEXT_QuestInfo"
#endif  ID_TEXT_QuestInfo
#ifndef ID_TEXT_GuoYun
#define ID_TEXT_GuoYun		"ID_TEXT_GuoYun"
#endif  ID_TEXT_GuoYun
#ifndef ID_TEXT_BinShu
#define ID_TEXT_BinShu		"ID_TEXT_BinShu"
#endif  ID_TEXT_BinShu
#ifndef ID_TEXT_GuoTan
#define ID_TEXT_GuoTan		"ID_TEXT_GuoTan"
#endif  ID_TEXT_GuoTan
#ifndef ID_TEXT_HuLiang
#define ID_TEXT_HuLiang		"ID_TEXT_HuLiang"
#endif  ID_TEXT_HuLiang
#ifndef ID_BUTTON_GuoYun
#define ID_BUTTON_GuoYun		"ID_BUTTON_GuoYun"
#endif  ID_BUTTON_GuoYun
#ifndef ID_BUTTON_GuoTan
#define ID_BUTTON_GuoTan		"ID_BUTTON_GuoTan"
#endif  ID_BUTTON_GuoTan
#ifndef ID_BUTTON_HuLiang
#define ID_BUTTON_HuLiang		"ID_BUTTON_HuLiang"
#endif  ID_BUTTON_HuLiang
#ifndef ID_BUTTON_BinShu
#define ID_BUTTON_BinShu		"ID_BUTTON_BinShu"
#endif  ID_BUTTON_BinShu

class CUI_ID_FRAME_Quest : public CUIBase
{
	// Member
	struct CountryTask
	{
		uint8 taskType;
		int nKeepTime;
		int requireRight;
		std::string strTaskName;
		std::string strPromulgator;
		std::string strDescribe;
	};
public:	
	 CUI_ID_FRAME_Quest();
	 ControlFrame*	m_pID_FRAME_Quest;
	 ControlText*	m_pID_TEXT_QuestInfo;
	 ControlText*	m_pID_TEXT_GuoYun;
	 ControlText*	m_pID_TEXT_BinShu;
	 ControlText*	m_pID_TEXT_GuoTan;
	 ControlText*	m_pID_TEXT_HuLiang;
	 ControlButton*	m_pID_BUTTON_GuoYun;
	 ControlButton*	m_pID_BUTTON_GuoTan;
	 ControlButton*	m_pID_BUTTON_HuLiang;
	 ControlButton*	m_pID_BUTTON_BinShu;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_GuoYunOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_GuoTanOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HuLiangOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_BinShuOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual void InitializeAtEnterWorld();

	void OnInitUIInfo();
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
	std::string		m_strTaskText;										// 国务文本
};
extern CUI_ID_FRAME_Quest s_CUI_ID_FRAME_Quest;
