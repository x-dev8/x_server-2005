#include "Me3d/Me3d.h"
#include "Me3d/MathEx.h"
#include <math.h>
#include "Dxsdk/d3dx9mesh.h"
#include "Me3d/MathLib.h"
#include "Me3d/Vector.h"
#include "Me3d/Quaternion.h"
#include "FuncPerformanceLog.h"
#include "3dsmax/gfloat.h"

//�������12���������
const int g_nBoxFace[12*3] = 
{
	// top
	0, 1, 2,
	2, 1, 3,
	//0, 2, 1,
	//2, 3, 1,
	// bottom
	6, 7, 4,
	4, 7, 5,
	//6, 4, 7,
	//4, 5, 7,
	
	// left
	0, 2, 4,
	4, 2, 6,
	//0, 4, 2,
	//4, 6, 2,
	// right
	3, 1, 7,
	7, 1, 5,
	//3, 7, 1,
	//7, 5, 1,
	// front
	2, 3, 6,
	6, 3, 7,
	//2, 6, 3,
	//6, 7, 3,
	// back
	0, 1, 5,
	5, 0, 4
	//1, 5, 0,
	//5, 4, 0,


};
// box�ı�����
const int g_nBoxEdge[12][2] = 
{
	0,	1,
	1,	3, 
	3,	2,
	2,	0,
	4,	5,
	5,	7,
	7,	6,
	6,	4,
	2,	6,
	3,	7,
	0,	4,
	1,	5
};




//float Random()
//{
//	return (float)rand()/RAND_MAX;
//}
Vector RandomDirection()
{
	guardfunc;
	Vector vDirection( -0.5+Random(), -0.5+Random(), -0.5+Random() );
	vDirection.normalize();
	return vDirection;
	unguard;
}
//float Random( float a, float b )
//{
//	return a+Random()*( b-a );
//}
//int FloatCmp ( float f0, float f1, float e )
//{
//	if ( fabs ( f0 - f1 ) < e )
//		return 0;
//	if ( f0 > f1 )
//		return 1;
//	return -1;
//}

bool InsideRect( Vector2 p, Vector2 rect[4] )
{
	guardfunc;
	if( FloatCmp( p.x, rect[Math::left].x ) < 0 )return false;
	if( FloatCmp( p.x, rect[Math::right].x ) > 0 )return false;
	if( FloatCmp( p.y, rect[Math::top].y ) < 0 )return false;
	if( FloatCmp( p.y, rect[Math::bottom].y ) > 0 )return false;
	return true;
	unguard;
}

// ��ˮƽ�߲ü���
// s->�����ڲü��߶εĲ���t
// u->������ˮƽ�߶εĲ���
bool ClipHorizon( Vector2 p[2], Vector2 horizon[2], Vector2* out, float* s, float* u )
{
	guardfunc;
	float y = horizon[0].y;
	if( FloatCmp( p[0].y, p[1].y ) == 0 )
		return false;
	if( p[0].y < y && p[1].y < y )return false;
	if( p[0].y > y && p[1].y > y )return false;
	float t = ( y-p[0].y )/( p[1].y-p[0].y );
	if( t < 0 || t > 1 )return false;
	*s = t;
	float x = p[0].x+t*( p[1].x-p[0].x );
	t = ( x-horizon[0].x )/( horizon[1].x-horizon[0].x );
	if( t < 0 || t > 1 )return false;
	out->y = y;
	out->x = x;
	*u = t;
	return true;
	unguard;
}
// �봹ֱ�߲ü���
// s->�����ڲü��߶εĲ���t
// u->�����ڴ�ֱ�߶εĲ���
bool ClipVertical( Vector2 p[2], Vector2 vertical[2], Vector2* out, float* s, float* v )
{
	guardfunc;
	float x = vertical[0].x;
	if( FloatCmp( p[0].x, p[1].x ) == 0 )return false;
	if( p[0].x < x && p[1].x < x )return false;
	if( p[0].x > x && p[1].x > x )return false;
	float t = ( x-p[0].x )/( p[1].x-p[0].x );
	if( t < 0 || t > 1 )return false;
	*s = t;
	float y = p[0].y+t*( p[1].y-p[0].y );
	t = ( y-vertical[0].y )/( vertical[1].y-vertical[0].y );
	if( t < 0 || t > 1 )return false;
	out->y = y;
	out->x = x;
	*v = t;
	return true;
	unguard;
}

