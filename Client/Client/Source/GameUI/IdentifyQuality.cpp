#include <assert.h>
#include "MeUi/UiManager.h"
#include "IdentifyQuality.h"
#include "Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Pack.h"
#include "PackItemEnableManager.h"
#include "EquipEvolveConfig.h"
#include "ScreenInfoManager.h"
#include "Pack.h"
#include "RandPropertyEvaluate.h"

#define DELAY_TIME 350

CUI_ID_FRAME_IdentifyQuality s_CUI_ID_FRAME_IdentifyQuality;
MAP_FRAME_RUN( s_CUI_ID_FRAME_IdentifyQuality, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_IdentifyQuality, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_IdentifyQuality, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_IdentifyQuality, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_IdentifyQuality, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_IdentifyQuality, ID_BUTTON_OkOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_IdentifyQuality, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_IdentifyQuality, ID_LISTIMG_ArmourOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_IdentifyQuality, ID_LISTIMG_ArmourOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_IdentifyQuality, ID_LISTIMG_ArmourOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_IdentifyQuality, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_IdentifyQuality, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_IdentifyQuality, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_IdentifyQuality, ID_LISTIMG_MaterialOnIconRButtonUp )

CUI_ID_FRAME_IdentifyQuality::CUI_ID_FRAME_IdentifyQuality()
{
	// Member
	m_pID_FRAME_IdentifyQuality = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Ok = NULL;	
	m_pID_LISTIMG_Armour = NULL;
	m_PID_LIST_Introduce = NULL;
	m_status = EquipEvolveUI::EffectStatus_No;
	m_pID_TEXT_Effect = NULL;
	m_pID_TEXT_Success = NULL;
	m_pID_TEXT_Fail = NULL;
	dwBeginTime = 0;
	m_bSendMsg = false;

	m_MaterialBagIndex = -1;
	m_MaterialBagGuide = 0;
	m_pID_LISTIMG_Material = NULL;
	m_pID_TEXT_Material_NotEnougth = NULL;
	m_pID_TEXT_EquipName = NULL;
	m_pID_TEXT_MaterialName = NULL;

}

// Frame
bool CUI_ID_FRAME_IdentifyQuality::OnFrameRun()
{
	//bool bOkEnable = m_pID_BUTTON_Ok->IsEnable();
	DWORD timenow = timeGetTime();
	switch (m_status)
	{
	case EquipEvolveUI::EffectStatus_Start:
		if (timenow-dwBeginTime>=DELAY_TIME && m_bSendMsg )
		{
			if (SendIdentifyMsg())
			{
				m_pID_BUTTON_Ok->SetEnable(false);
			}
			m_bSendMsg = false;
		}
		else
		{
			m_pID_BUTTON_Ok->SetEnable(false);
			if (m_pID_TEXT_Effect)
			{
				m_pID_TEXT_Effect->SetVisable(true);
			}
			if (m_pID_TEXT_Success)
			{
				m_pID_TEXT_Success->SetVisable(false);
			}
			if (m_pID_TEXT_Fail)
			{
				m_pID_TEXT_Fail->SetVisable(false);
			}
		}
		break;
	case EquipEvolveUI::EffectStatus_Fail:
		//m_pID_BUTTON_Ok->SetEnable(true);
		if(m_pID_TEXT_Fail) m_pID_TEXT_Fail->SetVisable(true);
		if(m_pID_TEXT_Success) m_pID_TEXT_Success->SetVisable(false);
		if(m_pID_TEXT_Effect) m_pID_TEXT_Effect->SetVisable(false);
		if(timenow-dwBeginTime>=DELAY_TIME)
			m_status = EquipEvolveUI::EffectStatus_No;
		m_bSendMsg = false;
		break;
	case EquipEvolveUI::EffectStatus_Success:
		//m_pID_BUTTON_Ok->SetEnable(true);
		if(m_pID_TEXT_Success) m_pID_TEXT_Success->SetVisable(true);
		if(m_pID_TEXT_Fail) m_pID_TEXT_Fail->SetVisable(false);
		if(m_pID_TEXT_Effect) m_pID_TEXT_Effect->SetVisable(false);
		if(timenow-dwBeginTime>=DELAY_TIME) 
			m_status = EquipEvolveUI::EffectStatus_No;
		m_bSendMsg = false;
		break;
	case EquipEvolveUI::EffectStatus_No:
		//m_pID_BUTTON_Ok->SetEnable(true);
		if(m_pID_TEXT_Success) m_pID_TEXT_Success->SetVisable(false);
		if(m_pID_TEXT_Fail) m_pID_TEXT_Fail->SetVisable(false);
		if(m_pID_TEXT_Effect) m_pID_TEXT_Effect->SetVisable(false);
		m_bSendMsg = false;
		break;
	}
	return true;
}

