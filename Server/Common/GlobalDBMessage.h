#pragma once
#include "MsgBase.h"
//#include "GlobalDef.h"
//#include "GlobalDBManager.h"
#include "MessageRangeDefine.h"

struct GlobalDB //ȫ�����ݽṹ ���������������
{
public:
	enum GlobalDBDefine
	{
		MAX_TimeHHandleSum = 256,
	};
	GlobalDB()
	{
		BattleSum = 0;//Ĭ��ֵ
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
		//���ٺ���
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
	unsigned int BattleSum;//ս����ȫ��״̬
	unsigned int MapCountryID;//Ұ��ս����ͼ��������ID Ĭ��Ϊ0 ��ʾ�޹���
	__int64 TimeHandleLog[MAX_TimeHHandleSum];//ʱ����� 
	int		TimeHandleState[MAX_TimeHHandleSum];//״̬����
};

enum GlobalDBMessageDefine
{
	CS2GS_LOADGLOBALDBREQ = GLOBALDB_SERVER_BEGIN, //��ȡ���ݿ������
	CS2GS_LOADGLOBALDBACK, //��ȡ���ݿ����ݵ�����ķ�����Ϣ
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
struct GS2CSLoadGlobalDBReq : public MsgGolbalDBModule//��ȡ��������
{
    GS2CSLoadGlobalDBReq()
    {
        header.dwType = CS2GS_LOADGLOBALDBREQ;
        header.stLength = sizeof( GS2CSLoadGlobalDBReq );	
    }
};
struct GS2CSLoadGlobalDBAck : public MsgGolbalDBModule//��ȡ���ݷ���
{
    GS2CSLoadGlobalDBAck()
    {
        header.dwType = CS2GS_LOADGLOBALDBACK;
        header.stLength = sizeof( GS2CSLoadGlobalDBAck );	
    }
	GlobalDB info;
};
struct GS2CSSaveGlobalDBReq : public MsgGolbalDBModule//��������
{
    GS2CSSaveGlobalDBReq()
    {
        header.dwType = CS2GS_SAVEGLOBALDBREQ;
        header.stLength = sizeof( GS2CSSaveGlobalDBReq );	
    }
	GlobalDB info;
};
struct GS2CSUpdateGlobalDBReq : public MsgGolbalDBModule//�޸���������
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

struct CS2GSUpdateGlobalDBAck : public MsgGolbalDBModule//�޸����ݷ���
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

struct CS2GSLoadGlobalDBAck : public MsgGolbalDBModule//GameServer���������
{
	CS2GSLoadGlobalDBAck()
    {
        header.dwType = CS2GS_LOADINGLOBALDBACK;
        header.stLength = sizeof( CS2GSLoadGlobalDBAck );	
    }
	GlobalDB info;
};