bool OutLine( Vector2& v0, Vector2& v1, Vector2& p )
{
	guardfunc;
	Vector2 t;
	t.x = p.x-v0.x;
	t.y = p.y-v0.y;
	Vector2 s;
	s.x = v1.x-v0.x;
	s.y = v1.y-v0.y;
	
	if( FloatCmp( s.x, 0 ) == 0 )
	{
		if( FloatCmp( s.y, 0 ) > 0 )
		{
			if( FloatCmp( t.x, 0 ) > 0 )
				return false;
			return true;
		}
		else
		{
			if( FloatCmp( t.x, 0 ) < 0 )
				return false;
			return true;
		}
	}

	if( FloatCmp( s.y, 0 ) == 0 )
	{
		if( FloatCmp( s.x, 0 ) > 0 )
		{
			if( FloatCmp( t.y, 0 ) > 0 )
				return true;
			return false;
		}
		else
		{
			if( FloatCmp( t.y, 0 ) < 0 )
				return true;
			return false;
		}
	}
	
	float k = ( v1.y-v0.y )/( v1.x-v0.x );
	if( FloatCmp( k*t.x-t.y, 0 ) > 0 )
	{
		if( FloatCmp( s.x, 0 ) > 0 &&
			FloatCmp( s.y, 0 ) > 0 )
			return false;
		if( FloatCmp( s.x, 0 ) < 0 &&
			FloatCmp( s.y, 0 ) > 0 )
			return true;
		if( FloatCmp( s.x, 0 ) < 0 &&
			FloatCmp( s.y, 0 ) < 0 )
			return true;
		if( FloatCmp( s.x, 0 ) > 0 &&
			FloatCmp( s.y, 0 ) < 0 )
			return false;
		return true;
	}
	else
	{
		if( FloatCmp( s.x, 0 ) > 0 &&
			FloatCmp( s.y, 0 ) > 0 )
			return true;
		if( FloatCmp( s.x, 0 ) < 0 &&
			FloatCmp( s.y, 0 ) > 0 )
			return false;
		if( FloatCmp( s.x, 0 ) < 0 &&
			FloatCmp( s.y, 0 ) < 0 )
			return false;
		if( FloatCmp( s.x, 0 ) > 0 &&
			FloatCmp( s.y, 0 ) < 0 )
			return true;
		return true;
	}
	unguard;	
}

bool InsideTri( Vector2 tri[3], Vector2 vt, float *u, float* v )
{
	guardfunc;
	float A, B, C, D, E, F, U, V;
	A = tri[1].x-tri[0].x;
	B = tri[2].x-tri[0].x;
	C = vt.x-tri[0].x;
	D = tri[1].y-tri[0].y;
	E = tri[2].y-tri[0].y;
	F = vt.y-tri[0].y;
	
	float d = E*A-B*D;

	U = ( F*A-C*D )/d;
	V = ( C*E-F*B )/d;
	
	if (u)
	{
		*u = U;
	}
	if (v)
	{
		*v = V;
	}
	if( U >= 0 && V >= 0 && U+V <= 1 )
		return true;
	else 
		return false;
	unguard;
}

void SwapXY( Vector& v )
{
	guardfunc;
	float t = v.x;
	v.x = v.y;
	v.y = t;
	unguard;
}

void SwapYZ( Vector& v )
{
	guardfunc;
	float t = v.y;
	v.y = v.z;
	v.z = t;
	unguard;
}

void SwapXZ( Vector& v )
{
	guardfunc;
	float t = v.x;
	v.x = v.z;
	v.z = t;
	unguard;
}

Vector ProjPoint2Screen( const Vector& p, const MeMatrix& matView, const MeMatrix& matProj, int nScreenWidth, int nScreenHeight )
{
	guardfunc;
	Vector q;
	MeMatrix mix;
	D3DXMatrixMultiply( (D3DXMATRIX*)&mix, (D3DXMATRIX*)&matView, (D3DXMATRIX*)&matProj );
	D3DXVec3TransformCoord( (D3DXVECTOR3*)&q, (D3DXVECTOR3*)&p, (D3DXMATRIX*)&mix );
	q.x += nScreenWidth/2;
	q.y -= nScreenHeight/2;
	return q;
	unguard;
}

