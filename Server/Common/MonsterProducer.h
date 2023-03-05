/********************************************************************
    Filename:     MonsterProducer.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __MONSTERPRODUCER_H__
#define __MONSTERPRODUCER_H__

#pragma once

#include "ItemDetail.h"
#include "MonsterConfig.h"
#include "Mutex.h"

#define HIDE_MONSTER    -2

class CMonsterProducer : public CSemiAutoIntLock
{ // 怪物生产基地
public:
    struct TagMonsterData
    {
        int      nMonsterIndex; // 在怪物信息容器中的下标
        float    x            ; // 出身点的坐标
        float    y            ; 
        RECT     rcBron       ;
        short    stZoneID     ;
        int      nDirection   ; // 朝向角度( 0 -360  小于0时表示随即朝向 )
        BOOL     CreateFlag   ; // 用来判定该monster是否已经出生了
        DWORD    dwDeadTime   ; // 用来记录该Monster上次死亡的时间
        DWORD    dwReliveTime ; // 用来记录该Monster的复活时间，就是说该Monster死了多久以后需要复活
        short    stAiValue    ; // Ai思考时间
        bool     bHide        ;
        bool     bRandRange   ;
        short    eCountry     ; // 国家
        short    nFightCamp   ; // 阵营
        short    nForce       ; // 势力
        int      nRouteID     ; // 路点ID

        // 未来开放
        std::string szMonsterNameCorrect;
        int iModelIDCorrect;
        std::string szCreatureSound;
        short stMonsterTypeCorrect;
        short stBodySizeCorrect;
        short stLevelCorrect;
        short stRewardExpCorrect;

        short stStrengthCorrect;
        short stConstitutionCorrect;
        short stAgilityCorrect;
        short stMagicCorrect;
        short stIntelligenceCorrect;
        short stCharmCorrect;

        short stHpMaxCorrect;
        short stMpMaxCorrect;
        short stHpRestoreCorrect;
        short stMpRestoreCorrect;

        short stExactCorrect;
        short stDodgeCorrect;
        short stViewSightCorrect;

        short stPhysicsAtkMinCorrect;
        short stPhysicsAtkMaxCorrect;
        short stMagicAtkMinCorrect;
        short stMagicAtkMaxCorrect;
        short stCriticalRateCorrect;
        short stAttackRateCorrect;
        short stPhysicsDefCorrect;
        short stMagicDefCorrect;

        short stFrostAttCorrect;
        short stBlazeAttCorrect;
        short stThunderAttCorrect;
        short stPoisonAttCorrect;
        short stFrostDefCorrect;
        short stBlazeDefCorrect;
        short stThunderDefCorrect;
        short stPoisonDefCorrect;
        DWORD dwCatchTimeCorrect;
        float fMoveSpeedCorrect;

        int iSkillIDCorrect[3];
        short stSkillLevelCorrect[3];
        short stSkillRateCorrect[3];
        int iGoodDropIDCorrect[6];
        short stGoodDropRateCorrect[6];
        short stDropMinMoneyCorrect;
        short stDropMaxMoneyCorrect;
        float fItemDropMultipleRateCorrect;
        unsigned int nEnmityRate;
        unsigned int nEnmity;

        std::string m_strDeadScriptName;
        std::string m_strLuaScript;

        TagMonsterData()
        {
            bRandRange = true;
            nMonsterIndex = -1;         //对应的monster在monster.slk表格中的ID
            x = -1;
            y = -1;                     //出身点的坐标
            rcBron.left = -1;
            rcBron.top = -1;
            rcBron.right = -1;
            rcBron.bottom = -1;
            CreateFlag = false;         //用来判定该monster是否已经出生了
            dwDeadTime = 0;             //用来记录该Monster上次死亡的时间
            dwReliveTime = 60000;       //用来记录该Monster的复活时间，就是说该Monster死了多久以后需要复活
            stAiValue = 1000;    
            bHide = false;
            eCountry = 0;
            nFightCamp = 0;
            nForce = 0;
            nRouteID = -1;

            m_strDeadScriptName.clear();
            m_strLuaScript.clear();

            iModelIDCorrect = -1;
            stMonsterTypeCorrect = -1;
            stBodySizeCorrect = 0;
            stLevelCorrect = 0;
            stRewardExpCorrect = 0;

            stStrengthCorrect = 0;
            stConstitutionCorrect = 0;
            stAgilityCorrect = 0;
            stMagicCorrect = 0;
            stIntelligenceCorrect = 0;
            stCharmCorrect = 0;

            stHpMaxCorrect = 0;
            stMpMaxCorrect = 0;
            stHpRestoreCorrect = 0;
            stMpRestoreCorrect = 0;
            stExactCorrect = 0;
            stDodgeCorrect = 0;
            stViewSightCorrect = 0;

            stPhysicsAtkMinCorrect = 0;
            stPhysicsAtkMaxCorrect = 0;
            stMagicAtkMinCorrect = 0;
            stMagicAtkMaxCorrect = 0;
            stCriticalRateCorrect = 0;
            stPhysicsDefCorrect = 0;
            stMagicDefCorrect = 0;

            stFrostAttCorrect = 0;
            stBlazeAttCorrect = 0;
            stThunderAttCorrect = 0;
            stPoisonAttCorrect = 0;
            stFrostDefCorrect = 0;
            stBlazeDefCorrect = 0;
            stThunderDefCorrect = 0;
            stPoisonDefCorrect = 0;
            dwCatchTimeCorrect = 0;
            fMoveSpeedCorrect = 0.0f;

            iSkillIDCorrect[0] = -1;
            iSkillIDCorrect[1] = -1;
            iSkillIDCorrect[2] = -1;
            stSkillLevelCorrect[0] = -1;
            stSkillLevelCorrect[1] = -1;
            stSkillLevelCorrect[2] = -1;
            stSkillRateCorrect[0] = 0;
            stSkillRateCorrect[1] = 0;
            stSkillRateCorrect[2] = 0;

            iGoodDropIDCorrect[0] = -1;
            iGoodDropIDCorrect[1] = -1;
            iGoodDropIDCorrect[2] = -1;
            iGoodDropIDCorrect[3] = -1;
            iGoodDropIDCorrect[4] = -1;
            iGoodDropIDCorrect[5] = -1;
            stGoodDropRateCorrect[0] = 0;
            stGoodDropRateCorrect[1] = 0;
            stGoodDropRateCorrect[2] = 0;
            stGoodDropRateCorrect[3] = 0;
            stGoodDropRateCorrect[4] = 0;
            stGoodDropRateCorrect[5] = 0;

            stDropMinMoneyCorrect = 0;
            stDropMaxMoneyCorrect = 0;
            fItemDropMultipleRateCorrect = 0;
        }
    };

    CMonsterProducer();
    ~CMonsterProducer();

    TagMonsterData* GetMonsterData( unsigned int nIndex );
    BOOL            GetMonsterData( unsigned int nIndex, int &nMonsterIndex, float &x, float &y ); //获取怪物    
    int             AddMonster( SMapMonsterInfo* pMonsterStruct, int nBornPosX, int nBornPosY, RECT& rcBronArea, const char* szFilePath, unsigned short ustMapLevel = 0); //添加怪物
    BOOL            IsHaveDeadMonster();         // 判断该地图上是否有死去的monster ,,需要刷出来
    BOOL            ReliveMonster();             // 堆尾部的monster活了
    BOOL            KillMonster( int index );    // 某个位置的monster死了
    int             PeekReliveDeadMonster();     // 取得堆，最前面的一个死人的编号
    int             PopDeadMonster();            // 提取出一个死人
    BOOL            PushDeadMonster( int index); // 增加一个死的npc到堆里面
    void            AllMonsterDeadTimeClear();   // 所有死亡怪物死亡时间清0
    uint32          GetDeadMonsterNumber();

private:
    typedef std::vector<TagMonsterData> TagMonsterDataContainer;
    typedef std::queue<int>             MonsterIndexContainer;

    TagMonsterDataContainer m_vtMonsterData; // 记录但前地图在编辑器中摆放的Monster的数据
    MonsterIndexContainer   m_qeDeadMonster; // 保存需要刷的怪物的堆
};

#endif // __MONSTERPRODUCER_H__
