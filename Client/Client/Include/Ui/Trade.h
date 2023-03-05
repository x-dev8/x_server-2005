/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\Trade.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_Trade
#define ID_FRAME_Trade		"ID_FRAME_Trade"
#endif  ID_FRAME_Trade
#ifndef ID_PICTURE_ShopItemWall
#define ID_PICTURE_ShopItemWall		"ID_PICTURE_ShopItemWall"
#endif  ID_PICTURE_ShopItemWall
#ifndef ID_BUTTON_Shopping
#define ID_BUTTON_Shopping		"ID_BUTTON_Shopping"
#endif  ID_BUTTON_Shopping
#ifndef ID_LISTIMG_Trade1
#define ID_LISTIMG_Trade1		"ID_LISTIMG_Trade1"
#endif  ID_LISTIMG_Trade1
#ifndef ID_TEXT_TradePrice1
#define ID_TEXT_TradePrice1		"ID_TEXT_TradePrice1"
#endif  ID_TEXT_TradePrice1
#ifndef ID_LISTIMG_Trade2
#define ID_LISTIMG_Trade2		"ID_LISTIMG_Trade2"
#endif  ID_LISTIMG_Trade2
#ifndef ID_TEXT_TradePrice2
#define ID_TEXT_TradePrice2		"ID_TEXT_TradePrice2"
#endif  ID_TEXT_TradePrice2
#ifndef ID_LISTIMG_Trade3
#define ID_LISTIMG_Trade3		"ID_LISTIMG_Trade3"
#endif  ID_LISTIMG_Trade3
#ifndef ID_TEXT_TradePrice3
#define ID_TEXT_TradePrice3		"ID_TEXT_TradePrice3"
#endif  ID_TEXT_TradePrice3
#ifndef ID_LISTIMG_Trade4
#define ID_LISTIMG_Trade4		"ID_LISTIMG_Trade4"
#endif  ID_LISTIMG_Trade4
#ifndef ID_TEXT_TradePrice4
#define ID_TEXT_TradePrice4		"ID_TEXT_TradePrice4"
#endif  ID_TEXT_TradePrice4
#ifndef ID_LISTIMG_Trade5
#define ID_LISTIMG_Trade5		"ID_LISTIMG_Trade5"
#endif  ID_LISTIMG_Trade5
#ifndef ID_TEXT_TradePrice5
#define ID_TEXT_TradePrice5		"ID_TEXT_TradePrice5"
#endif  ID_TEXT_TradePrice5
#ifndef ID_LISTIMG_Trade6
#define ID_LISTIMG_Trade6		"ID_LISTIMG_Trade6"
#endif  ID_LISTIMG_Trade6
#ifndef ID_TEXT_TradePrice6
#define ID_TEXT_TradePrice6		"ID_TEXT_TradePrice6"
#endif  ID_TEXT_TradePrice6
#ifndef ID_TEXT_13189
#define ID_TEXT_13189		"ID_TEXT_13189"
#endif  ID_TEXT_13189

#include "UiBase.h"
class CUI_ID_FRAME_Trade :public CUIBase
{
	// Member
private:
	void ResetMembers();
	ControlFrame*	m_pID_FRAME_Trade;
	//ControlPicture*	m_pID_PICTURE_ShopItemWall;
	ControlButton*	m_pID_BUTTON_Shopping;
	ControlListImage*	m_pID_LISTIMG_Trade1;
	ControlText*	m_pID_TEXT_TradePrice1;
	ControlListImage*	m_pID_LISTIMG_Trade2;
	ControlText*	m_pID_TEXT_TradePrice2;
	ControlListImage*	m_pID_LISTIMG_Trade3;
	ControlText*	m_pID_TEXT_TradePrice3;
	ControlListImage*	m_pID_LISTIMG_Trade4;
	ControlText*	m_pID_TEXT_TradePrice4;
	ControlListImage*	m_pID_LISTIMG_Trade5;
	ControlText*	m_pID_TEXT_TradePrice5;
	ControlListImage*	m_pID_LISTIMG_Trade6;
	ControlText*	m_pID_TEXT_TradePrice6;
	ControlText*	m_pID_TEXT_13189;

public:	
	CUI_ID_FRAME_Trade();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_ShoppingOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_Trade1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Trade1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Trade1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Trade1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Trade2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Trade2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Trade2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Trade2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Trade3OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Trade3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Trade3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Trade3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Trade4OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Trade4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Trade4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Trade4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Trade5OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Trade5OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Trade5OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Trade5OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Trade6OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Trade6OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Trade6OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Trade6OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


private:
	std::vector<ControlListImage*> m_listImages;
	std::vector<ControlText*> m_prices;

	bool Buy(ControlObject* pSender, ControlIconDrag::S_ListImg* pItem);
};
extern CUI_ID_FRAME_Trade s_CUI_ID_FRAME_Trade;
