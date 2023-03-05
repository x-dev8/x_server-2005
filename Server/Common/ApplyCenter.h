/********************************************************************
    Filename:    ApplyCenter.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_APPLYCENTER_H__
#define __GAMESERVER_APPLYCENTER_H__

#pragma once

#include "Formula.h"

class BaseCharacter;

class ApplyCenter
{
public:
    // ª÷∏¥¿‡–Õ
    enum EnumRestoreType
    {
        ERT_HP, // hp
        ERT_MP, // mp
    };

public:
    /////////////////////////////////////////////////////////////////////////
    static bool ApplyAttack( BaseCharacter* pCharTarget, BaseCharacter* pCharAttacker, const ItemDefine::SItemSkill* pSkillConfig, 
                             CFormula::SResult* pTargetFormula, CFormula::SResult* pAttackFormula, OUT SAttTargetResult* pAttTargetResult);
    
    static bool ApplyTargetFormule( BaseCharacter* pTargetChar, BaseCharacter* pSourceChar, float fPercentPlus, uint16 eventValue, 
                                    CFormula::SResult* pTargetFormulaResult, CFormula::SResult* pSourceFormulaResult, 
                                    OUT SAttTargetResult* pAttTargetResult, OUT bool& bTargetBuffHaveChanged, OUT bool& bSourceBuffHaveChanged );

    static bool ApplySourceFormule( BaseCharacter* pTargetChar, BaseCharacter* pSourceChar, float fPercentPlus, 
                                    CFormula::SResult* pSourceFormulaResult, 
                                    OUT SAttTargetResult* pAttTargetResult, OUT bool& bTargetBuffHaveChanged, OUT bool& bSourceBuffHaveChanged );
    
    static bool ApplyHPRestore( BaseCharacter* pChar, CFormula::SResult* pResult, SAttTargetResult* pClientResult, bool bAttacker );    
    static bool ApplyMPRestore( BaseCharacter* pChar, CFormula::SResult* pResult, SAttTargetResult* pClientResult, bool bAttacker );

    static bool ApplyXPRestore( BaseCharacter* pTarget, CFormula::SResult* pResult, bool bAttacker );

    static bool ApplyPhysicDamage( BaseCharacter* pChar, CFormula::SResult* pResult, SAttTargetResult* pClientResult, bool bAttacker );
    static bool ApplyMagicDamage(  BaseCharacter* pChar, CFormula::SResult* pResult, SAttTargetResult* pClientResult, bool bAttacker );
    
    static bool ApplyBalanceTypeNone( BaseCharacter* pChar, CFormula::SResult* pResult, SAttTargetResult* pClientResult, bool bAttacker );

    static bool Restore( EnumRestoreType type, BaseCharacter* pChar, int iRestore );    
    
};

#endif // __GAMESERVER_APPLYCENTER_H__
