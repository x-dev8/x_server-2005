//募捐奖励配置信息
#pragma once
class PKConfig
{	
public:
	PKConfig(){}
	~PKConfig(){}
	bool LoadConfigFile(const char* FilePath);

	static PKConfig& Instance()
    {
        static PKConfig s_xConfig;
        return s_xConfig;
    }

	int GetEnterJianYu(){return EnterJianYu;}
	int GetLeaveJianYu(){return LeaveJianYu;}
	int GetMaxPKValue(){return MaxPKValue;}
	int GetMinPKValue(){return MinPKValue;}
	int GetPKKillValue(){return PKKillValue;}
	int GetPKValueUpdateTime(){return PKValueUpdateTime;}
	int GetEnterCriticalPK(){return EnterCriticalPK;}
	int GetCommonID(){return CommonID;}
private:
	int		EnterJianYu;//进入监狱的PK值
	int     LeaveJianYu;//离开监狱的PK值
	int		MaxPKValue;//最大PK值
	int		MinPKValue;//最小PK值
	int		PKKillValue;//杀死玩家加的PK值
	int		PKValueUpdateTime;//PK更新时间 单位毫秒
	int		EnterCriticalPK;//进入狂暴模式 红名的阀值
	int		CommonID;
};
#define thePKConfig PKConfig::Instance()