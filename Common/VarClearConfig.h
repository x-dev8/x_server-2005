#ifndef __VARCLEARCONFIG_H__
#define __VARCLEARCONFIG_H__
/************************************************************************
        // 每天12点 要清除的一些记数变量

************************************************************************/
#include <map>
#include <vector>
#include "Singleton.h"

#define theVarClearConfig VarClearConfig::Instance()

class VarClearConfig : public ISingletion< VarClearConfig >
{
public:
    typedef std::vector< int > VarVector;
    typedef VarVector::const_iterator VarVectorIter;

    typedef std::map< int, VarVector > VarMap;
    typedef VarMap::iterator VarMapIter;
    typedef VarMap::const_iterator VarMapConstIter;

    VarClearConfig();

    const VarMap& GetPlayerVar() const; 
    const VarMap& GetGuildVar() const;

    bool LoadConfig( const char* szFile );

protected:
    void AddPlayerVar( int nTimeVar, int nClearVar );
    void AddGuildVar( int nTimeVar, int nClearVar );

private:
    VarMap m_mapPlayerVar;
    VarMap m_mapGuildVar;
};

inline const VarClearConfig::VarMap& VarClearConfig::GetPlayerVar() const
{
    return m_mapPlayerVar;
}

inline const VarClearConfig::VarMap& VarClearConfig::GetGuildVar() const
{
    return m_mapGuildVar;
}

inline void VarClearConfig::AddPlayerVar( int nTimeVar, int nClearVar )
{
    VarMapIter iter = m_mapPlayerVar.find( nTimeVar );
    if ( iter == m_mapPlayerVar.end() )
    {
        VarVector vecClear;
        vecClear.push_back( nClearVar );
        m_mapPlayerVar[ nTimeVar ] = vecClear;
    }
    else
    {
        iter->second.push_back( nClearVar );
    }
}

inline void VarClearConfig::AddGuildVar( int nTimeVar, int nClearVar )
{
    VarMapIter iter = m_mapGuildVar.find( nTimeVar );
    if ( iter == m_mapGuildVar.end() )
    {
        VarVector vecClear;
        vecClear.push_back( nClearVar );
        m_mapGuildVar[ nTimeVar ] = vecClear;
    }
    else
    {
        iter->second.push_back( nClearVar );
    }
}

#endif