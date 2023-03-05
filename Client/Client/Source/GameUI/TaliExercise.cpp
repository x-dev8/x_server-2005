/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\法宝资源\法宝\法宝\TaliExercise.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "TaliExercise.h"
#include "ItemDetail.h"
#include "Common.h"

CUI_ID_FRAME_TaliExercise s_CUI_ID_FRAME_TaliExercise;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TaliExercise, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TaliExercise, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_1935OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_1935OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_1935OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_1935OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_Material0OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_Material0OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_Material0OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_Material0OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_Material1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_Material1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_Material1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_Material1OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_Material2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_Material2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_Material2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_Material2OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_Material3OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_Material3OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_Material3OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_Material3OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_GenreOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_GenreOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_GenreOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_LISTIMG_GenreOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_BUTTON_ConfirmOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaliExercise, ID_BUTTON_HELPOnButtonClick )
CUI_ID_FRAME_TaliExercise::CUI_ID_FRAME_TaliExercise()
{
	// Member
	m_pID_FRAME_TaliExercise = NULL;
	m_pID_LISTIMG_1935 = NULL;
	m_pID_LISTIMG_Material0 = NULL;
	m_pID_LISTIMG_Material1 = NULL;
	m_pID_LISTIMG_Material2 = NULL;
	m_pID_LISTIMG_Material3 = NULL;
	m_pID_LISTIMG_Genre = NULL;
	m_pID_TEXT_TalismanName = NULL;
	m_pID_TEXT_TalismanLv = NULL;
	m_pID_TEXT_MaterialName0 = NULL;
	m_pID_TEXT_MaterialName1 = NULL;
	m_pID_TEXT_MaterialName2 = NULL;
	m_pID_TEXT_MaterialName3 = NULL;
	m_pID_TEXT_MaterialMoment0 = NULL;
	m_pID_TEXT_MaterialMoment1 = NULL;
	m_pID_TEXT_MaterialMoment2 = NULL;
	m_pID_TEXT_MaterialMoment3 = NULL;
	m_pID_TEXT_Moment = NULL;
	m_pID_TEXT_Probability = NULL;
	m_pID_TEXT_Introduce = NULL;
	m_pID_BUTTON_Confirm = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;

}
// Frame
bool CUI_ID_FRAME_TaliExercise::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_TaliExercise::OnFrameRender()
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_1935OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return false;
}
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_1935OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return false;
}
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_1935OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return false;
}
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_1935OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_Material0OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return false;
}
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_Material0OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return false;
}
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_Material0OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return false;
}
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_Material0OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;

	ItemOnIconDragOut(m_pID_LISTIMG_Material0);
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_Material1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return false;
}
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_Material1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return false;
}
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_Material1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return false;
}
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_Material1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;

	ItemOnIconDragOut(m_pID_LISTIMG_Material1);
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_Material2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return false;
}
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_Material2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return false;
}
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_Material2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return false;
}
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_Material2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;

	ItemOnIconDragOut(m_pID_LISTIMG_Material2);
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_Material3OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;

	return false;
}

bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_Material3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;

	return false;
}

bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_Material3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;

	return false;
}

bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_Material3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;

	ItemOnIconDragOut(m_pID_LISTIMG_Material3);
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_GenreOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return false;
}
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_GenreOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return false;
}
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_GenreOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return false;
}
bool CUI_ID_FRAME_TaliExercise::ID_LISTIMG_GenreOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return false;
}
// Button
bool CUI_ID_FRAME_TaliExercise::ID_BUTTON_ConfirmOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_TaliExercise::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_TaliExercise::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_TaliExercise::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return true;
}

