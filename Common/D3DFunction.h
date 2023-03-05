/********************************************************************
    Filename:     D3DFunction.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_D3DFUNCTION_H__
#define __COMMON_D3DFUNCTION_H__

#pragma once

#include "GlobalDef.h"

namespace D3DFunction
{
    inline D3DXVECTOR3 GetTargetPos( D3DXVECTOR3& vSrcPos, D3DXVECTOR3& vSrcDir, float fAngle, float fCorrect )
    {
        D3DXMATRIX rotMatrix;
        D3DXMatrixRotationZ( &rotMatrix, fAngle );

        // 目标点朝向
        D3DXVECTOR3 vTargetPos;
        D3DXVec3TransformNormal( &vTargetPos, &vSrcDir, &rotMatrix );

        // 计算目标点
        vTargetPos = vSrcPos + vTargetPos * fCorrect;

        return vTargetPos;
    }

    inline D3DXVECTOR3 GetTargetPos( D3DXVECTOR3& vSrcPos, float fDirX, float fDirY, float fAngle, float fCorrect )
    {

        D3DXVECTOR3 vSrcDir( fDirX, fDirY, 0 );

        return GetTargetPos( vSrcPos, vSrcDir, fAngle, fCorrect );
    }

    inline D3DXVECTOR3 GetTargetPos( float fPosX, float fPosY, float fPosZ, float fDirX, float fDirY, float fAngle, float fCorrect )
    {

        D3DXVECTOR3 vSrcPos( fPosX, fPosY, fPosZ );
        D3DXVECTOR3 vSrcDir( fDirX, fDirY, 0 );

        return GetTargetPos( vSrcPos, vSrcDir, fAngle, fCorrect );
    }
    
}

using namespace D3DFunction;

#endif // __COMMON_D3DFUNCTION_H__
