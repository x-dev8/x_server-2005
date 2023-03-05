/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	WorldWriteStream.h
* Date: 	01/24/2007
* Desc:
*
*******************************************************************************/
#ifndef _MAP_WORLDWRITESTREAM_H__
#define _MAP_WORLDWRITESTREAM_H__


class CWorld;
class CWorldBuffer;
class CWorldTile;
class CWorldChunk;
class CResEditMgr;
////////////////////////////////////////////////////////////////////////////////
class CWorldWriteStream
{
public:
					CWorldWriteStream( CWorld* world );
	virtual			~CWorldWriteStream();

	bool			WriteAllTile( const char* worldPath );

	void			CopyAllTilesToNewFolder( const char* worldPath );
	bool			WriteTile( sInt32 tileId );
	bool			WriteTile( CWorldTile* worldTile );
	bool			WriteMonsterData(CWorldTile* worldTile, const char* pathName );
	bool			WriteGameWtd(CWorldTile* worldTile );
	bool			WriteWtd(const char* pName, CWorldTile* worldTile,bool bClean = true );
	bool			WriteRoadRes(const char* pName, CWorldTile* worldTile);
	bool			WriteDoodadRes(const char* pName, CWorldTile* worldTile);
	bool			WriteAlphaRes(const char* pName, CWorldTile* worldTile);
	bool			RemoveReadOnly( const char* pName );
	bool			WriteZoneRes( const char* pName );
	bool			WriteLightmapColorData( const char* pName );
	bool			WriteStaticLightsRes( const char* pName );
protected:
	bool			WriteTextureTable( FILE* stream, CResEditMgr* resMgr );
	bool			WriteAlphaTable( FILE* stream, CResEditMgr* resMgr );

	void			CalAlphaMap( CNdlAlphaRes* res, TWTDAlphaMap &alphaMap,bool isShadow = false );
	bool			WriteShadowTable( FILE* stream, CResEditMgr* resMgr );
	bool			WriteRoadTable( FILE* stream, CResEditMgr* resMgr );
	bool			WriteLiquidTable( FILE* stream, CResEditMgr* resMgr );
	bool			WriteModelTable( FILE* stream, std::vector< CWorldRes* >& staticModelRefList );
	bool			WriteDoodadTable( FILE* stream, CResEditMgr* resMgr );
	bool			WriteMapObjTable( FILE* stream, std::vector< TObjectInfo* >& staticModelList, flt32* origin );
	bool			WriteChunk( FILE* stream, CWorldTile* tile );
	bool			WriteEnv( FILE* stream, CResEditMgr* resMgr);
	bool			WriteLight( FILE* stream, CResEditMgr* resMgr);
	bool			WriteFog( FILE* stream, CResEditMgr* resMgr);
	bool			WriteLightMapTable( FILE* stream, CWorldTile* tile );
	
	//sInt32			Push( CNdlModelRes* res, CResMgr* resMgr );
	void			RecalculateRefObj(CWorldTile* tile, std::vector< TObjectInfo* >& staticModelList);		// 重新计算chunk里static model的引用情况
	//bool			GetPosInfoByModelWorldBound( NiBound WorldBound, CWorldTile* tile, sInt32 chunk[4][2] );	//计算World Bound边界在当前tile的chunk ID
	bool			GetPosInfoByModelWorldBound( Vector2 vMin, Vector2 vMax, CWorldTile* tile, sInt32 chunk[4][2] );	//计算World Bound边界所在tile和chunk

	void			ModifyModelRefInTile( CWorldTile* tile, const sInt32* beginChunk, const sInt32* endChunk, sInt32 modelId);	//把model加入tile
	void			ModifyModelRefInOneChunk( CWorldTile* tile, const sInt32* chunk, sInt32 modelId);	//把model加入chunk

private:
	CWorld*			m_world;
	void			CopyFolder(LPCTSTR psourceFolder,LPCTSTR pdestFolder);
protected:
	bool			DirectAddNewRefModel(std::vector< CWorldRes* >& destList,CWorldRes* pRes);
	bool			DirectAddNewModel(std::vector< TObjectInfo* >& destList,std::vector< TObjectInfo* >& sourceList,size_t refOldId,sInt32 refNewId);
	bool			AddSubRefModel(std::vector< CWorldRes* >& destList,CWorldRes* pRes,const char* subName);
	bool			AddSubModel(std::vector< TObjectInfo* >& destList,std::vector< TObjectInfo* >& sourceList,size_t refOldId,sInt32 refNewId,sInt32 subIndex);

	void			GetTileChunkIdFromPos(  sInt32* chunk, flt32* pos ,CWorldTile* tile);
};



#endif	// _MAP_WORLDWRITESTREAM_H__
