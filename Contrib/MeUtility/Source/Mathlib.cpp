#include "MathLib.h"
#include "FuncPerformanceLog.h"
#include "Dxsdk/d3dx9.h"

float Random()
{
	guardfunc
	return (float)rand()/RAND_MAX;
	unguard;
}

float Random( float a )
{
	guardfunc
	return a*Random();
	unguard;
}

float Random( float a, float b )
{
	guardfunc
	return a+Random( b-a );
	unguard;
}

int FloatCmp( float a, float b, float e )
{
	guardfunc
	if( fabsf( a-b ) < e )
		return 0;
	if( a < b )
		return -1;
	return 1;
	unguard;
}

// 阶乘
int Factorial( int n )
{
	guardfunc
	switch( n )
	{
	case 0:
		return 1;
	case 1:
		return 1;
	case 2:
		return 2*1;
	case 3:
		return 3*2*1;
	case 4:
		return 4*3*2*1;
	case 5:
		return 5*4*3*2*1;
	case 6:
		return 6*5*4*3*2*1;
	case 7:
		return 7*6*5*4*3*2*1;
	case 8:
		return 8*7*6*5*4*3*2*1;
	case 9:
		return 9*8*7*6*5*4*3*2*1;
	case 10:
		return 10*9*8*7*6*5*4*3*2*1;
	};
	int s = 1;
	for( int i = n; i > 0; i-- )
	{
		s *= i;
	}
	return s;
	unguard;
}
// 组合
int C( int n, int i )
{
	guardfunc
	return Factorial( n )/( Factorial( i )*Factorial( n-i ) );
	unguard;
}
// Bernstein基数
float Bernstein( int n, int i, float t )
{
	guardfunc
	return	C( n, i )*powf( t, (float)i )*powf( 1-t, (float)(n-i) );
	unguard;
}
// Riesenfeld多项式
float Riesenfeld( int m, int i, float t )
{
	guardfunc
	float s = 0;
	for( int k = 0; k <= m-i; k++ )
	{
		s += powf( -1, (float)k )*powf( t+m-i-k, (float)m )/( Factorial( k )*Factorial( m-k+1 ) );
	}
	return s*( m+1 );
	unguard;
}

void CubicSpline( float fControlPoint[], float t, float fTrackPoint[] )
{
	guardfunc
	fTrackPoint[0] = 0;
	fTrackPoint[1] = 0;
	fTrackPoint[2] = 0;
	for( int i = 0; i <= 3; i++ )
	{
		float Rmit = Riesenfeld( 3, i, t );
		fTrackPoint[0] += fControlPoint[i*3]*Rmit;
		fTrackPoint[1] += fControlPoint[i*3+1]*Rmit;
		fTrackPoint[2] += fControlPoint[i*3+2]*Rmit;
	}
	unguard;
}

int CreateSegment( float fControlPoint[], int nSegmentId, int nOrder, float dt, float fTrackPoint[] )
{
	guardfunc
	float end = 1.0f+dt;
	float p[3];
	int nSegmentPointCount = 0;
	for( float t = 0; t < end; t += dt )
	{
		p[0] = p[1] = p[2] = 0;
		for( int i = 0; i <= nOrder; i++ )
		{
			float Rmit = Riesenfeld( nOrder, i, t );
			p[0] += fControlPoint[(nSegmentId+i)*3]*Rmit;
			p[1] += fControlPoint[(nSegmentId+i)*3+1]*Rmit;
			p[2] += fControlPoint[(nSegmentId+i)*3+2]*Rmit;
		}
		fTrackPoint[nSegmentPointCount*3] = p[0];
		fTrackPoint[nSegmentPointCount*3+1] = p[1];
		fTrackPoint[nSegmentPointCount*3+2] = p[2];
		nSegmentPointCount++;
	}
	return nSegmentPointCount;
	unguard;
}

int CreateCurve( float fControlPoint[], int nCurveSegmentCount, int nOrder, float dt, float fTrackPoint[] )
{
	guardfunc
	int nCurvePointCount = 0;
	for( int k = 0; k < nCurveSegmentCount; k++ )
	{
		int nSegmentPointCount = CreateSegment( fControlPoint, k, nOrder, dt, &fTrackPoint[nCurvePointCount*3] );
		nCurvePointCount += nSegmentPointCount;
	}
	return nCurvePointCount;	
	unguard;
}

void BuildMatrixFromVectorToVector( float* v0, float* v1, float* m )
{
	D3DXVECTOR3 vUp( v0 );
	D3DXVECTOR3 vAxis( v1 );
	D3DXVECTOR3 vRight;
	D3DXVec3Cross( &vRight, &vAxis, &vUp  );
	float fDot = D3DXVec3Dot( &vUp, &vAxis );
	float fTheta = acosf( fDot );
	D3DXMatrixRotationAxis( (D3DXMATRIX*)m, &vRight, fTheta );
}

