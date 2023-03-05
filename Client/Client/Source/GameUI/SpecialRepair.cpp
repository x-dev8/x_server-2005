/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\SpecialRepair.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SpecialRepair.h"
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
#include "color_config.h"
#include "ScreenInfoManager.h"
#include "ChatInfoBox.h"
#include "EquipUIHelper.h"
#include "Progress.h"
#include "PackItemEnableManager.h"

CUI_ID_FRAME_SpecialRepair s_CUI_ID_FRAME_SpecialRepair;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SpecialRepair, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SpecialRepair, OnFrameRender )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SpecialRepair, ID_BUTTON_CLOSEOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SpecialRepair, ID_BUTTON_helpOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SpecialRepair, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SpecialRepair, ID_LISTIMG_ArmourOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SpecialRepair, ID_LISTIMG_ArmourOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SpecialRepair, ID_LISTIMG_ArmourOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SpecialRepair, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SpecialRepair, ID_BUTTON_CancelOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SpecialRepair, ID_LISTIMG_AimOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SpecialRepair, ID_LISTIMG_AimOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SpecialRepair, ID_LISTIMG_AimOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SpecialRepair, ID_LISTIMG_AimOnIconRButtonUp )
CUI_ID_FRAME_SpecialRepair::CUI_ID_FRAME_SpecialRepair()
{
	// Member
	ResetMembers();
	m_bStartAnim = false;
	m_bStartIntonate = false;
	m_dwStartIntonateTime = 0;
	m_nIntonateTime = 0;
}

