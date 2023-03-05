/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\Star.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Star.h"
#include "Pack.h"
#include "NetworkInput.h"
#include "PlayerRole.h"
#include "Core/Name.h"
#include "XmlStringLanguage.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "UIBase.h"
#include "StarLevelUpConfig.h"
#include "MeUI/ExpressionManager.h"
#include "ScreenInfoManager.h"
#include "color_config.h"
#include "IconManagerClient.h"
#include "GlobalDef.h"
#include "Common.h"
#include "Cfg.h"
#include "PackItemEnableManager.h"
#include "MessageBox.h"

#define SET_STAR_VISIBLE( n, star ) if( star == n )m_pID_PICTURE_Star##n->SetVisable( true )
#define SET_NEXTSTAR_VISIBLE( n, star ) if( star == n )m_pID_PICTURE_NextStar##n->SetVisable( true )

#define DELAY_TIME 350

CUI_ID_FRAME_Star s_CUI_ID_FRAME_Star;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Star, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Star, OnFrameRender )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Star, ID_BUTTON_CLOSEOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Star, ID_BUTTON_helpOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_ArmourOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_ArmourOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_ArmourOnIconRButtonUp )
// MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_EspecialOnIconDragOn )
// MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_EspecialOnIconLDBClick )
// MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_EspecialOnIconButtonClick )
// MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_EspecialOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Star, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Star, ID_BUTTON_CancelOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Star, ID_LIST_ArmourPropertyOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Star, ID_LIST_TargetPropertyOnListSelectChange )
// MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_Especial2OnIconDragOn )
// MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_Especial2OnIconLDBClick )
// MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_Especial2OnIconButtonClick )
// MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_Especial2OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_TargetOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_TargetOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_TargetOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Star, ID_LISTIMG_TargetOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Star, ID_BUTTON_AutoUpOnButtonClick )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_Star, ID_COMBOBOX_AutoUpOnComboBoxChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Star, ID_BUTTON_StopOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Star, ID_CHECKBOX_AutoUpOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Star, ID_CHECKBOX_X1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Star, ID_CHECKBOX_X2OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Star, ID_CHECKBOX_X3OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Star, ID_CHECKBOX_X4OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Star, ID_CHECKBOX_Protect_NoUseOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Star, ID_CHECKBOX_Protect_SixStarOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Star, ID_CHECKBOX_Protect_NineStarOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Star, ID_CHECKBOX_Protect_TwelStarOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Star, ID_CHECKBOX_Protect_FiftStarOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Star, ID_CHECKBOX_Never_PromptOnCheckBoxCheck )

CUI_ID_FRAME_Star::CUI_ID_FRAME_Star()
{
	// Member
	ResetUIObjects();
	m_bStartAnim = false;
}
void CUI_ID_FRAME_Star::ResetUIObjects()
{
	EquipEvolveUI::ResetUIObjects();
// 	m_pID_PICTURE_title2 = NULL;
// 	m_pID_PICTURE_title = NULL;
// 	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
	//m_pID_LISTIMG_Especial = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_UseMoneyZ = NULL;
	m_pID_TEXT_Prompt = NULL;
	//m_pID_TEXT_TargetPrompt = NULL;
	m_pID_LIST_ArmourProperty = NULL;
	m_pID_LIST_TargetProperty = NULL;
// 	m_pID_PICTURE_Gray = NULL;
// 	m_pID_PICTURE_Yellow = NULL;
// 	m_pID_PICTURE_ItemGray = NULL;
	m_pID_PICTURE_ItemYellow = NULL;
	m_pID_PICTURE_MaterialGray = NULL;
	m_pID_PICTURE_MaterialYellow = NULL;
	m_pID_PICTURE_EspecialGray = NULL;
	m_pID_PICTURE_EspecialYellow = NULL;
	//m_pID_TEXT_Star = NULL;
	m_pID_PICTURE_Star18 = NULL;
	m_pID_PICTURE_Star17 = NULL;
	m_pID_PICTURE_Star16 = NULL;
	m_pID_PICTURE_Star15 = NULL;
	m_pID_PICTURE_Star14 = NULL;
	m_pID_PICTURE_Star13 = NULL;
	m_pID_PICTURE_Star12 = NULL;
	m_pID_PICTURE_Star11 = NULL;
	m_pID_PICTURE_Star10 = NULL;
	m_pID_PICTURE_Star9 = NULL;
	m_pID_PICTURE_Star8 = NULL;
	m_pID_PICTURE_Star7 = NULL;
	m_pID_PICTURE_Star6 = NULL;
	m_pID_PICTURE_Star5 = NULL;
	m_pID_PICTURE_Star4 = NULL;
	m_pID_PICTURE_Star3 = NULL;
	m_pID_PICTURE_Star2 = NULL;
	m_pID_PICTURE_Star1 = NULL;
	m_pID_PICTURE_Star0 = NULL;
	//m_pID_LISTIMG_Especial2 = NULL;
	m_pID_LISTIMG_Target = NULL;

	//m_pID_PICTURE_ItemWall = NULL;
	//m_pID_PICTURE_TargetWall = NULL;

	//m_pID_TEXT_NextStar = NULL;
	m_pID_PICTURE_NextStar18 = NULL;
	m_pID_PICTURE_NextStar17 = NULL;
	m_pID_PICTURE_NextStar16 = NULL;
	m_pID_PICTURE_NextStar15 = NULL;
	m_pID_PICTURE_NextStar14 = NULL;
	m_pID_PICTURE_NextStar13 = NULL;
	m_pID_PICTURE_NextStar12 = NULL;
	m_pID_PICTURE_NextStar11 = NULL;
	m_pID_PICTURE_NextStar10 = NULL;
	m_pID_PICTURE_NextStar9 = NULL;
	m_pID_PICTURE_NextStar8 = NULL;
	m_pID_PICTURE_NextStar7 = NULL;
	m_pID_PICTURE_NextStar6 = NULL;
	m_pID_PICTURE_NextStar5 = NULL;
	m_pID_PICTURE_NextStar4 = NULL;
	m_pID_PICTURE_NextStar3 = NULL;
	m_pID_PICTURE_NextStar2 = NULL;
	m_pID_PICTURE_NextStar1 = NULL;
	m_pID_PICTURE_NextStar0 = NULL;

	m_pID_TEXT_MaterialName = NULL;
	m_pID_TEXT_EquipName = NULL;
	m_pID_TEXT_PeotectName = NULL;
	m_pID_TEXT_T4 = NULL;

	m_shRateMaterialBagType    = -1;
	m_stRateMaterialIndex = -1;
	m_n64RateMaterialGuid = 0;
	m_bRateMaterialBagEnable = true;

	m_stProtectMaterialIndex = -1;
	m_n64ProtectMaterialGuid = 0;
	m_bProtectMaterialBagEnable = true;
    m_stProtectMaterialBagType = -1;
	m_pID_CHECKBOX_AutoUp = NULL;

	m_IsMaterialBound = false;
	m_IsEquipBound = false;
	m_IsProtectMaterialBound = false;

}

