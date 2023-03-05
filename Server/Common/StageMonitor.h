/********************************************************************
    Filename:     StageMonitor.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __STAGEMONITOR_H__
#define __STAGEMONITOR_H__

#pragma once

extern int g_start_stage;
extern int g_stage_show;
extern int g_stage_max;

extern bool g_bDBConnectted;
extern bool g_bAccountConnectted;
extern bool g_bLoginConnectted;
extern bool g_bLogConnectted;
extern int  g_GateServerNum;

//void RefreshGameServerMonitor();
void PrintMemoryInfo();

#endif // __STAGEMONITOR_H__
