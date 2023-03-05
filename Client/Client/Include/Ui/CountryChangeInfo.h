/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\CountryChangeInfo.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"
#ifndef ID_FRAME_CountryInfo
#define ID_FRAME_CountryInfo		"ID_FRAME_CountryInfo"
#endif  ID_FRAME_CountryInfo
#ifndef ID_LIST_Time
#define ID_LIST_Time		"ID_LIST_Time"
#endif  ID_LIST_Time
#ifndef ID_LIST_Info
#define ID_LIST_Info		"ID_LIST_Info"
#endif  ID_LIST_Info
#ifndef ID_LIST_Value
#define ID_LIST_Value		"ID_LIST_Value"
#endif  ID_LIST_Value

class CUI_ID_FRAME_CountryInfo :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_CountryInfo();
	virtual ~CUI_ID_FRAME_CountryInfo();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_TimeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_InfoOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ValueOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void OnInitUIInfo();
private:
	void OnShow();
private:	
	 ControlFrame*	m_pID_FRAME_CountryInfo;
	 ControlList*	m_pID_LIST_Time;
	 ControlList*	m_pID_LIST_Info;
	 ControlList*	m_pID_LIST_Value;
};
extern CUI_ID_FRAME_CountryInfo s_CUI_ID_FRAME_CountryInfo;
