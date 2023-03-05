/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\Soul.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "me3d/Vector.h"
#include "GlobalDef.h"
#include "MeUi/Animation/SlideAnimation.h"
#include "SoulConfig.h"

#ifndef ID_FRAME_Soul
#define ID_FRAME_Soul		"ID_FRAME_Soul"
#endif  ID_FRAME_Soul
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_LIST_ArmourProperty
#define ID_LIST_ArmourProperty		"ID_LIST_ArmourProperty"
#endif  ID_LIST_ArmourProperty
#ifndef ID_LIST_TargetProperty
#define ID_LIST_TargetProperty		"ID_LIST_TargetProperty"
#endif  ID_LIST_TargetProperty
#ifndef ID_LISTIMG_Target
#define ID_LISTIMG_Target		"ID_LISTIMG_Target"
#endif  ID_LISTIMG_Target
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_TEXT_Equip1
#define ID_TEXT_Equip1		"ID_TEXT_Equip1"
#endif  ID_TEXT_Equip1
#ifndef ID_TEXT_Equip2
#define ID_TEXT_Equip2		"ID_TEXT_Equip2"
#endif  ID_TEXT_Equip2
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_TEXT_Tip
#define ID_TEXT_Tip		"ID_TEXT_Tip"
#endif  ID_TEXT_Tip
#ifndef ID_PICTURE_Begin
#define ID_PICTURE_Begin		"ID_PICTURE_Begin"
#endif  ID_PICTURE_Begin
#ifndef ID_LISTIMG_Armour
#define ID_LISTIMG_Armour		"ID_LISTIMG_Armour"
#endif  ID_LISTIMG_Armour
#ifndef ID_PICTURE_StarEffect
#define ID_PICTURE_StarEffect		"ID_PICTURE_StarEffect"
#endif  ID_PICTURE_StarEffect
#ifndef ID_LISTIMG_Material1
#define ID_LISTIMG_Material1		"ID_LISTIMG_Material1"
#endif  ID_LISTIMG_Material1


#include "EquipEvolve.h"
class CUI_ID_FRAME_Soul : public EquipEvolveUI
{
	// Member
public:	
	 CUI_ID_FRAME_Soul();

	 void ResetUIObjects();
	 ControlList*	m_pID_LIST_ArmourProperty;
	 ControlList*	m_pID_LIST_TargetProperty;
	 ControlListImage*	m_pID_LISTIMG_Target;
	 ControlText*	m_pID_TEXT_Equip1;
	 ControlText*	m_pID_TEXT_Equip2;
	 ControlText*	m_pID_TEXT_Tip;
	 ControlListImage*	m_pID_LISTIMG_Material1;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	void ID_LIST_ArmourPropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_TargetPropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_LISTIMG_TargetOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_TargetOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_TargetOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_TargetOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Material1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	void OnMaterialItemDrag( ControlObject* pSender, ControlIconDrag::S_ListImg* pItemDrag );

	virtual bool UpdateGem();

private:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI

protected:
	virtual int			GetEvolveType(){return MsgEquipEvolve::ET_SoulStamp;}
	virtual int			GetEvolveMaterialType() {return  ItemDefine::ematerial_soulstamp;}
	virtual bool		IsEvolveAllDone(ControlIconDrag::S_ListImg * pImg);
	virtual char*		GetSlideEffectPath() {return NULL;}
	virtual void		TipVisible(bool IsMaterialExist);
	virtual bool		ProcessAllDone(ControlIconDrag::S_ListImg * pImg);

	void UpdateArmourInfo( SCharItem* pItem );
	virtual void _RefreshEquipInfo( ControlIconDrag::S_ListImg*  pListImg );
	virtual void ClearEquip();
	virtual void SetAtomVisible( bool bVisible );
	virtual void RefreshNeedMoney();
	virtual void RefreshOkButton();
	virtual void SendEvolveMsg();


	static void OnVisibleChange( ControlObject* pUIObject ); 

	void ShowWeapon( ItemDefine::SItemCommon* pItemCommon, SCharItem* pItem );
	void ShowArmour( ItemDefine::SItemCommon* pItemCommon, SCharItem* pItem );
	void AddToList( std::string& strDes, float fValue );

	struct SMaterial
	{
		SMaterial()
		{
			nCount = 0;
			nId = 0;
			nIndex = -1;
		}
		int nCount;
		int nId;
		int nIndex;
	};

	SMaterial m_sMaterial[SoulConfig::ED_Max_Material];

};
extern CUI_ID_FRAME_Soul s_CUI_ID_FRAME_Soul;
