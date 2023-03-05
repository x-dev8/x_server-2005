/********************************************************************
Created by UIEditor.exe
FileName: D:\Program\XSanguoRun\Client\UI\Group_DeBuffUI.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Group_DeBuffUI.h"
#include "FuncPerformanceLog.h"
#include "ItemDetail.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"

CUI_ID_FRAME_DeBuffUI s_CUI_ID_FRAME_DeBuffUI;
MAP_FRAME_RUN( s_CUI_ID_FRAME_DeBuffUI, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_DeBuffUI, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_DeBuffUI, ID_LISTIMG_DeBuffMeOnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_DeBuffUI, ID_LISTIMG_DeBuffMeOnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_DeBuffUI, ID_LISTIMG_DeBuffMeOnIconLDBClick )
CUI_ID_FRAME_DeBuffUI::CUI_ID_FRAME_DeBuffUI()
{
	guardfunc;
	// SGuildMember
	m_pID_FRAME_DeBuffUI = NULL;
	m_pID_LISTIMG_DeBuffMe = NULL;
	m_fCheckSpareTimeCD = 0;
	m_bRefresh = false;
	m_nBufferCount = 0;
	m_bBuffId = 0;
	unguard;

}
// Frame
bool CUI_ID_FRAME_DeBuffUI::OnFrameRun()
{
	if (IsVisable())
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
		int ndebuff = 0;
		for ( int n=0; n < pMe->m_cFightStatus.GetBufferStatusCount(); n++ )
		{
			pStatus = pMe->m_cFightStatus.GetBuff( n );
			if ( !pStatus )
				continue;

			//这里把status如果有持续时间的话 把这个持续时间加上去
			ItemDefine::SItemStatus* pItemStatus = NULL;
			pItemStatus = GettheItemDetail().GetStatus( pStatus->StatusID,
				pStatus->iLevel);
			if(pItemStatus)
			{
				if (pItemStatus->bAvail)
				{
				}
				else
				{
					ndebuff++;
				}				
			}		
		}
		if (ndebuff != m_nBufferCount)
		{
			RefreshBuffer();
			return true;
		}
		bool bClearStatus = false;
		int nCountPerLine = m_pID_LISTIMG_DeBuffMe->GetRowItemCnt();
		for(int nIndex = 0; nIndex < m_nBufferCount; ++nIndex)
		{
			int nOriOffset = nCountPerLine - 1 - nIndex % nCountPerLine;
			int nRow = nIndex/ nCountPerLine * nCountPerLine;
			ControlIconDrag::S_ListImg* pItemImg = m_pID_LISTIMG_DeBuffMe->GetItemByIndex(nRow + nOriOffset);
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
}
bool CUI_ID_FRAME_DeBuffUI::OnFrameRender()
{
	return true;
}

void CUI_ID_FRAME_DeBuffUI::InitializeAtEnterWorld()
{
    SetVisable( true );
}

// ListImg / ListEx
bool CUI_ID_FRAME_DeBuffUI::ID_LISTIMG_DeBuffMeOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															ControlIconDrag::S_ListImg* pItemDrag,
															ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!m_pID_FRAME_DeBuffUI)
		return false;
	return false;
}
bool CUI_ID_FRAME_DeBuffUI::ID_LISTIMG_DeBuffMeOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
															 ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_DeBuffUI)
		return false;
	return false;
}
bool CUI_ID_FRAME_DeBuffUI::ID_LISTIMG_DeBuffMeOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_DeBuffUI)
		return false;
	return false;
}
// 装载UI
bool CUI_ID_FRAME_DeBuffUI::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\Group_DeBuffUI.meui", true );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\Group_DeBuffUI.UI]失败")
			return false;
	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_DeBuffUI::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_DeBuffUI, s_CUI_ID_FRAME_DeBuffUIOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_DeBuffUI, s_CUI_ID_FRAME_DeBuffUIOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_DeBuffUI, ID_LISTIMG_DeBuffMe, s_CUI_ID_FRAME_DeBuffUIID_LISTIMG_DeBuffMeOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_DeBuffUI, ID_LISTIMG_DeBuffMe, s_CUI_ID_FRAME_DeBuffUIID_LISTIMG_DeBuffMeOnIconLDBClick );

	m_pID_FRAME_DeBuffUI = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_DeBuffUI );
	m_pID_LISTIMG_DeBuffMe = (ControlListImage*)theUiManager.FindControl( ID_FRAME_DeBuffUI, ID_LISTIMG_DeBuffMe );
	assert( m_pID_FRAME_DeBuffUI );
	assert( m_pID_LISTIMG_DeBuffMe );

	m_pID_FRAME_DeBuffUI->SetMsgHoldup(false);
	m_pID_LISTIMG_DeBuffMe->ShowPressEffect( false );
	m_pID_LISTIMG_DeBuffMe->SetMsgHoldup(false);
	m_pID_LISTIMG_DeBuffMe->SetShowAllInfo( true );
	m_pID_LISTIMG_DeBuffMe->SetDisableCanbePick( true );

	m_pID_LISTIMG_DeBuffMe->setOrderType(true);
	return true;
	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_DeBuffUI::_UnLoadUI()
{
	guardfunc;
	m_pID_FRAME_DeBuffUI = NULL;
	m_pID_LISTIMG_DeBuffMe = NULL;
	return theUiManager.RemoveFrame( "data\\ui\\Group_DeBuffUI.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_DeBuffUI::_IsVisable()
{
	guardfunc;
    if(!m_pID_FRAME_DeBuffUI)
        return false;

	return m_pID_FRAME_DeBuffUI->IsVisable();
	unguard;

}
// 设置是否可视
void CUI_ID_FRAME_DeBuffUI::_SetVisable( const bool bVisable )
{
	guardfunc;
    if(!m_pID_FRAME_DeBuffUI)
        return;
	m_pID_FRAME_DeBuffUI->SetVisable( bVisable );
	unguard;
}

void CUI_ID_FRAME_DeBuffUI::ClearListImage()
{
    if(!m_pID_FRAME_DeBuffUI)
        return;

    m_pID_LISTIMG_DeBuffMe->Clear();
}

void CUI_ID_FRAME_DeBuffUI::SetVisableListImage(bool bVisable)
{
    if(!m_pID_FRAME_DeBuffUI)
        return;

    m_pID_LISTIMG_DeBuffMe->SetVisable(bVisable);
}

void CUI_ID_FRAME_DeBuffUI::RefreshBuffer()
{
	ClearListImage();
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	SCharBuff* pStatus = NULL;
	int ndebuff = 0;
	for ( int n=0; n < pMe->m_cFightStatus.GetBufferStatusCount(); n++ )
	{
		pStatus = pMe->m_cFightStatus.GetBuff( n );
		if ( !pStatus )
			continue;

		//这里把status如果有持续时间的话 把这个持续时间加上去
		ItemDefine::SItemStatus* pItemStatus = NULL;
		pItemStatus = GettheItemDetail().GetStatus( pStatus->StatusID,
			pStatus->iLevel);
		if(pItemStatus)
		{
			if (pItemStatus->bAvail)
			{
			}
			else
			{
				ControlIconDrag::S_ListImg stItem;
				stItem.SetData( pStatus->StatusID, pStatus->iLevel, pStatus->bStop? eIcon_Disable:eIcon_Enable, true, eTipFlag_Status );
				if(m_pID_LISTIMG_DeBuffMe)
				{
					int nCountPerLine = m_pID_LISTIMG_DeBuffMe->GetRowItemCnt();
					int nOriOffset = nCountPerLine - 1 - ndebuff % nCountPerLine;
					int nRow = ndebuff / nCountPerLine * nCountPerLine;
					m_pID_LISTIMG_DeBuffMe->SetItem( &stItem,nRow + nOriOffset );
					m_pID_LISTIMG_DeBuffMe->SetSpareTime( nRow + nOriOffset, pStatus->dwDurationTime, pStatus->dwStartTime, true );
				}
				ndebuff++;
			}				
		}		
	}
	m_nBufferCount = ndebuff;
	m_pID_LISTIMG_DeBuffMe->RefreshTipShow(theUiManager.m_ptMoust.x,theUiManager.m_ptMoust.y);
}

bool CUI_ID_FRAME_DeBuffUI::IfHPBuffID()
{
	/*
	*	Author 2012-12-10 zhuxincong
	*	DESC: 现在慢慢恢复的药物在，自动打怪的时候会无限吃，那么当有这个buff的时候 就不会再吃，这里做的就是找到buffID
	*/
	SCharBuff* pStatus = NULL;
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	for ( int n=0; n < pMe->m_cFightStatus.GetBufferStatusCount(); n++ )
	{
		pStatus = pMe->m_cFightStatus.GetBuff( n );
		if ( !pStatus )
			continue;

		if (pStatus->StatusID == 2900 || pStatus->StatusID == 2902)
		{
			return true;
		}
	}
	return false;
}

bool CUI_ID_FRAME_DeBuffUI::IfMPBuffID()
{
	/*
	*	Author 2012-12-10 zhuxincong
	*	DESC: 现在慢慢恢复的药物在，自动打怪的时候会无限吃，那么当有这个buff的时候 就不会再吃，这里做的就是找到buffID
	*/
	SCharBuff* pStatus = NULL;
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	m_bBuffId = 0;
	for ( int n=0; n < pMe->m_cFightStatus.GetBufferStatusCount(); n++ )
	{
		pStatus = pMe->m_cFightStatus.GetBuff( n );
		if ( !pStatus )
			continue;

		if (pStatus->StatusID == 2901 || pStatus->StatusID == 2903)
		{
			return true;
		}
	}
	return false;
}