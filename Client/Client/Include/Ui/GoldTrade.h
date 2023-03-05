/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\chixin.ni\桌面\金锭UI\GoldTrade.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GlobalDef.h"
#include "me3d/Vector.h"
#include "ConsignmentMessage.h"
#include "ConsignmentDefine.h"

#ifndef ID_FRAME_GoldTrade
#define ID_FRAME_GoldTrade		"ID_FRAME_GoldTrade"
#endif  ID_FRAME_GoldTrade
#ifndef ID_PICTURE_EntrustWall
#define ID_PICTURE_EntrustWall		"ID_PICTURE_EntrustWall"
#endif  ID_PICTURE_EntrustWall
#ifndef ID_PICTURE_Sell
#define ID_PICTURE_Sell		"ID_PICTURE_Sell"
#endif  ID_PICTURE_Sell
#ifndef ID_PICTURE_26447
#define ID_PICTURE_26447		"ID_PICTURE_26447"
#endif  ID_PICTURE_26447
#ifndef ID_LIST_Sell
#define ID_LIST_Sell		"ID_LIST_Sell"
#endif  ID_LIST_Sell
#ifndef ID_PICTURE_TitleMiddle
#define ID_PICTURE_TitleMiddle		"ID_PICTURE_TitleMiddle"
#endif  ID_PICTURE_TitleMiddle
#ifndef ID_PICTURE_Title
#define ID_PICTURE_Title		"ID_PICTURE_Title"
#endif  ID_PICTURE_Title
#ifndef ID_PICTURE_TitleLeft
#define ID_PICTURE_TitleLeft		"ID_PICTURE_TitleLeft"
#endif  ID_PICTURE_TitleLeft
#ifndef ID_PICTURE_TitleRight
#define ID_PICTURE_TitleRight		"ID_PICTURE_TitleRight"
#endif  ID_PICTURE_TitleRight
#ifndef ID_PICTURE_TitleL
#define ID_PICTURE_TitleL		"ID_PICTURE_TitleL"
#endif  ID_PICTURE_TitleL
#ifndef ID_PICTURE_TradeEntrust
#define ID_PICTURE_TradeEntrust		"ID_PICTURE_TradeEntrust"
#endif  ID_PICTURE_TradeEntrust
#ifndef ID_PICTURE_TltleR
#define ID_PICTURE_TltleR		"ID_PICTURE_TltleR"
#endif  ID_PICTURE_TltleR
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_LIST_SellPrice
#define ID_LIST_SellPrice		"ID_LIST_SellPrice"
#endif  ID_LIST_SellPrice
#ifndef ID_LIST_BuyPrice
#define ID_LIST_BuyPrice		"ID_LIST_BuyPrice"
#endif  ID_LIST_BuyPrice
#ifndef ID_LIST_SellType
#define ID_LIST_SellType		"ID_LIST_SellType"
#endif  ID_LIST_SellType
#ifndef ID_LIST_SellGold
#define ID_LIST_SellGold		"ID_LIST_SellGold"
#endif  ID_LIST_SellGold
#ifndef ID_TEXT_TradeList
#define ID_TEXT_TradeList		"ID_TEXT_TradeList"
#endif  ID_TEXT_TradeList
#ifndef ID_LIST_SellUnitPrice
#define ID_LIST_SellUnitPrice		"ID_LIST_SellUnitPrice"
#endif  ID_LIST_SellUnitPrice
#ifndef ID_BUTTON_Buy
#define ID_BUTTON_Buy		"ID_BUTTON_Buy"
#endif  ID_BUTTON_Buy
#ifndef ID_PICTURE_Buy
#define ID_PICTURE_Buy		"ID_PICTURE_Buy"
#endif  ID_PICTURE_Buy
#ifndef ID_PICTURE_264473
#define ID_PICTURE_264473		"ID_PICTURE_264473"
#endif  ID_PICTURE_264473
#ifndef ID_LIST_Buy
#define ID_LIST_Buy		"ID_LIST_Buy"
#endif  ID_LIST_Buy
#ifndef ID_BUTTON_Sell
#define ID_BUTTON_Sell		"ID_BUTTON_Sell"
#endif  ID_BUTTON_Sell
#ifndef ID_LIST_BuyType
#define ID_LIST_BuyType		"ID_LIST_BuyType"
#endif  ID_LIST_BuyType
#ifndef ID_LIST_BuyGold
#define ID_LIST_BuyGold		"ID_LIST_BuyGold"
#endif  ID_LIST_BuyGold
#ifndef ID_LIST_BuyUnitPrice
#define ID_LIST_BuyUnitPrice		"ID_LIST_BuyUnitPrice"
#endif  ID_LIST_BuyUnitPrice
#ifndef ID_TEXT_UnitPrice1
#define ID_TEXT_UnitPrice1		"ID_TEXT_UnitPrice1"
#endif  ID_TEXT_UnitPrice1
#ifndef ID_TEXT_UnitPrice
#define ID_TEXT_UnitPrice		"ID_TEXT_UnitPrice"
#endif  ID_TEXT_UnitPrice
#ifndef ID_TEXT_BuyGoldNumber
#define ID_TEXT_BuyGoldNumber		"ID_TEXT_BuyGoldNumber"
#endif  ID_TEXT_BuyGoldNumber
#ifndef ID_TEXT_SellGoldNumber
#define ID_TEXT_SellGoldNumber		"ID_TEXT_SellGoldNumber"
#endif  ID_TEXT_SellGoldNumber
#ifndef ID_EDIT_GoldNumber
#define ID_EDIT_GoldNumber		"ID_EDIT_GoldNumber"
#endif  ID_EDIT_GoldNumber
#ifndef ID_TEXT_CostMoney
#define ID_TEXT_CostMoney		"ID_TEXT_CostMoney"
#endif  ID_TEXT_CostMoney
#ifndef ID_TEXT_GetMoney
#define ID_TEXT_GetMoney		"ID_TEXT_GetMoney"
#endif  ID_TEXT_GetMoney
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_TEXT_Tax1
#define ID_TEXT_Tax1		"ID_TEXT_Tax1"
#endif  ID_TEXT_Tax1
#ifndef ID_TEXT_Tax
#define ID_TEXT_Tax		"ID_TEXT_Tax"
#endif  ID_TEXT_Tax
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_SetPrice
#define ID_BUTTON_SetPrice		"ID_BUTTON_SetPrice"
#endif  ID_BUTTON_SetPrice
#ifndef ID_TEXT_Trade
#define ID_TEXT_Trade		"ID_TEXT_Trade"
#endif  ID_TEXT_Trade
#ifndef ID_PICTURE_Trade
#define ID_PICTURE_Trade		"ID_PICTURE_Trade"
#endif  ID_PICTURE_Trade
#ifndef ID_TEXT_TradeGold1
#define ID_TEXT_TradeGold1		"ID_TEXT_TradeGold1"
#endif  ID_TEXT_TradeGold1
#ifndef ID_TEXT_TradeGold
#define ID_TEXT_TradeGold		"ID_TEXT_TradeGold"
#endif  ID_TEXT_TradeGold
#ifndef ID_TEXT_TradeMoney1
#define ID_TEXT_TradeMoney1		"ID_TEXT_TradeMoney1"
#endif  ID_TEXT_TradeMoney1
#ifndef ID_TEXT_TradeMoney
#define ID_TEXT_TradeMoney		"ID_TEXT_TradeMoney"
#endif  ID_TEXT_TradeMoney
#ifndef ID_BUTTON_Deposit
#define ID_BUTTON_Deposit		"ID_BUTTON_Deposit"
#endif  ID_BUTTON_Deposit
#ifndef ID_BUTTON_Receive
#define ID_BUTTON_Receive		"ID_BUTTON_Receive"
#endif  ID_BUTTON_Receive
#ifndef ID_TEXT_Self
#define ID_TEXT_Self		"ID_TEXT_Self"
#endif  ID_TEXT_Self
#ifndef ID_PICTURE_Self
#define ID_PICTURE_Self		"ID_PICTURE_Self"
#endif  ID_PICTURE_Self
#ifndef ID_TEXT_SelfGold1
#define ID_TEXT_SelfGold1		"ID_TEXT_SelfGold1"
#endif  ID_TEXT_SelfGold1
#ifndef ID_TEXT_SelfGold
#define ID_TEXT_SelfGold		"ID_TEXT_SelfGold"
#endif  ID_TEXT_SelfGold
#ifndef ID_TEXT_SelfMoney1
#define ID_TEXT_SelfMoney1		"ID_TEXT_SelfMoney1"
#endif  ID_TEXT_SelfMoney1
#ifndef ID_TEXT_SelfMoney
#define ID_TEXT_SelfMoney		"ID_TEXT_SelfMoney"
#endif  ID_TEXT_SelfMoney
#ifndef ID_BUTTON_Refresh
#define ID_BUTTON_Refresh		"ID_BUTTON_Refresh"
#endif  ID_BUTTON_Refresh
#ifndef ID_BUTTON_SetPassword
#define ID_BUTTON_SetPassword		"ID_BUTTON_SetPassword"
#endif  ID_BUTTON_SetPassword
#ifndef ID_BUTTON_Registe
#define ID_BUTTON_Registe		"ID_BUTTON_Registe"
#endif  ID_BUTTON_Registe
#ifndef ID_BUTTON_SellPrice
#define ID_BUTTON_SellPrice		"ID_BUTTON_SellPrice"
#endif  ID_BUTTON_SellPrice
#ifndef ID_BUTTON_SellGold
#define ID_BUTTON_SellGold		"ID_BUTTON_SellGold"
#endif  ID_BUTTON_SellGold
#ifndef ID_BUTTON_SellUnitPrice
#define ID_BUTTON_SellUnitPrice		"ID_BUTTON_SellUnitPrice"
#endif  ID_BUTTON_SellUnitPrice
#ifndef ID_BUTTON_BuyPrice
#define ID_BUTTON_BuyPrice		"ID_BUTTON_BuyPrice"
#endif  ID_BUTTON_BuyPrice
#ifndef ID_BUTTON_BuyGold
#define ID_BUTTON_BuyGold		"ID_BUTTON_BuyGold"
#endif  ID_BUTTON_BuyGold
#ifndef ID_BUTTON_BuyUnitPrice
#define ID_BUTTON_BuyUnitPrice		"ID_BUTTON_BuyUnitPrice"
#endif  ID_BUTTON_BuyUnitPrice
#ifndef ID_BUTTON_SellType
#define ID_BUTTON_SellType		"ID_BUTTON_SellType"
#endif  ID_BUTTON_SellType
#ifndef ID_BUTTON_BuyType
#define ID_BUTTON_BuyType		"ID_BUTTON_BuyType"
#endif  ID_BUTTON_BuyType
#ifndef ID_CHECKBOX_BuyEntrust
#define ID_CHECKBOX_BuyEntrust		"ID_CHECKBOX_BuyEntrust"
#endif  ID_CHECKBOX_BuyEntrust
#ifndef ID_CHECKBOX_SellTrust
#define ID_CHECKBOX_SellTrust		"ID_CHECKBOX_SellTrust"
#endif  ID_CHECKBOX_SellTrust
#ifndef ID_BUTTON_Max
#define ID_BUTTON_Max		"ID_BUTTON_Max"
#endif  ID_BUTTON_Max
#ifndef ID_BUTTON_BuyFilter
#define ID_BUTTON_BuyFilter		"ID_BUTTON_BuyFilter"
#endif  ID_BUTTON_BuyFilter
#ifndef ID_BUTTON_SellFilter
#define ID_BUTTON_SellFilter		"ID_BUTTON_SellFilter"
#endif  ID_BUTTON_SellFilter
#ifndef ID_TEXT_Appoint
#define ID_TEXT_Appoint		"ID_TEXT_Appoint"
#endif  ID_TEXT_Appoint
#ifndef ID_COMBOBOX_SendTarget
#define ID_COMBOBOX_SendTarget		"ID_COMBOBOX_SendTarget"
#endif  ID_COMBOBOX_SendTarget
#ifndef ID_CHECKBOX_BuyListAll
#define ID_CHECKBOX_BuyListAll		"ID_CHECKBOX_BuyListAll"
#endif  ID_CHECKBOX_BuyListAll
#ifndef ID_CHECKBOX_BuyListMe
#define ID_CHECKBOX_BuyListMe		"ID_CHECKBOX_BuyListMe"
#endif  ID_CHECKBOX_BuyListMe
#ifndef ID_TEXT_ID_BuyListAll
#define ID_TEXT_ID_BuyListAll		"ID_TEXT_ID_BuyListAll"
#endif  ID_TEXT_ID_BuyListAll
#ifndef ID_TEXT_ID_BuyListMe
#define ID_TEXT_ID_BuyListMe		"ID_TEXT_ID_BuyListMe"
#endif  ID_TEXT_ID_BuyListMe
#ifndef ID_CHECKBOX_SellListAll
#define ID_CHECKBOX_SellListAll		"ID_CHECKBOX_SellListAll"
#endif  ID_CHECKBOX_SellListAll
#ifndef ID_CHECKBOX_SellListMe
#define ID_CHECKBOX_SellListMe		"ID_CHECKBOX_SellListMe"
#endif  ID_CHECKBOX_SellListMe
#ifndef ID_TEXT_ID_SellListAll
#define ID_TEXT_ID_SellListAll		"ID_TEXT_ID_SellListAll"
#endif  ID_TEXT_ID_SellListAll
#ifndef ID_TEXT_ID_SellListMe
#define ID_TEXT_ID_SellListMe		"ID_TEXT_ID_SellListMe"
#endif  ID_TEXT_ID_SellListMe
#ifndef ID_PICTURE_22611
#define ID_PICTURE_22611		"ID_PICTURE_22611"
#endif  ID_PICTURE_22611
#ifndef ID_PICTURE_226112
#define ID_PICTURE_226112		"ID_PICTURE_226112"
#endif  ID_PICTURE_226112
#ifndef ID_PICTURE_2261122
#define ID_PICTURE_2261122		"ID_PICTURE_2261122"
#endif  ID_PICTURE_2261122
#ifndef ID_EDIT_Gold
#define ID_EDIT_Gold		"ID_EDIT_Gold"
#endif  ID_EDIT_Gold
#ifndef ID_PICTURE_26210
#define ID_PICTURE_26210		"ID_PICTURE_26210"
#endif  ID_PICTURE_26210
#ifndef ID_TEXT_ArrowSellUnitPrice
#define ID_TEXT_ArrowSellUnitPrice		"ID_TEXT_ArrowSellUnitPrice"
#endif  ID_TEXT_ArrowSellUnitPrice
#ifndef ID_TEXT_ArrowBuyUnitPrice
#define ID_TEXT_ArrowBuyUnitPrice		"ID_TEXT_ArrowBuyUnitPrice"
#endif  ID_TEXT_ArrowBuyUnitPrice
#ifndef ID_TEXT_ArrowSellGold
#define ID_TEXT_ArrowSellGold		"ID_TEXT_ArrowSellGold"
#endif  ID_TEXT_ArrowSellGold
#ifndef ID_TEXT_ArrowBuyGold
#define ID_TEXT_ArrowBuyGold		"ID_TEXT_ArrowBuyGold"
#endif  ID_TEXT_ArrowBuyGold
#ifndef ID_TEXT_ArrowSellPrice
#define ID_TEXT_ArrowSellPrice		"ID_TEXT_ArrowSellPrice"
#endif  ID_TEXT_ArrowSellPrice
#ifndef ID_TEXT_ArrowBuyPrice
#define ID_TEXT_ArrowBuyPrice		"ID_TEXT_ArrowBuyPrice"
#endif  ID_TEXT_ArrowBuyPrice
#ifndef ID_COMBOBOX_Filter
#define ID_COMBOBOX_Filter		"ID_COMBOBOX_Filter"
#endif  ID_COMBOBOX_Filter
#ifndef ID_COMBOBOX_Filter2
#define ID_COMBOBOX_Filter2		"ID_COMBOBOX_Filter2"
#endif  ID_COMBOBOX_Filter2
#ifndef ID_EDIT_Num
#define ID_EDIT_Num		"ID_EDIT_Num"
#endif  ID_EDIT_Num
#ifndef ID_EDIT_Num2
#define ID_EDIT_Num2		"ID_EDIT_Num2"
#endif  ID_EDIT_Num2
#ifndef ID_BUTTON_Search
#define ID_BUTTON_Search		"ID_BUTTON_Search"
#endif  ID_BUTTON_Search
#ifndef ID_BUTTON_Search2
#define ID_BUTTON_Search2		"ID_BUTTON_Search2"
#endif  ID_BUTTON_Search2
#ifndef ID_TEXT_TradeList2
#define ID_TEXT_TradeList2		"ID_TEXT_TradeList2"
#endif  ID_TEXT_TradeList2
#ifndef ID_EDIT_Silver
#define ID_EDIT_Silver		"ID_EDIT_Silver"
#endif  ID_EDIT_Silver
#ifndef ID_EDIT_Copper
#define ID_EDIT_Copper		"ID_EDIT_Copper"
#endif  ID_EDIT_Copper

