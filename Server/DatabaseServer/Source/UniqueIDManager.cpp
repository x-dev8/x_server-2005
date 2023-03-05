#include "UniqueIDManager.h"

UniqueIDManager::UniqueIDManager() : m_invalidID(0xffffffff)
{
}

UniqueIDManager::~UniqueIDManager()
{
}

int UniqueIDManager::AddIDResource( uint32 id )
{
    CSALocker lockSelf(m_uidLock);

    m_usableID.push(id);
    return (int)m_usableID.size();
}

int UniqueIDManager::AddIDResource( uint32 min_id, uint32 max_id )
{   
    if ( min_id > max_id )
    { return -1; }

    CSALocker lockSelf(m_uidLock);
    for( uint32 i=min_id; i<=max_id; ++i)
    { m_usableID.push(i);}

    return (int)m_usableID.size();
}

uint32 UniqueIDManager::GetUniqueID()
{
    CSALocker lockSelf( m_uidLock );

    if(m_usableID.empty())
    { return m_invalidID; }
    
    uint32 id = m_usableID.front(); // 取值
    m_usableID.pop();               // 从可用id表移出
    m_usingID.insert(id);           // 加入使用中id表

    return id;
}

void UniqueIDManager::ReleaseUniqueID(uint32 id)
{
    CSALocker lockSelf( m_uidLock );
    m_usingID.erase(id); // 从‘使用中id表’移出
    m_usableID.push(id); // 加入‘可用id表’
}
