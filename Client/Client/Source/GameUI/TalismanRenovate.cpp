/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\法宝资源\法宝\法宝\TalismanRenovate.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "TalismanRenovate.h"
#include "ItemDetail.h"

CUI_ID_FRAME_TalismanRenovate s_CUI_ID_FRAME_TalismanRenovate;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TalismanRenovate, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TalismanRenovate, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_TalismanRenovate, ID_LISTIMG_TalismanIconOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_TalismanRenovate, ID_LISTIMG_TalismanIconOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TalismanRenovate, ID_LISTIMG_TalismanIconOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_TalismanRenovate, ID_LISTIMG_TalismanIconOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_TalismanRenovate, ID_LISTIMG_GenreOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_TalismanRenovate, ID_LISTIMG_GenreOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TalismanRenovate, ID_LISTIMG_GenreOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_TalismanRenovate, ID_LISTIMG_GenreOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_TalismanRenovate, ID_LISTIMG_MaterialIconOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_TalismanRenovate, ID_LISTIMG_MaterialIconOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TalismanRenovate, ID_LISTIMG_MaterialIconOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_TalismanRenovate, ID_LISTIMG_MaterialIconOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TalismanRenovate, ID_BUTTON_ReturnOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TalismanRenovate, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TalismanRenovate, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TalismanRenovate, ID_BUTTON_HELPOnButtonClick )
CUI_ID_FRAME_TalismanRenovate::CUI_ID_FRAME_TalismanRenovate()
{
	// Member
	m_pID_FRAME_TalismanRenovate = NULL;
	m_pID_LISTIMG_TalismanIcon = NULL;
	m_pID_TEXT_TalismanName = NULL;
	m_pID_TEXT_TalismanLv = NULL;
	m_pID_LISTIMG_Genre = NULL;
	m_pID_LISTIMG_MaterialIcon = NULL;
	m_pID_TEXT_MaterialName = NULL;
	m_pID_TEXT_Moment = NULL;
	m_pID_BUTTON_Return = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;

}
// Frame
bool CUI_ID_FRAME_TalismanRenovate::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_TalismanRenovate::OnFrameRender()
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_TalismanRenovate::ID_LISTIMG_TalismanIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_TalismanRenovate )
		return false;
	return false;
}
bool CUI_ID_FRAME_TalismanRenovate::ID_LISTIMG_TalismanIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TalismanRenovate )
		return false;
	return false;
}
bool CUI_ID_FRAME_TalismanRenovate::ID_LISTIMG_TalismanIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TalismanRenovate )
		return false;
	return false;
}
bool CUI_ID_FRAME_TalismanRenovate::ID_LISTIMG_TalismanIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TalismanRenovate )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_TalismanRenovate::ID_LISTIMG_GenreOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_TalismanRenovate )
		return false;
	return false;
}
bool CUI_ID_FRAME_TalismanRenovate::ID_LISTIMG_GenreOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TalismanRenovate )
		return false;
	return false;
}
bool CUI_ID_FRAME_TalismanRenovate::ID_LISTIMG_GenreOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TalismanRenovate )
		return false;
	return false;
}
bool CUI_ID_FRAME_TalismanRenovate::ID_LISTIMG_GenreOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TalismanRenovate )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_TalismanRenovate::ID_LISTIMG_MaterialIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_TalismanRenovate )
		return false;
	return false;
}
bool CUI_ID_FRAME_TalismanRenovate::ID_LISTIMG_MaterialIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TalismanRenovate )
		return false;
	return false;
}
bool CUI_ID_FRAME_TalismanRenovate::ID_LISTIMG_MaterialIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TalismanRenovate )
		return false;
	return false;
}
bool CUI_ID_FRAME_TalismanRenovate::ID_LISTIMG_MaterialIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TalismanRenovate )
		return false;
	return false;
}
// Button
bool CUI_ID_FRAME_TalismanRenovate::ID_BUTTON_ReturnOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TalismanRenovate )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_TalismanRenovate::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TalismanRenovate )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_TalismanRenovate::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TalismanRenovate )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_TalismanRenovate::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TalismanRenovate )
		return false;
	return true;
}

