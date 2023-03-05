#include "itembag2.h"
#include "ItemDetail.h"
#include "FuncPerformanceLog.h"
#include "XmlStringLanguage.h"
#include "MeUI/ControlIconDragManager.h"
#include "MeUI/IconManager.h"
#include <time.h>
#include <map>

extern ControlIconDragManager theIconDragManager;

CItemBag2::CItemBag2()
{
    guardfunc
    m_iBagSize = 0;
    m_pPackItem = NULL;
    m_bEnables = NULL;
    m_nBagIndex = -1;
    m_nLiveItemCount = -1;
    unguard;
}

CItemBag2::~CItemBag2()
{
    guardfunc
    if ( m_bEnables )
    {
        delete[] m_bEnables;
    }
    unguard;
}

__int64 GetCPUTime2()
{
    __asm{RDTSC}
}

//根据时间及CPU指令周期计数得出唯一ID号
__int64 CItemBag2::CreateID2()
{
    guardfunc
    time_t ltime;
    time(&ltime);
    __int64 value = ltime;
    value <<= 31;
    value += (int)(GetCPUTime2());
    return value;
    unguard;
}

bool CItemBag2::CreateFromData( SCharItem *pPackItem, int iBagSize )
{
    guardfunc
    m_pPackItem = pPackItem;
    m_iBagSize  = iBagSize;
    if ( m_bEnables )
    {
        delete[] m_bEnables;
    }
    m_bEnables = new bool[iBagSize];
    for( int n=0; n<iBagSize; n++ )
    {
        m_bEnables[n] = true;
    }
    return true;
    unguard;
} 

bool CItemBag2::CanPopItem( SCharItem &item )
{
    guardfunc
    ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( item.itembaseinfo.ustItemID );
    if( !pItemDetail )
        return false;

    if ( pItemDetail->IsExclusive() )
    {
        return CanPopExclusiveItem( item );
    }
    else
    {
        return CanPopNonExclusiveItem( item.itembaseinfo.ustItemID, item.itembaseinfo.ustItemCount );
    }
    return true;
    unguard;
}

bool CItemBag2::CanPushItem( SCharItem &item, bool& bUseNewGrid )
{
    guardfunc
    ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( item.itembaseinfo.ustItemID );
    if( !pItemDetail )
        return false;
    if ( pItemDetail->IsExclusive() )
    {
        bUseNewGrid = true;
        return CanPushExclusiveItem();
    }
    else
    {
        return CanPushNonExclusiveItem( item.itembaseinfo.ustItemID, item.itembaseinfo.ustItemCount, item.IsBounded(), bUseNewGrid );
    }
    return true;
    unguard;
}

int CItemBag2::PushItem(  SCharItem &item, unsigned short &ustCount, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog,
                        short stIndex, int *pOffSet, bool *pbNew )
{
    guardfunc
    if(pLogFunc != NULL && pPlayer != NULL)
    {
        pLogFunc(pPlayer, "PushItem because:%s\0", strLog.c_str());   
    }

    if( item.itembaseinfo.ustItemID == InvalidLogicNumber )
        return ierr_unknown;
    ItemDefine::SItemCommon *pItemDetail = NULL;
    pItemDetail = GettheItemDetail().GetItemByID( item.itembaseinfo.ustItemID );
    if ( !pItemDetail )
        return ierr_unknown;
    if ( pbNew )
    {
        *pbNew = false;
    }
    //ustCount = item.itembaseinfo.ustItemCount;
    int nResult = ierr_Success;
    if ( pItemDetail->IsExclusive() )
    {
        SCharItem stItem = item;
        stItem.itembaseinfo.ustItemCount = 1;
        for ( int n=0; n<item.itembaseinfo.ustItemCount; n++ )
        {
            nResult = PushExclusiveItem( stItem, pLogFunc, pPlayer, strLog, stIndex, pOffSet, pbNew );
            if ( nResult != ierr_Success )
            {
                break;
            }
        }
    }
    else
    {
        nResult = PushNonExclusiveItem( item, pLogFunc, pPlayer, strLog, stIndex, pOffSet, pbNew, ustCount);
    }
    return nResult;
    unguard;
}
int CItemBag2::PopItemByGuID(__int64 GuID,unsigned short ustCount, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog)
{
	guardfunc
    if(pLogFunc != NULL && pPlayer != NULL)
    {
        pLogFunc(pPlayer, "PopItemByGuID 原因:%s\0", strLog.c_str());   
    }
	if (m_pPackItem == NULL)
    {
        return ierr_NotHaveTargetCountItem;
    }
	int Index = GetItemIndexByGUID(GuID);
	if(Index == -1)
		return ierr_NotHaveTargetCountItem;
	if(m_pPackItem[Index].GetItemGuid() != GuID || m_pPackItem[Index].GetItemID() == InvalidLogicNumber || m_pPackItem[Index].GetItemCount() <=0)
		return ierr_NotHaveTargetCountItem;
	m_pPackItem[Index].itembaseinfo.ustItemCount -= ustCount;
	if(m_pPackItem[Index].itembaseinfo.ustItemCount <=0)
	{
		m_pPackItem[Index].itembaseinfo.ustItemCount = 0;
		m_pPackItem[Index].itembaseinfo.ustItemID = InvalidLogicNumber;
        m_pPackItem[Index].itembaseinfo.nOnlyInt = 0;
	}
	return ierr_Success;
	unguard;
}
int CItemBag2::PopItemByID( unsigned short ustItemId, unsigned short ustCount, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog, __int64* pretGUID )
{
    guardfunc
    if(pLogFunc != NULL && pPlayer != NULL)
    {
        pLogFunc(pPlayer, "PopItemByID 原因:%s\0", strLog.c_str());   
    }
    if (m_pPackItem == NULL)
    {
        return ierr_NotHaveTargetCountItem;
    }
    int n = -1;
    if( ustItemId == InvalidLogicNumber )
        return  ierr_erritemid;
    int nRemoveCount = ustCount;
    do
    {
        SCharItem *pItem = m_pPackItem;
        int iOffset = FindItemOffsetByID( ustItemId );
        if( iOffset == -1 )
        {
            break;
        }
        pItem += iOffset;
        n = iOffset;
        if( pItem->itembaseinfo.ustItemCount >= nRemoveCount )
        {
            pItem->itembaseinfo.ustItemCount -= nRemoveCount;
            nRemoveCount = 0;
        }
        else
        {
            nRemoveCount -= pItem->itembaseinfo.ustItemCount;
            pItem->itembaseinfo.ustItemCount = 0;
        }
        if( pItem->itembaseinfo.ustItemCount == 0 )
        {
            if (pretGUID != NULL)
            {
                *pretGUID = pItem->itembaseinfo.nOnlyInt;
            }
            pItem->itembaseinfo.ustItemID = InvalidLogicNumber;
        }
    } while( nRemoveCount > 0 );

    if ( nRemoveCount == 0 )
    {
        if (n > -1)
        {
            SetBagIndex(n);
        }
		//if (pItem->storageinfo.bIsLocked)
		//{
		//	pPlayer->SubLockedItemNum();			
		//}
        return ierr_Success;
    }
    else
    {
        return ierr_NotHaveTargetCountItem;
    }
    //ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( item.itembaseinfo.ustItemID );
    //if( item.itembaseinfo.ustItemID == ErrorUnsignedShortID )
    //	return  ierr_erritemid;
    //bool bLive = false;
    //if (pItemDetail)
    //{
    //	bLive = pItemDetail->IsExclusive();
    //}
    ////else
    ////	bLive = item.bIsExclusive;
    //if (bLive )
    //{
    //	if( PopExclusiveItem( item ))
    //		return ierr_Success;
    //}
    //else
    //{
    //	ustCount = item.itembaseinfo.ustItemCount;
    //	return PopNonExclusiveItem( item.itembaseinfo.ustItemID, ustCount );
    //}
    //return ierr_unknown;
    unguard;
}

