/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\Purple.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_Purple
#define ID_FRAME_Purple		"ID_FRAME_Purple"
#endif  ID_FRAME_Purple
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_TEXT_EquipName
#define ID_TEXT_EquipName		"ID_TEXT_EquipName"
#endif  ID_TEXT_EquipName
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
#ifndef ID_LISTIMG_Equip
#define ID_LISTIMG_Equip		"ID_LISTIMG_Equip"
#endif  ID_LISTIMG_Equip
#ifndef ID_PICTURE_StarEffect
#define ID_PICTURE_StarEffect		"ID_PICTURE_StarEffect"
#endif  ID_PICTURE_StarEffect
#ifndef ID_TEXT_TipAllDone
#define ID_TEXT_TipAllDone		"ID_TEXT_TipAllDone"
#endif  ID_TEXT_TipAllDone
#ifndef ID_LIST_Attribute
#define ID_LIST_Attribute		"ID_LIST_Attribute"
#endif  ID_LIST_Attribute

#include "EquipEvolve.h"
class CUI_ID_FRAME_Purple : public EquipEvolveUI
{
	// Member
public:	
	 CUI_ID_FRAME_Purple();
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_EquipName;
	 ControlText*	m_pID_TEXT_Tip;
	 ControlList*	m_pID_LIST_Attribute;

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
	bool ID_LISTIMG_EquipOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_EquipOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_EquipOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_EquipOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
protected:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
protected:
	virtual int			GetEvolveType(){return MsgEquipEvolve::ET_OpenLight;}
	virtual int			GetEvolveMaterialType() {return  ItemDefine::ematerial_openlight;}
	virtual bool		IsEvolveAllDone(ControlIconDrag::S_ListImg * pImg);
	virtual char*		GetSlideEffectPath() {return NULL;}
	virtual void		TipVisible(bool IsMaterialExist);
	virtual bool		ProcessAllDone(ControlIconDrag::S_ListImg * pImg);
	virtual void		ResetUIObjects();
	virtual void		ClearEquip();

	void UpdateArmourInfo( SCharItem* pItem );
	virtual void _RefreshEquipInfo( ControlIconDrag::S_ListImg*  pListImg );

	bool				IsOpenLighted(SCharItem* psItem);

	static void OnVisibleChange( ControlObject* pUIObject ); 
};
extern CUI_ID_FRAME_Purple s_CUI_ID_FRAME_Purple;
