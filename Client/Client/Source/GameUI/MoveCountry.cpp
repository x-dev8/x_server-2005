/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\MoveCountry.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "MoveCountry.h"
#include "PlayerRole.h"
#include "CountryDefine.h"
#include "XmlStringLanguage.h"
#include "ChangeCountryConfig.h"
#include "ui/Pack.h"
#include "PackItemEnableManager.h"
#include "CountryBaseInfo.h"
#include "NetworkInput.h"
#include "CountryMessage.h"
CUI_ID_FRAME_changecountry s_CUI_ID_FRAME_changecountry;
MAP_FRAME_RUN( s_CUI_ID_FRAME_changecountry, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_changecountry, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_changecountry, ID_CHECKBOX_countryA_AOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_changecountry, ID_BUTTON_changecountryOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_changecountry, ID_BUTTON_canelOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_changecountry, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_changecountry, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_changecountry, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_changecountry, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_changecountry, ID_CHECKBOX_countryA_COnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_changecountry, ID_CHECKBOX_countryA_BOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_changecountry, ID_CHECKBOX_countryB_BOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_changecountry, ID_CHECKBOX_countryB_COnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_changecountry, ID_CHECKBOX_countryB_AOnCheckBoxCheck )
CUI_ID_FRAME_changecountry::CUI_ID_FRAME_changecountry()
{
	// Member
	m_pID_FRAME_changecountry = NULL;
	m_pID_CHECKBOX_countryA_A = NULL;
	m_pID_TEXT_countryAStrong = NULL;
	m_pID_TEXT_countryBStrong = NULL;
	m_pID_BUTTON_changecountry = NULL;
	m_pID_BUTTON_canel = NULL;
	m_pID_TEXT_itemname = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_CHECKBOX_countryA_C = NULL;
	m_pID_CHECKBOX_countryA_B = NULL;
	m_pID_CHECKBOX_countryB_B = NULL;
	m_pID_CHECKBOX_countryB_C = NULL;
	m_pID_CHECKBOX_countryB_A = NULL;

	m_BagItemSum = 0;
	m_StepLogTime =0;
	m_IsUse = false;
	m_CountryID = 0;
	m_ACountryID = 0;
	m_BCountryID = 0;
	m_ItemID = 0;
	m_ItemSum = 0;
}
// Frame
bool CUI_ID_FRAME_changecountry::OnFrameRun()
{
	OnUpdate();
	return true;
}
bool CUI_ID_FRAME_changecountry::OnFrameRender()
{
	return true;
}
// CheckBox
void CUI_ID_FRAME_changecountry::ID_CHECKBOX_countryA_AOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!((ControlCheckBox*)pSender)->IsChecked())
		((ControlCheckBox*)pSender)->SetCheck(true);
	SetChecked(pSender);
	OnCheckCountry(m_ACountryID);
}
// Button
bool CUI_ID_FRAME_changecountry::ID_BUTTON_changecountryOnButtonClick( ControlObject* pSender )
{
	if(OnChangeCountry())
		SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_changecountry::ID_BUTTON_canelOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_changecountry::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_changecountry::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_changecountry::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_changecountry::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// CheckBox
void CUI_ID_FRAME_changecountry::ID_CHECKBOX_countryA_COnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!((ControlCheckBox*)pSender)->IsChecked())
		((ControlCheckBox*)pSender)->SetCheck(true);
	SetChecked(pSender);
	OnCheckCountry(m_ACountryID);
}
// CheckBox
void CUI_ID_FRAME_changecountry::ID_CHECKBOX_countryA_BOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!((ControlCheckBox*)pSender)->IsChecked())
		((ControlCheckBox*)pSender)->SetCheck(true);
	SetChecked(pSender);
	OnCheckCountry(m_ACountryID);
}
// CheckBox
void CUI_ID_FRAME_changecountry::ID_CHECKBOX_countryB_BOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!((ControlCheckBox*)pSender)->IsChecked())
		((ControlCheckBox*)pSender)->SetCheck(true);
	SetChecked(pSender);
	OnCheckCountry(m_BCountryID);
}
// CheckBox
void CUI_ID_FRAME_changecountry::ID_CHECKBOX_countryB_COnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!((ControlCheckBox*)pSender)->IsChecked())
		((ControlCheckBox*)pSender)->SetCheck(true);
	SetChecked(pSender);
	OnCheckCountry(m_BCountryID);
}
// CheckBox
void CUI_ID_FRAME_changecountry::ID_CHECKBOX_countryB_AOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!((ControlCheckBox*)pSender)->IsChecked())
		((ControlCheckBox*)pSender)->SetCheck(true);
	SetChecked(pSender);
	OnCheckCountry(m_BCountryID);
}
void CUI_ID_FRAME_changecountry::SetChecked(ControlObject* pSender)
{
	m_pID_CHECKBOX_countryA_C->SetCheck(false);
	m_pID_CHECKBOX_countryA_B->SetCheck(false);
	m_pID_CHECKBOX_countryB_B->SetCheck(false);
	m_pID_CHECKBOX_countryB_C->SetCheck(false);
	m_pID_CHECKBOX_countryB_A->SetCheck(false);
	m_pID_CHECKBOX_countryA_A->SetCheck(false);
	if(pSender)
		((ControlCheckBox*)pSender)->SetCheck(true);
}
// 装载UI
bool CUI_ID_FRAME_changecountry::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\MoveCountry.MEUI" ,false, UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\MoveCountry.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_changecountry::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_changecountry, s_CUI_ID_FRAME_changecountryOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_changecountry, s_CUI_ID_FRAME_changecountryOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_changecountry, ID_CHECKBOX_countryA_A, s_CUI_ID_FRAME_changecountryID_CHECKBOX_countryA_AOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_changecountry, ID_BUTTON_changecountry, s_CUI_ID_FRAME_changecountryID_BUTTON_changecountryOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_changecountry, ID_BUTTON_canel, s_CUI_ID_FRAME_changecountryID_BUTTON_canelOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_changecountry, ID_LISTIMG_Material, s_CUI_ID_FRAME_changecountryID_LISTIMG_MaterialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_changecountry, ID_LISTIMG_Material, s_CUI_ID_FRAME_changecountryID_LISTIMG_MaterialOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_changecountry, ID_LISTIMG_Material, s_CUI_ID_FRAME_changecountryID_LISTIMG_MaterialOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_changecountry, ID_LISTIMG_Material, s_CUI_ID_FRAME_changecountryID_LISTIMG_MaterialOnIconRButtonUp );
	theUiManager.OnCheckBoxCheck( ID_FRAME_changecountry, ID_CHECKBOX_countryA_C, s_CUI_ID_FRAME_changecountryID_CHECKBOX_countryA_COnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_changecountry, ID_CHECKBOX_countryA_B, s_CUI_ID_FRAME_changecountryID_CHECKBOX_countryA_BOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_changecountry, ID_CHECKBOX_countryB_B, s_CUI_ID_FRAME_changecountryID_CHECKBOX_countryB_BOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_changecountry, ID_CHECKBOX_countryB_C, s_CUI_ID_FRAME_changecountryID_CHECKBOX_countryB_COnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_changecountry, ID_CHECKBOX_countryB_A, s_CUI_ID_FRAME_changecountryID_CHECKBOX_countryB_AOnCheckBoxCheck );

	m_pID_FRAME_changecountry = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_changecountry );
	m_pID_CHECKBOX_countryA_A = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_changecountry, ID_CHECKBOX_countryA_A );
	m_pID_TEXT_countryAStrong = (ControlText*)theUiManager.FindControl( ID_FRAME_changecountry, ID_TEXT_countryAStrong );
	m_pID_TEXT_countryBStrong = (ControlText*)theUiManager.FindControl( ID_FRAME_changecountry, ID_TEXT_countryBStrong );
	m_pID_BUTTON_changecountry = (ControlButton*)theUiManager.FindControl( ID_FRAME_changecountry, ID_BUTTON_changecountry );
	m_pID_BUTTON_canel = (ControlButton*)theUiManager.FindControl( ID_FRAME_changecountry, ID_BUTTON_canel );
	m_pID_TEXT_itemname = (ControlText*)theUiManager.FindControl( ID_FRAME_changecountry, ID_TEXT_itemname );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_changecountry, ID_LISTIMG_Material );
	m_pID_CHECKBOX_countryA_C = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_changecountry, ID_CHECKBOX_countryA_C );
	m_pID_CHECKBOX_countryA_B = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_changecountry, ID_CHECKBOX_countryA_B );
	m_pID_CHECKBOX_countryB_B = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_changecountry, ID_CHECKBOX_countryB_B );
	m_pID_CHECKBOX_countryB_C = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_changecountry, ID_CHECKBOX_countryB_C );
	m_pID_CHECKBOX_countryB_A = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_changecountry, ID_CHECKBOX_countryB_A );
	assert( m_pID_FRAME_changecountry );
	assert( m_pID_CHECKBOX_countryA_A );
	assert( m_pID_TEXT_countryAStrong );
	assert( m_pID_TEXT_countryBStrong );
	assert( m_pID_BUTTON_changecountry );
	assert( m_pID_BUTTON_canel );
	assert( m_pID_TEXT_itemname );
	assert( m_pID_LISTIMG_Material );
	assert( m_pID_CHECKBOX_countryA_C );
	assert( m_pID_CHECKBOX_countryA_B );
	assert( m_pID_CHECKBOX_countryB_B );
	assert( m_pID_CHECKBOX_countryB_C );
	assert( m_pID_CHECKBOX_countryB_A );

	m_pID_CHECKBOX_countryA_C->SetVisable(false);
	m_pID_CHECKBOX_countryA_B->SetVisable(false);
	m_pID_CHECKBOX_countryB_B->SetVisable(false);
	m_pID_CHECKBOX_countryB_C->SetVisable(false);
	m_pID_CHECKBOX_countryB_A->SetVisable(false);
	m_pID_CHECKBOX_countryA_A->SetVisable(false);
	m_pID_BUTTON_changecountry->SetEnable(false);

	m_pID_FRAME_changecountry->SetOnVisibleChangedFun( OnVisibleChange );
	m_IsUse=false;
	return true;
}
	// 卸载UI
