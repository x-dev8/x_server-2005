#include "Helper.h"
#include "FuncPerformanceLog.h"
#include "md5.h"

char * HelperFunc::SafeNCpy( char *strDest,const char *strSource,size_t count )
{
	if( strDest == NULL || strSource == NULL )
	{
		assert( false && "HelperFunc::SafeNCpy error, src or dst is null" );
		return "";
	}
	strDest[ count - 1 ] = 0;
	return strncpy( strDest, strSource, count - 1 );
}

int HelperFunc::GetIDByConstString( char*szString,char**pszString,int iHowManyString )
{
	_strlwr( szString );
	int iLoop;
	int iBlack = ' ';

	//去掉前面和后面的空格
	char *szFind = 0;
	while( szFind = strchr( szString,iBlack ) )
	{
		if( szString == szFind )
			szString ++;
		else
			break;
	}

	szFind = 0;
	//int iLen;
	while( szFind = strrchr( szString,iBlack  ) )
	{	
		if( 1 == strlen( szFind ) )
		{
			szFind[0] = 0;
		}
		else
			break;
	}

	//
	for( iLoop = 0 ; iLoop < iHowManyString ; iLoop ++)
	{
		if( 0 == _stricmp( szString,pszString[iLoop] ) )
			return iLoop;
	}
	return -1;
}

static FILE *g_fpOutput = 0;
//输出
void HelperFunc::Output( char *szFormat,... )
{
	if( !g_fpOutput )
		return;
	char szBuf[ 4096];	
	va_list vl;

	//转换参数
	va_start(vl, szFormat);
	vsnprintf(szBuf, sizeof(szBuf)-1, szFormat, vl);
	va_end(vl);
	fprintf( g_fpOutput,szBuf );
}

//设置输出
void HelperFunc::SetOutputFile( FILE *fp )
{
	g_fpOutput = fp;
}

static char g_szErrorString[ 256 ];
void HelperFunc::SetErrorString( char *szErrorString,... )
{
	va_list vl;	
	//转换参数
	va_start(vl, szErrorString);
	vsnprintf(g_szErrorString, sizeof(g_szErrorString)-1, szErrorString, vl);
	va_end(vl);	
}

char* HelperFunc::GetErrorString()
{
	return g_szErrorString;
}

char* HelperFunc::GetFileDataString( char*szFileName )
{
	FILE *fp = fopen( szFileName,"rb" );
	if( !fp )
		return 0;
	char *szRet = GetFileDataString( fp );
	fclose( fp );
	return szRet;
}

char* HelperFunc::GetFileDataString( FILE *fp )
{
	if( !fp )
		return 0;
	char *szRet = 0;
	fseek( fp,0,SEEK_END );
	long lLen = ftell( fp );
	fseek( fp,0,SEEK_SET );
	
	szRet = new char[ lLen + 3 ];
	if( !szRet )
		return 0;
	szRet[ lLen ] = 0;
	if( 1 != fread( szRet,lLen,1,fp ) )
	{
		delete[] szRet;
		return 0;
	}
	strcpy( szRet + lLen, "\r\n" );
	return szRet;
}

void HelperFunc::VerifyString( char *szStr )
{
	int iLoop;
	for( iLoop = 0 ; iLoop < strlen( szStr ) ; iLoop ++ )
	{
		if( '$' == szStr[ iLoop ] )
			szStr[ iLoop ] = '_';
		if( '\'' == szStr[ iLoop ] )
			szStr[ iLoop ] = '_';
	}
}

void HelperFunc::LimitStringEight( char* szStr, int nLength )
{ // 检测名字小于八个中文字符
	if( strlen(szStr) > nLength )
	{
		szStr[nLength] = '\0';
	}
}

char * HelperFunc::AddNCpy( char *strDest,const char *strSource, size_t dstsize )
{
	if( !strDest || !strSource )
	{
		assert( false && "HelperFunc::SafeNCpy error, src or dst is null" );
		return "";
	}

    size_t freesize = dstsize - strlen(strDest);

	return strncat( strDest,strSource, freesize-1);
}

void DebugLogout(const char* szFormat, ...)
{
#ifdef OPEN_LOG
	char szDate[256] = {0};
	char szTime[256] = {0};
	char szFile[256] = {0};
	char szLog[1024] = {0};

	SYSTEMTIME systime;
	GetLocalTime( &systime );

	_snprintf(szDate, sizeof(szDate)-1, "%04d-%02d-%02d", systime.wYear, systime.wMonth, systime.wDay);
	_snprintf(szTime, sizeof(szTime)-1, "%02d:%02d:%02d", systime.wHour, systime.wMinute, systime.wSecond);

    char szPath[256] = {0};
    _snprintf(szPath, sizeof(szPath)-1, "Log\\%s", szDate);
    _mkdir("Log");
    _mkdir(szPath);

#ifdef LOGIN_SERVER
    _snprintf(szFile, sizeof(szTime)-1, "%s\\%02d_LOGIN.log", szPath, systime.wHour);
#else
    _snprintf(szFile, sizeof(szTime)-1, "%s\\%02d.log", szPath, systime.wHour);
#endif
	std::ofstream fLog(szFile, std::ios::app);

	if(!fLog.is_open())
	{
		return;
	}
	//转换参数
	va_list vl;
	va_start(vl, szFormat);
	int cnt = vsnprintf(szLog, sizeof(szLog)-1, szFormat, vl);
	va_end(vl);

	fLog << szDate << " " << szTime << "    " << szLog << std::endl;
	fLog.close();
#endif
}

