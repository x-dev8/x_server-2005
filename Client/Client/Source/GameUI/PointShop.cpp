/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\chixin.ni\桌面\PointShop.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PointShop.h"
#include "Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "XmlStringLanguage.h"
#include "Common.h"

#define POINTSHOP_BOX_COLUMN 7

CUI_ID_FRAME_PointShop s_CUI_ID_FRAME_PointShop;
MAP_FRAME_RUN( s_CUI_ID_FRAME_PointShop, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PointShop, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_PointShop, ID_LISTIMG_SelectedAwardOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_PointShop, ID_LISTIMG_SelectedAwardOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PointShop, ID_LISTIMG_SelectedAwardOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PointShop, ID_LISTIMG_SelectedAwardOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PointShop, ID_BUTTON_SelectOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PointShop, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PointShop, ID_BUTTON_CancelOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_PointShop, ID_LISTIMG_AllAwardOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_PointShop, ID_LISTIMG_AllAwardOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PointShop, ID_LISTIMG_AllAwardOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PointShop, ID_LISTIMG_AllAwardOnIconRButtonUp )
CUI_ID_FRAME_PointShop::CUI_ID_FRAME_PointShop()
{
	// Member
	m_pID_FRAME_PointShop = NULL;
	m_pID_PICTURE_Wall = NULL;
	m_pID_LISTIMG_SelectedAward = NULL;
	m_pID_BUTTON_Select = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_LISTIMG_AllAward = NULL;
	m_pID_TEXT_Null = NULL;
	m_pID_TEXT_Explain = NULL;

}
// Frame
bool CUI_ID_FRAME_PointShop::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_PointShop::OnFrameRender()
{
	if( IsVisable() )
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if ( pMe )
		{
			float fMeX,fMeY,fMeZ;			
			pMe->GetPos( &fMeX, &fMeY, &fMeZ );
			float dist = pMe->GetDistToTarget( m_vVisiblePos.x, m_vVisiblePos.y );			
			if( dist > 7.0f )
			{
				SetVisable( false );
			}
		}
	}

	if( IsVisable() )
	{
		if(m_vecItemSelect.size()==0)
		{
			m_pID_BUTTON_OK->SetEnable(false);
		}
		else
		{
			m_pID_BUTTON_OK->SetEnable(true);

		}
	}

	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_PointShop::ID_LISTIMG_SelectedAwardOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																  ControlIconDrag::S_ListImg* pItemDrag,
																  ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_PointShop )
		return false;
	return false;
}
bool CUI_ID_FRAME_PointShop::ID_LISTIMG_SelectedAwardOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PointShop )
		return false;
	int nIndex = m_pID_LISTIMG_SelectedAward->GetItemIndex( pItem );

	if( nIndex<m_vecItemSelect.size() )
	{
		m_vecItemSelect.erase(m_vecItemSelect.begin()+nIndex);
	}

	Refresh();

	return false;
}
bool CUI_ID_FRAME_PointShop::ID_LISTIMG_SelectedAwardOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_PointShop::ID_LISTIMG_SelectedAwardOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PointShop )
		return false;
	int nIndex = m_pID_LISTIMG_SelectedAward->GetItemIndex( pItem );

	if( nIndex<m_vecItemSelect.size() )
	{
		m_vecItemSelect.erase(m_vecItemSelect.begin()+nIndex);
	}

	Refresh();

	return false;
}
// Button
bool CUI_ID_FRAME_PointShop::ID_BUTTON_SelectOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PointShop )
		return false;
	int nIndex = m_pID_LISTIMG_AllAward->GetItemIndex( m_pID_LISTIMG_AllAward->GetCurSelItem() );
	
	if( nIndex<m_vecItemRecord.size() )
	{
		for(int i=0;i<m_vecItemSelect.size();++i)
		{
			if(m_vecItemSelect[i].id==m_vecItemRecord[nIndex].id)
			{
				return false;
			}
		}
		m_vecItemSelect.push_back( m_vecItemRecord[nIndex] );
	}

	Refresh();

	return true;
}
// Button
bool CUI_ID_FRAME_PointShop::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PointShop )
		return false;
	MsgJiFengShopItemsGain msg;
	
	if(m_vecItemSelect.size()==0)
		return false;

	for(int i=0;i<m_vecItemSelect.size();++i)
	{
		if(!msg.AddRecord( m_vecItemSelect[i].id,m_vecItemSelect[i].itemId))
		{
			GettheNetworkInput().SendMsg( &msg );
			msg.Reset();

			msg.AddRecord(m_vecItemSelect[i].id,m_vecItemSelect[i].itemId);
		}
	}

	GettheNetworkInput().SendMsg( &msg );

	SetVisable(false);

	return true;
}
// Button
bool CUI_ID_FRAME_PointShop::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PointShop )
		return false;

	SetVisable(false);

	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_PointShop::ID_LISTIMG_AllAwardOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															 ControlIconDrag::S_ListImg* pItemDrag,
															 ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_PointShop )
		return false;
	return false;
}
bool CUI_ID_FRAME_PointShop::ID_LISTIMG_AllAwardOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PointShop )
		return false;
    if(!pItem)
        return false;

	int nIndex = m_pID_LISTIMG_AllAward->GetItemIndex( pItem );
	
	if(nIndex >= 0 && nIndex<m_vecItemRecord.size() )
	{
		for(int i=0;i<m_vecItemSelect.size();++i)
		{
			if(m_vecItemSelect[i].id==m_vecItemRecord[nIndex].id)
			{
				return false;
			}
		}
		m_vecItemSelect.push_back( m_vecItemRecord[nIndex] );
	}

	Refresh();

	return false;
}
bool CUI_ID_FRAME_PointShop::ID_LISTIMG_AllAwardOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PointShop )
		return false;
	SetSelectItem(pItem);

	return false;
}
bool CUI_ID_FRAME_PointShop::ID_LISTIMG_AllAwardOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PointShop )
		return false;
    if(!pItem)
        return false;

	int nIndex = m_pID_LISTIMG_AllAward->GetItemIndex( pItem );
	
	if(nIndex >= 0 && nIndex<m_vecItemRecord.size() )
	{
		for(int i=0;i<m_vecItemSelect.size();++i)
		{
			if(m_vecItemSelect[i].id==m_vecItemRecord[nIndex].id)
			{
				return false;
			}
		}
		m_vecItemSelect.push_back( m_vecItemRecord[nIndex] );
	}

	Refresh();

	return false;
}

