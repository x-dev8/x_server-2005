#ifndef __COMMON_GAMEDEFINETALISMAN_H__
#define __COMMON_GAMEDEFINETALISMAN_H__

#pragma once

enum ETalismanQuality
{
    ETalismanQuality_None       ,
    ETalismanQuality_Normal     ,   // ��Ʒ
    ETalismanQuality_Fine       ,   // ��Ʒ
    ETalismanQuality_Refine     ,   // ��Ʒ
    ETalismanQuality_Fairy      ,   // ����
    ETalismanQuality_Deity      ,   // ����
    ETalismanQuality_Count   
};

// ������������ö��
enum ETalismanAttributeType
{
    TalismanAttr_None = 0        ,
    TalismanAttr_NimbusLimit     ,   //����ֵ����
    TalismanAttr_NimbusRestore   ,   //����ֵ�ظ�
    TalismanAttr_NimbusCost      ,   //����ֵ����
    TalismanAttr_SkillRange      ,   //ʩ����Χ
    TalismanAttr_SkillDamage     ,   //�����˺�
    TalismanAttr_SkillRestore    ,   //��������
    TalismanAttr_SkillCD         ,   //����CD
    TalismanAttr_StatusRate      ,   //����״̬�ɹ���
    TalismanAttr_StatusKeepTime  ,   //״̬����ʱ��
    
    TalismanAttr_MaxSize         ,   
};

static char* (g_szTalismanAttributeType[]) =
{
    "TalismanAttr_None"            ,
    "TalismanAttr_NimbusLimit"     ,   //����ֵ����
    "TalismanAttr_NimbusRestore"   ,   //����ֵ�ظ�
    "TalismanAttr_NimbusCost"      ,   //����ֵ����
    "TalismanAttr_SkillRange"      ,   //ʩ����Χ
    "TalismanAttr_SkillDamage"     ,   //�����˺�
    "TalismanAttr_SkillRestore"    ,   //��������
    "TalismanAttr_SkillCD"         ,   //����CD
    "TalismanAttr_StatusRate"      ,   //����״̬�ɹ���
    "TalismanAttr_StatusKeepTime"  ,   //״̬����ʱ��
};


#endif // __COMMON_GAMEDEFINETALISMAN_H__