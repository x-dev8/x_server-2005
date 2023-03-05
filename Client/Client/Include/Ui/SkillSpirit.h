/********************************************************************
	Created by UIEditor.exe
	FileName: F:\project\Turbo\Bin\Client\Data\Ui\SkillSpirit.h
*********************************************************************/

/*----------------------------------------------------------
desc	: 技能界面中对应的心法显示页。
author	: zilong
version	: 1.0
date	: 2011-02-16
revision:
----------------------------------------------------------*/

#pragma once
#include "MeUi/MeUi.h"
#include "XinFaConfig.h"	//for XinFaConfig

#ifndef ID_FRAME_Skill_Spirit
#define ID_FRAME_Skill_Spirit		"ID_FRAME_Skill_Spirit"
#endif  ID_FRAME_Skill_Spirit
#ifndef ID_LISTIMG_SkillBook
#define ID_LISTIMG_SkillBook		"ID_LISTIMG_SkillBook"
#endif  ID_LISTIMG_SkillBook
#ifndef ID_LISTIMG_Skill
#define ID_LISTIMG_Skill		"ID_LISTIMG_Skill"
#endif  ID_LISTIMG_Skill
#ifndef ID_TEXT_SkillName
#define ID_TEXT_SkillName		"ID_TEXT_SkillName"
#endif  ID_TEXT_SkillName
#ifndef ID_TEXT_SkillIntroduce
#define ID_TEXT_SkillIntroduce		"ID_TEXT_SkillIntroduce"
#endif  ID_TEXT_SkillIntroduce

#ifndef ID_LIST__BookName
#define ID_LIST__BookName		"ID_LIST__BookName"
#endif  ID_LIST__BookName

#ifndef ID_LIST__BookLv
#define ID_LIST__BookLv			"ID_LIST__BookLv"
#endif  ID_LIST__BookLv

#ifndef ID_LIST__Book
#define ID_LIST__Book			"ID_LIST__Book"
#endif  ID_LIST__Book

#ifndef ID_TEXT_SkillName11
#define ID_TEXT_SkillName11		"ID_TEXT_SkillName11"
#endif  ID_TEXT_SkillName11

#ifndef ID_TEXT_SkillName22
#define ID_TEXT_SkillName22		"ID_TEXT_SkillName22"
#endif  ID_TEXT_SkillName22

#ifndef ID_TEXT_SkillName33
#define ID_TEXT_SkillName33		"ID_TEXT_SkillName33"
#endif  ID_TEXT_SkillName33

#ifndef ID_TEXT_SkillName44
#define ID_TEXT_SkillName44		"ID_TEXT_SkillName44"
#endif  ID_TEXT_SkillName44

#ifndef ID_TEXT_SkillName55
#define ID_TEXT_SkillName55		"ID_TEXT_SkillName55"
#endif  ID_TEXT_SkillName55

#ifndef ID_TEXT_SkillName66
#define ID_TEXT_SkillName66		"ID_TEXT_SkillName66"
#endif  ID_TEXT_SkillName66

#ifndef ID_TEXT_SkillLevel11
#define ID_TEXT_SkillLevel11		"ID_TEXT_SkillLevel11"
#endif  ID_TEXT_SkillLevel11

#ifndef ID_TEXT_SkillLevel22
#define ID_TEXT_SkillLevel22		"ID_TEXT_SkillLevel22"
#endif  ID_TEXT_SkillLevel22
#ifndef ID_TEXT_SkillLevel33
#define ID_TEXT_SkillLevel33		"ID_TEXT_SkillLevel33"
#endif  ID_TEXT_SkillLevel33

#ifndef ID_TEXT_SkillLevel44
#define ID_TEXT_SkillLevel44		"ID_TEXT_SkillLevel44"
#endif  ID_TEXT_SkillLevel44

#ifndef ID_TEXT_SkillLevel55
#define ID_TEXT_SkillLevel55		"ID_TEXT_SkillLevel55"
#endif  ID_TEXT_SkillLevel55

#ifndef ID_TEXT_SkillLevel66
#define ID_TEXT_SkillLevel66		"ID_TEXT_SkillLevel66"
#endif  ID_TEXT_SkillLevel66

#ifndef ID_TEXT_SkillCondition11
#define ID_TEXT_SkillCondition11		"ID_TEXT_SkillCondition11"
#endif  ID_TEXT_SkillCondition11

#ifndef ID_TEXT_SkillCondition22
#define ID_TEXT_SkillCondition22		"ID_TEXT_SkillCondition22"
#endif  ID_TEXT_SkillCondition22

#ifndef ID_TEXT_SkillCondition33
#define ID_TEXT_SkillCondition33		"ID_TEXT_SkillCondition33"
#endif  ID_TEXT_SkillCondition33

#ifndef ID_TEXT_SkillCondition44
#define ID_TEXT_SkillCondition44		"ID_TEXT_SkillCondition44"
#endif  ID_TEXT_SkillCondition44

#ifndef ID_TEXT_SkillCondition55
#define ID_TEXT_SkillCondition55		"ID_TEXT_SkillCondition55"
#endif  ID_TEXT_SkillCondition55

