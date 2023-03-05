/********************************************************************
    Filename:    NpcNormal.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_NPCNORMAL_H__
#define __COMMON_NPCNORMAL_H__

#pragma once

#include "NpcBase.h"

class NpcNormal : public NpcBase,
                  public DNpcNormalChar,
                  INHERIT_POOL_PARAM( NpcNormal, gNpcPoolBatchSize )
{
public:
    DECLARE_POOL_FUNC( NpcNormal )

    NpcNormal();
    virtual ~NpcNormal(){}

    // IBaseCharProperty
    virtual SCharFightAttr* GetCharFightAttr(){ static SCharFightAttr instance; return &instance; }
    virtual void            SetHPMax( uint32 hpMax ) { _hpMax = hpMax; }
    virtual uint32          GetHPMax()               { return _hpMax; }
    virtual float           GetMoveSpeed()              { return _speed;  }
    virtual void            SetMoveSpeed( float fMove ) { _speed = fMove; }

protected:
    virtual void Prepare();
};

#endif // __COMMON_NPCNORMAL_H__