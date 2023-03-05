/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\Symbol.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Symbol.h"
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
#include "GameDefinePlayer.h"
#include "IconManagerClient.h"

CUI_ID_FRAME_Symbol s_CUI_ID_FRAME_Symbol;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Symbol, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Symbol, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Symbol, ID_BUTTON_CLOSEOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Symbol, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Symbol, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Symbol, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Symbol, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Symbol, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Symbol, ID_BUTTON_OkOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Symbol, ID_LIST_AttributeOnListSelectChange )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Symbol, ID_LISTIMG_EquipOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Symbol, ID_LISTIMG_EquipOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Symbol, ID_LISTIMG_EquipOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Symbol, ID_LISTIMG_EquipOnIconRButtonUp )
CUI_ID_FRAME_Symbol::CUI_ID_FRAME_Symbol()
{
	// Member
	m_pID_FRAME_EquipEvolve = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Rate = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_TEXT_Tip = NULL;
	m_pID_LIST_Attribute = NULL;
	m_pID_PICTURE_Begin = NULL;
	m_pID_LISTIMG_Equip = NULL;
	m_pID_PICTURE_StarEffect = NULL;

}
	// Frame
	bool CUI_ID_FRAME_Symbol::OnFrameRun()
	{
		if (!OnDirty())
		{
			return true;
		}
		return true;
	}
	bool CUI_ID_FRAME_Symbol::OnFrameRender()
	{
		OnRender();
		return true;
	}
	// Button
	bool CUI_ID_FRAME_Symbol::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
	{
		SetVisable(false);
		return true;
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_Symbol::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		return false;
	}
	bool CUI_ID_FRAME_Symbol::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_Symbol::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		if (!m_pID_FRAME_EquipEvolve)
			return false;
		if (pItem == NULL)
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
		}
		SetSelectItem(pItem);
		UpdateRateText();
		return false;
	}
	bool CUI_ID_FRAME_Symbol::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	// Button
	bool CUI_ID_FRAME_Symbol::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
	{
		SetVisable(false);
		return true;
	}
	// Button
	bool CUI_ID_FRAME_Symbol::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
	{
		OnOkClick();
		return true;
	}
	// List
	void CUI_ID_FRAME_Symbol::ID_LIST_AttributeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
	{
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_Symbol::ID_LISTIMG_EquipOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
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
		if (psItem->equipdata.quality != ItemDefine::EQL_Blue)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Soul_Failed, theXmlString.GetString(eWarning_Charm_BlueItem) );
			return false;
		}

		OnEquipDragOn(pItemDrag,pSender);
		return false;
	}
	bool CUI_ID_FRAME_Symbol::ID_LISTIMG_EquipOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_Symbol::ID_LISTIMG_EquipOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_Symbol::ID_LISTIMG_EquipOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		ClearEquip();
		return false;
	}

	// 装载UI
bool CUI_ID_FRAME_Symbol::_LoadUI()
	{
		DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Symbol.MEUI" , false, UI_Render_LayerThree );
		if ( dwResult == 0 )
		{
			MESSAGE_BOX("读取文件[Data\\UI\\Symbol.MEUI]失败")
			return false;
		}
		return DoControlConnect();
	}
	// 关连控件
	bool CUI_ID_FRAME_Symbol::DoControlConnect()
	{
		theUiManager.OnFrameRun( ID_FRAME_Symbol, s_CUI_ID_FRAME_SymbolOnFrameRun );
		theUiManager.OnFrameRender( ID_FRAME_Symbol, s_CUI_ID_FRAME_SymbolOnFrameRender );
theUiManager.OnButtonClick( ID_FRAME_Symbol, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SymbolID_BUTTON_CLOSEOnButtonClick );
theUiManager.OnIconDragOn( ID_FRAME_Symbol, ID_LISTIMG_Material, s_CUI_ID_FRAME_SymbolID_LISTIMG_MaterialOnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_Symbol, ID_LISTIMG_Material, s_CUI_ID_FRAME_SymbolID_LISTIMG_MaterialOnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_Symbol, ID_LISTIMG_Material, s_CUI_ID_FRAME_SymbolID_LISTIMG_MaterialOnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_Symbol, ID_LISTIMG_Material, s_CUI_ID_FRAME_SymbolID_LISTIMG_MaterialOnIconRButtonUp );
theUiManager.OnButtonClick( ID_FRAME_Symbol, ID_BUTTON_Cancel, s_CUI_ID_FRAME_SymbolID_BUTTON_CancelOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_Symbol, ID_BUTTON_Ok, s_CUI_ID_FRAME_SymbolID_BUTTON_OkOnButtonClick );
theUiManager.OnListSelectChange( ID_FRAME_Symbol, ID_LIST_Attribute, s_CUI_ID_FRAME_SymbolID_LIST_AttributeOnListSelectChange );
theUiManager.OnIconDragOn( ID_FRAME_Symbol, ID_LISTIMG_Equip, s_CUI_ID_FRAME_SymbolID_LISTIMG_EquipOnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_Symbol, ID_LISTIMG_Equip, s_CUI_ID_FRAME_SymbolID_LISTIMG_EquipOnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_Symbol, ID_LISTIMG_Equip, s_CUI_ID_FRAME_SymbolID_LISTIMG_EquipOnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_Symbol, ID_LISTIMG_Equip, s_CUI_ID_FRAME_SymbolID_LISTIMG_EquipOnIconRButtonUp );

		m_pID_FRAME_EquipEvolve = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Symbol );
		m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Symbol, ID_BUTTON_CLOSE );
		m_pID_TEXT_Rate = (ControlText*)theUiManager.FindControl( ID_FRAME_Symbol, ID_TEXT_Rate );
		m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Symbol, ID_LISTIMG_Material );
		m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_Symbol, ID_BUTTON_Cancel );
		m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_Symbol, ID_BUTTON_Ok );
		m_pID_TEXT_Tip = (ControlText*)theUiManager.FindControl( ID_FRAME_Symbol, ID_TEXT_Tip );
		m_pID_LIST_Attribute = (ControlList*)theUiManager.FindControl( ID_FRAME_Symbol, ID_LIST_Attribute );
		m_pID_PICTURE_Begin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Symbol, ID_PICTURE_Begin );
		m_pID_LISTIMG_Equip = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Symbol, ID_LISTIMG_Equip );
		m_pID_PICTURE_StarEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Symbol, ID_PICTURE_StarEffect );
		m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_Symbol, ID_TEXT_Money );
		assert( m_pID_FRAME_EquipEvolve );
		assert( m_pID_BUTTON_CLOSE );
		assert( m_pID_TEXT_Rate );
		assert( m_pID_LISTIMG_Material );
		assert( m_pID_BUTTON_Cancel );
		assert( m_pID_BUTTON_Ok );
		assert( m_pID_TEXT_Tip );
		assert( m_pID_LIST_Attribute );
		assert( m_pID_PICTURE_Begin );
		assert( m_pID_LISTIMG_Equip );
		assert( m_pID_PICTURE_StarEffect );
		assert( m_pID_TEXT_Money );
		m_pID_FRAME_EquipEvolve->SetOnVisibleChangedFun( OnVisibleChange );
		EquipEvolveIntialize();
		m_pID_LIST_Attribute->HaveSelBar( 0, 0 );
		SetDirty(true);
