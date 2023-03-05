/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\PlayerPrivateShop.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PlayerPrivateShop.h"
#include "PlayerRole.h"
#include "SystemStallage.h"
#include "MeUi/ExpressionManager.h"
#include "Common.h"
#include "Pack.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "UIMgr.h"
#include "ui\PutInItem.h"
#include "ui/SeeSuAnimal.h"

#define MAX_DIS_CLOSEWINDOW 12

CUI_ID_FRAME_PlayerPrivateShop s_CUI_ID_FRAME_PlayerPrivateShop;

MAP_FRAME_RUN( s_CUI_ID_FRAME_PlayerPrivateShop, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PlayerPrivateShop, OnFrameRender )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PlayerPrivateShop, ID_LISTIMG_CommonListOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PlayerPrivateShop, ID_LISTIMG_CommonListOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PlayerPrivateShop, ID_BUTTON_BuyOnButtonClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PlayerPrivateShop, ID_LISTIMG_PetListOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PlayerPrivateShop, ID_LISTIMG_PetListOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PlayerPrivateShop, ID_BUTTON_LeaveWordOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PlayerPrivateShop, ID_BUTTON_SeekPetOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_PlayerPrivateShop, ID_LISTIMG_ReclaimOnIconDragOn )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PlayerPrivateShop, ID_LISTIMG_ReclaimOnIconButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PlayerPrivateShop, ID_CHECKBOX_CommonOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PlayerPrivateShop, ID_CHECKBOX_PetOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PlayerPrivateShop, ID_CHECKBOX_ReplaceOnCheckBoxCheck )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_PlayerPrivateShop, ID_LIST_PetNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_PlayerPrivateShop, ID_LIST_PetSelectWallOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_PlayerPrivateShop, ID_LIST_ReplaceNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_PlayerPrivateShop, ID_LIST_ReplacePointOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_PlayerPrivateShop, ID_LIST_ReplaceLvlOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_PlayerPrivateShop, ID_LIST_ReplaceWallOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PlayerPrivateShop, ID_BUTTON_ChooseOnButtonClick )

CUI_ID_FRAME_PlayerPrivateShop::CUI_ID_FRAME_PlayerPrivateShop()
{
    ResetMembers();
    m_pSelectItem = NULL;
	m_IsOnlineStall = false;
}

void CUI_ID_FRAME_PlayerPrivateShop::ResetMembers()
{
	m_pID_FRAME_PlayerPrivateShop = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_LISTIMG_CommonList = NULL;
	m_pID_BUTTON_Buy = NULL;
	m_pID_TEXT_Price = NULL;
	m_pID_TEXT_TotalPrice = NULL;
	m_pID_TEXT_StallName = NULL;
	m_pID_TEXT_PlayerName = NULL;
	m_pID_LISTIMG_PetList = NULL;
	m_pID_TEXT_Tax = NULL;
	m_pID_BUTTON_LeaveWord = NULL;
	m_pID_BUTTON_SeekPet = NULL;
	m_pID_LISTIMG_Reclaim = NULL;
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
	m_pID_TEXT_Expend = NULL;
	m_pID_BUTTON_Choose = NULL;
}

bool CUI_ID_FRAME_PlayerPrivateShop::OnFrameRun()
{
    // 距离过远自动关闭界面
    int nVenderId = CSystemStallage::Instance()->GetVenderId();
    if( IsVisable() && nVenderId >= 0 )
    {
        CPlayer* pVender = theHeroGame.GetPlayerMgr()->FindByID( nVenderId );
        if( pVender )
        {
            if( pVender->GetDistanceToRole() > MAX_DIS_CLOSEWINDOW )
            {
                SetVisable( false );
            }
        }
    }
	return true;
}

bool CUI_ID_FRAME_PlayerPrivateShop::OnFrameRender()
{
	return true;
}

// Button
bool CUI_ID_FRAME_PlayerPrivateShop::ID_BUTTON_BuyOnButtonClick( ControlObject* pSender )
{
    if ( !IsUILoad() )
        return false;

    BuyCurrentItem();
    return true;
}

// Button
bool CUI_ID_FRAME_PlayerPrivateShop::ID_BUTTON_LeaveWordOnButtonClick( ControlObject* pSender )
{
    if ( !IsUILoad() )
        return false;

    CSystemStallage::Instance()->LeaveMessageToVender();
    return true;
}

