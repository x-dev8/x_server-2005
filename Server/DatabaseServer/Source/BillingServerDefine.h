#ifndef __BillingServerDefine_H__
#define __BillingServerDefine_H__
#pragma once

#include "MessageDefine.h"

#pragma pack( push, 1 ) 

enum eBillingServerMsgDefine
{
	eBillServerMsgDefine_begin = 0,
	eBillServerMsgDefine_AuthConnect = 1, //��֤
	eBillServerMsgDefine_AuthReq,         //��֤����
	eBillServerMsgDefine_Cash,			  //�Ʒѳ�ֵ��Ǯ
	eBillServerMsgDefine_SnCheck,         //��billing serverȷ�϶����Ƿ���ȷ
	eBillServerMsgDefine_SnCheckReq,      //billing server���ظ�֪����������
	eBillServerMsgDefine_CashResult,	  //��ֵ�����֪billing server
	
	//������س�ֵ
	eBillServerMsgDefine_Score,			  //�Ʒѳ�ֵ�����
	eBillServerMsgDefine_ScoreSnCheck,    //��billing serverȷ�϶����Ƿ���ȷ
	eBillServerMsgDefine_ScoreSnCheckReq, //billing server���ظ�֪����������
	eBillServerMsgDefine_ScoreResult,	  //��ֵ�����֪billing server

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
		char			sn[16]; //Ψһ����
		unsigned long	account_id;//�ʺ�ID
		int             money;     //�����Ǯ
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
	eCashResult_succ = 0,        //��ֵ�ɹ�
	eCashResult_cashed = 1,      //�Ѿ���ֵ�ɹ�
	eCashResult_checkerror = 2,  //����ȷ��ʧ��
	eCashResult_max               //δ֪����
};

struct MsgBillingCashResult:public Msg
{
	struct SContent
	{
		char			sn[16]; //Ψһ����
		char            result; //��ֵ���
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
		char			sn[16]; //Ψһ����
		unsigned long	account_id;//�ʺ�ID
		int             money;     //�����Ǯ
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
	eSnCheckReq_suc = 0,    //������Ϣȷ�ϳɹ�
	eSnCheckReq_cashed = 1, //�����ѳ�ֵ
	eSnCheckReq_fail = 2,     //ȷ��ʧ��
	eSnCheckReq_snError = 3,  //���Ŵ���
	eSnCheckReq_max             //δ֪����
};

struct MsgBillingSnCheckReq:public Msg
{
	struct SContent
	{
		char			sn[16]; //Ψһ����
		char            result; //ȷ�Ͻ��
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

//�������
struct MsgBillingScore:public Msg
{
	struct SContent
	{
		char			sn[16]; //Ψһ����
		unsigned long	account_id;//�ʺ�ID
		int             _value;     //�����Ǯ
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
		char			sn[16]; //Ψһ����
		unsigned long	account_id;//�ʺ�ID
		int             _value;     //�����Ǯ
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
		char			sn[16]; //Ψһ����
		char            result; //ȷ�Ͻ��
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
		char			sn[16]; //Ψһ����
		char            result; //��ֵ���
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