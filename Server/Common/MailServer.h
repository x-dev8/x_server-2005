/********************************************************************
    Filename:    MailServer.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __COMMON_SERVERMAIL_H__
#define __COMMON_SERVERMAIL_H__

#pragma once

#include "GlobalDef.h"
#include "Memory_Pool.h"

class ServerMail : INHERIT_POOL_PARAM( ServerMail, 50 )
{
public:
    DECLARE_POOL_FUNC( ServerMail )

    void         Clone( const SMail& mail );
    const SMail& GetBaseInfo() const { return _dbBaseInfo.baseInfo; }

    bool         IsFromOwner ( uint32 charDbId ); // 是否是发信人
    bool         IsToOwner   ( uint32 charDbId ); // 是否是收信人
    bool         IsOtherOwner( uint32 charDbId ); // 是否是抄送人

    uint32       DeleteByChar( uint32 charDbId );                       // 删除
    bool         IsAllDelete (){ return _dbBaseInfo.deleteState == 0; } // 是否被所有人都删除

private:
    SDBMail _dbBaseInfo;
};

typedef std::vector<ServerMail*>         ServerMailContainer;
typedef ServerMailContainer::iterator    ItrServerMailContainer;
typedef std::map< __int64, ServerMail* > MailContainer;
typedef MailContainer::iterator          ItrMailContainer;

//////////////////////////////////////////////////////////////////////////
// inline
inline bool ServerMail::IsFromOwner ( uint32 charDbId )
{
    if ( charDbId == 0 )
    { return false; }

    return _dbBaseInfo.baseInfo.owners[EM_FromIndex].charDbId == charDbId;
}

inline bool ServerMail::IsToOwner( uint32 charDbId )
{
    if ( charDbId == 0 )
    { return false; }

    return _dbBaseInfo.baseInfo.owners[EM_ToIndex].charDbId == charDbId;
}

inline bool ServerMail::IsOtherOwner( uint32 charDbId )
{
    if ( charDbId == 0 )
    { return false; }

    for ( int i=EM_OtherIndex; i<EM_OwnerMaxCount; ++i )
    {
        if ( _dbBaseInfo.baseInfo.owners[i].charDbId == 0 )
        { break; }

        if ( _dbBaseInfo.baseInfo.owners[i].charDbId == charDbId )
        { return true; }
    }
    return false;
}

#endif // __COMMON_SERVERMAIL_H__
