/********************************************************************
Created by UIEditor.exe
FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\Soul.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Soul.h"
#include "Pack.h"
#include "NetworkInput.h"
#include "PlayerRole.h"
#include "Core/Name.h"
#include "XmlStringLanguage.h"
#include "color_config.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "UIBase.h"
#include "MeUI/ExpressionManager.h"
#include "ScreenInfoManager.h"
#include "IconManagerClient.h"
#include "GlobalDef.h"
#include "Common.h"
#include "Cfg.h"
#include "PackItemEnableManager.h"

CUI_ID_FRAME_Soul s_CUI_ID_FRAME_Soul;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Soul, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Soul, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Soul, ID_BUTTON_CLOSEOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Soul, ID_LIST_ArmourPropertyOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Soul, ID_LIST_TargetPropertyOnListSelectChange )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Soul, ID_LISTIMG_TargetOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Soul, ID_LISTIMG_TargetOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Soul, ID_LISTIMG_TargetOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Soul, ID_LISTIMG_TargetOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Soul, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Soul, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Soul, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Soul, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Soul, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Soul, ID_BUTTON_OkOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Soul, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Soul, ID_LISTIMG_ArmourOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Soul, ID_LISTIMG_ArmourOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Soul, ID_LISTIMG_ArmourOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Soul, ID_LISTIMG_Material1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Soul, ID_LISTIMG_Material1OnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Soul, ID_LISTIMG_Material1OnIconRButtonUp )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Soul, ID_LISTIMG_Material1OnIconButtonClick )

CUI_ID_FRAME_Soul::CUI_ID_FRAME_Soul()
{
	ResetUIObjects();
	m_bStartAnim = false;

}
void CUI_ID_FRAME_Soul::SetAtomVisible( bool bVisible )
{
	if( !m_pID_FRAME_EquipEvolve )
		return;
	EquipEvolveUI::SetAtomVisible(bVisible);
	m_pID_LISTIMG_Target->SetVisable( bVisible );
	m_pID_LIST_ArmourProperty->SetVisable( bVisible );
	m_pID_LIST_TargetProperty->SetVisable( bVisible );
}

// Frame
bool CUI_ID_FRAME_Soul::OnFrameRun()
{
	if (!OnDirty())
	{
		return true;
	}
	return true;
}
bool CUI_ID_FRAME_Soul::OnFrameRender()
{
	OnRender();
	return true;
}
// Button
bool CUI_ID_FRAME_Soul::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	SetVisable( false );
	return true;
}
// List
void CUI_ID_FRAME_Soul::ID_LIST_ArmourPropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_Soul::ID_LIST_TargetPropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// ListImg / ListEx
bool CUI_ID_FRAME_Soul::ID_LISTIMG_TargetOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_Soul::ID_LISTIMG_TargetOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Soul::ID_LISTIMG_TargetOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Soul::ID_LISTIMG_TargetOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Soul::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														ControlIconDrag::S_ListImg* pItemDrag,
														ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!pSender || !pItemDrag)
		return false;
	// 包裹里
	if( !s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) )
		return false;

	ItemDefine::SItemCommon* pItemCommon = ( ItemDefine::SItemCommon* )GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
	if (!pItemCommon)
		return false;

	if ( pItemDrag->m_pkIconInfo->GetItemId() != m_sMaterial[0].nId || pItemDrag->m_pkIconInfo->Count() < m_sMaterial[0].nCount )
		return false;

	m_sMaterial[0].nIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_MaterialBag, pItemDrag );
	UpdateGem();

	return false;
}
bool CUI_ID_FRAME_Soul::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Soul::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Soul::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( m_sMaterial[0].nIndex == -1 )
		return false;

	m_sMaterial[0].nIndex = -1;
	UpdateGem();

	return false;
}
// Button
bool CUI_ID_FRAME_Soul::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	SetVisable( false );
	return true;
}
// Button
bool CUI_ID_FRAME_Soul::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_EquipEvolve)
		return false;
	// 播放序列帧动画
	//OnOkClick();
	SendEvolveMsg();
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Soul::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pObject,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_EquipEvolve )
		return false;
	if( !pItemDrag )
		return false;

	SCharItem* psItem = (SCharItem*)pItemDrag->m_pkIconInfo->GetData();
	if (!psItem)
	{
		return false;
	}
	/*if (psItem->IsSoulStamp())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Soul_Failed, theXmlString.GetString(eWarning_Cannot_Soul_Repeat) );
		return false;
	}*/
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (!pMe)
	{
		return false;
	}
	if (pMe->GetLevel() < gCfg.m_nMinSoulPlayerLevel)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Soul_Failed, theXmlString.GetString(eWarning_Cannot_Soul_PlayerLowTo45) );
		return false;
	}
	int nLevel = GetItemLevel(pItemDrag->m_pkIconInfo->GetItemId());
	if(nLevel < gCfg.m_nMinSoulItemLevel)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Soul_Failed, theXmlString.GetString(eWarning_Cannot_Soul_ItemLowTo40) );
		return false;
	}

	if ( !theSoulConfig.GetLevelData( nLevel ) )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Soul_Failed, theXmlString.GetString(eText_Cannot_Soul_LevelError) );
		return false;
	}

	ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
	if(!pItemCommon)
		return false;

	//只有武器和防具可以铸魂
	if(pItemCommon->ucItemType != ItemDefine::ITEMTYPE_WEAPON &&pItemCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR)
	{
		CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Soul_Failed,theXmlString.GetString(eText_Info_SoulStamp));
		return false;
	}

	ItemDefine::SItemCanEquip* pItemCanEquip = static_cast<ItemDefine::SItemCanEquip*>(pItemCommon);
	if(pItemCanEquip->bFashion || pItemCanEquip->IsCannotEvolve())
	{
		CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Soul_Failed,theXmlString.GetString(eText_Info_SoulStamp));
		return false;
	}

	OnEquipDragOn(pItemDrag,pSender);

	return false;
}
bool CUI_ID_FRAME_Soul::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Soul::ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Soul::ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	ClearEquip();
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_Soul::ID_LISTIMG_Material1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														 ControlIconDrag::S_ListImg* pItemDrag,
														 ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!pSender || !pItemDrag)
		return false;
	// 包裹里
	if( !s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) )
		return false;

	ItemDefine::SItemCommon* pItemCommon = ( ItemDefine::SItemCommon* )GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
	if (!pItemCommon)
		return false;

	if ( pItemDrag->m_pkIconInfo->GetItemId() != m_sMaterial[1].nId || pItemDrag->m_pkIconInfo->Count() < m_sMaterial[1].nCount )
		return false;

	m_sMaterial[1].nIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_MaterialBag, pItemDrag );
	UpdateGem();

	return false;
}
bool CUI_ID_FRAME_Soul::ID_LISTIMG_Material1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Soul::ID_LISTIMG_Material1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( m_sMaterial[1].nIndex == -1 )
		return false;

	m_sMaterial[1].nIndex = -1;
	UpdateGem();

	return false;
}
bool CUI_ID_FRAME_Soul::ID_LISTIMG_Material1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}


