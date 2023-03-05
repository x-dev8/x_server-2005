/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\Shop.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Shop.h"
#include "ItemDetail.h"
#include "MeUi/ExpressionManager.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "GameMain.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "ChatInfoBox.h"
#include "SystemConfig.h"
#include "InputBox.h"
#include "dxsdk/dinput.h"
#include "core/Name.h"
#include "ui/BatchShop.h"
#include "tstring.h"
#include "baseProperty.h"
#include "ui/PrivateShop.h"
#include "color_config.h"
#include "ui/PlayerPrivateShop.h"
#include "IconManagerClient.h"
#include "Common.h"
#include "GuildConfig.h"

#include "WealthProtect.h"
#include "PreventWallow.h"
#include "Ui/InfoList.h"
#include "NpcShop.h"
#include "PocketShop.h"
extern short GetKeyboardInput(int iKey);

extern GAME_STATE	g_GameState;
extern CHeroGame* theApp;
bool CUI_ID_FRAME_SHOP:: m_bGuildShop;
int CUI_ID_FRAME_SHOP:: m_nGuildShoplevel;
static bool sendMendMsg( const char bPressYesButton, void *pData )
{
	if( bPressYesButton )
	{
		MsgRepairItem msg;	
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
		if(pMe)
			msg.header.stID =  pMe->GetID();
		msg.eType = MsgRepairItem::RT_All;
		msg.bIsCostRmb = false;
		GettheNetworkInput().SendMsg(&msg);

		return true;
	}
	return false;
}

void SendBuyGuildItem(int nGuildLevel, int nItemId, int nItemCount)
{
	MsgGuildBuyItemReq msg;
	msg.uchLevel = nGuildLevel;
	msg.nItemID = nItemId;
	msg.nCount = nItemCount;
	GettheNetworkInput().SendMsg(&msg);
}

void SendBuyNormalItem(int nItemId, int nItemType, int nItemCount)
{
	MsgBuyOrSellGoods msg;
	msg.bIsBuy = true;
	msg.ustItemId = nItemId;
	msg.ustPackIndex = -1;
	msg.ucItemBagType = nItemType;
	msg.ustCount  = nItemCount;
	if (!s_CUI_ID_FRAME_SHOP.IsRemoteClose())
	{
		msg.bIsPocketShop = true;
	}
	else
	{
		msg.bIsPocketShop = false;
	}
	GettheNetworkInput().SendMsg(&msg);
}

void SetDataForEquipItem(ItemDefine::SItemCommon* pItemDetail, SCharItem* pStItem)
{
	if (!pStItem || !pItemDetail)
	{
		return;
	}

	ItemDefine::SItemCanEquip* pEquip = ( ItemDefine::SItemCanEquip* )pItemDetail;
	for( int loop = 0; loop < ItemDefine::SItemCanEquip::ECD_AdditiveRandAttrCount; ++loop )
	{
// 		if( loop < pEquip->additiveRandCount && pEquip->additiveRandFlags[loop] && pEquip->additiveRandValues[loop] > 0 )
// 			pStItem->equipdata.baseRands[loop] = pEquip->additiveRandValues[loop];
// 		else
			pStItem->equipdata.baseRands[loop] = 0;
	}

	for( int loop = 0; loop < ItemDefine::SItemCanEquip::ECD_PurpleRandAttrCount; ++loop )
	{
// 		if( loop < pEquip->purpleRandCount && pEquip->purpleRandFlags[loop] && pEquip->purpleRandValues[loop] > 0 )
// 			pStItem->equipdata.purpleRands[loop] = pEquip->purpleRandValues[loop];
// 		else
			pStItem->equipdata.purpleRands[loop] = 0;
	}
}

bool CUI_ID_FRAME_SHOP::UIShop_BuyGoodsByCount( const char* szInputData, void *pData_ )
{
	if( !s_CUI_ID_FRAME_SHOP.GetFrame() )
		return false;
	TempTransferStruct* pData = (TempTransferStruct*)pData_;
	int nGoodsCount = atoi( szInputData );
	if ( nGoodsCount <= 0 )
		return false;

	CUI_ID_FRAME_SHOP::ItemCost* pCost = s_CUI_ID_FRAME_SHOP.GetItemCost( pData->m_nId);
	if (!pCost)
		return false;

	
	ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID(pData->m_nId);
	if ( !pItemDetail )
		return false;

    // 安全保护
    if( CWealthProtect::Instance().IsInProtectTime() || CPreventWallow::Instance().IsFCMNotHealthy() )
		return true;

	// 一次购买数量过多
	if (pCost->nPerCount>0&&pCost->nPerCount < nGoodsCount)
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eExchange_ExceedUpperLimit) ); 
		return true;
	}

    // 都怪2哥，现在金钱商店和交子商店不用CT_JiaoZi、CT_Money区分，用m_bBound区分
	// 没有交子也没有钱
	if ( !thePlayerRole.HaveEnoughMoney(pCost->nCost*nGoodsCount) && pItemDetail->costType == ItemDefine::CT_JiaoZi
        && s_CUI_ID_FRAME_SHOP.IsBoundShop() )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eExchange_NoJiaoziNoMoney) );
		return true;
	}
    // 没有足够的钱
    if ( thePlayerRole.GetData(CPlayerRole::TYPE_MONEY) < (pCost->nCost*nGoodsCount)
        && pItemDetail->costType == ItemDefine::CT_JiaoZi && !s_CUI_ID_FRAME_SHOP.IsBoundShop() )
    {
        s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eExchange_NotMoney) );
        return true;
    }

	// 没有足够的钱
	if ( thePlayerRole.GetData(CPlayerRole::TYPE_MONEY) < (pCost->nCost*nGoodsCount) && pItemDetail->costType == ItemDefine::CT_Money )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eExchange_NotMoney) );
		return true;
	}	
	
	if( theHeroGame.GetPlayerMgr()->GetMe() )
	{
		// 没有足够的名望	
		if( pCost->nCost*nGoodsCount > theHeroGame.GetPlayerMgr()->GetMe()->GetReputation() && pItemDetail->costType == ItemDefine::CT_Reputation )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eExchange_NotReputation ) );
			return true;
		}
		// 没有足够的功勋	
		if( pCost->nCost*nGoodsCount > theHeroGame.GetPlayerMgr()->GetMe()->GetExploit() && pItemDetail->costType == ItemDefine::CT_Exploit  )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eExchange_NotExploit ) );
			return true;
		}
		// 没有足够的帮贡	
		if( pCost->nCost*nGoodsCount > theHeroGame.GetPlayerMgr()->GetMe()->GetGuildOffer() && pItemDetail->costType == ItemDefine::CT_GuildOffer  )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eExchange_NotGuildOffer ) );
			return true;
		}	
		// 没有足够的荣誉	
		if( pCost->nCost*nGoodsCount > theHeroGame.GetPlayerMgr()->GetMe()->GetGlory() && pItemDetail->costType == ItemDefine::CT_Honour  )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eExchange_GloryNotEnough ) );
			return true;
		}
	}
	// 没有足够的令牌
	if( pItemDetail->costType == ItemDefine::CT_Item )
	{
		bool bFound = false;
		if( thePlayerRole.m_bag.GetItemCount( pItemDetail->costItemID ) >= pItemDetail->dwCost ) 			
			bFound = true;		
		else if( thePlayerRole.m_bagMaterial.GetItemCount( pItemDetail->costItemID ) >= pItemDetail->dwCost)		
			bFound = true;		
		if( !bFound )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eExchange_NotLingPai ) ) ;
			return true;
		}
	}

	if (m_bGuildShop)
	{
		SendBuyGuildItem(m_nGuildShoplevel, pData->m_nId, nGoodsCount);
		return true;
	}

	SendBuyNormalItem(pData->m_nId, pData->m_nType, nGoodsCount);
	return true;
}

bool CUI_ID_FRAME_SHOP::UIShop_BuyGoods(int num, void *pData)
{
	if( !s_CUI_ID_FRAME_SHOP.GetFrame() )
		return false;
	char buf[64] = {0};
	sprintf(buf, "%d", num);
	return UIShop_BuyGoodsByCount(buf, pData);
}

CUI_ID_FRAME_SHOP s_CUI_ID_FRAME_SHOP;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SHOP, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SHOP, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SHOP, ID_LISTIMG_SHOPOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SHOP, ID_LISTIMG_SHOPOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SHOP, ID_LISTIMG_SHOPOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SHOP, ID_LISTIMG_SHOPOnIconRButtonUp )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SHOP, ID_BUTTON_helpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SHOP, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SHOP, ID_BUTTON_mendOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SHOP, ID_BUTTON_mend2OnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SHOP, ID_LISTIMG_SHOP2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SHOP, ID_LISTIMG_SHOP2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SHOP, ID_LISTIMG_SHOP2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SHOP, ID_LISTIMG_SHOP2OnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SHOP, ID_BUTTON_PagedownOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SHOP, ID_BUTTON_PageupOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SHOP, ID_CHECKBOX_GoumaiOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SHOP, ID_CHECKBOX_GouhuiOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SHOP, ID_BUTTON_ActiveOnButtonClick )

CUI_ID_FRAME_SHOP::CUI_ID_FRAME_SHOP()
{
    m_bBound = true;
	// Member
	ResetMembers();
}

