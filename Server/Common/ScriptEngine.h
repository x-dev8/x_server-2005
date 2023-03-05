#ifndef __COMMON_SCRIPTENGINE_H__
#define __COMMON_SCRIPTENGINE_H__

#pragma once

#include "MeRTLibsServer.h"

enum
{
    eScriptMaxCharVarNumber = 4096
};

enum
{
    eScriptDataType_Number,
    eScriptDataType_String
};
enum
{
    eScriptRangeType_List,
    eScriptRangeType_Range,
    eScriptRangeType_Table,
};
enum
{
    eScriptLogicOp_Unknown,
    eScriptLogicOp_Greater,
    eScriptLogicOp_GreaterEqual,
    eScriptLogicOp_Less,
    eScriptLogicOp_LessEqual,
    eScriptLogicOp_Equal,
    eScriptLogicOp_NotEqual,

};
enum
{
    eScriptCharProp_Unknown,
    eScriptCharProp_Money,
    eScriptCharProp_Level,
    eScriptCharProp_Pos,
    eScriptCharProp_Name,
    eScriptCharProp_Map,
    eScriptCharProp_Model,
    eScriptCharProp_Born,
    eScriptCharProp_Profession,
    eScriptCharProp_Country,
    eScriptCharProp_Exploit,
    eScriptCharProp_OfficialLevel,
    eScriptCharProp_Exp,
    eScriptCharProp_Hp,
    eScriptCharProp_Mp,
    eScriptCharProp_Max,
};

class CScriptCommandParam
{
public:
    int GetLength();
    BYTE* GetBuffer();
    int GetDataType();
};

class CScriptCommandParamBlock
{
public:
    int GetLength();
    int GetParamCount();
    CScriptCommandParam* GetParam( int nParam );
};
class CScriptVM;
class WordParser;
class CScriptCommand
{
public:
    CScriptCommand();

    virtual const char* GetCmdID() = 0;
    virtual BOOL Create( WordParser* pWords ) = 0;
    virtual void Execute( CScriptVM* pVM ) = 0;
    virtual void Release() = 0;

    void SetSourceLine( int nLine ){ m_nSourceLine = nLine; }
    int GetSourceLine(){ return m_nSourceLine; }
    BOOL LoadFromMemory( BYTE* pbyBuffer );

    BOOL SaveToMemory( BYTE* pbyBuffer, int nBufferSize );

    void SetReturnKey( int n ){ m_nReturnKey = n; }
    void SetOp( int n ){ m_nOp = n; }

protected:
    int	m_nSourceLine;
    //
    int m_nReturnKey;
    int m_nOp;
};

class CScriptEngine
{
public:
    CScriptEngine(void);
    ~CScriptEngine(void);


    //void SetCurCharID( short shID ){ m_shCurCharID = shID; }
    //void SetCurNpcID( short shID ){ m_shCurNpcID = shID; }
    void Log( const char* pszFormat, ... );
public:
    CScriptCommand* CreateCommand( const char* pszCommand );
    BOOL RegisterCommand( const char* pszCommand, CScriptCommand* pCommand );

    CScriptVM* CreateVMFromFile( const char* pszFilename );
    CScriptVM* CreateVMFromMemory( BYTE* pbyBuffer, int nBufferSize );

    int GetOp( const char* pszOp );
    int GetProp( const char* pszProp );

    std::string& GetLog(){ return m_strLog; }
protected:
    short	m_shCurCharID;
    short	m_shCurNpcID;
    std::string m_strLog;


};
//extern CScriptEngine* GetScriptEngine();
//extern void ReleaseScriptEngine();

#endif // __COMMON_SCRIPTENGINE_H__
