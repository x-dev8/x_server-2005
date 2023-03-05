/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\PrivateShop.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PrivateShop.h"
#include "SystemStallage.h"
#include "Pack.h"
#include "Pet.h"
#include "PlayerRole.h"
#include "MeUi/ExpressionManager.h"
#include "Common.h"
#include "Create.h"
#include "UIMgr.h"
#include "TradeRecord.h"
#include "ui\SelectPet.h"
#include "ui\ReplaceList.h"
#include "Helper\PetHelper.h"
#include "ui\PutInItem.h"
#include "SeekPet.h"
#include "ui/SeeSuAnimal.h"
#include "ScreenInfoManager.h"

extern HWND g_hWnd;

CUI_ID_FRAME_PrivateShop s_CUI_ID_FRAME_PrivateShop;

MAP_FRAME_RUN( s_CUI_ID_FRAME_PrivateShop, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PrivateShop, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_LISTIMG_CommonListOnIconDragOn )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_LISTIMG_CommonListOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_LISTIMG_CommonListOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_BUTTON_RecordOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_LISTIMG_PetListOnIconDragOn )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_LISTIMG_PetListOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_LISTIMG_PetListOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_BUTTON_SetPriceOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_BUTTON_SeekPetOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_BUTTON_RenameOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_LISTIMG_ReclaimOnIconDragOn )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_LISTIMG_ReclaimOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_LISTIMG_ReclaimOnIconRButtonUp )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_CHECKBOX_CommonOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_CHECKBOX_PetOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_CHECKBOX_ReplaceOnCheckBoxCheck )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_LIST_PetNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_LIST_PetSelectWallOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_LIST_ReplaceNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_LIST_ReplacePointOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_LIST_ReplaceLvlOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_LIST_ReplaceWallOnListSelectChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_COMBOBOX_ReplaceLvlChooseOnComboBoxChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_BUTTON_UpdateOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PrivateShop, ID_BUTTON_CLOSEOnButtonClick )

CUI_ID_FRAME_PrivateShop::CUI_ID_FRAME_PrivateShop()
{
    //ResetMembers();
	ResetControls();
	m_BisOnlineShop = false;
    m_pSelectItem = NULL;
}

// Button
bool CUI_ID_FRAME_PrivateShop::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PrivateShop )
		return false;

	SetVisable(false);

	return true;
}

void CUI_ID_FRAME_PrivateShop::ResetMembers()
{
    m_pID_FRAME_PrivateShop = NULL;
	m_pID_LISTIMG_CommonList = NULL;
	m_pID_BUTTON_Record = NULL;
	m_pID_TEXT_StallName = NULL;
	m_pID_TEXT_Jin = NULL;
	m_pID_TEXT_TotalPrice = NULL;
	m_pID_LISTIMG_PetList = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_SetPrice = NULL;
	m_pID_BUTTON_SeekPet = NULL;
	m_pID_TEXT_PlayerName = NULL;
	m_pID_TEXT_Tax = NULL;
	m_pID_LISTIMG_Reclaim = NULL;
    m_pID_BUTTON_Rename = NULL;
}

bool CUI_ID_FRAME_PrivateShop::OnFrameRun()
{
	return true;
}

bool CUI_ID_FRAME_PrivateShop::OnFrameRender()
{
	return true;
}

// ListImg / ListEx
bool CUI_ID_FRAME_PrivateShop::ID_LISTIMG_CommonListOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !IsUILoad() )
		return false;

    if( !pItemDrag || !pItemSrc )
        return false;

    // 物品出售栏内移动
    if( pSender == pMe && ( !pItemDrag->IsNull() || !pItemSrc->IsNull() ) )
    {
        int nDstIndex = m_pID_LISTIMG_CommonList->GetItemIndex( pItemSrc );
        int nSrcIndex = m_pID_LISTIMG_CommonList->GetItemIndex( pItemDrag );
        if( nDstIndex < 0 || nDstIndex >= m_pID_LISTIMG_CommonList->GetItemCnt() )
            return false;
        if( nSrcIndex < 0 || nSrcIndex >= m_pID_LISTIMG_CommonList->GetItemCnt() )
            return false;

        CSystemStallage::Instance()->MoveGoodsInSellSlots( nSrcIndex, nDstIndex );
        return false;
    }

    // 源地址空或目标地址满均返回
    if ( pItemDrag->IsNull() || !pItemSrc->IsNull() )
        return false;

    // 摊位道具栏索引
    int nDstIndex = m_pID_LISTIMG_CommonList->GetItemIndex( pItemSrc );
    if( nDstIndex < 0 || nDstIndex >= m_pID_LISTIMG_CommonList->GetItemCnt() )
        return false;

    // 背包中位置索引
    ControlListImage* pListImg = ( ControlListImage* )pSender;
    int nSrcIndex = pListImg->GetItemIndex( pItemDrag );
    if( nSrcIndex < 0 || nSrcIndex >= pListImg->GetItemCnt() )
        return false;

    // 物品类型只能是 普通道具 和 材料
    int nBagType( -1 );
    if( s_CUI_ID_FRAME_PACK.IsListImageByBagType( BT_NormalItemBag, pSender ) )
    {
        nBagType = BT_NormalItemBag;
    }
    else if( s_CUI_ID_FRAME_PACK.IsListImageByBagType( BT_MaterialBag, pSender ) )
    {
        nBagType = BT_MaterialBag;
    }
    else
    {
        return false;
    }

    CSystemStallage::Instance()->MoveFromPackToGoodsSell( nDstIndex, nSrcIndex, nBagType );

	return false;
}

bool CUI_ID_FRAME_PrivateShop::ID_LISTIMG_CommonListOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !IsUILoad() )
		return false;

    if( !pItem )
        return false;

    //SetSelectItem( pItem, true, false );
	SelectItem(((ControlListImage *)pSender)->GetItemIndex(pItem), CSystemStallage::E_Goods_common);

	return false;
}

bool CUI_ID_FRAME_PrivateShop::ID_LISTIMG_CommonListOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    // 出售栏内移除物品
	if ( !IsUILoad() )
		return false;

    if( !pItem || pItem->IsNull() )
        return false;

    int nIndex = m_pID_LISTIMG_CommonList->GetItemIndex( pItem );
    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_CommonList->GetItemCnt() )
        return false;

    CSystemStallage::Instance()->RemoveGoodsSell( nIndex );
	return false;
}

void bubble(int *a,int n) //冒泡排序 
{ 
	int i,j,temp; 

	for(i=0;i<n-1;i++) 
	{
		for(j=i+1;j<n;j++)  
		{
			if(a[i]>a[j])
			{ 
				temp=a[i]; 
				a[i]=a[j]; 
				a[j]=temp; 
			}
		}
	}
} 

void CUI_ID_FRAME_PrivateShop::AddPetToSell(int srcIndex_)
{
	if(NULL == m_pID_LIST_PetSelectWall)
		return;

	SPetItem &pet = thePlayerRole.GetPetByIndex(srcIndex_);
	if(!IsValidPet(pet))
		return;

	//下边这些代码只是为了能找到正确的空位，防止选择副将时该摊位已经有数据 lrt
	int ncount = m_pID_LIST_PetSelectWall->GetListItemCnt();
	int destIndex = ncount;
	int petIndex[10] = {0};

	for (int i = 0; i < ncount; i++ )
	{
		ControlList::S_List *pItem = m_pID_LIST_PetSelectWall->GetListItem(i);
		if (pItem)
		{
			petIndex[i] = pItem->m_nID;
		}
	}

	bubble(petIndex, ncount);

	for (int i = 0; i < ncount; i++)
	{
		if (petIndex[i] != i)
		{
			destIndex = i;
			break;
		}
	}

	CSystemStallage::Instance()->AddPetToSell(pet, srcIndex_, /*m_pID_LIST_PetSelectWall->GetListItemCnt()*/destIndex);

}

