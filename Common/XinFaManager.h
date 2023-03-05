/********************************************************************
    Filename:     XinFaManager.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_TALENTMANAGER_H__
#define __COMMON_TALENTMANAGER_H__

#pragma once

#include "GlobalDef.h"

class XinFaManager
{
public:
    XinFaManager();
    ~XinFaManager();

    void        Init( SCharXinFa *pXinFa,int iSize );
    bool        ClearAllXinFa();
    bool        AddXinFa( unsigned short nID, unsigned char nLevel = 1 );
    bool        RemoveXinFa( unsigned short nID );
    int         GetXinFaNum() {return m_iXinFaNum;}    
    int         GetXinFaIndexById( int nID );
    SCharXinFa* GetXinFaByID( unsigned short nID );
    SCharXinFa* GetXinFaByIndex( unsigned short nIndex );

private:
    int          m_iSize;       // 
    int          m_iXinFaNum;   // 
    SCharXinFa*  m_pXinFaArray; // 
};

//////////////////////////////////////////////////////////////////////////
// inline

#endif // __COMMON_TALENTMANAGER_H__