int CItemBag2::PopItem( short stIndex, unsigned short &ustCount, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog )
{
    guardfunc
    if(pLogFunc != NULL && pPlayer != NULL)
    {
        pLogFunc(pPlayer, "PopItem 原因:%s\0", strLog.c_str());   
    }

    SCharItem item;
    if( !GetItem( stIndex, &item ) )
        return ierr_IndexOutOfBagSize;
    ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( item.itembaseinfo.ustItemID );
    if( item.itembaseinfo.ustItemID == InvalidLogicNumber )
        return  ierr_ItemNotExist;

    bool bLive = false;
    if (pItemDetail)
    {
        bLive = pItemDetail->IsExclusive();
    }
    //else
    //bLive = item.bIsExclusive;
    if ( bLive )
    {
        if( PopExclusiveItemByIndex( stIndex, pLogFunc, pPlayer, strLog ) )
            return ierr_Success;
    }
    else
    {
        return PopNonExclusiveItemByIndex( stIndex, ustCount, pLogFunc, pPlayer, strLog );
    }
    return ierr_unknown;
    unguard;
}
//Luoz add 获取指定背包, 通过物品id
bool CItemBag2::GetItemByItemID( int itemid, SCharItem *pItem )
{
    guardfunc
    if( !pItem )
        return false;

    for( int iLoop = 0 ; iLoop < m_iBagSize ; iLoop ++ )
    {
        if( itemid == m_pPackItem[iLoop].itembaseinfo.ustItemID )
        {
            memcpy( pItem, &m_pPackItem[iLoop], sizeof(SCharItem) );
            return true;
        }
    }
    return false;
    unguard;
}
//Luoz add 获取指定背包,索引的信息 唯一ID
bool CItemBag2::GetItemByOnlyeID( __int64 n64Index, SCharItem *pItem )
{
    guardfunc
    if( !pItem )
        return false;

    for( int iLoop = 0 ; iLoop < m_iBagSize ; iLoop ++ )
    {
        if( ( n64Index == m_pPackItem[iLoop].itembaseinfo.nOnlyInt ) && 
			( m_pPackItem[iLoop].itembaseinfo.ustItemID != InvalidLogicNumber ) )
        {
            memcpy( pItem, &m_pPackItem[iLoop], sizeof(SCharItem) );
            return true;
        }
    }
    return false;
    unguard;
}//----------------end 


bool CItemBag2::GetItem( short stIndex, SCharItem *pItem )
{
    guardfunc
    if( !pItem )
        return false;

    if(	stIndex < 0 || stIndex >= m_iBagSize )
        return false;

    memcpy( pItem, &m_pPackItem[stIndex], sizeof(SCharItem) );
    return true;	
    unguard;
}

//清空指定背包,索引的信息
bool CItemBag2::ClearItem( short stIndex )
{
    guardfunc
    if(	stIndex < 0 || stIndex >= m_iBagSize )
        return false;

    m_pPackItem[stIndex].itembaseinfo.ustItemID = InvalidLogicNumber;
    /*m_pPackItem[stIndex].guid = GUID_NULL;*/
    m_bEnables[stIndex] = true;
    return true;
    unguard;
}
bool CItemBag2::ClearItem( unsigned int stIndex ,int Count)
{
    guardfunc
    if(	stIndex < 0 || stIndex >= m_iBagSize )
        return false;

    if (Count > 0)
    {
        if (m_pPackItem[stIndex].itembaseinfo.ustItemCount >= Count)
        {
            m_pPackItem[stIndex].itembaseinfo.ustItemCount -= Count;
        }
        else
        {
            return false;
        }


        if(m_pPackItem[stIndex].itembaseinfo.ustItemCount == 0)
        {	
            m_pPackItem[stIndex].itembaseinfo.ustItemID = InvalidLogicNumber;
        }
        return true;		
    }

    return false;
    unguard;
}
//获取指定背包,索引的状况
bool CItemBag2::IsHaveItem( unsigned short stIndex, unsigned short* pItemId )
{
    guardfunc
    SCharItem *pItem = m_pPackItem;

    if ( stIndex >= m_iBagSize )
        return false;
    if ( pItemId )
    {
        *pItemId = pItem[stIndex].itembaseinfo.ustItemID;
    }

    return (pItem[stIndex].itembaseinfo.ustItemID!=InvalidLogicNumber);
    unguard;
    /*return (pItem[stIndex].guid != GUID_NULL );*/
}

