/********************************************************************
	Created by UIEditor.exe
	FileName: D:\FullBag(13.10.181)\Data\Ui\ThreeDay.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ThreeDay.h"
#include "ThreeDayConfig.h"
#include "PlayerRole.h"
#include "OnlineReward.h"
#include "ShowThreeDay.h"
#include "NetworkInput.h"
CUI_ID_FRAME_ThreeDay s_CUI_ID_FRAME_ThreeDay;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ThreeDay, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ThreeDay, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ThreeDay, ID_BUTTON_GetAwardOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ThreeDay, ID_BUTTON_CLOSEOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_ThreeDay, ID_LISTIMG_20626OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_ThreeDay, ID_LISTIMG_20626OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ThreeDay, ID_LISTIMG_20626OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_ThreeDay, ID_LISTIMG_20626OnIconRButtonUp )
CUI_ID_FRAME_ThreeDay::CUI_ID_FRAME_ThreeDay()
{
	// Member
	m_pID_FRAME_ThreeDay = NULL;
	m_pID_BUTTON_GetAward = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_LISTIMG_20626 = NULL;
}
// Frame
bool CUI_ID_FRAME_ThreeDay::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_ThreeDay::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_ThreeDay::ID_BUTTON_GetAwardOnButtonClick( ControlObject* pSender )
{
	//领取物品
	//发送命令道服务器端 领取物品
	MsgGetThreeDayItem msg;
	GettheNetworkInput().SendMsg(&msg);
	SetVisable(false);
	s_CUI_ID_FRAME_ShowThreeDay.SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_ThreeDay::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_ThreeDay::ID_LISTIMG_20626OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_ThreeDay::ID_LISTIMG_20626OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ThreeDay::ID_LISTIMG_20626OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ThreeDay::ID_LISTIMG_20626OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// 装载UI
bool CUI_ID_FRAME_ThreeDay::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ThreeDay.meui",true,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ThreeDay.meui]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ThreeDay::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ThreeDay, s_CUI_ID_FRAME_ThreeDayOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ThreeDay, s_CUI_ID_FRAME_ThreeDayOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ThreeDay, ID_BUTTON_GetAward, s_CUI_ID_FRAME_ThreeDayID_BUTTON_GetAwardOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ThreeDay, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_ThreeDayID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_ThreeDay, ID_LISTIMG_20626, s_CUI_ID_FRAME_ThreeDayID_LISTIMG_20626OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_ThreeDay, ID_LISTIMG_20626, s_CUI_ID_FRAME_ThreeDayID_LISTIMG_20626OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_ThreeDay, ID_LISTIMG_20626, s_CUI_ID_FRAME_ThreeDayID_LISTIMG_20626OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_ThreeDay, ID_LISTIMG_20626, s_CUI_ID_FRAME_ThreeDayID_LISTIMG_20626OnIconRButtonUp );

	m_pID_FRAME_ThreeDay = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ThreeDay );
	m_pID_BUTTON_GetAward = (ControlButton*)theUiManager.FindControl( ID_FRAME_ThreeDay, ID_BUTTON_GetAward );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_ThreeDay, ID_BUTTON_CLOSE );
	m_pID_LISTIMG_20626 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ThreeDay, ID_LISTIMG_20626 );
	assert( m_pID_FRAME_ThreeDay );
	assert( m_pID_BUTTON_GetAward );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_LISTIMG_20626 );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ThreeDay::_UnLoadUI()
{
	m_pID_FRAME_ThreeDay = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\ThreeDay.meui" );
}
// 是否可视
bool CUI_ID_FRAME_ThreeDay::_IsVisable()
{
	return m_pID_FRAME_ThreeDay->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ThreeDay::_SetVisable( const bool bVisable )
{
	if(bVisable)
		OnShow();
	m_pID_FRAME_ThreeDay->SetVisable( bVisable );
}
void CUI_ID_FRAME_ThreeDay::OnShow()
{
	//当UI进行显示的时候
	//1.清空UI上全部的数据
	if(!m_pID_FRAME_ThreeDay)
		return;
	m_pID_LISTIMG_20626->Clear();
	m_pID_BUTTON_GetAward->SetEnable(false);
	//2.判断需要设置的数据
	if(thePlayerRole.GetCharInfo2().otherdataclient.nThreeDayVision != ThreeDayConfig::Instance().GetVision())
		return;//奖励的版本不正确
	const ThreeDayOnce* pInfo = ThreeDayConfig::Instance().GetNowDayThreeDayOnceInfo();
	if(!pInfo)
		return;//今天在线无奖励
	//今天有奖励
	if(thePlayerRole.GetCharInfo2().otherdataclient.nThreeDayValue & pInfo->nValue)
		return;//已经领取奖励了
	//判断在线时间
	unsigned int OnLineTime = COnlineReward::Instance().GetOnlineTime();
	if(OnLineTime< ThreeDayConfig::Instance().GetWriteTime())
		return;
	//现在玩家可以领取奖励了
	unsigned int ItemID = pInfo->nItemID;
	unsigned int ItemSum = pInfo->nItemSum;
	//设置到UI上面去 
	ControlIconDrag::S_ListImg stItem;
	stItem.SetData( ItemID, ItemSum );
	m_pID_LISTIMG_20626->SetItem( &stItem );
	m_pID_BUTTON_GetAward->SetEnable(true);
}