#include "BillingManager.h"
#include "DatabaseServerApp.h"
#include "md5.h"
#include "MySqlCommunication.h"

CBillingManager::CBillingManager(void)
{
	m_pConnector = NULL;
	connect_state = ecs_tryconnect;

	ping_time = 0;
	check_ping_time = 0;
	_service = false;

	m_mapCash.clear();
	m_mapCashResult.clear();
	m_CashChecked.clear();
	m_mapScore.clear();
	m_mapScoreResult.clear();
	m_ScoreChecked.clear();

	m_pScoreConnector = NULL;
	Scoreconnect_state = ecs_tryconnect;

	Scoreping_time = 0;
	Scorecheck_ping_time = 0;
	_Scoreservice = false;
}

CBillingManager::~CBillingManager(void)
{
	if (m_pConnector)
	{
		Socketer_release(m_pConnector);
		m_pConnector = NULL;
	}

	if (m_pScoreConnector)
	{
		Socketer_release(m_pScoreConnector);
		m_pScoreConnector = NULL;
	}

	mapCash::iterator itr = m_mapCash.begin();
	while(itr != m_mapCash.end())
	{
		if (itr->second)
		{
			delete itr->second;
		}
		itr++;
	}
	m_mapCash.clear();

	mapCash::iterator itr1 = m_mapCashResult.begin();
	while(itr != m_mapCashResult.end())
	{
		if (itr->second)
		{
			delete itr->second;
		}
		itr++;
	}
	m_mapCashResult.clear();

	mapScore::iterator itr2 = m_mapScore.begin();
	while(itr2 != m_mapScore.end())
	{
		if (itr2->second)
		{
			delete itr2->second;
		}
		itr2++;
	}
	m_mapScore.clear();

	mapScore::iterator itr3 = m_mapScoreResult.begin();
	while(itr3 != m_mapScoreResult.end())
	{
		if (itr3->second)
		{
			delete itr3->second;
		}
		itr3++;
	}
	m_mapScoreResult.clear();

	SConsumeScore* pScore = NULL;
	while(!m_ScoreChecked.empty())
	{		
		pScore = m_ScoreChecked.front();
		m_ScoreChecked.pop_front();
	}

	SCash* pCash = NULL;
	while(!m_CashChecked.empty())
	{		
		pCash = m_CashChecked.front();
		m_CashChecked.pop_front();
	}
}

string CBillingManager::GetMsgMd5Sign(void* _input0,int _length0,void* _input1,int _length1)
{
	char content_buff[1024];
	memset(content_buff,0,1024);
	memcpy(content_buff,_input0,_length0);
	memcpy(content_buff+_length0,_input1,_length1);
	MD5 xMD5( content_buff ,_length1+_length0);
	std::string strConent = xMD5.toString();
	return strConent;
}

#define MAX_ProcessNum 100 //每帧处理10个充值请求?不知道够不够,不够修改就好了
void CBillingManager::ProcessCheckedCash()
{
	int num =0;
	SCash* pCash = NULL;
	while(!m_CashChecked.empty())
	{
		num++;
		pCash = m_CashChecked.front();

		//todo:处理订单
		DB2DBCash msg;
		memcpy(msg.sn,pCash->sn,17);
		msg.account_id = pCash->account_id;
		msg.money = pCash->money;
		msg.shServerId = DiskServerId;
		if ( theMysqlCommunication.PushReqMessage( &msg, -1 ) == ER_Success )
		{
			m_mapCashResult.insert(mapCash::value_type(pCash->sn,pCash));
			m_CashChecked.pop_front();
		}
		else
		{//如果最前面的有问题,则return掉,防止死循环,可以做一些其他的操作,比如通知抛单等
			//todo:
			return;
		}

		if(num >= MAX_ProcessNum)
			return;
	}
}

