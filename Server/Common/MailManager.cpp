#include "MailManager.h"

MailSystemManager& MailSystemManager::Instance()
{
    static MailSystemManager mailManager;
    return mailManager;
}

MailSystemManager::MailSystemManager()
{

}

MailSystemManager::~MailSystemManager()
{

}

uint32 MailSystemManager::AddMail( SMail& mail )
{
    // 创建Id
    __int64 id = -1;
    for ( int i=0; i<ECD_CreateIDMaxCount; ++i )
    {
        id = HelperFunc::CreateID();
        if ( GetMail(id) )
        { continue; }
    }
    
    if ( id == -1)
    { return ER_MailCreateIdFail; }
    
    // 赋与mail Id
    mail.id = id;

    // 创建邮件实体
    ServerMail* pServerMail = NEW_POOL( ServerMail );
    if ( NULL == pServerMail)
    { return ER_NewPoolFail; }

    pServerMail->Clone( mail );
    
    // 加入容器
    if ( !_mails.insert( MailContainer::value_type( mail.id, pServerMail ) ).second )
    {
        pServerMail->Release();
        return ER_MailAddFail;
    }

    // 做邮件映射
    for ( int i=0; i<EM_OwnerMaxCount; ++i )
    {
        if ( mail.owners[i].charDbId == 0 )
        { break; }
        _dbIdToMainIds.insert( CharDbIdToMailIdContainer::value_type( mail.owners[i].charDbId, mail.id ) );
    }


    // 发消息给Mysql入库
    

    
    return ER_Success;
}

uint32 MailSystemManager::RemoveMail( __int64 id  )
{
    ItrMailContainer it = _mails.find( id );
    if ( it != _mails.end() )
    { 
        ServerMail* pServerMail = it->second;
        if ( pServerMail )
        { pServerMail->Release(); }

        _mails.erase( it );
    }

    // 发消息给Mysql入库

    return ER_Success;
}

ServerMail* MailSystemManager::GetMail( __int64 id )
{
    ItrMailContainer it = _mails.find( id );
    if ( it != _mails.end() )
    { return it->second;}

    return NULL;
}

uint32 MailSystemManager::GetMailByCharId( uint32 charDbId, ServerMailContainer& result )
{
    result.clear();

    ItrRangeCharIdToMailId range = _dbIdToMainIds.equal_range( charDbId );
    ItrCharDbIdToMailIdContainer it = range.first;    
    for ( ; it != range.second; ++it)
    {
        __int64 mailId = it->second;
        ServerMail* pServerMail = GetMail( mailId );
        if ( NULL == pServerMail)
        { 
            LOG_MESSAGE( MAILOBJECT, LOG_PRIORITY_INFO, "GetMailByCharId 人物[%u]索引邮件[%I64u]不存在", charDbId, mailId );
            continue;
        }
        result.push_back( pServerMail );
    }

    return ER_Success;
}

uint32 MailSystemManager::GetMailCountByCharId( uint32 charDbId )
{
    ItrRangeCharIdToMailId range = _dbIdToMainIds.equal_range( charDbId );
    ItrCharDbIdToMailIdContainer it = range.first;
    uint32 count = 0;
    for ( ; it != range.second; ++it)
    {
        __int64 mailId = it->second;
        ServerMail* pServerMail = GetMail( mailId );
        if ( NULL == pServerMail)
        { 
            LOG_MESSAGE( MAILOBJECT, LOG_PRIORITY_INFO, "GetMailCountByCharId 人物[%u]索引邮件[%I64u]不存在",charDbId, mailId );
            continue;
        }
        ++count;
    }
    return count;
}
