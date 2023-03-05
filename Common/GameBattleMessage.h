#pragma once
#include "MsgBase.h"
#include "MessageRangeDefine.h"
#include "GlobalDef.h"
#include "GameBattleDefine.h"
#include "GuildDefine.h"
enum GameBattleMessageDefine
{
	MSG_TELLGAMEBATTLESTATUS = GAMEBATTLE_BEGIN,
	MSG_SHOWGAMEGUILDBATTLEENTER,
	MSG_ENTERGAMEBATTLEACK,
	MSG_TELLGAMEBATTLERESOURCE,
	MSG_TELLGAMEBATTLEKILLPLAYER,
	MSG_TELLGAMEBATTLEPLAYER,
	MSG_TELLGAMEBATTLEMATCH,
	MSG_KILLGAMEBATTLEMONSTER,
	MSG_GAMEGUILDBATTLERESULT,
	MSG_TELLGAMEBATTLEFIGHTCAMP,


	CS2DB_LOADCAMPBATTLEDATA,
	DB2CS_LOADCAMPBATTLEDATA,
	CS2GS_LOADCAMPBATTLEDATA,
	MSG_LOADCAMPBATTLEDATAREQ,
	MSG_LOADCAMPBATTLEDATAACK,

	MSG_CAMPBATTLENEWDATAREQ,
	GS2CS_CAMPBATTLENEWDATAREQ,
	CS2GS_CAMPBATTLENEWDATAREQ,
	MSG_CAMPBATTLENEWDATAACK,
	MSG_ADDCAMPBATTLEDATAREQ,
	GS2CS_ADDCAMPBATTLEDATA,
	CS2DB_ADDCAMPBATTLEDATA,
	CS2GS_ADDCAMPBATTLEDATA,
	MSG_ADDCAMPBATTLEDATAACK,

	MSG_DELCAMPBATTLEDATAREQ,
	GS2CS_DELCAMPBATTLEDATA,
	CS2DB_DELCAMPBATTLEDATA,
	CS2GS_DELCAMPBATTLEDATA,
	MSG_DELCAMPBATTLEDATAACK,
	MSG_GAMEBATTLEERRORACK,
	MSG_FLYTOGAMEBATTLEREQ,
	MSG_ENTERGAMEBATTLEREQ,

	//GS2CS_ENTERGAMEBATTLEREQ,
	//CS2GS_ENTERGAMEBATTLEACK,

	GS2CS_DELPLAYERMONEY,
	CS2GS_DELPLAYERMONEY,

	GS2CS_CAMPBATTLEADDERROR,
	CS2GS_CAMPBATTLEADDERROR,
	MSG_UPDTECAMPBATTLECD,
};
struct MsgGameBattleModule : public Msg
{
    MsgGameBattleModule()
    {
        SetModuleType( EMessageModule_GameBattle );
    }
};

struct MsgTellGameBattleStatus : public MsgGameBattleModule
{
    MsgTellGameBattleStatus()
    {
        header.dwType = MSG_TELLGAMEBATTLESTATUS;
        header.stLength = sizeof( MsgTellGameBattleStatus );
        nLeftTime = 0;
    }
    unsigned char uchCampBattleType;    // 阵营战场类型
    unsigned char uchCampBattleStatus;  // 阵营战场状态
    unsigned int nLeftTime;             // 剩余时间 (单位: 秒, nLeftTime == 0时, 不需要处理剩余时间 )
};
struct MsgShowGameGuildBattleEnter : public MsgGameBattleModule
{
    MsgShowGameGuildBattleEnter()
    {
        header.dwType = MSG_SHOWGAMEGUILDBATTLEENTER;
        header.stLength = sizeof( MsgShowGameGuildBattleEnter );
    }

    unsigned char uchBattleType;    // 阵营战场类型
    unsigned int nRedGuildID;   // 红方帮派ID
    unsigned int nBlueGuildID;  // 蓝方帮派ID
};
struct MsgEnterGameBattleAck : public MsgGameBattleModule
{
    MsgEnterGameBattleAck()
    {
        header.dwType = MSG_ENTERGAMEBATTLEACK;
        header.stLength = sizeof( MsgEnterGameBattleAck );
    }

