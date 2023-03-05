/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	NdlWorldCreater.cpp
* Date: 	02/05/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "Resource/resource.h"
#include "RapidXml/MeRapidXml.h"
#include "EditRes/NdlEditRes.h"
#include "MeTerrain/NdlResMgr.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldTile.h"
#include "MeTerrain/WorldChunk.h"
#include "Ndl/NdlWorldEditor.h"
#include "Map/WorldWriteStream.h"
#include "WorldEditor.h"
#include <algorithm>
#include "Edit/ToolVertex.h"
#include "ui/Custom/TexturePreviewWnd.h"
#include "ui/Custom/TextureNavigationWnd.h"
#include "ui/ToolsScene/ToolWorld.h"
#include "MeTerrain/MapConfigXml.h"
// #include "MeTerrain/FlyRouteXml.h"
#include "MeTerrain/NPCRouteXml.h"
#include "MeTerrain/SoundPointXml.h"
#include "Me3d/engine/RendererDx.h"
#include "ui/Dlg/LightMapProcessDlg.h"
#include "MeTerrain/Lighting/StaticMeshRayTracer.h"
#include "MeTerrain/Lighting/LightMapTexture.h"
#include "ui/Dlg/LightMapMeshProcessDlg.h"
////////////////////////////////////////////////////////////////////////////////
namespace {
#define GlAtomFromPos(x,y,i)		( ZnFloor2Int( ((x)+WORLDORIGIN(i))/y ) )
#define AtomFromGlAtom(x,y)		( (x == CURRENTTILE->GetRowColumn()[i]*y)? y : (x%y) ) 

#define ChunkFromGlVert(x,i)		( (x == CURRENTTILE->GetRowColumn()[i]*WORLD_TILE_CHUNK_VERT_NUM)?(CURRENTTILE->GetRowColumn()[i] - 1):(x)/WORLD_TILE_CHUNK_VERT_NUM )

#define GlChunkFromGlAtom(x,y)	( (x == CURRENTTILE->GetRowColumn()[i]*y)?(CURRENTTILE->GetRowColumn()[i] - 1):(x)/y )
#define GlAtomMinFromGlChunk(x,y)	( (x)*y )
#define GlAtomMaxFromGlChunk(x,y)	( (x+1)*y-1 )

#define GLVertFromPos(x,i)		( ZnFloor2Int( ((x)+WORLDORIGIN(i))/WORLD_VERTSIZE ) )
#define PosFromGLVert(x,i)		( (x)*WORLD_VERTSIZE - WORLDORIGIN(i) )

	
	////////////////////////////////////////////////////////////////////////////////
	const flt32 l_minHeight = WORLD_UNITSIZE * 0.5f;
	////////////////////////////////////////////////////////////////////////////////
	struct _TVert {
		sInt32	chunk[2];
		sInt32	vert[2];
	};
	sInt32 GetSameVert( _TVert* outVertList, const _TVert& inVert ) {
		_TVert vert;
		sInt32 sameCount = 0;
		if( (inVert.vert[0]==0) && (inVert.vert[1]!=0) ) {
			memcpy( &vert, &inVert, sizeof(inVert) );
			vert.vert[0]	= WORLD_TILE_CHUNK_VERT_NUM;
			vert.chunk[0]	= vert.chunk[0] - 1;
			if( vert.chunk[0] >= 0 ) {
				outVertList[sameCount++] = vert;
			}
			
		}
		else if( (inVert.vert[0]!=0) && (inVert.vert[1]==0) ) {
			memcpy( &vert, &inVert, sizeof(inVert) );
			vert.vert[1]	= WORLD_TILE_CHUNK_VERT_NUM;
			vert.chunk[1]	= vert.chunk[1] - 1;
			if( vert.chunk[1] >= 0 ) {
				outVertList[sameCount++] = vert;
			}
		}
		else if( (inVert.vert[0]==0) && (inVert.vert[1]==0) ) {
			memcpy( &vert, &inVert, sizeof(inVert) );
			vert.vert[0]	= WORLD_TILE_CHUNK_VERT_NUM;
			vert.chunk[0]	= vert.chunk[0] - 1;
			if( vert.chunk[0] >= 0 ) 
			{
				outVertList[sameCount++] = vert;
			}
			
			memcpy( &vert, &inVert, sizeof(inVert) );
			vert.vert[1]	= WORLD_TILE_CHUNK_VERT_NUM;
			vert.chunk[1]	= vert.chunk[1] - 1;
			if( vert.chunk[1] >= 0 ) 
			{
				outVertList[sameCount++] = vert;
			}

			memcpy( &vert, &inVert, sizeof(inVert) );
			vert.vert[0]	= WORLD_TILE_CHUNK_VERT_NUM;
			vert.chunk[0]	= vert.chunk[0] - 1;
			vert.vert[1]	= WORLD_TILE_CHUNK_VERT_NUM;
			vert.chunk[1]	= vert.chunk[1] - 1;
			if (vert.chunk[0] >= 0 && vert.chunk[1] >= 0)
			{
				outVertList[sameCount++] = vert;
			}
		}
		else {
			
		}
		return sameCount;
	};
	struct _TProjRect {
		uInt32	brushMin[2];
		uInt32	brushMax[2];	
		sInt32	chunk[2];	
		uInt32	atomMin[2];	// 
		uInt32	atomMax[2];	// 
	};
	struct TProjResult {
		std::vector<_TProjRect*> resultList;
		~TProjResult() {
			for(size_t i=0;i<resultList.size();i++)	{
				SAFE_DELETE( resultList[i] );
			}
			resultList.clear();
		}
	};
	struct TGlAtomList {
		std::vector<sInt32>	glAtomList;
	};
	size_t ProjectWorld( flt32* minPt, flt32* maxPt, TProjResult& projResult,flt32 fworldAtomSize,uInt32 uWorldTileChunkAtomNum ) {
		sInt32 glChunkMin[2];
		sInt32 glAtomMin[2];
		sInt32 glChunkMax[2];
		sInt32 glAtomMax[2];
		sInt32 glChunk[2];
		sInt32 glAtom[2];
		sInt32 subChunk;
		TGlAtomList glAtomList[2];
		for( sInt32 i=0; i<2; i++ )	{
			glAtomMin[i]	= GlAtomFromPos( minPt[i],fworldAtomSize,i );
			glChunkMin[i]	= GlChunkFromGlAtom( glAtomMin[i] ,uWorldTileChunkAtomNum);
			glAtomMax[i]	= GlAtomFromPos( maxPt[i],fworldAtomSize,i );
			glChunkMax[i]	= GlChunkFromGlAtom( glAtomMax[i],uWorldTileChunkAtomNum );
			
			subChunk		= glChunkMax[i]-glChunkMin[i];
			glChunk[i]		= glChunkMin[i];
			glAtom[i]		= glAtomMin[i];
			glAtomList[i].glAtomList.push_back( glAtom[i] );
			for( sInt32 c=0; c<subChunk; c++ ) {
				glAtom[i]	= GlAtomMaxFromGlChunk( glChunk[i],uWorldTileChunkAtomNum );
				glAtomList[i].glAtomList.push_back( glAtom[i] );

				glAtom[i]	= GlAtomMinFromGlChunk( glChunk[i]+1 ,uWorldTileChunkAtomNum);
				glAtomList[i].glAtomList.push_back( glAtom[i] );

				glChunk[i]++;
			}
			glAtom[i]		= glAtomMax[i];
			glAtomList[i].glAtomList.push_back( glAtom[i] );
		} 
		Assert( glAtomList[0].glAtomList.size()>1 );
		Assert( glAtomList[1].glAtomList.size()>1 );
		
		_TProjRect* newRect = NULL;
		size_t at[2];
		sInt32 baseAtom[2];
		baseAtom[0] = glAtomList[0].glAtomList[0];
		baseAtom[1] = glAtomList[1].glAtomList[0];
		for( at[1]=0; at[1]<glAtomList[1].glAtomList.size()-1; at[1]+=2 ) {
			for( at[0]=0; at[0]<glAtomList[0].glAtomList.size()-1; at[0]+=2 ) {
				newRect = new _TProjRect;
				for( sInt32 i=0; i<2; i++ ) {
					sInt32 atom				= glAtomList[i].glAtomList[at[i]];
					newRect->chunk[i]		=  GlChunkFromGlAtom(atom,uWorldTileChunkAtomNum);
					newRect->atomMin[i]		= AtomFromGlAtom( atom ,uWorldTileChunkAtomNum);
					newRect->atomMax[i]		= AtomFromGlAtom( glAtomList[i].glAtomList[at[i]+1],uWorldTileChunkAtomNum );
					newRect->brushMin[i]	= atom-baseAtom[i];
					newRect->brushMax[i]	= glAtomList[i].glAtomList[at[i]+1]-baseAtom[i];
					
				}
				Assert( newRect->atomMax[0] >= newRect->atomMin[0] );
				Assert( newRect->atomMax[1] >= newRect->atomMin[1] );
				//Trace( "tile[%d][%d],chunk[%d][%d],atomMin[%d][%d],atomMax[%d][%d],brushMin[%d][%d],brushMax[%d][%d] \n"
				//		, newRect->tile[0], newRect->tile[1]
				//		, newRect->chunk[0], newRect->chunk[1]
				//		, newRect->atomMin[0], newRect->atomMin[1]
				//		, newRect->atomMax[0], newRect->atomMax[1] 
				//		, newRect->brushMin[0], newRect->brushMin[1]
				//		, newRect->brushMax[0], newRect->brushMax[1] );
				projResult.resultList.push_back( newRect );
			}
		}
		return projResult.resultList.size();
	}

	void BlendWithMode( uAlphaBit& blendDest,int nMod, uInt8 blendSrc, znLayerBlendMode blendMode, uInt8 alpha ) {
		Assert( ((alpha&0xF0)>>4) == (alpha&0x0F) );
		//Assert( (>>4) == (blendSrc&0x0F) );
		uInt8 blendDest8 = 0xFF;
		if (0 == nMod)
		{
			blendDest8 = (blendDest&0xF0) | ((blendDest&0xF0) >> 4);
		}
		else
		{
			blendDest8 = (blendDest&0x0F) | ((blendDest&0x0F) << 4);
		}
// 		uInt8 blendDest8 = UINT32HIGHTOUINT8(blendDest);
		Assert( ((blendDest8&0xF0)>>4) == (blendDest8&0x0F) );
		uInt8 bSrc		= (blendSrc&0xF0);
		bSrc			= bSrc|(bSrc>>4);
		flt32 percent	= (flt32)bSrc*(flt32)alpha/255.0f;
		sInt32 color	= ZnFloat2Int( percent );
		color = ZnClamp<sInt32>( color, 0x0, 0xFF );
		switch( blendMode )	{
			case znLBM_Add:
				color		= blendDest8-color;
				blendDest8	= ZnClamp<sInt32>( color, 0x0, 0xFF );
				break;
			case znLBM_InvAdd:
				color		= blendDest8+color;
				blendDest8	= ZnClamp<sInt32>( color, 0x0, 0xFF );
				break;
			case znLBM_SetUp:
				color	= 0xFF-color;
				if( blendDest8 > color )
					blendDest8	= (color);
				break;
			case znLBM_SetDown:
//				color	= 0xFF-color;
				if( blendDest8 < color )
					blendDest8	= (color);
				break;
// 			case znLBM_InvDelta:
// 				color		= blendDest-0x11;
// 				blendDest	= ZnClamp<sInt32>( color, 0x0, 0xFF );
// 				break;
			default:
				Assert( false );
				break;
		}
		blendDest8	= blendDest8&0xF0;
		blendDest8	= blendDest8|(blendDest8>>4);
		Assert( ((blendDest8&0xF0)>>4) == (blendDest8&0x0F) );
		if (0 == nMod)
		{
			blendDest = (blendDest&0x0F) | ((blendDest8) & 0xF0);	
		}
		else
		{
			blendDest = (blendDest&0xF0) | ((blendDest8) & 0x0F);	
		}
// 		blendDest = UINT8TOUINT32HIGH(blendDest8);
	}
};
//---------------------------------------------------------
/*
@added by jiayi
@desc:below are the functions to fix the 
	  alpha problem when in the edge of a chunk.
@originBrush: is the original brush data 
	  that loaded from disk.
@BeginEdgeAlphaTrick:to find the edge and assign a same alpha 
	  value to the both side of that edge.
@EndEdgeAlphaTrick:restore the brush data.
*/
//---------------------------------------------------------
uInt8* originBrush = new uInt8[ 128 * 128 ];
//---------------------------------------------------------
void BeginEdgeAlphaTrick( TProjResult& projResult, uInt8* brush, uInt32 brushSize)
{
	memcpy_s( originBrush, brushSize * brushSize, brush, brushSize * brushSize);
	/*
	the rule:
	either the x or y axis need to be fixed, the whole line
	will be changed. so there are only two operations: change x
	axis and change y axis.
	*/
	//flag of x&y axis
	bool bFixX = false;
	bool bFixY = false;
	//flag to determine is it the first compare
	sInt32 nFlagChunkX = -1;
	sInt32 nFlagChunkY = -1;
	//determine which axis need to be fixed
	for(uInt32 i = 0 ; i < projResult.resultList.size(); ++i)
	{
		_TProjRect* projRect = projResult.resultList[i];
		if( !bFixX && (nFlagChunkX != projRect->chunk[0]) ){
			if(nFlagChunkX != -1)
				bFixX = true;	
			nFlagChunkX = projRect->chunk[0];
		}
		if( !bFixY && (nFlagChunkY != projRect->chunk[1]) ){
			if(nFlagChunkY != -1)
				bFixY = true;	
			nFlagChunkY = projRect->chunk[1];
		}
	}
	//get the first one
	_TProjRect* projRect = projResult.resultList[0];
	uInt32 size[2];
	size[0]	= projRect->brushMax[0]-projRect->brushMin[0]+1;
	size[1]	= projRect->brushMax[1]-projRect->brushMin[1]+1;
	if( bFixX)//x
	{
		//assign the alpha value to the both side
		for( uInt32 y = 0 ; y < brushSize; ++ y)
		{
			uInt32 off = y * brushSize + size[0] - 1;
			uInt32 offRight = off + 1;
			brush[off] = brush[offRight];
		}
	}
	if( bFixY)//y
	{
		//assign the alpha value to the both side
		for( uInt32 x = 0 ; x < brushSize; ++ x)
		{
			uInt32 off = (size[1] -1) * brushSize + x;
			uInt32 offUp = (size[1]) * brushSize + x;
			brush[off] = brush[offUp];
		}
	}
}
//---------------------------------------------------------
void EndEdgeAlphaTrick(uInt8* brush, uInt32 brushSize)
{
	memcpy_s( brush, brushSize * brushSize, originBrush, brushSize * brushSize );
}
//---------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
CNdlWorldEditor::CNdlWorldEditor( )
{
	m_world				= NULL;
	m_changeMeshChunkList.clear();
	m_changeMatlChunkList.clear();
	m_changeTileList.clear();
}

CNdlWorldEditor::~CNdlWorldEditor()
{
	m_world		= NULL;
	m_changeMeshChunkList.clear();
	m_changeMatlChunkList.clear();
	m_changeTileList.clear();
	SAFE_DELETE_ARRAY(originBrush);
}

bool CNdlWorldEditor::Create( CWorld* world )
{
	m_world			= world;
	
	return true;
}

bool CNdlWorldEditor::NewWorld()
{
	m_world->m_isActive = true;

	return true;
}


bool CNdlWorldEditor::DeleteTile( uInt32 tileId )
{
	CWorldTile* worldTile = m_world->GetWorldBuffer()->GetTile(tileId);
	if (worldTile == NULL)
		return false;

	CString tileName;
	tileName.Format(_T("%hs\\%hs"),m_world->GetWorldPath(),worldTile->GetPathName());
	if (worldTile == m_world->GetWorldBuffer()->GetActiveTile())
	{
		CWorldEditDoc::GetActiveMapDoc()->Reset();
	}
	CMapConfigXml::Instance()->DeleteTileMapInfor(tileId);
// 	CFlyRouteXml::Instance()->DeleteTileFlyRoute(tileId);
	CNPCRouteXml::Instance()->DeleteTileNPCRoute(tileId);
	CSoundPointXml::Instance()->DeleteTileSoundPoint(tileId);
	m_world->GetWorldBuffer()->ReomveTileRes(tileId);
	SetFileAttributes(tileName,FILE_ATTRIBUTE_NORMAL);
	return DeleteFile(tileName);

}


CWorldTile* CNdlWorldEditor::NewTile( const char* pTileFullName, const char* baseTexture, flt32 height, uInt32 row,uInt32 column,flt32 heightMapUnit, const CImage* heightMap, CToolWorld* worlDlg )
{
	ASSERT(NULL == m_world->m_worldBuffer->GetTileFromPath(pTileFullName));

	theApp.SetPromptText( _T( "正在创建新地表..." ) );

	CWorldTile* worldTile = NULL;

	sInt32 baseCood[2];
	//if( NULL != heightMap )	
	//{
	//	if( ((heightMap->GetWidth()-1) % 8) != 0 || ((heightMap->GetHeight()-1) % 8) != 0 ) 
	//	{
	//		::AfxMessageBox( _T("高度图尺寸错误!"), MB_OK );
	//		return false;
	//	}
	//}
	{
		baseCood[0]	= 0;
		baseCood[1] = column * 8;	// 上下颠倒
		{
			worldTile = m_world->m_worldBuffer->PushTileRes(-1,pTileFullName);
			worldTile->SetRowColumn( row, column);
			worldTile->SetModify(true);
			worldTile->m_isLoad				= true;
			m_world->m_worldBuffer->SetActiveTile(worldTile);

			sInt32 texId					= worldTile->m_ndlResMgr->PushTexture( baseTexture );
			for( int i = 0; i < worldTile->GetChunkTotal(); i++ ) 
			{
				CWorldChunk* worldChunk = worldTile->m_chunckTable[i];
				worldChunk->Reset( worldTile );		
				worldChunk->SetPos( i%worldTile->GetRowColumn()[0], i/worldTile->GetRowColumn()[0]);
				if( NULL != heightMap ) 
				{
					FillChunkWithSHeightmap( worldChunk, height, heightMapUnit, texId, heightMap, baseCood );
				}
				else 
				{
					FillChunkNoHeightmap( worldChunk, height, texId );	
				}
				worldChunk->m_layerCount	= 1;
				worldChunk->m_liquidId = RES_INVALID_ID;
				Assert( RES_INVALID_ID == worldChunk->m_maskId );
				worldChunk->m_shape			= worldTile->m_ndlResMgr->PushChunkShape( worldChunk);
				//worldTile->m_ndlResMgr->PushMask( worldChunk );
				//worldTile->m_ndlResMgr->RefreshChunkMask( worldChunk );
				worldChunk->m_isLoad		= true;

				worldTile->m_height[0] = ZnMin( worldTile->m_height[0], worldChunk->m_height[0] );
				worldTile->m_height[1] = ZnMax( worldTile->m_height[1], worldChunk->m_height[1] );
				
				theApp.SetLoopCountText( i%worldTile->GetRowColumn()[0], i/worldTile->GetRowColumn()[0]);

			}
			UpdateNormal( worldTile );
			((CResEditMgr*)worldTile->m_ndlResMgr)->RefreshNormal();
			CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldTile );
			CWorldEditDoc::GetActiveMapDoc()->WriteDirtyTile( false );
			
			// 创建tile四叉树
			worldTile->m_tileQuadTree.Create(worldTile);

			CString prompt;
			prompt.Format( _T("创建Tile[%s]"), pTileFullName );
			theApp.SetPromptText( prompt );
		}
	}
	theApp.SetPromptText( _T( "创建新地表完成" ) );

	return worldTile;
}

