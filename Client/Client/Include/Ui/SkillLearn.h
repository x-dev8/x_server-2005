/********************************************************************
	Created by UIEditor.exe
	FileName: F:\project\Turbo\Bin\Client\Data\Ui\SkillLearn.h
*********************************************************************/

/*----------------------------------------------------------
desc	: 心法升级界面
author	: zilong
version	: 1.0
date	: 2011-02-16
revision:
----------------------------------------------------------*/
#pragma once
#include "MeUi/MeUi.h"
#include "Skill.h"
#include "UiBase.h"
#include "SkillSpirit.h"	//just for CXinFaUIHelper

#ifndef ID_FRAME_SKILL_LEARN
#define ID_FRAME_SKILL_LEARN		"ID_FRAME_SKILL_LEARN"
#endif  ID_FRAME_SKILL_LEARN
#ifndef ID_LISTIMG_SkillBook
#define ID_LISTIMG_SkillBook		"ID_LISTIMG_SkillBook"
#endif  ID_LISTIMG_SkillBook
#ifndef ID_LISTIMG_Skill
#define ID_LISTIMG_Skill		"ID_LISTIMG_Skill"
#endif  ID_LISTIMG_Skill
#ifndef ID_LISTIMG_SkillIcon
#define ID_LISTIMG_SkillIcon		"ID_LISTIMG_SkillIcon"
#endif  ID_LISTIMG_SkillIcon
#ifndef ID_TEXT_SkillName
#define ID_TEXT_SkillName		"ID_TEXT_SkillName"
#endif  ID_TEXT_SkillName
#ifndef ID_TEXT_SkillIntroduce
#define ID_TEXT_SkillIntroduce		"ID_TEXT_SkillIntroduce"
#endif  ID_TEXT_SkillIntroduce
// #ifndef ID_TEXT_BookLv1
// #define ID_TEXT_BookLv1		"ID_TEXT_BookLv1"
// #endif  ID_TEXT_BookLv1
// #ifndef ID_TEXT_BookLv2
// #define ID_TEXT_BookLv2		"ID_TEXT_BookLv2"
// #endif  ID_TEXT_BookLv2
// #ifndef ID_TEXT_BookLv3
// #define ID_TEXT_BookLv3		"ID_TEXT_BookLv3"
// #endif  ID_TEXT_BookLv3
// #ifndef ID_TEXT_BookLv4
// #define ID_TEXT_BookLv4		"ID_TEXT_BookLv4"
// #endif  ID_TEXT_BookLv4
// #ifndef ID_TEXT_BookLv5
// #define ID_TEXT_BookLv5		"ID_TEXT_BookLv5"
// #endif  ID_TEXT_BookLv5
// #ifndef ID_TEXT_BookLv6
// #define ID_TEXT_BookLv6		"ID_TEXT_BookLv6"
// #endif  ID_TEXT_BookLv6
// #ifndef ID_TEXT_BookLv7
// #define ID_TEXT_BookLv7		"ID_TEXT_BookLv7"
// #endif  ID_TEXT_BookLv7
// #ifndef ID_TEXT_BookLv8
// #define ID_TEXT_BookLv8		"ID_TEXT_BookLv8"
// #endif  ID_TEXT_BookLv8
// #ifndef ID_TEXT_BookLv9
// #define ID_TEXT_BookLv9		"ID_TEXT_BookLv9"
// #endif  ID_TEXT_BookLv9
// #ifndef ID_TEXT_BookLv10
// #define ID_TEXT_BookLv10		"ID_TEXT_BookLv10"
// #endif  ID_TEXT_BookLv10
#ifndef ID_TEXT_PointNeed
#define ID_TEXT_PointNeed		"ID_TEXT_PointNeed"
#endif  ID_TEXT_PointNeed
#ifndef ID_TEXT_PointNow
#define ID_TEXT_PointNow		"ID_TEXT_PointNow"
#endif  ID_TEXT_PointNow
#ifndef ID_TEXT_Cost
#define ID_TEXT_Cost		"ID_TEXT_Cost"
#endif  ID_TEXT_Cost
#ifndef ID_TEXT_Jiaozi
#define ID_TEXT_Jiaozi		"ID_TEXT_Jiaozi"
#endif  ID_TEXT_Jiaozi
#ifndef ID_TEXT_Jinqian
#define ID_TEXT_Jinqian		"ID_TEXT_Money"
#endif  ID_TEXT_Jinqian
#ifndef ID_BUTTON_Learn
#define ID_BUTTON_Learn		"ID_BUTTON_Learn"
#endif  ID_BUTTON_Learn
#ifndef ID_TEXT_NoPoint		
#define ID_TEXT_NoPoint		"ID_TEXT_NoPoint"
#endif	ID_TEXT_NoPoint
#ifndef	ID_TEXT_NoMoney
#define ID_TEXT_NoMoney		"ID_TEXT_NoMoney"
#endif	ID_TEXT_NoMoney
#ifndef	ID_LIST_Additional
#define ID_LIST_Additional		"ID_LIST_Additional"
#endif	ID_LIST_Additional
#ifndef ID_TEXT_SkillNextIntroduce
#define ID_TEXT_SkillNextIntroduce		"ID_TEXT_SkillNextIntroduce"
#endif  ID_TEXT_SkillNextIntroduce

