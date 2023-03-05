/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (22)\CrowdCarryMainMore.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_CrowdCarryMainMore
#define ID_FRAME_CrowdCarryMainMore		"ID_FRAME_CrowdCarryMainMore"
#endif  ID_FRAME_CrowdCarryMainMore
#ifndef ID_TEXT_Amount
#define ID_TEXT_Amount		"ID_TEXT_Amount"
#endif  ID_TEXT_Amount
#ifndef ID_BUTTON_Live
#define ID_BUTTON_Live		"ID_BUTTON_Live"
#endif  ID_BUTTON_Live
#ifndef ID_TEXT_CZ
#define ID_TEXT_CZ		"ID_TEXT_CZ"
#endif  ID_TEXT_CZ
#ifndef ID_LIST_Player
#define ID_LIST_Player		"ID_LIST_Player"
#endif  ID_LIST_Player
#ifndef ID_TEXT_PetName
#define ID_TEXT_PetName		"ID_TEXT_PetName"
#endif  ID_TEXT_PetName
#ifndef ID_BUTTON_Kick01
#define ID_BUTTON_Kick01		"ID_BUTTON_Kick01"
#endif  ID_BUTTON_Kick01
#ifndef ID_BUTTON_Kick02
#define ID_BUTTON_Kick02		"ID_BUTTON_Kick02"
#endif  ID_BUTTON_Kick02
#ifndef ID_BUTTON_Kick03
#define ID_BUTTON_Kick03		"ID_BUTTON_Kick03"
#endif  ID_BUTTON_Kick03
#ifndef ID_BUTTON_Kick04
#define ID_BUTTON_Kick04		"ID_BUTTON_Kick04"
#endif  ID_BUTTON_Kick04
#ifndef ID_BUTTON_Kick05
#define ID_BUTTON_Kick05		"ID_BUTTON_Kick05"
#endif  ID_BUTTON_Kick05
#ifndef ID_BUTTON_Kick06
#define ID_BUTTON_Kick06		"ID_BUTTON_Kick06"
#endif  ID_BUTTON_Kick06
#ifndef ID_BUTTON_Kick07
#define ID_BUTTON_Kick07		"ID_BUTTON_Kick07"
#endif  ID_BUTTON_Kick07
#ifndef ID_BUTTON_Kick08
#define ID_BUTTON_Kick08		"ID_BUTTON_Kick08"
#endif  ID_BUTTON_Kick08

#include "UIBase.h"

class CUI_ID_FRAME_CrowdCarryMainMore : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_CrowdCarryMainMore();
	 ControlFrame*	m_pID_FRAME_CrowdCarryMainMore;
	 ControlText*	m_pID_TEXT_Amount;
	 ControlButton*	m_pID_BUTTON_Live;
	 ControlText*	m_pID_TEXT_CZ;
	 ControlList*	m_pID_LIST_Player;
	 ControlText*	m_pID_TEXT_PetName;
	 ControlButton*	m_pID_BUTTON_Kick01;
	 ControlButton*	m_pID_BUTTON_Kick02;
	 ControlButton*	m_pID_BUTTON_Kick03;
	 ControlButton*	m_pID_BUTTON_Kick04;
	 ControlButton*	m_pID_BUTTON_Kick05;
	 ControlButton*	m_pID_BUTTON_Kick06;
	 ControlButton*	m_pID_BUTTON_Kick07;
	 ControlButton*	m_pID_BUTTON_Kick08;

public:
	void SetTotalSetNum( int num ){ m_iTotalSetNum = num; }
	void RefreshPassengerList( const std::vector<int32>& ls );

	bool IsOnYourBoard( int id );

protected:
	void ShowButton( int i );
	void HideAllButtons();
	void KickOffPassenger( int i );

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_LiveOnButtonClick( ControlObject* pSender );
	void ID_LIST_PlayerOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_Kick01OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Kick02OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Kick03OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Kick04OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Kick05OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Kick06OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Kick07OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Kick08OnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	        // 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

private:
	virtual bool IsHoldInMemory() const { return true; }

private:	
	int		m_iTotalSetNum;
	int		m_iCurSetNum;
	std::vector<int32>	m_passengers;
};
extern CUI_ID_FRAME_CrowdCarryMainMore s_CUI_ID_FRAME_CrowdCarryMainMore;
