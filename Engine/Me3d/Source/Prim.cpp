#include "Me3d/Prim.h"
#include "Me3d/MathEx.h"
#include "Dxsdk/d3dx9.h"
#include "FuncPerformanceLog.h"

//-----------------------------------------------------------------------------
/*αβγδεζηθικλμνξοπρστυφχψω
≈≡≠＝≤≥＜＞≮≯∷±＋－×÷／∫∮∝∞∧∨∑∏∪∩∈∵∴⊥∥∠⌒⊙≌∽√
ⅠⅡⅢⅣⅤⅥⅦⅧⅨⅩⅪⅫ
⒈⒉⒊⒋⒌⒍⒎⒏⒐⒑
㈠㈡㈢㈣㈤㈥㈦㈧㈨㈩⑴⑵⑷⑸⑹⑺⑻⑼⑽
§№☆★○●◎◇◆□■△▲※→←↑↓〓＃＆＠＼︿＿￣
*/
//-----------------------------------------------------------------------------


/*    
	  6-----7			y
	 /|    /|			|    z
	2-----3 |			|   /
	| | o | |			|  /
	| 4---|-5			| /
	|/    |/			+---------x
	0-----1
*/
//单位立方体的8个顶点的坐标
Vector g_vStdViewBox[8] = 
{
	Vector( -1, -1, 0 ),
	Vector(  1, -1, 0 ),
	Vector( -1,  1, 0 ),
	Vector(  1,  1, 0 ),
	Vector( -1, -1, 1 ),
	Vector(  1, -1, 1 ),
	Vector( -1,  1, 1 ),
	Vector(  1,  1, 1 ),
};


//长方体的12个面的索引
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
// box的边索引
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
void Box::BuildAABB( const Vector& max, const Vector& min )
{
	guardfunc;
	v[0].x = min.x;
	v[0].y = min.y;
	v[0].z = min.z;

	v[7].x = max.x;
	v[7].y = max.y;
	v[7].z = max.z;

	v[6].x = min.x;
	v[6].y = max.y;
	v[6].z = max.z;

	v[4].x = min.x;
	v[4].y = min.y;
	v[4].z = max.z;

	v[1].x = max.x;
	v[1].y = min.y;
	v[1].z = min.z;

	v[3].x = max.x;
	v[3].y = max.y;
	v[3].z = min.z;

	v[5].x = max.x;
	v[5].y = min.y;
	v[5].z = max.z;

	v[2].x = min.x;
	v[2].y = max.y;
	v[2].z = min.z;

	BuildPlane();
	unguard;
}

void Box::BuildPlane()
{
	guardfunc;
	// Determine planes of the bounding box
	PlaneFromPoints( &plane[0], &v[0], 
		&v[1], &v[2] ); // Near	012
	PlaneFromPoints( &plane[1], &v[6], 
		&v[7], &v[5] ); // Far	675
	PlaneFromPoints( &plane[2], &v[2], 
		&v[6], &v[4] ); // Left	264
	PlaneFromPoints( &plane[3], &v[7], 
		&v[3], &v[5] ); // Right	735
	PlaneFromPoints( &plane[4], &v[2], 
		&v[3], &v[6] ); // Top	236
	PlaneFromPoints( &plane[5], &v[1], 
		&v[0], &v[4] ); // Bottom	104
	unguard;
}

void Box::Transform( const MeMatrix& matTransform, Box& worldBox )
{
	guardfunc;
	// 变换到世界坐标系
	for( int i = 0; i < 8; i++ )
		V3XM( &worldBox.v[i], &v[i], &matTransform );
	// 建立平面
	worldBox.BuildPlane();
	unguard;
}

bool Box::Intersect( const Vector& pos, const Vector& dir ,float* pfDis,bool bNearest)
{
	guardfunc;
	int nOffset = 0;
	int index0, index1, index2;
	float t,tu, tv;

	float* pTemp = &t;

	float fNearest = 100000.f;
	for( int i = 0; i < 12; i++ )
	{
		index0 = g_nBoxFace[nOffset++];
		index1 = g_nBoxFace[nOffset++];
		index2 = g_nBoxFace[nOffset++];
		
		if( IntersectTri( 
			&v[index0], 
			&v[index1], 
			&v[index2], 
			&pos, 
			&dir,
			&tu, 
			&tv,
			pTemp ) )
		{
			if ( !bNearest)
			{
				fNearest = *pTemp;
				break;
			}
			else if (*pTemp < fNearest)
			{
				fNearest = *pTemp;
			}
		}
	}
	if (fNearest < 100000.f - 0.1)
	{
		if (pfDis)
		{
			*pfDis = fNearest;
		}
		return true;
	}
	else
	{
		return false;
	}
	unguard;
}

