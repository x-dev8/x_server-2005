#pragma once

#include "DBMessageDefine.h"

//保存角色信息的备份文件
//如果区别不同版本的角色信息
class CSaveCharBackFile
{
public:
	CSaveCharBackFile(void);
	~CSaveCharBackFile(void);

	//将Backup队列中的消息保存
	//将发送队列中的消息保存
	void	SaveMsgToFile( DBMsgSaveCharacter *pSave );
	//从文件载入，直接载入到DBCon::SendMsg
	void	LoadMsgFromFile( void );
};
