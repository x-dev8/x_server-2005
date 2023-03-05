/********************************************************************
Created by UIEditor.exe
FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\Gem.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Gem.h"
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
#include "PackItemEnableManager.h"

#define DELAY_TIME 350

CUI_ID_FRAME_Gem s_CUI_ID_FRAME_Gem;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Gem, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Gem, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gem, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gem, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gem, ID_BUTTON_OkOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LIST_GemFunction1OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LIST_GemFunction2OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LIST_GemFunction3OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LIST_GemFunction4OnListSelectChange )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Hole1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Hole1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Hole1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Hole1OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Hole2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Hole2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Hole2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Hole2OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Hole3OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Hole3OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Hole3OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Hole3OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Hole4OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Hole4OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Hole4OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Hole4OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_ArmourOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_ArmourOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_ArmourOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Material1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Material1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Material1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Material1OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Material2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Material2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Material2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Gem, ID_LISTIMG_Material2OnIconRButtonUp )
CUI_ID_FRAME_Gem::CUI_ID_FRAME_Gem()
{
	// Member
	m_pID_FRAME_EquipEvolve = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_TEXT_Tip2 = NULL;
	m_pID_TEXT_Tip1 = NULL;
	m_pID_LIST_GemFunction1 = NULL;
	m_pID_LIST_GemFunction2 = NULL;
	m_pID_LIST_GemFunction3 = NULL;
	m_pID_LIST_GemFunction4 = NULL;
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
	m_pID_PICTURE_StarEffect = NULL;
	m_pID_TEXT_TipAllDone = NULL;
	m_pID_PICTURE_Begin = NULL;
	m_pID_LISTIMG_Equip = NULL;
	m_pID_TEXT_SuccessRatio = NULL;
	m_pID_LISTIMG_Material1 = NULL;
	m_pID_LISTIMG_Material2 = NULL;
	m_pID_TEXT_Tip3 = NULL;
	m_pID_TEXT_Effect = NULL;
	m_pID_TEXT_Success = NULL;
	m_pID_TEXT_Fail = NULL;
	m_pID_TEXT_EquiqName = NULL;
	m_pID_TEXT_MaterialName = NULL;

	m_status = EffectStatus_No;
	dwBeginTime = 0;
	m_bSendMsg = false;
}
// Frame
bool CUI_ID_FRAME_Gem::OnFrameRun()
{
	bool isDirty = OnDirty();
	if (isDirty)
	{
		RefreshSuccessRatio();
	}
	bool bOkEnable = m_pID_BUTTON_Ok->IsEnable();
	DWORD timenow = timeGetTime();
	switch (m_status)
	{
	case EffectStatus_Start:
		if (timenow-dwBeginTime>=DELAY_TIME && m_bSendMsg )
		{
			if (OnOkClick())
			{
				SetShowTip(0);
				m_pID_BUTTON_Ok->SetEnable(false);
			}
			m_bSendMsg = false;
		}
		else
		{
			m_pID_BUTTON_Ok->SetEnable(false);
			if(m_pID_TEXT_Effect) m_pID_TEXT_Effect->SetVisable(true);
			if(m_pID_TEXT_Success) m_pID_TEXT_Success->SetVisable(false);
			if(m_pID_TEXT_Fail) m_pID_TEXT_Fail->SetVisable(false);
		}
		break;
	case EffectStatus_Fail:
		//m_pID_BUTTON_Ok->SetEnable(true);
		if(m_pID_TEXT_Fail) m_pID_TEXT_Fail->SetVisable(true);
		if(m_pID_TEXT_Success) m_pID_TEXT_Success->SetVisable(false);
		if(m_pID_TEXT_Effect) m_pID_TEXT_Effect->SetVisable(false);
		if(timenow-dwBeginTime>=DELAY_TIME)
			m_status = EffectStatus_No;
		m_bSendMsg = false;
		break;
	case EffectStatus_Success:
		//m_pID_BUTTON_Ok->SetEnable(true);
		if(m_pID_TEXT_Success) m_pID_TEXT_Success->SetVisable(true);
		if(m_pID_TEXT_Fail) m_pID_TEXT_Fail->SetVisable(false);
		if(m_pID_TEXT_Effect) m_pID_TEXT_Effect->SetVisable(false);
		if(timenow-dwBeginTime>=DELAY_TIME) 
			m_status = EffectStatus_No;
		m_bSendMsg = false;
		break;
	case EffectStatus_No:
		//m_pID_BUTTON_Ok->SetEnable(m_pID_BUTTON_Ok->IsEnable());
		if(m_pID_TEXT_Success) m_pID_TEXT_Success->SetVisable(false);
		if(m_pID_TEXT_Fail) m_pID_TEXT_Fail->SetVisable(false);
		if(m_pID_TEXT_Effect) m_pID_TEXT_Effect->SetVisable(false);
		m_bSendMsg = false;
		break;
	}

	return true;
}
bool CUI_ID_FRAME_Gem::OnFrameRender()
{
	OnRender();
	return true;
}
// Button
bool CUI_ID_FRAME_Gem::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_Gem::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_Gem::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_EquipEvolve)
		return false;
	if (-1 == m_nSelectMaterialIndex)
	{
		return false;
	}
	dwBeginTime = timeGetTime();
	m_status = EffectStatus_Start;
	m_bSendMsg = true;
	//OnOkClick();
	//SetShowTip(0);
	return true;
}
// List
void CUI_ID_FRAME_Gem::ID_LIST_GemFunction1OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_Gem::ID_LIST_GemFunction2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_Gem::ID_LIST_GemFunction3OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_Gem::ID_LIST_GemFunction4OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// ListImg / ListEx
bool CUI_ID_FRAME_Gem::ID_LISTIMG_Hole1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													ControlIconDrag::S_ListImg* pItemDrag,
													ControlIconDrag::S_ListImg* pItemSrc )
{
	RClickGemIn(pSender,pItemDrag);
	return false;
}
bool CUI_ID_FRAME_Gem::ID_LISTIMG_Hole1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Gem::ID_LISTIMG_Hole1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Gem::ID_LISTIMG_Hole1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return OnGemRemove(0);
}
// ListImg / ListEx
bool CUI_ID_FRAME_Gem::ID_LISTIMG_Hole2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													ControlIconDrag::S_ListImg* pItemDrag,
													ControlIconDrag::S_ListImg* pItemSrc )
{
	RClickGemIn(pSender,pItemDrag);
	return false;
}
bool CUI_ID_FRAME_Gem::ID_LISTIMG_Hole2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Gem::ID_LISTIMG_Hole2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Gem::ID_LISTIMG_Hole2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return OnGemRemove(1);
}
// ListImg / ListEx
bool CUI_ID_FRAME_Gem::ID_LISTIMG_Hole3OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													ControlIconDrag::S_ListImg* pItemDrag,
													ControlIconDrag::S_ListImg* pItemSrc )
{
	RClickGemIn(pSender,pItemDrag);
	return false;
}
bool CUI_ID_FRAME_Gem::ID_LISTIMG_Hole3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Gem::ID_LISTIMG_Hole3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Gem::ID_LISTIMG_Hole3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return OnGemRemove(2);
}
// ListImg / ListEx
bool CUI_ID_FRAME_Gem::ID_LISTIMG_Hole4OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													ControlIconDrag::S_ListImg* pItemDrag,
													ControlIconDrag::S_ListImg* pItemSrc )
{
	RClickGemIn(pSender,pItemDrag);
	return false;
}
bool CUI_ID_FRAME_Gem::ID_LISTIMG_Hole4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Gem::ID_LISTIMG_Hole4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Gem::ID_LISTIMG_Hole4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return OnGemRemove(3);
}
// ListImg / ListEx
bool CUI_ID_FRAME_Gem::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
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
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString(eText_Gem_ErrorItem) );
		return false;
	}
	if ( pItemCommon->ucItemType != ItemDefine::ITEMTYPE_WEAPON &&
		pItemCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString(eText_Gem_ErrorItem) );
		return false;
	}

	OnEquipDragOn(pItemDrag,pSender);
	ShowItemName(m_pID_TEXT_EquiqName, pItemDrag);
	//ShowMaterialIcon();
	return false;
}
bool CUI_ID_FRAME_Gem::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Gem::ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Gem::ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	ClearEquip();
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Gem::ID_LISTIMG_Material1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														ControlIconDrag::S_ListImg* pItemDrag,
														ControlIconDrag::S_ListImg* pItemSrc )
{
	ID_LISTIMG_Material1OnIconRButtonUp(NULL,NULL);
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
	if( !pImageSender )
		return false;

	if(pItemCommon->ucItemType != ItemDefine::ITEMTYPE_MATERIAL)
		return false;

	ItemDefine::SCreateMaterial* pMaterial = (ItemDefine::SCreateMaterial*)pItemCommon;
	if(pMaterial->stMaterialType != ItemDefine::ematerial_inlay)
		return false;

	int index = 1;
	// 包裹里
	if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pImageSender) )
	{			
		m_stMaterialIndex[index] = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_MaterialBag, pItemDrag );

		SCharItem item;
		if(m_stMaterialIndex[index] != -1 && thePlayerRole.m_bagMaterial.GetItem(m_stMaterialIndex[index],&item))
			m_n64MaterialGuid[index] = item.itembaseinfo.nOnlyInt;
		else
			m_n64MaterialGuid[index] = 0;
		m_shMaterialBagType[index] = BT_MaterialBag;
		ControlIconDrag::S_ListImg liGem;
		liGem.SetData( pItemDrag->m_pkIconInfo->GetItemId(),1,eIcon_Enable );

		m_pID_LISTIMG_Material1->SetItem(&liGem,0);
	}
	else
	{
		return false;
	}
	m_bMaterialBagEnable[index] = false;
	SetDirty( true );
	SetShowTip(0);

	return false;
}

bool CUI_ID_FRAME_Gem::ID_LISTIMG_Material1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_Gem::ID_LISTIMG_Material1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_Gem::ID_LISTIMG_Material1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	/*int nIndex = 1;
	if(m_n64MaterialGuid[nIndex] == 0)
		return false;

	int nHole = GetEmptyHole();
	if(nHole != -1)
		SetShowTip(3);

	m_pID_LISTIMG_Material1->Clear();
	m_bMaterialBagEnable[nIndex] = true;

	SetDirty(true);

	return false;*/
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_Gem::ID_LISTIMG_Material2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														ControlIconDrag::S_ListImg* pItemDrag,
														ControlIconDrag::S_ListImg* pItemSrc )
{
	ID_LISTIMG_Material2OnIconRButtonUp(NULL,NULL);

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
	if( !pImageSender )
		return false;

	if(pItemCommon->ucItemType != ItemDefine::ITEMTYPE_MATERIAL)
		return false;

	ItemDefine::SCreateMaterial* pMaterial = (ItemDefine::SCreateMaterial*)pItemCommon;
	if(pMaterial->stMaterialType != ItemDefine::ematerial_rateboll)
		return false;

	int index = 2;
	// 包裹里
	if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pImageSender) )
	{			
		m_stMaterialIndex[index] = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_MaterialBag, pItemDrag );

		SCharItem item;
		if(m_stMaterialIndex[index] != -1 && thePlayerRole.m_bagMaterial.GetItem(m_stMaterialIndex[index],&item))
			m_n64MaterialGuid[index] = item.itembaseinfo.nOnlyInt;
		else
			m_n64MaterialGuid[index] = 0;
		m_shMaterialBagType[index] = BT_MaterialBag;
		ControlIconDrag::S_ListImg liGem;
		liGem.SetData( pItemDrag->m_pkIconInfo->GetItemId(),1,eIcon_Enable );

		m_pID_LISTIMG_Material2->SetItem(&liGem,0);
	}
	else
	{
		return false;
	}
	m_bMaterialBagEnable[index] = false;

	SetDirty( true );
	return false;
}

