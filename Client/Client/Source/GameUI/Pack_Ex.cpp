/********************************************************************
Created by UIEditor.exe
FileName: D:\Tj\Client\UI\Pack_Ex.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Pack_Ex.h"
#include "Pack.h"
#include "Shop.h"
#include "PlayerRole.h"
#include "XmlStringLanguage.h"
#include "FuncPerformanceLog.h"
#include "RestoreColdDown.h"
#include "UIStorage.h"
#include "MeUi/MouseManager.h"
#include "MessageBox.h"
#include "InputBox.h"
#include "GameMain.h"
#include "ChatInfoBox.h"
#include "chat_particular.h"
#include "core/Name.h"
#include "PackItemEnableManager.h"

#define PACKEX_ROW_COUNT 0


CUI_ID_FRAME_pack_ex s_CUI_ID_FRAME_pack_ex;
MAP_FRAME_RUN( s_CUI_ID_FRAME_pack_ex, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_pack_ex, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_pack_ex, ID_LISTIMG_pack_exOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_pack_ex, ID_LISTIMG_pack_exOnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_pack_ex, ID_LISTIMG_pack_exOnIconRDBClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_pack_ex, ID_BUTTON_CLOSEOnButtonClick )
CUI_ID_FRAME_pack_ex::CUI_ID_FRAME_pack_ex()
{
	guardfunc;
	// SGuildMember
	m_pID_FRAME_pack_ex = NULL;
	m_pID_PICTURE_picBacEnable = NULL;
	m_pID_PICTURE_picBacDisable = NULL;
	m_pID_LISTIMG_pack_ex = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_PICTURE_picBacDisableRow = NULL;

	packEx_RowCnt = 2;
	unguard;
}

// Frame
bool CUI_ID_FRAME_pack_ex::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_pack_ex::OnFrameRender()
{
	return true;
}
//------------------------物品加密解密---------------------------------------
bool CheckPwd_Pack_ex(const char* szInputData, void *pData)
{
	guardfunc;
	s_CUI_ID_FRAME_Storage.SetItem_LastPWD( szInputData );
	if(strcmp(s_CUI_ID_FRAME_Storage.GetItem_LastPWD(),"") == 0)
	{
		s_CUI_ID_FRAME_Storage.SetInUIFrameLock(false);
		return false;
	}
	//光标置回原来的状态
	theMouseManager.SetUICursor(MouseManager::Type_Arrow);
	//判别两个字符串是否相等
	int nCompare = strcmp(s_CUI_ID_FRAME_Storage.GetItem_PrePWD(),s_CUI_ID_FRAME_Storage.GetItem_LastPWD());
	if(nCompare == 0)
	{
		if (thePlayerRole.IsLockNumLimit())
		{
			return false;
		}

		thePlayerRole.m_bag.SetItemProperty(s_CUI_ID_FRAME_pack_ex.GetDstIndex(),true);
		strcpy(thePlayerRole.szItem_PWD,s_CUI_ID_FRAME_Storage.GetItem_PrePWD()); 
		s_CUI_ID_FRAME_Storage.SetInUIFrameLock(false);
		s_CUI_ID_FRAME_Storage.Refeash();
		s_CUI_ID_FRAME_PACK.Refeash();
	}
	else
	{
		//两次输入的密码不一样！
		s_CUI_ID_FRAME_Storage.SetInUIFrameLock(false);
		return false;
	}
	return true;
	unguard;
}
bool ItemLock_Pack_ex(const char* szInputData, void *pData)
{
	guardfunc;	
	s_CUI_ID_FRAME_Storage.SetItem_PrePWD(szInputData);
	return true;
	unguard;
}
bool ItemLock_DefCallBackFun_Pack_ex(const bool bPressYesButton, void *pData )
{
	guardfunc;
	return false;
	unguard;
}
bool ItemUnLock_Pack_ex(const char* szInputData, void *pData)
{
	guardfunc;

    if ( thePlayerRole.m_bag.IsHaveItem(s_CUI_ID_FRAME_pack_ex.GetDstIndex()) == false )
        return false;
	SCharItem stItem;
	//如果物品已经加锁 return
	thePlayerRole.m_bag.GetItem( s_CUI_ID_FRAME_pack_ex.GetDstIndex(), &stItem );

	s_CUI_ID_FRAME_Storage.SetItem_PWD( szInputData );
	int nCmpPwd = strcmp(s_CUI_ID_FRAME_Storage.GetItem_PWD(),thePlayerRole.szItem_PWD);
	//如果密码正确
	if(nCmpPwd == 0 )
	{
		thePlayerRole.m_bag.SetItemProperty(s_CUI_ID_FRAME_pack_ex.GetDstIndex(),false);
		s_CUI_ID_FRAME_Storage.SetInUIFrameUnLock(false);
		s_CUI_ID_FRAME_Storage.Refeash();
		s_CUI_ID_FRAME_PACK.Refeash();
	}
	else
		//如果密码错误
	{
		s_CUI_ID_FRAME_Storage.SetInUIFrameUnLock(false);
		return false;		
	}
	return false;
	unguard;
}
bool IconOnClick_Pack_ex( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{	
	guardfunc;
	int index = s_CUI_ID_FRAME_pack_ex.GetItemIndexByListImg(pItem);
	if( index == -1 )
		return false;
	unsigned int nWhichItemIndex = ITEM_PACK_OLD + index;
	SCharItem stItem;
	if ( thePlayerRole.m_bag.IsHaveItem(nWhichItemIndex) == false )
		return false;
	//如果物品已经加锁 return
	thePlayerRole.m_bag.GetItem( nWhichItemIndex, &stItem );
	//物品加锁
	if(s_CUI_ID_FRAME_Storage.GetInUIFrameLock() || s_CUI_ID_FRAME_PACK.GetInUIFrameLock())
	{
		ItemDefine::SItemCommon *pCheckItem = GettheItemDetail().GetItemByID(pItem->m_pkIconInfo->Id());
		if(!pCheckItem->bIsCanLocked)
		{ 
			return false;	
		}

        // 统一接口         added by zhuomeng.hu		[12/30/2010]
        if( !CPackItemEnableManager::Instance()->IsPackItemEnable( &thePlayerRole.m_bag, nWhichItemIndex) )
		{
			return false;	
		}
		if (thePlayerRole.IsLockNumLimit())
		{
			return false;
		}

		if(!stItem.storageinfo.bIsLocked)
		{
			s_CUI_ID_FRAME_pack_ex.SetDstIndex(nWhichItemIndex);
			return true;
		}
		else
		{	
			s_CUI_ID_FRAME_Storage.SetInUIFrameLock(false);
			s_CUI_ID_FRAME_PACK.SetInUIFrameLock(false);
			theMouseManager.SetUICursor(MouseManager::Type_Arrow);
			return false;
		}
	}
	else if(s_CUI_ID_FRAME_Storage.GetInUIFrameUnLock() || s_CUI_ID_FRAME_PACK.GetInUIFrameUnLock())//物品解锁
	{
		//如果物品已经未处于lock状态则 return
		if(stItem.storageinfo.bIsLocked)
		{
			s_CUI_ID_FRAME_pack_ex.SetDstIndex(nWhichItemIndex);
			//光标置回原来的状态
			theMouseManager.SetUICursor(MouseManager::Type_Arrow);
			return true;	
		}
		else
		{
			s_CUI_ID_FRAME_PACK.SetInUIFrameUnLock(false);
			s_CUI_ID_FRAME_Storage.SetInUIFrameUnLock(false);
			theMouseManager.SetUICursor(MouseManager::Type_Arrow);
			return false;
		}
	}
	else
	{
		return false;

	}
	return false;
	unguard;
}
// ListImg / ListEx
bool CUI_ID_FRAME_pack_ex::ID_LISTIMG_pack_exOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{
	guardfunc;
	if( !m_pID_FRAME_pack_ex )
		return false;
	return false;
	unguard;
}
bool CUI_ID_FRAME_pack_ex::ID_LISTIMG_pack_exOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_pack_ex )
		return false;
	return false;
}
bool CUI_ID_FRAME_pack_ex::ID_LISTIMG_pack_exOnIconRDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_pack_ex )
		return false;
	return false;
}
// Button
bool CUI_ID_FRAME_pack_ex::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_pack_ex )
		return false;
	SetVisable( false );
	return true;
}

// 装载UI
bool CUI_ID_FRAME_pack_ex::_LoadUI()
{
	guardfunc;
    DWORD dwResult = theUiManager.AddFrame( "data\\ui\\Pack_Ex.meui", false,  UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\Pack_Ex.UI]失败")
			return false;
	}
	return DoControlConnect();
	unguard;
}

// 关连控件
bool CUI_ID_FRAME_pack_ex::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_pack_ex, s_CUI_ID_FRAME_pack_exOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_pack_ex, s_CUI_ID_FRAME_pack_exOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_pack_ex, ID_LISTIMG_pack_ex, s_CUI_ID_FRAME_pack_exID_LISTIMG_pack_exOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_pack_ex, ID_LISTIMG_pack_ex, s_CUI_ID_FRAME_pack_exID_LISTIMG_pack_exOnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_pack_ex, ID_LISTIMG_pack_ex, s_CUI_ID_FRAME_pack_exID_LISTIMG_pack_exOnIconRDBClick );
	theUiManager.OnButtonClick( ID_FRAME_pack_ex, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_pack_exID_BUTTON_CLOSEOnButtonClick );

	m_pID_FRAME_pack_ex = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_pack_ex );
	m_pID_PICTURE_picBacEnable = (ControlPicture*)theUiManager.FindControl( ID_FRAME_pack_ex, ID_PICTURE_picBacEnable );
	m_pID_PICTURE_picBacDisable = (ControlPicture*)theUiManager.FindControl( ID_FRAME_pack_ex, ID_PICTURE_picBacDisable );
	m_pID_LISTIMG_pack_ex = (ControlListImage*)theUiManager.FindControl( ID_FRAME_pack_ex, ID_LISTIMG_pack_ex );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_pack_ex, ID_BUTTON_CLOSE );
	m_pID_PICTURE_picBacDisableRow = (ControlPicture*)theUiManager.FindControl( ID_FRAME_pack_ex, ID_PICTURE_picBacDisableRow );

	assert( m_pID_FRAME_pack_ex );
	m_pID_FRAME_pack_ex->SetVisable( false );
	assert( m_pID_PICTURE_picBacEnable );
	assert( m_pID_PICTURE_picBacDisable );
	assert( m_pID_LISTIMG_pack_ex );
	m_pID_LISTIMG_pack_ex->SetScrollBarEnable( false );
	m_pID_LISTIMG_pack_ex->SetEnableRowCnt( PACKEX_ROW_COUNT );
    m_pID_LISTIMG_pack_ex->SetButtonClickFun(IconOnClick_Pack_ex);
	m_pID_LISTIMG_pack_ex->SetShiftLBClickFun( IconOnShiftLBClick );
	m_pID_FRAME_pack_ex->SetFrameMove( OnFrameMoveFun );
	m_pID_FRAME_pack_ex->SetOnClickFun( UIPackEx_FrameClick );
	assert( m_pID_BUTTON_CLOSE );

	return true;

	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_pack_ex::_UnLoadUI()
{
	m_pID_FRAME_pack_ex = NULL;
	m_pID_PICTURE_picBacEnable = NULL;
	m_pID_PICTURE_picBacDisable = NULL;
	m_pID_LISTIMG_pack_ex = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_PICTURE_picBacDisableRow = NULL;

    return theUiManager.RemoveFrame( "data\\ui\\Pack_Ex.meui" );
}
// 是否可视
bool CUI_ID_FRAME_pack_ex::_IsVisable()
{
	if( !m_pID_FRAME_pack_ex )
		return false;
	return m_pID_FRAME_pack_ex->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_pack_ex::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pID_FRAME_pack_ex )
		return;
		
	m_pID_FRAME_pack_ex->SetVisable( bVisable );
	unguard;
}

void CUI_ID_FRAME_pack_ex::setPicBackgroupPos()
{
	guardfunc;
	const int nRowItemCount = 7;	// 每行格子数
	const int nRowCount = 12;		// 行数
	const int nItemSize = 36;		// 格子的高度
	int nActiveCount = thePlayerRole.m_bag.GetNowBagSize() - ITEM_PACK_OLD;
	if( nActiveCount < 0 )
		return;
	int nRow = nActiveCount/nRowItemCount;
	int nCount = nActiveCount%nRowItemCount;
	if ( nCount != 0 )
	{
		nRow += 1;
	}
	RECT rc;
	m_pID_LISTIMG_pack_ex->SetHeight( nRow*nItemSize );
	m_pID_LISTIMG_pack_ex->SetHeightShowMaxCnt( nRow );
	m_pID_LISTIMG_pack_ex->SetEnableRowCnt( nRow );
	m_pID_LISTIMG_pack_ex->GetRealRect( &rc );
	//
	if ( nCount != 0 )
	{
		m_pID_PICTURE_picBacDisableRow->SetVisable( true );
		m_pID_PICTURE_picBacDisableRow->SetWidth( (nRowItemCount-nCount)*nItemSize );
		m_pID_PICTURE_picBacDisableRow->SetXPos( rc.left + nCount*nItemSize );
		m_pID_PICTURE_picBacDisableRow->SetYPos( rc.bottom - nItemSize );
		m_pID_PICTURE_picBacDisableRow->GetRealRect( &rc );
	}
	else
	{
		m_pID_PICTURE_picBacDisableRow->SetVisable( false );
	}
	//
	if ( nRow != nRowCount )
	{
		m_pID_PICTURE_picBacDisable->SetVisable( true );
		m_pID_PICTURE_picBacDisable->SetHeight( (nRowCount-nRow)*nItemSize );
		m_pID_PICTURE_picBacDisable->SetYPos( rc.bottom );
	}
	else
	{
		m_pID_PICTURE_picBacDisable->SetVisable( false );
	}
	unguard;
}

void CUI_ID_FRAME_pack_ex::SetPos(int x, int y )
{
	guardfunc;

	RECT rc;
	if( s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag) )
		s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag)->GetRealRect( &rc );
	m_pID_FRAME_pack_ex->SetPos( rc.right, rc.top );

	unguard;
}
void CUI_ID_FRAME_pack_ex::IconOnShiftLBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;

	if( pItem->IsNull() )
		return;

	ItemDefine::SItemCommon *pDetail = GettheItemDetail().GetItemByID( pItem->m_pkIconInfo->Id() );
	if( pDetail == NULL )
		return;

	int index = ITEM_PACK_OLD + s_CUI_ID_FRAME_pack_ex.m_pID_LISTIMG_pack_ex->GetItemIndex( pItem );
	SCharItem stItem;
	if( !thePlayerRole.m_bag.GetItem( index, &stItem ) )
        return;
	{
		CommonChatFrame::GetActiveChatFrame()->addHyberText( pDetail->GetItemName(), 
			stItem.itembaseinfo.nOnlyInt, stItem.itembaseinfo.ustItemID );
	}

	unguard;
}
void CUI_ID_FRAME_pack_ex::OnFrameMoveFun( ControlObject* pSender )
{
	guardfunc;
	unguard;
}
bool CUI_ID_FRAME_pack_ex::UIPackEx_FrameClick( ControlObject* pSender )
{
	guardfunc;
	if( s_CUI_ID_FRAME_PACK.GetFrame() )
		theUiManager.ToTop( s_CUI_ID_FRAME_PACK.GetFrame(), NULL, 1 );
	theUiManager.Compositor();
	return true;
	unguard;
}

int CUI_ID_FRAME_pack_ex::GetItemIndexByListImg( ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_pack_ex || !pItem )
		return -1;
	
	return m_pID_LISTIMG_pack_ex->GetItemIndex(pItem);
}