bool CUI_ID_FRAME_changecountry::_UnLoadUI()
{
	m_pID_FRAME_changecountry = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\MoveCountry.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_changecountry::_IsVisable()
{
	return m_pID_FRAME_changecountry->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_changecountry::_SetVisable( const bool bVisable )
{
	uint8 CountryID = thePlayerRole.GetCountry();
	if(CountryID == CountryDefine::Country_Init)
		return;
	if(bVisable)
		OnInit();
	else
		SetEmpty();
	m_pID_FRAME_changecountry->SetVisable( bVisable );
}
bool CUI_ID_FRAME_changecountry::IsPackItemBeUsing( __int64 nGuid )
{
	if(!IsVisable())
        return false;
	if(!m_IsUse)
		return false;
	SCharItem  pItems;
	thePlayerRole.m_bagMaterial.GetItemByOnlyeID(nGuid,&pItems);
	if(pItems.itembaseinfo.ustItemID == m_ItemID)
		return true;
	else
		return false;
}
void CUI_ID_FRAME_changecountry::SetCountry(uint8 CountryID)
{
	//根据国家ID 设置Ui上国家的展示
	m_pID_CHECKBOX_countryA_C->SetVisable(false);
	m_pID_CHECKBOX_countryA_B->SetVisable(false);
	m_pID_CHECKBOX_countryB_B->SetVisable(false);
	m_pID_CHECKBOX_countryB_C->SetVisable(false);
	m_pID_CHECKBOX_countryB_A->SetVisable(false);
	m_pID_CHECKBOX_countryA_A->SetVisable(false);

	if(CountryID == CountryDefine::Country_Init)
		return;
	int index = 0;
	for(int i =1;i<CountryDefine::Country_Max;++i)
	{
		if(i == CountryID)
			continue;
		if(index == 0)
		{
			switch(i)
			{
			case CountryDefine::Country_LouLan:
				m_pID_CHECKBOX_countryA_A->SetVisable(true);
				break;
			case CountryDefine::Country_KunLun:
				m_pID_CHECKBOX_countryA_B->SetVisable(true);
				break;
			case CountryDefine::Country_DunHuang:
				m_pID_CHECKBOX_countryA_C->SetVisable(true);
				break;
			}
			if(thePlayerRole.GetWeakCountryID() == i)
				m_pID_TEXT_countryAStrong->SetText(theXmlString.GetString(eText_Country_Weak));
			else if(thePlayerRole.GetStrongthCountryID() == i)
				m_pID_TEXT_countryAStrong->SetText(theXmlString.GetString(eText_Country_Strongth));
			else
				m_pID_TEXT_countryAStrong->SetText(theXmlString.GetString(eText_Country_Normal));
			++index;
			m_ACountryID = i;
		}
		else
		{
			switch(i)
			{
			case CountryDefine::Country_LouLan:
				m_pID_CHECKBOX_countryB_A->SetVisable(true);
				break;
			case CountryDefine::Country_KunLun:
				m_pID_CHECKBOX_countryB_B->SetVisable(true);
				break;
			case CountryDefine::Country_DunHuang:
				m_pID_CHECKBOX_countryB_C->SetVisable(true);
				break;
			}
			if(thePlayerRole.GetWeakCountryID() == i)
				m_pID_TEXT_countryBStrong->SetText(theXmlString.GetString(eText_Country_Weak));
			else if(thePlayerRole.GetStrongthCountryID() == i)
				m_pID_TEXT_countryBStrong->SetText(theXmlString.GetString(eText_Country_Strongth));
			else
				m_pID_TEXT_countryBStrong->SetText(theXmlString.GetString(eText_Country_Normal));
			++index;
			m_BCountryID = i;
			break;
		}
	}
}
void CUI_ID_FRAME_changecountry::OnInit()
{
	uint8 CountryID = thePlayerRole.GetCountry();
	if(CountryID == CountryDefine::Country_Init)
		return;
	SetCountry(CountryID);
	m_pID_BUTTON_changecountry->SetEnable(false);
}
void CUI_ID_FRAME_changecountry::OnCheckCountry(uint8 CountryID)
{
	//当玩家选择一个国家的时候 
	//1.获取需要的移民符的数量
	m_CountryID = CountryID;
	m_pID_BUTTON_changecountry->SetEnable(true);
	m_ItemID = theChangeCountryConfig.GetItemID(thePlayerRole.GetCountry(),CountryID,thePlayerRole.GetWeakCountryID(),thePlayerRole.GetStrongthCountryID());
	m_ItemSum =  theChangeCountryConfig.GetItemSum(thePlayerRole.GetCountry(),CountryID,thePlayerRole.GetWeakCountryID(),thePlayerRole.GetStrongthCountryID());
	if(m_ItemID == 0 || m_ItemSum == 0)
		return;
	int sum =thePlayerRole.m_bagMaterial.GetItemCount(m_ItemID);
	m_BagItemSum = sum;
	ControlIconDrag::S_ListImg pItems;
	pItems.SetData(m_ItemID,sum);
	if(sum == 0)
		pItems.SetEnable(eIcon_Disable);
	else
		pItems.SetEnable(eIcon_Enable);
	m_pID_LISTIMG_Material->SetItem(&pItems,0);
	//设置好物品的名称
	ItemDefine::SItemCommon* pItemCommon_s = GettheItemDetail().GetItemByID( m_ItemID);
	if(pItemCommon_s)
	{
		char szText[24] = {0};
		sprintf_s(szText, sizeof(szText)-1,"%s X%u",pItemCommon_s->GetItemName(),m_ItemSum);
		m_pID_TEXT_itemname->SetText(szText);//物品的名称
	}
	if(sum < m_ItemSum)
		m_pID_BUTTON_changecountry->SetEnable(false);
	//让背包的物品灰起来
	m_IsUse =true;
	int BagSize = thePlayerRole.m_bagMaterial.GetNowBagSize();
	for(int i =0;i<BagSize;++i)
	{
		SCharItem * pItem = thePlayerRole.m_bagMaterial.GetCharItemFromIdx(i);
		if(!pItem || pItem->itembaseinfo.ustItemID !=m_ItemID || m_ItemID == 0) continue;
		CPackItemEnableManager::Instance()->RefreshBagItemEnable(&thePlayerRole.m_bagMaterial,i,true);
	}
}
void CUI_ID_FRAME_changecountry::OnUpdate()
{
	//当继续更新的时候
	//1.当背包的移民符数量发生变化的时候
	if(!IsVisable() || m_ItemID == 0) return;
	if(HQ_TimeGetTime() - m_StepLogTime < 1000) return;//1秒更新一次
	int sum =thePlayerRole.m_bagMaterial.GetItemCount(m_ItemID);
	if(sum != m_BagItemSum)
	{
		m_BagItemSum = sum;
		ControlIconDrag::S_ListImg pItems;
		pItems.SetData(m_ItemID,sum);
		if(sum == 0)
			pItems.SetEnable(eIcon_Disable);
		else
			pItems.SetEnable(eIcon_Enable);
		m_pID_LISTIMG_Material->SetItem(&pItems,0);
		if(sum >= m_ItemSum)
			m_pID_BUTTON_changecountry->SetEnable(true);
		else
			m_pID_BUTTON_changecountry->SetEnable(false);
		//让背包的物品灰起来
		m_IsUse = true;
		int BagSize = thePlayerRole.m_bagMaterial.GetNowBagSize();
		for(int i =0;i<BagSize;++i)
		{
			SCharItem * pItem = thePlayerRole.m_bagMaterial.GetCharItemFromIdx(i);
			if(!pItem || pItem->itembaseinfo.ustItemID !=m_ItemID || m_ItemID == 0) continue;
			CPackItemEnableManager::Instance()->RefreshBagItemEnable(&thePlayerRole.m_bagMaterial,i,true);
		}
	}
	m_StepLogTime = HQ_TimeGetTime();
}
void CUI_ID_FRAME_changecountry::SetEmpty()
{
	//设置背包物品亮起来
	m_IsUse = false;
	int BagSize = thePlayerRole.m_bagMaterial.GetNowBagSize();
	for(int i =0;i<BagSize;++i)
	{
		SCharItem * pItem = thePlayerRole.m_bagMaterial.GetCharItemFromIdx(i);
		if(!pItem || pItem->itembaseinfo.ustItemID !=m_ItemID || m_ItemID == 0) continue;
		CPackItemEnableManager::Instance()->RefreshBagItemEnable(&thePlayerRole.m_bagMaterial,i,true);
	}
	//清空UI上的材料图标和 一些数据
	ControlIconDrag::S_ListImg pItems;
	pItems.SetData(0,0);
	m_pID_LISTIMG_Material->SetItem(&pItems,0);
	m_pID_BUTTON_changecountry->SetEnable(false);
	m_pID_TEXT_itemname->SetText("");

	m_pID_CHECKBOX_countryA_C->SetCheck(false);
	m_pID_CHECKBOX_countryA_B->SetCheck(false);
	m_pID_CHECKBOX_countryB_B->SetCheck(false);
	m_pID_CHECKBOX_countryB_C->SetCheck(false);
	m_pID_CHECKBOX_countryB_A->SetCheck(false);
	m_pID_CHECKBOX_countryA_A->SetCheck(false);

	m_CountryID = 0;
	m_BagItemSum= 0;
	m_ACountryID= 0;
	m_BCountryID= 0;
	m_ItemID= 0;
	m_ItemSum= 0;
	m_StepLogTime= 0;
}
bool CUI_ID_FRAME_changecountry::OnChangeCountry()
{
	//移民
	if(m_CountryID == CountryDefine::Country_Init)
	{
		s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult(MsgCountryChangeAck::ECD_ErrorCountry);
		return false;
	}
	else if(m_CountryID == thePlayerRole.GetCountry())
	{
		//不可以选择同一国家
		s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult(MsgCountryChangeAck::ECD_SameCountry);
		return false;
	}
	else if(thePlayerRole.GetGroupId() != -1)
	{
		//提示玩家有队伍 无法叛国
		s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult(MsgCountryChangeAck::ECD_HaveTeam);
		return false;
	}
	bool isCreTeacher = false;
	int studentSum = 0;
	thePlayerRole.CalculateTeacherStudent(isCreTeacher,studentSum);
	if(isCreTeacher)
	{
		//有师傅 不可以叛国
		s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult(MsgCountryChangeAck::ECD_HaveTeacher);
		return false;
	}
	if(studentSum >0)
	{
		//有徒弟 不可以叛国
		s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult(MsgCountryChangeAck::ECD_HaveStudent);
		return false;
	}
	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if(pGuild && pGuild->GetGuildID() != GuildDefine::InitID) 
	{
		//有帮派 
		s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult(MsgCountryChangeAck::ECD_HaveGuild);
		return false;
	}
	if(thePlayerRole.GetCharInfo2().baseinfo.liveinfo.uchPosition)
	{
		//有官职在身 无法叛国
		s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult(MsgCountryChangeAck::ECD_HaveOff);
		return false;
	}
	//判断等级
	if(theChangeCountryConfig.GetMaxLevel() !=-1 && theChangeCountryConfig.GetMaxLevel() < thePlayerRole.GetLevel())
	{
		s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult(MsgCountryChangeAck::ECD_MaxLevel);
		return false;
	}
	if(theChangeCountryConfig.GetMinLevel() !=-1 && theChangeCountryConfig.GetMinLevel() > thePlayerRole.GetLevel())
	{
		s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult(MsgCountryChangeAck::ECD_MinLevel);
		return false;
	}
	//判断物品数量
	int sum =thePlayerRole.m_bagMaterial.GetItemCount(m_ItemID);
	if(sum < m_ItemSum)
	{
		s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult(MsgCountryChangeAck::ECD_Item);
		return false;
	}
	MsgCountryChangeReq msg;	
	msg.uchCountryID = m_CountryID;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

void CUI_ID_FRAME_changecountry::OnVisibleChange( ControlObject* pUIObject )
{
	if(pUIObject->IsVisable()) return;
	s_CUI_ID_FRAME_changecountry.SetEmpty();
}