#include "UIBase.h"

class CUI_ID_FRAME_GoldTrade : public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_GoldTrade();
private:
	void ResetMembers();
	 ControlFrame*	m_pID_FRAME_GoldTrade;
	 ControlPicture*	m_pID_PICTURE_EntrustWall;
	 ControlPicture*	m_pID_PICTURE_Sell;
	 ControlPicture*	m_pID_PICTURE_26447;
	 ControlList*	m_pID_LIST_Sell;
	 ControlPicture*	m_pID_PICTURE_TitleMiddle;
	 ControlPicture*	m_pID_PICTURE_Title;
	 ControlPicture*	m_pID_PICTURE_TitleLeft;
	 ControlPicture*	m_pID_PICTURE_TitleRight;
	 ControlPicture*	m_pID_PICTURE_TitleL;
	 ControlPicture*	m_pID_PICTURE_TradeEntrust;
	 ControlPicture*	m_pID_PICTURE_TltleR;
	 ControlButton*	m_pID_BUTTON_help;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlList*	m_pID_LIST_SellPrice;
	 ControlList*	m_pID_LIST_BuyPrice;
	 ControlList*	m_pID_LIST_SellType;
	 ControlList*	m_pID_LIST_SellGold;
	 ControlText*	m_pID_TEXT_TradeList;
	 ControlList*	m_pID_LIST_SellUnitPrice;
	 ControlButton*	m_pID_BUTTON_Buy;
	 ControlPicture*	m_pID_PICTURE_Buy;
	 ControlPicture*	m_pID_PICTURE_264473;
	 ControlList*	m_pID_LIST_Buy;
	 ControlButton*	m_pID_BUTTON_Sell;
	 ControlList*	m_pID_LIST_BuyType;
	 ControlList*	m_pID_LIST_BuyGold;
	 ControlList*	m_pID_LIST_BuyUnitPrice;
	 ControlText*	m_pID_TEXT_UnitPrice1;
	 ControlText*	m_pID_TEXT_UnitPrice;
	 ControlText*	m_pID_TEXT_BuyGoldNumber;
	 ControlText*	m_pID_TEXT_SellGoldNumber;
	 ControlEdit*	m_pID_EDIT_GoldNumber;
	 ControlText*	m_pID_TEXT_CostMoney;
	 ControlText*	m_pID_TEXT_GetMoney;
	 ControlText*	m_pID_TEXT_Money;
	 ControlText*	m_pID_TEXT_Tax1;
	 ControlText*	m_pID_TEXT_Tax;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_SetPrice;
	 ControlText*	m_pID_TEXT_Trade;
	 ControlPicture*	m_pID_PICTURE_Trade;
	 ControlText*	m_pID_TEXT_TradeGold1;
	 ControlText*	m_pID_TEXT_TradeGold;
	 ControlText*	m_pID_TEXT_TradeMoney1;
	 ControlText*	m_pID_TEXT_TradeMoney;
	 ControlButton*	m_pID_BUTTON_Deposit;
	 ControlButton*	m_pID_BUTTON_Receive;
	 ControlText*	m_pID_TEXT_Self;
	 ControlPicture*	m_pID_PICTURE_Self;
	 ControlText*	m_pID_TEXT_SelfGold1;
	 ControlText*	m_pID_TEXT_SelfGold;
	 ControlText*	m_pID_TEXT_SelfMoney1;
	 ControlText*	m_pID_TEXT_SelfMoney;
	 ControlButton*	m_pID_BUTTON_Refresh;
	 ControlButton*	m_pID_BUTTON_SetPassword;
	 ControlButton*	m_pID_BUTTON_Registe;
	 ControlButton*	m_pID_BUTTON_SellPrice;
	 ControlButton*	m_pID_BUTTON_SellGold;
	 ControlButton*	m_pID_BUTTON_SellUnitPrice;
	 ControlButton*	m_pID_BUTTON_BuyPrice;
	 ControlButton*	m_pID_BUTTON_BuyGold;
	 ControlButton*	m_pID_BUTTON_BuyUnitPrice;
	 ControlButton*	m_pID_BUTTON_SellType;
	 ControlButton*	m_pID_BUTTON_BuyType;
	 ControlCheckBox*	m_pID_CHECKBOX_BuyEntrust;
	 ControlCheckBox*	m_pID_CHECKBOX_SellTrust;
	 ControlButton*	m_pID_BUTTON_Max;
	 ControlButton*	m_pID_BUTTON_BuyFilter;
	 ControlButton*	m_pID_BUTTON_SellFilter;
	 ControlText*	m_pID_TEXT_Appoint;
	 ControlComboBox*	m_pID_COMBOBOX_SendTarget;
	 ControlCheckBox*	m_pID_CHECKBOX_BuyListAll;
	 ControlCheckBox*	m_pID_CHECKBOX_BuyListMe;
	 ControlText*	m_pID_TEXT_ID_BuyListAll;
	 ControlText*	m_pID_TEXT_ID_BuyListMe;
	 ControlCheckBox*	m_pID_CHECKBOX_SellListAll;
	 ControlCheckBox*	m_pID_CHECKBOX_SellListMe;
	 ControlText*	m_pID_TEXT_ID_SellListAll;
	 ControlText*	m_pID_TEXT_ID_SellListMe;
	 ControlPicture*	m_pID_PICTURE_22611;
	 ControlPicture*	m_pID_PICTURE_226112;
	 ControlPicture*	m_pID_PICTURE_2261122;
	 ControlEdit*	m_pID_EDIT_Gold;
	 ControlPicture*	m_pID_PICTURE_26210;
	 ControlText*	m_pID_TEXT_ArrowSellUnitPrice;
	 ControlText*	m_pID_TEXT_ArrowBuyUnitPrice;
	 ControlText*	m_pID_TEXT_ArrowSellGold;
	 ControlText*	m_pID_TEXT_ArrowBuyGold;
	 ControlText*	m_pID_TEXT_ArrowSellPrice;
	 ControlText*	m_pID_TEXT_ArrowBuyPrice;
	 ControlComboBox*	m_pID_COMBOBOX_Filter;
	 ControlComboBox*	m_pID_COMBOBOX_Filter2;
	 ControlEdit*	m_pID_EDIT_Num;
	 ControlEdit*	m_pID_EDIT_Num2;
	 ControlButton*	m_pID_BUTTON_Search;
	 ControlButton*	m_pID_BUTTON_Search2;
	 ControlText*	m_pID_TEXT_TradeList2;
	 ControlEdit*	m_pID_EDIT_Silver;
	 ControlEdit*	m_pID_EDIT_Copper;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	void ID_LIST_SellPriceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_BuyPriceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_SellTypeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_SellGoldOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_SellUnitPriceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_BuyOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SellOnButtonClick( ControlObject* pSender );
	void ID_LIST_BuyTypeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_BuyGoldOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_BuyUnitPriceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_EDIT_GoldNumberOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SetPriceOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DepositOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ReceiveOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RefreshOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SetPasswordOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RegisteOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SellPriceOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SellGoldOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SellUnitPriceOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_BuyPriceOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_BuyGoldOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_BuyUnitPriceOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SellTypeOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_BuyTypeOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_BuyEntrustOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_SellTrustOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_MaxOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_BuyFilterOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SellFilterOnButtonClick( ControlObject* pSender );
	void ID_COMBOBOX_SendTargetOnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_CHECKBOX_BuyListAllOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_BuyListMeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_SellListAllOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_SellListMeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_LIST_SellOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_BuyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_EDIT_GoldOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_COMBOBOX_FilterOnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_COMBOBOX_Filter2OnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_EDIT_NumOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_Num2OnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_SearchOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Search2OnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void Clear();

	void Refresh();
	void RefreshList();

	void SetUnitPrice( int price );

	static void EditDataChange( OUT ControlObject* pSender, OUT const char *szData );
	static void EditUnitPriceGold( OUT ControlObject* pSender, OUT const char *szData );
	static void EditUnitPriceSilver( OUT ControlObject* pSender, OUT const char *szData );
	static void EditUnitPriceCopper( OUT ControlObject* pSender, OUT const char *szData );

	int GetGoldNumber();
	int GetUnitPrice();
	void SetTextMoney(string str);
	void SetTextTax(string str);
	int GetnSell();
	void SetnSell(int i);
	int  GetPrice(){ return m_nSell*m_nUnitPrice; }

	bool IsBuy();
	void CheckPrice();

	void UpdateBuyList();
	void UpdateSellList();

	void AddReturnExchangeMoney( ConsignmentBase &pReturnExchangeMoney );
	void DelExchangeMoney(__int64 n64ConsignmentID,unsigned char uchType);

	int m_nUnitPrice;
	int m_nSell;
	int m_nBuyFilter;
	int m_nSellFilter;

	void SetVisiblePosition( const Vector& vPos ){ m_vVisiblePos = vPos; };

	Vector m_vVisiblePos;

	void BuyClear();
	void SellClear();

	void SetBuyFilter(int i){ m_nBuyFilter = i;}
	void SetSellFilter(int i){ m_nSellFilter = i;}

	void SetBuyUnCheck();
	void SetSellUnCheck();

	void ClearSellSort();
	void ClearBuySort();

	void SendSortMsg(int nIndex,bool bBuy = false);

	bool IsCoolDowning();

	void InitComboxString();

	bool IsProtectedTime();

	static	bool GolgTradeFrame_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

private:
	vector<ConsignmentBase> m_vecBuy;
	vector<ConsignmentBase> m_vecSell;

	bool m_SellPriceSort;
	bool m_SellUnitPriceSort;
	bool m_SellGoldSort;
	bool m_BuyPriceSort;
	bool m_BuyUnitPriceSort;
	bool m_BuyGoldSort;

	DWORD m_dwCoolDownButton;  //记录上次排序按钮的时间，因为服务器有时间显示
};	

extern CUI_ID_FRAME_GoldTrade s_CUI_ID_FRAME_GoldTrade;
