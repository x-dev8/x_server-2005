/********************************************************************
    Filename:    TimeEventManager.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __CENTERSERVER_TIMEEVENTMANAGER_H__
#define __CENTERSERVER_TIMEEVENTMANAGER_H__

#pragma once
//·ÏÆú by cloud
#include "MeRTLibsServer.h"
#include "EventTimeTable.h"

struct STimeEvent
{
    uint8 year;
    uint8 month;
    uint8 day;
    uint8 hour;
    uint8 minute;
};

class TimeEventManager
{
public:
    TimeEventManager();
    ~TimeEventManager(){}

    bool Load  ( const char* szFileName );

    void Update( uint32 costTime );

    bool IsTime( const STimeEvent& targetTime, const STimeEvent& currentTime );

protected:
    typedef std::vector<STimeEvent>      TimeEventContainer;
    typedef TimeEventContainer::iterator ItrTimeEventContainer;    

    TimeEventContainer _timeEvents;
    uint32             _lastUpdateTime;
};

TimeEventManager& GetTimeEventManager();

#endif // __CENTERSERVER_TIMEEVENTMANAGER_H__
