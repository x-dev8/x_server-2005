#include "CommonModule.h"
#include "WordParser.h"
#include "PlatformWorkSpace.h"

#define BEGIN_COMMAND_EX( content, command) \
	if ( 0 == stricmp( content, command)) \
{ 

#define BEGIN_COMMAND( content, command ) \
	if ( 0 == stricmp( content, command ) ) \
{ 

#define END_COMMAND(result) \
	return result;\
}

CCommonModule::CCommonModule(void)
{
}

CCommonModule::~CCommonModule(void)
{
}

bool CCommonModule::ParseCommand(SGMTaskInfo* pInfo)
{
	if (!pInfo)
	{
		return false;
	}

	char szCmd[512] = {0};
	char szParam[512] = {0};
	char data[512] = {0};

	const char* szCommand = pInfo->content;
	if (!szCommand)
	{
		return false;
	}
	// 获取指令头
	if( 1 != sscanf( szCommand,"%s",szCmd) )
	{ return false; }
	bool result = false;
	BEGIN_COMMAND_EX( szCmd, "flytomap")	// 飞地图
		result = ProcessFlyToMap( szCommand,pInfo->serverid );
	END_COMMAND(result)

	BEGIN_COMMAND_EX( szCmd, "broadcast")	// 发公告
		result = ProcessBroadcast( szCommand,pInfo->serverid );
	END_COMMAND(result)

	BEGIN_COMMAND_EX( szCmd, "opchat")	// 聊天纪录开关
		result = ProcessOpChat( szCommand,pInfo->serverid );
	END_COMMAND(result)

	BEGIN_COMMAND_EX( szCmd, "shutdown")	// 关闭服务器
		result = ProcessShutDown( szCommand,pInfo->serverid );
	END_COMMAND(result)

	BEGIN_COMMAND_EX( szCmd, "banaccount")	// 锁定帐号
		result = ProcessBanAccount( szCommand,pInfo->serverid );
	END_COMMAND(result)

	BEGIN_COMMAND_EX( szCmd, "banmacaddr")	// 锁定mac
		result = ProcessBanMacAddr( szCommand,pInfo->serverid );
	END_COMMAND(result)
}

bool CCommonModule::ProcessFlyToMap( const char* szContent,int server_id )
{   
	char szCmd[64] = {0};

	int   iMapID = 0;
	float fX = 0;
	float fY = 0;

	char szMapID[10] = {0};
	if( 4 != sscanf( szContent,"%s%s%f%f", szCmd, szMapID, &fX, &fY ) )
		return false;

	WordParser word;
	if( word.IsNumber( szMapID ) )
	{
		iMapID = atoi(szMapID);
		if ( iMapID >= 0)
		{
			//todo: real fly
		}
	}
	return true;
}

bool CCommonModule::ProcessBroadcast(const char* szContent,int server_id )
{
	std::string sstr = szContent;
	if (sstr.empty())
		return false;

	std::string strBull = sstr.substr(sstr.find(" ")+1, sstr.length());
	if (strBull.empty())
		return false;
	//todo:send bc
	MsgPFGMBroadcastReq msg;
	strncpy_s( msg.content, sizeof( msg.content ), strBull.c_str(), sizeof( msg.content ) - 1 );
	if (server_id == eTaskResult_AllServer)
	{
		thePlatFormWorkSpace.SendMsgToAllServer(&msg);
	}
	else
		return thePlatFormWorkSpace.SendMsgToSingleServer(&msg,server_id);

	return true;
}

bool CCommonModule::ProcessOpChat(const char* szContent,int server_id )
{
	char szCmd[64] = {0};
	int  op = 0;

	if( 2 != sscanf( szContent,"%s%d", szCmd, &op) )
		return false;

	MsgPFGMOPChatOnOff msg;
	msg.isOpen = op;
	if (server_id == eTaskResult_AllServer)
	{
		thePlatFormWorkSpace.SendMsgToAllServer(&msg);
	}
	else
		return thePlatFormWorkSpace.SendMsgToSingleServer(&msg,server_id);

	return true;
}

bool CCommonModule::ProcessShutDown	(const char* szContent,int server_id )
{
	char szCmd[64] = {0};
	int  delaytime = 0;//秒
	if( 2 != sscanf( szContent,"%s%d", szCmd, &delaytime) )
		return false;
	if (delaytime <= 0)
	{
		return false;
	}

	MsgPFGMShutdownServersReq req;
	req.delayTime = delaytime;
	if (server_id == eTaskResult_AllServer)
	{
		thePlatFormWorkSpace.SendMsgToAllServer(&req);
	}
	else
		return thePlatFormWorkSpace.SendMsgToSingleServer(&req,server_id);

	return true;
}

bool CCommonModule::ProcessBanAccount(const char* szContent,int server_id )
{
	char szCmd[64] = {0};
	char name[32] = {0};
	int  blocktime = 0;//秒
	int  accountid = 0;
	if( 4 != sscanf( szContent,"%s%s%d%d", szCmd,name,&accountid,&blocktime) )
		return false;
// 	if (blocktime <= 0)
// 	{
// 		return false;
// 	}

	MsgPFBlockAccount ban;
	ban.accountid = accountid;
	strncpy_s( ban.name, sizeof(ban.name), name, sizeof(ban.name) - 1);
	ban.blocktime = blocktime;
	if (server_id == eTaskResult_AllServer)
	{
		thePlatFormWorkSpace.SendMsgToAllServer(&ban);
	}
	else
	{
		return thePlatFormWorkSpace.SendMsgToSingleServer(&ban,server_id);
	}

	return true;
}

bool CCommonModule::ProcessBanMacAddr  (const char* szContent,int server_id )
{
	char szCmd[64] = {0};
	char mac[20] = {0};
	int  blocktime = 0;//秒
	if( 3 != sscanf( szContent,"%s%s%d", szCmd,mac,&blocktime) )
		return false;

	MsgPFBlockMac ban;
	strncpy_s( ban.cMac, sizeof(ban.cMac), mac, sizeof(ban.cMac) - 1);
	ban.blocktime = blocktime;
	if (server_id == eTaskResult_AllServer)
	{
		thePlatFormWorkSpace.SendMsgToAllServer(&ban);
	}
	else
	{
		return thePlatFormWorkSpace.SendMsgToSingleServer(&ban,server_id);
	}

	return true;
}