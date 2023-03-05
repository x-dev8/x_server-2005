#ifndef __GAMECOUNTRYMESSAGE_H__
#define __GAMECOUNTRYMESSAGE_H__

/************************************************************************
            ������Ϣ����
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "MsgBase.h"
#include "MessageRangeDefine.h"
#include "CountryDefine.h"
#include "GlobalDef.h"

#pragma pack( push, 1 )

enum CountryMessageDefine
{
    MSG_TELLCOUNTRYTITLEINFO = GAMEWORD_COUNTRYMSG_BEGIN,          // �㲥���ҳƺ�
    MSG_QUERYCOUNTRYINFOREQ,                                       // �鿴������Ϣ
    MSG_QUERYCOUNTRYINFOACK,                                       // �鿴������Ϣ
	MSG_UPDATECOUNTRYINFOACK,                                      // ���¹�����Ϣ
    MSG_TELLCOUNTRYQUERYSTATUS,                                    // ֪ͨ��������״̬
    MSG_COUNTRYNOTICECHANGEREQ,                                    // ������Ĺ��ҹ���
    MSG_COUNTRYNOTICECHANGEACK,                                    // ���Ĺ��ҹ������
    MSG_COUNTRYQUESTSTATECHANGEREQ,                                // ���󷢲���������
    MSG_COUNTRYQUESTSTATECHANGEACK,                                // ���󷢲������������
    MSG_COUNTRYOFFICIALAPPOINTREQ,                                 // �����������ҹ�Ա
    MSG_COUNTRYOFFICIALAPPOINTACK,                                 // �����������ҹ�Ա����
    MSG_COUNTRYOFFICIALRECALLREQ,                                  // ����������ҹ�Ա
    MSG_COUNTRYOFFICIALRECALLACK,                                  // ����������ҹ�Ա����
    MSG_COUNTRYQUESTSTATUSSTOP,                                    // ֪ͨĳ�����ҷ������������
    MSG_TELLCOUNTRYKILLPOSITION,                                   // ȫ����㲥ɱ����ĳ����Ա
    MSG_COUNTRYREQUESTRAISEREQ,                                    // �������ļ��
    MSG_COUNTRYREQUESTRAISEACK,                                    // ����ļ������
    MSG_COUNTRYRAISETOPLAYERREQ,                                   // ���������ļ��
    MSG_COUNTRYRAISETOPLAYERACK,                                   // ���ļ�����
    MSG_COUNTRYRAISETELLPLAYER,                                    // ֪ͨ���ļ�����
    MSG_COUNTRYRECEIVEMOUNTACK,                                    // ��ȡ����������
    MSG_TELLCOUNTRYBORDERSFIGHT,                                   // ֪ͨ�߾����ڱ��ַ�
    MSG_TELLCOUNTRYKILLENEMY,                                      // ֪ͨĳ��ҵ����˵й�����
    MSG_COUNTRYFLYTOBORDERSREQ,                                    // ���Ҳ������������
    MSG_COUNTRYOPERATETOPLAYERREQ,                                 // ��������
    MSG_COUNTRYOPERATETOPLAYERACK,                                 // ���Ի���
    MSG_COUNTRYTELLOPERATETOPLAYER,                                // ֪ͨ���������㱻������
    MSG_COUNTRYCONVENERESULT,                                      // ��������ټ�������� 
    MSG_COUNTRYCONVENEREQ,                                         // �����ټ�
    MSG_COUNTRYCONVENEACK,                                         // �ټ�
    MSG_COUNTRYCOUNTRYAPPOINT,                                     // ֪ͨ���������߱���ְ
    MSG_COUNTRYTELLCOUNTRYID,                                      // ֪ͨ������Ϣ( �ѹ�ʹ�� )
    MSG_COUNTRYCHANGEREQ,
    MSG_COUNTRYCHANGEACK,
    MSG_TELLOPERATETOCOUNTRY,
    MSG_COUNTRYTELLWEAK,
	MSG_COUNTRYTELLSTRONG,
    MSG_COUNTRYBATTLEREPLACE,
    MSG_TELLCOUNTRYNAME,
    MSG_CHANGECOUNTRYNAMEREQ,
    MSG_CHANGECOUNTRYNAMEACK,
    MSG_TELLCOUNTRYNAMECHANGE,
    MSG_TELLCOUNTRYSTATUS,
    MSG_UPDATECOUNTRYWARFIGHTKILL,
    MSG_TELLCOUNTRYPLAYERRAISE,
	MSG_DELCOUNTRYOFFICIALREQ,

    GS2CS_COUNTRYNOTICECHANGEREQ = CENTERGAME_COUNTRY_BEGIN,        
    CS2GS_COUNTRYNOTICECHANGEACK,
    GS2CS_COUNTRYQUESTSTATUSCHANGEREQ,
    CS2GS_COUNTRYQUESTSTATUSCHANGEACK,
    GS2CS_COUNTRYOFFICIALAPPOINTREQ,
    GS2CS_COUNTRYOFFICIALRECALLREQ,
	GS2CS_DELCOUNTRYOFFICIALREQ,
    CS2GS_COUNTRYDATECHANGEED,                                       // �������ڸı���
    CS2GS_COUNTRYQUESTSTATUSSTOP,                                    // ���ҷ�������ʱ�䵽��
    CS2GS_COUNTRYDATALIST,
	CS2GS_COUNTRYWEAKSTRONGTH,
    GS2CS_COUNTRYBATTLERESULT,
    CS2GS_COUNTRYBATTLERESULT,
	GS2CS_ADDCOUNTRYOFFICIAL,
    GS2CS_COUNTRYREQUESTRAISEREQ,
    CS2GS_COUNTRYREQUESTRAISEACK,
    GS2CS_COUNTRYMONEYRAISEED,
	GS2CS_RAISECOUNTRYPLAYERITEM,
    GS2CS_COUNTRYBORDERSFIHGT,
    CS2GS_COUNTRYBORDERSFIHGT,
    GS2CS_COUNTRYOPERATETOPLAYERREQ,
    CS2GS_COUNTRYOPERATETOPLAYERREQ,
    GS2CS_COUNTRYOPERATETOPLAYERACK,
    CS2GS_COUNTRYOPERATETOPLAYERACK,
    GS2CS_COUNTRYCONVENEREQ,
    CS2GS_COUNTRYCONVENEREQ,

    GS2CS_COUNTRYSETOFFICIAL,
    CS2GS_COUNTRYSETOFFICIAL,
    CS2GS_COUNTRYDATAUPDATE,
    GS2CS_COUNTRYCHANGERESULT,
    CS2GS_COUNTRYOFFICIALCHANGE,
	CS2GS_COUNTRYOFFICIALREWARD,
    GS2CS_COUNTRYDATACHANGEREQ,
    CS2GS_TELLWEAKCOUNTRY,
	CS2GS_TELLSTRONGCOUNTRY,
    GS2CS_CHANGECOUNTRYNAMEREQ,
    CS2GS_COUNTRYNAMECHANGE,
    CS2GS_COUNTRYWARSTATUS,
    GS2CS_COUNTRYWARKILLPLAYER,
    CS2GS_COUNTRYWARKILLPLAYER,
    GS2CS_COUNTRYWARSTATUSCHANGE,
    GS2CS_COUNTRYPLAYERCHANGE,
	CS2GS_ADDCOUNTRYOFFICIAL,
    // DB����
    CS2DB_REQUESTCOUNTRYDATAREQ,                                     // ������ع�����Դ
    DB2CS_REQUESTCOUNTRYDATAACK,                                     // ������ع�����Դ����
    CS2DB_COUNTRYDATESAVEREQ,										// ������Ϣ���浽���ݿ�
	CS2CS_GS2CSCountryBattleReward,									//��ս����
	CS2DB_COUNTRYOFFICEREQ,
	DB2CS_REQUESTCOUNTRYOFFICECK,
	//CS2CS_GS2CSDeleteCountryBattleReward,							//ɾ������ս����
	MSG_COUNTRYFLYMAP,
	MSG_COUNTRYFLYMAPREQ,
	MSG_TELLCOUNTRYPLAYERRAISEITEM,
	CS2GS_ADDCOUNTRYINFOACK,
	GS2CS_ADDCOUNTRYINFOREQ,
	MSG_ADDCOUNTRYINFOREQ,
	DB2CS_REQUESTCOUNTRYINFOACK,
	CS2DB_REQUESTCOUNTRYINFOREQ,
	CS2GS_REQUESTCOUNTRYINFOACK,
	MSG_LOADCOUNTRYINFOREQ,
	MSG_LOADCOUNTRYINFOACK,

	MSG_COUNTRYBUFFCHANGE,
	MSG_COUNTRYBUFFCHANGEACK,

	MSG_TELLCHANGECOUNTRY  = 3033,
};

struct MsgCountryModule : public Msg
{
    MsgCountryModule()
    {
        SetModuleType( EMessageModule_Country );
    }
};

// ͬ�����ҳƺŸ��ͻ���
struct MsgTellCountryTitleInfo : public MsgCountryModule
{
    MsgTellCountryTitleInfo()
    {
        header.dwType = MSG_TELLCOUNTRYTITLEINFO;
        header.stLength = sizeof( MsgTellCountryTitleInfo );
    }

    GameObjectId stPlayerID;      // ���ID
    uint16  stCountryTitle;     // ���ҳƺ�
};

// ֪ͨ��������״̬, �����, �ͻ����ڻ�б�����Ҫ�������
struct MsgTellCountryQuestStatus : public MsgCountryModule
{
    MsgTellCountryQuestStatus()
    {
        header.dwType = MSG_TELLCOUNTRYQUERYSTATUS;
        header.stLength = sizeof( MsgTellCountryQuestStatus ) - sizeof( xQuest );
        nCount = 0;
    }
    
    enum EConstDefine
    {
        MaxCount = 4,
    };

    struct QuestStatus
    {
        QuestStatus() : bNeedNotice( false ), n64StartTime( 0 )
        {
        }

        uint8 uchType;          // ��������
        __int64 n64StartTime;   // ��ʼʱ��
        bool bNeedNotice;       // �Ƿ���Ҫ��ʾ֪ͨ
    };

    int nCount;
    QuestStatus xQuest[ MaxCount ];

    void AddQuestStatus( QuestStatus& xInfo )
    {
        if ( nCount >= MaxCount )
        { return; }
    
        xQuest[ nCount ] = xInfo;
        ++nCount;
        header.stLength += sizeof( QuestStatus );
    }
};

struct MsgCountryFlyMap : public MsgCountryModule
{
    MsgCountryFlyMap()
    {
        header.dwType = MSG_COUNTRYFLYMAP;
        header.stLength = sizeof( MsgCountryFlyMap );
    }
    uint8 uchType;// ��������
};
struct MsgCountryFlyMapReq : public MsgCountryModule
{
    MsgCountryFlyMapReq()
    {
        header.dwType = MSG_COUNTRYFLYMAPREQ;
        header.stLength = sizeof( MsgCountryFlyMapReq );
    }
    uint8 uchType;// ��������
};
struct MsgAddCountryInfoReq : public MsgCountryModule
{
    MsgAddCountryInfoReq()
    {
        header.dwType = MSG_ADDCOUNTRYINFOREQ;
        header.stLength = sizeof( MsgAddCountryInfoReq );
    }
    char szNotice[ CountryDefine::MaxCountryInfoLength ];
	int Value;
	__int64 Time;
};
// �����޸Ĺ��ҹ���
struct MsgCountryNoticeChangeReq : public MsgCountryModule
{
    MsgCountryNoticeChangeReq()
    {
        header.dwType = MSG_COUNTRYNOTICECHANGEREQ;
        header.stLength = sizeof( MsgCountryNoticeChangeReq );
    }

    char szNotice[ CountryDefine::MaxNoticeLength ];
};

// �޸Ĺ��ҹ������
struct MsgCountryNoticeChangeAck : public MsgCountryModule
{
    MsgCountryNoticeChangeAck()
    {
        header.dwType = MSG_COUNTRYNOTICECHANGEACK;
        header.stLength = sizeof( MsgCountryNoticeChangeAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,    // �޸ĳɹ�
        ECD_NotRight,       // û��Ȩ��
        ECD_TimeLimit,      // ʱ������
        ECD_NotEnoughMoney, // �����ʽ𲻹�
    };

    uint8 uchResult;
};

// ���󷢲���������
struct MsgQueryCountryInfoReq : public MsgCountryModule
{
    MsgQueryCountryInfoReq()
    {
        header.dwType = MSG_QUERYCOUNTRYINFOREQ;
        header.stLength = sizeof( MsgQueryCountryInfoReq );
    }
};

struct MsgLoadCountryInfoReq : public MsgCountryModule
{
    MsgLoadCountryInfoReq()
    {
        header.dwType = MSG_LOADCOUNTRYINFOREQ;
        header.stLength = sizeof( MsgLoadCountryInfoReq );
    }
};
struct MsgLoadCountryInfoAck : public MsgCountryModule
{
    MsgLoadCountryInfoAck()
    {
        header.dwType = MSG_LOADCOUNTRYINFOACK;
        header.stLength = sizeof( MsgLoadCountryInfoAck );

		memset( Info, 0, sizeof( Info ) );
		memset( Time, 0, sizeof( Time ) );
		memset( values, 0, sizeof( values ) );
		Sum = 0;
		IsEnd = false;
    }
	int Sum;
	char Info[CountryDefine::MaxMsgCountryInfoSum][CountryDefine::MaxCountryInfoLength];
	__int64 Time[CountryDefine::MaxMsgCountryInfoSum];
	int values[CountryDefine::MaxMsgCountryInfoSum];
	bool IsEnd;
};

//zhuxincong 9.18 ���¹�����Ϣ������˵Ǯ����Ʒ
struct MsgUpdateCountryDate : public MsgCountryModule
{
	MsgUpdateCountryDate()
	{
		header.dwType = MSG_UPDATECOUNTRYINFOACK;
		header.stLength = sizeof(MsgUpdateCountryDate);
	}

	int nValue;
	char chType;

};


// ֪ͨ�������񷢲�״̬
struct MsgQueryCountryInfoAck : public MsgCountryModule
{
    MsgQueryCountryInfoAck()
    {
        header.dwType = MSG_QUERYCOUNTRYINFOACK;
        header.stLength = sizeof( MsgQueryCountryInfoAck );
    }

    struct QuestStatus
    {
        QuestStatus() : uchCount( 0 ), nLeftTime( 0 ) {}

        uint8 uchCount;     // ���񿪷Ŵ��� ( 0 δ����,  1 = ���� )
        uint32 nLeftTime;   // ʣ�����ʱ��(  ��λ: �� 0 = �ѿ���, �Ѿ����� , ���� ������ )
    };

    char szName[ CountryDefine::MaxCountryLength ];         // ����
    char szNotice[ CountryDefine::MaxNoticeLength ];        //  ����
    char szOfficial[ CountryDefine::Position_Max ][ CountryDefine::MaxNameLength ];   // ��Ա����
    uint32 nMoney;          // �����ʽ� ( ��ҵ��ѯ������Դʱ��, ���ٷ� )
	uint32 nTribute;
    uint32 nCountryRight;   // ����Ȩ��
	uint32 nStrongth;		//����ʵ��
    QuestStatus xQuestStatus[ CountryDefine::QuestType_Max ];       // 4����������
	
	uint8 szsexID[CountryDefine::Position_Max];
	uint16 szfaceID[CountryDefine::Position_Max];
	uint16 szheaderID[CountryDefine::Position_Max];
	uint16 szprofession[CountryDefine::Position_Max];
};

// ���󷢲���������
struct MsgCountryQuestStatusChangeReq : public MsgCountryModule
{
    MsgCountryQuestStatusChangeReq()
    {
        header.dwType = MSG_COUNTRYQUESTSTATECHANGEREQ;
        header.stLength = sizeof( MsgCountryQuestStatusChangeReq );
    }

    uint8 uchQuestType;
};

// ���������������
struct MsgCountryQuestStatusChangeAck : public MsgCountryModule
{
    MsgCountryQuestStatusChangeAck()
    {
        header.dwType = MSG_COUNTRYQUESTSTATECHANGEACK;
        header.stLength = sizeof( MsgCountryQuestStatusChangeAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,    // �ɹ�( �շ��ɹ�, ��ť��� )
        ECD_NotRight,       // û��Ȩ��
        ECD_Already,        // �Ѿ���������
        ECD_NotEnoughMoney,
    };

    uint8 uchQuestType;
    uint8 uchResult;
};

// �������ҹ�Աְλ
struct MsgCountryOfficialAppointReq : public MsgCountryModule
{
    MsgCountryOfficialAppointReq()
    {
        header.dwType = MSG_COUNTRYOFFICIALAPPOINTREQ;
        header.stLength = sizeof( MsgCountryOfficialAppointReq );
    }

    uint8 uchPosition;      // ����ʲôְλ
    char szName[ CountryDefine::MaxNameLength ];   // ����������
};


// �������ҹ�Ա����
struct MsgCountryOfficialAppointAck : public MsgCountryModule
{
    MsgCountryOfficialAppointAck()
    {
        header.dwType = MSG_COUNTRYOFFICIALAPPOINTACK;
        header.stLength = sizeof( MsgCountryOfficialAppointAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,    // �ɹ�( �շ��ɹ�, ��ť��� )
        ECD_NotRight,       // û��Ȩ��
        ECD_NotCountryMember, // ���Ǳ�����Ա��������
        ECD_NotOnline,      // ������
        ECD_LevelLess,      // �ȼ�����45��
        ECD_Already,        // �Ѿ���ְλ, �����ظ�����
		ECD_NOGuild,        //û�й���
		ECD_NoItem,			//û����Ʒ
    };

    uint8 uchResult;
    uint8 uchPosition;      // ����ʲôְλ
    uint32 nPlayerID;       // �����������ID
};

// ������ҹ�Աְλ
struct MsgCountryOfficialRecallReq : public MsgCountryModule
{
    MsgCountryOfficialRecallReq()
    {
        header.dwType = MSG_COUNTRYOFFICIALRECALLREQ;
        header.stLength = sizeof( MsgCountryOfficialRecallReq );
    }

    uint8 uchPosition;       // ���ʲôְλ
};

struct MsgDelCountryOfficialReq : public MsgCountryModule //�Լ���ȥ��ְ
{
    MsgDelCountryOfficialReq()
    {
        header.dwType = MSG_DELCOUNTRYOFFICIALREQ;
        header.stLength = sizeof( MsgDelCountryOfficialReq );
    }
};


// ������ҹ�Աְλ����
struct MsgCountryOfficialRecallAck : public MsgCountryModule
{
    MsgCountryOfficialRecallAck()
    {
        header.dwType = MSG_COUNTRYOFFICIALRECALLACK;
        header.stLength = sizeof( MsgCountryOfficialRecallAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_NotRight,   // û��Ȩ��
		ECD_DelSuccess,
    };


    uint8 uchResult;
    uint8 uchPosition;       // ���ʲôְλ
};

// ֪ͨ���ҷ�������ʱ����
struct MsgCountryQuestStatusStop : public MsgCountryModule
{
    MsgCountryQuestStatusStop()
    {
        header.dwType = MSG_COUNTRYQUESTSTATUSSTOP;
        header.stLength = sizeof( MsgCountryQuestStatusStop );
    }

    uint8 uchQuestType;    
};

// ɱ�����ҹ�Ա
struct MsgTellCountryKillPosition : public MsgCountryModule
{
    MsgTellCountryKillPosition()
    {
        header.dwType = MSG_TELLCOUNTRYKILLPOSITION;
        header.stLength = sizeof( MsgTellCountryKillPosition );
    }

    uint8 uchKillerCountry;                  // ɱ���߹���  
    char szKillerName[ CountryDefine::MaxNameLength ];   // ɱ��������

    uint8 uchBeKilledCountry;                 // ��ɱ�߹���
    uint8 uchBeKilledPosition;                // ��ɱ�߹���ְλ
    char szBeKilledName[ CountryDefine::MaxNameLength ];  // ��ɱ������
};

// �ͻ�������ļ�������ʽ�
struct MsgCountryRequestRaiseReq : public MsgCountryModule
{
    MsgCountryRequestRaiseReq()
    {
        header.dwType = MSG_COUNTRYREQUESTRAISEREQ;
        header.stLength = sizeof( MsgCountryRequestRaiseReq );
    }
};

// ������������
struct MsgCountryRequestRaiseAck : public MsgCountryModule
{
    MsgCountryRequestRaiseAck()
    {
        header.dwType = MSG_COUNTRYREQUESTRAISEACK;
        header.stLength = sizeof( MsgCountryRequestRaiseAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_NotRight,       // û��Ȩ��
        ECD_TimeLimit,      // һ��ֻ��ļ��һ��
    };

    uint8 uchResult;
};

// ����������ļ����������, �ͻ����жϵȼ�
struct MsgCountryRaiseToPlayerReq : public MsgCountryModule
{
    MsgCountryRaiseToPlayerReq()
    {
        header.dwType = MSG_COUNTRYRAISETOPLAYERREQ;
        header.stLength = sizeof( MsgCountryRaiseToPlayerReq );
    }
};

// ���ļ��
struct MsgCountryRaiseToPlayerAck : public MsgCountryModule
{
    MsgCountryRaiseToPlayerAck()
    {
        header.dwType = MSG_COUNTRYRAISETOPLAYERACK;
        header.stLength = sizeof( MsgCountryRaiseToPlayerAck );
    }

    uint32 nMoney;      // ��Ľ�Ǯ
};

// ļ��
struct MsgCountryRaiseTellPlayer : public MsgCountryModule
{
    MsgCountryRaiseTellPlayer()
    {
        header.dwType = MSG_COUNTRYRAISETELLPLAYER;
        header.stLength = sizeof( MsgCountryRaiseTellPlayer );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_LevelLess,      // �ȼ�����
        ECD_NotEnoughMoney, // ��Ǯ����
        ECD_ErrorRaiseMoney,// ļ����Ǯ�������ֵ
        ECD_NotRaiseTime,   // ����ļ��ʱ�� ����ļ��
        ECD_CountryMoneyMax,// �����ʽ��Ѿ������
    };

    uint8 uchResult;
};

// ļ��ȫ���㲥
struct MsgTellCountryPlayerRaise : public MsgCountryModule
{
    MsgTellCountryPlayerRaise()
    {
        header.dwType = MSG_TELLCOUNTRYPLAYERRAISE;
        header.stLength = sizeof( MsgTellCountryPlayerRaise );

        memset( szName, 0, sizeof( szName ) );
    }

    char szName[ CountryDefine::MaxNameLength ];    // ���
    int nMoney;     // �����˶���Ǯ
};

struct MsgTellCountryPlayerRaiseItem : public MsgCountryModule
{
    MsgTellCountryPlayerRaiseItem()
    {
        header.dwType = MSG_TELLCOUNTRYPLAYERRAISEITEM;
        header.stLength = sizeof( MsgTellCountryPlayerRaiseItem );

        memset( szName, 0, sizeof( szName ) );
    }
    char szName[ CountryDefine::MaxNameLength ];    // ���
    unsigned short CountryID;
};

// ��ȡ�����������
struct MsgCountryReceiveMountAck : public MsgCountryModule
{
    MsgCountryReceiveMountAck()
    {
        header.dwType = MSG_COUNTRYRECEIVEMOUNTACK;
        header.stLength = sizeof( MsgCountryReceiveMountAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_NotRight,      // û��Ȩ�޲�����ȡ
        ECD_Alreadly,      // �Ѿ���ȡ��
        ECD_NotHaveMount,  // û�ж�Ӧ��ȼ�����
        ECD_MaxCount,      // ��Я�������Ѿ������
    };

    uint8 uchResult;
};

// ��¼���ұ���ս��������( �ͻ�Ҳ��¼, ��¼���г�����CountryConfig���� )
struct MsgTellCountryBordersFight : public MsgCountryModule
{
    MsgTellCountryBordersFight()
    {
        header.dwType = MSG_TELLCOUNTRYBORDERSFIGHT;
        header.stLength = sizeof( MsgTellCountryBordersFight );
    }

    uint16 ustMapID;
    uint16 ustPosX;
    uint16 ustPosY;
};

// ֪ͨ�ͻ��� ĳĳĳ���������
struct MsgTellCountryKillEnemy : public MsgCountryModule
{
    MsgTellCountryKillEnemy()
    {
        header.dwType = MSG_TELLCOUNTRYKILLENEMY;
        header.stLength = sizeof( MsgTellCountryKillEnemy );
    }
    
    uint16 ustMapID;
    char szPlayerName[ CountryDefine::MaxNameLength ];
};

// ���Ҳ� �����������
struct MsgCountryFlyToBordersReq : public MsgCountryModule
{
    MsgCountryFlyToBordersReq()
    {
        header.dwType = MSG_COUNTRYFLYTOBORDERSREQ;
        header.stLength = sizeof( MsgCountryFlyToBordersReq );
    }
    
    uint16 ustMapID;
    uint16 ustPosX;
    uint16 ustPosY;
};

// �ͻ����������
struct MsgCountryOperateToPlayerReq : public MsgCountryModule
{
    MsgCountryOperateToPlayerReq()
    {
        header.dwType = MSG_COUNTRYOPERATETOPLAYERREQ;
        header.stLength = sizeof( MsgCountryOperateToPlayerReq );
        memset( szName, 0, sizeof( szName ) );
    }
    
    enum EConstDefine
    {
        Operate_BanSpeak = 0,        // ����
        Operate_Chain,               // ����
        Operate_Remit,               // ����
    };

    uint8 uchOperate;
    char szName[ CountryDefine::MaxNameLength ];
};

// �ͻ��˲�������
struct MsgCountryOperateToPlayerAck : public MsgCountryModule
{
    MsgCountryOperateToPlayerAck()
    {
        header.dwType = MSG_COUNTRYOPERATETOPLAYERACK;
        header.stLength = sizeof( MsgCountryOperateToPlayerAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_NotRight,           // û��Ȩ��
        ECD_TimeLimit,          // һ��ֻ��3��
        ECD_NotEnoughMoney,     // û���㹻�Ľ�Ǯ
        ECD_NotOnLine,          // ������
        ECD_NotSameCountry,     // ���Ǳ�������
        ECD_NeedNotRemit,       // ����Ҫ����
        ECD_CountryBattle,      // ����, ����, ��ȸ����ս�ڼ䲻��ʹ��
    };

    uint8 uchOperate;
    uint8 uchResult;
};

// ֪ͨ�������� �㱻������
struct MsgCountryTellOperateToPlayer : public MsgCountryModule
{
    MsgCountryTellOperateToPlayer()
    {
        header.dwType = MSG_COUNTRYTELLOPERATETOPLAYER;
        header.stLength = sizeof( MsgCountryTellOperateToPlayer );
    }

    uint8 uchOperate;
};

// ֪ͨȫ��ĳ�˱�������( ��һ��ϵͳ���� )
struct MsgTellOperateToCountry : public MsgCountryModule
{
    MsgTellOperateToCountry()
    {
        header.dwType = MSG_TELLOPERATETOCOUNTRY;
        header.stLength = sizeof( MsgTellOperateToCountry );
    }

    char szName[ CountryDefine::MaxNameLength ];    // 
    uint8 uchOperate;
};

// ��������ټ����
struct MsgCountryConveneResult : public MsgCountryModule
{
    MsgCountryConveneResult()
    {
        header.dwType = MSG_COUNTRYCONVENERESULT;
        header.stLength = sizeof( MsgCountryConveneResult );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_NotRight,           // û��Ȩ��
        ECD_TimeLimit,          // һ��ֻ��3��
        ECD_NotEnoughMoney,     // û���㹻�Ľ�Ǯ
        ECD_EctypeMap,          // �������ܹ����ټ�
    };

    uint8 uchResult;
};

// ���������ͻ����ټ�����
struct MsgCountryConveneReq : public MsgCountryModule
{
    MsgCountryConveneReq()
    {
        header.dwType = MSG_COUNTRYCONVENEREQ;
        header.stLength = sizeof( MsgCountryConveneReq );
    }

    uint32 nOfficialID;  // �ټ���, ( ������Լ� �Ͳ�Ҫ������ )
};

// �Ƿ�ͬ���ټ� ( ��ͬ�ⲻ�û���Ϣ )
struct MsgCountryConveneAck : public MsgCountryModule
{
    MsgCountryConveneAck()
    {
        header.dwType = MSG_COUNTRYCONVENEACK;
        header.stLength = sizeof( MsgCountryConveneAck );
    }
};

struct MsgCountryTellAppoint : public MsgCountryModule
{
    MsgCountryTellAppoint()
    {
        header.dwType = MSG_COUNTRYCOUNTRYAPPOINT;
        header.stLength = sizeof( MsgCountryTellAppoint );
    }

    enum EConstDefine
    {
        ECD_Appoint = 0, // ������
        ECD_Recall,      // ����ְ
    };

    uint8 uchType;       // ������ ���߱���ְ
    uint8 uchPosition;   // ְλ
};

// ֪ͨ����ID
struct MsgCountryTellCountryID : public MsgCountryModule
{
    MsgCountryTellCountryID()
    {
        header.dwType = MSG_COUNTRYTELLCOUNTRYID;
        header.stLength = sizeof( MsgCountryTellCountryID );
    }
    /*uint8 stID;*/
    uint8 uchCountry;
};

