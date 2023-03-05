/********************************************************************
    Filename:    GameDefineLogic.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __PROJECTCOMMON_GAMEDEFINELOGIC_H__
#define __PROJECTCOMMON_GAMEDEFINELOGIC_H__

#pragma once

#pragma pack( push, 1 )

#include "MeRTLibs.h"

struct SWorldPos
{
    float fX;
    float fY;

    SWorldPos() : fX(0.0f), fY(0.0f) 
    {}

    SWorldPos(float fXX, float fYY): fX(fXX),fY(fYY)
    {}

    void Reset()
    { fX = 0.0f; fY = 0.0f; };

    SWorldPos& operator=(SWorldPos const& rhs)
    {
        fX = rhs.fX;
        fY = rhs.fY;
        return *this;
    }

    bool operator==(SWorldPos& Ref)
    { return (fabs(fX-Ref.fX)+fabs(fY-Ref.fY))<0.0001f; }

    bool operator==(const SWorldPos& Ref)
    { return (fabs(fX-Ref.fX)+fabs(fY-Ref.fY))<0.0001f; }
};

#pragma pack( pop )

#endif // __PROJECTCOMMON_GAMEDEFINELOGIC_H__