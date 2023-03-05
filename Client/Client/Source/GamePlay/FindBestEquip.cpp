#include "FindBestEquip.h"
#include "tstring.h"

FindBestEquip::FindBestEquip()
{

}

bool	FindBestEquip::LoadXml()
{
	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile( "..\\Data\\Config\\FindBestEquit.config" ) )
	{
		return false;
	}

	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (!pRoot)
	{
		return false;
	}

	MeXmlElement* pLevelType = pRoot->FirstChildElement("LevelType");

	int realCount = 0;

	if ( pLevelType )
	{
		// 读等级区域表
		MeXmlElement* pLevelId = pLevelType->FirstChildElement("LevelId");

		while( pLevelId )
		{
			int LevelId = -1;
			pLevelId->Attribute( "Id", &LevelId );


			LevelArea temp;

			pLevelId->Attribute( "MinLevel", &temp.mMinLevel );
			pLevelId->Attribute( "MaxLevel", &temp.mMaxLevel );

			mLevelArea.push_back( temp );

			// 这两表的长度一样，提前压入
			BestEquipSet_t bestEquipTemp;
			mBestEquipSet.push_back( bestEquipTemp );

			++realCount;

			pLevelId = pLevelId->NextSiblingElement();
		}
	}

	// 读装备表
	MeXmlElement* pAllBestEquip = pRoot->FirstChildElement("AllBestEquip");

	if ( pAllBestEquip )
	{
		MeXmlElement* pLevelId = pAllBestEquip->FirstChildElement("LevelId");
		while ( pLevelId )
		{
			int LevelId = -1;
			pLevelId->Attribute( "Id", &LevelId );

			if ( LevelId <= AREA_INVALID || LevelId >= realCount )
			{
				return false;
			}

			MeXmlElement* pBestEquip = pLevelId->FirstChildElement("BestEquip");

			while ( pBestEquip )
			{
				int equipId = -1;
				pBestEquip->Attribute( "EquipId", &equipId );
				
				BestEquip temp;
				pBestEquip->Attribute( "Career", &temp.mCareer );
				pBestEquip->Attribute( "Part", &temp.mPart );

				mBestEquipSet[LevelId].insert( BestEquipIt_t::value_type( equipId, temp ) );

				pBestEquip = pBestEquip->NextSiblingElement();
			}

			pLevelId = pLevelId->NextSiblingElement();
		}
	}

	// 读装备说明表
	MeXmlElement* pAllEquipInfo = pRoot->FirstChildElement("AllEquipInfo");

	if ( pAllEquipInfo )
	{
		MeXmlElement* pEquipInfo = pAllEquipInfo->FirstChildElement("EquipInfo");

		while ( pEquipInfo )
		{
			int EquipId = -1;
			pEquipInfo->Attribute( "EquipId", &EquipId );

			MeXmlElement* pInfo = pEquipInfo->FirstChildElement("Info");

			EquipInfo Info;
			for ( int idx = 0; pInfo && idx < MAX_INFOCOUNT; ++idx )
			{
				const char* pValue = pInfo->Attribute("Value");
				if ( NULL != pValue )
				{
					Info.mAllInfo[idx] = Common::_tstring::toNarrowString( Common::_tstring::UTF8towcs( pValue ).c_str() );
				}

				pInfo = pInfo->NextSiblingElement(); 
			}
			
			if ( mEquipInfoSet.count( EquipId ) == 0 )
			{
				mEquipInfoSet.insert( EquipInfoIt_t::value_type( EquipId, Info ) );
			}

			pEquipInfo = pEquipInfo->NextSiblingElement();
		}
	}

	return true;
}

int FindBestEquip::FindLevelAreaType( int level ) const
{
	int maxCount = mLevelArea.size();

	for ( int idx = 0; idx < maxCount; ++idx )
	{
		if ( level >= mLevelArea[idx].mMinLevel && level <= mLevelArea[idx].mMaxLevel )
		{
			return idx;
		}
	}

	return AREA_INVALID;
}

int FindBestEquip::FindEquipInfo( EArmType CareerId, EEquipPartType PartId, int level, EquipInfo& Data ) const
{
	// 找等级区域
	int areaType = FindLevelAreaType( level );

	if ( areaType <= AREA_INVALID )
	{
		return -1;
	}

	// 通过区域，部件，职业找装备ID
	BestEquipIt_t It		= mBestEquipSet[areaType].begin();
	BestEquipIt_t ItEnd		= mBestEquipSet[areaType].end();

	int Key = -1;

	for ( ; It != ItEnd; ++It )
	{
		if ( It->second.mCareer == CareerId && It->second.mPart == PartId )
		{
			Key = It->first;
			break;
		}
	}

	if ( Key == -1 )
	{
		return -1;
	}

	// 通过装备ID，找出说明
	EquipInfoIt_t InfoIt		= mEquipInfoSet.find( Key );
	EquipInfoIt_t InfoItEnd		= mEquipInfoSet.end();
	if ( InfoIt == InfoItEnd )
	{
		return -1;
	}

	Data = InfoIt->second;

	return Key;

}