    unsigned char uchResult;
};
struct MsgTellGameBattleResource : public MsgGameBattleModule
{
    MsgTellGameBattleResource()
    {
        header.dwType = MSG_TELLGAMEBATTLERESOURCE;
        header.stLength = sizeof( MsgTellGameBattleResource );
    }
	unsigned int nRedGuildID;
	unsigned int nBlueGuildID;
    unsigned int nRedResource;      // 红方资源
    unsigned int nBlueResource;     // 蓝方资源
	unsigned int nRedTotleKillSum;
	unsigned int nBlueTotleKillSum;
	float nRedAtterHp[4];
	float nBlueAtterHp[4];
};
struct MsgTellGameBattleKillPlayer : public MsgGameBattleModule
{
    MsgTellGameBattleKillPlayer()
    {
        header.dwType = MSG_TELLGAMEBATTLEKILLPLAYER;
        header.stLength = sizeof( MsgTellGameBattleKillPlayer );
    }

    enum EConstDefine
    {
        TypeFirstKill = 1,  // 一血
        TypeKeepKill,       // 连续杀人
        TypeBeKill,         // 终结杀人
        TypeTotalKill,      // 总共杀人
    };

    unsigned char uchCampBattleType;                // 阵营战场类型
    unsigned char uchKillType;                      // 杀人类型( 上面有定义 )
    char szKillerName[ GameBattleDefine::NameLength ];    // 杀人者
    char szBeKillName[ GameBattleDefine::NameLength ];    // 被杀者
    unsigned short ustKillCount;                    // 杀人数量( 被杀时的数量 )
    unsigned short ustStringID;                     // 广播使用的StringID;
};

struct MsgTellGameBattlePlayer : public MsgGameBattleModule
{
    MsgTellGameBattlePlayer()
    {
        header.dwType = MSG_TELLGAMEBATTLEPLAYER;
        header.stLength = sizeof( MsgTellGameBattlePlayer ) - sizeof( xPlayer );

        uchCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 200,
    };

    unsigned char uchCampBattleType;    // 阵营战场类型
    unsigned char uchCount;
	GameBattleDefine::BattlePlayer xPlayer[ MaxCount ];

	void AddBattlePlayer( GameBattleDefine::BattlePlayer& xData )
    {
        if ( uchCount >= MaxCount )
        { return; }

        xPlayer[ uchCount ] = xData;
        ++uchCount;
		header.stLength += sizeof ( GameBattleDefine::BattlePlayer );
    }
};
struct MsgTellGameBattleMatch : public MsgGameBattleModule
{
    MsgTellGameBattleMatch()
    {
        header.dwType = MSG_TELLGAMEBATTLEMATCH;
        header.stLength = sizeof( MsgTellGameBattleMatch );
    }

    unsigned char uchBattleType;
    unsigned int nRedID;
    unsigned int nBlueID;
};
struct MsgKillGameBattleMonster : public MsgGameBattleModule
{
    MsgKillGameBattleMonster()
    {
        header.dwType = MSG_KILLGAMEBATTLEMONSTER;
        header.stLength = sizeof( MsgKillGameBattleMonster );
    }

    unsigned char uchBattleType;
    unsigned char uchFightCamp;    
    int nMonsterID; // 怪物ID
    int nStringID;  // 广播的ID
};
struct MsgGameGuildBattleResult : public MsgGameBattleModule
{
    MsgGameGuildBattleResult()
    {
        header.dwType = MSG_GAMEGUILDBATTLERESULT;
        header.stLength = sizeof( MsgGameGuildBattleResult );
    }

    unsigned int nWinGuildID;   // 胜利帮派ID
    unsigned int nLoseGuildID;  // 胜利帮派ID
};
struct MsgTellGameBattleFightCamp : public MsgGameBattleModule
{
    MsgTellGameBattleFightCamp()
    {
        header.dwType = MSG_TELLGAMEBATTLEFIGHTCAMP;
        header.stLength = sizeof( MsgTellGameBattleFightCamp );
    }

