/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WorldReadStream.cpp
* Create: 	10/06/2006
* Desc:		地图读取类
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "MeTerrain/WorldPrecompiled.hpp"
// #include "atlpath.h"

#include "MeTerrain/MapConfigXml.h"
// #include "FlyRouteXml.h"
// #include "NPCRouteXml.h"
#include "MeTerrain/SoundPointXml.h"
#include "tstring.h"
#include "../filepacket/packet_interface.h"
//#include "Launcher/DataLauncher.h"
#include "logmgr.h"
#define INFO_LOG		"Info.log"

////////////////////////////////////////////////////////////////////////////////
namespace
{
	bool IsSame4Segment( const sInt8* a, const char* b )	
	{
		return ( (a[0]==b[0]) && (a[1]==b[1]) && (a[2]==b[2]) && (a[3]==b[3]) );
	}
};

#define CheckThrow( x )		if( !(x) ){ throw #x; }
////////////////////////////////////////////////////////////////////////////////
CWorldReadStream::CWorldReadStream( CWorldBuffer* worldBuffer )
{
	m_worldBuffer	= worldBuffer;
	m_ColorChange = NULL;
}

CWorldReadStream::~CWorldReadStream()
{
	m_worldBuffer	= NULL;
}

bool CWorldReadStream::LoadWorld( const char* worldPath)
{
	char fileName[_MAX_PATH];
	memset( fileName, 0, sizeof(char) * _MAX_PATH );



	CMapConfigXml::Instance()->LoadMapConfig();
	CSoundPointXml::Instance()->LoadSoundPoint();
	return true;
}

bool CWorldReadStream::LoadTile( CWorldTile* tile )
{
	Assert( !tile->m_isLoad );

	char fileName[MAX_PATH*2];


#if _MSC_VER >= 1400
	sprintf_s( fileName, MAX_PATH*2, "%s\\%s", m_worldBuffer->m_world->GetWorldPath(), tile->GetPathName() );
#else
	sprintf( fileName, "%s\\%s",m_worldBuffer->m_world->GetWorldPath(), tile->GetPathName() );
#endif
	if( !LoadWtd( tile, fileName ) )
	{
		return false;
	}
	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      LoadReachableMap加载", GetCurrentThreadId() );
	tile->LoadReachableMap();
	_strlwr(fileName);
	char* pFind = strstr(fileName,".mew");
	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      LoadMinimap加载", GetCurrentThreadId() );
	tile->LoadMinimap();
	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      LoadDoodadRes加载", GetCurrentThreadId() );
	strcpy(&pFind[1],"grass");
	if (!LoadDoodadRes(tile,fileName))
	{
		strcpy(&pFind[1],"cao");
		LoadDoodadRes(tile,fileName);
	}
	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      LoadZoneRes加载", GetCurrentThreadId() );
	strcpy(&pFind[1],"Zone");
	if (!LoadZoneRes(tile,fileName))
	{
		strcpy(&pFind[1],"Zone.xml");
		LoadZoneRes(tile,fileName);
	}
	for( sInt32 i = 0; i < ( tile->GetChunkTotal() ); ++i ) 
	{
		CWorldChunk* worldChunk = tile->GetChunk(i);
		InitializeLoadLevel(worldChunk);
	}
	return true;
}



static LONG AllObjectCount = 0;
static LONG CurrentLoadCount = 0;

bool CWorldReadStream::LoadWtd( CWorldTile* tile, const char* pathName )
{
	Assert( NULL != tile );
	Assert( NULL != pathName );

	char alphafileName[MAX_PATH*2];
	strcpy(alphafileName,pathName);
	char* pFind = strstr(alphafileName,".mew");

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      LoadAlpha加载", GetCurrentThreadId() );
	strcpy(&pFind[1],"alpha");
	if(!LoadAlphaRes(tile,alphafileName))
	{
		strcpy(&pFind[1],"alp");
		LoadAlphaRes(tile,alphafileName);
	}

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      LoadWtd加载", GetCurrentThreadId() );
	size_t uiReadSize = 0;
	f_Handle* stream = NULL;
	try
	{
		sInt32 offset = 0;
#if _MSC_VER >= 1400
		CheckThrow( packet_namespace::w_fopen_s( &stream, pathName, "rb" ) == 0 );
#else
		stream = fopen( pathName, "rb" );
		CheckThrow( stream != NULL );
#endif
		

		uiReadSize = packet_namespace::w_fread( &m_wifhead, sizeof( TWTDHead ), 1, stream );
		if (m_wifhead.version != WORLD_FILE_LASTEST_VERSION)
		{
			if (m_wifhead.version >= WORLD_FILE_OLD_VERSION)
			{
				Trace( "Old world file (%s)version [%d]!\n",pathName, m_wifhead.version);		
			}
			else
			{
				throw( "unsupported world file version \n" );
			}
		}

//		CheckThrow( uiReadSize != sizeof(TWTDHead) );
		CheckThrow( IsSame4Segment( m_wifhead.segment, "WTDH" )  );	
		if (m_wifhead.row == 0 || m_wifhead.column == 0)//old version
		{
			tile->SetRowColumn(16,16);
		}
		else
		{
			tile->SetRowColumn(m_wifhead.row,m_wifhead.column);
		}

		if (abs(m_wifhead.reachableAngle ) > 0.001f)
		{
			if (m_wifhead.reachableAngle > 360)
			{
				tile->m_reachableAngle = 40.f;
			}
			else
			{
				tile->m_reachableAngle = (m_wifhead.reachableAngle);
			}
		}

		flt32 origin[2];
		origin[0]	= TILEORIGIN(tile, 0 );
		origin[1]	= TILEORIGIN(tile, 1 );

		AllObjectCount = tile->GetChunkTotal() + 10; // +10（包括ReadTextureTable，ReadAlphaTable等等）
		CurrentLoadCount = 12;
		
		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      ReadTextureTable加载", GetCurrentThreadId() );
		offset = m_wifhead.offsAlphaTable - m_wifhead.offsTexNameTable;
		if( offset > 0 ) 
		{
			CheckThrow( 0 == packet_namespace::w_fseek( stream, m_wifhead.offsTexNameTable, SEEK_SET ) );
			if( !ReadTextureTable( stream, tile->m_ndlResMgr ) )
			{
				Trace( "Error read texture table! \n" );
			}
		}
		SwGlobal::SetLoadProgress((float)(++CurrentLoadCount) / AllObjectCount * 100.0f);
		Trace( "Load mew alphaTable! \n" );

		offset = m_wifhead.offsShadowTable-m_wifhead.offsAlphaTable;
		if( offset > 0 ) 
		{
			CheckThrow( 0 == packet_namespace::w_fseek( stream, m_wifhead.offsAlphaTable, SEEK_SET ) );
			if( !ReadAlphaTable( stream, tile->m_ndlResMgr ) )
			{
				Trace( "Error read texture table! \n" );
			}
		}	
		SwGlobal::SetLoadProgress((float)(++CurrentLoadCount) / AllObjectCount * 100.0f);
		
		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      ReadShadowTable加载", GetCurrentThreadId() );
		Trace( "Load mew offsShadowTable! \n" );
		offset = m_wifhead.offsLiquidTable - m_wifhead.offsShadowTable;
		if( offset > 0 ) 
		{
			if( 0 == packet_namespace::w_fseek( stream, m_wifhead.offsShadowTable, SEEK_SET ) ) 
			{
				if( !ReadShadowTable( stream, tile->m_ndlResMgr ) )
				{
					Trace( "Error read shadow table! \n" );
				}
			}
		}
		SwGlobal::SetLoadProgress((float)(++CurrentLoadCount) / AllObjectCount * 100.0f);

		// 水
		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      ReadLiquidTable加载", GetCurrentThreadId() );
		Trace( "Load mew offsLiquidTable! \n" );
		offset = m_wifhead.offsModelNameTable-m_wifhead.offsLiquidTable;
		if( offset >0 ) 
		{
			if( 0 == packet_namespace::w_fseek( stream, m_wifhead.offsLiquidTable, SEEK_SET ) ) 
			{
				if( !ReadLiquidTable( stream, tile->m_ndlResMgr ) ) 
				{
					Trace( "Error read liquid Table" );
				}
			}		
		}
		SwGlobal::SetLoadProgress((float)(++CurrentLoadCount) / AllObjectCount * 100.0f);
	
		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      ReadModelTable加载", GetCurrentThreadId() );
		Trace( "Load mew offsModelNameTable! \n" );
		offset = m_wifhead.offsMapObjNameTable-m_wifhead.offsModelNameTable;
		if( offset > 0 ) 
		{
			if( 0 == packet_namespace::w_fseek( stream, m_wifhead.offsModelNameTable, SEEK_SET ) ) 
			{
				if( !ReadModelTable( stream, tile->m_ndlResMgr ) ) 
				{
					Trace( "Error read model name Table \n" );
				}
			}		
		}
		SwGlobal::SetLoadProgress((float)(++CurrentLoadCount) / AllObjectCount * 100.0f);
		Trace( "Load mew offsMapObjNameTable! \n" );

		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      ReadMapObjTable加载", GetCurrentThreadId() );
		offset = m_wifhead.offsDoodNameTable - m_wifhead.offsMapObjNameTable;
		if( offset > 0 ) 
		{
			if( 0 == packet_namespace::w_fseek( stream, m_wifhead.offsMapObjNameTable, SEEK_SET ) )
			{
				if( !ReadMapObjTable( stream, tile->m_ndlResMgr, origin ) ) 
				{
					Trace( "Error read map obj Table \n" );
				}
			}		
		}

		Trace( "Load mew offsDoodNameTable! \n" );
		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      ReadDoodadTable加载", GetCurrentThreadId() );
		// 装饰物
		if (m_wifhead.offsZoneTable == 0)//old version
		{
			offset = m_wifhead.offsChunkTable-m_wifhead.offsDoodNameTable;
		}
		else
		{
			offset = m_wifhead.offsZoneTable-m_wifhead.offsDoodNameTable;
		}
		if( offset >0 ) 
		{
			if( 0 == packet_namespace::w_fseek( stream, m_wifhead.offsDoodNameTable, SEEK_SET ) )
			{
				if( !ReadDoodadTable( stream, tile->m_ndlResMgr ) ) 
				{
					Trace( "Error read doodads name Table \n" );
				}
			}
		}
		SwGlobal::SetLoadProgress((float)(++CurrentLoadCount) / AllObjectCount * 100.0f);


		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      ReadZoneTable加载", GetCurrentThreadId() );
		Trace( "Load mew offsZoneTable! \n" );
		offset = m_wifhead.offsFogTable-m_wifhead.offsZoneTable;
		if( offset >0 ) 
		{
			if( 0 == packet_namespace::w_fseek( stream, m_wifhead.offsZoneTable, SEEK_SET ) )
			{
				if( !ReadZoneTable( stream, tile->m_ndlResMgr ) ) 
				{
					Trace( "Error read doodads name Table \n" );
				}
			}
		}
		SwGlobal::SetLoadProgress((float)(++CurrentLoadCount) / AllObjectCount * 100.0f);

		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      ReadFogTable加载", GetCurrentThreadId() );
		Trace( "Load mew offsFogTable! \n" );
		offset = m_wifhead.offsLightTable-m_wifhead.offsFogTable;
		if( offset >0 ) 
		{
			if( 0 == packet_namespace::w_fseek( stream, m_wifhead.offsFogTable, SEEK_SET ) )
			{
				if( !ReadFogTable( stream, tile->m_ndlResMgr ) ) 
				{
					Trace( "Error read doodads name Table \n" );
				}
			}
		}
		SwGlobal::SetLoadProgress((float)(++CurrentLoadCount) / AllObjectCount * 100.0f);

		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      ReadLightTable加载", GetCurrentThreadId() );
		Trace( "Load mew offsLightTable! \n" );
		if (m_wifhead.offsLightTable > 0)
		{
			offset = m_wifhead.offsChunkTable-m_wifhead.offsLightTable;
			if( offset >0 ) 
			{
				if( 0 == packet_namespace::w_fseek( stream, m_wifhead.offsLightTable, SEEK_SET ) )
				{
					if( !ReadLightTable( stream, tile->m_ndlResMgr ) ) 
					{
						Trace( "Error read doodads name Table \n" );
					}
				}
			}
		}
		SwGlobal::SetLoadProgress((float)(++CurrentLoadCount) / AllObjectCount * 100.0f);

		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      ReadChunkTable加载", GetCurrentThreadId() );
		Trace( "Load mew offsChunkTable! \n" );
		// chunk table
		CheckThrow( 0 == packet_namespace::w_fseek( stream, m_wifhead.offsChunkTable, SEEK_SET ) );
		if( !ReadChunkTable( stream, tile ) )
		{
			throw "Error read chunk table!";
		}

		// 读模型灯光图
		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      ReadLightMapTable加载", GetCurrentThreadId() );
		Trace( "Load mew offsLightMapTable! \n" );
		if( m_wifhead.version >= WORLD_FILE_LASTEST_107 && m_wifhead.offsLightMapTable > 0 )
		{
			CheckThrow( 0 == packet_namespace::w_fseek( stream, m_wifhead.offsLightMapTable, SEEK_SET ) );
			if( !ReadLightMapTable( stream, tile ) )
			{
				throw "Error read lightmap table!";
			}
		}

		packet_namespace::w_fclose( stream );
		stream = NULL;

		// 创建tile四叉树
		tile->m_tileQuadTree.Create(tile);
		// 创建地面模型和碰撞模型
//  		tile->CreateFloorAndCollision();
		Trace( "Load tile OK \n" );
	}
	catch( const char* s )
	{
		Trace( "failed load mew:[ %s ] \n", s );
		if( NULL != stream )
		{
			packet_namespace::w_fclose( stream );
			stream	= NULL;
		}
		return false;
	}
	catch(...)
	{
		Trace( "failed load mew:\n");
		if( NULL != stream )
		{
			packet_namespace::w_fclose( stream );
			stream	= NULL;
		}
		return false;
	}
	
	return true;
}


