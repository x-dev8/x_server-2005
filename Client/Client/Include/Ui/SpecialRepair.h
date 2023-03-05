/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\SpecialRepair.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "me3d/Vector.h"
#include "MessageDefine.h"
#include "bag/ItemBag2.h"
#include "ItemDetail.h"
#include "MeUi/Animation/SlideAnimation.h"

#ifndef ID_FRAME_SpecialRepair
#define ID_FRAME_SpecialRepair		"ID_FRAME_SpecialRepair"
#endif  ID_FRAME_SpecialRepair
#ifndef ID_PICTURE_RightTitle
#define ID_PICTURE_RightTitle		"ID_PICTURE_RightTitle"
#endif  ID_PICTURE_RightTitle
#ifndef ID_PICTURE_MiddleTitle
#define ID_PICTURE_MiddleTitle		"ID_PICTURE_MiddleTitle"
#endif  ID_PICTURE_MiddleTitle
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_PICTURE_ItemWall
#define ID_PICTURE_ItemWall		"ID_PICTURE_ItemWall"
#endif  ID_PICTURE_ItemWall
#ifndef ID_LISTIMG_Armour
#define ID_LISTIMG_Armour		"ID_LISTIMG_Armour"
#endif  ID_LISTIMG_Armour
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_TEXT_UseMoneyZ
#define ID_TEXT_UseMoneyZ		"ID_TEXT_UseMoneyZ"
#endif  ID_TEXT_UseMoneyZ
#ifndef ID_TEXT_UseMoney
#define ID_TEXT_UseMoney		"ID_TEXT_UseMoney"
#endif  ID_TEXT_UseMoney
#ifndef ID_PICTURE_LeftTitle
#define ID_PICTURE_LeftTitle		"ID_PICTURE_LeftTitle"
#endif  ID_PICTURE_LeftTitle
#ifndef ID_PICTURE_TitleWord
#define ID_PICTURE_TitleWord		"ID_PICTURE_TitleWord"
#endif  ID_PICTURE_TitleWord
#ifndef ID_TEXT_Explain
#define ID_TEXT_Explain		"ID_TEXT_Explain"
#endif  ID_TEXT_Explain
#ifndef ID_PICTURE_ItemWall2
#define ID_PICTURE_ItemWall2		"ID_PICTURE_ItemWall2"
#endif  ID_PICTURE_ItemWall2
#ifndef ID_LISTIMG_Aim
#define ID_LISTIMG_Aim		"ID_LISTIMG_Aim"
#endif  ID_LISTIMG_Aim
#ifndef ID_TEXT_ArmourName
#define ID_TEXT_ArmourName		"ID_TEXT_ArmourName"
#endif  ID_TEXT_ArmourName
#ifndef ID_TEXT_AimName
#define ID_TEXT_AimName		"ID_TEXT_AimName"
#endif  ID_TEXT_AimName
#ifndef ID_PICTURE_SpecialRepairEffect
#define ID_PICTURE_SpecialRepairEffect		"ID_PICTURE_SpecialRepairEffect"
#endif  ID_PICTURE_SpecialRepairEffect

#include "UiBase.h"
class CUI_ID_FRAME_SpecialRepair :public CUIBase
{
	// Member
private:
	void ResetMembers();
	ControlFrame*	m_pID_FRAME_SpecialRepair;
// 	ControlPicture*	m_pID_PICTURE_RightTitle;
// 	ControlPicture*	m_pID_PICTURE_MiddleTitle;
// 	ControlButton*	m_pID_BUTTON_CLOSE;
// 	ControlButton*	m_pID_BUTTON_help;
// 	ControlPicture*	m_pID_PICTURE_ItemWall;
	ControlListImage*	m_pID_LISTIMG_Armour;
	ControlButton*	m_pID_BUTTON_Ok;
	ControlButton*	m_pID_BUTTON_Cancel;
	ControlText*	m_pID_TEXT_UseMoneyZ;
	ControlText*	m_pID_TEXT_UseMoney;
// 	ControlPicture*	m_pID_PICTURE_LeftTitle;
// 	ControlPicture*	m_pID_PICTURE_TitleWord;
	ControlText*	m_pID_TEXT_Explain;
	//ControlPicture*	m_pID_PICTURE_ItemWall2;
	ControlListImage*	m_pID_LISTIMG_Aim;
// 	ControlText*	m_pID_TEXT_ArmourName;
// 	ControlText*	m_pID_TEXT_AimName;
	 ControlPicture*	m_pID_PICTURE_SpecialRepairEffect;

public:	
	CUI_ID_FRAME_SpecialRepair();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
// 	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_AimOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_AimOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_AimOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_AimOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void RepairAck(MsgSpecialRepairItemAck* pAck);
private:
	bool SetEquip(ControlIconDrag::S_ListImg *pItem, ItemDefine::SItemCanEquip* pCanEquip);
	bool SetEquip(ControlObject* pSender, ControlIconDrag::S_ListImg* pItem);
	void SetEquipIndex(int index);
	bool SetAim(ControlIconDrag::S_ListImg *pItem, ItemDefine::SItemCommon* pItemCommon);
	bool SetAim_(ControlObject* pSender, ControlIconDrag::S_ListImg* pItem);
	void SetAimIndex(int index);
	bool RequestRepair();
	void RefreshBagIconEnable();
	void RefreshEquipIconEnable();
	void RefreshMaterialIconEnable();
	void Clear();
	void ClearEquip();
	void ClearAim();
	void ClearAnim();

	static void OnVisibleChanged(ControlObject* pSender);

	SCharItem		m_equip;
	int				m_equipBagIndex;
	bool			m_equipEnable;

	int				m_materialBagIndex;
	bool			m_materialEnable;
	ControlListImage* m_pMaterialBagListImg;
	CItemBag2*		m_pMaterialBag;
	int				m_bagType;

	int				m_needRepairMoney;

	Vector			m_vVisiblePos;

	bool			m_bNeedUpdate;

	bool			m_bShowError;

	CSlideAnimation m_slideAnim;			//序列帧动画
	bool			m_bStartAnim;

	bool			m_bStartIntonate;
	int				m_nIntonateTime;		// 吟唱时间，毫秒
	DWORD			m_dwStartIntonateTime;	// 开始吟唱时间
};
extern CUI_ID_FRAME_SpecialRepair s_CUI_ID_FRAME_SpecialRepair;
