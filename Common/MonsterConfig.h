/********************************************************************
    Filename:     MapMonsterConfig.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_MONSTERCONFIG_H__
#define __COMMON_MONSTERCONFIG_H__

#pragma once

#include "MeRTLibs.h"
#include "IOXMLObject.h"
#include "StageDataLoader.h"
#include "MonsterAITrigger.h"
#include "Mutex.h"

struct SMapMonsterInfo
{
    // 用到的
    int         m_iZone;         // ZoneId
    float       m_nX;            // 怪物在地图上的X坐标
    float       m_nY;            // 怪物在地图上的Y坐标
    bool        m_bRandRange;    // 怪物是否随机范围刷出 为真则为随机，为否则定点刷
    int         m_nDir;          // 怪物在地图上的朝向
    int         m_nId;           // 怪物Id
    int         m_iNumber;       // 几只
    bool        m_bEnable;       // 是否开启
    int         m_iCountry;      // 国家
    bool        m_bHide;         // 是否是隐藏怪
    std::string m_strScriptName; // 死亡脚本
    std::string m_strLuaScript;  // AI脚本
    int         m_iAiValue;      // 思考的时间
    int         m_nFightCamp;    // 阵营
    int         m_nForce;        // 势力
    int         m_nRouteID;      // 路点ID

    // 未来开放
    std::string m_strIntro;
    std::string m_strName;       // 怪物模板里的名字
    int         m_iRelife;       // 复活时间
    std::string m_strMonsterName;
    int m_iProfessionCorrect;
    int m_iModelIDCorrect;
    std::string m_strCreatureSound;
    int m_iMonsterTypeCorrect;
    int m_iBodySizeCorrect;
    int m_iLevelCorrect;
    int m_iRewardExpCorrect;
    int m_iStrengthCorrect;
    int m_iConstitutionCorrect;
    int m_iAgilityCorrect;
    int m_iMagicCorrect;
    int m_iIntelligenceCorrect;
    int m_iCharmCorrect;
    int m_iFrostAttCorrect;
    int m_iBlazeAttCorrect;
    int m_iThunderAttCorrect;
    int m_iPoisonAttCorrect;
    int m_iFrostDefCorrect;
    int m_iBlazeDefCorrect;
    int m_iThunderDefCorrect;
    int m_iPoisonDefCorrect;
    int m_iHpMaxCorrect;
    int m_iMpMaxCorrect;
    int m_iHpRestoreCorrect;
    int m_iMpRestoreCorrect;
    int m_iExactCorrect;
    int m_iDodgeCorrect;
    int m_iViewCorrect;
    int m_iCatchTimeCorrect;
    float m_fMoveSpeedCorrect;
    int m_iPhysicsMinCorrect;
    int m_iPhysicsMaxCorrect;
    int m_iMagicMinCorrect;
    int m_iMagicMaxCorrect;
    int m_iPhysicsDefCorrect;
    int m_iMagicDefCorrect;
    int m_iCriticalRateCorrect;
    int m_iAttackRateCorrect;
    int m_iSkill1RateCorrect;
    int m_iSkill2RateCorrect;
    int m_iSkill3RateCorrect;
    int m_iItem1RateCorrect;
    int m_iItem2RateCorrect;
    int m_iItem3RateCorrect;
    int m_iItem4RateCorrect;
    int m_iItem5RateCorrect;
    int m_iItem6RateCorrect;
    int m_iDropMoneyMinCorrect;
    int m_iDropMoneyMaxCorrect;
    float m_fDropMultipleRateCorrect;
    int m_iSkill1Correct;
    int m_iSkill2Correct;
    int m_iSkill3Correct;
    int m_iSkill1LevelCorrect;
    int m_iSkill2LevelCorrect;
    int m_iSkill3LevelCorrect;
    int m_iItem1Correct;
    int m_iItem2Correct;
    int m_iItem3Correct;
    int m_iItem4Correct;
    int m_iItem5Correct;
    int m_iItem6Correct;

    SMapMonsterInfo()
    {
        m_strIntro.clear();
        m_strName.clear();
        m_bRandRange = true;
        m_nX = 0;
        m_nY = 0;
        m_nDir = 0;
        m_nId = -1;
        m_iZone = -1;
        m_iNumber = 0;
        m_iRelife = 60000;
        m_iCountry = 0;
        m_nFightCamp = 0;
        m_nForce = 0;
        m_nRouteID = -1;
        m_bEnable = true;
        m_bHide = false;
        m_strScriptName.clear();
        m_strLuaScript.clear();
        m_iAiValue = 1000;
        m_strMonsterName.clear();
        m_iProfessionCorrect = -1;
        m_iModelIDCorrect = -1;
        m_strCreatureSound.clear();
        m_iMonsterTypeCorrect = -1;
        m_iBodySizeCorrect = 0;
        m_iLevelCorrect = 0;
        m_iRewardExpCorrect = 0;
        m_iStrengthCorrect = 0;
        m_iConstitutionCorrect = 0;
        m_iAgilityCorrect = 0;
        m_iMagicCorrect = 0;
        m_iIntelligenceCorrect = 0;
        m_iCharmCorrect = 0;
        m_iFrostAttCorrect = 0;
        m_iBlazeAttCorrect = 0;
        m_iThunderAttCorrect = 0;
        m_iPoisonAttCorrect = 0;
        m_iFrostDefCorrect = 0;
        m_iBlazeDefCorrect = 0;
        m_iThunderDefCorrect = 0;
        m_iPoisonDefCorrect = 0;
        m_iHpMaxCorrect = 0;
        m_iMpMaxCorrect = 0;
        m_iHpRestoreCorrect = 0;
        m_iMpRestoreCorrect = 0;
        m_iExactCorrect = 0;
        m_iDodgeCorrect = 0;
        m_iViewCorrect = 0;
        m_iCatchTimeCorrect = 0;
        m_fMoveSpeedCorrect = 0.0f;
        m_iPhysicsMinCorrect = 0;
        m_iPhysicsMaxCorrect = 0;
        m_iMagicMinCorrect = 0;
        m_iMagicMaxCorrect = 0;
        m_iPhysicsDefCorrect = 0;
        m_iMagicDefCorrect = 0;
        m_iCriticalRateCorrect = 0;
        m_iAttackRateCorrect = 0;
        m_iSkill1Correct = -1;
        m_iSkill2Correct = -1;
        m_iSkill3Correct = -1;
        m_iSkill1LevelCorrect = -1;
        m_iSkill2LevelCorrect = -1;
        m_iSkill3LevelCorrect = -1;
        m_iSkill1RateCorrect = 0;
        m_iSkill2RateCorrect = 0;
        m_iSkill3RateCorrect = 0;
        m_iItem1Correct = -1;
        m_iItem2Correct = -1;
        m_iItem3Correct = -1;
        m_iItem4Correct = -1;
        m_iItem5Correct = -1;
        m_iItem6Correct = -1;
        m_iItem1RateCorrect = 0;
        m_iItem2RateCorrect = 0;
        m_iItem3RateCorrect = 0;
        m_iItem4RateCorrect = 0;
        m_iItem5RateCorrect = 0;
        m_iItem6RateCorrect = 0;
        m_iDropMoneyMinCorrect = 0;
        m_iDropMoneyMaxCorrect = 0;
        m_fDropMultipleRateCorrect = 0;
    }
};

class CMonsterConfig
{
public:
    CMonsterConfig();
    virtual ~CMonsterConfig();

    void ProcessLoadZoneInfo( XMLElement* element, int nZoneNumber );
    void ProcessLoadMonsterGroup( XMLElement* element, int nZoneNumber );
    void loadXML( CStageDataLoader* pStageDataLoader, XMLElement* element, int nZoneNumber );
    void exportXML( CStageDataLoader* pStageDataLoader, int i );

    int  GetMonsterCount();
    SMapMonsterInfo* GetMapMonsterInfo( int nIndex );
    void Clear();

public:
    std::vector<SMapMonsterInfo> m_vecMonster;
    CSemiAutoIntLock  _lock;
};

#endif // __COMMON_MONSTERCONFIG_H__
