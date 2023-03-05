//
//#pragma once
//
//
//class CItemBag2;
//class CProduceItemBag
//{
//public:
//	CProduceItemBag( );
//	~CProduceItemBag( );
//
//	//初始化指针
//	bool CreateFromData( SProduceItem *pProduceItem );
//	void SetItemBagPoint( CItemBag2 *pItemBag );
//
//	//放入原料（包括工具）
//	void PushItem( SCharItem &item, short stPos );
//	//取出原料（包括工具）
//	void PopItem( short stPos, unsigned short &ustCount );
//	
//	//获取指定位置的信息
//	bool GetItem( short stPos, SCharItem *pItem );
//	//清空指定位置的信息
//	bool ClearItem( short stPos );
//	//判断指定位置是否有信息
//	bool IsHaveItem( short stPos );
//
//	//进行制造物品的操作！！
//	bool ProduceItem( );
//
//private:
//	CItemBag2 *m_pItemBag;	//物品背包的指针
//	SProduceItem *m_pProduceItem;
//							//制造背包的数据
//};