bool CNdlWorldEditor::FillChunkWithSHeightmap( CWorldChunk* chunk, flt32 height, flt32 heightMapUnit, sInt32 textureId, const CImage* heightMap, const sInt32* baseCoord )
{
	Assert( NULL != heightMap );

	sInt32 offX = chunk->m_chunk[0]*8;
	sInt32 offY = chunk->m_chunk[1]*8;

	for( sInt32 j = 0; j < (WORLD_TILE_CHUNK_UNIT_NUM+1)*(WORLD_TILE_CHUNK_UNIT_NUM+1); j++ ) {
		sInt32 x = j%(WORLD_TILE_CHUNK_UNIT_NUM+1)+offX;
		sInt32 y = j/(WORLD_TILE_CHUNK_UNIT_NUM+1)+offY;
		COLORREF col = heightMap->GetPixel(baseCoord[0]+x,baseCoord[1]-y);
		// 取红色
		flt32 h						= ((flt32)(col&0xFF)-128.0f)*heightMapUnit;
		chunk->m_vertexOut[j].height= height+h;
		chunk->m_height[0]			= ZnMin<flt32>( chunk->m_height[0], chunk->m_vertexOut[j].height );
		chunk->m_height[1]			= ZnMax<flt32>( chunk->m_height[1], chunk->m_vertexOut[j].height );
	}
	for( sInt32 j = 0; j < WORLD_TILE_CHUNK_UNIT_NUM*WORLD_TILE_CHUNK_UNIT_NUM; j++ ) {
		sInt32 x	= j%WORLD_TILE_CHUNK_UNIT_NUM;
		sInt32 y	= j/WORLD_TILE_CHUNK_UNIT_NUM;
		flt32 h0	= chunk->m_vertexOut[y*(WORLD_TILE_CHUNK_UNIT_NUM+1)+x].height;
		flt32 h1	= chunk->m_vertexOut[(y+1)*(WORLD_TILE_CHUNK_UNIT_NUM+1)+x].height;
		flt32 h2	= chunk->m_vertexOut[(y)*(WORLD_TILE_CHUNK_UNIT_NUM+1)+x+1].height;
		flt32 h3	= chunk->m_vertexOut[(y+1)*(WORLD_TILE_CHUNK_UNIT_NUM+1)+x+1].height;
		flt32 h		= (h0+h1+h2+h3)/4;
		chunk->m_vertexIn[j].height	= h;
	}
	chunk->m_layerCount = 1;
	chunk->m_texture[TextureLayer0] = textureId;

	CNdlTextureRes* pTexture = chunk->m_parentTile->GetCResMgr()->GetTexture(textureId);
	pTexture->IncRefCount();

	return true;
}

bool CNdlWorldEditor::FillChunkNoHeightmap( CWorldChunk* chunk, flt32 height, sInt32 textureId )
{
	chunk->m_height[0] = ZnMin<flt32>( chunk->m_height[0], height );
	chunk->m_height[1] = ZnMax<flt32>( chunk->m_height[1], height );

	for( sInt32 j = 0; j < (WORLD_TILE_CHUNK_UNIT_NUM+1)*(WORLD_TILE_CHUNK_UNIT_NUM+1); j++ ) {
		chunk->m_vertexOut[j].height = height;
	}
	for( sInt32 j = 0; j < WORLD_TILE_CHUNK_UNIT_NUM*WORLD_TILE_CHUNK_UNIT_NUM; j++ ) {
		chunk->m_vertexIn[j].height = height;
	}
	chunk->m_layerCount = 1;
	chunk->m_texture[TextureLayer0] = textureId;

	CNdlTextureRes* pTexture = chunk->m_parentTile->GetCResMgr()->GetTexture(textureId);
	pTexture->IncRefCount();

	return true;
}

bool CNdlWorldEditor::CheckVertex( const sInt32* vertId )
{
	//CWorldChunk* worldChunk = m_world->m_worldBuffer->GetChunk( vertInfo.tile[0], vertInfo.tile[1], vertInfo.chunk[0], vertInfo.chunk[1] );
	//if( NULL == worldChunk )	
	//	return false;
	return true;
}       

bool CNdlWorldEditor::AddVertDeltaHeight( flt32& retHeight,  const sInt32* chunk, const sInt32* vert, flt32 deltaHeight )
{
	CWorldChunk* worldChunk = m_world->m_worldBuffer->GetChunk(  chunk[0], chunk[1] );
	if( NULL == worldChunk )	
		return false;

	sInt32 axis[2];
	for( sInt32 i=0; i<2; i++ )	{
		axis[i] = vert[i]/2;
	}
	if( vert[0]%2 == 0 ) {
		if( vert[1]%2 == 0 ) {
			flt32& height	= worldChunk->m_vertexOut[axis[1]*(WORLD_TILE_CHUNK_UNIT_NUM+1)+axis[0]].height;
			height			+= deltaHeight;
			retHeight		= height;
		}
		else {
			Assert( false );
		}
	}
	else {
		if( vert[1]%2 == 1 ) {
			flt32& height	= worldChunk->m_vertexIn[axis[1]*WORLD_TILE_CHUNK_UNIT_NUM+axis[0]].height;
			height			+= deltaHeight;
			retHeight		= height;
		}
		else {
			Assert( false );
		}
	}
	SetChunkMeshDirty( worldChunk );

	return true;
}

bool CNdlWorldEditor::SetVertHeight(  const sInt32* chunk, const sInt32* vert, flt32 height )
{
	CWorldChunk* worldChunk = m_world->m_worldBuffer->GetChunk(  chunk[0], chunk[1] );
	if( NULL == worldChunk )	
		return false;

	sInt32 axis[2];
	for( sInt32 i=0; i<2; i++ )	{
		axis[i] = vert[i]/2;
	}
	if( vert[0]%2 == 0 ) {
		if( vert[1]%2 == 0 ) {
			worldChunk->m_vertexOut[axis[1]*(WORLD_TILE_CHUNK_UNIT_NUM+1)+axis[0]].height = height;
		}
		else {
			Assert( false );
		}
	}
	else {
		if( vert[1]%2 == 1 ) {
			worldChunk->m_vertexIn[axis[1]*WORLD_TILE_CHUNK_UNIT_NUM+axis[0]].height = height;
		}
		else {
			Assert( false );
		}
	}
	SetChunkMeshDirty( worldChunk );

	return true;
}

// 1
// |  		**
// | 	   *  *
// | 	  *	   *
// | 	  *	   *
// | 	 *		*
// |   **		 **
// |***			   ***
// |___________________
// 0                   1
flt32 GetWeightFromDist( flt32 distSqr, flt32 brushSize )
{
	flt32 radiusOut	= brushSize * 0.8f;
	flt32 alpha		= distSqr / (radiusOut * radiusOut);
	if( alpha > 1.0f )
		alpha = 1.0f;
	
	flt32 weight	= (Cos( alpha * PI )+1.0f) * 0.5f;

	return weight * weight;
}

bool CNdlWorldEditor::UpDownVert( const flt32* origin, flt32 brushSize, flt32 deltaHeight )
{
	sInt32 vertCount = ZnFloat2Int( brushSize/WORLD_VERTSIZE ) + 1;
	
	sInt32 centerVert[2], vId[2];
	flt32 vertDist[2];

	centerVert[0]		= GLVertFromPos( origin[0] ,0);
	centerVert[1]		= GLVertFromPos( origin[1],1 );

	flt32 refHeight	= 0.0f;			
	_TVert vertList[3];
	_TVert vert;

	for( sInt32 y=-(vertCount); y<vertCount; y++ ) {
		for( sInt32 x=-vertCount; x<vertCount; x++ ) {
			vId[0]			= centerVert[0] + x;
			vId[1]			= centerVert[1] + y;

			if(vId[0] < 0 || vId[1] < 0 
				|| vId[0] > (WORLD_TILE_CHUNK_UNIT_NUM*CURRENTTILE->GetRowColumn()[0])*2
				|| vId[1] > (WORLD_TILE_CHUNK_UNIT_NUM*CURRENTTILE->GetRowColumn()[1])*2
				)
			{
				continue;
			}

			if( ( vId[0] % 2 ) != ( vId[1] % 2 ) )
				continue;
			
			vertDist[0]		= PosFromGLVert( vId[0] ,0) - origin[0];
			vertDist[1]		= PosFromGLVert( vId[1] ,1) - origin[1];
			
			flt32 distSqr	= vertDist[0] * vertDist[0] + vertDist[1] * vertDist[1];
			flt32 weight	= GetWeightFromDist( distSqr, brushSize );
			
			vert.chunk[0]	= ChunkFromGlVert( vId[0] ,0);
			vert.chunk[1]	= ChunkFromGlVert( vId[1] ,1);
			vert.vert[0]	= vId[0] - vert.chunk[0]* WORLD_TILE_CHUNK_VERT_NUM;
			vert.vert[1]	= vId[1] - vert.chunk[1]* WORLD_TILE_CHUNK_VERT_NUM;;

			bool isOk		= AddVertDeltaHeight( refHeight,  vert.chunk, vert.vert, deltaHeight * weight );
			
			sInt32 sameCount = GetSameVert( vertList, vert );
			for( sInt32 j=0; j<sameCount; j++ ) {
				const _TVert& p = vertList[j];
				if( isOk )	{	
					// 同步高度.
					SetVertHeight( p.chunk, p.vert, refHeight );
				}
				else {
					isOk = AddVertDeltaHeight( refHeight, p.chunk, p.vert, deltaHeight * weight );
				}
			}
		}
	}
	UpdateShape();
	
	return true;
}

bool CNdlWorldEditor::SmoothVert( const flt32* origin, flt32 brushSize, flt32 deltaScale )
{
	sInt32 vertCount = ZnFloat2Int( brushSize/WORLD_VERTSIZE ) + 1;

	sInt32 centerVert[2], vId[2];
	flt32 vertDist[2];

	centerVert[0]	= GLVertFromPos( origin[0],0 );
	centerVert[1]	= GLVertFromPos( origin[1],1 );

	flt32 refHeight	= 0.0f;			
	_TVert vertList[3];
	_TVert vert;
	
	for( sInt32 y=-(vertCount); y<vertCount; y++ ) {
		for( sInt32 x=-vertCount; x<vertCount; x++ ) {
			vId[0]			= centerVert[0] + x;
			vId[1]			= centerVert[1] + y;
			if(vId[0] < 0 || vId[1] < 0 
				|| vId[0] > (WORLD_TILE_CHUNK_UNIT_NUM*CURRENTTILE->GetRowColumn()[0])*2
				|| vId[1] > (WORLD_TILE_CHUNK_UNIT_NUM*CURRENTTILE->GetRowColumn()[1])*2
				)
			{
				continue;
			}
			if( ( vId[0] % 2 ) != ( vId[1] % 2 ) )
				continue;

			flt32 height, tmpHeight;
			if( !GetVertHeight( vId, height ) ) {
				continue;
			}

			vertDist[0]			= PosFromGLVert( vId[0] ,0) - origin[0];
			vertDist[1]			= PosFromGLVert( vId[1] ,1) - origin[1];
			
			flt32 distSqr		= vertDist[0] * vertDist[0] + vertDist[1] * vertDist[1];
			flt32 weight		= GetWeightFromDist( distSqr, brushSize );
			
			vert.chunk[0]		= ChunkFromGlVert( vId[0] ,0);
			vert.chunk[1]		= ChunkFromGlVert( vId[1] ,1);
			vert.vert[0]	= vId[0] - vert.chunk[0]* WORLD_TILE_CHUNK_VERT_NUM;
			vert.vert[1]	= vId[1] - vert.chunk[1]* WORLD_TILE_CHUNK_VERT_NUM;;
			
			sInt32 numHeight	= 0;
			flt32 aveHeight		= 0.0f;
			if( GetVertHeight( vId[0]-1, vId[1]-1, tmpHeight ) ) {
				aveHeight		+= tmpHeight;
				numHeight++;
			}
			if( GetVertHeight( vId[0]-1, vId[1]+1, tmpHeight ) ) {
				aveHeight		+= tmpHeight;
				numHeight++;
			}
			if( GetVertHeight( vId[0]+1, vId[1]-1, tmpHeight ) ) {
				aveHeight		+= tmpHeight;
				numHeight++;
			}
			if( GetVertHeight( vId[0]+1, vId[1]+1, tmpHeight ) ) {
				aveHeight		+= tmpHeight;
				numHeight++;
			}
			if( numHeight < 1 )
				continue;

			aveHeight		= aveHeight / numHeight;
			flt32 delta		= ( aveHeight - height ) * weight * deltaScale;
			
			bool isOk		= AddVertDeltaHeight( refHeight, vert.chunk, vert.vert, delta );
			
			sInt32 sameCount = GetSameVert( vertList, vert );
			for( sInt32 j=0; j<sameCount; j++ ) {
				const _TVert& p = vertList[j];
				if( isOk )	{	
					// 同步高度.
					SetVertHeight(  p.chunk, p.vert, refHeight );
				}
				else {
					isOk = AddVertDeltaHeight( refHeight, p.chunk, p.vert, delta );
				}
			}
		}
	}
	UpdateShape();
	
	return true;
}

bool CNdlWorldEditor::PlaneVert( const flt32* beginPos, const flt32* endPos, flt32 flight )
{
	sInt32 beginVert[2], endVert[2], vId[2];
	
	flt32 centerPos[2], len[2] ;
	len[0]			= (endPos[0]-beginPos[0]) * 0.5f;
	len[1]			= (endPos[1]-beginPos[1]) * 0.5f;
	centerPos[0]	=  beginPos[0] + len[0];
	centerPos[1]	=  beginPos[1] + len[1];
	
	flt32 vLenSqr	= len[0]*len[0] + len[1]*len[1];
	if( vLenSqr < (WORLD_VERTSIZE * WORLD_VERTSIZE) )
		return false;
	
	flt32 vLen		= Sqrt( vLenSqr );
	flt32 vHeight	= endPos[2] - beginPos[2];
	
	flt32 vPos[2], vTransPos[2], minPos[2], maxPos[2];
	flt32 radius	= Sqrt( flight*flight + len[0]*len[0] + len[1]*len[1] );

	minPos[0]		= centerPos[0] - radius;
	minPos[1]		= centerPos[1] - radius;
	maxPos[0]		= centerPos[0] + radius;
	maxPos[1]		= centerPos[1] + radius;

	beginVert[0]	= GLVertFromPos( minPos[0] ,0);
	beginVert[1]	= GLVertFromPos( minPos[1] ,1);
	endVert[0]		= GLVertFromPos( maxPos[0] ,0);
	endVert[1]		= GLVertFromPos( maxPos[1] ,1);
	
	flt32 sinA		= -(beginPos[1]-centerPos[1]) / vLen;
	flt32 cosA		=  (beginPos[0]-centerPos[0]) / vLen;
	
	flt32 refHeight	= 0.0f;			
	_TVert vertList[3];
	_TVert vert;
	for( sInt32 y=0; y<=(endVert[1]-beginVert[1]); y++ ) {
		for( sInt32 x=0; x<=(endVert[0]-beginVert[0]); x++ ) {
			vId[0]			= beginVert[0] + x;
			vId[1]			= beginVert[1] + y;

			if(vId[0] < 0 || vId[1] < 0 
				|| vId[0] > (WORLD_TILE_CHUNK_UNIT_NUM*CURRENTTILE->GetRowColumn()[0])*2
				|| vId[1] > (WORLD_TILE_CHUNK_UNIT_NUM*CURRENTTILE->GetRowColumn()[1])*2
				)
			{
				continue;
			}
			if( ( vId[0] % 2 ) != ( vId[1] % 2 ) )
				continue;

			vPos[0]			= PosFromGLVert( vId[0] ,0); 
			vPos[1]			= PosFromGLVert( vId[1] ,1); 
			
			vPos[0]			= vPos[0]-centerPos[0];
			vPos[1]			= vPos[1]-centerPos[1];

			vTransPos[0]	= vPos[0]*cosA - vPos[1]*sinA;
			vTransPos[1]	= vPos[1]*cosA + vPos[0]*sinA;
			
			if( vTransPos[0]>=-vLen && vTransPos[0]<=vLen && vTransPos[1]>=-flight && vTransPos[1]<=flight ) {
				
				flt32 scale			= (vLen-vTransPos[0]) / vLen * 0.5f;
				flt32 height		= beginPos[2] + vHeight * scale;
				
				vert.chunk[0]		= ChunkFromGlVert( vId[0] ,0);
				vert.chunk[1]		= ChunkFromGlVert( vId[1] ,1);
				vert.vert[0]	= vId[0] - vert.chunk[0]* WORLD_TILE_CHUNK_VERT_NUM;
				vert.vert[1]	= vId[1] - vert.chunk[1]* WORLD_TILE_CHUNK_VERT_NUM;;
				
				SetVertHeight(  vert.chunk, vert.vert, height );
				sInt32 sameCount	= GetSameVert( vertList, vert );

				for( sInt32 j=0; j<sameCount; j++ ) {
					const _TVert& p = vertList[j];
					SetVertHeight(  p.chunk, p.vert, height );
				}
			} 
		}
	}
	UpdateShape();
	
	return true;
}

bool CNdlWorldEditor::EqualVert( const flt32* origin, flt32 brushSize, flt32 height )
{
	sInt32 vertCount = ZnFloat2Int( brushSize/WORLD_VERTSIZE ) + 1;

	sInt32 centerVert[2], vId[2];
	flt32 vertDist[2];

	centerVert[0]	= GLVertFromPos( origin[0] ,0);
	centerVert[1]	= GLVertFromPos( origin[1] ,1);

	flt32 refHeight	= 0.0f;			
	_TVert vertList[3];
	_TVert vert;

	for( sInt32 y=-(vertCount); y<vertCount; y++ ) {
		for( sInt32 x=-vertCount; x<vertCount; x++ ) {
			vId[0]			= centerVert[0] + x;
			vId[1]			= centerVert[1] + y;
			// 
			if(vId[0] < 0 || vId[1] < 0 
				|| vId[0] > (WORLD_TILE_CHUNK_UNIT_NUM*CURRENTTILE->GetRowColumn()[0])*2
				|| vId[1] > (WORLD_TILE_CHUNK_UNIT_NUM*CURRENTTILE->GetRowColumn()[1])*2
				)
			{
				continue;
			}
			if( ( vId[0] % 2 ) != ( vId[1] % 2 ) )
				continue;

			vertDist[0]			= PosFromGLVert( vId[0] ,0) - origin[0];
			vertDist[1]			= PosFromGLVert( vId[1] ,1) - origin[1];

			flt32 distSqr		= vertDist[0] * vertDist[0] + vertDist[1] * vertDist[1];
			if( distSqr > brushSize * brushSize )
				continue;

			vert.chunk[0]		= ChunkFromGlVert( vId[0] ,0);
			vert.chunk[1]		= ChunkFromGlVert( vId[1] ,1);
			vert.vert[0]	= vId[0] - vert.chunk[0]* WORLD_TILE_CHUNK_VERT_NUM;
			vert.vert[1]	= vId[1] - vert.chunk[1]* WORLD_TILE_CHUNK_VERT_NUM;;

			SetVertHeight( vert.chunk, vert.vert, height );

			sInt32 sameCount	= GetSameVert( vertList, vert );
			for( sInt32 j=0; j<sameCount; j++ ) {
				const _TVert& p = vertList[j];
				SetVertHeight( p.chunk, p.vert, height );
			}
		}
	}
	UpdateShape();
	
	return true;
}

bool CNdlWorldEditor::GetVertHeight( sInt32 vertIdX, sInt32 vertIdY, flt32& height )
{
	sInt32 vId[2];
	vId[0] = vertIdX;
	vId[1] = vertIdY;

	return GetVertHeight( vId, height );
}

