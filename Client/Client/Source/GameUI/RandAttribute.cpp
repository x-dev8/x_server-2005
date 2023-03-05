/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\RandAttribute.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "RandAttribute.h"
#include "Pack.h"
#include "UIMgr.h"
#include "PlayerRole.h"
#include "PackItemEnableManager.h"
#include "NetworkInput.h"
#include "XmlStringLanguage.h"
#include "MessageBox.h"

#define DELAY_TIME 350

CUI_ID_FRAME_RandAttribute s_CUI_ID_FRAME_RandAttribute;

MAP_FRAME_RUN( s_CUI_ID_FRAME_RandAttribute, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_RandAttribute, OnFrameRender )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RandAttribute, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RandAttribute, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RandAttribute, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RandAttribute, ID_BUTTON_OkOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_RandAttribute, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_RandAttribute, ID_LISTIMG_ArmourOnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_RandAttribute, ID_LISTIMG_ArmourOnIconRButtonUp )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_RandAttribute, ID_LIST_IntroduceOnListSelectChange )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_RandAttribute, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_RandAttribute, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_RandAttribute, ID_LISTIMG_MaterialOnIconRButtonUp )
CUI_ID_FRAME_RandAttribute::CUI_ID_FRAME_RandAttribute()
{
	// Member
	m_pID_FRAME_RandAttribute = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_TEXT_Introduce = NULL;
	m_pID_LISTIMG_Armour = NULL;
	m_pID_LIST_Introduce = NULL;
	m_pID_TEXT_Success = NULL;
	m_pID_TEXT_Fail = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_TEXT_Material_NotEnougth = NULL;
	m_pID_TEXT_EquipName = NULL;
	m_pID_TEXT_MaterialName = NULL;

	m_status = EffectStatus_No;
	m_ArmourSender = NULL;
	m_MaterialSender = NULL;

}
CUI_ID_FRAME_RandAttribute::~CUI_ID_FRAME_RandAttribute()
{
}
// Frame
bool CUI_ID_FRAME_RandAttribute::OnFrameRun()
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
bool CUI_ID_FRAME_RandAttribute::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_RandAttribute::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	_SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_RandAttribute::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_RandAttribute::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	_SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_RandAttribute::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	SendMsg();
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_RandAttribute::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!pSender || !pItemDrag)
		return false;
	ItemDefine::SItemCommon* pItemCommon = ( ItemDefine::SItemCommon* )GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
	if (!pItemCommon)
		return false;

	if (pItemCommon->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR)
		return false;

	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if ( pCanEquip->bFashion )
		return false;
	if ( !pCanEquip->RandWhenCreate()) //是否有随机属性
		return false;

	int nBagType = s_CUI_ID_FRAME_PACK.GetBagType(dynamic_cast<ControlListImage*>(pSender));
	// 包裹里
	if(!s_CUI_ID_FRAME_PACK.IsListImageByBagType(nBagType, pSender))
		return false;

	ClearImg(IT_Armour, m_pID_LISTIMG_Armour);

	m_ArmourSender = pSender;

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

	m_Armour.nItemBagType = nBagType;
	m_Armour.nItemIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( nBagType, pItemDrag );
	SCharItem item;
	if(m_Armour.nItemIndex != -1 && pdrag_bag->GetItem(m_Armour.nItemIndex,&item))
		m_Armour.nItemGuid = item.itembaseinfo.nOnlyInt;
	else
		m_Armour.nItemGuid = 0;

	m_pID_LISTIMG_Armour->Clear();
	m_pID_LISTIMG_Armour->SetItem( pItemDrag, 0 );
	m_pID_LISTIMG_Armour->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;
	m_pID_LISTIMG_Armour->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;

	if(m_Armour.nItemIndex != -1)
		CPackItemEnableManager::Instance()->RefreshBagItemEnable( pdrag_bag, m_Armour.nItemIndex, true );

	ShowItemName(m_pID_TEXT_EquipName, pItemDrag);
	ShowMaterialIcon();
	RefreshOkButton();
	RefreshItemInfo(item);
	RefreshMoney();

	return false;
}
bool CUI_ID_FRAME_RandAttribute::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_RandAttribute::ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	ClearAll();
	return false;
}
// List
void CUI_ID_FRAME_RandAttribute::ID_LIST_IntroduceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// ListImg / ListEx
bool CUI_ID_FRAME_RandAttribute::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_RandAttribute::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_RandAttribute::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// 装载UI
bool CUI_ID_FRAME_RandAttribute::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\RandAttribute.meui", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\RandAttribute.meui]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_RandAttribute::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_RandAttribute, s_CUI_ID_FRAME_RandAttributeOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_RandAttribute, s_CUI_ID_FRAME_RandAttributeOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_RandAttribute, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_RandAttributeID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RandAttribute, ID_BUTTON_HELP, s_CUI_ID_FRAME_RandAttributeID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RandAttribute, ID_BUTTON_Cancel, s_CUI_ID_FRAME_RandAttributeID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RandAttribute, ID_BUTTON_Ok, s_CUI_ID_FRAME_RandAttributeID_BUTTON_OkOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_RandAttribute, ID_LISTIMG_Armour, s_CUI_ID_FRAME_RandAttributeID_LISTIMG_ArmourOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_RandAttribute, ID_LISTIMG_Armour, s_CUI_ID_FRAME_RandAttributeID_LISTIMG_ArmourOnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_RandAttribute, ID_LISTIMG_Armour, s_CUI_ID_FRAME_RandAttributeID_LISTIMG_ArmourOnIconRButtonUp );
	theUiManager.OnListSelectChange( ID_FRAME_RandAttribute, ID_LIST_Introduce, s_CUI_ID_FRAME_RandAttributeID_LIST_IntroduceOnListSelectChange );
	theUiManager.OnIconDragOn( ID_FRAME_RandAttribute, ID_LISTIMG_Material, s_CUI_ID_FRAME_RandAttributeID_LISTIMG_MaterialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_RandAttribute, ID_LISTIMG_Material, s_CUI_ID_FRAME_RandAttributeID_LISTIMG_MaterialOnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_RandAttribute, ID_LISTIMG_Material, s_CUI_ID_FRAME_RandAttributeID_LISTIMG_MaterialOnIconRButtonUp );

	m_pID_FRAME_RandAttribute = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_RandAttribute );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_RandAttribute, ID_BUTTON_CLOSE );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_RandAttribute, ID_BUTTON_HELP );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_RandAttribute, ID_TEXT_Money );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_RandAttribute, ID_BUTTON_Cancel );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_RandAttribute, ID_BUTTON_Ok );
	m_pID_TEXT_Introduce = (ControlText*)theUiManager.FindControl( ID_FRAME_RandAttribute, ID_TEXT_Introduce );
	m_pID_LISTIMG_Armour = (ControlListImage*)theUiManager.FindControl( ID_FRAME_RandAttribute, ID_LISTIMG_Armour );
	m_pID_LIST_Introduce = (ControlList*)theUiManager.FindControl( ID_FRAME_RandAttribute, ID_LIST_Introduce );
	m_pID_TEXT_Success = (ControlText*)theUiManager.FindControl( ID_FRAME_RandAttribute, ID_TEXT_Success );
	m_pID_TEXT_Fail = (ControlText*)theUiManager.FindControl( ID_FRAME_RandAttribute, ID_TEXT_Fail );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_RandAttribute, ID_LISTIMG_Material );
	m_pID_TEXT_Material_NotEnougth = (ControlText*)theUiManager.FindControl( ID_FRAME_RandAttribute, ID_TEXT_Material_NotEnougth );
	m_pID_TEXT_EquipName = (ControlText*)theUiManager.FindControl( ID_FRAME_RandAttribute, ID_TEXT_EquipName );
	m_pID_TEXT_MaterialName = (ControlText*)theUiManager.FindControl( ID_FRAME_RandAttribute, ID_TEXT_MaterialName );

	assert( m_pID_FRAME_RandAttribute );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_TEXT_Money );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_TEXT_Introduce );
	assert( m_pID_LISTIMG_Armour );
	assert( m_pID_LIST_Introduce );
	assert( m_pID_TEXT_Success );
	assert( m_pID_TEXT_Fail );
	assert( m_pID_LISTIMG_Material );
	assert( m_pID_TEXT_Material_NotEnougth );
	assert( m_pID_TEXT_EquipName );
	assert( m_pID_TEXT_MaterialName );

	m_pID_TEXT_Success->SetVisable(false);
	m_pID_TEXT_Fail->SetVisable(false);
	m_pID_FRAME_RandAttribute->SetOnVisibleChangedFun( OnVisibleChange );
	m_pID_TEXT_Material_NotEnougth->SetVisable(false);
	m_pID_BUTTON_Ok->SetEnable(false);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_RandAttribute::_UnLoadUI()
{
	return theUiManager.RemoveFrame( "Data\\UI\\RandAttribute.meui" );
}
// 是否可视
bool CUI_ID_FRAME_RandAttribute::_IsVisable()
{
	if(!m_pID_FRAME_RandAttribute)
		return false;
	return m_pID_FRAME_RandAttribute->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_RandAttribute::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_RandAttribute)
		return;
	m_pID_FRAME_RandAttribute->SetVisable( bVisable );

	if (bVisable)
	{
		s_CUI_ID_FRAME_PACK.SetVisable(bVisable);
		ResetWindowPosition(m_pID_FRAME_RandAttribute, s_CUI_ID_FRAME_PACK.GetFrame());
	}
}

