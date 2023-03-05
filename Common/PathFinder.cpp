#include "Pathfinder.h"
#include "FuncPerformanceLog.h"
#include <assert.h>

CPathFinder::CPathFinder(void)
{
	guardfunc
	unguard
}

CPathFinder::~CPathFinder(void)
{
	guardfunc
	unguard
}

int GetDirFromTwoPoint( int xSrc, int ySrc,int xDst, int yDst )
{
	guardfunc

	int dx = xDst - xSrc;
	int dy = yDst - ySrc;

	assert( abs(dx) <= 1 && abs( dy ) <= 1 );

	switch( dx )
	{
	case 0:
		switch( dy )
		{
		case 0:
			assert( false );
			break;
		case -1:
			return DIR_270;
			break;
		case 1:
			return DIR_90;
			break;
		}
		break;
	case -1:
		switch( dy )
		{
		case 0:
			return DIR_180;
			break;
		case -1:
			return DIR_225;
			break;
		case 1:
			return DIR_135;
			break;
		}
		break;
	case 1:
		switch( dy )
		{
		case 0:
			return DIR_0;
			break;
		case -1:
			return DIR_315;
			break;
		case 1:
			return DIR_45;
			break;
		}
		break;
	}
	assert( false );
	return -1;
	unguard
}

short CPathFinder::FindPathDirectly( int xSrc,int ySrc,int xDst,int yDst,short *stPath,short stUnNecessaryStepNumber )
{
	guardfunc

	float dx = (float)(xDst-xSrc);
	float dy = (float)(yDst-ySrc);

	int iXOff = 0;
	int iYOff = 0;

	if ( dx >= 0 )
	{
		iXOff = 1;
	}
	else
	{
		iXOff = -1;
	}

	if ( dy >= 0 )
	{
		iYOff = 1;
	}
	else
	{
		iYOff = -1;
	}

	if( dx*dy > 40000 )
		return 0;

	int idx = abs(dx);
	int idy = abs(dy);

	//something impossible
	//POINT ptLast = { -1, -1 };
	POINT pts[200];
	//memset( pts, NULL, sizeof(pts) );
	int iPathSizeMin = 0;
	int iPathSizeMax = 0;
	POINT pt;
	//int i;
	//pts[0] = ptLast;
	pts[0].x = xSrc;
	pts[0].y = ySrc;

	if ( idx >= idy )
	{
		iPathSizeMin = idy;
		iPathSizeMax = idx;
	}
	else
	{
		iPathSizeMin = idx;
		iPathSizeMax = idy;
	}

	if ( stUnNecessaryStepNumber >= iPathSizeMax )
	{
		return 0;
	}
	else
	{
		if ( iPathSizeMax - stUnNecessaryStepNumber > iPathSizeMin )
		{
			for ( int i = 0; i < iPathSizeMin; i++ )
			{
				pts[i + 1].x = pts[i].x + iXOff;
				pts[i + 1].y = pts[i].y + iYOff;
			}

			if ( idx > idy )
			{
				iYOff = 0;
			}
			else
			{
				iXOff = 0;
			}

			for ( int i = iPathSizeMin; i < (iPathSizeMax - stUnNecessaryStepNumber); i++ )
			{
				pts[i + 1].x = pts[i].x + iXOff;
				pts[i + 1].y = pts[i].y + iYOff;
			}
		}
		else
		{
			for ( int i = 0; i < iPathSizeMin; i++ )
			{
				pts[i + 1].x = pts[i].x + iXOff;
				pts[i + 1].y = pts[i].y + iYOff;
			}
		}
	}

	if( iPathSizeMax > 256 )
	{
		return 0;
	}

	for( int i = 0 ;i < iPathSizeMax - stUnNecessaryStepNumber; i++ )
	{
		stPath[ i ] = GetDirFromTwoPoint( pts[ i ].x,pts[ i ].y,
			pts[i + 1].x,pts[i + 1].y );
		if( !MoveAble( (short)pts[i + 1].x, (short)pts[i + 1].y ) )
			return i;
	}
	return iPathSizeMax - stUnNecessaryStepNumber;
	unguard
}

