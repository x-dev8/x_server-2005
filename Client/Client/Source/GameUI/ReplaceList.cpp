/********************************************************************
Created by UIEditor.exe
FileName: F:\project\Turbo\Bin\Client\Data\Ui\ReplaceList.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ReplaceList.h"
#include "ui/PrivateShop.h"

CUI_ID_FRAME_ReplaceList s_CUI_ID_FRAME_ReplaceList;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ReplaceList, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ReplaceList, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ReplaceList, ID_LIST_NameOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ReplaceList, ID_BUTTON_UpdateOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ReplaceList, ID_LIST_LvlOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ReplaceList, ID_LIST_PriceOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ReplaceList, ID_LIST_ReplaceOnListSelectChange )
CUI_ID_FRAME_ReplaceList::CUI_ID_FRAME_ReplaceList()
{
	// Member
	m_pID_FRAME_ReplaceList = NULL;
	m_pID_LIST_Name = NULL;
	m_pID_BUTTON_Update = NULL;
	m_pID_LIST_Lvl = NULL;
	m_pID_LIST_Price = NULL;
	m_pID_LIST_Replace = NULL;

}
// Frame
bool CUI_ID_FRAME_ReplaceList::OnFrameRun()
{
	if(!IsVisable() || !s_CUI_ID_FRAME_PrivateShop._IsVisable())
		return true;

	RECT rcMain;
	s_CUI_ID_FRAME_PrivateShop.GetFrame()->GetRealRect(&rcMain);

	RECT rcMe;
	m_pID_FRAME_ReplaceList->GetRealRect(&rcMe);
	int nWidth = rcMe.right - rcMe.left;
	int nHeight = rcMe.bottom - rcMe.top;

	RECT rcNew;
	if (rcMain.left < nWidth)
	{
		rcNew.left = rcMain.right; 
	}
	else
	{
		rcNew.left = rcMain.left - nWidth; 
	}
	rcNew.top = rcMain.top;

	m_pID_FRAME_ReplaceList->SetPos(rcNew.left, rcNew.top);

	return true;
}
bool CUI_ID_FRAME_ReplaceList::OnFrameRender()
{
	return true;
}
// List
void CUI_ID_FRAME_ReplaceList::ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// Button
bool CUI_ID_FRAME_ReplaceList::ID_BUTTON_UpdateOnButtonClick( ControlObject* pSender )
{
	return true;
}
// List
void CUI_ID_FRAME_ReplaceList::ID_LIST_LvlOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_ReplaceList::ID_LIST_PriceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_ReplaceList::ID_LIST_ReplaceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}

// 装载UI
bool CUI_ID_FRAME_ReplaceList::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ReplaceList.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ReplaceList.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ReplaceList::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ReplaceList, s_CUI_ID_FRAME_ReplaceListOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ReplaceList, s_CUI_ID_FRAME_ReplaceListOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_ReplaceList, ID_LIST_Name, s_CUI_ID_FRAME_ReplaceListID_LIST_NameOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_ReplaceList, ID_BUTTON_Update, s_CUI_ID_FRAME_ReplaceListID_BUTTON_UpdateOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_ReplaceList, ID_LIST_Lvl, s_CUI_ID_FRAME_ReplaceListID_LIST_LvlOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_ReplaceList, ID_LIST_Price, s_CUI_ID_FRAME_ReplaceListID_LIST_PriceOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_ReplaceList, ID_LIST_Replace, s_CUI_ID_FRAME_ReplaceListID_LIST_ReplaceOnListSelectChange );

	m_pID_FRAME_ReplaceList = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ReplaceList );
	m_pID_LIST_Name = (ControlList*)theUiManager.FindControl( ID_FRAME_ReplaceList, ID_LIST_Name );
	m_pID_BUTTON_Update = (ControlButton*)theUiManager.FindControl( ID_FRAME_ReplaceList, ID_BUTTON_Update );
	m_pID_LIST_Lvl = (ControlList*)theUiManager.FindControl( ID_FRAME_ReplaceList, ID_LIST_Lvl );
	m_pID_LIST_Price = (ControlList*)theUiManager.FindControl( ID_FRAME_ReplaceList, ID_LIST_Price );
	m_pID_LIST_Replace = (ControlList*)theUiManager.FindControl( ID_FRAME_ReplaceList, ID_LIST_Replace );
	assert( m_pID_FRAME_ReplaceList );
	assert( m_pID_LIST_Name );
	assert( m_pID_BUTTON_Update );
	assert( m_pID_LIST_Lvl );
	assert( m_pID_LIST_Price );
	assert( m_pID_LIST_Replace );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ReplaceList::_UnLoadUI()
{
	m_pID_FRAME_ReplaceList = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\ReplaceList.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_ReplaceList::_IsVisable()
{
	return m_pID_FRAME_ReplaceList->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ReplaceList::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_ReplaceList->SetVisable( bVisable );
}