void CUI_ID_FRAME_SHOP::ResetMembers()
{
	m_pID_FRAME_SHOP = NULL;
	//m_pID_PICTURE_Di1 = NULL;
	m_pID_LISTIMG_SHOP = NULL;
	m_pID_PICTURE_Shop1 = NULL;
	m_pID_PICTURE_Shop2 = NULL;
	m_pID_PICTURE_Shop3 = NULL;
	m_pID_PICTURE_Shop4 = NULL;
	m_pID_PICTURE_Shop5 = NULL;
	m_pID_PICTURE_Shop6 = NULL;
	m_pID_PICTURE_Shop11 = NULL;
	m_pID_PICTURE_Shop12 = NULL;
	m_pID_PICTURE_Shop13 = NULL;
	m_pID_PICTURE_Shop14 = NULL;
	m_pID_PICTURE_Shop15 = NULL;
	m_pID_PICTURE_Shop16 = NULL;
	//m_pID_PICTURE_TitleDi = NULL;
// 	m_pID_BUTTON_help = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_mend = NULL;
	//m_pID_TEXT_Name = NULL;
	m_pID_BUTTON_mend2 = NULL;
	m_pID_TEXT_Name1 = NULL;
	m_pID_TEXT_Price1 = NULL;
	m_pID_TEXT_Name3 = NULL;
	m_pID_TEXT_Price3 = NULL;
	m_pID_TEXT_Name5 = NULL;
	m_pID_TEXT_Price5 = NULL;
	m_pID_TEXT_Name7 = NULL;
	m_pID_TEXT_Price7 = NULL;
	m_pID_TEXT_Name9 = NULL;
	m_pID_TEXT_Price9 = NULL;
	m_pID_TEXT_Name11 = NULL;
	//m_pID_TEXT_Price11 = NULL;
	m_pID_TEXT_Name2 = NULL;
	m_pID_TEXT_Price2 = NULL;
	m_pID_TEXT_Name4 = NULL;
	m_pID_TEXT_Price4 = NULL;
	m_pID_TEXT_Name6 = NULL;
	m_pID_TEXT_Price6 = NULL;
	m_pID_TEXT_Name8 = NULL;
	m_pID_TEXT_Price8 = NULL;
	m_pID_TEXT_Name10 = NULL;
	m_pID_TEXT_Price10 = NULL;
	m_pID_TEXT_Name12 = NULL;
	//m_pID_TEXT_Price12 = NULL;
	m_pID_LISTIMG_SHOP2 = NULL;
	m_pID_BUTTON_Pagedown = NULL;
	m_pID_BUTTON_Pageup = NULL;
	m_pID_TEXT_Lock1 = NULL;
	m_pID_TEXT_Lock2 = NULL;
	m_pID_TEXT_Lock3 = NULL;
	m_pID_TEXT_Lock4 = NULL;
	m_pID_TEXT_Lock5 = NULL;
	m_pID_TEXT_Lock6 = NULL;
	m_pID_TEXT_Lock7 = NULL;
	m_pID_TEXT_Lock8 = NULL;
	m_pID_TEXT_Lock9 = NULL;
	m_pID_TEXT_Lock10 = NULL;
	m_pID_TEXT_CurrentMoney = NULL;
	m_pID_BUTTON_Active = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_CHECKBOX_Goumai = NULL;
	m_pID_CHECKBOX_Gouhui = NULL;

	memset(m_pNameText, 0, sizeof(ControlText*)*ELEMENT_COUNT);
	memset(m_pPriceText, 0, sizeof(ControlText*)*ELEMENT_COUNT);
	m_nPageNum = 0;
	m_nCurrPage = 0;

	m_nNpcId = -1;
	m_bRepair = false;
	m_bGuildShop = false;
	m_nGuildShoplevel = 0;
	m_pCurrentShopData = NULL;
	//////////////////
	m_bRemoteClose = true;
}

void CUI_ID_FRAME_SHOP::UpdateIconInfo()
{
	POINT pos;
	RECT rect;
	GetCursorPos(&pos);
	GetWindowRect(g_hWnd, &rect);

	if(!theApp->IsFullScreen())
	{
		pos.x-=(rect.left + GetSystemMetrics(SM_CXBORDER));
		pos.y-=(rect.top + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXBORDER));
	}

	POINT ptMouseOnSel;
	if ( m_pID_LISTIMG_SHOP->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true
		||m_pID_LISTIMG_SHOP2->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true)
	{
		ControlListImage* pID_LISTIMG_SHOP;
		if(m_pID_LISTIMG_SHOP->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true)
		{
			pID_LISTIMG_SHOP = m_pID_LISTIMG_SHOP;
		}
		else if(m_pID_LISTIMG_SHOP2->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true)
		{
			pID_LISTIMG_SHOP = m_pID_LISTIMG_SHOP2;
		}
		else
		{
			assert(false);
		}
		// 这里tip的位置取当前item的左边界
		// 这样就可以固定tip位置
		RECT rcItem;
		pID_LISTIMG_SHOP->GetItemRect( pos.x, pos.y, rcItem );	
		// 偏移到中间
		rcItem.left += pID_LISTIMG_SHOP->GetItemWidth() / 2;
		rcItem.top += pID_LISTIMG_SHOP->GetItemHeight() / 2;

		bool bHaveCompare = false;
		ControlIconDrag::S_ListImg *pItem = pID_LISTIMG_SHOP->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );

		SCharItem* pscharItem = (SCharItem*)(pItem->m_pkIconInfo->GetData());

		for(int i = 0;i < s_CUI_ID_FRAME_SHOP.m_BuyBackPack.GetMaxPackSize();++i)
		{
			SCharItem* pscItem = s_CUI_ID_FRAME_SHOP.m_BuyBackPack.GetItemByIndex(i);
			if(pscItem&&pscItem->itembaseinfo.nOnlyInt == pscharItem->itembaseinfo.nOnlyInt)
			{
				pscItem->itembaseinfo.stPacketIdx = pscharItem->itembaseinfo.stPacketIdx;
				pItem->SetData(pscItem);
				break;
			}
		}
	}
}
// Frame
bool CUI_ID_FRAME_SHOP::OnFrameRun()
{
	if ( !IsVisable() )
	{
		return false;
	}

	if (m_bGuildShop)
	{
		UpdateIconInfo();
		UpdateMyInfo();
		return true;
	}

	CPlayer* pNpc = NULL;
	CPlayer* pMe = NULL;
	pNpc = theHeroGame.GetPlayerMgr()->FindByID( m_nNpcId );
	pMe = theHeroGame.GetPlayerMgr()->GetMe();
	//先这样判断看行不行
	//if (m_nNpcId==pMe->GetID() || m_nNpcId==-1)
	//{
	//	SetRemoteClose(false);		//随身商店不关闭
	//}
	//else
	//{
	//	SetRemoteClose(true);
	//}
	if ( !pMe || !pNpc )
	{
		SetVisable( false );
		return false;
	}
	float fNpcX, fNpcY, fNpcZ;
	float fMeX,fMeY,fMeZ;
	pNpc->GetPos( &fNpcX, &fNpcY, &fNpcZ );
	pMe->GetPos( &fMeX, &fMeY, &fMeZ );
	float x = fNpcX - fMeX;
	float y = fNpcY - fMeY;
	float dist = sqrtf( x*x + y*y );
	if( dist > 12.0f && IsRemoteClose())
	{
		SetVisable( false );
	}

	UpdateIconInfo();
	UpdateMyInfo();

	return true;
}
bool CUI_ID_FRAME_SHOP::OnFrameRender()
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SHOP::ID_LISTIMG_SHOPOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													ControlIconDrag::S_ListImg* pItemDrag,
													ControlIconDrag::S_ListImg* pItemSrc )
{
	if (!m_pID_FRAME_SHOP)
		return false;
	SellItem(pSender, pItemDrag);
	return false;
}
bool CUI_ID_FRAME_SHOP::ID_LISTIMG_SHOPOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_SHOP)
		return false;
	return false;
}
bool CUI_ID_FRAME_SHOP::ID_LISTIMG_SHOPOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_SHOP)
		return false;
	return false;
}
bool CUI_ID_FRAME_SHOP::ID_LISTIMG_SHOPOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_SHOP)
		return false;
	if (pItem)
		BuyItems(pItem);
	return true;
}
// Button
// bool CUI_ID_FRAME_SHOP::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	return true;
// }
// Button
bool CUI_ID_FRAME_SHOP::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_SHOP)
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SHOP::ID_BUTTON_mendOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_SHOP)
		return false;
	//时装不能修理
	/*if ( thePlayerRole.m_charinfo.visual.IsShowAecorative())
	{
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eCannotRepairFashion));
		return false;
	}*/

	DWORD dwMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
	int nItemHp = 0, nItemMaxHp = 0, nHpPoint = 0, mendPri = 0;
	bool bIsNeed = false;

	int nAllSprice = 0;

	for( int i = 0; i < EEquipPartType_MaxEquitPart; ++i)
	{
		//if( i == EPT_Hair || i == EPT_Face )
		//	continue;

		if(thePlayerRole.m_charinfo.visual.GetVisualArray()[i].itembaseinfo.ustItemID != InvalidLogicNumber)
		{
			ItemDefine::SItemCanEquip *pItem = (ItemDefine::SItemCanEquip *)GettheItemDetail().GetItemByID(
				thePlayerRole.m_charinfo.visual.GetVisualArray()[i].itembaseinfo.ustItemID ); 
			if (!pItem || pItem->uchRepairType != ItemDefine::SItemCanEquip::ECD_Repair_Normal)
				continue;

			nItemHp = thePlayerRole.m_charinfo.visual.GetVisualArray()[i].equipdata.usHP;
			nItemMaxHp = pItem->stHPMax;

			if( nItemHp >= 0 && nItemHp < nItemMaxHp )
			{//这里说明耐久已经下降了　应该计算修理
				bIsNeed = true;
				if( pItem )
				{
					nAllSprice += pItem->stRepairPrice * (pItem->stHPMax - nItemHp);
				}
			}
		}
	}

	if (nAllSprice == 0&&bIsNeed)
	{
		nAllSprice = 1;
	}
	if(!thePlayerRole.HaveEnoughMoney(nAllSprice))
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_MoneyNotEnoungh ) );
		return false;
	}
	if( nAllSprice == 0)
	{
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Fix_Failed, theXmlString.GetString(eClient_AddInfo_2slk_10) );
		return false;
	}

	char szTemp[128] = {0};

	int gold = 0,silver = 0,copper = 0;
    thePlayerRole.GetGSCFromMoney(nAllSprice,gold,silver,copper);

	std::stringstream sstr;
	sstr << theXmlString.GetString(eText_Client_Doyou_Mend_CostGold);
	if (gold > 0)
		sstr << gold << theXmlString.GetString(eText_Money_Gold);
	if (silver > 0)
		sstr << silver << theXmlString.GetString(eText_Money_Silver);
	if (copper > 0)
		sstr << copper << theXmlString.GetString(eText_Money_Copper);

	s_CUI_ID_FRAME_MessageBox.Show( sstr.str().c_str(), "", CUI_ID_FRAME_MessageBox::eTypeYesNo,
		false, sendMendMsg );
	return true;
}
// Button
bool CUI_ID_FRAME_SHOP::ID_BUTTON_mend2OnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_SHOP)
		return false;
	SetRepair(!GetRepair());
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SHOP::ID_LISTIMG_SHOP2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													 ControlIconDrag::S_ListImg* pItemDrag,
													 ControlIconDrag::S_ListImg* pItemSrc )
{
	if (!m_pID_FRAME_SHOP)
		return false;
	SellItem(pSender, pItemDrag);
	return false;
}
bool CUI_ID_FRAME_SHOP::ID_LISTIMG_SHOP2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_SHOP)
		return false;
	return false;
}
bool CUI_ID_FRAME_SHOP::ID_LISTIMG_SHOP2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_SHOP)
		return false;
	return false;
}
bool CUI_ID_FRAME_SHOP::ID_LISTIMG_SHOP2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_SHOP)
		return false;
	return false;
}
// Button
bool CUI_ID_FRAME_SHOP::ID_BUTTON_PagedownOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_SHOP)
		return false;
	TogglePage(m_nCurrPage + 1);
	return true;
}
// Button
bool CUI_ID_FRAME_SHOP::ID_BUTTON_PageupOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_SHOP)
		return false;
	TogglePage(m_nCurrPage - 1);
	return true;
}
// CheckBox
void CUI_ID_FRAME_SHOP::ID_CHECKBOX_GoumaiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (!m_pID_FRAME_SHOP)
		return;
	m_nCurrPage = 0;
	ToggleBuyFrame();
}
// CheckBox
void CUI_ID_FRAME_SHOP::ID_CHECKBOX_GouhuiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (!m_pID_FRAME_SHOP)
		return;
	m_nCurrPage = 0;
	ToggleReturnBuyFrame();
}

