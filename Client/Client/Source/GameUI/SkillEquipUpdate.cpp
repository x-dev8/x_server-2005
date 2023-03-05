/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\SkillEquipUpdate.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SkillEquipUpdate.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "SuitOperateConfig.h"
#include "ScreenInfoManager.h"

CUI_ID_FRAME_SkillEquipUpdate s_CUI_ID_FRAME_SkillEquipUpdate;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SkillEquipUpdate, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SkillEquipUpdate, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipUpdate, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipUpdate, ID_BUTTON_helpOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SkillEquipUpdate, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipUpdate, ID_LISTIMG_ArmourOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipUpdate, ID_LISTIMG_ArmourOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SkillEquipUpdate, ID_LISTIMG_ArmourOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipUpdate, ID_BUTTON_CancelOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Material1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Material1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Material1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Material1OnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipUpdate, ID_BUTTON_SureOnButtonClick )
// MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Material2OnIconDragOn )
// MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Material2OnIconLDBClick )
// MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Material2OnIconButtonClick )
// MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Material2OnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipUpdate, ID_BUTTON_ResetOnButtonClick )
CUI_ID_FRAME_SkillEquipUpdate::CUI_ID_FRAME_SkillEquipUpdate()
{
	// Member
	ResetMembers();
}

void CUI_ID_FRAME_SkillEquipUpdate::ResetMembers()
{
	m_pID_FRAME_SkillEquipUpdate = NULL;
	//m_pID_PICTURE_RightTitle = NULL;
	m_pID_PICTURE_MiddleTitle = NULL;
// 	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
	m_pID_PICTURE_ItemWall = NULL;
	m_pID_LISTIMG_Armour = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_UseMoneyZ = NULL;
	m_pID_TEXT_UseMoney = NULL;
// 	m_pID_PICTURE_LeftTitle = NULL;
// 	m_pID_PICTURE_TitleWord = NULL;
	m_pID_PICTURE_ItemWall2 = NULL;
	m_pID_LISTIMG_Material1 = NULL;
	m_pID_BUTTON_Sure = NULL;
// 	m_pID_PICTURE_TitleWordReturn = NULL;
// 	m_pID_LISTIMG_Material2 = NULL;
	m_pID_BUTTON_Reset = NULL;

}
// Frame
bool CUI_ID_FRAME_SkillEquipUpdate::OnFrameRun()
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
	}

	Update();
	return true;
}
bool CUI_ID_FRAME_SkillEquipUpdate::OnFrameRender()
{
	if (m_isStart)
	{
		RECT rc;
		m_pID_PICTURE_MiddleTitle->GetRealRect(&rc);
		m_slideAnim.Update(HQ_TimeGetTime(), &rc);
		if (!m_slideAnim.IsInAnimation())
		{
			ShowResult();
		}
	}
	return true;
}
// Button
bool CUI_ID_FRAME_SkillEquipUpdate::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_SkillEquipUpdate)
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SkillEquipUpdate::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_SkillEquipUpdate)
		return false;
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SkillEquipUpdate::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																  ControlIconDrag::S_ListImg* pItemDrag,
																  ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!m_pID_FRAME_SkillEquipUpdate)
		return false;
	return SetEquip(pSender, pItemDrag);
}
bool CUI_ID_FRAME_SkillEquipUpdate::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_SkillEquipUpdate)
		return false;
	return false;
}
bool CUI_ID_FRAME_SkillEquipUpdate::ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_SkillEquipUpdate)
		return false;
	return false;
}
bool CUI_ID_FRAME_SkillEquipUpdate::ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_SkillEquipUpdate)
		return false;
	ClearEquip();
	return true;
}
// Button
bool CUI_ID_FRAME_SkillEquipUpdate::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_SkillEquipUpdate)
		return false;
	SetVisable(false);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SkillEquipUpdate::ID_LISTIMG_Material1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																	 ControlIconDrag::S_ListImg* pItemDrag,
																	 ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!m_pID_FRAME_SkillEquipUpdate)
		return false;
	return SetMaterial0(pSender, pItemDrag);
}
bool CUI_ID_FRAME_SkillEquipUpdate::ID_LISTIMG_Material1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_SkillEquipUpdate)
		return false;
	return false;
}
bool CUI_ID_FRAME_SkillEquipUpdate::ID_LISTIMG_Material1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_SkillEquipUpdate)
		return false;
	return false;
}
bool CUI_ID_FRAME_SkillEquipUpdate::ID_LISTIMG_Material1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_SkillEquipUpdate)
		return false;
	ClearMaterial0();
	return false;
}
// Button
bool CUI_ID_FRAME_SkillEquipUpdate::ID_BUTTON_SureOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_SkillEquipUpdate)
		return false;
	OnOk();
	return true;
}
// ListImg / ListEx
// bool CUI_ID_FRAME_SkillEquipUpdate::ID_LISTIMG_Material2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
// 																	 ControlIconDrag::S_ListImg* pItemDrag,
// 																	 ControlIconDrag::S_ListImg* pItemSrc )
// {
// 	if(!m_pID_FRAME_SkillEquipUpdate)
// 		return false;
// 	return false;
// }
// bool CUI_ID_FRAME_SkillEquipUpdate::ID_LISTIMG_Material2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if(!m_pID_FRAME_SkillEquipUpdate)
// 		return false;
// 	return false;
// }
// bool CUI_ID_FRAME_SkillEquipUpdate::ID_LISTIMG_Material2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if(!m_pID_FRAME_SkillEquipUpdate)
// 		return false;
// 	return false;
// }
// bool CUI_ID_FRAME_SkillEquipUpdate::ID_LISTIMG_Material2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if(!m_pID_FRAME_SkillEquipUpdate)
// 		return false;
// 	return false;
// }
// Button
bool CUI_ID_FRAME_SkillEquipUpdate::ID_BUTTON_ResetOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_SkillEquipUpdate)
		return false;
	ClearEquip();
	return true;
}