const char* BigInt2String(__int64 nInt, char* pszBuffer)
{
    _ui64toa(nInt, pszBuffer, 10);
    return pszBuffer;
}

bool HelperFunc::CreateOutputFolder( const char *FolderName )
{
	if ( !FolderName)
		return false;
	AbrogateFolderAttribute(".\\Data");
	SetFileAttributes(FolderName,FILE_ATTRIBUTE_NORMAL);
	AbrogateFolderAttribute(FolderName);
	if(_access(FolderName,0)==-1)
	{
		int errorcode = _tmkdir(FolderName);
		if (errorcode!=0)
		{
            char error[261] = { 0 };
			sprintf_s(error,sizeof( error ) - 1,"创建%s文件失败错误码=%d",FolderName,errorcode);
			OutputDebugStringA(error);
			return false;
		}
	}
	return true;
}

bool HelperFunc::AbrogateFolderAttribute(const char *FolderName,unsigned long FileAttribute)
{
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA FindFileData;
	memset(&FindFileData,0,sizeof(FindFileData));
	std::string folder = FolderName;
	if(strcpy(&folder[folder.length()] , "\\")!=0)
		folder += "\\*.*";
	else
	{
		if(strcpy(&folder[folder.length()],"*")!=0)
			folder += "*.*";
	}
	hFind = FindFirstFile(folder.c_str(),&FindFileData);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		while( FindNextFile(hFind,&FindFileData)!=0 )
		{
			std::string filePath = FolderName;
			filePath += "\\";
			filePath += FindFileData.cFileName;
			if (strcmp(FindFileData.cFileName,".") == 0||strcmp(FindFileData.cFileName,"..") == 0)
			{
				continue;
			}
			if(FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				FindFileData.dwFileAttributes &= ~FileAttribute;
				SetFileAttributes(filePath.c_str(),FindFileData.dwFileAttributes);
				AbrogateFolderAttribute(filePath.c_str());
			}
			else
			{
				FindFileData.dwFileAttributes &= ~FileAttribute;
				BOOL ok = SetFileAttributes(filePath.c_str(),FindFileData.dwFileAttributes);
				if (!ok)
				{
					int errorNum = GetLastError();
					printf("set file attribute error,error_code = %d\n",errorNum);
				}
			}
		}
		FindClose(hFind);
	}
	hFind = INVALID_HANDLE_VALUE;
	return true;
}

__int64 HelperFunc::GetCPUTime()
{
    __asm{RDTSC}
}

__int64 HelperFunc::CreateID()
{ // 根据时间及CPU指令周期计数得出唯一ID号
    time_t ltime;
    time(&ltime);
    __int64 value = ltime;
    value <<= 31;
    value += (int)(GetCPUTime());
    return value;
}

bool HelperFunc::CheckToken(const char* Password,const char* Seed,const char* Token)
{
    if (!Password||!Token||!Seed)
    {
        return false;
    }
    char CheckBuff[513] = { 0 };
    memset(CheckBuff,0,sizeof(CheckBuff));
    sprintf_s(CheckBuff,sizeof(CheckBuff)-1,"%s%s",Seed,Password);    
    if ( true )
    {
        MD5 md(CheckBuff);
        return md.toString().compare(Token)==0;
    }
    else
    { // 当CenterServer Crash后
        return false;
    }
}

short HelperFunc::Ymd2Wday(unsigned int year,int month,int days)
{
    if (year == 0)
        return -1;

    if (month > 12 || month < 1)
        return -1;
    
    if (days > 31 || days < 1)
        return -1;

    int i,y=year - 1;

    static int mdays[]={0,31,28,31,30,31,30,31,31,30,31,30};

    for(i=0;i<month;++i)
        days+=mdays[i];

    if(month>2)
    {
        //increment date if this is a leap year after February
        if((year%400) == 0||((year&3)==0 &&(year%100)) )
            ++days;
    }
    int TempDay = (y+(y/4)-(y/100)+(y/400)+days);

    return TempDay%7;
}


// 检查修正 保证字符串都能有结束符
char* HelperFunc::CheckStringValid( char* szString, unsigned int nSize )
{
	if ( szString == NULL || nSize == 0 )
	{ return ""; }

	szString[ nSize - 1 ] = 0;

	return szString;
}