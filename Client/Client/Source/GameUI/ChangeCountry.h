/********************************************************************
Created by UIEditor.exe
FileName: E:\Zxc\3Guo Client 8.30\3Guo Client\Data\Ui\ChangeCountry.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"

#ifndef ID_FRAME_ChangeCountry
#define ID_FRAME_ChangeCountry		"ID_FRAME_ChangeCountry"
#endif  ID_FRAME_ChangeCountry
#ifndef ID_CHECKBOX_ShuGuo
#define ID_CHECKBOX_ShuGuo		"ID_CHECKBOX_ShuGuo"
#endif  ID_CHECKBOX_ShuGuo
#ifndef ID_CHECKBOX_WeiGuo
#define ID_CHECKBOX_WeiGuo		"ID_CHECKBOX_WeiGuo"
#endif  ID_CHECKBOX_WeiGuo
#ifndef ID_CHECKBOX_WuGuo
#define ID_CHECKBOX_WuGuo		"ID_CHECKBOX_WuGuo"
#endif  ID_CHECKBOX_WuGuo
#ifndef ID_BUTTON_Join
#define ID_BUTTON_Join		"ID_BUTTON_Join"
#endif  ID_BUTTON_Join
#ifndef ID_BUTTON_Exit
#define ID_BUTTON_Exit		"ID_BUTTON_Exit"
#endif  ID_BUTTON_Exit
#ifndef ID_BUTTON_Rand
#define ID_BUTTON_Rand		"ID_BUTTON_Rand"
#endif  ID_BUTTON_Rand
#ifndef RandCountry			
#define	RandCountry			11
#endif	RandCountry


class CUI_ID_FRAME_ChangeCountry : public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_ChangeCountry();
	ControlFrame*	m_pID_FRAME_ChangeCountry;
	ControlCheckBox*	m_pID_CHECKBOX_ShuGuo;
	ControlCheckBox*	m_pID_CHECKBOX_WeiGuo;
	ControlCheckBox*	m_pID_CHECKBOX_WuGuo;
	ControlButton*	m_pID_BUTTON_Join;
	ControlButton*	m_pID_BUTTON_Exit;
	ControlButton*	m_pID_BUTTON_Rand;
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_ShuGuoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_WeiGuoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_WuGuoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_JoinOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ExitOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RandOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual bool IsHoldInMemory() const { return true; }
	virtual void InitializeAtEnterWorld();

	int GetCountryId();

	void Refresh();
private:
	bool check_ShuGuo;
	bool check_WeiGuo;
	bool check_WuGuo;
};
extern CUI_ID_FRAME_ChangeCountry s_CUI_ID_FRAME_ChangeCountry;