bool CUI_ID_FRAME_Gem::ID_LISTIMG_Material2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_Gem::ID_LISTIMG_Material2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_Gem::ID_LISTIMG_Material2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	int nIndex = 2;
	if(m_n64MaterialGuid[nIndex] == 0)
		return false;

	m_pID_LISTIMG_Material2->Clear();

	m_bMaterialBagEnable[nIndex] = true;

	SetDirty(true);
	return false;
}

// 装载UI
bool CUI_ID_FRAME_Gem::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Gem.MEUI" , false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Gem.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Gem::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Gem, s_CUI_ID_FRAME_GemOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Gem, s_CUI_ID_FRAME_GemOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Gem, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_GemID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gem, ID_BUTTON_Cancel, s_CUI_ID_FRAME_GemID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gem, ID_BUTTON_Ok, s_CUI_ID_FRAME_GemID_BUTTON_OkOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Gem, ID_LIST_GemFunction1, s_CUI_ID_FRAME_GemID_LIST_GemFunction1OnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Gem, ID_LIST_GemFunction2, s_CUI_ID_FRAME_GemID_LIST_GemFunction2OnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Gem, ID_LIST_GemFunction3, s_CUI_ID_FRAME_GemID_LIST_GemFunction3OnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Gem, ID_LIST_GemFunction4, s_CUI_ID_FRAME_GemID_LIST_GemFunction4OnListSelectChange );
	theUiManager.OnIconDragOn( ID_FRAME_Gem, ID_LISTIMG_Hole1, s_CUI_ID_FRAME_GemID_LISTIMG_Hole1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Gem, ID_LISTIMG_Hole1, s_CUI_ID_FRAME_GemID_LISTIMG_Hole1OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Gem, ID_LISTIMG_Hole1, s_CUI_ID_FRAME_GemID_LISTIMG_Hole1OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Gem, ID_LISTIMG_Hole1, s_CUI_ID_FRAME_GemID_LISTIMG_Hole1OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Gem, ID_LISTIMG_Hole2, s_CUI_ID_FRAME_GemID_LISTIMG_Hole2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Gem, ID_LISTIMG_Hole2, s_CUI_ID_FRAME_GemID_LISTIMG_Hole2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Gem, ID_LISTIMG_Hole2, s_CUI_ID_FRAME_GemID_LISTIMG_Hole2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Gem, ID_LISTIMG_Hole2, s_CUI_ID_FRAME_GemID_LISTIMG_Hole2OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Gem, ID_LISTIMG_Hole3, s_CUI_ID_FRAME_GemID_LISTIMG_Hole3OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Gem, ID_LISTIMG_Hole3, s_CUI_ID_FRAME_GemID_LISTIMG_Hole3OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Gem, ID_LISTIMG_Hole3, s_CUI_ID_FRAME_GemID_LISTIMG_Hole3OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Gem, ID_LISTIMG_Hole3, s_CUI_ID_FRAME_GemID_LISTIMG_Hole3OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Gem, ID_LISTIMG_Hole4, s_CUI_ID_FRAME_GemID_LISTIMG_Hole4OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Gem, ID_LISTIMG_Hole4, s_CUI_ID_FRAME_GemID_LISTIMG_Hole4OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Gem, ID_LISTIMG_Hole4, s_CUI_ID_FRAME_GemID_LISTIMG_Hole4OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Gem, ID_LISTIMG_Hole4, s_CUI_ID_FRAME_GemID_LISTIMG_Hole4OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Gem, ID_LISTIMG_Armour, s_CUI_ID_FRAME_GemID_LISTIMG_ArmourOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Gem, ID_LISTIMG_Armour, s_CUI_ID_FRAME_GemID_LISTIMG_ArmourOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Gem, ID_LISTIMG_Armour, s_CUI_ID_FRAME_GemID_LISTIMG_ArmourOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Gem, ID_LISTIMG_Armour, s_CUI_ID_FRAME_GemID_LISTIMG_ArmourOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Gem, ID_LISTIMG_Material1, s_CUI_ID_FRAME_GemID_LISTIMG_Material1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Gem, ID_LISTIMG_Material1, s_CUI_ID_FRAME_GemID_LISTIMG_Material1OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Gem, ID_LISTIMG_Material1, s_CUI_ID_FRAME_GemID_LISTIMG_Material1OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Gem, ID_LISTIMG_Material1, s_CUI_ID_FRAME_GemID_LISTIMG_Material1OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Gem, ID_LISTIMG_Material2, s_CUI_ID_FRAME_GemID_LISTIMG_Material2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Gem, ID_LISTIMG_Material2, s_CUI_ID_FRAME_GemID_LISTIMG_Material2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Gem, ID_LISTIMG_Material2, s_CUI_ID_FRAME_GemID_LISTIMG_Material2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Gem, ID_LISTIMG_Material2, s_CUI_ID_FRAME_GemID_LISTIMG_Material2OnIconRButtonUp );

	m_pID_FRAME_EquipEvolve = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Gem );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_Gem, ID_TEXT_Money );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gem, ID_BUTTON_Cancel );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gem, ID_BUTTON_Ok );
	m_pID_TEXT_Tip2 = (ControlText*)theUiManager.FindControl( ID_FRAME_Gem, ID_TEXT_Tip2 );
	m_pID_TEXT_Tip1 = (ControlText*)theUiManager.FindControl( ID_FRAME_Gem, ID_TEXT_Tip1 );
	m_pID_LIST_GemFunction1 = (ControlList*)theUiManager.FindControl( ID_FRAME_Gem, ID_LIST_GemFunction1 );
	m_pID_LIST_GemFunction2 = (ControlList*)theUiManager.FindControl( ID_FRAME_Gem, ID_LIST_GemFunction2 );
	m_pID_LIST_GemFunction3 = (ControlList*)theUiManager.FindControl( ID_FRAME_Gem, ID_LIST_GemFunction3 );
	m_pID_LIST_GemFunction4 = (ControlList*)theUiManager.FindControl( ID_FRAME_Gem, ID_LIST_GemFunction4 );
	m_pID_PICTURE_Open1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gem, ID_PICTURE_Open1 );
	m_pID_PICTURE_Open2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gem, ID_PICTURE_Open2 );
	m_pID_PICTURE_Open3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gem, ID_PICTURE_Open3 );
	m_pID_PICTURE_Open4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gem, ID_PICTURE_Open4 );
	m_pID_LISTIMG_Hole1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Gem, ID_LISTIMG_Hole1 );
	m_pID_LISTIMG_Hole2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Gem, ID_LISTIMG_Hole2 );
	m_pID_LISTIMG_Hole3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Gem, ID_LISTIMG_Hole3 );
	m_pID_LISTIMG_Hole4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Gem, ID_LISTIMG_Hole4 );
	m_pID_PICTURE_Lock1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gem, ID_PICTURE_Lock1 );
	m_pID_PICTURE_Lock2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gem, ID_PICTURE_Lock2 );
	m_pID_PICTURE_Lock3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gem, ID_PICTURE_Lock3 );
	m_pID_PICTURE_Lock4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gem, ID_PICTURE_Lock4 );
	m_pID_PICTURE_StarEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gem, ID_PICTURE_StarEffect );
	m_pID_TEXT_TipAllDone = (ControlText*)theUiManager.FindControl( ID_FRAME_Gem, ID_TEXT_TipAllDone );
	m_pID_PICTURE_Begin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gem, ID_PICTURE_Begin );
	m_pID_LISTIMG_Equip = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Gem, ID_LISTIMG_Armour );
	m_pID_TEXT_SuccessRatio = (ControlText*)theUiManager.FindControl( ID_FRAME_Gem, ID_TEXT_SuccessRatio );
	m_pID_LISTIMG_Material1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Gem, ID_LISTIMG_Material1 );
	m_pID_LISTIMG_Material2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Gem, ID_LISTIMG_Material2 );
	m_pID_TEXT_Tip3 = (ControlText*)theUiManager.FindControl( ID_FRAME_Gem, ID_TEXT_Tip3 );
	m_pID_TEXT_Effect = (ControlText*)theUiManager.FindControl(ID_FRAME_Gem, ID_TEXT_Effect );
	m_pID_TEXT_Success = (ControlText*)theUiManager.FindControl(ID_FRAME_Gem, ID_TEXT_Success );
	m_pID_TEXT_Fail = (ControlText*)theUiManager.FindControl(ID_FRAME_Gem, ID_TEXT_Fail );
	m_pID_TEXT_EquiqName = (ControlText*)theUiManager.FindControl( ID_FRAME_Gem, ID_TEXT_EquiqName );
	m_pID_TEXT_MaterialName = (ControlText*)theUiManager.FindControl( ID_FRAME_Gem, ID_TEXT_MaterialName );

	assert( m_pID_FRAME_EquipEvolve );
	assert( m_pID_TEXT_Money );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_TEXT_Tip2 );
	assert( m_pID_TEXT_Tip1 );
	assert( m_pID_LIST_GemFunction1 );
	assert( m_pID_LIST_GemFunction2 );
	assert( m_pID_LIST_GemFunction3 );
	assert( m_pID_LIST_GemFunction4 );
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
	assert( m_pID_PICTURE_StarEffect );
	assert( m_pID_TEXT_TipAllDone );
	assert( m_pID_PICTURE_Begin );
	assert( m_pID_LISTIMG_Equip );
	assert( m_pID_TEXT_SuccessRatio );
	assert( m_pID_LISTIMG_Material1 );
	assert( m_pID_LISTIMG_Material2 );
	assert( m_pID_TEXT_Tip3 );
	assert( m_pID_TEXT_EquiqName );
	assert( m_pID_TEXT_MaterialName );

	m_pID_FRAME_EquipEvolve->SetOnVisibleChangedFun( OnVisibleChange );
	InitializeGemBase();
	m_GemInfoList[0] = m_pID_LIST_GemFunction1;
	m_GemInfoList[1] = m_pID_LIST_GemFunction2;
	//m_GemInfoList[2] = m_pID_LIST_GemFunction3;
	//m_GemInfoList[3] = m_pID_LIST_GemFunction4;
	for(int i = 0; i < m_nMaxHoleNum; ++i)
	{
		m_GemInfoList[i]->HaveSelBar( 0, 0 );	
	}
	m_pID_TEXT_Tip1->SetVisable(false);
	m_pID_TEXT_Tip2->SetVisable(false);
	m_pID_TEXT_Tip3->SetVisable(false);
	m_pID_TEXT_TipAllDone->SetVisable(false);
	m_pID_TEXT_Money->SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Gem::_UnLoadUI()
{
	ResetEquipEvolve();
	m_pID_FRAME_EquipEvolve = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\Gem.MEUI" );
}

