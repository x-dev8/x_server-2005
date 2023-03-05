#ifndef __CENTERGAMEMESSAGE_H__
#define __CENTERGAMEMESSAGE_H__

#pragma once

#include "MsgBase.h"
//#include "MessageDefine.h"
#include "GameDataType.h"
#include "PlatformMessageDefine.h"

#pragma pack( push, 1 ) 

enum CenterServerGameServerMessage
{
    GS2CS_REGISTERGAMESERVERINFO_REQ = CENTERGAME_MESSAGE_BEGIN, // ע����Ϸ����������
    CS2GS_REGISTERGAMESERVERINFO_ACK,                            // ע����Ϸ������Ӧ��

    UPDATEMAPINFO,                    // ������Ϸ��������ͼ��Ϣ��˫��

    CS2GS_LOGININFO,                  // ��½��Ϣ
    S2S_SWITCHGATE,                   // �л�GateServer��Ϣ
    GS2CS_SWITCHSTAGEREQ,             // �г�������
    CS2GS_SWITCHSTAGEACK,             // �г�����Ӧ
	GS2CS_CREATEMULITSTAGEREQ,
	GS2CS_CREATEMULITSTAGEACK,
                                    
    GS2CS_PLAYEREXITGAMESERVER,       // ����뿪GameServer
    GS2CS_PLAYERSYNINSERVERINFO,      // ��ҽ���GameServer
                                    
    GS2CS_PLAYERCREATETEAMREQ,        // ������󴴽�����
    GS2CS_PLAYERCREATETEAMACK,      
    GS2CS_PLAYERTEAMINVITEEREQ,       // �������ĳĳ�������
    GS2CS_PLAYERTEAMINVITEEACK,       // ��һ�Ӧ������
    GS2CS_PLAYERADDTEAMMEMBERREQ,     // ��Ҽ������
    GS2CS_PLAYERDELETETEAMMEMBER,
    GS2CS_PLAYERUPDATETEAMMEMBERINFO,
    GS2CS_PLAYERREMOVEFROMTEAMREQ,
    GS2CS_PLAYERREMOVEFROMTEAMACK,
    GS2CS_PLAYERTEAMINFOREQ,
    GS2CS_PLAYERTEAMINFOACK,
    GS2CS_PLAYERUPGRADETEAMREQ,
    GS2CS_PLAYERUPGRADETEAMACK,
    GS2CS_PLAYERCHATMESSAGE,          // ������Ϣ
    GS2CS_QUERYPLAYERINFOREQ,
    GS2CS_QUERYPLAYERINFOACK,
    GS2CS_TRANSMIT,                   // ��Ϣת��
    S2S_TRANSMIT_RESULT,              // ��Ϣת�����

    CS2GS_PLAYERJOINTEAM,               // ��Ҽ������
    CS2GS_PLAYEREXITTEAM,               // ����˳�����
    CS2GS_TEAMOUTLINE,                  // �������
    GS2CS_TEAMCHANGEASSIGNMODEREQ,      // �����������ģʽ
    CS2GS_TEAMCHANGEASSIGNMODEACK,      // ��Ӧ��������ģʽ
    GS2CS_TEAMCHANGEASSIGNITEMLEVELREQ, // �������������Ʒ����ȼ�
    CS2GS_TEAMCHANGEASSIGNITEMLEVELACK, // ��Ӧ����������Ʒ����ȼ�

    S2S_NOTIFYTIMEEVENT,                    // ʱ�伤��֪ͨ
    S2S_CHANGEEXP,                          // ͬ��������

    S2S_ANTIADDICTIONACCOUNTINFO,           // �˺�������Ϣ
    S2S_NOTIYANTIADDICTIONTIMEINFO,         // ֪ͨ��Ϸ�����������ԵĽ׶�ʱ��

    GS2GS_BANSPEAK,                         // ����
    GS2GS_CALLPALYER,                       // �������
    CS2GS_CREATETEAM,                       // ��������

    GS2CS_DRAWFROMPLATFORM_QUERY,         // ��ȡ��������
    CS2GS_DRAWFROMPLATFORM_ACK,           // ��ȡ��������

    S2S_CALL_GRAPHIC,                     // ���������֤��

    CS2GS_SETCHECKCHEATOPEN,              // ������Ҽ�⿪��

    S2S_UPDATEDROPITEMCONTROL,            // ������Ʒ������ֵ����
    GS2CS_TEAMONLINE,

    CS2GSMSGBORNMAPOPERATE,

//    GS2CS_MONEYITEMEXCHANGE,               // ʵ��һ�
    MSG_CHANGEMAPCALLBACK,                 // �л���ͼ�ص���Ϣ
    S2S_UPDATETRADESHOPCONFIG,             // ���½��̳������ļ�

    S2S_SHUTDOWNSERVER,                    // �رշ�����
    S2S_CHANGEMAPEXPRATE,                  // �ı��ͼ�������

    GS2CS_MAILLISTREQ,                     // �����ʼ��б�
    CS2GS_MAILLISTACK,                     // �����ʼ��б�
    GS2CS_SENDMAILREQ,                     // �����ʼ�
    CS2GS_SENDMAILACK,                     // �������ʼ�
    GS2CS_OPMAILREQ,                       // �ʼ�����
    CS2GS_OPMAILACK,                       // �ʼ���������

    GS2CS_QUERYMAILCANSENDREQ,             // ��ѯ�ʼ��Ƿ���Է���
    CS2GS_QUERYMAILCANSENDACK,             // �����ʼ��Ƿ���Է���
    S2S_REMOTEBANREQ,                      // Զ��Ban����
	S2S_DleteCountryBattleReward,			//����վ����ɾ��
    CS2GSLOADFRESOURCESUCCESS,

    CS2DB_ITEMDROPCONTROLREQ,       // ������Ʒ������ֵ���
    DB2CS_ITEMDROPCONTROL,
    CS2GS_ITEMDROPCONTROL,
    CS2DB_SAVEITEMDROPCONTROL,
    CS2GS_UPDATECOUNTRYONLINECOUNT,

    //***********************************************�޵зָ���**
    MSG_PARTITIONLOGFILE,

    CS2GS_OPRECORDCHATONOFF,     // �Ƿ�������¼����
    S2S_RECORDCHATCONTENT,       // �ϴ���������
    CS2GS_REWARDOPERATE,         // ȫ������

	GS2CS_CREATETEAM,			// �������˶���
	GS2CS_DISBANDTEAM,			// ��ɢ����
	GS2CS_DISBANDTEAMACK,		// ��ɢ����ظ�

	GS2CS_UPDATEANTIADDICTIONINFOREQ, // ���·�������Ϣ����
	CS2GS_UPDATEANTIADDICTIONINFOACK, // ���·�������Ϣ����
	CS2GS_PING,
	CS2LS_LOGIN_ERROR,               //��¼ʧ��
	CS2GS_QUEUE_OP,                  //�Ŷӿ�������
	GS2CS_REQ_EPISTARPOINT,          //������Ӿ�Ԫ��
	CS2GS_CHARREMOVEITEMBYID,        //��gs��ĳ�����ɾ���ض�id����Ʒ
	CS2GS_UPDATEARELOADCONFIG,		 //��GS���¼���ָ�������ļ�
    // ����������Ϸ�߼�Э����������� �����GM��
    CS2GS_GMBROATCAST_REQ  = CENTERGAME_MESSAGE_BEGIN + 1000,
    CS2GS_GMKICKPLAYER_REQ,
	CS2GS_PLATFORMSENDMAILREQ,        //platform�������ʼ�,Ҫ��game server������Ʒ��Ϣ
	CS2GS_PLATFORMSENDMAILACK,        //game server���ط���
	GS2CS_ASKFORPRESENT,              //��CENTER SERVER����������Ʒ
	GS2CS_ASKFORPLATFORMACTIVITY,     //��CENTER SERVER��������ƽ̨�

	CS2GS_ASKBROADCAST,				  //��game server���󹫸津����Ϣ
	GS2CS_ASKBROADCAST_ACK,			  //��center server���ع��津����Ϣ

	S2S_BlockAccount,				  //���ʺ�
	S2S_BlockMacAddress,		      //��mac ֻ����Ӫ��

