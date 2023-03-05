/********************************************************************
Created by UIEditor.exe
FileName: E:\3Guo_Client_11.23\Data\Ui\ManualLevelUp.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "LevelLimitDefine.h"

#ifndef ID_FRAME_ManualLevelUp
#define ID_FRAME_ManualLevelUp		"ID_FRAME_ManualLevelUp"
#endif  ID_FRAME_ManualLevelUp
#ifndef ID_BUTTON_LevelUp
#define ID_BUTTON_LevelUp		"ID_BUTTON_LevelUp"
#endif  ID_BUTTON_LevelUp
#ifndef ID_BUTTON_Active
#define ID_BUTTON_Active		"ID_BUTTON_Active"
#endif  ID_BUTTON_Active
#ifndef ID_TEXT_CurrExp
#define ID_TEXT_CurrExp		"ID_TEXT_CurrExp"
#endif  ID_TEXT_CurrExp
#ifndef ID_TEXT_LevelUpExp
#define ID_TEXT_LevelUpExp		"ID_TEXT_LevelUpExp"
#endif  ID_TEXT_LevelUpExp
#ifndef ID_TEXT_WholeExp
#define ID_TEXT_WholeExp		"ID_TEXT_WholeExp"
#endif  ID_TEXT_WholeExp
#ifndef ID_TEXT_LimitInfo
#define ID_TEXT_LimitInfo		"ID_TEXT_LimitInfo"
#endif  ID_TEXT_LimitInfo

class CUI_ID_FRAME_ManualLevelUp: public CUIBase 
{
	// Member
public:	
	CUI_ID_FRAME_ManualLevelUp();
	ControlFrame*	m_pID_FRAME_ManualLevelUp;
	ControlButton*	m_pID_BUTTON_LevelUp;
	ControlButton*	m_pID_BUTTON_Active;
	ControlText*	m_pID_TEXT_CurrExp;
	ControlText*	m_pID_TEXT_LevelUpExp;
	ControlText*	m_pID_TEXT_WholeExp;
	ControlText*	m_pID_TEXT_LimitInfo;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_LevelUpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ActiveOnButtonClick( ControlObject* pSender );

	//bool LoadUI();				// 载入UI
	//bool DoControlConnect();	// 关连控件
	//bool UnLoadUI();			// 卸载UI
	//bool IsVisable();			// 是否可见
	//void SetVisable( const bool bVisable );			// 设置是否可视

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual bool IsHoldInMemory() const { return true; }
	virtual void InitializeAtEnterWorld();

	void InitLevelLimitData(SLevelLimitInfo* pLLInfo,short max_lv);
	void InitExpInfo();
	void Refresh();
	void DoneLimit();
private:
	SLevelLimitInfo    sllinfo;
	bool               isInit;
	__int64			ulCanTakeExp;
	short              Max_level;
};
extern CUI_ID_FRAME_ManualLevelUp s_CUI_ID_FRAME_ManualLevelUp;