bool CUI_ID_FRAME_PlayerPrivateShop::ID_BUTTON_SeekPetOnButtonClick( ControlObject* pSender )
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

        CSystemStallage::Instance()->SeekPlayerMountByIndex( nIndex, m_pSelectItem->m_pkIconInfo->GetOnlyId() );
    }
*/

	if (m_selectedItemIndex >= 18 && m_selectedItemIndex < StallDefine::MaxSellCount)
	{
		ControlIconDrag::S_ListImg* pItem1 = NULL;
		if (m_pID_LISTIMG_PetList)
			pItem1 = m_pID_LISTIMG_PetList->GetCurSelItem();

		if (pItem1 != NULL)
		{
			int index = m_pID_LISTIMG_PetList->GetItemIndex( pItem1);
			CSystemStallage::Instance()->SeekPlayerMountByIndex( index, pItem1->m_pkIconInfo->GetOnlyId() );
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

    return true;
}

// ListImg / ListEx
bool CUI_ID_FRAME_PlayerPrivateShop::ID_LISTIMG_CommonListOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !IsUILoad() )
		return false;

    if( !pItem || pItem->IsNull() )
        return false;

    //SetSelectItem( pItem, true, false );
	SelectItem(((ControlListImage *)pSender)->GetItemIndex(pItem), CSystemStallage::E_Goods_common);
	return false;
}

bool CUI_ID_FRAME_PlayerPrivateShop::ID_LISTIMG_CommonListOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !IsUILoad() )
		return false;

    if( !pItem || pItem->IsNull() )
        return false;

    //SetSelectItem( pItem, true, false );
	SelectItem(((ControlListImage *)pSender)->GetItemIndex(pItem), CSystemStallage::E_Goods_common);
    BuyCurrentItem();
	return false;
}

bool CUI_ID_FRAME_PlayerPrivateShop::ID_LISTIMG_PetListOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !IsUILoad() )
		return false;

    //SetSelectItem( pItem, true, true );
	SelectItem(((ControlListImage *)pSender)->GetItemIndex(pItem), CSystemStallage::E_Goods_mount);
	return false;
}

bool CUI_ID_FRAME_PlayerPrivateShop::ID_LISTIMG_PetListOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !IsUILoad() )
		return false;

     //SetSelectItem( pItem, true, true );
	SelectItem(((ControlListImage *)pSender)->GetItemIndex(pItem), CSystemStallage::E_Goods_mount);
     BuyCurrentItem();
	return false;
}

bool CUI_ID_FRAME_PlayerPrivateShop::ID_LISTIMG_ReclaimOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !IsUILoad() )
		return false;

    if( !pItemDrag || !pItemSrc )
        return false;

    // 源地址空或目标地址空均返回
    if( pItemDrag->IsNull() || pItemSrc->IsNull() )
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

    // 获取Guid
    ControlListImage* pListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType( nBagType );
    if( !pListImg )
        return false;

    if( !pItemDrag->m_pkIconInfo )
        return false;
    
    __int64 nGuid = pItemDrag->m_pkIconInfo->GetOnlyId();

    // 玩家背包栏索引
    int nSrcIndex = pListImg->GetItemIndex( pItemDrag );
    if( nSrcIndex < 0 || nSrcIndex >= pListImg->GetItemCnt() )
        return false;
    
    
    // 摊主收购栏索引
    int nDstIndex = m_pID_LISTIMG_Reclaim->GetItemIndex( pItemSrc );
    if( nDstIndex < 0 || nDstIndex >= m_pID_LISTIMG_Reclaim->GetItemCnt() )
        return false;

    CSystemStallage::Instance()->MoveItemToVenderBuy( nBagType, nSrcIndex, nDstIndex, nGuid );
	return false;
}

bool CUI_ID_FRAME_PlayerPrivateShop::ID_LISTIMG_ReclaimOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !IsUILoad() )
		return false;

    //SetSelectItem( pItem, false, false );
	SelectItem(((ControlListImage *)pSender)->GetItemIndex(pItem), CSystemStallage::E_Goods_buy);
	return false;
}

