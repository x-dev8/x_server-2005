/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\ActivityMonthList(1).cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ActivityMonthList.h"
#include "ActivityList.h"
#include "PlayerRole.h"
#include "GameMain.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "MeUi/ExpressionManager.h"
#include "CrossMapPF.h"
#include "MeTerrain/stdafx.h"
#include "../color_config.h"
#include "XmlStringLanguage.h"
#include "Common.h"
#include "ui/ActivityDay.h"

CUI_ID_FRAME_ActivityMonthList s_CUI_ID_FRAME_ActivityMonthList;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ActivityMonthList, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ActivityMonthList, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityMonthList, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityMonthList, ID_BUTTON_HelpOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_ActivityMonthList, ID_LISTIMG_EncouragementOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityMonthList, ID_LISTIMG_EncouragementOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityMonthList, ID_LISTIMG_EncouragementOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_ActivityMonthList, ID_LISTIMG_EncouragementOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_ActivityMonthList, ID_LISTIMG_OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityMonthList, ID_LISTIMG_OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityMonthList, ID_LISTIMG_OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_ActivityMonthList, ID_LISTIMG_OnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityMonthList, ID_BUTTON_DayOnButtonClick )
CUI_ID_FRAME_ActivityMonthList::CUI_ID_FRAME_ActivityMonthList()
{
	// Member
	m_pID_FRAME_ActivityMonthList = NULL;
	m_pID_PICTURE_TitleDi = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_PICTURE_TitleLeftMiddle = NULL;
	m_pID_PICTURE_TitleRightMiddle = NULL;
	m_pID_PICTURE_TitleLeft = NULL;
	m_pID_PICTURE_TitleRight = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Help = NULL;
	m_pID_TEXT_TimeZ = NULL;
	m_pID_PICTURE_Wall2 = NULL;
	m_pID_TEXT_ActivityNameZ = NULL;
	m_pID_TEXT_PlayerLvlZ = NULL;
	m_pID_TEXT_ActivityTimeZ = NULL;
	m_pID_TEXT_ActivityNpcZ = NULL;
	m_pID_TEXT_ActivityInfo = NULL;
	m_pID_TEXT_ActivityInfoZ = NULL;
	m_pID_TEXT_Encouragement = NULL;
	m_pID_LISTIMG_Encouragement = NULL;
	m_pID_TEXT_ActivityName = NULL;
	m_pID_TEXT_PlayerLvl = NULL;
	m_pID_TEXT_ActivityTime = NULL;
	m_pID_TEXT_ActivityNpc = NULL;
	m_pID_TEXT_Time = NULL;
	m_pID_TEXT_Choose = NULL;
	m_pID_TEXT_Word = NULL;
	m_pID_PICTURE_Wall = NULL;
	m_pID_TEXT_Monday1 = NULL;
	m_pID_TEXT_Tuesday1 = NULL;
	m_pID_TEXT_Wednesday1 = NULL;
	m_pID_TEXT_Thursday1 = NULL;
	m_pID_TEXT_Friday1 = NULL;
	m_pID_TEXT_Saturday1 = NULL;
	m_pID_TEXT_Sunday1 = NULL;
	m_pID_TEXT_Monday2 = NULL;
	m_pID_TEXT_Monday3 = NULL;
	m_pID_TEXT_Monday4 = NULL;
	m_pID_TEXT_Monday5 = NULL;
	m_pID_TEXT_Monday6 = NULL;
	m_pID_TEXT_Tuesday2 = NULL;
	m_pID_TEXT_Tuesday3 = NULL;
	m_pID_TEXT_Tuesday4 = NULL;
	m_pID_TEXT_Tuesday5 = NULL;
	m_pID_TEXT_Tuesday6 = NULL;
	m_pID_TEXT_Wednesday2 = NULL;
	m_pID_TEXT_Wednesday3 = NULL;
	m_pID_TEXT_Wednesday4 = NULL;
	m_pID_TEXT_Wednesday5 = NULL;
	m_pID_TEXT_Wednesday6 = NULL;
	m_pID_TEXT_Thursday2 = NULL;
	m_pID_TEXT_Thursday3 = NULL;
	m_pID_TEXT_Thursday4 = NULL;
	m_pID_TEXT_Thursday5 = NULL;
	m_pID_TEXT_Thursday6 = NULL;
	m_pID_TEXT_Friday2 = NULL;
	m_pID_TEXT_Friday3 = NULL;
	m_pID_TEXT_Friday4 = NULL;
	m_pID_TEXT_Friday5 = NULL;
	m_pID_TEXT_Friday6 = NULL;
	m_pID_TEXT_Saturday2 = NULL;
	m_pID_TEXT_Saturday3 = NULL;
	m_pID_TEXT_Saturday4 = NULL;
	m_pID_TEXT_Saturday5 = NULL;
	m_pID_TEXT_Saturday6 = NULL;
	m_pID_TEXT_Sunday2 = NULL;
	m_pID_TEXT_Sunday3 = NULL;
	m_pID_TEXT_Sunday4 = NULL;
	m_pID_TEXT_Sunday5 = NULL;
	m_pID_TEXT_Sunday6 = NULL;
	m_pID_LISTIMG_Monday1 = NULL;
	m_pID_LISTIMG_Tuesday1 = NULL;
	m_pID_LISTIMG_Wednesday1 = NULL;
	m_pID_LISTIMG_Thursday1 = NULL;
	m_pID_LISTIMG_Friday1 = NULL;
	m_pID_LISTIMG_Saturday1 = NULL;
	m_pID_LISTIMG_Sunday1 = NULL;
	m_pID_LISTIMG_Monday2 = NULL;
	m_pID_LISTIMG_Monday3 = NULL;
	m_pID_LISTIMG_Monday4 = NULL;
	m_pID_LISTIMG_Monday5 = NULL;
	m_pID_LISTIMG_Monday6 = NULL;
	m_pID_LISTIMG_Tuesday2 = NULL;
	m_pID_LISTIMG_Tuesday3 = NULL;
	m_pID_LISTIMG_Tuesday4 = NULL;
	m_pID_LISTIMG_Tuesday5 = NULL;
	m_pID_LISTIMG_Tuesday6 = NULL;
	m_pID_LISTIMG_Wednesday2 = NULL;
	m_pID_LISTIMG_Wednesday3 = NULL;
	m_pID_LISTIMG_Wednesday4 = NULL;
	m_pID_LISTIMG_Wednesday5 = NULL;
	m_pID_LISTIMG_Wednesday6 = NULL;
	m_pID_LISTIMG_Thursday2 = NULL;
	m_pID_LISTIMG_Thursday3 = NULL;
	m_pID_LISTIMG_Thursday4 = NULL;
	m_pID_LISTIMG_Thursday5 = NULL;
	m_pID_LISTIMG_Thursday6 = NULL;
	m_pID_LISTIMG_Friday2 = NULL;
	m_pID_LISTIMG_Friday3 = NULL;
	m_pID_LISTIMG_Friday4 = NULL;
	m_pID_LISTIMG_Friday5 = NULL;
	m_pID_LISTIMG_Friday6 = NULL;
	m_pID_LISTIMG_Saturday2 = NULL;
	m_pID_LISTIMG_Saturday3 = NULL;
	m_pID_LISTIMG_Saturday4 = NULL;
	m_pID_LISTIMG_Saturday5 = NULL;
	m_pID_LISTIMG_Saturday6 = NULL;
	m_pID_LISTIMG_Sunday2 = NULL;
	m_pID_LISTIMG_Sunday3 = NULL;
	m_pID_LISTIMG_Sunday4 = NULL;
	m_pID_LISTIMG_Sunday5 = NULL;
	m_pID_LISTIMG_Sunday6 = NULL;
	m_pID_PICTURE_Monday = NULL;
	m_pID_PICTURE_Tuesday = NULL;
	m_pID_PICTURE_Wednesday = NULL;
	m_pID_PICTURE_Thursday = NULL;
	m_pID_PICTURE_Friday = NULL;
	m_pID_PICTURE_Saturday = NULL;
	m_pID_PICTURE_Sunday = NULL;
	m_pID_BUTTON_Day = NULL;

}
// Frame
bool CUI_ID_FRAME_ActivityMonthList::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_ActivityMonthList::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_ActivityMonthList::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_ActivityMonthList::ID_BUTTON_HelpOnButtonClick( ControlObject* pSender )
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_ActivityMonthList::ID_LISTIMG_EncouragementOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																		  ControlIconDrag::S_ListImg* pItemDrag,
																		  ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_ActivityMonthList::ID_LISTIMG_EncouragementOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ActivityMonthList::ID_LISTIMG_EncouragementOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ActivityMonthList::ID_LISTIMG_EncouragementOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// Button
