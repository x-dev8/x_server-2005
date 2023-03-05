#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#define STRICT
//////////////////////////////////////////////////////////////////////////
#include "InfoText.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "newwithdebug.h"



//#include "MemoryManager.h"	// 内存管理

bool CInfoText::Open(const char *szFileName, int iBufSize )
{
    fp = fopen( szFileName, "rb" );
    if(fp == NULL) 
        return false;

    m_iBufferSize = iBufSize;
    m_szBuffer = CNewWithDebug<unsigned char>::Alloc(m_iBufferSize, "CInfoText::Open中申请m_szBuffer");
    if(m_szBuffer==NULL)
        return false;

    return true;
}

void CInfoText::Close()
{
    if(m_szBuffer!=NULL)
    {
        CNewWithDebug<unsigned char>::Free(m_szBuffer);
        m_szBuffer = NULL;
    }
    if(fp!=NULL)
    {
        fclose(fp);
        fp = NULL;
    }
    m_iBufferSize = 0;
}

bool CInfoText::NextData( int &iDst, const char *szDataName )
{
    int nLine = FindDataInPara( (char*)szDataName, GetBuffer() );
    if( nLine == -1 )
        return false;
    iDst = GetDataInt( GetBuffer() );
    return true;
}

bool CInfoText::NextData( const char *szDst, const char *szDataName )
{
    int nLine = FindDataInPara( (char*)szDataName, GetBuffer() );
    if( nLine == -1 )
        return false;
    GetDataStr( GetBuffer(), (char*)szDst );
    return true;
}

bool CInfoText::NextData( float &fDst, const char* szDataName )
{
	int nLine = FindDataInPara( (char*)szDataName, GetBuffer() );
	if( nLine == -1 )
		return false;
	fDst = GetDataFloat( GetBuffer() );
	return true;
}

bool CInfoText::NextKeyword()
{
    if( FindKeyWord( "[]",GetBuffer()) == -1 )
        return false;
    else
        return true;
}

bool CInfoText::IsDimLine( char *szLine )
{
    // ToLog(szLine);
    // ToLog(strlen(szLine)>=0 && strlen(szLine)<=(size_t)m_iBufferSize);

    // 是否为注释行
    if( memcmp( szLine, "//", 2*sizeof(unsigned char) ) == 0 )
        return true;
    else
        return false;
}

bool CInfoText::IsBlankLine( char *szLine )
{
    // ToLog(szLine);
    // ToLog(strlen(szLine)>=0 && strlen(szLine)<=(size_t)m_iBufferSize);

    // 是否为空行
    if( strlen(szLine) == 0 ) 
        return true;
    else
        return false;
}

bool CInfoText::ReadLine( char *buf )
{
    // ToLog(fp);
    // ToLog(buf);

    // 读取文本文件行
    char buf_a,buf_b;
    int pos = 0;

    while(true)
    {
        if(feof(fp)) { buf[pos] = 0; return false; }
        buf_a = (char)fgetc(fp);
        if(buf_a == 0x0d)
        {
            if(feof(fp)) { buf[pos] = 0; return false; }
            buf_b = (char)fgetc(fp);
            if(buf_b == 0x0a)
            {
                buf[pos] = 0;
                break;
            }
            fseek(fp,-1,SEEK_CUR);
        }
        buf[pos] = buf_a;
        pos++;

        // ToLog(pos>=0 && pos<=260);

    }

    return true;
}

bool CInfoText::ReadAvailableLine( char *buf )
{
    // ToLog(fp);
    // ToLog(buf);

    // 读取有效行,不包含注释行和空行。
    while( ReadLine( buf ) )
    {
        if( !(IsDimLine( buf ) || IsBlankLine( buf )) )
            return true;
    }
    return false;
}


// 找到一个字符，返回字符所在位置
int CInfoText::FindLetter( char *buf, char fc )
{
    // ToLog( buf );
    // ToLog(strlen(buf)>=0 && strlen(buf)<=260);

    int pos = 0;
    int nMax = (int)strlen(buf);
    for(int i=0;i<nMax;i++)
    {
        if(buf[i] == fc)
            return i;
    }
    return -1;
}


// 找到左括号
int CInfoText::FindLeftBracket( char *buf )
{
    // ToLog( buf );
    // ToLog(strlen(buf)>=0 && strlen(buf)<=260);

    return FindLetter( buf, '[' );
}


