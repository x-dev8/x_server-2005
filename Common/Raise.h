//ƒºæËΩ±¿¯≈‰÷√–≈œ¢
#pragma once
#include <vector>
class RaiseConfig
{
public:
	struct RaiseInfo
	{
		unsigned int	MinMoneySum;
		unsigned int  MaxMoneySum;
		float   MontyToExp;
		float   ItemProbability;
		unsigned int	ItemID;
	};
public:
	RaiseConfig();
	~RaiseConfig();
	bool LoadConfigFile(const char* FilePath);

	static RaiseConfig& Instance()
    {
        static RaiseConfig s_xConfig;
        return s_xConfig;
    }
	
	void GetExpAndItemByGuildMoney(unsigned int MoneySum,unsigned int& ExpSum,unsigned int& ItemID);
	void GetExpAndItemByCountryMoney(unsigned int MoneySum,unsigned int& ExpSum,unsigned int& ItemID);
private:
	std::vector<RaiseInfo>		m_CountryRaiseInfo;
	std::vector<RaiseInfo>		m_GuildRaiseInfo;
};
#define theRaiseConfig RaiseConfig::Instance()