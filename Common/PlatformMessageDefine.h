#ifndef __PLATFORMMESSAGEDEFINE_H__
#define __PLATFORMMESSAGEDEFINE_H__

#pragma once
#include "GlobalDef.h"
#include "PlatformDefine.h"
#include "DBMessageDefine.h"

enum EPlatformMessageDefineO
{
	PFMSG_BEGIN         = 1,
//	PFMSG_ITEMEXCHANGE,       // ʵ��һ�   

	PFMSG_SERVERSTATUS_REQ,   // �����������״̬
	PFMSG_SERVERSTATUS_ACK,   // Ӧ���������״̬

	PFMSG_ADDITEM_REQ,        // �͵���
	PFMSG_ADDITEM_ACK,        // �͵��߻���

	//PFMSG_GMKICKPLAYER_REQ,   // �߽�ɫ
	//PFMSG_GMKICKPLAYER_ACK,

	PFMSG_RELOADTRADESHOP_REQ,      // �������̳����¼���
	PFMSG_SHUTDOWNSERVERS_REQ,      // ����ط�ά��
	PFMSG_CHANGEMAPEXPRATE_REQ,     // �����޸ĵ�ͼ����

	PFMSG_GMBROADCAST_REQ,          //ok ������
	PFMSG_GMOPCHATONOFF,            //ok �����¼����
	PFMSG_C2PTELLSERVERID,          //ok center server����platform�Լ���ID
	PFMSG_P2CREGERES,               //ok platform����center ע����,�����Ƿ����ʹ��

	PFMSG_SENDMAIL,				//ok platform�������͸�ĳ����ɫ�ʼ�
	PFMSG_ASKFORPRESENT,           //ok ����present
	PFMSG_ASKFORACTIVITY,		//ok ����activity

	PFMSG_MODIFY_ERROR,        // ok �������󷵻�ֵ,ͳһ����

	PFMSG_BANACCOUNT,			//�����ʺŵ�¼
	PFMSG_BANMACADRESS,			//����MAC��¼

	PFMSG_REQ_EPISTARPOINT,		//center server tell platform ���� ��Ԫ����
	PFMSG_ACK_EPISTARPOINT,		//platform tell center server ���� ��Ԫ���� ������Ϣ
	//PFMSG_GMUPDATEFILTERSTRING_REQ, // ���߸��¹��˴ʿ�
	//PFMSG_GMOPENEXPMUL_REQ,         // ��˫������
	//PFMSG_GMMONSTEROP_REQ,          // ɱ������ �ٻ�����
	/*PFMSG_ADDPOINTS,
	PFMSG_ADDPOINTS_ACK,*/
	//PFMSG_INFOQUERY_REQ = 50, // ��ѯ ���ֿ� ���ȼ� �����Ϣ ����
	//PFMSG_INFOQUERY_ACK,      // ��ѯ ���ֿ� ���ȼ� �����Ϣ ����
	//PFMSG_CREATECHAR_REQ,     // ������ɫ
	//PFMSG_CREATECHAR_ACK,     // ������ɫ����
	//PFMSG_GMGETPLAYERINFO_REQ,      // ��ѯ��ɫ��Ϣ�����ԣ���Ǯ���𶧣���Ʊ���ȼ���װ�������������ܣ��ֿ⣬���[���۽�ɫ�Ƿ����ߣ���������ߣ��������ݿ��е���Ϣ]
	//PFMSG_GMGETPLAYERINFO_ACK,
	//PFMSG_GMGETPLAYERMAPINFO_REQ,   // ��ѯ��ɫ�Ƿ����ߣ����������ڵ�ͼ��λ��
	//PFMSG_GMGETPLAYERMAPINFO_ACK,
	//PFMSG_GMMOVEPLAYER_REQ,         // �ƶ���ɫ����
	//PFMSG_GMMOVEPLAYER_ACK,
	//PFMSG_GMGETORGANIZEINFO_REQ,    // ��ѯ�����Ϣ
	//PFMSG_GMGETORGANIZEINFO_ACK,
	//PFMSG_GMGETITEMINFO_REQ,        // ��ѯ��Ʒ��������Ʒid��������Ʒ���Եȣ�
	//PFMSG_GMGETITEMINFO_ACK,
	//PFMSG_GMCHANGEPLAYERINFO_REQ,   // �ı��ɫ���ԣ��ȼ������飬���ܣ�
	//PFMSG_GMCHANGEPLAYERINFO_ACK,
	//PFMSG_GMBANCHAT_REQ,            // ���ԣ����
	//PFMSG_GMBANCHAT_ACK,
	//PFMSG_GMCREATEITEMTOPLAYER_REQ, // ���ɵ��߸�ĳ��ɫ
	//PFMSG_GMCREATEITEMTOPLAYER_ACK,

