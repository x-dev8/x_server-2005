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
{ // ������������
public:
    struct TagMonsterData
    {
        int      nMonsterIndex; // �ڹ�����Ϣ�����е��±�
        float    x            ; // ����������
        float    y            ; 
        RECT     rcBron       ;
        short    stZoneID     ;
        int      nDirection   ; // ����Ƕ�( 0 -360  С��0ʱ��ʾ�漴���� )
        BOOL     CreateFlag   ; // �����ж���monster�Ƿ��Ѿ�������
        DWORD    dwDeadTime   ; // ������¼��Monster�ϴ�������ʱ��
        DWORD    dwReliveTime ; // ������¼��Monster�ĸ���ʱ�䣬����˵��Monster���˶���Ժ���Ҫ����
        short    stAiValue    ; // Ai˼��ʱ��
        bool     bHide        ;
        bool     bRandRange   ;
        short    eCountry     ; // ����
        short    nFightCamp   ; // ��Ӫ
        short    nForce       ; // ����
        int      nRouteID     ; // ·��ID

        // δ������
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
            nMonsterIndex = -1;         //��Ӧ��monster��monster.slk����е�ID
            x = -1;
            y = -1;                     //����������
            rcBron.left = -1;
            rcBron.top = -1;
            rcBron.right = -1;
            rcBron.bottom = -1;
            CreateFlag = false;         //�����ж���monster�Ƿ��Ѿ�������
            dwDeadTime = 0;             //������¼��Monster�ϴ�������ʱ��
            dwReliveTime = 60000;       //������¼��Monster�ĸ���ʱ�䣬����˵��Monster���˶���Ժ���Ҫ����
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
    BOOL            GetMonsterData( unsigned int nIndex, int &nMonsterIndex, float &x, float &y ); //��ȡ����    
    int             AddMonster( SMapMonsterInfo* pMonsterStruct, int nBornPosX, int nBornPosY, RECT& rcBronArea, const char* szFilePath, unsigned short ustMapLevel = 0); //��ӹ���
    BOOL            IsHaveDeadMonster();         // �жϸõ�ͼ���Ƿ�����ȥ��monster ,,��Ҫˢ����
    BOOL            ReliveMonster();             // ��β����monster����
    BOOL            KillMonster( int index );    // ĳ��λ�õ�monster����
    int             PeekReliveDeadMonster();     // ȡ�öѣ���ǰ���һ�����˵ı��
    int             PopDeadMonster();            // ��ȡ��һ������
    BOOL            PushDeadMonster( int index); // ����һ������npc��������
    void            AllMonsterDeadTimeClear();   // ����������������ʱ����0
    uint32          GetDeadMonsterNumber();

private:
    typedef std::vector<TagMonsterData> TagMonsterDataContainer;
    typedef std::queue<int>             MonsterIndexContainer;

    TagMonsterDataContainer m_vtMonsterData; // ��¼��ǰ��ͼ�ڱ༭���аڷŵ�Monster������
    MonsterIndexContainer   m_qeDeadMonster; // ������Ҫˢ�Ĺ���Ķ�
};

#endif // __MONSTERPRODUCER_H__
