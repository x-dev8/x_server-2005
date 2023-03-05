#include "MailServer.h"

void ServerMail::Clone( const SMail& mail )
{
    // ∏≥÷µ
    memcpy_s( &_dbBaseInfo.baseInfo, sizeof(_dbBaseInfo.baseInfo), &mail, sizeof(_dbBaseInfo.baseInfo));

    // …æ≥˝Œª…Ë÷√
    for ( int i=EM_ToIndex; i<EM_OwnerMaxCount; ++i)
    {
        if ( _dbBaseInfo.baseInfo.owners[i].charDbId == 0 )
        { break;}
        _SET_FLAG( _dbBaseInfo.deleteState, 1 << i );
    }
}

uint32 ServerMail::DeleteByChar( uint32 charDbId )
{
    int index = -1;
    for ( int i=0; i<EM_OwnerMaxCount; ++i)
    {
        if ( _dbBaseInfo.baseInfo.owners[i].charDbId == 0 )
        { break; }

        if ( _dbBaseInfo.baseInfo.owners[i].charDbId == charDbId )
        {
            index = i;
            _SET_FLAG( _dbBaseInfo.deleteState, 1 << i );
            break;
        }
    }

    if ( index == -1 )
    { return ER_MailCannotDelete; }

    return ER_Success;
}