// 装载UI
bool CUI_ID_FRAME_SkillEquipUpdate::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SkillEquipUpdate.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SkillEquipUpdate.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SkillEquipUpdate::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SkillEquipUpdate, s_CUI_ID_FRAME_SkillEquipUpdateOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SkillEquipUpdate, s_CUI_ID_FRAME_SkillEquipUpdateOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_SkillEquipUpdate, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SkillEquipUpdateID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SkillEquipUpdate, ID_BUTTON_help, s_CUI_ID_FRAME_SkillEquipUpdateID_BUTTON_helpOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Armour, s_CUI_ID_FRAME_SkillEquipUpdateID_LISTIMG_ArmourOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Armour, s_CUI_ID_FRAME_SkillEquipUpdateID_LISTIMG_ArmourOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Armour, s_CUI_ID_FRAME_SkillEquipUpdateID_LISTIMG_ArmourOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Armour, s_CUI_ID_FRAME_SkillEquipUpdateID_LISTIMG_ArmourOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_SkillEquipUpdate, ID_BUTTON_Cancel, s_CUI_ID_FRAME_SkillEquipUpdateID_BUTTON_CancelOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Material1, s_CUI_ID_FRAME_SkillEquipUpdateID_LISTIMG_Material1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Material1, s_CUI_ID_FRAME_SkillEquipUpdateID_LISTIMG_Material1OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Material1, s_CUI_ID_FRAME_SkillEquipUpdateID_LISTIMG_Material1OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Material1, s_CUI_ID_FRAME_SkillEquipUpdateID_LISTIMG_Material1OnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_SkillEquipUpdate, ID_BUTTON_Sure, s_CUI_ID_FRAME_SkillEquipUpdateID_BUTTON_SureOnButtonClick );
// 	theUiManager.OnIconDragOn( ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Material2, s_CUI_ID_FRAME_SkillEquipUpdateID_LISTIMG_Material2OnIconDragOn );
// 	theUiManager.OnIconLDBClick( ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Material2, s_CUI_ID_FRAME_SkillEquipUpdateID_LISTIMG_Material2OnIconLDBClick );
// 	theUiManager.OnIconButtonClick( ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Material2, s_CUI_ID_FRAME_SkillEquipUpdateID_LISTIMG_Material2OnIconButtonClick );
// 	theUiManager.OnIconRButtonUp( ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Material2, s_CUI_ID_FRAME_SkillEquipUpdateID_LISTIMG_Material2OnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_SkillEquipUpdate, ID_BUTTON_Reset, s_CUI_ID_FRAME_SkillEquipUpdateID_BUTTON_ResetOnButtonClick );

	m_pID_FRAME_SkillEquipUpdate = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SkillEquipUpdate );
	//m_pID_PICTURE_RightTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillEquipUpdate, ID_PICTURE_RightTitle );
	m_pID_PICTURE_MiddleTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillEquipUpdate, ID_PICTURE_MiddleTitle );
