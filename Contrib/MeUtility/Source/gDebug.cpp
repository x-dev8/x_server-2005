#include "gDebug.h"
#include "Errorlog.h"
//
//#define new WKNEW
 
//char gDebugLog::TmpBuf[LOGSTR_MAXLENGTH];
//char gDebugLog::MsgBuf[LOGSTR_MAXLENGTH+MAX_PATH+10];

//#define NOLOG
void AddDlgMonitorString( LPSTR lpstr );

gDebugLog::gDebugLog()
{
	//OutputDebugStr("gDebugLog");
	//strncpy(m_logfile, "debug.txt", sizeof(m_logfile)-1);
	//strncpy(m_logname, ":", sizeof(m_logname)-1);
	////
	//remove(m_logfile);
	////
	//m_enable = true;
}

gDebugLog::gDebugLog( char* file )
{
	//strncpy(m_logfile, file, sizeof(m_logfile)-1);
	//strncpy(m_logname, ":", sizeof(m_logname)-1);
	//m_enable = true;
}

gDebugLog::~gDebugLog()
{}

bool gDebugLog::SetFile( char *file )
{
	//// ToLog( file );
	//// ToLog( strlen( file ) < MAX_PATH );
	//strncpy(m_logfile, file, sizeof(m_logfile)-1);
	return true;
}

bool gDebugLog::SetName( char *name )
{
	//// ToLog( name );
	//// ToLog( strlen( name ) < LOGSTR_MAXNAMELEN );
	//strncpy(m_logname, name, sizeof(m_logname)-1);
	return true;
}

bool gDebugLog::Reset( char *file, char *name )
{
	//FILE *fp;
	//fp = fopen(file,"wb");
	//if( fp == NULL ) 
	//	return false;
	//fclose(fp);

	//SetFile(file);
	//SetName(name);

	return true;
}

bool gDebugLog::OutputWithTime( LPCTSTR szError,... )
{
	//static char FormatString[ 4096];	
 //   SYSTEMTIME systime;
	//va_list vl;

	//GetLocalTime( &systime );
	//_snprintf( FormatString, sizeof(FormatString)-1,
 //       "[%04d-%02d-%02d %02d-%02d-%02d] %s\n",
	//	systime.wYear,
	//	systime.wMonth,
	//	systime.wDay,
	//	systime.wHour,
	//	systime.wMinute,
	//	systime.wSecond,szError );

	////转换参数
	//va_start(vl, szError);
	//int cnt = vsnprintf(TmpBuf, sizeof(TmpBuf)-1, FormatString, vl);
	//va_end(vl);
	//return Output( "%s", TmpBuf );
	return true;
}
extern CErrorLog* GetErrorLog();
bool gDebugLog::Output( LPCTSTR szError, ... )
{
//#ifdef NOLOG
//	return false;
//#endif
//	if(!m_enable) 
//		return false;
//
//	FILE* fp = NULL;
//	va_list vl;
//
//	//转换参数
//	va_start(vl, szError);
//	vsnprintf(TmpBuf, sizeof(TmpBuf)-1, szError, vl);
//	va_end(vl);
//
//	//检测总参数长度
//	// ToLog(strlen(TmpBuf)>=0&&strlen(TmpBuf)<LOGSTR_MAXLENGTH);
//
//	//在调试信息上附加块头名
//	strncpy(MsgBuf, m_logname, sizeof(MsgBuf) -1);
//
//    size_t freesize = sizeof(MsgBuf) - strlen(MsgBuf);
//    strncat(MsgBuf,":", freesize-1);
//
//    freesize = sizeof(MsgBuf) - strlen(MsgBuf);
//    strncat(MsgBuf,TmpBuf, freesize-1);
//
//	//输出调试窗口
//	//OutputDebugString( MsgBuf );
//    printf( MsgBuf );
//    //AddDlgMonitorString( MsgBuf );
//    //AddDlgCharInfoString( MsgBuf );
//
//	//输出
//	//fp = fopen(m_logfile,"at");
//	//if( fp == NULL ) 
//	//	return false;
//	//fprintf(fp,"%s",MsgBuf);
//	//fclose(fp);
//	GetErrorLog()->logString( MsgBuf );

	return true;
}

void gDebugLog::MsgBox( LPCTSTR szError, ... )
{
    //va_list vl;

    ////转换参数
    //va_start(vl, szError);
    //vsnprintf(TmpBuf, sizeof(TmpBuf)-1, szError, vl);
    //va_end(vl);

    ////检测总参数长度
    ////// ToLog(strlen(TmpBuf)>=0&&strlen(TmpBuf)<LOGSTR_MAXLENGTH);

    ////在调试信息上附加块头名
    //strncpy(MsgBuf, m_logname, sizeof(MsgBuf)-1);

    //size_t freesize = sizeof(MsgBuf) - strlen(MsgBuf);
    //strncat(MsgBuf, ":", freesize-1); 

    //freesize = sizeof(MsgBuf) - strlen(MsgBuf);
    //strncat(MsgBuf, TmpBuf, freesize-1);

    ////输出调试窗口
    ////OutputDebugString( MsgBuf );
    //printf( MsgBuf );
    ////AddDlgMonitorString( MsgBuf );

    //MessageBox( NULL, MsgBuf, "Debug Message Box", MB_OK );
}

void gDebugLog::Enable()
{
	//m_enable = true;
}

void gDebugLog::Disable()
{
	//m_enable = false;
}


bool gDebugLog::Output( BYTE* pBuffer, int nSize )
{
	//if(!m_enable) 
	//	return false;
	//FILE* fp;	
	////输出
	//fp = fopen(m_logfile,"at");
	//if( fp == NULL ) 
	//	return false;
	//
	//fprintf( fp, "\n" );
	//char* p = (char*)pBuffer;
	//char* line = p;

	//int i =0;
	//for( i = 0; i < nSize; i++ )
	//{
	//	if( i % 16 == 0 )
	//	{
	//		if( i > 0 )
	//		{
	//			fprintf( fp, "; " );
	//			for( int j = 0; j < 16; j++ )
	//				fprintf( fp, "%c", line[j] );
	//			//fwrite( line, sizeof( char )*16, 1, fp );
	//		}
	//		fprintf( fp, "\n%08xh: ", (DWORD)(&p[i]) );

	//		line = &p[i];
	//	}
	//	//if( (BYTE)p[i] >= ' ' )
	//	fprintf( fp, "%02x ", (BYTE)p[i] );
	//	//else 
	//	//	fprintf( fp, ".. " );
	//}

	//int nLeft = 16-i%16;
	//if( nLeft > 0 )
	//{
	//	for( int j = 0; j < nLeft; j++ )
	//		fprintf( fp, "   " );

	//	fprintf( fp, "; " );
	//	for( int j = 0; j < 16-nLeft; j++ )
	//	{
	//		if( line[j] >= ' ' )
	//			fprintf( fp, "%c", line[j] );
	//		else
	//			fprintf( fp, "." );
	//	}
	//	//fwrite( line, sizeof( char )*( 16-nLeft ), 1, fp );
	//}

	//fprintf( fp, "\n" );
	//
	//
	//fclose( fp );

	return true;
}

