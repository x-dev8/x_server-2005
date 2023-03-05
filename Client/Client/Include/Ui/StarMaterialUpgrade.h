/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\策划文档\升星\StarMaterialUpgrade.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "me3d/Vector.h"
#include "ItemComposeConfig.h"
#include "MeUi/Animation/SlideAnimation.h"
#include "ItemEnableChangeSysBase.h"

#ifndef ID_FRAME_StarMaterialUpgrade
#define ID_FRAME_StarMaterialUpgrade		"ID_FRAME_StarMaterialUpgrade"
#endif  ID_FRAME_StarMaterialUpgrade
#ifndef ID_PICTURE_Material2
#define ID_PICTURE_Material2		"ID_PICTURE_Material2"
#endif  ID_PICTURE_Material2
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_LISTIMG_Result
#define ID_LISTIMG_Result		"ID_LISTIMG_Result"
#endif  ID_LISTIMG_Result
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
#ifndef ID_PICTURE_Material
#define ID_PICTURE_Material		"ID_PICTURE_Material"
#endif  ID_PICTURE_Material
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_LISTIMG_Material2
#define ID_LISTIMG_Material2		"ID_LISTIMG_Material2"
#endif  ID_LISTIMG_Material2
#ifndef ID_PICTURE_Material3
#define ID_PICTURE_Material3		"ID_PICTURE_Material3"
#endif  ID_PICTURE_Material3
#ifndef ID_LISTIMG_Material3
#define ID_LISTIMG_Material3		"ID_LISTIMG_Material3"
#endif  ID_LISTIMG_Material3
#ifndef ID_PICTURE_Material4
#define ID_PICTURE_Material4		"ID_PICTURE_Material4"
#endif  ID_PICTURE_Material4
#ifndef ID_LISTIMG_Material4
#define ID_LISTIMG_Material4		"ID_LISTIMG_Material4"
#endif  ID_LISTIMG_Material4
#ifndef ID_PICTURE_Material5
#define ID_PICTURE_Material5		"ID_PICTURE_Material5"
#endif  ID_PICTURE_Material5
#ifndef ID_LISTIMG_Material5
#define ID_LISTIMG_Material5		"ID_LISTIMG_Material5"
#endif  ID_LISTIMG_Material5
#ifndef ID_TEXT_RateZ
#define ID_TEXT_RateZ		"ID_TEXT_RateZ"
#endif  ID_TEXT_RateZ
#ifndef ID_TEXT_Rate
#define ID_TEXT_Rate		"ID_TEXT_Rate"
#endif  ID_TEXT_Rate
#ifndef ID_PICTURE_Line2
#define ID_PICTURE_Line2		"ID_PICTURE_Line2"
#endif  ID_PICTURE_Line2
#ifndef ID_PICTURE_Line5
#define ID_PICTURE_Line5		"ID_PICTURE_Line5"
#endif  ID_PICTURE_Line5
#ifndef ID_PICTURE_Line3
#define ID_PICTURE_Line3		"ID_PICTURE_Line3"
#endif  ID_PICTURE_Line3
#ifndef ID_PICTURE_Line4
#define ID_PICTURE_Line4		"ID_PICTURE_Line4"
#endif  ID_PICTURE_Line4
#ifndef ID_PICTURE_Line
#define ID_PICTURE_Line		"ID_PICTURE_Line"
#endif  ID_PICTURE_Line
#ifndef ID_PICTURE_StarUpgradeEffect
#define ID_PICTURE_StarUpgradeEffect		"ID_PICTURE_StarUpgradeEffect"
#endif  ID_PICTURE_StarUpgradeEffect