// 装载UI
bool CUI_ID_FRAME_Soul::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Soul.MEUI" , false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Soul.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Soul::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Soul, s_CUI_ID_FRAME_SoulOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Soul, s_CUI_ID_FRAME_SoulOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Soul, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SoulID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Soul, ID_LIST_ArmourProperty, s_CUI_ID_FRAME_SoulID_LIST_ArmourPropertyOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Soul, ID_LIST_TargetProperty, s_CUI_ID_FRAME_SoulID_LIST_TargetPropertyOnListSelectChange );
	theUiManager.OnIconDragOn( ID_FRAME_Soul, ID_LISTIMG_Target, s_CUI_ID_FRAME_SoulID_LISTIMG_TargetOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Soul, ID_LISTIMG_Target, s_CUI_ID_FRAME_SoulID_LISTIMG_TargetOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Soul, ID_LISTIMG_Target, s_CUI_ID_FRAME_SoulID_LISTIMG_TargetOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Soul, ID_LISTIMG_Target, s_CUI_ID_FRAME_SoulID_LISTIMG_TargetOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Soul, ID_LISTIMG_Material, s_CUI_ID_FRAME_SoulID_LISTIMG_MaterialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Soul, ID_LISTIMG_Material, s_CUI_ID_FRAME_SoulID_LISTIMG_MaterialOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Soul, ID_LISTIMG_Material, s_CUI_ID_FRAME_SoulID_LISTIMG_MaterialOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Soul, ID_LISTIMG_Material, s_CUI_ID_FRAME_SoulID_LISTIMG_MaterialOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_Soul, ID_BUTTON_Cancel, s_CUI_ID_FRAME_SoulID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Soul, ID_BUTTON_Ok, s_CUI_ID_FRAME_SoulID_BUTTON_OkOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Soul, ID_LISTIMG_Armour, s_CUI_ID_FRAME_SoulID_LISTIMG_ArmourOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Soul, ID_LISTIMG_Armour, s_CUI_ID_FRAME_SoulID_LISTIMG_ArmourOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Soul, ID_LISTIMG_Armour, s_CUI_ID_FRAME_SoulID_LISTIMG_ArmourOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Soul, ID_LISTIMG_Armour, s_CUI_ID_FRAME_SoulID_LISTIMG_ArmourOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Soul, ID_LISTIMG_Material1, s_CUI_ID_FRAME_SoulID_LISTIMG_Material1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Soul, ID_LISTIMG_Material1, s_CUI_ID_FRAME_SoulID_LISTIMG_Material1OnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Soul, ID_LISTIMG_Material1, s_CUI_ID_FRAME_SoulID_LISTIMG_Material1OnIconRButtonUp );
	theUiManager.OnIconButtonClick( ID_FRAME_Soul, ID_LISTIMG_Material1, s_CUI_ID_FRAME_SoulID_LISTIMG_Material1OnIconButtonClick );

	m_pID_FRAME_EquipEvolve = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Soul );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_Soul, ID_TEXT_Money );
	m_pID_LIST_ArmourProperty = (ControlList*)theUiManager.FindControl( ID_FRAME_Soul, ID_LIST_ArmourProperty );
	m_pID_LIST_TargetProperty = (ControlList*)theUiManager.FindControl( ID_FRAME_Soul, ID_LIST_TargetProperty );
	m_pID_LISTIMG_Target = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Soul, ID_LISTIMG_Target );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Soul, ID_LISTIMG_Material );
	m_pID_TEXT_Equip1 = (ControlText*)theUiManager.FindControl( ID_FRAME_Soul, ID_TEXT_Equip1 );
	m_pID_TEXT_Equip2 = (ControlText*)theUiManager.FindControl( ID_FRAME_Soul, ID_TEXT_Equip2 );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_Soul, ID_BUTTON_Cancel );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_Soul, ID_BUTTON_Ok );
	m_pID_TEXT_Tip = (ControlText*)theUiManager.FindControl( ID_FRAME_Soul, ID_TEXT_Tip );
	m_pID_PICTURE_Begin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Soul, ID_PICTURE_Begin );
	m_pID_LISTIMG_Equip = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Soul, ID_LISTIMG_Armour );
	m_pID_PICTURE_StarEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Soul, ID_PICTURE_StarEffect );
	m_pID_TEXT_TipAllDone = (ControlText*)theUiManager.FindControl( ID_FRAME_Soul, ID_TEXT_TipAllDone );
	m_pID_LISTIMG_Material1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Soul, ID_LISTIMG_Material1 );

	assert( m_pID_FRAME_EquipEvolve );
	assert( m_pID_TEXT_Money );
	assert( m_pID_LIST_ArmourProperty );
	assert( m_pID_LIST_TargetProperty );
	assert( m_pID_LISTIMG_Target );
	assert( m_pID_LISTIMG_Material );
	assert( m_pID_TEXT_Equip1 );
	assert( m_pID_TEXT_Equip2 );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_TEXT_Tip );
	assert( m_pID_PICTURE_Begin );
	assert( m_pID_LISTIMG_Equip );
	assert( m_pID_LISTIMG_Material1 );

	m_pID_LIST_ArmourProperty->HaveSelBar( 0, 0 );	
	m_pID_LIST_TargetProperty->HaveSelBar( 0, 0 );
	m_pID_FRAME_EquipEvolve->SetOnVisibleChangedFun( OnVisibleChange );

	m_pID_LISTIMG_Target->SetEnableDrag( false );

	m_pID_TEXT_Tip->SetVisable(false);

	EquipEvolveIntialize();

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Soul::_UnLoadUI()
{
	ResetEquipEvolve();
	return theUiManager.RemoveFrame( "Data\\UI\\Soul.MEUI" );
}


