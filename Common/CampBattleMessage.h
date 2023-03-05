#ifndef __CAMPBATTLEMESSAGEDEFINE_H__
#define __CAMPBATTLEMESSAGEDEFINE_H__

/************************************************************************
            ��Ӫս����Ϣ����
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "MsgBase.h"
#include "MessageRangeDefine.h"
#include "CampBattleDefine.h"
#include "GuildDefine.h"
#pragma pack( push, 1 )

enum CampBattleMessageDefine
{
    MSG_TELLCAMPBATTLESTATUS = GAMEWORD_CAMPBATTLEMSG_BEGIN,   
    MSG_TELLCAMPBATTLEKILLPLAYER,
    MSG_TELLCAMPBATTLERESOURCE,
    MSG_TELLCAMPBATTLEFIGHTCAMP,
    MSG_CAMPBATTLEPLAYERREQ,
    MSG_TELLCAMPBATTLEPLAYER,
    MSG_LEAVECAMPBATTLEREQ,
    MSG_FLYTOCAMPBATTLEREQ,
    MSG_FLYTOCAMPBATTLEACK,
    MSG_CAMPBATTLESIGNUPREQ,
    MSG_CAMPBATTLESIGNUPACK,
    MSG_ENTERCAMPBATTLEREQ,
    MSG_ENTERCAMPBATTLEACK,
    MSG_KILLCAMPBATTLEMONSTER,
    MSG_TELLCAMPBATTLEMATCH,


    MSG_SHOWCAMPGUILDBATTLEENTER,
    MSG_CAMPGUILDBATTLERESULT,
    MSG_TELLCAMPGUILDBATTLEUNMATCH,
    MSG_TELLCAMPGUILDBATTLEREFRESHMONSTER,

    MSG_TELLCAMPBATTLESIGNUPREPLACE,
    MSG_TELLCOUNTERBATTLERESULT,
    MSG_TELLCAMPBATTLEDEATHCOUNT,
    MSG_TELLCOUNTRYBATTLEEGUILD,
    MSG_QUETYCOUNTRYBATTLESIGNUPACK,
    MSG_TELLCOUNTERBATTLEPLAYERCOUNT,
	MSG_CAMPWORLDBATTLEACK,
	MSG_GETGLOBALDBBATTLESUMREQ,
	MSG_GETGLOBALDBBATTLESUMACK,
	MSG_CAMPBATTLESIGNUPSECC,
	MSG_CAMPBATTLECHECKCAMPBATTLEVALUESUM,
	MSG_CAMPGUILDBATTLEREWARDINFO,
};

struct MsgCampBattleModule : public Msg
{
    MsgCampBattleModule()
    {
        SetModuleType( EMessageModule_CampBattle );
    }
};

// ֪ͨ��Ӫս��״̬
struct MsgTellCampBattleStatus : public MsgCampBattleModule
{
    MsgTellCampBattleStatus()
    {
        header.dwType = MSG_TELLCAMPBATTLESTATUS;
        header.stLength = sizeof( MsgTellCampBattleStatus );
        nLeftTime = 0;
    }

    unsigned char uchCampBattleType;    // ��Ӫս������
    unsigned char uchCampBattleStatus;  // ��Ӫս��״̬
    unsigned int nLeftTime;             // ʣ��ʱ�� (��λ: ��, nLeftTime == 0ʱ, ����Ҫ����ʣ��ʱ�� )
};

// ֪ͨ��Ӫս��ɱ��
struct MsgTellCampBattleKillPlayer : public MsgCampBattleModule
{
    MsgTellCampBattleKillPlayer()
    {
        header.dwType = MSG_TELLCAMPBATTLEKILLPLAYER;
        header.stLength = sizeof( MsgTellCampBattleKillPlayer );
    }

    enum EConstDefine
    {
        TypeFirstKill = 1,  // һѪ
        TypeKeepKill,       // ����ɱ��
        TypeBeKill,         // �ս�ɱ��
        TypeTotalKill,      // �ܹ�ɱ��
    };

    unsigned char uchCampBattleType;                // ��Ӫս������
    unsigned char uchKillType;                      // ɱ������( �����ж��� )
    char szKillerName[ CampDefine::NameLength ];    // ɱ����
    char szBeKillName[ CampDefine::NameLength ];    // ��ɱ��
    unsigned short ustKillCount;                    // ɱ������( ��ɱʱ������ )
    unsigned short ustStringID;                     // �㲥ʹ�õ�StringID;
};

// ͬ��ս����Դ��
struct MsgTellCampBattleResource : public MsgCampBattleModule
{
    MsgTellCampBattleResource()
    {
        header.dwType = MSG_TELLCAMPBATTLERESOURCE;
        header.stLength = sizeof( MsgTellCampBattleResource );
    }
	unsigned int nRedGuildID;
	unsigned int nBlueGuildID;
    unsigned int nRedResource;      // �췽��Դ
    unsigned int nBlueResource;     // ������Դ
	unsigned int nRedTotleKillSum;
	unsigned int nBlueTotleKillSum;
	float nRedAtterHp[4];
	float nBlueAtterHp[4];
};

// ֪ͨ�ͻ�����Ӫ��Ϣ
struct MsgTellCampBattleFightCamp : public MsgCampBattleModule
{
    MsgTellCampBattleFightCamp()
    {
        header.dwType = MSG_TELLCAMPBATTLEFIGHTCAMP;
        header.stLength = sizeof( MsgTellCampBattleFightCamp );
    }

    GameObjectId ustPlayerID; // ��Ҷ�̬ID
    unsigned char uchFightCamp; // ��Ӫ
};

// �ͻ�������ɱ����Ϣ
struct MsgCampBattlePlayerReq : public MsgCampBattleModule
{
    MsgCampBattlePlayerReq()
    {
        header.dwType = MSG_CAMPBATTLEPLAYERREQ;
        header.stLength = sizeof( MsgCampBattlePlayerReq );
    }
    
    enum EConstDefine
    {
        TypeSelfCamp = 1,   // �����Լ���Ӫ
        TypeTargetCamp,     // ����Է���Ӫ
        TypeAllCamp,        // ����˫����Ӫ
    };

    unsigned char uchReqType;   // ��������
};

// ��Ӫս����ɱ����Ϣ
struct MsgTellCampBattlePlayer : public MsgCampBattleModule
{
    MsgTellCampBattlePlayer()
    {
        header.dwType = MSG_TELLCAMPBATTLEPLAYER;
        header.stLength = sizeof( MsgTellCampBattlePlayer ) - sizeof( xPlayer );

        uchCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 200,
    };

    unsigned char uchCampBattleType;    // ��Ӫս������
    unsigned char uchCount;
    BattlePlayer xPlayer[ MaxCount ];

    void AddBattlePlayer( BattlePlayer& xData )
    {
        if ( uchCount >= MaxCount )
        { return; }

        xPlayer[ uchCount ] = xData;
        ++uchCount;
        header.stLength += sizeof ( BattlePlayer );
    }
};

// �����뿪ս��
struct MsgLeaveCampBattleReq : public MsgCampBattleModule
{
    MsgLeaveCampBattleReq()
    {
        header.dwType = MSG_LEAVECAMPBATTLEREQ;
        header.stLength = sizeof( MsgLeaveCampBattleReq );
    }
};

// ������֪ͨ�ͻ����Ƿ�Ҫ���������Ӫս��
struct MsgFlyToCampBattleReq : public MsgCampBattleModule
{
    MsgFlyToCampBattleReq()
    {
        header.dwType = MSG_FLYTOCAMPBATTLEREQ;
        header.stLength = sizeof( MsgFlyToCampBattleReq );
    }

    unsigned char uchBattleType;
    unsigned int nMapID;    // ConfigMapID
	unsigned int nKingdomID; //��������id
	float nKingdomX;
	float nKingdomY;
	unsigned int RedID;
	unsigned int BlueID;
};

// �ͻ���ͬ�������Ӫս��, ���������͸���ҵ�NPC��
struct MsgFlyToCampBattleAck : public MsgCampBattleModule
{
    MsgFlyToCampBattleAck()
    {
        header.dwType = MSG_FLYTOCAMPBATTLEACK;
        header.stLength = sizeof( MsgFlyToCampBattleAck );
    }

    unsigned int nMapID;    // ConfigMapID
};

// ������Ӫս��
struct MsgCampBattleSignUpReq : public MsgCampBattleModule
{
    MsgCampBattleSignUpReq()
    {
        header.dwType = MSG_CAMPBATTLESIGNUPREQ;
        header.stLength = sizeof( MsgCampBattleSignUpReq );
    }

    unsigned char uchBattleType;
};

// �����������
struct MsgCampBattleSignUpAck : public MsgCampBattleModule
{
	MsgCampBattleSignUpAck()
	{
		header.dwType = MSG_CAMPBATTLESIGNUPACK;
		header.stLength = sizeof( MsgCampBattleSignUpAck );
		uchWarxishu = 0;
		unhGuildxishu = 0;
	}

	unsigned char uchWarxishu;
	unsigned char uchResult;
	unsigned char unhGuildxishu;
};
struct MsgCampBattleSignUpSecc : public MsgCampBattleModule
{
	MsgCampBattleSignUpSecc()
	{
		header.dwType = MSG_CAMPBATTLESIGNUPSECC;
		header.stLength = sizeof( MsgCampBattleSignUpSecc );
	}
	unsigned int RedGuildID;
	unsigned int BlueGuildID;
};
struct MsgCampBattleCheckCampBattleValueSum : public MsgCampBattleModule
{
	MsgCampBattleCheckCampBattleValueSum()
	{
		header.dwType = MSG_CAMPBATTLECHECKCAMPBATTLEVALUESUM;
		header.stLength = sizeof( MsgCampBattleCheckCampBattleValueSum );
	}
	unsigned int redguildid;
	unsigned int blueguildid;
	bool redlose;
	bool bulelose;
};



// ������Ӫս������
struct MsgEnterCampBattleReq : public MsgCampBattleModule
{
    MsgEnterCampBattleReq()
    {
        header.dwType = MSG_ENTERCAMPBATTLEREQ;
        header.stLength = sizeof( MsgEnterCampBattleReq );
    }

    unsigned char uchBattleType;    // ��Ӫս������
};

// ����ս���������
struct MsgEnterCampBattleAck : public MsgCampBattleModule
{
    MsgEnterCampBattleAck()
    {
        header.dwType = MSG_ENTERCAMPBATTLEACK;
        header.stLength = sizeof( MsgEnterCampBattleAck );
    }

    unsigned char uchResult;
};

// ս��ɱ������
struct MsgKillCampBattleMonster : public MsgCampBattleModule
{
    MsgKillCampBattleMonster()
    {
        header.dwType = MSG_KILLCAMPBATTLEMONSTER;
        header.stLength = sizeof( MsgKillCampBattleMonster );
    }

    unsigned char uchBattleType;
    unsigned char uchFightCamp;    
    int nMonsterID; // ����ID
    int nStringID;  // �㲥��ID
};

// ֪ͨ��Ӫս�������б�
struct MsgTellCampBattleMatch : public MsgCampBattleModule
{
    MsgTellCampBattleMatch()
    {
        header.dwType = MSG_TELLCAMPBATTLEMATCH;
        header.stLength = sizeof( MsgTellCampBattleMatch );
    }

    unsigned char uchBattleType;
    unsigned int nRedID;
    unsigned int nBlueID;
};


// ֪ͨ���ɰ���, ��ı����б��������ɶ�����
struct MsgTellCampBattleSignUpReplace : public MsgCampBattleModule
{
    MsgTellCampBattleSignUpReplace()
    {
        header.dwType = MSG_TELLCAMPBATTLESIGNUPREPLACE;
        header.stLength = sizeof( MsgTellCampBattleSignUpReplace );
    }

    unsigned char uchBattleType;    // ��Ӫս������
};

struct MsgTellCampBattleDeathCount : public MsgCampBattleModule
{
    MsgTellCampBattleDeathCount()
    {
        header.dwType = MSG_TELLCAMPBATTLEDEATHCOUNT;
        header.stLength = sizeof( MsgTellCampBattleDeathCount );
    }

    uint8 nDeathCount;  // ��ǰ��������
    uint8 nMaxCount;    // �����������
};

////////////////////////////////////////////////////////////////////////////////
// ��������ս��ϢЭ��
// ��ʾ��������ս���봰��
struct MsgShowCampGuildBattleEnter : public MsgCampBattleModule
{
    MsgShowCampGuildBattleEnter()
    {
        header.dwType = MSG_SHOWCAMPGUILDBATTLEENTER;
        header.stLength = sizeof( MsgShowCampGuildBattleEnter );
    }

    unsigned char uchBattleType;    // ��Ӫս������

    unsigned int nRedGuildID;   // �췽����ID
    unsigned int nBlueGuildID;  // ��������ID
};

// ��������ս���
struct MsgCampGuildBattleResult : public MsgCampBattleModule
{
    MsgCampGuildBattleResult()
    {
        header.dwType = MSG_CAMPGUILDBATTLERESULT;
        header.stLength = sizeof( MsgCampGuildBattleResult );
    }

    unsigned int nWinGuildID;   // ʤ������ID
    unsigned int nLoseGuildID;  // ʤ������ID
};

struct MsgCampGuildBattleRewardInfo : public MsgCampBattleModule
{
	const static int MaxLength = 10;
    MsgCampGuildBattleRewardInfo()
    {
        header.dwType = MSG_CAMPGUILDBATTLEREWARDINFO;
        header.stLength = sizeof( MsgCampGuildBattleRewardInfo);
    }

	/*void calclength()
	{
		header.stLength = sizeof( MsgCampGuildBattleRewardInfo) - (MaxLength-OtherSum*2) * sizeof(unsigned int);
	}*/

    unsigned int nWinGuildID;   // ʤ������ID
    unsigned int nLoseGuildID; 
	unsigned int WinItemID;
	unsigned int LoseItemID;
	unsigned int OtherItemID;
	unsigned int OtherSum;
	unsigned int KissSum;
	unsigned int PlayerID[MaxLength];
	char Name[MaxLength][GuildDefine::MaxNameLength];
	unsigned int Point[MaxLength];
	//unsigned int Info[MaxLength];
};