#include "UiBase.h"
class CUI_ID_FRAME_StarMaterialUpgrade :public CUIBase, CItemEnableChangeSysBase
{
	// Member
public:	
	 CUI_ID_FRAME_StarMaterialUpgrade();
private:
	 ControlFrame*	m_pID_FRAME_StarMaterialUpgrade;
	 ControlPicture*	m_pID_PICTURE_Material2;
// 	 ControlButton*	m_pID_BUTTON_CLOSE;
// 	 ControlButton*	m_pID_BUTTON_help;
	 ControlListImage*	m_pID_LISTIMG_Result;
	 ControlButton*	m_pID_BUTTON_Ok;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlText*	m_pID_TEXT_UseMoneyZ;
	 ControlText*	m_pID_TEXT_UseMoney;
	 ControlPicture*	m_pID_PICTURE_Material;
	 ControlListImage*	m_pID_LISTIMG_Material;
	 ControlListImage*	m_pID_LISTIMG_Material2;
	 ControlPicture*	m_pID_PICTURE_Material3;
	 ControlListImage*	m_pID_LISTIMG_Material3;
	 ControlPicture*	m_pID_PICTURE_Material4;
	 ControlListImage*	m_pID_LISTIMG_Material4;
	 ControlPicture*	m_pID_PICTURE_Material5;
	 ControlListImage*	m_pID_LISTIMG_Material5;
	 ControlText*	m_pID_TEXT_RateZ;
	 ControlText*	m_pID_TEXT_Rate;
	 ControlPicture*	m_pID_PICTURE_Line2;
	 ControlPicture*	m_pID_PICTURE_Line5;
	 ControlPicture*	m_pID_PICTURE_Line3;
	 ControlPicture*	m_pID_PICTURE_Line4;
	 ControlPicture*	m_pID_PICTURE_Line;
	 ControlPicture*	m_pID_PICTURE_StarUpgradeEffect;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
// 	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ResultOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ResultOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ResultOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ResultOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Material2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material3OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Material3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material4OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Material4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material5OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Material5OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material5OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material5OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
	// iMaterialSlot != -1，则玩家把材料直接拖到第iMaterialSlot个材料槽里
	bool PutItemFromPack( ControlObject* pSender, ControlIconDrag::S_ListImg* pItemDrag, int iBagType, int iItemIndex, int iItemSlot = -1 );
	void ClearAll();
	void ClearItems();

	static void OnVisibleChanged(ControlObject* pSender);
    virtual bool IsPackItemBeUsing( __int64 nGuid );

	ControlFrame* GetFrame() {return m_pID_FRAME_StarMaterialUpgrade;}

private:
	bool SetMaterial(int iBagType, int index, __int64 n64Guid);
	bool SetItem(int iSlot, int iBagType, int index, __int64 n64Guid);
	int	 FindEmptyItemSlot();
	void ResetObjects();
	void ResetMembers();
	void ClearMaterial();
	void ClearItem(int id);
	void RefreshRateAndMoney();
	bool CanUpgrate(bool bShowInfo);
	void EnableBagItem(bool bEnable, int iBagType, int iItemIndex);
	void ClearAnim();

	Vector m_vVisiblePos;

	enum EConstDefine
	{
		ECD_MaxCount = 5,
	};

	struct ComposeItem
	{
		ComposeItem() : uchItemBagType( 0 ), stItemIndex( -1 ), n64ItemGuid( 0 ){}
		uint8 uchItemBagType;
		int16 stItemIndex;
		__int64 n64ItemGuid;
	};


	// 升级需要的原材料数据
	ComposeItem		m_xItem[ ECD_MaxCount ];          // 5个合成原材料
	ComposeData*	m_pComposeData;
	DWORD			m_dwCostMoney;
	int				m_iItemCount;
	int				m_iMainItemId;

	// 需要的材料
	int				m_iMaterialID;
	uint8			m_uchMaterialBagType;
	int				m_stMaterialIndex;
	__int64			m_n64MaterialGuid;

	bool			m_bUpdateRateAndMoney;

	CSlideAnimation m_slideAnim; //序列帧动画
	bool			m_bStartAnim;

	bool			m_bStartIntonate;
	int				m_nIntonateTime;		// 吟唱时间，毫秒
	DWORD			m_dwStartIntonateTime;	// 开始吟唱时间
};
extern CUI_ID_FRAME_StarMaterialUpgrade s_CUI_ID_FRAME_StarMaterialUpgrade;
