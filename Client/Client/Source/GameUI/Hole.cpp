/********************************************************************
Created by UIEditor.exe
FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\Hole.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Hole.h"
#include "Common.h"
#include "IconManagerClient.h"
#include "GlobalDef.h"
#include "Pack.h"
#include "ScreenInfoManager.h"
#include "XmlStringLanguage.h"
#include "color_config.h"
#include "Cfg.h"
#include "EquipEvolveConfig.h"
#include "PlayerRole.h"
#include "SoundConfig.h"
#include "PackItemEnableManager.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"

#define DELAY_TIME 350
extern CHeroGame	theHeroGame;

extern int PlayEffect( const char* pEffectName, CPlayer* pSrcPlayer = NULL, float fScale = 0 , DWORD dwFlyTime = 0, CPlayer* pDestPlayer = NULL, int nSlot = 0 ,bool bCalDist = true);
CUI_ID_FRAME_Hole s_CUI_ID_FRAME_Hole;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Hole, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Hole, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Hole, ID_BUTTON_CLOSEOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Hole, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Hole, ID_BUTTON_OkOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_Hole1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_Hole1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_Hole1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_Hole1OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_Hole2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_Hole2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_Hole2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_Hole2OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_Hole3OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_Hole3OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_Hole3OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_Hole3OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_Hole4OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_Hole4OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_Hole4OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_Hole4OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_ArmourOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_ArmourOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Hole, ID_LISTIMG_ArmourOnIconRButtonUp )
CUI_ID_FRAME_Hole::CUI_ID_FRAME_Hole()
{
	// Member
	m_pID_FRAME_EquipEvolve = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_TEXT_HoleTip = NULL;
	m_pID_TEXT_HoleNumber = NULL;
	m_pID_PICTURE_StarEffect = NULL;
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
	m_pID_TEXT_Effect = NULL;
	m_pID_TEXT_Success = NULL;
	m_pID_TEXT_Fail = NULL;
	m_pID_TEXT_EquipName = NULL;
	m_pID_TEXT_MaterialName = NULL;

	m_status = EffectStatus_No;
	dwBeginTime = 0;
	m_bSendMsg = false;
	//m_pUiEffect = NULL;
}
CUI_ID_FRAME_Hole::~CUI_ID_FRAME_Hole()
{
	//delete m_pUiEffect;
	//m_pUiEffect = NULL;
}
// Frame
bool CUI_ID_FRAME_Hole::OnFrameRun()
{
	//
	bool bDirty = OnDirty();
	if (bDirty)
		RefreshOkButton();
	//bool bTempEnable = m_pID_BUTTON_Ok->IsEnable();
	DWORD timenow = timeGetTime();
	switch (m_status)
	{
	case EffectStatus_Start:
		if (timenow-dwBeginTime>=DELAY_TIME && m_bSendMsg )
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
bool CUI_ID_FRAME_Hole::OnFrameRender()
{
	//m_pUiEffect->Render();
	OnRender();
	return true;
}
// Button
bool CUI_ID_FRAME_Hole::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Hole::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														ControlIconDrag::S_ListImg* pItemDrag,
														ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_Hole::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hole::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hole::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// Button
bool CUI_ID_FRAME_Hole::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_Hole::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	//m_pUiEffect->SetStartTime(timeGetTime());
	//m_pID_BUTTON_Ok->SetEnable(false);
	//m_pUiEffect->SetStatus(UiEffectBase::EffectStatus_Start);
	if (!m_pID_FRAME_EquipEvolve)
		return false;
	if (-1 == m_nSelectMaterialIndex)
	{
		return false;
	}
	dwBeginTime = timeGetTime();
	m_status = EffectStatus_Start;
	m_bSendMsg = true;
	m_pID_BUTTON_Ok->SetEnable(false);
	/*OnOkClick();*/
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Hole::ID_LISTIMG_Hole1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													 ControlIconDrag::S_ListImg* pItemDrag,
													 ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_Hole::ID_LISTIMG_Hole1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hole::ID_LISTIMG_Hole1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hole::ID_LISTIMG_Hole1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Hole::ID_LISTIMG_Hole2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													 ControlIconDrag::S_ListImg* pItemDrag,
													 ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_Hole::ID_LISTIMG_Hole2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hole::ID_LISTIMG_Hole2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hole::ID_LISTIMG_Hole2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Hole::ID_LISTIMG_Hole3OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													 ControlIconDrag::S_ListImg* pItemDrag,
													 ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_Hole::ID_LISTIMG_Hole3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hole::ID_LISTIMG_Hole3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hole::ID_LISTIMG_Hole3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Hole::ID_LISTIMG_Hole4OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													 ControlIconDrag::S_ListImg* pItemDrag,
													 ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_Hole::ID_LISTIMG_Hole4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hole::ID_LISTIMG_Hole4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hole::ID_LISTIMG_Hole4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Hole::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
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
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString(eText_Hole_OtherItem) );
		return false;
	}
	if ( pItemCommon->ucItemType != ItemDefine::ITEMTYPE_WEAPON &&
		pItemCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString(eText_Hole_OtherItem) );
		return false;
	}

	int nLevel = GetItemLevel(pItemDrag->m_pkIconInfo->GetItemId());
	if(nLevel < gCfg.m_nMinHoleLevel)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString(eText_Hole_ItemLevel) );
		return false;
	}

	if (_IsFullHole(pItemDrag))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString(eWarning_Hole_Full) );
		return false;
	}
	OnEquipDragOn(pItemDrag,pSender);
	/*SCharItem* pItem = ((SCharItem*)pItemDrag->m_pkIconInfo->GetData());
	if (pItem != NULL)
	{
		int nHole = pItem->equipdata.gemHoleCount;
		EquipEvolveConfig::SEquipStiletto *pStiletto = theEquipEvolveConfig.GetStiletto(nHole+1);
		if (pStiletto != NULL)
		{
			std::string temp;
			thePlayerRole.GetGSCStringFromMoney(pStiletto->nCostValue,temp);
			m_pID_TEXT_Money->SetText(temp.c_str());
		}
	}*/
	RefreshNeedMoney();
	RefreshOkButton();
	ShowItemName(m_pID_TEXT_EquipName, pItemDrag);

	return false;
}
bool CUI_ID_FRAME_Hole::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hole::ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hole::ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	ClearEquip();
	s_CUI_ID_FRAME_Hole.RefreshAllBagEnable();
	return false;
}

