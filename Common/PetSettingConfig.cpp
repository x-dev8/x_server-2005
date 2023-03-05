#include "PetSettingConfig.h"
#include "tstring.h"
#include "RapidXml/MeRapidXml.h"
#include "application_config.h"

PetSettingConfig::PetSettingConfig()
{
    vecPetCarry.clear();
    memset(_AptitudeTable, 0, sizeof(int)   * EPetQuality_Count * EPetAptitude_LevelMax);
    memset(_AptitudeFloat, 0, sizeof(float) * EPetAptitude_FloatCount);

    memset(_FightAttrBaseAttrParam,  0, sizeof(int) * CharAttr_AttributMaxCount);
    memset(_FightAttrLevelParam,     0, sizeof(int) * CharAttr_AttributMaxCount);

    memset(_PetDeathDropLoyalty,     0, sizeof(int) * const_iCharMaxLevel      );
    memset(_PetDeathDropDuration,    0, sizeof(int) * const_iCharMaxLevel      );
}

PetSettingConfig::~PetSettingConfig()
{
    vecPetCarry.clear()      ;
    vecSkillRepalce.clear()  ;
    vecAptitudeStar.clear()  ;
    vecBreedNum.clear()      ;
    vecBreedCost.clear()     ;
    vecBoneRate.clear()      ;
    vecTitle.clear()         ;
    vecSavvyUp.clear()       ;
    vecSavvyReduce.clear()   ;

    vecSkillCatchRate.clear()    ;
    vecHPCatchRate.clear()       ;
}

int PetSettingConfig::GetBaseAttrCount()
{
    return _BaseAttrCount;
}

int PetSettingConfig::GetBaseAttrValue()
{
    return _BaseAttrValue;
}

uint32 PetSettingConfig::GetRefreshLoyaltyTime()
{
    return _RefreshLoyaltyTime;
}

uint32 PetSettingConfig::GetRefreshDurationTime()
{
    return _RefreshDurationTime;
}

int  PetSettingConfig::GetPlayerPetLimit( int level )
{
    if ( level <= 0 )
    { return 0; }

    std::vector<SPetCarry>::iterator iter = vecPetCarry.begin();
    for ( ; iter != vecPetCarry.end(); ++iter )
    {
        if (iter->nBeginLevel <= level && iter->nEndLevel >= level)
        { return iter->nNumber; }
    }

    return 0;
}

int  PetSettingConfig::GetAptitudeLevel ( int quality )
{
    if ( quality >= EPetQuality_Count )
    { return 0; }

    return GetRandIndex( _AptitudeTable[quality], 10, theRand.rand32() % RAND_THOUSAND ) + 1;
}

float  PetSettingConfig::GetAptitudeFloat ( int aptitudeLevel )
{
    if ( aptitudeLevel >= EPetAptitude_FloatCount )
    { return 0.0f; }

    return GetRand(_AptitudeFloat[aptitudeLevel-1], _AptitudeFloat[aptitudeLevel]);
}

int  PetSettingConfig::GetGrowRateStar ( int quality )
{
    if ( quality >= EPetQuality_Count )
    { return 0; }

    return GetRandIndex( _GrowRateTable[quality], 10, theRand.rand32() % RAND_THOUSAND ) + 1;
}

int  PetSettingConfig::GetFightAttrBaseAttrParam ( int charAttr )
{
    if ( charAttr >= CharAttr_AttributMaxCount )
    { return 0; }

    return _FightAttrBaseAttrParam[charAttr];
}

int  PetSettingConfig::GetFightAttrLevelParam ( int charAttr )
{
    if ( charAttr >= CharAttr_AttributMaxCount )
    { return 0; }

    return _FightAttrLevelParam[charAttr];
}

int  PetSettingConfig::GetSavvyAddAptitudePer( int savvy )
{
    if ( savvy <= 0 || savvy > EPetSavvy_LevelMax )
    { return 0; }
    
    return _SavvyAddAptitudePer[savvy - 1];
}

int  PetSettingConfig::GetSavvyAddTakeLevel( int savvy )
{
    if ( savvy <= 0 || savvy > EPetSavvy_LevelMax )
    { return 0; }

    return _SavvyAddTakeLevel[savvy - 1];
}