	PFMSG_END
};

#pragma pack( push, 1 )

//struct MsgPFAddPoints : public Msg
//{ // ƽ̨��ֵ
//    MsgPFAddPoints()
//    {
//        header.dwType   = PFMSG_ADDPOINTS;
//        header.stLength = sizeof(*this);
//
//        memset( &info, 0, sizeof(info));
//    }
//
//    SAddPoints info;
//};

//struct MsgPFAddPointsAck : public Msg
//{ // ƽ̨��ֵ
//    MsgPFAddPointsAck()
//    {
//        header.dwType   = PFMSG_ADDPOINTS_ACK;
//        header.stLength = sizeof(*this);
//
//        result = ER_Success;
//        guid   = 0;
//        points = 0;
//        memset( &typesn, 0, sizeof(typesn));
//    }
//
//    uint32 result;     // ���
//    uint32 guid;       // �û�id
//    uint32 points;     // ����
//    int8   typesn[32]; // ������
//};

//struct MsgPFInfoQueryReq : public Msg
//{ // ��ƽ̨��ѯ��Ϣ
//
//    MsgPFInfoQueryReq()
//    {
//        header.dwType   = PFMSG_INFOQUERY_REQ;
//        header.stLength = sizeof( MsgPFInfoQueryReq );
//    }
//    uint32 guid;      // �û�id
//    uint8  queryType;
//};

//struct MsgPFInfoQueryAck : public Msg
//{ // ��ƽ̨��ѯ��Ϣ����
//    MsgPFInfoQueryAck()
//    {
//        header.dwType   = PFMSG_INFOQUERY_ACK;
//        header.stLength = sizeof( MsgPFInfoQueryAck );
//    }
//
//    uint32 result;   // ���
//    uint32 guid;     // �û�id
//    uint8  querType; // ��ѯ����
//};

//struct MsgPFItemExchange : public Msg
//{ // ��ƽ̨�ύʵ����Ϣ
//	MsgPFItemExchange()
//	{
//		header.dwType   = PFMSG_ITEMEXCHANGE;
//		header.stLength = sizeof(*this);
//	}
//	uint32  guid;             // �ʺ�
//	int8    charName[33];     // ��ɫ��
//	uint16  itemId;           // ����id
//	int64   itemguid;         // ����guid
//	int8    itemName[17];     // ��������
//	int8    linkman[17];      // ��ϵ��
//	int8    telephone[13];    // �绰
//	int8    email[50];        // email
//	int8    identityCard[19]; // ���֤
//	int8    passport[33];     // �ʺ�����
//};

//struct MsgPFCreateCharReq : public Msg
//{ // ���󴴽���ɫ
//    MsgPFCreateCharReq()
//    {
//        header.dwType   = PFMSG_CREATECHAR_REQ;
//        header.stLength = sizeof( MsgPFCreateCharReq );
//        
//        level   = 0;
//        byMonth = 0;
//        byDay   = 0;
//        bagid   = 0;
//    }
//    uint32  guid;         // �ʺ�
//    uint8   sex;          // �Ա�
//    uint8   profession;   // ��ɫְҵ
//    uint8   country;      // ����
//    int8    charName[33]; // ��ɫ��
//    uint16  level  ;      // �ȼ�
//    uint8   byMonth;      // ������
//    uint8   byDay  ;      // ������
//    uint16  bagid  ;      // ���Id
//};
//
//struct MsgPFCreateCharAck : public Msg
//{ // ���󴴽���ɫ
//    MsgPFCreateCharAck()
//    {
//        header.dwType   = PFMSG_CREATECHAR_ACK;
//        header.stLength = sizeof( MsgPFCreateCharAck );
//    }
//    uint32  result;       // 
//    uint32  guid;         // �ʺ�
//    int8    charName[33]; // ��ɫ��
//};

