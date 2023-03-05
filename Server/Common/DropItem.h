/********************************************************************
    Filename:     DropItem.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_DROPITEM_H__
#define __GAMESERVER_DROPITEM_H__

#pragma once

#include "MeRTLibsServer.h"
#include "ItemCharacter.h"

class ItemCharacter;
class MonsterBaseEx;
class BaseCharacter;
class GamePlayer;


#define DROP_PROBABILITY        100000
#define MAX_COMMONPACK_COUNT	15


enum EPackDropItemType
{
    PackDropType_Package,
    PackDropType_Around ,
};

struct SDropItem
{
	int     nItemId         ;
    int     nItemNum        ;
	int     nProbability    ;
    bool    bIsBound        ;
    bool    bStarRandom     ;
    uint8   nStarLevel      ;
    int     nBroadcastStrID ;   // 公告String ID

    SDropItem () 
    {
        memset( this, 0, sizeof(SDropItem));
    }

	SDropItem& operator = (const SDropItem& xSDropItem)
	{
		if (this != &xSDropItem)
		{
			nItemId       = xSDropItem.nItemId;
            nItemNum      = xSDropItem.nItemNum;
			nProbability  = xSDropItem.nProbability;
            bIsBound      = xSDropItem.bIsBound;
            bStarRandom   = xSDropItem.bStarRandom;
            nStarLevel    = xSDropItem.nStarLevel;
            nBroadcastStrID = xSDropItem.nBroadcastStrID;
		}

		return *this;
	}

	bool operator == (const int Id) { return (this->nItemId == Id); }
};

struct SCommonDrop
{
	int           nPackId;
	int           nMinDropCount;
	int           nMaxDropCount;
	bool          bRepeat;
	std::vector<SDropItem> vtItem;

	SCommonDrop& operator = (const SCommonDrop& xSCommonDrop)
	{
		if (this != &xSCommonDrop)
		{
			nPackId         = xSCommonDrop.nPackId;
			nMinDropCount   = xSCommonDrop.nMinDropCount;
			nMaxDropCount   = xSCommonDrop.nMaxDropCount;
			bRepeat			= xSCommonDrop.bRepeat;

			vtItem.clear();
			vtItem.assign(xSCommonDrop.vtItem.begin(),xSCommonDrop.vtItem.end() );
		}

		return *this;
	}

	bool operator == (const int Id) { return (this->nPackId == Id); }
	bool operator < (const SCommonDrop& xSCommonDrop) { return (this->nPackId < xSCommonDrop.nPackId); }
};

struct SMonsterPack
{
	SMonsterPack()
	{
		nRandCount = 0;
	}
	SDropItem stItem;
	int        nRandCount;

	SMonsterPack& operator = (const SMonsterPack& xSMonsterPack)
	{
		if (this != &xSMonsterPack)
		{
			stItem.nItemId        = xSMonsterPack.stItem.nItemId;
			stItem.nProbability   = xSMonsterPack.stItem.nProbability;
		}

		return *this;
	}

	bool operator == (const int Id) { return (this->stItem.nItemId == Id); }
};

struct SCommonPackID
{
	int nID;
	int nIndex;

	SCommonPackID& operator = (const SCommonPackID& xSCommonPackID)
	{
		if (this != &xSCommonPackID)
		{
			nID      = xSCommonPackID.nID;
			nIndex   = xSCommonPackID.nIndex;
		}

		return *this;
	}

	bool operator == (const int Id) { return (this->nID == Id); }
};

struct SCommonPack
{
	int nProbability;               // 掉落机率
	int nPackProbabilityRate;       // 等级差系数公式中的Y值
	std::vector<SCommonPackID> vtCommonPackID;    // 掉落包

	SCommonPack& operator = (const SCommonPack& xSCommonPack)
	{
		if (this != &xSCommonPack)
		{
			nProbability            = xSCommonPack.nProbability;
			nPackProbabilityRate    = xSCommonPack.nPackProbabilityRate;

            vtCommonPackID.assign(xSCommonPack.vtCommonPackID.begin(),xSCommonPack.vtCommonPackID.end());
		}

		return *this;
	}
};

struct SMonsterDrop
{
	int    nMonsterId;
    uint8  nPackDropType;
	std::vector<SMonsterPack> vtMonsterPack;
	std::vector<SCommonPack>  vtPackId;

	SMonsterDrop& operator = (const SMonsterDrop& xSMonsterDrop)
	{
		if (this != &xSMonsterDrop)
		{
			nMonsterId      = xSMonsterDrop.nMonsterId;
            nPackDropType   = xSMonsterDrop.nPackDropType;

			vtMonsterPack.assign(xSMonsterDrop.vtMonsterPack.begin(),xSMonsterDrop.vtMonsterPack.end());
			vtPackId.assign(xSMonsterDrop.vtPackId.begin(),xSMonsterDrop.vtPackId.end());
		}

		return *this;
	}

	bool operator == (const int Id) { return (this->nMonsterId == Id); }
};

struct SBroadcastDrop
{
    int nStringID   ;
    int nItemID     ;
};

typedef std::vector<SDropItem> DropItemVector;
typedef DropItemVector::iterator DropItemVectorIter;

typedef std::vector<SCharItem> DropCharItemVector;
typedef DropCharItemVector::iterator DropCharItemVectorIter;

typedef std::vector<SDropItem> DropItemInfos;

class DropBaseItem
{
public:
    // 掉落物品
    // 物品ID 物品数量 地图坐标 是否是任务物品 物品拥有者
    static bool DropItem( int nItemId, int nCount, int nMapId, float fX, float fY, int nTask, BaseCharacter* pOwner );          

    // 物品ID 物品数量 地图坐标 是否是任务物品 物品拥有者
    static bool DropItem( int nItemId, int nCount, int nMapId, float fX, float fY, int nTask, int nGruopId, int nPlayerId );    

    // 掉落物品在人物背包
    static bool DropItem(int nItemId, int nCount, GamePlayer* pOwner, int nTask = 0, int nTaskId = -1, int nTaskState = -1);

    // 掉落一个物品包裹
    static void AddDropItemInPackage( DropItemVector& vecDropItem, uint16 nItemId, int nCount = 1 );
    static void AddDropItemInPackage( DropItemVector& vecDropItem, SDropItem dropItem, int nCount = 1 );
    static bool DropItemPackage     ( DropItemVector& vecDropItem, DropCharItemVector& vecCharItem, unsigned long dwTeamSessionID, unsigned long dwPlayerID, GameObjectId nMonsterID, unsigned long nMapId, float fX, float fY, uint16 uchType = 0 );
    static bool DropItemAround      ( DropItemVector& vecDropItem, DropCharItemVector& vecCharItem, unsigned long dwTeamSessionID, unsigned long dwPlayerID, GameObjectId nMonsterID, unsigned long nMapId, float fX, float fY, uint16 uchType = 0 );

    DropBaseItem();
    virtual ~DropBaseItem();

protected:
    int  GetSumProbability( DropItemInfos& vtItem );                         // 获得掉落机率总和
    int  GetDropCount( DropItemInfos& vtItem,  int nMinDrop, int nMaxDrop ); // 获得掉落数量
    bool DropItems( DropItemInfos& vtItem,  int nCount, bool bRepeat, int nMapId, float fX, float fY, int nTask, BaseCharacter* pOwner ); // 掉落物品

};

#endif // __GAMESERVER_DROPITEM_H__