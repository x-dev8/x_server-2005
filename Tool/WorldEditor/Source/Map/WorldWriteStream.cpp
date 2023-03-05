/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	WorldWriteStream.cpp
* Date: 	01/24/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "RapidXml/MeRapidXml.h"
#include "MeTerrain/world.h"
#include "MeTerrain/WorldRes.h"
#include "EditRes/NdlEditRes.h"
#include "MeTerrain/WorldTile.h"
#include "MeTerrain/NdlResMgr.h"
#include "MeTerrain/NdlGlobalResMgr.h"
#include "MeTerrain/WorldChunk.h"
#include "MeTerrain/WorldBuffer.h"
#include "WorldWriteStream.h"
#include "MeTerrain/MapConfigXml.h"
// #include "MeTerrain/FlyRouteXml.h"
#include "MeTerrain/NPCRouteXml.h"
#include "MeTerrain/SoundPointXml.h"
#include "tstring.h"
#include "Cipher/cipher_factory.h"
#include "MeTerrain/Lighting/StaticMeshInstance.h"
#include "MeTerrain/Lighting/MeshLightmapColorData.h"
#include "MeTerrain/Lighting/LightRes.h"
////////////////////////////////////////////////////////////////////////////////
namespace
{
	bool SetSame4Segment( sInt8* a, const char* b )	
	{
		return ( (a[0]=b[0]) && (a[1]=b[1]) && (a[2]=b[2]) && (a[3]=b[3]) );
	}
};

////////////////////////////////////////////////////////////////////////////////
CWorldWriteStream::CWorldWriteStream( CWorld* world )
{
	m_world = world;
}

CWorldWriteStream::~CWorldWriteStream()
{
	m_world = NULL;
}

bool CWorldWriteStream::WriteTile(sInt32 tileId)
{
	if (!WriteTile(m_world->GetWorldBuffer()->GetTile(tileId)))
		return false;
	else
		return true;
}

bool CWorldWriteStream::WriteTile(CWorldTile *worldTile)
{
	CStringA fileName;
	fileName.Format("%s\\%s",m_world->GetWorldPath(),worldTile->GetPathName());
	if (!WriteWtd(fileName, worldTile))
		return false;

	if (!CMapConfigXml::Instance()->RefreshTileMapInfo(worldTile))
	{
		Trace( "failed write Map.Config \n" );
	}

// 	if (!CFlyRouteXml::Instance()->RefreshTileFlyRoute(worldTile))
// 	{
// 		Trace( "failed write FlyRoute.config \n" );
// 	}

	if(!CSoundPointXml::Instance()->RefreshTileSoundPoint(worldTile))
	{
		Trace( "failed write SoundPoint.config \n" );
	}

	if (!CNPCRouteXml::Instance()->RefreshTileNPCRoute(worldTile))
	{
		Trace( "failed write NPCRoute.config \n" );
	}

	// 保存Monster数据
	WriteMonsterData(worldTile, fileName);

	if (fileName.Replace(".mew",".road"))
	{
		WriteRoadRes(fileName, worldTile);
	}

	if (fileName.Replace(".road",".grass"))
	{
		WriteDoodadRes(fileName, worldTile);
	}

	if (fileName.Replace(".grass",".alpha"))
	{
		WriteAlphaRes(fileName, worldTile);
	}

	if (WORLD_FILE_LASTEST_VERSION >= WORLD_FILE_LASTEST_108)
	{
		if (fileName.Replace(".alpha",".lmcd"))
		{
			WriteLightmapColorData(fileName);
		}
	}

	if (WORLD_FILE_LASTEST_VERSION >= WORLD_FILE_LASTEST_109)
	{
		if (fileName.Replace(".lmcd",".lights"))
		{
			WriteStaticLightsRes(fileName);
		}
	}
	return true;
}

bool CWorldWriteStream::WriteAllTile( const char* worldPath )
{
	
	// 先复制以前存在的.
	if( !m_world->HasName() ) {
		return false;
	}

	CopyAllTilesToNewFolder(worldPath);


	// 再保存缓存的.
	char fileName[MAX_PATH*2];
	std::list<sInt32>& list = m_world->m_worldBuffer->GetTilePRIList();
	std::list<sInt32>::iterator ite = list.begin();
	while (ite != list.end())
	{
		CWorldTile* worldTile = m_world->m_worldBuffer->GetTile(*ite);
		ASSERT(worldTile);
		if (worldTile->m_isLoad)
		{
			sprintf_s( fileName, "%s\\%s", worldPath, worldTile->GetPathName());
			if (!WriteWtd(fileName,worldTile))
			{
				Trace( "failed to write [%s] \n", fileName );
			}
		}
		++ite;
	}
	
	CMapConfigXml::Instance()->WriteMapInfo(worldPath);
	//CMapConfigXml::Instance()->WriteMapInfo(worldPath);
	return true;
}



bool CWorldWriteStream::WriteWtd(const char* pName, CWorldTile* tile,bool bClean)
{

	FILE* stream = NULL;
	try	{
		if( NULL == tile )
			throw( "GetTile error!" );
		CResEditMgr* resMgr	= (CResEditMgr*)tile->GetCResMgr( );
		if( NULL == resMgr )
			throw( "GetResMgr error!" );
		if (bClean)
		{
			resMgr->CleanUnusedResource();
		}
		
		WIN32_FIND_DATAA data;
		HANDLE hFind = FindFirstFileA(pName,&data);
		bool bFind = (hFind != INVALID_HANDLE_VALUE);
		if (bFind
			&&((data.nFileSizeHigh * (MAXDWORD+1)) + data.nFileSizeLow != 0))
		{
			CStringA bakPath(pName);
			bakPath += ".bak";
			if (!RemoveReadOnly(bakPath))
			{
				return false;
			}
			if(!CopyFileA(pName,bakPath,false))
			{
				::AfxMessageBox( _T("不能创建备份，保存失败!") );
				return false;
			}
		}


		if (!RemoveReadOnly(pName))
		{
			throw( "Can not write read-only file!" );
		}
		if( fopen_s( &stream, pName, "wb" ) != 0 ) {
			throw( "error open file!" );
		}
		flt32 origin[2];
		origin[0]	= tile->GetOrigin()[0];
		origin[1]	= tile->GetOrigin()[1];
		
		RecalculateRefObj(tile, resMgr->GetStaticModelList());

		TWTDHead head;
		memset( &head, 0, sizeof(TWTDHead) );
		SetSame4Segment( head.segment, "WTDH" );
		head.version = WORLD_FILE_LASTEST_VERSION;
		head.column = tile->GetRowColumn()[0];
		head.row = tile->GetRowColumn()[1];
		head.reachableAngle = tile->m_reachableAngle;
		sInt32 offHead				= ftell( stream );
		fwrite( &head, sizeof( TWTDHead ), 1, stream );
		
		// texture name table
		head.offsTexNameTable		= ftell( stream );
		if( !WriteTextureTable( stream, resMgr ) )
			throw ( "Error write texture table!" );

		head.offsAlphaTable			= ftell( stream );
// 		if( !WriteAlphaTable( stream, resMgr ) )
// 			throw ( "Error write alpha table!" );

		head.offsShadowTable		= ftell( stream );
		if( !WriteShadowTable( stream, resMgr ) )
			throw ( "Error write shadow table!" );

		head.offsLiquidTable		= ftell(stream);
		if( !WriteLiquidTable( stream, resMgr ) ) 
			throw ( "Error write liquid table!" );

		head.offsModelNameTable		= ftell( stream );
		if( !WriteModelTable( stream, resMgr->GetStaticModelRefList() ) )
			throw ( "Error write model table!" );

		head.offsMapObjNameTable	= ftell( stream );
		if( !WriteMapObjTable( stream, resMgr->GetStaticModelList(), origin ) )
			throw ( "Error write map obj table!" );
			
		head.offsDoodNameTable		= ftell(stream);
		if( !WriteDoodadTable( stream, resMgr ) )
			throw ( "Error write doodad table!" );
		
		head.offsZoneTable			= ftell( stream );
		if( !WriteEnv( stream, resMgr ) )
			throw ( "Error write Zone table!" );

		head.offsFogTable			= ftell( stream );
		if( !WriteFog( stream, resMgr ) )
			throw ( "Error write fog table!" );

		head.offsLightTable			= ftell( stream );
		if( !WriteLight( stream, resMgr ) )
			throw ( "Error write light table!" );

		// chunk table.
		head.offsChunkTable			= ftell( stream );
		if( !WriteChunk( stream, tile ) )
			throw ( "Error write chunk table!" );

		// lightmap
		if( head.version >= WORLD_FILE_LASTEST_107 )
		{
			head.offsLightMapTable		= ftell( stream );
			if( !WriteLightMapTable( stream, tile ) )
				throw( "Error write Light Map table!" );
		}

		// 再写 head
		fseek( stream, offHead, SEEK_SET );
		fwrite( &head, sizeof( TWTDHead ), 1, stream );
		
		fclose( stream );
		stream = NULL;
	}
	catch( const char* s )
	{
		Trace( "failed write wtd:[ %s ] \n", s );
		if( NULL != stream )
		{
			fclose( stream );
			stream	= NULL;
		}
		return false;
	}


	return true;
}