bool Box::IntersectCircle( const Vector& pos, const Vector& dir, float fDisToRole )
{
	guardfunc;
	D3DXVECTOR3 vCentrePos = D3DXVECTOR3( 0,0,0 );
	for( int i = 0; i < 8; i++ )
	{
		vCentrePos = vCentrePos + *(D3DXVECTOR3*)&v[i];
	}
	vCentrePos = vCentrePos/8;

	float r = D3DXVec3Length( &(*(D3DXVECTOR3*)&v[0] - vCentrePos) ) * 1.24f;

	if( r < 0.6f )
	{
		return D3DXSphereBoundProbe( (D3DXVECTOR3*)&vCentrePos, r, (D3DXVECTOR3*)&pos, (D3DXVECTOR3*)&dir );
	}
	if( fDisToRole > 6.18f && r < 4 )
	{
		return D3DXSphereBoundProbe( (D3DXVECTOR3*)&vCentrePos, r, (D3DXVECTOR3*)&pos, (D3DXVECTOR3*)&dir );
	}
	else
	{
		return Intersect( pos, dir );
	}
	return false;
	unguard;
}

void Frustum::Build( const MeMatrix& matView, const MeMatrix& matProj )
{
	guardfunc;
	MeMatrix mat;

	MXM( &mat, &matView, &matProj );
	MINVERSE( &mat );

	for( int i = 0; i < 8; i++ )
		v[i] = g_vStdViewBox[i];

	for( int i = 0; i < 8; i++ )
		V3XM( &v[i], &v[i], &mat );
	BuildPlane();
	unguard;
}

bool Box::Cull( const Box& box )
{
	guardfunc;
	// 1) 如果 BBox 中的任意顶点在 FrustumEx 中返回 true
	int bOutside[8];
	ZeroMemory ( &bOutside, sizeof ( bOutside ) );

	for ( int iPoint = 0; iPoint < 8; iPoint++ )
	{
		for ( int iPlane = 0; iPlane < 6; iPlane++ )
		{
			if ( plane[iPlane].a * box.v[iPoint].x +
				 plane[iPlane].b * box.v[iPoint].y +
				 plane[iPlane].c * box.v[iPoint].z +
				 plane[iPlane].d > 0)
			{
				bOutside[iPoint] |= ( 1 << iPlane );
			}
		}
		if ( bOutside[iPoint] == 0 )
			return true;
	}

	// 2) 否则如果所有 BBox 顶点都在 FrustumEx 的任意一个平面之外返回 false
	if ( (  bOutside[0] &
			bOutside[1] &
			bOutside[2] &
			bOutside[3] &
			bOutside[4] & 
			bOutside[5] & 
			bOutside[6] & 
			bOutside[7] ) != 0 )
		return false;

	// 3) 否则如果 FrustumEx 中的任意边穿越于 BBox 的任意面返回 true
	Vector dir;
	float tu, tv, d;
	for ( int e = 0; e < 12; e++ )
	{
		for ( int f = 0; f < 12; f++ )
		{
			dir = v[g_nBoxEdge[e][1]]-v[g_nBoxEdge[e][0]];
			if ( IntersectTri ( &box.v[g_nBoxFace[f*3]],
				&box.v[g_nBoxFace[f*3+1]],
				&box.v[g_nBoxFace[f*3+2]],
				&v[g_nBoxEdge[e][0]],
				&dir,
				&tu,
				&tv,
				&d ) )
				return true;
		}
	}
	// 4) 否则如果 BBox 中的任意边穿越于 FrustumEx 的任意面返回 true
	for (int  e = 0; e < 12; e++ )
	{
		for ( int f = 0; f < 12; f++ )
		{
			dir = box.v[g_nBoxEdge[e][1]]-box.v[g_nBoxEdge[e][0]];
			if ( IntersectTri ( &v[g_nBoxFace[f*3]],
				&v[g_nBoxFace[f*3+1]],
				&v[g_nBoxFace[f*3+2]],
				&box.v[g_nBoxEdge[e][0]],
				&dir,
				&tu,
				&tv,
				&d ) )
				return true;
		}
	}
	// 5) 否则如果 FrustumEx 中的任意顶点在 BBox 的任意面之外返回 false
	for( int iPlane = 0; iPlane < 6; iPlane++ )
	{
		for( int iPoint = 0; iPoint < 8; iPoint++ )
		{
			if ( box.plane[iPlane].a * v[iPoint].x +
				box.plane[iPlane].b * v[iPoint].y +
				box.plane[iPlane].c * v[iPoint].z +
				box.plane[iPlane].d  > 0 )
				return false;
		}
	}
	// 6) 否则 FrustumEx 一定在 BBox 中返回 true
	return true;

	unguard;
}


void Box::Build( const MeMatrix& matTransform, const Vector& max, const Vector& min )
{
	v[0].x = min.x;
	v[0].y = min.y;
	v[0].z = min.z;

	v[7].x = max.x;
	v[7].y = max.y;
	v[7].z = max.z;

	v[6].x = min.x;
	v[6].y = max.y;
	v[6].z = max.z;

	v[4].x = min.x;
	v[4].y = min.y;
	v[4].z = max.z;

	v[1].x = max.x;
	v[1].y = min.y;
	v[1].z = min.z;

	v[3].x = max.x;
	v[3].y = max.y;
	v[3].z = min.z;

	v[5].x = max.x;
	v[5].y = min.y;
	v[5].z = max.z;

	v[2].x = min.x;
	v[2].y = max.y;
	v[2].z = min.z;
	// 变换到世界坐标系
	for( int i = 0; i < 8; i++ )
		V3XM( &v[i], &v[i], &matTransform );
	// 建立平面
	BuildPlane();

}