RECT MakeRect( POINT pt0, POINT pt1 )
{
	guardfunc;
	RECT rc;
	if( pt0.x < pt1.x )
	{
		rc.left = pt0.x;
		rc.right = pt1.x;
	}
	else
	{
		rc.left = pt1.x;
		rc.right = pt0.x;
	}
	if( pt0.y < pt1.y )
	{
		rc.top = pt0.y;
		rc.bottom = pt1.y;
	}
	else
	{
		rc.top = pt1.y;
		rc.bottom = pt0.y;
	}
	return rc;
	unguard;
}
//
//// �׳�
//int Factorial( int n )
//{
//	switch( n )
//	{
//	case 0:
//		return 1;
//	case 1:
//		return 1;
//	case 2:
//		return 2*1;
//	case 3:
//		return 3*2*1;
//	case 4:
//		return 4*3*2*1;
//	case 5:
//		return 5*4*3*2*1;
//	case 6:
//		return 6*5*4*3*2*1;
//	case 7:
//		return 7*6*5*4*3*2*1;
//	case 8:
//		return 8*7*6*5*4*3*2*1;
//	case 9:
//		return 9*8*7*6*5*4*3*2*1;
//	case 10:
//		return 10*9*8*7*6*5*4*3*2*1;
//	};
//	int s = 1;
//	for( int i = n; i > 0; i-- )
//	{
//		s *= i;
//	}
//	return s;
//}
//// ���
//int C( int n, int i )
//{
//	return Factorial( n )/( Factorial( i )*Factorial( n-i ) );
//}
//// Bernstein����
//float Bernstein( int n, int i, float t )
//{
//	return	C( n, i )*powf( t, i )*powf( 1-t, n-i );
//}
//// Riesenfeld����ʽ
//float Riesenfeld( int m, int i, float t )
//{
//	float s = 0;
//	for( int k = 0; k <= m-i; k++ )
//	{
//		s += powf( -1, k )*powf( t+m-i-k, m )/( Factorial( k )*Factorial( m-k+1 ) );
//	}
//	return s*( m+1 );
//}

float SinTable( int nDegree )
{
	guardfunc;
	static float fSinTable[360];
	static bool init = false;
	if( !init )
	{
		init = true;
		for( int i = 0; i < 360; i++ )
			fSinTable[i] = sinf( i*PIOVER180 );
	}
	nDegree %= 360;
	nDegree = nDegree>=0?nDegree:nDegree+360;
	nDegree = nDegree<=360?nDegree:nDegree-360;
	return fSinTable[nDegree];
	unguard;
}

float CosTable( int nDegree )
{
	guardfunc;
	static float fCosTable[360];
	static bool init = false;
	if( !init )
	{
		init = true;
		for( int i = 0; i < 360; i++ )
			fCosTable[i] = cosf( i*PIOVER180 );
	}
	nDegree %= 360;
	nDegree = nDegree>=0?nDegree:nDegree+360;
	nDegree = nDegree<=360?nDegree:nDegree-360;
	return fCosTable[nDegree];
	unguard;
}

float TanTable( int nDegree )
{
	guardfunc;
	static float fTanTable[360];
	static bool init = false;
	if( !init )
	{
		init = true;
		for( int i = 0; i < 360; i++ )
			fTanTable[i] = tanf( i*PIOVER180 );
	}
	nDegree %= 360;
	nDegree = nDegree>=0?nDegree:nDegree+360;
	nDegree = nDegree<=360?nDegree:nDegree-360;
	return fTanTable[nDegree];
	unguard;
}

void Min( Vector* v0, Vector* v1, Vector* m )
{
	guardfunc;
	m->x = min( v0->x, v1->x );
	m->y = min( v0->y, v1->y );
	m->z = min( v0->z, v1->z );
	unguard;
}

void Max( Vector* v0, Vector* v1, Vector* m )
{
	guardfunc;
	m->x = max( v0->x, v1->x );
	m->y = max( v0->y, v1->y );
	m->z = max( v0->z, v1->z );
	unguard;
}

float Shade( Vector& vLightPos, Vector& vNormal )
{
	guardfunc;
	float u = vLightPos.dot( vNormal );
	return u>=0?u:0;
	unguard;
}

typedef struct
{
	D3DXVECTOR3	v[8];
	D3DXPLANE	plane[6];
} BOX;