bool CUI_ID_FRAME_ActivityMonthList::ID_BUTTON_DayOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);

	//s_CUI_ID_FRAME_ActivityList.SetVisable(true);
	s_CUI_ID_FRAME_ActivityDay.SetVisable(true);

	return true;
}

// 装载UI
bool CUI_ID_FRAME_ActivityMonthList::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ActivityMonthList.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ActivityMonthList.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ActivityMonthList::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ActivityMonthList, s_CUI_ID_FRAME_ActivityMonthListOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ActivityMonthList, s_CUI_ID_FRAME_ActivityMonthListOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ActivityMonthList, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_ActivityMonthListID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityMonthList, ID_BUTTON_Help, s_CUI_ID_FRAME_ActivityMonthListID_BUTTON_HelpOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_ActivityMonthList, ID_LISTIMG_Encouragement, s_CUI_ID_FRAME_ActivityMonthListID_LISTIMG_EncouragementOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_ActivityMonthList, ID_LISTIMG_Encouragement, s_CUI_ID_FRAME_ActivityMonthListID_LISTIMG_EncouragementOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_ActivityMonthList, ID_LISTIMG_Encouragement, s_CUI_ID_FRAME_ActivityMonthListID_LISTIMG_EncouragementOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_ActivityMonthList, ID_LISTIMG_Encouragement, s_CUI_ID_FRAME_ActivityMonthListID_LISTIMG_EncouragementOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_ActivityMonthList, ID_BUTTON_Day, s_CUI_ID_FRAME_ActivityMonthListID_BUTTON_DayOnButtonClick );

	m_pID_FRAME_ActivityMonthList = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ActivityMonthList );
	m_pID_PICTURE_TitleDi = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_PICTURE_TitleDi );
	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Title );
	m_pID_PICTURE_TitleLeftMiddle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_PICTURE_TitleLeftMiddle );
	m_pID_PICTURE_TitleRightMiddle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_PICTURE_TitleRightMiddle );
	m_pID_PICTURE_TitleLeft = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_PICTURE_TitleLeft );
	m_pID_PICTURE_TitleRight = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_PICTURE_TitleRight );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_BUTTON_CLOSE );
	m_pID_BUTTON_Help = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_BUTTON_Help );
	m_pID_TEXT_TimeZ = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_TimeZ );
	m_pID_PICTURE_Wall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_PICTURE_Wall2 );
	m_pID_TEXT_ActivityNameZ = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_ActivityNameZ );
	m_pID_TEXT_PlayerLvlZ = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_PlayerLvlZ );
	m_pID_TEXT_ActivityTimeZ = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_ActivityTimeZ );
	m_pID_TEXT_ActivityNpcZ = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_ActivityNpcZ );
	m_pID_TEXT_ActivityInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_ActivityInfo );
	m_pID_TEXT_ActivityInfoZ = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_ActivityInfoZ );
	m_pID_TEXT_Encouragement = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Encouragement );
	m_pID_LISTIMG_Encouragement = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Encouragement );
	m_pID_TEXT_ActivityName = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_ActivityName );
	m_pID_TEXT_PlayerLvl = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_PlayerLvl );
	m_pID_TEXT_ActivityTime = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_ActivityTime );
	m_pID_TEXT_ActivityNpc = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_ActivityNpc );
	m_pID_TEXT_Time = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Time );
	m_pID_TEXT_Choose = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Choose );
	m_pID_TEXT_Word = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Word );
	m_pID_PICTURE_Wall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_PICTURE_Wall );
	m_pID_TEXT_Monday1 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Monday1 );
	m_pID_TEXT_Tuesday1 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Tuesday1 );
	m_pID_TEXT_Wednesday1 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Wednesday1 );
	m_pID_TEXT_Thursday1 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Thursday1 );
	m_pID_TEXT_Friday1 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Friday1 );
	m_pID_TEXT_Saturday1 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Saturday1 );
	m_pID_TEXT_Sunday1 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Sunday1 );
	m_pID_TEXT_Monday2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Monday2 );
	m_pID_TEXT_Monday3 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Monday3 );
	m_pID_TEXT_Monday4 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Monday4 );
	m_pID_TEXT_Monday5 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Monday5 );
	m_pID_TEXT_Monday6 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Monday6 );
	m_pID_TEXT_Tuesday2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Tuesday2 );
	m_pID_TEXT_Tuesday3 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Tuesday3 );
	m_pID_TEXT_Tuesday4 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Tuesday4 );
	m_pID_TEXT_Tuesday5 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Tuesday5 );
	m_pID_TEXT_Tuesday6 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Tuesday6 );
	m_pID_TEXT_Wednesday2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Wednesday2 );
	m_pID_TEXT_Wednesday3 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Wednesday3 );
	m_pID_TEXT_Wednesday4 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Wednesday4 );
	m_pID_TEXT_Wednesday5 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Wednesday5 );
	m_pID_TEXT_Wednesday6 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Wednesday6 );
	m_pID_TEXT_Thursday2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Thursday2 );
	m_pID_TEXT_Thursday3 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Thursday3 );
	m_pID_TEXT_Thursday4 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Thursday4 );
	m_pID_TEXT_Thursday5 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Thursday5 );
	m_pID_TEXT_Thursday6 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Thursday6 );
	m_pID_TEXT_Friday2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Friday2 );
	m_pID_TEXT_Friday3 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Friday3 );
	m_pID_TEXT_Friday4 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Friday4 );
	m_pID_TEXT_Friday5 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Friday5 );
	m_pID_TEXT_Friday6 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Friday6 );
	m_pID_TEXT_Saturday2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Saturday2 );
	m_pID_TEXT_Saturday3 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Saturday3 );
	m_pID_TEXT_Saturday4 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Saturday4 );
	m_pID_TEXT_Saturday5 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Saturday5 );
	m_pID_TEXT_Saturday6 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Saturday6 );
	m_pID_TEXT_Sunday2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Sunday2 );
	m_pID_TEXT_Sunday3 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Sunday3 );
	m_pID_TEXT_Sunday4 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Sunday4 );
	m_pID_TEXT_Sunday5 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Sunday5 );
	m_pID_TEXT_Sunday6 = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_TEXT_Sunday6 );
	m_pID_LISTIMG_Monday1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Monday1 );
	m_pID_LISTIMG_Tuesday1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Tuesday1 );
	m_pID_LISTIMG_Wednesday1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Wednesday1 );
	m_pID_LISTIMG_Thursday1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Thursday1 );
	m_pID_LISTIMG_Friday1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Friday1 );
	m_pID_LISTIMG_Saturday1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Saturday1 );
	m_pID_LISTIMG_Sunday1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Sunday1 );
	m_pID_LISTIMG_Monday2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Monday2 );
	m_pID_LISTIMG_Monday3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Monday3 );
	m_pID_LISTIMG_Monday4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Monday4 );
	m_pID_LISTIMG_Monday5 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Monday5 );
	m_pID_LISTIMG_Monday6 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Monday6 );
	m_pID_LISTIMG_Tuesday2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Tuesday2 );
	m_pID_LISTIMG_Tuesday3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Tuesday3 );
	m_pID_LISTIMG_Tuesday4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Tuesday4 );
	m_pID_LISTIMG_Tuesday5 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Tuesday5 );
	m_pID_LISTIMG_Tuesday6 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Tuesday6 );
	m_pID_LISTIMG_Wednesday2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Wednesday2 );
	m_pID_LISTIMG_Wednesday3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Wednesday3 );
	m_pID_LISTIMG_Wednesday4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Wednesday4 );
	m_pID_LISTIMG_Wednesday5 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Wednesday5 );
	m_pID_LISTIMG_Wednesday6 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Wednesday6 );
	m_pID_LISTIMG_Thursday2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Thursday2 );
	m_pID_LISTIMG_Thursday3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Thursday3 );
	m_pID_LISTIMG_Thursday4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Thursday4 );
	m_pID_LISTIMG_Thursday5 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Thursday5 );
	m_pID_LISTIMG_Thursday6 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Thursday6 );
	m_pID_LISTIMG_Friday2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Friday2 );
	m_pID_LISTIMG_Friday3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Friday3 );
	m_pID_LISTIMG_Friday4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Friday4 );
	m_pID_LISTIMG_Friday5 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Friday5 );
	m_pID_LISTIMG_Friday6 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Friday6 );
	m_pID_LISTIMG_Saturday2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Saturday2 );
	m_pID_LISTIMG_Saturday3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Saturday3 );
	m_pID_LISTIMG_Saturday4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Saturday4 );
	m_pID_LISTIMG_Saturday5 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Saturday5 );
	m_pID_LISTIMG_Saturday6 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Saturday6 );
	m_pID_LISTIMG_Sunday2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Sunday2 );
	m_pID_LISTIMG_Sunday3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Sunday3 );
	m_pID_LISTIMG_Sunday4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Sunday4 );
	m_pID_LISTIMG_Sunday5 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Sunday5 );
	m_pID_LISTIMG_Sunday6 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_LISTIMG_Sunday6 );
	m_pID_PICTURE_Monday = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_PICTURE_Monday );
	m_pID_PICTURE_Tuesday = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_PICTURE_Tuesday );
	m_pID_PICTURE_Wednesday = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_PICTURE_Wednesday );
	m_pID_PICTURE_Thursday = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_PICTURE_Thursday );
	m_pID_PICTURE_Friday = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_PICTURE_Friday );
	m_pID_PICTURE_Saturday = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_PICTURE_Saturday );
	m_pID_PICTURE_Sunday = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_PICTURE_Sunday );
	m_pID_BUTTON_Day = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, ID_BUTTON_Day );

	InitData();

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ActivityMonthList::_UnLoadUI()
{
	m_pID_FRAME_ActivityMonthList = NULL;
	m_pID_PICTURE_TitleDi = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_PICTURE_TitleLeftMiddle = NULL;
	m_pID_PICTURE_TitleRightMiddle = NULL;
	m_pID_PICTURE_TitleLeft = NULL;
	m_pID_PICTURE_TitleRight = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Help = NULL;
	m_pID_TEXT_TimeZ = NULL;
	m_pID_PICTURE_Wall2 = NULL;
	m_pID_TEXT_ActivityNameZ = NULL;
	m_pID_TEXT_PlayerLvlZ = NULL;
	m_pID_TEXT_ActivityTimeZ = NULL;
	m_pID_TEXT_ActivityNpcZ = NULL;
	m_pID_TEXT_ActivityInfo = NULL;
	m_pID_TEXT_ActivityInfoZ = NULL;
	m_pID_TEXT_Encouragement = NULL;
	m_pID_LISTIMG_Encouragement = NULL;
	m_pID_TEXT_ActivityName = NULL;
	m_pID_TEXT_PlayerLvl = NULL;
	m_pID_TEXT_ActivityTime = NULL;
	m_pID_TEXT_ActivityNpc = NULL;
	m_pID_TEXT_Time = NULL;
	m_pID_TEXT_Choose = NULL;
	m_pID_TEXT_Word = NULL;
	m_pID_PICTURE_Wall = NULL;
	m_pID_TEXT_Monday1 = NULL;
	m_pID_TEXT_Tuesday1 = NULL;
	m_pID_TEXT_Wednesday1 = NULL;
	m_pID_TEXT_Thursday1 = NULL;
	m_pID_TEXT_Friday1 = NULL;
	m_pID_TEXT_Saturday1 = NULL;
	m_pID_TEXT_Sunday1 = NULL;
	m_pID_TEXT_Monday2 = NULL;
	m_pID_TEXT_Monday3 = NULL;
	m_pID_TEXT_Monday4 = NULL;
	m_pID_TEXT_Monday5 = NULL;
	m_pID_TEXT_Monday6 = NULL;
	m_pID_TEXT_Tuesday2 = NULL;
	m_pID_TEXT_Tuesday3 = NULL;
	m_pID_TEXT_Tuesday4 = NULL;
	m_pID_TEXT_Tuesday5 = NULL;
	m_pID_TEXT_Tuesday6 = NULL;
	m_pID_TEXT_Wednesday2 = NULL;
	m_pID_TEXT_Wednesday3 = NULL;
	m_pID_TEXT_Wednesday4 = NULL;
	m_pID_TEXT_Wednesday5 = NULL;
	m_pID_TEXT_Wednesday6 = NULL;
	m_pID_TEXT_Thursday2 = NULL;
	m_pID_TEXT_Thursday3 = NULL;
	m_pID_TEXT_Thursday4 = NULL;
	m_pID_TEXT_Thursday5 = NULL;
	m_pID_TEXT_Thursday6 = NULL;
	m_pID_TEXT_Friday2 = NULL;
	m_pID_TEXT_Friday3 = NULL;
	m_pID_TEXT_Friday4 = NULL;
	m_pID_TEXT_Friday5 = NULL;
	m_pID_TEXT_Friday6 = NULL;
	m_pID_TEXT_Saturday2 = NULL;
	m_pID_TEXT_Saturday3 = NULL;
	m_pID_TEXT_Saturday4 = NULL;
	m_pID_TEXT_Saturday5 = NULL;
	m_pID_TEXT_Saturday6 = NULL;
	m_pID_TEXT_Sunday2 = NULL;
	m_pID_TEXT_Sunday3 = NULL;
	m_pID_TEXT_Sunday4 = NULL;
	m_pID_TEXT_Sunday5 = NULL;
	m_pID_TEXT_Sunday6 = NULL;
	m_pID_LISTIMG_Monday1 = NULL;
	m_pID_LISTIMG_Tuesday1 = NULL;
	m_pID_LISTIMG_Wednesday1 = NULL;
	m_pID_LISTIMG_Thursday1 = NULL;
	m_pID_LISTIMG_Friday1 = NULL;
	m_pID_LISTIMG_Saturday1 = NULL;
	m_pID_LISTIMG_Sunday1 = NULL;
	m_pID_LISTIMG_Monday2 = NULL;
	m_pID_LISTIMG_Monday3 = NULL;
	m_pID_LISTIMG_Monday4 = NULL;
	m_pID_LISTIMG_Monday5 = NULL;
	m_pID_LISTIMG_Monday6 = NULL;
	m_pID_LISTIMG_Tuesday2 = NULL;
	m_pID_LISTIMG_Tuesday3 = NULL;
	m_pID_LISTIMG_Tuesday4 = NULL;
	m_pID_LISTIMG_Tuesday5 = NULL;
	m_pID_LISTIMG_Tuesday6 = NULL;
	m_pID_LISTIMG_Wednesday2 = NULL;
	m_pID_LISTIMG_Wednesday3 = NULL;
	m_pID_LISTIMG_Wednesday4 = NULL;
	m_pID_LISTIMG_Wednesday5 = NULL;
	m_pID_LISTIMG_Wednesday6 = NULL;
	m_pID_LISTIMG_Thursday2 = NULL;
	m_pID_LISTIMG_Thursday3 = NULL;
	m_pID_LISTIMG_Thursday4 = NULL;
	m_pID_LISTIMG_Thursday5 = NULL;
	m_pID_LISTIMG_Thursday6 = NULL;
	m_pID_LISTIMG_Friday2 = NULL;
	m_pID_LISTIMG_Friday3 = NULL;
	m_pID_LISTIMG_Friday4 = NULL;
	m_pID_LISTIMG_Friday5 = NULL;
	m_pID_LISTIMG_Friday6 = NULL;
	m_pID_LISTIMG_Saturday2 = NULL;
	m_pID_LISTIMG_Saturday3 = NULL;
	m_pID_LISTIMG_Saturday4 = NULL;
	m_pID_LISTIMG_Saturday5 = NULL;
	m_pID_LISTIMG_Saturday6 = NULL;
	m_pID_LISTIMG_Sunday2 = NULL;
	m_pID_LISTIMG_Sunday3 = NULL;
	m_pID_LISTIMG_Sunday4 = NULL;
	m_pID_LISTIMG_Sunday5 = NULL;
	m_pID_LISTIMG_Sunday6 = NULL;
	m_pID_PICTURE_Monday = NULL;
	m_pID_PICTURE_Tuesday = NULL;
	m_pID_PICTURE_Wednesday = NULL;
	m_pID_PICTURE_Thursday = NULL;
	m_pID_PICTURE_Friday = NULL;
	m_pID_PICTURE_Saturday = NULL;
	m_pID_PICTURE_Sunday = NULL;
	m_pID_BUTTON_Day = NULL;

	return theUiManager.RemoveFrame( "Data\\UI\\ActivityMonthList.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_ActivityMonthList::_IsVisable()
{
	if(m_pID_FRAME_ActivityMonthList)
		return m_pID_FRAME_ActivityMonthList->IsVisable();

	return false;
}
// 设置是否可视
void CUI_ID_FRAME_ActivityMonthList::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_ActivityMonthList)
		return;

	m_pID_FRAME_ActivityMonthList->SetVisable( bVisable );
	if (bVisable)
	{
		Update();
	}
}

