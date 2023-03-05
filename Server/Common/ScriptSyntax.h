/********************************************************************
    Filename:    ScriptSyntax.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_SCRIPTSYNTAX_H__
#define __COMMON_SCRIPTSYNTAX_H__

#pragma once

#include "ScriptCommand.h"
#include "ScriptFunctionSupport.h"
#include "ScriptAbstract.h"
#include "ScriptVarMgr.h"


class CScriptCmd_ProcStart : public CScriptCommand
{ // 过程开始
public:
    virtual const char * GetCmdID(){ return "proc_start"; }
    BOOL		Create( WordParser* words );
    void        Execute( CScriptVM* vm );
    void		Release(){ delete this; }
    int			m_nProcId;
    int			m_nMatchProcEndAddr;
};

class CScriptCmd_ProcEnd : public CScriptCommand
{ // 过程结束
public:
    virtual const char * GetCmdID(){ return "proc_end"; }
    BOOL		Create( WordParser* words ){ return TRUE; }
    void		Execute( CScriptVM* vm );
    void		Release(){ delete this; }
    int			m_nMatchProcStartAddr;
};

class CScriptCmd_Call : public CScriptCommand
{ // 过程调用
public:
    virtual const char * GetCmdID(){ return "call"; }
    BOOL		Create( WordParser* words );
    void		Execute( CScriptVM* vm );
    void		Release(){ delete this; }
    int			m_nProcId;
};

class CScriptCmd_Return : public CScriptCommand
{ // 过程返回
public:
    virtual const char * GetCmdID(){ return "return"; }
    BOOL		Create( WordParser* words ){ return TRUE; }
    void		Execute( CScriptVM* vm );
    void		Release(){ delete this; }
};

class CScriptCmd_If : public CScriptCommand
{ // 逻辑判断
public:
    CScriptCmd_If():m_nMatchElseAddr(-1),
        m_nMatchEndIfAddr(-1)
    {}
    virtual const char * GetCmdID(){ return "if"; }
    BOOL		Create( WordParser* words );
    int			m_nMatchElseAddr;
    int			m_nMatchEndIfAddr;

    int			m_key;
    int			m_op;
    int			m_nValue;
    bool		m_bValIsKey;

    void	Execute( CScriptVM* vm );
    void	Release(){ delete this; }
};

class CScriptCmd_Else : public CScriptCommand
{
public:
    virtual const char * GetCmdID(){ return "else"; }
    BOOL		Create( WordParser* words ){ return TRUE; }
    void        Execute(CScriptVM *vm );
    void		Release(){ delete this; }
    DWORD		m_nMatchIfAddr;
    DWORD		m_nMatchEndIfAddr;
};

class CScriptCmd_JumpToEndIf:public CScriptCommand
{
public:
    virtual const char * GetCmdID(){ return "jumptoendif"; }
    BOOL		Create( WordParser* words );
    void		Execute( CScriptVM* vm );
    void		Release(){ delete this; }
    DWORD		m_nMatchEndIfAddr;
};

class CScriptCmd_EndIf:public CScriptCommand
{
public:
    virtual const char * GetCmdID(){ return "endif"; }
    BOOL		Create( WordParser* words ){ return TRUE; }
    void		Execute( CScriptVM* vm );
    void		Release(){ delete this; }
    DWORD		m_nMatchIfAddr;
    DWORD		m_nMatchElseAddr;
};

class CScriptCmd_Jump:public CScriptCommand
{
public:
    virtual const char * GetCmdID(){ return "jump"; }
    BOOL		Create( WordParser* words );
    void		Execute( CScriptVM* vm );
    void		Release(){ delete this; }
    int			m_nProcId;
};

#endif // __COMMON_SCRIPTSYNTAX_H__
