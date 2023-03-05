/********************************************************************
Created by UIEditor.exe
FileName: E:\新建文件夹\3Guo_Client_02.05\Data\Ui\TransferStar.cpp
*********************************************************************/
#include <assert.h>
#include <math.h>
#include "MeUi/UiManager.h"
#include "TransferStar.h"
#include "Pack.h"
#include "UIMgr.h"
#include "PackItemEnableManager.h"
#include "ItemDetail.h"
#include "PlayerRole.h"
#include "XmlStringLanguage.h"
#include "Core/Name.h"
#include "ScreenInfoManager.h"
#include "NetworkInput.h"
#include "MessageDefine.h"
#include "StarLevelUpConfig.h"

#define DELAY_TIME 350

CUI_ID_FRAME_TransferStar s_CUI_ID_FRAME_TransferStar;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TransferStar, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TransferStar, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TransferStar, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TransferStar, ID_BUTTON_HELPOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_TransferStar, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_TransferStar, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TransferStar, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_TransferStar, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TransferStar, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TransferStar, ID_BUTTON_OkOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_TransferStar, ID_LISTIMG_SourceEquipOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_TransferStar, ID_LISTIMG_SourceEquipOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TransferStar, ID_LISTIMG_SourceEquipOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_TransferStar, ID_LISTIMG_SourceEquipOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_TransferStar, ID_LISTIMG_TargetEquipOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_TransferStar, ID_LISTIMG_TargetEquipOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TransferStar, ID_LISTIMG_TargetEquipOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_TransferStar, ID_LISTIMG_TargetEquipOnIconRButtonUp )
CUI_ID_FRAME_TransferStar::CUI_ID_FRAME_TransferStar()
{
	// Member
	m_pID_FRAME_TransferStar = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_TEXT_Tip2 = NULL;
	m_pID_TEXT_Tip1 = NULL;
	m_pID_LISTIMG_SourceEquip = NULL;
	m_pID_LISTIMG_TargetEquip = NULL;
	m_pID_TEXT_Success = NULL;
	m_pID_TEXT_Fail = NULL;
	m_pID_TEXT_SourceName = NULL;
	m_pID_TEXT_TargetName = NULL;
	m_pID_TEXT_MaterialName = NULL;

	m_status = EffectStatus_No;
	m_bAckMsg = false;
	m_SourceSender = NULL;
	m_TargetSender = NULL;
	m_MaterialSender = NULL;

	m_bSourceBound = false;
	m_bTargetBound = false;

}
// Frame
bool CUI_ID_FRAME_TransferStar::OnFrameRun()
{
	DWORD dwTimeNow = timeGetTime();
	switch (m_status)
	{
	case EffectStatus_Fail:
		if(m_pID_TEXT_Fail) m_pID_TEXT_Fail->SetVisable(true);
		if(m_pID_TEXT_Success) m_pID_TEXT_Success->SetVisable(false);
		if(dwTimeNow-dwBeginTime >= DELAY_TIME)
			m_status = EffectStatus_No;
		break;
	case EffectStatus_Success:
		if(m_pID_TEXT_Success) m_pID_TEXT_Success->SetVisable(true);
		if(m_pID_TEXT_Fail) m_pID_TEXT_Fail->SetVisable(false);
		if(dwTimeNow-dwBeginTime >= DELAY_TIME) 
			m_status = EffectStatus_No;
		break;
	case EffectStatus_No:
		if(m_pID_TEXT_Success) m_pID_TEXT_Success->SetVisable(false);
		if(m_pID_TEXT_Fail) m_pID_TEXT_Fail->SetVisable(false);
		break;
	}

	return true;
}
bool CUI_ID_FRAME_TransferStar::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_TransferStar::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	_SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_TransferStar::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_TransferStar::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																ControlIconDrag::S_ListImg* pItemDrag,
																ControlIconDrag::S_ListImg* pItemSrc )
{
	ClearImg(IT_Material, m_pID_LISTIMG_Material);

	if(!pSender || !pItemDrag)
		return false;
	ItemDefine::SItemCommon* pItemCommon = ( ItemDefine::SItemCommon* )GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
	if (!pItemCommon)
		return false;

	if ( pItemDrag->m_pkIconInfo->GetItemId() != SID_TRANSFERSTAR_DROP && pItemDrag->m_pkIconInfo->GetItemId() != SID_TRABSFERSTAR_UNDROP )
		return false;

	int nBagType = s_CUI_ID_FRAME_PACK.GetBagType(dynamic_cast<ControlListImage*>(pSender));
	// 包裹里
	if(!s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) && !s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender))
		return false;

	CItemBag2* pdrag_bag;
	switch (nBagType)
	{
	case BT_NormalItemBag:
		pdrag_bag = &thePlayerRole.m_bag;
		break;
	case BT_MaterialBag:
		pdrag_bag = &thePlayerRole.m_bagMaterial;
		break;
	default:
		pdrag_bag = &thePlayerRole.m_bag;
		break;
	}

	m_material.nItemBagType = nBagType;
	m_material.nItemIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( nBagType, pItemDrag );
	SCharItem item;
	if(m_material.nItemIndex != -1 && pdrag_bag->GetItem(m_material.nItemIndex,&item))
		m_material.nItemGuid = item.itembaseinfo.nOnlyInt;
	else
		m_material.nItemGuid = 0;

	m_pID_LISTIMG_Material->Clear();
	ControlIconDrag::S_ListImg img;
	img.SetData(pItemDrag->m_pkIconInfo->Id(), pItemDrag->m_pkIconInfo->Count());
	m_pID_LISTIMG_Material->SetItem(&img);

	if(m_material.nItemIndex != -1)
	{
		CPackItemEnableManager::Instance()->RefreshBagItemEnable( pdrag_bag, m_material.nItemIndex, true );
		theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
	}

	TipsVisable();
	RefreshOkButton();
	RefreshMoney();
	ShowMaterialName(pItemDrag);

	return false;
}
bool CUI_ID_FRAME_TransferStar::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_TransferStar::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_TransferStar::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	ClearImg(IT_Material, m_pID_LISTIMG_Material);
	return false;
}
// Button
bool CUI_ID_FRAME_TransferStar::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	_SetVisable(false);
	return true;
}

