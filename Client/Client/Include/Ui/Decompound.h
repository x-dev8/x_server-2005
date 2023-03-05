/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\分级系统\Decompound.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "me3d/Vector.h"
#include "GlobalDef.h"
#include "MeUi/Animation/SlideAnimation.h"

#ifndef ID_FRAME_Decompound
#define ID_FRAME_Decompound		"ID_FRAME_Decompound"
#endif  ID_FRAME_Decompound
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
#ifndef ID_TEXT_Wall
#define ID_TEXT_Wall		"ID_TEXT_Wall"
#endif  ID_TEXT_Wall
#ifndef ID_PICTURE_ItemWall
#define ID_PICTURE_ItemWall		"ID_PICTURE_ItemWall"
#endif  ID_PICTURE_ItemWall
#ifndef ID_LISTIMG_Aim1
#define ID_LISTIMG_Aim1		"ID_LISTIMG_Aim1"
#endif  ID_LISTIMG_Aim1
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
#ifndef ID_LIST_BaseProperty
#define ID_LIST_BaseProperty		"ID_LIST_BaseProperty"
#endif  ID_LIST_BaseProperty
#ifndef ID_LIST_BaseProperty2
#define ID_LIST_BaseProperty2		"ID_LIST_BaseProperty2"
#endif  ID_LIST_BaseProperty2
#ifndef ID_PICTURE_LeftTitle
#define ID_PICTURE_LeftTitle		"ID_PICTURE_LeftTitle"
#endif  ID_PICTURE_LeftTitle
#ifndef ID_PICTURE_TitleWord
#define ID_PICTURE_TitleWord		"ID_PICTURE_TitleWord"
#endif  ID_PICTURE_TitleWord
#ifndef ID_TEXT_GoldPlating
#define ID_TEXT_GoldPlating		"ID_TEXT_GoldPlating"
#endif  ID_TEXT_GoldPlating
#ifndef ID_LISTIMG_Aim2
#define ID_LISTIMG_Aim2		"ID_LISTIMG_Aim2"
#endif  ID_LISTIMG_Aim2
#ifndef ID_LIST_Quality
#define ID_LIST_Quality		"ID_LIST_Quality"
#endif  ID_LIST_Quality
#ifndef ID_PICTURE_DecompoundEffect
#define ID_PICTURE_DecompoundEffect		"ID_PICTURE_DecompoundEffect"
#endif  ID_PICTURE_DecompoundEffect

#include "UiBase.h"
class CUI_ID_FRAME_Decompound :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_Decompound();
private:
	 ControlFrame*	m_pID_FRAME_Decompound;
// 	 ControlPicture*	m_pID_PICTURE_RightTitle;
// 	 ControlPicture*	m_pID_PICTURE_MiddleTitle;
// 	 ControlButton*	m_pID_BUTTON_CLOSE;
// 	 ControlButton*	m_pID_BUTTON_help;
// 	 ControlText*	m_pID_TEXT_Wall;
// 	 ControlPicture*	m_pID_PICTURE_ItemWall;
// 	 ControlListImage*	m_pID_LISTIMG_Aim1;
	 ControlListImage*	m_pID_LISTIMG_Armour;
	 ControlButton*	m_pID_BUTTON_Ok;
	 ControlButton*	m_pID_BUTTON_Cancel;
// 	 ControlText*	m_pID_TEXT_UseMoneyZ;
// 	 ControlText*	m_pID_TEXT_UseMoney;
// 	 ControlList*	m_pID_LIST_BaseProperty;
// 	 ControlList*	m_pID_LIST_BaseProperty2;
// 	 ControlPicture*	m_pID_PICTURE_LeftTitle;
// 	 ControlPicture*	m_pID_PICTURE_TitleWord;
// 	 ControlText*	m_pID_TEXT_GoldPlating;
// 	 ControlListImage*	m_pID_LISTIMG_Aim2;
// 	 ControlList*	m_pID_LIST_Quality;
	 ControlPicture*	m_pID_PICTURE_DecompoundEffect;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
// 	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
// 	bool ID_LISTIMG_Aim1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
// 	bool ID_LISTIMG_Aim1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
// 	bool ID_LISTIMG_Aim1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
// 	bool ID_LISTIMG_Aim1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
// 	void ID_LIST_BasePropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
//	void ID_LIST_BaseProperty2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
// 	bool ID_LISTIMG_Aim2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
// 	bool ID_LISTIMG_Aim2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
// 	bool ID_LISTIMG_Aim2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
// 	bool ID_LISTIMG_Aim2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
//	void ID_LIST_QualityOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

    void DecompoundSuccess(int index);   // 分解结束，解锁包裹，重置数据

    void SetVisiblePosition( const Vector& vPos ){ m_vVisiblePos = vPos; }
    const Vector& GetVisiblePosition() const { return m_vVisiblePos; }
    bool IsUseSameItemInNormalBag( int index ) { return (index == m_iNormalBagIndex); }
	void StartIntonate();
	bool CanDecompound(int iNormalBagIndex, bool bShowInfo);

protected:
    void SetBagItemLock(bool bLock);                // 恢复包裹物品非锁定
    void ResetAll();
    void RefreshArmour();
    void UpdateAtomVisible();                       // 更新界面控件是否可见
    void SetArmourInfo( ControlIconDrag::S_ListImg* pListImg );    // 设置装备
    void RefreshBagEnable();
    void ShowArmour( void* pItemDetail, INT nType, SCharItem* pItem );
    void ShowWeapon( void* pItemDetail, INT nType, SCharItem* pItem );
    void ShowCanWeapon( void* pItemDetail, INT nType, SCharItem* pItem );
    void ShowBaseInfo( void* pItemDetail, INT nType, SCharItem* pstItem );
    void UpdateArmourInfo( SCharItem* pItem, ControlList* pList );

    int				m_iNormalBagIndex;           // 目标物品Index
    bool			m_bNormalBagEnable;
    Vector			m_vVisiblePos;			 // 分解界面打开时的人物位置,用来自动关闭时使用

	CSlideAnimation m_slideAnim;			//序列帧动画
	bool			m_bStartAnim;

	bool			m_bStartIntonate;
	int				m_nIntonateTime;		// 吟唱时间，毫秒
	DWORD			m_dwStartIntonateTime;	// 开始吟唱时间
};
extern CUI_ID_FRAME_Decompound s_CUI_ID_FRAME_Decompound;