// 装载UI
bool CUI_ID_FRAME_Hole::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Hole.MEUI" , false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Hole.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Hole::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Hole, s_CUI_ID_FRAME_HoleOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Hole, s_CUI_ID_FRAME_HoleOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Hole, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_HoleID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Hole, ID_LISTIMG_Material, s_CUI_ID_FRAME_HoleID_LISTIMG_MaterialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Hole, ID_LISTIMG_Material, s_CUI_ID_FRAME_HoleID_LISTIMG_MaterialOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Hole, ID_LISTIMG_Material, s_CUI_ID_FRAME_HoleID_LISTIMG_MaterialOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Hole, ID_LISTIMG_Material, s_CUI_ID_FRAME_HoleID_LISTIMG_MaterialOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_Hole, ID_BUTTON_Cancel, s_CUI_ID_FRAME_HoleID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Hole, ID_BUTTON_Ok, s_CUI_ID_FRAME_HoleID_BUTTON_OkOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Hole, ID_LISTIMG_Hole1, s_CUI_ID_FRAME_HoleID_LISTIMG_Hole1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Hole, ID_LISTIMG_Hole1, s_CUI_ID_FRAME_HoleID_LISTIMG_Hole1OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Hole, ID_LISTIMG_Hole1, s_CUI_ID_FRAME_HoleID_LISTIMG_Hole1OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Hole, ID_LISTIMG_Hole1, s_CUI_ID_FRAME_HoleID_LISTIMG_Hole1OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Hole, ID_LISTIMG_Hole2, s_CUI_ID_FRAME_HoleID_LISTIMG_Hole2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Hole, ID_LISTIMG_Hole2, s_CUI_ID_FRAME_HoleID_LISTIMG_Hole2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Hole, ID_LISTIMG_Hole2, s_CUI_ID_FRAME_HoleID_LISTIMG_Hole2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Hole, ID_LISTIMG_Hole2, s_CUI_ID_FRAME_HoleID_LISTIMG_Hole2OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Hole, ID_LISTIMG_Hole3, s_CUI_ID_FRAME_HoleID_LISTIMG_Hole3OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Hole, ID_LISTIMG_Hole3, s_CUI_ID_FRAME_HoleID_LISTIMG_Hole3OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Hole, ID_LISTIMG_Hole3, s_CUI_ID_FRAME_HoleID_LISTIMG_Hole3OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Hole, ID_LISTIMG_Hole3, s_CUI_ID_FRAME_HoleID_LISTIMG_Hole3OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Hole, ID_LISTIMG_Hole4, s_CUI_ID_FRAME_HoleID_LISTIMG_Hole4OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Hole, ID_LISTIMG_Hole4, s_CUI_ID_FRAME_HoleID_LISTIMG_Hole4OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Hole, ID_LISTIMG_Hole4, s_CUI_ID_FRAME_HoleID_LISTIMG_Hole4OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Hole, ID_LISTIMG_Hole4, s_CUI_ID_FRAME_HoleID_LISTIMG_Hole4OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Hole, ID_LISTIMG_Armour, s_CUI_ID_FRAME_HoleID_LISTIMG_ArmourOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Hole, ID_LISTIMG_Armour, s_CUI_ID_FRAME_HoleID_LISTIMG_ArmourOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Hole, ID_LISTIMG_Armour, s_CUI_ID_FRAME_HoleID_LISTIMG_ArmourOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Hole, ID_LISTIMG_Armour, s_CUI_ID_FRAME_HoleID_LISTIMG_ArmourOnIconRButtonUp );

	m_pID_FRAME_EquipEvolve = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Hole );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Hole, ID_BUTTON_CLOSE );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_Hole, ID_TEXT_Money );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Hole, ID_LISTIMG_Material );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_Hole, ID_BUTTON_Cancel );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_Hole, ID_BUTTON_Ok );
	m_pID_TEXT_HoleTip = (ControlText*)theUiManager.FindControl( ID_FRAME_Hole, ID_TEXT_HoleTip );
	m_pID_TEXT_HoleNumber = (ControlText*)theUiManager.FindControl( ID_FRAME_Hole, ID_TEXT_HoleNumber );
	m_pID_PICTURE_StarEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Hole, ID_PICTURE_StarEffect );
	m_pID_PICTURE_Open1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Hole, ID_PICTURE_Open1 );
	m_pID_PICTURE_Open2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Hole, ID_PICTURE_Open2 );
	m_pID_PICTURE_Open3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Hole, ID_PICTURE_Open3 );
	m_pID_PICTURE_Open4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Hole, ID_PICTURE_Open4 );
	m_pID_LISTIMG_Hole1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Hole, ID_LISTIMG_Hole1 );
	m_pID_LISTIMG_Hole2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Hole, ID_LISTIMG_Hole2 );
	m_pID_LISTIMG_Hole3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Hole, ID_LISTIMG_Hole3 );
	m_pID_LISTIMG_Hole4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Hole, ID_LISTIMG_Hole4 );
	m_pID_PICTURE_Lock1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Hole, ID_PICTURE_Lock1 );
	m_pID_PICTURE_Lock2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Hole, ID_PICTURE_Lock2 );
	m_pID_PICTURE_Lock3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Hole, ID_PICTURE_Lock3 );
	m_pID_PICTURE_Lock4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Hole, ID_PICTURE_Lock4 );
	m_pID_PICTURE_Begin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Hole, ID_PICTURE_Begin );
	m_pID_LISTIMG_Equip = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Hole, ID_LISTIMG_Armour );
	m_pID_TEXT_TipAllDone = (ControlText*)theUiManager.FindControl( ID_FRAME_Hole, ID_TEXT_TipAllDone );
	m_pID_TEXT_SuccessRatio = (ControlText*)theUiManager.FindControl(ID_FRAME_Hole, ID_TEXT_SuccessRatio );
	m_pID_TEXT_Effect = (ControlText*)theUiManager.FindControl(ID_FRAME_Hole, ID_TEXT_Effect );
	m_pID_TEXT_Success = (ControlText*)theUiManager.FindControl(ID_FRAME_Hole, ID_TEXT_Success );
	m_pID_TEXT_Fail = (ControlText*)theUiManager.FindControl(ID_FRAME_Hole, ID_TEXT_Fail );
	m_pID_TEXT_EquipName = (ControlText*)theUiManager.FindControl( ID_FRAME_Hole, ID_TEXT_EquipName );
	m_pID_TEXT_MaterialName = (ControlText*)theUiManager.FindControl( ID_FRAME_Hole, ID_TEXT_MaterialName );
	/*m_pUiEffect = new UiEffectBase;
	if (m_pUiEffect)
	{
		m_pUiEffect->DoControlConnect(ID_FRAME_Hole);
		m_pUiEffect->SetStatus(UiEffectBase::EffectStatus_No);
	}*/
	assert( m_pID_FRAME_EquipEvolve );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_Money );
	assert( m_pID_LISTIMG_Material );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_TEXT_HoleTip );
	assert( m_pID_TEXT_HoleNumber );
	assert( m_pID_PICTURE_StarEffect );
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
	assert( m_pID_TEXT_SuccessRatio );
	assert( m_pID_TEXT_EquipName );
	assert( m_pID_TEXT_MaterialName );
	InitializeGemBase();
	m_pID_FRAME_EquipEvolve->SetOnVisibleChangedFun( OnVisibleChange );
	m_pID_TEXT_HoleTip->SetVisable(false);
	m_pID_TEXT_TipAllDone->SetVisable(false);
	m_pID_TEXT_EquipName->SetText("");
	m_pID_TEXT_MaterialName->SetText("");
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Hole::_UnLoadUI()
{
	ResetEquipEvolve();
	m_pID_FRAME_EquipEvolve = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\Hole.MEUI" );
}

