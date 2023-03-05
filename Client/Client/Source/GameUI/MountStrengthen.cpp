/********************************************************************
Created by UIEditor.exe
FileName: E:\新建文件夹\3Guo_Client_02.05\Data\Ui\MountStrengthen.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "MountStrengthen.h"
#include "UIMgr.h"
#include "Pet.h"
#include "Pack.h"
#include "PlayerRole.h"
#include "XmlStringLanguage.h"
#include "GlobalDef.h"
#include "PackItemEnableManager.h"
#include "MountStrengthenConfig.h"
#include "MessageDefine.h"
#include "NetworkInput.h"
#include "ScreenInfoManager.h"
#include "MountMoveStar.h"
#define DELAY_TIME 350

CUI_ID_FRAME_MountStrengthen s_CUI_ID_FRAME_MountStrengthen;
MAP_FRAME_RUN( s_CUI_ID_FRAME_MountStrengthen, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_MountStrengthen, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MountStrengthen, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MountStrengthen, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MountStrengthen, ID_BUTTON_OkOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_MountStrengthen, ID_LISTIMG_ProtectOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_MountStrengthen, ID_LISTIMG_ProtectOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MountStrengthen, ID_LISTIMG_ProtectOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_MountStrengthen, ID_LISTIMG_ProtectOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_MountStrengthen, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_MountStrengthen, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MountStrengthen, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_MountStrengthen, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MountStrengthen, ID_BUTTON_CancelOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_MountStrengthen, ID_LISTIMG_MountOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_MountStrengthen, ID_LISTIMG_MountOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MountStrengthen, ID_LISTIMG_MountOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_MountStrengthen, ID_LISTIMG_MountOnIconRButtonUp )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_MountStrengthen, ID_CHECKBOX_Use_ProtectOnCheckBoxCheck )
CUI_ID_FRAME_MountStrengthen::CUI_ID_FRAME_MountStrengthen()
{
	// Member
	m_pID_FRAME_MountStrengthen = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_TEXT_UseMoney = NULL;
	m_pID_LISTIMG_Protect = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_LISTIMG_Mount = NULL;
	m_pID_TEXT_SuccessRatio = NULL;
	m_pID_TEXT_Fail = NULL;
	m_pID_TEXT_Success = NULL;
	m_pID_TEXT_MaterialName = NULL;
	m_pID_TEXT_MountName = NULL;
	m_pID_TEXT_PeotectName = NULL;
	m_pID_CHECKBOX_Use_Protect = NULL;
	m_pID_TEXT_T1 = NULL;
	m_pID_TEXT_T2 = NULL;
	m_pID_TEXT_T3 = NULL;
	m_pID_TEXT_T4 = NULL;

	m_nMaterialIndex = -1;
	m_nMaterialGuid = 0;
	m_nMountIndex = -1;
	m_nMountGuid = 0;

	m_unProtectNum = 0;
	m_lastStarLevel = 0;

	m_status = EffectStatus_No;
	m_MountSender = NULL;
	m_MaterialSender = NULL;
	m_bAckMsg = false;
}
// Frame
bool CUI_ID_FRAME_MountStrengthen::OnFrameRun()
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
bool CUI_ID_FRAME_MountStrengthen::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_MountStrengthen::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	_SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_MountStrengthen::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_MountStrengthen::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	SendMsg();
	m_pID_BUTTON_Ok->SetEnable(false);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_MountStrengthen::ID_LISTIMG_ProtectOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																  ControlIconDrag::S_ListImg* pItemDrag,
																  ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_MountStrengthen::ID_LISTIMG_ProtectOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_MountStrengthen::ID_LISTIMG_ProtectOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_MountStrengthen::ID_LISTIMG_ProtectOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_MountStrengthen::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																   ControlIconDrag::S_ListImg* pItemDrag,
																   ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!pSender || !pItemDrag)
		return false;
	ItemDefine::SItemCommon* pItemCommon = ( ItemDefine::SItemCommon* )GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
	if (!pItemCommon)
		return false;
	if(pItemCommon->ucItemType != ItemDefine::ITEMTYPE_MATERIAL)
		return false;

	ItemDefine::SCreateMaterial* pMaterial = (ItemDefine::SCreateMaterial*)pItemCommon;
	if(pMaterial->stMaterialType != ItemDefine::ematerial_mountrune)
		return false;
	// 包裹里
	if(!s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender))
		return false;

	m_MaterialSender = pSender;

	ClearImg(ITP_Material, m_pID_LISTIMG_Material);

	CItemBag2* pdrag_bag = &thePlayerRole.m_bagMaterial;

	m_nMaterialIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_MaterialBag, pItemDrag );
	SCharItem item;
	if(m_nMaterialIndex != -1 && pdrag_bag->GetItem(m_nMaterialIndex,&item))
		m_nMaterialGuid = item.itembaseinfo.nOnlyInt;
	else
		m_nMaterialGuid = 0;

	m_pID_LISTIMG_Material->Clear();
	ControlIconDrag::S_ListImg img;
	img.SetData(pItemDrag->m_pkIconInfo->Id(), pItemDrag->m_pkIconInfo->Count());
	m_pID_LISTIMG_Material->SetItem(&img);

	if(m_nMaterialIndex != -1)
		CPackItemEnableManager::Instance()->RefreshBagItemEnable( pdrag_bag, m_nMaterialIndex, true );

	ShowMaterialName(pItemDrag);
	RefreshOkButton();
	TipsVisiable();

	return false;
}
void CUI_ID_FRAME_MountStrengthen::ShowMaterialName(ControlIconDrag::S_ListImg* pItemDrag)
{
	if (!m_pID_TEXT_MaterialName || !pItemDrag || pItemDrag->IsNull())
		return;
	m_pID_TEXT_MaterialName->SetText("");

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if (!pItemCommon)
		return;

	char temp[128] = {0};
	sprintf(temp, "%s", pItemCommon->GetItemName());
	m_pID_TEXT_MaterialName->SetText(temp);
}

void CUI_ID_FRAME_MountStrengthen::ShowProtectName(ControlIconDrag::S_ListImg* pItemDrag)
{
	if (!m_pID_TEXT_PeotectName || !pItemDrag || pItemDrag->IsNull())
		return;
	m_pID_TEXT_PeotectName->SetText("");

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if (!pItemCommon)
		return;

	char temp[128] = {0};
	sprintf(temp, "%s,%d%s", pItemCommon->GetItemName(), m_unProtectNum, theXmlString.GetString(eText_StarProtect_Text));
	m_pID_TEXT_PeotectName->SetText(temp);
}

bool CUI_ID_FRAME_MountStrengthen::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_MountStrengthen::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_MountStrengthen::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	//ClearImg(ITP_Material, m_pID_LISTIMG_Material);
	return false;
}
// Button
bool CUI_ID_FRAME_MountStrengthen::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	_SetVisable(false);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_MountStrengthen::ID_LISTIMG_MountOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																ControlIconDrag::S_ListImg* pItemDrag,
																ControlIconDrag::S_ListImg* pItemSrc )
{
	if (!pSender || !pItemDrag || pItemDrag->IsNull())
		return false;
	int nIndex = s_CUI_ID_FRAME_Pet.PenIcon_GetIndexByItem( pItemDrag );
	if ( nIndex == -1 )
		return false;
	if (thePlayerRole.GetActivedMountIndex() == nIndex)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eText_MountStrengthen_ActivedMount) );
		return false;
	}
	SMountItem* pMountItem = &thePlayerRole.GetMountByIndex( nIndex );
	if( !pMountItem || pMountItem->baseInfo.id == InvalidLogicNumber )
		return false;
	if (pMountItem->baseInfo.level >= SMountItem::MICD_MountMaxLevel && !m_bAckMsg)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eText_MountStrengthen_MaxLevel) );
		return false;
	}
	const MountStrengthenData* pData = theMountStrengthenConfig.GetMountStrengthenData(pMountItem->baseInfo.id);
	if (!pData)
	{
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_MountStrengthen_ErrorMount));
		return false;
	}

	m_MountSender = pSender;

	m_nMountIndex = nIndex;
	m_nMountGuid = pMountItem->baseInfo.guid;
#ifndef BANSHU
	if (m_lastStarLevel < 4 && pMountItem->baseInfo.level >= 4)
	{
		if (!m_pID_CHECKBOX_Use_Protect->IsChecked())
			s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_MountStrengthen_NoSelect));
	}
#endif

	m_lastStarLevel = pMountItem->baseInfo.level;

	m_pID_LISTIMG_Mount->Clear();
	m_pID_LISTIMG_Mount->SetItem( pItemDrag, 0 );
	m_pID_LISTIMG_Mount->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;
	m_pID_LISTIMG_Mount->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;

	ShowMountName(pItemDrag);
	ShowMaterialIcon();
	RefreshOkButton();
	RefreshMoney();
	RefreshProbability();
	TipsVisiable();

	return false;
}

void CUI_ID_FRAME_MountStrengthen::ShowMountName(ControlIconDrag::S_ListImg* pItemDrag)
{
	if (!m_pID_TEXT_MountName || !pItemDrag || pItemDrag->IsNull())
		return;
	m_pID_TEXT_MountName->SetText("");

	if (m_nMountIndex == -1)
		return;

	SMountItem* pMountItem = &thePlayerRole.GetMountByIndex( m_nMountIndex );
	if( !pMountItem || pMountItem->baseInfo.id == InvalidLogicNumber )
		return;

	char temp[128] = {0};
	if (pMountItem->baseInfo.level)
		sprintf(temp, "%s+%d", pMountItem->baseInfo.szName, pMountItem->baseInfo.level);
	else
		sprintf(temp, "%s", pMountItem->baseInfo.szName);

	m_pID_TEXT_MountName->SetText(temp);

	if (pMountItem->baseInfo.level < 4)
	{
		m_pID_CHECKBOX_Use_Protect->SetEnable(false);
		m_pID_LISTIMG_Protect->Clear();
		m_unProtectNum = 0;
		m_pID_TEXT_PeotectName->SetText("");
		m_pID_TEXT_T4->SetText(theXmlString.GetString(eText_MountStrengthen_UnderFour));
	}
	else
	{
		m_pID_CHECKBOX_Use_Protect->SetEnable(true);
		m_pID_TEXT_T4->SetText(theXmlString.GetString(eText_MountStrengthen_BeyongFour));
	}
}

bool CUI_ID_FRAME_MountStrengthen::ID_LISTIMG_MountOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_MountStrengthen::ID_LISTIMG_MountOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_MountStrengthen::ID_LISTIMG_MountOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	//ClearImg(ITP_Mount, m_pID_LISTIMG_Mount);
	ClearAll();
	return false;
}
// CheckBox
void CUI_ID_FRAME_MountStrengthen::ID_CHECKBOX_Use_ProtectOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	ShowProtectMaterialIcon();
}

// 装载UI
bool CUI_ID_FRAME_MountStrengthen::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\MountStrengthen.MEUI", false, UI_Render_LayerThree  );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\MountStrengthen.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_MountStrengthen::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_MountStrengthen, s_CUI_ID_FRAME_MountStrengthenOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_MountStrengthen, s_CUI_ID_FRAME_MountStrengthenOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_MountStrengthen, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_MountStrengthenID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MountStrengthen, ID_BUTTON_HELP, s_CUI_ID_FRAME_MountStrengthenID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MountStrengthen, ID_BUTTON_Ok, s_CUI_ID_FRAME_MountStrengthenID_BUTTON_OkOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_MountStrengthen, ID_LISTIMG_Protect, s_CUI_ID_FRAME_MountStrengthenID_LISTIMG_ProtectOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_MountStrengthen, ID_LISTIMG_Protect, s_CUI_ID_FRAME_MountStrengthenID_LISTIMG_ProtectOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_MountStrengthen, ID_LISTIMG_Protect, s_CUI_ID_FRAME_MountStrengthenID_LISTIMG_ProtectOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_MountStrengthen, ID_LISTIMG_Protect, s_CUI_ID_FRAME_MountStrengthenID_LISTIMG_ProtectOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_MountStrengthen, ID_LISTIMG_Material, s_CUI_ID_FRAME_MountStrengthenID_LISTIMG_MaterialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_MountStrengthen, ID_LISTIMG_Material, s_CUI_ID_FRAME_MountStrengthenID_LISTIMG_MaterialOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_MountStrengthen, ID_LISTIMG_Material, s_CUI_ID_FRAME_MountStrengthenID_LISTIMG_MaterialOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_MountStrengthen, ID_LISTIMG_Material, s_CUI_ID_FRAME_MountStrengthenID_LISTIMG_MaterialOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_MountStrengthen, ID_BUTTON_Cancel, s_CUI_ID_FRAME_MountStrengthenID_BUTTON_CancelOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_MountStrengthen, ID_LISTIMG_Mount, s_CUI_ID_FRAME_MountStrengthenID_LISTIMG_MountOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_MountStrengthen, ID_LISTIMG_Mount, s_CUI_ID_FRAME_MountStrengthenID_LISTIMG_MountOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_MountStrengthen, ID_LISTIMG_Mount, s_CUI_ID_FRAME_MountStrengthenID_LISTIMG_MountOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_MountStrengthen, ID_LISTIMG_Mount, s_CUI_ID_FRAME_MountStrengthenID_LISTIMG_MountOnIconRButtonUp );
	theUiManager.OnCheckBoxCheck( ID_FRAME_MountStrengthen, ID_CHECKBOX_Use_Protect, s_CUI_ID_FRAME_MountStrengthenID_CHECKBOX_Use_ProtectOnCheckBoxCheck );

	m_pID_FRAME_MountStrengthen = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_MountStrengthen );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_MountStrengthen, ID_BUTTON_CLOSE );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_MountStrengthen, ID_BUTTON_HELP );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_MountStrengthen, ID_BUTTON_Ok );
	m_pID_TEXT_UseMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_MountStrengthen, ID_TEXT_UseMoney );
	m_pID_LISTIMG_Protect = (ControlListImage*)theUiManager.FindControl( ID_FRAME_MountStrengthen, ID_LISTIMG_Protect );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_MountStrengthen, ID_LISTIMG_Material );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_MountStrengthen, ID_BUTTON_Cancel );
	m_pID_LISTIMG_Mount = (ControlListImage*)theUiManager.FindControl( ID_FRAME_MountStrengthen, ID_LISTIMG_Mount );
	m_pID_TEXT_SuccessRatio = (ControlText*)theUiManager.FindControl( ID_FRAME_MountStrengthen, ID_TEXT_SuccessRatio );
	m_pID_TEXT_Fail = (ControlText*)theUiManager.FindControl( ID_FRAME_MountStrengthen, ID_TEXT_Fail );
	m_pID_TEXT_Success = (ControlText*)theUiManager.FindControl( ID_FRAME_MountStrengthen, ID_TEXT_Success );
	m_pID_TEXT_MaterialName = (ControlText*)theUiManager.FindControl( ID_FRAME_MountStrengthen, ID_TEXT_MaterialName );
	m_pID_TEXT_MountName = (ControlText*)theUiManager.FindControl( ID_FRAME_MountStrengthen, ID_TEXT_MountName );
	m_pID_TEXT_PeotectName = (ControlText*)theUiManager.FindControl( ID_FRAME_MountStrengthen, ID_TEXT_PeotectName );
	m_pID_CHECKBOX_Use_Protect = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MountStrengthen, ID_CHECKBOX_Use_Protect );
	m_pID_TEXT_T1 = (ControlText*)theUiManager.FindControl( ID_FRAME_MountStrengthen, ID_TEXT_T1 );
	m_pID_TEXT_T2 = (ControlText*)theUiManager.FindControl( ID_FRAME_MountStrengthen, ID_TEXT_T2 );
	m_pID_TEXT_T3 = (ControlText*)theUiManager.FindControl( ID_FRAME_MountStrengthen, ID_TEXT_T3 );
	m_pID_TEXT_T4 = (ControlText*)theUiManager.FindControl( ID_FRAME_MountStrengthen, ID_TEXT_T4 );

	assert( m_pID_FRAME_MountStrengthen );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_TEXT_UseMoney );
	assert( m_pID_LISTIMG_Protect );
	assert( m_pID_LISTIMG_Material );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_LISTIMG_Mount );
	assert( m_pID_TEXT_SuccessRatio );
	assert( m_pID_TEXT_Fail );
	assert( m_pID_TEXT_Success );
	assert( m_pID_TEXT_MaterialName );
	assert( m_pID_TEXT_MountName );
	assert( m_pID_TEXT_PeotectName );
	assert( m_pID_CHECKBOX_Use_Protect );
	assert( m_pID_TEXT_T1 );
	assert( m_pID_TEXT_T2 );
	assert( m_pID_TEXT_T3 );
	assert( m_pID_TEXT_T4 );

	m_pID_TEXT_Success->SetVisable(false);
	m_pID_TEXT_Fail->SetVisable(false);
	m_pID_FRAME_MountStrengthen->SetOnVisibleChangedFun( OnVisibleChange );
	m_pID_TEXT_T1->SetVisable(false);
	m_pID_TEXT_T2->SetVisable(false);
	m_pID_TEXT_T3->SetVisable(false);
	m_pID_BUTTON_Ok->SetEnable(false);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_MountStrengthen::_UnLoadUI()
{
	m_pID_FRAME_MountStrengthen = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\MountStrengthen.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_MountStrengthen::_IsVisable()
{
	return m_pID_FRAME_MountStrengthen->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_MountStrengthen::_SetVisable( const bool bVisable )
{
	if (bVisable)
	{
		TipsVisiable();

		if (!s_CUI_ID_FRAME_PACK.IsVisable())
			s_CUI_ID_FRAME_PACK.SetVisable(true);
		if (!s_CUI_ID_FRAME_Pet.IsVisable())
			s_CUI_ID_FRAME_Pet.SetVisable(true);

		ResetWindowPositionEx(s_CUI_ID_FRAME_PACK.GetFrame(), m_pID_FRAME_MountStrengthen, s_CUI_ID_FRAME_Pet.GetFrame());
	}
	
	m_pID_FRAME_MountStrengthen->SetVisable( bVisable );
	m_pID_FRAME_MountStrengthen->SetCovered(false);
	if (!bVisable)
	{
		if(s_CUI_ID_FRAME_MountMoveStar.IsVisable())
			s_CUI_ID_FRAME_MountMoveStar.SetVisable(false);//坐骑强化也一起关闭 免得数据不同步
	}
}

bool CUI_ID_FRAME_MountStrengthen::IsPackItemBeUsing( __int64 nGuid )
{
	if( !IsVisable() || nGuid <= 0 )
		return false;

	if (m_nMaterialGuid == nGuid)
		return true;

	return false;
}

void CUI_ID_FRAME_MountStrengthen::ClearImg(ItemType itype,ControlListImage *pTargetImg)
{
	if (!pTargetImg)
		return;
	pTargetImg->Clear();

	if (itype == ITP_Mount)
	{
		m_nMountIndex = -1;
		m_nMountGuid = 0;
		m_pID_TEXT_MountName->SetText("");
		m_pID_TEXT_T4->SetText("");
		m_pID_CHECKBOX_Use_Protect->SetCheck(false);
		m_pID_CHECKBOX_Use_Protect->SetEnable(false);
		m_pID_LISTIMG_Protect->Clear();
		m_unProtectNum = 0;
		m_pID_TEXT_PeotectName->SetText("");

		RefreshMoney();
		RefreshProbability();
		SetAckMsg(false);
	}
	else if (itype == ITP_Material)
	{
		CItemBag2* pTargetBag = &thePlayerRole.m_bagMaterial;
		int16 nItemIndex = m_nMaterialIndex;

		m_nMaterialIndex = -1;
		m_nMaterialGuid = 0;
		m_pID_TEXT_MaterialName->SetText("");

		if(nItemIndex != -1)
			CPackItemEnableManager::Instance()->RefreshBagItemEnable( pTargetBag, nItemIndex, true );
	}

	RefreshOkButton();
	TipsVisiable();
}

void CUI_ID_FRAME_MountStrengthen::OnVisibleChange( ControlObject* pUIObject )
{
	s_CUI_ID_FRAME_MountStrengthen.ClearAll();
}

void CUI_ID_FRAME_MountStrengthen::ClearAll()
{
	ClearImg(ITP_Material, m_pID_LISTIMG_Material);
	ClearImg(ITP_Mount, m_pID_LISTIMG_Mount);

	m_unProtectNum = 0;
	m_status = EffectStatus_No;
	m_MountSender = NULL;
	m_MaterialSender = NULL;
	m_pID_TEXT_T4->SetText("");
	m_lastStarLevel = 0;
}

uint16 CUI_ID_FRAME_MountStrengthen::GetProtectMatrialID(uint16 item_level)
{
	if (item_level >= 4 && item_level < 7)
	{
		m_unProtectNum = 4;
		return SID_ProtectMountFour;
	}
	else if (item_level >= 7 && item_level < 10)
	{
		m_unProtectNum = 7;
		return SID_ProtectMountSeven;
	}
	else if (item_level >= 10)
	{
		m_unProtectNum = 10;
		return SID_ProtectMountTen;
	}
	else
		return 0xffff;
}

void CUI_ID_FRAME_MountStrengthen::ShowProtectMaterialIcon()
{
	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Mount->GetItemByIndex(0);
	if (!pImg || pImg->IsNull() || m_nMountIndex == -1)
	{
		m_pID_CHECKBOX_Use_Protect->SetCheck(false);
		m_unProtectNum = 0;
		return;
	}

	SMountItem* pMountItem = &thePlayerRole.GetMountByIndex( m_nMountIndex );
	if( !pMountItem || pMountItem->baseInfo.id == InvalidLogicNumber )
	{
		m_pID_CHECKBOX_Use_Protect->SetCheck(false);
		m_unProtectNum = 0;
		return;
	}

	if (m_pID_CHECKBOX_Use_Protect->IsChecked())
	{
		m_pID_LISTIMG_Protect->Clear();
		uint16 proMaterialID = GetProtectMatrialID(pMountItem->baseInfo.level);
		int nBagIndex = -1;
		ControlIconDrag::S_ListImg * pListImgItem = RetriveMaterialImg(proMaterialID,nBagIndex);
		ControlIconDrag::S_ListImg ImgItem;
		if (NULL == pListImgItem)
		{
			ImgItem.SetData(proMaterialID,1,eIcon_Disable);
			pListImgItem = &ImgItem;
			m_pID_LISTIMG_Protect->SetItem( pListImgItem );
			ShowProtectName(pListImgItem);
			m_unProtectNum = 0;

			s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_MountStrengthen_NoProtect));
		}
		else
		{
			m_pID_LISTIMG_Protect->SetItem( pListImgItem );
			ShowProtectName(pListImgItem);
		}
	}
	else
	{
		m_pID_LISTIMG_Protect->Clear();
		m_unProtectNum = 0;
		m_pID_TEXT_PeotectName->SetText("");
	}
}

ControlIconDrag::S_ListImg* CUI_ID_FRAME_MountStrengthen::RetriveMaterialImg( short itemId ,int& nIndex)
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

void CUI_ID_FRAME_MountStrengthen::RefreshOkButton()
{
	if (!m_pID_BUTTON_Ok)
		return;
	m_pID_BUTTON_Ok->SetEnable(false);

	if (m_nMountIndex == -1)
		return;
	if (m_nMaterialIndex == -1)
		return;

	SMountItem* pMountItem = &thePlayerRole.GetMountByIndex( m_nMountIndex );
	if( !pMountItem || pMountItem->baseInfo.id == InvalidLogicNumber )
		return;
	if (pMountItem->baseInfo.level >= SMountItem::MICD_MountMaxLevel)
	{
		TipsVisiable();
		return;
	}
	const MountStrengthenData* pData = theMountStrengthenConfig.GetMountStrengthenData(pMountItem->baseInfo.id);
	if (!pData)
		return;
	if(!thePlayerRole.HaveEnoughMoney(pData->GetPrice(pMountItem->baseInfo.level)))
		return;

	m_pID_BUTTON_Ok->SetEnable(true);
}

void CUI_ID_FRAME_MountStrengthen::RefreshMoney()
{
	if (!m_pID_TEXT_UseMoney)
		return;
	m_pID_TEXT_UseMoney->SetText("");

	if (m_nMountIndex == -1)
		return;
	SMountItem* pMountItem = &thePlayerRole.GetMountByIndex( m_nMountIndex );
	if( !pMountItem || pMountItem->baseInfo.id == InvalidLogicNumber )
		return;

	const MountStrengthenData* pData = theMountStrengthenConfig.GetMountStrengthenData(pMountItem->baseInfo.id);
	if (!pData)
		return;

	int nMoney = pData->GetPrice(pMountItem->baseInfo.level);
	if (nMoney <= 0)
		return;

	std::string text = "";
	thePlayerRole.GetGSCStringFromJiaoZi(nMoney, text);
	DWORD dwColor = 0xffffffff;
	if(!thePlayerRole.HaveEnoughMoney(nMoney))
	{
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_StarLEvolveNoMomeny), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true);
		dwColor = 0xffff0000;
	}

	m_pID_TEXT_UseMoney->SetText(text,dwColor);
}

void CUI_ID_FRAME_MountStrengthen::RefreshProbability()
{
	if (!m_pID_TEXT_SuccessRatio)
		return;
	m_pID_TEXT_SuccessRatio->SetText("");

	if (m_nMountIndex == -1)
		return;
	SMountItem* pMountItem = &thePlayerRole.GetMountByIndex( m_nMountIndex );
	if( !pMountItem || pMountItem->baseInfo.id == InvalidLogicNumber )
		return;

	const MountStrengthenData* pData = theMountStrengthenConfig.GetMountStrengthenData(pMountItem->baseInfo.id);
	if (!pData)
		return;

	float fProbability = pData->GetProbability(pMountItem->baseInfo.level);
	if (fProbability < 0.000001)
		return;

	int nProb = int(fProbability * 100);
	char tmpStr[32] = {};
	sprintf(tmpStr, "%d%%", nProb);
	m_pID_TEXT_SuccessRatio->SetText(tmpStr);
}

void CUI_ID_FRAME_MountStrengthen::SendMsg()
{
	MsgMountStrengthen msg;

	if (m_nMountIndex == -1 || m_nMaterialIndex == -1)
		return;

	msg.mountIndex = m_nMountIndex;
	msg.mountGuid = m_nMountGuid;

	msg.materialIndex = m_nMaterialIndex;
	msg.materialGuid = m_nMaterialGuid;

	msg.protectNum = m_unProtectNum;

	GettheNetworkInput().SendMsg( &msg );
}

void CUI_ID_FRAME_MountStrengthen::UpdataAll()
{
	if (m_nMountIndex != -1 && m_MountSender)
	{
		ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_Pet.PenIcon_GetItemByIndex( m_nMountIndex );
		if (!pItemImg || pItemImg->IsNull())
		{
			ClearImg(ITP_Mount, m_pID_LISTIMG_Mount);
		}
		else
			ID_LISTIMG_MountOnIconDragOn(m_MountSender, NULL, pItemImg, 0);
	}

	/*if (m_nMaterialIndex != -1 && m_MaterialSender)
	{
		ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( BT_MaterialBag, m_nMaterialIndex );
		if (!pItemImg || pItemImg->IsNull())
		{
			ClearImg(ITP_Material, m_pID_LISTIMG_Material);
		}
		else
			ID_LISTIMG_MaterialOnIconDragOn(m_MaterialSender, NULL, pItemImg, 0);
	}*/

	if (m_nMountIndex != -1)
	{
		SMountItem* pMountItem = &thePlayerRole.GetMountByIndex( m_nMountIndex );
		if( !pMountItem || pMountItem->baseInfo.id == InvalidLogicNumber )
			return;
		if (pMountItem->baseInfo.level >= 4)
			ShowProtectMaterialIcon();
	}
}

