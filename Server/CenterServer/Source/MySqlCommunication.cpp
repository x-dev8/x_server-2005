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
	// ���������߳� һ���߳���ԭ������sql
	bool bResult = MySqlWorkThread::InitMysqlLib();
	if ( !bResult  )
	{ return ER_Failed;}

	// ��ͨ��Ϸ�߼� �������߳�
	_pNormalLogicThread = new NormalLogicWorkThread( this );
	if ( _pNormalLogicThread == NULL )
	{ return ER_NewNormalFail; }

	_pNormalLogicThread->Init( roleDbName, host, port, user, password, ECD_NormalLogicWorkThread );
	_pNormalLogicThread->CreateThread( WorkThreadMain, _pNormalLogicThread );

	// ��ֵ�߼� �������߳�
	//_pBillingLogicThread = new BillingLogicWorkThread( this );
	//if ( _pBillingLogicThread == NULL )
	//{ return ER_NewNormalFail; }

	//_pBillingLogicThread->Init( billingDbName, hostBL, portBL, userBL, passwordBL, ECD_BillingLogicWorkThread );
	//_pBillingLogicThread->CreateThread( WorkThreadMain, _pBillingLogicThread );

	// Platform�߼� �������߳�---�����������￴����...
	_pPlatformLogicThread = new PlatformRPCLogicWorkThread( this );
	if ( _pPlatformLogicThread == NULL )
	{ return ER_NewNormalFail; }

	_pPlatformLogicThread->Init( platformDbName, hostPL, portPL, userPL, passwordPL, ECD_PlatformLogicWorkThread );
	_pPlatformLogicThread->CreateThread( WorkThreadMain, _pPlatformLogicThread );

	// �ж��Ƿ��п�������---��Ч�ķ������߼�
	//if ( theConfig.bOpenAntiAddiction )
	//{ // Platform�߼� �������߳�
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
		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "[�ѷ����ڴ�ռ�������ʼ]");
		uint32 nAllMemory = 0;
		for (map<const char*, ALLOCMEMORYINFO>::iterator itr = GetAllocInfo().begin(); itr != GetAllocInfo().end(); ++itr)
		{
			nAllMemory += itr->second.nAllUseMemory;
			LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "%-60s ռ���ڴ� [%-15d] �ֽ�, Ŀǰδ�ͷŹ����� [%-10d] ��, ��ʷ����[%-10d]��", itr->first!=NULL?itr->first:"δ������;", itr->second.nAllUseMemory, itr->second.nExistCount, itr->second.nAllocCount );
		}
		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "ȫ�������ڴ�[%d]Byte [%d]MByte", nAllMemory, nAllMemory/(1024*1024) );
		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "[�ѷ����ڴ�ռ�������ֹ]\n" );
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
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "�޴���ϢMessageId[%d] ��Ӧ��SqlMessage", pMsg->GetType() ); 
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
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "�޴���ϢMessageId[%d] ��Ӧ��SqlMessage", pMsg->GetType()); 
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
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "�޴���ϢMessageId[%d] ��Ӧ��SqlMessage", pMsg->GetType()  ); 
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
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "�޴���ϢMessageId[%d] ��Ӧ��SqlMessage", pMsg->GetType() ); 
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
	// ��������
	DbMesageContainer tempDbReqMessages;
	{
		CSALocker _lock(_dbReqMessageLock);
		tempDbReqMessages = _dbReqMessages;
		_dbReqMessages.clear();
	}

	// �������������߳�
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
	// ������
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
		//CenterServer����ָ��,�����Ĳ�������ߴ���        
		if( pDbMessage->nClientId == 0 )
		{ ParseMysqlAck( pDbMessage ); }
		//��Ҫ���ͳ�ȥ����Ϣ
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

