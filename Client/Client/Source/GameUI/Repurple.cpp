/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\Repurple.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Repurple.h"
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

CUI_ID_FRAME_Repurple s_CUI_ID_FRAME_Repurple;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Repurple, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Repurple, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Repurple, ID_BUTTON_CLOSEOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Repurple, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Repurple, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Repurple, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Repurple, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Repurple, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Repurple, ID_BUTTON_OkOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Repurple, ID_LISTIMG_EquipOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Repurple, ID_LISTIMG_EquipOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Repurple, ID_LISTIMG_EquipOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Repurple, ID_LISTIMG_EquipOnIconRButtonUp )
CUI_ID_FRAME_Repurple::CUI_ID_FRAME_Repurple()
{
	// Member
	m_pID_FRAME_EquipEvolve = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_TEXT_EquipName = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_TEXT_Tip = NULL;
	m_pID_PICTURE_Begin = NULL;
	m_pID_LISTIMG_Equip = NULL;
	m_pID_PICTURE_StarEffect = NULL;
	ResetUIObjects();

}
	// Frame
	bool CUI_ID_FRAME_Repurple::OnFrameRun()
	{
		if (!OnDirty())
		{
			return true;
		}
		return true;
	}
	bool CUI_ID_FRAME_Repurple::OnFrameRender()
	{
		OnRender();
		return true;
	}
	// Button
	bool CUI_ID_FRAME_Repurple::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
	{
		SetVisable( false );
		return true;
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_Repurple::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		return false;
	}
	bool CUI_ID_FRAME_Repurple::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_Repurple::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_Repurple::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	// Button
	bool CUI_ID_FRAME_Repurple::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
	{
		SetVisable( false );
		return true;
	}
	// Button
	bool CUI_ID_FRAME_Repurple::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
	{
		OnOkClick();
		return true;
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_Repurple::ID_LISTIMG_EquipOnIconDragOn( ControlObject* pSender, ControlObject* pObject,
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
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
		if (!pMe)
		{
			return false;
		}
		if (pMe->GetLevel() < gCfg.m_nMinOpenLightPlayerLevel)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseGold_Failed, theXmlString.GetString(eWarning_OpenLight_PlayerLowTo60) );
			return false;
		}
		int nLevel = GetItemLevel(pItemDrag->m_pkIconInfo->GetItemId());
		if(nLevel < gCfg.m_nMinOpenLightItemLevel)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseGold_Failed, theXmlString.GetString(eWarning_OpenLight_ItemLowTo60) );
			return false;
		}
		if (!IsOpenLighted(psItem))
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseGold_Failed, theXmlString.GetString(eWarning_ReOpenLight_NoPurple) );
			return false;
		}
		OnEquipDragOn(pItemDrag,pSender);
		return false;
	}
	bool CUI_ID_FRAME_Repurple::ID_LISTIMG_EquipOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_Repurple::ID_LISTIMG_EquipOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_Repurple::ID_LISTIMG_EquipOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		ClearEquip();
		return false;
	}

	// 装载UI
