/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\GameSettingSell.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GameSettingSell
#define ID_FRAME_GameSettingSell		"ID_FRAME_GameSettingSell"
#endif  ID_FRAME_GameSettingSell
#ifndef ID_PICTURE_Wall1
#define ID_PICTURE_Wall1		"ID_PICTURE_Wall1"
#endif  ID_PICTURE_Wall1
#ifndef ID_TEXT_SellInfo
#define ID_TEXT_SellInfo		"ID_TEXT_SellInfo"
#endif  ID_TEXT_SellInfo
#ifndef ID_TEXT_Quality0
#define ID_TEXT_Quality0		"ID_TEXT_Quality0"
#endif  ID_TEXT_Quality0
#ifndef ID_TEXT_Quality4
#define ID_TEXT_Quality4		"ID_TEXT_Quality4"
#endif  ID_TEXT_Quality4
#ifndef ID_TEXT_Quality1
#define ID_TEXT_Quality1		"ID_TEXT_Quality1"
#endif  ID_TEXT_Quality1
#ifndef ID_TEXT_Quality3
#define ID_TEXT_Quality3		"ID_TEXT_Quality3"
#endif  ID_TEXT_Quality3
#ifndef ID_TEXT_Quality2
#define ID_TEXT_Quality2		"ID_TEXT_Quality2"
#endif  ID_TEXT_Quality2
#ifndef ID_CHECKBOX_Quality0
#define ID_CHECKBOX_Quality0		"ID_CHECKBOX_Quality0"
#endif  ID_CHECKBOX_Quality0
#ifndef ID_CHECKBOX_Quality1
#define ID_CHECKBOX_Quality1		"ID_CHECKBOX_Quality1"
#endif  ID_CHECKBOX_Quality1
#ifndef ID_CHECKBOX_Quality2
#define ID_CHECKBOX_Quality2		"ID_CHECKBOX_Quality2"
#endif  ID_CHECKBOX_Quality2
#ifndef ID_CHECKBOX_Quality3
#define ID_CHECKBOX_Quality3		"ID_CHECKBOX_Quality3"
#endif  ID_CHECKBOX_Quality3
#ifndef ID_CHECKBOX_Quality4
#define ID_CHECKBOX_Quality4		"ID_CHECKBOX_Quality4"
#endif  ID_CHECKBOX_Quality4
#ifndef ID_TEXT_Quality5
#define ID_TEXT_Quality5		"ID_TEXT_Quality5"
#endif  ID_TEXT_Quality5
#ifndef ID_CHECKBOX_Quality5
#define ID_CHECKBOX_Quality5		"ID_CHECKBOX_Quality5"
#endif  ID_CHECKBOX_Quality5
#ifndef ID_CHECKBOX_QualityAll
#define ID_CHECKBOX_QualityAll		"ID_CHECKBOX_QualityAll"
#endif  ID_CHECKBOX_QualityAll

#include "UiBase.h"
class CUI_ID_FRAME_GameSettingSell :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_GameSettingSell();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	//void ID_CHECKBOX_Quality0OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Quality1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Quality2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Quality3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Quality4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Quality5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	//void ID_CHECKBOX_QualityAllOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


    void RefreshUI();

    ControlFrame* GetFrame(){return m_pID_FRAME_GameSettingSell;}
private:
    ControlFrame*	m_pID_FRAME_GameSettingSell;
    ControlPicture*	m_pID_PICTURE_Wall1;
    ControlText*	m_pID_TEXT_SellInfo;
    //ControlText*	m_pID_TEXT_Quality0;
    ControlText*	m_pID_TEXT_Quality4;
    ControlText*	m_pID_TEXT_Quality1;
    ControlText*	m_pID_TEXT_Quality3;
    ControlText*	m_pID_TEXT_Quality2;
    //ControlCheckBox*	m_pID_CHECKBOX_Quality0;
    ControlCheckBox*	m_pID_CHECKBOX_Quality1;
    ControlCheckBox*	m_pID_CHECKBOX_Quality2;
    ControlCheckBox*	m_pID_CHECKBOX_Quality3;
    ControlCheckBox*	m_pID_CHECKBOX_Quality4;
    ControlText*	m_pID_TEXT_Quality5;
    ControlCheckBox*	m_pID_CHECKBOX_Quality5;
    //ControlCheckBox*	m_pID_CHECKBOX_QualityAll;
};
extern CUI_ID_FRAME_GameSettingSell s_CUI_ID_FRAME_GameSettingSell;
