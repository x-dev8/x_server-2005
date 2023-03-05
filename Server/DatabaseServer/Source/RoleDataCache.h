#ifndef __DATABASESERVER_ROLEDATACACHE_H__
#define __DATABASESERVER_ROLEDATACACHE_H__

#pragma once

#include "MeRTLibsServer.h"
#include "DBMessageDefine.h"
#include "Mutex.h"
#include "Memory_Pool.h"

#pragma pack ( push, 1 )

class RoleDataCache : INHERIT_POOL_PARAM( RoleDataCache, 50 )
{
public:
    DECLARE_POOL_FUNC( RoleDataCache )

    RoleDataCache(){ nGMLevel = 0; }
    ~RoleDataCache(){}

    void CloneData( const DBMsgSaveCharacter* pMessage );
    void MakeData( DBMsgAckEnterWorld& ack );

public:
    SCharDBInfo      dbInfo                   ; // 需要入库数据
	SCharStorageData stStorage                ;
	bool             bOpenDB                  ;
    short            nPKValue                 ;
    short            stPKProtect              ;
    unsigned int     nStayInHellTime          ;
    unsigned int     nGMLevel                 ; // GM权限等级 0为无权限    
    SRuntimeInfo     runtimeInfo              ; // 运行时数据
    int8             newName[dr_MaxPlayerName];
};

#pragma pack ( pop )

class RoleDataCacheManager
{
public:
    RoleDataCacheManager();
    ~RoleDataCacheManager();

    RoleDataCache* GetRoleDataCache( uint32 accountId, uint32 charDbId );
    long UpdateAccountRoleDataCaches( const DBMsgSaveCharacter* pMessage );
    long RemoveAccountRoleDataCaches( uint32 accountId );

protected:
    void Release();

private:
    typedef MAP< uint32, RoleDataCache* >              RoleDataCacheContainer;
    typedef RoleDataCacheContainer::iterator           ItrRoleDataCacheContainer;
    typedef HASHMAP< uint32, RoleDataCacheContainer* > AccountRoleDataCacheContainer;
    typedef AccountRoleDataCacheContainer::iterator    ItrAccountRoleDataCacheContainer;

    AccountRoleDataCacheContainer _accountRoleDataCaches;
    CSemiAutoIntLock              _accountLock;
};

RoleDataCacheManager& GetRoleDataCacheManager();

#endif // __DATABASESERVER_ROLEDATACACHE_H__