// 装载UI
bool CUI_ID_FRAME_SHOP::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Shop.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Shop.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}

static void UIShop_VisableChanged(ControlObject* pObject)
{
	if (!s_CUI_ID_FRAME_SHOP.IsVisable())
	{
		s_CUI_ID_FRAME_PACK.RefreshNormalPack();
		s_CUI_ID_FRAME_PACK.RefreshMaterialPack();
		s_CUI_ID_FRAME_PACK.SetDestroyItem(false);
		s_CUI_ID_FRAME_PACK.SetSplitItem(false);
		s_CUI_ID_FRAME_SHOP.SetRepair(false);
		
		theMouseManager.SetCanSetCursor(true);
		theMouseManager.SetCursor(MouseManager::Type_Arrow);
		theMouseManager.SetUICursor(MouseManager::Type_Arrow);
		theMouseManager.SetCanSetCursor(false);
		theIconDragManager.ClearDrag();
		s_CUI_ID_FRAME_SHOP.SetRemoteClose(true);

		
	}
}

// 关连控件
bool CUI_ID_FRAME_SHOP::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SHOP, s_CUI_ID_FRAME_SHOPOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SHOP, s_CUI_ID_FRAME_SHOPOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_SHOP, ID_LISTIMG_SHOP, s_CUI_ID_FRAME_SHOPID_LISTIMG_SHOPOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SHOP, ID_LISTIMG_SHOP, s_CUI_ID_FRAME_SHOPID_LISTIMG_SHOPOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SHOP, ID_LISTIMG_SHOP, s_CUI_ID_FRAME_SHOPID_LISTIMG_SHOPOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SHOP, ID_LISTIMG_SHOP, s_CUI_ID_FRAME_SHOPID_LISTIMG_SHOPOnIconRButtonUp );
// 	theUiManager.OnButtonClick( ID_FRAME_SHOP, ID_BUTTON_help, s_CUI_ID_FRAME_SHOPID_BUTTON_helpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SHOP, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SHOPID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SHOP, ID_BUTTON_mend, s_CUI_ID_FRAME_SHOPID_BUTTON_mendOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SHOP, ID_BUTTON_mend2, s_CUI_ID_FRAME_SHOPID_BUTTON_mend2OnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SHOP, ID_LISTIMG_SHOP2, s_CUI_ID_FRAME_SHOPID_LISTIMG_SHOP2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SHOP, ID_LISTIMG_SHOP2, s_CUI_ID_FRAME_SHOPID_LISTIMG_SHOP2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SHOP, ID_LISTIMG_SHOP2, s_CUI_ID_FRAME_SHOPID_LISTIMG_SHOP2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SHOP, ID_LISTIMG_SHOP2, s_CUI_ID_FRAME_SHOPID_LISTIMG_SHOPOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_SHOP, ID_BUTTON_Pagedown, s_CUI_ID_FRAME_SHOPID_BUTTON_PagedownOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SHOP, ID_BUTTON_Pageup, s_CUI_ID_FRAME_SHOPID_BUTTON_PageupOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SHOP, ID_CHECKBOX_Goumai, s_CUI_ID_FRAME_SHOPID_CHECKBOX_GoumaiOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SHOP, ID_CHECKBOX_Gouhui, s_CUI_ID_FRAME_SHOPID_CHECKBOX_GouhuiOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_SHOP, ID_BUTTON_Active, s_CUI_ID_FRAME_SHOPID_BUTTON_ActiveOnButtonClick );
	theUiManager.OnIconDragOn(ID_FRAME_SHOP,ID_LISTIMG_SHOP11111,s_CUI_ID_FRAME_SHOPID_LISTIMG_SHOP2OnIconDragOn);

	m_pID_FRAME_SHOP = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SHOP );
	//m_pID_PICTURE_Di1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SHOP, ID_PICTURE_Di1 );
	m_pID_LISTIMG_SHOP = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SHOP, ID_LISTIMG_SHOP );
	m_pID_PICTURE_Shop1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SHOP, ID_PICTURE_Shop1 );
	m_pID_PICTURE_Shop2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SHOP, ID_PICTURE_Shop2 );
	m_pID_PICTURE_Shop3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SHOP, ID_PICTURE_Shop3 );
	m_pID_PICTURE_Shop4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SHOP, ID_PICTURE_Shop4 );
	m_pID_PICTURE_Shop5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SHOP, ID_PICTURE_Shop5 );
	m_pID_PICTURE_Shop6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SHOP, ID_PICTURE_Shop6 );
	m_pID_PICTURE_Shop11 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SHOP, ID_PICTURE_Shop11 );
	m_pID_PICTURE_Shop12 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SHOP, ID_PICTURE_Shop12 );
	m_pID_PICTURE_Shop13 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SHOP, ID_PICTURE_Shop13 );
	m_pID_PICTURE_Shop14 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SHOP, ID_PICTURE_Shop14 );
	m_pID_PICTURE_Shop15 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SHOP, ID_PICTURE_Shop15 );
	m_pID_PICTURE_Shop16 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SHOP, ID_PICTURE_Shop16 );
// 	m_pID_PICTURE_TitleDi = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SHOP, ID_PICTURE_TitleDi );
// 	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_SHOP, ID_BUTTON_help );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SHOP, ID_BUTTON_CLOSE );
	m_pID_BUTTON_mend = (ControlButton*)theUiManager.FindControl( ID_FRAME_SHOP, ID_BUTTON_mend );
	//m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Name );
	m_pID_BUTTON_mend2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SHOP, ID_BUTTON_mend2 );
	m_pID_TEXT_Name1 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Name1 );
	m_pID_TEXT_Price1 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Price1 );
	m_pID_TEXT_Name3 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Name3 );
	m_pID_TEXT_Price3 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Price3 );
	m_pID_TEXT_Name5 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Name5 );
	m_pID_TEXT_Price5 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Price5 );
	m_pID_TEXT_Name7 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Name7 );
	m_pID_TEXT_Price7 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Price7 );
	m_pID_TEXT_Name9 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Name9 );
	m_pID_TEXT_Price9 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Price9 );
	m_pID_TEXT_Name11 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Name11 );
	//m_pID_TEXT_Price11 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Price11 );
	m_pID_TEXT_Name2 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Name2 );
	m_pID_TEXT_Price2 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Price2 );
	m_pID_TEXT_Name4 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Name4 );
	m_pID_TEXT_Price4 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Price4 );
	m_pID_TEXT_Name6 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Name6 );
	m_pID_TEXT_Price6 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Price6 );
	m_pID_TEXT_Name8 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Name8 );
	m_pID_TEXT_Price8 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Price8 );
	m_pID_TEXT_Name10 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Name10 );
	m_pID_TEXT_Price10 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Price10 );
	m_pID_TEXT_Name12 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Name12 );
	//m_pID_TEXT_Price12 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Price12 );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Page );
	m_pID_CHECKBOX_Goumai = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SHOP, ID_CHECKBOX_Goumai );
	m_pID_CHECKBOX_Gouhui = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SHOP, ID_CHECKBOX_Gouhui );
	m_pID_BUTTON_Pageup = (ControlButton*)theUiManager.FindControl( ID_FRAME_SHOP, ID_BUTTON_Pageup );
	m_pID_BUTTON_Pagedown = (ControlButton*)theUiManager.FindControl( ID_FRAME_SHOP, ID_BUTTON_Pagedown );
	m_pID_LISTIMG_SHOP = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SHOP, ID_LISTIMG_SHOP );
	m_pID_LISTIMG_SHOP2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SHOP, ID_LISTIMG_SHOP2 );
	m_pID_TEXT_CurrentMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_CurrentMoney );
	m_pID_BUTTON_Active = (ControlButton*)theUiManager.FindControl( ID_FRAME_SHOP, ID_BUTTON_Active );
	m_pID_TEXT_Lock1 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Lock1 );
	m_pID_TEXT_Lock2 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Lock2 );
	m_pID_TEXT_Lock3 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Lock3 );
	m_pID_TEXT_Lock4 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Lock4 );
	m_pID_TEXT_Lock5 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Lock5 );
	m_pID_TEXT_Lock6 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Lock6 );
	m_pID_TEXT_Lock7 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Lock7 );
	m_pID_TEXT_Lock8 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Lock8 );
	m_pID_TEXT_Lock9 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Lock9 );
	m_pID_TEXT_Lock10 = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, ID_TEXT_Lock10 );


	assert( m_pID_FRAME_SHOP );
