/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\GroupPanel.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GroupPanel
#define ID_FRAME_GroupPanel		"ID_FRAME_GroupPanel"
#endif  ID_FRAME_GroupPanel
#ifndef ID_PICTURE_Di
#define ID_PICTURE_Di		"ID_PICTURE_Di"
#endif  ID_PICTURE_Di
#ifndef ID_PICTURE_Title
#define ID_PICTURE_Title		"ID_PICTURE_Title"
#endif  ID_PICTURE_Title
#ifndef ID_PICTURE_Fenge
#define ID_PICTURE_Fenge		"ID_PICTURE_Fenge"
#endif  ID_PICTURE_Fenge
#ifndef ID_CHECKBOX_Fujin
#define ID_CHECKBOX_Fujin		"ID_CHECKBOX_Fujin"
#endif  ID_CHECKBOX_Fujin
#ifndef ID_CHECKBOX_Xunzhao
#define ID_CHECKBOX_Xunzhao		"ID_CHECKBOX_Xunzhao"
#endif  ID_CHECKBOX_Xunzhao
#ifndef ID_CHECKBOX_Tongchen
#define ID_CHECKBOX_Tongchen		"ID_CHECKBOX_Tongchen"
#endif  ID_CHECKBOX_Tongchen
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help

#include "UiBase.h"
class CUI_ID_FRAME_GroupPanel :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_GroupPanel();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_FujinOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_XunzhaoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_TongchenOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


    ControlCheckBox* GetGroupSelect(){if(!m_pID_FRAME_GroupPanel) return NULL;return m_optionGroup.GetSelectRadio();}

    ControlCheckBox* GetFuJinCheckBox(){if(!m_pID_FRAME_GroupPanel) return NULL;return m_pID_CHECKBOX_Fujin;}
    ControlCheckBox* GetCheckBoxXunZhao(){if(!m_pID_FRAME_GroupPanel) return NULL;return m_pID_CHECKBOX_Xunzhao;}
    ControlCheckBox* GetCheckBoxTongchen(){if(!m_pID_FRAME_GroupPanel) return NULL;return m_pID_CHECKBOX_Tongchen;}

	static void OnVisibleChanged(ControlObject* pUIObject);
private:
    ControlFrame*	m_pID_FRAME_GroupPanel;
    ControlPicture*	m_pID_PICTURE_Di;
    ControlPicture*	m_pID_PICTURE_Title;
    ControlPicture*	m_pID_PICTURE_Fenge;
    ControlCheckBox*	m_pID_CHECKBOX_Fujin;
    ControlCheckBox*	m_pID_CHECKBOX_Xunzhao;
    ControlCheckBox*	m_pID_CHECKBOX_Tongchen;
    ControlButton*	m_pID_BUTTON_CLOSE;
    ControlButton*	m_pID_BUTTON_help;

    ControlRadioGroup m_optionGroup;
};
extern CUI_ID_FRAME_GroupPanel s_CUI_ID_FRAME_GroupPanel;