bool TransferStartSendMsg(char bSend, void *pData )
{
	if( !bSend )
		return false;

	s_CUI_ID_FRAME_TransferStar.SendMsg();
	return true;
}
// Button
bool CUI_ID_FRAME_TransferStar::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	if ( !m_bSourceBound || !m_bTargetBound )
	{
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_TransferStar_Bound), "", CUI_ID_FRAME_MessageBox::eTypeYesNo, true, TransferStartSendMsg);
	}
	else
		SendMsg();

	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_TransferStar::ID_LISTIMG_SourceEquipOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																   ControlIconDrag::S_ListImg* pItemDrag,
																   ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!pSender || !pItemDrag)
		return false;
	ItemDefine::SItemCommon* pItemCommon = ( ItemDefine::SItemCommon* )GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
	if (!pItemCommon)
		return false;

	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if (/*pCanEquip->ustEquipType == ItemDefine::equip_AecorativeClothing*/pCanEquip->bFashion)
		return false;

	int nBagType = s_CUI_ID_FRAME_PACK.GetBagType(dynamic_cast<ControlListImage*>(pSender));
	// 包裹里
	if(!s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) && !s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender))
		return false;

	SCharItem* pSourceEquipItem = (SCharItem*)pItemDrag->m_pkIconInfo->GetData();
	if (!pSourceEquipItem)
		return false;
	if (pSourceEquipItem->equipdata.ucLevel <= 0 && !m_bAckMsg)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eText_TransferStar_SourceStarLevel) );
		return false;
	}

	if (m_targetEquip.nItemIndex != -1 && !m_bAckMsg)
	{
		ControlIconDrag::S_ListImg* pTargetEquipImg = m_pID_LISTIMG_TargetEquip->GetItemByIndex(0);
		if (!IsSamePart(pItemDrag, pTargetEquipImg))
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eText_TransferStar_WrongPart) );
			return false;
		}
		if (!IsOverLevel(pItemDrag, pTargetEquipImg))
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eText_TransferStar_WrongLevel) );
			return false;
		}
		if (!IsOverStarLevel(pItemDrag, pTargetEquipImg))
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eText_TransferStar_WrongStarLevel) );
			return false;
		}
	}

	CItemBag2* pdrag_bag;
	switch (nBagType)
	{
	case BT_NormalItemBag:
		pdrag_bag = &thePlayerRole.m_bag;
		break;
	case BT_MaterialBag:
		pdrag_bag = &thePlayerRole.m_bagMaterial;
		break;
	default:
		pdrag_bag = &thePlayerRole.m_bag;
		break;
	}

	int16 nLastIndex = m_sourceEquip.nItemIndex;

	m_sourceEquip.nItemBagType = nBagType;
	m_sourceEquip.nItemIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( nBagType, pItemDrag );
	SCharItem item;
	if(m_sourceEquip.nItemIndex != -1 && pdrag_bag->GetItem(m_sourceEquip.nItemIndex,&item))
		m_sourceEquip.nItemGuid = item.itembaseinfo.nOnlyInt;
	else
		m_sourceEquip.nItemGuid = 0;

	m_pID_LISTIMG_SourceEquip->Clear();
	/*ControlIconDrag::S_ListImg img;
	img.SetData(pItemDrag->m_pkIconInfo->Id(), 1);
	m_pID_LISTIMG_SourceEquip->SetItem(&img);*/
	m_pID_LISTIMG_SourceEquip->SetItem( pItemDrag, 0 );
	m_pID_LISTIMG_SourceEquip->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;
	m_pID_LISTIMG_SourceEquip->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;

	if(m_sourceEquip.nItemIndex != -1)
	{
		CPackItemEnableManager::Instance()->RefreshBagItemEnable( pdrag_bag, m_sourceEquip.nItemIndex, true );
		theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);

		if ( nLastIndex != -1 )
			CPackItemEnableManager::Instance()->RefreshBagItemEnable( pdrag_bag, nLastIndex, true );
	}

	TipsVisable();
	RefreshOkButton();
	RefreshMoney();
	ShowEquipName(m_pID_TEXT_SourceName, pItemDrag);

	m_bSourceBound = pSourceEquipItem->IsBounded();

	return false;
}
bool CUI_ID_FRAME_TransferStar::ID_LISTIMG_SourceEquipOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_TransferStar::ID_LISTIMG_SourceEquipOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_TransferStar::ID_LISTIMG_SourceEquipOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	ClearImg(IT_Source, m_pID_LISTIMG_SourceEquip);
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_TransferStar::ID_LISTIMG_TargetEquipOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																   ControlIconDrag::S_ListImg* pItemDrag,
																   ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!pSender || !pItemDrag)
		return false;
	ItemDefine::SItemCommon* pItemCommon = ( ItemDefine::SItemCommon* )GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
	if (!pItemCommon)
		return false;

	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if (/*pCanEquip->ustEquipType == ItemDefine::equip_AecorativeClothing*/pCanEquip->bFashion)
		return false;

	int nBagType = s_CUI_ID_FRAME_PACK.GetBagType(dynamic_cast<ControlListImage*>(pSender));
	// 包裹里
	if(!s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) && !s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender))
		return false;

	SCharItem* pTargetEquipItem = (SCharItem*)pItemDrag->m_pkIconInfo->GetData();
	if (!pTargetEquipItem)
		return false;

	if (m_sourceEquip.nItemIndex != -1 && !m_bAckMsg)
	{
		ControlIconDrag::S_ListImg* pSourceEquipImg = m_pID_LISTIMG_SourceEquip->GetItemByIndex(0);
		if (!IsSamePart(pSourceEquipImg, pItemDrag))
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eText_TransferStar_WrongPart) );
			return false;
		}
		if (!IsOverLevel(pSourceEquipImg, pItemDrag))
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eText_TransferStar_WrongLevel) );
			return false;
		}
		if (!IsOverStarLevel(pSourceEquipImg, pItemDrag))
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eText_TransferStar_WrongStarLevel) );
			return false;
		}
	}

	CItemBag2* pdrag_bag;
	switch (nBagType)
	{
	case BT_NormalItemBag:
		pdrag_bag = &thePlayerRole.m_bag;
		break;
	case BT_MaterialBag:
		pdrag_bag = &thePlayerRole.m_bagMaterial;
		break;
	default:
		pdrag_bag = &thePlayerRole.m_bag;
		break;
	}

	int16 nLastIndex = m_targetEquip.nItemIndex;

	m_targetEquip.nItemBagType = nBagType;
	m_targetEquip.nItemIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( nBagType, pItemDrag );
	SCharItem item;
	if(m_targetEquip.nItemIndex != -1 && pdrag_bag->GetItem(m_targetEquip.nItemIndex,&item))
		m_targetEquip.nItemGuid = item.itembaseinfo.nOnlyInt;
	else
		m_targetEquip.nItemGuid = 0;

	m_pID_LISTIMG_TargetEquip->Clear();
	/*ControlIconDrag::S_ListImg img;
	img.SetData(pItemDrag->m_pkIconInfo->Id(), 1);
	m_pID_LISTIMG_TargetEquip->SetItem(&img);*/
	m_pID_LISTIMG_TargetEquip->SetItem( pItemDrag, 0 );
	m_pID_LISTIMG_TargetEquip->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;
	m_pID_LISTIMG_TargetEquip->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;

	if(m_targetEquip.nItemIndex != -1)
	{
		CPackItemEnableManager::Instance()->RefreshBagItemEnable( pdrag_bag, m_targetEquip.nItemIndex, true );
		theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);

		if ( nLastIndex != -1 )
			CPackItemEnableManager::Instance()->RefreshBagItemEnable( pdrag_bag, nLastIndex, true );
	}

	TipsVisable();
	RefreshOkButton();
	RefreshMoney();
	ShowEquipName(m_pID_TEXT_TargetName, pItemDrag);

	m_bTargetBound = pTargetEquipItem->IsBounded();

	return false;
}
bool CUI_ID_FRAME_TransferStar::ID_LISTIMG_TargetEquipOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_TransferStar::ID_LISTIMG_TargetEquipOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_TransferStar::ID_LISTIMG_TargetEquipOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	ClearImg(IT_Target, m_pID_LISTIMG_TargetEquip);
	return false;
}

