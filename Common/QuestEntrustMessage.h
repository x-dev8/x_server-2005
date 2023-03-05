#pragma once
#include "MsgBase.h"
#include "MessageRangeDefine.h"
#include "GlobalDef.h"
#include "QuestEntrustDefine.h"
enum QuestEntrustMessageDefine
{
	//数据库和中央服务器
	CS2DB_REQUESTQUESTENTRUSTDATAREQ = GAMEWORD_QUESTENTRUST_BEGIN,
	DB2CS_REQUESTQUESTENTRUSTDATAACK,
	
	CS2DB_ADDQUESTENTRUSTDATAACK,
	CS2DB_QUESTENTRUSTDELETEREQ,
	CS2DB_QUESTENTRUSTDATASAVEREQ,
	//中央服务器和GameServer
	GS2CS_LOADQUESTENTRUSTDATAREQ,
	CS2GS_LOADQUESTENTRUSTDATAACK,

	GS2CS_ADDQUESTENTRUSTREQ,
	CS2GS_ADDQUESTENTRUSTACK,

	GS2CS_DELQUESTENTRUSTREQ,
	CS2GS_DELQUESTENTRUSTACK,

	GS2CS_UPDATEJOINQUESTENTRUSTREQ,
	CS2GS_UPDATEJOINQUESTENTRUSTACK,

	GS2CS_UPDATECANELQUESTENTRUSTREQ,
	CS2GS_UPDATECANELQUESTENTRUSTACK,

	GS2CS_QUESTENTRUSTSECCREQ,
	CS2GS_QUESTENTRUSTSECCACK,

	GS2CS_QUESTENTRUSTENDREQ,
	CS2GS_QUESTENTRUSTENDACK,

	//GameServer和Client
	MSG_LOADQUESTENTRUSTDATAREQ,
	MSG_LOADQUESTENTRUSTDATAACK,
	//添加委托
	MSG_ADDQUESTENTRUSTREQ,
	MSG_ADDQUESTENTRUSTACK,
	//取消委托
	MSG_DELQUESTENTRUSTREQ,
	MSG_DELQUESTENTRUSTACK,

	MSG_UPDATEJOINQUESTENTRUSTREQ,
	MSG_UPDATEJOINQUESTENTRUSTACK,
	
	MSG_UPDATECANELQUESTENTRUSTREQ,
	MSG_UPDATECANELQUESTENTRUSTACK,

	MSG_QUESTENTRUSTSECCREQ,