// 	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SkillEquipUpdate, ID_BUTTON_CLOSE );
// 	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_SkillEquipUpdate, ID_BUTTON_help );
	m_pID_PICTURE_ItemWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillEquipUpdate, ID_PICTURE_ItemWall );
	m_pID_LISTIMG_Armour = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Armour );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_SkillEquipUpdate, ID_BUTTON_Cancel );
	m_pID_TEXT_UseMoneyZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquipUpdate, ID_TEXT_UseMoneyZ );
	m_pID_TEXT_UseMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquipUpdate, ID_TEXT_UseMoney );
// 	m_pID_PICTURE_LeftTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillEquipUpdate, ID_PICTURE_LeftTitle );
// 	m_pID_PICTURE_TitleWord = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillEquipUpdate, ID_PICTURE_TitleWord );
	m_pID_PICTURE_ItemWall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillEquipUpdate, ID_PICTURE_ItemWall2 );
	m_pID_LISTIMG_Material1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Material1 );
	m_pID_BUTTON_Sure = (ControlButton*)theUiManager.FindControl( ID_FRAME_SkillEquipUpdate, ID_BUTTON_Sure );
// 	m_pID_PICTURE_TitleWordReturn = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillEquipUpdate, ID_PICTURE_TitleWordReturn );
	//m_pID_LISTIMG_Material2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SkillEquipUpdate, ID_LISTIMG_Material2 );
	m_pID_TEXT_ChangeInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquipUpdate, ID_TEXT_ChangeInfo );
	m_pID_BUTTON_Reset = (ControlButton*)theUiManager.FindControl( ID_FRAME_SkillEquipUpdate, ID_BUTTON_Reset );
// 	assert( m_pID_FRAME_SkillEquipUpdate );
// 	assert( m_pID_PICTURE_RightTitle );
// 	assert( m_pID_PICTURE_MiddleTitle );
// 	assert( m_pID_BUTTON_CLOSE );
// 	assert( m_pID_BUTTON_help );
// 	assert( m_pID_PICTURE_ItemWall );
// 	assert( m_pID_LISTIMG_Armour );
// 	assert( m_pID_BUTTON_Cancel );
// 	assert( m_pID_TEXT_UseMoneyZ );
// 	assert( m_pID_TEXT_UseMoney );
// 	assert( m_pID_PICTURE_LeftTitle );
// 	assert( m_pID_PICTURE_TitleWord );
// 	assert( m_pID_PICTURE_ItemWall2 );
// 	assert( m_pID_LISTIMG_Material1 );
// 	assert( m_pID_BUTTON_Sure );
// 	assert( m_pID_PICTURE_TitleWordReturn );
// 	assert( m_pID_LISTIMG_Material2 );

	RECT rc;
	m_pID_PICTURE_MiddleTitle->GetRealRect(&rc);
	m_slideAnim.Initialize("Ui\\Common\\SkillEquipEffect\\HudSkillEquipFire", 15, rc, 2000);

	m_isStart = false;
	m_hasAck = false;
	m_result = 0;

	m_pID_FRAME_SkillEquipUpdate->SetOnVisibleChangedFun(OnVisibleChanged);
	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SkillEquipUpdate::_UnLoadUI()
{
	m_pID_FRAME_SkillEquipUpdate = NULL;
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\SkillEquipUpdate.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SkillEquipUpdate::_IsVisable()
{
	if(!m_pID_FRAME_SkillEquipUpdate)
		return false;

	return m_pID_FRAME_SkillEquipUpdate->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SkillEquipUpdate::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_SkillEquipUpdate)
		return;
	m_pID_FRAME_SkillEquipUpdate->SetVisable( bVisable );

	if (bVisable)
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if ( pMe )
			m_vVisiblePos = *(Vector*)&pMe->GetPos();
	}
}

