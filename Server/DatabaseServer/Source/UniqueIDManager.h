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

    void   SetInvalidID( uint32 iid ){ m_invalidID = iid;} // 设置非法id值 缺省为 0xFFFFFFFF
    uint32 GetInvalidID() { return m_invalidID;}

    int    AddIDResource( uint32 id); 
    int    AddIDResource( uint32 min_id, uint32 max_id); // 添加可用id资源
    
    uint32 GetUniqueID();               // 取得唯一id
    void   ReleaseUniqueID( uint32 id); // 释放id资源

private:
    CSemiAutoIntLock   m_uidLock;    
    std::queue<uint32> m_usableID; // 可用id 集合
    HASHSET<uint32>    m_usingID;  // 使用中的id 集合
    uint32             m_invalidID;
};

#endif // __COMMON_UNIQUEIDMANAGER_H__
