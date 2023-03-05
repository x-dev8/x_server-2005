/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	NdlWorldPickerBase.cpp
* Create: 	10/06/2006
* Desc:		计算和获取地表高度
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "MeTerrain/NdlWorldPickerBase.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldTile.h"
#include "MeTerrain/WorldChunk.h"
#include "MeTerrain/NdlResMgr.h"
#include "FuncPerformanceLog.h"

//for getzbyxy


////////////////////////////////////////////////////////////////////////////////
namespace {
	struct TRay {
		Vector	point;
		Vector	dir;
		sInt32		flagDir[2];
	};
	
	struct TSquard {
		flt32	halfGridSize[2];
		sInt32	grid[2];
		flt32	origin[2];
		flt32	pos[2];
		flt32	height[2];	// height[0] min, height[1] max.
	};
	
	struct TCollideResult {
		flt32	nextPos[2];
		sInt32	nextGrid[2];
		flt32	rayScale;
	};



	void GetUnitIdFromPos( TSquard& squard, const flt32* offset ) {
		for( sInt32 i=0;i<2;i++ ) {
			squard.grid[i]		= UnitFromPos( squard.pos[i]-offset[i] );
			if( squard.grid[i] < 0 )
				squard.grid[i] = 0;
			else if( squard.grid[i] >= WORLD_TILE_CHUNK_UNIT_NUM )
				squard.grid[i] = (WORLD_TILE_CHUNK_UNIT_NUM-1);
		}
	}

	bool CollideSquard( const TRay& ray, const TSquard& sqard, TCollideResult& collideResult ) {
		flt32 scale, prevScale	= swInfinity;
		collideResult.rayScale	= swInfinity;
		sInt32 useAxis			= -1;	// -1 None, 0 => x, 1 => y, 2 => x and y
		
		for( sInt32 i=0; i<2; i++ ) {
			if( ray.dir[i] != 0.0f ) {
				scale = (sqard.origin[i]+ray.flagDir[i]*sqard.halfGridSize[i]-ray.point[i]) / ray.dir[i];
				if( collideResult.rayScale > scale ) {
					useAxis = i;
					collideResult.rayScale		= scale;
				}
				else if( collideResult.rayScale < scale ) {
					
				}
				else{
					useAxis = 2;
				}	
				// scale. if( ray.dir[0]  != 0) then (scaleX == scaleY) 
				if( swInfinity == prevScale )
					prevScale	= (sqard.pos[i]-ray.point[i]) / ray.dir[i];
				// only for debug.
				//else {
				//	if( ( prevScale-((sqard.pos[i]-ray.point[i])/ray.dir[i]) ) > 1.0f )	{
				//		Assert( ( prevScale-((sqard.pos[i]-ray.point[i])/ray.dir[i]) ) < 1.0f )
				//	}
				//}
			}
		}
		switch( useAxis )
		{
		case 0:
			collideResult.nextGrid[0] = sqard.grid[0]+ray.flagDir[0];
			collideResult.nextGrid[1] = sqard.grid[1];
			break;
		case 1:
			collideResult.nextGrid[0] = sqard.grid[0];
			collideResult.nextGrid[1] = sqard.grid[1]+ray.flagDir[1];
			break;
		case 2:
			collideResult.nextGrid[0] = sqard.grid[0]+ray.flagDir[0];
			collideResult.nextGrid[1] = sqard.grid[1]+ray.flagDir[1];
			break;
		default:
			Assert( false );
		}
		Assert( swInfinity != collideResult.rayScale );
		collideResult.nextPos[0] = ray.point.x + collideResult.rayScale * ray.dir.x;
		collideResult.nextPos[1] = ray.point.y + collideResult.rayScale * ray.dir.y;

		
		flt32 z		= ray.point.z + collideResult.rayScale * ray.dir.z;
		flt32 prevZ = ray.point.z + prevScale * ray.dir.z;

		if( (z<sqard.height[0]) ) {
			if(prevZ<sqard.height[0]) {
				return false;
			}
		}
		else if( z>sqard.height[1] ) {
			if(prevZ>sqard.height[1]) {
				return false;
			}
		}
		return true;
	}

	bool IntersectTriangle(const Vector& kOrigin, 
		Vector& kDir, const Vector& kV1, const Vector& kV2, 
		const Vector& kV3, bool bCull, Vector& kIntersect, float& r, float& s, 
		float& t)
	{
		// All input quantities are in model space of the NiMesh object.
		// Input:
		//     ray (kOrigin+T*kDir), 
		//     triangle vertices (kV1, kV2, kV3)
		//     backface culling is performed when bCull=true
		// Return value:  true iff the ray intersects the triangle
		// Output (valid when return value is true):
		//     intersection of ray and triangle (kIntersect)
		//     kIntersect = kOrigin+r*kDir
		//     kIntersect = kV1+s*(kV2-kV1)+t*(kV3-kV1)

		// From "Real-Time Rendering" which references Moller, Tomas & Trumbore, 
		// "Fast, Minimum Storage Ray-Triangle Intersection", Journal of Graphics 
		// Tools, vol. 2, no. 1, pp 21-28, 1997. With some modifications to the 
		// non-culling case by Michael Mounier.

		const float fTolerance = 1e-05f;

		Vector kEdge1 = kV2 - kV1;
		Vector kEdge2 = kV3 - kV1;

		Vector kPt = kDir.cross(kEdge2);

		float fDet = kEdge1 * kPt;
		if (fDet >= fTolerance) // Determinant is positive.
		{
			Vector kS = kOrigin - kV1;
			s = kS * kPt;

			if (s < 0.0f || s > fDet)
				return false;

			Vector q = kS.cross(kEdge1);
			t = kDir * q;

			if (t < 0.0f || s + t > fDet)
				return false;

			r = kEdge2 * q;

			if (r < 0.0f)
				return false;
		}
		else if (fDet <= -fTolerance && !bCull) // Determinant is negative.
		{
			Vector kS = kOrigin - kV1;
			s = kS * kPt;

			if (s > 0.0f || s < fDet)
				return false;

			Vector q = kS.cross(kEdge1);
			t = kDir * q;

			if (t > 0.0f || s + t < fDet)
				return false;

			r = kEdge2 * q;

			if (r > 0.0f)
				return false;
		}
		else    // Parallel ray or culled.
		{
			return false;
		}

		float inv_det = 1.0f / fDet;

		s *= inv_det;
		t *= inv_det;
		r *= inv_det;

		kIntersect = kOrigin + r * kDir;

		return true;
	}