void CUI_ID_FRAME_Star::SetAtomVisible( bool bVisible )
{
	if( !m_pID_FRAME_EquipEvolve )
		return;
	EquipEvolveUI::SetAtomVisible(bVisible);
	m_pID_LISTIMG_Target->SetVisable( bVisible );
	m_pID_PICTURE_ItemYellow->SetVisable( bVisible );
	m_pID_PICTURE_MaterialYellow->SetVisable( bVisible );
	m_pID_PICTURE_EspecialYellow->SetVisable( bVisible );
	m_pID_TEXT_Prompt->SetVisable( !bVisible );
// 	m_pID_LIST_ArmourProperty->SetVisable( bVisible );
// 	m_pID_LIST_TargetProperty->SetVisable( bVisible );
// 	m_pID_TEXT_Equip1->SetVisable(bVisible);
// 	m_pID_TEXT_Equip2->SetVisable(bVisible);
}
void CUI_ID_FRAME_Star::RefreshAllBagEnable()
{
	if( !m_pID_FRAME_EquipEvolve )
		return;
	EquipEvolveUI::RefreshAllBagEnable();
	// 颜色ui全灰

	if( m_stRateMaterialIndex != -1 )
	{
        if( m_bRateMaterialBagEnable )
        {
            m_n64RateMaterialGuid = 0;
        }
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stRateMaterialIndex, true );
		theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
		m_pID_PICTURE_EspecialYellow->SetVisable( true );
	}	

	if( m_stProtectMaterialIndex != -1 )
	{
        if( m_bProtectMaterialBagEnable )
        {
            m_n64ProtectMaterialGuid = 0;
        }
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stProtectMaterialIndex, true );
		theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
	}	
}
// Frame
bool CUI_ID_FRAME_Star::OnFrameRun()
{
	OnDirty();
	DWORD dwTimeNow = timeGetTime();
	switch (m_status)
	{
	case EffectStatus_Start:
		if (/*dwTimeNow-dwBeginTime>=DELAY_TIME && */m_bSendMsg ) //按钮cd时间1秒
		{
			if (OnOkClick())
			{
				//m_pID_BUTTON_Ok->SetEnable(false);
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
		if(dwTimeNow-dwBeginTime>=DELAY_TIME)
			m_status = EffectStatus_No;
		m_bSendMsg = false;
		break;
	case EffectStatus_Success:
		//m_pID_BUTTON_Ok->SetEnable(true);
		if(m_pID_TEXT_Success) m_pID_TEXT_Success->SetVisable(true);
		if(m_pID_TEXT_Fail) m_pID_TEXT_Fail->SetVisable(false);
		if(m_pID_TEXT_Effect) m_pID_TEXT_Effect->SetVisable(false);
		if(dwTimeNow-dwBeginTime>=DELAY_TIME) 
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
	if (m_bWaitNextAuto)
	{
		if (m_bAutoLevelUp)
		{
			if (dwTimeNow - m_dwLastLevelUpTime > gCfg.m_dwAutoStarLevelUpInterval)
			{
				m_dwLastLevelUpTime = dwTimeNow;
				OnOkClick();
				m_bWaitNextAuto = false;
			}
		}
		else
		{
			m_bWaitNextAuto = false;
		}
	}
	return true;
}
bool CUI_ID_FRAME_Star::OnFrameRender()
{
	OnRender();
	return true;
}

bool CUI_ID_FRAME_Star::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														ControlIconDrag::S_ListImg* pItemDrag,
														ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_EquipEvolve )
		return false;
	if( !pItemDrag )
		return false;
	// 包裹里
	if(!s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) && !s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender))
		return false;

	if (OnMaterialDragOn(pItemDrag, pSender))
	{
		ShowMaterialName(pItemDrag);

		SCharItem* pMaterialItem = (SCharItem*)pItemDrag->m_pkIconInfo->GetData();
		if ( pMaterialItem )
			m_IsMaterialBound = pMaterialItem->IsBounded();
	}
	return false;
}
bool CUI_ID_FRAME_Star::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_EquipEvolve)
		return false;
	return false;
}
bool CUI_ID_FRAME_Star::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_EquipEvolve)
		return false;
	/*if (pItem == NULL)
	{
		return false;
	}
	for (int i = 0; i < m_nsMaxMaterialNum; ++i)
	{
		if (m_stMaterialIndex[i] != -1)
		{
			ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( BT_MaterialBag, m_stMaterialIndex[i]  );
			if (pItem->m_pkIconInfo->GetItemId() == pItemImg->m_pkIconInfo->GetItemId())
			{
				m_nSelectMaterialIndex = i;
			}
		}
	}*/
	//SetSelectItem(pItem);
	return false;
}
bool CUI_ID_FRAME_Star::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_EquipEvolve )
		return false;
	m_pID_LISTIMG_Material->Clear();
	m_pID_TEXT_Tip1->SetVisable(true);
	m_pID_BUTTON_Ok->SetEnable(false);
	m_pID_TEXT_T3->SetVisable(false);
	m_pID_TEXT_Money->SetText("");
	m_pID_TEXT_SuccessRatio->SetText("");
	m_pID_TEXT_MaterialName->SetText("");
	m_IsMaterialBound = false;

	m_nSelectMaterialIndex = -1;
	for (int i = 0; i < m_nsMaxMaterialNum; ++i)
	{
		// enable原材料的icon
		if( m_stMaterialIndex[i] != -1 )
		{
			m_n64MaterialGuid[i] = 0;

			// 刷背包物品 Enable 态统一流程     modified by zhuomeng.hu		[12/30/2010]
			CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stMaterialIndex[i], true );
			theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
			m_stMaterialIndex[i] = -1;
			m_shMaterialBagType[i] = -1;
		}
	}
	
	return false;
}

void CUI_ID_FRAME_Star::UpdateProtectGem()
{
}

void CUI_ID_FRAME_Star::UpdateAddRateGem()
{
}
bool CUI_ID_FRAME_Star::UpdateGem()
{
	if( !m_pID_FRAME_EquipEvolve )
		return false;
	if( !IsVisable() )
		return false;

	SetSelectItem(NULL);
	EquipEvolveUI::UpdateGem();
	//SetSelectItem(m_pSelectItem);
	return true;
}
void CUI_ID_FRAME_Star::ClearEquip()
{
	if( !m_pID_FRAME_EquipEvolve )
		return;
	EquipEvolveUI::ClearEquip();
	m_pID_LISTIMG_Target->Clear();
	SetAutoLevelUp(false);
	m_bWaitNextAuto = false;
	m_dwLastLevelUpTime = 0;
	m_pID_TEXT_MaterialName->SetText("");
	m_pID_TEXT_EquipName->SetText("");
	m_pID_TEXT_PeotectName->SetText("");
	m_pID_CHECKBOX_Protect_NoUse->SetCheck(false);
	m_lastStarLevel = 0;
	m_IsMaterialBound = false;
	m_IsEquipBound = false;
	m_IsProtectMaterialBound = false;
}

void CUI_ID_FRAME_Star::UpdateArmourInfo( SCharItem* pItem, ControlList* pList, bool bNextLevel )
{
	if( !m_pID_FRAME_EquipEvolve )
		return;
	char szBuf[256] = {0};
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
	if( !pItemCommon )
		return;
	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if( !pCanEquip )
		return;

	pList->Clear();
	// 添加名字
	Common::_tstring tstrName( pItemCommon->GetItemName() );
	S_IconInfoHero::ReplaceSpecifiedName( pItemCommon->ustLevel, tstrName );
	MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char)-1, "%s +%d", tstrName.c_str() ,pItem->equipdata.ucLevel + (int)bNextLevel);
	if (bNextLevel)
	{
		m_pID_TEXT_Equip2->SetText(szBuf,S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel));
	}
	else
	{
		m_pID_TEXT_Equip1->SetText(szBuf,S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel ));
	}
	//这里逐一判断
	if( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON )
	{	
		AddShowString(pCanEquip,pItem,pList, bNextLevel,pItem->IsSoulStamp());
		//AddAttackString(pCanEquip, pItem, pList, bNextLevel,pItem->IsSoulStamp());
	}
	else if( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
	{
		AddShowString(pCanEquip,pItem,pList, bNextLevel,pItem->IsSoulStamp());
		//AddAttackString(pCanEquip, pItem, pList, bNextLevel,pItem->IsSoulStamp());
		ItemDefine::SItemArmour* pArmour = (ItemDefine::SItemArmour*)pCanEquip;
		AddDefendString(pArmour, pItem,  pList,bNextLevel,pItem->IsSoulStamp());
		//添加HP和MP
		//AddHpMpString(pArmour, pItem,  pList,bNextLevel,pItem->IsSoulStamp());
	}
	if( IsStarAllDone(pItem))//max level
	{
		ControlList::S_List sList;
		sList.UseSelColor = false;
		// 添加提示信息
		MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char)-1, "%s", theXmlString.GetString(eText_StarAll) );
		sList.SetData( szBuf );
		pList->AddItem( &sList );
		return;
	}	

}

void CUI_ID_FRAME_Star::_RefreshEquipInfo( ControlIconDrag::S_ListImg* pListImg )
{
	if( !m_pID_FRAME_EquipEvolve )
		return;
	EquipEvolveUI::_RefreshEquipInfo(pListImg);

	//m_pID_LISTIMG_Target->Clear();
    int nLevel = GetItemLevel(pListImg->m_pkIconInfo->GetItemId());
    if(nLevel <= 0)
        return;
	SCharItem* pEquipItem = (SCharItem*)pListImg->m_pkIconInfo->GetData();
	UpdateArmourInfo( pEquipItem, m_pID_LIST_ArmourProperty , false );
	// 显示星
	ShowStar( (int)pEquipItem->equipdata.ucLevel,GetItemLevel(pListImg->m_pkIconInfo->GetItemId()) );
	ShowEquipName(pListImg);
	if (pEquipItem->equipdata.ucLevel >= 6)
		ShowProtectStarIcon();

	m_IsEquipBound = pEquipItem->IsBounded();

#ifndef BANSHU
	if (m_lastStarLevel < 6 && pEquipItem->equipdata.ucLevel >= 6)
	{
		if (!m_pID_CHECKBOX_Protect_NoUse->IsChecked())
			s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_StarLevelUp_NoSelect));
	}
#endif
	m_lastStarLevel = pEquipItem->equipdata.ucLevel;

	/*SetProtectStarBox(pEquipItem->equipdata.ucLevel);
	if (!IsStarAllDone(pEquipItem))
	{
		ControlIconDrag::S_ListImg liTarget;
		SCharItem sItem = *pEquipItem;
		sItem.equipdata.ucLevel++;
		liTarget.SetData( &sItem );
		m_pID_LISTIMG_Target->SetItem( &liTarget, 0 );
		m_pID_LISTIMG_Target->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;				
		UpdateArmourInfo( pEquipItem, m_pID_LIST_TargetProperty , true );
		ShowNextStar( (int)pEquipItem->equipdata.ucLevel + 1,GetItemLevel(pListImg->m_pkIconInfo->GetItemId()) );
	}*/

}
// ListImg / ListEx
bool CUI_ID_FRAME_Star::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
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
	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if (/*pCanEquip->ustEquipType == ItemDefine::equip_AecorativeClothing*/ pCanEquip->bFashion)
		return false;

	if(!s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) && !s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender))
		return false;

    int nLevel = GetItemLevel(pItemDrag->m_pkIconInfo->GetItemId());
    if(nLevel <= 0)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseStar_Failed, theXmlString.GetString(eClient_SkillSuitCannotUpStar) );

        return false;
	}
	if (!IsTypeMatch(pItemDrag))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseStar_Failed, theXmlString.GetString(eClient_SkillSuitCannotUpStar) );
		return false;
	}
	// 只能放入9星以下（包含9星）装备
	if (IsEvolveAllDone(pItemDrag))
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseStar_Failed, theXmlString.GetString(eClient_SkillSuitMaxLevel) );
        return false;
    }

	SetEquipInfoVisable(true);
	OnEquipDragOn(pItemDrag,pSender);
	ShowEquipName(pItemDrag);

	SCharItem* pEquipItem = (SCharItem*)pItemDrag->m_pkIconInfo->GetData();
	if ( pEquipItem )
	{
		m_lastStarLevel = pEquipItem->equipdata.ucLevel;
		m_IsEquipBound = pEquipItem->IsBounded();
	}
	
	return false;
}

