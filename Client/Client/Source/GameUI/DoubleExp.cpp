/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\DoubleExp.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "DoubleExp.h"
#include "ShopCenter.h"
#include "PlayerRole.h"
//#include "MeNetwork.h"
#include "MessageDefine.h"
#include "GlobalDef.h"
#include "NetworkInput.h"
CUI_ID_FRAME_DuobleExp s_CUI_ID_FRAME_DuobleExp;
MAP_FRAME_RUN( s_CUI_ID_FRAME_DuobleExp, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_DuobleExp, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_DuobleExp, ID_LISTIMG_ItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_DuobleExp, ID_LISTIMG_ItemOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_DuobleExp, ID_LISTIMG_ItemOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_DuobleExp, ID_LISTIMG_ItemOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_DuobleExp, ID_BUTTON_BuyOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_DuobleExp, ID_BUTTON_StartOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_DuobleExp, ID_BUTTON_StopOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_DuobleExp, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_DuobleExp, ID_BUTTON_HELPOnButtonClick )
CUI_ID_FRAME_DuobleExp::CUI_ID_FRAME_DuobleExp()
{
	// Member
	m_pID_FRAME_DuobleExp = NULL;
	m_pID_PICTURE_System = NULL;
	m_pID_PICTURE_Item1 = NULL;
	m_pID_PICTURE_Total = NULL;
	m_pID_PICTURE_Item2 = NULL;
	m_pID_PICTURE_Icon = NULL;
	m_pID_PICTURE_NumBg1 = NULL;
	m_pID_PICTURE_NumBg2 = NULL;
	m_pID_PICTURE_NumBg3 = NULL;
	m_pID_PICTURE_Minute1 = NULL;
	m_pID_PICTURE_Minute2 = NULL;
	m_pID_PICTURE_Minute3 = NULL;
	m_pID_TEXT_Tip = NULL;
	m_pID_TEXT_Time1 = NULL;
	m_pID_TEXT_Time2 = NULL;
	m_pID_TEXT_Time3 = NULL;
	m_pID_LISTIMG_Item = NULL;
	m_pID_BUTTON_Buy = NULL;
	m_pID_BUTTON_Start = NULL;
	m_pID_BUTTON_Stop = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;

	nLastRefreshTime = 0;
	nLastUIUpdateTime = 0;

}
// Frame
bool CUI_ID_FRAME_DuobleExp::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	if( IsVisable() && m_bState)
	{
		DWORD dThisTime = HQ_TimeGetTime();
		if(dThisTime - nLastUIUpdateTime > 60000)
		{
			nLastUIUpdateTime = dThisTime;
			RefreshDoubleExp();
		}
	}
	return true;
}
bool CUI_ID_FRAME_DuobleExp::OnFrameRender()
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_DuobleExp::ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_DuobleExp )
		return false;
	return false;
}
bool CUI_ID_FRAME_DuobleExp::ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_DuobleExp )
		return false;
	return false;
}
bool CUI_ID_FRAME_DuobleExp::ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_DuobleExp )
		return false;
	return false;
}
bool CUI_ID_FRAME_DuobleExp::ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_DuobleExp )
		return false;
	return false;
}
// Button
bool CUI_ID_FRAME_DuobleExp::ID_BUTTON_BuyOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_DuobleExp )
		return false;
// 	s_CUI_ID_FRAME_ShopCenter.SetVisable(true);
	return true;
}
// Button
bool CUI_ID_FRAME_DuobleExp::ID_BUTTON_StartOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_DuobleExp )
		return false;
	MsgReqDoubleExp doubleExp;
	doubleExp.bState = true;
	GettheNetworkInput().SendMsg( &doubleExp );
	return true;
}
// Button
bool CUI_ID_FRAME_DuobleExp::ID_BUTTON_StopOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_DuobleExp )
		return false;
	MsgReqDoubleExp doubleExp;
	doubleExp.bState = false;
	GettheNetworkInput().SendMsg( &doubleExp );
	return true;
}
// Button
bool CUI_ID_FRAME_DuobleExp::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_DuobleExp )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_DuobleExp::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_DuobleExp )
		return false;
	return true;
}

