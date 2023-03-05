#include "Me3d/Engine/Frustum.h"
#include "FuncPerformanceLog.h"
FrustumEx::FrustumEx(void)
{
	guardfunc;
	memset( veFrustumEx,0,sizeof(veFrustumEx) );
	unguard;
}

FrustumEx::~FrustumEx(void)
{
	guardfunc;
	unguard;
}

void FrustumEx::BuildFrustum( D3DXVECTOR3 vecMin,D3DXVECTOR3 vecMax )
{
	guardfunc;
	veFrustumEx[0] = D3DXVECTOR3( vecMin.x, vecMin.y,  vecMin.z ); // xyz
	veFrustumEx[1] = D3DXVECTOR3( vecMax.x, vecMin.y,  vecMin.z); // Xyz
	veFrustumEx[2] = D3DXVECTOR3( vecMin.x, vecMax.y,  vecMin.z); // xYz
	veFrustumEx[3] = D3DXVECTOR3( vecMax.x, vecMax.y,  vecMin.z); // XYz
	veFrustumEx[4] = D3DXVECTOR3( vecMin.x, vecMin.y,  vecMax.z); // xyZ
	veFrustumEx[5] = D3DXVECTOR3( vecMax.x, vecMin.y,  vecMax.z); // XyZ
	veFrustumEx[6] = D3DXVECTOR3( vecMin.x, vecMax.y,  vecMax.z); // xYZ
	veFrustumEx[7] = D3DXVECTOR3( vecMax.x, vecMax.y,  vecMax.z); // XYZ

	// 
	D3DXPlaneFromPoints( &planeFrustumEx[0], &veFrustumEx[0], 
		&veFrustumEx[1], &veFrustumEx[2] ); // Near
	D3DXPlaneFromPoints( &planeFrustumEx[1], &veFrustumEx[6], 
		&veFrustumEx[7], &veFrustumEx[5] ); // Far
	D3DXPlaneFromPoints( &planeFrustumEx[2], &veFrustumEx[2], 
		&veFrustumEx[6], &veFrustumEx[4] ); // Left
	D3DXPlaneFromPoints( &planeFrustumEx[3], &veFrustumEx[7], 
		&veFrustumEx[3], &veFrustumEx[5] ); // Right
	D3DXPlaneFromPoints( &planeFrustumEx[4], &veFrustumEx[2], 
		&veFrustumEx[3], &veFrustumEx[6] ); // Top
	D3DXPlaneFromPoints( &planeFrustumEx[5], &veFrustumEx[1], 
		&veFrustumEx[0], &veFrustumEx[4] ); // Bottom
	unguard;
}

void FrustumEx::BuildFrustum( D3DXMATRIX &matProj, D3DXMATRIX &matView )
{
	guardfunc;
	D3DXMATRIX mat;

	D3DXMatrixMultiply( &mat, &matView,&matProj  );
	D3DXMatrixInverse( &mat, NULL, &mat );

	//运算取得视锥的8个定点
	//vec * view * proj = 屏幕点
	//取逆
	veFrustumEx[0] = D3DXVECTOR3(-1.0f, -1.0f,  0.0f); // xyz
	veFrustumEx[1] = D3DXVECTOR3( 1.0f, -1.0f,  0.0f); // Xyz
	veFrustumEx[2] = D3DXVECTOR3(-1.0f,  1.0f,  0.0f); // xYz
	veFrustumEx[3] = D3DXVECTOR3( 1.0f,  1.0f,  0.0f); // XYz
	veFrustumEx[4] = D3DXVECTOR3(-1.0f, -1.0f,  1.0f); // xyZ
	veFrustumEx[5] = D3DXVECTOR3( 1.0f, -1.0f,  1.0f); // XyZ
	veFrustumEx[6] = D3DXVECTOR3(-1.0f,  1.0f,  1.0f); // xYZ
	veFrustumEx[7] = D3DXVECTOR3( 1.0f,  1.0f,  1.0f); // XYZ

	for( UINT i = 0; i < 8; i++ )
		D3DXVec3TransformCoord( &veFrustumEx[i], &veFrustumEx[i], &mat );


	// 
	D3DXPlaneFromPoints( &planeFrustumEx[0], &veFrustumEx[0], 
		&veFrustumEx[1], &veFrustumEx[2] ); // Near
	D3DXPlaneFromPoints( &planeFrustumEx[1], &veFrustumEx[6], 
		&veFrustumEx[7], &veFrustumEx[5] ); // Far
	D3DXPlaneFromPoints( &planeFrustumEx[2], &veFrustumEx[2], 
		&veFrustumEx[6], &veFrustumEx[4] ); // Left
	D3DXPlaneFromPoints( &planeFrustumEx[3], &veFrustumEx[7], 
		&veFrustumEx[3], &veFrustumEx[5] ); // Right
	D3DXPlaneFromPoints( &planeFrustumEx[4], &veFrustumEx[2], 
		&veFrustumEx[3], &veFrustumEx[6] ); // Top
	D3DXPlaneFromPoints( &planeFrustumEx[5], &veFrustumEx[1], 
		&veFrustumEx[0], &veFrustumEx[4] ); // Bottom
	unguard;
	
}