// ListImg / ListEx
bool CUI_ID_FRAME_PrivateShop::ID_LISTIMG_PetListOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	return true; //先不让交易 lrt
	if ( !IsUILoad() )
		return false;

    if( !pItemDrag || !pItemSrc )
        return false;

	ItemDefine::SItemCommon *pItem = NULL;
	pItem = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->Id() );
	if( !pItem )
		return false;

	// 是否可买卖
	if( !pItem->bIsCanTrade )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed, theXmlString.GetString( eClient_AddInfo_2slk_31 ) );
		return false;
	}

    // 宠物栏内移动
    if( pSender == pMe && ( !pItemDrag->IsNull() || !pItemSrc->IsNull() ) )
    {
        int nDstIndex = m_pID_LISTIMG_PetList->GetItemIndex( pItemSrc );
        int nSrcIndex = m_pID_LISTIMG_PetList->GetItemIndex( pItemDrag );
        if( nDstIndex < 0 || nDstIndex >= m_pID_LISTIMG_PetList->GetItemCnt() )
            return false;
        if( nSrcIndex < 0 || nSrcIndex >= m_pID_LISTIMG_PetList->GetItemCnt() )
            return false;

        CSystemStallage::Instance()->MoveMountInSellSlots( nSrcIndex, nDstIndex );
        return false;
    }

    // 源地址空或目标地址满均返回
    if ( pItemDrag->IsNull() || !pItemSrc->IsNull() )
        return false;

    // 摊位道具栏索引
    int nDstIndex = m_pID_LISTIMG_PetList->GetItemIndex( pItemSrc );
    if( nDstIndex < 0 || nDstIndex >= m_pID_LISTIMG_PetList->GetItemCnt() )
        return false;

    // 背包中位置索引
    ControlListImage* pListImg = ( ControlListImage* )pSender;
    int nSrcIndex = pListImg->GetItemIndex( pItemDrag );
    if( nSrcIndex < 0 || nSrcIndex >= pListImg->GetItemCnt() )
        return false;

    // 背包类型必须为坐骑
    if( !s_CUI_ID_FRAME_Pet.IsEqualToLISTIMG_PetIcon( pSender ) )
        return false;

    CSystemStallage::Instance()->MoveMountToSell( nDstIndex, nSrcIndex );

	return false;
}

bool CUI_ID_FRAME_PrivateShop::ID_LISTIMG_PetListOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !IsUILoad() )
		return false;

    if( !pItem )
        return false;

    //SetSelectItem( pItem, true, true );
	SelectItem(((ControlListImage *)pSender)->GetItemIndex(pItem), CSystemStallage::E_Goods_mount);

	return false;
}

bool CUI_ID_FRAME_PrivateShop::ID_LISTIMG_PetListOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    // 坐骑栏内移除物品
    if ( !IsUILoad() )
        return false;

    if( !pItem || pItem->IsNull() )
        return false;

    int nIndex = m_pID_LISTIMG_PetList->GetItemIndex( pItem );
    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_PetList->GetItemCnt() )
        return false;

    CSystemStallage::Instance()->RemoveMountSell( nIndex );

	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_PrivateShop::ID_LISTIMG_ReclaimOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
                                                              ControlIconDrag::S_ListImg* pItemDrag,
                                                              ControlIconDrag::S_ListImg* pItemSrc )
{
    if ( !IsUILoad() )
        return false;

    if( !pItemDrag || !pItemSrc )
        return false;

    // 收购栏内移动
    if( pSender == pMe && ( !pItemDrag->IsNull() || !pItemSrc->IsNull() ) )
    {
        int nDstIndex = m_pID_LISTIMG_Reclaim->GetItemIndex( pItemSrc );
        int nSrcIndex = m_pID_LISTIMG_Reclaim->GetItemIndex( pItemDrag );
        if( nDstIndex < 0 || nDstIndex >= m_pID_LISTIMG_Reclaim->GetItemCnt() )
            return false;
        if( nSrcIndex < 0 || nSrcIndex >= m_pID_LISTIMG_Reclaim->GetItemCnt() )
            return false;

        CSystemStallage::Instance()->MoveGoodsInBuySlots( nSrcIndex, nDstIndex );
        return false;
    }

    // 源地址空或目标地址满均返回
    if ( pItemDrag->IsNull() || !pItemSrc->IsNull() )
        return false;

    // 摊位道具栏索引
    int nDstIndex = m_pID_LISTIMG_Reclaim->GetItemIndex( pItemSrc );
    if( nDstIndex < 0 || nDstIndex >= m_pID_LISTIMG_Reclaim->GetItemCnt() )
        return false;

    // 背包中位置索引
    ControlListImage* pListImg = ( ControlListImage* )pSender;
    int nSrcIndex = pListImg->GetItemIndex( pItemDrag );
    if( nSrcIndex < 0 || nSrcIndex >= pListImg->GetItemCnt() )
        return false;

    // 物品类型只能是 普通道具 和 材料
    int nBagType( -1 );
    if( s_CUI_ID_FRAME_PACK.IsListImageByBagType( BT_NormalItemBag, pSender ) )
    {
        nBagType = BT_NormalItemBag;
    }
    else if( s_CUI_ID_FRAME_PACK.IsListImageByBagType( BT_MaterialBag, pSender ) )
    {
        nBagType = BT_MaterialBag;
    }
    else
    {
        return false;
    }

    CSystemStallage::Instance()->MoveFromPackToGoodsBuy( nDstIndex, nSrcIndex, nBagType );

    return false;
}

bool CUI_ID_FRAME_PrivateShop::ID_LISTIMG_ReclaimOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if ( !IsUILoad() )
        return false;

    if( !pItem )
        return false;

    //SetSelectItem( pItem, false, false );
	SelectItem(((ControlListImage *)pSender)->GetItemIndex(pItem), CSystemStallage::E_Goods_buy);

    return false;
}

bool CUI_ID_FRAME_PrivateShop::ID_LISTIMG_ReclaimOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    // 收购栏内移除物品
    if ( !IsUILoad() )
        return false;

    if( !pItem || pItem->IsNull() )
        return false;

    int nIndex = m_pID_LISTIMG_Reclaim->GetItemIndex( pItem );
    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_Reclaim->GetItemCnt() )
        return false;

    CSystemStallage::Instance()->RemoveGoodsBuy( nIndex );

    return false;
}

// Button
bool CUI_ID_FRAME_PrivateShop::ID_BUTTON_RecordOnButtonClick( ControlObject* pSender )
{
    if ( !IsUILoad() )
        return false;

    s_CUI_ID_FRAME_TradeRecord.SetVisable( true );
    return true;
}

// Button
bool CUI_ID_FRAME_PrivateShop::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	if ( !IsUILoad() )
		return false;

    CSystemStallage::Instance()->StartStallRequest();
	return true;
}

// Button
bool CUI_ID_FRAME_PrivateShop::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !IsUILoad() )
		return false;
    
    CSystemStallage::Instance()->CloseStallRequest();
	SetVisable(false);
	return true;
}

// Button
bool CUI_ID_FRAME_PrivateShop::ID_BUTTON_SetPriceOnButtonClick( ControlObject* pSender )
{
	if ( !IsUILoad() )
		return false;

    SetCurrentItemPrice();
	return true;
}

// Button
bool CUI_ID_FRAME_PrivateShop::ID_BUTTON_SeekPetOnButtonClick( ControlObject* pSender )
{
	if ( !IsUILoad() )
		return false;

/*
    // 查看坐骑
    if( m_pSelectItem )
    {
        int nIndex = m_pID_LISTIMG_PetList->GetItemIndex( m_pSelectItem );
        if( nIndex < 0 || nIndex >= m_pID_LISTIMG_PetList->GetItemCnt() )
            return false;

        if( !m_pSelectItem->m_pkIconInfo )
            return false;

        CSystemStallage::Instance()->SeekSelfMountByIndex( nIndex, m_pSelectItem->m_pkIconInfo->GetOnlyId() );

    }

*/

	if (m_selectedItemIndex >= 18 && m_selectedItemIndex < StallDefine::MaxSellCount)
	{
		ControlIconDrag::S_ListImg* pItem1 = NULL;
		if (m_pID_LISTIMG_PetList)
			pItem1 = m_pID_LISTIMG_PetList->GetCurSelItem();

		if (pItem1 != NULL)
		{
			SMountItem* pMount = thePlayerRole.GetMountByGUID( pItem1->m_pkIconInfo->GetOnlyId() );
			if( !pMount )
				return false;

			s_CUI_ID_FRAME_SeekPet.SetVisable( true );
			s_CUI_ID_FRAME_SeekPet.SetMount( *pMount );
		}

		return true;
	}

	if(NULL == m_pID_CHECKBOX_Pet || !m_pID_CHECKBOX_Pet->IsChecked())
		return false;

	ControlList::S_List *pItem = NULL;
	if(m_pID_LIST_PetSelectWall)
		pItem = m_pID_LIST_PetSelectWall->GetCurSelItem();

	if(pItem != NULL)
	{
		SPetItem *pet = (SPetItem *)pItem->m_pData;
		if(pet != NULL)
		{
			s_CUI_ID_FRAME_SeeSuAnimal.SetVisable(true);
			s_CUI_ID_FRAME_SeeSuAnimal.SetPetItem(*pet);
		}
	}

	/*ControlIconDrag::S_ListImg* pItem1 = NULL;
	if (m_pID_LISTIMG_PetList)
		pItem1 = m_pID_LISTIMG_PetList->GetCurSelItem();

	if (pItem1 != NULL)
	{
		int nSrcIndex = m_pID_LISTIMG_PetList->GetItemIndex( pItem1 );
		SMountItem* pMount = &thePlayerRole.GetMountByIndex( nSrcIndex );
		if( !pMount )
			return false;

		s_CUI_ID_FRAME_SeekPet.SetVisable( true );
		s_CUI_ID_FRAME_SeekPet.SetMount( *pMount );
	}*/

	return true;
}

