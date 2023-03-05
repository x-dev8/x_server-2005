/********************************************************************
Created by UIEditor.exe
FileName: E:\Work\Run\Client\UI\Task_Track.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Task_Track.h"
#include "UIMgr.h"
#include "FuncPerformanceLog.h"
#include "../NpcCoord.h"
#include "Task.h"
#include "QuestManager.h"
#include "ActivityList.h"
#include "FriendDlg.h"
#include "MeTerrain/stdafx.h"
#include "color_config.h"
#include "GameMain.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "SystemConfig.h"
#include "PlayerRole.h"
#include "RbtnMenu.h"
#include "XmlStringLanguage.h"
#include "Target.h"
#include "MiniMap.h"
#include "NpcInfo.h"

CUI_ID_FRAME_TRACK s_CUI_ID_FRAME_TRACK;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TRACK, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TRACK, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TRACK, ID_LIST_TRACKOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TRACK, ID_BUTTON_PlusOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TRACK, ID_BUTTON_SubOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TRACK, ID_BUTTON_AvailableTaskOnButtonClick )
CUI_ID_FRAME_TRACK::CUI_ID_FRAME_TRACK()
{
	ResetMembers();
}

void CUI_ID_FRAME_TRACK::ResetMembers()
{
	m_pID_FRAME_TRACK = NULL;
	m_pID_PICTURE_Drag = NULL;
	m_pID_LIST_TRACK = NULL;
	m_pID_LIST_Finish = NULL;
	m_pID_CHECKBOX_Task = NULL;
    m_pID_BUTTON_Plus = NULL;
    m_pID_BUTTON_Sub = NULL;
	m_nLastNpcMap = -1;
    m_bMinisize = false;
	m_pID_BUTTON_AvailableTask = NULL;
}

ControlList* CUI_ID_FRAME_TRACK::GetLIST_TRACK()
{
	if( !m_pID_FRAME_TRACK )
		return NULL;
	return m_pID_LIST_TRACK;
}

ControlList* CUI_ID_FRAME_TRACK::GetLIST_Finish()
{
	if( !m_pID_FRAME_TRACK )
		return NULL;
	return m_pID_LIST_Finish;
}

bool CUI_ID_FRAME_TRACK::ID_BUTTON_PlusOnButtonClick( ControlObject* pSender )
{
    if( !m_pID_FRAME_TRACK )
        return false;

    m_bMinisize = false;
    s_CUI_ID_FRAME_Task.UpdateTrackInfo();
    m_pID_BUTTON_Plus->SetVisable( false );
    m_pID_BUTTON_Sub->SetVisable( true );
    return true;
}

bool CUI_ID_FRAME_TRACK::ID_BUTTON_SubOnButtonClick( ControlObject* pSender )
{
    if( !m_pID_FRAME_TRACK )
        return false;

    m_bMinisize = true;
    m_pID_LIST_TRACK->Clear();
    m_pID_LIST_Finish->Clear();
    m_pID_BUTTON_Plus->SetVisable( true );
    m_pID_BUTTON_Sub->SetVisable( false );
    return true;
}

bool CUI_ID_FRAME_TRACK::OnFrameRun()
{
	guardfunc;
	int nStartIndex = m_pID_LIST_TRACK->GetShowStartHeight();
	m_pID_LIST_Finish->SetShowStartHeight(nStartIndex);

    return true;
	unguard;
}
bool CUI_ID_FRAME_TRACK::OnFrameRender()
{
	guardfunc;
	return true;
	unguard;
}
// List
void CUI_ID_FRAME_TRACK::ID_LIST_TRACKOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	guardfunc;
	if( !m_pID_FRAME_TRACK )
		return;
	unguard;
}

// Button
bool CUI_ID_FRAME_TRACK::ID_BUTTON_AvailableTaskOnButtonClick( ControlObject* pSender )
{
	if(s_CUI_ID_FRAME_Task.IsVisable())
		s_CUI_ID_FRAME_Task.SetVisable(false);
	else
	{
		s_CUI_ID_FRAME_Task.SetVisable(true);
		s_CUI_ID_FRAME_Task.ID_CHECKBOX_Task2OnCheckBoxCheck(NULL,NULL);
	}
	return true;
}

// 装载UI
bool CUI_ID_FRAME_TRACK::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\Task_Track.meui", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\Task_Track.UI]失败")
			return false;
	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_TRACK::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_TRACK, s_CUI_ID_FRAME_TRACKOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TRACK, s_CUI_ID_FRAME_TRACKOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_TRACK, ID_LIST_TRACK, s_CUI_ID_FRAME_TRACKID_LIST_TRACKOnListSelectChange );
    theUiManager.OnButtonClick( ID_FRAME_TRACK, ID_BUTTON_Plus, s_CUI_ID_FRAME_TRACKID_BUTTON_PlusOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_TRACK, ID_BUTTON_Sub, s_CUI_ID_FRAME_TRACKID_BUTTON_SubOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TRACK, ID_BUTTON_AvailableTask, s_CUI_ID_FRAME_TRACKID_BUTTON_AvailableTaskOnButtonClick );

	m_pID_FRAME_TRACK = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TRACK );
	m_pID_PICTURE_Drag = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TRACK, ID_PICTURE_Drag );
	m_pID_LIST_TRACK = (ControlList*)theUiManager.FindControl( ID_FRAME_TRACK, ID_LIST_TRACK );
	m_pID_LIST_Finish = (ControlList*)theUiManager.FindControl( ID_FRAME_TRACK, ID_LIST_Finish );
	m_pID_CHECKBOX_Task = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_TRACK, ID_CHECKBOX_Task );
    m_pID_BUTTON_Plus = (ControlButton*)theUiManager.FindControl( ID_FRAME_TRACK, ID_BUTTON_Plus );
    m_pID_BUTTON_Sub = (ControlButton*)theUiManager.FindControl( ID_FRAME_TRACK, ID_BUTTON_Sub );
	m_pID_BUTTON_AvailableTask = (ControlButton*)theUiManager.FindControl( ID_FRAME_TRACK, ID_BUTTON_AvailableTask );

    char szTemp[64] = {0};
    m_finishPicGroup.Clear();
    for(int i=1; i<16; ++i)
    {
        sprintf(szTemp, "ID_PICTURE_Finish%d", i);
        ControlPicture* pPic = ( ControlPicture* )theUiManager.FindControl( ID_FRAME_TRACK, szTemp );
        m_finishPicGroup.AddControl(pPic);
    }

    m_taskTrackGroup.Clear();
    m_taskTrackGroup.AddControl( m_pID_LIST_TRACK );
    m_taskTrackGroup.AddControl( m_pID_LIST_Finish );
    m_tabGroup.Clear();
    m_tabGroup.AddPage( m_pID_CHECKBOX_Task, &m_taskTrackGroup );
    m_tabGroup.TogglePage( m_pID_CHECKBOX_Task );

//     m_pID_LIST_TRACK->SetHyberOtherClick(CUI_ID_FRAME_Task::Task_HyberOtherClick);
    m_pID_LIST_TRACK->SetHyberRBtnDown( CUI_ID_FRAME_Task::Task_HyberRBtnDown );

    m_finishPicGroup.SetVisible( false );
    m_pID_FRAME_TRACK->SetVisable( false );
    m_pID_FRAME_TRACK->SetMsgProcFun( MsgProc );

    m_pID_LIST_TRACK->SetMsgHoldup( false );	//不接受消息
    m_pID_LIST_TRACK->HaveSelBar( false );	//没有绿色cur选中地图
    m_pID_LIST_TRACK->setShowTip( true );

    m_pID_LIST_TRACK->SetOnCollapseFun( Task_CollapseCallBackFun );
	m_pID_LIST_TRACK->RemoveSyntaxFlag(eKeyItem);

    m_pID_LIST_Finish->SetMsgHoldup( false );	//不接受消息
    m_pID_LIST_Finish->SetItemMaxCount( 200 );
    m_pID_LIST_Finish->HaveSelBar( false );	//没有绿色cur选中地图
    m_pID_LIST_Finish->SetCurSelIndex( -1 );
    m_pID_LIST_Finish->SetDrawFlags( DT_CENTER | DT_NOCLIP );

    m_pID_BUTTON_Plus->SetVisable( false );
    m_bMinisize = false;
    
	_SetVisable( false );
	return true;
	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_TRACK::_UnLoadUI()
{
	guardfunc;
	m_finishPicGroup.Clear();
	m_pID_FRAME_TRACK = NULL;
	m_nLastNpcMap = -1;
	ResetMembers();
	return theUiManager.RemoveFrame( "data\\ui\\Task_Track.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_TRACK::_IsVisable()
{
	guardfunc;
	if( !m_pID_FRAME_TRACK )
		return false;
	return m_pID_FRAME_TRACK->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_TRACK::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pID_FRAME_TRACK )
		return;
	m_pID_FRAME_TRACK->SetVisable( bVisable );
	unguard;
}

void CUI_ID_FRAME_TRACK::RefreshTask()
{
	if( !m_pID_FRAME_TRACK )
		return;
	m_pID_LIST_Finish->Clear();

	ControlList::S_List stItem;
	for (int i = 0; i < m_pID_LIST_TRACK->GetListItemCnt(); ++i)
	{
		short done = (short)m_pID_LIST_TRACK->GetListItem(i)->m_pData;
		if (done)
		{
			stItem.clear();
			stItem.SetData( "{#1030}" );
			m_pID_LIST_Finish->AddItem(&stItem,NULL, false);
		}
		else
		{
			stItem.clear();
			stItem.SetData( "" );
			m_pID_LIST_Finish->AddItem(&stItem,NULL, false);
		}
	}

	if (m_pID_LIST_TRACK->GetListItemCnt() - m_pID_LIST_TRACK->GetStartIndex() < m_pID_LIST_TRACK->GetItemShowCount())
	{
		m_pID_LIST_TRACK->SetShowStartHeight(0);
		m_pID_LIST_TRACK->SetShowStartHeight(0);
	}
}

void CUI_ID_FRAME_TRACK::Task_CollapseCallBackFun( ControlObject* pSender, ControlList::S_List* pItem )
{
	s_CUI_ID_FRAME_TRACK.RefreshTask();
}

void CUI_ID_FRAME_TRACK::ShowUIs(bool bVisible)
{
	m_pID_CHECKBOX_Task->SetVisable(bVisible);
	m_pID_LIST_TRACK->SetScrollVisable(bVisible);
}

bool CUI_ID_FRAME_TRACK::MsgProc(UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed)
{
	switch( msg ) 
	{
	case WM_MOUSEMOVE:
		{
			INT nX = GET_X_LPARAM(lParam);
			INT nY = GET_Y_LPARAM(lParam);

			const std::vector<UiManager::S_UI*>& vtUIs = theUiManager.getUIVec()[UI_Render_LayerThree];
			for ( UINT n=0; n<vtUIs.size(); n++ )
			{
				if ( !vtUIs[n]->m_pUI )
					continue;  
				if (vtUIs[n]->m_pUI->IsVisable() &&
					vtUIs[n]->m_pUI->IsMsgHoldup() &&
					vtUIs[n]->m_pUI->PtInObject(nX, nY) )
				{

					theMouseManager.SetCanSetCursor(true);
					if (theMouseManager.GetUICursor() == MouseManager::Type_MoveWindow)
						theMouseManager.SetUICursor(MouseManager::Type_Arrow);
					return false;
				}
			}

			if (s_CUI_ID_FRAME_TRACK.m_pID_PICTURE_Drag->PtInObject(nX,nY) &&
				(!s_CUI_ID_FRAME_TRACK.m_pID_CHECKBOX_Task->PtInObject(nX,nY))
				)
			{
				theMouseManager.SetUICursor(MouseManager::Type_MoveWindow);
				theMouseManager.SetCursor(MouseManager::Type_MoveWindow);
				theMouseManager.SetCanSetCursor(false);
			}
			else
			{

				if (theMouseManager.GetUICursor() == MouseManager::Type_MoveWindow)
				{
					theMouseManager.SetCanSetCursor(true);
					theMouseManager.SetUICursor(MouseManager::Type_Arrow);
				}
			}
		}
		break;
	}
	return false;
}

void CUI_ID_FRAME_TRACK::Npc_HyberClick( ControlObject* pSender, const std::string& content ,int nId )
{
	CWorldTile* pCurrTile = CURRENTTILE;
	NpcCoord::getInstance()->clickHyberToMiniMap(content.c_str(),pCurrTile->GetMapId());
}

bool CUI_ID_FRAME_TRACK::IsMinisized()
{
    if( !IsUILoad() )
        return true;

    return m_bMinisize;
}
