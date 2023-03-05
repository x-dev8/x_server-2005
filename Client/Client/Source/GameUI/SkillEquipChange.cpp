/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\SkillEquipChange.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SkillEquipChange.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "SuitOperateConfig.h"
#include "XmlStringLanguage.h"
#include "MeUI/ExpressionManager.h"
#include "color_config.h"
#include "ScreenInfoManager.h"
#include "Common.h"

CUI_ID_FRAME_SkillEquipChange s_CUI_ID_FRAME_SkillEquipChange;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SkillEquipChange, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SkillEquipChange, OnFrameRender )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipChange, ID_BUTTON_CLOSEOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipChange, ID_BUTTON_helpOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SkillEquipChange, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipChange, ID_LISTIMG_ArmourOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipChange, ID_LISTIMG_ArmourOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SkillEquipChange, ID_LISTIMG_ArmourOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipChange, ID_BUTTON_CancelOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SkillEquipChange, ID_LISTIMG_Material1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipChange, ID_LISTIMG_Material1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipChange, ID_LISTIMG_Material1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SkillEquipChange, ID_LISTIMG_Material1OnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipChange, ID_BUTTON_SureOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SkillEquipChange, ID_LISTIMG_Material2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipChange, ID_LISTIMG_Material2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipChange, ID_LISTIMG_Material2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SkillEquipChange, ID_LISTIMG_Material2OnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquipChange, ID_BUTTON_ResetOnButtonClick )
CUI_ID_FRAME_SkillEquipChange::CUI_ID_FRAME_SkillEquipChange()
{
	// Member
	ResetMembers();
}
void CUI_ID_FRAME_SkillEquipChange::ResetMembers()
{
	m_pID_FRAME_SkillEquipChange = NULL;
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
	//m_pID_PICTURE_TitleWordReturn = NULL;
	m_pID_LISTIMG_Material2 = NULL;
	m_pID_BUTTON_Reset = NULL;

}
// Frame
bool CUI_ID_FRAME_SkillEquipChange::OnFrameRun()
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
bool CUI_ID_FRAME_SkillEquipChange::OnFrameRender()
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
// bool CUI_ID_FRAME_SkillEquipChange::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_SkillEquipChange )
// 		return false;
// 	return true;
// }
// // Button
// bool CUI_ID_FRAME_SkillEquipChange::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_SkillEquipChange )
// 		return false;
// 	return true;
// }
// ListImg / ListEx
bool CUI_ID_FRAME_SkillEquipChange::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																  ControlIconDrag::S_ListImg* pItemDrag,
																  ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SkillEquipChange )
		return false;
	return SetEquip(pSender, pItemDrag);
}
bool CUI_ID_FRAME_SkillEquipChange::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillEquipChange )
		return false;
	return false;
}
bool CUI_ID_FRAME_SkillEquipChange::ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillEquipChange )
		return false;
	return false;
}
bool CUI_ID_FRAME_SkillEquipChange::ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillEquipChange )
		return false;
	ClearEquip();
	return false;
}
// Button
bool CUI_ID_FRAME_SkillEquipChange::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SkillEquipChange )
		return false;
	SetVisable(false);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SkillEquipChange::ID_LISTIMG_Material1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																	 ControlIconDrag::S_ListImg* pItemDrag,
																	 ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SkillEquipChange )
		return false;
	return SetMaterial0(pSender, pItemDrag);
}
bool CUI_ID_FRAME_SkillEquipChange::ID_LISTIMG_Material1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillEquipChange )
		return false;
	return false;
}
bool CUI_ID_FRAME_SkillEquipChange::ID_LISTIMG_Material1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillEquipChange )
		return false;
	return false;
}
bool CUI_ID_FRAME_SkillEquipChange::ID_LISTIMG_Material1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillEquipChange )
		return false;
	ClearMaterial0();
	return false;
}
// Button
bool CUI_ID_FRAME_SkillEquipChange::ID_BUTTON_SureOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SkillEquipChange )
		return false;
	OnOk();
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SkillEquipChange::ID_LISTIMG_Material2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																	 ControlIconDrag::S_ListImg* pItemDrag,
																	 ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SkillEquipChange )
		return false;
	return SetMaterial1(pSender, pItemDrag);
}
bool CUI_ID_FRAME_SkillEquipChange::ID_LISTIMG_Material2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillEquipChange )
		return false;
	return false;
}
bool CUI_ID_FRAME_SkillEquipChange::ID_LISTIMG_Material2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillEquipChange )
		return false;
	return false;
}
bool CUI_ID_FRAME_SkillEquipChange::ID_LISTIMG_Material2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillEquipChange )
		return false;
	ClearMaterial1();
	return false;
}
// Button
bool CUI_ID_FRAME_SkillEquipChange::ID_BUTTON_ResetOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SkillEquipChange )
		return false;
	ClearEquip();
	return true;
}

