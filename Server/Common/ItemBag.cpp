#include "ItemBag.h"
#include "ItemDetail.h"
#include "FuncPerformanceLog.h"
#include "XmlStringLanguage.h"
//#include "LogFileObjectName.h"
#include "GamePlayer.h"
#include "TimeEx.h"

ItemBag::ItemBag()
{
    m_iBagSize       = 0;
    m_pPackItem      = NULL;
    m_bEnables       = NULL;
    m_nBagIndex      = -1;
    m_nLiveItemCount = -1;
    m_mapPackItem.clear();
    _pGamePlayer     = NULL;
    _nItemBagType    = BT_NormalItemBag;
}

ItemBag::~ItemBag()
{
    if ( m_bEnables )
    {
        delete[] m_bEnables;
    }
}

bool ItemBag::CreateFromData( GamePlayer* pOwn, SCharItem* pPackItem, int iBagSize, unsigned char nItemBagType  )
{
    if ( !pPackItem || iBagSize<0 || !pOwn)
        return false;

    m_pPackItem   = pPackItem;
    m_iBagSize    = iBagSize;
    _pGamePlayer  = pOwn;
    _nItemBagType = nItemBagType;
    m_mapPackItem.clear();
    for(int i=0; i<m_iBagSize; ++i)
    {
        if( m_pPackItem[i].itembaseinfo.ustItemID == InvalidLogicNumber)
        { continue; }

        if ( m_pPackItem[i].itembaseinfo.nOnlyInt <= 0 )
        {
           // _pGamePlayer->Log( "上线背包中有错误的物品 ID = [%u], GUID = [%I64u]", m_pPackItem[i].itembaseinfo.ustItemID, 0 );
			_pGamePlayer->Log( theXmlString.GetString(eServerLog_OnLineHaveErrorItemInBag), m_pPackItem[i].itembaseinfo.ustItemID, 0 );
            continue;
        }

        bool bResult = m_mapPackItem.insert( ItemContainer::value_type(m_pPackItem[i].itembaseinfo.nOnlyInt, &m_pPackItem[i]) ).second;
        if ( !bResult )
        {
           // _pGamePlayer->Log( "CreateFromData 背包物品[%I64u][%d] 重复出现", m_pPackItem[i].itembaseinfo.nOnlyInt, m_pPackItem[i].itembaseinfo.ustItemID );
			 _pGamePlayer->Log( theXmlString.GetString(eServerLog_CreateFromDataItemDuoCiChuXian), m_pPackItem[i].itembaseinfo.nOnlyInt, m_pPackItem[i].itembaseinfo.ustItemID );

           // _pGamePlayer->CheckCheatLog( "CreateFromData 背包物品[%I64u][%d] 重复出现", m_pPackItem[i].itembaseinfo.nOnlyInt, m_pPackItem[i].itembaseinfo.ustItemID );
			 _pGamePlayer->CheckCheatLog( theXmlString.GetString(eServerLog_CreateFromDataItemDuoCiChuXian), m_pPackItem[i].itembaseinfo.nOnlyInt, m_pPackItem[i].itembaseinfo.ustItemID );
        }
    }

    if ( m_bEnables )
    {
        delete[] m_bEnables;
    }

    m_bEnables = new bool[iBagSize];
    for( int n=0; n<iBagSize; ++n )
    { m_bEnables[n] = true; }

    return true;
} 

bool ItemBag::CleanUp()
{
    ItemSortContainer items;
    for(int i=0; i<m_iBagSize; ++i)
    {
        if( m_pPackItem[i].itembaseinfo.ustItemID == InvalidLogicNumber || m_pPackItem[i].itembaseinfo.nOnlyInt == 0 )
            continue;

        items.push_back( m_pPackItem[i] );

        m_pPackItem[i].itembaseinfo.ustItemID = InvalidLogicNumber;
        m_pPackItem[i].itembaseinfo.nOnlyInt  = 0;
        m_pPackItem[i].bCanUse = false;
    }

    sort( items.begin(), items.end(), SortItemID);

    MsgUpdateBag msg;
    ItrItemSortContainer it    = items.begin();
    ItrItemSortContainer itEnd = items.end();
    for ( int i=0; i<m_iBagSize && it!=itEnd; ++it, ++i)
    {
        it->IsPassUnLockTime( true );   // 检查解锁时间
        it->IsOverdue( true );          // 检查是否过期

        m_pPackItem[i] = *it;
        m_pPackItem[i].itembaseinfo.stPacketIdx = i;
        msg.AddItem( m_pPackItem[i] );
    }
    msg.ucItemBagType = _nItemBagType;
    msg.stNum         = items.size();
    GettheServer().SendMsgToSingle( &msg, _pGamePlayer);    
    return true;
}

bool ItemBag::CanPopItem( SCharItem &item )
{
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
}

bool ItemBag::CanPushItem( SCharItem &item, bool& bUseNewGrid )
{
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
}

