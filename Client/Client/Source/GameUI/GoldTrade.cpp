/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\chixin.ni\桌面\金锭UI\GoldTrade.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GoldTrade.h"
#include "Player.h"
#include "GoldTradeRegiste.h"
#include "GoldTradeTransfer.h"
#include "GoldTradeSelect.h"
#include "SuperPasswordReset.h"
#include "SuperPasswordRegister.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "NetworkInput.h"
#include "Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "ScreenInfoManager.h"
#include "color_config.h"
#include "Common.h"
#include "Sociality.h"
#include "PlayerRole.h"
#include "WealthProtect.h"

#define TRADE_TAX 0.02
#define SortCountIndex 4

bool StartTrade( const char bPressYesButton, void *pData )
{
	if(bPressYesButton && pData)
	{
		MsgConsignmentMoneyReq msg;
		::CopyMemory(&msg,pData,sizeof(MsgConsignmentMoneyReq));
		GettheNetworkInput().SendMsg( &msg );
	}
	return true;
}

bool BuyTrade( const char bPressYesButton, void *pData )
{
	if(bPressYesButton && pData)
	{
		MsgConsignmentOperateReq msg;
		::CopyMemory(&msg,pData,sizeof(MsgConsignmentOperateReq));
		GettheNetworkInput().SendMsg( &msg );
	}
	return true;
}


CUI_ID_FRAME_GoldTrade s_CUI_ID_FRAME_GoldTrade;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GoldTrade, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GoldTrade, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_LIST_SellOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_helpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_CLOSEOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_LIST_SellPriceOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_LIST_BuyPriceOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_LIST_SellTypeOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_LIST_SellGoldOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_LIST_SellUnitPriceOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_BuyOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_LIST_BuyOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_SellOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_LIST_BuyTypeOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_LIST_BuyGoldOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_LIST_BuyUnitPriceOnListSelectChange )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_EDIT_GoldNumberOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_SetPriceOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_DepositOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_ReceiveOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_RefreshOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_SetPasswordOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_RegisteOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_SellPriceOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_SellGoldOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_SellUnitPriceOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_BuyPriceOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_BuyGoldOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_BuyUnitPriceOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_SellTypeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_BuyTypeOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_CHECKBOX_BuyEntrustOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_CHECKBOX_SellTrustOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_MaxOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_BuyFilterOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_SellFilterOnButtonClick )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_COMBOBOX_SendTargetOnComboBoxChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_CHECKBOX_BuyListAllOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_CHECKBOX_BuyListMeOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_CHECKBOX_SellListAllOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_CHECKBOX_SellListMeOnCheckBoxCheck )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_EDIT_GoldOnEditEnter )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_COMBOBOX_FilterOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_COMBOBOX_Filter2OnComboBoxChange )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_EDIT_NumOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_EDIT_Num2OnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_SearchOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTrade, ID_BUTTON_Search2OnButtonClick )
CUI_ID_FRAME_GoldTrade::CUI_ID_FRAME_GoldTrade()
{
	// Member
	ResetMembers();
}

