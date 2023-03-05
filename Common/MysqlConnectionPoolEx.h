/********************************************************************
    Filename:    MysqlConnectionPoolEx.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_MYSQLCONNECTIONPOOLEX_H__
#define __COMMON_MYSQLCONNECTIONPOOLEX_H__

#pragma once

#include "MeRTLibs.h"
#include "mysql++.h"

class MysqlConnectionPoolEx : public mysqlpp::ConnectionPool
{
public:
    MysqlConnectionPoolEx( const std::string& dbName, const std::string& host, uint16 port, const std::string& user, const std::string& password );
    ~MysqlConnectionPoolEx();

protected:
    virtual mysqlpp::Connection* create();
    virtual void destroy(mysqlpp::Connection* cp);
    virtual unsigned int max_idle_time() { return 3;}

private: 
    std::string _dbName;   // 数据库名
    std::string _host;     // 地址
    std::string _user;     // 用户名
    std::string _password; // 密码
    uint16      _port;     // 端口
};

#endif // __COMMON_MYSQLCONNECTIONPOOLEX_H__