int ItemBag::PushItem( SCharItem& item, unsigned short& ustCount, short stIndex, int* pOffSet, bool* pbNew )
{   
    if( item.itembaseinfo.ustItemID == InvalidLogicNumber/*||ustCount <= 0*/ )
    { return ierr_erritemid; }

    ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( item.itembaseinfo.ustItemID );
    if ( !pItemDetail )
    { return ierr_erritemid; }

    if ( item.itembaseinfo.nOnlyInt <=0 )
    { return ierr_ErrorItemGuid; }

    if ( pbNew )
    { *pbNew = false; }

    int nResult = ierr_Success;

#ifndef GAME_CLIENT
    //CalcItemLeftUseTime( item );        // 计算装备的剩余使用时间
    //CalcItemUnLockLeftTime( item );     // 计算装备的解锁时间
#endif

    if ( pItemDetail->IsExclusive() )
    { // 独占的
        SCharItem stItem = item;
        stItem.itembaseinfo.ustItemCount = 1;
        for ( int n=0; n<item.itembaseinfo.ustItemCount; ++n )
        {
            nResult = PushExclusiveItem( stItem, stIndex, pOffSet, pbNew );
            if ( nResult != ierr_Success )
            {  break;  }
        }
    }
    else
    { // 非独占的
        nResult = PushNonExclusiveItem( item, stIndex, ustCount, pOffSet, pbNew);
    }
    return nResult;
}
int ItemBag::PopItemByGuID(__int64 GuID,unsigned short ustCount)
{
	 if ( !m_pPackItem||ustCount <= 0)
        return ierr_PackItemPointerNull;
	//删除指定唯一ID的物品数据
	int Index = GetItemIndexByGuid(GuID);
	if(Index == -1)
		return ierr_PackItemPointerNull;
	 SCharItem* pItem = GetItemByIndex(Index);
	 if(!pItem || pItem->GetItemGuid() != GuID || pItem->GetItemID() == InvalidLogicNumber || pItem->GetItemCount() <= 0)
		 return ierr_PackItemPointerNull;
	pItem->itembaseinfo.ustItemCount -= ustCount;
	if(pItem->itembaseinfo.ustItemCount <=0)
	{
		pItem->itembaseinfo.ustItemCount = 0;
		pItem->itembaseinfo.ustItemID = InvalidLogicNumber;
        m_mapPackItem.erase(GuID);
        pItem->itembaseinfo.nOnlyInt = 0;
	}
	return ierr_Success;
}
int ItemBag::PopItemByID( unsigned short ustItemId, unsigned short ustCount, __int64* pretGUID )
{
    if ( !m_pPackItem||ustCount <= 0)
        return ierr_PackItemPointerNull;

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

        //是否拥有这个物品
        if(m_mapPackItem.find(pItem->itembaseinfo.nOnlyInt) == m_mapPackItem.end())
        {
            break;
        }

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
            m_mapPackItem.erase(pItem->itembaseinfo.nOnlyInt);
            pItem->itembaseinfo.nOnlyInt = 0;
        }
    } while( nRemoveCount > 0 );

    if ( nRemoveCount == 0 )
    {
        if (n > -1)
        {
            SetBagIndex(n);
        }
        return ierr_Success;
    }
    else
    {
        return ierr_NotHaveTargetCountItem;
    }
    //ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( item.itembaseinfo.ustItemID );
    //if( item.itembaseinfo.ustItemID == ErrorUnsignedShortID )
    //    return  ierr_erritemid;
    //bool bLive = false;
    //if (pItemDetail)
    //{
    //    bLive = pItemDetail->IsExclusive();
    //}
    ////else
    ////    bLive = item.bIsExclusive;
    //if (bLive )
    //{
    //    if( PopExclusiveItem( item ))
    //        return ierr_Success;
    //}
    //else
    //{
    //    ustCount = item.itembaseinfo.ustItemCount;
    //    return PopNonExclusiveItem( item.itembaseinfo.ustItemID, ustCount );
    //}
    //return ierr_unknown;
}

int ItemBag::PopItem( short stIndex, unsigned short& ustCount )
{
    SCharItem item;
    if ( !GetItem( stIndex, &item ) )
        return ierr_ItemNotExist;

    ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( item.itembaseinfo.ustItemID );
    if ( !pItemDetail )
        return ierr_ItemNotExist;

    if( item.itembaseinfo.ustItemID == InvalidLogicNumber || item.itembaseinfo.nOnlyInt <= 0 )
        return ierr_ItemNotExist;

    if ( pItemDetail->IsExclusive() )
    {
        return PopExclusiveItemByIndex( stIndex );
    }
    else
    {
        return PopNonExclusiveItemByIndex( stIndex, ustCount );
    }
    return ierr_unknown;
}
//Luoz add 获取指定背包, 通过物品id
bool ItemBag::GetItemByItemID( int itemid, SCharItem *pItem )
{
    for( int iLoop = 0 ; iLoop < m_iBagSize ; iLoop ++ )
    {
        if( itemid == m_pPackItem[iLoop].itembaseinfo.ustItemID )
        {
            if(m_mapPackItem.find(m_pPackItem[iLoop].itembaseinfo.nOnlyInt) == m_mapPackItem.end())
            {
                return false;
            }
            memcpy( pItem, &m_pPackItem[iLoop], sizeof(SCharItem) );
            return true;
        }
    }
    return false;
}

SCharItem* ItemBag::GetItemByItemID( int nItemID )
{
    for( int iLoop = 0; iLoop < m_iBagSize; ++iLoop )
    {
        if( nItemID != m_pPackItem[iLoop].itembaseinfo.ustItemID )
        { continue; }

        if( m_mapPackItem.find( m_pPackItem[iLoop].itembaseinfo.nOnlyInt ) == m_mapPackItem.end() )
        { continue; }

        return &m_pPackItem[iLoop];
    }

    return NULL;
}

bool ItemBag::GetItemByOnlyBigId( __int64 n64Index, SCharItem *pItem )
{
    for( int iLoop = 0 ; iLoop < m_iBagSize ; ++ iLoop )
    {
        if ( m_pPackItem[iLoop].itembaseinfo.ustItemID == InvalidLogicNumber )
            continue;

        if( n64Index == m_pPackItem[iLoop].itembaseinfo.nOnlyInt )
        {
            ItrItemContainer it = m_mapPackItem.find(n64Index);
            if( it != m_mapPackItem.end())
            {
                if ( pItem )
                {
                    memcpy( pItem, &m_pPackItem[iLoop], sizeof(SCharItem) );
                }
                return true;
            }

            return false;
        }
    }
    return false;
}

SCharItem* ItemBag::GetItemByOnlyBigId( __int64 nGuid )
{
    for( int iLoop = 0 ; iLoop < m_iBagSize ; ++iLoop )
    {
        if ( m_pPackItem[iLoop].itembaseinfo.ustItemID == InvalidLogicNumber )
        { continue; }

        if( nGuid == m_pPackItem[iLoop].itembaseinfo.nOnlyInt )
        {
            ItrItemContainer it = m_mapPackItem.find( nGuid );
            if( it == m_mapPackItem.end() )
            { return NULL; }

            return &m_pPackItem[iLoop];
        }
    }

    return NULL;
}