bool PetSettingConfig::IsSkillRepalce( bool bIsManualSkill, int skillNum, int manualNum, int autoNum )
{
    std::vector<SSkillRepalce>::iterator iter = vecSkillRepalce.begin();
    for ( ; iter != vecSkillRepalce.end(); ++iter )
    {
        if ( skillNum  != iter->skillNum )
        { continue; }

        if ( manualNum != iter->manualNum )
        { continue; }

        if ( autoNum   != iter->autoNum )
        { continue; }

        int nRandom = theRand.rand32() % PET_SKILL_REPALCE_PROBABILITY;

        if (bIsManualSkill)
        {
            if ( nRandom < iter->manualRate  )
            { return false; }
        }
        else
        {
            if ( nRandom < iter->autoRate  )
            { return false; }
        }
        
    }

    return true;
}

int PetSettingConfig::GetAptitudeStar ( int aptitudeValue )
{
    std::vector<SAptitudeStar>::iterator iter = vecAptitudeStar.begin();
    for ( ; iter != vecAptitudeStar.end(); ++iter )
    {
        if ( aptitudeValue >= iter->nLowValue && aptitudeValue <= iter->nHighValue )
        {
            return iter->nStarLevel;
        }
    }

    return 0;
}

int PetSettingConfig::GetPetBreedNum ( int petLevel )
{
    if ( petLevel <= 0 )
    { return 0; }

    std::vector<SBreedNum>::iterator iter = vecBreedNum.begin();
    for ( ; iter != vecBreedNum.end(); ++iter )
    {
        if (iter->nBeginLevel <= petLevel && iter->nEndLevel >= petLevel)
        { return iter->nNumber; }
    }

    return 0;
}

int PetSettingConfig::GetPetBreedMoney ( int quality, int catchLevel )
{
    std::vector<SBreedMoney>::iterator iter = vecBreedCost.begin();
    for ( ; iter != vecBreedCost.end(); ++iter )
    {
        if ( iter->nCatchQuality == quality && iter->nCatchLevel == catchLevel )
        { return iter->nMoney; }
    }

    return 0;
}

int PetSettingConfig::GetPetBone ( int quality, int catchLevel )
{
    std::vector<SBoneRate>::iterator iter = vecBoneRate.begin();
    for ( ; iter != vecBoneRate.end(); ++iter )
    {
        if ( iter->nCatchQuality == quality && iter->nCatchLevel == catchLevel )
        { return GetRandIndex( iter->nBoneRate, 11, theRand.rand32() % RAND_THOUSAND ); }
    }

    return 0;
}

int PetSettingConfig::GetPetDeathDropLoyalty ( int petLevel )
{
    if ( petLevel < 0 || petLevel >= const_iCharMaxLevel  )
    { return 0; }

    return _PetDeathDropLoyalty[ petLevel ];
}

int PetSettingConfig::GetPetDeathDropDuration ( int petLevel )
{
    if ( petLevel < 0 || petLevel >= const_iCharMaxLevel  )
    { return 0; }

    return _PetDeathDropDuration[ petLevel ];
}

int PetSettingConfig::GetCharacterizeAutoSkillPer ( int autoSkillType, int characterize )
{
    if ( autoSkillType < 0 || autoSkillType >= EPetSkillCategory_MaxSize  )
    { return 0; }

    if ( characterize < 0 || characterize >= EPetChar_Count  )
    { return 0; }

    return _CharacterizeTable[ autoSkillType ][ characterize ];
}

int PetSettingConfig::GetSavvyUpItemRate ( int quality, int catchLevel, int savvy )
{
    std::vector<SSavvyUp>::iterator iter = vecSavvyUp.begin();
    for ( ; iter != vecSavvyUp.end(); ++iter )
    {
        if ( iter->nCatchQuality == quality && iter->nCatchLevel == catchLevel && iter->nSavvy == savvy )
        { return  iter->nItemRate; }
    }

    return 0;
}

int PetSettingConfig::GetSavvyUpEatRate ( int quality, int catchLevel, int savvy )
{
    std::vector<SSavvyUp>::iterator iter = vecSavvyUp.begin();
    for ( ; iter != vecSavvyUp.end(); ++iter )
    {
        if ( iter->nCatchQuality == quality && iter->nCatchLevel == catchLevel && iter->nSavvy == savvy )
        { return  iter->nEatRate; }
    }

    return 0;
}