void CUI_ID_FRAME_Soul::ClearEquip()
{
	if( !m_pID_FRAME_EquipEvolve )
		return;
	EquipEvolveUI::ClearEquip();
	m_pID_LISTIMG_Target->Clear();

	if(m_pID_TEXT_Equip1)
		m_pID_TEXT_Equip1->SetText("");
	if(m_pID_TEXT_Equip2)
		m_pID_TEXT_Equip2->SetText("");
	if(m_pID_TEXT_Tip)
		m_pID_TEXT_Tip->SetVisable(false);

	if( m_pID_LIST_ArmourProperty )
		m_pID_LIST_ArmourProperty->Clear();

	m_pID_LISTIMG_Material1->Clear();

	for (int i = 0; i < SoulConfig::ED_Max_Material; i++)
	{
		m_sMaterial[i].nCount = 0;
		m_sMaterial[i].nId = 0;
		m_sMaterial[i].nIndex = -1;
	}
}
void CUI_ID_FRAME_Soul::UpdateArmourInfo( SCharItem* pItem)
{
	if( !m_pID_FRAME_EquipEvolve )
		return;
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
	if( !pItemCommon )
		return;
	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if( !pCanEquip )
		return;

	bool bSouled = pItem->IsSoulStamp();
	// 名字
	Common::_tstring tstrName( pItemCommon->GetItemName() );
	S_IconInfoHero::ReplaceSpecifiedName( pItemCommon->ustLevel, tstrName );
	char szBuf[256] = {0};
	MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char)-1, "%s", tstrName.c_str() );
	m_pID_TEXT_Equip1->SetText(szBuf,S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel ));
	m_pID_TEXT_Equip2->Clear();
	if (!bSouled)
	{
		m_pID_TEXT_Equip2->SetText(szBuf,S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel ));
	}

	m_pID_LIST_ArmourProperty->Clear();
	m_pID_LIST_TargetProperty->Clear();
	//添加影响的属性
	//仅气血、法术、攻击(2)、防御(2)
	//这里逐一判断
	if( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON )
	{		
		/*AddAttackString(pCanEquip, pItem,  m_pID_LIST_ArmourProperty,false,bSouled);
		if (!bSouled)
		{
			AddAttackString(pCanEquip, pItem,  m_pID_LIST_TargetProperty,false,true);
		}*/
		if ( bSouled )
			ShowWeapon( pItemCommon, pItem );
	}
	else if( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
	{
		/*AddAttackString(pCanEquip, pItem,  m_pID_LIST_ArmourProperty,false,bSouled);
		if (!bSouled)
		{
			AddAttackString(pCanEquip, pItem,  m_pID_LIST_TargetProperty,false,true);
		}

		ItemDefine::SItemArmour* pArmour = (ItemDefine::SItemArmour*)pItemCommon;
		AddDefendString(pArmour, pItem,  m_pID_LIST_ArmourProperty,false,bSouled);
		if (!bSouled)
		{
			AddDefendString(pArmour, pItem,  m_pID_LIST_TargetProperty,false,true);
		}*/
		//AddHpMpString(pArmour, pItem,  m_pID_LIST_ArmourProperty,false,bSouled);
		if ( bSouled )
			ShowArmour( pItemCommon, pItem );
	}

}

