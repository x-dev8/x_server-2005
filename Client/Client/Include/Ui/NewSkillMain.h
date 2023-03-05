/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\NewSkillMain.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_NewSkillMain
#define ID_FRAME_NewSkillMain		"ID_FRAME_NewSkillMain"
#endif  ID_FRAME_NewSkillMain
#ifndef ID_LISTIMG_Hotkey
#define ID_LISTIMG_Hotkey		"ID_LISTIMG_Hotkey"
#endif  ID_LISTIMG_Hotkey

#include "UiBase.h"
class CUI_ID_FRAME_NewSkillMain :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_NewSkillMain();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_HotkeyOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_HotkeyOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_HotkeyOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_HotkeyOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

    void AddSkill(int id, int level = 1);
	void AddSkillByCheck(int id,int level = 1);
    void EnableAddSkill(bool b) { m_bAddSkill = true; }

    ControlListImage* GetListImage(){return m_pID_LISTIMG_Hotkey;}
    int  GetListImageIndex(ControlIconDrag::S_ListImg* pImg);

    void RemoveSkill(unsigned int index);

private:
	static void OnVisibleChanged(ControlObject* pSender);

    ControlFrame*	m_pID_FRAME_NewSkillMain;
    ControlListImage*	m_pID_LISTIMG_Hotkey;

	bool m_bAddSkill;
	std::vector<int> m_skillIds;
	std::vector<int> m_skillLevels;

	void _Refresh();
};
extern CUI_ID_FRAME_NewSkillMain s_CUI_ID_FRAME_NewSkillMain;