// 装载UI
bool CUI_ID_FRAME_SkillEquipChange::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SkillEquipChange.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SkillEquipChange.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SkillEquipChange::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SkillEquipChange, s_CUI_ID_FRAME_SkillEquipChangeOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SkillEquipChange, s_CUI_ID_FRAME_SkillEquipChangeOnFrameRender );
// 	theUiManager.OnButtonClick( ID_FRAME_SkillEquipChange, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SkillEquipChangeID_BUTTON_CLOSEOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_SkillEquipChange, ID_BUTTON_help, s_CUI_ID_FRAME_SkillEquipChangeID_BUTTON_helpOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SkillEquipChange, ID_LISTIMG_Armour, s_CUI_ID_FRAME_SkillEquipChangeID_LISTIMG_ArmourOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SkillEquipChange, ID_LISTIMG_Armour, s_CUI_ID_FRAME_SkillEquipChangeID_LISTIMG_ArmourOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SkillEquipChange, ID_LISTIMG_Armour, s_CUI_ID_FRAME_SkillEquipChangeID_LISTIMG_ArmourOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SkillEquipChange, ID_LISTIMG_Armour, s_CUI_ID_FRAME_SkillEquipChangeID_LISTIMG_ArmourOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_SkillEquipChange, ID_BUTTON_Cancel, s_CUI_ID_FRAME_SkillEquipChangeID_BUTTON_CancelOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SkillEquipChange, ID_LISTIMG_Material1, s_CUI_ID_FRAME_SkillEquipChangeID_LISTIMG_Material1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SkillEquipChange, ID_LISTIMG_Material1, s_CUI_ID_FRAME_SkillEquipChangeID_LISTIMG_Material1OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SkillEquipChange, ID_LISTIMG_Material1, s_CUI_ID_FRAME_SkillEquipChangeID_LISTIMG_Material1OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SkillEquipChange, ID_LISTIMG_Material1, s_CUI_ID_FRAME_SkillEquipChangeID_LISTIMG_Material1OnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_SkillEquipChange, ID_BUTTON_Sure, s_CUI_ID_FRAME_SkillEquipChangeID_BUTTON_SureOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SkillEquipChange, ID_LISTIMG_Material2, s_CUI_ID_FRAME_SkillEquipChangeID_LISTIMG_Material2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SkillEquipChange, ID_LISTIMG_Material2, s_CUI_ID_FRAME_SkillEquipChangeID_LISTIMG_Material2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SkillEquipChange, ID_LISTIMG_Material2, s_CUI_ID_FRAME_SkillEquipChangeID_LISTIMG_Material2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SkillEquipChange, ID_LISTIMG_Material2, s_CUI_ID_FRAME_SkillEquipChangeID_LISTIMG_Material2OnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_SkillEquipChange, ID_BUTTON_Reset, s_CUI_ID_FRAME_SkillEquipChangeID_BUTTON_ResetOnButtonClick );

	m_pID_FRAME_SkillEquipChange = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SkillEquipChange );
	//m_pID_PICTURE_RightTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillEquipChange, ID_PICTURE_RightTitle );
	m_pID_PICTURE_MiddleTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillEquipChange, ID_PICTURE_MiddleTitle );
// 	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SkillEquipChange, ID_BUTTON_CLOSE );
// 	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_SkillEquipChange, ID_BUTTON_help );
	m_pID_PICTURE_ItemWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillEquipChange, ID_PICTURE_ItemWall );
	m_pID_LISTIMG_Armour = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SkillEquipChange, ID_LISTIMG_Armour );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_SkillEquipChange, ID_BUTTON_Cancel );
	m_pID_TEXT_UseMoneyZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquipChange, ID_TEXT_UseMoneyZ );
	m_pID_TEXT_UseMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquipChange, ID_TEXT_UseMoney );
