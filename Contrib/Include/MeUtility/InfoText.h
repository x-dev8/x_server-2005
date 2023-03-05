/********************************************************************
	Filename: 	InfoText.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __COMMON_INFOTEXT_H__
#define __COMMON_INFOTEXT_H__

#include "MeRTLibs.h"

// 信息文件读取类
class CInfoText
{
public:

    // 初始化
    bool Open( const char* szFileName, int iBufSize );
    // 释放
    void Close();

    // 顺序读出数据
    bool NextData( const char *szDst, const char *szDataName );
    bool NextData( int &iDst, const char *szDataName );
	bool NextData( float &fDst, const char* szDataName );
	bool NextKeyword();

    // /	搜索关健字,返回该行号        /
    int FindKeyWord( char *keyword, char *buf );

    // /	搜索配置变量                 /
    int FindData( char *DataName, char *buf );

    // 在段内找
    int FindDataInPara( char *DataName, char *buf );

    // /	获得配置变量 字符串值        /
    bool GetDataStr( char *buf, char *outstr );

    // /	获得配置变量 整数值          /
    int GetDataInt( char *buf );

	// /	获得配置变量 单精度			/
	float GetDataFloat ( char *buf );


    // /	读取有效行,不包含注释行和空行。 /
    bool ReadAvailableLine( char *buf );
    // /	获得单词                        /
    bool GetWordInString( char *dst, char *str, int n );

    // 获得缓冲指针
    char* GetBuffer() { return (char*)m_szBuffer; }
//////////////////////////////////////////////////////////////////////////
    
    CInfoText():
    fp(NULL),
    m_szBuffer(NULL),
    m_iBufferSize(0)
    {}
    virtual ~CInfoText()
    {}

//////////////////////////////////////////////////////////////////////////
    // 读取文字信息
    bool ReadLine( char *buf );

protected:

    // 是否为注释行
    bool IsDimLine( char *szLine );
    // 是否为空行
    bool IsBlankLine( char *szLine );

    // 找到一个字符，返回字符所在位置
    int FindLetter( char *buf, char fc );
    // 找到左括号
    int FindLeftBracket( char *buf );
    //找到右括号
    int FindRightBracket( char *buf );

private:

    FILE *fp;                       //文件指针
    unsigned char *m_szBuffer;      //文件缓冲区
    int m_iBufferSize;              //缓冲区大小

};

#endif // _INFOTEXT_H