	CS2GS_TEAMSTATECHANGE,
};

struct GS2CSRegiseterGameServerInfoReq : public Msg
{   
    GS2CSRegiseterGameServerInfoReq()
    {
        header.dwType = GS2CS_REGISTERGAMESERVERINFO_REQ;
        header.stLength = sizeof( GS2CSRegiseterGameServerInfoReq );
        Reset();
    }
    
    enum RegisterOpType
    {
        ROT_NOT_REPLACE,
        ROT_REPLACE,
		ROT_LOOP,//ѭ��ע�� һֱ��ע����Ϊֹ
    };

    void Reset()
    {
        memset( szGameServerName, 0, sizeof(szGameServerName));
        btReset = ROT_NOT_REPLACE;
        nServerId = 0;
    }

    char szGameServerName[32];
    unsigned long nServerId;
    char btReset;
};

struct CS2GSRegiseterGameserverInfoAck : public Msg
{
    CS2GSRegiseterGameserverInfoAck()
    {
        header.dwType = CS2GS_REGISTERGAMESERVERINFO_ACK;
        header.stLength = sizeof( CS2GSRegiseterGameserverInfoAck );
    }   
    
    unsigned short nResult;
};

struct MessageUpdateMapInfo : public Msg
{
    enum EConstDefine
    {
        PerMessageGameStageMaxCount = 20,
    };

    MessageUpdateMapInfo()
    {
        header.dwType   = UPDATEMAPINFO;
        header.stLength = 0;
        Reset();
    }

    void Reset()
    {
        memset( szGameStageOp, 0, sizeof(szGameStageOp));
        szGameStageCount = 0;
    }

    bool AddStageOp( const SGameStageOp& gs )
    {
        if ( szGameStageCount >= PerMessageGameStageMaxCount)
            return false;

        szGameStageOp[szGameStageCount] = gs;
        ++szGameStageCount;

        header.stLength = sizeof(*this) - sizeof(SGameStageOp) * ( PerMessageGameStageMaxCount - szGameStageCount);
        return true;
    }
    
    SGameStageOp* GetStageOp( int nIndex )
    {
        if ( nIndex >= szGameStageCount || nIndex >= PerMessageGameStageMaxCount )
            return NULL;
        
        return &(szGameStageOp[nIndex]);
    }
    
    char szGameStageCount;
    SGameStageOp szGameStageOp[PerMessageGameStageMaxCount];
};

struct CS2GSLoginInfo : public MsgLoginInfo
{
    CS2GSLoginInfo ()
    {
        header.dwType = CS2GS_LOGININFO;
        header.stLength = sizeof(CS2GSLoginInfo);
    }
    char          clientPeerInServerType;
    unsigned long nServerId; 
};

struct S2SSwitchGate : public MsgSwitchGate
{
    S2SSwitchGate()
    {
        header.dwType = S2S_SWITCHGATE;
        header.stLength = sizeof(S2SSwitchGate );
    }
    char          nSourcePeerInServerType; // ClientPeer���ڷ���������
    char          nTargetServerType;       // ��Ŀ�����������
    unsigned long nTargetServerId;         // ��Ŀ��Ŀ�������Id
    unsigned long nAccountId;              // �˺�Id
    unsigned long dwMapID;
    float fX;
    float fY;
    float fDir;
};

struct GS2CSSwitchStageReq : public Msg
{
    GS2CSSwitchStageReq()
    {
        header.dwType = GS2CS_SWITCHSTAGEREQ;
        header.stLength = sizeof(GS2CSSwitchStageReq);
        ustCountryID = 0;
    }
    
    char          nSwitchStageType;
    unsigned long nAccountId;
    unsigned long nCharacterDbId;
    short         stWhichSlot;
    unsigned long nMapId;
    unsigned long nSessionId;
    float         fX;
    float         fY;
    float         fDir;
    unsigned long dwTime;
    unsigned long nServerId;
    short         ustCountryID;
	unsigned long nTargetServerId;
};


struct GS2CSCreateMulitStageReq : public Msg
{
    GS2CSCreateMulitStageReq()
    {
        header.dwType = GS2CS_CREATEMULITSTAGEREQ;
        header.stLength = sizeof(GS2CSCreateMulitStageReq);
    }
	//��GameServer�������� ���ҷ���ֵ
	uint32		PlayerDBID;
	uint32		MapID;
	uint32		EctypeMapID;
	float		x;
	float		y;
	float		dir;
	unsigned short Level;
	uint32		ReserveValue;
	long		GameServerID;
};

struct GS2CSCreateMulitStageAck : public Msg
{
    GS2CSCreateMulitStageAck()
    {
        header.dwType = GS2CS_CREATEMULITSTAGEACK;
        header.stLength = sizeof(GS2CSCreateMulitStageAck);
		ErrorID = 0;
    }
	//��GameServer�������� ���ҷ���ֵ
	uint32		PlayerDBID;
	bool		Result;
	uint32		ErrorID;
	long		GameServerID;
	uint32		MapID;
	float		x;
	float		y;
	float		dir;
};



struct CS2GSSwitchStageAck : public Msg
{
    CS2GSSwitchStageAck ()
    {
        header.dwType = CS2GS_SWITCHSTAGEACK;
        header.stLength = sizeof(CS2GSSwitchStageAck);
        ucNeedTellClientCharInfo = BV_NotNeedTellClientCharInfo;
        ucNeedUseMessageMapInfo  = BV_NotNeedUseMessageMapInfo;
        ucIsLocalFlyMap          = BV_NotLocalFlyMap;
        dwTeamSessionId          = 0;
    }

    short         nResult;    
    unsigned long nAccountId;
    unsigned long nCharDBId;
    short         stWhichSlot;
    DWORD         dwTime;
    unsigned long nMapId;
    float         fX;
    float         fY;
    float         fDir;
    unsigned char ucNeedTellClientCharInfo; // �Ƿ�Ҫ���߿ͻ��˽�ɫ����      ��ֻ�е�һ��ʱ�򷢡�
    unsigned char ucNeedUseMessageMapInfo;  // �Ƿ�Ҫʹ�ô���Ϣ�д��ĵ�ͼ��Ϣ���з����ߵ�ͼ��������
    unsigned char ucIsLocalFlyMap;          // �Ƿ��ǵ�ǰ�������е�ͼ
    unsigned long dwTeamSessionId;            // ����Ψһ�Ķ���id
};

struct GS2CSPlayerExit : public Msg
{
    GS2CSPlayerExit()
    {
        header.dwType   = GS2CS_PLAYEREXITGAMESERVER;
        header.stLength = sizeof(GS2CSPlayerExit);
        cExitType       = ET_ExitGame;
		blockTime		= 0;
        //memset( szSessionKey, 0, sizeof(szSessionKey) );
		SessionKey = 0;
    }

    uint32 nAccountId;         // �ʺ�Id
    uint32 dwDBID;             // ��ɫdbId
    uint8  cExitType;          // �˳�����
    uint32 blockTime;          // ��Ҫblock��ʱ��
    //int8   szSessionKey[32+1]; // ��½��
	__int64 SessionKey;
};

struct GS2CSPlayerSynInServerInfo : public Msg
{ // ͬ����������ڷ���������Ϣ (���ĸ����������ŵ�ͼ�ĸ�λ�ø�ʲô)
    enum EStatus
    {
        ES_None,
        ES_InServerLoginStage, // ��GameServer����Character��LoginStage��
        ES_FirstInMapStagePlaying,  // ��һ����GameServer��MapStage����Ϸ
        ES_InMapStagePlaying,  // ��GameServer��MapStage����Ϸ
		ES_OfflineStall,	// ���߰�̯��
    };

    GS2CSPlayerSynInServerInfo()
    {
        header.dwType   = GS2CS_PLAYERSYNINSERVERINFO;
        header.stLength = sizeof(GS2CSPlayerSynInServerInfo);
    
        nAccountId     = 0;
        nCharacterDbId = 0;
        memset( &serverInfo, 0, sizeof(SServerInfo) );
        memset( szCharacterName, 0, sizeof(szCharacterName));
        ucStatus       = ES_None;
    }
    unsigned long nAccountId;
    unsigned long nCharacterDbId;
    unsigned char uchCountry;
    char          szCharacterName[dr_MaxPlayerName];
    SServerInfo   serverInfo; // ��������Ϣ
    unsigned char ucStatus;   // ״̬
};