int CItemBag2::GetNullItemCount()
{
    guardfunc
    int nCount = 0;
    for( int iLoop = 0 ; iLoop < m_iBagSize ; iLoop ++ )
    {
        if( InvalidLogicNumber ==
            m_pPackItem[iLoop].itembaseinfo.ustItemID )
        {
            nCount++;
        }
    }
    return nCount;
    unguard;
}

int CItemBag2::FindNullItemOffset()
{
    guardfunc
    int iLoop;
    for( iLoop = 0 ; iLoop < m_iBagSize ; iLoop ++ )
    {
        if( InvalidLogicNumber == m_pPackItem[iLoop].itembaseinfo.ustItemID
            /*m_pPackItem[iLoop].guid == GUID_NULL*/)
            return iLoop;
    }
    return -1;
    unguard;
}

float CItemBag2::StatAllItemWeight()
{
    guardfunc
    //float fAllWeight = 0.0f;
    //int iloop;
    //for (iloop =0;iloop<m_iBagSize;iloop++)
    //{
    //	if (ErrorUnsignedShortID != m_pPackItem[iloop].itembaseinfo.ustItemID )
    //	{
    //		fAllWeight += m_pPackItem[iloop].itembaseinfo.fWeight;
    //	}
    //}	
    //return fAllWeight;
    return 0;
    unguard;
}

int CItemBag2::FindItemOffsetByID( unsigned short ustItemID,int iBeginPos )
{
    guardfunc
    int iLoop;
    for( iLoop = iBeginPos ; iLoop < m_iBagSize ; iLoop ++ )
    {
        if( ustItemID == m_pPackItem[iLoop].itembaseinfo.ustItemID )
            return iLoop;
    }
    return -1;
    unguard;
}

//是否能放入(独占类)物品
bool CItemBag2::CanPushExclusiveItem()
{
    guardfunc
    if( -1 != FindNullItemOffset() )
        return true;
    return false;
    unguard;
}

//放入(独占类)物品
int CItemBag2::PushExclusiveItem( SCharItem &item, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog, short stIndex,
                                 int *pOffSet, bool *pbNew )
{
    guardfunc
    if(pLogFunc != NULL && pPlayer != NULL)
    {
        pLogFunc(pPlayer, "PushExclusiveItem 原因:%s\0", strLog.c_str());   
    }
    if (m_pPackItem == NULL)
    {
        return ierr_unknown;
    }
    if (stIndex >= m_iBagSize)
    {
        return ierr_PackIsFull;
    }

    SCharItem *pItem = m_pPackItem;

    int iOffset = stIndex;
    float fLastWeight = 0.0f;
    if( iOffset < 0 )
    {
        iOffset = FindNullItemOffset();		
        if( -1==iOffset )
            return ierr_PackIsFull;
        if ( pbNew )
        {
            *pbNew = true;
        }
    }
    pItem += iOffset;
    if (pItem->itembaseinfo.ustItemID != InvalidLogicNumber)
    {
        return ierr_CanNotOverlap;
    }
    *pItem = item;
    if(pOffSet)
    {
        (*pOffSet) = iOffset;
    }
    SetBagIndex(iOffset);
    return ierr_Success;
    unguard;
}

//是否能取出(独占类)物品
bool CItemBag2::CanPopExclusiveItem( SCharItem &item )
{
    guardfunc
    if (&item == NULL )
    {
        return false;
    }
    SCharItem *pItem = m_pPackItem;

    int iLoop;
    for( iLoop=0; iLoop<m_iBagSize; iLoop++, pItem++ )
    {
        if( *pItem == item )
            return true;
    }
    return false;
    unguard;
}

////取出(独占类)物品
//bool CItemBag2::PopExclusiveItem( SCharItem &item )
//{
//	SCharItem *pItem = m_pPackItem;
//
//	int iLoop;
//	for( iLoop=0; iLoop<m_iBagSize; iLoop++, pItem++ )
//	{
//		//		if( *pItem == item )
//		if ( pItem->itembaseinfo.ustItemID == item.itembaseinfo.ustItemID )
//		{
//			pItem->itembaseinfo.ustItemID = ErrorUnsignedShortID;
//			/*pItem->guid = GUID_NULL;*/
//			return true;
//		}
//	}
//	return false;
//}

bool CItemBag2::PopExclusiveItemByIndex( short stIndex, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog )
{
    guardfunc
    if(pLogFunc != NULL && pPlayer != NULL)
    {
        pLogFunc(pPlayer, "PopExclusiveItemByIndex 原因:%s", strLog.c_str());   
    }
    if (stIndex <0 || stIndex >= m_iBagSize || m_pPackItem == NULL)
    {
        return false;
    }

    SCharItem *pItem = m_pPackItem;

    pItem[stIndex].itembaseinfo.ustItemID = InvalidLogicNumber;
    pItem[stIndex].bCanUse = TRUE;
	pItem[stIndex].itembaseinfo.ustItemCount = InvalidLogicNumber; //lyh++ 弹出物品的时候 设置格子中的物品数量设置为0 ，该bug是在改邮箱资费bug的时候发现 具体查看thePlayerRole.m_bag.IsHaveItemById(itemID)

    SetBagIndex(stIndex);

	//if (pItem[stIndex]->storageinfo.bIsLocked)
	//{
	//	pPlayer->SubLockedItemNum();
	//}
    /*pItem[stIndex].guid = GUID_NULL;*/
    return true;
    unguard;
}