// CheckBox
void CUI_ID_FRAME_PrivateShop::ID_CHECKBOX_CommonOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	//m_tabFrame.TogglePage((ControlCheckBox *)pSender);

	TogglePage((ControlCheckBox *)pSender);
}
// CheckBox
void CUI_ID_FRAME_PrivateShop::ID_CHECKBOX_PetOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	//m_tabFrame.TogglePage((ControlCheckBox *)pSender);

	TogglePage((ControlCheckBox *)pSender);
}
// CheckBox
void CUI_ID_FRAME_PrivateShop::ID_CHECKBOX_ReplaceOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	//m_tabFrame.TogglePage((ControlCheckBox *)pSender);

	TogglePage((ControlCheckBox *)pSender);
}

// Button
bool CUI_ID_FRAME_PrivateShop::ID_BUTTON_RenameOnButtonClick( ControlObject* pSender )
{
    if ( !IsUILoad() )
        return false;

    CSystemStallage::Instance()->ChangeStallName();
    return true;
}

// List
void CUI_ID_FRAME_PrivateShop::ID_LIST_PetNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_PrivateShop::ID_LIST_PetSelectWallOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(NULL == pItem)
		return;

	SelectItem(/*((ControlList *)pSender)->GetCurSelIndex()*/pItem->m_nID, CSystemStallage::E_Goods_pet);
}
// List
void CUI_ID_FRAME_PrivateShop::ID_LIST_ReplaceNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_PrivateShop::ID_LIST_ReplacePointOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_PrivateShop::ID_LIST_ReplaceLvlOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_PrivateShop::ID_LIST_ReplaceWallOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(NULL == pItem)
		return;

	SelectItem(((ControlList *)pSender)->GetCurSelIndex(), CSystemStallage::E_Goods_replace);
}

// ComboBox
void CUI_ID_FRAME_PrivateShop::ID_COMBOBOX_ReplaceLvlChooseOnComboBoxChange( ControlObject* pSender, const char* szData )
{
}
// Button
bool CUI_ID_FRAME_PrivateShop::ID_BUTTON_UpdateOnButtonClick( ControlObject* pSender )
{
	return true;
}

// 装载UI
bool CUI_ID_FRAME_PrivateShop::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PrivateShop.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\PrivateShop.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_PrivateShop::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PrivateShop, s_CUI_ID_FRAME_PrivateShopOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PrivateShop, s_CUI_ID_FRAME_PrivateShopOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_PrivateShop, ID_LISTIMG_CommonList, s_CUI_ID_FRAME_PrivateShopID_LISTIMG_CommonListOnIconDragOn );
	theUiManager.OnIconButtonClick( ID_FRAME_PrivateShop, ID_LISTIMG_CommonList, s_CUI_ID_FRAME_PrivateShopID_LISTIMG_CommonListOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PrivateShop, ID_LISTIMG_CommonList, s_CUI_ID_FRAME_PrivateShopID_LISTIMG_CommonListOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_PrivateShop, ID_BUTTON_Record, s_CUI_ID_FRAME_PrivateShopID_BUTTON_RecordOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_PrivateShop, ID_LISTIMG_PetList, s_CUI_ID_FRAME_PrivateShopID_LISTIMG_PetListOnIconDragOn );
	theUiManager.OnIconButtonClick( ID_FRAME_PrivateShop, ID_LISTIMG_PetList, s_CUI_ID_FRAME_PrivateShopID_LISTIMG_PetListOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PrivateShop, ID_LISTIMG_PetList, s_CUI_ID_FRAME_PrivateShopID_LISTIMG_PetListOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_PrivateShop, ID_BUTTON_Ok, s_CUI_ID_FRAME_PrivateShopID_BUTTON_OkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PrivateShop, ID_BUTTON_Cancel, s_CUI_ID_FRAME_PrivateShopID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PrivateShop, ID_BUTTON_SetPrice, s_CUI_ID_FRAME_PrivateShopID_BUTTON_SetPriceOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PrivateShop, ID_BUTTON_SeekPet, s_CUI_ID_FRAME_PrivateShopID_BUTTON_SeekPetOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_PrivateShop, ID_BUTTON_Rename, s_CUI_ID_FRAME_PrivateShopID_BUTTON_RenameOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_PrivateShop, ID_LISTIMG_Reclaim, s_CUI_ID_FRAME_PrivateShopID_LISTIMG_ReclaimOnIconDragOn );
	theUiManager.OnIconButtonClick( ID_FRAME_PrivateShop, ID_LISTIMG_Reclaim, s_CUI_ID_FRAME_PrivateShopID_LISTIMG_ReclaimOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PrivateShop, ID_LISTIMG_Reclaim, s_CUI_ID_FRAME_PrivateShopID_LISTIMG_ReclaimOnIconRButtonUp );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PrivateShop, ID_CHECKBOX_Common, s_CUI_ID_FRAME_PrivateShopID_CHECKBOX_CommonOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PrivateShop, ID_CHECKBOX_Pet, s_CUI_ID_FRAME_PrivateShopID_CHECKBOX_PetOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PrivateShop, ID_CHECKBOX_Replace, s_CUI_ID_FRAME_PrivateShopID_CHECKBOX_ReplaceOnCheckBoxCheck );
	theUiManager.OnListSelectChange( ID_FRAME_PrivateShop, ID_LIST_PetName, s_CUI_ID_FRAME_PrivateShopID_LIST_PetNameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_PrivateShop, ID_LIST_PetSelectWall, s_CUI_ID_FRAME_PrivateShopID_LIST_PetSelectWallOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_PrivateShop, ID_LIST_ReplaceName, s_CUI_ID_FRAME_PrivateShopID_LIST_ReplaceNameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_PrivateShop, ID_LIST_ReplacePoint, s_CUI_ID_FRAME_PrivateShopID_LIST_ReplacePointOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_PrivateShop, ID_LIST_ReplaceLvl, s_CUI_ID_FRAME_PrivateShopID_LIST_ReplaceLvlOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_PrivateShop, ID_LIST_ReplaceWall, s_CUI_ID_FRAME_PrivateShopID_LIST_ReplaceWallOnListSelectChange );
	theUiManager.OnComboBoxChange( ID_FRAME_PrivateShop, ID_COMBOBOX_ReplaceLvlChoose, s_CUI_ID_FRAME_PrivateShopID_COMBOBOX_ReplaceLvlChooseOnComboBoxChange );
	theUiManager.OnButtonClick( ID_FRAME_PrivateShop, ID_BUTTON_Update, s_CUI_ID_FRAME_PrivateShopID_BUTTON_UpdateOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PrivateShop, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_PrivateShopID_BUTTON_CLOSEOnButtonClick );

