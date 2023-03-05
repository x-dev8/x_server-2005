/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\GemMaterialUp.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GemMaterialUp.h"
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
#include "ItemComposeConfig.h"

CUI_ID_FRAME_GemMaterialUp s_CUI_ID_FRAME_GemMaterialUp;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GemMaterialUp, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GemMaterialUp, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemMaterialUp, ID_BUTTON_CLOSEOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemMaterialUp, ID_LISTIMG_Material2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemMaterialUp, ID_LISTIMG_Material2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemMaterialUp, ID_LISTIMG_Material2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemMaterialUp, ID_LISTIMG_Material2OnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemMaterialUp, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemMaterialUp, ID_BUTTON_OkOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemMaterialUp, ID_LISTIMG_Material1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemMaterialUp, ID_LISTIMG_Material1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemMaterialUp, ID_LISTIMG_Material1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemMaterialUp, ID_LISTIMG_Material1OnIconRButtonUp )
CUI_ID_FRAME_GemMaterialUp::CUI_ID_FRAME_GemMaterialUp()
{
	// Member
	m_pID_FRAME_EquipEvolve = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_LISTIMG_Target = NULL;
	m_pID_TEXT_MaterialName1 = NULL;
	m_pID_TEXT_MaterialName2 = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_TEXT_Tip = NULL;
	m_pID_LISTIMG_Equip = NULL;
	m_pID_TEXT_NumCurrent = NULL;
	m_pID_TEXT_NumNeed = NULL;
	m_pID_PICTURE_StarEffect = NULL;
	m_pID_TEXT_TipAllDone = NULL;
	ResetUIObjects();

}
	// Frame
	bool CUI_ID_FRAME_GemMaterialUp::OnFrameRun()
	{
		if (!OnDirty())
		{
			return true;
		}
		return true;
	}
	bool CUI_ID_FRAME_GemMaterialUp::OnFrameRender()
	{
		OnRender();
		return true;
	}
	// Button
	bool CUI_ID_FRAME_GemMaterialUp::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
	{
		SetVisable(false);
		return true;
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_GemMaterialUp::ID_LISTIMG_Material2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemMaterialUp::ID_LISTIMG_Material2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemMaterialUp::ID_LISTIMG_Material2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemMaterialUp::ID_LISTIMG_Material2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	// Button
	bool CUI_ID_FRAME_GemMaterialUp::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
	{
		SetVisable(false);
		return true;
	}
	// Button
	bool CUI_ID_FRAME_GemMaterialUp::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
	{
		OnOkClick();
		return true;
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_GemMaterialUp::ID_LISTIMG_Material1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		ItemDefine::SItemCommon* pCommon = ( ItemDefine::SItemCommon* )GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
		if (!pCommon)
		{
			return false;
		}
		if (pCommon->ucItemType != ItemDefine::ITEMTYPE_MATERIAL)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString(eWarning_XSJUp_ErrorType) );
			return false;
		}
		ItemDefine::SCreateMaterial* pMaterial = ( ItemDefine::SCreateMaterial* )pCommon;
		if (pMaterial->stMaterialType != ItemDefine::ematerial_gemlevelup)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString(eWarning_XSJUp_ErrorType) );
			return false;
		}
		OnEquipDragOn(pItemDrag,pSender,BT_MaterialBag);
		SetDirty( true );
		return false;
	}
	bool CUI_ID_FRAME_GemMaterialUp::ID_LISTIMG_Material1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemMaterialUp::ID_LISTIMG_Material1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemMaterialUp::ID_LISTIMG_Material1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		ClearEquip();
		return false;
	}

	// 装载UI
