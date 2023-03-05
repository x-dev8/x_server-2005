#include "MySqlCommunication.h"
#include "RunStatusDefine.h"
//#include "NetApi.h"
#include "NormalLogicWorkThread.h"
#include "BillingLogicWorkThread.h"
#include "PlatformRPCLogicWorkThread.h"
#include "GameTime.h"
#include "CenterServer.h"
#include "MailManagerMain.h"
#include "CountryManager.h"
#include "RelationManager.h"
#include "GuildManager.h"
#include "ConsignmentManager.h"
#include "GameServerManager.h"
#include "CenterItemDropManager.h"
#include "CenterSystemVarManager.h"
#include "FamilyManager.h"
#include "CenterFamily.h"
#include "Config.h"
#include "LevelLimitCenterManager.h"
#include "GlobalDBManager.h"
//xuda #include "WantedManager.h"
#include "QuestEntrust.h"
#include "GameBattleDataManager.h"
void WorkThreadMain( void* pVoid )
{
	MySqlWorkThread* pThread = (MySqlWorkThread*)pVoid;

	pThread->Update();

	static const int nSleepTime = 1;
	/*NetApi::*/Sleep( nSleepTime );
}

MySqlCommunication& GetMySqlCommunication()
{
	static MySqlCommunication instance;
	return instance;
}

MySqlCommunication::MySqlCommunication()
{
	_pNormalLogicThread      = NULL;
	//_pBillingLogicThread     = NULL;
	_pPlatformLogicThread    = NULL;
	//_pPlatformRPCLogicThread = NULL;
	bMemoryInfo = false;
}

MySqlCommunication::~MySqlCommunication()
{
	SAVE_DELETE_POINTER( _pNormalLogicThread      );
	//SAVE_DELETE_POINTER( _pBillingLogicThread     );
	SAVE_DELETE_POINTER( _pPlatformLogicThread    );
	//SAVE_DELETE_POINTER( _pPlatformRPCLogicThread );
}

uint32 MySqlCommunication::Init( const std::string& roleDbName  , const std::string& host  , uint16 port  , const std::string& user  , const std::string& password  , // GameDB
								const std::string& platformDbName, const std::string& hostPL, uint16 portPL, const std::string& userPL, const std::string& passwordPL  // PlatformDB
								)
{
	// 创建两个线程 一个线程做原来所有sql
	bool bResult = MySqlWorkThread::InitMysqlLib();
	if ( !bResult  )
	{ return ER_Failed;}

	// 普通游戏逻辑 处理工作线程
	_pNormalLogicThread = new NormalLogicWorkThread( this );
	if ( _pNormalLogicThread == NULL )
	{ return ER_NewNormalFail; }

	_pNormalLogicThread->Init( roleDbName, host, port, user, password, ECD_NormalLogicWorkThread );
	_pNormalLogicThread->CreateThread( WorkThreadMain, _pNormalLogicThread );

	// 充值逻辑 处理工作线程
	//_pBillingLogicThread = new BillingLogicWorkThread( this );
	//if ( _pBillingLogicThread == NULL )
	//{ return ER_NewNormalFail; }

	//_pBillingLogicThread->Init( billingDbName, hostBL, portBL, userBL, passwordBL, ECD_BillingLogicWorkThread );
	//_pBillingLogicThread->CreateThread( WorkThreadMain, _pBillingLogicThread );

	// Platform逻辑 处理工作线程---防沉迷在这里看这里...
	_pPlatformLogicThread = new PlatformRPCLogicWorkThread( this );
	if ( _pPlatformLogicThread == NULL )
	{ return ER_NewNormalFail; }

	_pPlatformLogicThread->Init( platformDbName, hostPL, portPL, userPL, passwordPL, ECD_PlatformLogicWorkThread );
	_pPlatformLogicThread->CreateThread( WorkThreadMain, _pPlatformLogicThread );

	// 判断是否有开防沉迷---无效的防沉迷逻辑
	//if ( theConfig.bOpenAntiAddiction )
	//{ // Platform逻辑 处理工作线程
	//    _pPlatformRPCLogicThread = new PlatformRPCLogicWorkThread( this );
	//    if ( _pPlatformRPCLogicThread == NULL )
	//    { return ER_NewNormalFail; }
	//    _pPlatformRPCLogicThread->Init( strPlatformRPCDbName, hostPLR, portPLR, userPLR, passwordPLR, ECD_PlatformRPCLogicWorkThread );
	//    _pPlatformRPCLogicThread->CreateThread( WorkThreadMain, _pPlatformRPCLogicThread );
	//}
	return ER_Success;
}

