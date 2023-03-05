#ifndef __DATABASE_AccountBillingDefine_H__
#define __DATABASE_AccountBillingDefine_H__

#pragma once

//#include <map>
#include "MeRTLibs.h"
#include "DBMessageDefine.h"
#include "Mutex.h"

//using namespace std;
//操作flag
enum eMoneyOperate
{
	eMoneyOperate_sub =0,
	eMoneyOperate_add,
	eMoneyOperate_set,
	eMoneyOperate_max
};

//帐号点数结构
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
	uint32 OperateConsumeScore(uint32 account_id,uint32 ConsumeScore,eMoneyOperate emo); //操作商城积分（实时存数据库的）
	uint32 GetAccountMoneyById(uint32 account_id);
	uint32 GetAccountConsumeScoreById(uint32 account_id);
	void   MakeMoneyData( DBMsgAckEnterWorld& ack,uint32 account_id);
public:
	typedef map<uint32,SAccountMoney*> mapMoneyCache;//所有的点数集合
private:
	mapMoneyCache				  _mapMoneyCache;
	mapMoneyCache                 _mapConsumeScoreCache;
	CSemiAutoIntLock              _Lock;
};

#define theAccountMoneyCache CAccountMoneyCache::Instance()

#endif