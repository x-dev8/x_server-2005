/********************************************************************
Filename:    RandPropertyEvaluate.h
Description: 随机属性评估
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
        PropertyEvaluate_Identify   = 0,    // 鉴定
        PropertyEvaluate_OpenLight,         // 开光
        PropertyEvaluateTypeCount,
    };

    enum EPropertyEvaluateEquipmentType
    {
        PropEvalEquipment_Aumour    = 0,    // 防具
        PropEvalEquipment_Weapon,           // 武器
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
        unsigned short usEvalType;                                      // 见EPropertyEvaluateType
        vectorEquipmentEval _EquipmentEval[PropEvalEquipmentTypeCount];
    };

    CRandPropertyEvaluate();
    ~CRandPropertyEvaluate();

    void Reset();
    bool LoadConfig( const char* szFileName );
    // 根据鉴定类型，装备类型，和装备等级，获取随机等级，返回-1表示获取失败
    const SEquipmentEval* GetEquipmentEval( unsigned short usEvaluateType, unsigned short usEquipType, unsigned short usItemLevel );

private:
    typedef std::map< unsigned short, SPropertyEvaluate >              mapPropertyEvaluate;
    mapPropertyEvaluate m_mapPropertyEvaluate;
};

extern CRandPropertyEvaluate theRandPropEvaluate;

#endif // __COMMON_RANDPROPERTYEVALUATE_H__