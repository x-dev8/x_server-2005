//ļ�轱��������Ϣ
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
	int		EnterJianYu;//���������PKֵ
	int     LeaveJianYu;//�뿪������PKֵ
	int		MaxPKValue;//���PKֵ
	int		MinPKValue;//��СPKֵ
	int		PKKillValue;//ɱ����Ҽӵ�PKֵ
	int		PKValueUpdateTime;//PK����ʱ�� ��λ����
	int		EnterCriticalPK;//�����ģʽ �����ķ�ֵ
	int		CommonID;
};
#define thePKConfig PKConfig::Instance()