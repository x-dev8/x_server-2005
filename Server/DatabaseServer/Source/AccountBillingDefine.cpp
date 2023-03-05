#include "AccountBillingDefine.h"
#include "ErrorCode.h"
#include "DatabaseServerApp.h"

CAccountMoneyCache::CAccountMoneyCache()
{
	_mapMoneyCache.clear();
	_mapConsumeScoreCache.clear();
}
CAccountMoneyCache::~CAccountMoneyCache()
{
	mapMoneyCache::iterator itr = _mapMoneyCache.begin();
	while(itr != _mapMoneyCache.end())
	{
		delete itr->second;
		itr++;
	}
	_mapMoneyCache.clear();

	mapMoneyCache::iterator itr1 = _mapConsumeScoreCache.begin();
	while(itr1 != _mapConsumeScoreCache.end())
	{
		delete itr1->second;
		itr1++;
	}
	_mapConsumeScoreCache.clear();

}

uint32 CAccountMoneyCache::GetAccountMoneyById(uint32 account_id)
{
	CSALocker lock(_Lock);
	mapMoneyCache::iterator itr = _mapMoneyCache.find(account_id);
	if (itr != _mapMoneyCache.end())
	{
		return itr->second->account_money;
	}
	return 0;
}

uint32 CAccountMoneyCache::GetAccountConsumeScoreById(uint32 account_id)
{
	CSALocker lock(_Lock);
	mapMoneyCache::iterator itr = _mapConsumeScoreCache.find(account_id);
	if (itr != _mapConsumeScoreCache.end())
	{
		return itr->second->account_money;
	}
	return 0;
}

uint32 CAccountMoneyCache::OperateConsumeScore(uint32 account_id,uint32 ConsumeScore,eMoneyOperate emo)
{
	if (ConsumeScore < 0)
	{
		return ER_Success;
	}

	CSALocker lock(_Lock);
	uint32 result = ER_Failed;
	mapMoneyCache::iterator itr = _mapConsumeScoreCache.find(account_id);
	if (itr != _mapConsumeScoreCache.end())
	{
		switch(emo)
		{
		case eMoneyOperate::eMoneyOperate_add:
			{
				itr->second->account_money += ConsumeScore;
				result = ER_Success;
			}
			break;
		case eMoneyOperate::eMoneyOperate_sub:
			{
				if (itr->second->account_money < ConsumeScore)
				{
					result = ER_Failed;
				}
				else
				{
					itr->second->account_money -= ConsumeScore;
					result = ER_Success;
				}
			}
			break;
		case eMoneyOperate::eMoneyOperate_set:
			{
				itr->second->account_money = ConsumeScore;
				result = ER_Success;
			}
			break;
		}
	}
	else
	{
		//新加记录一定要是添加FLAG
		if (eMoneyOperate::eMoneyOperate_set == emo)
		{
			SAccountMoney* pAccountMoney = new SAccountMoney;
			pAccountMoney->account_id = account_id;
			pAccountMoney->account_money = ConsumeScore;

			_mapConsumeScoreCache.insert(mapMoneyCache::value_type(pAccountMoney->account_id,pAccountMoney));
			result = ER_Success;
		}
	}
	return result;

}

uint32 CAccountMoneyCache::OperateMoney(uint32 account_id,uint32 money,eMoneyOperate emo)
{
	if (money < 0)
	{
		return ER_Success;
	}
	CSALocker lock(_Lock);
	uint32 result = ER_Failed;
	mapMoneyCache::iterator itr = _mapMoneyCache.find(account_id);
	if (itr != _mapMoneyCache.end())
	{
		switch(emo)
		{
		case eMoneyOperate::eMoneyOperate_add:
			{
				itr->second->account_money += money;
				result = ER_Success;
			}
			break;
		case eMoneyOperate::eMoneyOperate_sub:
			{
				if (itr->second->account_money < money)
				{
					result = ER_Failed;
				}
				else
				{
					itr->second->account_money -= money;
					result = ER_Success;
				}
			}
			break;
		case eMoneyOperate::eMoneyOperate_set:
			{
				itr->second->account_money = money;
				result = ER_Success;
			}
			break;
		}
	}
	else
	{
		//新加记录一定要是添加FLAG
		if (eMoneyOperate::eMoneyOperate_set == emo)
		{
			SAccountMoney* pAccountMoney = new SAccountMoney;
			pAccountMoney->account_id = account_id;
			pAccountMoney->account_money = money;

			_mapMoneyCache.insert(mapMoneyCache::value_type(pAccountMoney->account_id,pAccountMoney));
			result = ER_Success;
		}
	}
	return result;
}

void CAccountMoneyCache::MakeMoneyData( DBMsgAckEnterWorld& ack,uint32 account_id )
{
	CSALocker lock(_Lock);
	if (GetDatabaseServerApp()->m_bAccountBilling)
	{
		ack.charinfo.baseinfo.liveinfo.jinDing = GetAccountMoneyById(account_id);

		//lyh商城积分赋值
		ack.charinfo.baseinfo.liveinfo.ConsumeScore = GetAccountConsumeScoreById(account_id);
	}
}