#pragma once
#include "CampGuildBattleConfig.h"
//公会联合战的配置文件处理 每一轮相当于一个工会战的配置 可以配置多轮
class CampGuildOnceBattleConfig : public CampGuildBattleConfig
{
public:
	CampGuildOnceBattleConfig(){}
	bool Init(MeXmlElement* pGuildBattle);
	 ~CampGuildOnceBattleConfig(){}

	 int GetBattleSum(){return BattleSum;}
private:
	int		BattleSum;
};

class CampGuildUnionBattleConfig 
{
public:
	static CampGuildUnionBattleConfig& Instance()
    {
        static CampGuildUnionBattleConfig s_xConfig;
        return s_xConfig;
    }
	CampGuildUnionBattleConfig();
	~CampGuildUnionBattleConfig();
	bool LoadConfig( const char* szFile );
	CampGuildOnceBattleConfig& GetGuildBattleSumConfig(int BattleSum);
	int GetBattleSum(){return m_BattleSum;}
private:
	int			m_BattleSum;//配置文件标记的经历的轮数
	std::map<unsigned int,CampGuildOnceBattleConfig> m_Config;//具体的配置信息
};
#define theCampGuildUnionBattleConfig CampGuildUnionBattleConfig::Instance()