void CUI_ID_FRAME_Soul::_RefreshEquipInfo( ControlIconDrag::S_ListImg* pListImg )
{
	if( !m_pID_FRAME_EquipEvolve )
		return;
	EquipEvolveUI::_RefreshEquipInfo(pListImg);
	m_pID_LISTIMG_Target->Clear();

	SCharItem* psItem = (SCharItem*)pListImg->m_pkIconInfo->GetData();
	if (!psItem)
	{
		return;
	}
	{
		ControlIconDrag::S_ListImg liTarget;
		liTarget.SetData( psItem );
		m_pID_LISTIMG_Target->SetItem( &liTarget, 0 );
		m_pID_LISTIMG_Target->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;				
	}
	UpdateArmourInfo( psItem);
}
void CUI_ID_FRAME_Soul::OnVisibleChange( ControlObject* pUIObject )
{
	s_CUI_ID_FRAME_Soul.SetDirty( true );
	s_CUI_ID_FRAME_Soul.ClearEquip();	
	s_CUI_ID_FRAME_Soul.RefreshAllBagEnable();
}

void CUI_ID_FRAME_Soul::ResetUIObjects()
{
	EquipEvolveUI::ResetUIObjects();
	// Member
	m_pID_LIST_ArmourProperty = NULL;
	m_pID_LIST_TargetProperty = NULL;
	m_pID_LISTIMG_Target = NULL;
	m_pID_TEXT_Equip1 = NULL;
	m_pID_TEXT_Equip2 = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_TEXT_Tip = NULL;
	m_pID_LISTIMG_Material1 = NULL;

}


void CUI_ID_FRAME_Soul::TipVisible( bool IsMaterialExist )
{
	if (IsMaterialExist)
	{
		m_pID_TEXT_Tip->SetVisable(false);
	}
	else
	{
		m_pID_TEXT_Tip->SetVisable(true);
	}

}


