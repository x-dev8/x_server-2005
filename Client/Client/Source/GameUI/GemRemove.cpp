/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\GemRemove.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GemRemove.h"
#include "Common.h"
#include "IconManagerClient.h"
#include "GlobalDef.h"
#include "Pack.h"
#include "ScreenInfoManager.h"
#include "XmlStringLanguage.h"
#include "color_config.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "NetworkInput.h"
#include "ItemDetailConfig.h"
#include "ItemDetail.h"
#include "PackItemEnableManager.h"

CUI_ID_FRAME_GemRemove s_CUI_ID_FRAME_GemRemove;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GemRemove, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GemRemove, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_BUTTON_CLOSEOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_BUTTON_OkOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_Hole1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_Hole1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_Hole1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_Hole1OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_Hole2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_Hole2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_Hole2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_Hole2OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_Hole3OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_Hole3OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_Hole3OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_Hole3OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_Hole4OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_Hole4OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_Hole4OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_Hole4OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_ArmourOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_ArmourOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemRemove, ID_LISTIMG_ArmourOnIconRButtonUp )
CUI_ID_FRAME_GemRemove::CUI_ID_FRAME_GemRemove()
{
	// Member
	m_pID_FRAME_EquipEvolve = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_TEXT_Tip2 = NULL;
	m_pID_TEXT_TipAllDone = NULL;
	m_pID_PICTURE_Open1 = NULL;
	m_pID_PICTURE_Open2 = NULL;
	m_pID_PICTURE_Open3 = NULL;
	m_pID_PICTURE_Open4 = NULL;
	m_pID_LISTIMG_Hole1 = NULL;
	m_pID_LISTIMG_Hole2 = NULL;
	m_pID_LISTIMG_Hole3 = NULL;
	m_pID_LISTIMG_Hole4 = NULL;
	m_pID_PICTURE_Lock1 = NULL;
	m_pID_PICTURE_Lock2 = NULL;
	m_pID_PICTURE_Lock3 = NULL;
	m_pID_PICTURE_Lock4 = NULL;
	m_pID_PICTURE_Begin = NULL;
	m_pID_LISTIMG_Equip = NULL;
	m_pID_PICTURE_StarEffect = NULL;
	m_pID_TEXT_EquipName = NULL;
	m_pID_TEXT_MaterialName = NULL;
	m_pID_TEXT_Gem1_Name = NULL;
	m_pID_TEXT_Gem2_Name = NULL;

	m_SelectGemIndex = -1;

}
	// Frame
	bool CUI_ID_FRAME_GemRemove::OnFrameRun()
	{
 		if (!OnDirty())
 		{
 			return true;
 		}
		return true;
	}
	bool CUI_ID_FRAME_GemRemove::OnFrameRender()
	{
		OnRender();
		return true;
	}
	// Button
	bool CUI_ID_FRAME_GemRemove::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
	{
		SetVisable(false);
		return true;
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	// Button
	bool CUI_ID_FRAME_GemRemove::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
	{
		SetVisable(false);
		return true;
	}
	// Button
	bool CUI_ID_FRAME_GemRemove::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
	{
		OnOkClick();
		return true;
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_Hole1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_Hole1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_Hole1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		SelectGem(0,pItem);
		return false;
	}
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_Hole1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_Hole2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_Hole2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_Hole2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		SelectGem(1,pItem);
		return false;
	}
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_Hole2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_Hole3OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_Hole3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_Hole3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		SelectGem(2,pItem);
		return false;
	}
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_Hole3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_Hole4OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_Hole4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_Hole4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		SelectGem(3,pItem);
		return false;
	}
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_Hole4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		if( !m_pID_FRAME_EquipEvolve )
			return false;
		if( !pItemDrag )
			return false;

		ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
		if( !pItemCommon )
			return false;

		if(!s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) && !s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender))
			return false;

		ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
		if (/*pCanEquip->ustEquipType == ItemDefine::equip_AecorativeClothing*/pCanEquip->bFashion)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString(eText_GemRemove_ErrorItem) );
			return false;
		}
		if ( pItemCommon->ucItemType != ItemDefine::ITEMTYPE_WEAPON &&
			pItemCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString(eText_GemRemove_ErrorItem) );
			return false;
		}
		if (!_IsGemExist(pItemDrag))
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString(eText_GemRemove_NoGem) );
			return false;
		}

		OnEquipDragOn(pItemDrag,pSender);
		ShowItemName(m_pID_TEXT_EquipName, pItemDrag);
		return false;
	}
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemRemove::ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		ClearEquip();
		return false;
	}

	// 装载UI
