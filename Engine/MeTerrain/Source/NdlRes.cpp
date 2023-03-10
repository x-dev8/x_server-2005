/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	NdlRes.cpp
* Date: 	03/18/2007
* Desc:
*
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "MeTerrain/NdlGlobalResMgr.h"
#include "MeTerrain/NdlRes.h"
#include "Me3d/Utility.h"
#include "MeTerrain/SwRender.h"
#include "tstring.h"
float g_fTerrainScale = 0.02f;
char	g_NullModelPath[512] = "data\\SceneObject\\Common\\Null\\null.mex";
////////////////////////////////////////////////////////////////////////////////
namespace {
	int IndexMapBuf(int x, int y, sInt16 gridCount) {
		return ((y+1)/2)*(gridCount+1) + (y/2)*gridCount + x;
	}
	template <class T>
	void Stripify( T *in, T* out, sInt16 gridCount )	{
		for (int row=0; row < gridCount; row++) 
		{
			T *thisrow = &in[IndexMapBuf(0,row*2,gridCount)];
			T *nextrow = &in[IndexMapBuf(0,row*2+1,gridCount)];
			T *overrow = &in[IndexMapBuf(0,(row+1)*2,gridCount)];

			for(int col=0; col< gridCount; col++) 
			{
				*out++ = overrow[col];
				*out++ = nextrow[col];
				*out++ = thisrow[col];

				*out++ = nextrow[col];
				*out++ = thisrow[(col + 1)];
				*out++ = thisrow[col];

				*out++ = overrow[(col + 1)];
				*out++ = nextrow[col];
				*out++ = overrow[col];

				*out++ = nextrow[col];
				*out++ = overrow[(col + 1)];
				*out++ = thisrow[(col + 1)];
			}
		}
// 		for (int row=0; row<gridCount; row++) { 
// 			T *thisrow = &in[IndexMapBuf(0,row*2,gridCount)];
// 			T *nextrow = &in[IndexMapBuf(0,row*2+1,gridCount)];
// 			T *overrow = &in[IndexMapBuf(0,(row+1)*2,gridCount)];
// 			if(row>0) {
// 				*out++ = thisrow[0];// jump end
// 			}
// 			for(int col=0; col<gridCount; col++) {
// 				*out++ = thisrow[col];
// 				*out++ = nextrow[col];
// 			}
// 			*out++ = thisrow[gridCount];
// 			*out++ = overrow[gridCount];
// 			*out++ = overrow[gridCount];	// jump start
// 			*out++ = thisrow[0];	// jump end
// 			*out++ = thisrow[0];
// 			for(int col=0; col<gridCount; col++) {
// 				*out++ = overrow[col];
// 				*out++ = nextrow[col];
// 			}
// 			if(row<gridCount)		*out++ = overrow[gridCount];
// 			if(row<(gridCount-1))	*out++ = overrow[gridCount];// jump start
// 		}
	}
	void _CopyVertexTable( TChunkVertex* destData, const swRect& destRect, TChunkVertex* srcData, const swRect& srcRect, sInt32 numX, sInt32 numY ) {
		TChunkVertex* destPtr	= destData;
		TChunkVertex* baseDPtr	= destPtr;
		
		TChunkVertex* srcPtr	= srcData;
		TChunkVertex* baseSPtr	= srcPtr;
		
		Assert( (destRect.w-destRect.x) >= numX );
		Assert( (destRect.h-destRect.y) >= numY );
		Assert( (srcRect.w-srcRect.x) >= numX );
		Assert( (srcRect.h-srcRect.y) >= numY );
		
		for( sInt32 y=0; y<numY; y++ ) {
			destPtr = baseDPtr+(destRect.y+y)*destRect.w+destRect.x;
			srcPtr	= baseSPtr+(srcRect.y+y)*srcRect.w+srcRect.x;
			memcpy( destPtr, srcPtr, sizeof(TChunkVertex)*numX );
		}
		//for( sInt32 y=0; y<numY; y++ ) {
		//	destPtr = baseDPtr+(destRect.y+y)*destRect.w+destRect.x;
		//	srcPtr	= baseSPtr+(srcRect.y+y)*srcRect.w+srcRect.x;
		//	for( sInt32 x=0; x<numX; x++ ) {
		//		Trace( "[%d,%d] %8.3f " );
		//		, x, y, *srcPtr
		//		
		//	}
		//	Trace( "\n" );
		//}		
	}
	inline
	void LinearLerpByte( uInt8& result, uInt8 lerpA, uInt8 lerpB, flt32 scale ) {  
		sInt16 l	= ZnFloat2Int( (lerpB-lerpA)*scale );
		l			= lerpA + l;
		result		= ZnClamp<uInt16>( l, 0x0, 0xFF );
	}
	inline
	void LinearLerpRGB( uInt32& result, uInt32 lerpA, uInt32 lerpB, flt32 scale ) {
		uInt8 r,g,b;
		LinearLerpByte( r, (lerpA>>16)&0xFF, (lerpB>>16)&0xFF, scale );
		LinearLerpByte( g, (lerpA>>8)&0xFF, (lerpB>>8)&0xFF, scale );
		LinearLerpByte( b, (lerpA)&0xFF, (lerpB)&0xFF, scale );
		result = (r<<16) | (g<<8) | b;
	}
	inline
	void LinearLerpNiPiont3( Vector& result, const Vector& lerpA, const Vector& lerpB, flt32 scale ) {
		
		result = lerpA + (lerpB - lerpA) * scale;
		
	}
};

////////////////////////////////////////////////////////////////////////////////
CNdlShapeRes::CNdlShapeRes(bool isCulled)
:m_culled(isCulled)
{
	m_pVB = 0;
	m_pVBLOD2 = 0;
// 	m_terrainVertex = NULL;
// 	m_LOD2Vertex = NULL;
	m_liquidVertex = NULL;
}

CNdlShapeRes::~CNdlShapeRes()
{
	ReleaseTerrainData();
	ReleaseTerrainLODData();
}

CNdlShapeRes::WaterVertex* CNdlShapeRes::CreateLiquidVertex()
{
	if (m_liquidVertex != NULL)
		DeleteLiquidVertex();

	m_liquidVertex = MeDefaultNew WaterVertex[CHUNK_LIQUID_VERTEX_NUMBER];
	return m_liquidVertex;
}

CNdlShapeRes::WaterVertex* CNdlShapeRes::GetLiquidVertex() 
{
	return m_liquidVertex;
}

void CNdlShapeRes::DeleteLiquidVertex()
{
	SAFE_DELETE(m_liquidVertex);
}

void CNdlShapeRes::ReleaseTerrainData()
{
	SafeRelease(m_pVB);
// 	if (m_terrainVertex != NULL)
// 	{
// 		delete [] m_terrainVertex;
// 		m_terrainVertex = NULL;
// 	}
	if (m_liquidVertex != NULL)
	{
		delete [] m_liquidVertex;
		m_liquidVertex = NULL;
	}
}

void CNdlShapeRes::ReleaseTerrainLODData()
{
// 	if (m_LOD2Vertex != NULL)
// 	{
// 		delete [] m_LOD2Vertex;
// 		m_LOD2Vertex = NULL;
// 	}
	SafeRelease(m_pVBLOD2);
}

void CNdlStaticModelRes::IncRefCount(bool bKeepOldData /*= false*/)
{
	CWorldRes::IncRefCount();
	if (!IsLoad())
	{
		LoadModel(bKeepOldData);
	}
}

void CNdlStaticModelRes::DecRefCount()
{
	CWorldRes::DecRefCount();
	if (0 == RefCount())
	{
		UnloadModel();
	}
}

////////////////////////////////////////////////////////////////////////////////
CNdlStaticModelRes::CNdlStaticModelRes()
{
	m_cloneMark		= 0;
}

CNdlStaticModelRes::~CNdlStaticModelRes()
{
	UnloadModel();
}


