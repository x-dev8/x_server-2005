#ifndef __EQUIPUPGRADECONFIG_H__
#define __EQUIPUPGRADECONFIG_H__

#include <map>
#include <vector>
#include <algorithm>


class MaterialInfo
{
public:
    enum EConstDefine
    {
        ECD_Must          = 0,      // ����Ĳ���
        ECD_SaveOpenLight = 0x1,    // �������صĲ���
        ECD_SaveCheckup   = 0x2,    // ���������Ĳ���
        ECD_SaveElements  = 0x4,    // �������еĲ���
        ECD_SaveLevel     = 0x8,    // ���������ᴿ���߼�����װ�����ȼ�

        ECD_Max           = 0xFF,
    };

public:
    void SetMaterialID( unsigned short ustValue )     { m_ustMaterialID = ustValue; }
    void SetMaterialCount( unsigned short ustValue )  { m_ustCount = ustValue; }
    void SetMaterialEffect( unsigned short ustValue ) { m_ustEffect = ustValue; }

    const unsigned short GetMaterialID() const     { return m_ustMaterialID; }
    const unsigned short GetMaterialCount() const  { return m_ustCount; }
    const unsigned short GetMaterialEffect() const { return m_ustEffect; }

    bool IsMustMaterial() const          { return ( m_ustEffect == ECD_Must ); }                  // �Ƿ��Ǳ���Ĳ���
    bool IsSaveOpenLightMaterial() const { return ( m_ustEffect & ECD_SaveOpenLight ) != 0; }     // �Ƿ��Ǳ�������Ĳ���
    bool IsSaveCheckupmaterial() const   { return ( m_ustEffect & ECD_SaveCheckup ) != 0; }       // �Ƿ��Ǳ��������Ĳ���
    bool IsSaveElementsmaterial() const  { return ( m_ustEffect & ECD_SaveElements ) != 0; }      // �Ƿ��Ǳ����������ԵĲ���
    bool IsSaveSuitLevel() const         { return ( m_ustEffect & ECD_SaveLevel ) != 0; }         // �Ƿ��Ǳ��������ᴿ���߼�����װ�����ȼ��Ĳ���

    bool operator == ( unsigned short ustValue ) { return m_ustMaterialID == ustValue; }
    bool operator == ( const MaterialInfo& xInfo ) { return m_ustMaterialID == xInfo.GetMaterialID(); }
    friend bool operator == ( const MaterialInfo& xLeft, const MaterialInfo& xRight  ) { return xLeft.GetMaterialID() == xRight.GetMaterialID(); }
    friend bool operator == ( const MaterialInfo& xInfo, unsigned short ustValue ) { return xInfo.GetMaterialID() == ustValue; }
    friend bool operator == ( unsigned short ustValue,  const MaterialInfo& xInfo ) { return xInfo.GetMaterialID() == ustValue; }

private:
    unsigned short m_ustMaterialID;     // ���ϵ�ID
    unsigned short m_ustCount;          // ���ϵ�����
    unsigned short m_ustEffect;         // ���ϵ�����Ч�� ( �������Ͽ����� ����ͬʱ���� )
};

class UpToEquipInfo
{
protected:
    typedef std::vector< MaterialInfo > MaterialInfoVector;
    typedef MaterialInfoVector::iterator MaterialInfoVectorIter;
    typedef MaterialInfoVector::const_iterator MaterialInfoVectorConstIter;

public:
    UpToEquipInfo() : m_ustUpToEquipID( 0 ), m_nCostMoney( 0 )
    {
        m_vecMaterialInfo.clear();
    }

    UpToEquipInfo( const UpToEquipInfo& xInfo )
    {
        *this = xInfo;
    }

    UpToEquipInfo& operator = ( const UpToEquipInfo& xInfo )
    {
        if ( this != &xInfo )
        {
            m_ustUpToEquipID  = xInfo.m_ustUpToEquipID;
            m_nCostMoney      = xInfo.m_nCostMoney;
            m_vecMaterialInfo = xInfo.m_vecMaterialInfo;
        }

        return *this;
    }

    bool operator == ( unsigned short stID ) { return m_ustUpToEquipID == stID; }
    bool operator == ( const UpToEquipInfo& xInfo ){ return m_ustUpToEquipID == xInfo.m_ustUpToEquipID; }
    friend bool operator == ( const UpToEquipInfo& xLeft, const UpToEquipInfo& xRight ){ return xLeft.m_ustUpToEquipID == xRight.m_ustUpToEquipID; }
    friend bool operator == ( const UpToEquipInfo& xInfo, unsigned short stID ) { return xInfo.m_ustUpToEquipID == stID; }
    friend bool operator == ( unsigned short stID, const UpToEquipInfo& xInfo ) { return stID == xInfo.m_ustUpToEquipID; }
    
    const unsigned short GetUpToEquipID() const { return m_ustUpToEquipID; }
    const unsigned int GetCostMoney() const { return m_nCostMoney; }

    const unsigned short GetMaterialCount() const { return static_cast< unsigned short >( m_vecMaterialInfo.size() ); }
    const MaterialInfo* GetMaterialByIndex( int nIndex ) const
    {
        if ( nIndex < 0 || nIndex >= GetMaterialCount() )
        { return NULL; }

        return &( m_vecMaterialInfo.at( nIndex ) );
    }