void CUI_ID_FRAME_SpecialRepair::ResetMembers()
{
	m_pID_FRAME_SpecialRepair = NULL;
// 	m_pID_PICTURE_RightTitle = NULL;
// 	m_pID_PICTURE_MiddleTitle = NULL;
// 	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
// 	m_pID_PICTURE_ItemWall = NULL;
	m_pID_LISTIMG_Armour = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_UseMoneyZ = NULL;
	m_pID_TEXT_UseMoney = NULL;
// 	m_pID_PICTURE_LeftTitle = NULL;
// 	m_pID_PICTURE_TitleWord = NULL;
	m_pID_TEXT_Explain = NULL;
	//m_pID_PICTURE_ItemWall2 = NULL;
	m_pID_LISTIMG_Aim = NULL;
// 	m_pID_TEXT_ArmourName = NULL;
// 	m_pID_TEXT_AimName = NULL;
	m_pID_PICTURE_SpecialRepairEffect = NULL;

}
// Frame
bool CUI_ID_FRAME_SpecialRepair::OnFrameRun()
{
	if( IsVisable() )
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if ( pMe )
		{
			float fMeX,fMeY,fMeZ;			
			pMe->GetPos( &fMeX, &fMeY, &fMeZ );
			Vector v;
			float dist = pMe->GetDistToTarget( m_vVisiblePos.x, m_vVisiblePos.y );			
			if( dist > 12.0f )
			{
				SetVisable( false );
			}
		}

		// 走路或跳跃打断吟唱
		if( m_bStartIntonate )
		{
			CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
			if( pMe && (pMe->IsMoving() || pMe->IsJumping()) )
			{
				m_bStartIntonate = false;
				s_CUI_Progress.SetProgressComplete();
			}
		}
		// 吟唱结束
		if( m_bStartIntonate && m_dwStartIntonateTime + m_nIntonateTime < HQ_TimeGetTime() )
		{
			m_bStartIntonate = false;
			s_CUI_Progress.SetProgressComplete();

			// 请求特修
			m_slideAnim.StartAnimation(HQ_TimeGetTime());
			m_bStartAnim = true;

			MsgSpecialRepairItemReq req;
			req.stEquipIndex = m_equipBagIndex;
			req.nEquipGuid = m_equip.itembaseinfo.nOnlyInt;
			GettheNetworkInput().SendMsg( &req );
		}
	}

	if (!m_bNeedUpdate)
		return false;

	m_bNeedUpdate = false;

	RefreshBagIconEnable();
	return true;
}
bool CUI_ID_FRAME_SpecialRepair::OnFrameRender()
{
	if( !IsVisable() )
		return false;
 
	if( m_bStartAnim )
	{
		RECT rc;
		m_pID_PICTURE_SpecialRepairEffect->GetRealRect(&rc);
		m_slideAnim.Update(HQ_TimeGetTime(),&rc);
		if (!m_slideAnim.IsInAnimation())
		{
			m_bStartAnim = false;
			m_slideAnim.UnRelativePicResource();
		}
	}
	return true;
}
// Button
// bool CUI_ID_FRAME_SpecialRepair::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
// {
// 	if (!m_pID_FRAME_SpecialRepair)
// 		return false;
// 	return true;
// }
// // Button
// bool CUI_ID_FRAME_SpecialRepair::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	if (!m_pID_FRAME_SpecialRepair)
// 		return false;
// 	return true;
// }
// ListImg / ListEx
bool CUI_ID_FRAME_SpecialRepair::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															   ControlIconDrag::S_ListImg* pItemDrag,
															   ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SpecialRepair )
		return false;
	return SetEquip(pSender, pItemDrag);
}
bool CUI_ID_FRAME_SpecialRepair::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_SpecialRepair)
		return false;
	return false;
}
bool CUI_ID_FRAME_SpecialRepair::ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_SpecialRepair)
		return false;
	return false;
}
bool CUI_ID_FRAME_SpecialRepair::ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_SpecialRepair)
		return false;
	ClearEquip();
	return true;
}
// Button
bool CUI_ID_FRAME_SpecialRepair::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_SpecialRepair)
		return false;
	return RequestRepair();
}
// Button
bool CUI_ID_FRAME_SpecialRepair::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_SpecialRepair)
		return false;
	SetVisable(false);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SpecialRepair::ID_LISTIMG_AimOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															ControlIconDrag::S_ListImg* pItemDrag,
															ControlIconDrag::S_ListImg* pItemSrc )
{	
	if( !m_pID_FRAME_SpecialRepair )
		return false;
	return SetAim_(pSender, pItemDrag);
}
bool CUI_ID_FRAME_SpecialRepair::ID_LISTIMG_AimOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_SpecialRepair)
		return false;
	return false;
}
bool CUI_ID_FRAME_SpecialRepair::ID_LISTIMG_AimOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_SpecialRepair)
		return false;
	return false;
}
bool CUI_ID_FRAME_SpecialRepair::ID_LISTIMG_AimOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_SpecialRepair)
		return false;
	ClearAim();
	return true;
}

// 装载UI
bool CUI_ID_FRAME_SpecialRepair::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SpecialRepair.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SpecialRepair.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SpecialRepair::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SpecialRepair, s_CUI_ID_FRAME_SpecialRepairOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SpecialRepair, s_CUI_ID_FRAME_SpecialRepairOnFrameRender );
// 	theUiManager.OnButtonClick( ID_FRAME_SpecialRepair, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SpecialRepairID_BUTTON_CLOSEOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_SpecialRepair, ID_BUTTON_help, s_CUI_ID_FRAME_SpecialRepairID_BUTTON_helpOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SpecialRepair, ID_LISTIMG_Armour, s_CUI_ID_FRAME_SpecialRepairID_LISTIMG_ArmourOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SpecialRepair, ID_LISTIMG_Armour, s_CUI_ID_FRAME_SpecialRepairID_LISTIMG_ArmourOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SpecialRepair, ID_LISTIMG_Armour, s_CUI_ID_FRAME_SpecialRepairID_LISTIMG_ArmourOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SpecialRepair, ID_LISTIMG_Armour, s_CUI_ID_FRAME_SpecialRepairID_LISTIMG_ArmourOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_SpecialRepair, ID_BUTTON_Ok, s_CUI_ID_FRAME_SpecialRepairID_BUTTON_OkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SpecialRepair, ID_BUTTON_Cancel, s_CUI_ID_FRAME_SpecialRepairID_BUTTON_CancelOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SpecialRepair, ID_LISTIMG_Aim, s_CUI_ID_FRAME_SpecialRepairID_LISTIMG_AimOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SpecialRepair, ID_LISTIMG_Aim, s_CUI_ID_FRAME_SpecialRepairID_LISTIMG_AimOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SpecialRepair, ID_LISTIMG_Aim, s_CUI_ID_FRAME_SpecialRepairID_LISTIMG_AimOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SpecialRepair, ID_LISTIMG_Aim, s_CUI_ID_FRAME_SpecialRepairID_LISTIMG_AimOnIconRButtonUp );

	m_pID_FRAME_SpecialRepair = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SpecialRepair );