bool CWorldWriteStream::WriteGameWtd(  CWorldTile* tile )
{

	char gameWtdPath[MAX_PATH];
	GetGameWtdFileName(tile->GetPathName(),gameWtdPath);
	std::vector< CWorldRes* >	newModelRefList;
	std::vector< TObjectInfo* >	newModelList;
	bool bRet = true;
	FILE* stream = NULL;
	try	{
		if( NULL == tile )
			throw( "GetTile error!" );
		CResEditMgr* resMgr	= (CResEditMgr*)tile->GetCResMgr( );
		if( NULL == resMgr )
			throw( "GetResMgr error!" );
		resMgr->CleanUnusedResource(true);
		WIN32_FIND_DATAA data;
		HANDLE hFind = FindFirstFileA(gameWtdPath,&data);
		bool bFind = (hFind != INVALID_HANDLE_VALUE);
		if (bFind
			&&((data.nFileSizeHigh * (MAXDWORD+1)) + data.nFileSizeLow != 0))
		{
			CStringA bakPath(gameWtdPath);
			bakPath += ".bak";
			if (!RemoveReadOnly(bakPath))
			{
				throw( "Can not write read-only file!" );
			}
			if(!CopyFileA(gameWtdPath,bakPath,false))
			{
				::AfxMessageBox( _T("不能创建备份，保存失败!") );
				return false;
			}
		}
			
		if (!RemoveReadOnly(gameWtdPath))
		{
			throw( "Can not write read-only file!" );
		}
		if( fopen_s( &stream, gameWtdPath, "wb" ) != 0 ) {
			throw( "error open file!" );
		}

		CNdlGlobalResMgr* globalResMgr = theApp.GetWorld()->GetWorldBuffer()->GetGlobalResMgr();
		for (size_t i = 0; i < resMgr->GetStaticModelRefList().size();++i)
		{
			CWorldRes* pRes = resMgr->GetStaticModelRefList()[i];
			CStringA modelRealName(pRes->GetName());
			int speratorPos = modelRealName.Find('|');
			if (-1 != speratorPos)
			{//已经分解过了，跳过
				DirectAddNewModel(newModelList,resMgr->GetStaticModelList(),i,newModelRefList.size());
				DirectAddNewRefModel(newModelRefList,pRes);
				continue;
			}
			CNdlStaticModelRes* pGlobal	= dynamic_cast<CNdlStaticModelRes*>(globalResMgr->FindRefStaticModel(modelRealName));
			if (!pGlobal->IsSubExist())
			{//不存在子模型，跳过
				DirectAddNewModel(newModelList,resMgr->GetStaticModelList(),i,newModelRefList.size());
				DirectAddNewRefModel(newModelRefList,pRes);
				continue;
			}
#ifdef ST_EDITOR_WRITE
			int uiSize = pGlobal->GetModel()->GetArrayCount();

			for( int uiIdx = 0; uiIdx < uiSize; ++uiIdx )
			{
#ifdef ST_EDITOR_WRITE
				NiAVObject* pkChild = pGlobal->GetModel()->GetAt(uiIdx);
#endif
				if( !pkChild || NULL == pkChild->GetName())
					continue;
				if (pGlobal->IsSubChild(pkChild))
				{
					AddSubModel(newModelList,resMgr->GetStaticModelList(),i,newModelRefList.size(),uiIdx);
					AddSubRefModel(newModelRefList,pRes,pkChild->GetName());
				}
			}
#endif

		}





		flt32 origin[2];
		origin[0]	= tile->GetOrigin()[0];
		origin[1]	= tile->GetOrigin()[1];

		RecalculateRefObj(tile, newModelList);

		TWTDHead head;
		memset( &head, 0, sizeof(TWTDHead) );
		SetSame4Segment( head.segment, "WTDH" );
		head.version = WORLD_FILE_LASTEST_VERSION;
		head.column = tile->GetRowColumn()[0];
		head.row = tile->GetRowColumn()[1];
		head.reachableAngle = tile->m_reachableAngle;
		sInt32 offHead				= ftell( stream );
		fwrite( &head, sizeof( TWTDHead ), 1, stream );

		// texture name table
		head.offsTexNameTable		= ftell( stream );
		if( !WriteTextureTable( stream, resMgr ) )
			throw ( "Error write texture table!" );

		head.offsAlphaTable			= ftell( stream );
// 		if( !WriteAlphaTable( stream, resMgr ) )
// 			throw ( "Error write alpha table!" );

		head.offsShadowTable		= ftell( stream );
		if( !WriteShadowTable( stream, resMgr ) )
			throw ( "Error write shadow table!" );

		head.offsLiquidTable		= ftell(stream);
		if( !WriteLiquidTable( stream, resMgr ) ) 
			throw ( "Error write liquid table!" );

		head.offsModelNameTable		= ftell( stream );
		if( !WriteModelTable( stream, newModelRefList ) )
			throw ( "Error write model table!" );

		head.offsMapObjNameTable	= ftell( stream );
		if( !WriteMapObjTable( stream, newModelList, origin ) )
			throw ( "Error write map obj table!" );

		head.offsDoodNameTable		= ftell(stream);
		if( !WriteDoodadTable( stream, resMgr ) )
			throw ( "Error write doodad table!" );

		head.offsZoneTable			= ftell( stream );
		if( !WriteEnv( stream, resMgr ) )
			throw ( "Error write Zone table!" );

		head.offsFogTable			= ftell( stream );
		if( !WriteFog( stream, resMgr ) )
			throw ( "Error write fog table!" );

		head.offsLightTable			= ftell( stream );
		if( !WriteLight( stream, resMgr ) )
			throw ( "Error write light table!" );

		// chunk table.
		head.offsChunkTable			= ftell( stream );
		if( !WriteChunk( stream, tile ) )
			throw ( "Error write chunk table!" );

		// 再写 head
		fseek( stream, offHead, SEEK_SET );
		fwrite( &head, sizeof( TWTDHead ), 1, stream );

		fclose( stream );
		stream = NULL;
	}
	catch( const char* s )
	{
		Trace( "failed write wtd:[ %s ] \n", s );
		if( NULL != stream )
		{
			fclose( stream );
			stream	= NULL;
		}
		bRet = false;
	}

	for (size_t i = 0; i < newModelList.size(); ++i)
	{
		SAFE_DELETE(newModelList[i]);
	}
	for (size_t i = 0; i < newModelRefList.size(); ++i)
	{
		SAFE_DELETE(newModelRefList[i]);
	}
	return bRet;
}

bool CWorldWriteStream::WriteTextureTable( FILE* stream, CResEditMgr* resMgr )
{
	TWTDNameTable nameTable;
	SetSame4Segment(nameTable.head.segment,"WNTT");
	nameTable.head.size = resMgr->m_textureList.size();
	fwrite( &nameTable, sizeof(TWTDNameTable), 1, stream );

	for( uInt32 i = 0; i < nameTable.head.size; i++ ) {
		CWorldRes* p = resMgr->m_textureList[i];				
		fwrite( p->GetName(), RES_NAME_LEN*sizeof(char), 1, stream );
	}
	return true;
}

void CWorldWriteStream::CalAlphaMap( CNdlAlphaRes* res, TWTDAlphaMap &alphaMap,bool isShadow )
{
	uAlphaBit* alphaPtr		= res->m_maskData;
	uInt8* mapPtr		= alphaMap.alpha;
	for( sInt32 y=0; y<MASK_SIZE; y++) {
		for ( sInt32 x=0; x<(MASK_SIZE>>1); x++) 
		{
// 				uInt8 a		= UINT32HIGHTOUINT8(*alphaPtr++) ;
// 				uInt8 b		= UINT32HIGHTOUINT8(*alphaPtr++) ;
// 				*mapPtr++	= (b&0xF0)|((a&0xF0)>>4);
				*mapPtr++	= *alphaPtr++;

		}
	}
	//char name[MAX_PATH];
	//sprintf_s( name, "test\\alpha_w_%d.tga", i );
	//Ze::saveTGA( name, 64, 64, res->m_maskData );
}
bool CWorldWriteStream::WriteAlphaTable( FILE* stream, CResEditMgr* resMgr )
{
	TWTDAlphaTable alphaTable;
	SetSame4Segment( alphaTable.head.segment, "WAMD" );
	alphaTable.head.size = resMgr->GetAlphaCount();
	fwrite( &alphaTable, sizeof(TWTDAlphaTable), 1, stream );

	for( sInt32 i = 0; i<resMgr->GetAlphaCount(); i++ ) {
		TWTDAlphaMap alphaMap;
		memset( &alphaMap, 0, sizeof(TWTDAlphaMap) );	
		CNdlAlphaRes* res	= resMgr->GetAlpha( i );
		CalAlphaMap(res, alphaMap);

		fwrite( &alphaMap, sizeof(TWTDAlphaMap), 1, stream );
	}
	

	return true;
}

bool CWorldWriteStream::WriteShadowTable( FILE* stream, CResEditMgr* resMgr )
{
	TWTDShadowTable shadowTable;
	SetSame4Segment( shadowTable.head.segment, "WSMD" );
	shadowTable.head.size = resMgr->GetShadowCount();
	fwrite( &shadowTable, sizeof(TWTDShadowTable), 1, stream );

	for( sInt32 i=0; i<resMgr->GetShadowCount(); i++ ) {
		TWTDAlphaMap shadowMap;
		memset( &shadowMap, 0, sizeof(TWTDAlphaMap) );	
		CNdlAlphaRes* res = resMgr->GetShadow( i );
		CalAlphaMap(res, shadowMap,true);
		fwrite( &shadowMap, sizeof(TWTDAlphaMap), 1, stream );
	}
	return true;
}

