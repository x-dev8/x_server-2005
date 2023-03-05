/********************************************************************
    Filename:    MysqlTableStruct.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __MYSQLTABLESTRUCT_H__
#define __MYSQLTABLESTRUCT_H__

#pragma once

#include "mysql++.h"
#include "ssqls.h"

sql_create_16( account_billing_log,
              1, 16,
              mysqlpp::sql_int,      id,
              mysqlpp::sql_smallint, typeid,
              mysqlpp::sql_varchar,  typesn,
              mysqlpp::sql_int,      guid,
              mysqlpp::sql_smallint, addamount,
              mysqlpp::sql_int,      netincome,
              mysqlpp::sql_int,      lastaccountpoint, 
              mysqlpp::sql_int,      addaccountpoint,
              mysqlpp::sql_int,      finalaccountpoint,
              mysqlpp::sql_smallint, discount,
              mysqlpp::sql_varchar,  gateway,
              mysqlpp::sql_smallint, channel,
              mysqlpp::sql_int,      paytime,
              mysqlpp::sql_int,      addtime,
              mysqlpp::sql_int,      userip,
              mysqlpp::sql_varchar,  remark )
// sql_create_( characters_bases, 1, )

#endif // __MYSQLTABLESTRUCT_H__