void CUI_ID_FRAME_GoldTrade::ResetMembers()
{
	m_pID_FRAME_GoldTrade = NULL;
	m_pID_PICTURE_EntrustWall = NULL;
	m_pID_PICTURE_Sell = NULL;
	m_pID_PICTURE_26447 = NULL;
	m_pID_LIST_Sell = NULL;
	m_pID_PICTURE_TitleMiddle = NULL;
	m_pID_PICTURE_Title = NULL;
	m_pID_PICTURE_TitleLeft = NULL;
	m_pID_PICTURE_TitleRight = NULL;
	m_pID_PICTURE_TitleL = NULL;
	m_pID_PICTURE_TradeEntrust = NULL;
	m_pID_PICTURE_TltleR = NULL;
	m_pID_BUTTON_help = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_LIST_SellPrice = NULL;
	m_pID_LIST_BuyPrice = NULL;
	m_pID_LIST_SellType = NULL;
	m_pID_LIST_SellGold = NULL;
	m_pID_TEXT_TradeList = NULL;
	m_pID_LIST_SellUnitPrice = NULL;
	m_pID_BUTTON_Buy = NULL;
	m_pID_PICTURE_Buy = NULL;
	m_pID_PICTURE_264473 = NULL;
	m_pID_LIST_Buy = NULL;
	m_pID_BUTTON_Sell = NULL;
	m_pID_LIST_BuyType = NULL;
	m_pID_LIST_BuyGold = NULL;
	m_pID_LIST_BuyUnitPrice = NULL;
	m_pID_TEXT_UnitPrice1 = NULL;
	m_pID_TEXT_UnitPrice = NULL;
	m_pID_TEXT_BuyGoldNumber = NULL;
	m_pID_TEXT_SellGoldNumber = NULL;
	m_pID_EDIT_GoldNumber = NULL;
	m_pID_TEXT_CostMoney = NULL;
	m_pID_TEXT_GetMoney = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_TEXT_Tax1 = NULL;
	m_pID_TEXT_Tax = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_SetPrice = NULL;
	m_pID_TEXT_Trade = NULL;
	m_pID_PICTURE_Trade = NULL;
	m_pID_TEXT_TradeGold1 = NULL;
	m_pID_TEXT_TradeGold = NULL;
	m_pID_TEXT_TradeMoney1 = NULL;
	m_pID_TEXT_TradeMoney = NULL;
	m_pID_BUTTON_Deposit = NULL;
	m_pID_BUTTON_Receive = NULL;
	m_pID_TEXT_Self = NULL;
	m_pID_PICTURE_Self = NULL;
	m_pID_TEXT_SelfGold1 = NULL;
	m_pID_TEXT_SelfGold = NULL;
	m_pID_TEXT_SelfMoney1 = NULL;
	m_pID_TEXT_SelfMoney = NULL;
	m_pID_BUTTON_Refresh = NULL;
	m_pID_BUTTON_SetPassword = NULL;
	m_pID_BUTTON_Registe = NULL;
	m_pID_BUTTON_SellPrice = NULL;
	m_pID_BUTTON_SellGold = NULL;
	m_pID_BUTTON_SellUnitPrice = NULL;
	m_pID_BUTTON_BuyPrice = NULL;
	m_pID_BUTTON_BuyGold = NULL;
	m_pID_BUTTON_BuyUnitPrice = NULL;
	m_pID_BUTTON_SellType = NULL;
	m_pID_BUTTON_BuyType = NULL;
	m_pID_CHECKBOX_BuyEntrust = NULL;
	m_pID_CHECKBOX_SellTrust = NULL;
	m_pID_BUTTON_Max = NULL;
	m_pID_BUTTON_BuyFilter = NULL;
	m_pID_BUTTON_SellFilter = NULL;
	m_pID_TEXT_Appoint = NULL;
	m_pID_COMBOBOX_SendTarget = NULL;
	m_pID_CHECKBOX_BuyListAll = NULL;
	m_pID_CHECKBOX_BuyListMe = NULL;
	m_pID_TEXT_ID_BuyListAll = NULL;
	m_pID_TEXT_ID_BuyListMe = NULL;
	m_pID_CHECKBOX_SellListAll = NULL;
	m_pID_CHECKBOX_SellListMe = NULL;
	m_pID_TEXT_ID_SellListAll = NULL;
	m_pID_TEXT_ID_SellListMe = NULL;
	m_pID_LIST_Sell = NULL;
	m_pID_LIST_Buy = NULL;
	m_pID_PICTURE_22611 = NULL;
	m_pID_PICTURE_226112 = NULL;
	m_pID_PICTURE_2261122 = NULL;
	m_pID_EDIT_Gold = NULL;
	m_pID_PICTURE_26210 = NULL;
	m_pID_TEXT_ArrowSellUnitPrice = NULL;
	m_pID_TEXT_ArrowBuyUnitPrice = NULL;
	m_pID_TEXT_ArrowSellGold = NULL;
	m_pID_TEXT_ArrowBuyGold = NULL;
	m_pID_TEXT_ArrowSellPrice = NULL;
	m_pID_TEXT_ArrowBuyPrice = NULL;
	m_pID_COMBOBOX_Filter = NULL;
	m_pID_COMBOBOX_Filter2 = NULL;
	m_pID_EDIT_Num = NULL;
	m_pID_EDIT_Num2 = NULL;
	m_pID_BUTTON_Search = NULL;
	m_pID_BUTTON_Search2 = NULL;
	m_pID_TEXT_TradeList2 = NULL;
	m_pID_EDIT_Silver = NULL;
	m_pID_EDIT_Copper = NULL;

	m_dwCoolDownButton = 0;
}
// Frame
bool CUI_ID_FRAME_GoldTrade::OnFrameRun()
{
	if( IsVisable() )
	{
		int nStartIndex = m_pID_LIST_Sell->GetShowStartHeight();

		m_pID_LIST_SellPrice->SetShowStartHeight(nStartIndex);
		m_pID_LIST_SellType->SetShowStartHeight(nStartIndex);
		m_pID_LIST_SellGold->SetShowStartHeight(nStartIndex);
		m_pID_LIST_SellUnitPrice->SetShowStartHeight(nStartIndex);


		nStartIndex = m_pID_LIST_Buy->GetShowStartHeight();

		m_pID_LIST_BuyPrice->SetShowStartHeight(nStartIndex);
		m_pID_LIST_BuyType->SetShowStartHeight(nStartIndex);
		m_pID_LIST_BuyGold->SetShowStartHeight(nStartIndex);
		m_pID_LIST_BuyUnitPrice->SetShowStartHeight(nStartIndex);


		int sel = m_pID_LIST_Sell->GetCurSelIndex();

		if(sel == -1)
		{
			m_pID_BUTTON_Buy->SetEnable(false);
		}
		else
		{
			m_pID_BUTTON_Buy->SetEnable(true);
		}

		sel = m_pID_LIST_Buy->GetCurSelIndex();

		if(sel == -1)
		{
			m_pID_BUTTON_Sell->SetEnable(false);
		}
		else
		{
			m_pID_BUTTON_Sell->SetEnable(true);
		}

		/*if(atoi(m_pID_EDIT_Gold->GetText())==0)
		{
			string str = "1";
			*m_pID_EDIT_Gold = str;
		}*/
		//CheckPrice();
	}
	return true;
}
bool CUI_ID_FRAME_GoldTrade::OnFrameRender()
{
	//if( IsVisable() )
	//{
	//	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
	//	if ( pMe )
	//	{
	//		float fMeX,fMeY,fMeZ;			
	//		pMe->GetPos( &fMeX, &fMeY, &fMeZ );
	//		float dist = pMe->GetDistToTarget( m_vVisiblePos.x, m_vVisiblePos.y );
	//		//这个UI不是npc身上呼出来的吧？
	//		//if( dist > 7.0f )
	//		//{
	//		//	SetVisable( false );
	//		//}
	//	}
	//}

	return true;
}
// List
void CUI_ID_FRAME_GoldTrade::ID_LIST_SellOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_GoldTrade )
		return;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;
	SetVisable(false);
	return true;
}
// List
void CUI_ID_FRAME_GoldTrade::ID_LIST_SellPriceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_GoldTrade )
		return;
}
// List
void CUI_ID_FRAME_GoldTrade::ID_LIST_BuyPriceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_GoldTrade )
		return;
}
// List
void CUI_ID_FRAME_GoldTrade::ID_LIST_SellTypeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_GoldTrade )
		return;
}
// List
void CUI_ID_FRAME_GoldTrade::ID_LIST_SellGoldOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_GoldTrade )
		return;
}
// List
void CUI_ID_FRAME_GoldTrade::ID_LIST_SellUnitPriceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_GoldTrade )
		return;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_BuyOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;
	
	if(!IsProtectedTime())
		return true;

	int sel = m_pID_LIST_Sell->GetCurSelIndex();
	if(sel!=-1&&sel<m_vecSell.size())
	{
		MsgConsignmentOperateReq msg;
		msg.uchOperate = ConsignmentDefine::Operate_Buy;
		msg.n64ConsignmentID = m_vecSell[sel].GetID();
		msg.uchConsignmentType = m_vecSell[sel].GetType();

		int gold = 0, silver = 0, copper = 0;
		thePlayerRole.GetGSCFromMoney(m_vecSell[sel].GetPrice() * m_vecSell[sel].GetCount(), gold, silver, copper);
		char str[256] = {0};
		char str2[256] = {0};
		if (gold > 0)
		{
			if (silver > 0)
			{
				if (copper > 0)
				{
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#81}%d{#82}%d{#83}",gold,silver,copper);
				}
				else
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#81}%d{#82}",gold,silver);
			}
			else
			{
				if (copper > 0)
				{
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#81}%d{#83}",gold,copper);
				}
				else
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#81}",gold);
			}
		}
		else
		{
			if (silver > 0)
			{
				if (copper > 0)
				{
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#82}%d{#83}",silver,copper);
				}
				else
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#82}",silver);
			}
			else
			{
				MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#83}",copper);
			}
		}
		/*if(gold>0)
		{
			MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d金",gold);
			if(silver>0)
			{
				MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%s%d银",str,silver);
				if(copper>0)
				{
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%s%d铜",str,copper);
				}
			}
			else if(copper>0)
			{
				MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%s%d铜",str,copper);
			}
		}
		else
		{
			if(silver>0)
			{
				MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d银",silver);
				if(copper>0)
				{
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%s%d铜",str,copper);
				}
			}
			else if(copper>0)
			{
				MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d铜",copper);
			}
		}*/

		MeSprintf_s(str2,sizeof(str2)/sizeof(char)-1,theXmlString.GetString(eText_GoldTrade_BuyConfirmleft),str,m_vecSell[sel].GetCount());

		s_CUI_ID_FRAME_MessageBox.Show( str2,"" ,
			CUI_ID_FRAME_MessageBox::eTypeYesNo,false,BuyTrade,&msg,sizeof(MsgConsignmentOperateReq));
	}
	return true;
}
// List
void CUI_ID_FRAME_GoldTrade::ID_LIST_BuyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_GoldTrade )
		return;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_SellOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;

	if(!IsProtectedTime())
		return true;

	int sel = m_pID_LIST_Buy->GetCurSelIndex();
	if(sel!=-1&&sel<m_vecBuy.size())
	{
		MsgConsignmentOperateReq msg;
		msg.uchOperate = ConsignmentDefine::Operate_Sell;
		msg.n64ConsignmentID = m_vecBuy[sel].GetID();
		msg.uchConsignmentType = m_vecBuy[sel].GetType();

		int gold = 0, silver = 0, copper = 0;
		thePlayerRole.GetGSCFromMoney(m_vecBuy[sel].GetPrice(), gold, silver, copper);
		char str[256] = {0};
		char str2[256] = {0};
		if (gold > 0)
		{
			if (silver > 0)
			{
				if (copper > 0)
				{
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#81}%d{#82}%d{#83}",gold,silver,copper);
				}
				else
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#81}%d{#82}",gold,silver);
			}
			else
			{
				if (copper > 0)
				{
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#81}%d{#83}",gold,copper);
				}
				else
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#81}",gold);
			}
		}
		else
		{
			if (silver > 0)
			{
				if (copper > 0)
				{
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#82}%d{#83}",silver,copper);
				}
				else
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#82}",silver);
			}
			else
			{
				MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#83}",copper);
			}
		}
		/*if(gold>0)
		{
			MeSprintf_s(str,sizeof(str)/sizeof(char)-1,theXmlString.GetString(eTextMoney_Gold),gold);
			if(silver>0)
			{
				MeSprintf_s(str,sizeof(str)/sizeof(char)-1,theXmlString.GetString(eTextMoney_StringSilver),str,silver);
				if(copper>0)
				{
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,theXmlString.GetString(eTextMoney_StringCopper),str,copper);
				}
			}
			else if(copper>0)
			{
				MeSprintf_s(str,sizeof(str)/sizeof(char)-1,theXmlString.GetString(eTextMoney_StringCopper),str,copper);
			}
		}
		else
		{
			if(silver>0)
			{
				MeSprintf_s(str,sizeof(str)/sizeof(char)-1,theXmlString.GetString(eTextMoney_StringSilver),silver);
				if(copper>0)
				{
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,theXmlString.GetString(eTextMoney_StringCopper),str,copper);
				}
			}
			else if(copper>0)
			{
				MeSprintf_s(str,sizeof(str)/sizeof(char)-1,theXmlString.GetString(eTextMoney_Copper),copper);
			}
		}*/

		MeSprintf_s(str2,sizeof(str2)/sizeof(char)-1,theXmlString.GetString(eText_GoldTrade_SellConfirmleft),str,m_vecBuy[sel].GetCount());

		s_CUI_ID_FRAME_MessageBox.Show( str2,"" ,
			CUI_ID_FRAME_MessageBox::eTypeYesNo,false,BuyTrade,&msg,sizeof(MsgConsignmentOperateReq));
	}
	return true;
}
// List
void CUI_ID_FRAME_GoldTrade::ID_LIST_BuyTypeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_GoldTrade )
		return;
}
// List
void CUI_ID_FRAME_GoldTrade::ID_LIST_BuyGoldOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_GoldTrade )
		return;
}
// List
void CUI_ID_FRAME_GoldTrade::ID_LIST_BuyUnitPriceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_GoldTrade )
		return;
}
// Edit
void CUI_ID_FRAME_GoldTrade::ID_EDIT_GoldNumberOnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_GoldTrade )
		return;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade||m_nUnitPrice <= 0)
		return false;
	
	if(!IsProtectedTime())
		return true;

	if(m_nSell>=15)
	{
		MsgConsignmentMoneyReq msg;
		if(m_pID_CHECKBOX_BuyEntrust->IsChecked())
			msg.xConsignment.SetType(ConsignmentDefine::Consignment_BuyRMB);
		else
			msg.xConsignment.SetType(ConsignmentDefine::Consignment_SellRMB);

		msg.xConsignment.SetPrice(m_nUnitPrice);  //买的价格
		msg.xConsignment.SetCount(m_nSell);

		char szWord[256] = {0};
		MeSprintf_s(szWord, sizeof(szWord)/sizeof(char) - 1,"%s", m_pID_COMBOBOX_SendTarget->GetEditInput().GetText());
		int nPlayerID = thePlayerRole.GetdbID(szWord);
		if(nPlayerID != -1)
		    msg.xConsignment.SetBuyPlayerID(nPlayerID);

		int gold = 0, silver = 0, copper = 0;
		thePlayerRole.GetGSCFromMoney(m_nUnitPrice*m_nSell, gold, silver, copper);
		char str[256] = {0};
		char str2[256] = {0};
		if (gold > 0)
		{
			if (silver > 0)
			{
				if (copper > 0)
				{
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#81}%d{#82}%d{#83}",gold,silver,copper);
				}
				else
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#81}%d{#82}",gold,silver);
			}
			else
			{
				if (copper > 0)
				{
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#81}%d{#83}",gold,copper);
				}
				else
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#81}",gold);
			}
		}
		else
		{
			if (silver > 0)
			{
				if (copper > 0)
				{
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#82}%d{#83}",silver,copper);
				}
				else
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#82}",silver);
			}
			else
			{
				MeSprintf_s(str,sizeof(str)/sizeof(char)-1,"%d{#83}",copper);
			}
		}
		/*if(gold>0)
		{
			MeSprintf_s(str,sizeof(str)/sizeof(char)-1,theXmlString.GetString(eTextMoney_Gold),gold);
			if(silver>0)
			{
				MeSprintf_s(str,sizeof(str)/sizeof(char)-1,theXmlString.GetString(eTextMoney_StringSilver),str,silver);
				if(copper>0)
				{
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,theXmlString.GetString(eTextMoney_StringCopper),str,copper);
				}
			}
			else if(copper>0)
			{
				MeSprintf_s(str,sizeof(str)/sizeof(char)-1,theXmlString.GetString(eTextMoney_StringCopper),str,copper);
			}
		}
		else
		{
			if(silver>0)
			{
				MeSprintf_s(str,sizeof(str)/sizeof(char)-1,theXmlString.GetString(eTextMoney_Silver),silver);
				if(copper>0)
				{
					MeSprintf_s(str,sizeof(str)/sizeof(char)-1,theXmlString.GetString(eTextMoney_StringCopper),str,copper);
				}
			}
			else if(copper>0)
			{
				MeSprintf_s(str,sizeof(str)/sizeof(char)-1,theXmlString.GetString(eTextMoney_Copper),copper);
			}
		}*/

		if(m_pID_CHECKBOX_BuyEntrust->IsChecked())
		{
			MeSprintf_s(str2,sizeof(str2)/sizeof(char)-1,theXmlString.GetString(eText_GoldTrade_BuyConfirm),str,m_nSell);
		}
		else
		{
			MeSprintf_s(str2,sizeof(str2)/sizeof(char)-1,theXmlString.GetString(eText_GoldTrade_SellConfirm),str,m_nSell);
		}
		

		s_CUI_ID_FRAME_MessageBox.Show( str2,"" ,
			CUI_ID_FRAME_MessageBox::eTypeYesNo,false,StartTrade,&msg,sizeof(MsgConsignmentMoneyReq));
	}
	else
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_GoldTrade_TooLess) );
	}

	return true;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_SetPriceOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_DepositOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;

	if(!IsProtectedTime())
		return true;

	s_CUI_ID_FRAME_GoldTradeDeposit.SetPush();
	s_CUI_ID_FRAME_GoldTradeDeposit.SetVisable(true);
	return true;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_ReceiveOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;

	if(!IsProtectedTime())
		return true;

	s_CUI_ID_FRAME_GoldTradeDeposit.SetPop();
	s_CUI_ID_FRAME_GoldTradeDeposit.SetVisable(true);
	return true;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_RefreshOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;

	MsgQueryConsignmentList msg;
	msg.uchConsignmentType = ConsignmentDefine::Consignment_BuyRMB;
	
	if( m_pID_CHECKBOX_BuyListAll->IsChecked() )
		msg.uchQueryType = ConsignmentDefine::Sort_Normal;
	else if( m_pID_CHECKBOX_BuyListMe->IsChecked() )
		msg.uchQueryType = ConsignmentDefine::Sort_ForMe;

	msg.nCount = m_nBuyFilter;
	GettheNetworkInput().SendMsg( &msg );


	msg.uchConsignmentType = ConsignmentDefine::Consignment_SellRMB;
	msg.nCount = m_nSellFilter;

	GettheNetworkInput().SendMsg( &msg );

	m_pID_LIST_Buy->SetCurSelIndex(-1);
	m_pID_LIST_Buy->Clear();
	m_pID_LIST_BuyPrice->Clear();
	m_pID_LIST_BuyType->Clear();
	m_pID_LIST_BuyGold->Clear();
	m_pID_LIST_BuyUnitPrice->Clear();

	m_pID_LIST_Sell->SetCurSelIndex(-1);
	m_pID_LIST_Sell->Clear();
	m_pID_LIST_SellPrice->Clear();
	m_pID_LIST_SellType->Clear();
	m_pID_LIST_SellGold->Clear();
	m_pID_LIST_SellUnitPrice->Clear();

	return true;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_SetPasswordOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;
	if(thePlayerRole.GetIsSecondPassword())
	{
		s_CUI_ID_FRAME_SuperPasswordReset.Reset();
		s_CUI_ID_FRAME_SuperPasswordReset.SetVisable(true);
		s_CUI_ID_FRAME_SuperPasswordReset.SetVisiblePosition(Vector(0,0,0));

		theUiManager.SetFocus(s_CUI_ID_FRAME_SuperPasswordReset.GetID_EDIT_AddName3());
	}
	else
	{
		s_CUI_ID_FRAME_SuperPasswordRegister.Reset();
		s_CUI_ID_FRAME_SuperPasswordRegister.SetVisable(true);
		s_CUI_ID_FRAME_SuperPasswordRegister.SetVisiblePosition(Vector(0,0,0));

		theUiManager.SetFocus(s_CUI_ID_FRAME_SuperPasswordRegister.GetEDIT_AddName());
	}
	return true;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_RegisteOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;
	if(!s_CUI_ID_FRAME_GoldTradeRegiste.IsVisable())
	{
		s_CUI_ID_FRAME_GoldTradeRegiste.SetVisable(true);

		MsgConsignmentMoneyHistroyReq msg;
		GettheNetworkInput().SendMsg( &msg );
	}
	else
	{
		s_CUI_ID_FRAME_GoldTradeRegiste.SetVisable(false);
	}

	return true;
}

