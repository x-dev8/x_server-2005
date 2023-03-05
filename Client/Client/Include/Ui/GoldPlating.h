/********************************************************************
	Created by UIEditor.exe
	FileName: D:\My Documents\桌面\GoldPlating.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "me3d/Vector.h"
#include "EquipUIHelper.h"
#include "MeUi/Animation/SlideAnimation.h"
#include "ItemEnableChangeSysBase.h"

#ifndef ID_FRAME_GoldPlating
#define ID_FRAME_GoldPlating		"ID_FRAME_GoldPlating"
#endif  ID_FRAME_GoldPlating
#ifndef ID_PICTURE_DI2
#define ID_PICTURE_DI2		"ID_PICTURE_DI2"
#endif  ID_PICTURE_DI2
#ifndef ID_PICTURE_title2
#define ID_PICTURE_title2		"ID_PICTURE_title2"
#endif  ID_PICTURE_title2
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
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
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
#ifndef ID_TEXT_GoldPlating
#define ID_TEXT_GoldPlating		"ID_TEXT_GoldPlating"
#endif  ID_TEXT_GoldPlating
#ifndef ID_PICTURE_6105
#define ID_PICTURE_6105		"ID_PICTURE_6105"
#endif  ID_PICTURE_6105
#ifndef ID_TEXT_UseMoney
#define ID_TEXT_UseMoney		"ID_TEXT_UseMoney"
#endif  ID_TEXT_UseMoney
#ifndef ID_LIST_BaseProperty
#define ID_LIST_BaseProperty		"ID_LIST_BaseProperty"
#endif  ID_LIST_BaseProperty
#ifndef ID_LIST_Property
#define ID_LIST_Property		"ID_LIST_Property"
#endif  ID_LIST_Property
#ifndef ID_PICTURE_LeftTitle
#define ID_PICTURE_LeftTitle		"ID_PICTURE_LeftTitle"
#endif  ID_PICTURE_LeftTitle
#ifndef ID_TEXT_Prompt
#define ID_TEXT_Prompt		"ID_TEXT_Prompt"
#endif  ID_TEXT_Prompt
#ifndef ID_PICTURE_IdentifyTitle
#define ID_PICTURE_IdentifyTitle		"ID_PICTURE_IdentifyTitle"
#endif  ID_PICTURE_IdentifyTitle
#ifndef ID_TEXT_Property
#define ID_TEXT_Property		"ID_TEXT_Property"
#endif  ID_TEXT_Property
#ifndef ID_TEXT_Identify
#define ID_TEXT_Identify		"ID_TEXT_Identify"
#endif  ID_TEXT_Identify
#ifndef ID_PICTURE_GoldPlatingTitle
#define ID_PICTURE_GoldPlatingTitle		"ID_PICTURE_GoldPlatingTitle"
#endif  ID_PICTURE_GoldPlatingTitle
#ifndef ID_TEXT_EspecialProperty
#define ID_TEXT_EspecialProperty		"ID_TEXT_EspecialProperty"
#endif  ID_TEXT_EspecialProperty
#ifndef ID_LIST_Quality
#define ID_LIST_Quality		"ID_LIST_Quality"
#endif  ID_LIST_Quality
#ifndef ID_BUTTON_Identify
#define ID_BUTTON_Identify		"ID_BUTTON_Identify"
#endif  ID_BUTTON_Identify
#ifndef ID_PICTURE_GoldPlatingEffect
#define ID_PICTURE_GoldPlatingEffect		"ID_PICTURE_GoldPlatingEffect"
#endif  ID_PICTURE_GoldPlatingEffect
#ifndef ID_PICTURE_IdentifyEffect
#define ID_PICTURE_IdentifyEffect		"ID_PICTURE_IdentifyEffect"
#endif  ID_PICTURE_IdentifyEffect
#ifndef ID_LISTIMG_Especial
#define ID_LISTIMG_Especial		"ID_LISTIMG_Especial"
#endif  ID_LISTIMG_Especial

#include "UiBase.h"

class CUI_ID_FRAME_GoldPlating :public CUIBase, CItemEnableChangeSysBase
{
public:
	enum ePlatingType
	{
		ePlatingType_Identify, // 鉴定
		ePlatingType_KaiGuang,   // 开光
		ePlatingType_Count
	};

	// Member
public:	
	 CUI_ID_FRAME_GoldPlating();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
// 	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	//void ID_LIST_BasePropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_PropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_QualityOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_IdentifyOnButtonClick( ControlObject* pSender );
    bool ID_LISTIMG_EspecialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
    bool ID_LISTIMG_EspecialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_EspecialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_EspecialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


    void RefreshOkButton();
	void RefreshArmour();	
    void RefreshMaterial();
    void SetPlatingType( ePlatingType eType );
	void SetVisiblePosition( const Vector& vPos ){ m_vVisiblePos = vPos; }

    bool IsReturnMaterial(ControlIconDrag::S_ListImg *pItem);  //是否回炉材料
    bool IsLevelAnaly(ControlIconDrag::S_ListImg *pItemAmor,ControlIconDrag::S_ListImg *pItemMaterial);

    bool IsHaveDone(SCharItem *pItem);  //是否已经鉴定或开光
    virtual bool IsPackItemBeUsing( __int64 nGuid );

private:	
	void UpdateAccessory();

	void RefreshAllBagEnable();
	void RefreshNeedMoney( SCharItem* pItem );	
	void SetDirty( bool bDirty ){ m_bDirty = bDirty; }
	bool IsDirty(){ return m_bDirty; }


	ePlatingType GetPlatingType(){ return m_ePlatingType; }

	static void OnVisibleChange( ControlObject* pUIObject ); 

	void ClearAllList();


	const Vector& GetVisiblePosition() const { return m_vVisiblePos; }

    bool SetMaterial0(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag);

	bool SetMaterial1(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag);

	void ClearAnim();

protected:
	void UpdateArmourInfo( SCharItem* pItem, ControlList* pList );
	void SetArmourInfo( ControlIconDrag::S_ListImg*  pListImg );
	void UpdateAtomVisible();
	void ClearMoney();
	void ShowArmour( void* pItemDetail, INT nType, SCharItem* pItem );
	void ShowWeapon( void* pItemDetail, INT nType, SCharItem* pItem );
	void ShowCanWeapon( void* pItemDetail, INT nType, SCharItem* pItem );
	void ShowBaseInfo( void* pItemDetail, INT nType, SCharItem* pstItem );

protected:
	short m_stNormalBagIndex;        // 目标物品Index
    __int64 m_stNormalGuid;
	bool  m_bNormalBagEnable;

    short m_stMaterialBagType;      //背包类型
	short m_stMaterialIndex;		// 鉴定/开光道具Index
	__int64 m_n64MaterialGuid;		// 材料GUID
	bool  m_bMaterialBagEnable;

    short m_stNeedMaterialBagType;   //回炉材料
    short m_stNeedMaterialIndex;     //回炉材料索引
    __int64 m_n64NeedMaterialGuid;   //材料GUID
    bool    m_bNeedMaterialBagEnable; 
	unsigned short m_ustNeedMaterialItemId;	// 回炉材料ItemId

	ePlatingType m_ePlatingType;

	bool  m_bDirty;

	Vector m_vVisiblePos;			 // 界面打开时的人物位置,用来自动关闭时使用
    ControlFrame*	m_pID_FRAME_GoldPlating;
//     ControlPicture*	m_pID_PICTURE_DI2;
//     ControlPicture*	m_pID_PICTURE_title2;
//     ControlButton*	m_pID_BUTTON_CLOSE;
//     ControlButton*	m_pID_BUTTON_help;
    ControlText*	m_pID_TEXT_Wall;
    //ControlPicture*	m_pID_PICTURE_ItemWall;
    ControlListImage*	m_pID_LISTIMG_Material;
    ControlListImage*	m_pID_LISTIMG_Armour;
    ControlButton*	m_pID_BUTTON_Ok;
    ControlButton*	m_pID_BUTTON_Cancel;
    ControlText*	m_pID_TEXT_UseMoneyZ;
//     ControlText*	m_pID_TEXT_GoldPlating;
//     ControlPicture*	m_pID_PICTURE_6105;
    ControlText*	m_pID_TEXT_UseMoney;
    //ControlList*	m_pID_LIST_BaseProperty;
    ControlList*	m_pID_LIST_Property;
    //ControlPicture*	m_pID_PICTURE_LeftTitle;
    ControlText*	m_pID_TEXT_Prompt;
    ControlPicture*	m_pID_PICTURE_IdentifyTitle;
//     ControlText*	m_pID_TEXT_Property;
//     ControlText*	m_pID_TEXT_Identify;
    ControlPicture*	m_pID_PICTURE_GoldPlatingTitle;
    //ControlText*	m_pID_TEXT_EspecialProperty;
    ControlList*	m_pID_LIST_Quality;
	ControlButton*	m_pID_BUTTON_Identify;
	ControlPicture*	m_pID_PICTURE_GoldPlatingEffect;
	ControlPicture*	m_pID_PICTURE_IdentifyEffect;
	ControlListImage*	m_pID_LISTIMG_Especial;

	CSlideAnimation m_slideAnimGoldPlating;			//开光序列帧动画
	CSlideAnimation m_slideAnimIdentify;			//鉴定序列帧动画
	bool			m_bStartAnim;

	bool			m_bStartIntonate;
	int				m_nIntonateTime;		// 吟唱时间，毫秒
	DWORD			m_dwStartIntonateTime;	// 开始吟唱时间
};
extern CUI_ID_FRAME_GoldPlating s_CUI_ID_FRAME_GoldPlating;