void CBillingManager::ProcessUnCheckCash()
{
	uint32 currtime = HQ_TimeGetTime();
	mapCash::iterator itr = m_mapCash.begin();
	while(itr!= m_mapCash.end())
	{
		SCash* pCash = itr->second;
		if(pCash)
		{
			if(currtime - pCash->check_time >= GiveUp_Time)
			{
				if(pCash->check_degree < GiveUp_Degree)
				{
					MsgBillingSnCheck sncheck;
					memcpy(sncheck.content.sn,pCash->sn,16);
					sncheck.content.account_id = pCash->account_id;
					sncheck.content.money = pCash->money;
					strncpy_s( sncheck.sign,sizeof(sncheck.sign),GetMsgMd5Sign((void*)&(sncheck.content),sizeof(MsgBillingSnCheck::SContent),(void*)theDatabaseServerApp->strKey.c_str(),16).c_str(),sizeof(sncheck.sign)-1);
					SendMsgToBillingServer(&sncheck);

					pCash->check_time = HQ_TimeGetTime();
					pCash->check_degree++;
				}
				else
				{
					MsgBillingCashResult cashresult;
					memcpy(cashresult.content.sn,pCash->sn,16);
					cashresult.content.result = eCashResult_checkerror;
					strncpy_s( cashresult.sign,sizeof(cashresult.sign),GetMsgMd5Sign((void*)&(cashresult.content),sizeof(MsgBillingCashResult::SContent),(void*)theDatabaseServerApp->strKey.c_str(),16).c_str(),sizeof(cashresult.sign)-1);
					SendMsgToBillingServer(&cashresult);
			
					itr = m_mapCash.erase(itr);

					delete pCash;
					continue;
				}
			}			
		}
		else
		{
			itr = m_mapCash.erase(itr);
			continue;
		}
		itr++;
	}
}

void CBillingManager::ProcessResultCash()
{
}

char CBillingManager::TryConnectBillServer()
{
	switch(connect_state)
	{
	case ecs_tryconnect:
		{
			_service = false;
			if (!m_pConnector)
			{
				m_pConnector = Socketer_create();
				if (!m_pConnector)
				{
					break;
				}
			}		

			if(m_pConnector->Connect(theDatabaseServerApp->strBillingServerIp.c_str(),
				theDatabaseServerApp->ustBillingServerPort,
				theDatabaseServerApp->nBindBillingServerPort))
			{
				connect_state = ecs_connected;
				check_ping_time = HQ_TimeGetTime();
				ping_time = check_ping_time;
				//////
				MsgAuthConnect msg;
				memcpy(msg.content.chKey,theDatabaseServerApp->strKey.c_str(),16);
				strncpy_s( msg.sign,sizeof(msg.sign),GetMsgMd5Sign((void*)&(msg.content),sizeof(MsgAuthConnect::SContent),(void*)theDatabaseServerApp->strKey.c_str(),16).c_str(),sizeof(msg.sign)-1);
				SendMsgToBillingServer(&msg);
				////////
				PrintfInfo("conncet to billing server succ,and send auth\n");
			}
		}
		break;
	default:
		break;
	}
	return connect_state;
}

char CBillingManager::TryConnectBillScoreServer()
{
	switch(Scoreconnect_state)
	{
	case ecs_tryconnect:
		{
			_Scoreservice = false;
			if (!m_pScoreConnector)
			{
				m_pScoreConnector = Socketer_create();
				if (!m_pScoreConnector)
				{
					break;
				}
			}		

			if(m_pScoreConnector->Connect(theDatabaseServerApp->strBillingScoreServerIp.c_str(),
				theDatabaseServerApp->ustBillingScoreServerPort,
				theDatabaseServerApp->nBindBillingScoreServerPort))
			{
				Scoreconnect_state = ecs_connected;
				Scoreping_time = HQ_TimeGetTime();
				Scorecheck_ping_time = Scorecheck_ping_time;
				//////
				MsgAuthConnect msg;
				memcpy(msg.content.chKey,theDatabaseServerApp->strKeyScore.c_str(),16);
				strncpy_s( msg.sign,sizeof(msg.sign),GetMsgMd5Sign((void*)&(msg.content),sizeof(MsgAuthConnect::SContent),(void*)theDatabaseServerApp->strKeyScore.c_str(),16).c_str(),sizeof(msg.sign)-1);
				SendMsgToBillingScoreServer(&msg);
				////////
				PrintfInfo("conncet to billingScore server succ,and send auth\n");
			}
		}
		break;
	default:
		break;
	}
	return Scoreconnect_state;
}

