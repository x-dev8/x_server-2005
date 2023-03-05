#ifndef _GLSSERVICE_H_
#define _GLSSERVICE_H_

#pragma once

#include "GlobalDef.h"
#include "mysql++.h"
#include <map>
#include "Mutex.h"

using namespace std;

class GLSService
{
public:

	struct SBlockInfo 
	{
		unsigned long guid;
		char		  name[MAX_NAME_STRING];//账号名
		unsigned long blocktime; // 注意这个是秒
		unsigned long begintime;
	};
	struct SBlockInfoMac 
	{
		char		  cMac[MAC_LENGTH];
		unsigned long blocktime;
		unsigned long begintime;
	};

	enum EWorkStatus
	{
		SS_TryConnect,
		SS_Connected,
		SS_ReConnected,
	};
public:
	GLSService(void);
	~GLSService(void);

	static GLSService& Instance()
	{
		static GLSService gls;
		return gls;
	}

	bool _CheckState();        // 检查SqlService运行情况
	void RunOnStep();
	void ReLoadBlockInfo(){_loadblockinfo = false;}	// 重新加载机制
	
	int	 CheckBlockAccount(char* accountname); //检查这个账号锁剩余的时间
	bool AddNewBlockInfoPublic(SBlockInfo* pInfo);

	int	 CheckBlockUserMac( const char* cMac);//检查这个mac锁剩余的时间
	bool AddNewBlockInfoMacPublic(SBlockInfoMac* pInfo);

	//tool
	int	 GetBlockInfoSize(){return m_mapBlockInfo.size();}
protected:
	void _TryConnectToSqlDb();
	void RunBlockInfo();
	void LoadBlockInfo();	   // 从数据库加载锁定信息 并不是启动的时候加载一次的
	void RunOverdueBlockInfo();

	void ProcessNewBlockInfo();
	bool InsertNewBlockInfo(SBlockInfo* pInfo);
	bool AddBlockInfo(SBlockInfo* pInfo);
	void DelBlockInfo(SBlockInfo* pInfo);
	SBlockInfo* GetBlockInfoByName(const char* name);

	void ProcessNewBlockInfoMac();
	bool InsertNewBlockInfoMac(SBlockInfoMac* pInfo);
	bool AddBlockInfoMac(SBlockInfoMac* pInfo);
	void DelBlockInfoMac(SBlockInfoMac* pInfo);
	SBlockInfoMac* GetBlockInfoByMac(const char* cMac);

private:
	mysqlpp::Connection* _pMysqlConnect;  // 和mysql 的连接
	unsigned char		 _workState;      // 连接的状态
	unsigned long        _lastUpdateTime; // 最新的更新时间
	bool				 _loadblockinfo;  // 锁定信息是否已经载入
	unsigned long		 _lastRunBlocktime;//最新检测的时间

	//********************************** for account
	typedef map<string,SBlockInfo*> _mapBlockInfo;
	_mapBlockInfo					m_mapBlockInfo;		// 正在锁定的account信息
	_mapBlockInfo					m_mapOverdueBlockInfo;// 正要解锁的信息
	CSemiAutoIntLock				_Lock;

	typedef std::list<SBlockInfo*>  ContainerBlockInfo;	
	ContainerBlockInfo				m_BlockInfoList;	// 多线程所以提供一个运行时添加锁账号的列表
	CSemiAutoIntLock				_LockList;
	//********************************** for Mac
	typedef map<string,SBlockInfoMac*> _mapBlockInfoMac;
	_mapBlockInfoMac					m_mapBlockInfoMac;	// 正在锁定的mac信息
	_mapBlockInfoMac					m_mapOverdueBlockInfoMac;// 正要解锁的信息
	CSemiAutoIntLock				_LockMac;

	typedef std::list<SBlockInfoMac*>  ContainerBlockInfoMac;	
	ContainerBlockInfoMac				m_BlockInfoListMac;// 多线程所以提供一个运行时添加锁账号的列表
	CSemiAutoIntLock				_LockListMac;
	//**********************************
};

#define theGLSService GLSService::Instance()


#define TRYBEGIN  try {

#define TRYEND } \
	catch (mysqlpp::BadQuery er) \
{ \
	printf( "BadQuery [%s] Error:%s",szSql, er.what()); \
	result = false; \
} \
	catch (const mysqlpp::BadConversion& er)  \
{ \
	printf( "BadConversion [%s] Error:%s retrieved data size:%d, actual size:%d",szSql,er.what(), er.retrieved, er.actual_size); \
	result = false; \
} \
	catch (const mysqlpp::Exception& er) \
{ \
	printf( "mysqlpp::Exception [%s] Error:%s",szSql, er.what()); \
	result = false; \
}\
	catch(exception &er) \
{ \
	printf( "std::exception [%s] Error:%s",szSql, er.what()); \
	result = false; \
}

#define FREESTOREPROCEDURE_TRY \
	try \
{ \
	while(mysqlQuery.more_results()) \
{ mysqlQuery.store_next(); } \
} \
	catch ( ... ) \
{ }


#endif