bool CUI_ID_FRAME_Gem::IsEvolveAllDone( ControlIconDrag::S_ListImg * pImg )
{
	return _IsFullHole(pImg)&&(!_IsExistEmptyHole(pImg));
}

bool CUI_ID_FRAME_Gem::_IsExistEmptyHole( ControlIconDrag::S_ListImg * pImg )
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
			++nGemCount;
		}		
	}

	if (nGemCount == nHole)
	{
		return false;
	}

	return true;

}

void CUI_ID_FRAME_Gem::ClearEquip()
{
	GemBaseUI::ClearEquip();
	for(int i = 0; i < m_nMaxHoleNum; ++i)
	{
		m_GemInfoList[i]->Clear();
		m_HoledPic[i]->SetVisable(false);
		m_UnHolePic[i]->SetVisable(true);
	}
	m_pID_LISTIMG_Material1->Clear();
	m_pID_LISTIMG_Material2->Clear();
	RefreshSuccessRatio();
	SetShowTip(0);

	m_pID_TEXT_SuccessRatio->SetVisable(false);
	m_pID_TEXT_TipAllDone->SetVisable(false);
	m_pID_TEXT_Money->SetVisable(false);

	m_pID_TEXT_EquiqName->SetText("");
	ClearMaterialIcon();
}

