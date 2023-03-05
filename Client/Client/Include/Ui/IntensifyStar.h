/********************************************************************
	Created by UIEditor.exe
	FileName: D:\My Documents\桌面\IntensifyStar.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "me3d/Vector.h"
#include "GlobalDef.h"
#include "MeUi/Animation/SlideAnimation.h"
#include "ItemEnableChangeSysBase.h"

#ifndef ID_FRAME_IntensifyStar
#define ID_FRAME_IntensifyStar		"ID_FRAME_IntensifyStar"
#endif  ID_FRAME_IntensifyStar
#ifndef ID_PICTURE_DI2
#define ID_PICTURE_DI2		"ID_PICTURE_DI2"
#endif  ID_PICTURE_DI2
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_LISTIMG_Armour
#define ID_LISTIMG_Armour		"ID_LISTIMG_Armour"
#endif  ID_LISTIMG_Armour
#ifndef ID_LISTIMG_Especial
#define ID_LISTIMG_Especial		"ID_LISTIMG_Especial"
#endif  ID_LISTIMG_Especial
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
#ifndef ID_LIST_ArmourProperty
#define ID_LIST_ArmourProperty		"ID_LIST_ArmourProperty"
#endif  ID_LIST_ArmourProperty
#ifndef ID_LIST_TargetProperty
#define ID_LIST_TargetProperty		"ID_LIST_TargetProperty"
#endif  ID_LIST_TargetProperty
#ifndef ID_PICTURE_Star18
#define ID_PICTURE_Star18		"ID_PICTURE_Star18"
#endif  ID_PICTURE_Star18
#ifndef ID_PICTURE_Star17
#define ID_PICTURE_Star17		"ID_PICTURE_Star17"
#endif  ID_PICTURE_Star17
#ifndef ID_PICTURE_Star16
#define ID_PICTURE_Star16		"ID_PICTURE_Star16"
#endif  ID_PICTURE_Star16
#ifndef ID_PICTURE_Star15
#define ID_PICTURE_Star15		"ID_PICTURE_Star15"
#endif  ID_PICTURE_Star15
#ifndef ID_PICTURE_Star14
#define ID_PICTURE_Star14		"ID_PICTURE_Star14"
#endif  ID_PICTURE_Star14
#ifndef ID_PICTURE_Star13
#define ID_PICTURE_Star13		"ID_PICTURE_Star13"
#endif  ID_PICTURE_Star13
#ifndef ID_PICTURE_Star12
#define ID_PICTURE_Star12		"ID_PICTURE_Star12"
#endif  ID_PICTURE_Star12
#ifndef ID_PICTURE_Star11
#define ID_PICTURE_Star11		"ID_PICTURE_Star11"
#endif  ID_PICTURE_Star11
#ifndef ID_PICTURE_Star10
#define ID_PICTURE_Star10		"ID_PICTURE_Star10"
#endif  ID_PICTURE_Star10
#ifndef ID_PICTURE_Star9
#define ID_PICTURE_Star9		"ID_PICTURE_Star9"
#endif  ID_PICTURE_Star9
#ifndef ID_LISTIMG_Target2
#define ID_LISTIMG_Target2		"ID_LISTIMG_Target2"
#endif  ID_LISTIMG_Target2
#ifndef ID_PICTURE_NextStar18
#define ID_PICTURE_NextStar18		"ID_PICTURE_NextStar18"
#endif  ID_PICTURE_NextStar18
#ifndef ID_PICTURE_NextStar17
#define ID_PICTURE_NextStar17		"ID_PICTURE_NextStar17"
#endif  ID_PICTURE_NextStar17
#ifndef ID_PICTURE_NextStar16
#define ID_PICTURE_NextStar16		"ID_PICTURE_NextStar16"
#endif  ID_PICTURE_NextStar16
#ifndef ID_PICTURE_NextStar15
#define ID_PICTURE_NextStar15		"ID_PICTURE_NextStar15"
#endif  ID_PICTURE_NextStar15
#ifndef ID_PICTURE_NextStar14
#define ID_PICTURE_NextStar14		"ID_PICTURE_NextStar14"
#endif  ID_PICTURE_NextStar14
#ifndef ID_PICTURE_NextStar13
#define ID_PICTURE_NextStar13		"ID_PICTURE_NextStar13"
#endif  ID_PICTURE_NextStar13
#ifndef ID_PICTURE_NextStar12
#define ID_PICTURE_NextStar12		"ID_PICTURE_NextStar12"
#endif  ID_PICTURE_NextStar12
#ifndef ID_PICTURE_NextStar11
#define ID_PICTURE_NextStar11		"ID_PICTURE_NextStar11"
#endif  ID_PICTURE_NextStar11
#ifndef ID_PICTURE_NextStar10
#define ID_PICTURE_NextStar10		"ID_PICTURE_NextStar10"
#endif  ID_PICTURE_NextStar10
#ifndef ID_PICTURE_NextStar9
#define ID_PICTURE_NextStar9		"ID_PICTURE_NextStar9"
#endif  ID_PICTURE_NextStar9
#ifndef ID_PICTURE_StarEffect
#define ID_PICTURE_StarEffect		"ID_PICTURE_StarEffect"
#endif  ID_PICTURE_StarEffect
#ifndef ID_LISTIMG_Target
#define ID_LISTIMG_Target		"ID_LISTIMG_Target"
#endif  ID_LISTIMG_Target
#ifndef ID_TEXT_Rate
#define ID_TEXT_Rate		"ID_TEXT_Rate"
#endif  ID_TEXT_Rate

#include "UiBase.h"

class CUI_ID_FRAME_IntensifyStar :public CUIBase, CItemEnableChangeSysBase
{
	// Member
public:
	 CUI_ID_FRAME_IntensifyStar();

private:
	void ResetUIObjects();
	 ControlFrame*	m_pID_FRAME_IntensifyStar;
	 ControlPicture*	m_pID_PICTURE_DI2;
	 ControlListImage*	m_pID_LISTIMG_Material;
	 ControlListImage*	m_pID_LISTIMG_Armour;
	 ControlListImage*	m_pID_LISTIMG_Especial;
	 ControlButton*	m_pID_BUTTON_Ok;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlText*	m_pID_TEXT_UseMoneyZ;
	 ControlText*	m_pID_TEXT_UseMoney;
	 ControlList*	m_pID_LIST_ArmourProperty;
	 ControlList*	m_pID_LIST_TargetProperty;
	 ControlPicture*	m_pID_PICTURE_Star18;
	 ControlPicture*	m_pID_PICTURE_Star17;
	 ControlPicture*	m_pID_PICTURE_Star16;
	 ControlPicture*	m_pID_PICTURE_Star15;
	 ControlPicture*	m_pID_PICTURE_Star14;
	 ControlPicture*	m_pID_PICTURE_Star13;
	 ControlPicture*	m_pID_PICTURE_Star12;
	 ControlPicture*	m_pID_PICTURE_Star11;
	 ControlPicture*	m_pID_PICTURE_Star10;
	 ControlPicture*	m_pID_PICTURE_Star9;
	 ControlListImage*	m_pID_LISTIMG_Target2;
	 ControlPicture*	m_pID_PICTURE_NextStar18;
	 ControlPicture*	m_pID_PICTURE_NextStar17;
	 ControlPicture*	m_pID_PICTURE_NextStar16;
	 ControlPicture*	m_pID_PICTURE_NextStar15;
	 ControlPicture*	m_pID_PICTURE_NextStar14;
	 ControlPicture*	m_pID_PICTURE_NextStar13;
	 ControlPicture*	m_pID_PICTURE_NextStar12;
	 ControlPicture*	m_pID_PICTURE_NextStar11;
	 ControlPicture*	m_pID_PICTURE_NextStar10;
	 ControlPicture*	m_pID_PICTURE_NextStar9;
	 ControlPicture*	m_pID_PICTURE_StarEffect;
	 ControlListImage*	m_pID_LISTIMG_Target;
	 ControlText*	m_pID_TEXT_Rate;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_EspecialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_EspecialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_EspecialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_EspecialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	void ID_LIST_ArmourPropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_TargetPropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_LISTIMG_Target2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Target2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Target2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Target2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_TargetOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_TargetOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_TargetOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_TargetOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void UpdateGem();
	void UpdateAddRateGem();
	void RefreshArmour();
	void SetVisiblePosition( const Vector& vPos ){ m_vVisiblePos = vPos; }
	void RefreshOkButton();
	short GetItemMaterialType( unsigned short ustId );

    virtual bool IsPackItemBeUsing( __int64 nGuid );

protected:
	void RefreshAllBagEnable();
	void ClearAllList();
	void SetAtomVisible( bool bVisible );

	void ShowStar( int nStar ,int nLevel);
	void ShowNextStar( int nStar,int nLevel );

	void SetDirty( bool bDirty ){ m_bNeedUpdate = bDirty; }
	bool IsDirty(){ return m_bNeedUpdate; }
	
    int  GetItemLevel(unsigned short ustItemID );

	void RefreshNeedMoney( SCharItem* pItem );

	const Vector& GetVisiblePosition() const { return m_vVisiblePos; }


	static void OnVisibleChange( ControlObject* pUIObject ); 

private:
	void UpdateArmourInfo( SCharItem* pItem, ControlList* pList, bool bNextLevel );
	void SetArmourAndTargetInfo( ControlIconDrag::S_ListImg*  pListImg );

	ControlGroup		m_StarGroup;
	ControlGroup		m_NextStarGroup;


	short m_stNormalBagIndex;			// 目标物品Index
    __int64 m_stNormalBagGuid;			//目标物品Guid
	bool  m_bNormalBagEnable;

    short m_shLevelupMaterialBagType;    //升星宝石背包类型
	short m_stLevelupMaterialIndex;		// 升星宝石Index
	__int64 m_n64LevelupMaterialGuid;	// 升星宝石Guid
	bool  m_bLevelupMaterialBagEnable;

    short m_shRateMaterialBagType;      //提高几率的背包类型
	short m_stRateMaterialIndex;		// 提高几率的Index
	__int64 m_n64RateMaterialGuid;		// 提高几率材料Guid
	bool  m_bRateMaterialBagEnable;  
	short m_shRateMaterialCount;		// 提高几率的材料个数

	bool  m_bNeedUpdate;			 // 刷新界面

	Vector m_vVisiblePos;			 // 升星界面打开时的人物位置,用来自动关闭时使用

	CSlideAnimation m_slideAnim;			//序列帧动画
	bool			m_bStartAnim;
};
extern CUI_ID_FRAME_IntensifyStar s_CUI_ID_FRAME_IntensifyStar;