bool CUI_ID_FRAME_RandAttribute::IsPackItemBeUsing( __int64 nGuid )
{
	if( !IsVisable() || nGuid <= 0 )
		return false;

	if (m_Armour.nItemGuid == nGuid)
		return true;

	if (m_Material.nItemGuid == nGuid)
		return true;

	return false;
}

void CUI_ID_FRAME_RandAttribute::OnVisibleChange( ControlObject* pUIObject )
{
	s_CUI_ID_FRAME_RandAttribute.ClearAll();
}

void CUI_ID_FRAME_RandAttribute::ClearAll()
{
	ClearImg(IT_Armour, m_pID_LISTIMG_Armour);
	ClearImg(IT_Material, m_pID_LISTIMG_Material);

	m_status = EffectStatus_No;
	m_ArmourSender = NULL;
	m_MaterialSender = NULL;
	m_pID_TEXT_Material_NotEnougth->SetVisable(false);
}

void CUI_ID_FRAME_RandAttribute::ShowItemName(ControlText* pText, ControlIconDrag::S_ListImg* pItemDrag)
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

void CUI_ID_FRAME_RandAttribute::ClearImg(ImgTpye itype,ControlListImage *pTargetImg)
{
	if (!pTargetImg)
		return;
	pTargetImg->Clear();

	CItemBag2* pTargetBag;
	int bagIndex = -1;
	switch (itype)
	{
	case IT_Armour:
		{
			switch (m_Armour.nItemBagType)
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
			bagIndex = m_Armour.nItemIndex;
			m_Armour.nItemBagType = 0;
			m_Armour.nItemIndex = -1;
			m_Armour.nItemGuid = 0;

			m_pID_TEXT_EquipName->SetText("");
			m_pID_LIST_Introduce->Clear();
		}
		break;
	case IT_Material:
		{
			pTargetBag = &thePlayerRole.m_bagMaterial;
			bagIndex = m_Material.nItemIndex;
			m_Material.nItemBagType = 0;
			m_Material.nItemIndex = -1;
			m_Material.nItemGuid = 0;

			m_pID_TEXT_MaterialName->SetText("");
			m_pID_TEXT_Material_NotEnougth->SetVisable(false);
		}
		break;
	}

	if(bagIndex != -1)
		CPackItemEnableManager::Instance()->RefreshBagItemEnable( pTargetBag, bagIndex, true );

	RefreshOkButton();
	RefreshMoney();
}

