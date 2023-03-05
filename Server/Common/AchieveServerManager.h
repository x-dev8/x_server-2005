/********************************************************************
    Filename:     AchieveServerManager.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __SERVER_ACHIEVEMANAGER_H__
#define __SERVER_ACHIEVEMANAGER_H__

#pragma once

#include "AchieveManager.h"

class GamePlayer;

class AchieveServerManager : public AchieveManager
{
public:
    // ��ʼ��ϵ��
    AchieveServerManager() 
    {  
        m_pPlayer = NULL;
        m_pAchieveData = NULL; 
    };

    virtual ~AchieveServerManager() 
    {
        m_pPlayer = NULL;
        m_pAchieveData = NULL; 
    };    

    void  CreateFromData( GamePlayer* pPlayer, SAchieveData* pData );

    bool  UpdateTriggerById( uint16 nId, uint32 nValue = 1 );   // ����һ���ɾ�
    bool  UpdateTriggerByValueType( uint16 nValueType, uint32 nValue = 1, bool bAddValue = false ); // �����ɾ�

    uint8 GetAchieveState( uint16 nId );            // ��óɾ�״̬
    bool  TriggerFinishAchieve(  uint16 nId  );     // ֱ�Ӵ����ɾ����

    void  SetGamePlayer(GamePlayer* pPlayer) { m_pPlayer = pPlayer; }

protected:
    GamePlayer* m_pPlayer;
    
};

#endif // __COMMON_ACHIEVEMANAGER_H__