struct LessByUnitPrice
{
	bool operator()(const ConsignmentBase& v1, const ConsignmentBase& v2)
	{
		if (v1.GetPrice()/v1.GetCount() > v2.GetPrice()/v2.GetCount())
			return true;
		else
			return false;
		return false;
	}
}; 
struct MoreByUnitPrice
{
	bool operator()(const ConsignmentBase& v1, const ConsignmentBase& v2)
	{
		if (v1.GetPrice()/v1.GetCount() < v2.GetPrice()/v2.GetCount())
			return true;
		else
			return false;
		return false;
	}
}; 
struct LessByGold
{
	bool operator()(const ConsignmentBase& v1, const ConsignmentBase& v2)
	{
		if (v1.GetCount() > v2.GetCount())
			return true;
		else
			return false;
		return false;
	}
}; 
struct MoreByGold
{
	bool operator()(const ConsignmentBase& v1, const ConsignmentBase& v2)
	{
		if (v1.GetCount() < v2.GetCount())
			return true;
		else
			return false;
		return false;
	}
}; 
struct LessByPrice
{
	bool operator()(const ConsignmentBase& v1, const ConsignmentBase& v2)
	{
		if (v1.GetPrice() > v2.GetPrice())
			return true;
		else
			return false;
		return false;
	}
}; 
struct MoreByPrice
{
	bool operator()(const ConsignmentBase& v1, const ConsignmentBase& v2)
	{
		if (v1.GetPrice() < v2.GetPrice())
			return true;
		else
			return false;
		return false;
	}
}; 
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_SellPriceOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;
	ClearSellSort();
	if(m_SellPriceSort)
	{
		sort(m_vecSell.begin(),m_vecSell.end(),MoreByPrice());
		*m_pID_TEXT_ArrowSellPrice = "{#203}";
	}
	else
	{
		sort(m_vecSell.begin(),m_vecSell.end(),LessByPrice());
		*m_pID_TEXT_ArrowSellPrice = "{#204}";
	}

	m_SellPriceSort = !m_SellPriceSort;
	m_SellUnitPriceSort = false;
	m_SellGoldSort = false;

	RefreshList();

	return true;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_SellGoldOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;
	ClearSellSort();

	if(m_SellGoldSort)
	{
		sort(m_vecSell.begin(),m_vecSell.end(),MoreByGold());
		*m_pID_TEXT_ArrowSellGold = "{#203}";
	}
	else
	{
		sort(m_vecSell.begin(),m_vecSell.end(),LessByGold());
		*m_pID_TEXT_ArrowSellGold = "{#204}";
	}

	m_SellGoldSort = !m_SellGoldSort;
	m_SellUnitPriceSort = false;
	m_SellPriceSort = false;

	RefreshList();

	return true;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_SellUnitPriceOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;
	ClearSellSort();

	if(m_SellUnitPriceSort)
	{
		sort(m_vecSell.begin(),m_vecSell.end(),MoreByUnitPrice());
		*m_pID_TEXT_ArrowSellUnitPrice = "{#203}";
	}
	else
	{
		sort(m_vecSell.begin(),m_vecSell.end(),LessByUnitPrice());
		*m_pID_TEXT_ArrowSellUnitPrice = "{#204}";
	}

	m_SellUnitPriceSort = !m_SellUnitPriceSort;
	m_SellGoldSort = false;
	m_SellPriceSort = false;

	RefreshList();

	return true;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_BuyPriceOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;
	ClearBuySort();

	if(m_BuyPriceSort)
	{
		sort(m_vecBuy.begin(),m_vecBuy.end(),MoreByUnitPrice());
		*m_pID_TEXT_ArrowBuyPrice = "{#203}";
	}
	else
	{
		sort(m_vecBuy.begin(),m_vecBuy.end(),LessByUnitPrice());
		*m_pID_TEXT_ArrowBuyPrice = "{#204}";
	}

	m_BuyPriceSort = !m_BuyPriceSort;
	m_BuyUnitPriceSort = false;
	m_BuyGoldSort = false;

	RefreshList();
	return true;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_BuyGoldOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;
	ClearBuySort();

	if(m_BuyGoldSort)
	{
		sort(m_vecBuy.begin(),m_vecBuy.end(),MoreByGold());
		*m_pID_TEXT_ArrowBuyGold = "{#203}";
	}
	else
	{
		sort(m_vecBuy.begin(),m_vecBuy.end(),LessByGold());
		*m_pID_TEXT_ArrowBuyGold = "{#204}";
	}

	m_BuyGoldSort = !m_BuyGoldSort;
	m_BuyPriceSort = false;
	m_BuyUnitPriceSort = false;

	RefreshList();

	return true;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_BuyUnitPriceOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;
	ClearBuySort();

	if(m_BuyUnitPriceSort)
	{
		sort(m_vecBuy.begin(),m_vecBuy.end(),MoreByUnitPrice());
		*m_pID_TEXT_ArrowBuyUnitPrice = "{#203}";
	}
	else
	{
		sort(m_vecBuy.begin(),m_vecBuy.end(),LessByUnitPrice());
		*m_pID_TEXT_ArrowBuyUnitPrice = "{#204}";
	}

	m_BuyUnitPriceSort = !m_BuyUnitPriceSort;
	m_BuyPriceSort = false;
	m_BuyGoldSort = false;

	RefreshList();

	return true;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_SellTypeOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_BuyTypeOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;
	return true;
}
// CheckBox
void CUI_ID_FRAME_GoldTrade::ID_CHECKBOX_BuyEntrustOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_GoldTrade )
		return;
	m_pID_CHECKBOX_BuyEntrust->SetCheck(true);
	m_pID_CHECKBOX_SellTrust->SetCheck(false);
	m_pID_BUTTON_Max->SetVisable(false);

	m_pID_TEXT_BuyGoldNumber->SetVisable(true);
	m_pID_TEXT_SellGoldNumber->SetVisable(false);

	m_pID_TEXT_CostMoney->SetVisable(true);
	m_pID_TEXT_GetMoney->SetVisable(false);

	CheckPrice();

	Refresh();
}
// CheckBox
void CUI_ID_FRAME_GoldTrade::ID_CHECKBOX_SellTrustOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_GoldTrade )
		return;
	m_pID_CHECKBOX_BuyEntrust->SetCheck(false);
	m_pID_CHECKBOX_SellTrust->SetCheck(true);
	m_pID_BUTTON_Max->SetVisable(true);

	m_pID_TEXT_BuyGoldNumber->SetVisable(false);
	m_pID_TEXT_SellGoldNumber->SetVisable(true);

	m_pID_TEXT_CostMoney->SetVisable(false);
	m_pID_TEXT_GetMoney->SetVisable(true);

	CheckPrice();

	Refresh();
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_MaxOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;
	m_nSell = thePlayerRole.GetData(CPlayerRole::TYPE_TradeJinDing);

	m_pID_EDIT_GoldNumber->SetText(m_nSell);

	CheckPrice();

	Refresh();

	return true;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_BuyFilterOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;
	s_CUI_ID_FRAME_GoldTradeSelect.SetVisable(true);
	s_CUI_ID_FRAME_GoldTradeSelect.SetBuy();
	return true;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_SellFilterOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GoldTrade )
		return false;
	s_CUI_ID_FRAME_GoldTradeSelect.SetVisable(true);
	s_CUI_ID_FRAME_GoldTradeSelect.SetSell();
	return true;
}
// ComboBox
void CUI_ID_FRAME_GoldTrade::ID_COMBOBOX_SendTargetOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_GoldTrade )
		return;
}
// CheckBox
void CUI_ID_FRAME_GoldTrade::ID_CHECKBOX_BuyListAllOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_GoldTrade )
		return;
	m_pID_CHECKBOX_BuyListAll->SetCheck(true);
	m_pID_CHECKBOX_BuyListMe->SetCheck(false);

	MsgQueryConsignmentList msg;
	msg.uchConsignmentType =  ConsignmentDefine::Consignment_SellRMB;
	msg.uchQueryType = ConsignmentDefine::Sort_Normal;
	msg.nCount = 0;

	GettheNetworkInput().SendMsg( &msg );

	m_nBuyFilter = -1;
}
// CheckBox
void CUI_ID_FRAME_GoldTrade::ID_CHECKBOX_BuyListMeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_GoldTrade )
		return;
	m_pID_CHECKBOX_BuyListAll->SetCheck(false);
	m_pID_CHECKBOX_BuyListMe->SetCheck(true);

	MsgQueryConsignmentList msg;
	msg.uchConsignmentType =  ConsignmentDefine::Consignment_SellRMB;
	msg.uchQueryType = ConsignmentDefine::Sort_ForMe;
	msg.nCount = 0;

	GettheNetworkInput().SendMsg( &msg );

	m_nBuyFilter = -1;
}
// CheckBox
void CUI_ID_FRAME_GoldTrade::ID_CHECKBOX_SellListAllOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_GoldTrade )
		return;
	m_pID_CHECKBOX_SellListAll->SetCheck(true);
	m_pID_CHECKBOX_SellListMe->SetCheck(false);

	MsgQueryConsignmentList msg;
	msg.uchConsignmentType =  ConsignmentDefine::Consignment_BuyRMB;
	msg.uchQueryType = ConsignmentDefine::Sort_Normal;
	msg.nCount = 0;

	GettheNetworkInput().SendMsg( &msg );

	m_nSellFilter = -1;
}
// CheckBox
void CUI_ID_FRAME_GoldTrade::ID_CHECKBOX_SellListMeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_GoldTrade )
		return;
	m_pID_CHECKBOX_SellListAll->SetCheck(false);
	m_pID_CHECKBOX_SellListMe->SetCheck(true);

	MsgQueryConsignmentList msg;
	msg.uchConsignmentType =  ConsignmentDefine::Consignment_BuyRMB;
	msg.uchQueryType = ConsignmentDefine::Sort_ForMe;
	msg.nCount = 0;

	GettheNetworkInput().SendMsg( &msg );

	m_nSellFilter = -1;
}
	// Edit