bool CUI_ID_FRAME_GemRemove::_LoadUI()
	{
		DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GemRemove.MEUI", false, UI_Render_LayerThree );
		if ( dwResult == 0 )
		{
			MESSAGE_BOX("读取文件[Data\\UI\\GemRemove.MEUI]失败")
			return false;
		}
		return DoControlConnect();
	}
	// 关连控件
	bool CUI_ID_FRAME_GemRemove::DoControlConnect()
	{
		theUiManager.OnFrameRun( ID_FRAME_GemRemove, s_CUI_ID_FRAME_GemRemoveOnFrameRun );
		theUiManager.OnFrameRender( ID_FRAME_GemRemove, s_CUI_ID_FRAME_GemRemoveOnFrameRender);
		theUiManager.OnButtonClick( ID_FRAME_GemRemove, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_GemRemoveID_BUTTON_CLOSEOnButtonClick );
		theUiManager.OnIconDragOn( ID_FRAME_GemRemove, ID_LISTIMG_Material, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_MaterialOnIconDragOn );
		theUiManager.OnIconLDBClick( ID_FRAME_GemRemove, ID_LISTIMG_Material, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_MaterialOnIconLDBClick );
		theUiManager.OnIconButtonClick( ID_FRAME_GemRemove, ID_LISTIMG_Material, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_MaterialOnIconButtonClick );
		theUiManager.OnIconRButtonUp( ID_FRAME_GemRemove, ID_LISTIMG_Material, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_MaterialOnIconRButtonUp );
		theUiManager.OnButtonClick( ID_FRAME_GemRemove, ID_BUTTON_Cancel, s_CUI_ID_FRAME_GemRemoveID_BUTTON_CancelOnButtonClick );
		theUiManager.OnButtonClick( ID_FRAME_GemRemove, ID_BUTTON_Ok, s_CUI_ID_FRAME_GemRemoveID_BUTTON_OkOnButtonClick );
		theUiManager.OnIconDragOn( ID_FRAME_GemRemove, ID_LISTIMG_Hole1, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_Hole1OnIconDragOn );
		theUiManager.OnIconLDBClick( ID_FRAME_GemRemove, ID_LISTIMG_Hole1, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_Hole1OnIconLDBClick );
		theUiManager.OnIconButtonClick( ID_FRAME_GemRemove, ID_LISTIMG_Hole1, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_Hole1OnIconButtonClick );
		theUiManager.OnIconRButtonUp( ID_FRAME_GemRemove, ID_LISTIMG_Hole1, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_Hole1OnIconRButtonUp );
		theUiManager.OnIconDragOn( ID_FRAME_GemRemove, ID_LISTIMG_Hole2, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_Hole2OnIconDragOn );
		theUiManager.OnIconLDBClick( ID_FRAME_GemRemove, ID_LISTIMG_Hole2, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_Hole2OnIconLDBClick );
		theUiManager.OnIconButtonClick( ID_FRAME_GemRemove, ID_LISTIMG_Hole2, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_Hole2OnIconButtonClick );
		theUiManager.OnIconRButtonUp( ID_FRAME_GemRemove, ID_LISTIMG_Hole2, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_Hole2OnIconRButtonUp );
		theUiManager.OnIconDragOn( ID_FRAME_GemRemove, ID_LISTIMG_Hole3, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_Hole3OnIconDragOn );
		theUiManager.OnIconLDBClick( ID_FRAME_GemRemove, ID_LISTIMG_Hole3, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_Hole3OnIconLDBClick );
		theUiManager.OnIconButtonClick( ID_FRAME_GemRemove, ID_LISTIMG_Hole3, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_Hole3OnIconButtonClick );
		theUiManager.OnIconRButtonUp( ID_FRAME_GemRemove, ID_LISTIMG_Hole3, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_Hole3OnIconRButtonUp );
		theUiManager.OnIconDragOn( ID_FRAME_GemRemove, ID_LISTIMG_Hole4, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_Hole4OnIconDragOn );
		theUiManager.OnIconLDBClick( ID_FRAME_GemRemove, ID_LISTIMG_Hole4, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_Hole4OnIconLDBClick );
		theUiManager.OnIconButtonClick( ID_FRAME_GemRemove, ID_LISTIMG_Hole4, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_Hole4OnIconButtonClick );
		theUiManager.OnIconRButtonUp( ID_FRAME_GemRemove, ID_LISTIMG_Hole4, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_Hole4OnIconRButtonUp );
		theUiManager.OnIconDragOn( ID_FRAME_GemRemove, ID_LISTIMG_Armour, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_ArmourOnIconDragOn );
		theUiManager.OnIconLDBClick( ID_FRAME_GemRemove, ID_LISTIMG_Armour, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_ArmourOnIconLDBClick );
		theUiManager.OnIconButtonClick( ID_FRAME_GemRemove, ID_LISTIMG_Armour, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_ArmourOnIconButtonClick );
		theUiManager.OnIconRButtonUp( ID_FRAME_GemRemove, ID_LISTIMG_Armour, s_CUI_ID_FRAME_GemRemoveID_LISTIMG_ArmourOnIconRButtonUp );

		m_pID_FRAME_EquipEvolve = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GemRemove );
		m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_BUTTON_CLOSE );
		m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_TEXT_Money );
		m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_LISTIMG_Material );
		m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_BUTTON_Cancel );
		m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_BUTTON_Ok );
		m_pID_TEXT_Tip2 = (ControlText*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_TEXT_Tip2 );
		m_pID_TEXT_Tip1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_TEXT_Tip1 );
		m_pID_TEXT_TipAllDone = (ControlText*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_TEXT_TipAllDone );
		m_pID_PICTURE_Open1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_PICTURE_Open1 );
		m_pID_PICTURE_Open2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_PICTURE_Open2 );
		m_pID_PICTURE_Open3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_PICTURE_Open3 );
		m_pID_PICTURE_Open4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_PICTURE_Open4 );
		m_pID_LISTIMG_Hole1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_LISTIMG_Hole1 );
		m_pID_LISTIMG_Hole2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_LISTIMG_Hole2 );
		m_pID_LISTIMG_Hole3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_LISTIMG_Hole3 );
		m_pID_LISTIMG_Hole4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_LISTIMG_Hole4 );
		m_pID_PICTURE_Lock1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_PICTURE_Lock1 );
		m_pID_PICTURE_Lock2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_PICTURE_Lock2 );
		m_pID_PICTURE_Lock3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_PICTURE_Lock3 );
		m_pID_PICTURE_Lock4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_PICTURE_Lock4 );
		m_pID_PICTURE_Begin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_PICTURE_Begin );
		m_pID_LISTIMG_Equip = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_LISTIMG_Armour );
		m_pID_PICTURE_StarEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_PICTURE_StarEffect );
		m_pID_TEXT_EquipName = (ControlText*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_TEXT_EquipName );
		m_pID_TEXT_MaterialName = (ControlText*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_TEXT_MaterialName );
		m_pID_TEXT_Gem1_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_TEXT_Gem1_Name );
		m_pID_TEXT_Gem2_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_GemRemove, ID_TEXT_Gem2_Name );

		assert( m_pID_FRAME_EquipEvolve );
		assert( m_pID_BUTTON_CLOSE );
		assert( m_pID_TEXT_Money );
		assert( m_pID_LISTIMG_Material );
		assert( m_pID_BUTTON_Cancel );
		assert( m_pID_BUTTON_Ok );
		assert( m_pID_TEXT_Tip2 );
		assert( m_pID_TEXT_TipAllDone );
		assert( m_pID_PICTURE_Open1 );
		assert( m_pID_PICTURE_Open2 );
		assert( m_pID_PICTURE_Open3 );
		assert( m_pID_PICTURE_Open4 );
		assert( m_pID_LISTIMG_Hole1 );
		assert( m_pID_LISTIMG_Hole2 );
		assert( m_pID_LISTIMG_Hole3 );
		assert( m_pID_LISTIMG_Hole4 );
		assert( m_pID_PICTURE_Lock1 );
		assert( m_pID_PICTURE_Lock2 );
		assert( m_pID_PICTURE_Lock3 );
		assert( m_pID_PICTURE_Lock4 );
		assert( m_pID_PICTURE_Begin );
		assert( m_pID_LISTIMG_Equip );
		assert( m_pID_PICTURE_StarEffect );
		assert( m_pID_TEXT_EquipName );
		assert( m_pID_TEXT_MaterialName );
		assert( m_pID_TEXT_Gem1_Name );
		assert( m_pID_TEXT_Gem2_Name );

		m_pID_FRAME_EquipEvolve->SetOnVisibleChangedFun( OnVisibleChange );
		InitializeGemBase();
		m_pID_TEXT_Tip1->SetVisable(false);
		m_pID_TEXT_Tip2->SetVisable(false);
		return true;
	}
	// 卸载UI
