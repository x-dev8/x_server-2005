/********************************************************************
	Created by UIEditor.exe
	FileName: E:\trunk\Bin\Client\Data\Ui\BasePropertyBGFrame.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_BasePropertyBGFrame
#define ID_FRAME_BasePropertyBGFrame		"ID_FRAME_BasePropertyBGFrame"
#endif  ID_FRAME_BasePropertyBGFrame
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_CHECKBOX_ShuXing
#define ID_CHECKBOX_ShuXing		"ID_CHECKBOX_ShuXing"
#endif  ID_CHECKBOX_ShuXing
#ifndef ID_CHECKBOX_ZiLiao
#define ID_CHECKBOX_ZiLiao		"ID_CHECKBOX_ZiLiao"
#endif  ID_CHECKBOX_ZiLiao
#ifndef ID_CHECKBOX_Other
#define ID_CHECKBOX_Other		"ID_CHECKBOX_Other"
#endif  ID_CHECKBOX_Other
#ifndef ID_PICTURE_ShuXing
#define ID_PICTURE_ShuXing		"ID_PICTURE_ShuXing"
#endif  ID_PICTURE_ShuXing
#ifndef ID_PICTURE_ZiLiao
#define ID_PICTURE_ZiLiao		"ID_PICTURE_ZiLiao"
#endif  ID_PICTURE_ZiLiao
#ifndef ID_PICTURE_Other
#define ID_PICTURE_Other		"ID_PICTURE_Other"
#endif  ID_PICTURE_Other
#ifndef ID_PICTURE_HeadPic
#define ID_PICTURE_HeadPic		"ID_PICTURE_HeadPic"
#endif  ID_PICTURE_HeadPic
#ifndef ID_CHECKBOX_Rank
#define ID_CHECKBOX_Rank		"ID_CHECKBOX_Rank"
#endif  ID_CHECKBOX_Rank

class CUI_ID_FRAME_BasePropertyBGFrame : public CUIBase
{
	// Member
private:	
	 ControlFrame*	m_pID_FRAME_BasePropertyBGFrame;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlCheckBox*	m_pID_CHECKBOX_ShuXing;
	 ControlCheckBox*	m_pID_CHECKBOX_ZiLiao;
	 ControlCheckBox*	m_pID_CHECKBOX_Other;
	 ControlPicture*	m_pID_PICTURE_ShuXing;
	 ControlPicture*	m_pID_PICTURE_ZiLiao;
	 ControlPicture*	m_pID_PICTURE_Other;
	 ControlPicture*	m_pID_PICTURE_HeadPic;
	 ControlCheckBox*	m_pID_CHECKBOX_Rank;
public:	
	// Frame
	CUI_ID_FRAME_BasePropertyBGFrame();
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_ShuXingOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_ZiLiaoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_OtherOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	//void ID_CHECKBOX_HeroOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_RankOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视
	ControlFrame *GetFrame() { return m_pID_FRAME_BasePropertyBGFrame;}
	virtual bool IsHoldInMemory() const { return true; }
	virtual void InitializeAtEnterWorld();
private:	
};
extern CUI_ID_FRAME_BasePropertyBGFrame s_CUI_ID_FRAME_BasePropertyBGFrame;