#ifndef ID_TEXT_SkillCondition66
#define ID_TEXT_SkillCondition66		"ID_TEXT_SkillCondition66"
#endif  ID_TEXT_SkillCondition66

#ifndef	ID_TEXT_NowExp
#define ID_TEXT_NowExp					"ID_TEXT_NowExp"
#endif	ID_TEXT_NowExp

#ifndef ID_LIST_Additional
#define ID_LIST_Additional			"ID_LIST_Additional"
#endif  ID_LIST_Additional

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

/*------------------------------------------------------------
desc	: 设置心法界面的辅助性类。
------------------------------------------------------------*/
class CXinFaUIHelper
{
public:
	CXinFaUIHelper();
	~CXinFaUIHelper();

	void Init(ControlListImage *pImageBook_, ControlListImage *pImageSkill_, 
		ControlText *pTextName_, ControlText *pTextIntroduction_, ControlList *pTextLevels_, 
		ControlList *pXinfaNames_, ControlText **pSkillName, ControlText **pSkillCondition, 
		ControlText **pNeedXinFaLevel, uint8 booksCount_, ControlList* pAdditional=NULL, ControlText* pTextNextIntroduction_ = NULL);

	void Reset(void);

	//清除保存被选择的心法或者技能的指针
	void ClearSelectedInfo(void);

	XinFaConfig::STalentXinFa *GetSelectedXinFa(void){return m_pSelectedXinFa;}

	void RefreshXinFa();
	bool ClickXinFaIcon(const ControlIconDrag::S_ListImg *pItem_);
	bool ClickSkillIcon(const ControlIconDrag::S_ListImg *pItem_);

	bool CheckXinFaLevel();

private:
	void RefreshSkills(XinFaConfig::STalentXinFa *pXinFa_, bool bFixed = false, bool bClearList = true);

	/*--------------------------------------------------------------
	In	: index_, 图标在ControlListImage的位置序号。
		  bUseIconIndex, true, 使用图标数据自带的序号；false, 使用index_
	--------------------------------------------------------------*/
	bool SetXinFaIcon(const XinFaConfig::STalentXinFa *pXinFa_, ControlListImage *_pListImage_, int index_ = 0, bool lock = false);
	bool SetSkillIcon(const XinFaConfig::SXinFaSkill *pItemSkill_, ControlListImage *_pListImage_, int index_ = 0, bool bUseIconIndex = true, bool fixed = false);

	bool SetXinFaInfo(/*const*/ XinFaConfig::STalentXinFa *pXinFa_, bool isNext = false);
	//bool SetSkillInfo(const XinFaConfig::SXinFaSkill *pItemSkill_);

	//设置文本控件信息
	void SetText_SkillName(const char *info_);
	void SetText_SkillIntroduction(const char *info_);
	void SetText_NextSkillIntroduction(const char *info_);

	//检验心法书的index是否合法
	bool IsXinFaImageIndexValid(int index_){return index_ >= 0 && index_ < m_booksCount;}

private:
	XinFaConfig::STalentXinFa *m_pSelectedXinFa;
	XinFaConfig::SXinFaSkill *m_pSelectedSkill;

	//指向拥有者的控件
	ControlListImage *m_pImageBook;
	ControlListImage *m_pImageSkill;
	
	ControlText *m_pTextName;
	ControlText *m_pTextIntroduction;
	ControlText *m_pTextNextIntroduction;

	ControlList *m_pListXinfaLevels;
	ControlList *m_pListXinfaNames;

	ControlList *m_pAdditional;

	ControlText **m_pTextSkillCondition;
	ControlText **m_pTextNeedXinfaLevels;
	ControlText **m_pTextSkillNames;

	uint8 m_booksCount;
};

#include "UiBase.h"
class CUI_ID_FRAME_Skill_Spirit: public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_Skill_Spirit();
	ControlFrame*	m_pID_FRAME_Skill_Spirit;
	ControlListImage*	m_pID_LISTIMG_SkillBook;
	ControlListImage*	m_pID_LISTIMG_Skill;
	
	ControlText*	m_pID_TEXT_SkillName;
	ControlText*	m_pID_TEXT_SkillIntroduce;

	ControlText*	m_pID_TEXT_SubSkillName[6];
	ControlText*	m_pID_TEXT_SubSkillLevel[6];
	ControlText*	m_pID_TEXT_SubSkillCondition[6];

	ControlList*	m_pID_LIST__BookName;
	ControlList*	m_pID_LIST__BookLv;
	ControlList*	m_pID_LIST__Book;
	ControlList*	m_pID_LIST_Additional;			//
	
	ControlText*	m_pID_TEXT_NowExp;

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
	bool ID_LISTIMG_SkillIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_SkillIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SkillIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SkillIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	//add for click effect
	void ID_LIST__BookNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_AdditionalOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
	ControlFrame* GetFrame() { return m_pID_FRAME_Skill_Spirit; }
	bool IsSkillList(const ControlObject* pObject);

	void Refresh();

	static void IconOnShiftLBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
private:
	CXinFaUIHelper m_xinFaUIHelper;
};

extern CUI_ID_FRAME_Skill_Spirit s_CUI_ID_FRAME_Skill_Spirit;
extern const int UI_XINFACOUNT;
