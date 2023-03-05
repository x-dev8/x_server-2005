#ifndef __MATH_H__
#define __MATH_H__

#include "MeRTLibs.h"
#include <windows.h>
#include "Vector.h"

//#define PlaneFromPoints( plane, v0, v1, v2 ) D3DXPlaneFromPoints( (D3DXPLANE*)plane, (D3DXVECTOR3*)v0, (D3DXVECTOR3*)v1, (D3DXVECTOR3*)v2 )
//#define MXM( a, b, c )	D3DXMatrixMultiply( (D3DXMATRIX*)a, (D3DXMATRIX*)b, (D3DXMATRIX*)c )
//#define V3XM( a, b, c )	D3DXVec3TransformCoord( (D3DXVECTOR3*)a, (D3DXVECTOR3*) b, (D3DXMATRIX*)c )
//#define MINVERSE( mat )	D3DXMatrixInverse( (D3DXMATRIX*)mat, NULL, (D3DXMATRIX*)mat )
//#define IntersectTri( p0, p1, p2, pos, dir, u, v, dist ) D3DXIntersectTri( (D3DXVECTOR3*)p0, (D3DXVECTOR3*)p1, (D3DXVECTOR3*)p2, (D3DXVECTOR3*)pos, (D3DXVECTOR3*)dir, u, v, dist )
#define PlaneFromPoints( plane, v0, v1, v2 ) D3DXPlaneFromPoints( (D3DXPLANE*)plane, (D3DXVECTOR3*)v0, (D3DXVECTOR3*)v1, (D3DXVECTOR3*)v2 )
#define MXM( a, b, c )	D3DXMatrixMultiply( (D3DXMATRIX*)a, (D3DXMATRIX*)b, (D3DXMATRIX*)c )
#define V3XM( a, b, c )	D3DXVec3TransformCoord( (D3DXVECTOR3*)a, (D3DXVECTOR3*) b, (D3DXMATRIX*)c )
#define MINVERSE( mat )	D3DXMatrixInverse( (D3DXMATRIX*)mat, NULL, (D3DXMATRIX*)mat )
#define IntersectTri( p0, p1, p2, pos, dir, u, v, dist ) D3DXIntersectTri( (D3DXVECTOR3*)p0, (D3DXVECTOR3*)p1, (D3DXVECTOR3*)p2, (D3DXVECTOR3*)pos, (D3DXVECTOR3*)dir, u, v, dist )


// rect float rect[4]
// rect[0]-left, rect[1]-bottom, rect[2]-right, rect[3]-top
// counterclockwize order
#define PI	3.1415926f
#define PI2 (PI*2.0f)
#define PIOVER180	(PI/180)
#define PIUNDER180	(180/PI)


//int FloatCmp ( float f0, float f1, float e = 0.00001f );
bool InsideRect( Vector2 p, Vector2 rect[4] );
bool ClipHorizon( Vector2 p[2], Vector2 horizon[2], Vector2* out, float* s, float* u );
bool ClipVertical( Vector2 p[2], Vector2 vertical[2], Vector2* out, float* s, float* v );
bool OutLine( Vector2& v0, Vector2& v1, Vector2& p );
bool InsideTri( Vector2 tri[3], Vector2 vt, float *u, float* v );
void SwapXY( Vector& v );
void SwapYZ( Vector& v );
void SwapXZ( Vector& v );
//float Random();
Vector ProjPoint2Screen( const Vector& p, const MeMatrix& matView, const MeMatrix& matProj, int nScreenWidth, int nScreenHeight );
RECT MakeRect( POINT pt0, POINT pt1 );
Vector RandomDirection();
//float Random( float a, float b = 0 );
//// RealRender added 2002.12.17 for spline
//int Factorial( int n );
//int C( int n, int i );
//float Bernstein( int n, int i, float t );
//float Riesenfeld( int m, int i, float t );
float SinTable( int nDegree );
float CosTable( int nDegree );
float TanTable( int nDegree );
void Min( Vector* v0, Vector* v1, Vector* m );
void Max( Vector* v0, Vector* v1, Vector* m );
float Shade( Vector& vLightPos, Vector& vNormal );

// inline function
inline float Slerp( float a, float b, float t ){ return a+t*(b-a); }
inline void MakeATextureTileUV(	
							int nRow, 
							int nCol,	
							int nTileId, 
							float* u0, 
							float* v0,
							float* u1, 
							float* v1,
							float* u2, 
							float* v2,
							float* u3, 
							float* v3 )
{
	float du = 1.0f/nCol;
	float dv = 1.0f/nRow;

	int row = nTileId/nCol;
	int col = nTileId%nCol;


	*u0 = du*col;
	*v0 = dv*row+dv;
	*u1 = du*col;
	*v1 = dv*row;
	*u2 = du*col+du;
	*v2 = dv*row+dv;
	*u3 = du*col+du;
	*v3 = dv*row;
}

template< class T > inline T Clamp( const T X, const T Min, const T Max )
{
	return X<Min ? Min : X<Max ? X : Max;
}

extern void MirrorMatrix( int nAxis, MeMatrix* pMatrix  );
extern float DegreeToRad( int nDegree );

#endif // __MATH_H__