bool CNdlStaticModelRes::LoadModel(bool bKeepOldData /*= false*/)
{
	if( m_isLoad )
		return true;

	MexResMgr::Record* pRecord = GetMexResMgr()->CreateModel(m_name, true, bKeepOldData);
	if (pRecord && pRecord->res.pMex)
	{
	}
	else
	{
		pRecord = GetMexResMgr()->CreateModel(g_NullModelPath);
	}
// 	char path[MAX_PATH*2];
// 
// 	sprintf_s( path, MAX_PATH*2, "%s\\%s", CWorld::GetAppDataCharDir(), m_name );
	// 加载IMex模型
// 	IMex* pMex = GetEngine()->CreateMex();
// 	MexCfg* pMexCfg = MeNew MexCfg;
// 
// 	DWORD dwFlag = 0;
// 	if( GetMe3dConfig()->m_bFastLoadMex )
// 		dwFlag |= eMex_LoadFlag_FastLoad;
// 	m_isLoad = pMex->LoadFromFile( path, dwFlag );
// 
// 	if( !m_isLoad )
// 	{
// 		// 加载默认Null模型
// 		sprintf_s( path, MAX_PATH*2, "%s\\data\\SceneObject\\Common\\Null\\null.mex" , CWorld::GetAppDataCharDir());
// 		m_isLoad = pMex->LoadFromFile( path, dwFlag );
// 	}

	if (pRecord)
	{
		m_isLoad = true;
	}
	else
	{
		return false;
	}
// 	if( !m_isLoad )
// 	{
// 		pMex->Release();
// 		delete pMex;
// 		if( pMexCfg )
// 		{
// 			delete pMexCfg;
// 		}
// 		return m_isLoad;
// 	}
// 	else
	{
// 		Common::_tstring strAniFileName( path );
// 		strAniFileName = strAniFileName.MakeLower();
// 		strAniFileName.Replace( Common::_tstring( ".mex" ), Common::_tstring( ".ani" ) );
// 		if( !pMexCfg->LoadFromFile( strAniFileName.c_str() ) )
// 		{
// 			MexCfgSequence* sequence = MeNew MexCfgSequence;
// 			sequence->m_spAnimName.SetString( "none" );
// 			sequence->m_npStartFrameId.SetNumber( pMex->GetSequence()->GetStartFrameID() );
// 			sequence->m_npEndFrameId.SetNumber( pMex->GetSequence()->GetEndFrameID() );
// 			sequence->m_npHasLightTrack.SetNumber( 1 );
// 			pMexCfg->m_sequences.m_vectorSequence.push_back( sequence );
// 		}
// 
// 		int nVectorSequenceSize = pMexCfg->m_sequences.m_vectorSequence.size();
// 		for( int i = 0; i < nVectorSequenceSize; i++ )
// 		{
// 			MexCfgSequence* sequence = pMexCfg->m_sequences.m_vectorSequence[i];
// 
// 			int nFrameCount = 0;
// 			int nStartFrameID = sequence->m_npStartFrameId.GetNumber(); //动作的开始帧数
// 			int nEndFrameID = sequence->m_npEndFrameId.GetNumber(); //动作的结束帧数
// 
// 			if( pMex->GetSkeleton() )
// 			{
// 				IMexBone* pBone = pMex->GetSkeleton()->GetBone(0);
// 				if( pBone )
// 				{
// 					nFrameCount = pBone->GetFrameCount();
// 				}
// 			}
// 
// 			if( nFrameCount > 0 )
// 			{
// 				if( nStartFrameID > nFrameCount - 1 )
// 				{
// 					assert( "Very Terrible Error!!!!!!!!" && false );
// 					nStartFrameID = nFrameCount - 1;
// 				}
// 
// 				if( nStartFrameID < 0 )
// 				{
// 					assert( "Very Terrible Error!!!!!!!!" && false );
// 					nStartFrameID = 0;
// 				}
// 
// 				if( nEndFrameID > nFrameCount - 1 )
// 				{
// 					assert( "Very Terrible Error!!!!!!!!" && false );
// 					nEndFrameID = nFrameCount - 1;
// 				}
// 
// 				if( nEndFrameID < 0 )
// 				{
// 					assert( "Very Terrible Error!!!!!!!!" && false );
// 					nEndFrameID = 0;
// 				}
// 
// 				if( nStartFrameID > nEndFrameID )
// 				{
// 					assert( "Very Terrible Error!!!!!!!!" && false );
// 					nStartFrameID = nEndFrameID;
// 				}
// 			}
// 
// 			sequence->m_npStartFrameId.SetNumber( nStartFrameID );
// 			sequence->m_npEndFrameId.SetNumber( nEndFrameID );
// 		}
// 
// 
// 		IMexGeometry* pGeomtry = pMex->GetGeometry();
// 		IMexTextures* pTextures = pMex->GetTextures();
// 
// 		MexCfgAvatarSetting* pSetting = pMexCfg->m_AvatarSettings.FindByName( DEFAULT_AVATARSETTING_NAME );
// 		if( pGeomtry )
// 		{
// 			DWORD dwFlag = eMexCfg_SubsetVisible;
// 			for( int nSubset = 0; nSubset < pGeomtry->GetChunkCount(); nSubset++  )
// 			{
// 				pSetting->m_vectorSubsetFlag.push_back( dwFlag );	
// 			}
// 		}
// 		if( pTextures )
// 		{
// 			for( int nTexture = 0; nTexture < pTextures->GetTextureCount(); nTexture++ )
// 			{
// 				MexCfgAvatarSetting::ReplaceableTexture rt;
// 				strcpy( rt.szFileName, pTextures->GetTexture(nTexture)->GetName() );
// 				pSetting->m_vectorReplaceableTexture.push_back( rt );
// 			}
// 
// 		}

		// 加载完毕
		m_animctrl.ChangeModel(pRecord->nId, TRUE);
		GetMexResMgr()->DestroyModel(pRecord->nId);
		//m_animctrl.MirrorX(TRUE);
	}



	return true;
}


bool CNdlStaticModelRes::UnloadModel()
{
	if( !m_isLoad )
		return false;

	m_isLoad		= false;
	m_cloneMark		= 0;
	SetRefCount(0);
	m_animctrl.Destroy();		// 销毁MexAnimCtrl

	return true;
}


bool CNdlStaticModelRes::IsSubExist()
{
	return false;

}

sInt32 CNdlStaticModelRes::GetChildIndex( const char* pchildName )
{
	return -1;
}

void CNdlStaticModelRes::MarkClone( sInt32 nsubIndex ,bool bFlag)
{
	if (nsubIndex < 32)
	{
		if (bFlag)
		{
			m_cloneMark |= (1 << nsubIndex);
		}
		else
		{
			m_cloneMark &= (~(1 << nsubIndex));
		}
	}
}

bool CNdlStaticModelRes::IsNeedClone( sInt32 nsubIndex )
{
	if (nsubIndex <32)
	{
		return m_cloneMark & (1 << nsubIndex);
	}
	return true;
}
////////////////////////////////////////////////////////////////////////////////
CNdlTextureRes::CNdlTextureRes()
{
	m_texture	= RES_INVALID_ID;
}

CNdlTextureRes::~CNdlTextureRes()
{
	if (m_texture != RES_INVALID_ID)
	{
		if (GetEngine())
		{
			ITextureManager* pMgr = GetEngine()->GetTextureManager();
			pMgr->UnRegisterTexture(m_texture);
		}
	}
}

void CNdlTextureRes::IncRefCount()
{
	CWorldRes::IncRefCount();
	if (!IsLoad())
	{
		if (GetEngine())
		{
			char path[MAX_PATH*2];
#if _MSC_VER >= 1400
			sprintf_s( path, MAX_PATH*2, "%s\\%s", CWorld::GetAppDataCharDir(), GetName() );
#else
			sprintf( path, "%s\\%s", CWorld::GetAppDataCharDir(), lwsPath );
#endif

			ITextureManager* pMgr = GetEngine()->GetTextureManager();
			Trace( "Load texture[%s]\n", path );
			m_texture = pMgr->RegisterTexture(path,FALSE,FALSE);
			m_isLoad = true;
		}
	}
}

