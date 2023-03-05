/********************************************************************
	Filename: 	FileDB.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

/*
Abstract:
    ���ã�
    1.	��Ϊ��DatabaseServerͨѶ��һ����ʱ���棬��֤��DatabaseServer�洢ʧ��ʱ�������ṩ���ݡ�
    2.	Ϊ�ؼ����ݣ�����Ʒ���ȼ������飩�ṩʵʱ�洢����֤�������������쳣����ʱ�����������ʧ������С��
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

    // �����ɫ���������� ��bToDBΪtrue����˳�㽫���ݱ�����DB
    bool SaveCharAllData( GamePlayer* pGamePlayer, uint8 saveType, const S2SSwitchGate* pMessage = NULL );

protected:
    CFileDB(const CFileDB&);
    const CFileDB& operator = (const CFileDB&);

    bool MakeSaveMsg( uint32 dwCharacterID, GamePlayer* pGamePlayer, DBMsgSaveCharacter& msg);

protected:
    _tstring m_strFileDBPath;     // �ļ����ݿ�洢·��
};

CFileDB& GettheFileDB();

#endif //_H_FILEDB_H
