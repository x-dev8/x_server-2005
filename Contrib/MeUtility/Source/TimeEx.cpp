#include "TimeEx.h"


#pragma warning(push)
#pragma warning(disable : 4996)

TimeSpan::TimeSpan() throw() :
m_timeSpan(0)
{
}

TimeSpan::TimeSpan( __time64_t time ) throw() :
m_timeSpan( time )
{
}

TimeSpan::TimeSpan( DWORD dwTime /* */)
{
	//Min TimeEx
	//∫¡√Îº∂
	LONG dayTime = 24 * 60 * 60;
	int HoursTime = 60*60;
	int nMinsTime = 60;
	//int nSecsTime = 1;

	LONG lDays = dwTime / ( dayTime );
	int nHours = ( dwTime - lDays*( dayTime ) ) / HoursTime;
	int nMins = ( dwTime - lDays*( dayTime ) - nHours*HoursTime )/nMinsTime;
	int nSecs = ( dwTime - lDays*( dayTime ) - nHours*HoursTime - nMins*nMinsTime);

	
	TimeSpan TimeSpanT( lDays, nHours, nMins, nSecs );
	*this = TimeSpanT;

}


TimeSpan::TimeSpan(LONG lDays, int nHours, int nMins, int nSecs) throw()
{
	m_timeSpan = nSecs + 60* (nMins + 60* (nHours + __int64(24) * lDays));
}

LONGLONG TimeSpan::GetDays() const throw()
{
	return( m_timeSpan/(24*3600) );
}

LONGLONG TimeSpan::GetTotalHours() const throw()
{
	return( m_timeSpan/3600 );
}

LONG TimeSpan::GetHours() const throw()
{
	return( LONG( GetTotalHours()-(GetDays()*24) ) );
}

LONGLONG TimeSpan::GetTotalMinutes() const throw()
{
	return( m_timeSpan/60 );
}

LONG TimeSpan::GetMinutes() const throw()
{
	return( LONG( GetTotalMinutes()-(GetTotalHours()*60) ) );
}

LONGLONG TimeSpan::GetTotalSeconds() const throw()
{
	return( m_timeSpan );
}

LONG TimeSpan::GetSeconds() const throw()
{
	return( LONG( GetTotalSeconds()-(GetTotalMinutes()*60) ) );
}

__time64_t TimeSpan::GetTimeSpan() const throw()
{
	return( m_timeSpan );
}

TimeSpan TimeSpan::operator+( TimeSpan span ) const throw()
{
	return( TimeSpan( m_timeSpan+span.m_timeSpan ) );
}

TimeSpan TimeSpan::operator-( TimeSpan span ) const throw()
{
	return( TimeSpan( m_timeSpan-span.m_timeSpan ) );
}

TimeSpan& TimeSpan::operator+=( TimeSpan span ) throw()
{
	m_timeSpan += span.m_timeSpan;
	return( *this );
}

TimeSpan& TimeSpan::operator-=( TimeSpan span ) throw()
{
	m_timeSpan -= span.m_timeSpan;
	return( *this );
}

bool TimeSpan::operator==( TimeSpan span ) const throw()
{
	return( m_timeSpan == span.m_timeSpan );
}

bool TimeSpan::operator!=( TimeSpan span ) const throw()
{
	return( m_timeSpan != span.m_timeSpan );
}

bool TimeSpan::operator<( TimeSpan span ) const throw()
{
	return( m_timeSpan < span.m_timeSpan );
}

bool TimeSpan::operator>( TimeSpan span ) const throw()
{
	return( m_timeSpan > span.m_timeSpan );
}

bool TimeSpan::operator<=( TimeSpan span ) const throw()
{
	return( m_timeSpan <= span.m_timeSpan );
}

bool TimeSpan::operator>=( TimeSpan span ) const throw()
{
	return( m_timeSpan >= span.m_timeSpan );
}


/////////////////////////////////////////////////////////////////////////////
// TimeEx
/////////////////////////////////////////////////////////////////////////////

TimeEx TimeEx::GetCurrentTime() throw()
{
	return( TimeEx( ::_time64( NULL ) ) );
}

BOOL  TimeEx::IsValidFILETIME(const FILETIME& fileTime) throw()
{
	FILETIME localTime;
	if (!FileTimeToLocalFileTime(&fileTime, &localTime))
	{
		return FALSE;
	}

	// then convert that time to system time
	SYSTEMTIME sysTime;
	if (!FileTimeToSystemTime(&localTime, &sysTime))
	{
		return FALSE;
	}

	return TRUE;
}

