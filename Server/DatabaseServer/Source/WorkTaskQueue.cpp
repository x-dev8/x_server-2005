#include "WorkTaskQueue.h"
#include "FuncPerformanceLog.h"
#include "FileDatabase.h"
#include "RoleDataCache.h"
#include "DatabaseServerApp.h"

WorkTaskQueue::WorkTaskQueue() : m_nSaveQueryTotalNum(0), m_nSaveQueryMaxNum(0),m_nEnterWorldQueueSize(0)
{
}

WorkTaskQueue::~WorkTaskQueue()
{   
    while (!m_CharacterSaves.empty())
    {
        theSqlMessageManager.FreeSqlMessage( m_CharacterSaves.begin()->second );
        m_CharacterSaves.erase(m_CharacterSaves.begin());
    }

    while (!_querys.empty())
    {
        theSqlMessageManager.FreeSqlMessage( *_querys.begin() );
        _querys.erase(_querys.begin());
    }

    while (!m_CharacterLoadQuery.empty())
    {
        theSqlMessageManager.FreeSqlMessage( *m_CharacterLoadQuery.begin() );
        m_CharacterLoadQuery.erase(m_CharacterLoadQuery.begin());
    }

    while (!m_CharacterEnterWorld.empty())
    {
        theSqlMessageManager.FreeSqlMessage( *m_CharacterEnterWorld.begin() );
        m_CharacterEnterWorld.erase( m_CharacterEnterWorld.begin() );
    }
}

bool WorkTaskQueue::PushQuery( BaseSqlMessage* pSqlMessage )
{   
    if ( pSqlMessage == NULL )
    { return false; }

    CSALocker locker(this);

	switch( pSqlMessage->type )
	{
    case DBMSG_QUERYACCOUNTCHAR:
        { m_CharacterLoadQuery.push_back( pSqlMessage ); }
        break;
    case DBMSG_ENTERWORD:
        { m_CharacterEnterWorld.push_back( pSqlMessage ); }
        break;
    case DBMSG_SAVECHARACTER:
        {
            SqlMessageDBMsgSaveCharacter* pSqlSave = (SqlMessageDBMsgSaveCharacter*)pSqlMessage;

            // ��һʱ��д����
            if ( theFileMappingCharSaveManager.SaveDataToFile( pSqlSave ) != ER_Success)
            {
                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "account %u:%u:%s SaveDataToFile fail", pSqlSave->msg.accountId, pSqlSave->msg.dwCharacterID, pSqlSave->msg.dbInfo.baseinfo.aptotic.szCharacterName);
            }

            // ���뵽�洢��Ϣ���� (�оɵ����ϸ������µ�)
            InsertSaveQueryToSaveList( pSqlSave );

            // ���������ʱ��Ĵ洢��Ϣ��һ����������Ϸ����ʱ��Ĵ洢��Ϣ��һ���Ǹ��������ʱ����������ݣ�
            if ( pSqlSave->msg.shServerId != DiskServerId )
            {
                switch ( pSqlSave->msg.savetype )
                {
                case EST_ExitWorld:
                    GetRoleDataCacheManager().RemoveAccountRoleDataCaches( pSqlSave->msg.accountId );
                    break;
                case EST_ExitGameServer:
                case EST_Time:
                    long nResult = GetRoleDataCacheManager().UpdateAccountRoleDataCaches( &pSqlSave->msg );
                    if ( nResult != ER_Success )
                    {
                        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "GetRoleDataCacheManager().UpdateAccountRoleDataCaches Fail[%d]", nResult );
                    }
                    break;
                }

                DBAckOperSucc acksucc;
                acksucc.header.stID   = pSqlSave->msg.header.stID;
                acksucc.dwMsgType     = DBMSG_SAVECHARACTER;
                acksucc.dwMsgID       = pSqlSave->msg.subMarker;
                acksucc.dwCharacterID = pSqlSave->msg.dwCharacterID;

                if ( GetDatabaseServerApp()->useSqlType == DatabaseServerApp::ST_MSSql )
                { GetDatabaseInterface()->PushResult( pSqlSave->nClientId, &acksucc); }
                else
                { theMysqlCommunication.PushAckMessage( &acksucc, pSqlMessage->nClientId );}
            }
        }
        break;
    default:
        _querys.push_back( pSqlMessage );
        break;
    }

    const uint32 limitCount = 2000;
    if ( GetSaveQueueSize() > limitCount || GetEnterWorldQueueSize()> limitCount || GetOtherQueueSize() > limitCount || G_PrinfInfo == PRINTFQUEUESIZE )
    {
		std::string strMessageId = G_PrinfInfo == PRINTFQUEUESIZE ? SYSTEMOBJECT : LOGICSYSTEMOBJECT;
        LOG_MESSAGE( strMessageId, LOG_PRIORITY_INFO,"Save:%d Other:%d Total:%d SaveMax:%d EnterWordQueueSize:%d CharacterLoadQueryQueueSize:%d", 
            GetSaveQueueSize(), GetOtherQueueSize(), GetSaveQueryTotalNum(), GetSaveQueryMaxNum(), GetEnterWorldQueueSize(), GetCharacterLoadQuery());
        G_PrinfInfo = NOPRINT;
    }
    return true;
}