// CheckBox
void CUI_ID_FRAME_PlayerPrivateShop::ID_CHECKBOX_CommonOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_tabFrame.TogglePage((ControlCheckBox *)pSender);

	SelectItem(-1);
}
// CheckBox
void CUI_ID_FRAME_PlayerPrivateShop::ID_CHECKBOX_PetOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_tabFrame.TogglePage((ControlCheckBox *)pSender);
	SelectItem(-1);
}
// CheckBox
void CUI_ID_FRAME_PlayerPrivateShop::ID_CHECKBOX_ReplaceOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_tabFrame.TogglePage((ControlCheckBox *)pSender);
	SelectItem(-1);
}

// List
void CUI_ID_FRAME_PlayerPrivateShop::ID_LIST_PetNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_PlayerPrivateShop::ID_LIST_PetSelectWallOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(NULL == pItem)
		return;

	SelectItem(/*((ControlList *)pSender)->GetCurSelIndex()*/pItem->m_nID, CSystemStallage::E_Goods_pet);
}
// List
void CUI_ID_FRAME_PlayerPrivateShop::ID_LIST_ReplaceNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_PlayerPrivateShop::ID_LIST_ReplacePointOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_PlayerPrivateShop::ID_LIST_ReplaceLvlOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_PlayerPrivateShop::ID_LIST_ReplaceWallOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(NULL == pItem)
		return;

	SelectItem(((ControlList *)pSender)->GetCurSelIndex(), CSystemStallage::E_Goods_replace);
}
// Button
bool CUI_ID_FRAME_PlayerPrivateShop::ID_BUTTON_ChooseOnButtonClick( ControlObject* pSender )
{
	return true;
}

