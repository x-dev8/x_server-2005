/********************************************************************
    Filename:    TimeEx.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#pragma once

#include "MeRTLibs.h"

class TimeSpan
{
public:
	TimeSpan() throw();
	
	
	//TimeGetTime秒时间转换. 牺牲毫秒精度
	TimeSpan( DWORD dwTime /* */);
	
	TimeSpan( __time64_t time ) throw();
	TimeSpan( LONG lDays, int nHours, int nMins, int nSecs ) throw();

	LONGLONG GetDays() const throw();
	LONGLONG GetTotalHours() const throw();
	LONG GetHours() const throw();
	LONGLONG GetTotalMinutes() const throw();
	LONG GetMinutes() const throw();
	LONGLONG GetTotalSeconds() const throw();
	LONG GetSeconds() const throw();

	__time64_t GetTimeSpan() const throw();

	TimeSpan operator+( TimeSpan span ) const throw();
	TimeSpan operator-( TimeSpan span ) const throw();
	TimeSpan& operator+=( TimeSpan span ) throw();
	TimeSpan& operator-=( TimeSpan span ) throw();
	bool operator==( TimeSpan span ) const throw();
	bool operator!=( TimeSpan span ) const throw();
	bool operator<( TimeSpan span ) const throw();
	bool operator>( TimeSpan span ) const throw();
	bool operator<=( TimeSpan span ) const throw();
	bool operator>=( TimeSpan span ) const throw();

//#ifndef _ATL_MIN_CRT
//public:
//	std::string Format( LPCTSTR pszFormat ) const;
//	std::string Format( UINT nID ) const;
//#endif
//#if defined(_AFX) && defined(_UNICODE)
//	// for compatibility with MFC 3.x
//	std::string Format(LPCSTR pFormat) const;
//#endif

//#ifdef _AFX
//	CArchive& Serialize64(CArchive& ar);
//#endif

private:
	__time64_t m_timeSpan;
};

class TimeEx
{
public:
	enum
	{
		UNDEF_TIME = -1
	};
public:
	static TimeEx GetCurrentTime() throw();
	static BOOL IsValidFILETIME(const FILETIME& ft) throw();

	TimeEx() throw();
	TimeEx( __time64_t time ) throw();
	TimeEx( int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec,
		int nDST = -1 );
	TimeEx( WORD wDosDate, WORD wDosTime, int nDST = -1 );
	TimeEx( const SYSTEMTIME& st, int nDST = -1 );
	TimeEx( const FILETIME& ft, int nDST = -1 );
//#ifdef __oledb_h__
//	Time( const DBTIMESTAMP& dbts, int nDST = -1 ) throw();
//#endif

	TimeEx& operator=( __time64_t time ) throw();

	TimeEx& operator+=( TimeSpan span ) throw();
	TimeEx& operator-=( TimeSpan span ) throw();

	TimeSpan operator-( TimeEx time ) const throw();
	TimeEx operator-( TimeSpan span ) const throw();
	TimeEx operator+( TimeSpan span ) const throw();

	bool operator==( TimeEx time ) const throw();
	bool operator!=( TimeEx time ) const throw();
	bool operator<( TimeEx time ) const throw();
	bool operator>( TimeEx time ) const throw();
	bool operator<=( TimeEx time ) const throw();
	bool operator>=( TimeEx time ) const throw();

	struct tm* GetGmtTm( struct tm* ptm ) const;
	struct tm* GetLocalTm( struct tm* ptm ) const;
#if !_SECURE_ATL
//	_ATL_INSECURE_DEPRECATE("Pass an output time structure to Time::GetGmtTm")
	struct tm* GetGmtTm() const throw();
//	_ATL_INSECURE_DEPRECATE("Pass an output time structure to Time::GetLocalTm")
	struct tm* GetLocalTm() const throw();
#endif

	bool GetAsSystemTime( SYSTEMTIME& st ) const throw();
//	bool GetAsDBTIMESTAMP( DBTIMESTAMP& dbts ) const throw();

	__time64_t GetTime() const throw();

	int GetYear() const throw();
	int GetMonth() const throw();
	int GetDay() const throw();
	int GetHour() const throw();
	int GetMinute() const throw();
	int GetSecond() const throw();
	int GetDayOfWeek() const throw();

//#ifndef _ATL_MIN_CRT
//	// formatting using "C" strftime
//	std::string Format( LPCTSTR pszFormat ) const;
//	std::string FormatGmt( LPCTSTR pszFormat ) const;
//	std::string Format( UINT nFormatID ) const;
//	std::string FormatGmt( UINT nFormatID ) const;
//#endif
	// for compatibility with MFC 3.x
//	std::string Format(LPCSTR pFormat) const;
//	std::string FormatGmt(LPCSTR pFormat) const;
//	std::string Format();

    static bool IsPassCurrentTime( __time64_t n64Time ) // 是否过期了
    {
        TimeEx ItemTime( n64Time );
        return ( ItemTime <= GetCurrentTime() );
    }

    static bool IsPassCurrentTime( __time64_t n64StartTime, __time64_t nSpaceTime )
    {
        TimeEx xTime( n64StartTime );
        TimeSpan xSpan( nSpaceTime );
        xTime += xSpan;

        return ( GetCurrentTime() >= xTime );
    }

    static __time64_t GetNowTime()
    {
        return GetCurrentTime().GetTime();
    }

private:
	__time64_t m_time;
};

