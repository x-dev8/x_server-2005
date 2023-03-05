#pragma once
#include <string>

using namespace std;
class CPlatFormConfig
{
public:
	CPlatFormConfig(void);
	~CPlatFormConfig(void);

	static CPlatFormConfig& Instance()
	{
		static CPlatFormConfig cpfc;
		return cpfc;
	}

	bool LoadConfig();

public:
	unsigned short ListenPort;
	unsigned short ListenClientPort;
	bool		   openCheckService;       //�Ƿ����ͻ���ֱ��,�����򲻴����ݿ��ȡ����

	string		   strTaskDatabaseUser;
	string		   strTaskDatabasePwd;
	string		   strTaskDatabaseName;
	string		   strTaskDatabaseIP;
	unsigned short TaskDatabasePort;

	/*string		   strAccountDatabaseUser;
	string		   strAccountDatabasePwd;
	string		   strAccountDatabaseName;
	

	string		   strLogDatabaseUser;
	string		   strLogDatabasePwd;
	string		   strLogDatabaseName;*/
};

#define thePlatFormConfig CPlatFormConfig::Instance()