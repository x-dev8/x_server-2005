/********************************************************************
Filename:     FuncPerformanceLog.h
MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_FUNCPERFORMANCELOG_H__
#define __UTILITY_FUNCPERFORMANCELOG_H__

#pragma once

#include "MeRTLibs.h"
#include "Mutex.h"

// #ifdef GAME_CLIENT
// 
// #define  ME_SET_CRT_DEBUG_FIELD(a) \
// 	_CrtSetDbgFlag((a) | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
// #define  ME_CLEAR_CRT_DEBUG_FIELD(a) \
// 	_CrtSetDbgFlag(~(a) & _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
// 
// #define ME_BEGIN_MEMORY_CHECK ME_SET_CRT_DEBUG_FIELD( _CRTDBG_DELAY_FREE_MEM_DF )
// #define ME_END_MEMORY_CHECK ME_CLEAR_CRT_DEBUG_FIELD( _CRTDBG_DELAY_FREE_MEM_DF )
// #define ME_MEMORY_CHECK if ( !_CrtCheckMemory() ) { LOG_MESSAGE( "ErrorInfo.log", LOG_PRIORITY_ERROR, "file:%s, line:%d, func:%s", __FILE__, __LINE__, __FUNCTION__); MessageBox( NULL, "找程序", "异常", MB_OKCANCEL );    }
// 
// class MeMemoryChecker
// {
// 	std::string _filename;
// 	int _line;
// 	std::string _func;
// 
// public:
// 	MeMemoryChecker(const std::string& filename, int line, const std::string& func)
// 		: _filename(filename), _line(line), _func(func)
// 	{ ME_BEGIN_MEMORY_CHECK; }
// 
// 	~MeMemoryChecker()
// 	{
// 		if ( !_CrtCheckMemory() )
// 		{
// 			LOG_MESSAGE( "ErrorInfo.log", LOG_PRIORITY_ERROR, "file:%s, line:%d, func:%s",
// 				_filename.c_str(), _line, _func.c_str());
// 			MessageBox( NULL, "内存错误，找程序！", "异常", MB_OK | MB_ICONERROR );
// 		}
// 
// 		ME_END_MEMORY_CHECK;
// 	}
// };
// 
// #define ME_MEMORY_CHECK_GUARD(name) MeMemoryChecker name(__FILE__, __LINE__, __FUNCTION__);
// 
// #endif

// 统计运行中，某个区段代码的执行时间
extern void appUnwindf( const CHAR* Fmt, ... );

#ifndef _DO_GUARD_
#define guardfunc            
#define guard(func)            
#ifdef GAME_CLIENT_TEMP
#define unguard             if ( !_CrtCheckMemory() ) { LOG_MESSAGE( "ErrorInfo.log", LOG_PRIORITY_ERROR, "file:%s, line:%d, func:%s", __FILE__, __LINE__, __FUNCTION__); MessageBox( NULL, "找程序", "异常", MB_OKCANCEL ); }   }
#define unguardf(msg)       if ( !_CrtCheckMemory() ) { LOG_MESSAGE( "ErrorInfo.log", LOG_PRIORITY_ERROR, "file:%s, line:%d, func:%s", __FILE__, __LINE__, __FUNCTION__); MessageBox( NULL, "找程序", "异常", MB_OKCANCEL ); }   }
#else
#define unguard               
#define unguardf(msg)        
#endif
#else
#define guardfunc            {static const char __FUNC_NAME__[]=__FUNCTION__; try{
#define guard(func)            {static const char __FUNC_NAME__[]=#func; try{
#define unguard                }catch(char*Err){throw Err;}catch(...){appUnwindf("%s",__FUNC_NAME__); throw;}}
#define unguardf(msg)        }catch(char*Err){throw Err;}catch(...){appUnwindf("%s",__FUNC_NAME__); appUnwindf msg; throw;}}

//#define guardfunc            {DWORD dwStartTimeguardfunc = HQ_TimeGetTime(); static const char __FUNC_NAME__[]=__FUNCTION__; try{
//#define guard(func)            {DWORD dwStartTimeguardfunc = HQ_TimeGetTime(); static const char __FUNC_NAME__[]=#func; try{
//#define unguard                }catch(char*Err){throw Err;}catch(...){appUnwindf("%s",__FUNC_NAME__); throw;} if( HQ_TimeGetTime() - dwStartTimeguardfunc > 300 && HQ_TimeGetTime() - dwStartTimeguardfunc < 10000){char szBufguardfunc[256];_snprintf( szBufguardfunc, 256, "%s = %d", __FUNC_NAME__, HQ_TimeGetTime() - dwStartTimeguardfunc );OutputDebugString( szBufguardfunc );} }
//#define unguardf(msg)        }catch(char*Err){throw Err;}catch(...){appUnwindf("%s",__FUNC_NAME__); appUnwindf msg; throw;}}

#endif

#define _EnterFunction try {

#define _EndFuction } \
    catch( std::exception& e) \
{ \
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"%s %s %s", __FUNCTION__, __LINE__, e.what() ); \
    return; \
}

class CFuncPerformanceLog : public CSemiAutoIntLock
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
    unsigned long m_dwStartLogTick;
    struct SPeriod
    {
        BOOL bBeginPeriod;
        DWORD dwCallTimes;
        float fAbsTime;
        float fAllPeriod;        
        //SPeriod* pMe;
        SPeriod* pParent;
        SPeriod() : bBeginPeriod(FALSE),dwCallTimes(0),fAbsTime(0.0f),fAllPeriod(0.0f),//pMe(this),
            pParent(NULL){}
    };

    typedef std::map< std::string,SPeriod > mapPeriod;
    typedef mapPeriod::iterator ItrMapPeriod;

    mapPeriod m_map;
    std::stack<SPeriod*> m_stack;
    char    m_szFile[ MAX_PATH ];

public:
    CFuncPerformanceLog();
    ~CFuncPerformanceLog();

    void BeginPeriod( char* lpName );
    void EndPeriod( char* lpName );

    float __stdcall HQ_Timer( TIMER_COMMAND command );

    void SetFile( char *szFile )
    {
        memset( m_szFile, 0, sizeof(m_szFile) );
        strncpy_s(m_szFile, sizeof( m_szFile ), szFile, sizeof(m_szFile)-1);
    }
    void Output( bool bOutClearHistory = false );
};

class CTimeLog
{
public:
    CTimeLog(const char *funcname);
    virtual ~CTimeLog();
    const char* pString;
};

extern CFuncPerformanceLog gTrueTime;
extern DWORD HQ_TimeGetTime();

#define USETRUETIME
#ifdef USETRUETIME
#define BEGINFUNCPERLOG(x) gTrueTime.BeginPeriod(x);
#define ENDFUNCPERLOG(x) gTrueTime.EndPeriod(x);

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

#define DECLARE_TIME_TEST \
    uint32 functime = 0; \
    uint32 spacetime = 0;

#define BEGIN_TIME_TEST( functionname ) \
    functime = HQ_TimeGetTime();

#define END_TIME_TEST( functionname ) END_TIME_TEST_1( functionname, 20 )

#define END_TIME_TEST_1( functionname, time ) \
    spacetime = HQ_TimeGetTime() - functime; \
    if ( spacetime > time ) \
    { \
        std::cout << functionname << "->elapse:" << spacetime << "/" << time << std::endl; \
    }

#endif // __UTILITY_FUNCPERFORMANCELOG_H__
