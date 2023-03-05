#ifndef __SERVERTITLEMANAGER_H__
#define __SERVERTITLEMANAGER_H__

/*********************************************************************************************
                    �ƺŹ�����( ������ʹ�� )
                    Filename:     TitleManager.h 
                    MaintenanceMan Mail: lori227@live.cn
*********************************************************************************************/
#include "TitleManager.h"
struct TitleCounter;

template< class T >
class ServerTitleManager : public TitleManager
{
protected:
    typedef std::map< unsigned short, TitleCounter > TitleCounterMap; 
    typedef typename TitleCounterMap::iterator TitleCounterMapIter;
public:
    ServerTitleManager()
    {
        m_mapTitleCounter.clear();
    }

    unsigned short GetTitleCounterSize() { return static_cast< unsigned short >( m_mapTitleCounter.size() ); }

    bool AddTitleCounter( TitleCounter& xCounter, bool bReplace = false );                      // ���һ���ƺż���  
    bool RemoveTitleCounter( unsigned short ustTitleID );                                       // ɾ��һ���ƺż���
    TitleCounter* GetTitleCounterByIndex( unsigned short ustIndex );                            // ������óƺż���
    TitleCounter* GetTitleCounterByTitleID( unsigned short ustTitleID );                        // �ƺ�ID��óƺż��� 
    TitleCounter* GetTitleCounterByConditionType( unsigned short ustType, int nValue );         // ����ID��óƺż���,     
    void ChangeTitleCounterArrayToMap( TitleCounter* pCounter, int nCount );                    // �Ѽ�������ת����map
    void ChangeTitleCounterMapToArray( TitleCounter* pCounter, int nCount );                    // �Ѽ���mapת��������

    void UpdataTitleCounterByCount( T* pPlayer, short nType, int nValue, int nCount = 1, bool bOnlyOne = false );        // ���¼���, bOnlyOne = true ����ͬ���͵����м���

    void SendRemoveTitleToClient( T* pPlayer );

private:
    TitleCounterMap m_mapTitleCounter;
};

template< class T >
bool ServerTitleManager< T >::AddTitleCounter( TitleCounter& xCounter, bool bReplace /* = false */ )
{
    TitleCounterMapIter iter = m_mapTitleCounter.find( xCounter.GetTitleID() );
    if ( iter != m_mapTitleCounter.end() )
    {
        if ( bReplace )
        { iter->second = xCounter; }
        return bReplace;
    }

    return m_mapTitleCounter.insert( std::make_pair( xCounter.GetTitleID(), xCounter ) ).second;
}

template< class T >
bool ServerTitleManager< T >::RemoveTitleCounter( unsigned short ustTitleID )
{
    TitleCounterMapIter iter = m_mapTitleCounter.find( ustTitleID );
    if ( iter == m_mapTitleCounter.end() )
    { return false; }

    m_mapTitleCounter.erase( iter );
    return false;
}

template< class T >
TitleCounter* ServerTitleManager< T >::GetTitleCounterByIndex( unsigned short ustIndex )
{
    if ( ustIndex >= GetTitleCounterSize() )
    { return NULL; }

    TitleCounterMapIter iter = m_mapTitleCounter.begin();
    advance( iter, ustIndex );

    return &( iter->second );
}

template< class T >
TitleCounter* ServerTitleManager< T >::GetTitleCounterByTitleID( unsigned short ustTitleID )
{
    TitleCounterMapIter iter = m_mapTitleCounter.find( ustTitleID );
    if ( iter == m_mapTitleCounter.end() )
    { return NULL; }

    return &( iter->second );
}

template< class T >
TitleCounter* ServerTitleManager< T >::GetTitleCounterByConditionType( unsigned short ustType, int nValue )
{
    for ( TitleCounterMapIter iter = m_mapTitleCounter.begin(); iter != m_mapTitleCounter.end(); ++iter )
    {
        if ( iter->second.GetType() == ustType && iter->second.GetValue() == nValue )
        { return &( iter->second ); }
    }

    return NULL;
}

template< class T >
void ServerTitleManager< T >::ChangeTitleCounterArrayToMap( TitleCounter* pCounter, int nCount )
{
    m_mapTitleCounter.clear();
    for ( int i = 0; i < nCount ;++i )
    {
        m_mapTitleCounter.insert( std::make_pair( pCounter[i].GetTitleID(), pCounter[i] ) );
    }
}

template< class T >
void ServerTitleManager< T >::ChangeTitleCounterMapToArray( TitleCounter* pCounter, int nCount )
{
    int i = 0;
    for ( TitleCounterMapIter iter = m_mapTitleCounter.begin(); iter != m_mapTitleCounter.end() && i < nCount; ++iter, ++i )
    {
        if ( !iter->second.IsEmpty() )
        {
            pCounter[ i ] = iter->second;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GamePlayer;
typedef ServerTitleManager< GamePlayer > TitleEx;

#endif
