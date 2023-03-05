/*++

Copyright (c) 2007

Module Name:

    CheckStateHandle.h
    CheckStateHandle.cpp

Abstract:

    用于临时存储玩家的验证码检测状态，保证玩家下线后再上线有些状态不会还原
    临时存储的数据在服务器重启后消失

Author:

    Luo_157@hotmail.com 14-Mar-2007

Revision History:

--*/

#ifndef _H_CHECKSTATEHANDLE_H
#define _H_CHECKSTATEHANDLE_H

#include <map>
#include <string>
#include "GraphicCodeCheck.h"

using std::map;
using std::string;

class CCheckStateHandle
{
public:
    CCheckStateHandle();
    virtual ~CCheckStateHandle();

    bool LoadCheckState(const char* pPlayerName, SCheckState& state);
    bool SaveCheckState(const char* pPlayerName, SCheckState state);

private:
    map<string, SCheckState> m_handle;
};

CCheckStateHandle& GetCheckStateHandle();

#endif //_H_CHECKSTATEHANDLE_H