// ����ı����
struct MsgCountryChangeReq : public MsgCountryModule
{
    MsgCountryChangeReq()
    {
        header.dwType = MSG_COUNTRYCHANGEREQ;
        header.stLength = sizeof( MsgCountryChangeReq );
    }

    uint8 uchCountryID;
};

// �������Ҹı�
struct MsgCountryChangeAck : public MsgCountryModule
{
    MsgCountryChangeAck()
    {
        header.dwType = MSG_COUNTRYCHANGEACK;
        header.stLength = sizeof( MsgCountryChangeAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_HaveTeam,       // �ѹ������ж���
        ECD_HaveGuild,      // �ѹ������а���
        ECD_SameCountry,    // ��ͬ����
        ECD_ErrorCountry,   // ����Ĺ���ID
        ECD_NotEnoughMoney, // û���㹻�Ľ�Ǯ
        ECD_HaveMarriage,   // �з��޹�ϵ���ܸı����
        ECD_HaveStudent,    // ��ͽ��
        ECD_HaveTeacher,    // ��ʦ��
        ECD_TimeLimit,      // һ��ֻ�ܸı�һ�ι���
		ECD_Item,			// �ѹ�����Ʒ���㹻
		ECD_HaveOff,		// �й�ְ
		ECD_MaxLevel,		//
		ECD_MinLevel,		//
		ECD_QuestStates		//
    };

    uint8 uchResult;
};

// ֪ͨ������� ��Ĺ����Ѿ����������
struct MsgCountryTellWeak : public MsgCountryModule
{
    MsgCountryTellWeak()
    {
        header.dwType = MSG_COUNTRYTELLWEAK;
        header.stLength = sizeof( MsgCountryTellWeak );
    }

