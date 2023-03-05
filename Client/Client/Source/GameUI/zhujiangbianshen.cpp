/********************************************************************
Created by UIEditor.exe
FileName: F:\3Guo Client\Data\Ui\zhujiangbianshen.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "zhujiangbianshen.h"
#include "ItemHero.h"
#include "Pack.h"
#include "ItemDetail.h"
#include "PlayerRole.h"
#include "NetworkInput.h"
#include "PlayerInfoMgr.h"
#include <map>
#include <string.h>
#include "UIMgr.h"
#include "ScreenInfoManager.h"
#include "Ui/Skill.h"
#include "PackItemEnableManager.h"
#include "PlayerRole.h"
CUI_ID_FRAME_zhujiangbianshen s_CUI_ID_FRAME_zhujiangbianshen;

MAP_FRAME_RUN( s_CUI_ID_FRAME_zhujiangbianshen, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_zhujiangbianshen, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_zhujiangbianshen, ID_LISTIMG_skillOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_zhujiangbianshen, ID_LISTIMG_skillOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_zhujiangbianshen, ID_LISTIMG_skillOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_zhujiangbianshen, ID_LISTIMG_skillOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_zhujiangbianshen, ID_BUTTON_dianjiangpaiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_zhujiangbianshen, ID_BUTTON_okOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_zhujiangbianshen, ID_BUTTON_CancelOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_zhujiangbianshen, ID_LISTIMG_bianshenitemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_zhujiangbianshen, ID_LISTIMG_bianshenitemOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_zhujiangbianshen, ID_LISTIMG_bianshenitemOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_zhujiangbianshen, ID_LISTIMG_bianshenitemOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_zhujiangbianshen, ID_BUTTON_CLOSEOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_zhujiangbianshen, ID_LISTIMG_dianjiangpaiOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_zhujiangbianshen, ID_LISTIMG_dianjiangpaiOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_zhujiangbianshen, ID_LISTIMG_dianjiangpaiOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_zhujiangbianshen, ID_LISTIMG_dianjiangpaiOnIconRButtonUp )
CUI_ID_FRAME_zhujiangbianshen::CUI_ID_FRAME_zhujiangbianshen()
{
	// Member
	m_pID_FRAME_zhujiangbianshen = NULL;
	m_pID_PICTURE_zhujiangtouxiang = NULL;
	m_pID_PICTURE_nameLV = NULL;
	m_pID_TEXT_jieshao = NULL;
	m_pID_PICTURE_ability = NULL;
	m_pID_LISTIMG_skill = NULL;
	m_pID_BUTTON_dianjiangpai = NULL;
	m_pID_TEXT_money = NULL;
	m_pID_TEXT_needLV = NULL;
	m_pID_BUTTON_ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_LISTIMG_bianshenitem = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_PICTURE_warability = NULL;
	m_pID_LISTIMG_dianjiangpai = NULL;
	OnlyItemID = 0;
}
// Frame
bool CUI_ID_FRAME_zhujiangbianshen::OnFrameRun()
{
	if(!IsVisable() && OnlyItemID !=0)
	{
		clear();
	}
	return true;
}
bool CUI_ID_FRAME_zhujiangbianshen::OnFrameRender()
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_zhujiangbianshen::ID_LISTIMG_skillOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																 ControlIconDrag::S_ListImg* pItemDrag,
																 ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_zhujiangbianshen::ID_LISTIMG_skillOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_zhujiangbianshen::ID_LISTIMG_skillOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_zhujiangbianshen::ID_LISTIMG_skillOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_zhujiangbianshen::ID_LISTIMG_dianjiangpaiOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																 ControlIconDrag::S_ListImg* pItemDrag,
																 ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_zhujiangbianshen::ID_LISTIMG_dianjiangpaiOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_zhujiangbianshen::ID_LISTIMG_dianjiangpaiOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_zhujiangbianshen::ID_LISTIMG_dianjiangpaiOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// Button
bool CUI_ID_FRAME_zhujiangbianshen::ID_BUTTON_dianjiangpaiOnButtonClick( ControlObject* pSender )
{
	
	return true;
}

bool IFSendMsg(char bSend, void *pData )
{
	if( !bSend )
		return false;

	s_CUI_ID_FRAME_zhujiangbianshen.SendMsg();
	return true;
}
// Button
bool CUI_ID_FRAME_zhujiangbianshen::ID_BUTTON_okOnButtonClick( ControlObject* pSender )
{
	//todo:send msg to server
	//msg type

	CItemHero::SItemHero *hero = theItemHero.FindHeroByItemID(s_CUI_ID_FRAME_zhujiangbianshen.item_id);
	if (hero == NULL)
		return false;

	if ( hero->hero_sex != thePlayerRole.GetSex() && (hero->hero_sex == 1 || hero->hero_sex ==0) )
	{
		CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_Server_UseItem_Error,
			theXmlString.GetString(eText_ZhuJiangSexErro) );
		return false;
	}
	CItemBag2* pBag = 0;
	ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID(hero->material_id);
	if (!pItemDetail)
		return false;
	switch (thePlayerRole.GetBagTypeByItemType(pItemDetail->ucItemType))
	{
	case BT_NormalItemBag:
		pBag = &thePlayerRole.m_bag;
		break;
	case BT_MaterialBag:
		pBag = &thePlayerRole.m_bagMaterial;
		break;
	case BT_TaskBag:
		pBag = &thePlayerRole.m_bagTask;
		break;
	default:
		pBag = &thePlayerRole.m_bag;
		break;
	}

	if (pBag->GetItemCount(hero->material_id) < hero->material_count)
	{
		CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_Server_UseItem_Error,
			theXmlString.GetString(eText_ZhuJiangMaterial_NoEnough) );
		return false;
	}
 
	if(thePlayerRole.GetLevel()< hero->need_lv)  //等级不足
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Relive_Belongs, theXmlString.GetString( eText_LevelNotmeet ) );
		return false;
	}

	DWORD HeroHaveMoney = thePlayerRole.GetData(CPlayerRole::TYPE_JiaoZi) + thePlayerRole.m_charinfo.baseinfo.liveinfo.dwMoney;
	if (HeroHaveMoney < hero->need_money) //金钱不足
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Relive_Belongs, theXmlString.GetString( eText_Error_NotEnoughMoney ) );
		return false;
	}

	bool bBounded = false;
	SCharItem item;
	if (pBag->GetItemByItemID(item_id, &item))
	{
		if (!item.IsBounded())
			bBounded = true;
	}

	if (bBounded)
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_BianShen_Bound), "",
		CUI_ID_FRAME_MessageBox::eTypeYesNo, true, IFSendMsg);
	else
		SendMsg();
	
	return true;
}

void CUI_ID_FRAME_zhujiangbianshen::SendMsg()
{
	MsgC2GAskBianShen msg;

	CItemHero::SItemHero *hero = theItemHero.FindHeroByItemID(s_CUI_ID_FRAME_zhujiangbianshen.item_id);
	if (!hero)
		return;

	msg.hero_id = hero->hero_id;
	msg.nItemIndex = nItemIndex;
	GettheNetworkInput().SendMsg(&msg);
}
// Button
bool CUI_ID_FRAME_zhujiangbianshen::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	clear();
	return true;
	//return ID_BUTTON_CLOSEOnButtonClick(pSender);
}
// ListImg / ListEx
bool CUI_ID_FRAME_zhujiangbianshen::ID_LISTIMG_bianshenitemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																		ControlIconDrag::S_ListImg* pItemDrag,
																		ControlIconDrag::S_ListImg* pItemSrc )
{	
	
	/*ControlListImage* pBagListImg = 0;
	pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType( BT_NormalItemBag );
	int nIndex = pBagListImg->GetItemIndex( pItemDrag);*/
	//ControlIconDrag::S_ListImg* pImg = s_CUI_ID_FRAME_PACK.GetItemByIndex(BT_NormalItemBag,nIndex);
	if (!IsUILoad())
	{
		return false;
	}
	ControlListImage* pBagListImg = 0;
	CItemBag2* pBag = 0;
	int bagType = BT_NormalItemBag;
	int nNullIndex = m_pID_LISTIMG_bianshenitem->GetNullItem();
	pItemSrc = m_pID_LISTIMG_bianshenitem->GetItemByIndex( nNullIndex );

	if( s_CUI_ID_FRAME_PACK.IsListImageByBagType( BT_NormalItemBag, pSender ) )
	{
		pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType( BT_NormalItemBag );
		pBag = &thePlayerRole.m_bag;
		bagType = BT_NormalItemBag;
	}
	else if( s_CUI_ID_FRAME_PACK.IsListImageByBagType( BT_MaterialBag, pSender ) )
	{
		pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType( BT_MaterialBag );
		pBag = &thePlayerRole.m_bagMaterial;
		bagType = BT_MaterialBag;
	}
	else
	{
		return false;
	}

	if ( !pItemDrag || pItemDrag->IsNull() )
		return false;
	if (!pItemSrc || !pItemSrc->IsNull())
	{
		return false;
	}
	
	int nIndex = pBagListImg->GetItemIndex(pItemDrag);
	if (nIndex == -1)
	{
		return false;
	}
	nItemIndex = nIndex;
	ItemDefine::SItemCommon *pItem = NULL;
	pItem = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->Id() );
	if( !pItem||pItem->ucItemType != ItemDefine::ITEMTYPE_OTHER)
		return false;

	ItemDefine::SItemOther *pOhter = (ItemDefine::SItemOther *)pItem;
	if (!pOhter||pOhter->otherType != ItemDefine::OtherType_ZhujiangIdentify)
	{
		return false;
	}

	SetItemID(pItemDrag->m_pkIconInfo->Id());
	
	Refresh();

	//让主将图鉴变灰
	OnlyItemID = pItemDrag->m_pkIconInfo->GetOnlyId();
	CPackItemEnableManager::Instance()->RefreshBagItemEnable(pBag,pItemDrag->m_pkIconInfo->GetOnlyId(),true);
	theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
	return true;
}
bool CUI_ID_FRAME_zhujiangbianshen::IsPackItemBeUsing( __int64 nGuid )
{
   	if(!IsVisable())
        return false;
	if(OnlyItemID == nGuid)
		return true;
	else
		return false;
}
bool CUI_ID_FRAME_zhujiangbianshen::ID_LISTIMG_bianshenitemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_zhujiangbianshen::ID_LISTIMG_bianshenitemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_zhujiangbianshen::ID_LISTIMG_bianshenitemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	CItemBag2* pBag=NULL;
	thePlayerRole.GetBagByItemGUID(OnlyItemID,pBag);
	if(!pBag)
		return true;
	__int64 nowID = OnlyItemID;
	OnlyItemID = 0;
	SetItemID(INVALID_HERO_ID);
	Refresh();
	//根据物品的唯一ID获取物品的背包
	CPackItemEnableManager::Instance()->RefreshBagItemEnable(pBag,nowID,true);
	theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
	return true;
}
// Button
bool CUI_ID_FRAME_zhujiangbianshen::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}