// 装载UI
bool CUI_ID_FRAME_TalismanRenovate::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TalismanRenovate.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\TalismanRenovate.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_TalismanRenovate::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TalismanRenovate, s_CUI_ID_FRAME_TalismanRenovateOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TalismanRenovate, s_CUI_ID_FRAME_TalismanRenovateOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_TalismanRenovate, ID_LISTIMG_TalismanIcon, s_CUI_ID_FRAME_TalismanRenovateID_LISTIMG_TalismanIconOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_TalismanRenovate, ID_LISTIMG_TalismanIcon, s_CUI_ID_FRAME_TalismanRenovateID_LISTIMG_TalismanIconOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_TalismanRenovate, ID_LISTIMG_TalismanIcon, s_CUI_ID_FRAME_TalismanRenovateID_LISTIMG_TalismanIconOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_TalismanRenovate, ID_LISTIMG_TalismanIcon, s_CUI_ID_FRAME_TalismanRenovateID_LISTIMG_TalismanIconOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_TalismanRenovate, ID_LISTIMG_Genre, s_CUI_ID_FRAME_TalismanRenovateID_LISTIMG_GenreOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_TalismanRenovate, ID_LISTIMG_Genre, s_CUI_ID_FRAME_TalismanRenovateID_LISTIMG_GenreOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_TalismanRenovate, ID_LISTIMG_Genre, s_CUI_ID_FRAME_TalismanRenovateID_LISTIMG_GenreOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_TalismanRenovate, ID_LISTIMG_Genre, s_CUI_ID_FRAME_TalismanRenovateID_LISTIMG_GenreOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_TalismanRenovate, ID_LISTIMG_MaterialIcon, s_CUI_ID_FRAME_TalismanRenovateID_LISTIMG_MaterialIconOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_TalismanRenovate, ID_LISTIMG_MaterialIcon, s_CUI_ID_FRAME_TalismanRenovateID_LISTIMG_MaterialIconOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_TalismanRenovate, ID_LISTIMG_MaterialIcon, s_CUI_ID_FRAME_TalismanRenovateID_LISTIMG_MaterialIconOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_TalismanRenovate, ID_LISTIMG_MaterialIcon, s_CUI_ID_FRAME_TalismanRenovateID_LISTIMG_MaterialIconOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_TalismanRenovate, ID_BUTTON_Return, s_CUI_ID_FRAME_TalismanRenovateID_BUTTON_ReturnOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TalismanRenovate, ID_BUTTON_Cancel, s_CUI_ID_FRAME_TalismanRenovateID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TalismanRenovate, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_TalismanRenovateID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TalismanRenovate, ID_BUTTON_HELP, s_CUI_ID_FRAME_TalismanRenovateID_BUTTON_HELPOnButtonClick );

	m_pID_FRAME_TalismanRenovate = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TalismanRenovate );
	m_pID_LISTIMG_TalismanIcon = (ControlListImage*)theUiManager.FindControl( ID_FRAME_TalismanRenovate, ID_LISTIMG_TalismanIcon );
	m_pID_TEXT_TalismanName = (ControlText*)theUiManager.FindControl( ID_FRAME_TalismanRenovate, ID_TEXT_TalismanName );
	m_pID_TEXT_TalismanLv = (ControlText*)theUiManager.FindControl( ID_FRAME_TalismanRenovate, ID_TEXT_TalismanLv );
	m_pID_LISTIMG_Genre = (ControlListImage*)theUiManager.FindControl( ID_FRAME_TalismanRenovate, ID_LISTIMG_Genre );
	m_pID_LISTIMG_MaterialIcon = (ControlListImage*)theUiManager.FindControl( ID_FRAME_TalismanRenovate, ID_LISTIMG_MaterialIcon );
	m_pID_TEXT_MaterialName = (ControlText*)theUiManager.FindControl( ID_FRAME_TalismanRenovate, ID_TEXT_MaterialName );
	m_pID_TEXT_Moment = (ControlText*)theUiManager.FindControl( ID_FRAME_TalismanRenovate, ID_TEXT_Moment );
	m_pID_BUTTON_Return = (ControlButton*)theUiManager.FindControl( ID_FRAME_TalismanRenovate, ID_BUTTON_Return );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_TalismanRenovate, ID_BUTTON_Cancel );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_TalismanRenovate, ID_BUTTON_CLOSE );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_TalismanRenovate, ID_BUTTON_HELP );

	assert( m_pID_FRAME_TalismanRenovate );
	assert( m_pID_LISTIMG_TalismanIcon );
	assert( m_pID_TEXT_TalismanName );
	assert( m_pID_TEXT_TalismanLv );
	assert( m_pID_LISTIMG_Genre );
	assert( m_pID_LISTIMG_MaterialIcon );
	assert( m_pID_TEXT_MaterialName );
	assert( m_pID_TEXT_Moment );
	assert( m_pID_BUTTON_Return );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_HELP );

	SetVisable(false);
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_TalismanRenovate::_UnLoadUI()
{
	m_pID_FRAME_TalismanRenovate = NULL;
	m_pID_LISTIMG_TalismanIcon = NULL;
	m_pID_TEXT_TalismanName = NULL;
	m_pID_TEXT_TalismanLv = NULL;
	m_pID_LISTIMG_Genre = NULL;
	m_pID_LISTIMG_MaterialIcon = NULL;
	m_pID_TEXT_MaterialName = NULL;
	m_pID_TEXT_Moment = NULL;
	m_pID_BUTTON_Return = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\TalismanRenovate.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_TalismanRenovate::_IsVisable()
{
	if ( !m_pID_FRAME_TalismanRenovate )
		return false;
	return m_pID_FRAME_TalismanRenovate->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_TalismanRenovate::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_TalismanRenovate )
		return;

	m_pID_FRAME_TalismanRenovate->SetVisable( bVisable );
}

void CUI_ID_FRAME_TalismanRenovate::UpdateTaliInfo(SCharItem *pItem)
{
	if(!pItem)
		return;

	ItemDefine::SItemCommon *pCommon = GettheItemDetail().GetItemByID(pItem->itembaseinfo.ustItemID);
	if(!pCommon)
		return;

	ControlListImage::S_ListImg img;
	img.SetData(pCommon->ustItemID,1);
	m_pID_LISTIMG_TalismanIcon->SetItem(&img);

	//法宝名称
	m_pID_TEXT_TalismanName->SetText(pCommon->GetItemName());

	//法宝名称 
	m_pID_TEXT_TalismanLv->SetText(pItem->talismandata.level);
}

void CUI_ID_FRAME_TalismanRenovate::UpdateMaterialInfo(unsigned short usItemId,int nCount)
{
	ItemDefine::SItemCommon *pCommon = GettheItemDetail().GetItemByID(usItemId);
	if(!pCommon)
		return;

	ControlListImage::S_ListImg img;
	img.SetData(usItemId,1);
	m_pID_LISTIMG_MaterialIcon->SetItem(&img);

	m_pID_TEXT_MaterialName->SetText(pCommon->GetItemName());
	m_pID_TEXT_Moment->SetText(nCount);
}