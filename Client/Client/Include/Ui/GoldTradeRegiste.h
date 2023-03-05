/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\chixin.ni\桌面\金锭UI\GoldTradeRegiste.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GlobalDef.h"
#include "ConsignmentMessage.h"
#include "ConsignmentDefine.h"

#ifndef ID_FRAME_GoldTradeRegiste
#define ID_FRAME_GoldTradeRegiste		"ID_FRAME_GoldTradeRegiste"
#endif  ID_FRAME_GoldTradeRegiste
#ifndef ID_PICTURE_Entrust
#define ID_PICTURE_Entrust		"ID_PICTURE_Entrust"
#endif  ID_PICTURE_Entrust
#ifndef ID_PICTURE_Wall
#define ID_PICTURE_Wall		"ID_PICTURE_Wall"
#endif  ID_PICTURE_Wall
#ifndef ID_LIST_Sell
#define ID_LIST_Sell		"ID_LIST_Sell"
#endif  ID_LIST_Sell
#ifndef ID_PICTURE_TitleMiddle
#define ID_PICTURE_TitleMiddle		"ID_PICTURE_TitleMiddle"
#endif  ID_PICTURE_TitleMiddle
#ifndef ID_PICTURE_Title
#define ID_PICTURE_Title		"ID_PICTURE_Title"
#endif  ID_PICTURE_Title
#ifndef ID_TEXT_Price
#define ID_TEXT_Price		"ID_TEXT_Price"
#endif  ID_TEXT_Price
#ifndef ID_TEXT_Gold
#define ID_TEXT_Gold		"ID_TEXT_Gold"
#endif  ID_TEXT_Gold
#ifndef ID_PICTURE_TitleLeft
#define ID_PICTURE_TitleLeft		"ID_PICTURE_TitleLeft"
#endif  ID_PICTURE_TitleLeft
#ifndef ID_PICTURE_TitleRight
#define ID_PICTURE_TitleRight		"ID_PICTURE_TitleRight"
#endif  ID_PICTURE_TitleRight
#ifndef ID_PICTURE_TitleL
#define ID_PICTURE_TitleL		"ID_PICTURE_TitleL"
#endif  ID_PICTURE_TitleL
#ifndef ID_PICTURE_TltleR
#define ID_PICTURE_TltleR		"ID_PICTURE_TltleR"
#endif  ID_PICTURE_TltleR
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_LIST_Type
#define ID_LIST_Type		"ID_LIST_Type"
#endif  ID_LIST_Type
#ifndef ID_TEXT_Type
#define ID_TEXT_Type		"ID_TEXT_Type"
#endif  ID_TEXT_Type
#ifndef ID_LIST_Gold
#define ID_LIST_Gold		"ID_LIST_Gold"
#endif  ID_LIST_Gold
#ifndef ID_TEXT_UnitPrice
#define ID_TEXT_UnitPrice		"ID_TEXT_UnitPrice"
#endif  ID_TEXT_UnitPrice
#ifndef ID_LIST_UnitPrice
#define ID_LIST_UnitPrice		"ID_LIST_UnitPrice"
#endif  ID_LIST_UnitPrice
#ifndef ID_BUTTON_Close
#define ID_BUTTON_Close		"ID_BUTTON_Close"
#endif  ID_BUTTON_Close
#ifndef ID_BUTTON_Cancle
#define ID_BUTTON_Cancle		"ID_BUTTON_Cancle"
#endif  ID_BUTTON_Cancle
#ifndef ID_TEXT_FinishTime
#define ID_TEXT_FinishTime		"ID_TEXT_FinishTime"
#endif  ID_TEXT_FinishTime
#ifndef ID_LIST_FinishTime
#define ID_LIST_FinishTime		"ID_LIST_FinishTime"
#endif  ID_LIST_FinishTime
#ifndef ID_LIST_Price
#define ID_LIST_Price		"ID_LIST_Price"
#endif  ID_LIST_Price

#include "UIBase.h"

class CUI_ID_FRAME_GoldTradeRegiste : public CUIBase
{
	// Member
private:
	void ResetMembers();
	 ControlFrame*	m_pID_FRAME_GoldTradeRegiste;
	 ControlPicture*	m_pID_PICTURE_Entrust;
	 ControlPicture*	m_pID_PICTURE_Wall;
	 ControlList*	m_pID_LIST_Sell;
	 ControlPicture*	m_pID_PICTURE_TitleMiddle;
	 ControlPicture*	m_pID_PICTURE_Title;
	 ControlText*	m_pID_TEXT_Price;
	 ControlText*	m_pID_TEXT_Gold;
	 ControlPicture*	m_pID_PICTURE_TitleLeft;
	 ControlPicture*	m_pID_PICTURE_TitleRight;
	 ControlPicture*	m_pID_PICTURE_TitleL;
	 ControlPicture*	m_pID_PICTURE_TltleR;
	 ControlButton*	m_pID_BUTTON_help;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlList*	m_pID_LIST_Type;
	 ControlText*	m_pID_TEXT_Type;
	 ControlList*	m_pID_LIST_Gold;
	 ControlText*	m_pID_TEXT_UnitPrice;
	 ControlList*	m_pID_LIST_UnitPrice;
	 ControlButton*	m_pID_BUTTON_Close;
	 ControlButton*	m_pID_BUTTON_Cancle;
	 ControlText*	m_pID_TEXT_FinishTime;
	 ControlList*	m_pID_LIST_FinishTime;
	 ControlList*	m_pID_LIST_Price;

public:	
	CUI_ID_FRAME_GoldTradeRegiste();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_SellOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	void ID_LIST_TypeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_GoldOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_UnitPriceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancleOnButtonClick( ControlObject* pSender );
	void ID_LIST_FinishTimeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_PriceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void Refresh();
	void Clear();
	void AddMoneyAuctionHistroy(ConsignmentHistroy &data);
	bool UpdateConsignState(__int64 n64ConsignmentID,unsigned char ucStatus);
private:

	vector<ConsignmentHistroy> m_vecHistory;
};
extern CUI_ID_FRAME_GoldTradeRegiste s_CUI_ID_FRAME_GoldTradeRegiste;
