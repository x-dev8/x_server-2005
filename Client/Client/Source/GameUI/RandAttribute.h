/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\RandAttribute.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "ItemEnableChangeSysBase.h"
#include "ItemDetail.h"

#ifndef ID_FRAME_RandAttribute
#define ID_FRAME_RandAttribute		"ID_FRAME_RandAttribute"
#endif  ID_FRAME_RandAttribute
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_TEXT_Introduce
#define ID_TEXT_Introduce		"ID_TEXT_Introduce"
#endif  ID_TEXT_Introduce
#ifndef ID_LISTIMG_Armour
#define ID_LISTIMG_Armour		"ID_LISTIMG_Armour"
#endif  ID_LISTIMG_Armour
#ifndef ID_LIST_Introduce
#define ID_LIST_Introduce		"ID_LIST_Introduce"
#endif  ID_LIST_Introduce
#ifndef ID_TEXT_Success
#define ID_TEXT_Success		"ID_TEXT_Success"
#endif  ID_TEXT_Success
#ifndef ID_TEXT_Fail
#define ID_TEXT_Fail		"ID_TEXT_Fail"
#endif  ID_TEXT_Fail
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_TEXT_Material_NotEnougth
#define ID_TEXT_Material_NotEnougth		"ID_TEXT_Material_NotEnougth"
#endif  ID_TEXT_Material_NotEnougth
#ifndef ID_TEXT_EquipName
#define ID_TEXT_EquipName		"ID_TEXT_EquipName"
#endif  ID_TEXT_EquipName
#ifndef ID_TEXT_MaterialName
#define ID_TEXT_MaterialName		"ID_TEXT_MaterialName"
#endif  ID_TEXT_MaterialName

class CUI_ID_FRAME_RandAttribute : public CUIBase, CItemEnableChangeSysBase
{
	// Member
	enum ImgTpye
	{
		IT_Armour,
		IT_Material,
	};

public:	
	enum EffectStatus
	{
		EffectStatus_No,
		EffectStatus_Fail,
		EffectStatus_Success
	};

	CUI_ID_FRAME_RandAttribute();
	virtual ~CUI_ID_FRAME_RandAttribute();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_LIST_IntroduceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	virtual bool IsPackItemBeUsing( __int64 nGuid );
	static void OnVisibleChange( ControlObject* pUIObject );

	void SetEffectStatus(EffectStatus status){m_status = status;}
	void SetBeginTime(DWORD time){dwBeginTime = time;}

	void ClearAll();
	void ShowItemName(ControlText* pText, ControlIconDrag::S_ListImg* pItemDrag);
	void ClearImg(ImgTpye itype,ControlListImage *pTargetImg);

	void RefreshMoney();
	void RefreshOkButton();
	void RefreshItemInfo(SCharItem &m_item);
	void SendMsg();
	void UpdataAll();

	void ShowMaterialIcon();
	ControlIconDrag::S_ListImg* RetriveMaterialImg( short itemId ,int& nIndex);

private:
	ControlFrame*	m_pID_FRAME_RandAttribute;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlButton*	m_pID_BUTTON_HELP;
	ControlText*	m_pID_TEXT_Money;
	ControlButton*	m_pID_BUTTON_Cancel;
	ControlButton*	m_pID_BUTTON_Ok;
	ControlText*	m_pID_TEXT_Introduce;
	ControlListImage*	m_pID_LISTIMG_Armour;
	ControlList*	m_pID_LIST_Introduce;
	ControlText*	m_pID_TEXT_Success;
	ControlText*	m_pID_TEXT_Fail;
	ControlListImage*	m_pID_LISTIMG_Material;
	ControlText*	m_pID_TEXT_Material_NotEnougth;
	ControlText*	m_pID_TEXT_EquipName;
	ControlText*	m_pID_TEXT_MaterialName;

	EffectStatus m_status;
	DWORD dwBeginTime;

	ControlObject* m_ArmourSender;
	ControlObject* m_MaterialSender;

	struct SMaterials
	{
		uint8 nItemBagType  ;
		int16 nItemIndex    ;
		int64 nItemGuid     ;

		SMaterials()
		{
			nItemBagType = 0;
			nItemIndex = -1;
			nItemGuid = 0;
		}
	};

	SMaterials m_Armour;
	SMaterials m_Material;
};
extern CUI_ID_FRAME_RandAttribute s_CUI_ID_FRAME_RandAttribute;