bool CWorldReadStream::ReadTextureTable( f_Handle* stream, CResMgr* resMgr )
{
	// texture name table
	TWTDNameTable nameTable;
	sInt32 numRead = packet_namespace::w_fread( &nameTable, 1, sizeof(TWTDNameTable), stream );
	CheckThrow( numRead == sizeof(TWTDNameTable) );
	CheckThrow( IsSame4Segment(nameTable.head.segment,"WNTT") );
	for( uInt32 i = 0; i < nameTable.head.size; ++i ) 
	{
		char name[RES_NAME_LEN];
		packet_namespace::w_fread( name, 1, sizeof(name), stream );
		resMgr->PushTexture( name );
	}
	return true;
}


bool CWorldReadStream::ReadAlphaTable( f_Handle* stream, CResMgr* resMgr )
{
	TWTDAlphaTable alphaTable;
	sInt32 numRead = packet_namespace::w_fread( &alphaTable, 1, sizeof(TWTDAlphaTable), stream );
	CheckThrow( IsSame4Segment(alphaTable.head.segment,"WAMD") );

	for( uInt32 i = 0; i < alphaTable.head.size; ++i ) 
	{
		TWTDAlphaMap kAlphaMap;
		sInt32 numRead = packet_namespace::w_fread( &kAlphaMap, 1, sizeof(TWTDAlphaMap), stream );
// 		uInt8 alphaData[WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM];
// 		GetAlphaData(alphaData, kAlphaMap.alpha);
		resMgr->PushAlpha( kAlphaMap.alpha );
	}
	return true;
}