// 装载UI
bool CUI_ID_FRAME_DuobleExp::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\DoubleExp.MEUI" ,false,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\DoubleExp.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_DuobleExp::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_DuobleExp, s_CUI_ID_FRAME_DuobleExpOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_DuobleExp, s_CUI_ID_FRAME_DuobleExpOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_DuobleExp, ID_LISTIMG_Item, s_CUI_ID_FRAME_DuobleExpID_LISTIMG_ItemOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_DuobleExp, ID_LISTIMG_Item, s_CUI_ID_FRAME_DuobleExpID_LISTIMG_ItemOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_DuobleExp, ID_LISTIMG_Item, s_CUI_ID_FRAME_DuobleExpID_LISTIMG_ItemOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_DuobleExp, ID_LISTIMG_Item, s_CUI_ID_FRAME_DuobleExpID_LISTIMG_ItemOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_DuobleExp, ID_BUTTON_Buy, s_CUI_ID_FRAME_DuobleExpID_BUTTON_BuyOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_DuobleExp, ID_BUTTON_Start, s_CUI_ID_FRAME_DuobleExpID_BUTTON_StartOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_DuobleExp, ID_BUTTON_Stop, s_CUI_ID_FRAME_DuobleExpID_BUTTON_StopOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_DuobleExp, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_DuobleExpID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_DuobleExp, ID_BUTTON_HELP, s_CUI_ID_FRAME_DuobleExpID_BUTTON_HELPOnButtonClick );

	m_pID_FRAME_DuobleExp = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_DuobleExp );
	m_pID_PICTURE_System = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_PICTURE_System );
	m_pID_PICTURE_Item1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_PICTURE_Item1 );
	m_pID_PICTURE_Total = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_PICTURE_Total );
	m_pID_PICTURE_Item2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_PICTURE_Item2 );
	m_pID_PICTURE_Icon = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_PICTURE_Icon );
	m_pID_PICTURE_NumBg1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_PICTURE_NumBg1 );
	m_pID_PICTURE_NumBg2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_PICTURE_NumBg2 );
	m_pID_PICTURE_NumBg3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_PICTURE_NumBg3 );
	m_pID_PICTURE_Minute1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_PICTURE_Minute1 );
	m_pID_PICTURE_Minute2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_PICTURE_Minute2 );
	m_pID_PICTURE_Minute3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_PICTURE_Minute3 );
	m_pID_TEXT_Tip = (ControlText*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_TEXT_Tip );
	m_pID_TEXT_Time1 = (ControlText*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_TEXT_Time1 );
	m_pID_TEXT_Time2 = (ControlText*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_TEXT_Time2 );
	m_pID_TEXT_Time3 = (ControlText*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_TEXT_Time3 );
	m_pID_LISTIMG_Item = (ControlListImage*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_LISTIMG_Item );
	m_pID_BUTTON_Buy = (ControlButton*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_BUTTON_Buy );
	m_pID_BUTTON_Start = (ControlButton*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_BUTTON_Start );
	m_pID_BUTTON_Stop = (ControlButton*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_BUTTON_Stop );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_BUTTON_CLOSE );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_DuobleExp, ID_BUTTON_HELP );

	assert( m_pID_FRAME_DuobleExp );
	assert( m_pID_PICTURE_System );
	assert( m_pID_PICTURE_Item1 );
	assert( m_pID_PICTURE_Total );
	assert( m_pID_PICTURE_Item2 );
	assert( m_pID_PICTURE_Icon );
	assert( m_pID_PICTURE_NumBg1 );
	assert( m_pID_PICTURE_NumBg2 );
	assert( m_pID_PICTURE_NumBg3 );
	assert( m_pID_PICTURE_Minute1 );
	assert( m_pID_PICTURE_Minute2 );
	assert( m_pID_PICTURE_Minute3 );
	assert( m_pID_TEXT_Tip );
	assert( m_pID_TEXT_Time1 );
	assert( m_pID_TEXT_Time2 );
	assert( m_pID_TEXT_Time3 );
	assert( m_pID_LISTIMG_Item );
	assert( m_pID_BUTTON_Buy );
	assert( m_pID_BUTTON_Start );
	assert( m_pID_BUTTON_Stop );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_HELP );

	m_pID_LISTIMG_Item->SetEnableDrag(false);
	ControlIconDrag::S_ListImg ImgItem;
	ImgItem.SetData(6400,1,eIcon_Enable,false,eTipFlag_Normal);
	m_pID_LISTIMG_Item->SetItem(&ImgItem,0);

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_DuobleExp::_UnLoadUI()
{
	m_pID_FRAME_DuobleExp = NULL;
	m_pID_PICTURE_System = NULL;
	m_pID_PICTURE_Item1 = NULL;
	m_pID_PICTURE_Total = NULL;
	m_pID_PICTURE_Item2 = NULL;
	m_pID_PICTURE_Icon = NULL;
	m_pID_PICTURE_NumBg1 = NULL;
	m_pID_PICTURE_NumBg2 = NULL;
	m_pID_PICTURE_NumBg3 = NULL;
	m_pID_PICTURE_Minute1 = NULL;
	m_pID_PICTURE_Minute2 = NULL;
	m_pID_PICTURE_Minute3 = NULL;
	m_pID_TEXT_Tip = NULL;
	m_pID_TEXT_Time1 = NULL;
	m_pID_TEXT_Time2 = NULL;
	m_pID_TEXT_Time3 = NULL;
	m_pID_LISTIMG_Item = NULL;
	m_pID_BUTTON_Buy = NULL;
	m_pID_BUTTON_Start = NULL;
	m_pID_BUTTON_Stop = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\DoubleExp.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_DuobleExp::_IsVisable()
{
	if ( !m_pID_FRAME_DuobleExp )
		return false;
	return m_pID_FRAME_DuobleExp->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_DuobleExp::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_DuobleExp )
		return ;
	m_pID_FRAME_DuobleExp->SetVisable( bVisable );
	if (bVisable)
	{
		nLastUIUpdateTime = HQ_TimeGetTime();
		RefreshDoubleExp();
	}
	
}