// 	m_pID_FRAME_PrivateShop = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PrivateShop );
// 	m_pID_LISTIMG_CommonList = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_LISTIMG_CommonList );
// 	m_pID_BUTTON_Record = (ControlButton*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_BUTTON_Record );
// 	m_pID_TEXT_StallName = (ControlText*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_TEXT_StallName );
// 	m_pID_TEXT_Jin = (ControlText*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_TEXT_Jin );
// 	m_pID_TEXT_TotalPrice = (ControlText*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_TEXT_TotalPrice );
// 	m_pID_LISTIMG_PetList = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_LISTIMG_PetList );
// 	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_BUTTON_Ok );
// 	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_BUTTON_Cancel );
// 	m_pID_BUTTON_SetPrice = (ControlButton*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_BUTTON_SetPrice );
// 	m_pID_BUTTON_SeekPet = (ControlButton*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_BUTTON_SeekPet );
// 	m_pID_TEXT_PlayerName = (ControlText*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_TEXT_PlayerName );
// 	m_pID_TEXT_Tax = (ControlText*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_TEXT_Tax );
// 	m_pID_LISTIMG_Reclaim = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_LISTIMG_Reclaim );
//     m_pID_BUTTON_Rename = (ControlButton*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_BUTTON_Rename );
// 
// 	assert( m_pID_FRAME_PrivateShop );
// 	assert( m_pID_LISTIMG_CommonList );
// 	assert( m_pID_BUTTON_Record );
// 	assert( m_pID_TEXT_StallName );
// 	assert( m_pID_TEXT_Jin );
// 	assert( m_pID_TEXT_TotalPrice );
// 	assert( m_pID_LISTIMG_PetList );
// 	assert( m_pID_BUTTON_Ok );
// 	assert( m_pID_BUTTON_Cancel );
// 	assert( m_pID_BUTTON_SetPrice );
// 	assert( m_pID_BUTTON_SeekPet );
// 	assert( m_pID_TEXT_PlayerName );
// 	assert( m_pID_TEXT_Tax );
// 	assert( m_pID_LISTIMG_Reclaim );
//     assert( m_pID_BUTTON_Rename );

	m_pID_FRAME_PrivateShop = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PrivateShop );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_BUTTON_CLOSE );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_BUTTON_HELP );
	m_pID_LISTIMG_CommonList = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_LISTIMG_CommonList );
	m_pID_BUTTON_Record = (ControlButton*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_BUTTON_Record );
	m_pID_EDIT_StallName = (ControlEdit*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_EDIT_StallName );
	m_pID_TEXT_Jin = (ControlText*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_TEXT_Jin );
	m_pID_TEXT_TotalPrice = (ControlText*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_TEXT_TotalPrice );
	m_pID_LISTIMG_PetList = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_LISTIMG_PetList );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_BUTTON_Ok );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_BUTTON_Cancel );
	m_pID_BUTTON_SetPrice = (ControlButton*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_BUTTON_SetPrice );
	m_pID_BUTTON_SeekPet = (ControlButton*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_BUTTON_SeekPet );
	m_pID_TEXT_PlayerName = (ControlText*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_TEXT_PlayerName );
	m_pID_TEXT_Tax = (ControlText*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_TEXT_Tax );
	m_pID_LISTIMG_Reclaim = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_LISTIMG_Reclaim );
	m_pID_TEXT_StallName = (ControlText*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_TEXT_StallName );
	m_pID_BUTTON_Rename = (ControlButton*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_BUTTON_Rename );
	m_pID_CHECKBOX_Common = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_CHECKBOX_Common );
	m_pID_CHECKBOX_Pet = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_CHECKBOX_Pet );
	m_pID_CHECKBOX_Replace = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_CHECKBOX_Replace );
	m_pID_LIST_PetName = (ControlList*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_LIST_PetName );
	m_pID_LIST_PetSelectWall = (ControlList*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_LIST_PetSelectWall );
	m_pID_PICTURE_CommonWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_PICTURE_CommonWall );
	m_pID_PICTURE_PetWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_PICTURE_PetWall );
	m_pID_PICTURE_ReplaceWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_PICTURE_ReplaceWall );
	m_pID_LIST_ReplaceName = (ControlList*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_LIST_ReplaceName );
	m_pID_LIST_ReplacePoint = (ControlList*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_LIST_ReplacePoint );
	m_pID_LIST_ReplaceLvl = (ControlList*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_LIST_ReplaceLvl );
	m_pID_LIST_ReplaceWall = (ControlList*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_LIST_ReplaceWall );
	m_pID_COMBOBOX_ReplaceLvlChoose = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_COMBOBOX_ReplaceLvlChoose );
	m_pID_TEXT_Expend = (ControlText*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_TEXT_Expend );
	m_pID_BUTTON_Update = (ControlButton*)theUiManager.FindControl( ID_FRAME_PrivateShop, ID_BUTTON_Update );
	assert( m_pID_FRAME_PrivateShop );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_LISTIMG_CommonList );
	assert( m_pID_BUTTON_Record );
	assert( m_pID_EDIT_StallName );
	assert( m_pID_TEXT_Jin );
	assert( m_pID_TEXT_TotalPrice );
	assert( m_pID_LISTIMG_PetList );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_SetPrice );
	assert( m_pID_BUTTON_SeekPet );
	assert( m_pID_TEXT_PlayerName );
	assert( m_pID_TEXT_Tax );
	assert( m_pID_LISTIMG_Reclaim );
	assert( m_pID_TEXT_StallName );
	assert( m_pID_BUTTON_Rename );
	assert( m_pID_CHECKBOX_Common );
	assert( m_pID_CHECKBOX_Pet );
	assert( m_pID_CHECKBOX_Replace );
	assert( m_pID_LIST_PetName );
	assert( m_pID_LIST_PetSelectWall );
	assert( m_pID_PICTURE_CommonWall );
	assert( m_pID_PICTURE_PetWall );
	assert( m_pID_PICTURE_ReplaceWall );
	assert( m_pID_LIST_ReplaceName );
	assert( m_pID_LIST_ReplacePoint );
	assert( m_pID_LIST_ReplaceLvl );
	assert( m_pID_LIST_ReplaceWall );
	assert( m_pID_COMBOBOX_ReplaceLvlChoose );
	assert( m_pID_TEXT_Expend );
	assert( m_pID_BUTTON_Update );

    m_pID_FRAME_PrivateShop->SetOnVisibleChangedFun( OnVisibleChange );

	m_tabFrame.Clear();
	m_groupCommon.Clear();
	m_groupPet.Clear();
	m_groupProxy.Clear();
	//设置分组控件
	if(m_pID_CHECKBOX_Common)
	{
		m_groupCommon.AddControl(m_pID_LISTIMG_CommonList);
		m_groupCommon.AddControl(m_pID_PICTURE_CommonWall);
		m_groupCommon.AddControl(m_pID_LISTIMG_Reclaim);

		m_tabFrame.AddPage(m_pID_CHECKBOX_Common, &m_groupCommon);
	}

	if(m_pID_CHECKBOX_Pet)
	{
		m_groupPet.AddControl(m_pID_PICTURE_PetWall);
		m_groupPet.AddControl(m_pID_LISTIMG_PetList);
		m_groupPet.AddControl(m_pID_LIST_PetName);
		m_groupPet.AddControl(m_pID_LIST_PetSelectWall);
		m_groupPet.AddControl(m_pID_BUTTON_SeekPet);

		m_tabFrame.AddPage(m_pID_CHECKBOX_Pet, &m_groupPet);
	}

	if(m_pID_CHECKBOX_Replace)
	{
		m_groupProxy.AddControl(m_pID_PICTURE_ReplaceWall);
		m_groupProxy.AddControl(m_pID_LIST_ReplaceName);
		m_groupProxy.AddControl(m_pID_LIST_ReplacePoint);
		m_groupProxy.AddControl(m_pID_LIST_ReplaceLvl);
		m_groupProxy.AddControl(m_pID_LIST_ReplaceWall);
		m_groupProxy.AddControl(m_pID_COMBOBOX_ReplaceLvlChoose);
		m_groupProxy.AddControl(m_pID_TEXT_Expend);
		m_groupProxy.AddControl(m_pID_BUTTON_Update);

		m_tabFrame.AddPage(m_pID_CHECKBOX_Replace, &m_groupProxy);
	}

	m_tabFrame.TogglePage(m_pID_CHECKBOX_Common);


	SetVisable( false );
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_PrivateShop::_UnLoadUI()
{
    m_pSelectItem = NULL;
	//ResetMembers();

	ResetControls();
	return theUiManager.RemoveFrame( "Data\\UI\\PrivateShop.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_PrivateShop::_IsVisable()
{
	if ( !m_pID_FRAME_PrivateShop )
		return false;
	return m_pID_FRAME_PrivateShop->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_PrivateShop::_SetVisable( const bool bVisable )
{
	if ( !IsUILoad() )
		return;

	m_pID_FRAME_PrivateShop->SetVisable( bVisable );

    if( bVisable )
    {
        s_CUI_ID_FRAME_PACK.SetVisable( true );
        ResetWindowPosition( m_pID_FRAME_PrivateShop, s_CUI_ID_FRAME_PACK.GetFrame() );

		if(m_pID_CHECKBOX_Common)
		{
			m_tabFrame.TogglePage(m_pID_CHECKBOX_Common);
		}
    }
	else
	{
		if(s_CUI_ID_FRAME_SelectPet.IsVisable())
		{
			s_CUI_ID_FRAME_SelectPet.SetVisable(false);
		}

		if(s_CUI_ID_FRAME_PutInItem.IsVisable())
		{
			s_CUI_ID_FRAME_PutInItem.SetVisable(false);
		}

		if(s_CUI_ID_FRAME_ReplaceList.IsVisable())
		{
			s_CUI_ID_FRAME_ReplaceList.SetVisable(false);
		}

		if(s_CUI_ID_FRAME_SeekPet.IsVisable())
		{
			s_CUI_ID_FRAME_SeekPet.SetVisable(false);
		}
	}
}

void CUI_ID_FRAME_PrivateShop::OnVisibleChange( ControlObject* pUIObject )
{
    CSystemStallage::Instance()->RefreshCharItemsInStallage();
}

void CUI_ID_FRAME_PrivateShop::InitializeAtEnterWorld()
{
    CSystemStallage::Instance()->TellSelfEnterWorld();
}

void CUI_ID_FRAME_PrivateShop::ChangePriceUI( DWORD dwPrice, unsigned int uiCount )
{
    //计算单价
    std::string text = "";
    thePlayerRole.GetGSCStringFromMoney( dwPrice, text );
    *m_pID_TEXT_Jin = text;

    //计算总价
    DWORD dwTotalPrice = dwPrice * uiCount;
    std::string strTotalPriceText = "";
    thePlayerRole.GetGSCStringFromMoney( dwTotalPrice, strTotalPriceText );
    ExpressionManager::GetInstance().AddExpressionAni( strTotalPriceText );
    *m_pID_TEXT_TotalPrice = strTotalPriceText;
}

int CUI_ID_FRAME_PrivateShop::PetList_GetNullItem()
{
    if( !IsUILoad() )
        return -1;

    return m_pID_LISTIMG_PetList->GetNullItem();
}

ControlIconDrag::S_ListImg* CUI_ID_FRAME_PrivateShop::PetList_GetItemByIndex( int index )
{
    if( !IsUILoad() || index < 0 )
        return NULL;

    return m_pID_LISTIMG_PetList->GetItemByIndex( index );
}

int CUI_ID_FRAME_PrivateShop::CommonList_GetNullItem()
{
    if( !IsUILoad() )
        return -1;

    return m_pID_LISTIMG_CommonList->GetNullItem();
}

ControlIconDrag::S_ListImg* CUI_ID_FRAME_PrivateShop::CommonList_GetItemByIndex( int index )
{
    if( !IsUILoad() || index < 0 )
        return NULL;

    return m_pID_LISTIMG_CommonList->GetItemByIndex( index );
}

bool CUI_ID_FRAME_PrivateShop::IsEqualToCommonList( ControlObject* pObject )
{
    if( !IsUILoad() || !pObject )
        return false;

    return ( m_pID_LISTIMG_CommonList == ( ControlListImage* )pObject );
}

bool CUI_ID_FRAME_PrivateShop::IsOpening()
{
    return CSystemStallage::Instance()->IsSelfInStalling();
}

//--------------------新的摆摊逻辑相关部分--------------------------
void CUI_ID_FRAME_PrivateShop::ClearAll()
{
    if( !IsUILoad() )
        return;

    m_pID_TEXT_StallName->SetText( "" );
    m_pID_TEXT_PlayerName->SetText( "" );
    m_pID_TEXT_Tax->SetText( "" );

	if(m_pID_LISTIMG_CommonList)
		m_pID_LISTIMG_CommonList->Clear();
	if(m_pID_LISTIMG_Reclaim)
		m_pID_LISTIMG_Reclaim->Clear();

	if(m_pID_LIST_PetSelectWall)
		m_pID_LIST_PetSelectWall->Clear();
	if(m_pID_LIST_PetName)
		m_pID_LIST_PetName->Clear();
	if(m_pID_LISTIMG_PetList)
		m_pID_LISTIMG_PetList->Clear();

	if(m_pID_LIST_ReplaceName)
		m_pID_LIST_ReplaceName->Clear();
	if(m_pID_LIST_ReplacePoint)
		m_pID_LIST_ReplacePoint->Clear();
	if(m_pID_LIST_ReplaceLvl)
		m_pID_LIST_ReplaceLvl->Clear();
	if(m_pID_LIST_ReplaceWall)
		m_pID_LIST_ReplaceWall->Clear();
    
    SetStallStart( CSystemStallage::Instance()->IsSelfInStalling() );
    //SetSelectItem( NULL );
	SelectItem(-1);
}

void CUI_ID_FRAME_PrivateShop::SetStallStart( bool bStart )
{
    if( !IsUILoad() )
        return;

    if( bStart )
    {
        m_pID_BUTTON_Rename->SetEnable( false );
        m_pID_BUTTON_Ok->SetVisable( false );
        m_pID_BUTTON_Cancel->SetVisable( true );
    }
    else
    {
        m_pID_BUTTON_Rename->SetEnable( true );
        m_pID_BUTTON_Ok->SetVisable( true );
        m_pID_BUTTON_Cancel->SetVisable( false );
    }
}

void CUI_ID_FRAME_PrivateShop::SetTitleName( const char* pTitle )
{
    if( !IsUILoad() || !pTitle )
        return;

    m_pID_TEXT_StallName->SetText( pTitle );
}

void CUI_ID_FRAME_PrivateShop::SetPlayerName( const char* pName )
{
    if( !IsUILoad() || !pName )
        return;

    m_pID_TEXT_PlayerName->SetText( pName );
}

void CUI_ID_FRAME_PrivateShop::SetTaxPercent( int nTax )
{
    if( !IsUILoad() )
        return;

    nTax = min( nTax, 100 );
    nTax = max( nTax, 0 );

    char szTax[MAX_PATH] = {0};
    MeSprintf_s( szTax, sizeof( szTax ) / sizeof( char ) - 1, "%d%%", nTax );
    m_pID_TEXT_Tax->SetText( szTax );
}

void CUI_ID_FRAME_PrivateShop::SetSellGoods( int nIndex, SCharItem* pItem, int nMoneyPrice, int nGoldPrice )
{
    if( !IsUILoad() )
        return;

    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_CommonList->GetItemCnt() )
        return;

    if( !pItem )
        return;

    ControlIconDrag::S_ListImg stList;
    stList.SetData( pItem );
    stList.SetOtherInfo( CSystemStallage::Instance()->GetPriceTipString( nMoneyPrice ).c_str() );
    m_pID_LISTIMG_CommonList->SetItem( &stList, nIndex );


    // 重置价格
//     ControlIconDrag::S_ListImg* pCurList = m_pID_LISTIMG_CommonList->GetItemByIndex( nIndex );
//     if( pCurList && pCurList == m_pSelectItem )
//     {
//         SetSelectItem( pCurList, true, false );
//     }

	SelectItem(nIndex, CSystemStallage::E_Goods_common);
}

void CUI_ID_FRAME_PrivateShop::SetSellMount( int nIndex, SCharItem* pItem, int nMoneyPrice, int nGoldPrice )
{
    if( !IsUILoad() )
        return;

    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_PetList->GetItemCnt() )
        return;

    if( !pItem )
        return;

    ControlIconDrag::S_ListImg stList;
    stList.SetData( pItem );
    stList.SetOtherInfo( CSystemStallage::Instance()->GetPriceTipString( nMoneyPrice ).c_str() );
    m_pID_LISTIMG_PetList->SetItem( &stList, nIndex );


    // 重置价格
//     ControlIconDrag::S_ListImg* pCurList = m_pID_LISTIMG_Reclaim->GetItemByIndex( nIndex );
//     if( pCurList && pCurList == m_pSelectItem )
//     {
//         SetSelectItem( pCurList, true, true );
//     }


	SelectItem(nIndex, CSystemStallage::E_Goods_mount);

}

void CUI_ID_FRAME_PrivateShop::SetBuyGoods( int nIndex, int nItemId, int nItemCnt, int nMoneyPrice, int nGoldPrice )
{
    if( !IsUILoad() )
        return;

    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_Reclaim->GetItemCnt() )
        return;

    ControlIconDrag::S_ListImg stList;
    stList.SetData( nItemId, nItemCnt );
    stList.SetOtherInfo( CSystemStallage::Instance()->GetPriceTipString( nMoneyPrice ).c_str() );
    m_pID_LISTIMG_Reclaim->SetItem( &stList, nIndex );


    // 重置价格
//     ControlIconDrag::S_ListImg* pCurList = m_pID_LISTIMG_Reclaim->GetItemByIndex( nIndex );
//     if( pCurList && pCurList == m_pSelectItem )
//     {
//         SetSelectItem( pCurList, false, false );
//     }


	SelectItem(nIndex, CSystemStallage::E_Goods_buy);

}
void CUI_ID_FRAME_PrivateShop::SetSellGoodsPrice( int nIndex, int nMoneyPrice, int nGoldPrice )
{
    if( !IsUILoad() )
        return;

    // 更新数量
    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_CommonList->GetItemCnt() )
        return;

    ControlIconDrag::S_ListImg* pList =  m_pID_LISTIMG_CommonList->GetItemByIndex( nIndex );
    if( !pList || !pList->m_pkIconInfo )
        return;

    pList->m_pkIconInfo->ClearOtherInfo();
    pList->SetOtherInfo( CSystemStallage::Instance()->GetPriceTipString( nMoneyPrice ).c_str() );

    // 重置价格