bool CWorldReadStream::ReadShadowTable( f_Handle* stream, CResMgr* resMgr )
{
	TWTDShadowTable kShadowTable;
	sInt32 numRead = packet_namespace::w_fread( &kShadowTable, 1, sizeof(TWTDShadowTable), stream );
	CheckThrow( IsSame4Segment(kShadowTable.head.segment,"WSMD") );

	for( uInt32 i = 0; i < kShadowTable.head.size; ++i )
	{
// 		uInt8 ucShadowData[64*64];
// 		if (m_wifhead.version < WORLD_FILE_VERSION_104)
// 		{
// 			TWTDShadowMap shadowMap;
// 			numRead = fread( &shadowMap, 1, sizeof(TWTDShadowMap), stream );
// 			CheckThrow( numRead == sizeof(TWTDShadowMap) );
// 			uInt8* pcShadow	= ucShadowData;
// 			for( sInt32 y = 0; y < MASK_SIZE; ++y)
// 			{
// 				for ( sInt32 x = 0; x < 8; ++x)
// 				{
// 					uInt8 a	= shadowMap.shadow[ y * 8 + x];
// 					sInt32 test = 0x100;
// 					for( sInt32  k = 0x01; k != 0x100; k = (k << 1) )
// 					{
// 						*pcShadow = ( ((a & k)==0) ? 0xFF:0xAA );
// 						//Trace( "shadowPtr[%d][%d][%d] (%d) \n", x, y, k, *shadowPtr );
// 						pcShadow++;
// 					}
// 				}
// 			}
// 			resMgr->PushShadow( shadowMap.shadow );
// 		}
// 		else
		{
			TWTDAlphaMap shadowMap;
			numRead = packet_namespace::w_fread( &shadowMap, 1, sizeof(TWTDAlphaMap), stream );
			CheckThrow( numRead == sizeof(TWTDAlphaMap) );
// 			GetAlphaData(ucShadowData, shadowMap.alpha);
			resMgr->PushShadow( shadowMap.alpha );
		}
	}
	return true;
}

bool CWorldReadStream::ReadLiquidTable( f_Handle* stream, CResMgr* resMgr )
{
	return true;
}

bool CWorldReadStream::ReadDoodadTable( f_Handle* stream, CResMgr* resMgr )
{
	TWTDNameTable nameTable;
	packet_namespace::w_fread( &nameTable, sizeof(TWTDNameTable), 1, stream );
	if( !IsSame4Segment(nameTable.head.segment,"WNDT") )
	{
		return false;
	}
	if( nameTable.head.size <= 0 )
	{
		return true;
	}
	for( uInt32 i = 0; i < nameTable.head.size; i++ ) 
	{
		char name[RES_NAME_LEN];
		packet_namespace::w_fread( name, 1, sizeof(name), stream );

		resMgr->PushRefDoodad( name );
	}
	return true;
}

bool CWorldReadStream::ReadModelTable( f_Handle* stream, CResMgr* resMgr )
{
	TWTDNameTable nameTable;
	packet_namespace::w_fread( &nameTable, sizeof(TWTDNameTable), 1, stream );
	if( !IsSame4Segment(nameTable.head.segment,"WNMT") )
	{
		return false;
	}
	if( nameTable.head.size <= 0 )
	{
		return true;
	}
	for( uInt32 i = 0; i < nameTable.head.size; i++ ) 
	{
		char name[RES_NAME_LEN];
		packet_namespace::w_fread( name, 1, sizeof(name), stream );
		
		resMgr->PushRefStaticModel( name );
	}
	return true;
}