struct CS2GSCreateTeam : public Msg
{
    CS2GSCreateTeam()
    {
        header.dwType = CS2GS_CREATETEAM;
        header.stLength = sizeof(CS2GSCreateTeam);
    }

    uint32 dwTeamSessionID;       // ����SessionID
    uint8 AssignMode;			  // �������ģʽ
    uint8 AssignItemLevel;        // ������Ʒ�ķ���ȼ�
};

struct CS2GSAckJoinTeam : public Msg
{
    CS2GSAckJoinTeam()
    {
        header.dwType = CS2GS_PLAYERJOINTEAM;
        header.stLength = sizeof(CS2GSAckJoinTeam);
        bIsTeamHeader = false;
    }

    uint32 dwTeamSessionID;               // ����sessionid
    uint32 dwDataBaseID;                  // ����Ķ�ԱID
    char szName[dr_MaxPlayerName];        // �����Ա������
    int nHp;                              // �������ʱ��HP
    int nMp;                              // �������ʱ��MP 
    int nHpMax;                           // �������ʱ�����HP
    int nMpMax;                           // �������ʱ�����MP
    short stLevel;                        // �������ʱ�ĵȼ�
    uint8 chProfession;                   // ְҵ 
    uint8 chSex;                          // �Ա�
    int nFaceId;                          // Ԥ��������Id
    int nHairId;                          // ͷ��ID
    int nHeadPicId;                       // ͷ��ID

    bool bIsTeamHeader;                   // �Ƿ��Ƕӳ�
    short stManipleID;                    // С��ID
    bool bIsManipleHeader;                // �Ƿ���С�ӳ�

    uint8 chAssignModeType;
    uint8 chAssignItemLevel;      
};

struct CS2GSExitTeam : public Msg
{
    CS2GSExitTeam()
    {
        header.dwType = CS2GS_PLAYEREXITTEAM;
        header.stLength = sizeof(CS2GSExitTeam);
    }

    uint32 dwDataBaseID;
    uint32 dwTeamSessionID;
};

// �������˶���
struct GS2CSCreateTeam : public Msg
{
	GS2CSCreateTeam()
	{
		header.dwType = GS2CS_CREATETEAM;
		header.stLength = sizeof(GS2CSCreateTeam);

		dwReqID = 0;
		memset(szReqName, 0, sizeof(szReqName));
		AssignMode = 0;
		AssignItemLevel = 0;
	}

	uint8 uchCountry;                     // �����߹���
	unsigned long dwReqID;                // �����ߵ�id
	char szReqName[dr_MaxPlayerName];     // ����������
	int nHp;                              // �������ʱ��HP
	int nMp;                              // �������ʱ��MP 
	int nHpMax;                           // �������ʱ�����HP
	int nMpMax;                           // �������ʱ�����MP
	short stLevel;                        // �������ʱ�ĵȼ�
	uint8 chProfession;                   // ְҵ 
	uint8 chSex;                          // �Ա�
	int nFaceId;                          // Ԥ��������Id
	int nHairId;                          // ͷ��ID
	int nHeadPicId;                       // ͷ��ID

	uint8 AssignMode;
	uint8 AssignItemLevel;           // �������ȼ�
};

struct GS2CSPlayerTeamInviteeReq : public Msg
{
    GS2CSPlayerTeamInviteeReq()
    {
        header.dwType = GS2CS_PLAYERTEAMINVITEEREQ;
        header.stLength = sizeof(GS2CSPlayerTeamInviteeReq);
        memset(szReqName, 0, sizeof(szReqName));
        memset(szAckName, 0, sizeof(szAckName));

        AssignMode = 0;
        nFaceId = 0;
    }

    char szAckName[dr_MaxPlayerName];     // ������������
    
    uint8 uchCountry;                     // �����߹���
    unsigned long dwReqID;                // �����ߵ�id
    char szReqName[dr_MaxPlayerName];     // ����������
    int nHp;                              // �������ʱ��HP
    int nMp;                              // �������ʱ��MP 
    int nHpMax;                           // �������ʱ�����HP
    int nMpMax;                           // �������ʱ�����MP
    short stLevel;                        // �������ʱ�ĵȼ�
    uint8 chProfession;                   // ְҵ 
    uint8 chSex;                          // �Ա�
    int nFaceId;                          // Ԥ��������Id
    int nHairId;                          // ͷ��ID
    int nHeadPicId;                       // ͷ��ID

	bool countryTeam;					  // �Ƿ���Ժ��Թ��ҵ��ж�
    
	uint8 AssignMode;			  // �������ģʽ
    uint8 AssignItemLevel;        // ������Ʒ�ķ���ȼ�
};

struct CS2GSTeamStateChange : public Msg
{
	CS2GSTeamStateChange()
    {
        header.dwType = CS2GS_TEAMSTATECHANGE;
        header.stLength = sizeof(CS2GSTeamStateChange);
    }

	unsigned int TeamID;
	bool Result;
};

struct GS2CSPlayerTeamInviteeAck : public Msg
{
    GS2CSPlayerTeamInviteeAck()
    {
        header.dwType = GS2CS_PLAYERTEAMINVITEEACK;
        header.stLength = sizeof(GS2CSPlayerTeamInviteeAck);
        memset(szAckName,0, sizeof(szAckName));
    }
    
    unsigned long dwReqID;
    unsigned long dwAckID;
    char szAckName[dr_MaxPlayerName];        //�������ߵ�����
    int nHp;                              // �������ʱ��HP
    int nMp;                              // �������ʱ��MP 
    int nHpMax;                           // �������ʱ�����HP
    int nMpMax;                           // �������ʱ�����MP
    short stLevel;                        // �������ʱ�ĵȼ�
    uint8 chProfession;                   // ְҵ 
    uint8 chSex;                          // �Ա�
    int nFaceId;                          // Ԥ��������Id
    int nHairId;                          // ͷ��ID
    int nHeadPicId;                       // ͷ��ID
    unsigned char AssignMode;             //�������ģʽ
    unsigned char AssignItemLevel;
	uint8 bAgree;						  // �Ƿ�ͬ��
};

struct GS2CSTeamOnLine : public Msg
{
    GS2CSTeamOnLine()
    {
        header.dwType = GS2CS_TEAMONLINE;
        header.stLength = sizeof( GS2CSTeamOnLine );
    }
    uint32 dwID;
};

struct CS2GSMsgTeamOutLine : public Msg
{
    CS2GSMsgTeamOutLine()
    {
        header.dwType = CS2GS_TEAMOUTLINE;
        header.stLength = sizeof(CS2GSMsgTeamOutLine);
    }

    DWORD dwID;
    DWORD dwTeamSessionID;
};

struct GS2CSPlayerUpdateTeamMemberInfo : public Msg
{
    GS2CSPlayerUpdateTeamMemberInfo()
    {
        header.dwType = GS2CS_PLAYERUPDATETEAMMEMBERINFO;
        header.stLength = sizeof(GS2CSPlayerUpdateTeamMemberInfo);
        memset( szName, 0, sizeof( szName ) );
    }

    unsigned long dwSessionId;
    unsigned long dwDataBaseId;
    int nHp; 
    int nHpMax;
    int nMp;
    int nMpMax;    
    unsigned char Profession;
    short stLevel;
    DWORD dwMapID;
    short x;                //��������
    short y;
    float fx;
    float fy;
    short stManiple;
    bool bManipleHeader;            //С�Ӷӳ�
    bool bTeamHeader;
    short stSex;
    int nFaceID;
    int nHairID;
    int nHeadPicId;
    char szName[dr_MaxPlayerName];
};

struct GS2CSPlayerRemoveFromTeamReq : public Msg
{
    GS2CSPlayerRemoveFromTeamReq()
    {
        header.dwType = GS2CS_PLAYERREMOVEFROMTEAMREQ;
        header.stLength = sizeof(GS2CSPlayerRemoveFromTeamReq);
    }
    unsigned long dwSessionId;
    unsigned long dwDataBaseId;         // -1 ���������ɢ��������
    bool bKick;                    //�Ƿ�Ҫ�ߵ���
};

