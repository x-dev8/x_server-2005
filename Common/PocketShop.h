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
		int		nPerCount;			//ÿ�ѵĸ�����ÿ������ô�ࣩ
		int		nBuyPrice;			//ÿ����ļ۸�
		//int		nSellPrice;			//ÿ�����ļ۸�
		byte	byCostType;			//��������				ItemDetail.h  ECostType�ж���
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