short CPathFinder::FindPathDirectlyNoBlock( int xSrc,int ySrc,int xDst,int yDst,short *stPath,short stBufSize )
{
	guardfunc
	// 计算目标点和出发点的差值
	float dx = (float)(xDst-xSrc);
	float dy = (float)(yDst-ySrc);

	// 计算X,Y的增量的正负
	int iXOff = 0;
	int iYOff = 0;

	if ( dx >= 0 )
	{
		iXOff = 1;
	}
	else
	{
		iXOff = -1;
	}

	if ( dy >= 0 )
	{
		iYOff = 1;
	}
	else
	{
		iYOff = -1;
	}

	//if( dx*dy > 40000 )
	//	return 0;

	int idx = abs(dx);
	int idy = abs(dy);

	//something impossible
	//POINT ptLast = { -1, -1 };
	POINT pts[200];
	//memset( pts, NULL, sizeof(pts) );
	int iPathSizeMin = 0;
	int iPathSizeMax = 0;
	POINT pt;
	//int i;
	//pts[0] = ptLast;
	pts[0].x = xSrc;
	pts[0].y = ySrc;

	if ( idx >= idy )
	{
		iPathSizeMin = idy;
		iPathSizeMax = idx;
	}
	else
	{
		iPathSizeMin = idx;
		iPathSizeMax = idy;
	}

	for ( int i = 0; i < iPathSizeMin; i++ )
	{
		pts[i + 1].x = pts[i].x + iXOff;
		pts[i + 1].y = pts[i].y + iYOff;
	}

	if ( idx > idy )
	{
		iYOff = 0;
	}
	else
	{
		iXOff = 0;
	}

	for ( int i = iPathSizeMin; i < iPathSizeMax; i++ )
	{
		pts[i + 1].x = pts[i].x + iXOff;
		pts[i + 1].y = pts[i].y + iYOff;
	}

	if( iPathSizeMax >= stBufSize )
		return 0;

	for(int i = 0 ;i < iPathSizeMax; i++ )
	{
		stPath[ i ] = GetDirFromTwoPoint( pts[ i ].x,pts[ i ].y,
			pts[i + 1].x,pts[i + 1].y );
	}
	return iPathSizeMax;
	unguard
}

short CPathFinder::FindPathAstar( int xSrc,int ySrc,int xDst,int yDst,short *stPath,short stBufSize )
{
	guardfunc
	if( 0 != FindPath( xSrc,ySrc,xDst,yDst ) )
		return 0;
	short stLen = GetPathLengh();
	if( stLen < 1 )
		return 0;
	//路径超长
	if( stLen > 500 || stLen > stBufSize )
	{
		//assert( false );
		return 0;
	}
	short stPoints[ 500*2 ];
	GetPosPath( stPoints,500 );
	//
	for( int i = 0 ;i < stLen ; i ++ )
	{
		stPath[ i ] = GetDirFromTwoPoint( stPoints[ 2*i ],stPoints[ 2*i + 1 ],
			stPoints[ 2*i + 2 ],stPoints[ 2*i + 3 ] );
	}
	return stLen;
	unguard
}

short CPathFinder::FindPathAstarS( int xSrc,int ySrc,int xDst,int yDst,short *stPath,short stBufSize )
{
	guardfunc
    CAstarPathFind::m_dwShortFindStartTime = HQ_TimeGetTime();
    if( 0 != FindPathShort( xSrc,ySrc,xDst,yDst ) )
        return 0;
    short stLen = GetPathLengh();
    if( stLen < 1 )
        return 0;
    //路径超长
    if( stLen > 500 || stLen > stBufSize )
    {
        //assert( false );
        return 0;
    }
    short stPoints[ 500*2 ];
    GetPosPath( stPoints,500 );
    //
    for( int i = 0 ;i < stLen ; i ++ )
    {
        stPath[ i ] = GetDirFromTwoPoint( stPoints[ 2*i ],stPoints[ 2*i + 1 ],
            stPoints[ 2*i + 2 ],stPoints[ 2*i + 3 ] );
    }
	return stLen;
	unguard
}
