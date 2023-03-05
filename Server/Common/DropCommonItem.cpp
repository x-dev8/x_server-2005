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
	
    // ��õ�������
    int nDropCount = GetDropCount( pDropItem->vtItem,
                                    pDropItem->nMinDropCount,
                                    pDropItem->nMaxDropCount );
    if ( nDropCount > 0 )
    {
        // ������Ʒ
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
    // ��õ����
    SCommonDrop* pDropItem = theDropCommonItemConfig.GetSCommonDropByIndex(nPackIndex) ;  //&m_vtDropItem[nPackIndex];

    if(pDropItem == NULL)
    { return false; }

    if (pDropItem->vtItem.size() == 0)
    { return false; }

    // ��õ�������
    int nDropCount = GetDropCount( pDropItem->vtItem, pDropItem->nMinDropCount, pDropItem->nMaxDropCount );

    if (nDropCount == 0)
    { return false; }

    // ���伸��
    int nProbability = 0;
    int nRand = theRand.rand32() % DROP_PROBABILITY;

    // �����Ѿ��������Ʒid
    std::vector<uint16> vecHasDrop; 
    for ( int i = 0; i < nDropCount; ++i )
    {
        DropItemInfos::iterator iter = pDropItem->vtItem.begin();
        for ( ; iter != pDropItem->vtItem.end() ; ++iter)
        {
            if ( nDropCount <= 0 )
            { break; }

            if(!pDropItem->bRepeat) // �ǲ����ظ�����
            {
                std::vector<uint16>::iterator findIter = find(vecHasDrop.begin(), vecHasDrop.end(), iter->nItemId);
                if (findIter != vecHasDrop.end()) // �Ѿ�������
                { continue; }
            }

            nProbability += iter->nProbability;
            
            // �жϸ���
            if ( nRand < nProbability ) 
            {
                if ( theDropItemManager.CheckItemCanDrop( iter->nItemId, iter->nItemNum ) )      // �ж���ֵ
                {
                    AddDropItemInPackage(vecDropItem, *iter, iter->nItemNum );

                    // ����������ظ�����
                    if (!pDropItem->bRepeat)        
                    { vecHasDrop.push_back(iter->nItemId); }

                    --nDropCount;
                }
            }
        }
    }

    // ��õ�������(��ƽ���������㷨)
    //while ( pDropItem->vtItem.size() > 0 && nDropCount > 0 )
    //{
    //    // ��������ܺ�
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