void CUI_ID_FRAME_Gem::ResetUIObjects()
{
	GemBaseUI::ResetUIObjects();
	m_pID_TEXT_Tip2 = NULL;
	m_pID_TEXT_Tip1 = NULL;
	for(int i = 0; i < m_nMaxHoleNum; ++i)
	{
		m_GemInfoList[i] = NULL;
	}

}

void CUI_ID_FRAME_Gem::_RefreshEquipInfo( ControlIconDrag::S_ListImg* pListImg )
{
	GemBaseUI::_RefreshEquipInfo(pListImg);
	for (int i = 0; i < m_nsMaxMaterialNum;++i)
	{
		// enable原材料的icon
		if( m_stMaterialIndex[i] != -1 )
		{
			m_n64MaterialGuid[i] = 0;
			// 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
			CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stMaterialIndex[i], true );
			m_stMaterialIndex[i] = -1;
			m_shMaterialBagType[i] = -1;
			m_GemInfoList[i]->Clear();
		}
	}
	SCharItem* pItem = ((SCharItem*)pListImg->m_pkIconInfo->GetData());
	if (NULL == pItem)
	{
		return;
	}
	int nHole = pItem->equipdata.gemHoleCount;
	for(int i = 0; i < nHole; ++i)
	{
		if (pItem->equipdata.gemIds[i] != 0)
		{
			FillGemInfoInList(pItem->equipdata.gemIds[i],m_GemInfoList[i]);
		}
	}
	//m_pID_LISTIMG_Material1->Clear();
	m_pID_LISTIMG_Material2->Clear();
	m_pID_TEXT_SuccessRatio->Clear();
	m_pID_TEXT_Money->Clear();
}