void CUI_ID_FRAME_GoldTrade::ID_EDIT_GoldOnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_GoldTrade )
		return;
}

// ComboBox
void CUI_ID_FRAME_GoldTrade::ID_COMBOBOX_FilterOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if(m_pID_COMBOBOX_Filter->GetListBox().GetCurSelIndex() ==  SortCountIndex)
	{
		m_pID_EDIT_Num->SetEnable(true);
		m_pID_EDIT_Num->SetReadOnly(false);
		theUiManager.SetFocus(m_pID_EDIT_Num);
	}
	else
	{
		m_pID_EDIT_Num->SetEnable(false);
		m_pID_EDIT_Num->SetReadOnly(true);
	}

}

// ComboBox
void CUI_ID_FRAME_GoldTrade::ID_COMBOBOX_Filter2OnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if(m_pID_COMBOBOX_Filter2->GetListBox().GetCurSelIndex() ==  SortCountIndex)
	{
		m_pID_EDIT_Num2->SetEnable(true);
		m_pID_EDIT_Num2->SetReadOnly(false);
		theUiManager.SetFocus(m_pID_EDIT_Num2);
	}
	else
	{
		m_pID_EDIT_Num2->SetEnable(false);
		m_pID_EDIT_Num2->SetReadOnly(true);
	}
}
// Edit
void CUI_ID_FRAME_GoldTrade::ID_EDIT_NumOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Edit
void CUI_ID_FRAME_GoldTrade::ID_EDIT_Num2OnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_SearchOnButtonClick( ControlObject* pSender )
{
	if (m_pID_CHECKBOX_BuyListMe->IsChecked())
	{
		MsgQueryConsignmentList msg;
		msg.uchConsignmentType =  ConsignmentDefine::Consignment_SellRMB;
		msg.uchQueryType = ConsignmentDefine::Sort_ForMe;
		msg.nCount = 0;

		GettheNetworkInput().SendMsg( &msg );

		m_nBuyFilter = -1;
		return true;
	}

	int nIndex = m_pID_COMBOBOX_Filter->GetListBox().GetCurSelIndex();
	SendSortMsg(nIndex);
	return true;
}
// Button
bool CUI_ID_FRAME_GoldTrade::ID_BUTTON_Search2OnButtonClick( ControlObject* pSender )
{
	if (m_pID_CHECKBOX_SellListMe->IsChecked())
	{
		MsgQueryConsignmentList msg;
		msg.uchConsignmentType =  ConsignmentDefine::Consignment_BuyRMB;
		msg.uchQueryType = ConsignmentDefine::Sort_ForMe;
		msg.nCount = 0;

		GettheNetworkInput().SendMsg( &msg );

		m_nSellFilter = -1;
		return true;
	}

	int nIndex = m_pID_COMBOBOX_Filter2->GetListBox().GetCurSelIndex();
	SendSortMsg(nIndex,true);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_GoldTrade::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GoldTrade.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GoldTrade.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GoldTrade::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GoldTrade, s_CUI_ID_FRAME_GoldTradeOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GoldTrade, s_CUI_ID_FRAME_GoldTradeOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_GoldTrade, ID_LIST_Sell, s_CUI_ID_FRAME_GoldTradeID_LIST_SellOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_help, s_CUI_ID_FRAME_GoldTradeID_BUTTON_helpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_GoldTradeID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_GoldTrade, ID_LIST_SellPrice, s_CUI_ID_FRAME_GoldTradeID_LIST_SellPriceOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GoldTrade, ID_LIST_BuyPrice, s_CUI_ID_FRAME_GoldTradeID_LIST_BuyPriceOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GoldTrade, ID_LIST_SellType, s_CUI_ID_FRAME_GoldTradeID_LIST_SellTypeOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GoldTrade, ID_LIST_SellGold, s_CUI_ID_FRAME_GoldTradeID_LIST_SellGoldOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GoldTrade, ID_LIST_SellUnitPrice, s_CUI_ID_FRAME_GoldTradeID_LIST_SellUnitPriceOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_Buy, s_CUI_ID_FRAME_GoldTradeID_BUTTON_BuyOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_GoldTrade, ID_LIST_Buy, s_CUI_ID_FRAME_GoldTradeID_LIST_BuyOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_Sell, s_CUI_ID_FRAME_GoldTradeID_BUTTON_SellOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_GoldTrade, ID_LIST_BuyType, s_CUI_ID_FRAME_GoldTradeID_LIST_BuyTypeOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GoldTrade, ID_LIST_BuyGold, s_CUI_ID_FRAME_GoldTradeID_LIST_BuyGoldOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GoldTrade, ID_LIST_BuyUnitPrice, s_CUI_ID_FRAME_GoldTradeID_LIST_BuyUnitPriceOnListSelectChange );
	theUiManager.OnEditEnter( ID_FRAME_GoldTrade, ID_EDIT_GoldNumber, s_CUI_ID_FRAME_GoldTradeID_EDIT_GoldNumberOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_OK, s_CUI_ID_FRAME_GoldTradeID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_SetPrice, s_CUI_ID_FRAME_GoldTradeID_BUTTON_SetPriceOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_Deposit, s_CUI_ID_FRAME_GoldTradeID_BUTTON_DepositOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_Receive, s_CUI_ID_FRAME_GoldTradeID_BUTTON_ReceiveOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_Refresh, s_CUI_ID_FRAME_GoldTradeID_BUTTON_RefreshOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_SetPassword, s_CUI_ID_FRAME_GoldTradeID_BUTTON_SetPasswordOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_Registe, s_CUI_ID_FRAME_GoldTradeID_BUTTON_RegisteOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_SellPrice, s_CUI_ID_FRAME_GoldTradeID_BUTTON_SellPriceOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_SellGold, s_CUI_ID_FRAME_GoldTradeID_BUTTON_SellGoldOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_SellUnitPrice, s_CUI_ID_FRAME_GoldTradeID_BUTTON_SellUnitPriceOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_BuyPrice, s_CUI_ID_FRAME_GoldTradeID_BUTTON_BuyPriceOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_BuyGold, s_CUI_ID_FRAME_GoldTradeID_BUTTON_BuyGoldOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_BuyUnitPrice, s_CUI_ID_FRAME_GoldTradeID_BUTTON_BuyUnitPriceOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_SellType, s_CUI_ID_FRAME_GoldTradeID_BUTTON_SellTypeOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_BuyType, s_CUI_ID_FRAME_GoldTradeID_BUTTON_BuyTypeOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GoldTrade, ID_CHECKBOX_BuyEntrust, s_CUI_ID_FRAME_GoldTradeID_CHECKBOX_BuyEntrustOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GoldTrade, ID_CHECKBOX_SellTrust, s_CUI_ID_FRAME_GoldTradeID_CHECKBOX_SellTrustOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_Max, s_CUI_ID_FRAME_GoldTradeID_BUTTON_MaxOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_BuyFilter, s_CUI_ID_FRAME_GoldTradeID_BUTTON_BuyFilterOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_SellFilter, s_CUI_ID_FRAME_GoldTradeID_BUTTON_SellFilterOnButtonClick );
	theUiManager.OnComboBoxChange( ID_FRAME_GoldTrade, ID_COMBOBOX_SendTarget, s_CUI_ID_FRAME_GoldTradeID_COMBOBOX_SendTargetOnComboBoxChange );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GoldTrade, ID_CHECKBOX_BuyListAll, s_CUI_ID_FRAME_GoldTradeID_CHECKBOX_BuyListAllOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GoldTrade, ID_CHECKBOX_BuyListMe, s_CUI_ID_FRAME_GoldTradeID_CHECKBOX_BuyListMeOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GoldTrade, ID_CHECKBOX_SellListAll, s_CUI_ID_FRAME_GoldTradeID_CHECKBOX_SellListAllOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GoldTrade, ID_CHECKBOX_SellListMe, s_CUI_ID_FRAME_GoldTradeID_CHECKBOX_SellListMeOnCheckBoxCheck );
	theUiManager.OnEditEnter( ID_FRAME_GoldTrade, ID_EDIT_Gold, s_CUI_ID_FRAME_GoldTradeID_EDIT_GoldOnEditEnter );
	theUiManager.OnComboBoxChange( ID_FRAME_GoldTrade, ID_COMBOBOX_Filter, s_CUI_ID_FRAME_GoldTradeID_COMBOBOX_FilterOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_GoldTrade, ID_COMBOBOX_Filter2, s_CUI_ID_FRAME_GoldTradeID_COMBOBOX_Filter2OnComboBoxChange );
	theUiManager.OnEditEnter( ID_FRAME_GoldTrade, ID_EDIT_Num, s_CUI_ID_FRAME_GoldTradeID_EDIT_NumOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_GoldTrade, ID_EDIT_Num2, s_CUI_ID_FRAME_GoldTradeID_EDIT_Num2OnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_Search, s_CUI_ID_FRAME_GoldTradeID_BUTTON_SearchOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTrade, ID_BUTTON_Search2, s_CUI_ID_FRAME_GoldTradeID_BUTTON_Search2OnButtonClick );

	m_pID_FRAME_GoldTrade = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GoldTrade );
	m_pID_PICTURE_EntrustWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_PICTURE_EntrustWall );
	m_pID_PICTURE_Sell = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_PICTURE_Sell );
	m_pID_PICTURE_26447 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_PICTURE_26447 );
	m_pID_LIST_Sell = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_LIST_Sell );
	m_pID_PICTURE_TitleMiddle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_PICTURE_TitleMiddle );
	m_pID_PICTURE_Title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_PICTURE_Title );
	m_pID_PICTURE_TitleLeft = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_PICTURE_TitleLeft );
	m_pID_PICTURE_TitleRight = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_PICTURE_TitleRight );
	m_pID_PICTURE_TitleL = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_PICTURE_TitleL );
	m_pID_PICTURE_TradeEntrust = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_PICTURE_TradeEntrust );
	m_pID_PICTURE_TltleR = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_PICTURE_TltleR );
	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_help );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_CLOSE );
	m_pID_LIST_SellPrice = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_LIST_SellPrice );
	m_pID_LIST_BuyPrice = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_LIST_BuyPrice );
	m_pID_LIST_SellType = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_LIST_SellType );
	m_pID_LIST_SellGold = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_LIST_SellGold );
	m_pID_TEXT_TradeList = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_TradeList );
	m_pID_LIST_SellUnitPrice = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_LIST_SellUnitPrice );
	m_pID_BUTTON_Buy = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_Buy );
	m_pID_PICTURE_Buy = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_PICTURE_Buy );
	m_pID_PICTURE_264473 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_PICTURE_264473 );
	m_pID_LIST_Buy = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_LIST_Buy );
	m_pID_BUTTON_Sell = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_Sell );
	m_pID_LIST_BuyType = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_LIST_BuyType );
	m_pID_LIST_BuyGold = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_LIST_BuyGold );
	m_pID_LIST_BuyUnitPrice = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_LIST_BuyUnitPrice );
	m_pID_TEXT_UnitPrice1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_UnitPrice1 );
	m_pID_TEXT_UnitPrice = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_UnitPrice );
	m_pID_TEXT_BuyGoldNumber = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_BuyGoldNumber );
	m_pID_TEXT_SellGoldNumber = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_SellGoldNumber );
	m_pID_EDIT_GoldNumber = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_EDIT_GoldNumber );
	m_pID_TEXT_CostMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_CostMoney );
	m_pID_TEXT_GetMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_GetMoney );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_Money );
	m_pID_TEXT_Tax1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_Tax1 );
	m_pID_TEXT_Tax = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_Tax );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_OK );
	m_pID_BUTTON_SetPrice = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_SetPrice );
	m_pID_TEXT_Trade = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_Trade );
	m_pID_PICTURE_Trade = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_PICTURE_Trade );
	m_pID_TEXT_TradeGold1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_TradeGold1 );
	m_pID_TEXT_TradeGold = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_TradeGold );
	m_pID_TEXT_TradeMoney1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_TradeMoney1 );
	m_pID_TEXT_TradeMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_TradeMoney );
	m_pID_BUTTON_Deposit = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_Deposit );
	m_pID_BUTTON_Receive = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_Receive );
	m_pID_TEXT_Self = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_Self );
	m_pID_PICTURE_Self = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_PICTURE_Self );
	m_pID_TEXT_SelfGold1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_SelfGold1 );
	m_pID_TEXT_SelfGold = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_SelfGold );
	m_pID_TEXT_SelfMoney1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_SelfMoney1 );
	m_pID_TEXT_SelfMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_SelfMoney );
	m_pID_BUTTON_Refresh = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_Refresh );
	m_pID_BUTTON_SetPassword = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_SetPassword );
	m_pID_BUTTON_Registe = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_Registe );
	m_pID_BUTTON_SellPrice = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_SellPrice );
	m_pID_BUTTON_SellGold = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_SellGold );
	m_pID_BUTTON_SellUnitPrice = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_SellUnitPrice );
	m_pID_BUTTON_BuyPrice = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_BuyPrice );
	m_pID_BUTTON_BuyGold = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_BuyGold );
	m_pID_BUTTON_BuyUnitPrice = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_BuyUnitPrice );
	m_pID_BUTTON_SellType = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_SellType );
	m_pID_BUTTON_BuyType = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_BuyType );
	m_pID_CHECKBOX_BuyEntrust = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_CHECKBOX_BuyEntrust );
	m_pID_CHECKBOX_SellTrust = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_CHECKBOX_SellTrust );
	m_pID_BUTTON_Max = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_Max );
	m_pID_BUTTON_BuyFilter = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_BuyFilter );
	m_pID_BUTTON_SellFilter = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_SellFilter );
	m_pID_TEXT_Appoint = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_Appoint );
	m_pID_COMBOBOX_SendTarget = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_COMBOBOX_SendTarget );
	m_pID_CHECKBOX_BuyListAll = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_CHECKBOX_BuyListAll );
	m_pID_CHECKBOX_BuyListMe = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_CHECKBOX_BuyListMe );
	m_pID_TEXT_ID_BuyListAll = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_ID_BuyListAll );
	m_pID_TEXT_ID_BuyListMe = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_ID_BuyListMe );
	m_pID_CHECKBOX_SellListAll = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_CHECKBOX_SellListAll );
	m_pID_CHECKBOX_SellListMe = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_CHECKBOX_SellListMe );
	m_pID_TEXT_ID_SellListAll = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_ID_SellListAll );
	m_pID_TEXT_ID_SellListMe = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_ID_SellListMe );
	m_pID_LIST_Sell = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_LIST_Sell );
	m_pID_LIST_Buy = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_LIST_Buy );
	m_pID_PICTURE_22611 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_PICTURE_22611 );
	m_pID_PICTURE_226112 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_PICTURE_226112 );
	m_pID_PICTURE_2261122 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_PICTURE_2261122 );
	m_pID_EDIT_Gold = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_EDIT_Gold );
	m_pID_PICTURE_26210 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_PICTURE_26210 );
	m_pID_TEXT_ArrowSellUnitPrice = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_ArrowSellUnitPrice );
	m_pID_TEXT_ArrowBuyUnitPrice = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_ArrowBuyUnitPrice );
	m_pID_TEXT_ArrowSellGold = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_ArrowSellGold );
	m_pID_TEXT_ArrowBuyGold = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_ArrowBuyGold );
	m_pID_TEXT_ArrowSellPrice = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_ArrowSellPrice );
	m_pID_TEXT_ArrowBuyPrice = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_ArrowBuyPrice );
	m_pID_COMBOBOX_Filter = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_COMBOBOX_Filter );
	m_pID_COMBOBOX_Filter2 = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_COMBOBOX_Filter2 );
	m_pID_EDIT_Num = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_EDIT_Num );
	m_pID_EDIT_Num2 = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_EDIT_Num2 );
	m_pID_BUTTON_Search = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_Search );
	m_pID_BUTTON_Search2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_BUTTON_Search2 );
	m_pID_TEXT_TradeList2 = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_TEXT_TradeList2 );
	m_pID_EDIT_Silver = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_EDIT_Silver );
	m_pID_EDIT_Copper = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GoldTrade, ID_EDIT_Copper );
	assert( m_pID_FRAME_GoldTrade );
	assert( m_pID_PICTURE_EntrustWall );
	assert( m_pID_PICTURE_Sell );
	assert( m_pID_PICTURE_26447 );
	assert( m_pID_LIST_Sell );
	assert( m_pID_PICTURE_TitleMiddle );
	assert( m_pID_PICTURE_Title );
	assert( m_pID_PICTURE_TitleLeft );
	assert( m_pID_PICTURE_TitleRight );
	assert( m_pID_PICTURE_TitleL );
	assert( m_pID_PICTURE_TradeEntrust );
	assert( m_pID_PICTURE_TltleR );
	assert( m_pID_BUTTON_help );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_LIST_SellPrice );
	assert( m_pID_LIST_BuyPrice );
	assert( m_pID_LIST_SellType );
	assert( m_pID_LIST_SellGold );
	assert( m_pID_TEXT_TradeList );
	assert( m_pID_LIST_SellUnitPrice );
	assert( m_pID_BUTTON_Buy );
	assert( m_pID_PICTURE_Buy );
	assert( m_pID_PICTURE_264473 );
	assert( m_pID_LIST_Buy );
	assert( m_pID_BUTTON_Sell );
	assert( m_pID_LIST_BuyType );
	assert( m_pID_LIST_BuyGold );
	assert( m_pID_LIST_BuyUnitPrice );
	assert( m_pID_TEXT_UnitPrice1 );
	assert( m_pID_TEXT_UnitPrice );
	assert( m_pID_TEXT_BuyGoldNumber );
	assert( m_pID_TEXT_SellGoldNumber );
	assert( m_pID_EDIT_GoldNumber );
	assert( m_pID_TEXT_CostMoney );
	assert( m_pID_TEXT_GetMoney );
	assert( m_pID_TEXT_Money );
	assert( m_pID_TEXT_Tax1 );
	assert( m_pID_TEXT_Tax );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_SetPrice );
	assert( m_pID_TEXT_Trade );
	assert( m_pID_PICTURE_Trade );
	assert( m_pID_TEXT_TradeGold1 );
	assert( m_pID_TEXT_TradeGold );
	assert( m_pID_TEXT_TradeMoney1 );
	assert( m_pID_TEXT_TradeMoney );
	assert( m_pID_BUTTON_Deposit );
	assert( m_pID_BUTTON_Receive );
	assert( m_pID_TEXT_Self );
	assert( m_pID_PICTURE_Self );
	assert( m_pID_TEXT_SelfGold1 );
	assert( m_pID_TEXT_SelfGold );
	assert( m_pID_TEXT_SelfMoney1 );
	assert( m_pID_TEXT_SelfMoney );
	assert( m_pID_BUTTON_Refresh );
	assert( m_pID_BUTTON_SetPassword );
	assert( m_pID_BUTTON_Registe );
	assert( m_pID_BUTTON_SellPrice );
	assert( m_pID_BUTTON_SellGold );
	assert( m_pID_BUTTON_SellUnitPrice );
	assert( m_pID_BUTTON_BuyPrice );
	assert( m_pID_BUTTON_BuyGold );
	assert( m_pID_BUTTON_BuyUnitPrice );
	assert( m_pID_BUTTON_SellType );
	assert( m_pID_BUTTON_BuyType );
	assert( m_pID_CHECKBOX_BuyEntrust );
	assert( m_pID_CHECKBOX_SellTrust );
	assert( m_pID_BUTTON_Max );
	assert( m_pID_BUTTON_BuyFilter );
	assert( m_pID_BUTTON_SellFilter );
	assert( m_pID_TEXT_Appoint );
	assert( m_pID_COMBOBOX_SendTarget );
	assert( m_pID_CHECKBOX_BuyListAll );
	assert( m_pID_CHECKBOX_BuyListMe );
	assert( m_pID_TEXT_ID_BuyListAll );
	assert( m_pID_TEXT_ID_BuyListMe );
	assert( m_pID_CHECKBOX_SellListAll );
	assert( m_pID_CHECKBOX_SellListMe );
	assert( m_pID_TEXT_ID_SellListAll );
	assert( m_pID_TEXT_ID_SellListMe );
	assert( m_pID_COMBOBOX_Filter );
	assert( m_pID_COMBOBOX_Filter2 );
	assert( m_pID_EDIT_Num );
	assert( m_pID_EDIT_Num2 );
	assert( m_pID_BUTTON_Search );
	assert( m_pID_BUTTON_Search2 );
	assert( m_pID_TEXT_TradeList2 );
	assert( m_pID_EDIT_Silver );
	assert( m_pID_EDIT_Copper );
	SetVisable(false);

	m_pID_LIST_SellPrice->HaveSelBar(false);
	m_pID_LIST_SellType->HaveSelBar(false);
	m_pID_LIST_SellGold->HaveSelBar(false);
	m_pID_LIST_SellUnitPrice->HaveSelBar(false);

	m_pID_LIST_BuyPrice->HaveSelBar(false);
	m_pID_LIST_BuyType->HaveSelBar(false);
	m_pID_LIST_BuyGold->HaveSelBar(false);
	m_pID_LIST_BuyUnitPrice->HaveSelBar(false);

	m_pID_LIST_Sell->SetDrawFlags(DT_CENTER|DT_NOCLIP);
	m_pID_LIST_SellPrice->SetDrawFlags(DT_CENTER|DT_NOCLIP);
	m_pID_LIST_SellType->SetDrawFlags(DT_CENTER|DT_NOCLIP);
	m_pID_LIST_SellGold->SetDrawFlags(DT_CENTER|DT_NOCLIP);
	m_pID_LIST_SellUnitPrice->SetDrawFlags(DT_CENTER|DT_NOCLIP);

	m_pID_LIST_Buy->SetDrawFlags(DT_CENTER|DT_NOCLIP);
	m_pID_LIST_BuyPrice->SetDrawFlags(DT_CENTER|DT_NOCLIP);
	m_pID_LIST_BuyType->SetDrawFlags(DT_CENTER|DT_NOCLIP);
	m_pID_LIST_BuyGold->SetDrawFlags(DT_CENTER|DT_NOCLIP);
	m_pID_LIST_BuyUnitPrice->SetDrawFlags(DT_CENTER|DT_NOCLIP);


	m_pID_CHECKBOX_BuyEntrust->SetCheck(true);
	m_pID_CHECKBOX_SellTrust->SetCheck(false);
	m_pID_BUTTON_Max->SetVisable(false);

	m_pID_TEXT_BuyGoldNumber->SetVisable(true);
	m_pID_TEXT_SellGoldNumber->SetVisable(false);
	m_pID_TEXT_CostMoney->SetVisable(true);
	m_pID_TEXT_GetMoney->SetVisable(false);

	m_pID_CHECKBOX_BuyListAll->SetCheck(true);
	m_pID_CHECKBOX_BuyListMe->SetCheck(false);

	m_pID_CHECKBOX_SellListAll->SetCheck(true);
	m_pID_CHECKBOX_SellListMe->SetCheck(false);

	m_pID_EDIT_GoldNumber->SetMaxLength(5);

	m_pID_EDIT_GoldNumber->SetTextChangedFun(CUI_ID_FRAME_GoldTrade::EditDataChange);

	m_pID_EDIT_Gold->SetTextChangedFun(CUI_ID_FRAME_GoldTrade::EditUnitPriceGold);
	m_pID_EDIT_Silver->SetTextChangedFun(CUI_ID_FRAME_GoldTrade::EditUnitPriceSilver);
	m_pID_EDIT_Copper->SetTextChangedFun(CUI_ID_FRAME_GoldTrade::EditUnitPriceCopper);
	m_pID_EDIT_Gold->SetMaxLength(4);
	m_pID_EDIT_Silver->SetMaxLength(2);
	m_pID_EDIT_Copper->SetMaxLength(2);

	m_nUnitPrice = 0;

	m_nSell = 0;

	m_nBuyFilter = -1;
	m_nSellFilter = -1;

	*m_pID_EDIT_Gold = "0";
	*m_pID_EDIT_Silver = "0";
	*m_pID_EDIT_Copper = "0";


	m_SellPriceSort = false;
	m_SellUnitPriceSort = false;
	m_SellGoldSort = false;
	m_BuyPriceSort = false;
	m_BuyUnitPriceSort = false;
	m_BuyGoldSort = false;

	InitComboxString();

	m_pID_EDIT_Num->SetEnable(false);
	m_pID_EDIT_Num->SetReadOnly(true);

	m_pID_EDIT_Num2->SetEnable(false);
	m_pID_EDIT_Num2->SetReadOnly(true);

	m_pID_FRAME_GoldTrade->SetMsgProcFun(GolgTradeFrame_MsgProc);

	Refresh();

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GoldTrade::_UnLoadUI()
{
	m_pID_FRAME_GoldTrade = NULL;
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\GoldTrade.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GoldTrade::_IsVisable()
{
	if(m_pID_FRAME_GoldTrade)
		return m_pID_FRAME_GoldTrade->IsVisable();

	return false;
}
// 设置是否可视
void CUI_ID_FRAME_GoldTrade::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_GoldTrade)
		return;
	
	m_pID_FRAME_GoldTrade->SetVisable( bVisable );

	if( bVisable )
	{
		MsgOperateMoneyReq msg;
		msg.nRMBMoney = 0;
		msg.nGameMoney = 0;
		msg.uchOperate = ConsignmentDefine::Operate_TakeOut;
		GettheNetworkInput().SendMsg( &msg );


		Refresh();
		RefreshList();
	}
	else
	{
		m_pID_CHECKBOX_BuyListAll->SetCheck(true);
		m_pID_CHECKBOX_BuyListMe->SetCheck(false);

		m_pID_CHECKBOX_SellListAll->SetCheck(true);
		m_pID_CHECKBOX_SellListMe->SetCheck(false);

		m_pID_COMBOBOX_SendTarget->GetEditInput().SetText("");
	}
}