struct GS2CSPlayerRemoveFromTeamAck : public Msg
{
    GS2CSPlayerRemoveFromTeamAck()
    {
        header.dwType = GS2CS_PLAYERREMOVEFROMTEAMACK;
        header.stLength = sizeof(GS2CSPlayerRemoveFromTeamAck);

        bDisband = false;
    }
    unsigned long dwSessionId;
    unsigned long dwDataBaseId;
    bool bDisband;              // �Ƿ��ɢ
};

// ��ɢ����
struct GS2CSPlayerDisbandTeam : public Msg
{
	GS2CSPlayerDisbandTeam()
	{
		header.dwType = GS2CS_DISBANDTEAM;
		header.stLength = sizeof( GS2CSPlayerDisbandTeam );

		dwDataBaseID = 0;
		dwTeamSessionID = 0;
	}

	uint32 dwDataBaseID;
	uint32 dwTeamSessionID;
};

struct GS2CSPlayerDisbandTeamAck : public Msg
{
	GS2CSPlayerDisbandTeamAck()
	{
		header.dwType = GS2CS_DISBANDTEAMACK;
		header.stLength = sizeof( GS2CSPlayerDisbandTeamAck );

		dwDataBaseID = 0;
		dwTeamSessionID = 0;
	}

	uint32 dwDataBaseID;
	uint32 dwTeamSessionID;
};

struct GS2CSPlayerUpgradeTeamReq : public Msg
{
    GS2CSPlayerUpgradeTeamReq()
    {
        header.dwType = GS2CS_PLAYERUPGRADETEAMREQ;
        header.stLength = sizeof(GS2CSPlayerUpgradeTeamReq);
    }

    DWORD dwSessionId;              
    DWORD dwDataBaseId;             //��ĳ������Ϊ�ӳ�
};

struct GS2CSPlayerUpgradeTeamAck : public Msg
{
    GS2CSPlayerUpgradeTeamAck()
    {
        header.dwType = GS2CS_PLAYERUPGRADETEAMACK;
        header.stLength = sizeof(GS2CSPlayerUpgradeTeamAck);
        memset(szName, 0, sizeof(szName));
    }

    DWORD dwSessionId;              
    DWORD dwDataBaseId;             //��ĳ������Ϊ�ӳ�
    char szName[dr_MaxPlayerName];
};


//GS2CS_TEAMCHANGEASSIGNMODEREQ,                                  // �����������ģʽ
//CS2GS_TEAMCHANGEASSIGNMODEACK,                                  // ��Ӧ��������ģʽ
//GS2CS_TEAMCHANGEASSIGNITEMLEVELREQ,                             // �������������Ʒ����ȼ�
//CS2GS_TEAMCHANGEASSIGNITEMLEVELACK,                             // ��Ӧ����������Ʒ����ȼ�

struct GS2CSTeamChangeAssignModeReq : public Msg
{
    GS2CSTeamChangeAssignModeReq()
    {
        header.dwType = GS2CS_TEAMCHANGEASSIGNMODEREQ;
        header.stLength = sizeof(*this);
    }

    uint32 dwTeamSessionID;                 // ����sessionid
    uint32 dwTeamHeaderID;                  // �ӳ�id            
    uint8 chAssignMode;                     // Ҫ�ı�ķ���ģʽ
};

struct CS2GSTeamChangeAssignModeAck : public Msg
{
    CS2GSTeamChangeAssignModeAck()
    {
        header.dwType = CS2GS_TEAMCHANGEASSIGNMODEACK;
        header.stLength = sizeof(*this);
    }

    uint32 dwTeamSessionID;                 // ����sessionid
    uint8 chAssignMode;                     // ����ģʽ
};

struct GS2CSTeamChangeAssignItemLevelReq : public Msg
{
    GS2CSTeamChangeAssignItemLevelReq()
    {
        header.dwType = GS2CS_TEAMCHANGEASSIGNITEMLEVELREQ;
        header.stLength = sizeof(*this);
    }

    uint32 dwTeamSessionID;                 // ����sessionid
    uint32 dwTeamHeaderID;                  // �ӳ�id            
    uint8 chAssignItemLevlel;               // Ҫ�ı����Ʒ����ȼ�
};

struct CS2GSTeamChangeAssignItemLevelAck : public Msg
{
    CS2GSTeamChangeAssignItemLevelAck()
    {
        header.dwType = CS2GS_TEAMCHANGEASSIGNITEMLEVELACK;
        header.stLength = sizeof(*this);
    }

    uint32 dwTeamSessionID;                 // ����sessionid
    uint8 chAssignItemLevel;               // ��Ʒ����ȼ�
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
struct GS2GSBanSpeak : public Msg
{
    GS2GSBanSpeak()
    {
        header.dwType = GS2GS_BANSPEAK;
        header.stLength = sizeof(GS2GSBanSpeak);
        memset(szName, 0, sizeof(szName));
        dwDBID = InvalidLogicNumber;
    }

    uint32 dwBanTime;                   // ����ʱ��
    char  szName[dr_MaxPlayerName];     // ���ԵĶ���
    uint32 dwDBID;                      // �������
};

struct GS2GSCallPlayer : public Msg
{
    GS2GSCallPlayer()
    {
        header.dwType = GS2GS_CALLPALYER;
        header.stLength = sizeof(GS2GSCallPlayer);
        memset(szName, 0, sizeof(szName));
    }

    char  szName[dr_MaxPlayerName];     // ���ԵĶ���
    uint32 dwMapID;
    float fX;
    float fY;
    float fDir;
};

struct GS2CSPlayerChatMessage : public Msg
{
    //enum EConstDefine
    //{
    //    BUFFER_SIZE = 1536,
    //};

    GS2CSPlayerChatMessage()
    {
        header.dwType = GS2CS_PLAYERCHATMESSAGE;
        header.stLength = sizeof(GS2CSPlayerChatMessage);
        memset(szBuf, 0, sizeof(szBuf));
    }

    uint32 dwRecvID;                // ������ID
    char szBuf[ dr_MaxChatString ];      // ��Ϣ����
};

/////////////////////////////////////////////////////////////////////////////////
struct GS2CSQueryPlayerInfoReq : public Msg
{
    GS2CSQueryPlayerInfoReq()
    {
        header.dwType = GS2CS_QUERYPLAYERINFOREQ;
        header.stLength = sizeof(GS2CSQueryPlayerInfoReq);

        memset(szAckName, 0, sizeof(szAckName));
    }

    enum ActionType
    {
        Action_FlyToPlayer = 0,
        Action_ItemFlyToPlayer,
    };

    DWORD dwReqID;                  //������
    DWORD dwAckID;                  //������
    char szAckName[dr_MaxPlayerName];       //������������

    int nAction;                    //���������Ϣ�Ժ�Ķ���
};


struct GS2CSQueryPlayerInfoAck : public Msg
{
    GS2CSQueryPlayerInfoAck()
    {
        header.dwType = GS2CS_QUERYPLAYERINFOACK;
        header.stLength = sizeof(GS2CSQueryPlayerInfoAck);

        memset(szAckName, 0, sizeof(szAckName));
    }

    DWORD dwReqID;                          //������
    DWORD dwAckID;                          //������
    char szAckName[dr_MaxPlayerName];       //������������
    int nAction;                            //���������Ϣ�Ժ�Ķ���

    unsigned int nMapID;           //��ǰ��ͼID
    float fX;
    float fY;                     //��������
    float fDir;
};

//////////////////////////////////////////////////////////////////////////
// ԭ����GameServer�㲥����Ϣ �Ӹ��������� ͬ���� CenterServer
// ��֤ȫ����Ĺ㲥
struct S2STransmit : public S2SMsg
{
    enum ESessionType   // ���͵�Ŀ�귶Χ
    { 
        SESSIONT_None,
        SESSIONT_World,   // ȫ����
        SESSTONT_Single,  // ����
        SESSIONT_Team,    // ����
        SESSIONT_Guild,   // ����
        SESSIONT_Server,  // ������
        SESSIONT_Country, // ����
        SESSIONT_Max,
    };

    enum EConstDefine
    {
        BUFFER_SIZE = 1024 * 32,
    };

