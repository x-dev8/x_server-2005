//����ս����������Ϣ 
#pragma once
struct GuildCampBattleSetting
{
	int MaxSum;//������õ�����
	int MinLevel;//��͵ĵȼ�
	unsigned char Profession;//ְҵ
	int Offer;//����
	bool IsOpen;//�Ƿ���
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