bool CWorldWriteStream::WriteLiquidTable( FILE* stream, CResEditMgr* resMgr )
{
	
	
	return true;
}

//sInt32 CWorldWriteStream::Push( CNdlModelRes* res, CResMgr* resMgr )
//{
//	for( size_t i = 0; i < resMgr->m_tempModelList.size(); i++ ) {
//		CNdlModelRes* p = (CNdlModelRes*)resMgr->m_tempModelList[i];
//		if( strcmp( p->GetName(), res->GetName() ) == 0 ) {
//			return i;
//		}
//	}
//	resMgr->m_tempModelList.push_back( res );
//	return resMgr->m_tempModelList.size()-1;
//}
//#include "atlpath.h"


bool CWorldWriteStream::WriteModelTable( FILE* stream, std::vector< CWorldRes* >& staticModelRefList )
{
	TWTDNameTable nameTable;
	SetSame4Segment(nameTable.head.segment,"WNMT");
	nameTable.head.size = staticModelRefList.size();
	fwrite( &nameTable, sizeof(TWTDNameTable), 1, stream );
	for(uInt32 i = 0; i < nameTable.head.size; i++ ) {
 		CWorldRes* p = staticModelRefList[i];
// 		CPathA workPath;
// 		workPath.RelativePathTo(CWorld::GetAppDataCharDir(),FILE_ATTRIBUTE_DIRECTORY,p->GetName(),FILE_ATTRIBUTE_NORMAL);
//		fwrite( workPath.m_strPath.GetString(), RES_NAME_LEN*sizeof(char), 1, stream );
		fwrite( p->GetName(), RES_NAME_LEN*sizeof(char), 1, stream );
	}
	return true;
}

bool CWorldWriteStream::WriteDoodadTable( FILE* stream, CResEditMgr* resMgr )
{
	TWTDNameTable nameTable;
	SetSame4Segment(nameTable.head.segment,"WNDT");
	nameTable.head.size = resMgr->m_doodadRefList.size();
	fwrite( &nameTable, sizeof(TWTDNameTable), 1, stream );
	for( uInt32 i = 0; i < nameTable.head.size; i++ ) {
		CWorldRes* p = resMgr->m_doodadRefList[i];
		fwrite( p->GetName(), RES_NAME_LEN*sizeof(char), 1, stream );
	}
	return true;
}

bool CWorldWriteStream::WriteMapObjTable( FILE* stream, std::vector< TObjectInfo* >& staticModelList, flt32* origin )
{
	TWTNMapObjTable nameTable;
	SetSame4Segment(nameTable.head.segment,"WMOT");
	nameTable.head.size = staticModelList.size();
	fwrite( &nameTable, sizeof(TWTNMapObjTable), 1, stream );
	for( uInt32 i = 0; i < nameTable.head.size; i++ ) {
		TObjectInfo* p = staticModelList[i];

		TWTDMapObjInfo objInfo;
		for( sInt32 j=0; j<3; j++ ) {
			if( j < 2 ) {
				objInfo.pos[j]	= p->pos[j]-origin[j];
			}
			else {
				objInfo.pos[j]	= p->pos[j];
			}
			objInfo.off[j]	= p->offset[j];
			objInfo.rot[j]	= p->rotate[j];
			objInfo.scl[j]	= p->scale[j];
		}
		objInfo.id			= p->id;
		fwrite( &objInfo, sizeof(TWTDMapObjInfo), 1, stream );

		if( WORLD_FILE_LASTEST_VERSION >= WORLD_FILE_LASTEST_107 )
		{
			TWTDObjLightmapInfo lmInfo;
			lmInfo.bCastShadow = p->CastShadow();
			lmInfo.ucLightMapScale = p->GetLightMapScale();
			lmInfo.ucInstanceNum = p->GetStaticMeshIntanceCount();
			fwrite( &lmInfo, sizeof(TWTDObjLightmapInfo), 1, stream );

			TWTDObjInstance Ins;
			for( int idIns=0; idIns<p->GetStaticMeshIntanceCount(); ++idIns )
			{
				StaticMeshInstance* pInstance = p->GetStaticMeshInstance(idIns);
				assert(pInstance);
				memset(&Ins, 0, sizeof(TWTDObjInstance));
				Ins.ucChunkIndex = pInstance->GetChunkIndex();
				Ins.nStaticMeshVertexCount = pInstance->GetVertexCount();
				if( pInstance->GetLayer() )
				{
					Ins.ucLightMapIndex = pInstance->GetLayer()->LightMapIndex;
					Ins.LightMapUVOffset[0] = pInstance->GetLayer()->LightMapUVOffset.x;
					Ins.LightMapUVOffset[1] = pInstance->GetLayer()->LightMapUVOffset.y;
					Ins.LightMapUVScale[0] = pInstance->GetLayer()->LightMapUVScale.x;
					Ins.LightMapUVScale[1] = pInstance->GetLayer()->LightMapUVScale.y;
				}				
				fwrite( &Ins, sizeof(TWTDObjInstance), 1, stream );
			}
		}
		if( WORLD_FILE_LASTEST_VERSION >= WORLD_FILE_LASTEST_108 )
		{
			// 保存格式和TWTDObjLightmapColorData保持一致
			const std::map<sInt16, sInt32>& ColorData = p->GetColorData();
			sInt16 count = ColorData.size();
			fwrite( &count, sizeof(uInt16), 1, stream );
			std::map<sInt16, sInt32>::const_iterator iter = ColorData.begin();
			for( ; iter != ColorData.end(); ++iter )
			{
				sInt16 key = iter->first;
				sInt32 nColorIndex = iter->second;
				fwrite( &key, sizeof(sInt16), 1, stream );
				fwrite( &nColorIndex, sizeof(sInt32), 1, stream );
			}
		}
	}
	
	return true;
}

bool CWorldWriteStream::WriteChunk( FILE* stream, CWorldTile* tile )
{
	TWTDChunkTable chunkTable;
	memset( &chunkTable, 0, sizeof(TWTDChunkTable) );
	SetSame4Segment( chunkTable.head.segment, "WCTT" ); 
	sInt32 chunkOff = ftell( stream );
	fwrite( &chunkTable, sizeof(TWTDChunkTable), 1, stream );
	
	sInt32 envId = -1;
	if (tile->GetChunkTotal() > 0)
	{
		CWorldChunk *firstChunk = tile->GetChunk(0, 0);
		if (firstChunk != NULL)
			envId = firstChunk->m_envId;
	}

	for( sInt32 chunkId=0; chunkId<(tile->GetChunkTotal()); chunkId++ ) {
		TWTDChunkInfo chunkInfo;
		memset( &chunkInfo, 0, sizeof(TWTDChunkInfo) );

		CWorldChunk* worldChunk = tile->m_chunckTable[chunkId];
		Assert( NULL != worldChunk );
		Assert( worldChunk->m_chunk[0] == (chunkId%tile->GetRowColumn()[0]) );
		Assert( worldChunk->m_chunk[1] == (chunkId/tile->GetRowColumn()[0]) );

		chunkInfo.chunk[0]	= worldChunk->m_chunk[0];
		chunkInfo.chunk[1]	= worldChunk->m_chunk[1];
		chunkInfo.envId	= envId;
		chunkInfo.culled	= worldChunk->IsCulled();

		// Layer
		memset( &(chunkInfo.layerTable), -1, sizeof(TWTDLayer) );
		for( sInt32 j = 0; j<RES_LAYER_NUM; j++ ) {
			chunkInfo.layerTable.texId[j]	= worldChunk->m_texture[j];
			if (worldChunk->m_texture[j] != RES_INVALID_ID)
			{
				chunkInfo.textureInfo[j]		= worldChunk->m_texInfo[j];
			}
			if( j < (RES_LAYER_NUM-1) )	{
				chunkInfo.layerTable.alphaId[j] = worldChunk->m_alpha[j];
			}
		}
		chunkInfo.layerTable.shadowId	= worldChunk->m_shadow;
		chunkInfo.layerTable.roadResId	= worldChunk->m_road;
		// height & normal table
		memset( &(chunkInfo.heightTable), 0, sizeof(TWTDHeightTable) );
		memset( &(chunkInfo.vertexColorTable), 0xffff, sizeof(TWTDVertexColorTable) );
		memset( &(chunkInfo.normalTable), 0, sizeof(TWTDNameTable) );
		SetSame4Segment( chunkInfo.normalTable.segment, "WTTT" ); 
		for( sInt32 x = 0; x < (WORLD_TILE_CHUNK_UNIT_NUM+1); x++ )	{
			for( sInt32 y = 0; y < (WORLD_TILE_CHUNK_UNIT_NUM+1); y++ )	{
				chunkInfo.heightTable.heightB[x][y] = worldChunk->m_vertexOut[y*(WORLD_TILE_CHUNK_UNIT_NUM+1)+x].height;
				chunkInfo.vertexColorTable.vertexColorB[x][y] = worldChunk->m_vertexOut[y*(WORLD_TILE_CHUNK_UNIT_NUM+1)+x].niColor;
				for( sInt32 axis=0; axis<3; axis++ ) {
					chunkInfo.normalTable.normalB[x][y].value[axis] = worldChunk->m_vertexOut[y*(WORLD_TILE_CHUNK_UNIT_NUM+1)+x].normal[axis];
				}
				if( x < WORLD_TILE_CHUNK_UNIT_NUM && y < WORLD_TILE_CHUNK_UNIT_NUM ) {
					chunkInfo.heightTable.heightM[x][y] = worldChunk->m_vertexIn[y*WORLD_TILE_CHUNK_UNIT_NUM+x].height;
					chunkInfo.vertexColorTable.vertexColorM[x][y] = worldChunk->m_vertexIn[y*(WORLD_TILE_CHUNK_UNIT_NUM)+x].niColor;
					for( sInt32 axis=0; axis<3; axis++ ) {
						chunkInfo.normalTable.normalM[x][y].value[axis] = worldChunk->m_vertexIn[y*WORLD_TILE_CHUNK_UNIT_NUM+x].normal[axis];
					}
				}
			}
		}
		uInt32 offChunk			= ftell( stream );
		fwrite( &chunkInfo, sizeof(TWTDChunkInfo), 1, stream );

		chunkInfo.sizeModel		= worldChunk->m_staticModelList.size();
		for( size_t modelId=0; modelId<chunkInfo.sizeModel; modelId++ ) {
			TWTDModelRef modelRef;
			SetSame4Segment( modelRef.segment, "WCDR" );
			modelRef.modelId		= worldChunk->m_staticModelList[modelId]; 
			fwrite( &modelRef, sizeof(TWTDModelRef), 1, stream );
		}
		chunkInfo.offsLiquid	= ftell( stream );
		chunkInfo.sizeLiquid	= 0;
		{
			chunkInfo.sizeLiquid	= 1;
			TWTDLiquid liquid;
			SetSame4Segment( liquid.segment, "WTLT" );
			liquid.liquidId		= worldChunk->m_liquidId; 
			liquid.height		= worldChunk->m_liquidHeight;
			ConvertRGB2NiColor(worldChunk->m_liquidColor,liquid.color);
			fwrite( &liquid, sizeof(TWTDLiquid), 1, stream );
		}
		chunkInfo.sizeDoodad = 0;//worldChunk->m_doodadList.size();
// 		for (size_t doodadID = 0; doodadID < chunkInfo.sizeDoodad; ++doodadID)
// 		{
// 			TWTDDoodesRef doodes;
// 			doodes.doodesId = worldChunk->m_doodadList[doodadID]->mdoodadId;
// 			doodes.mulevelUnit = worldChunk->m_doodadList[doodadID]->mulevelUnit;
// 			fwrite( &doodes, sizeof(TWTDDoodesRef), 1, stream );
// 			fwrite(worldChunk->m_doodadList[doodadID]->m_pDoodadMap,sizeof(TDoodadInfo)*doodes.mulevelUnit*doodes.mulevelUnit,1,stream);
// 		}
		uInt32 offOldPos		= ftell( stream );
		fseek( stream, offChunk, SEEK_SET );
		fwrite( &chunkInfo, sizeof(TWTDChunkInfo), 1, stream );
		fseek( stream, offOldPos, SEEK_SET );
	}

	return true;
}

