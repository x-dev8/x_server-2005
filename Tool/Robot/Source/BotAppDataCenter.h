#ifndef _BotAppDataCenter_
#define _BotAppDataCenter_
#include "MeRTLibsServer.h"

class BotAppDataCenter
{
public:
    enum ConstValue
    {
        BuffSize = 512,
        VersionBuffSize = 30,
        IpBuffSize = 20,
        SamllBuffSize = 20,
    };

    enum IniResult
    {
        Successed = 0,
        Fail = 1,
    };

public:
    static BotAppDataCenter& GetInstance()
    {
        static BotAppDataCenter _Object;
        return _Object;
    }

    ~BotAppDataCenter(){}

    uint32 Init(const char* pszConfig);


    char* GetServerIP()  { return ServerIp; }
    void SetServerIp(const char* pServerIp){
        if(NULL == pServerIp)
            return;
        strncpy_s(ServerIp,IpBuffSize,pServerIp,IpBuffSize-1);
    }
    uint16  GetServerPort() { return ServerPort; }
    void    SetServerPort(uint16 port){ServerPort = port;}

    const char* GetVersion() { return Version; }
    void SetVersion(const char* pVersion)
    {
        if(NULL == pVersion)
            return;
        strncpy_s(Version,VersionBuffSize,pVersion,VersionBuffSize-1);
    }
    char* GetBotAccount() { return BotAccount; }
    void SetBotAccount(const char* pAccount)
    {
        if (NULL == pAccount)
            return;
        strncpy_s(BotAccount,SamllBuffSize,pAccount,SamllBuffSize-1);
    }
    char *GetBotPassword() { return BotPassword; }
    void SetBotPassword(const char* pPassword)
    {
        if (NULL == pPassword)
            return;
        strncpy_s(BotPassword,SamllBuffSize,pPassword,SamllBuffSize-1);
    }
    int     GetAccountWidth() { return WildCardNum; }
    void    SetAccountWidth(int wildcardnum){WildCardNum = wildcardnum;}

    int GetLoginThreadNum(){ return LoginThreadNum; }

    void WritePrivateProfileInt(LPCTSTR lpAppName,LPCTSTR lpKeyName, int nValue, LPCTSTR lpFileName);
    bool SaveConfigFile(const char* FileName);

    char GmCommondStr[BuffSize];   // ����ƽ̨GM�㲥��Ϣ���������ֻ����һ��%s 
    char ScriptFilePath[MAX_PATH]; // Lua�ű�·��
    char ScriptFileName[FILENAME_MAX]; // Lua�ű��ļ���
    

    int  SleepTime;                // ����������ʱ��
    int  QueueLimit;               // �Ŷ�������
    bool TensionTest;              // �Ŷ������Ƿ���Ч
    int16 BotProfession;           // ������ְҵ
    int   BotFlyLimit;             // �����˷ɵ�ͼ����

    int  GetBotNet() { return nNet;}
    void SetBotNet(int net){ nNet = net;}
    
    bool GetOpenConsole() { return OpenConsole;}
    void SetOpenConsole(bool b) { OpenConsole = b;}

	std::string	m_strHttp;
private:
    int  nNet;      // Ŀ����������
    char ServerIp[IpBuffSize];          // Ŀ�������IP
    uint16 ServerPort;                  // Ŀ��������˿�
    char Version[VersionBuffSize];      // version
    int  WildCardNum;                   // �����ʺŵ�λ��
    char BotAccount[SamllBuffSize];     // �������ʺ�
    char BotPassword[SamllBuffSize];    // ����������
    int  LoginThreadNum;                // ��¼�߳���
    bool  OpenConsole;                   // �Ƿ�򿪿���̨

    bool bIsAlreadyInit;                // �Ƿ��Ѿ���ʼ����
private:
    BotAppDataCenter();
    BotAppDataCenter(const BotAppDataCenter&);
    BotAppDataCenter& operator = (const BotAppDataCenter&);
};

#define theBotDataCenter BotAppDataCenter::GetInstance()

#endif