void CUI_ID_FRAME_GoldTrade::Refresh()
{
	if(!m_pID_FRAME_GoldTrade)
		return;
	//self
	std::stringstream str;
	std::string text = "";

	DWORD dwMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
	int gold = 0,silver = 0,copper = 0;
	// 用统一格式显示金币
	thePlayerRole.GetGSCStringFromMoney(dwMoney,text);
	*m_pID_TEXT_SelfMoney = text;

	str.str("");

	str << thePlayerRole.GetData(/*CPlayerRole::TYPE_JinDing*/CPlayerRole::TYPE_JinPiao) << /*"{#1103} "*/"{#1104} ";

	text = str.str();
	*m_pID_TEXT_SelfGold = text;

	str.str("");
	//trade
	dwMoney = thePlayerRole.GetData(CPlayerRole::TYPE_TradeMoney);
	// 用统一格式显示金币
	text = "";
	thePlayerRole.GetGSCStringFromMoney(dwMoney,text);
	*m_pID_TEXT_TradeMoney = text;

	str.str("");

	str << thePlayerRole.GetData(CPlayerRole::TYPE_TradeJinDing) << /*"{#1103} "*/"{#1104} ";

	text = str.str();

	*m_pID_TEXT_TradeGold = text;

	//单价
	str.str("");
	//trade
	// 用统一格式显示金币
	text = "";
	thePlayerRole.GetGSCStringFromMoney(m_nUnitPrice,text);
	*m_pID_TEXT_UnitPrice = text;

	//价格
	DWORD price = m_nSell*m_nUnitPrice;

	str.str("");
	//trade
	// 用统一格式显示金币
	text = "";
	thePlayerRole.GetGSCStringFromMoney(price,text);
	*m_pID_TEXT_Money = text;

	//手续费////////////
	if(m_pID_CHECKBOX_BuyEntrust->IsChecked())
	{
		price *= TRADE_TAX;

		str.str("");
		//trade
		thePlayerRole.GetGSCFromMoney(price, gold, silver, copper);
		if(price>0)
		{
			if(gold==0&&silver!=0)
			{
				str << silver << "{#82} ";
			}
			else if(gold!=0)
			{
				str << gold << "{#81} ";
				if(copper>0||silver>0)
				{
					str << silver << "{#82} ";
				}
			}
			if(copper>0)
			{
				str << copper << "{#83} ";
			}
		}
		else
		{
			str << copper << "{#83} ";
		}

		text = str.str();
		*m_pID_TEXT_Tax = text;
	}
	else
	{
		int tax = ConsignmentDefine::GetConsignmentCost(m_nSell);//(int)(m_nSell * TRADE_TAX +0.5f);
		if(tax<1)
		{
			tax = 1;
		}
		str.str("");

		str<< tax << /*"{#1103}"*/"{#1104}";

		text = str.str();
		*m_pID_TEXT_Tax = text;
	}

	m_pID_COMBOBOX_SendTarget->GetListBox().Clear();

	map<int, RelationDataToClient>::iterator iter = thePlayerRole.GetMapFriendInfo().begin();

	char buf[128] = {0};
	ControlList::S_List	stItem;
	stItem.SetData( "" );
	m_pID_COMBOBOX_SendTarget->GetListBox().AddItem(&stItem,NULL,false);

	for(;iter != thePlayerRole.GetMapFriendInfo().end();++iter)
	{
		if (!thePlayerRole.IsFriend((*iter).second.GetName()))
			continue;

		MeSprintf_s(buf, sizeof(buf)/sizeof(char)-1, "%s",(*iter).second.GetName() );
		stItem.SetData( buf );
		m_pID_COMBOBOX_SendTarget->GetListBox().AddItem(&stItem,NULL,false);
	}
}