int PetSettingConfig::GetSavvyUpItemMoney ( int quality, int catchLevel, int savvy )
{
    std::vector<SSavvyUp>::iterator iter = vecSavvyUp.begin();
    for ( ; iter != vecSavvyUp.end(); ++iter )
    {
        if ( iter->nCatchQuality == quality && iter->nCatchLevel == catchLevel && iter->nSavvy == savvy )
        { return iter->nItemCostMoney; }
    }

    return 0;
}

int PetSettingConfig::GetSavvyUpEatMoney ( int quality, int catchLevel, int savvy )
{
    std::vector<SSavvyUp>::iterator iter = vecSavvyUp.begin();
    for ( ; iter != vecSavvyUp.end(); ++iter )
    {
        if ( iter->nCatchQuality == quality && iter->nCatchLevel == catchLevel && iter->nSavvy == savvy )
        { return iter->nEatCostMoney; }
    }

    return 0;
}

int PetSettingConfig::GetReduceSavvy ( int savvy )
{
    std::vector<SSavvyReduce>::iterator iter = vecSavvyReduce.begin();
    for ( ; iter != vecSavvyReduce.end(); ++iter )
    {
        if ( iter->nSavvy == savvy )
        { 
            int index = GetRandIndex( iter->nRate, ESavvyReduce_NumMax, theRand.rand16() % RAND_NUM );
            return iter->nReduce[index];
        }
    }

    return 0;
}

int PetSettingConfig::GetSkillCatchRate( int catchLevel, int skillLevel )
{
    std::vector<SSkillCatchRate>::iterator iter = vecSkillCatchRate.begin();
    for ( ; iter != vecSkillCatchRate.end(); ++iter )
    {
        if ( iter->nCatchLevel == catchLevel && iter->nSkillLevel == catchLevel )
        { return iter->nAddRate; }
    }

    return 0;
}

int PetSettingConfig::GetHPCatchRate   ( int hpPer )
{
    std::vector<SHPCatchRate>::iterator iter = vecHPCatchRate.begin();
    for ( ; iter != vecHPCatchRate.end(); ++iter )
    {
        if ( iter->nMaxHpPer >= hpPer && iter->nMinHpPer < hpPer )
        { return iter->nAddRate; }
    }

    return 0;
}

PetSettingConfig::STitle* PetSettingConfig::GetPetTitle( int savvy, int growStar, int aptitude )
{
    PetSettingConfig::STitle* pTitle = NULL;
    std::vector<STitle>::iterator iter = vecTitle.begin();
    for ( ; iter != vecTitle.end(); ++iter )
    {
        if ( iter->nSavvyLowValue != 0 && iter->nSavvyHighValue != 0 )
        {
            if ( iter->nSavvyLowValue > savvy || iter->nSavvyHighValue < savvy )
            { continue; }
        }

        if ( iter->nGrowStarLevel != 0 && iter->nGrowStarLevel != growStar )
        { continue; }

        if ( iter->nAptitudeLowValue != 0 && iter->nAptitudeHighValue != 0 )
        {
            if ( iter->nAptitudeLowValue > aptitude || iter->nAptitudeHighValue < aptitude )
            { continue; }
        }

        pTitle = &( *iter );
    }

    return pTitle;
}

