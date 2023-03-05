#include "Funcperformancelog.h"

#pragma comment(lib,"winmm.lib")
#pragma comment(lib, "shlwapi.lib")

#define GetTime timeGetTime

#define XML_CRASH_LOG_FILE   "..\\Output\\Crash.config"
#define FUNCPERFORMANCE_FILE "..\\Output\\Performance.log"

CHAR GErrorHist[4096]="";

CFuncPerformanceLog gTrueTime;

CFuncPerformanceLog::CFuncPerformanceLog()
{
    //m_dwStartLogTick = GetTime();
    HQ_Timer( TIMER_START );
    SetFile( FUNCPERFORMANCE_FILE );
}

CFuncPerformanceLog::~CFuncPerformanceLog()
{
    Output();
}

void CFuncPerformanceLog::Output( bool bOutClearHistory /*= false*/)
{
    //static bool volatile bHaveWrite = false;
    //if ( bHaveWrite)
    //    return;

    FILE* fp = NULL;
    
    char dbuffer[9];
    char tbuffer[9];

    if( m_map.size() <= 0 )
        return;

    _strdate( dbuffer );
    _strtime( tbuffer );
    fp = fopen( m_szFile,"ab" );
    if( !fp )
        return;

#ifdef _DEBUG
    fprintf( fp,"Debug version   ==========时间:%s %s==========\r\n",dbuffer,tbuffer );
#else
    fprintf( fp,"Release version ==========时间:%s %s==========\r\n",dbuffer,tbuffer );
#endif
    
    //DWORD iTotal = GetTickCount() - m_dwStartLogTick;

    {   
        CSALocker locker(this);
        float fTotal = HQ_Timer( TIMER_GETAPPTIME );
        fprintf( fp,"Total:%d\r\n",(DWORD)(fTotal*1000) );
        mapPeriod::iterator it = m_map.begin();
        fprintf( fp,"performance information:\r\n" );
        fprintf( fp,"|%-30s|%-11s|%-11s|%-15s|%-12s|\r\n","功能","花费时间","调用次数","平均调用时间","总百分比" );
        for( ; it != m_map.end();  ++it )
        {
            fprintf( fp, "|%-30s|%11d|%11d|%15f|%12f|\r\n",
                (*it).first.c_str(),
                //(*it).second.dwAllPeriod,
                DWORD((*it).second.fAllPeriod*1000),
                (*it).second.dwCallTimes,
                (float)((*it).second.fAllPeriod*1000/(float)(*it).second.dwCallTimes),
                //((float)((*it).second.dwAllPeriod)/(float)iTotal)*100.0f );
                (*it).second.fAllPeriod/fTotal*100.0f );
        }

        if ( bOutClearHistory)
        { m_map.clear();}
    }
    
    
    fclose( fp );
    
    //bHaveWrite = true;
}

void CFuncPerformanceLog::BeginPeriod( char* lpName )
{
    SPeriod period;
    
    {
        CSALocker locker(this);
        mapPeriod::iterator it = m_map.find( lpName );
        if( it == m_map.end() )
        {
            period.bBeginPeriod = TRUE;
            period.fAbsTime = HQ_Timer( TIMER_GETABSOLUTETIME );
            period.dwCallTimes = 0;
            period.fAllPeriod = 0;
            period.pParent = NULL;
            
            //if( !m_stack.empty() )
            //{
            //    period.pParent = m_stack.top();
            //    m_stack.push( &
            //}
            
            m_map.insert( mapPeriod::value_type(lpName,period) );
        }
        else
        {
            (*it).second.bBeginPeriod = TRUE;
            (*it).second.fAbsTime = HQ_Timer( TIMER_GETABSOLUTETIME );
        }
    }
}

void CFuncPerformanceLog::EndPeriod( char* lpName )
{
    {
        CSALocker locker(this);
        mapPeriod::iterator it = m_map.find( lpName );
        if( it == m_map.end() || !(*it).second.bBeginPeriod )
            return;

        //DWORD dwTick = GetTime();
        //dwTick -= (*it).second.dwPeriod;
        //(*it).second.dwAllPeriod += dwTick;

        float fTime = HQ_Timer( TIMER_GETABSOLUTETIME );
        fTime -= (*it).second.fAbsTime;
        (*it).second.fAllPeriod += fTime;
        (*it).second.dwCallTimes ++;
    }
}