//     ControlIconDrag::S_ListImg* pCurList = m_pID_LISTIMG_CommonList->GetItemByIndex( nIndex );
//     if( pCurList && pCurList == m_pSelectItem )
//     {
//         SetSelectItem( pCurList, true, false );
//     }


	SelectItem(nIndex, CSystemStallage::E_Goods_common);
}

void CUI_ID_FRAME_PrivateShop::SetSellPetPrice(int nIndex, int nMoneyPrice, int nGoldPrice)
{
	if( !IsUILoad() )
		return;

	if( !IsUILoad() )
		return;

	// 设置商品信息
	if(nIndex < 0)
		return;

	SelectItem(nIndex, CSystemStallage::E_Goods_pet);
}

void CUI_ID_FRAME_PrivateShop::SetSellMountPrice( int nIndex, int nMoneyPrice, int nGoldPrice )
{
    if( !IsUILoad() )
        return;

    // 更新数量
    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_PetList->GetItemCnt() )
        return;

    ControlIconDrag::S_ListImg* pList =  m_pID_LISTIMG_PetList->GetItemByIndex( nIndex );
    if( !pList || !pList->m_pkIconInfo )
        return;

    pList->m_pkIconInfo->ClearOtherInfo();
    pList->SetOtherInfo( CSystemStallage::Instance()->GetPriceTipString( nMoneyPrice ).c_str() );

    // 重置价格
