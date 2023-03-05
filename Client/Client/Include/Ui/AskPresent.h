/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\AskPresent.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_AskPresent
#define ID_FRAME_AskPresent		"ID_FRAME_AskPresent"
#endif  ID_FRAME_AskPresent
#ifndef ID_EDIT_SN
#define ID_EDIT_SN		"ID_EDIT_SN"
#endif  ID_EDIT_SN
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel

class CUI_ID_FRAME_AskPresent:public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_AskPresent();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_EDIT_SNOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void SetVisiblePosition( const Vector& vPos ){ m_vVisiblePos = vPos; }
	void Reset();
	ControlEdit* GetEDIT_AddName();

	static bool FrameMsg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );
	bool EditInputIsVisable();

private:
	ControlFrame*	m_pID_FRAME_AskPresent;
	ControlEdit*	m_pID_EDIT_SN;
	ControlButton*	m_pID_BUTTON_OK;
	ControlButton*	m_pID_BUTTON_Cancel;

	Vector			m_vVisiblePos;
};
extern CUI_ID_FRAME_AskPresent s_CUI_ID_FRAME_AskPresent;