void CUI_ID_FRAME_RandAttribute::RefreshOkButton()
{
	if (!m_pID_BUTTON_Ok)
		return;
	m_pID_BUTTON_Ok->SetEnable(false);

	if (m_Armour.nItemIndex == -1)
		return;
	if (m_Material.nItemIndex == -1)
		return;

	ControlIconDrag::S_ListImg* pImg = s_CUI_ID_FRAME_PACK.GetItemByIndex(m_Material.nItemBagType, m_Material.nItemIndex);
	if (!pImg)
		return;
	ItemDefine::SCreateMaterial *pMaterialItem = (ItemDefine::SCreateMaterial *)GettheItemDetail().GetItemByID( pImg->m_pkIconInfo->GetItemId());
	if (!pMaterialItem)
		return;

	if(!thePlayerRole.HaveEnoughMoney(pMaterialItem->useCostMoney))
		return;

	m_pID_BUTTON_Ok->SetEnable(true);
}

void CUI_ID_FRAME_RandAttribute::RefreshItemInfo(SCharItem &m_item)
{
	if (m_item.itembaseinfo.ustItemID != 0)
	{
		DWORD dwBlue   = 0xff06a2ff;
		ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID(m_item.itembaseinfo.ustItemID);
		if( !pItemCommon )
			return;
		ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
		if( !pCanEquip )
			return;
		m_pID_LIST_Introduce->Clear();
		ControlList::S_List sList;
		sList.UseSelColor = false;
		// 随机属性
		if( pCanEquip->ucItemType != ItemDefine::ITEMTYPE_ARMOUR  && pCanEquip->ucItemType != ItemDefine::ITEMTYPE_WEAPON )
			return;			

		int nRandValue = 0;
		char szTemp[256] = {0};
		int nTipPreTextIndex = 0;
		for (int nloop = 0; nloop < SCharItem::EConstDefine_BaseRandMaxCount; nloop++)
		{
			ItemDefine::SRandAttribute* pArmourRand = NULL;
			unsigned short usRand =m_item.equipdata.baseRands[nloop];
			if( usRand == InvalidLogicNumber )//
			{   
				continue;
			}

			pArmourRand = GettheItemDetail().GetRandByID(m_item.equipdata.baseRands[nloop]);

			if (!pArmourRand)
				continue;

			for( int i = 0 ; i < ItemDefine::SRandAttribute::CD_TypeCount ; ++ i )
			{
				nRandValue = S_IconInfoHero::GetRandValueByType( pArmourRand, i );
				if( pArmourRand->type[i] == RT_None )
					continue;
				float intensity = GettheItemDetail().GetEquipQualityIntensity(m_item.equipdata.quality);
				int  m_value = (float)nRandValue*intensity;
				sprintf( szTemp, "%s+%d", S_IconInfoHero::GetRandStringByType( pArmourRand->type[i] ).c_str(), m_value>0? m_value:1 );
				nTipPreTextIndex ++ ;
				sList.clear();
				sList.SetData( szTemp, 0, 0, dwBlue );
				sList.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
				m_pID_LIST_Introduce->AddItem( &sList );					
			}
		}
	}
}