// 装载UI
bool CUI_ID_FRAME_TransferStar::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TransferStar.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\TransferStar.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_TransferStar::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TransferStar, s_CUI_ID_FRAME_TransferStarOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TransferStar, s_CUI_ID_FRAME_TransferStarOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_TransferStar, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_TransferStarID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TransferStar, ID_BUTTON_HELP, s_CUI_ID_FRAME_TransferStarID_BUTTON_HELPOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_TransferStar, ID_LISTIMG_Material, s_CUI_ID_FRAME_TransferStarID_LISTIMG_MaterialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_TransferStar, ID_LISTIMG_Material, s_CUI_ID_FRAME_TransferStarID_LISTIMG_MaterialOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_TransferStar, ID_LISTIMG_Material, s_CUI_ID_FRAME_TransferStarID_LISTIMG_MaterialOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_TransferStar, ID_LISTIMG_Material, s_CUI_ID_FRAME_TransferStarID_LISTIMG_MaterialOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_TransferStar, ID_BUTTON_Cancel, s_CUI_ID_FRAME_TransferStarID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TransferStar, ID_BUTTON_Ok, s_CUI_ID_FRAME_TransferStarID_BUTTON_OkOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_TransferStar, ID_LISTIMG_SourceEquip, s_CUI_ID_FRAME_TransferStarID_LISTIMG_SourceEquipOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_TransferStar, ID_LISTIMG_SourceEquip, s_CUI_ID_FRAME_TransferStarID_LISTIMG_SourceEquipOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_TransferStar, ID_LISTIMG_SourceEquip, s_CUI_ID_FRAME_TransferStarID_LISTIMG_SourceEquipOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_TransferStar, ID_LISTIMG_SourceEquip, s_CUI_ID_FRAME_TransferStarID_LISTIMG_SourceEquipOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_TransferStar, ID_LISTIMG_TargetEquip, s_CUI_ID_FRAME_TransferStarID_LISTIMG_TargetEquipOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_TransferStar, ID_LISTIMG_TargetEquip, s_CUI_ID_FRAME_TransferStarID_LISTIMG_TargetEquipOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_TransferStar, ID_LISTIMG_TargetEquip, s_CUI_ID_FRAME_TransferStarID_LISTIMG_TargetEquipOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_TransferStar, ID_LISTIMG_TargetEquip, s_CUI_ID_FRAME_TransferStarID_LISTIMG_TargetEquipOnIconRButtonUp );

	m_pID_FRAME_TransferStar = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TransferStar );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_TransferStar, ID_BUTTON_CLOSE );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_TransferStar, ID_BUTTON_HELP );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_TransferStar, ID_TEXT_Money );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_TransferStar, ID_LISTIMG_Material );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_TransferStar, ID_BUTTON_Cancel );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_TransferStar, ID_BUTTON_Ok );
	m_pID_TEXT_Tip2 = (ControlText*)theUiManager.FindControl( ID_FRAME_TransferStar, ID_TEXT_Tip2 );
	m_pID_TEXT_Tip1 = (ControlText*)theUiManager.FindControl( ID_FRAME_TransferStar, ID_TEXT_Tip1 );
	m_pID_LISTIMG_SourceEquip = (ControlListImage*)theUiManager.FindControl( ID_FRAME_TransferStar, ID_LISTIMG_SourceEquip );
	m_pID_LISTIMG_TargetEquip = (ControlListImage*)theUiManager.FindControl( ID_FRAME_TransferStar, ID_LISTIMG_TargetEquip );
	m_pID_TEXT_Success = (ControlText*)theUiManager.FindControl( ID_FRAME_TransferStar, ID_TEXT_Success );
	m_pID_TEXT_Fail = (ControlText*)theUiManager.FindControl( ID_FRAME_TransferStar, ID_TEXT_Fail );
	m_pID_TEXT_SourceName = (ControlText*)theUiManager.FindControl( ID_FRAME_TransferStar, ID_TEXT_SourceName );
	m_pID_TEXT_TargetName = (ControlText*)theUiManager.FindControl( ID_FRAME_TransferStar, ID_TEXT_TargetName );
	m_pID_TEXT_MaterialName = (ControlText*)theUiManager.FindControl( ID_FRAME_TransferStar, ID_TEXT_MaterialName );

	assert( m_pID_FRAME_TransferStar );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_TEXT_Money );
	assert( m_pID_LISTIMG_Material );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_TEXT_Tip2 );
	assert( m_pID_TEXT_Tip1 );
	assert( m_pID_LISTIMG_SourceEquip );
	assert( m_pID_LISTIMG_TargetEquip );
	assert( m_pID_TEXT_Success );
	assert( m_pID_TEXT_Fail );
	assert( m_pID_TEXT_SourceName );
	assert( m_pID_TEXT_TargetName );
	assert( m_pID_TEXT_MaterialName );

	m_pID_BUTTON_Ok->SetEnable(false);
	m_pID_FRAME_TransferStar->SetOnVisibleChangedFun( OnVisibleChange );
	m_pID_TEXT_Success->SetVisable(false);
	m_pID_TEXT_Fail->SetVisable(false);
	m_pID_TEXT_Money->SetText("");
	m_pID_TEXT_SourceName->SetText("");
	m_pID_TEXT_TargetName->SetText("");
	m_pID_TEXT_MaterialName->SetText("");
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_TransferStar::_UnLoadUI()
{
	m_pID_FRAME_TransferStar = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\TransferStar.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_TransferStar::_IsVisable()
{
	if (!m_pID_FRAME_TransferStar)
		return false;
	return m_pID_FRAME_TransferStar->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_TransferStar::_SetVisable( const bool bVisable )
{
	if (!m_pID_FRAME_TransferStar)
		return;

	/*if (bVisable)
	{
		if (!s_CUI_ID_FRAME_PACK.IsVisable())
			s_CUI_ID_FRAME_PACK.SetVisable(true);

		ResetWindowPosition(m_pID_FRAME_TransferStar, s_CUI_ID_FRAME_PACK.GetFrame());
	}*/
	TipsVisable();
	m_status = EffectStatus_No;
	m_pID_FRAME_TransferStar->SetVisable( bVisable );
}

bool CUI_ID_FRAME_TransferStar::IsPackItemBeUsing( __int64 nGuid )
{
	if( !IsVisable() || nGuid <= 0 )
		return false;

	if (m_targetEquip.nItemGuid == nGuid)
		return true;
	if (m_sourceEquip.nItemGuid == nGuid)
		return true;
	if (m_material.nItemGuid == nGuid)
		return true;

	return false;
}

void CUI_ID_FRAME_TransferStar::OnDragOn(ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc)
{
	if(!pSender || !pItemDrag)
		return;
	ItemDefine::SItemCommon* pItemCommon = ( ItemDefine::SItemCommon* )GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
	if (!pItemCommon)
		return;

	if (pItemCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON || pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR)
	{
		if (m_sourceEquip.nItemIndex == -1)
		{
			m_SourceSender = pSender;
			ID_LISTIMG_SourceEquipOnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);
		}
		else if (m_targetEquip.nItemIndex == -1)
		{
			m_TargetSender = pSender;
			ID_LISTIMG_TargetEquipOnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);
		}
	}
	else if(pItemCommon->ucItemType == ItemDefine::ITEMTYPE_MATERIAL)
	{
		const TransferStarMaterial* pMaterial = theStarLevelUpConfig.GetTransferStarMaterial(pItemDrag->m_pkIconInfo->GetItemId());
		if (!pMaterial)
			return;
		m_MaterialSender = pSender;
		ID_LISTIMG_MaterialOnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);
	}
}

