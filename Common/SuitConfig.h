#pragma once
#include <map>
#include <vector>
struct SuitAtt
{
	const static int MAXSUITNAMELENGTH = 32;
	unsigned int ID;//��װ��ID
	char Name[MAXSUITNAMELENGTH];//��װ������
	bool IsRepeatItem;//�Ƿ�����ظ���װ��
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
	std::map<unsigned int,SuitAtt>	m_SuiltList;//��װ��ȫ������
	//����װ���н�������
	std::map<unsigned int,unsigned int> m_ItemToSuitID;//������ƷID��ȡ��װID
};
#define theSuitConfig SuitConfig::Instance()