bool CNdlWorldEditor::GetVertHeight( const sInt32* vertId, flt32& height )
{
	if(vertId[0] < 0 || vertId[1] < 0 
		|| vertId[0] > (WORLD_TILE_CHUNK_UNIT_NUM*CURRENTTILE->GetRowColumn()[0])*2
		|| vertId[1] > (WORLD_TILE_CHUNK_UNIT_NUM*CURRENTTILE->GetRowColumn()[1])*2
	)
	{
		return false;
	}
	sInt32  chunk[2],vert[2];
	for( sInt32 i=0; i<2; i++ )	{
		chunk[i]	= ChunkFromGlVert( vertId[i] ,i);
		vert[i]		= vertId[i] - chunk[i]* WORLD_TILE_CHUNK_VERT_NUM;
	}
	
	if( GetChunkVertHeight(  chunk, vert, height ) )
		return true;

	const sInt32 vertStep = WORLD_TILE_CHUNK_UNIT_NUM*2;
	
	if( (vert[0]!=0) && (vert[1]!=0) ) {

	}
	else if( (vert[0]==0)&&(vert[1]!=0) ) {
		vert[0]		= WORLD_TILE_CHUNK_UNIT_NUM*2;
		chunk[0]	= chunk[0]-1;
		if( GetChunkVertHeight(  chunk, vert, height ) ) {
			return true;
		}
	}
	else if( (vert[0]!=0)&&(vert[1]==0) ) {
		vert[1]		= WORLD_TILE_CHUNK_UNIT_NUM*2;
		chunk[1]	= chunk[1]-1;
		if( GetChunkVertHeight(  chunk, vert, height ) ) {
			return true;
		}
	}
	else {
		sInt32 curChunk[2], curVert[2];
		curVert[0]		= WORLD_TILE_CHUNK_UNIT_NUM*2;
		curChunk[0]		= chunk[0]-1;
		curVert[1]		= vert[1];
		curChunk[1]		= chunk[1];
		if( GetChunkVertHeight(  curChunk, curVert, height ) ) {
			return true;
		}
		curVert[1]		= WORLD_TILE_CHUNK_UNIT_NUM*2;
		curChunk[1]		= chunk[1]-1;
		curVert[0]		= vert[0];
		curChunk[0]		= chunk[0];
		if( GetChunkVertHeight( curChunk, curVert, height ) ) {
			return true;
		}

		curVert[0]		= WORLD_TILE_CHUNK_UNIT_NUM*2;
		curChunk[0]		= chunk[0]-1;
		curVert[1]		= WORLD_TILE_CHUNK_UNIT_NUM*2;
		curChunk[1]		= chunk[1]-1;
		if( GetChunkVertHeight( curChunk, curVert, height ) ) {
			return true;
		}
	}	
	
	return false;
}

bool CNdlWorldEditor::GetChunkVertHeight( const sInt32 chunk[2], sInt32 vert[2], flt32& height )
{
	CWorldChunk* worldChunk = m_world->m_worldBuffer->GetChunk(  chunk[0], chunk[1] );
	if( NULL == worldChunk )	
		return false;

	sInt32 axis[2];
	for( sInt32 i=0; i<2; i++ )	{
		axis[i] = vert[i]/2;
	}
	if( vert[0]%2 == 0 ) {
		if( vert[1]%2 == 0 )
			height = worldChunk->m_vertexOut[axis[1]*(WORLD_TILE_CHUNK_UNIT_NUM+1)+axis[0]].height;
		else
			return false;
	}
	else {
		if( vert[1]%2 == 1 )
			height = worldChunk->m_vertexIn[axis[1]*WORLD_TILE_CHUNK_UNIT_NUM+axis[0]].height;
		else
			return false;
	}
	return true;
}

bool CNdlWorldEditor::SetGlVertNormal( const sInt32* vertId, sInt32* normal )
{
	sInt32 chunk[2],vert[2];
	for( sInt32 i=0; i<2; i++ )	{
		chunk[i]	= ChunkFromGlVert( vertId[i] ,i);
		vert[i]		= vertId[i] - chunk[i]* WORLD_TILE_CHUNK_VERT_NUM;
	}
	if( !SetChunkVertNormal(  chunk, vert, normal ) ) {
		//Trace( "0 不能设置法线:tile[%d,%d] chunk[%d,%d] vert[%d,%d] \n",
		//	tile[0], tile[1], chunk[0], chunk[1], vert[0], vert[1] );
	}
	//Trace( "SetGlVertNormal[%d,%d] \n", vertId[0], vertId[1] );
	const sInt32 vertStep = WORLD_TILE_CHUNK_UNIT_NUM*2;

	if( (vert[0]!=0) && (vert[1]!=0) ) {
		
		
	}
	else if( (vert[0]==0)&&(vert[1]!=0) ) {
		vert[0]		= WORLD_TILE_CHUNK_UNIT_NUM*2;
		chunk[0]	= chunk[0]-1;
		if(chunk[0]>=0)
		{
			if(!SetChunkVertNormal(  chunk, vert, normal ) ) {
			}
		}
	}
	else if( (vert[0]!=0)&&(vert[1]==0) ) {
		vert[1]		= WORLD_TILE_CHUNK_UNIT_NUM*2;
		chunk[1]	= chunk[1]-1;
		if(chunk[1] >= 0)
		{
			if(!SetChunkVertNormal( chunk, vert, normal ) ) {
			//Trace( "2 不能设置法线:tile[%d,%d] chunk[%d,%d] vert[%d,%d] \n",
			//	tile[0], tile[1], chunk[0], chunk[1], vert[0], vert[1] );
		}
		}
	}
	else {
		sInt32  curChunk[2], curVert[2];
		curVert[0]		= WORLD_TILE_CHUNK_UNIT_NUM*2;
		curChunk[0]		= chunk[0]-1;
		if( curChunk[0]>=0 ) {
			curVert[1]		= vert[1];
			curChunk[1]		= chunk[1];
			if( !SetChunkVertNormal(  curChunk, curVert, normal ) ) {
				//Trace( "3 不能设置法线:tile[%d,%d] chunk[%d,%d] vert[%d,%d] \n",
				//	curTile[0], curTile[1], curChunk[0], curChunk[1], curVert[0], curVert[1] );
			}
		}
		curVert[1]		= WORLD_TILE_CHUNK_UNIT_NUM*2;
		curChunk[1]		= chunk[1]-1;
		if( curChunk[1]>=0 ) {
			curVert[0]		= vert[0];
			curChunk[0]		= chunk[0];
			if( !SetChunkVertNormal(  curChunk, curVert, normal ) ) {
				//Trace( "4 不能设置法线:tile[%d,%d] chunk[%d,%d] vert[%d,%d] \n",
				//	curTile[0], curTile[1], curChunk[0], curChunk[1], curVert[0], curVert[1] );
			}
		}
				
		curVert[0]		= WORLD_TILE_CHUNK_UNIT_NUM*2;
		curChunk[0]		= chunk[0]-1;
		curVert[1]		= WORLD_TILE_CHUNK_UNIT_NUM*2;
		curChunk[1]		= chunk[1]-1;
		if (curChunk[0] >= 0 && curChunk[1] >= 0)
		{
			if( !SetChunkVertNormal(  curChunk, curVert, normal ) ) {
				//Trace( "5 不能设置法线:tile[%d,%d] chunk[%d,%d] vert[%d,%d] \n",
				//	curTile[0], curTile[1], curChunk[0], curChunk[1], curVert[0], curVert[1] );
			}
		}
	}
	
	return true;
}

bool CNdlWorldEditor::SetChunkVertNormal( const sInt32 chunk[2], sInt32 vert[2], sInt32* normal )
{
	CWorldChunk* worldChunk = m_world->m_worldBuffer->GetChunk( chunk[0], chunk[1] );
	if( NULL == worldChunk )	
		return false;

	//Trace( "tile[%d,%d] chunk[%d,%d] vert[%d,%d] normal[%d,%d,%d] \n"
	//	, tile[0], tile[1], chunk[0], chunk[1], vert[0], vert[1], normal[0], normal[1], normal[2] );
	
	sInt32 axis[2];
	for( sInt32 i=0; i<2; i++ )	{
		axis[i] = vert[i]/2;
	}
	if( vert[0]%2 == 0 ) {
		if( vert[1]%2 == 0 ) {
			sInt32 id = axis[1]*(WORLD_TILE_CHUNK_UNIT_NUM+1)+axis[0];
			worldChunk->m_vertexOut[id].normal[0] = normal[0];
			worldChunk->m_vertexOut[id].normal[1] = normal[1];
			worldChunk->m_vertexOut[id].normal[2] = normal[2];
			
			//Trace( "outVertex[%d] chunk[%d,%d] vert[%d,%d] axis[%d,%d] (%d,%d,%d) \n"
			//	, id, chunk[0], chunk[1], vert[0], vert[1], axis[0], axis[1], worldChunk->m_vertexOut[id].normal[0], worldChunk->m_vertexOut[id].normal[1], worldChunk->m_vertexOut[id].normal[2] );
		}
		else
			return false;
	}
	else {
		if( vert[1]%2 == 1 ) {
			sInt32 id = axis[1]*WORLD_TILE_CHUNK_UNIT_NUM+axis[0];
			worldChunk->m_vertexIn[id].normal[0] = normal[0];
			worldChunk->m_vertexIn[id].normal[1] = normal[1];
			worldChunk->m_vertexIn[id].normal[2] = normal[2];

			//Trace( "inVertex[%d] chunk[%d,%d] vert[%d,%d] axis[%d,%d] (%d,%d,%d) \n"
			//	, id, chunk[0], chunk[1], vert[0], vert[1], axis[0], axis[1], worldChunk->m_vertexIn[id].normal[0], worldChunk->m_vertexIn[id].normal[1], worldChunk->m_vertexIn[id].normal[2] );
		}
		else
			return false;
	}

	return true;
}
 
void CNdlWorldEditor::SetChunkMeshDirty( CWorldChunk* worldChunk )
{
	m_changeMeshChunkList.insert( worldChunk );
	m_changeTileList.insert( worldChunk->m_parentTile );


	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldChunk->m_parentTile);
}

//		    		out vertex
//						v7	
//				   | /	|  \ |
//          	   v5 n6|n7 v6
//           	 / n4 \	|  / n5\
//              v3----- v  -----v4  
//               \ n2/  |  \ n3/
//                 v1 n0|n1 v2
//				   | \  |  / |
//						v0
//
bool CNdlWorldEditor::CalcOutVertNormal( sInt32* vertId )
{
	Vector pt0,pt1,pt2,pt3,pt4,pt5,pt6,pt7;
	Vector nm0,nm1,nm2,nm3,nm4,nm5,nm6,nm7,nm;
	
	pt0 = Vector( 0.0f, 0.0f, 0.0f );
	pt1 = Vector( 0.0f, 0.0f, 0.0f );
	pt2 = Vector( 0.0f, 0.0f, 0.0f );
	pt3 = Vector( 0.0f, 0.0f, 0.0f );
	pt4 = Vector( 0.0f, 0.0f, 0.0f );
	pt5 = Vector( 0.0f, 0.0f, 0.0f );
	pt6 = Vector( 0.0f, 0.0f, 0.0f );
	pt7 = Vector( 0.0f, 0.0f, 0.0f );
	nm	= Vector( 0.0f, 0.0f, 0.0f );

	flt32 height;
	if( !GetVertHeight( vertId, height ) ) {
		return false;
	}

	sInt32 siblingId[2];
	siblingId[0]	= vertId[0];
	siblingId[1]	= vertId[1]-2;
	if( GetVertHeight( siblingId, pt0.z ) ) {
		pt0.x	=  0.0f;
		pt0.y	= -WORLD_UNITSIZE;
		pt0.z	=  pt0.z - height;
	}
	siblingId[0]	= vertId[0]-1;
	siblingId[1]	= vertId[1]-1;
	if( GetVertHeight( siblingId, pt1.z ) ) {
		pt1.x	= -(WORLD_UNITSIZE*0.5f);
		pt1.y	= -(WORLD_UNITSIZE*0.5f);
		pt1.z	=   pt1.z - height;
	}
	siblingId[0]	= vertId[0]+1;
	siblingId[1]	= vertId[1]-1;
	if( GetVertHeight( siblingId, pt2.z ) ) {
		pt2.x	=  (WORLD_UNITSIZE*0.5f);
		pt2.y	= -(WORLD_UNITSIZE*0.5f);
		pt2.z	=  pt2.z - height;
	}
	siblingId[0]	= vertId[0]-2;
	siblingId[1]	= vertId[1];
	if( GetVertHeight( siblingId, pt3.z ) ) {
		pt3.x	= -WORLD_UNITSIZE;
		pt3.y	=  0.0f;
		pt3.z	=  pt3.z - height;
	}
	siblingId[0]	= vertId[0]+2;
	siblingId[1]	= vertId[1];
	if( GetVertHeight( siblingId, pt4.z ) ) {
		pt4.x	=  WORLD_UNITSIZE;
		pt4.y	=  0.0f;
		pt4.z	=  pt4.z - height;
	}
	siblingId[0]	= vertId[0]-1;
	siblingId[1]	= vertId[1]+1;
	if( GetVertHeight( siblingId, pt5.z ) ) {
		pt5.x	= -(WORLD_UNITSIZE*0.5f);
		pt5.y	=  (WORLD_UNITSIZE*0.5f);
		pt5.z	=  pt5.z - height;
	}
	siblingId[0]	= vertId[0]+1;
	siblingId[1]	= vertId[1]+1;
	if( GetVertHeight( siblingId, pt6.z ) ) {
		pt6.x	=  (WORLD_UNITSIZE*0.5f);
		pt6.y	=  (WORLD_UNITSIZE*0.5f);
		pt6.z	=  pt6.z - height;
	}
	siblingId[0]	= vertId[0];
	siblingId[1]	= vertId[1]+2;
	if( GetVertHeight( siblingId, pt7.z ) ) {
		pt7.x	=  0.0f;
		pt7.y	=  WORLD_UNITSIZE;
		pt7.z	=  pt7.z - height;
	}
	nm0 = pt1.cross( pt0 );
	nm1 = pt0.cross( pt2 );
	nm2 = pt3.cross( pt1 );
	nm3 = pt2.cross( pt4 );
	nm4 = pt5.cross( pt3 );
	nm5 = pt4.cross( pt6 );
	nm6 = pt7.cross( pt5 );
	nm7 = pt6.cross( pt7 );
	
	nm	= nm0+nm1+nm2+nm3+nm4+nm5+nm6+nm7;
	nm.normalize();
	
	//Trace( "outVertId[%d][%d] (%8.3f,%8.3f,%8.3f) \n"
	//	, vertId[0], vertId[1], nm.x, nm.y, nm.z );

	sInt32 normal[3];
	normal[0]	= ZnFloat2Int( nm.x*127.0f );
	normal[1]	= ZnFloat2Int( nm.y*127.0f );
	normal[2]	= ZnFloat2Int( nm.z*127.0f );

	SetGlVertNormal( vertId, normal );

	return true;
}

//  in vertex
// v2--------v3
// | \  n3 / |
// |n1  v  n2|
// | /  n0 \ |
// v0--------v1
// 
bool CNdlWorldEditor::CalcInVertNormal( sInt32* vertId )
{
	Vector pt0,pt1,pt2,pt3;
	Vector nm0,nm1,nm2,nm3,nm;
	
	pt0 = Vector( 0.0f, 0.0f, 0.0f );
	pt1 = Vector( 0.0f, 0.0f, 0.0f );
	pt2 = Vector( 0.0f, 0.0f, 0.0f );
	pt3 = Vector( 0.0f, 0.0f, 0.0f );
	nm	= Vector( 0.0f, 0.0f, 0.0f );
	
	flt32 height;
	if( !GetVertHeight( vertId, height ) ) {
		return false;
	}

	sInt32 siblingId[2];
	siblingId[0]	= vertId[0]-1;
	siblingId[1]	= vertId[1]-1;
	if( GetVertHeight( siblingId, pt0.z ) ) {
		pt0.x = -(WORLD_UNITSIZE*0.5f);
		pt0.y = -(WORLD_UNITSIZE*0.5f);
		pt0.z = pt0.z - height;
	}
	siblingId[0]	= vertId[0]+1;
	siblingId[1]	= vertId[1]-1;
	if( GetVertHeight( siblingId, pt1.z ) ) {
		pt1.x =  (WORLD_UNITSIZE*0.5f);
		pt1.y = -(WORLD_UNITSIZE*0.5f);
		pt1.z = pt1.z - height;
	}
	siblingId[0]	= vertId[0]-1;
	siblingId[1]	= vertId[1]+1;
	if( GetVertHeight( siblingId, pt2.z ) ) {
		pt2.x = -(WORLD_UNITSIZE*0.5f);
		pt2.y =  (WORLD_UNITSIZE*0.5f);
		pt2.z = pt2.z - height;
	}
	siblingId[0]	= vertId[0]+1;
	siblingId[1]	= vertId[1]+1;
	if( GetVertHeight( siblingId, pt3.z ) ) {
		pt3.x =  (WORLD_UNITSIZE*0.5f);
		pt3.y =  (WORLD_UNITSIZE*0.5f);
		pt3.z = pt3.z - height;
	}
	nm0 = pt0.cross( pt1 );
	nm1 = pt2.cross( pt0 );
	nm2 = pt1.cross( pt3 );
	nm3 = pt3.cross( pt2 );

	nm = nm0+nm1+nm2+nm3;
	nm.normalize();
	
	//Trace( "inVertId[%d][%d] (%8.3f,%8.3f,%8.3f) \n"
	//	, vertId[0], vertId[1], nm.x, nm.y, nm.z );
	sInt32 normal[3];
	normal[0]	= ZnFloat2Int( nm.x*127.0f );
	normal[1]	= ZnFloat2Int( nm.y*127.0f );
	normal[2]	= ZnFloat2Int( nm.z*127.0f );

	SetGlVertNormal( vertId, normal );
	
	return true;
}


bool CNdlWorldEditor::UpdateNormal( CWorldTile* worldTile )
{
	sInt32 startVert[2], vert[2];

	startVert[0] = 0;
	startVert[1] = 0;
	
	for( sInt32 y=0; y<(WORLD_TILE_CHUNK_UNIT_NUM*2*worldTile->GetRowColumn()[1])+1; y++ ) {
		vert[1]	= startVert[1] + y;
		for( sInt32 x=0; x<(WORLD_TILE_CHUNK_UNIT_NUM*2*worldTile->GetRowColumn()[0])+1; x++ ) {
			vert[0]	= startVert[0] + x;
			if( vert[0]%2==0 && vert[1]%2==0 ) {
				CalcOutVertNormal( vert );
			}
			else if( vert[0]%2==1 && vert[1]%2==1 ) {
				CalcInVertNormal( vert );
			}
		}
	}
	return true;
}

bool CNdlWorldEditor::UpdateTileNormal()
{
	std::set<CWorldTile*>::iterator it = m_changeTileList.begin();
	for( ; it!=m_changeTileList.end(); it++ ) {
		CWorldTile* dirtyTile = *it;
		Assert( NULL != dirtyTile );

		UpdateNormal( dirtyTile );

		CResEditMgr* resMgr = (CResEditMgr*)dirtyTile->GetCResMgr();	
		Assert( NULL != resMgr );
		
		for( int i = 0; i <dirtyTile->GetChunkTotal(); i++ ) {
			CWorldChunk* worldChunk = dirtyTile->m_chunckTable[i];
			resMgr->RefreshChunkShapeNormal( worldChunk->m_shape, worldChunk->m_vertexOut, worldChunk->m_vertexIn );
		}
		CWorldEditDoc::GetActiveMapDoc()->AddTileModify( dirtyTile );
	}
	m_changeTileList.clear();
	return true;
}

bool CNdlWorldEditor::UpdateChunkNormal( CWorldChunk* worldChunk )
{
	sInt32 startVert[2], vert[2];
	
	startVert[0] = worldChunk->m_chunk[0]*(WORLD_TILE_CHUNK_UNIT_NUM*2);
	startVert[1] = worldChunk->m_chunk[1]*(WORLD_TILE_CHUNK_UNIT_NUM*2);

	for( sInt32 y=0; y<(WORLD_TILE_CHUNK_UNIT_NUM*2)+1; y++ ) {
		vert[1]	= startVert[1] + y;
		for( sInt32 x=0; x<(WORLD_TILE_CHUNK_UNIT_NUM*2)+1; x++ ) {
			vert[0]	= startVert[0] + x;
			if( vert[0]%2==0 && vert[1]%2==0 ) {
				CalcOutVertNormal( vert );
			}
			else if( vert[0]%2==1 && vert[1]%2==1 ) {
				CalcInVertNormal( vert );
			}
		}
	}

	return true;
}