// 	assert( m_pID_PICTURE_Di1 );
	assert( m_pID_LISTIMG_SHOP );
	//assert( m_pID_PICTURE_TitleDi );
// 	assert( m_pID_BUTTON_help );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_mend );
	//assert( m_pID_TEXT_Name );
	assert( m_pID_BUTTON_mend2 );
	assert( m_pID_LISTIMG_SHOP2 );
	assert( m_pID_BUTTON_Pagedown );
	assert( m_pID_BUTTON_Pageup );
	assert( m_pID_TEXT_Page );
	assert( m_pID_CHECKBOX_Goumai );
	assert( m_pID_CHECKBOX_Gouhui );

	//SetVisable( false );

	m_BuyBackPack.ClearPack();

	char buf[128] = {0};
	for (int i = 0; i < ELEMENT_COUNT; ++i)
	{
		sprintf(buf, "ID_TEXT_Name%d", i + 1);
		m_pNameText[i] = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, buf );
		assert(m_pNameText[i]);

		sprintf(buf, "ID_TEXT_Price%d", i + 1);
		m_pPriceText[i] = (ControlText*)theUiManager.FindControl( ID_FRAME_SHOP, buf );
		m_pPriceText[i]->setShowTip( true );
		assert(m_pPriceText[i]);
	}

	m_pID_LISTIMG_SHOP->SetScrollBarEnable(false);
	m_pID_LISTIMG_SHOP->ShowPressEffect(true);
	m_pID_LISTIMG_SHOP->SetOnlyShowItemIcon(true);
	m_pID_LISTIMG_SHOP2->SetScrollBarEnable(false);
	m_pID_LISTIMG_SHOP2->ShowPressEffect(true);
	m_pID_LISTIMG_SHOP2->SetOnlyShowItemIcon(true);

	m_pID_FRAME_SHOP->SetOnVisibleChangedFun(UIShop_VisableChanged);
	//m_pID_FRAME_SHOP->SetMsgProcFun( ShopFrame_MsgProc );

	theUiManager.SetFrameLayout(UI_LAYOUT_1, m_pID_FRAME_SHOP);

	m_LockGroup.Clear();
	m_vctLock.clear();
	m_LockGroup.AddControl(m_pID_TEXT_Lock1);
	m_vctLock.push_back(m_pID_TEXT_Lock1);
	m_LockGroup.AddControl(m_pID_TEXT_Lock2);
	m_vctLock.push_back(m_pID_TEXT_Lock2);
	m_LockGroup.AddControl(m_pID_TEXT_Lock3);
	m_vctLock.push_back(m_pID_TEXT_Lock3);
	m_LockGroup.AddControl(m_pID_TEXT_Lock4);
	m_vctLock.push_back(m_pID_TEXT_Lock4);
	m_LockGroup.AddControl(m_pID_TEXT_Lock5);
	m_vctLock.push_back(m_pID_TEXT_Lock5);
	m_LockGroup.AddControl(m_pID_TEXT_Lock6);
	m_vctLock.push_back(m_pID_TEXT_Lock6);
	m_LockGroup.AddControl(m_pID_TEXT_Lock7);
	m_vctLock.push_back(m_pID_TEXT_Lock7);
	m_LockGroup.AddControl(m_pID_TEXT_Lock8);
	m_vctLock.push_back(m_pID_TEXT_Lock8);
	m_LockGroup.AddControl(m_pID_TEXT_Lock9);
	m_vctLock.push_back(m_pID_TEXT_Lock9);
	m_LockGroup.AddControl(m_pID_TEXT_Lock10);
	m_vctLock.push_back(m_pID_TEXT_Lock10);
	m_LockGroup.AddControl(m_pID_BUTTON_Active);

	m_PriceGroup.Clear();
	m_PriceGroup.AddControl(m_pID_TEXT_Price1);
	m_PriceGroup.AddControl(m_pID_TEXT_Price3);
	m_PriceGroup.AddControl(m_pID_TEXT_Price5);
	m_PriceGroup.AddControl(m_pID_TEXT_Price7);
	m_PriceGroup.AddControl(m_pID_TEXT_Price9);
	m_PriceGroup.AddControl(m_pID_TEXT_Price2);
	m_PriceGroup.AddControl(m_pID_TEXT_Price4);
	m_PriceGroup.AddControl(m_pID_TEXT_Price6);
	m_PriceGroup.AddControl(m_pID_TEXT_Price8);
	m_PriceGroup.AddControl(m_pID_TEXT_Price10);
	
	m_PriceGroup.SetVisible(true);
	m_LockGroup.SetVisible(false);
	USE_SCRIPT( eUI_OBJECT_Shop, this );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SHOP::_UnLoadUI()
{
	CLOSE_SCRIPT ( eUI_OBJECT_Shop );
	theUiManager.RemoveFrameLayout(m_pID_FRAME_SHOP);
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\Shop.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SHOP::_IsVisable()
{
	if (!m_pID_FRAME_SHOP)
		return false;
	return m_pID_FRAME_SHOP->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_SHOP::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_SHOP )
		return;
	if (!m_pID_FRAME_SHOP->IsVisable())
		m_nCurrPage = 0;

	if (!m_bGuildShop)
	{
		m_PriceGroup.SetVisible(true);
		m_LockGroup.SetVisible(false);
	}

   bool bOldVisible = m_pID_FRAME_SHOP->IsVisable();	
	m_pID_FRAME_SHOP->SetVisable( bVisable );
	if( !bOldVisible && bVisable )
	{
		s_CUI_ID_FRAME_PACK.RefreshNormalPack();
		s_CUI_ID_FRAME_PACK.RefreshMaterialPack();
	}	

	if (bVisable)
	{
		/*CPlayer* pNpc = theHeroGame.GetPlayerMgr()->FindByID( m_nNpcId );*/

		if (!s_CUI_ID_FRAME_PACK.IsVisable())
			s_CUI_ID_FRAME_PACK.SetVisable(true);
		
		/*RECT tempRect;
		m_pID_FRAME_SHOP->GetRealRect(&tempRect);
		s_CUI_ID_FRAME_PACK.MoveToXY(tempRect.right, tempRect.top);*/
		ResetWindowPosition(m_pID_FRAME_SHOP, s_CUI_ID_FRAME_PACK.GetFrame());

		//随身商店，从本地配置文件中读取商店数据
		if (!IsRemoteClose())
		{
			//char path[MAX_PATH];
			//sprintf_s(path,MAX_PATH,"%s\\data\\config\\PocketShop.config",GetRootPath());
			if (!thePocketShopManager.IsLoad())
			{
				thePocketShopManager.LoadConifg(POCKETSHOP_FILEPATH);
			}
			MsgAckGetShop MsgDiy;
			MsgDiy.header.stID = theHeroGame.GetPlayerMgr()->GetMe()->GetID();    // 
			MsgDiy.byType      = 0xff;
			MsgDiy.bIsBound    = false;
			CPocketShopManger::PocketShopMap PocketShopData = thePocketShopManager.GetPocketShopData();
			MsgDiy.nCount      = PocketShopData.size();
			SShopItem* pItem=NULL;
			//CPocketShopManger::PocketShopMap::iterator itr = thePocketShopManager.GetPocketShopData().begin();
			std::vector<int> vecID = thePocketShopManager.GetPocketShopAllID();
			std::vector<int>::iterator itr = vecID.begin();
			
			float N = 1;
			//if(thePlayerRole.IsInStrongCountry() && !m_bRemoteClose)
			//{
			//	//是强国的话
			//	N = 0.85;
			//}

			for (int i=0;itr!=vecID.end(); i++,itr++)
			{
				//当前数量，先填个数随便测试下
				MsgDiy.nIds[i] = *itr;
				MsgDiy.nCounts[i] = 9999;
				int Price = N * PocketShopData[*itr]->nBuyPrice;
				MsgDiy.dwSellPrices[i] = Price;    //itr->second->nBuyPrice;
				MsgDiy.dwBuyPrices[i] =Price/2;
				MsgDiy.nBuyCounts[i] = PocketShopData[*itr]->nPerCount;
				MsgDiy.bIsBound = true;
				MsgDiy.bIsItemBound[i] = PocketShopData[*itr]->bIsBound;
			}
			Refresh(&MsgDiy);

			//随身商店不进行修理
			m_pID_BUTTON_mend->SetVisable(false);
			m_pID_BUTTON_mend2->SetVisable(false);
		}
		else
		{
			m_pID_BUTTON_mend->SetVisable(true);
			m_pID_BUTTON_mend2->SetVisable(true);

			
			
		}
	}
}

