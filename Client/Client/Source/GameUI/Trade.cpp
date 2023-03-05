/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\Trade.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Trade.h"
#include "TradeCenterInfo.h"
#include "ShopCenter.h"

CUI_ID_FRAME_Trade s_CUI_ID_FRAME_Trade;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Trade, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Trade, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Trade, ID_BUTTON_ShoppingOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade1OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade2OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade3OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade3OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade3OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade3OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade4OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade4OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade4OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade4OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade5OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade5OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade5OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade5OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade6OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade6OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade6OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Trade, ID_LISTIMG_Trade6OnIconRButtonUp )
CUI_ID_FRAME_Trade::CUI_ID_FRAME_Trade()
{
	// Member
	ResetMembers();
}

void CUI_ID_FRAME_Trade::ResetMembers()
{
	m_pID_FRAME_Trade = NULL;
	//m_pID_PICTURE_ShopItemWall = NULL;
	m_pID_BUTTON_Shopping = NULL;
	m_pID_LISTIMG_Trade1 = NULL;
	m_pID_TEXT_TradePrice1 = NULL;
	m_pID_LISTIMG_Trade2 = NULL;
	m_pID_TEXT_TradePrice2 = NULL;
	m_pID_LISTIMG_Trade3 = NULL;
	m_pID_TEXT_TradePrice3 = NULL;
	m_pID_LISTIMG_Trade4 = NULL;
	m_pID_TEXT_TradePrice4 = NULL;
	m_pID_LISTIMG_Trade5 = NULL;
	m_pID_TEXT_TradePrice5 = NULL;
	m_pID_LISTIMG_Trade6 = NULL;
	m_pID_TEXT_TradePrice6 = NULL;
	m_pID_TEXT_13189 = NULL;

}
// Frame
bool CUI_ID_FRAME_Trade::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_Trade::OnFrameRender()
{
	for (int i = 0; i < m_listImages.size(); ++i)
	{
		m_listImages[i]->SetVisable(false);
		m_prices[i]->SetVisable(false);
	}

	if (m_pID_FRAME_Trade->GetFather())
	{
		std::vector<int> itemIds;
		if (theTradeCenter.GetShortcutsItems(m_pID_FRAME_Trade->GetFather()->GetControlID(), &itemIds))
		{
			int index = 0;
			for (int i = 0; i < itemIds.size() && index < m_listImages.size(); ++i)
			{
				int nItemId = itemIds[i];

				CTradeCenterInfo::cTradeItem* pTradeItem = theTradeCenter.GetTradeItemByItemID(nItemId);
				if (!pTradeItem)
					continue;
				ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID(nItemId);
				if (!pItemDetail)
					continue;

				int nItemCount = s_CUI_ID_FRAME_ShopCenter.FindItemCount(nItemId);
				bool bEnable = nItemCount != 0;

				ControlIconDrag::S_ListImg stListImg;
				if (pTradeItem->m_RefreshInterval == 0)
					stListImg.SetData(nItemId, 1, bEnable ? eIcon_Enable : eIcon_Disable, false);
				else
					stListImg.SetData(nItemId, nItemCount, bEnable ? eIcon_Enable : eIcon_Disable, true);

				stListImg.m_pkIconInfo->SetColorFrameType(eColorFrame_Level);

				m_listImages[index]->SetItem(&stListImg, 0);
				m_listImages[index]->SetVisable(true);

				m_prices[index]->SetText(s_CUI_ID_FRAME_ShopCenter.GetTradeItemMoneyText(*pTradeItem));
				m_prices[index]->SetVisable(true);

				++index;
			}
		}
	}
	return true;
}
// Button
bool CUI_ID_FRAME_Trade::ID_BUTTON_ShoppingOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	if( s_CUI_ID_FRAME_ShopCenter.GetFrame() )
	{
		if( m_pID_FRAME_Trade->GetFather() )
		{
			ControlObject* pObject = s_CUI_ID_FRAME_ShopCenter.GetFrame()->FindControl(
				theTradeCenter.GetShortcutsShopTypeUIID(m_pID_FRAME_Trade->GetFather()->GetControlID()).c_str(),
				s_CUI_ID_FRAME_ShopCenter.GetFrame()->GetControlID());
			if (pObject)
				s_CUI_ID_FRAME_ShopCenter.ToggleTab(pObject);
		}
		s_CUI_ID_FRAME_ShopCenter.SetVisable(!s_CUI_ID_FRAME_ShopCenter.IsVisable());
	}
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													   ControlIconDrag::S_ListImg* pItemDrag,
													   ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													   ControlIconDrag::S_ListImg* pItemDrag,
													   ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade3OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													   ControlIconDrag::S_ListImg* pItemDrag,
													   ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade4OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													   ControlIconDrag::S_ListImg* pItemDrag,
													   ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade5OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													   ControlIconDrag::S_ListImg* pItemDrag,
													   ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade5OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade5OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade5OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade6OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													   ControlIconDrag::S_ListImg* pItemDrag,
													   ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return true;
}
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade6OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return true;
}
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade6OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return Buy(pSender, pItem);
}
bool CUI_ID_FRAME_Trade::ID_LISTIMG_Trade6OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return Buy(pSender, pItem);
}

// 装载UI
bool CUI_ID_FRAME_Trade::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Trade.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Trade.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Trade::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Trade, s_CUI_ID_FRAME_TradeOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Trade, s_CUI_ID_FRAME_TradeOnFrameRender, true );
	theUiManager.OnButtonClick( ID_FRAME_Trade, ID_BUTTON_Shopping, s_CUI_ID_FRAME_TradeID_BUTTON_ShoppingOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Trade, ID_LISTIMG_Trade1, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Trade, ID_LISTIMG_Trade1, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade1OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Trade, ID_LISTIMG_Trade1, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade1OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Trade, ID_LISTIMG_Trade1, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade1OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Trade, ID_LISTIMG_Trade2, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Trade, ID_LISTIMG_Trade2, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Trade, ID_LISTIMG_Trade2, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Trade, ID_LISTIMG_Trade2, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade2OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Trade, ID_LISTIMG_Trade3, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade3OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Trade, ID_LISTIMG_Trade3, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade3OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Trade, ID_LISTIMG_Trade3, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade3OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Trade, ID_LISTIMG_Trade3, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade3OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Trade, ID_LISTIMG_Trade4, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade4OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Trade, ID_LISTIMG_Trade4, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade4OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Trade, ID_LISTIMG_Trade4, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade4OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Trade, ID_LISTIMG_Trade4, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade4OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Trade, ID_LISTIMG_Trade5, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade5OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Trade, ID_LISTIMG_Trade5, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade5OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Trade, ID_LISTIMG_Trade5, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade5OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Trade, ID_LISTIMG_Trade5, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade5OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Trade, ID_LISTIMG_Trade6, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade6OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Trade, ID_LISTIMG_Trade6, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade6OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Trade, ID_LISTIMG_Trade6, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade6OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Trade, ID_LISTIMG_Trade6, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade6OnIconRButtonUp );

	m_pID_FRAME_Trade = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Trade );
	//m_pID_PICTURE_ShopItemWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Trade, ID_PICTURE_ShopItemWall );
	m_pID_BUTTON_Shopping = (ControlButton*)theUiManager.FindControl( ID_FRAME_Trade, ID_BUTTON_Shopping );
	m_pID_LISTIMG_Trade1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Trade, ID_LISTIMG_Trade1 );
	m_pID_TEXT_TradePrice1 = (ControlText*)theUiManager.FindControl( ID_FRAME_Trade, ID_TEXT_TradePrice1 );
	m_pID_LISTIMG_Trade2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Trade, ID_LISTIMG_Trade2 );
	m_pID_TEXT_TradePrice2 = (ControlText*)theUiManager.FindControl( ID_FRAME_Trade, ID_TEXT_TradePrice2 );
	m_pID_LISTIMG_Trade3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Trade, ID_LISTIMG_Trade3 );
	m_pID_TEXT_TradePrice3 = (ControlText*)theUiManager.FindControl( ID_FRAME_Trade, ID_TEXT_TradePrice3 );
	m_pID_LISTIMG_Trade4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Trade, ID_LISTIMG_Trade4 );
	m_pID_TEXT_TradePrice4 = (ControlText*)theUiManager.FindControl( ID_FRAME_Trade, ID_TEXT_TradePrice4 );
	m_pID_LISTIMG_Trade5 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Trade, ID_LISTIMG_Trade5 );
	m_pID_TEXT_TradePrice5 = (ControlText*)theUiManager.FindControl( ID_FRAME_Trade, ID_TEXT_TradePrice5 );
	m_pID_LISTIMG_Trade6 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Trade, ID_LISTIMG_Trade6 );
	m_pID_TEXT_TradePrice6 = (ControlText*)theUiManager.FindControl( ID_FRAME_Trade, ID_TEXT_TradePrice6 );
	m_pID_TEXT_13189 = (ControlText*)theUiManager.FindControl( ID_FRAME_Trade, ID_TEXT_13189 );
	assert( m_pID_FRAME_Trade );
	//assert( m_pID_PICTURE_ShopItemWall );
	assert( m_pID_BUTTON_Shopping );
	assert( m_pID_LISTIMG_Trade1 );
	assert( m_pID_TEXT_TradePrice1 );
	assert( m_pID_LISTIMG_Trade2 );
	assert( m_pID_TEXT_TradePrice2 );
	assert( m_pID_LISTIMG_Trade3 );
	assert( m_pID_TEXT_TradePrice3 );
	assert( m_pID_LISTIMG_Trade4 );
	assert( m_pID_TEXT_TradePrice4 );
	assert( m_pID_LISTIMG_Trade5 );
	assert( m_pID_TEXT_TradePrice5 );
	assert( m_pID_LISTIMG_Trade6 );
	assert( m_pID_TEXT_TradePrice6 );
	assert( m_pID_TEXT_13189 );

	char buf[64];
	int index = 1;
	sprintf(buf, "ID_LISTIMG_Trade%d", index);
	ControlListImage* pListImg = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Trade, buf );
	while (pListImg)
	{
		pListImg->ShowPressEffect(true);

		theUiManager.OnIconDragOn( ID_FRAME_Trade, buf, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade6OnIconDragOn );
		theUiManager.OnIconLDBClick( ID_FRAME_Trade, buf, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade6OnIconLDBClick );
		theUiManager.OnIconButtonClick( ID_FRAME_Trade, buf, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade6OnIconButtonClick );
		theUiManager.OnIconRButtonUp( ID_FRAME_Trade, buf, s_CUI_ID_FRAME_TradeID_LISTIMG_Trade6OnIconRButtonUp );


		sprintf(buf, "ID_TEXT_TradePrice%d", index);
		ControlText* pText = (ControlText*)theUiManager.FindControl( ID_FRAME_Trade, buf );
		if (!pText)
			break;

		m_listImages.push_back(pListImg);
		m_prices.push_back(pText);

		++index;
		sprintf(buf, "ID_LISTIMG_Trade%d", index);
		pListImg = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Trade, buf );
	}

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Trade::_UnLoadUI()
{
	m_listImages.clear();
	m_prices.clear();
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\Trade.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Trade::_IsVisable()
{
	if( !m_pID_FRAME_Trade ) 
		return false;
	return m_pID_FRAME_Trade->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Trade::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_Trade ) 
		return;
	m_pID_FRAME_Trade->SetVisable( bVisable );
}


bool CUI_ID_FRAME_Trade::Buy(ControlObject *pSender, ControlIconDrag::S_ListImg *pItem)
{
	if (!m_pID_FRAME_Trade->GetFather())
		return true;

	std::vector<int> itemIds;
	if (theTradeCenter.GetShortcutsItems(m_pID_FRAME_Trade->GetFather()->GetControlID(), &itemIds))
	{
		int index = 0;
		for (int i = 0; i < itemIds.size() && index < m_listImages.size(); ++i)
		{
			int nItemId = itemIds[i];

			CTradeCenterInfo::cTradeItem* pTradeItem = theTradeCenter.GetTradeItemByItemID(nItemId);
			if (!pTradeItem)
				continue;
			ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID(nItemId);
			if (!pItemDetail)
				continue;

			if (m_listImages[index] == pSender)
				return s_CUI_ID_FRAME_ShopCenter.Buy(nItemId);

			++index;
		}
	}

	return true;
}