bool PetSettingConfig::LoadPetSettingConfig(const char* szFile)
{
    if (szFile == NULL || *szFile == 0)
    { return false;	}

    MeXmlDocument xMeXml;
    if (!xMeXml.LoadFile(szFile, 1))
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
    if (pRoot == NULL )
    { return false; }

    MeXmlElement* pPetSetting = pRoot->FirstChildElement("PetSetting");
    if (pPetSetting == NULL) 
    { return false; }

    int     iValue = 0;
    double  dValue = 0.0;

    MeXmlElement* pPetAttr = pPetSetting->FirstChildElement("PetAttr");
    while (pPetAttr != NULL)
    {	
        pPetAttr->Attribute("BaseAttrCount", &iValue);
        _BaseAttrCount = iValue;

        pPetAttr->Attribute("BaseAttrValue", &iValue);
        _BaseAttrValue = iValue;

        pPetAttr->Attribute("RefreshLoyaltyTime", &iValue);
        _RefreshLoyaltyTime = iValue;

        pPetAttr->Attribute("RefreshDurationTime", &iValue);
        _RefreshDurationTime = iValue;

        pPetAttr = pPetAttr->NextSiblingElement("PetAttr");
    }

    //人物等级宠物携带数量
    MeXmlElement* pPetCarry = pPetSetting->FirstChildElement("PetCarry");
    while (pPetCarry != NULL)
    {	
        SPetCarry  xPetCarry;

        pPetCarry->Attribute("BeginLevel", &iValue);
        xPetCarry.nBeginLevel = iValue;

        pPetCarry->Attribute("EndLevel", &iValue);
        xPetCarry.nEndLevel = iValue;

        pPetCarry->Attribute("Number", &iValue);
        xPetCarry.nNumber = iValue;

        vecPetCarry.push_back(xPetCarry);

        pPetCarry = pPetCarry->NextSiblingElement("PetCarry");
    }

    //捕捉几率
    MeXmlElement* pCatchTable = pPetSetting->FirstChildElement("CatchTable");
    if (pCatchTable == NULL) 
    { return false; }

    MeXmlElement* pSkillCatchRate = pCatchTable->FirstChildElement("SkillCatchRate");
    while (pSkillCatchRate != NULL)
    {
        SSkillCatchRate xSkillCatchRate;

        pSkillCatchRate->Attribute("CatchLevel", &iValue);
        xSkillCatchRate.nCatchLevel = iValue;

        pSkillCatchRate->Attribute("SkillLevel", &iValue);
        xSkillCatchRate.nSkillLevel = iValue;

        pSkillCatchRate->Attribute("AddRate", &iValue);
        xSkillCatchRate.nAddRate = iValue;

        vecSkillCatchRate.push_back( xSkillCatchRate );

        pSkillCatchRate = pSkillCatchRate->NextSiblingElement("SkillCatchRate");
    }

    MeXmlElement* pHPCatchRate = pCatchTable->FirstChildElement("HPCatchRate");
    while (pHPCatchRate != NULL)
    {
        SHPCatchRate xHPCatchRate;

        pHPCatchRate->Attribute("MaxHpPer", &iValue);
        xHPCatchRate.nMaxHpPer = iValue;

        pHPCatchRate->Attribute("MinHpPer", &iValue);
        xHPCatchRate.nMinHpPer = iValue;

        pHPCatchRate->Attribute("AddRate", &iValue);
        xHPCatchRate.nAddRate = iValue;

        vecHPCatchRate.push_back( xHPCatchRate );

        pHPCatchRate = pHPCatchRate->NextSiblingElement("HPCatchRate");
    }

    //宠物技能
    MeXmlElement* pSkillTable = pPetSetting->FirstChildElement("SkillTable");
    if (pSkillTable == NULL) 
    { return false; }

    MeXmlElement* pSkillRepalce = pSkillTable->FirstChildElement("SkillRepalce");
    while (pSkillRepalce != NULL)
    {
        SSkillRepalce xRepalce;
        
        pSkillRepalce->Attribute("ID", &iValue);
        xRepalce.id = iValue;

        pSkillRepalce->Attribute("SkillNum", &iValue);
        xRepalce.skillNum = iValue;

        pSkillRepalce->Attribute("ManualNum", &iValue);
        xRepalce.manualNum = iValue;

        pSkillRepalce->Attribute("AutoNum", &iValue);
        xRepalce.autoNum = iValue;

        pSkillRepalce->Attribute("ManualRate", &iValue);
        xRepalce.manualRate = iValue;

        pSkillRepalce->Attribute("AutoRate", &iValue);
        xRepalce.autoRate = iValue;

        vecSkillRepalce.push_back(xRepalce);

        pSkillRepalce = pSkillRepalce->NextSiblingElement("SkillRepalce");
    }

    //宠物资质等级和浮动值
    MeXmlElement* pAptitudeTable= pPetSetting->FirstChildElement("AptitudeTable");
    if (pAptitudeTable == NULL) 
    { return false; }

    MeXmlElement* pAptitude = pAptitudeTable->FirstChildElement("Aptitude");
    while (pAptitude != NULL)
    {
        int quality = 0;
        pAptitude->Attribute("Quality", &quality);
        if (quality >= EPetQuality_Count)
        { return false; }

        for (int i=0;i<EPetAptitude_LevelMax;++i)
        {
            char szTmp[65] = { 0 };
            sprintf_s(szTmp, sizeof(szTmp) - 1, "Rand%d",i+1);
            pAptitude->Attribute(szTmp, &iValue);
            _AptitudeTable[quality][i] = iValue;
        }

        pAptitude = pAptitude->NextSiblingElement("Aptitude");
    }

    MeXmlElement* pAptitudeFloat = pAptitudeTable->FirstChildElement("AptitudeFloat");
    while (pAptitudeFloat != NULL)
    {
        for (int i=0;i<EPetAptitude_FloatCount;++i)
        {
            char szTmp[65] = { 0 };
            sprintf_s(szTmp, sizeof(szTmp) - 1, "Value%d",i);
            pAptitudeFloat->Attribute(szTmp, &dValue);
            _AptitudeFloat[i] = dValue;
        }
        
        pAptitudeFloat = pAptitudeFloat->NextSiblingElement("AptitudeFloat");
    }

    MeXmlElement* pAptitudeStar = pAptitudeTable->FirstChildElement("AptitudeStar");
    while (pAptitudeStar != NULL)
    {
        SAptitudeStar xStar;

        pAptitudeStar->Attribute("LowValue", &iValue);
        xStar.nLowValue  = iValue;

        pAptitudeStar->Attribute("HighValue", &iValue);
        xStar.nHighValue = iValue;

        pAptitudeStar->Attribute("StarLevel", &iValue);
        xStar.nStarLevel = iValue;

        vecAptitudeStar.push_back(xStar);

        pAptitudeStar = pAptitudeStar->NextSiblingElement("AptitudeStar");
    }

    //宠物成长率
    MeXmlElement* pGrowRateTable = pPetSetting->FirstChildElement("GrowRateTable");
    if (pGrowRateTable == NULL) 
    { return false; }

    MeXmlElement* pGrowRate = pGrowRateTable->FirstChildElement("GrowRate");
    while (pGrowRate != NULL)
    {
        int quality = 0;
        pGrowRate->Attribute("Quality", &quality);
        if (quality >= EPetQuality_Count)
        { return false; }

        for (int i=0;i<EPetGrowth_Count;++i)
        {
            char szTmp[65] = { 0 };
            sprintf_s(szTmp, sizeof(szTmp) - 1, "Star%d",i+1);
            pGrowRate->Attribute(szTmp, &iValue);
            _GrowRateTable[quality][i] = iValue;
        }

        pGrowRate = pGrowRate->NextSiblingElement("GrowRate");
    }

    //宠物称号
    MeXmlElement* pTitleTable = pPetSetting->FirstChildElement("TitleTable");
    if (pTitleTable == NULL) 
    { return false; }

    MeXmlElement* pTitle = pTitleTable->FirstChildElement("Title");
    while (pTitle != NULL)
    {
        STitle xTitle;

        Common::_tstring strTitleName;
        strTitleName.fromUTF8( pTitle->Attribute("TitleName") );
        xTitle.strTitleName = strTitleName;

        Common::_tstring strTitleDesc;
        strTitleDesc.fromUTF8( pTitle->Attribute("TitleDesc") );
        xTitle.strTitleDesc = strTitleDesc;


        pTitle->Attribute("SavvyLowValue", &iValue);
        xTitle.nSavvyLowValue  = iValue;

        pTitle->Attribute("SavvyHighValue", &iValue);
        xTitle.nSavvyHighValue = iValue;

        pTitle->Attribute("GrowStarLevel", &iValue);
        xTitle.nGrowStarLevel = iValue;

        pTitle->Attribute("AptitudeLowValue", &iValue);
        xTitle.nAptitudeLowValue = iValue;

        pTitle->Attribute("AptitudeHighValue", &iValue);
        xTitle.nAptitudeHighValue = iValue;

		pTitle->Attribute("Quality",&iValue);
		xTitle.nQuality     = iValue;

		const char* color = pTitle->Attribute("Color");
		if (color)
		{
			std::string temp(color);
			size_t findPos = temp.find(',');
			int r = 0xff;
			int g = 0xff;
			int b = 0xff;
			if (findPos != std::string::npos)
			{
				r = atoi(temp.substr(0,findPos).c_str());
				size_t findPos2 = temp.find(',',findPos+1);
				if (findPos != std::string::npos)
				{
					g = atoi(temp.substr(findPos+1,findPos2-findPos-1).c_str());
					b = atoi(temp.substr(findPos2+1,temp.length()-findPos2-1).c_str());
					xTitle.nColor = D3DCOLOR_XRGB(r, g, b);
				}
			}
		}

        vecTitle.push_back( xTitle );
        pTitle = pTitle->NextSiblingElement("Title");
    }

    //宠物二级属性相关
    MeXmlElement* pSecondAttrTable = pPetSetting->FirstChildElement("SecondAttrTable");
    if (pSecondAttrTable == NULL) 
    { return false; }

    MeXmlElement* pBaseAttrParam = pSecondAttrTable->FirstChildElement("BaseAttrParam");
    while (pBaseAttrParam != NULL)
    {
        pBaseAttrParam->Attribute("HP", &iValue);
        _FightAttrBaseAttrParam[CharAttr_HPMax] = iValue;

        pBaseAttrParam->Attribute("PhyAttack", &iValue);
        _FightAttrBaseAttrParam[CharAttr_AttackPhysics] = iValue;

        pBaseAttrParam->Attribute("MagAttack", &iValue);
        _FightAttrBaseAttrParam[CharAttr_AttackMagic] = iValue;

        pBaseAttrParam->Attribute("PhyDefend", &iValue);
        _FightAttrBaseAttrParam[CharAttr_DefendPhysics] = iValue;

        pBaseAttrParam->Attribute("MagDefend", &iValue);
        _FightAttrBaseAttrParam[CharAttr_DefendMagic] = iValue;

        pBaseAttrParam->Attribute("Exact", &iValue);
        _FightAttrBaseAttrParam[CharAttr_Exact] = iValue;

        pBaseAttrParam->Attribute("Dodge", &iValue);
        _FightAttrBaseAttrParam[CharAttr_Dodge] = iValue;

        pBaseAttrParam->Attribute("Critical", &iValue);
        _FightAttrBaseAttrParam[CharAttr_Critical] = iValue;

        pBaseAttrParam->Attribute("Tenacity", &iValue);
        _FightAttrBaseAttrParam[CharAttr_Tenacity] = iValue;

        pBaseAttrParam = pBaseAttrParam->NextSiblingElement("BaseAttrParam");
    }

    MeXmlElement* pLevelParam = pSecondAttrTable->FirstChildElement("LevelParam");
    while (pLevelParam != NULL)
    {
        pLevelParam->Attribute("HP", &iValue);
        _FightAttrLevelParam[CharAttr_HPMax] = iValue;

        pLevelParam->Attribute("PhyAttack", &iValue);
        _FightAttrLevelParam[CharAttr_AttackPhysics] = iValue;

        pLevelParam->Attribute("MagAttack", &iValue);
        _FightAttrLevelParam[CharAttr_AttackMagic] = iValue;

        pLevelParam->Attribute("PhyDefend", &iValue);
        _FightAttrLevelParam[CharAttr_DefendPhysics] = iValue;

        pLevelParam->Attribute("MagDefend", &iValue);
        _FightAttrLevelParam[CharAttr_DefendMagic] = iValue;

        pLevelParam->Attribute("Exact", &iValue);
        _FightAttrLevelParam[CharAttr_Exact] = iValue;

        pLevelParam->Attribute("Dodge", &iValue);
        _FightAttrLevelParam[CharAttr_Dodge] = iValue;

        pLevelParam->Attribute("Critical", &iValue);
        _FightAttrLevelParam[CharAttr_Critical] = iValue;

        pLevelParam->Attribute("Tenacity", &iValue);
        _FightAttrLevelParam[CharAttr_Tenacity] = iValue;

        pLevelParam = pLevelParam->NextSiblingElement("LevelParam");
    }

    //宠物悟性相关
    MeXmlElement* pSavvyTable = pPetSetting->FirstChildElement("SavvyTable");
    if (pSavvyTable == NULL) 
    { return false; }

    MeXmlElement* pAddAptitudePer = pSavvyTable->FirstChildElement("AddAptitudePer");
    while (pAddAptitudePer != NULL)
    {
        int nSavvy = 0;
        pAddAptitudePer->Attribute("Savvy", &nSavvy);
        
        if ( nSavvy > EPetSavvy_LevelMax )
        { break; }

        pAddAptitudePer->Attribute("Value", &iValue);
        
        _SavvyAddAptitudePer[nSavvy - 1] = iValue;
        pAddAptitudePer = pAddAptitudePer->NextSiblingElement("AddAptitudePer");
    }

    MeXmlElement* pAddCarryLevel = pSavvyTable->FirstChildElement("AddCarryLevel");
    while (pAddCarryLevel != NULL)
    {
        int nSavvy = 0;
        pAddCarryLevel->Attribute("Savvy", &nSavvy);

        if ( nSavvy > EPetSavvy_LevelMax )
        { break; }

        pAddCarryLevel->Attribute("Value", &iValue);

        _SavvyAddTakeLevel[nSavvy - 1] = iValue;
        pAddCarryLevel = pAddCarryLevel->NextSiblingElement("AddCarryLevel");
    }

    MeXmlElement* pUpSavvyRate = pSavvyTable->FirstChildElement("UpSavvyRate");
    while (pUpSavvyRate != NULL)
    {
        SSavvyUp xSavvyUp;
        pUpSavvyRate->Attribute("CatchQuality", &iValue);
        xSavvyUp.nCatchQuality = iValue;

        pUpSavvyRate->Attribute("CatchLevel", &iValue);
        xSavvyUp.nCatchLevel = iValue;

        pUpSavvyRate->Attribute("Savvy", &iValue);
        xSavvyUp.nSavvy = iValue;

        pUpSavvyRate->Attribute("ItemCostMoney", &iValue);
        xSavvyUp.nItemCostMoney = iValue;

        pUpSavvyRate->Attribute("EatCostMoney", &iValue);
        xSavvyUp.nEatCostMoney = iValue;

        pUpSavvyRate->Attribute("ItemRate", &iValue);
        xSavvyUp.nItemRate = iValue;

        pUpSavvyRate->Attribute("EatRate", &iValue);
        xSavvyUp.nEatRate = iValue;

        vecSavvyUp.push_back( xSavvyUp );
        pUpSavvyRate = pUpSavvyRate->NextSiblingElement("UpSavvyRate");
    }

    MeXmlElement* pSavvyReduce = pSavvyTable->FirstChildElement("SavvyReduce");
    while (pSavvyReduce != NULL)
    {
        SSavvyReduce xSavvyReduce;
        pSavvyReduce->Attribute("Savvy", &iValue);
        xSavvyReduce.nSavvy = iValue;

        for (int i=0;i<ESavvyReduce_NumMax;++i)
        {
            char szTmp[65] = { 0 };
            sprintf_s(szTmp, sizeof(szTmp) - 1, "Reduce%d",i+1);
            pSavvyReduce->Attribute(szTmp, &iValue);
            xSavvyReduce.nReduce[i] = iValue;

            sprintf_s(szTmp, sizeof(szTmp) - 1, "Rate%d",i+1);
            pSavvyReduce->Attribute(szTmp, &iValue);
            xSavvyReduce.nRate[i] = iValue;
        }
        
        vecSavvyReduce.push_back( xSavvyReduce );
        pSavvyReduce = pSavvyReduce->NextSiblingElement("SavvyReduce");
    }

    //宠物根骨相关
    MeXmlElement* pBoneTable = pPetSetting->FirstChildElement("BoneTable");
    if (pBoneTable == NULL) 
    { return false; }

    MeXmlElement* pBoneRate = pBoneTable->FirstChildElement("BoneRate");
    while (pBoneRate != NULL)
    {
        SBoneRate xBone;

        pBoneRate->Attribute("CatchQuality", &iValue);
        xBone.nCatchQuality = iValue;

        pBoneRate->Attribute("CatchLevel", &iValue);
        xBone.nCatchLevel = iValue;

        for (int i=0;i<=EPetBone_NumberMax;++i)
        {
            char szTmp[65] = { 0 };
            sprintf_s(szTmp, sizeof(szTmp) - 1, "Value%d",i);
            pBoneRate->Attribute(szTmp, &iValue);
            xBone.nBoneRate[i] = iValue;
        }

        vecBoneRate.push_back( xBone );
        pBoneRate = pBoneRate->NextSiblingElement("BoneRate");
    }

    //宠物繁殖相关
    MeXmlElement* pBreedTable = pPetSetting->FirstChildElement("BreedTable");
    if (pBreedTable == NULL) 
    { return false; }

    MeXmlElement* pBreedNum  = pBreedTable->FirstChildElement("BreedNum");
    while (pBreedNum != NULL)
    {	
        SBreedNum  xBreedNum;

        pBreedNum->Attribute("BeginLevel", &iValue);
        xBreedNum.nBeginLevel = iValue;

        pBreedNum->Attribute("EndLevel", &iValue);
        xBreedNum.nEndLevel = iValue;

        pBreedNum->Attribute("Number", &iValue);
        xBreedNum.nNumber = iValue;

        vecBreedNum.push_back(xBreedNum);

        pBreedNum = pBreedNum->NextSiblingElement("BreedNum");
    }


    MeXmlElement* pBreedMoney = pBreedTable->FirstChildElement("BreedMoney");
    while (pBreedMoney != NULL)
    {
        SBreedMoney xBreedMoney;

        pBreedMoney->Attribute("CatchQuality", &iValue);
        xBreedMoney.nCatchQuality = iValue;

        pBreedMoney->Attribute("CatchLevel", &iValue);
        xBreedMoney.nCatchLevel = iValue;

        pBreedMoney->Attribute("Money", &iValue);
        xBreedMoney.nMoney = iValue;

        vecBreedCost.push_back(xBreedMoney);

        pBreedMoney = pBreedMoney->NextSiblingElement("BreedMoney");
    }

    //宠物死亡相关
    MeXmlElement* pDeathTable = pPetSetting->FirstChildElement("DeathTable");
    if (pDeathTable == NULL) 
    { return false; }

    MeXmlElement* pDropValue = pDeathTable->FirstChildElement("DropValue");
    while (pDropValue != NULL)
    {
        int level = 0;
        pDropValue->Attribute("Level", &level);

        int loyalty = 0;
        pDropValue->Attribute("Loyalty", &loyalty);

        int duration = 0;
        pDropValue->Attribute("Duration", &duration);

        _PetDeathDropLoyalty [level]  = loyalty ;
        _PetDeathDropDuration[level]  = duration;

        pDropValue = pDropValue->NextSiblingElement("DropValue");
    }

    //宠物性格相关
    MeXmlElement* pCharacterizeTable = pPetSetting->FirstChildElement("Characterize");
    if (pCharacterizeTable == NULL) 
    { return false; }

    MeXmlElement* pPetAutoSkill = pCharacterizeTable->FirstChildElement("PetAutoSkill");
    while (pPetAutoSkill != NULL)
    {
        int nAutoSkillType = 0;
        pPetAutoSkill->Attribute("Type", &nAutoSkillType);

        pPetAutoSkill->Attribute("Cowardice", &iValue);
        _CharacterizeTable[nAutoSkillType][EPetChar_Cowardice] = iValue;

        pPetAutoSkill->Attribute("Reticence", &iValue);
        _CharacterizeTable[nAutoSkillType][EPetChar_Reticence] = iValue;

        pPetAutoSkill->Attribute("Ligeance", &iValue);
        _CharacterizeTable[nAutoSkillType][EPetChar_Ligeance] = iValue;

        pPetAutoSkill->Attribute("Prudence", &iValue);
        _CharacterizeTable[nAutoSkillType][EPetChar_Prudence] = iValue;

        pPetAutoSkill->Attribute("Valor", &iValue);
        _CharacterizeTable[nAutoSkillType][EPetChar_Valor]    = iValue;

        pPetAutoSkill = pPetAutoSkill->NextSiblingElement("PetAutoSkill");
    }

    return true;
}
//only for client
unsigned long PetSettingConfig::GetTitleColorByTitleName(const std::string &m_name,int &Quality)
{
	unsigned long dwColor = 0;
	for (int i=0; i< vecTitle.size(); i++)
	{
		if (vecTitle[i].strTitleName.compare(m_name) ==0)
		{
			if (vecTitle[i].nQuality == -1)
			{
				dwColor = vecTitle[i].nColor;
				break;
			}
			else
			{
				Quality = vecTitle[i].nQuality;
				break;
			}
		}
	}
	return dwColor;
}