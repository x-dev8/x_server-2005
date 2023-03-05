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
		char		  name[MAX_NAME_STRING];//�˺���
		unsigned long blocktime; // ע���������
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

	bool _CheckState();        // ���SqlService�������
	void RunOnStep();
	void ReLoadBlockInfo(){_loadblockinfo = false;}	// ���¼��ػ���
	
	int	 CheckBlockAccount(char* accountname); //�������˺���ʣ���ʱ��
	bool AddNewBlockInfoPublic(SBlockInfo* pInfo);

	int	 CheckBlockUserMac( const char* cMac);//������mac��ʣ���ʱ��
	bool AddNewBlockInfoMacPublic(SBlockInfoMac* pInfo);

	//tool
	int	 GetBlockInfoSize(){return m_mapBlockInfo.size();}
protected:
	void _TryConnectToSqlDb();
	void RunBlockInfo();
	void LoadBlockInfo();	   // �����ݿ����������Ϣ ������������ʱ�����һ�ε�
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
	mysqlpp::Connection* _pMysqlConnect;  // ��mysql ������
	unsigned char		 _workState;      // ���ӵ�״̬
	unsigned long        _lastUpdateTime; // ���µĸ���ʱ��
	bool				 _loadblockinfo;  // ������Ϣ�Ƿ��Ѿ�����
	unsigned long		 _lastRunBlocktime;//���¼���ʱ��

	//********************************** for account
	typedef map<string,SBlockInfo*> _mapBlockInfo;
	_mapBlockInfo					m_mapBlockInfo;		// ����������account��Ϣ
	_mapBlockInfo					m_mapOverdueBlockInfo;// ��Ҫ��������Ϣ
	CSemiAutoIntLock				_Lock;

	typedef std::list<SBlockInfo*>  ContainerBlockInfo;	
	ContainerBlockInfo				m_BlockInfoList;	// ���߳������ṩһ������ʱ������˺ŵ��б�
	CSemiAutoIntLock				_LockList;
	//********************************** for Mac
	typedef map<string,SBlockInfoMac*> _mapBlockInfoMac;
	_mapBlockInfoMac					m_mapBlockInfoMac;	// ����������mac��Ϣ
	_mapBlockInfoMac					m_mapOverdueBlockInfoMac;// ��Ҫ��������Ϣ
	CSemiAutoIntLock				_LockMac;

	typedef std::list<SBlockInfoMac*>  ContainerBlockInfoMac;	
	ContainerBlockInfoMac				m_BlockInfoListMac;// ���߳������ṩһ������ʱ������˺ŵ��б�
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