	bool CollideUnit( TRay& ray, const TVertInfo* fiveVert, TPickResult& pickResult ) {
		if( pickResult.pickResultCount >= MAX_PICK_OBJ_COUNT )
			return false;

// 		sInt32 collideCount = 0;
		flt32 scale=swInfinity,s,t;
		bool isCollide = false;

		Vector v0, v1, v2, n0, n1, n2,pickPt;
		v0.x = fiveVert[0].pos[0];
		v0.y = fiveVert[0].pos[1];
		v0.z = fiveVert[0].pos[2];
		n0.x = fiveVert[0].normal[0];
		n0.y = fiveVert[0].normal[1];
		n0.z = fiveVert[0].normal[2];
		sInt32 id;
		for( sInt32 i = 0; i < 4; i++ ) {
			id	 = i+1;
			v1.x = fiveVert[id].pos[0];
			v1.y = fiveVert[id].pos[1];
			v1.z = fiveVert[id].pos[2];
			n1.x = fiveVert[id].normal[0];
			n1.y = fiveVert[id].normal[1];
			n1.z = fiveVert[id].normal[2];
			id	= ZnNextOneIdLoop( id, 1, 4 );
			v2.x = fiveVert[id].pos[0];
			v2.y = fiveVert[id].pos[1];
			v2.z = fiveVert[id].pos[2];
			n2.x = fiveVert[id].normal[0];
			n2.y = fiveVert[id].normal[1];
			n2.z = fiveVert[id].normal[2];
			if( IntersectTriangle( ray.point, ray.dir, v0, v1, v2, false, pickPt, scale, s, t ) ) {
				// 碰撞,求法线.
				pickResult.pickResultInfo[pickResult.pickResultCount].resultType	= emPT_Terrain;
				pickResult.pickResultInfo[pickResult.pickResultCount].dist			= scale;
				pickResult.pickResultInfo[pickResult.pickResultCount].point			= pickPt;
				pickResult.pickResultInfo[pickResult.pickResultCount].normal		= (1.0 - (s + t))*n0 + s*n1 + t*n2;//(1.0f-t)*((1.0f-s)*n0+s*n1)+t*n2;
				pickResult.pickResultInfo[pickResult.pickResultCount].normal.normalize();

				pickResult.pickResultCount++;

				isCollide = true;

				//Trace( "Collide triangle Point(%8.3f,%8.3f,%8.3f) \n"
				//	, pickResult.point.x, pickResult.point.y, pickResult.point.z
				//	);
			}
			//Trace( "Collide triangle(%d): ray(%8.3f,%8.3f,%8.3f)(%8.3f,%8.3f,%8.3f) Tri[%8.3f,%8.3f,%8.3f][%8.3f,%8.3f,%8.3f][%8.3f,%8.3f,%8.3f]\n"
			//	, collideCount
			//	, ray.point.x, ray.point.y, ray.point.z, ray.dir.x, ray.dir.y, ray.dir.z
			//	, v0.x, v0.y, v0.z, v1.x, v1.y, v1.z, v2.x, v2.y, v2.z
			//	);
		}
		return isCollide;
	}

	

	bool RayIntersectionSphere( const Vector& origin, flt32 radius, const Vector& start, const Vector& dir, flt32& scale1, flt32& scale2 )
	{
		double a, b, c, d, sqrtd;
		Vector p;
		p = start - origin;
		a = dir * dir;
		b = dir * p;
		c = p * p - radius * radius;
		d = b * b - c * a;
		if ( d < 0.0f ) {
			return false;
		}
		sqrtd = Sqrt( d );
		a = 1.0f / a;
		scale1 = ( -b + sqrtd ) * a;
		scale2 = ( -b - sqrtd ) * a;
		return true;
	}
}
////////////////////////////////////////////////////////////////////////////////
bool CNdlWorldPickerBase::CalcHeight(Vector v0, Vector v1, Vector v2, Vector& v, Vector& normal) const
{
	Vector v01	= v1 - v0;
	Vector v02	= v2 - v0;


	normal = v02.cross(v01);
	flt32 len	= normal.normalize();

	v.z = (normal.x * (v0.x - v.x) + normal.y * (v0.y - v.y)) / normal.z + v0.z;

	return true;
}

////////////////////////////////////////////////////////////////////////////////
CNdlWorldPickerBase::CNdlWorldPickerBase( CWorld* world ) {
	Assert( NULL != world );
	Assert( NULL != world->GetWorldBuffer() );

	m_worldBuffer = world->GetWorldBuffer();
	
	m_maxRayCastDistance = MAX_RAYCAST_DISTANCE;
	m_bSort				= false;
	m_bNearest		= true;
}

CNdlWorldPickerBase::~CNdlWorldPickerBase() {
	m_worldBuffer = NULL;
}
//GetZByXY里面使用静态数组作为返回值，多线程不安全
float CNdlWorldPickerBase::GetZByXY(float fCurrentZ,  float x, float y,DWORD dwFlag, 
									BOOL* bInFloor /* = NULL */, DWORD* pdwRet /* = NULL */, BOOL bIsRole /* = false */, D3DXVECTOR3 *pNormal /* = NULL */)
{
	float fHeight			= 0.0f;
	float fHugeModelHeight	= 0.0f;
	float fModelHeight		= 0.f;
	BOOL bHitHugeModelFloor = FALSE;
	BOOL bHitModelFloor		= FALSE;
	BOOL bHitTerrain		= FALSE;


	D3DXVECTOR3 NormalHugeModel(0,0,0);
	D3DXVECTOR3 NormalScene(0,0,0);
	D3DXVECTOR3 NormalModel(0,0,0);

	// Tile是否有效并加载

	CWorldTile* activeTile = m_worldBuffer->GetActiveTile();
	if( !activeTile || !activeTile->IsLoad() )
	{
		if( pdwRet )
		{
			*pdwRet = emPT_Unknown;
		}
		return 0.0f;
	}

// 	if( activeTile && activeTile->IsLoad() )
	{
		THeightResult heightResult;
		if (GetHeight(x,y,heightResult))
		{
			fHeight = heightResult.height;
			NormalScene = *((D3DXVECTOR3*) (&heightResult.normal));
			bHitTerrain = TRUE;
		}

// 		Vector dir(0.f, 0.f, -1.f);
// 		Vector origin( x, y, 10000.f);
// 		TPickResult result;
// 		if( Pick( origin, dir, result ) )	// 默认Pick地表
// 		{
// 			fHeight = result.pickResultInfo[0].point.z;
// 			NormalScene = D3DXVECTOR3( result.pickResultInfo[0].normal.x, result.pickResultInfo[0].normal.y, result.pickResultInfo[0].normal.z);
// 			bHitTerrain = TRUE;
// 		}

		// 判断模型地面高度
		BspTree::SIntersect* pIntersect = GetFloorZByXY( fCurrentZ,  x, y,  pdwRet, &NormalModel );

		if (pIntersect)
		{
			fModelHeight =  pIntersect->pos.z;
			bHitModelFloor = TRUE;
		}

	}


	// 优先选择与floor的交点
	// 判断模型地面和地表高度
	enum{
		eResultTerrain = 0,
		eResultModel,
		eResultHugeModel
	};
	int nRetResult = eResultTerrain;	// 用nRetResult记录是取哪个高度
	FLOAT fCmpModel = fabsf( fCurrentZ - fModelHeight );
	FLOAT fCmpTerrain = fabsf( fCurrentZ - fHeight );
	float fCmpHugeModel = fabsf( fHugeModelHeight - fCurrentZ );

	if( bHitModelFloor && bHitTerrain )
	{
		if( fCmpTerrain > fCmpModel )
		{
			// 取Model
			nRetResult = eResultModel;
		}
	}

	if( bHitHugeModelFloor )
	{
		if( nRetResult == eResultTerrain )
		{
			if( fCmpTerrain > fCmpHugeModel )
			{
				// 取Huge Model
				nRetResult = eResultHugeModel;
			}
		}
		else
		{
			if( fCmpModel > fCmpHugeModel )
			{
				// 取Huge Model
				nRetResult = eResultHugeModel;
			}
		}
	}
	switch( nRetResult )
	{
	case eResultTerrain:
		if( bInFloor )
			*bInFloor = FALSE;
		if( pdwRet )
			*pdwRet = emPT_Terrain;
		if( pNormal )
			*pNormal = NormalScene;
		return fHeight;
		break;
	case eResultModel:
		if( bInFloor )
			*bInFloor = TRUE;
		if( pdwRet )
			*pdwRet = emPT_FloorObj;
		if( pNormal )
			*pNormal = NormalModel;
		return fModelHeight;
		break;
	case eResultHugeModel:
		if( bInFloor )
			*bInFloor = TRUE;
		if( pdwRet )
			*pdwRet = emPT_FloorObj;
		if( pNormal )
			*pNormal = NormalHugeModel;
		return fHugeModelHeight;
		break;
	}
//	if( fCmpZ1 > fCmpZ0 )
//	{
// 		if( bInFloor )
// 			*bInFloor = TRUE;
// 		if( pdwRet )
// 			*pdwRet = CScene::eIntersect_Floor;
// 
// 		if( *pNormal )
// 		{
// 			*pNormal = NormalHugeModel;
// 		}
// 		return fHugeModelHeight;
//	}

	//if( bInFloor )
	//	*bInFloor = FALSE;
	//if( *pNormal )
	//{
	//	*pNormal = NormalScene;
	//}
	return fHeight;
}
bool CNdlWorldPickerBase::GetHeight( flt32 posX, flt32 posY, flt32& height ) const {
	Assert( NULL != m_worldBuffer );
	
	CWorldTile* tile = m_worldBuffer->GetActiveTile();
	if( NULL == tile )
		return false;
	
	return GetHeight(tile,posX,posY,height);
}

