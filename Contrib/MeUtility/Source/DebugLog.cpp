#include "DebugLog.h"
#include <ctime>
#include <fstream>
#include <string>
#include <windows.h>

#pragma warning ( push )
#pragma warning ( disable : 4996 )

_DEBUGLOG_BEGIN_

const char* const logTitle		= "/\\\\\\ Game Log ///\\ -> ";
const char * const LOGFILE_NAME = "log.txt";

 CLogFile clog( e_info );
 CLogFile cerr( e_error );
 CLogFile cwarn( e_warning );
 CLogFile cout( e_comment );

std::ofstream CLogFile::m_file;
bool CLogFile::m_bInitialized = false;
bool CLogFile::m_bModeError = false;
bool CLogFile::m_bModeComment = false;
bool CLogFile::m_bModeWarning = false;
bool CLogFile::m_bModeInfo = false;

CLogFile::CLogFile( enumLogMode elm )
{
    m_eMode = elm;
}

CLogFile::~CLogFile()
{
    if( m_bInitialized )
    {
        m_file.close();
        m_bInitialized = false;
    }
}

void CLogFile::init()
{
    if( !m_bInitialized )
    {
        m_file.open( LOGFILE_NAME );

        if( !m_file )
            m_bInitialized = false;
        else
        {
            m_bInitialized = true;

            std::time_t t = std::time( NULL );
            std::tm *tme = std::localtime( &t );

            m_file << logTitle<<" "
                    << tme->tm_mday << "/"
                    << tme->tm_mon + 1 << "/"
                    << (tme->tm_year + 1900) << " "
                    << tme->tm_hour << ":"
                    << tme->tm_min << ":"
                    << tme->tm_sec << "\n";

            m_file << "==========================================================================\n";
        }
    }
}

CLogFile& CLogFile::file_line_func( const char *file, const unsigned int line, const char * func )
{
    setmode();
    std::string str = file;
    m_file<< str << "(" << line << ")::" <<func;
    return (*this);
}

void CLogFile::setmode()
{
    init();
    end();
    start();
}

void CLogFile::start()
{
    if( !m_bInitialized )
        return;

    if( m_eMode == e_comment && !m_bModeComment )
    {
        m_file << "COMMENT:" ;

        m_bModeComment = true;
        m_bModeInfo = false;
        m_bModeError = false;
        m_bModeWarning = false; 
    }
    else if( m_eMode == e_error && !m_bModeError )
    {
        m_file << "ERROR:" ;

        m_bModeError = true;
        m_bModeInfo = false;
        m_bModeComment = false; 
        m_bModeWarning = false; 
    }
    else if( m_eMode == e_info && !m_bModeInfo )
    {
        m_file << "INFO:" ;

        m_bModeInfo = true;
        m_bModeError = false;
        m_bModeComment = false; 
        m_bModeWarning = false; 
    }
    else if( m_eMode == e_warning && !m_bModeWarning )
    {
        m_file << "WARNING:" ;

        m_bModeWarning = true;
        m_bModeInfo = false;
        m_bModeError = false;
        m_bModeComment = false; 
    }
}

void CLogFile::end()
{
    if( !m_bInitialized )
        return;

    if( m_bModeInfo && m_eMode != e_info )
    {
        m_file<< "";
    }
    else if( m_bModeError && m_eMode != e_error )
    {
        m_file<< "";
        m_file.flush();
    }
    else if( m_bModeComment && m_eMode != e_comment )
    {
        m_file<< "";
    }
    else if( m_bModeWarning && m_eMode != e_warning )
    {
        m_file<< "";
    }
}

 CLogFile& endl( CLogFile& l )
{
    l.m_file << "\n";
    l.m_file.flush();
    return l;
}
 CLogFile& endp( CLogFile& l )
{
    l.m_file << "\n";
    l.m_file.flush();
    l.m_bModeError = false;
    l.m_bModeInfo = false;
    l.m_bModeWarning = false;
    l.m_bModeComment = false;
    return l;
}
 CLogFile& tab( CLogFile& l )
{
    l.m_file << "    ";
    l.m_file.flush();
    return l;
}
 CLogFile& lbreak( CLogFile& l )
{
    l.m_file << "";
    l.m_file.flush();
    return l;
}

 CLogFile& time( CLogFile& l )
{
    static char FormatString[ 4096];
    SYSTEMTIME systime;

    GetLocalTime( &systime );
    _snprintf( FormatString, sizeof(FormatString)-1,
        "[%04d-%02d-%02d %02d:%02d:%02d]",
        systime.wYear,
        systime.wMonth,
        systime.wDay,
        systime.wHour,
        systime.wMinute,
        systime.wSecond );

    l.m_file << FormatString;

    return l;
}

_DEBUGLOG_END_

#pragma warning ( pop )
