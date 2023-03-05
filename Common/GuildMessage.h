#ifndef __GUILDMESSAGEDEFINE_H__
#define __GUILDMESSAGEDEFINE_H__

/************************************************************************
            ������Ϣ����
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "MsgBase.h"
#include "GlobalDef.h"
#include "MessageRangeDefine.h"
#include "GuildDefine.h"

#pragma pack( push, 1 )

enum GuildMessageDefine
{
    MSG_CREATEGUILDREQ = GAMEWORD_GUILDMSG_BEGIN,       // ���󴴽�����
    MSG_CREATEGUILDACK,
    MSG_TELLCREATEGUILD,
    MSG_TELLJOINGUILDTOVIEW,
    MSG_TELLJOINGUILDTOGUILD,
    MSG_TELLLEAVEGUILDTOVIEW,
    MSG_TELLLEAVEGUILDTOGUILD,
    MSG_TELLGUILDDATA,
    MSG_TELLGUILDLIST,
    MSG_LEAVEGUILDREQ,
    MSG_LEAVEGUILDACK,
    MSG_KICKGUILDREQ,
    MSG_KICKGUILDACK,
    MSG_INVITEUILDREQ,
    MSG_INVITEGUILDACK,
    MSG_INVITEJOINGUILDREQ,
    MSG_INVITEJOINGUILDACK,
    MSG_JOINGUILDREQ,
    MSG_JOINGUILDACK,
    MSG_REQUESTJOINGUILDREQ,
	MSG_GUILDADDSQREQ,
	MSG_GUILDDELSQREQ,
    MSG_REQUESTJOINGUILDACK,
    MSG_QUERYGUILDATAREQ,
    MSG_QUERYGUILDATAACK,
    MSG_TELLDISBANDGUILD,
    MSG_MEMBERDATAUPDATE,
    MSG_GUILDDATAUPDATE,
	MSG_GUILDCLIENUPDATE,
    MSG_GUILDNOTICECHANGEREQ,
    MSG_TELLGUILDNOTICE,
    MSG_GUILDRESIGNPOSITIONREQ,
    MSG_GUILDASSIGNPOSITIONREQ,
    MSG_GUILDASSIGNPOSITIONACK,
    MSG_GUILDTRANSFERPOSITIONREQ,
    MSG_GUILDCREATEFAMILYREQ,
    MSG_GUILDCREATEFAMILYACK,
    MSG_TELLGUILDFAMILYCHANGE,
    MSG_GUILDFAMILYCHANGEREQ,
    MSG_GUILDFAMILYCHANGEACK,
    MSG_GUILDMEMBERFAMILYCHANGEREQ,
    MSG_GUILDMEMBERFAMILYCHANGEACK,
    MSG_GUILDLEVELUPACK,
    MSG_GUILDOFFERBUILDACK,
    MSG_GUILDDELATEREQUESTACK,
    MSG_GUILDDELATEAGREEREQ,
    MSG_GUILDDELATEAGREEACK,
    MSG_GUILDDELATERESULT,
    MSG_GUILDDONATEREQ,
    MSG_GUILDDONATEACK,
    MSG_GUILDRELEASEACK,
    MSG_GUILDQUESTRELEASESTATUS,
    MSG_GUILDCLEARMEMBERACTIVITY,
    MSG_TELLGUILDDISBANDTIME,
    MSG_GUILDSHOPLEVELUPREQ,
    MSG_GUILDSHOPLEVELUPACK,
    MSG_GUILDBUYITEMREQ,
    MSG_GUILDBUYITEMACK,
    MSG_GUILDCONVENTREQ,
    MSG_GUILDCONVENTACK,
	MSG_CHANGEGUILDAIM,
	MSG_CHANGEGUILDAIMACK,
	MSG_TELLGUILDAIM,
	MSG_GUILDNOTICEACK,
	MSG_GUILDTRANSFERACK,

    // ����������Ϣ����
    CS2DB_GUILDDATALOADREQ = CENTERGAME_GUILD_BEGIN,
    DB2CS_GUILDDATALIST,
    DB2CS_GUILDMEMBERLIST,
    CS2GS_GUILDDATALIST,
    CS2GS_GUILDDATASENDSUCCESS,
    CS2DB_GUILDDATAUPDATEREQ,
    CS2DB_GUILDMEMBERUPDATEREQ,
    CS2DB_GUILDDISBANDREQ,
    CS2DB_GUILDMEMBERLEAVEREQ,


    GS2CS_CREATEGUILDREQ,
    CS2GS_CREATEGUILDACK,
    GS2CS_LEAVEGUILDREQ,
    CS2GS_LEAVEGUILDACK,
    GS2CS_KICKGUILDREQ,
    GS2CS_INVITEGUILDREQ,
    GS2CS_INVITEJOINGUILDACK,
    CS2GS_JOINGUILDACK,
    GS2CS_JOINGUILDREQ,
    GS2CS_REQUESTJOINGUILDACK,
    GS2CS_DISBANDGUILDACK,
    CS2GS_MEMBERDATAUPDATE,
    CS2GS_GUILDDATAUPDATE,
    GS2CS_GUILDNOTICECHANGEREQ,
    CS2GS_GUILDNOTICECHANGEACK,
    GS2CS_GUILDRESIGNPOSITIONREQ,
    GS2CS_GUILDTRANSFERPOSITIONREQ,
    GS2CS_GUILDCREATEFAMILYREQ,
    GS2CS_GUILDFAMILYCHANGEREQ,
    CS2GS_GUILDFAMILYCHANGE,
    GS2CS_GUILDMEMBERFAMILYCHANGEREQ,
    GS2CS_GUILDASSIGNPOSTIONREQ,
    GS2CS_GUILDDATACHANGEREQ,
    GS2CS_MEMBERDATACHANGEREQ,
    GS2CS_GUILDLEVELUPREQ,
    GS2CS_GUILDOFFEGUILDRREQ,
    GS2CS_GUILDCOLLECTREQ,
    GS2CS_GUILDDELATEREQUESTREQ,
    CS2GS_GUILDDELATEREQUESTREQ,
    GS2CS_GUILDDELATEAGREEACK,
    CS2GS_GUILDDELATERESULT,
    GS2CS_GUILDDONATEREQUESTREQ,
    CS2GS_GUILDDONATEREQUESTREQ,
    GS2CS_GUILDDONATEACK,
	GS2CS_RAISEGUILDPLAYERITEM,
    CS2GS_GUILDDONATESTOP,
    GS2CS_GUILDQUESTRELEASEREQ,
    CS2GS_GUILDQUESTRELEASESTATUS,
    CS2GS_GUILDCLEARMEMBERACTIVITY,
    GS2CS_GUILDMESSAGE,
    CS2GS_GUILDMESSAGE,
    GS2CS_GUILDCONVENEREQ,
    CS2GS_GUILDCONVENEREQ,
    CS2GS_GUILDCONVENESTOP,
	GS2CS_GUILDAIMCHANGE,
	CS2GS_GUILDAIMCHANGEACK,
	GS2CS_PLAYERLVUPTOTHIRTY,			// luo.qin 4.20
	CS2GS_PLAYERLVUPTOTHIRTY,			// luo.qin 4.22
	CS2GS_MISSIONNOTENOUGH,
	GS2CS_GUILDSQREQ,
	CS2GS_GUILDBATTLESUM,
	MSG_GUILDSQACK,
	MSG_SETGUILDCAMPBATTLEVALUE,
	MSG_SETGUILDCAMPBATTLEVALUEACK,
	GS2CS_SETGUILDCAMPBATTLEVALUE,
	MSG_CHANGEGUILDNAMEREQ,
	GS2CS_CHANGEGUILDNAMEREQ,
	CS2GS_CHANGEGUILDNAMEACK,
	MSG_CHANGEGUILDNAMEACK,
	MSG_TELLGUILDPLAYERAISEITEM,

	GS2CS_GUILDMEMBERCHANGENAME,
	CS2GS_GUILDMEMBERCHANGENAME,
	MSG_GUILDCHANGENAMEACK,
	GS2CS_UPDATEGUILDCAMPBATTLEPOINT,
	GS2CS_UPDATEGUILDMEMBERONLINETIME,
	CS2GS_UPDATEGUILDMEMBERONLINETIME,
	MSG_UPDATEGUILDMEMBERONLINETIME,
};

struct MsgGuildModule : public Msg
{
    MsgGuildModule()
    {
        SetModuleType( EMessageModule_Guild );
    }
};

// ���󴴽�����
struct MsgCreateGuildReq : public MsgGuildModule
{
    MsgCreateGuildReq()
    {
        header.dwType   = MSG_CREATEGUILDREQ;
        header.stLength = sizeof( MsgCreateGuildReq );
    }

    char szName[ GuildDefine::MaxCreateLength ];    // ��������
	char szAim[ GuildDefine::MaxAimLength ];		// ������ּ
};

// ��Ӧ���󴴽�����
struct MsgCreateGuildAck : public MsgGuildModule
{
    MsgCreateGuildAck()
    {
        header.dwType   = MSG_CREATEGUILDACK;
        header.stLength = sizeof( MsgCreateGuildAck );

        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // �����ɹ�
        ECD_ErrorName,          // ���������ַ�, �Ƿ�����, 
        ECD_SaveName,           // ������ͬ���ֵİ���
        ECD_HaveGuild,          // �Ѿ��а�����, ���ܴ���
        ECD_LevelLess,          // �ȼ�����30��
        ECD_NotEnoughMoney,     // û���㹻������
		ECD_NotCountry,
    };

    unsigned char uchResult;
};

// ֪ͨ���, �´�����һ������, ����ͻ��˰����б�( ������Լ����ҵ�, ���һ��ϵͳ���� )
struct MsgTellCreateGuild : public MsgGuildModule
{
    MsgTellCreateGuild()
    {
        header.dwType   = MSG_TELLCREATEGUILD;
        header.stLength = sizeof( MsgTellCreateGuild );
    }

    unsigned char uchCountry;
    char szPlayer[ GuildDefine::MaxNameLength ];    // ������
    unsigned int nGuildID;
    char szName[ GuildDefine::MaxCreateLength ];    // ��������
};

// ֪ͨ�������ĳ�˼��������
struct MsgTellJoinGuildToView : public MsgGuildModule
{
    MsgTellJoinGuildToView()
    {
        header.dwType   = MSG_TELLJOINGUILDTOVIEW;
        header.stLength = sizeof( MsgTellJoinGuildToView );
		nGuildPosition = 0;
    }

    unsigned int nGuildID;          // ����ID
	unsigned char nGuildPosition;
};

// ֪ͨ�������ĳ���뿪������
struct MsgTellLeaveGuildToView : public MsgGuildModule
{
    MsgTellLeaveGuildToView()
    {
        header.dwType   = MSG_TELLLEAVEGUILDTOVIEW;
        header.stLength = sizeof( MsgTellLeaveGuildToView );
    }
};

// ֪ͨ���ɳ�Ա, �г�Ա������
struct MsgTellJoinGuildToGuild : public MsgGuildModule
{
    MsgTellJoinGuildToGuild()
    {
        header.dwType   = MSG_TELLJOINGUILDTOGUILD;
        header.stLength = sizeof( MsgTellJoinGuildToGuild );
    }

    GuildMember xMember;
};

// ֪ͨ���ɳ�Ա, �г�Ա�뿪��
struct MsgTellLeaveGuildToGuild : public MsgGuildModule
{
    MsgTellLeaveGuildToGuild()
    {
        header.dwType   = MSG_TELLLEAVEGUILDTOGUILD;
        header.stLength = sizeof( MsgTellLeaveGuildToGuild );
    }

    unsigned int nPlayerID;
};

// ���Ͱ�����Ϣ���ͻ���,
struct MsgTellGuildData : public MsgGuildModule
{
    MsgTellGuildData()
    {
        header.dwType   = MSG_TELLGUILDDATA;
        header.stLength = sizeof( MsgTellGuildData ) - sizeof( xMember );

        ustCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 200,
    };

    GuildData xData;

    unsigned short ustCount;
    GuildMember xMember[ MaxCount ];

    void AddMember( GuildMember& xInfo )
    {
        if ( ustCount >= MaxCount )
        { return; }

        xMember[ ustCount ] = xInfo;
        ++ustCount;
        header.stLength += sizeof( GuildMember );
    }
};

// �������а����б���ͻ���
struct MsgTellGuildList : public MsgGuildModule
{
    MsgTellGuildList()
    {
        header.dwType   = MSG_TELLGUILDLIST;
        header.stLength = sizeof( MsgTellGuildList ) - sizeof( xList );

        ustCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 500,
    };

    unsigned short ustCount;
    GuildListInfo xList[ MaxCount ]; 

    void AddGuild( GuildListInfo& xData )
    {
        if ( IsFull() )
        { return; }

        xList[ ustCount ] = xData;
        ++ustCount;

        header.stLength += sizeof( GuildListInfo );
    }

    bool IsFull() { return ustCount >= MaxCount; }

    void Reset()
    {
        header.stLength = sizeof( MsgTellGuildList ) - sizeof( xList );
        ustCount = 0;
    }
};

// �����뿪����
struct MsgLeaveGuildReq : public MsgGuildModule
{
    MsgLeaveGuildReq()
    {
        header.dwType   = MSG_LEAVEGUILDREQ;
        header.stLength = sizeof( MsgLeaveGuildReq );
    }
};

// �����뿪���
struct MsgLeaveGuildAck : public MsgGuildModule
{
    MsgLeaveGuildAck()
    {
        header.dwType   = MSG_LEAVEGUILDACK;
        header.stLength = sizeof( MsgLeaveGuildAck );

        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // �뿪�ɹ�
        ECD_NotHaveGuild,       // û�й���, 
        ECD_NotHaveRight,       // û��Ȩ��( ������ְλ, �޷�ֱ���˳����� )
    };

    unsigned char uchResult;
};

// ����ĳ��T������
struct MsgKickGuildReq : public MsgGuildModule
{
    MsgKickGuildReq()
    {
        header.dwType   = MSG_KICKGUILDREQ;
        header.stLength = sizeof( MsgKickGuildReq );
    }

    unsigned int nPlayerID;
};

// ��ӦT�˳�����
struct MsgKickGuildAck : public MsgGuildModule
{
    MsgKickGuildAck()
    {
        header.dwType   = MSG_KICKGUILDACK;
        header.stLength = sizeof( MsgKickGuildAck );

        uchResult = ECD_Success;

    }

    enum EConstDefine
    {
        ECD_Success = 0,        // �߳��ɹ�
        ECD_NotHaveGuild,       // û�а���, 
        ECD_NotHaveRight,       // û��T��Ȩ��, ���߱��˺���ְλһ���� ����һ����
    };

    unsigned char uchResult;
};

// ����ĳ�˽������
struct MsgInviteGuildReq : public MsgGuildModule
{
    MsgInviteGuildReq()
    {
        header.dwType   = MSG_INVITEUILDREQ;
        header.stLength = sizeof( MsgInviteGuildReq );
    }

    char szPlayerName[ GuildDefine::MaxNameLength ];
};

// ��Ӧ����������
struct MsgInviteGuildAck : public MsgGuildModule
{
    MsgInviteGuildAck()
    {
        header.dwType   = MSG_INVITEGUILDACK;
        header.stLength = sizeof( MsgInviteGuildAck );
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // ����ɹ�
        ECD_NotHaveGuild,       // �Լ�û�а���, 
        ECD_NotHaveRight,       // û������Ȩ��
        ECD_NotSaveCountry,     // ���Ǳ����Ĳ�������
        ECD_NotOnLine,          // �Է������� ���߲����� ������, 
        ECD_AlreadyHaveGuild,   // �Է��Ѿ��а�����
        ECD_LevelLess,          // �Է��ȼ�����20��, ��������������
        ECD_MemberFull,         // ��Ա���Ѿ�����
        ECD_NotAgree,           // �ܾ��������
		ECD_Agree,				// ͬ��������
        ECD_LeaveTimeLimit,     // �뿪���ɺ�24Сʱ��,�Է����ܼ������
    };

    unsigned char uchResult;
};

// ֪ͨĳ��, ĳ����������������
struct MsgInviteJoinGuildReq : public MsgGuildModule
{
    MsgInviteJoinGuildReq()
    {
        header.dwType   = MSG_INVITEJOINGUILDREQ;
        header.stLength = sizeof( MsgInviteJoinGuildReq );
    }

    unsigned int nGuildID;      // ����ID
    char szInviterName[ GuildDefine::MaxNameLength ];   // �����˵�����
};

// �����Ӧ�������뵽������
struct MsgInviteJoinGuildAck : public MsgGuildModule
{
    MsgInviteJoinGuildAck()
    {
        header.dwType   = MSG_INVITEJOINGUILDACK;
        header.stLength = sizeof( MsgInviteJoinGuildAck );
    }

    unsigned int nGuildID;      // ����ID
    bool bAgreeJoin;            // �Ƿ�ͬ������
};


// �������������
struct MsgJoinGuildReq : public MsgGuildModule
{
    MsgJoinGuildReq()
    {
        header.dwType   = MSG_JOINGUILDREQ;
        header.stLength = sizeof( MsgJoinGuildReq );
    }

    unsigned int nGuildID;      // ����ID
};

// ��Ӧ����������
struct MsgJoinGuildAck : public MsgGuildModule
{
    MsgJoinGuildAck()
    {
        header.dwType   = MSG_JOINGUILDACK;
        header.stLength = sizeof( MsgJoinGuildAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // ������ɳɹ�
        ECD_CreateSuccess,      // �������ɳɹ�
        ECD_AlreadyHaveGuild,   // �Է��Ѿ��а�����
        ECD_LevelLess,          // �ȼ�����
        ECD_NotSaveCountry,     // ���Ǳ����Ĳ�������
        ECD_TimeLimit,          // �˰��Ժ�24Сʱ�ڲ��ܼ������
        ECD_GuildNotExist,      // ����İ��ɲ�����
        ECD_MemberFull,         // Ŀ����ɳ�Ա���Ѿ�����
        ECD_NotAgree,           // �ܾ��������
        ECD_NotOnLine,          // ���ɹ���Ա��������
		ECD_IsCreSQ,			// �����ظ���
    };

    unsigned char uchResult;
};

// ������Ϣ�����ɹ���Ա, ĳ������������
struct MsgRequestJoinGuildReq : public MsgGuildModule
{
    MsgRequestJoinGuildReq()
    {
        header.dwType   = MSG_REQUESTJOINGUILDREQ;
        header.stLength = sizeof( MsgRequestJoinGuildReq );
    }

    unsigned int nPlayerID;                      // �����˵�DBID
    char szName[ GuildDefine::MaxNameLength ];   // �����˵�����
};

struct MsgGuildAddSQReq : public MsgGuildModule
{
    MsgGuildAddSQReq()
    {
        header.dwType   = MSG_GUILDADDSQREQ;
        header.stLength = sizeof( MsgGuildAddSQReq );
    }
    char szName[dr_MaxPlayerName];
	uint32 ID;
	uint32 Level;
	uint16 Profession;
};

struct MsgGuildDelSQReq : public MsgGuildModule
{
    MsgGuildDelSQReq()
    {
        header.dwType   = MSG_GUILDDELSQREQ;
        header.stLength = sizeof( MsgGuildDelSQReq );
    }
	uint32 ID;
};
// ��������������
struct MsgRequestJoinGuildAck : public MsgGuildModule
{
    MsgRequestJoinGuildAck()
    {
        header.dwType   = MSG_REQUESTJOINGUILDACK;
        header.stLength = sizeof( MsgRequestJoinGuildAck );
    }

    unsigned int nPlayerID;      // �����˵�DBID
    bool bAgreeJoin;             // �Ƿ�ͬ��������   
};

// �ͻ��������ѯ������Ϣ
struct MsgQueryGuildDataReq : public MsgGuildModule
{
    MsgQueryGuildDataReq()
    {
        header.dwType   = MSG_QUERYGUILDATAREQ;
        header.stLength = sizeof( MsgQueryGuildDataReq );
    }

    unsigned int nGuildID;
};

// ��Ӧ��ѯ������Ϣ
struct MsgQueryGuildDataAck : public MsgGuildModule
{
    MsgQueryGuildDataAck()
    {
        header.dwType   = MSG_QUERYGUILDATAACK;
        header.stLength = sizeof( MsgQueryGuildDataAck );

        memset( szGuildName, 0, sizeof( szGuildName ) );
        memset( szMasterName, 0, sizeof( szMasterName ) );
        memset( szGuildAim, 0, sizeof( szGuildAim ) );
    }

    unsigned int nGuildID;                              // ����ID
    char szGuildName[ GuildDefine::MaxNameLength ];     // ��������
    unsigned char uchLevel;                             // ���ɵȼ�
    char szMasterName[ GuildDefine::MaxNameLength ];    // ��������
    unsigned short ustMemberCount;                      // ��Ա����
    __int64 n64CreateTime;                                // ����ʱ��
    //char szGuildNotice[ GuildDefine::MaxNoticeLength ]; // ���ɹ���
	char szGuildAim[ GuildDefine::MaxAimLength ];		// ������ּ
};

// ֪ͨ�ͻ��˰��ɽ�ɢ��
struct MsgTellDisbandGuild : public MsgGuildModule
{
    MsgTellDisbandGuild()
    {
        header.dwType   = MSG_TELLDISBANDGUILD;
        header.stLength = sizeof( MsgTellDisbandGuild );
    }

    unsigned int nGuildID;      // ������Լ����ɽ�ɢ��, Ҫ������ʾ, ������Ҫ
};

// ���°��ɳ�Ա��Ϣ���ͻ���
struct MsgMemberDataUpdate : public MsgGuildModule
{
    MsgMemberDataUpdate()
    {
        header.dwType   = MSG_MEMBERDATAUPDATE;
        header.stLength = sizeof( MsgMemberDataUpdate );
    }

    unsigned int nPlayerID;         // ��ԱID

    unsigned char uchUpdateType;            // ������GuildDefine.h��    UpdateMemberOnLine....
    unsigned int nUpdateValue;
};

struct MsgGuildClientUpdate : public MsgGuildModule
{
    MsgGuildClientUpdate()
    {
        header.dwType   = MSG_GUILDCLIENUPDATE;
        header.stLength = sizeof( MsgGuildClientUpdate );
    }
	GuildListInfo ClientInfo;
};


// ���°�����Ϣ���ͻ���
struct MsgGuildDataUpdate : public MsgGuildModule
{
    MsgGuildDataUpdate()
    {
        header.dwType   = MSG_GUILDDATAUPDATE;
        header.stLength = sizeof( MsgGuildDataUpdate );
    }

    unsigned char uchUpdateType;            // ������GuildDefine.h��    UpdateGuildLevel....
    unsigned int nUpdateValue;
};

// �����޸İ��ɹ���
struct MsgGuildNoticeChangeReq : public MsgGuildModule
{
    MsgGuildNoticeChangeReq()
    {
        header.dwType   = MSG_GUILDNOTICECHANGEREQ;
        header.stLength = sizeof( MsgGuildNoticeChangeReq );
    }

    char szNotice[ GuildDefine::MaxNoticeLength ];
};

// ���Ͱ��ɹ��浽�ͻ���
struct MsgTellGuildNotice : public MsgGuildModule
{
    MsgTellGuildNotice()
    {
        header.dwType   = MSG_TELLGUILDNOTICE;
        header.stLength = sizeof( MsgTellGuildNotice );
    }
    
    char szNotice[ GuildDefine::MaxNoticeLength ];
};

// �����޸İ�����ּ
struct MsgChangeGuildAimReq : public MsgGuildModule
{
	MsgChangeGuildAimReq()
	{
		header.dwType = MSG_CHANGEGUILDAIM;
		header.stLength = sizeof( MsgChangeGuildAimReq );
	}

	char szAim[ GuildDefine::MaxAimLength ];
};

// �ظ������޸İ�����ּ
struct MsgChangeGuildAimAck : public MsgGuildModule
{
	MsgChangeGuildAimAck()
	{
		header.dwType = MSG_CHANGEGUILDAIMACK;
		header.stLength = sizeof( MsgChangeGuildAimAck );

		uchResult = ECD_Success;
	}

	enum EConstDefine
	{
		ECD_Success = 0,
		ECD_InCD,	// �޸���ּCD��
	};

	unsigned char uchResult;
};

// ֪ͨ�ͻ��˰�����ּ�仯
struct MsgTellGuildAim : public MsgGuildModule
{
	MsgTellGuildAim()
	{
		header.dwType = MSG_TELLGUILDAIM;
		header.stLength = sizeof( MsgTellGuildAim );
	}

	char szAim[ GuildDefine::MaxAimLength ];
};

// �����ȥ����ְ��
struct MsgGuildResignPositionReq : public MsgGuildModule
{
    MsgGuildResignPositionReq()
    {
        header.dwType   = MSG_GUILDRESIGNPOSITIONREQ;
        header.stLength = sizeof( MsgGuildResignPositionReq );
    }
};

// ����ĳ���˵�ְλ
struct MsgGuildAssignPositionReq : public MsgGuildModule
{
    MsgGuildAssignPositionReq()
    {
        header.dwType   = MSG_GUILDASSIGNPOSITIONREQ;
        header.stLength = sizeof( MsgGuildAssignPositionReq );
    }

    unsigned int nPlayerID;         // ��ԱID
    unsigned char uchPosition;      // ������ְλ ( ����GuildDefine::Position_Member �൱�ڰ������Ĺ�ְ )
};

// ��������Ӧ����ְλ
struct MsgGuildAssignPositionAck : public MsgGuildModule
{
    MsgGuildAssignPositionAck()
    {
        header.dwType   = MSG_GUILDASSIGNPOSITIONACK;
        header.stLength = sizeof( MsgGuildAssignPositionAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // �����ɹ�
        ECD_NotHaveRight,       // û��Ȩ��
        ECD_SamePosition,       // �Ѿ��Ǹ�ְλ
        ECD_NotHaveFamily,      // û�м���, ��������Ϊ���峤
    };

    unsigned char uchResult;
};

// ����ְλ��ĳ��
struct MsgGuildTransferPositionReq : public MsgGuildModule
{
    MsgGuildTransferPositionReq()
    {
        header.dwType   = MSG_GUILDTRANSFERPOSITIONREQ;
        header.stLength = sizeof( MsgGuildTransferPositionReq );
    }

    unsigned int nPlayerID;     // ����ֻ�����ø�������...����ֻ�����ø���ְλ����
};

// ��������
struct MsgGuildCreateFamilyReq : public MsgGuildModule
{
    MsgGuildCreateFamilyReq()
    {
        header.dwType   = MSG_GUILDCREATEFAMILYREQ;
        header.stLength = sizeof( MsgGuildCreateFamilyReq );

        memset( szName, 0, sizeof( szName ) );
    }

    char szName[ GuildDefine::MaxFamilyLength ];
};

// ��������Ӧ��������
struct MsgGuildCreateFamilyAck : public MsgGuildModule
{
    MsgGuildCreateFamilyAck()
    {
        header.dwType   = MSG_GUILDCREATEFAMILYACK;
        header.stLength = sizeof( MsgGuildCreateFamilyAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // �����ɹ�
        ECD_NotHaveRight,       // û��Ȩ��
        ECD_FamilyFull,         // ��������
        ECD_SaveFamily,         // ������ͬ���ֵļ���
    };

    unsigned char uchResult;
};

// �ͻ��������޸ļ�������
struct MsgGuildFamilyChangeReq : public MsgGuildModule
{
    MsgGuildFamilyChangeReq()
    {
        header.dwType   = MSG_GUILDFAMILYCHANGEREQ;
        header.stLength = sizeof( MsgGuildFamilyChangeReq );

        memset( szName, 0, sizeof( szName ) );
    }

    unsigned char uchFamilyID;
    char szName[ GuildDefine::MaxFamilyLength ];        // ���������, �൱��ɾ������
};

// ��������Ӧ�޸ļ���
struct MsgGuildFamilyChangeAck : public MsgGuildModule
{
    MsgGuildFamilyChangeAck()
    {
        header.dwType   = MSG_GUILDFAMILYCHANGEACK;
        header.stLength = sizeof( MsgGuildFamilyChangeAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // �޸ĳɹ�
        ECD_NotHaveRight,       // û��Ȩ��
        ECD_SaveFamily,         // ������ͬ���ֵļ���
        ECD_EmptyFamily,        // �ռ��岻�ܸ��� ���� ɾ��
		ECD_AlreadyHaveFamily,	// �Է��Ǽ��峤
        ECD_IsFamilyMaster,     // ���峤�޷�ת��
    };

    unsigned char uchResult;
};

// ������֪ͨ�ͻ��˼�����Ϣ�ı�
struct MsgTellGuildFamilyChange : public MsgGuildModule
{
    MsgTellGuildFamilyChange()
    {
        header.dwType   = MSG_TELLGUILDFAMILYCHANGE;
        header.stLength = sizeof( MsgTellGuildFamilyChange );

        memset( szName, 0, sizeof( szName ) );
    }

    unsigned char uchFamilyID;                      // ����ID
    char szName[ GuildDefine::MaxFamilyLength ];    // ��������( Ϊ�� �൱��ɾ������ )
};

// �ͻ�������ı��Ա������Ϣ
struct MsgGuildMemberFamilyChangeReq : public MsgGuildModule
{
    MsgGuildMemberFamilyChangeReq()
    {
        header.dwType   = MSG_GUILDMEMBERFAMILYCHANGEREQ;
        header.stLength = sizeof( MsgGuildMemberFamilyChangeReq );
    }

    unsigned int nPlayerID;
    unsigned char uchFamilyID;
};

// ��������Ӧ�ı��Ա������Ϣ
struct MsgGuildMemberFamilyChangeAck : public MsgGuildModule
{
    MsgGuildMemberFamilyChangeAck()
    {
        header.dwType   = MSG_GUILDMEMBERFAMILYCHANGEACK;
        header.stLength = sizeof( MsgGuildMemberFamilyChangeAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // �ı�ɹ�
        ECD_NotHaveRight,       // û��Ȩ��
        ECD_SaveFamily,         // ��ͬ�ļ���, ����Ҫ�ƶ�
        ECD_EmptyFamily,        // �����ƶ����ռ���
		ECD_AlreadyHaveFamily,	// �Է��Ǽ��峤
    };

    unsigned char uchResult;
};

// �������������Ϣ
struct MsgGuildLevelUpAck : public MsgGuildModule
{
    MsgGuildLevelUpAck()
    {
        header.dwType   = MSG_GUILDLEVELUPACK;
        header.stLength = sizeof( MsgGuildLevelUpAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // �����ɹ�
        ECD_NotHaveRight,       // û��Ȩ��
        ECD_NotEnoughMoney,     // û���㹻�İ���ʽ�
        ECD_NotEnoughExp,       // û���㹻�İ�ᾭ��
        ECD_MaxLevel,           // �Ѿ��������ɵȼ���
		ECD_NotEnoughMisson,	// û���㹻��ʹ����
    };

    unsigned char uchResult;
};

// ��Ӧ�ﹱ����
struct MsgGuildOfferBuildAck : public MsgGuildModule
{
    MsgGuildOfferBuildAck()
    {
        header.dwType   = MSG_GUILDOFFERBUILDACK;
        header.stLength = sizeof( MsgGuildOfferBuildAck );
    }

    enum EConstDefine
    {
        ECD_NotEnoughOffer = 0,     // û���㹻�İﹱ
        ECD_MaxGuildExp,        // ���ɾ����Ѿ������ֵ��
    };

    unsigned char uchResult;
};

// ���뵯������
struct MsgGuildDelateRequestAck : public MsgGuildModule
{
    MsgGuildDelateRequestAck()
    {
        header.dwType   = MSG_GUILDDELATEREQUESTACK;
        header.stLength = sizeof( MsgGuildDelateRequestAck );
    }

    enum EConstDefine
    {
        ECD_ErrorTime = 0,          // �����ʱ���
        ECD_AlreadyDelate,      // �Ѿ����˵�����
        ECD_LevelLess,          // �ȼ�����
        ECD_MaxGuildExp,        // ���ɾ����Ѿ������ֵ��
        ECD_NotEnoughMoney,     // û���㹻�Ľ�Ǯ
        ECD_OnLineLess,         // �������߳�Ա����20��, ���ܷ�����
    };

    unsigned char uchResult;
};

// �����а��ɳ�Ա�����Ƿ�ͬ�ⵯ������Ϣ
struct MsgGuildDelateAgreeReq : public MsgGuildModule
{
    MsgGuildDelateAgreeReq()
    {
        header.dwType   = MSG_GUILDDELATEAGREEREQ;
        header.stLength = sizeof( MsgGuildDelateAgreeReq );
    }

    unsigned int nPlayerID;     // �����������
};

// �ָ��Ƿ�ͬ�ⵯ��
struct MsgGuildDelateAgreeAck : public MsgGuildModule
{
    MsgGuildDelateAgreeAck()
    {
        header.dwType   = MSG_GUILDDELATEAGREEACK;
        header.stLength = sizeof( MsgGuildDelateAgreeAck );
    }

    bool bAgreeDelate;  // �Ƿ�ͬ�ⵯ��
};

// �������
struct MsgGuildDelateResult : public MsgGuildModule
{
    MsgGuildDelateResult()
    {
        header.dwType   = MSG_GUILDDELATERESULT;
        header.stLength = sizeof( MsgGuildDelateResult );
    }

    unsigned int nPlayerID;     // �����������
    bool bDelateSuccess;        // �Ƿ����ɹ�
};

// ����ļ��������ͻ���
struct MsgGuildDonateReq : public MsgGuildModule
{
    MsgGuildDonateReq()
    {
        header.dwType   = MSG_GUILDDONATEREQ;
        header.stLength = sizeof( MsgGuildDonateReq );
    }
};

// �ͻ��˸����������;��׶��ٽ�Ǯ
struct MsgGuildDonateAck : public MsgGuildModule
{
    MsgGuildDonateAck()
    {
        header.dwType   = MSG_GUILDDONATEACK;
        header.stLength = sizeof( MsgGuildDonateAck );
    }

    unsigned int nMoney;        // ���׶���Ǯ( ��������10�� )
};

// �����ͻ��˷�������
struct MsgGuildReleaseAck : public MsgGuildModule
{
    MsgGuildReleaseAck()
    {
        header.dwType   = MSG_GUILDRELEASEACK;
        header.stLength = sizeof( MsgGuildReleaseAck );

        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // �ı�ɹ�
        ECD_NotHaveRight,       // û��Ȩ��
        ECD_GuildLevelLess,     // ���ɵȼ�����
        ECD_ErrorTime,          // ������22����ǰ����
        ECD_AlreadyRelease,     // �Ѿ�������
        ECD_NotEnoughMoney,     // û���㹻�Ľ�Ǯ
        ECD_QuestError,         // ���ܷ���������
    };

    unsigned char uchResult;
};

// ֪ͨ�ͻ��˰������񷢲�״̬
struct MsgGuildQuestReleaseStatus : public MsgGuildModule
{
    MsgGuildQuestReleaseStatus()
    {
        header.dwType   = MSG_GUILDQUESTRELEASESTATUS;
        header.stLength = sizeof( MsgGuildQuestReleaseStatus );
    }

    unsigned int nQuestType;      // == 0 ��ʾ�������Ѿ�������
    __int64 n64RelasetTime;    
};

// ֪ͨ�����г�Ա���ܻ�Ծ�����õ�����, ��������ܵĻ�Ծ��,
struct MsgGuildClearMemberActivity : public MsgGuildModule
{
    MsgGuildClearMemberActivity()
    {
        header.dwType   = MSG_GUILDCLEARMEMBERACTIVITY;
        header.stLength = sizeof( MsgGuildClearMemberActivity );
    }
};

// ��ʾ������Ὣ��ĳ���ڽ�ɢ
struct MsgTellGuildDisbanTime : public MsgGuildModule
{
    MsgTellGuildDisbanTime()
    {
        header.dwType   = MSG_TELLGUILDDISBANDTIME;
        header.stLength = sizeof( MsgTellGuildDisbanTime );
    }

    __int64 n64DisbandTime;
};

struct MsgGuildShopLevelUpReq : public MsgGuildModule
{
    MsgGuildShopLevelUpReq()
    {
        header.dwType   = MSG_GUILDSHOPLEVELUPREQ;
        header.stLength = sizeof( MsgGuildShopLevelUpReq );
    }

    unsigned char uchLevel;
};

// ���������̵꼤����Ϣ
struct MsgGuildShopLevelUpAck : public MsgGuildModule 
{
    MsgGuildShopLevelUpAck()
    {
        header.dwType   = MSG_GUILDSHOPLEVELUPACK;
        header.stLength = sizeof( MsgGuildShopLevelUpAck );

        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // �ı�ɹ�
        ECD_NotHaveRight,       // û��Ȩ��
        ECD_GuildLevelLess,     // ���ɵȼ�����
        ECD_NotEnoughExp,      // û���㹻�İ��ɾ���
        ECD_AlreadActive,      // �Ѿ���������
        ECD_ErrorLevel,        // ����ĵȼ�
    };

    unsigned char uchResult;
};

// ��������̵���Ʒ
struct MsgGuildBuyItemReq : public MsgGuildModule
{
    MsgGuildBuyItemReq()
    {
        header.dwType   = MSG_GUILDBUYITEMREQ;
        header.stLength = sizeof( MsgGuildBuyItemReq );
    }

    unsigned char uchLevel;     // �����̵�ȼ�
    unsigned int nItemID;       // �������Ʒ
    unsigned int nCount;        // ���������
};

struct MsgGuildBuyItemAck : public MsgGuildModule
{
    MsgGuildBuyItemAck()
    {
        header.dwType   = MSG_GUILDBUYITEMACK;
        header.stLength = sizeof( MsgGuildBuyItemAck );
    }

    enum EConstDefine
    {
        ECD_NotHaveRight,       // û��Ȩ��
        ECD_LevelNotActive,     // �����̵�û�м���
        ECD_ErrorItem,          // û�д���Ʒ����
        ECD_NotEnoughOffer,     // û���㹻�İﹱ
        ECD_ErrorLevel,         // ������̵�ȼ�
        ECD_PackFull,           // ��������
    };

    unsigned char uchResult;
};

// �����ټ����� ��ĳ����ͼ
struct MsgGuildConveneReq : public MsgGuildModule
{
    MsgGuildConveneReq()
    {
        header.dwType   = MSG_GUILDCONVENTREQ;
        header.stLength = sizeof( MsgGuildConveneReq );
    }

    unsigned int nMapID;
};

// ���ڴ�Ӧ�ټ�, ��ͬ�����û���Ϣ
struct MsgGuildConveneAck : public MsgGuildModule
{
    MsgGuildConveneAck()
    {
        header.dwType   = MSG_GUILDCONVENTACK;
        header.stLength = sizeof( MsgGuildConveneAck );
    }
};

// �ظ������ɹ���
struct MsgGuildNoticeAck : public MsgGuildModule
{
	MsgGuildNoticeAck()
	{
		SetType( MSG_GUILDNOTICEACK );
		SetLength( sizeof( MsgGuildNoticeAck ) );
	}

	enum EConstDefine
	{
		ECD_Success = 0,
		ECD_NotHaveRight,
	};

	unsigned char uchResult;
};

// �ظ�ת��ְλ
struct MsgGuildTransferAck : public MsgGuildModule
{
	MsgGuildTransferAck()
	{
		SetType( MSG_GUILDTRANSFERACK );
		SetLength( sizeof( MsgGuildTransferAck ) );
	}

	enum EConstDefine
	{
		ECD_Success = 0,
		ECD_NotHaveRight,			// ��û��Ȩ��ת��ְλ
		ECD_NotViceMaster,			// ����ֻ��ת�ø����������Է����Ǹ�����	
		ECD_LevelLess,				// �Է��ȼ����㣬�޷�ת��
		ECD_NotGuildMember,		    // �Է����Ǳ����Ա
		ECD_NotSameFamily,			// ת���峤ʱ���Է�������ͬһ�����Ա
		ECD_IsKing,					// �Լ��ǹ����� ����ת�ð���
		ECD_GameBattleCD,			// ����ԼսCD�ڼ䲻����ת�ù���Լս
		ECD_GameBattleExites,		// ����Լս����
	};

	unsigned char uchResult;
};

///////////////////////////////////////////////////////////////////////////////
// ��������ͨѶ
////////////////////////////////////////////////////////////////////////////////
struct CS2DBGuildDataLoadReq : public MsgGuildModule
{
    CS2DBGuildDataLoadReq()
    {
        header.dwType   = CS2DB_GUILDDATALOADREQ;
        header.stLength = sizeof( CS2DBGuildDataLoadReq );
    }
};

struct DB2CSGuildDataList : public MsgGuildModule
{
    DB2CSGuildDataList()
    {
        header.dwType   = DB2CS_GUILDDATALIST;
        header.stLength = sizeof( DB2CSGuildDataList ) - sizeof( xList );
        ustCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 500,
    };

    unsigned short ustCount;
    GuildDataToServer xList[ MaxCount ];

    void AddGuildData( GuildDataToServer& xData )
    {
        if ( IsFull() )
        { return; }

        xList[ ustCount ] = xData;
        ++ustCount;
        header.stLength += sizeof( GuildDataToServer );
    }

    bool IsFull() { return ustCount >= MaxCount; }
    void Reset()
    {
        header.stLength = sizeof( DB2CSGuildDataList ) - sizeof( xList );
        ustCount = 0;
    }
};

struct DB2CSGuildMemberList : public MsgGuildModule
{
    DB2CSGuildMemberList()
    {
        header.dwType   = DB2CS_GUILDMEMBERLIST;
        header.stLength = sizeof( DB2CSGuildMemberList ) - sizeof( xList );
        ustCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 300,
    };

    unsigned short ustCount;
    GuildMember xList[ MaxCount ];

    void AddGuildMember( GuildMember& xMember )
    {
        if ( IsFull() )
        { return; }

        xList[ ustCount ] = xMember;
        ++ustCount;
        header.stLength += sizeof( GuildMember );
    }

    bool IsFull() { return ustCount >= MaxCount; }
    void Reset()
    {
        header.stLength = sizeof( DB2CSGuildMemberList ) - sizeof( xList );
        ustCount = 0;
    }
};

struct CS2DBGuildDataUpdateReq : public MsgGuildModule
{
    CS2DBGuildDataUpdateReq()
    {
        header.dwType   = CS2DB_GUILDDATAUPDATEREQ;
        header.stLength = sizeof( CS2DBGuildDataUpdateReq );
    }

    GuildDataToServer xData;
};

struct CS2DBGuildMemberUpdateReq : public MsgGuildModule
{
    CS2DBGuildMemberUpdateReq()
    {
        header.dwType   = CS2DB_GUILDMEMBERUPDATEREQ;
        header.stLength = sizeof( CS2DBGuildMemberUpdateReq ) - sizeof( xList );
        ustCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 300,
    };

    unsigned short ustCount;
    GuildMember xList[ MaxCount ];

    void AddGuildMember( GuildMember& xMember )
    {
        if ( IsFull() )
        { return; }

        xList[ ustCount ] = xMember;
        ++ustCount;
        header.stLength += sizeof( GuildMember );
    }

    bool IsFull() { return ustCount >= MaxCount; }
};

struct CS2DBGuildDisbandReq : public MsgGuildModule
{
    CS2DBGuildDisbandReq()
    {
        header.dwType   = CS2DB_GUILDDISBANDREQ;
        header.stLength = sizeof( CS2DBGuildDisbandReq );
    }

    unsigned int nGuildID;
};

struct CS2DBGuildMemberLeaveReq : public MsgGuildModule
{
    CS2DBGuildMemberLeaveReq()
    {
        header.dwType   = CS2DB_GUILDMEMBERLEAVEREQ;
        header.stLength = sizeof( CS2DBGuildMemberLeaveReq );
    }

    unsigned int nPlayerID;
};

///////////////////////////////////////////////////////////////////////////////
struct CS2GSGuildDataList : public MsgGuildModule
{
    CS2GSGuildDataList()
    {
        header.dwType   = CS2GS_GUILDDATALIST;
        header.stLength = sizeof( CS2GSGuildDataList ) - sizeof( xMemberList );
        ustCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 300,
    };

    GuildDataToServer xData;

    unsigned short ustCount;
    GuildMember xMemberList[ MaxCount ];

    void AddGuildMember( GuildMember& xMember )
    {
        if ( IsFull() )
        { return; }

        xMemberList[ ustCount ] = xMember;

        ++ustCount;
        header.stLength += sizeof( GuildMember );
    }

    bool IsFull() { return ustCount >= MaxCount; }
};

struct CS2GSGuildDataSendSuccess : public MsgGuildModule
{
    CS2GSGuildDataSendSuccess()
    {
        header.dwType   = CS2GS_GUILDDATASENDSUCCESS;
        header.stLength = sizeof( CS2GSGuildDataSendSuccess );
    }
};

struct GS2CSCreateGuildReq : public MsgGuildModule
{
    GS2CSCreateGuildReq()
    {
        header.dwType   = GS2CS_CREATEGUILDREQ;
        header.stLength = sizeof( GS2CSCreateGuildReq );
    }

    unsigned char uchCountry;       // ����
    char szName[ GuildDefine::MaxCreateLength ];    // ��������
	char szAim[ GuildDefine::MaxAimLength ];		// ������ּ
    GuildMember xMember;
};

struct CS2GSCreateGuildAck : public MsgGuildModule
{
    CS2GSCreateGuildAck()
    {
        header.dwType   = CS2GS_CREATEGUILDACK;
        header.stLength = sizeof( CS2GSCreateGuildAck );
    }

    char szPlayer[ GuildDefine::MaxNameLength ];
    GuildDataToServer xGuild;
};


struct GS2CSLeaveGuildReq : public MsgGuildModule
{
    GS2CSLeaveGuildReq()
    {
        header.dwType   = GS2CS_LEAVEGUILDREQ;
        header.stLength = sizeof( GS2CSLeaveGuildReq );
    }

    unsigned int nPlayerID;
    unsigned int nGuildID;
};

struct CS2GSLeaveGuildAck : public MsgGuildModule
{
    CS2GSLeaveGuildAck()
    {
        header.dwType   = CS2GS_LEAVEGUILDACK;
        header.stLength = sizeof( CS2GSLeaveGuildAck );
    }

    unsigned int nPlayerID;
    unsigned int nGuildID;
};

struct GS2CSKickGuildReq : public MsgGuildModule
{
    GS2CSKickGuildReq()
    {
        header.dwType   = GS2CS_KICKGUILDREQ;
        header.stLength = sizeof( GS2CSKickGuildReq );
    }

    unsigned int nPlayerID;
    unsigned int nTargetID;
    unsigned int nGuildID;
};

struct GS2CSInviteGuildReq : public MsgGuildModule
{
    GS2CSInviteGuildReq()
    {
        header.dwType   = GS2CS_INVITEGUILDREQ;
        header.stLength = sizeof( GS2CSInviteGuildReq );
    }

    unsigned int nPlayerID;
    unsigned int nTargetID;
    unsigned int nGuildID;
};

struct GS2CSGuildSQReq : public MsgGuildModule
{
    GS2CSGuildSQReq()
    {
        header.dwType   = GS2CS_GUILDSQREQ;
        header.stLength = sizeof( GS2CSGuildSQReq );
    }
    unsigned int nPlayerID;
    unsigned int nGuildID;
};


struct MsgGuildSQAck : public MsgGuildModule
{
	enum EConstDefine
    {
        const_iMaxNum = 500
    };
	struct SQAtt
	{
		uint32	Level;
		uint32	ID;
		uint16  Profession;
		char	szName[dr_MaxPlayerName];	
	};
    MsgGuildSQAck()
    {
        header.dwType   = MSG_GUILDSQACK;
		Num =0;
    }
	void CaluLength()
    {
        header.stLength = (int)(sizeof( MsgGuildSQAck ) - (const_iMaxNum - Num)*sizeof(SQAtt));
    }
	void pushItem(uint32 ID,uint32 Level,uint16 Profession,const char* Name)
	{
		SQAtt sq;
		sq.ID =ID;
		sq.Level = Level;
		sq.Profession = Profession;
		strcpy_s(sq.szName,dr_MaxPlayerName-1,Name);
		Info[Num] = sq;
		++Num;
	}
    uint32		Num;
	//���� ְҵ ID �ȼ�	
	SQAtt		Info[const_iMaxNum];
};

struct GS2CSInviteJoinGuildAck : public MsgGuildModule
{
    GS2CSInviteJoinGuildAck()
    {
        header.dwType   = GS2CS_INVITEJOINGUILDACK;
        header.stLength = sizeof( GS2CSInviteJoinGuildAck );
    }

    bool bAgreeJoin;
    GuildMember xMember;
};

struct CS2GSJoinGuildAck : public MsgGuildModule
{
    CS2GSJoinGuildAck()
    {
        header.dwType   = CS2GS_JOINGUILDACK;
        header.stLength = sizeof( CS2GSJoinGuildAck );
    }

    GuildMember xMember;
};

struct GS2CSJoinGuildReq : public MsgGuildModule
{
    GS2CSJoinGuildReq()
    {
        header.dwType   = GS2CS_JOINGUILDREQ;
        header.stLength = sizeof( GS2CSJoinGuildReq );
    }

    GuildMember xMember;
};

struct GS2CSRequestJoinGuildAck : public MsgGuildModule
{
    GS2CSRequestJoinGuildAck()
    {
        header.dwType   = GS2CS_REQUESTJOINGUILDACK;
        header.stLength = sizeof( GS2CSRequestJoinGuildAck );
    }

    unsigned int nPlayerID;     // ������ID
    unsigned int nGuildID;      // ����ID
    unsigned int nTargetID;     // ������ID
    bool bAgreeJoin;
};

struct CS2GSDisbandGuildAck : public MsgGuildModule
{
    CS2GSDisbandGuildAck()
    {
        header.dwType   = GS2CS_DISBANDGUILDACK;
        header.stLength = sizeof( CS2GSDisbandGuildAck );
    }

    unsigned int nGuildID;
};

struct CS2GSMemberDataUpdate : public MsgGuildModule
{
    CS2GSMemberDataUpdate()
    {
        header.dwType   = CS2GS_MEMBERDATAUPDATE;
        header.stLength = sizeof( CS2GSMemberDataUpdate );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    unsigned char uchUpdateType;
    unsigned int nUpdateValue;
};

struct CS2GSGuildDataUpdate : public MsgGuildModule
{
    CS2GSGuildDataUpdate()
    {
        header.dwType   = CS2GS_GUILDDATAUPDATE;
        header.stLength = sizeof( CS2GSGuildDataUpdate );
    }

    unsigned int nGuildID;

    unsigned char uchUpdateType;
    __int64 n64UpdateValue;
};

struct GS2CSGuildNoticeChangeReq : public MsgGuildModule
{
    GS2CSGuildNoticeChangeReq()
    {
        header.dwType   = GS2CS_GUILDNOTICECHANGEREQ;
        header.stLength = sizeof( GS2CSGuildNoticeChangeReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    char szNotice[ GuildDefine::MaxNoticeLength ];
};

struct GS2CSGuildAimChangeReq : public MsgGuildModule
{
	GS2CSGuildAimChangeReq()
	{
		header.dwType = GS2CS_GUILDAIMCHANGE;
		header.stLength = sizeof( GS2CSGuildAimChangeReq );
	}

	unsigned int nGuildID;
	unsigned int nPlayerID;

	char szAim[ GuildDefine::MaxAimLength ];
};

struct CS2GSGuildAimChangeAck : public MsgGuildModule
{
	CS2GSGuildAimChangeAck()
	{
		header.dwType   = CS2GS_GUILDAIMCHANGEACK;
		header.stLength = sizeof( CS2GSGuildAimChangeAck );
	}

	unsigned int nGuildID;
	__int64 nChangeAimTime;
	char szAim[ GuildDefine::MaxAimLength ];
};

struct CS2GSGuildNoticeChangeAck : public MsgGuildModule
{
    CS2GSGuildNoticeChangeAck()
    {
        header.dwType   = CS2GS_GUILDNOTICECHANGEACK;
        header.stLength = sizeof( CS2GSGuildNoticeChangeAck );
    }

    unsigned int nGuildID;
    char szNotice[ GuildDefine::MaxNoticeLength ];
};

struct GS2CSGuildResignPositionReq : public MsgGuildModule
{
    GS2CSGuildResignPositionReq()
    {
        header.dwType   = GS2CS_GUILDRESIGNPOSITIONREQ;
        header.stLength = sizeof( GS2CSGuildResignPositionReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
};

struct GS2CSGuildTransferPositionReq : public MsgGuildModule
{
    GS2CSGuildTransferPositionReq()
    {
        header.dwType   = GS2CS_GUILDTRANSFERPOSITIONREQ;
        header.stLength = sizeof( GS2CSGuildTransferPositionReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    unsigned int nTargetID;
};

struct GS2CSGuildCreateFamilyReq : public MsgGuildModule
{
    GS2CSGuildCreateFamilyReq()
    {
        header.dwType   = GS2CS_GUILDCREATEFAMILYREQ;
        header.stLength = sizeof( GS2CSGuildCreateFamilyReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    char szName[ GuildDefine::MaxFamilyLength ];
};

struct GS2CSGuildFamilyChangeReq : public MsgGuildModule
{
    GS2CSGuildFamilyChangeReq()
    {
        header.dwType   = GS2CS_GUILDFAMILYCHANGEREQ;
        header.stLength = sizeof( GS2CSGuildFamilyChangeReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    unsigned char uchFamilyID;
    char szName[ GuildDefine::MaxFamilyLength ];
};

struct CS2GSGuildFamilyChange : public MsgGuildModule
{
    CS2GSGuildFamilyChange()
    {
        header.dwType   = CS2GS_GUILDFAMILYCHANGE;
        header.stLength = sizeof( CS2GSGuildFamilyChange );

        memset( szName, 0, sizeof( szName ) );
    }

    unsigned int nGuildID;
	unsigned int nRequesterID;
    unsigned char uchFamilyID;
    char szName[ GuildDefine::MaxFamilyLength ];
};

struct GS2CSGuildMemberFamilyChangeReq : public MsgGuildModule
{
    GS2CSGuildMemberFamilyChangeReq()
    {
        header.dwType   = GS2CS_GUILDMEMBERFAMILYCHANGEREQ;
        header.stLength = sizeof( GS2CSGuildMemberFamilyChangeReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    unsigned int nTargetID;
    unsigned char uchFamilyID;
};

struct GS2CSGuildAssignPositionReq : public MsgGuildModule
{
    GS2CSGuildAssignPositionReq()
    {
        header.dwType   = GS2CS_GUILDASSIGNPOSTIONREQ;
        header.stLength = sizeof( GS2CSGuildAssignPositionReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    unsigned int nTargetID;
    unsigned char uchPosition;
};

// ������������ı�
struct GS2CSGuildDataChangeReq : public MsgGuildModule
{
    GS2CSGuildDataChangeReq()
    {
        header.dwType   = GS2CS_GUILDDATACHANGEREQ;
        header.stLength = sizeof( GS2CSGuildDataChangeReq );
    }

    unsigned int nGuildID;
    unsigned char uchChangeType;

    unsigned char uchOperateType;
    unsigned int nValue;
};

struct GS2CSMemberDataChangeReq : public MsgGuildModule
{
    GS2CSMemberDataChangeReq()
    {
        header.dwType   = GS2CS_MEMBERDATACHANGEREQ;
        header.stLength = sizeof( GS2CSMemberDataChangeReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    unsigned char uchChangeType;
    unsigned char uchOperateType;
    unsigned int nValue;
};

// �����������
struct GS2CSGuildLevelUpReq : public MsgGuildModule
{
    GS2CSGuildLevelUpReq()
    {
        header.dwType   = GS2CS_GUILDLEVELUPREQ;
        header.stLength = sizeof( GS2CSGuildLevelUpReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
};

// ������װﹱ
struct GS2CSGuildOfferBuildReq : public MsgGuildModule
{
    GS2CSGuildOfferBuildReq()
    {
        header.dwType   = GS2CS_GUILDOFFEGUILDRREQ;
        header.stLength = sizeof( GS2CSGuildOfferBuildReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
};

struct GS2CSGuildCollectReq : public MsgGuildModule
{
    GS2CSGuildCollectReq()
    {
        header.dwType   = GS2CS_GUILDCOLLECTREQ;
        header.stLength = sizeof( GS2CSGuildCollectReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
};

struct GS2CSGuildDelateRequestReq : public MsgGuildModule
{
    GS2CSGuildDelateRequestReq()
    {
        header.dwType   = GS2CS_GUILDDELATEREQUESTREQ;
        header.stLength = sizeof( GS2CSGuildDelateRequestReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
};

struct CS2GSGuildDelateRequestReq : public MsgGuildModule
{
    CS2GSGuildDelateRequestReq()
    {
        header.dwType   = CS2GS_GUILDDELATEREQUESTREQ;
        header.stLength = sizeof( CS2GSGuildDelateRequestReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
};

struct GS2CSGuildDelateAgreeAck : public MsgGuildModule
{
    GS2CSGuildDelateAgreeAck()
    {
        header.dwType   = GS2CS_GUILDDELATEAGREEACK;
        header.stLength = sizeof( GS2CSGuildDelateAgreeAck );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
};

struct CS2GSGuildDelateResult : public MsgGuildModule
{
    CS2GSGuildDelateResult()
    {
        header.dwType   = CS2GS_GUILDDELATERESULT;
        header.stLength = sizeof( CS2GSGuildDelateResult );
        bDelateSuccess = false;
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    bool bDelateSuccess;      // �ɹ� ���� ʧ��
};

struct GS2CSGuildDonateRequestReq : public MsgGuildModule
{
    GS2CSGuildDonateRequestReq()
    {
        header.dwType   = GS2CS_GUILDDONATEREQUESTREQ;
        header.stLength = sizeof( GS2CSGuildDonateRequestReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
};

struct CS2GSGuildDonateRequestReq : public MsgGuildModule
{
    CS2GSGuildDonateRequestReq()
    {
        header.dwType   = CS2GS_GUILDDONATEREQUESTREQ;
        header.stLength = sizeof( CS2GSGuildDonateRequestReq );
    }

    unsigned int nGuildID;
};

struct GS2CSGuildDonateAck : public MsgGuildModule
{
    GS2CSGuildDonateAck()
    {
        header.dwType   = GS2CS_GUILDDONATEACK;
        header.stLength = sizeof( GS2CSGuildDonateAck );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
    unsigned int nMoney;
};

struct GS2CSRaiseGuildPlayerItem : public MsgGuildModule
{
    GS2CSRaiseGuildPlayerItem()
    {
        header.dwType = GS2CS_RAISEGUILDPLAYERITEM;
        header.stLength = sizeof( GS2CSRaiseGuildPlayerItem );

		
    }
	uint32 ItemID;
	uint32 PlayerID;
	SCharItem CItem;
	char szName[dr_MaxPlayerName];
};

struct CS2GSGuildDonateStop : public MsgGuildModule
{
    CS2GSGuildDonateStop()
    {
        header.dwType   = CS2GS_GUILDDONATESTOP;
        header.stLength = sizeof( CS2GSGuildDonateStop );
    }

    unsigned int nGuildID;
};

struct GS2CSGuildQuestReleaseReq : public MsgGuildModule
{
    GS2CSGuildQuestReleaseReq()
    {
        header.dwType   = GS2CS_GUILDQUESTRELEASEREQ;
        header.stLength = sizeof( GS2CSGuildQuestReleaseReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    unsigned int nQuestType;
};

struct CS2GSGuildQuestReleaseStatus : public MsgGuildModule
{
    CS2GSGuildQuestReleaseStatus()
    {
        header.dwType   = CS2GS_GUILDQUESTRELEASESTATUS;
        header.stLength = sizeof( CS2GSGuildQuestReleaseStatus );
    }

    unsigned int nGuildID;
    unsigned int nQuestID;  // == 0 ��ʾ�������Ѿ�������
    __int64 n64RelasetTime;    
};

struct CS2GSGuildClearMemberActivity : public MsgGuildModule
{
    CS2GSGuildClearMemberActivity()
    {
        header.dwType   = CS2GS_GUILDCLEARMEMBERACTIVITY;
        header.stLength = sizeof( CS2GSGuildClearMemberActivity );
    }

    unsigned int nGuildID;
};

struct GS2CSGuildConveneReq : public MsgGuildModule
{
    GS2CSGuildConveneReq()
    {
        header.dwType   = GS2CS_GUILDCONVENEREQ;
        header.stLength = sizeof( GS2CSGuildConveneReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;     // �ټ���
    unsigned char uchLevel;     // ���ڵ����Ƶȼ�
    unsigned int nMapID;
    float fPosX;
    float fPosY;
    float fDir;
};

struct CS2GSGuildConveneReq : public MsgGuildModule
{
    CS2GSGuildConveneReq()
    {
        header.dwType   = CS2GS_GUILDCONVENEREQ;
        header.stLength = sizeof( CS2GSGuildConveneReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
    unsigned char uchLevel;
    unsigned int nMapID;
    float fPosX;
    float fPosY;
    float fDir;
};

struct CS2GSGuildConveneStop : public MsgGuildModule
{
    CS2GSGuildConveneStop()
    {
        header.dwType   = CS2GS_GUILDCONVENESTOP;
        header.stLength = sizeof( CS2GSGuildConveneStop );
    }

    unsigned int nGuildID;
};

struct GS2CSGuildMessage : public MsgGuildModule
{
    GS2CSGuildMessage()
    {
        header.dwType   = GS2CS_GUILDMESSAGE;
        header.stLength = sizeof( GS2CSGuildMessage ) - MaxLength;
        
        memset( szMessage, 0, sizeof( szMessage ) );
    }

    enum EConstDefine
    {
        MaxLength = 1024 * 32,
    };

    unsigned int nGuildID;
    unsigned int nExceptID;
    unsigned short ustLevel;   
    
    char szMessage[ MaxLength ];
    void AddMessage( void* pMessage, unsigned int nLength )
    {
        if ( pMessage == NULL || nLength > MaxLength )
        { return; }

        memcpy_s( szMessage, MaxLength, pMessage, nLength );

        header.stLength += nLength;
    }
};

struct CS2GSGuildMessage : public MsgGuildModule
{
    CS2GSGuildMessage()
    {
        header.dwType   = CS2GS_GUILDMESSAGE;
        header.stLength = sizeof( CS2GSGuildMessage ) - MaxLength;

        memset( szMessage, 0, sizeof( szMessage ) );
    }

    enum EConstDefine
    {
        MaxLength = 1024 * 32,
    };

    unsigned int nGuildID;
    unsigned int nExceptID;
    unsigned short ustLevel;   

    char szMessage[ MaxLength ];
    void AddMessage( void* pMessage, unsigned int nLength )
    {
        if ( pMessage == NULL || nLength > MaxLength )
        { return; }

        memcpy_s( szMessage, MaxLength, pMessage, nLength );

        header.stLength += nLength;
    }
};

//luo.qin 4.20
struct GS2CSPlayerLvUpToThirtyMessage : public MsgGuildModule
{
	GS2CSPlayerLvUpToThirtyMessage()
	{
		header.dwType   = GS2CS_PLAYERLVUPTOTHIRTY;
		header.stLength = sizeof( GS2CSPlayerLvUpToThirtyMessage );
	}

	unsigned int nPlayerID;
	unsigned int nTargetID;
	unsigned int nPlayerLv;
	char szSpeakName[dr_MaxPlayerName]; 
};
struct CS2GSMissionNotEnuoughMessage : public MsgGuildModule
{
	CS2GSMissionNotEnuoughMessage()
	{
		header.dwType   = CS2GS_MISSIONNOTENOUGH;
		header.stLength = sizeof( CS2GSMissionNotEnuoughMessage );
	}
	unsigned int nMissionCount;
	unsigned int nMasterID;

};


struct CS2GSGuildBattleSum : public MsgGuildModule
{
    CS2GSGuildBattleSum()
    {
        header.dwType   = CS2GS_GUILDBATTLESUM;
        header.stLength = sizeof( CS2GSGuildBattleSum );
    }

    unsigned int nGuildID;
	unsigned int battleSum;
};


struct MsgSetGuildCampBattleValue : public MsgGuildModule
{
    MsgSetGuildCampBattleValue()
    {
        header.dwType   = MSG_SETGUILDCAMPBATTLEVALUE;
        header.stLength = sizeof( MsgSetGuildCampBattleValue );
    }
	
	unsigned int TargetID;//Ŀ��ID
	unsigned int CampBattleValue;//��Ҫ���õ�ֵ
	bool		 IsAdd;
};

struct MsgSetGuildCampBattleValueAck : public MsgGuildModule
{
    MsgSetGuildCampBattleValueAck()
    {
        header.dwType   = MSG_SETGUILDCAMPBATTLEVALUEACK;
        header.stLength = sizeof( MsgSetGuildCampBattleValueAck );
    }
	
	unsigned int PlayerID;
	unsigned int ErrorID;//������Ϣ
};

struct GS2CSSetGuildCampBattleValue : public MsgGuildModule
{
    GS2CSSetGuildCampBattleValue()
    {
        header.dwType   = GS2CS_SETGUILDCAMPBATTLEVALUE;
        header.stLength = sizeof( GS2CSSetGuildCampBattleValue );
    }
	unsigned int GuildID;
	unsigned int PlayerID;
	unsigned int TargetID;//Ŀ��ID
	unsigned int CampBattleValue;//��Ҫ���õ�ֵ
	bool		 IsAdd;
};

struct MsgChangeGuldNameReq : public MsgGuildModule
{
	MsgChangeGuldNameReq()
    {
        header.dwType   = MSG_CHANGEGUILDNAMEREQ;
        header.stLength = sizeof( MsgChangeGuldNameReq );
    }
	unsigned int GuildID;
	char	Name[ GuildDefine::MaxNameLength ];
};

struct GS2CSChangeGuildNameReq : public MsgGuildModule
{
	GS2CSChangeGuildNameReq()
    {
        header.dwType   =  GS2CS_CHANGEGUILDNAMEREQ;
        header.stLength = sizeof( GS2CSChangeGuildNameReq );
    }
	unsigned int GuildID;
	unsigned int PlayerID;
	char	Name[ GuildDefine::MaxNameLength ];
};
struct CS2GSChangeGuildNameAck : public MsgGuildModule
{
	CS2GSChangeGuildNameAck()
    {
        header.dwType   =  CS2GS_CHANGEGUILDNAMEACK;
        header.stLength = sizeof( CS2GSChangeGuildNameAck );
    }
	unsigned int GuildID;
	char	Name[ GuildDefine::MaxNameLength ];
};
struct MsgChangeGuldNameAck : public MsgGuildModule
{
	MsgChangeGuldNameAck()
    {
        header.dwType   = MSG_CHANGEGUILDNAMEACK;
        header.stLength = sizeof( MsgChangeGuldNameAck );
    }
	unsigned int GuildID;
	bool	IsCanChange;
	char	Name[ GuildDefine::MaxNameLength ];
};
struct MsgTellGuildPlayerRaiseItem : public MsgGuildModule
{
	MsgTellGuildPlayerRaiseItem()
    {
        header.dwType   = MSG_TELLGUILDPLAYERAISEITEM;
        header.stLength = sizeof( MsgTellGuildPlayerRaiseItem );
    }
	char	szName[ GuildDefine::MaxNameLength ];
	unsigned short CountryID;
};

struct GS2CSGuildMemberChangeName : public MsgGuildModule
{
    GS2CSGuildMemberChangeName()
    {
        header.dwType = GS2CS_GUILDMEMBERCHANGENAME;
        header.stLength = sizeof( GS2CSGuildMemberChangeName );
    }
    int   PlayerID;
	char  szName[dr_MaxUserName];
	int	  GuildID;
};
struct CS2GSGuildMemberChangeName : public MsgGuildModule
{
    CS2GSGuildMemberChangeName()
    {
        header.dwType = CS2GS_GUILDMEMBERCHANGENAME;
        header.stLength = sizeof( CS2GSGuildMemberChangeName );
    }
    int   PlayerID;
	char  szName[dr_MaxUserName];
	int	  GuildID;
};
struct MsgGuildChangeNameAck : public MsgGuildModule
{
    MsgGuildChangeNameAck()
    {
        header.dwType = MSG_GUILDCHANGENAMEACK;
        header.stLength = sizeof( MsgGuildChangeNameAck );
    }
    int   PlayerID;
	char  szName[dr_MaxUserName];
	int	  GuildID;
};
struct GS2CSUpdateGuildCampBattlePoint : public MsgGuildModule
{
    GS2CSUpdateGuildCampBattlePoint()
    {
        header.dwType = GS2CS_UPDATEGUILDCAMPBATTLEPOINT;
        header.stLength = sizeof( GS2CSUpdateGuildCampBattlePoint );
    }
    unsigned int GuildID;
	unsigned int Point;
};

struct GS2CSUpdateGuildMemberOnLineTime : public MsgGuildModule
{
    GS2CSUpdateGuildMemberOnLineTime()
    {
        header.dwType = GS2CS_UPDATEGUILDMEMBERONLINETIME;
        header.stLength = sizeof( GS2CSUpdateGuildMemberOnLineTime );
    }
    unsigned int GuildID;
	unsigned int PlayerID;
	__int64 OnLineTime;
};
struct CS2GSUpdateGuildMemberOnLineTime : public MsgGuildModule
{
    CS2GSUpdateGuildMemberOnLineTime()
    {
        header.dwType = CS2GS_UPDATEGUILDMEMBERONLINETIME;
        header.stLength = sizeof( CS2GSUpdateGuildMemberOnLineTime );
    }
    unsigned int GuildID;
	unsigned int PlayerID;
	__int64 OnLineTime;
};
struct MsgUpdateGuildMemberOnLineTime : public MsgGuildModule
{
    MsgUpdateGuildMemberOnLineTime()
    {
        header.dwType = MSG_UPDATEGUILDMEMBERONLINETIME;
        header.stLength = sizeof( MsgUpdateGuildMemberOnLineTime );
    }
    unsigned int GuildID;
	unsigned int PlayerID;
	__int64 OnLineTime;
};

#pragma pack( pop )

#endif