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
/*slk��ʽ
*	
����;Y���õ��к�
����;X,�õ��к�
����;K,�õ���ֵ,��ֵ��"\r\n"����
if K"  ���ַ�������"��������K"hello  dhdhhd" 
�ַ����еĻ����� 1b 20 3a �滻
else ��ֵ

��ֵ��\r\n����;����

;;��ʾһ��;

����ʼ�µ�һ��ʱ���ж�
;Y 
;X 
�������ֺ�;���߻���
;K
�������"
��Ϊ�ַ������ݣ�
ת��:1b 20 3a  -> \r\n
;;        -> ;

���������ԣ��ȴ���һ��������;
*/

//written by dfk[2003/10/29]
/*
ʹ�÷�����
�ȵ���ReadFromFile ���� ReadFromString ����slk��Ϣ
Ȼ�����ε���
//��һ����1
GotoNextLine()
RETURN
//�ɹ���ת����
ret_succ
//û�������
,ret_nothisline
//��ȡ����
,ret_readover

//��һ������1
�� GetFieldOfLine()ȡ�þ������ֵ
*/
//////////////////////////////////////////////////////////////////////////

#pragma pack(push,1) 

//������˳���ȡ
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

    //Ŀǰ�еĵ� ��ֵ
    SField *GetFieldOfLine( int iFieldNo );
    int		GetFieldNumOfLine();

    enum enumGotoRet
    {        
        ret_succ        // �ɹ���ת����        
        ,ret_nothisline // û�������        
        ,ret_readover   // ��ȡ����
    };

    int GetNumMaxLine(){ return m_iMaxLineNo; }
    int GetNumWorkLine(){ return m_list.size(); }
    int GotoNextLine( int iLine );

    void OutDebugInfo();

    int	 FindFirstLineByIntField( int iFieldNo,int iValue );
    //return  -1:Not found
    int	 FindLineByIntField( int iFieldNo,int iValue );

    
    bool GetIntField( int iCol,int &iValue );                                    // ��ȡ����
    bool GetStringField( int iCol,std::string& pstrRetValue);                    // ��ȡstring
    bool GetStringField( int iCol,char **pstrRetValue,CFlyMemAllocer*pAllocer ); // ��ȡstring
    bool GetFloatField( int iCol, float &fValue );                               // ��ȡ����

    int ConvHeaderToId( const char* pszCol );
    bool GetIntField( const char* pszCol,int &iValue );
    
    bool GetStringField( const char* pszCol,std::string& pstrRetValue);                    // ��ȡstring    
    bool GetStringField( const char* pszCol,char **pstrRetValue,CFlyMemAllocer*pAllocer ); // ��ȡstring
    bool GetFloatField( const char* pszCol, float &fValue );                               // ��ȡ����

    void InitFiledName();
    int  GetFiledNameID( const char * strName );

    bool GetIntFieldByName( const char* pszColName,int &iValue );                                    // ��ȡint
    bool GetIntFieldByName( const char* pszColName,short &shValue );                                 // ��ȡint
    bool GetStringFieldByName( const char* pszColName,std::string& pstrRetValue);                    // ��ȡstring
    bool GetStringFieldByName( const char* pszColName,char **pstrRetValue,CFlyMemAllocer*pAllocer ); // ��ȡstring
    bool GetFloatFieldByName( const char* pszColName, float &fValue );                               // ��ȡ����
};

#pragma pack( pop ) 

#endif // __UTILITY_SLKREADER_H__