bool CUI_ID_FRAME_IdentifyQuality::OnFrameRender()
{
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
	if (!pMe )
		return true;

	Vector vPos;
	pMe->GetPos( &vPos.x, &vPos.y, &vPos.z );
	if(IsOverDistance(vPos))
		SetVisable(false);

	return true;
}

// Button
bool CUI_ID_FRAME_IdentifyQuality::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}

// Button
bool CUI_ID_FRAME_IdentifyQuality::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	return true;
}

// Button
bool CUI_ID_FRAME_IdentifyQuality::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	return true;
}

// Button
bool CUI_ID_FRAME_IdentifyQuality::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_IdentifyQuality)
		return false;
	//判断是否需要对装备进行绑定
	


	dwBeginTime = timeGetTime();
	m_status = EquipEvolveUI::EffectStatus_Start;
	m_bSendMsg = true;
	//SendIdentifyMsg();
	return true;
}

// ListImg / ListEx
bool CUI_ID_FRAME_IdentifyQuality::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																 ControlIconDrag::S_ListImg* pItemDrag,
																 ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!pSender)
		return false;

	if(!pItemDrag)
		return false;

	EquipEvolveConfig::SEquipUnknowIdentify *pIdentify = theEquipEvolveConfig.GetUnknowIdentify(pItemDrag->m_pkIconInfo->Id());
	if(!pIdentify)
	{
		CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Identify, theXmlString.GetString(eText_EquipNoIdentity));
		return false;
	}

	int nIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem(BT_NormalItemBag,pItemDrag);
	if(nIndex == -1)
		return false;

	int nOldIndex = m_stBagIndex;
	__int64 stOldEquipGuid = m_stEquipBagGuid;
	Clear();
	if(stOldEquipGuid != 0)
	{
		CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, nOldIndex, true );
		theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
	}

	m_pID_LISTIMG_Armour->Clear();
	m_pID_LISTIMG_Armour->SetItem(pItemDrag,0);
	m_pID_LISTIMG_Armour->GetItemByIndex(0)->m_pkIconInfo->Count() = 1;
	m_pID_LISTIMG_Armour->GetItemByIndex(0)->m_eEnable             = eIcon_Enable;

	m_stEquipBagGuid = pItemDrag->m_pkIconInfo->GetOnlyId();
	m_stBagIndex = nIndex;

	CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, nIndex, true );

	theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
	RefreshMoney(pIdentify->nCostValue);
	ItemDefine::SItemCommon *pCommon = GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->Id());
	RefreshEquipQuility(pCommon);
	ShowMaterialIcon();
	RefreshOKButton();

	return false;
}

bool CUI_ID_FRAME_IdentifyQuality::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_IdentifyQuality::ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_IdentifyQuality::ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	int nIndex = m_stBagIndex; 
	Clear();

	CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, nIndex, true );
	theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_IdentifyQuality::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																   ControlIconDrag::S_ListImg* pItemDrag,
																   ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}

bool CUI_ID_FRAME_IdentifyQuality::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_IdentifyQuality::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_IdentifyQuality::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}