void CNdlTextureRes::DecRefCount()
{
	CWorldRes::DecRefCount();
	if (0 == RefCount())
	{
		if (m_texture != RES_INVALID_ID)
		{
			if (GetEngine())
			{
				m_isLoad = false;
				ITextureManager* pMgr = GetEngine()->GetTextureManager();
				pMgr->UnRegisterTexture(m_texture);
				m_texture = RES_INVALID_ID;
			}
		}
	}

}
uAlphaBit CNdlAlphaRes::m_sShadowColor = 0x99;
////////////////////////////////////////////////////////////////////////////////
CNdlAlphaRes::CNdlAlphaRes()
{
	m_maskData	= MeDefaultNew uAlphaBit[WORLD_TILE_CHUNK_ATOM_NUM*32];
// 	m_maskTetureId = RES_INVALID_ID;
}

CNdlAlphaRes::~CNdlAlphaRes()
{
	SAFE_DELETE_ARRAY( m_maskData );
// 	if (m_maskTetureId != RES_INVALID_ID)
// 	{
// 		if (GetEngine())
// 		{
// 			ITextureManager* pMgr = GetEngine()->GetTextureManager();
// 			pMgr->UnRegisterTexture(m_maskTetureId);
// 		}
// 	}
}

void CNdlAlphaRes::UpdateToTexture()
{
// 	Assert( RES_INVALID_ID != m_maskTetureId );
// 	ITextureManager* pMgr = GetEngine()->GetTextureManager();
// 	TextureDx8* pTexture = (TextureDx8*)(pMgr->GetTexture( m_maskTetureId ));
// 	if( pTexture )
// 	{
// 		pTexture->UpdateTexture( (BYTE*)m_maskData, WORLD_TILE_CHUNK_ATOM_NUM, WORLD_TILE_CHUNK_ATOM_NUM, D3DFMT_A8R8G8B8 );
// 	}

}
////////////////////////////////////////////////////////////////////////////////
CNdlMaskRes::CNdlMaskRes()
{
	m_texture	= NULL;
}

CNdlMaskRes::~CNdlMaskRes()
{
	ReleaseMask();
}

void CNdlMaskRes::ReleaseMask()
{
	if (m_texture != NULL)
	{
		m_texture->DecRef();
		m_texture->Release();
		m_texture = NULL;
	}
}
////////////////////////////////////////////////////////////////////////////////
CNdlLiquidRes::CNdlLiquidRes()
{
	m_texId	= RES_INVALID_ID;
	m_texList.clear();
}

CNdlLiquidRes::~CNdlLiquidRes()
{
	for( size_t i=0; i<m_texList.size(); i++ ) {
		SAFE_DELETE( m_texList[i] );
	}
	SAFE_DELETE( m_normalRes );

	m_texList.clear();
	m_texId		= RES_INVALID_ID;

}

bool CNdlLiquidRes::Create( const char* pathName, sInt32 texCount )
{
//	SetName( pathName );
	
	ITextureManager* pMgr = GetEngine()->GetTextureManager();

	char path[MAX_PATH*2];
	for( sInt32 i=0; i<texCount; i++ ) {
#if _MSC_VER >= 1400
		sprintf_s( path, MAX_PATH*2, "%s\\%s_%02d.tga", CWorld::GetAppDataCharDir(), pathName, (i+1) );
#else
		sprintf( path, "%s\\%s_%02d.tga", CWorld::GetAppDataCharDir(), pathName, (i+1) );
#endif

		CNdlTextureRes* res = MeNew CNdlTextureRes();
		res->SetId( m_texList.size() );
		Trace( "Load texture[%s]\n", path );
#if _MSC_VER >= 1400
		sprintf_s( res->m_name, RES_NAME_LEN, "_%02d.tga", (i+1) );
#else
		sprintf( res->m_name, "_%02d.tga", (i+1) );
#endif


		res->m_texture = pMgr->RegisterTexture(path,FALSE,FALSE);

		
		m_texList.push_back( res );
	}

	if( m_texList.size() < 1 )
		return false;

	// added, jiayi, [2009.4.23],normal
	sprintf_s( path, MAX_PATH*2, "%s\\\\Data\\Texture\\Liquid\\ocean\\WaterNormal.tga", CWorld::GetAppDataCharDir() );
	m_normalRes = MeNew CNdlTextureRes();
	m_normalRes->m_texture = pMgr->RegisterTexture( path, false,FALSE );	

// 	m_property = NiNew NiTexturingProperty();
// 	m_property->SetApplyMode( NiTexturingProperty::APPLY_MODULATE );
// 	m_property->SetBaseClampMode( NiTexturingProperty::WRAP_S_WRAP_T );
// 	m_property->SetBaseFilterMode( NiTexturingProperty::FILTER_BILERP );
// 	NiTexturingProperty::ShaderMap* shaderMap = NiNew NiTexturingProperty::ShaderMap();
// 	shaderMap->SetTexture( texture );
// 	m_property->SetShaderMap( 0, shaderMap );
// 	m_property->Update(0.0f);

	m_texId = 0;
	
	return true;
}

void CNdlLiquidRes::NextTexture()
{
	m_texId++;
	if (0 == m_texList.size())
	{
		return;
	}
	if( m_texId >= m_texList.size() )
		m_texId = 0;
}

CNdlTextureRes* CNdlLiquidRes::GetTexture()
{
	return m_texList[m_texId];
}

CNdlTextureRes*	CNdlLiquidRes::GetNormalTexture()
{
	return m_normalRes;
}
////////////////////////////////////////////////////////////////////////////////
//
//   2  ----------- 3
//	 |            / |
//	 |          /   |
//	 |        /     |
//	 |      /       |
//	 |    /         |
//	 |  /           |
//	 0 -----------  1
// unsigned short CNdlDecalRes::swFloorDecalShape::floorIndex[6] = {0,3,1,0,2,3};
CNdlDecalRes::CNdlDecalRes()
{
	m_radius		= 0.0f;
	m_Scale			= 1.0f;
	m_unitNum		= 1;

	m_unitPos[0]	= 0;
	m_unitPos[1]	= 0;

	m_position[0]	= 0.0f;
	m_position[1]	= 0.0f;
	
	m_vertexOut		= NULL;
	m_vertexIn		= NULL;

	m_isFill		= false;
	m_pDecalShape	= 0;
	m_sDecalTexID	= -1;
	m_floorDecalEnable = true;
	m_AllShapeOnFloor= false;
	m_vetexColor	= 0xffffffff;
	m_angle			= 0.f;
	m_bUseVertexBuffer = false;
	m_bUnRegisterTexture = false;
}

CNdlDecalRes::~CNdlDecalRes()
{
	SAFE_DELETE_ARRAY( m_vertexOut );
	SAFE_DELETE_ARRAY( m_vertexIn );
	delete m_pDecalShape;
	m_pDecalShape = 0;
	if (m_bUnRegisterTexture)
	{
		GetEngine()->GetTextureManager()->UnRegisterTexture(m_sDecalTexID);
	}
}

bool CNdlDecalRes::Create( const char* textureName, flt32 radius ,bool bUseVexterBuffer)
{
//	Assert( radius > WORLD_UNITSIZE * 0.5f );


	m_sDecalTexID = GetEngine()->GetTextureManager()->RegisterTexture( textureName, false ,TRUE);
	assert(m_sDecalTexID != -1 && "cannot find the decal texture.");
	
	m_bUnRegisterTexture = true;
	return Create(m_sDecalTexID,radius);
}

