#pragma once
#include "MyString.h"

//统计运行中，某个区段代码的执行时间
#include <windows.h>
#include <map>
#include <stack>
#include <functional>
#include <list>
#include <vector>
//using namespace std;

extern void appUnwindf( const CHAR* Fmt, ... );

/*#ifdef _DEBUG
	#define _DO_GUARD_ 0
#endif*/
#define _DO_GUARD_ 1

#if !_DO_GUARD_
#define guardfunc			{
#define guard(func)			{
#define unguard				}
#define unguardf(msg)		}
#else
#define guardfunc			{static const char __FUNC_NAME__[]=__FUNCTION__; try{
#define guard(func)			{static const char __FUNC_NAME__[]=#func; try{
#define unguard				}catch(char*Err){throw Err;}catch(...){appUnwindf("%s",__FUNC_NAME__); throw;}}
#define unguardf(msg)		}catch(char*Err){throw Err;}catch(...){appUnwindf("%s",__FUNC_NAME__); appUnwindf msg; throw;}}

//#define guardfunc			{DWORD dwStartTimeguardfunc = HQ_TimeGetTime(); static const char __FUNC_NAME__[]=__FUNCTION__; try{
//#define guard(func)			{DWORD dwStartTimeguardfunc = HQ_TimeGetTime(); static const char __FUNC_NAME__[]=#func; try{
//#define unguard				}catch(char*Err){throw Err;}catch(...){appUnwindf("%s",__FUNC_NAME__); throw;} if( HQ_TimeGetTime() - dwStartTimeguardfunc > 300 && HQ_TimeGetTime() - dwStartTimeguardfunc < 10000){char szBufguardfunc[256];_snprintf( szBufguardfunc, 256, "%s = %d", __FUNC_NAME__, HQ_TimeGetTime() - dwStartTimeguardfunc );OutputDebugString( szBufguardfunc );} }
//#define unguardf(msg)		}catch(char*Err){throw Err;}catch(...){appUnwindf("%s",__FUNC_NAME__); appUnwindf msg; throw;}}

#endif

//
//#if !_DO_GUARD_
//#define guardfunc
//#define guard(func)			
//#define unguard				
//#define unguardf(msg)
//#else
//#define guardfunc			GUARD gd(__FUNCTION__)
//#define guard(func)			GUARD gd(#func)
//#define unguard				
//#define unguardf(msg)		
//#endif
//
//class GUARD
//{
//public:
//	GUARD(const char* szLog);
//
//	virtual ~GUARD();
//private:
//	friend long  WINAPI UnHandledExceptionFilter(_EXCEPTION_POINTERS* pExceptionInfo);
//
//	static std::vector<std::string> m_stack;
//};

void InitSEH();

class CFuncPerformanceLog
{
public:
	enum TIMER_COMMAND 
	{ 
		TIMER_RESET, 
		TIMER_START, 
		TIMER_STOP, 
		TIMER_ADVANCE,
		TIMER_GETABSOLUTETIME, 
		TIMER_GETAPPTIME, 
		TIMER_GETELAPSEDTIME 
	};

protected:
	DWORD m_dwStartLogTick;
	struct SPeriod
	{
		BOOL bBeginPeriod;
		DWORD dwCallTimes;
		// realrender added 2004.08.02 for QueryPerformanceFrequency
		float fAbsTime;
		float fAllPeriod;
		// realrender added 2004.08.03
		//SPeriod* pMe;
		SPeriod* pParent;
		SPeriod():	bBeginPeriod(FALSE),
					dwCallTimes(0),
					fAbsTime(0.0f),
					fAllPeriod(0.0f),
					//pMe(this),
					pParent(NULL){}
	};
	
	typedef std::map<CMyString,SPeriod,std::less<CMyString> > mapPeriod;
	mapPeriod m_map;
	std::stack<SPeriod*> m_stack;

	char	m_szFile[ 200 ];
public:
	CFuncPerformanceLog(void);
	~CFuncPerformanceLog(void);

	void WriteLog();
	void BeginPeriod( char* lpName );
	void EndPeriod( char* lpName );

	float __stdcall HQ_Timer( TIMER_COMMAND command );

	void SetFile( char *szFile )
	{
		memset( m_szFile, 0, sizeof(m_szFile) );
		strncpy(m_szFile, szFile, sizeof(m_szFile)-1);
	}
};
class CTimeLog
{
public:
	CTimeLog(const char *funcname);
	virtual ~CTimeLog();
	const char* pString;
};

extern CFuncPerformanceLog gTrueTime;
static DWORD HQ_TimeGetTime()
{ return timeGetTime(); }
#define OUTTIMERATE     5000
#define OUTTIMECODERATE 200
#define USETRUETIME
#ifdef USETRUETIME
#define BEGINFUNCPERLOG(x) gTrueTime.BeginPeriod(x);
#define ENDFUNCPERLOG(x) gTrueTime.EndPeriod(x);
#define OUTFUNCPERLOG gTrueTime.WriteLog();

#define TRUETIMEBEGIN BEGINFUNCPERLOG
#define TRUETIMEEND ENDFUNCPERLOG
#define TRUETIMEFUNC() CTimeLog gTrueTime_localvar(__FUNCTION__);
#define TRUETIMEBLOCK(a) CTimeLog gTrueTime_localvar(a);

#else
#define BEGINFUNCPERLOG(x)
#define ENDFUNCPERLOG(x)

#define TRUETIMEFUNC()
#define TRUETIMEBLOCK(a)
#endif