CTimeLog::CTimeLog(const char *funcname)
{
    guardfunc
    assert( funcname );
    pString = funcname; 
    gTrueTime.BeginPeriod( (char*)pString );
    unguard;
}
CTimeLog::~CTimeLog()
{
    guardfunc
    gTrueTime.EndPeriod( (char*)pString );
    unguard;
}

//-----------------------------------------------------------------------------
// Name: DXUtil_Timer()
// Desc: Performs timer opertations. Use the following commands:
//          TIMER_RESET           - to reset the timer
//          TIMER_START           - to start the timer
//          TIMER_STOP            - to stop (or pause) the timer
//          TIMER_ADVANCE         - to advance the timer by 0.1 seconds
//          TIMER_GETABSOLUTETIME - to get the absolute system time
//          TIMER_GETAPPTIME      - to get the current time
//          TIMER_GETELAPSEDTIME  - to get the time that elapsed between 
//                                  TIMER_GETELAPSEDTIME calls
//-----------------------------------------------------------------------------
float __stdcall CFuncPerformanceLog::HQ_Timer( TIMER_COMMAND command )
{
    static BOOL     m_bTimerInitialized = FALSE;
    static BOOL     m_bUsingQPF         = FALSE;
    static BOOL     m_bTimerStopped     = TRUE;
    static LONGLONG m_llQPFTicksPerSec  = 0;

    // Initialize the timer
    if( FALSE == m_bTimerInitialized )
    {
        m_bTimerInitialized = TRUE;

        // Use QueryPerformanceFrequency() to get frequency of timer.  If QPF is
        // not supported, we will timeGetTime() which returns milliseconds.
        LARGE_INTEGER qwTicksPerSec;
        m_bUsingQPF = QueryPerformanceFrequency( &qwTicksPerSec );
        if( m_bUsingQPF )
            m_llQPFTicksPerSec = qwTicksPerSec.QuadPart;
    }

    if( m_bUsingQPF )
    {
        static LONGLONG m_llStopTime        = 0;
        static LONGLONG m_llLastElapsedTime = 0;
        static LONGLONG m_llBaseTime        = 0;
        double fTime;
        double fElapsedTime;
        LARGE_INTEGER qwTime;

        // Get either the current time or the stop time, depending
        // on whether we're stopped and what command was sent
        if( m_llStopTime != 0 && command != TIMER_START && command != TIMER_GETABSOLUTETIME)
            qwTime.QuadPart = m_llStopTime;
        else
            QueryPerformanceCounter( &qwTime );

        // Return the elapsed time
        if( command == TIMER_GETELAPSEDTIME )
        {
            fElapsedTime = (double) ( qwTime.QuadPart - m_llLastElapsedTime ) / (double) m_llQPFTicksPerSec;
            m_llLastElapsedTime = qwTime.QuadPart;
            return (FLOAT) fElapsedTime;
        }

        // Return the current time
        if( command == TIMER_GETAPPTIME )
        {
            double fAppTime = (double) ( qwTime.QuadPart - m_llBaseTime ) / (double) m_llQPFTicksPerSec;
            return (FLOAT) fAppTime;
        }

        // Reset the timer
        if( command == TIMER_RESET )
        {
            m_llBaseTime        = qwTime.QuadPart;
            m_llLastElapsedTime = qwTime.QuadPart;
            m_llStopTime        = 0;
            m_bTimerStopped     = FALSE;
            return 0.0f;
        }

        // Start the timer
        if( command == TIMER_START )
        {
            if( m_bTimerStopped )
                m_llBaseTime += qwTime.QuadPart - m_llStopTime;
            m_llStopTime = 0;
            m_llLastElapsedTime = qwTime.QuadPart;
            m_bTimerStopped = FALSE;
            return 0.0f;
        }

        // Stop the timer
        if( command == TIMER_STOP )
        {
            m_llStopTime = qwTime.QuadPart;
            m_llLastElapsedTime = qwTime.QuadPart;
            m_bTimerStopped = TRUE;
            return 0.0f;
        }

        // Advance the timer by 1/10th second
        if( command == TIMER_ADVANCE )
        {
            m_llStopTime += m_llQPFTicksPerSec/10;
            return 0.0f;
        }

        if( command == TIMER_GETABSOLUTETIME )
        {
            fTime = qwTime.QuadPart / (double) m_llQPFTicksPerSec;
            return (FLOAT) fTime;
        }

        return -1.0f; // Invalid command specified
    }
    else
    {
        // Get the time using timeGetTime()
        static double m_fLastElapsedTime  = 0.0;
        static double m_fBaseTime         = 0.0;
        static double m_fStopTime         = 0.0;
        double fTime;
        double fElapsedTime;

        // Get either the current time or the stop time, depending
        // on whether we're stopped and what command was sent
        if( m_fStopTime != 0.0 && command != TIMER_START && command != TIMER_GETABSOLUTETIME)
            fTime = m_fStopTime;
        else
            fTime = timeGetTime() * 0.001;

        // Return the elapsed time
        if( command == TIMER_GETELAPSEDTIME )
        {   
            fElapsedTime = (double) (fTime - m_fLastElapsedTime);
            m_fLastElapsedTime = fTime;
            return (FLOAT) fElapsedTime;
        }

        // Return the current time
        if( command == TIMER_GETAPPTIME )
        {
            return (FLOAT) (fTime - m_fBaseTime);
        }

        // Reset the timer
        if( command == TIMER_RESET )
        {
            m_fBaseTime         = fTime;
            m_fLastElapsedTime  = fTime;
            m_fStopTime         = 0;
            m_bTimerStopped     = FALSE;
            return 0.0f;
        }

        // Start the timer
        if( command == TIMER_START )
        {
            if( m_bTimerStopped )
                m_fBaseTime += fTime - m_fStopTime;
            m_fStopTime = 0.0f;
            m_fLastElapsedTime  = fTime;
            m_bTimerStopped = FALSE;
            return 0.0f;
        }

        // Stop the timer
        if( command == TIMER_STOP )
        {
            m_fStopTime = fTime;
            m_fLastElapsedTime  = fTime;
            m_bTimerStopped = TRUE;
            return 0.0f;
        }

        // Advance the timer by 1/10th second
        if( command == TIMER_ADVANCE )
        {
            m_fStopTime += 0.1f;
            return 0.0f;
        }

        if( command == TIMER_GETABSOLUTETIME )
        {
            return (FLOAT) fTime;
        }

        return -1.0f; // Invalid command specified
    }
}