// 	m_pID_PICTURE_RightTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SpecialRepair, ID_PICTURE_RightTitle );
// 	m_pID_PICTURE_MiddleTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SpecialRepair, ID_PICTURE_MiddleTitle );
// 	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SpecialRepair, ID_BUTTON_CLOSE );
// 	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_SpecialRepair, ID_BUTTON_help );
// 	m_pID_PICTURE_ItemWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SpecialRepair, ID_PICTURE_ItemWall );
	m_pID_LISTIMG_Armour = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SpecialRepair, ID_LISTIMG_Armour );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_SpecialRepair, ID_BUTTON_Ok );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_SpecialRepair, ID_BUTTON_Cancel );
	m_pID_TEXT_UseMoneyZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SpecialRepair, ID_TEXT_UseMoneyZ );
	m_pID_TEXT_UseMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_SpecialRepair, ID_TEXT_UseMoney );
// 	m_pID_PICTURE_LeftTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SpecialRepair, ID_PICTURE_LeftTitle );
// 	m_pID_PICTURE_TitleWord = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SpecialRepair, ID_PICTURE_TitleWord );
	m_pID_TEXT_Explain = (ControlText*)theUiManager.FindControl( ID_FRAME_SpecialRepair, ID_TEXT_Explain );
	//m_pID_PICTURE_ItemWall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SpecialRepair, ID_PICTURE_ItemWall2 );
	m_pID_LISTIMG_Aim = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SpecialRepair, ID_LISTIMG_Aim );
// 	m_pID_TEXT_ArmourName = (ControlText*)theUiManager.FindControl( ID_FRAME_SpecialRepair, ID_TEXT_ArmourName );
// 	m_pID_TEXT_AimName = (ControlText*)theUiManager.FindControl( ID_FRAME_SpecialRepair, ID_TEXT_AimName );
	m_pID_PICTURE_SpecialRepairEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SpecialRepair, ID_PICTURE_SpecialRepairEffect );