// 装载UI
bool CUI_ID_FRAME_TaliExercise::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TaliExercise.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\TaliExercise.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_TaliExercise::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TaliExercise, s_CUI_ID_FRAME_TaliExerciseOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TaliExercise, s_CUI_ID_FRAME_TaliExerciseOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_TaliExercise, ID_LISTIMG_1935, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_1935OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_TaliExercise, ID_LISTIMG_1935, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_1935OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_TaliExercise, ID_LISTIMG_1935, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_1935OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_TaliExercise, ID_LISTIMG_1935, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_1935OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_TaliExercise, ID_LISTIMG_Material0, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_Material0OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_TaliExercise, ID_LISTIMG_Material0, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_Material0OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_TaliExercise, ID_LISTIMG_Material0, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_Material0OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_TaliExercise, ID_LISTIMG_Material0, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_Material0OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_TaliExercise, ID_LISTIMG_Material1, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_Material1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_TaliExercise, ID_LISTIMG_Material1, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_Material1OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_TaliExercise, ID_LISTIMG_Material1, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_Material1OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_TaliExercise, ID_LISTIMG_Material1, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_Material1OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_TaliExercise, ID_LISTIMG_Material2, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_Material2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_TaliExercise, ID_LISTIMG_Material2, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_Material2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_TaliExercise, ID_LISTIMG_Material2, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_Material2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_TaliExercise, ID_LISTIMG_Material2, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_Material2OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_TaliExercise, ID_LISTIMG_Material3, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_Material3OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_TaliExercise, ID_LISTIMG_Material3, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_Material3OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_TaliExercise, ID_LISTIMG_Material3, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_Material3OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_TaliExercise, ID_LISTIMG_Material3, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_Material3OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_TaliExercise, ID_LISTIMG_Genre, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_GenreOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_TaliExercise, ID_LISTIMG_Genre, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_GenreOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_TaliExercise, ID_LISTIMG_Genre, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_GenreOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_TaliExercise, ID_LISTIMG_Genre, s_CUI_ID_FRAME_TaliExerciseID_LISTIMG_GenreOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_TaliExercise, ID_BUTTON_Confirm, s_CUI_ID_FRAME_TaliExerciseID_BUTTON_ConfirmOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TaliExercise, ID_BUTTON_Cancel, s_CUI_ID_FRAME_TaliExerciseID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TaliExercise, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_TaliExerciseID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TaliExercise, ID_BUTTON_HELP, s_CUI_ID_FRAME_TaliExerciseID_BUTTON_HELPOnButtonClick );

	m_pID_FRAME_TaliExercise = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TaliExercise );
	m_pID_LISTIMG_1935 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_LISTIMG_1935 );
	m_pID_LISTIMG_Material0 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_LISTIMG_Material0 );
	m_pID_LISTIMG_Material1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_LISTIMG_Material1 );
	m_pID_LISTIMG_Material2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_LISTIMG_Material2 );
	m_pID_LISTIMG_Material3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_LISTIMG_Material3 );
	m_pID_LISTIMG_Genre = (ControlListImage*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_LISTIMG_Genre );
	m_pID_TEXT_TalismanName = (ControlText*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_TEXT_TalismanName );
	m_pID_TEXT_TalismanLv = (ControlText*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_TEXT_TalismanLv );
	m_pID_TEXT_MaterialName0 = (ControlText*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_TEXT_MaterialName0 );
	m_pID_TEXT_MaterialName1 = (ControlText*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_TEXT_MaterialName1 );
	m_pID_TEXT_MaterialName2 = (ControlText*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_TEXT_MaterialName2 );
	m_pID_TEXT_MaterialName3 = (ControlText*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_TEXT_MaterialName3 );
	m_pID_TEXT_MaterialMoment0 = (ControlText*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_TEXT_MaterialMoment0 );
	m_pID_TEXT_MaterialMoment1 = (ControlText*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_TEXT_MaterialMoment1 );
	m_pID_TEXT_MaterialMoment2 = (ControlText*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_TEXT_MaterialMoment2 );
	m_pID_TEXT_MaterialMoment3 = (ControlText*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_TEXT_MaterialMoment3 );
	m_pID_TEXT_Moment = (ControlText*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_TEXT_Moment );
	m_pID_TEXT_Probability = (ControlText*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_TEXT_Probability );
	m_pID_TEXT_Introduce = (ControlText*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_TEXT_Introduce );
	m_pID_BUTTON_Confirm = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_BUTTON_Confirm );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_BUTTON_Cancel );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_BUTTON_CLOSE );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaliExercise, ID_BUTTON_HELP );

	assert( m_pID_FRAME_TaliExercise );
	assert( m_pID_LISTIMG_1935 );
	assert( m_pID_LISTIMG_Material0 );
	assert( m_pID_LISTIMG_Material1 );
	assert( m_pID_LISTIMG_Material2 );
	assert( m_pID_LISTIMG_Material3 );
	assert( m_pID_LISTIMG_Genre );
	assert( m_pID_TEXT_TalismanName );
	assert( m_pID_TEXT_TalismanLv );
	assert( m_pID_TEXT_MaterialName0 );
	assert( m_pID_TEXT_MaterialName1 );
	assert( m_pID_TEXT_MaterialName2 );
	assert( m_pID_TEXT_MaterialName3 );
	assert( m_pID_TEXT_MaterialMoment0 );
	assert( m_pID_TEXT_MaterialMoment1 );
	assert( m_pID_TEXT_MaterialMoment2 );
	assert( m_pID_TEXT_MaterialMoment3 );
	assert( m_pID_TEXT_Moment );
	assert( m_pID_TEXT_Probability );
	assert( m_pID_TEXT_Introduce );
	assert( m_pID_BUTTON_Confirm );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_HELP );

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_TaliExercise::_UnLoadUI()
{
	m_pID_FRAME_TaliExercise = NULL;
	m_pID_LISTIMG_1935 = NULL;
	m_pID_LISTIMG_Material0 = NULL;
	m_pID_LISTIMG_Material1 = NULL;
	m_pID_LISTIMG_Material2 = NULL;
	m_pID_LISTIMG_Material3 = NULL;
	m_pID_LISTIMG_Genre = NULL;
	m_pID_TEXT_TalismanName = NULL;
	m_pID_TEXT_TalismanLv = NULL;
	m_pID_TEXT_MaterialName0 = NULL;
	m_pID_TEXT_MaterialName1 = NULL;
	m_pID_TEXT_MaterialName2 = NULL;
	m_pID_TEXT_MaterialName3 = NULL;
	m_pID_TEXT_MaterialMoment0 = NULL;
	m_pID_TEXT_MaterialMoment1 = NULL;
	m_pID_TEXT_MaterialMoment2 = NULL;
	m_pID_TEXT_MaterialMoment3 = NULL;
	m_pID_TEXT_Moment = NULL;
	m_pID_TEXT_Probability = NULL;
	m_pID_TEXT_Introduce = NULL;
	m_pID_BUTTON_Confirm = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\TaliExercise.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_TaliExercise::_IsVisable()
{
	if ( !m_pID_FRAME_TaliExercise )
		return false;
	return m_pID_FRAME_TaliExercise->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_TaliExercise::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_TaliExercise )
		return;

	m_pID_FRAME_TaliExercise->SetVisable( bVisable );
}