bool CNdlDecalRes::Create( int textureId, flt32 radius ,bool bUseVexterBuffer)
{
	Assert( NULL == m_vertexOut );
	Assert( NULL == m_vertexIn );
	m_sDecalTexID			= textureId;
	m_radius				= radius;
	m_bUseVertexBuffer		= bUseVexterBuffer;

	m_unitNum				= ((sInt32)( m_radius / WORLD_UNITSIZE ) + 1) * 2 ;
	m_vertexOut				= MeNew TChunkVertex[(m_unitNum+1)*(m_unitNum+1)];
	m_vertexIn				= MeNew TChunkVertex[m_unitNum*m_unitNum];

	m_pDecalShape = MeNew swDecalShape();

	sInt32 IndexSize		= 4*m_unitNum*m_unitNum*3;
	const uInt16 vertCount	= (m_unitNum+1)*(m_unitNum+1) + m_unitNum*m_unitNum;
	
	if (m_bUseVertexBuffer)
	{
		LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
		if (SUCCEEDED(pd3dDevice->CreateIndexBuffer(
			IndexSize*sizeof(short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
			D3DPOOL_MANAGED, &m_pDecalShape->m_pIB, 0)))
		{
			WORD* pDatas = 0;
			if (SUCCEEDED(m_pDecalShape->m_pIB->Lock(0, 0, (void**)&m_pDecalShape->pIdx, 0)))
			{
				InitIndexBuffer(vertCount);
				m_pDecalShape->m_pIB->Unlock();
			}
		}
		SUCCEEDED(pd3dDevice->CreateVertexBuffer(vertCount * sizeof(swDecalShapeVertex),
			D3DUSAGE_WRITEONLY, swDecalShapeVertex::eFVF, D3DPOOL_MANAGED,
			&m_pDecalShape->m_pVB, 0));
	}
	else
	{
		m_pDecalShape->pIdx = MeDefaultNew unsigned short[IndexSize];
		InitIndexBuffer(vertCount);
		m_pDecalShape->pVertex = MeNew swDecalShapeVertex[vertCount];
	}


// 	if (
// 		SUCCEEDED(pd3dDevice->CreateVertexBuffer(vertCount * sizeof(swDecalShapeVertex),
// 		D3DUSAGE_WRITEONLY, swDecalShapeVertex::eFVF, D3DPOOL_MANAGED,
// 		&m_pDecalShape->m_pVB, 0))
// 		)
	{
// 		if (SUCCEEDED(m_pDecalShape->m_pVB->Lock(0, 0, (void**)&m_pDecalShape->pVertex, 0)))
// 		{
// 			sInt32 id = 0;
// 			for( sInt32 y=0; y<(m_unitNum+1); y++ )	{
// 				for( sInt32 x=0;x<(m_unitNum+1);x++ ) {
// 					Assert( id < vertCount );
// 					m_pDecalShape->pVertex[id].p.x		= 0.0f;
// 					m_pDecalShape->pVertex[id].p.y		= 0.0f;
// 					m_pDecalShape->pVertex[id].p.z		= 0.0f;
// 					m_pDecalShape->pVertex[id].u		= 0.0f;
// 					m_pDecalShape->pVertex[id].v		= 0.0f;
// 					m_pDecalShape->pVertex[id].color	= m_vetexColor;
// 
// 					m_vertexOut[y*(m_unitNum+1)+x].p.z	= 0.1f;
// 					id++;
// 				}
// 				if( y < m_unitNum ) {
// 					for( sInt32 x=0;x<m_unitNum;x++ ) {
// 						m_pDecalShape->pVertex[id].p.x		= 0.0f;
// 						m_pDecalShape->pVertex[id].p.y		= 0.0f;
// 						m_pDecalShape->pVertex[id].p.z		= 0.0f;
// 						m_pDecalShape->pVertex[id].u		= 0.0f;
// 						m_pDecalShape->pVertex[id].v		= 0.0f;
// 						m_pDecalShape->pVertex[id].color	= m_vetexColor;
// 
// 						m_vertexIn[y*m_unitNum+x].p.z	= 0.1f;
// 						id++;
// 					}
// 				}
// 			}
// 			m_pDecalShape->m_pVB->Unlock();
// 		}
	}

// 	m_pDecalShape->pVertex = MeNew swDecalShapeVertex[vertCount];


	return true;

}
void CNdlDecalRes::FastRenderDecal( LPDIRECT3DDEVICE9 m_pDevice )
{
	const uInt16 vertCount	= (m_unitNum+1)*(m_unitNum+1) + m_unitNum*m_unitNum;
	sInt32 faceSize		= 4*m_unitNum*m_unitNum;
	if (m_bUseVertexBuffer)
	{
		m_pDevice->SetStreamSource(0, m_pDecalShape->m_pVB, 0, sizeof( swDecalShapeVertex ));
		m_pDevice->SetIndices(m_pDecalShape->m_pIB);
		m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertCount, 0, faceSize);
	}
	else
	{
		m_pDevice->DrawIndexedPrimitiveUP(
			D3DPT_TRIANGLELIST,
			0,
			vertCount,
			faceSize,
			(m_pDecalShape->pIdx),
			D3DFMT_INDEX16,
			(m_pDecalShape->pVertex),
			sizeof( swDecalShapeVertex ) );
	}

}

void CNdlDecalRes::Render()
{
	if (m_bUseVertexBuffer)
	{
		return;
	}	
	const uInt16 vertCount	= (m_unitNum+1)*(m_unitNum+1) + m_unitNum*m_unitNum;
	sInt32 faceSize		= 4*m_unitNum*m_unitNum;
	IRenderer* r = GetEngine()->GetRenderer();

	D3DXMATRIXA16 world;
	D3DXMatrixIdentity(&world);
	r->SetTransform( D3DTS_WORLD, (float*)&world );

	if (!m_floorDecalEnable || !m_AllShapeOnFloor)
	{
		r->DirectPushSurface(
			m_sDecalTexID,				
			-1,				
			TERRAIN_BLEND,
			swDecalShapeVertex::eFVF,
			sizeof( swDecalShapeVertex ),
			(BYTE*)(m_pDecalShape->pVertex),
			vertCount,
			(BYTE*)(m_pDecalShape->pIdx),
			faceSize,eUClamp | eVClamp | eNoMipmap | eZWriteDisable, D3DPT_TRIANGLELIST);
	}
	if (m_floorDecalEnable)
	{
		for (int i = 0; i < m_floorDecalArr.size();++i)
		{
			swFloorDecalShape& floorShape = m_floorDecalArr[i];
			if (!floorShape.m_bEnble)
			{
				continue;
			}
			r->DirectPushSurface(
				m_sDecalTexID,				
				-1,				
				TERRAIN_BLEND,
				swDecalShapeVertex::eFVF,
				sizeof( swDecalShapeVertex ),
				(BYTE*)(floorShape.floorVertex),
				4,
				(BYTE*)(floorShape.floorIndex),
				2,eUClamp | eVClamp | eNoMipmap | eZWriteDisable, D3DPT_TRIANGLELIST);
			// 		GetDrawer()->FillTri( floorShape.floorVertex[0].p, floorShape.floorVertex[1].p, floorShape.floorVertex[2].p, 0xFFFF0000 );
		}
	}
}
// #define WORLD_ORIGIN					( 32.0f * (WORLD_TILESIZE) )
// #define GlUnitFromPos(x)		( ZnFloor2Int( ((x)+WORLD_ORIGIN)/WORLD_UNITSIZE ) )

void CNdlDecalRes::SetPos( const flt32* pt2 ,float* pAngle)
{
	m_position[0]	= pt2[0] - m_radius*m_Scale;
	m_position[1]	= pt2[1] - m_radius*m_Scale;
	m_position[2]   = pt2[2];
	if (pAngle)
	{
		m_angle = *pAngle;
	}
	if (m_position[0]< 0.f)
	{
		m_position[0] = 0.f;
	}
	if (m_position[1]< 0.f)
	{
		m_position[1] = 0.f;
	}
	m_unitPos[0]	=  ZnFloor2Int((m_position[0] )/WORLD_UNITSIZE);
	m_unitPos[1]	=  ZnFloor2Int((m_position[1] )/WORLD_UNITSIZE);
	
// 	m_unitPos[0]	= GlUnitFromPos( m_position[0] );
// 	m_unitPos[1]	= GlUnitFromPos( m_position[1] );

	m_AllShapeOnFloor= false;
	if (m_floorDecalEnable)
	{
		CreateFloorShape();
	}
	if (!m_AllShapeOnFloor)
	{
		RefillHeight(); 
		if( m_isFill )
			RebuildGeometry();
	}
}