    GameObjectId ustPlayerID; // 玩家动态ID
    unsigned char uchFightCamp; // 阵营
};


static const int GuildBattleDataMaxSum = 10;
struct CS2DBLoadCampBattleData:public MsgGameBattleModule
{
	CS2DBLoadCampBattleData()
	{
		header.stLength = sizeof(CS2DBLoadCampBattleData);
		header.dwType = CS2DB_LOADCAMPBATTLEDATA;
	}
};
struct DB2CSLoadCampBattleData:public MsgGameBattleModule
{	
	DB2CSLoadCampBattleData()
	{
		header.stLength = sizeof(DB2CSLoadCampBattleData);
		header.dwType = DB2CS_LOADCAMPBATTLEDATA;
	}
	bool PushInfo(GameBattleDefine::GuildCampBattle& pInfo,bool DataIsEnd)
	{
		info[Sum] = pInfo;
		++Sum;
		if(DataIsEnd)
		{
			IsEnd = true;
			return true;
		}
		else if(Sum == GuildBattleDataMaxSum)
		{
			IsEnd = false;
			return true;
		}
		else
		{
			return false;
		}
	}
	void ClearAllData()
	{
		Sum = 0;
		IsEnd = false;
		memset(info,0,sizeof(GameBattleDefine::GuildCampBattle)*GuildBattleDataMaxSum);
	}
	GameBattleDefine::GuildCampBattle info[GuildBattleDataMaxSum];
	int Sum;
	bool IsEnd;
};
struct CS2GSLoadCampBattleData:public MsgGameBattleModule
{
	CS2GSLoadCampBattleData()
	{
		header.stLength = sizeof(CS2GSLoadCampBattleData);
		header.dwType = CS2GS_LOADCAMPBATTLEDATA;
	}
	bool PushInfo(GameBattleDefine::GuildCampBattle& pInfo,bool DataIsEnd)
	{
		info[Sum] = pInfo;
		++Sum;
		if(DataIsEnd)
		{
			IsEnd = true;
			return true;
		}
		else if(Sum == GuildBattleDataMaxSum)
		{
			IsEnd = false;
			return true;
		}
		else
		{
			return false;
		}
	}
	void ClearAllData()
	{
		Sum = 0;
		IsEnd = false;
		memset(info,0,sizeof(GameBattleDefine::GuildCampBattle)*GuildBattleDataMaxSum);
	}
	GameBattleDefine::GuildCampBattle info[GuildBattleDataMaxSum];
	int Sum;
	bool IsEnd;
};
struct MsgLoadCampBattleDataReq:public MsgGameBattleModule
{
	MsgLoadCampBattleDataReq()
	{
		header.stLength = sizeof(MsgLoadCampBattleDataReq);
		header.dwType = MSG_LOADCAMPBATTLEDATAREQ;
	}
};
struct MsgLoadCampBattleDataAck:public MsgGameBattleModule
{
	MsgLoadCampBattleDataAck()
	{
		header.stLength = sizeof(MsgLoadCampBattleDataAck);
		header.dwType = MSG_LOADCAMPBATTLEDATAACK;
	}
	bool PushInfo(GameBattleDefine::GuildCampBattle& pInfo,bool DataIsEnd)
	{
		info[Sum] = pInfo;
		++Sum;
		if(DataIsEnd)
		{
			IsEnd = true;
			return true;
		}
		else if(Sum == GuildBattleDataMaxSum)
		{
			IsEnd = false;
			return true;
		}
		else
		{
			return false;
		}
	}
	void ClearAllData()
	{
		Sum = 0;
		IsEnd = false;
		memset(info,0,sizeof(GameBattleDefine::GuildCampBattle)*GuildBattleDataMaxSum);
	}
	GameBattleDefine::GuildCampBattle info[GuildBattleDataMaxSum];
	int Sum;
	bool IsEnd;
};

