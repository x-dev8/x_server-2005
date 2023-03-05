#ifndef __NPCCREATER_H__
#define __NPCCREATER_H__

/************************************************************************
                  npc������
                  Filename:     NpcCreater.h
                  MaintenanceMan Mail: lori227@live.cn

************************************************************************/
#include "NpcInfo.h"
#include "GameWorld.h"
class GameStage;

class NpcCreater
{
public:
    
    // ���������ڵ�NPC
    static void CreateNpc( GameStage* pStage );
	static void AsynCreateNpc( GameStage* pStage,GameWorld::SSynStageInfo* pSyn);

    // ��������NPC
    static void CreateNpc( GameStage* pStage, NpcInfo::Npc* pNpcInfo, bool bNewConfig, DWORD OnlineTime = 0 );
	static void AsynCreateNpc( GameStage* pStage, NpcInfo::Npc* pNpcInfo, bool bNewConfig,GameWorld::SSynStageInfo* pSyn,DWORD OnlineTime = 0 );
};

#endif