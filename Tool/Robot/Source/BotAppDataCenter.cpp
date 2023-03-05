#include "BotAppDataCenter.h"
#include "GlobalDef.h"
#include "application_config.h"

BotAppDataCenter::BotAppDataCenter(): ServerPort(0), WildCardNum(0), SleepTime(0), QueueLimit(0),
TensionTest(false), BotProfession(-1), BotFlyLimit(0), LoginThreadNum(0), bIsAlreadyInit(false), nNet(0)
{
    memset(Version,0,sizeof(Version));
    memset(BotPassword,0,sizeof(BotPassword));
    memset(BotAccount,0,sizeof(BotAccount));
    memset(ScriptFilePath,0,sizeof(ScriptFilePath));
    memset(ScriptFileName,0,sizeof(ScriptFileName));
    memset(BotAccount,0,sizeof(BotAccount));
    memset(ServerIp,0,sizeof(ServerIp));
    memset(GmCommondStr,0,sizeof(GmCommondStr));
    memset(ScriptFilePath,0,sizeof(ScriptFilePath));
}

uint32 BotAppDataCenter::Init(const char* pszConfig)
{
    if (bIsAlreadyInit)
    { return Successed; }

    char* szConfigFile = "..\\Data\\RobotScript\\Robot.ini";
    char* szDef = "GameBot";
    char szBuffer[256] = {0};
    memset( szBuffer, 0, sizeof(szBuffer));

    strncpy(Version, ApplicationConfig::Instance().GetFullVersion(), sizeof(BotAccount) - 1);
    GetIniInt(nNet, "Net", 0); // 得到网络
    GetIniStr(ServerIp, "Server", "192.168.50.127", sizeof(ServerIp));
	
	char buf[256];
	GetIniStr(buf, "HttpLogin", "172.20.254.17", sizeof(buf));
	m_strHttp=buf;
	
	
	GetIniInt(ServerPort, "Port", 20003 );
    GetIniInt(WildCardNum, "WildCardNum", 4 );
    GetIniStr(BotAccount, "UserName", "Robot",   sizeof(BotAccount));
    GetIniStr(BotPassword, "PassWord", "111111", sizeof(BotPassword));
    GetIniInt(SleepTime, "Sleep", 0);
    GetIniInt(QueueLimit,"QueueLimit", 5);
    int bIsTest = 0;
    GetIniInt (bIsTest,"IsTensionTest",0);
    bIsTest == 0?TensionTest = false:TensionTest = true;

    GetIniInt (BotProfession,"BotProfession",-1);
    GetIniInt (BotFlyLimit,"BotFlyLimit",0);
    GetIniStr(GmCommondStr, "GmCommandStr", "Robot.%s Test GM Broadcast", sizeof(GmCommondStr));

    GetIniStr(ScriptFilePath, "ScriptFilePath", "..\\Data\\RobotScript\\", sizeof(ScriptFilePath));
    GetIniStr(ScriptFileName, "ScriptFileName", "Bot.lua", sizeof(ScriptFileName));

    GetIniInt(LoginThreadNum,"LoginThreadNum",10);
    if (LoginThreadNum < 0)
    {
        LoginThreadNum = 0;
    }

    if (QueueLimit <= 0)
    {
        QueueLimit = 99999;
    }

    GetIniInt(OpenConsole, "OpenConsole", 0);
    if (OpenConsole == 1)
    {
        SetOpenConsole(true);
    }
    else
    {
        SetOpenConsole(false);
    }

    //if (nNet != 0 || nNet != 1)
    //{ SetBotNet(0);}    //如果不是0/1，则默认设置为内网

    bIsAlreadyInit = true;
    return Successed;
}

void BotAppDataCenter::WritePrivateProfileInt(LPCTSTR lpAppName,LPCTSTR lpKeyName, int nValue, LPCTSTR lpFileName)
{
    char strValue[20] = {0};
    sprintf_s(strValue,20,"%d",nValue);

    WritePrivateProfileString(lpAppName, lpKeyName, strValue, lpFileName);
}

bool BotAppDataCenter::SaveConfigFile(const char* FileName)
{
    if (NULL == FileName)
    {
        return false;
    }

    WritePrivateProfileInt("GameBot", "Net", GetBotNet(), FileName);
    WritePrivateProfileString("GameBot", "Server", GetServerIP(), FileName);
    WritePrivateProfileString("GameBot", "UserName", GetBotAccount(), FileName);
    WritePrivateProfileString("GameBot", "PassWord", GetBotPassword(), FileName);
    WritePrivateProfileInt("GameBot", "WildCardNum", GetAccountWidth(), FileName);
    WritePrivateProfileInt("GameBot", "Port", GetServerPort(), FileName);
    WritePrivateProfileInt("GameBot", "Sleep", SleepTime, FileName);
    WritePrivateProfileInt("GameBot", "QueueLimit",QueueLimit, FileName);
    WritePrivateProfileInt("GameBot", "IsTensionTest", TensionTest?1:0,FileName);
    WritePrivateProfileInt("GameBot", "BotProfession",BotProfession,FileName);
    WritePrivateProfileInt("GameBot", "BotFlyLimit",BotFlyLimit,FileName);
    WritePrivateProfileInt("GameBot", "LoginThreadNum",LoginThreadNum,FileName);
    WritePrivateProfileInt("GameBot", "OpenConsole", OpenConsole, FileName);
    return true;
}