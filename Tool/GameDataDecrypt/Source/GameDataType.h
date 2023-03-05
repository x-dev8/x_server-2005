/********************************************************************
    Filename:    GameDataType.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_GAMEDATATYPE_H__
#define __COMMON_GAMEDATATYPE_H__

#pragma once

#include "MeRTLibs.h"

typedef uint16 TGameObjectId;
typedef uint8  TCountryId;
typedef uint32 TStageId;

struct FPos3
{
    float x;
    float y;
    float z;
};

struct SFPos2
{
    SFPos2(){ x=0; y=0;}
    SFPos2( float fx, float fy){ x=fx; y=fy;}
    float x;
    float y;
};

struct SFDir3
{
    SFDir3()
    { eDir = 0; fDirX = 0; fDirY = 0;}

    SFDir3( float dx, float dy, int8 dir)
    { eDir = dir; fDirX = dx; fDirY = dy;}

    int8  eDir ; // 方向
    float fDirX; // X方向
    float fDirY; // Y方向
};

#endif //__COMMON_GAMEDATATYPE_H__
