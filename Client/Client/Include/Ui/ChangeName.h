/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\ChangeName.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#ifndef ID_FRAME_ChangeName
#define ID_FRAME_ChangeName		"ID_FRAME_ChangeName"
#endif  ID_FRAME_ChangeName
#ifndef ID_EDIT_Name
#define ID_EDIT_Name		"ID_EDIT_Name"
#endif  ID_EDIT_Name
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK

#ifndef ID_TEXT_Info
#define ID_TEXT_Info		"ID_TEXT_Info"
#endif  ID_TEXT_Info

class CUI_ID_FRAME_ChangeName :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_ChangeName();
	virtual ~CUI_ID_FRAME_ChangeName();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	void ID_EDIT_NameOnEditEnter( ControlObject* pSender, const char* szData );

	virtual bool _LoadUI();				// 载入UI
	virtual bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void	Clear();
	void	SetPlayerID(int ID){m_PlayerID =ID;}
	void OnChangeNameAck(bool Result);
	string GetTextName();
private:	
	 ControlFrame*	m_pID_FRAME_ChangeName;
	 ControlEdit*	m_pID_EDIT_Name;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlText*   m_pID_TEXT_Info;
	 int			m_PlayerID;
};
extern CUI_ID_FRAME_ChangeName s_CUI_ID_FRAME_ChangeName;
