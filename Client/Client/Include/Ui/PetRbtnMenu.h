/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\PetRbtnMenu.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_PetRBMenu
#define ID_FRAME_PetRBMenu		"ID_FRAME_PetRBMenu"
#endif  ID_FRAME_PetRBMenu
#ifndef ID_BUTTON_ChangeName
#define ID_BUTTON_ChangeName		"ID_BUTTON_ChangeName"
#endif  ID_BUTTON_ChangeName
#ifndef ID_BUTTON_Close
#define ID_BUTTON_Close		"ID_BUTTON_Close"
#endif  ID_BUTTON_Close

#include "UiBase.h"
class CUI_ID_FRAME_PetRBMenu :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_PetRBMenu();
private:
	 ControlFrame*	m_pID_FRAME_PetRBMenu;
	 ControlButton*	m_pID_BUTTON_ChangeName;
	 ControlButton*	m_pID_BUTTON_Close;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_ChangeNameOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
public:


	void ChangePetName(const char* szName);

private:
};
extern CUI_ID_FRAME_PetRBMenu s_CUI_ID_FRAME_PetRBMenu;