TimeEx::TimeEx() throw() :
m_time(0)
{
}

TimeEx::TimeEx( __time64_t time )  throw():
m_time( time )
{
}

TimeEx::TimeEx(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec,
			   int nDST)
{
#pragma warning (push)
#pragma warning (disable: 4127)  // conditional expression constant

	//ATLENSURE( nYear >= 1900 );
	//ATLENSURE( nMonth >= 1 && nMonth <= 12 );
	//ATLENSURE( nDay >= 1 && nDay <= 31 );
	//ATLENSURE( nHour >= 0 && nHour <= 23 );
	//ATLENSURE( nMin >= 0 && nMin <= 59 );
	//ATLENSURE( nSec >= 0 && nSec <= 59 );

#pragma warning (pop)

	struct tm atm;

	atm.tm_sec = nSec;
	atm.tm_min = nMin;
	atm.tm_hour = nHour;
	atm.tm_mday = nDay;
	atm.tm_mon = nMonth - 1;        // tm_mon is 0 based
	atm.tm_year = nYear - 1900;     // tm_year is 1900 based
	atm.tm_isdst = nDST;

	m_time = _mktime64(&atm);
//	ATLASSUME(m_time != -1);       // indicates an illegal input time
	if(m_time == -1)
	{
	//	AtlThrow(E_INVALIDARG);
	}
}

TimeEx::TimeEx(WORD wDosDate, WORD wDosTime, int nDST)
{
	struct tm atm;
	atm.tm_sec = (wDosTime & ~0xFFE0) << 1;
	atm.tm_min = (wDosTime & ~0xF800) >> 5;
	atm.tm_hour = wDosTime >> 11;

	atm.tm_mday = wDosDate & ~0xFFE0;
	atm.tm_mon = ((wDosDate & ~0xFE00) >> 5) - 1;
	atm.tm_year = (wDosDate >> 9) + 80;
	atm.tm_isdst = nDST;
	m_time = _mktime64(&atm);
//	ATLASSUME(m_time != -1);       // indicates an illegal input time

	if(m_time == -1)
	{
//		AtlThrow(E_INVALIDARG);
	}

}

TimeEx::TimeEx(const SYSTEMTIME& sysTime, int nDST)
{
	if (sysTime.wYear < 1900)
	{
		__time64_t time0 = 0L;
		TimeEx timeT(time0);
		*this = timeT;
	}
	else
	{
		TimeEx timeT(
			(int)sysTime.wYear, (int)sysTime.wMonth, (int)sysTime.wDay,
			(int)sysTime.wHour, (int)sysTime.wMinute, (int)sysTime.wSecond,
			nDST);
		*this = timeT;
	}
}

TimeEx::TimeEx(const FILETIME& fileTime, int nDST)
{
	// first convert file time (UTC time) to local time
	FILETIME localTime;
	if (!FileTimeToLocalFileTime(&fileTime, &localTime))
	{
		m_time = 0;
//		AtlThrow(E_INVALIDARG);
		return;
	}

	// then convert that time to system time
	SYSTEMTIME sysTime;
	if (!FileTimeToSystemTime(&localTime, &sysTime))
	{
		m_time = 0;
//		AtlThrow(E_INVALIDARG);		
		return;
	}

	// then convert the system time to a time_t (C-runtime local time)
	TimeEx timeT(sysTime, nDST);
	*this = timeT;
}

TimeEx& TimeEx::operator=( __time64_t time ) throw()
{
	m_time = time;

	return( *this );
}

TimeEx& TimeEx::operator+=( TimeSpan span ) throw()
{
	m_time += span.GetTimeSpan();

	return( *this );
}

TimeEx& TimeEx::operator-=( TimeSpan span ) throw()
{
	m_time -= span.GetTimeSpan();

	return( *this );
}

TimeSpan TimeEx::operator-( TimeEx time ) const throw()
{
	return( TimeSpan( m_time-time.m_time ) );
}

TimeEx TimeEx::operator-( TimeSpan span ) const throw()
{
	return( TimeEx( m_time-span.GetTimeSpan() ) );
}

TimeEx TimeEx::operator+( TimeSpan span ) const throw()
{
	return( TimeEx( m_time+span.GetTimeSpan() ) );
}

bool TimeEx::operator==( TimeEx time ) const throw()
{
	return( m_time == time.m_time );
}