// 装载UI
bool CUI_ID_FRAME_PlayerPrivateShop::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PlayerPrivateShop.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\PlayerPrivateShop.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_PlayerPrivateShop::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PlayerPrivateShop, s_CUI_ID_FRAME_PlayerPrivateShopOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PlayerPrivateShop, s_CUI_ID_FRAME_PlayerPrivateShopOnFrameRender );
	theUiManager.OnIconButtonClick( ID_FRAME_PlayerPrivateShop, ID_LISTIMG_CommonList, s_CUI_ID_FRAME_PlayerPrivateShopID_LISTIMG_CommonListOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PlayerPrivateShop, ID_LISTIMG_CommonList, s_CUI_ID_FRAME_PlayerPrivateShopID_LISTIMG_CommonListOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_PlayerPrivateShop, ID_BUTTON_Buy, s_CUI_ID_FRAME_PlayerPrivateShopID_BUTTON_BuyOnButtonClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PlayerPrivateShop, ID_LISTIMG_PetList, s_CUI_ID_FRAME_PlayerPrivateShopID_LISTIMG_PetListOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PlayerPrivateShop, ID_LISTIMG_PetList, s_CUI_ID_FRAME_PlayerPrivateShopID_LISTIMG_PetListOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_PlayerPrivateShop, ID_BUTTON_LeaveWord, s_CUI_ID_FRAME_PlayerPrivateShopID_BUTTON_LeaveWordOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PlayerPrivateShop, ID_BUTTON_SeekPet, s_CUI_ID_FRAME_PlayerPrivateShopID_BUTTON_SeekPetOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_PlayerPrivateShop, ID_LISTIMG_Reclaim, s_CUI_ID_FRAME_PlayerPrivateShopID_LISTIMG_ReclaimOnIconDragOn );
	theUiManager.OnIconButtonClick( ID_FRAME_PlayerPrivateShop, ID_LISTIMG_Reclaim, s_CUI_ID_FRAME_PlayerPrivateShopID_LISTIMG_ReclaimOnIconButtonClick );
	
	theUiManager.OnCheckBoxCheck( ID_FRAME_PlayerPrivateShop, ID_CHECKBOX_Common, s_CUI_ID_FRAME_PlayerPrivateShopID_CHECKBOX_CommonOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PlayerPrivateShop, ID_CHECKBOX_Pet, s_CUI_ID_FRAME_PlayerPrivateShopID_CHECKBOX_PetOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PlayerPrivateShop, ID_CHECKBOX_Replace, s_CUI_ID_FRAME_PlayerPrivateShopID_CHECKBOX_ReplaceOnCheckBoxCheck );

	theUiManager.OnListSelectChange( ID_FRAME_PlayerPrivateShop, ID_LIST_PetName, s_CUI_ID_FRAME_PlayerPrivateShopID_LIST_PetNameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_PlayerPrivateShop, ID_LIST_PetSelectWall, s_CUI_ID_FRAME_PlayerPrivateShopID_LIST_PetSelectWallOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_PlayerPrivateShop, ID_LIST_ReplaceName, s_CUI_ID_FRAME_PlayerPrivateShopID_LIST_ReplaceNameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_PlayerPrivateShop, ID_LIST_ReplacePoint, s_CUI_ID_FRAME_PlayerPrivateShopID_LIST_ReplacePointOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_PlayerPrivateShop, ID_LIST_ReplaceLvl, s_CUI_ID_FRAME_PlayerPrivateShopID_LIST_ReplaceLvlOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_PlayerPrivateShop, ID_LIST_ReplaceWall, s_CUI_ID_FRAME_PlayerPrivateShopID_LIST_ReplaceWallOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_PlayerPrivateShop, ID_BUTTON_Choose, s_CUI_ID_FRAME_PlayerPrivateShopID_BUTTON_ChooseOnButtonClick );

	m_pID_FRAME_PlayerPrivateShop = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PlayerPrivateShop );
	m_pID_LISTIMG_CommonList = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_LISTIMG_CommonList );
	m_pID_BUTTON_Buy = (ControlButton*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_BUTTON_Buy );
	m_pID_TEXT_Price = (ControlText*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_TEXT_Price );
	m_pID_TEXT_TotalPrice = (ControlText*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_TEXT_TotalPrice );
	m_pID_TEXT_StallName = (ControlText*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_TEXT_StallName );
	m_pID_TEXT_PlayerName = (ControlText*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_TEXT_PlayerName );
	m_pID_LISTIMG_PetList = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_LISTIMG_PetList );
	m_pID_TEXT_Tax = (ControlText*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_TEXT_Tax );
	m_pID_BUTTON_LeaveWord = (ControlButton*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_BUTTON_LeaveWord );
	m_pID_BUTTON_SeekPet = (ControlButton*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_BUTTON_SeekPet );
	m_pID_LISTIMG_Reclaim = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_LISTIMG_Reclaim );

	m_pID_FRAME_PlayerPrivateShop = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PlayerPrivateShop );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_BUTTON_CLOSE );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_BUTTON_HELP );
	m_pID_LISTIMG_CommonList = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_LISTIMG_CommonList );
	m_pID_BUTTON_Buy = (ControlButton*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_BUTTON_Buy );
	m_pID_TEXT_Price = (ControlText*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_TEXT_Price );
	m_pID_TEXT_TotalPrice = (ControlText*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_TEXT_TotalPrice );
	m_pID_TEXT_StallName = (ControlText*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_TEXT_StallName );
	m_pID_TEXT_PlayerName = (ControlText*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_TEXT_PlayerName );
	m_pID_LISTIMG_PetList = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_LISTIMG_PetList );
	m_pID_TEXT_Tax = (ControlText*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_TEXT_Tax );
	m_pID_BUTTON_LeaveWord = (ControlButton*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_BUTTON_LeaveWord );
	m_pID_BUTTON_SeekPet = (ControlButton*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_BUTTON_SeekPet );
	m_pID_LISTIMG_Reclaim = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_LISTIMG_Reclaim );
	m_pID_CHECKBOX_Common = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_CHECKBOX_Common );
	m_pID_CHECKBOX_Pet = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_CHECKBOX_Pet );
	m_pID_CHECKBOX_Replace = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_CHECKBOX_Replace );
	m_pID_LIST_PetName = (ControlList*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_LIST_PetName );
	m_pID_LIST_PetSelectWall = (ControlList*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_LIST_PetSelectWall );
	m_pID_PICTURE_CommonWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_PICTURE_CommonWall );
	m_pID_PICTURE_PetWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_PICTURE_PetWall );
	m_pID_PICTURE_ReplaceWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_PICTURE_ReplaceWall );
	m_pID_LIST_ReplaceName = (ControlList*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_LIST_ReplaceName );
	m_pID_LIST_ReplacePoint = (ControlList*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_LIST_ReplacePoint );
	m_pID_LIST_ReplaceLvl = (ControlList*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_LIST_ReplaceLvl );
	m_pID_LIST_ReplaceWall = (ControlList*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_LIST_ReplaceWall );
	m_pID_TEXT_Expend = (ControlText*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_TEXT_Expend );
	m_pID_BUTTON_Choose = (ControlButton*)theUiManager.FindControl( ID_FRAME_PlayerPrivateShop, ID_BUTTON_Choose );
	assert( m_pID_FRAME_PlayerPrivateShop );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_LISTIMG_CommonList );
	assert( m_pID_BUTTON_Buy );
	assert( m_pID_TEXT_Price );
	assert( m_pID_TEXT_TotalPrice );
	assert( m_pID_TEXT_StallName );
	assert( m_pID_TEXT_PlayerName );
	assert( m_pID_LISTIMG_PetList );
	assert( m_pID_TEXT_Tax );
	assert( m_pID_BUTTON_LeaveWord );
	assert( m_pID_BUTTON_SeekPet );
	assert( m_pID_LISTIMG_Reclaim );
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
	assert( m_pID_TEXT_Expend );
	assert( m_pID_BUTTON_Choose );

    m_pID_LISTIMG_CommonList->SetCanbePick( false );
    m_pID_LISTIMG_PetList->SetCanbePick( false );
    m_pID_LISTIMG_Reclaim->SetCanbePick( false );

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
		m_groupProxy.AddControl(m_pID_TEXT_Expend);
		m_groupProxy.AddControl(m_pID_BUTTON_Choose);

		m_tabFrame.AddPage(m_pID_CHECKBOX_Replace, &m_groupProxy);
	}

	if (m_pID_CHECKBOX_Common)
		m_tabFrame.TogglePage(m_pID_CHECKBOX_Common);

	SetVisable( false );
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_PlayerPrivateShop::_UnLoadUI()
{
    m_pSelectItem = NULL;
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\PlayerPrivateShop.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_PlayerPrivateShop::_IsVisable()
{
	if ( !m_pID_FRAME_PlayerPrivateShop )
		return false;
	return m_pID_FRAME_PlayerPrivateShop->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_PlayerPrivateShop::_SetVisable( const bool bVisable )
{
	if ( !IsUILoad() )
		return;

	m_pID_FRAME_PlayerPrivateShop->SetVisable( bVisable );

    if( bVisable )
    {
        s_CUI_ID_FRAME_PACK.SetVisable( true );
        ResetWindowPosition( m_pID_FRAME_PlayerPrivateShop, s_CUI_ID_FRAME_PACK.GetFrame() );

		if ( m_IsOnlineStall )
			m_pID_BUTTON_LeaveWord->SetEnable(true);
		else
			m_pID_BUTTON_LeaveWord->SetEnable(false);
    }
}

bool CUI_ID_FRAME_PlayerPrivateShop::IsEqualToCommonList( ControlObject* pObject )
{
    if( !IsUILoad() || !pObject )
        return false;

    return ( m_pID_LISTIMG_CommonList == ( ControlListImage* )pObject);
}

void CUI_ID_FRAME_PlayerPrivateShop::ChangePriceUI( DWORD dwPrice, unsigned int uiCount )
{
    //计算单价
    std::string text = "";
    thePlayerRole.GetGSCStringFromMoney( dwPrice, text );
    *m_pID_TEXT_Price = text;

    //计算总价
    DWORD dwTotalPrice = dwPrice * uiCount;
    std::string strTotalPriceText = "";
    thePlayerRole.GetGSCStringFromMoney( dwTotalPrice, strTotalPriceText );
    ExpressionManager::GetInstance().AddExpressionAni( strTotalPriceText );
    *m_pID_TEXT_TotalPrice = strTotalPriceText;
}

//--------------------新的摆摊逻辑相关部分--------------------------
void CUI_ID_FRAME_PlayerPrivateShop::ClearAll()
{
    if( !IsUILoad() )
        return;

    m_pID_TEXT_StallName->SetText( "" );
    m_pID_TEXT_PlayerName->SetText( "" );
    m_pID_TEXT_Tax->SetText( "" );

//     m_pID_LISTIMG_CommonList->Clear();
//     m_pID_LISTIMG_PetList->Clear();
//     m_pID_LISTIMG_Reclaim->Clear();

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

    //SetSelectItem( NULL );
	SelectItem(-1);
}

void CUI_ID_FRAME_PlayerPrivateShop::SetTitleName( const char* pTitle )
{
    if( !IsUILoad() || !pTitle )
        return;

    m_pID_TEXT_StallName->SetText( pTitle );
}

void CUI_ID_FRAME_PlayerPrivateShop::SetPlayerName( const char* pName )
{
    if( !IsUILoad() || !pName )
        return;

    m_pID_TEXT_PlayerName->SetText( pName );
}

void CUI_ID_FRAME_PlayerPrivateShop::SetTaxPercent( int nTax )
{
    if( !IsUILoad() )
        return;

    nTax = min( nTax, 100 );
    nTax = max( nTax, 0 );

    char szTax[MAX_PATH] = {0};
    MeSprintf_s( szTax, sizeof( szTax ) / sizeof( char ) - 1, "%d%%", nTax );
    m_pID_TEXT_Tax->SetText( szTax );
}

void CUI_ID_FRAME_PlayerPrivateShop::SetSellPet(int index_, SPetItem *pItem_, int moneyPrice_, int goldPrice_)
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
		stItem.SetData("",/* 0*/index_, pItem_);
		m_pID_LIST_PetSelectWall->AddItem(&stItem,NULL, false);
	}

	if(m_pID_LIST_PetName)
	{
		ControlList::S_List stItem;
		stItem.SetData(pItem_->GetPetName(), index_);
		m_pID_LIST_PetName->AddItem(&stItem, NULL, false);
	}

// 	// 重置价格
// 	ControlIconDrag::S_ListImg* pCurList = m_pID_LISTIMG_CommonList->GetItemByIndex( nIndex );
// 	if( pCurList && pCurList == m_pSelectItem )
// 	{
// 		SetSelectItem( pCurList, true, false );
// 	}

	SelectItem(index_, CSystemStallage::E_Goods_pet);
}

