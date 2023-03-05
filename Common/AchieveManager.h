/********************************************************************
    Filename:     AchieveManager.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_ACHIEVEMANAGER_H__
#define __COMMON_ACHIEVEMANAGER_H__

#pragma once

#include "AchieveConfig.h"

class AchieveManager
{
public:
    // ��ʼ��ϵ��
    AchieveManager() { }
    virtual ~AchieveManager() { }    
    virtual void CreateFromData(SAchieveData* pData) { }

    virtual uint32 GetCurrentValueByType( uint16 nValueType) 
    { 
        if ( m_pAchieveData == NULL )
        { return 0; }

        if ( nValueType >= More_iMaxAchieveVars )
        { return 0; }

        return m_pAchieveData->achieveVars[nValueType]; 
    }

protected:
    SAchieveData* m_pAchieveData;   // ����ɾ�
    
};

#endif // __COMMON_ACHIEVEMANAGER_H__
