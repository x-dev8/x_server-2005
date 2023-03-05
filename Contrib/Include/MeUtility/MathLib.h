/********************************************************************
	Filename: 	MathLib.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_MATHLIB_H__
#define __UTILITY_MATHLIB_H__

#pragma once

#include "MeRTLibs.h"

namespace Math
{
	enum 
	{
		left, 
		bottom, 
		right,
		top
	};
}

enum
{
    XY,
    YZ,
    XZ
};

float Random();
float Random( float a );
float Random( float a, float b );
int   FloatCmp( float a, float b, float e = 0.0001f );
int   Factorial( int n );
int   C( int n, int i );
float Bernstein( int n, int i, float t );
float Riesenfeld( int m, int i, float t );
void  CubicSpline( float fControlPoint[], float t, float fTrackPoint[] );
int   CreateSegment( float fControlPoint[], int nSegmentId, int nOrder, float dt, float fTrackPoint[] );
int   CreateCurve( float fControlPoint[], int nCurveSegmentCount, int nOrder, float dt, float fTrackPoint[] );
void  BuildMatrixFromVectorToVector( float* v0, float* v1, float* m );

#endif // __COMMON_MATHLIB_H__
