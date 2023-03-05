#include "Raise.h"
#include "RapidXml/MeRapidXml.h"
RaiseConfig::RaiseConfig()
{
	
}
RaiseConfig::~RaiseConfig()
{

}
bool RaiseConfig::LoadConfigFile(const char* FilePath)
{
	//加载指定的配置文件
	MeXmlDocument mKwameXmlDoc;
	if (!mKwameXmlDoc.LoadFile(FilePath)) return false;
	MeXmlElement* pRoot = mKwameXmlDoc.FirstChildElement("country");
	if(pRoot != NULL)
	{
		MeXmlElement* pInfo = pRoot->FirstChildElement("info");
		while (pInfo != NULL)
		{
			RaiseInfo ri;
			
			int MinSum = 0;
			if (pInfo->Attribute("minSum",&MinSum) == NULL)
				return false;
			ri.MinMoneySum = MinSum;
			
			int MaxSum =0;
			if (pInfo->Attribute("maxSum",&MaxSum) == NULL)
				MaxSum = -1;
			ri.MaxMoneySum = MaxSum;

			int ItemID = 0;
			if (pInfo->Attribute("ItemID",&ItemID) == NULL) 
				return false;
			ri.ItemID = ItemID;

			if (pInfo->Attribute("MontyToExp",&ri.MontyToExp) == NULL) 
				return false;
			if (pInfo->Attribute("ItemProbability",&ri.ItemProbability) == NULL) 
				return false;

			m_CountryRaiseInfo.push_back(ri);

			pInfo = pInfo->NextSiblingElement("info");
		}
	}
	pRoot = pRoot->NextSiblingElement("guild");
	if(pRoot != NULL)
	{
		MeXmlElement* pInfo = pRoot->FirstChildElement("info");
		while (pInfo != NULL)
		{
			RaiseInfo ri;
			
			int MinSum = 0;
			if (pInfo->Attribute("minSum",&MinSum) == NULL)
				return false;
			ri.MinMoneySum = MinSum;
			
			int MaxSum =0;
			if (pInfo->Attribute("maxSum",&MaxSum) == NULL)
				MaxSum = -1;
			ri.MaxMoneySum = MaxSum;

			int ItemID = 0;
			if (pInfo->Attribute("ItemID",&ItemID) == NULL) 
				return false;
			ri.ItemID = ItemID;

			if (pInfo->Attribute("MontyToExp",&ri.MontyToExp) == NULL) 
				return false;
			if (pInfo->Attribute("ItemProbability",&ri.ItemProbability) == NULL) 
				return false;

			m_GuildRaiseInfo.push_back(ri);

			pInfo = pInfo->NextSiblingElement("info");
		}
	}
	return true;
}
void RaiseConfig::GetExpAndItemByGuildMoney(unsigned int MoneySum,unsigned int& ExpSum,unsigned int& ItemID)
{
	ExpSum =0;
	ItemID = 0;
	if(m_GuildRaiseInfo.empty()) return;
	float jilv = 0;
	std::vector<RaiseInfo>::iterator Iter = m_GuildRaiseInfo.begin();
	for(;Iter != m_GuildRaiseInfo.end();++Iter)
	{
		//判断奖励
		if(Iter->MinMoneySum >= MoneySum)
			continue;
		if(Iter->MaxMoneySum >= MoneySum)
		{
			ExpSum += (unsigned int)((MoneySum - Iter->MinMoneySum) * Iter->MontyToExp);
			ItemID = Iter->ItemID;
			jilv = Iter->ItemProbability;
		}
		else
		{
			ExpSum += (unsigned int)((Iter->MaxMoneySum - Iter->MinMoneySum) * Iter->MontyToExp);
		}
	}
	//生成随机数 判断是否需要奖励
	jilv = jilv * 100;
	int x = rand() % 100 +1;// 1-100
	if(jilv < x)
	{
		ItemID = 0;
	}
}
void RaiseConfig::GetExpAndItemByCountryMoney(unsigned int MoneySum,unsigned int& ExpSum,unsigned int& ItemID)
{
	ExpSum =0;
	ItemID = 0;
	if(m_CountryRaiseInfo.empty()) return;
	float jilv = 0;
	std::vector<RaiseInfo>::iterator Iter = m_CountryRaiseInfo.begin();
	for(;Iter != m_CountryRaiseInfo.end();++Iter)
	{
		//判断奖励
		if(Iter->MinMoneySum >= MoneySum)
			continue;
		if(Iter->MaxMoneySum >= MoneySum)
		{
			ExpSum += (unsigned int)((MoneySum - Iter->MinMoneySum) * Iter->MontyToExp);
			ItemID = Iter->ItemID;
			jilv = Iter->ItemProbability;
		}
		else
		{
			ExpSum += (unsigned int)((Iter->MaxMoneySum - Iter->MinMoneySum) * Iter->MontyToExp);
		}
	}
	//生成随机数 判断是否需要奖励
	jilv = jilv * 100;
	int x = rand() % 100 +1;// 1-100
	if(jilv < x)
	{
		ItemID = 0;
	}
}