void CUI_ID_FRAME_SHOP::Refresh(MsgAckGetShop* pMsg)
{
	m_bGuildShop = false;
	if (!IsVisable())
	{
		SetVisable(true);
	}
	if( !m_pID_FRAME_SHOP )
		return;
	m_nNpcId = pMsg->header.stID;

	m_vtItemCost.clear();
	ControlListImage* pListImg = 0;
	for (short n = 0; n < pMsg->nCount; ++n)
	{
		ItemCost stItemCost;
		stItemCost.nId = pMsg->nIds[n];
		stItemCost.nCost = pMsg->dwSellPrices[n];
		stItemCost.nPerCount = pMsg->nBuyCounts[n];
		m_vtItemCost.push_back( stItemCost );
	}

    m_bBound = pMsg->bIsBound;
	m_shopData = *pMsg;

	ToggleBuyFrame();
}

void CUI_ID_FRAME_SHOP::TogglePage(int nPage)
{
	if (!m_pCurrentShopData)
	{
		return;
	}

	if (nPage >= m_nPageNum || nPage < 0)
		return;

	m_nCurrPage = nPage;

	std::stringstream strPage;
	strPage << m_nCurrPage + 1;
	strPage << "/";
	strPage << m_nPageNum;
	m_pID_TEXT_Page->SetText(strPage.str());

	SetLockText(m_pCurrentShopData->nCount, m_nCurrPage + 1);

	m_pID_LISTIMG_SHOP->Clear();
	m_pID_LISTIMG_SHOP2->Clear();

	for (int i = 0; i < ELEMENT_COUNT; ++i)
	{
		m_pNameText[i]->SetText("");
		m_pNameText[i]->setTip("");
		m_pPriceText[i]->SetText("");
		m_pPriceText[i]->setTip("");
	}

	ItemDefine::SItemCommon *pItemDetail = NULL;
	ControlListImage* pListImg = m_pID_LISTIMG_SHOP;
	short nBeginIndex = nPage * ELEMENT_COUNT;
	int nPageSize = 0;
	if (ELEMENT_COUNT > m_pCurrentShopData->nCount)
		nPageSize = m_pCurrentShopData->nCount;
	else if (m_pCurrentShopData->nCount - nBeginIndex > ELEMENT_COUNT)
		nPageSize = ELEMENT_COUNT;
	else
		nPageSize = m_pCurrentShopData->nCount - nBeginIndex;
	for (short n = 0; n < nPageSize; ++n)
	{
		if (n%2 == 0)
			pListImg = m_pID_LISTIMG_SHOP;
		else
			pListImg = m_pID_LISTIMG_SHOP2;

		ControlIconDrag::S_ListImg stListImg;
		ControlList::S_List	stList;

		int nIndex = n + nBeginIndex;
		int nId = m_pCurrentShopData->nIds[nIndex];
		int nCount = m_pCurrentShopData->nCounts[nIndex];
		int nCost = m_pCurrentShopData->dwSellPrices[nIndex];
		__int64 nGuid = m_pCurrentShopData->nGuids[nIndex];
		int nPackIndex = m_pCurrentShopData->nPackIndex[nIndex];
		bool bBound = m_pCurrentShopData->bIsBound[nIndex];
		if ( nCount == -1 )
			continue;
		eIconDrawState bEnable = eIcon_Disable;
		if(nCount > 0)
		{
			bEnable = eIcon_Enable;
		}
		else
		{
			bEnable = eIcon_Disable;
		}
		SCharItem stItem;

		if(m_pID_CHECKBOX_Gouhui->IsChecked())
		{
			SCharItem* pstItem;

			pstItem = s_CUI_ID_FRAME_SHOP.m_BuyBackPack.GetItemByIndex(nPackIndex);

			if(pstItem)
			{
				memcpy(&stItem, pstItem, sizeof(SCharItem) );
			}
			else
			{
				return;
			}
		}

		if (IsRemoteClose()) 
			stItem.SetBounded( m_bBound );
		else
			stItem.SetBounded( bBound );
		stItem.itembaseinfo.ustItemID = nId;
		stItem.itembaseinfo.nOnlyInt = nGuid;
		stItem.itembaseinfo.stPacketIdx = nPackIndex;
		stItem.equipdata.usHP = -1;
		pItemDetail = GettheItemDetail().GetItemByID( nId );
		if ( !pItemDetail )
		{
			assert( pItemDetail );
			continue;
		}

        // 拷贝品质     added by zhuomeng.hu		[12/29/2010]
        stItem.equipdata.quality = pItemDetail->ustLevel;

		if ( pItemDetail->IsExclusive() )
		{
            /*
			for( int loop=0; loop<SCharItem::EConstDefine_GemHoleMaxCount; loop++ )
				stItem.equipdata.gemIds[loop] = 0;
            for( int loop = 0; loop < SCharItem::EConstDefine_SuitRandMaxCount; ++loop )
                stItem.equipdata.suitRands[loop] = 0;
			for (int loop = 0;loop<SCharItem::EConstDefine_BaseRandMaxCount;loop++)
				stItem.equipdata.baseRands[loop] = 0;
            for( int loop = 0; loop < SCharItem::EConstDefine_PurpleRandMaxCount; ++loop )
                stItem.equipdata.purpleRands[loop] = 0;*/
			if( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON 
				|| pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
			{
				SetDataForEquipItem(pItemDetail, &stItem);
				stListImg.SetData( &stItem, bEnable, eTipFlag_Normal );
				/*stListImg.SetData( nId, nCount );*/
			}
			else
			{
				stListImg.SetData( &stItem, bEnable, eTipFlag_Normal );
			}
			
			stListImg.m_pkIconInfo->Count() = nCount;
			stListImg.m_pkIconInfo->SetCost( nCost );
			if ( nCount <= 0 )
				stListImg.SetEnable( eIcon_Disable );
			pListImg->SetItem( &stListImg, n / 2 );
		}
		else
		{
			if ( nCount == -1 )
				stItem.itembaseinfo.ustItemCount = 99;
			else
				stItem.itembaseinfo.ustItemCount = nCount;
			
			if (!IsRemoteClose() && !m_pID_CHECKBOX_Gouhui->IsChecked())
			{
				stItem.itembaseinfo.ustItemCount = 1;//m_pCurrentShopData->nBuyCounts[nIndex];
			}

			stListImg.SetData( &stItem, bEnable, eTipFlag_Normal );
			stListImg.m_pkIconInfo->SetCost( nCost );
			pListImg->SetItem( &stListImg,  n / 2 );
		}

		Common::_tstring tstrName( pItemDetail->GetItemName() );
		S_IconInfoHero::ReplaceSpecifiedName( pItemDetail->ustLevel, tstrName );

		m_pNameText[n]->SetText( tstrName.c_str(), S_IconInfoHero::GetQualityColor(pItemDetail->ustLevel) );

		std::stringstream str;
		std::stringstream strTip;
		unsigned char uchCostType = 0;
		int nCostSome = 0;
		if (IsRemoteClose())
		{
			uchCostType = pItemDetail->costType;
			nCostSome = pItemDetail->dwCost;
		}
		else
		{
			CPocketShopManger::SPocketShop* pShopData = thePocketShopManager.GetPocketShopItemByID(nId);
			if (pShopData)
			{
				uchCostType = pShopData->byCostType;
			}
			else
			{
				uchCostType = pItemDetail->costType;
			}
			nCostSome = nCost;
		}

		if(m_bGuildShop)
		{
			uchCostType = ItemDefine::CT_GuildOffer;
			nCostSome = nCost;
		}

		if( /*pItemDetail->costType*/uchCostType == ItemDefine::CT_Money || m_pID_CHECKBOX_Gouhui->IsChecked())
		{
			// 金钱gif
			int gold = 0,silver = 0,copper = 0;
            thePlayerRole.GetGSCFromMoney(nCost,gold,silver,copper);

			if (gold > 0)
			{
                if(/*pItemDetail->costType*/uchCostType == ItemDefine::CT_JiaoZi)
				   str << gold << "#61  ";
                else
				   str << gold << "#81  ";
				strTip << gold << theXmlString.GetString( eText_Money_Gold ) << "  ";
			}
			if (silver > 0)
			{
                if(/*pItemDetail->costType*/uchCostType == ItemDefine::CT_JiaoZi)
                    str << silver << "#62  ";
                else
                    str << silver << "#82  ";
				strTip << silver << theXmlString.GetString( eText_Money_Silver ) <<  "  ";
			}
			if (copper > 0)
			{
                if(/*pItemDetail->costType*/uchCostType == ItemDefine::CT_JiaoZi)
                   str << copper << "#63  ";
                else
				   str << copper << "#83  ";
				strTip << copper << theXmlString.GetString( eText_Money_Copper ) << "  ";
			}
		}
		else if( /*pItemDetail->costType*/uchCostType == ItemDefine::CT_Reputation )
		{
			// 名望gif,98
			int dwReputation = nCostSome;			//pItemDetail->dwCost
			if( dwReputation > 0 )
			{
				str << dwReputation << "#98 ";
				strTip << dwReputation << theXmlString.GetString( eText_Reputation );
			}			
		}
		else if( /*pItemDetail->costType*/uchCostType == ItemDefine::CT_Exploit )
		{
			// 功勋gif,99
			int dwExploit = nCostSome;				//pItemDetail->dwCost;
			if( dwExploit > 0 )
			{
				str << dwExploit << "#99";
				strTip << dwExploit << theXmlString.GetString( eText_Exploit );
			}			
		}	
		else if( /*pItemDetail->costType*/uchCostType == ItemDefine::CT_Honour )
		{
			// 荣誉gif, 110
			DWORD dwGlory = nCostSome;				//pItemDetail->dwCost;
			if( dwGlory > 0 )
			{
				//zhuxincong 110 变成411
				str << dwGlory << "#411";
				strTip << dwGlory << theXmlString.GetString( eText_Glory );
			}
		}
		else if( /*pItemDetail->costType*/uchCostType == ItemDefine::CT_Item )
		{
			// 令牌
			char szBuff[256];
			MeSprintf_s( szBuff, sizeof(szBuff)/sizeof(char) - 1, "%s%d", "#lp", pItemDetail->costItemID );
			if( ExpressionManager::GetInstance().GetExpressionInfo( szBuff ) )
			{
				char szTip[256];
				std::string tip = ExpressionManager::GetInstance().GetExpressionInfo( szBuff )->m_Tip;
				tip = tip.substr( tip.find( szBuff ) + strlen( szBuff ) );
				MeSprintf_s( szTip, sizeof(szTip)/sizeof(char) - 1, "%d个", nCostSome/*pItemDetail->dwCost*/ );
				strTip << szTip << tip << " ";
			}
			MeSprintf_s( szBuff, sizeof(szBuff)/sizeof(char) - 1, "%d%s%d", nCostSome/*pItemDetail->dwCost*/, "#lp", pItemDetail->costItemID );
			str << szBuff << " ";
			
		}
		else if( /*pItemDetail->costType*/uchCostType == ItemDefine::CT_GuildOffer )
		{
			// 帮贡gif,80
			int dwExploit = nCostSome;				//pItemDetail->dwCost;
			if( dwExploit > 0 )
			{
				str << dwExploit << "#80 ";
				strTip << dwExploit << theXmlString.GetString( eText_GuildOffer );
			}			
		}	
		else if( /*pItemDetail->costType*/uchCostType == ItemDefine::CT_GuildMoney )
		{
			// 帮会资金
			int dwGuildMoney = nCostSome;			//pItemDetail->dwCost;
			if( dwGuildMoney > 0 )
			{
				int gold = 0, silver = 0, copper = 0;
				thePlayerRole.GetGSCFromMoney(dwGuildMoney, gold, silver, copper);

				strTip << theXmlString.GetString( eText_GuildMoney );

				if (gold > 0)
				{
					str << gold << "#68  ";
					strTip << gold << theXmlString.GetString( eText_Money_Gold ) << "  ";
				}
				if (silver > 0)
				{
					str << silver << "#66  ";
					strTip << silver << theXmlString.GetString( eText_Money_Silver ) <<  "  ";
				}
				if (copper > 0)
				{
					str << copper << "#67  ";
					strTip << copper << theXmlString.GetString( eText_Money_Copper ) << "  ";
				}				
			}			
		}	
		else if( /*pItemDetail->costType*/uchCostType == ItemDefine::CT_GuildBuild )
		{
			// 帮会建设度
			int dwMoney = nCostSome;			//pItemDetail->dwCost;
			if( dwMoney > 0 )
			{
				str << dwMoney << "#69 ";
				strTip << dwMoney << theXmlString.GetString( eText_GuildBuild );
			}			
		}
		else if( /*pItemDetail->costType*/uchCostType == ItemDefine::CT_MasterValue )
		{
			// 师傅威望
			int dwMoney = nCostSome;			//pItemDetail->dwCost;
			if( dwMoney > 0 )
			{
				str << dwMoney << "#64 ";
				strTip << dwMoney << theXmlString.GetString( eText_WeiWang1 );
			}			
		}
        else if(/*pItemDetail->costType*/uchCostType == ItemDefine::CT_JiaoZi)
        {
            // 由于服务端2哥的改动，现在交子和金钱商店的所有物品都走交子流程，m_bBound 为 false 时为金钱商店
            // 交子
            int nCost = nCostSome;				//pItemDetail->dwCost;

			int gold = 0, silver = 0, copper = 0;
			thePlayerRole.GetGSCFromMoney(nCost, gold, silver, copper);

            if (gold > 0)
            {
                if( m_bBound )
                    str << gold << "#61  ";
                else
                    str << gold << "#81  ";
                strTip << gold << theXmlString.GetString( eText_Money_Gold ) << "  ";
            }
            if (silver > 0)
            {
                if( m_bBound )
                    str << silver << "#62  ";
                else
                    str << silver << "#82  ";
                strTip << silver << theXmlString.GetString( eText_Money_Silver ) <<  "  ";
            }
            if (copper > 0)
            {
                if( m_bBound )
                    str << copper << "#63  ";
                else
                    str << copper << "#83  ";
                strTip << copper << theXmlString.GetString( eText_Money_Copper ) << "  ";
            }
        }

		std::string text = str.str();
		ExpressionManager::GetInstance().AddExpressionAni(text);
		m_pPriceText[n]->SetText(text);
		m_pPriceText[n]->setTip( strTip.str().c_str() );
	}
}

bool CUI_ID_FRAME_SHOP::IsList(const ControlObject* pObject)
{
	if( !m_pID_FRAME_SHOP )
		return false;
	return pObject == m_pID_LISTIMG_SHOP || pObject == m_pID_LISTIMG_SHOP2;
}

DWORD CUI_ID_FRAME_SHOP::GetItemSellPrice( int nID )
{
	if( !m_pID_FRAME_SHOP )
		return -1;
	for( int i = 0 ; i < MsgAckGetShop::eMaxItem ; ++ i )
	{
		if( m_shopData.nIds[i] == nID )//found
			return m_shopData.dwSellPrices[i];
	}
	return -1;
}

CUI_ID_FRAME_SHOP::ItemCost* CUI_ID_FRAME_SHOP::GetItemCost(int nId)
{
	if( !m_pID_FRAME_SHOP )
		return NULL;
	for ( unsigned int n=0; n<m_vtItemCost.size(); n++ )
	{
		if( m_vtItemCost[n].nId == nId )
			return &m_vtItemCost[n];
	}
	return NULL;
}

void CUI_ID_FRAME_SHOP::SetRepair(bool v)
{
	if( !m_pID_FRAME_SHOP )
		return;

	theMouseManager.SetCanSetCursor(true);
	m_bRepair = v;
	if (m_bRepair)
	{
		/*s_CUI_ID_FRAME_PACK.SetDestroyItem(false);
		s_CUI_ID_FRAME_PACK.SetSplitItem(false);*/
		s_CUI_ID_FRAME_PACK.ClearMotion();
		theMouseManager.SetCursor(MouseManager::Type_Repair);
		theMouseManager.SetUICursor(MouseManager::Type_Repair);
	}
	else
	{
		theMouseManager.SetCursor(MouseManager::Type_Arrow);
		theMouseManager.SetUICursor(MouseManager::Type_Arrow);
	}
	theMouseManager.SetCanSetCursor(false);
}

static DWORD s_dwLastBuyTime = HQ_TimeGetTime();

bool CUI_ID_FRAME_SHOP::BuyItems(ControlIconDrag::S_ListImg *pItem)
{
	if (!pItem || pItem->m_eEnable == eIcon_Disable)
		return true;

	DWORD dwCurrTime = HQ_TimeGetTime();
	if (dwCurrTime - s_dwLastBuyTime < 500)
		return true;
	s_dwLastBuyTime = dwCurrTime;

	ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID(pItem->m_pkIconInfo->Id());
	if ( !pItemDetail )
		return false;

    // 安全保护
    if( CWealthProtect::Instance().IsInProtectTime() || CPreventWallow::Instance().IsFCMNotHealthy() )
        return true;

	if (m_pID_CHECKBOX_Gouhui->IsChecked())
	{
		return BuyBack(pItem);
	}

    // 都怪2哥，现在金钱商店和交子商店不用CT_JiaoZi、CT_Money区分，用m_bBound区分
    // 没有交子也没有钱
    if ( !thePlayerRole.HaveEnoughMoney(pItem->m_pkIconInfo->Cost()) && pItemDetail->costType == ItemDefine::CT_JiaoZi
        && s_CUI_ID_FRAME_SHOP.IsBoundShop() )
    {
        s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eExchange_NoJiaoziNoMoney) );
        return true;
    }
    // 没有足够的钱
    if ( thePlayerRole.GetData(CPlayerRole::TYPE_MONEY) < (pItem->m_pkIconInfo->Cost())
        && pItemDetail->costType == ItemDefine::CT_JiaoZi && !s_CUI_ID_FRAME_SHOP.IsBoundShop() )
    {
        s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eExchange_NotMoney) );
        return true;
    }

	if( theHeroGame.GetPlayerMgr()->GetMe() )
	{
		// 没有足够的名望	
		if( pItem->m_pkIconInfo->Cost() > theHeroGame.GetPlayerMgr()->GetMe()->GetReputation() && pItemDetail->costType == ItemDefine::CT_Reputation )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eExchange_NotReputation ) );
			return true;
		}
		// 没有足够的功勋	
		if( pItem->m_pkIconInfo->Cost() > theHeroGame.GetPlayerMgr()->GetMe()->GetExploit() && pItemDetail->costType == ItemDefine::CT_Exploit  )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eExchange_NotExploit ) );
			return true;
		}
		// 没有足够的帮贡	
		if( pItem->m_pkIconInfo->Cost() > theHeroGame.GetPlayerMgr()->GetMe()->GetGuildOffer() && pItemDetail->costType == ItemDefine::CT_GuildOffer  )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eExchange_NotGuildOffer ) );
			return true;
		}
		// 没有足够荣誉
		if( pItem->m_pkIconInfo->Cost() > theHeroGame.GetPlayerMgr()->GetMe()->GetGlory() && pItemDetail->costType == ItemDefine::CT_Honour  )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eExchange_GloryNotEnough ) );
			return true;
		}
	}
	// 没有足够的令牌
	if( pItemDetail->costType == ItemDefine::CT_Item )
	{		
		bool bFound = false;
		if( thePlayerRole.m_bag.GetItemCount( pItemDetail->costItemID ) >= pItemDetail->dwCost ) 			
			bFound = true;		
		else if( thePlayerRole.m_bagMaterial.GetItemCount( pItemDetail->costItemID ) >= pItemDetail->dwCost )			
			bFound = true;		
		if( !bFound )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eExchange_NotLingPai ) ) ;
			return true;
		}

	}

	ControlListImage* pBagListImg = 0;
	CItemBag2* pBag = 0;
	int bagType = BT_NormalItemBag;
	switch (pItemDetail->ucItemType)
	{
	case ItemDefine::ITEMTYPE_MATERIAL:
	case ItemDefine::ITEMTYPE_GEM:
		pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag);
		pBag = &thePlayerRole.m_bagMaterial;
		bagType = BT_MaterialBag;
		break;
	case ItemDefine::ITEMTYPE_TASK:
		pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_TaskBag);
		pBag = &thePlayerRole.m_bagTask;
		bagType = BT_TaskBag;
		break;
	default:
		pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag);
		pBag = &thePlayerRole.m_bag;
		bagType = BT_NormalItemBag;
		break;
	}

	int nPackEmptyIndex = pBag->FindNullItemOffset();
	if (nPackEmptyIndex == -1)
	{
		switch (bagType)
		{
		case BT_MaterialBag:
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_MaterialPackFull) );
			break;
		case BT_TaskBag:
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_TaskPackFull) );
			break;
		default:
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_NormalPackFull) );
			break;
		}
		return true;
	}

	/*MsgBuyOrSellGoods msg;
	msg.bIsBuy = true;
	msg.ustItemId = pItem->m_pkIconInfo->Id();
	msg.ustPackIndex = -1;
	msg.ucItemBagType = bagType;*/

	TempTransferStruct tempData;
	tempData.m_nId = pItem->m_pkIconInfo->Id();
	tempData.m_nType = bagType;
    tempData.m_bNeedJiaozi = s_CUI_ID_FRAME_SHOP.IsBoundShop();

	SCharItem* pkCharItem = (SCharItem*)(pItem->m_pkIconInfo->GetData());
	//pkCharItem->itembaseinfo.ustItemID;
	//pkCharItem->itembaseinfo.ustItemCount;
	//pkCharItem->itembaseinfo.nOnlyInt;
	//pkCharItem->itembaseinfo.n64UseTime;

	if (!pItemDetail->IsExclusive() && (GetKeyboardInput(DIK_LSHIFT) || GetKeyboardInput(DIK_RSHIFT) ) )
	{
		//请输入要购买的物品数量
		CUI_ID_FRAME_BatchShop::Show( "",
			true, true, UIShop_BuyGoodsByCount,
			&tempData, sizeof(TempTransferStruct) );

		CUI_ID_FRAME_SHOP::ItemCost* pCost = s_CUI_ID_FRAME_SHOP.GetItemCost( pItem->m_pkIconInfo->Id() );
		if (pCost && pCost->nPerCount > 1)
		{
			s_CUI_ID_FRAME_BatchShop.SetMaxValue(pCost->nPerCount);
		}
		else
		{
			if (pCost)
			{
				s_CUI_ID_FRAME_BatchShop.SetMaxValue(pItemDetail->GetStackNum());
			}
		}


		s_CUI_ID_FRAME_BatchShop.SetEditNumber( 1 );
	}
	else
	{
		int nCount = 1;
		if (!IsRemoteClose())
		{
			CPocketShopManger::SPocketShop* pShopData = thePocketShopManager.GetPocketShopItemByID(tempData.m_nId);
			if (pShopData)
			{
				nCount = 1; //pShopData->nPerCount;	按右键只购买1个
			}
		}
		
		UIShop_BuyGoods(nCount, &tempData);
	}

	return true;
}