void CUI_ID_FRAME_TransferStar::TipsVisable()
{
	if (!m_pID_TEXT_Tip1 || !m_pID_TEXT_Tip2)
		return;
	m_pID_TEXT_Tip1->SetVisable(false);
	m_pID_TEXT_Tip2->SetVisable(false);

	if (m_targetEquip.nItemIndex == -1)
	{
		m_pID_TEXT_Tip1->SetVisable(true);
		return;
	}
	if (m_sourceEquip.nItemIndex == -1)
	{
		m_pID_TEXT_Tip1->SetVisable(true);
		return;
	}
	if (m_material.nItemIndex == -1)
	{
		m_pID_TEXT_Tip2->SetVisable(true);
		return;
	}
}

void CUI_ID_FRAME_TransferStar::OnVisibleChange( ControlObject* pUIObject )
{
	s_CUI_ID_FRAME_TransferStar.ClearAll();
}

void CUI_ID_FRAME_TransferStar::ClearImg(ImgTpye itype,ControlListImage *pTargetImg)
{
	if (!pTargetImg)
		return;
	pTargetImg->Clear();

	CItemBag2* pTargetBag;
	int bagIndex = -1;
	switch (itype)
	{
	case IT_Source:
		{
			switch (m_sourceEquip.nItemBagType)
			{
			case BT_NormalItemBag:
				pTargetBag = &thePlayerRole.m_bag;
				break;
			case BT_MaterialBag:
				pTargetBag = &thePlayerRole.m_bagMaterial;
				break;
			default:
				pTargetBag = &thePlayerRole.m_bag;
				break;
			}
			bagIndex = m_sourceEquip.nItemIndex;
			m_sourceEquip.nItemBagType = 0;
			m_sourceEquip.nItemIndex = -1;
			m_sourceEquip.nItemGuid = 0;

			m_bSourceBound = false;

			m_pID_TEXT_SourceName->SetText("");
		}
		break;
	case IT_Target:
		{
			switch (m_targetEquip.nItemBagType)
			{
			case BT_NormalItemBag:
				pTargetBag = &thePlayerRole.m_bag;
				break;
			case BT_MaterialBag:
				pTargetBag = &thePlayerRole.m_bagMaterial;
				break;
			default:
				pTargetBag = &thePlayerRole.m_bag;
				break;
			}
			bagIndex = m_targetEquip.nItemIndex;
			m_targetEquip.nItemBagType = 0;
			m_targetEquip.nItemIndex = -1;
			m_targetEquip.nItemGuid = 0;

			m_bTargetBound = false;

			m_pID_TEXT_TargetName->SetText("");
		}
		break;
	case IT_Material:
		{
			switch (m_material.nItemBagType)
			{
			case BT_NormalItemBag:
				pTargetBag = &thePlayerRole.m_bag;
				break;
			case BT_MaterialBag:
				pTargetBag = &thePlayerRole.m_bagMaterial;
				break;
			default:
				pTargetBag = &thePlayerRole.m_bagMaterial;
				break;
			}
			bagIndex = m_material.nItemIndex;
			m_material.nItemBagType = 0;
			m_material.nItemIndex = -1;
			m_material.nItemGuid = 0;

			m_pID_TEXT_MaterialName->SetText("");
		}
		break;
	}

	if(bagIndex != -1)
		CPackItemEnableManager::Instance()->RefreshBagItemEnable( pTargetBag, bagIndex, true );

	TipsVisable();
	RefreshOkButton();
	RefreshMoney();
	SetAckMsg(false);
}

