/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\RTX\TransferToNpc.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"

#ifndef ID_FRAME_TransferToNpc
#define ID_FRAME_TransferToNpc		"ID_FRAME_TransferToNpc"
#endif  ID_FRAME_TransferToNpc
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_PICTURE_FrameHead
#define ID_PICTURE_FrameHead		"ID_PICTURE_FrameHead"
#endif  ID_PICTURE_FrameHead
#ifndef ID_BUTTON_Cancle
#define ID_BUTTON_Cancle		"ID_BUTTON_Cancle"
#endif  ID_BUTTON_Cancle
#ifndef ID_TEXT_Msg
#define ID_TEXT_Msg		"ID_TEXT_Msg"
#endif  ID_TEXT_Msg

class CUI_ID_FRAME_TransferToNpc: public CUIBase
{
	// Member
public:
	CUI_ID_FRAME_TransferToNpc();

private:	
	 ControlFrame*	m_pID_FRAME_TransferToNpc;
	 ControlButton*	m_pID_BUTTON_Ok;
	 ControlPicture*	m_pID_PICTURE_FrameHead;
	 ControlButton*	m_pID_BUTTON_Cancle;
	 ControlText*	m_pID_TEXT_Msg;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancleOnButtonClick( ControlObject* pSender );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	void InitMember();

	//----------------------------------------------------------------
public:
	typedef void(*funcPressYes) (int nValue);
	void Show(funcPressYes, int, const char*);
	
private:	
	int m_nValue;
	funcPressYes m_funcPressYes;
	std::string m_strShowMessage;

private:
	void SetMemberValue(funcPressYes func, int nValue, const char* szText);
	void ShowInfo();
};

extern CUI_ID_FRAME_TransferToNpc s_CUI_ID_FRAME_TransferToNpc;
