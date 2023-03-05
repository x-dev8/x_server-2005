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

#define GiveUp_Time 1000*60 //�׵�,1MIN
#define GiveUp_Degree 3     //����ȷ��û������׵�



class CBillingManager
{
public:
	enum ecs
	{
		ecs_tryconnect = 0,
		ecs_connected,
		ecs_max,
	};

	//��ֵ��Ϣ
#pragma pack ( push, 1 )
	struct SCash:INHERIT_POOL(SCash)
	{
		char			sn[17]; //Ψһ����
		unsigned long	account_id;//�ʺ�ID
		int             money;     //�����Ǯ
		unsigned long   check_time; //�������̫�������׵�����
		char		    check_degree; //ȷ�ϴ���
		SCash()
		{
			memset(this,0,sizeof(SCash));
		}
	};

	struct SConsumeScore:INHERIT_POOL(SConsumeScore)
	{
		char			sn[17]; //Ψһ����
		unsigned long	account_id;//�ʺ�ID
		int             money;     //�����Ǯ
		unsigned long   check_time; //�������̫�������׵�����
		char		    check_degree; //ȷ�ϴ���
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
	void OnMsgAuthConnect	(Msg* pMsg,char servertype);//server type 0:Ԫ��,1:����
	void OnMsgCash			(Msg* pMsg);
	void OnMsgChenckSnResult(Msg* pMsg);

	void OnMsgConsumeScore	(Msg* pMsg);
	void OnMsgChenckConsumeScoreSnResult(Msg* pMsg);
	//////////////////////////////////////////////

	void ProcessUnCheckCash();//ˢ����δȷ�϶���
	void ProcessResultCash(); //ˢ�µȴ���ֵ����Ķ���
	void ProcessCheckedCash();//ÿ֡�����Ѿ���ӵĳ�ֵ����
	//void AckCashResult();	  //���س�ֵ���
	void ProcessUnCheckConsumeScore();//ˢ����δȷ�϶���
	void ProcessResultConsumeScore(); //ˢ�µȴ���ֵ����Ķ���
	void ProcessCheckedConsumeScore();//ÿ֡�����Ѿ���ӵĳ�ֵ����

	void OnDBMsgCashResult(DB2DBCashResult* pMess);
	void OnDBMsgConsumeSocreResult(DB2DBConsumeScoreResult* pMess);

	bool IsCanAddCashInfo(const char* sn);
	bool IsCanAddScoreInfo(const char* sn);

	void PrintfInfo(const char* szFormat, ...);
	
private:
	Socketer*		 m_pConnector;
	char			 connect_state;
	unsigned long    ping_time;        //����ping��ʱ��
	unsigned long    check_ping_time;  //���һ�μ��PINGͨ����ʱ��
	bool             _service;         //�����Ƿ���,��Ҫ��֤������

	Socketer*		 m_pScoreConnector;
	char			 Scoreconnect_state;
	unsigned long    Scoreping_time;        //����ping��ʱ��
	unsigned long    Scorecheck_ping_time;  //���һ�μ��PINGͨ����ʱ��
	bool             _Scoreservice;         //�����Ƿ���,��Ҫ��֤������

	typedef map<string,SCash*> mapCash;
	mapCash m_mapCash;					//���յ�,����δ����Ķ���
	mapCash m_mapCashResult;			//�ȴ���ֵ����ļ���
	typedef std::list<SCash*> QueryContainer;//��list����ΪҪÿ֡����,�����ȵ�������ԭ��
	typedef QueryContainer::iterator   ItrQueryContainer;	
	QueryContainer m_CashChecked;			//ȷ����ϵĶ���,�ȴ���ֵ����

	typedef map<string,SConsumeScore*> mapScore;
	mapScore m_mapScore;					//���յ�,����δ����Ķ���
	mapScore m_mapScoreResult;			//�ȴ���ֵ����ļ���
	typedef std::list<SConsumeScore*> SocreQueryContainer;//��list����ΪҪÿ֡����,�����ȵ�������ԭ��
	typedef SocreQueryContainer::iterator   ItrSocreQueryContainer;	
	SocreQueryContainer m_ScoreChecked;			//ȷ����ϵĶ���,�ȴ���ֵ����
};

#define theBillingManager CBillingManager::Instance()

#endif
