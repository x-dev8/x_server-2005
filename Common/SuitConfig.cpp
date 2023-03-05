#include "SuitConfig.h"
#include "RapidXml/MeRapidXml.h"
#include "tstring.h"
SuitConfig::SuitConfig()
{

}
SuitConfig::~SuitConfig()
{

}
bool SuitConfig::LoadFilePath(const char* FilePath)
{
	//读取配置文件
	MeXmlDocument mKwameXmlDoc;
	if (!mKwameXmlDoc.LoadFile(FilePath)) 
		return false;
	MeXmlElement* pRoot = mKwameXmlDoc.FirstChildElement("Project");
	if(pRoot == NULL)
		return false;
	MeXmlElement* pSuitSRoot = pRoot->FirstChildElement("SuitS");
	if(pSuitSRoot == NULL)
		return false;
	MeXmlElement * pSuit = pSuitSRoot->FirstChildElement( "Suit" );
	while ( pSuit != NULL )
	{
		SuitAtt sa;
		int ID = 0;
		if ( pSuit->Attribute( "ID", &ID ) == NULL )
			return false;
		sa.ID  = (unsigned int)ID;

		Common::_tstring strValue;
		strValue.fromUTF8(pSuit->Attribute( "Name"));
		std::string Name = strValue;
		if(Name.empty())
			return false;
		strcpy_s(sa.Name,sa.MAXSUITNAMELENGTH,Name.c_str());

		int nValue = 0;
		if ( pSuit->Attribute( "RepeatItem", &nValue ) == NULL )
			return false;
		sa.IsRepeatItem = (nValue == 1?true:false);

		MeXmlElement * pAtts = pSuit->FirstChildElement("SuitAtts");
		if(pAtts)
		{
			MeXmlElement * pAtt = pAtts->FirstChildElement("SuitAtt");
			while ( pAtt != NULL )
			{
				int Sum =0;
				if ( pAtt->Attribute( "Sum", &Sum ) == NULL )
					return false;
				int Suit = 0;
				if ( pAtt->Attribute( "SuitID", &Suit ) == NULL )
					return false;
				sa.SuitList.insert(std::map<unsigned char,unsigned int>::value_type((unsigned int)Sum,(unsigned int)Suit));
				pAtt = pAtt->NextSiblingElement();
			}
		}
		MeXmlElement * pItems = pSuit->FirstChildElement("Items");
		if(pItems)
		{
			MeXmlElement * pItem = pItems->FirstChildElement("Once");
			while(pItem!= NULL)
			{
				int ItemID = 0;
				if ( pItem->Attribute( "ItemID", &ItemID ) == NULL )
					return false;
				sa.ItemList.push_back((unsigned int)ItemID);

				m_ItemToSuitID.insert(std::map<unsigned int,unsigned int>::value_type((unsigned int)ItemID,sa.ID));
			
				pItem = pItem->NextSiblingElement();
			}
		}
		m_SuiltList.insert(std::map<unsigned int,SuitAtt>::value_type(sa.ID,sa));
		pSuit = pSuit->NextSiblingElement();
	}
	return true;
}
unsigned int SuitConfig::GetSuitIDByItemID(unsigned int ItemID)
{
	if(m_ItemToSuitID.count(ItemID) == 1)
		return m_ItemToSuitID.find(ItemID)->second;
	else
		return 0;
}
SuitAtt* SuitConfig::GetSuitInfoBySuitID(unsigned int SuitID)
{
	if(m_SuiltList.count(SuitID))
		return &m_SuiltList.find(SuitID)->second;
	else
		return NULL;
}
bool SuitConfig::IsRepeatSum(unsigned int SuitID)
{
	SuitAtt*  pSuit = GetSuitInfoBySuitID(SuitID);
	if(pSuit)
		return pSuit->IsRepeatItem;
	else
		return false;
}
void SuitAtt::GetAllFullSuitIDBySum(unsigned char Sum,std::vector<unsigned int>& vecList)
{
	vecList.clear();
	//根据已经装备的套装的件数 获取可以获取的属性ID
	std::map<unsigned char,unsigned int>::iterator Iter = SuitList.begin();
	for(;Iter != SuitList.end();++Iter)
	{
		if(Sum >= Iter->first)
		{
			vecList.push_back(Iter->second);
		}
	}
}