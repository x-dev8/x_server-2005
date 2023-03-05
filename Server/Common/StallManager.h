#ifndef __STALLMANAGERR_H__
#define __STALLMANAGERR_H__

/************************************************************************
            摆摊管理, 以前难维护, 重新弄下
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "StallDefine.h"

template< class T >
class StallManger
{
public:
    StallManger() : m_nStallDataCount( 0 )
    { 
        m_pStaller = NULL;
    }

    // 初始化
    void InitStall( T* pPlayer );

    // 添加一个出售物品到摊位
    void AddStallData( unsigned int nIndex, const StallData& xData );

    // 获得摆摊物品个数
    int GetStallDataCount() const;

    // 清除一个摊位物品
    void RemoveStallData( unsigned int nIndex );
    void RemoveStallData( StallData* pData );

    // 清除所有摆摊数据
    void ClearAllStallData();

    // 获得一个摆摊物品
    StallData* GetStallData( unsigned int nIndex );

    // 移动一个摆摊物品
    bool MoveStallData( unsigned int nSrcIndex, unsigned int nDestIndex );

    // 检查摊位的数据
    bool CheckStallDataValid();  

    // 检查摆摊物品是否正确
    bool CheckStallDataValid( unsigned char uchIndex, StallData* pData );

    // 检查是否已经在摆摊栏中了
    bool CheckStallDataValid( unsigned char uchBagType, __int64 n64Guid );

    // 获得摆摊出售能获得的最大金钱
    unsigned int GetStallDataTotalSellMoney();

    // 获得摆摊收购需要的最大金钱
    unsigned int GetStallDataTotalBuyMoney();

    // 显示摊位信息给玩家
    void ShowStallDataToPlayer( T* pPlayer );

    // 检查收购时, 背包空间是否足够
    bool CheckStallBuyBagCount( unsigned int nNormalCount, unsigned int nMaterialCount, unsigned int nMountCount, unsigned int nPetCount );

protected:
    // 添加摆摊物品数量
    void AddStallDataCount();
    
    // 减少摆摊物品数量
    void SubStallDataCount();

private:
    T* m_pStaller;                                          // 摊主                             
    int m_nStallDataCount;                                  // 摆摊数量
    StallData m_xStallData[ StallDefine::MaxStallCount ];   // 摊位信息
};

template< class T >
inline void StallManger< T >::InitStall( T* pPlayer )
{
    m_pStaller        = pPlayer;
    m_nStallDataCount = 0;
}

template< class T >
inline void StallManger< T >::AddStallDataCount()
{
    ++m_nStallDataCount;
}

template< class T >
inline void StallManger< T >::SubStallDataCount()
{
    --m_nStallDataCount;
    if ( m_nStallDataCount< 0 )
    { m_nStallDataCount = 0; }
}

template< class T >
inline int StallManger< T >::GetStallDataCount() const
{
    return m_nStallDataCount;
}

template< class T >
inline void StallManger< T >::AddStallData( unsigned int nIndex, const StallData& xData )
{
    if ( nIndex >= StallDefine::MaxStallCount )
    { return; }

    m_xStallData[ nIndex ] = xData;
    
    AddStallDataCount();
}

template< class T >
inline void StallManger< T >::RemoveStallData( unsigned int nIndex )
{
    StallData* pData = GetStallData( nIndex );
    if ( pData == NULL )
    { return; }

    RemoveStallData( pData );
}

template< class T >
inline void StallManger< T >::RemoveStallData( StallData* pData )
{
    if ( pData == NULL )
    { return; }

    pData->ClearStall();
    SubStallDataCount();
}

template< class T >
inline void StallManger< T >::ClearAllStallData()
{
    for ( int i = 0; i < StallDefine::MaxStallCount; ++i )
    {
        m_xStallData[ i ].ClearStall();
    }

    m_nStallDataCount = 0;
}

template< class T >
inline StallData* StallManger< T >::GetStallData( unsigned int nIndex )
{
    if ( nIndex >= StallDefine::MaxStallCount )
    { return NULL; }

    return &( m_xStallData[ nIndex ] );
}

template< class T >
inline bool StallManger< T >::MoveStallData( unsigned int nSrcIndex, unsigned int nDestIndex )
{
    if ( nSrcIndex >= StallDefine::MaxStallCount || nDestIndex >= StallDefine::MaxStallCount )
    { return false; }
    
    // 相同位置不需要移动
    if ( nSrcIndex == nDestIndex )
    { return false; }

    // 出售 和 收购 不能在一起 , 分来管理
    if ( nSrcIndex < StallDefine::MaxSellCount && nDestIndex >= StallDefine::MaxSellCount )
    { return false; }
    if ( nSrcIndex >= StallDefine::MaxSellCount && nDestIndex < StallDefine::MaxSellCount )
    { return false; }

    StallData xData = m_xStallData[ nDestIndex ];
    m_xStallData[ nDestIndex ] = m_xStallData[ nSrcIndex ];
    m_xStallData[ nSrcIndex ]  = xData;

    return true;
}

template< class T >     // 没有物品了, 返回false
bool StallManger< T >::CheckStallDataValid()
{
    for ( int i = 0; i < StallDefine::MaxStallCount; ++i )
    {
        if ( m_xStallData[i].IsEmpty() )
        { continue; }
        
        if ( !CheckStallDataValid( i, &m_xStallData[i] ) )
        { SubStallDataCount(); }
    }

    return ( GetStallDataCount() > 0 );
}

template< class T >
bool StallManger< T >::CheckStallDataValid( unsigned char uchIndex, StallData* pData )
{
    if ( pData == NULL )
    { return false; }

    if ( pData->GetStallType() == StallDefine::StallBuy )
    { return true; } // 收购的不用检查

    switch ( pData->GetBagType() )
    {
    case BT_MaterialBag:
    case BT_NormalItemBag:
    case BT_MountBag:
    case BT_PetBag:
        return m_pStaller->CheckStallDataValid( uchIndex, pData );
        break;
    default:
        break;
    }

    return false;
}

template< class T >
bool StallManger< T >::CheckStallDataValid(  unsigned char uchBagType, __int64 n64Guid )
{
    for ( int i = 0; i < StallDefine::MaxStallCount; ++i )
    {
        if ( m_xStallData[i].IsEmpty() )
        { continue; }

        if ( m_xStallData[i].GetGuid() == n64Guid )
        { return false; }
    }

    return true;
}

template< class T >
unsigned int StallManger< T >::GetStallDataTotalSellMoney()
{
    unsigned int nTotalMoney = 0;
    for ( int i = 0; i < StallDefine::MaxStallCount; ++i )
    {
        if ( m_xStallData[i].IsEmpty() )
        { continue; }

        if ( m_xStallData[i].GetStallType() == StallDefine::StallBuy )
        { continue; }

        nTotalMoney += m_xStallData[i].GetGameMoneyPrice() * m_xStallData[i].GetCount();
    }

    return nTotalMoney;
}

template< class T >
unsigned int StallManger< T >::GetStallDataTotalBuyMoney()
{
    unsigned int nTotalMoney = 0;
    for ( int i = 0; i < StallDefine::MaxStallCount; ++i )
    {
        if ( m_xStallData[i].IsEmpty() )
        { continue; }

        if ( m_xStallData[i].GetStallType() == StallDefine::StallSell )
        { continue; }

        nTotalMoney += m_xStallData[i].GetGameMoneyPrice() * m_xStallData[i].GetCount();
    }

    return nTotalMoney;
}

template< class T >
bool StallManger< T >::CheckStallBuyBagCount( unsigned int nNormalCount, unsigned int nMaterialCount, unsigned int nMountCount, unsigned int nPetCount )
{
    unsigned int nStallNormalCount = 0;
    unsigned int nStallMaterialCount = 0;
    unsigned int nStallMountCount = 0;
    unsigned int nStallPetCount = 0;

    for ( int i = 0; i < StallDefine::MaxStallCount; ++i )
    {
        if ( m_xStallData[i].IsEmpty() )
        { continue; }

        if ( m_xStallData[i].GetStallType() == StallDefine::StallSell )
        { continue; }

        switch ( m_xStallData[i].GetBagType() )
        {
        case BT_NormalItemBag:
            ++nStallNormalCount;
            break;
        case BT_MaterialBag:
            ++nStallMaterialCount;
            break;
        case BT_MountBag:
            ++nStallMountCount;
            break;
        case BT_PetBag:
            ++nStallPetCount;
            break;
        default:
            break;
        }
    }

    return ( nNormalCount >= nStallNormalCount && nMaterialCount >= nStallMaterialCount && nMountCount >= nStallMountCount  && nPetCount >= nStallPetCount );
}

////////////////////////////////////////////////////////////////////
class GamePlayer;
typedef StallManger< GamePlayer > StallEx;
////////////////////////////////////////////////////////////////////
#endif