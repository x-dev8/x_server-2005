#include "MysqlConnectionPoolEx.h"

MysqlConnectionPoolEx::MysqlConnectionPoolEx( const std::string& dbName, const std::string& host, uint16 port, const std::string& user, const std::string& password ) 
{
    _dbName = dbName;     // 数据库名
    _host   = host;       // 地址
    _user   = user;       // 用户名
    _password = password; // 密码
    _port     = port;     // 端口
}

MysqlConnectionPoolEx::~MysqlConnectionPoolEx()
{ 
    clear(); 
}

mysqlpp::Connection* MysqlConnectionPoolEx::create()
{
    return new mysqlpp::Connection( _dbName.c_str(), _host.c_str(), _user.c_str(),_password.c_str(), _port );
}

void MysqlConnectionPoolEx::destroy(mysqlpp::Connection* cp)
{
    if ( cp != NULL )
    { delete cp;}
}
