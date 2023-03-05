#pragma once

#include "MeRTLibsServer.h"

struct DBMsg;
//备份消息
//保存角色信息 必须确认被数据库处理
//在数据库处理返回前，做备份
class CMsgBackupList
{
	//消息

	std::list<DBMsg*>	m_listMsg;
public:
	CMsgBackupList(void);
	~CMsgBackupList(void);

	//备份消息
	bool BackupMsg( DBMsg * pDBMsg );
	//去掉备份的消息
	bool RemoveMsg( DWORD dwMsgType,int iWho,unsigned short ustLifeCode );

	//取消息
	//szBuf的大小应该是MSGCANCUTMAXSIZE
	bool PopMsg( char *szBuf );
	int	 GetSize( void ){ return (int)m_listMsg.size(); }
};
