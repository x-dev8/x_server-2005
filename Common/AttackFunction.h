/********************************************************************
    Filename:     AttackFunction.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_ATTACKFUNCTION_H__
#define __COMMON_ATTACKFUNCTION_H__

#pragma once

#include "GlobalDef.h"
#include "ItemDetailConfig.h"

namespace AttackFunction
{
    inline bool InAttackRange( ItemDefine::SItemSkill* pSkill,float fSrcX,float fSrcY,float fDstX,float fDstY,float fSrcBodySize,float fDstBodySize,float fWeaponAttackRange,float fRangeCorrect)
	    {// 判断某个技能攻击距离
        float fRange = 0;   // 可攻击距离    
        float fMinRange = 0;// 最小攻击距离

        fRange += fSrcBodySize;
        fRange += fDstBodySize;

        if ( pSkill )
        { // 技能存在
            if ( IsNormalAttack( pSkill->ustItemID ))
            { // 普通攻击技能 只算武器距离 
                fRange += fWeaponAttackRange; 
            }
            else
            { // 常规技能 只算技能距离
                fRange    += pSkill->fRangeCanCast;
                fMinRange += pSkill->fRangeCanCastMin;
            }
        }
        else
        { // 技能不存在 只算武器距离
            fRange += fWeaponAttackRange; 
        }

        fRange += fRangeCorrect;

        D3DXVECTOR3 distance( fDstX - fSrcX, fDstY - fSrcY, 0 );
        float fDistance = D3DXVec3Length( &distance );

		//让客户端的攻击距离比服务器近一个0.3的偏差，否则会卡技能
#ifdef GAME_CLIENT
		fDistance += 0.3f;
#endif

        if( fDistance <= fRange)
        { return true; }

        return false;
    }

    // 是否在施法的作用距离内
    inline bool InAttackRange( ItemDefine::SItemSkill* pSkill,const D3DXVECTOR3& vSrcPos,const D3DXVECTOR3& vDstPos,float fSrcBodySize,float fDstBodySize, float fWeaponAttackRange,float fRangeCorrect )
    {
        return InAttackRange( pSkill, vSrcPos.x, vSrcPos.y, vDstPos.x, vDstPos.y, fSrcBodySize, fDstBodySize, fWeaponAttackRange, fRangeCorrect );
    }

    // 是否在Aoe的作用距离内
    inline bool InAoeRange( const ItemDefine::SItemSkill* pSkillConfig, const D3DXVECTOR3& vSrcPos,const D3DXVECTOR3& vDstPos, float fDstBodySize, float fRangeCorrect )
    {
        float fRange = 0; // 可攻击距离

        // 身形
        fRange += fDstBodySize;

        if ( pSkillConfig )
        { fRange += pSkillConfig->fAOEradius; }

        // 修正
        fRange += fRangeCorrect;

        D3DXVECTOR3 distance( vDstPos.x - vSrcPos.x, vDstPos.y - vSrcPos.y, 0 );
        float fDistance = D3DXVec3Length( &distance );

        if( fDistance <= fRange)
        { return true; }

        return false;   
    }
}

using namespace AttackFunction;

#endif // __COMMON_ACHIEVEMANAGER_H__
