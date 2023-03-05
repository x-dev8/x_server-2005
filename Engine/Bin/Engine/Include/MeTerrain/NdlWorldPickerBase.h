/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	NdlWorldPickerBase.h
* Create: 	10/06/2006
* Desc:		计算和获取地表高度
* Author:	Yuan Ding
*
* Modify:	10/21, 增加Pick功能，鼠标点击屏幕，获取该点地形或模型上的位置
* Modify by: Qiu Li
*******************************************************************************/
#ifndef _NDL_NDLWORLDPICKERBASE_H__
#define _NDL_NDLWORLDPICKERBASE_H__

////////////////////////////////////////////////////////////////////////////////
class CWorld;
class CResMgr;
class CWorldChunk;
class CWorldBuffer;
class TObjectInfo;
////////////////////////////////////////////////////////////////////////////////
struct THeightResult
{
	bool		isCollided;
	Vector	normal;
	flt32		height;
	bool		isInLiquid;
	flt32		liquidHeight;
	uInt32		matId;			// 地形材质 id.	
	sInt32		zoneId;			// zone id.
	flt32		terrainHeight;	// TBD: 如果和模型碰撞,这个高度将返回.以后改成可以判断可见面的方式.
};

const sInt32 MAX_PICK_OBJ_COUNT	= 16;
enum emPickType
{
	emPT_Unknown	= 0x0,
	emPT_Terrain	= 0x1,
	emPT_Liquid		= 0x2,	
// 	emPT_Obj		= 0x4,	使用辅助模型，或者bbox的点选代替模型本身三角形的点选
	emPT_FloorObj	= 0x8,
	emPT_ViewBlock	= 0x10,
	emPT_Transport	= 0x20,
	emPT_CollisionObj= 0x40,
	emPT_MonsterQuad= 0x80,
	emPT_CameraCollisionObj=0x100,
	emPT_FlyRoute	= 0x200,
	emPT_NpcRoute	= 0x400,
	emPT_Click2Add	= 0x800,
	emPT_Flight		= 0x1000,
	emPT_ObjBBox	= 0x2000,
    emPT_NPC        = 0x4000,   
	emPT_AlphaBox	= 0x8000,
};

struct TPickResultInfo
{
	sInt32			resultType;
	sInt32			resultId;
	CWorldChunk*	resultChunk;
	TObjectInfo*	resultObjInfo;

	// 不赋值,节省赋值时间.
	Vector		point;
	Vector		normal;
	flt32			dist;
	Vector		vFacePos[3];

	void			Reset()
	{
		resultType		= emPT_Unknown;
		resultId		= RES_INVALID_ID;
		resultChunk		= NULL;
		resultObjInfo	= NULL;
	}
};

struct TPickResult
{
	sInt32			pickResultCount;
	TPickResultInfo	pickResultInfo[MAX_PICK_OBJ_COUNT];	
	sInt32			vertId[2];

	void			Reset()
	{
		pickResultCount	= 0;		
		for( sInt32 i=0; i<MAX_PICK_OBJ_COUNT; i++ ) 
			pickResultInfo[i].Reset();
	}
};
////////////////////////////////////////////////////////////////////////////////
class CNdlWorldPickerBase 
{
	friend CWorldTile;
public:
					CNdlWorldPickerBase( CWorld* world );
					~CNdlWorldPickerBase();
	
	bool			GetHeight( flt32 posX, flt32 posY, flt32& height ) const;
	bool			GetHeight(CWorldTile* pTile, flt32 posX, flt32 posY, flt32& height ) const;
	bool			GetHeight( flt32 posX, flt32 posY, THeightResult& heightResult ) const;
	bool			GetHeight(CWorldTile* pTile, flt32 posX, flt32 posY, THeightResult& heightResult ) const;

	bool			Pick(  Vector& rayPt,  Vector& rayDir, TPickResult& castResult, sInt32 pickType = emPT_Terrain ,bool bNearest = true,float fMaxDistance = MAX_RAYCAST_DISTANCE);	

	virtual bool IsNeedCheck( CWorldChunk* worldChunk )
	{
		return 									(!worldChunk->IsCulled());
	}
	bool			SimplePickCollision(flt32 posX, flt32 posY, flt32 posZ,  TPickResult& castResult);	
	bool			CollideModel( TObjectInfo* obj,   Vector& rayPt,  Vector& rayDir, TPickResult& castResult, int id , sInt32 pickType);
	float			GetMaxRayCastDistance() const { return m_maxRayCastDistance; }
	void			SetMaxRayCastDistance(float val) { m_maxRayCastDistance = val; }
// 	BspTree::SIntersect* GetNearestIntersect(Vector& vPos, Vector& vDir);
	float			GetZByXY( float fCurrentZ,float x, float y,DWORD dwFlag, BOOL* bInFloor = NULL, 
							DWORD* pdwRet = NULL, BOOL bIsRole = false, D3DXVECTOR3 *pNormal = NULL);
	void			GetCameraTerrainIntersection(int nChunkX, int nChunkY,D3DXVECTOR3* pvFrom, D3DXVECTOR3* pvDir, std::vector<ChunkIntersection>* pvectorIntersection);

	inline bool		IsShadow( float nTileX, float nTileY , CWorldTile* tile = 0 );

	bool			GetSort() const { return m_bSort; }
	void			SetSort(bool val) { m_bSort = val; }
	bool			GetNearest() const { return m_bNearest; }
	void			SetNearest(bool val) { m_bNearest = val; }
	BspTree::SIntersect*			GetFloorZByXY( float fCurrentZ,	float x, float y, DWORD* pdwRet,	D3DXVECTOR3* pvNormal );
protected:
	virtual void CollideObjForEditer( sInt32 pickType, bool bPickResult, Vector& rayPt, Vector& rayDir, TPickResult& pickResult )
	{
	}
	virtual void CollideSupperFloor( TObjectInfo* obj, Vector& rayPt, Vector& rayDir, TPickResult &castResult, int id, bool& bPick )
	{
	}

	bool			CollideObjInChunk( CWorldChunk* worldChunk,  Vector& rayPt,  Vector& rayDir, TPickResult& castResult , sInt32 pickType);
// 	bool			CollideObj( CWorldTile* worldTile, CResMgr* resMgr,  Vector& rayPt,  Vector& rayDir, TPickResult& castResult , sInt32 pickType);
	bool			CollideLiquidInChunk(CWorldChunk* worldChunk,  Vector& rayPt,  Vector& rayDir, TPickResult& castResult );
	void			RetrieveNearest( TPickResult &castResult );
	bool			CalcHeight(Vector v0, Vector v1, Vector v2, Vector& v, Vector& normal)const;

	BspTree::SIntersect*			GetSimpleCollision( Vector& vPos,bool bNearest = false,bool bDown = true);	// 判断从[x,y]垂直向下或向上是否有碰到碰撞模型
	BspTree::SIntersect*			GetSimpleFloor( Vector& vPos,bool bNearest = false,bool bDown = true ,bool bSupper = false,BOOL bNormal = FALSE);	// 判断从[x,y]垂直向下或向上是否有碰到碰撞模型

	CWorldBuffer*	m_worldBuffer;
	float			m_maxRayCastDistance;
	bool			m_bSort;
	bool			m_bNearest;
};
	
#include "NdlWorldPickerBase.inl"

#endif	// _NDL_NDLWORLDPICKERBASE_H__