//是否能放入(非独占类)物品
bool CItemBag2::CanPushNonExclusiveItem( unsigned short ustItemID, unsigned short ustCount, bool bBind, bool& bUseNewGrid )
{
    guardfunc
    if( ustCount == 0 )
        return false;

    int iOffset = -1;
    for( int iLoop = 0 ; iLoop < m_iBagSize ; iLoop ++ )
    {
        if( ustItemID == m_pPackItem[iLoop].itembaseinfo.ustItemID && bBind == m_pPackItem[iLoop].IsBounded() )
        {
            SCharItem *pItem = m_pPackItem;
            pItem += iLoop;
            if( pItem->itembaseinfo.ustItemCount + ustCount <= GetItemStackCount( ustItemID ) )
            {
                iOffset = iLoop; 
                break;
            }
        }
    }

    if( -1 == iOffset )
    {
        iOffset = FindNullItemOffset();
        bUseNewGrid = true;
        if( -1 == iOffset )
            return false;	
    }

    bUseNewGrid = false;
    return true;
    unguard;
}

//放入(非独占类)物品
int CItemBag2::PushNonExclusiveItem( SCharItem &item, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog, short stIndex,
                                    int *pOffSet, bool *pbNew, int nCnt )
{
    guardfunc
    if ( nCnt > item.itembaseinfo.ustItemCount )
    {
        return ierr_NotHaveTargetCountItem;
    }
    int nPushCount = item.itembaseinfo.ustItemCount;
    if ( nCnt > 0 )
    {
        nPushCount = nCnt;
    }

    if(pLogFunc != NULL && pPlayer != NULL)
    {
        pLogFunc(pPlayer, "PushNonExclusiveItem 原因:%s\0", strLog.c_str());   
    }
    //if( 0 == item.itembaseinfo.ustItemCount )
    //	return ierr_unknown;
    if (stIndex >= m_iBagSize)
    {
        return ierr_PackIsFull;
    }
    SCharItem *pItem = m_pPackItem;
    int iOffset = stIndex;
    if( iOffset < 0 )
    {
        for( int iLoop=0; iLoop<m_iBagSize; iLoop++ )
        {
            //找相同的物品的地址
            if( m_pPackItem[iLoop].itembaseinfo.ustItemID == item.itembaseinfo.ustItemID )
            {
                if (m_pPackItem[iLoop].IsBounded() == item.IsBounded())
                {// 绑定与不绑定物品不能放一起
                    int nSum = m_pPackItem[iLoop].itembaseinfo.ustItemCount + nPushCount;
                    if ( nSum <= GetItemStackCount(item.itembaseinfo.ustItemID) )
                    {
                        iOffset = iLoop;
                        break;
                    }
                }
            }
        }
        //找空位置
        if( iOffset == -1 )
        {
            iOffset = FindNullItemOffset();
        }
    }
    if( iOffset == -1 )
    {
        return ierr_PackIsFull;
    }
    pItem += iOffset;
    if( pItem->itembaseinfo.ustItemID == InvalidLogicNumber )//空的位置放新物品
    {
        *pItem = item;
        pItem->itembaseinfo.ustItemCount = nPushCount;
        SetBagIndex(iOffset);
        return ierr_Success;
    }
    else
    {
        //		if( strcmp( pItem->itembaseinfo.szItemName, item.itembaseinfo.szItemName ) != 0 )
        if( pItem->itembaseinfo.ustItemID != item.itembaseinfo.ustItemID )
        {
            return ierr_CanNotOverlap;
        }
    }
    //相同物品处理
    //如果包裹里有物品加锁则找空位置填充没有则叠加一起
    if(pItem->storageinfo.bIsLocked)
    {
        SCharItem *pLockItem = m_pPackItem;
        int nOffset = -1;
        nOffset = FindNullItemOffset();
        if(nOffset == -1)
            return ierr_ItemIsLocked;
        pLockItem += nOffset;
        if( pLockItem->itembaseinfo.ustItemID == InvalidLogicNumber )//空的位置放新物品
        {
            *pLockItem = item;
            pLockItem->itembaseinfo.ustItemCount = nPushCount;
            SetBagIndex(iOffset);
            return ierr_Success;
        }
    }
    else
    {
        int nSum = pItem->itembaseinfo.ustItemCount + nPushCount;
        if ( nSum <= GetItemStackCount(item.itembaseinfo.ustItemID) )
        {
            pItem->itembaseinfo.ustItemCount += nPushCount;
        }
        else
        {
            SCharItem *pItem2 = m_pPackItem;
            iOffset = -1;
            for( int n=0; n<m_iBagSize; n++ )
            {
                if (m_pPackItem[n].itembaseinfo.ustItemID == InvalidLogicNumber)
                {
                    iOffset = n;
                    break;
                }
            }
            if ( iOffset == -1)
            {
                return ierr_PackIsFull;
            }

            pItem2 += iOffset;

            if( pItem2->itembaseinfo.ustItemID == InvalidLogicNumber )
            {
                *pItem2 = item;
                pItem2->itembaseinfo.ustItemCount = nPushCount;
                SetBagIndex(iOffset);
                return ierr_Success;
            }
            /*pItem->itembaseinfo.ustItemCount = More_iMaxCountOfAItem;*/
            /*int nLess = nSum - More_iMaxCountOfAItem;*/
            /*if ( nLess > 0 )
            {*/
            /*item.itembaseinfo.ustItemCount = nLess;*/
            /*nResult = PushNonExclusiveItem( item, -1, pOffSet );*/
            /*return nResult;*/

            /*}*/
        }	
    }

    if ( pOffSet )
    {
        *pOffSet = iOffset;
    }
    SetBagIndex(iOffset);
    return ierr_Success;
    unguard;
}