void CUI_ID_FRAME_TransferStar::RefreshOkButton()
{
	if (!m_pID_BUTTON_Ok)
		return;
	m_pID_BUTTON_Ok->SetEnable(false);

	if (m_targetEquip.nItemIndex == -1)
		return;
	if (m_sourceEquip.nItemIndex == -1)
		return;
	if (m_material.nItemIndex == -1)
		return;

	ControlIconDrag::S_ListImg* pItemImg = m_pID_LISTIMG_Material->GetItemByIndex(0);
	if (!pItemImg || pItemImg->IsNull())
		return;

	ControlIconDrag::S_ListImg* pSourceItemImg = m_pID_LISTIMG_SourceEquip->GetItemByIndex(0);
	if (!pSourceItemImg || pSourceItemImg->IsNull())
		return;

	ControlIconDrag::S_ListImg* pTargetItemImg = m_pID_LISTIMG_TargetEquip->GetItemByIndex(0);
	if (!pTargetItemImg || pTargetItemImg->IsNull())
		return;

	SCharItem* pSourceEquipItem = (SCharItem*)pSourceItemImg->m_pkIconInfo->GetData();
	if (!pSourceEquipItem)
		return;
	if (pSourceEquipItem->equipdata.ucLevel <= 0)
	{
		//if (m_bAckMsg)
			//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eText_TransferStar_SourceStarLevel) );
		return;
	}

	if (!IsOverStarLevel(pSourceItemImg, pTargetItemImg))
	{
		//if (m_bAckMsg)
			//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eText_TransferStar_WrongStarLevel) );
		return;
	}

	const TransferStarMaterial* pMaterial = theStarLevelUpConfig.GetTransferStarMaterial(pItemImg->m_pkIconInfo->GetItemId());
	if (!pMaterial)
		return;
	if(!thePlayerRole.HaveEnoughMoney(pMaterial->GetCostMoney(pSourceEquipItem->equipdata.ucLevel)))
		return;

	m_pID_BUTTON_Ok->SetEnable(true);
}

