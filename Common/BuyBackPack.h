#ifndef __BUYBACKPACK_H__
#define __BUYBACKPACK_H__

/************************************************************************
                     回购包裹逻辑     
                     Filename:    BuyBackPack.h
                     MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include <list>

template< class T >
class BuyBackPack
{
protected:
    typedef std::list< T > PackList;
    typedef typename PackList::iterator PackListIter; 

    enum BuyBackPackDefine
    {
        MaxPackSize = 10,
    };

public:
    BuyBackPack()
    {
        m_listPack.clear();
    }

    unsigned char GetMaxPackSize() { return static_cast< unsigned char >( m_listPack.size() ); }

    bool AddItem( T& xItem );
    bool RemoveItemByIndex( unsigned char uchIndex );
    T* GetItemByIndex( unsigned char uchIndex );

    void InitPack( T* pItem, int nCount );
    void GetPack( T* pItem, int &nCount, int nMaxCount );

    void ClearPack();

private:
    PackList m_listPack;                   // 背包数组
};

template< class T >
bool BuyBackPack< T >::AddItem( T& xItem )
{
    if ( xItem.IsEmpty() )
    { return false; }

    if ( m_listPack.size() == MaxPackSize )
    {
        m_listPack.pop_front();
    }

    m_listPack.push_back( xItem );
    return true;
}

template< class T >
bool BuyBackPack< T >::RemoveItemByIndex( unsigned char uchIndex )
{
    if ( uchIndex >= GetMaxPackSize() )
    { return false; }

    PackListIter iter = m_listPack.begin();
    advance( iter, uchIndex );

    m_listPack.erase( iter );
    return true;
}


template< class T >
T* BuyBackPack< T >::GetItemByIndex( unsigned char uchIndex )
{
    if ( uchIndex >= GetMaxPackSize() )
    { return NULL; }

    PackListIter iter = m_listPack.begin();
    advance( iter, uchIndex );
        
    return &( *iter );
}

template< class T >
void BuyBackPack< T >::InitPack( T* pItem, int nCount )
{
    ClearPack();        // 先清空

    if ( pItem == NULL || nCount == 0 )
    { return; }

    if ( nCount > MaxPackSize )
        nCount = MaxPackSize;

    for ( int i = 0; i < nCount; ++i )
    {
        AddItem( pItem[ i ] );
    }
}

template< class T >
void BuyBackPack< T >::GetPack( T* pItem, int &nCount, int nMaxCount )
{
    nCount = 0;
    if ( pItem == NULL || nMaxCount == 0 )
    { return; }

    for ( int i = 0; i < nMaxCount; ++i )
    {
        pItem[i].Clear();
    }

    for ( PackListIter iter = m_listPack.begin(); iter != m_listPack.end() && nCount < nMaxCount; ++iter, ++nCount )
    {
        pItem[ nCount ] = *iter;
    }
}

template< class T >
inline void BuyBackPack< T >::ClearPack()
{ 
    m_listPack.clear(); 
}

#endif