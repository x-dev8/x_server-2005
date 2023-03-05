#include "DropCommonItem.h"
#include "DropItem.h"
#include "SlkReader.h"
#include "ErrorLog.h"
#include "ResourcePath.h"
#include "DropItemManager.h"

DropCommonItem::DropCommonItem()
{
}

DropCommonItem::~DropCommonItem()
{
}

bool DropCommonItem::Drop( unsigned int nPackIndex, int nMapId, float fX, float fY,
                                    int nTask, BaseCharacter* pOwner )
{

    SCommonDrop* pDropItem = theDropCommonItemConfig.GetSCommonDropByIndex(nPackIndex) ;  //&m_vtDropItem[nPackIndex];
	
	if(pDropItem == NULL)
	{
		return false;
	}
	
    // 获得掉落数量
    int nDropCount = GetDropCount( pDropItem->vtItem,
                                    pDropItem->nMinDropCount,
                                    pDropItem->nMaxDropCount );
    if ( nDropCount > 0 )
    {
        // 掉落物品
        if ( pDropItem->bRepeat )
        {
            DropItems( pDropItem->vtItem, nDropCount,
                        pDropItem->bRepeat,
                        nMapId, fX, fY,
                        nTask, pOwner );
        }
        else
        {
            std::vector<SDropItem> vtDropItem = pDropItem->vtItem;
            DropItems( vtDropItem, nDropCount,
                        pDropItem->bRepeat,
                        nMapId, fX, fY,
                        nTask, pOwner );
        }
    }

    return true;
}

bool DropCommonItem::DropPackage(unsigned int nPackIndex, DropItemVector& vecDropItem )
{
    // 获得掉落包
    SCommonDrop* pDropItem = theDropCommonItemConfig.GetSCommonDropByIndex(nPackIndex) ;  //&m_vtDropItem[nPackIndex];

    if(pDropItem == NULL)
    { return false; }

    if (pDropItem->vtItem.size() == 0)
    { return false; }

    // 获得掉落数量
    int nDropCount = GetDropCount( pDropItem->vtItem, pDropItem->nMinDropCount, pDropItem->nMaxDropCount );

    if (nDropCount == 0)
    { return false; }

    // 掉落几率
    int nProbability = 0;
    int nRand = theRand.rand32() % DROP_PROBABILITY;

    // 保存已经掉落的物品id
    std::vector<uint16> vecHasDrop; 
    for ( int i = 0; i < nDropCount; ++i )
    {
        DropItemInfos::iterator iter = pDropItem->vtItem.begin();
        for ( ; iter != pDropItem->vtItem.end() ; ++iter)
        {
            if ( nDropCount <= 0 )
            { break; }

            if(!pDropItem->bRepeat) // 是不能重复掉的
            {
                std::vector<uint16>::iterator findIter = find(vecHasDrop.begin(), vecHasDrop.end(), iter->nItemId);
                if (findIter != vecHasDrop.end()) // 已经掉落了
                { continue; }
            }

            nProbability += iter->nProbability;
            
            // 判断概率
            if ( nRand < nProbability ) 
            {
                if ( theDropItemManager.CheckItemCanDrop( iter->nItemId, iter->nItemNum ) )      // 判断阈值
                {
                    AddDropItemInPackage(vecDropItem, *iter, iter->nItemNum );

                    // 如果不可以重复掉落
                    if (!pDropItem->bRepeat)        
                    { vecHasDrop.push_back(iter->nItemId); }

                    --nDropCount;
                }
            }
        }
    }

    // 获得掉落数量(用平均数量的算法)
    //while ( pDropItem->vtItem.size() > 0 && nDropCount > 0 )
    //{
    //    // 掉落机率总和
    //    int nSum = GetSumProbability( pDropItem->vtItem );
    //    if ( nSum <= 0 )
    //        break;
    //    int nRand = theRand.rand32() % nSum;
    //    int nCur = 0;
    //    DropItemInfos::iterator end = pDropItem->vtItem.end();
    //    for (DropItemInfos::iterator iter = pDropItem->vtItem.begin(); iter != end; ++iter)
    //    {
    //        nCur += iter->nProbability;

    //        if ( nRand < nCur )
    //        {
    //            AddDropItemInPackage(mapDropItem, iter->nItemId);
    //        }
    //    }

    //    --nDropCount;
    //}

    return true;
}