void CUI_ID_FRAME_MountStrengthen::TipsVisiable()
{
	if (!m_pID_TEXT_T1 || !m_pID_TEXT_T2 || !m_pID_TEXT_T3)
		return;
	m_pID_TEXT_T1->SetVisable(false);
	m_pID_TEXT_T2->SetVisable(false);
	m_pID_TEXT_T3->SetVisable(false);

	if (m_nMountIndex == -1)
	{
		m_pID_TEXT_T1->SetVisable(true);
		return;
	}
	if (m_nMountIndex != -1)
	{
		SMountItem* pMountItem = &thePlayerRole.GetMountByIndex( m_nMountIndex );
		if( !pMountItem || pMountItem->baseInfo.id == InvalidLogicNumber )
			return;
		if (pMountItem->baseInfo.level >= SMountItem::MICD_MountMaxLevel)
		{
			m_pID_TEXT_T3->SetVisable(true);
			return;
		}
	}
	if (m_nMaterialIndex == -1)
	{
		m_pID_TEXT_T2->SetVisable(true);
		return;
	}
}

void CUI_ID_FRAME_MountStrengthen::ShowMaterialIcon()
{
	if (!m_pID_LISTIMG_Mount || !m_pID_LISTIMG_Material)
		return;
	ClearImg(ITP_Material, m_pID_LISTIMG_Material);
	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Mount->GetItemByIndex(0);
	if (!pImg || pImg->IsNull())
		return;

	int nBagIndex = -1;
	ControlIconDrag::S_ListImg * pListImgItem = RetriveMaterialImg(SID_MountStrengthen,nBagIndex);
	ControlIconDrag::S_ListImg ImgItem;
	if (NULL == pListImgItem)
	{
		ImgItem.SetData(SID_MountStrengthen,1,eIcon_Disable);
		pListImgItem = &ImgItem;
		m_pID_LISTIMG_Material->SetItem( pListImgItem );
	}
	else
	{
		m_pID_LISTIMG_Material->SetItem( pListImgItem );
		m_nMaterialGuid = pListImgItem->m_pkIconInfo->GetOnlyId();
		if (nBagIndex != -1)
		{
			m_nMaterialIndex = nBagIndex;
			CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_nMaterialIndex, true );
		}
	}

	ShowMaterialName(pListImgItem);
}