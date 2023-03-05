#ifndef __KILLMONSTERCOUNTCONFIG_H__
#define __KILLMONSTERCOUNTCONFIG_H__

/************************************************************************/
/*                  杀怪记数对应的经验百分比                            */
/************************************************************************/

#include <map>
#include <functional>

class KillMonsterCount
{
public:
    static KillMonsterCount& Instance()
    {
        static KillMonsterCount s_KillMonsterCount;
        return s_KillMonsterCount;
    }

    float GetModulus( unsigned short nCount ) const
    {
        if ( nCount < m_ustMinCount )
        { return m_fMaxModulus; }   
        if ( nCount >= m_ustMaxCount )
        { return m_fMinModulus; }

        for ( KillCountMapConstIter iter = m_mapKillCount.begin(); iter != m_mapKillCount.end(); ++iter )
        {
            if ( nCount >= iter->first )
            {
                return iter->second;
            }
        }

        return m_fMaxModulus;
    }

	unsigned int GetMaxCount( unsigned short nCount ) const
	{
        if ( nCount < m_ustMinCount )
        { return m_ustMinCount; }   
        if ( nCount >= m_ustMaxCount )
        { return m_ustMaxCount; }

        for ( KillCountMapConstIter iter = m_mapKillCount.begin(); iter != m_mapKillCount.end(); ++iter )
        {
            if ( nCount >= iter->first )
            {
                return iter->first;
            }
        }

        return m_ustMinCount;
    }

    bool IsSettingKillCount( unsigned short nCount ) const
    {
        KillCountMapConstIter iter = m_mapKillCount.find( nCount );
        return ( iter != m_mapKillCount.end() );
    }

    bool LoadKillMonsterCountConfig( const char* szFile );

protected:
    typedef std::map< unsigned short, float, std::greater< unsigned short > > KillCountMap;
    typedef KillCountMap::iterator KillCountMapIter;
    typedef KillCountMap::const_iterator KillCountMapConstIter;

    KillMonsterCount() : m_ustMinCount( 5000 ), m_ustMaxCount( 9000 ), m_fMaxModulus( 1.0f ), m_fMinModulus( 0.1f )
    {
        m_mapKillCount.clear();
    }

    bool AddModulus( unsigned short nCount, float fModulus )
    {
        KillCountMapIter iter = m_mapKillCount.find( nCount );
        if ( iter != m_mapKillCount.end() )
        { return false; }

        return m_mapKillCount.insert( std::make_pair( nCount, fModulus ) ).second;
    }
private:
    KillCountMap m_mapKillCount;
    
    // 保存最大和最小数量和百分比, 这样就省去大部分查找
    unsigned short m_ustMinCount;
    unsigned short m_ustMaxCount;
    float m_fMaxModulus;
    float m_fMinModulus;
};

#define theKillMonsterCountConfig KillMonsterCount::Instance()

#endif