bool ItemBag::PopItemByOnlyBigId( __int64 n64Index, unsigned short usCount , int& nIndex )
{
    for( int iLoop = 0 ; iLoop < m_iBagSize ; ++ iLoop )
    {
        if ( m_pPackItem[iLoop].itembaseinfo.ustItemID == InvalidLogicNumber )
            continue;

        if( n64Index == m_pPackItem[iLoop].itembaseinfo.nOnlyInt )
        {
            ItrItemContainer it = m_mapPackItem.find(n64Index);
            if( it != m_mapPackItem.end())
            {                
                nIndex = iLoop;
                return ( PopItem( iLoop, usCount ) == ierr_Success );
            }

            return false;
        }
    }
    return false;
}

bool ItemBag::GetItem( short stIndex,  SCharItem* pItem  )
{
    if( stIndex < 0 || stIndex >= m_iBagSize )
        return false;

    SCharItem* pItemArray = m_pPackItem;
    if( !pItemArray )
        return false;

    ItrItemContainer it = m_mapPackItem.find(pItemArray[stIndex].itembaseinfo.nOnlyInt);
    if( it == m_mapPackItem.end())
        return false;

    if ( pItemArray[stIndex].itembaseinfo.ustItemID == InvalidLogicNumber||pItemArray[stIndex].itembaseinfo.ustItemCount <= 0)
        return false;

    if ( pItem )
    {
        *pItem = pItemArray[stIndex];
    }
    return true;
}

bool ItemBag::ClearItem( short stIndex )
{
    if( stIndex < 0 || stIndex >= m_iBagSize )
        return false;

    m_pPackItem[stIndex].itembaseinfo.ustItemID = InvalidLogicNumber;
    m_pPackItem[stIndex].itembaseinfo.ustItemCount = 0;
    m_bEnables[stIndex] = true;
    m_mapPackItem.erase(m_pPackItem[stIndex].itembaseinfo.nOnlyInt);
    m_pPackItem[stIndex].itembaseinfo.nOnlyInt = 0;
    return true;
}

bool ItemBag::ClearItem( unsigned int stIndex ,int Count)
{
    if( stIndex < 0 || stIndex >= m_iBagSize || Count <= 0 )
    { return false; }

    if ( m_pPackItem[stIndex].itembaseinfo.ustItemCount < Count )
    { return false; }

    m_pPackItem[stIndex].itembaseinfo.ustItemCount -= Count;
    if( m_pPackItem[stIndex].itembaseinfo.ustItemCount == 0 )
    {    
        m_pPackItem[stIndex].itembaseinfo.ustItemID = InvalidLogicNumber;
        m_mapPackItem.erase( m_pPackItem[stIndex].itembaseinfo.nOnlyInt );
        m_pPackItem[stIndex].itembaseinfo.nOnlyInt  = 0;
    }

    return true;        
}

bool ItemBag::IsHaveItem( unsigned short stIndex, unsigned short* pItemId )
{ //获取指定背包,索引的状况
    SCharItem* pItem = m_pPackItem;

    if ( stIndex<0 || stIndex >= m_iBagSize )
        return false;

    ItrItemContainer it = m_mapPackItem.find(pItem[stIndex].itembaseinfo.nOnlyInt);
    if ( it == m_mapPackItem.end())
        return false;

    if ( pItem[stIndex].itembaseinfo.ustItemID==InvalidLogicNumber)
        return false;

    if ( pItemId )
    {
        *pItemId = pItem[stIndex].itembaseinfo.ustItemID;
    }

    return true;
}

int ItemBag::GetNullItemCount()
{
    int nCount = 0;
    for( int iLoop = 0 ; iLoop < m_iBagSize ; iLoop ++ )
    {
        if( InvalidLogicNumber == m_pPackItem[iLoop].itembaseinfo.ustItemID )
        { ++nCount;}
    }
    return nCount;
}

int ItemBag::FindNullItemOffset()
{
    for(int iLoop = 0 ; iLoop < m_iBagSize ; ++ iLoop )
    {
        if( InvalidLogicNumber == m_pPackItem[iLoop].itembaseinfo.ustItemID)
            return iLoop;
    }
    return -1;
}

int ItemBag::FindItemOffsetByID( unsigned short ustItemID,int iBeginPos )
{
    int iLoop;
    for( iLoop = iBeginPos ; iLoop < m_iBagSize ; iLoop ++ )
    {
        if( ustItemID == m_pPackItem[iLoop].itembaseinfo.ustItemID )
            return iLoop;
    }
    return -1;
}

//是否能放入(独占类)物品
bool ItemBag::CanPushExclusiveItem()
{
    if( -1 != FindNullItemOffset() )
        return true;
    return false;
}

int ItemBag::PushExclusiveItem( SCharItem &item, short stIndex, int *pOffSet, bool *pbNew )
{
    if (!m_pPackItem)
        return ierr_PackItemPointerNull;

    if (stIndex >= m_iBagSize)
        return ierr_IndexOutOfBagSize;

    ItrItemContainer it = m_mapPackItem.find(item.itembaseinfo.nOnlyInt);
    if( it != m_mapPackItem.end())
        return ierr_RepeatedBigId;

    SCharItem* pItem = m_pPackItem;

    int iOffset = stIndex;    
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
        return ierr_CanNotOverlap;

    SetBagIndex(iOffset);
    if( pOffSet )
    { (*pOffSet) = iOffset; }
    item.itembaseinfo.stPacketIdx = iOffset;

	*pItem = item;

    m_mapPackItem.insert( ItemContainer::value_type(item.itembaseinfo.nOnlyInt, &item) );

    return ierr_Success;
}

bool ItemBag::CanPopExclusiveItem( SCharItem& item )
{
    ItrItemContainer it = m_mapPackItem.find(item.itembaseinfo.nOnlyInt);
    if( it== m_mapPackItem.end())
        return false;

    SCharItem* pItem = m_pPackItem;

    for(int iLoop=0; iLoop<m_iBagSize; ++iLoop, ++pItem )
    {
        if( *pItem == item )
            return true;
    }
    return false;
}

