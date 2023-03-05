#ifndef __DATABASE_AccountBillingDefine_H__
#define __DATABASE_AccountBillingDefine_H__

#pragma once

//#include <map>
#include "MeRTLibs.h"
#include "DBMessageDefine.h"
#include "Mutex.h"

//using namespace std;
//����flag
enum eMoneyOperate
{
	eMoneyOperate_sub =0,
	eMoneyOperate_add,
	eMoneyOperate_set,
	eMoneyOperate_max
};

//�ʺŵ����ṹ
struct SAccountMoney
{
	uint32 account_id;
	uint32 account_money;
};

class CAccountMoneyCache
{
public:
	CAccountMoneyCache();
	~CAccountMoneyCache();

	static CAccountMoneyCache& Instance()
	{
		static CAccountMoneyCache camc;
		return camc;
	}


	uint32 OperateMoney(uint32 account_id,uint32 money,eMoneyOperate emo);	
	uint32 OperateConsumeScore(uint32 account_id,uint32 ConsumeScore,eMoneyOperate emo); //�����̳ǻ��֣�ʵʱ�����ݿ�ģ�
	uint32 GetAccountMoneyById(uint32 account_id);
	uint32 GetAccountConsumeScoreById(uint32 account_id);
	void   MakeMoneyData( DBMsgAckEnterWorld& ack,uint32 account_id);
public:
	typedef map<uint32,SAccountMoney*> mapMoneyCache;//���еĵ�������
private:
	mapMoneyCache				  _mapMoneyCache;
	mapMoneyCache                 _mapConsumeScoreCache;
	CSemiAutoIntLock              _Lock;
};

#define theAccountMoneyCache CAccountMoneyCache::Instance()

#endif