    uint8 uchWeakCountryID;     
};

struct MsgCountryTellStrong : public MsgCountryModule
{
    MsgCountryTellStrong()
    {
        header.dwType = MSG_COUNTRYTELLSTRONG;
        header.stLength = sizeof( MsgCountryTellStrong );
    }

    uint8 uchStrongCountryID;     
};

// ֪ͨ���ɰ���, ��İ����ڹ�������ս�����б��������ɶ�����
struct MsgCountryBattleReplace : public MsgCountryModule
{
    MsgCountryBattleReplace()
    {
        header.dwType = MSG_COUNTRYBATTLEREPLACE;
        header.stLength = sizeof( MsgCountryBattleReplace );
    }
    
    uint8 uchBattleType;
};

// ֪ͨ���ҹ���
struct MsgTellCountryName : public MsgCountryModule
{
    MsgTellCountryName()
    {
        header.dwType = MSG_TELLCOUNTRYNAME;
        header.stLength = sizeof( MsgTellCountryName );

        memset( szName, 0, sizeof( szName ) );
    }

    char szName[ CountryDefine::Country_Max ][ CountryDefine::MaxCountryLength ];      // ��������
};

// �����޸Ĺ�������
struct MsgChangeCountryNameReq : public MsgCountryModule
{
    MsgChangeCountryNameReq()
    {
        header.dwType = MSG_CHANGECOUNTRYNAMEREQ;
        header.stLength = sizeof( MsgChangeCountryNameReq );
    }

