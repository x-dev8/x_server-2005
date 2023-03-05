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
	    {// �ж�ĳ�����ܹ�������
        float fRange = 0;   // �ɹ�������    
        float fMinRange = 0;// ��С��������

        fRange += fSrcBodySize;
        fRange += fDstBodySize;

        if ( pSkill )
        { // ���ܴ���
            if ( IsNormalAttack( pSkill->ustItemID ))
            { // ��ͨ�������� ֻ���������� 
                fRange += fWeaponAttackRange; 
            }
            else
            { // ���漼�� ֻ�㼼�ܾ���
                fRange    += pSkill->fRangeCanCast;
                fMinRange += pSkill->fRangeCanCastMin;
            }
        }
        else
        { // ���ܲ����� ֻ����������
            fRange += fWeaponAttackRange; 
        }

        fRange += fRangeCorrect;

        D3DXVECTOR3 distance( fDstX - fSrcX, fDstY - fSrcY, 0 );
        float fDistance = D3DXVec3Length( &distance );

		//�ÿͻ��˵Ĺ�������ȷ�������һ��0.3��ƫ�����Ῠ����
#ifdef GAME_CLIENT
		fDistance += 0.3f;
#endif

        if( fDistance <= fRange)
        { return true; }

        return false;
    }

    // �Ƿ���ʩ�������þ�����
    inline bool InAttackRange( ItemDefine::SItemSkill* pSkill,const D3DXVECTOR3& vSrcPos,const D3DXVECTOR3& vDstPos,float fSrcBodySize,float fDstBodySize, float fWeaponAttackRange,float fRangeCorrect )
    {
        return InAttackRange( pSkill, vSrcPos.x, vSrcPos.y, vDstPos.x, vDstPos.y, fSrcBodySize, fDstBodySize, fWeaponAttackRange, fRangeCorrect );
    }

    // �Ƿ���Aoe�����þ�����
    inline bool InAoeRange( const ItemDefine::SItemSkill* pSkillConfig, const D3DXVECTOR3& vSrcPos,const D3DXVECTOR3& vDstPos, float fDstBodySize, float fRangeCorrect )
    {
        float fRange = 0; // �ɹ�������

        // ����
        fRange += fDstBodySize;

        if ( pSkillConfig )
        { fRange += pSkillConfig->fAOEradius; }

        // ����
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
