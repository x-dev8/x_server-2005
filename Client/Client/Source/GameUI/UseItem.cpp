/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\UseItem.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "UseItem.h"
#include "PlayerRole.h"
#include "Pack.h"

CUI_ID_FRAME_UseItem s_CUI_ID_FRAME_UseItem;

MAP_FRAME_RUN( s_CUI_ID_FRAME_UseItem, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_UseItem, OnFrameRender )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_UseItem, ID_LISTIMG_ItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_UseItem, ID_LISTIMG_ItemOnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_UseItem, ID_LISTIMG_ItemOnIconRButtonUp )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_UseItem, ID_LISTIMG_ItemOnIconButtonClick )
CUI_ID_FRAME_UseItem::CUI_ID_FRAME_UseItem()
{
	// Member
	m_pID_FRAME_UseItem = NULL;
	m_pID_LISTIMG_Item = NULL;
	m_ItemId = 0;

}
CUI_ID_FRAME_UseItem::~CUI_ID_FRAME_UseItem()
{
}
// Frame
bool CUI_ID_FRAME_UseItem::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_UseItem::OnFrameRender()
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_UseItem::ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_UseItem::ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_UseItem::ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_LISTIMG_Item || !pItem || pItem->IsNull() || m_ItemId == 0)
	{
		_SetVisable(false);
		return false;
	}

	ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( m_ItemId );
	if (!pItemDetail)
	{
		_SetVisable(false);
		return false;
	}

	CItemBag2* pBag = 0;
	int nBagType = thePlayerRole.GetBagTypeByItemType( pItemDetail->ucItemType );
	ControlListImage* pBagListImg = 0;

	switch ( nBagType )
	{
	case BT_NormalItemBag:
		{
			pBag = &thePlayerRole.m_bag;
			pBagListImg = s_CUI_ID_FRAME_PACK.GetBagListImg();
		}

		break;
	case BT_MaterialBag:
		{
			pBag = &thePlayerRole.m_bagMaterial;
			pBagListImg = s_CUI_ID_FRAME_PACK.GetMaterialListImg();
		}
		break;
	case BT_TaskBag:
		{
			pBag = &thePlayerRole.m_bagTask;
			pBagListImg = s_CUI_ID_FRAME_PACK.GetTaskListImg();
		}
		break;
	}

	if (!pBag || !pBagListImg)
	{
		_SetVisable(false);
		return false;
	}

	int nIndex = pBag->GetItemIndexById( m_ItemId );

	if (nIndex == -1)
	{
		_SetVisable(false);
		return false;
	}

	s_CUI_ID_FRAME_PACK.UseItem( pBagListImg, pBag, nBagType, m_ItemId, nIndex );
	m_pID_LISTIMG_Item->Clear();
	m_ItemId = 0;
	_SetVisable(false);

	return false;
}
bool CUI_ID_FRAME_UseItem::ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_LISTIMG_Item || !pItem || pItem->IsNull() || m_ItemId == 0)
	{
		_SetVisable(false);
		return false;
	}

	ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( m_ItemId );
	if (!pItemDetail)
	{
		_SetVisable(false);
		return false;
	}

	CItemBag2* pBag = 0;
	int nBagType = thePlayerRole.GetBagTypeByItemType( pItemDetail->ucItemType );
	ControlListImage* pBagListImg = 0;

	switch ( nBagType )
	{
	case BT_NormalItemBag:
		{
			pBag = &thePlayerRole.m_bag;
			pBagListImg = s_CUI_ID_FRAME_PACK.GetBagListImg();
		}

		break;
	case BT_MaterialBag:
		{
			pBag = &thePlayerRole.m_bagMaterial;
			pBagListImg = s_CUI_ID_FRAME_PACK.GetMaterialListImg();
		}
		break;
	case BT_TaskBag:
		{
			pBag = &thePlayerRole.m_bagTask;
			pBagListImg = s_CUI_ID_FRAME_PACK.GetTaskListImg();
		}
		break;
	}

	if (!pBag || !pBagListImg)
	{
		_SetVisable(false);
		return false;
	}

	int nIndex = pBag->GetItemIndexById( m_ItemId );

	if (nIndex == -1)
	{
		_SetVisable(false);
		return false;
	}

	s_CUI_ID_FRAME_PACK.UseItem( pBagListImg, pBag, nBagType, m_ItemId, nIndex );
	m_pID_LISTIMG_Item->Clear();
	m_ItemId = 0;
	_SetVisable(false);

	return false;
}
// 装载UI
bool CUI_ID_FRAME_UseItem::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\UseItem.meui", true, UI_Render_LayerThree  );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\UseItem.meui]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_UseItem::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_UseItem, s_CUI_ID_FRAME_UseItemOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_UseItem, s_CUI_ID_FRAME_UseItemOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_UseItem, ID_LISTIMG_Item, s_CUI_ID_FRAME_UseItemID_LISTIMG_ItemOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_UseItem, ID_LISTIMG_Item, s_CUI_ID_FRAME_UseItemID_LISTIMG_ItemOnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_UseItem, ID_LISTIMG_Item, s_CUI_ID_FRAME_UseItemID_LISTIMG_ItemOnIconRButtonUp );
	theUiManager.OnIconButtonClick( ID_FRAME_UseItem, ID_LISTIMG_Item, s_CUI_ID_FRAME_UseItemID_LISTIMG_ItemOnIconButtonClick );

	m_pID_FRAME_UseItem = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_UseItem );
	m_pID_LISTIMG_Item = (ControlListImage*)theUiManager.FindControl( ID_FRAME_UseItem, ID_LISTIMG_Item );
	assert( m_pID_FRAME_UseItem );
	assert( m_pID_LISTIMG_Item );

	m_pID_FRAME_UseItem->SetOnEscResponseType( ControlFrame::EscResponse_SkipMe );

	_SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_UseItem::_UnLoadUI()
{
	return theUiManager.RemoveFrame( "Data\\UI\\UseItem.meui" );
}
// 是否可视
bool CUI_ID_FRAME_UseItem::_IsVisable()
{
	if (!m_pID_FRAME_UseItem)
		return false;
	return m_pID_FRAME_UseItem->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_UseItem::_SetVisable( const bool bVisable )
{
	if (!m_pID_FRAME_UseItem)
		return;
	m_pID_FRAME_UseItem->SetVisable( bVisable );
}

void CUI_ID_FRAME_UseItem::SetItem(unsigned short ustItemId)
{
	if (ustItemId == 0 || !m_pID_LISTIMG_Item)
	{
		_SetVisable(false);
		return;
	}
	m_pID_LISTIMG_Item->Clear();

	ControlIconDrag::S_ListImg sListItem;
	SCharItem stItem;

	ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( ustItemId );
	if (!pItemDetail)
	{
		_SetVisable(false);
		return;
	}

	CItemBag2* pBag = 0;

	switch (thePlayerRole.GetBagTypeByItemType(pItemDetail->ucItemType))
	{
	case BT_NormalItemBag:
		pBag = &thePlayerRole.m_bag;
		break;
	case BT_MaterialBag:
		pBag = &thePlayerRole.m_bagMaterial;
		break;
	case BT_TaskBag:
		pBag = &thePlayerRole.m_bagTask;
		break;
	}

	if (!pBag)
	{
		_SetVisable(false);
		return;
	}

	if ( !pBag->GetItemByItemID( ustItemId, &stItem) )
	{
		_SetVisable(false);
		return;
	}

	m_ItemId = ustItemId;

	sListItem.SetData( &stItem );
	sListItem.SetSparkEnable( true );

	m_pID_LISTIMG_Item->SetItem( &sListItem, 0 );
}