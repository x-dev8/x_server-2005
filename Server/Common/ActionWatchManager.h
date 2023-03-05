/********************************************************************
    Filename:    ActionWatchManager.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __SERVERCOMMON_ACTIONWATCHMANAGER_H__
#define __SERVERCOMMON_ACTIONWATCHMANAGER_H__

#pragma once

#include "MeRTLibsServer.h"

class GamePlayer;

class ActionWatchManager
{
public:
    enum EConstDefine
    {
        CD_DEFAULT_LIMITCOUNT        = 2,
        CD_DEFAULT_LIMITINTERVALTIME = 1000,
    };
    struct SWatchData
    {
        SWatchData()
        {
            limitCount        = CD_DEFAULT_LIMITCOUNT;
            limitIntervalTime = CD_DEFAULT_LIMITINTERVALTIME;
            count      = 0;
            startTime  = 0;
        };
        uint8  count;
        uint32 startTime;
        uint8  limitCount;        // ���Ƶĸ���     Ĭ�� 2 ��  �Ժ�ÿ����Ϊ�������Ʋ�һ��
        uint32 limitIntervalTime; // ���Ƶļ��ʱ�� Ĭ��
    };

public:
    ActionWatchManager();

    void SetBeWatcher( GamePlayer* pGamePlayer ) { _pBeWatcher = pGamePlayer; }
    
    long Action( uint16 actionId );

private:
    GamePlayer* _pBeWatcher;

    typedef std::map< uint16, SWatchData > ActionWatchContainer;
    typedef ActionWatchContainer::iterator ItrActionWatchContainer;
    ActionWatchContainer _actionWatchs;
};

#endif // __SERVERCOMMON_ACTIONWATCHMANAGER_H__