void CWorldWriteStream::RecalculateRefObj(CWorldTile* tile, std::vector< TObjectInfo* >& staticModelList)
{
	// 删除所有chunk的reference obj
	for( int chunkX = 0; chunkX<tile->GetRowColumn()[0]; chunkX++ )
	{
		for( int chunkY = 0; chunkY<tile->GetRowColumn()[1]; chunkY++ )
		{
			CWorldChunk* worldChunk = tile->GetChunk( chunkX, chunkY );

			if( NULL == worldChunk || worldChunk->m_staticModelList.size() == 0) 
				continue;

			//std::vector<sInt32>::iterator it	= worldChunk->m_staticModelList.begin();
			//for(;it!=worldChunk->m_staticModelList.end();it++)
			//{
			//	worldChunk->m_staticModelList.erase(it);
			//}
			worldChunk->m_staticModelList.clear();
		}
	}

	// 先根据modelWorldBound从tile和chunk中删除modelId，然后根据新的world bound把modelId加入场景
	for(size_t i=0; i<staticModelList.size(); i++)
	{
		sInt32		chunkList[4][2];

		// 获取world bound
		Vector2 vMin, vMax;
		TObjectEditInfo* pObjInfo = (TObjectEditInfo*)staticModelList[i];
		//Me3d_Matrix mat;
		//pObjInfo->model->CalcTransformMatrix( &mat );
		//pObjInfo->model->UpdateWorldBBox( &mat );
		//vMin.x = 10000.f;
		//vMin.y = 10000.f;
		//vMax.x = -10000.f;
		//vMax.y = -10000.f;

		//Box* pWorldBox = pObjInfo->model->GetWorldBBox();
		//for(int i=0; i<8; i++)
		//{
		//	vMin.x = min(vMin.x, pWorldBox->v[i].x);
		//	vMin.y = min(vMin.y, pWorldBox->v[i].y);
		//	vMax.x = max(vMax.x, pWorldBox->v[i].x);
		//	vMax.y = max(vMax.y, pWorldBox->v[i].y);
		//}
		vMin.x = pObjInfo->model->GetWorldMin().x;
		vMin.y = pObjInfo->model->GetWorldMin().y;
		vMax.x = pObjInfo->model->GetWorldMax().x;
		vMax.y = pObjInfo->model->GetWorldMax().y;


		if( GetPosInfoByModelWorldBound(vMin, vMax, tile, chunkList) )
		{
			//
			//0---------1
			//|			|
			//|			|
			//|			|
			//2---------3
			//
			// 把modelId加入tiles
			sInt32 chunkBegin[2], chunkEnd[2];	//当前tile里，chunk的起始值和结束值
			chunkBegin[0] = min(chunkList[0][0],chunkList[1][0]);	//0位置所在chunk X
			chunkBegin[1] = min(chunkList[0][1],chunkList[2][1]);	//0位置所在chunk Y
			chunkEnd[0] = max(chunkList[0][0],chunkList[1][0]);		//1位置所在chunk X
			chunkEnd[1] = max(chunkList[0][1],chunkList[2][1]);		//2位置所在chunk Y

			ModifyModelRefInTile(tile, chunkBegin, chunkEnd, i);
		}

		//NiBound modelWorldBound = staticModelList[i]->model->GetWorldBound();
		//if( GetPosInfoByModelWorldBound(modelWorldBound, tile, chunkList) )
		//{
		//	//
		//	//0---------1
		//	//|			|
		//	//|			|
		//	//|			|
		//	//2---------3
		//	//
		//	// 把modelId加入tiles
		//	sInt32 chunkBegin[2], chunkEnd[2];	//当前tile里，chunk的起始值和结束值
		//	chunkBegin[0] = chunkList[0][0];	//0位置所在chunk X
		//	chunkBegin[1] = chunkList[0][1];	//0位置所在chunk Y
		//	chunkEnd[0] = chunkList[1][0];		//1位置所在chunk X
		//	chunkEnd[1] = chunkList[2][1];		//2位置所在chunk Y

		//	ModifyModelRefInTile(tile, chunkBegin, chunkEnd, i);
		//}
	}
}

void CWorldWriteStream::GetTileChunkIdFromPos(  sInt32* chunk, flt32* pos ,CWorldTile* tile)
{
	for( sInt32 i=0;i<2;i++ ) {
		chunk[i]	= ChunkFromPos( pos[i] );
		if (chunk[i] < 0)
		{
			chunk[i] = 0;
		}
		if (chunk[i] >= tile->GetRowColumn()[i])
		{
			chunk[i] = tile->GetRowColumn()[i] - 1;
		}
	}
}

//bool CWorldWriteStream::GetPosInfoByModelWorldBound( NiBound WorldBound, CWorldTile* tile, sInt32 chunk[4][2] )
//{
//	Vector	center = WorldBound.GetCenter();
//	flt32		radius = WorldBound.GetRadius();
//	flt32		pos[2];
//	//
//	//0---------1
//	//|			|
//	//|			|
//	//|			|
//	//2---------3
//	//
//	// 计算Xmin,Ymin所在tile和chunk
//	pos[0] = center.x - radius;
//	pos[1] = center.y - radius;
//	GetTileChunkIdFromPos(  chunk[0], pos ,tile);
//
//	// 计算Xmax,Ymin所在tile和chunk
//	pos[0] = center.x + radius;
//	pos[1] = center.y - radius;
//	GetTileChunkIdFromPos(  chunk[1], pos ,tile);
//
//	// 计算Xmin,Ymax所在tile和chunk
//	pos[0] = center.x - radius;
//	pos[1] = center.y + radius;
//	GetTileChunkIdFromPos(  chunk[2], pos ,tile);
//
//	// 计算Xmax,Ymax所在tile和chunk
//	pos[0] = center.x + radius;
//	pos[1] = center.y + radius;
//	GetTileChunkIdFromPos(  chunk[3], pos ,tile);
//
//	return true;
//}