bool CUI_ID_FRAME_Repurple::_LoadUI()
	{
		DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Repurple.MEUI"  , false, UI_Render_LayerThree );
		if ( dwResult == 0 )
		{
			MESSAGE_BOX("读取文件[Data\\UI\\Repurple.MEUI]失败")
			return false;
		}
		return DoControlConnect();
	}
	// 关连控件
	bool CUI_ID_FRAME_Repurple::DoControlConnect()
	{
		theUiManager.OnFrameRun( ID_FRAME_Repurple, s_CUI_ID_FRAME_RepurpleOnFrameRun );
		theUiManager.OnFrameRender( ID_FRAME_Repurple, s_CUI_ID_FRAME_RepurpleOnFrameRender );
theUiManager.OnButtonClick( ID_FRAME_Repurple, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_RepurpleID_BUTTON_CLOSEOnButtonClick );
theUiManager.OnIconDragOn( ID_FRAME_Repurple, ID_LISTIMG_Material, s_CUI_ID_FRAME_RepurpleID_LISTIMG_MaterialOnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_Repurple, ID_LISTIMG_Material, s_CUI_ID_FRAME_RepurpleID_LISTIMG_MaterialOnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_Repurple, ID_LISTIMG_Material, s_CUI_ID_FRAME_RepurpleID_LISTIMG_MaterialOnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_Repurple, ID_LISTIMG_Material, s_CUI_ID_FRAME_RepurpleID_LISTIMG_MaterialOnIconRButtonUp );
theUiManager.OnButtonClick( ID_FRAME_Repurple, ID_BUTTON_Cancel, s_CUI_ID_FRAME_RepurpleID_BUTTON_CancelOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_Repurple, ID_BUTTON_Ok, s_CUI_ID_FRAME_RepurpleID_BUTTON_OkOnButtonClick );
theUiManager.OnIconDragOn( ID_FRAME_Repurple, ID_LISTIMG_Equip, s_CUI_ID_FRAME_RepurpleID_LISTIMG_EquipOnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_Repurple, ID_LISTIMG_Equip, s_CUI_ID_FRAME_RepurpleID_LISTIMG_EquipOnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_Repurple, ID_LISTIMG_Equip, s_CUI_ID_FRAME_RepurpleID_LISTIMG_EquipOnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_Repurple, ID_LISTIMG_Equip, s_CUI_ID_FRAME_RepurpleID_LISTIMG_EquipOnIconRButtonUp );

		m_pID_FRAME_EquipEvolve = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Repurple );
		m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Repurple, ID_BUTTON_CLOSE );
		m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_Repurple, ID_TEXT_Money );
		m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Repurple, ID_LISTIMG_Material );
		m_pID_TEXT_EquipName = (ControlText*)theUiManager.FindControl( ID_FRAME_Repurple, ID_TEXT_EquipName );
		m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_Repurple, ID_BUTTON_Cancel );
		m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_Repurple, ID_BUTTON_Ok );
		m_pID_TEXT_Tip = (ControlText*)theUiManager.FindControl( ID_FRAME_Repurple, ID_TEXT_Tip );
		m_pID_LIST_Attribute = (ControlList*)theUiManager.FindControl( ID_FRAME_Repurple, ID_LIST_Attribute );
		m_pID_PICTURE_Begin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Repurple, ID_PICTURE_Begin );
		m_pID_LISTIMG_Equip = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Repurple, ID_LISTIMG_Equip );
		m_pID_PICTURE_StarEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Repurple, ID_PICTURE_StarEffect );
		assert( m_pID_FRAME_EquipEvolve );
		assert( m_pID_BUTTON_CLOSE );
		assert( m_pID_TEXT_Money );
		assert( m_pID_LISTIMG_Material );
		assert( m_pID_TEXT_EquipName );
		assert( m_pID_BUTTON_Cancel );
		assert( m_pID_BUTTON_Ok );
		assert( m_pID_TEXT_Tip );
		assert( m_pID_PICTURE_Begin );
		assert( m_pID_LISTIMG_Equip );
		assert( m_pID_PICTURE_StarEffect );
		m_pID_FRAME_EquipEvolve->SetOnVisibleChangedFun( OnVisibleChange );
		m_pID_LIST_Attribute->HaveSelBar( 0, 0 );	
		EquipEvolveIntialize();
		return true;
	}
	// 卸载UI
bool CUI_ID_FRAME_Repurple::_UnLoadUI()
	{
		ResetEquipEvolve();
		m_pID_FRAME_EquipEvolve = NULL;
		return theUiManager.RemoveFrame( "Data\\UI\\Repurple.MEUI" );
	}
