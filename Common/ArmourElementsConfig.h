#ifndef __ARMOURELEMENTSCONFIG_H__
#define __ARMOURELEMENTSCONFIG_H__

#include <map>
#include <vector>
#include <algorithm>

#define theArmourElementsConfig ArmourElementsConfig::Instance()

class ArmourElementsConfig
{
public:

    enum EConstDefine
    {
        ECD_ElementCount = 5,
    };

    class ElementsData
    {
    public:
        ElementsData() : chForbear( 0 ), chAssist( 0 ) { }

        void SetForbear( unsigned char chValue ) { chForbear = chValue; }
        void SetAssist( unsigned char chValue )  { chAssist = chValue; }

        const unsigned char GetForbear() const { return chForbear; }
        const unsigned char GetAssist() const  { return chAssist; }

    private:
        unsigned char chForbear;     // 相克的元素
        unsigned char chAssist;      // 相生的元素
    };

    typedef std::map< unsigned char, ElementsData > MapElementsData;
    typedef MapElementsData::iterator MapElemestsDataIter;

    class ModulusData
    {
    public:
        ModulusData() : stForbear( 0 ), stAssist( 0 ) { }

        void SetForbear( unsigned short stValue ) { stForbear = stValue; }
        void SetAssist( unsigned short stValue )  { stAssist = stValue; }

        const unsigned short GetForbear() const { return stForbear; }
        const unsigned short GetAssist() const { return stAssist; }

    private:
        unsigned short stForbear;       // 相克的系数
        unsigned short stAssist;        // 相生的系数
    };

    typedef std::map< unsigned char, ModulusData > MapModulusData;
    typedef MapModulusData::iterator MapModulusDataIter;
    
    typedef std::map< unsigned short, MapModulusData > MapLevelModulusData;
    typedef MapLevelModulusData::iterator MapLevelModulusDataIter;

    typedef std::vector< unsigned short > ValueVector;
    typedef ValueVector::iterator ValueVectorIter;
    typedef ValueVector::const_iterator ValueVectorConstIter;

    typedef std::vector< ValueVector > LevelValueVector;
    typedef LevelValueVector::iterator LevelValueVectorIter;
    typedef LevelValueVector::const_iterator LevelValueVectorConstIter;

    typedef std::vector< LevelValueVector > ElementValueVector;
    typedef ElementValueVector::iterator ElementValueVectorIter;
    typedef ElementValueVector::const_iterator ElementValueVectorConstIter;

    typedef std::map< unsigned short, ValueVector > ValueMap;
    typedef ValueMap::iterator ValueMapIter;
    typedef ValueMap::const_iterator ValueMapConstIter;

    typedef std::map< unsigned short, LevelValueVector > LevelValueMap;
    typedef LevelValueMap::iterator LevelValueMapIter;
    typedef LevelValueMap::const_iterator LevelValueMapConstiter;

    typedef std::map< unsigned short, ElementValueVector > ElementValueMap;
    typedef ElementValueMap::iterator ElementValueMapIter;
    typedef ElementValueMap::const_iterator ElementValueMapConstIter;


public: // 方法
    static ArmourElementsConfig& Instance()
    {
        static ArmourElementsConfig s_xConfig;
        return s_xConfig;
    }

    bool IsForbear( unsigned char chFirst, unsigned char chSecond )
    {
        MapElemestsDataIter iter = m_mapElementsData.find( chFirst );
        if ( iter == m_mapElementsData.end() )
        { return false; }

        return ( iter->second.GetForbear() == chSecond );
    }

    bool IsAssist( unsigned char chFirst, unsigned char chSecond )
    {
        MapElemestsDataIter iter = m_mapElementsData.find( chFirst );
        if ( iter == m_mapElementsData.end() )
        { return false; }

        return ( iter->second.GetAssist() == chSecond );
    }

    unsigned short GetForbearModulus( unsigned short stLevel, unsigned char chElementCount )
    {
        MapLevelModulusDataIter iter = m_mapElementsModulus.find( stLevel );
        if ( iter == m_mapElementsModulus.end() )
        { return 0; }

        MapModulusDataIter miter = iter->second.find( chElementCount );
        if ( miter == iter->second.end() )
        { return 0; }

        return miter->second.GetForbear();
    }

    unsigned short GetAssistModulus( unsigned short stLevel, unsigned char chElementCount )
    {
        MapLevelModulusDataIter iter = m_mapElementsModulus.find( stLevel );
        if ( iter == m_mapElementsModulus.end() )
        { return 0; }

        MapModulusDataIter miter = iter->second.find( chElementCount );
        if ( miter == iter->second.end() )
        { return 0; }

        return miter->second.GetAssist();
    }

    unsigned short GetExtendAttack( unsigned short ustEquipLevel, unsigned char uchElementLevel ) const
    {
        ValueMapConstIter iter = m_mapExtendAttack.find( ustEquipLevel );
        if ( iter == m_mapExtendAttack.end() )
        { return 0; }

        if ( uchElementLevel > m_uchElementMaxLevel )
        { return 0; }

        return iter->second.at( uchElementLevel );
    }

    void GetHideAttribute( unsigned short ustEquipLevel, unsigned char uchElementLevel, ValueVector& vecValue ) const
    {
        vecValue.clear();

        if ( uchElementLevel > m_uchElementMaxLevel )
        { return; }

        LevelValueMapConstiter iter = m_mapHideAttribute.find( ustEquipLevel );
        if ( iter == m_mapHideAttribute.end() )
        { return; }

        vecValue = iter->second.at( uchElementLevel );
    }