bool CWorldReadStream::ReadMapObjTable( f_Handle* stream, CResMgr* resMgr, flt32* origin )
{
	TWTNMapObjTable nameTable;
	packet_namespace::w_fread( &nameTable, sizeof(TWTNMapObjTable), 1, stream );
	if( !IsSame4Segment(nameTable.head.segment,"WMOT") )
	{
		return false;
	}
	if( nameTable.head.size <=0 )
	{
		return true;
	}

	AllObjectCount += nameTable.head.size;

	for( uInt32 i = 0; i < nameTable.head.size; ++i ) 
	{
		TWTDMapObjInfo objInfo;
		packet_namespace::w_fread( &objInfo, sizeof(TWTDMapObjInfo), 1, stream );
		// TBD: 需要改为相对于Tile的坐标.
		objInfo.pos[0]	= objInfo.pos[0]/**16/16.666666 */+ origin[0];
		objInfo.pos[1]	= objInfo.pos[1]/**16/16.666666*/ + origin[1];
		
		if( objInfo.id < 0 || objInfo.id >= resMgr->m_staticModelRefList.size() ) 
		{
			Trace( "<<<ERROR>>> read: Invalid model id! \n" );	
			//continue;
		}

		TWTDObjLightmapInfo lmInfo;
		TWTDObjLightmapInfo* plmInfo = NULL;
		TWTDObjInstance* pIns = NULL;
		TWTDObjLightmapColorData lmColorData;
		if( m_wifhead.version >= WORLD_FILE_LASTEST_107 )
		{
			packet_namespace::w_fread( &lmInfo, sizeof(TWTDObjLightmapInfo), 1, stream );
			plmInfo = &lmInfo;
			pIns = new TWTDObjInstance[lmInfo.ucInstanceNum];
			packet_namespace::w_fread( pIns, sizeof(TWTDObjInstance), lmInfo.ucInstanceNum, stream );
		}
		if( m_wifhead.version >= WORLD_FILE_LASTEST_108 )
		{
			packet_namespace::w_fread( &lmColorData.usColorDataCount, sizeof(lmColorData.usColorDataCount), 1, stream );
			if( lmColorData.usColorDataCount > 0 )
			{
				lmColorData.pColorData = new TWTDOneObjLightmapColorData[lmColorData.usColorDataCount];
				packet_namespace::w_fread( lmColorData.pColorData, sizeof(TWTDOneObjLightmapColorData), lmColorData.usColorDataCount, stream );
			}
		}

		if( RES_INVALID_ID == resMgr->PushStaticModel( objInfo.id, objInfo.pos, objInfo.off, objInfo.rot, objInfo.scl, plmInfo, pIns, &lmColorData ) ) 
		{
			Assert( false );
		}
		if( pIns )
		{
			delete[] pIns;
			pIns = NULL;
		}
		if( lmColorData.pColorData )
		{
			delete[] lmColorData.pColorData;
			lmColorData.pColorData = NULL;
		}

		SwGlobal::SetLoadProgress((float)(++CurrentLoadCount) / AllObjectCount * 100.0f);
	}
	return true;
}
//float fTileMaxY;
bool CWorldReadStream::ReadChunkTable( f_Handle* stream, CWorldTile* tile )
{
	TWTDChunkTable chunkTable;
	packet_namespace::w_fread( &chunkTable, sizeof(TWTDChunkTable), 1, stream );
	CheckThrow( IsSame4Segment( chunkTable.head.segment, "WCTT" ) );


	for( sInt32 i = 0; i < ( tile->GetChunkTotal() ); ++i ) 
	{
		CWorldChunk* worldChunk = tile->GetChunk(i);
		Assert( NULL != worldChunk );
		TWTDChunkInfo chunkInfo;
		if (m_wifhead.version == WORLD_FILE_OLD_VERSION)
		{
			packet_namespace::w_fread( &chunkInfo, sizeof(TWTDChunkInfo) - sizeof(TTextureInfo) * RES_LAYER_NUM, 1, stream );
		}
		else
		{
			packet_namespace::w_fread( &chunkInfo, sizeof(TWTDChunkInfo), 1, stream );
		}
		Assert( (i%tile->GetRowColumn()[0]) == chunkInfo.chunk[0] );
		Assert( (i/tile->GetRowColumn()[0]) == chunkInfo.chunk[1] );

		worldChunk->SetPos( chunkInfo.chunk[0], chunkInfo.chunk[1] );
		worldChunk->SetCulled(chunkInfo.culled);
		sInt32 layerCount = 0;
		for( int l = 0; l < RES_LAYER_NUM; ++l ) 
		{
			worldChunk->m_texture[l] = chunkInfo.layerTable.texId[l];
			if( RES_INVALID_ID != worldChunk->m_texture[l] ) 
			{
				layerCount++;
				worldChunk->m_texInfo[l] = chunkInfo.textureInfo[l];
			}
			if( l < (RES_LAYER_NUM-1) )	
			{
				worldChunk->m_alpha[l]	= chunkInfo.layerTable.alphaId[l];
			}
		}
		worldChunk->m_layerCount	= layerCount;
		worldChunk->m_shadow		= chunkInfo.layerTable.shadowId;
		worldChunk->m_road			= chunkInfo.layerTable.roadResId;
		worldChunk->m_height[0]		=  swInfinity;
		worldChunk->m_height[1]		= -swInfinity;
		worldChunk->m_envId		= chunkInfo.envId;

		for( sInt32 x = 0; x < (WORLD_TILE_CHUNK_UNIT_NUM + 1); ++x ) 
		{
			for( sInt32 y = 0; y < (WORLD_TILE_CHUNK_UNIT_NUM + 1); ++y ) 
			{
				if( worldChunk->m_height[0] > chunkInfo.heightTable.heightB[x][y] )
				{
					worldChunk->m_height[0] = chunkInfo.heightTable.heightB[x][y];
				}
				else if( worldChunk->m_height[1] < chunkInfo.heightTable.heightB[x][y] )
				{
					worldChunk->m_height[1] = chunkInfo.heightTable.heightB[x][y];
				}

				sInt32 vId = y * (WORLD_TILE_CHUNK_UNIT_NUM+1) + x;
				worldChunk->m_vertexOut[vId].height		= chunkInfo.heightTable.heightB[x][y];
				worldChunk->m_vertexOut[vId].niColor = chunkInfo.vertexColorTable.vertexColorB[x][y];
				ColorChange(worldChunk->m_vertexOut[vId].niColor);
				worldChunk->m_vertexOut[vId].normal[0]	= chunkInfo.normalTable.normalB[x][y].value[0];	
				worldChunk->m_vertexOut[vId].normal[1]	= chunkInfo.normalTable.normalB[x][y].value[1];	
				worldChunk->m_vertexOut[vId].normal[2]	= chunkInfo.normalTable.normalB[x][y].value[2];	
				if( x < WORLD_TILE_CHUNK_UNIT_NUM && y < WORLD_TILE_CHUNK_UNIT_NUM ) 
				{
					if( worldChunk->m_height[0] > chunkInfo.heightTable.heightM[x][y] )
					{
						worldChunk->m_height[0] = chunkInfo.heightTable.heightM[x][y];
					}
					else if( worldChunk->m_height[1] < chunkInfo.heightTable.heightM[x][y] )
					{
						worldChunk->m_height[1] = chunkInfo.heightTable.heightM[x][y];
					}

					vId = y * WORLD_TILE_CHUNK_UNIT_NUM + x;
					worldChunk->m_vertexIn[vId].height		= chunkInfo.heightTable.heightM[x][y];
					worldChunk->m_vertexIn[vId].niColor = chunkInfo.vertexColorTable.vertexColorM[x][y];
					ColorChange(worldChunk->m_vertexIn[vId].niColor);
					worldChunk->m_vertexIn[vId].normal[0]	= chunkInfo.normalTable.normalM[x][y].value[0];
					worldChunk->m_vertexIn[vId].normal[1]	= chunkInfo.normalTable.normalM[x][y].value[1];
					worldChunk->m_vertexIn[vId].normal[2]	= chunkInfo.normalTable.normalM[x][y].value[2];
				}

				if( tile->m_height[0] > worldChunk->m_height[0] )
				{
					tile->m_height[0] = worldChunk->m_height[0];
				}
				if( tile->m_height[1] < worldChunk->m_height[1] )
				{
					tile->m_height[1] = worldChunk->m_height[1];
				}
			}
		}
		tile->m_ndlResMgr->PushChunkShape( worldChunk);
		if( chunkInfo.sizeModel > 0 && chunkInfo.sizeModel < RES_MAX_NUM )
		{
			for( size_t i=0; i<chunkInfo.sizeModel; i++ ) 
			{
				TWTDModelRef modelRef;
				packet_namespace::w_fread( &modelRef, sizeof(TWTDModelRef), 1, stream );
				if( IsSame4Segment( modelRef.segment, "WCDR" ) ) 
				{
					worldChunk->PushModel( modelRef.modelId );
				}
			}
		}
		if( chunkInfo.sizeLiquid > 0 && chunkInfo.sizeLiquid < RES_MAX_NUM ) 
		{
			TWTDLiquid liquid;
// 			if (m_wifhead.version == WORLD_FILE_OLD_VERSION)
// 			{
// 				fread( &liquid, sizeof(TWTDLiquid) - sizeof(D3DXCOLOR), 1, stream );
// 				liquid.color = g_defaultLiquidColor;
// 			}
// 			else
			{
				packet_namespace::w_fread( &liquid, sizeof(TWTDLiquid), 1, stream );
			}
			if( IsSame4Segment( liquid.segment, "WTLT" ) ) 
			{
				worldChunk->m_liquidId		= liquid.liquidId; 
				worldChunk->m_liquidHeight	= liquid.height;
				ConvertNiColor2RGB(liquid.color, worldChunk->m_liquidColor);
// 				worldChunk->m_liquidColor = 0xFF000000|worldChunk->m_liquidColor ;
				worldChunk->m_liquidAlphaCoaf = 1.0f;
// 				tile->m_ndlResMgr->PushChunkLiquid( worldChunk, worldChunk->m_shape, worldChunk->m_liquidId, worldChunk->m_liquidHeight,worldChunk->m_liquidColor,worldChunk->m_liquidAlphaCoaf );
			}
		}
		if (m_wifhead.version < WORLD_FILE_LASTEST_106)
		{
			if (chunkInfo.sizeDoodad > 0 && chunkInfo.sizeDoodad < RES_MAX_NUM)
			{
				for (size_t  i = 0; i < chunkInfo.sizeDoodad; ++i)
				{
					TWTDDoodesRef doodes;
					packet_namespace::w_fread( &doodes, sizeof(TWTDDoodesRef), 1, stream );

					AddDoodadLevel(worldChunk, doodes);
					worldChunk->GetDoodadLevel(i)->mdoodadId = doodes.doodesId;
// 					tile->m_ndlResMgr->IncDoodadRef(doodes.doodesId);
					TDoodadLevelInfo* pLevelInfo = worldChunk->GetDoodadLevel(i);
					ReadInDoodadData(pLevelInfo, doodes, stream, tile, worldChunk);

				}
			}
		}
		SwGlobal::SetLoadProgress((float)(++CurrentLoadCount) / AllObjectCount * 100.0f);
	}

	return true;
}




