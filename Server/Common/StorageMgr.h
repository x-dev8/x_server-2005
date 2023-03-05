/********************************************************************
    Filename:    StorageMgr.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#pragma once
/*urpose:
仓库是储存玩家道具的场所
1	每个城市有每个城市的仓库
2	每个城市的仓库不能互通
3	整个游戏世界一共拥有30个仓库
4	每个仓库最大可以拥有10个格子
5	每个格子最大可以累加存放99个物品
6	每个仓库有开启密码
7	玩家可以对物品进行锁操作
8	每个在仓库存放的物品,都有独立的使用密码
9	拥有独立密码的物品丢弃,交换,买卖都必须经过主人确认
10	独立密码由玩家自己设定
11	玩家使用独立密码才能对物品产生操作
12	仓库初始拥有5个格子,最大拥有10个格子
13	可以花钱购买新的格子
14	每个格子需要花费1游戏币*(N+1), N=已有钱柜数量
*/
#include "MeRTLibsServer.h"

class CStorageMgr
{
public:
	CStorageMgr(void);
	~CStorageMgr(void);
public:
	int GetCityInfo(int nStorageNpcId);
	const char* GetNpcName(int nStorageNpcId);
public:
	int nNpcID;
};

CStorageMgr* GetStorageMgr();
