#include "TimeEventManager.h"
#include "GameTime.h"
#include "SlkReader.h"
#include "CenterGameMessage.h"
#include "GameServerManager.h"

TimeEventManager& GetTimeEventManager()
{
    static TimeEventManager instance;
    return instance;
}

TimeEventManager::TimeEventManager() : _lastUpdateTime( 0 )
{
}

bool TimeEventManager::Load( const char* szFileName )
{   
    CSlkReader reader;
    if( !reader.ReadFromFile( szFileName ) )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "%s  read failed",szFileName );
        return false;
    }

    int nGameType = 0;
    int iRow      = 3;
    int iRet      = 0;    
    std::string strScriptFileName;

    int year = -1, month = -1, day = -1, hour = -1, minute = -1;
    while ( CSlkReader::ret_readover != ( iRet = reader.GotoNextLine( iRow++ ) ) ) 
    {
        if( CSlkReader::ret_nothisline == iRet )
        { continue;}

        STimeEvent timeEvent;
        if( !reader.GetIntFieldByName( "TimeType", nGameType ) )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "%s  [TimeType]  read failed", szFileName );
            return false;
        }

        if( !reader.GetIntFieldByName( "Year", year ) )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "%s  [Year]  read failed",szFileName );
            return false;
        }

        if( !reader.GetIntFieldByName( "Month", month) )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "%s  [Month]  read failed", szFileName );
            return false;
        }

        if( !reader.GetIntFieldByName( "Day", day) )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "%s [Day] read failed", szFileName );
            return false;
        }

        if( !reader.GetIntFieldByName( "Hour", hour) )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "%s [Hour] read failed", szFileName );
            return false;
        }

        if( !reader.GetIntFieldByName( "Minute", minute ) )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "%s [Minute] read failed", szFileName );
            return false;
        }

        if ( year == -1 ) 
        { timeEvent.year = 0xFF;}
        else
        { timeEvent.year = year; }

        if ( month == -1 ) 
        { timeEvent.month = 0xFF; }
        else
        { timeEvent.month = month; }

        if ( day == -1 )
        { timeEvent.day = 0xFF; }
        else
        { timeEvent.day = day; }

        if ( hour == -1 ) 
        { timeEvent.hour = 0xFF; }
        else
        { timeEvent.hour = hour; }

        if ( minute == -1 )
        { timeEvent.minute = 0xFF; }
        else
        { timeEvent.minute = minute; }
        
        _timeEvents.push_back( timeEvent);
    }
    return true;
}

void TimeEventManager::Update( uint32 costTime )
{
//    if ( _lastUpdateTime == 0 )
//    { _lastUpdateTime = HQ_TimeGetTime();}
//    
//    if ( !GameTime::IsLessOrEqualCurrentTime( _lastUpdateTime + 60000) )
//    { return; }
//
//    std::time_t t = std::time( NULL );
//    std::tm* tme  = std::localtime( &t );
//    STimeEvent currentTime;
//    currentTime.year   = tme->tm_year - 100;
//    currentTime.month  = tme->tm_mon + 1;
//    currentTime.day    = tme->tm_mday;
//    currentTime.hour   = tme->tm_hour;
//    currentTime.minute = tme->tm_min;
//
//    ItrTimeEventContainer it    = _timeEvents.begin();
//    ItrTimeEventContainer itEnd = _timeEvents.end();
//    for( ; it!=itEnd; ++it)
//    {
//        STimeEvent& timeEvent = *it;
//        if ( !IsTime( timeEvent, currentTime))
//        { continue; }
//        
//        DWORD dwTime = ( timeEvent.year<<28)|( timeEvent.month<<24)|( timeEvent.day<<16)|( timeEvent.hour<<8)|(timeEvent.minute);
//
//        S2SNotifyTimeEvent msg;
//        msg.timeEventValue = dwTime;
//        theGameServerManager.SendMessageToGameServers( &msg );
//    }
//    _lastUpdateTime = HQ_TimeGetTime();
}

bool TimeEventManager::IsTime( const STimeEvent& targetTime, const STimeEvent& currentTime )
{
    //年 月 日 时 分
    //F  F  FF FF FF

    if ( targetTime.minute != 0xFF && targetTime.minute != currentTime.minute  )
    { return false;}

    if ( targetTime.hour != 0xFF && targetTime.hour != currentTime.hour )
    { return false; }

    if ( targetTime.day != 0xFF && targetTime.day != currentTime.day )
    { return false; }

    if ( targetTime.month != 0xFF && targetTime.month != currentTime.month )
    { return false; }

    if ( targetTime.year != 0xFF && targetTime.year != currentTime.year )
    { return false; }

    return true;
}