bool CUI_ID_FRAME_GemRemove::_UnLoadUI()
	{
		ResetEquipEvolve();
		m_pID_FRAME_EquipEvolve = NULL;
		return theUiManager.RemoveFrame( "Data\\UI\\GemRemove.MEUI" );
	}

void CUI_ID_FRAME_GemRemove::OnVisibleChange( ControlObject* pUIObject )
{
	s_CUI_ID_FRAME_GemRemove.SetDirty( true );
	s_CUI_ID_FRAME_GemRemove.ClearEquip();	
	s_CUI_ID_FRAME_GemRemove.RefreshAllBagEnable();

}
bool CUI_ID_FRAME_GemRemove::_IsVisable()
{
	if (!m_pID_FRAME_EquipEvolve)
	{
		return false;
	}
	return m_pID_FRAME_EquipEvolve->IsVisable();
}

void CUI_ID_FRAME_GemRemove::_SetVisable(bool bVisible)
{
	if (!m_pID_FRAME_EquipEvolve)
	{
		return ;
	}
	m_pID_FRAME_EquipEvolve->SetVisable(bVisible);
	OnSetVisable(bVisible);
}

bool CUI_ID_FRAME_GemRemove::IsEvolveAllDone( ControlIconDrag::S_ListImg * pImg )
{
	return !_IsGemExist(pImg);
}