struct MsgCampBattleNewDataReq:public MsgGameBattleModule
{
	MsgCampBattleNewDataReq()
	{
		header.stLength = sizeof(MsgCampBattleNewDataReq);
		header.dwType = MSG_CAMPBATTLENEWDATAREQ;
	}
	GameBattleDefine::GuildCampBattle add;
	char info[GameBattleDefine::MaxGameGuildGeneralBattleInfoLength];
};
struct GS2CSCampBattleNewDataReq :public MsgGameBattleModule
{
	GS2CSCampBattleNewDataReq()
	{
		header.stLength = sizeof(GS2CSCampBattleNewDataReq);
		header.dwType = GS2CS_CAMPBATTLENEWDATAREQ;
	}
	GameBattleDefine::GuildCampBattle add;
	char info[GameBattleDefine::MaxGameGuildGeneralBattleInfoLength];
};
struct CS2GSCampBattleNewDataReq :public MsgGameBattleModule
{
	CS2GSCampBattleNewDataReq()
	{
		header.stLength = sizeof(CS2GSCampBattleNewDataReq);
		header.dwType = CS2GS_CAMPBATTLENEWDATAREQ;
	}
	GameBattleDefine::GuildCampBattle add;
	char info[GameBattleDefine::MaxGameGuildGeneralBattleInfoLength];
};
struct MsgCampBattleNewDataAck:public MsgGameBattleModule
{
	MsgCampBattleNewDataAck()
	{
		header.stLength = sizeof(MsgCampBattleNewDataAck);
		header.dwType = MSG_CAMPBATTLENEWDATAACK;
	}
	GameBattleDefine::GuildCampBattle add;
	char info[GameBattleDefine::MaxGameGuildGeneralBattleInfoLength];
	char srcGuildName[GuildDefine::MaxNameLength];
};
struct MsgAddCampBattleDataReq:public MsgGameBattleModule
{
	MsgAddCampBattleDataReq()
	{
		header.stLength = sizeof(MsgAddCampBattleDataReq);
		header.dwType = MSG_ADDCAMPBATTLEDATAREQ;
	}
	GameBattleDefine::GuildCampBattle add;
	bool Result;
};
struct GS2CSAddCampBattleData:public MsgGameBattleModule
{
	GS2CSAddCampBattleData()
	{
		header.stLength = sizeof(GS2CSAddCampBattleData);
		header.dwType = GS2CS_ADDCAMPBATTLEDATA;
	}
	GameBattleDefine::GuildCampBattle add;
	bool Result;
};
struct CS2DBAddCampBattleData:public MsgGameBattleModule
{
	CS2DBAddCampBattleData()
	{
		header.stLength = sizeof(CS2DBAddCampBattleData);
		header.dwType = CS2DB_ADDCAMPBATTLEDATA;
	}
	GameBattleDefine::GuildCampBattle add;
	bool IsUpadte;
	bool Result;
};
struct CS2GSAddCampBattleData:public MsgGameBattleModule
{
	CS2GSAddCampBattleData()
	{
		header.stLength = sizeof(CS2GSAddCampBattleData);
		header.dwType = CS2GS_ADDCAMPBATTLEDATA;
	}
	GameBattleDefine::GuildCampBattle add;
	bool Result;
};
struct MsgAddCampBattleDataAck:public MsgGameBattleModule
{
	MsgAddCampBattleDataAck()
	{
		header.stLength = sizeof(MsgAddCampBattleDataAck);
		header.dwType = MSG_ADDCAMPBATTLEDATAACK;
	}
	GameBattleDefine::GuildCampBattle add;
	bool Result;
};