void CBillingManager::ReciveBillingMsg()
{
	if (!m_pConnector||m_pConnector->IsClose())
	{
		connect_state = ecs_tryconnect;
		_service = false;
		if (m_pConnector)
		{
			Socketer_release(m_pConnector);
			m_pConnector = NULL;
		}
		PrintfInfo("billing server disconnect\n");
		return;
	}

	if (connect_state == ecs_connected)
	{
		m_pConnector->CheckRecv();
	}
}

void CBillingManager::SendBillingMsg()
{
	if (!m_pConnector||m_pConnector->IsClose())
	{
		connect_state = ecs_tryconnect;
		_service = false;
		if (m_pConnector)
		{
			Socketer_release(m_pConnector);
			m_pConnector = NULL;
		}
		PrintfInfo("billing server disconnect\n");
		return;
	}

	if (connect_state == ecs_connected)
	{
		m_pConnector->CheckSend();
	}
}

void CBillingManager::SendMsgToBillingServer(Msg* pMsg)
{
	if (connect_state != ecs_connected||pMsg == NULL||!m_pConnector||m_pConnector->IsClose())
	{
		return;
	}
	m_pConnector->SendMsg(pMsg);
}

void CBillingManager::SendMsgToBillingScoreServer(Msg* pMsg)
{
	if (Scoreconnect_state != ecs_connected||pMsg == NULL||!m_pScoreConnector||m_pScoreConnector->IsClose())
	{
		return;
	}
	m_pScoreConnector->SendMsg(pMsg);
}

void CBillingManager::ProcessBillingServerMsg()
{
	if(!m_pConnector)
		return;
//#define MAX_MSG 30 //每帧最多处理30个过来的消息
	//Msg* pMsg = NULL;
	//int i = 0;
	GameTimerEx processGameMessageTime;
	processGameMessageTime.StartTimer( HQ_TimeGetTime(), 20 );
	Msg *pMsg = NULL;
	// 时间片到了就退了
	while( !processGameMessageTime.DoneTimer( HQ_TimeGetTime() ) )
	{
		//++i;
		pMsg = m_pConnector->GetMsg();
		if ( pMsg == NULL )
		{ break;  }

		switch(pMsg->GetType())
		{
		case eBillServerMsgDefine_AuthReq:
			OnMsgAuthConnect(pMsg,0);
			break;
		case eBillServerMsgDefine_Cash:
			OnMsgCash(pMsg);
			break;
		case eBillServerMsgDefine_SnCheckReq:
			OnMsgChenckSnResult(pMsg);
			break;
		default:
			break;
		}
		//if (MAX_MSG <= i)
		//	break;
	}
}

void CBillingManager::ProcessBillingScoreServerMsg()
{
	if(!m_pScoreConnector)
		return;
	GameTimerEx processGameMessageTime;
	processGameMessageTime.StartTimer( HQ_TimeGetTime(), 20 );
	Msg *pMsg = NULL;
	// 时间片到了就退了
	while( !processGameMessageTime.DoneTimer( HQ_TimeGetTime() ) )
	{
		//++i;
		pMsg = m_pScoreConnector->GetMsg();
		if ( pMsg == NULL )
		{ break;  }

		switch(pMsg->GetType())
		{
		case eBillServerMsgDefine_AuthReq:
			OnMsgAuthConnect(pMsg,1);
			break;
		case eBillServerMsgDefine_Score:
			OnMsgConsumeScore(pMsg);
			break;
		case eBillServerMsgDefine_ScoreSnCheckReq:
			OnMsgChenckConsumeScoreSnResult(pMsg);
			break;
		default:
			break;
		}
	}
}

