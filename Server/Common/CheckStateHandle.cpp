/*++

Copyright (c) 2007

Module Name:

    CheckStateHandle.h
    CheckStateHandle.cpp

Abstract:

    ������ʱ�洢��ҵ���֤����״̬����֤������ߺ���������Щ״̬���ỹԭ
    ��ʱ�洢�������ڷ�������������ʧ

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