//     ControlIconDrag::S_ListImg* pCurList = m_pID_LISTIMG_PetList->GetItemByIndex( nIndex );
//     if( pCurList && pCurList == m_pSelectItem )
//     {
//         SetSelectItem( pCurList, true, false );
//    }

	SelectItem(nIndex, CSystemStallage::E_Goods_mount);
}

void CUI_ID_FRAME_PrivateShop::SetBuyGoodsPrice( int nIndex, int nMoneyPrice, int nGoldPrice )
{
    if( !IsUILoad() )
        return;

    // 更新数量
    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_Reclaim->GetItemCnt() )
        return;

    ControlIconDrag::S_ListImg* pList =  m_pID_LISTIMG_Reclaim->GetItemByIndex( nIndex );
    if( !pList || !pList->m_pkIconInfo )
        return;

    pList->m_pkIconInfo->ClearOtherInfo();
    pList->SetOtherInfo( CSystemStallage::Instance()->GetPriceTipString( nMoneyPrice ).c_str() );

    // 重置价格
//     ControlIconDrag::S_ListImg* pCurList = m_pID_LISTIMG_Reclaim->GetItemByIndex( nIndex );
//     if( pCurList && pCurList == m_pSelectItem )
//     {
//         SetSelectItem( pCurList, true, false );
//     }

	SelectItem(nIndex, CSystemStallage::E_Goods_buy);
}

void CUI_ID_FRAME_PrivateShop::RemoveGoodsSellByIndex( int nIndex )
{
    if( !IsUILoad() )
        return;

    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_CommonList->GetItemCnt() )
        return;

    // 移除
    ControlIconDrag::S_ListImg* pList = m_pID_LISTIMG_CommonList->GetItemByIndex( nIndex );
    if( pList && pList == m_pSelectItem )
    {
        //SetSelectItem( NULL );

		SelectItem(-1, CSystemStallage::E_Goods_common);
    }
    m_pID_LISTIMG_CommonList->RemoveItemByIndex( nIndex );
}

void CUI_ID_FRAME_PrivateShop::RemoveMountSellByIndex( int nIndex )
{
    if( !IsUILoad() )
        return;

    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_PetList->GetItemCnt() )
        return;
    
    // 移除
    ControlIconDrag::S_ListImg* pList = m_pID_LISTIMG_PetList->GetItemByIndex( nIndex );
    if( pList && pList == m_pSelectItem )
    {
        //SetSelectItem( NULL );

		SelectItem(-1, CSystemStallage::E_Goods_mount);
    }
    m_pID_LISTIMG_PetList->RemoveItemByIndex( nIndex );
}

void CUI_ID_FRAME_PrivateShop::RemoveGoodsBuyByIndex( int nIndex )
{
    if( !IsUILoad() )
        return;

    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_Reclaim->GetItemCnt() )
        return;

    // 移除
    ControlIconDrag::S_ListImg* pList = m_pID_LISTIMG_Reclaim->GetItemByIndex( nIndex );
    if( pList && pList == m_pSelectItem )
    {
        //SetSelectItem( NULL );

		SelectItem(-1, CSystemStallage::E_Goods_buy);
    }
    m_pID_LISTIMG_Reclaim->RemoveItemByIndex( nIndex );
}

std::string CUI_ID_FRAME_PrivateShop::GetStallageTitleName()
{
    std::string strTitle;
    if( IsUILoad() )
    {
        strTitle = m_pID_TEXT_StallName->GetText();
    }
    return strTitle;
}

/*
void CUI_ID_FRAME_PrivateShop::RefreshCurrentPageInfo(void)
{
	if( !IsUILoad() )
		return;

	ControlCheckBox *page = GetCurrentPage();
	if(NULL == page)
		return;

	CSystemStallage::EGoodsType goodType = CSystemStallage::E_Goods_end;
	int subIndex = -1;

	if(page == m_pID_CHECKBOX_Common)
	{
		ControlIconDrag::S_ListImg* pSeletedItem = NULL;
		if(m_pID_LISTIMG_CommonList)
		{
			pSeletedItem = m_pID_LISTIMG_CommonList->GetCurSelItem();
			if(pSeletedItem)
			{
				goodType = CSystemStallage::E_Goods_common;

			}
		}
	
		if(m_pID_LISTIMG_Reclaim)
		{
			pSeletedItem = m_pID_LISTIMG_Reclaim->GetCurSelItem();
			if(pSeletedItem)
				goodType = CSystemStallage::E_Goods_buy;
		}

		if(NULL == pSeletedItem)
		{
			if(m_pID_BUTTON_SetPrice)
				m_pID_BUTTON_SetPrice->SetEnable( false );

			ChangePriceUI(0, 0);
		}
		else
		{

		}

	}
	else if(page == m_pID_CHECKBOX_Pet)
	{

	}
	else if(page == m_pID_CHECKBOX_Replace)
	{
		 
	}



	// 清空
	if( !pItem )
	{
		if( m_pSelectItem && m_pSelectItem->m_pkIconInfo )
		{
			m_pSelectItem->m_pkIconInfo->SetColorFrameType( eColorFrame_None );
		}
		m_pSelectItem = NULL;
		m_pID_BUTTON_SetPrice->SetEnable( false );
		m_pID_BUTTON_SeekPet->SetEnable( false );
		ChangePriceUI( 0, 0 );
		return;
	}

	int nIndex( -1 );
	if( bIsSell && !bIsMount )
	{
		// 出售道具
		nIndex = m_pID_LISTIMG_CommonList->GetItemIndex( pItem );
	}
	else if( bIsSell && bIsMount )
	{
		// 出售坐骑
		nIndex = m_pID_LISTIMG_PetList->GetItemIndex( pItem );
	}
	else if( !bIsSell && !bIsMount )
	{
		// 收购道具
		nIndex = m_pID_LISTIMG_Reclaim->GetItemIndex( pItem );
	}

	if( nIndex < 0 )
		return;

	int nMoneyPrice( 0 ), nGoldPrice( 0 ), nCount( 0 );
	if( !CSystemStallage::Instance()->GetSelfItemPrice( nIndex, bIsSell, bIsMount, nMoneyPrice, nGoldPrice, nCount ) )
		return;

	// 显示价格
	ChangePriceUI( nMoneyPrice, nCount );

	m_pID_BUTTON_SetPrice->SetEnable( true );

	// 选中的为坐骑时可以查看
	if( bIsMount )
	{
		m_pID_BUTTON_SeekPet->SetEnable( true );
	}
	else
	{
		m_pID_BUTTON_SeekPet->SetEnable( false );
	}

	// 设置选中框
	if( m_pSelectItem && m_pSelectItem->m_pkIconInfo )
	{
		m_pSelectItem->m_pkIconInfo->SetColorFrameType( eColorFrame_None );
	}

	m_pSelectItem = pItem;
	if( m_pSelectItem->m_pkIconInfo )
	{
		m_pSelectItem->m_pkIconInfo->SetColorFrameType( eColorFrame_Select );
	}
}
*/