    struct SCharacter
    {
        unsigned long uDbId;
        char          szName[dr_MaxPlayerName]; 
    };

    struct STeam
    {
        unsigned long dwSessionID; // session id
        short nTeamIndex;          // ��Ա�ڶ����е�����

        STeam& operator == (const STeam& xTeam)
        {
            if(this != &xTeam)
            {
                dwSessionID = xTeam.dwSessionID;
                nTeamIndex  = xTeam.nTeamIndex;
            }

            return *this;
        }
    };

    struct SGuild
    {
        unsigned long id;
    };

    struct SServer
    {
        unsigned long id;
        char          exceptMe;
    };

    struct SCountry
    {
        TCountryId countryId;
    };

    union uDataType
    {
        SCharacter character;
        STeam      team;
        SGuild     guild;
        SServer    server;
        SCountry   country;
    };

    S2STransmit()
    {
        header.dwType   = GS2CS_TRANSMIT;
        header.stLength = sizeof(S2STransmit) - sizeof( buffer );
        directToClient = 1;
    }

    bool StorageMessage( Msg* pMessage )
    {
        if ( pMessage->GetLength() >= BUFFER_SIZE )
        { return false; }

        memcpy_s( buffer, sizeof( buffer), pMessage, pMessage->GetLength());
        header.stLength = sizeof(S2STransmit) - sizeof( buffer ) + pMessage->GetLength();
        return true;
    }
    unsigned char ucSessionType;
    uDataType     targetData;
    unsigned char directToClient;
    char          buffer[ BUFFER_SIZE ];
};

struct S2STransmitResult : public S2SMsg
{
    enum ETResult
    {
        ETR_Success,
        ETR_ClientPeerNotExist,
        ETR_GamePeerNotExist,
    };

    struct SCharacter
    {
        unsigned long uDbId;
        char          szName[dr_MaxPlayerName]; 
    };

    struct STeam
    {   
        unsigned long id;
    };

    struct SGuild
    {
        unsigned long id;
    };

    struct SServer
    {
        unsigned long id;
    };

    union uDataType
    {
        SCharacter character;
        STeam      team;
        SGuild     guild;
        SServer    server;
    };

    S2STransmitResult()
    {
        header.dwType   = S2S_TRANSMIT_RESULT;
        header.stLength = sizeof(S2STransmitResult);
    }

    unsigned long  nResult;
    unsigned char  ucSessionType;
    uDataType      targetData;
    unsigned long  msgType;
};

struct S2SNotifyTimeEvent : public Msg
{ 
    S2SNotifyTimeEvent()
    {
        header.stLength = sizeof(S2SNotifyTimeEvent);
        header.dwType   = S2S_NOTIFYTIMEEVENT;
    }

    unsigned long timeEventValue;
};

struct S2SChangeExp : public Msg
{ 
    S2SChangeExp()
    {
        header.stLength = sizeof(S2SChangeExp);
        header.dwType   = S2S_CHANGEEXP;
        expPer = 100;
    }
    int expPer;
};

struct S2SAntiAddictionAccountInfo : public Msg
{ 
    S2SAntiAddictionAccountInfo()
    {
        header.stLength = sizeof(S2SAntiAddictionAccountInfo);
        header.dwType   = S2S_ANTIADDICTIONACCOUNTINFO;
    }
    unsigned long accountId;        // �˺�
    unsigned long onlineMinuteTime; // ����ʱ��
    unsigned long offMinuteTime;    // ����ʱ��
};

struct S2SNotiyAntiAddictionTimeInfo : public Msg
{
    S2SNotiyAntiAddictionTimeInfo()
    {
        header.stLength = sizeof(S2SNotiyAntiAddictionTimeInfo);
        header.dwType   = S2S_NOTIYANTIADDICTIONTIMEINFO;
		bOpenantiAddiction = false;
		nAntiAddictionSaveTime = 0;
	}

	bool              bOpenantiAddiction;
	AntiAddictionTime antiAddictionTime ;
	uint32            nAntiAddictionSaveTime;
};

struct GS2CSDrawFromPlatformQuery : public Msg
{
    GS2CSDrawFromPlatformQuery()
    {
        header.stLength = sizeof(GS2CSDrawFromPlatformQuery);
        header.dwType   = GS2CS_DRAWFROMPLATFORM_QUERY;
    }

    uint8  drawType;
    uint32 guid;
};

struct CS2GSDrawFromPlatformAck : public Msg
{
    CS2GSDrawFromPlatformAck()
    {
        header.stLength = sizeof( CS2GSDrawFromPlatformAck );
        header.dwType   = CS2GS_DRAWFROMPLATFORM_ACK;
    }

    uint16 drawType;
    uint32 result; // ���
    uint32 guid;   // �û�id
    uint32 value;  // �����
};

struct S2SCallGraphic : public Msg
{
    S2SCallGraphic()
    {
        header.stLength = sizeof( S2SCallGraphic );
        header.dwType   = S2S_CALL_GRAPHIC;
    }
};

struct CS2GSMsgSetCheckCheatOpen : public Msg
{
    CS2GSMsgSetCheckCheatOpen()
    {
        header.dwType = CS2GS_SETCHECKCHEATOPEN;
        header.stLength = sizeof( CS2GSMsgSetCheckCheatOpen );
    }

    bool bOpen;
};


struct S2SMsgUpdateItemDropControl : public Msg
{
    S2SMsgUpdateItemDropControl()
    {
        header.dwType = S2S_UPDATEDROPITEMCONTROL;
        header.stLength = sizeof( S2SMsgUpdateItemDropControl );

        dwDropCount = 0;
    }

    uint16 nItemID;
    uint32 dwControlCount;
    uint32 dwDropCount;
};

struct CS2GSMsgBornMapOperate : public Msg
{
    CS2GSMsgBornMapOperate()
    {
        header.dwType = CS2GSMSGBORNMAPOPERATE;
        header.stLength = sizeof( CS2GSMsgBornMapOperate );
    }
 
    bool chOperate;
};

//struct GS2CSMoneyItemExchange : public Msg
//{
//    GS2CSMoneyItemExchange()
//    {
//        header.dwType = GS2CS_MONEYITEMEXCHANGE;
//        header.stLength = sizeof( GS2CSMoneyItemExchange );
//    }
//
//    uint32  guid;
//    int8    charName[33];
//    uint16  itemId;
//    int64   itemguid;
//    int8    itemName[17];
//    int8    linkman[17];
//    int8    telephone[13];
//    int8    email[50];
//    int8    identityCard[19];
//    int8    passport[33];
//};

struct CS2GSGMBroatcastReq : public Msg
{
    enum EConstDefine
    {
        CD_ContentMaxSize = 512,
    };

    CS2GSGMBroatcastReq()
    {
        header.dwType = CS2GS_GMBROATCAST_REQ;
        header.stLength = sizeof( CS2GSGMBroatcastReq );
    }

    int8 content[CD_ContentMaxSize];
};

struct CS2GSGmKickPlayerReq : public Msg
{ // GM ����
    CS2GSGmKickPlayerReq()
    {
        header.dwType   = CS2GS_GMKICKPLAYER_REQ;
        header.stLength = sizeof( CS2GSGmKickPlayerReq );
        accountGuid = 0;
        chardbId    = InvalidLogicNumber;
        memset( charName, 0, sizeof( charName ));
        time        = 0;
    }
    uint32  accountGuid;  // �ʺ�
    uint32  chardbId;     // ��ɫId
    int8    charName[33]; // ��ɫ��
    uint32  time;         // s ��
};

struct MsgChangeMapCallBack : public Msg
{
    MsgChangeMapCallBack()
    {
        header.dwType   = MSG_CHANGEMAPCALLBACK;
        header.stLength = sizeof( *this );
    }

    uint32 dwTeamSessionID;
};

struct S2SUpdateTradeShopConfig : public Msg
{ // �����̳ǵ�����ȡ
    enum EConstDefine
    {
        ECD_ConfigBufferMaxSize = 50 * 1024,
    };

    S2SUpdateTradeShopConfig()
    {
        Reset();
        header.dwType   = S2S_UPDATETRADESHOPCONFIG;
        header.stLength = sizeof( S2SUpdateTradeShopConfig ) - sizeof( buffer );
    }