    char szName[ CountryDefine::MaxCountryLength ];      // ��������
};

// ��������Ӧ�޸Ĺ�������
struct MsgChangeCountryNameAck : public MsgCountryModule
{
    MsgChangeCountryNameAck()
    {
        header.dwType = MSG_CHANGECOUNTRYNAMEACK;
        header.stLength = sizeof( MsgChangeCountryNameAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_NotHaveRight,  // û��Ȩ��
        ECD_ChangeOnce,    // ֻ���޸�һ������
        ECD_ErrorName,     // ����Ĺ�������
    };

    unsigned char uchResult;
};

// ֪ͨȫ����ĳ���Ĺ������ָı���
struct MsgTellCountryNameChange : public MsgCountryModule
{
    MsgTellCountryNameChange()
    {
        header.dwType = MSG_TELLCOUNTRYNAMECHANGE;
        header.stLength = sizeof( MsgTellCountryNameChange );
    }

    unsigned char uchCountryID; // ����ID
    char szPlayer[ CountryDefine::MaxNameLength ];       // ��������
    char szName[ CountryDefine::MaxCountryLength ];     // ��������
};

// ֪ͨȫ�����ս״̬
struct MsgTellCountryWarStatus : public MsgCountryModule
{
    MsgTellCountryWarStatus()
    {
        header.dwType = MSG_TELLCOUNTRYSTATUS;
        header.stLength = sizeof( MsgTellCountryWarStatus );
    }

