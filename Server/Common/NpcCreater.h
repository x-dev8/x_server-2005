#ifndef __NPCCREATER_H__
#define __NPCCREATER_H__

/************************************************************************
                  npc创建类
                  Filename:     NpcCreater.h
                  MaintenanceMan Mail: lori227@live.cn

************************************************************************/
#include "NpcInfo.h"
#include "GameWorld.h"
class GameStage;

class NpcCreater
{
public:
    
    // 创建场景内的NPC
    static void CreateNpc( GameStage* pStage );
	static void AsynCreateNpc( GameStage* pStage,GameWorld::SSynStageInfo* pSyn);

    // 创建单个NPC
    static void CreateNpc( GameStage* pStage, NpcInfo::Npc* pNpcInfo, bool bNewConfig, DWORD OnlineTime = 0 );
	static void AsynCreateNpc( GameStage* pStage, NpcInfo::Npc* pNpcInfo, bool bNewConfig,GameWorld::SSynStageInfo* pSyn,DWORD OnlineTime = 0 );
};

#endif