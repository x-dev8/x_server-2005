#ifndef __LEVELLIMITMESSAGE_H1__
#define __LEVELLIMITMESSAGE_H1__

#include "MsgBase.h"
#include "LevelLimitDefine.h"
#include "MessageRangeDefine.h"

#pragma pack( push, 1 )

enum LevelLimitMessageDefine
{
	MSG_LOADDATA_REQ = CENTERGAME_LEVELLIMIT_BEGIN,   //��MYSQL��ȡ��������
	MSG_LOADDATA_ACK,								  //���������е���������
	MSG_ADDLEVELLIMIT,                                //����һ����ӡ����
	MSG_UPDATELEVELLIMIT,                             //���·�ӡ����
	MSG_UPDATELEVELLIMITSTATE,                        //ֻ��Ҫ�ı��ӡ��״̬
	MSG_2ALLGAMEINFO,                                 //center server��֪���е�GAME SERVER��ӡ��Ϣ
	MSG_ACTIVELIMIT,                                  //֪ͨcenter server�����ӡ
	MSG_UPDATEPLAYERCOUNT,                            //ͬ����ɫ�����ӡ�ȼ�����
	MSG_ADDPLAYERCOUNT_LIMIT,                         //֪ͨcenter server���ӵ����ӡ�ȼ��Ľ�ɫ����
	MSG_ACTIVELIMIT_ACK,                              //center server���ؼ����ӡ
	MSG_GS2CSREQLIMITINFO,                            //GAME SERVER�����ӡ��Ϣ
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