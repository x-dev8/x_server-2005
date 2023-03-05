/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\Client\UI\BillBoard.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include <vector>
#ifndef ID_FRAME_BillBoard
#define ID_FRAME_BillBoard		"ID_FRAME_BillBoard"
#endif  ID_FRAME_BillBoard
#ifndef ID_BUTTON_Next
#define ID_BUTTON_Next		"ID_BUTTON_Next"
#endif  ID_BUTTON_Next
#ifndef ID_BUTTON_Back
#define ID_BUTTON_Back		"ID_BUTTON_Back"
#endif  ID_BUTTON_Back
#ifndef ID_BUTTON_Close
#define ID_BUTTON_Close		"ID_BUTTON_Close"
#endif  ID_BUTTON_Close
#ifndef ID_TEXT_Text
#define ID_TEXT_Text		"ID_TEXT_Text"
#endif  ID_TEXT_Text

using namespace std;

#include "UiBase.h"
class CUI_ID_FRAME_BillBoard :public CUIBase
{
public:
	vector<std::string>	StringBuffer;
	// SGuildMember
private:
	ControlFrame*		m_pID_FRAME_BillBoard;
	ControlButton*	m_pID_BUTTON_Next;
	ControlButton*	m_pID_BUTTON_Back;
	ControlButton*	m_pID_BUTTON_Close;
	ControlText*		m_pID_TEXT_Text;

public:
	// Frame
	CUI_ID_FRAME_BillBoard();
	void PushStringBuffer(std::string szbuff);
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_NextOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_BackOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );
    void OnVisibleChanged( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

};

extern	CUI_ID_FRAME_BillBoard s_CUI_ID_FRAME_BillBoard;