#ifndef __RELATIONMESSAGE_H__
#define __RELATIONMESSAGE_H__

/************************************************************************
            ��ϵ��Ϣ����
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "MsgBase.h"
#include "RelationDefine.h"
#include "MessageRangeDefine.h"

#pragma pack( push, 1 )

enum RelationMessageDefine
{
    MSG_ADDRELATIONREQ = GAMEWORD_RELATION_BEGIN,       // ������Ӻ���
    MSG_ADDRELATIONACK,                     // ������Ӻ���
    MSG_INVITERELATIONREQ,                  // ֪ͨ�Է�������ӹ�ϵ
    MSG_INVITERELATIONACK,               // ��Ӧ�Է���������ӹ�ϵ
    MSG_UPDATERELATIONREQ,                  // ������¹�ϵ��Ϣ
    MSG_UPDATERELATIONACK,                  // ���ظ��¹�ϵ��Ϣ
    MSG_DELETERELATIONREQ,                  // ����ɾ����ϵ
    MSG_DELETERELATIONACK,                  // ����ɾ����ϵ
    MSG_DELETERELATIONCHECKREQ,             // ����ȷ��ɾ����ϵ
    MSG_DELETERELATIONCHECKACK,             // ����ȷ��ɾ����ϵ
    MSG_RELATIONLIST,                       // ���غ����б�
    MSG_FRIENDONLINE,                       // ����������Ϣ
    MSG_FRIENDOUTLINE,                      // ����������Ϣ
    MSG_UPDATEFRIENDLY,                     // ���º��Ѷ�
    MSG_RELATIONLOCKREQ,
    MSG_RELATIONUNLOCKREQ,
    MSG_RELATIONLOCKSTATUS,
    MSG_TELLADDREALTION,
    MSG_QUERYATTRIBUTEREQ,
    MSG_QUERYATTRIBUTERESULT,
    MSG_SETRECEIVESTRANGERREQ,
    MSG_REGISTERRELATIONREQ,
    MSG_REGISTERRELATIONLIST,
    MSG_TELLADDRELATIONTIMELEFT,
    MSG_STUDENTLEVELUP,
    MSG_TELLWORLDADDRELATION,
    MSG_CHANGESIGNATUREREQ,
    MSG_RELATIONATTRIBUTE,
    MSG_RELATIONGROUPADDREQ,
    MSG_RELATIONGROUPCHANGENAMEREQ,
    MSG_TELLRELATIONGROUP,
    MSG_RELATIONGROUPDELETEREQ,
    MSG_RELATIONGROUPDELETEACK,
    MSG_RELATIONGROUPCHANGEREQ,
    MSG_RELATIONGROUPCHANGEACK,
    MSG_RELATIONREMARTCHANGEREQ,

    CS2DB_RELATIONLISTREQ = CENTERGAME_RELATION_BEGIN,
    DB2CS_RELATIONATTRIBUTELIST,		//DB����ÿ���˵ĸ����罻����
    DB2CS_RELATIONDATALIST,				//DB����center�ĺ��ѵĹ�ϵ����
    CS2DB_ADDRELATIONREQ,
    CS2DB_ADDATTRIBUTEREQ,
    CS2DB_UPDATEATTRIBUTEREQ,
    CS2DB_UPDATERELATIONGROUP,
    CS2DB_UPDATERELATIONDATAREQ,


    CS2GS_RELATIONLIST,
    CS2GS_RELATIONDATASENDSUCCESS,
    CS2GS_RELATIONONLINE,               // ��������
    CS2GS_RELATIONOUTLINE,
    GS2CS_ADDRELATIONATTRIBUTE,
    CS2GS_ADDRELATIONATTRIBUTE,
    GS2CS_UPDATERELATIONATTRIBUTE,
    CS2GS_UPDATERELATIONATTRIBUTE,
    GS2CS_ADDRELAITONREQ,
    GS2CS_ADDRELATIONACK,
    CS2GS_ADDRELATIONRESULT,
    GS2CS_DELETERELATIONREQ,
    CS2GS_DELETERELATIONACK,
    CS2GS_ADDFRIENDLYTIMELIST,            // ���ͺ��Ѷ�ʱ���б�
    GS2CS_UPDATEADDFRIENDLYTIME,          // �������ͺ��Ѷ�ʱ��
    CS2GS_RECEIVEQUESTTIMELIST,
    GS2CS_UPDATERECEIVEQUESTTIME,
    CS2GS_RELATIONLOCKSTATUS,
    GS2CS_QUERYATTRIBUTEREQ,
    DB2CS_QUERYATTRIBUTEACK,
    GS2CS_STUDENTLEVELUP,
    CS2GS_STUDENTLEVELUP,
    GS2CS_RESETSTUDENTREWARD,
    GS2CS_RELATIONGROUPNAMECHANGEREQ,
    CS2GS_RELATIONGROUPNAMECHANGE,
    GS2CS_RELATIONDATACHANGEREQ,
    CS2GS_UPDATERELATIONDATA,

	MSG_PERSONALINFO,					// ��������
	MSG_CHANGEPERSONALINFO,				// ���ĸ�������
	MSG_FINDBYCONDITION,				// �������������
	MSG_FINDPERSONRESULT,				// �������
	
	CS2DB_UPDATEPERSONALINFOREQ,
	GS2CS_UPDATEPERSONALINFOREQ,
	CS2GS_UPDATEPERSONALINFOREQ,
	GS2CS_FINDBYCONDITION,

	GS2CS_RELATIONUPDATENAME,
	CS2GS_RELATIONUPDATENAME,
	MSG_RELATIONUPDATENAMEACK,
};

struct MsgRelationModule : public Msg
{
    MsgRelationModule()
    {
        SetModuleType( EMessageModule_Relation );
    }
};

// ������Ӻ���
struct MsgAddRelationReq : public MsgRelationModule             
{
    MsgAddRelationReq()
    {
        header.dwType   = MSG_ADDRELATIONREQ;
        header.stLength = sizeof( MsgAddRelationReq );
    }

    unsigned short stRelation;       // ����Ҫ��ӵĹ�ϵ
    unsigned char uchGroupID;        // ���ѷ���
    char szName[RelationDefine::MaxNameLength];      // Ҫ��ӹ�ϵ�Է���ҵ�����
};

// ������Ӻ���
struct MsgAddRelationAck : public MsgRelationModule         
{
    MsgAddRelationAck()
    {
        header.dwType = MSG_ADDRELATIONACK;
        header.stLength = sizeof( MsgAddRelationAck );
    }

    unsigned char uchResult;                // ���ؽ��
    RelationDataToClient xRelationData;     // ��ϵ��Ϣ, ����������Ϣ���ǵ�ǰ������Ϣ
};

// ����������Է���ӹ�ϵ
struct MsgInviteRelationReq : public MsgRelationModule            
{
    MsgInviteRelationReq()
    {
        header.dwType = MSG_INVITERELATIONREQ;
        header.stLength = sizeof( MsgInviteRelationReq );

        memset( szReqName, 0, sizeof( szReqName ) );
    }

    unsigned int dwReqID;                                // �����˵�ID
    char szReqName[RelationDefine::MaxNameLength];       // �����˵�����
    unsigned short stRelation;                           // ������ӵĹ�ϵ
};

// ��Ӧ������ӹ�ϵ
struct MsgInviteRelationAck : public MsgRelationModule            
{   
    MsgInviteRelationAck()
    {
        header.dwType = MSG_INVITERELATIONACK;
        header.stLength = sizeof( MsgInviteRelationAck );
        bAgree = true;
    }

    bool bAgree;                            // �Ƿ�ͬ��
    unsigned int nReqID;                    // �����˵�ID
    unsigned short stRelation;              // ������ӵĹ�ϵ
};

// ������º�����Ϣ
struct MsgUpdateRelationReq : public MsgRelationModule
{    
    MsgUpdateRelationReq()
    {
        header.dwType = MSG_UPDATERELATIONREQ;
        header.stLength = sizeof( MsgUpdateRelationReq );
    }
};

// ����������ҵ����Ը��ͻ���
struct MsgUpdateRelationAck : public MsgRelationModule      
{
    MsgUpdateRelationAck()
    {
        header.dwType = MSG_UPDATERELATIONACK;
        header.stLength = sizeof( MsgUpdateRelationAck ) - sizeof( xAttribute );
        ustCount = 0;
    }

    enum EConstDefine
    {
        ECD_MaxCount = 200,
    };
 
    unsigned short ustCount;
    RelationAttribute xAttribute[ ECD_MaxCount ];

    void AddAttribute( RelationAttribute& xData )
    {
        if ( ustCount >= ECD_MaxCount )
        { return; }

        xAttribute[ ustCount ] = xData;
        ++ustCount;

        header.stLength += sizeof( RelationAttribute );
    }

    bool IsFull() { return ustCount == ECD_MaxCount; }

    void Reset()
    {
        header.stLength = sizeof( MsgUpdateRelationAck ) - sizeof( xAttribute );
        ustCount = 0;
    }
};

//����ɾ������
struct MsgDeleteRelationReq : public MsgRelationModule
{
    MsgDeleteRelationReq()
    {
        header.dwType = MSG_DELETERELATIONREQ;
        header.stLength = sizeof( MsgDeleteRelationReq );
    }

    unsigned int nPlayerID;           // ɾ��ĳ��ҵĹ�ϵ
    unsigned short stRelation;        // ɾ��ĳһ�ֹ�ϵ
};

//����ɾ������
struct MsgDeleteRaltionAck : public MsgRelationModule
{
    MsgDeleteRaltionAck()
    {
        header.dwType = MSG_DELETERELATIONACK;
        header.stLength = sizeof( MsgDeleteRaltionAck );
        nResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,             // �ɹ�
        ECD_NotHaveThisRelation,     // �����������ϵ
        ECD_CanNotDelRelation,       // ����ɾ�������ϵ
        ECD_NotEnoughMoney,          // ɾ��ʦͽ��ϵû���㹻�ļ���
    };

    unsigned char nResult;
    unsigned int nPlayerID;           // DBID
    unsigned short stRelation;        // ɾ���Ĺ�ϵ
    unsigned short stFriendly;        // ��ǰ���Ѷ�
};

// ���͸��Է�Э��
struct MsgDeleteRelationCheckReq : public MsgRelationModule
{
    MsgDeleteRelationCheckReq()
    {
        header.dwType = MSG_DELETERELATIONCHECKREQ;
        header.stLength = sizeof( MsgDeleteRelationCheckReq );
    }

    unsigned int nPlayerID;           // ɾ��ĳ��ҵĹ�ϵ
    unsigned short ustRelation;       // ɾ��ĳһ�ֹ�ϵ
};

// �ͻ��˻ظ���Ϣ���������ܾ����ǽ���, �����������͸�������
struct MsgDeleteRelationCheckAck : public MsgRelationModule
{
    MsgDeleteRelationCheckAck()
    {
        header.dwType = MSG_DELETERELATIONCHECKACK;
        header.stLength = sizeof( MsgDeleteRelationCheckAck );
    }

    bool bDelete;               // �Ƿ�ɾ��
    unsigned int nFriendID;     // ɾ��ĳ��ҵĹ�ϵ
    unsigned short stRelation;  // ɾ��ĳһ�ֹ�ϵ
};

// �Լ��Ĺ�ϵ��������
struct MsgRelationAttribute : public MsgRelationModule
{
    MsgRelationAttribute()
    {
        header.dwType = MSG_RELATIONATTRIBUTE;
        header.stLength = sizeof( MsgRelationAttribute );
    }


    unsigned short ustMessageRefuse;                        // ����˽����Ϣ����
    char szSignature[ RelationDefine::MaxSignLength ];      // ����ǩ��
    RelationGroup xGroup[ RelationDefine::GroupCount ];     // ������Ϣ
};

//��ҵ�½������ʱ�����غ����б�
struct MsgRelationList : public MsgRelationModule
{
    MsgRelationList()
    {
        header.dwType = MSG_RELATIONLIST;
        header.stLength = sizeof( MsgRelationList ) - sizeof( xDataToClient );
        ustCount = 0;
    }

    enum EConstDefine
    {
        ECD_MaxCount = 200,
    };

    unsigned short ustCount;
    RelationDataToClient xDataToClient[ECD_MaxCount];

    void AddRelationData( RelationDataToClient& xData )
    {
        if ( ustCount >= ECD_MaxCount )
        { return; }

        xDataToClient[ ustCount ] = xData;
        ++ustCount;
        header.stLength += sizeof( RelationDataToClient );
    }

    bool IsFull()
    {
        return ustCount == ECD_MaxCount;
    }

    void Reset()
    {
        header.stLength = sizeof( MsgRelationList ) - sizeof( xDataToClient );
        ustCount = 0;
    }
};

//����������Ϣ
struct MsgFriendOnline : public MsgRelationModule
{
    MsgFriendOnline()
    {
        header.dwType = MSG_FRIENDONLINE;
        header.stLength = sizeof( MsgFriendOnline );
    }
    
    unsigned int nPlayerID;
};

 // ����������
struct MsgFriendOutLine : public MsgRelationModule
{  
    MsgFriendOutLine()
    {
        header.dwType = MSG_FRIENDOUTLINE;
        header.stLength = sizeof( MsgFriendOutLine );
    }

    unsigned int nPlayerID;         //��ҵ�DBID
};

// ˢ�º��Ѷ�
struct MsgUpdateFriendly : public MsgRelationModule
{
    MsgUpdateFriendly()
    {
        header.dwType = MSG_UPDATEFRIENDLY;
        header.stLength = sizeof( MsgUpdateFriendly );
    }

    unsigned int  nPlayerID;    // �Է�ID
    unsigned int  nFriendly;    // ��ǰ���Ѷ�
};

// ����ĳ��
struct MsgRelationLockReq : public MsgRelationModule
{
    MsgRelationLockReq()
    {
        header.dwType = MSG_RELATIONLOCKREQ;
        header.stLength = sizeof( MsgRelationLockReq );
    }

    unsigned int nPlayerID;
};

// ��������ĳ��
struct MsgRelationUnLockReq : public MsgRelationModule
{
    MsgRelationUnLockReq()
    {
        header.dwType = MSG_RELATIONUNLOCKREQ;
        header.stLength = sizeof( MsgRelationUnLockReq );
    }

    unsigned int nPlayerID;
};

// ֪ͨ����״̬
struct MsgRelationLockStatus : public MsgRelationModule
{
    MsgRelationLockStatus()
    {
        header.dwType = MSG_RELATIONLOCKSTATUS;
        header.stLength = sizeof( MsgRelationLockStatus );
    }

    unsigned int nPlayerID;
    bool bLocked;               // �Ƿ�����
};

// ֪ͨĳ�˼���Ϊ������
struct MsgTellAddRelation : public MsgRelationModule
{
    MsgTellAddRelation()
    {
        header.dwType = MSG_TELLADDREALTION;
        header.stLength = sizeof( MsgTellAddRelation );
    }

    char szName[ RelationDefine::MaxNameLength ];
    unsigned short ustRelation;     // Ŀǰֻ֪ͨ����
};

// ��ѯ����������Ϣ
struct MsgQueryAttributeReq : public MsgRelationModule
{
    MsgQueryAttributeReq()
    {
        header.dwType = MSG_QUERYATTRIBUTEREQ;
        header.stLength = sizeof( MsgQueryAttributeReq );
    }

    char szName[ RelationDefine::MaxNameLength ];
};

// ���ز�ѯ���
struct MsgQueryAttributeResult : public MsgRelationModule
{
    MsgQueryAttributeResult()
    {
        header.dwType = MSG_QUERYATTRIBUTERESULT;
        header.stLength = sizeof( MsgQueryAttributeResult ) - sizeof( xAttribute );
        ustCount = 0;
    }

    enum EConstDefine
    {
        ECD_MaxCount = 100,
    };

    uint16 ustCount;            // ustCount = 0 ˵��û�в�ѯ�����
    RelationAttribute xAttribute[ ECD_MaxCount ];      

    void AddAttribute( RelationAttribute& xData )
    {
        if ( ustCount >= ECD_MaxCount )
        { return; }

        xAttribute[ ustCount ] = xData;
        ++ustCount;

        header.stLength += sizeof( RelationAttribute );
    }

    bool IsFull() { return ustCount == ECD_MaxCount; }
    void Reset()
    {
        ustCount = 0;
        header.stLength = sizeof( MsgQueryAttributeResult ) - sizeof( xAttribute );
    }
};

// �����Ƿ����İ������Ϣ
struct MsgSetReceiveStrangerReq : public MsgRelationModule
{
    MsgSetReceiveStrangerReq()
    {
        header.dwType = MSG_SETRECEIVESTRANGERREQ;
        header.stLength = sizeof( MsgSetReceiveStrangerReq );
    }

    unsigned short ustMessageRefuse;    // �ܾ�������Ϣ�趨
};

// ע��һ��ʦ������ͽ����Ϣ���������б���
struct MsgRegisterRelationReq : public MsgRelationModule
{
    MsgRegisterRelationReq()
    {
        header.dwType = MSG_REGISTERRELATIONREQ;
        header.stLength = sizeof( MsgRegisterRelationReq );
    }

    unsigned short ustRelation;     // ʦ�� or ͽ�� ��ϵ
};

// ����ʦ�� or ͽ�� �б���ͻ���
struct MsgRegisterRelationList : public MsgRelationModule
{
    MsgRegisterRelationList()
    {
        header.dwType = MSG_REGISTERRELATIONLIST;
        header.stLength = sizeof( MsgRegisterRelationList ) - sizeof ( xAttribute );
        ustCount = 0;
    }

    enum EConstDefine
    {
        ECD_MaxCount = 300,
    };

    unsigned short ustRelation;     // ʦ�� or ͽ�� ��ϵ

    uint16 ustCount;            // ustCount = 0 ˵��û�в�ѯ�����
    RelationAttribute xAttribute[ ECD_MaxCount ];      

    void AddAttribute( RelationAttribute& xData )
    {
        if ( ustCount >= ECD_MaxCount )
        { return; }

        xAttribute[ ustCount ] = xData;
        ++ustCount;

        header.stLength += sizeof( RelationAttribute );
    }

    bool IsFull() { return ustCount == ECD_MaxCount; }
    void Reset()
    {
        ustCount = 0;
        header.stLength = sizeof( MsgRegisterRelationList ) - sizeof( xAttribute );
    }
};

// ֪ͨ�ͻ������ĳ�ֹ�ϵ��ʣ��ʱ��
struct MsgTellAddRelationTimeLeft : public MsgRelationModule
{
    MsgTellAddRelationTimeLeft()
    {
        header.dwType = MSG_TELLADDRELATIONTIMELEFT;
        header.stLength = sizeof( MsgTellAddRelationTimeLeft );
        nTimeLeft = 0;
    }

    unsigned short ustRelation;
    unsigned int nTimeLeft;     // ʣ��ʱ��: ��
};

struct MsgStudentLevelUp : public MsgRelationModule
{
    MsgStudentLevelUp()
    {
        header.dwType = MSG_STUDENTLEVELUP;
        header.stLength = sizeof( MsgStudentLevelUp );
    }

    unsigned int nStudentID;
    bool bIsStudent;                    // true = �Լ���ͽ��   false = ͽ�ܵ�ͽ��

    unsigned int nRewardExp;            // �����ľ���
    unsigned int nRewardMasterValue;    // ��������
};

// ֪ͨȫ����ĳ2���˼���ĳ�ֹ�ϵ, ��Ҫ�Ƿ��޹�ϵ
struct MsgTellWorldAddRelation : public MsgRelationModule
{
    MsgTellWorldAddRelation()
    {
        header.dwType = MSG_TELLWORLDADDRELATION;
        header.stLength = sizeof( MsgTellWorldAddRelation );
    }

    unsigned short ustRelation;                         // ��ӵĹ�ϵ( ���޹�ϵ �� eTellClient_Marriage ����ִ� )
    char szPlayer1[ RelationDefine::MaxNameLength ];
    char szPlayer2[ RelationDefine::MaxNameLength ];
};

// ������ĸ���ǩ�� ( ����������������, �ͻ���ֱ�ӱ����µĸ���ǩ�� )
struct MsgChangeSignatureReq : public MsgRelationModule
{
    MsgChangeSignatureReq()
    {
        header.dwType = MSG_CHANGESIGNATUREREQ;
        header.stLength = sizeof( MsgChangeSignatureReq );
    }

    char szSignature[ RelationDefine::MaxSignLength ];
};

// �������� (Enterworld���� S->C)
struct MsgPersonalInfo : public Msg
{
	MsgPersonalInfo()
	{
		header.dwType = MSG_PERSONALINFO;
		header.stLength = sizeof( MsgPersonalInfo );
	}
	PersonalInfo xPersonalInfo;
};

// ���ĸ�����Ϣ
struct MsgChangePersonalInfo : public MsgRelationModule
{
	MsgChangePersonalInfo()
	{
		header.dwType = MSG_CHANGEPERSONALINFO;
		header.stLength = sizeof( MsgChangePersonalInfo );
	}

	PersonalInfo xPersonalInfo;
};

// �������������
struct MsgFindByCondiotion : public MsgRelationModule
{
	MsgFindByCondiotion()
	{
		header.dwType = MSG_FINDBYCONDITION;
		header.stLength = sizeof( MsgFindByCondiotion );
	}
	unsigned char	uchUnlimit;			// ��������

	unsigned char	uchSex;				// �Ա� ESexType
	unsigned char	uchAgeMin;			// �����
	unsigned char	uchAgeMax;
	char	szProvince[RelationDefine::ProvinceLength];			// ʡ��
	char	szCity[RelationDefine::CityLength];					// ����
};

// �������һ������
struct MsgRelationGroupAddReq : public MsgRelationModule
{
    MsgRelationGroupAddReq()
    {
        header.dwType = MSG_RELATIONGROUPADDREQ;
        header.stLength = sizeof( MsgRelationGroupAddReq );

        memset( szGroup, 0, sizeof( szGroup ) );
    }

    char szGroup[ RelationDefine::GroupLength ];    // ��������
};

// �����޸ķ�������
struct MsgRelationGroupChangeNameReq : public MsgRelationModule
{
    MsgRelationGroupChangeNameReq()
    {
        header.dwType = MSG_RELATIONGROUPCHANGENAMEREQ;
        header.stLength = sizeof( MsgRelationGroupChangeNameReq );

        memset( szGroup, 0, sizeof( szGroup ) );
    }

    unsigned char uchGroupID;                       // ����ID
    char szGroup[ RelationDefine::GroupLength ];    // ��������( ���Ҫɾ������, �ѷ�����������Ϊ�� )
};

// ������ͬ��������Ϣ���ͻ���
struct MsgTellRelationGroup : public MsgRelationModule
{
    MsgTellRelationGroup()
    {
        header.dwType = MSG_TELLRELATIONGROUP;
        header.stLength = sizeof( MsgTellRelationGroup );
    }

    unsigned char uchGroupID;                       // ����ID
    char szGroup[ RelationDefine::GroupLength ];    // ��������( ���Ϊ��, ����ɾ������ �ͻ��˰Ѹ÷����Աȫ������Ĭ�Ϸ����� )
};

// ���󽫺��ѷ���ĳ����
struct MsgRelationGroupChangeReq : public MsgRelationModule
{
    MsgRelationGroupChangeReq()
    {
        header.dwType = MSG_RELATIONGROUPCHANGEREQ;
        header.stLength = sizeof( MsgRelationGroupChangeReq );
    }

    unsigned int nPlayerID;     // ����ID
    unsigned char uchGroupID;   // ����ID
};

// ��������Ӧ���ѷ���
struct MsgRelationGroupChangeAck : public MsgRelationModule
{
    MsgRelationGroupChangeAck()
    {
        header.dwType = MSG_RELATIONGROUPCHANGEACK;
        header.stLength = sizeof( MsgRelationGroupChangeAck );
    }

    unsigned int nPlayerID;     // ����ID
    unsigned char uchGroupID;   // ����ID
};

// ������º��ѱ�ע( �ͻ����޸ĺ�ֱ�ӱ��� )
struct MsgRelationRemarkChangeReq : public MsgRelationModule
{
    MsgRelationRemarkChangeReq()
    {
        header.dwType = MSG_RELATIONREMARTCHANGEREQ;
        header.stLength = sizeof( MsgRelationRemarkChangeReq );
    }

    unsigned int nPlayerID;         // ����DBID
    char szRemark[ RelationDefine::ReMarkLength ];  // ��ע
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// ���·���������Ϣ

// ��������б�
struct CS2DBRelationListReq : public MsgRelationModule
{
    CS2DBRelationListReq()
    {
        header.dwType = CS2DB_RELATIONLISTREQ;
        header.stLength = sizeof( CS2DBRelationListReq );
    }
};

// Ӧ���ϵ�����б�
struct DB2CSRelationAttributeList : public MsgRelationModule
{
    DB2CSRelationAttributeList()
    {
        header.dwType = DB2CS_RELATIONATTRIBUTELIST;
        header.stLength = sizeof( DB2CSRelationAttributeList ) - sizeof( xAttribute );
        ustCount = 0;
    }

    enum EConstDefine
    {
        ECD_MaxCount = 400,
    };

    uint16 ustCount;
    RelationAttributeToServer xAttribute[ ECD_MaxCount ];

    void AddAttribute( RelationAttributeToServer& xData )
    {
        if ( ustCount >= ECD_MaxCount )
        { return; }

        xAttribute[ ustCount ] = xData;
        ++ustCount;

        header.stLength += sizeof( RelationAttributeToServer );
    }

    bool IsFull() { return ustCount == ECD_MaxCount; }
    void Reset()
    {
        ustCount = 0;
        header.stLength = sizeof( DB2CSRelationAttributeList ) - sizeof( xAttribute );
    }
};

// Ӧ���ϵ�����б�
struct DB2CSRelationDataList : public MsgRelationModule
{
    DB2CSRelationDataList()
    {
        header.dwType = DB2CS_RELATIONDATALIST;
        header.stLength = sizeof( DB2CSRelationDataList ) - sizeof( xDBRelation );
        ustCount = 0;
    }

    enum EConstDefine
    {
        ECD_MaxCount = 500,
    };

    uint16 ustCount;
    RelationDataToDatabase xDBRelation[ ECD_MaxCount ];

    void AddRelationData( unsigned int nPlayerID, RelationDataToServer& xData )
    {
        if ( ustCount >= ECD_MaxCount )
        { return; }

        xDBRelation[ ustCount ].nPlayerID    = nPlayerID;
        xDBRelation[ ustCount ].xDataToServer = xData;
        ++ustCount;

        header.stLength += sizeof( RelationDataToDatabase );
    }

    bool IsFull() { return ustCount == ECD_MaxCount; }
    void Reset()
    {
        ustCount = 0;
        header.stLength = sizeof( DB2CSRelationDataList ) - sizeof( xDBRelation );
    }
};

// ������Ӻ���
struct CS2DBAddRelationReq : public MsgRelationModule
{
    CS2DBAddRelationReq()
    {
        header.dwType = CS2DB_ADDRELATIONREQ;
        header.stLength = sizeof( CS2DBAddRelationReq );
    }

    unsigned int nPlayerID;
    RelationDataToServer xData;
};

// �����������
struct CS2DBAddAttributeReq : public MsgRelationModule
{
    CS2DBAddAttributeReq()
    {
        header.dwType = CS2DB_ADDATTRIBUTEREQ;
        header.stLength = sizeof( CS2DBAddAttributeReq );
    }

    RelationAttributeToServer xAttribute;
};

// ������¹�ϵ������Ϣ
struct CS2DBUpdateAttributeReq : public MsgRelationModule
{
    CS2DBUpdateAttributeReq()
    {
        header.dwType = CS2DB_UPDATEATTRIBUTEREQ;
        header.stLength = sizeof( CS2DBUpdateAttributeReq );
    }

    union AttributeData
    {
        __int64 n64Value;
        char szValue[ RelationDefine::MaxNameLength ];
    };

    unsigned int nPlayerID;
    unsigned char uchType;
    AttributeData xAttribute;
};

// ������¸�������
struct CS2DBUpdatePersonalInfoReq : public MsgRelationModule
{
	CS2DBUpdatePersonalInfoReq()
	{
		header.dwType = CS2DB_UPDATEPERSONALINFOREQ;
		header.stLength = sizeof( CS2DBUpdatePersonalInfoReq );
	}
	unsigned int nPlayerID;
	PersonalInfo xPersonalInfo;
};

// ���º��ѷ�����Ϣ
struct CS2DBUpdateRelationGroup : public MsgRelationModule
{
    CS2DBUpdateRelationGroup()
    {
        header.dwType = CS2DB_UPDATERELATIONGROUP;
        header.stLength = sizeof( CS2DBUpdateRelationGroup );
    }

    unsigned int nPlayerID;
    unsigned char uchGroupID;
    char szGroup[ RelationDefine::GroupLength ];
};

// ���º��ѹ�ϵ��Ϣ
struct CS2DBUpdateRelationDataReq : public MsgRelationModule
{
    CS2DBUpdateRelationDataReq()
    {
        header.dwType = CS2DB_UPDATERELATIONDATAREQ;
        header.stLength = sizeof( CS2DBUpdateRelationDataReq );
    }

    union UnionData
    {
        unsigned int nValue;
        char szValue[ RelationDefine::ReMarkLength ];
    };

    unsigned int nPlayerID;
    unsigned int nTargetID;
    unsigned char uchType;
    UnionData xData;
};

/////////////////////////////////////////////////////////////////////////////////////////////
// ���͹�ϵ�б�������
struct CS2GSRelationList : public MsgRelationModule
{
    CS2GSRelationList()
    {
        header.dwType = CS2GS_RELATIONLIST;
        header.stLength = sizeof( CS2GSRelationList ) - sizeof( xData );
        ustCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 600,
    };

    RelationAttributeToServer xAttribute;

    unsigned short ustCount;
    RelationDataToServer xData[ MaxCount ];

    void AddRelationData( const RelationDataToServer& xInfo )
    {
        if ( ustCount >= MaxCount )
        { return; }

        xData[ ustCount++ ] = xInfo;
        header.stLength += sizeof( RelationDataToServer );
    }

    bool IsFull() { return ustCount >= MaxCount; }

    void Reset()
    {
        header.stLength = sizeof( CS2GSRelationList ) - sizeof( xData );
        ustCount = 0;
    }
};

struct CS2GSRelationDataSendSuccess : public MsgRelationModule
{
    CS2GSRelationDataSendSuccess()
    {
        header.dwType = CS2GS_RELATIONDATASENDSUCCESS;
        header.stLength = sizeof( CS2GSRelationDataSendSuccess );
    }
};

// ���������
struct CS2GSRelationOnLine : public MsgRelationModule
{
    CS2GSRelationOnLine()
    {
        header.dwType = CS2GS_RELATIONONLINE;
        header.stLength = sizeof( CS2GSRelationOnLine );
    }

    unsigned int nPlayerID;
};

// ���������
struct CS2GSRelationOutLine : public MsgRelationModule
{
    CS2GSRelationOutLine()
    {
        header.dwType = CS2GS_RELATIONOUTLINE;
        header.stLength = sizeof( CS2GSRelationOutLine );
    }

    unsigned int nPlayerID;
};

// ��ӹ�ϵ����
struct GS2CSAddRelationAttribute : public MsgRelationModule
{
    GS2CSAddRelationAttribute()
    {
        header.dwType = GS2CS_ADDRELATIONATTRIBUTE;
        header.stLength = sizeof( GS2CSAddRelationAttribute );
    }

    RelationAttribute xAttribute;
};

struct CS2GSAddRelationAttribute : public MsgRelationModule
{
    CS2GSAddRelationAttribute()
    {
        header.dwType = CS2GS_ADDRELATIONATTRIBUTE;
        header.stLength = sizeof( CS2GSAddRelationAttribute );
    }

    RelationAttributeToServer xAttribute;
};

// �������Թ�ϵ
struct GS2CSUpdateRelationAttribute : public MsgRelationModule
{
    GS2CSUpdateRelationAttribute()
    {
        header.dwType = GS2CS_UPDATERELATIONATTRIBUTE;
        header.stLength = sizeof( GS2CSUpdateRelationAttribute );
    }

    union AttributeData
    {
        __int64 n64Value;
        char szValue[ RelationDefine::MaxNameLength ];
    };

    unsigned int nPlayerID;
    unsigned char uchType;
    AttributeData xAttribute;
};

// ���¸�������
struct GS2CSUpdatePersonalInfo : public MsgRelationModule
{
	GS2CSUpdatePersonalInfo()
	{
		header.dwType = GS2CS_UPDATEPERSONALINFOREQ;
		header.stLength = sizeof( GS2CSUpdatePersonalInfo );
	}
	unsigned int nPlayerID;
	PersonalInfo xPersonalInfo;
};

struct CS2GSUpdateRelationAttribute : public MsgRelationModule
{
    CS2GSUpdateRelationAttribute()
    {
        header.dwType = CS2GS_UPDATERELATIONATTRIBUTE;
        header.stLength = sizeof( CS2GSUpdateRelationAttribute );
    }
 
    union AttributeData
    {
        __int64 n64Value;
        char szValue[ RelationDefine::MaxNameLength ];
    };

    unsigned int nPlayerID;
    unsigned char uchType;
    AttributeData xAttribute;
};


struct CS2GSUpdatePersonalInfo : public MsgRelationModule
{
	CS2GSUpdatePersonalInfo()
	{
		header.dwType = CS2GS_UPDATEPERSONALINFOREQ;
		header.stLength = sizeof( CS2GSUpdatePersonalInfo );
	}
	unsigned int nPlayerID;
	PersonalInfo xPersonalInfo;
};


//���� �������ߵ���Ϣ
struct GS2CSAddRelationReq : public MsgRelationModule
{
    GS2CSAddRelationReq()
    {
        header.dwType = GS2CS_ADDRELAITONREQ;
        header.stLength = sizeof( GS2CSAddRelationReq );

        uchGroupID = 0;
    }

    unsigned int nReqID;   // ������ID
    unsigned int nAckID;   // ��������ID        

    unsigned char uchGroupID;
    unsigned short stRelation;
};  

struct GS2CSAddRelationAck : public MsgRelationModule
{
    GS2CSAddRelationAck()
    {
        header.dwType = GS2CS_ADDRELATIONACK;
        header.stLength = sizeof( GS2CSAddRelationAck );
    }

    bool bAgreeAdd;
    unsigned int nReqID;
    unsigned int nAckID;
    unsigned short ustRelation;
};

struct CS2GSAddRelationResult : public MsgRelationModule
{
    CS2GSAddRelationResult()
    {
        header.dwType = CS2GS_ADDRELATIONRESULT;
        header.stLength = sizeof( CS2GSAddRelationResult );
    }

    unsigned int nReqID;
    RelationDataToServer xData;
};

struct GS2CSRemoveRelationReq : public MsgRelationModule
{
    GS2CSRemoveRelationReq()
    {
        header.dwType = GS2CS_DELETERELATIONREQ;
        header.stLength = sizeof( GS2CSRemoveRelationReq );
    }

    unsigned int nReqID;        // ������
    unsigned int nAckID;        // Ҫɾ�������
    unsigned short stRelation;  // Ҫɾ���Ĺ�ϵ
};

struct CS2GSRemoveRelationAck : public MsgRelationModule
{
    CS2GSRemoveRelationAck()
    {
        header.dwType = CS2GS_DELETERELATIONACK;
        header.stLength = sizeof( CS2GSRemoveRelationAck );
    }

    unsigned int nReqID;        // ������
    unsigned int nAckID;        // Ҫɾ�������
    unsigned short stRelation;  // Ҫɾ���Ĺ�ϵ
};

struct CS2GSMsgAddFriendlyTimeList : public MsgRelationModule 
{
    CS2GSMsgAddFriendlyTimeList()
    {
        header.dwType   = CS2GS_ADDFRIENDLYTIMELIST;
        header.stLength = sizeof( CS2GSMsgAddFriendlyTimeList );
        nCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 10,
    };

    int nCount;
    unsigned int dwSelfID;
    unsigned int dwPlayerID[ MaxCount ];

    void AddPlayerID( uint32 dwValue )
    {
        if ( nCount >= MaxCount )
        { return; }
        dwPlayerID[ nCount ] = dwValue;
        ++nCount;
    }
};

struct GS2CSUpdateAddFriendlyTime : public MsgRelationModule
{
    GS2CSUpdateAddFriendlyTime()
    {
        header.dwType   = GS2CS_UPDATEADDFRIENDLYTIME;
        header.stLength = sizeof( GS2CSUpdateAddFriendlyTime );
    }

    bool bClear;
    unsigned int dwSelfID;
    unsigned int dwPlayerID;
};

struct CS2GSMsgReceiveQuestTimeList : public MsgRelationModule 
{
    CS2GSMsgReceiveQuestTimeList()
    {
        header.dwType   = CS2GS_RECEIVEQUESTTIMELIST;
        header.stLength = sizeof( CS2GSMsgReceiveQuestTimeList );
        nCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 10,
    };

    int nCount;
    unsigned int  dwSelfID;
    unsigned int  dwPlayerID[ MaxCount ];

    void AddPlayerID( uint32 dwValue )
    {
        if ( nCount >= MaxCount )
        { return; }
        dwPlayerID[ nCount ] = dwValue;
        ++nCount;
    }
};

struct GS2CSUpdateReceiveQuestTime : public MsgRelationModule
{
    GS2CSUpdateReceiveQuestTime()
    {
        header.dwType   = GS2CS_UPDATERECEIVEQUESTTIME;
        header.stLength = sizeof( GS2CSUpdateReceiveQuestTime );
    }

    bool bClear;
    unsigned int dwSelfID;
    unsigned int dwPlayerID;
};

struct GS2CSQueryAttributeReq : public MsgRelationModule
{
    GS2CSQueryAttributeReq()
    {
        header.dwType = GS2CS_QUERYATTRIBUTEREQ;
        header.stLength = sizeof( GS2CSQueryAttributeReq );
    }

    unsigned int nPlayerID;

    unsigned char uchCountry;
    char szName[ RelationDefine::MaxNameLength ];
};

struct GS2CSFindPersonReq : MsgRelationModule
{
	GS2CSFindPersonReq()
	{
		header.dwType = GS2CS_FINDBYCONDITION;
		header.stLength = sizeof( GS2CSFindPersonReq );
	}
	unsigned int nPlayerID;

	unsigned char	uchUnlimit;			// ��������
	unsigned char	uchSex;				// �Ա� ESexType
	unsigned char	uchAgeMin;			// �����
	unsigned char	uchAgeMax;
	char	szProvince[RelationDefine::ProvinceLength];			// ʡ��
	char	szCity[RelationDefine::CityLength];					// ����
};

struct DB2CSQueryAttributeAck : public MsgRelationModule
{
    DB2CSQueryAttributeAck()
    {
        header.dwType = DB2CS_QUERYATTRIBUTEACK;
        header.stLength = sizeof( DB2CSQueryAttributeAck ) - sizeof( nAttributeID );
        ustCount = 0;
    }

    enum EConstDefine
    {
        ECD_MaxCount = 100,
    };

    unsigned int nPlayerID;

    unsigned short ustCount;
    unsigned int nAttributeID[ ECD_MaxCount ];

    void AddAttributeID( unsigned int nValue )
    {
        if ( ustCount >= ECD_MaxCount )
        { return; }

        nAttributeID[ ustCount ] = nValue;
        ++ustCount;

        header.stLength += sizeof( unsigned int );
    }

    bool IsFull() { return ustCount == ECD_MaxCount; }
    void Reset()
    {
        ustCount = 0;
        header.stLength = sizeof( DB2CSQueryAttributeAck ) - sizeof( nAttributeID );
    }
};

struct GS2CSStudentLevelUp : public MsgRelationModule
{
    GS2CSStudentLevelUp()
    {
        header.dwType = GS2CS_STUDENTLEVELUP;
        header.stLength = sizeof( GS2CSStudentLevelUp );
    }
    
    unsigned int nPlayerID;
    unsigned int nLevel;
};

struct CS2GSStudentLevelUp : public MsgRelationModule
{
    CS2GSStudentLevelUp()
    {
        header.dwType = CS2GS_STUDENTLEVELUP;
        header.stLength = sizeof( CS2GSStudentLevelUp );
    }

    unsigned int nPlayerID;
    unsigned int nStudentID;    // ��� nStudentID = 0ֱ����ʾ ���ͽ����   != 0;
    bool bIsStudent;            // true = �Լ���ͽ��   false = ͽ�ܵ�ͽ��

    unsigned int nRewardExp;            // �����ľ���
    unsigned int nRewardMasterValue;    // ��������
};

struct GS2CSResetStudentReward : public MsgRelationModule
{
    GS2CSResetStudentReward()
    {
        header.dwType = GS2CS_RESETSTUDENTREWARD;
        header.stLength = sizeof( GS2CSResetStudentReward );
    }

    unsigned int nPlayerID;
};

struct GS2CSRelationGroupNameChangeReq : public MsgRelationModule
{
    GS2CSRelationGroupNameChangeReq()
    {
        header.dwType = GS2CS_RELATIONGROUPNAMECHANGEREQ;
        header.stLength = sizeof( GS2CSRelationGroupNameChangeReq );

        memset( szName, 0, sizeof( szName ) );
    }

    unsigned int nPlayerID;
    unsigned char uchGroupID;
    char szName[ RelationDefine::GroupLength ];
};

struct CS2GSRelationGroupNameChange : public MsgRelationModule
{
    CS2GSRelationGroupNameChange()
    {
        header.dwType = CS2GS_RELATIONGROUPNAMECHANGE;
        header.stLength = sizeof( CS2GSRelationGroupNameChange );

        memset( szName, 0, sizeof( szName ) );
    }

    unsigned int nPlayerID;
    unsigned char uchGroupID;
    char szName[ RelationDefine::GroupLength ];
};

struct GS2CSRelationDataChangeReq : public MsgRelationModule
{
    GS2CSRelationDataChangeReq()
    {
        header.dwType = GS2CS_RELATIONDATACHANGEREQ;
        header.stLength = sizeof( GS2CSRelationDataChangeReq );
    }

    union UnionData
    {
        unsigned int nValue;
        char szValue[ RelationDefine::ReMarkLength ];
    };

    unsigned int nPlayerID;
    unsigned int nTargetID;
    unsigned char uchType;
    UnionData xData;
};

struct CS2GSUpdateRelationData : public MsgRelationModule
{
    CS2GSUpdateRelationData()
    {
        header.dwType = CS2GS_UPDATERELATIONDATA;
        header.stLength = sizeof( CS2GSUpdateRelationData );
    }

    union UnionData
    {
        unsigned int nValue;
        char szValue[ RelationDefine::ReMarkLength ];
    };

    unsigned int nPlayerID;
    unsigned int nTargetID;
    unsigned char uchType;
    UnionData xData;
};

struct GS2CSRelationUpdateName : public MsgRelationModule
{
    GS2CSRelationUpdateName()
    {
        header.dwType = GS2CS_RELATIONUPDATENAME;
        header.stLength = sizeof( GS2CSRelationUpdateName );
    }
    int   PlayerID;
	char  szName[dr_MaxUserName];
};

struct CS2GSRelationUpdateName : public MsgRelationModule
{
    CS2GSRelationUpdateName()
    {
        header.dwType = CS2GS_RELATIONUPDATENAME;
        header.stLength = sizeof( CS2GSRelationUpdateName );
    }
    int   PlayerID;
	char  szName[dr_MaxUserName];
};
struct MsgRelationUpdateNameAck: public MsgRelationModule
{
    MsgRelationUpdateNameAck()
    {
        header.dwType = MSG_RELATIONUPDATENAMEACK;
        header.stLength = sizeof( MsgRelationUpdateNameAck );
    }
    int   PlayerID;
	char  szName[dr_MaxUserName];
};

#pragma pack( pop )

#endif