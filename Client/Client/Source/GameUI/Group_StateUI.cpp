/********************************************************************
Created by UIEditor.exe
FileName: D:\Tj\Client\UI\Group_StateUI.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Group_StateUI.h"
#include "FuncPerformanceLog.h"
#include "NetworkInput.h"
#include "ItemDetail.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"

extern CHeroGame theHeroGame;

#ifndef MAX_STATUS_SPARETIME
#define MAX_STATUS_SPARETIME 36000000
#endif

CUI_ID_FRAME_StateUI s_CUI_ID_FRAME_StateUI;
MAP_FRAME_RUN( s_CUI_ID_FRAME_StateUI, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_StateUI, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_StateUI, ID_LISTIMG_StateMeOnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_StateUI, ID_LISTIMG_StateMeOnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_StateUI, ID_LISTIMG_StateMeOnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_StateUI, ID_LISTIMG_StateMeOnIconRButtonUp )
CUI_ID_FRAME_StateUI::CUI_ID_FRAME_StateUI()
{
	guardfunc;
	// SGuildMember
	m_pID_FRAME_StateUI = NULL;
	m_pID_LISTIMG_StateMe = NULL;
	m_fCheckSpareTimeCD = 0;
	m_nBufferCount = 0;
	m_bRefresh = false;
	unguard;

}
// Frame
bool CUI_ID_FRAME_StateUI::OnFrameRun()
{
	guardfunc;

	if( IsVisable() )
	{
		if( !theHeroGame.GetPlayerMgr() || !theHeroGame.GetPlayerMgr()->GetMe() )
			return true;

		if (m_bRefresh)
		{
			RefreshBuffer();
			m_bRefresh = false;
			return true;
		}
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
		if( pMe->m_cFightStatus.GetBufferStatusCount() <= 0 )
			return true;

		if( m_fCheckSpareTimeCD > 0 )
		{
			m_fCheckSpareTimeCD -= theHeroGame.GetFrameElapsedTime();
			if( m_fCheckSpareTimeCD > 0 )
				return true;
		}

		m_fCheckSpareTimeCD = 1.f;
		SCharBuff* pStatus = NULL;
		int i = 0;
		for ( int n=0; n < pMe->m_cFightStatus.GetBufferStatusCount(); ++n )
		{
			pStatus = pMe->m_cFightStatus.GetBuff( n );
			if ( !pStatus )
				continue;

			ItemDefine::SItemStatus* pItemStatus = NULL;
			pItemStatus = GettheItemDetail().GetStatus( pStatus->StatusID,
				pStatus->iLevel);

			if(pItemStatus)
			{
				if (pItemStatus->bAvail)
				{
					++i;
				}
			}
		}
		if (i != m_nBufferCount)
		{
			RefreshBuffer();
			return true;
		}
		bool bClearStatus = false;
		int nCountPerLine = m_pID_LISTIMG_StateMe->GetRowItemCnt();
		for(int nIndex = 0; nIndex < m_nBufferCount; ++nIndex)
		{
			int nOriOffset = nCountPerLine - 1 - nIndex % nCountPerLine;
			int nRow = nIndex/ nCountPerLine * nCountPerLine;
			ControlIconDrag::S_ListImg* pItemImg = m_pID_LISTIMG_StateMe->GetItemByIndex(nRow + nOriOffset);
			if( pItemImg && pItemImg->m_pkIconInfo->GetItemId() != 65535 )
			{
				DWORD dwSpareTime = ((S_IconInfoHero*)pItemImg->m_pkIconInfo)->GetSpareTime();
				if( dwSpareTime == 0 )
				{
					pMe->m_cFightStatus.ClearBuffByBuffId(pItemImg->m_pkIconInfo->GetItemId());
					bClearStatus = true;
				}
			}
		}
		if( bClearStatus )
		{
			pMe->m_cFightStatus.LogAndClearBufferClearIdArray();
		}
	}

	return true;
	unguard;
}
bool CUI_ID_FRAME_StateUI::OnFrameRender()
{
	guardfunc;
	return true;
	unguard;
}

void CUI_ID_FRAME_StateUI::InitializeAtEnterWorld()
{
    SetVisable( true );
    m_fCheckSpareTimeCD = 0;
}

// ListImg / ListEx
bool CUI_ID_FRAME_StateUI::ID_LISTIMG_StateMeOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{
	guardfunc;
	if( !m_pID_FRAME_StateUI )
		return false;
	return false;
	unguard;
}
bool CUI_ID_FRAME_StateUI::ID_LISTIMG_StateMeOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
														   ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	if( !m_pID_FRAME_StateUI )
		return false;
	return false;
	unguard;
}
bool CUI_ID_FRAME_StateUI::ID_LISTIMG_StateMeOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	if( !m_pID_FRAME_StateUI )
		return false;
	return false;
	unguard;
}
bool CUI_ID_FRAME_StateUI::ID_LISTIMG_StateMeOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_StateUI )
		return false;
	if( !pItem )
		return false;
	
	ItemDefine::SItemStatus* pItemStatus = NULL;
	pItemStatus = GettheItemDetail().GetStatus( pItem->m_pkIconInfo->Id(), pItem->m_pkIconInfo->Count());
	if(!pItemStatus || !pItemStatus->canCancel)
		return false;

	MsgCancelBuff msg;
	msg.buffId = pItem->m_pkIconInfo->Id();
	GettheNetworkInput().SendMsg( &msg );
	return false;
}


// 装载UI
bool CUI_ID_FRAME_StateUI::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\Group_StateUI.meui", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\Group_StateUI.UI]失败")
			return false;
	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_StateUI::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_StateUI, s_CUI_ID_FRAME_StateUIOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_StateUI, s_CUI_ID_FRAME_StateUIOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_StateUI, ID_LISTIMG_StateMe, s_CUI_ID_FRAME_StateUIID_LISTIMG_StateMeOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_StateUI, ID_LISTIMG_StateMe, s_CUI_ID_FRAME_StateUIID_LISTIMG_StateMeOnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_StateUI, ID_LISTIMG_StateMe, s_CUI_ID_FRAME_StateUIID_LISTIMG_StateMeOnIconRButtonUp );

	m_pID_FRAME_StateUI = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_StateUI );
	m_pID_LISTIMG_StateMe = (ControlListImage*)theUiManager.FindControl( ID_FRAME_StateUI, ID_LISTIMG_StateMe );
	assert( m_pID_FRAME_StateUI );
	assert( m_pID_LISTIMG_StateMe );

    m_pID_LISTIMG_StateMe->SetShowAllInfo( true );
    m_pID_FRAME_StateUI->enableEscKey( false );
    m_pID_FRAME_StateUI->SetOnEscResponseType(ControlFrame::EscResponse_SkipMe);
	return true;
	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_StateUI::_UnLoadUI()
{
	guardfunc;
	m_pID_FRAME_StateUI = NULL;
	m_pID_LISTIMG_StateMe = NULL;
	return theUiManager.RemoveFrame( "data\\ui\\Group_StateUI.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_StateUI::_IsVisable()
{
	guardfunc;
	if( !m_pID_FRAME_StateUI )
		return false;
	return m_pID_FRAME_StateUI->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_StateUI::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pID_FRAME_StateUI )
		return;
	m_pID_FRAME_StateUI->SetVisable( bVisable );
	unguard;
}

void CUI_ID_FRAME_StateUI::RefreshBuffer()
{
	if(!m_pID_FRAME_StateUI)
		return;

	m_pID_LISTIMG_StateMe->Clear();
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	int nCountPerLine = m_pID_LISTIMG_StateMe->GetRowItemCnt();
	int i = 0;
	for ( int n=0; n < pMe->m_cFightStatus.GetBufferStatusCount(); ++n )
	{
		SCharBuff* pStatus = pMe->m_cFightStatus.GetBuff( n );
		if ( !pStatus )
			continue;

		ItemDefine::SItemStatus* pItemStatus = NULL;
		pItemStatus = GettheItemDetail().GetStatus( pStatus->StatusID,
			pStatus->iLevel);

		if(pItemStatus)
		{
			if (pItemStatus->bAvail)
			{
				ControlIconDrag::S_ListImg stItem;
				stItem.SetData( pStatus->StatusID, pStatus->iLevel, pStatus->bStop? eIcon_Disable:eIcon_Enable, true, eTipFlag_Status );
				int nOriOffset = nCountPerLine - 1 - i % nCountPerLine;
				int nRow = i / nCountPerLine * nCountPerLine;
				m_pID_LISTIMG_StateMe->SetItem( &stItem, nRow + nOriOffset);
				if( pStatus->bStop )	// 暂停
				{
					m_pID_LISTIMG_StateMe->SetSpareTime( nRow + nOriOffset, 0xffffffff, pStatus->dwStartTime, true );
				}
				else if( pItemStatus->IsForeverStatus() )	// 永久BUFF
					m_pID_LISTIMG_StateMe->SetSpareTime( nRow + nOriOffset, MAX_STATUS_SPARETIME, pStatus->dwStartTime, true );
				else
					m_pID_LISTIMG_StateMe->SetSpareTime( nRow + nOriOffset, pStatus->dwDurationTime, pStatus->dwStartTime, true );
				++i;
			}
		}
	}
	m_nBufferCount = i;
	m_pID_LISTIMG_StateMe->RefreshTipShow(theUiManager.m_ptMoust.x,theUiManager.m_ptMoust.y);
	m_pID_FRAME_StateUI->SetRedraw();

}