#pragma once
#include <map>
#include <vector>
struct SuitAtt
{
	const static int MAXSUITNAMELENGTH = 32;
	unsigned int ID;//套装的ID
	char Name[MAXSUITNAMELENGTH];//套装的名称
	bool IsRepeatItem;//是否计算重复的装备
	std::vector<unsigned int> ItemList;
	std::map<unsigned char,unsigned int> SuitList; 
	void GetAllFullSuitIDBySum(unsigned char Sum,std::vector<unsigned int>& vecList);
};

class SuitConfig
{
public:
	SuitConfig();
	~SuitConfig();

	static SuitConfig& Instance()
    {
        static SuitConfig s_xConfig;
        return s_xConfig;
    }

	bool LoadFilePath(const char* FilePath);

	unsigned int GetSuitIDByItemID(unsigned int ItemID);
	SuitAtt* GetSuitInfoBySuitID(unsigned int SuitID);
	bool IsRepeatSum(unsigned int SuitID);
private:
	std::map<unsigned int,SuitAtt>	m_SuiltList;//套装的全部内容
	//对套装进行建立索引
	std::map<unsigned int,unsigned int> m_ItemToSuitID;//根据物品ID获取套装ID
};
#define theSuitConfig SuitConfig::Instance()