////取出(独占类)物品
//bool ItemBag::PopExclusiveItem( SCharItem &item )
//{
//    SCharItem *pItem = m_pPackItem;
//
//    int iLoop;
//    for( iLoop=0; iLoop<m_iBagSize; iLoop++, pItem++ )
//    {
//        //        if( *pItem == item )
//        if ( pItem->itembaseinfo.ustItemID == item.itembaseinfo.ustItemID )
//        {
//            pItem->itembaseinfo.ustItemID = ErrorUnsignedShortID;
//            /*pItem->guid = GUID_NULL;*/
//            return true;
//        }
//    }
//    return false;
//}

int ItemBag::PopExclusiveItemByIndex( short stIndex )
{
    if (stIndex <0 || stIndex >= m_iBagSize )
        return ierr_IndexOutOfBagSize;

    if ( !m_pPackItem)
        return ierr_ItemNotExist;

    SCharItem *pItem = m_pPackItem;

    ItrItemContainer it = m_mapPackItem.find(pItem[stIndex].itembaseinfo.nOnlyInt);
    if( it == m_mapPackItem.end())
        return false;

    pItem[stIndex].itembaseinfo.ustItemID = InvalidLogicNumber;
    pItem[stIndex].bCanUse                = true;

    m_mapPackItem.erase(pItem[stIndex].itembaseinfo.nOnlyInt);
    pItem[stIndex].itembaseinfo.nOnlyInt  = 0;

    SetBagIndex(stIndex);
    return ierr_Success;
}

//是否能放入(非独占类)物品
bool ItemBag::CanPushNonExclusiveItem( unsigned short ustItemID, unsigned short ustCount, bool bBind, bool& bUseNewGrid )
{
    if( ustCount == 0 )
        return false;

    int iOffset = -1;
    for( int iLoop = 0 ; iLoop < m_iBagSize ; iLoop ++ )
    {
        if( ustItemID == m_pPackItem[iLoop].itembaseinfo.ustItemID && bBind == m_pPackItem[iLoop].IsBounded() )
        {
            SCharItem *pItem = m_pPackItem;
            pItem += iLoop;

            ItemDefine::SItemCommon* pCommon = theItemDetailConfig.GetItemByID(pItem->itembaseinfo.ustItemID); // 得到Item信息
            if ( NULL == pCommon )
            { return false; }

            if( pItem->itembaseinfo.ustItemCount + ustCount <= pCommon->nStackNum )
            {
                iOffset = iLoop; 
                break;
            }
        }
    }

    if( -1 == iOffset )
    {
        iOffset     = FindNullItemOffset();
        bUseNewGrid = true;
        if( -1 == iOffset )
            return false;    
    }

    bUseNewGrid = false;
    return true;
}