    unsigned char uchStatus;
};

// ���¹���ɱ����Ϣ
struct MsgUpdateCountryWarFightKill : public MsgCountryModule
{
    MsgUpdateCountryWarFightKill()
    {
        header.dwType = MSG_UPDATECOUNTRYWARFIGHTKILL;
        header.stLength = sizeof( MsgUpdateCountryWarFightKill );
    }

    uint32 nKillCount[ CountryDefine::Country_Max ];    // 3�����ҵ�ɱ�����
};

/////////////////////////////////////////////////////////////////////////////////
// ��������ͨ��
////////////////////////////////////////////////////////////////////////////////
struct GS2CSCountryNoticeChangeReq : public MsgCountryModule
{
    GS2CSCountryNoticeChangeReq()
    {
        header.dwType = GS2CS_COUNTRYNOTICECHANGEREQ;
        header.stLength = sizeof( GS2CSCountryNoticeChangeReq );
    }

    uint8 uchCountryID;
    uint32 nPlayerID;
    char szNotice[ CountryDefine::MaxNoticeLength ];
};

struct CS2GSCountryNoticeChangeAck : public MsgCountryModule
{
    CS2GSCountryNoticeChangeAck()
    {
        header.dwType = CS2GS_COUNTRYNOTICECHANGEACK;
        header.stLength = sizeof( CS2GSCountryNoticeChangeAck );
    }

    uint8 uchCountryID;
    uint32 nPlayerID;
    char szNotice[ CountryDefine::MaxNoticeLength ];
};

struct CS2GSAddCountryInfoAck : public MsgCountryModule
{
    CS2GSAddCountryInfoAck()
    {
        header.dwType = CS2GS_ADDCOUNTRYINFOACK;
        header.stLength = sizeof( CS2GSAddCountryInfoAck );
    }
	uint8 uchCountryID;
    char szNotice[ CountryDefine::MaxCountryInfoLength ];
	__int64 Time;
	int Value;
};

struct CS2GSRequestCountryInfoAck : public MsgCountryModule
{
	CS2GSRequestCountryInfoAck()
    {
        header.dwType = CS2GS_REQUESTCOUNTRYINFOACK;
        header.stLength = sizeof( CS2GSRequestCountryInfoAck );
		memset( Info, 0, sizeof( Info ) );
		memset( Time, 0, sizeof( Time ) );
		memset( CountryID, 0, sizeof( CountryID ) );
		memset( values, 0, sizeof( values ) );
		Sum = 0;
		IsEnd = false;
    }
	int Sum;
	char Info[CountryDefine::MaxMsgCountryInfoSum][CountryDefine::MaxCountryInfoLength];
	uint8 CountryID[CountryDefine::MaxMsgCountryInfoSum];
	__int64 Time[CountryDefine::MaxMsgCountryInfoSum];
	int values[CountryDefine::MaxMsgCountryInfoSum];
	bool IsEnd;
};


struct GS2CSAddCountryInfoReq : public MsgCountryModule
{
    GS2CSAddCountryInfoReq()
    {
        header.dwType = GS2CS_ADDCOUNTRYINFOREQ;
        header.stLength = sizeof( GS2CSAddCountryInfoReq );
    }
	uint8 uchCountryID;
    char szNotice[ CountryDefine::MaxCountryInfoLength ];
	int Value;
	__int64 Time;
};

struct GS2CSCountryQuestStatusChangeReq : public MsgCountryModule
{
    GS2CSCountryQuestStatusChangeReq()
    {
        header.dwType = GS2CS_COUNTRYQUESTSTATUSCHANGEREQ;
        header.stLength = sizeof( GS2CSCountryQuestStatusChangeReq );
    }