bool CNdlWorldEditor::UpdateShape()
{
	//UpdateTileNormal();

	std::set<CWorldChunk*>::iterator it = m_changeMeshChunkList.begin();
	for( ; it!=m_changeMeshChunkList.end(); it++ ) {

		CWorldChunk* worldChunk = *it;
		Assert( NULL != worldChunk );
			
		worldChunk->CalcHeight();
		CResEditMgr* resMgr = (CResEditMgr*)worldChunk->m_parentTile->GetCResMgr();	
		Assert( NULL != resMgr );
		resMgr->RefreshLiquidHeight(worldChunk,worldChunk->m_liquidHeight,worldChunk->m_liquidColor,worldChunk->m_liquidAlphaCoaf);
		
		resMgr->RefreshObjHeight( worldChunk );
		resMgr->RefreshChunkShapeHeight( worldChunk->m_shape, worldChunk->m_vertexOut, worldChunk->m_vertexIn, worldChunk );
		UpdateChunkNormal( worldChunk );
		resMgr->RefreshChunkShapeNormal( worldChunk->m_shape, worldChunk->m_vertexOut, worldChunk->m_vertexIn );
		resMgr->RefreshLineRes( worldChunk, worldChunk->m_shape );

		// 更新四叉树
		flt32 fHeight[2];
		worldChunk->CalculateChunkTotalHeight(resMgr, fHeight);
		worldChunk->m_parentTile->m_tileQuadTree.UpdateQuadTree( worldChunk );
	}
	m_changeMeshChunkList.clear();
	//m_changeTileList.clear();

	return true;
}

void CNdlWorldEditor::Rescale( flt32 scale )
{
	theApp.SetPromptText( _T( "正在刷新高度..." ) );

	CWorldTile* tile = m_world->m_worldBuffer->GetActiveTile();
	Assert( NULL != tile );
	if( tile->m_isLoad ){
			tile->m_height[0] =  swInfinity;
			tile->m_height[1] = -swInfinity;
			for( int i = 0; i < tile->GetChunkTotal(); i++ ) {
				CWorldChunk* chunk = tile->m_chunckTable[i];
				chunk->m_height[0] =  swInfinity;
				chunk->m_height[1] = -swInfinity;
				RescaleChunkHeight(  chunk, scale );
				tile->m_height[0] = ZnMin( tile->m_height[0], chunk->m_height[0] );
				tile->m_height[1] = ZnMax( tile->m_height[1], chunk->m_height[1] );
			}
			tile->SetModify(true);
			CWorldEditDoc::GetActiveMapDoc()->AddTileModify( tile );
	}
	UpdateShape();

	theApp.SetPromptText( _T( "刷新高度完成" ) );

}

bool CNdlWorldEditor::RescaleChunkHeight( CWorldChunk* chunk, flt32 scale )
{
	for( sInt32 j = 0; j < (WORLD_TILE_CHUNK_UNIT_NUM+1)*(WORLD_TILE_CHUNK_UNIT_NUM+1); j++ ) {
		chunk->m_vertexOut[j].height	*= scale;
		chunk->m_height[0] = ZnMin<flt32>( chunk->m_height[0], chunk->m_vertexOut[j].height );
		chunk->m_height[1] = ZnMax<flt32>( chunk->m_height[1], chunk->m_vertexOut[j].height );
	}

	for( sInt32 j = 0; j < WORLD_TILE_CHUNK_UNIT_NUM*WORLD_TILE_CHUNK_UNIT_NUM; j++ ) {
		chunk->m_vertexIn[j].height	*= scale;
		chunk->m_height[0] = ZnMin<flt32>( chunk->m_height[0], chunk->m_vertexIn[j].height );
		chunk->m_height[1] = ZnMax<flt32>( chunk->m_height[1], chunk->m_vertexIn[j].height );
	}
	SetChunkMeshDirty( chunk );

	return true;
}

bool CNdlWorldEditor::GetVertexList( uInt32 vertId, sInt32 halfSize, std::vector<TSelInfo*>* selList )	
{


	
	return true;
}

//bool CNdlWorldEditor::PaintLayer( flt32* pt2, uInt8* brush, uInt32 brushSize, znAppendMode appendMode )
//{
//		
//	return true;
//}
//
void CNdlWorldEditor::GetChunkIndexFromPos( sInt32* chunk, flt32* pos )
{
	for( sInt32 i=0;i<2;i++ ) {
		chunk[i]	= ChunkFromPos( pos[i] );
	}

}


bool CNdlWorldEditor::GetSelWorld( flt32* pt2, CWorldChunk** worldChunk, CResEditMgr** resMgr )
{
	sInt32 chunk[2];
	GetChunkIdFromPos( chunk, pt2 );

	*worldChunk	= NULL;
	*resMgr		= NULL;
	
	CWorldChunk* pickChunk = m_world->m_worldBuffer->GetChunk(  chunk[0], chunk[1] );
	if( NULL == pickChunk ) 
		return false;

	CResEditMgr* pickResMgr = (CResEditMgr*)m_world->m_worldBuffer->GetActiveTile()->GetCResMgr();
	if( NULL == pickResMgr )
		return false;
	
	*worldChunk	= pickChunk;
	*resMgr		= pickResMgr;

	return true;
}

bool CNdlWorldEditor::GetChunkLayerTextureInfo( CWorldChunk* worldChunk, CResEditMgr* resMgr
										, CNdlTextureRes** layer0
										, CNdlTextureRes** layer1
										, CNdlTextureRes** layer2
										, CNdlTextureRes** layer3 )
{
	*layer0 = NULL;
	*layer1	= NULL;
	*layer2	= NULL;
	*layer3	= NULL;
	if( RES_INVALID_ID != worldChunk->m_texture[0] ) {
		*layer0 = (CNdlTextureRes*)resMgr->GetTexture( worldChunk->m_texture[0] );
	}
	if( RES_INVALID_ID != worldChunk->m_texture[1] ) {
		Assert( (NULL!=*layer0) );
		*layer1 = (CNdlTextureRes*)resMgr->GetTexture( worldChunk->m_texture[1] );
	}
	if( RES_INVALID_ID != worldChunk->m_texture[2] ) {
		Assert( (NULL!=*layer0) && (NULL!=*layer1) );
		*layer2 = (CNdlTextureRes*)resMgr->GetTexture( worldChunk->m_texture[2] );
	}
	if( RES_INVALID_ID != worldChunk->m_texture[3] ) {
		Assert( (NULL!=*layer0) && (NULL!=*layer1) && (NULL!=*layer2) );
		*layer3 = (CNdlTextureRes*)resMgr->GetTexture( worldChunk->m_texture[3] );
	}
	return true;
}

bool CNdlWorldEditor::ReplaceChunkTexture( CWorldChunk* worldChunk, CResEditMgr* resMgr, sInt32 layerId, const char* textureName )
{
	if( RES_INVALID_ID == worldChunk->m_texture[layerId] ) 
		return false;
	
	
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( resMgr->m_bindTile);
	return	resMgr->ReplaceChunkTexture(worldChunk,layerId,textureName);
}

bool CNdlWorldEditor::DelChunkLayer( CWorldChunk* worldChunk, CResEditMgr* resMgr, sInt32 layerId )
{
	if( NULL == worldChunk )
		return false;
	if( NULL == resMgr )
		return false;

	if( layerId<0 || layerId >=4 )
		return false;

	sInt32 oldLayerId[4];
	sInt32 oldAlphaId[3];
	TTextureInfo oldTexInfo[4];
	if( layerId==0 ){
		if( RES_INVALID_ID == worldChunk->m_texture[1] ) {
			return false;
		}
	}
	else {
		if( RES_INVALID_ID == worldChunk->m_texture[layerId] ) {
			return false;
		}
	}

	for( sInt32 i=0; i<4; i++ ) {
		oldLayerId[i] = worldChunk->m_texture[i];
		oldTexInfo[i] = worldChunk->m_texInfo[i];
// 		worldChunk->m_texture[i] = RES_INVALID_ID;
		if( i < 3 ) {
			oldAlphaId[i] = worldChunk->m_alpha[i];
// 			worldChunk->m_alpha[i] = RES_INVALID_ID;
		}
	}
	resMgr->ReplaceChunkTexture(worldChunk,layerId,RES_INVALID_ID);
	worldChunk->m_texture[worldChunk->m_layerCount - 1] = RES_INVALID_ID;
	worldChunk->m_alpha[worldChunk->m_layerCount - 2] = RES_INVALID_ID;
	for( sInt32 i=0; i<4; i++ ) {
		if( i<layerId ){
// 			resMgr->ReplaceChunkTexture(worldChunk,i,oldLayerId[i]);
// 			worldChunk->m_texture[i] = oldLayerId[i];
// 			if( i>0 )
// 				worldChunk->m_alpha[i-1] = oldAlphaId[i-1];
		}else if( i>=layerId &&(i<3) ) {
 			worldChunk->m_texture[i] = oldLayerId[i+1];
			worldChunk->m_texInfo[i] = oldTexInfo[i+1];
			if( i>0 ) 
			{
				worldChunk->m_alpha[i-1] = oldAlphaId[i];
			}
		}
	}
	worldChunk->m_layerCount--;
	resMgr->RefreshChunkMask( worldChunk );
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldChunk->m_parentTile );

	return true;
}

bool CNdlWorldEditor::UpChunkLayer( CWorldChunk* worldChunk, CResEditMgr* resMgr, sInt32 layerId )
{
	if( NULL == worldChunk )
		return false;
	if( NULL == resMgr )
		return false;

	if( layerId<0 || layerId >2 )
		return false;

// 	if (0 == layerId && worldChunk->IsExistSpecialLayer())
// 	{
// 		return false;
// 	}
	sInt32 keepId = worldChunk->m_texture[layerId+1];
	if( RES_INVALID_ID == worldChunk->m_texture[layerId] ) {
		return false;
	}
	else {
		if( RES_INVALID_ID == keepId )
			return false;
	}

	TTextureInfo keepInfo = worldChunk->m_texInfo[layerId+1];
	worldChunk->m_texture[layerId+1]	= worldChunk->m_texture[layerId];
	worldChunk->m_texInfo[layerId+1]	= worldChunk->m_texInfo[layerId];
	worldChunk->m_texture[layerId]		= keepId;
	worldChunk->m_texInfo[layerId]		= keepInfo;
	if (layerId > 0)
	{
		sInt32 keepAlphaId = worldChunk->m_alpha[layerId ];
		worldChunk->m_alpha[layerId ]	= worldChunk->m_alpha[layerId - 1];
		worldChunk->m_alpha[layerId - 1]		= keepAlphaId;
	}
	resMgr->RefreshChunkMask( worldChunk );
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldChunk->m_parentTile);	
	
	return true;
}

bool CNdlWorldEditor::DownChunkLayer( CWorldChunk* worldChunk, CResEditMgr* resMgr, sInt32 layerId )
{
	if( NULL == worldChunk )
		return false;
	if( NULL == resMgr )
		return false;

	if( layerId<1 || layerId >3 )
		return false;

// 	if (1 == layerId && worldChunk->IsExistSpecialLayer())
// 	{
// 		return false;
// 	}

	sInt32 keepId = worldChunk->m_texture[layerId-1];
	if( RES_INVALID_ID == worldChunk->m_texture[layerId] ) {
		return false;
	}
	else {
		if( RES_INVALID_ID == keepId )
			return false;
	}

	TTextureInfo keepInfo = worldChunk->m_texInfo[layerId-1];
	worldChunk->m_texture[layerId-1]	= worldChunk->m_texture[layerId];
	worldChunk->m_texInfo[layerId-1]	= worldChunk->m_texInfo[layerId];
	worldChunk->m_texture[layerId]		= keepId;
	worldChunk->m_texInfo[layerId]		= keepInfo;

	if (layerId > 1)
	{
		sInt32 keepAlphaId = worldChunk->m_alpha[layerId - 2];
		worldChunk->m_alpha[layerId-2]	= worldChunk->m_alpha[layerId - 1];
		worldChunk->m_alpha[layerId - 1]		= keepAlphaId;
	}

	resMgr->RefreshChunkMask( worldChunk );
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldChunk->m_parentTile );	
	
	
	return true;
}

void CNdlWorldEditor::ChangeAllShadowColor(short sShadowColor)
{	
	//覆盖所有已经有的阴影
	//只能覆盖自动生成的阴影，手绘阴影不可覆盖

	CWorldTile* worldTile = NULL;
	CResEditMgr* resMgr = NULL;
	if(!GetActiveTileAndMgr(worldTile,resMgr))
		return;

	//显示进度
	LightMapProcessDlg processDlg;	
	processDlg.Create(IDD_LIGHTMAP_PROCESS, 0);
	CRect rect;
	processDlg.GetWindowRect(&rect);
	processDlg.SetWindowPos(0, 500, 500, rect.right - rect.left, rect.bottom - rect.top, 0);
	processDlg.UpdateWindow();
	processDlg.ShowWindow(SW_SHOW);

	const int textlenth= 1000;
	char textOfDlg[textlenth];
	processDlg.m_processOfTile.SetRange(0, worldTile->GetChunkTotal());
	for(int i = 0 ; i < worldTile->GetChunkTotal(); ++i)
	{
		//更新进度条
		processDlg.m_processOfTile.SetPos(i);
		sprintf_s(textOfDlg, textlenth, "%s%d/%d%s", "正在更新第", i + 1, worldTile->GetChunkTotal(),"个阴影");
		processDlg.m_staticTile.SetWindowText(textOfDlg);
		CWorldChunk* worldChunk = worldTile->GetChunk(i);
		//没有则跳过
		if( RES_INVALID_ID == worldChunk->m_shadow ) {
			continue;
		}
		CNdlAlphaRes* shadowRes = resMgr->GetShadow( worldChunk->m_shadow );			
		uAlphaBit* destPtr		= shadowRes->m_maskData;
		uAlphaBit* destBasePtr	= destPtr;
		for( int shadowX = 0 ; shadowX < WORLD_TILE_CHUNK_ATOM_NUM; ++ shadowX)
		{
			for(int shadowY = 0 ; shadowY < WORLD_TILE_CHUNK_ATOM_NUM; ++ shadowY)
			{
				int nIndex = (shadowX)/2;
				destPtr = destBasePtr + shadowY * WORLD_TILE_CHUNK_ATOM_NUM/2 + nIndex;
				int nMod = (shadowX + 1)%2;
				if(*destPtr != 0xff)
				{
					if(sShadowColor == 0xff)
						sShadowColor = 0xee;
					if (0 == nMod)
					{
						*destPtr = (*destPtr&0x0F) | ((char)sShadowColor & 0xF0);	
					}
					else
					{
						*destPtr = (*destPtr&0xF0) | ((char)sShadowColor & 0x0F);	
					}
// 					*destPtr = (char)sShadowColor;
				}
			}
		}
		resMgr->UpdateChunkMask( worldChunk );
	}
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldTile );
	//更新阴影信息
	CNdlAlphaRes::m_sShadowColor = sShadowColor;

}

/*-------------------------------------------------------------
Desc	: 处理chunk接缝处的左右两个像素的阴影值
In		: bFlag_。true，pMe所对应的x坐标应为偶数；false, 奇数
-------------------------------------------------------------*/
void CNdlWorldEditor::ProcessLRNeighbourPixelForShadow(uAlphaBit *pMe_, uAlphaBit *pYou_, bool bFlag_/* = true*/)
{
	ASSERT(pMe_ != NULL && pYou_ != NULL);

	const uAlphaBit invalidValue = 0xff;

	if(bFlag_)
	{
		if((*pMe_ & 0x0f) != (invalidValue & 0x0f))
		{
			if((*pYou_ & 0xf0) != (invalidValue & 0xf0))
				return;

			*pYou_ = (*pYou_ & 0x0f) | (*pMe_ << 4);

// 			*pYou_ = (*pYou_ & 0x0f);
// 			*pMe_ = (*pMe_ & 0xf0) | 0x05;
		}
		else
		{
			if((*pYou_ & 0xf0) != (invalidValue & 0xf0))
			{
				*pMe_ = (*pMe_ & 0xf0) | ((*pYou_ >> 4) & 0x0f);

// 				*pMe_ = (*pMe_ & 0xf0);
// 				*pYou_ = (*pYou_ & 0x0f) | 0x50;
			}
		}
	}
	else
	{
		if((*pMe_ & 0xf0) != (invalidValue & 0xf0))
		{
			if((*pYou_ & 0x0f) != (invalidValue & 0x0f))
				return;

			*pYou_ = (*pYou_ & 0xf0) | ((*pMe_ >> 4) & 0x0f);

// 			*pYou_ = (*pYou_ & 0xf0);
// 			*pMe_ = (*pMe_ & 0x0f) | 0x50;
		}
		else
		{
			if((*pYou_ & 0x0f) != (invalidValue & 0x0f))
			{
				*pMe_ = (*pMe_ & 0x0f) | (*pYou_ << 4);

// 				*pMe_ = (*pMe_ & 0x0f);
// 				*pYou_ = (*pYou_ & 0xf0) & 0x05;
			}
		}
	}
}

/*-------------------------------------------------------------
Desc	: 处理chunk接缝处的上下两个像素的阴影值
-------------------------------------------------------------*/
void CNdlWorldEditor::ProcessUDNeighbourPixelForShadow(uAlphaBit *pMe_, uAlphaBit *pYou_)
{
	ASSERT(pMe_ != NULL && pYou_ != NULL);

	const uAlphaBit invalidValue = 0xff;

	if((*pMe_ & 0x0f) != (invalidValue & 0x0f))
	{
		if((*pYou_ & 0x0f) == (invalidValue & 0x0f))
		{
			*pYou_ = (*pYou_ & 0xf0) | (*pMe_ & 0x0f);
		}
	}
	else
	{
		if((*pYou_ & 0x0f) != (invalidValue & 0x0f))
		{
			*pMe_ = (*pMe_ & 0xf0) | (*pYou_ & 0x0f);
		}
	}

	if((*pMe_ & 0xf0) != (invalidValue & 0xf0))
	{
		if((*pYou_ & 0xf0) == (invalidValue & 0xf0))
		{
			*pYou_ = (*pYou_ & 0x0f) | (*pMe_ & 0xf0);
		}
	}
	else
	{
		if((*pYou_ & 0xf0) != (invalidValue & 0xf0))
		{
			*pMe_ = (*pMe_ & 0x0f) | (*pYou_ & 0xf0);
		}
	}

}