// ֪ͨ����, ��İ������һ������û��ƥ����, ���ܲμӰ�������ս
struct MsgTellCampGuildBattleUnMatch : public MsgCampBattleModule
{
    MsgTellCampGuildBattleUnMatch()
    {
        header.dwType = MSG_TELLCAMPGUILDBATTLEUNMATCH;
        header.stLength = sizeof( MsgTellCampGuildBattleUnMatch );
    }
};

// ֪ͨս�������, ĳĳ��ˢ������
struct MsgTellCampGuildBattleRefreshMonster : public MsgCampBattleModule
{
    MsgTellCampGuildBattleRefreshMonster()
    {
        header.dwType = MSG_TELLCAMPGUILDBATTLEREFRESHMONSTER;
        header.stLength = sizeof( MsgTellCampGuildBattleRefreshMonster );
    }

    int nMonsterID;
    int nStringID;
};


///////////////////////////////////////////////////////////////////////////////////
// ��������ս, ��������ս, ��ȸ����ս ��Ϣ
// ȫ���㲥ĳ�����ɻ����ս���ʸ�
struct MsgTellCountryBattleGuild : public MsgCampBattleModule
{
    MsgTellCountryBattleGuild()
    {
        header.dwType = MSG_TELLCOUNTRYBATTLEEGUILD;
        header.stLength = sizeof( MsgTellCountryBattleGuild );
    }

