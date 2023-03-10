/********************************************************************
    Filename:    MailManager.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_MAILMANAGER_H__
#define __COMMON_MAILMANAGER_H__

#include "GlobalDef.h"
//#include "ServerMail.h"

#pragma once

class MailSystemManager
{
public:
    enum EConstDefine
    {
        ECD_CreateIDMaxCount = 3,
    };

public:
    static MailSystemManager& Instance();
    MailSystemManager();
    ~MailSystemManager();

    uint32      AddMail   ( SMail& mail );
    uint32      RemoveMail( __int64 id  );
    ServerMail* GetMail   ( __int64 id  );
    uint32      GetMailByCharId( uint32 charDbId, ServerMailContainer& result );
    uint32      GetMailCountByCharId( uint32 charDbId );
    uint32      GetMemoryUse(); // 得到内存的使用量

private:
    typedef std::map< __int64, ServerMail* >    MailContainer;
    typedef MailContainer::iterator             ItrMailContainer;
    typedef std::multimap< uint32, __int64>     CharDbIdToMailIdContainer;
    typedef CharDbIdToMailIdContainer::iterator ItrCharDbIdToMailIdContainer;
    typedef std::pair<ItrCharDbIdToMailIdContainer,ItrCharDbIdToMailIdContainer> ItrRangeCharIdToMailId;
    MailContainer             _mails;
    CharDbIdToMailIdContainer _dbIdToMainIds;
};

#define theMailSystemManager MailSystemManager::Instance()

#endif // __COMMON_MAILMANAGER_H__
