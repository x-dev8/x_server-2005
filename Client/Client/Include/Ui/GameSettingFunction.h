/********************************************************************
	Created by UIEditor.exe
	FileName: D:\My Documents\桌面\gamesetting\GameSettingFunction.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GameSettingFunction
#define ID_FRAME_GameSettingFunction		"ID_FRAME_GameSettingFunction"
#endif  ID_FRAME_GameSettingFunction
#ifndef ID_TEXT_ScreenPlayerNumber
#define ID_TEXT_ScreenPlayerNumber		"ID_TEXT_ScreenPlayerNumber"
#endif  ID_TEXT_ScreenPlayerNumber
#ifndef ID_TEXT_Fov
#define ID_TEXT_Fov		"ID_TEXT_Fov"
#endif  ID_TEXT_Fov
#ifndef ID_TEXT_CameraMaxDistance
#define ID_TEXT_CameraMaxDistance		"ID_TEXT_CameraMaxDistance"
#endif  ID_TEXT_CameraMaxDistance
#ifndef ID_TEXT_Weisui
#define ID_TEXT_Weisui		"ID_TEXT_Weisui"
#endif  ID_TEXT_Weisui
#ifndef ID_CHECKBOX_Weisui
#define ID_CHECKBOX_Weisui		"ID_CHECKBOX_Weisui"
#endif  ID_CHECKBOX_Weisui
#ifndef ID_SCROLLBAREX_ScreenPlayerNumber
#define ID_SCROLLBAREX_ScreenPlayerNumber		"ID_SCROLLBAREX_ScreenPlayerNumber"
#endif  ID_SCROLLBAREX_ScreenPlayerNumber
#ifndef ID_SCROLLBAREX_Fov
#define ID_SCROLLBAREX_Fov		"ID_SCROLLBAREX_Fov"
#endif  ID_SCROLLBAREX_Fov
#ifndef ID_SCROLLBAREX_CameraMaxDistance
#define ID_SCROLLBAREX_CameraMaxDistance		"ID_SCROLLBAREX_CameraMaxDistance"
#endif  ID_SCROLLBAREX_CameraMaxDistance
#ifndef ID_TEXT_VerticleView
#define ID_TEXT_VerticleView		"ID_TEXT_VerticleView"
#endif  ID_TEXT_VerticleView
#ifndef ID_TEXT_ShowHelmet
#define ID_TEXT_ShowHelmet		"ID_TEXT_ShowHelmet"
#endif  ID_TEXT_ShowHelmet
#ifndef ID_TEXT_Suo45
#define ID_TEXT_Suo45		"ID_TEXT_Suo45"
#endif  ID_TEXT_Suo45
#ifndef ID_CHECKBOX_VerticleView
#define ID_CHECKBOX_VerticleView		"ID_CHECKBOX_VerticleView"
#endif  ID_CHECKBOX_VerticleView
#ifndef ID_CHECKBOX_ShowHelmet
#define ID_CHECKBOX_ShowHelmet		"ID_CHECKBOX_ShowHelmet"
#endif  ID_CHECKBOX_ShowHelmet
#ifndef ID_CHECKBOX_Suo45
#define ID_CHECKBOX_Suo45		"ID_CHECKBOX_Suo45"
#endif  ID_CHECKBOX_Suo45
#ifndef ID_TEXT_Help
#define ID_TEXT_Help		"ID_TEXT_Help"
#endif  ID_TEXT_Help
#ifndef ID_CHECKBOX_Help
#define ID_CHECKBOX_Help		"ID_CHECKBOX_Help"
#endif  ID_CHECKBOX_Help
#ifndef ID_TEXT_LockMain
#define ID_TEXT_LockMain		"ID_TEXT_LockMain"
#endif  ID_TEXT_LockMain
#ifndef ID_CHECKBOX_LockMain
#define ID_CHECKBOX_LockMain		"ID_CHECKBOX_LockMain"
#endif  ID_CHECKBOX_LockMain

#include "UiBase.h"
class CUI_ID_FRAME_GameSettingFunction :public CUIBase
{
	// Member
public:	
    CUI_ID_FRAME_GameSettingFunction();
    // Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_WeisuiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_SCROLLBAREX_ScreenPlayerNumberOnScrollBarExUpdatePos( ControlObject* pSender, int n );
	void ID_SCROLLBAREX_FovOnScrollBarExUpdatePos( ControlObject* pSender, int n );
	void ID_SCROLLBAREX_CameraMaxDistanceOnScrollBarExUpdatePos( ControlObject* pSender, int n );
	void ID_CHECKBOX_VerticleViewOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_ShowHelmetOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Suo45OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_HelpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_ChangeEquipOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_LockMainOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


    void RefreshUI();

    ControlCheckBox* GetLockMainCheckBox(){return m_pID_CHECKBOX_LockMain;}
    ControlCheckBox* GetHelpCheckBox(){return m_pID_CHECKBOX_Help;}
    ControlFrame*    GetFrame(){return m_pID_FRAME_GameSettingFunction;}

private:
    ControlFrame*	m_pID_FRAME_GameSettingFunction;
    ControlText*	m_pID_TEXT_ScreenPlayerNumber;
    ControlText*	m_pID_TEXT_Fov;
    ControlText*	m_pID_TEXT_CameraMaxDistance;
    ControlText*	m_pID_TEXT_Weisui;
    ControlCheckBox*	m_pID_CHECKBOX_Weisui;
    ControlScrollBarEx*	m_pID_SCROLLBAREX_ScreenPlayerNumber;
    ControlScrollBarEx*	m_pID_SCROLLBAREX_Fov;
    ControlScrollBarEx*	m_pID_SCROLLBAREX_CameraMaxDistance;
    ControlText*	m_pID_TEXT_VerticleView;
    ControlText*	m_pID_TEXT_ShowHelmet;
    ControlText*	m_pID_TEXT_Suo45;
    ControlCheckBox*	m_pID_CHECKBOX_VerticleView;
    ControlCheckBox*	m_pID_CHECKBOX_ShowHelmet;
    ControlCheckBox*	m_pID_CHECKBOX_Suo45;
    ControlText*	m_pID_TEXT_Help;
    ControlCheckBox*	m_pID_CHECKBOX_Help;
    //     ControlText*	m_pID_TEXT_ChangeEquip;
    ControlText*	m_pID_TEXT_LockMain;
    ControlCheckBox*	m_pID_CHECKBOX_LockMain;
};
extern CUI_ID_FRAME_GameSettingFunction s_CUI_ID_FRAME_GameSettingFunction;