bool CUI_ID_FRAME_TransferStar::IsSamePart(ControlIconDrag::S_ListImg * pSourceImg,ControlIconDrag::S_ListImg * pTargetImg)
{
	if( !pTargetImg || !pSourceImg)
		return false;
	if( pTargetImg->IsNull() || pSourceImg->IsNull())
		return false;
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pSourceImg->m_pkIconInfo->GetItemId() );
	if( !pItemCommon )
		return false;
	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;

	ItemDefine::SItemCommon* pTargetItemCommon = GettheItemDetail().GetItemByID( pTargetImg->m_pkIconInfo->GetItemId() );
	if( !pTargetItemCommon )
		return false;
	ItemDefine::SItemCanEquip* pTargetCanEquip = ( ItemDefine::SItemCanEquip* )pTargetItemCommon;

	return pCanEquip->ustEquipType == pTargetCanEquip->ustEquipType;
}

bool CUI_ID_FRAME_TransferStar::IsOverLevel(ControlIconDrag::S_ListImg * pSourceImg,ControlIconDrag::S_ListImg * pTargetImg)
{
	if( !pTargetImg || !pSourceImg)
		return false;
	if( pTargetImg->IsNull() || pSourceImg->IsNull())
		return false;
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pSourceImg->m_pkIconInfo->GetItemId() );
	if( !pItemCommon )
		return false;
	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;

	ItemDefine::SItemCommon* pTargetItemCommon = GettheItemDetail().GetItemByID( pTargetImg->m_pkIconInfo->GetItemId() );
	if( !pTargetItemCommon )
		return false;
	ItemDefine::SItemCanEquip* pTargetCanEquip = ( ItemDefine::SItemCanEquip* )pTargetItemCommon;

	return  pTargetCanEquip->stEquipLevelReq - pCanEquip->stEquipLevelReq <= 10 && pCanEquip->stEquipLevelReq <= pTargetCanEquip->stEquipLevelReq;
}

