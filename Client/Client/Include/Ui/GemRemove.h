/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\GemRemove.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GemRemove
#define ID_FRAME_GemRemove		"ID_FRAME_GemRemove"
#endif  ID_FRAME_GemRemove
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_TEXT_Tip1
#define ID_TEXT_Tip1		"ID_TEXT_Tip1"
#endif  ID_TEXT_Tip1
#ifndef ID_TEXT_Tip2
#define ID_TEXT_Tip2		"ID_TEXT_Tip2"
#endif  ID_TEXT_Tip2
#ifndef ID_TEXT_TipAllDone
#define ID_TEXT_TipAllDone		"ID_TEXT_TipAllDone"
#endif  ID_TEXT_TipAllDone
#ifndef ID_PICTURE_Open1
#define ID_PICTURE_Open1		"ID_PICTURE_Open1"
#endif  ID_PICTURE_Open1
#ifndef ID_PICTURE_Open2
#define ID_PICTURE_Open2		"ID_PICTURE_Open2"
#endif  ID_PICTURE_Open2
#ifndef ID_PICTURE_Open3
#define ID_PICTURE_Open3		"ID_PICTURE_Open3"
#endif  ID_PICTURE_Open3
#ifndef ID_PICTURE_Open4
#define ID_PICTURE_Open4		"ID_PICTURE_Open4"
#endif  ID_PICTURE_Open4
#ifndef ID_LISTIMG_Hole1
#define ID_LISTIMG_Hole1		"ID_LISTIMG_Hole1"
#endif  ID_LISTIMG_Hole1
#ifndef ID_LISTIMG_Hole2
#define ID_LISTIMG_Hole2		"ID_LISTIMG_Hole2"
#endif  ID_LISTIMG_Hole2
#ifndef ID_LISTIMG_Hole3
#define ID_LISTIMG_Hole3		"ID_LISTIMG_Hole3"
#endif  ID_LISTIMG_Hole3
#ifndef ID_LISTIMG_Hole4
#define ID_LISTIMG_Hole4		"ID_LISTIMG_Hole4"
#endif  ID_LISTIMG_Hole4
#ifndef ID_PICTURE_Lock1
#define ID_PICTURE_Lock1		"ID_PICTURE_Lock1"
#endif  ID_PICTURE_Lock1
#ifndef ID_PICTURE_Lock2
#define ID_PICTURE_Lock2		"ID_PICTURE_Lock2"
#endif  ID_PICTURE_Lock2
#ifndef ID_PICTURE_Lock3
#define ID_PICTURE_Lock3		"ID_PICTURE_Lock3"
#endif  ID_PICTURE_Lock3
#ifndef ID_PICTURE_Lock4
#define ID_PICTURE_Lock4		"ID_PICTURE_Lock4"
#endif  ID_PICTURE_Lock4
#ifndef ID_PICTURE_Begin
#define ID_PICTURE_Begin		"ID_PICTURE_Begin"
#endif  ID_PICTURE_Begin
#ifndef ID_LISTIMG_Armour
#define ID_LISTIMG_Armour		"ID_LISTIMG_Armour"
#endif  ID_LISTIMG_Armour
#ifndef ID_PICTURE_StarEffect
#define ID_PICTURE_StarEffect		"ID_PICTURE_StarEffect"
#endif  ID_PICTURE_StarEffect
#ifndef ID_TEXT_EquipName
#define ID_TEXT_EquipName		"ID_TEXT_EquipName"
#endif  ID_TEXT_EquipName
#ifndef ID_TEXT_MaterialName
#define ID_TEXT_MaterialName		"ID_TEXT_MaterialName"
#endif  ID_TEXT_MaterialName
#ifndef ID_TEXT_Gem1_Name
#define ID_TEXT_Gem1_Name		"ID_TEXT_Gem1_Name"
#endif  ID_TEXT_Gem1_Name
#ifndef ID_TEXT_Gem2_Name
#define ID_TEXT_Gem2_Name		"ID_TEXT_Gem2_Name"
#endif  ID_TEXT_Gem2_Name

#include "GemBase.h"
class CUI_ID_FRAME_GemRemove :public GemBaseUI
{
	// Member
public:	
	 CUI_ID_FRAME_GemRemove();
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_Tip2;
	 ControlText*	m_pID_TEXT_Tip1;
	 ControlText*	m_pID_TEXT_EquipName;
	 ControlText*	m_pID_TEXT_MaterialName;
	 ControlText*	m_pID_TEXT_Gem1_Name;
	 ControlText*	m_pID_TEXT_Gem2_Name;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_Hole1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Hole1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Hole2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole3OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Hole3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole4OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Hole4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	virtual bool		UpdateGem();

protected:
	bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
protected:
	virtual int			GetEvolveType(){return MsgEquipEvolve::ET_TakeDown;}
	virtual int			GetEvolveMaterialType() {return  ItemDefine::ematerial_gemtakedown;}
	virtual bool		IsEvolveAllDone(ControlIconDrag::S_ListImg * pImg);
	virtual void		_RefreshEquipInfo( ControlIconDrag::S_ListImg*  pListImg );

	virtual bool		OnDirty();
	virtual void		SendEvolveMsg();
	virtual bool		ProcessAllDone(ControlIconDrag::S_ListImg * pImg);
	virtual void		TipVisible(bool IsMaterialExist);
	virtual void		ClearEquip();
	virtual void		ResetUIObjects();
	virtual int			GetEvolveMoneyCost();
	virtual bool		IsMatchOther(ItemDefine::SCreateMaterial* pMaterial);

	static void			OnVisibleChange( ControlObject* pUIObject ); 

	void ShowGemName(ControlText* pText, uint16 itemId);
	void ShowItemName(ControlText* pText, ControlIconDrag::S_ListImg* pItemDrag);

protected:
	bool				_IsGemExist(ControlIconDrag::S_ListImg * pImg);
	bool				SelectGem(int index, ControlIconDrag::S_ListImg* pGemItem);
	int					m_SelectGemIndex;
};
extern CUI_ID_FRAME_GemRemove s_CUI_ID_FRAME_GemRemove;