bool CUI_ID_FRAME_SkillEquipUpdate::_CanSetEquipCallback(ControlObject *pSender, ControlIconDrag::S_ListImg *pItemDrag, ItemDefine::SItemCanEquip *pDragItemCanEquip)
{
	// 当前状态不能放入东西
	if (!IsActived())
		return false;

	if (pDragItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_ARMOUR)
	{
		ShowError(eClient_SkillSuitCannotUpgrade);
		return false;
	}

	// 不是套装技能的装备部件
	ItemDefine::SItemArmour* pArmour = (ItemDefine::SItemArmour*)pDragItemCanEquip;
	if (!pArmour->IsSkillSuitEquip())
	{
		ShowError(eClient_SkillSuitCannotUpgrade);
		return false;
	}

	// 不能放入满级的装备部件
	if (((SCharItem*)pItemDrag->m_pkIconInfo->GetData())->GetSuitLevel() >= SkillSuitLevelUp::GetMaxLevel())
	{
		ShowError(eClient_SkillSuitMaxLevel);
		return false;
	}

	return true;
}

bool CUI_ID_FRAME_SkillEquipUpdate::_CanSetMaterial0Callback(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag, ItemDefine::SItemCommon* pDragItemCommon)
{
	// 当前状态不能放入东西
	if (!IsActived())
		return false;

	// 材料不符合
	if (pDragItemCommon->ucItemType != ItemDefine::ITEMTYPE_CHECKUP)
	{
		ShowError(eClient_SkillSuitUpgradeItemError);
		return false;
	}

	// 材料不符合
	ItemDefine::SItemCheckUp* pItemCheckUp = (ItemDefine::SItemCheckUp*)pDragItemCommon;
	if (pItemCheckUp->stCheckUpType != ItemDefine::SItemCheckUp::ECD_Suit ||
		pItemCheckUp->stEffectType != ItemDefine::SItemCheckUp::ECD_SkillSuitLevel)
	{
		ShowError(eClient_SkillSuitUpgradeItemError);
		return false;
	}

	ItemDefine::SItemArmour* pArmour = (ItemDefine::SItemArmour*)GettheItemDetail().GetItemByID( m_equip.itembaseinfo.ustItemID );
	if ( pItemCheckUp->nValue1 == 0 || pItemCheckUp->nValue2 == 0 ) // 错误的鉴定材料
	{
		ShowError(eClient_SkillSuitUpgradeItemError);
		return false;
	}

	switch ( pArmour->cEquipSexReq )
	{
	case Sex_Male:
		if ( pArmour->sSuitID != pItemCheckUp->nValue1 )
		{
			ShowError(eClient_SkillSuitUpgradeItemError);
			return false;
		}
		break;

	case Sex_Female:
		if ( pArmour->sSuitID != pItemCheckUp->nValue2 )
		{
			ShowError(eClient_SkillSuitUpgradeItemError);
			return false;
		}
		break;
	}

	// 材料升级装备的作用等级不够
	if (pItemCheckUp->stEffectLevel <= m_equip.GetSuitLevel() || 
		pItemCheckUp->stEquipLevel < pArmour->stEquipLevelReq)
	{
		ShowError(eClient_SkillSuitUpgradeLessItemLevel);
		return false;
	}

	return true;
}