void CUI_ID_FRAME_GoldTrade::SetUnitPrice( int price )
{
	if(price>0)
	{
		m_nUnitPrice = price;
	}
	else
	{
		m_nUnitPrice = 0;
	}

	CheckPrice();

	Refresh();
}

int CUI_ID_FRAME_GoldTrade::GetGoldNumber()
{
	if(m_pID_EDIT_GoldNumber)
		return atoi(m_pID_EDIT_GoldNumber->GetText());
	else
		return 0;
}

int CUI_ID_FRAME_GoldTrade::GetUnitPrice()
{	
	int g = 0;
	int s = 0;
	int c =	0;

	if (m_pID_EDIT_Gold)
	{
		g = atoi(m_pID_EDIT_Gold->GetText())*10000;
	}
	if (m_pID_EDIT_Silver)
	{
		s = atoi(m_pID_EDIT_Silver->GetText())*100;
	}
	if (m_pID_EDIT_Copper)
	{
		c = atoi(m_pID_EDIT_Copper->GetText());
	}

	return g+s+c;

	/*if(m_pID_EDIT_Gold)
		return atoi(m_pID_EDIT_Gold->GetText())*10000;
	else
		return 0;*/
}

void CUI_ID_FRAME_GoldTrade::SetTextMoney(string str)
{
	if(m_pID_TEXT_Money)
		*m_pID_TEXT_Money = str;
}

