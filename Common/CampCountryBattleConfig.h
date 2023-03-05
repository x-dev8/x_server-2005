#ifndef __CAMPCOUNTRYBATTLECONFIG_H__
#define __CAMPCOUNTRYBATTLECONFIG_H__

#include "CampBattleConfig.h"

//#define theCampCountryBattleConfig CampCountryBattleConfig::Instance()
//
//#define theKingCampBattleConfig CampCountryBattleConfig::KingCampInstance()

class CampCountryBattleConfig : public CampBattleConfig
{
public:
   /* static CampCountryBattleConfig& Instance()
    {
        static CampCountryBattleConfig s_xConfig;
        return s_xConfig;
    }

	static CampCountryBattleConfig& KingCampInstance()
	{
		static CampCountryBattleConfig s_xConfig;
		return s_xConfig;
	}*/

    class SignUpSetting
    {
    public:
        unsigned int GetMinGuildLevel() const { return nMinGuildLevel; }
        unsigned int GetMinMemberCount() const { return nMinMemberCount; }
        unsigned int GetCostGuildMoney() const { return nCostGuildMoney; }

        void SetMinGuildLevel( unsigned int nValue ) { nMinGuildLevel = nValue; }
        void SetMinMemberCount( unsigned int nValue ) { nMinMemberCount = nValue; }
        void SetCostGuildMoney( unsigned int nValue ) { nCostGuildMoney = nValue; }
    private:
        unsigned int nMinGuildLevel;
        unsigned int nMinMemberCount;
        unsigned int nCostGuildMoney;
    };

	class EnterSetting
	{
	public:
		unsigned int GetMaxEnterCount() const { return nMaxEnterCount; }
		unsigned int GetMinEnterLevel() const { return nMinEnterLevel; }

		void SetMaxEnterCount(unsigned int nValue) { nMaxEnterCount = nValue; }
		void SetMinEnterLevel(unsigned int nValue) { nMinEnterLevel = nValue; }
	private:
		unsigned int nMaxEnterCount;
		unsigned int nMinEnterLevel;
	};

    // 加载设定
    virtual bool LoadConfig( const char* szFile,unsigned char countryid = CountryDefine::Country_Init );

    const SignUpSetting& GetSignUpSetting() const;

	const EnterSetting& GetEnterSetting() const;

    unsigned int GetMaxDeathCount() const;
	unsigned int GetMaxScoreCount() const;
	unsigned int GetRedScore();
	unsigned int GetBlueScore();

	//zhuxincong这个是为了保持最后的稳定
	void SetRedScore(){nRedScore = nMaxScore;}
	void SetBlueScore(){nBlueScore = nMaxScore;}

	//zhuxincong 这个是为了让分数有个判断
	void SetFRedScore(int nValue){nRedScore = nValue;}
	void SetFBlueScore(int nValue){nBlueScore = nValue;}



	/*void SetCountryID(unsigned char uchid){uchCoutryID = uchid;}
	unsigned char GetCountryID(){return uchCoutryID;}*/

protected:
   // virtual bool LoadResourceSetting( MeXmlElement* pElement ) { return true; }
    virtual bool LoadRewardSetting( MeXmlElement* pElement ) { return true; }
    virtual bool LoadMonsterSetting( MeXmlElement* pElement ) { return true; }

protected:
    SignUpSetting xSignUpSetting;

	EnterSetting xEnterSetting;

    unsigned int nMaxDeathCount;

	unsigned int nMaxScore;//国战基分 初始化的
	unsigned int nRedScore;
	unsigned int nBlueScore;
	
	//unsigned char uchCoutryID;
};

inline const CampCountryBattleConfig::SignUpSetting& CampCountryBattleConfig::GetSignUpSetting() const
{
    return xSignUpSetting;
}

inline const CampCountryBattleConfig::EnterSetting& CampCountryBattleConfig::GetEnterSetting() const
{
	return xEnterSetting;
}

inline unsigned int CampCountryBattleConfig::GetMaxDeathCount() const
{
    return nMaxDeathCount;
}

inline unsigned int CampCountryBattleConfig::GetMaxScoreCount() const
{
	return nMaxScore;
}

inline unsigned int CampCountryBattleConfig::GetRedScore()
{
	return nRedScore;
}

inline unsigned int CampCountryBattleConfig::GetBlueScore()
{
	return nBlueScore;
}
#endif