#pragma once
#include "MsgBase.h"
//#include "GlobalDef.h"
//#include "GlobalDBManager.h"
#include "MessageRangeDefine.h"

struct GlobalDB //全局数据结构 可以自行添加数据
{
public:
	enum GlobalDBDefine
	{
		MAX_TimeHHandleSum = 256,
	};
	GlobalDB()
	{
		BattleSum = 0;//默认值
		MapCountryID = 0;
		for(unsigned int i =0;i<MAX_TimeHHandleSum;++i)
		{
			SetTimeHandleLog(i,0);
			SetTimeHandleState(i,0);
		}
	}

	void SetData(const GlobalDB& other)
	{
		SetBattleSum(other.GetBattleSum());
		SetMapCountryID(other.GetMapCountryID());
		for(unsigned int i =0;i<MAX_TimeHHandleSum;++i)
		{
			SetTimeHandleLog(i,other.GetTimeHandleLog(i));
			SetTimeHandleState(i,other.GetTimeHandleState(i));
		}
	}

	void Destroy()
	{
		//销毁函数
	}

	unsigned int GetBattleSum() const {return BattleSum;}
	void SetBattleSum(unsigned int Value){BattleSum = Value;}

	unsigned int GetMapCountryID() const {return MapCountryID;}
	void SetMapCountryID(unsigned int Value){MapCountryID = Value;}

	__int64 GetTimeHandleLog(unsigned int Index) const {return TimeHandleLog[Index];}
	void SetTimeHandleLog(unsigned int Index,__int64 Value){TimeHandleLog[Index] = Value;}

	int GetTimeHandleState(unsigned int Index) const {return TimeHandleState[Index];}
	void SetTimeHandleState(unsigned int Index,int Value){TimeHandleState[Index] = Value;}
private:
	unsigned int BattleSum;//战场的全局状态
	unsigned int MapCountryID;//野外战场地图所属国家ID 默认为0 表示无国家
	__int64 TimeHandleLog[MAX_TimeHHandleSum];//时间计数 
	int		TimeHandleState[MAX_TimeHHandleSum];//状态计数
};

enum GlobalDBMessageDefine
{
	CS2GS_LOADGLOBALDBREQ = GLOBALDB_SERVER_BEGIN, //读取数据库的数据
	CS2GS_LOADGLOBALDBACK, //读取数据库数据的命令的返回消息
	CS2GS_SAVEGLOBALDBREQ,
	GS2CS_UPDATEGLOBALDBREQ,
	CS2GS_UPDATEGLOBALDBACK,
	CS2GS_LOADINGLOBALDBACK,
};
struct MsgGolbalDBModule : public Msg
{
    MsgGolbalDBModule()
    {
        SetModuleType( EMessageModule_GolbalDB );
    }
};
struct GS2CSLoadGlobalDBReq : public MsgGolbalDBModule//读取数据请求
{
    GS2CSLoadGlobalDBReq()
    {
        header.dwType = CS2GS_LOADGLOBALDBREQ;
        header.stLength = sizeof( GS2CSLoadGlobalDBReq );	
    }
};
struct GS2CSLoadGlobalDBAck : public MsgGolbalDBModule//读取数据返回
{
    GS2CSLoadGlobalDBAck()
    {
        header.dwType = CS2GS_LOADGLOBALDBACK;
        header.stLength = sizeof( GS2CSLoadGlobalDBAck );	
    }
	GlobalDB info;
};
struct GS2CSSaveGlobalDBReq : public MsgGolbalDBModule//保存数据
{
    GS2CSSaveGlobalDBReq()
    {
        header.dwType = CS2GS_SAVEGLOBALDBREQ;
        header.stLength = sizeof( GS2CSSaveGlobalDBReq );	
    }
	GlobalDB info;
};
struct GS2CSUpdateGlobalDBReq : public MsgGolbalDBModule//修改数据请求
{
	GS2CSUpdateGlobalDBReq()
    {
        header.dwType = GS2CS_UPDATEGLOBALDBREQ;
        header.stLength = sizeof( GS2CSUpdateGlobalDBReq );	
    }
    uint8 uchUpdateType;
	uint32 Index;
    __int64 n64Value;
};

struct CS2GSUpdateGlobalDBAck : public MsgGolbalDBModule//修改数据返回
{
	CS2GSUpdateGlobalDBAck()
    {
        header.dwType = CS2GS_UPDATEGLOBALDBACK;
        header.stLength = sizeof( CS2GSUpdateGlobalDBAck );	
    }
    uint8 uchUpdateType;
	uint32 Index;
    __int64 n64Value;
};

struct CS2GSLoadGlobalDBAck : public MsgGolbalDBModule//GameServer请求获数据
{
	CS2GSLoadGlobalDBAck()
    {
        header.dwType = CS2GS_LOADINGLOBALDBACK;
        header.stLength = sizeof( CS2GSLoadGlobalDBAck );	
    }
	GlobalDB info;
};