bool CUI_ID_FRAME_Soul::IsEvolveAllDone(ControlIconDrag::S_ListImg * pImg)
{
	SCharItem* psItem = (SCharItem*)pImg->m_pkIconInfo->GetData();
	if (!psItem)
	{
		return true;
	}
	return /*(psItem->IsSoulStamp())*/false;

}

bool CUI_ID_FRAME_Soul::ProcessAllDone( ControlIconDrag::S_ListImg * pImg )
{
	bool bRet = EquipEvolveUI::ProcessAllDone(pImg);
	m_pID_LISTIMG_Target->SetVisable(!bRet);
	if (bRet)
	{
		m_pID_TEXT_Tip->SetVisable(false);
	}
	return bRet;
}

void CUI_ID_FRAME_Soul::AddToList( std::string& strDes, float fValue )
{
	strDes += " ";
	char szTemp[128] = {0};
	MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_Tip_SoulStamp ), (int)fValue );
	strDes += szTemp;

	ControlList::S_List listItem;
	listItem.SetData(strDes.c_str());
	listItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_ArmourProperty->AddItem(&listItem);
}

void CUI_ID_FRAME_Soul::ShowWeapon( ItemDefine::SItemCommon* pItemCommon, SCharItem* pItem )
{
	ItemDefine::SItemWeapon* pWeapon = NULL;
	if( pItemCommon )
	{
		pWeapon = ( ItemDefine::SItemWeapon* )pItemCommon;
	}
	else
	{
		return;
	}
	if ( !pItem )
		return;

	if(pWeapon->attackPhysics != 0)
	{
		float fValue = pWeapon->attackPhysics * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eText_PlayAtt_Short );
		AddToList( strDescribe, fValue );
	}

	if(pWeapon->attackMagic != 0)
	{
		float fValue = pWeapon->attackMagic * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eText_PlayAtt_Magic );
		AddToList( strDescribe, fValue );
	}

	if(pWeapon->exact != 0)
	{
		float fValue = pWeapon->exact * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddExact );
		AddToList( strDescribe, fValue );
	}

	if(pWeapon->dodge != 0)
	{
		float fValue = pWeapon->dodge * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddDodge );
		AddToList( strDescribe, fValue );
	}

	if(pWeapon->critical != 0)
	{
		float fValue = pWeapon->critical * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddCritical );
		AddToList( strDescribe, fValue );
	}

	if(pWeapon->tenacity != 0)
	{
		float fValue = pWeapon->tenacity * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddTenacity );
		AddToList( strDescribe, fValue );
	}

	if(pWeapon->breakStrike != 0)
	{
		float fValue = pWeapon->breakStrike * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddBreakStrike );
		AddToList( strDescribe, fValue );
	}

	if(pWeapon->breakResist != 0)
	{
		float fValue = pWeapon->breakResist * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddBreakResist );
		AddToList( strDescribe, fValue );
	}

	if(pWeapon->stabStrike != 0)
	{
		float fValue = pWeapon->stabStrike * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddStabStrike );
		AddToList( strDescribe, fValue );
	}

	if(pWeapon->stabResist != 0)
	{
		float fValue = pWeapon->stabResist * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddStabResist );
		AddToList( strDescribe, fValue );
	}

	if(pWeapon->elementStrike != 0)
	{
		float fValue = pWeapon->elementStrike * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddElementStrike );
		AddToList( strDescribe, fValue );
	}

	if(pWeapon->elementResist != 0)
	{
		float fValue = pWeapon->elementResist * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddElementResist );
		AddToList( strDescribe, fValue );
	}

	if(pWeapon->toxinStrike != 0)
	{
		float fValue = pWeapon->toxinStrike * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddToxinStrike );
		AddToList( strDescribe, fValue );
	}

	if(pWeapon->toxinResist != 0)
	{
		float fValue = pWeapon->toxinResist * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddToxinResist );
		AddToList( strDescribe, fValue );
	}

	if(pWeapon->spiritStrike != 0)
	{
		float fValue = pWeapon->spiritStrike * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddSpiritStrike );
		AddToList( strDescribe, fValue );
	}

	if(pWeapon->spiritResist != 0)
	{
		float fValue = pWeapon->spiritResist * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddSpiritResist );
		AddToList( strDescribe, fValue );
	}
}