// ����Mysql���ݷ���
void MySqlCommunication::ParseMysqlAck( BaseSqlMessage *pAckMsg )
{
	switch(pAckMsg->type)
	{
	case CS2GS_MAILLISTACK: // gs �������� center ֱ�Ӵ������ø�gs
		{ 
			SqlMessageCS2GSMailListAck* pDetailSqlMesage = (SqlMessageCS2GSMailListAck*)pAckMsg;
			CS2GSMailListAck* pMessage = &(pDetailSqlMesage->msg);
			theMailSystemManager.OnCS2GSMailListAck( pMessage );
		}
		break;
	case CS2GS_QUERYMAILCANSENDACK:// �ʼ���ѯ
		{
			SqlMessageCS2GSQueryMailCanSendAck* pDetailSqlMesage = (SqlMessageCS2GSQueryMailCanSendAck*)pAckMsg;
			CS2GSQueryMailCanSendAck* pMessage = &(pDetailSqlMesage->msg);
			theMailSystemManager.OnCS2GSQueryMailCanSendAck( pMessage );
		}
		break;

	case CS2GS_SENDMAILACK:	//�ʼ����ͽ���
		{
			SqlMessageCS2GSSendMailAck* pDetailSqlMesage = (SqlMessageCS2GSSendMailAck*)pAckMsg;
			CS2GSSendMailAck* pMessage = &(pDetailSqlMesage->msg);
			theMailSystemManager.OnCS2GSSendMailAck( pMessage );
		}
		break;
	case CS2GS_OPMAILACK://�����ʼ��Ļظ�
		{
			SqlMessageCS2GSOpMailAck* pDetailSqlMesage = (SqlMessageCS2GSOpMailAck*)pAckMsg;
			CS2GSOpMailAck* pMessage = &(pDetailSqlMesage->msg);
			theMailSystemManager.OnCS2GSOpMailAck( pMessage );
		}
		break;
	case DB2CS_REQUESTCOUNTRYDATAACK:
		{
			DB2CSRequestCountryDataAck *pCountryDataAck = static_cast< DB2CSRequestCountryDataAck* >( pAckMsg->GetMessageAddress() );
			//����ÿ�����ҵ�����
			for(int i =CountryDefine::Country_Init;i<CountryDefine::Country_Max;++i)
			{
				CenterCountry* pCenterCountry = theCenterCountryManager.GetCountry(i);
				if(!pCenterCountry) continue;
				pCenterCountry->SetCountryPlayerSum(pCountryDataAck->PlayerSum[i]);
			}
			theCenterCountryManager.InitCountry( pCountryDataAck->xData );
			//�������ʵ�� ���ҵ�ǰʵ�������ݿ��ȡ���ܲ�׼ȷ
			theCenterCountryManager.HandleAllCountryStrength(false);
		}
		break;
		//xuda 
		/*case DB2CS_REQUESTCOUNTRYINFOACK:
		{
		DB2CSRequestCountryInfoAck* pMsg = static_cast< DB2CSRequestCountryInfoAck* >( pAckMsg->GetMessageAddress() );
		//���ع�����Ϣ
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
		//���յ�ͨ�������ݿ������
		DBS2CSRequestWantedDataAck * pAck = static_cast< DBS2CSRequestWantedDataAck* >( pAckMsg->GetMessageAddress() );
		//���������õ����������
		for(int i =0;i<pAck->Sum;++i)
		{
		theCenterWantedManager.LoadWanted(pAck->List[i]);
		}
		//��Ϻ� �������ü������
		if(pAck->IsEnd)
		{
		theCenterWantedManager.SetLoadSuccess(true);
		theCenterWantedManager.SetNewWantedID();//0�������µ�ͨ����˳��ID
		}
		}
		break;*/
	case DB2CS_REQUESTCOUNTRYOFFICECK:
		{
			//����ָ����Ա���������
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
				//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "���ع�ϵ��Ϣ���!");

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
				//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "���ذ�����Ϣ���!");

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
				//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "���ؼ�����Ϣ���!");

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
				//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "���ؼ����ʺ��б����!" );
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
				//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "���ؼ��۽𶧽�Ǯ�б����!" );
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
				//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "���ؼ��۽𶧽�Ǯ��ʷ��¼���!" );
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
				//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "������Ʒ������ֵ��Ϣ���!" );
			}
		}
		break;
	case DB2CS_LOADSYSTEMVARACK:    // ����ϵͳ��������
		{
			DB2CSLoadSystemVarAck* pAck = static_cast<DB2CSLoadSystemVarAck*>(pAckMsg->GetMessageAddress());
			theCenterSysVarManager.AddServerSysVar(&pAck->xSystemVar);
			//theCenterSysVarManager.SendSysVarToGameServer(pAck->xSystemVar.GetServerId());
		}
		break;
	case DB2CS_LOADSYSVARSUCCESS:   // ���سɹ�
		{
			theCenterSysVarManager.SetLoadSuccess( true );
			theCenterSysVarManager.StopLoadTimer();
			//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "����ϵͳ����������Ϣ���!");
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
			//��ȡ���ݿ����ݵķ��ز���
			theCenterGlobalDBManager.LoadGlobalDB(pAck->info);
			theCenterGlobalDBManager.SetLoadSuccess(true);
		}
		break;
	case DB2CS_REQUESTQUESTENTRUSTDATAACK://����ί��
		{
			DBS2CSRequestQuestEntrustDataAck * pAck = static_cast< DBS2CSRequestQuestEntrustDataAck* >( pAckMsg->GetMessageAddress() );
			for(int i =0;i<pAck->Sum;++i)
			{
				theCenterQuestEntrustManager.LoadQuestEntrust(pAck->List[i]);
			}
			//��Ϻ� �������ü������
			if(pAck->IsEnd)
			{
				theCenterQuestEntrustManager.SetLoadSuccess(true);
				theCenterQuestEntrustManager.SetNewQuestEntrustID();
				//theCenterQuestEntrustManager.SendQuestEntrustData(-1);
			}
		}
		break;
	case DB2CS_LOADCAMPBATTLEDATA: // ս������
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
				//theCenterCampBattleDataManager.SendDataToServer(-1);//���еķ�����
			}
		}
		break;
	default:
		break;
	}
}
