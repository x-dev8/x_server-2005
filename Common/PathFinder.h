/********************************************************************
	Filename: 	PathFinder.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_PATHFINDER_H__
#define __COMMON_PATHFINDER_H__

#pragma once

#include "GlobalDef.h"
#include "astarpathfind.h"

//寻找路径
//直线寻找和AStar寻路
//
class CPathFinder :
    public CAstarPathFind
{
public:
    CPathFinder(void);
    virtual ~CPathFinder(void);
    //扩展。。。使用直线搜索方式
    //必须先调用Create
    short FindPathDirectly( int xSrc,int ySrc,int xDst,int yDst,short *stPath,short stUnNecessaryStepNumber );
    short FindPathDirectlyNoBlock( int xSrc,int ySrc,int xDst,int yDst,short *stPath,short stBufSize );
    short FindPathAstar( int xSrc,int ySrc,int xDst,int yDst,short *stPath,short stBufSize );
    short FindPathAstarS( int xSrc,int ySrc,int xDst,int yDst,short *stPath,short stBufSize );
};


#endif // __COMMON_PATHFINDER_H__
