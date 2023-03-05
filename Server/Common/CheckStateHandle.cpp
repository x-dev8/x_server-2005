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

#include "CheckStateHandle.h"

CCheckStateHandle& GetCheckStateHandle()
{
    static CCheckStateHandle s_handle;
    return s_handle;
}

CCheckStateHandle::CCheckStateHandle()
{
}

CCheckStateHandle::~CCheckStateHandle()
{
}

bool CCheckStateHandle::LoadCheckState(const char* pPlayerName, SCheckState& state)
{
    if (pPlayerName == NULL)
    {
        return false;
    }

    map<string, SCheckState>::iterator itr = m_handle.find(string(pPlayerName));
    if (itr != m_handle.end())
    {
        state = itr->second;
        return true;
    }

    return false;
}

bool CCheckStateHandle::SaveCheckState(const char* pPlayerName, SCheckState state)
{
    if (pPlayerName == NULL)
    {
        return false;
    }

    m_handle[string(pPlayerName)] = state;
    return true;
}