void CUI_ID_FRAME_SHOP::RepairPack(int index)
{
	SCharItem stBagItemSrc;
	if (thePlayerRole.m_bag.IsHaveItem(index))
	{
		thePlayerRole.m_bag.GetItem( index, &stBagItemSrc );

		ItemDefine::SItemCanEquip *pItemCanEquip = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID(
			stBagItemSrc.itembaseinfo.ustItemID );
		if (!pItemCanEquip)
			return;

		int nItemHp = stBagItemSrc.equipdata.usHP;
		int nItemMaxHp = pItemCanEquip->stHPMax;
		if( nItemHp >= 0 && nItemHp < nItemMaxHp )
		{
			if (pItemCanEquip->ucItemType == ItemDefine::ITEMTYPE_WEAPON ||
				pItemCanEquip->ucItemType ==  ItemDefine::ITEMTYPE_ARMOUR)
			{
				MsgRepairItem msg;	
				CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
				if(pMe)
					msg.header.stID =  pMe->GetID();
				msg.eType = MsgRepairItem::RT_Pack;
				msg.stIndex = index;
				msg.nGuid = stBagItemSrc.itembaseinfo.nOnlyInt;
				msg.bIsCostRmb = false;
				GettheNetworkInput().SendMsg(&msg);
			}
		}
	}
}