	MSG_QUESTENTRUSTNEEDUPDATE,
	MSG_QUESTENTRUSTINFOACK,
	MSG_QUESTENTRUSTSHOWINFO,
};
struct MsgQuestEntrustModule : public Msg
{
    MsgQuestEntrustModule()
    {
        SetModuleType( EMessageModule_QuestEntrust );
    }
};
struct CS2DBRequestQuestEntrustDataReq : public MsgQuestEntrustModule
{
    CS2DBRequestQuestEntrustDataReq()
    {
        header.dwType = CS2DB_REQUESTQUESTENTRUSTDATAREQ;
        header.stLength = sizeof( CS2DBRequestQuestEntrustDataReq );
    }
};
struct DBS2CSRequestQuestEntrustDataAck : public MsgQuestEntrustModule
{
    DBS2CSRequestQuestEntrustDataAck()
    {
        header.dwType = DB2CS_REQUESTQUESTENTRUSTDATAACK;
        header.stLength = sizeof( DBS2CSRequestQuestEntrustDataAck );
    }
	void SetLength()
	{
		 header.stLength = sizeof( DBS2CSRequestQuestEntrustDataAck ) - (QuestEntrustMaxLength-Sum)*sizeof(QuestEntrustStates);
	}
	bool PushInfo(QuestEntrustStates& info,bool InfoIsEnd)
	{
		//添加数据
		List[Sum] = info;
		++Sum;
		if(InfoIsEnd)
		{
			IsEnd = true;
			SetLength();
			return true;
		}
		else
		{
			IsEnd = false;
			if(Sum == QuestEntrustMaxLength)
			{
				SetLength();
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	void ClearAllInfo()
	{
		Sum = 0;
		IsEnd = false;
		for(int i =0;i<QuestEntrustMaxLength;++i)
		{
			List[i].ID = 0;
		}
	}
	bool    IsEnd;//命令是分次的 最后个为true  其他为false
	int		Sum;
	QuestEntrustStates	List[QuestEntrustMaxLength];
};
struct CS2DBAddQuestEntrustDataAck : public MsgQuestEntrustModule
{
	CS2DBAddQuestEntrustDataAck()
    {
        header.dwType = CS2DB_ADDQUESTENTRUSTDATAACK;
        header.stLength = sizeof( CS2DBAddQuestEntrustDataAck );
    }
	void SetLength()
	{
		 header.stLength = sizeof( CS2DBAddQuestEntrustDataAck );
	}
	bool PushInfo(QuestEntrustStates& info,bool InfoIsEnd)
	{
		//添加数据
		List[Sum] = info;
		++Sum;
		if(InfoIsEnd)
		{
			IsEnd = true;
			SetLength();
			return true;
		}
		else
		{
			IsEnd = false;
			if(Sum == QuestEntrustMaxLength)
			{
				SetLength();
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	void ClearAllInfo()
	{
		Sum = 0;
		IsEnd = false;
		for(int i =0;i<QuestEntrustMaxLength;++i)
		{
			List[i].ID = 0;
		}
	}
	bool    IsEnd;//命令是分次的 最后个为true  其他为false
	int		Sum;
	QuestEntrustStates	List[QuestEntrustMaxLength];
};
struct CS2DBQuestEntrustDeleteReq : public MsgQuestEntrustModule
{
	CS2DBQuestEntrustDeleteReq()
    {
        header.dwType = CS2DB_QUESTENTRUSTDELETEREQ;
        header.stLength = sizeof( CS2DBQuestEntrustDeleteReq );
    }
	//unsigned int ID;
	void SetLength()
	{
		 header.stLength = sizeof( CS2DBQuestEntrustDeleteReq );
	}
	bool PushInfo(unsigned int info,bool InfoIsEnd)
	{
		//添加数据
		List[Sum] = info;
		++Sum;
		if(InfoIsEnd)
		{
			IsEnd = true;
			SetLength();
			return true;
		}
		else
		{
			IsEnd = false;
			if(Sum == QuestEntrustMaxLength)
			{
				SetLength();
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	void ClearAllInfo()
	{
		Sum = 0;
		IsEnd = false;
		for(int i =0;i<QuestEntrustMaxLength;++i)
		{
			List[i] = 0;
		}
	}
	bool    IsEnd;//命令是分次的 最后个为true  其他为false
	int		Sum;
	unsigned int	List[QuestEntrustMaxLength];
};
struct CS2DBQuestEntrustDataSaveReq : public MsgQuestEntrustModule
{
	CS2DBQuestEntrustDataSaveReq()
    {
        header.dwType = CS2DB_QUESTENTRUSTDATASAVEREQ;
        header.stLength = sizeof( CS2DBQuestEntrustDataSaveReq );
    }
	//QuestEntrustStates info;
	void SetLength()
	{
		 header.stLength = sizeof( CS2DBQuestEntrustDataSaveReq );
	}
	bool PushInfo(QuestEntrustStates& info,bool InfoIsEnd)
	{
		//添加数据
		List[Sum] = info;
		++Sum;
		if(InfoIsEnd)
		{
			IsEnd = true;
			SetLength();
			return true;
		}
		else
		{
			IsEnd = false;
			if(Sum == QuestEntrustMaxLength)
			{
				SetLength();
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	void ClearAllInfo()
	{
		Sum = 0;
		IsEnd = false;
		for(int i =0;i<QuestEntrustMaxLength;++i)
		{
			List[i].ID = 0;
		}
	}
	bool    IsEnd;//命令是分次的 最后个为true  其他为false
	int		Sum;
	QuestEntrustStates	List[QuestEntrustMaxLength];
};
struct GS2CSLoadQuestEntrustDataReq : public MsgQuestEntrustModule
{
	GS2CSLoadQuestEntrustDataReq()
    {
        header.dwType = GS2CS_LOADQUESTENTRUSTDATAREQ;
        header.stLength = sizeof( GS2CSLoadQuestEntrustDataReq );
    }
};
struct CS2GSLoadQuestEntrustDataAck : public MsgQuestEntrustModule
{
    CS2GSLoadQuestEntrustDataAck()
    {
        header.dwType = CS2GS_LOADQUESTENTRUSTDATAACK;
        header.stLength = sizeof( CS2GSLoadQuestEntrustDataAck );
    }
	void SetLength()
	{
		//服务器间的通讯不用
		 header.stLength =  sizeof( CS2GSLoadQuestEntrustDataAck );//sizeof( CS2GSLoadQuestEntrustDataAck ) - (QuestEntrustMaxLength-Sum)*sizeof(QuestEntrustStates);
	}
	bool PushInfo(QuestEntrustStates& info,bool InfoIsEnd)
	{
		//添加数据
		List[Sum] = info;
		++Sum;
		if(InfoIsEnd)
		{
			IsEnd = true;
			SetLength();
			return true;
		}
		else
		{
			IsEnd = false;
			if(Sum == QuestEntrustMaxLength)
			{
				SetLength();
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	void ClearAllInfo()
	{
		Sum = 0;
		IsEnd = false;
		for(int i =0;i<QuestEntrustMaxLength;++i)
		{
			List[i].ID = 0;
		}
	}
	bool    IsEnd;//命令是分次的 最后个为true  其他为false
	int		Sum;
	QuestEntrustStates	List[QuestEntrustMaxLength];
};

struct GS2CSAddQuestEntrustReq : public MsgQuestEntrustModule
{
	GS2CSAddQuestEntrustReq()
    {
        header.dwType = GS2CS_ADDQUESTENTRUSTREQ;
        header.stLength = sizeof( GS2CSAddQuestEntrustReq );
    }
	QuestEntrustStates info;
};
struct CS2GSAddQuestEntrustAck : public MsgQuestEntrustModule
{
	CS2GSAddQuestEntrustAck()
    {
        header.dwType = CS2GS_ADDQUESTENTRUSTACK;
        header.stLength = sizeof( CS2GSAddQuestEntrustAck );
    }
	QuestEntrustStates info;
};

struct GS2CSDelQuestEntrustReq : public MsgQuestEntrustModule
{
	GS2CSDelQuestEntrustReq()
    {
        header.dwType = GS2CS_DELQUESTENTRUSTREQ;
        header.stLength = sizeof( GS2CSDelQuestEntrustReq );
    }
	unsigned int ID;
};
struct CS2GSDelQuestEntrustAck : public MsgQuestEntrustModule
{
	CS2GSDelQuestEntrustAck()
    {
        header.dwType = CS2GS_DELQUESTENTRUSTACK;
        header.stLength = sizeof( CS2GSDelQuestEntrustAck );
    }
	unsigned int ID;
	bool IsTimeEnd;//是否为时间到了删除的
};

struct GS2CSUpdateJoinQuestEntrustReq : public MsgQuestEntrustModule
{
	GS2CSUpdateJoinQuestEntrustReq()
    {
        header.dwType = GS2CS_UPDATEJOINQUESTENTRUSTREQ;
        header.stLength = sizeof( GS2CSUpdateJoinQuestEntrustReq );
    }
	QuestEntrustStates info;
};
struct CS2GSUpdateJoinQuestEntrustAck : public MsgQuestEntrustModule
{
	CS2GSUpdateJoinQuestEntrustAck()
    {
        header.dwType = CS2GS_UPDATEJOINQUESTENTRUSTACK;
        header.stLength = sizeof( CS2GSUpdateJoinQuestEntrustAck );
    }
	QuestEntrustStates info;
};

struct GS2CSUpdateCanelQuestEntrustReq : public MsgQuestEntrustModule
{
	GS2CSUpdateCanelQuestEntrustReq()
    {
        header.dwType = GS2CS_UPDATECANELQUESTENTRUSTREQ;
        header.stLength = sizeof( GS2CSUpdateCanelQuestEntrustReq );
    }
	QuestEntrustStates info;
};
struct CS2GSUpdateCanelQuestEntrustAck : public MsgQuestEntrustModule
{
	CS2GSUpdateCanelQuestEntrustAck()
    {
        header.dwType = CS2GS_UPDATECANELQUESTENTRUSTACK;
        header.stLength = sizeof( CS2GSUpdateCanelQuestEntrustAck );
    }
	QuestEntrustStates info;
};

struct MsgLoadQuestEntrustDataReq : public MsgQuestEntrustModule
{
	MsgLoadQuestEntrustDataReq()
    {
        header.dwType = MSG_LOADQUESTENTRUSTDATAREQ;
        header.stLength = sizeof( MsgLoadQuestEntrustDataReq );
    }
};
struct MsgLoadQuestEntrustDataAck : public MsgQuestEntrustModule
{
    MsgLoadQuestEntrustDataAck()
    {
        header.dwType = MSG_LOADQUESTENTRUSTDATAACK;
        header.stLength = sizeof( MsgLoadQuestEntrustDataAck );
    }
	void SetLength()
	{
		 header.stLength = sizeof( MsgLoadQuestEntrustDataAck ) - (QuestEntrustMaxLength-Sum)*sizeof(QuestEntrustStates);
	}
	bool PushInfo(QuestEntrustStates& info,bool InfoIsEnd)
	{
		//添加数据
		List[Sum] = info;
		++Sum;
		if(InfoIsEnd)
		{
			IsEnd = true;
			SetLength();
			return true;
		}
		else
		{
			IsEnd = false;
			if(Sum == QuestEntrustMaxLength)
			{
				SetLength();
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	void ClearAllInfo()
	{
		Sum = 0;
		IsEnd = false;
		for(int i =0;i<QuestEntrustMaxLength;++i)
		{
			List[i].ID = 0;
		}
	}
	bool    IsEnd;//命令是分次的 最后个为true  其他为false
	int		Sum;
	QuestEntrustStates	List[QuestEntrustMaxLength];
};

struct MsgAddQuestEntrustReq : public MsgQuestEntrustModule
{
	MsgAddQuestEntrustReq()
    {
        header.dwType = MSG_ADDQUESTENTRUSTREQ;
        header.stLength = sizeof( MsgAddQuestEntrustReq );
    }
	QuestEntrustStates info;
};
struct MsgAddQuestEntrustAck : public MsgQuestEntrustModule
{
	MsgAddQuestEntrustAck()
    {
        header.dwType = MSG_ADDQUESTENTRUSTACK;
        header.stLength = sizeof( MsgAddQuestEntrustAck );
    }
	QuestEntrustStates info;
};


struct MsgDelQuestEntrustReq : public MsgQuestEntrustModule
{
	MsgDelQuestEntrustReq()
    {
		header.dwType = MSG_DELQUESTENTRUSTREQ;
        header.stLength = sizeof( MsgDelQuestEntrustReq );
    }
	unsigned int ID;
};
struct MsgDelQuestEntrustAck : public MsgQuestEntrustModule//提示玩家 委托过期就 自动删除了
{
	MsgDelQuestEntrustAck()
    {
		header.dwType = MSG_DELQUESTENTRUSTACK;
        header.stLength = sizeof( MsgDelQuestEntrustAck );
    }
	unsigned int ID;
};

struct MsgUpdateJoinQuestEntrustReq : public MsgQuestEntrustModule
{
	MsgUpdateJoinQuestEntrustReq()
    {
		header.dwType = MSG_UPDATEJOINQUESTENTRUSTREQ;
        header.stLength = sizeof( MsgUpdateJoinQuestEntrustReq );
    }
	unsigned int ID;
};
struct MsgUpdateJoinQuestEntrustAck : public MsgQuestEntrustModule
{
	MsgUpdateJoinQuestEntrustAck()
    {
		header.dwType = MSG_UPDATEJOINQUESTENTRUSTACK;
        header.stLength = sizeof( MsgUpdateJoinQuestEntrustAck );
    }
	QuestEntrustStates info;
};


struct MsgUpdateCanelQuestEntrustReq : public MsgQuestEntrustModule
{
	MsgUpdateCanelQuestEntrustReq()
    {
		header.dwType = MSG_UPDATECANELQUESTENTRUSTREQ;
        header.stLength = sizeof( MsgUpdateCanelQuestEntrustReq );
    }
	unsigned int ID;
};
struct MsgUpdateCanelQuestEntrustAck : public MsgQuestEntrustModule
{
	MsgUpdateCanelQuestEntrustAck()
    {
		header.dwType = MSG_UPDATECANELQUESTENTRUSTACK;
        header.stLength = sizeof( MsgUpdateCanelQuestEntrustAck );
    }
	QuestEntrustStates info;
};

struct MsgQuestEntrustSeccReq : public MsgQuestEntrustModule
{
	MsgQuestEntrustSeccReq()
    {
		header.dwType = MSG_QUESTENTRUSTSECCREQ;
        header.stLength = sizeof( MsgQuestEntrustSeccReq );
    }
	unsigned int ID;
};

struct GS2CSQuestEntrustSeccReq : public MsgQuestEntrustModule
{
	GS2CSQuestEntrustSeccReq()
    {
		header.dwType = GS2CS_QUESTENTRUSTSECCREQ;
        header.stLength = sizeof( GS2CSQuestEntrustSeccReq );
    }
	unsigned int ID;
};

struct CS2GSQuestEntrustSeccAck : public MsgQuestEntrustModule
{
	CS2GSQuestEntrustSeccAck()
    {
		header.dwType = CS2GS_QUESTENTRUSTSECCACK;
        header.stLength = sizeof( CS2GSQuestEntrustSeccAck );
    }
	unsigned int ID;
};

struct GS2CSQuestEntrustEndReq : public MsgQuestEntrustModule
{
	GS2CSQuestEntrustEndReq()
    {
		header.dwType = GS2CS_QUESTENTRUSTENDREQ;
        header.stLength = sizeof( GS2CSQuestEntrustEndReq );
    }
	unsigned int ID;
};
struct CS2GSQuestEntrustEndAck : public MsgQuestEntrustModule
{
	CS2GSQuestEntrustEndAck()
    {
		header.dwType = CS2GS_QUESTENTRUSTENDACK;
        header.stLength = sizeof( CS2GSQuestEntrustEndAck );
    }
	unsigned int ID;
};
struct MsgQuestEntrustNeedUpdate : public MsgQuestEntrustModule
{
	MsgQuestEntrustNeedUpdate()
    {
		header.dwType = MSG_QUESTENTRUSTNEEDUPDATE;
        header.stLength = sizeof( MsgQuestEntrustNeedUpdate );
    }
};
struct MsgQuestEntrustInfoAck : public MsgQuestEntrustModule
{
	MsgQuestEntrustInfoAck()
    {
		header.dwType = MSG_QUESTENTRUSTINFOACK;
        header.stLength = sizeof( MsgQuestEntrustInfoAck );
    }
	unsigned int ID;
};

struct MsgQuestEntrustShowInfo : public MsgQuestEntrustModule
{
	MsgQuestEntrustShowInfo()
    {
		header.dwType = MSG_QUESTENTRUSTSHOWINFO;
        header.stLength = sizeof( MsgQuestEntrustShowInfo );
    }
	unsigned int ID;
};