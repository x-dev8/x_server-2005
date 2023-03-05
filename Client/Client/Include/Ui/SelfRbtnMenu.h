/********************************************************************
	Created by UIEditor.exe
	FileName: D:\Tj\Client\UI\SelfRbtnMenu.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_SelfRBMenu
#define ID_FRAME_SelfRBMenu		"ID_FRAME_SelfRBMenu"
#endif  ID_FRAME_SelfRBMenu
#ifndef ID_BUTTON_Disband
#define ID_BUTTON_Disband		"ID_BUTTON_Disband"
#endif  ID_BUTTON_Disband
#ifndef ID_BUTTON_Getout
#define ID_BUTTON_Getout		"ID_BUTTON_Getout"
#endif  ID_BUTTON_Getout
#ifndef ID_BUTTON_DisMount
#define ID_BUTTON_DisMount		"ID_BUTTON_DisMount"
#endif  ID_BUTTON_DisMount
#ifndef ID_BUTTON_AssignMode
#define ID_BUTTON_AssignMode	"ID_BUTTON_AssignMode"
#endif ID_BUTTON_AssignMode
#ifndef ID_BUTTON_SelectQuality
#define ID_BUTTON_SelectQuality		"ID_BUTTON_SelectQuality"
#endif  ID_BUTTON_SelectQuality
#ifndef ID_BUTTON_FreeMode
#define ID_BUTTON_FreeMode		"ID_BUTTON_FreeMode"
#endif  ID_BUTTON_FreeMode
#ifndef ID_BUTTON_TeamMode
#define ID_BUTTON_TeamMode		"ID_BUTTON_TeamMode"
#endif  ID_BUTTON_TeamMode
#ifndef ID_BUTTON_LeaderMode
#define ID_BUTTON_LeaderMode		"ID_BUTTON_LeaderMode"
#endif  ID_BUTTON_LeaderMode
#ifndef ID_BUTTON_Esc
#define ID_BUTTON_Esc		"ID_BUTTON_Esc"
#endif  ID_BUTTON_Esc
#ifndef ID_BUTTON_Quality2
#define ID_BUTTON_Quality2		"ID_BUTTON_Quality2"
#endif  ID_BUTTON_Quality2
#ifndef ID_BUTTON_Quality3
#define ID_BUTTON_Quality3		"ID_BUTTON_Quality3"
#endif  ID_BUTTON_Quality3
#ifndef ID_BUTTON_Quality4
#define ID_BUTTON_Quality4		"ID_BUTTON_Quality4"
#endif  ID_BUTTON_Quality4
#ifndef ID_BUTTON_Quit
#define ID_BUTTON_Quit		"ID_BUTTON_Quit"
#endif  ID_BUTTON_Quit
#ifndef ID_PICTURE_AssignLeft
#define ID_PICTURE_AssignLeft		"ID_PICTURE_AssignLeft"
#endif  ID_PICTURE_AssignLeft
#ifndef ID_PICTURE_QualityLeft
#define ID_PICTURE_QualityLeft		"ID_PICTURE_QualityLeft"
#endif  ID_PICTURE_QualityLeft
#ifndef ID_PICTURE_FreeMode
#define ID_PICTURE_FreeMode		"ID_PICTURE_FreeMode"
#endif  ID_PICTURE_FreeMode
#ifndef ID_PICTURE_TeamMode
#define ID_PICTURE_TeamMode		"ID_PICTURE_TeamMode"
#endif  ID_PICTURE_TeamMode
#ifndef ID_PICTURE_LeaderMode
#define ID_PICTURE_LeaderMode		"ID_PICTURE_LeaderMode"
#endif  ID_PICTURE_LeaderMode
#ifndef ID_PICTURE_Quality2
#define ID_PICTURE_Quality2		"ID_PICTURE_Quality2"
#endif  ID_PICTURE_Quality2
#ifndef ID_PICTURE_Quality3
#define ID_PICTURE_Quality3		"ID_PICTURE_Quality3"
#endif  ID_PICTURE_Quality3
#ifndef ID_PICTURE_Quality4
#define ID_PICTURE_Quality4		"ID_PICTURE_Quality4"
#endif  ID_PICTURE_Quality4
#ifndef ID_BUTTON_Close
#define ID_BUTTON_Close		"ID_BUTTON_Close"
#endif  ID_BUTTON_Close
#ifndef ID_PICTURE_QualityLeft2
#define ID_PICTURE_QualityLeft2		"ID_PICTURE_QualityLeft2"
#endif  ID_PICTURE_QualityLeft2
#ifndef ID_BUTTON_CJDW
#define ID_BUTTON_CJDW		"ID_BUTTON_CJDW"
#endif  ID_BUTTON_CJDW
#ifndef ID_BUTTON_QXGS
#define ID_BUTTON_QXGS		"ID_BUTTON_QXGS"
#endif  ID_BUTTON_QXGS
#ifndef ID_BUTTON_ZDGS
#define ID_BUTTON_ZDGS		"ID_BUTTON_ZDGS"
#endif  ID_BUTTON_ZDGS

#ifndef ID_BUTTON_ClearTeamMap
#define ID_BUTTON_ClearTeamMap		"ID_BUTTON_ClearTeamMap"
#endif  ID_BUTTON_ClearTeamMap


#include "UiBase.h"
class CUI_ID_FRAME_SelfRBMenu :public CUIBase
{
// 	DECLARE_DLG_INST(CUI_ID_FRAME_SelfRBMenu);
	// SGuildMember
public:	
	CUI_ID_FRAME_SelfRBMenu();
private:
	void ResetMembers();
	 ControlFrame*	m_pID_FRAME_SelfRBMenu;
	 ControlButton*	m_pID_BUTTON_Disband;		//解散
	 ControlButton*	m_pID_BUTTON_Getout;		//离队

	 ControlButton* m_pID_BUTTON_DisMount;		//下马 ..Human
	 ControlButton* m_pID_BUTTON_AssignMode;	//分配模式 
	 ControlButton*	m_pID_BUTTON_SelectQuality;
	 ControlButton*	m_pID_BUTTON_FreeMode;
	 ControlButton*	m_pID_BUTTON_TeamMode;
	 ControlButton*	m_pID_BUTTON_LeaderMode;
	 ControlButton*	m_pID_BUTTON_Esc;
	 ControlButton*	m_pID_BUTTON_Quality2;
	 ControlButton*	m_pID_BUTTON_Quality3;
	 ControlButton*	m_pID_BUTTON_Quality4;
	 ControlButton*	m_pID_BUTTON_Quit;
// 	 ControlPicture*	m_pID_PICTURE_AssignLeft;
// 	 ControlPicture*	m_pID_PICTURE_QualityLeft;
// 	 ControlPicture*	m_pID_PICTURE_FreeMode;
// 	 ControlPicture*	m_pID_PICTURE_TeamMode;
// 	 ControlPicture*	m_pID_PICTURE_LeaderMode;
// 	 ControlPicture*	m_pID_PICTURE_Quality2;
// 	 ControlPicture*	m_pID_PICTURE_Quality3;
// 	 ControlPicture*	m_pID_PICTURE_Quality4;
	 ControlButton*	m_pID_BUTTON_Close;
	// ControlPicture*	m_pID_PICTURE_QualityLeft2;

	 ControlButton*	m_pID_BUTTON_CJDW;
	 ControlButton*	m_pID_BUTTON_QXGS;
	 ControlButton*	m_pID_BUTTON_ZDGS;
	 ControlButton*	m_pID_BUTTON_ClearTeamMap;
	 

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_DisbandOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_GetoutOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DisMountOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OpenCorpsOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AssignModeOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_SelectQualityOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FreeModeOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TeamModeOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LeaderModeOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_EscOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Quality2OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Quality3OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Quality4OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_QuitOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );

	bool ID_BUTTON_CJDWOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_QXGSOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ZDGSOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ClearTeamMapOnButtonClick( ControlObject* pSender );
	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


    void SetAssignMode( unsigned char ucMode );
    void SetQuality( unsigned char ucQuality );
    void UpdateAssignMode();
    void UpdateSelectQuality();

	void GetoutOnButtonClick(ControlObject* pSender);

protected:
    void UpdateAssignModeButton();
    void UpdateSelectQualityButton();
    void SetSelectQualityCaptionColor(const char* szCaption, DWORD color);
    void CheckSetAssignMode();
    void UpdateAssignModeTips();
    void ShowSelectQualityButtons(bool bshow);

    bool m_bShowAssignMode;
    bool m_bShowSelectQuality;
    unsigned char m_ucSelectAssignMode;
};

extern CUI_ID_FRAME_SelfRBMenu s_CUI_ID_FRAME_SelfRBMenu;