void CBillingManager::ReciveBillingScoreMsg()
{
	if (!m_pScoreConnector||m_pScoreConnector->IsClose())
	{
		Scoreconnect_state = ecs_tryconnect;
		_Scoreservice = false;
		if (m_pScoreConnector)
		{
			Socketer_release(m_pScoreConnector);
			m_pScoreConnector = NULL;
		}
		PrintfInfo("billing Score server disconnect\n");
		return;
	}

	if (Scoreconnect_state == ecs_connected)
	{
		m_pScoreConnector->CheckRecv();
	}
}

void CBillingManager::SendBillingScoreMsg()
{
	if (!m_pScoreConnector||m_pScoreConnector->IsClose())
	{
		Scoreconnect_state = ecs_tryconnect;
		_Scoreservice = false;
		if (m_pScoreConnector)
		{
			Socketer_release(m_pScoreConnector);
			m_pScoreConnector = NULL;
		}
		PrintfInfo("billing Score server disconnect\n");
		return;
	}

	if (Scoreconnect_state == ecs_connected)
	{
		m_pScoreConnector->CheckSend();
	}
}

void CBillingManager::Run()
{
	if (theDatabaseServerApp->bOpenBillingService&&TryConnectBillServer() == ecs_connected)
	{
		ReciveBillingMsg();
		ProcessBillingServerMsg();

		ProcessUnCheckCash();
		ProcessCheckedCash();

		SendBillingMsg();		
	}

	if (theDatabaseServerApp->bOpenBillingScoreService&&TryConnectBillScoreServer() == ecs_connected)
	{
		ReciveBillingScoreMsg();
		ProcessBillingScoreServerMsg();

		ProcessUnCheckConsumeScore();
		ProcessCheckedConsumeScore();

		SendBillingScoreMsg();
	}	
}

void CBillingManager::OnMsgAuthConnect(Msg* pMsg,char servertype)
{
	MsgAuthConnectReq* pReq = (MsgAuthConnectReq*)pMsg;
	if (!pReq)
	{
		return;
	}
	switch(servertype)
	{
	case 0:
		_service = atoi(&pReq->content.result);
		PrintfInfo("billing server auth result:%d\n",_service);
		break;
	case 1:
		_Scoreservice = atoi(&pReq->content.result);
		PrintfInfo("billing score server auth result:%d\n",_Scoreservice);
		break;
	default:
		PrintfInfo("Unkown Server type:%d\n",servertype);
		break;
	}
}

void CBillingManager::OnMsgCash(Msg* pMsg)
{
	MsgBillingCash* pCachMsg = (MsgBillingCash*)pMsg;
	if (!pCachMsg)
	{
		return;
	}
	
	if(IsCanAddCashInfo(pCachMsg->content.sn))
	{
		//加入到等待处理表
		SCash* pCash = new SCash;
		if(!pCash)
			return;

		memcpy(pCash->sn,pCachMsg->content.sn,16);
		pCash->account_id = pCachMsg->content.account_id;
		pCash->money = pCachMsg->content.money;
		pCash->check_time = HQ_TimeGetTime();
		pCash->check_degree++;

		m_mapCash.insert(mapCash::value_type(pCash->sn,pCash));

		//发送给billing再次确认订单
		MsgBillingSnCheck sncheck;
		memcpy(sncheck.content.sn,pCash->sn,16);
		sncheck.content.account_id = pCash->account_id;
		sncheck.content.money = pCash->money;
		strncpy_s( sncheck.sign,sizeof(sncheck.sign),GetMsgMd5Sign((void*)&(sncheck.content),sizeof(MsgBillingSnCheck::SContent),(void*)theDatabaseServerApp->strKey.c_str(),16).c_str(),sizeof(sncheck.sign)-1);
		SendMsgToBillingServer(&sncheck);
	}
}

