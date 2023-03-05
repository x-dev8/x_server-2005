/********************************************************************
    Filename:    ScriptCommand.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_SCRIPTCOMMAND_H__
#define __COMMON_SCRIPTCOMMAND_H__

#pragma once

#include "ScriptKeyWord.h"
#include "WordParser.h"

class CScriptVM;
class CScriptCommand
{
public:
    CScriptCommand() : m_nSourceLine(0) ,m_nReturnKey(-1) ,m_nOp(SKW_SET)
    {}
    virtual const char* GetCmdID()            = 0;
    virtual BOOL Create( WordParser* pWords ) = 0;
    virtual void Execute( CScriptVM* pVM )    = 0;
    virtual void Release()                    = 0;

    void SetSourceLine( int nLine ){ m_nSourceLine = nLine; }
    int  GetSourceLine()           { return m_nSourceLine;  }
    void SetReturnKey( int n )     { m_nReturnKey = n;      }
    void SetOp       ( int n )     { m_nOp = n;             }

protected:
    int	m_nSourceLine; // 行数
    int m_nReturnKey;  // 返回变量的Id
    int m_nOp;         // 操作
};

#endif // __COMMON_SCRIPTCOMMAND_H__