bool CNdlWorldPickerBase::GetHeight( CWorldTile* tile, flt32 posX, flt32 posY, flt32& height ) const
{
	THeightResult heightResult;
	bool ret = true;
	if (NULL == tile)
	{
		ret = GetHeight(posX,posY,heightResult);
	}
	else
	{
		ret = GetHeight(tile, posX, posY, heightResult);
	}

	if( ret )
	{
		height = heightResult.height;
	}
	return ret;
}

bool CNdlWorldPickerBase::GetHeight( flt32 posX, flt32 posY, THeightResult& heightResult ) const
{
	Assert( NULL != m_worldBuffer );

	CWorldTile* tile = m_worldBuffer->GetActiveTile();
	if( NULL == tile )
		return false;

	return GetHeight(tile,posX,posY,heightResult);

}

bool CNdlWorldPickerBase::GetHeight( CWorldTile* tile, flt32 posX, flt32 posY, THeightResult& heightResult ) const
{
	if (NULL == tile)
	{
		return GetHeight(posX,posY,heightResult);
	}

	sInt32 blkX, blkY;
	flt32 offX, offY, deltaX, deltaY;
	offX			= posX - tile->GetOrigin()[0];
	offY			= posY - tile->GetOrigin()[1];

	blkX			= ZnFloor2Int( ((offX)+tile->GetOrigin()[0])/WORLD_CHUNKSIZE );
	blkY			= ZnFloor2Int( ((offY)+tile->GetOrigin()[1])/WORLD_CHUNKSIZE );

	CWorldChunk* chunk = tile->GetChunk( blkX, blkY );
	if( NULL == chunk )
		return false;

	offX			= posX - chunk->Origin()[0];
	offY			= posY - chunk->Origin()[1];

	blkX			= UnitFromPos( offX );
	blkY			= UnitFromPos( offY );

	if( blkX < 0 )	// 当压住边界时有可能小于零.
		blkX = 0;
	if( blkY < 0 )
		blkY = 0;

	const TChunkVertex* vertexOut= chunk->GetVertexOut();
	const TChunkVertex* vertexIn	= chunk->GetVertexIn();

	Vector v;

	deltaX			= blkX * WORLD_UNITSIZE;
	deltaY			= blkY * WORLD_UNITSIZE;
	deltaX			= offX - deltaX + (WORLD_CHUNK_ORIGIN-0.5f*WORLD_UNITSIZE);
	deltaY			= offY - deltaY + (WORLD_CHUNK_ORIGIN-0.5f*WORLD_UNITSIZE);

	v.x				= deltaX + 0.5f*WORLD_UNITSIZE;
	v.y				= deltaY + 0.5f*WORLD_UNITSIZE;

	sInt32 inId		= blkY * WORLD_TILE_CHUNK_UNIT_NUM + blkX;
	sInt32 outId;	

	Vector v0, v1, v2;	// 逆时针方向记录v0,v1,v2
	//				A----------B
	//			   / \		  / \
	//			  /   \	 2	 /   \
	//			 /	1  \    /  3  \
	//			/       \  /       \
	//		   /         \/         \
	//		  C----------D----------E
	//		   \        / \        /
	//			\  4   /   \   6  /
	//			 \    /     \    /
	//			  \  /   5   \  /
	//			   \/         \/
	//				F---------G

	if( deltaY< -1.0e-5 )
	{
		flt32 arctan = deltaX / deltaY;
		if( arctan > 1.0 )			//1
		{
			outId	= inId + blkY;
			v0		= Vector(0,					0,						vertexOut[outId].height);	//A
			if( blkX == 0 )
				v1	= Vector(0,					WORLD_UNITSIZE,			vertexOut[outId+(WORLD_TILE_CHUNK_UNIT_NUM+1)].height);	//F，chunk边界上
			else
				v1	= Vector(-0.5f*WORLD_UNITSIZE,0.5f*WORLD_UNITSIZE,	vertexIn[inId-1].height);	//C
			v2		= Vector(0.5f*WORLD_UNITSIZE,	0.5f*WORLD_UNITSIZE,	vertexIn[inId].height);		//D
		}
		else if( arctan > -1.0 )	//2
		{
			outId	= inId + blkY;
			v0		= Vector(0,					0,						vertexOut[outId].height);	//A
			v1		= Vector(0.5f*WORLD_UNITSIZE,	0.5f*WORLD_UNITSIZE,	vertexIn[inId].height);		//D
			v2		= Vector(WORLD_UNITSIZE,		0,						vertexOut[outId+1].height);	//B
		}
		else						//3
		{
			outId	= inId+blkY+1;
			v0		= Vector(WORLD_UNITSIZE,		0,						vertexOut[outId].height);	//B
			v1		= Vector(0.5f*WORLD_UNITSIZE,	0.5f*WORLD_UNITSIZE,	vertexIn[inId].height);		//D
			if( blkX == WORLD_TILE_CHUNK_UNIT_NUM-1 )
				v2	= Vector(WORLD_UNITSIZE,		WORLD_UNITSIZE,			vertexOut[outId+(WORLD_TILE_CHUNK_UNIT_NUM+1)].height);	//G, chunk边界上
			else
				v2	= Vector(1.5f*WORLD_UNITSIZE,	0.5f*WORLD_UNITSIZE,	vertexIn[inId+1].height);	//E
		}
	}
	else if ( deltaY > 1.0e-5 )
	{
		flt32 arctan = deltaX / deltaY;
		if( arctan < -1.0 )			//4
		{
			outId	= inId + blkY;
			if( blkX == 0 )
				v0	= Vector(0,					0,						vertexOut[outId].height);	//A，chunk边界上
			else
				v0	= Vector(-0.5f*WORLD_UNITSIZE,0.5f*WORLD_UNITSIZE,	vertexIn[inId-1].height);	//C
			v1		= Vector(0,					WORLD_UNITSIZE,			vertexOut[outId+(WORLD_TILE_CHUNK_UNIT_NUM+1)].height);	//F
			v2		= Vector(0.5f*WORLD_UNITSIZE,	0.5f*WORLD_UNITSIZE,	vertexIn[inId].height);		//D
		}
		else if ( arctan < 1.0 )	//5
		{
			outId	= inId + blkY + (WORLD_TILE_CHUNK_UNIT_NUM+1);
			v0		= Vector(0.5f*WORLD_UNITSIZE,	0.5f*WORLD_UNITSIZE,	vertexIn[inId].height);		//D
			v1		= Vector(0,					WORLD_UNITSIZE,			vertexOut[outId].height);	//F
			v2		= Vector(WORLD_UNITSIZE,		WORLD_UNITSIZE,			vertexOut[outId+1].height);	//G
		}
		else						//6
		{
			outId	= inId+blkY+1;
			if( blkX == WORLD_TILE_CHUNK_UNIT_NUM-1 )
				v0	= Vector(WORLD_UNITSIZE,		0,						vertexOut[outId].height);	//B, chunk边界上
			else
				v0	= Vector(1.5f*WORLD_UNITSIZE,	0.5f*WORLD_UNITSIZE,	vertexIn[inId+1].height);	//E
			v1		= Vector(0.5f*WORLD_UNITSIZE,	0.5f*WORLD_UNITSIZE,	vertexIn[inId].height);		//D
			v2		= Vector(WORLD_UNITSIZE,		WORLD_UNITSIZE,			vertexOut[outId+(WORLD_TILE_CHUNK_UNIT_NUM+1)].height);	//G
		}
	}
	else	//deltaY == 0
	{
		if( deltaX < 0 )
		{
			//1或4都可以，此处取1
			outId	= inId + blkY;
			v0		= Vector(0,					0,						vertexOut[outId].height);	//A
			if( blkX == 0 )
				v1	= Vector(0,					WORLD_UNITSIZE,			vertexOut[outId+(WORLD_TILE_CHUNK_UNIT_NUM+1)].height);	//F，chunk边界上
			else
				v1	= Vector(-0.5f*WORLD_UNITSIZE,0.5f*WORLD_UNITSIZE,	vertexIn[inId-1].height);	//C
			v2		= Vector(0.5f*WORLD_UNITSIZE,	0.5f*WORLD_UNITSIZE,	vertexIn[inId].height);		//D
		}
		else
		{
			//3或6都可以，此处取3
			outId	= inId+blkY+1;
			v0		= Vector(WORLD_UNITSIZE,		0,						vertexOut[outId].height);	//B
			v1		= Vector(0.5f*WORLD_UNITSIZE,	0.5f*WORLD_UNITSIZE,	vertexIn[inId].height);		//D
			if( blkX == WORLD_TILE_CHUNK_UNIT_NUM-1 )
				v2	= Vector(WORLD_UNITSIZE,		WORLD_UNITSIZE,			vertexOut[outId+(WORLD_TILE_CHUNK_UNIT_NUM+1)].height);	//G, chunk边界上
			else
				v2	= Vector(1.5f*WORLD_UNITSIZE,	0.5f*WORLD_UNITSIZE,	vertexIn[inId+1].height);	//E
		}
	}
	CalcHeight( v0, v1, v2, v, heightResult.normal );
	heightResult.isCollided		= true;
	heightResult.height			= v.z;
	heightResult.terrainHeight	= v.z;
	heightResult.liquidHeight	= chunk->GetLiquidHeight();
	heightResult.isInLiquid		= (chunk->GetLiquidHeight() - 1.3 > v.z )?true:false;

	return true;
}

