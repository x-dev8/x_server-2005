#include "LevelExperienceConfig.h"
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"

#include "tstring.h"
#include "GlobalDef.h"

LevelExperienceConfig::LevelExperienceConfig()
{
    _characterLevelExperience.clear();

    //等级从1开始,先填入一个0等级
    LevelExperience xTemp;
    _characterLevelExperience.push_back(xTemp);
}

bool LevelExperienceConfig::AddCharacterLevelExperience(LevelExperience& xLevelExperience, bool bReplace /* = false */)
{
    LevelExperience* pLevelExperience = GetCharacterLevelExperienceByLevel(xLevelExperience.Level);
    if (pLevelExperience != NULL)
    {
        if (bReplace) { pLevelExperience->Experience = xLevelExperience.Experience; }

        return bReplace;        
    }

    _characterLevelExperience.push_back(xLevelExperience);

    return true;
}

bool LevelExperienceConfig::AddMountLevelExperience(LevelExperience& xLevelExperience, bool bReplace /*= false*/)
{
    LevelExperience* pLevelExperience = GetMountLevelExperienceByLevel(xLevelExperience.Level);
    if (pLevelExperience != NULL)
    {
        if (bReplace) { pLevelExperience->Experience = xLevelExperience.Experience; }
        return bReplace;        
    }
    _mountLevelExperience.push_back(xLevelExperience);
    return true;
}

bool LevelExperienceConfig::AddPetLevelExperience(LevelExperience& xLevelExperience, bool bReplace /*= false*/)
{
    LevelExperience* pLevelExperience = GetPetLevelExperienceByLevel(xLevelExperience.Level);
    if (pLevelExperience != NULL)
    {
        if (bReplace) { pLevelExperience->Experience = xLevelExperience.Experience; }
        return bReplace;        
    }
    _petLevelExperience.push_back(xLevelExperience);
    return true;
}

LevelExperienceConfig::LevelExperience* LevelExperienceConfig::GetCharacterLevelExperienceByLevel(unsigned short nLevel)
{
    if (nLevel < MinLevel || nLevel >= CharacterLevelExperienceCount()) { return NULL; }

    return &_characterLevelExperience[nLevel];
}

LevelExperienceConfig::LevelExperience* LevelExperienceConfig::GetCharacterLevelExperienceByExperience(unsigned long nExperience)
{
    leiter iter = _characterLevelExperience.begin() + 1;
    leiter end = _characterLevelExperience.end();

    for ( ; iter != end; ++iter)
    {
        if (iter->Experience == nExperience) { return &(*iter); }
    }
    
    return NULL;
}

LevelExperienceConfig::LevelExperience* LevelExperienceConfig::GetMountLevelExperienceByLevel(unsigned short nLevel)
{
    if (nLevel < MinLevel || nLevel >= MountLevelExperienceCount()) { return NULL; }

    return &_mountLevelExperience[nLevel];
}

LevelExperienceConfig::LevelExperience* LevelExperienceConfig::GetMountLevelExperienceByExperience(unsigned long nExperience)
{
    leiter iter = _mountLevelExperience.begin() + 1;
    leiter end = _mountLevelExperience.end();

    for ( ; iter != end; ++iter)
    {
        if (iter->Experience == nExperience) { return &(*iter); }
    }
    
    return NULL;
}

LevelExperienceConfig::LevelExperience* LevelExperienceConfig::GetPetLevelExperienceByLevel(unsigned short nLevel)
{
    if (nLevel < MinLevel || nLevel >= PetLevelExperienceCount()) { return NULL; }

    return &_petLevelExperience[nLevel];
}