BaseSqlMessage* WorkTaskQueue::PopQuery()
{
    CSALocker locker(this);

    // �����Ҫ�������ﱣ�����������̫���˾͸��ߺ����˷�������æ
    // CheckStopEnterWorldWhenDBBusy();

    m_nEnterWorldQueueSize = (uint32)(m_CharacterEnterWorld.size());

    BaseSqlMessage* pSqlMessage = NULL;
    
    if ( !m_CharacterLoadQuery.empty() )
    {
        pSqlMessage = m_CharacterLoadQuery.front();
        m_CharacterLoadQuery.pop_front();
    }
    else if (!m_CharacterEnterWorld.empty())
    { // ��������н�ɫ��ҪEnterWorld,���ȿ������Ƿ���Ҫ����
        // CheckEnterWorld(); // ����ѻ���¼����̫���˾͸��ߺ����˷�������æ
        pSqlMessage = m_CharacterEnterWorld.front();
        m_CharacterEnterWorld.pop_front();

        //pSqlMessage = *m_CharacterEnterWorld.begin();

        //SqlMessageDBMsgEnterWorld* pSqlMessageEnterWorld = (SqlMessageDBMsgEnterWorld*)pSqlMessage;

        //// �Ƿ��ڱ��������
        //ItrCharSaveInfoContainer it = m_CharacterSaves.find( pSqlMessageEnterWorld->msg.dwCharacterID);
        //if (it != m_CharacterSaves.end())
        //{ // ����ڱ�������� ���ȴ�  // �ƺ�û�б�Ҫ�ˡ����������˶�save�������� ToModify
        //    pSqlMessage = it->second;
        //    m_CharacterSaves.erase(it);
        //}
        //else
        //{ // ������ڱ�������� ����
        //    m_CharacterEnterWorld.erase(m_CharacterEnterWorld.begin());
        //}
    }
    else if ( !_querys.empty() )
    {
        pSqlMessage = _querys.front();
        _querys.pop_front();
    }
    else if ( !m_CharacterSaves.empty() )
    {
        pSqlMessage = m_CharacterSaves.begin()->second;
        m_CharacterSaves.erase(m_CharacterSaves.begin());
        m_nSaveQueryTotalNum++;
    }

    return pSqlMessage;
}

BaseSqlMessage* WorkTaskQueue::GetSaveQueryByCharDbId( uint32 charDbid )
{
    CSALocker locker(this);

    ItrCharSaveInfoContainer it = m_CharacterSaves.find( charDbid );
    if ( it != m_CharacterSaves.end() )
    { return it->second; }
    return NULL;
}

void WorkTaskQueue::InsertSaveQueryToSaveList( BaseSqlMessage* pSqlMessage )
{
    if ( pSqlMessage == NULL)
    { return; }

    CSALocker locker(this);

    SqlMessageDBMsgSaveCharacter* pSqlSave = (SqlMessageDBMsgSaveCharacter*)pSqlMessage;

    // �����һ�δ��������ݻ�δ�洢�꣬�򸲸ǵ�
    ItrCharSaveInfoContainer it = m_CharacterSaves.find( pSqlSave->msg.dwCharacterID );
    if ( it != m_CharacterSaves.end() )
    {
        theSqlMessageManager.FreeSqlMessage( it->second );
        m_CharacterSaves.erase( it );
    }

    m_CharacterSaves.insert( CharSaveInfoContainer::value_type( pSqlSave->msg.dwCharacterID, pSqlMessage));

    if( m_CharacterSaves.size() > m_nSaveQueryMaxNum )
    { m_nSaveQueryMaxNum = static_cast<unsigned int>(m_CharacterSaves.size()); }
}