bool CNdlWorldPickerBase::Pick(  Vector& rayPt,  Vector& rayDir, TPickResult& pickResult, sInt32 pickType,bool bNearest,float fMaxDistance) 
{
	CWorldTile* tile = m_worldBuffer->GetActiveTile();
	if (NULL == tile)
	{
		return false;
	}
	m_bNearest = bNearest;
	SetMaxRayCastDistance(fMaxDistance);
	// PickResult
	pickResult.Reset();
	bool bPickResult = false;


	CollideObjForEditer(pickType, bPickResult, rayPt, rayDir, pickResult);

	TVertInfo vert[5];
	TRay ray;
	ray.point	= rayPt;
	ray.dir		= rayDir;
	ray.flagDir[0] = ZnFloatFlag(rayDir.x); 
	ray.flagDir[1] = ZnFloatFlag(rayDir.y);

	// 垂直射线．
	if( (abs(rayDir.x)< 0.0001f)&&(abs(rayDir.y)<0.0001f) ) 
	{
		bool bDown = true;
		if (rayDir.z > 0 )
		{
			bDown = false;
		}
		else
		{
			THeightResult heightResult;
			if(GetHeight(rayPt.x,rayPt.y,heightResult))
			{
				if (heightResult.isInLiquid && rayPt.z > heightResult.liquidHeight)
				{//liquid picked
					pickResult.pickResultInfo[pickResult.pickResultCount].dist			= rayPt.z - heightResult.liquidHeight;
					pickResult.pickResultInfo[pickResult.pickResultCount].point			= Vector(rayPt.x,rayPt.y,heightResult.liquidHeight);
					pickResult.pickResultInfo[pickResult.pickResultCount].resultType	= emPT_Liquid;
					++pickResult.pickResultCount;
				}
				pickResult.pickResultInfo[pickResult.pickResultCount].resultType	= emPT_Terrain;
				pickResult.pickResultInfo[pickResult.pickResultCount].dist			= rayPt.z - heightResult.height;
				pickResult.pickResultInfo[pickResult.pickResultCount].point			= Vector(rayPt.x,rayPt.y,heightResult.height);
				pickResult.pickResultInfo[pickResult.pickResultCount].normal		= heightResult.normal;
				pickResult.pickResultInfo[pickResult.pickResultCount].normal.normalize();
				++pickResult.pickResultCount;
			}
		}
		BspTree::SIntersect* pIntersect = GetSimpleFloor(rayPt,true,bDown);
		if(pIntersect)
		{
			pickResult.pickResultInfo[pickResult.pickResultCount].resultType	= emPT_FloorObj;
			pickResult.pickResultInfo[pickResult.pickResultCount].point	= pIntersect->pos;
			pickResult.pickResultInfo[pickResult.pickResultCount].dist			= pIntersect->t;
			pickResult.pickResultInfo[pickResult.pickResultCount].vFacePos[0]	= pIntersect->vFacePos[0];
			pickResult.pickResultInfo[pickResult.pickResultCount].vFacePos[1]	= pIntersect->vFacePos[1];
			pickResult.pickResultInfo[pickResult.pickResultCount].vFacePos[2]	= pIntersect->vFacePos[2];
			pickResult.pickResultInfo[pickResult.pickResultCount].normal		= pIntersect->vNormal;
			++pickResult.pickResultCount;
		}
	}
	else
	{
		sInt32 curTile=0,curChunk=0,curUnit=0;
		TSquard tileSquard;
		TSquard chunkSquad;
		TSquard unitSquad;
		TCollideResult tileResult, chunkResult, unitResult;	

		tileSquard.halfGridSize[0] = CURRENTTILEORIGIN(0);
		tileSquard.halfGridSize[1] = CURRENTTILEORIGIN(1);
		tileSquard.pos[0]		= rayPt.x;
		tileSquard.pos[1]		= rayPt.y;
		//	while( curTile<4 ) 
		{
			tileSquard.origin[0]	= CURRENTTILEORIGIN( 0 );
			tileSquard.origin[1]	= CURRENTTILEORIGIN( 1 );
			if( NULL != tile )
			{
				ZnSetValue2<flt32>(tileSquard.height,tile->GetTotalHeight()/*tile->GetHeight()*/);
				if( CollideSquard( ray, tileSquard, tileResult ) ) 
				{
					chunkSquad.halfGridSize[0] = WORLD_CHUNKSIZE*0.5f;
					chunkSquad.halfGridSize[1] = WORLD_CHUNKSIZE*0.5f;
					ZnSetValue2<flt32>(chunkSquad.pos,tileSquard.pos);
					GetChunkIdFromPos( chunkSquad.grid, tileSquard.pos );
					curChunk = 0;
					int nMax = tile->GetRowColumn()[0]>tile->GetRowColumn()[1]?tile->GetRowColumn()[0]:tile->GetRowColumn()[1];
					while( curChunk<(nMax*2+1) ) 
					{
						chunkSquad.origin[0]	= ChunkOrigin( chunkSquad.grid[0], tileSquard.origin[0] ,0);
						chunkSquad.origin[1]	= ChunkOrigin( chunkSquad.grid[1], tileSquard.origin[1] ,1);
						CWorldChunk* worldChunk = tile->GetChunk( chunkSquad.grid[0], chunkSquad.grid[1] );
						if( NULL != worldChunk ) 
						{
							pickResult.pickResultInfo[pickResult.pickResultCount].resultChunk	= worldChunk;
							CollideObjInChunk(worldChunk,rayPt,rayDir,pickResult,pickType);
							ZnSetValue2<flt32>(chunkSquad.height,worldChunk->GetHeight());

							// PickResult

							if( CollideSquard( ray, chunkSquad, chunkResult )) 
							{
								if ((emPT_Terrain & pickType))
								{
									(CollideLiquidInChunk(worldChunk,rayPt,rayDir,pickResult));
									if(IsNeedCheck(worldChunk))
									{
										unitSquad.halfGridSize[0] = WORLD_UNITSIZE*0.5f;
										unitSquad.halfGridSize[1] = WORLD_UNITSIZE*0.5f;
										ZnSetValue2<flt32>( unitSquad.pos, chunkSquad.pos );
										GetUnitIdFromPos( unitSquad, chunkSquad.origin );
										curUnit					= 0;
										while( curUnit<(WORLD_TILE_CHUNK_UNIT_NUM*2+1) ) 
										{
											unitSquad.origin[0] = UnitOrigin( unitSquad.grid[0], chunkSquad.origin[0] );
											unitSquad.origin[1] = UnitOrigin( unitSquad.grid[1], chunkSquad.origin[1] );
											if( worldChunk->GetUnitVertex( unitSquad.grid[0], unitSquad.grid[1], vert ) ) 
											{
												worldChunk->GetMinMaxHeight( unitSquad.grid[0], unitSquad.grid[1], unitSquad.height[0], unitSquad.height[1] );
												if( CollideSquard(ray,unitSquad,unitResult) ) 
												{
													CollideUnit( ray, vert, pickResult );
												}
											}
											//Trace( "Collide unit[%d,%d](%d) \n", unitSquad.grid[0], unitSquad.grid[1], curUnit );
											if( !ZnIsValideId(unitResult.nextGrid[0],0,(WORLD_TILE_CHUNK_UNIT_NUM-1))
												||!ZnIsValideId(unitResult.nextGrid[1],0,(WORLD_TILE_CHUNK_UNIT_NUM-1)) ) 
											{
												break;
											}
											if( unitResult.rayScale > m_maxRayCastDistance )
												break;
											ZnSetValue2<sInt32>( unitSquad.grid, unitResult.nextGrid );
											ZnSetValue2<flt32>( unitSquad.pos, unitResult.nextPos );
											curUnit++;
										}
									}
								}
							}

						}
						//Trace( "Collide chunk[%d,%d](%d) \n", chunkSquad.grid[0], chunkSquad.grid[1], curChunk );
						if( !ZnIsValideId(chunkResult.nextGrid[0],0,(tile->GetRowColumn()[0]-1))
							||!ZnIsValideId(chunkResult.nextGrid[1],0,(tile->GetRowColumn()[1]-1)) ) 
						{
							break;
						}
						if( chunkResult.rayScale > m_maxRayCastDistance )
							break;
						ZnSetValue2<sInt32>( chunkSquad.grid, chunkResult.nextGrid );
						ZnSetValue2<flt32>( chunkSquad.pos, chunkResult.nextPos );
						curChunk++;
					}
				}
			}


			//Trace( "Collide tile[%d,%d](%d) \n", tileSquard.grid[0], tileSquard.grid[1], curTile );
			// 		if( !ZnIsValideId(tileResult.nextGrid[0],0,(WORLD_TILE_NUM-1))
			// 			||!ZnIsValideId(tileResult.nextGrid[1],0,(WORLD_TILE_NUM-1)) ) {
			// 				break;
			// 			}
			// 			if( tileResult.rayScale > m_maxRayCastDistance )
			// 				break;
			// 			ZnSetValue2<sInt32>( tileSquard.grid, tileResult.nextGrid );
			// 			ZnSetValue2<flt32>( tileSquard.pos, tileResult.nextPos );
			// 			curTile++;
		}
	}


	RetrieveNearest(pickResult);
	return (pickResult.pickResultCount>0);
}
// bool CNdlWorldPickerBase::CollideObj( CWorldTile* worldTile, CResMgr* resMgr,  Vector& rayPt,  Vector& rayDir, TPickResult& castResult, sInt32 pickType )
// {
// 	if( castResult.pickResultCount >= MAX_PICK_OBJ_COUNT )
// 		return false;
// 
// 	bool bCollide = false;
// 	for( size_t i=0; i<resMgr->GetStaticModelList().size(); i++ ) {
// 		TObjectInfo* objInfo = resMgr->GetStaticModelList()[i];
// 			if( castResult.pickResultCount >= MAX_PICK_OBJ_COUNT )
// 				break;
// 
// 			bCollide |= CollideModel( objInfo,  rayPt, rayDir, castResult, i,pickType );
// 	}
// 	RetrieveNearest(castResult);
// 
// 	return bCollide;
// }

