/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (18)\新建文件夹 (6)\TutorialBox.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_TutorialBox
#define ID_FRAME_TutorialBox		"ID_FRAME_TutorialBox"
#endif  ID_FRAME_TutorialBox
#ifndef ID_TEXT_CAPTION
#define ID_TEXT_CAPTION		"ID_TEXT_CAPTION"
#endif  ID_TEXT_CAPTION
#ifndef ID_CHECKBOX_Up
#define ID_CHECKBOX_Up		"ID_CHECKBOX_Up"
#endif  ID_CHECKBOX_Up
#ifndef ID_CHECKBOX_Down
#define ID_CHECKBOX_Down		"ID_CHECKBOX_Down"
#endif  ID_CHECKBOX_Down
#ifndef ID_CHECKBOX_Left
#define ID_CHECKBOX_Left		"ID_CHECKBOX_Left"
#endif  ID_CHECKBOX_Left
#ifndef ID_CHECKBOX_Right
#define ID_CHECKBOX_Right		"ID_CHECKBOX_Right"
#endif  ID_CHECKBOX_Right
#ifndef ID_PICTURE_FangXiang
#define ID_PICTURE_FangXiang		"ID_PICTURE_FangXiang"
#endif  ID_PICTURE_FangXiang
#ifndef ID_CHECKBOX_MouseLeft
#define ID_CHECKBOX_MouseLeft		"ID_CHECKBOX_MouseLeft"
#endif  ID_CHECKBOX_MouseLeft
#ifndef ID_CHECKBOX_MouseRight
#define ID_CHECKBOX_MouseRight		"ID_CHECKBOX_MouseRight"
#endif  ID_CHECKBOX_MouseRight
#ifndef ID_PICTURE_Mouse
#define ID_PICTURE_Mouse		"ID_PICTURE_Mouse"
#endif  ID_PICTURE_Mouse
#ifndef ID_CHECKBOX_Space
#define ID_CHECKBOX_Space		"ID_CHECKBOX_Space"
#endif  ID_CHECKBOX_Space
#ifndef ID_PICTURE_Space
#define ID_PICTURE_Space		"ID_PICTURE_Space"
#endif  ID_PICTURE_Space
#ifndef ID_TEXT_Info
#define ID_TEXT_Info		"ID_TEXT_Info"
#endif  ID_TEXT_Info

#ifndef ID_TEXT_Mouse
#define ID_TEXT_Mouse		"ID_TEXT_Mouse"
#endif  ID_TEXT_Mouse
#ifndef ID_PICTURE_And
#define ID_PICTURE_And		"ID_PICTURE_And"
#endif  ID_PICTURE_And

#include "UIBase.h"

class CUI_ID_FRAME_TutorialBox : public CUIBase
{
	enum TutorialType
	{
		T_MOVEPLAYER_UP,
		T_MOVEPLAYER_DOWN,
		T_MOVEPLAYER_LEFT,
		T_MOVEPLAYER_RIGHT,
		T_MOUSELBUTTON_OPT,
		T_MOUSERBUTTON_OPT,
		T_SPACE_OPT,
		T_MAX
	};

	typedef void (CUI_ID_FRAME_TutorialBox::*CallBackFunc)();

	class MovePair
	{
	public:
		MovePair()
		{
			m_fStartX = 0.0f;
			m_fStartY = 0.0f;
			m_fEndX = 0.0f;
			m_fEndY = 0.0f;
			m_bFinished = true;
			m_func = NULL;

			m_fMoveTime = 0.0f;
			m_fElapse = 0.0f;
		}
	public:
		void Update( DWORD tic );

	protected:
	public:
		float m_fStartX;
		float m_fStartY;
		float m_fEndX;
		float m_fEndY;
		bool m_bFinished;
		CallBackFunc m_func;

		float m_fMoveTime;
		float m_fElapse;

		DWORD m_dwLastTic;
	};
	
	//typedef void (CUI_ID_FRAME_TutorialBox::CallBackFunc*)();

	// Member
public:	
	 CUI_ID_FRAME_TutorialBox();
	 ControlFrame*	m_pID_FRAME_TutorialBox;
	 ControlText*	m_pID_TEXT_CAPTION;
	 ControlCheckBox*	m_pID_CHECKBOX_Up;
	 ControlCheckBox*	m_pID_CHECKBOX_Down;
	 ControlCheckBox*	m_pID_CHECKBOX_Left;
	 ControlCheckBox*	m_pID_CHECKBOX_Right;
	 ControlPicture*	m_pID_PICTURE_FangXiang;
	 ControlCheckBox*	m_pID_CHECKBOX_MouseLeft;
	 ControlCheckBox*	m_pID_CHECKBOX_MouseRight;
	 ControlPicture*	m_pID_PICTURE_Mouse;
	 ControlCheckBox*	m_pID_CHECKBOX_Space;
	 ControlPicture*	m_pID_PICTURE_Space;
	 ControlText*	m_pID_TEXT_Info;
	 ControlText*	m_pID_TEXT_Mouse;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_UpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_DownOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_LeftOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_RightOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_MouseLeftOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_MouseRightOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_SpaceOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void StartTutorial();
	void SetTutorialMovePlayer();	//移动玩家指引
	void SetTutorialMovePlayerUp();
	void SetTutorialMovePlayerDown();
	void SetTutorialMovePlayerLeft();
	void SetTutorialMovePlayerRight();
	void SetTutorialLMouseOpt();		//鼠标操作
	void SetTutorialRMouseOpt();		//鼠标操作
	void SetTutorialSapceOpt();		//空格键操作

	void OnMovePlayerUp();
	void OnMovePlayerDown();
	void OnMovePlayerLeft();
	void OnMovePlayerRight();
	void OnLMouseButton();
	void OnRMouseButton();
	void OnSapcePress();

	void HideAllButton();


	void MoveOutEffect();
	void MoveInEffect();

	int		GetPosY();
private:
	TutorialType	m_eTutorialType;

	bool			m_bUpPressed;
	bool			m_bDowPressed;
	bool			m_bLeftPressed;
	bool			m_bRightPressed;


	MovePair		m_movePair;
	ControlPicture*	m_pID_PICTURE_And;
};
extern CUI_ID_FRAME_TutorialBox s_CUI_ID_FRAME_TutorialBox;