// �����󶨵�ƽ��
void BuildBBoxPlane( BOX* box )
{

	guardfunc;
	// Determine planes of the bounding box
	D3DXPlaneFromPoints( &box->plane[0], &box->v[0], 
		&box->v[1], &box->v[2] ); // Near	012
	D3DXPlaneFromPoints( &box->plane[1], &box->v[6], 
		&box->v[7], &box->v[5] ); // Far	675
	D3DXPlaneFromPoints( &box->plane[2], &box->v[2], 
		&box->v[6], &box->v[4] ); // Left	264
	D3DXPlaneFromPoints( &box->plane[3], &box->v[7], 
		&box->v[3], &box->v[5] ); // Right	735
	D3DXPlaneFromPoints( &box->plane[4], &box->v[2], 
		&box->v[3], &box->v[6] ); // Top	236
	D3DXPlaneFromPoints( &box->plane[5], &box->v[1], 
		&box->v[0], &box->v[4] ); // Bottom	104
	unguard;
}
// ��������󶨺�
void BuildWorldBBox( BOX* box, D3DXMATRIX* mat, BOX* wbox )
{
	guardfunc;
	// �任����������ϵ
	for( int i = 0; i < 8; i++ )
		D3DXVec3TransformCoord( &wbox->v[i], &box->v[i], mat );
	// ����ƽ��
	BuildBBoxPlane( wbox );	
	unguard;
}
//-----------------------------------------------------------------------------
// ����һ����׶
void BuildFrustum( BOX* frustum, D3DXMATRIX* pMatView, D3DXMATRIX* pMatProj )
{
	guardfunc;
	D3DXMATRIX mat;

	D3DXMatrixMultiply( &mat, pMatView, pMatProj );
	D3DXMatrixInverse( &mat, NULL, &mat );

	frustum->v[0] = D3DXVECTOR3(-1.0f, -1.0f,  0.0f); // xyz
	frustum->v[1] = D3DXVECTOR3( 1.0f, -1.0f,  0.0f); // Xyz
	frustum->v[2] = D3DXVECTOR3(-1.0f,  1.0f,  0.0f); // xYz
	frustum->v[3] = D3DXVECTOR3( 1.0f,  1.0f,  0.0f); // XYz
	frustum->v[4] = D3DXVECTOR3(-1.0f, -1.0f,  1.0f); // xyZ
	frustum->v[5] = D3DXVECTOR3( 1.0f, -1.0f,  1.0f); // XyZ
	frustum->v[6] = D3DXVECTOR3(-1.0f,  1.0f,  1.0f); // xYZ
	frustum->v[7] = D3DXVECTOR3( 1.0f,  1.0f,  1.0f); // XYZ

	for( int i = 0; i < 8; i++ )
		D3DXVec3TransformCoord( &frustum->v[i], &frustum->v[i], &mat );
	BuildBBoxPlane( frustum );
	unguard;
}

// ��׶�޳�
int FrustumExCull( BOX* frustum, BOX* box )
{
	guardfunc;
	// 1) ��� BBox �е����ⶥ���� FrustumEx �з��� true
    int bOutside[8];
    ZeroMemory ( &bOutside, sizeof ( bOutside ) );

    for ( int iPoint = 0; iPoint < 8; iPoint++ )
    {
        for ( int iPlane = 0; iPlane < 6; iPlane++ )
        {
            if ( frustum->plane[iPlane].a * box->v[iPoint].x +
                 frustum->plane[iPlane].b * box->v[iPoint].y +
                 frustum->plane[iPlane].c * box->v[iPoint].z +
                 frustum->plane[iPlane].d < 0)
            {
                bOutside[iPoint] |= ( 1 << iPlane );
            }
        }
        if ( bOutside[iPoint] == 0 )
            return true;
    }

	// 2) ����������� BBox ���㶼�� FrustumEx ������һ��ƽ��֮�ⷵ�� false
    if ( ( bOutside[0] &
		   bOutside[1] &
		   bOutside[2] &
		   bOutside[3] &
		   bOutside[4] & 
		   bOutside[5] & 
		   bOutside[6] & 
		   bOutside[7] ) != 0 )
        return false;

	// 3) ������� FrustumEx �е�����ߴ�Խ�� BBox �������淵�� true
	D3DXVECTOR3 dir;
	float u, v, d;
	for ( int e = 0; e < 12; e++ )
	{
		for ( int f = 0; f < 12; f++ )
		{
			dir = frustum->v[g_nBoxEdge[e][1]]-frustum->v[g_nBoxEdge[e][0]];
			if ( D3DXIntersectTri ( &box->v[g_nBoxFace[f*3]],
								    &box->v[g_nBoxFace[f*3+1]],
								    &box->v[g_nBoxFace[f*3+2]],
								    &frustum->v[g_nBoxEdge[e][0]],
								    &dir,
								    &u,
								    &v,
								    &d ) )
				return true;
		}
	}
	// 4) ������� BBox �е�����ߴ�Խ�� FrustumEx �������淵�� true
	for (int  e = 0; e < 12; e++ )
	{
		for ( int f = 0; f < 12; f++ )
		{
			dir = box->v[g_nBoxEdge[e][1]]-box->v[g_nBoxEdge[e][0]];
			if ( D3DXIntersectTri ( &frustum->v[g_nBoxFace[f*3]],
								    &frustum->v[g_nBoxFace[f*3+1]],
								    &frustum->v[g_nBoxFace[f*3+2]],
								    &box->v[g_nBoxEdge[e][0]],
								    &dir,
								    &u,
								    &v,
								    &d ) )
				return true;
		}
	}
	// 5) ������� FrustumEx �е����ⶥ���� BBox ��������֮�ⷵ�� false
    for( int iPlane = 0; iPlane < 6; iPlane++ )
    {
        for( int iPoint = 0; iPoint < 8; iPoint++ )
		{
			if ( box->plane[iPlane].a * frustum->v[iPoint].x +
             box->plane[iPlane].b * frustum->v[iPoint].y +
             box->plane[iPlane].c * frustum->v[iPoint].z +
             box->plane[iPlane].d  < 0 )
            return false;
		}
    }
	// 6) ���� FrustumEx һ���� BBox �з��� true
	return true;
	unguard;
}

