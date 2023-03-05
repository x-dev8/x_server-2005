/********************************************************************
    Filename:    NpcManager.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_NPCMANAGER_H__
#define __GAMESERVER_NPCMANAGER_H__

#pragma once

#include "MeRTLibsServer.h"
/*#include "NpcBaseCharacter.h"*/

class NpcManager
{
public:    
    struct SNpc 
    {
        int         nID;
        std::string strName;
        int         nLevel;
        int         nModelId;
        DWORD       dwMapId;
        float       fMapX;
        float       fMapY;
        float       fDir;
        bool        bChangeDir;
        bool        bShadow;
        int         nNpcType;
        std::string strFileName;
        std::string strImgPath;
        std::string strWalkPath;
        bool        bMask;       // 是否有阻挡
    };

public:
    NpcManager();
    ~NpcManager();

    bool LoadNpcInfo( const char* szFileName );
    //bool CreateNpcs( DWORD dwMapId, DWORD dwEctypeId );

    SNpc* FindNpcByModelId(int id);

private:
    typedef std::vector<SNpc>          NpcInfoContainer;
    typedef NpcInfoContainer::iterator ItNpcInfoContainer;
    NpcInfoContainer _NpcInfos;

};

NpcManager& GetNpcManager();

//需要优化按照地图保存

#endif // __GAMESERVER_NPCMANAGER_H__