/*-------------------------------------------------------------
Desc	: 处理chunk邻接处阴影接缝的问题。
-------------------------------------------------------------*/
void CNdlWorldEditor::ProcessChunkBoundaryForShadow(CResEditMgr *pResMgr_, CWorldTile *pTile_, CWorldChunk *pChunk_)
{
	//这个类仅仅是为了导出两个CWorldChunk的数据m_chunk。
	class CWorldChunk_M: public CWorldChunk
	{
	public:
		void GetChunkPos(sInt32 &_x, sInt32 &_y)
		{
			_x = m_chunk[0];
			_y = m_chunk[1];
		}
	};

	ASSERT(pResMgr_ != NULL && pTile_ != NULL && pChunk_ != NULL);

	sInt32 myPosX;
	sInt32 myPosY;
	((CWorldChunk_M *)pChunk_)->GetChunkPos(myPosX, myPosY);

	CWorldChunk *pHisChunk = NULL;
	const int xSize = WORLD_TILE_CHUNK_ATOM_NUM / 2;	//width of a chunk
	const int ySize = WORLD_TILE_CHUNK_ATOM_NUM;	//height of a chunk
	CNdlAlphaRes* pMyShadow = pResMgr_->GetShadow(pChunk_->m_shadow);	
	if(NULL == pMyShadow)
		return;
	uAlphaBit *pMyShadowDataHead = pMyShadow->m_maskData;
	ASSERT(pMyShadowDataHead != NULL);

	if(myPosX > 0)
	{//left neighbour chunk
		
		pHisChunk = pTile_->GetChunk(myPosX - 1, myPosY);
		if(pHisChunk)
		{
			CNdlAlphaRes* pHisShadow = pResMgr_->GetShadow(pHisChunk->m_shadow);
			if(pHisShadow != NULL)
			{
				uAlphaBit *pHisShadowDataHead = pHisShadow->m_maskData;
				ASSERT(pHisShadowDataHead != NULL);

				//point to the head of my most left shadow data
				uAlphaBit *pMyData = pMyShadowDataHead;

				//point to the head of his most right shadow data
				uAlphaBit *pHisData = pHisShadowDataHead + xSize - 1;

				//now, to process my left boundary
				for(int y=0; y<ySize; ++y)
				{
					ProcessLRNeighbourPixelForShadow(pMyData, pHisData, true);

					//point to the next pixel
					pMyData += xSize;
					pHisData += xSize;
				}
			}
		}
	}

	{//right neighbour chunk

		pHisChunk = pTile_->GetChunk(myPosX + 1, myPosY);
		if(pHisChunk)
		{
			CNdlAlphaRes* pHisShadow = pResMgr_->GetShadow(pHisChunk->m_shadow);
			if(pHisShadow != NULL)
			{
				uAlphaBit *pHisShadowDataHead = pHisShadow->m_maskData;
				ASSERT(pHisShadowDataHead != NULL);

				//point to the head of my most right shadow data
				uAlphaBit *pMyData = pMyShadowDataHead + xSize - 1;

				//point to the head of his most left shadow data
				uAlphaBit *pHisData = pHisShadowDataHead;

				//now, to process my right boundary
				for(int y=0; y<ySize; ++y)
				{
					ProcessLRNeighbourPixelForShadow(pMyData, pHisData, false);

					//point to the next pixel
					pMyData += xSize;
					pHisData += xSize;
				}
			}
		}
	}

	{//up neighbour chunk
		
		pHisChunk = pTile_->GetChunk(myPosX, myPosY + 1);
		if(pHisChunk)
		{
			CNdlAlphaRes* pHisShadow = pResMgr_->GetShadow(pHisChunk->m_shadow);
			if(pHisShadow != NULL)
			{
				uAlphaBit *pHisShadowDataHead = pHisShadow->m_maskData;
				ASSERT(pHisShadowDataHead != NULL);

				//point to the head of my most up shadow data
				uAlphaBit *pMyData = pMyShadowDataHead + (ySize - 1) * xSize;

				//point to the head of his most down shadow data
				uAlphaBit *pHisData = pHisShadowDataHead;

				//now, to process my up boundary
				for(int x=0; x<xSize; ++x)
				{
					ProcessUDNeighbourPixelForShadow(pMyData, pHisData);
					ASSERT(*pMyData == *pHisData);

					//point to the next 2 pixel
					++pMyData;
					++pHisData;
				}
			}
		}
	}

	if(myPosY > 0)
	{//down neighbour chunk

		pHisChunk = pTile_->GetChunk(myPosX, myPosY - 1);
		if(pHisChunk)
		{
			CNdlAlphaRes* pHisShadow = pResMgr_->GetShadow(pHisChunk->m_shadow);
			if(pHisShadow != NULL)
			{
				uAlphaBit *pHisShadowDataHead = pHisShadow->m_maskData;
				ASSERT(pHisShadowDataHead != NULL);

				//point to the head of my most down shadow data
				uAlphaBit *pMyData = pMyShadowDataHead;

				//point to the head of his most up shadow data
				uAlphaBit *pHisData = pHisShadowDataHead + (ySize - 1) * xSize;

				//now, to process my down boundary
				for(int x=0; x<xSize; ++x)
				{
					ProcessUDNeighbourPixelForShadow(pMyData, pHisData);
					ASSERT(*pMyData == *pHisData);

					//point to the next 2 pixel
					++pMyData;
					++pHisData;
				}
			}
		}
	}
	
}

bool CNdlWorldEditor::GenerateLightMap()
{

	const unsigned int uiLightMapSize = WORLD_TILE_CHUNK_ATOM_NUM;
	const int size		= WORLD_TILE_CHUNK_ATOM_NUM;
	CWorldTile* worldTile = NULL;
	CResEditMgr* resMgr = NULL;
	if(!GetActiveTileAndMgr(worldTile,resMgr))
		return false;

	//显示进度
	LightMapProcessDlg processDlg;	
	processDlg.Create(IDD_LIGHTMAP_PROCESS, 0);
	CRect rect;
	processDlg.GetWindowRect(&rect);
	processDlg.SetWindowPos(0, 500, 500, rect.right - rect.left, rect.bottom - rect.top, 0);
	processDlg.UpdateWindow();
	processDlg.ShowWindow(SW_SHOW);
	//备份相机数据
	D3DXVECTOR3 vEye = GetMe3dConfig()->GetCamera()->GetEyePt();
	D3DXVECTOR3 vLookAt = GetMe3dConfig()->GetCamera()->GetLookatPt();

	const int textlenth= 1000;
	char textOfDlg[textlenth];
	//取出光方向
	RendererDx* pRender =  (RendererDx*)GetEngine()->GetRenderer();
	D3DXVECTOR3 lightDir = pRender->GetLightDir(LIGHT_INDEX_TERRAIN);
	D3DXVec3Normalize(&lightDir, &lightDir);

	//更新billboard,使每个billboard对着摄像机
	processDlg.m_processOfTile.SetRange(0, worldTile->GetChunkTotal());
	for(int i = 0 ; i < worldTile->GetChunkTotal(); ++i)
	{
		CWorldChunk* worldChunk = worldTile->GetChunk(i);
		std::vector<sInt32> staticModelListIDs = worldChunk->GetStaticModelList();
		//更新进度条
		processDlg.m_processOfTile.SetPos(i);
		sprintf_s(textOfDlg, textlenth, "%s%d/%d%s", "更新", i + 1, worldTile->GetChunkTotal(),"个Chunk");
		processDlg.m_staticTile.SetWindowText(textOfDlg);

		processDlg.m_processOfGenerate.SetRange(0, staticModelListIDs.size());
		for(int nidx = 0 ; nidx < staticModelListIDs.size(); ++nidx)
		{			
			//更新进度条			
			processDlg.m_processOfGenerate.SetPos(nidx);
			sprintf_s(textOfDlg, textlenth, "%s%d/%d%s", "更新第", nidx + 1, staticModelListIDs.size(),"个模型的billboard");
			processDlg.m_staticChunk.SetWindowText(textOfDlg);

			TObjectInfo* pObject = resMgr->GetStaticModel(staticModelListIDs[nidx]);
			//计算光位置						
			D3DXVECTOR3 vModelPos = *(D3DXVECTOR3*)&pObject->model->GetPosition();
			D3DXVECTOR3 vLightPos = vModelPos - lightDir * 1000.f;										
			GetMe3dConfig()->GetCamera()->SetViewParams(vLightPos, vModelPos, D3DXVECTOR3(0,0,1));
			//update billboard
 			pObject->model->UpdateBillboardBBox();
			
		}
	}
	
	processDlg.m_processOfTile.SetRange(0, worldTile->GetChunkTotal());
	for(int i = 0 ; i < worldTile->GetChunkTotal(); ++i)
	{
		//更新进度条
		processDlg.m_processOfTile.SetPos(i);
		sprintf_s(textOfDlg, textlenth, "%s%d/%d%s", "正在清除第", i + 1, worldTile->GetChunkTotal(),"个阴影");
		processDlg.m_staticTile.SetWindowText(textOfDlg);
		CWorldChunk* worldChunk = worldTile->GetChunk(i);
		float fHeight[2];
		worldChunk->CalculateChunkTotalHeightForEditor(resMgr, fHeight);
		//清理shadow
		if( RES_INVALID_ID == worldChunk->m_shadow ) {
			worldChunk->m_shadow = resMgr->PushShadow( NULL );
		}
		CNdlAlphaRes* shadowRes = resMgr->GetShadow( worldChunk->m_shadow );			
		uAlphaBit* destPtr		= shadowRes->m_maskData;
		memset(destPtr, 0xff, sizeof(uAlphaBit) * size * size/2 );
	}
	WORD* index = resMgr->GetStaticIndexStream(CResEditMgr::LOD0);
	int nFaceCount = CResEditMgr::m_LODFaceCount[CResEditMgr::LOD0];
	D3DXVECTOR3 p[3];
	D3DXVECTOR3 normal[3];
	D3DXVECTOR2 uv[3];
	//更新进度条
	processDlg.m_processOfTile.SetRange(0, worldTile->GetChunkTotal());
	for( int nChunkY = 0; nChunkY < worldTile->GetRowColumn()[1]; nChunkY++ ) {
		for(int nChunkX = 0 ; nChunkX < worldTile->GetRowColumn()[0]; nChunkX++){

			CWorldChunk* chunkToBeTest = worldTile->GetChunk(nChunkX, nChunkY);
			std::vector<sInt32> staticModelListIDs = chunkToBeTest->GetStaticModelList();
			if(staticModelListIDs.size() == 0)continue;
			//取chunk最大高度，取以改值递增的chunk进行检测
			float fDirTrick;
			fDirTrick = (chunkToBeTest->GetTotalHeight()[1] - chunkToBeTest->GetHeight()[1])/ 9.0f;			
			float fDirX = fDirTrick * lightDir.x;
			int nSignX = (fDirX == abs(fDirX)) ? 1 : -1;
			int nDirX = ceil(abs(fDirTrick * lightDir.x));
			float fDirY = fDirTrick * lightDir.y;
			int nSignY = (fDirY == abs(fDirY)) ? 1 : -1;
			int nDirY = ceil(abs(fDirTrick * lightDir.y));
			
			for(int dirx = 0 ; dirx <= nDirX; ++dirx)
			{
				for(int diry = 0 ; diry <=nDirY; ++diry)
				{	
					CWorldChunk* worldChunk = worldTile->GetChunk(nChunkX + dirx * nSignX, nChunkY + diry * nSignY);
					if( NULL != worldChunk ) {					
						//设置进度
						int nChunkIndex = nChunkY * worldTile->GetRowColumn()[1] + nChunkX + 1;
						sprintf_s(textOfDlg, textlenth, "%s%d/%d%s", "正在处理第", nChunkIndex, worldTile->GetChunkTotal(),"个Chunk");
						processDlg.m_processOfTile.SetPos(nChunkIndex);
						processDlg.m_staticTile.SetWindowText(textOfDlg);

						if( worldChunk->GetLiquidId() != RES_INVALID_ID )//水
						{
							//检测高度差，如果过大则不计算阴影
							float fMaxHeight = worldChunk->GetHeight()[1];
							static float s_fMaxDeltaHeight = 90.f;
							if( abs( fMaxHeight - chunkToBeTest->GetTotalHeight()[1] ) >= s_fMaxDeltaHeight )
								continue;
						}

						CNdlAlphaRes* shadowRes = resMgr->GetShadow( worldChunk->m_shadow );			
						uAlphaBit* destPtr		= shadowRes->m_maskData;
						uAlphaBit* destBasePtr	= destPtr;

						//取出包含定点信息的shape
						CNdlShapeRes* pShapeRes = resMgr->Shape(worldChunk->GetShape());										

						//设置进度
						processDlg.m_processOfGenerate.SetRange(0, nFaceCount);
						for( int i = 0; i < nFaceCount; i++ )
						{
							//设置每个chunk的生成进度
							processDlg.m_processOfGenerate.SetPos(i);
							sprintf_s(textOfDlg, textlenth, "%s%d/%d%s", "正在处理第", i + 1, nFaceCount, "个面");
							processDlg.m_staticChunk.SetWindowText(textOfDlg);

							FTerrainVertexSpecial* pDatas = 0;
							if (SUCCEEDED(pShapeRes->m_pVB->Lock(0, CHUNK_VERTEX_NUMBER * sizeof(FTerrainVertexSpecial), (void**)&pDatas, 0)))
							{
								p[0] = pDatas[index[i*3]].p;
								p[1] = pDatas[index[i*3+1]].p;
								p[2] = pDatas[index[i*3+2]].p;
								normal[0]= pDatas[index[i*3]].n;
								normal[1]= pDatas[index[i*3+1]].n;
								normal[2]= pDatas[index[i*3+2]].n;
								uv[0] = D3DXVECTOR2(pDatas[index[i*3]].uvShadow.u,pDatas[index[i*3]].uvShadow.v);
								uv[1] = D3DXVECTOR2(pDatas[index[i*3+1]].uvShadow.u,pDatas[index[i*3+1]].uvShadow.v);
								uv[2] = D3DXVECTOR2(pDatas[index[i*3+2]].uvShadow.u,pDatas[index[i*3+2]].uvShadow.v);
								pShapeRes->m_pVB->Unlock();
							}

							// 计算UV坐标的包围盒
							D3DXVECTOR2 uvmin(FLT_MAX, FLT_MAX);
							D3DXVECTOR2 uvmax(FLT_MIN, FLT_MIN);
							if ( uv[0].x> uvmax.x ) uvmax.x = uv[0].x;
							if ( uv[0].x< uvmin.x ) uvmin.x = uv[0].x;
							if ( uv[1].x> uvmax.x ) uvmax.x = uv[1].x;
							if ( uv[1].x< uvmin.x ) uvmin.x = uv[1].x;
							if ( uv[2].x> uvmax.x ) uvmax.x = uv[2].x;
							if ( uv[2].x< uvmin.x ) uvmin.x = uv[2].x;

							if ( uv[0].y> uvmax.y ) uvmax.y = uv[0].y;
							if ( uv[0].y< uvmin.y ) uvmin.y = uv[0].y;
							if ( uv[1].y> uvmax.y ) uvmax.y = uv[1].y;
							if ( uv[1].y< uvmin.y ) uvmin.y = uv[1].y;
							if ( uv[2].y> uvmax.y ) uvmax.y = uv[2].y;
							if ( uv[2].y< uvmin.y ) uvmin.y = uv[2].y;

							// 计算其对应对光照图的范围
							int maxW = (int)( uvmax.x * uiLightMapSize );
							int minW = (int)( uvmin.x * uiLightMapSize );
							int maxH = (int)( uvmax.y * uiLightMapSize);
							int minH = (int)( uvmin.y * uiLightMapSize);

							if ( maxW >= uiLightMapSize ) maxW = uiLightMapSize  - 1;
							if ( maxH >= uiLightMapSize) maxH = uiLightMapSize - 1;
							if ( minW < 0 ) minW = 0;
							if ( minH < 0 ) minH = 0;

							// 计算每个象素的光照值
							float fInvWidth = 1.f / (float)uiLightMapSize;
							float fInvHeight = 1.f / (float)uiLightMapSize;

							for (int h = minH; h <= maxH; ++h)
							{
								for (int w = minW; w <= maxW; ++w)
								{										
									int nIndex = (w)/2;
									destPtr = destBasePtr+h*size/2+nIndex;
									int nMod = (w+1)%2;
// 									destPtr = destBasePtr + h * size + w;	
									if ((0 == nMod )&& ((*destPtr&0xF0) == (CNdlAlphaRes::m_sShadowColor&0xF0)))
									{
										continue;
									}
									if ((1 == nMod )&& ((*destPtr&0x0F) == (CNdlAlphaRes::m_sShadowColor&0x0F)))
									{
										continue;
									}
// 									if(*destPtr == CNdlAlphaRes::m_sShadowColor)
// 										continue;

									D3DXVECTOR2 tuv;
									tuv.x = ((float)w + 0.5f) * fInvWidth;
									tuv.y = ((float)h + 0.5f) * fInvHeight;

									float u, v;
									if ( !IsPointInTriangle( uv[0], uv[1], uv[2], tuv, u, v ) )
										continue;

									// 得到其在世界中的位置
									D3DXVECTOR3 desPos;
									desPos = p[0] + v * (p[1]-p[0]) + u * (p[2]-p[0]);

									// 平滑normal
									D3DXVECTOR3 n;
									n = (1 - v - u ) * normal[0] + v * normal[1] + u * normal[2];
									desPos = desPos + n * 0.001f;
									D3DXVec3Normalize(&n, &n);
									D3DXVECTOR3 lightPos = - lightDir * 1000.f;
									for(int nidx = 0 ; nidx < staticModelListIDs.size(); ++nidx)
									{
										TObjectInfo* pObject = resMgr->GetStaticModel(staticModelListIDs[nidx]);										
										if(MexAnimCtrl::IntersectQuick(pObject->model, &desPos, &lightPos))
										{
											if (0 == nMod)
											{
												*destPtr = (*destPtr&0x0F) | (CNdlAlphaRes::m_sShadowColor & 0xF0);	
											}
											else
											{
												*destPtr = (*destPtr&0xF0) | (CNdlAlphaRes::m_sShadowColor & 0x0F);	
											}
// 												*destPtr = CNdlAlphaRes::m_sShadowColor;
												break;
										}
										
									}				


								}//for (int w = minW; w <= maxW; ++w)
							}//for (int h = minH; h <= maxH; ++h)

						}
						//BlurLightMap(shadowRes);

						//added by zilong. 2011-02-10. --------------------------
						//增加chunk邻接处的阴影处理，防止接缝现象的产生
						ProcessChunkBoundaryForShadow(resMgr, worldTile, worldChunk);
						//added by zilong. end. ---------------------------------
					}

				}
			}
			

		}
		
	}

	// added, jiayi, [2009.4.20],更新bbox,主要针对billboard
	for(int i = 0 ; i < worldTile->GetChunkTotal(); ++i)
	{
		CWorldChunk* worldChunk = worldTile->GetChunk(i);
		std::vector<sInt32> staticModelListIDs = worldChunk->GetStaticModelList();
		//更新进度条
		processDlg.m_processOfTile.SetPos(i);
		sprintf_s(textOfDlg, textlenth, "%s%d/%d%s", "更新", i + 1, worldTile->GetChunkTotal(),"个Chunk");
		processDlg.m_staticTile.SetWindowText(textOfDlg);

		for(int nidx = 0 ; nidx < staticModelListIDs.size(); ++nidx)
		{			
			//更新进度条
			processDlg.m_processOfGenerate.SetPos(nidx);
			sprintf_s(textOfDlg, textlenth, "%s%d/%d%s", "清除", nidx + 1, staticModelListIDs.size(),"个模型flag");
			processDlg.m_staticChunk.SetWindowText(textOfDlg);

			TObjectInfo* pObject = resMgr->GetStaticModel(staticModelListIDs[nidx]);	
			pObject->model->SetUpdatedBillboardBBox( false );
		}
	}

	for(int i = 0 ; i < worldTile->GetChunkTotal(); ++i)
	{
		//更新进度条
		processDlg.m_processOfTile.SetPos(i);
		sprintf_s(textOfDlg, textlenth, "%s%d/%d%s", "更新", i + 1, worldTile->GetChunkTotal(),"个Chunk");
		processDlg.m_staticTile.SetWindowText(textOfDlg);
		CWorldChunk* worldChunk = worldTile->GetChunk(i);
		
		resMgr->UpdateChunkMask( worldChunk );
	}
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldTile );
	GetMe3dConfig()->GetCamera()->SetViewParams(vEye, vLookAt, D3DXVECTOR3(0,0,1));

	return true;
}
void CNdlWorldEditor::BlurLightMap(CNdlAlphaRes* shadowRes)
{
	struct PIXELKERNEL
	{
		int x;
		int y;
	};
	const unsigned int uiLightMapSize = WORLD_TILE_CHUNK_ATOM_NUM;
	const int size		= WORLD_TILE_CHUNK_ATOM_NUM;

	CWorldTile* worldTile = NULL;

	uAlphaBit* destPtr		= shadowRes->m_maskData;
	uAlphaBit* destBasePtr		= destPtr;

	static const PIXELKERNEL pixelkernel[9]=
	{
		{-1,-1}, 
		{-1, 1}, 
		{1, -1},
		{1, 1}, 
		{0, 0},	
		{0,  1},
		{0, -1}, 
		{1,  0},
		{-1, 0},
	};
	static const float weights[9] = 
	{
		0.05f, 
		0.05f,
		0.05f,
		0.05f,
		0.4f,
		0.1f,
		0.1f,
		0.1f,
		0.1f,
	};
	int h, w;
	for (h = 0; h < uiLightMapSize; ++h)
		for (w = 0; w < uiLightMapSize; ++w)
		{
			int nIndex = (w)/2;
			destPtr = destBasePtr+h*size/2+nIndex;
			int nMod = (w+1)%2;
// 			destPtr = destBasePtr + h * size + w;	
			//stLumel& lumel = GetLumel( w, h );
			if ((0 == nMod )&& ((*destPtr&0xF0) == (CNdlAlphaRes::m_sShadowColor&0xF0))
				|| (1 == nMod )&& ((*destPtr&0x0F) == (CNdlAlphaRes::m_sShadowColor&0x0F)))
// 			if ( *destPtr == CNdlAlphaRes::m_sShadowColor )
			{
				uAlphaBit color = 0xff;
				for (int n = 0; n < 9; ++n)
				{
					int nh = h + pixelkernel[n].y;
					int nw = w + pixelkernel[n].x;		
					if ( nh < 0 ) nh = 0;
					if ( nw < 0 ) nw = 0;
					if ( nh >= uiLightMapSize ) nh = uiLightMapSize - 1;
					if ( nw >= uiLightMapSize )  nw = uiLightMapSize - 1;

					color -= *(destBasePtr + nh * size + nw) * weights[n];
				}
				if (0 == nMod)
				{
					*destPtr = (*destPtr&0x0F) | (color & 0xF0);	
				}
				else
				{
					*destPtr = (*destPtr&0xF0) | (color & 0x0F);	
				}
// 				*destPtr = color;
			}
		}
}
void CNdlWorldEditor::BlurLightMapGauss(CNdlAlphaRes* shadowRes)
{
	const int gauss_width = 5;
	const unsigned int uiLightMapSize = WORLD_TILE_CHUNK_ATOM_NUM;
	const int size		= WORLD_TILE_CHUNK_ATOM_NUM;

	CWorldTile* worldTile = NULL;

	uAlphaBit* outDestPtr		= shadowRes->m_maskData;
	uAlphaBit* destBasePtr		= outDestPtr;

	//begin blur
	int gauss_fact[gauss_width]={1,2,3,2,1};
	int gauss_sum=16;

	int i,j,k;
	for( i = 0; i < uiLightMapSize; i++ )
	{
		for( j = 0; j < uiLightMapSize; j++ )
		{
			outDestPtr = destBasePtr + j * size + i;
			if ( *outDestPtr != CNdlAlphaRes::m_sShadowColor )
				continue;

			uAlphaBit oColor = 0x00;
			int nSum = 0;
			for( k = 0; k < gauss_width; k++ )
			{
				uAlphaBit* destPtr = destBasePtr + j * size + i -((gauss_width - 1)>>1) + k;
				//stLumel& oLumel = GetLumel(i-((gauss_width-1)>>1)+k, j);
				//if( *destPtr == m_sShadowColor )
				{
					oColor += *destPtr * (float)gauss_fact[k];
					nSum += gauss_fact[k];
				}
			}
			if( nSum )
			{
				LightMapPixel lmp;
				lmp.ucBlurColor = 255 - oColor / (float)nSum;
				lmp.ucColor = *outDestPtr;
				m_mapLightMapPixel[outDestPtr] = lmp;
			}
		} 
	}
	for( i = 0; i < uiLightMapSize; i++ ){
		for( j = 0; j < uiLightMapSize; j++ )
		{
			outDestPtr = destBasePtr + j * size + i;
			if ( *outDestPtr != CNdlAlphaRes::m_sShadowColor )
				continue;
			uAlphaBit oColor = 0x00;
			int nSum = 0;
			for( k = 0; k < gauss_width; k++ )
			{
				uAlphaBit* destPtr = destBasePtr + (j-((gauss_width-1)>>1)+k) * size + i;						
				//if( *destPtr == m_sShadowColor )
				{
					oColor += m_mapLightMapPixel[destPtr].ucBlurColor * (float)gauss_fact[k];
					nSum += gauss_fact[k];
				}
			}
			if( nSum )
				*outDestPtr = 255 - oColor / (float)nSum;
		} 
	}
	
}

