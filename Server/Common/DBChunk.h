/********************************************************************
    Filename:    DBChunk.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __DB_CHUNK_H__
#define __DB_CHUNK_H__

#pragma once

#include "MeRTLibsServer.h"
#include "Database.h"

class CDBChunk
{
public:
    CDBChunk(void);
public:
    virtual ~CDBChunk(void);

public:
    bool ConnectDB();
    bool AsynConnectDB();

    bool LoadChunkMgrDataFromDB();
    bool SaveChunkMgrDataToDB();
    void SaveOnlineInfoToDB(unsigned int nOnlineNum);
    bool SaveUserInfo(const char* szUser, const char* szLog);

private:
    DataBase::CConnection m_pConn;
};

// extern CDBChunk g_dbchunk;

#endif // __DB_CHUNK_H__
