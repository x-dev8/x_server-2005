#ifndef __SYSTEMVARDEFINE_H__
#define __SYSTEMVARDEFINE_H__
// 每个服务器 系统变量数据结构
#include "GlobalDef.h"
#include "memory_pool.h"

#pragma once

namespace SystemVarDefine
{
    enum EConstDefine
    {
        NAME_LENGTH = 16,
    };
}

struct SStrVar
{
    SStrVar()
    {
        Reset();
    }

    void Reset()
    {
        memset( szName, 0, sizeof(szName) );
        nVar = 0;
    }

    char szName[SystemVarDefine::NAME_LENGTH];
    int  nVar;
};

struct SystemVar : INHERIT_POOL_PARAM( SystemVar, 5 )
{
    SystemVar()
    {
        memset(sysVar, 0, sizeof(sysVar));
    }
    ~SystemVar()
    { Release();}

    static SystemVar* CreateSystemVar() { return CNewWithDebug< SystemVar >::Alloc( 1, "SystemVar中创建SystemVar实例" ); }
    virtual void Release() { CNewWithDebug< SystemVar >::Free( this ); }

    uint32 GetServerId() { return ServerId;}
    void SetServerId(uint32 nValue) { ServerId = nValue;}
    void SetSysVarNull() { memset(sysVar, 0, sizeof(sysVar));}
    int GetVarByIndex(int nIndex);

    uint32 ServerId;
    SStrVar sysVar[More_iMaxSysVars];
};

#endif