bool CNdlDecalRes::RefillHeight()
{
	m_isFill			= false;

	sInt32  startChunk[2], startUnit[2], startGlUnit[2], unitLen[2], len[2], startHeight[2];
	swRect srcRect, destRect;
	
	CWorldBuffer* worldBuffer	= SwGlobal::GetWorld()->GetWorldBuffer();
	Assert( NULL != worldBuffer );

	startGlUnit[0]		= m_unitPos[0];
	startGlUnit[1]		= m_unitPos[1];

	startHeight[0]		= 0;
	startHeight[1]		= 0;

	unitLen[0]			= m_unitNum;
	unitLen[1]			= m_unitNum;
	
	bool	isFirst		= true;

	startChunk[0]		= ( ((startGlUnit[0])%(CURRENTTILE->GetRowColumn()[0]*WORLD_TILE_CHUNK_UNIT_NUM))/WORLD_TILE_CHUNK_UNIT_NUM );
	startChunk[1]		= ( ((startGlUnit[1])%(CURRENTTILE->GetRowColumn()[1]*WORLD_TILE_CHUNK_UNIT_NUM))/WORLD_TILE_CHUNK_UNIT_NUM );
	startUnit[0]		= UnitFromGlUnit( startGlUnit[0] );
	startUnit[1]		= UnitFromGlUnit( startGlUnit[1] );
	sInt32 baseUnit		= startUnit[0];
	sInt32 baseChunk	= startChunk[0];

	//Trace( "======================================= \n" );
	for(;;) {

		CWorldChunk* worldChunk = worldBuffer->GetChunk( startChunk[0], startChunk[1] );
		
		if( isFirst ) {
			len[1]				= WORLD_TILE_CHUNK_UNIT_NUM - startUnit[1];
			if( len[1] >= unitLen[1] ) {
				len[1]			= unitLen[1];
				unitLen[1]		= 0;
				srcRect.y		= startUnit[1];
				//startUnit[1]	= startUnit[1] + len[1];
			}
			else {
				srcRect.y		= startUnit[1];
				unitLen[1]		= unitLen[1] - len[1];
			}
			unitLen[0]		= m_unitNum;
			startHeight[0]	= 0;
			destRect.y		= startHeight[1];
			isFirst			= false;
		}
		
		len[0]				= WORLD_TILE_CHUNK_UNIT_NUM - startUnit[0];
		if( len[0] >= unitLen[0] ) {
			srcRect.x		= startUnit[0];
			//startUnit[0]	= startUnit[0] + len[0];	
			isFirst			= true;
			startHeight[1]	+= len[1];
			startUnit[1]	= 0;
			startChunk[1]	= startChunk[1]+1;
			if( startChunk[1] >= CURRENTTILE->GetRowColumn()[1] ) {
				startChunk[1]	= CURRENTTILE->GetRowColumn()[1] -1 ;
			}
			len[0]			= unitLen[0];
			unitLen[0]		= 0;
			startUnit[0]	= baseUnit;
			startChunk[0]	= baseChunk;
		}
		else {
			srcRect.x		= startUnit[0];
			startUnit[0]	= 0;
			unitLen[0]		= unitLen[0] - len[0];
			startChunk[0]	= startChunk[0]+1;
			if( startChunk[0] >= CURRENTTILE->GetRowColumn()[0] ) {
				startChunk[0]	= CURRENTTILE->GetRowColumn()[0] -1;
			}
		}
		destRect.x			= startHeight[0];
		startHeight[0]		+= len[0];

		if( NULL != worldChunk ) {

			srcRect.w	= WORLD_TILE_CHUNK_UNIT_NUM+1;
			srcRect.h	= WORLD_TILE_CHUNK_UNIT_NUM+1;
			destRect.w	= m_unitNum+1;
			destRect.h	= m_unitNum+1;
			
			_CopyVertexTable( m_vertexOut, destRect, worldChunk->m_vertexOut, srcRect, len[0]+1, len[1]+1 );

			srcRect.w	= WORLD_TILE_CHUNK_UNIT_NUM;
			srcRect.h	= WORLD_TILE_CHUNK_UNIT_NUM;
			destRect.w	= m_unitNum;
			destRect.h	= m_unitNum;
			
			_CopyVertexTable( m_vertexIn, destRect, worldChunk->m_vertexIn, srcRect, len[0], len[1] );
			m_isFill = true;
		}
		else {
//			m_isFill = false;
		}

		//Trace( "Dest[%d,%d], Src[%d,%d] Len[%d,%d]\n"
		//	, destRect.x, destRect.y
		//	, srcRect.x, srcRect.y
		//	, len[0], len[1] );

		
		if( (unitLen[1]<=0) && (unitLen[0]<=0) ) {
			break;
		}
	}
	//Trace( "---------------------------------------- \n" );

	return true;
}

void CNdlDecalRes::RebuildGeometry()
{
	Assert( m_pDecalShape != NULL);



	if (m_bUseVertexBuffer)
	{
		if (SUCCEEDED(m_pDecalShape->m_pVB->Lock(0, 0, (void**)&m_pDecalShape->pVertex, 0)))
		{
			_rebuildGeometry();
			m_pDecalShape->m_pVB->Unlock();
		}
	}
	else
	{
		_rebuildGeometry();
	}

}

