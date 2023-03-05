/********************************************************************
    Filename:    DbRunStatus.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/
#ifndef __DATABASESERVER_SERVERSTATUS_H__
#define __DATABASESERVER_SERVERSTATUS_H__

#include "MeRTLibsServer.h"

#pragma once

#define theDbRunStatus GetRunStatus()

class DbRunStatus
{
public:
    enum ERunStatus
    {
        RunStatus_PrepareData   // ׼������
        ,RunStatus_Running      // ��ʼ����
        ,RunStatus_PrepareStop  // ׼��ֹͣ
        ,RunStatus_Stopped      // ��Ϸֹͣ
    };
    
    void SetStatus( long status )
    {  InterlockedExchange(&_runstatus, status );}

    long GetStatus(){ return _runstatus;}

    DbRunStatus();
    ~DbRunStatus();
    
private:
    volatile long _runstatus;
};

DbRunStatus& GetRunStatus();

#endif // __DATABASESERVER_SERVERSTATUS_H__