void CUI_ID_FRAME_Star::ShowEquipName(ControlIconDrag::S_ListImg* pItemDrag)
{
	if (!m_pID_TEXT_EquipName || !pItemDrag)
		return;
	m_pID_TEXT_EquipName->SetText("");

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

	m_pID_TEXT_EquipName->SetText(temp);

	if (pEquipItem->equipdata.ucLevel < 6)
	{
		m_pID_CHECKBOX_Protect_NoUse->SetEnable(false);
		m_pID_LISTIMG_Target->Clear();
		m_unProtectStarNum = 0;
		m_IsProtectMaterialBound = false;
		m_pID_TEXT_PeotectName->SetText("");
		m_pID_TEXT_Tip2->SetText(theXmlString.GetString(eText_MaterialStar_UnderSix));
	}
	else
	{
		m_pID_CHECKBOX_Protect_NoUse->SetEnable(true);
		m_pID_TEXT_Tip2->SetText(theXmlString.GetString(eText_MaterialStar_BeyondSix));
	}
}

void CUI_ID_FRAME_Star::ShowMaterialName(ControlIconDrag::S_ListImg* pItemDrag)
{
	if (!m_pID_TEXT_MaterialName || !pItemDrag)
		return;
	m_pID_TEXT_MaterialName->SetText("");

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if (!pItemCommon)
		return;

	char temp[128] = {0};
	sprintf(temp, "%s", pItemCommon->GetItemName());
	m_pID_TEXT_MaterialName->SetText(temp);
}

void CUI_ID_FRAME_Star::ShowProtectStarName(ControlIconDrag::S_ListImg* pItemDrag)
{
	if (!m_pID_TEXT_PeotectName || !pItemDrag)
		return;
	m_pID_TEXT_PeotectName->SetText("");

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if (!pItemCommon)
		return;

	char temp[128] = {0};
	sprintf(temp, "%s,%d%s", pItemCommon->GetItemName(), m_unProtectStarNum, theXmlString.GetString(eText_StarProtect_Text));
	m_pID_TEXT_PeotectName->SetText(temp);
}

bool CUI_ID_FRAME_Star::IsTypeMatch(ControlIconDrag::S_ListImg * pImg)
{
	if(pImg == NULL) 
		return false;
	SCharItem* psItem = (SCharItem*)pImg->m_pkIconInfo->GetData();
	if (psItem == NULL) 
		return false;
	ItemDefine::SItemCommon *pCommon = GettheItemDetail().GetItemByID(psItem->itembaseinfo.ustItemID);
	if(pCommon == NULL)
		return false;

	if(pCommon->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR)
		return false;

	ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)pCommon;
	StarLevelUpData* pLevelUpData = theStarLevelUpConfig.GetStarLevelUpData( pItemCanEquip->stEquipLevelReq, psItem->equipdata.ucLevel );
	if(pLevelUpData)
		return true;
	return false;
}
bool CUI_ID_FRAME_Star::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_EquipEvolve)
		return false;
	return false;
}
bool CUI_ID_FRAME_Star::ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_EquipEvolve)
		return false;
	return false;
}
bool CUI_ID_FRAME_Star::ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{		
	ClearEquip();
	m_pID_TEXT_Tip1->SetVisable(true);
	m_pID_TEXT_Tip2->SetText("");
	m_pID_TEXT_T3->SetVisable(false);
	SetEquipInfoVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_Star::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{		
	if (!m_pID_FRAME_EquipEvolve)
		return false;
	//if (-1 == m_nSelectMaterialIndex)
	//{
	//	return false;
	//}
	ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( m_stEquipBagType, m_stEquipBagIndex );
	if( !pItemImg )
		return false;
	SCharItem* pEquipItem = (SCharItem*)pItemImg->m_pkIconInfo->GetData();
	if (!pEquipItem)
		return false;
#ifndef BANSHU
	if (pEquipItem->equipdata.ucLevel >= 6)
	{
		if (!m_unProtectStarNum && m_pID_CHECKBOX_Protect_NoUse->IsChecked())
			s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_NoProtectStarMaterial));
		else
			SetStatusStart();
	}
	else
		SetStatusStart();
#else
	SetStatusStart();
#endif
	
	//OnOkClick();
	return true;
}
bool StarMessageBoxResult(char bSend, void *pData )
{
	if( !bSend )
		return false;
	s_CUI_ID_FRAME_Star.SetStatusStart(false);
	return true;
}
void CUI_ID_FRAME_Star::SetStatusStart(bool CheckBounded)
{
	if(m_IsProtectMaterialBound && CheckBounded)
	{
		//提示玩家装备将会绑定
		SCharItem pEquip;
		if(thePlayerRole.GetBagItemByGUID(m_stEquipBagGuid,&pEquip) && !pEquip.IsBounded())
			s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_EquipMaterialBound), "", CUI_ID_FRAME_MessageBox::eTypeYesNo, true,StarMessageBoxResult);
		else
		{
			dwBeginTime = timeGetTime();
			m_status = EffectStatus_Start;
			m_bSendMsg = true;
		}
	}
	else
	{
		dwBeginTime = timeGetTime();
		m_status = EffectStatus_Start;
		m_bSendMsg = true;
	}
}

void CUI_ID_FRAME_Star::ID_CHECKBOX_AutoUpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (IsVisable())
	{
		if(m_pID_CHECKBOX_AutoUp->IsChecked())
		{
			m_pID_BUTTON_AutoUp->SetVisable(true);
			m_pID_BUTTON_Ok->SetVisable(false);
			m_pID_COMBOBOX_AutoUp->SetVisable(true);
		}
		else
		{
			m_pID_BUTTON_AutoUp->SetVisable(false);
			m_pID_BUTTON_Ok->SetVisable(true);
			m_pID_COMBOBOX_AutoUp->SetVisable(false);
		}
	}
}

// Button
bool CUI_ID_FRAME_Star::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_EquipEvolve)
		return false;
	m_pID_TEXT_Tip1->SetVisable(false);
	m_pID_TEXT_Tip2->SetText("");
	SetVisable( false );
	return true;
}
// List
void CUI_ID_FRAME_Star::ID_LIST_ArmourPropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if (!m_pID_FRAME_EquipEvolve)
		return;
}
// List
void CUI_ID_FRAME_Star::ID_LIST_TargetPropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if (!m_pID_FRAME_EquipEvolve)
		return;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Star::ID_LISTIMG_TargetOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	if (!m_pID_FRAME_EquipEvolve)
		return false;
	return false;
}
bool CUI_ID_FRAME_Star::ID_LISTIMG_TargetOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_EquipEvolve)
		return false;
	return false;
}
bool CUI_ID_FRAME_Star::ID_LISTIMG_TargetOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_EquipEvolve)
		return false;
	return false;
}
bool CUI_ID_FRAME_Star::ID_LISTIMG_TargetOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_EquipEvolve)
		return false;
	return false;
}

