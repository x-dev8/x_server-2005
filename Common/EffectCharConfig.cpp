#include "EffectCharConfig.h"
#include "tstring.h"
#include "RapidXml/MeRapidXml.h"

bool EffectCharConfig::LoadEffectCharConfig(const char* szFile)
{
 	if (szFile == NULL || *szFile == 0)
 	{ return false;	}

	m_EffectCharConfigVec.clear();

 	MeXmlDocument xMeXml;
 	if (!xMeXml.LoadFile( szFile ))
 	{ return false; }
 
 	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
 	if (pRoot == NULL )
 	{ return false; }

 	//  ¼ÓÔØ´ò¿×ÅäÖÃ
 	MeXmlElement* EffectCharConfigs = pRoot->FirstChildElement("EffectCharConfigs");
 	if (EffectCharConfigs == NULL) 
 	{ return false; }
 
 	int iValue;
 
 	MeXmlElement* _EffectCharConfig = EffectCharConfigs->FirstChildElement("EffectCharConfig");
 	while (_EffectCharConfig != NULL)
 	{	
 		EFFECTCHARCONFIG _config;
 
 		_EffectCharConfig->Attribute("skillID", &iValue);
 		_config.SkillID = iValue;
 
 		_EffectCharConfig->Attribute("movespeed", &iValue);
 		_config.moveSpeed = iValue;
 
 		_EffectCharConfig->Attribute("summoncnt", &iValue);
 		_config.SummonCnt = iValue;
 
 		_EffectCharConfig->Attribute("canbeattack", &iValue);
 		_config.bCanBeAttack = iValue;

		_EffectCharConfig->Attribute("onceattack", &iValue);
		_config.bOnceAttack = iValue;

		_EffectCharConfig->Attribute("aitype", &iValue);
		_config.AiType = (EFFECTCHAR_AI_TYPE)iValue;

		_EffectCharConfig->Attribute("modelid", &iValue);
		_config.ModelID = iValue;

		_EffectCharConfig->Attribute("waittime", &iValue);
		_config.WaitTime = iValue;

		_EffectCharConfig->Attribute("OnceFindTarget", &iValue);
		_config.bOnceFindeNearTarget = iValue;

		_EffectCharConfig->Attribute("OnDeadUseSkillID", &iValue);
		_config.OnDeadUseSkill = iValue;

		_EffectCharConfig->Attribute("OnDeadUseSkillLevel", &iValue);
		_config.OnDeadUseSkillLevel = iValue;

		_EffectCharConfig->Attribute("bAttackedDeadCnt", &iValue);
		_config.BeAttackDeadCnt = iValue;

		_EffectCharConfig->Attribute("SummonDistince", &iValue);
		_config.SummonDistince = iValue;

		

		

      //--------------------------------------------------------------
		m_EffectCharConfigVec.insert(std::make_pair(_config.SkillID,_config));
 	
 		_EffectCharConfig= _EffectCharConfig->NextSiblingElement();
	}

	return true;
}

bool EffectCharConfig::FindEffectCharConfigBySkillID(EFFECTCHARCONFIG &des ,int skillID) 
{
	if (skillID < 0)
		return false;

	MAP_EFFECTCHRCONFIG::iterator iter;
	if((iter = m_EffectCharConfigVec.find(skillID))== m_EffectCharConfigVec.end())
	    return false;
  
	des.AiType = iter->second.AiType;
	des.SkillID = iter->second.SkillID;
	des.moveSpeed = iter->second.moveSpeed;
	des.SummonCnt = iter->second.SummonCnt;
	des.bCanBeAttack = iter->second.bCanBeAttack;
	des.bOnceAttack = iter->second.bOnceAttack;
	des.ModelID = iter->second.ModelID;
	des.WaitTime = iter->second.WaitTime;
	des.bOnceFindeNearTarget = iter->second.bOnceFindeNearTarget;
	des.OnDeadUseSkill = iter->second.OnDeadUseSkill;
	des.OnDeadUseSkillLevel = iter->second.OnDeadUseSkillLevel;
	des.BeAttackDeadCnt = iter->second.BeAttackDeadCnt;
	des.SummonDistince = iter->second.SummonDistince;
	
    return true;
}
