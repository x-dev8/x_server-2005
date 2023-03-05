/********************************************************************
    Filename:    RunningScriptControl.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_RUNNINGSCRIPTCONTROL_H__
#define __COMMON_RUNNINGSCRIPTCONTROL_H__

#pragma once

#include "ScriptMgr.h"

class RunningScriptControl
{
public:
    enum EOwnerType
    {
        EOwnerType_None        , // 无类型
        EOwnerType_GamePlayer  , // 玩家
        EOwnerType_GlobalSystem, // 全局系统
    };

    enum EConstDefine
    { 
        EConstDefine_MaxCacheScriptCount = 10, 
    };

public:
    RunningScriptControl(){}
    virtual ~RunningScriptControl(){}

    virtual void   CancelCurScript( const char* szFile, const char* szFunc );
    virtual void   CancelAllScript();

    virtual void   SetVar( int nKey, int nVar, int nOp = SKW_SET, unsigned char uchSendMessage = BV_SendMessage );
    virtual int    GetVar( int nKey );

    uint8    GetOwnerType(){ return _ownerType; }
    void     SetOwnerType( uint8 ownerType ){ _ownerType = ownerType; }
    int      PushScript( SScript* p);
    bool     PopScript();
    SScript* GetScript();
    bool     RegisterVar( short stVarId );

private:
    VMScriptContainer m_lsScript;
    unsigned long     m_dwScriptSleep;
    unsigned long     m_dwScriptSleepStartTime;
    int               m_nTempVars[More_iMaxTempVars]; // 临时脚本数据
    uint8             _ownerType;
};

#endif // __COMMON_RUNNINGSCRIPTCONTROL_H__