void CUI_ID_FRAME_Hole::TipVisible( bool IsMaterialExist )
{
	if (IsMaterialExist)
	{
		m_pID_TEXT_HoleTip->SetVisable(false);
	}
	else
	{
		m_pID_TEXT_HoleTip->SetVisable(true);
	}

}

void CUI_ID_FRAME_Hole::_SetVisable(const bool bVisable)
{
	if (bVisable)
	{
		OnDirty();
	}
	OnSetVisable(bVisable);
	m_pID_BUTTON_Ok->SetEnable(false);
	m_pID_TEXT_HoleTip->SetVisable(false);
	m_pID_TEXT_TipAllDone->SetVisable(false);
}

void CUI_ID_FRAME_Hole::OnVisibleChange( ControlObject* pUIObject )
{
	s_CUI_ID_FRAME_Hole.m_status = EffectStatus_No;
	s_CUI_ID_FRAME_Hole.SetDirty( true );
	s_CUI_ID_FRAME_Hole.ClearEquip();	
	s_CUI_ID_FRAME_Hole.RefreshAllBagEnable();
	s_CUI_ID_FRAME_Hole.OnDirty();
}


void CUI_ID_FRAME_Hole::ClearEquip()
{
	GemBaseUI::ClearEquip();
	m_pID_TEXT_HoleNumber->Clear();
	for (int i = 0;i < m_nMaxHoleNum;++i)
	{
		m_UnHolePic[i]->SetVisable(true);
		m_HoledPic[i]->SetVisable(false);
	}
	m_pID_TEXT_SuccessRatio->SetVisable(false);
	m_pID_TEXT_HoleTip->SetVisable(false);
	m_pID_TEXT_TipAllDone->SetVisable(false);
	m_pID_TEXT_EquipName->SetText("");
	m_pID_TEXT_MaterialName->SetText("");
}

