/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	MapUtil.h
* Create: 	10/06/2006
* Desc:		定义地图通用数据结构和函数
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef _MAP_MAPUTIL_H__
#define _MAP_MAPUTIL_H__
#include "3dsmax/gfloat.h"
#include "MeTerrain/SwDebug.h"
////////////////////////////////////////////////////////////////////////////////
#define MAX_RAYCAST_DISTANCE		(WORLD_TILESIZE/**0.5f*/)		// 最远 pick 距离.
#define CULL_DISTANCE				(WORLD_TILESIZE)			// 最远 显示距离.
#define MAX_OBJECT_DISPLAY_DISTANCE	(WORLD_TILESIZE*0.25f)		// 最远 物体 显示距离.
#define MAX_ACTOR_DISPLAY_DISTANCE	(WORLD_TILESIZE*0.2f)		// 最远 生物 显示距离.
#define MAX_DOODAD_DISPLAY_DISTANCE	(WORLD_TILESIZE*0.1f)		// 最远 装饰物 显示距离.
#define MAX_EFFECT_DISPLAY_DISTANCE	(WORLD_TILESIZE*0.2f)		// 最远 特效 显示距离.
#define MAP_GRID_SIZE (2.56f)
#define DEFAULT_FAR_PLANE	200.f	// 定义默认远端裁剪距离，用于雾距离计算，大约7*29米，取近似值200

////////////////////////////////////////////////////////////////////////////////
#define HEIGHTMAP_UNIT			(WORLD_UNITSIZE*0.5f)

//   -------- 
//  | \  1 / |
//  |0	 *  2|	
//  | /  3 \ |
//   -------- 
enum znFaceOrder
{
	FO_None = -1,
	FO_Zero = 0,
	FO_One,
	FO_Two,
	FO_Three
};

enum znMapDir2d
{
	MD2D_Crack	= -1,
	MD2D_Left,
	MD2D_Top,
	MD2D_Right,
	MD2D_Down
};

////////////////////////////////////////////////////////////////////////////////
struct TUnitInfo
{
	sInt32			tile[2];
	sInt32			chunk[2];
	sInt32			unit[2];
	bool			isHole;
};

struct TVertInfo
{
	sInt32			vert[2];
	flt32			pos[3];
	flt32			normal[3];
};

struct TFaceInfo 
{
	znFaceOrder		order;
	TVertInfo		vertex[3];
};

struct TBox2D
{
	flt32			minPt[2];
	flt32			maxPt[2];
};

struct TBox3D
{
	flt32			minPt[3];
	flt32			maxPt[3];
};

////////////////////////////////////////////////////////////////////////////////
// 左下　Grid 为 (0,0) 向右上为(+x,+y) 没有 负值
#define ChunkFromPos( x )		ZnFloor2Int( ((x))/WORLD_CHUNKSIZE )
#define UnitFromPos( x )		ZnFloor2Int( ((x)+WORLD_CHUNK_ORIGIN)/WORLD_UNITSIZE )
#define HalfUnitFromPos( x )	ZnFloor2Int( ((x)+WORLD_CHUNK_ORIGIN)/(WORLD_UNITSIZE*0.5f) )
#define AtomFromPos( x )		ZnFloor2Int( ((x)+WORLD_CHUNK_ORIGIN)/WORLD_ATOMSIZE )

////////////////////////////////////////////////////////////////////////////////
#define GlChunkFromGlUnit(x)	( (x)/WORLD_TILE_CHUNK_UNIT_NUM )
#define UnitFromGlUnit(x)		( (x)%WORLD_TILE_CHUNK_UNIT_NUM )

// a 为在父节点内的 id ，t 为Tile的中心坐标,c为Chunk的中心坐标
// a 不能为 unsigned 类型,否则计算会出错.
#define ChunkOrigin( a, t ,i )		((t)-CURRENTTILE->GetOrigin()[i]+(a)*WORLD_CHUNKSIZE+(WORLD_CHUNKSIZE*0.5f))
#define UnitOrigin( a, c )		((c)-(WORLD_CHUNKSIZE*0.5f)+(a)*WORLD_UNITSIZE+(WORLD_UNITSIZE*0.5f))

////////////////////////////////////////////////////////////////////////////////
#define swMaxInt				(0x7FFFFFFF)
#define swInfinity				(1e30f)				// huge number which should be larger than any valid number used
#define swEpsilonFlt32			(1.192092896e-07f)	// smallest positive number such that 1.0+swEpsilonFlt32 != 1.0

////////////////////////////////////////////////////////////////////////////////
inline float ZnBias( float x, float biasAmt )
{
	// WARNING: not thread safe
	static float lastAmt = -1;
	static float lastExponent = 0;
	if( lastAmt != biasAmt )
	{
		lastExponent = log( biasAmt ) * -1.4427f; // (-1.4427 = 1 / log(0.5))
	}
	return pow( x, lastExponent );
}


// Over 15x faster than: (int)floor(value)
inline sInt32 ZnFloor2Int( flt32 a )
{
	sInt32 CtrlwdHolder;
	sInt32 CtrlwdSetter;
	sInt32 RetVal;
	__asm 
	{
		fld    a					// push 'a' onto the FP stack
		fnstcw CtrlwdHolder			// store FPU control word
		movzx  eax, CtrlwdHolder	// move and zero extend word into eax
		and    eax, 0xFFFFF3FF		// set all bits except rounding bits to 1
		or     eax, 0x00000400		// set rounding mode bits to round down
		mov    CtrlwdSetter, eax	// Prepare to set the rounding mode -- prepare to enter plaid!
		fldcw  CtrlwdSetter			// Entering plaid!
		fistp  RetVal				// Store floored and converted (to int) result
		fldcw  CtrlwdHolder			// Restore control word
	}
	return RetVal;
}