// 	m_pID_PICTURE_LeftTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillEquipChange, ID_PICTURE_LeftTitle );
// 	m_pID_PICTURE_TitleWord = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillEquipChange, ID_PICTURE_TitleWord );
	m_pID_PICTURE_ItemWall1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillEquipChange, ID_PICTURE_ItemWall1 );
	m_pID_PICTURE_ItemWall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillEquipChange, ID_PICTURE_ItemWall2 );
	m_pID_LISTIMG_Material1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SkillEquipChange, ID_LISTIMG_Material1 );
	m_pID_BUTTON_Sure = (ControlButton*)theUiManager.FindControl( ID_FRAME_SkillEquipChange, ID_BUTTON_Sure );
	//m_pID_PICTURE_TitleWordReturn = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillEquipChange, ID_PICTURE_TitleWordReturn );
	m_pID_LISTIMG_Material2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SkillEquipChange, ID_LISTIMG_Material2 );
	m_pID_TEXT_ChangeInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquipChange, ID_TEXT_ChangeInfo );
	m_pID_BUTTON_Reset = (ControlButton*)theUiManager.FindControl( ID_FRAME_SkillEquipChange, ID_BUTTON_Reset );
// 	assert( m_pID_FRAME_SkillEquipChange );
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

	m_pID_FRAME_SkillEquipChange->SetOnVisibleChangedFun(OnVisibleChanged);
	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SkillEquipChange::_UnLoadUI()
{
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\SkillEquipChange.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SkillEquipChange::_IsVisable()
{
	if( !m_pID_FRAME_SkillEquipChange )
		return false;

	return m_pID_FRAME_SkillEquipChange->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SkillEquipChange::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_SkillEquipChange )
		return;
	m_pID_FRAME_SkillEquipChange->SetVisable( bVisable );

	if (bVisable)
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if ( pMe )
			m_vVisiblePos = *(Vector*)&pMe->GetPos();
	}
}

bool CUI_ID_FRAME_SkillEquipChange::_CanSetEquipCallback(ControlObject *pSender, ControlIconDrag::S_ListImg *pItemDrag, ItemDefine::SItemCanEquip *pDragItemCanEquip)
{
	// 当前状态不能放入东西
	if (!IsActived())
		return false;

	if (pDragItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_ARMOUR)
	{
		ShowError(eClient_SkillSuitCannotChange);
		return false;
	}

	// 不是套装技能的装备部件
	ItemDefine::SItemArmour* pArmour = (ItemDefine::SItemArmour*)pDragItemCanEquip;
	if (!pArmour->IsSkillSuitEquip())
	{
		ShowError(eClient_SkillSuitCannotChange);
		return false;
	}

	const ChangeCostInfo* pCostInfo = theSuitOperateConfig.GetSkillSuitChangeCostInfo( pArmour->stEquipLevelReq, ((SCharItem*)pItemDrag->m_pkIconInfo->GetData())->GetSuitLevel() );
	if ( pCostInfo == NULL )
	{
		ShowError(eClient_SkillSuitCannotChange);
		return false;
	}

	// 套装技能的装备部件的等级太小，不符合条件
	if (((SCharItem*)pItemDrag->m_pkIconInfo->GetData())->GetSuitLevel() < theSuitOperateConfig.GetMinSkillSuitChangeLevel())
	{
		ShowError(eClient_SkillSuitLessChangeLevel);
		return false;
	}

	return true;
}

bool CUI_ID_FRAME_SkillEquipChange::_CanSetMaterial0Callback(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag, ItemDefine::SItemCommon* pDragItemCommon)
{
	// 当前状态不能放入东西
	if (!IsActived())
		return false;

	// 材料不符合
	if (pDragItemCommon->ucItemType != ItemDefine::ITEMTYPE_CHECKUP)
	{
		ShowError(eClient_SkillSuitChangeItem1Error);
		return false;
	}

	// 材料不符合
	ItemDefine::SItemCheckUp* pItemCheckUp = (ItemDefine::SItemCheckUp*)pDragItemCommon;
	if (pItemCheckUp->stCheckUpType != ItemDefine::SItemCheckUp::ECD_Suit ||
		pItemCheckUp->stEffectType != ItemDefine::SItemCheckUp::ECD_SkillSuitChange)
	{
		ShowError(eClient_SkillSuitChangeItem1Error);
		return false;
	}

	// 材料升级装备的作用等级不够
	if ( theSuitOperateConfig.IsCheckSkillSuitChangeLevel() )
	{
		if (pItemCheckUp->stEffectLevel <= m_equip.GetSuitLevel())
		{
			ShowError(eClient_SkillSuitLessChangeLevel);
			return false;
		}
	}

	return true;
}