void CUI_ID_FRAME_SHOP::RepairEquip(int index)
{
	if( !m_pID_FRAME_SHOP )
		return;
	SCharItem stBagItemSrc;
	if (thePlayerRole.m_pVisual->GetVisualArray()[index].itembaseinfo.ustItemID != InvalidLogicNumber)
	{
		ItemDefine::SItemCanEquip *pItemCanEquip = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID(
			thePlayerRole.m_pVisual->GetVisualArray()[index].itembaseinfo.ustItemID);
		if (!pItemCanEquip)
			return;

		if (thePlayerRole.m_pVisual->GetVisualArray()[index].equipdata.usHP <
			pItemCanEquip->stHPMax)
		{
			MsgRepairItem msg;	
			CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
			if(pMe)
				msg.header.stID =  pMe->GetID();
			msg.eType = MsgRepairItem::RT_Equip;
			msg.stIndex = index;
			msg.nGuid = thePlayerRole.m_pVisual->GetVisualArray()[index].itembaseinfo.nOnlyInt;
			msg.bIsCostRmb = false;
			GettheNetworkInput().SendMsg(&msg);
		}
	}
}

void CUI_ID_FRAME_SHOP::EnableShopItem()
{
	if( !m_pID_FRAME_SHOP )
		return;
	for (int i = 0; i < m_pID_LISTIMG_SHOP->GetItemCnt(); ++i)
	{
		ControlIconDrag::S_ListImg* pListImg = m_pID_LISTIMG_SHOP->GetItemByIndex(i);
		if (pListImg && !pListImg->IsNull() && pListImg->m_eEnable == eIcon_Disable)
			pListImg->m_eEnable = eIcon_Enable;
	}
	for (int i = 0; i < m_pID_LISTIMG_SHOP2->GetItemCnt(); ++i)
	{
		ControlIconDrag::S_ListImg* pListImg = m_pID_LISTIMG_SHOP2->GetItemByIndex(i);
		if (pListImg && !pListImg->IsNull() && pListImg->m_eEnable == eIcon_Disable)
			pListImg->m_eEnable = eIcon_Enable;
	}
}

void CUI_ID_FRAME_SHOP::ToggleBuyFrame()
{
	m_pID_CHECKBOX_Goumai->SetCheck(true);
	m_pID_CHECKBOX_Gouhui->SetCheck(false);
	m_pID_TEXT_Page->SetVisable(true);
	m_pID_BUTTON_Pagedown->SetVisable(true);
	m_pID_BUTTON_Pageup->SetVisable(true);

	//m_shopData = m_buyShopData;
	m_nPageNum = m_shopData.nCount % ELEMENT_COUNT ? m_shopData.nCount / ELEMENT_COUNT + 1 : m_shopData.nCount / ELEMENT_COUNT;
	if (m_nPageNum < 1)
		m_nPageNum = 1;
	if (m_nCurrPage >= m_nPageNum)
		m_nCurrPage = m_nPageNum - 1;
	m_pCurrentShopData = &m_shopData;
	TogglePage(m_nCurrPage);
}

void CUI_ID_FRAME_SHOP::ToggleReturnBuyFrame()
{
	if( !m_pID_FRAME_SHOP )
		return;
	m_pID_CHECKBOX_Goumai->SetCheck(false);
	m_pID_CHECKBOX_Gouhui->SetCheck(true);
	m_pID_TEXT_Page->SetVisable(false);
	m_pID_BUTTON_Pagedown->SetVisable(false);
	m_pID_BUTTON_Pageup->SetVisable(false);

	m_buyShopData.nCount = 0;
	for (int i = 0; i < m_BuyBackPack.GetMaxPackSize(); ++i)
	{
		SCharItem* pItem = m_BuyBackPack.GetItemByIndex(i);
		if (pItem)
		{
			int nSellMoney = theNpcShop.GetPlayerSellNpcItemCost(pItem->itembaseinfo.ustItemID,pItem->itembaseinfo.ustItemCount);
			if (nSellMoney == -1)
			{
				continue;
			}
// 			ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID(pItem->itembaseinfo.ustItemID);
// 			if ( !pItemCommon )
// 				continue;
// 
// 			int nSellMoney = 0;
// 			switch ( pItemCommon->costType )
// 			{
// 			case ItemDefine::CT_Money:
//             case ItemDefine::CT_JiaoZi:
// 				nSellMoney = pItemCommon->dwCost * 0.2 * pItem->itembaseinfo.ustItemCount;
// 				break;
// 			default:
// 				{
// 					float fMoney = pItemCommon->dwSpecialCost * 0.2 * pItem->itembaseinfo.ustItemCount;
// 					if ( fMoney < 1.0f )
// 						fMoney = 1.0f;
// 					nSellMoney = fMoney;
// 				}
// 				break;
// 			}

			m_buyShopData.nIds[i] = pItem->itembaseinfo.ustItemID;
			m_buyShopData.nGuids[i] = pItem->itembaseinfo.nOnlyInt;
			m_buyShopData.nCounts[i] = pItem->itembaseinfo.ustItemCount;
			m_buyShopData.dwSellPrices[i] = nSellMoney;
			m_buyShopData.nPackIndex[i] = i;
			
			++m_buyShopData.nCount;
		}
	}

	m_nPageNum = m_buyShopData.nCount % ELEMENT_COUNT ? m_buyShopData.nCount / ELEMENT_COUNT + 1 : m_buyShopData.nCount / ELEMENT_COUNT;
	if (m_nPageNum < 1)
		m_nPageNum = 1;
	if (m_nCurrPage >= m_nPageNum)
		m_nCurrPage = m_nPageNum - 1;
	m_pCurrentShopData = &m_buyShopData;
	TogglePage(m_nCurrPage);
	m_LockGroup.SetVisible(false);
}