// ListImg / ListEx
bool CUI_ID_FRAME_ActivityMonthList::ID_LISTIMG_OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															 ControlIconDrag::S_ListImg* pItemDrag,
															 ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_ActivityMonthList::ID_LISTIMG_OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (pItem)
	{
		Event* evt = FindEventByIndex(m_mapS_ListImgEventIndex[pItem]);
		if (evt)
		{
			const char* npc = evt->npc.c_str();
			NpcCoord::getInstance()->clickHyberToMiniMap(npc);

			return true;
		}
	}
	return false;
}
bool CUI_ID_FRAME_ActivityMonthList::ID_LISTIMG_OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (pItem)
	{
		SelectChanged(m_mapS_ListImgEventIndex[pItem]);
		return true;
	}
	return false;
}
bool CUI_ID_FRAME_ActivityMonthList::ID_LISTIMG_OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

void CUI_ID_FRAME_ActivityMonthList::InitData()
{
	m_listImages.clear();
	m_texts.clear();
	m_mapS_ListImgEventIndex.clear();

	m_pID_LISTIMG_Encouragement->SetCanbePick(false);
	m_pID_LISTIMG_Encouragement->ShowPressEffect(false);

	char buf[64];
	int index = 1;
	sprintf(buf, "ID_LISTIMG_%d", index);
	ControlListImage* pListImg = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, buf );
	while (pListImg)
	{
		pListImg->ShowPressEffect(false);

		theUiManager.OnIconDragOn( ID_FRAME_ActivityMonthList, buf, s_CUI_ID_FRAME_ActivityMonthListID_LISTIMG_OnIconDragOn );
		theUiManager.OnIconLDBClick( ID_FRAME_ActivityMonthList, buf, s_CUI_ID_FRAME_ActivityMonthListID_LISTIMG_OnIconLDBClick );
		theUiManager.OnIconButtonClick( ID_FRAME_ActivityMonthList, buf, s_CUI_ID_FRAME_ActivityMonthListID_LISTIMG_OnIconButtonClick );
		theUiManager.OnIconRButtonUp( ID_FRAME_ActivityMonthList, buf, s_CUI_ID_FRAME_ActivityMonthListID_LISTIMG_OnIconRButtonUp );

		m_listImages.push_back(pListImg);

		sprintf(buf, "ID_TEXT_%d", index);
		ControlText* pText = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, buf );
		m_texts.push_back(pText);

		++index;
		sprintf(buf, "ID_LISTIMG_%d", index);
		pListImg = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActivityMonthList, buf );
	}

