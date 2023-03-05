#include "AntiAddictionSystem.h"
#include "GameTime.h"
#include "TimeEx.h"
#include "CenterGameMessage.h"
#include "GameServerManager.h"
#include "Config.h"

/* comment out by zhangqi 2010-7-8
AntiAddictionSystem& GetAntiAddictionSystem()
{
    static AntiAddictionSystem instance;
    return instance;
}

AntiAddictionAccountInfo::AntiAddictionAccountInfo() : accountId( 0 ), lastOfflineTime( 0 ),
onlineMinuteTime( 0 ), offMinuteTime( 0 )
{
}

AntiAddictionAccountInfo::~AntiAddictionAccountInfo()
{    
}

void AntiAddictionAccountInfo::Release()
{
    CNewWithDebug<AntiAddictionAccountInfo>::Free(this); 
}

AntiAddictionSystem::AntiAddictionSystem() : _lastUpdateTime( 0 ) 
{
}


AntiAddictionSystem::~AntiAddictionSystem()
{
    ItrAccountInfoContainer it    = _accountOnlineInfo.begin();
    ItrAccountInfoContainer itEnd = _accountOnlineInfo.end();
    
    AntiAddictionAccountInfo* pAntiAddictionAccountInfo = NULL;
    for ( ; it!=itEnd; ++it )
    {
        pAntiAddictionAccountInfo = it->second;
        if ( pAntiAddictionAccountInfo == NULL )
        { continue; }

        pAntiAddictionAccountInfo->Release();
    }
    _accountOnlineInfo.clear();

    it    = _accountOfflineInfo.begin();
    itEnd = _accountOfflineInfo.end();
    for ( ; it!=itEnd; ++it )
    {
        pAntiAddictionAccountInfo = it->second;
        if ( pAntiAddictionAccountInfo == NULL )
        { continue; }

        pAntiAddictionAccountInfo->Release();
    }
    _accountOfflineInfo.clear();
}

void AntiAddictionSystem::Update()
{
    if ( _lastUpdateTime == 0)
    { _lastUpdateTime = HQ_TimeGetTime();}

    if ( !GameTime::IsPassCurrentTime( _lastUpdateTime, 60000 ) )
    { return; }

    ItrAccountInfoContainer it    = _accountOnlineInfo.begin();
    ItrAccountInfoContainer itEnd = _accountOnlineInfo.end();

    AntiAddictionAccountInfo* pAntiAddictionAccountInfo = NULL;
    for (; it!=itEnd; )
    {
        pAntiAddictionAccountInfo = it->second;
        if ( pAntiAddictionAccountInfo == NULL )
        {
            it = _accountOnlineInfo.erase( it );
            continue;
        }

        // ʱ���ۼ�
        pAntiAddictionAccountInfo->onlineMinuteTime += 1;

        if ( pAntiAddictionAccountInfo->onlineMinuteTime <= Config::GetInstance().antiAddictionTime[0])
        { // 3Сʱ��
            if ( pAntiAddictionAccountInfo->onlineMinuteTime % Config::GetInstance().antiAddictionTimeTell[0] == 0)
            { // ÿ60����֪ͨһ��
                _TellAntiAddictionAccountInfo( pAntiAddictionAccountInfo );
            }
        }
        else if ( pAntiAddictionAccountInfo->onlineMinuteTime <= Config::GetInstance().antiAddictionTime[1])
        { // 5Сʱ��
            if ( pAntiAddictionAccountInfo->onlineMinuteTime % Config::GetInstance().antiAddictionTimeTell[1] == 0)
            { // ÿ30����֪ͨһ��
                _TellAntiAddictionAccountInfo( pAntiAddictionAccountInfo );
            }
        }
        else
        { // 5Сʱ��
            if ( pAntiAddictionAccountInfo->onlineMinuteTime % Config::GetInstance().antiAddictionTimeTell[2] == 0)
            { // ÿ15����֪ͨһ��
                _TellAntiAddictionAccountInfo( pAntiAddictionAccountInfo );
            }
        }

        ++it;
    }

    _lastUpdateTime = HQ_TimeGetTime();
}

/*
void AntiAddictionSystem::OnMinorAccountOnline( uint32 accountId )
{
    AntiAddictionAccountInfo* pAntiAddictionAccountInfo = GetAntiAddictionAccountInfo( accountId, ECT_OfflineContainer);
    if ( pAntiAddictionAccountInfo ) 
    { // ����������
        TimeEx lastItemEx( pAntiAddictionAccountInfo->lastOfflineTime );        
        TimeSpan timeSpan = TimeEx::GetCurrentTime() - lastItemEx;
        pAntiAddictionAccountInfo->offMinuteTime += timeSpan.GetTotalMinutes();
        if ( pAntiAddictionAccountInfo->offMinuteTime >= Config::GetInstance().antiAddictionTime[1])
        { // ���´���5Сʱ
            pAntiAddictionAccountInfo->onlineMinuteTime = 0;
            pAntiAddictionAccountInfo->offMinuteTime    = 0;
            pAntiAddictionAccountInfo->lastOfflineTime  = 0;
        }
        
        // �����±���ɾ��
        RemoveAntiAddictionAccountInfo( accountId, ECT_OfflineContainer );

        // ���µ����߱���
        UpdateAntiAddictionAccountInfo( pAntiAddictionAccountInfo, ECT_OnlineContainer );
    }
    else
    {
        // �õ����߱��е����� �˺ų���
        pAntiAddictionAccountInfo = GetAntiAddictionAccountInfo( accountId, ECT_OnlineContainer );
        if ( pAntiAddictionAccountInfo == NULL )
        {
            pAntiAddictionAccountInfo = AntiAddictionAccountInfo::CreateInstance();
            if ( pAntiAddictionAccountInfo == NULL )
            {
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "AntiAddictionAccountInfo::CreateInstance() %d", accountId );
                return;
            }
            pAntiAddictionAccountInfo->accountId = accountId;
            // ���µ����߱���
            UpdateAntiAddictionAccountInfo( pAntiAddictionAccountInfo, ECT_OnlineContainer );
        }
    }
}

void AntiAddictionSystem::OnMinorAccountOffline( uint32 accountId )
{
    AntiAddictionAccountInfo* pAntiAddictionAccountInfo = GetAntiAddictionAccountInfo( accountId, ECT_OnlineContainer);
    if ( pAntiAddictionAccountInfo )
    {
        // ��¼����ʱ��
        pAntiAddictionAccountInfo->lastOfflineTime = TimeEx::GetCurrentTime().GetTime();

        // �����߱���ɾ��
        RemoveAntiAddictionAccountInfo( accountId, ECT_OnlineContainer );

        // �������±�
        UpdateAntiAddictionAccountInfo( pAntiAddictionAccountInfo, ECT_OfflineContainer );
    }
}

AntiAddictionAccountInfo* AntiAddictionSystem::RemoveAntiAddictionAccountInfo( uint32 accountId, unsigned char containerType )
{
    ItrAccountInfoContainer it;    
    AntiAddictionAccountInfo* pAntiAddictionAccountInfo = NULL;
    switch ( containerType )
    {
    case ECT_OnlineContainer:
        it = _accountOnlineInfo.find( accountId );
        if ( it != _accountOnlineInfo.end() )
        { 
            pAntiAddictionAccountInfo = it->second;
            _accountOnlineInfo.erase( it );
        }
    	break;
    case ECT_OfflineContainer:
        it = _accountOfflineInfo.find( accountId );
        if ( it != _accountOfflineInfo.end() )
        { 
            pAntiAddictionAccountInfo = it->second;
            _accountOfflineInfo.erase( it );
        }
    	break;
    }
    return pAntiAddictionAccountInfo;
}

void AntiAddictionSystem::UpdateAntiAddictionAccountInfo( AntiAddictionAccountInfo* pAntiAddictionAccountInfo, unsigned char containerType )
{   
    if ( pAntiAddictionAccountInfo == NULL)
    { return; }

    ItrAccountInfoContainer it;    
    switch ( containerType )
    {
    case ECT_OnlineContainer:
        it = _accountOnlineInfo.find( pAntiAddictionAccountInfo->accountId );
        if ( it != _accountOnlineInfo.end() )
        { 
            AntiAddictionAccountInfo* pOld = it->second;
            pOld->Release();
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "_accountOnlineInfo have�������" );
            it->second = pAntiAddictionAccountInfo;
        }
        else
        {
            _accountOnlineInfo.insert( AccountInfoContainer::value_type( pAntiAddictionAccountInfo->accountId, pAntiAddictionAccountInfo ));
        }
    	break;
    case ECT_OfflineContainer:
        it = _accountOfflineInfo.find( pAntiAddictionAccountInfo->accountId );
        if ( it != _accountOfflineInfo.end() )
        {
            AntiAddictionAccountInfo* pOld = it->second;
            pOld->Release();
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "_accountOfflineInfo have�������" ); 
            it->second = pAntiAddictionAccountInfo;
        }
        else
        {   
            _accountOfflineInfo.insert( AccountInfoContainer::value_type( pAntiAddictionAccountInfo->accountId, pAntiAddictionAccountInfo ));
        }
    	break;
    }
}

AntiAddictionAccountInfo* AntiAddictionSystem::GetAntiAddictionAccountInfo( uint32 accountId, unsigned char containerType )
{
    ItrAccountInfoContainer it;    
    switch ( containerType )
    {
    case ECT_OnlineContainer:
        it = _accountOnlineInfo.find( accountId );
        if ( it != _accountOnlineInfo.end() )
        { return it->second;}
    	break;
    case ECT_OfflineContainer:
        it = _accountOfflineInfo.find( accountId );
        if ( it != _accountOfflineInfo.end() )
        { return it->second;}
    	break;
    }
    return NULL;
}

void AntiAddictionSystem::_TellAntiAddictionAccountInfo( AntiAddictionAccountInfo* pAntiAddictionAccountInfo )
{
    S2SAntiAddictionAccountInfo msg;
    msg.accountId        = pAntiAddictionAccountInfo->accountId;
    msg.onlineMinuteTime = pAntiAddictionAccountInfo->onlineMinuteTime;
    msg.offMinuteTime    = pAntiAddictionAccountInfo->offMinuteTime;
    theGameServerManager.SendMsgToSingleByAccountId( &msg, msg.accountId );
}
*/