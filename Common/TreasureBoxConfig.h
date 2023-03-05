#ifndef __TREASUREBOXCONFIG_H__
#define __TREASUREBOXCONFIG_H__

#include <vector>
#include <map>

enum ETreasureBoxDefine
{
    ECD_Min_BoxLevel      = 1,      //  ������С�ȼ�
    ECD_Max_BoxLevel      = 7,      //  ������7���ȼ�
    ECD_Max_TreasureCount = 24,     //  ÿ��������24����Ʒ
};

class TreasureData
{
public:
    TreasureData() : m_uchIndex( -1 ), m_ustItemID( 0 ), m_ustCount( 0 ), m_nProbability( 0 ), m_bNoticeWorld( false ) {}
    const unsigned char GetIndex() const      { return m_uchIndex; }
    const unsigned short GetItemID() const    { return m_ustItemID; }
    const unsigned short GetCount() const     { return m_ustCount; }
    const unsigned int GetProbability() const { return m_nProbability; }
    static unsigned char GetMaxIndex()        { return m_uchMaxIndex; }
    bool GetNoticeWorld() const               { return m_bNoticeWorld; }

    bool SetIndex( unsigned char uchIndex )
    { 
        if ( uchIndex >= ECD_Max_TreasureCount )
        { return false; }

        m_uchIndex = uchIndex;
        return true;
    }

    void SetNoticeWorld( bool bValue )               { m_bNoticeWorld = bValue; }   
    void SetItemID( unsigned short ustItemID )       { m_ustItemID = ustItemID; }
    void SetItemCount( unsigned short ustCount )     { m_ustCount = ustCount; }
    void SetProbability( unsigned int nProbability ) { m_nProbability = nProbability; }
    static void SetMaxLevel( unsigned char uchMaxIndex )    { m_uchMaxIndex = uchMaxIndex; }

    bool IsError() { return ( m_uchIndex < 0 || m_uchIndex >= m_uchMaxIndex || m_ustItemID == 0 || m_ustCount == 0 ); }

    bool operator < ( const TreasureData& xData ) { return m_uchIndex < xData.GetIndex(); }
    friend bool operator < ( const TreasureData& xLeft, const TreasureData& xRight ) { return xLeft.GetIndex() < xRight.GetIndex(); }
private:
    static unsigned char m_uchMaxIndex;     // �����Ʒ����
    unsigned char m_uchIndex;               // λ������
    unsigned short m_ustItemID;             // ��ƷID
    unsigned short m_ustCount;              // ��Ʒ����
    unsigned int m_nProbability;            // ��Ʒ����
    bool m_bNoticeWorld;                    // �Ƿ�Ҫȫ������
};

#define theTreasureBoxConfig TreasureBoxConfig::Instance()
class TreasureBoxConfig
{
public:
    typedef std::vector< TreasureData > DataVector;
    typedef DataVector::const_iterator DataVectorIter;

    typedef std::map< unsigned short, DataVector > DataMap;
    typedef DataMap::iterator DataMapIter;
    typedef DataMap::const_iterator DataMapConstIter;

    typedef std::vector< DataMap > TreasureDataVector;
    typedef TreasureDataVector::iterator TreasureDataIter;
    typedef TreasureDataVector::const_iterator TreasureDataConstIter;

    typedef std::map< unsigned short, unsigned int > ProbabilityMap;
    typedef ProbabilityMap::iterator ProbabilityMapIter;
    typedef ProbabilityMap::const_iterator ProbabilityMapConstIter;

    typedef std::vector< ProbabilityMap > ProbabilityVector;
    typedef ProbabilityVector::const_iterator ProbabilityVectorIter;

public:
    static TreasureBoxConfig& Instance()
    {
        static TreasureBoxConfig s_xTreasureBoxConfig;
        return s_xTreasureBoxConfig;
    }

    void SetMaxBoxLevel( unsigned char chValue ) { m_uchMaxBoxLevel = chValue; }

    bool Initialize();

    const DataVector* GetTreasureData( unsigned char uchLevel, unsigned short ustItemID ) const;
    const TreasureData* GetTreasureData( unsigned char uchLevel, unsigned short ustItemID, unsigned char uchIndex ) const;
    const unsigned char GetRandTreasureData( unsigned char uchLevel, unsigned short ustItemID, unsigned int nRandNumber ) const;
    const unsigned int GetSpecificValue( unsigned char uchLevel, unsigned short ustItemID );

    bool LoadConfig( const char* pszConfig );

protected:
    TreasureBoxConfig() : m_uchMaxBoxLevel( ECD_Max_BoxLevel ){}

    bool AddTreasureData( unsigned char uchLevel, unsigned short ustItemID, TreasureData& xData );
    bool AddProbability( unsigned char uchLevel, unsigned short ustItemID, unsigned int nProbability );

    bool AddSpecificValue( unsigned char uchLevel, unsigned short ustItemID, unsigned int nSpecificValue );

private:
    TreasureBoxConfig( const TreasureBoxConfig& );
    TreasureBoxConfig& operator == ( const TreasureBoxConfig& );

private:
    unsigned char m_uchMaxBoxLevel;         // ���ȼ�
    TreasureDataVector m_vecTreasureData;   // ���汦������Ʒ������
    ProbabilityVector m_vecProbability;     // ���汦������Ʒ���漴�����ܺ�

    ProbabilityVector m_vecSpecificValue;   // ���������ֵ������, ��ѡ�������Ʒ
};


#endif