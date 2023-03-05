/********************************************************************
    Filename:     ProcessCharInfo.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_PROCESSCHARINFO_H__
#define __COMMON_PROCESSCHARINFO_H__

#pragma once

#include "GlobalDef.h"

class ProcessCharInfo
{
public:
    static std::string ProcessProfession(unsigned short usArmsType);
    static void   BaseAttrEffectFightAttr( uint8 baseType, uint16 part, SBaseAttrType& baseValue, uint16 armType, SCharFightAttr& figtAttr, bool bAdd = true );
    static uint16 ActivityMax  ( uint16 level ) { return 45 + level * 15 ; }     // 活力最大值
    static uint16 VigorMax     ( uint16 level ) { return 45 + level * 5 ; }     // 精力力最大值
    static float  StdDaoxing   ( uint16 level ) { return level * level * level * 0.3f; } // 标准道行
};

#endif // __COMMON_PROCESSCHARINFO_H__
