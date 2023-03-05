/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\InputBox.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_InputBox
#define ID_InputBox		"ID_InputBox"
#endif  ID_InputBox
#ifndef ID_EDIT_INPUT
#define ID_EDIT_INPUT		"ID_EDIT_INPUT"
#endif  ID_EDIT_INPUT
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_CANCEL
#define ID_BUTTON_CANCEL		"ID_BUTTON_CANCEL"
#endif  ID_BUTTON_CANCEL
#ifndef ID_TEXT_CAPTION
#define ID_TEXT_CAPTION		"ID_TEXT_CAPTION"
#endif  ID_TEXT_CAPTION
#ifndef ID_BUTTON_UP
#define ID_BUTTON_UP		"ID_BUTTON_UP"
#endif  ID_BUTTON_UP
#ifndef ID_BUTTON_DOWN
#define ID_BUTTON_DOWN		"ID_BUTTON_DOWN"
#endif  ID_BUTTON_DOWN

#include "UIBase.h"
class CUI_InputBox : public CUIBase
{
private:
	// SGuildMember
	ControlFrame*	m_pID_InputBox;
	ControlEdit*	m_pID_EDIT_INPUT;
	ControlText*	m_pID_TEXT_CAPTION;
	ControlButton*	m_pID_BUTTON_OK;
	ControlButton*	m_pID_BUTTON_CANCEL;
	ControlButton*	m_pID_BUTTON_UP;
	ControlButton*	m_pID_BUTTON_DOWN;

public:
	// Frame
	CUI_InputBox();
	bool OnFrameRun();
	bool OnFrameRender();
	// Edit
	void ID_EDIT_INPUTOnEditEnter( ControlObject* pSender, const char* szData );
	// Button
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	// Button
	bool ID_BUTTON_CANCELOnButtonClick( ControlObject* pSender );

	bool ID_BUTTON_UPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DOWNOnButtonClick( ControlObject* pSender );


	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	typedef bool (*funCallbackFun)( const char* szInputData, void *pData );
	BOOL EditInputIsVisable();
	ControlFrame* GetFrame() { return m_pID_InputBox; }

	// struct
	struct S_InputBox
	{
		S_InputBox()
		{
			m_bModal = true;
			m_pCallbackFun = NULL;
			m_pData = NULL;
			m_bIsNumber = true;
			m_bIsPassWord = false;
		}
		std::string m_strCaption;
		bool m_bModal;
		bool m_bIsNumber;
		bool m_bIsPassWord;
		funCallbackFun	m_pCallbackFun;
		void	*m_pData;
	};

	void Show( const char* szCaption, const bool bIsNumber = true, const bool bModal = true,
		const funCallbackFun pFun = NULL, void *pData = NULL, const int nDataLength = 0 , const bool bIfPwd = false,int nMaxLength = 2);
	void SetMaxValue(int v);
	void EditInput_SetText(int num);

private:

	void Refeash();

	static bool InputBox_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );
	static void InputBox_OnVisibleChanged(ControlObject* pSender);

	int				m_nMaxValue;
	int				m_nMinValue;
	funCallbackFun	m_pCurCallbackFun;
	void*			m_pData;
	std::vector<S_InputBox> m_vtInputBox;

};
extern CUI_InputBox s_CUI_InputBox;