// void CWorldReadStream::LoadWmos( LPCTSTR strPath,void* point )
// {
// 	if( NULL == wcsstr( strPath, _T(".wmo")) ) 
// 	{
// 		return;
// 	}
// 	char workPathName[MAX_PATH*2];
// 
// 	SwPublicFunc::TChar2MutiChar( workPathName, MAX_PATH*2*sizeof(char), strPath, wcslen(strPath) + 1 );
// 	CWorldReadStream* pStream = (CWorldReadStream*)point;
// 	pStream->LoadWmo(workPathName);
// }

bool CWorldReadStream::ReadZoneTable( f_Handle* stream, CResMgr* resMgr )
{
	THead head;
	packet_namespace::w_fread( &head, sizeof(THead), 1, stream );

	CheckThrow( IsSame4Segment( head.segment, "WZON" )  );	

	TWTDEnv zone;
	for( uInt32 i=0; i< head.size; i++ ) {

		packet_namespace::w_fread( &zone, 1, sizeof(TWTDEnv), stream );

		if (zone.lightId == RES_INVALID_ID)
		{
			Trace("Invalid lightId in zone %s",zone.zoneName);
		}
		if (zone.fogId == RES_INVALID_ID)
		{
			Trace("Invalid fogId in zone %s",zone.zoneName);
		}
		resMgr->CreateEnv( zone.zoneName, zone.lightId, zone.fogId );

	}
	return true;
}

bool CWorldReadStream::ReadLightTable( f_Handle* stream, CResMgr* resMgr )
{
	THead head;
	packet_namespace::w_fread( &head, sizeof(THead), 1, stream );
	CheckThrow( IsSame4Segment( head.segment, "WLIG" )  );	
	TWTDLight light;
	for( uInt32 i=0; i<head.size; i++ ) {
		if (m_wifhead.version < WORLD_FILE_LASTEST_105)
		{
			packet_namespace::w_fread( &light, 1, sizeof(TWTDLight) - sizeof(uInt32)*2, stream );
			light.colorSunless = RGB(0xbb,0xbb,0xbb);
		}
		else
		{
			packet_namespace::w_fread( &light, 1, sizeof(TWTDLight), stream );
		}

		CNdlLightRes* lightRes		= MeNew CNdlLightRes;
		lightRes->SetName( light.lightName );

		lightRes->m_lightAmbient	= light.ambientLight;		
		lightRes->m_lightDiffuse	= light.diffuseLight;		
		lightRes->m_lightSpecular	= light.specularLight;		
		lightRes->m_colorSunless	= light.colorSunless;		
		lightRes->m_lightDir[0]		= light.directionLight[0];		
		lightRes->m_lightDir[1]		= light.directionLight[1];		
		lightRes->m_lightDir[2]		= light.directionLight[2];		

		lightRes->SetId(resMgr->m_lightList.size());
		resMgr->m_lightList.push_back( lightRes );
	}
	return true;

}