void CUI_ID_FRAME_PlayerPrivateShop::SetSellGoods( int nIndex, SCharItem* pItem, int nMoneyPrice, int nGoldPrice )
{
    if( !IsUILoad() )
        return;

    // 设置商品信息
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

void CUI_ID_FRAME_PlayerPrivateShop::SetSellMount( int nIndex, SCharItem* pItem, int nMoneyPrice, int nGoldPrice )
{
    if( !IsUILoad() )
        return;

    // 设置商品信息
    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_PetList->GetItemCnt() )
        return;
    
    if( !pItem )
        return;

    ControlIconDrag::S_ListImg stList;
    stList.SetData( pItem );
    stList.SetOtherInfo( CSystemStallage::Instance()->GetPriceTipString( nMoneyPrice ).c_str() );
    m_pID_LISTIMG_PetList->SetItem( &stList, nIndex );

    // 重置价格
//     ControlIconDrag::S_ListImg* pCurList = m_pID_LISTIMG_CommonList->GetItemByIndex( nIndex );
//     if( pCurList && pCurList == m_pSelectItem )
//     {
//         SetSelectItem( pCurList, true, true );
//     }

	SelectItem(nIndex, CSystemStallage::E_Goods_mount);
}

void CUI_ID_FRAME_PlayerPrivateShop::SetBuyGoods( int nIndex, int nItemId, int nItemCnt, int nMoneyPrice, int nGoldPrice )
{
    if( !IsUILoad() )
        return;

    // 设置商品信息
    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_Reclaim->GetItemCnt() )
        return;

    ControlIconDrag::S_ListImg stList;
    stList.SetData( nItemId, nItemCnt );
    stList.SetOtherInfo( CSystemStallage::Instance()->GetPriceTipString( nMoneyPrice ).c_str() );
    m_pID_LISTIMG_Reclaim->SetItem( &stList, nIndex );

    // 重置价格
