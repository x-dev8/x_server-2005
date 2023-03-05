/********************************************************************
	Filename: 	FileDB.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

/*
Abstract:
    作用：
    1.	作为与DatabaseServer通讯的一个临时缓存，保证当DatabaseServer存储失败时，数据提供备份。
    2.	为关键数据（如物品，等级，经验）提供实时存储，保证当服务器产生异常崩溃时，玩家数据损失减至最小。
*/

#ifndef __GAMESERVER_FILEDB_H__
#define __GAMESERVER_FILEDB_H__

#pragma once

#include "MeRTLibsServer.h"
#include "tstring.h"
#include "GamePlayer.h"
#include "DBMessageDefine.h"
#include "Mutex.h"
#include "CenterGameMessage.h"

class CFileDB
{
public:
    CFileDB();
    virtual ~CFileDB();

    bool SetPath(const char* szPath);

    // 保存角色的所有数据 当bToDB为true，则顺便将数据保存至DB
    bool SaveCharAllData( GamePlayer* pGamePlayer, uint8 saveType, const S2SSwitchGate* pMessage = NULL );

protected:
    CFileDB(const CFileDB&);
    const CFileDB& operator = (const CFileDB&);

    bool MakeSaveMsg( uint32 dwCharacterID, GamePlayer* pGamePlayer, DBMsgSaveCharacter& msg);

protected:
    _tstring m_strFileDBPath;     // 文件数据库存储路径
};

CFileDB& GettheFileDB();

#endif //_H_FILEDB_H