void CNdlDecalRes::CreateFloorShape()
{
	m_floorDecalArr.clear();
	D3DXPLANE intersectPLane;
	D3DXVECTOR3 vPos0(m_position[0] + m_radius*m_Scale,m_position[1]+ m_radius*m_Scale,m_position[2]);
	D3DXVECTOR3 vPos1(vPos0.x,vPos0.y + m_radius*m_Scale*2*0.7,m_position[2]);
	D3DXVECTOR3 vPos2(m_position[0] ,m_position[1],m_position[2]);
	D3DXVECTOR3 vPos3(m_position[0]+ m_radius*2.73*m_Scale*0.7,m_position[1],m_position[2]);
// 	D3DXVECTOR3 vPos0(m_position[0] ,m_position[1],m_position[2]);
// 	D3DXVECTOR3 vPos1(m_position[0] + m_radius*2*m_Scale,m_position[1],m_position[2]);
// 	D3DXVECTOR3 vPos2(m_position[0],m_position[1]+ m_radius*2*m_Scale,m_position[2]);
// 	D3DXVECTOR3 vPos3(m_position[0]+ m_radius*2*m_Scale,m_position[1]+ m_radius*2*m_Scale,m_position[2]);
	bool bIgnore1 = false;
	bool bIgnore2 = false;
	bool bIgnore3 = false;
	int shapeIndex = 0;
	int onShape = 0;
	int keepIndex[4] = {-1};
	bool bRet = CreateFloorShape(vPos0);
	if (bRet)
	{
		++onShape;
		keepIndex[0] = shapeIndex;
		if (IsPointInShape(&vPos1,m_floorDecalArr[shapeIndex]))
		{
			++onShape;
			bIgnore1 = true;
		}
		if (IsPointInShape(&vPos2,m_floorDecalArr[shapeIndex]))
		{
			++onShape;
			bIgnore2 = true;
		}
		if (IsPointInShape(&vPos3,m_floorDecalArr[shapeIndex]))
		{
			++onShape;
			bIgnore3 = true;
		}
		++shapeIndex;
	}
	if (!bIgnore1)
	{
		bRet = CreateFloorShape(vPos1);
		if (bRet)
		{
			++onShape;
			keepIndex[1] = shapeIndex;
			if (keepIndex[0] != -1 && IsPointInShape(&vPos0,m_floorDecalArr[shapeIndex]))
			{
				m_floorDecalArr[keepIndex[0]].m_bEnble = false;
			}
			if (!bIgnore2 && IsPointInShape(&vPos2,m_floorDecalArr[shapeIndex]))
			{
				++onShape;
				bIgnore2 = true;
			}
			if (!bIgnore3 && IsPointInShape(&vPos3,m_floorDecalArr[shapeIndex]))
			{
				++onShape;
				bIgnore3 = true;
			}
			++shapeIndex;
		}
	}
	if (!bIgnore2)
	{
		bRet = CreateFloorShape(vPos2);
		if (bRet)
		{
			++onShape;
			keepIndex[2] = shapeIndex;
			if (keepIndex[0] != -1 && IsPointInShape(&vPos0,m_floorDecalArr[shapeIndex]))
			{
				m_floorDecalArr[keepIndex[0]].m_bEnble = false;
			}
			if (keepIndex[1] != -1 && IsPointInShape(&vPos1,m_floorDecalArr[shapeIndex]))
			{
				m_floorDecalArr[keepIndex[1]].m_bEnble = false;
			}
			if (!bIgnore3 && IsPointInShape(&vPos3,m_floorDecalArr[shapeIndex]))
			{
				++onShape;
				bIgnore3 = true;
			}
			++shapeIndex;
		}
	}
	if (!bIgnore3)
	{
		bRet = CreateFloorShape(vPos3);
		if (bRet)
		{
			++onShape;
			if (keepIndex[0] != -1 && IsPointInShape(&vPos0,m_floorDecalArr[shapeIndex]))
			{
				m_floorDecalArr[keepIndex[0]].m_bEnble = false;
			}
			if (keepIndex[1] != -1 && IsPointInShape(&vPos1,m_floorDecalArr[shapeIndex]))
			{
				m_floorDecalArr[keepIndex[1]].m_bEnble = false;
			}
			if (keepIndex[2] != -1 && IsPointInShape(&vPos2,m_floorDecalArr[shapeIndex]))
			{
				m_floorDecalArr[keepIndex[2]].m_bEnble = false;
			}
		}
	}
	m_AllShapeOnFloor = (onShape == 4);

}

bool CNdlDecalRes::CreateFloorShape( D3DXVECTOR3& vPos)
{


// 	D3DXVECTOR3 vNormal;
	BspTree::SIntersect* pIntersect = SwGlobal::GetWorldPicker()->GetFloorZByXY(vPos.z + 1.0,vPos.x,vPos.y,NULL,NULL);
	if (!pIntersect)
	{
		return false;
	}
// 	D3DXVECTOR3& vIntersectPos = *(D3DXVECTOR3*)&pIntersect->pos;

	swFloorDecalShape floorShape;
// 	D3DXPLANE intersectPLane;
// 	D3DXPlaneFromPointNormal(&intersectPLane,&vIntersectPos,&vNormal);
// 	floorShape.floorVertex[0].p = D3DXVECTOR3(vIntersectPos.x,vIntersectPos.y,vIntersectPos.z + 0.01);
// 	floorShape.floorVertex[0].u = 0;
// 	floorShape.floorVertex[0].v = 0;
// 
// 	floorShape.floorVertex[1].p = D3DXVECTOR3(vIntersectPos.x+ m_radius*2*m_Scale,vIntersectPos.y,vIntersectPos.z + 0.01);
// 	GetZFromXYAndPlane(&floorShape.floorVertex[1].p,&intersectPLane);
// 	floorShape.floorVertex[1].u = 1.0;
// 	floorShape.floorVertex[1].v = 0;
// 
// 	floorShape.floorVertex[2].p = D3DXVECTOR3(vIntersectPos.x,vIntersectPos.y+ m_radius*2*m_Scale,vIntersectPos.z + 0.01);
// 	GetZFromXYAndPlane(&floorShape.floorVertex[2].p,&intersectPLane);
// 	floorShape.floorVertex[2].u = 0;
// 	floorShape.floorVertex[2].v = 1.0;
// 
// 	floorShape.floorVertex[3].p = D3DXVECTOR3(vIntersectPos.x+ m_radius*2*m_Scale,vIntersectPos.y+ m_radius*2*m_Scale,vIntersectPos.z + 0.01);
// 	GetZFromXYAndPlane(&floorShape.floorVertex[3].p,&intersectPLane);
// 	floorShape.floorVertex[3].u = 1.0;
// 	floorShape.floorVertex[3].v = 1.0;
// 	m_floorDecalArr.push_back(floorShape);

	flt32 len				= m_radius * 2.0f*m_Scale;
	for (int i = 0; i < 3; ++i)
	{
		floorShape.floorVertex[i].p = D3DXVECTOR3(pIntersect->vFacePos[i].x,pIntersect->vFacePos[i].y,pIntersect->vFacePos[i].z + 0.01);
		floorShape.floorVertex[i].u = (floorShape.floorVertex[i].p.x - m_position[0])/len;
		floorShape.floorVertex[i].v = (floorShape.floorVertex[i].p.y - m_position[1])/len;
		floorShape.floorVertex[i].color	= m_vetexColor;
		floorShape.floorIndex[i] = i;
	}

	Vector bc = pIntersect->vFacePos[2] - pIntersect->vFacePos[1]; 
	Vector ab = pIntersect->vFacePos[1] - pIntersect->vFacePos[0]; 
	Vector posFour;
	if(bc.dot(ab) > -0.01)
	{//B直角或钝角

		Vector center = (pIntersect->vFacePos[2] + pIntersect->vFacePos[0])/2;
		posFour = center*2 - pIntersect->vFacePos[1];
		floorShape.floorIndex[3] = 0;
		floorShape.floorIndex[4] = 2;
		floorShape.floorIndex[5] = 3;
	}
	else
	{
		Vector ca = pIntersect->vFacePos[0] - pIntersect->vFacePos[2]; 
		if (ab.dot(ca) > -0.01)
		{//A直角或钝角
			Vector center = (pIntersect->vFacePos[2] + pIntersect->vFacePos[1])/2;
			posFour = center*2 - pIntersect->vFacePos[0];
			floorShape.floorIndex[3] = 2;
			floorShape.floorIndex[4] = 1;
			floorShape.floorIndex[5] = 3;
		}
		else
		{//C直角或钝角
			Vector center = (pIntersect->vFacePos[0] + pIntersect->vFacePos[1])/2;
			posFour = center*2 - pIntersect->vFacePos[2];
			floorShape.floorIndex[3] = 0;
			floorShape.floorIndex[4] = 3;
			floorShape.floorIndex[5] = 1;
		}
	}
	floorShape.floorVertex[3].p = D3DXVECTOR3(posFour.x,posFour.y,posFour.z + 0.01);
	floorShape.floorVertex[3].u = (floorShape.floorVertex[3].p.x - m_position[0])/len;
	floorShape.floorVertex[3].v = (floorShape.floorVertex[3].p.y - m_position[1])/len;
	floorShape.floorVertex[3].color	= m_vetexColor;
	m_floorDecalArr.push_back(floorShape);
	return true;
}

void CNdlDecalRes::GetZFromXYAndPlane( D3DXVECTOR3* pos,D3DXPLANE* plane )
{
	if (abs(plane->c) >0.00001)
	{
		pos->z = -(plane->a*pos->x + plane->b* pos->y + plane->d)/plane->c + 0.01;
	}
	else
	{
	}
}