    uint8 uchCountryID;
    uint8 uchQuestType;
    uint32 nPlayerID;
};

struct CS2GSCountryQuestStatusChangeAck : public MsgCountryModule
{
    CS2GSCountryQuestStatusChangeAck()
    {
        header.dwType = CS2GS_COUNTRYQUESTSTATUSCHANGEACK;
        header.stLength = sizeof( CS2GSCountryQuestStatusChangeAck );
    }

    uint8 uchCountryID;
    uint8 uchQuestType;
    uint32 nPlayerID;
};

struct GS2CSCountryOfficialAppointReq : public MsgCountryModule
{
    GS2CSCountryOfficialAppointReq()
    {
        header.dwType = GS2CS_COUNTRYOFFICIALAPPOINTREQ;
        header.stLength = sizeof( GS2CSCountryOfficialAppointReq );

		sexID = -1;
		faceID = -1;
		headerID = -1;
		professionID = -1;
    }

    uint8 uchCountryID;
    uint32 nOfficialID;     // ������ID

    uint8 uchPosition;      // ������ְλ
    uint32 nPlayerID;       // ��������ID

	uint8	sexID;
	uint16  faceID;
	uint16  headerID;
	uint16  professionID;
};

struct GS2CSCountryOfficialRecallReq : public MsgCountryModule
{
    GS2CSCountryOfficialRecallReq()
    {
        header.dwType = GS2CS_COUNTRYOFFICIALRECALLREQ;
        header.stLength = sizeof( GS2CSCountryOfficialRecallReq );
    }

    uint8 uchCountryID;
    uint32 nOfficialID;     
    uint8 uchPosition;      // �����ְλ
};

struct GS2CSDelCountryOfficialReq : public MsgCountryModule
{
    GS2CSDelCountryOfficialReq()
    {
        header.dwType = GS2CS_DELCOUNTRYOFFICIALREQ;
        header.stLength = sizeof( GS2CSDelCountryOfficialReq );
    }
    uint8 uchCountryID; 
    uint8 uchPosition;      // �����ְλ
};

struct CS2GSCountryDateChangeed : public MsgCountryModule
{
    CS2GSCountryDateChangeed()
    {
        header.dwType = CS2GS_COUNTRYDATECHANGEED;
        header.stLength = sizeof( CS2GSCountryDateChangeed );
    }
    uint8 uchCountryID;
};

struct CS2GSCountryQuestStatusStop : public MsgCountryModule
{
    CS2GSCountryQuestStatusStop()
    {
        header.dwType = CS2GS_COUNTRYQUESTSTATUSSTOP;
        header.stLength = sizeof( CS2GSCountryQuestStatusStop );
    }
    
    uint8 uchCountryID;
    uint8 uchQuestType;
};


//ZHUXINCONG
struct GS2CSCountryBattleReward:public MsgCountryModule
{
	GS2CSCountryBattleReward()
	{
		header.dwType = CS2CS_GS2CSCountryBattleReward;
		header.stLength = sizeof(GS2CSCountryBattleReward);
		oldID = 0;
		newID = 0;
		nCampBattle = 0;
	}
	int nLevel;
	int nPlayerID;
	SCharItem CItem;
	int nPosition;
    int nGuidID;
	int oldID;
	int newID;
	int nCampBattle;
	char szName[ CountryDefine::MaxNameLength ];
};

struct GS2CSCountryBattleResult : public MsgCountryModule
{
    GS2CSCountryBattleResult()
    {
        header.dwType = GS2CS_COUNTRYBATTLERESULT;
        header.stLength = sizeof( GS2CSCountryBattleResult );
    }

    uint8 uchCountryID;

    uint8 uchBattleType;
    uint8 uchWinType;
    uint32 nGuildID;
	uint32 nLoseGuildID;
	uint32 nCampBattle;
};

struct GS2CSAddCountryOfficial : public MsgCountryModule
{
    GS2CSAddCountryOfficial()
    {
        header.dwType = GS2CS_ADDCOUNTRYOFFICIAL;
        header.stLength = sizeof( GS2CSAddCountryOfficial );

		sexID = -1;
		faceID = -1;
		headerID = -1;
		professionID = -1;
    }

    uint8 uchCountryID;
	uint8 sexID;
	uint16 faceID;
	uint16 headerID;
	uint32 nPlayerID;
	uint8  position;
	uint16 professionID;
	char szName[ CountryDefine::MaxNameLength ];
};

struct CS2GSCountryBattleResult : public MsgCountryModule
{
    CS2GSCountryBattleResult()
    {
        header.dwType = CS2GS_COUNTRYBATTLERESULT;
        header.stLength = sizeof( CS2GSCountryBattleResult );
    }

    uint8 uchCountryID;

    uint8 uchBattleType;
    uint8 uchWinType;
    uint32 nGuildID;
	uint32 nLoseGuildID;
	uint32 nCampBattle;
};

struct GS2CSCountryRequestRaiseReq : public MsgCountryModule
{
    GS2CSCountryRequestRaiseReq()
    {
        header.dwType = GS2CS_COUNTRYREQUESTRAISEREQ;
        header.stLength = sizeof( GS2CSCountryRequestRaiseReq );
    }
    
    uint8 uchCountryID;
    uint32 nPlayerID;
};

struct CS2GSCountryRequestRaiseAck : public MsgCountryModule
{
    CS2GSCountryRequestRaiseAck()
    {
        header.dwType = CS2GS_COUNTRYREQUESTRAISEACK;
        header.stLength = sizeof( CS2GSCountryRequestRaiseAck );
    }

    uint8 uchCountryID;
    uint32 nPlayerID;
};

struct GS2CSCountryMoneyRaiseed : public MsgCountryModule
{
    GS2CSCountryMoneyRaiseed()
    {
        header.dwType = GS2CS_COUNTRYMONEYRAISEED;
        header.stLength = sizeof( GS2CSCountryMoneyRaiseed );

		OperateType = 1;
    }
	int nType;// Ĭ��Ϊ0 Ϊ��Ǯ 1Ϊ��Ʒ
    uint8 uchCountryID;
    int nMoney;
	int OperateType; // 1+,2-,3set,ֻ��ntype=1������set�������Ĳ���ȫ��Ϊ��
};

struct GS2CSRaiseCountryPlayerItem : public MsgCountryModule
{
    GS2CSRaiseCountryPlayerItem()
    {
        header.dwType = GS2CS_RAISECOUNTRYPLAYERITEM;
        header.stLength = sizeof( GS2CSRaiseCountryPlayerItem );

		
    }
	uint32 ItemID;
	uint32 PlayerID;
	SCharItem CItem;
	char szName[dr_MaxPlayerName];
};

struct GS2CSCountryBordersFight : public MsgCountryModule
{
    GS2CSCountryBordersFight()
    {
        header.dwType = GS2CS_COUNTRYBORDERSFIHGT;
        header.stLength = sizeof( GS2CSCountryBordersFight );
    }

    unsigned uchCountryID;

    uint16 ustMapID;
    int nPosX;
    int nPosY;
};

struct CS2GSCountryBordersFight : public MsgCountryModule
{
    CS2GSCountryBordersFight()
    {
        header.dwType = CS2GS_COUNTRYBORDERSFIHGT;
        header.stLength = sizeof( CS2GSCountryBordersFight );
    }