void CUI_ID_FRAME_RandAttribute::SendMsg()
{
	MsgRandAttrReq msg;

	if (m_Armour.nItemIndex == -1 || m_Material.nItemIndex == -1)
		return;

	msg.sArmour.nItemBagType = m_Armour.nItemBagType;
	msg.sArmour.nItemIndex = m_Armour.nItemIndex;
	msg.sArmour.nItemGuid = m_Armour.nItemGuid;

	msg.sMaterial.nItemBagType = m_Material.nItemBagType;
	msg.sMaterial.nItemGuid = m_Material.nItemGuid;
	msg.sMaterial.nItemIndex = m_Material.nItemIndex;

	//检查材料是否绑定
	SCharItem pEquip;
	SCharItem pItem;
	if(thePlayerRole.GetBagItemByGUID(m_Material.nItemGuid,&pItem) &&
		thePlayerRole.GetBagItemByGUID(m_Armour.nItemGuid,&pEquip) )
	{
		if(!pEquip.IsBounded() && pItem.IsBounded())
			s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_EquipMaterialBound), "", CUI_ID_FRAME_MessageBox::eTypeYesNo, true, MsgEquipEvolve::EquipMaterialSendMsg,&msg,msg.GetLength());
		else
			GettheNetworkInput().SendMsg( &msg );
	}
	else
		GettheNetworkInput().SendMsg( &msg );
}

