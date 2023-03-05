/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\CountryInfo.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"
#ifndef ID_FRAME_Info
#define ID_FRAME_Info		"ID_FRAME_Info"
#endif  ID_FRAME_Info
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_TEXT_CountryTribute
#define ID_TEXT_CountryTribute		"ID_TEXT_CountryTribute"
#endif  ID_TEXT_CountryTribute
#ifndef ID_TEXT_CountryMoney
#define ID_TEXT_CountryMoney		"ID_TEXT_CountryMoney"
#endif  ID_TEXT_CountryMoney
#ifndef ID_TEXT_CountryState
#define ID_TEXT_CountryState		"ID_TEXT_CountryState"
#endif  ID_TEXT_CountryState
#ifndef ID_TEXT_CountryStrong
#define ID_TEXT_CountryStrong		"ID_TEXT_CountryStrong"
#endif  ID_TEXT_CountryStrong
#ifndef ID_TEXT_KingName
#define ID_TEXT_KingName		"ID_TEXT_KingName"
#endif  ID_TEXT_KingName
//#ifndef ID_BUTTON_CountryCommon
//#define ID_BUTTON_CountryCommon		"ID_BUTTON_CountryCommon"
//#endif  ID_BUTTON_CountryCommon
#ifndef ID_TEXT_CommonInfo
#define ID_TEXT_CommonInfo		"ID_TEXT_CommonInfo"
#endif  ID_TEXT_CommonInfo

class CUI_ID_FRAME_Info : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_Info();
	 ControlFrame*	m_pID_FRAME_Info;
	 ControlText*	m_pID_TEXT_Name;
	 ControlText*	m_pID_TEXT_CountryTribute;
	 ControlText*	m_pID_TEXT_CountryMoney;
	 ControlText*	m_pID_TEXT_CountryState;
	 ControlText*	m_pID_TEXT_CountryStrong;
	 ControlText*	m_pID_TEXT_KingName;
	 //ControlButton*	m_pID_BUTTON_CountryCommon;
	 ControlText*	m_pID_TEXT_CommonInfo;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	//bool ID_BUTTON_CountryCommonOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void OnInitUIInfo();
};
extern CUI_ID_FRAME_Info s_CUI_ID_FRAME_Info;