struct MsgDelCampBattleDataReq:public MsgGameBattleModule
{
	MsgDelCampBattleDataReq()
	{
		header.stLength = sizeof(MsgDelCampBattleDataReq);
		header.dwType = MSG_DELCAMPBATTLEDATAREQ;
	}
	unsigned int ID;
};
struct GS2CSDelCampBattleData:public MsgGameBattleModule
{
	GS2CSDelCampBattleData()
	{
		header.stLength = sizeof(GS2CSDelCampBattleData);
		header.dwType = GS2CS_DELCAMPBATTLEDATA;
	}
	unsigned int ID;
};
struct CS2DBDelCampBattleData:public MsgGameBattleModule
{
	CS2DBDelCampBattleData()
	{
		header.stLength = sizeof(CS2DBDelCampBattleData);
		header.dwType = CS2DB_DELCAMPBATTLEDATA;
	}
	unsigned int ID;
};
struct CS2GSDelCampBattleData:public MsgGameBattleModule
{
	CS2GSDelCampBattleData()
	{
		header.stLength = sizeof(CS2GSDelCampBattleData);
		header.dwType = CS2GS_DELCAMPBATTLEDATA;
	}
	unsigned int ID;
};
struct MsgDelCampBattleDataAck:public MsgGameBattleModule
{
	MsgDelCampBattleDataAck()
	{
		header.stLength = sizeof(MsgDelCampBattleDataAck);
		header.dwType = MSG_DELCAMPBATTLEDATAACK;
	}
	unsigned int ID;
};

struct MsgGameBattleErrorAck:public MsgGameBattleModule
{
	MsgGameBattleErrorAck()
	{
		header.stLength = sizeof(MsgGameBattleErrorAck);
		header.dwType = MSG_GAMEBATTLEERRORACK;
	}
	unsigned int Info;
};
struct MsgFlyToGameBattleReq : public MsgGameBattleModule
{
    MsgFlyToGameBattleReq()
    {
        header.dwType = MSG_FLYTOGAMEBATTLEREQ;
        header.stLength = sizeof( MsgFlyToGameBattleReq );
    }

    unsigned char uchBattleType;
    unsigned int nMapID;    // ConfigMapID
	unsigned int nKingdomID; //国家主城id
	float nKingdomX;
	float nKingdomY;
	unsigned int RedID;
	unsigned int BlueID;
};
struct MsgEnterGameBattleReq : public MsgGameBattleModule
{
    MsgEnterGameBattleReq()
    {
        header.dwType = MSG_ENTERGAMEBATTLEREQ;
        header.stLength = sizeof( MsgEnterGameBattleReq );
    }

    unsigned int uchBattleType;    // 阵营战场类型
};
struct GS2CSDelPlayerMoney:public MsgGameBattleModule
{
	GS2CSDelPlayerMoney()
	{
		header.stLength = sizeof(GS2CSDelPlayerMoney);
		header.dwType = GS2CS_DELPLAYERMONEY;
	}
	GameBattleDefine::GuildCampBattle add;
};
struct CS2GSSDelPlayerMoney:public MsgGameBattleModule
{
	CS2GSSDelPlayerMoney()
	{
		header.stLength = sizeof(CS2GSSDelPlayerMoney);
		header.dwType = CS2GS_DELPLAYERMONEY;
	}
	GameBattleDefine::GuildCampBattle add;
};

struct GS2CSCampBattleAddError :public MsgGameBattleModule
{
	GS2CSCampBattleAddError()
	{
		header.stLength = sizeof(GS2CSCampBattleAddError);
		header.dwType = GS2CS_CAMPBATTLEADDERROR;
	}
	unsigned int PlayerID;
	unsigned int ErrorID;
	bool Result;
	GameBattleDefine::GuildCampBattle add;
};
struct CS2GSCampBattleAddError :public MsgGameBattleModule
{
	CS2GSCampBattleAddError()
	{
		header.stLength = sizeof(CS2GSCampBattleAddError);
		header.dwType = CS2GS_CAMPBATTLEADDERROR;
	}
	unsigned int PlayerID;
	unsigned int ErrorID;
	bool Result;
};

struct MsgUpdateAddCampBattleCD:public MsgGameBattleModule
{
	MsgUpdateAddCampBattleCD()
	{
		header.stLength = sizeof(MsgUpdateAddCampBattleCD);
		header.dwType = MSG_UPDTECAMPBATTLECD;
	}
	__int64 Time;
};