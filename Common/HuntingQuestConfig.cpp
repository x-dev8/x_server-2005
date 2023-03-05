#include "HuntingQuestConfig.h"
#include "RapidXml/MeRapidXml.h"
#include "ItemDetail.h"
#include "QuestManager.h"
#include "QuestDefine.h"

HuntingQuestConfig::HuntingQuestConfig()
{
	nReFreshGold = 0;
	nReFreshMoney = 0;
	nReFreshTime = 0;
	fProbability = 0.0f;
}

HuntingQuestConfig::~HuntingQuestConfig()
{
	vecBase.clear();
	vecType.clear();
	mapLevel.clear();

	vecGoldType.clear();
	mapGoldLevel.clear();

	vecAllQuest.clear();

	vecLevelGoldQuest.clear();
	vecLevelTypeQuest.clear();
}

bool HuntingQuestConfig::LoadHuntingQuestConfig( const char* pszConfig )
{
	if (!pszConfig || *pszConfig == 0)
		return false;

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(pszConfig))
		return false;
	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (!pRoot)
		return false;

	MeXmlElement* pReFresh = pRoot->FirstChildElement("ReFresh");
	if (!pReFresh)
		return false;

	pReFresh->Attribute("Gold", &nReFreshGold);
	pReFresh->Attribute("Money", &nReFreshMoney);
	pReFresh->Attribute("Time", &nReFreshTime);

	MeXmlElement* pQuests = pRoot->FirstChildElement("Quests");
	if ( !pQuests )
		return false;

	pQuests->Attribute("Probability", &fProbability);

	MeXmlElement* pLevel = pQuests->FirstChildElement("Level");
	while ( pLevel )
	{
		int nNeenLevel = 0;
		pLevel->Attribute("NeedLevel", &nNeenLevel);

		TypeVec vecTV;
		GoldTypeVec vecGTV;

		MeXmlElement* pTypes = pLevel->FirstChildElement("Types");
		while ( pTypes )
		{
			int nType = 0;
			pTypes->Attribute("Type", &nType);

			BaseVec vecBT;

			MeXmlElement* pQuest = pTypes->FirstChildElement("Quest");
			while ( pQuest )
			{
				SData data;

				if ( !pQuest->Attribute("ID", &data.nId) )
					return false;
				if ( !theQuestManager.IsQuestIdValid( data.nId ) )
					return false;
				//判断是否已经存在
				if ( GetBaseDataById( data.nId ) )
					return false;

				pQuest->Attribute("Quality", &data.nQuality);
				pQuest->Attribute("AdviseLevel", &data.nAdviseLevel);

				if ( data.nQuality != ItemDefine::EQL_Orange )
				{
					vecBT.push_back( data );
					vecBase.push_back( data );
				}
				else
				{
					vecGTV.push_back( data );
					vecGoldType.push_back( data );
				}

				vecAllQuest.push_back( data );

				pQuest = pQuest->NextSiblingElement();
			}

			vecTV.push_back( vecBT );
			vecType.push_back( vecBT );

			pTypes = pTypes->NextSiblingElement();
		}

		LevelMap::iterator iter = mapLevel.find( nNeenLevel );
		if ( iter == mapLevel.end() )
			mapLevel.insert( std::make_pair( nNeenLevel, vecTV ) );

		GoldLevelMap::iterator iter1 = mapGoldLevel.find( nNeenLevel );
		if ( iter1 == mapGoldLevel.end() )
			mapGoldLevel.insert( std::make_pair( nNeenLevel, vecGTV ) );

		pLevel = pLevel->NextSiblingElement();
	}

	return true;
}

HuntingQuestConfig::BaseVec& HuntingQuestConfig::GetLevelGoldQuest( int level, int Country )
{
	vecLevelGoldQuest.clear();

	GoldLevelMap::iterator iter = mapGoldLevel.begin();
	for ( ; iter != mapGoldLevel.end(); iter++ )
	{
		if ( iter->first <= level )
		{
			GoldTypeVec::iterator it;
			for ( it = iter->second.begin(); it != iter->second.end(); it++ )
			{
				SQuest * pQuest = theQuestManager.GetQuest((*it).nId );
				if(!pQuest || (pQuest->Country !=0 &&  pQuest->Country != Country) )
					continue;

				vecLevelGoldQuest.push_back( *it );
			}
		}
	}

	return vecLevelGoldQuest;
}

HuntingQuestConfig::TypeVec& HuntingQuestConfig::GetLevelTypeQuest( int level, int Country )
{
	for ( TypeVec::iterator iter = vecLevelTypeQuest.begin(); iter != vecLevelTypeQuest.end(); iter++ )
	{
		(*iter).clear();
	}
	vecLevelTypeQuest.clear();

	TypeVec vecTypeQuest;
	vecTypeQuest.clear();

	LevelMap::iterator iter = mapLevel.begin();
	for ( ; iter != mapLevel.end(); iter++ )
	{
		if ( iter->first <= level )
		{
			TypeVec::iterator it;
			for ( it = iter->second.begin(); it != iter->second.end(); it++ )
			{
				//vecLevelTypeQuest.push_back( *it );
				vecTypeQuest.push_back( *it );
			}
		}
	}

	vecLevelTypeQuest.resize( vecTypeQuest.size() );
	int i = 0;
	for ( TypeVec::iterator iter = vecTypeQuest.begin(); iter != vecTypeQuest.end() && i < vecLevelTypeQuest.size(); iter++, i++ )
	{
		for ( BaseVec::iterator it = (*iter).begin(); it != (*iter).end(); it++ )
		{
			SQuest * pQuest = theQuestManager.GetQuest((*it).nId );
			if(!pQuest || (pQuest->Country !=0 &&  pQuest->Country != Country) )
				continue;
			vecLevelTypeQuest[i].push_back( *it );
		}
	}

	return vecLevelTypeQuest;
}

HuntingQuestConfig::SData* HuntingQuestConfig::GetBaseDataById( int nId )
{
	for ( BaseVec::iterator it = vecAllQuest.begin(); it != vecAllQuest.end(); it++ )
	{
		if ( (*it).nId == nId )
			return &(*it);
	}

	return NULL;
}