bool CNdlWorldEditor::PaintShadow( flt32* pt2, uInt8* brush, uInt32 brushSize, bool isAddShadow, uInt8 alpha )
{
	flt32 minPt[2];
	flt32 maxPt[2];
	TProjResult projResult;
	
	flt32 radius = (brushSize>>1)*WORLD_ATOMSIZE;
	minPt[0] = ZnMax<flt32> (pt2[0]-radius,0.f);
	minPt[1] = ZnMax<flt32> (pt2[1]-radius,0.f);
	maxPt[0] = ZnMin<flt32> (minPt[0]+(brushSize-1)*WORLD_ATOMSIZE,CURRENTTILE->GetRowColumn()[0]*WORLD_CHUNKSIZE - WORLD_ATOMSIZE*0.5);
	maxPt[1] = ZnMin<flt32> (minPt[1]+(brushSize-1)*WORLD_ATOMSIZE,CURRENTTILE->GetRowColumn()[1]*WORLD_CHUNKSIZE - WORLD_ATOMSIZE*0.5);

	ProjectWorld( minPt, maxPt, projResult,WORLD_ATOMSIZE,WORLD_TILE_CHUNK_ATOM_NUM );	
	BeginEdgeAlphaTrick( projResult, brush, brushSize);
	for( uInt32 i=0; i< projResult.resultList.size(); i++ ) {
		_TProjRect* projRect = projResult.resultList[i];
		CWorldChunk* worldChunk = m_world->m_worldBuffer->GetChunk(  projRect->chunk[0], projRect->chunk[1] );
		if( NULL != worldChunk ) {
			CResEditMgr* resMgr = (CResEditMgr*)m_world->m_worldBuffer->GetResMgr(  );
			Assert( NULL != resMgr );
			uInt32 size[2];
			size[0]	= projRect->brushMax[0]-projRect->brushMin[0]+1;
			size[1]	= projRect->brushMax[1]-projRect->brushMin[1]+1;
			if( RES_INVALID_ID == worldChunk->m_shadow ) {
				worldChunk->m_shadow = resMgr->PushShadow( NULL );
			}
			CNdlAlphaRes* shadowRes = resMgr->GetShadow( worldChunk->m_shadow );			
			if( FillShadowData( shadowRes, projRect->atomMin, brush, projRect->brushMin, size, brushSize, isAddShadow ,alpha) ) {
				resMgr->UpdateChunkMask( worldChunk );
				CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldChunk->m_parentTile);
			}
		}
	}
	EndEdgeAlphaTrick(brush, brushSize);

	//Trace( "Paint shadow---------------------------------------------- \n" );

	return true;
}

bool CNdlWorldEditor::FillRoadData( CNdlAlphaRes* res, uInt32* originDest, uInt8* brush, uInt32* originSrc, uInt32* sizeSrc, uInt32 brushSize, bool isAddShadow , uInt8 alpha)
{
	Assert( NULL != res );

	const int size		= WORLD_TILE_CHUNK_ATOM_NUM;
	uAlphaBit* destPtr		= res->m_maskData;
	uAlphaBit* destBasePtr	= destPtr;

	for( uInt32 y=0; y<sizeSrc[1]; y++ ) {
		for( uInt32 x=0; x<sizeSrc[0]; x++ ) {
// 			uInt32 off = (originSrc[1]+y)*brushSize+originSrc[0]+x;
			int nIndex = (originDest[0] + x)/2;
			destPtr = destBasePtr+(originDest[1]+y)*size/2+nIndex;
			int nMod = (originDest[0] + x + 1)%2;
			if( isAddShadow )
			{
				if (alpha < 0x88)
				{
					if (0 == nMod)
					{
						*destPtr = (*destPtr&0x0F) | (0x80);	
					}
					else
					{
						*destPtr = (*destPtr&0xF0) | (0x08);	
					}
				}
				else
				{
					if (0 == nMod)
					{
						*destPtr &= 0x08;
					}
					else
					{
						*destPtr &= 0x80;
					}
				}
			}
			else 
			{
				if (0 == nMod)
				{
					*destPtr |= 0xF0;
				}
				else
				{
					*destPtr |= 0x0F;
				}
			}
		}
	}
	return true;
}

bool CNdlWorldEditor::PaintRoad( flt32* pt2, uInt8* brush, uInt32 brushSize, bool isAddRoad, uInt8 alpha )
{
	flt32 minPt[2];
	flt32 maxPt[2];
	TProjResult projResult;

	flt32 radius = (brushSize>>1)*WORLD_ATOMSIZE;
	minPt[0] = ZnMax<flt32> (pt2[0]-radius,0.f);
	minPt[1] = ZnMax<flt32> (pt2[1]-radius,0.f);
	maxPt[0] = ZnMin<flt32> (minPt[0]+(brushSize-1)*WORLD_ATOMSIZE,CURRENTTILE->GetRowColumn()[0]*WORLD_CHUNKSIZE - WORLD_ATOMSIZE*0.5);
	maxPt[1] = ZnMin<flt32> (minPt[1]+(brushSize-1)*WORLD_ATOMSIZE,CURRENTTILE->GetRowColumn()[1]*WORLD_CHUNKSIZE - WORLD_ATOMSIZE*0.5);

	ProjectWorld( minPt, maxPt, projResult,WORLD_ATOMSIZE,WORLD_TILE_CHUNK_ATOM_NUM );	
	BeginEdgeAlphaTrick( projResult, brush, brushSize);
	for( uInt32 i=0; i< projResult.resultList.size(); i++ ) {
		_TProjRect* projRect = projResult.resultList[i];
		CWorldChunk* worldChunk = m_world->m_worldBuffer->GetChunk(  projRect->chunk[0], projRect->chunk[1] );
		if( NULL != worldChunk ) {
			CResEditMgr* resMgr = (CResEditMgr*)m_world->m_worldBuffer->GetResMgr(  );
			Assert( NULL != resMgr );
			uInt32 size[2];
			size[0]	= projRect->brushMax[0]-projRect->brushMin[0]+1;
			size[1]	= projRect->brushMax[1]-projRect->brushMin[1]+1;
			if( RES_INVALID_ID == worldChunk->m_road ) {
				worldChunk->m_road = resMgr->PushRoad( NULL );
			}
			CNdlAlphaRes* roadRes = resMgr->GetRoad( worldChunk->m_road );			
			if( FillRoadData( roadRes, projRect->atomMin, brush, projRect->brushMin, size, brushSize, isAddRoad ,alpha) ) {
				resMgr->UpdateChunkMask( worldChunk );
				CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldChunk->m_parentTile);
			}
		}
	}
	EndEdgeAlphaTrick(brush, brushSize);

	//Trace( "Paint road---------------------------------------------- \n" );

	return true;
}

bool CNdlWorldEditor::ResetTileTexture( const char* textureName, sInt32 tile )
{
	CWorldTile* worldTile = NULL;
	CResEditMgr* resMgr = NULL;
	if(!GetActiveTileAndMgr(worldTile,resMgr))
		return false;
	
	sInt32 textureId = resMgr->PushTexture( textureName );
	for( int i = 0; i < worldTile->GetChunkTotal(); i++ ) {
		CWorldChunk* worldChunk	= worldTile->m_chunckTable[i];
		worldChunk->UnloadTexture();
		if( NULL != worldChunk ) {
			
			worldChunk->m_layerCount	= 1;

			worldChunk->m_texture[0]	= textureId;
			worldChunk->m_texture[1]	= RES_INVALID_ID;
			worldChunk->m_texture[2]	= RES_INVALID_ID;
			worldChunk->m_texture[3]	= RES_INVALID_ID;

			worldChunk->m_texInfo[0].Reset();
			worldChunk->m_texInfo[1].Reset();
			worldChunk->m_texInfo[2].Reset();
			worldChunk->m_texInfo[3].Reset();

			worldChunk->m_alpha[0]		= RES_INVALID_ID;
			worldChunk->m_alpha[1]		= RES_INVALID_ID;
			worldChunk->m_alpha[2]		= RES_INVALID_ID;

			resMgr->RefreshChunkMask( worldChunk );
		}
	}
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( tile );
	
	return true;
}

bool CNdlWorldEditor::PaintTexture( flt32* pt2, uInt8* brush, uInt32 brushSize, const char* textureName, uInt8 alpha, sInt32 paintMode )
{
	flt32 minPt[2];
	flt32 maxPt[2];
	TProjResult projResult;

	flt32 radius = (brushSize>>1)*WORLD_ATOMSIZE;
	minPt[0] = ZnMax<flt32> (pt2[0]-radius,0.f);
	minPt[1] = ZnMax<flt32> (pt2[1]-radius,0.f);
	maxPt[0] = ZnMin<flt32> (minPt[0]+(brushSize-1)*WORLD_ATOMSIZE,CURRENTTILE->GetRowColumn()[0]*WORLD_CHUNKSIZE - WORLD_ATOMSIZE*0.5);
	maxPt[1] = ZnMin<flt32> (minPt[1]+(brushSize-1)*WORLD_ATOMSIZE,CURRENTTILE->GetRowColumn()[1]*WORLD_CHUNKSIZE - WORLD_ATOMSIZE*0.5);
	
	//brush = new uInt8[brushSize*brushSize];
	//for( sInt32 j=0; j<brushSize; j++ ) {
	//	for( sInt32 i=0; i<brushSize; i++ ) {
	//		brush[j*brushSize+i] = 0xFF;
	//	}
	//}
	ProjectWorld( minPt, maxPt, projResult ,WORLD_ATOMSIZE,WORLD_TILE_CHUNK_ATOM_NUM);
	BeginEdgeAlphaTrick(projResult, brush, brushSize);
	for( uInt32 i=0; i< projResult.resultList.size(); i++ ) {
		_TProjRect* projRect = projResult.resultList[i];
		CWorldChunk* worldChunk = m_world->m_worldBuffer->GetChunk( projRect->chunk[0], projRect->chunk[1] );
		if( NULL != worldChunk ) {
			CResEditMgr* resMgr = (CResEditMgr*)m_world->m_worldBuffer->GetResMgr();
			Assert( NULL != resMgr );
			sInt32 textureId = resMgr->PushTexture( textureName );
			uInt32 size[2];
			size[0]	= projRect->brushMax[0]-projRect->brushMin[0]+1;
			size[1]	= projRect->brushMax[1]-projRect->brushMin[1]+1;
			
			sInt32 layerId = RES_INVALID_ID;
			if( FindTextureLayer( worldChunk, textureId, layerId ) ) {
				if( RES_INVALID_ID == worldChunk->m_texture[layerId] ) {
					resMgr->ReplaceChunkTextrueId(worldChunk,layerId,textureId);
				}
				sInt32 alphaLayerId = layerId-1;
				Assert( (alphaLayerId>=0) && (alphaLayerId<4) );
				bool isCountChange = false;
				if( RES_INVALID_ID == worldChunk->m_alpha[alphaLayerId] ) {
					worldChunk->m_alpha[alphaLayerId] = resMgr->PushAlpha( NULL );
					worldChunk->m_layerCount++;
					isCountChange = true;
				}
				CNdlAlphaRes* alphaRes = resMgr->GetAlpha( worldChunk->m_alpha[alphaLayerId] );
				if( FillLayerData( alphaRes, projRect->atomMin, brush, projRect->brushMin, size, brushSize, layerId, paintMode, alpha ) ) {
					if( isCountChange ) {
						resMgr->RefreshChunkMask( worldChunk );
					}
					else {
						resMgr->UpdateChunkMask( worldChunk );
					}
					CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldChunk->m_parentTile);
				}
			}
		}
	}
	EndEdgeAlphaTrick(brush, brushSize);
	//SAFE_DELETE_ARRAY( brush );
	return true;
}

bool CNdlWorldEditor::PaintDoodads(const flt32* pt2, sInt32 doodadId, uInt32 brushUnit,  uInt32 brushSize, sInt32 nDensity, uInt32* scale,sInt32 paintMode )
{
	flt32 minPt[2];
	flt32 maxPt[2];
	TProjResult projResult;

	flt32 fAtomSize = (WORLD_CHUNKSIZE/brushUnit);
	flt32 radius = (brushSize>>1)*fAtomSize;
	minPt[0] = ZnMax<flt32> (pt2[0]-radius,0.f);
	minPt[1] = ZnMax<flt32> (pt2[1]-radius,0.f);
	maxPt[0] = ZnMin<flt32> (minPt[0]+(brushSize-1)*WORLD_ATOMSIZE,CURRENTTILE->GetRowColumn()[0]*WORLD_CHUNKSIZE - WORLD_ATOMSIZE*0.5);
	maxPt[1] = ZnMin<flt32> (minPt[1]+(brushSize-1)*WORLD_ATOMSIZE,CURRENTTILE->GetRowColumn()[1]*WORLD_CHUNKSIZE - WORLD_ATOMSIZE*0.5);

	ProjectWorld( minPt, maxPt, projResult,fAtomSize,brushUnit );
	for( uInt32 i=0; i< projResult.resultList.size(); i++ ) {
		_TProjRect* projRect = projResult.resultList[i];
		CWorldChunk* worldChunk = m_world->m_worldBuffer->GetChunk( projRect->chunk[0], projRect->chunk[1] );
		if( NULL != worldChunk ) {
			uInt32 size[2];
			size[0]	= projRect->brushMax[0]-projRect->brushMin[0]+1;
			size[1]	= projRect->brushMax[1]-projRect->brushMin[1]+1;
			CResEditMgr*	pResMgr = (CResEditMgr*)m_world->m_worldBuffer->GetResMgr();
			TDoodadLevelInfo*	pInfo = worldChunk->GetDoodadLevel(doodadId,brushUnit,pResMgr);
			if( FillDoodadData( pInfo, projRect->atomMin, projRect->brushMin, size, nDensity,scale,paintMode ) ) {
				pInfo->RefreshDoodadInstance(pResMgr, worldChunk);

				CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldChunk->m_parentTile );
			}
		}
	}
	
	return true;
}


bool CNdlWorldEditor::SetChunkEnv( flt32* pt, sInt32 brushSize, sInt32 envId )
{
	sInt32  chunk[2];
	GetChunkIdFromPos(  chunk, pt );
	
	CWorldChunk* worldChunk = m_world->m_worldBuffer->GetChunk(  chunk[0], chunk[1] );
	if( NULL == worldChunk ) 
		return false;
		
	Assert( RES_INVALID_ID != envId );
	Assert( NULL != worldChunk->m_parentTile );
	
	worldChunk->m_envId	= envId;
	
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldChunk->m_parentTile);
	
	sInt32 curChunk[2];
	for( sInt32 y=-brushSize; y<=brushSize; y++ ) {
		for( sInt32 x=-brushSize; x<=brushSize; x++ ) {
			
			if( 0 == x && 0 == y )	
				continue;
			
			curChunk[0]	= chunk[0] + x;
			curChunk[1]	= chunk[1] + y;
			
			if (!CheckChunk(chunk))
			{
				continue;
			}
			
			worldChunk = m_world->m_worldBuffer->GetChunk(  curChunk[0], curChunk[1] );
			if( NULL == worldChunk ) 
				continue;
			
			worldChunk->m_envId	= envId;
		}
	}
	
	return true;
}



bool CNdlWorldEditor::CleanUnusedModel( sInt32 tile )
{
	CWorldTile* worldTile = NULL;
	CResEditMgr* resMgr = NULL;
	if(!GetActiveTileAndMgr(worldTile,resMgr))
		return false;

	resMgr->CleanUnusedResource();


	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( tile );
	return true;
}



bool CNdlWorldEditor::DeleteStaticModel(  sInt32 modelId,bool isKeyTrigger)
{
	CWorldTile* worldTile = NULL;
	CResEditMgr* resMgr = NULL;
	if(!GetActiveTileAndMgr(worldTile,resMgr))
		return false;
	
	TObjectInfo* objInfo = resMgr->m_staticModelList[modelId];
	if( NULL != objInfo ) {

		// 获取world bound
		Vector2 kMinPos, kMaxPos;
		TObjectInfo* pObjInfo = resMgr->GetStaticModel(modelId);
		CalculateModelWorldBound(pObjInfo, kMinPos, kMaxPos);

		// 重新计算tile和chunk，根据model的world bound来确定所在chunk范围
		sInt32		tileList[4][2];
		sInt32		chunkList[4][2];

		if( !GetPosInfoByModelWorldBound(kMinPos, kMaxPos, tileList, chunkList) )
		{
			return false;
		}
// 		NiBound		modelWorldBound = objInfo->model->GetWorldBound();
// 		if( !GetPosInfoByModelWorldBound(modelWorldBound, tileList, chunkList) )
// 		{
// 			return false;
// 		}


		// 把modelId从tiles删除
		//
		//0---------1
		//|			|
		//|			|
		//|			|
		//2---------3
		//
		sInt32 chunkBegin[2], chunkEnd[2];	//当前tile里，chunk的起始值和结束值
		chunkBegin[0] = chunkList[0][0];	//0位置所在chunk X
		chunkBegin[1] = chunkList[0][1];	//0位置所在chunk Y
		chunkEnd[0] = chunkList[1][0];		//1位置所在chunk X
		chunkEnd[1] = chunkList[2][1];		//2位置所在chunk Y
		ModifyModelRefInTile(worldTile, chunkBegin, chunkEnd, modelId, EMS_DELETE);
		CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldTile );

		if (isKeyTrigger)
		{
			resMgr->PopStaticModel( modelId );
		}
	}