void CUI_ID_FRAME_Gem::OnVisibleChange( ControlObject* pUIObject )
{
	s_CUI_ID_FRAME_Gem.m_status = EquipEvolveUI::EffectStatus_No;
	s_CUI_ID_FRAME_Gem.SetDirty( true );
	s_CUI_ID_FRAME_Gem.ClearEquip();	
	s_CUI_ID_FRAME_Gem.RefreshAllBagEnable();
	s_CUI_ID_FRAME_Gem.OnDirty();
}

void CUI_ID_FRAME_Gem::_SetVisable(const bool bVisable)
{
	if (bVisable)
	{
		OnDirty();
	}
	OnSetVisable(bVisable);
}

bool CUI_ID_FRAME_Gem::UpdateGem()
{


	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	bool isExist = _IsExistEmptyHole(pImg);
	//if (!isExist)
	{
		TipVisible(isExist);
		m_pID_TEXT_Tip3->SetVisable(false);
	}
	/*else
	{
	m_pID_TEXT_Tip1->SetVisable(!isExist);
	m_pID_TEXT_Tip2->SetVisable(!isExist);
	m_pID_TEXT_Tip3->SetVisable(isExist);
	}*/

	ShowMaterialIcon();
	RefreshNeedMoney();
	SetDirty(true);
	return true;
}