// 	assert( m_pID_FRAME_SpecialRepair );
// 	assert( m_pID_PICTURE_RightTitle );
// 	assert( m_pID_PICTURE_MiddleTitle );
// 	assert( m_pID_BUTTON_CLOSE );
// 	assert( m_pID_BUTTON_help );
// 	assert( m_pID_PICTURE_ItemWall );
// 	assert( m_pID_LISTIMG_Armour );
// 	assert( m_pID_BUTTON_Ok );
// 	assert( m_pID_BUTTON_Cancel );
// 	assert( m_pID_TEXT_UseMoneyZ );
// 	assert( m_pID_TEXT_UseMoney );
// 	assert( m_pID_PICTURE_LeftTitle );
// 	assert( m_pID_PICTURE_TitleWord );
// 	assert( m_pID_TEXT_Explain );
// 	assert( m_pID_PICTURE_ItemWall2 );
// 	assert( m_pID_LISTIMG_Aim );
// 	assert( m_pID_TEXT_ArmourName );
// 	assert( m_pID_TEXT_AimName );
// 	assert( m_pID_PICTURE_SpecialRepairEffect );

	m_equipBagIndex = -1;
	m_materialBagIndex = -1;
	m_bShowError = true;
	m_bStartAnim = false;
	m_bStartIntonate = false;
	m_dwStartIntonateTime = 0;
	m_nIntonateTime = 0;
	RECT rc;
	m_pID_PICTURE_SpecialRepairEffect->GetRealRect(&rc);
	m_slideAnim.Initialize("Ui\\Common\\SpecialRepairEffect\\SpecialRepairEffect", 22, rc, 1400);

	Clear();

	SetVisable(false);

	m_pID_FRAME_SpecialRepair->SetOnVisibleChangedFun(OnVisibleChanged);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SpecialRepair::_UnLoadUI()
{
	ResetMembers();
	ClearAnim();
	return theUiManager.RemoveFrame( "Data\\UI\\SpecialRepair.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SpecialRepair::_IsVisable()
{
	if (!m_pID_FRAME_SpecialRepair)
		return false;
	return m_pID_FRAME_SpecialRepair->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SpecialRepair::_SetVisable( const bool bVisable )
{
	if (!m_pID_FRAME_SpecialRepair)
		return;
	m_pID_FRAME_SpecialRepair->SetVisable( bVisable );

	if (bVisable)
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if ( pMe )
			m_vVisiblePos = *(Vector*)&pMe->GetPos();

		s_CUI_ID_FRAME_PACK.SetVisable(true);
	}
	ClearAnim();
}

bool CUI_ID_FRAME_SpecialRepair::SetEquip(ControlIconDrag::S_ListImg *pItem, ItemDefine::SItemCanEquip* pCanEquip)
{
	// 不能放入普通修理装备
	if (pCanEquip->uchRepairType == ItemDefine::SItemCanEquip::ECD_Repair_Normal)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Fix_Failed, theXmlString.GetString( eText_NotSpecialRepair ) );
		return false;
	}

	int index = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItem );
	if (index == -1)
		return false;

	SetEquipIndex(index);

	// 刷新金钱
	m_needRepairMoney = pCanEquip->stRepairPrice * (pCanEquip->stHPMax - ((SCharItem*)pItem->m_pkIconInfo->GetData())->equipdata.usHP);
	if (m_needRepairMoney <= 0)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Fix_Failed, theXmlString.GetString( eText_NotNeedRepairFineEquip ) );
		return false;
	}

	std::string text = "";
	thePlayerRole.GetGSCStringFromJiaoZi(m_needRepairMoney, text);

	if (thePlayerRole.GetData( CPlayerRole::TYPE_MONEY ) >= m_needRepairMoney)
		m_pID_TEXT_UseMoney->SetText(text);
	else
		m_pID_TEXT_UseMoney->SetText(text, D3DCOLOR_XRGB(255,0,0));

	// 刷新装备ICON
	ControlIconDrag::S_ListImg item = *pItem;
	item.m_eEnable = eIcon_Enable;
	m_pID_LISTIMG_Armour->SetItem(&item, 0);
	m_equip = *(SCharItem*)(item.m_pkIconInfo->GetData());

	// 刷新装备名字
	//m_pID_TEXT_ArmourName->SetText(pCanEquip->GetItemName());

	// 刷新修理道具名字
	ItemDefine::SItemCommon* pRepairItem = GettheItemDetail().GetItemByID( pCanEquip->nRepairValue );
	char buf[256];
	if (pRepairItem)
	{
		sprintf(buf, theXmlString.GetString(eText_NeedFillItem),
			S_IconInfoHero::GetQualityColor(pRepairItem->ustLevel), pRepairItem->GetItemName());
	}
	else
		sprintf(buf, theXmlString.GetString(eText_NeedFillItem), 0xFFFFFFFF, "");

	//m_pID_TEXT_AimName->SetText(buf);

	m_equipEnable = false;
	m_bNeedUpdate = true;

	m_bShowError = false;
	SeachMaterialAndSetMaterial(this, &CUI_ID_FRAME_SpecialRepair::SetAim_);
	m_bShowError = true;
	return true;
}

