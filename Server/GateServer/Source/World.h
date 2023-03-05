/********************************************************************
    Filename:    World.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GATESERVER_WORLD_H__
#define __GATESERVER_WORLD_H__

#pragma once

#include "Stage.h"

class CGateWorld
{
public:
    CGateWorld();
    ~CGateWorld();

    bool   InitStages();
    uint32 CreateStage( DWORD dwMapId, DWORD dwEctypeId );
    bool   ReleaseStage( DWORD dwEctypeId );

    // ·µ»ØArea±àºÅ
    int AddToTile( GameObjectId stID, DWORD dwStageID, short stTileID );
    void RemoveFromTile( GameObjectId stID, DWORD dwStageID, short stTileID );

    void SendMsgToView   ( GameObjectId stID, Msg *pMsg,bool bExceptMe = false );
    void SendMsgToArea   ( uint32 dwMapId, int nX, int nY, Msg *pMsg );
    void SendMsgToRegion ( GameObjectId id, Msg *pMsg );
    void SendMsgToStage  ( uint32 dwMapId, Msg *pMsg );
    void SendMsgToWorld  ( Msg* pMsg );
    void SendMsgToCountry( Msg* pMsg, TCountryId country, uint16 ustLevel, uint16 stExceptID );

    CGateStage* GetStageById( DWORD dwMapId );

    void ShowAllPlayerPos();

private:
    bool AddGateStage( CGateStage* pStage );

private:
    typedef std::map<uint32,CGateStage*> GateStageContainer;
    typedef GateStageContainer::iterator ItGateStageContainer;
    GateStageContainer m_mapStage;
};

#endif // __GATESERVER_WORLD_H__