void CUI_ID_FRAME_Gem::RClickGemIn( ControlObject* pSender, ControlIconDrag::S_ListImg* pItemDrag )
{
	if (m_stEquipBagIndex == -1)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString(eWarning_Gem_Equip_First) );
		return ;
	}
	int nEmptyHole = GetEmptyHole();
	if (-1 == nEmptyHole)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString(eWarning_NoEmptyHole) );
		return;
	}

	ControlIconDrag::S_ListImg* pListImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	SCharItem* pItem = ((SCharItem*)pListImg->m_pkIconInfo->GetData());
	if (NULL == pItem)
	{
		return;
	}

	if (pItem->equipdata.gemIds[nEmptyHole] != 0)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString(eWarning_GemInHole) );
		return;
	}
	if (!IsGemTypeMatch(pItemDrag))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString(eWarning_GemTypeError) );
		return;
	}

	/*
	* Author: 2012-10-25 17:46:01 wangshuai
	* Desc:   相同类型的宝石镶嵌不作限制
	*/
	/*
	if(IsHaveSameGem(pItemDrag))
	{
	CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Gem_Failed,theXmlString.GetString(eText_Gem_SameType));
	return;
	}*/

	if(m_stMaterialIndex[0] != -1)
	{
		m_n64MaterialGuid[0] = 0;
		CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stMaterialIndex[0], true );
		m_stMaterialIndex[0] = -1;
		m_shMaterialBagType[0] = -1;
	}

	OnDragOnGem(nEmptyHole,pItemDrag,pSender);
}


int CUI_ID_FRAME_Gem::GetEmptyHole()
{

	if (m_stEquipBagIndex == -1)
	{
		return -1;
	}

	ControlIconDrag::S_ListImg* pListImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	SCharItem* pItem = ((SCharItem*)pListImg->m_pkIconInfo->GetData());
	if (NULL == pItem)
	{
		return -1;
	}
	int nHole = pItem->equipdata.gemHoleCount;
	for(int i = 0; i < nHole; ++i)
	{
		if (pItem->equipdata.gemIds[i] == 0)
		{
			//if (m_stMaterialIndex[i] == -1)
			{
				return i;
			}

		}
	}
	return -1;
}

bool CUI_ID_FRAME_Gem::IsGemTypeMatch(ControlIconDrag::S_ListImg* pItemDrag)
{
	if (m_stEquipBagIndex == -1)
	{
		return false;
	}
	ControlIconDrag::S_ListImg* pItemImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
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
	SCharItem* pItem = ((SCharItem*)pItemDrag->m_pkIconInfo->GetData());
	ItemDefine::SItemGem* pGem = ( ItemDefine::SItemGem* )GettheItemDetail().GetItemByID(pItem->GetItemID());
	if( pGem->levelLimit <= pCanEquip->stEquipLevelReq  //符合装备等级
		&& pGem->gemLevel <= nMeLevel																				//符合人物等级
		&& pGem->CanEquipPart(pCanEquip->ustEquipType)																//符合部位需求
		)			
	{
		return true;
	}

	return false;
}

bool CUI_ID_FRAME_Gem::OnDragOnGem( int index, ControlIconDrag::S_ListImg* pItemDrag, ControlObject* pSender )
{
	if (m_stEquipBagIndex == -1)
	{
		return false;
	}

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if( pItemCommon && ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_GEM) )
	{
		ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
		if( !pImageSender )
			return false;

		// 包裹里
		if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pImageSender) )
		{			
			m_stMaterialIndex[0] = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_MaterialBag, pItemDrag );

			SCharItem item;
			if(m_stMaterialIndex[0] != -1 && thePlayerRole.m_bagMaterial.GetItem(m_stMaterialIndex[0],&item))
				m_n64MaterialGuid[0] = item.itembaseinfo.nOnlyInt;
			else
				m_n64MaterialGuid[0] = 0;
			m_shMaterialBagType[0] = BT_MaterialBag;
			ControlIconDrag::S_ListImg liGem;
			liGem.SetData( pItemDrag->m_pkIconInfo->GetItemId(),1,eIcon_Enable );
			m_pID_LISTIMG_Hole[index]->SetItem( &liGem, 0 );
			FillGemInfoInList(item.GetItemID(),m_GemInfoList[index]);
		}
		else
		{
			return false;
		}
		m_bMaterialBagEnable[0] = false;
		UpdateGem();
		SetDirty( true );

		ControlListImage::S_ListImg *pImg = m_pID_LISTIMG_Material1->GetItemByIndex(0);
		if(pImg)
		{
			if(pImg->IsNull())
				SetShowTip(3);
			else
				SetShowTip(0);
		}
	}
	return true;
}

