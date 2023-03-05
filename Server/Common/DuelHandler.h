/********************************************************************
	Filename: 	DuelHandler.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/
#ifndef __GAMESERVER_DUELHANDLER_H__
#define __GAMESERVER_DUELHANDLER_H__

#pragma once

#include "MeRTLibsServer.h"
#include "Dxsdk/d3dx9math.h"
#include "BaseCharacter.h"

class CDuelHandler
{
private:
    struct DuelInfo
    {
        DuelInfo()
        {
            memset(shDuelCharID, 0, sizeof(GameObjectId)*2);
            bReady = false;
            bInArea = true;
        }

        GameObjectId   shDuelCharID[2]; // 决斗人ID
        std::string strDuelCharName[2]; // 决斗人名字
        int nMapID;                     // 决斗地图
        D3DXVECTOR3 vPos;               // 决斗位置
        bool bReady;                    // 决斗准备完成
        bool bInArea;                   // 判断是否不在决斗区域
    };

public:
    CDuelHandler();
    virtual ~CDuelHandler();

    void Process();

    bool CreateDuel(GameObjectId shInviteCharID, GameObjectId shTargetCharID);
    bool DuelReady(GameObjectId shReadyCharID, bool bExitGame = false);
    bool RemoveDuel(GameObjectId shCharID, bool bRecvStopMessage = true);
    void OutDuleRange(GameObjectId shCharID);
    bool IsDuelFight(GameObjectId shAttackID, GameObjectId shTargetID);
    bool IsInDuel(GameObjectId shCharID);
    void RemovePlayer( BaseCharacter* pChar, BaseCharacter* pTarget, MsgDuelEnd* pEnd, GameObjectId shCharID, DWORD dwTime, bool bIsSelf );

private:
    typedef std::map<GameObjectId, DuelInfo> DuelInfoContainer;
    DuelInfoContainer m_mapDuelList;
    DuelInfoContainer m_mapReadyList;
};

CDuelHandler* theDuelHandler();

#endif // __GAMESERVER_DUELHANDLER_H__