//     ControlIconDrag::S_ListImg* pCurList = m_pID_LISTIMG_CommonList->GetItemByIndex( nIndex );
//     if( pCurList && pCurList == m_pSelectItem )
//     {
//         SetSelectItem( pCurList, false, false );
//     }

	SelectItem(nIndex, CSystemStallage::E_Goods_buy);
}

void CUI_ID_FRAME_PlayerPrivateShop::RemovePetSellByIndex(int index_)
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

void CUI_ID_FRAME_PlayerPrivateShop::RemoveGoodsSellByIndex( int nIndex )
{
    if( !IsUILoad() )
        return;

    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_CommonList->GetItemCnt() )
        return;

    // 移除
 //   ControlIconDrag::S_ListImg* pList = m_pID_LISTIMG_CommonList->GetItemByIndex( nIndex );
//     if( pList && pList == m_pSelectItem )
//     {
//         SetSelectItem( NULL );
//     }

	SelectItem(-1);
    m_pID_LISTIMG_CommonList->RemoveItemByIndex( nIndex );
}

void CUI_ID_FRAME_PlayerPrivateShop::RemoveMountSellByIndex( int nIndex )
{
    if( !IsUILoad() )
        return;

    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_PetList->GetItemCnt() )
        return;

    // 移除
//     ControlIconDrag::S_ListImg* pList = m_pID_LISTIMG_PetList->GetItemByIndex( nIndex );
//     if( pList && pList == m_pSelectItem )
//     {
//         SetSelectItem( NULL );
//     }
	SelectItem(-1);
    m_pID_LISTIMG_PetList->RemoveItemByIndex( nIndex );
}