void CBillingManager::OnMsgChenckSnResult(Msg* pMsg)
{
	MsgBillingSnCheckReq* pSnChenckRes = (MsgBillingSnCheckReq*)pMsg;
	if (!pSnChenckRes)
	{
		return;
	}

	SCash* pCash = NULL;
	char chTemp[17];
	memset(chTemp,0,17);
	memcpy(chTemp,pSnChenckRes->content.sn,16);
	mapCash::iterator itr = m_mapCash.find(chTemp);
	if (itr != m_mapCash.end())
	{
		pCash = itr->second;
		if(!pCash)
		{
			return;
		}
	}

	if (pSnChenckRes->content.result)
	{
		pCash->check_time = HQ_TimeGetTime();
		m_CashChecked.push_back(pCash);
	}
	else
	{
		MsgBillingCashResult cashresult;
		memcpy(cashresult.content.sn,pCash->sn,16);
		cashresult.content.result = eCashResult_checkerror;
		strncpy_s( cashresult.sign,sizeof(cashresult.sign),GetMsgMd5Sign((void*)&(cashresult.content),sizeof(MsgBillingCashResult::SContent),(void*)theDatabaseServerApp->strKey.c_str(),16).c_str(),sizeof(cashresult.sign)-1);
		SendMsgToBillingServer(&cashresult);

		delete pCash;
	}
	m_mapCash.erase(itr);
}

void CBillingManager::OnDBMsgCashResult(DB2DBCashResult* pMess)
{
	if(!pMess)
	{
		return;
	}

	mapCash::iterator itr = m_mapCashResult.find(pMess->sn);
	if(itr == m_mapCashResult.end())
	{
		return;
	}
	SCash *pCash = itr->second;
	if(!pCash)
	{
		return;
	}

	MsgBillingCashResult cashresult;
	memcpy(cashresult.content.sn,pMess->sn,16);
	cashresult.content.result = pMess->result;
	strncpy_s( cashresult.sign,sizeof(cashresult.sign),GetMsgMd5Sign((void*)&(cashresult.content),sizeof(MsgBillingCashResult::SContent),(void*)theDatabaseServerApp->strKey.c_str(),16).c_str(),sizeof(cashresult.sign)-1);
	SendMsgToBillingServer(&cashresult);

	m_mapCashResult.erase(itr);

	delete pCash;
}

bool CBillingManager::IsCanAddCashInfo(const char* sn)
{//过来一个充值请求,要判断下是不是已经在处理队列了

	char chTemp[17];
	memset(chTemp,0,17);
	memcpy(chTemp,sn,16);

	//1,是否在等待验证队列
	mapCash::iterator itr = m_mapCash.find(chTemp);
	if(itr != m_mapCash.end())
		return false;
	//2,是否在等待充值结果的集合
	itr = m_mapCashResult.find(chTemp);
	if(itr != m_mapCashResult.end())
		return false;

	//3,确认完毕的订单,等待充值操作
	ItrQueryContainer itrQ = m_CashChecked.begin();
	for(;itrQ != m_CashChecked.end();++itrQ)
	{
		if(strcmp((*itrQ)->sn,sn) == 0)
			return false;
	}
	
	return true;
}

void CBillingManager::PrintfInfo(const char* szFormat, ...)
{
	char szDate[256] = {0};
	char szTime[256] = {0};
	char szBuf[1024] = {0};

	SYSTEMTIME systime;
	GetLocalTime( &systime );

	_snprintf(szDate, sizeof(szDate)-1, "%04d-%02d-%02d", systime.wYear, systime.wMonth, systime.wDay);
	_snprintf(szTime, sizeof(szTime)-1, "%02d:%02d:%02d", systime.wHour, systime.wMinute, systime.wSecond);

	//转换参数
	va_list vl;
	va_start(vl, szFormat);
	int cnt = vsnprintf(szBuf, sizeof(szBuf)-1, szFormat, vl);
	va_end(vl);

	printf("%s %s %s\n",szDate, szTime,szBuf);	

}

bool CBillingManager::IsCanAddScoreInfo(const char* sn)
{
	//过来一个充值请求,要判断下是不是已经在处理队列了
	char chTemp[17];
	memset(chTemp,0,17);
	memcpy(chTemp,sn,16);

	//1,是否在等待验证队列
	mapScore::iterator itr = m_mapScore.find(chTemp);
	if(itr != m_mapScore.end())
		return false;
	//2,是否在等待充值结果的集合
	itr = m_mapScoreResult.find(chTemp);
	if(itr != m_mapScoreResult.end())
		return false;

	//3,确认完毕的订单,等待充值操作
	ItrSocreQueryContainer itrQ = m_ScoreChecked.begin();
	for(;itrQ != m_ScoreChecked.end();++itrQ)
	{
		if(strcmp((*itrQ)->sn,sn) == 0)
			return false;
	}

	return true;
}

void CBillingManager::OnMsgConsumeScore(Msg* pMsg)
{
	MsgBillingScore* pScoreMsg = (MsgBillingScore*)pMsg;
	if (!pScoreMsg)
	{
		return;
	}

	if(IsCanAddScoreInfo(pScoreMsg->content.sn))
	{
		//加入到等待处理表
		SConsumeScore* pScore = new SConsumeScore;
		if(!pScore)
			return;

		memcpy(pScore->sn,pScoreMsg->content.sn,16);
		pScore->account_id = pScoreMsg->content.account_id;
		pScore->money = pScoreMsg->content._value;
		pScore->check_time = HQ_TimeGetTime();
		pScore->check_degree++;

		m_mapScore.insert(mapScore::value_type(pScore->sn,pScore));

		//发送给billing再次确认订单
		MsgBillingScoreSnCheck sncheck;
		memcpy(sncheck.content.sn,pScore->sn,16);
		sncheck.content.account_id = pScore->account_id;
		sncheck.content._value = pScore->money;
		strncpy_s( sncheck.sign,sizeof(sncheck.sign),GetMsgMd5Sign((void*)&(sncheck.content),sizeof(MsgBillingScoreSnCheck::SContent),(void*)theDatabaseServerApp->strKeyScore.c_str(),16).c_str(),sizeof(sncheck.sign)-1);
		SendMsgToBillingScoreServer(&sncheck);
	}
}

void CBillingManager::OnMsgChenckConsumeScoreSnResult(Msg* pMsg)
{
	MsgBillingScoreSnCheckReq* pSnChenckRes = (MsgBillingScoreSnCheckReq*)pMsg;
	if (!pSnChenckRes)
	{
		return;
	}

	SConsumeScore* pScore = NULL;
	char chTemp[17];
	memset(chTemp,0,17);
	memcpy(chTemp,pSnChenckRes->content.sn,16);
	mapScore::iterator itr = m_mapScore.find(chTemp);
	if (itr != m_mapScore.end())
	{
		pScore = itr->second;
		if(!pScore)
		{
			return;
		}
	}

	if (pSnChenckRes->content.result)
	{
		pScore->check_time = HQ_TimeGetTime();
		m_ScoreChecked.push_back(pScore);
	}
	else
	{
		MsgBillingScoreResult scoreresult;
		memcpy(scoreresult.content.sn,pScore->sn,16);
		scoreresult.content.result = eCashResult_checkerror;
		strncpy_s( scoreresult.sign,sizeof(scoreresult.sign),GetMsgMd5Sign((void*)&(scoreresult.content),sizeof(MsgBillingScoreResult::SContent),(void*)theDatabaseServerApp->strKeyScore.c_str(),16).c_str(),sizeof(scoreresult.sign)-1);
		SendMsgToBillingScoreServer(&scoreresult);

		delete pScore;
	}
	m_mapScore.erase(itr);
}

