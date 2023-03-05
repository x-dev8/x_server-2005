/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (6)\CorpsTask.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"

#include "GlobalDef.h"
#include "PlayerRole.h"
#include "ui/Pack.h"
#include "ui/NpcTaskDialogBox.h"
#include "NetworkInput.h"


#include "CorpsTask.h"

CUI_ID_FRAME_CorpsTask s_CUI_ID_FRAME_CorpsTask;
MAP_FRAME_RUN( s_CUI_ID_FRAME_CorpsTask, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CorpsTask, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CorpsTask, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CorpsTask, ID_BUTTON_TrueOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CorpsTask, ID_BUTTON_CancelOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_CorpsTask, ID_LISTIMG_IconOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_CorpsTask, ID_LISTIMG_IconOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CorpsTask, ID_LISTIMG_IconOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_CorpsTask, ID_LISTIMG_IconOnIconRButtonUp )
CUI_ID_FRAME_CorpsTask::CUI_ID_FRAME_CorpsTask()
{
	// Member
	m_pID_FRAME_CorpsTask = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_True = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_LISTIMG_Icon = NULL;

	for ( int i = 0; i < MsgReqDoneQuest::EDoneQuest_CommitItemMax; i ++ )
	{
		m_vtRequestItemUUID.push_back(0);
	}
	m_nQuestID = 0;

}
// Frame
bool CUI_ID_FRAME_CorpsTask::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_CorpsTask::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_CorpsTask::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CorpsTask )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_CorpsTask::ID_BUTTON_TrueOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CorpsTask )
		return false;

	if ( m_vtRequestItemUUID.size() > 0 )
	{
		MsgReqDoneQuest msg;
		//msg.stNpcId = m_nNpcId;
		msg.nQuestId = m_nQuestID;
		for ( int i = 0; i < m_vtRequestItemUUID.size() && i < MsgReqDoneQuest::EDoneQuest_CommitItemMax; i ++ )
		{
			msg.nGuid[i] = m_vtRequestItemUUID[i];
		}
		GettheNetworkInput().SendMsg( &msg );
	}
	this->SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_CorpsTask::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CorpsTask )
		return false;
	this->SetVisable(false);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_CorpsTask::ID_LISTIMG_IconOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_CorpsTask )
		return false;

	if ( s_CUI_ID_FRAME_PACK.IsList(pSender) == false )	//如果不是玩家背包是不能拖到这里的
	{
		return false;
	}
	

	//ItemDefine::SItemCommon *pSrcItemDetail = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->Id() );

	//if( pSrcItemDetail == NULL )
	//	return false;

	ControlListImage* dragListImage = dynamic_cast<ControlListImage*>(pSender);
	if ( dragListImage )
	{
		int nSrcIndex = dragListImage->GetItemIndex( pItemDrag );
		SCharItem scharItem;
		if (thePlayerRole.m_bag.IsHaveItem(nSrcIndex))
		{
			thePlayerRole.m_bag.GetItem( nSrcIndex, &scharItem );
			if ( IsItemAlreadyIn( scharItem.GetItemGuid() ))
			{
				return false;
			}
			
			pItemSrc->SetData(&scharItem);
			ControlListImage* meListImage = dynamic_cast<ControlListImage*>(pMe);
			int idx = meListImage->GetItemIndex(pItemSrc);
			if ( idx >= 0 && idx < MsgReqDoneQuest::EDoneQuest_CommitItemMax )
			{
				m_vtRequestItemUUID[idx] = scharItem.GetItemGuid();
			}
			
			return true;
		}
	}
	return false;
}
bool CUI_ID_FRAME_CorpsTask::ID_LISTIMG_IconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_CorpsTask )
		return false;
	return false;
}
bool CUI_ID_FRAME_CorpsTask::ID_LISTIMG_IconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_CorpsTask )
		return false;
	return false;
}
bool CUI_ID_FRAME_CorpsTask::ID_LISTIMG_IconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_CorpsTask )
		return false;
	return false;
}

// 装载UI
bool CUI_ID_FRAME_CorpsTask::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CorpsTask.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CorpsTask.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_CorpsTask::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_CorpsTask, s_CUI_ID_FRAME_CorpsTaskOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_CorpsTask, s_CUI_ID_FRAME_CorpsTaskOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_CorpsTask, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_CorpsTaskID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CorpsTask, ID_BUTTON_True, s_CUI_ID_FRAME_CorpsTaskID_BUTTON_TrueOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CorpsTask, ID_BUTTON_Cancel, s_CUI_ID_FRAME_CorpsTaskID_BUTTON_CancelOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_CorpsTask, ID_LISTIMG_Icon, s_CUI_ID_FRAME_CorpsTaskID_LISTIMG_IconOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_CorpsTask, ID_LISTIMG_Icon, s_CUI_ID_FRAME_CorpsTaskID_LISTIMG_IconOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_CorpsTask, ID_LISTIMG_Icon, s_CUI_ID_FRAME_CorpsTaskID_LISTIMG_IconOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_CorpsTask, ID_LISTIMG_Icon, s_CUI_ID_FRAME_CorpsTaskID_LISTIMG_IconOnIconRButtonUp );

	m_pID_FRAME_CorpsTask = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_CorpsTask );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_CorpsTask, ID_BUTTON_CLOSE );
	m_pID_BUTTON_True = (ControlButton*)theUiManager.FindControl( ID_FRAME_CorpsTask, ID_BUTTON_True );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_CorpsTask, ID_BUTTON_Cancel );
	m_pID_LISTIMG_Icon = (ControlListImage*)theUiManager.FindControl( ID_FRAME_CorpsTask, ID_LISTIMG_Icon );

	assert( m_pID_FRAME_CorpsTask );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_True );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_LISTIMG_Icon );

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_CorpsTask::_UnLoadUI()
{
	m_pID_FRAME_CorpsTask = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_True = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_LISTIMG_Icon = NULL;
	m_vtRequestItemUUID.clear();
	return theUiManager.RemoveFrame( "Data\\UI\\CorpsTask.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_CorpsTask::_IsVisable()
{
	if ( !m_pID_FRAME_CorpsTask )
		return false;
	return m_pID_FRAME_CorpsTask->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_CorpsTask::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_CorpsTask )
		return ;

	for ( int i = 0; i < MsgReqDoneQuest::EDoneQuest_CommitItemMax; i ++ )
	{
		m_vtRequestItemUUID[i] = 0;
		ControlIconDrag::S_ListImg* pItem = m_pID_LISTIMG_Icon->GetItemByIndex( i );
		pItem->Clear();
	}
	m_nQuestID = 0;

	

	m_pID_FRAME_CorpsTask->SetVisable( bVisable );
	m_nNpcId = s_CUI_NpcTaskDialogBox.GetNpc();
	s_CUI_NpcTaskDialogBox.SetVisable(false);	//关闭刚才打开npc的对话框
	s_CUI_ID_FRAME_PACK.SetVisable(true);
}

void CUI_ID_FRAME_CorpsTask::SetQuestID( short id )
{
	m_nQuestID = id;
}

bool CUI_ID_FRAME_CorpsTask::IsItemAlreadyIn( __int64 uuid )
{
	for ( int i = 0; i < MsgReqDoneQuest::EDoneQuest_CommitItemMax; i ++ )
	{
		if( m_vtRequestItemUUID[i] == uuid )
		{
			return true;
		}
		
	}

	return false;
}