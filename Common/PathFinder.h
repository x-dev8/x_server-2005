/********************************************************************
	Filename: 	PathFinder.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_PATHFINDER_H__
#define __COMMON_PATHFINDER_H__

#pragma once

#include "GlobalDef.h"
#include "astarpathfind.h"

//Ѱ��·��
//ֱ��Ѱ�Һ�AStarѰ·
//
class CPathFinder :
    public CAstarPathFind
{
public:
    CPathFinder(void);
    virtual ~CPathFinder(void);
    //��չ������ʹ��ֱ��������ʽ
    //�����ȵ���Create
    short FindPathDirectly( int xSrc,int ySrc,int xDst,int yDst,short *stPath,short stUnNecessaryStepNumber );
    short FindPathDirectlyNoBlock( int xSrc,int ySrc,int xDst,int yDst,short *stPath,short stBufSize );
    short FindPathAstar( int xSrc,int ySrc,int xDst,int yDst,short *stPath,short stBufSize );
    short FindPathAstarS( int xSrc,int ySrc,int xDst,int yDst,short *stPath,short stBufSize );
};


#endif // __COMMON_PATHFINDER_H__