bool CWorldWriteStream::GetPosInfoByModelWorldBound( Vector2 vMin, Vector2 vMax, CWorldTile* tile, sInt32 chunk[4][2] )
{
	flt32		pos[2];
	//
	//0---------1
	//|			|
	//|			|
	//|			|
	//2---------3
	//
	// 计算Xmin,Ymin所在tile和chunk
	pos[0] = vMin.x;
	pos[1] = vMin.y;
	GetTileChunkIdFromPos(  chunk[0], pos ,tile);

	// 计算Xmax,Ymin所在tile和chunk
	pos[0] = vMax.x;
	pos[1] = vMin.y;
	GetTileChunkIdFromPos(  chunk[1], pos ,tile);

	// 计算Xmin,Ymax所在tile和chunk
	pos[0] = vMin.x;
	pos[1] = vMax.y;
	GetTileChunkIdFromPos(  chunk[2], pos ,tile);

	// 计算Xmax,Ymax所在tile和chunk
	pos[0] = vMax.x;
	pos[1] = vMax.y;
	GetTileChunkIdFromPos(  chunk[3], pos ,tile);

	return true;
}

void CWorldWriteStream::ModifyModelRefInTile( CWorldTile* tile, const sInt32* beginChunk, const sInt32* endChunk, sInt32 modelId)
{
	sInt32 curChunk[2];

	for( curChunk[1]=beginChunk[1]; curChunk[1]<=endChunk[1]; curChunk[1]++ )
	{
		for( curChunk[0]=beginChunk[0]; curChunk[0]<=endChunk[0]; curChunk[0]++ )
		{
			ModifyModelRefInOneChunk( tile, curChunk, modelId);
		}
	}
}

void CWorldWriteStream::ModifyModelRefInOneChunk( CWorldTile* tile, const sInt32* chunk, sInt32 modelId)
{
	//之前用CheckTileChunkValid检查过chunk是否有效，所以此处不再重复
	CWorldChunk* worldChunk = tile->GetChunk( chunk[0], chunk[1] );

	worldChunk->PushModel( modelId );
}


void CWorldWriteStream::CopyFolder( LPCTSTR psourceFolder,LPCTSTR pdestFolder )
{
	CFileFind ff;
	CString strPath( psourceFolder );
	strPath += _T("\\*.*");
	BOOL bFound = ff.FindFile(strPath);
	if (!bFound) 
		return ;

	while (bFound)
	{
		bFound = ff.FindNextFile();

		if (ff.IsDots())
			continue;

		strPath = ff.GetFilePath();
		CString dest(pdestFolder);
		dest += '\\';
		dest += ff.GetFileName();
		if (ff.IsDirectory()) {
			CreateDirectory(dest,NULL);
			CopyFolder(strPath,dest);
		}
		else 
		{
			CopyFile(strPath,dest,false);
		}
	}	

}

void CWorldWriteStream::CopyAllTilesToNewFolder( const char* worldPath )
{
	TCHAR oldFileName[MAX_PATH*2];
	memset(oldFileName,0,MAX_PATH*2*sizeof(TCHAR));
	_stprintf_s( oldFileName, _T("%hs"), m_world->GetWorldPath() );
	TCHAR newFileName[MAX_PATH*2];
	memset(newFileName,0,MAX_PATH*2*sizeof(TCHAR));
	_stprintf_s( newFileName, _T("%hs"), worldPath );
	if (0 != strcmp(oldFileName,newFileName))
	{
		CopyFolder(oldFileName,newFileName);
	}
}

bool CWorldWriteStream::WriteEnv( FILE* stream, CResEditMgr* resMgr )
{
	if (resMgr->GetEnvResList().size() == 0)
	{
		return true;
	}
	THead head;
	memset( &head, 0, sizeof(THead) );
	head.size	= resMgr->GetEnvResList().size();
	SetSame4Segment( head.segment, "WZON" );
	fwrite( &head, sizeof( THead ), 1, stream );

	TWTDEnv zone;
	for( uInt32 i=0; i< head.size; i++ ) {
		CNdlEnvRes* zoneRes = resMgr->GetEnvRes( i );
		strcpy_s( zone.zoneName, zoneRes->GetName() );
		zone.lightId		= zoneRes->GetLightId();
		zone.fogId			= zoneRes->GetFogId();
		fwrite( &zone, sizeof(TWTDEnv), 1, stream );
	}
	return true;
}

bool CWorldWriteStream::WriteLight( FILE* stream, CResEditMgr* resMgr )
{
	if (resMgr->GetLightList().size() == 0)
	{
		return true;
	}

	THead head;
	memset( &head, 0, sizeof(THead) );
	head.size	= resMgr->GetLightList().size();
	SetSame4Segment( head.segment, "WLIG" );
	fwrite( &head, sizeof( THead ), 1, stream );

	TWTDLight light;
	for( uInt32 i=0; i<head.size; i++ ) 
	{
		CNdlLightRes* lightRes	= resMgr->GetLightRes( i );
		strcpy_s( light.lightName, lightRes->GetName() );

		light.ambientLight		= lightRes->m_lightAmbient;		
		light.diffuseLight		= lightRes->m_lightDiffuse;		
		light.specularLight		= lightRes->m_lightSpecular;		
		light.colorSunless		= lightRes->m_colorSunless;		
		light.directionLight[0]	= lightRes->m_lightDir[0];		
		light.directionLight[1]	= lightRes->m_lightDir[1];		
		light.directionLight[2]	= lightRes->m_lightDir[2];		

		fwrite( &light, sizeof(TWTDLight), 1, stream );
	}
	return true;
}

bool CWorldWriteStream::WriteFog( FILE* stream, CResEditMgr* resMgr )
{
	if (resMgr->GetFogList().size() == 0)
	{
		return true;
	}

	THead head;
	memset( &head, 0, sizeof(THead) );
	head.size	= resMgr->GetFogList().size();
	SetSame4Segment( head.segment, "WFOG" );
	fwrite( &head, sizeof( THead ), 1, stream );

	TWTDFog fog;
	for ( uInt32 i=0; i<head.size; i++ ) {
		CNdlFogRes* fogRes	= resMgr->GetFogRes( i );
		strcpy_s( fog.fogName, fogRes->GetName() );

		fog.fogLight		= fogRes->m_lightColor;
		fog.fogNearLight	= fogRes->m_lightNear;
		fog.fogFarLight		= fogRes->m_lightFar;

		fwrite( &fog, sizeof(TWTDFog), 1, stream );
	}
	return true;
}

bool CWorldWriteStream::DirectAddNewModel( std::vector< TObjectInfo* >& destList,std::vector< TObjectInfo* >& sourceList,size_t refOldId,sInt32 refNewId)
{
	for(size_t i = 0; i < sourceList.size(); ++i)
	{
		TObjectInfo* pInfo = sourceList[i];
		if (pInfo->id == refOldId)
		{
			TObjectInfo* pNewInfo = MeNew TObjectEditInfo;
			pNewInfo->id				= refNewId;
			memcpy( pNewInfo->pos, pInfo->pos, sizeof(flt32)*3 );
			memcpy( pNewInfo->offset, pInfo->offset, sizeof(flt32)*3 );
			memcpy( pNewInfo->rotate, pInfo->rotate, sizeof(flt32)*3 );
			memcpy( pNewInfo->scale, pInfo->scale, sizeof(flt32)*3 );
			destList.push_back(pNewInfo);
		}
	}
	return true;
}

bool CWorldWriteStream::DirectAddNewRefModel( std::vector< CWorldRes* >& destList,CWorldRes* pRes )
{
	CWorldRes* pNew = MeNew CWorldRes;
	pNew->SetId(destList.size());
	pNew->SetName(pRes->GetName());
	destList.push_back(pNew);
	return true;
}

bool CWorldWriteStream::AddSubModel( std::vector< TObjectInfo* >& destList,std::vector< TObjectInfo* >& sourceList,size_t refOldId,sInt32 refNewId,sInt32 subIndex )
{
	for(size_t i = 0; i < sourceList.size(); ++i)
	{
		TObjectInfo* pInfo = sourceList[i];
		if (pInfo->id == refOldId)
		{
			TObjectInfo* pNewInfo = MeNew TObjectEditInfo;
			pNewInfo->id				= refNewId;
		}
	}
	return true;
}

bool CWorldWriteStream::AddSubRefModel( std::vector< CWorldRes* >& destList,CWorldRes* pRes,const char* subName )
{
	CWorldRes* pNew = MeNew CWorldRes;
	CStringA newName(pRes->GetName());
	newName += '|';
	newName += subName;
	pNew->SetId(destList.size());
	pNew->SetName(newName);
	destList.push_back(pNew);
	return true;
}

#include "MeTerrain/MonsterFile.h"

