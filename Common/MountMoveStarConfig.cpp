#include "MountMoveStarConfig.h"
#include "RapidXml/MeRapidXml.h"
#include "GlobalDef.h"
MountMoveStarConfig::MountMoveStarConfig()
{
	
}
MountMoveStarConfig::~MountMoveStarConfig()
{

}
bool MountMoveStarConfig::LoadMountMoveStarConfig(const char* FilePath)
{
	//加载配置文件
	if ( FilePath == NULL || FilePath[ 0 ] == 0 )
    { return false; }

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( FilePath, 1 ) )
    { return false; }

    MeXmlElement* pMounts = xMeXml.FirstChildElement( "Mounts" );
    if ( pMounts == NULL )
    { return false; }

	MeXmlElement* pMount = pMounts->FirstChildElement( "Mount" );
    while ( pMount != NULL )
	{
		//读取移星的配置
		MountMoveStatStruct pMountStruct;
		int nValue = 0;

		if ( pMount->Attribute( "StarLevel", &nValue ) == NULL )
			return false;
		pMountStruct.Star = nValue;
		nValue = 0;

		if ( pMount->Attribute( "Money", &nValue ) == NULL )
			return false;
		pMountStruct.Money = nValue;
		nValue = 0;

		char tempchar[64] = {0};
		for(int i =0;i<SMountItem::MICD_MountMaxLevel;++i)
		{
			//读取掉星的记录
			sprintf_s(tempchar,64,"DownStar%d",i);
			if ( pMount->Attribute(tempchar, &nValue ) == NULL )
			{
				pMountStruct.DownStarVec.push_back(0);
				continue;
			}
			pMountStruct.DownStarVec.push_back(nValue);
			nValue = 0;
			ZeroMemory(tempchar,sizeof(char) * 64);
		}

		//记录需要的物品数据
		MeXmlElement* pItem = pMount->FirstChildElement( "Item" );
        while ( pItem != NULL )
		{
			int ItemID = 0;
			int ItemSum = 0;

			if ( pItem->Attribute( "ItemID", &ItemID ) == NULL )
				return false;
			if ( pItem->Attribute( "ItemSum", &ItemSum ) == NULL )
				return false;

			pMountStruct.ItemMap.insert(std::map<unsigned int,unsigned int>::value_type(ItemID,ItemSum));

			pItem = pItem->NextSiblingElement();
		}
		m_ConfigMap.insert(std::map<unsigned int,MountMoveStatStruct>::value_type(pMountStruct.Star,pMountStruct));
		pMount = pMount->NextSiblingElement();
	}
	return true;
}
MountMoveStatStruct* MountMoveStarConfig::GetConfigStruct(unsigned int Star)
{
	if(m_ConfigMap.count(Star) == 1)
		return &m_ConfigMap[Star];
	else
		return NULL;
}