//是否能取出(非独占类)物品
bool CItemBag2::CanPopNonExclusiveItem( unsigned short ustItemID, unsigned short ustCount )
{
    guardfunc
    SCharItem *pItem = m_pPackItem;

    int iOffset;
    iOffset = FindItemOffsetByID( ustItemID );
    if( -1 == iOffset )
    {
        return false;
    }

    pItem += iOffset;
    if( pItem->itembaseinfo.ustItemCount < ustCount )
    {
        return false;
    }
    return true;
    unguard;
}

int CItemBag2::PopNonExclusiveItemByIndex( short stIndex, unsigned short &ustCount, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog )
{
    guardfunc
    if(pLogFunc != NULL && pPlayer != NULL)
    {
        pLogFunc(pPlayer, "PopNonExclusiveItemByIndex 原因:%s\0", strLog.c_str());   
    }
    SCharItem *pItem = m_pPackItem;

    if( !IsHaveItem(stIndex) )
    {
        return ierr_NotHaveTargetCountItem;
    }

    pItem += stIndex;

    if( pItem->itembaseinfo.ustItemCount < ustCount )
    {
        //个数不足
        ustCount = pItem->itembaseinfo.ustItemCount;

        pItem->itembaseinfo.ustItemCount = 0;
        pItem->itembaseinfo.ustItemID = InvalidLogicNumber;
        pItem->bCanUse = TRUE;

        return ierr_NotHaveTargetCountItem;
    }
    if (pItem->itembaseinfo.ustItemCount >= ustCount)
    {
        pItem->itembaseinfo.ustItemCount -= ustCount;

        // 更新大红大蓝的值为初始值
        ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
        if ( pItemDetail && pItemDetail->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
        {
            ItemDefine::SItemRestore* restoreItemDetail = (ItemDefine::SItemRestore*)pItemDetail;
            if ( restoreItemDetail->bHPAuto )
            {
                pItem->itembaseinfo.value2 = restoreItemDetail->dwAddHP;
            }
            else if( restoreItemDetail->bMPAuto )
            {
                pItem->itembaseinfo.value2 = restoreItemDetail->dwAddMP;
            }
        }
    }
    else
    {
        return ierr_NotHaveTargetCountItem;
    }

    if( 0 == pItem->itembaseinfo.ustItemCount )
    {
        pItem->itembaseinfo.ustItemID = InvalidLogicNumber;
        pItem->bCanUse = TRUE;
    }
    SetBagIndex(stIndex);
	//if (pItem->storageinfo.bIsLocked)
	//{
	//	pPlayer->SubLockedItemNum();
	//}
    return ierr_Success;
    unguard;
}
bool CItemBag2::IsHaveItemById( int itemID )
{
    guardfunc
    for( int i = 0 ; i < m_iBagSize ; i ++ )
    {
        if( itemID == m_pPackItem[i].itembaseinfo.ustItemID &&
            m_pPackItem[i].itembaseinfo.ustItemCount > 0 )
        {
            return true;
        }
    }
    return false;
    unguard;
}
int CItemBag2::GetItemCount()
{
    guardfunc
//     SCharItem *pItem = m_pPackItem;
//     int n=0;
//     for ( n=0; n<m_iBagSize; n++ )
//     {
//         if ( pItem[n].itembaseinfo.ustItemID == ErrorUnsignedShortID )
//             break;
//     }
//     return n;
    return m_iBagSize - GetNullItemCount();
    unguard;
}

//{ add by ^^
int CItemBag2::GetItemCount( int iItemID )
{
    guardfunc
    int	iItemCount = 0;

    ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( iItemID );
    if( !pItemDetail )
        return 0;

    for( int i = 0 ; i < m_iBagSize ; i ++ )
    {
        if( iItemID == m_pPackItem[i].itembaseinfo.ustItemID )
        {
            //if( pItemDetail->IsExclusive() )
            //{
            //	iItemCount++;
            //}
            //else
            //{
            iItemCount += m_pPackItem[i].itembaseinfo.ustItemCount;
            //}
        }
    }
    return iItemCount;
    unguard;
}

SCharItem *CItemBag2::GetCharItemFromIdx( INT nIdx )
{
    guardfunc
    if( nIdx < 0 || nIdx >= GetNowBagSize() )
        return NULL;

    return &m_pPackItem[nIdx];
    unguard;
}
int CItemBag2::GetItemIndexByGUID( __int64 nGUID )
{
	for( int i = 0 ; i < m_iBagSize ; i ++ )
	{
		if( m_pPackItem[i].itembaseinfo.nOnlyInt == nGUID &&
			m_pPackItem[i].itembaseinfo.ustItemID != InvalidLogicNumber )
			return i;
	}
	return -1;
}

int CItemBag2::GetItemIndex( SCharItem *pItem )
{
    guardfunc
    if ( !pItem )
    {
        assert( pItem );
        return -1;
    }
    for( int i = 0 ; i < m_iBagSize ; i ++ )
    {
        //if( m_pPackItem[i] == *pItem )
        //	return i;
        if( m_pPackItem[i].Included( *pItem ) )
            return i;
    }
    return -1;
    unguard;
}

int CItemBag2::GetItemIndexById( int nId )
{
    guardfunc
    for( int i = 0 ; i < m_iBagSize ; i ++ )
    {
        if( m_pPackItem[i].itembaseinfo.ustItemID == nId )
            return i;
    }
    return -1;
    unguard;
}

//int CItemBag2::DestoryItem( SCharItem* pSrc)
//{
//	if( !pSrc )
//	{
//		assert(false);
//		return -1;
//	}
//	if( pSrc->itembaseinfo.ustItemID == ErrorUnsignedShortID )
//	{ //拖动肯定保证有物品
//		return -1;
//	}
//	
//	//ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pSrc->itembaseinfo.ustItemID );
//	
//	pSrc->itembaseinfo.ustItemID = ErrorUnsignedShortID;
//
//}

int CItemBag2::MoveItem( SCharItem* pDst, SCharItem* pSrc, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog, int nCount)
{
    guardfunc
    if(pLogFunc != NULL && pPlayer != NULL)
    {
        pLogFunc(pPlayer, "MoveItem because:%s\0", strLog.c_str());   
    }

    if ( !pDst || !pSrc )
    {
        assert(false);
        return -1;
    }

    if ( pSrc->itembaseinfo.ustItemID == InvalidLogicNumber )
    {
        return -1;
    }
    ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pSrc->itembaseinfo.ustItemID );
    if (!pItemDetail)
    {
        return -1;
    }

    bool bLive = false;
    if (pItemDetail)
    {
        bLive = pItemDetail->IsExclusive();
    }
    //else
    //	bLive = pSrc->bIsExclusive;

//     if (/*pSrc->itembaseinfo.ustItemType*/pItemDetail->ucItemType == ItemDefine::ITEMTYPE_MATERIAL)
//     {
//         ItemDefine::SCreateMaterial* pMaterial = NULL;
//         if (pItemDetail)
//         {
//             pMaterial = (ItemDefine::SCreateMaterial*)pItemDetail;
//             switch(pMaterial->stMaterialType)
//             {
//             case ItemDefine::ematerial_metal:
//             case ItemDefine::ematerial_pelage:
//             case ItemDefine::ematerial_wood:
//                 {
//                     int  iCount = MoveMaterial(pDst, pSrc, pLogFunc, pPlayer,strLog, nCount);
//                     return iCount;
//                 }
//                 break;
//             default:
//                 break;
//             }
//         }
//         else
//             return -1;
//     }
    if ( bLive)
    {
        if ( nCount != -1 && nCount != 1 )
        {
            return -1;
        }
        //
        if ( pDst->itembaseinfo.ustItemID == InvalidLogicNumber/*&&pDst->guid == GUID_NULL*/)
        {
            *pDst = *pSrc;
            pSrc->itembaseinfo.ustItemID = InvalidLogicNumber;
            pSrc->bCanUse = TRUE;
			pSrc->itembaseinfo.ustItemCount = InvalidLogicNumber; //lyh++ 移动物品的时候 原格子中的物品数量设置为0 ，该bug是在改邮箱资费bug的时候发现 具体查看thePlayerRole.m_bag.IsHaveItemById(itemID)
            /*pSrc->guid = GUID_NULL;*/
            return 1;
        }
        else
        {
            /*		SCharItem* pCharItem = NULL;
            pCharItem = pSrc;
            pSrc = pDst;
            pDst = pCharItem;
            return 1;			*/
            return -1;
        }
    }
    else
    {
        if ( nCount == -1 )
        {
            nCount = pSrc->itembaseinfo.ustItemCount;
        }
        else if( nCount > pSrc->itembaseinfo.ustItemCount||nCount > GetItemStackCount(pSrc->itembaseinfo.ustItemID) )
        {
            return -1;
        }
        //
        if ( pDst->itembaseinfo.ustItemID == InvalidLogicNumber/*&&pDst->guid == GUID_NULL*/ )
        {
            if (pSrc->itembaseinfo.ustItemCount < nCount||nCount > GetItemStackCount(pSrc->itembaseinfo.ustItemID))
            {
                return -1;
            }
			if (pSrc->itembaseinfo.ustItemCount > nCount&&pSrc->storageinfo.bIsLocked)
			{
				return -1;
			}
            pDst->itembaseinfo.ustItemID = pSrc->itembaseinfo.ustItemID;
            *pDst = *pSrc;

            if( pSrc->itembaseinfo.ustItemCount == nCount ) // 移动物品
            {
                pDst->itembaseinfo.ustItemCount = nCount;
                pSrc->itembaseinfo.ustItemCount -= nCount;

                if (pDst->IsBounded() || pSrc->IsBounded())
                { pDst->SetBounded( true ); }

                pSrc->itembaseinfo.ustItemID = InvalidLogicNumber;
                /*pSrc->guid = GUID_NULL;*/
            }
            else                                                                    // 拆分物品
            {
                // 拆分物品，先不改pSrc堆叠数，等接收到服务端MSG_MOVEGOODSACK消息再改
                pDst->itembaseinfo.ustItemCount = 0;

                // 移动AutoRestore等物品，要更新道具值
                if ( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_RESTORE && !pItemDetail->IsExclusive() )
                {
                    ItemDefine::SItemRestore* itemRestore = (ItemDefine::SItemRestore*)pItemDetail;
                    if ( itemRestore->bHPAuto )
                        pSrc->itembaseinfo.value2 = itemRestore->dwAddHP;
                    else if ( itemRestore->bMPAuto )
                        pSrc->itembaseinfo.value2 = itemRestore->dwAddMP;
                }

    //            //__int64 nInt = CreateID2();
				//// modified, jiayi, [2009/12/23]
				//// 修改guid的生成规则，与服务器同步用
    //            pDst->itembaseinfo.nOnlyInt = pSrc->itembaseinfo.nOnlyInt + 1;
            }
            return nCount;
        }
        else if ( pDst->itembaseinfo.ustItemID == pSrc->itembaseinfo.ustItemID )
        {
			if (pDst->storageinfo.bIsLocked||pSrc->storageinfo.bIsLocked)
			{
				return -1;
			}

            if ( nCount > GetItemStackCount(pSrc->itembaseinfo.ustItemID) - pDst->itembaseinfo.ustItemCount )
            {
                nCount = GetItemStackCount(pSrc->itembaseinfo.ustItemID) - pDst->itembaseinfo.ustItemCount;
            }
            pDst->itembaseinfo.ustItemCount += nCount;
            pSrc->itembaseinfo.ustItemCount -= nCount;

            if (pDst->IsBounded() || pSrc->IsBounded())
            { pDst->SetBounded( true ); }

            // 移动AutoRestore等物品，要更新道具值
            if ( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_RESTORE && !pItemDetail->IsExclusive() )
            {
                ItemDefine::SItemRestore* itemRestore = (ItemDefine::SItemRestore*)pItemDetail;
                if ( itemRestore->bHPAuto )
                {
					int totalValue = pDst->itembaseinfo.value2 + pSrc->itembaseinfo.value2;
                    if ( totalValue <= itemRestore->dwAddHP )
                    {
                        --pDst->itembaseinfo.ustItemCount;
                        pDst->itembaseinfo.value2 = totalValue;
                    }
                    else
                    {
                        pDst->itembaseinfo.value2 = totalValue - itemRestore->dwAddHP;
                    }

                    pSrc->itembaseinfo.value2 = itemRestore->dwAddHP;
                }
                else if ( itemRestore->bMPAuto )
                {
                    int totalValue = pDst->itembaseinfo.value2 + pSrc->itembaseinfo.value2;
                    if ( totalValue <= itemRestore->dwAddMP )
                    {
                        --pDst->itembaseinfo.ustItemCount;
                        pDst->itembaseinfo.value2 = totalValue;
                    }
                    else
                    {
                        pDst->itembaseinfo.value2 = totalValue - itemRestore->dwAddMP;
                    }

                    pSrc->itembaseinfo.value2 = itemRestore->dwAddMP;
                }
            }

            if ( pSrc->itembaseinfo.ustItemCount == 0 )
            {
                pSrc->itembaseinfo.ustItemID = InvalidLogicNumber;
                /*pSrc->guid = GUID_NULL;*/
            }

            return nCount;
        }
        else
        {
            return -1;
        }
    }
    unguard;
}

