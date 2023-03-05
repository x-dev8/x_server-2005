#pragma once
#include "CampGuildBattleConfig.h"
//��������ս�������ļ����� ÿһ���൱��һ������ս������ �������ö���
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
	int			m_BattleSum;//�����ļ���ǵľ���������
	std::map<unsigned int,CampGuildOnceBattleConfig> m_Config;//�����������Ϣ
};
#define theCampGuildUnionBattleConfig CampGuildUnionBattleConfig::Instance()