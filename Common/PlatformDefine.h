/********************************************************************
Filename:    PlatformDefine.h
MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __COMMON_PLATFORMDEFINE_H__
#define __COMMON_PLATFORMDEFINE_H__

#pragma once

#pragma pack( push, 1 )

// 旧的,新的做完就废弃
struct SAddPoints
{
	uint32 guid;          // 用户id
	uint32 gssid;         // 充值游戏服务器的id  
	uint8  typeId;        // 1--paycard  2--paynet  3--esales
	int8   typesn[32];    // 订单号
	uint32 points;        // 加点数
	uint16 discount;      // 折扣
	uint32 addamount;     // 充值钱数
	uint32 netincome;     // 净收入
	int8   signstr[32+1]; // 签名
	int8   remark[32+1];  // 备注
	int8   userip[17];    // ip地址 
	int8   gateway[17];   // 网关 
	uint8  channel;       // 通道
	uint32 paytime;       // 订单生效时间
};

// 平台给的PayInfo信息
enum EPayFlagType
{
	EPayFlagType_WaitingProcess, // 等待处理
	EPayFlagType_Processing    , // 处理中
	EPayFlagType_ProcessOver   , // 处理完成
};

enum EAccountPointOpType
{
	EAPOT_Sub, // 减点
	EAPOT_Add, // 加点
	EAPOT_Set, // 设置点
};

struct SPayInfo
{ // 其他数据结构不关心,只需要打log出来
	int32  pid         ;
	int32  gssid       ;
	int8   passport[33];
	uint32 guid        ; // 账号id
	int16  typeId      ; // 订单号全局唯一
	int8   typesn[31]  ;
	int32  addpoint    ; // 要加的点数
	int32  discount    ;
	int32  addamount   ;
	int32  netincome   ;
	int8   remark[32]  ;
	int8   userip[21]  ;
	int8   gateway[21] ;
	int16  channel     ;
	int    paytime     ;
	int8   flag        ; // 默认为0---未加点 1---加点成功
	int    ctime       ; // 充值时间
};

//struct SGMTaskInfo
//{
//    uint32 id         ; // taskid
//    uint8  type       ; // task类型 协议标示符
//    int8   values[256]; // 参数值
//    int32  ctime      ; // 时间
//    int8   result[31] ; // 结果参数值
//    int32  stateTime  ; // 状态时间
//    int8   flag       ; // 标示位 默认为0-未处理 1-处理成功 2-处理中
//};

enum eTaskResult
{
	eTaskResult_ConntenMax = 256,
	eTaskResult_ResNo	   = -1,//需要做的
	eTaskResult_ResSucc	   = 0,//已经完成
	eTaskResult_ResWaiting = 1,//等待结果	
	eTaskResult_ResFail	   = 2,//执行失败
	eTaskResult_ResFail2	   = 3,//执行失败
	eTaskResult_ResFail3	   = 4,//执行失败
	eTaskResult_AllServer  = -1,//对所有的server都执行
};

struct SGMTaskInfo
{
	SGMTaskInfo(){memset(this, 0, sizeof(*this));}
	~SGMTaskInfo(){}
	uint32 id								;//id
	char   content[eTaskResult_ConntenMax]	;//命令内容,需要解析
	int16 serverid							;//操作
	int16  result							;//结果
};

enum ETaskInfo
{  
	ETaskInfo_NameMaxLength		 = 33,					//收件人的名字大小
	ETaskInfo_MoneySendMax        = 200 * 10000,      // 最多寄200金
	ETaskInfo_MailMaxCount        = 100,              // 收件箱可保存邮件的上限为100封    
	ETaskInfo_MailFullNotifyCount = 90,               // 邮箱容量超过90封系统提示清理邮箱    
	ETaskInfo_AddressNameSize     = 32+1,			  // 地址
	ETaskInfo_HoldMailDays        = 30,               // 邮箱里的存放时间
	ETaskInfo_MailFee             = 50,               // 每份邮件的邮资    
	ETaskInfo_MailContentMax      = 50 * 2,           // 每份邮件的最大字符数    
	ETaskInfo_TileMaxCount        = 32,               // 邮件标题
	ETaskInfo_MailAccessorySize   = 300,              // 附件大小
	ETaskInfo_FromMaxCount        = 1,                // 发信人的个数
	ETaskInfo_ToMaxCount          = 1,                // 目标最大个数
	ETaskInfo_OtherSendMaxCount   = 6,                // 抄送
	ETaskInfo_TargetMaxCount      = ETaskInfo_ToMaxCount + ETaskInfo_OtherSendMaxCount,
	ETaskInfo_OwnerMaxCount       = ETaskInfo_FromMaxCount + ETaskInfo_TargetMaxCount,

	ETaskInfo_FromIndex           = 0,                              // 发信人在数组中的位置
	ETaskInfo_ToIndex             = ETaskInfo_FromIndex + ETaskInfo_FromMaxCount, // 收信人在数组中的位置
	ETaskInfo_OtherIndex          = ETaskInfo_ToIndex + ETaskInfo_ToMaxCount,     // 抄送人在数组中的位置

	ETaskInfo_ActivityIDArray	  = 30,				//最大的id数量集
};

enum eMailType
{
	eMailType_maillist = 0, //从数据库中获得的邮件数据
	eMailType_Present = 1, //是present触发的邮件
	eMailType_Activity = 2, //是Activity触发的邮件
};

struct SMailTaskInfo
{
	SMailTaskInfo(){memset(this, 0, sizeof(*this));}
	~SMailTaskInfo(){}
	uint32 id				;//id
	uint32 characterid		;//角色DB ID
	char   charactername[ETaskInfo_NameMaxLength]	;//角色名字
	char   title[ETaskInfo_TileMaxCount]			;//邮件标题
	char   content[ETaskInfo_MailContentMax]			;//邮件正文
	uint32 money			;//银币
	uint16 itemid			;//物品ID
	uint16 itemcount		;//物品数量
	int16  serverid			;//服务器id
	int16  result			;//结果
	uint8  _type			;//邮件类型
};

///////////////////////////////////////////////////////////////
enum eWorkSpaceTask
{
	eWorkSpaceTask_SNLength   = 33,//sn长度

	eWorkSpaceTask_AskPresent = 0,//请求present
	eWorkSpaceTask_AskActivity = 1,//请求活动
	eWorkSpaceTask_EpistarPoint = 2,//游戏对晶元积分点的操作 by cloud
};

struct SAskPresent
{
	char   charactername[ETaskInfo_NameMaxLength];
	uint32 characterid;
	uint32 accountid;
	char   sn[eWorkSpaceTask_SNLength];	
};

struct SAskAvtivity
{
	char   charactername[ETaskInfo_NameMaxLength];
	uint32 characterid;
	uint32 accountid;
	int32  _type;
	uint32 idArray[ETaskInfo_ActivityIDArray];
};
struct SEpistarPoint
{
	char   charactername[ETaskInfo_NameMaxLength];
	uint32 characterid;
	uint32 accountid;
	int32  _type;
	uint16 nItemId;
	uint16 nPoint;
};

struct SWorkSpaceTask
{
	SWorkSpaceTask(){memset(this, 0, sizeof(*this));}
	~SWorkSpaceTask(){}

	union
	{
		SAskPresent		askpresent;
		SAskAvtivity	askactivity;
		SEpistarPoint   askEpistarPoint;
	}s;

	uint16 tasktype;
	uint16 serverid;
	int16  result;
};

enum eError
{	
	eError_NoActivity = 0,//无活动奖励或者已经领取过了
	eError_SNError = 1,//序列号错误
	eError_AccountError = 2,//帐号已经领取过了
	eError_CharacterError = 3,//角色已经领取过了
	eError_PresentSucc = 4,//领取奖励成功
	eError_ActivitySucc = 5,//领取奖励成功
	eError_EpistarPointSucc = 6,//晶元点添加成功
	eError_EpistarPointError = 7,//晶元点添加失败
	eError_Unkown//未知错误
};

struct SErrorInfo
{
	SErrorInfo()
	{
		memset(this, 0, sizeof(*this));
		result = eError_Unkown;
	}
	~SErrorInfo(){}
	uint32 accountid		;//帐号ID
	uint32 characterid		;//角色DB ID
	int16  serverid			;//服务器id
	int16  result			;//结果
};

#pragma pack( pop )

#endif // __COMMON_PLATFORMDEFINE_H__
