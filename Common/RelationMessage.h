#ifndef __RELATIONMESSAGE_H__
#define __RELATIONMESSAGE_H__

/************************************************************************
            关系消息定义
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "MsgBase.h"
#include "RelationDefine.h"
#include "MessageRangeDefine.h"

#pragma pack( push, 1 )

enum RelationMessageDefine
{
    MSG_ADDRELATIONREQ = GAMEWORD_RELATION_BEGIN,       // 请求添加好友
    MSG_ADDRELATIONACK,                     // 回馈添加好友
    MSG_INVITERELATIONREQ,                  // 通知对方申请添加关系
    MSG_INVITERELATIONACK,               // 回应对方的申请添加关系
    MSG_UPDATERELATIONREQ,                  // 请求更新关系信息
    MSG_UPDATERELATIONACK,                  // 返回更新关系信息
    MSG_DELETERELATIONREQ,                  // 请求删除关系
    MSG_DELETERELATIONACK,                  // 回馈删除关系
    MSG_DELETERELATIONCHECKREQ,             // 请求确认删除关系
    MSG_DELETERELATIONCHECKACK,             // 回馈确认删除关系
    MSG_RELATIONLIST,                       // 返回好友列表
    MSG_FRIENDONLINE,                       // 好友上线消息
    MSG_FRIENDOUTLINE,                      // 好友下线消息
    MSG_UPDATEFRIENDLY,                     // 更新好友度
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
    DB2CS_RELATIONATTRIBUTELIST,		//DB返回每个人的个人社交数据
    DB2CS_RELATIONDATALIST,				//DB返回center的好友的关系数据
    CS2DB_ADDRELATIONREQ,
    CS2DB_ADDATTRIBUTEREQ,
    CS2DB_UPDATEATTRIBUTEREQ,
    CS2DB_UPDATERELATIONGROUP,
    CS2DB_UPDATERELATIONDATAREQ,


    CS2GS_RELATIONLIST,
    CS2GS_RELATIONDATASENDSUCCESS,
    CS2GS_RELATIONONLINE,               // 好友在线
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
    CS2GS_ADDFRIENDLYTIMELIST,            // 赠送好友度时间列表
    GS2CS_UPDATEADDFRIENDLYTIME,          // 更新赠送好友度时间
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

	MSG_PERSONALINFO,					// 个人资料
	MSG_CHANGEPERSONALINFO,				// 更改个人资料
	MSG_FINDBYCONDITION,				// 按条件搜索玩家
	MSG_FINDPERSONRESULT,				// 搜索结果
	
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

// 申请添加好友
struct MsgAddRelationReq : public MsgRelationModule             
{
    MsgAddRelationReq()
    {
        header.dwType   = MSG_ADDRELATIONREQ;
        header.stLength = sizeof( MsgAddRelationReq );
    }

    unsigned short stRelation;       // 申请要添加的关系
    unsigned char uchGroupID;        // 好友分组
    char szName[RelationDefine::MaxNameLength];      // 要添加关系对方玩家的名字
};

// 返回添加好友
struct MsgAddRelationAck : public MsgRelationModule         
{
    MsgAddRelationAck()
    {
        header.dwType = MSG_ADDRELATIONACK;
        header.stLength = sizeof( MsgAddRelationAck );
    }

    unsigned char uchResult;                // 返回结果
    RelationDataToClient xRelationData;     // 关系信息, 里面所有信息都是当前最新信息
};

// 发送邀请给对方添加关系
struct MsgInviteRelationReq : public MsgRelationModule            
{
    MsgInviteRelationReq()
    {
        header.dwType = MSG_INVITERELATIONREQ;
        header.stLength = sizeof( MsgInviteRelationReq );

        memset( szReqName, 0, sizeof( szReqName ) );
    }

    unsigned int dwReqID;                                // 申请人的ID
    char szReqName[RelationDefine::MaxNameLength];       // 申请人的名字
    unsigned short stRelation;                           // 申请添加的关系
};

// 回应申请添加关系
struct MsgInviteRelationAck : public MsgRelationModule            
{   
    MsgInviteRelationAck()
    {
        header.dwType = MSG_INVITERELATIONACK;
        header.stLength = sizeof( MsgInviteRelationAck );
        bAgree = true;
    }

    bool bAgree;                            // 是否同意
    unsigned int nReqID;                    // 申请人的ID
    unsigned short stRelation;              // 申请添加的关系
};

// 请求更新好友信息
struct MsgUpdateRelationReq : public MsgRelationModule
{    
    MsgUpdateRelationReq()
    {
        header.dwType = MSG_UPDATERELATIONREQ;
        header.stLength = sizeof( MsgUpdateRelationReq );
    }
};

// 更新在线玩家的属性给客户端
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

//申请删除好友
struct MsgDeleteRelationReq : public MsgRelationModule
{
    MsgDeleteRelationReq()
    {
        header.dwType = MSG_DELETERELATIONREQ;
        header.stLength = sizeof( MsgDeleteRelationReq );
    }

    unsigned int nPlayerID;           // 删除某玩家的关系
    unsigned short stRelation;        // 删除某一种关系
};

//返回删除好友
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
        ECD_Success = 0,             // 成功
        ECD_NotHaveThisRelation,     // 不存在这个关系
        ECD_CanNotDelRelation,       // 不能删除这个关系
        ECD_NotEnoughMoney,          // 删除师徒关系没有足够的几笔
    };

    unsigned char nResult;
    unsigned int nPlayerID;           // DBID
    unsigned short stRelation;        // 删除的关系
    unsigned short stFriendly;        // 当前好友度
};

// 发送给对方协议
struct MsgDeleteRelationCheckReq : public MsgRelationModule
{
    MsgDeleteRelationCheckReq()
    {
        header.dwType = MSG_DELETERELATIONCHECKREQ;
        header.stLength = sizeof( MsgDeleteRelationCheckReq );
    }

    unsigned int nPlayerID;           // 删除某玩家的关系
    unsigned short ustRelation;       // 删除某一种关系
};

// 客户端回复消息给服务器拒绝还是接受, 服务器并回送给请求者
struct MsgDeleteRelationCheckAck : public MsgRelationModule
{
    MsgDeleteRelationCheckAck()
    {
        header.dwType = MSG_DELETERELATIONCHECKACK;
        header.stLength = sizeof( MsgDeleteRelationCheckAck );
    }

    bool bDelete;               // 是否删除
    unsigned int nFriendID;     // 删除某玩家的关系
    unsigned short stRelation;  // 删除某一种关系
};

// 自己的关系基本属性
struct MsgRelationAttribute : public MsgRelationModule
{
    MsgRelationAttribute()
    {
        header.dwType = MSG_RELATIONATTRIBUTE;
        header.stLength = sizeof( MsgRelationAttribute );
    }


    unsigned short ustMessageRefuse;                        // 接受私聊消息设置
    char szSignature[ RelationDefine::MaxSignLength ];      // 个性签名
    RelationGroup xGroup[ RelationDefine::GroupCount ];     // 分组信息
};

//玩家登陆服务器时　返回好友列表
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

//好友上线消息
struct MsgFriendOnline : public MsgRelationModule
{
    MsgFriendOnline()
    {
        header.dwType = MSG_FRIENDONLINE;
        header.stLength = sizeof( MsgFriendOnline );
    }
    
    unsigned int nPlayerID;
};

 // 好友下线了
struct MsgFriendOutLine : public MsgRelationModule
{  
    MsgFriendOutLine()
    {
        header.dwType = MSG_FRIENDOUTLINE;
        header.stLength = sizeof( MsgFriendOutLine );
    }

    unsigned int nPlayerID;         //玩家的DBID
};

// 刷新好友度
struct MsgUpdateFriendly : public MsgRelationModule
{
    MsgUpdateFriendly()
    {
        header.dwType = MSG_UPDATEFRIENDLY;
        header.stLength = sizeof( MsgUpdateFriendly );
    }

    unsigned int  nPlayerID;    // 对方ID
    unsigned int  nFriendly;    // 当前好友度
};

// 锁定某人
struct MsgRelationLockReq : public MsgRelationModule
{
    MsgRelationLockReq()
    {
        header.dwType = MSG_RELATIONLOCKREQ;
        header.stLength = sizeof( MsgRelationLockReq );
    }

    unsigned int nPlayerID;
};

// 解锁锁定某人
struct MsgRelationUnLockReq : public MsgRelationModule
{
    MsgRelationUnLockReq()
    {
        header.dwType = MSG_RELATIONUNLOCKREQ;
        header.stLength = sizeof( MsgRelationUnLockReq );
    }

    unsigned int nPlayerID;
};

// 通知锁定状态
struct MsgRelationLockStatus : public MsgRelationModule
{
    MsgRelationLockStatus()
    {
        header.dwType = MSG_RELATIONLOCKSTATUS;
        header.stLength = sizeof( MsgRelationLockStatus );
    }

    unsigned int nPlayerID;
    bool bLocked;               // 是否锁定
};

// 通知某人加你为好友了
struct MsgTellAddRelation : public MsgRelationModule
{
    MsgTellAddRelation()
    {
        header.dwType = MSG_TELLADDREALTION;
        header.stLength = sizeof( MsgTellAddRelation );
    }

    char szName[ RelationDefine::MaxNameLength ];
    unsigned short ustRelation;     // 目前只通知好友
};

// 查询本国好友信息
struct MsgQueryAttributeReq : public MsgRelationModule
{
    MsgQueryAttributeReq()
    {
        header.dwType = MSG_QUERYATTRIBUTEREQ;
        header.stLength = sizeof( MsgQueryAttributeReq );
    }

    char szName[ RelationDefine::MaxNameLength ];
};

// 返回查询结果
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

    uint16 ustCount;            // ustCount = 0 说明没有查询到结果
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

// 设置是否接受陌生人消息
struct MsgSetReceiveStrangerReq : public MsgRelationModule
{
    MsgSetReceiveStrangerReq()
    {
        header.dwType = MSG_SETRECEIVESTRANGERREQ;
        header.stLength = sizeof( MsgSetReceiveStrangerReq );
    }

    unsigned short ustMessageRefuse;    // 拒绝聊天消息设定
};

// 注册一个师傅或者徒弟信息到服务器列表中
struct MsgRegisterRelationReq : public MsgRelationModule
{
    MsgRegisterRelationReq()
    {
        header.dwType = MSG_REGISTERRELATIONREQ;
        header.stLength = sizeof( MsgRegisterRelationReq );
    }

    unsigned short ustRelation;     // 师傅 or 徒弟 关系
};

// 发送师傅 or 徒弟 列表给客户端
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

    unsigned short ustRelation;     // 师傅 or 徒弟 关系

    uint16 ustCount;            // ustCount = 0 说明没有查询到结果
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

// 通知客户端添加某种关系的剩余时间
struct MsgTellAddRelationTimeLeft : public MsgRelationModule
{
    MsgTellAddRelationTimeLeft()
    {
        header.dwType = MSG_TELLADDRELATIONTIMELEFT;
        header.stLength = sizeof( MsgTellAddRelationTimeLeft );
        nTimeLeft = 0;
    }

    unsigned short ustRelation;
    unsigned int nTimeLeft;     // 剩余时间: 秒
};

struct MsgStudentLevelUp : public MsgRelationModule
{
    MsgStudentLevelUp()
    {
        header.dwType = MSG_STUDENTLEVELUP;
        header.stLength = sizeof( MsgStudentLevelUp );
    }

    unsigned int nStudentID;
    bool bIsStudent;                    // true = 自己的徒弟   false = 徒弟的徒弟

    unsigned int nRewardExp;            // 奖励的经验
    unsigned int nRewardMasterValue;    // 奖励威望
};

// 通知全世界某2个人加了某种关系, 主要是夫妻关系
struct MsgTellWorldAddRelation : public MsgRelationModule
{
    MsgTellWorldAddRelation()
    {
        header.dwType = MSG_TELLWORLDADDRELATION;
        header.stLength = sizeof( MsgTellWorldAddRelation );
    }

    unsigned short ustRelation;                         // 添加的关系( 夫妻关系 用 eTellClient_Marriage 这个字串 )
    char szPlayer1[ RelationDefine::MaxNameLength ];
    char szPlayer2[ RelationDefine::MaxNameLength ];
};

// 请求更改个性签名 ( 请求后服务器不回馈, 客户端直接保存新的个性签名 )
struct MsgChangeSignatureReq : public MsgRelationModule
{
    MsgChangeSignatureReq()
    {
        header.dwType = MSG_CHANGESIGNATUREREQ;
        header.stLength = sizeof( MsgChangeSignatureReq );
    }

    char szSignature[ RelationDefine::MaxSignLength ];
};

// 个人资料 (Enterworld发送 S->C)
struct MsgPersonalInfo : public Msg
{
	MsgPersonalInfo()
	{
		header.dwType = MSG_PERSONALINFO;
		header.stLength = sizeof( MsgPersonalInfo );
	}
	PersonalInfo xPersonalInfo;
};

// 更改个人信息
struct MsgChangePersonalInfo : public MsgRelationModule
{
	MsgChangePersonalInfo()
	{
		header.dwType = MSG_CHANGEPERSONALINFO;
		header.stLength = sizeof( MsgChangePersonalInfo );
	}

	PersonalInfo xPersonalInfo;
};

// 按条件搜索玩家
struct MsgFindByCondiotion : public MsgRelationModule
{
	MsgFindByCondiotion()
	{
		header.dwType = MSG_FINDBYCONDITION;
		header.stLength = sizeof( MsgFindByCondiotion );
	}
	unsigned char	uchUnlimit;			// 不限条件

	unsigned char	uchSex;				// 性别 ESexType
	unsigned char	uchAgeMin;			// 年龄段
	unsigned char	uchAgeMax;
	char	szProvince[RelationDefine::ProvinceLength];			// 省份
	char	szCity[RelationDefine::CityLength];					// 城市
};

// 请求添加一个分组
struct MsgRelationGroupAddReq : public MsgRelationModule
{
    MsgRelationGroupAddReq()
    {
        header.dwType = MSG_RELATIONGROUPADDREQ;
        header.stLength = sizeof( MsgRelationGroupAddReq );

        memset( szGroup, 0, sizeof( szGroup ) );
    }

    char szGroup[ RelationDefine::GroupLength ];    // 分组名字
};

// 请求修改分组名字
struct MsgRelationGroupChangeNameReq : public MsgRelationModule
{
    MsgRelationGroupChangeNameReq()
    {
        header.dwType = MSG_RELATIONGROUPCHANGENAMEREQ;
        header.stLength = sizeof( MsgRelationGroupChangeNameReq );

        memset( szGroup, 0, sizeof( szGroup ) );
    }

    unsigned char uchGroupID;                       // 分组ID
    char szGroup[ RelationDefine::GroupLength ];    // 分组名字( 如果要删除分组, 把分组名字设置为空 )
};

// 服务器同步分组信息给客户端
struct MsgTellRelationGroup : public MsgRelationModule
{
    MsgTellRelationGroup()
    {
        header.dwType = MSG_TELLRELATIONGROUP;
        header.stLength = sizeof( MsgTellRelationGroup );
    }

    unsigned char uchGroupID;                       // 分组ID
    char szGroup[ RelationDefine::GroupLength ];    // 分组名字( 如果为空, 就是删除分组 客户端把该分组成员全部放入默认分组中 )
};

// 请求将好友放入某分组
struct MsgRelationGroupChangeReq : public MsgRelationModule
{
    MsgRelationGroupChangeReq()
    {
        header.dwType = MSG_RELATIONGROUPCHANGEREQ;
        header.stLength = sizeof( MsgRelationGroupChangeReq );
    }

    unsigned int nPlayerID;     // 好友ID
    unsigned char uchGroupID;   // 分组ID
};

// 服务器回应好友分组
struct MsgRelationGroupChangeAck : public MsgRelationModule
{
    MsgRelationGroupChangeAck()
    {
        header.dwType = MSG_RELATIONGROUPCHANGEACK;
        header.stLength = sizeof( MsgRelationGroupChangeAck );
    }

    unsigned int nPlayerID;     // 好友ID
    unsigned char uchGroupID;   // 分组ID
};

// 请求更新好友备注( 客户端修改好直接保存 )
struct MsgRelationRemarkChangeReq : public MsgRelationModule
{
    MsgRelationRemarkChangeReq()
    {
        header.dwType = MSG_RELATIONREMARTCHANGEREQ;
        header.stLength = sizeof( MsgRelationRemarkChangeReq );
    }

    unsigned int nPlayerID;         // 好友DBID
    char szRemark[ RelationDefine::ReMarkLength ];  // 备注
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// 以下服务器间消息

// 请求好友列表
struct CS2DBRelationListReq : public MsgRelationModule
{
    CS2DBRelationListReq()
    {
        header.dwType = CS2DB_RELATIONLISTREQ;
        header.stLength = sizeof( CS2DBRelationListReq );
    }
};

// 应答关系属性列表
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

// 应答关系数据列表
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

// 请求添加好友
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

// 请求添加属性
struct CS2DBAddAttributeReq : public MsgRelationModule
{
    CS2DBAddAttributeReq()
    {
        header.dwType = CS2DB_ADDATTRIBUTEREQ;
        header.stLength = sizeof( CS2DBAddAttributeReq );
    }

    RelationAttributeToServer xAttribute;
};

// 请求更新关系属性信息
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

// 请求更新个人资料
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

// 更新好友分组信息
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

// 更新好友关系信息
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
// 发送关系列表到服务器
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

// 玩家上线了
struct CS2GSRelationOnLine : public MsgRelationModule
{
    CS2GSRelationOnLine()
    {
        header.dwType = CS2GS_RELATIONONLINE;
        header.stLength = sizeof( CS2GSRelationOnLine );
    }

    unsigned int nPlayerID;
};

// 玩家下线了
struct CS2GSRelationOutLine : public MsgRelationModule
{
    CS2GSRelationOutLine()
    {
        header.dwType = CS2GS_RELATIONOUTLINE;
        header.stLength = sizeof( CS2GSRelationOutLine );
    }

    unsigned int nPlayerID;
};

// 添加关系属性
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

// 更新属性关系
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

// 更新个人资料
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


//请求 被邀请者的信息
struct GS2CSAddRelationReq : public MsgRelationModule
{
    GS2CSAddRelationReq()
    {
        header.dwType = GS2CS_ADDRELAITONREQ;
        header.stLength = sizeof( GS2CSAddRelationReq );

        uchGroupID = 0;
    }

    unsigned int nReqID;   // 请求者ID
    unsigned int nAckID;   // 被邀请者ID        

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

    unsigned int nReqID;        // 请求者
    unsigned int nAckID;        // 要删除的玩家
    unsigned short stRelation;  // 要删除的关系
};

struct CS2GSRemoveRelationAck : public MsgRelationModule
{
    CS2GSRemoveRelationAck()
    {
        header.dwType = CS2GS_DELETERELATIONACK;
        header.stLength = sizeof( CS2GSRemoveRelationAck );
    }

    unsigned int nReqID;        // 请求者
    unsigned int nAckID;        // 要删除的玩家
    unsigned short stRelation;  // 要删除的关系
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

	unsigned char	uchUnlimit;			// 不限条件
	unsigned char	uchSex;				// 性别 ESexType
	unsigned char	uchAgeMin;			// 年龄段
	unsigned char	uchAgeMax;
	char	szProvince[RelationDefine::ProvinceLength];			// 省份
	char	szCity[RelationDefine::CityLength];					// 城市
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
    unsigned int nStudentID;    // 如果 nStudentID = 0直接显示 你的徒弟们   != 0;
    bool bIsStudent;            // true = 自己的徒弟   false = 徒弟的徒弟

    unsigned int nRewardExp;            // 奖励的经验
    unsigned int nRewardMasterValue;    // 奖励威望
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