bool CNdlWorldPickerBase::CollideModel( TObjectInfo* obj,   Vector& rayPt,  Vector& rayDir, TPickResult& castResult, int id , sInt32 pickType)
{
	MexAnimCtrl* pAnimCtrl = NULL;	// 替代原先的model
	bool bPick = false;
// 	if (pickType & emPT_Obj)
// 	{
// 		//if( obj->model == NULL ) 
// 		//	return false;
// 		//m_modelPick->SetTarget( obj->model);
// 		pAnimCtrl = obj->model;
// 		if( pAnimCtrl && pAnimCtrl->GetWorldBBox()->Intersect(rayPt, rayDir) )
// 		{
// 			Vector vHit;
// 			if( pAnimCtrl->IntersectRay( &rayPt, &rayDir, &vHit ) )
// 			{
// 				castResult.pickResultInfo[castResult.pickResultCount].resultType	= emPT_Obj;
// 				castResult.pickResultInfo[castResult.pickResultCount].resultId		= id;
// 				castResult.pickResultInfo[castResult.pickResultCount].resultObjInfo	= obj;
// 				Vector l = vHit-rayPt;
// 				castResult.pickResultInfo[castResult.pickResultCount].dist		= l.length();
// 				castResult.pickResultCount++;
// 				bPick = true;
// 			}
// 			else // 如果只有emmiter, 返回true
// 			{
// 				IMexGeometry* pGeo = pAnimCtrl->GetMex()->GetGeometry();
// 				if( pGeo && pGeo->GetChunkCount() == 0 && pAnimCtrl->HasEmitter() )
// 				{
// 					castResult.pickResultInfo[castResult.pickResultCount].resultType	= emPT_Obj;
// 					castResult.pickResultInfo[castResult.pickResultCount].resultId		= id;
// 					castResult.pickResultInfo[castResult.pickResultCount].resultObjInfo	= obj;
// 					Vector l = vHit-rayPt;
// 					castResult.pickResultInfo[castResult.pickResultCount].dist		= l.length();
// 					castResult.pickResultCount++;
// 					bPick = true;
// 				}
// 			}
// 		}
// 	}
	if (!bPick && pickType & emPT_ObjBBox)
	{
		pAnimCtrl = obj->model;
		if( pAnimCtrl )
		{
			if( pAnimCtrl->GetWorldBBox()->Intersect(rayPt, rayDir) )
			{
				castResult.pickResultInfo[castResult.pickResultCount].resultType	= emPT_ObjBBox;
				castResult.pickResultInfo[castResult.pickResultCount].resultId		= id;
				castResult.pickResultInfo[castResult.pickResultCount].resultObjInfo	= obj;
				castResult.pickResultInfo[castResult.pickResultCount].dist			= 0;
				castResult.pickResultCount++;
				bPick = true;
			}
		}
	}
	if (!bPick && pickType & emPT_AlphaBox)
	{
		if (obj->m_pAlphaBox)
		{
			BspTree::SIntersect* pIntersect = obj->m_pAlphaBox->GetNearestIntersect(rayPt,rayDir);
			if (pIntersect)
			{
				castResult.pickResultInfo[castResult.pickResultCount].resultType	= emPT_AlphaBox;
				castResult.pickResultInfo[castResult.pickResultCount].resultId		= id;
				castResult.pickResultInfo[castResult.pickResultCount].resultObjInfo	= obj;
				castResult.pickResultInfo[castResult.pickResultCount].point	= pIntersect->pos;
				castResult.pickResultInfo[castResult.pickResultCount].dist			= pIntersect->t;
				castResult.pickResultInfo[castResult.pickResultCount].vFacePos[0]	= pIntersect->vFacePos[0];
				castResult.pickResultInfo[castResult.pickResultCount].vFacePos[1]	= pIntersect->vFacePos[1];
				castResult.pickResultInfo[castResult.pickResultCount].vFacePos[2]	= pIntersect->vFacePos[2];
				castResult.pickResultInfo[castResult.pickResultCount].normal			= pIntersect->vNormal;
				castResult.pickResultCount++;
				bPick = true;
			}
		}
	}
	if(!bPick && pickType & emPT_FloorObj)
	{
		if (obj->m_pModelFloor)
		{
			BspTree::SIntersect* pIntersect = obj->m_pModelFloor->GetNearestIntersect(rayPt,rayDir);
			if (pIntersect)
			{
				castResult.pickResultInfo[castResult.pickResultCount].resultType	= emPT_FloorObj;
				castResult.pickResultInfo[castResult.pickResultCount].resultId		= id;
				castResult.pickResultInfo[castResult.pickResultCount].resultObjInfo	= obj;
				castResult.pickResultInfo[castResult.pickResultCount].point	= pIntersect->pos;
				castResult.pickResultInfo[castResult.pickResultCount].dist			= pIntersect->t;
				castResult.pickResultInfo[castResult.pickResultCount].vFacePos[0]	= pIntersect->vFacePos[0];
				castResult.pickResultInfo[castResult.pickResultCount].vFacePos[1]	= pIntersect->vFacePos[1];
				castResult.pickResultInfo[castResult.pickResultCount].vFacePos[2]	= pIntersect->vFacePos[2];
				castResult.pickResultInfo[castResult.pickResultCount].normal			= pIntersect->vNormal;
				castResult.pickResultCount++;
				bPick = true;
			}
		}
		CollideSupperFloor(obj, rayPt, rayDir, castResult, id, bPick);
	}
	
	if(!bPick && pickType & emPT_CollisionObj)
	{
		if (obj->m_pCollision)
		{
			BspTree::SIntersect* pIntersect = obj->m_pCollision->GetNearestIntersect(rayPt,rayDir,TRUE);
			if (pIntersect)
			{
				castResult.pickResultInfo[castResult.pickResultCount].resultType	= emPT_CollisionObj;
				castResult.pickResultInfo[castResult.pickResultCount].resultId		= id;
				castResult.pickResultInfo[castResult.pickResultCount].resultObjInfo	= obj;
				castResult.pickResultInfo[castResult.pickResultCount].point	= pIntersect->pos;
				castResult.pickResultInfo[castResult.pickResultCount].dist			= pIntersect->t;
				castResult.pickResultInfo[castResult.pickResultCount].vFacePos[0]	= pIntersect->vFacePos[0];
				castResult.pickResultInfo[castResult.pickResultCount].vFacePos[1]	= pIntersect->vFacePos[1];
				castResult.pickResultInfo[castResult.pickResultCount].vFacePos[2]	= pIntersect->vFacePos[2];
				castResult.pickResultInfo[castResult.pickResultCount].normal			= pIntersect->vNormal;
				castResult.pickResultCount++;
				bPick = true;
			}
		}
	}
	if(!bPick && pickType & emPT_CameraCollisionObj)	// emPT_CameraCollisionObj是emPT_CollisionObj的子集，所以只判断一种
	{
		if (obj->m_pCameraCollision != NULL)
		{
			BspTree::SIntersect* pIntersect = obj->m_pCameraCollision->GetNearestIntersect(rayPt, rayDir, TRUE);
			if (pIntersect)
			{
				castResult.pickResultInfo[castResult.pickResultCount].resultType	= emPT_CameraCollisionObj;
				castResult.pickResultInfo[castResult.pickResultCount].resultId		= id;
				castResult.pickResultInfo[castResult.pickResultCount].resultObjInfo	= obj;
				castResult.pickResultInfo[castResult.pickResultCount].point	= pIntersect->pos;
				castResult.pickResultInfo[castResult.pickResultCount].dist			= pIntersect->t;
				castResult.pickResultInfo[castResult.pickResultCount].vFacePos[0]	= pIntersect->vFacePos[0];
				castResult.pickResultInfo[castResult.pickResultCount].vFacePos[1]	= pIntersect->vFacePos[1];
				castResult.pickResultInfo[castResult.pickResultCount].vFacePos[2]	= pIntersect->vFacePos[2];
				castResult.pickResultInfo[castResult.pickResultCount].normal			= pIntersect->vNormal;
				castResult.pickResultCount++;
				bPick = true;
			}
		}
		else
		{
			/*
			* Author: 2012-10-29 17:40:04 wangshuai
			* Desc:   如果物件定义了2.5D碰撞, 执行阻挡碰撞
			*/
			if (obj->m_bIs2_5dColi)
			{
				BspTree::SIntersect* pIntersect = obj->m_pCollision->GetNearestIntersect(rayPt, rayDir, TRUE);
				if (pIntersect)
				{
					castResult.pickResultInfo[castResult.pickResultCount].resultType	= emPT_CollisionObj;
					castResult.pickResultInfo[castResult.pickResultCount].resultId		= id;
					castResult.pickResultInfo[castResult.pickResultCount].resultObjInfo	= obj;
					castResult.pickResultInfo[castResult.pickResultCount].point	= pIntersect->pos;
					castResult.pickResultInfo[castResult.pickResultCount].dist			= pIntersect->t;
					castResult.pickResultInfo[castResult.pickResultCount].vFacePos[0]	= pIntersect->vFacePos[0];
					castResult.pickResultInfo[castResult.pickResultCount].vFacePos[1]	= pIntersect->vFacePos[1];
					castResult.pickResultInfo[castResult.pickResultCount].vFacePos[2]	= pIntersect->vFacePos[2];
					castResult.pickResultInfo[castResult.pickResultCount].normal			= pIntersect->vNormal;
					castResult.pickResultCount++;
					bPick = true;
				}
			}
		}
	}

	//else if(pickType & emPT_ViewBlock)
	//{
	//}

//	Vector pickPos	= rayPt;

	//if( m_modelPick->PickObjects( pickPos, rayDir ) )
	//{
	//	const NiPick::Results& kResults = m_modelPick->GetResults();
	//	if( kResults.GetSize() > 0 )
	//	{
	//		for( int i=0; i<kResults.GetSize(); ++i )
	//		{
	//			NiPick::Record* pkRecord											= kResults.GetAt(i);
	//			castResult.pickResultInfo[castResult.pickResultCount].resultType	= thisPickType;
	//			castResult.pickResultInfo[castResult.pickResultCount].resultId		= id;
	//			castResult.pickResultInfo[castResult.pickResultCount].resultObject	= pkRecord->GetAVObject();
	//			castResult.pickResultInfo[castResult.pickResultCount].resultObjInfo	= obj;
	//			castResult.pickResultInfo[castResult.pickResultCount].point			= pkRecord->GetIntersection();
	//			castResult.pickResultCount++;
	//			if( castResult.pickResultCount >= MAX_PICK_OBJ_COUNT )
	//				break;
	//		}
	//	}
	//	return true;
	//}
	//m_modelPick->SetFrontOnly(true);

	return bPick;
}