// 装载UI
bool CUI_ID_FRAME_PointShop::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PointShop.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\PointShop.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_PointShop::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PointShop, s_CUI_ID_FRAME_PointShopOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PointShop, s_CUI_ID_FRAME_PointShopOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_PointShop, ID_LISTIMG_SelectedAward, s_CUI_ID_FRAME_PointShopID_LISTIMG_SelectedAwardOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PointShop, ID_LISTIMG_SelectedAward, s_CUI_ID_FRAME_PointShopID_LISTIMG_SelectedAwardOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PointShop, ID_LISTIMG_SelectedAward, s_CUI_ID_FRAME_PointShopID_LISTIMG_SelectedAwardOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PointShop, ID_LISTIMG_SelectedAward, s_CUI_ID_FRAME_PointShopID_LISTIMG_SelectedAwardOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_PointShop, ID_BUTTON_Select, s_CUI_ID_FRAME_PointShopID_BUTTON_SelectOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PointShop, ID_BUTTON_OK, s_CUI_ID_FRAME_PointShopID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PointShop, ID_BUTTON_Cancel, s_CUI_ID_FRAME_PointShopID_BUTTON_CancelOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_PointShop, ID_LISTIMG_AllAward, s_CUI_ID_FRAME_PointShopID_LISTIMG_AllAwardOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PointShop, ID_LISTIMG_AllAward, s_CUI_ID_FRAME_PointShopID_LISTIMG_AllAwardOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PointShop, ID_LISTIMG_AllAward, s_CUI_ID_FRAME_PointShopID_LISTIMG_AllAwardOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PointShop, ID_LISTIMG_AllAward, s_CUI_ID_FRAME_PointShopID_LISTIMG_AllAwardOnIconRButtonUp );

	m_pID_FRAME_PointShop = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PointShop );
	m_pID_PICTURE_Wall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PointShop, ID_PICTURE_Wall );
	m_pID_LISTIMG_SelectedAward = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PointShop, ID_LISTIMG_SelectedAward );
	m_pID_BUTTON_Select = (ControlButton*)theUiManager.FindControl( ID_FRAME_PointShop, ID_BUTTON_Select );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_PointShop, ID_BUTTON_OK );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_PointShop, ID_BUTTON_Cancel );
	m_pID_LISTIMG_AllAward = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PointShop, ID_LISTIMG_AllAward );
	m_pID_TEXT_Null = (ControlText*)theUiManager.FindControl( ID_FRAME_PointShop, ID_TEXT_Null );
	m_pID_TEXT_Explain = (ControlText*)theUiManager.FindControl( ID_FRAME_PointShop, ID_TEXT_Explain );
	assert( m_pID_FRAME_PointShop );
	assert( m_pID_PICTURE_Wall );
	assert( m_pID_LISTIMG_SelectedAward );
	assert( m_pID_BUTTON_Select );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_LISTIMG_AllAward );
	assert( m_pID_TEXT_Null );
	assert( m_pID_TEXT_Explain );

	m_pID_FRAME_PointShop->SetVisable(false);

	m_pID_LISTIMG_AllAward->SetHeightShowMaxCnt(0);
	m_pID_LISTIMG_SelectedAward->SetHeightShowMaxCnt(0);

	m_pID_LISTIMG_AllAward->SetHeightMaxCnt(0);
	m_pID_LISTIMG_SelectedAward->SetHeightMaxCnt(0);

	m_pID_TEXT_Null->SetVisable(true);
	m_pID_BUTTON_Select->SetEnable(false);
	m_pID_BUTTON_OK->SetEnable(false);

	m_pID_LISTIMG_AllAward->SetEnableDrag(false);
	m_pID_LISTIMG_SelectedAward->SetEnableDrag(false);

	m_nItemCount = 0;
	m_pSelectItem = NULL;

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_PointShop::_UnLoadUI()
{
	m_pID_FRAME_PointShop = NULL;
	m_pID_PICTURE_Wall = NULL;
	m_pID_LISTIMG_SelectedAward = NULL;
	m_pID_BUTTON_Select = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_LISTIMG_AllAward = NULL;
	m_pID_TEXT_Null = NULL;
	m_pID_TEXT_Explain = NULL;
	m_pSelectItem = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\PointShop.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_PointShop::_IsVisable()
{
	if( m_pID_FRAME_PointShop )
		return m_pID_FRAME_PointShop->IsVisable();

	return false;
}
// 设置是否可视
void CUI_ID_FRAME_PointShop::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_PointShop )
		return;

	m_pSelectItem = NULL;

	m_vecItemRecord.clear();
	m_vecItemSelect.clear();

	if(m_pID_BUTTON_Select)
		m_pID_BUTTON_Select->SetEnable(false);
	if(m_pID_BUTTON_OK)
		m_pID_BUTTON_OK->SetEnable(false);

	if(m_pID_LISTIMG_AllAward)
	{
		m_pID_LISTIMG_AllAward->Clear();
		m_pID_LISTIMG_AllAward->SetScrollValue(0);
	}

	if(m_pID_LISTIMG_SelectedAward)
		m_pID_LISTIMG_SelectedAward->Clear();

	if( m_pID_FRAME_PointShop )
		m_pID_FRAME_PointShop->SetVisable( bVisable );

    if(m_pID_TEXT_Null)
    {
        char szWord[256];
        MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"%s",theXmlString.GetString(eText_WaitingServerUpdate));
        m_pID_TEXT_Null->SetText(szWord);
        m_pID_TEXT_Null->SetVisable(true);
    }
}