bool CUI_ID_FRAME_TaliExercise::ItemOnIconDragOn(ControlListImage *pImg,ControlIconDrag::S_ListImg* pItemDrag,int nCount /*= 1*/)
{
	if(!pImg || !pItemDrag)
		return false;

	pImg->Clear();
	pImg->SetItem(pItemDrag,0);
	pImg->GetItemByIndex(0)->m_pkIconInfo->Count() = nCount;
	pImg->GetItemByIndex(0)->m_eEnable         = eIcon_Enable;

	return false;
}

bool CUI_ID_FRAME_TaliExercise::ItemOnIconDragOut(ControlListImage* pImg)
{
	if(!pImg)
	  return false;

	pImg->Clear();
	return true;
}

void CUI_ID_FRAME_TaliExercise::UpdateTaliInfo(SCharItem *pItem)
{
	if(!pItem)
		return;

	ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID(pItem->itembaseinfo.ustItemID);
	if(!pItemCommon)
		return;

	m_pID_TEXT_TalismanName->SetText(pItemCommon->GetItemName());

	char szInfo[256] = {0};
	MeSprintf_s(szInfo,sizeof(szInfo),"法宝等级:%d",pItem->talismandata.level);
	m_pID_TEXT_TalismanLv->SetText(szInfo);

	ControlListImage::S_ListImg img;
	img.SetData(pItemCommon->ustItemID,1);
	m_pID_LISTIMG_1935->SetItem(&img);
}

void CUI_ID_FRAME_TaliExercise::UpdateTaliMaterialInfo(ControlListImage::S_ListImg *pImg,ControlText* pTexName,ControlText* pTexCount)
{
	if(!pImg || !pTexCount || !pTexName)
		return;

	ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID(pImg->m_pkIconInfo->Id());
	if(!pItemCommon)
		return;

	pTexName->SetText(pItemCommon->GetItemName());

	pTexCount->SetText(pImg->m_pkIconInfo->Count());
}

void CUI_ID_FRAME_TaliExercise::UpdateOtherInfo(SCharItem *pItem)
{
	if(!pItem)
		return;

}