void CUI_ID_FRAME_PrivateShop::MarkItem(int subIndex_, CSystemStallage::EGoodsType goodType_)
{
	if(subIndex_ < 0)
		return;

	switch(goodType_)
	{
	case CSystemStallage::E_Goods_common:
		{
			if(m_pID_LISTIMG_CommonList)
			{
				ControlIconDrag::S_ListImg *pItem = m_pID_LISTIMG_CommonList->GetItemByIndex(subIndex_);
				if(pItem && pItem->m_pkIconInfo )
				{
					pItem->m_pkIconInfo->SetColorFrameType(eColorFrame_Select);
				}
			}
		}
		break;
	case CSystemStallage::E_Goods_pet:
		{

		}
		break;
	case CSystemStallage::E_Goods_replace:
		{

		}
		break;
	case CSystemStallage::E_Goods_mount:
		{
			if(m_pID_LISTIMG_PetList)
			{
				ControlIconDrag::S_ListImg *pItem = m_pID_LISTIMG_PetList->GetItemByIndex(subIndex_);
				if(pItem && pItem->m_pkIconInfo )
				{
					pItem->m_pkIconInfo->SetColorFrameType( eColorFrame_Select );
				}
			}
		}
		break;
	case CSystemStallage::E_Goods_buy:
		{
			if(m_pID_LISTIMG_Reclaim)
			{
				ControlIconDrag::S_ListImg *pItem = m_pID_LISTIMG_Reclaim->GetItemByIndex(subIndex_);
				if(pItem && pItem->m_pkIconInfo )
				{
					pItem->m_pkIconInfo->SetColorFrameType(eColorFrame_Select);
				}
			}
		}
		break;
	default:
		{
			assert(false);
		}
	}
}

void CUI_ID_FRAME_PrivateShop::UnmarkItem(int subIndex_, CSystemStallage::EGoodsType goodType_)
{
	if(subIndex_ < 0)
		return;

	switch(goodType_)
	{
	case CSystemStallage::E_Goods_common:
		{
			if(m_pID_LISTIMG_CommonList)
			{
				ControlIconDrag::S_ListImg *pItem = m_pID_LISTIMG_CommonList->GetItemByIndex(subIndex_);
				if(pItem && pItem->m_pkIconInfo )
				{
					pItem->m_pkIconInfo->SetColorFrameType( eColorFrame_None );
				}
			}
		}
		break;
	case CSystemStallage::E_Goods_pet:
		{

		}
		break;
	case CSystemStallage::E_Goods_replace:
		{

		}
		break;
	case CSystemStallage::E_Goods_mount:
		{
			if(m_pID_LISTIMG_PetList)
			{
				ControlIconDrag::S_ListImg *pItem = m_pID_LISTIMG_PetList->GetItemByIndex(subIndex_);
				if(pItem && pItem->m_pkIconInfo )
				{
					pItem->m_pkIconInfo->SetColorFrameType( eColorFrame_None );
				}
			}
		}
		break;
	case CSystemStallage::E_Goods_buy:
		{
			if(m_pID_LISTIMG_Reclaim)
			{
				ControlIconDrag::S_ListImg *pItem = m_pID_LISTIMG_Reclaim->GetItemByIndex(subIndex_);
				if(pItem && pItem->m_pkIconInfo )
				{
					pItem->m_pkIconInfo->SetColorFrameType( eColorFrame_None );
				}
			}
		}
		break;
	default:
		{
			assert(false);
		}
	}
}

void CUI_ID_FRAME_PrivateShop::ClearSelectedItemInfo(int subIndex_, CSystemStallage::EGoodsType goodType_)
{
	UnmarkItem(subIndex_, goodType_);
	m_selectedItemIndex = -1;
	ChangePriceUI( 0, 0 );

	if(m_pID_BUTTON_SetPrice)
		m_pID_BUTTON_SetPrice->SetEnable( false );

	//m_pID_BUTTON_SeekPet->SetEnable( false );
}

void CUI_ID_FRAME_PrivateShop::SetSelectedItemInfo(int subIndex_, CSystemStallage::EGoodsType goodType_)
{
	m_selectedItemIndex = CSystemStallage::Instance()->GetTotalIndexBySubIndex(subIndex_, goodType_);
	MarkItem(subIndex_, goodType_);

	if(m_pID_BUTTON_SetPrice)
		m_pID_BUTTON_SetPrice->SetEnable(true);
}

void CUI_ID_FRAME_PrivateShop::SelectItem(int totalIndex_)
{
	int subIndex = -1;
	CSystemStallage::EGoodsType goodType = CSystemStallage::Instance()->GetGoodInfo(totalIndex_, subIndex);
	SelectItem(subIndex, goodType);
}

void CUI_ID_FRAME_PrivateShop::SelectItem(int subIndex_, CSystemStallage::EGoodsType goodType_)
{
	if( !IsUILoad() )
		return;

	//clear
	if(subIndex_ < 0 || goodType_ >= CSystemStallage::E_Goods_end)
	{
		ClearSelectedItemInfo(subIndex_, goodType_);
		return;
	}
	
	//check whether the param is valid or not

	int nMoneyPrice( 0 ), nGoldPrice( 0 ), nCount( 0 );
	if( !CSystemStallage::Instance()->GetSelfItemPrice(subIndex_, goodType_, nMoneyPrice, nGoldPrice, nCount ) )
		return;

	// 显示价格
	ChangePriceUI( nMoneyPrice, nCount );

	{
		int oldSubIndex = -1;
		CSystemStallage::EGoodsType oldGoodType = CSystemStallage::Instance()->GetGoodInfo(m_selectedItemIndex, oldSubIndex);
		UnmarkItem(oldSubIndex, oldGoodType);
	}

	SetSelectedItemInfo(subIndex_, goodType_);
}

void CUI_ID_FRAME_PrivateShop::SetSelectItem( ControlIconDrag::S_ListImg* pItem, bool bIsSell, bool bIsMount )
{
    if( !IsUILoad() )
        return;

    // 清空
    if( !pItem )
    {
        if( m_pSelectItem && m_pSelectItem->m_pkIconInfo )
        {
            m_pSelectItem->m_pkIconInfo->SetColorFrameType( eColorFrame_None );
        }
        m_pSelectItem = NULL;
        m_pID_BUTTON_SetPrice->SetEnable( false );
        m_pID_BUTTON_SeekPet->SetEnable( false );
        ChangePriceUI( 0, 0 );
        return;
    }

    int nIndex( -1 );
    if( bIsSell && !bIsMount )
    {
        // 出售道具
        nIndex = m_pID_LISTIMG_CommonList->GetItemIndex( pItem );
    }
    else if( bIsSell && bIsMount )
    {
        // 出售坐骑
        nIndex = m_pID_LISTIMG_PetList->GetItemIndex( pItem );
    }
    else if( !bIsSell && !bIsMount )
    {
        // 收购道具
        nIndex = m_pID_LISTIMG_Reclaim->GetItemIndex( pItem );
    }

    if( nIndex < 0 )
        return;

    int nMoneyPrice( 0 ), nGoldPrice( 0 ), nCount( 0 );
    if( !CSystemStallage::Instance()->GetSelfItemPrice( nIndex, bIsSell, bIsMount, nMoneyPrice, nGoldPrice, nCount ) )
        return;

    // 显示价格
    ChangePriceUI( nMoneyPrice, nCount );

    m_pID_BUTTON_SetPrice->SetEnable( true );

    // 选中的为坐骑时可以查看
    if( bIsMount )
    {
        m_pID_BUTTON_SeekPet->SetEnable( true );
    }
    else
    {
        m_pID_BUTTON_SeekPet->SetEnable( false );
    }

    // 设置选中框
    if( m_pSelectItem && m_pSelectItem->m_pkIconInfo )
    {
        m_pSelectItem->m_pkIconInfo->SetColorFrameType( eColorFrame_None );
    }

    m_pSelectItem = pItem;
    if( m_pSelectItem->m_pkIconInfo )
    {
        m_pSelectItem->m_pkIconInfo->SetColorFrameType( eColorFrame_Select );
    }
}