// 装载UI
bool CUI_ID_FRAME_IdentifyQuality::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\IdentifyQuality.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\IdentifyQuality.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_IdentifyQuality::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_IdentifyQuality, s_CUI_ID_FRAME_IdentifyQualityOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_IdentifyQuality, s_CUI_ID_FRAME_IdentifyQualityOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_IdentifyQuality, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_IdentifyQualityID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_IdentifyQuality, ID_BUTTON_HELP, s_CUI_ID_FRAME_IdentifyQualityID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_IdentifyQuality, ID_BUTTON_Cancel, s_CUI_ID_FRAME_IdentifyQualityID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_IdentifyQuality, ID_BUTTON_Ok, s_CUI_ID_FRAME_IdentifyQualityID_BUTTON_OkOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_IdentifyQuality, ID_LISTIMG_Armour, s_CUI_ID_FRAME_IdentifyQualityID_LISTIMG_ArmourOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_IdentifyQuality, ID_LISTIMG_Armour, s_CUI_ID_FRAME_IdentifyQualityID_LISTIMG_ArmourOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_IdentifyQuality, ID_LISTIMG_Armour, s_CUI_ID_FRAME_IdentifyQualityID_LISTIMG_ArmourOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_IdentifyQuality, ID_LISTIMG_Armour, s_CUI_ID_FRAME_IdentifyQualityID_LISTIMG_ArmourOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_IdentifyQuality, ID_LISTIMG_Material, s_CUI_ID_FRAME_IdentifyQualityID_LISTIMG_MaterialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_IdentifyQuality, ID_LISTIMG_Material, s_CUI_ID_FRAME_IdentifyQualityID_LISTIMG_MaterialOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_IdentifyQuality, ID_LISTIMG_Material, s_CUI_ID_FRAME_IdentifyQualityID_LISTIMG_MaterialOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_IdentifyQuality, ID_LISTIMG_Material, s_CUI_ID_FRAME_IdentifyQualityID_LISTIMG_MaterialOnIconRButtonUp );

	m_pID_FRAME_IdentifyQuality = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_IdentifyQuality );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_IdentifyQuality, ID_BUTTON_CLOSE );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_IdentifyQuality, ID_BUTTON_HELP );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_IdentifyQuality, ID_TEXT_Money );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_IdentifyQuality, ID_BUTTON_Cancel );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_IdentifyQuality, ID_BUTTON_Ok );
	m_pID_LISTIMG_Armour = (ControlListImage*)theUiManager.FindControl( ID_FRAME_IdentifyQuality, ID_LISTIMG_Armour );
	m_PID_LIST_Introduce     = (ControlList*)theUiManager.FindControl(ID_FRAME_IdentifyQuality,ID_LIST_Introduce);
	m_pID_TEXT_Effect = (ControlText*)theUiManager.FindControl( ID_FRAME_IdentifyQuality, ID_TEXT_Effect );
	m_pID_TEXT_Success = (ControlText*)theUiManager.FindControl( ID_FRAME_IdentifyQuality, ID_TEXT_Success );
	m_pID_TEXT_Fail = (ControlText*)theUiManager.FindControl( ID_FRAME_IdentifyQuality, ID_TEXT_Fail );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_IdentifyQuality, ID_LISTIMG_Material );
	m_pID_TEXT_Material_NotEnougth = (ControlText*)theUiManager.FindControl( ID_FRAME_IdentifyQuality, ID_TEXT_Material_NotEnougth );
	m_pID_TEXT_EquipName = (ControlText*)theUiManager.FindControl( ID_FRAME_IdentifyQuality, ID_TEXT_EquipName );
	m_pID_TEXT_MaterialName = (ControlText*)theUiManager.FindControl( ID_FRAME_IdentifyQuality, ID_TEXT_MaterialName );
	
	assert(m_PID_LIST_Introduce);
	assert( m_pID_FRAME_IdentifyQuality );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_TEXT_Money );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_TEXT_Success );
	assert( m_pID_TEXT_Fail );
	assert( m_pID_LISTIMG_Material );
	assert( m_pID_TEXT_Material_NotEnougth );
	assert( m_pID_LISTIMG_Armour );
	assert( m_pID_TEXT_EquipName );
	assert( m_pID_TEXT_MaterialName );

	m_PID_LIST_Introduce->HaveSelBar( false, LIST_NOTSHOWBAR );
	m_pID_FRAME_IdentifyQuality->SetOnVisibleChangedFun(OnVisibleChange);
	m_pID_BUTTON_Ok->SetEnable(false);
	m_pID_TEXT_Material_NotEnougth->SetVisable(false);
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_IdentifyQuality::_UnLoadUI()
{
	m_pID_FRAME_IdentifyQuality = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\IdentifyQuality.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_IdentifyQuality::_IsVisable()
{
	if(!m_pID_FRAME_IdentifyQuality)
		return false;

	return m_pID_FRAME_IdentifyQuality->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_IdentifyQuality::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_IdentifyQuality)
		return;

	m_pID_FRAME_IdentifyQuality->SetVisable( bVisable );
	if (bVisable)
	{
		s_CUI_ID_FRAME_PACK.SetVisable(bVisable);
		ResetWindowPosition(m_pID_FRAME_IdentifyQuality, s_CUI_ID_FRAME_PACK.GetFrame());
	}
	m_pID_TEXT_Material_NotEnougth->SetVisable(false);
}

bool CUI_ID_FRAME_IdentifyQuality::IsPackItemBeUsing( __int64 nGuid )
{
	if( !IsVisable() || nGuid <= 0 )
		return false;

	if (m_stEquipBagGuid == nGuid)
		return true;
	if (m_MaterialBagGuide == nGuid)
		return true;

	return false;
}