    unsigned uchCountryID;

    uint16 ustMapID;
    int nPosX;
    int nPosY;
};

struct GS2CSCountryOperateToPlayerReq : public MsgCountryModule
{
    GS2CSCountryOperateToPlayerReq()
    {
        header.dwType = GS2CS_COUNTRYOPERATETOPLAYERREQ;
        header.stLength = sizeof( GS2CSCountryOperateToPlayerReq );
    }

    uint8 uchCountryID;
    uint8 uchOperate;
    uint32 nPlayerID;
    char szName[ CountryDefine::MaxNameLength ];
};

struct CS2GSCountryOperateToPlayerReq : public MsgCountryModule
{
    CS2GSCountryOperateToPlayerReq()
    {
        header.dwType = CS2GS_COUNTRYOPERATETOPLAYERREQ;
        header.stLength = sizeof( CS2GSCountryOperateToPlayerReq );
    }

    uint8 uchCountryID;
    uint8 uchOperate;
    uint32 nOfficialID;
    uint32 nPlayerID;
};

struct GS2CSCountryOperateToPlayerAck : public MsgCountryModule
{
    GS2CSCountryOperateToPlayerAck()
    {
        header.dwType = GS2CS_COUNTRYOPERATETOPLAYERACK;
        header.stLength = sizeof( GS2CSCountryOperateToPlayerAck );
    }

    uint8 uchCountryID;
    uint8 uchOperate;
    uint32 nOfficialID;
};

struct CS2GSCountryOperateToPlayerAck : public MsgCountryModule
{
    CS2GSCountryOperateToPlayerAck()
    {
        header.dwType = CS2GS_COUNTRYOPERATETOPLAYERACK;
        header.stLength = sizeof( CS2GSCountryOperateToPlayerAck );
    }

    uint8 uchCountryID;
    uint8 uchOperate;
    uint32 nOfficialID;
};

struct GS2CSCountryConveneReq : public MsgCountryModule
{
    GS2CSCountryConveneReq()
    {
        header.dwType = GS2CS_COUNTRYCONVENEREQ;
        header.stLength = sizeof( GS2CSCountryConveneReq );
    }

    uint8 uchCountryID;
    uint32 nOfficialID;
    uint16 ustLevel;     // ��ͼ�ĵȼ�

    uint32 nMapID;
    float fX;
    float fY;
};

struct CS2GSCountryConveneReq : public MsgCountryModule
{
    CS2GSCountryConveneReq()
    {
        header.dwType = CS2GS_COUNTRYCONVENEREQ;
        header.stLength = sizeof( CS2GSCountryConveneReq );
    }

    uint8 uchCountryID;
    uint32 nOfficialID;
    uint16 ustLevel;     // ��ͼ�ĵȼ�

    uint32 nMapID;
    float fX;
    float fY;
};

struct GS2CSCountrySetOfficial : public MsgCountryModule
{
    GS2CSCountrySetOfficial()
    {
        header.dwType = GS2CS_COUNTRYSETOFFICIAL;
        header.stLength = sizeof( GS2CSCountrySetOfficial );

		sexID = -1;
		faceID = -1;
		headerID = -1;
		professionID = -1;
    }

    uint8 uchCountryID;
    uint8 uchPosition;

    uint32 nGuildID;
    uint32 nPlayerID;
	
	uint16 faceID;
	uint16 headerID;
	uint8  sexID;
	uint16 professionID;

    char szName[ CountryDefine::MaxNameLength ];
};

struct CS2GSCountrySetOfficial : public MsgCountryModule
{
    CS2GSCountrySetOfficial()
    {
        header.dwType = CS2GS_COUNTRYSETOFFICIAL;
        header.stLength = sizeof( CS2GSCountrySetOfficial );

		sexID = -1;
		faceID = -1;
		headerID = -1;
		professionID = -1;
    }

    uint8 uchCountryID;
    uint8 uchPosition;
    uint32 nGuildID;
    uint32 nPlayerID;

	uint16 faceID;
	uint16 headerID;
	uint8  sexID;
	uint16 professionID;

    char szName[ CountryDefine::MaxNameLength ];
};


struct CS2GSCountryDataUpdate : public MsgCountryModule
{
    CS2GSCountryDataUpdate()
    {
        header.dwType = CS2GS_COUNTRYDATAUPDATE;
        header.stLength = sizeof( CS2GSCountryDataUpdate );
    }

    uint8 uchCountryID;

    uint8 uchUpdateType;
    __int64 n64Value;
};

struct GS2CSCountryChangeResult : public MsgCountryModule
{
    GS2CSCountryChangeResult()
    {
        header.dwType = GS2CS_COUNTRYCHANGERESULT;
        header.stLength = sizeof( GS2CSCountryChangeResult );
    }

    unsigned int nPlayerID;
    uint8 uchCountryID;
};

struct CS2GSCountryOfficialChange : public MsgCountryModule
{
    CS2GSCountryOfficialChange()
    {
        header.dwType = CS2GS_COUNTRYOFFICIALCHANGE;
        header.stLength = sizeof( CS2GSCountryOfficialChange );

        nPlayerID = 0;
        memset( szName, 0, sizeof( szName ) );

		sexID = -1;
		faceID = -1;
		headerID = -1;
		professionID = -1;
    }

    uint8 uchCountryID;
    uint8 uchPosition;      // ְλ

	uint8 sexID;
	uint16 faceID;
	uint16 headerID;
	uint16 professionID;

    unsigned int nPlayerID;
    char szName[ CountryDefine::MaxNameLength ];
};

struct CS2GSCountryOfficialReward : public MsgCountryModule
{
	CS2GSCountryOfficialReward()
    {
        header.dwType = CS2GS_COUNTRYOFFICIALREWARD;
        header.stLength = sizeof( CS2GSCountryOfficialReward );

        nPlayerID = 0;
        uchPosition = 0;
    }
    uint8 uchPosition;      // ְλ
    unsigned int nPlayerID;
	char szName[ CountryDefine::MaxNameLength ];
};	

struct CS2GSAddCountryOfficial : public MsgCountryModule
{
    CS2GSAddCountryOfficial()
    {
        header.dwType = CS2GS_ADDCOUNTRYOFFICIAL;
        header.stLength = sizeof( CS2GSAddCountryOfficial );

        nPlayerID = 0;
    }

