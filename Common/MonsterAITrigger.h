/********************************************************************
    Filename:     MonsterAITrigger.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#include "MeRTLibs.h"

#pragma once

enum EnumTriggerEvent
{
    eTE_WhenAIBeStarted,     // ÿ������AI�������ʱ�� 
    eTE_WhenThinking,        // ÿ������˼����ʱ��
    eTE_WhenGotoTargetPoint, // ÿ�������ƶ���Ŀ����ʱ��
    eTE_WhenAttacked,        // ÿ�������ܵ�������ʱ��
    eTE_WhenAttack,          // ÿ�����﹥����ʱ��
    eTE_WhenIdle,            // ÿ��������е�ʱ��
    eTE_WhenReturnToBron,    // ÿ������س������ʱ��
};

enum EnumTriggerCondition
{
    eTC_HPChanged, // ����HP�ı�
    eTC_MPChanged, // ����MP�ı�
};

enum EnumTriggerAction
{
    eTA_UseSkill,  // �ͷż���
    eTA_ReStoreHP, // �ظ�HP
    eTA_ReStoreMP, // �ظ�MP
};

struct SEvent
{ // �¼�
    short stEventID;         // �¼�ID
    char szEventIntro[1024]; // �¼�����
    SEvent()
    {
        stEventID = -1;
        memset(szEventIntro, NULL, sizeof(szEventIntro));
    }
};

struct SCondition
{ // ����
    short stConditionID;         // ����ID
    char szConditionIntro[1024]; // ��������
    BYTE byOperation[1];
    int nValue[1];
    SCondition()
    {
        memset(byOperation, 0, sizeof(byOperation));
        memset(nValue, 0, sizeof(nValue));
        stConditionID = -1;
        memset(szConditionIntro, NULL, sizeof(szConditionIntro));
    }
};

struct SAction
{ // ����
    short stActionID;                //����ID
    char szActionIntro[1024];        //��������
    int nValue[1];
    SAction()
    {
        memset(nValue, 0, sizeof(nValue));
        stActionID = -1;
        memset(szActionIntro, NULL, sizeof(szActionIntro));
    }
};

struct SMonsterTrigger 
{ // ����
    char szTriggerIntro[256];
    //char szTriggerRemark[2048];
    SEvent event;
    SCondition condition;
    SAction action;
    SMonsterTrigger()
    {
        memset(szTriggerIntro, NULL, sizeof(szTriggerIntro));
    }
};

//����AI������
class CMonsterAITrigger
{
public:
    CMonsterAITrigger();
    virtual ~CMonsterAITrigger();

    void AddMonsterAITrigger();

    void AddMonsterAITrigger( SMonsterTrigger mt );

    int GetMaxMonsterAITrigger();

    SMonsterTrigger* GetMonsterAITriggerByID( int id );

    void Clear();

    std::vector< SMonsterTrigger > m_vectorMonsterAITriggerStore;
    //std::map< std::string, int > m_mapAreaStore;
//private:
//    CStageDataLoader* m_pStageDataLoader;

};