///********************************************************************
//	Filename: 	ShopCenterSlk.h
//	MaintenanceMan Mail: Luo_157@hotmail.com
//*********************************************************************/
//
#ifndef __TRADECENTERCONFIG_H__
#define __TRADECENTERCONFIG_H__
//
#pragma once
//
//#include "GlobalDef.h"
/*
 * Author: 2012-9-26 16:02:47 liaojie
 * Desc:   这个文件貌似没什么用，功能都在TradeCenterInfo.h里了，先把这个注释掉看有没有问题
 */
///************************************************************************
//    DiscountPercent     总体折扣
//    Name                商品类型
//    ItemId              物品id
//    OriginalPrice       原始价格
//    FinalDiscountPrice  最终价格
//    TicketPrice         所需购物券
//    Count               商品数量
//    RefreshInterval     刷新间隔（分钟）
//    IsHot               热卖
//    IsNew               新品                                                            
//************************************************************************/
////商品信息
//class TradeItem
//{
//public:
//	TradeItem()
//	{
//		ItemId = InvalidLogicNumber;
//		OriginalPrice = 0;
//		FinalDiscountPrice = 0;
//        TicketPrice = 0;
//		Count = 0;
//		CurrentCount = 0;
//		RefreshInterval = 0;
//		IsHot = false;
//		IsNew = false;
//        TypeName.clear();
//	}
//
//    TradeItem( const TradeItem& xItem )
//    {
//        *this = xItem;
//    }
//
//    TradeItem& operator = ( const TradeItem& xItem )
//    {
//        if ( &xItem != this )
//        {
//            TypeName           = xItem.TypeName;
//            ItemId             = xItem.ItemId;
//            OriginalPrice      = xItem.OriginalPrice;
//            FinalDiscountPrice = xItem.FinalDiscountPrice;
//            TicketPrice        = xItem.TicketPrice;
//            Count              = xItem.Count;
//            CurrentCount       = xItem.CurrentCount;
//            RefreshInterval    = xItem.RefreshInterval;
//            IsHot              = xItem.IsHot;
//            IsNew              = xItem.IsNew;
//        }
//        return *this;
//    }
//
//	bool operator == (const int& nItemId)
//	{
//		return (this->ItemId == nItemId);
//	}
//
//public:
//	static unsigned char DiscountPercent;	//商城整体折扣比率，如有填DiscountPrice，依旧会折上折 ( 1 - 100)
//    
//    std::string TypeName;                   // 商品类型
//	unsigned short ItemId;					// 物品ID
//	unsigned short OriginalPrice;			// 原始价格
//	unsigned short FinalDiscountPrice;		// 最终价格
//    unsigned short TicketPrice;             // 所需购物券 金锭
//    unsigned int Count;					    // 出售数量   金票
//	unsigned int CurrentCount;			    // 当前出售的数量
//	unsigned int RefreshInterval;			// 刷新周期  或空为每天刷新，否则以分钟为单位刷新
//	bool IsHot;								// 是否热卖, 0或空为无效
//	bool IsNew;								// 是否新品, 0或空为无效
//};
//
//#define theTradeCenterConfig TradeCenterConfig::Instance()
//
//class TradeCenterConfig
//{
//public:
//	~TradeCenterConfig();
//
//	static TradeCenterConfig& Instance()
//	{
//		static TradeCenterConfig s_xTradeCenterManger;
//		return s_xTradeCenterManger;
//	}
//
//	bool       LoadTradeItemConfig( const char* szFile );
//	bool       AddTradeItem       ( TradeItem &xShopData, bool bReplace = false );
//	uint32     GetTradeItemCount  () { return static_cast<unsigned int>( m_mapTradeItem.size() ); }
//	TradeItem* GetTradeItemByIndex( unsigned int nIndex );
//	TradeItem* GetTradeItemByItemID( unsigned short nItemId );
//
//    bool AddTradeItemTypeName( std::string& strType, unsigned short ustItemID );
//    bool RemoveTradeItemTypeName( std::string& strType, unsigned short ustItemID );
//    void GetTradeItemIDByType( std::string& strType, std::vector<unsigned short>& vecItemID );
//
//	bool RefurbishCount(DWORD dwTime);			//刷新出售数量
//
//    //编辑器使用相关
//	bool SaveTradeItemConfig(const char* szFile);
//	bool RemoveTradeItem(unsigned short nItemId);
//	bool ChangeDiscountPercent(unsigned char nDiscountPercent);   //修改折扣
//
//public:
//    typedef std::map< std::string, std::vector< unsigned short > > TypeMap;
//    typedef TypeMap::iterator TypeMapIter;
//
//    typedef std::map< unsigned short, TradeItem > TradeItemMap;
//    typedef TradeItemMap::iterator TradeItemMapIter;
//
//	TradeItemMap m_mapTradeItem; // id 和商品关联
//    TypeMap m_mapType;           // 保存商品类型和该类商品的关联
//
//private:
//	TradeCenterConfig();
//};
//
#endif // __TRADECENTERCONFIG_H__
