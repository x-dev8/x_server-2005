/********************************************************************
    Filename:     DBMsg.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#pragma once

#include "GlobalDef.h"
#include "MessageDefine.h"
#include "CampBattleDefine.h"
//�������ݿ����Ϸ���罻������Ϣ�ṹ
enum EDBMessageDefine
{
    //���ݿ����
    DB_FIRST_MSG = DB_MSG_BEGIN
    ,DBMSG_LOGIN                // ��¼�ʺ�
    ,DBMSG_ACKLOGIN             // ACK up
    ,DBMSG_ACKCHAR              // ACK ��ɫ��Ϣ
    ,DBMSG_ENDACKCHAR           // ����ACK��ѯ
    ,DBMSG_SAVECHAR             // ���ɫ��Ϣ
    ,DBMSG_CREATECHAR           // ������ɫ
    ,DBMSG_ACKCREATECHAR        // ACK up
    ,DBMSG_DELETECHAR           // ɾ����ɫ
    ,DBMSG_ACKDELETECHAR        // ACK up
    ,DBMSG_REGACCOUNTS          // ע���ʺ�
    ,DBMSG_ACKREGACC            // ACK up
    ,DBMSG_DELACCOUNTS          // ɾ���ʺ�
    ,DBMSG_ACKDELACC            // ACK up
    ,DBMSG_OFFLINE              // �ʺ�����
    ,DBMSG_GSERVEREXIT
    ,DBMSG_CHANGEPASSWORD       // Change password
    ,DBMSG_ACKCHANGEPASSWORD
    ,DBMSG_CHANGECASHPOINT      // add or deduct cashpoint
    ,DBMSG_ACKCHANGECASHPOINT
    ,DBMSG_QUERYACCOUNTCHAR
    ,DBMSG_ENTERWORD            // ������Ϸ����
    ,DBMSG_ACKENTERWORD         // ACK UP
    ,DBMSG_ACKCHARDATA          // �������ݿ⴫���Ľ�ɫ����
    ,DBMSG_ACKCHARITEMBAG       // �������ݿ⴫���Ľ�ɫ��������
    ,DBMSG_SAVEITEM             // ���ɫ��Ʒ��
    ,DBMSG_SAVECHARACTER        // ֪ͨ���ݿⱣ���ɫ����
    ,DBMSG_ACKOPERSUCC          // ֪ͨGameServer�洢�����ɹ� ������Ϣ�����ɹ�
    ,DBMSG_QUERY_SELCHARS       // ��¼�ɹ��������ɫ��Ϣ
    ,DBMSG_CHARSAVEVARS         // ���ɫϵͳ����
    ,DBMSG_CHARLOADVARS         // ȡ��ɫϵͳ����
    ,DBMSG_ITEMTRACELOG         // ���߸���
    ,DBMSG_REQ_STORAGE          // ��ѯ�ֿ�������ݿ�
    ,DBMSG_ACK_STORAGE
    ,DBMSG_KICKCHAR             // ֪ͨ��Ϸ�������ߵ�ĳ���ʺŵĽ�ɫ
    ,DBMSG_ACCOUNTSTATE         // ����ʺŵ���Ϸ״̬�����õ�ǰ״̬
    ,DBMSG_ACK_ACCOUNTSTATE     // ���ؼ���ʺŵ���Ϸ״̬���

    ,DBMSG_REQ_CREATE_CHECKNAME // ���� ��� ��������Ƿ��ظ�
    ,DBMSG_ACK_CREATE_CHECKNAME // ���� ���� ��� ��������Ƿ��ظ�

	,DBMSG_CHANGENAMEREQ
	,DBMSG_CHANGENAMEACK
    
    ,DBMSG_SAVELEVEL            // ����ȼ�
    ,DBMSG_SAVEEXP              // ���澭��
    ,DBMSG_SAVESKILLEXP         // ���漼�ܾ���
    ,DBMSG_ADDITEM              // �����Ʒ
    ,DBMSG_REMOVEITEM           // �Ƴ���Ʒ
    ,DBMSG_EXCHANGEITEM         // ������Ʒ
    ,DBMSG_ITEMATTRIBCHANGE     // ��Ʒ���Ա仯
    ,DBMSG_ITEMAMOUNTCHANGE     // ��Ʒ�����仯
    ,DBMSG_ITEMLOCKSTATUSCHANGE // ��Ʒ����״̬�仯
    ,DBMSG_CANCELDELCHAR        // ȡ��ɾ����ɫ
    ,DBMSG_ACKCANCELDELCHAR     // ��Ӧȡ��ɾ����ɫ
    ,DBMSG_REQ_ACCOUNT_BILLING      // ��ȡ�ʺŵ���
    ,DBMSG_ACK_ACCOUNT_BILLING      // ������ȡ�ʺŵ���
    ,DBMSG_REQ_ACCOUNT_BILLING_OP   // �ʺŵ�������
    ,DBMSG_LOG                      // ��־��Ϣ

    ,DBMSG_ACCOUNTWALLOWINFO_REQ    // �ʺų�����Ϣ
    ,DBMSG_ACCOUNTWALLOWINFO_ACK    // �ʺų�����Ϣ
    ,DBMSG_ACCOUNTWALLOWINFO_SAVE   // �ʺų�����Ϣ�洢
    ,DBMSG_KICKCHARACK              // �߳�ĳ�ʺŵĻ���
    ,DBMSG_JIFENGSHOPITEMSLISTREQ   // �����̳ǵ��߲�ѯ
    ,DBMSG_JIFENGSHOPITEMSLISTACK   // �����̳ǵ����б�
    ,DBMSG_JIFENGSHOPITEMSGAINREQ   // �����̳ǵ�����ȡ
    ,DBMSG_JIFENGSHOPITEMSGAINACK   // �����̳ǵ��߻���
    ,DBMSG_CHANGENAME               // �ı�����
    ,GS2DB_REQ_INIT_DATA
    ,DB2GS_ACK_INIT_DATA
    ,DB2DB_NOTIFYFILEDBSAVECHAR     // �����ļ�db��ɫ�����

    ,DBMSG_PETBREEDQUERYREQ         // ���ﷱֳ��ѯ
    ,DBMSG_PETBREEDQUERYACK         // ���ﷱֳ��ѯ����

	,DBMSG_SHOPPING                 //�̳ǹ�����Ʒ
	,DBMSG_OPERATEACCOUNTMONEY      //��������
	,DBMSG_SETBILLINGMONEY          //֪ͨGS���õ���

	,DB2DB_Cash                     //DB SERVER�������ݿ���̳�ֵ
	,DB2DB_CashResult               //���س�ֵ���
	,DBMSG_OPCONSUMESCORE           //��������
	,DBMSG_SETCONSUMESCORE
	,DB2DB_ConsumeScore				//DB SERVER�������ݿ���̳�ֵ����
	,DB2DB_ConsumeScoreResult

	,DBMSG_LOADCAMPBATTLEDATA
	,DB2DB_LOADCAMPBATTLEDATA
	,DBMSG_ADDCAMPBATTLEDATA
	,DBMSG_DELCAMPBATTLEDATA

	,GS2DB_UPDATEYUANBAODATA
	,DB2GS_UPDATEYUANBAODATA

	,GS2DB_UPDATEPLAYERPOINT
	,DB2GS_UPDATEPLAYERPOINT
};

#pragma pack(push,1) 

struct DBMsg : public Msg
{
    DBMsg()
    {
        SetLevel(level_high);
        ustLifeCode = 0;
        shServerId  = -1;
        subMarker   = 0;
    }

    // ��ID�����һ���ж�Ψһ�Ķ��� CDBInterface��DispatchMsgת����Ϣʱ�ж�
    unsigned short ustLifeCode; // ��������
    short          shServerId;
    unsigned long  subMarker;   // DB��Ϣ������һ��ID�����ڱ�ʶ���سɹ�
};

//////////////////////////////////////////////////////////////////////////
struct DBMsg_GServerExit : public DBMsg
{
	DBMsg_GServerExit()
	{
		header.dwType = DBMSG_GSERVEREXIT;
		header.stLength = sizeof(*this);
        header.uMsgLevel = level_high;
	}
};
//��¼
//typedef DBMsgLogin DBMsgLogin2;
struct DBMsgLogin2:public DBMsg
{
	DBMsgLogin2()
	{
        memset(this, 0, sizeof(DBMsgLogin2));
		header.dwType = DBMSG_LOGIN;
		header.stLength = sizeof( DBMsgLogin2 );
        IsForceLogin = false;
	}
	char szUserName[ dr_MaxUserName ];
    char szPassword[ dr_MaxPassword ];
    char szIP[20];              //IP��ַ
	//��Ϣ����loginServerʱ����loginServer��д
	DWORD dwGWorldServerID;
	//��Ϣ����AccountServerʱ����AccountServer��д
	DWORD dwLoginServerID;
    bool IsForceLogin;
};
//��Ϣ����
struct DBMsgAckLogin2:public DBMsg
{

	DBMsgAckLogin2()
	{
		header.dwType = DBMSG_ACKLOGIN;
		header.stLength = sizeof( DBMsgAckLogin2 );
        IsForceLogin = false;
	}
	//�Ƿ��¼�ɹ�
	short		stRet;
	DWORD		dwAccountID;		
    short       stflag;
	//LoginServer����ID���͵���ͬ��LoginServer
	DWORD dwGWorldServerID;
	//AccountServer����ID���͵���ͬ��LoginServer
	DWORD dwLoginServerID;
	char szUserName[ dr_MaxUserName ];

	short stCharaterAmount;
    bool IsForceLogin;
};
struct DBMsgQuerySelChars:public DBMsg
{
	DBMsgQuerySelChars()
	{
		header.dwType = DBMSG_QUERY_SELCHARS;
		header.stLength = sizeof( *this );
		dwAccountID = 0;
		memset(szCharname,0,dr_MaxUserName);
	}
	DWORD dwAccountID;
	char  szCharname[dr_MaxUserName];
};

struct DBMsgQueryAccountChar:public DBMsg
{
	DBMsgQueryAccountChar()
	{
		header.dwType = DBMSG_QUERYACCOUNTCHAR;
		header.stLength = sizeof( *this );
		dwAccountId    = 0;
		dwCharacterId  = 0;
		bQueryAllChars = 0;
        needEnd        = 0;
	}
	uint32 dwAccountId;
	uint32 dwCharacterId;
	uint8  bQueryAllChars;
	short  stWitchSlot;
	uint16 ustLifeCode;
    uint8  needEnd;      // �Ƿ���Ҫ������Ϣ
};

struct DBMsgAckCharInfo : public DBMsg
{ // �˺Ž�ɫ�Ļ�����Ϣ,ѡ���������ʹ��
	DBMsgAckCharInfo()
	{
		header.dwType   = DBMSG_ACKCHAR;
		header.stLength = sizeof( DBMsgAckCharInfo );
        dwDelTimes      = 0;
	}

	int16         stWhichSlot;
	uint32        dwCharacterID;
    uint8         bIsDel;
	SCharBaseInfo baseinfo;
	SCharVisual   visual;
    uint32        nMapId;
    uint32        dwAccountID;
    uint32        dwDelTimes;       // ʣ��ʱ��(��λ��)
};

struct DBMsgEndAckChar:public DBMsg
{ // ������ɫ��ѯ
	DBMsgEndAckChar()
	{
		header.dwType = DBMSG_ENDACKCHAR;
		header.stLength = sizeof(DBMsgEndAckChar);
	}
	DWORD dwAccountID;
};

//������ɫ����
struct DBMsgCreateHeroChar : public DBMsg
{
    enum EFlag
    {
        EF_WithEmpty     = 0,
        EF_WithNormalBag = 1 << 1,
    };

	DBMsgCreateHeroChar()
	{
		header.dwType   = DBMSG_CREATECHAR;
		header.stLength = sizeof( DBMsgCreateHeroChar );
        stWhichSlot     = -1;
        withFlag        = EF_WithEmpty;
	}

	uint32        accoundId;		
	int16         stWhichSlot;
	SCharDBInfo   charinfo;
    uint32        withFlag;
};

//��������ʱ ����Ƿ�ͬ��
struct DBMsgReqCreateCheckName : public DBMsg
{
    enum ECheckType
    {
        ECT_CreateChar, // ������ɫ
        ECT_ChangeName, // ������
    };

	DBMsgReqCreateCheckName()
	{
		header.dwType   = DBMSG_REQ_CREATE_CHECKNAME;
		header.stLength = sizeof( DBMsgReqCreateCheckName );
		checkType       = ECT_CreateChar;
	}
	char  szName[dr_MaxUserName];
    int8  checkType; // �Ƿ��Ǹ������
};

struct DBMsgChangeNameReq : public DBMsg
{
	DBMsgChangeNameReq()
	{
		header.dwType   = DBMSG_CHANGENAMEREQ;
		header.stLength = sizeof( DBMsgChangeNameReq );
	}
	int   PlayerID;
	char  szName[dr_MaxUserName];
};

struct DBMsgChangeNameAck : public DBMsg
{
	DBMsgChangeNameAck()
	{
		header.dwType   = DBMSG_CHANGENAMEACK;
		header.stLength = sizeof( DBMsgChangeNameAck );
	}
	bool Result;
	int   PlayerID;
	char  szName[dr_MaxUserName];
	int GuildID;
};


struct DBMsgAckCreateCheckName : public DBMsg
{
	DBMsgAckCreateCheckName()
	{
		header.dwType = DBMSG_ACK_CREATE_CHECKNAME;
		header.stLength = sizeof( DBMsgAckCreateCheckName );
        memset( szName, 0, sizeof(szName));
	}
    bool bResult;
    int8 checkType; // �Ƿ��Ǹ������
    char szName[dr_MaxUserName];
};

struct DBMsgCreateCharAck : public DBMsg
{ // ACK������ɫ	
	DBMsgCreateCharAck()
	{
		header.dwType = DBMSG_ACKCREATECHAR;
		header.stLength = sizeof( DBMsgCreateCharAck );
        result = ER_Success;
	}

	uint32 result;				
	int16  stWhichSlot;
	uint32 dwCharacterId;
    uint32 accountId;
    int8   charName[dr_MaxPlayerName];
};

//ɾ����ɫ����
struct DBMsgDeleteChar2:public DBMsg
{
	DBMsgDeleteChar2()
	{
		header.dwType = DBMSG_DELETECHAR;
		header.stLength = sizeof( DBMsgDeleteChar2 );
	}
	DWORD dwAccountID;		
	short stWhichSlot;
	DWORD dwCharId;
};

//ACK ɾ����ɫ
struct DBMsgAckDeleteChar2:public DBMsg
{
	DBMsgAckDeleteChar2()
	{
		header.dwType   = DBMSG_ACKDELETECHAR;
		header.stLength = sizeof( DBMsgAckDeleteChar2 );
	}
	bool bSuccessed;
	short stWhichSlot;		
};

//ɾ����ɫ����
struct DBMsgCancelDelChar:public DBMsg
{
    DBMsgCancelDelChar()
    {
        header.dwType = DBMSG_CANCELDELCHAR;
        header.stLength = sizeof( DBMsgCancelDelChar );
    }
    DWORD dwAccountID;		
    short stWhichSlot;
    DWORD dwCharId;
};

//ACK ɾ����ɫ
struct DBMsgAckCancelDelChar:public DBMsg
{
    DBMsgAckCancelDelChar()
    {
        header.dwType   = DBMSG_ACKCANCELDELCHAR;
        header.stLength = sizeof( DBMsgAckCancelDelChar );
    }
    bool bSuccessed;
    short stWhichSlot;		
};

struct DBMsgEnterWorld : public DBMsg
{ // ������Ϸ����
	DBMsgEnterWorld()
	{
		header.dwType            = DBMSG_ENTERWORD;
		header.stLength          = sizeof( DBMsgEnterWorld );
        memset(szIP, 0, sizeof(szIP));
        ucNeedTellClientCharInfo = BV_NotNeedTellClientCharInfo;
        ucNeedUseMessageMapInfo  = BV_NotNeedUseMessageMapInfo;
        dwTeamSessionID          = 0;
	}

	short         stSlot;
	DWORD         dwAccountID;
    DWORD         dwCharacterID;
    char          szIP[20]; // ��½���IP
    unsigned long nMapId;
    int16         nTileX;
    int16         nTileY;
    float         fDir;
    uint32        dwTeamSessionID;
    unsigned char ucNeedTellClientCharInfo;
    unsigned char ucNeedUseMessageMapInfo;
};

struct DBMsgAckEnterWorld : public DBMsg
{ // ACK ���ݿ������Ϸ����
	DBMsgAckEnterWorld()
	{
		header.dwType            = DBMSG_ACKENTERWORD;
		header.stLength          = sizeof( DBMsgAckEnterWorld );		
        nPKValue                 = 0;
        stPKProtectFlag          = 0;
        nStayInHellTime          = 0;
        fDir                     = 0.0f;
        ucNeedTellClientCharInfo = BV_NotNeedTellClientCharInfo;
        ucNeedUseMessageMapInfo  = BV_NotNeedUseMessageMapInfo;
        dwTeamSessionID          = 0;
        nGMLevel                 = 0;
        memset( &runtimeInfo, 0, sizeof(runtimeInfo) );
	}

    unsigned long    bRet;
	DWORD            dwCharacterID;
    unsigned int     nGMLevel;
    int              nPKValue;
    short            stPKProtectFlag;
    unsigned int     nStayInHellTime;           // �Ѿ��ڵ������ε�ʱ��
    unsigned long    nMapId;
    int16            nTileX;
    int16            nTileY;
    float            fDir;
    unsigned char    ucNeedTellClientCharInfo;
    unsigned char    ucNeedUseMessageMapInfo;
    SCharStorageData stStorage;
    SCharDBInfo      charinfo;
    SRuntimeInfo     runtimeInfo;
    uint32           dwTeamSessionID;
	uint32			 dwAccountYuanBaoTotle;
	uint32			 dwAccountYuanBaoStates;//Ԫ��״̬
};

struct DBMsgSaveCharacter : public DBMsg
{ // �����ɫ��Ϣ
	DBMsgSaveCharacter()
	{
		header.dwType     = DBMSG_SAVECHARACTER;
		header.stLength   = sizeof( DBMsgSaveCharacter );
        nPKValue          = 0;
        stPKProtectFlag   = 0;
        accountId         = 0;
        savetype          = EST_None;
	}

	uint32           dwCharacterID;
	uint32           dwSaveTime;       // ����һ�α����ʱ���
	SCharDBInfo      dbInfo;
	SCharStorageData storageInfo;
	bool             bOpenDB;
    int32            nPKValue;         // PKֵ�� 
    int16            stPKProtectFlag;  // PK����ģʽ 
    uint32           nGMLevel;         // GMȨ�޵ȼ� 0Ϊ��Ȩ��
    SRuntimeInfo     runtimeInfo;      // ����ʱ�������
    uint32           accountId;        // �˺�Id
    uint8            savetype;         // ���ֵ�����
};

struct DBAckOperSucc : public DBMsg
{
    DBAckOperSucc()
    {
		header.dwType = DBMSG_ACKOPERSUCC;
		header.stLength = sizeof( *this );
    }
    DWORD dwMsgType;     // ��Ϣ����
    DWORD dwCharacterID; // ��ɫID
    DWORD dwMsgID;       // ���͵Ĳ�����ϢID
};

//�������
struct DBMsgOffline2:public DBMsg
{
	DBMsgOffline2()
	{	
		header.dwType   = DBMSG_OFFLINE;
		header.stLength = sizeof( DBMsgOffline2 );
        nIsJustSwitchGame = 0;
	}
	DWORD dwAccountID;
    char nIsJustSwitchGame;
};

//register account
struct DBMsgRegisterAccounts2:public DBMsg
{
	DBMsgRegisterAccounts2()
	{
		header.dwType   = DBMSG_REGACCOUNTS;
		header.stLength = sizeof(DBMsgRegisterAccounts2);
		memset(szUserName,0,dr_MaxUserName);
		memset(szPassword,0,dr_MaxPassword);
	}
	char szUserName[ dr_MaxUserName ];
	char szPassword[ dr_MaxPassword ];
};

//ack register account
struct DBMsgAckRegisterAccounts2:public DBMsg
{
	enum enum_result_regacc
	{
		regacc_success =0
		,regacc_alreadyhasaccount
		,regacc_failed
	};
	DBMsgAckRegisterAccounts2()
	{
		header.dwType   = DBMSG_ACKREGACC;
		header.stLength = sizeof(DBMsgAckRegisterAccounts2);
	}
	short		stRet;//result
	DWORD		dwAccountID;
};

//delete account
struct DBMsgDeleteAccounts2:public DBMsg
{
	DBMsgDeleteAccounts2()
	{
		header.dwType   = DBMSG_DELACCOUNTS;
		header.stLength = sizeof(DBMsgDeleteAccounts2);
		memset(szUserName,0,dr_MaxUserName);
	}
	char szUserName[ dr_MaxUserName ];
};

//ack delete account
struct DBMsgAckDeleteAccounts2:public DBMsg
{
	DBMsgAckDeleteAccounts2()
	{
		header.dwType   = DBMSG_ACKDELACC;
		header.stLength = sizeof(DBMsgAckDeleteAccounts2);
	}
	bool		bSuccessed;//result
};

//change password
struct DBMsgChangePassword2:public DBMsg
{
	DBMsgChangePassword2()
	{
		header.dwType      = DBMSG_CHANGEPASSWORD;
		header.stLength    = sizeof(DBMsgChangePassword2);
		memset(szUserName,0,dr_MaxUserName);
		memset(szOldPassword,0,dr_MaxPassword);
		memset(szNewPassword,0,dr_MaxPassword);
		bForceChange = false;
	}
	bool bForceChange;                 //force change password when OldPassword is incorrect 
	char szUserName[ dr_MaxUserName ];
	char szOldPassword[ dr_MaxPassword];
	char szNewPassword[ dr_MaxPassword];
};

//ack change password
struct DBMsgAckChangePassword2:public DBMsg
{
	DBMsgAckChangePassword2()
	{
		header.dwType      = DBMSG_ACKCHANGEPASSWORD;
		header.stLength    = sizeof(DBMsgAckChangePassword2);
	}
	bool		bSuccessed;//result
};

//change cashpoint
struct DBMsgChangeCashPoint2:public DBMsg
{
	DBMsgChangeCashPoint2()
	{
		header.dwType      = DBMSG_CHANGECASHPOINT;
		header.stLength    = sizeof(DBMsgChangeCashPoint2);
		memset(szUserName,0,dr_MaxUserName);
		memset(szPassword,0,dr_MaxPassword);
	}
	char szUserName[ dr_MaxUserName ];
	char szPassword[ dr_MaxPassword ];
};

//ack change cashpoint
struct DBMsgAckChangeCashPoint2:public DBMsg
{
	DBMsgAckChangeCashPoint2()
	{
		header.dwType      = DBMSG_ACKCHANGECASHPOINT;
		header.stLength    = sizeof(DBMsgAckChangeCashPoint2);
	}
	short		stRet;//result
};

//
struct DBMsgItemTraceLog : public DBMsg
{
	DBMsgItemTraceLog()
	{
		header.dwType      = DBMSG_ITEMTRACELOG;
		header.stLength    = sizeof(*this);
	}
//		DWORD	dwItemGlobalID;
	//GUID	guid;
	__int64 nBigInt;
	DWORD	dwSrcCharID;
	DWORD	dwDstCharID;
};
//��ѯ�ֿⶨ��Ľṹ  server to dbgate
struct DBMsgReqStorage:public DBMsg
{
	DBMsgReqStorage()
	{
		header.dwType = DBMSG_REQ_STORAGE;
		header.stLength = sizeof(DBMsgReqStorage);
	}
	DWORD dwCharacterId;
};
//
struct DBMsgAckStorage:public DBMsg
{
	DBMsgAckStorage()
	{
		header.dwType = DBMSG_ACK_STORAGE;
		header.stLength = sizeof(DBMsgAckStorage);
	}
	DWORD dwCharacterId;
	SCharStorageData stStorage;
};

struct S2SMsgKickChar : public DBMsg
{ // ֪ͨ����������
    enum EKickReason
    {
        KR_AccountRepeat, // ����Ϸ����������Ϸ���ʺ�
        KR_Ban,           // Ban��ɫ
        KR_KickToConnect, // ���з������У���û�н���Ϸ��������
    };

    enum EConstDefine
    {
        ECD_AckCount = 2,
    };

	S2SMsgKickChar()
	{
		header.dwType   = DBMSG_KICKCHAR;
		header.stLength = sizeof(S2SMsgKickChar);
        dwAccountID     = InvalidLogicNumber;
        usReason        = KR_AccountRepeat;
        time            = 0;
        uchFailAck      = 0;
        //memset( szSessionKey, 0, sizeof(szSessionKey));
		SessionKey = 0;
	}

	uint32 dwAccountID;
    uint8  usReason;
    uint32 time;
    uint8  uchFailAck;         // ʧ�ܻ�Ӧ����
    //char   szSessionKey[32+1]; // SessionKey
	__int64 SessionKey;
};

struct S2SMsgKickCharAck : public DBMsg
{
    S2SMsgKickCharAck()
    {
        header.dwType   = DBMSG_KICKCHARACK;
        header.stLength = sizeof( S2SMsgKickCharAck );
        dwAccountID     = InvalidLogicNumber;
        time            = 0;
        uchFailAck      = 0;
        //memset( szSessionKey, 0, sizeof(szSessionKey));
		SessionKey = 0;
    }

    uint32 dwAccountID;
    uint8  usReason;
    uint32 time;
    uint8  uchFailAck;          // ʧ�ܻ�Ӧ����
    //char   szSessionKey[32+1];  // ��֤��
	__int64 SessionKey;
};

struct DBMsgAccountState:public DBMsg
{
	enum
	{
		state_offline, // ����
		state_login,   // ��½
		state_select,  // ѡ��
		state_play,    // ��Ϸ
        state_change_gameserver // �з�����
	};
	DBMsgAccountState()
	{
		header.dwType = DBMSG_ACCOUNTSTATE;
		header.stLength = sizeof(DBMsgAccountState);
	}
	DWORD dwAccountID;
	short shState;
};

struct DBMsgAckAccountState:public DBMsg
{
	DBMsgAckAccountState()
	{
		header.dwType = DBMSG_ACK_ACCOUNTSTATE;
		header.stLength = sizeof(DBMsgAckAccountState);
	}
	DWORD dwAccountID;
	short shRet;
    short shState;
};

struct DBMsgSaveLevel : public DBMsg
{
    DBMsgSaveLevel()
    {
        header.dwType = DBMSG_SAVELEVEL;
        header.stLength = sizeof(*this);
    }
    DWORD dwCharacterID;
    unsigned int nLevel;
};

struct DBMsgSaveExp : public DBMsg
{
    DBMsgSaveExp()
    {
        header.dwType = DBMSG_SAVEEXP;
        header.stLength = sizeof(*this);
    }
    DWORD dwCharacterID;
    DWORD nExp;
};

struct DBMsgSkillExp : public DBMsg
{
    DBMsgSkillExp()
    {
        header.dwType = DBMSG_SAVESKILLEXP;
        header.stLength = sizeof(*this);
    }
    DWORD dwCharacterID;
    DWORD nSkillExp;
};

struct DBMsgAddItem : public DBMsg
{
    DBMsgAddItem()
    {
        header.dwType = DBMSG_ADDITEM;
        header.stLength = sizeof(*this);
    }
    DWORD dwCharacterID;
    short type;         //��Ʒ�������
    unsigned int nPos;              //���������е�λ��
    SCharItem item;
};

struct DBMsgRemoveItem : public DBMsg
{
    DBMsgRemoveItem()
    {
        header.dwType = DBMSG_REMOVEITEM;
        header.stLength = sizeof(*this);
    }
    DWORD dwCharacterID;
    short type;         //��Ʒ�������
    unsigned int nPos;              //���������е�λ��
    __int64 itemid;
};

struct DBMsgItemAttribChange : public DBMsg
{
    DBMsgItemAttribChange()
    {
        header.dwType = DBMSG_ITEMATTRIBCHANGE;
        header.stLength = sizeof(*this);
    }
    DWORD dwCharacterID;
    short type;         //��Ʒ�������
    unsigned int nPos;              //���������е�λ��
    SCharItem item;
};

struct DBMsgItemAmountChange : public DBMsg
{
    DBMsgItemAmountChange()
    {
        header.dwType = DBMSG_ITEMAMOUNTCHANGE;
        header.stLength = sizeof(*this);
    }
    DWORD dwCharacterID;
    short type;         //��Ʒ�������
    unsigned int nPos;              //���������е�λ��
    __int64 itemid;                 //��ƷID
    unsigned int nAmount;           //��Ʒ����
};

struct DBMsgItemLockStatusChange : public DBMsg
{
    DBMsgItemLockStatusChange()
    {
        header.dwType = DBMSG_ITEMLOCKSTATUSCHANGE;
        header.stLength = sizeof(*this);
    }
    DWORD dwCharacterID;
    short type;         //��Ʒ�������
    unsigned int nPos;              //���������е�λ��
    __int64 itemid;                 //��ƷID
    bool IsLock;                    //�Ƿ���ס
};

struct DBMsgReqAccountBilling : public S2SMsg
{
    enum EOpType
    {
        ET_ExchangeJinDing, // �һ���
        ET_QueryPoint,      // ��ѯ����
    };

    DBMsgReqAccountBilling()
    {
        header.dwType = DBMSG_REQ_ACCOUNT_BILLING;
        header.stLength = sizeof(*this);
        guid  = 0;
        op    = ET_QueryPoint;
        value = 0;
    }
    uint32 guid;   // �ʺ�guid
    uint8  op;
    uint32 value;  // ʹ�õĵ���
};

struct DBMsgAckAccountBilling : public S2SMsg
{
    DBMsgAckAccountBilling()
    {
        header.dwType   = DBMSG_ACK_ACCOUNT_BILLING;
        header.stLength = sizeof(*this);
        guid  = 0;
        point = 0;
        op    = DBMsgReqAccountBilling::ET_QueryPoint;
    }
    uint8  op;
    uint32 result; // result
    uint32 guid;   // �ʺ�guid
    uint32 point;  // ����
    uint32 value;  // ʹ�õĵ���
};

struct DBMsgReqAccountBillingOp : public S2SMsg
{   
    enum EBillingOpType
    {
        EBOT_Sub,
    };

    DBMsgReqAccountBillingOp()
    {
        header.dwType   = DBMSG_REQ_ACCOUNT_BILLING_OP;
        header.stLength = sizeof(*this);
    }

    uint8  op;     // ����
    uint32 guid;   // �ʺ�guid
    uint32 point;  // ����
};

struct DBMsgLog : public DBMsg
{
    DBMsgLog()
    {
        header.dwType = DBMSG_LOG;
        header.stLength = sizeof(*this);
    }
    char szCharName[dr_MaxPlayerName];
    WORD wCharID;
    char szDate[dr_LengthDate];
    char szTime[dr_LengthDate];
    char szLog[dr_MaxChatString];
};

struct DBAccountWallowInfoReq: public DBMsg
{
    // add by ZhangQi for ������ϵͳ 2010/07/07
   enum {
        ACCOUNT_TYPE_CHILD,
        ACCOUNT_TYPE_ADULT,
    };

    DBAccountWallowInfoReq()
    {
        header.dwType = DBMSG_ACCOUNTWALLOWINFO_REQ;
        header.stLength = sizeof( DBAccountWallowInfoReq );
        accountType = ACCOUNT_TYPE_ADULT;     // add by ZhangQi for ������ϵͳ 2010/07/07
    }

    bool IsChild(){ return ACCOUNT_TYPE_CHILD == accountType ;}

    uint32 accountId;   
    uint32 accountType;    //add by ZhangQi for ������ϵͳ 2010/07/07
};

struct DBAccountWallowInfoAck: public DBMsg
{
    DBAccountWallowInfoAck()
    {
        header.dwType = DBMSG_ACCOUNTWALLOWINFO_ACK;
        header.stLength = sizeof( DBAccountWallowInfoAck );
        accountId                 = 0;
        onlineMinuteTimeForWallow = 0;
        offMinuteTimeForWallow    = 0;
    }
    uint32  accountId;
    uint32  onlineMinuteTimeForWallow; // �����ۼ� ��λ����
    uint32  offMinuteTimeForWallow;    // �����ۼ� ��λ����
    __int64 lastOfflineTime;           // ��ʵ���ͷ�ʱ��

    //start add by ZhangQi for ������ϵͳ 2010/07/07
    uint32  bOpenAntiAddiction;          //�Ƿ�򿪷�����ϵͳ
    AntiAddictionTime antiAddictionTime;   //������ϵͳʱ������
   // end add

};

struct DBAccountWallowInfoSave : public DBMsg
{
    DBAccountWallowInfoSave()
    {
        header.dwType = DBMSG_ACCOUNTWALLOWINFO_SAVE;
        header.stLength = sizeof( DBAccountWallowInfoSave );
        accountId                 = 0;
        onlineMinuteTimeForWallow = 0;
        offMinuteTimeForWallow    = 0;
    }
    uint32  accountId;
    uint32  onlineMinuteTimeForWallow; // �����ۼ� ��λ����
    uint32  offMinuteTimeForWallow;    // �����ۼ� ��λ����
    __int64 lastOfflineTime;           // ��ʵ���ͷ�ʱ��
};


struct DBMsgJiFengShopItemsListReq : public DBMsg
{ // �����̳ǵ��߲�ѯ
    DBMsgJiFengShopItemsListReq()
    {
        header.dwType   = DBMSG_JIFENGSHOPITEMSLISTREQ;
        header.stLength = sizeof( DBMsgJiFengShopItemsListReq );
        accountId = 0;
    }
    uint32 accountId;
};

struct DBMsgJiFengShopItemsListAck : public DBMsg
{ // �����̳ǵ����б�
    enum EConstDefine
    {
        ECD_MaxJiFengItemCount = 200,
    };

    DBMsgJiFengShopItemsListAck()
    {
        isNew = 1;
        Reset();
        header.dwType   = DBMSG_JIFENGSHOPITEMSLISTACK;
        header.stLength = sizeof( DBMsgJiFengShopItemsListAck ) - sizeof(SJiFengItemRecordServer) * ( ECD_MaxJiFengItemCount - count );        
    }

    void Reset()
    {
        count = 0;
        memset( items, 0, sizeof(items));
    }

    bool AddItem( const SJiFengItemRecordServer& itemRecord )
    {
        if ( count >= ECD_MaxJiFengItemCount )
        { return false; }

        items[count++] = itemRecord;
        header.stLength = sizeof( DBMsgJiFengShopItemsListAck ) - sizeof(SJiFengItemRecordServer) * ( ECD_MaxJiFengItemCount - count );
        return true;
    }

    bool IsFull()
    { return count >= ECD_MaxJiFengItemCount; }

    uint8                   isNew; // �Ƿ����µ�
    uint16                  count;
    SJiFengItemRecordServer items[ ECD_MaxJiFengItemCount ];
};

struct DBMsgJiFengShopItemsGainReq : public DBMsg
{ // �����̳ǵ�����ȡ
    DBMsgJiFengShopItemsGainReq()
    {   
        accountId       = 0;
        count           = 0;

        header.dwType   = DBMSG_JIFENGSHOPITEMSGAINREQ;        
        header.stLength = sizeof( DBMsgJiFengShopItemsGainReq ) - sizeof(uint32) * ( gJiFengGainMaxCount - count );
    }

    bool AddId( const uint32& id )
    {
        if ( count >= gJiFengGainMaxCount )
        { return false; }

        ids[count++] = id;
        header.stLength = sizeof( DBMsgJiFengShopItemsGainReq ) - sizeof(uint32) * ( gJiFengGainMaxCount - count );
        return true;
    }

    bool IsFull()
    { return count >= gJiFengGainMaxCount; }

    bool IsInIds( uint32 id )
    {
        for ( size_t i=0; i<count; ++i)
        {
            if ( id == ids[i] )
            { return true;}
        }
        return false;
    }

    void RecalLength()
    { header.stLength = sizeof( DBMsgJiFengShopItemsGainReq ) - sizeof(uint32) * ( gJiFengGainMaxCount - count );}

    uint32 accountId;
    uint16 count;
    uint32 ids[gJiFengGainMaxCount];
};

struct DBMsgJiFengShopItemsGainAck : public DBMsg
{
    enum EConstDefine
    {
        ECD_MaxJiFengItemCount = 100,
    };

    DBMsgJiFengShopItemsGainAck()
    {
        Reset();
        header.dwType   = DBMSG_JIFENGSHOPITEMSGAINACK;
        header.stLength = sizeof( DBMsgJiFengShopItemsGainAck ) - sizeof(SJiFengItemRecordServer) * ( ECD_MaxJiFengItemCount - count );        
    }

    void Reset()
    {
        count = 0;
        memset( items, 0, sizeof(items));
    }

    bool AddItem( const SJiFengItemRecordServer& itemRecord )
    {
        if ( count >= ECD_MaxJiFengItemCount )
        { return false; }

        items[count++] = itemRecord;
        header.stLength = sizeof( DBMsgJiFengShopItemsGainAck ) - sizeof(SJiFengItemRecordServer) * ( ECD_MaxJiFengItemCount - count );
        return true;
    }

    bool IsFull()
    { return count >= ECD_MaxJiFengItemCount; }

    uint16                  count;
    SJiFengItemRecordServer items[ ECD_MaxJiFengItemCount ];
};

struct MsgReqInitData : public Msg
{
    MsgReqInitData()
    {
        header.dwType   = GS2DB_REQ_INIT_DATA;
        header.stLength = sizeof( MsgReqInitData );
    }
};

struct MsgAckInitData : public Msg
{
    MsgAckInitData()
    {
        header.dwType   = DB2GS_ACK_INIT_DATA;
        header.stLength = sizeof( MsgAckInitData );
    }

    //��������������
    uint32  bOpenAntiAddiction;          //�Ƿ�򿪷�����ϵͳ
    AntiAddictionTime antiAddictionTime; //������ϵͳʱ������
};

struct DB2DBNotifyFileDBSaveChar : public DBMsg
{
    DB2DBNotifyFileDBSaveChar()
    {
        header.dwType   = DB2DB_NOTIFYFILEDBSAVECHAR;
        header.stLength = sizeof( DB2DBNotifyFileDBSaveChar );
        charId = 0;
        lifeId = 0;
    }

    uint32 charId;
    uint32 lifeId;
};

struct DBMsgPetBreedQueryReq : public DBMsg
{
    DBMsgPetBreedQueryReq()
    {
        header.dwType   = DBMSG_PETBREEDQUERYREQ;
        header.stLength = sizeof( DBMsgPetBreedQueryReq );
    }

    uint32  dwDBCharacterID;    //Ŀ���DB ID
    int64   nPetGuid       ;    
};

struct DBMsgPetBreedQueryAck : public DBMsg
{
    DBMsgPetBreedQueryAck()
    {
        header.dwType   = DBMSG_PETBREEDQUERYACK;
        header.stLength = sizeof( DBMsgPetBreedQueryAck );
    }
    
    uint32  dwDBCharacterID;    //Ŀ���DB ID
    int64   nPetGuid       ;    
    bool    bIsAcquired    ;    //�Ƿ�����ȡ
};

struct DBMsgShopping : public DBMsg
{
	DBMsgShopping()
	{
		header.dwType = DBMSG_SHOPPING;
		header.stLength = sizeof(DBMsgShopping);
	}
	uint32 account_id;
	uint32 character_id;
	uint16 item_id;
	uint16 item_count;
	uint32 cost_money;
	uint32 Unit_price;//����
	uint8  flag; //lyh++ ���� 0 Ԫ�� 1��� 2 ���� ����2��ֵ�Ǹ����ֻ��߰����
	uint32 oldValue;
	uint32 newValue;
};



struct DBMsgOperateAccountMoney:public DBMsg
{
	DBMsgOperateAccountMoney()
	{
		header.stLength = sizeof(DBMsgOperateAccountMoney);
		header.dwType = DBMSG_OPERATEACCOUNTMONEY;
	}
	uint32 account_id;
	uint32 character_id;
	uint16 operate_flag;//0:�Ǽ�,1:�Ǽ�,2:������
	uint32 modify_money;
};

//lyh�����˺Ż���
struct DBMsgOperateAccountConsumeScore:public DBMsg
{
	DBMsgOperateAccountConsumeScore()
	{
		header.stLength = sizeof(DBMsgOperateAccountConsumeScore);
		header.dwType = DBMSG_OPCONSUMESCORE;
	}
	uint32 account_id;
	uint32 character_id;
	uint16 operate_flag;//0:�Ǽ�,1:�Ǽ�,2:������
	uint32 modify_money;
};


struct DBMsgSetBillingMoney:public DBMsg
{
	DBMsgSetBillingMoney()
	{
		header.stLength = sizeof(DBMsgSetBillingMoney);
		header.dwType = DBMSG_SETBILLINGMONEY;
	}
	uint32 account_id;
	uint32 character_id;
	uint32 money;
};

struct DBMsgSetConsumeScore:public DBMsg
{
	DBMsgSetConsumeScore()
	{
		header.stLength = sizeof(DBMsgSetConsumeScore);
		header.dwType = DBMSG_SETCONSUMESCORE;
	}
	uint32 account_id;
	uint32 character_id;
	uint32 money;
};


struct DB2DBCash:public DBMsg
{
	DB2DBCash()
	{
		header.stLength = sizeof(DB2DBCash);
		header.dwType = DB2DB_Cash;

		memset(sn,0,17);
	}

	char	sn[17];
	uint32	account_id;
	int		money;
};

//��BillingServerDefine.h�е�result����һ��Ҫһ��
enum eDB2DBCashResult
{
	eDB2DBCashResult_succ = 0,        //��ֵ�ɹ�
	eDB2DBCashResult_cashed = 1,      //�Ѿ���ֵ�ɹ�
	eDB2DBCashResult_checkerror = 2,  //����ȷ��ʧ��
	eDB2DBCashResult_max               //δ֪����
};

struct DB2DBCashResult:public DBMsg
{
	DB2DBCashResult()
	{
		header.stLength = sizeof(DB2DBCashResult);
		header.dwType = DB2DB_CashResult;
	}

	char sn[17];
	char result;
	int  money;
	uint32 account_id;
	uint32 all_money;
	uint32 account_yuanbao_totle;
	uint32 account_yuanbao_states;
};

struct DB2DBConsumeScore:public DBMsg
{
	DB2DBConsumeScore()
	{
		header.stLength = sizeof(DB2DBConsumeScore);
		header.dwType = DB2DB_ConsumeScore;

		memset(sn,0,17);
	}

	char	sn[17];
	uint32	account_id;
	int		money;
};

struct DB2DBConsumeScoreResult:public DBMsg
{
	DB2DBConsumeScoreResult()
	{
		header.stLength = sizeof(DB2DBConsumeScoreResult);
		header.dwType = DB2DB_ConsumeScoreResult;
	}

	char sn[17];
	char result;
	int  money;
	uint32 account_id;
	uint32 all_money;
};

struct GS2DBUpdateYuanBaoData : public DBMsg
{
	GS2DBUpdateYuanBaoData()
    {
        header.dwType   = GS2DB_UPDATEYUANBAODATA;
        header.stLength = sizeof( GS2DBUpdateYuanBaoData );
		AccountID = 0;
		States = 0;
    }
	unsigned int AccountID;
	unsigned int States;
};
struct DB2GSUpdateYuanBaoData : public DBMsg
{
	DB2GSUpdateYuanBaoData()
    {
        header.dwType   = DB2GS_UPDATEYUANBAODATA;
        header.stLength = sizeof( DB2GSUpdateYuanBaoData );
    }
	unsigned int AccountID;
	unsigned int States;
	bool result;
};

struct GS2DBUpdatePlayerPoint : public DBMsg
{
	GS2DBUpdatePlayerPoint()
    {
        header.dwType   = GS2DB_UPDATEPLAYERPOINT;
        header.stLength = sizeof( GS2DBUpdatePlayerPoint );
		ID = 0;
		States = 0;
		Op = 0;
		Value = 0;
		PlayerID = 0;
    }
	unsigned int PlayerID;
	unsigned int ID;
	unsigned int Op;
	unsigned int States;
	unsigned int Value;
};
struct DB2GSUpdatePlayerPoint : public DBMsg
{
	DB2GSUpdatePlayerPoint()
    {
        header.dwType   = DB2GS_UPDATEPLAYERPOINT;
        header.stLength = sizeof( DB2GSUpdatePlayerPoint );
		ID = 0;
		States = 0;
		Op = 0;
		Value = 0;
		PlayerID = 0;
		ChangeValue = 0;
    }
	unsigned int PlayerID;
	unsigned int ID;
	unsigned int States;
	unsigned int Op;
	unsigned int Value;
	unsigned int ChangeValue;
};
#pragma pack(pop) 
