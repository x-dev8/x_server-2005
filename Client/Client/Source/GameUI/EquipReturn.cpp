/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\EquipReturn.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "EquipReturn.h"
#include "Pack.h"
#include "NetworkInput.h"
#include "PlayerRole.h"
#include "Core/Name.h"
#include "XmlStringLanguage.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "MeUI/ExpressionManager.h"
#include "ScreenInfoManager.h"
#include "color_config.h"
#include "IconManagerClient.h"
#include "Common.h"
#include "NpcShop.h"
CUI_ID_FRAME_EquipReturn s_CUI_ID_FRAME_EquipReturn;
MAP_FRAME_RUN( s_CUI_ID_FRAME_EquipReturn, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_EquipReturn, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipReturn, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipReturn, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipReturn, ID_BUTTON_OkOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_EquipReturn, ID_LISTIMG_EquipOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipReturn, ID_LISTIMG_EquipOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipReturn, ID_LISTIMG_EquipOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_EquipReturn, ID_LISTIMG_EquipOnIconRButtonUp )
CUI_ID_FRAME_EquipReturn::CUI_ID_FRAME_EquipReturn()
{
	// Member
	m_pID_FRAME_EquipEvolve = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_LISTIMG_Equip = NULL;
	m_pID_PICTURE_StarEffect = NULL;
	m_pID_TEXT_ReturnMoney = NULL;

}
	// Frame
	bool CUI_ID_FRAME_EquipReturn::OnFrameRun()
	{
		if (!OnDirty())
		{
			return true;
		}
		return true;
	}
	bool CUI_ID_FRAME_EquipReturn::OnFrameRender()
	{
		OnRender();
		return true;
	}
	// Button
	bool CUI_ID_FRAME_EquipReturn::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
	{
		SetVisable( false );
		return true;
	}
	// Button
	bool CUI_ID_FRAME_EquipReturn::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
	{
		SetVisable( false );
		return true;
	}
	// Button
	bool CUI_ID_FRAME_EquipReturn::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
	{
		OnOkClick();
		return true;
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_EquipReturn::ID_LISTIMG_EquipOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		SCharItem* psItem = (SCharItem*)pItemDrag->m_pkIconInfo->GetData();
		if (!psItem)
		{
			return false;
		}
		if (psItem->equipdata.quality < ItemDefine::EQL_Golden)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eWarning_Recycle_GoldItem) );
			return false;
		}
// 		ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pListImg->m_pkIconInfo->GetItemId() );
// 		switch ( pItemCommon->costType )
// 		{
// 		case ItemDefine::CT_Reputation:
// 		case ItemDefine::CT_Exploit:
// 		case ItemDefine::CT_GuildOffer:
// 		case ItemDefine::CT_Item:
// 			break;;
// 		default:
// 			{
// 				GetShowScreenText() ->AddInfo(theXmlString.GetString(eWarning_Recycle_ErrorItem),Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW);
// 				return false;
// 
// 			}
// 		}
		OnEquipDragOn(pItemDrag,pSender);
		return false;
	}
	bool CUI_ID_FRAME_EquipReturn::ID_LISTIMG_EquipOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_EquipReturn::ID_LISTIMG_EquipOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_EquipReturn::ID_LISTIMG_EquipOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		ClearEquip();
		return false;
	}

	// 装载UI
bool CUI_ID_FRAME_EquipReturn::_LoadUI()
	{
		DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\EquipReturn.MEUI" , false, UI_Render_LayerThree);
		if ( dwResult == 0 )
		{
			MESSAGE_BOX("读取文件[Data\\UI\\EquipReturn.MEUI]失败")
			return false;
		}
		return DoControlConnect();
	}
	// 关连控件
	bool CUI_ID_FRAME_EquipReturn::DoControlConnect()
	{
		theUiManager.OnFrameRun( ID_FRAME_EquipReturn, s_CUI_ID_FRAME_EquipReturnOnFrameRun );
		theUiManager.OnFrameRender( ID_FRAME_EquipReturn, s_CUI_ID_FRAME_EquipReturnOnFrameRender );
theUiManager.OnButtonClick( ID_FRAME_EquipReturn, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_EquipReturnID_BUTTON_CLOSEOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_EquipReturn, ID_BUTTON_Cancel, s_CUI_ID_FRAME_EquipReturnID_BUTTON_CancelOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_EquipReturn, ID_BUTTON_Ok, s_CUI_ID_FRAME_EquipReturnID_BUTTON_OkOnButtonClick );
theUiManager.OnIconDragOn( ID_FRAME_EquipReturn, ID_LISTIMG_Equip, s_CUI_ID_FRAME_EquipReturnID_LISTIMG_EquipOnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_EquipReturn, ID_LISTIMG_Equip, s_CUI_ID_FRAME_EquipReturnID_LISTIMG_EquipOnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_EquipReturn, ID_LISTIMG_Equip, s_CUI_ID_FRAME_EquipReturnID_LISTIMG_EquipOnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_EquipReturn, ID_LISTIMG_Equip, s_CUI_ID_FRAME_EquipReturnID_LISTIMG_EquipOnIconRButtonUp );

		m_pID_FRAME_EquipEvolve = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_EquipReturn );
		m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_EquipReturn, ID_BUTTON_CLOSE );
		m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_EquipReturn, ID_BUTTON_Cancel );
		m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_EquipReturn, ID_BUTTON_Ok );
		m_pID_LISTIMG_Equip = (ControlListImage*)theUiManager.FindControl( ID_FRAME_EquipReturn, ID_LISTIMG_Equip );
		m_pID_PICTURE_StarEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EquipReturn, ID_PICTURE_StarEffect );
		m_pID_TEXT_ReturnMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipReturn, ID_TEXT_ReturnMoney );
		assert( m_pID_FRAME_EquipEvolve );
		assert( m_pID_BUTTON_CLOSE );
		assert( m_pID_BUTTON_Cancel );
		assert( m_pID_BUTTON_Ok );
		assert( m_pID_LISTIMG_Equip );
		assert( m_pID_PICTURE_StarEffect );
		assert( m_pID_TEXT_ReturnMoney );

		m_pID_TEXT_ReturnMoney->Clear();
		m_pID_FRAME_EquipEvolve->SetOnVisibleChangedFun( OnVisibleChange );
		EquipEvolveIntialize();

		SetDirty( true );
		return true;
	}
	// 卸载UI