bool CWorldReadStream::ReadFogTable( f_Handle* stream, CResMgr* resMgr )
{
	THead head;
	packet_namespace::w_fread( &head, sizeof(THead), 1, stream );
	CheckThrow( IsSame4Segment( head.segment, "WFOG" )  );	
	TWTDFog fog;
	for ( uInt32 i=0; i<head.size; i++ ) {
		packet_namespace::w_fread( &fog, 1, sizeof(TWTDFog), stream );

		CNdlFogRes* fogRes	= MeNew CNdlFogRes;
		fogRes->SetName( fog.fogName );

		fogRes->m_lightColor		= fog.fogLight;
		{
			fogRes->m_lightNear			= fog.fogNearLight;
		}
		fogRes->m_lightFar			= fog.fogFarLight;
		fogRes->SetId(resMgr->GetFogList().size());
		resMgr->GetFogList().push_back( fogRes );
	}
	return true;
}
bool CWorldReadStream::LoadZoneRes( CWorldTile* worldTile, const char* pathName )
{
	MeXmlDocument m_doc;
// 	WIN32_FIND_DATAA data;
// 	HANDLE hFind = FindFirstFileA(pathName,&data);
// 	bool bFind = (hFind != INVALID_HANDLE_VALUE);
// 	if (bFind)
	{
		if (!m_doc.LoadFile(pathName))
		{
			Trace("error Zone.config in tile %s!\n",pathName);
			return false;
		}
	}
// 	else
// 	{
// 		return false;
// 	}
	CResMgr * resMgr = worldTile->GetCResMgr();
	MeXmlElement* pRoot = m_doc.FirstChildElement("ZoneList")->ToElement();
	MeXmlElement* pMapNode = pRoot->FirstChildElement( "Zone");
	const char* szRect = NULL;
	RECT rect = {0, 0, 0,  0};
	while (pMapNode)
	{		
		std::wstring str = Common::_tstring::UTF8towcs(pMapNode->Attribute("Name"));
		szRect = pMapNode->Attribute("Rect");
		if (szRect)
		{
			sscanf( szRect, "%d, %d, %d, %d", &rect.left, &rect.top, &rect.right, &rect.bottom);
		}
		sInt32 newId = resMgr->CreateZone(Common::_tstring::toNarrowString(str.c_str()).c_str(),pMapNode->Attribute("Music"), &rect);
		sInt32 recordId = 0;
		pMapNode->QueryIntAttribute("id",&recordId);
		Assert(newId == recordId);
		pMapNode = pMapNode->NextSiblingElement("Zone");
	}
	MeXmlElement* pChunkZoneRoot = m_doc.FirstChildElement( "ChunkZone")->ToElement();
	for (int i = 0; i < worldTile->GetRowColumn()[1];++i)
	{
		//CStringA strKey;
		//strKey.Format("ChunkRow%3d",i);
		//strKey.Replace(' ','0');
		char strKey[MAX_PATH];
		sprintf(strKey, "ChunkRow%3d",i);
		char *p = strchr(strKey, ' ');
		while( p )
		{
			*p = '0';
			p = strchr(strKey, ' ');
		}
		MeXmlElement* pMapNode = pChunkZoneRoot->FirstChildElement(strKey/*.GetString()*/);
		if (pMapNode)
		{
			//CStringA strZone = pMapNode->Attribute("Value");
			char chZone[MAX_PATH];
			//strcpy(chZone,strZone.GetString());
			char strZone[MAX_PATH];
			strcpy(strZone, pMapNode->Attribute("Value"));
			strcpy(chZone, strZone);

			int strlength = strlen(strZone);
			for (int z = 0; z < strlength; ++z)
			{
				if (chZone[z] == ' ')
				{
					chZone[z] = '\0';
				}
			}
			char* chZoneId = chZone;
			for(int j = 0; j < worldTile->GetRowColumn()[0]; ++j)
			{
				CWorldChunk* chunk = worldTile->GetChunk(j,i);
				while(*chZoneId == '\0')
				{
					++chZoneId;
				}
				int zoneId = atoi(chZoneId);
				chZoneId += strlen(chZoneId);
				chunk->SetZoneId(zoneId);
			}
		}
	}
	return true;

}