void MySqlCommunication::Update()
{
	UpdateForRequest();

	UpdateForAcknowledge();

	CheckExitCondition();

	static uint32 lastPrintMemoryTime = HQ_TimeGetTime();
	if ( bMemoryInfo || GameTime::IsPassCurrentTime( lastPrintMemoryTime, ONE_MIN * 10 ))
	{
		CSALocker locker(GetAutoIntLock());
		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "[堆分配内存占用输出起始]");
		uint32 nAllMemory = 0;
		for (map<const char*, ALLOCMEMORYINFO>::iterator itr = GetAllocInfo().begin(); itr != GetAllocInfo().end(); ++itr)
		{
			nAllMemory += itr->second.nAllUseMemory;
			LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "%-60s 占用内存 [%-15d] 字节, 目前未释放共分配 [%-10d] 次, 历史申请[%-10d]次", itr->first!=NULL?itr->first:"未定义用途", itr->second.nAllUseMemory, itr->second.nExistCount, itr->second.nAllocCount );
		}
		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "全部分配内存[%d]Byte [%d]MByte", nAllMemory, nAllMemory/(1024*1024) );
		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "[堆分配内存占用输出终止]\n" );
		bMemoryInfo = false;
		lastPrintMemoryTime = HQ_TimeGetTime();
	}
}

void MySqlCommunication::ShutDown()
{
	if ( _pNormalLogicThread )
	{ _pNormalLogicThread->StopThreadAndWaitDead(); }

	Sleep( 1000 );
}


uint32 MySqlCommunication::PushReqMessage( Msg* pMsg, uint32 nClientId )
{
	BaseSqlMessage* pBaseSqlMessage = NULL;

	try
	{
		pBaseSqlMessage = theSqlMessageManager.GetSqlMessageByDbMsg( pMsg );
	}
	catch ( std::exception& e)
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "PushReqMessage->GetSqlMessageByDbMsg Memory Not Enough(%s)", e.what());
		return ER_Failed;
	}

	if ( pBaseSqlMessage == NULL )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "无此消息MessageId[%d] 对应的SqlMessage", pMsg->GetType() ); 
		return ER_Failed;
	}

	pBaseSqlMessage->nClientId = nClientId;
	pBaseSqlMessage->type      = pMsg->GetType();
	pBaseSqlMessage->time      = HQ_TimeGetTime();
	memcpy( pBaseSqlMessage->GetMessageAddress(), pMsg, pBaseSqlMessage->GetMessageSize());

	CSALocker _lock(_dbReqMessageLock);
	_dbReqMessages.push_back( pBaseSqlMessage );

	return ER_Success;
}

uint32 MySqlCommunication::PushAckMessage( Msg* pMsg, uint32 nClientId )
{
	BaseSqlMessage* pBaseSqlMessage = NULL;

	try
	{
		pBaseSqlMessage = theSqlMessageManager.GetSqlMessageByDbMsg( pMsg );
	}
	catch ( std::exception& e )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "PushReqMessage->GetSqlMessageByDbMsg Memory Not Enough(%s)", e.what());
		return ER_Failed;
	} 

	if ( pBaseSqlMessage == NULL )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "无此消息MessageId[%d] 对应的SqlMessage", pMsg->GetType()); 
		return ER_Failed;
	}

	pBaseSqlMessage->nClientId = nClientId;
	pBaseSqlMessage->type      = pMsg->GetType();
	pBaseSqlMessage->time      = HQ_TimeGetTime();
	memcpy( pBaseSqlMessage->GetMessageAddress(), pMsg, pBaseSqlMessage->GetMessageSize());

	{
		CSALocker _lock(_dbAckMessageLock);
		_dbAckMessages.push_back( pBaseSqlMessage );
	}

	return ER_Success;
}