void CUI_ID_FRAME_Soul::ShowArmour( ItemDefine::SItemCommon* pItemCommon, SCharItem* pItem )
{
	ItemDefine::SItemArmour* pArmour = NULL;

	if( pItemCommon )
	{
		pArmour = ( ItemDefine::SItemArmour* )pItemCommon;
	}
	else
	{
		return;
	}
	if ( !pItem )
		return;

	if(pArmour->attackPhysics != 0)
	{
		float fValue = pArmour->attackPhysics * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eText_PlayAtt_Short );
		AddToList( strDescribe, fValue );
	}

	if(pArmour->attackMagic != 0)
	{
		float fValue = pArmour->attackMagic * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eText_PlayAtt_Magic );
		AddToList( strDescribe, fValue );
	}

	if( pArmour->defendPhysics != 0 ) 
	{
		float fValue = pArmour->defendPhysics * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eText_PlayDef_Short );
		AddToList( strDescribe, fValue );
	}

	if( pArmour->defendMagic != 0 )
	{
		float fValue = pArmour->defendMagic * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eText_PlayDef_Magic );
		AddToList( strDescribe, fValue );
	}

	if( pArmour->Hp != 0 )
	{
		float fValue = pArmour->Hp * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddHPMax );
		AddToList( strDescribe, fValue );
	}

	if( pArmour->Mp != 0 )
	{
		float fValue = pArmour->Mp * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddMPMax );
		AddToList( strDescribe, fValue );
	}

	if(pArmour->exact != 0)
	{
		float fValue = pArmour->exact * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddExact );
		AddToList( strDescribe, fValue );
	}

	if(pArmour->dodge != 0)
	{
		float fValue = pArmour->dodge * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddDodge );
		AddToList( strDescribe, fValue );
	}

	if(pArmour->critical != 0)
	{
		float fValue = pArmour->critical * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddCritical );
		AddToList( strDescribe, fValue );
	}

	if(pArmour->tenacity != 0)
	{
		float fValue = pArmour->tenacity * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddTenacity );
		AddToList( strDescribe, fValue );
	}

	if(pArmour->breakStrike != 0)
	{
		float fValue = pArmour->breakStrike * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddBreakStrike );
		AddToList( strDescribe, fValue );
	}

	if(pArmour->breakResist != 0)
	{
		float fValue = pArmour->breakResist * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddBreakResist );
		AddToList( strDescribe, fValue );
	}

	if(pArmour->stabStrike != 0)
	{
		float fValue = pArmour->stabStrike * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddStabStrike );
		AddToList( strDescribe, fValue );
	}

	if(pArmour->stabResist != 0)
	{
		float fValue = pArmour->stabResist * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddStabResist );
		AddToList( strDescribe, fValue );
	}

	if(pArmour->elementStrike != 0)
	{
		float fValue = pArmour->elementStrike * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddElementStrike );
		AddToList( strDescribe, fValue );
	}

	if(pArmour->elementResist != 0)
	{
		float fValue = pArmour->elementResist * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddElementResist );
		AddToList( strDescribe, fValue );
	}

	if(pArmour->toxinStrike != 0)
	{
		float fValue = pArmour->toxinStrike * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddToxinStrike );
		AddToList( strDescribe, fValue );
	}

	if(pArmour->toxinResist != 0)
	{
		float fValue = pArmour->toxinResist * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddToxinResist );
		AddToList( strDescribe, fValue );
	}

	if(pArmour->spiritStrike != 0)
	{
		float fValue = pArmour->spiritStrike * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddSpiritStrike );
		AddToList( strDescribe, fValue );
	}

	if(pArmour->spiritResist != 0)
	{
		float fValue = pArmour->spiritResist * pItem->equipdata.ucSoulPer / 100.0f;
		std::string strDescribe = theXmlString.GetString( eTip_sAddSpiritResist );
		AddToList( strDescribe, fValue );
	}
}