bool CWorldReadStream::LoadDoodadRes( CWorldTile* tile, const char* pathName )
{
	Assert( NULL != tile );
	Assert( NULL != pathName );
	if (m_wifhead.version < WORLD_FILE_LASTEST_106)
	{
		return true;
	}

	size_t uiReadSize = 0;
	f_Handle* stream = NULL;
	try
	{
// 		sInt32 offset = 0;
		CheckThrow( packet_namespace::w_fopen_s( &stream, pathName, "rb" ) == 0 );


		TRoadResHead head;
		uiReadSize = packet_namespace::w_fread( &head, sizeof( TRoadResHead ), 1, stream );
//		CheckThrow( uiReadSize != sizeof(TRoadResHead) );
		CheckThrow( IsSame4Segment( head.head.segment, "WCAO" )  );	
		if (head.version < WORLD_FILE_LASTEST_106)
		{
			throw( "unsupported Doodad file version \n" );
		}
		else 
		{
			for( sInt32 chunkId=0; chunkId<(tile->GetChunkTotal()); chunkId++ ) 
			{
				TWTDDoodadInfo chunkInfo;
				uiReadSize = packet_namespace::w_fread( &chunkInfo, sizeof( TWTDDoodadInfo ), 1, stream );
//				CheckThrow( uiReadSize != sizeof(TWTDDoodadInfo) );
				CWorldChunk* worldChunk = tile->GetChunk(chunkId);
				if (chunkInfo.sizeDoodad > 0 && chunkInfo.sizeDoodad < RES_MAX_NUM)
				{
					for (size_t  i = 0; i < chunkInfo.sizeDoodad; ++i)
					{
						TWTDDoodesRef doodes;
						packet_namespace::w_fread( &doodes, sizeof(TWTDDoodesRef), 1, stream );

						AddDoodadLevel(worldChunk, doodes);
						worldChunk->GetDoodadLevel(i)->mdoodadId = doodes.doodesId;
// 						tile->m_ndlResMgr->IncDoodadRef(doodes.doodesId);
						TDoodadLevelInfo* pLevelInfo = worldChunk->GetDoodadLevel(i);
						ReadInDoodadData(pLevelInfo, doodes, stream, tile, worldChunk);

					}
				}
			}
		}

		packet_namespace::w_fclose( stream );
	}
	catch( const char* s )
	{
		Trace( "failed read doodad resource:[ %s ] \n", s );
		if( NULL != stream )
		{
			packet_namespace::w_fclose( stream );
			stream	= NULL;
		}
		return false;
	}
	catch(...)
	{
		Trace( "failed read doodad resource:\n");
		if( NULL != stream )
		{
			packet_namespace::w_fclose( stream );
			stream	= NULL;
		}
		return false;
	}
	return true;

}

bool CWorldReadStream::LoadAlphaRes( CWorldTile* tile, const char* pathName )
{
	Assert( NULL != tile );
	Assert( NULL != pathName );

	size_t uiReadSize = 0;
	f_Handle* stream = NULL;
	try
	{
// 		sInt32 offset = 0;
		CheckThrow( packet_namespace::w_fopen_s( &stream, pathName, "rb" ) == 0 );


		TRoadResHead head;
		uiReadSize = packet_namespace::w_fread( &head, sizeof( TRoadResHead ), 1, stream );
//		CheckThrow( uiReadSize != sizeof(TRoadResHead) );
		CheckThrow( IsSame4Segment( head.head.segment, "WALP" )  );	
		if (head.version < WORLD_FILE_LASTEST_106)
		{
			throw( "unsupported alpha file version \n" );
		}
		else 
		{
			if( !ReadAlphaTable( stream, tile->m_ndlResMgr ) )
			{
				Trace( "Error read texture table! \n" );
			}

		}

		packet_namespace::w_fclose( stream );
	}
	catch( const char* s )
	{
		Trace( "failed read alpha resource:[ %s ] \n", s );
		if( NULL != stream )
		{
			packet_namespace::w_fclose( stream );
			stream	= NULL;
		}
		return false;
	}
	catch(...)
	{
		Trace( "failed read alpha resource: \n");
		if( NULL != stream )
		{
			packet_namespace::w_fclose( stream );
			stream	= NULL;
		}
		return false;
	}

	return true;
}


void CWorldReadStream::ReadInDoodadData( TDoodadLevelInfo* pLevelInfo, TWTDDoodesRef &doodes, f_Handle* stream, CWorldTile* tile, CWorldChunk* worldChunk )
{
	TDoodadInfoForEdit* pBuffer = MeNew TDoodadInfoForEdit[doodes.mulevelUnit*doodes.mulevelUnit];
	packet_namespace::w_fread(pBuffer,sizeof(TDoodadInfoForEdit)*doodes.mulevelUnit*doodes.mulevelUnit,1,stream);
	for (int z = 0; z < doodes.mulevelUnit*doodes.mulevelUnit; ++z)
	{
		pLevelInfo->GetDoodad(z).m_nScale = pBuffer[z].m_nScale;
	}
	delete [] pBuffer;
}

void CWorldReadStream::InitializeLoadLevel( CWorldChunk* worldChunk )
{
	worldChunk->SetLoadLevel(CWorldChunk::eInitialize);
}

void CWorldReadStream::AddDoodadLevel( CWorldChunk* worldChunk, TWTDDoodesRef &doodes )
{
	worldChunk->AddDoodadLevel(doodes.mulevelUnit);
}

void CWorldReadStream::ColorChange( COLORREF& niColor )
{
	if (m_ColorChange)
	{
		m_ColorChange(niColor);
	}
}

bool CWorldReadStream::ReadLightMapTable( f_Handle* stream, CWorldTile* tile )
{
	TWTDLightMap lmTable;
	packet_namespace::w_fread( &lmTable, sizeof(TWTDLightMap), 1, stream );
	if( !IsSame4Segment(lmTable.head.segment,"WLMP") )
	{
		return false;
	}
	if( lmTable.head.size <=0 )
	{
		return true;
	}

	tile->ClearLightMaps();
	for( int i=0; i<lmTable.head.size; ++i )
	{
		tile->LoadLightMap(i);
	}

	tile->RefreshLightmapTexId();

	return true;
}