bool CUI_ID_FRAME_TransferStar::IsOverStarLevel(ControlIconDrag::S_ListImg * pSourceImg,ControlIconDrag::S_ListImg * pTargetImg)
{
	if( !pTargetImg || !pSourceImg)
		return false;
	if( pTargetImg->IsNull() || pSourceImg->IsNull())
		return false;

	SCharItem* pSourceEquipItem = (SCharItem*)pSourceImg->m_pkIconInfo->GetData();
	if (!pSourceEquipItem)
		return false;
	SCharItem* pTargetEquipItem = (SCharItem*)pTargetImg->m_pkIconInfo->GetData();
	if (!pTargetEquipItem)
		return false;

	return pSourceEquipItem->equipdata.ucLevel > pTargetEquipItem->equipdata.ucLevel;
}

void CUI_ID_FRAME_TransferStar::RefreshMoney()
{
	if (!m_pID_TEXT_Money)
		return;
	m_pID_TEXT_Money->SetText("");

	if (m_targetEquip.nItemIndex == -1)
		return;
	if (m_sourceEquip.nItemIndex == -1)
		return;
	if (m_material.nItemIndex == -1)
		return;

	ControlIconDrag::S_ListImg* pItemImg = m_pID_LISTIMG_Material->GetItemByIndex(0);
	if (!pItemImg || pItemImg->IsNull())
		return;

	ControlIconDrag::S_ListImg* pSourceItemImg = m_pID_LISTIMG_SourceEquip->GetItemByIndex(0);
	if (!pSourceItemImg || pSourceItemImg->IsNull())
		return;

	ControlIconDrag::S_ListImg* pTargetItemImg = m_pID_LISTIMG_TargetEquip->GetItemByIndex(0);
	if (!pTargetItemImg || pTargetItemImg->IsNull())
		return;

	SCharItem* pSourceEquipItem = (SCharItem*)pSourceItemImg->m_pkIconInfo->GetData();
	if (!pSourceEquipItem)
		return;

	if (!IsOverStarLevel(pSourceItemImg, pTargetItemImg))
		return;

	const TransferStarMaterial* pMaterial = theStarLevelUpConfig.GetTransferStarMaterial(pItemImg->m_pkIconInfo->GetItemId());
	if (!pMaterial)
		return;

	int nMoney = pMaterial->GetCostMoney(pSourceEquipItem->equipdata.ucLevel);
	if (nMoney <= 0)
		return;

	std::string text = "";
	thePlayerRole.GetGSCStringFromJiaoZi(nMoney, text);
	DWORD dwColor = 0xffffffff;
	if(!thePlayerRole.HaveEnoughMoney(nMoney))
	{
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_StarLEvolveNoMomeny), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true);
		dwColor = 0xffff0000;
	}

	m_pID_TEXT_Money->SetText(text,dwColor);
}

