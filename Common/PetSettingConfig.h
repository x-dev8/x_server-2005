#ifndef __COMMON_PETSETTINGCONFIG_H__
#define __COMMON_PETSETTINGCONFIG_H__

#pragma once

#include <string>
#include <vector>
#include <map>

#include "GlobalDef.h"
#include "GameDefinePet.h"
#include "ExpStage.h"

#define PET_CATCH_PROBABILITY           10000
#define PET_SKILL_REPALCE_PROBABILITY   100000
#define PET_BREED_PROBABILITY           100000

class PetSettingConfig
{
public:
    enum EPetSetConstDefine
    {
        EPetAptitude_LevelMax   = 10,   // 资质等级最大值
        EPetAptitude_FloatCount = 11,   // 资质随机最大数量

        EPetSavvy_LevelMax      = 10,   // 最高悟性
        EPetBone_NumberMax      = 10,   // 最多根骨

        ESavvyReduce_NumMax     =  3,   // 悟性降低
    };
public:
    struct SPetCarry
    {
        uint8  nBeginLevel  ;
        uint8  nEndLevel    ;
        uint8  nNumber      ;
    };

    struct SSkillRepalce
    {
        uint16 id       ;
        uint8  skillNum ;
        uint8  manualNum;
        uint8  autoNum  ;
        uint32 manualRate;
        uint32 autoRate ;
    };

    struct SBreedNum
    {
        uint8  nBeginLevel  ;
        uint8  nEndLevel    ;
        uint8  nNumber      ;
    };

    struct SAptitudeStar
    {
        uint16  nLowValue ;
        uint16  nHighValue;
        uint8   nStarLevel;
    };

    struct SBreedMoney
    {
        uint8   nCatchQuality;
        uint8   nCatchLevel  ;
        uint32  nMoney       ;
    };

    struct SBoneRate
    {
        uint8   nCatchQuality;
        uint8   nCatchLevel  ;
        uint16  nBoneRate[EPetBone_NumberMax + 1];
    };

    struct STitle
    {
        std::string  strTitleName;
        std::string  strTitleDesc;
        uint8  nSavvyLowValue;
        uint8  nSavvyHighValue;
        uint8  nGrowStarLevel;
        uint8  nAptitudeLowValue;
        uint8  nAptitudeHighValue;
		int	   nQuality;
		unsigned long nColor;
    };

    struct SSavvyUp
    {
        uint8   nCatchQuality;
        uint8   nCatchLevel  ;
        uint8   nSavvy       ;
        uint32  nItemCostMoney;
        uint32  nEatCostMoney;
        uint16  nItemRate    ;
        uint16  nEatRate     ;
    };

    struct SSkillCatchRate
    {
        uint8   nCatchLevel;
        uint8   nSkillLevel;
        uint16  nAddRate   ;
    };

    struct SHPCatchRate
    {
        uint8   nMaxHpPer;
        uint8   nMinHpPer;
        uint16  nAddRate ;
    };

    struct SSavvyReduce
    {
        uint8   nSavvy;
        uint8   nReduce [ESavvyReduce_NumMax];
        uint8   nRate   [ESavvyReduce_NumMax];
    };

protected:
    PetSettingConfig();

public:
    ~PetSettingConfig();

    inline static PetSettingConfig& Instance()
    {
        static PetSettingConfig s_xConfig;
        return s_xConfig;
    }

    bool   LoadPetSettingConfig( const char* szFile );

    int    GetBaseAttrCount    ();
    int    GetBaseAttrValue    ();

    uint32 GetRefreshLoyaltyTime    ();
    uint32 GetRefreshDurationTime   ();

    int    GetPlayerPetLimit   ( int level );

    int    GetAptitudeLevel    ( int quality );
    float  GetAptitudeFloat    ( int aptitudeLevel );

    int    GetGrowRateStar     ( int quality );

    int    GetFightAttrBaseAttrParam ( int charAttr );
    int    GetFightAttrLevelParam    ( int charAttr );

    int    GetSavvyAddAptitudePer( int savvy );
    int    GetSavvyAddTakeLevel  ( int savvy );

    bool   IsSkillRepalce( bool bIsManualSkill, int skillNum, int manualNum, int autoNum );

    int    GetAptitudeStar     ( int aptitudeValue );

    int    GetPetBreedNum      ( int petLevel );
    int    GetPetBreedMoney    ( int quality, int catchLevel );

    int    GetPetBone          ( int quality, int catchLevel );

    int    GetPetDeathDropLoyalty   ( int petLevel );
    int    GetPetDeathDropDuration  ( int petLevel );

    int    GetCharacterizeAutoSkillPer ( int autoSkillType, int characterize );

    STitle* GetPetTitle( int savvy, int growStar, int aptitude );
	unsigned long GetTitleColorByTitleName(const std::string &m_name,int &nQuality);

    int    GetSavvyUpItemRate ( int quality, int catchLevel, int savvy );
    int    GetSavvyUpEatRate  ( int quality, int catchLevel, int savvy );
    int    GetSavvyUpItemMoney( int quality, int catchLevel, int savvy );
    int    GetSavvyUpEatMoney ( int quality, int catchLevel, int savvy );

    int    GetReduceSavvy     ( int savvy );    

    int    GetSkillCatchRate( int catchLevel, int skillLevel );
    int    GetHPCatchRate   ( int hpPer );

private:
    std::vector<SPetCarry>      vecPetCarry     ;
    std::vector<SSkillRepalce>  vecSkillRepalce ;
    std::vector<SAptitudeStar>  vecAptitudeStar ;
    std::vector<SBreedNum>      vecBreedNum     ;
    std::vector<SBreedMoney>    vecBreedCost    ;
    std::vector<SBoneRate>      vecBoneRate     ;
    std::vector<STitle>         vecTitle        ;
    std::vector<SSavvyUp>       vecSavvyUp      ;
    std::vector<SSavvyReduce>   vecSavvyReduce  ;

    std::vector<SSkillCatchRate>    vecSkillCatchRate   ;
    std::vector<SHPCatchRate>       vecHPCatchRate      ;

    int    _AptitudeTable[EPetQuality_Count][EPetAptitude_LevelMax];
    float  _AptitudeFloat[EPetAptitude_FloatCount];

    int    _GrowRateTable[EPetQuality_Count][EPetGrowth_Count];

    int    _FightAttrBaseAttrParam[CharAttr_AttributMaxCount];
    int    _FightAttrLevelParam   [CharAttr_AttributMaxCount];

    int    _SavvyAddAptitudePer   [EPetSavvy_LevelMax];
    int    _SavvyAddTakeLevel     [EPetSavvy_LevelMax];

    int    _PetDeathDropLoyalty   [const_iCharMaxLevel];
    int    _PetDeathDropDuration  [const_iCharMaxLevel];

    int    _CharacterizeTable[EPetSkillCategory_MaxSize][EPetChar_Count];

    int    _BaseAttrCount ;  
    int    _BaseAttrValue ; 
    uint32 _RefreshLoyaltyTime ; 
    uint32 _RefreshDurationTime;
};

#define thePetSettingConfig PetSettingConfig::Instance()   //实例接口

#endif