
#pragma once

#include <windows.h>
#include <string>
#include <time.h>
class HRTimeSpan
{
public:
	HRTimeSpan() throw();
	
	
	//TimeGetTime秒时间转换. 牺牲毫秒精度
	HRTimeSpan( DWORD dwTime /* */);
	
	HRTimeSpan( __time64_t time ) throw();
	HRTimeSpan( LONG lDays, int nHours, int nMins, int nSecs ) throw();

	LONGLONG GetDays() const throw();
	LONGLONG GetTotalHours() const throw();
	LONG GetHours() const throw();
	LONGLONG GetTotalMinutes() const throw();
	LONG GetMinutes() const throw();
	LONGLONG GetTotalSeconds() const throw();
	LONG GetSeconds() const throw();

	__time64_t GetTimeSpan() const throw();

	HRTimeSpan operator+( HRTimeSpan span ) const throw();
	HRTimeSpan operator-( HRTimeSpan span ) const throw();
	HRTimeSpan& operator+=( HRTimeSpan span ) throw();
	HRTimeSpan& operator-=( HRTimeSpan span ) throw();
	bool operator==( HRTimeSpan span ) const throw();
	bool operator!=( HRTimeSpan span ) const throw();
	bool operator<( HRTimeSpan span ) const throw();
	bool operator>( HRTimeSpan span ) const throw();
	bool operator<=( HRTimeSpan span ) const throw();
	bool operator>=( HRTimeSpan span ) const throw();

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

class HRTime
{
public:
	enum
	{
		UNDEF_TIME = -1
	};
public:
	static HRTime  GetCurrentTime() throw();
	static BOOL  IsValidFILETIME(const FILETIME& ft) throw();

	HRTime() throw();
	HRTime( __time64_t time ) throw();
	HRTime( int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec,
		int nDST = -1 );
	HRTime( WORD wDosDate, WORD wDosTime, int nDST = -1 );
	HRTime( const SYSTEMTIME& st, int nDST = -1 );
	HRTime( const FILETIME& ft, int nDST = -1 );
//#ifdef __oledb_h__
//	HRTime( const DBTIMESTAMP& dbts, int nDST = -1 ) throw();
//#endif

	HRTime& operator=( __time64_t time ) throw();

	HRTime& operator+=( HRTimeSpan span ) throw();
	HRTime& operator-=( HRTimeSpan span ) throw();

	HRTimeSpan operator-( HRTime time ) const throw();
	HRTime operator-( HRTimeSpan span ) const throw();
	HRTime operator+( HRTimeSpan span ) const throw();

	bool operator==( HRTime time ) const throw();
	bool operator!=( HRTime time ) const throw();
	bool operator<( HRTime time ) const throw();
	bool operator>( HRTime time ) const throw();
	bool operator<=( HRTime time ) const throw();
	bool operator>=( HRTime time ) const throw();

	struct tm* GetGmtTm( struct tm* ptm ) const;
	struct tm* GetLocalTm( struct tm* ptm ) const;
#if !_SECURE_ATL
//	_ATL_INSECURE_DEPRECATE("Pass an output time structure to HRTime::GetGmtTm")
	struct tm* GetGmtTm() const throw();
//	_ATL_INSECURE_DEPRECATE("Pass an output time structure to HRTime::GetLocalTm")
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


private:
	__time64_t m_time;
};

/**
*实现个简单的定时器，方便使用，使用timeGetTime获取时间，精确到10ms
* 描述:封装下定时器,检测当前时间和上次触发时间,如果当前时间>=上次触发时间，本次检测触发有效，本定时器不是严格的Delay
* 请保证初始化定时器的时间间隔>0
* 参数:
**/
class HRTimer
{
public:
	/**
	* 描述:定时器构造函数,
	* 返回值:
	* 参数:interval:定时器的触发间隔毫秒,delay:延迟触发的毫秒
	**/
	HRTimer(const DWORD interval, const DWORD delay = 0):_long(interval)
	{
		_time = timeGetTime();
		_time += (interval + delay);
	}
	/**
	* 描述:制定特定的时间开始触发定时器
	* 返回值:
	* 参数:interval:定时器触发间隔,cur开始触发的时间
	**/
	HRTimer(const DWORD cur, const int interval, const int delay = 0):_long(interval)
	{
		_time = cur;
		_time += (_long + delay);
	}
	/**
	* 描述:中断本次触发，从制定的时间开始触发
	* 返回值:
	* 参数:cur:开始触发的时间
	**/
	void next(DWORD cur)
	{
		_time = cur;
		_time += _long;
	}
	/**
	* 描述:离current还剩下的毫秒数
	* 返回值:
	* 参数:cur:当前时间
	**/
	DWORD left(DWORD current)
	{
		if(_time <= current)
		{
			return 0;
		}
		if(  _time >= 0xffff0000 && current <= 60000 )
		{
			uint64 currentTime = current + ULONG_MAX;
			if(_time > currentTime)
			{
				return (DWORD)(_time - currentTime);
			}
			else
			{
				return 0;
			}
		}
		return (DWORD)(_time - current);
	}
	/**
	* 描述:重载()运算符,检测是否到了触发时间
	* 返回值:
	* 参数:current:检测触发器是否到得当前时间
	**/
	bool operator()(DWORD current)
	{
		if(_time <= current || ( _time >= 0xffff0000 && current <= 60000) )
		{
			_time = current; 
			_time += _long;
			return true;
		}
		return false;
	}
private:
	/**
	* 描叙:定时器的间隔，单位毫秒
	**/
	DWORD _long;
	/**
	* 描述:上一次检测定时器的时间
	**/
	uint64	_time;
};
