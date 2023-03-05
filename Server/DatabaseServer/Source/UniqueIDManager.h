/********************************************************************
    Filename:    UniqueIDManager.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/
#ifndef __COMMON_UNIQUEIDMANAGER_H__
#define __COMMON_UNIQUEIDMANAGER_H__

#pragma once

#include "MeRTLibsServer.h"
#include "Mutex.h"

class UniqueIDManager
{
public:
    UniqueIDManager();
    ~UniqueIDManager();

    void   SetInvalidID( uint32 iid ){ m_invalidID = iid;} // ���÷Ƿ�idֵ ȱʡΪ 0xFFFFFFFF
    uint32 GetInvalidID() { return m_invalidID;}

    int    AddIDResource( uint32 id); 
    int    AddIDResource( uint32 min_id, uint32 max_id); // ��ӿ���id��Դ
    
    uint32 GetUniqueID();               // ȡ��Ψһid
    void   ReleaseUniqueID( uint32 id); // �ͷ�id��Դ

private:
    CSemiAutoIntLock   m_uidLock;    
    std::queue<uint32> m_usableID; // ����id ����
    HASHSET<uint32>    m_usingID;  // ʹ���е�id ����
    uint32             m_invalidID;
};

#endif // __COMMON_UNIQUEIDMANAGER_H__
