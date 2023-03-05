/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\策划文档\GivePresent.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GivePresent.h"
#include "UIMgr.h"
#include "ScreenInfoManager.h"
#include "XmlStringLanguage.h"
#include "NetworkInput.h"
#include "ItemDetail.h"
#include "color_config.h"
#include "PlayerRole.h"
#include "Pack.h"
#include "PackItemEnableManager.h"

CUI_ID_FRAME_GivePresent s_CUI_ID_FRAME_GivePresent;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GivePresent, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GivePresent, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GivePresent, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GivePresent, ID_BUTTON_helpOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GivePresent, ID_LISTIMG_ItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GivePresent, ID_LISTIMG_ItemOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GivePresent, ID_LISTIMG_ItemOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GivePresent, ID_LISTIMG_ItemOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GivePresent, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GivePresent, ID_BUTTON_CancelOnButtonClick )
CUI_ID_FRAME_GivePresent::CUI_ID_FRAME_GivePresent()
{
	// Member
	m_pID_FRAME_GivePresent = NULL;
	m_pID_PICTURE_RightTitle = NULL;
	m_pID_PICTURE_MiddleTitle = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_help = NULL;
	m_pID_PICTURE_ItemWall = NULL;
	m_pID_LISTIMG_Item = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_PICTURE_LeftTitle = NULL;
	m_pID_PICTURE_TitleWord = NULL;
	m_pID_TEXT_Explain = NULL;

	m_shTargetID = -1;
	m_iItemIndex = -1;
	m_n64ItemGuild = 0;
	m_iBagType = -1;
	m_iItemCount = 0;
	m_dwCDEndTime = 0;
}
// Frame
bool CUI_ID_FRAME_GivePresent::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GivePresent::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_GivePresent::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GivePresent )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_GivePresent::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GivePresent )
		return false;
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_GivePresent::ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_GivePresent )
		return false;
	if( !pSender )
		return false;

	ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
	int iBagType = s_CUI_ID_FRAME_PACK.GetBagType(pImageSender);
	if( iBagType != -1 )
	{
		int index = pImageSender->GetItemIndex( pItemDrag );
		if( index != -1 )
			PutItemFromPack(pSender, pItemDrag, iBagType, index);
	}
	return false;
}
bool CUI_ID_FRAME_GivePresent::ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_GivePresent )
		return false;
	return false;
}
bool CUI_ID_FRAME_GivePresent::ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_GivePresent )
		return false;
	return false;
}
bool CUI_ID_FRAME_GivePresent::ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_GivePresent )
		return false;
	ClearItem();
	m_pID_BUTTON_Ok->SetEnable(false);
	return false;
}
// Button
bool CUI_ID_FRAME_GivePresent::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GivePresent )
		return false;
	if( m_pID_BUTTON_Ok->IsEnable() && m_iItemIndex != -1 && m_shTargetID >= 0 && m_iItemCount > 0 )
	{
		if( m_dwCDEndTime > HQ_TimeGetTime() )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Present_SendFailed, theXmlString.GetString(eText_UseItemFailed_InCD) );
			return false;
		}
		MsgUseGoods msg;
		msg.ustItemIndex = m_iItemIndex;
		msg.nGuid = m_n64ItemGuild;
		msg.stDstChar = m_shTargetID;
		msg.ucItemBagType = (unsigned char)m_iBagType;
		msg.stItemCount = m_iItemCount;
		GettheNetworkInput().SendMsg( &msg );
		m_pID_BUTTON_Ok->SetEnable(false);
	}

	return true;
}
// Button
bool CUI_ID_FRAME_GivePresent::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GivePresent )
		return false;
	ClearItem();
	SetVisable(false);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_GivePresent::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GivePresent.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GivePresent.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GivePresent::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GivePresent, s_CUI_ID_FRAME_GivePresentOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GivePresent, s_CUI_ID_FRAME_GivePresentOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GivePresent, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_GivePresentID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GivePresent, ID_BUTTON_help, s_CUI_ID_FRAME_GivePresentID_BUTTON_helpOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_GivePresent, ID_LISTIMG_Item, s_CUI_ID_FRAME_GivePresentID_LISTIMG_ItemOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_GivePresent, ID_LISTIMG_Item, s_CUI_ID_FRAME_GivePresentID_LISTIMG_ItemOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_GivePresent, ID_LISTIMG_Item, s_CUI_ID_FRAME_GivePresentID_LISTIMG_ItemOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_GivePresent, ID_LISTIMG_Item, s_CUI_ID_FRAME_GivePresentID_LISTIMG_ItemOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_GivePresent, ID_BUTTON_Ok, s_CUI_ID_FRAME_GivePresentID_BUTTON_OkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GivePresent, ID_BUTTON_Cancel, s_CUI_ID_FRAME_GivePresentID_BUTTON_CancelOnButtonClick );

	m_pID_FRAME_GivePresent = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GivePresent );
	m_pID_PICTURE_RightTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GivePresent, ID_PICTURE_RightTitle );
	m_pID_PICTURE_MiddleTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GivePresent, ID_PICTURE_MiddleTitle );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GivePresent, ID_BUTTON_CLOSE );
	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_GivePresent, ID_BUTTON_help );
	m_pID_PICTURE_ItemWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GivePresent, ID_PICTURE_ItemWall );
	m_pID_LISTIMG_Item = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GivePresent, ID_LISTIMG_Item );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_GivePresent, ID_BUTTON_Ok );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_GivePresent, ID_BUTTON_Cancel );
	m_pID_PICTURE_LeftTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GivePresent, ID_PICTURE_LeftTitle );
	m_pID_PICTURE_TitleWord = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GivePresent, ID_PICTURE_TitleWord );
	m_pID_TEXT_Explain = (ControlText*)theUiManager.FindControl( ID_FRAME_GivePresent, ID_TEXT_Explain );
	assert( m_pID_FRAME_GivePresent );
	assert( m_pID_PICTURE_RightTitle );
	assert( m_pID_PICTURE_MiddleTitle );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_help );
	assert( m_pID_PICTURE_ItemWall );
	assert( m_pID_LISTIMG_Item );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_PICTURE_LeftTitle );
	assert( m_pID_PICTURE_TitleWord );
	assert( m_pID_TEXT_Explain );

	m_shTargetID = -1;
	m_iItemIndex = -1;
	m_n64ItemGuild = 0;
	m_iBagType = -1;
	m_iItemCount = 0;
	m_dwCDEndTime = 0;

	m_pID_FRAME_GivePresent->SetOnVisibleChangedFun(OnVisibleChanged);

	USE_SCRIPT( eUI_OBJECT_GivePresent, this );
	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GivePresent::_UnLoadUI()
{
	m_pID_FRAME_GivePresent = NULL;
	m_pID_PICTURE_RightTitle = NULL;
	m_pID_PICTURE_MiddleTitle = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_help = NULL;
	m_pID_PICTURE_ItemWall = NULL;
	m_pID_LISTIMG_Item = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_PICTURE_LeftTitle = NULL;
	m_pID_PICTURE_TitleWord = NULL;
	m_pID_TEXT_Explain = NULL;
	CLOSE_SCRIPT( eUI_OBJECT_GivePresent );
	return theUiManager.RemoveFrame( "Data\\UI\\GivePresent.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GivePresent::_IsVisable()
{
	if( !m_pID_FRAME_GivePresent )
		return false;
	return m_pID_FRAME_GivePresent->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GivePresent::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_GivePresent )
		return;
	m_pID_FRAME_GivePresent->SetVisable( bVisable );
	if( bVisable )
	{
		m_pID_BUTTON_Ok->SetEnable(false);
	}
	ClearItem();
}

bool CUI_ID_FRAME_GivePresent::SetTarget( short shPlayerID )
{
	if( !m_pID_FRAME_GivePresent )
		return false;

	if( shPlayerID < 0 )
		return false;

	m_shTargetID = shPlayerID;
	return true;
}

bool CUI_ID_FRAME_GivePresent::PutItemFromPack( ControlObject* pSender, ControlIconDrag::S_ListImg* pItemDrag, int iBagType, int iItemIndex )
{
	if( !m_pID_FRAME_GivePresent )
		return false;

	if( !pSender || !pItemDrag || !pItemDrag->m_pkIconInfo || iItemIndex < 0 )
		return false;

	int iItemId = pItemDrag->m_pkIconInfo->GetItemId();
	if( iItemId == InvalidLogicNumber )
		return false;

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( iItemId );
	if( !pItemCommon )
		return false;

	if( pItemCommon->byUserTarget != ItemDefine::eTargetFriend )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Present_SendFailed, theXmlString.GetString(eText_GivePresentFailed_ItemCannotGive) );
		return false;
	}

	// 原背包物品解锁
	EnableBagItem(true, m_iBagType, m_iItemIndex);

	m_iItemIndex = iItemIndex;
	m_iBagType = iBagType;
	m_n64ItemGuild = pItemDrag->m_pkIconInfo->GetOnlyId();
	m_iItemCount = pItemDrag->m_pkIconInfo->Count();
	m_dwCDEndTime = pItemDrag->m_dwStartTime + pItemDrag->m_dwPeriod;

	// 锁定包裹物品
	if( m_iItemIndex != -1 )
	{
		EnableBagItem(false, m_iBagType, m_iItemIndex);
		theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
	}

	// 显示物品
	ControlIconDrag::S_ListImg item = *pItemDrag;
	item.m_eEnable = eIcon_Enable;
	m_pID_LISTIMG_Item->Clear();
	m_pID_LISTIMG_Item->SetItem(&item, 0);

	m_pID_BUTTON_Ok->SetEnable(true);
	return true;
}