void WorkTaskQueue::CheckEnterWorld()
{
    if(GetEnterWorldQueueSize() > GetDatabaseServerApp()->m_dwEnterWorldConfine)
    {
        //int i = 0;
        //for(ItrQueryContainer enterWorlditr = m_CharacterEnterWorld.begin();enterWorlditr!=m_CharacterEnterWorld.end();)
        //{
        //    if(i > GetDatabaseServerApp()->m_dwEnterWorldConfine)
        //    {
        //        DBMsgEnterWorld* pReq = (DBMsgEnterWorld*)((*enterWorlditr)->m_pBuffer);
        //        if (pReq)
        //        {   
        //            MsgAckResult msg;
        //            msg.result = ER_EnterWorldRequstDataBusy;
        //            GetDatabaseInterface()->PushResult( (*enterWorlditr)->nClientId, &msg );
        //            (*enterWorlditr)->ReleaseBuffer();
        //            pReq = NULL;
        //            *enterWorlditr = NULL;
        //        }
        //        enterWorlditr = m_CharacterEnterWorld.erase(enterWorlditr);
        //        ++i;
        //        continue;
        //    }
        //    ++enterWorlditr;
        //    ++i;
        //}
        //for (int i = theCfg.dwEnterWorldConfine+1;i <= GetEnterWorldQueueSize();++i)
        //{
        //    //ȡ������ֵ�Ժ������������ǲ��ܵ�¼��������æ
        //    DBMsgEnterWorld* pEnterWorld = *m_CharacterEnterWorld[theCfg.dwEnterWorldConfine+1];
        //    //m_CharacterEnterWorld.find(pEnterWorld->dwCharacterID);
        //    //m_CharacterEnterWorld.l()
        //}
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING,"EnterWorld Out Of %d,Now EnterWorld Queue Size = %d",GetDatabaseServerApp()->m_dwEnterWorldConfine,GetEnterWorldQueueSize());
    }
}

void WorkTaskQueue::CheckStopEnterWorldWhenDBBusy()
{ // �����Ҫ�������ﱣ�����������̫���˾͸��ߺ����˷�������æ
    //if (GetSaveQueueSize() > GetDatabaseServerApp()->m_RoleSaveMax || GetOtherQueueSize() > GetDatabaseServerApp()->m_OtherSaveMax)
    //{
    //    for(ItrQueryContainer enterWorlditr = m_CharacterEnterWorld.begin();enterWorlditr!=m_CharacterEnterWorld.end();)
    //    {
    //        DBMsgEnterWorld* pReq = (DBMsgEnterWorld*)((*enterWorlditr)->m_pBuffer);
    //        if (pReq)
    //        {
    //            MsgAckResult msg;
    //            msg.result = ER_EnterDatabaseBusy;                
    //            GetDatabaseInterface()->PushResult( (*enterWorlditr)->nClientId, &msg );
    //            (*enterWorlditr)->ReleaseBuffer();
    //            pReq = NULL;
    //            *enterWorlditr = NULL;
    //        }
    //        enterWorlditr = m_CharacterEnterWorld.erase(enterWorlditr);
    //    }

    //    if(GetSaveQueryMaxNum() > GetDatabaseServerApp()->m_RoleSaveMax)
    //    {
    //        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING,"Save Role Out Of %d,Now EnterWorld Queue Size = %d,Role Save Queue Size = %d",GetDatabaseServerApp()->m_RoleSaveMax,GetEnterWorldQueueSize(),GetSaveQueueSize());
    //    }

    //    if (GetOtherQueueSize() > GetDatabaseServerApp()->m_OtherSaveMax)
    //    {
    //        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING,"Save Other Out Of %d,Now EnterWorld Queue Size = %d,Other Save Queue Size = %d",GetDatabaseServerApp()->m_OtherSaveMax,GetEnterWorldQueueSize(),GetOtherQueueSize());
    //    }
    //}
}