bool CNdlWorldPickerBase::SimplePickCollision(flt32 posX, flt32 posY, flt32 posZ,TPickResult& castResult )
{
	castResult.Reset();
// 	bool bRet = false;
// 	CWorldTile* ptile = CURRENTTILE;
// 	CWorldChunk* pchunk = ptile->GetChunkFromPos(posX,posY);
// 	CResMgr* resMgr = ptile->GetCResMgr();

	if (GetSimpleFloor(Vector(posX,posY,10000.f),false,true,true))
	{
		castResult.pickResultCount = 1;
		castResult.pickResultInfo[0].resultType = emPT_FloorObj;
		return true;
	}
	if (GetSimpleCollision(Vector(posX,posY,10000.f)))
	{
		castResult.pickResultCount = 1;
		castResult.pickResultInfo[0].resultType = emPT_CollisionObj;
		return true;
	}
	if (GetSimpleFloor(Vector(posX,posY,10000.f)))
	{
		castResult.pickResultCount = 1;
		castResult.pickResultInfo[0].resultType = emPT_FloorObj;
		return true;
	}
// 	BOOL bInFloor = false;
// 	GetFloorZByXY(posZ,posX,posY,0,&bInFloor,NULL,NULL);
// 	if (bInFloor)
// 	{
// 		castResult.pickResultCount = 1;
// 		castResult.pickResultInfo[0].resultType = emPT_FloorObj;
// 		return true;
// 	}
 	return false;
}