void CUI_ID_FRAME_PrivateShop::SetCurrentItemPrice()
{
    if( !IsUILoad() )
        return;

/*
    if( !m_pSelectItem || !m_pSelectItem->m_pkIconInfo )
        return;

    // 判断当前选的是什么
    int nIndex( -1 );
    bool bIsSell( true ), bIsMount( false );
    nIndex = m_pID_LISTIMG_CommonList->GetItemIndex( m_pSelectItem );
    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_CommonList->GetItemCnt() )
    {
        nIndex = -1;
    }
    else
    {
        bIsMount = false;
        bIsSell = true;
    }

    if( nIndex < 0 )
    {
        nIndex = m_pID_LISTIMG_PetList->GetItemIndex( m_pSelectItem );
        if( nIndex < 0 || nIndex >= m_pID_LISTIMG_PetList->GetItemCnt() )
        {
            nIndex = -1;
        }
        else
        {
            bIsMount = true;
            bIsSell = true;
        }
    }

    if( nIndex < 0 )
    {
        nIndex = m_pID_LISTIMG_Reclaim->GetItemIndex( m_pSelectItem );
        if( nIndex < 0 || nIndex >= m_pID_LISTIMG_Reclaim->GetItemCnt() )
            return;

        bIsMount = false;
        bIsSell = false;
    }

    // 设置价格
    CSystemStallage::Instance()->SetItemPrice( nIndex, bIsSell, bIsMount, m_pSelectItem->m_pkIconInfo->GetOnlyId() );
*/

	CSystemStallage::Instance()->SetItemPrice(m_selectedItemIndex); 
}

void CUI_ID_FRAME_PrivateShop::ResetControls(void)
{
	m_pID_FRAME_PrivateShop = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_LISTIMG_CommonList = NULL;
	m_pID_BUTTON_Record = NULL;
	m_pID_EDIT_StallName = NULL;
	m_pID_TEXT_Jin = NULL;
	m_pID_TEXT_TotalPrice = NULL;
	m_pID_LISTIMG_PetList = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_SetPrice = NULL;
	m_pID_BUTTON_SeekPet = NULL;
	m_pID_TEXT_PlayerName = NULL;
	m_pID_TEXT_Tax = NULL;
	m_pID_LISTIMG_Reclaim = NULL;
	m_pID_TEXT_StallName = NULL;
	m_pID_BUTTON_Rename = NULL;
	m_pID_CHECKBOX_Common = NULL;
	m_pID_CHECKBOX_Pet = NULL;
	m_pID_CHECKBOX_Replace = NULL;
	m_pID_LIST_PetName = NULL;
	m_pID_LIST_PetSelectWall = NULL;
	m_pID_PICTURE_CommonWall = NULL;
	m_pID_PICTURE_PetWall = NULL;
	m_pID_PICTURE_ReplaceWall = NULL;
	m_pID_LIST_ReplaceName = NULL;
	m_pID_LIST_ReplacePoint = NULL;
	m_pID_LIST_ReplaceLvl = NULL;
	m_pID_LIST_ReplaceWall = NULL;
	m_pID_COMBOBOX_ReplaceLvlChoose = NULL;
	m_pID_TEXT_Expend = NULL;
	m_pID_BUTTON_Update = NULL;
	m_tabFrame.Clear();
}

void CUI_ID_FRAME_PrivateShop::TogglePage(ControlCheckBox *pPage_)
{
	SelectItem(0);

	if(NULL == pPage_)
		return;

	m_tabFrame.TogglePage(pPage_);

	if(m_pID_CHECKBOX_Common == pPage_)
	{
		s_CUI_ID_FRAME_PACK.SetVisable(true);
	}
	else
	{
		s_CUI_ID_FRAME_PACK.SetVisable(false);
	}

	if(m_pID_CHECKBOX_Pet == pPage_)
	{
		s_CUI_ID_FRAME_SelectPet.SetVisable(true);
	}
	else
	{
		s_CUI_ID_FRAME_SelectPet.SetVisable(false);
	}

	if(m_pID_CHECKBOX_Replace == pPage_)
	{
		s_CUI_ID_FRAME_ReplaceList.SetVisable(true);
	}
	else
	{
		s_CUI_ID_FRAME_ReplaceList.SetVisable(false);
	}
}

void CUI_ID_FRAME_PrivateShop::RemovePetSellByIndex(int index_)
{
	if( !IsUILoad() )
		return;

	if(index_ < 0)
		return;

	// 移除
/*
	ControlIconDrag::S_ListImg* pList = m_pID_LISTIMG_CommonList->GetItemByIndex( nIndex );
	if( pList && pList == m_pSelectItem )
	{
		SetSelectItem( NULL );
	}
	m_pID_LISTIMG_CommonList->RemoveItemByIndex( nIndex );
*/

	if(m_pID_LIST_PetSelectWall)
	{
		for(int i=0; i<m_pID_LIST_PetSelectWall->GetListItemCnt(); ++i)
		{
			ControlList::S_List *pstList = m_pID_LIST_PetSelectWall->GetListItem()[i];
			if( pstList )
			{
				if (index_ == pstList->m_nID)
				{
					m_pID_LIST_PetSelectWall->RemoveListItem(i);
					break;
				}
			}
		}
	}

	if(m_pID_LIST_PetName)
	{
		for(int i=0; i<m_pID_LIST_PetName->GetListItemCnt(); ++i)
		{
			ControlList::S_List *pstList = m_pID_LIST_PetName->GetListItem()[i];
			if( pstList )
			{
				if (index_ == pstList->m_nID)
				{
					m_pID_LIST_PetName->RemoveListItem(i);
					break;
				}
			}
		}
	}

	if(m_pID_LISTIMG_PetList)
	{
		m_pID_LISTIMG_PetList->RemoveItemByIndex(index_);
	}

}

void CUI_ID_FRAME_PrivateShop::SetSellPet(int index_, SPetItem *pItem_, int moneyPrice_, int goldPrice_)
{
	if( !IsUILoad() )
		return;

	// 设置商品信息
	if(index_ < 0)
		return;

	if( !pItem_)
		return;

	if(m_pID_LIST_PetSelectWall)
	{
		ControlList::S_List stItem;
		stItem.SetData("", /*0*/index_, pItem_);
		m_pID_LIST_PetSelectWall->AddItem(&stItem,NULL, false);
	}

	if(m_pID_LIST_PetName)
	{
		ControlList::S_List stItem;
		ItemDefine::SPetMonster *pPetMonster = GettheItemDetail().GetPetById(pItem_->baseInfo.petId);
		char temp[64]={0};
		if(pPetMonster != NULL)
		{
			if (strcmp(pPetMonster->GetName(),pItem_->GetPetName())!= 0)
			{
				MeSprintf_s(temp,sizeof(temp),"%s(%s)",pItem_->GetPetName(),pPetMonster->GetName());
			}
			else
			{
				MeSprintf_s(temp,sizeof(temp),"%s",pItem_->GetPetName());
			}
		}
		else
		{
			MeSprintf_s(temp,sizeof(temp),"%s",pItem_->GetPetName());
		}
		stItem.SetData(temp, index_);
		m_pID_LIST_PetName->AddItem(&stItem, NULL, false);
	}

	SelectItem(index_, CSystemStallage::E_Goods_pet);
}

int CUI_ID_FRAME_PrivateShop::GetPetIndex(const SPetItem &pet_)
{
	int index = -1;
	if(!IsVisable() || NULL == m_pID_LIST_PetSelectWall)
		return index;

	for(int i=0; i<m_pID_LIST_PetSelectWall->GetListItemCnt(); ++i)
	{
		ControlList::S_List *pItem = m_pID_LIST_PetSelectWall->GetListItem(i);

		if(pItem != NULL)
		{
			SPetItem *pet = (SPetItem *)pItem->m_pData;
			if(pet != NULL && IsValidPet(*pet))
			{
				if(pet->GetPetGuid() == pet_.GetPetGuid())
					return /*i*/pItem->m_nID;
			}
		}
	}

	return index;
}

ControlCheckBox *CUI_ID_FRAME_PrivateShop::GetCurrentPage(void)
{
	ControlCheckBox *page = NULL;

	if(m_pID_CHECKBOX_Common && m_pID_CHECKBOX_Common->IsChecked())
		page = m_pID_CHECKBOX_Common;
	else if(m_pID_CHECKBOX_Pet && m_pID_CHECKBOX_Pet->IsChecked())
		page = m_pID_CHECKBOX_Pet;
	else if(m_pID_CHECKBOX_Replace && m_pID_CHECKBOX_Replace->IsChecked())
		page = m_pID_CHECKBOX_Replace;

	return page;
}