//int CheckAABBVisible(D3DXVECTOR3& vecMin, D3DXVECTOR3& vecMax)
//{
//	D3DXVECTOR3	vecMinPt, vecMaxPt;
//	bool bIntersecting = false;
//
//	for (int i = 0; i < 6; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			if (m_WorldPlanes[i][j] >= 0.0f)
//			{
//				vecMinPt[j] = vecMin[j];
//				vecMaxPt[j] = vecMax[j];
//			}
//			else
//			{
//				vecMinPt[j] = vecMax[j];
//				vecMaxPt[j] = vecMin[j];
//			}
//		}
//		float fMinDistance = D3DXPlaneDotCoord(&m_WorldPlanes[i], &vecMinPt);
//		if (fMinDistance > 0.0f)
//			return 0;
//
//		float fMaxDistance = D3DXPlaneDotCoord(&m_WorldPlanes[i], &vecMaxPt);
//		if (fMaxDistance >= 0.0f)
//			bIntersecting = true;
//	}
//	// At this stage it's visible, but may be intersecting.  Return true in either case.
//	return bIntersecting ? 1 : 2;
//}

//上面可能有更好的算法
//#define NEWCROSSMETHON
int FrustumEx::BBoxCrossFrustum( SBBox & bbox, bool bLeftHand /*= true*/)
{
	guardfunc;
#ifdef NEWCROSSMETHON
	D3DXVECTOR3 vPoint[8];

	vPoint[0].x = bbox.vecMin.x;
	vPoint[0].y = bbox.vecMin.y;
	vPoint[0].z = bbox.vecMin.z;

	vPoint[1].x = bbox.vecMax.x;
	vPoint[1].y = bbox.vecMin.y;
	vPoint[1].z = bbox.vecMin.z;

	vPoint[2].x = bbox.vecMax.x;
	vPoint[2].y = bbox.vecMax.y;
	vPoint[2].z = bbox.vecMin.z;

	vPoint[3].x = bbox.vecMin.x;
	vPoint[3].y = bbox.vecMax.y;
	vPoint[3].z = bbox.vecMin.z;

	vPoint[4].x = bbox.vecMin.x;
	vPoint[4].y = bbox.vecMin.y;
	vPoint[4].z = bbox.vecMax.z;

	vPoint[5].x = bbox.vecMax.x;
	vPoint[5].y = bbox.vecMin.y;
	vPoint[5].z = bbox.vecMax.z;

	vPoint[6].x = bbox.vecMax.x;
	vPoint[6].y = bbox.vecMax.y;
	vPoint[6].z = bbox.vecMax.z;

	vPoint[7].x = bbox.vecMin.x;
	vPoint[7].y = bbox.vecMax.y;
	vPoint[7].z = bbox.vecMax.z;


	BYTE bOutside[8];
	ZeroMemory( &bOutside, sizeof(bOutside) );

	for( int iPoint = 0 ; iPoint < 8 ; iPoint ++ )
	{
		for( int iPlane = 0 ; iPlane < 6 ; iPlane ++ )
		{
			if( planeFrustumEx[iPlane].a * vPoint[ iPoint ].x +
				planeFrustumEx[iPlane].b * vPoint[ iPoint ].y +
				planeFrustumEx[iPlane].c * vPoint[ iPoint ].z +
				planeFrustumEx[iPlane].d < 0 )
			{
				bOutside[iPoint] ++;
			}
		}
		if( 6 == bOutside[ iPoint ] )
			return cross_exclude;
	}

	if( (bOutside[0] | bOutside[1] | bOutside[2] | bOutside[3]
	| bOutside[4] | bOutside[5] | bOutside[6] | bOutside[7]) == 0 )
		return cross_include;

	//if( bOutside[0] & bOutside[1] & bOutside[2] & bOutside[3]
	//& bOutside[4] & bOutside[5] & bOutside[6] & bOutside[7] != 0 )
	//	return cross_exclude;

	return cross_cross;
#else
	int iCount;	
	int iCount1 = 0 ;

	for( UINT iPlane = 0; iPlane < 6; iPlane++ )
	{
		iCount = 0;
		if( bLeftHand )
		{
			if( planeFrustumEx[iPlane].a * bbox.vecMin.x +
				planeFrustumEx[iPlane].b * bbox.vecMin.y +
				planeFrustumEx[iPlane].c * bbox.vecMin.z +
				planeFrustumEx[iPlane].d > 0)
				iCount ++;
			if( planeFrustumEx[iPlane].a * bbox.vecMax.x +
				planeFrustumEx[iPlane].b * bbox.vecMin.y +
				planeFrustumEx[iPlane].c * bbox.vecMin.z +
				planeFrustumEx[iPlane].d > 0)
				iCount ++;
			if( planeFrustumEx[iPlane].a * bbox.vecMax.x +
				planeFrustumEx[iPlane].b * bbox.vecMax.y +
				planeFrustumEx[iPlane].c * bbox.vecMin.z +
				planeFrustumEx[iPlane].d > 0)
				iCount ++;
			if( planeFrustumEx[iPlane].a * bbox.vecMin.x +
				planeFrustumEx[iPlane].b * bbox.vecMax.y +
				planeFrustumEx[iPlane].c * bbox.vecMin.z +
				planeFrustumEx[iPlane].d > 0)
				iCount ++;
			if( planeFrustumEx[iPlane].a * bbox.vecMin.x +
				planeFrustumEx[iPlane].b * bbox.vecMin.y +
				planeFrustumEx[iPlane].c * bbox.vecMax.z +
				planeFrustumEx[iPlane].d > 0)
				iCount ++;
			if( planeFrustumEx[iPlane].a * bbox.vecMax.x +
				planeFrustumEx[iPlane].b * bbox.vecMin.y +
				planeFrustumEx[iPlane].c * bbox.vecMax.z +
				planeFrustumEx[iPlane].d > 0)
				iCount ++;
			if( planeFrustumEx[iPlane].a * bbox.vecMax.x +
				planeFrustumEx[iPlane].b * bbox.vecMax.y +
				planeFrustumEx[iPlane].c * bbox.vecMax.z +
				planeFrustumEx[iPlane].d > 0)
				iCount ++;
			if( planeFrustumEx[iPlane].a * bbox.vecMin.x +
				planeFrustumEx[iPlane].b * bbox.vecMax.y +
				planeFrustumEx[iPlane].c * bbox.vecMax.z +
				planeFrustumEx[iPlane].d > 0)
				iCount ++;
		}
		else
		{
			if( planeFrustumEx[iPlane].a * bbox.vecMin.x +
				planeFrustumEx[iPlane].b * bbox.vecMin.y +
				planeFrustumEx[iPlane].c * bbox.vecMin.z +
				planeFrustumEx[iPlane].d <= 0)
				iCount ++;
			if( planeFrustumEx[iPlane].a * bbox.vecMax.x +
				planeFrustumEx[iPlane].b * bbox.vecMin.y +
				planeFrustumEx[iPlane].c * bbox.vecMin.z +
				planeFrustumEx[iPlane].d <= 0)
				iCount ++;
			if( planeFrustumEx[iPlane].a * bbox.vecMax.x +
				planeFrustumEx[iPlane].b * bbox.vecMax.y +
				planeFrustumEx[iPlane].c * bbox.vecMin.z +
				planeFrustumEx[iPlane].d <= 0)
				iCount ++;
			if( planeFrustumEx[iPlane].a * bbox.vecMin.x +
				planeFrustumEx[iPlane].b * bbox.vecMax.y +
				planeFrustumEx[iPlane].c * bbox.vecMin.z +
				planeFrustumEx[iPlane].d <= 0)
				iCount ++;
			if( planeFrustumEx[iPlane].a * bbox.vecMin.x +
				planeFrustumEx[iPlane].b * bbox.vecMin.y +
				planeFrustumEx[iPlane].c * bbox.vecMax.z +
				planeFrustumEx[iPlane].d <= 0)
				iCount ++;
			if( planeFrustumEx[iPlane].a * bbox.vecMax.x +
				planeFrustumEx[iPlane].b * bbox.vecMin.y +
				planeFrustumEx[iPlane].c * bbox.vecMax.z +
				planeFrustumEx[iPlane].d <= 0)
				iCount ++;
			if( planeFrustumEx[iPlane].a * bbox.vecMax.x +
				planeFrustumEx[iPlane].b * bbox.vecMax.y +
				planeFrustumEx[iPlane].c * bbox.vecMax.z +
				planeFrustumEx[iPlane].d <= 0)
				iCount ++;
			if( planeFrustumEx[iPlane].a * bbox.vecMin.x +
				planeFrustumEx[iPlane].b * bbox.vecMax.y +
				planeFrustumEx[iPlane].c * bbox.vecMax.z +
				planeFrustumEx[iPlane].d <= 0)
				iCount ++;
		}

		//所有的点都在面的外侧
		if (iCount == 0)
			return cross_exclude;		
		if( 8 == iCount )
			iCount1 ++;
	}
	if( 6 == iCount1)
		return cross_include;
	return cross_cross;
#endif
	unguard;
}