// 装载UI
bool CUI_ID_FRAME_Star::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Star.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Star.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Star::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Star, s_CUI_ID_FRAME_StarOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Star, s_CUI_ID_FRAME_StarOnFrameRender );
// 	theUiManager.OnButtonClick( ID_FRAME_Star, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_StarID_BUTTON_CLOSEOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_Star, ID_BUTTON_help, s_CUI_ID_FRAME_StarID_BUTTON_helpOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Star, ID_LISTIMG_Material, s_CUI_ID_FRAME_StarID_LISTIMG_MaterialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Star, ID_LISTIMG_Material, s_CUI_ID_FRAME_StarID_LISTIMG_MaterialOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Star, ID_LISTIMG_Material, s_CUI_ID_FRAME_StarID_LISTIMG_MaterialOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Star, ID_LISTIMG_Material, s_CUI_ID_FRAME_StarID_LISTIMG_MaterialOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Star, ID_LISTIMG_Armour, s_CUI_ID_FRAME_StarID_LISTIMG_ArmourOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Star, ID_LISTIMG_Armour, s_CUI_ID_FRAME_StarID_LISTIMG_ArmourOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Star, ID_LISTIMG_Armour, s_CUI_ID_FRAME_StarID_LISTIMG_ArmourOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Star, ID_LISTIMG_Armour, s_CUI_ID_FRAME_StarID_LISTIMG_ArmourOnIconRButtonUp );
// 	theUiManager.OnIconDragOn( ID_FRAME_Star, ID_LISTIMG_Especial, s_CUI_ID_FRAME_StarID_LISTIMG_EspecialOnIconDragOn );
// 	theUiManager.OnIconLDBClick( ID_FRAME_Star, ID_LISTIMG_Especial, s_CUI_ID_FRAME_StarID_LISTIMG_EspecialOnIconLDBClick );
// 	theUiManager.OnIconButtonClick( ID_FRAME_Star, ID_LISTIMG_Especial, s_CUI_ID_FRAME_StarID_LISTIMG_EspecialOnIconButtonClick );
// 	theUiManager.OnIconRButtonUp( ID_FRAME_Star, ID_LISTIMG_Especial, s_CUI_ID_FRAME_StarID_LISTIMG_EspecialOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_Star, ID_BUTTON_Ok, s_CUI_ID_FRAME_StarID_BUTTON_OkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Star, ID_BUTTON_Cancel, s_CUI_ID_FRAME_StarID_BUTTON_CancelOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Star, ID_LIST_ArmourProperty, s_CUI_ID_FRAME_StarID_LIST_ArmourPropertyOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Star, ID_LIST_TargetProperty, s_CUI_ID_FRAME_StarID_LIST_TargetPropertyOnListSelectChange );
// 	theUiManager.OnIconDragOn( ID_FRAME_Star, ID_LISTIMG_Especial2, s_CUI_ID_FRAME_StarID_LISTIMG_Especial2OnIconDragOn );
// 	theUiManager.OnIconLDBClick( ID_FRAME_Star, ID_LISTIMG_Especial2, s_CUI_ID_FRAME_StarID_LISTIMG_Especial2OnIconLDBClick );
// 	theUiManager.OnIconButtonClick( ID_FRAME_Star, ID_LISTIMG_Especial2, s_CUI_ID_FRAME_StarID_LISTIMG_Especial2OnIconButtonClick );
// 	theUiManager.OnIconRButtonUp( ID_FRAME_Star, ID_LISTIMG_Especial2, s_CUI_ID_FRAME_StarID_LISTIMG_Especial2OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Star, ID_LISTIMG_Target, s_CUI_ID_FRAME_StarID_LISTIMG_TargetOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Star, ID_LISTIMG_Target, s_CUI_ID_FRAME_StarID_LISTIMG_TargetOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Star, ID_LISTIMG_Target, s_CUI_ID_FRAME_StarID_LISTIMG_TargetOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Star, ID_LISTIMG_Target, s_CUI_ID_FRAME_StarID_LISTIMG_TargetOnIconRButtonUp );
theUiManager.OnButtonClick( ID_FRAME_Star, ID_BUTTON_AutoUp, s_CUI_ID_FRAME_StarID_BUTTON_AutoUpOnButtonClick );
theUiManager.OnComboBoxChange( ID_FRAME_Star, ID_COMBOBOX_AutoUp, s_CUI_ID_FRAME_StarID_COMBOBOX_AutoUpOnComboBoxChange );
theUiManager.OnButtonClick( ID_FRAME_Star, ID_BUTTON_Stop, s_CUI_ID_FRAME_StarID_BUTTON_StopOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Star, ID_CHECKBOX_AutoUp, s_CUI_ID_FRAME_StarID_CHECKBOX_AutoUpOnCheckBoxCheck );

	theUiManager.OnCheckBoxCheck( ID_FRAME_Star, ID_CHECKBOX_X1, s_CUI_ID_FRAME_StarID_CHECKBOX_X1OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Star, ID_CHECKBOX_X2, s_CUI_ID_FRAME_StarID_CHECKBOX_X2OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Star, ID_CHECKBOX_X3, s_CUI_ID_FRAME_StarID_CHECKBOX_X3OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Star, ID_CHECKBOX_X4, s_CUI_ID_FRAME_StarID_CHECKBOX_X4OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Star, ID_CHECKBOX_Protect_NoUse, s_CUI_ID_FRAME_StarID_CHECKBOX_Protect_NoUseOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Star, ID_CHECKBOX_Protect_SixStar, s_CUI_ID_FRAME_StarID_CHECKBOX_Protect_SixStarOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Star, ID_CHECKBOX_Protect_NineStar, s_CUI_ID_FRAME_StarID_CHECKBOX_Protect_NineStarOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Star, ID_CHECKBOX_Protect_TwelStar, s_CUI_ID_FRAME_StarID_CHECKBOX_Protect_TwelStarOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Star, ID_CHECKBOX_Protect_FiftStar, s_CUI_ID_FRAME_StarID_CHECKBOX_Protect_FiftStarOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Star, ID_CHECKBOX_Never_Prompt, s_CUI_ID_FRAME_StarID_CHECKBOX_Never_PromptOnCheckBoxCheck );


	m_pID_FRAME_EquipEvolve = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Star );
	m_pID_TEXT_Effect = (ControlText*)theUiManager.FindControl(ID_FRAME_Star, ID_TEXT_Effect );
	m_pID_TEXT_Success = (ControlText*)theUiManager.FindControl(ID_FRAME_Star, ID_TEXT_Success );
	m_pID_TEXT_Fail = (ControlText*)theUiManager.FindControl(ID_FRAME_Star, ID_TEXT_Fail );
// 	m_pID_PICTURE_title2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_title2 );
// 	m_pID_PICTURE_title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_title );
// 	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Star, ID_BUTTON_CLOSE );
// 	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_Star, ID_BUTTON_help );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Star, ID_LISTIMG_Material );
	m_pID_LISTIMG_Equip = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Star, ID_LISTIMG_Armour );
	//m_pID_LISTIMG_Especial = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Star, ID_LISTIMG_Especial );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_Star, ID_BUTTON_Ok );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_Star, ID_BUTTON_Cancel );
	m_pID_TEXT_UseMoneyZ = (ControlText*)theUiManager.FindControl( ID_FRAME_Star, ID_TEXT_UseMoneyZ );
	m_pID_TEXT_Prompt = (ControlText*)theUiManager.FindControl( ID_FRAME_Star, ID_TEXT_Prompt );
	//m_pID_TEXT_TargetPrompt = (ControlText*)theUiManager.FindControl( ID_FRAME_Star, ID_TEXT_TargetPrompt );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_Star, ID_TEXT_UseMoney );
	m_pID_LIST_ArmourProperty = (ControlList*)theUiManager.FindControl( ID_FRAME_Star, ID_LIST_ArmourProperty );
	m_pID_LIST_TargetProperty = (ControlList*)theUiManager.FindControl( ID_FRAME_Star, ID_LIST_TargetProperty );
// 	m_pID_PICTURE_Gray = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Gray );
// 	m_pID_PICTURE_Yellow = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Yellow );
// 	m_pID_PICTURE_ItemGray = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_ItemGray );
	m_pID_PICTURE_ItemYellow = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_ItemYellow );
	m_pID_PICTURE_MaterialGray = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_MaterialGray );
	m_pID_PICTURE_MaterialYellow = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_MaterialYellow );
	m_pID_PICTURE_EspecialGray = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_EspecialGray );
	m_pID_PICTURE_EspecialYellow = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_EspecialYellow );
	//m_pID_TEXT_Star = (ControlText*)theUiManager.FindControl( ID_FRAME_Star, ID_TEXT_Star );
	m_pID_PICTURE_Star18 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Star18 );
	m_pID_PICTURE_Star17 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Star17 );
	m_pID_PICTURE_Star16 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Star16 );
	m_pID_PICTURE_Star15 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Star15 );
	m_pID_PICTURE_Star14 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Star14 );
	m_pID_PICTURE_Star13 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Star13 );
	m_pID_PICTURE_Star12 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Star12 );
	m_pID_PICTURE_Star11 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Star11 );
	m_pID_PICTURE_Star10 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Star10 );
	m_pID_PICTURE_Star9 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Star9 );
	m_pID_PICTURE_Star8 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Star8 );
	m_pID_PICTURE_Star7 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Star7 );
	m_pID_PICTURE_Star6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Star6 );
	m_pID_PICTURE_Star5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Star5 );
	m_pID_PICTURE_Star4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Star4 );
	m_pID_PICTURE_Star3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Star3 );
	m_pID_PICTURE_Star2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Star2 );
	m_pID_PICTURE_Star1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Star1 );
	m_pID_PICTURE_Star0 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Star0 );