bool CUI_ID_FRAME_Gem::OnGemRemove( int index )
{
	if (m_stMaterialIndex[0] == -1)
	{
		return false;
	}
	if ( m_GemHoleIndex == index )
	{
		return false;
	}
	m_pID_LISTIMG_Hole[index]->Clear();
	m_GemInfoList[index]->Clear();
	m_bMaterialBagEnable[0] = true;				
	SetDirty( true );
	SetShowTip(1);
	return false;
}

int CUI_ID_FRAME_Gem::GetEvolveMoneyCost()
{
	int nMoney = 0;
	for (int i = 0; i < m_nsMaxMaterialNum;++i)
	{
		if( m_stMaterialIndex[i] != -1 )
		{
			SCharItem item;
			thePlayerRole.m_bagMaterial.GetItem(m_stMaterialIndex[i],&item);
			ItemDefine::SItemGem* pGem = ( ItemDefine::SItemGem* )GettheItemDetail().GetItemByID(item.GetItemID());
			if (pGem)
			{
				nMoney += pGem->useCostMoney;
			}
		}
	}
	//因为不需要钱，所以
	return 0;
	//return nMoney;
}

void CUI_ID_FRAME_Gem::SendEvolveMsg()
{
	MsgEquipEvolve msgEvolve;
	msgEvolve.nEvolveType = GetEvolveType();

	msgEvolve.nNormalBagIndex = m_stEquipBagIndex;
	msgEvolve.nNormalGuid      = m_stEquipBagGuid;

	for(int i = 0; i < m_nsMaxMaterialNum; ++i)
	{
		msgEvolve.materials[i].bagType= m_shMaterialBagType[i];
		msgEvolve.materials[i].bagIndex = m_stMaterialIndex[i];
		msgEvolve.materials[i].guid = m_n64MaterialGuid[i];
	}
	msgEvolve.SendEquipMsg();
	//GettheNetworkInput().SendMsg( &msgEvolve );

}

bool CUI_ID_FRAME_Gem::ProcessAllDone( ControlIconDrag::S_ListImg * pImg )
{
	bool bRet = GemBaseUI::ProcessAllDone(pImg);
	if (bRet)
	{
		m_pID_TEXT_Tip2->SetVisable(false);
		m_pID_TEXT_Tip1->SetVisable(false);
	}
	//没宝石和镶嵌符不能合成
	if(m_n64MaterialGuid[0] == 0 || m_n64MaterialGuid[1] == 0)
		return true;

	return bRet;

}

void CUI_ID_FRAME_Gem::TipVisible( bool IsHoleExist )
{
	if (IsHoleExist)
	{
		m_pID_TEXT_Tip2->SetVisable(false);
		m_pID_TEXT_Tip1->SetVisable(true);
	}
	else
	{
		m_pID_TEXT_Tip2->SetVisable(true);
		m_pID_TEXT_Tip1->SetVisable(false);
	}

}

void CUI_ID_FRAME_Gem::RefreshDragEnable( SCharItem* pItem, int index )
{
	// 	if (pItem->equipdata.gemIds[index] != 0)
	// 	{
	// 		m_pID_LISTIMG_Hole[index]->SetEnableDrag(false);
	// 	}
	// 	else
	{
		m_pID_LISTIMG_Hole[index]->SetEnableDrag(true);
	}

}

void CUI_ID_FRAME_Gem::RefreshAllBagEnable()
{
	GemBaseUI::RefreshAllBagEnable();
	m_nSelectMaterialIndex = -1;
	for (int index = 0; index < m_nMaxHoleNum; ++index)
	{
		if (m_stMaterialIndex[index] != -1)
		{
			m_nSelectMaterialIndex = index;
			break;
		}
	}
}

void CUI_ID_FRAME_Gem::RefreshSuccessRatio(void)
{
	ControlListImage::S_ListImg *pImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	if(!pImg)
	{
		m_pID_TEXT_SuccessRatio->SetVisable(false);
		return;
	}

	if(pImg->IsNull())
	{
		m_pID_TEXT_SuccessRatio->SetVisable(false);
		return;
	}

	float ratio = 0.0f;

	for(int index = 1; index <= 2; ++index)
	{
		SCharItem materialItem;
		if(BT_MaterialBag ==m_shMaterialBagType[index] && 
			m_stMaterialIndex[index] != -1)
		{
			bool bSuccess = thePlayerRole.m_bagMaterial.GetItem(m_stMaterialIndex[index],&materialItem);
			assert(bSuccess);
			if(!bSuccess)
				continue;

			ItemDefine::SCreateMaterial *pItem = (ItemDefine::SCreateMaterial *)GettheItemDetail().GetItemByID(materialItem.GetItemID());
			if(pItem != NULL)
			{
				ratio += pItem->fAddIntensifyRate[0];
			}
		}
	}

	if(m_pID_TEXT_SuccessRatio != NULL)
	{
		if(ratio > 100.0f)
			ratio = 100.0f;

		char buf[32];
		MeSprintf_s(buf, sizeof(buf),"%d%%", (int)ratio);
		m_pID_TEXT_SuccessRatio->SetText(buf);
		m_pID_TEXT_SuccessRatio->SetVisable(true);
	}
}