    uint8 uchBattleType;      // ����ս������ ( 1 2 3 �ֱ���  ���� ����  ��ȸս��,  ��CountryDefine.h���ж��� )
    uint32 nGuildID;          // ����ʸ�İ���ID
};

// ֪ͨ����ս�����
struct MsgTellCountryBattleResult : public MsgCampBattleModule
{
    MsgTellCountryBattleResult()
    {
        header.dwType = MSG_TELLCOUNTERBATTLERESULT;
        header.stLength = sizeof( MsgTellCountryBattleResult );
    }

    uint8 uchBattleType;      // ����ս������ ( 1 2 3  �ֱ���  ���� ����  ��ȸս��,  ��CountryDefine.h���ж��� )
    uint8 uchWinType;         // ʤ����ʽ
    uint32 nGuildID;          // ʤ�����ID
};

// ��ѯ����ս������
struct MsgQueryCountryBattleSignUpAck : public MsgCampBattleModule
{
    MsgQueryCountryBattleSignUpAck()
    {
        header.dwType = MSG_QUETYCOUNTRYBATTLESIGNUPACK;
        header.stLength = sizeof( MsgQueryCountryBattleSignUpAck );

        uchResult = ECD_Success;
        nGuildID = 0;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_NotOpen,            // ���ڱ���״̬, ���ܲ�ѯ
    };