void CUI_ID_FRAME_Repurple::UpdateArmourInfo( SCharItem* pItem)
{
	if( !m_pID_FRAME_EquipEvolve )
		return;
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
	if( !pItemCommon )
		return;
	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if( !pCanEquip )
		return;

	bool bSouled = IsOpenLighted(pItem);
	// 名字
	Common::_tstring tstrName( pItemCommon->GetItemName() );
	S_IconInfoHero::ReplaceSpecifiedName( pItemCommon->ustLevel, tstrName );
	char szBuf[256] = {0};
	MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char)-1, "%s", tstrName.c_str() );
	m_pID_TEXT_EquipName->SetText(szBuf,S_IconInfoHero::GetQualityColor( pItem->equipdata.quality ));
	m_pID_LIST_Attribute->Clear();

	for( int nloop = 0; nloop < SCharItem::EConstDefine_PurpleRandMaxCount; ++nloop )
	{
		ItemDefine::SRandAttribute* pArmourRand = NULL;
		unsigned short usRand = pItem->equipdata.purpleRands[nloop];
		if( nloop >= pCanEquip->purpleRandCount || usRand == InvalidLogicNumber ) //随机个数以内
			continue;

		pArmourRand = GettheItemDetail().GetRandByID( pItem->equipdata.purpleRands[nloop] );
		if ( !pArmourRand )
			continue;

		for( int i = 0 ; i < ItemDefine::SRandAttribute::CD_TypeCount ; ++ i )
		{
			int nRandValue = S_IconInfoHero::GetRandValueByType( pArmourRand, i );
			if( pArmourRand->type[i] == RT_None )
				continue;

			char szTemp[256] = {0};
			char szMiddle[256] = {0};
            if( pArmourRand->type[i] == RT_AddMoveSpeed )
            {
                sprintf( szTemp, "%s+%.2f", S_IconInfoHero::GetRandStringByType( pArmourRand->type[i] ).c_str(), ( float )nRandValue / 100.0f );
            }
            else
            {
				// 对同一buff使用拷贝危险 [11/18/2010 zhangjiayi]
                sprintf( szMiddle, "%s+%d", S_IconInfoHero::GetRandStringByType( pArmourRand->type[i] ).c_str(), nRandValue );
                if( pArmourRand->type[i] == RT_AddExpPer )
                    sprintf( szTemp, "%s%s", szMiddle, "%" );
				else
					strcpy_s( szTemp, 256, szMiddle );
            }
			ControlList::S_List listItem;
			listItem.SetData(szTemp,0,NULL,S_IconInfoHero::GetQualityColor( ItemDefine::EQL_Purple ));
			listItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
			m_pID_LIST_Attribute->AddItem(&listItem);
		}

	}


}

void CUI_ID_FRAME_Repurple::_RefreshEquipInfo( ControlIconDrag::S_ListImg* pListImg )
{
	if( !m_pID_FRAME_EquipEvolve )
		return;
	EquipEvolveUI::_RefreshEquipInfo(pListImg);

	SCharItem* psItem = (SCharItem*)pListImg->m_pkIconInfo->GetData();
	if (!psItem)
	{
		return;
	}
	UpdateArmourInfo( psItem);
}
void CUI_ID_FRAME_Repurple::OnVisibleChange( ControlObject* pUIObject )
{
	s_CUI_ID_FRAME_Repurple.SetDirty( true );
	s_CUI_ID_FRAME_Repurple.ClearEquip();	
	s_CUI_ID_FRAME_Repurple.RefreshAllBagEnable();
}

void CUI_ID_FRAME_Repurple::ResetUIObjects()
{
	EquipEvolveUI::ResetUIObjects();
	// Member
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_EquipName = NULL;
	m_pID_TEXT_Tip = NULL;

}


void CUI_ID_FRAME_Repurple::TipVisible( bool IsMaterialExist )
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


bool CUI_ID_FRAME_Repurple::IsEvolveAllDone(ControlIconDrag::S_ListImg * pImg)
{
	SCharItem* psItem = (SCharItem*)pImg->m_pkIconInfo->GetData();
	if (!psItem)
	{
		return true;
	}
	return (IsOpenLighted(psItem));

}

bool CUI_ID_FRAME_Repurple::ProcessAllDone( ControlIconDrag::S_ListImg * pImg )
{
	return false;
}

bool CUI_ID_FRAME_Repurple::IsOpenLighted(SCharItem* psItem)
{
	if (!psItem)
	{
		return false;
	}

	bool bIs = false;

	for( int nloop = 0; nloop < SCharItem::EConstDefine_PurpleRandMaxCount; ++nloop )
	{
		unsigned short usRand = psItem->equipdata.purpleRands[nloop];
		if(  usRand != InvalidLogicNumber )
		{
			bIs = true;
			break;
		}
	}

	return bIs;
	//return psItem->equipdata.quality > ItemDefine::EQL_Golden;
}

void CUI_ID_FRAME_Repurple::ClearEquip()
{
	EquipEvolveUI::ClearEquip();

	if ( m_pID_TEXT_EquipName )
		m_pID_TEXT_EquipName->SetText("");
	if ( m_pID_LIST_Attribute )
		m_pID_LIST_Attribute->Clear();
}