void CUI_ID_FRAME_Hole::_RefreshEquipInfo( ControlIconDrag::S_ListImg* pListImg )
{
	if( !m_pID_FRAME_EquipEvolve )
		return;
	GemBaseUI::_RefreshEquipInfo(pListImg);

	SCharItem* pItem = ((SCharItem*)pListImg->m_pkIconInfo->GetData());
	if (NULL == pItem)
	{
		return;
	}
	int nHole = pItem->equipdata.gemHoleCount;
	char cTemp[256];
	MeSprintf_s(cTemp,256,"%d/%d",nHole,m_nMaxHoleNum);
	m_pID_TEXT_HoleNumber->SetText(cTemp);

	RefreshSuccessRatio(nHole + 1);
	RefreshNeedMoney();
}

bool CUI_ID_FRAME_Hole::IsEvolveAllDone(ControlIconDrag::S_ListImg * pImg)
{
	return _IsFullHole(pImg);
}

bool CUI_ID_FRAME_Hole::IsMatchOther(ItemDefine::SCreateMaterial* pMaterial)
{
	if (m_stEquipBagIndex == -1)
	{
		return false;
	}

	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Equip->GetItemByIndex( 0 );
	SCharItem* pItem = ((SCharItem*)pImg->m_pkIconInfo->GetData());
	if (NULL == pItem)
	{
		return false;
	}
	int nHole = pItem->equipdata.gemHoleCount;
	if (pMaterial->nValue >= nHole + 1)
	{
		return true;
	}
	return false;
}

