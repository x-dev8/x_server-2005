/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\����\�½��ļ��� (13)\FamilyUI\FamilyTenet.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GUILD_FamilyTenet
#define ID_FRAME_GUILD_FamilyTenet		"ID_FRAME_GUILD_FamilyTenet"
#endif  ID_FRAME_GUILD_FamilyTenet
#ifndef ID_BUTTON_CREATE
#define ID_BUTTON_CREATE		"ID_BUTTON_CREATE"
#endif  ID_BUTTON_CREATE
#ifndef ID_BUTTON_close
#define ID_BUTTON_close		"ID_BUTTON_close"
#endif  ID_BUTTON_close
#ifndef ID_TEXT_JiaZuZongZhi
#define ID_TEXT_JiaZuZongZhi		"ID_TEXT_JiaZuZongZhi"
#endif  ID_TEXT_JiaZuZongZhi
#ifndef ID_EDIT_ZongZhi
#define ID_EDIT_ZongZhi		"ID_EDIT_ZongZhi"
#endif  ID_EDIT_ZongZhi

#include "UiBase.h"

class CUI_ID_FRAME_GUILD_FamilyTenet : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_GUILD_FamilyTenet();
	 ControlFrame*	m_pID_FRAME_GUILD_FamilyTenet;
	 ControlButton*	m_pID_BUTTON_CREATE;
	 ControlButton*	m_pID_BUTTON_close;
	 ControlText*	m_pID_TEXT_JiaZuZongZhi;
	 ControlEdit*	m_pID_EDIT_ZongZhi;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CREATEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_closeOnButtonClick( ControlObject* pSender );
	void ID_EDIT_ZongZhiOnEditEnter( ControlObject* pSender, const char* szData );

public:
	void UpdateAim();	//���µ���������

	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����

public:
	bool    EditInputIsVisable();

private:
	std::string		szNewAim;
};
extern CUI_ID_FRAME_GUILD_FamilyTenet s_CUI_ID_FRAME_GUILD_FamilyTenet;
