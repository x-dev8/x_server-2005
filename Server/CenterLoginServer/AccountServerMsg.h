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
		char account_name[17];     //�ʺ�����
		unsigned long account_id; //�ʺ�ID 4
		unsigned char is_wallow; //�Ƿ������ 1
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
	eFail_Succ = 1,//�ɹ�
	eFail_NoAccount = 2,// �ʺŲ����� �ʺŲ����� �ʺŲ�����
	eFail_PWDSError = 3,// ������� �������
	eFail_NoServer = 4,// �޷����ӵ������� �޷����ӵ������� �޷����ӵ������� �޷����ӵ�������
	eFail_NoActive = 5,// ��� OB δ�����ʺ� δ�����ʺ� δ�����ʺ�
	eFail_SecondPwdsError = 6,// ������֤����� ������֤����� ������֤����� ������֤�����
	eFail_PwdCardChect = 7,//�ܱ�����������
	eFail_UnKown = 8,//δ֪����
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
		// ���к�
		char	 PwdCardSerialNumber[PwdCardSerialLength];
		// ������Ϣ
		char     crA[PwdCardLength]; 
		char     crB[PwdCardLength]; 
		char     crC[PwdCardLength]; 
		// ����
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