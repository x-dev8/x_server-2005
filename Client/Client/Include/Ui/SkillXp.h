/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\SkillXp.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_XpSkill
#define ID_FRAME_XpSkill		"ID_FRAME_XpSkill"
#endif  ID_FRAME_XpSkill
#ifndef ID_PICTURE_SkillBack
#define ID_PICTURE_SkillBack		"ID_PICTURE_SkillBack"
#endif  ID_PICTURE_SkillBack
#ifndef ID_LISTIMG_Skill1
#define ID_LISTIMG_Skill1		"ID_LISTIMG_Skill1"
#endif  ID_LISTIMG_Skill1
#ifndef ID_LISTIMG_Skill2
#define ID_LISTIMG_Skill2		"ID_LISTIMG_Skill2"
#endif  ID_LISTIMG_Skill2
#ifndef ID_LISTIMG_Skill3
#define ID_LISTIMG_Skill3		"ID_LISTIMG_Skill3"
#endif  ID_LISTIMG_Skill3
#ifndef ID_LISTIMG_Skill4
#define ID_LISTIMG_Skill4		"ID_LISTIMG_Skill4"
#endif  ID_LISTIMG_Skill4
#ifndef ID_LISTIMG_Skill5
#define ID_LISTIMG_Skill5		"ID_LISTIMG_Skill5"
#endif  ID_LISTIMG_Skill5
#ifndef ID_LISTIMG_Skill6
#define ID_LISTIMG_Skill6		"ID_LISTIMG_Skill6"
#endif  ID_LISTIMG_Skill6
#ifndef ID_LISTIMG_Skill7
#define ID_LISTIMG_Skill7		"ID_LISTIMG_Skill7"
#endif  ID_LISTIMG_Skill7
#ifndef ID_TEXT_SkillText1
#define ID_TEXT_SkillText1		"ID_TEXT_SkillText1"
#endif  ID_TEXT_SkillText1
#ifndef ID_TEXT_SkillText2
#define ID_TEXT_SkillText2		"ID_TEXT_SkillText2"
#endif  ID_TEXT_SkillText2
#ifndef ID_TEXT_SkillText3
#define ID_TEXT_SkillText3		"ID_TEXT_SkillText3"
#endif  ID_TEXT_SkillText3
#ifndef ID_TEXT_SkillText4
#define ID_TEXT_SkillText4		"ID_TEXT_SkillText4"
#endif  ID_TEXT_SkillText4
#ifndef ID_TEXT_SkillText5
#define ID_TEXT_SkillText5		"ID_TEXT_SkillText5"
#endif  ID_TEXT_SkillText5
#ifndef ID_TEXT_SkillText6
#define ID_TEXT_SkillText6		"ID_TEXT_SkillText6"
#endif  ID_TEXT_SkillText6
#ifndef ID_TEXT_SkillText7
#define ID_TEXT_SkillText7		"ID_TEXT_SkillText7"
#endif  ID_TEXT_SkillText7

#define SKILL_XP_NUM   7

#include "UIBase.h"
class CUI_ID_FRAME_XpSkill : public CUIBase
{
	// Member
private:	
	 ControlFrame*	m_pID_FRAME_XpSkill;
	 ControlPicture*	m_pID_PICTURE_SkillBack;
	 ControlListImage*	m_pID_LISTIMG_Skill[SKILL_XP_NUM];
	 ControlText*	m_pID_TEXT_SkillText[SKILL_XP_NUM];

public:	
	CUI_ID_FRAME_XpSkill();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_Skill1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Skill1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Skill2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill3OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Skill3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill4OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Skill4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill5OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Skill5OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill5OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill5OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill6OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Skill6OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill6OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill6OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill7OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Skill7OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill7OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill7OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	void					Update();
	bool					IsSkillList( const ControlObject* pObject );
private:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视
private:	
};
extern CUI_ID_FRAME_XpSkill s_CUI_ID_FRAME_XpSkill;