// 	m_pID_PICTURE_ItemWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_ItemWall );
// 	m_pID_PICTURE_TargetWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_TargetWall );
// 	m_pID_TEXT_NextStar = (ControlText*)theUiManager.FindControl( ID_FRAME_Star, ID_TEXT_NextStar );
	m_pID_PICTURE_NextStar18 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_NextStar18 );
	m_pID_PICTURE_NextStar17 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_NextStar17 );
	m_pID_PICTURE_NextStar16 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_NextStar16 );
	m_pID_PICTURE_NextStar15 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_NextStar15 );
	m_pID_PICTURE_NextStar14 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_NextStar14 );
	m_pID_PICTURE_NextStar13 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_NextStar13 );
	m_pID_PICTURE_NextStar12 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_NextStar12 );
	m_pID_PICTURE_NextStar11 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_NextStar11 );
	m_pID_PICTURE_NextStar10 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_NextStar10 );
	m_pID_PICTURE_NextStar9 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_NextStar9 );
	m_pID_PICTURE_NextStar8 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_NextStar8 );
	m_pID_PICTURE_NextStar7 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_NextStar7 );
	m_pID_PICTURE_NextStar6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_NextStar6 );
	m_pID_PICTURE_NextStar5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_NextStar5 );
	m_pID_PICTURE_NextStar4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_NextStar4 );
	m_pID_PICTURE_NextStar3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_NextStar3 );
	m_pID_PICTURE_NextStar2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_NextStar2 );
	m_pID_PICTURE_NextStar1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_NextStar1 );
	m_pID_PICTURE_NextStar0 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_NextStar0 );
	//m_pID_LISTIMG_Especial2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Star, ID_LISTIMG_Especial2 );
	m_pID_LISTIMG_Target = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Star, ID_LISTIMG_Target );
		m_pID_TEXT_Equip1 = (ControlText*)theUiManager.FindControl( ID_FRAME_Star, ID_TEXT_Equip1 );
		m_pID_TEXT_Equip2 = (ControlText*)theUiManager.FindControl( ID_FRAME_Star, ID_TEXT_Equip2 );
		m_pID_BUTTON_AutoUp = (ControlButton*)theUiManager.FindControl( ID_FRAME_Star, ID_BUTTON_AutoUp );
		m_pID_TEXT_Tip1 = (ControlText*)theUiManager.FindControl( ID_FRAME_Star, ID_TEXT_Tip1 );
		m_pID_TEXT_Tip2 = (ControlText*)theUiManager.FindControl( ID_FRAME_Star, ID_TEXT_Tip2 );
		m_pID_TEXT_T3 = (ControlText*)theUiManager.FindControl( ID_FRAME_Star, ID_TEXT_T3 );

	m_pID_PICTURE_StarEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_StarEffect );
		m_pID_PICTURE_Begin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Star, ID_PICTURE_Begin );
		m_pID_COMBOBOX_AutoUp = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_Star, ID_COMBOBOX_AutoUp );
		m_pID_BUTTON_Stop = (ControlButton*)theUiManager.FindControl( ID_FRAME_Star, ID_BUTTON_Stop );
		m_pID_TEXT_TipAllDone = (ControlText*)theUiManager.FindControl( ID_FRAME_Star, ID_TEXT_TipAllDone );
		m_pID_TEXT_SuccessRatio = (ControlText*)theUiManager.FindControl( ID_FRAME_Star, ID_TEXT_SuccessRatio );
		//m_pID_TEXT_SuccessRatio->SetText("成功率");
		//m_pID_TEXT_Money->SetText("所需金币");
	m_pID_CHECKBOX_AutoUp = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Star, ID_CHECKBOX_AutoUp );

	m_pID_CHECKBOX_X1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Star, ID_CHECKBOX_X1 );
	m_pID_CHECKBOX_X2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Star, ID_CHECKBOX_X2 );
	m_pID_CHECKBOX_X3 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Star, ID_CHECKBOX_X3 );
	m_pID_CHECKBOX_X4 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Star, ID_CHECKBOX_X4 );
	
	m_pID_CHECKBOX_Protect_NoUse = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Star, ID_CHECKBOX_Protect_NoUse );
	m_pID_CHECKBOX_Protect_SixStar = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Star, ID_CHECKBOX_Protect_SixStar );
	m_pID_CHECKBOX_Protect_NineStar = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Star, ID_CHECKBOX_Protect_NineStar );
	m_pID_CHECKBOX_Protect_TwelStar = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Star, ID_CHECKBOX_Protect_TwelStar );
	m_pID_CHECKBOX_Protect_FiftStar = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Star, ID_CHECKBOX_Protect_FiftStar );
	m_pID_CHECKBOX_Never_Prompt = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Star, ID_CHECKBOX_Never_Prompt );

	m_pID_TEXT_MaterialName = (ControlText*)theUiManager.FindControl( ID_FRAME_Star, ID_TEXT_MaterialName );
	m_pID_TEXT_EquipName = (ControlText*)theUiManager.FindControl( ID_FRAME_Star, ID_TEXT_EquipName );
	m_pID_TEXT_PeotectName = (ControlText*)theUiManager.FindControl( ID_FRAME_Star, ID_TEXT_PeotectName );
	m_pID_TEXT_T4 = (ControlText*)theUiManager.FindControl( ID_FRAME_Star, ID_TEXT_T4 );

	assert(m_pID_CHECKBOX_AutoUp);
	assert( m_pID_CHECKBOX_X1 );
	assert( m_pID_CHECKBOX_X2 );
	assert( m_pID_CHECKBOX_X3 );
	assert( m_pID_CHECKBOX_X4 );
	
	assert( m_pID_CHECKBOX_Protect_NoUse );
	assert( m_pID_CHECKBOX_Protect_SixStar );
	assert( m_pID_CHECKBOX_Protect_NineStar );
	assert( m_pID_CHECKBOX_Protect_TwelStar );
	assert( m_pID_CHECKBOX_Protect_FiftStar );
	assert( m_pID_CHECKBOX_Never_Prompt );
	assert( m_pID_TEXT_MaterialName );
	assert( m_pID_TEXT_EquipName );
	assert( m_pID_TEXT_PeotectName );
	assert( m_pID_TEXT_T4 );

	m_pID_CHECKBOX_AutoUp->SetCheck(false);
	m_pID_COMBOBOX_AutoUp->SetVisable(false);
	m_pID_BUTTON_AutoUp->SetVisable(false);
	m_pID_BUTTON_Ok->SetVisable(true);
	m_pID_CHECKBOX_X1->SetCheck(true);
	m_pID_CHECKBOX_X2->SetCheck(false);
	m_pID_CHECKBOX_X3->SetCheck(false);
	m_pID_CHECKBOX_X4->SetCheck(false);
	m_pID_CHECKBOX_Protect_NoUse->SetCheck(false);
	m_pID_CHECKBOX_Protect_SixStar->SetCheck(false);
	m_pID_CHECKBOX_Protect_NineStar->SetCheck(false);
	m_pID_CHECKBOX_Protect_TwelStar->SetCheck(false);
	m_pID_CHECKBOX_Protect_FiftStar->SetCheck(false);

	m_StarGroup.AddControl(m_pID_PICTURE_Star18);
	m_StarGroup.AddControl(m_pID_PICTURE_Star17);
	m_StarGroup.AddControl(m_pID_PICTURE_Star16);
	m_StarGroup.AddControl(m_pID_PICTURE_Star15);
	m_StarGroup.AddControl(m_pID_PICTURE_Star14);
	m_StarGroup.AddControl(m_pID_PICTURE_Star13);
	m_StarGroup.AddControl(m_pID_PICTURE_Star12);
	m_StarGroup.AddControl(m_pID_PICTURE_Star11);
	m_StarGroup.AddControl(m_pID_PICTURE_Star10);
	m_StarGroup.AddControl(m_pID_PICTURE_Star9);
	m_StarGroup.AddControl(m_pID_PICTURE_Star8);
	m_StarGroup.AddControl(m_pID_PICTURE_Star7);
	m_StarGroup.AddControl(m_pID_PICTURE_Star6);
	m_StarGroup.AddControl(m_pID_PICTURE_Star5);
	m_StarGroup.AddControl(m_pID_PICTURE_Star4);
	m_StarGroup.AddControl(m_pID_PICTURE_Star3);
	m_StarGroup.AddControl(m_pID_PICTURE_Star2);
	m_StarGroup.AddControl(m_pID_PICTURE_Star1);
	m_StarGroup.AddControl(m_pID_PICTURE_Star0);
	m_StarGroup.SetVisible( false );
	
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar18);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar17);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar16);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar15);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar14);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar13);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar12);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar11);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar10);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar9);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar8);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar7);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar6);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar5);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar4);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar3);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar2);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar1);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar0);
	m_NextStarGroup.SetVisible( false );

	m_pID_LIST_ArmourProperty->HaveSelBar( 0, 0 );	
	m_pID_LIST_TargetProperty->HaveSelBar( 0, 0 );
	m_pID_FRAME_EquipEvolve->SetOnVisibleChangedFun( OnVisibleChange );

	m_pID_LISTIMG_Target->SetEnableDrag( false );

	EquipEvolveIntialize();

	char cTmp[256];
	ControlList::S_List listItem;
	for (int i = 1; i <= 18; ++i)
	{
		listItem.clear();
		sprintf_s(cTmp,256,theXmlString.GetString(eText_Star_Star),i);
		listItem.SetData(cTmp);
		listItem.SetMargin( 5 );
		m_pID_COMBOBOX_AutoUp->GetListBox().AddItem(&listItem);
		if (i == 1)
		{
			m_pID_COMBOBOX_AutoUp->GetEditInput().SetText(cTmp);
			m_nMaxAutoLevelUp = 1;
		}
	}
	SetAutoLevelUp(false);
	m_bWaitNextAuto = false;
	m_dwLastLevelUpTime = 0;

	m_pID_TEXT_Tip1->SetVisable(true);
	m_pID_TEXT_Tip2->SetVisable(true);
	m_pID_TEXT_Tip2->SetText("");
	m_pID_TEXT_T3->SetVisable(false);
	SetEquipInfoVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Star::_UnLoadUI()
{
	ResetEquipEvolve();
	m_StarGroup.Clear();
	m_NextStarGroup.Clear();
	return theUiManager.RemoveFrame( "Data\\UI\\Star.MEUI" );
}

void CUI_ID_FRAME_Star::OnVisibleChange( ControlObject* pUIObject )
{
	s_CUI_ID_FRAME_Star.m_status = EffectStatus_No;
	s_CUI_ID_FRAME_Star.SetDirty( true );
	s_CUI_ID_FRAME_Star.ClearEquip();
	s_CUI_ID_FRAME_Star.SetAutoLevelUp(false);
	s_CUI_ID_FRAME_Star.RefreshAllBagEnable();
	s_CUI_ID_FRAME_Star.SetEquipInfoVisable(false);
}

void CUI_ID_FRAME_Star::ShowStar( int nStar ,int nLevel )
{
	if( !m_pID_FRAME_EquipEvolve )
		return;
	int nMaxLevel = 18;

	nStar = min( nMaxLevel, nStar );
	m_StarGroup.SetVisible( false );
	//for (int i=0;i<=nMaxLevel;i++)
	//{
	//	SET_STAR_VISIBLE( i, nStar );
	//}
	SET_STAR_VISIBLE( 0, nStar );
	SET_STAR_VISIBLE( 1, nStar );
	SET_STAR_VISIBLE( 2, nStar );
	SET_STAR_VISIBLE( 3, nStar );
	SET_STAR_VISIBLE( 4, nStar );
	SET_STAR_VISIBLE( 5, nStar );
	SET_STAR_VISIBLE( 6, nStar );
	SET_STAR_VISIBLE( 7, nStar );
	SET_STAR_VISIBLE( 8, nStar );
	SET_STAR_VISIBLE( 9, nStar );
	SET_STAR_VISIBLE( 10, nStar );
	SET_STAR_VISIBLE( 11, nStar );
	SET_STAR_VISIBLE( 12, nStar );
	SET_STAR_VISIBLE( 13, nStar );
	SET_STAR_VISIBLE( 14, nStar );
	SET_STAR_VISIBLE( 15, nStar );
	SET_STAR_VISIBLE( 16, nStar );
	SET_STAR_VISIBLE( 17, nStar );
	SET_STAR_VISIBLE( 18, nStar );
}

