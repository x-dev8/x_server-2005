#include "PetDefineConfig.h"
#include "RapidXml/MeRapidXml.h"
PetDefineConfig::PetDefineConfig()
{

}
PetDefineConfig::~PetDefineConfig()
{

}
bool PetDefineConfig::LoadFileConfigPath(const char * FilePath)
{
	MeXmlDocument mKwameXmlDoc;
	if (!mKwameXmlDoc.LoadFile(FilePath)) return false;
	MeXmlElement* pPet = mKwameXmlDoc.FirstChildElement("Pet");
	if(pPet == NULL)
		return false;
	//获取属性
	if (pPet->Attribute("Time",&TimeStep) == NULL)
		return false;

	if (pPet->Attribute("Exp",&TimeExp) == NULL)
		return false;

	if (pPet->Attribute("AttChangeMinLevel",&MinAttChangeLevel) == NULL)
		return false;

	if (pPet->Attribute("MaxLevel",&MaxLevel) == NULL)
		return false;
	//获取副将技能的配置
	MeXmlElement* pSkill = pPet->FirstChildElement("Skill");
	while(pSkill != NULL)
	{
		int Level = 0;
		int SkillSum = 0;
		if (pSkill->Attribute("Level",&Level) == NULL)
		{
			pSkill = pSkill->NextSiblingElement("Skill");
			continue;
		}
		if (pSkill->Attribute("SkillSum",&SkillSum) == NULL)
		{
			pSkill = pSkill->NextSiblingElement("Skill");
			continue;
		}
		PetSKillSum.insert(std::map<int,int>::value_type(Level,SkillSum));
		pSkill = pSkill->NextSiblingElement("Skill");
	}
	return true;
}
bool PetDefineConfig::IsNeedChangeSkillSum(int Level)
{
	if(PetSKillSum.count(Level) != 1)
		return false;
	else
		return true;
}
int PetDefineConfig::GetLevelSkillSum(int Level)
{
	//根据等级获取技能的数量
	// >= Level
	while(PetSKillSum.count(Level) != 1 && Level>0)
	{
		--Level;
	}
	return PetSKillSum[Level];
}