void CUI_ID_FRAME_SkillEquipUpdate::_SetEquipCallback(ControlIconDrag::S_ListImg& item)
{
	m_pID_LISTIMG_Armour->SetItem(&item, 0);

	// 钱
	ItemDefine::SItemArmour* pArmour = (ItemDefine::SItemArmour*)GettheItemDetail().GetItemByID( m_equip.itembaseinfo.ustItemID );
	int money = theSuitOperateConfig.GetSkillSuitLevelUpCostMoney(pArmour->stEquipLevelReq);
	m_needMoney = money;

	std::string text = "";
	thePlayerRole.GetGSCStringFromJiaoZi(money, text);
	m_pID_TEXT_UseMoney->SetText(text);

	RefreshControls();
}

void CUI_ID_FRAME_SkillEquipUpdate::_SetMaterial0Callback(ControlIconDrag::S_ListImg& item)
{
	m_pID_LISTIMG_Material1->SetItem(&item, 0);
	RefreshControls();
}

void CUI_ID_FRAME_SkillEquipUpdate::_ClearEquipCallback()
{
	m_pID_LISTIMG_Armour->Clear();
	ShowControls(true);
	RefreshControls();
}

void CUI_ID_FRAME_SkillEquipUpdate::_ClearMaterial0Callback()
{
	m_pID_LISTIMG_Material1->Clear();
	RefreshControls();
}

void CUI_ID_FRAME_SkillEquipUpdate::OnVisibleChanged(ControlObject* pSender)
{
	if (s_CUI_ID_FRAME_SkillEquipUpdate.m_isStart)
	{
		s_CUI_ID_FRAME_SkillEquipUpdate.SetVisable(true);
		return;
	}

	s_CUI_ID_FRAME_SkillEquipUpdate.Clear();

	if (pSender->IsVisable())
	{

		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if ( pMe )
			s_CUI_ID_FRAME_SkillEquipUpdate.m_vVisiblePos = *(Vector*)&pMe->GetPos();

		s_CUI_ID_FRAME_PACK.SetVisable(true);
	}
}

void CUI_ID_FRAME_SkillEquipUpdate::RefreshControls()
{
	bool enable = m_equipBagIndex != -1 && m_materialBagIndex[0] != -1;
	m_pID_BUTTON_Sure->SetEnable(enable);
	m_pID_BUTTON_Cancel->SetEnable(true);

	if (m_equipBagIndex == -1)
		m_pID_TEXT_UseMoney->SetText("");
}

void CUI_ID_FRAME_SkillEquipUpdate::OnOk()
{
    if(!thePlayerRole.HaveEnoughMoney(m_needMoney))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Identify, theXmlString.GetString(eClient_SkillSuitUpgradeNoMoney) );
		return;
	}

	MsgSuitLevelUpReq req;
	req.stEquipIndex = m_equipBagIndex;
	req.nEquipGuid = m_equip.itembaseinfo.nOnlyInt;
	req.chOperate = MsgSuitLevelUpReq::ECD_SkillSuitLevelUp;
	// 第一个材料
	req.xItemInfo[0].chItemBagType = m_bagTypeMateral[0];
	req.xItemInfo[0].stItemIndex = m_materialBagIndex[0];
	req.xItemInfo[0].nItemGuid = m_material[0].itembaseinfo.nOnlyInt;
	GettheNetworkInput().SendMsg( &req );

	m_pID_BUTTON_Sure->SetEnable(false);
	m_pID_BUTTON_Cancel->SetEnable(false);

	ShowControls(false);

	m_slideAnim.StartAnimation(HQ_TimeGetTime());

	m_hasAck = false;
	m_isStart = true;
}