//long  WINAPI UnHandledExceptionFilter(_EXCEPTION_POINTERS* pExceptionInfo)
//{
//    std::string str;
//    while (!GUARD::m_stack.empty())
//    {
//        str += GUARD::m_stack.back();
//        str += "\n";
//        GUARD::m_stack.pop_back();
//    }
//
//    MessageBoxA(NULL, str.c_str(), NULL, NULL); 
//    return 0;
//}

//
//void InitSEH()
//{
//    SetUnhandledExceptionFilter(UnHandledExceptionFilter);
//}

void appUnwindf( const CHAR* Fmt, ... )
{
    guardfunc
    if( !Fmt )
        return;
    char TempStr[4096] = {0};
    va_list    va;
    va_start( va, Fmt );
    wvnsprintf(TempStr, sizeof(TempStr)-1, Fmt, va );
    va_end( va );

    static INT Count=0;

    if( Count++ )
    {
    //    strncat( GErrorHist, "<Fun>", 4096 );
    //    strncat( GErrorHist, "</Fun>", 4096 );
    }

    char TempStr1[4096] = {0};
    _snprintf(TempStr1, sizeof(TempStr1)-1, "<Fun>%s</Fun>", TempStr );
    strncat( GErrorHist, TempStr1, 4096 );

    static char szAppName[MAX_PATH + 1] = "";
    static BOOL bGeted = FALSE;
    if( !bGeted )
    {    
        bGeted = TRUE;
        GetModuleFileName( NULL, szAppName, MAX_PATH );

        size_t freesize = sizeof(szAppName) - strlen(szAppName);
        /*strncat( szAppName, ".config", freesize-1 );*/
        sprintf_s( szAppName, MAX_PATH, "%s", XML_CRASH_LOG_FILE );
    }
    if( strlen( szAppName ) > 0 )
    {
        FILE *fp = fopen( szAppName, "w" );
        if( fp )
        {
            //fwrite
            const char* szTile = "<FunList>";
            const char* szEndTile = "</FunList>";
            fwrite( szTile, strlen(szTile), 1, fp );
            fwrite( GErrorHist, strlen( GErrorHist ), 1, fp );
            fwrite( szEndTile, strlen(szEndTile), 1, fp );
        }
        if( fp )
            fclose(fp);

    }
    
    //MessageBox( NULL, GErrorHist, "**", MB_OK );
    unguard;
}