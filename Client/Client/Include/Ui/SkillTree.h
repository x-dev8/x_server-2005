/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\SkillTreeSpear.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_SkillTree
#define ID_FRAME_SkillTree		"ID_FRAME_SkillTree"
#endif  ID_FRAME_SkillTree
#ifndef ID_PICTURE_DI2
#define ID_PICTURE_DI2		"ID_PICTURE_DI2"
#endif  ID_PICTURE_DI2
#ifndef ID_PICTURE_Fenge
#define ID_PICTURE_Fenge		"ID_PICTURE_Fenge"
#endif  ID_PICTURE_Fenge
#ifndef ID_TEXT_SkillPoint
#define ID_TEXT_SkillPoint		"ID_TEXT_SkillPoint"
#endif  ID_TEXT_SkillPoint

#include "UiBase.h"
class CUI_ID_FRAME_SkillTree :public CUIBase
{
	// Member
private:
	ControlFrame*	m_pID_FRAME_SkillTree;
	//ControlPicture*	m_pID_PICTURE_DI2;
	ControlPicture*	m_pID_PICTURE_Fenge;
	//ControlText*	m_pID_TEXT_SkillPoint;

public:	
	CUI_ID_FRAME_SkillTree();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();

	bool ID_LISTIMG_SkillOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_SkillOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SkillOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SkillOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_SkillOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
	ControlFrame* GetFrame() { return m_pID_FRAME_SkillTree; }
	void RefreshSkillTree();
	void RefreshSkillPoint();
	bool IsSkillList( const ControlObject* pObject );	

private:
	std::vector<ControlListImage*> m_skillTrees;
	std::vector<ControlText*> m_skillLevels;
	std::vector<ControlText*> m_skillNames;
	std::vector<ControlButton*> m_skillUps;
	std::vector<ControlPicture*> m_skillArrows;
	std::vector<ControlPicture*> m_skillBackgrounds;
	std::string m_professionName;

private:
	void Refresh();
};
extern CUI_ID_FRAME_SkillTree s_CUI_ID_FRAME_SkillTree;