void CBillingManager::ProcessUnCheckConsumeScore()//刷新下未确认订单
{
	uint32 currtime = HQ_TimeGetTime();
	mapScore::iterator itr = m_mapScore.begin();
	while(itr!= m_mapScore.end())
	{
		SConsumeScore* pScore = itr->second;
		if(pScore)
		{
			if(currtime - pScore->check_time >= GiveUp_Time)
			{
				if(pScore->check_degree < GiveUp_Degree)
				{
					MsgBillingScoreSnCheck sncheck;
					memcpy(sncheck.content.sn,pScore->sn,16);
					sncheck.content.account_id = pScore->account_id;
					sncheck.content._value = pScore->money;
					strncpy_s( sncheck.sign,sizeof(sncheck.sign),GetMsgMd5Sign((void*)&(sncheck.content),sizeof(MsgBillingScoreSnCheck::SContent),(void*)theDatabaseServerApp->strKeyScore.c_str(),16).c_str(),sizeof(sncheck.sign)-1);
					SendMsgToBillingScoreServer(&sncheck);

					pScore->check_time = HQ_TimeGetTime();
					pScore->check_degree++;
				}
				else
				{
					MsgBillingScoreResult scoreresult;
					memcpy(scoreresult.content.sn,pScore->sn,16);
					scoreresult.content.result = eCashResult_checkerror;
					strncpy_s( scoreresult.sign,sizeof(scoreresult.sign),GetMsgMd5Sign((void*)&(scoreresult.content),sizeof(MsgBillingScoreResult::SContent),(void*)theDatabaseServerApp->strKeyScore.c_str(),16).c_str(),sizeof(scoreresult.sign)-1);
					SendMsgToBillingScoreServer(&scoreresult);

					itr = m_mapScore.erase(itr);

					delete pScore;
					continue;
				}
			}			
		}
		else
		{
			itr = m_mapScore.erase(itr);
			continue;
		}
		itr++;
	}
}
void CBillingManager::ProcessResultConsumeScore() //刷新等待充值结果的订单
{

}
void CBillingManager::ProcessCheckedConsumeScore()//每帧处理已经添加的充值请求
{
	int num =0;
	SConsumeScore* pScore = NULL;
	while(!m_ScoreChecked.empty())
	{
		num++;
		pScore = m_ScoreChecked.front();

		//todo:处理订单
		DB2DBConsumeScore msg;
		memcpy(msg.sn,pScore->sn,17);
		msg.account_id = pScore->account_id;
		msg.money = pScore->money;
		msg.shServerId = DiskServerId;
		if ( theMysqlCommunication.PushReqMessage( &msg, -1 ) == ER_Success )
		{
			m_mapScoreResult.insert(mapScore::value_type(pScore->sn,pScore));
			m_ScoreChecked.pop_front();
		}
		else
		{//如果最前面的有问题,则return掉,防止死循环,可以做一些其他的操作,比如通知抛单等
			//todo:
			return;
		}

		if(num >= MAX_ProcessNum)
			return;
	}
}

void CBillingManager::OnDBMsgConsumeSocreResult(DB2DBConsumeScoreResult* pMess)
{
	if(!pMess)
	{
		return;
	}

	mapScore::iterator itr = m_mapScoreResult.find(pMess->sn);
	if(itr == m_mapScoreResult.end())
	{
		return;
	}
	SConsumeScore *pScore = itr->second;
	if(!pScore)
	{
		return;
	}

	MsgBillingScoreResult scoreresult;
	memcpy(scoreresult.content.sn,pMess->sn,16);
	scoreresult.content.result = pMess->result;
	strncpy_s( scoreresult.sign,sizeof(scoreresult.sign),GetMsgMd5Sign((void*)&(scoreresult.content),sizeof(MsgBillingScoreResult::SContent),(void*)theDatabaseServerApp->strKeyScore.c_str(),16).c_str(),sizeof(scoreresult.sign)-1);
	SendMsgToBillingScoreServer(&scoreresult);

	m_mapScoreResult.erase(itr);

	delete pScore;
}