LevelExperienceConfig::LevelExperience* LevelExperienceConfig::GetPetLevelExperienceByExperience(unsigned long nExperience)
{
    leiter iter = _petLevelExperience.begin() + 1;
    leiter end = _petLevelExperience.end();

    for ( ; iter != end; ++iter)
    {
        if (iter->Experience == nExperience) { return &(*iter); }
    }

    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
#define Root_Key                   "Project"
#define Name_Key                   "Name"
#define Version_Key                "Version"
#define LevelExperiences_Key       "LevelExperiences"
#define Mount_LevelExperiences_Key "MountLevelExperiences"
#define Pet_LevelExperiences_Key   "PetLevelExperiences"
#define LevelExperience_Key        "LevelExperience"
#define Level_Key                  "Level"
#define Experience_Key             "Experience"
//////////////////////////////////////////////////////////////////////////////

bool LevelExperienceConfig::LoadLevelExperienceConfig(const char* szFile)
{
    if (szFile == NULL || *szFile == NULL) { return false; }

    _characterLevelExperience.clear();

    //等级从1开始,先填入一个0等级
    LevelExperience xTemp;
    _characterLevelExperience.push_back(xTemp);
    _mountLevelExperience.push_back(xTemp);
    _petLevelExperience.push_back(xTemp);

    MeXmlDocument xMeXml;
    if (!xMeXml.LoadFile(szFile, 1)) { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement(Root_Key);
    if (pRoot == NULL ) { return false; }

    { // 人物经验
        MeXmlElement* pLevelExperiences = pRoot->FirstChildElement(LevelExperiences_Key);
        if (pLevelExperiences == NULL) { return false; }

        MeXmlElement* pLevelExperience = pLevelExperiences->FirstChildElement(LevelExperience_Key);
        while (pLevelExperience != NULL)
        {    
            LevelExperience xLevelExperience;

            //level
            int nLevel;
            if (pLevelExperience->Attribute(Level_Key, &nLevel) == NULL || nLevel < MinLevel || nLevel > MAX_LEVEL_LIMIT ) { return false; }
            xLevelExperience.Level = nLevel;

            //experience  32位太小了，改成64
            /*int nExperience;
            if (pLevelExperience->Attribute(Experience_Key, &nExperience) == NULL || nExperience <= 0 ) { return false; }
            xLevelExperience.Experience = nExperience;*/

			int64 nExperience;
			Common::_tstring strExperience;
			strExperience.fromUTF8(pLevelExperience->Attribute(Experience_Key));
			if (strExperience.c_str())
			{
				nExperience = _atoi64(strExperience.c_str());
				if (nExperience<=0)
				{
					return false;
				}
				xLevelExperience.Experience = nExperience;
			}
			else
			{
				return false;
			}

            if (!AddCharacterLevelExperience(xLevelExperience)) { return false; }

            //next
            pLevelExperience = pLevelExperience->NextSiblingElement();
        }
    }

    { // 坐骑经验
        MeXmlElement* pLevelExperiences = pRoot->FirstChildElement(Mount_LevelExperiences_Key);
        if (pLevelExperiences == NULL) { return false; }

        MeXmlElement* pLevelExperience = pLevelExperiences->FirstChildElement(LevelExperience_Key);
        while (pLevelExperience != NULL)
        {    
            LevelExperience xLevelExperience;

            //level
            int nLevel;
            if (pLevelExperience->Attribute(Level_Key, &nLevel) == NULL || nLevel < MinLevel || nLevel > MAX_LEVEL_LIMIT ) { return false; }
            xLevelExperience.Level = nLevel;

            //experience
            int nExperience;
            if (pLevelExperience->Attribute(Experience_Key, &nExperience) == NULL || nExperience <= 0 ) { return false; }
            xLevelExperience.Experience = nExperience;

            if (!AddMountLevelExperience(xLevelExperience)) { return false; }

            //next
            pLevelExperience = pLevelExperience->NextSiblingElement();
        }
    }

    { // 宠物经验
        MeXmlElement* pLevelExperiences = pRoot->FirstChildElement(Pet_LevelExperiences_Key);
        if (pLevelExperiences == NULL) { return false; }

        MeXmlElement* pLevelExperience = pLevelExperiences->FirstChildElement(LevelExperience_Key);
        while (pLevelExperience != NULL)
        {    
            LevelExperience xLevelExperience;

            //level
            int nLevel;
            if (pLevelExperience->Attribute(Level_Key, &nLevel) == NULL || nLevel < MinLevel || nLevel > MAX_LEVEL_LIMIT ) { return false; }
            xLevelExperience.Level = nLevel;

            //experience
            int nExperience;
            if (pLevelExperience->Attribute(Experience_Key, &nExperience) == NULL || nExperience <= 0 ) { return false; }
            xLevelExperience.Experience = nExperience;

            if (!AddPetLevelExperience(xLevelExperience)) { return false; }

            //next
            pLevelExperience = pLevelExperience->NextSiblingElement();
        }
    }

    return true;
}

bool LevelExperienceConfig::SaveLevelExperienceConfig(const char *szFile)
{
    if (szFile == NULL || *szFile == 0) { return false;    }

    MeXmlDocument xMeXmlDoc;
    xMeXmlDoc.InsertEndChild(MeXmlDeclaration("1.0","UTF-8","yes"));

    MeXmlElement* pRoot = xMeXmlDoc.InsertEndChild((Root_Key))->ToElement();
    if (pRoot == NULL) { return false; }

    Common::_tstring strName = "HeroOnline";
    pRoot->SetAttribute(Name_Key, strName.toUTF8().c_str());
    pRoot->SetAttribute(Version_Key, "");     

    MeXmlElement* pLevelExperiences = pRoot->InsertEndChild((LevelExperiences_Key))->ToElement();
    if(pLevelExperiences == NULL) { return false; }

    leiter iter = _characterLevelExperience.begin() + 1; //保存时候不保存0等级
    leiter end = _characterLevelExperience.end();
    for (; iter != end; ++iter)
    {
        MeXmlElement* pLevelExperience = pLevelExperiences->InsertEndChild((LevelExperience_Key))->ToElement();
        if (pLevelExperience == NULL) { return false; }

        pLevelExperience->SetAttribute(Level_Key, iter->Level);    
        pLevelExperience->SetAttribute(Experience_Key, iter->Experience);        
    }

    return xMeXmlDoc.SaveFile(szFile);
}