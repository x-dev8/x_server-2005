#ifndef __STALLMANAGERR_H__
#define __STALLMANAGERR_H__

/************************************************************************
            ��̯����, ��ǰ��ά��, ����Ū��
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

    // ��ʼ��
    void InitStall( T* pPlayer );

    // ���һ��������Ʒ��̯λ
    void AddStallData( unsigned int nIndex, const StallData& xData );

    // ��ð�̯��Ʒ����
    int GetStallDataCount() const;

    // ���һ��̯λ��Ʒ
    void RemoveStallData( unsigned int nIndex );
    void RemoveStallData( StallData* pData );

    // ������а�̯����
    void ClearAllStallData();

    // ���һ����̯��Ʒ
    StallData* GetStallData( unsigned int nIndex );

    // �ƶ�һ����̯��Ʒ
    bool MoveStallData( unsigned int nSrcIndex, unsigned int nDestIndex );

    // ���̯λ������
    bool CheckStallDataValid();  

    // ����̯��Ʒ�Ƿ���ȷ
    bool CheckStallDataValid( unsigned char uchIndex, StallData* pData );

    // ����Ƿ��Ѿ��ڰ�̯������
    bool CheckStallDataValid( unsigned char uchBagType, __int64 n64Guid );

    // ��ð�̯�����ܻ�õ�����Ǯ
    unsigned int GetStallDataTotalSellMoney();

    // ��ð�̯�չ���Ҫ������Ǯ
    unsigned int GetStallDataTotalBuyMoney();

    // ��ʾ̯λ��Ϣ�����
    void ShowStallDataToPlayer( T* pPlayer );

    // ����չ�ʱ, �����ռ��Ƿ��㹻
    bool CheckStallBuyBagCount( unsigned int nNormalCount, unsigned int nMaterialCount, unsigned int nMountCount, unsigned int nPetCount );

protected:
    // ��Ӱ�̯��Ʒ����
    void AddStallDataCount();
    
    // ���ٰ�̯��Ʒ����
    void SubStallDataCount();

private:
    T* m_pStaller;                                          // ̯��                             
    int m_nStallDataCount;                                  // ��̯����
    StallData m_xStallData[ StallDefine::MaxStallCount ];   // ̯λ��Ϣ
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
    
    // ��ͬλ�ò���Ҫ�ƶ�
    if ( nSrcIndex == nDestIndex )
    { return false; }

    // ���� �� �չ� ������һ�� , ��������
    if ( nSrcIndex < StallDefine::MaxSellCount && nDestIndex >= StallDefine::MaxSellCount )
    { return false; }
    if ( nSrcIndex >= StallDefine::MaxSellCount && nDestIndex < StallDefine::MaxSellCount )
    { return false; }

    StallData xData = m_xStallData[ nDestIndex ];
    m_xStallData[ nDestIndex ] = m_xStallData[ nSrcIndex ];
    m_xStallData[ nSrcIndex ]  = xData;

    return true;
}

template< class T >     // û����Ʒ��, ����false
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
    { return true; } // �չ��Ĳ��ü��

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