struct MsgPFAddItemReq : public Msg
{ // ���������Ʒ
	MsgPFAddItemReq()
	{
		header.dwType   = PFMSG_ADDITEM_REQ;
		header.stLength = sizeof( MsgPFAddItemReq );
	}

	uint32            accountId; // �ʺ�
	SJiFengItemRecordPlatform item;      // ��Ʒ��¼
};

struct MsgPFAddItemAck : public Msg
{ // ���������Ʒ
	enum EResult
	{
		ER_Success,
		ER_SnHaveExist,
	};

	MsgPFAddItemAck()
	{
		header.dwType   = PFMSG_ADDITEM_ACK;
		header.stLength = sizeof( MsgPFAddItemAck );
		result = ER_Success;
		memset( sn, 0, sizeof(sn) );
	}

	uint32 result;    // ���
	uint32 accountId; // �ʺ�Id
	int8   sn[32];    // ���к�
	uint8  itemType;  // ��Ʒ����
	uint16 itemid;    // ��ƷId
	uint16 itemCount; // ��Ʒ����
};

// GM
//struct MsgPFGmKickPlayerReq : public Msg
//{ // GM ����
//	MsgPFGmKickPlayerReq()
//	{
//		header.dwType   = PFMSG_GMKICKPLAYER_REQ;
//		header.stLength = sizeof( MsgPFGmKickPlayerReq );
//	}
//	uint32  accountGuid;  // �ʺ�
//	uint32  chardbId;     // ��ɫId
//	int8    charName[33]; // ��ɫ��
//	uint32  time;         // s ��
//};

//struct MsgPFGmKickPlayerAck : public Msg
//{ // GM ����
//	MsgPFGmKickPlayerAck()
//	{
//		header.dwType   = PFMSG_GMKICKPLAYER_ACK;
//		header.stLength = sizeof( MsgPFGmKickPlayerAck );
//		result = ER_Success;
//	}
//
//	uint32 result;
//	uint32 accountGuid;  // �ʺ�
//	uint32 chardbId;     // ��ɫId
//	int8   charName[33]; // ��ɫ��
//	uint32 time;         // s ��
//};

struct MsgPFGMBroadcastReq : public Msg
{ // GM ����
	enum EConstDefine
	{
		CD_ContentMaxSize = 256,
	};

	MsgPFGMBroadcastReq()
	{
		header.dwType   = PFMSG_GMBROADCAST_REQ;
		header.stLength = sizeof( MsgPFGMBroadcastReq );
		memset( content, 0, CD_ContentMaxSize );
	}
	int8 content[CD_ContentMaxSize];
};

struct MsgPFServerStatusReq : public Msg
{
	MsgPFServerStatusReq()
	{
		header.dwType   = PFMSG_SERVERSTATUS_REQ;
		header.stLength = sizeof( MsgPFServerStatusReq );
	}
};

struct MsgPFServerStatusAck : public Msg
{
	MsgPFServerStatusAck()
	{
		nCount = 0;
		header.dwType   = PFMSG_SERVERSTATUS_ACK;
		header.stLength = sizeof( MsgPFServerStatusAck ) - sizeof(ServerStatus) * ( ECD_MaxCount - nCount );
	}

	enum EConstDefine
	{
		ECD_MaxCount = 10,
	};

	struct ServerStatus
	{
		ServerStatus()
		{
			memset( szName, 0, sizeof( szName ) );
		}

		int8 szName[37]; // ����������
		uint8 uchStatus; // 1 = �е㿨 2 = ����Ӧ( may be ���� )
	};

	uint8        nCount; // nCount = 0 ˵�����з���������
	ServerStatus xStatus[ECD_MaxCount];