bool CUI_ID_FRAME_SpecialRepair::SetEquip(ControlObject* pSender, ControlIconDrag::S_ListImg* pItemDrag)
{
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if( pItemCommon && ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON ||
		pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR ) )
	{
		ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
		if( !pImageSender )
			return false;

		// 包裹里
		if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pImageSender) )
		{
			ItemDefine::SItemCanEquip* pCanEquip = (ItemDefine::SItemCanEquip*)pItemCommon;
			return SetEquip(pItemDrag, pCanEquip);
		}
		else
		{
			return false;
		}
	}	
	return false;
}

void CUI_ID_FRAME_SpecialRepair::SetEquipIndex(int index)
{
	if (m_equipBagIndex != -1)
	{
		m_equipEnable = true;
		RefreshEquipIconEnable();
	}

	m_equipBagIndex = index;
}

bool CUI_ID_FRAME_SpecialRepair::SetAim(ControlIconDrag::S_ListImg *pItem, ItemDefine::SItemCommon *pItemCommon)
{
	if (m_equip.itembaseinfo.ustItemID == InvalidLogicNumber)
		return false;

	ItemDefine::SItemCanEquip* pCanEquip = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( m_equip.itembaseinfo.ustItemID );
	switch (pCanEquip->uchRepairType)
	{
	case ItemDefine::SItemCanEquip::ECD_Repair_Item:
		{
			// 道具不符合
			if (pCanEquip->nRepairValue != pItemCommon->ustItemID)
			{
				return false;
			}

			ItemDefine::SItemCommon* pRepairItem = GettheItemDetail().GetItemByID( pCanEquip->nRepairValue );
			switch (pRepairItem->ucItemType)
			{
			case ItemDefine::ITEMTYPE_MATERIAL:
				m_pMaterialBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag);
				m_pMaterialBag = &thePlayerRole.m_bagMaterial;
				m_bagType = BT_MaterialBag;
				break;
			case ItemDefine::ITEMTYPE_TASK:
				m_pMaterialBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_TaskBag);
				m_pMaterialBag = &thePlayerRole.m_bagTask;
				m_bagType = BT_TaskBag;
				break;
			default:
				m_pMaterialBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag);
				m_pMaterialBag = &thePlayerRole.m_bag;
				m_bagType = BT_NormalItemBag;
				break;
			}
			break;
		}
	default:
		{
			return false;
		}
	}

	int index = m_pMaterialBagListImg->GetItemIndex( pItem );
	if (index == -1)
		return false;

	SetAimIndex(index);

	// 刷新修理道具ICON
	ControlIconDrag::S_ListImg item = *pItem;
	item.m_eEnable = eIcon_Enable;
	m_pID_LISTIMG_Aim->SetItem(&item, 0);

	if (thePlayerRole.GetData( CPlayerRole::TYPE_MONEY ) >= m_needRepairMoney)
		m_pID_BUTTON_Ok->SetEnable(true);

	m_materialEnable = false;
	m_bNeedUpdate = true;
	return true;
}

bool CUI_ID_FRAME_SpecialRepair::SetAim_(ControlObject* pSender, ControlIconDrag::S_ListImg* pItemDrag)
{
	if (m_equipBagIndex == -1)
		return false;

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if( pItemCommon )
	{
		ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
		if( !pImageSender )
			return false;

		return SetAim(pItemDrag, pItemCommon);
	}	
	return false;
}

void CUI_ID_FRAME_SpecialRepair::SetAimIndex(int index)
{
	if (m_materialBagIndex != -1)
	{
		m_materialEnable = true;
		RefreshMaterialIconEnable();
	}

	m_materialBagIndex = index;
}

bool CUI_ID_FRAME_SpecialRepair::RequestRepair()
{
	if (m_needRepairMoney > thePlayerRole.GetData( CPlayerRole::TYPE_MONEY ))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Fix_Failed, theXmlString.GetString(eText_Error_NotEnoughMoney) );
		return false;
	}

	// 开始吟唱
	if( !m_bStartIntonate )
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if( pMe && !pMe->IsMoving() && !pMe->IsJumping() )
		{
			m_bStartIntonate = true;
			m_dwStartIntonateTime = HQ_TimeGetTime();
			m_nIntonateTime = 3000;
			s_CUI_Progress.ShowByTime( m_dwStartIntonateTime, m_nIntonateTime, true, 1, true, true, theXmlString.GetString(eText_SpecialRepair_Progress) );
		}
		else
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Fix_Failed, theXmlString.GetString(eClient_AddInfo_2slk_11) );
		}
	}
	return true;
}