bool CUI_ID_FRAME_GemMaterialUp::_LoadUI()
	{
		DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GemMaterialUp.MEUI" , false, UI_Render_LayerThree);
		if ( dwResult == 0 )
		{
			MESSAGE_BOX("读取文件[Data\\UI\\GemMaterialUp.MEUI]失败")
			return false;
		}
		return DoControlConnect();
	}
	// 关连控件
	bool CUI_ID_FRAME_GemMaterialUp::DoControlConnect()
	{
		theUiManager.OnFrameRun( ID_FRAME_GemMaterialUp, s_CUI_ID_FRAME_GemMaterialUpOnFrameRun );
		theUiManager.OnFrameRender( ID_FRAME_GemMaterialUp, s_CUI_ID_FRAME_GemMaterialUpOnFrameRender );
theUiManager.OnButtonClick( ID_FRAME_GemMaterialUp, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_GemMaterialUpID_BUTTON_CLOSEOnButtonClick );
theUiManager.OnIconDragOn( ID_FRAME_GemMaterialUp, ID_LISTIMG_Material2, s_CUI_ID_FRAME_GemMaterialUpID_LISTIMG_Material2OnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_GemMaterialUp, ID_LISTIMG_Material2, s_CUI_ID_FRAME_GemMaterialUpID_LISTIMG_Material2OnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_GemMaterialUp, ID_LISTIMG_Material2, s_CUI_ID_FRAME_GemMaterialUpID_LISTIMG_Material2OnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_GemMaterialUp, ID_LISTIMG_Material2, s_CUI_ID_FRAME_GemMaterialUpID_LISTIMG_Material2OnIconRButtonUp );
theUiManager.OnButtonClick( ID_FRAME_GemMaterialUp, ID_BUTTON_Cancel, s_CUI_ID_FRAME_GemMaterialUpID_BUTTON_CancelOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_GemMaterialUp, ID_BUTTON_Ok, s_CUI_ID_FRAME_GemMaterialUpID_BUTTON_OkOnButtonClick );
theUiManager.OnIconDragOn( ID_FRAME_GemMaterialUp, ID_LISTIMG_Material1, s_CUI_ID_FRAME_GemMaterialUpID_LISTIMG_Material1OnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_GemMaterialUp, ID_LISTIMG_Material1, s_CUI_ID_FRAME_GemMaterialUpID_LISTIMG_Material1OnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_GemMaterialUp, ID_LISTIMG_Material1, s_CUI_ID_FRAME_GemMaterialUpID_LISTIMG_Material1OnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_GemMaterialUp, ID_LISTIMG_Material1, s_CUI_ID_FRAME_GemMaterialUpID_LISTIMG_Material1OnIconRButtonUp );

		m_pID_FRAME_EquipEvolve = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GemMaterialUp );
		m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GemMaterialUp, ID_BUTTON_CLOSE );
		m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_GemMaterialUp, ID_TEXT_Money );
		m_pID_LISTIMG_Target = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemMaterialUp, ID_LISTIMG_Material2 );
		m_pID_TEXT_MaterialName1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GemMaterialUp, ID_TEXT_MaterialName1 );
		m_pID_TEXT_MaterialName2 = (ControlText*)theUiManager.FindControl( ID_FRAME_GemMaterialUp, ID_TEXT_MaterialName2 );
		m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_GemMaterialUp, ID_BUTTON_Cancel );
		m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_GemMaterialUp, ID_BUTTON_Ok );
		m_pID_TEXT_Tip = (ControlText*)theUiManager.FindControl( ID_FRAME_GemMaterialUp, ID_TEXT_Tip );
		m_pID_LISTIMG_Equip = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemMaterialUp, ID_LISTIMG_Material1 );
		m_pID_TEXT_NumCurrent = (ControlText*)theUiManager.FindControl( ID_FRAME_GemMaterialUp, ID_TEXT_NumCurrent );
		m_pID_TEXT_NumNeed = (ControlText*)theUiManager.FindControl( ID_FRAME_GemMaterialUp, ID_TEXT_NumNeed );
		m_pID_PICTURE_StarEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemMaterialUp, ID_PICTURE_StarEffect );
		m_pID_TEXT_TipAllDone = (ControlText*)theUiManager.FindControl( ID_FRAME_GemMaterialUp, ID_TEXT_TipAllDone );
		assert( m_pID_FRAME_EquipEvolve );
		assert( m_pID_BUTTON_CLOSE );
		assert( m_pID_TEXT_Money );
		assert( m_pID_LISTIMG_Target );
		assert( m_pID_TEXT_MaterialName1 );
		assert( m_pID_TEXT_MaterialName2 );
		assert( m_pID_BUTTON_Cancel );
		assert( m_pID_BUTTON_Ok );
		assert( m_pID_TEXT_Tip );
		assert( m_pID_LISTIMG_Equip );
		assert( m_pID_TEXT_NumCurrent );
		assert( m_pID_TEXT_NumNeed );
		assert( m_pID_PICTURE_StarEffect );
		assert( m_pID_TEXT_TipAllDone );
		m_pID_FRAME_EquipEvolve->SetOnVisibleChangedFun( OnVisibleChange );

		m_pID_LISTIMG_Target->SetEnableDrag( false );

		EquipEvolveIntialize();
		m_pID_TEXT_TipAllDone->SetVisable(false);
		m_pID_TEXT_Tip->SetVisable(false);
		m_pID_TEXT_Money->SetVisable(false);
		return true;
	}
	// 卸载UI
