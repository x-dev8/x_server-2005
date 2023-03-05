/********************************************************************
	Filename: 	LogFileObjectName.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __LOGFILEOBJECTNAME_H__
#define __LOGFILEOBJECTNAME_H__

#pragma once

#include "logmgr.h"


//////////////////////////////////////////////////////////////////////////
// Common
#define SYSTEMOBJECT      "System.log"      // ϵͳ����     Ҫ��ʾ��Console�ϵ� �����ʾ
#define LOGICSYSTEMOBJECT "LogicSystem.log" // �߼�ϵͳ���� ����ʾ��Console��,�Ƚ���Ҫ��ϵͳ
#define CAPABILITYOBJECT  "Capability.log"  // ����
#define SQLOBJECT         "Sql.log"			// sql���
#define STATISTICSOBJECT  "Statistics.log"	// ͳ��
#define BILLINGOBJECT     "Billing.log"     // ��ֵϵͳ
#define SHOPPINGOBJECT    "Shopping.log"	// �̳Ǽ�¼
#define CHECKCHEATOBJECT  "CheckCheat.log"  // ��¼��ҵ�log
#define MAILOBJECT        "Mail.log"        // ��¼�ʼ���log
#define AUCTIONOBJECT	  "Auction.log"		// ��¼ϵͳ���׵�log
#define CHATOBJECT        "Chat.log"        // ����log
#define PKOBJECT          "PK.log"          // PK
#define ITEMDROPOBJECT    "ItemDrop.log"    // ������ƷLOG

// GameServer
#define PLAYERLOGIC		  "PlayerLogic.log" //����߼���־
#define SCRIPTOBJECT	  "Script.log"		//�ű���¼

// GateServer

// CenterServer
#define PLATFORMOBJECT	  "Platform.log"	//ƽ̨��־
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//�۲������˺�
#define TEST_ACCOUNT 1
#define TEST_ACCOUNT_NAME "echoaccount"

#define TEST_ACCOUNT_ID 9095853		// �޼����˺�

//#define TESTECHO_SWITCH

#ifdef TESTECHO_SWITCH
#define TESTECHORECV(accountID , message ) \
	if (  accountID == TEST_ACCOUNT_ID ) \
	{ \
	LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"TestEcho recv account[%d] [%s] [%s] [%d]",accountID, #message, __FUNCTION__, __LINE__ ); \
	}
#else
#define TESTECHORECV( accountID , message ) ;
#endif

#ifdef TESTECHO_SWITCH
#define TESTECHOSEND(accountID , message) \
	if (  accountID == TEST_ACCOUNT_ID ) \
	{ \
		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"TestEcho send account[%d] [%s] [%s] [%d]",accountID, #message, __FUNCTION__, __LINE__ ); \
	}
#else
#define TESTECHOSEND(accountID , message) ;
#endif

#endif // __LOGFILEOBJECTNAME_H__