bool CUI_ID_FRAME_Soul::UpdateGem()
{
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
	m_pID_LISTIMG_Material1->Clear();

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

	SoulConfig::SData* pData = theSoulConfig.GetLevelData( pCanEquip->stEquipLevelReq );
	if ( !pData )
		return false;

	bool bHasMaterial = true;

	int nCount = 0;
	if ( nCount < SoulConfig::ED_Max_Material )
	{
		if ( pData->material[nCount].nId > 0 && pData->material[nCount].nNum > 0 )
		{
			if ( m_sMaterial[nCount].nId <= 0 )
			{
				m_sMaterial[nCount].nId = pData->material[nCount].nId;
				m_sMaterial[nCount].nCount = pData->material[nCount].nNum;
			}

			ControlIconDrag::S_ListImg * pListImgItem = NULL/*RetriveMaterialImg(pData->material[nCount].nId,nBagIndex)*/;
			ControlIconDrag::S_ListImg ImgItem;

			if ( m_sMaterial[nCount].nIndex == -1 )
			{
				ImgItem.SetData(pData->material[nCount].nId,pData->material[nCount].nNum,eIcon_Disable);
				pListImgItem = &ImgItem;
				m_pID_LISTIMG_Material->SetItem( pListImgItem );
				bHasMaterial = false;
			}
			else
			{
				pListImgItem = s_CUI_ID_FRAME_PACK.GetItemByIndex( BT_MaterialBag, m_sMaterial[nCount].nIndex );

				if ( pListImgItem == NULL || pListImgItem->m_pkIconInfo->Count() < pData->material[nCount].nNum )
				{
					ImgItem.SetData(pData->material[nCount].nId,pData->material[nCount].nNum,eIcon_Disable);
					pListImgItem = &ImgItem;
					m_pID_LISTIMG_Material->SetItem( pListImgItem );
					bHasMaterial = false;
					m_sMaterial[nCount].nIndex = -1;
				}
				else
				{
					m_stMaterialIndex[nCount] = m_sMaterial[nCount].nIndex;
					m_n64MaterialGuid[nCount] = pListImgItem->m_pkIconInfo->GetOnlyId();
					m_shMaterialBagType[nCount] = BT_MaterialBag;
					m_bMaterialBagEnable[nCount] = false;
					pListImgItem->m_eEnable = eIcon_Enable;
					m_pID_LISTIMG_Material->SetItem( pListImgItem );
				}
			}
		}

		nCount++;
	}

	if ( nCount < SoulConfig::ED_Max_Material )
	{
		if ( pData->material[nCount].nId > 0 && pData->material[nCount].nNum > 0 )
		{
			if ( m_sMaterial[nCount].nId <= 0 )
			{
				m_sMaterial[nCount].nId = pData->material[nCount].nId;
				m_sMaterial[nCount].nCount = pData->material[nCount].nNum;
			}

			ControlIconDrag::S_ListImg * pListImgItem = NULL/*RetriveMaterialImg(pData->material[nCount].nId,nBagIndex)*/;
			ControlIconDrag::S_ListImg ImgItem;

			if ( m_sMaterial[nCount].nIndex == -1 )
			{
				ImgItem.SetData(pData->material[nCount].nId,pData->material[nCount].nNum,eIcon_Disable);
				pListImgItem = &ImgItem;
				m_pID_LISTIMG_Material1->SetItem( pListImgItem );
				bHasMaterial = false;
				m_sMaterial[nCount].nIndex = -1;
			}
			else
			{
				pListImgItem = s_CUI_ID_FRAME_PACK.GetItemByIndex( BT_MaterialBag, m_sMaterial[nCount].nIndex );

				if ( pListImgItem == NULL || pListImgItem->m_pkIconInfo->Count() < pData->material[nCount].nNum )
				{
					ImgItem.SetData(pData->material[nCount].nId,pData->material[nCount].nNum,eIcon_Disable);
					pListImgItem = &ImgItem;
					m_pID_LISTIMG_Material1->SetItem( pListImgItem );
					bHasMaterial = false;
				}
				else
				{
					m_stMaterialIndex[nCount] = m_sMaterial[nCount].nIndex;
					m_n64MaterialGuid[nCount] = pListImgItem->m_pkIconInfo->GetOnlyId();
					m_shMaterialBagType[nCount] = BT_MaterialBag;
					m_bMaterialBagEnable[nCount] = false;
					pListImgItem->m_eEnable = eIcon_Enable;
					m_pID_LISTIMG_Material1->SetItem( pListImgItem );
				}
			}
		}

		nCount++;
	}

	TipVisible( bHasMaterial );
	//RefreshAllBagEnable();
	RefreshNeedMoney();
	RefreshProbability();
	SetDirty( true );

	return true;
}

void CUI_ID_FRAME_Soul::RefreshNeedMoney()
{
	if (m_pID_TEXT_Money)
		m_pID_TEXT_Money->SetText("");

	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	if ( !pImg || pImg->IsNull() )
		return;

	int nLevel = GetItemLevel(pImg->m_pkIconInfo->GetItemId());

	SoulConfig::SData* pData = theSoulConfig.GetLevelData( nLevel );
	if ( !pData )
		return;

	int nMoney = pData->nMoney;
	if (nMoney <= 0)
	{
		if (m_pID_TEXT_Money)
		{
			m_pID_TEXT_Money->SetText("");
		}
		return;
	}
	std::string text = "";
	thePlayerRole.GetGSCStringFromJiaoZi(nMoney, text);
	DWORD dwColor = 0xffffffff;
	if(!thePlayerRole.HaveEnoughMoney(nMoney))
	{
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_StarLEvolveNoMomeny), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true);
		dwColor = 0xffff0000;
	}
	if (m_pID_TEXT_Money)
	{
		m_pID_TEXT_Money->SetText(text,dwColor);
	}	
}

