/********************************************************************
    Filename:     EctypeMapMgr.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#pragma once

#include "MeRTLibsServer.h"

class BaseCharacter;

class CEctypeMapMgr
{
public:
	CEctypeMapMgr();
	~CEctypeMapMgr();

	void UpdateEctypeInfoToClient( BaseCharacter* pChar );
};

extern CEctypeMapMgr* GetEctypeMapMgr();