bool CUI_ID_FRAME_SkillEquipChange::_CanSetMaterial1Callback(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag, ItemDefine::SItemCommon* pDragItemCommon)
{
	// 当前状态不能放入东西
	if (!IsActived())
		return false;

	ItemDefine::SItemArmour* pArmour = (ItemDefine::SItemArmour*)GettheItemDetail().GetItemByID( m_equip.itembaseinfo.ustItemID );
	const ChangeCostInfo* pCostInfo = theSuitOperateConfig.GetSkillSuitChangeCostInfo( pArmour->stEquipLevelReq, m_equip.GetSuitLevel() );
	if ( pCostInfo == NULL )
	{
		ShowError(eClient_SkillSuitChangeItem2Error);
		return false;
	}

	if ( pCostInfo->GetCostType() != pDragItemCommon->costType )
	{
		ShowError(eClient_SkillSuitChangeItem2Error);
		return false;
	}

	if ( pCostInfo->GetCostType() == ItemDefine::CT_Item )
	{   // 如果是用物品兑换来的东西, 判断数量
		if ( pCostInfo->GetCostValue() != pDragItemCommon->costItemID || pCostInfo->GetCostCount() != pDragItemCommon->dwCost )
		{
			ShowError(eClient_SkillSuitChangeItem2Error);
			return false;
		}
	}
	else
	{
		if ( pCostInfo->GetCostValue() != pDragItemCommon->dwCost )
		{
			ShowError(eClient_SkillSuitChangeItem2Error);
			return false;
		}
	}

	return true;
}

void CUI_ID_FRAME_SkillEquipChange::_SetEquipCallback(ControlIconDrag::S_ListImg& item)
{
	m_pID_LISTIMG_Armour->SetItem(&item, 0);

	// 钱
	ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( m_equip.itembaseinfo.ustItemID );
	int money = theSuitOperateConfig.GetSkillSuitChangeCostMoney(pItemCanEquip->stEquipLevelReq);
	m_needMoney = money;

	std::string text = "";
	thePlayerRole.GetGSCStringFromJiaoZi(money, text);

	if (thePlayerRole.HaveEnoughMoney(m_needMoney))
		m_pID_TEXT_UseMoney->SetText(text);
	else
		m_pID_TEXT_UseMoney->SetText(text, D3DCOLOR_XRGB(255,0,0));

	RefreshControls();
}

void CUI_ID_FRAME_SkillEquipChange::_SetMaterial0Callback(ControlIconDrag::S_ListImg& item)
{
	m_pID_LISTIMG_Material1->SetItem(&item, 0);
	RefreshControls();
}

void CUI_ID_FRAME_SkillEquipChange::_SetMaterial1Callback(ControlIconDrag::S_ListImg& item)
{
	m_pID_LISTIMG_Material2->SetItem(&item, 0);
	RefreshControls();
}

void CUI_ID_FRAME_SkillEquipChange::_ClearEquipCallback()
{
	m_pID_LISTIMG_Armour->Clear();
	ShowControls(true);
	RefreshControls();
}

void CUI_ID_FRAME_SkillEquipChange::_ClearMaterial0Callback()
{
	m_pID_LISTIMG_Material1->Clear();
	RefreshControls();
}

void CUI_ID_FRAME_SkillEquipChange::_ClearMaterial1Callback()
{
	m_pID_LISTIMG_Material2->Clear();
	RefreshControls();
}

void CUI_ID_FRAME_SkillEquipChange::OnVisibleChanged(ControlObject* pSender)
{
	if (s_CUI_ID_FRAME_SkillEquipChange.m_isStart)
	{
		s_CUI_ID_FRAME_SkillEquipChange.SetVisable(true);
		return;
	}

	s_CUI_ID_FRAME_SkillEquipChange.Clear();

	if (pSender->IsVisable())
	{

		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if ( pMe )
			s_CUI_ID_FRAME_SkillEquipChange.m_vVisiblePos = *(Vector*)&pMe->GetPos();

		s_CUI_ID_FRAME_PACK.SetVisable(true);
	}
}

void CUI_ID_FRAME_SkillEquipChange::RefreshControls()
{
	bool enable =
		m_equipBagIndex != -1 &&
		m_materialBagIndex[0] != -1 &&
		m_materialBagIndex[1] != -1 &&
		thePlayerRole.HaveEnoughMoney(m_needMoney);
	m_pID_BUTTON_Sure->SetEnable(enable);
	m_pID_BUTTON_Cancel->SetEnable(true);

	if (m_equipBagIndex == -1)
		m_pID_TEXT_UseMoney->SetText("");
}

