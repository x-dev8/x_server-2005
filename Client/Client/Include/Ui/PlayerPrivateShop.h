/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\PlayerPrivateShop.h
*********************************************************************/
#pragma once

#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "GlobalDef.h"

#ifndef ID_FRAME_PlayerPrivateShop
#define ID_FRAME_PlayerPrivateShop		"ID_FRAME_PlayerPrivateShop"
#endif  ID_FRAME_PlayerPrivateShop
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_LISTIMG_CommonList
#define ID_LISTIMG_CommonList		"ID_LISTIMG_CommonList"
#endif  ID_LISTIMG_CommonList
#ifndef ID_BUTTON_Buy
#define ID_BUTTON_Buy		"ID_BUTTON_Buy"
#endif  ID_BUTTON_Buy
#ifndef ID_TEXT_Price
#define ID_TEXT_Price		"ID_TEXT_Price"
#endif  ID_TEXT_Price
#ifndef ID_TEXT_TotalPrice
#define ID_TEXT_TotalPrice		"ID_TEXT_TotalPrice"
#endif  ID_TEXT_TotalPrice
#ifndef ID_TEXT_StallName
#define ID_TEXT_StallName		"ID_TEXT_StallName"
#endif  ID_TEXT_StallName
#ifndef ID_TEXT_PlayerName
#define ID_TEXT_PlayerName		"ID_TEXT_PlayerName"
#endif  ID_TEXT_PlayerName
#ifndef ID_LISTIMG_PetList
#define ID_LISTIMG_PetList		"ID_LISTIMG_PetList"
#endif  ID_LISTIMG_PetList
#ifndef ID_TEXT_Tax
#define ID_TEXT_Tax		"ID_TEXT_Tax"
#endif  ID_TEXT_Tax
#ifndef ID_BUTTON_LeaveWord
#define ID_BUTTON_LeaveWord		"ID_BUTTON_LeaveWord"
#endif  ID_BUTTON_LeaveWord
#ifndef ID_BUTTON_SeekPet
#define ID_BUTTON_SeekPet		"ID_BUTTON_SeekPet"
#endif  ID_BUTTON_SeekPet
#ifndef ID_LISTIMG_Reclaim
#define ID_LISTIMG_Reclaim		"ID_LISTIMG_Reclaim"
#endif  ID_LISTIMG_Reclaim
#ifndef ID_CHECKBOX_Common
#define ID_CHECKBOX_Common		"ID_CHECKBOX_Common"
#endif  ID_CHECKBOX_Common
#ifndef ID_CHECKBOX_Pet
#define ID_CHECKBOX_Pet		"ID_CHECKBOX_Pet"
#endif  ID_CHECKBOX_Pet
#ifndef ID_CHECKBOX_Replace
#define ID_CHECKBOX_Replace		"ID_CHECKBOX_Replace"
#endif  ID_CHECKBOX_Replace
#ifndef ID_LIST_PetName
#define ID_LIST_PetName		"ID_LIST_PetName"
#endif  ID_LIST_PetName
#ifndef ID_LIST_PetSelectWall
#define ID_LIST_PetSelectWall		"ID_LIST_PetSelectWall"
#endif  ID_LIST_PetSelectWall
#ifndef ID_PICTURE_CommonWall
#define ID_PICTURE_CommonWall		"ID_PICTURE_CommonWall"
#endif  ID_PICTURE_CommonWall
#ifndef ID_PICTURE_PetWall
#define ID_PICTURE_PetWall		"ID_PICTURE_PetWall"
#endif  ID_PICTURE_PetWall
#ifndef ID_PICTURE_ReplaceWall
#define ID_PICTURE_ReplaceWall		"ID_PICTURE_ReplaceWall"
#endif  ID_PICTURE_ReplaceWall
#ifndef ID_LIST_ReplaceName
#define ID_LIST_ReplaceName		"ID_LIST_ReplaceName"
#endif  ID_LIST_ReplaceName
#ifndef ID_LIST_ReplacePoint
#define ID_LIST_ReplacePoint		"ID_LIST_ReplacePoint"
#endif  ID_LIST_ReplacePoint
#ifndef ID_LIST_ReplaceLvl
#define ID_LIST_ReplaceLvl		"ID_LIST_ReplaceLvl"
#endif  ID_LIST_ReplaceLvl
#ifndef ID_LIST_ReplaceWall
#define ID_LIST_ReplaceWall		"ID_LIST_ReplaceWall"
#endif  ID_LIST_ReplaceWall
#ifndef ID_TEXT_Expend
#define ID_TEXT_Expend		"ID_TEXT_Expend"
#endif  ID_TEXT_Expend
#ifndef ID_BUTTON_Choose
#define ID_BUTTON_Choose		"ID_BUTTON_Choose"
#endif  ID_BUTTON_Choose

#include "SystemStallage.h"

