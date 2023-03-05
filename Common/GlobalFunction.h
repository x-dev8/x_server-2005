#ifndef __GLOBALFUNCTION_H__
#define __GLOBALFUNCTION_H__

/////////////////////////////////////////////////////////////////////////////////////
// 地区声望操作相关
class ProcessAreaReputation
{
public:
    // 保存地区声望到__int64中
    static __int64 SetAreaRepulation( __int64 nMapID, __int64 nCurrentValue, __int64 nMaxValue )
    {
        return ( nMapID << 48 ) | ( nCurrentValue << 24 ) | nMaxValue; 
    }

    // 获得__int64中的地区声望信息
    static void GetAreaRepulation( __int64 nValue, short& nMapID, int& nCurrentValue, int& nMaxValue )
    {
        nMapID        = static_cast< short >( nValue >> 48 );
        nCurrentValue = static_cast< int >( ( nValue & 0xFFFFFF000000 ) >> 24 );
        nMaxValue     = static_cast< int >( ( nValue & 0xFFFFFF ) ); 
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////
// 判断时间是否过了一天( 也就是是否过了0:00, 用GetLocalTime函数过的当前时间 )
class RecordTime
{
private:
    enum EConstDefine
    {
        ECD_Year       = 16,            // 位移16
        ECD_Month      = 8,             // 位移8

        ECD_MonthValue = 0xFF00,
        ECD_DayValue   = 0xFF,

    };
public:
    RecordTime() : m_dwRecordTime( 0 ) { }

    unsigned int GetRecordTime() { return m_dwRecordTime; }
    void SetRecordTime( unsigned int dwTime ) { m_dwRecordTime = dwTime; }
    void SaveRecordTime( unsigned int nYear, unsigned int nMonth, unsigned int nDay )   // 保存日期
    {
        m_dwRecordTime = ( nYear << ECD_Year ) | ( nMonth << ECD_Month ) | nDay;
    }

    unsigned short GetRecordYear() { return ( m_dwRecordTime >> ECD_Year ); }   // 获得记录的年份
    unsigned char GetRecordMonth() { return ( ( m_dwRecordTime & ECD_MonthValue ) >> ECD_Month ); } // 获得记录的月份
    unsigned char GetRecordDay()   { return ( m_dwRecordTime & ECD_DayValue ); }    // 获得记录的日期

    bool CheckRecordTime( unsigned short nYear, unsigned int nMonth, unsigned int nDay )    // 判断是否是不同日期了
    {
        // 日期第一个判断,可减少判断次数
        return ( GetRecordDay() != nDay || GetRecordMonth() != nMonth || GetRecordYear() != nYear );
    }

    // 静态函数
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

// 记录的记数变量时间
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

// 对内置类型的位操作 类型值只能是内置的类型 ( int, short char..等 )
template< class T >
class BitValue
{
public:
    enum BitValueDefine
    {
        ErrorValue = -1,        // 错误值
        NoneValue = 0,          // 没有位值
        HaveValue = 1,          // 存在位值
    };

    BitValue() : m_nValue( 0 ) { }
    BitValue( T nValue ) : m_nValue ( nValue ) { }

    void SetValue( T nValue ) { m_nValue = nValue; }
    T GetValue() const { return m_nValue; }

    static int GetBitLength() { return sizeof( T ) * 8; }
  
    int GetFirstNoValueIndex()                      // 获得第一个位值是0的位索引
    { 
        for ( int i = 0; i < GetBitLength(); ++i )
        {
            if ( ( m_nValue & ( 1 << i ) ) == NoneValue )
            { return i; }
        }
        return -1;  // 32位都有值
    }    

    int GetBitValue( unsigned char nIndex )         // 得到某位上的值
    {
        if ( nIndex < 0 || nIndex >= GetBitLength() )
        { return ErrorValue; }

        return ( m_nValue & ( 1 << nIndex ) );
    }
    
    void SetBitValue( unsigned char nIndex )        // 设置某位上的值
    {
        if ( nIndex < 0 || nIndex >= GetBitLength() )
        { return; }

        m_nValue |= ( 1 << nIndex );
    }
    
    void ClearBitValue( unsigned char nIndex )      // 清除某位上的值
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
        return -1;  // 32位都有值
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
        //获取Linux 下的格林威治时间
        union
        {
            long long ns100;
            _FILETIME  ft;
        }now;
        GetSystemTimeAsFileTime(&now.ft);
        //得出微妙级的格林威治时间在换算成秒
        return (int)((now.ns100-116444736000000000LL)/10000000LL);
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif