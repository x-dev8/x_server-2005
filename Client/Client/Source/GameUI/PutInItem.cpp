/********************************************************************
Created by UIEditor.exe
FileName: F:\project\Turbo\Bin\Client\Data\Ui\PutInItem.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PutInItem.h"

CUI_ID_FRAME_PutInItem s_CUI_ID_FRAME_PutInItem;
MAP_FRAME_RUN( s_CUI_ID_FRAME_PutInItem, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PutInItem, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PutInItem, ID_BUTTON_TureOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PutInItem, ID_BUTTON_CancelOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_PutInItem, ID_LISTIMG_ItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_PutInItem, ID_LISTIMG_ItemOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PutInItem, ID_LISTIMG_ItemOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PutInItem, ID_LISTIMG_ItemOnIconRButtonUp )
CUI_ID_FRAME_PutInItem::CUI_ID_FRAME_PutInItem()
{
	// Member
	m_pID_FRAME_PutInItem = NULL;
	m_pID_BUTTON_Ture = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_LISTIMG_Item = NULL;
	m_pID_TEXT_Title = NULL;

}
// Frame
bool CUI_ID_FRAME_PutInItem::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_PutInItem::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_PutInItem::ID_BUTTON_TureOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_PutInItem::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_PutInItem::ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														 ControlIconDrag::S_ListImg* pItemDrag,
														 ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_PutInItem::ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_PutInItem::ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_PutInItem::ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// 装载UI
bool CUI_ID_FRAME_PutInItem::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PutInItem.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\PutInItem.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_PutInItem::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PutInItem, s_CUI_ID_FRAME_PutInItemOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PutInItem, s_CUI_ID_FRAME_PutInItemOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_PutInItem, ID_BUTTON_Ture, s_CUI_ID_FRAME_PutInItemID_BUTTON_TureOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PutInItem, ID_BUTTON_Cancel, s_CUI_ID_FRAME_PutInItemID_BUTTON_CancelOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_PutInItem, ID_LISTIMG_Item, s_CUI_ID_FRAME_PutInItemID_LISTIMG_ItemOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PutInItem, ID_LISTIMG_Item, s_CUI_ID_FRAME_PutInItemID_LISTIMG_ItemOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PutInItem, ID_LISTIMG_Item, s_CUI_ID_FRAME_PutInItemID_LISTIMG_ItemOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PutInItem, ID_LISTIMG_Item, s_CUI_ID_FRAME_PutInItemID_LISTIMG_ItemOnIconRButtonUp );

	m_pID_FRAME_PutInItem = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PutInItem );
	m_pID_BUTTON_Ture = (ControlButton*)theUiManager.FindControl( ID_FRAME_PutInItem, ID_BUTTON_Ture );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_PutInItem, ID_BUTTON_Cancel );
	m_pID_LISTIMG_Item = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PutInItem, ID_LISTIMG_Item );
	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_PutInItem, ID_TEXT_Title );
	assert( m_pID_FRAME_PutInItem );
	assert( m_pID_BUTTON_Ture );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_LISTIMG_Item );
	assert( m_pID_TEXT_Title );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_PutInItem::_UnLoadUI()
{
	m_pID_FRAME_PutInItem = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\PutInItem.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_PutInItem::_IsVisable()
{
	return m_pID_FRAME_PutInItem->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_PutInItem::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_PutInItem->SetVisable( bVisable );
}
