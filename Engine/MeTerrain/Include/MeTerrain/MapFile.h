/*******************************************************************************
*  Copyright ShenWang 2008 - All Rights Reserved
*
* File: 	MapFile.h
* Date: 	10/06/06
* Desc:		地图数据格式
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef _MAP_MAPFILE_H__
#define _MAP_MAPFILE_H__

#include "MeTerrain/MapDef.h"
#include "MeTerrain/MapUtil.h"
#include "MeTerrain/WorldChunk.h"
////////////////////////////////////////////////////////////////////////////////
#pragma pack(push,1)

////////////////////////////////////////////////////////////////////////////////
struct THead					// 公共头
{
	sInt8	segment[4];			// 
	uInt32	size;			
};

////////////////////////////////////////////////////////////////////////////////
// Road Doodad Res file,地图索引文件
struct TRoadResHead 
{
	THead	head;				// WIFF
	uInt32	version;
};

struct TWIFTileTable
{
	sInt8	segment[4];			// WIFT
	uInt8	tile[WORLD_TILE_NUM][WORLD_TILE_NUM];		// 
};

////////////////////////////////////////////////////////////////////////////////
// WLS file
struct TWLSHead
{
	THead	head;				// head.segment	WLSH
};

struct TWLSHeightTable 
{
	sInt16	heightOut[17][17];	
	sInt16	heightIn[16][16];	
};

////////////////////////////////////////////////////////////////////////////////
// WTD file
struct TWTDHead 
{
	sInt8	segment[4];			// segment WTDH
	uInt32	version;			
	uInt32	offsTexNameTable;	// 纹理的偏移
	uInt32	offsAlphaTable;		// 透明表的偏移
	uInt32	offsShadowTable;	
	uInt32	offsLiquidTable;	
	uInt32	offsModelNameTable;	// 模型
	uInt32	offsMapObjNameTable;// 地图物体
	uInt32	offsDoodNameTable;	// 装饰物
	uInt32	offsChunkTable;		
	uInt32	offsZoneTable;
	uInt32	offsFogTable;
	uInt32	offsLightTable;
	uInt32	offsLightMapTable;	// 模型灯光图
	uInt32	offsKeep4;
	flt32	reachableAngle;
	uInt32	row;
	uInt32	column;
};

struct TWTDNameTable 
{	
	THead	head;						// tex-WNTT;model-WNMT;mapObj-WNOT;dood-WNDT
	//sInt8	texName[TEXTURE_NAME_LEN];	// head.size *( texName[64] )
};

struct TWTDTexIdTable				 
{
	THead	head;				// WTIT
	//uInt32	texId;
};

struct TWTDAlphaTable 
{	
	THead	head;				// WAMD
};

struct TWTDAlphaMap
{
	uInt8	alpha[WORLD_TILE_CHUNK_ATOM_NUM*32];
};

struct TWTDShadowTable 
{	
	THead	head;				// WAMD
};

struct TWTDShadowMap
{
	uInt8	shadow[WORLD_TILE_CHUNK_ATOM_NUM*8];	// 64 bit.
};

//struct TWTDStaticModelTable		
//{
//	THead	head;				// WSMT
//};

struct TWTNMapObjTable
{
	THead	head;				// WMOT
};

struct TWTDMapObjInfo 
{
	sInt32		id;
	flt32		pos[3];
	flt32		off[3];
	flt32		rot[3];
	flt32		scl[3];
};

struct TWTDObjLightmapInfo	// 模型实例灯光图
{
	bool			bCastShadow;			// 是否投影到其他模型上，默认为true
	uInt8			ucLightMapScale;		// 灯光图分辨率枚举，ELightMapScale，默认LMS_128
	uInt8			ucInstanceNum;			// 静态模型实例个数
};

struct TWTDObjInstance
{
	uInt8				ucChunkIndex;
	uInt8				ucLightMapIndex;
	sInt32				nStaticMeshVertexCount;
	flt32				LightMapUVOffset[2];
	flt32				LightMapUVScale[2];
};

struct TWTDOneObjLightmapColorData
{
	sInt16				nGeoChunkIndex;
	sInt32				nColorDataIndex;
};

struct TWTDObjLightmapColorData	// 模型已生成的灯光数据
{
	TWTDObjLightmapColorData(): usColorDataCount(0), pColorData(NULL) {}
	uInt16				usColorDataCount;
	TWTDOneObjLightmapColorData* pColorData;		// 指向全局光照图列表的索引
};

struct TWTDLiquidTable 
{	
	THead	head;				// WNLQ
};

struct TWTDLiquidInfo
{
	char	name[RES_NAME_LEN];
	uInt8	count;
};

struct TWTDChunkTable
{
	THead	head;				// WCTT
};

struct TWTDLayer
{
	uInt32		texId[RES_LAYER_NUM];
	uInt32		alphaId[RES_LAYER_NUM - 1];
	uInt32		shadowId;
	uInt32		roadResId;//reserve for the 5th texture
};

struct TWTDHeightTable 
{
	flt32	heightB[9][9];		// out vertex
	flt32	heightM[8][8];		// in vertex
};
struct TWTDVertexColorTable 
{
	COLORREF	vertexColorB[9][9];		// out vertex
	COLORREF	vertexColorM[8][8];		// in vertex
};

struct _TWTDNormal	
{
	sInt8		value[3];
};

struct TWTDNormalTable		
{
	sInt8		segment[4];		// WTTT
	_TWTDNormal	normalB[9][9];
	_TWTDNormal	normalM[8][8];
};

struct TWTDChunkInfo
{
	uInt32			culled;
	uInt32			chunk[2];		// X,Y坐标
	TWTDLayer		layerTable;		// 样式
	TWTDHeightTable	heightTable;	// 高度
	TWTDNormalTable	normalTable;	// 法线
	uInt32			holes;			// 洞，每Bit 对应一个　unit.
	uInt32			envId;			// 地区 id.
	uInt32			sizeModel;		// 模型	
	uInt32			offsLiquid;		// 水面 id.
	uInt32			sizeLiquid;
	uInt32			sizeDoodad;		// 草	102 version from here 
	TWTDVertexColorTable	vertexColorTable;
 	TTextureInfo	textureInfo[RES_LAYER_NUM];//103 version 
};

struct TWTDDoodadInfo
{
// 	uInt32			chunk;		// chunk序号
	uInt32			sizeDoodad;		// 草	102 version from here 
};

struct TWTDRoadInfo
{
// 	uInt32			chunk;		// chunk序号
	uInt32		roadResId;			//
};

struct TWTDModelRef 
{
	sInt8		segment[4];			// WCDR
	sInt32		modelId;		
};

struct TWTDDoodesRef 
{
	sInt32							doodesId;		
	uInt32							mulevelUnit;
};

struct TWTDLiquid {
	sInt8		segment[4];			// WTLT
	sInt32		liquidId;	
	flt32		height;
	NiColor		color;
};

////////////////////////////////////////////////////////////////////////////////

struct TWTDEnv {
	char	zoneName[RES_NAME_LEN];	
	sInt32	lightId;
	sInt32	fogId;
};

struct TWTDLight {
	char		lightName[RES_NAME_LEN];
	uInt32		ambientLight;
	uInt32		diffuseLight;
	uInt32		specularLight;
	flt32		directionLight[3];
	uInt32		colorSunless;
	uInt32		forReserve;
};

struct TWTDFog {
	char		fogName[RES_NAME_LEN];
	uInt32		fogLight;
	flt32		fogNearLight;
	flt32		fogFarLight;
};

struct TWTDLightMap
{
	THead	head;				// WLMP
};

////////////////////////////////////////////////////////////////////////////////
// 模型灯光图数据，编辑器读取
struct TMeshLightMapHead 
{
	THead	head;				// WMLM
	uInt32	version;
};

// 静态灯光数据，编辑器读取
struct TStaticLightHead 
{
	THead	head;				// WSLR
	uInt32	version;
};

#pragma pack(pop)

#endif	// _MAP_MAPFILE_H__