	void AddServerStatus( const char* pszName, uint8 uchValue )
	{
		if ( nCount >= ECD_MaxCount )
		{ return; }

		strncpy_s( xStatus[nCount].szName, sizeof( xStatus[nCount].szName ), pszName, sizeof( xStatus[nCount].szName ) - 1 );
		xStatus[nCount].uchStatus = uchValue;
		++nCount;
		header.stLength = sizeof( MsgPFServerStatusAck ) - sizeof(ServerStatus) * ( ECD_MaxCount - nCount );
	}
};

struct MsgPFGMReloadTradeShop : public Msg
{ // GM �������ؽ��̳�����
	MsgPFGMReloadTradeShop()
	{
		header.dwType   = PFMSG_RELOADTRADESHOP_REQ;
		header.stLength = sizeof( MsgPFGMReloadTradeShop );
	}
};

struct MsgPFGMShutdownServersReq : public Msg
{ // GM �����ر���Ϸ��������
	MsgPFGMShutdownServersReq()
	{
		header.dwType      = PFMSG_SHUTDOWNSERVERS_REQ;
		header.stLength    = sizeof( MsgPFGMShutdownServersReq );
		delayTime = 0;
	}

	uint32 delayTime; // ��λ��
};

struct MsgPFGMChangeMapExpRateReq : public Msg
{ // GM ������Ϸ���������ͼ�������
	MsgPFGMChangeMapExpRateReq()
	{
		header.dwType        = PFMSG_CHANGEMAPEXPRATE_REQ;
		header.stLength      = sizeof( MsgPFGMChangeMapExpRateReq );
		mapConfigId = InvalidLogicNumber;
		fExpRate    = 1.0f;
	}

	uint32 mapConfigId; // 
	float  fExpRate;    // ��λ 1.0 == 100% 
};

struct MsgPFGMOPChatOnOff : public Msg
{ // GM �������¼����
	MsgPFGMOPChatOnOff()
	{
		header.dwType        = PFMSG_GMOPCHATONOFF;
		header.stLength      = sizeof( MsgPFGMOPChatOnOff );
		isOpen      = 0;
	}    
	uint8  isOpen;
};

struct MsgC2PTellServerid:public Msg
{
	MsgC2PTellServerid()
	{
		header.dwType        = PFMSG_C2PTELLSERVERID;
		header.stLength      = sizeof( MsgC2PTellServerid );
		server_id = -1;
	}
	int server_id;
};

enum eRegeResult
{
	eRegeResult_fail = 0,//ʧ��
	eRegeResult_succ,    //�ɹ�
	eRegeResult_Refrain, //�ظ�ע��
	eRegeResult_max
};

struct MsgP2CRegeResult:public Msg
{
	MsgP2CRegeResult()
	{
		header.dwType        = PFMSG_P2CREGERES;
		header.stLength      = sizeof( MsgC2PTellServerid );
	}
	char _result;
};

struct MsgPFSendMail:public Msg
{
	MsgPFSendMail()
	{
		header.dwType        = PFMSG_SENDMAIL;
		header.stLength      = sizeof( MsgPFSendMail );
	}
	uint32 characterid		;//��ɫDB ID
	char   charactername[ETaskInfo_NameMaxLength]	;
	char   title[ETaskInfo_TileMaxCount]			;//�ʼ�����
	char   content[ETaskInfo_MailContentMax]			;//�ʼ�����
	uint32 money			;//����
	uint16 itemid			;//��ƷID
	uint16 itemcount		;//��Ʒ����
};

struct MsgPFAskForPresent:public Msg
{
	MsgPFAskForPresent()
	{
		header.dwType = PFMSG_ASKFORPRESENT;
		header.stLength = sizeof(MsgPFAskForPresent);
	}
	uint32 characterid;
	uint32 accountid;
	char   sn[33];
	char   charactername[33];
};

struct MsgPFAskForActivity:public Msg
{
	MsgPFAskForActivity()
	{
		header.dwType = PFMSG_ASKFORACTIVITY;
		header.stLength = sizeof(MsgPFAskForActivity);
	}
	uint32 characterid;
	uint32 accountid;
	int32  _type;
	char   charactername[33];
};

