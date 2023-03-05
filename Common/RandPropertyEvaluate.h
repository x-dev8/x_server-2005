/********************************************************************
Filename:    RandPropertyEvaluate.h
Description: �����������
*********************************************************************/

#ifndef __COMMON_RANDPROPERTYEVALUATE_H__
#define __COMMON_RANDPROPERTYEVALUATE_H__

#pragma once

#include "MeRTLibs.h"
#include <map>
#include <vector>

class CRandPropertyEvaluate
{
public:	
    enum EPropertyEvaluateType
    {
        PropertyEvaluate_Identify   = 0,    // ����
        PropertyEvaluate_OpenLight,         // ����
        PropertyEvaluateTypeCount,
    };

    enum EPropertyEvaluateEquipmentType
    {
        PropEvalEquipment_Aumour    = 0,    // ����
        PropEvalEquipment_Weapon,           // ����
        PropEvalEquipmentTypeCount,
    };

    struct SEquipmentEval
    {
        SEquipmentEval()
        {
            memset(this, 0, sizeof(*this) );
        }

        unsigned short  usEquipType;
        unsigned short  usLevel;
        unsigned short  usRandLevel;
        float           fEvalNormal;
        float           fEvalLiangPin;
        float           fEvalJingPin;
        float           fEvalJiPin;
        float           fEvalShenPin;
    };

    typedef std::vector<SEquipmentEval> vectorEquipmentEval;
    struct SPropertyEvaluate
    {
        unsigned short usEvalType;                                      // ��EPropertyEvaluateType
        vectorEquipmentEval _EquipmentEval[PropEvalEquipmentTypeCount];
    };

    CRandPropertyEvaluate();
    ~CRandPropertyEvaluate();

    void Reset();
    bool LoadConfig( const char* szFileName );
    // ���ݼ������ͣ�װ�����ͣ���װ���ȼ�����ȡ����ȼ�������-1��ʾ��ȡʧ��
    const SEquipmentEval* GetEquipmentEval( unsigned short usEvaluateType, unsigned short usEquipType, unsigned short usItemLevel );

private:
    typedef std::map< unsigned short, SPropertyEvaluate >              mapPropertyEvaluate;
    mapPropertyEvaluate m_mapPropertyEvaluate;
};

extern CRandPropertyEvaluate theRandPropEvaluate;

#endif // __COMMON_RANDPROPERTYEVALUATE_H__