void CUI_ID_FRAME_GivePresent::EnableBagItem( bool bEnable, int iBagType, int iItemIndex )
{
	if( iItemIndex != -1 )
	{
        if( bEnable )
        {
            m_n64ItemGuild = 0;
        }
		switch (iBagType)
		{
		case BT_NormalItemBag:
			{
                // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
                CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, iItemIndex, true );
			}
			break;
		case BT_MaterialBag:
			{
                // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
                CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, iItemIndex, true );
			}
			break;
		case BT_TaskBag:
			{
                // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
                CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagTask, iItemIndex, true );
			}
			break;
		default:
			break;
		}
	}
}

void CUI_ID_FRAME_GivePresent::ClearItem()
{
	EnableBagItem(true, BT_NormalItemBag, m_iItemIndex);
	m_iItemIndex = -1;
	m_n64ItemGuild = 0;
	m_pID_LISTIMG_Item->Clear();
}

void CUI_ID_FRAME_GivePresent::OnFailed()
{
	if( !m_pID_FRAME_GivePresent )
		return;

	if( IsVisable() )
		m_pID_BUTTON_Ok->SetEnable(true);
}

void CUI_ID_FRAME_GivePresent::OnVisibleChanged( ControlObject* pSender )
{
	s_CUI_ID_FRAME_GivePresent.ClearItem();
}

bool CUI_ID_FRAME_GivePresent::IsPackItemBeUsing( __int64 nGuid )
{
    if( !IsVisable() || nGuid <= 0 )
        return false;

    if( m_n64ItemGuild == nGuid )
    {
        return true;
    }
    return false;
}
