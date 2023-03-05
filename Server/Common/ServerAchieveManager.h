/********************************************************************
    Filename:     AchieveServerManager.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __SERVER_ACHIEVEMANAGER_H__
#define __SERVER_ACHIEVEMANAGER_H__

#pragma once

#include "AchieveManager.h"

class ServerAchieveManager : public AchieveManager
{
public:
    // ��ʼ��ϵ��
    ServerAchieveManager();
    virtual ~ServerAchieveManager();    

    void  CreateFromData(SAchieveData* pData);

    bool  TriggerById( uint16 nId, uint32 nValue = 1 );                     // ����һ���ɾ�
    bool  UpdateTriggerBySubType  ( uint16 nSubType, uint32 nValue = 1 );   // ���³ɾ�

    void SetGamePlayer(GamePlayer* pPlayer) { m_pPlayer = pPlayer; }

protected:
    GamePlayer* m_pPlayer;
    
};

#endif // __COMMON_ACHIEVEMANAGER_H__