void CUI_ID_FRAME_SkillEquipUpdate::OnAck(MsgSuitLevelUpAck* pAck)
{
	//if( !m_pID_FRAME_SkillEquipUpdate )
	//	return;

	//switch (pAck->uchResult)
	//{
	//case MsgSuitLevelUpAck::ECD_SuccessSkillSuit:
	//	{
	//		if (GetEquipItem())
	//		{
	//			GetEquipItem()->itembaseinfo.value1 = pAck->nValue;
	//			GetEquipItem()->equipdata.specials[SCharItem::e_SkillSuitIndex] = pAck->stAttriID;
	//		}
	//	}
	//	break;
	//case MsgSuitLevelUpAck::ECD_CheckUpFailed:
	//	break;
	//default:
	//	break;
	//}

	//m_result = pAck->uchResult;
	//m_hasAck = true;

	//if (!m_slideAnim.IsInAnimation()) // 火焰停止了
	//{
	//	ShowResult();
	//}
}

void CUI_ID_FRAME_SkillEquipUpdate::ShowResult()
{/*
	if (m_hasAck)
	{
		ClearMaterial0();
		RefreshBagIconEnable();

		m_pID_TEXT_ChangeInfo->SetVisable(true);
		m_pID_PICTURE_ItemWall->SetVisable(true);
		m_pID_BUTTON_Reset->SetVisable(true);

		if (m_result == MsgSuitLevelUpAck::ECD_SuccessSkillSuit)
		{
			ItemDefine::SRandAttribute* pArmourRand = NULL;
			ControlIconDrag::S_ListImg* pSrc = s_CUI_ID_FRAME_PACK.GetItemByIndex( BT_NormalItemBag, m_equipBagIndex );
			if (pSrc)
			{
				ControlIconDrag::S_ListImg item = *pSrc;
				item.m_eEnable = eIcon_Enable;
				m_pID_LISTIMG_Armour->SetItem(&item, 0);

				pArmourRand = GettheItemDetail().GetRandByID(
					((SCharItem*)item.m_pkIconInfo->GetData())->equipdata.gemIds[SCharItem::e_SkillSuitIndex]);
			}

			std::string strInfo;
			strInfo = theXmlString.GetString(eClient_SkillSuitUpgradeSuccess);
			strInfo += "\n";

			if (pArmourRand)
			{
				int nRandValue = InvalidLogicNumber;
				int nTipPreTextIndex = 0;
				char szBuf[256];
				for( int i = 0 ; i < ItemDefine::SRandAttribute::CD_TypeCount ; ++ i )
				{
					if( pArmourRand->type[i] == CItemDetail::RT_None )continue;
                    nRandValue = S_IconInfoHero::GetRandValueByType( pArmourRand, i );
					if( nRandValue != InvalidLogicNumber )  
					{ 
						sprintf( szBuf, "%s+%d", 
							S_IconInfoHero::GetRandStringByType( pArmourRand->type[i] ),
							nRandValue );  

						strInfo += szBuf;
						strInfo += "    ";
					}
				}

				// 去掉后面的空格
				if (strInfo.length() > strlen("    "))
					strInfo.erase(strInfo.length() - strlen("    "));
			}

			m_pID_TEXT_ChangeInfo->SetText(strInfo);
		}
		else
		{
			m_pID_TEXT_ChangeInfo->SetText(theXmlString.GetString(eClient_SkillSuitUpgradeFailed));
		}
	}

	m_isStart = false;
	m_slideAnim.UnRelativePicResource();
    */
}

bool CUI_ID_FRAME_SkillEquipUpdate::IsActived()
{
	// 当前状态不能放入东西
	if (!m_pID_LISTIMG_Material1->IsVisable())
		return false;
	return true;
}

void CUI_ID_FRAME_SkillEquipUpdate::ShowControls(bool bInitializeStatus)
{
	m_pID_LISTIMG_Material1->SetVisable(bInitializeStatus);
	m_pID_PICTURE_ItemWall2->SetVisable(bInitializeStatus);
	if (bInitializeStatus)
	{
		m_pID_TEXT_ChangeInfo->SetVisable(false);
		m_pID_PICTURE_ItemWall->SetVisable(false);
		m_pID_BUTTON_Reset->SetVisable(false);
	}
}