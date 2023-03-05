/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\PetMain.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GlobalDef.h"
#ifndef ID_FRAME_PetMain
#define ID_FRAME_PetMain		"ID_FRAME_PetMain"
#endif  ID_FRAME_PetMain
#ifndef ID_PICTURE_PetMain0
#define ID_PICTURE_PetMain0		"ID_PICTURE_PetMain0"
#endif  ID_PICTURE_PetMain0
#ifndef ID_PICTURE_PetMain1
#define ID_PICTURE_PetMain1		"ID_PICTURE_PetMain1"
#endif  ID_PICTURE_PetMain1
#ifndef ID_PICTURE_PetMain2
#define ID_PICTURE_PetMain2		"ID_PICTURE_PetMain2"
#endif  ID_PICTURE_PetMain2
#ifndef ID_PICTURE_PetMain3
#define ID_PICTURE_PetMain3		"ID_PICTURE_PetMain3"
#endif  ID_PICTURE_PetMain3
#ifndef ID_PICTURE_PetMain4
#define ID_PICTURE_PetMain4		"ID_PICTURE_PetMain4"
#endif  ID_PICTURE_PetMain4
#ifndef ID_PICTURE_PetMain5
#define ID_PICTURE_PetMain5		"ID_PICTURE_PetMain5"
#endif  ID_PICTURE_PetMain5
#ifndef ID_LISTIMG_PetMain
#define ID_LISTIMG_PetMain		"ID_LISTIMG_PetMain"
#endif  ID_LISTIMG_PetMain
#ifndef ID_LISTIMG_PetMain0
#define ID_LISTIMG_PetMain0		"ID_LISTIMG_PetMain0"
#endif  ID_LISTIMG_PetMain0
#ifndef ID_LISTIMG_PetMain1
#define ID_LISTIMG_PetMain1		"ID_LISTIMG_PetMain1"
#endif  ID_LISTIMG_PetMain1
#ifndef ID_LISTIMG_PetMain2
#define ID_LISTIMG_PetMain2		"ID_LISTIMG_PetMain2"
#endif  ID_LISTIMG_PetMain2
#ifndef ID_LISTIMG_PetMain3
#define ID_LISTIMG_PetMain3		"ID_LISTIMG_PetMain3"
#endif  ID_LISTIMG_PetMain3
#ifndef ID_LISTIMG_PetMain4
#define ID_LISTIMG_PetMain4		"ID_LISTIMG_PetMain4"
#endif  ID_LISTIMG_PetMain4
#ifndef ID_LISTIMG_PetMain5
#define ID_LISTIMG_PetMain5		"ID_LISTIMG_PetMain5"
#endif  ID_LISTIMG_PetMain5

#include "UiBase.h"
class CUI_ID_FRAME_PetMain :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_PetMain();
private:
	ControlFrame*	m_pID_FRAME_PetMain;
	enum {
		eMaxInitiativeSkillNumber = SMountItem::MICD_PassiveSkillIndex
	};
	ControlPicture*	m_pID_PICTURE_PetMain[eMaxInitiativeSkillNumber];
	ControlListImage*	m_pID_LISTIMG_PetMain[eMaxInitiativeSkillNumber];
public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_PetMainOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_PetMainOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMainOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMainOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void InitializeAtEnterWorld();

	void Refresh();

	bool IsSkillList( const ControlObject* pObject );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视


private:

	void RefreshPetSkill();

	bool UseSkill(ControlIconDrag::S_ListImg* pItem);
	

	//void SetPetAction(int action, int keyIndex);
	//void SetPetAI(int ai);

	DWORD m_dwPetAI;

public:
	void SetHotkeyPressIndex(int nIndex);


private:
	int m_nSkillIndex;
};
extern CUI_ID_FRAME_PetMain s_CUI_ID_FRAME_PetMain;