    uint8 uchBattleType;      // ����ս������ ( 1 2 3  �ֱ���  ���� ����  ��ȸս��,  ��CountryDefine.h���ж��� )
    uint8 uchResult;          // ������( ֻ��ʧ�ܲ�����Ϣ���� )
    uint32 nGuildID;          // �����ɹ��İ��ID
};

// ����ս����Ա����, �Լ������������� ( �췽�������޷�, �����������޷� )
struct MsgTellCountryBattlePlayerCount : public MsgCampBattleModule
{
    MsgTellCountryBattlePlayerCount()
    {
        header.dwType = MSG_TELLCOUNTERBATTLEPLAYERCOUNT;
        header.stLength = sizeof( MsgTellCountryBattlePlayerCount );
        nRedCount = 0;
        nBlueCount = 0;
    }

    uint16 nRedCount;   
    uint16 nBlueCount;

    uint16 nRedMasterDeathCount;    // �췽������������
    uint16 nBlueMasterDeathCount;   // ����������������
};


struct MsgCampWorldBattleAck : public MsgCampBattleModule
{
	enum WorldBattleDefine
	{
		WBD_Prepare = 1, //׼��
		WBD_Fight = 2, // ��ʼ
		WBD_End = 3, // ����
	};
	MsgCampWorldBattleAck()
	{
		header.dwType = MSG_CAMPWORLDBATTLEACK;
		header.stLength = sizeof( MsgCampWorldBattleAck );
	}
	unsigned char uchResult;
	unsigned int  GlobalDBCOuntryID;
};

struct MsgGetGlobalDBBattleSumReq : public MsgCampBattleModule
{
    MsgGetGlobalDBBattleSumReq()
    {
        header.dwType = MSG_GETGLOBALDBBATTLESUMREQ;
        header.stLength = sizeof( MsgGetGlobalDBBattleSumReq );
    }
};

struct MsgGetGlobalDBBattleSumAck : public MsgCampBattleModule
{
    MsgGetGlobalDBBattleSumAck()
    {
        header.dwType = MSG_GETGLOBALDBBATTLESUMACK;
        header.stLength = sizeof( MsgGetGlobalDBBattleSumAck );
    }
	int Sum;
};
////////////////////////////////////////////////////////////////////////////////////

#pragma pack( pop )

#endif