class CUI_ID_FRAME_SKILL_LEARN: public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_SKILL_LEARN();
	 ControlFrame*	m_pID_FRAME_SKILL_LEARN;
	 ControlListImage*	m_pID_LISTIMG_SkillBook;
	 ControlListImage*	m_pID_LISTIMG_Skill;
	
	 ControlText*	m_pID_TEXT_SkillName;
	 ControlText*	m_pID_TEXT_SkillIntroduce;

	 ControlList*	m_pID_LIST__BookName;
	 ControlList*	m_pID_LIST__BookLv;
	 ControlList*	m_pID_LIST__Book;
	 ControlList*	m_pID_LIST_Additional;

	 ControlText*	m_pID_TEXT_SubSkillName[6];
	 ControlText*	m_pID_TEXT_SubSkillLevel[6];
	 ControlText*	m_pID_TEXT_SubSkillCondition[6];

	 ControlText*	m_pID_TEXT_PointNeed;
	 ControlText*	m_pID_TEXT_PointNow;
	 ControlText*	m_pID_TEXT_Cost;
	 ControlText*	m_pID_TEXT_Jiaozi;
	 ControlText*	m_pID_TEXT_Jinqian;
	 ControlButton*	m_pID_BUTTON_Learn;

	 ControlText*	m_pID_TEXT_NoPoint;
	 ControlText*	m_pID_TEXT_NoMoney;
	 ControlText*	m_pID_TEXT_SkillNextIntroduce;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_SkillBookOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_SkillBookOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SkillBookOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SkillBookOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SkillOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_SkillOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SkillOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SkillOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	
	bool ID_BUTTON_LearnOnButtonClick( ControlObject* pSender );
	void ID_LIST__BookNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_AdditionalOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	bool IsSkillList(const ControlObject* pObject)
	{
		return pObject == m_pID_LISTIMG_SkillBook || pObject == m_pID_LISTIMG_Skill;
	}

	void CheckLevel();

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	        // 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

private:
	static bool m_bStartLearn;
	int m_nNpcId;

	CXinFaUIHelper m_xinFaUIHelper;

public:
	void Refresh();
	ControlFrame* GetFrame() { return m_pID_FRAME_SKILL_LEARN; }
	static void SetStartLearn(bool bStart) { m_bStartLearn = bStart; }
	static bool GetStartLearn() { return m_bStartLearn; }

private:
	void UpdateOtherInfo(void);
};
extern CUI_ID_FRAME_SKILL_LEARN s_CUI_ID_FRAME_SKILL_LEARN;