void CUI_ID_FRAME_Star::ShowNextStar( int nStar  ,int nLevel)
{
	if( !m_pID_FRAME_EquipEvolve )
		return;

	int nMaxLevel = 18;

	nStar = min( nMaxLevel, nStar );
	m_NextStarGroup.SetVisible( false );
	//for (int i=0;i<=nMaxLevel;i++)
	//{
	//	SET_NEXTSTAR_VISIBLE( i, nStar );
	//}
	SET_NEXTSTAR_VISIBLE( 0, nStar );
	SET_NEXTSTAR_VISIBLE( 1, nStar );
	SET_NEXTSTAR_VISIBLE( 2, nStar );
	SET_NEXTSTAR_VISIBLE( 3, nStar );
	SET_NEXTSTAR_VISIBLE( 4, nStar );
	SET_NEXTSTAR_VISIBLE( 5, nStar );
	SET_NEXTSTAR_VISIBLE( 6, nStar );
	SET_NEXTSTAR_VISIBLE( 7, nStar );
	SET_NEXTSTAR_VISIBLE( 8, nStar );
	SET_NEXTSTAR_VISIBLE( 9, nStar );
	SET_NEXTSTAR_VISIBLE( 10, nStar );
	SET_NEXTSTAR_VISIBLE( 11, nStar );
	SET_NEXTSTAR_VISIBLE( 12, nStar );
	SET_NEXTSTAR_VISIBLE( 13, nStar );
	SET_NEXTSTAR_VISIBLE( 14, nStar );
	SET_NEXTSTAR_VISIBLE( 15, nStar );
	SET_NEXTSTAR_VISIBLE( 16, nStar );
	SET_NEXTSTAR_VISIBLE( 17, nStar );
	SET_NEXTSTAR_VISIBLE( 18, nStar );
}


bool CUI_ID_FRAME_Star::ID_BUTTON_AutoUpOnButtonClick( ControlObject* pSender )
{
	SetAutoLevelUp(true);
	ProcessAutoLevelUp();
	return true;

}

void CUI_ID_FRAME_Star::_SetVisable(const bool bVisable)
{
	if (bVisable)
	{
		OnDirty();
	}
	OnSetVisable(bVisable);
	m_pID_CHECKBOX_AutoUp->SetCheck(false);
	m_pID_COMBOBOX_AutoUp->SetVisable(false);
	m_pID_BUTTON_AutoUp->SetVisable(false);
	m_pID_BUTTON_Ok->SetVisable(true);
	m_pID_BUTTON_Ok->SetEnable(false);

	m_pID_CHECKBOX_X1->SetCheck(true);
	m_pID_CHECKBOX_X2->SetCheck(false);
	m_pID_CHECKBOX_X3->SetCheck(false);
	m_pID_CHECKBOX_X4->SetCheck(false);
	m_pID_CHECKBOX_X1->SetEnable(true);
	m_pID_CHECKBOX_X2->SetEnable(true);
	m_pID_CHECKBOX_X3->SetEnable(true);
	m_pID_CHECKBOX_X4->SetEnable(true);
	m_stMaterialUseNum = 1;

	m_pID_CHECKBOX_Protect_NoUse->SetCheck(false);
	m_pID_CHECKBOX_Protect_SixStar->SetCheck(false);
	m_pID_CHECKBOX_Protect_NineStar->SetCheck(false);
	m_pID_CHECKBOX_Protect_TwelStar->SetCheck(false);
	m_pID_CHECKBOX_Protect_FiftStar->SetCheck(false);
	m_pID_CHECKBOX_Protect_NoUse->SetEnable(true);
	m_pID_CHECKBOX_Protect_SixStar->SetEnable(true);
	m_pID_CHECKBOX_Protect_NineStar->SetEnable(true);
	m_pID_CHECKBOX_Protect_TwelStar->SetEnable(true);
	m_pID_CHECKBOX_Protect_FiftStar->SetEnable(true);
	m_unProtectStarNum = 0;

	m_pID_TEXT_T3->SetVisable(false);
	m_pID_TEXT_T4->SetVisable(false);
	m_pID_TEXT_MaterialName->SetText("");
	m_pID_TEXT_EquipName->SetText("");
	m_pID_TEXT_PeotectName->SetText("");
}

void CUI_ID_FRAME_Star::ID_COMBOBOX_AutoUpOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if (!szData)
	{
		return ;
	}
	char cTmp[256];
	ControlList::S_List listItem;
	for (int i = 1; i <= 18; ++i)
	{
		listItem.clear();
		sprintf_s(cTmp,256,theXmlString.GetString(eText_Star_Star),i);
		if (strcmp(cTmp,szData) == 0)
		{
			m_nMaxAutoLevelUp = i;
			break;
		}
	}

}

bool CUI_ID_FRAME_Star::ID_BUTTON_StopOnButtonClick( ControlObject* pSender )
{
	SetAutoLevelUp(false);
	return true;
}



int CUI_ID_FRAME_Star::GetEvolveMoneyCost(  )
{
	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	if(!pImg)
		return -1;

	if(pImg->IsNull())
		return -1;

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pImg->m_pkIconInfo->GetItemId() );
	if( !pItemCommon )
		return -1;

	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if( !pCanEquip )
		return -1;	

	StarLevelUpData* pData = theStarLevelUpConfig.GetStarLevelUpData( pCanEquip->stEquipLevelReq, ((SCharItem*)pImg->m_pkIconInfo->GetData())->equipdata.ucLevel );
	if( !pData )
		return -1;

	return pData->GetCostMoney();

}

float CUI_ID_FRAME_Star::GetEvolveProbability()
{
	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	if(!pImg)
		return 0.0f;

	if(pImg->IsNull())
		return 0.0f;

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pImg->m_pkIconInfo->GetItemId() );
	if( !pItemCommon )
		return 0.0f;

	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if( !pCanEquip )
		return 0.0f;	

	StarLevelUpData* pData = theStarLevelUpConfig.GetStarLevelUpData( pCanEquip->stEquipLevelReq, ((SCharItem*)pImg->m_pkIconInfo->GetData())->equipdata.ucLevel );
	if( !pData )
		return 0.0f;

	return pData->GetProbability();
}

void CUI_ID_FRAME_Star::TipVisible( bool IsMaterialExist )
{
	if (IsMaterialExist)
	{
		m_pID_TEXT_Tip1->SetVisable(false);
		//m_pID_TEXT_Tip2->SetVisable(true);
	}
	else
	{
		m_pID_TEXT_Tip1->SetVisable(true);
		//m_pID_TEXT_Tip2->SetVisable(false);
		m_pID_BUTTON_Ok->SetEnable(false);
	}

}


bool CUI_ID_FRAME_Star::IsEvolveAllDone(ControlIconDrag::S_ListImg * pImg)
{
	SCharItem* psItem = (SCharItem*)pImg->m_pkIconInfo->GetData();
	return IsStarAllDone(psItem);
}

bool CUI_ID_FRAME_Star::ProcessAllDone( ControlIconDrag::S_ListImg * pImg )
{
	bool bRet = EquipEvolveUI::ProcessAllDone(pImg);
	m_pID_LISTIMG_Target->SetVisable(!bRet);
	m_pID_LIST_TargetProperty->SetVisable(!bRet);
	m_pID_TEXT_Equip2->SetVisable(!bRet);
	if (bRet)
	{
		m_pID_TEXT_Tip1->SetVisable(false);
		m_pID_TEXT_Tip2->SetText("");
		m_NextStarGroup.SetVisible(false);
	}
	return bRet;
}

void CUI_ID_FRAME_Star::ProcessAutoLevelUp()
{
	if (!m_bAutoLevelUp)
	{
		return;
	}
	OnDirty();
	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	if(!pImg || pImg->IsNull())
		return ;
	SCharItem* psItem = (SCharItem*)pImg->m_pkIconInfo->GetData();
	if (!psItem)
	{
		SetAutoLevelUp(false);
		return ;
	}
	if (psItem->equipdata.ucLevel >= m_nMaxAutoLevelUp)
	{
		char cTemp[1024] = {0};
		sprintf_s(cTemp,1024,theXmlString.GetString(eWarning_AutoStar_Ok),m_nMaxAutoLevelUp);
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, cTemp );
		SetAutoLevelUp(false);
		return ;
	}
	if (m_nSelectMaterialIndex == -1)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseStar_Failed, theXmlString.GetString(eWarning_AutoStar_LackMaterial) );
		SetAutoLevelUp(false);
		return ;
	}
	int nNeedMoney = GetEvolveMoneyCost();

	if(!thePlayerRole.HaveEnoughMoney(nNeedMoney))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseStar_Failed, theXmlString.GetString(eWarning_AutoStar_LackMoney) );
		SetAutoLevelUp(false);
		return ;
	}
	ControlIconDrag::S_ListImg* pItemImg = m_pID_LISTIMG_Material->GetItemByIndex( m_nSelectMaterialIndex );
	if (pItemImg && pItemImg->m_pkIconInfo->Count() < m_stMaterialUseNum)
	{
		SetAutoLevelUp(false);
		return ;
	}
	if (HQ_TimeGetTime() - m_dwLastLevelUpTime > gCfg.m_dwAutoStarLevelUpInterval)
	{
		m_dwLastLevelUpTime = HQ_TimeGetTime();
		OnOkClick();
	}
	else
	{
		m_bWaitNextAuto = true;
	}
	
}

void CUI_ID_FRAME_Star::SetAutoLevelUp( bool bFlag )
{
	m_bAutoLevelUp = bFlag;
	//m_pID_BUTTON_AutoUp->SetVisable(!bFlag);
	m_pID_BUTTON_AutoUp->SetEnable(!bFlag);
	m_pID_COMBOBOX_AutoUp->SetEnable(m_pID_BUTTON_AutoUp->IsEnable());
	m_pID_CHECKBOX_AutoUp->SetEnable(m_pID_BUTTON_AutoUp->IsEnable());
	m_pID_COMBOBOX_AutoUp->SetVisable(m_pID_BUTTON_AutoUp->IsVisable());
	m_pID_BUTTON_Stop->SetVisable(bFlag);
}

void CUI_ID_FRAME_Star::RefreshOkButton()
{
	EquipEvolveUI::RefreshOkButton();
	{
		m_pID_BUTTON_AutoUp->SetVisable(!m_pID_BUTTON_Ok->IsVisable());
		m_pID_BUTTON_AutoUp->SetEnable(!m_bAutoLevelUp && m_pID_BUTTON_Ok->IsEnable());
		m_pID_COMBOBOX_AutoUp->SetVisable(m_pID_BUTTON_AutoUp->IsVisable());
		m_pID_COMBOBOX_AutoUp->SetEnable(m_pID_BUTTON_AutoUp->IsEnable());
	}
}

