/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\PrivateShop.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "GlobalDef.h"
#include "SystemStallage.h"

#ifndef ID_FRAME_PrivateShop
#define ID_FRAME_PrivateShop		"ID_FRAME_PrivateShop"
#endif  ID_FRAME_PrivateShop
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_LISTIMG_CommonList
#define ID_LISTIMG_CommonList		"ID_LISTIMG_CommonList"
#endif  ID_LISTIMG_CommonList
#ifndef ID_BUTTON_Record
#define ID_BUTTON_Record		"ID_BUTTON_Record"
#endif  ID_BUTTON_Record
#ifndef ID_EDIT_StallName
#define ID_EDIT_StallName		"ID_EDIT_StallName"
#endif  ID_EDIT_StallName
#ifndef ID_TEXT_Jin
#define ID_TEXT_Jin		"ID_TEXT_Jin"
#endif  ID_TEXT_Jin
#ifndef ID_TEXT_TotalPrice
#define ID_TEXT_TotalPrice		"ID_TEXT_TotalPrice"
#endif  ID_TEXT_TotalPrice
#ifndef ID_LISTIMG_PetList
#define ID_LISTIMG_PetList		"ID_LISTIMG_PetList"
#endif  ID_LISTIMG_PetList
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_SetPrice
#define ID_BUTTON_SetPrice		"ID_BUTTON_SetPrice"
#endif  ID_BUTTON_SetPrice
#ifndef ID_BUTTON_SeekPet
#define ID_BUTTON_SeekPet		"ID_BUTTON_SeekPet"
#endif  ID_BUTTON_SeekPet
#ifndef ID_TEXT_PlayerName
#define ID_TEXT_PlayerName		"ID_TEXT_PlayerName"
#endif  ID_TEXT_PlayerName
#ifndef ID_TEXT_Tax
#define ID_TEXT_Tax		"ID_TEXT_Tax"
#endif  ID_TEXT_Tax
#ifndef ID_LISTIMG_Reclaim
#define ID_LISTIMG_Reclaim		"ID_LISTIMG_Reclaim"
#endif  ID_LISTIMG_Reclaim
#ifndef ID_TEXT_StallName
#define ID_TEXT_StallName		"ID_TEXT_StallName"
#endif  ID_TEXT_StallName
#ifndef ID_BUTTON_Rename
#define ID_BUTTON_Rename		"ID_BUTTON_Rename"
#endif  ID_BUTTON_Rename
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
#ifndef ID_COMBOBOX_ReplaceLvlChoose
#define ID_COMBOBOX_ReplaceLvlChoose		"ID_COMBOBOX_ReplaceLvlChoose"
#endif  ID_COMBOBOX_ReplaceLvlChoose
#ifndef ID_TEXT_Expend
#define ID_TEXT_Expend		"ID_TEXT_Expend"
#endif  ID_TEXT_Expend
#ifndef ID_BUTTON_Update
#define ID_BUTTON_Update		"ID_BUTTON_Update"
#endif  ID_BUTTON_Update




class CUI_ID_FRAME_PrivateShop : public CUIBase
{
private:	
	ControlFrame*	m_pID_FRAME_PrivateShop;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlButton*	m_pID_BUTTON_HELP;
	ControlListImage*	m_pID_LISTIMG_CommonList;
	ControlButton*	m_pID_BUTTON_Record;
	ControlEdit*	m_pID_EDIT_StallName;
	ControlText*	m_pID_TEXT_Jin;
	ControlText*	m_pID_TEXT_TotalPrice;
	ControlListImage*	m_pID_LISTIMG_PetList;
	ControlButton*	m_pID_BUTTON_Ok;
	ControlButton*	m_pID_BUTTON_Cancel;
	ControlButton*	m_pID_BUTTON_SetPrice;
	ControlButton*	m_pID_BUTTON_SeekPet;
	ControlText*	m_pID_TEXT_PlayerName;
	ControlText*	m_pID_TEXT_Tax;
	ControlListImage*	m_pID_LISTIMG_Reclaim;
	ControlText*	m_pID_TEXT_StallName;
	ControlButton*	m_pID_BUTTON_Rename;
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
	ControlComboBox*	m_pID_COMBOBOX_ReplaceLvlChoose;
	ControlText*	m_pID_TEXT_Expend;
	ControlButton*	m_pID_BUTTON_Update;

