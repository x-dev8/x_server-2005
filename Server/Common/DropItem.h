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
    int     nBroadcastStrID ;   // ����String ID

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
	int nProbability;               // �������
	int nPackProbabilityRate;       // �ȼ���ϵ����ʽ�е�Yֵ
	std::vector<SCommonPackID> vtCommonPackID;    // �����

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
    // ������Ʒ
    // ��ƷID ��Ʒ���� ��ͼ���� �Ƿ���������Ʒ ��Ʒӵ����
    static bool DropItem( int nItemId, int nCount, int nMapId, float fX, float fY, int nTask, BaseCharacter* pOwner );          

    // ��ƷID ��Ʒ���� ��ͼ���� �Ƿ���������Ʒ ��Ʒӵ����
    static bool DropItem( int nItemId, int nCount, int nMapId, float fX, float fY, int nTask, int nGruopId, int nPlayerId );    

    // ������Ʒ�����ﱳ��
    static bool DropItem(int nItemId, int nCount, GamePlayer* pOwner, int nTask = 0, int nTaskId = -1, int nTaskState = -1);

    // ����һ����Ʒ����
    static void AddDropItemInPackage( DropItemVector& vecDropItem, uint16 nItemId, int nCount = 1 );
    static void AddDropItemInPackage( DropItemVector& vecDropItem, SDropItem dropItem, int nCount = 1 );
    static bool DropItemPackage     ( DropItemVector& vecDropItem, DropCharItemVector& vecCharItem, unsigned long dwTeamSessionID, unsigned long dwPlayerID, GameObjectId nMonsterID, unsigned long nMapId, float fX, float fY, uint16 uchType = 0 );
    static bool DropItemAround      ( DropItemVector& vecDropItem, DropCharItemVector& vecCharItem, unsigned long dwTeamSessionID, unsigned long dwPlayerID, GameObjectId nMonsterID, unsigned long nMapId, float fX, float fY, uint16 uchType = 0 );

    DropBaseItem();
    virtual ~DropBaseItem();

protected:
    int  GetSumProbability( DropItemInfos& vtItem );                         // ��õ�������ܺ�
    int  GetDropCount( DropItemInfos& vtItem,  int nMinDrop, int nMaxDrop ); // ��õ�������
    bool DropItems( DropItemInfos& vtItem,  int nCount, bool bRepeat, int nMapId, float fX, float fY, int nTask, BaseCharacter* pOwner ); // ������Ʒ

};

#endif // __GAMESERVER_DROPITEM_H__