void CUI_ID_FRAME_GemRemove::SendEvolveMsg()
{
	if (thePlayerRole.m_bagMaterial.GetNullItemCount() <= 0)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString( eText_MaterialPackFull ) );
		return;
	}
	
	MsgEquipEvolve msgEvolve;
	msgEvolve.nEvolveType = GetEvolveType();

	msgEvolve.nNormalBagIndex = m_stEquipBagIndex;
	msgEvolve.nNormalGuid      = m_stEquipBagGuid;

	msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType= m_shMaterialBagType[m_nSelectMaterialIndex];
	msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex = m_stMaterialIndex[m_nSelectMaterialIndex];
	msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid = m_n64MaterialGuid[m_nSelectMaterialIndex];
	msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].value = m_SelectGemIndex;

	msgEvolve.SendEquipMsg();
	//GettheNetworkInput().SendMsg( &msgEvolve );

}

bool CUI_ID_FRAME_GemRemove::ProcessAllDone( ControlIconDrag::S_ListImg * pImg )
{
	bool bRet = GemBaseUI::ProcessAllDone(pImg);
	if (bRet)
	{
		m_pID_TEXT_Tip1->SetVisable(false);
		m_pID_TEXT_Tip2->SetVisable(false);
	}
	m_pID_LISTIMG_Material->SetVisable(true);//在基类中会隐藏这个函数
	return bRet;
}

