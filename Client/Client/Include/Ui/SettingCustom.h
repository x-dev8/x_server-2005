/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\Ui\SettingCustom.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_SettingCustom
#define ID_FRAME_SettingCustom		"ID_FRAME_SettingCustom"
#endif  ID_FRAME_SettingCustom
#ifndef ID_PICTURE_Di
#define ID_PICTURE_Di		"ID_PICTURE_Di"
#endif  ID_PICTURE_Di
#ifndef ID_BUTTON_Minimize
#define ID_BUTTON_Minimize		"ID_BUTTON_Minimize"
#endif  ID_BUTTON_Minimize
#ifndef ID_CHECKBOX_LightLow
#define ID_CHECKBOX_LightLow		"ID_CHECKBOX_LightLow"
#endif  ID_CHECKBOX_LightLow
#ifndef ID_BUTTON_Clear
#define ID_BUTTON_Clear		"ID_BUTTON_Clear"
#endif  ID_BUTTON_Clear
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_CHECKBOX_LightHigh
#define ID_CHECKBOX_LightHigh		"ID_CHECKBOX_LightHigh"
#endif  ID_CHECKBOX_LightHigh
#ifndef ID_CHECKBOX_GroundLow
#define ID_CHECKBOX_GroundLow		"ID_CHECKBOX_GroundLow"
#endif  ID_CHECKBOX_GroundLow
#ifndef ID_CHECKBOX_TextureLow
#define ID_CHECKBOX_TextureLow		"ID_CHECKBOX_TextureLow"
#endif  ID_CHECKBOX_TextureLow
#ifndef ID_CHECKBOX_ActionLow
#define ID_CHECKBOX_ActionLow		"ID_CHECKBOX_ActionLow"
#endif  ID_CHECKBOX_ActionLow
#ifndef ID_CHECKBOX_WaterLow
#define ID_CHECKBOX_WaterLow		"ID_CHECKBOX_WaterLow"
#endif  ID_CHECKBOX_WaterLow
#ifndef ID_CHECKBOX_GrassLow
#define ID_CHECKBOX_GrassLow		"ID_CHECKBOX_GrassLow"
#endif  ID_CHECKBOX_GrassLow
#ifndef ID_CHECKBOX_GroundHigh
#define ID_CHECKBOX_GroundHigh		"ID_CHECKBOX_GroundHigh"
#endif  ID_CHECKBOX_GroundHigh
#ifndef ID_CHECKBOX_TextureHigh
#define ID_CHECKBOX_TextureHigh		"ID_CHECKBOX_TextureHigh"
#endif  ID_CHECKBOX_TextureHigh
#ifndef ID_CHECKBOX_ActionHigh
#define ID_CHECKBOX_ActionHigh		"ID_CHECKBOX_ActionHigh"
#endif  ID_CHECKBOX_ActionHigh
#ifndef ID_CHECKBOX_WaterHigh
#define ID_CHECKBOX_WaterHigh		"ID_CHECKBOX_WaterHigh"
#endif  ID_CHECKBOX_WaterHigh
#ifndef ID_CHECKBOX_GrassHigh
#define ID_CHECKBOX_GrassHigh		"ID_CHECKBOX_GrassHigh"
#endif  ID_CHECKBOX_GrassHigh
#ifndef ID_CHECKBOX_ShadowLow
#define ID_CHECKBOX_ShadowLow		"ID_CHECKBOX_ShadowLow"
#endif  ID_CHECKBOX_ShadowLow
#ifndef ID_CHECKBOX_ShadowMiddle
#define ID_CHECKBOX_ShadowMiddle		"ID_CHECKBOX_ShadowMiddle"
#endif  ID_CHECKBOX_ShadowMiddle
#ifndef ID_CHECKBOX_ShadowHigh
#define ID_CHECKBOX_ShadowHigh		"ID_CHECKBOX_ShadowHigh"
#endif  ID_CHECKBOX_ShadowHigh
#ifndef ID_CHECKBOX_EffectLow
#define ID_CHECKBOX_EffectLow		"ID_CHECKBOX_EffectLow"
#endif  ID_CHECKBOX_EffectLow
#ifndef ID_CHECKBOX_EffecMiddle
#define ID_CHECKBOX_EffecMiddle		"ID_CHECKBOX_EffecMiddle"
#endif  ID_CHECKBOX_EffecMiddle
#ifndef ID_CHECKBOX_EffectHigh
#define ID_CHECKBOX_EffectHigh		"ID_CHECKBOX_EffectHigh"
#endif  ID_CHECKBOX_EffectHigh
#ifndef ID_CHECKBOX_YinMiddle
#define ID_CHECKBOX_YinMiddle "ID_CHECKBOX_YinMiddle"
#endif ID_CHECKBOX_YinMiddle
#ifndef ID_CHECKBOX_YinLow
#define ID_CHECKBOX_YinLow "ID_CHECKBOX_YinLow"
#endif ID_CHECKBOX_YinLow
#ifndef ID_CHECKBOX_YinHigh
#define  ID_CHECKBOX_YinHigh "ID_CHECKBOX_YinHigh"
#endif ID_CHECKBOX_YinHigh

