#ifndef __CENTERSERVER_SESSION_H__
#define __CENTERSERVER_SESSION_H__

#pragma once

#include "MeRTLibsServer.h"
#include "GlobalDef.h"
#include "Memory_Pool.h"
#include "StaticArray.h"
#include "CenterGameMessage.h"

struct SessionMember
{
    unsigned long nAccountId;
    unsigned long nCharDbId;
};

class Session : INHERIT_POOL(Session)
{
public:    
    enum ESessionType
    {
        NoneSession,
        TeamSession,
    };

    static Session* CreateInstance() {return CNewWithDebug<Session>::Alloc(1, "Session::CreateInstance中创建Session实例");}
    void Release() { CNewWithDebug<Session>::Free(this);}

    Session()  {}
    ~Session (){}

protected:
private:
    ESessionType _type;
    typedef std::map< unsigned long, SessionMember > ContainerMember;
    ContainerMember members;
};

#endif // __CENTERSERVER_SESSION_H__