bool CUI_ID_FRAME_Star::IsStarAllDone( SCharItem* psItem )
{
	if (!psItem)
	{
		return true;
	}

	ItemDefine::SItemCommon *pCommon = GettheItemDetail().GetItemByID(psItem->itembaseinfo.ustItemID);
	if(!pCommon)
		return true;

	if(pCommon->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR)
		return true;

	ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)pCommon;
	StarLevelUpData* pLevelUpData = theStarLevelUpConfig.GetStarLevelUpData( pItemCanEquip->stEquipLevelReq, psItem->equipdata.ucLevel );
	if(pLevelUpData)
		return false;

	return true;
//	return psItem->equipdata.ucLevel >= 10;
// 	if (psItem->equipdata.quality < ItemDefine::EQL_Purple)
// 	{
// 		return psItem->equipdata.ucLevel >= 9;
// 	}
// 	else
// 	{
// 		return psItem->equipdata.ucLevel >= 10;
// 	}
}

bool CUI_ID_FRAME_Star::IsPackItemBeUsing( __int64 nGuid )
{
    if( EquipEvolveUI::IsPackItemBeUsing( nGuid ) )
        return true;

    if( !IsVisable() || nGuid <= 0 )
        return false;

    if( m_n64RateMaterialGuid == nGuid || m_n64ProtectMaterialGuid == nGuid )
    {
        return true;
    }
    return false;
}

void CUI_ID_FRAME_Star::SetEquipInfoVisable(bool bVisable)
{
	if(!m_pID_FRAME_EquipEvolve)
		return;

	m_pID_LIST_ArmourProperty->SetVisable( bVisable );
	m_pID_LIST_TargetProperty->SetVisable( bVisable );
	m_pID_TEXT_Equip1->SetVisable(bVisable);
	m_pID_TEXT_Equip2->SetVisable(bVisable);
	m_StarGroup.SetVisible(bVisable);
	m_NextStarGroup.SetVisible(bVisable);
	m_pID_TEXT_T4->SetVisable(bVisable);
}

void CUI_ID_FRAME_Star::AddShowString(ItemDefine::SItemCanEquip* pWeapon, SCharItem* pItem, ControlList* pList, bool bNextLevel ,bool bSoul )
{
	if (pWeapon == NULL || pItem == NULL || pList == NULL)
		return;
	char szBuf[256] = {0};
	ControlList::S_List sList;
	sList.clear();
	if(pWeapon->attackPhysics != 0)//物理攻击
	{
		int nAttStarVal = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->attackPhysics, pItem->equipdata.ucLevel + (int)bNextLevel );
		MeSprintf_s( szBuf, sizeof( szBuf ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eText_PlayAtt_Short ), nAttStarVal );
		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );
		sList.clear();
	}
	if (pWeapon->attackMagic != 0) //魔法攻击
	{
		int nAttStarVal = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->attackMagic, pItem->equipdata.ucLevel + (int)bNextLevel );
		MeSprintf_s( szBuf, sizeof( szBuf ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddMagicAttack ), nAttStarVal );
		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );
		sList.clear();
	}
	/*
	if (pWeapon->attackSpeed != 0) //攻击速度
	{
		int nAttStarVal = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->attackSpeed, pItem->equipdata.ucLevel + (int)bNextLevel );
		MeSprintf_s( szBuf, sizeof( szBuf ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddMoveSpeed ), nAttStarVal );
		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );
		sList.clear();
	}
	*/
	if (pWeapon->exact  != 0)//命中率
	{
		int nAttStarVal = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->exact, pItem->equipdata.ucLevel + (int)bNextLevel );
		MeSprintf_s( szBuf, sizeof( szBuf ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddExact ), nAttStarVal );
		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );
		sList.clear();
	}
	if (pWeapon->dodge != 0) //闪避率
	{
		int nAttStarVal = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->dodge, pItem->equipdata.ucLevel + (int)bNextLevel );
		MeSprintf_s( szBuf, sizeof( szBuf ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddDodge ), nAttStarVal );
		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );
		sList.clear();
	}
	if (pWeapon->critical != 0) //暴击率
	{
		int nAttStarVal = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->critical, pItem->equipdata.ucLevel + (int)bNextLevel );
		MeSprintf_s( szBuf, sizeof( szBuf ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddCritical ), nAttStarVal );
		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );
		sList.clear();
	}
	if (pWeapon->tenacity != 0) //韧性
	{
		int nAttStarVal = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->tenacity, pItem->equipdata.ucLevel + (int)bNextLevel );
		MeSprintf_s( szBuf, sizeof( szBuf ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddTenacity ), nAttStarVal );
		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );
		sList.clear();
	}
#pragma message("增加下元素属性")
	if (pWeapon->breakStrike != 0) //破甲伤害
	{
		int nAttStarVal = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->breakStrike, pItem->equipdata.ucLevel + (int)bNextLevel );
		MeSprintf_s( szBuf, sizeof( szBuf ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddBreakStrike ), nAttStarVal );
		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );
		sList.clear();
	}
	if (pWeapon->breakResist != 0) //破甲抗性
	{
		int nAttStarVal = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->breakResist, pItem->equipdata.ucLevel + (int)bNextLevel );
		MeSprintf_s( szBuf, sizeof( szBuf ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddBreakResist ), nAttStarVal );
		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );
		sList.clear();
	}
	if (pWeapon->stabStrike != 0) //贯穿伤害
	{
		int nAttStarVal = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->stabStrike, pItem->equipdata.ucLevel + (int)bNextLevel );
		MeSprintf_s( szBuf, sizeof( szBuf ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddStabStrike ), nAttStarVal );
		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );
		sList.clear();
	}
	if (pWeapon->stabResist != 0) //贯穿抗性
	{
		int nAttStarVal = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->stabResist, pItem->equipdata.ucLevel + (int)bNextLevel );
		MeSprintf_s( szBuf, sizeof( szBuf ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddStabResist ), nAttStarVal );
		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );
		sList.clear();
	}
	if (pWeapon->elementStrike != 0) //元素伤害
	{
		int nAttStarVal = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->elementStrike, pItem->equipdata.ucLevel + (int)bNextLevel );
		MeSprintf_s( szBuf, sizeof( szBuf ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddElementStrike ), nAttStarVal );
		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );
		sList.clear();
	}
	if (pWeapon->elementResist != 0) //元素抗性
	{
		int nAttStarVal = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->elementResist, pItem->equipdata.ucLevel + (int)bNextLevel );
		MeSprintf_s( szBuf, sizeof( szBuf ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddElementResist ), nAttStarVal );
		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );
		sList.clear();
	}
	if (pWeapon->toxinStrike != 0) //毒素伤害
	{
		int nAttStarVal = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->toxinStrike, pItem->equipdata.ucLevel + (int)bNextLevel );
		MeSprintf_s( szBuf, sizeof( szBuf ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddToxinStrike ), nAttStarVal );
		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );
		sList.clear();
	}
	if (pWeapon->toxinResist != 0) //毒素抗性
	{
		int nAttStarVal = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->toxinResist, pItem->equipdata.ucLevel + (int)bNextLevel );
		MeSprintf_s( szBuf, sizeof( szBuf ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddToxinResist ), nAttStarVal );
		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );
		sList.clear();
	}
	if (pWeapon->spiritStrike != 0) //精神伤害
	{
		int nAttStarVal = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->spiritStrike, pItem->equipdata.ucLevel + (int)bNextLevel );
		MeSprintf_s( szBuf, sizeof( szBuf ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddSpiritStrike ), nAttStarVal );
		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );
		sList.clear();
	}
	if (pWeapon->spiritResist != 0) //精神抗性
	{
		int nAttStarVal = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->spiritResist, pItem->equipdata.ucLevel + (int)bNextLevel );
		MeSprintf_s( szBuf, sizeof( szBuf ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddSpiritResist ), nAttStarVal );
		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );
		sList.clear();
	}

}
// CheckBox
void CUI_ID_FRAME_Star::ID_CHECKBOX_X1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (m_pID_CHECKBOX_X2 && m_pID_CHECKBOX_X3 && m_pID_CHECKBOX_X4)
	{
		m_pID_CHECKBOX_X2->SetCheck(false);
		m_pID_CHECKBOX_X3->SetCheck(false);
		m_pID_CHECKBOX_X4->SetCheck(false);
	}

	//if (m_pID_CHECKBOX_X1->IsChecked())
	//	m_stMaterialUseNum = 1;
	//else
	//	//m_stMaterialUseNum = 0;
	//	return;
	m_pID_CHECKBOX_X1->SetCheck(true);
	m_stMaterialUseNum = 1;
	EquipEvolveUI::RefreshProbability();
	
}
// CheckBox
void CUI_ID_FRAME_Star::ID_CHECKBOX_X2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (m_pID_CHECKBOX_X1 && m_pID_CHECKBOX_X3 && m_pID_CHECKBOX_X4)
	{
		m_pID_CHECKBOX_X1->SetCheck(false);
		m_pID_CHECKBOX_X3->SetCheck(false);
		m_pID_CHECKBOX_X4->SetCheck(false);
	}

	//if (m_pID_CHECKBOX_X2->IsChecked())
	//	m_stMaterialUseNum = 2;
	//else
	//	//m_stMaterialUseNum = 0;
	//	return;
	m_pID_CHECKBOX_X2->SetCheck(true);
	m_stMaterialUseNum = 2;
	EquipEvolveUI::RefreshProbability();
}
// CheckBox
void CUI_ID_FRAME_Star::ID_CHECKBOX_X3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (m_pID_CHECKBOX_X2 && m_pID_CHECKBOX_X1 && m_pID_CHECKBOX_X4)
	{
		m_pID_CHECKBOX_X2->SetCheck(false);
		m_pID_CHECKBOX_X1->SetCheck(false);
		m_pID_CHECKBOX_X4->SetCheck(false);
	}

	//if (m_pID_CHECKBOX_X3->IsChecked())
	//	m_stMaterialUseNum = 3;
	//else
	//	//m_stMaterialUseNum = 0;
	//	return;
	m_pID_CHECKBOX_X3->SetCheck(true);
	m_stMaterialUseNum = 3;
	EquipEvolveUI::RefreshProbability();
}
// CheckBox
void CUI_ID_FRAME_Star::ID_CHECKBOX_X4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (m_pID_CHECKBOX_X2 && m_pID_CHECKBOX_X3 && m_pID_CHECKBOX_X1)
	{
		m_pID_CHECKBOX_X2->SetCheck(false);
		m_pID_CHECKBOX_X3->SetCheck(false);
		m_pID_CHECKBOX_X1->SetCheck(false);
	}

	//if (m_pID_CHECKBOX_X4->IsChecked())
	//	m_stMaterialUseNum = 4;
	//else
	//	//m_stMaterialUseNum = 0;
	//	return;
	m_pID_CHECKBOX_X4->SetCheck(true);
	m_stMaterialUseNum = 4;
	EquipEvolveUI::RefreshProbability();
}
// CheckBox
uint16 CUI_ID_FRAME_Star::GetProtectMatrialID(uint16 item_star)
{
	if (item_star >= 6 && item_star < 9)
	{
		m_unProtectStarNum = 6;
		return SID_ProtectStarSix;
	}
	else if (item_star >= 9 && item_star < 12)
	{
		m_unProtectStarNum = 9;
		return SID_ProtectStarNine;
	}
	else if (item_star >= 12 && item_star < 15)
	{
		m_unProtectStarNum = 12;
		return SID_ProtectStarTwelve;
	}
	else if (item_star >= 15)
	{
		m_unProtectStarNum = 15;
		return SID_ProtectStarFifteen;
	}
	else
		return 0xffff;
}
void CUI_ID_FRAME_Star::ShowProtectStarIcon()
{
	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	if(!pImg)
	{
		m_pID_CHECKBOX_Protect_NoUse->SetCheck(false);
		m_unProtectStarNum = 0;
		m_IsProtectMaterialBound = false;
		return;
	}
	if(pImg->IsNull())
	{
		m_pID_CHECKBOX_Protect_NoUse->SetCheck(false);
		m_unProtectStarNum = 0;
		m_IsProtectMaterialBound = false;
		return;
	}

	SCharItem* pEquipItem = (SCharItem*)pImg->m_pkIconInfo->GetData();
	if (!pEquipItem)
	{
		m_pID_CHECKBOX_Protect_NoUse->SetCheck(false);
		m_unProtectStarNum = 0;
		m_IsProtectMaterialBound = false;
		return;
	}
	
	if (m_pID_CHECKBOX_Protect_NoUse->IsChecked())
	{
		m_pID_LISTIMG_Target->Clear();
		uint16 proMaterialID = GetProtectMatrialID(pEquipItem->equipdata.ucLevel);
		int nBagIndex = -1;
		ControlIconDrag::S_ListImg * pListImgItem = RetriveMaterialImg(proMaterialID,nBagIndex);
		ControlIconDrag::S_ListImg ImgItem;
		if (NULL == pListImgItem)
		{
			ImgItem.SetData(proMaterialID,1,eIcon_Disable);
			pListImgItem = &ImgItem;
			m_pID_LISTIMG_Target->SetItem( pListImgItem );
			ShowProtectStarName(pListImgItem);
			m_unProtectStarNum = 0;
			m_IsProtectMaterialBound = false;

			s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_MountStrengthen_NoProtect));
		}
		else
		{
			m_pID_LISTIMG_Target->SetItem( pListImgItem );
			ShowProtectStarName(pListImgItem);

			SCharItem* pProtectItem = (SCharItem*)pListImgItem->m_pkIconInfo->GetData();
			if ( pProtectItem )
				m_IsProtectMaterialBound = pProtectItem->IsBounded();
		}
	}
	else
	{
		m_pID_LISTIMG_Target->Clear();
		m_unProtectStarNum = 0;
		m_pID_TEXT_PeotectName->SetText("");
		m_IsProtectMaterialBound = false;
	}
	
}