void CUI_ID_FRAME_TransferStar::ClearAll()
{
	ClearImg(IT_Material, m_pID_LISTIMG_Material);
	ClearImg(IT_Source, m_pID_LISTIMG_SourceEquip);
	ClearImg(IT_Target, m_pID_LISTIMG_TargetEquip);

	m_status = EffectStatus_No;
	m_SourceSender = NULL;
	m_TargetSender = NULL;
	m_MaterialSender = NULL;
}

void CUI_ID_FRAME_TransferStar::SendMsg()
{
	MsgTransferStar msg;

	if (m_targetEquip.nItemIndex == -1)
		return;
	if (m_sourceEquip.nItemIndex == -1)
		return;
	if (m_material.nItemIndex == -1)
		return;

	msg.sTargetEquip.nItemBagType = m_targetEquip.nItemBagType;
	msg.sTargetEquip.nItemIndex = m_targetEquip.nItemIndex;
	msg.sTargetEquip.nItemGuid = m_targetEquip.nItemGuid;

	msg.sSourceEquip.nItemBagType = m_sourceEquip.nItemBagType;
	msg.sSourceEquip.nItemIndex = m_sourceEquip.nItemIndex;
	msg.sSourceEquip.nItemGuid = m_sourceEquip.nItemGuid;

	msg.sMaterial.nItemBagType = m_material.nItemBagType;
	msg.sMaterial.nItemIndex = m_material.nItemIndex;
	msg.sMaterial.nItemGuid = m_material.nItemGuid;

	GettheNetworkInput().SendMsg( &msg );
}

void CUI_ID_FRAME_TransferStar::UpdataAll()
{
	if (m_sourceEquip.nItemIndex != -1 && m_SourceSender)
	{
		ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( m_sourceEquip.nItemBagType, m_sourceEquip.nItemIndex );
		if (!pItemImg || pItemImg->IsNull())
		{
			ClearImg(IT_Source, m_pID_LISTIMG_SourceEquip);
		}
		else
			ID_LISTIMG_SourceEquipOnIconDragOn(m_SourceSender, NULL, pItemImg, 0);
	}

	if (m_targetEquip.nItemIndex != -1 && m_TargetSender)
	{
		ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( m_targetEquip.nItemBagType, m_targetEquip.nItemIndex );
		if (!pItemImg || pItemImg->IsNull())
		{
			ClearImg(IT_Target, m_pID_LISTIMG_TargetEquip);
		}
		else
			ID_LISTIMG_TargetEquipOnIconDragOn(m_TargetSender, NULL, pItemImg, 0);
	}

	if (m_material.nItemIndex != -1 && m_MaterialSender)
	{
		ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( m_material.nItemBagType, m_material.nItemIndex );
		if (!pItemImg || pItemImg->IsNull())
		{
			ClearImg(IT_Material, m_pID_LISTIMG_Material);
		}
		else
			ID_LISTIMG_MaterialOnIconDragOn(m_MaterialSender, NULL, pItemImg, 0);
	}
}

void CUI_ID_FRAME_TransferStar::ShowEquipName(ControlText* pText, ControlIconDrag::S_ListImg* pItemDrag)
{
	if (!pText || !pItemDrag)
		return;
	pText->SetText("");

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if (!pItemCommon)
		return;
	SCharItem* pEquipItem = (SCharItem*)pItemDrag->m_pkIconInfo->GetData();
	if (!pEquipItem)
		return;

	char temp[128] = {0};
	if (pEquipItem->equipdata.ucLevel)
		sprintf(temp, "%s+%d", pItemCommon->GetItemName(), pEquipItem->equipdata.ucLevel);
	else
		sprintf(temp, "%s", pItemCommon->GetItemName());

	pText->SetText(temp);
}

void CUI_ID_FRAME_TransferStar::ShowMaterialName(ControlIconDrag::S_ListImg* pItemDrag)
{
	if (!m_pID_TEXT_MaterialName || !pItemDrag)
		return;
	m_pID_TEXT_MaterialName->SetText("");

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if (!pItemCommon)
		return;

	char temp[128] = {0};
	if (pItemDrag->m_pkIconInfo->GetItemId() == SID_TRANSFERSTAR_DROP)
		sprintf(temp, "%s：%s", pItemCommon->GetItemName(), theXmlString.GetString(eText_TransferStar_MaterialDrop));
	else if (pItemDrag->m_pkIconInfo->GetItemId() == SID_TRABSFERSTAR_UNDROP)
		sprintf(temp, "%s：%s", pItemCommon->GetItemName(), theXmlString.GetString(eText_TransferStar_MaterialUnDrop));

	m_pID_TEXT_MaterialName->SetText(temp);
}