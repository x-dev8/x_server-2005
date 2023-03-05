//����ʹ����
//ļ�轱��������Ϣ
#pragma once
#include <map>
class GuildMissionConfig
{
public:
	GuildMissionConfig();
	~GuildMissionConfig();
	bool LoadConfigFile(const char* FilePath);

	static GuildMissionConfig& Instance()
    {
        static GuildMissionConfig s_xConfig;
        return s_xConfig;
    }

	int	GetMissionValue(int GuildLevel);

	int GetInitMissionValue(){return m_InitMission;}
private:
	std::map<int,int>		m_Mission;
	int						m_InitMission;
};
#define theGuildMissionConfig GuildMissionConfig::Instance()