uint32 MySqlCommunication::Push3PartyReqMessage( Msg* pMsg, uint32 nClientId )
{
	BaseSqlMessage* pBaseSqlMessage = NULL;
	try
	{
		pBaseSqlMessage = theSqlMessageManager.Get3PartySqlMessageByDbMsg( pMsg );
	}
	catch ( std::exception& e)
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "PushReqMessage->GetSqlMessageByDbMsg Memory Not Enough(%s)", e.what());
		return FALSE;
	}

	if ( pBaseSqlMessage == NULL )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "无此消息MessageId[%d] 对应的SqlMessage", pMsg->GetType()  ); 
		return FALSE;
	}

	pBaseSqlMessage->nClientId = nClientId;
	pBaseSqlMessage->type      = pMsg->GetType() ;
	pBaseSqlMessage->time      = HQ_TimeGetTime();
	memcpy( pBaseSqlMessage->GetMessageAddress(), pMsg, pBaseSqlMessage->GetMessageSize());

	{
		CSALocker _lock(_dbReqMessageLock);
		_dbReqMessages.push_back( pBaseSqlMessage );
	}

	return ER_Success;
}

uint32 MySqlCommunication::Push3PartyAckMessage( Msg* pMsg, uint32 nClientId )
{
	BaseSqlMessage* pBaseSqlMessage = NULL;

	try
	{
		pBaseSqlMessage = theSqlMessageManager.Get3PartySqlMessageByDbMsg( pMsg );
	}
	catch ( std::exception& e )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "PushReqMessage->GetSqlMessageByDbMsg Memory Not Enough(%s)", e.what());
		return FALSE;
	} 

	if ( pBaseSqlMessage == NULL )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "无此消息MessageId[%d] 对应的SqlMessage", pMsg->GetType() ); 
		return FALSE;
	}

	pBaseSqlMessage->nClientId = nClientId;
	pBaseSqlMessage->type      = pMsg->GetType();
	pBaseSqlMessage->time      = HQ_TimeGetTime();
	memcpy( pBaseSqlMessage->GetMessageAddress(), pMsg, pBaseSqlMessage->GetMessageSize());

	{
		CSALocker _lock(_dbAckMessageLock);
		_dbAckMessages.push_back( pBaseSqlMessage );
	}

	return ER_Success;
}

void MySqlCommunication::UpdateForRequest()
{
	// 处理请求
	DbMesageContainer tempDbReqMessages;
	{
		CSALocker _lock(_dbReqMessageLock);
		tempDbReqMessages = _dbReqMessages;
		_dbReqMessages.clear();
	}

	// 丢给各个工作线程
	ItrDbMesageContainer it    = tempDbReqMessages.begin();
	ItrDbMesageContainer itEnd = tempDbReqMessages.end();
	for( ; it!=itEnd ; ++it )
	{
		BaseSqlMessage* pDbMessage = (*it);
		switch ( pDbMessage->type)
		{
		case GS2CS_UPDATEANTIADDICTIONINFOREQ:
			{
				if ( theConfig.bOpenAntiAddiction && _pPlatformLogicThread )
				{ _pPlatformLogicThread->PushMessage( pDbMessage ); }
			}
			break;
			/* case CS2P_ADDPAYACK:
			{
			if ( _pBillingLogicThread )
			{ _pBillingLogicThread->PushMessage( pDbMessage ); }                
			}
			break;*/
			//case 1:
			//    {
			//        if ( _pPlatformLogicThread )
			//        { _pPlatformLogicThread->PushMessage( pDbMessage ); }
			//    }
		default:
			{
				if ( _pNormalLogicThread )
				{ _pNormalLogicThread->PushMessage( pDbMessage );}
			}
			break;
		}
	}
}
void MySqlCommunication::UpdateForAcknowledge()
{
	// 处理结果
	DbMesageContainer tempAckDbMessage;
	{
		CSALocker _lock( _dbAckMessageLock );
		tempAckDbMessage = _dbAckMessages;
		_dbAckMessages.clear();
	}

	ItrDbMesageContainer it    = tempAckDbMessage.begin();
	ItrDbMesageContainer itEnd = tempAckDbMessage.end();
	for( ; it!=itEnd ; ++it )
	{
		BaseSqlMessage* pDbMessage = (*it);    
		if ( pDbMessage == NULL )
		{ continue; }
		//CenterServer加载指令,其他的不放在这边处理        
		if( pDbMessage->nClientId == 0 )
		{ ParseMysqlAck( pDbMessage ); }
		//需要发送出去的消息
		else
		{ theCenterServer.SendMessageToPlatform( pDbMessage->nClientId,(Msg*)pDbMessage->GetMessageAddress() ); }
		theSqlMessageManager.FreeSqlMessage( pDbMessage );
	}
}
void MySqlCommunication::CheckExitCondition()
{
	if ( _pNormalLogicThread && _pNormalLogicThread->IsHaveTask() )
	{ return; }    
}

