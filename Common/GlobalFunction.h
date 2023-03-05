#ifndef __GLOBALFUNCTION_H__
#define __GLOBALFUNCTION_H__

/////////////////////////////////////////////////////////////////////////////////////
// ���������������
class ProcessAreaReputation
{
public:
    // �������������__int64��
    static __int64 SetAreaRepulation( __int64 nMapID, __int64 nCurrentValue, __int64 nMaxValue )
    {
        return ( nMapID << 48 ) | ( nCurrentValue << 24 ) | nMaxValue; 
    }

    // ���__int64�еĵ���������Ϣ
    static void GetAreaRepulation( __int64 nValue, short& nMapID, int& nCurrentValue, int& nMaxValue )
    {
        nMapID        = static_cast< short >( nValue >> 48 );
        nCurrentValue = static_cast< int >( ( nValue & 0xFFFFFF000000 ) >> 24 );
        nMaxValue     = static_cast< int >( ( nValue & 0xFFFFFF ) ); 
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////
// �ж�ʱ���Ƿ����һ��( Ҳ�����Ƿ����0:00, ��GetLocalTime�������ĵ�ǰʱ�� )
class RecordTime
{
private:
    enum EConstDefine
    {
        ECD_Year       = 16,            // λ��16
        ECD_Month      = 8,             // λ��8

        ECD_MonthValue = 0xFF00,
        ECD_DayValue   = 0xFF,

    };
public:
    RecordTime() : m_dwRecordTime( 0 ) { }

    unsigned int GetRecordTime() { return m_dwRecordTime; }
    void SetRecordTime( unsigned int dwTime ) { m_dwRecordTime = dwTime; }
    void SaveRecordTime( unsigned int nYear, unsigned int nMonth, unsigned int nDay )   // ��������
    {
        m_dwRecordTime = ( nYear << ECD_Year ) | ( nMonth << ECD_Month ) | nDay;
    }

    unsigned short GetRecordYear() { return ( m_dwRecordTime >> ECD_Year ); }   // ��ü�¼�����
    unsigned char GetRecordMonth() { return ( ( m_dwRecordTime & ECD_MonthValue ) >> ECD_Month ); } // ��ü�¼���·�
    unsigned char GetRecordDay()   { return ( m_dwRecordTime & ECD_DayValue ); }    // ��ü�¼������

    bool CheckRecordTime( unsigned short nYear, unsigned int nMonth, unsigned int nDay )    // �ж��Ƿ��ǲ�ͬ������
    {
        // ���ڵ�һ���ж�,�ɼ����жϴ���
        return ( GetRecordDay() != nDay || GetRecordMonth() != nMonth || GetRecordYear() != nYear );
    }

    // ��̬����
    static unsigned short GetRecordYear( unsigned int dwRecordTime ) { return ( dwRecordTime >> ECD_Year ); }
    static unsigned char GetRecordMonth( unsigned int dwRecordTime ) { return ( ( dwRecordTime & ECD_MonthValue ) >> ECD_Month ); }
    static unsigned char GetRecordDay( unsigned int dwRecordTime )   { return ( dwRecordTime & ECD_DayValue ); }

    static void  SaveRecordTime( unsigned int &dwRecordTime )
    {
        SYSTEMTIME xSystem;
        ::GetLocalTime( &xSystem );

        SaveRecordTime( dwRecordTime, xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    }

    static void  SaveRecordTime( unsigned long &dwRecordTime )
    {
        SYSTEMTIME xSystem;
        ::GetLocalTime( &xSystem );

        SaveRecordTime( dwRecordTime, xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    }

    static void SaveRecordTime( unsigned int &dwRecordTime, unsigned int nYear, unsigned int nMonth, unsigned int nDay )
    {
        dwRecordTime = ( nYear << ECD_Year ) | ( nMonth << ECD_Month ) | nDay;
    }

    static void SaveRecordTime( unsigned long &dwRecordTime, unsigned int nYear, unsigned int nMonth, unsigned int nDay )
    {
        dwRecordTime = ( nYear << ECD_Year ) | ( nMonth << ECD_Month ) | nDay;
    }

    static bool CheckRecordTime( unsigned int dwRecordTime, unsigned short nYear, unsigned int nMonth, unsigned int nDay )
    {
        return ( GetRecordDay( dwRecordTime ) != nDay || GetRecordMonth( dwRecordTime ) != nMonth || GetRecordYear( dwRecordTime ) != nYear );
    }

    static bool CheckRecordTime( unsigned int dwRecordTime )
    {
        SYSTEMTIME xSystem;
        ::GetLocalTime( &xSystem );

        return ( GetRecordDay( dwRecordTime ) != xSystem.wDay || GetRecordMonth( dwRecordTime ) != xSystem.wMonth || GetRecordYear( dwRecordTime ) != xSystem.wYear );
    }

private:
    unsigned int m_dwRecordTime;
};

// ��¼�ļ�������ʱ��
class RecordVarTime
{
public:
    static unsigned short FormatTimeVar()
    {
        static SYSTEMTIME xSystemTime;
        ::GetLocalTime( &xSystemTime );

        short nYear  = xSystemTime.wYear - 2000;
        short nMonth = xSystemTime.wMonth;
        short nDay   = xSystemTime.wDay;

        return ( nYear << 12 ) | ( nMonth << 8 ) | nDay;
    }

    static bool CheckPassOneDay( unsigned short nRecordTime )
    {
        short nYear  = ( nRecordTime >> 12 ) + 2000;
        short nMonth = ( ( nRecordTime & 0x0F00 ) >> 8 );
        short nDay   = ( nRecordTime & 0xFF );

        static SYSTEMTIME xSystemTime;
        ::GetLocalTime( &xSystemTime );
        return ( nDay != xSystemTime.wDay || nMonth != xSystemTime.wMonth || nYear != xSystemTime.wYear );
    }
};

// ���������͵�λ���� ����ֵֻ�������õ����� ( int, short char..�� )
template< class T >
class BitValue
{
public:
    enum BitValueDefine
    {
        ErrorValue = -1,        // ����ֵ
        NoneValue = 0,          // û��λֵ
        HaveValue = 1,          // ����λֵ
    };

    BitValue() : m_nValue( 0 ) { }
    BitValue( T nValue ) : m_nValue ( nValue ) { }

    void SetValue( T nValue ) { m_nValue = nValue; }
    T GetValue() const { return m_nValue; }

    static int GetBitLength() { return sizeof( T ) * 8; }
  
    int GetFirstNoValueIndex()                      // ��õ�һ��λֵ��0��λ����
    { 
        for ( int i = 0; i < GetBitLength(); ++i )
        {
            if ( ( m_nValue & ( 1 << i ) ) == NoneValue )
            { return i; }
        }
        return -1;  // 32λ����ֵ
    }    

    int GetBitValue( unsigned char nIndex )         // �õ�ĳλ�ϵ�ֵ
    {
        if ( nIndex < 0 || nIndex >= GetBitLength() )
        { return ErrorValue; }

        return ( m_nValue & ( 1 << nIndex ) );
    }
    
    void SetBitValue( unsigned char nIndex )        // ����ĳλ�ϵ�ֵ
    {
        if ( nIndex < 0 || nIndex >= GetBitLength() )
        { return; }

        m_nValue |= ( 1 << nIndex );
    }
    
    void ClearBitValue( unsigned char nIndex )      // ���ĳλ�ϵ�ֵ
    {
        if ( nIndex < 0 || nIndex >= GetBitLength() )
        { return; }

        m_nValue &= ~( 1 << nIndex );
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    static int GetFirstNoValueIndex( T nValue )
    {
        for ( int i = 0; i < GetBitLength(); ++i )
        {
            if ( ( nValue & ( 1 << i ) ) == NoneValue )
            { return i; }
        }
        return -1;  // 32λ����ֵ
    }

    static int GetBitValue( unsigned char nIndex, T nValue )
    {
        if ( nIndex < 0 || nIndex >= GetBitLength() )
        { return ErrorValue; }

        return ( nValue & ( 1 << nIndex ) );
    }

    static void SetBitValue( unsigned char nIndex, T& nValue )
    {
        if ( nIndex < 0 || nIndex >= GetBitLength() )
        { return; }

        nValue |= ( 1 << nIndex );
    }

    static void ClearBitValue( unsigned char nIndex, T& nValue )
    {
        if ( nIndex < 0 || nIndex >= GetBitLength() )
        { return; }

        nValue &= ~( 1 << nIndex );
    }

private:
    T m_nValue;
};

class GreenwichTime
{
public:
    static int GetTime()
    {
        //��ȡLinux �µĸ�������ʱ��
        union
        {
            long long ns100;
            _FILETIME  ft;
        }now;
        GetSystemTimeAsFileTime(&now.ft);
        //�ó�΢��ĸ�������ʱ���ڻ������
        return (int)((now.ns100-116444736000000000LL)/10000000LL);
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif