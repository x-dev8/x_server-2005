/********************************************************************
    Filename:     DetailWorkThread.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __DETAILWORKTHREAD_H__
#define __DETAILWORKTHREAD_H__

#pragma once

#include "MSSqlWorkThread.h"
#include "SqlMessages.h"

class NormalWorkThread : public DatabaseServerWorkThread
{
public:
    NormalWorkThread(){}
    virtual ~NormalWorkThread(){}
    
    virtual bool IsHaveTask() { return false; }
    virtual void Update();
};

class OrganizeWorkThread : public DatabaseServerWorkThread
{
public:
    OrganizeWorkThread(){}
    virtual ~OrganizeWorkThread(){}
    
    virtual bool IsHaveTask();
    virtual void Update();
};

#endif // __DETAILWORKTHREAD_H__
