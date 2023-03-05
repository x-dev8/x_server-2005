/********************************************************************
    Filename:    GameStageDataCenter.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_GAMESTAGEDATACENTER_H__
#define __COMMON_GAMESTAGEDATACENTER_H__

#pragma once

#include "GlobalDef.h"
#include "StageDataLoader.h"
#include "Mutex.h"

class GameStageDataCenter
{
public:
    GameStageDataCenter(){}
    ~GameStageDataCenter();
    
    long InitStageDataLoader( uint32 mapId , const std::string& strFileName );
    CStageDataLoader* GetStageDataLoader( uint32 mapId );

private:
    typedef std::map< uint32 , CStageDataLoader* > StageDataLoaderContainer;
    typedef StageDataLoaderContainer::iterator         ItrStageDataLoaderContainer;

    StageDataLoaderContainer _stageDataLoaders;
    CSemiAutoIntLock         _lock;
};

GameStageDataCenter& GetGameStageDataCenter();

#endif // __COMMON_GAMESTAGEDATACENTER_H__

