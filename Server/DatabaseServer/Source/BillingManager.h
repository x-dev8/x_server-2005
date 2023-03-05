/********************************************************************
Filename:    BillingManager.h
MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __CENTER_BillingManager_H__
#define __CENTER_BillingManager_H__

#pragma once

#include "network.h"
#include "BillingServerDefine.h"
#include "memory_pool.h"
#include "DBMessageDefine.h"

using namespace network;

#define GiveUp_Time 1000*60 //抛单,1MIN
#define GiveUp_Degree 3     //几次确认没结果后抛单



class CBillingManager
{
public:
	enum ecs
	{
		ecs_tryconnect = 0,
		ecs_connected,
		ecs_max,
	};

	//充值信息
#pragma pack ( push, 1 )
	struct SCash:INHERIT_POOL(SCash)
	{
		char			sn[17]; //唯一单号
		unsigned long	account_id;//帐号ID
		int             money;     //冲入的钱
		unsigned long   check_time; //如果存在太久则作抛单处理
		char		    check_degree; //确认次数
		SCash()
		{
			memset(this,0,sizeof(SCash));
		}
	};

	struct SConsumeScore:INHERIT_POOL(SConsumeScore)
	{
		char			sn[17]; //唯一单号
		unsigned long	account_id;//帐号ID
		int             money;     //冲入的钱
		unsigned long   check_time; //如果存在太久则作抛单处理
		char		    check_degree; //确认次数
		SConsumeScore()
		{
			memset(this,0,sizeof(SCash));
		}
	};
#pragma pack ( pop )

public:
	CBillingManager(void);
	~CBillingManager(void);

	static CBillingManager& Instance()
	{
		static CBillingManager cbm;
		return cbm;
	}

	bool IsInService(){return _service;}
	bool IsScoreInService(){return _Scoreservice;}

	char TryConnectBillServer();
	char TryConnectBillScoreServer();

	void ProcessBillingServerMsg();
	void ReciveBillingMsg();
	void SendBillingMsg();

	void ProcessBillingScoreServerMsg();
	void ReciveBillingScoreMsg();
	void SendBillingScoreMsg();

	void SendMsgToBillingServer(Msg* pMsg);
	void SendMsgToBillingScoreServer(Msg* pMsg);

	void Run();

	string GetMsgMd5Sign(void* _input0,int _length0,void* _input1,int _length1);


	///////////////////logic//////////////////////
	void OnMsgAuthConnect	(Msg* pMsg,char servertype);//server type 0:元宝,1:积分
	void OnMsgCash			(Msg* pMsg);
	void OnMsgChenckSnResult(Msg* pMsg);

	void OnMsgConsumeScore	(Msg* pMsg);
	void OnMsgChenckConsumeScoreSnResult(Msg* pMsg);
	//////////////////////////////////////////////

	void ProcessUnCheckCash();//刷新下未确认订单
	void ProcessResultCash(); //刷新等待充值结果的订单
	void ProcessCheckedCash();//每帧处理已经添加的充值请求
	//void AckCashResult();	  //返回充值结果
	void ProcessUnCheckConsumeScore();//刷新下未确认订单
	void ProcessResultConsumeScore(); //刷新等待充值结果的订单
	void ProcessCheckedConsumeScore();//每帧处理已经添加的充值请求

	void OnDBMsgCashResult(DB2DBCashResult* pMess);
	void OnDBMsgConsumeSocreResult(DB2DBConsumeScoreResult* pMess);

	bool IsCanAddCashInfo(const char* sn);
	bool IsCanAddScoreInfo(const char* sn);

	void PrintfInfo(const char* szFormat, ...);
	
private:
	Socketer*		 m_pConnector;
	char			 connect_state;
	unsigned long    ping_time;        //发送ping的时间
	unsigned long    check_ping_time;  //最后一次检测PING通过的时间
	bool             _service;         //服务是否开启,需要认证后设置

	Socketer*		 m_pScoreConnector;
	char			 Scoreconnect_state;
	unsigned long    Scoreping_time;        //发送ping的时间
	unsigned long    Scorecheck_ping_time;  //最后一次检测PING通过的时间
	bool             _Scoreservice;         //服务是否开启,需要认证后设置

	typedef map<string,SCash*> mapCash;
	mapCash m_mapCash;					//接收到,但是未处理的订单
	mapCash m_mapCashResult;			//等待充值结果的集合
	typedef std::list<SCash*> QueryContainer;//用list是因为要每帧调用,采用先到先做的原则
	typedef QueryContainer::iterator   ItrQueryContainer;	
	QueryContainer m_CashChecked;			//确认完毕的订单,等待充值操作

	typedef map<string,SConsumeScore*> mapScore;
	mapScore m_mapScore;					//接收到,但是未处理的订单
	mapScore m_mapScoreResult;			//等待充值结果的集合
	typedef std::list<SConsumeScore*> SocreQueryContainer;//用list是因为要每帧调用,采用先到先做的原则
	typedef SocreQueryContainer::iterator   ItrSocreQueryContainer;	
	SocreQueryContainer m_ScoreChecked;			//确认完毕的订单,等待充值操作
};

#define theBillingManager CBillingManager::Instance()

#endif