// Over 15x faster than: (int)ceil(value)
inline sInt32 ZnCeil2Int( flt32 a )
{
	sInt32 CtrlwdHolder;
	sInt32 CtrlwdSetter;
	sInt32 RetVal;
	__asm 
	{
		fld    a					// push 'a' onto the FP stack
		fnstcw CtrlwdHolder			// store FPU control word
		movzx  eax, CtrlwdHolder	// move and zero extend word into eax
		and    eax, 0xFFFFF3FF		// set all bits except rounding bits to 1
		or     eax, 0x00000800		// set rounding mode bits to round down
		mov    CtrlwdSetter, eax	// Prepare to set the rounding mode -- prepare to enter plaid!
		fldcw  CtrlwdSetter			// Entering plaid!
		fistp  RetVal				// Store floored and converted (to int) result
		fldcw  CtrlwdHolder			// Restore control word
	}
	return RetVal;
}

// Fast, accurate ftol.
inline sInt32 ZnFloat2Int( flt32 a )
{
	sInt32 CtrlwdHolder;
	sInt32 CtrlwdSetter;
	sInt32 RetVal;
	__asm 
	{
		fld    a					// push 'a' onto the FP stack
			fnstcw CtrlwdHolder			// store FPU control word
			movzx  eax, CtrlwdHolder	// move and zero extend word into eax
			and    eax, 0xFFFFF3FF		// set all bits except rounding bits to 1
			or     eax, 0x00000C00		// set rounding mode bits to round down
			mov    CtrlwdSetter, eax	// Prepare to set the rounding mode -- prepare to enter plaid!
			fldcw  CtrlwdSetter			// Entering plaid!
			fistp  RetVal				// Store and converted (to int) result
			fldcw  CtrlwdHolder			// Restore control word
	}
	return RetVal;
}

inline bool ZnIsValideId( sInt32 id, sInt32 minId, sInt32 maxId )
{
	if( id < minId || id > maxId )
		return false;

	return true;
}

inline sInt32 ZnNextOneIdLoop( sInt32 id, sInt32 minId, sInt32 maxId )
{
	Assert( (id >=minId) && (id<=maxId) );

	id++;
	if( id>maxId )
	{
		id = minId;
	}
	return id;
}

inline sInt32 ZnPrevOneIdLoop( sInt32 id, sInt32 minId, sInt32 maxId )
{
	Assert( (id >=minId) && (id<=maxId) );

	id--;
	if( id<minId )
		id = maxId;
}

inline sInt32 ZnUnitInt( sInt32 a )
{
	if( a < 0 )
		return -1;
	else
		return 1;
}

inline sInt32 ZnFloatFlag( flt32 a )
{
	if( a < 0.0f )
		return -1;
	else if( a > 0.0f )
		return 1;
	else
		return 0;
}


template< class T > 
inline T ZnAbs( const T& A )
{
	return (A>=(T)0) ? A : -A;
}


template< class T > 
inline T ZnMax( const T& A, const T& B )
{
	return (A>=B) ? A : B;
}

template< class T > 
inline T ZnMin( const T& A, const T& B )
{
	return (A<=B) ? A : B;
}

template< class T > 
inline T ZnClamp( const T&V, const T& minV, const T& maxV )
{
	if( V<minV ) 
		return minV;
	else if( V>maxV )
		return maxV;
	return V;
}

template< class T > 
inline void ZnSetValue2( T* dest, const T* src )
{
	memcpy( dest, src, sizeof(T)*2 );
}

bool SpliteFullPathToDataPathWithoutPostfix( LPCTSTR fullPath, char* texPath, char* texName );
bool SpliteFullPathToDataPath( LPCTSTR fullPath, char* texPath, char* texName );
bool GetRelativePathToWorldPath(LPCTSTR fullPath, char* texPath);
bool GetRelativePathToWorldPathWithoutPostfix(LPCTSTR fullPath, char* texPath);
inline void ConvertRGB2NiColor( COLORREF color, NiColor& niColor ) 
{
	niColor.r = ( color & 0xFF ) / 255.0f;
	niColor.g = ( (color >>  8) & 0xFF ) / 255.0f;
	niColor.b = ( (color >> 16) & 0xFF ) / 255.0f;
}

inline void ConvertNiColor2RGB( const NiColor& niColor, COLORREF& color ) 
{
	color = RGB(  ZnFloat2Int(niColor.r*255.0f)
		, ZnFloat2Int(niColor.g*255.0f)
		, ZnFloat2Int(niColor.b*255.0f) ) | 0xFF000000;
}

extern COLORREF	g_defaultLiquidColor;

inline Quaternion RotationArc( Vector& pUnitFrom, Vector& pUnitTo ) 
{
	Quaternion q;
	Vector c	= pUnitFrom.cross( pUnitTo );
	float   d	= pUnitFrom.dot( pUnitTo );
	float   s	= Sqrt( (1.0f + d) * 2.0f );
	if( s < 0.0001f )
		s = 0.0001f;
	q.x = c.x / s;
	q.y = c.y / s;
	q.z = c.z / s;
	q.w = s	 / 2.0f;
	return q;
}


void GetChunkIdFromPos(  sInt32* chunk, flt32* pos );


typedef bool (*swFileOperation)(LPCTSTR strPath,void* point);

bool	EnumFile(LPCTSTR strPath,swFileOperation opt,void* point,bool isRecursive);
flt32						GetAtan( Vector2 &tex);
#endif	// _MAP_MAPUTIL_H__

