/********************************************************************
    Filename:     MiniDumper.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#pragma once

#include "MeRTLibs.h"
#include "dbghelp.h"
typedef void (*CRASHCALLBACKFUNC)();
typedef void (*CRASHCALLBACKFUNC_WITHPATH)( const char* pszDumpFileName,const char* pszDumpResult );

#define  CONFIG_RPT_FILE "bugrpt.ini"


class MiniDumper
{
private:
    static LPCSTR m_szAppName;
    static LPCSTR m_szAppVersion;
    static LPCSTR m_szDumpDesc;

public:
    static LONG WINAPI TopLevelFilter(struct _EXCEPTION_POINTERS* pExceptionInfo);

    static char m_szCmdLinePrefix[MAX_PATH];   // �쳣������ִ�е�������
    static char m_szExeNameToReboot[MAX_PATH]; // �쳣������������������ִ�еĳ����ļ���
	static void set_upload_info(std::string user_,std::string pwd_,std::string ip_,bool bUpload);
	static void set_upload_info(std::string apppara);
	static void set_upload_enable(bool bEnable);
    
public:
	
	static CRASHCALLBACKFUNC pCrashFunc;
	static CRASHCALLBACKFUNC_WITHPATH pCrashFunc_WithPath;
    static bool m_bDebugMode;

public:
    // ȱʡ��ʽ��ֻ���� Dump �ļ�������
    // �������Ի���֪ͨ
    MiniDumper( LPCSTR DumpFileNamePrefix, LPCSTR AppVersion, LPCSTR DumpDesc );

    // BugReport��ʽ�������ļ���ִ�� CmdLine
    // �����������ʹ��󱨸��

    // Param List:    
    // DumpFileNamePrefix ������Dump�ļ����ļ���ǰ׺
    // CmdLine            ����Dump֮��ִ�е�WinExec��������ʽΪ��"Bugreport.exe + �ո� + ������������, + �˿ڲ���, +·������"
    // ExeNameToReboot    ���Dump����������Crash���ĳ�����ļ�����Ŀǰֻ���BugReporter.exe��
    MiniDumper(LPCSTR DumpFileNamePrefix, LPCSTR AppVersion, LPCSTR DumpDesc, LPCSTR CmdLine, LPCSTR ExeNameToReboot = NULL);

	~MiniDumper();
private:
	bool SetUnhandleExpt();
};