void CUI_ID_FRAME_RandAttribute::UpdataAll()
{
	if (m_Armour.nItemIndex != -1 && m_ArmourSender)
	{
		ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( m_Armour.nItemBagType, m_Armour.nItemIndex );
		if (!pItemImg || pItemImg->IsNull())
		{
			ClearAll();
		}
		else
			ID_LISTIMG_ArmourOnIconDragOn(m_ArmourSender, NULL, pItemImg, 0);
	}
}

void CUI_ID_FRAME_RandAttribute::ShowMaterialIcon()
{
	if (!m_pID_LISTIMG_Armour || !m_pID_LISTIMG_Material)
		return;
	ClearImg(IT_Material, m_pID_LISTIMG_Material);

	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Armour->GetItemByIndex(0);
	if (!pImg || pImg->IsNull())
		return;

	int nBagIndex = -1;
	ControlIconDrag::S_ListImg * pListImgItem = RetriveMaterialImg(SID_RandAttr_Material,nBagIndex);
	ControlIconDrag::S_ListImg ImgItem;
	if (NULL == pListImgItem)
	{
		ImgItem.SetData(SID_RandAttr_Material,1,eIcon_Disable);
		pListImgItem = &ImgItem;
		m_pID_LISTIMG_Material->SetItem( pListImgItem );
		m_pID_TEXT_Material_NotEnougth->SetVisable(true);
	}
	else
	{
		m_pID_LISTIMG_Material->SetItem( pListImgItem );
		m_Material.nItemBagType = BT_MaterialBag;
		m_Material.nItemGuid = pListImgItem->m_pkIconInfo->GetOnlyId();

		if (nBagIndex != -1)
		{
			m_Material.nItemIndex = nBagIndex;
			CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_Material.nItemIndex, true );
		}

		m_pID_TEXT_Material_NotEnougth->SetVisable(false);
	}

	ShowItemName(m_pID_TEXT_MaterialName, pListImgItem);
}

ControlIconDrag::S_ListImg* CUI_ID_FRAME_RandAttribute::RetriveMaterialImg( short itemId ,int& nIndex)
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

void CUI_ID_FRAME_RandAttribute::RefreshMoney()
{
	if (!m_pID_TEXT_Money)
		return;
	m_pID_TEXT_Money->SetText("");

	if (m_Armour.nItemIndex == -1)
		return;
	if (m_Material.nItemIndex == -1)
		return;

	ControlIconDrag::S_ListImg* pImg = s_CUI_ID_FRAME_PACK.GetItemByIndex(m_Material.nItemBagType, m_Material.nItemIndex);
	if (!pImg)
		return;
	ItemDefine::SCreateMaterial *pMaterialItem = (ItemDefine::SCreateMaterial *)GettheItemDetail().GetItemByID( pImg->m_pkIconInfo->GetItemId());
	if (!pMaterialItem)
		return;

	if (pMaterialItem->useCostMoney <= 0)
		return;

	std::string text = "";
	thePlayerRole.GetGSCStringFromJiaoZi(pMaterialItem->useCostMoney, text);
	DWORD dwColor = 0xffffffff;
	if(!thePlayerRole.HaveEnoughMoney(pMaterialItem->useCostMoney))
	{
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_StarLEvolveNoMomeny), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true);
		dwColor = 0xffff0000;
	}

	m_pID_TEXT_Money->SetText(text,dwColor);
}