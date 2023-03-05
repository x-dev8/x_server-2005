#include "logmgr.h"
#include "LogFileObjectNameEx.h"
#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#include <direct.h>
#include <io.h>
#include <Errno.h>
#define my_mkdir _mkdir
#define snprintf _snprintf
#else
#include <sys/stat.h>
#include <sys/types.h>
#define my_mkdir(a) mkdir((a), 0777)
#endif

bool MakeEmbedFolder(std::string strFolderPath)
{
	std::string  strPath = strFolderPath;
	if (strPath[strPath.length()-1] != '\\')
	{
		strPath += "\\";
	}
	size_t nLength = strPath.length();
	for (size_t i = 0; i<nLength; i++)
	{
		if (strPath[i] == '\\')
		{
			std::string strFolder = strPath.substr(0, i);
			if (_mkdir(strFolder.c_str()) == ENOENT)
			{
				return false;
			}
		}
	}
	return true;
}

CLogMgr::CLogMgr()
{
	for (int i = 0; i < enum_log_type_max; ++i)
	{

		logmgr.loggroup[i].fp = NULL;
		logmgr.loggroup[i].last_filename[0] = 0;
	}
}
CLogMgr::~CLogMgr()
{
	for (int i = 0; i < enum_log_type_max; ++i)
	{
		if(logmgr.loggroup[i].fp)fclose(logmgr.loggroup[i].fp);
	}
};
std::map<std::string,CLogMgr*>  logMaps;
CLogMgr * CLogMgr::GetLog(std::string name)
{
	if(name.empty())return NULL;
	std::map<std::string,CLogMgr*>::const_iterator it = logMaps.find( name );
	if( it == logMaps.end() )
	{
		CLogMgr * log = new CLogMgr;
		std::string dir=name;
		int pos=name.find(".");
		if(pos!=std::string::npos)
			dir=name.substr(0,pos);
		log->logmgr.dir1=dir;
		log->logmgr.filename=name;
		logMaps[name] = log;
		return log;
	}
	return it->second;
}
void CLogMgr::LOG(std::string  messageid,unsigned int type, const char *fmt, ...)
{
	if(type==LOG_PRIORITY_DEBUG)return;
	if(strcmp(messageid.c_str(),"Info.log")==0)return;
	if( strcmp(messageid.c_str(),SYSTEMOBJECT)==0 )
	{
		va_list	args;
		va_start( args, fmt );
		vprintf(fmt, args);
		va_end( args );
		::printf("\n");
	}
// #endif
	
	CLogMgr * log_1=CLogMgr::GetLog(messageid);
	if(!log_1)return ;
	
	
	const char *directname;
	struct l_fileinfo *info;
	time_t tval;
	struct tm *currTM;
	char szDate[512] = {0};
	char szFile[512] = {0};
	char szPath[512] = {0};
#ifdef _TEST_WRITE_LOG_NEED_TIME
	int64 begin, end;
 #endif

	info = &log_1->logmgr.loggroup[type];
	directname = log_1->logmgr.dir1.c_str();

	if (!fmt)
		return;
	time(&tval);
	currTM = localtime(&tval);
	switch (type)
	{
	case enum_log_type_log:
		{
			snprintf(szDate, sizeof(szDate)-1, "%04d-%02d-%02d", currTM->tm_year+1900, currTM->tm_mon+1, currTM->tm_mday);
			my_mkdir("log");
			snprintf(szPath, sizeof(szPath)-1, "log/%s", directname);
			my_mkdir(szPath);
			snprintf(szPath, sizeof(szPath)-1, "log/%s/%s", directname, szDate);
			my_mkdir(szPath);
			snprintf(szFile, sizeof(szFile)-1, "%s/%s_%02d_%s", szPath, s_type_name[type],currTM->tm_hour,log_1->logmgr.filename.c_str());
		}
		break;
	default:
		{
			my_mkdir("log");
			snprintf(szPath, sizeof(szPath)-1, "log/%s", directname);
			my_mkdir(szPath);
			snprintf(szFile, sizeof(szFile)-1, "log/%s/%s_%s", directname, s_type_name[type],log_1->logmgr.filename.c_str());
		}
	}
	
	if (strcmp(info->last_filename, szFile) != 0)
	{
		strncpy(info->last_filename, szFile, sizeof(info->last_filename)-1);
		info->last_filename[sizeof(info->last_filename)-1] = 0;
		if (info->fp)
		{
			fclose(info->fp);
			info->fp = NULL;
		}	
	}
	if (!info->fp)
		info->fp = fopen(szFile, "a");

#ifdef _TEST_WRITE_LOG_NEED_TIME
	begin = get_microsecond();
#endif
	if (info->fp)
	{
		va_list args;
		if (enum_log_type_log == type)
		{
			fprintf(info->fp, "[%s %02d:%02d:%02d]  ",	szDate,
			currTM->tm_hour, currTM->tm_min, currTM->tm_sec);
		}
		else
		{
			fprintf(info->fp, "[%d/%02d/%02d %02d:%02d:%02d]   ", //file:%s, function:%s, line:%ld
			currTM->tm_year+1900, currTM->tm_mon+1, currTM->tm_mday, currTM->tm_hour, currTM->tm_min, currTM->tm_sec);
		}
		va_start(args, fmt);
		vfprintf(info->fp, fmt, args);
		va_end(args);
		fprintf(info->fp, "\n");

#ifdef _TEST_WRITE_LOG_NEED_TIME
		end = get_microsecond();
		fprintf(info->fp, "need: %ld us\n", (long)(end - begin));
		fflush(info->fp);
		begin = get_microsecond();
		fprintf(info->fp, "fflush need:%ld us\n", (long)(begin - end));
#endif	
		fflush(info->fp);
	}
}
#include <shlwapi.h>

#pragma comment(lib, "shlwapi.lib")

void CLogMgr::printf( const char *string, ... )
{
	if( !string )
		return;
	va_list	va;
	char data[1024] = {0};
	va_start( va, string );
	wvnsprintf(data, sizeof(data)-1, string, va );
	va_end( va );
	OutputDebugStr( data );
}