// 		m_pID_TEXT_Money->SetVisable(false);
		return true;
	}
	// 卸载UI
bool CUI_ID_FRAME_Symbol::_UnLoadUI()
	{
		ResetEquipEvolve();
		m_pID_FRAME_EquipEvolve = NULL;
		return theUiManager.RemoveFrame( "Data\\UI\\Symbol.MEUI" );
	}

void CUI_ID_FRAME_Symbol::OnVisibleChange( ControlObject* pUIObject )
{
	s_CUI_ID_FRAME_Symbol.SetDirty( true );
	s_CUI_ID_FRAME_Symbol.ClearEquip();	
	s_CUI_ID_FRAME_Symbol.RefreshAllBagEnable();

}


void CUI_ID_FRAME_Symbol::TipVisible( bool IsMaterialExist )
{
	if (IsMaterialExist)
	{
		m_pID_TEXT_Tip->SetVisable(false);
	}
	else
	{
		m_pID_TEXT_Tip->SetVisable(true);
	}

	return;
}

void CUI_ID_FRAME_Symbol::ClearEquip()
{
	EquipEvolveUI::ClearEquip();
	m_pID_LIST_Attribute->Clear();
	m_pID_TEXT_Rate->Clear();
}

void CUI_ID_FRAME_Symbol::UpdateRateText()
{
	m_pID_TEXT_Rate->Clear();
	if (-1 == m_nSelectMaterialIndex)
	{
		return;
	}
	
	ControlIconDrag::S_ListImg* pItemImg = m_pID_LISTIMG_Material->GetItemByIndex(m_nSelectMaterialIndex);
	if (pItemImg->IsNull())
	{
		return ;
	}
	ItemDefine::SCreateMaterial* pMaterial = ( ItemDefine::SCreateMaterial* )GettheItemDetail().GetItemByID(pItemImg->m_pkIconInfo->GetItemId());
	if (!pMaterial)
	{
		return ;
	}
	int probability = 100;
	SCharItem* pMaterialItem = (SCharItem*)pItemImg->m_pkIconInfo->GetData();
	if(pMaterialItem->equipdata.quality == ItemDefine::EQL_White)
	{
		ControlIconDrag::S_ListImg* pEquipImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
		if (pEquipImg->IsNull())
		{
			return ;
		}
		SCharItem* pEquipItem = (SCharItem*)pEquipImg->m_pkIconInfo->GetData();
		int blueCount = 0;
		for (int i=0;i<SCharItem::EConstDefine_BaseRandMaxCount;++i)
		{
			if (pEquipItem->equipdata.baseRands[i] != InvalidLogicNumber)
			{ ++blueCount; }
		}
		probability = CharmAbsorbProbabilitys[blueCount - 1];
	}
	else 
	{
		assert(pMaterialItem->equipdata.quality == ItemDefine::EQL_Green);
	}
	

	char cTemp[256] = {0};
	sprintf( cTemp, "%d%s", probability, "%" );
	m_pID_TEXT_Rate->SetText(cTemp);
}

bool CUI_ID_FRAME_Symbol::UpdateGem()
{
	if( !m_pID_FRAME_EquipEvolve )
		return false;
	if( !IsVisable() )
		return false;

	SetSelectItem(NULL);
	EquipEvolveUI::UpdateGem();
	SetSelectItem(m_pSelectItem);
	UpdateRateText();
	return true;
}

bool CUI_ID_FRAME_Symbol::MatchMaterialOption( SCharItem* pItem )
{
	if (pItem->equipdata.quality > ItemDefine::EQL_Green)
	{
		return false;
	}
	return true;
}

void CUI_ID_FRAME_Symbol::_RefreshEquipInfo( ControlIconDrag::S_ListImg* pEquipImg )
{
	EquipEvolveUI::_RefreshEquipInfo(pEquipImg);
	FillBlueAttriList(pEquipImg,m_pID_LIST_Attribute);

}

void CUI_ID_FRAME_Symbol::ResetUIObjects()
{
	EquipEvolveUI::ResetUIObjects();
	m_pID_TEXT_Rate = NULL;
	m_pID_LIST_Attribute = NULL;
	m_pID_TEXT_Tip = NULL;
}