bool CUI_ID_FRAME_EquipReturn::_UnLoadUI()
	{
		ResetEquipEvolve();
		m_pID_FRAME_EquipEvolve = NULL;
		return theUiManager.RemoveFrame( "Data\\UI\\EquipReturn.MEUI" );
	}

void CUI_ID_FRAME_EquipReturn::OnVisibleChange( ControlObject* pUIObject )
{
	s_CUI_ID_FRAME_EquipReturn.SetDirty( true );
	s_CUI_ID_FRAME_EquipReturn.ClearEquip();	
	s_CUI_ID_FRAME_EquipReturn.RefreshAllBagEnable();

}

void CUI_ID_FRAME_EquipReturn::SendEvolveMsg()
{
	MsgItemReclaim itemReclaim;
	itemReclaim.nCount = 1;
	itemReclaim.nPackIndex = m_stEquipBagIndex;
	itemReclaim.nGuid = m_stEquipBagGuid;
	itemReclaim.nItemBagType = BT_NormalItemBag;
	GettheNetworkInput().SendMsg( &itemReclaim );
}

void CUI_ID_FRAME_EquipReturn::ClearEquip()
{
	m_bEquipBagEnable = true;				
	m_pID_LISTIMG_Equip->Clear();
	m_stEquipBagGuid = 0;
	m_pID_TEXT_ReturnMoney->Clear();
	SetDirty(true);
}

void CUI_ID_FRAME_EquipReturn::ResetUIObjects()
{
	EquipEvolveUI::ResetUIObjects();
	m_pID_TEXT_ReturnMoney = NULL;
}

void CUI_ID_FRAME_EquipReturn::_RefreshEquipInfo( ControlIconDrag::S_ListImg* pListImg )
{
	EquipEvolveUI::_RefreshEquipInfo(pListImg);
	SCharItem* psItem = (SCharItem*)pListImg->m_pkIconInfo->GetData();
	int nCostReturn = theNpcShop.GetPlayerItemReclaimCost(psItem,1);

	ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( pListImg->m_pkIconInfo->GetItemId() );
	std::stringstream str;
	std::string text = "";
	switch ( pItem->costType )
	{
	case ItemDefine::CT_Reputation:
		{
			str << nCostReturn << "#98 ";
			text = str.str();
		}
		break;
	case ItemDefine::CT_Exploit:
		{
			str << nCostReturn << "#99 ";
			text = str.str();
		}
		break;
	case ItemDefine::CT_GuildOffer:
		{
			str << nCostReturn << "#80 ";
			text = str.str();
		}
		break;
	case ItemDefine::CT_Item:
		{
			thePlayerRole.GetGSCStringFromMoney(nCostReturn, text);
		}
		break;
	case ItemDefine::CT_Honour:
		{
			str << nCostReturn << "#110 ";
			text = str.str();
		}
		break;
	default:
		{ 
			return;
		}
		break;
	}
	ExpressionManager::Instance()->AddExpressionAni(text);
	m_pID_TEXT_ReturnMoney->SetText(text);
}

bool CUI_ID_FRAME_EquipReturn::UpdateGem()
{
	return true;
}

void CUI_ID_FRAME_EquipReturn::RefreshOkButton()
{
	if( !m_pID_FRAME_EquipEvolve )
		return;
	if(!IsVisable())
		return;

	m_pID_BUTTON_Ok->SetEnable( true );
	if( m_stEquipBagIndex == -1 )
	{
		m_pID_BUTTON_Ok->SetEnable( false );
		return;
	}

}

bool CUI_ID_FRAME_EquipReturn::OnOkClick()
{
	// 播放序列帧动画
	m_slideAnim.StartAnimation(HQ_TimeGetTime());
	m_bStartAnim = true;

	SendEvolveMsg();
	return true;
}