#ifndef __DEBUG_LOG_H__
#define __DEBUG_LOG_H__

#include <fstream>

#define _DEBUGLOG_BEGIN_ namespace DebugLog {
#define _DEBUGLOG_END_ }

_DEBUGLOG_BEGIN_

// 日志模式定义
enum enumLogMode
{
    e_error		// 错误日志模式
    ,
    e_info		// 信息日志模式
    ,
    e_comment	// 注释日志模式
    ,
    e_warning	// 警告日志模式
    ,
};

// 日志类
class CLogFile
{
public:

    CLogFile( enumLogMode elm );
    ~CLogFile();

    CLogFile& file_line_func( const char* file, const unsigned int line, const char* func );

    template<class T> CLogFile& operator << ( T data )
    {
        setmode();
        if( m_bInitialized )
        {
            m_file << data;
        }
        return (*this);
    }

    template<> CLogFile& operator << ( CLogFile& (*_manip)(CLogFile&) )
    {
        return _manip(*this);
    }

    template<> CLogFile& operator << ( bool b )
    {
        setmode();
        if( m_bInitialized )
        {
            m_file << ( (b==true)?"true":"false");
        }
        return (*this);
    }

    friend  CLogFile& endl( CLogFile& l );
    friend  CLogFile& endp( CLogFile& l );
    friend  CLogFile& tab( CLogFile& l );
    friend  CLogFile& lbreak( CLogFile& l );
    friend  CLogFile& time( CLogFile& l );

private:

    static std::ofstream m_file;
    static bool m_bInitialized;
    static bool m_bModeError;
    static bool m_bModeInfo;
    static bool m_bModeComment;
    static bool m_bModeWarning;
    enumLogMode m_eMode;

    void start();
    void end();
    void setmode();
    void init();
};

extern  CLogFile clog;
extern  CLogFile cerr;
extern  CLogFile cwarn;
extern  CLogFile cout;

_DEBUGLOG_END_

#define DL_FATAL() { DebugLog::cerr << "failed in:" << endl; \
        DebugLog::cerr.file_line_func(__FILE__,__LINE__,__FUNCTION__); }

#endif // __DEBUG_LOG_H__
