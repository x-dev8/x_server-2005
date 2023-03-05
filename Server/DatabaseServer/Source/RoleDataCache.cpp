#include "RoleDataCache.h"

RoleDataCacheManager& GetRoleDataCacheManager()
{
    static RoleDataCacheManager instance;
    return instance;
}

void RoleDataCache::CloneData( const DBMsgSaveCharacter* pMessage )
{
    memcpy_s( &dbInfo,    sizeof( dbInfo ),     &(pMessage->dbInfo),  sizeof( dbInfo ));
    memcpy_s( &stStorage, sizeof( stStorage ),  &(pMessage->storageInfo), sizeof( stStorage ));
    bOpenDB         = pMessage->bOpenDB;
    nPKValue        = pMessage->nPKValue;
    stPKProtect     = pMessage->stPKProtectFlag;
    nGMLevel        = pMessage->nGMLevel;    // GM权限等级 0为无权限
    memcpy_s( &runtimeInfo, sizeof( runtimeInfo), &(pMessage->runtimeInfo), sizeof( runtimeInfo ));
}

void RoleDataCache::MakeData( DBMsgAckEnterWorld& ack )
{
    ack.bRet            = ER_Success;
    ack.nPKValue        = nPKValue;
    ack.stPKProtectFlag = stPKProtect;
    ack.nStayInHellTime = nStayInHellTime;
    ack.nGMLevel        = nGMLevel;
    memcpy_s( &ack.charinfo,    sizeof( ack.charinfo ),   &dbInfo,      sizeof( ack.charinfo  ));
    memcpy_s( &ack.stStorage,   sizeof( ack.stStorage),   &stStorage,   sizeof( ack.stStorage ));
    memcpy_s( &ack.runtimeInfo, sizeof( ack.runtimeInfo), &runtimeInfo, sizeof( ack.runtimeInfo ));
}

RoleDataCacheManager::RoleDataCacheManager()
{
    Release();
}

RoleDataCacheManager::~RoleDataCacheManager()
{
    Release();
}

RoleDataCache* RoleDataCacheManager::GetRoleDataCache( uint32 accountId, uint32 charDbId )
{
    CSALocker lock(_accountLock);
    ItrAccountRoleDataCacheContainer it = _accountRoleDataCaches.find( accountId );
    if ( it == _accountRoleDataCaches.end() )
    { return NULL; }

    RoleDataCacheContainer* pRoleDataCaches = it->second;
    if ( pRoleDataCaches == NULL )
    { return NULL; }

    ItrRoleDataCacheContainer itRoleData = pRoleDataCaches->find( charDbId );
    if ( itRoleData == pRoleDataCaches->end() )
    { return NULL; }

    return itRoleData->second;
}

long RoleDataCacheManager::UpdateAccountRoleDataCaches( const DBMsgSaveCharacter* pMessage )
{
    if ( pMessage == NULL )
    { return false; }

    CSALocker lock(_accountLock);

    ItrAccountRoleDataCacheContainer it = _accountRoleDataCaches.find( pMessage->accountId );
    if ( it != _accountRoleDataCaches.end() )
    { // 账号不为空
        RoleDataCacheContainer* pRoleDataCaches = it->second;
        if ( pRoleDataCaches == NULL )
        { return ER_NullPointer; }

        ItrRoleDataCacheContainer itRoleData = pRoleDataCaches->find( pMessage->dwCharacterID );
        if ( itRoleData != pRoleDataCaches->end())
        {
            RoleDataCache* pRoleDataCaches = itRoleData->second;
            if ( pRoleDataCaches == NULL )
            { return ER_NullPointer; }

            pRoleDataCaches->CloneData( pMessage );
        }
        else
        { // 有账号,但是没有这个人
            RoleDataCache* pRoleDataCache = RoleDataCache::CreateInstance();
            if ( pRoleDataCache == NULL )
            { return ER_NewPoolFail; }

            pRoleDataCache->CloneData( pMessage );

            pRoleDataCaches->insert( RoleDataCacheContainer::value_type( pMessage->dwCharacterID, pRoleDataCache) );
        }
    }
    else
    { // 账号为空
        RoleDataCacheContainer* pRoleDataCaches = new RoleDataCacheContainer();
        if ( pRoleDataCaches == NULL )
        { return ER_NewNormalFail; }

        RoleDataCache* pRoleDataCache = RoleDataCache::CreateInstance();
        if ( pRoleDataCache == NULL )
        { return ER_NewPoolFail; }

        pRoleDataCache->CloneData( pMessage );
        pRoleDataCaches->insert( RoleDataCacheContainer::value_type( pMessage->dwCharacterID, pRoleDataCache) );

        _accountRoleDataCaches.insert( AccountRoleDataCacheContainer::value_type( pMessage->accountId, pRoleDataCaches) );
    }

    const uint32 limintCount = 5000;
    if ( _accountRoleDataCaches.size() > 5000 )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "RoleDataCacheManager::UpdateAccountRoleDataCaches%d>%u", _accountRoleDataCaches.size(), limintCount);
    }
    return ER_Success;
}

long RoleDataCacheManager::RemoveAccountRoleDataCaches( uint32 accountId )
{
    CSALocker lock(_accountLock);

    ItrAccountRoleDataCacheContainer it = _accountRoleDataCaches.find( accountId );
    if ( it != _accountRoleDataCaches.end())
    {
        RoleDataCacheContainer* pRoleDataCaches = it->second;
        if ( pRoleDataCaches != NULL )
        {
            ItrRoleDataCacheContainer itRoleData    = pRoleDataCaches->begin();
            ItrRoleDataCacheContainer itRoleDataEnd = pRoleDataCaches->end();
            for ( ; itRoleData!=itRoleDataEnd; ++itRoleData )
            {
                RoleDataCache* pRoleData = itRoleData->second;
                if ( pRoleData )
                { pRoleData->Release(); }
            }
            pRoleDataCaches->clear();
            delete pRoleDataCaches;
        }
        _accountRoleDataCaches.erase( it );
    }
    return ER_Success;
}

void RoleDataCacheManager::Release()
{
    CSALocker lock(_accountLock);

    ItrAccountRoleDataCacheContainer it    = _accountRoleDataCaches.begin();
    ItrAccountRoleDataCacheContainer itEnd = _accountRoleDataCaches.end();
    for ( ; it!=itEnd; ++it )
    {
        RoleDataCacheContainer* pRoleDataCaches = it->second;
        if ( pRoleDataCaches != NULL )
        {
            ItrRoleDataCacheContainer itRoleData    = pRoleDataCaches->begin();
            ItrRoleDataCacheContainer itRoleDataEnd = pRoleDataCaches->end();
            for ( ; itRoleData!=itRoleDataEnd; ++itRoleData )
            {
                RoleDataCache* pRoleData = itRoleData->second;
                if ( pRoleData )
                { pRoleData->Release(); }
            }
            pRoleDataCaches->clear();
            delete pRoleDataCaches;
        }     
    }
    _accountRoleDataCaches.clear();
}