void CUI_ID_FRAME_PlayerPrivateShop::RemoveGoodsBuyByIndex( int nIndex )
{
    if( !IsUILoad() )
        return;

    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_Reclaim->GetItemCnt() )
        return;

    // 移除
//     ControlIconDrag::S_ListImg* pList = m_pID_LISTIMG_Reclaim->GetItemByIndex( nIndex );
//     if( pList && pList == m_pSelectItem )
//     {
//         SetSelectItem( NULL );
//     }
	SelectItem(-1);
    m_pID_LISTIMG_Reclaim->RemoveItemByIndex( nIndex );
}

void CUI_ID_FRAME_PlayerPrivateShop::SetGoodsSellCnt( int nIndex, int nItemCnt, int nMoneyPrice, int nGoldPrice )
{
    if( !IsUILoad() )
        return;

    // 更新数量
    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_CommonList->GetItemCnt() )
        return;

    ControlIconDrag::S_ListImg* pList =  m_pID_LISTIMG_CommonList->GetItemByIndex( nIndex );
    if( !pList || !pList->m_pkIconInfo )
        return;

    SCharItem charItem;
    charItem.itembaseinfo.ustItemID = pList->m_pkIconInfo->GetItemId();
    charItem.itembaseinfo.nOnlyInt = pList->m_pkIconInfo->GetOnlyId();
    charItem.SetItemCount( nItemCnt );

    ControlIconDrag::S_ListImg stList;
    stList.SetData( &charItem );
    stList.SetOtherInfo( CSystemStallage::Instance()->GetPriceTipString( nMoneyPrice ).c_str() );
    m_pID_LISTIMG_CommonList->SetItem( &stList, nIndex );

    // 重置价格
//     ControlIconDrag::S_ListImg* pCurList = m_pID_LISTIMG_CommonList->GetItemByIndex( nIndex );
//     if( pCurList && pCurList == m_pSelectItem )
//     {
//         SetSelectItem( pCurList, true, false );
//    }
	SelectItem(nIndex, CSystemStallage::E_Goods_common);
}

void CUI_ID_FRAME_PlayerPrivateShop::SetGoodsBuyCnt( int nIndex, int nItemCnt, int nMoneyPrice, int nGoldPrice )
{
    if( !IsUILoad() )
        return;

    // 更新数量
    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_Reclaim->GetItemCnt() )
        return;

    ControlIconDrag::S_ListImg* pList =  m_pID_LISTIMG_Reclaim->GetItemByIndex( nIndex );
    if( !pList || !pList->m_pkIconInfo )
        return;

    ControlIconDrag::S_ListImg stList;
    stList.SetData( pList->m_pkIconInfo->GetItemId(), nItemCnt );
    stList.SetOtherInfo( CSystemStallage::Instance()->GetPriceTipString( nMoneyPrice ).c_str() );
    m_pID_LISTIMG_Reclaim->SetItem( &stList, nIndex );

    // 重置价格
