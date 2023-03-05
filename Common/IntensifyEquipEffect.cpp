#include "IntensifyEquipEffect.h"
#include "tstring.h"
#include "RapidXml/MeRapidXml.h"

//EquipIntensifyEffect.config

bool EquipEffectSort(EQUIPINTENSIFY_INFO one, EQUIPINTENSIFY_INFO two)
{
   return one.MinIntensifyLev >= two.MinIntensifyLev;
}

bool IntensifyEquip::LoadIntensifyEffectConfig(const char *szFile)
{
 	if (szFile == NULL || *szFile == 0)
 	{ return false;	}

	m_WeaponEffectMgr.clear();
	m_EquipEffectMgr.clear();

 	MeXmlDocument xMeXml;
 	if (!xMeXml.LoadFile( szFile ))
 	{ return false; }
 
 	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
 	if (pRoot == NULL )
 	{ return false; }

	{
 	//  加载武器强化配置
 	MeXmlElement* EffectCharConfigs = pRoot->FirstChildElement("WeaponIntensifyEffects");
 	if (EffectCharConfigs == NULL) 
 	{ return false; }
 
 	int iValue;
 
 	MeXmlElement* _EffectCharConfig = EffectCharConfigs->FirstChildElement("WeaponIntensify");
 	while (_EffectCharConfig != NULL)
 	{	
 		WEAPONINTENSIFY_INFO _config;
 
 		_EffectCharConfig->Attribute("WeaponIDMin", &iValue);
 		_config.MinWeapoinID = iValue;
 
 		_EffectCharConfig->Attribute("WeaponIDMax", &iValue);
 		_config.MaxWeapoinID = iValue;
 
 		_EffectCharConfig->Attribute("WeaponIntensifyLevMin", &iValue);
 		_config.MinIntensifyLev = iValue;
 
 		_EffectCharConfig->Attribute("WeaponIntensifyLevMax", &iValue);
 		_config.MaxIntensifyLev = iValue;

		_EffectCharConfig->Attribute("EffectId", &iValue);
		_config.EffectID = iValue;

		m_WeaponEffectMgr.push_back(_config);

 		_EffectCharConfig= _EffectCharConfig->NextSiblingElement();
	}
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{

	//  加载装备强化配置
	MeXmlElement* EffectCharConfigs = pRoot->FirstChildElement("EquipIntensifyEffects");
	if (EffectCharConfigs == NULL) 
	{ return false; }

	int iValue;

	MeXmlElement* _EffectCharConfig = EffectCharConfigs->FirstChildElement("EquipIntensify");
	while (_EffectCharConfig != NULL)
	{	
		EQUIPINTENSIFY_INFO _config;

		_EffectCharConfig->Attribute("IntensifyMin", &iValue);
		_config.MinIntensifyLev = iValue;
		_config.EffectPath = _EffectCharConfig->Attribute("path");
		m_EquipEffectMgr.push_back(_config);

		_EffectCharConfig= _EffectCharConfig->NextSiblingElement();
	}
   }

	std::sort(m_EquipEffectMgr.begin(),m_EquipEffectMgr.end(),EquipEffectSort);


	return true;
}


bool IntensifyEquip::FindWeaponEffectID(int &des_EffectID ,int weaponId , int weapon_IntensifyLev)
{
	 if (m_WeaponEffectMgr.size() <= 0 ) return false;	
     if( weaponId <= 0 )   return false;
	 if(weapon_IntensifyLev <=  0) return false;

	for (int i = 0 ; i < m_WeaponEffectMgr.size() ; i++)
	{
		if (weaponId <= m_WeaponEffectMgr[i].MaxWeapoinID &&  //id区间正确
			weaponId >= m_WeaponEffectMgr[i].MinWeapoinID &&
			weapon_IntensifyLev <= m_WeaponEffectMgr[i].MaxIntensifyLev && //强化等级区间正确
			weapon_IntensifyLev >= m_WeaponEffectMgr[i].MinIntensifyLev)
		{		
		   des_EffectID = m_WeaponEffectMgr[i].EffectID;
	       return true;
		}
	}

   return false;

}

std::string IntensifyEquip::GetEquipIntensifyModelPath(int LowIntensify)
{
	std::string EffectPath = "NULL";
	if(m_EquipEffectMgr.size() <= 0) return EffectPath;

	for (int i = 0 ; i < m_EquipEffectMgr.size() ; i++)
	{
		if (LowIntensify >= m_EquipEffectMgr[i].MinIntensifyLev )
		{

			return m_EquipEffectMgr[i].EffectPath;
		}
	}
	return EffectPath;
}