// 	resMgr->CleanUnusedModel();
	return true;
}

bool CNdlWorldEditor::ModifyStaticModel(  sInt32 modelId, const flt32* offset, const flt32* rotate, const flt32* scale )
{
	Assert( RES_INVALID_ID != modelId );

	CWorldTile* worldTile = NULL;
	CResEditMgr* resMgr = NULL;
	if(!GetActiveTileAndMgr(worldTile,resMgr))
		return false;

	flt32 off[3];
	for( sInt32 i=0; i<3; i++ ) {
		off[i]	= offset[i];
	}

	// 获取world bound
	Vector2 kMinPos, kMaxPos;
	TObjectInfo* pObjInfo = resMgr->GetStaticModel(modelId);
	if( !pObjInfo )
		return false;
	CalculateModelWorldBound(pObjInfo, kMinPos, kMaxPos);

	// 重新计算tile和chunk，根据model的world bound来确定所在chunk范围
	sInt32		tileList[4][2];
	sInt32		chunkList[4][2];

	if( !GetPosInfoByModelWorldBound(kMinPos, kMaxPos, tileList, chunkList) )
	{
		return false;
	}
	//NiBound		modelWorldBound = resMgr->GetStaticModel(modelId)->model->GetWorldBound();
	//if( !GetPosInfoByModelWorldBound(modelWorldBound, tileList, chunkList) )
	//{
	//	return false;
	//}

	// 把modelId从tiles删除
	//
	//0---------1
	//|			|
	//|			|
	//|			|
	//2---------3
	//
	sInt32 chunkBegin[2], chunkEnd[2];	//当前tile里，chunk的起始值和结束值
	chunkBegin[0] = chunkList[0][0];	//0位置所在chunk X
	chunkBegin[1] = chunkList[0][1];	//0位置所在chunk Y
	chunkEnd[0] = chunkList[1][0];		//1位置所在chunk X
	chunkEnd[1] = chunkList[2][1];		//2位置所在chunk Y
	ModifyModelRefInTile(worldTile, chunkBegin, chunkEnd, modelId, EMS_DELETE);
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldTile );

	resMgr->ModifyStaticModel( modelId, off, rotate, scale );

	if( !GetPosInfoByModelWorldBound(kMinPos, kMaxPos, tileList, chunkList) )
	{
		return false;
	}
// 	modelWorldBound = resMgr->GetStaticModel(modelId)->model->GetWorldBound();
// 	if( !GetPosInfoByModelWorldBound(modelWorldBound, tileList, chunkList) )
// 	{
// 		return false;
// 	}

	// 把modelId加入tiles
	//
	//0---------1
	//|			|
	//|			|
	//|			|
	//2---------3
	//
	chunkBegin[0] = chunkList[0][0];	//0位置所在chunk X
	chunkBegin[1] = chunkList[0][1];	//0位置所在chunk Y
	chunkEnd[0] = chunkList[1][0];		//1位置所在chunk X
	chunkEnd[1] = chunkList[2][1];		//2位置所在chunk Y
	ModifyModelRefInTile(worldTile, chunkBegin, chunkEnd, modelId, EMS_ADD);
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldTile );


	return true;
}

bool CNdlWorldEditor::PutStaticModel(const flt32* pt, const flt32* offset, const flt32* rotate, const flt32* scale, sInt32 modelID)
{
	CWorldTile* worldTile = NULL;
	CResEditMgr* resMgr = NULL;
	if(!GetActiveTileAndMgr(worldTile,resMgr))
		return false;

	TObjectInfo* pModel = resMgr->GetStaticModel(modelID);
	if(NULL == pModel)
		return false;

	return PutStaticModel(pt, offset, rotate, scale, pModel);
}

bool CNdlWorldEditor::PutStaticModel(const flt32* pt, const flt32* offset, const flt32* rotate, const flt32* scale, TObjectInfo *pModel)
{
	ASSERT(pModel != NULL);

	CWorldTile* worldTile = NULL;
	CResEditMgr* resMgr = NULL;
	if(!GetActiveTileAndMgr(worldTile,resMgr))
		return false;

	//检查条件是否满足
	{
		sInt32  chunk[2];
		flt32 pt2[2];
		ZnSetValue2<flt32>( pt2, pt );
		GetChunkIdFromPos(  chunk, pt2 );
		CWorldChunk* worldChunk = m_world->m_worldBuffer->GetChunk( chunk[0], chunk[1] );
		if( NULL == worldChunk ) 
			return false;
	}

	sInt32 refID = pModel->id;
	if(refID >= 0 && refID < resMgr->GetStaticModelRefList().size())
	{
		sInt32 modelId = resMgr->PushStaticModel(refID, pt, offset, rotate, scale );
		if( modelId == RES_INVALID_ID ) {
			return false;
		}

		// 获取world bound
		Vector2 kMinPos, kMaxPos;
		CalculateModelWorldBound(pModel, kMinPos, kMaxPos);

		// 重新计算tile和chunk，根据model的world bound来确定所在chunk范围
		sInt32		tileList[4][2];
		sInt32		chunkList[4][2];

		if( !GetPosInfoByModelWorldBound(kMinPos, kMaxPos, tileList, chunkList) )
		{
			return false;
		}

		// 把modelId加入tiles
		//
		//0---------1
		//|			|
		//|			|
		//|			|
		//2---------3
		//
		sInt32 chunkBegin[2], chunkEnd[2];	//当前tile里，chunk的起始值和结束值
		chunkBegin[0] = chunkList[0][0];	//0位置所在chunk X
		chunkBegin[1] = chunkList[0][1];	//0位置所在chunk Y
		chunkEnd[0] = chunkList[1][0];		//1位置所在chunk X
		chunkEnd[1] = chunkList[2][1];		//2位置所在chunk Y
		ModifyModelRefInTile(worldTile, chunkBegin, chunkEnd, modelId, EMS_ADD);
		worldTile->CreateFloorAndCollision();
		CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldTile );

		return true;
	}

	return false;
}

bool CNdlWorldEditor::PutStaticModel( const flt32* pt, const flt32* offset, const flt32* rotate, const flt32* scale, const char* modelName )
{
	sInt32  chunk[2];
	flt32 pt2[2];
	ZnSetValue2<flt32>( pt2, pt );
	GetChunkIdFromPos(  chunk, pt2 );
		
	CWorldTile* worldTile = NULL;
	CResEditMgr* resMgr = NULL;
	if(!GetActiveTileAndMgr(worldTile,resMgr))
		return false;
	CWorldChunk* worldChunk = m_world->m_worldBuffer->GetChunk( chunk[0], chunk[1] );
	if( NULL == worldChunk ) 
		return false;


	sInt32 id = resMgr->PushRefStaticModel( modelName );
	if( -1 != id ) {
		sInt32 modelId = resMgr->PushStaticModel( id, pt, offset, rotate, scale );
		if( modelId == RES_INVALID_ID ) {
			return false;
		}

		// 获取world bound
		Vector2 kMinPos, kMaxPos;
		TObjectInfo* pObjInfo = resMgr->GetStaticModel(modelId);
		CalculateModelWorldBound(pObjInfo, kMinPos, kMaxPos);

		// 重新计算tile和chunk，根据model的world bound来确定所在chunk范围
		sInt32		tileList[4][2];
		sInt32		chunkList[4][2];

		if( !GetPosInfoByModelWorldBound(kMinPos, kMaxPos, tileList, chunkList) )
		{
			return false;
		}

		//NiBound		modelWorldBound = resMgr->GetStaticModel(modelId)->model->GetWorldBound();
		//if( !GetPosInfoByModelWorldBound(modelWorldBound, tileList, chunkList) )
		//{
		//	resMgr->PopStaticModel( modelId );
		//	return false;
		//}

		// 把modelId加入tiles
		//
		//0---------1
		//|			|
		//|			|
		//|			|
		//2---------3
		//
		sInt32 chunkBegin[2], chunkEnd[2];	//当前tile里，chunk的起始值和结束值
		chunkBegin[0] = chunkList[0][0];	//0位置所在chunk X
		chunkBegin[1] = chunkList[0][1];	//0位置所在chunk Y
		chunkEnd[0] = chunkList[1][0];		//1位置所在chunk X
		chunkEnd[1] = chunkList[2][1];		//2位置所在chunk Y
		ModifyModelRefInTile(worldTile, chunkBegin, chunkEnd, modelId, EMS_ADD);
		worldTile->CreateFloorAndCollision();
		CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldTile );

		return true;
	}else {
		Assert( false );
	}

	return false;
}

bool CNdlWorldEditor::FillShadowData( CNdlAlphaRes* res, uInt32* originDest, uInt8* brush, uInt32* originSrc, uInt32* sizeSrc, uInt32 brushSize, bool isAddShadow , uInt8 alpha)
{
	Assert( NULL != res );

	const int size		= WORLD_TILE_CHUNK_ATOM_NUM;
	uAlphaBit* destPtr		= res->m_maskData;
	uAlphaBit* destBasePtr	= destPtr;

	for( uInt32 y=0; y<sizeSrc[1]; y++ ) {
		destPtr = destBasePtr+(originDest[1]+y)*size+originDest[0];
		for( uInt32 x=0; x<sizeSrc[0]; x++ ) {
			int nIndex = (originDest[0] + x)/2;
			destPtr = destBasePtr+(originDest[1]+y)*size/2+nIndex;
			int nMod = (originDest[0] + x + 1)%2;

			uInt32 off = (originSrc[1]+y)*brushSize+originSrc[0]+x;

			
			if( brush[off] > 0x80 ) 
			{
				if( isAddShadow )
				{
					if (0 == nMod)
					{
						*destPtr = (*destPtr&0x0F) | ((0xFF - alpha) & 0xF0);	
					}
					else
					{
						*destPtr = (*destPtr&0xF0) | ((0xFF - alpha) & 0x0F);	
					}
				}
				else 
				{
					if (0 == nMod)
					{
						*destPtr |= 0xF0;
					}
					else
					{
						*destPtr |= 0x0F;
					}
				}
			}
		}
	}
// 	res->UpdateToTexture();
	return true;
}

bool CNdlWorldEditor::FillLayerData( CNdlAlphaRes* res, uInt32* originDest, uInt8* brush, uInt32* originSrc, uInt32* sizeSrc, uInt32 brushSize, sInt32 layerId, sInt32 blendMode, uInt8 alpha )
{
	Assert( NULL != res );
	Assert( layerId > 0 );

	const int size	= WORLD_TILE_CHUNK_ATOM_NUM;
	uAlphaBit* destPtr	= res->m_maskData;
	uAlphaBit* basePtr	= destPtr;


	for( uInt32 y=0; y<sizeSrc[1]; y++ ) {
// 		destPtr = basePtr+(originDest[1]+y)*size+originDest[0];
		for( uInt32 x=0; x<sizeSrc[0]; x++ ) {
			int nIndex = (originDest[0] + x)/2;
			destPtr = basePtr+(originDest[1]+y)*size/2+nIndex;
			int nMod = (originDest[0] + x + 1)%2;
			uInt32 off = (originSrc[1]+y)*brushSize+originSrc[0]+x;

			BlendWithMode( *destPtr,nMod, brush[off], (znLayerBlendMode)blendMode, alpha );
			
// 			destPtr++;
		}
	}
// 	res->UpdateToTexture();
	return true;
}

bool CNdlWorldEditor::FindTextureLayer( CWorldChunk* worldChunk, sInt32 textureId, sInt32& texLayerId )
{
	if( (worldChunk->m_texture[0]==textureId) || (worldChunk->m_texture[0]==RES_INVALID_ID) ) {
		return false;
	}
	for( sInt32 i=1; i<TextureLayerFlight; i++ ) {
		if( (worldChunk->m_texture[i]==textureId) || (worldChunk->m_texture[i]==RES_INVALID_ID) ) {
			texLayerId = i;
			return true;
		}
	}
	return false;
}

// enum emDoodadOptMode {
// 	emDOM_Assign   = 0,
// 	emDOM_Add,
// 	emDOM_Reduce,
// 	emDOM_Del,
// 	emDOM_ScaleRefresh
// };

bool FillDoodadMap( TDoodadInfoForEdit* dest, sInt32 nDensity, uInt32* scale, sInt32 paintMode ) 
{
	switch( paintMode ) {
	case 0:	// emDOM_Assign.
		dest->m_nDensity = nDensity;
		break;
	case 1:	// emDOM_Add.
		dest->m_nDensity += nDensity;
		
		break;
	case 2:	// emDOM_Reduce.
		dest->m_nDensity -= nDensity;
		break;
	case 3:	// emDOM_Del.
		dest->m_nDensity = 0;
		break;
	case 4:	// emDOM_ScaleRefresh.
		{
// 			if (0 != dest->m_nScale)
// 			{
// 				if (scale[1] == scale[0])
// 				{
// 					dest->m_nScale = scale[0];
// 				}
// 				else
// 				{
// 					dest->m_nScale = scale[0]+ rand()%(scale[1] - scale[0]);
// 				}
// 			}
// 			return true;
		}
		break;
	default:
		break;
	}
	if (dest->m_nDensity > 100)
	{
		dest->m_nDensity = 100;
	}
	if (dest->m_nDensity < 0)
	{
		dest->m_nDensity = 0;
	}
	if ((rand()%100) < dest->m_nDensity)
	{
		if (scale[1] == scale[0])
		{
			dest->m_nScale = scale[0];
		}
		else
		{
			dest->m_nScale = scale[0]+ rand()%(scale[1] - scale[0]);
		}
	}
	else
	{
		dest->m_nScale = 0;
	}
		
	
	return true;
}

bool CNdlWorldEditor::FillDoodadData( TDoodadLevelInfo* pLevelInfo,uInt32* originDest, uInt32* originSrc, uInt32* sizeSrc,sInt32 nDensity, uInt32* scale, sInt32 paintMode  )
{
	Assert( NULL != pLevelInfo );

	const int size		= pLevelInfo->mulevelUnit;
	
	for( uInt32 y=0; y<sizeSrc[1]; y++ ) {
		uInt32 destLable	= (originDest[1]+y) * size + originDest[0];
		for( uInt32 x=0; x<sizeSrc[0]; x++ ) {
			FillDoodadMap( (TDoodadInfoForEdit*)&pLevelInfo->GetDoodad(destLable), nDensity,scale, paintMode );
			destLable++;
		}
	}
	return true;
}

//bool CNdlWorldEditor::GetPosInfoByModelWorldBound( NiBound WorldBound, sInt32 tile[4][2], sInt32 chunk[4][2] )
//{
//	Vector	center = WorldBound.GetCenter();
//	flt32		radius = WorldBound.GetRadius();
//	flt32		pos[2];
////
////0---------1
////|			|
////|			|
////|			|
////2---------3
////
//	// 计算Xmin,Ymin所在tile和chunk
//	pos[0] = center.x - radius;
//	pos[1] = center.y - radius;
//	GetChunkIdFromPos(  chunk[0], pos );
//
//	// 计算Xmax,Ymin所在tile和chunk
//	pos[0] = center.x + radius;
//	pos[1] = center.y - radius;
//	GetChunkIdFromPos( chunk[1], pos );
//
//	// 计算Xmin,Ymax所在tile和chunk
//	pos[0] = center.x - radius;
//	pos[1] = center.y + radius;
//	GetChunkIdFromPos(  chunk[2], pos );
//
//	// 计算Xmax,Ymax所在tile和chunk
//	pos[0] = center.x + radius;
//	pos[1] = center.y + radius;
//	GetChunkIdFromPos( chunk[3], pos );
//	
//	return true;
//}

bool CNdlWorldEditor::GetPosInfoByModelWorldBound( Vector2 vMin, Vector2 vMax, sInt32 tile[4][2], sInt32 chunk[4][2] )
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
	GetChunkIdFromPos(  chunk[0], pos );

	// 计算Xmax,Ymin所在tile和chunk
	pos[0] = vMax.x;
	pos[1] = vMin.y;
	GetChunkIdFromPos( chunk[1], pos );

	// 计算Xmin,Ymax所在tile和chunk
	pos[0] = vMin.x;
	pos[1] = vMax.y;
	GetChunkIdFromPos(  chunk[2], pos );

	// 计算Xmax,Ymax所在tile和chunk
	pos[0] = vMax.x;
	pos[1] = vMax.y;
	GetChunkIdFromPos( chunk[3], pos );

	return true;
}

	//
	//0---------1
	//|			|
	//|			|
	//|			|
	//2---------3
	//
void CNdlWorldEditor::ModifyModelRefInTile( CWorldTile* tile, const sInt32* beginChunk, const sInt32* endChunk, sInt32 modelId, int change )
{
	sInt32 curChunk[2];

	for( curChunk[1]=beginChunk[1]; curChunk[1]<=endChunk[1]; curChunk[1]++ )
	{
		for( curChunk[0]=beginChunk[0]; curChunk[0]<=endChunk[0]; curChunk[0]++ )
		{
			ModifyModelRefInOneChunk( tile, curChunk, modelId, change );
		}
	}
}

void CNdlWorldEditor::ModifyModelRefInOneChunk( CWorldTile* tile, const sInt32* chunk, sInt32 modelId, int change )
{
	CWorldChunk* worldChunk = tile->GetChunk( chunk[0], chunk[1] );

	if( change == EMS_ADD )
	{
		worldChunk->PushModel( modelId );
	}
	else if( change == EMS_DELETE )
	{
		std::vector<sInt32>::iterator it	= worldChunk->m_staticModelList.begin();
		for(;it!=worldChunk->m_staticModelList.end();)
		{
			sInt32 p = *it;
			if( p == modelId ) {
				worldChunk->m_staticModelList.erase(it);
				break;
			}
			else {
				it++;
			}
		}
	}

	// 更新四叉树
	flt32 fHeight[2];
	worldChunk->CalculateChunkTotalHeight(tile->GetCResMgr(), fHeight);
	worldChunk->m_parentTile->m_tileQuadTree.UpdateQuadTree( worldChunk );
}


bool CNdlWorldEditor::PaintVertexColor( flt32* origin, uInt32 brushSize,NiColor& niColor, uInt32 flow,bool isAdd /*= true */, uInt8 alpha )
{
	flt32 radius = (brushSize)*WORLD_VERTSIZE/2;
	sInt32 vertCount = brushSize + 1;

	sInt32 centerVert[2], vId[2];
	flt32 vertDist[2];

	centerVert[0]		= GLVertFromPos( origin[0] ,0);
	centerVert[1]		= GLVertFromPos( origin[1] ,1);

	flt32 refHeight	= 0.0f;			
	_TVert vertList[3];
	_TVert vert;

	for( sInt32 y=-(vertCount); y<vertCount; y++ ) {
		for( sInt32 x=-vertCount; x<vertCount; x++ ) {
			vId[0]			= centerVert[0] + x;
			vId[1]			= centerVert[1] + y;
			if(vId[0] < 0 || vId[1] < 0 
				|| vId[0] > (WORLD_TILE_CHUNK_UNIT_NUM*CURRENTTILE->GetRowColumn()[0])*2
				|| vId[1] > (WORLD_TILE_CHUNK_UNIT_NUM*CURRENTTILE->GetRowColumn()[1])*2
				)
			{
				continue;
			}
			if( ( vId[0] % 2 ) != ( vId[1] % 2 ) )
				continue;

			vertDist[0]		= PosFromGLVert( vId[0] ,0) - origin[0];
			vertDist[1]		= PosFromGLVert( vId[1] ,1) - origin[1];


			if (abs(vertDist[0]) > radius || abs(vertDist[1]) > radius )
			{
				continue;
			}
			vert.chunk[0]	= ChunkFromGlVert( vId[0] ,0);
			vert.chunk[1]	= ChunkFromGlVert( vId[1] ,1);
			vert.vert[0]	= vId[0] - vert.chunk[0]* WORLD_TILE_CHUNK_VERT_NUM;
			vert.vert[1]	= vId[1] - vert.chunk[1]* WORLD_TILE_CHUNK_VERT_NUM;;

			NiColor		destColor;
			bool isOk		= AddVertColor(destColor,  vert.chunk, vert.vert,flow,niColor,isAdd ,alpha);

			sInt32 sameCount = GetSameVert( vertList, vert );
			for( size_t j=0; j<sameCount; j++ ) {
				const _TVert& p = vertList[j];
				if (isOk)
				{
					SetVertColor( p.chunk, p.vert, destColor,alpha );
				}
				else
				{
					isOk = AddVertColor(destColor,  vert.chunk, vert.vert,flow,niColor,isAdd ,alpha);
				}
			}
		}
	}

	return true;
}