void CUI_ID_FRAME_IdentifyQuality::Clear()
{
	if(!m_pID_FRAME_IdentifyQuality)
		return;

	m_pID_TEXT_Money->SetText(0);
	
	m_pID_LISTIMG_Armour->Clear();
	m_PID_LIST_Introduce->Clear();
	RefreshMoney(0);
	RefreshEquipQuility(NULL);

	ClearMaterialIcon();
	RefreshOKButton();

	m_stEquipBagGuid = 0;
    m_stBagIndex  = 0;
}

void CUI_ID_FRAME_IdentifyQuality::SetVisiblePosition(const Vector &vPos)
{
	m_vVisualPos.x = vPos.x;
	m_vVisualPos.y = vPos.y;
	m_vVisualPos.z = vPos.z;
}

bool CUI_ID_FRAME_IdentifyQuality::IsOverDistance(const Vector& vCurPos)
{
	float xoff = vCurPos.x - m_vVisualPos.x;
	float yoff = vCurPos.y - m_vVisualPos.y;
	float fDist = sqrtf( xoff*xoff + yoff*yoff );
	return (fDist > 12.0f);
}

void CUI_ID_FRAME_IdentifyQuality::RefreshMoney(int nMoney)
{
	if(!m_pID_FRAME_IdentifyQuality)
		return;

	std::string strText;
	strText.clear();

	thePlayerRole.GetGSCStringFromJiaoZi(nMoney,strText);
	DWORD dwColor = 0xffffffff;
	if(!thePlayerRole.HaveEnoughMoney(nMoney))
		dwColor = 0xffff0000;
	
	m_pID_TEXT_Money->SetText(strText.c_str(), dwColor);
}

void CUI_ID_FRAME_IdentifyQuality::RefreshEquipQuility(ItemDefine::SItemCommon *pCommon)
{
	/*if(!pCommon)
	{
		m_PID_LIST_Introduce->Clear();
		return;
	}
	else
	{
		m_PID_LIST_Introduce->Clear();
		ControlList::S_List sList;
		sList.UseSelColor = false;		

		sList.clear();
		sList.SetData( pCommon->GetItemName(), 0, 0, S_IconInfoHero::GetQualityColor( pCommon ->ustLevel ) );
		sList.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		m_PID_LIST_Introduce->AddItem( &sList );	
		
	}*/
	if (!m_pID_TEXT_EquipName)
		return;

	if (!pCommon )
	{
		m_pID_TEXT_EquipName->SetText("");
		return;
	}

	m_pID_TEXT_EquipName->SetText(pCommon->GetItemName(), S_IconInfoHero::GetQualityColor( pCommon ->ustLevel ));
}

void CUI_ID_FRAME_IdentifyQuality::OnVisibleChange(ControlObject* pUIObject)
{
	s_CUI_ID_FRAME_IdentifyQuality.m_status = EquipEvolveUI::EffectStatus_No;
	s_CUI_ID_FRAME_IdentifyQuality.ID_LISTIMG_ArmourOnIconRButtonUp(NULL,NULL);
	s_CUI_ID_FRAME_IdentifyQuality.RefreshOKButton();
}

bool CUI_ID_FRAME_IdentifyQuality::SendIdentifyMsg()
{
	if(m_stEquipBagGuid == 0)
		return false;

	MsgEquipEvolve msgEvolve;
	msgEvolve.nEvolveType = MsgEquipEvolve::ET_UnknowIdentify;

	msgEvolve.nNormalBagIndex = m_stBagIndex;
	msgEvolve.nNormalGuid     = m_stEquipBagGuid;

	msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType= BT_MaterialBag;
	msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex = m_MaterialBagIndex;
	msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid = m_MaterialBagGuide;

	//判断是否需要进行绑定判断 装备鉴定很特殊 必须特殊处理
	bool IsNeedBounded = false;
	SCharItem pEquip;
	if(thePlayerRole.GetBagItemByGUID(msgEvolve.nNormalGuid,&pEquip))
	{
		if(pEquip.IsBounded())
			IsNeedBounded = true;
		for(int i =0;i<MsgEquipEvolve::EConstDefine_MaxMaterialCount;++i)
		{
			if(msgEvolve.materials[i].guid == 0 || msgEvolve.materials[i].guid==-1)
				continue;
			SCharItem pItem;
			if(!thePlayerRole.GetBagItemByGUID(msgEvolve.materials[i].guid,&pItem))
				continue;
			if(pItem.IsBounded())
				IsNeedBounded = true;
		}
	}
	if(IsNeedBounded)
	{
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_EquipMaterialBound), "", CUI_ID_FRAME_MessageBox::eTypeYesNo, true, MsgEquipEvolve::EquipMaterialSendMsg,&msgEvolve,msgEvolve.GetLength());
	}
	else
	{
		GettheNetworkInput().SendMsg( &msgEvolve );
	}

	//msgEvolve.SendEquipMsg();
	//GettheNetworkInput().SendMsg( &msgEvolve );
	return true;
}

