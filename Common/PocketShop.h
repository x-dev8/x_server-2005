#pragma once
#include <map>
#include <string>
#include <vector>
#include "GlobalDef.h"

class CPocketShopManger
{
public:
	struct SPocketShop
	{
		int		nItemID;
		//int	nTotalCount;
		int		nPerCount;			//每堆的个数（每次买这么多）
		int		nBuyPrice;			//每堆买的价格
		//int		nSellPrice;			//每堆卖的价格
		byte	byCostType;			//消费类型				ItemDetail.h  ECostType中定义
		bool    bIsBound;
	};
public:
	CPocketShopManger();
	~CPocketShopManger();

	typedef std::map<int,SPocketShop*> PocketShopMap;
	bool LoadConifg(const char* szFileName);

	static CPocketShopManger& Instance()
	{
		static CPocketShopManger cPocketShop;
		return cPocketShop;
	}
	static SShopItem SPocketShopToSShopItem(SPocketShop* item);
	bool IsLoad(){return m_bIsLoad;}
	PocketShopMap& GetPocketShopData(){return mapPocketShop;}
	SPocketShop*   GetPocketShopItemByID(int nItemID);
	std::vector<int>& GetPocketShopAllID(){return m_vecID;}
private:
	PocketShopMap mapPocketShop;
	bool m_bIsLoad;
	std::vector<int>		m_vecID;
};

#define thePocketShopManager		CPocketShopManger::Instance()