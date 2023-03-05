#ifndef __COMMON_GAMEDEFINEPET_H__
#define __COMMON_GAMEDEFINEPET_H__

#pragma once

#include "GlobalDef.h"

#define PET_LEVELUP_BASEATTR            1   // ��������������Ե�
#define PET_LEVELUP_POTENTIALPOINT      4   // �����������Ǳ����
#define PET_LOYALTY_LIMIT               100 // ������ֶ�����
#define PET_LEVEL_OVERTOP_MAX           5   // ����ȼ���������� 5��

enum EPetBreedConstDefine
{
    //////////////////////////////////////////////////////////////////////////
    // ��ֳ����״̬
    EPetBreed_StatusInit = 0,
    EPetBreed_StatusStart  ,  
    EPetBreed_StatusLock   ,  
    EPetBreed_StatusConfirm,  
    /////////////////////////////////////////////////////////////
    // ��ֳ��������
    EPetBreed_FinishSuccess = 0 ,       
    EPetBreed_FinishFailed      ,
    EPetBreed_FinishTimeOut     ,           
    EPetBreed_FinishCancel      ,            
    EPetBreed_FinishOutLine     ,
    EPetBreed_FinishHasBreed    ,
};

//�����Ը�	
//��С	cowardice
//����	reticence
//�ҳ�	ligeance
//����	prudence
//����	valor
enum EPetCharacterize
{
    EPetChar_Cowardice   ,
    EPetChar_Reticence   ,
    EPetChar_Ligeance    ,
    EPetChar_Prudence    ,
    EPetChar_Valor       ,
    EPetChar_Count            
};

enum EPetQuality
{
    EPetQuality_None      ,
    EPetQuality_Normal    ,
    EPetQuality_Advance   ,
    EPetQuality_Flaunt    ,
    EPetQuality_Count   
};

enum EPetGrowthRateStar
{
    EPetGrowth_One       ,
    EPetGrowth_Two       ,
    EPetGrowth_Three     ,
    EPetGrowth_Four      ,
    EPetGrowth_Five      ,
    EPetGrowth_Count
};

enum EPetFood
{
    EPetFood_Meat       ,   // ��
    EPetFood_Grass      ,   // ��
    EPetFood_Insect     ,   // ����
    EPetFood_Grain      ,   // ����
    EPetFood_Count
};

static char* (g_szPetFoodType[]) = 
{
    "Meat"      , 
    "Grass"     , 
    "Insect"    , 
    "Grain"     , 
};

enum EPetAttackType
{
    EPetAttack_Unkonw  , // û���κν���
    EPetAttack_Physical, // �﹥
    EPetAttack_Magic   , // ħ��
    EPetAttack_Both    , // �����ħ�������˺�����
};

enum EPetSkillCategory
{
    EPetSkillCategory_ManualAttack      =   1,  // ����
    EPetSkillCategory_AssistAttack      =   2,  // ��������
    EPetSkillCategory_Restore           =   3,  // ����
    EPetSkillCategory_AssistDefend      =   4,  // ��������
    EPetSkillCategory_Relive            =   5,  // ����
    EPetSkillCategory_AutoAttack        =   6,  // �Զ�����
    EPetSkillCategory_PetAttr           =   7,  // ���ӳ�������
    EPetSkillCategory_MasterAttr        =   8,  // ������������
    EPetSkillCategory_AssistMaster      =   9,  // ���������˺�
	EPetSkillCategory_Aptitude			=   10, // ������
    EPetSkillCategory_MaxSize           =   11,
};

enum EPetSource
{
    EPetSource_Other = 0 ,   //����
    EPetSource_Skill     ,   //��׽
    EPetSource_Breed     ,   //��ֳ
    EPetSource_Stall     ,   //����
};

enum EDisappearSource
{
    EDS_Discard     ,   // ����
    EDS_SavvyUp     ,   // ��������
    EDS_Breed       ,   // ��ֳ
    EDS_Stall       ,   // ����
};

//�ٻ������
struct SSummonPet
{
    SSummonPet()
    {
        petId       = InvalidGameObjectId;
        petAIType   = ePetCommandAI;
        skillId     = 0;
    }

    void Clear()
    {
        petId       = InvalidGameObjectId;
        petAIType   = ePetCommandAI;
        skillId     = 0;
    }

    GameObjectId  petId;   //����ID
    uint8   petAIType   ;   //��������
    uint16  skillId     ;   //�ٻ�����

    bool operator == ( uint16 id ) { return skillId == id; }
};

#endif // __COMMON_GAMEDEFINEPET_H__