void CUI_ID_FRAME_Soul::RefreshOkButton()
{
	if(!IsVisable())
		return;

	m_pID_BUTTON_Ok->SetEnable( false );

	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	if(!pImg || pImg->IsNull())
		return;
	
	if (ProcessAllDone(pImg))
		return;

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pImg->m_pkIconInfo->GetItemId() );
	if( !pItemCommon )
		return;
	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if( !pCanEquip )
		return;

	SoulConfig::SData* pData = theSoulConfig.GetLevelData( pCanEquip->stEquipLevelReq );
	if ( !pData )
		return;

	bool bHasMaterial = true;

	int nCount = 0;
	if ( nCount < SoulConfig::ED_Max_Material )
	{
		if ( pData->material[nCount].nId > 0 && pData->material[nCount].nNum > 0 )
		{
			ControlIconDrag::S_ListImg * pListImgItem = m_pID_LISTIMG_Material->GetItemByIndex(0);

			if (NULL == pListImgItem || pListImgItem->IsNull())
			{
				bHasMaterial = false;
			}
			else
			{
				if ( pListImgItem->m_eEnable == eIcon_Disable )
				{
					bHasMaterial = false;
				}
			}
		}

		nCount++;
	}

	if ( nCount < SoulConfig::ED_Max_Material )
	{
		if ( pData->material[nCount].nId > 0 && pData->material[nCount].nNum > 0 )
		{
			ControlIconDrag::S_ListImg * pListImgItem = m_pID_LISTIMG_Material1->GetItemByIndex(0);

			if (NULL == pListImgItem || pListImgItem->IsNull())
			{
				bHasMaterial = false;
			}
			else
			{
				if ( pListImgItem->m_eEnable == eIcon_Disable )
				{
					bHasMaterial = false;
				}
			}
		}

		nCount++;
	}

	if ( !bHasMaterial )
		return;

	int nMoney = pData->nMoney;
	if(!thePlayerRole.HaveEnoughMoney(nMoney))
		return;
	
	m_pID_BUTTON_Ok->SetEnable( true );
}

void CUI_ID_FRAME_Soul::SendEvolveMsg()
{
	MsgEquipEvolve msgEvolve;
	msgEvolve.nEvolveType = GetEvolveType();

	msgEvolve.nNormalBagIndex = m_stEquipBagIndex;
	msgEvolve.nNormalGuid      = m_stEquipBagGuid;

	msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType= m_shMaterialBagType[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex];
	msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex = m_stMaterialIndex[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex];
	msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid = m_n64MaterialGuid[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex];
	
	msgEvolve.materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagType= m_shMaterialBagType[MsgEquipEvolve::EConstDefine_SecondMaterialIndex];
	msgEvolve.materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex = m_stMaterialIndex[MsgEquipEvolve::EConstDefine_SecondMaterialIndex];
	msgEvolve.materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].guid = m_n64MaterialGuid[MsgEquipEvolve::EConstDefine_SecondMaterialIndex];

	msgEvolve.SendEquipMsg();
	//GettheNetworkInput().SendMsg( &msgEvolve );
}

void CUI_ID_FRAME_Soul::OnMaterialItemDrag( ControlObject* pSender, ControlIconDrag::S_ListImg* pItemDrag )
{
	if(!pSender || !pItemDrag)
		return;
	// 包裹里
	if( !s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) )
		return;

	ItemDefine::SItemCommon* pItemCommon = ( ItemDefine::SItemCommon* )GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
	if (!pItemCommon)
		return;

	if ( pItemDrag->m_pkIconInfo->GetItemId() == m_sMaterial[0].nId && pItemDrag->m_pkIconInfo->Count() >= m_sMaterial[0].nCount)
	{
		ID_LISTIMG_MaterialOnIconDragOn( pSender, NULL, pItemDrag, NULL );
	}

	if ( pItemDrag->m_pkIconInfo->GetItemId() == m_sMaterial[1].nId && pItemDrag->m_pkIconInfo->Count() >= m_sMaterial[1].nCount)
	{
		ID_LISTIMG_Material1OnIconDragOn( pSender, NULL, pItemDrag, NULL );
	}
}