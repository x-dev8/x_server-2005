#ifndef __STALL_CONFIG_H__
#define __STALL_CONFIG_H__

#include "GlobalDef.h"

class StallConfig
{
public:
	// һ���
	struct OneCost
	{
		uint8	nType;		// ���� ECostType
		uint16	nSubType;	// ������(����ID)
		uint16	nValue;		// ����
	};
	typedef std::vector<OneCost>	CostList;
	typedef CostList::iterator		ItrCostList;

	// һ���ײ�
	struct CostSetmeal
	{
		uint8		nID;			// �ײ�ID
		uint32		nStallRevenue;	// ̯λ˰(ռ��˰)
		uint8		nTradeRevenue;	// ����˰��
		uint32		nTime;			// ����ʱ��,��λ��,��������
		CostList	costList;		// �����б�
	};

	// ���߰�̯�����п�ѡ�ײ�
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