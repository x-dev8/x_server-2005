/********************************************************************
	Filename: 	SlkReader.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_SLKREADER_H__
#define __UTILITY_SLKREADER_H__

#pragma once

#include "MeRTLibs.h"
#include "Mutex.h"

class CFlyMemAllocer;
class CMapStrToIDMgr;

//////////////////////////////////////////////////////////////////////////
/*slk格式
*	
发现;Y，得到行号
发现;X,得到列号
发现;K,得到数值,数值以"\r\n"结束
if K"  是字符串，以"结束比如K"hello  dhdhhd" 
字符串中的换行用 1b 20 3a 替换
else 数值

数值以\r\n或者;结束

;;表示一个;

当开始新得一行时，判定
;Y 
;X 
后续数字和;或者换行
;K
如果后续"
则为字符串数据，
转义:1b 20 3a  -> \r\n
;;        -> ;

其他：忽略，等待下一个单独的;
*/

//written by dfk[2003/10/29]
/*
使用方法：
先调用ReadFromFile 或者 ReadFromString 解析slk信息
然后依次调用
//第一行是1
GotoNextLine()
RETURN
//成功挑转到行
ret_succ
//没有这个行
,ret_nothisline
//读取结束
,ret_readover

//第一个域是1
和 GetFieldOfLine()取得具体域的值
*/
//////////////////////////////////////////////////////////////////////////

#pragma pack(push,1) 

//解析后，顺序读取
class CSlkReader
{
public:
    enum enumFieldType
    {
        field_int
        ,field_string
        ,field_float
    };
    struct SField
    {
        SField()
        {
            data.iValue = 0;
        }
        int iFieldType;
        union unionFieldData
        {
            int iValue;
            float fValue;
            char *szValue;
        }data;
    };


private:
    typedef std::vector<SField*> vectorField;

    struct SLine
    {
        int iLineNo;
        vectorField vector;
    };
    typedef std::list<SLine*> listLine;
    typedef std::map<int,SLine*> mapLine;

    char						m_szTest0[ 1000 ];
    std::map<std::string,int> m_mapFiledNameToId;
    char						m_szTest1[ 1000 ];

    SLine *	m_pLastFindLine;

    listLine m_list;
    mapLine  m_mapIndex;
    SLine *  m_pCurGetLine;
    int		 m_iMaxLineNo;

    void   FreeLine(SLine*pLine);
    char*  GetFieldValue( char *szString,SField &field );
    char*  GetRowOrLineNO(char *szString,int &iValue );
    SLine* FindLine( int iLine,bool bAddIfNotFound = true );
    void   SetValue( SLine *pLine,int iX,SField &field );
    void   OutDebugLine(SLine*pLine,FILE *fp);
    void   ClearBlankRow();

public:
    CSlkReader();
    ~CSlkReader();
    void FreeAll();
    bool ReadFromString( char *szString,int iSize );
    bool ReadFromFile( const char *szFile );

    //目前行的第 个值
    SField *GetFieldOfLine( int iFieldNo );
    int		GetFieldNumOfLine();

    enum enumGotoRet
    {        
        ret_succ        // 成功挑转到行        
        ,ret_nothisline // 没有这个行        
        ,ret_readover   // 读取结束
    };

    int GetNumMaxLine(){ return m_iMaxLineNo; }
    int GetNumWorkLine(){ return m_list.size(); }
    int GotoNextLine( int iLine );

    void OutDebugInfo();

    int	 FindFirstLineByIntField( int iFieldNo,int iValue );
    //return  -1:Not found
    int	 FindLineByIntField( int iFieldNo,int iValue );

    
    bool GetIntField( int iCol,int &iValue );                                    // 读取整数
    bool GetStringField( int iCol,std::string& pstrRetValue);                    // 读取string
    bool GetStringField( int iCol,char **pstrRetValue,CFlyMemAllocer*pAllocer ); // 读取string
    bool GetFloatField( int iCol, float &fValue );                               // 读取浮点

    int ConvHeaderToId( const char* pszCol );
    bool GetIntField( const char* pszCol,int &iValue );
    
    bool GetStringField( const char* pszCol,std::string& pstrRetValue);                    // 读取string    
    bool GetStringField( const char* pszCol,char **pstrRetValue,CFlyMemAllocer*pAllocer ); // 读取string
    bool GetFloatField( const char* pszCol, float &fValue );                               // 读取浮点

    void InitFiledName();
    int  GetFiledNameID( const char * strName );

    bool GetIntFieldByName( const char* pszColName,int &iValue );                                    // 读取int
    bool GetIntFieldByName( const char* pszColName,short &shValue );                                 // 读取int
    bool GetStringFieldByName( const char* pszColName,std::string& pstrRetValue);                    // 读取string
    bool GetStringFieldByName( const char* pszColName,char **pstrRetValue,CFlyMemAllocer*pAllocer ); // 读取string
    bool GetFloatFieldByName( const char* pszColName, float &fValue );                               // 读取浮点
};

#pragma pack( pop ) 

#endif // __UTILITY_SLKREADER_H__
