#pragma once
#include "MeUi/MeUi.h"
#include "../GuildIcon.h"
#include "Guild_Create.h"

#ifndef ID_FRAME_Guild_Pic
#define ID_FRAME_Guild_Pic		"ID_FRAME_Guild_Pic"
#endif  ID_FRAME_Guild_Pic
#ifndef ID_PICTURE_12234
#define ID_PICTURE_12234		"ID_PICTURE_12234"
#endif  ID_PICTURE_12234
#ifndef ID_BUTTON_COMFIRM
#define ID_BUTTON_COMFIRM		"ID_BUTTON_COMFIRM"
#endif  ID_BUTTON_COMFIRM
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_PICTURE_20150
#define ID_PICTURE_20150		"ID_PICTURE_20150"
#endif  ID_PICTURE_20150
#ifndef ID_PICTURE_12235
#define ID_PICTURE_12235		"ID_PICTURE_12235"
#endif  ID_PICTURE_12235
#ifndef ID_LIST_TextList
#define ID_LIST_TextList		"ID_LIST_TextList"
#endif  ID_LIST_TextList
#ifndef ID_PICTURE_10413
#define ID_PICTURE_10413		"ID_PICTURE_10413"
#endif  ID_PICTURE_10413
#ifndef ID_PICTURE_Image
#define ID_PICTURE_Image		"ID_PICTURE_Image"
#endif  ID_PICTURE_Image
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#include "UiBase.h"
class CUI_ID_FRAME_Guild_Pic :public CUIBase
{
	// SGuildMember
public:	

	CUI_ID_FRAME_Guild_Pic();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_COMFIRMOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	void ID_LIST_TextListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


public:
	int			index;
	FileIO::CFileSearch::FileList	 flst;
private:
    ControlFrame*		m_pID_FRAME_Guild_Pic;
    ControlPicture*	m_pID_PICTURE_12234;
    ControlButton*	m_pID_BUTTON_COMFIRM;
    ControlButton*	m_pID_BUTTON_Cancel;
    ControlPicture*	m_pID_PICTURE_20150;
    ControlPicture*	m_pID_PICTURE_12235;
    ControlList*			m_pID_LIST_TextList;
    ControlPicture*	m_pID_PICTURE_10413;
    ControlPicture*	m_pID_PICTURE_Image;
    ControlButton*	m_pID_BUTTON_CLOSE;
};


extern CUI_ID_FRAME_Guild_Pic s_CUI_ID_FRAME_Guild_Pic;