void CUI_ID_FRAME_Star::ID_CHECKBOX_Protect_NoUseOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	/*if (m_pID_CHECKBOX_Protect_SixStar && m_pID_CHECKBOX_Protect_NineStar && m_pID_CHECKBOX_Protect_TwelStar && m_pID_CHECKBOX_Protect_FiftStar)
	{
		m_pID_CHECKBOX_Protect_SixStar->SetCheck(false);
		m_pID_CHECKBOX_Protect_NineStar->SetCheck(false);
		m_pID_CHECKBOX_Protect_TwelStar->SetCheck(false);
		m_pID_CHECKBOX_Protect_FiftStar->SetCheck(false);
	}

	m_pID_CHECKBOX_Protect_NoUse->SetCheck(true);
	m_unProtectStarNum = 0;*/
	ShowProtectStarIcon();
}
// CheckBox
void CUI_ID_FRAME_Star::ID_CHECKBOX_Protect_SixStarOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (m_pID_CHECKBOX_Protect_NoUse && m_pID_CHECKBOX_Protect_NineStar && m_pID_CHECKBOX_Protect_TwelStar && m_pID_CHECKBOX_Protect_FiftStar)
	{
		m_pID_CHECKBOX_Protect_NoUse->SetCheck(false);
		m_pID_CHECKBOX_Protect_NineStar->SetCheck(false);
		m_pID_CHECKBOX_Protect_TwelStar->SetCheck(false);
		m_pID_CHECKBOX_Protect_FiftStar->SetCheck(false);
	}

	if (HasMaterialItem(SID_ProtectStarSix))
	{
		m_pID_CHECKBOX_Protect_SixStar->SetCheck(true);
		m_unProtectStarNum = 6;
	}
	else
	{
		m_pID_CHECKBOX_Protect_SixStar->SetCheck(false);
		m_pID_CHECKBOX_Protect_NoUse->SetCheck(true);
		m_unProtectStarNum = 0;
	}
}
// CheckBox
void CUI_ID_FRAME_Star::ID_CHECKBOX_Protect_NineStarOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (m_pID_CHECKBOX_Protect_SixStar && m_pID_CHECKBOX_Protect_NoUse && m_pID_CHECKBOX_Protect_TwelStar && m_pID_CHECKBOX_Protect_FiftStar)
	{
		m_pID_CHECKBOX_Protect_SixStar->SetCheck(false);
		m_pID_CHECKBOX_Protect_NoUse->SetCheck(false);
		m_pID_CHECKBOX_Protect_TwelStar->SetCheck(false);
		m_pID_CHECKBOX_Protect_FiftStar->SetCheck(false);
	}

	if (HasMaterialItem(SID_ProtectStarNine))
	{
		m_pID_CHECKBOX_Protect_NineStar->SetCheck(true);
		m_unProtectStarNum = 9;
	}
	else
	{
		m_pID_CHECKBOX_Protect_NineStar->SetCheck(false);
		m_pID_CHECKBOX_Protect_NoUse->SetCheck(true);
		m_unProtectStarNum = 0;
	}
}
// CheckBox
void CUI_ID_FRAME_Star::ID_CHECKBOX_Protect_TwelStarOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (m_pID_CHECKBOX_Protect_SixStar && m_pID_CHECKBOX_Protect_NineStar && m_pID_CHECKBOX_Protect_NoUse && m_pID_CHECKBOX_Protect_FiftStar)
	{
		m_pID_CHECKBOX_Protect_SixStar->SetCheck(false);
		m_pID_CHECKBOX_Protect_NineStar->SetCheck(false);
		m_pID_CHECKBOX_Protect_NoUse->SetCheck(false);
		m_pID_CHECKBOX_Protect_FiftStar->SetCheck(false);
	}

	if (HasMaterialItem(SID_ProtectStarTwelve))
	{
		m_pID_CHECKBOX_Protect_TwelStar->SetCheck(true);
		m_unProtectStarNum = 12;
	}
	else
	{
		m_pID_CHECKBOX_Protect_TwelStar->SetCheck(false);
		m_pID_CHECKBOX_Protect_NoUse->SetCheck(true);
		m_unProtectStarNum = 0;
	}
}
// CheckBox
void CUI_ID_FRAME_Star::ID_CHECKBOX_Protect_FiftStarOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (m_pID_CHECKBOX_Protect_SixStar && m_pID_CHECKBOX_Protect_NineStar && m_pID_CHECKBOX_Protect_TwelStar && m_pID_CHECKBOX_Protect_NoUse)
	{
		m_pID_CHECKBOX_Protect_SixStar->SetCheck(false);
		m_pID_CHECKBOX_Protect_NineStar->SetCheck(false);
		m_pID_CHECKBOX_Protect_TwelStar->SetCheck(false);
		m_pID_CHECKBOX_Protect_NoUse->SetCheck(false);
	}

	if (HasMaterialItem(SID_ProtectStarFifteen))
	{
		m_pID_CHECKBOX_Protect_FiftStar->SetCheck(true);
		m_unProtectStarNum = 15;
	}
	else
	{
		m_pID_CHECKBOX_Protect_FiftStar->SetCheck(false);
		m_pID_CHECKBOX_Protect_NoUse->SetCheck(true);
		m_unProtectStarNum = 0;
	}
}
// CheckBox
void CUI_ID_FRAME_Star::ID_CHECKBOX_Never_PromptOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
}