void MirrorMatrix( int nAxis, MeMatrix* pMatrix  )
{
	guardfunc;
	D3DXMatrixIdentity( (D3DXMATRIX*)pMatrix );

	//switch( nAxis )
	//{
	//default:
		pMatrix->m[0][0] *= -1;
		pMatrix->m[1][0] *= -1;
		pMatrix->m[2][0] *= -1;
		pMatrix->m[3][0] *= -1;
		//break;
	//case 2:
	//	pMatrix->m[0][0] *= -1;
	//	break;
	//}
	unguard;
}
float DegreeToRad( int nDegree )
{
	guardfunc;
	return nDegree*3.1415926f/180.0f;
	unguard;
}
void Quat2Mat( Quaternion& q, MeMatrix& mat )
{
	guardfunc;
	enum
	{
		X = 0,
		Y = 1,
		Z = 2,
		W = 3,
	};
	float s, xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;
	s = 2.0f/Sqrt(q[W]*q[W]+q[X]*q[X]+q[Y]*q[Y]+q[Z]*q[Z]);
	xs = q[X]*s; ys = q[Y]*s; zs = q[Z]*s;
	wx = q[W]*xs; wy = q[W]*ys; wz = q[W]*zs;
	xx = q[X]*xs; xy = q[X]*ys; xz = q[X]*zs;
	yy = q[Y]*ys; yz = q[Y]*zs; zz = q[Z]*zs;
	//float m[4][4];
	//memset( m, 0, sizeof(m) );
	//m[0][0] = 1.0f-(yy+zz);
	//m[0][1] = xy-wz;
	//m[0][2] = xz+wy;
	//m[1][0] = xy+wz;
	//m[1][1] = 1.0f-(xx+zz);
	//m[1][2] = yz-wx;
	//m[2][0] = xz-wy;
	//m[2][1] = yz+wx;
	//m[2][2] = 1.0f-(xx+yy);
	//m[0][3] = 0.0; m[1][3] = 0.0; m[2][3] = 0.0; m[3][3] = 1.0;
	//m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0;

	////mat = m;
	//memcpy( mat.m, m, sizeof(float)*16 );

    memset( mat.m, 0, sizeof(mat.m) );
    mat.m[0][0] = 1.0f-(yy+zz);
    mat.m[0][1] = xy-wz;
    mat.m[0][2] = xz+wy;
    mat.m[1][0] = xy+wz;
    mat.m[1][1] = 1.0f-(xx+zz);
    mat.m[1][2] = yz-wx;
    mat.m[2][0] = xz-wy;
    mat.m[2][1] = yz+wx;
    mat.m[2][2] = 1.0f-(xx+yy);
    mat.m[3][3] = 1.0;

	unguard;
}
void MakeMatrix( Vector& v, Quaternion& q, MeMatrix& m )
{
	guardfunc;
	//D3DXQUATERNION q0( q.x, q.y, q.z, -q.w );

	//D3DXMatrixRotationQuaternion( (D3DXMATRIX*)&m, (D3DXQUATERNION*)&q0 );

	Quat2Mat( q, m );
	m.m[3][0] = v.x;
	m.m[3][1] = v.y;
	m.m[3][2] = v.z;
	unguard;
}
void ConvertMatrixToTranslationAndRotation( MeMatrix& m, Vector& v, Quaternion& q )
{
	guardfunc;
	D3DXMATRIX mat = *(D3DXMATRIX*)&m;
	v.x = mat._41;
	v.y = mat._42;
	v.z = mat._43;

	mat._41 = 0.0f;
	mat._42 = 0.0f;
	mat._43 = 0.0f;

	D3DXQUATERNION q0;
	D3DXQuaternionRotationMatrix( &q0, &mat );

	q.x = q0.x;
	q.y = q0.y;
	q.z = q0.z;
	q.w = -q0.w;
	unguard;
}