bool CUI_ID_FRAME_Hole::ProcessAllDone( ControlIconDrag::S_ListImg * pImg )
{
	bool bRet = GemBaseUI::ProcessAllDone(pImg);
	if (bRet)
	{
		m_pID_TEXT_HoleTip->SetVisable(false);
	}
	return bRet;
}

void CUI_ID_FRAME_Hole::RefreshSuccessRatio(int holeIndex_)
{
	float ratio = 0.0f;
	EquipEvolveConfig::SEquipStiletto *pStiletto = theEquipEvolveConfig.GetStiletto(holeIndex_);

	if(pStiletto != NULL)
	{
		ratio = (float)(pStiletto->nSuccessRate / 100);
	}

	if(m_pID_TEXT_SuccessRatio != NULL)
	{
		if(ratio > 100.0f)
			ratio = 100.0f;

		char buf[8];
		sprintf(buf, "%d%%", (int)ratio);
		m_pID_TEXT_SuccessRatio->SetText(buf);
		m_pID_TEXT_SuccessRatio->SetVisable(true);
	}
}

void CUI_ID_FRAME_Hole::RefreshMoney()
{
	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Equip->GetItemByIndex( 0 );
	if (pImg != NULL)
	{
		SCharItem* pItem = ((SCharItem*)pImg->m_pkIconInfo->GetData());
		if (pItem != NULL)
		{
			int nHole = pItem->equipdata.gemHoleCount;
			EquipEvolveConfig::SEquipStiletto *pStiletto = theEquipEvolveConfig.GetStiletto(nHole+1);
			if (pStiletto != NULL)
			{
				std::string temp;
				thePlayerRole.GetGSCStringFromJiaoZi(pStiletto->nCostValue,temp);
				m_pID_TEXT_Money->SetText(temp.c_str());
			}
		}
	}	
}