void CUI_ID_FRAME_SkillEquipChange::OnOk()
{
	if(!thePlayerRole.HaveEnoughMoney(m_needMoney))
    {
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Identify, theXmlString.GetString(eClient_SkillSuitChangeNoMoney) );
		return;
	}

	MsgSuitChangeReq req;
	req.stEquipIndex = m_equipBagIndex;
	req.nEquipGuid = m_equip.itembaseinfo.nOnlyInt;
	req.chOperate = MsgSuitChangeReq::ECD_SkillSuitChange;
	// 材料
	for (int i = 0; i < 2; ++i)
	{
		req.xItemInfo[i].chItemBagType = m_bagTypeMateral[i];
		req.xItemInfo[i].stItemIndex = m_materialBagIndex[i];
		req.xItemInfo[i].nItemGuid = m_material[i].itembaseinfo.nOnlyInt;
	}
	GettheNetworkInput().SendMsg( &req );

	m_pID_BUTTON_Sure->SetEnable(false);
	m_pID_BUTTON_Cancel->SetEnable(false);

	ShowControls(false);

	m_slideAnim.StartAnimation(HQ_TimeGetTime());

	m_hasAck = false;
	m_isStart = true;
}

void CUI_ID_FRAME_SkillEquipChange::OnAck(MsgSuitChangeAck* pAck)
{
	if( !m_pID_FRAME_SkillEquipChange )
		return;
	switch (pAck->uchResult)
	{
	case MsgSuitChangeAck::ECD_SuccessChagneSkillSuit:
		{
			if (GetEquipItem())
			{
				GetEquipItem()->itembaseinfo.ustItemID = pAck->nValue;
				m_equip.itembaseinfo.ustItemID = pAck->nValue;
			}
		}
		break;
	case MsgSuitChangeAck::ECD_ChangeFailed:
		s_CUI_ID_FRAME_PACK.ChangeMoney(pAck->nLeftMoney);
		break;
    case MsgSuitChangeAck::ECD_SuccessChagneElementSuit:
        break;
	default:
		{

		}
		break;
	}

	m_result = pAck->uchResult;
	m_hasAck = true;

	if (!m_slideAnim.IsInAnimation()) // 火焰停止了
	{
		ShowResult();
	}
}

void CUI_ID_FRAME_SkillEquipChange::ShowResult()
{
	if (m_hasAck)
	{
		ClearMaterial0();
		ClearMaterial1();
		RefreshBagIconEnable();

		m_pID_TEXT_ChangeInfo->SetVisable(true);
		m_pID_PICTURE_ItemWall->SetVisable(true);
		m_pID_BUTTON_Reset->SetVisable(true);

		if (m_result == MsgSuitChangeAck::ECD_SuccessChagneSkillSuit)
		{

			ControlIconDrag::S_ListImg* pSrc = s_CUI_ID_FRAME_PACK.GetItemByIndex( BT_NormalItemBag, m_equipBagIndex );
			if (pSrc)
			{
				ControlIconDrag::S_ListImg item = *pSrc;
				item.m_eEnable = eIcon_Enable;
				m_pID_LISTIMG_Armour->SetItem(&item, 0);
			}

			ItemDefine::SItemArmour* pArmour = (ItemDefine::SItemArmour*)GettheItemDetail().GetItemByID( m_equip.itembaseinfo.ustItemID );
			if (pArmour)
			{
				char szBuf[256];
				MeSprintf_s(szBuf,sizeof(szBuf)/sizeof(char) - 1, theXmlString.GetString(4818), pArmour->GetItemName());
				m_pID_TEXT_ChangeInfo->SetText(szBuf);
			}
		}
		else
		{
			m_pID_TEXT_ChangeInfo->SetText(theXmlString.GetString(eClient_SkillSuitChangeFailed));
		}
	}

	m_isStart = false;
	m_slideAnim.UnRelativePicResource();
}

bool CUI_ID_FRAME_SkillEquipChange::IsActived()
{
	// 当前状态不能放入东西
	if (!m_pID_LISTIMG_Material1->IsVisable())
		return false;
	return true;
}

void CUI_ID_FRAME_SkillEquipChange::ShowControls(bool bInitializeStatus)
{
	m_pID_LISTIMG_Material1->SetVisable(bInitializeStatus);
	m_pID_LISTIMG_Material2->SetVisable(bInitializeStatus);
	m_pID_PICTURE_ItemWall1->SetVisable(bInitializeStatus);
	m_pID_PICTURE_ItemWall2->SetVisable(bInitializeStatus);
	if (bInitializeStatus)
	{
		m_pID_TEXT_ChangeInfo->SetVisable(false);
		m_pID_PICTURE_ItemWall->SetVisable(false);
		m_pID_BUTTON_Reset->SetVisable(false);
	}
}