void CUI_ID_FRAME_GoldTrade::SetTextTax(string str)
{
	if(m_pID_TEXT_Tax)
		*m_pID_TEXT_Tax = str;
}

void CUI_ID_FRAME_GoldTrade::SetnSell(int i)
{
	m_nSell = i;
}

int CUI_ID_FRAME_GoldTrade::GetnSell()
{
	return m_nSell;
}

void CUI_ID_FRAME_GoldTrade::CheckPrice()
{
	if(!m_pID_FRAME_GoldTrade)
		return;

	DWORD price = GetPrice();

	int nSell = 0;
	if(m_pID_CHECKBOX_BuyEntrust->IsChecked())
	{
		//price += price*TRADE_TAX;
		int nCost = ConsignmentDefine::GetConsignmentCost(price);
		price += nCost;

		if(price > thePlayerRole.GetData(CPlayerRole::TYPE_TradeMoney))
		{
			if( m_nUnitPrice!=0 )
				nSell = (thePlayerRole.GetData(CPlayerRole::TYPE_TradeMoney)/(1+TRADE_TAX))/m_nUnitPrice;
			SetnSell( nSell );

			m_pID_EDIT_GoldNumber->SetText(nSell);
		}
	}
	else
	{
		if (m_nUnitPrice > 0)
		{
			nSell = price/m_nUnitPrice;
		}
		else
			nSell = 0;
		
		int nCost = ConsignmentDefine::GetConsignmentCost(nSell);

		if(nSell + nCost > thePlayerRole.GetData(CPlayerRole::TYPE_TradeJinDing))
		{
			DWORD dwValue = thePlayerRole.GetData(CPlayerRole::TYPE_TradeJinDing);
			nSell = dwValue - ConsignmentDefine::GetConsignmentCost(dwValue);
			SetnSell( nSell );

			m_pID_EDIT_GoldNumber->SetText(nSell);
		}
	}
}

void CUI_ID_FRAME_GoldTrade::EditDataChange( OUT ControlObject* pSender, OUT const char *szData )
{

	std::stringstream str;
	std::string text;

	s_CUI_ID_FRAME_GoldTrade.SetnSell( s_CUI_ID_FRAME_GoldTrade.GetGoldNumber() );

	//s_CUI_ID_FRAME_GoldTrade.CheckPrice();

	DWORD price = s_CUI_ID_FRAME_GoldTrade.GetPrice();

	//价格
	str.str("");
	//trade
	int gold = 0;
	int silver = 0;
	int copper = 0;
	thePlayerRole.GetGSCFromMoney(price, gold, silver, copper);

	{
		str << gold << "{#81} ";
	}
	if (silver > 0)
	{
		str << silver << "{#82} ";
	}
	if (copper > 0)
	{
		str << copper << "{#83} ";
	}

	text = str.str();
	s_CUI_ID_FRAME_GoldTrade.SetTextMoney( text );

	//手续费////////////
	if(s_CUI_ID_FRAME_GoldTrade.IsBuy())
	{
		price *= TRADE_TAX;

		str.str("");
		//trade
		thePlayerRole.GetGSCFromMoney(price, gold, silver, copper);
		if(price>0)
		{
			if(gold==0&&silver!=0)
			{
				str << silver << "{#82} ";
			}
			else if(gold!=0)
			{
				str << gold << "{#81} ";
				if(copper>0||silver>0)
				{
					str << silver << "{#82} ";
				}
			}
			if(copper>0)
			{
				str << copper << "{#83} ";
			}
		}
		else
		{
			str << copper << "{#83} ";
		}

		text = str.str();
		s_CUI_ID_FRAME_GoldTrade.SetTextTax( text );
	}
	else
	{
		int tax = ConsignmentDefine::GetConsignmentCost(s_CUI_ID_FRAME_GoldTrade.GetnSell());//(int)(s_CUI_ID_FRAME_GoldTrade.GetnSell() * TRADE_TAX +0.5f);
		if(tax<1)
		{
			tax = 1;
		}
		str.str("");

		str<< tax << /*"{#1103}"*/"{#1104}";

		text = str.str();
		s_CUI_ID_FRAME_GoldTrade.SetTextTax( text );
	}

	text = str.str();
	s_CUI_ID_FRAME_GoldTrade.SetTextTax( text );
}

void CUI_ID_FRAME_GoldTrade::UpdateBuyList()
{
	if(!m_pID_FRAME_GoldTrade)
		return;

	m_pID_LIST_Buy->SetCurSelIndex(-1);
	m_pID_LIST_Buy->Clear();
	m_pID_LIST_BuyPrice->Clear();
	m_pID_LIST_BuyType->Clear();
	m_pID_LIST_BuyGold->Clear();
	m_pID_LIST_BuyUnitPrice->Clear();

	char buf[128] = {0};
	ControlList::S_List	stItem;

	for(int i=0;i<m_vecBuy.size();++i)
	{
		int gold = 0;
		int silver = 0;
		int copper = 0;
		thePlayerRole.GetGSCFromMoney(m_vecBuy[i].GetPrice() * m_vecBuy[i].GetCount(), gold, silver, copper);

		stItem.SetData("");
		m_pID_LIST_Buy->AddItem(&stItem,NULL, false);

		if (gold > 0)
		{
			if (silver > 0)
			{
				if (copper > 0)
				{
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}%d{#82}%d{#83}",gold,silver,copper);
				}
				else
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}%d{#82}",gold,silver);
			}
			else
			{
				if (copper > 0)
				{
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}%d{#83}",gold,copper);
				}
				else
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}",gold);
			}
		}
		else
		{
			if (silver > 0)
			{
				if (copper > 0)
				{
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#82}%d{#83}",silver,copper);
				}
				else
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#82}",silver);
			}
			else
			{
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#83}",copper);
			}
		}
		

		stItem.SetData( buf );
		m_pID_LIST_BuyPrice->AddItem(&stItem,NULL, false);

		MeSprintf_s(buf, sizeof(buf)/sizeof(char)-1,"%s" ,theXmlString.GetString(eText_GoldTrade_Buy));
		stItem.SetData( buf );
		m_pID_LIST_BuyType->AddItem(&stItem,NULL, false);


		MeSprintf_s(buf, sizeof(buf)/sizeof(char)-1, /*"%d{#1103}"*/"%d{#1104}",m_vecBuy[i].GetCount());
		stItem.SetData( buf );
		m_pID_LIST_BuyGold->AddItem(&stItem,NULL, false);

		thePlayerRole.GetGSCFromMoney(m_vecBuy[i].GetPrice(), gold, silver, copper);

		if (gold > 0)
		{
			if (silver > 0)
			{
				if (copper > 0)
				{
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}%d{#82}%d{#83}",gold,silver,copper);
				}
				else
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}%d{#82}",gold,silver);
			}
			else
			{
				if (copper > 0)
				{
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}%d{#83}",gold,copper);
				}
				else
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}",gold);
			}
		}
		else
		{
			if (silver > 0)
			{
				if (copper > 0)
				{
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#82}%d{#83}",silver,copper);
				}
				else
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#82}",silver);
			}
			else
			{
				MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#83}",copper);
			}
		}

		stItem.SetData( buf );
		m_pID_LIST_BuyUnitPrice->AddItem(&stItem,NULL, false);
	}
}

void CUI_ID_FRAME_GoldTrade::UpdateSellList()
{
	if(!m_pID_FRAME_GoldTrade)
		return;

	m_pID_LIST_Sell->SetCurSelIndex(-1);
	m_pID_LIST_Sell->Clear();
	m_pID_LIST_SellPrice->Clear();
	m_pID_LIST_SellType->Clear();
	m_pID_LIST_SellGold->Clear();
	m_pID_LIST_SellUnitPrice->Clear();

	char buf[128] = {0};
	ControlList::S_List	stItem;

	for(int i=0;i<m_vecSell.size();++i)
	{
		int gold = 0;
		int silver = 0;
		int copper = 0;
		thePlayerRole.GetGSCFromMoney(m_vecSell[i].GetPrice() * m_vecSell[i].GetCount(), gold, silver, copper);

		stItem.SetData("");
		m_pID_LIST_Sell->AddItem(&stItem,NULL, false);


		if (gold > 0)
		{
			if (silver > 0)
			{
				if (copper > 0)
				{
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}%d{#82}%d{#83}",gold,silver,copper);
				}
				else
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}%d{#82}",gold,silver);
			}
			else
			{
				if (copper > 0)
				{
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}%d{#83}",gold,copper);
				}
				else
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}",gold);
			}
		}
		else
		{
			if (silver > 0)
			{
				if (copper > 0)
				{
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#82}%d{#83}",silver,copper);
				}
				else
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#82}",silver);
			}
			else
			{
				MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#83}",copper);
			}
		}

		stItem.SetData( buf );
		m_pID_LIST_SellPrice->AddItem(&stItem,NULL, false);

		MeSprintf_s(buf, sizeof(buf)/sizeof(char)-1,"%s",theXmlString.GetString(eText_GoldTrade_Sell));
		stItem.SetData( buf );
		m_pID_LIST_SellType->AddItem(&stItem,NULL, false);

		MeSprintf_s(buf, sizeof(buf)/sizeof(char)-1, /*"%d{#1103}"*/"%d{#1104}",m_vecSell[i].GetCount());
		stItem.SetData( buf );
		m_pID_LIST_SellGold->AddItem(&stItem,NULL, false);


		thePlayerRole.GetGSCFromMoney(m_vecSell[i].GetPrice(), gold, silver, copper);

		if (gold > 0)
		{
			if (silver > 0)
			{
				if (copper > 0)
				{
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}%d{#82}%d{#83}",gold,silver,copper);
				}
				else
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}%d{#82}",gold,silver);
			}
			else
			{
				if (copper > 0)
				{
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}%d{#83}",gold,copper);
				}
				else
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}",gold);
			}
		}
		else
		{
			if (silver > 0)
			{
				if (copper > 0)
				{
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#82}%d{#83}",silver,copper);
				}
				else
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#82}",silver);
			}
			else
			{
				MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#83}",copper);
			}
		}
		stItem.SetData( buf );
		m_pID_LIST_SellUnitPrice->AddItem(&stItem,NULL, false);
	}
}