    void Reset()
    {
        zip = 0;
        bufferSize = 0;
        memset( buffer, 0, sizeof(buffer));
    }

    bool Clone( const uint8* inBuffer, uint32 size, bool bZip = true )
    {
        if ( size >= ECD_ConfigBufferMaxSize)
        { return false; }

        zip = bZip;
        bufferSize = size;
        memcpy_s( buffer, ECD_ConfigBufferMaxSize, inBuffer, size );
        header.stLength = sizeof( S2SUpdateTradeShopConfig ) - sizeof( buffer ) + size;
        return true;
    }
   
    uint8  zip;
    uint32 bufferSize;
    uint8  buffer[ECD_ConfigBufferMaxSize];
};

struct S2SShutdownServer : public Msg
{
    S2SShutdownServer()
    {
        header.dwType   = S2S_SHUTDOWNSERVER;
        header.stLength = sizeof( S2SShutdownServer );
        serverType      = ST_CenterServer;
        delayTime       = 0;
    }

    uint8  serverType;
    uint32 delayTime;  // ��
};

struct S2SChangeMapExpRate : public Msg
{
    S2SChangeMapExpRate()
    {
        header.dwType   = S2S_CHANGEMAPEXPRATE;
        header.stLength = sizeof( S2SChangeMapExpRate );
        mapConfigId = InvalidLogicNumber;
        fExpRate    = 1.0f;
    }

    uint32 mapConfigId; // ��λ��
    float  fExpRate;    // 1.0 == 100% 
};

struct GS2CSMailListReq : public Msg
{
    GS2CSMailListReq()
    {
        header.dwType   = GS2CS_MAILLISTREQ;
        header.stLength = sizeof( GS2CSMailListReq );
        accountId = 0;
        charDbId  = 0;
    }
    uint32 accountId;
    uint32 charDbId;
};

struct CS2GSMailListAck : public Msg
{
    CS2GSMailListAck()
    {
        header.dwType = CS2GS_MAILLISTACK;
        header.stLength = sizeof(CS2GSMailListAck) - sizeof(mails);
        accountId = 0;
        charDbId  = 0;
        count     = 0;
        isnew     = 1;
        memset( mails, 0, sizeof(mails));
    }

    void Reset()
    {
        count = 0;        
        memset( mails, 0, sizeof(mails));
    }

    bool AddMail( const SMail& mail )
    {
        if ( count >= EM_MailMaxCount )
        { return false; }

        mails[count++] = mail;
        header.stLength = sizeof(CS2GSMailListAck) - sizeof(SMail) * ( EM_MailMaxCount - count );
        return true;
    }

    bool IsFull()
    {
        if ( count >= EM_MailMaxCount )
        { return true; }
        return false;
    }

    void RecalLength()
    { header.stLength = sizeof(CS2GSMailListAck) - sizeof(SMail) * ( EM_MailMaxCount - count ); }

    uint32 accountId;
    uint32 charDbId;
    uint8  isnew;
    uint8  count;
    SMail  mails[EM_MailMaxCount];
};

struct GS2CSSendMailReq : public Msg
{ // �����ʼ�
    GS2CSSendMailReq()
    {
        header.dwType   = GS2CS_SENDMAILREQ;
        header.stLength = sizeof( GS2CSSendMailReq );
        accountId = InvalidLogicNumber;
        
    }
    uint32 accountId;
    uint32 charDbId;
    SMail  mail;
};

struct CS2GSSendMailAck : public Msg
{ // �����ʼ�����
    CS2GSSendMailAck()
    {
        header.dwType   = CS2GS_SENDMAILACK;
        header.stLength = sizeof( CS2GSSendMailAck ) - sizeof(SMail);
        result = ER_Success;
    }

    void RecalLength()
    {
        header.stLength = sizeof( CS2GSSendMailAck );
    }

    uint32 result;
    uint32 accountId;
    uint32 charDbId;
    SMail  mail;
};

struct GS2CSOpMailReq : public Msg
{ // �ʼ�����
    GS2CSOpMailReq()
    {
        header.dwType   = GS2CS_OPMAILREQ;
        header.stLength = sizeof( GS2CSOpMailReq );
        op = 0;
        mailId = 0;
        accountId = 0;
        charDbId = 0;
    }
    uint8  op;
    uint32 mailId;
    uint32 accountId;
    uint32 charDbId;
};

struct CS2GSOpMailAck : public Msg
{ // �ʼ���������
    CS2GSOpMailAck()
    {
        header.dwType   = CS2GS_OPMAILACK;
        header.stLength = sizeof( CS2GSOpMailAck ) - sizeof(accessory.content);
        result = ER_Success;
        op = 0;
        mailId = 0;
        accountId = 0;
        charDbId = 0;
        money = 0;
    }

    void RecalLength()
    { header.stLength = sizeof( CS2GSOpMailAck ); }

    uint32     result;
    uint8      op;
    uint32     mailId;
    uint32     accountId;
    uint32     charDbId;
    uint32     money;
    SMail::SAccessory accessory; // ��������
};
struct GS2CSQueryMailCanSendReq : public Msg
{
    GS2CSQueryMailCanSendReq()
    {
        header.dwType   = GS2CS_QUERYMAILCANSENDREQ;
        header.stLength = sizeof( GS2CSQueryMailCanSendReq );
        memset( targets, 0, sizeof(targets) );
        isHaveItem = 0;
    }

    uint32          charDbId;                     // ������
    uint8           isHaveItem;                 // ����Ǯ����Ʒ
    SMail::SAddress targets[EM_TargetMaxCount]; // �����˵ĵ�ַ
};

struct CS2GSQueryMailCanSendAck : public Msg
{
    CS2GSQueryMailCanSendAck()
    {
        header.dwType   = CS2GS_QUERYMAILCANSENDACK;
        header.stLength = sizeof( CS2GSQueryMailCanSendAck );
    }
    uint32                result;                     // �ṹ
    uint32                charDbId;                     // ������
    SMail::SAddressResult targets[EM_TargetMaxCount]; // �����Ŀ���ַ
};

struct S2SRemoteBanReq : public Msg
{
    S2SRemoteBanReq()
    {
        header.dwType   = S2S_REMOTEBANREQ;
        header.stLength = sizeof( S2SRemoteBanReq );
    }
    char   chOrAcc;                   // ��ɫ��Ϊ0/�ʺ�Ϊ1,ע��ʹ���ʺ�ʱҪ���ʺ�ID
    int8   _Name[dr_MaxPlayerName]; // Ŀ������
    uint32 banTime;                    // ban��ʱ��
	uint32 accountid;				//�ʺ�ID
};

//zhuxincong
struct S2SDleteCountryBattleReward: public Msg
{
	S2SDleteCountryBattleReward()
	{
		header.dwType = S2S_DleteCountryBattleReward;
		header.stLength = sizeof( S2SDleteCountryBattleReward );
		nPosition = 0;
		nPlayerID = 0;
	}

	int nPosition;
	int nPlayerID;
};


struct MsgPartitionLogFile : public Msg
{
    MsgPartitionLogFile()
    {
        header.dwType   = MSG_PARTITIONLOGFILE;
        header.stLength = sizeof( MsgPartitionLogFile );
    }
};

struct CS2GSOpRecordChatOnOff : public Msg
{
    CS2GSOpRecordChatOnOff()
    {
        header.dwType   = CS2GS_OPRECORDCHATONOFF;
        header.stLength = sizeof( CS2GSOpRecordChatOnOff);
        isOpen = 0;
    }
    int8 isOpen;
};

struct S2SRecordChatContent : public Msg
{
    enum EConstDefine
    {
        ECD_ContentMaxSize = 1024,
    };

    S2SRecordChatContent()
    {
        header.dwType   = S2S_RECORDCHATCONTENT;
        header.stLength = sizeof( S2SRecordChatContent) - sizeof(content);
        length = 0;
        memset( content, 0, sizeof(content));
    }

    void BuildString(const char* szFormat, ...)
    {
        va_list vl;
        va_start(vl, szFormat);
        int cnt = vsnprintf_s( content, sizeof(content), sizeof(content)-1, szFormat, vl);
        va_end(vl);

        length = (uint16)strlen( content );
        header.stLength += length;
    }