bool CWorldWriteStream::WriteMonsterData( CWorldTile* worldTile , const char* gameMapPath)
{
	if (worldTile->GetMonsterPath()[0] == '\0')
	{
		char cTemp[MAX_PATH];
		strcpy_s(cTemp,MAX_PATH,worldTile->GetPathName());
		char* pFind = strstr(cTemp,".mew");
		strcpy(&pFind[1],"monster");
		worldTile->SetMonsterPath(cTemp);
	}
	char fileName[MAX_PATH];
	sprintf_s( fileName, MAX_PATH*2, "%s\\%s", SwGlobal::GetWorld()->GetWorldPath(), worldTile->GetMonsterPath() );

	if (!RemoveReadOnly(fileName))
		return false;

	//<Stage>
	//	<Zone>
	//		<ZoneInfo Name = "0" Left = "40" Top = "64" Right = "44" Bottom = "74" AIStep = "0" CanPK = "false" CanPrivateShop = "false" EnterScript = "NULL" LeaveScript = "NULL">
	//		</ZoneInfo>
	//		...
	//	</Zone>
	//	<Monster>
	//		<MonsterGroup>
	//			<MonsterGroupInfo ZoneId = "0" X = "40.8809" Y = "72.8907" RandRange = "false" Dir = "2" TemplateName = "机关地刺#" 
	//							  Index = "17011" Number = "1" Relife = "36000000" County = "0" Enable = "true" Hide = "true" 
	//							  DeadScript = "Script\quest\GUAIWU\0000.s" LuaScript = "NULL" AIValue = "1000" MoveAIType = "1" 
	//							  AttackAIType = "1" IdleMoveAIType = "1" SpecialAIType = "1">
	//			</MonsterGroupInfo>
	//		</MonsterGroup>
	//		...
	//	</Monster>
	//</Stage>

	MeXmlDocument monsterDocument;
	monsterDocument.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));

	MeXmlElement *pRoot = monsterDocument.InsertEndChild(("Stage"))->ToElement();
	MeXmlElement *pZone = pRoot->InsertEndChild(("Zone"))->ToElement();
	CResEditMgr *resMgr =  (CResEditMgr*)worldTile->GetCResMgr();

	const int numOfMonsterQuad = resMgr->GetMonsterQuadCount();

	// Save ZoneInfo
	char floatTemp[100];
	std::wstring strValue;
	for (int i = 0 ; i < numOfMonsterQuad; ++i)
	{
		CMonsterQuadRes *pRes = resMgr->MonsterQuad(i);
		MeXmlElement *pZoneInfo = pZone->InsertEndChild(("ZoneInfo"))->ToElement();

		strValue = Common::_tstring::toWideString(pRes->GetZoneName());
		pZoneInfo->SetAttribute("Name", Common::_tstring::wcstoUTF8(strValue.c_str()).c_str());

		sprintf_s(floatTemp, "%f", (pRes->m_fLeft-MAP_GRID_SIZE/2.0f)/MAP_GRID_SIZE);
		pZoneInfo->SetAttribute("Left", floatTemp);
		//top 和 bottom相反设置，配合服务器 
		sprintf_s(floatTemp, "%f", (pRes->m_fTop-MAP_GRID_SIZE/2.0f)/MAP_GRID_SIZE + 2.0f);
		pZoneInfo->SetAttribute("Bottom", floatTemp);
		sprintf_s(floatTemp, "%f", (pRes->m_fRight-MAP_GRID_SIZE/2.0f)/MAP_GRID_SIZE+2.0f);
		pZoneInfo->SetAttribute("Right", floatTemp);
		sprintf_s(floatTemp, "%f", (pRes->m_fBottom-MAP_GRID_SIZE/2.0f)/MAP_GRID_SIZE);
		pZoneInfo->SetAttribute("Top", floatTemp);

		pZoneInfo->SetAttribute("AIStep", pRes->m_nAIStep);
		pZoneInfo->SetAttribute("CanPK", pRes->m_nPKMode);

		pZoneInfo->SetAttribute("CanDuel", pRes->m_bCanDuel ? 1 : 0);
		pZoneInfo->SetAttribute("CanPrivateShop", pRes->m_bCanStall ? "true" : "false");

		strValue = Common::_tstring::toWideString(pRes->GetEnterScript());
		pZoneInfo->SetAttribute("EnterScript", Common::_tstring::wcstoUTF8(strValue.c_str()).c_str());

		strValue = Common::_tstring::toWideString(pRes->GetLeaveScript());
		pZoneInfo->SetAttribute("LeaveScript", Common::_tstring::wcstoUTF8(strValue.c_str()).c_str());
	}

	// Save MonsterGroup
	MeXmlElement *pMonster = pRoot->InsertEndChild(("Monster"))->ToElement();
	for (int i = 0; i < numOfMonsterQuad; ++i)
	{
		CMonsterQuadRes *pRes = resMgr->MonsterQuad(i);

		MeXmlElement *pMonsterGroup = pMonster->InsertEndChild(("MonsterGroup"))->ToElement();
		{
			MeXmlElement *pMonsterGroupInfo = pMonsterGroup->InsertEndChild(("MonsterGroupInfo"))->ToElement();
			pMonsterGroupInfo->SetAttribute("TemplateName", "");

			pMonsterGroupInfo->SetAttribute("ZoneId", i);

			sprintf_s(floatTemp, "%f", pRes->GetPosX());
			pMonsterGroupInfo->SetAttribute("X", floatTemp);

			sprintf_s(floatTemp, "%f", pRes->GetPosY());
			pMonsterGroupInfo->SetAttribute("Y", floatTemp);

			pMonsterGroupInfo->SetAttribute("Enable", "true");
			pMonsterGroupInfo->SetAttribute("RandRange", "false");
			pMonsterGroupInfo->SetAttribute("Hide", "false");						
			pMonsterGroupInfo->SetAttribute("OnePoint", 1);

			pMonsterGroupInfo->SetAttribute("Index", pRes->m_nMonsterId);
			pMonsterGroupInfo->SetAttribute("County", pRes->m_nCountry);
			pMonsterGroupInfo->SetAttribute("Camp", pRes->m_nCamp);
			pMonsterGroupInfo->SetAttribute("Force", pRes->m_nForce);
			pMonsterGroupInfo->SetAttribute("Path", pRes->m_nPath);

			pMonsterGroupInfo->SetAttribute("Relife", pRes->m_nRelife);
			pMonsterGroupInfo->SetAttribute("Number", pRes->m_nNumber);
			pMonsterGroupInfo->SetAttribute("Dir", pRes->m_nDir);
			pMonsterGroupInfo->SetAttribute("AIValue", pRes->m_nAIValue);

			std::wstring str = Common::_tstring::toWideString(pRes->m_szDeadScript); //写入的地方
			pMonsterGroupInfo->SetAttribute("DeadScript", Common::_tstring::wcstoUTF8(str.c_str()).c_str());

			str = Common::_tstring::toWideString(pRes->m_szAIScript);
			pMonsterGroupInfo->SetAttribute("LuaScript", Common::_tstring::wcstoUTF8(str.c_str()).c_str());
		}
	}

	// 保存XML
	monsterDocument.SaveFile(fileName);

	/*
 	CResMgr* resMgr =  worldTile->GetCResMgr();
 	FILE* stream = NULL;
 	try	{
 		if( fopen_s( &stream, gameMapPath, "wb" ) != 0 ) 
 		{
 			throw( "error open file !" );
 		}
 		TMONHead header;
 		header.version = TMONHead::MAPVRSION;
 		SetSame4Segment(header.segment,"MOND");
 		header.nQuadCount = resMgr->GetMonsterQuadCount();
 
 		fwrite( &header, sizeof( TMONHead ), 1, stream );
 
 		for (int i = 0; i < header.nQuadCount; ++i)
 		{
 			CMonsterQuadRes* pRes = resMgr->MonsterQuad(i);
 			TMONQuadHead quadHead;
 			quadHead.m_fLeft = pRes->GetLeft();
 			quadHead.m_fRight = pRes->GetRight();
 			quadHead.m_fBottom = pRes->GetBottom();
 			quadHead.m_fTop = pRes->GetTop();
 			quadHead.m_monsterInterval = pRes->GetMonsterInterval();
 			quadHead.m_monsterNumber = pRes->GetMonsterNumber();
 			quadHead.m_monsterRadio = pRes->GetMonsterRadio();
 			quadHead.m_bpointInstanced = (pRes->GetMonsterList().size() != 0);
 			for (int t = 0; t < 3; ++t)
 			{
 				quadHead.m_monsterType[t] = pRes->GetMonsterType(t);
 			}
 			quadHead.m_bvisible = pRes->IsVisible();
 			fwrite( &quadHead, sizeof( TMONQuadHead ), 1, stream );
 			if (quadHead.m_bpointInstanced)
 			{
 				for (int j = 0; j < quadHead.m_monsterNumber;++j)
 				{
 					Vector2* pSrcPoint = pRes->GetMonsterList()[j];
 					TMONPoint	point;
 					point.x = pSrcPoint->x;
 					point.y = pSrcPoint->y;
 					fwrite( &point, sizeof( TMONPoint ), 1, stream );
 				}
 			}
 		}
 		fclose( stream );
 		stream = NULL;
 	}
 	catch( const char* s )
 	{
 		Trace( "failed write monster data:[ %s ] \n", worldTile->GetPathName() );
 		if( NULL != stream )
 		{
 			fclose( stream );
 			stream	= NULL;
 		}
 		return false;
 	}
	*/
	return true;
}

bool CWorldWriteStream::WriteRoadTable( FILE* stream, CResEditMgr* resMgr )
{
	TWTDShadowTable roadTable;
	SetSame4Segment( roadTable.head.segment, "WRMD" );
	roadTable.head.size = resMgr->GetRoadCount();
	fwrite( &roadTable, sizeof(TWTDShadowTable), 1, stream );

	for( sInt32 i=0; i<resMgr->GetRoadCount(); i++ ) 
	{
		TWTDAlphaMap roadMap;
		memset( &roadMap, 0, sizeof(TWTDAlphaMap) );	
		CNdlAlphaRes* res = resMgr->GetRoad( i );
		CalAlphaMap(res, roadMap);
		fwrite( &roadMap, sizeof(TWTDAlphaMap), 1, stream );
	}
	return true;

}