// 	m_pID_TEXT_ActivityNpc->SetHyberClickFun(ID_TEXT_ActivityNpc_HyberClick);
}

void CUI_ID_FRAME_ActivityMonthList::SelectChanged(int selEventIndex)
{
	m_selEventIndex = selEventIndex;

	m_pID_LISTIMG_Encouragement->Clear();
	m_pID_TEXT_ActivityName->SetText("");
	m_pID_TEXT_PlayerLvl->SetText("");
	m_pID_TEXT_ActivityTime->SetText("");
	m_pID_TEXT_ActivityNpc->SetText("");
	m_pID_TEXT_ActivityInfo->SetText("");

	Event* evt = FindEventByIndex(m_selEventIndex);
	if (evt)
	{
		Event& content = *evt;

		m_pID_TEXT_ActivityName->SetText(content.name);

		// level
		char buf[128];
		MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, "%d", content.needLevel);
		if (content.needLevel > thePlayerRole.GetLevel())
			m_pID_TEXT_PlayerLvl->SetText( buf, D3DCOLOR_XRGB(255,0,0) );
		else
			m_pID_TEXT_PlayerLvl->SetText( buf );

		// time
		MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, "%02d:%02d - %02d:%02d", content.hour, content.minute, content.endHour, content.endMinute);
		m_pID_TEXT_ActivityTime->SetText(buf);

		// npc
		std::string npc = content.npc;
		const NpcCoordInfo *pNpcInfo = NpcCoord::getInstance()->/*getNpcCoordInPrimaryMap*/getNpcCoord(content.npcId);
		if (pNpcInfo)
		{
			char cTip[256] = {0};
			CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(pNpcInfo->_mapId);
			if (pTile)
			{
				sprintf(cTip,"%s(%d,%d)",pTile->GetTileName(),(int)pNpcInfo->_pfMapX,(int)pNpcInfo->_pfMapY);
				m_pID_TEXT_ActivityNpc->setTip(cTip);
				m_pID_TEXT_ActivityNpc->setShowTip(true);
			}
		}
		NpcCoord::getInstance()->addNpcHyber(npc);
		m_pID_TEXT_ActivityNpc->SetColUrl(Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)));
		m_pID_TEXT_ActivityNpc->SetText(npc);

		// description
		m_pID_TEXT_ActivityInfo->SetText(content.description);

		for (int i = 0; i < content.rewards.size(); ++i)
		{
			ControlIconDrag::S_ListImg stItem;
			stItem.SetData( content.rewards[i].id, content.rewards[i].count, eIcon_Enable, true );
			m_pID_LISTIMG_Encouragement->SetItem(&stItem);
		}
	}
}