    uint16 length;
    int8   content[ECD_ContentMaxSize];
};

struct CS2GSMsgRewardOperate : public Msg
{
    CS2GSMsgRewardOperate()
    {
        header.dwType   = CS2GS_REWARDOPERATE;
        header.stLength = sizeof( CS2GSMsgRewardOperate );
    }

    enum EConstDefine
    {
        ECD_Exp = 0,
    };

    uint8 uchType;
    uint32 dwValue;
};

struct CS2GSLoadResourceSuccess : public Msg
{
    CS2GSLoadResourceSuccess()
    {
        header.dwType   = CS2GSLOADFRESOURCESUCCESS;
        header.stLength = sizeof( CS2GSLoadResourceSuccess );
    }

    uint8 uchLoadType;
};

struct CS2DBItemDropControlReq : public Msg
{
    CS2DBItemDropControlReq()
    {
        header.dwType = CS2DB_ITEMDROPCONTROLREQ;
        header.stLength = sizeof( CS2DBItemDropControlReq );
    }
};

struct ItemDropInfo
{
    uint16 nItemID;
    ItemDropControl xControl;
};

struct DB2CSItemDropControl : public Msg
{
    DB2CSItemDropControl()
    {
        header.dwType = DB2CS_ITEMDROPCONTROL;
        header.stLength = sizeof( DB2CSItemDropControl ) - sizeof( xDropInfo );
        nCount = 0;
    }

    enum EConstDefine
    {
        ECD_MaxCount = 500,
    };

    int nCount;
    ItemDropInfo xDropInfo[ECD_MaxCount];

    void AddItemDropControl( uint16 nItemID, uint32 dwControlCount, uint32 dwDropCount )
    {
        if ( nCount >= ECD_MaxCount )
        { return; }

        xDropInfo[nCount].nItemID = nItemID;
        xDropInfo[nCount].xControl.dwControlCount = dwControlCount;
        xDropInfo[nCount].xControl.dwDropCount    = dwDropCount;

        ++nCount;
        header.stLength += sizeof( ItemDropInfo );
    }

    bool IsFull() { return nCount >= ECD_MaxCount; }

    void Reset()
    {
        nCount = 0;
        header.stLength = sizeof ( DB2CSItemDropControl ) - sizeof( xDropInfo );
    }

};

struct CS2GSItemDropControl : public Msg
{
    CS2GSItemDropControl()
    {
        header.dwType = CS2GS_ITEMDROPCONTROL;
        header.stLength = sizeof( CS2GSItemDropControl ) - sizeof( xDropInfo );
        nCount = 0;
    }

    enum EConstDefine
    {
        ECD_MaxCount = 500,
    };

    int nCount;
    ItemDropInfo xDropInfo[ECD_MaxCount];

    void AddItemDropControl( uint16 nItemID, uint32 dwControlCount, uint32 dwDropCount )
    {
        if ( nCount >= ECD_MaxCount )
        { return; }

        xDropInfo[nCount].nItemID = nItemID;
        xDropInfo[nCount].xControl.dwControlCount = dwControlCount;
        xDropInfo[nCount].xControl.dwDropCount    = dwDropCount;

        ++nCount;
        header.stLength += sizeof( ItemDropInfo );
    }

    bool IsFull() { return nCount >= ECD_MaxCount; }

    void Reset()
    {
        nCount = 0;
        header.stLength = sizeof ( CS2GSItemDropControl ) - sizeof( xDropInfo );
    }

};

struct CS2DBSaveItemDropControl : public Msg
{
    CS2DBSaveItemDropControl()
    {
        header.dwType = CS2DB_SAVEITEMDROPCONTROL;
        header.stLength = sizeof( CS2DBSaveItemDropControl ) - sizeof( xDropInfo );
        nCount = 0;
    }

    struct ItemDropInfo
    {
        uint16 nItemID;
        ItemDropControl xControl;
    };

    enum EConstDefine
    {
        ECD_MaxCount = 500,
    };

    int nCount;
    ItemDropInfo xDropInfo[ECD_MaxCount];

    void AddItemDropControl( uint16 nItemID, uint32 dwControlCount, uint32 dwDropCount )
    {
        if ( nCount >= ECD_MaxCount )
        { return; }

        xDropInfo[nCount].nItemID = nItemID;
        xDropInfo[nCount].xControl.dwControlCount = dwControlCount;
        xDropInfo[nCount].xControl.dwDropCount    = dwDropCount;

        ++nCount;
        header.stLength += sizeof( ItemDropInfo );
    }

    bool IsFull() { return nCount >= ECD_MaxCount; }

    void Reset()
    {
        nCount = 0;
        header.stLength = sizeof ( CS2DBSaveItemDropControl ) - sizeof( xDropInfo );
    }
};

struct CS2GSUpdateCountryOnLineCount : public Msg
{
    CS2GSUpdateCountryOnLineCount()
    {
        header.dwType = CS2GS_UPDATECOUNTRYONLINECOUNT;
        header.stLength = sizeof( CS2GSUpdateCountryOnLineCount );
    }

    uint8 uchCountryID;
    int nCount;
};

struct GS2CSUpdateAntiaddictionInfoReq : public Msg
{ // ���·�������Ϣ
	enum EUpdateReqType
	{
		EUpdateReqType_Init  , // ��һ�ε�¼��
		EUpdateReqType_Update, // ��Ϸ��Update
		EUpdateReqType_Exit  , // �˳�����
	};

	GS2CSUpdateAntiaddictionInfoReq()
	{
		header.dwType   = GS2CS_UPDATEANTIADDICTIONINFOREQ;
		header.stLength = sizeof( GS2CSUpdateAntiaddictionInfoReq );
		nType = EUpdateReqType_Init;
		memset( passport, 0, sizeof(passport));
		nAccountId = 0;
		nDuration = 0;
	}

	uint8  nType       ; // ��������
	int8   passport[33]; // �˺�
	uint32 nAccountId  ; // �˺�Id
	uint32 nDuration   ; // ������ʱ�� ��λ����
};

struct CS2GSUpdateAntiaddictionInfoAck : public Msg
{ // ���·�������Ϣ
	CS2GSUpdateAntiaddictionInfoAck()
	{
		header.dwType   = CS2GS_UPDATEANTIADDICTIONINFOACK;
		header.stLength = sizeof( CS2GSUpdateAntiaddictionInfoAck );
		nResult = ER_Success;
		nAccountId = 0;
		nOnlineTime = 0;
		nDuration = 0;
	}

	uint16 nResult     ; // ���
	uint8  nType       ; // ��������
	uint32 nAccountId  ; // �˺�Id
	uint32 nOnlineTime ; // �ۼ�����ʱ��
	uint32 nDuration   ; // ������ʱ�� ��λ����
};

struct CS2GSPing : public Msg
{
	CS2GSPing()
	{
		header.dwType = CS2GS_PING;
		header.stLength = sizeof(CS2GSPing);
	}
};

#pragma pack( pop ) 

#pragma pack( push, 1)
struct SqlMessage 
{ // �����ѯ�ĵ���Ϣcache���ṹ��buff��
	enum ESqlMessageId
	{
		ESM_CanLogin        = 1000,
		ESM_PlayerInGame    ,
		ESM_PlayerExitGame  ,
		ESM_ClientConnectGateOverTime , // �ͻ�������Gate��ʱ
		ESM_GameWorldNotReady,
		ESM_KickSuccess,
		ESM_ProcessLoginAllowTimeOver, // �����¼ʱ��̫����
		ESM_NotGameServerService,      // ��������æ
		ESM_KickInValid,               // ��Ч��Kick
		ESM_OfflineStall,				// �����˺�״̬Ϊ���߰�̯
	};

