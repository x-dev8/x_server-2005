/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\Gem.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_Gem
#define ID_FRAME_Gem		"ID_FRAME_Gem"
#endif  ID_FRAME_Gem
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
#ifndef ID_TEXT_Tip2
#define ID_TEXT_Tip2		"ID_TEXT_Tip2"
#endif  ID_TEXT_Tip2
#ifndef ID_TEXT_Tip1
#define ID_TEXT_Tip1		"ID_TEXT_Tip1"
#endif  ID_TEXT_Tip1
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
#ifndef ID_TEXT_SuccessRatio
#define ID_TEXT_SuccessRatio		"ID_TEXT_SuccessRatio"
#endif  ID_TEXT_SuccessRatio
#ifndef ID_LISTIMG_Material1
#define ID_LISTIMG_Material1		"ID_LISTIMG_Material1"
#endif  ID_LISTIMG_Material1
#ifndef ID_LISTIMG_Material2
#define ID_LISTIMG_Material2		"ID_LISTIMG_Material2"
#endif  ID_LISTIMG_Material2
#ifndef ID_TEXT_Tip3
#define ID_TEXT_Tip3		"ID_TEXT_Tip3"
#endif  ID_TEXT_Tip3
//#ifndef ID_TEXT_Effect
//#define ID_TEXT_Effect			"ID_TEXT_Effect"
//#endif	ID_TEXT_Effect
//#ifndef ID_TEXT_Success
//#define ID_TEXT_Success			"ID_TEXT_Success"
//#endif	ID_TEXT_Success
//#ifndef ID_TEXT_Fail
//#define ID_TEXT_Fail			"ID_TEXT_Fail"
//#endif	ID_TEXT_Fail
#ifndef ID_TEXT_EquiqName
#define ID_TEXT_EquiqName		"ID_TEXT_EquiqName"
#endif  ID_TEXT_EquiqName
#ifndef ID_TEXT_MaterialName
#define ID_TEXT_MaterialName		"ID_TEXT_MaterialName"
#endif  ID_TEXT_MaterialName

#include "GemBase.h"
class CUI_ID_FRAME_Gem : public GemBaseUI
{
	// Member
public:	
	CUI_ID_FRAME_Gem();
	 ControlText*	m_pID_TEXT_Tip2;
	 ControlText*	m_pID_TEXT_Tip1;
	 ControlList*	m_pID_LIST_GemFunction1;
	 ControlList*	m_pID_LIST_GemFunction2;
	 ControlList*	m_pID_LIST_GemFunction3;
	 ControlList*	m_pID_LIST_GemFunction4;
	 ControlText*	m_pID_TEXT_SuccessRatio;
	 ControlListImage*	m_pID_LISTIMG_Material1;
	 ControlListImage*	m_pID_LISTIMG_Material2;
	 ControlText*	m_pID_TEXT_Tip3;
	 //ControlText*	m_pID_TEXT_Effect;
	 //ControlText*	m_pID_TEXT_Success;
	 //ControlText*	m_pID_TEXT_Fail;
	 //DWORD dwBeginTime;
	 //EffectStatus m_status;
	 //bool m_bSendMsg;
	 ControlText*	m_pID_TEXT_EquiqName;
	 ControlText*	m_pID_TEXT_MaterialName;

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

	bool ID_LISTIMG_Material1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Material1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Material2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void		RClickGemIn(ControlObject* pSender, ControlIconDrag::S_ListImg* pItemDrag);

	virtual bool		UpdateGem();
	void        SetRatioVisable(bool bValue);
	//void SetEffectStatus(EffectStatus status){m_status = status;}
	//void SetBeginTime(DWORD time){dwBeginTime = time;}
protected:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI

protected:
	virtual int			GetEvolveType(){return MsgEquipEvolve::ET_Inlay;}
	virtual int			GetEvolveMaterialType() {return  ItemDefine::ematerial_max;}
	virtual bool		IsEvolveAllDone(ControlIconDrag::S_ListImg * pImg) ;
	virtual int			GetEvolveMoneyCost();
	virtual void		SendEvolveMsg();
	virtual bool		ProcessAllDone(ControlIconDrag::S_ListImg * pImg);
	virtual void		TipVisible(bool IsHoleExist);
	virtual void _SetVisable( const bool bVisable );

	bool OnDragOnGem(int index, ControlIconDrag::S_ListImg* pItemDrag, ControlObject* pSender );
	bool OnGemRemove(int index);
	bool _IsExistEmptyHole( ControlIconDrag::S_ListImg * pImg );
	virtual char*		GetSlideEffectPath() {return NULL;}

	virtual void		RefreshAllBagEnable();
	virtual void ClearEquip();
	virtual void ResetUIObjects();
	virtual void _RefreshEquipInfo( ControlIconDrag::S_ListImg*  pListImg );

	virtual void RefreshDragEnable( SCharItem* pItem, int index );
	virtual void RefreshOkButton();

	ControlList* m_GemInfoList[m_nMaxHoleNum];
	int			GetEmptyHole();
	bool		IsGemTypeMatch(ControlIconDrag::S_ListImg* pItemDrag);
	static void OnVisibleChange( ControlObject* pUIObject ); 
	bool        IsHaveSameGem(ControlIconDrag::S_ListImg* pItemDrag);
	void        SetShowTip(int nValue);
	void		ShowItemName(ControlText* pText, ControlIconDrag::S_ListImg* pItemDrag);

	void ClearMaterialIcon();
	void ShowMaterialIcon();
	ControlIconDrag::S_ListImg* RetriveMaterialImg( short itemId ,int& nIndex);

private:
	void RefreshSuccessRatio(void);
};
extern CUI_ID_FRAME_Gem s_CUI_ID_FRAME_Gem;
