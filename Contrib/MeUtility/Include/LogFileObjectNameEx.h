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
#define SYSTEMOBJECT      "System.log"      // 系统级别     要显示在Console上的 最高提示
#define LOGICSYSTEMOBJECT "LogicSystem.log" // 逻辑系统级别 不显示在Console上,比较重要的系统
#define CAPABILITYOBJECT  "Capability.log"  // 性能
#define SQLOBJECT         "Sql.log"			// sql语句
#define STATISTICSOBJECT  "Statistics.log"	// 统计
#define BILLINGOBJECT     "Billing.log"     // 冲值系统
#define SHOPPINGOBJECT    "Shopping.log"	// 商城记录
#define CHECKCHEATOBJECT  "CheckCheat.log"  // 记录外挂的log
#define MAILOBJECT        "Mail.log"        // 记录邮件的log
#define AUCTIONOBJECT	  "Auction.log"		// 记录系统交易的log
#define CHATOBJECT        "Chat.log"        // 聊天log
#define PKOBJECT          "PK.log"          // PK
#define ITEMDROPOBJECT    "ItemDrop.log"    // 掉落物品LOG

// GameServer
#define PLAYERLOGIC		  "PlayerLogic.log" //玩家逻辑日志
#define SCRIPTOBJECT	  "Script.log"		//脚本记录

// GateServer

// CenterServer
#define PLATFORMOBJECT	  "Platform.log"	//平台日志
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//观测特殊账号
#define TEST_ACCOUNT 1
#define TEST_ACCOUNT_NAME "echoaccount"

#define TEST_ACCOUNT_ID 9095853		// 罗坚封测账号

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