void CNdlWorldPickerBase::GetCameraTerrainIntersection(int nChunkX, 
													   int nChunkY,
													   D3DXVECTOR3* pvFrom, 
													   D3DXVECTOR3* pvDir, 
													   std::vector<ChunkIntersection>* pvectorIntersection)
{
	CWorldTile* tile = m_worldBuffer->GetActiveTile();
	if( !tile )
		return;

	CWorldChunk* chunk = tile->GetChunk(nChunkX, nChunkY);
	if(!chunk)
		return;

	chunk->GetCameraTerrainIntersection(pvFrom, pvDir, pvectorIntersection);
}
// BspTree::SIntersect* CNdlWorldPickerBase::GetNearestIntersect(Vector& vPos, Vector& vDir)
// {
// 	CWorldTile* activeTile = m_worldBuffer->GetActiveTile();
// 	if( !activeTile )
// 		return NULL;
// 
// 
// 	BspTree* pModelFloor = activeTile->GetModelFloor();
// 	if( pModelFloor )
// 	{
// 		BspTree::SIntersect* pIntersect = pModelFloor->GetNearestIntersect( vPos, vDir );
// 		return pIntersect;
// 		
// 	}
// 	return NULL;
// }
BspTree::SIntersect* CNdlWorldPickerBase::GetFloorZByXY( float fCurrentZ, float x, float y,  DWORD* pdwRet, D3DXVECTOR3* pvNormal )
{
	guardfunc;
	//CSALocker locker(this);
	BOOL bHitFloor = FALSE;
	// 用返回值判断是否碰到模型地面，所以初始化参数[QL]
	//if( pdwRet )
	//	*pdwRet = 0;
	//if( bInFloor )
	//	*bInFloor = FALSE;

	CWorldTile* activeTile = m_worldBuffer->GetActiveTile();
	if( !activeTile )
		return NULL;

	//动态Floor，目前游戏不读取dynamic floor数据，所以此处先不实现[QL]

	//////////////////////////////////////////////////////////////////////////
	// GetDynamicCollision...
	//{
	//	Vector		vPos(x,y,fCurrentZ+WORLD_HEIGHT);
	//	Vector		vDir(0,0,-1);
	//	BOOL bNormal = FALSE;
	//	if (*pvNormal)
	//	{
	//		bNormal = TRUE;
	//	}
	//	BspTree::SIntersect* pIntersect = DynamicCollision.GetNearestIntersectCmpZ( vPos, vDir, bNormal, fCurrentZ+WORLD_HEIGHT );
	//	if( pIntersect )
	//	{
	//		fModelFloorZ = pIntersect->pos.z;
	//		bHitFloor = TRUE;
	//		if( *pvNormal )
	//		{
	//			vNormalFloor.x = pIntersect->vNormal.x;
	//			vNormalFloor.y = pIntersect->vNormal.y;
	//			vNormalFloor.z = pIntersect->vNormal.z;
	//		}
	//	}
	//	if( bHitFloor )
	//	{
	//		//DynamicCollision.Destroy();
	//		return fModelFloorZ;
	//	}
	//}

	//////////////////////////////////////////////////////////////////////////

	// 过滤

	CWorldChunk* pChunk = activeTile->GetChunkFromPos(x,y);
	BspTree::SIntersect* pIntersect = NULL;
	if( pChunk)
	{
		Vector vPos(x,y,fCurrentZ);
		Vector vDir(0,0,-1);
		bool bNormal = pvNormal? TRUE : FALSE;
		pIntersect = pChunk->GetNearestIntersectCmpZ( vPos, vDir, bNormal, fCurrentZ );
		if( pIntersect )
		{
			bHitFloor = TRUE;
			if( pvNormal )
			{
				pvNormal->x = pIntersect->vNormal.x;
				pvNormal->y = pIntersect->vNormal.y;
				pvNormal->z = pIntersect->vNormal.z;
			}

			if( pdwRet )
				*pdwRet |= emPT_FloorObj;
			
			return pIntersect;
		}
	}
	return NULL;
	unguard;
}


