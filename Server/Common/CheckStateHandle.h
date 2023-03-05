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