// 加载Mysql数据返回
void MySqlCommunication::ParseMysqlAck( BaseSqlMessage *pAckMsg )
{
	switch(pAckMsg->type)
	{
	case CS2GS_MAILLISTACK: // gs 主动请求 center 直接从数据拿给gs
		{ 
			SqlMessageCS2GSMailListAck* pDetailSqlMesage = (SqlMessageCS2GSMailListAck*)pAckMsg;
			CS2GSMailListAck* pMessage = &(pDetailSqlMesage->msg);
			theMailSystemManager.OnCS2GSMailListAck( pMessage );
		}
		break;
	case CS2GS_QUERYMAILCANSENDACK:// 邮件查询
		{
			SqlMessageCS2GSQueryMailCanSendAck* pDetailSqlMesage = (SqlMessageCS2GSQueryMailCanSendAck*)pAckMsg;
			CS2GSQueryMailCanSendAck* pMessage = &(pDetailSqlMesage->msg);
			theMailSystemManager.OnCS2GSQueryMailCanSendAck( pMessage );
		}
		break;

	case CS2GS_SENDMAILACK:	//邮件发送结束
		{
			SqlMessageCS2GSSendMailAck* pDetailSqlMesage = (SqlMessageCS2GSSendMailAck*)pAckMsg;
			CS2GSSendMailAck* pMessage = &(pDetailSqlMesage->msg);
			theMailSystemManager.OnCS2GSSendMailAck( pMessage );
		}
		break;
	case CS2GS_OPMAILACK://操作邮件的回复
		{
			SqlMessageCS2GSOpMailAck* pDetailSqlMesage = (SqlMessageCS2GSOpMailAck*)pAckMsg;
			CS2GSOpMailAck* pMessage = &(pDetailSqlMesage->msg);
			theMailSystemManager.OnCS2GSOpMailAck( pMessage );
		}
		break;
	case DB2CS_REQUESTCOUNTRYDATAACK:
		{
			DB2CSRequestCountryDataAck *pCountryDataAck = static_cast< DB2CSRequestCountryDataAck* >( pAckMsg->GetMessageAddress() );
			//设置每个国家的人数
			for(int i =CountryDefine::Country_Init;i<CountryDefine::Country_Max;++i)
			{
				CenterCountry* pCenterCountry = theCenterCountryManager.GetCountry(i);
				if(!pCenterCountry) continue;
				pCenterCountry->SetCountryPlayerSum(pCountryDataAck->PlayerSum[i]);
			}
			theCenterCountryManager.InitCountry( pCountryDataAck->xData );
			//计算国家实力 国家当前实力从数据库读取可能不准确
			theCenterCountryManager.HandleAllCountryStrength(false);
		}
		break;
		//xuda 
		/*case DB2CS_REQUESTCOUNTRYINFOACK:
		{
		DB2CSRequestCountryInfoAck* pMsg = static_cast< DB2CSRequestCountryInfoAck* >( pAckMsg->GetMessageAddress() );
		//加载国家信息
		for(int i =CountryDefine::Country_Init;i<CountryDefine::Country_Max;++i)
		{
		CenterCountry* pCenterCountry = theCenterCountryManager.GetCountry(i);
		if(!pCenterCountry) continue;
		for(int j = 0;j<pMsg->Sum;++j)
		{
		if(pMsg->CountryID[j] != i)
		continue;
		pCenterCountry->SetCountryInfo(pMsg->Info[j],pMsg->Time[j],pMsg->values[j]);
		}
		}
		}
		break;
		case DB2CS_REQUESTWANTEDDATAACK:
		{
		//接收到通缉令数据库的数据
		DBS2CSRequestWantedDataAck * pAck = static_cast< DBS2CSRequestWantedDataAck* >( pAckMsg->GetMessageAddress() );
		//将数据设置到中央服务器
		for(int i =0;i<pAck->Sum;++i)
		{
		theCenterWantedManager.LoadWanted(pAck->List[i]);
		}
		//完毕后 我们设置加载完毕
		if(pAck->IsEnd)
		{
		theCenterWantedManager.SetLoadSuccess(true);
		theCenterWantedManager.SetNewWantedID();//0设置最新的通缉令顺序ID
		}
		}
		break;*/
	case DB2CS_REQUESTCOUNTRYOFFICECK:
		{
			//设置指定官员的外观数据
			DB2CSRequestCountryOfficeAck *pCountryDataAck = static_cast< DB2CSRequestCountryOfficeAck* >( pAckMsg->GetMessageAddress() );
			CenterCountry* pCenterCountry = theCenterCountryManager.GetCountry(pCountryDataAck->countryID);
			if(!pCenterCountry) return;
			pCenterCountry->ProcessCountryOfficialChange(pCountryDataAck->uchPosition,pCountryDataAck->nPlayerID,pCountryDataAck->szName,pCountryDataAck->sexID
				,pCountryDataAck->faceID,pCountryDataAck->headerID,pCountryDataAck->professionID);			
		}
		break;
	case DB2CS_RELATIONATTRIBUTELIST:
		{
			DB2CSRelationAttributeList *pAttributeList = static_cast< DB2CSRelationAttributeList* >( pAckMsg->GetMessageAddress() );
			theCenterRelationManager.InitRelationsAttribute( pAttributeList->xAttribute, pAttributeList->ustCount );
		}
		break;
	case DB2CS_RELATIONDATALIST:
		{
			DB2CSRelationDataList *pDataList = static_cast< DB2CSRelationDataList* >( pAckMsg->GetMessageAddress() );
			theCenterRelationManager.InitRelationsData( pDataList->xDBRelation, pDataList->ustCount );
			if ( !pDataList->IsFull() )
			{
				//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "加载关系信息完成!");

				theCenterRelationManager.SetLoadSuccess( true );
				//theCenterRelationManager.SendRelationList2Client( RelationDefine::InitID );
			}
		}
		break;
	case DB2CS_QUERYATTRIBUTEACK:
		{
			DB2CSQueryAttributeAck *pDataList = static_cast< DB2CSQueryAttributeAck* >( pAckMsg->GetMessageAddress() );

			theCenterRelationManager.SendQueryAttributeResultToClient( pDataList->nPlayerID, pDataList->nAttributeID, pDataList->ustCount );
		}
		break;
	case DB2CS_GUILDDATALIST:
		{
			DB2CSGuildDataList *pDataList = static_cast< DB2CSGuildDataList* >( pAckMsg->GetMessageAddress() );
			theCenterGuildManager.InitGuild( pDataList->xList, pDataList->ustCount );
		}
		break;
	case DB2CS_GUILDMEMBERLIST:
		{
			DB2CSGuildMemberList *pDataList = static_cast< DB2CSGuildMemberList* >( pAckMsg->GetMessageAddress() );
			theCenterGuildManager.InitGuildMember( pDataList->xList, pDataList->ustCount );
			if ( !pDataList->IsFull() )
			{
				//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "加载帮派信息完成!");

				theCenterGuildManager.SetLoadSuccess( true );
				//theCenterGuildManager.SendGuildListToClient( RelationDefine::InitID );
			}
		}
		break;
	case DB2CS_FAMILYDATALIST:
		{
			DB2CSFamilyDataList *pDataList = static_cast< DB2CSFamilyDataList* >( pAckMsg->GetMessageAddress() );
			theCenterFamilyManager.InitFamily( pDataList->infoList, pDataList->nCount );
		}
		break;
	case DB2CS_FAMILYMEMBERLIST:
		{
			DB2CSFamilyMemberList *pDataList = static_cast< DB2CSFamilyMemberList* >( pAckMsg->GetMessageAddress() );
			theCenterFamilyManager.InitFamilyMember( pDataList->memberList, pDataList->nCount );
			if ( pDataList->bTheLastPack )
			{
				//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "加载家族信息完成!");

				theCenterFamilyManager.SetLoadSuccess( true );
				//theCenterFamilyManager.SendAllFamiliesToClient( RelationDefine::InitID );
			}
		}
		break;
	case DB2CS_OPERATEMONEYACK:
		{
			DB2CSOperateMoneyAck* pAck = static_cast< DB2CSOperateMoneyAck* >( pAckMsg->GetMessageAddress() ); 
			theConsignmentManager.ProcessDBAccountOperate( pAck->xAccount, pAck->uchOperate, pAck->nRMBMoney, pAck->nGameMoney );
		}
		break;
	case DB2CS_CONSIGNMENTMONEYOPERATEACK:
		{
			DB2CSConsignmentmoneyOperateAck* pAck = static_cast< DB2CSConsignmentmoneyOperateAck* >( pAckMsg->GetMessageAddress() ); 
			theConsignmentManager.ProcessDBConsignmentmoneyOperate( pAck->xOperaterAccount, pAck->xSellerAccount, pAck->nConsignmentID, pAck->uchEndStatus, pAck->n64EndTime, pAck->xNewHistroy );
		}
		break;
	case DB2CS_CONSIGNMENTACCOUNTLIST:
		{
			DB2CSLoadConsignmentAccount* pAck = static_cast< DB2CSLoadConsignmentAccount* >( pAckMsg->GetMessageAddress() ); 
			theConsignmentManager.InitConsignmentAccount( pAck->xAccount, pAck->nCount );
			if ( !pAck->IsFull() )
			{
				theConsignmentManager.SetLoadConsignmentAccount( true );
				theConsignmentManager.StopLoadTimer();
				//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "加载寄售帐号列表完成!" );
			}
		}
		break;
	case DB2CS_CONSIGNMENTMONEYLIST:
		{
			DB2CSLoadConsignmentMoneyList* pAck = static_cast< DB2CSLoadConsignmentMoneyList* >( pAckMsg->GetMessageAddress() ); 
			theConsignmentManager.InitConsignmentMoneyList( pAck->xList, pAck->nCount );
			if ( !pAck->IsFull() )
			{
				theConsignmentManager.SetLoadConsignmentMoneyList( true );
				//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "加载寄售金锭金钱列表完成!" );
			}
		}
		break;
	case DB2CS_CONSIGNMENTHISTROYLIST:
		{
			DB2CSLoadConsignmentHistroy* pAck = static_cast< DB2CSLoadConsignmentHistroy* >( pAckMsg->GetMessageAddress() ); 
			theConsignmentManager.InitConsignmentHistoryList( pAck->xList, pAck->nCount );
			if ( !pAck->IsFull() )
			{
				theConsignmentManager.SetLoadConsignmentMoneyHistroy( true );
				theConsignmentManager.SetLoadSuccess( true );
				//theGameServerManager.SendLoadResourceSuccessMessage( RunStatusDefine::LoadConsignmentSuccess );
				//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "加载寄售金锭金钱历史记录完成!" );
			}
		}
		break;
	case DB2CS_ITEMDROPCONTROL:
		{
			DB2CSItemDropControl* pAck = static_cast< DB2CSItemDropControl* >( pAckMsg->GetMessageAddress() ); 

			for ( int i = 0; i < pAck->nCount; ++i )
			{
				theCenterItemDropManager.AddItemDropControl( pAck->xDropInfo[i].nItemID, pAck->xDropInfo[i].xControl.dwControlCount, pAck->xDropInfo[i].xControl.dwDropCount ); 
			}

			if ( !pAck->IsFull() )
			{
				theCenterItemDropManager.SetLoadSuccess( true );
				theCenterItemDropManager.StopLoadTimer();
				//theCenterItemDropManager.SendDropControlToGameServer();
				//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "加载物品掉落阈值信息完成!" );
			}
		}
		break;
	case DB2CS_LOADSYSTEMVARACK:    // 加载系统变量反馈
		{
			DB2CSLoadSystemVarAck* pAck = static_cast<DB2CSLoadSystemVarAck*>(pAckMsg->GetMessageAddress());
			theCenterSysVarManager.AddServerSysVar(&pAck->xSystemVar);
			//theCenterSysVarManager.SendSysVarToGameServer(pAck->xSystemVar.GetServerId());
		}
		break;
	case DB2CS_LOADSYSVARSUCCESS:   // 加载成功
		{
			theCenterSysVarManager.SetLoadSuccess( true );
			theCenterSysVarManager.StopLoadTimer();
			//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "加载系统计数变量信息完成!");
		}
		break;
	case CS2GS_UPDATEANTIADDICTIONINFOACK:
		{
			CS2GSUpdateAntiaddictionInfoAck* pAck = static_cast< CS2GSUpdateAntiaddictionInfoAck* >( pAckMsg->GetMessageAddress() ); 
			theGameServerManager.SendMsgToSingleByAccountId( pAck, pAck->nAccountId );
		}
		break;
	case MSG_LOADDATA_ACK:
		{
			MsgAckMySQLData* pAck = static_cast< MsgAckMySQLData* >( pAckMsg->GetMessageAddress() );
			if (pAck)
			{
				theLevelLimitCenterManager.ProceeMySqlData(pAck);
			}
		}
		break;
	case CS2GS_LOADGLOBALDBACK:
		{
			GS2CSLoadGlobalDBAck* pAck = static_cast< GS2CSLoadGlobalDBAck* >( pAckMsg->GetMessageAddress());
			//读取数据库数据的返回操作
			theCenterGlobalDBManager.LoadGlobalDB(pAck->info);
			theCenterGlobalDBManager.SetLoadSuccess(true);
		}
		break;
	case DB2CS_REQUESTQUESTENTRUSTDATAACK://任务委托
		{
			DBS2CSRequestQuestEntrustDataAck * pAck = static_cast< DBS2CSRequestQuestEntrustDataAck* >( pAckMsg->GetMessageAddress() );
			for(int i =0;i<pAck->Sum;++i)
			{
				theCenterQuestEntrustManager.LoadQuestEntrust(pAck->List[i]);
			}
			//完毕后 我们设置加载完毕
			if(pAck->IsEnd)
			{
				theCenterQuestEntrustManager.SetLoadSuccess(true);
				theCenterQuestEntrustManager.SetNewQuestEntrustID();
				//theCenterQuestEntrustManager.SendQuestEntrustData(-1);
			}
		}
		break;
	case DB2CS_LOADCAMPBATTLEDATA: // 战场数据
		{
			DB2CSLoadCampBattleData * pAck = static_cast< DB2CSLoadCampBattleData* >( pAckMsg->GetMessageAddress() );
			for(int i =0;i<pAck->Sum;++i)
			{
				theCenterCampBattleDataManager.InsertGuildBattleData(pAck->info[i]);
			}
			if(pAck->IsEnd)
			{
				theCenterCampBattleDataManager.SetLoadSecc();
				theCenterCampBattleDataManager.SetNewID();
				//theCenterCampBattleDataManager.SendDataToServer(-1);//已有的发送下
			}
		}
		break;
	default:
		break;
	}
}