BspTree::SIntersect* CNdlWorldPickerBase::GetSimpleCollision(  Vector& vPos,bool bNearest,bool bDown)
{
	guardfunc;

	CWorldTile* activeTile = m_worldBuffer->GetActiveTile();
	if( !activeTile )
		return NULL;

	//////////////////////////////////////////////////////////////////////////
	CWorldChunk* pChunk = activeTile->GetChunkFromPos(vPos.x,vPos.y);
	return pChunk->GetSimpleCollision(vPos,bNearest,bDown);
	unguard;
}

BspTree::SIntersect* CNdlWorldPickerBase::GetSimpleFloor( Vector& vPos ,bool bNearest,bool bDown ,bool bSupper,BOOL bNormal )
{
	guardfunc;

	CWorldTile* activeTile = m_worldBuffer->GetActiveTile();
	if( !activeTile )
		return NULL;

	//////////////////////////////////////////////////////////////////////////
	CWorldChunk* pChunk = activeTile->GetChunkFromPos(vPos.x,vPos.y);
	if( !pChunk )
		return NULL;
	return pChunk->GetSimpleFloor(vPos,bNearest,bDown,bSupper,bNormal);
	unguard;

}

bool CNdlWorldPickerBase::CollideObjInChunk( CWorldChunk* worldChunk, Vector& rayPt, Vector& rayDir, TPickResult& castResult , sInt32 pickType )
{
	if (worldChunk->GetLoadLevel() < CWorldChunk::eModelLoaded)
	{
		return false;
	}
	if (worldChunk->IsLockFlag())
	{
		return false;
	}
	worldChunk->LockFlag(true);
	bool isMyLocked = false;
	if (!worldChunk->IsDataInUsing(CWorldChunk::eModel))
	{
		worldChunk->MarkDataUsing(CWorldChunk::eModel,true);
		isMyLocked = true;
	}
	CResMgr* resMgr = worldChunk->GetParentTile()->GetCResMgr();
	bool bCollide = false;
	for( size_t i=0; i<worldChunk->GetStaticModelList().size(); i++ )
	{
		if( castResult.pickResultCount >= MAX_PICK_OBJ_COUNT )
			break;
		sInt32 id		= worldChunk->GetStaticModelList()[i];
		if( id < resMgr->GetStaticModelList().size() )
		{
			bool isCollided = false;
			for(sInt32 x = 0; x < castResult.pickResultCount; ++x)
			{
				if(castResult.pickResultInfo[x].resultId == id)
				{
					isCollided = true;
					break;
				}
			}
			if (isCollided)
			{
				continue;
			}
			TObjectInfo* objInfo	= resMgr->GetStaticModelList()[id];
			bCollide |= CollideModel( objInfo,  rayPt, rayDir, castResult, id,pickType );
		}
	}
	if (isMyLocked)
	{
		worldChunk->MarkDataUsing(CWorldChunk::eModel,false);
	}
	worldChunk->LockFlag(false);
	return bCollide;
}

void CNdlWorldPickerBase::RetrieveNearest( TPickResult &castResult )
{
	if (GetNearest())
	{
		float fMinDist = 100000.0f;
		int close_id=0;
		for (sInt32 i = 0; i < castResult.pickResultCount; ++i)
		{
			if (castResult.pickResultInfo[i].dist < fMinDist)
			{
				fMinDist = castResult.pickResultInfo[i].dist;
				close_id = i;						
			}
		}
		if( close_id != 0 )
		{
			// 兑换数组下标clost_id和0的内容
			// 			TPickResultInfo tempInfo = castResult.pickResultInfo[close_id];
			// 			castResult.pickResultInfo[close_id]	= castResult.pickResultInfo[0];
			// 			castResult.pickResultInfo[0] = tempInfo;
			castResult.pickResultInfo[0] = castResult.pickResultInfo[close_id];
		}
		if( castResult.pickResultCount > 0 )
			castResult.pickResultCount = 1;
	}
}

bool CNdlWorldPickerBase::CollideLiquidInChunk( CWorldChunk* worldChunk, Vector& rayPt, Vector& rayDir, TPickResult& castResult )
{
	if( castResult.pickResultCount >= MAX_PICK_OBJ_COUNT )
		return false;
	if (worldChunk->GetLiquidId() == RES_INVALID_ID || abs(rayDir.z )< 0.000001f)
	{
		return false;
	}
	float t = (worldChunk->GetLiquidHeight() - rayPt.z)/rayDir.z;
	float crossX = rayPt.x + t*rayDir.x;
	float crossY = rayPt.y + t*rayDir.y;
	if (crossX > worldChunk->Origin()[0] - WORLD_CHUNKSIZE/2
		&& crossX < worldChunk->Origin()[0] + WORLD_CHUNKSIZE/2
		&& crossY > worldChunk->Origin()[1] - WORLD_CHUNKSIZE/2
		&& crossY < worldChunk->Origin()[1] + WORLD_CHUNKSIZE/2
		)
	{
		castResult.pickResultInfo[castResult.pickResultCount].resultType	= emPT_Liquid;
		Vector crossPoint(crossX,crossY,worldChunk->GetLiquidHeight());
		castResult.pickResultInfo[castResult.pickResultCount].dist = (rayPt - crossPoint).length();
		castResult.pickResultInfo[castResult.pickResultCount].point = crossPoint;
// 		castResult.pickResultInfo[castResult.pickResultCount].normal = 
		++castResult.pickResultCount;
	}
	return false;
}