class CUI_ID_FRAME_PlayerPrivateShop : public CUIBase
{
private:	
	ControlFrame*	m_pID_FRAME_PlayerPrivateShop;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlButton*	m_pID_BUTTON_HELP;
	ControlListImage*	m_pID_LISTIMG_CommonList;
	ControlButton*	m_pID_BUTTON_Buy;
	ControlText*	m_pID_TEXT_Price;
	ControlText*	m_pID_TEXT_TotalPrice;
	ControlText*	m_pID_TEXT_StallName;
	ControlText*	m_pID_TEXT_PlayerName;
	ControlListImage*	m_pID_LISTIMG_PetList;
	ControlText*	m_pID_TEXT_Tax;
	ControlButton*	m_pID_BUTTON_LeaveWord;
	ControlButton*	m_pID_BUTTON_SeekPet;
	ControlListImage*	m_pID_LISTIMG_Reclaim;
	ControlCheckBox*	m_pID_CHECKBOX_Common;
	ControlCheckBox*	m_pID_CHECKBOX_Pet;
	ControlCheckBox*	m_pID_CHECKBOX_Replace;
	ControlList*	m_pID_LIST_PetName;
	ControlList*	m_pID_LIST_PetSelectWall;
	ControlPicture*	m_pID_PICTURE_CommonWall;
	ControlPicture*	m_pID_PICTURE_PetWall;
	ControlPicture*	m_pID_PICTURE_ReplaceWall;
	ControlList*	m_pID_LIST_ReplaceName;
	ControlList*	m_pID_LIST_ReplacePoint;
	ControlList*	m_pID_LIST_ReplaceLvl;
	ControlList*	m_pID_LIST_ReplaceWall;
	ControlText*	m_pID_TEXT_Expend;
	ControlButton*	m_pID_BUTTON_Choose;

	ControlGroup	m_groupCommon;		// 物品
	ControlGroup	m_groupPet;		// 宠物
	ControlGroup	m_groupProxy;		//代工
	ControlTabGroup m_tabFrame;

public:	
	CUI_ID_FRAME_PlayerPrivateShop();
	bool OnFrameRun();
	bool OnFrameRender();
    bool ID_BUTTON_BuyOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_SeekPetOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_LeaveWordOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_CommonListOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_CommonListOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetListOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetListOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ReclaimOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ReclaimOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	void ID_CHECKBOX_CommonOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_PetOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_ReplaceOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	void ID_LIST_PetNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_PetSelectWallOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ReplaceNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ReplacePointOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ReplaceLvlOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ReplaceWallOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_ChooseOnButtonClick( ControlObject* pSender );

	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视

    bool IsEqualToCommonList( ControlObject* pObject );

    // 新的摆摊逻辑相关部分
    void ClearAll();
    void SetTitleName( const char* pTitle );
    void SetPlayerName( const char* pName );
    void SetTaxPercent( int nTax );
    void SetSellGoods( int nIndex, SCharItem* pItem, int nMoneyPrice, int nGoldPrice );
    void SetSellMount( int nIndex, SCharItem* pItem, int nMoneyPrice, int nGoldPrice );
    void SetBuyGoods( int nIndex, int nItemId, int nItemCnt, int nMoneyPrice, int nGoldPrice );
    void SetGoodsSellCnt( int nIndex, int nItemCnt, int nMoneyPrice, int nGoldPrice );
    void SetGoodsBuyCnt( int nIndex, int nItemCnt, int nMoneyPrice, int nGoldPrice );
    void RemoveGoodsSellByIndex( int nIndex );
    void RemoveMountSellByIndex( int nIndex );
    void RemoveGoodsBuyByIndex( int nIndex );

	void RemovePetSellByIndex(int index_);
	void SetSellPet(int index_, SPetItem *pItem_, int moneyPrice_, int goldPrice_);

	bool m_IsOnlineStall;

protected:
    void ResetMembers();
    void ChangePriceUI( DWORD dwPrice, unsigned int uiCount );
    void SetSelectItem( ControlIconDrag::S_ListImg* pItem, bool bIsSell = true, bool bIsMount = false );
    void BuyCurrentItem();

	void SelectItem(int subIndex_, CSystemStallage::EGoodsType goodType_);
	void SelectItem(int totalIndex_);
	void MarkItem(int subIndex_, CSystemStallage::EGoodsType goodType_);	//在UI界面上设置选中标志
	void UnmarkItem(int subIndex_, CSystemStallage::EGoodsType goodType_);	//在UI界面上取消选中标志
	void ClearSelectedItemInfo(int subIndex_, CSystemStallage::EGoodsType goodType_);
	void SetSelectedItemInfo(int subIndex_, CSystemStallage::EGoodsType goodType_);

private:
    ControlIconDrag::S_ListImg*     m_pSelectItem;      // 当前选中框

	int m_selectedItemIndex;	//当前被选择的item的totalIndex

};

extern CUI_ID_FRAME_PlayerPrivateShop s_CUI_ID_FRAME_PlayerPrivateShop;