    void GetBaseAttribute( unsigned short ustEquipLevel, unsigned char uchElement, unsigned char uchElementCount, ValueVector& vecValue ) const
    {
        vecValue.clear();
        if ( uchElement > ECD_ElementCount || uchElementCount > m_uchElementMaxCount )
        { return; }

        ElementValueMapConstIter iter = m_mapBaseAttribute.find( ustEquipLevel );
        if ( iter == m_mapBaseAttribute.end() )
        { return; }

        vecValue = iter->second[ uchElement ].at( uchElementCount );
    }

    unsigned char GetElementMaxLevel() const { return m_uchElementMaxLevel; }
    unsigned char GetElementMinHideAttributeLevel() const { return m_uchHideAttributeLevel; }

    bool LoadArmourElementsConfig( const char* szFile );

protected: // 方法
    ArmourElementsConfig() : m_uchHideAttributeLevel( 3 ) { }

    bool AddElementsData( unsigned char chElement, ElementsData& xData )
    {
        MapElemestsDataIter iter = m_mapElementsData.find( chElement );
        if ( iter != m_mapElementsData.end() )
        { return false; }

        return m_mapElementsData.insert( std::make_pair( chElement, xData ) ).second;
    }

    bool AddElementsModulus( unsigned short stLevel, unsigned char chElementCount, ModulusData& xData )
    {
        MapLevelModulusDataIter iter = m_mapElementsModulus.find( stLevel );
        if ( iter == m_mapElementsModulus.end() )
        {
            MapModulusData mapData;
            mapData.insert( std::make_pair( chElementCount, xData ) );

            return m_mapElementsModulus.insert( std::make_pair( stLevel, mapData ) ).second;
        }
        else
        {
            MapModulusDataIter miter = iter->second.find( chElementCount );
            if ( miter != iter->second.end() )
            { return false; }

            return iter->second.insert( std::make_pair( chElementCount, xData ) ).second;
        }
    }

    bool AddExtendAttack( unsigned short ustEquipLevel, unsigned char uchElementLevel, unsigned short ustAttack )
    {
        if ( uchElementLevel > m_uchElementMaxLevel )
        { return false; }

        ValueMapIter iter = m_mapExtendAttack.find( ustEquipLevel );
        if ( iter == m_mapExtendAttack.end() )
        {
            ValueVector vecValue;
            vecValue.resize( m_uchElementMaxLevel + 1 );

            vecValue[ uchElementLevel ] = ustAttack;

            m_mapExtendAttack.insert( std::make_pair( ustEquipLevel, vecValue ) );
        }
        else
        {
            iter->second[ uchElementLevel ] = ustAttack;
        }

        return true;
    }

    bool AddHideAttribute( unsigned short ustEquipLevel, unsigned char uchElementLevel, unsigned char uchIndex, unsigned char uchMaxCount, unsigned short ustAttriID )
    {
        if ( uchElementLevel > m_uchElementMaxLevel || uchIndex >= uchMaxCount )
        { return false; }

        LevelValueMapIter iter = m_mapHideAttribute.find( ustEquipLevel );
        if ( iter == m_mapHideAttribute.end() )
        {
            LevelValueVector vecLevelValue;
            vecLevelValue.resize( m_uchElementMaxLevel + 1 );
            for ( int i = 0; i < m_uchElementMaxLevel + 1; ++i )
            {
                vecLevelValue[i].resize( uchMaxCount );
            }

            vecLevelValue[ uchElementLevel ][ uchIndex ] = ustAttriID;

            m_mapHideAttribute.insert( std::make_pair( ustEquipLevel, vecLevelValue ) );
        }
        else
        {
            iter->second[ uchElementLevel ][ uchIndex ] = ustAttriID;
        }

        return true;
    }

    bool AddBaseAttribute( unsigned short ustEquipLevel, unsigned char uchElement, unsigned char uchElementCount, unsigned char uchIndex, unsigned char uchMaxAttriCount, unsigned short ustAttriID )
    {
        if ( uchElement == 0 || uchElement > ECD_ElementCount || uchElementCount > m_uchElementMaxCount || uchIndex >= uchMaxAttriCount )
        { return false; }

        ElementValueMapIter iter = m_mapBaseAttribute.find( ustEquipLevel );
        if ( iter == m_mapBaseAttribute.end() )
        {
            ElementValueVector vecElementValue;
            vecElementValue.resize( ECD_ElementCount + 1 );    // 五种元素

            for ( int i = 0; i < ECD_ElementCount + 1; ++i )
            {
                vecElementValue[i].resize( m_uchElementMaxCount + 1 );
                for ( int j = 0; j < m_uchElementMaxCount + 1; ++j )
                {
                    vecElementValue[i][j].resize( uchMaxAttriCount );
                }
            }

            vecElementValue[ uchElement ][ uchElementCount ][ uchIndex ] = ustAttriID;

            m_mapBaseAttribute.insert( std::make_pair( ustEquipLevel, vecElementValue ) );
        }
        else
        {
            iter->second[ uchElement ][ uchElementCount ][ uchIndex ] = ustAttriID;
        }

        return true;
    }

private: // 方法
    ArmourElementsConfig( const ArmourElementsConfig& );
    ArmourElementsConfig& operator = ( const ArmourElementsConfig& );

private:        // 属性
    MapElementsData m_mapElementsData;          // 五行的关系    
    MapLevelModulusData m_mapElementsModulus;        // 五行的加成系数

    unsigned char m_uchElementMaxLevel;     // 五行元素提纯的最大等级
    unsigned char m_uchElementMaxCount;     // 一套五行装备的最大五行元素个数

    unsigned char m_uchHideAttributeLevel;  // 最小激活隐藏属性的等级

    ValueMap m_mapExtendAttack;          // 附加的攻击
    LevelValueMap m_mapHideAttribute;    // 隐藏的属性
    ElementValueMap m_mapBaseAttribute;  // 基础附加的属性
};

#endif