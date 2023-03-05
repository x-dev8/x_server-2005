/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\chixin.ni\����\TeamBattleRule.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "me3d/Vector.h"

#ifndef ID_FRAME_TeamBattleRule
#define ID_FRAME_TeamBattleRule		"ID_FRAME_TeamBattleRule"
#endif  ID_FRAME_TeamBattleRule
#ifndef ID_PICTURE_BackWall
#define ID_PICTURE_BackWall		"ID_PICTURE_BackWall"
#endif  ID_PICTURE_BackWall
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Team
#define ID_BUTTON_Team		"ID_BUTTON_Team"
#endif  ID_BUTTON_Team
#ifndef ID_TEXT_Rule
#define ID_TEXT_Rule		"ID_TEXT_Rule"
#endif  ID_TEXT_Rule

#include "UiBase.h"
class CUI_ID_FRAME_TeamBattleRule :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_TeamBattleRule();
private:
	 ControlFrame*	m_pID_FRAME_TeamBattleRule;
	 ControlPicture*	m_pID_PICTURE_BackWall;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlButton*	m_pID_BUTTON_Team;
	 ControlText*	m_pID_TEXT_Rule;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TeamOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
public:

	const Vector& GetVisiblePosition() const { return m_vVisiblePos; }
	void SetVisiblePosition( const Vector& vPos ){ m_vVisiblePos = vPos; }

private:
	Vector m_vVisiblePos;	
};
extern CUI_ID_FRAME_TeamBattleRule s_CUI_ID_FRAME_TeamBattleRule;