void CUI_ID_FRAME_ActivityMonthList::Update()
{
	for (int i = 0; i < m_listImages.size(); ++i)
	{
		m_listImages[i]->Clear();
	}
	for (int i = 0; i < m_texts.size(); ++i)
	{
		m_texts[i]->Clear();
	}
	
	m_eventContents.clear();

	struct tm nowtime = s_CUI_ID_FRAME_ActivityList.GetNowtime();

	EventManager::Instance().GetMonthEventContents(nowtime, m_eventContents);
	EventContents& contents = m_eventContents;

	// 该月1号是星期几
	int week = HelperFunc::Ymd2Wday(nowtime.tm_year + 1900,
		nowtime.tm_mon + 1,
		1);
	int start = week;
	int lastEvtIndex = 0;

	static int mdays[]={31,28,31,30,31,30,31,31,30,31,30,31};
	int days = mdays[nowtime.tm_mon]; 
	for (int d = 0; d < days; ++d, ++start)
	{
		int day = d + 1;
		m_texts[start]->SetText(day);
		
		while (lastEvtIndex < contents.size())
		{
			const Event& content = contents[lastEvtIndex];
			if (contents[lastEvtIndex].day == day)
			{
				int eventId = content.eventItemId;
				ControlIconDrag::S_ListImg stItem;
				stItem.SetData( eventId, 1, eIcon_Enable, false, eTipFlag_Event );
				int imageItemIndex = m_listImages[start]->GetNullItem();
				m_listImages[start]->SetItem(&stItem);
				m_mapS_ListImgEventIndex[m_listImages[start]->GetItemByIndex(imageItemIndex)] = lastEvtIndex;

				++lastEvtIndex;
			}
			else
			{
				break;
			}
		}
	}

	SelectChanged(-1);
}

Event* CUI_ID_FRAME_ActivityMonthList::FindEventByIndex(int index)
{
	if (index >=0 && index < m_eventContents.size())
		return &m_eventContents[index];
	return 0;
}

void CUI_ID_FRAME_ActivityMonthList::ID_TEXT_ActivityNpc_HyberClick( ControlObject* pSender, const char* szData )
{
	NpcCoord::getInstance()->clickHyberToMiniMap(szData);
}

void CUI_ID_FRAME_ActivityMonthList::SetTextTime(const char* chr)
{
	if(m_pID_TEXT_Time && chr )
		m_pID_TEXT_Time->SetText(chr);
}