void CUI_ID_FRAME_IdentifyQuality::RrefreshItem(SCharItem& m_item)
{
	if(!m_pID_FRAME_IdentifyQuality)
		return;
	ControlIconDrag::S_ListImg* pImg = s_CUI_ID_FRAME_PACK.GetItemByIndex(BT_NormalItemBag,m_item.itembaseinfo.stPacketIdx);
	//s_CUI_ID_FRAME_GemUp.ID_LISTIMG_Gem1OnIconDragOn(s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag),NULL,pImg,NULL);

	//ControlIconDrag::S_ListImg *sItem = m_pID_LISTIMG_Armour->GetItemById(m_item.itembaseinfo.ustItemID);
	
	//int nIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem(BT_NormalItemBag,sItem);
	//if(nIndex == -1)
	//	return ;

	//int nOldIndex = m_stBagIndex;
	//__int64 stOldEquipGuid = m_stEquipBagGuid;

	//if(stOldEquipGuid != 0)
//	{
//	//	CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, nOldIndex, true );
//		theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
//	}

	m_pID_LISTIMG_Armour->Clear();
	m_pID_LISTIMG_Armour->SetItem(pImg,0);
	m_pID_LISTIMG_Armour->GetItemByIndex(0)->m_pkIconInfo->Count() = 1;
	m_pID_LISTIMG_Armour->GetItemByIndex(0)->m_eEnable             = eIcon_Enable;
	m_pID_LISTIMG_Armour->GetItemByIndex(0)->SetSparkEnable(false);
// 	m_stEquipBagGuid = m_item.itembaseinfo.nOnlyInt;//pItemDrag->m_pkIconInfo->GetOnlyId();
// 	m_stBagIndex = nIndex;

	//CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, nIndex, true );

	theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
	RefreshMoney(0);
	ItemDefine::SItemCommon *pCommon = GettheItemDetail().GetItemByID(m_item.itembaseinfo.ustItemID);
	RefreshEquipQuility(pCommon);
	RefreshItemInfo(m_item);
}

void CUI_ID_FRAME_IdentifyQuality::RefreshItemInfo(SCharItem &m_item)
{
 	if (m_item.itembaseinfo.ustItemID != 0)
 	{
 		DWORD dwBlue   = 0xff06a2ff;
 		ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID(m_item.itembaseinfo.ustItemID);
 		if( !pItemCommon )
 		return;
 		ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
 		if( !pCanEquip )
 			return;
 		m_PID_LIST_Introduce->Clear();
 		ControlList::S_List sList;
 		sList.UseSelColor = false;
 		// 随机属性
 		if( pCanEquip->ucItemType != ItemDefine::ITEMTYPE_ARMOUR  && pCanEquip->ucItemType != ItemDefine::ITEMTYPE_WEAPON )
 			return;	
 
		/*sList.clear();
		sList.SetData( pItemCommon->GetItemName(), 0, 0, S_IconInfoHero::GetQualityColor( pItemCommon ->ustLevel ) );
		sList.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		m_PID_LIST_Introduce->AddItem( &sList );*/					

 		int nRandValue = 0;
 		char szTemp[256] = {0};
 		int nTipPreTextIndex = 0;
 		for (int nloop = 0; nloop < SCharItem::EConstDefine_BaseRandMaxCount; nloop++)
 		{
 			ItemDefine::SRandAttribute* pArmourRand = NULL;
 			unsigned short usRand =m_item.equipdata.baseRands[nloop];
 			if( usRand == InvalidLogicNumber )//
 			{   
 				continue;
 			}
 
 			pArmourRand = GettheItemDetail().GetRandByID(m_item.equipdata.baseRands[nloop]);
 
 			if (!pArmourRand)
 				continue;
 
 			for( int i = 0 ; i < ItemDefine::SRandAttribute::CD_TypeCount ; ++ i )
 			{
 				nRandValue = S_IconInfoHero::GetRandValueByType( pArmourRand, i );
 				if( pArmourRand->type[i] == RT_None )
 					continue;
				float intensity = GettheItemDetail().GetEquipQualityIntensity(m_item.equipdata.quality);
 				int  m_value = (float)nRandValue*intensity;
				sprintf( szTemp, "%s+%d", S_IconInfoHero::GetRandStringByType( pArmourRand->type[i] ).c_str(), m_value>0? m_value:1 );
				nTipPreTextIndex ++ ;
				sList.clear();
				sList.SetData( szTemp, 0, 0, dwBlue );
				sList.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
				m_PID_LIST_Introduce->AddItem( &sList );					
 							
 			}
 		}
 	}
}