//找到右括号
int CInfoText::FindRightBracket( char *buf )
{
    // ToLog( buf );
    // ToLog(strlen(buf)>=0 && strlen(buf)<=260);

    return FindLetter( buf, ']' );
}

int CInfoText::FindKeyWord( char *keyword, char *buf )
{
    // ToLog(fp);
    // ToLog(keyword);
    // ToLog(buf);
    // ToLog(strlen(keyword)>=0&&strlen(keyword)<=260);

    int nLine = 0;
    int s_pos,d_pos;
    char tmp[260];

    while( ReadLine( buf ) )
    {
        s_pos = FindLeftBracket( buf );
        if( s_pos != -1 )
        {
            d_pos = FindRightBracket( buf );
			int i =0;
            for(i=0;i<d_pos-s_pos-1;i++)
            {
                tmp[i] = buf[i+s_pos+1];
            }
            tmp[i] = 0;
            // ToLog( strlen(tmp) >= 0 && strlen(tmp) <= 260 );
            if( strcmp( keyword , "[]" ) == 0 )
            {
                if( buf[0] == '[' )
                {
                    return nLine;
                }
            }
            else if( strcmp( tmp, keyword ) == 0 )
                return nLine;
        }
        nLine++;
    }

    return -1;
}

int CInfoText::FindData( char *DataName, char *buf )
{
    // ToLog(fp);
    // ToLog(DataName);
    // ToLog(strlen(DataName)>=0&&strlen(DataName)<=260);

    int nLine = 0;
    int len = (int)strlen(DataName);
    while( ReadLine( buf ) )
    {
		int i = 0;
        for( i =0;i<len;i++)
        {
            if( DataName[i] != buf[i] )
                break;
        }
        if(i==len)
        {
            return nLine;
        }
        nLine++;
    }

    return -1;
}

int CInfoText::FindDataInPara( char *DataName, char *buf )
{
    // ToLog(fp);
    // ToLog(DataName);
    // ToLog(strlen(DataName)>=0&&strlen(DataName)<=260);

    int nLine = 0;
    int len = (int)strlen(DataName);
    long off = ftell( fp );
    while( ReadLine( buf ) )
    {
        if( buf[0] == '[' )
        {
            fseek( fp, off, SEEK_SET );
            return -1;
        }
		int i = 0;
        for(i=0;i<len;i++)
        {
            if( DataName[i] != buf[i] )
                break;
        }
        if(i==len)
        {
            return nLine;
        }
        nLine++;
        off = ftell( fp );
    }

    return -1;
}

bool CInfoText::GetDataStr( char *buf, char *outstr )
{
    // ToLog(buf);
    // ToLog(outstr);
    // ToLog(strlen(buf)>=0&&strlen(buf)<=260);

    int s_pos,d_pos;
    int len = (int)strlen(buf);

    s_pos = FindLeftBracket( buf );
    if( s_pos != -1 )
    {
        d_pos = FindRightBracket( buf );
		int i = 0;
        for(i=0;i<d_pos-s_pos-1;i++)
        {
            outstr[i] = buf[i+s_pos+1];
        }
        outstr[i] = 0;
        // ToLog( strlen(outstr) >= 0 && strlen(outstr) <= 260 );
        return true;
    }
    return false;
}

int CInfoText::GetDataInt( char *buf )
{
    // ToLog(buf);
    // ToLog(strlen(buf)>=0&&strlen(buf)<=260);

    int retNumber = -1;
    char outstr[260];
    if( GetDataStr( buf, outstr ) )
    {
        retNumber = atoi( outstr );
    }

    return retNumber;
}

float CInfoText::GetDataFloat( char *buf )
{
	// ToLog(buf);
	// ToLog(strlen(buf)>=0&&strlen(buf)<=260);

	float retNumber = -1;
	char outstr[260];
	if( GetDataStr( buf, outstr ) )
	{
		retNumber = atof( outstr );
	}

	return retNumber;
}

bool CInfoText::GetWordInString( char *dst, char *str, int n )
{
    // ToLog(str);
    // ToLog(dst);

    int slen = (int)strlen(str);
    int inumber = 0;
    int pos = 0;
    for(int i=0;i<slen;i++)
    {
        dst[pos] = str[i];
        if( str[i]==32 || str[i] == 13 || str[i] == 0 || str[i] == 9 || i>=slen ) 
        {
            dst[pos] = 0;
            inumber++;
            if(inumber==n)
            {
                return true;
            }
            pos = 0;
        }
        else
        {
            pos++;
            dst[pos] = 0;
        }
    }
    return false;
}