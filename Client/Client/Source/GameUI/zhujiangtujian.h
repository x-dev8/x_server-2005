/********************************************************************
	Created by UIEditor.exe
	FileName: F:\3Guo Client\Data\Ui\zhujiangtujian.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_zhujiangtujian
#define ID_FRAME_zhujiangtujian		"ID_FRAME_zhujiangtujian"
#endif  ID_FRAME_zhujiangtujian
#ifndef ID_PICTURE_zhujiangtouxiang
#define ID_PICTURE_zhujiangtouxiang		"ID_PICTURE_zhujiangtouxiang"
#endif  ID_PICTURE_zhujiangtouxiang
#ifndef ID_PICTURE_nameLV
#define ID_PICTURE_nameLV		"ID_PICTURE_nameLV"
#endif  ID_PICTURE_nameLV
#ifndef ID_TEXT_jieshao
#define ID_TEXT_jieshao		"ID_TEXT_jieshao"
#endif  ID_TEXT_jieshao
#ifndef ID_PICTURE_ability
#define ID_PICTURE_ability		"ID_PICTURE_ability"
#endif  ID_PICTURE_ability
#ifndef ID_LISTIMG_skill
#define ID_LISTIMG_skill		"ID_LISTIMG_skill"
#endif  ID_LISTIMG_skill
#ifndef ID_PICTURE_warability
#define ID_PICTURE_warability		"ID_PICTURE_warability"
#endif  ID_PICTURE_warability
#ifndef ID_BUTTON_close
#define ID_BUTTON_close		"ID_BUTTON_close"
#endif  ID_BUTTON_close

#include "UiBase.h"

class CUI_ID_FRAME_zhujiangtujian:public CUIBase
{
	// Member  
public:	
	 CUI_ID_FRAME_zhujiangtujian();
	 ControlFrame*	m_pID_FRAME_zhujiangtujian;
	 ControlPicture*	m_pID_PICTURE_zhujiangtouxiang;
	 ControlPicture*	m_pID_PICTURE_nameLV;
	 ControlText*	m_pID_TEXT_jieshao;
	 ControlPicture*	m_pID_PICTURE_ability;
	 ControlListImage*	m_pID_LISTIMG_skill;
	 ControlPicture*	m_pID_PICTURE_warability;
	 ControlButton*	m_pID_BUTTON_close;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_skillOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_skillOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_skillOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_skillOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_closeOnButtonClick( ControlObject* pSender );

	//bool LoadUI();				// 载入UI
	//bool DoControlConnect();	// 关连控件
	//bool UnLoadUI();			// 卸载UI
	//bool IsVisable();			// 是否可见
	//void SetVisable( const bool bVisable );			// 设置是否可视

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual bool IsHoldInMemory() const { return true; }
	virtual void InitializeAtEnterWorld();
public:
	void Refresh();
	void SetItemId(uint16 id){item_id = id;}
	bool clear();
private:
	uint16 item_id;
};
extern CUI_ID_FRAME_zhujiangtujian s_CUI_ID_FRAME_zhujiangtujian;