	 ControlGroup	m_groupCommon;		// 物品
	 ControlGroup	m_groupPet;		// 宠物
	 ControlGroup	m_groupProxy;		//代工
	 ControlTabGroup m_tabFrame;

public:
    CUI_ID_FRAME_PrivateShop();
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_CommonListOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_CommonListOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_CommonListOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	
	bool ID_LISTIMG_PetListOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_PetListOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetListOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

    bool ID_LISTIMG_ReclaimOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
    bool ID_LISTIMG_ReclaimOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_ReclaimOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_RecordOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SetPriceOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SeekPetOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_RenameOnButtonClick( ControlObject* pSender );

	void ID_CHECKBOX_CommonOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_PetOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_ReplaceOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	void ID_LIST_PetNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_PetSelectWallOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ReplaceNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ReplacePointOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ReplaceLvlOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ReplaceWallOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	void ID_COMBOBOX_ReplaceLvlChooseOnComboBoxChange( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_UpdateOnButtonClick( ControlObject* pSender );


public:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视
    virtual void InitializeAtEnterWorld();

    int  PetList_GetNullItem();
    int  CommonList_GetNullItem();
    bool IsEqualToCommonList( ControlObject* pObject );
    ControlIconDrag::S_ListImg* PetList_GetItemByIndex( int index );
    ControlIconDrag::S_ListImg* CommonList_GetItemByIndex( int index );

    bool IsOpening();

    // 新的摆摊逻辑相关部分
    void ClearAll();
    void SetStallStart( bool bStart );
    void SetTitleName( const char* pTitle );
    void SetPlayerName( const char* pName );
    void SetTaxPercent( int nTax );
    void SetSellGoods( int nIndex, SCharItem* pItem, int nMoneyPrice, int nGoldPrice );
    void SetSellMount( int nIndex, SCharItem* pItem, int nMoneyPrice, int nGoldPrice );
    void SetBuyGoods( int nIndex, int nItemId, int nItemCnt, int nMoneyPrice, int nGoldPrice );
    void SetSellGoodsPrice( int nIndex, int nMoneyPrice, int nGoldPrice );
    void SetSellMountPrice( int nIndex, int nMoneyPrice, int nGoldPrice );
    void SetBuyGoodsPrice( int nIndex, int nMoneyPrice, int nGoldPrice );
    void RemoveMountSellByIndex( int nIndex );
    void RemoveGoodsSellByIndex( int nIndex );
    void RemoveGoodsBuyByIndex( int nIndex );
    std::string GetStallageTitleName();

	void RemovePetSellByIndex(int index_);
	void SetSellPet(int index_, SPetItem *pItem_, int moneyPrice_, int goldPrice_);
	void SetSellPetPrice(int nIndex, int nMoneyPrice, int nGoldPrice);

	int GetPetIndex(const SPetItem &pet_);

	//ui operations
	void TogglePage(ControlCheckBox *pPage_);

	ControlFrame *GetFrame(void){return m_pID_FRAME_PrivateShop;}

	bool m_BisOnlineShop;

protected:
	//初始化控件指针
	void ResetControls(void);

protected:
    void ResetMembers();
    void ChangePriceUI( DWORD dwPrice, unsigned int uiCount );
    void SetSelectItem( ControlIconDrag::S_ListImg* pItem, bool bIsSell = true, bool bIsMount = false );
    void SetCurrentItemPrice();
    static void OnVisibleChange( ControlObject* pUIObject );

	void TogglePageCommon();

public:
	void AddPetToSell(int srcIndex_);
	//void RefreshCurrentPageInfo(void);
	ControlCheckBox *GetCurrentPage(void);
	void SelectItem(int subIndex_, CSystemStallage::EGoodsType goodType_);
	void SelectItem(int totalIndex_);
	void MarkItem(int subIndex_, CSystemStallage::EGoodsType goodType_);	//在UI界面上设置选中标志
	void UnmarkItem(int subIndex_, CSystemStallage::EGoodsType goodType_);	//在UI界面上取消选中标志
	void ClearSelectedItemInfo(int subIndex_, CSystemStallage::EGoodsType goodType_);
	void SetSelectedItemInfo(int subIndex_, CSystemStallage::EGoodsType goodType_);

private:
    ControlIconDrag::S_ListImg*     m_pSelectItem;              // 当前选中框

	int m_selectedItemIndex;	//当前被选择的item的totalIndex
};

extern CUI_ID_FRAME_PrivateShop s_CUI_ID_FRAME_PrivateShop;
