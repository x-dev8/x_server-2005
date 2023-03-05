/********************************************************************
    Filename:     EnterMySightPackage.h
    MaintenanceMan Mail: Luo_157@hotmail.com
    
    ����������Ұ��Ϣ�������
    ʹ��zlib������Ϣѹ��
*********************************************************************/


#ifndef __ENTERMYSIGHT_PACKAGE_H__
#define __ENTERMYSIGHT_PACKAGE_H__

#pragma once

#include "MeRTLibs.h"
#include "MessageDefine.h"

class CEnterMySightPackage
{
public:
    CEnterMySightPackage();
    virtual ~CEnterMySightPackage();
    
    bool MakePackMsg(MsgEnterMySightPack& msg);
    bool LoadPackMsg(MsgEnterMySightPack& msg);

    void Clear();
    bool IsEmpty() const;

public:

    MsgPlayerEnterMySight* PopEnterMySight();
    bool PushEnterMySight(MsgPlayerEnterMySight& msg);

protected:
    std::vector<MsgPlayerEnterMySight> m_list;
};

#endif // __ENTERMYSIGHT_PACKAGE_H__
