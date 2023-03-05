
/********************************************************************
Created by UIEditor.exe
FileName: F:\sanguo\Data\Ui\HeroInfo.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_HeroInfo
#define ID_FRAME_HeroInfo		"ID_FRAME_HeroInfo"
#endif  ID_FRAME_HeroInfo
#ifndef ID_PICTURE_touxiang
#define ID_PICTURE_touxiang		"ID_PICTURE_touxiang"
#endif  ID_PICTURE_touxiang
#ifndef ID_PICTURE_ability
#define ID_PICTURE_ability		"ID_PICTURE_ability"
#endif  ID_PICTURE_ability
#ifndef ID_TEXT_introduce
#define ID_TEXT_introduce		"ID_TEXT_introduce"
#endif  ID_TEXT_introduce
#ifndef ID_PICTURE_warability
#define ID_PICTURE_warability		"ID_PICTURE_warability"
#endif  ID_PICTURE_warability
#ifndef ID_LISTIMG_skill
#define ID_LISTIMG_skill		"ID_LISTIMG_skill"
#endif  ID_LISTIMG_skill

class CUI_ID_FRAME_HeroInfo:public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_HeroInfo();
	ControlFrame*	m_pID_FRAME_HeroInfo;
	ControlPicture*	m_pID_PICTURE_touxiang;
	ControlPicture*	m_pID_PICTURE_ability;
	ControlText*	m_pID_TEXT_introduce;
	ControlPicture*	m_pID_PICTURE_warability;
	ControlListImage*	m_pID_LISTIMG_skill;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_skillOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_skillOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_skillOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_skillOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual bool IsHoldInMemory() const{return true;}
	virtual void InitializeAtEnterWorld();

	void Refresh();
	void Clear();

};
extern CUI_ID_FRAME_HeroInfo s_CUI_ID_FRAME_HeroInfo;