// 装载UI
bool CUI_ID_FRAME_zhujiangbianshen::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\zhujiangbianshen.MEUI",false,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\zhujiangbianshen.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_zhujiangbianshen::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_zhujiangbianshen, s_CUI_ID_FRAME_zhujiangbianshenOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_zhujiangbianshen, s_CUI_ID_FRAME_zhujiangbianshenOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_zhujiangbianshen, ID_LISTIMG_skill, s_CUI_ID_FRAME_zhujiangbianshenID_LISTIMG_skillOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_zhujiangbianshen, ID_LISTIMG_skill, s_CUI_ID_FRAME_zhujiangbianshenID_LISTIMG_skillOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_zhujiangbianshen, ID_LISTIMG_skill, s_CUI_ID_FRAME_zhujiangbianshenID_LISTIMG_skillOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_zhujiangbianshen, ID_LISTIMG_skill, s_CUI_ID_FRAME_zhujiangbianshenID_LISTIMG_skillOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_zhujiangbianshen, ID_BUTTON_dianjiangpai, s_CUI_ID_FRAME_zhujiangbianshenID_BUTTON_dianjiangpaiOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_zhujiangbianshen, ID_BUTTON_ok, s_CUI_ID_FRAME_zhujiangbianshenID_BUTTON_okOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_zhujiangbianshen, ID_BUTTON_Cancel, s_CUI_ID_FRAME_zhujiangbianshenID_BUTTON_CancelOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_zhujiangbianshen, ID_LISTIMG_bianshenitem, s_CUI_ID_FRAME_zhujiangbianshenID_LISTIMG_bianshenitemOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_zhujiangbianshen, ID_LISTIMG_bianshenitem, s_CUI_ID_FRAME_zhujiangbianshenID_LISTIMG_bianshenitemOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_zhujiangbianshen, ID_LISTIMG_bianshenitem, s_CUI_ID_FRAME_zhujiangbianshenID_LISTIMG_bianshenitemOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_zhujiangbianshen, ID_LISTIMG_bianshenitem, s_CUI_ID_FRAME_zhujiangbianshenID_LISTIMG_bianshenitemOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_zhujiangbianshen, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_zhujiangbianshenID_BUTTON_CLOSEOnButtonClick );

	m_pID_FRAME_zhujiangbianshen = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_zhujiangbianshen );
	m_pID_PICTURE_zhujiangtouxiang = (ControlPicture*)theUiManager.FindControl( ID_FRAME_zhujiangbianshen, ID_PICTURE_zhujiangtouxiang );
	m_pID_PICTURE_nameLV = (ControlPicture*)theUiManager.FindControl( ID_FRAME_zhujiangbianshen, ID_PICTURE_nameLV );
	m_pID_TEXT_jieshao = (ControlText*)theUiManager.FindControl( ID_FRAME_zhujiangbianshen, ID_TEXT_jieshao );
	m_pID_PICTURE_ability = (ControlPicture*)theUiManager.FindControl( ID_FRAME_zhujiangbianshen, ID_PICTURE_ability );
	m_pID_LISTIMG_skill = (ControlListImage*)theUiManager.FindControl( ID_FRAME_zhujiangbianshen, ID_LISTIMG_skill );
	m_pID_BUTTON_dianjiangpai = (ControlButton*)theUiManager.FindControl( ID_FRAME_zhujiangbianshen, ID_BUTTON_dianjiangpai );
	m_pID_TEXT_money = (ControlText*)theUiManager.FindControl( ID_FRAME_zhujiangbianshen, ID_TEXT_money );
	m_pID_TEXT_needLV = (ControlText*)theUiManager.FindControl( ID_FRAME_zhujiangbianshen, ID_TEXT_needLV );
	m_pID_BUTTON_ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_zhujiangbianshen, ID_BUTTON_ok );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_zhujiangbianshen, ID_BUTTON_Cancel );
	m_pID_LISTIMG_bianshenitem = (ControlListImage*)theUiManager.FindControl( ID_FRAME_zhujiangbianshen, ID_LISTIMG_bianshenitem );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_zhujiangbianshen, ID_BUTTON_CLOSE );
	m_pID_PICTURE_warability = (ControlPicture*)theUiManager.FindControl( ID_FRAME_zhujiangbianshen, ID_PICTURE_warability );
	m_pID_LISTIMG_dianjiangpai = (ControlListImage*)theUiManager.FindControl( ID_FRAME_zhujiangbianshen, ID_LISTIMG_dianjiangpai );
	assert( m_pID_FRAME_zhujiangbianshen );
	assert( m_pID_PICTURE_zhujiangtouxiang );
	assert( m_pID_PICTURE_nameLV );
	assert( m_pID_TEXT_jieshao );
	assert( m_pID_PICTURE_ability );
	assert( m_pID_LISTIMG_skill );
	assert( m_pID_BUTTON_dianjiangpai );
	assert( m_pID_TEXT_money );
	assert( m_pID_TEXT_needLV );
	assert( m_pID_BUTTON_ok );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_LISTIMG_bianshenitem );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_PICTURE_warability );
	assert( m_pID_LISTIMG_dianjiangpai );
	_SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_zhujiangbianshen::_UnLoadUI()
{
	m_pID_FRAME_zhujiangbianshen = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\zhujiangbianshen.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_zhujiangbianshen::_IsVisable()
{
	return m_pID_FRAME_zhujiangbianshen->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_zhujiangbianshen::_SetVisable( const bool bVisable )
{
	if (_IsVisable()&&bVisable)
	{
		return;
	}

	if (bVisable)
	{
		clear();

		if (!s_CUI_ID_FRAME_PACK.IsVisable())
		{
			s_CUI_ID_FRAME_PACK.SetVisable(true);
		}
		ResetWindowPosition(m_pID_FRAME_zhujiangbianshen, s_CUI_ID_FRAME_PACK.GetFrame());
	}
	m_pID_FRAME_zhujiangbianshen->SetVisable( bVisable );
	SetItemID(INVALID_HERO_ID);
	CItemBag2* pBag=NULL;
	thePlayerRole.GetBagByItemGUID(OnlyItemID,pBag);
	if(!pBag)
		return;	
	__int64 noeID = OnlyItemID;
	OnlyItemID = 0;
	CPackItemEnableManager::Instance()->RefreshBagItemEnable(pBag,noeID,true);
}

void CUI_ID_FRAME_zhujiangbianshen::InitializeAtEnterWorld()
{
	if( !m_pID_FRAME_zhujiangbianshen )
		return;

	//ClearSlotSpark();
	_SetVisable( false );
}

bool CUI_ID_FRAME_zhujiangbianshen::clear()
{
	m_pID_TEXT_jieshao->Clear();
	m_pID_LISTIMG_skill->Clear();
	m_pID_TEXT_money->Clear();
	m_pID_TEXT_needLV->Clear();
	m_pID_LISTIMG_bianshenitem->Clear();
	m_pID_LISTIMG_dianjiangpai->Clear();
	m_pID_PICTURE_warability->SetVisable(false);
	m_pID_PICTURE_zhujiangtouxiang->SetVisable(false);
	m_pID_PICTURE_ability->SetVisable(false);
	m_pID_PICTURE_nameLV->SetVisable(false);
	CItemBag2* pBag=NULL;
	thePlayerRole.GetBagByItemGUID(OnlyItemID,pBag);
	if(!pBag)
		return false;	
	__int64 noeID = OnlyItemID;
	OnlyItemID = 0;
	CPackItemEnableManager::Instance()->RefreshBagItemEnable(pBag,noeID,true);
	return true;
}

void CUI_ID_FRAME_zhujiangbianshen::Refresh()
{

	if (!_IsVisable())
	{
		return;
	}

	clear();

	//int listimgsize = m_pID_LISTIMG_skill->GetIconSize();

	if(item_id == INVALID_HERO_ID)
	{
		return;
	}
	
	CItemHero::SItemHero* pHero = theItemHero.FindHeroByItemID(item_id);
	if (!pHero)
	{
		return;
	}
	m_pID_PICTURE_warability->SetVisable(true);
	m_pID_PICTURE_zhujiangtouxiang->SetVisable(true);
	m_pID_PICTURE_ability->SetVisable(true);
	m_pID_PICTURE_nameLV->SetVisable(true);
	m_pID_PICTURE_nameLV->SetPicName(pHero->namePicAddr.c_str());
	m_pID_PICTURE_zhujiangtouxiang->SetPicName(pHero->Pic_BianShenUI.c_str());
	//m_pID_PICTURE_zhujiangtouxiang->SetPicName(PlayerInfoMgr::Instance()->GetPlayerHeadPic(pHero));		//portrait
	m_pID_PICTURE_ability->SetPicName(pHero->icon_addr.c_str());				//ability
	//m_pID_LISTIMG_skill->SetPicName(pHero->icon_addr.c_str());					


	int skillArray[3] = {pHero->hero_skill1,pHero->hero_skill2,pHero->hero_skill3};
	int skillLevel[3] = {pHero->skill1_lv,pHero->skill2_lv,pHero->skill3_lv};
	//map<int,int> mapSkill;
	//mapSkill.insert(pair<int,int>(pHero->hero_skill1,pHero->skill1_lv));
	for(int i=0;i<sizeof(skillArray)/sizeof(int);i++)
	{
		if(skillArray[i]==0)
		{
			continue;
		}
		ControlIconDrag::S_ListImg stListItem;
		SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(skillArray[i]);
		if (iconSet)
			stListItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);
		bool bEnable = eIcon_Enable/*CPackItemEnableManager::Instance()->IsPackItemEnable( pBag, n )*/;
		stListItem.SetData( skillArray[i], skillLevel[i], bEnable? eIcon_Enable: eIcon_Disable, true, eTipFlag_SkillNoNextLevel );
		//stListItem.SetData( skillArray[i],skillLevel[i], ( bEnable ? eIcon_Enable : eIcon_Disable ));
		stListItem.SetSparkEnable( false );
		m_pID_LISTIMG_skill->SetItem( &stListItem, i );								//skill
	}

	ItemDefine::SItemCommon *pItem = NULL;
	pItem = GettheItemDetail().GetItemByID( pHero->itemd_id );
	ControlIconDrag::S_ListImg stItem;
	stItem.SetData(pHero->itemd_id,1);
	m_pID_LISTIMG_bianshenitem->SetItem(&stItem);
	
	pItem = GettheItemDetail().GetItemByID( pHero->material_id );
	CItemBag2* pBag = 0;
	if (!pItem)
		return;
	switch (thePlayerRole.GetBagTypeByItemType(pItem->ucItemType))
	{
	case BT_NormalItemBag:
		pBag = &thePlayerRole.m_bag;
		break;
	case BT_MaterialBag:
		pBag = &thePlayerRole.m_bagMaterial;
		break;
	case BT_TaskBag:
		pBag = &thePlayerRole.m_bagTask;
		break;
	default:
		pBag = &thePlayerRole.m_bag;
		break;
	}

	ControlIconDrag::S_ListImg stItemMaterial;
	if (pBag->GetItemCount(pHero->material_id) < pHero->material_count)
	{
		stItemMaterial.SetData(pHero->material_id,pHero->material_count,eIcon_Disable);
	}
	else
		stItemMaterial.SetData(pHero->material_id,pHero->material_count);	
	
	m_pID_LISTIMG_dianjiangpai->SetItem(&stItemMaterial);

	m_pID_TEXT_jieshao->SetText(pHero->explain_hero);							//intro
	//m_pID_TEXT_money->SetText(pHero->need_money);								//money
	std::string strText;
	strText.clear();

	thePlayerRole.GetGSCStringFromJiaoZi(pHero->need_money,strText);
	DWORD dwColor = 0xffffffff;
	/*if(!thePlayerRole.HaveEnoughMoney(pHero->need_money))
		dwColor = 0xffff0000;*/
	if (thePlayerRole.GetData(CPlayerRole::TYPE_JiaoZi) < pHero->need_money)
	{
		dwColor = 0xffff0000;
	}

	m_pID_TEXT_money->SetText(strText.c_str(), dwColor);

	m_pID_TEXT_needLV->SetText(pHero->need_lv);									//LV
	m_pID_PICTURE_warability->SetPicName(pHero->proPicAddr.c_str());			//war ability
	
}

bool CUI_ID_FRAME_zhujiangbianshen::IsSkillList(const ControlObject* pObject)
{
	return pObject==m_pID_LISTIMG_skill;
}