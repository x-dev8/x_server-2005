/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\EquipReturn.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_EquipReturn
#define ID_FRAME_EquipReturn		"ID_FRAME_EquipReturn"
#endif  ID_FRAME_EquipReturn
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_LISTIMG_Equip
#define ID_LISTIMG_Equip		"ID_LISTIMG_Equip"
#endif  ID_LISTIMG_Equip
#ifndef ID_PICTURE_StarEffect
#define ID_PICTURE_StarEffect		"ID_PICTURE_StarEffect"
#endif  ID_PICTURE_StarEffect
#ifndef ID_TEXT_ReturnMoney
#define ID_TEXT_ReturnMoney		"ID_TEXT_ReturnMoney"
#endif  ID_TEXT_ReturnMoney

#include "EquipEvolve.h"
class CUI_ID_FRAME_EquipReturn : public EquipEvolveUI
{
	// Member
public:	
	 CUI_ID_FRAME_EquipReturn();
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_ReturnMoney;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_EquipOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_EquipOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_EquipOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_EquipOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	virtual bool UpdateGem();
	virtual void RefreshOkButton();
	virtual void		ClearEquip();

protected:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI

protected:
	virtual int			GetEvolveType(){return MsgEquipEvolve::ET_Max;}
	virtual int			GetEvolveMaterialType() {return  ItemDefine::ematerial_max;}
	virtual bool		IsEvolveAllDone(ControlIconDrag::S_ListImg * pImg){return false;}
	virtual char*		GetSlideEffectPath() {return NULL;}
	virtual void		TipVisible(bool IsMaterialExist){;}
	virtual bool		ProcessAllDone(ControlIconDrag::S_ListImg * pImg){return false;}
	virtual void		ResetUIObjects();
	virtual void		_RefreshEquipInfo( ControlIconDrag::S_ListImg*  pListImg );
	virtual bool		OnOkClick();

	virtual void		SendEvolveMsg();

	static void			OnVisibleChange( ControlObject* pUIObject ); 

};
extern CUI_ID_FRAME_EquipReturn s_CUI_ID_FRAME_EquipReturn;
