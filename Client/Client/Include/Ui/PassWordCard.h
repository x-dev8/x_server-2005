/********************************************************************
	Created by UIEditor.exe
	FileName: D:\SVNClient\sg_pro\3Guo_Main\FullClient\Data\Ui\PassWordCard.h
*********************************************************************/
//密保卡
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#ifndef ID_FRAME_PassWordCard
#define ID_FRAME_PassWordCard		"ID_FRAME_PassWordCard"
#endif  ID_FRAME_PassWordCard
#ifndef ID_TEXT_PwdA
#define ID_TEXT_PwdA		"ID_TEXT_PwdA"
#endif  ID_TEXT_PwdA
#ifndef ID_TEXT_PwdC
#define ID_TEXT_PwdC		"ID_TEXT_PwdC"
#endif  ID_TEXT_PwdC
#ifndef ID_TEXT_PwdB
#define ID_TEXT_PwdB		"ID_TEXT_PwdB"
#endif  ID_TEXT_PwdB
#ifndef ID_EDIT_InfoA
#define ID_EDIT_InfoA		"ID_EDIT_InfoA"
#endif  ID_EDIT_InfoA
#ifndef ID_EDIT_InfoC
#define ID_EDIT_InfoC		"ID_EDIT_InfoC"
#endif  ID_EDIT_InfoC
#ifndef ID_EDIT_InfoB
#define ID_EDIT_InfoB		"ID_EDIT_InfoB"
#endif  ID_EDIT_InfoB
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK

#ifndef ID_TEXT_OnlyID
#define ID_TEXT_OnlyID		"ID_TEXT_OnlyID"
#endif  ID_TEXT_OnlyID

#ifndef ID_BUTTON_Canel
#define ID_BUTTON_Canel		"ID_BUTTON_Canel"
#endif  ID_BUTTON_Canel

#ifndef ID_TEXT_Time
#define ID_TEXT_Time		"ID_TEXT_Time"
#endif  ID_TEXT_Time


class CUI_ID_FRAME_PassWordCard :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_PassWordCard();
	 ControlFrame*	m_pID_FRAME_PassWordCard;
	 ControlText*	m_pID_TEXT_PwdA;
	 ControlText*	m_pID_TEXT_PwdC;
	 ControlText*	m_pID_TEXT_PwdB;
	 ControlEdit*	m_pID_EDIT_InfoA;
	 ControlEdit*	m_pID_EDIT_InfoC;
	 ControlEdit*	m_pID_EDIT_InfoB;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlText*	m_pID_TEXT_OnlyID;
	 ControlButton*	m_pID_BUTTON_Canel;
	 ControlText*	m_pID_TEXT_Time;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_EDIT_InfoAOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_InfoCOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_InfoBOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CanelOnButtonClick( ControlObject* pSender );


	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );// 设置是否可视
	
	void SetShow(const char* A,const char* B,const char* C,const char* OnlyID);
private:
	unsigned int m_LogTime;
};
extern CUI_ID_FRAME_PassWordCard s_CUI_ID_FRAME_PassWordCard;
