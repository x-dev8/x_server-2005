/********************************************************************
    Filename:     MapContainer.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#pragma once

#include "MeRTLibs.h"
/*  Sample

    // 一个释放char*的回调函数
    void destroy( char** p )
    {
        if(*p)
        {
            delete *p;
            *p = NULL;
        }
    }

    // 定义一个Key为int类型，对象为char*类型的容器
    // 在析构或者Remove的时候自动delete对象
    CMapContainer<int,char*> c;    
    // 在析构或者Remove的时候不自动delete对象
    // CMapContainer<int,char*> c(FALSE); 
    // 在析构或者Remove的时候自动使用destroy回调函数delete对象，
    // destroy回调函数参看上面的定义
    // CMapContainer<int,char*> c(TRUE,destroy);    

    // 加入一个对象
    c.Add( 1100, new char('a') );
    c.Add( 1101, new char('b') );
    c.Add( 1102, new char('c') );
    // 查找一个对象，没有找到的时候返回NULL
    char* pObj = c.Find( 1102 );

    // 把对象返回到一个vector中
    std::vector<char*> vectorObject;
    int nElementCount = c.GetObjects(&vectorObject);
    for( int i = 0; i < nElementCount; i++ )
    {
        char* ch = vectorObject[i];
    }
    // 删除一个对象，
    c.Remove( 1102 );
    pObj = c.Find( 1102 );
    // 把对象返回到一个vector中， 如果vector为NULL，则仅仅返回对象的数量
    nElementCount = c.GetObjects( NULL );
*/
template<class KeyType, class ObjectType >
class CMapContainer
{
public:
    typedef void (*ObjectDeleteCallBack)( ObjectType* pObj );
public:
    CMapContainer( BOOL bNeedDelete = TRUE,  ObjectDeleteCallBack pObjectDeleteCallBack = NULL ):
      m_bNeedDelete(TRUE), m_pfnObjectDeleteCallBack(NULL)
    {
        m_bNeedDelete = bNeedDelete;
        m_pfnObjectDeleteCallBack = pObjectDeleteCallBack;
    }

    ~CMapContainer()
    {
        Destroy();
    }

    void NeedDelete( BOOL b ){ m_bNeedDelete = b; }

    void Destroy()
    {
        if( m_bNeedDelete )
        {
            std::map<KeyType, ObjectType>::iterator it;
            for( it = m_mapObject.begin(); it != m_mapObject.end(); it++ )
            {
                ObjectType obj = it->second;
                if( obj )
                {
                    DestroyObject( &obj );
                }
            }            
        }
        m_mapObject.clear();
    }

    BOOL Add( KeyType key, ObjectType obj )
    {
        ObjectType found = Find( key );
        if( found )
        {
            return FALSE;
        }
        m_mapObject[key] = obj;
        return TRUE;
    }

    BOOL Remove( KeyType key )
    {
        ObjectType found = Find( key );
        if( !found )
            return FALSE;
        if( m_bNeedDelete )
        {
            if( found )
            {
                DestroyObject( &found );
            }
        }
        m_mapObject.erase( key );
        return TRUE;
    }

    ObjectType Find( KeyType key )
    {
        std::map<KeyType,ObjectType>::const_iterator it = m_mapObject.find( key );
        if( it == m_mapObject.end() )
            return NULL;
        return it->second;
    }

    int GetObjects( std::vector<ObjectType>* pvectorObject )
    {
        if( pvectorObject )
        {
            pvectorObject->clear();
            std::map<KeyType, ObjectType>::iterator it;
            for( it = m_mapObject.begin(); it != m_mapObject.end(); it++ )
            {
                ObjectType obj = it->second;
                pvectorObject->push_back( obj );
            }
        }
        return (int)m_mapObject.size();
    } 

    int GetObjects( ObjectType buffer[], int nBufferSize )
    {
        if( (int)m_mapObject.size() > nBufferSize )
        {
            assert( false );
            for( int i = 0; i < nBufferSize; i++ )
                buffer[i] = NULL;
            // 返回0有助于解决问题,返回一个合理的值往往会导致程序员忽略错误存在
            return 0;
        }
        std::map<KeyType, ObjectType>::iterator it;
        int i = 0;
        for( it = m_mapObject.begin(); it != m_mapObject.end(); it++ )
        {
            ObjectType obj = it->second;
            //pvectorObject->push_back( obj );
            buffer[i++] = obj;
        }
        return i;
    }

    void DestroyObject( ObjectType* pObj )
    {
        if( m_pfnObjectDeleteCallBack )
            m_pfnObjectDeleteCallBack( pObj );
        else
        {
            delete *pObj;
            *pObj = NULL;
        }
    }

    size_t GetSize() { return m_mapObject.size();}

protected:
    BOOL m_bNeedDelete;
    ObjectDeleteCallBack m_pfnObjectDeleteCallBack;
    std::map<KeyType,ObjectType> m_mapObject;
};