void CUI_ID_FRAME_GoldTrade::RefreshList()
{
	UpdateBuyList();
	UpdateSellList();
}

void CUI_ID_FRAME_GoldTrade::AddReturnExchangeMoney( ConsignmentBase &pReturnExchangeMoney )
{
	if(pReturnExchangeMoney.GetType() == ConsignmentDefine::Consignment_SellRMB)
		m_vecSell.push_back( pReturnExchangeMoney );
	else if(pReturnExchangeMoney.GetType() == ConsignmentDefine::Consignment_BuyRMB)
		m_vecBuy.push_back( pReturnExchangeMoney );
}

void CUI_ID_FRAME_GoldTrade::DelExchangeMoney(__int64 n64ConsignmentID,unsigned char uchType)
{
	if(uchType == ConsignmentDefine::Consignment_SellRMB)
	{
		vector<ConsignmentBase>::iterator it = m_vecSell.begin();
		for (;it != m_vecSell.end();++it)
		{
			if(it->GetID() == n64ConsignmentID)
			{
				m_vecSell.erase(it);
				UpdateSellList();
				return;
			}
		}
	}
	else if(uchType == ConsignmentDefine::Consignment_BuyRMB)
	{
		vector<ConsignmentBase>::iterator it = m_vecBuy.begin();
		for (;it != m_vecBuy.end();++it)
		{
			if(it->GetID() == n64ConsignmentID)
			{
				m_vecBuy.erase(it);
				UpdateBuyList();
				return;
			}
		}
	}
}

void CUI_ID_FRAME_GoldTrade::Clear()
{
	m_vecBuy.clear();
	m_vecSell.clear();
}

void CUI_ID_FRAME_GoldTrade::BuyClear()
{
	m_vecBuy.clear();
}

void CUI_ID_FRAME_GoldTrade::SellClear()
{
	m_vecSell.clear();
}

bool CUI_ID_FRAME_GoldTrade::IsBuy()
{
	if(m_pID_CHECKBOX_BuyEntrust)
		return m_pID_CHECKBOX_BuyEntrust->IsChecked();

	return false;
}

void CUI_ID_FRAME_GoldTrade::SetBuyUnCheck()
{
	m_pID_CHECKBOX_BuyListAll->SetCheck(false);
	m_pID_CHECKBOX_BuyListMe->SetCheck(false);
}

void CUI_ID_FRAME_GoldTrade::SetSellUnCheck()
{
	m_pID_CHECKBOX_SellListAll->SetCheck(false);
	m_pID_CHECKBOX_SellListMe->SetCheck(false);
}

void CUI_ID_FRAME_GoldTrade::EditUnitPriceGold( OUT ControlObject* pSender, OUT const char *szData )
{
	s_CUI_ID_FRAME_GoldTrade.SetUnitPrice(s_CUI_ID_FRAME_GoldTrade.GetUnitPrice());
}
void CUI_ID_FRAME_GoldTrade::EditUnitPriceSilver( OUT ControlObject* pSender, OUT const char *szData )
{
	s_CUI_ID_FRAME_GoldTrade.SetUnitPrice(s_CUI_ID_FRAME_GoldTrade.GetUnitPrice());
}
void CUI_ID_FRAME_GoldTrade::EditUnitPriceCopper( OUT ControlObject* pSender, OUT const char *szData )
{
	s_CUI_ID_FRAME_GoldTrade.SetUnitPrice(s_CUI_ID_FRAME_GoldTrade.GetUnitPrice());
}

void CUI_ID_FRAME_GoldTrade::ClearSellSort()
{
	*m_pID_TEXT_ArrowSellUnitPrice = "";
	*m_pID_TEXT_ArrowSellGold = "";
	*m_pID_TEXT_ArrowSellPrice = "";
}

void CUI_ID_FRAME_GoldTrade::ClearBuySort()
{
	*m_pID_TEXT_ArrowBuyUnitPrice = "";
	*m_pID_TEXT_ArrowBuyGold = "";
	*m_pID_TEXT_ArrowBuyPrice = "";
}

void CUI_ID_FRAME_GoldTrade::SendSortMsg(int nIndex,bool bBuy/* = false*/)
{
#ifdef _DEBUG
	char szWord[256] ={0};
	MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"%d\n",m_dwCoolDownButton);
	::OutputDebugString(szWord);
#endif

	if(IsCoolDowning())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_OperateFailedInCD) );
		return;
	}

	m_dwCoolDownButton = ::HQ_TimeGetTime();

	if(nIndex >= 5)
		return;


	//默认值，为收购金锭，正常排序
	unsigned char ucConsignType = ConsignmentDefine::Consignment_SellRMB;
	unsigned char ucType = ConsignmentDefine::Sort_LessPrice;
	int           nCount = 0;

	if(bBuy)
		ucConsignType = ConsignmentDefine::Consignment_BuyRMB;

	switch(nIndex)
	{
	case  0:  //单价由低至高或单价由高至低
		{
			if(bBuy)
				ucType = ConsignmentDefine::Sort_GreaterPrice;
		}
		break;
	case  1:  //指定给我的
		ucType = ConsignmentDefine::Sort_ForMe;
		break;
	case  2:  //金锭由少至多
		ucType = ConsignmentDefine::Sort_LessCount;
		break;
	case  3:  //金锭由多至少
		ucType = ConsignmentDefine::Sort_GreaterCount;
		break;
	case  4: //指定金锭数量
		ucType = ConsignmentDefine::Sort_Count;
		break;
	default:
	    assert(0&&"数组越界");
		break;
	}

	//如果是按数量排序
	if(nIndex == SortCountIndex/*ConsignmentDefine::Sort_Count*/)
	{
		std::string str;
		str.clear();
		
		if(!bBuy)
			str = m_pID_EDIT_Num->GetText();
		else
			str = m_pID_EDIT_Num2->GetText();

		if(sscanf_s(str.c_str(),"%d",&nCount) != 1)
			return;
	}

	MsgQueryConsignmentList msg;
	msg.uchConsignmentType =  ucConsignType;
	msg.uchQueryType = ucType;
	msg.nCount = nCount;

	GettheNetworkInput().SendMsg( &msg );
}


bool CUI_ID_FRAME_GoldTrade::IsCoolDowning()
{
	return (::HQ_TimeGetTime() - m_dwCoolDownButton) <= 2000;
}

void CUI_ID_FRAME_GoldTrade::InitComboxString()
{
	std::string strBuy   = theXmlString.GetString(eText_RegisterBuyString);
	std::string strSell  = theXmlString.GetString(eText_RegisterSellString);

	std::string::size_type s = 0;
	std::string::size_type pos = 0;
	bool bFirst = true;
	std::string strValue;

	ControlList::S_List stItem;
	while ((pos = strBuy.find(',', s)) != std::string::npos)
	{
		strValue = strBuy.substr(s,pos - s);
		if(bFirst)
		{
		   m_pID_COMBOBOX_Filter->GetEditInput().SetText(strValue);
		   bFirst = false;
		}

		stItem.SetData(strValue.c_str());
		m_pID_COMBOBOX_Filter->GetListBox().AddItem(&stItem,NULL,false);

		s = pos + 1;
	}

	strValue = strBuy.substr(s);
	stItem.SetData(strValue.c_str());
	m_pID_COMBOBOX_Filter->GetListBox().AddItem(&stItem,NULL,false);

	s = 0;
	pos = 0;
	bFirst = true;
	while ((pos = strSell.find(',', s)) != std::string::npos)
	{
		std::string strValue = strSell.substr(s,pos - s);
		if(bFirst)
		{
			m_pID_COMBOBOX_Filter2->GetEditInput().SetText(strValue);
			bFirst = false;
		}

		stItem.SetData(strValue.c_str());
		m_pID_COMBOBOX_Filter2->GetListBox().AddItem(&stItem,NULL,false);

		s = pos + 1;
	}

	strValue = strSell.substr(s);
	stItem.SetData(strValue.c_str());
	m_pID_COMBOBOX_Filter2->GetListBox().AddItem(&stItem,NULL,false);
}


bool CUI_ID_FRAME_GoldTrade::IsProtectedTime()
{
	DWORD dwEndTime = CWealthProtect::Instance().GetProtectEndingTime();
	if( dwEndTime > HQ_TimeGetTime() )
	{
		// 安全保护时间内无法修改安全保护时间
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_OperateFailInProtectTime) );
		return false;
	}

	return true;
}

bool CUI_ID_FRAME_GoldTrade::GolgTradeFrame_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;
	if( !s_CUI_ID_FRAME_GoldTrade.IsVisable() )
		return false;

	if (!(s_CUI_ID_FRAME_SuperPasswordRegister.IsVisable() || s_CUI_ID_FRAME_SuperPasswordReset.IsVisable()))
	{
		return false;
	}

	switch( msg ) 
	{
	case WM_KEYUP:
		{
			if( wParam == VK_TAB )	//cancle
			{
				if( s_CUI_ID_FRAME_SuperPasswordRegister.IsVisable() && s_CUI_ID_FRAME_SuperPasswordRegister.GetEDIT_AddName() && s_CUI_ID_FRAME_SuperPasswordRegister.GetEDIT_AddName2())
				{
					if (theUiManager.GetFocus() == s_CUI_ID_FRAME_SuperPasswordRegister.GetEDIT_AddName())
					{
						theUiManager.SetFocus(s_CUI_ID_FRAME_SuperPasswordRegister.GetEDIT_AddName2());
					}else
					{
						if (theUiManager.GetFocus() == s_CUI_ID_FRAME_SuperPasswordRegister.GetEDIT_AddName2())
						{
							theUiManager.SetFocus(s_CUI_ID_FRAME_SuperPasswordRegister.GetEDIT_AddName());
						}
					}



				}else if (s_CUI_ID_FRAME_SuperPasswordReset.IsVisable() && s_CUI_ID_FRAME_SuperPasswordReset.AddNameArray[0] && s_CUI_ID_FRAME_SuperPasswordReset.AddNameArray[1]&&s_CUI_ID_FRAME_SuperPasswordReset.AddNameArray[2]) 
				{
					int NameId = 0;


					if (theUiManager.GetFocus() == s_CUI_ID_FRAME_SuperPasswordReset.AddNameArray[0])
						NameId = 1;

					if (theUiManager.GetFocus() == s_CUI_ID_FRAME_SuperPasswordReset.AddNameArray[1])
						NameId = 2;

					if (theUiManager.GetFocus() == s_CUI_ID_FRAME_SuperPasswordReset.AddNameArray[2])
						NameId = 0;

					theUiManager.SetFocus(s_CUI_ID_FRAME_SuperPasswordReset.AddNameArray[NameId]);


				}

				return true;
			}


		}
		break;
	}
	return false;
	unguard;
}