bool CUI_ID_FRAME_SHOP::BuyBack(ControlIconDrag::S_ListImg *pItem)
{
	if( !m_pID_FRAME_SHOP )
		return false;
	// 没有足够的钱
	int nSellMoney = theNpcShop.GetPlayerSellNpcItemCost(pItem->m_pkIconInfo->GetItemId(),pItem->m_pkIconInfo->Count());
    if(!thePlayerRole.HaveEnoughMoney(nSellMoney))
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eExchange_NotMoney) );
		return true;
	}

	MsgBuyBackItemReq req;
	SCharItem* pkCharItem = (SCharItem*)(pItem->m_pkIconInfo->GetData());
	req.uchIndex = pkCharItem->itembaseinfo.stPacketIdx;
	req.n64Guid = pkCharItem->itembaseinfo.nOnlyInt;
	GettheNetworkInput().SendMsg( &req );
	return true;
}

bool CUI_ID_FRAME_SHOP::CHECKBOX_Goumai_IsChecked()
{
	if( !m_pID_FRAME_SHOP )
		return false;
	return m_pID_CHECKBOX_Goumai->IsChecked();
}

bool CUI_ID_FRAME_SHOP::CHECKBOX_Gouhui_IsChecked()
{
	if( !m_pID_FRAME_SHOP )
		return false;
	return m_pID_CHECKBOX_Gouhui->IsChecked();
}

void CUI_ID_FRAME_SHOP::ClearBuyBackPack()
{
	if( !m_pID_FRAME_SHOP )
		return;
	m_BuyBackPack.ClearPack();
}

void CUI_ID_FRAME_SHOP::UpdateMyInfo()
{
	if( !m_pID_FRAME_SHOP )
		return;

// 	char str[256];
// 	MeSprintf_s(str,sizeof(str)/sizeof(char) - 1,"%d{#99}",theHeroGame.GetPlayerMgr()->GetMe()->GetExploit());
// // 	*m_pID_TEXT_Exploit = str;
// 
// 	MeSprintf_s(str,sizeof(str)/sizeof(char) - 1,"%d{#98}",theHeroGame.GetPlayerMgr()->GetMe()->GetReputation());
// 	*m_pID_TEXT_Reputation = str;
// 
// 	MeSprintf_s(str,sizeof(str)/sizeof(char) - 1,"%d{#64}",thePlayerRole.GetMasterValue());
// 	*m_pID_TEXT_Prestige = str;
// 
// 	MeSprintf_s(str,sizeof(str)/sizeof(char) - 1,"%d{#80}",theHeroGame.GetPlayerMgr()->GetMe()->GetGuildOffer());
// 	*m_pID_TEXT_Guildoffer = str;
// 
// 	MeSprintf_s(str,sizeof(str)/sizeof(char) - 1,"%d{#lp4907}",thePlayerRole.m_bagMaterial.GetItemCount( 4907 ));
// 	*m_pID_TEXT_CopperBrand = str;
// 
// 	MeSprintf_s(str,sizeof(str)/sizeof(char) - 1,"%d{#lp4906}",thePlayerRole.m_bagMaterial.GetItemCount( 4906 ));
// 	*m_pID_TEXT_BlackBrand = str;
// 
// 	MeSprintf_s(str,sizeof(str)/sizeof(char) - 1,"%d{#lp4908}",thePlayerRole.m_bag.GetItemCount( 4908 ));
// 	*m_pID_TEXT_BattleBrand = str;
// 
// 	MeSprintf_s(str,sizeof(str)/sizeof(char) - 1,"%d{#lp4904}",thePlayerRole.m_bagMaterial.GetItemCount( 4904 ));
// 	*m_pID_TEXT_GoldBrand = str;

	DWORD money = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
	int gold = 0,silver = 0,copper = 0;

    thePlayerRole.GetGSCFromMoney(money,gold,silver,copper);

	std::stringstream str1;
	std::string str2;

	if(gold==0&&silver!=0)
	{
		str1 << silver << "{#82} ";
	}
	else if(gold!=0)
	{
		str1 << gold << "{#81} ";
		if(copper>0||silver>0)
		{
			str1 << silver << "{#82} ";
		}
	}
	if(copper>0||(gold==0&&silver==0))
	{
		str1 << copper << "{#83} ";
	}

	str2 = str1.str();
// 	*m_pID_TEXT_Money = str2;
}

//-----------------------------------------------------------------------------------------------------------------------------
//帮会商店
void CUI_ID_FRAME_SHOP::SetGuildShop(int nLevel)
{
	m_nGuildShoplevel = nLevel;
	s_CUI_ID_FRAME_SHOP.SetVisable(true);
	m_bGuildShop = true;
	m_LockGroup.SetVisible(true);
	RefreshGuildShop();
}

bool CUI_ID_FRAME_SHOP::ID_BUTTON_ActiveOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SHOP )
		return false;

	MsgGuildShopLevelUpReq msg;
	msg.uchLevel = m_nGuildShoplevel;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

void CUI_ID_FRAME_SHOP::RefreshGuildShop()
{
	if (!IsVisable())
	{
		return;
	}
	
	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if(pGuild == NULL || pGuild->GetGuildID() == GuildDefine::InitID)
	{
		return;
	}

	m_PriceGroup.SetVisible(false);
	m_LockGroup.SetVisible(true);
		
	RefreshGuildShopData();

	ToggleBuyFrame();

	SetGuildShopActived();
	
	m_pID_TEXT_CurrentMoney->SetText(theHeroGame.GetPlayerMgr()->GetMe()->GetGuildOffer());
}

void CUI_ID_FRAME_SHOP::SetGuildShopActived()
{
	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if(pGuild == NULL || pGuild->GetGuildID() == GuildDefine::InitID)
	{
		return;
	}

	if (pGuild->CheckShopActive(m_nGuildShoplevel))
	{
		m_PriceGroup.SetVisible(true);
		m_LockGroup.SetVisible(false);
		EnableShopItem();
	}
}

const int MaxBuyNum = 256;
void CUI_ID_FRAME_SHOP::RefreshGuildShopData()
{
	m_vtItemCost.clear();
	m_shopData.Clear();
	m_buyShopData.Clear();

	const GuildConfig::ShopSetting* pShopSetting = theGuildConfig.GetShopSetting(m_nGuildShoplevel);

	if (!pShopSetting)
	{
		return;
	}
	//加载帮派商店的物品数据
	std::map< unsigned int, unsigned int > ItemData = pShopSetting->GetItemMap();
	std::map< unsigned int, unsigned int >::const_iterator iter = ItemData.begin();
	for (int i = 0; iter != ItemData.end() && i < ShopData::eMaxItem; ++iter, ++i)
	{
		ItemCost stItemCost;
		stItemCost.nId = iter->first;
		m_shopData.nIds[i] = stItemCost.nId;
		stItemCost.nCost = iter->second;
		m_shopData.dwSellPrices[i] = stItemCost.nCost;
		stItemCost.nPerCount = 99;
		m_shopData.nBuyCounts[i] = stItemCost.nPerCount;
		m_shopData.nCounts[i] = 1;
		m_vtItemCost.push_back( stItemCost );
	}
	m_shopData.nCount = ItemData.size();
	//SetLockText(m_buyShopData.nCount);
}

void CUI_ID_FRAME_SHOP::SetLockText(int nItemNum, int nCurrentPage)
{
	const int nItemPerPage = 10;
	int nLockNum = 0;
	if (nCurrentPage * nItemPerPage <= nItemNum)
	{
		nLockNum = nItemPerPage;
	}
	else
	{
		nLockNum = nItemNum - (nCurrentPage - 1) * nItemPerPage;
	}
	
	for (std::vector<ControlText*>::iterator iter = m_vctLock.begin(); iter != m_vctLock.end(); ++iter)
	{
		(*iter)->Clear();
	}

	for (int i = 0; i < nLockNum; ++i)
	{
		if (!m_vctLock[i])
		{
			continue;
		}
		m_vctLock[i]->SetText("未激活");
	}


}

void CUI_ID_FRAME_SHOP::UpdataCurrentMoney()
{
	if (!m_bGuildShop || !m_pID_TEXT_CurrentMoney)
	{
		return;
	}

	m_pID_TEXT_CurrentMoney->SetText(theHeroGame.GetPlayerMgr()->GetMe()->GetGuildOffer());
}
//-----------------------------------------------------------------------------------------------------------------------------

bool CUI_ID_FRAME_SHOP::IsBoundShop()
{
    return m_bBound;
}

void CUI_ID_FRAME_SHOP::SellItem(ControlObject* pSender, ControlIconDrag::S_ListImg* pItemDrag)
{
	if (!pSender || !pItemDrag || pItemDrag->IsNull())
		return;
	if ( !s_CUI_ID_FRAME_PACK.IsVisable() )
		return;
	if ( !s_CUI_ID_FRAME_SHOP.CHECKBOX_Goumai_IsChecked() )
		return;

	if(m_bGuildShop)
	{
		//公会商店不允许出售物品
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_Guild_SellItem));
		return;
	}

	ControlListImage* pBagListImg = 0;
	CItemBag2* pBag = 0;
	int bagType = 0;

	int nIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItemDrag );
	if (nIndex != -1)
	{
		pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag);
		pBag = &thePlayerRole.m_bag;
		bagType = BT_NormalItemBag;
	}
	else if ( (nIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem(BT_MaterialBag, pItemDrag)) != -1 )
	{
		pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag);
		pBag = &thePlayerRole.m_bagMaterial;
		bagType = BT_MaterialBag;
	}
	else
	{
		return;
	}

	s_CUI_ID_FRAME_PACK.SellItem(pItemDrag, pBagListImg, pBag, bagType);
}