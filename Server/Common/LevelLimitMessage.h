#ifndef __LEVELLIMITMESSAGE_H1__
#define __LEVELLIMITMESSAGE_H1__

#include "MsgBase.h"
#include "LevelLimitDefine.h"
#include "MessageRangeDefine.h"

#pragma pack( push, 1 )

enum LevelLimitMessageDefine
{
	MSG_LOADDATA_REQ = CENTERGAME_LEVELLIMIT_BEGIN,   //从MYSQL读取所有数据
	MSG_LOADDATA_ACK,								  //返回数据中的数据内容
	MSG_ADDLEVELLIMIT,                                //增加一个封印数据
	MSG_UPDATELEVELLIMIT,                             //更新封印数据
	MSG_UPDATELEVELLIMITSTATE,                        //只需要改变封印的状态
	MSG_2ALLGAMEINFO,                                 //center server告知所有的GAME SERVER封印信息
	MSG_ACTIVELIMIT,                                  //通知center server激活封印
	MSG_UPDATEPLAYERCOUNT,                            //同步角色到达封印等级数量
	MSG_ADDPLAYERCOUNT_LIMIT,                         //通知center server增加到达封印等级的角色数量
	MSG_ACTIVELIMIT_ACK,                              //center server返回激活封印
	MSG_GS2CSREQLIMITINFO,                            //GAME SERVER请求封印信息
};


struct MsgLevelLimitModule : public Msg
{
	MsgLevelLimitModule()
	{
		SetModuleType( EMessageModule_LEVELLIMIT );
	}
};

struct MsgReqMYSQLData:public MsgLevelLimitModule
{
	MsgReqMYSQLData()
	{
		header.dwType = MSG_LOADDATA_REQ;
		header.stLength = sizeof(MsgReqMYSQLData);
	}
};

struct MsgAckMySQLData:public MsgLevelLimitModule
{
	MsgAckMySQLData()
	{
		header.dwType = MSG_LOADDATA_ACK;
		header.stLength = sizeof(MsgAckMySQLData) - sizeof( sllinfo );
		max_level = 0;
		ustCount = 0;
	}
	enum eMax
	{
		MaxCount = 100
	};

	short           max_level;
	unsigned short  ustCount;
	SLevelLimitInfo sllinfo[MaxCount];

	void AddData( SLevelLimitInfo& xData )
	{
		if ( IsFull() )
		{ return; }

		sllinfo[ ustCount ] = xData;
		++ustCount;
		header.stLength += sizeof( SLevelLimitInfo );
	}
	bool IsFull() { return ustCount >= MaxCount; }
	void Reset()
	{
		header.stLength = sizeof( MsgAckMySQLData ) - sizeof( sllinfo );
		ustCount = 0;
	}
};

struct MsgAddLevelLimit:public MsgLevelLimitModule
{
	MsgAddLevelLimit()
	{
		header.dwType = MSG_ADDLEVELLIMIT;
		header.stLength = sizeof(MsgAddLevelLimit);
	}
	SLevelLimitInfo sllinfo;
};

struct MsgUpdateLevelLimit:public MsgLevelLimitModule
{
	MsgUpdateLevelLimit()
	{
		header.dwType = MSG_UPDATELEVELLIMIT;
		header.stLength = sizeof(MsgUpdateLevelLimit);
	}
	SLevelLimitInfo sllinfo;
};

struct Msg2AllGameInfo:public MsgLevelLimitModule
{
	Msg2AllGameInfo()
	{
		header.dwType = MSG_2ALLGAMEINFO;
		header.stLength = sizeof(Msg2AllGameInfo);
	}
	SLevelLimitInfo sllinfo;
};

struct MsgActiveLimit:public MsgLevelLimitModule
{
	MsgActiveLimit()
	{
		header.dwType = MSG_ACTIVELIMIT;
		header.stLength = sizeof(MsgActiveLimit);
	}
	char active_name[eLimitGlobal_name];
};

struct MsgUpdatePlayerCount:public MsgLevelLimitModule
{
	MsgUpdatePlayerCount()
	{
		header.stLength = sizeof(MsgUpdatePlayerCount);
		header.dwType = MSG_UPDATEPLAYERCOUNT;
		_count = 0;
	}
	short _count;
};

struct MsgAddPlayerCountLimit:public MsgLevelLimitModule
{
	MsgAddPlayerCountLimit()
	{
		header.dwType = MSG_ADDPLAYERCOUNT_LIMIT;
		header.stLength = sizeof(MsgAddPlayerCountLimit);
		add_count = 0;
	}
	short add_count;
};

struct MsgActiveLimitAck:public MsgLevelLimitModule
{
	MsgActiveLimitAck()
	{
		header.dwType = MSG_ACTIVELIMIT_ACK;
		header.stLength = sizeof(MsgActiveLimitAck);
	}
	char active_name[eLimitGlobal_name];
	short _state;
};

struct MsgGS2CSReqLimitInfo:public MsgLevelLimitModule
{
	MsgGS2CSReqLimitInfo()
	{
		header.dwType = MSG_GS2CSREQLIMITINFO;
		header.stLength = sizeof(MsgGS2CSReqLimitInfo);
	}
};
struct MsgUpdateLevelLimitSate:public Msg
{
	MsgUpdateLevelLimitSate()
	{
		header.dwType = MSG_UPDATELEVELLIMITSTATE;
		header.stLength = sizeof(MsgUpdateLevelLimitSate);
	}
	short _state;
};
#pragma pack( pop )
#endif