void CUI_ID_FRAME_PointShop::UpdateItem( Msg* pMsg )
{
	if( !m_pID_FRAME_PointShop )
		return;
	MsgJiFengShopItemsListAck* pItemListAck = (MsgJiFengShopItemsListAck*)pMsg;


    if(pItemListAck->isNew)  //表示第一次发送消息，清空上次的容器
    {
        m_vecItemRecord.clear();
        m_vecItemSelect.clear();

        m_nItemCount = 0;         //清空物品数量
        if(pItemListAck->count > 0)
            m_pID_TEXT_Null->SetVisable(false);
        else
        {
            char szWord[256];
            MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"%s",theXmlString.GetString(eText_PointShowInfo));
            m_pID_TEXT_Null->SetText(szWord);
        }
    } 

    //计算改发送过来的总个数
    m_nItemCount += pItemListAck->count;

    //清楚UI控件
    m_pID_LISTIMG_AllAward->Clear();
    m_pID_LISTIMG_SelectedAward->Clear();

    //计算Image滚动条的高度,用于设置最大值
    int cnt = m_nItemCount/POINTSHOP_BOX_COLUMN;
    if( m_nItemCount%POINTSHOP_BOX_COLUMN != 0 )
    {
        ++cnt;
    }

    m_pID_LISTIMG_AllAward->SetHeightShowMaxCnt( 3 );  //可见行数为3行
    m_pID_LISTIMG_AllAward->SetHeightMaxCnt( cnt);     //最大行数

    m_pID_LISTIMG_SelectedAward->SetHeightShowMaxCnt( 0 );
    m_pID_LISTIMG_SelectedAward->SetHeightMaxCnt( 0 );

    int nSize = m_vecItemRecord.size();
    for (int i = 0;i < nSize;++i)
    {
        ControlIconDrag::S_ListImg item;
        item.SetData(m_vecItemRecord[i].itemId,m_vecItemRecord[i].itemCount);

        m_pID_LISTIMG_AllAward->SetItem( &item);
    }


    for (int i = 0;i < pItemListAck->count;++i)
    {
         m_vecItemRecord.push_back(pItemListAck->items[i]);

        ControlIconDrag::S_ListImg item;
        item.SetData(pItemListAck->items[i].itemId,pItemListAck->items[i].itemCount);

        m_pID_LISTIMG_AllAward->SetItem( &item);
    }

    m_pID_BUTTON_Select->SetEnable(true);
    m_pID_BUTTON_OK->SetEnable(true);
    return;



	if(pItemListAck->isNew)
	{
		m_vecItemRecord.clear();
		m_nItemCount = pItemListAck->count;

		int cnt = m_nItemCount/POINTSHOP_BOX_COLUMN;
		if( m_nItemCount%POINTSHOP_BOX_COLUMN != 0 )
		{
			++cnt;
		}

		for( int i = 0; i < pItemListAck->count; ++i)
		{
			ControlIconDrag::S_ListImg item;
			item.SetData(pItemListAck->items[i].itemId,pItemListAck->items[i].itemCount);

#ifdef _DEBUG
            char szWord[128];
            MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"%d %d\n",pItemListAck->items[i].itemId,pItemListAck->items[i].itemCount);
            ::OutputDebugString(szWord);
#endif

			m_pID_LISTIMG_AllAward->SetItem( &item/*, i*/ );

			m_vecItemRecord.push_back(pItemListAck->items[i]);
		}
	}
	else
	{
		m_nItemCount += pItemListAck->count;
		int cnt = m_nItemCount/POINTSHOP_BOX_COLUMN;
		if( m_nItemCount%POINTSHOP_BOX_COLUMN != 0 )
		{
			++cnt;
		}

		m_pID_LISTIMG_AllAward->Clear();
		m_pID_LISTIMG_SelectedAward->Clear();

		m_pID_LISTIMG_AllAward->SetHeightShowMaxCnt( cnt );
		m_pID_LISTIMG_AllAward->SetHeightMaxCnt( cnt*2 );

		m_pID_LISTIMG_SelectedAward->SetHeightShowMaxCnt( 0 );
		m_pID_LISTIMG_SelectedAward->SetHeightMaxCnt( 0 );

		for( int i = 0; i < pItemListAck->count; ++i)
		{
			ControlIconDrag::S_ListImg item;
			item.SetData(pItemListAck->items[i].itemId,pItemListAck->items[i].itemCount);

#ifdef _DEBUG
            char szWord[128];
            MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"%d %d\n",pItemListAck->items[i].itemId,pItemListAck->items[i].itemCount);
            ::OutputDebugString(szWord);
#endif

			m_pID_LISTIMG_AllAward->SetItem( &item/*, i*/ );

			m_vecItemRecord.push_back(pItemListAck->items[i]);
		}
	}

	m_pID_BUTTON_Select->SetEnable(true);
	m_pID_BUTTON_OK->SetEnable(true);
}