//lyh++ 下列四个控件 ，分别控制 hdr 的开关 和 地形凹凸纹理映射的开关
#ifndef ID_CHECKBOX_HdrOff
#define  ID_CHECKBOX_HdrOff "ID_CHECKBOX_HdrOff"
#endif ID_CHECKBOX_HdrOff

#ifndef ID_CHECKBOX_HdrOn
#define ID_CHECKBOX_HdrOn "ID_CHECKBOX_HdrOn"
#endif ID_CHECKBOX_HdrOn

#ifndef ID_CHECKBOX_TerrainAOTUOff
#define  ID_CHECKBOX_TerrainAOTUOff "ID_CHECKBOX_TerrainAOTUOff"
#endif ID_CHECKBOX_TerrainAOTUOff

#ifndef ID_CHECKBOX_TerrainAOTUOn
#define  ID_CHECKBOX_TerrainAOTUOn "ID_CHECKBOX_TerrainAOTUOn"
#endif ID_CHECKBOX_TerrainAOTUOn






class CUI_ID_FRAME_SettingCustom
{
	// Member
public:	
	 CUI_ID_FRAME_SettingCustom();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_MinimizeOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_LightLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_ClearOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_LightHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_GroundLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_TextureLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_ActionLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_WaterLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_GrassLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_GroundHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_TextureHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_ActionHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_WaterHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_GrassHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_ShadowLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_ShadowMiddleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_ShadowHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_EffectLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_EffecMiddleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_EffectHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_YinMiddleOnCheckBoxCheck(ControlObject* pSender, bool* pbChecked);
	void ID_CHECKBOX_YinLowOnCheckBoxCheck(ControlObject* pSender, bool* pbChecked);
	void ID_CHECKBOX_YinHighOnCheckBoxCheck(ControlObject* pSender, bool* pbChecked);

	void ID_CHECKBOX_HdrOnOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_HdrOffOnCheckBoxCheck(ControlObject* pSender, bool* pbChecked);
	void ID_CHECKBOX_TerrainAOTUOffOnCheckBoxCheck(ControlObject* pSender, bool* pbChecked);
	void ID_CHECKBOX_TerrainAOTUOnOnCheckBoxCheck(ControlObject* pSender, bool* pbChecked);


	bool LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool UnLoadUI();			// 卸载UI
	bool IsVisable();			// 是否可见
	void SetVisable( const bool bVisable );			// 设置是否可视


private:

	ControlCheckBox*	m_pID_CHECKBOX_HdrOn;
	ControlCheckBox*	m_pID_CHECKBOX_HdrOff;
	ControlCheckBox*	m_pID_CHECKBOX_TerrainAOTUOff;
	ControlCheckBox*	m_pID_CHECKBOX_TerrainAOTUOn;


	ControlFrame*	m_pID_FRAME_SettingCustom;
	ControlPicture*	m_pID_PICTURE_Di;
	ControlButton*	m_pID_BUTTON_Minimize;
	ControlCheckBox*	m_pID_CHECKBOX_LightLow;
	ControlButton*	m_pID_BUTTON_Clear;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlButton*	m_pID_BUTTON_Ok;
	ControlCheckBox*	m_pID_CHECKBOX_LightHigh;
	ControlCheckBox*	m_pID_CHECKBOX_GroundLow;
	ControlCheckBox*	m_pID_CHECKBOX_TextureLow;
	ControlCheckBox*	m_pID_CHECKBOX_ActionLow;
	ControlCheckBox*	m_pID_CHECKBOX_WaterLow;
	ControlCheckBox*	m_pID_CHECKBOX_GrassLow;
	ControlCheckBox*	m_pID_CHECKBOX_GroundHigh;
	ControlCheckBox*	m_pID_CHECKBOX_TextureHigh;
	ControlCheckBox*	m_pID_CHECKBOX_ActionHigh;
	ControlCheckBox*	m_pID_CHECKBOX_WaterHigh;
	ControlCheckBox*	m_pID_CHECKBOX_GrassHigh;
	ControlCheckBox*	m_pID_CHECKBOX_ShadowLow;
	ControlCheckBox*	m_pID_CHECKBOX_ShadowMiddle;
	ControlCheckBox*	m_pID_CHECKBOX_ShadowHigh;
	ControlCheckBox*	m_pID_CHECKBOX_EffectLow;
	ControlCheckBox*	m_pID_CHECKBOX_EffecMiddle;
	ControlCheckBox*	m_pID_CHECKBOX_EffectHigh;
	ControlCheckBox*	m_pID_CHECKBOX_YinMiddle;
	ControlCheckBox*	m_pID_CHECKBOX_YinLow;
	ControlCheckBox*	m_pID_CHECKBOX_YinHigh;




public:
	void Refersh();
};
extern CUI_ID_FRAME_SettingCustom s_CUI_ID_FRAME_SettingCustom;