void CUI_ID_FRAME_GemRemove::TipVisible( bool IsMaterialExist )
{
	if (IsMaterialExist)
	{
		m_pID_TEXT_Tip2->SetVisable(false);
	}
	else
	{
		m_pID_TEXT_Tip2->SetVisable(true);
	}
	if (m_SelectGemIndex == -1)
	{
		m_pID_TEXT_Tip1->SetVisable(true);
	}
	else
	{
		m_pID_TEXT_Tip1->SetVisable(false);
	}

}

bool CUI_ID_FRAME_GemRemove::_IsGemExist(ControlIconDrag::S_ListImg * pImg)
{
	SCharItem* pItem = ((SCharItem*)pImg->m_pkIconInfo->GetData());
	if (NULL == pItem)
	{
		return false;
	}
	int nHole = pItem->equipdata.gemHoleCount;
	int nGemCount = 0;
	for (int i = 0; i < nHole; ++i)
	{
		if (pItem->equipdata.gemIds[i] != 0)
		{
			return true;
		}		
	}

	return false;
}

void CUI_ID_FRAME_GemRemove::ClearEquip()
{
	GemBaseUI::ClearEquip();
	m_SelectGemIndex = -1;
	for (int i = 0;i < m_nMaxHoleNum;++i)
	{
		m_HoledPic[i]->SetVisable(false);
		m_UnHolePic[i]->SetVisable(true);
	}
	m_pID_TEXT_Tip1->SetVisable(false);
	m_pID_TEXT_Tip2->SetVisable(false);
	m_pID_TEXT_TipAllDone->SetVisable(false);

	m_pID_TEXT_EquipName->SetText("");
	m_pID_TEXT_MaterialName->SetText("");
	m_pID_TEXT_Gem1_Name->SetText("");
	m_pID_TEXT_Gem2_Name->SetText("");
}

bool CUI_ID_FRAME_GemRemove::OnDirty()
{
	GemBaseUI::OnDirty();
	if (m_SelectGemIndex == -1)
	{
		m_pID_BUTTON_Ok->SetEnable( false );
	}
	return true;
}

bool CUI_ID_FRAME_GemRemove::SelectGem( int index , ControlIconDrag::S_ListImg* pGemItem)
{
	if (m_stEquipBagIndex == -1)
	{
		return false;
	}
	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	SCharItem* pItem = ((SCharItem*)pImg->m_pkIconInfo->GetData());
	if (pItem->equipdata.gemIds[index] == 0)
	{
		return false;
	}
	m_SelectGemIndex = index;
	SetSelectItem(pGemItem);
	RefreshNeedMoney();
	SetDirty(true);
	return true;	
}

void CUI_ID_FRAME_GemRemove::ResetUIObjects()
{
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Tip2 = NULL;
	m_pID_TEXT_Tip1 = NULL;
	m_SelectGemIndex = -1;
}

void CUI_ID_FRAME_GemRemove::_RefreshEquipInfo( ControlIconDrag::S_ListImg* pListImg )
{
	GemBaseUI::_RefreshEquipInfo(pListImg);
	m_SelectGemIndex = -1;
	SCharItem* pItem = ((SCharItem*)pListImg->m_pkIconInfo->GetData());
	if (NULL == pItem)
	{
		return ;
	}
	if (m_pID_TEXT_Gem1_Name && m_pID_TEXT_Gem2_Name)
	{
		m_pID_TEXT_Gem1_Name->SetText("");
		m_pID_TEXT_Gem2_Name->SetText("");
	}
	int nHole = pItem->equipdata.gemHoleCount;
	int nGemCount = 0;
	int nLastIndex = 0;
	for (int i = 0; i < nHole; ++i)
	{
		if (pItem->equipdata.gemIds[i] != 0)
		{
			++nGemCount;
			nLastIndex = i;
			if (i == 0)
				ShowGemName(m_pID_TEXT_Gem1_Name,pItem->equipdata.gemIds[i]);
			else if (i == 1)
				ShowGemName(m_pID_TEXT_Gem2_Name,pItem->equipdata.gemIds[i]);
		}		
	}
	if (nGemCount > 0)
	{
		if (nGemCount == 2)
			SelectGem(0,m_pID_LISTIMG_Hole[0]->GetItemByIndex(0));
		else
			SelectGem(nLastIndex,m_pID_LISTIMG_Hole[nLastIndex]->GetItemByIndex(0));
	}
	
}