bool CWorldWriteStream::WriteRoadRes( const char* pName, CWorldTile* tile )
{

	FILE* stream = NULL;
	try	{
		if( NULL == tile )
			throw( "GetTile error!" );
		CResEditMgr* resMgr	= (CResEditMgr*)tile->GetCResMgr( );
		if( NULL == resMgr )
			throw( "GetResMgr error!" );

		WIN32_FIND_DATAA data;
		HANDLE hFind = FindFirstFileA(pName,&data);
		bool bFind = (hFind != INVALID_HANDLE_VALUE);
		if (bFind
			&&((data.nFileSizeHigh * (MAXDWORD+1)) + data.nFileSizeLow != 0))
		{
			CStringA bakPath(pName);
			bakPath += ".bak";
			if (!RemoveReadOnly(bakPath))
			{
				return false;
			}
			if(!CopyFileA(pName,bakPath,false))
			{
				::AfxMessageBox( _T("不能创建备份，保存失败!") );
				return false;
			}
		}


		if (!RemoveReadOnly(pName))
		{
			throw( "Can not write read-only file!" );
		}
		if( fopen_s( &stream, pName, "wb" ) != 0 ) {
			throw( "error open file!" );
		}


		TRoadResHead head;
		memset( &head, 0, sizeof(TRoadResHead) );
		SetSame4Segment( head.head.segment, "WRDH" );
		head.version = WORLD_FILE_LASTEST_VERSION;
		sInt32 offHead				= ftell( stream );
		fwrite( &head, sizeof( TRoadResHead ), 1, stream );

		for( sInt32 chunkId=0; chunkId<(tile->GetChunkTotal()); chunkId++ ) {
			TWTDRoadInfo chunkInfo;
			memset( &chunkInfo, 0, sizeof(TWTDRoadInfo) );
			CWorldChunk* worldChunk = tile->m_chunckTable[chunkId];
// 			chunkInfo.chunk	= worldChunk->m_chunk[0] + worldChunk->m_chunk[1] * tile->GetRowColumn()[0];
			chunkInfo.roadResId = worldChunk->m_road;
			fwrite( &chunkInfo, sizeof( TWTDRoadInfo ), 1, stream );
		}
		// texture name table
		if( !WriteRoadTable( stream, resMgr ) )
			throw ( "Error write road resource table!" );

		fclose( stream );
		stream = NULL;
	}
	catch( const char* s )
	{
		Trace( "failed write road resource:[ %s ] \n", s );
		if( NULL != stream )
		{
			fclose( stream );
			stream	= NULL;
		}
		return false;
	}


	return true;

}

bool CWorldWriteStream::RemoveReadOnly( const char* lpszPathName )
{
	WIN32_FIND_DATAA data;
	HANDLE hFind = FindFirstFileA(lpszPathName,&data);
	bool bFind = (hFind != INVALID_HANDLE_VALUE);
	if (bFind)
	{
		DWORD dwAttrs = GetFileAttributes( lpszPathName );
		if ( dwAttrs!=INVALID_FILE_ATTRIBUTES )
		{
			if ( dwAttrs & FILE_ATTRIBUTE_READONLY ) 
			{ 
				char prompt[2*MAX_PATH];
				sprintf_s(prompt,"文件%s只读，是否覆盖？",lpszPathName);
				int ret = ::AfxMessageBox(prompt,  MB_OKCANCEL );
				if (ret == IDOK)
				{
					dwAttrs &= ~FILE_ATTRIBUTE_READONLY;
					SetFileAttributes(lpszPathName, dwAttrs ); 
				}
				else
					return FALSE;
			} 
		} 
	}
	return true;
}
static sInt32	nZoneXmlVersion = 100;

bool CWorldWriteStream::WriteZoneRes( const char* pName )
{
	CWorldTile* worldTile = CURRENTTILE;
	if (!worldTile)
	{
		return false;
	}
	FILE* stream = NULL;
	try	{
		MeXmlDocument	doc;
		CResEditMgr* resMgr	= (CResEditMgr*)worldTile->GetCResMgr( );
		if( NULL == resMgr )
			throw( "GetResMgr error!" );

		WIN32_FIND_DATAA data;
		HANDLE hFind = FindFirstFileA(pName,&data);
		bool bFind = (hFind != INVALID_HANDLE_VALUE);
		if (bFind
			&&((data.nFileSizeHigh * (MAXDWORD+1)) + data.nFileSizeLow != 0))
		{
			CStringA bakPath(pName);
			bakPath += ".bak";
			if (!RemoveReadOnly(bakPath))
			{
				return false;
			}
			if(!CopyFileA(pName,bakPath,false))
			{
				::AfxMessageBox( _T("不能创建备份，保存失败!") );
				return false;
			}
		}


		if (!RemoveReadOnly(pName))
		{
			throw( "Can not write read-only file!" );
		}


		doc.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));
// 		doc.InsertEndChild(MeXmlComment("Notice: This xml is generated automatically. "));
// 		doc.InsertEndChild(MeXmlComment("It is recommend always to generate the file by world editor. However, you can modify some integer or float values for convenience."));
		MeXmlElement* pZoneRoot = doc.InsertEndChild(("ZoneList"))->ToElement();
		pZoneRoot->SetAttribute("ConfigVersion",nZoneXmlVersion);
		for (int i = 0;i < resMgr->GetZoneResList().size();++i)
		{
			CNdlZoneRes* zone = resMgr->GetZoneRes(i);
			MeXmlElement* pMapNode = pZoneRoot->InsertEndChild(("Zone"))->ToElement();
			pMapNode->SetAttribute("id",i);
			std::wstring str = Common::_tstring::toWideString(zone->GetName());
			pMapNode->SetAttribute("Name",Common::_tstring::wcstoUTF8(str.c_str()).c_str());
			pMapNode->SetAttribute("Music",zone->GetMuiscPath());
			if (zone->GetFontRect())
			{
				char szRect[128] = {0};
				sprintf_s(szRect, "%d, %d, %d, %d", zone->GetFontRect()->left, zone->GetFontRect()->top, zone->GetFontRect()->right, zone->GetFontRect()->bottom);
				pMapNode->SetAttribute("Rect", szRect);
			}
		}

		MeXmlElement* pChunkZoneRoot = doc.InsertEndChild(("ChunkZone"))->ToElement();
		for (int i = 0; i < worldTile->GetRowColumn()[1];++i)
		{
			CStringA strZone;
			for(int j = 0; j < worldTile->GetRowColumn()[0]; ++j)
			{
				CWorldChunk* chunk = worldTile->GetChunk(j,i);
				CStringA strTmp;
				strTmp.Format("%4d",chunk->GetZoneId());
// 				char pTmp[5];
// 				pTmp[4] = '\0';
// 				memcpy(pTmp,strTmp.GetString(),strTmp.GetLength());
// 				for (int x = strTmp.GetLength(); x < 4; ++x)
// 				{
// 					pTmp[x] = ' ';
// 				}
				strZone += strTmp;
			}
			CStringA strKey;
			strKey.Format("ChunkRow%3d",i);
			strKey.Replace(' ','0');
			MeXmlElement* pMapNode = pChunkZoneRoot->InsertEndChild((strKey.GetString()))->ToElement();
			pMapNode->SetAttribute("Value",strZone);
		}
		doc.SaveFile(pName);
	}
	catch( const char* s )
	{
		Trace( "failed write zone resource:[ %s ] \n", s );
		if( NULL != stream )
		{
			fclose( stream );
			stream	= NULL;
		}
		return false;
	}


	return true;

}

bool CWorldWriteStream::WriteDoodadRes( const char* pName, CWorldTile* tile )
{
	FILE* stream = NULL;
	try	{
		if( NULL == tile )
			throw( "GetTile error!" );
		CResEditMgr* resMgr	= (CResEditMgr*)tile->GetCResMgr( );
		if( NULL == resMgr )
			throw( "GetResMgr error!" );

		WIN32_FIND_DATAA data;
		HANDLE hFind = FindFirstFileA(pName,&data);
		bool bFind = (hFind != INVALID_HANDLE_VALUE);
		if (bFind
			&&((data.nFileSizeHigh * (MAXDWORD+1)) + data.nFileSizeLow != 0))
		{
			CStringA bakPath(pName);
			bakPath += ".bak";
			if (!RemoveReadOnly(bakPath))
			{
				return false;
			}
			if(!CopyFileA(pName,bakPath,false))
			{
				::AfxMessageBox( _T("不能创建备份，保存失败!") );
				return false;
			}
		}


		if (!RemoveReadOnly(pName))
		{
			throw( "Can not write read-only file!" );
		}
		if( fopen_s( &stream, pName, "wb" ) != 0 ) {
			throw( "error open file!" );
		}


		TRoadResHead head;
		memset( &head, 0, sizeof(TRoadResHead) );
		SetSame4Segment( head.head.segment, "WCAO" );
		head.version = WORLD_FILE_LASTEST_VERSION;
		sInt32 offHead				= ftell( stream );
		fwrite( &head, sizeof( TRoadResHead ), 1, stream );

		for( sInt32 chunkId=0; chunkId<(tile->GetChunkTotal()); chunkId++ ) {
			TWTDDoodadInfo chunkInfo;
			memset( &chunkInfo, 0, sizeof(TWTDDoodadInfo) );
			CWorldChunk* worldChunk = tile->m_chunckTable[chunkId];
			// 			chunkInfo.chunk	= worldChunk->m_chunk[0] + worldChunk->m_chunk[1] * tile->GetRowColumn()[0];
			chunkInfo.sizeDoodad = worldChunk->m_doodadList.size();
			fwrite( &chunkInfo, sizeof( TWTDDoodadInfo ), 1, stream );
			for (size_t doodadID = 0; doodadID < chunkInfo.sizeDoodad; ++doodadID)
			{
				TWTDDoodesRef doodes;
				doodes.doodesId = worldChunk->m_doodadList[doodadID]->mdoodadId;
				doodes.mulevelUnit = worldChunk->m_doodadList[doodadID]->mulevelUnit;
				fwrite( &doodes, sizeof(TWTDDoodesRef), 1, stream );
				fwrite(worldChunk->m_doodadList[doodadID]->GetDoodadMap(),sizeof(TDoodadInfoForEdit)*doodes.mulevelUnit*doodes.mulevelUnit,1,stream);
			}
		}

		fclose( stream );
		stream = NULL;
	}
	catch( const char* s )
	{
		Trace( "failed write doodad resource:[ %s ] \n", s );
		if( NULL != stream )
		{
			fclose( stream );
			stream	= NULL;
		}
		return false;
	}


	return true;

}