//     ControlIconDrag::S_ListImg* pCurList = m_pID_LISTIMG_Reclaim->GetItemByIndex( nIndex );
//     if( pCurList && pCurList == m_pSelectItem )
//     {
//         SetSelectItem( pCurList, false, false );
//    }

	SelectItem(nIndex, CSystemStallage::E_Goods_buy);
}

void CUI_ID_FRAME_PlayerPrivateShop::SetSelectItem( ControlIconDrag::S_ListImg* pItem, bool bIsSell, bool bIsMount )
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
        m_pID_BUTTON_Buy->SetEnable( false );
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
    if( !CSystemStallage::Instance()->GetPlayerItemPrice( nIndex, bIsSell, bIsMount, nMoneyPrice, nGoldPrice, nCount ) )
        return;

    // 显示价格
    ChangePriceUI( nMoneyPrice, nCount );

    // 玩家不可以买摊主的收购物品
    if( bIsSell )
    {
        m_pID_BUTTON_Buy->SetEnable( true );
    }
    else
    {
        m_pID_BUTTON_Buy->SetEnable( false );
    }

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

void CUI_ID_FRAME_PlayerPrivateShop::BuyCurrentItem()
{
    if( !IsUILoad() )
        return;

	
    /*if( !m_pSelectItem || !m_pSelectItem->m_pkIconInfo )
        return;

    // 判断当前选的是什么
    int nIndex( -1 );
    bool bIsMount( false );
    nIndex = m_pID_LISTIMG_CommonList->GetItemIndex( m_pSelectItem );
    if( nIndex < 0 || nIndex >= m_pID_LISTIMG_CommonList->GetItemCnt() )
    {
        nIndex = -1;
    }
    else
    {
        bIsMount = false;
    }

    if( nIndex < 0 )
    {
        nIndex = m_pID_LISTIMG_PetList->GetItemIndex( m_pSelectItem );
        if( nIndex < 0 || nIndex >= m_pID_LISTIMG_PetList->GetItemCnt() )
            return;

        bIsMount = true;
    }

    // 玩家向摊主购买
    CSystemStallage::Instance()->GetItemFromVenderSell( nIndex, bIsMount, m_pSelectItem->m_pkIconInfo->GetOnlyId() );
	*/

	CSystemStallage::Instance()->GetItemFromVenderSell(m_selectedItemIndex);
}

void CUI_ID_FRAME_PlayerPrivateShop::MarkItem(int subIndex_, CSystemStallage::EGoodsType goodType_)
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

void CUI_ID_FRAME_PlayerPrivateShop::UnmarkItem(int subIndex_, CSystemStallage::EGoodsType goodType_)
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

void CUI_ID_FRAME_PlayerPrivateShop::ClearSelectedItemInfo(int subIndex_, CSystemStallage::EGoodsType goodType_)
{
	UnmarkItem(subIndex_, goodType_);
	m_selectedItemIndex = -1;
	ChangePriceUI( 0, 0 );

	if(m_pID_BUTTON_Buy)
		m_pID_BUTTON_Buy->SetEnable( false );

	//m_pID_BUTTON_SeekPet->SetEnable( false );
}

void CUI_ID_FRAME_PlayerPrivateShop::SetSelectedItemInfo(int subIndex_, CSystemStallage::EGoodsType goodType_)
{
	m_selectedItemIndex = CSystemStallage::Instance()->GetTotalIndexBySubIndex(subIndex_, goodType_);
	MarkItem(subIndex_, goodType_);

	if(m_pID_BUTTON_Buy)
		m_pID_BUTTON_Buy->SetEnable(true);
}

void CUI_ID_FRAME_PlayerPrivateShop::SelectItem(int totalIndex_)
{
	int subIndex = -1;
	CSystemStallage::EGoodsType goodType = CSystemStallage::Instance()->GetGoodInfo(totalIndex_, subIndex);
	SelectItem(subIndex, goodType);
}

void CUI_ID_FRAME_PlayerPrivateShop::SelectItem(int subIndex_, CSystemStallage::EGoodsType goodType_)
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
	if( !CSystemStallage::Instance()->GetPlayerItemPrice(subIndex_, goodType_, nMoneyPrice, nGoldPrice, nCount ) )
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