int	CUI_ID_FRAME_GemRemove::GetEvolveMoneyCost()
{
	DWORD dwMoney = 0;
	if(!m_pID_FRAME_EquipEvolve)
		return dwMoney;

	ControlIconDrag::S_ListImg *pImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	if(!pImg)
		return dwMoney;

	SCharItem* pItem = ((SCharItem*)pImg->m_pkIconInfo->GetData());
	if(!pItem)
		return dwMoney;

	if (m_SelectGemIndex < 0 || m_SelectGemIndex >= SCharItem::EConstDefine_GemHoleMaxCount)
		return dwMoney;

	uint16	nGemID = 0;		
	nGemID= pItem->equipdata.gemIds[m_SelectGemIndex];
	if (nGemID == InvalidLogicNumber )
		return dwMoney;

	ItemDefine::SItemGem *pItemGemConfig = (ItemDefine::SItemGem *)GettheItemDetail().GetItemByID(nGemID);
	if(!pItemGemConfig)
		return dwMoney;

	dwMoney = pItemGemConfig->useCostMoney;
	return dwMoney;
}

bool CUI_ID_FRAME_GemRemove::IsMatchOther(ItemDefine::SCreateMaterial* pMaterial)
{
	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	if (!pImg || pImg->IsNull())
		return false;

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pImg->m_pkIconInfo->GetItemId() );
	if( !pItemCommon )
		return false;
	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if( !pCanEquip )
		return false;

	if (pMaterial->equipQuality == pCanEquip->ustLevel)
		return true;

	return false;
}

void CUI_ID_FRAME_GemRemove::ShowGemName(ControlText* pText, uint16 itemId)
{
	if (!pText )
		return;
	pText->SetText("");

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( itemId );
	if (!pItemCommon)
		return;
	ItemDefine::SItemGem* pGem = ( ItemDefine::SItemGem* )pItemCommon;

	// 一颗宝石2属性
	char szTemp[MAX_PATH] = {0};
	std::string strGemAttr;
	for( int j = 0; j < ItemDefine::SItemGem::CD_TypeCount; ++j )
	{
		strGemAttr = S_IconInfoHero::GetRandStringByType( pGem->type[j] );
		if( strGemAttr.empty() )
			continue;

		if( pGem->type[j] == RT_AddMoveSpeed )
		{
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%.2f", strGemAttr.c_str(), pGem->value[j].fValue );
			strGemAttr = szTemp;
			break;
		}
		else
		{
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", strGemAttr.c_str(), ( int )pGem->value[j].fValue );
			strGemAttr = szTemp;
			if( pGem->type[j] == RT_AddExpPer )
				strGemAttr += "%";
			break;
		}
	}

	pText->SetText(strGemAttr.c_str());
}

void CUI_ID_FRAME_GemRemove::ShowItemName(ControlText* pText, ControlIconDrag::S_ListImg* pItemDrag)
{
	if (!pText || !pItemDrag)
		return;
	pText->SetText("");

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if (!pItemCommon)
		return;

	char temp[128] = {0};
	sprintf(temp, "%s", pItemCommon->GetItemName());

	pText->SetText(temp);
}

