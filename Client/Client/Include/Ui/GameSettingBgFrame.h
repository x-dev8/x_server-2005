/********************************************************************
	Created by UIEditor.exe
	FileName: E:\trunk\Bin\Client\Data\Ui\GameSettingBgFrame.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_GameSettingBgFrame
#define ID_FRAME_GameSettingBgFrame		"ID_FRAME_GameSettingBgFrame"
#endif  ID_FRAME_GameSettingBgFrame
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_CHECKBOX_Effect
#define ID_CHECKBOX_Effect		"ID_CHECKBOX_Effect"
#endif  ID_CHECKBOX_Effect
#ifndef ID_CHECKBOX_GamePlay
#define ID_CHECKBOX_GamePlay		"ID_CHECKBOX_GamePlay"
#endif  ID_CHECKBOX_GamePlay
#ifndef ID_CHECKBOX_ShortcutKey
#define ID_CHECKBOX_ShortcutKey		"ID_CHECKBOX_ShortcutKey"
#endif  ID_CHECKBOX_ShortcutKey
#ifndef ID_PICTURE_GamePlay
#define ID_PICTURE_GamePlay		"ID_PICTURE_GamePlay"
#endif  ID_PICTURE_GamePlay
#ifndef ID_PICTURE_ShortcutKey
#define ID_PICTURE_ShortcutKey		"ID_PICTURE_ShortcutKey"
#endif  ID_PICTURE_ShortcutKey
#ifndef ID_PICTURE_Effect
#define ID_PICTURE_Effect		"ID_PICTURE_Effect"
#endif  ID_PICTURE_Effect

class CUI_ID_FRAME_GameSettingBgFrame:public CUIBase
{
	// Member
private:	

	 ControlFrame*	m_pID_FRAME_GameSettingBgFrame;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlCheckBox*	m_pID_CHECKBOX_Effect;
	 ControlCheckBox*	m_pID_CHECKBOX_GamePlay;
	 ControlCheckBox*	m_pID_CHECKBOX_ShortcutKey;
	 ControlPicture*	m_pID_PICTURE_GamePlay;
	 ControlPicture*	m_pID_PICTURE_ShortcutKey;
	 ControlPicture*	m_pID_PICTURE_Effect;
public:	
	// Frame
	CUI_ID_FRAME_GameSettingBgFrame();
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_EffectOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_GamePlayOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_ShortcutKeyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视
	ControlFrame *GetFrame() { return m_pID_FRAME_GameSettingBgFrame;}
	virtual void InitializeAtEnterWorld();
private:	
};
extern CUI_ID_FRAME_GameSettingBgFrame s_CUI_ID_FRAME_GameSettingBgFrame;