bool CNdlDecalRes::IsPointInShape( D3DXVECTOR3* pos,swFloorDecalShape& plane )
{
	Vector2 pos2(pos->x,pos->y);
	Vector2 tri[3];
	for (int i = 0; i < 3; ++i)
	{
		tri[i].x = plane.floorVertex[plane.floorIndex[i]].p.x;
		tri[i].y = plane.floorVertex[plane.floorIndex[i]].p.y;
	}
	if (InsideTri(tri,pos2,NULL,NULL))
	{
		return true;
	}
	for (int i = 3; i < 6; ++i)
	{
		tri[i - 3].x = plane.floorVertex[plane.floorIndex[i]].p.x;
		tri[i - 3].y = plane.floorVertex[plane.floorIndex[i]].p.y;
	}
	if (InsideTri(tri,pos2,NULL,NULL))
	{
		return true;
	}
	return false;
}

void CNdlDecalRes::SetAlpha( BYTE alpha )
{
	if (m_bUseVertexBuffer)
	{
		if (SUCCEEDED(m_pDecalShape->m_pVB->Lock(0, 0, (void**)&m_pDecalShape->pVertex, 0)))
		{
			_setalpha(alpha);
			m_pDecalShape->m_pVB->Unlock();
		}
	}
	else
	{
		_setalpha(alpha);
	}


}

void CNdlDecalRes::InitIndexBuffer( const uInt16 vertCount )
{
	unsigned short* stripBuf		= MeDefaultNew unsigned short[vertCount];
	for (unsigned short i=0; i<vertCount; i++) 
		stripBuf[i] = i; 

	Stripify<unsigned short>(stripBuf,m_pDecalShape->pIdx,m_unitNum);
	delete [] stripBuf;
	stripBuf = NULL;
}

void CNdlDecalRes::_rebuildGeometry()
{
	const uInt16 vertCount	= (m_unitNum+1)*(m_unitNum+1) + m_unitNum*m_unitNum;
	flt32 basePt[2];
	basePt[0]				= m_unitPos[0] * WORLD_UNITSIZE - WORLDORIGIN(0);
	basePt[1]				= m_unitPos[1] * WORLD_UNITSIZE - WORLDORIGIN(1);
	Assert( basePt[0] <= (m_position[0]+0.01f) );
	Assert( basePt[1] <= (m_position[1]+0.01f) );

	Vector2 UVCenterPos(m_position[0] + m_radius*m_Scale,m_position[1] + m_radius*m_Scale);//´Ë´¦µÄuv = (0.5,0.5)

	//flt32 len				= m_unitNum * WORLD_UNITSIZE;
	flt32 len				= m_radius * 2.0f*m_Scale;
	sInt32 id				= 0;

	swDecalShapeVertex* verts = m_pDecalShape->pVertex;
	for( sInt32 y=0; y<(m_unitNum+1); y++ )	
	{
		for( sInt32 x=0;x<(m_unitNum+1);x++ ) 
		{
			verts[id].p.x		= basePt[0] + WORLD_UNITSIZE*x;
			verts[id].p.y		= basePt[1] + WORLD_UNITSIZE*y;
			verts[id].p.z		= m_vertexOut[y*(m_unitNum+1)+x].height + 0.01f;
			verts[id].color	= m_vetexColor;
			if (abs(m_angle) < 0.01)
			{
				verts[id].u			= (verts[id].p.x - UVCenterPos.x) / len + 0.5;
				verts[id].v			= (verts[id].p.y - UVCenterPos.y) / len + 0.5;				
			}
			else
			{
				Vector2 deltaXY(verts[id].p.x - UVCenterPos.x,verts[id].p.y - UVCenterPos.y);
				float distance = deltaXY.length();
				flt32 Atan = GetAtan(deltaXY);

				flt32 angle = Atan - m_angle;
				verts[id].u			= distance*cos(angle) / len + 0.5;
				verts[id].v			= distance*sin(angle) / len + 0.5;			

			}

			++id;
		}
		if( y < m_unitNum ) 
		{
			for( sInt32 x=0;x<m_unitNum;x++ ) 
			{
				verts[id].p.x		= basePt[0] + WORLD_UNITSIZE * x + WORLD_UNITSIZE * 0.5f;
				verts[id].p.y		= basePt[1] + WORLD_UNITSIZE * y + WORLD_UNITSIZE * 0.5f;
				verts[id].p.z		= m_vertexIn[y*m_unitNum+x].height + 0.01f;
				verts[id].color	= m_vetexColor;
				if (abs(m_angle) < 0.01)
				{
					verts[id].u			= (verts[id].p.x - UVCenterPos.x) / len + 0.5;
					verts[id].v			= (verts[id].p.y - UVCenterPos.y) / len + 0.5;				
				}
				else
				{
					Vector2 deltaXY(verts[id].p.x - UVCenterPos.x,verts[id].p.y - UVCenterPos.y);
					float distance = deltaXY.length();
					flt32 Atan = GetAtan(deltaXY);

					flt32 angle = Atan - m_angle;
					verts[id].u			= distance*cos(angle) / len + 0.5;
					verts[id].v			= distance*sin(angle) / len + 0.5;			

				}

				++id;
			}
		}
	}
}

void CNdlDecalRes::_setalpha( BYTE alpha )
{
	m_vetexColor = (m_vetexColor & 0x00ffffff) | ((alpha << 24) & 0xff000000);
	sInt32 id = 0;
	for( sInt32 y=0; y<(m_unitNum+1); y++ )	{
		for( sInt32 x=0;x<(m_unitNum+1);x++ ) {
			m_pDecalShape->pVertex[id].color	= m_vetexColor;

			id++;
		}
		if( y < m_unitNum ) {
			for( sInt32 x=0;x<m_unitNum;x++ ) {
				m_pDecalShape->pVertex[id].color	= m_vetexColor;

				id++;
			}
		}
	}
	if (m_floorDecalEnable)
	{
		for (int i = 0; i < m_floorDecalArr.size();++i)
		{
			swFloorDecalShape& floorShape = m_floorDecalArr[i];
			if (!floorShape.m_bEnble)
			{
				continue;
			}
			for(int j = 0; j < 4;++j)
			{
				floorShape.floorVertex[j].color		= m_vetexColor;
			}
		}
	}
}

