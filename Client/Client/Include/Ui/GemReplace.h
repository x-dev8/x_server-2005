/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\GemReplace.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GemReplace
#define ID_FRAME_GemReplace		"ID_FRAME_GemReplace"
#endif  ID_FRAME_GemReplace
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
#ifndef ID_LIST_GemFunction1
#define ID_LIST_GemFunction1		"ID_LIST_GemFunction1"
#endif  ID_LIST_GemFunction1
#ifndef ID_LIST_GemFunction2
#define ID_LIST_GemFunction2		"ID_LIST_GemFunction2"
#endif  ID_LIST_GemFunction2
#ifndef ID_LIST_GemFunction3
#define ID_LIST_GemFunction3		"ID_LIST_GemFunction3"
#endif  ID_LIST_GemFunction3
#ifndef ID_LIST_GemFunction4
#define ID_LIST_GemFunction4		"ID_LIST_GemFunction4"
#endif  ID_LIST_GemFunction4
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
#ifndef ID_PICTURE_StarEffect
#define ID_PICTURE_StarEffect		"ID_PICTURE_StarEffect"
#endif  ID_PICTURE_StarEffect
#ifndef ID_TEXT_TipAllDone
#define ID_TEXT_TipAllDone		"ID_TEXT_TipAllDone"
#endif  ID_TEXT_TipAllDone
#ifndef ID_PICTURE_Begin
#define ID_PICTURE_Begin		"ID_PICTURE_Begin"
#endif  ID_PICTURE_Begin
#ifndef ID_LISTIMG_Armour
#define ID_LISTIMG_Armour		"ID_LISTIMG_Armour"
#endif  ID_LISTIMG_Armour

#include "GemBase.h"
class CUI_ID_FRAME_GemReplace : public GemBaseUI
{
	// Member
public:	
	 CUI_ID_FRAME_GemReplace();
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_Tip;
	 ControlList*	m_pID_LIST_GemFunction1;
	 ControlList*	m_pID_LIST_GemFunction2;
	 ControlList*	m_pID_LIST_GemFunction3;
	 ControlList*	m_pID_LIST_GemFunction4;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	void ID_LIST_GemFunction1OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_GemFunction2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_GemFunction3OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_GemFunction4OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
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
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI

protected:
	virtual int			GetEvolveType(){return MsgEquipEvolve::ET_Replace;}
	virtual int			GetEvolveMaterialType() {return  ItemDefine::ematerial_max;}
	virtual bool		IsEvolveAllDone(ControlIconDrag::S_ListImg * pImg) ;
	virtual int			GetEvolveMoneyCost();
	virtual void		SendEvolveMsg();
	virtual bool		ProcessAllDone(ControlIconDrag::S_ListImg * pImg);
	virtual void		TipVisible(bool IsHoleExist);


	bool _IsExistGem( ControlIconDrag::S_ListImg * pImg );
	virtual char*		GetSlideEffectPath() {return NULL;}

	virtual void		RefreshAllBagEnable();
	bool OnDragOnGem(int index, ControlIconDrag::S_ListImg* pItemDrag, ControlObject* pSender );
	bool OnGemRemove(int index);
	virtual void ClearEquip();
	virtual void ResetUIObjects();
	virtual void _RefreshEquipInfo( ControlIconDrag::S_ListImg*  pListImg );

	virtual void RefreshDragEnable( SCharItem* pItem, int index );

	ControlList* m_GemInfoList[m_nMaxHoleNum];
	int			GetEmptyHole();
	bool		IsGemTypeMatch(ControlIconDrag::S_ListImg* pItemDrag);
	static void OnVisibleChange( ControlObject* pUIObject ); 
};
extern CUI_ID_FRAME_GemReplace s_CUI_ID_FRAME_GemReplace;