	int     nMessageId;                       // ��ϢId
	int     Guid;                             //�ʺ�ID    
	//char    GLSId[MAX_NAME_STRING+1];       // ���ݿ�����32�ֽ�
	char    Passport[MAX_NAME_STRING+1];      //�ʺ���
	//char    sPassword[MAX_PASSWORD_STRING+1]; //����,Ӧ���Ǽ��ܺ��
	int     AccountLevel;                     //�ʺŵȼ�
	//char    SessionKey[40+1];          //��֤session,Ψһ,����ԶԶ��Ψһ
	__int64   SessionKey;
	//char    Token[32+1];
	//char    Seed[40+1];
	char    IpPort[128+1];					  //�ʺ���֤��IP��ַ
	short   Status;							  // ��¼״̬ 1 --- ��½������dbcenter���Դ��� 2 --- dbcenter�õ�����û� 3 --- dbcenter������ϣ�client�˿��Ե�¼��Ϸ������ 4 --- �û�����game server�� 
	int     State_Time;						  // ��ʱʱ��
	uint32  MessageCreateTime;				  // ����Ϣ����ʱ��
	int8    isWallow;						  // �Ƿ��ǳ�����

	SqlMessage()
	{ memset(this,0,sizeof(SqlMessage)); }

	SqlMessage(const SqlMessage& table)
	{
		if (&table == this)
		{ return ; }
		memcpy_s( this, sizeof(SqlMessage), &table, sizeof(SqlMessage));
	}

	void Clear()
	{  memset(this,0,sizeof(SqlMessage));}

	bool operator ==(const SqlMessage &other)
	{
		return Guid == other.Guid;
	}

	bool operator ==(const int GuildId)
	{
		return Guid == GuildId;
	}

	bool operator ==(const char* Passport)
	{
		return strcmp(this->Passport , Passport) == 0;
	}

	SqlMessage& operator =(const SqlMessage& Passport)
	{
		if (&Passport == this)
		{
			return *this;
		}
		memcpy_s(this, sizeof(SqlMessage), &Passport, sizeof(SqlMessage));
		return *this;
	}
};

struct KickMessage
{
	KickMessage()
	{
		nGuid = 0;
		memset( szPassport, 0, sizeof(szPassport) );
		bProcess = 0;
		bAcceptTime = 0;
	}

	unsigned int  nGuid;
	char          szPassport[32+1];
	char          bProcess; // �Ƿ񱻴����
	unsigned long bAcceptTime;
};

struct MsgCenterKick:public Msg
{
	MsgCenterKick()
	{
		SetType( TO_CENTER_LOGIN_KICK );
		SetLength( sizeof( MsgCenterKick ) );
	}
	uint32           _loginserverId;
	KickMessage sql;
};

struct MsgCenterLoginOn:public Msg
{
	MsgCenterLoginOn()
	{
		SetType( TO_CENTER_LOGIN_ON );
		SetLength( sizeof( MsgCenterLoginOn ) );
	}
	uint32           _loginserverId;
	SqlMessage sql;
};

struct MsgCenterLoginOff:public Msg
{
	MsgCenterLoginOff()
	{
		SetType( TO_LOGIN_LOGIN_OFF );
		SetLength( sizeof( MsgCenterLoginOff ) );
	}
	uint32           _loginserverId;
	SqlMessage sql;
};


enum eLoginError
{
	eLE_AccountInGame = 0,//�ʺ��Ѿ�����
	eLE_AccountServerFullLoad ,//��������������
	eLE_AccountOverOneMac,//��������mac��������
};
struct MsgLoginError:public Msg 
{
	MsgLoginError()
	{
		SetType(CS2LS_LOGIN_ERROR);
		SetLength(sizeof(MsgLoginError));
	}
	uint32 uAccountId;
	uint8  chErrorType;
};

struct MsgPFSendmailReq:public Msg
{
	MsgPFSendmailReq()
	{
		header.stLength = sizeof(MsgPFSendmailReq);
		header.dwType  = CS2GS_PLATFORMSENDMAILREQ;
	}
	uint32 characterid		;//��ɫDB ID
	char   charactername[ETaskInfo_NameMaxLength]	;
	char   title[ETaskInfo_TileMaxCount]			;//�ʼ�����
	char   content[ETaskInfo_MailContentMax]			;//�ʼ�����
	uint32 money			;//����
	uint16 itemid			;//��ƷID
	uint16 itemcount		;//��Ʒ����
};

struct MsgPFSendmailAck:public Msg
{
	MsgPFSendmailAck()
	{
		header.stLength = sizeof(MsgPFSendmailAck);
		header.dwType  = CS2GS_PLATFORMSENDMAILACK;
	}
	uint32 characterid		;//��ɫDB ID
	char   charactername[ETaskInfo_NameMaxLength]	;
	char   title[ETaskInfo_TileMaxCount]			;//�ʼ�����
	char   content[ETaskInfo_MailContentMax]			;//�ʼ�����
	uint32 money			;//����
	SCharItem item			;
};

struct MsgGS2CSAskForPresent:public Msg
{
	MsgGS2CSAskForPresent()
	{
		header.stLength = sizeof(MsgGS2CSAskForPresent);
		header.dwType = GS2CS_ASKFORPRESENT;
	}
	uint32 characterid;
	uint32 accountid;
	char   sn[33];
	char   charactername[33];
};

struct MsgGS2CsAskForPlatformActivity:public Msg 
{
	MsgGS2CsAskForPlatformActivity()
	{
		header.stLength = sizeof(MsgGS2CsAskForPlatformActivity);
		header.dwType = GS2CS_ASKFORPLATFORMACTIVITY;
	}
	uint32 characterid;
	uint32 accountid;
	int32  _type;
	char   charactername[33];
};

struct MsgCS2GSQueueOp:public Msg
{
	MsgCS2GSQueueOp()
	{
		header.stLength = sizeof(MsgCS2GSQueueOp);
		header.dwType = CS2GS_QUEUE_OP;
		_open = false;
	}
	bool _open;
};

struct MsgGS2CSEpistarPoint:public Msg
{
	MsgGS2CSEpistarPoint()
	{
		header.stLength = sizeof(MsgGS2CSEpistarPoint);
		header.dwType = GS2CS_REQ_EPISTARPOINT;
	}
	uint32 accountid;
	uint32 characterid;
	uint8  _type;			//������
	uint16 nItemId;
	uint16 nPoint;
	char   charactername[ETaskInfo_NameMaxLength];
};
struct MsgCS2GSCharRemoveItembyId:public Msg
{
	MsgCS2GSCharRemoveItembyId()
	{
		header.stLength = sizeof(MsgCS2GSCharRemoveItembyId);
		header.dwType = CS2GS_CHARREMOVEITEMBYID;
	}
	uint32 characterid;
	uint16 nItemId;
};

struct MsgCS2GSUpdateReloadCfg:public Msg
{
	MsgCS2GSUpdateReloadCfg()
	{
		header.stLength = sizeof(MsgCS2GSUpdateReloadCfg);
		header.dwType = CS2GS_UPDATEARELOADCONFIG;
		nReloadType = -1;
	}
	uint16 nReloadType;
};
struct MsgS2SBlockAccount:public Msg
{
	MsgS2SBlockAccount()
	{
		header.stLength = sizeof(MsgS2SBlockAccount);
		header.dwType = S2S_BlockAccount;
	}
	uint32 guid;
	char   name[MAX_NAME_STRING];
	uint32 blocktime;
};

struct MsgS2SBlockMac:public Msg
{
	MsgS2SBlockMac()
	{
		header.stLength = sizeof(MsgS2SBlockMac);
		header.dwType = S2S_BlockMacAddress;
	}
	char   scMac[MAC_LENGTH];
	uint32 blocktime;
};

struct MsgCS2GSBroadCast : public Msg
{
	enum Type
	{
		Type_Monster,

		Type_Max,
	};

	MsgCS2GSBroadCast()
	{
		header.stLength = sizeof( MsgCS2GSBroadCast );
		header.dwType = CS2GS_ASKBROADCAST;

		type = Type_Max;
		nMonsterID = -1;
		nMapID = -1;
	}

	Type type;
	int nMonsterID;
	int nMapID;
};

struct MsgGS2CSBroadCastAck : public Msg
{
	MsgGS2CSBroadCastAck()
	{
		header.dwType = GS2CS_ASKBROADCAST_ACK;
		header.stLength = sizeof( MsgGS2CSBroadCastAck );

		type = MsgCS2GSBroadCast::Type_Max;
		nResult = -1;
	}

	MsgCS2GSBroadCast::Type type;
	int nResult;
};

#pragma pack( pop )

#endif // __CENTERGAMEMESSAGE_H__
