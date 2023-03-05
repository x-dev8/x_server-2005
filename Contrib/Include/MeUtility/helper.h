/********************************************************************
	Filename: 	Helper.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_HELPER_H__
#define __UTILITY_HELPER_H__

#include "MeRTLibs.h"
// �Ƿ����־��¼
//#define OPEN_LOG

namespace HelperFunc
{
	//copy string...when strlen(strSounrce) >= count, strDest[count-1] = 0;
	char *SafeNCpy( char *strDest,const char *strSource,size_t count );
	//��һ���ַ�������ƥ���ַ������������
	int GetIDByConstString( char*szString,char**pszString,int iHowManyString );

	//���
	void Output( char *szFormat,... );
	//�������
	void SetOutputFile( FILE *fp );
	void SetErrorString( char *szErrorString,... );
	char* GetErrorString();

	//ȡ���ļ��ַ���
	//��ȡһ���ı���ʽ���ļ������䲢�ҷ���һ��
	//�����ַ�����strlen( szRet ) = filelen + 1;
	char* GetFileDataString( FILE *fp );
	char* GetFileDataString( char*szFileName );

	//ȥ���ַ����еİٷֺ�
	void VerifyString( char *szStr );

	char* CheckStringValid( char* szString, unsigned int nSize );

	char *AddNCpy( char *strDest,const char *strSource, size_t dstsize );

	void LimitStringEight( char *szStr, int nLength );//modified, jiayi.MAX_NAME_CREATE

	//����һ���ļ��У�ͬʱȡ�����ļ����µ��ļ�ֻ������
	bool CreateOutputFolder( const char* FolderName );
	//ȡ���ļ���ֻ������
	bool AbrogateFolderAttribute(const char *FolderName,unsigned long FileAttribute = FILE_ATTRIBUTE_READONLY);
    
    __int64 GetCPUTime();
    __int64 CreateID();

    bool CheckToken(const char *Password,const char *Seed,const char *Token);

    short Ymd2Wday(unsigned int year,int month,int days);   // �����յ����ڼ�
}

void DebugLogout(const char* szFormat, ...);
const char* BigInt2String(__int64 nInt, char* pszBuffer);

#endif // __UTILITY_HELPER_H__
