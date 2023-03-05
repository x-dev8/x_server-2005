#ifndef __TSingleton_H__
#define __TSingleton_H__

#include <vector>
#include <string>
#include <map>
#include <utility>

template <class T>
class TSingleton
{
public:
    TSingleton()
    {
        if( m_vecT == NULL )
            m_vecT = new std::vector<T *>();

        if( m_mapT == NULL )
            m_mapT = new std::map<std::string,T *>();
    }

    virtual ~TSingleton()
    {
        if( m_vecT )
        {
            for( int i=0; i<(int)(*m_vecT).size(); i++ )
            {
                delete (*m_vecT)[i];
            }
            delete m_vecT;
            m_vecT = NULL;
        }
        if( m_mapT )
        {
            delete m_mapT;
            m_mapT = NULL;
        }
    }

    static T* Lookup( const char* szName )
    {
        std::map<std::string,T *>::iterator it = (*m_mapT).find( szName );
        if( it == (*m_mapT).end() )
            return NULL;

        return it->second;
    }

    static bool Register( const char *szName, T *pClassData )
    {
        if( Lookup( szName ) )
            return false;
        
        (*m_vecT).push_back( pClassData );
        (*m_mapT).insert( std::pair<std::string, T *>( szName, pClassData ) );

        if( !Lookup( szName ) )
            return false;
        return true;
    }

    T *operator[](int index)
    {
        size_t i = (size_t)index;
        if( i < 0 || i>= (*m_vecT).size() )
            return NULL;

        return (*m_vecT)[i];
    }
    
    int Size() { return (*m_vecT).size();}

protected:
    static std::vector<T*>*          m_vecT;
    static std::map<std::string,T*>* m_mapT;
};

template <class T>
std::vector<T*>* TSingleton<T>::m_vecT = NULL;

template <class T>
std::map<std::string,T*>* TSingleton<T>::m_mapT = NULL;

#endif // __TSingleton_H__