void CUI_ID_FRAME_SpecialRepair::Clear()
{
	ClearEquip();
	m_bNeedUpdate = false;
}

void CUI_ID_FRAME_SpecialRepair::ClearEquip()
{
	SetEquipIndex(-1);
	m_equip.itembaseinfo.ustItemID = InvalidLogicNumber;

	m_pID_LISTIMG_Armour->Clear();
	//m_pID_TEXT_ArmourName->SetText("");
	m_pID_TEXT_UseMoney->SetText("");

// 	char buf[256];
// 	sprintf(buf, theXmlString.GetString(eText_NeedFillItem), 0xFFFFFFFF, "");
// 	m_pID_TEXT_AimName->SetText(buf);

	ClearAim();
}

void CUI_ID_FRAME_SpecialRepair::ClearAim()
{
	SetAimIndex(-1);

	m_pMaterialBag = NULL;
	m_pMaterialBagListImg = NULL;

	m_pID_LISTIMG_Aim->Clear();

	m_pID_BUTTON_Ok->SetEnable(false);
}

void CUI_ID_FRAME_SpecialRepair::RepairAck(MsgSpecialRepairItemAck* pAck)
{
	if( !m_pID_FRAME_SpecialRepair )
		return;
	switch (pAck->chResult)
	{
	case MsgSpecialRepairItemAck::ECD_Success:
		{
			unsigned short id;
			if (!thePlayerRole.m_bag.IsHaveItem(pAck->stEquipIndex, &id))
				return;
			SCharItem& item = thePlayerRole.m_bag.m_pPackItem[pAck->stEquipIndex];
			item.equipdata.usHP = pAck->fEquipHp;
			s_CUI_ID_FRAME_PACK.RefreshNormalPackByIndex(pAck->stEquipIndex);
			Clear();

			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Fix_Success, theXmlString.GetString( eText_RepairSuccess ) );
			break;
		}
	case MsgSpecialRepairItemAck::ECD_NotItem:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Fix_Failed, theXmlString.GetString( eText_NotFindRepairItem ) );
			break;
		}
	case MsgSpecialRepairItemAck::ECD_NotEnoughMoney:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Fix_Failed, theXmlString.GetString(eText_Error_NotEnoughMoney) );
			break;
		}
	default:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Fix_Failed, "修理失败" );
			break;
		}
	}
}

void CUI_ID_FRAME_SpecialRepair::RefreshBagIconEnable()
{
	RefreshEquipIconEnable();
	RefreshMaterialIconEnable();
}

void CUI_ID_FRAME_SpecialRepair::RefreshEquipIconEnable()
{
	if( m_equipBagIndex != -1 )
	{
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_equipBagIndex, true );
	}
}

void CUI_ID_FRAME_SpecialRepair::RefreshMaterialIconEnable()
{
	if( m_materialBagIndex!= -1 )
	{
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( m_pMaterialBag, m_materialBagIndex, true );
	}
}

void CUI_ID_FRAME_SpecialRepair::OnVisibleChanged(ControlObject* pSender)
{
	s_CUI_ID_FRAME_SpecialRepair.Clear();
	s_CUI_ID_FRAME_SpecialRepair.ClearAnim();
}

void CUI_ID_FRAME_SpecialRepair::ClearAnim()
{
	if( m_bStartAnim )
	{
		m_bStartAnim = false;
		m_slideAnim.StopAnimation();
		m_slideAnim.UnRelativePicResource();
	}
	if( m_bStartIntonate )
	{
		m_bStartIntonate = false;
		s_CUI_Progress.SetProgressComplete();
	}
}