bool CUI_ID_FRAME_GemMaterialUp::_UnLoadUI()
	{
		ResetEquipEvolve();
		m_pID_FRAME_EquipEvolve = NULL;
		return theUiManager.RemoveFrame( "Data\\UI\\GemMaterialUp.MEUI" );
	}


void CUI_ID_FRAME_GemMaterialUp::OnVisibleChange( ControlObject* pUIObject )
{
	s_CUI_ID_FRAME_GemMaterialUp.SetDirty( true );
	s_CUI_ID_FRAME_GemMaterialUp.ClearEquip();	
	s_CUI_ID_FRAME_GemMaterialUp.RefreshAllBagEnable();

}

void CUI_ID_FRAME_GemMaterialUp::RetriveGemUpInfo( SCharItem* pItem )
{
	const ComposeData2* pData = theItemComposeConfig.GetItemComposeData2( pItem->GetItemID() );
	if ( pData == NULL )
	{
		return;
	}
	m_TargetId = pData->GetNewItemID();
	m_nNeedMoney = pData->GetCostMoney();
	const std::vector<ComposeData2::SMaterial> & vecMaterial = pData->GetMaterialList();
	for(int i = 0; i < vecMaterial.size(); ++i)
	{
		if (vecMaterial[i].nMaterialID == pItem->GetItemID())
		{
			m_nNeedCount = vecMaterial[i].nCount;
			break;
		}		
	}

}

bool CUI_ID_FRAME_GemMaterialUp::IsEvolveAllDone( ControlIconDrag::S_ListImg * pImg )
{
	const ComposeData2* pData = theItemComposeConfig.GetItemComposeData2( pImg->m_pkIconInfo->Id() );
	if ( pData == NULL )
	{
		return true;
	}
	return false;

}

bool CUI_ID_FRAME_GemMaterialUp::ProcessAllDone( ControlIconDrag::S_ListImg * pImg )
{
	bool bRet = EquipEvolveUI::ProcessAllDone(pImg);
	m_pID_LISTIMG_Target->SetVisable(!bRet);
	if (bRet)
	{
		m_pID_TEXT_Tip->SetVisable(false);
	}

	return bRet;

}

void CUI_ID_FRAME_GemMaterialUp::ClearEquip()
{
	EquipEvolveUI::ClearEquip();
	m_pID_LISTIMG_Target->Clear();
	m_pID_TEXT_MaterialName1->SetText("");
	m_pID_TEXT_MaterialName2->SetText("");
	m_pID_TEXT_NumCurrent->SetText("");
	m_pID_TEXT_NumNeed->SetText("");
	m_TargetId = -1;
	m_nNeedCount = 0;
	m_nNeedMoney = 0;

}

