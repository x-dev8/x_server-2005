/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\SettingEffect.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "Ui/UIBase.h"

#ifndef ID_FRAME_SettingEffect
#define ID_FRAME_SettingEffect		"ID_FRAME_SettingEffect"
#endif  ID_FRAME_SettingEffect
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Default
#define ID_BUTTON_Default		"ID_BUTTON_Default"
#endif  ID_BUTTON_Default
#ifndef ID_TEXT_Mode
#define ID_TEXT_Mode		"ID_TEXT_Mode"
#endif  ID_TEXT_Mode
#ifndef ID_SCROLLBAREX_Music
#define ID_SCROLLBAREX_Music		"ID_SCROLLBAREX_Music"
#endif  ID_SCROLLBAREX_Music
#ifndef ID_BUTTON_SetHigh
#define ID_BUTTON_SetHigh		"ID_BUTTON_SetHigh"
#endif  ID_BUTTON_SetHigh
#ifndef ID_BUTTON_SetMiddle
#define ID_BUTTON_SetMiddle		"ID_BUTTON_SetMiddle"
#endif  ID_BUTTON_SetMiddle
#ifndef ID_BUTTON_SetLow
#define ID_BUTTON_SetLow		"ID_BUTTON_SetLow"
#endif  ID_BUTTON_SetLow
#ifndef ID_CHECKBOX_Window
#define ID_CHECKBOX_Window		"ID_CHECKBOX_Window"
#endif  ID_CHECKBOX_Window
#ifndef ID_CHECKBOX_FullScreen
#define ID_CHECKBOX_FullScreen		"ID_CHECKBOX_FullScreen"
#endif  ID_CHECKBOX_FullScreen
#ifndef ID_CHECKBOX_NoMusic
#define ID_CHECKBOX_NoMusic		"ID_CHECKBOX_NoMusic"
#endif  ID_CHECKBOX_NoMusic
#ifndef ID_CHECKBOX_NoSoundEffect
#define ID_CHECKBOX_NoSoundEffect		"ID_CHECKBOX_NoSoundEffect"
#endif  ID_CHECKBOX_NoSoundEffect
// #ifndef ID_BUTTON_CLOSE
// #define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
// #endif  ID_BUTTON_CLOSE
// #ifndef ID_BUTTON_HELP
// #define ID_BUTTON_HELP		"ID_BUTTON_HELP"
// #endif  ID_BUTTON_HELP
#ifndef ID_BUTTON_Custom
#define ID_BUTTON_Custom		"ID_BUTTON_Custom"
#endif  ID_BUTTON_Custom
#ifndef ID_LIST_23209
#define ID_LIST_23209		"ID_LIST_23209"
#endif  ID_LIST_23209
#ifndef ID_SCROLLBAREX_SoundEffect
#define ID_SCROLLBAREX_SoundEffect		"ID_SCROLLBAREX_SoundEffect"
#endif  ID_SCROLLBAREX_SoundEffect
#ifndef ID_PICTURE_7314
#define ID_PICTURE_7314		"ID_PICTURE_7314"
#endif  ID_PICTURE_7314
#ifndef ID_SCROLLBAREX_TongPing
#define ID_SCROLLBAREX_TongPing		"ID_SCROLLBAREX_TongPing"
#endif  ID_SCROLLBAREX_TongPing
#ifndef ID_SCROLLBAREX_GuangJiao
#define ID_SCROLLBAREX_GuangJiao		"ID_SCROLLBAREX_GuangJiao"
#endif  ID_SCROLLBAREX_GuangJiao
#ifndef ID_SCROLLBAREX_JingTou
#define ID_SCROLLBAREX_JingTou		"ID_SCROLLBAREX_JingTou"
#endif  ID_SCROLLBAREX_JingTou
// #ifndef ID_CHECKBOX_Effect
// #define ID_CHECKBOX_Effect		"ID_CHECKBOX_Effect"
// #endif  ID_CHECKBOX_Effect
// #ifndef ID_CHECKBOX_GamePlay
// #define ID_CHECKBOX_GamePlay		"ID_CHECKBOX_GamePlay"
// #endif  ID_CHECKBOX_GamePlay
// #ifndef ID_CHECKBOX_ShortcutKey
// #define ID_CHECKBOX_ShortcutKey		"ID_CHECKBOX_ShortcutKey"
// #endif  ID_CHECKBOX_ShortcutKey
#ifndef ID_TEXT_23801231233
#define ID_TEXT_23801231233		"ID_TEXT_23801231233"
#endif  ID_TEXT_23801231233
#ifndef ID_TEXT_23821312303
#define ID_TEXT_23821312303		"ID_TEXT_23821312303"
#endif  ID_TEXT_23821312303
#ifndef ID_TEXT_212313803
#define ID_TEXT_212313803		"ID_TEXT_212313803"
#endif  ID_TEXT_212313803
#ifndef ID_TEXT_238031231
#define ID_TEXT_238031231		"ID_TEXT_238031231"
#endif  ID_TEXT_238031231
#ifndef ID_TEXT_238031233
#define ID_TEXT_238031233		"ID_TEXT_238031233"
#endif  ID_TEXT_238031233

