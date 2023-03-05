/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\Symbol.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_Symbol
#define ID_FRAME_Symbol		"ID_FRAME_Symbol"
#endif  ID_FRAME_Symbol
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_Rate
#define ID_TEXT_Rate		"ID_TEXT_Rate"
#endif  ID_TEXT_Rate
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_TEXT_Tip
#define ID_TEXT_Tip		"ID_TEXT_Tip"
#endif  ID_TEXT_Tip
#ifndef ID_LIST_Attribute
#define ID_LIST_Attribute		"ID_LIST_Attribute"
#endif  ID_LIST_Attribute
#ifndef ID_PICTURE_Begin
#define ID_PICTURE_Begin		"ID_PICTURE_Begin"
#endif  ID_PICTURE_Begin
#ifndef ID_LISTIMG_Equip
#define ID_LISTIMG_Equip		"ID_LISTIMG_Equip"
#endif  ID_LISTIMG_Equip
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_PICTURE_StarEffect
#define ID_PICTURE_StarEffect		"ID_PICTURE_StarEffect"
#endif  ID_PICTURE_StarEffect
#include "EquipEvolve.h"
class CUI_ID_FRAME_Symbol : public EquipEvolveUI
{
	// Member
public:	
	 CUI_ID_FRAME_Symbol();
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_Rate;
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
	void ID_LIST_AttributeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_LISTIMG_EquipOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_EquipOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_EquipOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_EquipOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
public:
	virtual bool UpdateGem();

	virtual void		ClearEquip();

protected:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI

protected:
	virtual int			GetEvolveType(){return MsgEquipEvolve::ET_Charm;}
	virtual int			GetEvolveMaterialType() {return  ItemDefine::ematerial_charm;}
	virtual bool		IsEvolveAllDone(ControlIconDrag::S_ListImg * pImg){return false;}
	virtual void		TipVisible(bool IsMaterialExist) ;
	virtual void		ResetUIObjects();

	virtual bool		ProcessAllDone(ControlIconDrag::S_ListImg * pImg){return false;}


	static void			OnVisibleChange( ControlObject* pUIObject ); 

	virtual void		_RefreshEquipInfo( ControlIconDrag::S_ListImg*  pListImg );

	virtual bool		MatchMaterialOption(SCharItem* pItem);

	void				UpdateRateText();
};
extern CUI_ID_FRAME_Symbol s_CUI_ID_FRAME_Symbol;