void CNdlDecalRes::CombineRenderData()
{
    const uInt16 vertCount	= (m_unitNum+1)*(m_unitNum+1) + m_unitNum*m_unitNum;
    sInt32 faceSize		= 4*m_unitNum*m_unitNum;
    if (!m_floorDecalEnable || !m_AllShapeOnFloor)
    {
        SwGlobal::GetRender()->CombineShadowDecal(m_pDecalShape->pVertex, vertCount, (unsigned short*)(m_pDecalShape->pIdx), faceSize, m_sDecalTexID);
    }
    if (m_floorDecalEnable)
    {
        for (int i = 0; i < m_floorDecalArr.size();++i)
        {
            swFloorDecalShape& floorShape = m_floorDecalArr[i];
            if (!floorShape.m_bEnble)
            {
                continue;
            }
            SwGlobal::GetRender()->CombineShadowDecal(floorShape.floorVertex, 4, (unsigned short*)(floorShape.floorIndex), 2, m_sDecalTexID);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
CNdlLightRes::CNdlLightRes()
:m_lightDir(0.f,0.f,-1.f)
,m_bLightChanged(false)
{
	m_lightAmbient	= 0x0;
	m_lightDiffuse	= 0x0;
	m_lightSpecular	= 0x0;
	m_colorSunless	= 0x0;
}

CNdlLightRes::~CNdlLightRes()
{

}

bool CNdlLightRes::Create()
{
	return true;
}

bool CNdlLightRes::LinearLerp( const CNdlLightRes* lfA, const CNdlLightRes* lfB, flt32 lerp )
{
	if( NULL == lfA ) {
		if( NULL != lfB ) {
			this->m_lightAmbient		= lfB->m_lightAmbient;
			this->m_lightDiffuse		= lfB->m_lightDiffuse;
			this->m_lightSpecular		= lfB->m_lightSpecular;
			this->m_lightDir			= lfB->m_lightDir;
		}
		return true;
	}
	if( NULL == lfB ) {
		this->m_lightAmbient		= lfA->m_lightAmbient;
		this->m_lightDiffuse		= lfA->m_lightDiffuse;
		this->m_lightSpecular		= lfA->m_lightSpecular;
		this->m_lightDir			= lfA->m_lightDir;
		return true;
	}
	LinearLerpRGB( this->m_lightAmbient, lfA->m_lightAmbient, lfB->m_lightAmbient, lerp );
	LinearLerpRGB( this->m_lightDiffuse, lfA->m_lightDiffuse, lfB->m_lightDiffuse, lerp );
	LinearLerpRGB( this->m_lightSpecular, lfA->m_lightSpecular, lfB->m_lightSpecular, lerp );

	LinearLerpNiPiont3( this->m_lightDir, lfA->m_lightDir, lfB->m_lightDir, lerp );
	
	return true;
}

////////////////////////////////////////////////////////////////////////////////
CNdlFogRes::CNdlFogRes()
{
	m_lightColor	= 0x0;
	m_lightNear		= 0.0f;
	m_lightFar		= 1.0f;
}

CNdlFogRes::~CNdlFogRes()
{

}

bool CNdlFogRes::Create()
{
	return true;
}

bool CNdlFogRes::LinearLerp( const CNdlFogRes* lfA, const CNdlFogRes* lfB, flt32 lerp )
{
	if( NULL == lfA ) {
		if( NULL != lfB ) {
			this->m_lightColor	= lfB->m_lightColor;
			this->m_lightNear	= lfB->m_lightNear;
			this->m_lightFar	= lfB->m_lightFar;
		}
		return true;
	}
	if( NULL == lfB ) {
		this->m_lightColor	= lfA->m_lightColor;
		this->m_lightNear	= lfA->m_lightNear;
		this->m_lightFar	= lfA->m_lightFar;
		return true;
	}

	LinearLerpRGB( this->m_lightColor, lfA->m_lightColor, lfB->m_lightColor, lerp );
	LinearLerpRGB( this->m_lightColor, lfA->m_lightColor, lfB->m_lightColor, lerp );

	this->m_lightNear	= lfA->m_lightNear + (lfB->m_lightNear - lfA->m_lightNear) * lerp;
	this->m_lightFar	= lfA->m_lightFar + (lfB->m_lightFar - lfA->m_lightFar) * lerp;

	//this->m_lightNear	= lfA->m_lightNear + (lfB->m_lightNear - lfA->m_darkNear) * lerp;
	//this->m_lightFar	= lfA->m_lightFar + (lfB->m_darkFar - lfA->m_darkFar) * lerp;

	return true;
}

////////////////////////////////////////////////////////////////////////////////
CNdlEnvRes::CNdlEnvRes() 
{
	m_lightId	= RES_INVALID_ID;
	m_fogId		= RES_INVALID_ID;
}

CNdlEnvRes::~CNdlEnvRes()
{

}


////////////////////////////////////////////////////////////////////////////////
CDoodadRes::CDoodadRes()
:m_Object(NULL)
{
}

CDoodadRes::~CDoodadRes()
{
}

////////////////////////////////////////////////////////////////////////////////
void CDoodadRes::IncRefCount()
{
	CWorldRes::IncRefCount();
	if (!IsLoad())
	{
		LoadModel();
	}
}

void CDoodadRes::DecRefCount()
{
	CWorldRes::DecRefCount();
	if (0 == RefCount())
	{
		UnloadModel();
	}
}



bool CDoodadRes::LoadModel( )
{
	if(!GetEngine()->GetRenderer()->GetRealDevice())
		return false;
	if( m_isLoad )
		return true;
	TObjectInfo* pkObject = MeNew TObjectInfo();
	if( !pkObject->LoadFromFile( m_name ) )
	{
		delete pkObject;
		return false;

	}
// 	char path[MAX_PATH*2];
// 
// #if _MSC_VER >= 1400
// 	sprintf_s( path, MAX_PATH*2, "%s\\%s", CWorld::GetAppDataCharDir(), m_name );
// #else
// 	sprintf( path, "%s\\%s", CWorld::GetAppDataCharDir(), m_name );
// #endif
// 	_strlwr(path);
// 	Trace( "Load doodad file[%s] \n", m_name );
// 
// 	TObjectInfo* pkObject = MeNew TObjectInfo();
// 	if ( strstr( path, ".mex" ) )
// 	{
// 		if( !pkObject->LoadFromFile( path ) ){
// 
// 			sprintf_s( path, MAX_PATH*2, "%s\\data\\SceneObject\\Common\\Null\\null.mex", CWorld::GetAppDataCharDir() );
// 			if( !pkObject->LoadFromFile( path ) ) {
// 				Trace( "<<<ERROR>>> load [%s] \n", path );
// 				delete pkObject;
// 				return false;
// 			}
// 		}
// 	}
	
	m_isLoad = true;
	pkObject->model->SetPosition( 0.f, 0.f, 0.f );

	m_Object = pkObject;
	
	return true;
}

bool CDoodadRes::UnloadModel()
{
	if( !m_isLoad )
		return false;

	m_isLoad	= false;
	SAFE_DELETE(m_Object);
	return true;
}

int CDoodadRes::GetPartCount()
{
	if (GetModel()
		&&GetModel()->model&&
		GetModel()->model->GetMex()
		&&GetModel()->model->GetMex()->GetGeometry())
	{
		return GetModel()->model->GetMex()->GetGeometry()->GetChunkCount();
	}
	return 0;
}

CTransportResBase::CTransportResBase(sInt32 id )
{
	m_ntargetID		= id;

}


CTransportRes::CTransportRes()
{
	m_fLeft			= 0.f;
	m_fTop			= 0.f;
	m_fRight		= 0.f;
	m_fBottom		= 0.f;
	m_ntargetID		= 0;

	m_dwDesMapID	= -1;
	m_entranceId	= -1;


}

CTransportResBase::~CTransportResBase()
{
}

void CTransportResBase::ApplyTransform()
{

}

TObjectInfo* CTransportResBase::GetModel()
{
	return NULL;
}

void CTransportResBase::AttachModel()
{

}

void CTransportResBase::DetachModel()
{

}

CTargetRes::CTargetRes(  )
{
	m_fTargetPosX	= 0.f;
	m_fTargetPosY	= 0.f;
	m_ntargetID		= 0;
	m_bRelive = false;
	m_nReliveId = -1;
	m_nReliveMapId = -1;
}

CTargetRes::CTargetRes(bool bRelive)
{
	m_fTargetPosX	= 0.f;
	m_fTargetPosY	= 0.f;
	m_ntargetID		= 0;

	m_nReliveId = -1;
	m_bRelive = bRelive;
	m_nReliveType = Relive_Default;
	m_nReliveMapId = -1;

}




void CNdlZoneRes::SetMuiscPath(const char* val )
{
	if (val)
	{
		strcpy( m_muiscPath, val );
	}
}

const RECT* CNdlZoneRes::GetFontRect() const 
{ 
	if (m_fontRect.left == 0 && m_fontRect.top == 0 && m_fontRect.left == 0 && m_fontRect.bottom)
	{
		return NULL;
	}

	return &m_fontRect; 
}

void CNdlZoneRes::SetFontRect(const RECT* pRect)
{
	if (!pRect)
	{
		return;
	}

	m_fontRect.left = pRect->left;
	m_fontRect.top = pRect->top;
	m_fontRect.right = pRect->right;
	m_fontRect.bottom = pRect->bottom;
}

CNdlZoneRes::CNdlZoneRes()
{
	memset(m_muiscPath,0,sizeof(char)*MAX_PATH);
	
}

CNdlZoneRes::~CNdlZoneRes()
{

}


CSoundPointRes::CSoundPointRes()
{
	memset(m_muiscPath,0,sizeof(char)*MAX_PATH);
	m_fMinDistance = 3;
	m_fMaxDistance = 50;

}
CSoundPointRes::~CSoundPointRes()
{

}
void CSoundPointRes::SetMuiscPath( const char* val )
{
	if (val)
	{
		strcpy( m_muiscPath, val );
	}
}

