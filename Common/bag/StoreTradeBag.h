//
//#pragma once
//#include "..\..\common\More.h"
//
//class CStoreTradeBag
//{
//public:
//	CStoreTradeBag( );
//	~CStoreTradeBag( );
//
//	//初始化指针
//	bool CreateFromData( SCharStore *pStoreItem,
//						 SCharTrade *pTradeItem,
//						 int iStoreBagSize, int iTradeBagSize );
//
//
//
//	//放入物品
//	bool PushItem( short stWhichBag, SCharItem &item, short stIndex=-1 );
//	//取出物品
//	bool PopItem( short stWhichBag, SCharItem &item );
//	bool PopItem( short stWhichBag, short stIndex );
//
//
//	//放入金钱
//	bool PushMoney( short stWhichBag, DWORD dwMoney );
//	//取出金钱
//	bool PopMoney( short stWhichBag, DWORD dwMoney );
//
//	//获取金钱总数
//	int  GetMoney( short stWhichBag );
//
//	//获取指定背包,索引的信息
//	bool GetItem( short stWhichBag, short stIndex, SCharItem *pItem );
//
//	//清空指定背包,索引的信息
//	bool ClearItem( short stWhichBag, short stIndex );
//
//	//获取指定背包,索引的状况...判断该位置是有
//	bool IsHaveItem( short stWhichBag, short stIndex );
//	//add by ^^
//	int  GetItemCount( int iItemID );
//
//private:
//	//找出指定背包的空闲位置
//	int FindNullItemOffset( short stWhichBag );
//
//	//根据背包的类型取得指针
//	SCharItem* GetBagPointByType( short stWhichBag );
//
//	//根据背包的类型取得最大数目
//	short GetBagSizeByType( short stWhichBag );
//
//	//仓库背包的最大数目
//	int m_iStoreBagSize;
//
//	//交易背包的最大数目
//	int m_iTradeBagSize;
//
//	//相关指针
//	SCharStore *m_pStoreItem;
//	SCharTrade *m_pTradeItem;
//};
//