struct MsgPFModifyError:public Msg
{
	MsgPFModifyError()
	{
		header.dwType = PFMSG_MODIFY_ERROR;
		header.stLength = sizeof(MsgPFModifyError);
	}
	uint32 characterid;
	uint32 accountid;
	int16  result;//���
};

struct MsgPFBlockAccount:public Msg
{
	MsgPFBlockAccount()
	{
		header.dwType = PFMSG_BANACCOUNT;
		header.stLength = sizeof(MsgPFBlockAccount);
	}
	uint32 accountid;
	char   name[MAX_NAME_STRING];
	uint32 blocktime;
};

struct MsgPFBlockMac:public Msg
{
	MsgPFBlockMac()
	{
		header.dwType = PFMSG_BANMACADRESS;
		header.stLength = sizeof(MsgPFBlockMac);
	}
	char   cMac[MAC_LENGTH];
	uint32 blocktime;
};

struct MsgPFEpistarPoint:public Msg
{
	MsgPFEpistarPoint()
	{
		header.stLength = sizeof(MsgPFEpistarPoint);
		header.dwType = PFMSG_REQ_EPISTARPOINT;
	}
	uint32 accountid;
	uint32 characterid;
	uint8  _type;			//������
	uint16 nItemId;
	uint16 nPoint;
	char   charactername[ETaskInfo_NameMaxLength];
};

struct MsgPFEpistarPointACK:public Msg
{
	MsgPFEpistarPointACK()
	{
		header.stLength = sizeof(MsgPFEpistarPointACK);
		header.dwType = PFMSG_ACK_EPISTARPOINT;
	}
	uint32 accountid;
	uint32 characterid;
	uint16 nItemId;
};

//////////////////////////////////////////////////////////////////////////
//enum EPlatformMessageDefine
//{
//    P2CS_ADDPAYREQ = PLATFORM_MESSAGE_BEGIN, // ��ֵ����
//    CS2P_ADDPAYACK                         , // ��ֵ����
//    CS2P_NEWCARDREQ                        , // ��ѯ��Ƭ����
//    P2CS_NEWCARDACK                        , // ��ѯ��Ƭ����
//};
//
//struct MsgPlatformModule : public DBMsg
//{
//    MsgPlatformModule()
//    { SetModuleType( EMessageModule_Platform ); }
//};
//
//struct P2CSAddPayReq : public MsgPlatformModule
//{
//    P2CSAddPayReq()
//    {
//        header.dwType = P2CS_ADDPAYREQ;
//        header.stLength = sizeof( P2CSAddPayReq );
//    }
//    
//    SPayInfo payInfo;
//};
// 
//struct CS2PAddPayAck : public MsgPlatformModule
//{
//    CS2PAddPayAck()
//    {
//        header.dwType = CS2P_ADDPAYACK;
//        header.stLength = sizeof( CS2PAddPayAck );
//    }
//
//    uint16 result; // ���
//    uint32 guid  ; // �˺�Id
//    uint16 typeId; // ��ֵ�˵�Id
//};
//
//struct CS2PNewCardReq : public MsgPlatformModule
//{ // ��ƽ̨��ѯ����Ϣ
//    CS2PNewCardReq()
//    {
//        header.dwType = CS2P_NEWCARDREQ;
//        header.stLength = sizeof( CS2PNewCardReq );
//        gssid = 0;
//        memset( passport, 0, sizeof(passport) );
//        types = 0;
//    }
//
//    uint16 gssid       ; // ���������
//    int8   passport[33]; // �û�ͨ��֤
//    uint8  types       ; // ���ֿ�����
//};
//
//struct P2CSNewCardAck : public MsgPlatformModule
//{ // ��ƽ̨��ѯ����Ϣ
//    P2CSNewCardAck()
//    {
//        header.dwType = P2CS_NEWCARDACK;
//        header.stLength = sizeof( P2CSNewCardAck );
//        result = 0;
//        memset( passport, 0, sizeof(passport) );
//        types = 0;
//    }
//
//    uint16 result      ; // ���
//    int8   passport[33]; // �û�ͨ��֤
//    uint8  types       ; // ���ֿ�����
//};


#pragma pack( pop ) 

#endif // __PLATFORMMESSAGEDEFINE_H__
