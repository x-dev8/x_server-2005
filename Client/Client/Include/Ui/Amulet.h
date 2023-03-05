/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\Amulet.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_Amulet
#define ID_FRAME_Amulet		"ID_FRAME_Amulet"
#endif  ID_FRAME_Amulet
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_TEXT_Tip
#define ID_TEXT_Tip		"ID_TEXT_Tip"
#endif  ID_TEXT_Tip
#ifndef ID_LIST_Amulet
#define ID_LIST_Amulet		"ID_LIST_Amulet"
#endif  ID_LIST_Amulet
#ifndef ID_LIST_Symbol
#define ID_LIST_Symbol		"ID_LIST_Symbol"
#endif  ID_LIST_Symbol
#ifndef ID_PICTURE_Begin
#define ID_PICTURE_Begin		"ID_PICTURE_Begin"
#endif  ID_PICTURE_Begin
#ifndef ID_LISTIMG_Amulet
#define ID_LISTIMG_Amulet		"ID_LISTIMG_Amulet"
#endif  ID_LISTIMG_Amulet
#ifndef ID_LISTIMG_Symbol
#define ID_LISTIMG_Symbol		"ID_LISTIMG_Symbol"
#endif  ID_LISTIMG_Symbol
#ifndef ID_PICTURE_StarEffect
#define ID_PICTURE_StarEffect		"ID_PICTURE_StarEffect"
#endif  ID_PICTURE_StarEffect
#ifndef ID_TEXT_TipAllDone
#define ID_TEXT_TipAllDone		"ID_TEXT_TipAllDone"
#endif  ID_TEXT_TipAllDone
#include "EquipEvolve.h"
class CUI_ID_FRAME_Amulet : public EquipEvolveUI
{
	// Member
public:	
	 CUI_ID_FRAME_Amulet();
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_Tip;
	 ControlList*	m_pID_LIST_Amulet;
	 ControlList*	m_pID_LIST_Symbol;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	void ID_LIST_AmuletOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_SymbolOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_LISTIMG_AmuletOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_AmuletOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_AmuletOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_AmuletOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SymbolOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_SymbolOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SymbolOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SymbolOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	void				ClearSymbol();

protected:
	virtual int			GetEvolveType(){return MsgEquipEvolve::ET_Amulet;}
	virtual int			GetEvolveMaterialType() {return  ItemDefine::ematerial_charm;}
	virtual bool		IsEvolveAllDone(ControlIconDrag::S_ListImg * pImg);
	virtual void		ResetUIObjects();
	virtual void		ClearEquip();
	virtual bool		ProcessAllDone(ControlIconDrag::S_ListImg * pImg);

	virtual void		_RefreshEquipInfo( ControlIconDrag::S_ListImg*  pListImg );
	virtual void		RefreshBeginPic();

	static void			OnVisibleChange( ControlObject* pUIObject ); 

	virtual void		TipVisible(bool IsMaterialExist) {;}

	int					GetBlueAttriCount(SCharItem* psItem);
	virtual bool		UpdateGem(){return true;}
protected:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
};
extern CUI_ID_FRAME_Amulet s_CUI_ID_FRAME_Amulet;