int CItemBag2::MoveItemGray( SCharItem* pDst, SCharItem* pSrc, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog, int nCount)
{
	guardfunc
		if(pLogFunc != NULL && pPlayer != NULL)
		{
			pLogFunc(pPlayer, "MoveItemGray because:%s\0", strLog.c_str());   
		}

		if ( !pDst || !pSrc )
		{
			assert(false);
			return -1;
		}

		if ( pSrc->itembaseinfo.ustItemID == InvalidLogicNumber )
		{
			return -1;
		}
		ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pSrc->itembaseinfo.ustItemID );
		if (!pItemDetail)
		{
			return -1;
		}

		bool bLive = false;
		if (pItemDetail)
		{
			bLive = pItemDetail->IsExclusive();
		}
		//else
		//	bLive = pSrc->bIsExclusive;

		if (/*pSrc->itembaseinfo.ustItemType*/pItemDetail->ucItemType == ItemDefine::ITEMTYPE_MATERIAL)
		{
			ItemDefine::SCreateMaterial* pMaterial = NULL;
			if (pItemDetail)
			{
				pMaterial = (ItemDefine::SCreateMaterial*)pItemDetail;
				switch(pMaterial->stMaterialType)
				{
				case ItemDefine::ematerial_metal:
				case ItemDefine::ematerial_pelage:
				case ItemDefine::ematerial_wood:
					{
						int  iCount = MoveMaterialGray(pDst, pSrc, pLogFunc, pPlayer,strLog, nCount);
						return iCount;
					}
					break;
				default:
					break;
				}
			}
			else
				return -1;
		}
		if ( bLive)
		{
			if ( nCount != -1 && nCount != 1 )
			{
				return -1;
			}
			//
			if ( pDst->itembaseinfo.ustItemID == InvalidLogicNumber/*&&pDst->guid == GUID_NULL*/)
			{
				*pDst = *pSrc;
				return 1;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			if ( nCount == -1 )
			{
				nCount = pSrc->itembaseinfo.ustItemCount;
			}
			else if( nCount > pSrc->itembaseinfo.ustItemCount||nCount > GetItemStackCount(pSrc->itembaseinfo.ustItemID))
			{
				return -1;
			}
			// 移到一个空的格子
			if ( pDst->itembaseinfo.ustItemID == InvalidLogicNumber/*&&pDst->guid == GUID_NULL*/ )
			{
				if (pSrc->itembaseinfo.ustItemCount < nCount||nCount > GetItemStackCount(pSrc->itembaseinfo.ustItemID))
				{
					return -1;
				}
				if (pSrc->itembaseinfo.ustItemCount > nCount&&pSrc->storageinfo.bIsLocked)
				{
					return -1;
				}
				pDst->itembaseinfo.ustItemID = pSrc->itembaseinfo.ustItemID;
				*pDst = *pSrc;
				pDst->itembaseinfo.ustItemCount = nCount;				
				if ( pSrc->itembaseinfo.ustItemCount == 0 )
				{
					assert( 0 && "不应该到这里，测试" );					
				}
				else
				{
					// 移动AutoRestore等物品，要更新道具值
					if ( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_RESTORE && !pItemDetail->IsExclusive() )
					{
						ItemDefine::SItemRestore* itemRestore = (ItemDefine::SItemRestore*)pItemDetail;
						if ( itemRestore->bHPAuto )
							pSrc->itembaseinfo.value2 = itemRestore->dwAddHP;
						else if ( itemRestore->bMPAuto )
							pSrc->itembaseinfo.value2 = itemRestore->dwAddMP;
					}
				}
				return nCount;
			}			
			else
			{
				return -1;
			}
		}
		unguard;
}

