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

    char GmCommondStr[BuffSize];   // 调试平台GM广播消息，里面必须只包含一个%s 
    char ScriptFilePath[MAX_PATH]; // Lua脚本路径
    char ScriptFileName[FILENAME_MAX]; // Lua脚本文件名
    

    int  SleepTime;                // 机器人休眠时间
    int  QueueLimit;               // 排队限制数
    bool TensionTest;              // 排队限制是否生效
    int16 BotProfession;           // 机器人职业
    int   BotFlyLimit;             // 机器人飞地图限制

    int  GetBotNet() { return nNet;}
    void SetBotNet(int net){ nNet = net;}
    
    bool GetOpenConsole() { return OpenConsole;}
    void SetOpenConsole(bool b) { OpenConsole = b;}

	std::string	m_strHttp;
private:
    int  nNet;      // 目标网络类型
    char ServerIp[IpBuffSize];          // 目标服务器IP
    uint16 ServerPort;                  // 目标服务器端口
    char Version[VersionBuffSize];      // version
    int  WildCardNum;                   // 限制帐号的位数
    char BotAccount[SamllBuffSize];     // 机器人帐号
    char BotPassword[SamllBuffSize];    // 机器人密码
    int  LoginThreadNum;                // 登录线程数
    bool  OpenConsole;                   // 是否打开控制台

    bool bIsAlreadyInit;                // 是否已经初始化过
private:
    BotAppDataCenter();
    BotAppDataCenter(const BotAppDataCenter&);
    BotAppDataCenter& operator = (const BotAppDataCenter&);
};

#define theBotDataCenter BotAppDataCenter::GetInstance()

#endif