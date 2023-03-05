#ifndef _H_C_LOGGR_C_H_
#define _H_C_LOGGR_C_H_

#include <stdio.h>
#include <assert.h>
#include <string>
#include <map>

enum logtypelog_
{
	enum_log_type_assert = 0,
	enum_log_type_error,
	enum_log_type_log,
	LOG_PRIORITY_ERROR,
	LOG_PRIORITY_WARNING,
	LOG_PRIORITY_CRITICAL,
	LOG_PRIORITY_NOTICE,
	LOG_PRIORITY_INFO,
	LOG_PRIORITY_DEBUG,
	LOG_PRIORITY_NOTSET,
	enum_log_type_max=10,
};

#define LOG_MESSAGE CLogMgr::LOG

/*默认主目录以及默认文件名   dir1/s_type_name_s_default_filename */
static const char *s_type_name[enum_log_type_max] = {"_assert_log_", "_error_log_", "_log_log_",
"_p_error_log_", "_p_waring_log_", "_p_critical_log_","_p_notice_log_", "_p_info_log_", "_p_debug_log_",
"_p_notset_log_"
};




struct l_fileinfo
{
	FILE *fp;char last_filename[256];
};

struct filelog
{
	std::string dir1;
	std::string filename;
	l_fileinfo loggroup[enum_log_type_max];
};

class CLogMgr
{
public:
	CLogMgr();
	~CLogMgr();
	static void LOG(std::string  messageid,unsigned int type,  const char *fmt, ...);
	static void LOG(std::string  messageid,unsigned int type,std::string & msg)
	{
		CLogMgr::LOG(messageid,type,"%s",msg.c_str());
	}
	filelog logmgr; 
	static CLogMgr * GetLog(std::string name);
	static void printf( const char *string, ... );
};
#endif