bool CUI_ID_FRAME_Gem::IsHaveSameGem(ControlIconDrag::S_ListImg* pItemDrag)
{
	if(!m_pID_FRAME_EquipEvolve || !pItemDrag)
		return true;

	ItemDefine::SItemCommon* pGemCommon = GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->Id());
	if(!pGemCommon)
		return true;

	if(pGemCommon->ucItemType != ItemDefine::ITEMTYPE_GEM)
		return true;

	ItemDefine::SItemGem* pMaterialGem = (ItemDefine::SItemGem*)pGemCommon;
	int nGemType = pMaterialGem->gemType;

	ControlIconDrag::S_ListImg* pListImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	SCharItem* pItem = ((SCharItem*)pListImg->m_pkIconInfo->GetData());
	if (!pItem)
		return true;

	for (int i = 0;i < pItem->equipdata.gemHoleCount;++i)
	{
		if(pItem->equipdata.gemIds[i] != 0)
		{
			ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID(pItem->equipdata.gemIds[i]);
			if(pCommon->ucItemType != ItemDefine::ITEMTYPE_GEM)
				return true;

			ItemDefine::SItemGem* pGem = (ItemDefine::SItemGem*)pCommon;
			if(pGem->gemType == nGemType)
				return true;
		}
	}

	return false;
}

void CUI_ID_FRAME_Gem::SetRatioVisable(bool bValue)
{
	if(!m_pID_FRAME_EquipEvolve)
		return;

	m_pID_TEXT_Money->SetVisable(bValue);
	m_pID_TEXT_SuccessRatio->SetVisable(bValue);
}

void CUI_ID_FRAME_Gem::SetShowTip(int nValue)
{
	if(!m_pID_FRAME_EquipEvolve)
		return;

	m_pID_TEXT_Tip1->SetVisable(false);
	m_pID_TEXT_Tip2->SetVisable(false);
	m_pID_TEXT_Tip3->SetVisable(false);

	if(nValue == 1)
		m_pID_TEXT_Tip1->SetVisable(true);
	else if(nValue == 2)
		m_pID_TEXT_Tip2->SetVisable(true);
	else if(nValue == 3)
		m_pID_TEXT_Tip3->SetVisable(true);
}

void CUI_ID_FRAME_Gem::ShowItemName(ControlText* pText, ControlIconDrag::S_ListImg* pItemDrag)
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

ControlIconDrag::S_ListImg* CUI_ID_FRAME_Gem::RetriveMaterialImg( short itemId ,int& nIndex)
{
	nIndex = -1;
	ControlListImage* pMaterialBag = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag);
	for(int index = 0; index < pMaterialBag->GetItemCnt(); ++index)
	{
		ControlIconDrag::S_ListImg * pListImg = pMaterialBag->GetItemByIndex(index);
		if (!pListImg || pListImg->IsNull() || NULL == pListImg->m_pkIconInfo)
		{
			continue;
		}
		if (pListImg->m_pkIconInfo->Id() == itemId)
		{
			nIndex =  index;
			return pListImg;
		}						
	}
	return NULL;
}

void CUI_ID_FRAME_Gem::ShowMaterialIcon()
{
	if (!m_pID_LISTIMG_Equip || !m_pID_LISTIMG_Material1 || !m_pID_TEXT_MaterialName)
		return;
	ClearMaterialIcon();
	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	if (!pImg || pImg->IsNull())
		return;

	int nBagIndex = -1;
	ControlIconDrag::S_ListImg * pListImgItem = RetriveMaterialImg(SID_Gem_Material,nBagIndex);
	ControlIconDrag::S_ListImg ImgItem;
	if (NULL == pListImgItem)
	{
		ImgItem.SetData(SID_Gem_Material,1,eIcon_Disable);
		pListImgItem = &ImgItem;
		m_pID_LISTIMG_Material1->SetItem( pListImgItem );
	}
	else
	{
		m_pID_LISTIMG_Material1->SetItem( pListImgItem );
		 m_pID_LISTIMG_Material1->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;	
		m_n64MaterialGuid[1] = pListImgItem->m_pkIconInfo->GetOnlyId();
		m_stMaterialIndex[1] = nBagIndex;
			//CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, nBagIndex, true );
		m_bMaterialBagEnable[1] = false;
		m_shMaterialBagType[1] = BT_MaterialBag;
		
		SetDirty( true );

	}
	ShowItemName(m_pID_TEXT_MaterialName, pListImgItem);
}

void CUI_ID_FRAME_Gem::ClearMaterialIcon()
{
	if (!m_pID_LISTIMG_Material1 || !m_pID_TEXT_MaterialName)
		return;
	m_pID_TEXT_MaterialName->SetText("");

	if(m_n64MaterialGuid[1] == 0)
		return;

	m_pID_LISTIMG_Material1->Clear();
	
	m_bMaterialBagEnable[1] = true;

	SetDirty( true );
}

void CUI_ID_FRAME_Gem::RefreshOkButton()
{
	if (!m_pID_BUTTON_Ok)
		return;
	EquipEvolveUI::RefreshOkButton();

	m_pID_BUTTON_Ok->SetEnable(false);

	if(m_stEquipBagGuid == 0 || m_n64MaterialGuid[0] == 0 || m_n64MaterialGuid[1] == 0)
		return;

	m_pID_BUTTON_Ok->SetEnable(true);
}