bool TimeEx::operator!=( TimeEx time ) const throw()
{
	return( m_time != time.m_time );
}

bool TimeEx::operator<( TimeEx time ) const throw()
{
	return( m_time < time.m_time );
}

bool TimeEx::operator>( TimeEx time ) const throw()
{
	return( m_time > time.m_time );
}

bool TimeEx::operator<=( TimeEx time ) const throw()
{
	return( m_time <= time.m_time );
}

bool TimeEx::operator>=( TimeEx time ) const throw()
{
	return( m_time >= time.m_time );
}

#if !_SECURE_ATL

//_ATL_INSECURE_DEPRECATE("Pass an output time structure to TimeEx::GetGmtTm")
struct tm* TimeEx::GetGmtTm() const throw()
{
	return _gmtime64(&m_time);
}

//_ATL_INSECURE_DEPRECATE("Pass an output time structure to TimeEx::GetLocalTm")
struct tm* TimeEx::GetLocalTm() const throw()
{
#pragma warning(push)
#pragma warning(disable : 4996)
	return _localtime64(&m_time);
#pragma warning(pop)
}

#endif // !_SECURE_ATL

struct tm* TimeEx::GetGmtTm(struct tm* ptm) const
{
#if _SECURE_ATL
	// Ensure ptm is valid
	ATLENSURE( ptm != NULL );

	if (ptm != NULL)
	{
		struct tm ptmTemp;
		errno_t err = _gmtime64_s(&ptmTemp, &m_time);

		// Be sure the call succeeded
		if(err != 0) { return NULL; }

		*ptm = ptmTemp;
		return ptm;
	}

	return NULL;
#else
	if (ptm != NULL)
	{
		struct tm * ptmTemp;
		ptmTemp = _gmtime64(&m_time);

		if(ptmTemp == NULL)
			return NULL;

		*ptm = *ptmTemp;

		return ptm;
	}
	else
		return _gmtime64(&m_time);
#endif
}

struct tm* TimeEx::GetLocalTm(struct tm* ptm) const
{
#if _SECURE_ATL
	// Ensure ptm is valid
	ATLENSURE( ptm != NULL );

	if (ptm != NULL)
	{
		struct tm ptmTemp;
		errno_t err = _localtime64_s(&ptmTemp, &m_time);

		if (err != 0)
		{
			return NULL;    // indicates that m_time was not initialized!
		}

		*ptm = ptmTemp;
		return ptm;
	}

	return NULL;
#else
	if (ptm != NULL)
	{
		struct tm* ptmTemp = _localtime64(&m_time);
		if (ptmTemp == NULL)
			return NULL;    // indicates the m_time was not initialized!

		*ptm = *ptmTemp;
		return ptm;
	}
	else
		return _localtime64(&m_time);
#endif
}

bool TimeEx::GetAsSystemTime(SYSTEMTIME& timeDest) const throw()
{
	struct tm ttm;
	struct tm* ptm;

	ptm = GetLocalTm(&ttm);

	if(!ptm) { return false; }

	timeDest.wYear = (WORD) (1900 + ptm->tm_year);
	timeDest.wMonth = (WORD) (1 + ptm->tm_mon);
	timeDest.wDayOfWeek = (WORD) ptm->tm_wday;
	timeDest.wDay = (WORD) ptm->tm_mday;
	timeDest.wHour = (WORD) ptm->tm_hour;
	timeDest.wMinute = (WORD) ptm->tm_min;
	timeDest.wSecond = (WORD) ptm->tm_sec;
	timeDest.wMilliseconds = 0;

	return true;
}

__time64_t TimeEx::GetTime() const throw()
{
	return( m_time );
}

int TimeEx::GetYear() const
{ 
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? (ptm->tm_year) + 1900 : 0 ; 
}

int TimeEx::GetMonth() const
{ 
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? ptm->tm_mon + 1 : 0;
}

int TimeEx::GetDay() const
{
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? ptm->tm_mday : 0 ; 
}

int TimeEx::GetHour() const
{
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? ptm->tm_hour : -1 ; 
}

int TimeEx::GetMinute() const
{
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? ptm->tm_min : -1 ; 
}

int TimeEx::GetSecond() const
{ 
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? ptm->tm_sec : -1 ;
}

int TimeEx::GetDayOfWeek() const
{ 
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? ptm->tm_wday + 1 : 0 ;
}

#pragma warning(pop)