bool CWorldWriteStream::WriteAlphaRes( const char* pName, CWorldTile* tile )
{
	FILE* stream = NULL;
	try	{
		if( NULL == tile )
			throw( "GetTile error!" );
		CResEditMgr* resMgr	= (CResEditMgr*)tile->GetCResMgr( );
		if( NULL == resMgr )
			throw( "GetResMgr error!" );

		WIN32_FIND_DATAA data;
		HANDLE hFind = FindFirstFileA(pName,&data);
		bool bFind = (hFind != INVALID_HANDLE_VALUE);
		if (bFind
			&&((data.nFileSizeHigh * (MAXDWORD+1)) + data.nFileSizeLow != 0))
		{
			CStringA bakPath(pName);
			bakPath += ".bak";
			if (!RemoveReadOnly(bakPath))
			{
				return false;
			}
			if(!CopyFileA(pName,bakPath,false))
			{
				::AfxMessageBox( _T("不能创建备份，保存失败!") );
				return false;
			}
		}


		if (!RemoveReadOnly(pName))
		{
			throw( "Can not write read-only file!" );
		}
		if( fopen_s( &stream, pName, "wb" ) != 0 ) {
			throw( "error open file!" );
		}


		TRoadResHead head;
		memset( &head, 0, sizeof(TRoadResHead) );
		SetSame4Segment( head.head.segment, "WALP" );
		head.version = WORLD_FILE_LASTEST_VERSION;
		sInt32 offHead				= ftell( stream );
		fwrite( &head, sizeof( TRoadResHead ), 1, stream );

		// texture name table
		if( !WriteAlphaTable( stream, resMgr ) )
			throw ( "Error write alpha resource table!" );

		fclose( stream );
		stream = NULL;
	}
	catch( const char* s )
	{
		Trace( "failed write alpha resource:[ %s ] \n", s );
		if( NULL != stream )
		{
			fclose( stream );
			stream	= NULL;
		}
		return false;
	}


	return true;

}

bool CWorldWriteStream::WriteLightMapTable( FILE* stream, CWorldTile* tile )
{
	if( !stream || !tile )
		return false;

	TWTDLightMap lmTable;
	memset( &lmTable, 0, sizeof(TWTDLightMap) );
	SetSame4Segment( lmTable.head.segment, "WLMP" ); 
	lmTable.head.size = tile->GetLightMapNum();
	fwrite( &lmTable, sizeof(TWTDLightMap), 1, stream );

	return true;
}

bool CWorldWriteStream::WriteLightmapColorData( const char* pName )
{
	FILE* stream = NULL;
	try	{
		WIN32_FIND_DATAA data;
		HANDLE hFind = FindFirstFileA(pName,&data);
		bool bFind = (hFind != INVALID_HANDLE_VALUE);
		if (bFind
			&&((data.nFileSizeHigh * (MAXDWORD+1)) + data.nFileSizeLow != 0))
		{
			CStringA bakPath(pName);
			bakPath += ".bak";
			if (!RemoveReadOnly(bakPath))
			{
				return false;
			}
			if(!CopyFileA(pName,bakPath,false))
			{
				::AfxMessageBox( _T("不能创建光照数据备份，保存失败!") );
				return false;
			}
		}


		if (!RemoveReadOnly(pName))
		{
			throw( "Can not write read-only file!" );
		}
		if( fopen_s( &stream, pName, "wb" ) != 0 ) {
			throw( "error open file!" );
		}

		TMeshLightMapHead head;
		memset( &head, 0, sizeof(TMeshLightMapHead) );
		SetSame4Segment( head.head.segment, "WMLM" );
		head.version = WORLD_FILE_LASTEST_VERSION;
		sInt32 offHead = ftell( stream );
		fwrite( &head, sizeof( TMeshLightMapHead ), 1, stream );

		const std::map<sInt32, MeshLightmapColorData::LMColorData*>& ColorData = MeshLightmapColorData::GetInstance()->GetColorDataMap();
		sInt32 count = ColorData.size();
		fwrite( &count, sizeof(sInt32), 1, stream );

		if( ColorData.size() )
		{
			std::map<sInt32, MeshLightmapColorData::LMColorData*>::const_iterator iter = ColorData.begin();
			for( ; iter != ColorData.end(); ++iter )
			{
				if( NULL == iter->second )
				{
					sInt32 key = INVALID_LIGHTMAP_DATA;
					fwrite( &key, sizeof(sInt32), 1, stream );
					continue;
				}

				sInt32 key = iter->first;
				MeshLightmapColorData::LMColorData* pCD = iter->second;
				sInt32 resolution = pCD->m_nColorDataResolution;
				if( NULL == pCD->m_pColorData )
				{
					key = INVALID_LIGHTMAP_DATA;
					fwrite( &key, sizeof(sInt32), 1, stream );
					continue;
				}
				fwrite( &key, sizeof(sInt32), 1, stream );
				fwrite( &resolution, sizeof(sInt32), 1, stream );
				fwrite( pCD->m_pColorData, sizeof(NiColorB), resolution*resolution, stream );
			}
		}

		fclose( stream );
		stream = NULL;
	}
	catch( const char* s )
	{
		Trace( "failed write road resource:[ %s ] \n", s );
		if( NULL != stream )
		{
			fclose( stream );
			stream	= NULL;
		}
		return false;
	}

	return true;
}

bool CWorldWriteStream::WriteStaticLightsRes( const char* pName )
{
	FILE* stream = NULL;
	try	{
		WIN32_FIND_DATAA data;
		HANDLE hFind = FindFirstFileA(pName,&data);
		bool bFind = (hFind != INVALID_HANDLE_VALUE);
		if (bFind
			&&((data.nFileSizeHigh * (MAXDWORD+1)) + data.nFileSizeLow != 0))
		{
			CStringA bakPath(pName);
			bakPath += ".bak";
			if (!RemoveReadOnly(bakPath))
			{
				return false;
			}
			if(!CopyFileA(pName,bakPath,false))
			{
				::AfxMessageBox( _T("不能创建静态光源文件备份，保存失败!") );
				return false;
			}
		}


		if (!RemoveReadOnly(pName))
		{
			throw( "Can not write read-only file!" );
		}
		if( fopen_s( &stream, pName, "wb" ) != 0 ) {
			throw( "error open file!" );
		}

		TStaticLightHead head;
		memset( &head, 0, sizeof(TStaticLightHead) );
		SetSame4Segment( head.head.segment, "WSLR" );
		head.version = WORLD_FILE_LASTEST_VERSION;
		sInt32 offHead = ftell( stream );
		fwrite( &head, sizeof( TStaticLightHead ), 1, stream );

		const std::map<unsigned short, LightRes*>& StaticLights = StaticLightsContainer::GetInstance()->GetStaticLights();
		sInt32 count = StaticLights.size();
		fwrite( &count, sizeof(sInt32), 1, stream );

		if( StaticLights.size() )
		{
			std::map<unsigned short, LightRes*>::const_iterator iter = StaticLights.begin();
			for( ; iter != StaticLights.end(); ++iter )
			{
				if( NULL == iter->second )
				{
					sInt32 id = INVALID_STATIC_LIGHT_DATA;
					fwrite( &id, sizeof(sInt32), 1, stream );
					continue;
				}

				LightRes* pLight = iter->second;

				// 检查光源类型
				switch(pLight->GetType())
				{
					case LightRes::LT_POINTLIGHT:
						break;
					default:
						assert(0&&"光源类型不支持");
						break;
				}

				unsigned char type = LightRes::LT_POINTLIGHT;
				fwrite(&type, sizeof(unsigned char), 1, stream);

				sInt32 id = iter->first;
				fwrite( &id, sizeof(sInt32), 1, stream );
				pLight->SaveToFile(stream);
			}
		}

		fclose( stream );
		stream = NULL;
	}
	catch( const char* s )
	{
		Trace( "failed write road resource:[ %s ] \n", s );
		if( NULL != stream )
		{
			fclose( stream );
			stream	= NULL;
		}
		return false;
	}

	return true;
}