bool CUI_ID_FRAME_GemRemove::UpdateGem()
{
	if (!m_pID_LISTIMG_Material)
		return false;

	//EquipEvolveUI::UpdateGem();
	int nMatchMaterialEnableCount = 0; 
	int nLastItemId = -1;
	if (m_nSelectMaterialIndex != -1)
	{
		nLastItemId = m_stMaterialIndex[m_nSelectMaterialIndex];
		m_nSelectMaterialIndex = -1;
	}
	for (int i = 0; i < m_nsMaxMaterialNum;++i)
	{
		// enable原材料的icon
		if( m_stMaterialIndex[i] != -1 )
		{
			m_n64MaterialGuid[i] = 0;

			// 刷背包物品 Enable 态统一流程     modified by zhuomeng.hu		[12/30/2010]
			CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stMaterialIndex[i], true );

			m_stMaterialIndex[i] = -1;
			m_shMaterialBagType[i] = -1;
		}
	}
	m_pID_LISTIMG_Material->Clear();
	ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( m_stEquipBagType, m_stEquipBagIndex );
	if( !pItemImg )
		return false;
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemImg->m_pkIconInfo->GetItemId() );
	if( !pItemCommon )
		return false;
	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if( !pCanEquip )
		return false;

	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
	if ( !pMe )
	{
		return false;
	}
	int nMeLevel = pMe->GetLevel();
	int nMatchMaterialCount = 0; 
	//int nMatchMaterialEnableCount = 0; 
	for (int i = 0; i < m_MatchMaterialArray.size(); ++i)
	{
		ItemDefine::SCreateMaterial* pMaterial = ( ItemDefine::SCreateMaterial* )GettheItemDetail().GetItemByID(m_MatchMaterialArray[i]);
		if( pMaterial->levelLowLimit <= pCanEquip->stEquipLevelReq && pMaterial->levelUpLimit >= pCanEquip->stEquipLevelReq //符合装备等级
			&& pMaterial->useLevel <= nMeLevel																				//符合人物等级
			&& ((pMaterial->equipQuality == 0) || (pMaterial->equipQuality == pCanEquip->ustLevel))							//符合装备品质
			&& pMaterial->CanEquipPart(pCanEquip->ustEquipType)																//符合部位需求
			&& IsMatchOther(pMaterial))																						//符合其他条件，比如打孔的孔数
		{
			int nBagIndex = -1;
			ControlIconDrag::S_ListImg * pListImgItem = RetriveMaterialImg(m_MatchMaterialArray[i],nBagIndex);
			ControlIconDrag::S_ListImg ImgItem;
			if (NULL == pListImgItem)
			{
				ImgItem.SetData(m_MatchMaterialArray[i],1,eIcon_Disable);
				pListImgItem = &ImgItem;
				m_pID_LISTIMG_Material->SetItem( pListImgItem, nMatchMaterialCount );
			}
			else
			{
				assert(nBagIndex != -1);
				m_stMaterialIndex[nMatchMaterialCount] = nBagIndex;
				m_n64MaterialGuid[nMatchMaterialCount] = pListImgItem->m_pkIconInfo->GetOnlyId();
				m_shMaterialBagType[nMatchMaterialCount] = BT_MaterialBag;
				m_pID_LISTIMG_Material->SetItem( pListImgItem, nMatchMaterialCount );
				ControlIconDrag::S_ListImg* pNewImg = m_pID_LISTIMG_Material->GetItemByIndex( nMatchMaterialCount );
				if (pNewImg)
				{
					pNewImg->m_pkIconInfo->Count() = pListImgItem->m_pkIconInfo->Count();
					pNewImg->m_eEnable = eIcon_Enable;
					m_nSelectMaterialIndex = nMatchMaterialCount;
					m_bMaterialBagEnable[nMatchMaterialCount] = false;
					++nMatchMaterialEnableCount;
				}
			}			
			++nMatchMaterialCount;
			if (nMatchMaterialCount >= m_nsMaxMaterialNum)
			{
				break;
			}
		}
	}
	

	TipVisible(nMatchMaterialEnableCount > 0);
	//RefreshAllBagEnable();
	RefreshNeedMoney();
	RefreshProbability();
	SetDirty( true );

	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Material->GetItemByIndex(0);
	if (!pImg || pImg->IsNull())
		return false;

	ShowItemName(m_pID_TEXT_MaterialName, pImg);
}