void CUI_ID_FRAME_PointShop::Refresh()
{
	if( !m_pID_FRAME_PointShop )
		return;
	int sel1 = m_pID_LISTIMG_AllAward->GetItemIndex(m_pID_LISTIMG_AllAward->GetCurSelItem());
	int sel2 = m_pID_LISTIMG_SelectedAward->GetItemIndex(m_pID_LISTIMG_SelectedAward->GetCurSelItem());

	m_pID_LISTIMG_SelectedAward->Clear();
	int cnt = m_vecItemSelect.size()/POINTSHOP_BOX_COLUMN;
	if( m_vecItemSelect.size()%POINTSHOP_BOX_COLUMN != 0 )
	{
		++cnt;
	}

	m_pID_LISTIMG_SelectedAward->SetHeightShowMaxCnt( 2 );
	m_pID_LISTIMG_SelectedAward->SetHeightMaxCnt( cnt );

	for( int i=0;i<m_vecItemRecord.size();++i )
	{
		ControlIconDrag::S_ListImg item;
		item.SetData( m_vecItemRecord[i].itemId, m_vecItemRecord[i].itemCount );

		item.SetEnable(eIcon_Enable);
		m_pID_LISTIMG_AllAward->SetItem( &item, i );

		for( int j=0;j<m_vecItemSelect.size();++j )
		{
			if( m_vecItemSelect[j].id==m_vecItemRecord[i].id )
			{
				item.SetEnable(eIcon_Disable);
				m_pID_LISTIMG_AllAward->SetItem( &item, i );
			}
		}
	}

	for( int j=0;j<m_vecItemSelect.size();++j )
	{
		ControlIconDrag::S_ListImg item;
		item.SetData( m_vecItemSelect[j].itemId, m_vecItemSelect[j].itemCount );

		m_pID_LISTIMG_SelectedAward->SetItem( &item, j );
	}
}

void CUI_ID_FRAME_PointShop::SetSelectItem(ControlIconDrag::S_ListImg* pItem)
{
	if (!pItem)
		return;

	if (m_pSelectItem)
		m_pSelectItem->m_pkIconInfo->SetColorFrameType(eColorFrame_None);

	m_pSelectItem = pItem;
	m_pSelectItem->m_pkIconInfo->SetColorFrameType(eColorFrame_Select);
}
