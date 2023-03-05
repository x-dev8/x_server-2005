/********************************************************************
    Filename:    ScriptCompiler.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_SCRIPTCOMPILER_H__
#define __COMMON_SCRIPTCOMPILER_H__

#pragma once

#include "ScriptVM.h"

enum
{
    eScriptLine_NormalLine        = 0,
    eScriptLine_ErrorLine         = 1<<0,
    eScriptLine_UnknownCommand    = 1<<1,
    eScriptLine_InvalidParamType  = 1<<2,
    eScriptLine_InvalidParamValue = 1<<3,
    eScriptLine_NotMatch          = 1<<4,
    eScriptLine_InvalidEmbeded    = 1<<5,
};

class CScriptCompilerSourceLine
{
public:
    CScriptCompilerSourceLine();
    ~CScriptCompilerSourceLine();

    void         SetSourceLine( int nLine ){ m_nSourceLine = nLine;}
    int          GetSourceLine()           { return m_nSourceLine; }
    WordParser*  GetWords()                { return &m_words;      }
    void         ParseSourceCode( const char* pszSourceCode );
    std::string& GetSourceCode()           { return m_strSourceCode;}
    DWORD        GetState()                { return m_dwState;     }
    void         SetState( DWORD dwState ) { m_dwState = dwState;  }
    void         AddState( DWORD dwState ) { m_dwState |= dwState; }

protected:
    int         m_nSourceLine;
    WordParser  m_words;
    std::string m_strSourceCode;
    std::string m_strLog;
    DWORD       m_dwState;
};

class CScriptCompiler
{
public:
    CScriptCompiler(){}
    virtual ~CScriptCompiler();
    BOOL            LoadSourceFile( const char* pszFilename );
    CScriptCommand* CreateCmd( int nSourceLine, const char* pszCmd );
    CScriptCommand* CreateCmd( int nSourceLine, WordParser* words );
    CScriptVM*      CreateVM( const char* pszFilename );

    int          MatchIf( DWORD dwIfAddr );

    // 检查
    BOOL         FirstPass();  // 单词拼写 数据合法性
    BOOL         SecondPass(); // 逻辑判断
    BOOL         ThirdPass();  // 紧凑编译
    void         Destroy();    // 清除资源

    void         Log( const char* pszFormat, ... );
    void         ClearLog();
    std::string& GetLog(){ return m_strLog; }

    int                        GetSourceLineCount()      { return m_vectorLine.size(); }
    CScriptCompilerSourceLine* GetSourceLine( int nLine ){ return m_vectorLine[nLine]; }

protected:
    std::vector<CScriptCompilerSourceLine*> m_vectorLine;
    std::vector<CScriptCommand*>            m_vectorCmd;
    int                                     m_anProcAddr[CScriptVM::MAX_PROC];    
    std::string                             m_strFileName;
    std::string                             m_strLog;
};

#endif // __COMMON_SCRIPTCOMPILER_H__