void CUI_ID_FRAME_IdentifyQuality::RefreshOKButton()
{
	if (!m_pID_LISTIMG_Armour)
		return;
	if (!m_pID_BUTTON_Ok)
		return;

	m_pID_BUTTON_Ok->SetEnable(false);

	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Armour->GetItemByIndex(0);
	if (!pImg || pImg->IsNull())
		return;

	EquipEvolveConfig::SEquipUnknowIdentify *pIdentify = theEquipEvolveConfig.GetUnknowIdentify(pImg->m_pkIconInfo->Id());
	if(!pIdentify)
		return;

	if(!thePlayerRole.HaveEnoughMoney(pIdentify->nCostValue))
		return;

	if (m_MaterialBagIndex == -1)
		return;

	m_pID_BUTTON_Ok->SetEnable(true);
}

ControlIconDrag::S_ListImg* CUI_ID_FRAME_IdentifyQuality::RetriveMaterialImg( short itemId ,int& nIndex)
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

void CUI_ID_FRAME_IdentifyQuality::ShowMaterialIcon()
{
	if (!m_pID_LISTIMG_Armour || !m_pID_LISTIMG_Material || !m_pID_TEXT_Material_NotEnougth)
		return;
	ClearMaterialIcon();
	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Armour->GetItemByIndex(0);
	if (!pImg || pImg->IsNull())
		return;
	EquipEvolveConfig::SEquipUnknowIdentify *pIdentify = theEquipEvolveConfig.GetUnknowIdentify(pImg->m_pkIconInfo->Id());
	if(!pIdentify)
		return;

	int nBagIndex = -1;
	ControlIconDrag::S_ListImg * pListImgItem = RetriveMaterialImg(SID_Identify_Material,nBagIndex);
	ControlIconDrag::S_ListImg ImgItem;
	if (NULL == pListImgItem)
	{
		ImgItem.SetData(SID_Identify_Material,1,eIcon_Disable);
		pListImgItem = &ImgItem;
		m_pID_LISTIMG_Material->SetItem( pListImgItem );
		m_pID_TEXT_Material_NotEnougth->SetVisable(true);
	}
	else
	{
		m_pID_LISTIMG_Material->SetItem( pListImgItem );
		m_MaterialBagGuide = pListImgItem->m_pkIconInfo->GetOnlyId();
		if (nBagIndex != -1)
		{
			m_MaterialBagIndex = nBagIndex;
			CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_MaterialBagIndex, true );
		}
		
		m_pID_TEXT_Material_NotEnougth->SetVisable(false);
	}

	ShowMaterialName(pListImgItem);
}

void CUI_ID_FRAME_IdentifyQuality::ClearMaterialIcon()
{
	if (!m_pID_LISTIMG_Material || !m_pID_TEXT_Material_NotEnougth)
		return;

	m_pID_LISTIMG_Material->Clear();
	m_MaterialBagGuide = 0;

	if (m_MaterialBagIndex != -1)
		CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_MaterialBagIndex, true );
	m_MaterialBagIndex = -1;

	m_pID_TEXT_Material_NotEnougth->SetVisable(false);
	m_pID_TEXT_MaterialName->SetText("");
}

void CUI_ID_FRAME_IdentifyQuality::ShowMaterialName(ControlIconDrag::S_ListImg* pItemDrag)
{
	if (!pItemDrag || !m_pID_TEXT_MaterialName)
		return;
	m_pID_TEXT_MaterialName->SetText("");

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if (!pItemCommon)
		return;

	char temp[128] = {0};
	sprintf(temp, "%s", pItemCommon->GetItemName());

	m_pID_TEXT_MaterialName->SetText(temp);
}