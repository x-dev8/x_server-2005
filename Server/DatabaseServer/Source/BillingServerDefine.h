#ifndef __BillingServerDefine_H__
#define __BillingServerDefine_H__
#pragma once

#include "MessageDefine.h"

#pragma pack( push, 1 ) 

enum eBillingServerMsgDefine
{
	eBillServerMsgDefine_begin = 0,
	eBillServerMsgDefine_AuthConnect = 1, //认证
	eBillServerMsgDefine_AuthReq,         //认证返回
	eBillServerMsgDefine_Cash,			  //计费充值冲钱
	eBillServerMsgDefine_SnCheck,         //向billing server确认订单是否正确
	eBillServerMsgDefine_SnCheckReq,      //billing server返回告知订单号详情
	eBillServerMsgDefine_CashResult,	  //充值结果告知billing server
	
	//积分相关充值
	eBillServerMsgDefine_Score,			  //计费充值冲积分
	eBillServerMsgDefine_ScoreSnCheck,    //向billing server确认订单是否正确
	eBillServerMsgDefine_ScoreSnCheckReq, //billing server返回告知订单号详情
	eBillServerMsgDefine_ScoreResult,	  //充值结果告知billing server

	eBillServerMsgDefine_max,
};

//send to billing server
struct MsgAuthConnect:public Msg
{
	struct SContent
	{
		char chKey[16];
	};
	MsgAuthConnect()
	{
		header.stLength = sizeof(MsgAuthConnect);
		header.dwType   = eBillServerMsgDefine_AuthConnect;

		memset(&content,0,sizeof(SContent));
		memset(sign,0,33);
	}
	SContent content;
	char     sign[33];
};

struct MsgBillingSnCheck:public Msg
{
	struct SContent
	{
		char			sn[16]; //唯一单号
		unsigned long	account_id;//帐号ID
		int             money;     //冲入的钱
	};
	MsgBillingSnCheck()
	{
		header.stLength = sizeof(MsgBillingSnCheck);
		header.dwType   = eBillServerMsgDefine_SnCheck;

		memset(&content,0,sizeof(SContent));
		memset(sign,0,33);
	}
	SContent content;
	char     sign[33];
};

enum eCashResult
{
	eCashResult_succ = 0,        //充值成功
	eCashResult_cashed = 1,      //已经充值成功
	eCashResult_checkerror = 2,  //单号确认失败
	eCashResult_max               //未知错误
};

struct MsgBillingCashResult:public Msg
{
	struct SContent
	{
		char			sn[16]; //唯一单号
		char            result; //充值结果
	};
	MsgBillingCashResult()
	{
		header.stLength = sizeof(MsgBillingCashResult);
		header.dwType   = eBillServerMsgDefine_CashResult;

		memset(&content,0,sizeof(SContent));
		memset(sign,0,33);
		content.result = eCashResult_max;
	}
	SContent content;
	char     sign[33];
};


//billing server send
struct MsgAuthConnectReq:public Msg
{
	struct SContent
	{
		char result;
	};
	MsgAuthConnectReq()
	{
		header.stLength = sizeof(MsgAuthConnectReq);
		header.dwType   = eBillServerMsgDefine_AuthReq;

		memset(&content,0,sizeof(SContent));
		memset(sign,0,33);
	}
	SContent content;
	char     sign[33];
};

struct MsgBillingCash:public Msg
{
	struct SContent
	{
		char			sn[16]; //唯一单号
		unsigned long	account_id;//帐号ID
		int             money;     //冲入的钱
	};
	MsgBillingCash()
	{
		header.stLength = sizeof(MsgBillingCash);
		header.dwType   = eBillServerMsgDefine_Cash;

		memset(&content,0,sizeof(SContent));
		memset(sign,0,33);
	}
	SContent content;
	char     sign[33];
};

enum eSnCheckReq
{
	eSnCheckReq_suc = 0,    //订单信息确认成功
	eSnCheckReq_cashed = 1, //订单已充值
	eSnCheckReq_fail = 2,     //确认失败
	eSnCheckReq_snError = 3,  //单号错误
	eSnCheckReq_max             //未知错误
};

struct MsgBillingSnCheckReq:public Msg
{
	struct SContent
	{
		char			sn[16]; //唯一单号
		char            result; //确认结果
	};
	MsgBillingSnCheckReq()
	{
		header.stLength = sizeof(MsgBillingSnCheckReq);
		header.dwType   = eBillServerMsgDefine_SnCheckReq;

		memset(&content,0,sizeof(SContent));
		memset(sign,0,33);
		content.result = eSnCheckReq_max;
	}
	SContent content;
	char     sign[33];
};

//积分相关
struct MsgBillingScore:public Msg
{
	struct SContent
	{
		char			sn[16]; //唯一单号
		unsigned long	account_id;//帐号ID
		int             _value;     //冲入的钱
	};
	MsgBillingScore()
	{
		header.stLength = sizeof(MsgBillingScore);
		header.dwType   = eBillServerMsgDefine_Score;

		memset(&content,0,sizeof(SContent));
		memset(sign,0,33);
	}
	SContent content;
	char     sign[33];
};

struct MsgBillingScoreSnCheck:public Msg
{
	struct SContent
	{
		char			sn[16]; //唯一单号
		unsigned long	account_id;//帐号ID
		int             _value;     //冲入的钱
	};
	MsgBillingScoreSnCheck()
	{
		header.stLength = sizeof(MsgBillingScoreSnCheck);
		header.dwType   = eBillServerMsgDefine_ScoreSnCheck;

		memset(&content,0,sizeof(SContent));
		memset(sign,0,33);
	}
	SContent content;
	char     sign[33];
};

struct MsgBillingScoreSnCheckReq:public Msg
{
	struct SContent
	{
		char			sn[16]; //唯一单号
		char            result; //确认结果
	};
	MsgBillingScoreSnCheckReq()
	{
		header.stLength = sizeof(MsgBillingScoreSnCheckReq);
		header.dwType   = eBillServerMsgDefine_ScoreSnCheckReq;

		memset(&content,0,sizeof(SContent));
		memset(sign,0,33);
		content.result = eSnCheckReq_max;
	}
	SContent content;
	char     sign[33];
};

struct MsgBillingScoreResult:public Msg
{
	struct SContent
	{
		char			sn[16]; //唯一单号
		char            result; //充值结果
	};
	MsgBillingScoreResult()
	{
		header.stLength = sizeof(MsgBillingScoreResult);
		header.dwType   = eBillServerMsgDefine_ScoreResult;

		memset(&content,0,sizeof(SContent));
		memset(sign,0,33);
		content.result = eCashResult_max;
	}
	SContent content;
	char     sign[33];
};

#pragma pack( pop ) 


#endif