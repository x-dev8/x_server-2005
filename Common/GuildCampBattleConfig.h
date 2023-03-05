//公会战场的配置信息 
#pragma once
struct GuildCampBattleSetting
{
	int MaxSum;//最多设置的人数
	int MinLevel;//最低的等级
	unsigned char Profession;//职业
	int Offer;//贡献
	bool IsOpen;//是否开启
};
class GuildCampBattleConfig
{
public:
	GuildCampBattleConfig();
	virtual ~GuildCampBattleConfig(){}
	bool OnLoadFilePath(const char* FilePath);

	GuildCampBattleSetting	m_GuildSetting;
	GuildCampBattleSetting  m_CountrySetting;
	GuildCampBattleSetting  m_GuildUnionSetting;
	GuildCampBattleSetting	m_GuildGeneralSetting;
};