    uint8 uchCountryID;
    uint8 uchPosition;      // ְλ
    unsigned int nPlayerID;
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//���ݿ��ȡ����
struct CS2DBRequestCountryDataReq : public MsgCountryModule
{
    CS2DBRequestCountryDataReq()
    {
        header.dwType = CS2DB_REQUESTCOUNTRYDATAREQ;
        header.stLength = sizeof( CS2DBRequestCountryDataReq );
    }
};

struct CS2DBRequestCountryInfoReq : public MsgCountryModule
{
    CS2DBRequestCountryInfoReq()
    {
        header.dwType = CS2DB_REQUESTCOUNTRYINFOREQ;
        header.stLength = sizeof( CS2DBRequestCountryInfoReq );
    }
	char Info[CountryDefine::MaxCountryInfoLength];
	uint8 CountryID;
	int Value;
	__int64 Time;
};

struct DB2CSRequestCountryDataAck : public MsgCountryModule
{
    DB2CSRequestCountryDataAck()
    {
        header.dwType = DB2CS_REQUESTCOUNTRYDATAACK;
        header.stLength = sizeof( DB2CSRequestCountryDataAck );
		memset( PlayerSum, 0, sizeof( PlayerSum ) );
    }
	unsigned int PlayerSum[CountryDefine::Country_Max];//���й��ҵ�����
    CountryData xData[ CountryDefine::Country_Max ];
};

struct DB2CSRequestCountryInfoAck : public MsgCountryModule
{
	DB2CSRequestCountryInfoAck()
    {
        header.dwType = DB2CS_REQUESTCOUNTRYINFOACK;
        header.stLength = sizeof( DB2CSRequestCountryInfoAck );
		memset( Info, 0, sizeof( Info ) );
		memset( Time, 0, sizeof( Time ) );
		memset( CountryID, 0, sizeof( CountryID ) );
		memset( values, 0, sizeof( values ) );
		Sum = 0;
		IsEnd = false;
    }
	int Sum;
	char Info[CountryDefine::MaxMsgCountryInfoSum][CountryDefine::MaxCountryInfoLength];
	uint8 CountryID[CountryDefine::MaxMsgCountryInfoSum];
	int values[CountryDefine::MaxMsgCountryInfoSum];
	__int64 Time[CountryDefine::MaxMsgCountryInfoSum];
	bool IsEnd;
};

struct DB2CSRequestCountryOfficeAck : public MsgCountryModule
{
    DB2CSRequestCountryOfficeAck()
    {
        header.dwType = DB2CS_REQUESTCOUNTRYOFFICECK;
        header.stLength = sizeof( DB2CSRequestCountryOfficeAck );

		sexID = -1;
		faceID = -1;
		headerID = -1;
		professionID = -1;
    }
	uint32 nPlayerID;
	uint8 countryID;
	uint8 uchPosition;
	uint8 sexID;
	uint16 faceID;
	uint16 headerID;
	uint16 professionID;
	char szName[ CountryDefine::MaxNameLength ];
};

struct CS2DBCountryDataSaveReq : public MsgCountryModule
{
    CS2DBCountryDataSaveReq()
    {
        header.dwType = CS2DB_COUNTRYDATESAVEREQ;
        header.stLength = sizeof( CS2DBCountryDataSaveReq );
    }

    CountryData xData;
};

struct CS2DBCountryOfficeReq : public MsgCountryModule
{
    CS2DBCountryOfficeReq()
    {
        header.dwType = CS2DB_COUNTRYOFFICEREQ;
        header.stLength = sizeof( CS2DBCountryOfficeReq );
    }
	uint32	nPlayerID;
	uint8 countryID;
	uint8 uchPosition;
	char szName[ CountryDefine::MaxNameLength ];
};

struct CS2GSCountryDataList : public MsgCountryModule
{
    CS2GSCountryDataList()
    {
        header.dwType = CS2GS_COUNTRYDATALIST;
        header.stLength = sizeof( CS2GSCountryDataList );
    }

    unsigned char uchWeakCountryID;
	unsigned char uchStrongCountryID;
    CountryData xData[ CountryDefine::Country_Max ];
};

struct CS2GSCountryWeakStrongthChange : public MsgCountryModule
{
    CS2GSCountryWeakStrongthChange()
    {
        header.dwType = CS2GS_COUNTRYWEAKSTRONGTH;
        header.stLength = sizeof( CS2GSCountryWeakStrongthChange );
    }

    unsigned char uchWeakCountryID;
	unsigned char uchStrongCountryID;
};

struct GS2CSCountryDateChangeReq : public MsgCountryModule
{
    GS2CSCountryDateChangeReq()
    {
        header.dwType = GS2CS_COUNTRYDATACHANGEREQ;
        header.stLength = sizeof( GS2CSCountryDateChangeReq );
    }

    unsigned char uchCountryID;
    unsigned char uchChangeType;
    unsigned char uchOperateType;
    unsigned int nValue;
};

struct CS2GSTellWeakCountry : public MsgCountryModule
{
    CS2GSTellWeakCountry()
    {
        header.dwType = CS2GS_TELLWEAKCOUNTRY;
        header.stLength = sizeof( CS2GSTellWeakCountry );
    }

    unsigned char uchCountryID;
};

struct CS2GSTellStrongCountry : public MsgCountryModule
{
    CS2GSTellStrongCountry()
    {
        header.dwType = CS2GS_TELLSTRONGCOUNTRY;
        header.stLength = sizeof( CS2GSTellStrongCountry );
    }

    unsigned char uchCountryID;
};


struct GS2CSChangeCountryNameReq : public MsgCountryModule
{
    GS2CSChangeCountryNameReq()
    {
        header.dwType = GS2CS_CHANGECOUNTRYNAMEREQ;
        header.stLength = sizeof( GS2CSChangeCountryNameReq );
    }

    unsigned char uchCountryID;
    unsigned int nPlayerID;
    char szPlayer[ CountryDefine::MaxNameLength ];
    char szName[ CountryDefine::MaxCountryLength ];
};

struct CS2GSCountryNameChange : public MsgCountryModule
{
    CS2GSCountryNameChange()
    {
        header.dwType = CS2GS_COUNTRYNAMECHANGE;
        header.stLength = sizeof( CS2GSCountryNameChange );
    }

    unsigned char uchCountryID;
    unsigned int nPlayerID;
    char szPlayer[ CountryDefine::MaxNameLength ];
    char szName[ CountryDefine::MaxCountryLength ];
};

struct CS2GSCountryWarStatus : public MsgCountryModule
{
    CS2GSCountryWarStatus()
    {
        header.dwType = CS2GS_COUNTRYWARSTATUS;
        header.stLength = sizeof( CS2GSCountryWarStatus );
    }
    
    unsigned char uchStatus;
};

struct GS2CSCountryWarKillPlayer : public MsgCountryModule
{
    GS2CSCountryWarKillPlayer()
    {
        header.dwType = GS2CS_COUNTRYWARKILLPLAYER;
        header.stLength = sizeof( GS2CSCountryWarKillPlayer );
    }

    unsigned char uchKillCountryID;
    unsigned char uchDeathCountryID;
};

struct CS2GSCountryWarKillPlayer : public MsgCountryModule
{
    CS2GSCountryWarKillPlayer()
    {
        header.dwType = CS2GS_COUNTRYWARKILLPLAYER;
        header.stLength = sizeof( CS2GSCountryWarKillPlayer );
    }

    unsigned char uchKillCountryID;
    unsigned int nKillCount;
    unsigned char uchDeathCountryID;
    unsigned int nDeathCount;
};

struct GS2CSCountryWarStatusChange : public MsgCountryModule
{
    GS2CSCountryWarStatusChange()
    {
        header.dwType = GS2CS_COUNTRYWARSTATUSCHANGE;
        header.stLength = sizeof( GS2CSCountryWarStatusChange );
    }
    
    unsigned char uchStatus;
};


struct GS2CSCountryPlayerChange : public MsgCountryModule
{
    GS2CSCountryPlayerChange()
    {
        header.dwType = GS2CS_COUNTRYPLAYERCHANGE;
        header.stLength = sizeof( GS2CSCountryPlayerChange );
    }

    unsigned int nPlayerID;
    uint8 nowCountryID;
	uint8 oldCountryID;
};	

struct MsgCountryBuffChange : public MsgCountryModule
{
    MsgCountryBuffChange()
    {
        header.dwType = MSG_COUNTRYBUFFCHANGE;
        header.stLength = sizeof( MsgCountryBuffChange );
    }
};

struct MsgCountryBuffChangeAck : public MsgCountryModule
{
    MsgCountryBuffChangeAck()
    {
        header.dwType = MSG_COUNTRYBUFFCHANGEACK;
        header.stLength = sizeof( MsgCountryBuffChangeAck );
    }
};

#pragma pack( pop )

#endif