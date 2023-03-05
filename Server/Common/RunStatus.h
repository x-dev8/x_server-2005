/********************************************************************
    Filename:    RunStatus.h
    MaintenanceMan Mail: Luo_157@hotmail.com


    初始化为ServerStatus_PrepareData
    数据准备就绪的时候设为 ServerStatus_Running
    当服务器退出时 设为ServerStatus_PrepareStop

    服务器逻辑线程 发现为ServerStatus_PrepareStop,断开所有玩家 设为ServerStatus_GameThreadStopped
    数据库线程发现ServerStatus_GameThreadStopped，且消息队列为空 设为ServerStatus_DBThreadStopped 
    Console线程发现ServerStatus_DBThreadStopped，退出程序

*********************************************************************/
#ifndef __COMMON_SERVERSTATUS_H__
#define __COMMON_SERVERSTATUS_H__

#include "MeRTLibsServer.h"
#include "RunStatusDefine.h"
#include "GlobalFunction.h"
#include "Singleton.h"

#define theRunStatus RunStatus::Instance()

class RunStatus : public ISingletion< RunStatus >
{
public:
	RunStatus();

    // 设置加载成功
    void SetLoadSuccess( unsigned char uchLoadType );

    // 设置服务器运行状态
    void SetStatus( long status ) { InterlockedExchange(&_runstatus, status ); }

    // 获得服务器运行状态
    long GetStatus() { return _runstatus; }
protected:
    // 检测服务器运行状态
    void CheckRunStatus();
private:
    // 加载资源信息标识
    BitValue< unsigned long > m_xLoadResource;      
    
    // 服务器运行状态
    volatile long _runstatus;
};

#endif // __COMMON_SERVERSTATUS_H__
