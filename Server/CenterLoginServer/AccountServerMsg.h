#ifndef __AccountServerMsg_H__
#define __AccountServerMsg_H__
#pragma once

#include "MessageDefine.h"

#pragma pack( push, 1 ) 

enum eAccountMsg
{
	eAccountMsg_begin = 0,
	eAccountMsg_ChenckAccount = 1,
	eAccountMsg_CheckSucc = 6,
	eAccountMsg_KickAccount = 7,
	eAccountMsg_CheckFail = 8,
	eAccountMsg_AuthConnect = 9,
	eAccountMsg_ReqConnect = 10,
	eAccountMsg_BlockAccount = 11,
	eAccountMsg_PwdCardReq = 12,
	eAccountMsg_PwdCardAck = 13,
	eAccountMsg_max,
};

struct MsgCheckAccount:public Msg
{
	struct SContent
	{
		char account_name[17];
		char pwds[14];
	};
	MsgCheckAccount()
	{
		header.stLength = sizeof(MsgCheckAccount);
		header.dwType   = eAccountMsg_ChenckAccount;
		memset(&content,0,sizeof(SContent));
		memset(sign,0,33);
	}
	SContent content;
	char     sign[33];
};

struct MsgAuthConnect:public Msg
{
	struct SContent
	{
		char chKey[16];
	};
	MsgAuthConnect()
	{
		header.stLength = sizeof(MsgAuthConnect);
		header.dwType   = eAccountMsg_AuthConnect;

		memset(&content,0,sizeof(SContent));
		memset(sign,0,33);
	}
	SContent content;
	char     sign[33];
};

struct MsgCheckAccountSucc:public Msg
{
	struct SContent
	{
		char account_name[17];     //帐号名字
		unsigned long account_id; //帐号ID 4
		unsigned char is_wallow; //是否成年人 1
		//char account_name[16];
	};
	MsgCheckAccountSucc()
	{
		header.stLength = sizeof(MsgCheckAccountSucc);
		header.dwType   = eAccountMsg_CheckSucc;

		memset(&content,0,sizeof(SContent));
		memset(sign,0,33);
	}
	SContent content;
	char     sign[33];
};

struct MsgKickAccount:public Msg
{
	struct SContent
	{
		char account_name[17];
		unsigned long account_id;
	};
	MsgKickAccount()
	{
		header.stLength = sizeof(MsgKickAccount);
		header.dwType   = eAccountMsg_KickAccount;

		memset(&content,0,sizeof(SContent));
		memset(sign,0,33);
	}
	SContent content;
	char     sign[33];
};

enum eFail
{
	eFail_Succ = 1,//成功
	eFail_NoAccount = 2,// 帐号不存在 帐号不存在 帐号不存在
	eFail_PWDSError = 3,// 密码错误 密码错误
	eFail_NoServer = 4,// 无法连接到服务器 无法连接到服务器 无法连接到服务器 无法连接到服务器
	eFail_NoActive = 5,// 针对 OB 未激活帐号 未激活帐号 未激活帐号
	eFail_SecondPwdsError = 6,// 二次验证码错误 二次验证码错误 二次验证码错误 二次验证码错误
	eFail_PwdCardChect = 7,//密保卡输入有误
	eFail_UnKown = 8,//未知错误
};

struct MsgCheckFail:public Msg
{
	struct SContent
	{
		short result;
	};
	MsgCheckFail()
	{
		header.stLength = sizeof(MsgCheckFail);
		header.dwType   = eAccountMsg_CheckFail;

		memset(&content,0,sizeof(SContent));
		memset(sign,0,33);
	}
	SContent content;
	char     sign[33];
};

struct MsgReqConnect:public Msg
{
	struct SContent
	{
		char result;
	};
	MsgReqConnect()
	{
		header.stLength = sizeof(MsgReqConnect);
		header.dwType   = eAccountMsg_ReqConnect;

		memset(&content,0,sizeof(SContent));
		memset(sign,0,33);
	}
	SContent content;
	char     sign[33]; 
};

struct MsgBlockAccount:public Msg
{
	struct SContent
	{
		char account_name[17];
		unsigned long account_id;
		unsigned long blocktime;
	};
	MsgBlockAccount()
	{
		header.stLength = sizeof(MsgBlockAccount);
		header.dwType   = eAccountMsg_BlockAccount;

		memset(&content,0,sizeof(SContent));
		memset(sign,0,33);
	}
	SContent content;
	char     sign[33]; 
};

struct MsgPwdCardReq:public Msg
{
	MsgPwdCardReq()
	{
		header.stLength = sizeof(MsgPwdCardReq);
		header.dwType   = eAccountMsg_PwdCardReq;

		memset(PwdCardSerialNumber,0,PwdCardSerialLength);
		memset(A,0,PwdCardLength);
		memset(B,0,PwdCardLength);
		memset(C,0,PwdCardLength);
	}
	char	 PwdCardSerialNumber[PwdCardSerialLength];
	char     A[PwdCardLength]; 
	char     B[PwdCardLength]; 
	char     C[PwdCardLength]; 
};
struct MsgPwdCardAck:public Msg
{
	struct SContent 
	{
		char	 account_name[17];
		// 序列号
		char	 PwdCardSerialNumber[PwdCardSerialLength];
		// 横列信息
		char     crA[PwdCardLength]; 
		char     crB[PwdCardLength]; 
		char     crC[PwdCardLength]; 
		// 数字
		char     A[PwdCardLength]; 
		char     B[PwdCardLength]; 
		char     C[PwdCardLength]; 
	};
	MsgPwdCardAck()
	{
		header.stLength = sizeof(MsgPwdCardAck);
		header.dwType   = eAccountMsg_PwdCardAck;

		memset(&content,0,sizeof(SContent));
		memset(sign,0,33);
	}
	
	SContent content;
	char     sign[33];
};

#pragma pack( pop ) 

#endif