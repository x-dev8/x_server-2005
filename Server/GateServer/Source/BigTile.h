/********************************************************************
	Filename: 	BigTile.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GATESERVER_TILE_H__
#define __GATESERVER_TILE_H__

#pragma once

#include "GlobalDef.h"
#include "MsgBase.h"
#include "GameDataType.h"

class BigTile
{
public:
    BigTile();
    virtual ~BigTile();

    void AddId          ( GameObjectId stID );
    void RemoveId       ( GameObjectId stID );
    void SendMsg        ( GameObjectId stID, Msg* pMsg, bool bExceptMe = false);
    void SendCountryMsg ( Msg* pMsg, TCountryId country, uint16 ustLevel, uint16 stExceptID );

public:
    TStageId MapId;

private:
    GameObjectIDSet m_chars;
};

#endif // __GATESERVER_TILE_H__