bool CNdlWorldEditor::ClearVertexColor( flt32* origin,  uInt32 brushSize )
{
	flt32 radius = (brushSize)*WORLD_VERTSIZE/2;
	sInt32 vertCount = brushSize + 1;

	sInt32 centerVert[2], vId[2];
	flt32 vertDist[2];

	centerVert[0]		= GLVertFromPos( origin[0] ,0);
	centerVert[1]		= GLVertFromPos( origin[1] ,1);

	flt32 refHeight	= 0.0f;			
	_TVert vertList[3];
	_TVert vert;

	for( sInt32 y=-(vertCount); y<vertCount; y++ ) {
		for( sInt32 x=-vertCount; x<vertCount; x++ ) {
			vId[0]			= centerVert[0] + x;
			vId[1]			= centerVert[1] + y;
			if(vId[0] < 0 || vId[1] < 0 
				|| vId[0] > (WORLD_TILE_CHUNK_UNIT_NUM*CURRENTTILE->GetRowColumn()[0])*2
				|| vId[1] > (WORLD_TILE_CHUNK_UNIT_NUM*CURRENTTILE->GetRowColumn()[1])*2
				)
			{
				continue;
			}
			if( ( vId[0] % 2 ) != ( vId[1] % 2 ) )
				continue;

			vertDist[0]		= PosFromGLVert( vId[0] ,0) - origin[0];
			vertDist[1]		= PosFromGLVert( vId[1] ,1) - origin[1];


			if (abs(vertDist[0]) > radius || abs(vertDist[1]) > radius )
			{
				continue;
			}

			vert.chunk[0]	= ChunkFromGlVert( vId[0] ,0);
			vert.chunk[1]	= ChunkFromGlVert( vId[1] ,1);
			vert.vert[0]	= vId[0] - vert.chunk[0]* WORLD_TILE_CHUNK_VERT_NUM;
			vert.vert[1]	= vId[1] - vert.chunk[1]* WORLD_TILE_CHUNK_VERT_NUM;;

			NiColor		destColor(NiColor::WHITE/2);
			bool isOk		= SetVertColor(  vert.chunk, vert.vert,destColor,0x22 );

			sInt32 sameCount = GetSameVert( vertList, vert );
			for( size_t j=0; j<sameCount; j++ ) {
				const _TVert& p = vertList[j];
				SetVertColor( p.chunk, p.vert, destColor,0x22 );
			}
		}
	}

	return true;
}


bool CNdlWorldEditor::AddVertColor( NiColor& retColor,  const sInt32* chunk, const sInt32* vert,uInt32 flow, NiColor& destColor ,bool isAdd, uInt8 alpha)
{
	CWorldChunk* worldChunk = m_world->m_worldBuffer->GetChunk(  chunk[0], chunk[1] );
	if( NULL == worldChunk )	
		return false;

	CResEditMgr* resMgr = (CResEditMgr*)m_world->m_worldBuffer->GetResMgr(  );	
	sInt32 axis[2];
	for( sInt32 i=0; i<2; i++ )	{
		axis[i] = vert[i]/2;
	}
	if( vert[0]%2 == 0 ) {
		if( vert[1]%2 == 0 ) {
			sInt32 VertId = axis[1]*(WORLD_TILE_CHUNK_UNIT_NUM+1)+axis[0];
			NiColor myColor;
			ConvertRGB2NiColor(worldChunk->m_vertexOut[VertId].niColor,myColor);
			float fCoaf = flow/100.f;
			myColor = CalColor(isAdd, myColor, fCoaf, destColor);
			COLORREF refColor;
			ConvertNiColor2RGB(myColor,refColor);
			worldChunk->m_vertexOut[VertId].niColor = (alpha<< 24) | (refColor & 0x00FFFFFF);
			resMgr->RefreshChunkShapeVertexColor(worldChunk->m_shape,VertId,worldChunk->m_vertexOut[VertId].niColor,true);
			retColor	= myColor;
		}
		else {
			Assert( false );
		}
	}
	else {
		if( vert[1]%2 == 1 ) {
			sInt32 VertId = axis[1]*WORLD_TILE_CHUNK_UNIT_NUM+axis[0];
			NiColor myColor;
			ConvertRGB2NiColor(worldChunk->m_vertexIn[VertId].niColor,myColor);
			float fCoaf = flow/100.f;
			myColor = CalColor(isAdd, myColor, fCoaf, destColor);
			COLORREF refColor;
			ConvertNiColor2RGB(myColor,refColor);
			worldChunk->m_vertexIn[VertId].niColor = (alpha<< 24) | (refColor & 0x00FFFFFF);
			resMgr->RefreshChunkShapeVertexColor(worldChunk->m_shape,VertId,worldChunk->m_vertexIn[VertId].niColor,false);
			retColor		= myColor;
		}
		else {
			Assert( false );
		}
	}
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldChunk->m_parentTile );

	return true;
}

bool CNdlWorldEditor::SetVertColor(  const sInt32* chunk, const sInt32* vert, NiColor& destColor , uInt8 alpha)
{
	CWorldChunk* worldChunk = m_world->m_worldBuffer->GetChunk( chunk[0], chunk[1] );
	if( NULL == worldChunk )	
		return false;

	CResEditMgr* resMgr = (CResEditMgr*)m_world->m_worldBuffer->GetResMgr(   );	
	sInt32 axis[2];
	for( sInt32 i=0; i<2; i++ )	{
		axis[i] = vert[i]/2;
	}
	if( vert[0]%2 == 0 ) {
		if( vert[1]%2 == 0 ) {
			sInt32 VertId = axis[1]*(WORLD_TILE_CHUNK_UNIT_NUM+1)+axis[0];
			COLORREF refColor;
			ConvertNiColor2RGB(destColor,refColor);
			worldChunk->m_vertexOut[VertId].niColor = (alpha << 24) | (refColor & 0x00FFFFFF);
			resMgr->RefreshChunkShapeVertexColor(worldChunk->m_shape,VertId,worldChunk->m_vertexOut[VertId].niColor,true);
		}
		else {
			Assert( false );
		}
	}
	else {
		if( vert[1]%2 == 1 ) {
			sInt32 VertId = axis[1]*WORLD_TILE_CHUNK_UNIT_NUM+axis[0];
			COLORREF refColor;
			ConvertNiColor2RGB(destColor,refColor);
			worldChunk->m_vertexIn[VertId].niColor = (alpha << 24) | (refColor & 0x00FFFFFF);
			resMgr->RefreshChunkShapeVertexColor(worldChunk->m_shape,VertId,worldChunk->m_vertexIn[VertId].niColor,false);
		}
		else {
			Assert( false );
		}
	}
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldChunk->m_parentTile );

	return true;
}

NiColor& CNdlWorldEditor::CalColor( bool isAdd, NiColor& myColor, float fCoaf, NiColor& destColor )
{
	if (isAdd)
	{
		myColor		= myColor*(1.0f - fCoaf) + destColor *fCoaf;
	}
	else
	{
		myColor = myColor + fCoaf*(NiColor::WHITE - destColor);
		if (myColor.r > 1.0f)
		{
			myColor.r = 1.f;
		}
		if (myColor.g > 1.0f)
		{
			myColor.g = 1.f;
		}
		if (myColor.b > 1.0f)
		{
			myColor.b = 1.f;
		}
	}
//	Trace("CalColor result: %f ,  %f ,  %f\n",myColor.r,myColor.g,myColor.b);
	return myColor;
}

bool CNdlWorldEditor::GetActiveTileAndMgr( CWorldTile*& worldTile,CResEditMgr*& resMgr )
{
	 worldTile = m_world->m_worldBuffer->GetActiveTile();
	if( NULL == worldTile )
		return false;
	resMgr = (CResEditMgr*)worldTile->GetCResMgr();
	if( NULL == resMgr )
		return false;
	return true;
}

bool CNdlWorldEditor::CheckChunk( sInt32* chunk )
{
	if( chunk[0]<0 || chunk[0]>=CURRENTTILE->GetRowColumn()[0] )
		return false;
	if( chunk[1]<0 || chunk[1]>=CURRENTTILE->GetRowColumn()[1])
		return false;
	return true;
}

void CNdlWorldEditor::CalculateModelWorldBound( TObjectInfo* pObjInfo, Vector2& vMin, Vector2& vMax )
{
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
}

bool CNdlWorldEditor::SetChunkZone( flt32* pt, sInt32 brushSize, sInt32 zoneId )
{
	sInt32  chunk[2];
	GetChunkIdFromPos(  chunk, pt );

	CWorldChunk* worldChunk = m_world->m_worldBuffer->GetChunk(  chunk[0], chunk[1] );
	if( NULL == worldChunk ) 
		return false;

	Assert( RES_INVALID_ID != zoneId );
	Assert( NULL != worldChunk->m_parentTile );

	worldChunk->m_zoneId	= zoneId;

	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( worldChunk->m_parentTile);

	sInt32 curChunk[2];
	for( sInt32 y=-brushSize; y<=brushSize; y++ ) {
		for( sInt32 x=-brushSize; x<=brushSize; x++ ) {

			if( 0 == x && 0 == y )	
				continue;

			curChunk[0]	= chunk[0] + x;
			curChunk[1]	= chunk[1] + y;

			if (!CheckChunk(chunk))
			{
				continue;
			}

			worldChunk = m_world->m_worldBuffer->GetChunk(  curChunk[0], curChunk[1] );
			if( NULL == worldChunk ) 
				continue;

			worldChunk->m_zoneId	= zoneId;
		}
	}

	return true;
}

bool CNdlWorldEditor::ReplaceTexture( CResEditMgr* resMgr, sInt32 texId, const char* textureName )
{
	if( RES_INVALID_ID == texId) 
		return false;


	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( resMgr->m_bindTile);
	CWorldChunk* pErrorChunk = NULL;
	bool bRet =	resMgr->ReplaceTexture(texId,textureName,&pErrorChunk);
	if (!bRet)
	{
		CString prompt;
		prompt.Format(_T("chunk [%d %d] 已经使用了贴图：%s,未能替换所有该贴图!"),pErrorChunk->m_chunk[0],pErrorChunk->m_chunk[1],textureName);
		::AfxMessageBox(prompt);
	}
	return bRet;
}
extern long SaveBmpFile(char *filename,long sx,long sy,long xl,long yl,BYTE *bitmap);
bool CNdlWorldEditor::GenerateMeshLightMap()
{
	CWorldTile* pWorldTile = NULL;
	CResEditMgr* pResMgr = NULL;
	if(!GetActiveTileAndMgr(pWorldTile,pResMgr))
		return false;

	// 旧lightmap贴图注销lyh光照图生成入口
	for( int i=0; i<pWorldTile->GetLightMaps().size(); ++i )
	{
		GetEngine()->GetTextureManager()->UnRegisterTexture( pWorldTile->GetLightMaps()[i]->GetTextureId() );
	}


	//显示进度
	/*LightMapMeshProcessDlg processDlg;	
	processDlg.Create(IDD_LIGHTMAP_MESH_PROCESS, 0);
	CRect rect;
	processDlg.GetWindowRect(&rect);
	processDlg.SetWindowPos(0, 500, 500, rect.right - rect.left, rect.bottom - rect.top, 0);
	processDlg.UpdateWindow();
	processDlg.ShowWindow(SW_SHOW);*/

	// 创建灯光图
	DWORD time = HQ_TimeGetTime();
	BOOL bChangeOnly = FALSE;
	StaticMeshRayTracer xTracer(pWorldTile, bChangeOnly);
	int nObjects = xTracer.RetrieveIlluminateObjects();
	if( nObjects )
		pWorldTile->ClearLightMaps();

	// 射线处理每个受光模型
	//processDlg.m_process.SetRange(0, nObjects);
	for( int i=0; i<nObjects; ++i )
	{
		//char text[256] = {0};
		//processDlg.m_process.SetPos(i+1);
		//sprintf_s(text, sizeof(text)-1, "创建%d/%d个模型光照信息", i+1, nObjects);
		//processDlg.m_static.SetWindowText(text);

		xTracer.RayTraceObject(i, SwGlobal::GetWorldPicker());
	}
	// 生成光照图
	for( int i=0; i<nObjects; ++i )
	{
		/*char text[256] = {0};
		processDlg.m_process.SetPos(i+1);
		sprintf_s(text, sizeof(text)-1, "保存%d/%d个模型光照图", i+1, nObjects);
		processDlg.m_static.SetWindowText(text);*/

		xTracer.BuildObjectResource(i);
		xTracer.AllocateObjectLightMap(i);  //lyh这里将压入光照图 把上边算好的光照图颜色数据拷贝到最终需要生成的图片数据中
	}
	// 释放临时数据
	xTracer.ReleaseData();

	{
		char msg[256] = {0};
		float second = (HQ_TimeGetTime() - time)*0.001f;
		if( second < 60 )
			sprintf_s(msg, sizeof(msg)-1, "-> Create mesh lightmap cost %.2f seconds\n", second);
		else
			sprintf_s(msg, sizeof(msg)-1, "-> Create mesh lightmap cost %.2f minutes\n", second/60.f);
		OutputDebugString(msg);
	}


	// 重置灯光的lightchanged标志
	for( int i=0; i<pWorldTile->GetChunkTotal(); ++i )
	{
		CWorldChunk* worldChunk = pWorldTile->GetChunk( i );
		if( NULL != worldChunk )
		{
			if( RES_INVALID_ID != worldChunk->GetEnvId() )
			{
				Assert( worldChunk->GetEnvId() >=0 && worldChunk->GetEnvId() < pResMgr->GetEnvResList().size() );
				CNdlEnvRes* envRes = (CNdlEnvRes*)pResMgr->GetEnvRes( worldChunk->GetEnvId() );
				if( !envRes )
					continue;
				CNdlLightRes* lightRes = (CNdlLightRes*)pResMgr->GetLightRes( envRes->GetLightId() );
				if( !lightRes )
					continue;
				lightRes->ClearLightChanged();
			}
		}
	}

	// 保存全局光照贴图
	SaveLightmapTexture(pWorldTile,NULL /*&processDlg*/);

	/*processDlg.ShowWindow(SW_HIDE);*/

	char text[MAX_PATH] = {0};
	sprintf_s(text, sizeof(text)-1, "模型光照投影创建完成，生成 %d 张光照图！", pWorldTile->GetLightMapNum());
	::AfxMessageBox( _T(text) );

	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( pWorldTile );

	if( pWorldTile->GetLightMapNum() )
		pWorldTile->RefreshLightmapTexId();

	return true;
}

void CNdlWorldEditor::SaveLightmapTexture(CWorldTile* pWorldTile, LightMapMeshProcessDlg* dlg)
{
	if( !pWorldTile /*|| !dlg*/ )
		return;

	// 保存全局光照贴图
	char szLightmapName[MAX_PATH] = {0};
	char szLightmapDDS[MAX_PATH] = {0};
	char szTileNoExt[128] = {0};
	strncpy(szTileNoExt, pWorldTile->GetPathName(), sizeof(szTileNoExt)-1);
	char* p = strrchr(szTileNoExt, '.');
	*p = '\0';

	// 从lightmap子目录下找
	// 查找'\\'
	char szFolder[128] = {0};
	char szTileName[128] = {0};
	strncpy(szFolder, szTileNoExt, sizeof(szFolder)-1);
	p = strrchr(szFolder, '\\');
	if( p && strlen(szFolder) > p - szFolder + 1)	// p后面还有字母
	{
		strncpy(szTileName, p+1, sizeof(szTileName)-1);
		*(p+1) = '\0';
		char szTemp[MAX_PATH] = {0};
		sprintf_s(szTemp, sizeof(szTemp)-1, "%slightmap", szFolder);
		strncpy(szFolder, szTemp, sizeof(szFolder)-1);
	}

	char szSubFolder[MAX_PATH] = {0};
	sprintf_s(szSubFolder, sizeof(szSubFolder)-1, "%s\\%s", SwGlobal::GetWorld()->GetWorldPath(), "lightmap"/*szFolder*/);//lyh改路径光照图
	CString strSubFolder = szSubFolder;
	CreateDirectory(strSubFolder,NULL);

	std::vector<LightMapTexture*>& vecLightMaps = pWorldTile->GetLightMaps();
	//dlg->m_process.SetRange(0, vecLightMaps.size());
	for( int i=0; i<vecLightMaps.size(); ++i )
	{
		/*char text[256] = {0};
		dlg->m_process.SetPos(i+1);
		sprintf_s(text, sizeof(text)-1, "保存%d/%d张光照贴图", i+1, vecLightMaps.size());
		dlg->m_static.SetWindowText(text);*/

		// 保存BMP
		sprintf_s(szLightmapName, sizeof(szLightmapName)-1, "%s\\%s_lm%d.bmp",
			szSubFolder, /*szTileName*/szFolder, vecLightMaps[i]->GetLocalId());//lyh改路径 光照图

		BYTE *pRGBBytes = new BYTE[vecLightMaps[i]->GetWidth()*vecLightMaps[i]->GetHeight()*3];
		int offset = 0;
		BYTE* pLightMapBits = (BYTE*)vecLightMaps[i]->GetBitmap();
		for( int j=0; j<vecLightMaps[i]->GetWidth()*vecLightMaps[i]->GetHeight(); ++j )
		{
			++offset;	// 跳过alpha
			pRGBBytes[j*3] = pLightMapBits[offset++];	//r
			pRGBBytes[j*3+1] = pLightMapBits[offset++];	//g
			pRGBBytes[j*3+2] = pLightMapBits[offset++];	//b
		}
		SaveBmpFile(szLightmapName, 0, 0, vecLightMaps[i]->GetWidth(), vecLightMaps[i]->GetHeight(), pRGBBytes);

		// BMP转成DDS(DXT1)
		sprintf_s(szLightmapDDS, sizeof(szLightmapDDS)-1, "%s\\%s_lm%d.dds",
			szSubFolder, /*szTileName*/szFolder, vecLightMaps[i]->GetLocalId());//lyh改路径 光照图

		DeleteFile(szLightmapDDS);

		PROCESS_INFORMATION pi;
		STARTUPINFO si = {sizeof(si)};
		char szCommand[1024] = {0};
		char szExeFileName[128] = "DxTex.exe";
		sprintf( szCommand, "%s %s -m DXT1 %s", szExeFileName, szLightmapName, szLightmapDDS );
		BOOL ret = CreateProcess(
			szExeFileName,
			szCommand,
			NULL, 
			NULL, 
			FALSE, 
			0, 
			NULL, 
			NULL, 
			&si,
			&pi );
		if(!ret) 
		{
			::AfxMessageBox( _T("缺少DxTex.exe工具无法压缩灯光图！") );
			return;
		}
		else
		{
			DWORD st = HQ_TimeGetTime();
			// 等待压缩完成
			while( !SwPublicFunc::IsFileExist(szLightmapDDS) )
				Sleep(100);

			{
				char msg[256] = {0};
				float second = (HQ_TimeGetTime() - st)*0.001f;
				if( second < 60 )
					sprintf_s(msg, sizeof(msg)-1, "-> Create lightmap %s cost %.2f seconds\n", szLightmapDDS, second);
				else
					sprintf_s(msg, sizeof(msg)-1, "-> Create lightmap %s cost %.2f minutes\n", szLightmapDDS, second/60.f);
				OutputDebugString(msg);
			}
			CloseHandle(pi.hThread);
			pi.hThread = NULL;
		}

		// 加载DDS贴图
		int texid = GetEngine()->GetTextureManager()->RegisterTexture( szLightmapDDS, FALSE, FALSE);
		if( texid >= 0 )
		{
			vecLightMaps[i]->SetTextureId(texid);
		}
		DeleteFile(szLightmapName);
	}
}