int CItemBag2::MoveMaterialGray(SCharItem* pDst,SCharItem* pSrc, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog,int nCount )
{
	guardfunc
		if(pLogFunc != NULL && pPlayer != NULL)
		{
			pLogFunc(pPlayer, "MoveMaterialGray 原因:%s\0", strLog.c_str());   
		}
		if ( !pDst || !pSrc )
		{
			assert(false);
			return -1;
		}
		if ( pSrc->itembaseinfo.ustItemID == InvalidLogicNumber/*&&pSrc->guid == GUID_NULL*/)
		{
			return -1;
		}
		ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pSrc->itembaseinfo.ustItemID );

		if ( pDst->itembaseinfo.ustItemID == InvalidLogicNumber )
		{
			pDst->itembaseinfo.ustItemID = pSrc->itembaseinfo.ustItemID;
			*pDst = *pSrc;
			pDst->itembaseinfo.ustItemCount = nCount;
			
			return nCount;
		}	
		else
			return -1;

		unguard;
}

int CItemBag2::MoveMaterial(SCharItem* pDst,SCharItem* pSrc, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog,int nCount )
{
    guardfunc
    if(pLogFunc != NULL && pPlayer != NULL)
    {
        pLogFunc(pPlayer, "MoveMaterial 原因:%s\0", strLog.c_str());   
    }
    if ( !pDst || !pSrc )
    {
        assert(false);
        return -1;
    }
    if ( pSrc->itembaseinfo.ustItemID == InvalidLogicNumber/*&&pSrc->guid == GUID_NULL*/)
    {
        return -1;
    }
    ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pSrc->itembaseinfo.ustItemID );

    if ( pDst->itembaseinfo.ustItemID == InvalidLogicNumber )
    {
        pDst->itembaseinfo.ustItemID = pSrc->itembaseinfo.ustItemID;
        *pDst = *pSrc;
        pDst->itembaseinfo.ustItemCount = nCount;
        pSrc->itembaseinfo.ustItemCount -= nCount;
        if ( pSrc->itembaseinfo.ustItemCount == 0 )
        {
            pSrc->itembaseinfo.ustItemID = InvalidLogicNumber;
            /*pSrc->guid = GUID_NULL;*/
        }
        return nCount;
    }

    else if ( pDst->itembaseinfo.ustItemID == pSrc->itembaseinfo.ustItemID )
    {   

     
        /*float fAllMaterialBulk = (pDst->itembaseinfo.fBulk)*(pDst->itembaseinfo.ustItemCount) + nCount*(pSrc->itembaseinfo.fBulk);
        float fpDstMod = (pDst->itembaseinfo.fBulk)/fAllMaterialBulk;
        float fpSrcMod = (pSrc->itembaseinfo.fBulk)/fAllMaterialBulk;

        float fAllMaterialRigidity = (pDst->itembaseinfo.fRigidity)*fpDstMod*(pDst->itembaseinfo.ustItemCount)+(pSrc->itembaseinfo.fRigidity)*fpSrcMod*nCount;
        float fAllMaterialIntensity = (pDst->itembaseinfo.fIntensity)*fpDstMod*(pDst->itembaseinfo.ustItemCount)+(pSrc->itembaseinfo.fIntensity)*fpSrcMod*nCount;
        float fAllMaterialToughness = (pDst->itembaseinfo.fToughness)*fpDstMod*(pDst->itembaseinfo.ustItemCount)+(pSrc->itembaseinfo.fToughness)*fpSrcMod*nCount;
        float fAllMaterialWeight = (pDst->itembaseinfo.fWeight)*(pDst->itembaseinfo.ustItemCount)+nCount*(pSrc->itembaseinfo.fWeight);
        float fAllMaterialDensity = (pDst->itembaseinfo.fDensity)*(pDst->itembaseinfo.ustItemCount) + nCount*(pSrc->itembaseinfo.fDensity);		

        memcpy(&theItem,pSrc,sizeof(SCharItem));

        theItem.itembaseinfo.fBulk = fAllMaterialBulk/nSum;
        theItem.itembaseinfo.fDensity = fAllMaterialDensity/nSum;
        theItem.itembaseinfo.fIntensity = fAllMaterialIntensity/nSum;
        theItem.itembaseinfo.fRigidity = fAllMaterialRigidity/nSum;
        theItem.itembaseinfo.fToughness = fAllMaterialToughness/nSum;
        theItem.itembaseinfo.fWeight = fAllMaterialWeight/nSum;*/
	

		pDst->itembaseinfo.ustItemCount += nCount;
		pSrc->itembaseinfo.ustItemCount -= nCount;

        if ( pSrc->itembaseinfo.ustItemCount == 0 )
        {
            pSrc->itembaseinfo.ustItemID = InvalidLogicNumber;
            /*pSrc->guid = GUID_NULL;*/
        }

        return pDst->itembaseinfo.ustItemCount;
    }
    else
        return -1;

    unguard;
}
/*
@ stindex : 物品索引
@ bLocked : 物品加锁开关
@ return: BasePlayer
*/
bool CItemBag2::SetItemProperty(short stIndex,bool bLocked)
{
    guardfunc
    bool ret = false;
    if (stIndex <0 || stIndex >= m_iBagSize)
    {
        return ret;
    }
    if (m_pPackItem[stIndex].storageinfo.bIsLocked != bLocked) 
    {
        m_pPackItem[stIndex].storageinfo.bIsLocked = bLocked;
        ret = true;
    }
	return ret;
    unguard;
}
/*

*/
bool CItemBag2::ExchangeItem( SCharItem* pDst, SCharItem* pSrc, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog )
{
    guardfunc
    if(pLogFunc != NULL && pPlayer != NULL)
    {
        pLogFunc(pPlayer, "ExchangeItem 原因:%s\0", strLog.c_str());   
    }
    if ( !pDst || !pSrc )
    {
        return false;
    }
    SCharItem temp;
    temp = *pDst;
    *pDst = *pSrc;
    *pSrc = temp;
    return true;
    unguard;
}

unsigned short CItemBag2::m_usLastItemIdOfQueryStackCount = InvalidLogicNumber;
unsigned short CItemBag2::m_usLastQueryStackCount = More_iMaxCountOfAItem;

int CItemBag2::GetItemStackCount( unsigned short ustItemID )
{
	if( m_usLastItemIdOfQueryStackCount == ustItemID )
		return m_usLastQueryStackCount;
	ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( ustItemID );
	if( pItemDetail )
	{
		// TODO
		m_usLastItemIdOfQueryStackCount = ustItemID;
		m_usLastQueryStackCount = pItemDetail->nStackNum;
		return m_usLastQueryStackCount;
	}
	return More_iMaxCountOfAItem;
}