void CUI_ID_FRAME_Hole::RefreshOkButton()
{
	EquipEvolveUI::RefreshOkButton();

	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	if(!pImg || pImg->IsNull())
	{
		m_pID_BUTTON_Ok->SetEnable( false );
		return;
	}
	SCharItem* pItem = ((SCharItem*)pImg->m_pkIconInfo->GetData());
	if (!pItem)
	{
		m_pID_BUTTON_Ok->SetEnable( false );
		return;
	}
	int nHole = pItem->equipdata.gemHoleCount;
	if (nHole >= m_nMaxHoleNum)
	{
		m_pID_TEXT_Money->SetText("");
		m_pID_TEXT_SuccessRatio->SetText("");
		m_pID_BUTTON_Ok->SetEnable( false );
		return;
	}

	EquipEvolveConfig::SEquipStiletto *pStiletto = theEquipEvolveConfig.GetStiletto(nHole+1);
	if (pStiletto)
	{
		if(!thePlayerRole.HaveEnoughMoney(pStiletto->nCostValue))
		{
			m_pID_BUTTON_Ok->SetEnable(false);
			return;
		}
	}

	if( m_nSelectMaterialIndex == -1 )
	{
		m_pID_BUTTON_Ok->SetEnable( false );
		return;
	}

	m_pID_BUTTON_Ok->SetEnable( true );
}

//lyh 重载 之前的已经乱了
bool CUI_ID_FRAME_Hole::UpdateGem()
{

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
	bool isHaveMat = false;
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
					m_pSelectItem = pNewImg;
					m_nSelectMaterialIndex = nMatchMaterialCount;
					m_bMaterialBagEnable[nMatchMaterialCount] = false;
					//++nMatchMaterialEnableCount;
				}

				isHaveMat = true;
				break; //找到了直接跳出，防止往后再找到没有的 那就错了
			}			
			//++nMatchMaterialCount;
			//if (nMatchMaterialCount >= m_nsMaxMaterialNum)
			//{
			//	break;
			//}
		}
	}

      if (!isHaveMat) //没有找到 则默认第一个可用材料为选择材料，并且显示灰色
      {
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
					  break;
				  }
			  }
		  }
		
      }



	if (nLastItemId != -1)
	{
		for (int i = 0; i <m_nsMaxMaterialNum; ++i)
		{
			if (m_stMaterialIndex[i] == nLastItemId)
			{
				m_pSelectItem = m_pID_LISTIMG_Material->GetItemByIndex( i );
				m_nSelectMaterialIndex = i;
			}
		}
	}

	TipVisible(isHaveMat);

	RefreshNeedMoney();
	RefreshProbability();
	SetDirty( true );

	ControlIconDrag::S_ListImg* pItemDrag = m_pID_LISTIMG_Material->GetItemByIndex(0);
	if (pItemDrag && !pItemDrag->IsNull())
		ShowItemName(m_pID_TEXT_MaterialName, pItemDrag);

	return true;
}

void CUI_ID_FRAME_Hole::RefreshNeedMoney()
{
	ControlIconDrag::S_ListImg* pItemDrag = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	if (!pItemDrag || pItemDrag->IsNull())
		return;
	SCharItem* pItem = ((SCharItem*)pItemDrag->m_pkIconInfo->GetData());
	if (pItem != NULL)
	{
		int nHole = pItem->equipdata.gemHoleCount;
		EquipEvolveConfig::SEquipStiletto *pStiletto = theEquipEvolveConfig.GetStiletto(nHole+1);
		if (pStiletto != NULL)
		{
			std::string temp;
			thePlayerRole.GetGSCStringFromJiaoZi(pStiletto->nCostValue,temp);
			m_pID_TEXT_Money->SetText(temp.c_str());

			if(!thePlayerRole.HaveEnoughMoney(pStiletto->nCostValue))
			{
				s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_StarLEvolveNoMomeny), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true);
			}
		}
	}
}

void CUI_ID_FRAME_Hole::ShowItemName(ControlText* pText, ControlIconDrag::S_ListImg* pItemDrag)
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