    const MaterialInfo* GetMaterialByID( unsigned short stID ) const
    {
        MaterialInfoVectorConstIter iter = std::find( m_vecMaterialInfo.begin(), m_vecMaterialInfo.end(), stID );
        if ( iter == m_vecMaterialInfo.end() )
        { return NULL; }

        return &( *iter );
    }

    void SetUpToEquipID( unsigned short stValue ) { m_ustUpToEquipID = stValue; }
    void SetCostMoney( unsigned int nValue ) { m_nCostMoney = nValue; }

    bool AddMaterialInfo( const MaterialInfo& xInfo )
    {
        MaterialInfoVectorIter iter = std::find( m_vecMaterialInfo.begin(), m_vecMaterialInfo.end(), xInfo );
        if ( iter != m_vecMaterialInfo.end() )
        { return false; }

        m_vecMaterialInfo.push_back( xInfo );
        return true;
    }

private:
    unsigned short m_ustUpToEquipID;
    unsigned int m_nCostMoney;              // ���ĵĽ�Ǯ
    MaterialInfoVector m_vecMaterialInfo;   // �õ��Ĳ�������

};

class UpgradeData
{
protected:
    typedef std::vector< UpToEquipInfo > UpToEquipVector;
    typedef UpToEquipVector::iterator UpToEquipVectorIter;
    typedef UpToEquipVector::const_iterator UpToEquipVectorConstIter;

public:
    UpgradeData() : m_ustEquipID( 0 )
    {
        m_vecUpToEquipInfo.clear();
    }

    UpgradeData( const UpgradeData& xData )
    {
        *this = xData;
    }

    UpgradeData& operator = ( const UpgradeData& xData )
    {
        if ( this != &xData )
        {
            m_ustEquipID       = xData.m_ustEquipID;
            m_vecUpToEquipInfo = xData.m_vecUpToEquipInfo;
        }

        return *this;
    }

    const unsigned short GetEquipID() const { return m_ustEquipID; }
    const unsigned short GetUpToEquipCount() const { return static_cast< unsigned short >( m_vecUpToEquipInfo.size() ); }
    const UpToEquipInfo* GetUpToEquipByIndex( int nIndex ) const
    {
        if ( nIndex < 0 || nIndex >= GetUpToEquipCount() )
        { return 0; }

        return &( m_vecUpToEquipInfo.at( nIndex ) );
    }

    const UpToEquipInfo* GetUpToEquipByID( unsigned short stID ) const
    {
        UpToEquipVectorConstIter iter = std::find( m_vecUpToEquipInfo.begin(), m_vecUpToEquipInfo.end(), stID );
        if ( iter == m_vecUpToEquipInfo.end() )
        { return NULL; }

        return &( *iter );
    }

    bool IsUptoEquipID( unsigned short stID ) const 
    {
        UpToEquipVectorConstIter iter = std::find( m_vecUpToEquipInfo.begin(), m_vecUpToEquipInfo.end(), stID );
        return iter != m_vecUpToEquipInfo.end();
    }

    void SetEquipID( unsigned short ustValue ) { m_ustEquipID = ustValue; }
    bool AddUpToEquipID( UpToEquipInfo& xInfo )
    {
        UpToEquipVectorIter iter = std::find( m_vecUpToEquipInfo.begin(), m_vecUpToEquipInfo.end(), xInfo );
        if ( iter != m_vecUpToEquipInfo.end() )
        { return false; }

        m_vecUpToEquipInfo.push_back( xInfo );
        return true;
    }

private:
    unsigned short m_ustEquipID;            // ԭʼװ��ID
    UpToEquipVector m_vecUpToEquipInfo;     // ��������������װ����Ϣ
};

#define theEquipUpgradeConfig EquipUpgradeConfig::Instance()

class EquipUpgradeConfig
{
protected:
    typedef std::map< unsigned short, UpgradeData > UpgradeDataMap;
    typedef UpgradeDataMap::iterator UpgradeDataMapIter;
    typedef UpgradeDataMap::const_iterator UpgradeDataMapConstIter;
public:
    ~EquipUpgradeConfig() {};

    static EquipUpgradeConfig& Instance()
    {
        static EquipUpgradeConfig s_xConfig;
        return s_xConfig;
    }

    const UpgradeData* GetEquipUpgradeData( unsigned short ustEquipID ) const 
    {
        UpgradeDataMapConstIter iter = m_mapUpgradeData.find( ustEquipID );
        if ( iter == m_mapUpgradeData.end() )
        { return NULL; }

        return &( iter->second );
    }

    bool LoadEquipUpgradeConfig( const char* szFile );

	bool IsLoadEquipUpgradeConfig( )
	{
		return (m_mapUpgradeData.size() != 0);
	}
protected:
    EquipUpgradeConfig()
    {
        m_mapUpgradeData.clear();
    }

    bool AddEquipUpgradeData( UpgradeData& xData )
    {
        UpgradeDataMapIter iter = m_mapUpgradeData.find( xData.GetEquipID() );
        if ( iter != m_mapUpgradeData.end() )
        { return false; }

        return m_mapUpgradeData.insert( std::make_pair( xData.GetEquipID(), xData ) ).second;
    }

private:
    EquipUpgradeConfig( const EquipUpgradeConfig& );
    EquipUpgradeConfig& operator = ( const EquipUpgradeConfig& );

private:
    UpgradeDataMap m_mapUpgradeData;
};

#endif