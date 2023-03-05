/********************************************************************
    Filename:     RestoreColdDown.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_RESTORTCOLDDOWN_H__
#define __COMMON_RESTORTCOLDDOWN_H__

#pragma once

#include "MeRTLibs.h"
#include "GlobalDef.h"

class RestoreColdDown
{
public:
    RestoreColdDown();
    ~RestoreColdDown();

    bool UseRestore( const int nId, bool bCheckCanUse = false );

    bool GetTime( const int nId, DWORD* pdwStartTime, DWORD* pdwPeriod );

    void Clear()
    { memset(m_stCoolDown, 0, sizeof(m_stCoolDown)); }

    void InitColdDown( SColdDown* pColdDown, int nCount );      // ≥ı ºªØ
    void SaveColdDown( SColdDown* pColdDown, int nCount );      // ±£¥Ê

private:
    int       m_nUsedCount;
    SColdDown m_stCoolDown[MAX_RESTORE_COUNT];
};

#endif // __COMMON_RESTORTCOLDDOWN_H__