void CUI_ID_FRAME_DuobleExp::OnMsgDoubleExp( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgDoubleExpAck );
	MsgDoubleExpAck* pDoubleExpMsg = ( MsgDoubleExpAck* )pMsg;
	if( !pDoubleExpMsg )
		return;
	m_bState = pDoubleExpMsg->bState;
	thePlayerRole.m_charinfo.baseinfo.liveinfo.nSysDoubleExpTime = pDoubleExpMsg->nSysDoubleExpTime;
	thePlayerRole.m_charinfo.baseinfo.liveinfo.nItemDoubleExpTime = pDoubleExpMsg->nItemDoubleExpTime;
	nLastRefreshTime = HQ_TimeGetTime();
	nLastUIUpdateTime = nLastRefreshTime;
	RefreshDoubleExp();
}

void CUI_ID_FRAME_DuobleExp::RefreshDoubleExp()
{
	if (!IsUILoad())
	{
		return;
	}
	
	m_pID_BUTTON_Start->SetVisable(false);
	m_pID_BUTTON_Stop->SetVisable(false);
	uint32 nDeltaTime = 0;
	if (m_bState)
	{
		m_pID_BUTTON_Stop->SetVisable(true);
		nDeltaTime = HQ_TimeGetTime() - nLastRefreshTime;
	}
	else
	{
		m_pID_BUTTON_Start->SetVisable(true);
		if (thePlayerRole.m_charinfo.baseinfo.liveinfo.nSysDoubleExpTime == 0 && thePlayerRole.m_charinfo.baseinfo.liveinfo.nItemDoubleExpTime == 0)
		{
			m_pID_BUTTON_Start->SetEnable(false);
		}
		else
		{
			m_pID_BUTTON_Start->SetEnable(true);
		}
		
	}
	uint32 nSysDoubleExpMinute = 0;
	uint32 nItemDoubleExpMinute = 0;
	if (thePlayerRole.m_charinfo.baseinfo.liveinfo.nSysDoubleExpTime != 0)
	{
		if (thePlayerRole.m_charinfo.baseinfo.liveinfo.nSysDoubleExpTime > nDeltaTime)
		{
			nSysDoubleExpMinute = (thePlayerRole.m_charinfo.baseinfo.liveinfo.nSysDoubleExpTime - nDeltaTime)/60000;
			nItemDoubleExpMinute = thePlayerRole.m_charinfo.baseinfo.liveinfo.nItemDoubleExpTime/60000;
		}
		else
		{
			nDeltaTime -= thePlayerRole.m_charinfo.baseinfo.liveinfo.nSysDoubleExpTime;
			nItemDoubleExpMinute = (thePlayerRole.m_charinfo.baseinfo.liveinfo.nItemDoubleExpTime - nDeltaTime)/60000;
		}		
	}
	else
	{
		if (thePlayerRole.m_charinfo.baseinfo.liveinfo.nItemDoubleExpTime > nDeltaTime)
		{
			nItemDoubleExpMinute = (thePlayerRole.m_charinfo.baseinfo.liveinfo.nItemDoubleExpTime - nDeltaTime)/60000;
		}
	}
	
	
	m_pID_TEXT_Time1->SetText(nSysDoubleExpMinute);
	m_pID_TEXT_Time2->SetText(nItemDoubleExpMinute);
	m_pID_TEXT_Time3->SetText(nSysDoubleExpMinute + nItemDoubleExpMinute);
}