//放入(非独占类)物品
int ItemBag::PushNonExclusiveItem( SCharItem& item, short stIndex, int nCount, int *pOffSet, bool *pbNew )
{
    if ( nCount > item.itembaseinfo.ustItemCount )
    { return ierr_NotHaveTargetCountItem; }

    int nPushCount = item.itembaseinfo.ustItemCount;
    if ( nCount > 0 )
    { nPushCount = nCount; }

    if (stIndex >= m_iBagSize)
    { return ierr_IndexOutOfBagSize; }

    SCharItem* pItem = m_pPackItem;
    int iOffset = stIndex;
    if( iOffset < 0 )
    { // 无制定位置
        for( int iLoop=0; iLoop<m_iBagSize; ++iLoop )
        {    
            if( m_pPackItem[iLoop].itembaseinfo.ustItemID == item.itembaseinfo.ustItemID )
            { // 找相同的物品的地址
                if (m_pPackItem[iLoop].IsBounded() == item.IsBounded())
                {// 绑定与不绑定物品不能放一起
                    int nSum = m_pPackItem[iLoop].itembaseinfo.ustItemCount + nPushCount;
                    ItemDefine::SItemCommon* pCommon = theItemDetailConfig.GetItemByID( m_pPackItem[iLoop].itembaseinfo.ustItemID );
                    if ( NULL == pCommon )
                    { continue; }

                    if ( nSum <= pCommon->nStackNum )
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
    { return ierr_PackIsFull; }

    pItem += iOffset;

    if ( pOffSet )
    { *pOffSet = iOffset; }

    item.itembaseinfo.stPacketIdx = iOffset;

    if( pItem->itembaseinfo.ustItemID == InvalidLogicNumber )
    { // 空的位置放新物品
        *pItem = item;
        pItem->itembaseinfo.ustItemCount = nPushCount;
        SetBagIndex(iOffset);

        m_mapPackItem.insert( ItemContainer::value_type(pItem->itembaseinfo.nOnlyInt, pItem) );
        return ierr_Success;
    }
    else
    { // 位置上有东西 
        // 判断是否是一类
        if( pItem->itembaseinfo.ustItemID != item.itembaseinfo.ustItemID )
        { return ierr_CanNotOverlap; }
    }

    //相同物品处理
    //包裹里有物品是否加锁则找空位置填充没有则叠加一起
    if(pItem->IsLock())
    { // 包裹里物品加锁 则找空位置填充
        SCharItem* pLockItem = m_pPackItem;
        int nOffset = FindNullItemOffset();
        if(nOffset == -1)
        { return ierr_ItemIsLocked; }

        pLockItem += nOffset;

        if( pLockItem->itembaseinfo.ustItemID == InvalidLogicNumber )
        { // 空的位置放新物品
            *pLockItem = item;
            pLockItem->itembaseinfo.ustItemCount = nPushCount;
            SetBagIndex(iOffset);

            m_mapPackItem.insert( ItemContainer::value_type(pLockItem->itembaseinfo.nOnlyInt, pLockItem) );
            return ierr_Success;
        }
    }
    else
    { // 包裹里物品没有加锁 则叠加一起        
        int nSum = pItem->itembaseinfo.ustItemCount + nPushCount;
        ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
        if ( NULL == pCommon )  // 如果得到的物品不存在
        { return ierr_ItemNotExist; }

        if ( nSum <= pCommon->nStackNum )
        { // 是否在最大数量内
            pItem->itembaseinfo.ustItemCount += nPushCount;
        }
        else
        {
            SCharItem* pItem2 = m_pPackItem;
            iOffset = FindNullItemOffset();            
            if ( iOffset == -1)
                return ierr_PackIsFull;

            pItem2 += iOffset;

            if( pItem2->itembaseinfo.ustItemID == InvalidLogicNumber )
            {
                *pItem2 = item;
                pItem2->itembaseinfo.ustItemCount = nPushCount;
                SetBagIndex(iOffset);
                m_mapPackItem.insert( ItemContainer::value_type(pItem2->itembaseinfo.nOnlyInt, pItem) );
                return ierr_Success;
            }
        }    
    }

    SetBagIndex(iOffset);
    return ierr_Success;
}

//是否能取出(非独占类)物品
bool ItemBag::CanPopNonExclusiveItem( unsigned short ustItemID, unsigned short ustCount )
{
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
}

int ItemBag::PopNonExclusiveItemByIndex( short stIndex, unsigned short &ustCount )
{
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
        pItem->bCanUse = true;
        m_mapPackItem.erase(pItem->itembaseinfo.nOnlyInt);
        pItem->itembaseinfo.nOnlyInt = 0;

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
        pItem->bCanUse = true;
        m_mapPackItem.erase(pItem->itembaseinfo.nOnlyInt);
        pItem->itembaseinfo.nOnlyInt  = 0;
    }
    SetBagIndex(stIndex);
    return ierr_Success;
}

bool ItemBag::IsHaveItemById( int itemID )
{
    for( int i = 0 ; i < m_iBagSize ; i ++ )
    {
        if( itemID == m_pPackItem[i].itembaseinfo.ustItemID && m_pPackItem[i].itembaseinfo.ustItemCount > 0 )
        {
            ItrItemContainer it = m_mapPackItem.find(m_pPackItem[i].itembaseinfo.nOnlyInt);
            if( it!= m_mapPackItem.end())
                return true;
        }
    }
    return false;
}

__int64 ItemBag::GetNewItemID()
{   
    static const int nCount = 3;
    for ( int i = 0; i < nCount; ++i )
    {
        __int64 nBigId = HelperFunc::CreateID();
        if ( !GetItemByOnlyBigId( nBigId, NULL ) )
        {
            return nBigId;
        }
    }
    return 0;
}

__int64 ItemBag::GetNewItemID( __int64 nGuid )
{
    static const int nCount = 3;
    for ( int i= 0; i < nCount; ++i )
    {
        __int64 nBigId = nGuid + 1;
        if ( !GetItemByOnlyBigId( nBigId, NULL ) )
        { return nBigId; }
    }

    return 0;
}


int ItemBag::GetItemCount()
{
    SCharItem* pItem = m_pPackItem;

    int nCount = 0;
    for (int n=0; n<m_iBagSize; n++ )
    {
        if ( pItem[n].itembaseinfo.ustItemID != InvalidLogicNumber )
            nCount++;
    }
    return nCount;
}

int ItemBag::GetItemEmptyCount()
{
    return m_iBagSize - GetItemCount();
}

int ItemBag::GetItemCount( int iItemID )
{
    int iItemCount = 0;

    ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( iItemID );
    if( !pItemDetail )
        return 0;

    for( int i = 0 ; i<m_iBagSize ; ++i)
    {
        if( iItemID == m_pPackItem[i].itembaseinfo.ustItemID )
        {   
            iItemCount += m_pPackItem[i].itembaseinfo.ustItemCount;
        }
    }
    return iItemCount;
}

SCharItem* ItemBag::GetItemByIndex( int nIdx )
{   
    if( nIdx < 0 || nIdx >= GetNowBagSize() )
        return NULL;

    SCharItem* pItemArray = m_pPackItem;
    if( !pItemArray )
        return NULL;

    ItrItemContainer it = m_mapPackItem.find(pItemArray[nIdx].itembaseinfo.nOnlyInt);
    if( it == m_mapPackItem.end())
        return NULL;

    if ( pItemArray[nIdx].itembaseinfo.ustItemID == InvalidLogicNumber)
        return NULL;

    return &m_pPackItem[nIdx];
}

int ItemBag::GetItemIndex( SCharItem *pItem )
{
    if ( !pItem )
    {
        // ToLog( pItem );
        return -1;
    }
    for( int i = 0 ; i < m_iBagSize ; i ++ )
    {
        //if( m_pPackItem[i] == *pItem )
        //    return i;
        if( m_pPackItem[i].Included( *pItem ) )
            return i;
    }
    return -1;
}

int ItemBag::GetItemIndexById( int nId )
{
    for( int i = 0 ; i < m_iBagSize ; i ++ )
    {
        if( m_pPackItem[i].itembaseinfo.ustItemID == nId )
            return i;
    }
    return -1;
}

int ItemBag::GetItemIndexByGuid( __int64 n64Guid )
{
    for( int i = 0 ; i < m_iBagSize; ++i )
    {
        if( m_pPackItem[i].itembaseinfo.nOnlyInt == n64Guid )
            return i;
    }
    return -1;
}

//int ItemBag::DestoryItem( SCharItem* pSrc)
//{
//    if( !pSrc )
//    {
//        // ToLog(false);
//        return -1;
//    }
//    if( pSrc->itembaseinfo.ustItemID == ErrorUnsignedShortID )
//    { //拖动肯定保证有物品
//        return -1;
//    }
//    
//    //ItemDefine::SItemCommon *pSrcItemDetail = GettheItemDetail().GetItemByID( pSrc->itembaseinfo.ustItemID );
//    
//    pSrc->itembaseinfo.ustItemID = ErrorUnsignedShortID;
//
//}

int ItemBag::MoveItem( SCharItem* pDst, EBagType DstType, SCharItem* pSrc, EBagType SrcType, ItemBag* pBag, int nCount)
{
    if ( !pDst || !pSrc || !pBag||nCount==0 )
        return ECD_MoveGood_Error;

    if ( pSrc->itembaseinfo.ustItemID == InvalidLogicNumber || pSrc->itembaseinfo.nOnlyInt <= 0 ) 
        return ECD_MoveGood_Error;

    ItemDefine::SItemCommon* pSrcItemDetail = GettheItemDetail().GetItemByID( pSrc->itembaseinfo.ustItemID );
    if (!pSrcItemDetail)
        return ECD_MoveGood_Error;

    bool bCheckPop  = false;
    bool bCheckPush = false;
    if(pBag != NULL && DstType != SrcType)
    {
        // 将物品放进包裹
        if(DstType == BT_NormalItemBag || DstType == BT_MaterialBag || DstType == BT_TaskBag  )
            bCheckPush = true;

        // 将物品拿出包裹
        if(SrcType == BT_NormalItemBag || SrcType == BT_MaterialBag || SrcType == BT_TaskBag )
            bCheckPop = true;
    }

    //if ( pSrcItemDetail->ucItemType == ItemDefine::ITEMTYPE_MATERIAL )
    //{
    //    ItemDefine::SCreateMaterial* pMaterial = (ItemDefine::SCreateMaterial*)pSrcItemDetail;
    //    switch(pMaterial->stMaterialType)
    //    {
    //    case CItemDetail::ematerial_metal:
    //    case CItemDetail::ematerial_pelage:
    //    case CItemDetail::ematerial_wood:
    //    case CItemDetail::ematerial_uplevel:
    //    case CItemDetail::ematerial_compound:
    //        {
    //            int iCount = MoveMaterial(pDst, DstType, pSrc, SrcType, pBag, nCount);
    //            return iCount;
    //        }
    //        break;
    //    }
    //}

    // 判断是否独占
    //bool bExclusive = false;
    //if ( pSrcItemDetail->IsExclusive() )
    //{
    //    bExclusive = true;
    //}
    //else
    //{
    //    // 特殊物品之类
    //}

    if ( pSrcItemDetail->IsExclusive() )
    { // 是独占的物品
        if ( nCount != -1 && nCount != 1 )
            return ECD_MoveGood_Error;

        if ( pDst->itembaseinfo.ustItemID == InvalidLogicNumber)
        {
            if(bCheckPop)
            {
                if( pBag->m_mapPackItem.find(pSrc->itembaseinfo.nOnlyInt) == pBag->m_mapPackItem.end() )
                { // 没有这个物品
                    return ECD_MoveGood_Error;
                }
                else
                {
                    pBag->m_mapPackItem.erase(pSrc->itembaseinfo.nOnlyInt);
                }
            }

            if(bCheckPush)
            {
                if( pBag->m_mapPackItem.find(pSrc->itembaseinfo.nOnlyInt) != pBag->m_mapPackItem.end() )
                {
                    //ID重复了                    
                    return ECD_MoveGood_Error;
                }
            }

            *pDst = *pSrc;
            pSrc->itembaseinfo.ustItemID = InvalidLogicNumber;
            pSrc->itembaseinfo.nOnlyInt = 0;
            pSrc->bCanUse = false;

            if( bCheckPush )
            {
                pBag->m_mapPackItem.insert( std::pair<__int64, SCharItem*>(pDst->itembaseinfo.nOnlyInt, pDst) );
            }

            return ECD_MoveGood_Move;
        }
        else
        {
            // SCharItem* pCharItem = NULL;
            // pCharItem = pSrc;
            // pSrc = pDst;
            // pDst = pCharItem;
            // return 1;
            return ECD_MoveGood_Error;
        }
    }
    else
    { // 不是独占的物品
        if ( nCount == -1 )
        {
            nCount = pSrc->itembaseinfo.ustItemCount;
        }
        else if ( nCount > pSrc->itembaseinfo.ustItemCount || nCount > pSrcItemDetail->nStackNum )  // 使用最大堆叠数来判断
        {
            return ECD_MoveGood_Error;
        }

        if ( pDst->itembaseinfo.ustItemID == InvalidLogicNumber )
        {
            if ( pSrc->itembaseinfo.ustItemCount < nCount || nCount > pSrcItemDetail->nStackNum )
            {
                return ECD_MoveGood_Error;
            }

            if ( pSrc->itembaseinfo.ustItemCount > nCount && pSrc->IsLock() )
            {
                return ECD_MoveGood_Error;
            }

            if(bCheckPop)
            {
                if( pBag->m_mapPackItem.find(pSrc->itembaseinfo.nOnlyInt) == pBag->m_mapPackItem.end() )
                {
                    //没有这个物品
                    return ECD_MoveGood_Error;
                }
            }

            if(bCheckPush)
            {
                if( pBag->m_mapPackItem.find(pSrc->itembaseinfo.nOnlyInt) != pBag->m_mapPackItem.end() )
                {
                    //包裹中已经有这个唯一ID，但是目标格子并不是这个ID
                    return ECD_MoveGood_Error;
                }
            }

            pDst->itembaseinfo.ustItemID = pSrc->itembaseinfo.ustItemID;
            *pDst = *pSrc;
            pDst->itembaseinfo.ustItemCount = nCount;
            pSrc->itembaseinfo.ustItemCount -= nCount;

            if (pDst->IsBounded() || pSrc->IsBounded())
            { pDst->SetBounded( true ); }

            if ( pSrc->itembaseinfo.ustItemCount == 0 )
            {
                pSrc->itembaseinfo.ustItemID = InvalidLogicNumber;
                pSrc->itembaseinfo.nOnlyInt  = 0;

                if(bCheckPop)
                {
                    pBag->m_mapPackItem.erase(pSrc->itembaseinfo.nOnlyInt);
                }
                if(bCheckPush)
                {
                    pBag->m_mapPackItem.insert( std::pair<__int64, SCharItem*>(pDst->itembaseinfo.nOnlyInt, pDst) );
                }
                /*pSrc->guid = GUID_NULL;*/
            }
            else
            {
                __int64 n64Guid = pBag->GetNewItemID();     // 创建一个新的guid
                if ( n64Guid == 0 )
                { return ECD_MoveGood_Error; }

                pDst->itembaseinfo.nOnlyInt = n64Guid;

                // 移动蚩尤之血等物品，要更新道具值
                if ( pSrcItemDetail->ucItemType == ItemDefine::ITEMTYPE_RESTORE && !pSrcItemDetail->IsExclusive() )
                {
                    ItemDefine::SItemRestore* itemRestore = (ItemDefine::SItemRestore*)pSrcItemDetail;
                    if ( itemRestore->bHPAuto )
                        pSrc->itembaseinfo.value2 = itemRestore->dwAddHP;
                    else if ( itemRestore->bMPAuto )
                        pSrc->itembaseinfo.value2 = itemRestore->dwAddMP;
                }

                if( DstType == BT_NormalItemBag || DstType == BT_MaterialBag || DstType == BT_TaskBag )
                {
                    pBag->m_mapPackItem.insert( std::pair<__int64, SCharItem*>(pDst->itembaseinfo.nOnlyInt, pDst) );
                }

                return ECD_MoveGood_Split;
            }
            return ECD_MoveGood_Move;
        }
        else if ( pDst->itembaseinfo.ustItemID == pSrc->itembaseinfo.ustItemID )
        {
            if ( pDst->IsLock()||pSrc->IsLock() )
            { return ECD_MoveGood_Error; }

            if ( nCount > pSrcItemDetail->nStackNum - pDst->itembaseinfo.ustItemCount )
            { nCount = pSrcItemDetail->nStackNum - pDst->itembaseinfo.ustItemCount; }

            if(bCheckPop)
            {
                //没有这个物品
                if( pBag->m_mapPackItem.find(pSrc->itembaseinfo.nOnlyInt) == pBag->m_mapPackItem.end() )
                { return ECD_MoveGood_Error; }
            }

            if(bCheckPush)
            {
                //包裹中已经有这个唯一ID，但是目标格子并不是这个ID
                if( pBag->m_mapPackItem.find(pSrc->itembaseinfo.nOnlyInt) != pBag->m_mapPackItem.end() &&
                    pSrc->itembaseinfo.nOnlyInt != pDst->itembaseinfo.nOnlyInt)
                { return ECD_MoveGood_Error; }
            }

            pDst->itembaseinfo.ustItemCount += nCount;
            pSrc->itembaseinfo.ustItemCount -= nCount;

            if (pDst->IsBounded() || pSrc->IsBounded())
            { pDst->SetBounded( true ); }

            // 移动蚩尤之血等物品，要更新道具值
            if ( pSrcItemDetail->ucItemType == ItemDefine::ITEMTYPE_RESTORE && !pSrcItemDetail->IsExclusive() )
            {
                ItemDefine::SItemRestore* itemRestore = (ItemDefine::SItemRestore*)pSrcItemDetail;
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
                pSrc->itembaseinfo.nOnlyInt  = 0;
                if(bCheckPop)
                {
                    pBag->m_mapPackItem.erase(pSrc->itembaseinfo.nOnlyInt);
                }
                /*pSrc->guid = GUID_NULL;*/
            }

            return ECD_MoveGood_Move;
        }
        else
        { return ECD_MoveGood_Error; }
    }
}

//int ItemBag::MoveMaterial(SCharItem* pDst, EBagType DstType, SCharItem* pSrc, EBagType SrcType, ItemBag* pBag, int nCount )
//{
//    if ( !pDst || !pSrc ||nCount <= 0)
//    {
//        // ToLog(false);
//        return -1;
//    }
//
//    bool bCheckPop  = false;
//    bool bCheckPush = false;
//    if(pBag != NULL && DstType != SrcType)
//    {
//        //将物品放进包裹
//
//        if(DstType == BT_NormalItemBag || SrcType == BT_MaterialBag || SrcType == BT_TaskBag)
//        {
//            bCheckPush = true;
//        }
//
//        //将物品拿出包裹
//        if(SrcType == BT_NormalItemBag || SrcType == BT_MaterialBag || SrcType == BT_TaskBag )
//        {
//            bCheckPop = true;
//        }
//    }
//
//    if ( pSrc->itembaseinfo.ustItemID == InvalidLogicNumber/*&&pSrc->guid == GUID_NULL*/)
//    {
//        return -1;
//    }
//    ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pSrc->itembaseinfo.ustItemID );
//
//    if ( pDst->itembaseinfo.ustItemID == InvalidLogicNumber )
//    {
//        if(bCheckPop)
//        {
//            if( pBag->m_mapPackItem.find(pSrc->itembaseinfo.nOnlyInt) == pBag->m_mapPackItem.end() )
//            {
//                //没有这个物品
//                return -1;
//            }
//        }
//
//        if(bCheckPush)
//        {
//            if( pBag->m_mapPackItem.find(pSrc->itembaseinfo.nOnlyInt) != pBag->m_mapPackItem.end() )
//            {
//                //包裹中已经有这个唯一ID，但是目标格子并不是这个ID
//                return -1;
//            }
//        }
//
//        pDst->itembaseinfo.ustItemID = pSrc->itembaseinfo.ustItemID;
//        *pDst = *pSrc;
//        pDst->itembaseinfo.ustItemCount = nCount;
//        pSrc->itembaseinfo.ustItemCount -= nCount;
//        if ( pSrc->itembaseinfo.ustItemCount == 0 )
//        {
//            pSrc->itembaseinfo.ustItemID = InvalidLogicNumber;
//            pSrc->itembaseinfo.nOnlyInt  = 0;
//            if(bCheckPop)
//            {
//                pBag->m_mapPackItem.erase(pSrc->itembaseinfo.nOnlyInt);
//            }
//            /*pSrc->guid = GUID_NULL;*/
//        }
//        return nCount;
//    }
//
//    else if ( pDst->itembaseinfo.ustItemID == pSrc->itembaseinfo.ustItemID )
//    {
//        SCharItem theItem;
//
//        if(bCheckPop)
//        {
//            if( pBag->m_mapPackItem.find(pSrc->itembaseinfo.nOnlyInt) == pBag->m_mapPackItem.end() )
//            {
//                //没有这个物品
//                return -1;
//            }
//        }
//
//        if(bCheckPush)
//        {
//            if( pBag->m_mapPackItem.find(pSrc->itembaseinfo.nOnlyInt) != pBag->m_mapPackItem.end() &&
//                pSrc->itembaseinfo.nOnlyInt != pDst->itembaseinfo.nOnlyInt)
//            {
//                //包裹中已经有这个唯一ID，但是目标格子并不是这个ID
//                return -1;
//            }
//        }
//
//        //int nSum = pDst->itembaseinfo.ustItemCount + nCount;
//        /*float fAllMaterialBulk = (pDst->itembaseinfo.fBulk)*(pDst->itembaseinfo.ustItemCount) + nCount*(pSrc->itembaseinfo.fBulk);
//        float fpDstMod = (pDst->itembaseinfo.fBulk)/fAllMaterialBulk;
//        float fpSrcMod = (pSrc->itembaseinfo.fBulk)/fAllMaterialBulk;
//
//        float fAllMaterialRigidity = (pDst->itembaseinfo.fRigidity)*fpDstMod*(pDst->itembaseinfo.ustItemCount)+(pSrc->itembaseinfo.fRigidity)*fpSrcMod*nCount;
//        float fAllMaterialIntensity = (pDst->itembaseinfo.fIntensity)*fpDstMod*(pDst->itembaseinfo.ustItemCount)+(pSrc->itembaseinfo.fIntensity)*fpSrcMod*nCount;
//        float fAllMaterialToughness = (pDst->itembaseinfo.fToughness)*fpDstMod*(pDst->itembaseinfo.ustItemCount)+(pSrc->itembaseinfo.fToughness)*fpSrcMod*nCount;
//        float fAllMaterialWeight = (pDst->itembaseinfo.fWeight)*(pDst->itembaseinfo.ustItemCount)+nCount*(pSrc->itembaseinfo.fWeight);
//        float fAllMaterialDensity = (pDst->itembaseinfo.fDensity)*(pDst->itembaseinfo.ustItemCount) + nCount*(pSrc->itembaseinfo.fDensity);        
//
//        memcpy(&theItem,pSrc,sizeof(SCharItem));
//
//        theItem.itembaseinfo.fBulk = fAllMaterialBulk/nSum;
//        theItem.itembaseinfo.fDensity = fAllMaterialDensity/nSum;
//        theItem.itembaseinfo.fIntensity = fAllMaterialIntensity/nSum;
//        theItem.itembaseinfo.fRigidity = fAllMaterialRigidity/nSum;
//        theItem.itembaseinfo.fToughness = fAllMaterialToughness/nSum;
//        theItem.itembaseinfo.fWeight = fAllMaterialWeight/nSum;*/
//        //theItem.itembaseinfo.ustItemCount = nSum;
//
//        //memcpy(pDst,&theItem,sizeof(SCharItem));
//
//        pDst->itembaseinfo.ustItemCount += nCount;
//        pSrc->itembaseinfo.ustItemCount -= nCount;
//
//        if ( pSrc->itembaseinfo.ustItemCount == 0 )
//        {
//            pSrc->itembaseinfo.ustItemID = InvalidLogicNumber;
//            pSrc->itembaseinfo.nOnlyInt  = 0;
//            if(bCheckPop)
//            {
//                pBag->m_mapPackItem.erase(pSrc->itembaseinfo.nOnlyInt);
//            }
//        }
//
//        return pDst->itembaseinfo.ustItemCount;
//    }
//    else
//        return -1;
//}
/*
@ stindex : 物品索引
@ bLocked : 物品加锁开关
*/
bool ItemBag::SetItemProperty( short stIndex,bool bLocked )
{
    if ( stIndex <0 || stIndex >= m_iBagSize )
    { return false; }

    m_pPackItem[stIndex].SetLock( bLocked );
    return true;
}

bool ItemBag::ExchangeItem( SCharItem* pDst, SCharItem* pSrc )
{
    if ( !pDst || !pSrc )
        return false;

    SCharItem temp;
    temp = *pDst;
    *pDst = *pSrc;
    *pSrc = temp;
    return true;
}

bool ItemBag::RemoveItemByID( unsigned short nItemId, unsigned short nCount, __int64* pretGUID /*= NULL*/ )
{
    if( PopItemByID( nItemId, nCount, pretGUID ) == ierr_Success )
    {
        MsgRemoveItem msg;
        msg.ucItemBagType = _nItemBagType;
        msg.ustItemID     = nItemId;
        msg.ustCount      = nCount;
        GettheServer().SendMsgToSingle( &msg, _pGamePlayer );
        return true;
    }

    return false;
}
bool ItemBag::RemoveItemByGuID(__int64 GuID,unsigned short nCount)
{
	//根据唯一ID 移除物品
	if( PopItemByGuID( GuID, nCount ) == ierr_Success )
    {
        MsgRemoveItemByGuID msg;
        msg.ucItemBagType = _nItemBagType;
        msg.GuID		  = GuID;
        msg.ustCount      = nCount;
        GettheServer().SendMsgToSingle( &msg, _pGamePlayer );
        return true;
    }
    return false;
}
void ItemBag::CheckItemBag()
{
    for(int i=0;i<m_iBagSize;i++)
    {
        if(m_mapPackItem.find(m_pPackItem[i].itembaseinfo.nOnlyInt) == m_mapPackItem.end())
        {
            m_pPackItem[i].itembaseinfo.ustItemID = InvalidLogicNumber; 
            m_pPackItem[i].itembaseinfo.nOnlyInt  = 0;
            m_pPackItem[i].itembaseinfo.ustItemCount = 0;
        }
    }  
}