void CUI_ID_FRAME_GemMaterialUp::_RefreshEquipInfo( ControlIconDrag::S_ListImg* pListImg )
{
	EquipEvolveUI::_RefreshEquipInfo(pListImg);
	SCharItem* pItem = (SCharItem*)pListImg->m_pkIconInfo->GetData();
	RetriveGemUpInfo(pItem);

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
	// 添加名字
	Common::_tstring tstrName( pItemCommon->GetItemName() );
	S_IconInfoHero::ReplaceSpecifiedName( pItemCommon->ustLevel, tstrName );
	m_pID_TEXT_MaterialName1->SetText(tstrName.c_str());

	char cTmp[256] = {0};
	sprintf_s(cTmp,256,"%d",m_nNeedCount);
	m_pID_TEXT_NumNeed->SetText(cTmp);

	int nTotal = pListImg->m_pkIconInfo->Count();
	m_pID_LISTIMG_Equip->GetItemByIndex( 0 )->m_pkIconInfo->Count() = nTotal;
	sprintf_s(cTmp,256,"%d",nTotal);

	DWORD dwColor = 0xffffffff;
	if(nTotal < m_nNeedCount)
	{
		dwColor = 0xffff0000;
	}
	m_pID_TEXT_NumCurrent->SetText(cTmp,dwColor);

	m_pID_LISTIMG_Target->Clear();
	if (m_TargetId != -1)
	{
		ControlIconDrag::S_ListImg liTarget;
		liTarget.SetData( m_TargetId,1 );
		m_pID_LISTIMG_Target->SetItem( &liTarget, 0 );
		ControlIconDrag::S_ListImg* pTargetItem = m_pID_LISTIMG_Target->GetItemByIndex(0);
		ItemDefine::SItemCommon* pTargetItemCommon = GettheItemDetail().GetItemByID( pTargetItem->m_pkIconInfo->Id());
		Common::_tstring tstrTargetName( pTargetItemCommon->GetItemName() );
		S_IconInfoHero::ReplaceSpecifiedName( pTargetItemCommon->ustLevel, tstrTargetName );
		m_pID_TEXT_MaterialName2->SetText(tstrTargetName.c_str());

	}
	TipVisible(nTotal >= m_nNeedCount );
	RefreshNeedMoney();

}

void CUI_ID_FRAME_GemMaterialUp::ResetUIObjects()
{
	m_pID_TEXT_MaterialName1 = NULL;
	m_pID_TEXT_MaterialName2 = NULL;
	m_pID_LISTIMG_Target = NULL;
	m_pID_TEXT_NumCurrent = NULL;
	m_pID_TEXT_Tip = NULL;
	m_pID_TEXT_NumNeed = NULL;
	m_TargetId = -1;
	m_nNeedCount = 0;
	m_nNeedMoney = 0;

}

void CUI_ID_FRAME_GemMaterialUp::SendEvolveMsg()
{
	MsgItemComposeGem msgComposeGem;
	msgComposeGem.nMaterialCount = 1;
	msgComposeGem.composeType = MsgItemComposeGem::ECT_MATERIAL;

	msgComposeGem.materials[0].nItemBagType= BT_MaterialBag;
	msgComposeGem.materials[0].nItemIndex = m_stEquipBagIndex;
	msgComposeGem.materials[0].nItemGuid = m_stEquipBagGuid;
	msgComposeGem.materials[0].nCount = 5;

	GettheNetworkInput().SendMsg( &msgComposeGem );

}

bool CUI_ID_FRAME_GemMaterialUp::IsMatchEquipType( ItemDefine::SItemCommon* pItemCommon )
{
	return pItemCommon && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_MATERIAL;

}

void CUI_ID_FRAME_GemMaterialUp::TipVisible( bool IsMaterialExist )
{
	if (IsMaterialExist)
	{
		m_nSelectMaterialIndex = 0;
		m_pID_TEXT_Tip->SetVisable(false);
	}
	else
	{
		m_nSelectMaterialIndex = -1;
		m_pID_TEXT_Tip->SetVisable(true);
	}

}

void CUI_ID_FRAME_GemMaterialUp::RefreshOkButton()
{
	EquipEvolveUI::RefreshOkButton();

// 	ControlIconDrag::S_ListImg* pListImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
// 	if (pListImg)
// 	{
// 		int nTotal = thePlayerRole.m_bagMaterial.GetItemCount(pListImg->m_pkIconInfo->Id());
// 		if (nTotal < m_nNeedCount)
// 		{
// 			m_pID_BUTTON_Ok->SetEnable(false);
// 		}		
// 	}
	

}

void CUI_ID_FRAME_GemMaterialUp::RefreshByItemChange()
{
	RefreshEquipInfo();
	RefreshOkButton();
}