#ifndef ID_COMBOBOX_MS
#define  ID_COMBOBOX_MS "ID_COMBOBOX_MS"
#endif ID_COMBOBOX_MS

#ifndef ID_CHECKBOX_CAMERA_SHAKE
#define  ID_CHECKBOX_CAMERA_SHAKE "ID_CHECKBOX_CAMERA_SHAKE"
#endif ID_CHECKBOX_CAMERA_SHAKE

class CUI_ID_FRAME_SettingEffect : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_SettingEffect();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DefaultOnButtonClick( ControlObject* pSender );
	void ID_SCROLLBAREX_MusicOnScrollBarExUpdatePos( ControlObject* pSender, int n );
	bool ID_BUTTON_SetHighOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SetMiddleOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SetLowOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_WindowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_FullScreenOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_NoMusicOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_NoSoundEffectOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
/*	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );*/
	bool ID_BUTTON_CustomOnButtonClick( ControlObject* pSender );
	void ID_LIST_23209OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_SCROLLBAREX_SoundEffectOnScrollBarExUpdatePos( ControlObject* pSender, int n );
	void ID_SCROLLBAREX_TongPingOnScrollBarExUpdatePos( ControlObject* pSender, int n );
	void ID_SCROLLBAREX_GuangJiaoOnScrollBarExUpdatePos( ControlObject* pSender, int n );
	void ID_SCROLLBAREX_JingTouOnScrollBarExUpdatePos( ControlObject* pSender, int n );
// 	void ID_CHECKBOX_EffectOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
// 	void ID_CHECKBOX_GamePlayOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
// 	void ID_CHECKBOX_ShortcutKeyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
/*	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender);*/
	void ID_COMBOBOX_MSOnComboboxChange(ControlObject* pSender, const char* szData);
	void ID_CHECKBOX_CameraShakeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked );

	void GetItemTextByMSAALevel(int msaaLevel, char *szItemText);

	ControlFrame * GetFrame() { return m_pID_FRAME_SettingEffect; }
public:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
private:
	ControlFrame*	m_pID_FRAME_SettingEffect;
	ControlButton*	m_pID_BUTTON_OK;
	ControlButton*	m_pID_BUTTON_Cancel;
	ControlButton*	m_pID_BUTTON_Default;
	ControlText*	m_pID_TEXT_Mode;
	ControlScrollBarEx*	m_pID_SCROLLBAREX_Music;
	ControlButton*	m_pID_BUTTON_SetHigh;
	ControlButton*	m_pID_BUTTON_SetMiddle;
	ControlButton*	m_pID_BUTTON_SetLow;
	ControlCheckBox*	m_pID_CHECKBOX_Window;
	ControlCheckBox*	m_pID_CHECKBOX_FullScreen;
	ControlCheckBox*	m_pID_CHECKBOX_NoMusic;
	ControlCheckBox*	m_pID_CHECKBOX_NoSoundEffect;
/*	ControlButton*	m_pID_BUTTON_CLOSE;*/
	ControlButton*	m_pID_BUTTON_Custom;
	ControlList*	m_pID_LIST_23209;
	ControlScrollBarEx*	m_pID_SCROLLBAREX_SoundEffect;
	ControlPicture*	m_pID_PICTURE_7314;
/*	ControlButton*	m_pID_BUTTON_HELP;*/
	ControlScrollBarEx*	m_pID_SCROLLBAREX_TongPing;
	ControlScrollBarEx*	m_pID_SCROLLBAREX_GuangJiao;
	ControlScrollBarEx*	m_pID_SCROLLBAREX_JingTou;
// 	ControlCheckBox*	m_pID_CHECKBOX_Effect;
// 	ControlCheckBox*	m_pID_CHECKBOX_GamePlay;
// 	ControlCheckBox*	m_pID_CHECKBOX_ShortcutKey;
	ControlText*	m_pID_TEXT_23801231233;
	ControlText*	m_pID_TEXT_23821312303;
	ControlText*	m_pID_TEXT_212313803;
	ControlText*	m_pID_TEXT_238031231;
	ControlText*	m_pID_TEXT_238031233;
	ControlComboBox* m_pID_COMBOBOX_MultiSample;
	ControlCheckBox* m_pID_CHECKBOX_CameraShake;

public:
	enum eQuility
	{
		eQuility_High, //高品质
		eQuility_Middle, //中品质
		eQuility_Low,    //低品质
		eQuility_Custom  //自定义
	};
	void Refresh(bool bResolution = true);	
	void AddResolutionString( const char* pszReslution );
	void LoadQuilityConfig(eQuility eValue);
public:
	static void ID_LIST_SELECTOnListDBClick( ControlObject* pSender, ControlList::S_List* pItem );
private:
	static int m_ScreenValue;    //用来保存当前分辨率的值
	ControlGroup		*m_EffectGroup; //效果设置
	ControlGroup		*m_GameGroup; //游戏性设置
	ControlGroup		*m_KeyGroup;    //快捷键
public:
	void SetScrollBarFov(int nValue);
};
extern CUI_ID_FRAME_SettingEffect s_CUI_ID_FRAME_SettingEffect;
