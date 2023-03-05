#ifndef __STALL_CONFIG_H__
#define __STALL_CONFIG_H__

#include "GlobalDef.h"

class StallConfig
{
public:
	// 一项花费
	struct OneCost
	{
		uint8	nType;		// 类型 ECostType
		uint16	nSubType;	// 子类型(道具ID)
		uint16	nValue;		// 数量
	};
	typedef std::vector<OneCost>	CostList;
	typedef CostList::iterator		ItrCostList;

	// 一种套餐
	struct CostSetmeal
	{
		uint8		nID;			// 套餐ID
		uint32		nStallRevenue;	// 摊位税(占地税)
		uint8		nTradeRevenue;	// 交易税率
		uint32		nTime;			// 持续时间,单位秒,仅离线用
		CostList	costList;		// 花费列表
	};

	// 离线摆摊的所有可选套餐
	typedef	std::vector<CostSetmeal>	StallCostMenu;
	typedef StallCostMenu::iterator		ItrStallCostMenu;

public:
	bool	LoadStallConfig( const char* szFile );

	int		GetOfflineCostSetmealCount()	{ return static_cast< int > ( _OfflineStallCostMenu.size() ) ; }
	CostSetmeal*	GetOfflineCostSetmeal( int nIndex );

	int		GetOnlineCostSetmealCount()	{ return static_cast< int > ( _OnlineStallCostMenu.size() ) ; }
	CostSetmeal*	GetOnlineCostSetmeal( int nIndex );

	CostSetmeal*	GetOnlineCostSetmealByID( uint8 nID );
	CostSetmeal*	GetOfflineCostSetmealByID( uint8 nID );

private:
	StallCostMenu	_OfflineStallCostMenu;
	StallCostMenu	_OnlineStallCostMenu;
};
StallConfig& GetStallConfig();

#endif