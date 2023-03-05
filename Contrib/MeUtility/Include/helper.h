/********************************************************************
	Filename: 	Helper.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_HELPER_H__
#define __UTILITY_HELPER_H__

#include "MeRTLibs.h"
// 是否打开日志记录
//#define OPEN_LOG

namespace HelperFunc
{
	//copy string...when strlen(strSounrce) >= count, strDest[count-1] = 0;
	char *SafeNCpy( char *strDest,const char *strSource,size_t count );
	//从一个字符串数组匹配字符串，返回序号
	int GetIDByConstString( char*szString,char**pszString,int iHowManyString );

	//输出
	void Output( char *szFormat,... );
	//设置输出
	void SetOutputFile( FILE *fp );
	void SetErrorString( char *szErrorString,... );
	char* GetErrorString();

	//取得文件字符串
	//读取一个文本格式的文件，分配并且返回一个
	//数据字符串，strlen( szRet ) = filelen + 1;
	char* GetFileDataString( FILE *fp );
	char* GetFileDataString( char*szFileName );

	//去掉字符串中的百分号
	void VerifyString( char *szStr );

	char* CheckStringValid( char* szString, unsigned int nSize );

	char *AddNCpy( char *strDest,const char *strSource, size_t dstsize );

	void LimitStringEight( char *szStr, int nLength );//modified, jiayi.MAX_NAME_CREATE

	//创建一个文件夹，同时取消该文件夹下的文件只读属性
	bool CreateOutputFolder( const char* FolderName );
	//取消文件的只读属性
	bool AbrogateFolderAttribute(const char *FolderName,unsigned long FileAttribute = FILE_ATTRIBUTE_READONLY);
    
    __int64 GetCPUTime();
    __int64 CreateID();

    bool CheckToken(const char *Password,const char *Seed,const char *Token);

    short Ymd2Wday(unsigned int year,int month,int days);   // 年月日到星期几
}

void DebugLogout(const char* szFormat, ...);
const char* BigInt2String(__int64 nInt, char* pszBuffer);

#endif // __UTILITY_HELPER_H__
