#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_SuAnimalMain
#define ID_FRAME_SuAnimalMain		"ID_FRAME_SuAnimalMain"
#endif  ID_FRAME_SuAnimalMain
#ifndef ID_TEXT_PetSkillText
#define ID_TEXT_PetSkillText		"ID_TEXT_PetSkillText"
#endif  ID_TEXT_PetSkillText
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
#ifndef ID_PICTURE_PetMain6
#define ID_PICTURE_PetMain6		"ID_PICTURE_PetMain6"
#endif  ID_PICTURE_PetMain6
#ifndef ID_PICTURE_PetMain7
#define ID_PICTURE_PetMain7		"ID_PICTURE_PetMain7"
#endif  ID_PICTURE_PetMain7
#ifndef ID_LISTIMG_PetMain6
#define ID_LISTIMG_PetMain6		"ID_LISTIMG_PetMain6"
#endif  ID_LISTIMG_PetMain6
#ifndef ID_LISTIMG_PetMain7
#define ID_LISTIMG_PetMain7		"ID_LISTIMG_PetMain7"
#endif  ID_LISTIMG_PetMain7

#define PET_SKILLNUM 8
class CUI_ID_FRAME_SuAnimalMain : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_SuAnimalMain();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_PetMain0OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_PetMain0OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain0OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain0OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_PetMain1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_PetMain2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain3OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_PetMain3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain4OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_PetMain4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain5OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_PetMain5OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain5OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain5OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain6OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_PetMain6OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain6OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain6OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain7OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_PetMain7OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain7OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetMain7OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void UpdateUIState();
public:
	void RefreshPetSkill();
	bool IsSkillList(const ControlObject* pObject);
	bool UseSkill(ControlIconDrag::S_ListImg* pItem);
	void SetHotkeyPressIndex(int nIndex);
	void SortControl();

	bool IsSubControlInFrame(ControlObject *control)
	{
		return control == m_pID_LISTIMG_PetMain0 || control == m_pID_LISTIMG_PetMain1 || control == m_pID_LISTIMG_PetMain2
			|| control == m_pID_LISTIMG_PetMain3 || control == m_pID_LISTIMG_PetMain4 || control == m_pID_LISTIMG_PetMain5
			|| control == m_pID_LISTIMG_PetMain6 || control == m_pID_LISTIMG_PetMain7;
	}

private:
	DWORD m_dwPetAI;
	int   m_nSkillIndex;
private:
	ControlFrame*	m_pID_FRAME_SuAnimalMain;
	ControlText*	m_pID_TEXT_PetSkillText;
	ControlPicture*	m_pID_PICTURE_PetMain0;
	ControlPicture*	m_pID_PICTURE_PetMain1;
	ControlPicture*	m_pID_PICTURE_PetMain2;
	ControlPicture*	m_pID_PICTURE_PetMain3;
	ControlPicture*	m_pID_PICTURE_PetMain4;
	ControlPicture*	m_pID_PICTURE_PetMain5;
	ControlPicture*	m_pID_PICTURE_PetMain6;
	ControlPicture*	m_pID_PICTURE_PetMain7;

	ControlListImage*	m_pID_LISTIMG_PetMain0;
	ControlListImage*	m_pID_LISTIMG_PetMain1;
	ControlListImage*	m_pID_LISTIMG_PetMain2;
	ControlListImage*	m_pID_LISTIMG_PetMain3;
	ControlListImage*	m_pID_LISTIMG_PetMain4;
	ControlListImage*	m_pID_LISTIMG_PetMain5;
	ControlListImage*	m_pID_LISTIMG_PetMain6;
	ControlListImage*	m_pID_LISTIMG_PetMain7;

	ControlListImage*  m_pID_LISTIMG_PetMain[PET_SKILLNUM];
	ControlPicture*	m_pID_PICTURE_PetMain[PET_SKILLNUM];
};
extern CUI_ID_FRAME_SuAnimalMain s_CUI_ID_FRAME_SuAnimalMain;
