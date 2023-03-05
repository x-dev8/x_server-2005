
#include "Me3d/Me3d.h"

#include "Me3d/Model/Mex2.h"
#include "Me3d/StdioEx.h"
//#include "shader.h"
#include "Me3d/emitter.h"
#include "Me3d/camera.h"
#include "Me3d/config.h"
#include "Me3d/MathLib.h"
#include "Me3d/BaseGraphics.h"
#include "Me3d/Decal.h"
#include "Me3d/Global.h"
#include "Me3d/Spline.h"
//#include "Me3d/world.h"
//#include "Me3d/light.h"
//#include "engine.h"
#include "FuncPerformanceLog.h"
#include "datachunkwriter.h"
#include "helper.h"
//#include "CSVolumeMex2Src.h"
#include "Me3d/Engine/Engine.h"
#include "Me3d/Engine/RendererDx8.h"
#include "Me3d/Engine/EngineInstance.h"
#include "FilePath.h"
#include "Me3d/MathLib.h"

// #include "VirtualFileSystem/vfs.h"
#include "Dxsdk/d3dx9.h"
#include "Me3d/Engine\RendererDX.h"
#include "MeTerrain/SwGlobal.h"

#include "../filepacket/packet_interface.h"
//#include "Launcher/DataLauncher.h"
#include "Me3d/Shader.h"
#include "Me3d/ShaderManager.h"

#include "Me3d/Engine/MeRenderManager.h"

extern void MakeMatrix( Vector& v, Quaternion& q, MeMatrix& m );
extern void ConvertMatrixToTranslationAndRotation( MeMatrix& m, Vector& v, Quaternion& q );
// extern FileIO::CVFS	g_ModelVfs;
// extern FileIO::CVFS	g_WorldVfs;
#define MAX_CACHE_ACTION 20


#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)       { if(p) { delete [] (p);     (p)=NULL; } }
#endif


void MakeLower( char string[] )
{
	for( int i = 0; ; i++ )
	{
		if( string[i] == 0 )
			return;
		if( string[i] >= 'A' && string[i] <= 'Z' )
			string[i] += 32;
	}
}

Mex2Action::Mex2Action():
nStartFrame(0),
nEndFrame(0),
bLoaded(FALSE),
pbyMatrixBuffer(NULL),
pbyKeyFrameBuffer(NULL),
pbVisiBuffer(NULL),
nNumFrame(0),
dwLastUseTime(0),
nRef(0)
{
	guardfunc;
	unguard;
}
void Mex2Action::Use()
{
	nRef++;
	dwLastUseTime = HQ_TimeGetTime();
} 
void Mex2Action::Unload()
{
	if( pbyKeyFrameBuffer )
	{
		delete[] pbyKeyFrameBuffer;
		pbyKeyFrameBuffer = NULL;
	}
	if( pbyMatrixBuffer )
	{
		delete[] pbyMatrixBuffer;
		pbyMatrixBuffer = NULL;
	}
	if( pbVisiBuffer )
	{
		delete[] pbVisiBuffer;
		pbVisiBuffer = NULL;
	}
	Loaded(FALSE);
	nRef = 0;
	dwLastUseTime = 0;
}
Mex2ActionList::Mex2ActionList():
nActionCache(-1),
pMex(NULL)
//nNumMexFrame(0)
{
	guardfunc;
	unguard;
}
BOOL Mex2ActionList::AddAction( int nStartFrame, int nEndFrame )
{
	Mex2Action* act = MeNew Mex2Action;
	act->nStartFrame = nStartFrame;
	act->nEndFrame = nEndFrame;
	act->nNumFrame = act->nEndFrame-act->nStartFrame+1;
	actions.push_back( act );
	return TRUE;
}
int	Mex2ActionList::FindRecentlyMostUnusedActionInLoaded()
{
	// 没有缓冲
	if( actions.size() == 0 ||
		LoadedActions.size() == 0 )
		return -1;

	int nFound = 0;;
	if( LoadedActions[nFound] < 0 || 
		LoadedActions[nFound] >= actions.size() )
	{
		assert( false );
		return -1;
	}
	DWORD dwTime = actions[LoadedActions[nFound]]->dwLastUseTime;
	for( int nAction = 1; nAction < LoadedActions.size(); nAction++ )
	{
		int nId = LoadedActions[nAction];
		if( nId < 0 || nId >= actions.size() )
		{
			assert( false );
			continue;
		}
		if( dwTime > actions[nId]->dwLastUseTime )
		{
			dwTime = actions[nId]->dwLastUseTime;
			nFound = nAction;
		}
	}
	return nFound;
}
Mex2Action* Mex2ActionList::GetAction( int nFrameId )
{
	guardfunc;
	if( nFrameId < 0 || !pMex || nFrameId > pMex->m_pSequence->GetEndFrameID()+1 )
	{
		assert( false );
		return NULL;
	}
	//int nNumActionFrame = 0;
	//for( int nAction = 0; nAction < actions.size(); nAction++ )
	//{
	//	nNumActionFrame += actions[nAction]->nNumFrame;
	//}
	//int nNumLoadedFrame = 0;
	//for( int nAction = 0; nAction < LoadedActions.size(); nAction++ )
	//{
	//	int nId = LoadedActions[nAction];
	//	nNumLoadedFrame += actions[nId]->nNumFrame;
	//}
	//int nNumTotalFrame = pMex->m_pSequence->GetEndFrameID();

	// 首先在高速缓冲中查找
	if( nActionCache != -1 )
	{
		Mex2Action* act = actions[nActionCache];
		if( nFrameId >= act->nStartFrame &&
			nFrameId <= act->nEndFrame )
		{
			assert( act->IsLoaded() );
			act->Use();
			return act;
		}
	}
	// 在缓冲中查找
	for( int nAction = 0; nAction < LoadedActions.size(); nAction++ )
	{
		int nId = LoadedActions[nAction];
		if( nId < 0 || nId >= actions.size() )
		{
			assert(false);
			continue;
		}
		Mex2Action* act = actions[nId];
		if( nFrameId >= act->nStartFrame &&
			nFrameId <= act->nEndFrame )
		{
			nActionCache = nId;
			assert( act->IsLoaded() );
			act->Use();
			return act;
		}
	}
	// 在所有列表中查找
	for( int nAction = 0; nAction < actions.size(); nAction++ )
	{
		Mex2Action* act = actions[nAction];
		if( nFrameId >= act->nStartFrame &&
			nFrameId <= act->nEndFrame )
		{
			assert( act->pbyKeyFrameBuffer == NULL );
			assert( act->pbyMatrixBuffer == NULL );
			// 此时应该没有载入到缓冲
			if( !pMex->LoadAction( act ) )
			{
				assert( false );
				continue;
			}
			assert( act->IsLoaded() );
			// 如果多于N个载入的动作
			if( LoadedActions.size() >= MAX_CACHE_ACTION )
			{
				// 淘汰一个
				int nFound = FindRecentlyMostUnusedActionInLoaded();
				if( nFound != -1 )
				{
					actions[LoadedActions[nFound]]->Unload();
				}
				LoadedActions.erase( LoadedActions.begin()+nFound );
			}
			LoadedActions.push_back( nAction );
			
			nActionCache = nAction;
			act->Use();
			return act;
		}
	}
	// 如果还是没有找到这个action,我们生成一个action
	// 这个action从frameid 到frameid+33
	//if( pMex->m_pSequence->GetEndFrameID() <= 200 )
	//{
	//	AddAction( 0, pMex->m_pSequence->GetEndFrameID()-1 );
	//}
	//else
	{
		int nStartFrame = nFrameId;
		int nEndFrame = nFrameId+33;
		if( nEndFrame >= pMex->m_pSequence->GetEndFrameID() )
			nEndFrame = pMex->m_pSequence->GetEndFrameID()-1;
		if( nEndFrame < nStartFrame )
			nEndFrame = nStartFrame;
		AddAction( nStartFrame, nEndFrame );
	}
	
	return GetAction( nFrameId );
	unguard;
}
Mex2ActionKeyframe* Mex2ActionList::GetKeyframe( int nBoneId, int nFrameId )
{
	guardfunc;

	Mex2Action* pAction = GetAction( nFrameId );
	if( !pAction )
	{
		assert( false );
		return NULL;
	}
	if( !pAction->IsLoaded() )
	{
		assert( false );
		return NULL;
	}

	Mex2ActionKeyframe* pKeyframe = (Mex2ActionKeyframe*)pAction->pbyKeyFrameBuffer;
	int f = nFrameId-pAction->nStartFrame;
	return &pKeyframe[nBoneId*pAction->nNumFrame+f];

	unguard;
}
BOOL Mex2ActionList::IsVisible( int nBoneId, int nFrameId )
{
	guardfunc;
	Mex2Action* pAction = GetAction( nFrameId );
	if( !pAction )
		return TRUE;
	if( !pAction->pbVisiBuffer )
		return TRUE;
	BOOL* pbVisi = pAction->pbVisiBuffer;
	int f = nFrameId-pAction->nStartFrame;
	return pbVisi[nBoneId*pAction->nNumFrame+f];
	unguard;

}
float* Mex2ActionList::GetMatrices( int nBoneId, int nFrameId )
{
	guardfunc;
	Mex2Action* pAction = GetAction( nFrameId );
	if( !pAction )
		return FALSE;
	//if( pAction->pbyKeyFrameBuffer )
	//{
	//	Vector v;
	//	Quaternion q;
	//	GetTranslationAndRotation( fKeyTime, nFps, v, q );
	//	MakeMatrix( v, q, m );
	//	return (float*)&m;
	//}
	MeMatrix* pMatrix = (MeMatrix*)pAction->pbyMatrixBuffer;
	int f = nFrameId-pAction->nStartFrame;
	return (float*)&pMatrix[nBoneId*pAction->nNumFrame+f];

	//return NULL;
	unguard;
}
void Mex2ActionList::Destroy()
{
	guardfunc;
	for( int nAction = 0; nAction < actions.size(); nAction++ )
	{
		Mex2Action* act = actions[nAction];
		act->Unload();
		delete act;
	}
	actions.clear();
	LoadedActions.clear();
	nActionCache = -1;
	unguard;
}

void Mex2Texture::SetName( const char* pszName )
{
	guardfunc;
	HelperFunc::SafeNCpy( szName, pszName, MAX_PATH );
	unguard;
}

BOOL Mex2Version::Read( Mex2Pointer inP, int nSize )
{
	guardfunc;
	Mex2Pointer p(inP.p);
	dwVersion = *p.dw++;
	return TRUE;
	unguard;
}

BOOL Mex2Textures::Read( Mex2Pointer inP, int nSize )
{
	guardfunc;
	Mex2Pointer p(inP.p);
	//if( MEX_TAG( *p.dw ) != 'texs' )
	//	return FALSE;
	//p.dw++;
	int nTextureCount = *p.i++;
	//pTextures = p.tex;
	//p.tex += nTextureCount;
	//vectorTexture.re
	for( int i = 0; i < nTextureCount; i++ )
	{
		Mex2Texture texture;
		texture.SetName( (const char*)p.c );
		vectorTexture.push_back( texture );
		p.c += MAX_PATH;
	}
	return TRUE;
	unguard;
}
IMexTexture* Mex2Textures::AddTexture()
{
	guardfunc;
	Mex2Texture texture;
	texture.SetName( "" );
	vectorTexture.push_back( texture );
	return &vectorTexture[vectorTexture.size()-1];
	unguard;
}
IMexTexture* Mex2Textures::GetTexture( int i )
{ 

	guardfunc;

	if( i < 0 || i >= vectorTexture.size() )
		return NULL;
	return &vectorTexture[i]; 
	unguard;
}
int Mex2Textures::GetRenderTextureID( int i )
{ 
	guardfunc;
	if( i < 0 || i >= vectorRenderTextureId.size() )
		return -1;
	return vectorRenderTextureId[i]; 
	unguard;
}
BOOL Mex2MtlAnim::Read( Mex2Pointer inP, int nSize )
{
	guardfunc;
	Mex2Pointer p(inP.p);
	bTiling = *p.i++;
	nUTile = *p.i++;
	nVTile = *p.i++;
	nStartFrame = *p.i++;
	fPlaybackRate = *p.f++;
	nKeyCount = *p.i++;
	if( nKeyCount > 0 )
	{
// 		pKeys = p.colorKey;
		pKeys = MeNew Mex2ColorKey[nKeyCount];
		memcpy(pKeys,p.colorKey,sizeof(Mex2ColorKey)*nKeyCount);
		p.colorKey += nKeyCount;
	}

	// 遍历所有材质帧, 检查是否有Alpha变化
	for (int i = 0; i < nKeyCount; ++i)
	{
		if (i > 1)
		{
			if (pKeys[i].alpha != pKeys[i - 1].alpha)
			{
				bHasAlphaChange = true;
				break;
			}
		}
	}
	return TRUE;
	unguard;
}

BOOL Mex2MtlAnims::Read( Mex2Pointer inP, int nSize )
{
	guardfunc;
	Mex2Pointer p(inP.p);
	while( p.c < inP.c+nSize )
	{
		switch( MEX_TAG( *p.dw ) )
		{
		case 'clra':
			{
				p.dw++;
				int size = *p.i++;
				Mex2MtlAnim* track = MeNew Mex2MtlAnim;
				track->Read( p.c, size );
				vectorColorTrack.push_back( track );
				p.c += size; 
			}
			break;
		default:
			{
				p.dw++;
				int size = *p.i++;
				p.c += size; 
			}
			break;
		}
	}
	return TRUE;
	unguard;
}
BOOL Mex2Layer::IsSameLayer( IMexLayer* pLayer )
{
	guardfunc;
	if( !pLayer )
	{
		assert( false );
		return FALSE;
	}
	if( GetAlpha() != pLayer->GetAlpha() )
		return FALSE;
	if( GetBlendMode() != pLayer->GetBlendMode() )
		return FALSE;
	if( GetFlag() != pLayer->GetFlag() )
		return FALSE;
	if( GetTextureID() != pLayer->GetTextureID() )
		return FALSE;
	return TRUE;
	unguard;
}
BOOL Mex2Material::Read( Mex2Pointer inP, int nSize )
{
	guardfunc;
	Mex2Pointer p(inP.p);
	while( p.c < inP.c+nSize )
	{
		switch( MEX_TAG( *p.dw ) )
		{
		case 'lays':
			{
				p.dw++;
				int size = *p.i++;
				Mex2Pointer s(p.c);
				int nLayerCount = *s.i++;
				//pLayers = p.layer;
				//p.layer += nLayerCount;
				vectorLayer.reserve( nLayerCount );
				vectorLayer.resize( nLayerCount );
				for( int nLayer = 0; nLayer < nLayerCount; nLayer++ )
				{
					Mex2Layer* pLayer = &vectorLayer[nLayer];
					pLayer->m_nBlendMode = *s.i++;
					pLayer->m_dwFlag = *s.dw++;
					pLayer->m_nTextureID = *s.i++;
					pLayer->m_fAlpha = *s.f++;
				}
				
				//for( int i = 0; i < nLayerCount; i++ )
				//{
				//	if( pLayers[i].dwFlag & MEX2_ZWRITEENABLE )
				//	{
				//		int k = 0;
				//	}
				//}

				p.c += size;
			}
			break;
		case 'cras':
			{
				p.dw++;
				int size = *p.i++;
				colorTracks.Read( p, size );
				p.c += size; 
			}
			break;
		default:
			{
				p.dw++;
				int size = *p.i++;
				p.c += size; 
			}
			break;
		}
	}
	//if( colorTracks.vectorColorTrack.size() > 0 )
	//{
	//	assert( GetLayerCount() == colorTracks.vectorColorTrack.size() &&
	//		"layer count must equal color track count" );
	//}
	/*if( MEX_TAG( *p.dw ) != 'lays' )
		return FALSE;
	p.dw++;
	// skip size
	p.i++;
	
	int nLayerCount = *p.i++;
	pLayers = p.layer;
	p.layer += nLayerCount;*/
	return TRUE;
	unguard;
}

IMexLayer* Mex2Material::AddLayer()
{
	guardfunc;
	Mex2Layer layer;
	vectorLayer.push_back( layer );
	return &vectorLayer[vectorLayer.size()-1];
	unguard;
}
BOOL Mex2Material::IsSameMtl( IMexMaterial* pMtl , DWORD dwFlag )
{
	guardfunc;
	if( !pMtl )
	{
		assert( false );
		return FALSE;
	}
	if( GetLayerCount() != pMtl->GetLayerCount() )
		return FALSE;
	for( int nLayer = 0; nLayer < GetLayerCount(); nLayer++ )
	{
		IMexLayer* pSrcLayer = GetLayer(nLayer);
		IMexLayer* pDstLayer = pMtl->GetLayer(nLayer);
		if( !pSrcLayer->IsSameLayer( pDstLayer ) )
			return FALSE;
	}
	return TRUE;
	unguard;
}

IMexMaterial* Mex2Materials::GetMtl( int nMtl )
{ 
	guardfunc;
////	//CSALocker locker(this);
	if( nMtl < 0 || nMtl >= vectorMtl.size() )
		return NULL;
	return vectorMtl[nMtl]; 
	unguard;
}
BOOL Mex2Materials::Read( Mex2Pointer inP, int nSize )
{
	guardfunc;
////	//CSALocker locker(this);
	Mex2Pointer p(inP.p);

	while( p.c < inP.c+nSize )
	{
		switch( MEX_TAG( *p.dw ) )
		{
		case 'matl':
			{
				p.dw++;
				int size = *p.i++;
				Mex2Material* mtl = MeNew Mex2Material;
				mtl->Read( p, size );
				vectorMtl.push_back( mtl );
				p.c += size;
			}
			break;
		default:
			{
				p.dw++;
				int size = *p.i++;
				p.c += size; 
			}
			break;
		}
	}
	
	return TRUE;
	unguard;
}
BOOL Mex2Material::Prepare( IRenderer* pRenderer, 
								IReplaceableTextureProj* pTextureProj, 
								DWORD* pdwFlag,
								int* pnTextureID )
{
	guardfunc;
	DWORD dwFlag = 0;
	short stUseTexId = -1;
	BOOL bAlphaBlend = FALSE;
	BOOL bAlphaTest = FALSE;
	DWORD dwColor = 0xffffffff;
	DWORD dwBlendMode = MEX2_MODULATE2X;
	assert( GetLayerCount() > 0 && "mex geomchunk render error, mtl layer count must > 0" );
	if( GetLayer(0)->GetFlag() & MEX2_TWOSIDED )
		dwFlag |= eTwoSided;



	int nLocalTextureId = GetLayer(0)->GetTextureID();// pMtl->pLayers[0].nTextureId;
	if( pTextureProj )
	{
		stUseTexId = pTextureProj->GetRenderTextureID( nLocalTextureId );

	}

	IMexLayer* pLayer0 = GetLayer(0);
	DWORD dwLayerFlag = pLayer0->GetFlag();
	if( dwLayerFlag & MEX2_ALPHABLEND )
	{
		bAlphaBlend = TRUE;
		if( !( dwLayerFlag & MEX2_ZWRITEENABLE )  )
			dwFlag |= eZWriteDisable;
	}
	if( dwLayerFlag & MEX2_ALPHATEST )
	{
		bAlphaTest = TRUE;
	}
	if( dwLayerFlag & MEX2_SPECULARENABLE )
	{
	}


	switch( dwBlendMode )
	{
	case MEX2_MODULATE:
		dwFlag |= eOpModulate1X;
		break;
	case MEX2_MODULATE2X:
		dwFlag |= eOpModulate2X;
		break;
	case MEX2_ADD:
		dwFlag |= eOpAdd;
		break;
	default:
		dwFlag |= eOpModulate1X;
		break;
	}

// 	dwFlag |= eMipmapLinear;


	if( bAlphaTest )
	{
		bAlphaBlend = FALSE;
		dwFlag |= eAlphaTest;
	}

	if( bAlphaBlend )
	{
		dwFlag |= eTwoSided;
		dwFlag |= eAlphaBlend;
		dwFlag |= eSortByFarZ;
	}

	//pRenderer->SetTextureId( stUseTexId, 0 );
	//pRenderer->SetShaderId( MEX2_SHADER );

	if( pnTextureID )
		*pnTextureID = stUseTexId;
	if( pdwFlag ) 
		*pdwFlag = dwFlag;
	return TRUE;
	unguard;	
	
}
int Mex2Geometry::GetChunkCount()
{
	guardfunc;
////	//CSALocker locker(this);
	return vectorChunk.size();
	unguard;
}
IRenderable* Mex2Geometry::GetChunk( int nChunkId )
{
	guardfunc;
////	//CSALocker locker(this);
	if( nChunkId < 0 || nChunkId >= vectorChunk.size() )
		return NULL;
	return vectorChunk[nChunkId];
	unguard;
}
//Mex2GeoChunk* Mex2Geometry::FindChunkByName( const char* pszName )
IRenderable* Mex2Geometry::FindChunkByName( const char* pszName )
{
	guardfunc;
////	//CSALocker locker(this);
	for( int i = 0; i < vectorChunk.size(); i++ )
	{
		if( !vectorChunk[i]->GetName() )
			continue;
		if( _stricmp( pszName, vectorChunk[i]->GetName() ) ==0 )
			return vectorChunk[i];
	}
	return NULL;
	unguard;
}
BOOL Mex2Geometry::Read( Mex2Pointer inP, int nSize )
{
	guardfunc;
////	//CSALocker locker(this);
	//if (nSize <= 0)
	//{
	//	return false;
	//}
	Mex2Pointer p(inP.p);
	if(pSrcMex->GetVersion() >= 103)//added by jiayi.发布版本需要去掉这行.使老版本mex也同样不兼容
		*p.dw++;//added,jiayi,[09.04.07]
	while( p.c < inP.c+nSize )
	{
		switch( MEX_TAG( *p.dw ) )
		{
		case 'chks':
			{
				p.dw++;
				int size = *p.i++;
				CMexChunkData* chunkData = MeNew CMexChunkData;
				//   added 2005.09.27
				chunkData->SetChunkID(vectorChunkData.size());
				//   added 2003.10.14
				
				static int iii = 0;
				iii ++;
				if( iii == 16 )
				{
					int kkk = 0;
				}
				chunkData->Read( p, size, pSrcMex->GetVersion() );

				
				vectorChunkData.push_back( chunkData );
				
				
				p.c += size; 
			}
			break;
		default:
			{
				p.dw++;
				int size = *p.i++;
				p.c += size; 
				break;
			}
			break;
		}

	}
	return TRUE;
	unguard;
}

BOOL Mex2Bone::SnapShotFromFile( FILE* fp, int nSize, DWORD dwFlag )
{
	guardfunc;
	int nByte = 0;

	fread( szName, MEX2_MAX_NAME, 1, fp );
	nByte += MEX2_MAX_NAME;
	fread( &nParentId, sizeof(int), 1, fp );
	nByte += sizeof(int);
	fread( &nChildCount, sizeof(int), 1, fp );
	nByte += sizeof(int);
	if( nChildCount > 0 )
	{
		pnChildIds = MeDefaultNew int[nChildCount];
		fread( pnChildIds, sizeof(int)*nChildCount, 1, fp );

	}

	nByte += sizeof(int)*nChildCount;
	int nNumFrame = 0;
	while( nByte < nSize )
	{
		DWORD dwChunkName = 0;
		int nChunkSize = 0;
		fread( &dwChunkName, sizeof(DWORD), 1, fp );
		nByte += sizeof(DWORD);
		fread( &nChunkSize, sizeof(int), 1, fp );
		nByte += sizeof(int);
		switch( MEX_TAG( dwChunkName ) )
		{
		case 'trck':
			{
				fread( &nFrameCount, sizeof(int), 1, fp );
				MeMatrix frame0;
				fread( &frame0, sizeof(MeMatrix), 1, fp );
				fseek( fp, sizeof(MeMatrix)*(nFrameCount-1), SEEK_CUR );
				D3DXMatrixInverse( (D3DXMATRIX*)&matFrame0Inv, NULL, (D3DXMATRIX*)&frame0 );
			}
			break;
		case 'trk2':
			{
				fread( &nFrameCount, sizeof(int), 1, fp );

				Vector vTrans;
				Quaternion qRot;
				fread( &vTrans, sizeof(Vector), 1, fp );

				fseek( fp, sizeof(Vector)*(nFrameCount-1), SEEK_CUR );


				fread( &qRot, sizeof(Quaternion), 1, fp );

				fseek( fp, sizeof(Quaternion)*(nFrameCount-1), SEEK_CUR );

				MeMatrix m;
				MakeMatrix( vTrans, qRot, m );
				D3DXMatrixInverse( (D3DXMATRIX*)&matFrame0Inv, NULL, (D3DXMATRIX*)&m );
				bHasKeyframe = TRUE;
			}
			break;
		default:
			{
				fseek( fp, nChunkSize, SEEK_CUR );
				break;
			}
		}
		nByte += nChunkSize;

	}
	return TRUE;
	unguard;
}
BOOL Mex2Bone::Read( Mex2Pointer inP, int nSize, DWORD dwVersion /*= 0*/ )
{
	guardfunc;
	Mex2Pointer p(inP.p);

	memcpy( szName, p.c, MEX2_MAX_NAME );
	//pszName = p.c;
	p.c += MEX2_MAX_NAME;
	nParentId = *p.i++;
	nChildCount = *p.i++;
	//pnChildIds = p.i;
	if( nChildCount > 0 )
	{
		pnChildIds = MeDefaultNew int[nChildCount];
		memcpy( pnChildIds, p.c, sizeof(int)*nChildCount );
	}
	p.i += nChildCount;

	m_bFullFrame = FALSE;
	Mex2Skeleton* pMex2Skeleton = (Mex2Skeleton*)pSkeleton;
	if( dwVersion >= 108 )
	{
		m_bFullFrame = pMex2Skeleton->m_bSpecialModel;
	}

	while( p.c < inP.c+nSize )
	{
		switch( MEX_TAG( *p.dw ) )
		{
		case 'trck':
			{
				p.dw++;
				int size = *p.i++;
				
				nFrameCount = *p.i++;
				pMatrices = MeNew MeMatrix[nFrameCount];
				memcpy(pMatrices,p.matrix,sizeof(MeMatrix)*nFrameCount);
				p.matrix += nFrameCount;

				//p.c += size; 
				D3DXMatrixInverse( (D3DXMATRIX*)&matFrame0Inv, NULL, (D3DXMATRIX*)&pMatrices[0] );
			}
			break;
		case 'trk2':
			{
				p.dw++;
				int size = *p.i++;

				nFrameCount = *p.i++;

				if( dwVersion >= 108 && !pMex2Skeleton->m_bSpecialModel &&
					( !stricmp( szName, "Bip01" ) ||
					!stricmp( szName, "Bip01 L Thigh" ) ||
					!stricmp( szName, "Bip01 L Calf" ) || 
					!stricmp( szName, "Bip01 L Foot" ) || 
					!stricmp( szName, "Bip01 L Toe0" ) || 
					!stricmp( szName, "Bip01 R Thigh" ) || 
					!stricmp( szName, "Bip01 R Calf" ) || 
					!stricmp( szName, "Bip01 R Foot" ) || 
					!stricmp( szName, "Bip01 R Toe0" ) /*||
					!stricmp( szName, "lh." ) ||
					!stricmp( szName, "rh." )*/
					) )
				{
					m_bFullFrame = TRUE;
				}
				if( dwVersion < 108 || pMex2Skeleton->m_bSpecialModel || m_bFullFrame )
				{
					pTrans = MeNew Vector[nFrameCount];
					memcpy(pTrans,p.v3,sizeof(Vector)*nFrameCount);
	// 				pTrans = p.v3;
					p.v3 += nFrameCount;
					pQuats = MeNew Quaternion[nFrameCount];
					memcpy(pQuats,p.quat,sizeof(Quaternion)*nFrameCount);
	// 				pQuats = p.quat;
					p.quat += nFrameCount;

					MeMatrix m;
					MakeMatrix( pTrans[0], pQuats[0], m );
					D3DXMatrixInverse( (D3DXMATRIX*)&matFrame0Inv, NULL, (D3DXMATRIX*)&m );
				}
				else
				{
					// 新关键帧动画
					MEX2_SAFE_DELETE(m_pTrack);
					m_pTrack = new AnimationTrack;
					// 初始位置和旋转（本地空间）
					m_pTrack->m_kInitTrans = *p.v3++;
					m_pTrack->m_kInitQuat = *p.quat++;
					// 第0帧模型空间坐标和旋转
					Vector vFrame0Trans = *p.v3++;
					Quaternion qFrame0Quat = *p.quat++;
					MeMatrix m;
					MakeMatrix( vFrame0Trans, qFrame0Quat, m );
					D3DXMatrixInverse( (D3DXMATRIX*)&matFrame0Inv, NULL, (D3DXMATRIX*)&m );

					// 帧数
					int nKeyFrameCount = *p.i++;
					
					// 插值类型
					int nIsTcb = *p.i++;
					if( nIsTcb > 0)
						m_pTrack->SetKeyType(AnimationTrack::eKT_Tcb);
					else
						m_pTrack->SetKeyType(AnimationTrack::eKT_Linear);

					m_pTrack->GetKeyFrames().reserve(nKeyFrameCount);
					for(int i=0; i<nKeyFrameCount; ++i)
					{
						if( m_pTrack->GetKeyType() == AnimationTrack::eKT_Tcb )
						{
							TcbKeyFrame* pKeyFrame = new TcbKeyFrame;
							pKeyFrame->nFrameId = (unsigned short)*p.i++;
							pKeyFrame->ucPosSpace = (unsigned char)*p.i++;
							pKeyFrame->ucRotSpace = (unsigned char)*p.i++;
							pKeyFrame->kTrans = *p.v3++;
							pKeyFrame->kQuat = *p.quat++;
							pKeyFrame->m_iTcbIndex = *p.i++;
							if( pKeyFrame->m_iTcbIndex >= pMex2Skeleton->m_vTcbList.size() )
							{
								assert(0&&"Tcb表出错");
								// 加保护
								if( pMex2Skeleton->m_vTcbList.size() == 0 )
								{
									Mex2Skeleton::TcbData kTcb;
									kTcb.fTension = 0.25f;
									kTcb.fContinuity = 0.25f;
									kTcb.fBias = 0.25f;
									pMex2Skeleton->m_vTcbList.push_back(kTcb);
								}
								pKeyFrame->m_iTcbIndex = 0;
							}
							m_pTrack->GetKeyFrames().push_back(pKeyFrame);
						}
						else
						{
							KeyFrame* pKeyFrame = new KeyFrame;
							//memcpy(pKeyFrame, p.c, sizeof(KeyFrame));
							//p.c += sizeof(KeyFrame);
							pKeyFrame->nFrameId = (unsigned short)*p.i++;
							pKeyFrame->ucPosSpace = (unsigned char)*p.i++;
							pKeyFrame->ucRotSpace = (unsigned char)*p.i++;
							pKeyFrame->kTrans = *p.v3++;
							pKeyFrame->kQuat = *p.quat++;
							m_pTrack->GetKeyFrames().push_back(pKeyFrame);
						}
					}

					// 读取关键帧映射表
					if( m_pTrack->GetKeyFrames().size() > 0 )
					{
						m_pTrack->m_KeyFrameIndexMap.clear();
						int nKeyFrameIndexSize = *p.i++;
						if( nKeyFrameIndexSize > 0 )
						{
							m_pTrack->m_KeyFrameIndexMap.resize(nKeyFrameIndexSize);
							for( int j=0; j<nKeyFrameIndexSize; ++j )
							{
								int nIndex = *p.i++;
								m_pTrack->m_KeyFrameIndexMap[j] = (unsigned short)nIndex;
							}
						}

						BuildInterpolationSplines(pSkeleton);
					}
				}

				bHasKeyframe = TRUE;
			}
			break;
		//case 'visi':
		//	{
		//		p.dw++;
		//		int size = *p.i++;
		//		pVisible = p.boolean;
		//		p.boolean += nFrameCount;
		//		//p.c += size; 
		//		break;
		//	}
		//	break;
		case 'vis2':
			{
				p.dw++;
				int size = *p.i++;
				// modified, [8/10/2010 zhangjiayi],106以后不再记录
				if( dwVersion > 103 && dwVersion < 106 )// added, jiayi, [2010/7/29]
				{
					pVisibleFloat = new float[nFrameCount];
					memcpy(pVisibleFloat,p.f,sizeof(float)*nFrameCount);
					p.f += nFrameCount;
				}
				pVisible = new BOOL[nFrameCount];
				memcpy(pVisible,p.i,sizeof(BOOL)*nFrameCount);
								
				p.i += nFrameCount;
				//p.c += size; 
				break;
			}
			break;
		case 'visf':
			{
				if (dwVersion >= 105)
				{
					p.dw++;
					int size = *p.i++;
					pVisibleFloat = new float[nFrameCount];
					memcpy(pVisibleFloat, p.f, sizeof(float) * nFrameCount);
					p.f += nFrameCount;
				}
			}
			break;
		default:
			{
				p.dw++;
				int size = *p.i++;
				p.c += size; 
				break;
			}
			break;
		}

	}

	//   added 2003.10.07


	

	return TRUE;
	unguard;
}

float* Mex2Bone::GetBlendedMatrices( float t, float fKeyTime0, float fKeyTime1, int nFps, BOOL bIsLastBlend /*= FALSE*/, Vector* pLastBlendTrans /*= NULL*/, Quaternion* pLastBlendQuats /*= NULL*/ )
{
	guardfunc;
	if( !HasKeyFrame() )
	{
		assert(false);
		return NULL;
	}

	Vector v0, v1;
	Quaternion q0, q1;
	BOOL bGet = TRUE;
	// 上一个动作是否blend状态
	if( !bIsLastBlend || pLastBlendTrans == NULL || pLastBlendQuats == NULL
    ||( pLastBlendTrans->positionEquals(Vector(0,0,0)) && pLastBlendQuats->equals(Quaternion(0,0,0,0)) ))
		bGet = GetTranslationAndRotation( fKeyTime0, nFps, v0, q0 );
	else if( pLastBlendTrans && pLastBlendQuats )
	{
		v0 = *pLastBlendTrans;
		q0 = *pLastBlendQuats;
	}
	if( bGet &&	GetTranslationAndRotation( fKeyTime1, nFps, v1, q1 ) )
	{
		v0 = v0+t*(v1-v0);

		if( FloatCmp( q0.x, q1.x ) == 0 &&
			FloatCmp( q0.y, q1.y ) == 0 &&
			FloatCmp( q0.z, q1.z ) == 0 &&
			FloatCmp( q0.w, q1.w ) == 0)
		{
		}
		else
			q0.blend( t, q1 );
	}

	static MeMatrix m;
	MakeMatrix( v0, q0, m );
	// 解决blend过程中切动画，QL，2009/4/14
	if( !bIsLastBlend )
	{
        if( pLastBlendTrans )
		    *pLastBlendTrans = v0;
        if( pLastBlendQuats )
		    *pLastBlendQuats = q0;
	}

	return (float*)&m;
	unguard;
}

BOOL Mex2Bone::HasKeyFrame()
{
	guardfunc;

	//return pTrans != NULL;
	return bHasKeyframe;
	unguard;
}
//BOOL Mex2Bone::GetTranslationAndRotation( float fKeyTime, 
//											  int nFps, 
//											  Vector& v, 
//											  Quaternion& q )
//{
//	guardfunc;
//
//	//Mex2* pMex = (Mex2*)pSkeleton->GetMex();
//	//if( !pTrans )
//	if( !HasKeyFrame() )
//	{
//		//assert( FALSE );
//		return FALSE;
//	}
//	if( nFps <= 0 )
//		nFps = 1;
//	//if( nFps < 0 )
//	//	return ;
//
//	guard( FrameOutRange );
//	float fInterval = 1000.0f/nFps;
//	int nStartFrame = (int)(fKeyTime/fInterval);
//	if( nStartFrame < 0 /*||
//		nStartFrame >= nFrameCount*/ )
//	{
//		assert( false );
//		return FALSE;
//	}
//	if( nStartFrame == nFrameCount )
//		nStartFrame = nFrameCount-1;
//
//
//	//D3DXQuaternionToAxisAngle()
//
//	int nEndFrame = nStartFrame+1;
//	if( nEndFrame >= nFrameCount )
//		nEndFrame = 0;
//
//	float t = (fKeyTime-nStartFrame*fInterval)/fInterval;
//	if( t < 0 /*||
//		t > 1.0f*/ )
//	{
//		return FALSE;
//	}
//	if( t > 1.0f )
//		t = 1.0f;
//
//	Vector vStart(0,0,0);
//	Vector vEnd(0,0,0);
//	Quaternion qStart(0,0,0,0);
//	Quaternion qEnd(0,0,0,0);
//	//if( pMex->IsSmartLoading() )
//	if( pActionList )
//	{
//		//Mex2ActionList* pActionList = ((Mex2*)pSkeleton->GetMex())->GetActionList();
//		Mex2ActionKeyframe* pKeyStart = pActionList->GetKeyframe( nBoneId, nStartFrame );
//		Mex2ActionKeyframe* pKeyEnd = pActionList->GetKeyframe( nBoneId, nEndFrame );
//
//		if( pKeyStart && pKeyEnd )
//		{
//			vStart = pKeyStart->vTrans;
//			vEnd = pKeyEnd->vTrans;
//
//			qStart = pKeyStart->qRot;
//			qEnd = pKeyEnd->qRot;
//		}
//	}
//	else
//	{
//		if( nStartFrame >= nFrameCount )
//			nStartFrame = 0;
//		if( nEndFrame >= nFrameCount )
//			nEndFrame = 0;
//
//		vStart = pTrans[nStartFrame];
//		vEnd = pTrans[nEndFrame];
//		qStart = pQuats[nStartFrame];
//		qEnd = pQuats[nEndFrame];
//	}
//	v = vStart+t*(vEnd-vStart);
//	q = qStart;
//	q.blend( t, qEnd );
//	unguard;
//	return TRUE;
//	unguard;
//}

float Mex2Bone::GetRotation(float fKeyTime, int nFps )
{
	guardfunc;

	//float fInterval = 1000.0f/nFps;
	//int nStartFrame = (int)(fKeyTime/fInterval+0.001f);

	//if( !pTrans )
	if( !HasKeyFrame() )
		return 0;
	Vector v;
	Quaternion q;

	if( pSkeleton && ((Mex2Skeleton*)pSkeleton)->GetMex()->GetVersion() >= 108 && !((Mex2Skeleton*)pSkeleton)->m_bSpecialModel && !m_bFullFrame )
	{
		KeyFrame kKeyFrame, kKeyFrameEx;
		FrameIndex frameIndex = ((Mex2Skeleton*)pSkeleton)->GetTimeIndex(fKeyTime);
		GetInterpolatedKeyFrame(frameIndex, kKeyFrame, kKeyFrameEx);
		v = kKeyFrame.kTrans;
		q = kKeyFrame.kQuat;

		if( GetParentId() >= 0 )
		{
			MeMatrix parentMat;
			GetParentModelMatAtKeyFrame(fKeyTime, frameIndex, parentMat);
			Quaternion parentQuat;
			Vector parentVec;
			ConvertMatrixToTranslationAndRotation(parentMat, parentVec, parentQuat);
			q *= parentQuat;
		}
	}
	else
		GetTranslationAndRotation( fKeyTime, nFps, v, q );

	float w = q.w;
	float x = q.x;
	float y = q.y;
	float z = q.z;
	float b = 0;
//	float h,p,b;

	//计算sin(pitch)
	float sp = -2.0f * (y*z - w*x);

	//检查万向锁，允许有一定误差
	//if( fabs(sp) > 0.9999f )
	if( fabs(sp) > 0.90f )
	{
		//向正上或正下看
	//	p = D3DX_PI/2 * sp;
		//计算heading,bank置零
		//h = atan2(-x*z - w*y, 0.5f - y*y - z*z);
		//b = 0.0f;
		b = D3DX_PI;
	}
	else
	{
		//计算角度
		//p = asin(sp);
	//	h = atan2(x*z + w*y, 0.5f - x*x - y*y);
		b = atan2(x*y + w*z, 0.5f - x*x - z*z);
		//b = atan2(x*y - w*z, 0.5f - x*x - z*z);
	}

	//char szBuf[256];
	//_snprintf( szBuf, 256, "sp %f frameid %d\n",sp,nStartFrame );
	//OutputDebugString( szBuf );

	return b;
	unguard;
}

void Mex2Bone::CalModelSpaceKeyFrame(KeyFrame& kKeyFrame, KeyFrame& kOutKeyFrame, float fKeyTime, const FrameIndex& frameIndex, float* parentMat)
{
	MeMatrix m;
	kOutKeyFrame.nFrameId = kKeyFrame.nFrameId;

	switch( kKeyFrame.ucPosSpace )
	{
	case KeyFrame::eKS_World:
		{
			kOutKeyFrame.kTrans = kKeyFrame.kTrans;
			kOutKeyFrame.kQuat = kKeyFrame.kQuat;
		}
		break;
	case KeyFrame::eKS_Body:
		{
			MeMatrix initBodyMat;
			D3DXMatrixInverse( (D3DXMATRIX*)&initBodyMat, NULL, (D3DXMATRIX*)&matFrame0Inv );

			int nSpine1BoneId = -1;
			if( nSpine1BoneId < 0 )
			{
				Mex2Skeleton* pMex2Skeleton = (Mex2Skeleton*)pSkeleton;
				for( int i = 0; i < pMex2Skeleton->vectorBone.size(); i++ )
				{
					Mex2Bone* pBone = pMex2Skeleton->vectorBone[i];
					if( !stricmp(pBone->szName, "Bip01 Spine1") )
					{
						nSpine1BoneId = i;
						break;
					}
				}
			}
			if( nSpine1BoneId < 0 )
				assert(0);
			else
			{
				Mex2Bone* pBodyBone = ((Mex2Skeleton*)pSkeleton)->vectorBone[nSpine1BoneId];
				if( pBodyBone )
				{
					D3DXMatrixMultiply( (D3DXMATRIX*)&initBodyMat, (D3DXMATRIX*)&initBodyMat, (D3DXMATRIX*)pBodyBone->GetFrame0Inv() );
				}
			}

			kKeyFrame.kQuat.normalise();
			MakeMatrix( kKeyFrame.kTrans, kKeyFrame.kQuat, m );
			D3DXMatrixMultiply( (D3DXMATRIX*)&m, (D3DXMATRIX*)&m, (D3DXMATRIX*)&initBodyMat );

			if( nSpine1BoneId >= 0 )
			{
				int nParentIdBack = GetParentId();
				nParentId = nSpine1BoneId;
				MeMatrix kParentMat;
				GetParentModelMatAtKeyFrame(fKeyTime, frameIndex, kParentMat);
				D3DXMatrixMultiply( (D3DXMATRIX*)&m, (D3DXMATRIX*)&m, (D3DXMATRIX*)&kParentMat );
				nParentId = nParentIdBack;
			}

			ConvertMatrixToTranslationAndRotation(m, kOutKeyFrame.kTrans, kOutKeyFrame.kQuat);
		}
		break;
	default:
		{
			kKeyFrame.kQuat.normalise();
			MakeMatrix( kKeyFrame.kTrans, kKeyFrame.kQuat, m );

			MeMatrix initMat;
			MakeMatrix(m_pTrack->m_kInitTrans, m_pTrack->m_kInitQuat, initMat);
			D3DXMatrixMultiply( (D3DXMATRIX*)&m, (D3DXMATRIX*)&m, (D3DXMATRIX*)&initMat );

			if( GetParentId() >= 0 )
			{
				if( parentMat == NULL )
				{
					MeMatrix kParentMat;
					GetParentModelMatAtKeyFrame(fKeyTime, frameIndex, kParentMat);
					D3DXMatrixMultiply( (D3DXMATRIX*)&m, (D3DXMATRIX*)&m, (D3DXMATRIX*)&kParentMat );
				}
				else
				{
					D3DXMatrixMultiply( (D3DXMATRIX*)&m, (D3DXMATRIX*)&m, (D3DXMATRIX*)parentMat );
				}
			}
			ConvertMatrixToTranslationAndRotation(m, kOutKeyFrame.kTrans, kOutKeyFrame.kQuat);
		}
		break;
	}

}

float* Mex2Bone::GetMatricesFromKeyTime( float fKeyTime, int nFps, float* parentMat/* = NULL*/ )
{
	guardfunc;

	static MeMatrix m;
	float fInterval = 1000.0f/nFps;
	int nStartFrame = (int)(fKeyTime/fInterval/*+0.001f*/);
	if( !HasKeyFrame() )
		return GetMatrices( nStartFrame );
	Vector v;
	Quaternion q;

	if( pSkeleton && m_pTrack && ((Mex2Skeleton*)pSkeleton)->GetMex()->GetVersion() >= 108 && !((Mex2Skeleton*)pSkeleton)->m_bSpecialModel && !m_bFullFrame )
	{
		KeyFrame kKeyFrame, kKeyFrameEx;
		FrameIndex frameIndex = ((Mex2Skeleton*)pSkeleton)->GetTimeIndex(fKeyTime);
		float t = GetInterpolatedKeyFrame(frameIndex, kKeyFrame, kKeyFrameEx);
		if( t >= 0.001f )
		{
			KeyFrame kModelKF1, kModelKF2;
			CalModelSpaceKeyFrame( kKeyFrame, kModelKF1, fKeyTime, frameIndex, parentMat );
			CalModelSpaceKeyFrame( kKeyFrameEx, kModelKF2, fKeyTime, frameIndex, parentMat );
			// 线性插值
			KeyFrame kResultKf;
			kModelKF1.Interpolate(t, &kModelKF2, &kResultKf);
			MakeMatrix( kResultKf.kTrans, kResultKf.kQuat, m );
		}
		else
		{
			KeyFrame kModelKF1;
			CalModelSpaceKeyFrame( kKeyFrame, kModelKF1, fKeyTime, frameIndex, parentMat );
			MakeMatrix( kModelKF1.kTrans, kModelKF1.kQuat, m );
		}

		return (float*)&m;
	}
	else if( m_bFullFrame )
	{
		//fKeyTime = nStartFrame * fInterval;
		GetTranslationAndRotation( fKeyTime, nFps, v, q );
	}
	else
		GetTranslationAndRotation( fKeyTime, nFps, v, q );
	MakeMatrix( v, q, m );
	//if( stricmp( szName, "shangbi" ) == 0 )
	//{
	//	fScaleAdjust = 1.5;
	//	D3DXMATRIX scale;
	//	D3DXMatrixScaling( &scale, fScaleAdjust, fScaleAdjust, 1.0f );
	//	D3DXMatrixMultiply( (D3DXMATRIX*)&m, &scale, (D3DXMATRIX*)&m );
	//}
	////else
	////{
	////	if( nParentId )
	////	{
	////		Mex2Bone* pParent = (Mex2Bone*)pSkeleton->GetBone( nParentId );
	////		fScaleAdjust *= pParent->fScaleAdjust;
	////	}

	////}

	//else if( stricmp( szName, "Bip01 R Forearm" ) == 0 || 
	//	stricmp( szName, "Bip01 R UpperArm" ) == 0 )
	//{
	//	fScaleAdjust = 1.2;
	//	D3DXMATRIX scale;
	//	D3DXMatrixScaling( &scale, fScaleAdjust, fScaleAdjust, 1.0f );
	//	D3DXMatrixMultiply( (D3DXMATRIX*)&m, &scale, (D3DXMATRIX*)&m );
	//}
	return (float*)&m;
	unguard;
}
float Mex2Bone::GetVisibleFloat( int nFrameId )
{
	Mex2* pMex = (Mex2*)pSkeleton->GetMex();
	if( pActionList )
	{
		return (float)pActionList->IsVisible( nBoneId, nFrameId );
	}
	if( !pVisibleFloat )
		return -1;

	return pVisibleFloat[nFrameId];
}

BOOL Mex2Bone::IsVisible( int nFrameId )
{
	/*
	 * 2012.6.7 废弃了VisibleBool(vis2), 直接使用VisibleFloat(visf)
	 * 使骨骼支持透明度, 而不是原来的可不可见
	 */
	Mex2 *pMex = (Mex2 *) pSkeleton->GetMex();
	if (pActionList != NULL)
	{
		return pActionList->IsVisible( nBoneId, nFrameId );
	}

	/*
	* 注意: 当所有的Bone的Visibility都是1.0f时, 为了节省空间, 不写入Mex文件中
	*/
	if (pVisibleFloat == NULL)
		return TRUE;

	return pVisibleFloat[nFrameId] != 0.0f;
	/*
	if (!pVisible)
		return TRUE;
	return pVisible[nFrameId];*/
}

float* Mex2Bone::GetMatrices( int nFrameId )
{ 
	guardfunc;

	static MeMatrix m;
	if( pActionList )
		return pActionList->GetMatrices( nBoneId, nFrameId );
	if( bHasKeyframe )
	{
		// 关键帧动画尽量使用GetMatricesFromKeyTime函数，不要用GetMatrices
		if( pSkeleton && ((Mex2Skeleton*)pSkeleton)->GetMex()->GetVersion() >= 108 && !((Mex2Skeleton*)pSkeleton)->m_bSpecialModel && !m_bFullFrame )	// 关键帧
		{
			return GetMatricesFromKeyTime(nFrameId*ONEFRAMEINTERVAL, FRAMEPERSEC);
		}
		else if( pTrans )	// 逐帧动画
		{
			MakeMatrix( pTrans[nFrameId], pQuats[nFrameId], m );
			return (float*)&m;
		}
	}
	return (float*)&pMatrices[nFrameId]; 
	unguard;
}

Mex2Skeleton::~Mex2Skeleton()
{
	guardfunc;
	for( int i = 0; i < vectorBone.size(); i++ )
	{
		Mex2Bone* bone = vectorBone[i];
		delete bone;
// 		if( bone.pnChildIds )
// 		{
// 			delete[] bone.pnChildIds;
// 			bone.pnChildIds = NULL;
// 		}
	}
	vectorBone.clear();
	MEX2_SAFE_DELETE_ARRAY(pnRootBoneIds);
	m_KeyFrameTimes.clear();
	m_KeyFrameSegments.clear();

	unguard;
}



BOOL Mex2Skeleton::IsSameFormat( IMexSkeleton* pSkeleton )
{
	guardfunc;

	if( !pSkeleton )
	{
		assert( false );
		return FALSE;
	}
	// 如果骨骼数目相同，而且起始位置一一对应相同
	// 那么我们就认为是格式一致的骨骼
	if( pSkeleton->GetBoneCount() != GetBoneCount() )
	{
		//assert( 0 && "骨骼数不同" );
#ifdef _DEBUG
        OutputDebugString("骨骼数不同\n");
#endif
		return FALSE;
	}
	for( int nBone = 0; nBone < GetBoneCount(); nBone++ )
	{
		IMexBone* pSrcBone = GetBone( nBone );
		IMexBone* pDstBone = pSkeleton->GetBone( nBone );

		if( _stricmp( pSrcBone->GetName(), pDstBone->GetName() ) != 0 )
		{
			return FALSE;
		}

		//float* pSrcMatrix = pSrcBone->GetMatrices(0);
		//float* pDstMatrix = pDstBone->GetMatrices(0);
		//float pSrcMatrix[16];
		//memcpy( pSrcMatrix, pSrcBone->GetMatricesFromKeyTime(0,30), sizeof(float)*16 );
		//float pDstMatrix[16];
		//memcpy( pDstMatrix, pDstBone->GetMatricesFromKeyTime(0,30), sizeof(float)*16 );

		//BOOL bEqual = TRUE;
		//for( int i = 0; i < 16; i++ )
		//{
		//	if( FloatCmp( pSrcMatrix[0], pDstMatrix[0] ) != 0 )
		//	{
		//		bEqual = FALSE;
		//		break;
		//	}
		//}
		//if( !bEqual )
		//	return FALSE;
	}
	return TRUE;
	unguard;
}
int Mex2Skeleton::FindBone( const char* pszBoneName )
{
	guardfunc;
	if( !pszBoneName )
		return -1;

	for( int i = 0; i < GetBoneCount(); i++ )
	{
		if( GetBone( i ) && _stricmp( GetBone( i )->GetName(), pszBoneName ) == 0 )
			return i;
	}
	return -1;
	unguard;
}
BOOL Mex2Skeleton::SnapShotFromFile( FILE* fp, int nSize, DWORD dwFlag )
{
	guardfunc;
	int nByte = 0;
	int nBoneCount = 0;
	fread( &nBoneCount, sizeof(int), 1, fp );
	nByte += sizeof(int);
	fread( &nRootBoneCount, sizeof(int), 1, fp );
	nByte += sizeof(int);
	pnRootBoneIds = MeDefaultNew int[nRootBoneCount];
	fread( pnRootBoneIds, sizeof(int)*nRootBoneCount, 1, fp );
	nByte += sizeof(int)*nRootBoneCount;

	while( nByte < nSize )
	{
		DWORD dwName = 0;
		int size = 0;
		fread( &dwName, sizeof(DWORD), 1, fp );
		nByte += sizeof(DWORD);
		fread( &size, sizeof(int), 1, fp );
		nByte += sizeof(int);
		switch( MEX_TAG( dwName ) )
		{
		case 'bone':
			{
				Mex2Bone* bone = MeNew Mex2Bone;
				bone->pSkeleton = this;

				bone->SnapShotFromFile( fp, size, dwFlag );
				bone->nBoneId = vectorBone.size();
				bone->pActionList = ((Mex2*)pMex)->GetActionList();
				vectorBone.push_back( bone );
			}
			break;
		default:
			{
				fseek( fp, size, SEEK_CUR );
				break;
			}
			break;
		}
		nByte += size;
	}
		
	return TRUE;

	unguard;
}
BOOL Mex2Skeleton::Read( void* pp, int nSize, DWORD dwVersion /*= 0*/ )
{
	guardfunc;

	//Mex2Pointer p(inP.p);
	Mex2Pointer p(pp);

	int nBoneCount = *p.i++;
	nRootBoneCount = *p.i++;
	
	if( nRootBoneCount > 0 )
	{
		pnRootBoneIds = MeDefaultNew int[nRootBoneCount];
		//pnRootBoneIds = p.i;
		memcpy( pnRootBoneIds, p.i, sizeof(int)*nRootBoneCount );
	}
	p.i += nRootBoneCount;

	m_vTcbList.clear();
	if( dwVersion >= 108 )
	{
		// 读关键帧表，所有骨骼关键帧从小到大
		m_bSpecialModel = FALSE;
		m_KeyFrameTimes.clear();
		int nKeyFrameTimesSize = *p.i++;
		if( nKeyFrameTimesSize > 0 )
		{
			m_KeyFrameTimes.resize(nKeyFrameTimesSize);
			for( int i=0; i<nKeyFrameTimesSize; ++i )
			{
				int nFrameId = *p.i++;
				m_KeyFrameTimes[i] = nFrameId;
			}
		}
		else if( nKeyFrameTimesSize == -1 )
		{
			// 特殊坐骑，逐帧动画
			m_bSpecialModel = TRUE;
		}

		int nTcbCount = *p.i++;
		if( nTcbCount > 0 )
		{
			m_vTcbList.resize(nTcbCount);
			for( int i=0; i<nTcbCount; ++i )
			{
				m_vTcbList[i].fTension = *p.f++;
				m_vTcbList[i].fTension *= 0.01f;
				m_vTcbList[i].fContinuity = *p.f++;
				m_vTcbList[i].fContinuity *= 0.01f;
				m_vTcbList[i].fBias = *p.f++;
				m_vTcbList[i].fBias *= 0.01f;
			}
		}
	}

	//while( p.c < inP.c+nSize )
	while( p.c < (char*)pp+nSize )
	{
		switch( MEX_TAG( *p.dw ) )
		{
		case 'bone':
			{
				p.dw++;
				int size = *p.i++;
				Mex2Bone* bone = MeNew Mex2Bone;
				//Mex2Bone* bone = MeNew Mex2Bone;
				//   added 2003.10.09
				//bone->pMex = pMex;
				bone->pSkeleton = this;
				
				bone->Read( p, size, dwVersion );
				bone->nBoneId = vectorBone.size();
				vectorBone.push_back( bone );
				p.c += size; 

				
			}
			break;
		default:
			{
				p.dw++;
				int size = *p.i++;
				p.c += size; 
				break;
			}
			break;
		}
	}


	return TRUE;
	unguard;
}

int Mex2Skeleton::GetBoneId( const char* pszBoneName )
{
	guardfunc;

	for( int i = 0; i < vectorBone.size(); i++ )
	{
		char* p = vectorBone[i]->szName;
		//char* p = GetBone(i)->Getn
		if( strcmp( pszBoneName, p ) == 0 )
			return i;
	}
	return -1;
	unguard;
}
BOOL Mex2BoneGroup::SetBoneID( int i, int nBoneID )
{
	guardfunc;

	if( i < 0 || i >= GetBoneCount() )
		return FALSE;
	pnBoneIds[i] = nBoneID;
	return TRUE;
	unguard;
}
IMexBoneGroup* Mex2BoneGroups::GetBoneGroup( int i )
{ 
	guardfunc;
///	//CSALocker locker(this);
	if( i >= 0 && i < vectorBoneGroup.size() )
		return vectorBoneGroup[i]; 
	return NULL;
	unguard;
}
BOOL Mex2BoneGroup::Read( Mex2Pointer inP, int nSize, DWORD version )
{
	guardfunc;

	Mex2Pointer p(inP.p);
	nBoneCount = *p.i++;
	pnBoneIds = new int[nBoneCount];
	memcpy(pnBoneIds,p.i,sizeof(int)*nBoneCount);
// 	pnBoneIds = p.i;
	p.i += nBoneCount;
	// 读取骨骼权重
	if( version >= 102 )
	{
		pfBondWeight = new float[nBoneCount];
		memcpy(pfBondWeight,p.f,sizeof(float)*nBoneCount);
// 		pfBondWeight = p.f;
		p.f += nBoneCount;
	}

	return TRUE;
	unguard;
}

BOOL Mex2BoneGroups::Read( Mex2Pointer inP, int nSize, DWORD version )
{
	guardfunc;
////	//CSALocker locker(this);
	Mex2Pointer p(inP.p);
	while( p.c < inP.c+nSize )
	{
		switch( MEX_TAG( *p.dw ) )
		{
		case 'bgrp':
			{
				p.dw++;
				int size = *p.i++;
				Mex2BoneGroup* boneGroup = MeNew Mex2BoneGroup;
				boneGroup->Read( p, size, version );
				vectorBoneGroup.push_back( boneGroup );
				p.c += size; 
			}
			break;
		default:
			{
				p.dw++;
				int size = *p.i++;
				p.c += size; 
			}
			break;
		}
	}
	return TRUE;
	unguard;
}

//   added 2004.08.06

IMexLight* Mex2Light::Clone()
{
	guardfunc;
	Mex2Light* pLight = MeNew Mex2Light;
	pLight->m_param = m_param;
	return pLight;
	unguard;
}




//void Mex2Light::Update( int nTime, MeMatrix* pMatrices, MeMatrix* pmatModel )
void Mex2Light::Update( int nTime, float* pfMatrices, float* pfMatModel )
{
	guardfunc;
	MeMatrix* pMatrices = (MeMatrix*)pfMatrices;
	MeMatrix* pmatModel = (MeMatrix*)pfMatModel;
	if( m_param.m_nParentBoneID == -1 )
	{
		assert( false && "mex2 light update error, parent bone id is -1" );
		return;
	}
	//if( nLightId == -1 )
	//{
	//	assert( false && "mex2 light update error, light id is -1" );
	//	return;
	//}

	D3DXVec3TransformCoord( (D3DXVECTOR3*)&m_vPos, 
		(D3DXVECTOR3*)&m_param.m_vPivot,	
		(D3DXMATRIX*)&pMatrices[m_param.m_nParentBoneID] );
	//   added 2004.05.11
	D3DXVec3TransformCoord( (D3DXVECTOR3*)&m_vPos, 
		(D3DXVECTOR3*)&m_vPos,	
		(D3DXMATRIX*)pmatModel );

	//g_Me3dLightMgr.UpdateLight( nLightId, this );

	//g_pfnUpdate
	unguard;
}
void Mex2Light::SetName( const char* pszName )
{
	guardfunc;
	HelperFunc::SafeNCpy( m_param.m_szName, pszName, MEX2_MAX_NAME );
	unguard;
}
void Mex2Light::SetColor( float* pfColor )
{
	guardfunc;
	m_param.m_fDiffuse[0] = pfColor[0]; 
	m_param.m_fDiffuse[1] = pfColor[1]; 
	m_param.m_fDiffuse[2] = pfColor[2]; 
	unguard;
}
void Mex2Light::SetAttenuration( float* pfAtten )
{
	guardfunc;
	m_param.m_fAttenuration[0] = pfAtten[0];
	m_param.m_fAttenuration[1] = pfAtten[1];
	m_param.m_fAttenuration[2] = pfAtten[2];
	unguard;
}
BOOL Mex2Light::Read( Mex2Pointer inP, int nSize )
{
	guardfunc;
	Mex2Pointer p(inP.p);

	m_param.m_dwFlag = *p.i++;
	//pszName = p.c;
	HelperFunc::SafeNCpy( m_param.m_szName, p.c, MEX2_MAX_NAME );
	p.c += MEX2_MAX_NAME;
	m_param.m_nParentBoneID = *p.i++;
	m_param.m_vPivot = *p.v3++;
	m_param.m_fRange = *p.f++;
	m_param.m_fIntense = *p.f++;
	


	m_param.m_fAttenuration[0] = *p.f++;
	m_param.m_fAttenuration[1] = *p.f++;
	m_param.m_fAttenuration[2] = *p.f++;
	
	//p.f += 3;
	
	m_param.m_nFrameCount = *p.i++;
	m_param.m_pColorTrack = new float[m_param.m_nFrameCount*3];
	memcpy(m_param.m_pColorTrack,p.f,sizeof(float)*m_param.m_nFrameCount*3);
// 	m_param.m_pColorTrack = p.f;
	p.f += m_param.m_nFrameCount*3;
	
	
	m_param.m_fDiffuse[0] = m_param.m_pColorTrack[0];
	m_param.m_fDiffuse[1] = m_param.m_pColorTrack[1];
	m_param.m_fDiffuse[2] = m_param.m_pColorTrack[2];
	return TRUE;
	unguard;
}
BOOL Mex2Lights::Read( Mex2Pointer inP, int nSize )
{
	guardfunc;
	Mex2Pointer p(inP.p);
	while( p.c < inP.c+nSize )
	{
		switch( MEX_TAG( *p.dw ) )
		{
		case 'olt2':
			{
				p.dw++;
				int size = *p.i++;
				Mex2Light light;
				light.Read( p, size );
				//vectorRibbonEmitter.push_back( re );
				vectorLight.push_back( light );
				p.c += size; 

			}
			break;
		default:
			{
				p.dw++;
				int size = *p.i++;
				p.c += size; 
				break;
			}
			break;
		}
	}
	return TRUE;
	unguard;
}
void Mex2Lights::Bind( Mex2* pMex )
{
	guardfunc;
	for( int i = 0; i < vectorLight.size(); i++ )
		//vectorLight[i].Bind( pMex );
		vectorLight[i].m_param.m_pSrcMex = pMex;
	unguard;
}



BOOL Mex2Attachment::Read( Mex2Pointer inP, int nSize )
{
	guardfunc;
////	//CSALocker locker(this);
	Mex2Pointer p(inP.p);


	nAttachBoneID = *p.i++;
	strcpy_s(pszName,MEX2_MAX_NAME,p.c);
	p.c += MEX2_MAX_NAME;
	matInit = *p.matrix++;
	return TRUE;
	unguard;
}
int Mex2Attachments::GetNumAttachment()
{
	guardfunc;
////	//CSALocker locker(this);

	return m_Attachments.size();
	unguard;
}
IMexAttachment* Mex2Attachments::GetAttachment( int nAttachment )
{
	guardfunc;
////	//CSALocker locker(this);
	if( nAttachment < 0 || nAttachment >= m_Attachments.size() )
	{
		assert( false );
		return NULL;
	}
	return &m_Attachments[nAttachment];
	unguard;
}
// add, jiayi, [2009.4.17]
IMexAttachment*	Mex2Attachments::FindAttachment( const char* pszName, int nOffset )
{
	guardfunc;
	for( int nAtt = nOffset; nAtt < m_Attachments.size(); nAtt++ )
	{
		if( _stricmp( pszName, m_Attachments[nAtt].pszName ) == 0 )
			return &m_Attachments[nAtt];
	}
	return NULL;
	unguard;
}

IMexAttachment* Mex2Attachments::FindAttachment( const char* pszName )
{
	guardfunc;
////	//CSALocker locker(this);
	for( int nAtt = 0; nAtt < m_Attachments.size(); nAtt++ )
	{
		if( _stricmp( pszName, m_Attachments[nAtt].pszName ) == 0 )
			return &m_Attachments[nAtt];
	}
	return NULL;
	unguard;
}

BOOL Mex2Attachments::Read( Mex2Pointer inP, int nSize )
{
	guardfunc;
////	//CSALocker locker(this);
	Mex2Pointer p(inP.p);
	while( p.c < inP.c+nSize )
	{
		switch( MEX_TAG( *p.dw ) )
		{
		case 'att0':
			{
				p.dw++;
				int size = *p.i++;
				Mex2Attachment attachment;
				attachment.Read( p, size );
				m_Attachments.push_back( attachment );
				p.c += size; 
			}
			break;
		default:
			{
				p.dw++;
				int size = *p.i++;
				p.c += size; 
				break;
			}
			break;
		}

	}
	return TRUE;

	unguard;
}


//////////////////////////////////////////////////////////////////////////
Mex2::~Mex2()
{
	guardfunc;
	MEX2_ASSERT( m_version );
	MEX2_ASSERT( m_textures );
	MEX2_ASSERT( m_mtls );
	MEX2_ASSERT( m_geometry );
	MEX2_ASSERT( m_skeleton );
// 	MEX2_ASSERT( m_sequences );
	MEX2_ASSERT( m_boneGroups );
	MEX2_ASSERT( m_attachments );
	MEX2_ASSERT( m_ribbonEmitters );
	//MEX2_ASSERT( m_billboards );
	//MEX2_ASSERT( m_hitPointsSet );
	MEX2_ASSERT( m_particleEmitters );
	//MEX2_ASSERT( m_lights );
//	MEX2_ASSERT( m_pbyMemory );
	unguard;
}
void Mex2::Release()
{
	guardfunc;
	//CSALocker locker(this);
	try
	{
		Destroy();
	}
	catch (...)
	{
		
	}
	//delete this;
	unguard;
}
void Mex2::Destroy()
{
	guardfunc;
	//CSALocker locker(this);
	//UnRegisterTextures();
	MEX2_SAFE_DELETE( m_version );
	MEX2_SAFE_DELETE( m_textures );
	MEX2_SAFE_DELETE( m_mtls );
	MEX2_SAFE_DELETE( m_pSequence );
	
	if( m_geometry )
	{
		for( int nChunk = 0; nChunk < m_geometry->vectorChunk.size(); nChunk++ )
		{
			delete m_geometry->vectorChunk[nChunk];
		}
		m_geometry->vectorChunk.clear();
		m_geometry->vectorChunkData.clear();
	}
	MEX2_SAFE_DELETE( m_geometry );

// 	if( m_nReallocBoneFrameCount&&m_skeleton != NULL)
// 	{
// 		Mex2Skeleton* pSkeleton = (Mex2Skeleton*)m_skeleton;
// 		for(UINT nBone=0; nBone<pSkeleton->GetBoneCount(); nBone++)
// 		{
// 			Mex2Bone* pBone = (Mex2Bone*)pSkeleton->GetBone( nBone );
// 			delete pBone;
// 		}
// 	}
	MEX2_SAFE_DELETE( m_skeleton );
// 	MEX2_SAFE_DELETE( m_pSrcSkeleton );
	
// 	MEX2_SAFE_DELETE( m_sequences );
	MEX2_SAFE_DELETE( m_boneGroups );
	MEX2_SAFE_DELETE( m_attachments );
	//MEX2_SAFE_DELETE( m_hitPointsSet );
	//MEX2_SAFE_DELETE( m_lights );

	DestroyParticleEmitters();

	if( m_ribbonEmitters )
	{
		//for( int i = 0; i < m_ribbonEmitters->vectorRibbonEmitter.size(); i++ )
		//	m_ribbonEmitters->vectorRibbonEmitter[i].Release();
	}
	MEX2_SAFE_DELETE( m_ribbonEmitters );

	
	//UnRegisterTextures();
	//if( m_pbyMemory )
	//{
	//	delete []m_pbyMemory;
	//	m_pbyMemory = NULL;
	//}
//	m_Unit.ReleaseUnit();
// 	if( m_pSkinMesh )
// 	{
// 		m_pSkinMesh->Destroy();
// 		delete m_pSkinMesh;
// 		m_pSkinMesh = NULL;
// 	}
	m_ActionList.Destroy();
	//GetMemoryFactory()->Destroy();


	MEX2_SAFE_DELETE_ARRAY(m_pbyMemory);
	unguard;
}
int Mex2::GetVertexCount()
{
	guardfunc;
	//CSALocker locker(this);
	if( !m_geometry) 
		return 0;
	int nTotalVertexCount = 0;
	for( int i = 0; i < m_geometry->vectorChunk.size(); i++ )
	{
		nTotalVertexCount += m_geometry->vectorChunk[i]->GetVertexCount();
	}
	return nTotalVertexCount;
	unguard;
}
int Mex2::GetFaceCount()
{
	guardfunc;
	//CSALocker locker(this);
	if( !m_geometry) 
		return 0;
	int nTotalFaceCount = 0;
	for( int i = 0; i < m_geometry->vectorChunk.size(); i++ )
	{
		nTotalFaceCount += m_geometry->vectorChunk[i]->GetFaceCount();
	}
	return nTotalFaceCount;
	unguard;
}
BOOL Mex2::HasMtl()
{
	guardfunc;
	//CSALocker locker(this);
	if( GetMtls() &&
		//GetMtls()->vectorMtl.size() > 0 )
		GetMtls()->GetMtlCount() > 0 )
		return TRUE;
	return FALSE;
	unguard;
}

bool Mex2::IntersectQuick( Vector* pvStart, Vector* pvDir, MexReplaceableTextureProj* replaceableTexture, D3DXMATRIX* pModelInverseMatrix )
{
	guardfunc;
	//CSALocker locker(this);
	if( !m_geometry )
	{
		assert( FALSE && "intersect error, geometry is null" );
		return FALSE;
	}
	
	int nChunk = m_geometry->vectorChunk.size();
	for( int i = 0; i < nChunk; i++ )
	{
		Mex2GeoChunk* pChunk = m_geometry->vectorChunk[i];
		if( pChunk->GetType() == Mex2GeoChunkProperty::eStatic || pChunk->GetType() == Mex2GeoChunkProperty::eBillboard )
		{
			if( pChunk->IntersectQuick(pvStart,pvDir,replaceableTexture,pModelInverseMatrix))
			{
				return true;
			}
		}
	}
	return false;
	unguard;
}

// BOOL Mex2::Intersect( float* pfStart, float* pfDir, float* pfHit, DWORD dwFlag )
// {
// 	guardfunc;
// 	//CSALocker locker(this);
// 	if( !m_geometry )
// 	{
// 		assert( FALSE && "intersect error, geometry is null" );
// 		return FALSE;
// 	}
// 	Vector* pvStart = (Vector*)pfStart;
// 	Vector* pvDir = (Vector*)pfDir;
// 	Vector* pvHit = (Vector*)pfHit;
// 	
// 	long const MAX_INTERSECTION = 32;
// 	float hits[MAX_INTERSECTION];
// 	int nHit = 0;
// 	int nChunk = m_geometry->vectorChunk.size();
// 	for( int i = 0; i < nChunk; i++ )
// 	{
// 		Mex2GeoChunk* pChunk = m_geometry->vectorChunk[i];
// 		pChunk->Intersect(pvStart, 
// 			pvDir,hits,MAX_INTERSECTION,nHit,dwFlag);
// 	}
// 	if( nHit == 0 )
// 		return FALSE;
// 	float fMinT = hits[0];
// 	for( int i = 1; i < nHit; i++ )
// 	{
// 		if( fMinT > hits[i] )
// 			fMinT = hits[i];
// 	}
// 	*pvHit = *pvStart+fMinT*(*pvDir);
// 
// 	return TRUE;
// 	unguard;
// }

float Mex2::GetBoneVisibleFloat( int nFrameId, int nBoneId )
{
	if( nFrameId < 0  )
		return -1;

	if( !m_skeleton )
		return -1;

	Mex2Bone* pBone = (Mex2Bone*)m_skeleton->GetBone(nBoneId);
	if( !pBone )
		return -1;

	return pBone->GetVisibleFloat(nFrameId);
}

BOOL Mex2::IsBoneVisible(int nFrameId, int nBoneId)
{
	guardfunc;
	if (nFrameId < 0)
		return FALSE;

	if (m_skeleton == NULL)
		return FALSE;
	
	Mex2Bone *bone = (Mex2Bone *) m_skeleton->GetBone(nBoneId);
    if (bone == NULL)
        return FALSE;

	return bone->IsVisible(nFrameId);
	unguard;
}


BOOL Mex2::SaveToFile( const char* pszFilename, DWORD dwFlag )
{
	guardfunc;
	//CSALocker locker(this);
	static const unsigned int MEX_BUFFER_SIZE = 1024*1024*30;

	BYTE* pBuffer = new BYTE[MEX_BUFFER_SIZE];
	if( !pBuffer )
	{
		::MessageBox(NULL, "内存不足模型保存失败", "Error", MB_OK);
		return FALSE;
	}

	CDataChunkWriter w( pBuffer, MEX_BUFFER_SIZE );	// 30 mega memory
	//CDataChunkWriter w( 1024*1024*6 );	// 6 mega memory
	//CXmlChunkWriter w( 1024*1024*6 );	// 6 mega memory
	w.StartChunk( DC_TAG( 'vers' ) );
	{
		if( m_version )
		{
			w.WriteInt( m_version->dwVersion );
		}
	}
	w.EndChunk( DC_TAG( 'vers' ) );
	w.StartChunk( DC_TAG( 'texs' ) );
	{
		if( m_textures )
		{
			//w.WriteInt( m_textures->nTextureCount );
			w.WriteInt( m_textures->GetTextureCount() );
			for( int nTexture = 0; nTexture < m_textures->GetTextureCount(); nTexture++ )
			{
				char s[MAX_PATH];
				memset( s, 0x00, sizeof(s) );
				strncpy( s, m_textures->GetTexture(nTexture)->GetName(), MAX_PATH-1 );

				CFilePath path;
				path.Split( s );
				memset( s, 0x00, sizeof(s) );
				sprintf_s( s, MAX_PATH, "%s%s", path.GetFileName(), path.GetExt() );
				w.Write( s, MAX_PATH, 1 );
			}
		}
	}
	w.EndChunk( DC_TAG( 'texs' ) );

	w.StartChunk( DC_TAG( 'mtls' ) );
	{
		if( m_mtls )
		{
			for( int i = 0; i < m_mtls->vectorMtl.size(); i++ )
			{
				w.StartChunk( DC_TAG( 'matl' ) );
				{
					w.StartChunk( DC_TAG( 'lays' ) );
					{
						//w.WriteInt( m_mtls->GetMtl(i)->nLayerCount );
						w.WriteInt( m_mtls->GetMtl(i)->GetLayerCount() );
						//if( m_mtls->GetMtl(i)->nLayerCount > 0 )
						for( int nLayer = 0; nLayer < m_mtls->GetMtl(i)->GetLayerCount(); nLayer++ )
						{
							IMexLayer* pLayer = m_mtls->GetMtl(i)->GetLayer(nLayer);
							w.WriteInt( pLayer->GetBlendMode() );
							w.WriteInt( pLayer->GetFlag() );
							w.WriteInt( pLayer->GetTextureID() );
							w.WriteFloat( pLayer->GetAlpha() );
						}
						//if( m_mtls->GetMtl(i)->GetLayerCount() > 0 )
						//{
						//	for( )
						//	w.Write( &m_mtls->GetMtl(i)->vectorLayer[0], 
						//		sizeof( Mex2Layer ), 
						//		m_mtls->GetMtl(i)->GetLayerCount() );
						//}
					}
					w.EndChunk( DC_TAG( 'lays' ) );
					//   added 2003.12.09 for color animation
					w.StartChunk( DC_TAG( 'cras' ) );
					{
						Mex2Material* pMtl = (Mex2Material*)m_mtls->GetMtl(i);
						int nColorAnimCount = pMtl->colorTracks.vectorColorTrack.size();
						for( int j = 0; j < nColorAnimCount; j++ )
						{
							w.StartChunk( DC_TAG( 'clra' ) );
							{
								w.WriteInt( pMtl->colorTracks.vectorColorTrack[j]->bTiling );
								w.WriteInt( pMtl->colorTracks.vectorColorTrack[j]->nUTile );
								w.WriteInt( pMtl->colorTracks.vectorColorTrack[j]->nVTile );
								w.WriteInt( pMtl->colorTracks.vectorColorTrack[j]->nStartFrame );
								w.WriteFloat( pMtl->colorTracks.vectorColorTrack[j]->fPlaybackRate );

								int nKeyCount =
									pMtl->colorTracks.vectorColorTrack[j]->nKeyCount;
								w.WriteInt( nKeyCount );
								if( nKeyCount > 0 )
								{

									w.Write( pMtl->colorTracks.vectorColorTrack[j]->pKeys,
										sizeof( Mex2ColorKey ),
										nKeyCount );
								}
							}
							w.EndChunk( DC_TAG( 'clra' ) );
						}
					}
					w.EndChunk( DC_TAG( 'cras' ) );
				}
				w.EndChunk( DC_TAG( 'matl' ) );
			}
		}

	}
	w.EndChunk( DC_TAG( 'mtls' ) );
	w.StartChunk( DC_TAG( 'geom' ) );
	{
		if( m_geometry )
		{
			w.WriteInt(0);//added,jiayi,[09.04.07]
			for( int i = 0; i < m_geometry->vectorChunk.size(); i++ )
			{
				Mex2GeoChunk* pGeoChunk = m_geometry->vectorChunk[i];
				CMexChunkData* pChunk = pGeoChunk->m_ChunkData;
				w.StartChunk( DC_TAG( 'chks' ) );
				{
					
					w.WriteInt( pChunk->m_nVertexCount );
					w.WriteInt( pChunk->m_nFaceCount );
					w.WriteInt( pChunk->m_nMtlId );

					int nVertexCount = pChunk->m_nVertexCount;
					int nFaceCount = pChunk->m_nFaceCount;
					w.Write( pChunk->m_pVertices, sizeof( Vector ), nVertexCount );
					w.Write( pChunk->m_pNormals, sizeof( Vector ), nVertexCount );

					w.Write( pChunk->m_pUVs[0], sizeof( float )*2, nVertexCount );
					
					w.Write( pChunk->m_pBoneGroupIndices, sizeof( BYTE ), nVertexCount );
					w.Write( pChunk->m_pFaces, sizeof( Mex2Face ), nFaceCount );

					//   added 2005.10.22
					// 如果存在多重纹理坐标
					// 13906016902 13950063913
 					w.StartChunk( DC_TAG( 'mtuv' ) );
 					{
 						w.WriteInt( pChunk->m_shUVLayerCount );
 						for( int nLayer = 1; nLayer < pChunk->m_shUVLayerCount; nLayer++ )
 						{
 							if( pChunk->m_pUVs[nLayer] )
 								w.Write( pChunk->m_pUVs[nLayer], sizeof( float )*2, nVertexCount );
 							else
 							{
 								// 安全措施，确保不因空指针当机
 								for( int nVert = 0; nVert < nVertexCount*2; nVert++ )
 									w.WriteFloat( 0.0f );
 							}
 						}
						{
							// 光照图UV索引
							if( pChunk->m_shUVLayerCount > 1 )
								w.WriteInt( pChunk->m_shLightmapLayer );
						}
 					}
 					w.EndChunk( DC_TAG( 'mtuv' ) );

					w.StartChunk( DC_TAG( 'vcol' ) );
					{
						if( pChunk->m_pColors )
							w.Write( pChunk->m_pColors, sizeof(DWORD), nVertexCount );
					}
					w.EndChunk( DC_TAG( 'vcol' ) );

					w.StartChunk( DC_TAG( 'gcpt' ) );
					{
						w.WriteInt( pChunk->m_property.nType );
						w.WriteDwordChunk( 'flag', pChunk->m_property.dwFlag );
					}
					w.EndChunk( DC_TAG( 'gcpt' ) );
					//   added 2005.10.09

				
					w.StartChunk( DC_TAG( 'name' ) );
					{
						const char* pszPartName = pChunk->GetName();
						if( pszPartName )
						{
							char szPartName[MEX2_MAX_NAME];
							ZeroMemory( szPartName, sizeof( szPartName ) );
							strcpy( szPartName, pszPartName);
							w.Write( szPartName, MEX2_MAX_NAME, 1 );
						}
					}
					w.EndChunk( DC_TAG( 'name' ) );

				}
				w.EndChunk( DC_TAG( 'chks' ) );
			}
		}
	}
	w.EndChunk( DC_TAG( 'geom' ) );

	w.StartChunk( DC_TAG( 'sklt' ) );
	{
		Mex2Skeleton* pSkeleton = (Mex2Skeleton*)m_skeleton;
		if( pSkeleton )
		{
			w.WriteInt( pSkeleton->vectorBone.size() );
			w.WriteInt( pSkeleton->nRootBoneCount );
			w.Write( pSkeleton->pnRootBoneIds,
				sizeof( int ), pSkeleton->nRootBoneCount );
			if( GetVersion() >= 108 )
			{
				// 读关键帧表，所有骨骼关键帧从小到大
				if( pSkeleton->GetKeyFrameTimeList().size() > 0 )
				{
					w.WriteInt( pSkeleton->GetKeyFrameTimeList().size() );
					for( int i=0; i<pSkeleton->GetKeyFrameTimeList().size(); ++i )
					{
						w.WriteInt( pSkeleton->GetKeyFrameTimeList()[i] );
					}
				}
				else if( pSkeleton->m_bSpecialModel )
					w.WriteInt( -1 );
				else 
					w.WriteInt( 0 );

				// 写入Tcb表
				w.WriteInt( pSkeleton->m_vTcbList.size() );
				if( pSkeleton->m_vTcbList.size() > 0 )
				{
					for( int i=0; i<pSkeleton->m_vTcbList.size(); ++i )
					{
						w.WriteFloat(pSkeleton->m_vTcbList[i].fTension*100.f);
						w.WriteFloat(pSkeleton->m_vTcbList[i].fContinuity*100.f);
						w.WriteFloat(pSkeleton->m_vTcbList[i].fBias*100.f);
					}
				}
			}

			for( int i = 0; i < pSkeleton->vectorBone.size(); i++ )
			{
				Mex2Bone* pBone = pSkeleton->vectorBone[i];
				w.StartChunk( DC_TAG( 'bone' ) );
				{
					//w.WriteString( pBone->szName );
					w.Write( pBone->szName, MEX2_MAX_NAME, 1 );
					w.WriteInt( pBone->nParentId );
					w.WriteInt( pBone->nChildCount );
					for( int b = 0; b < pBone->nChildCount; b++ )
						w.WriteInt( pBone->pnChildIds[b] );

					BOOL bExpKeyframeTrack = FALSE;
					if( ( dwFlag & eMex_SaveFlag_ConvertBoneMatrixToTranslationAndRotation ) &&
						pBone->pTrans )
						bExpKeyframeTrack = TRUE;

					if( pBone->pTrans || pBone->m_pTrack )
					{
						w.StartChunkWithTag( 'trk2' );
						{
							w.WriteInt( pBone->nFrameCount );
							if( GetVersion() < 108 || pSkeleton->m_bSpecialModel || pBone->m_bFullFrame)
							{
								w.Write( pBone->pTrans, sizeof( Vector ), pBone->nFrameCount );
								w.Write( pBone->pQuats, sizeof( Quaternion ), pBone->nFrameCount );
							}
							else if( pBone->m_pTrack )
							{
								// 新关键帧格式
								// 检索骨骼名，用'_'替代空格
								w.Write( (void*)&pBone->m_pTrack->m_kInitTrans, sizeof( Vector ),	1 );
								w.Write( (void*)&pBone->m_pTrack->m_kInitQuat, sizeof( Quaternion ), 1 );

								Vector kTrans0;
								Quaternion kQuat0;
								MeMatrix m;
								D3DXMatrixInverse( (D3DXMATRIX*)&m, NULL, (D3DXMATRIX*)&pBone->matFrame0Inv );
								ConvertMatrixToTranslationAndRotation(m, kTrans0, kQuat0);
								w.Write( (void*)&kTrans0, sizeof( Vector ),	1 );
								w.Write( (void*)&kQuat0, sizeof( Quaternion ), 1 );

								w.WriteInt( pBone->m_pTrack->GetKeyFrames().size() );
								if( pBone->m_pTrack->GetKeyType() == AnimationTrack::eKT_Tcb )
									w.WriteInt( 1 );
								else 
									w.WriteInt( 0 );

								if( pBone->m_pTrack->GetKeyFrames().size() > 0 )
								{
									for(int j=0; j<pBone->m_pTrack->GetKeyFrames().size(); ++j)
									{
										if( pBone->m_pTrack->GetKeyType() == AnimationTrack::eKT_Tcb )
										{
											TcbKeyFrame* pTcbKey = (TcbKeyFrame*)pBone->m_pTrack->GetKeyFrames()[j];
											w.WriteInt( pTcbKey->nFrameId );
											w.WriteInt( pTcbKey->ucPosSpace );
											w.WriteInt( pTcbKey->ucRotSpace );
											w.Write( (void*)&pTcbKey->kTrans, sizeof( Vector ), 1 );
											w.Write( (void*)&pTcbKey->kQuat, sizeof( Quaternion ), 1 );
											w.WriteInt( pTcbKey->m_iTcbIndex );
										}
										else
										{
											w.WriteInt( pBone->m_pTrack->GetKeyFrames()[j]->nFrameId );
											w.WriteInt( pBone->m_pTrack->GetKeyFrames()[j]->ucPosSpace );
											w.WriteInt( pBone->m_pTrack->GetKeyFrames()[j]->ucRotSpace );
											w.Write( (void*)&pBone->m_pTrack->GetKeyFrames()[j]->kTrans, sizeof( Vector ), 1 );
											w.Write( (void*)&pBone->m_pTrack->GetKeyFrames()[j]->kQuat, sizeof( Quaternion ), 1 );
										}
									}
								}

								// 保存KeyFrameIndexMap
								w.WriteInt( pBone->m_pTrack->m_KeyFrameIndexMap.size() );
								for( int j=0; j<pBone->m_pTrack->m_KeyFrameIndexMap.size(); ++j )
								{
									w.WriteInt( pBone->m_pTrack->m_KeyFrameIndexMap[j] );
								}
							}
						}
						w.EndChunkWithTag( 'trk2' );
					}
					else
					{
						//if( 1 )
						if( 0 )
						//if( dwFlag & eMex_SaveFlag_ConvertBoneMatrixToTranslationAndRotation )
						{
							w.StartChunkWithTag( 'trk2' );
							{
								w.WriteInt( pBone->nFrameCount );
								std::vector<Vector> trans;
								std::vector<Quaternion> rotations;
								for( int nFrame = 0; nFrame < pBone->nFrameCount; nFrame++ )
								{
									Vector v;
									Quaternion q;
									ConvertMatrixToTranslationAndRotation( pBone->pMatrices[nFrame], v, q );
									trans.push_back( v );
									rotations.push_back( q );

								}
								w.Write( &trans[0], sizeof(Vector), pBone->nFrameCount );
								w.Write( &rotations[0], sizeof(Quaternion), pBone->nFrameCount );
							}
							w.EndChunkWithTag( 'trk2' );
						}
						else 
						{
							w.StartChunk( DC_TAG( 'trck' ) );
						
							if( dwFlag & eMex_SaveFlag_OnlyFirstFrame )
							{
								w.WriteInt( 1 );
								w.Write( pBone->pMatrices, 
									sizeof( MeMatrix ), 1 );
							}
							else
							{
								w.WriteInt( pBone->nFrameCount );

								w.Write( pBone->pMatrices, 
									sizeof( MeMatrix ), pBone->nFrameCount );

							}
							w.EndChunk( DC_TAG( 'trck' ) );
						}
						

					}

					
					/*w.StartChunk( DC_TAG( 'visi' ) );
					{
						if( pBone->pVisible )
						{
							BOOL bHasUnvisibleFrame = FALSE;
							// 如果不是每一帧都是可见的，那么就需要存储
							for( int i = 0; i < pBone->nFrameCount; i++ )
							{
								if( !pBone->pVisible[i] )
								{
									bHasUnvisibleFrame = TRUE;
									break;
								}
							}
							if( bHasUnvisibleFrame )
							{
								if( dwFlag & eMex_SaveFlag_OnlyFirstFrame )
								{
									w.Write( pBone->pVisible, 
										sizeof( bool ), 1 );
								}
								else
								{
									w.Write( pBone->pVisible, 
										sizeof( bool ), pBone->nFrameCount );
								}
							}

						}
					}
					w.EndChunk( DC_TAG( 'visi' ) );

					w.StartChunk( DC_TAG( 'vis2' ) );
					{
						if( pBone->pVisible || pBone->pVisibleFloat )
						{
							BOOL bHasUnvisibleFrame = FALSE;
                            if( pBone->pVisibleFloat )
                            {
                                if( m_version->dwVersion > 103 && m_version->dwVersion < 106 )// added, jiayi, [2010/7/29], new
                                {
                                    // 如果不是每一帧都是可见的，那么就需要存储
                                    for( int i = 0; i < pBone->nFrameCount; i++ )
                                    {
                                        if( pBone->pVisibleFloat[i] > 0)
                                        {
                                            bHasUnvisibleFrame = TRUE;
                                            break;
                                        }
                                    }
                                    if( bHasUnvisibleFrame )
                                    {
                                        if( dwFlag & eMex_SaveFlag_OnlyFirstFrame )
                                        {
                                            w.Write( pBone->pVisibleFloat, 
                                                sizeof( float ), 1 );
                                        }
                                        else
                                        {
                                            w.Write( pBone->pVisibleFloat, 
                                                sizeof( float ), pBone->nFrameCount );
                                        }
                                    }
                                }
                            }
							// 如果不是每一帧都是可见的，那么就需要存储
                            if( pBone->pVisible )
                            {
                                for( int i = 0; i < pBone->nFrameCount; i++ )
                                {
                                    if( !pBone->pVisible[i] )
                                    {
                                        bHasUnvisibleFrame = TRUE;
                                        break;
                                    }
                                }
                                if( bHasUnvisibleFrame )
                                {
                                    if( dwFlag & eMex_SaveFlag_OnlyFirstFrame )
                                    {
                                        w.Write( pBone->pVisible, 
                                            sizeof( BOOL ), 1 );
                                    }
                                    else
                                    {
                                        w.Write( pBone->pVisible, 
                                            sizeof( BOOL ), pBone->nFrameCount );
                                    }
                                }
                            }
						}
					}
					w.EndChunk( DC_TAG( 'vis2' ) );*/

					/*
					 * 2012.6.7 废弃了VisibleBool(vis2), 直接使用VisibleFloat(visf)
					 */
					w.StartChunk( DC_TAG( 'visf' ) );
					{
						if (pBone->pVisibleFloat != NULL)
						{							
							if( m_version->dwVersion >= 105 )// added, jiayi, [2010/7/29]
							{
								// 注意: 当所有的Bone的Visibility都是1.0f时, 为了节省空间, 不写入Mex文件中
								BOOL bHasBlendFrame = FALSE;
								for( int i = 0; i < pBone->nFrameCount; i++ )
								{
									float fBoneVisibility = pBone->pVisibleFloat[i];
									if (fBoneVisibility >= 0.0f && fBoneVisibility < 1.0f)
									{
										bHasBlendFrame = TRUE;
										break;
									}
								}
								if (bHasBlendFrame)
								{
									w.Write( &pBone->pVisibleFloat[0], sizeof( float ), pBone->nFrameCount);
								}
							}					

						}
					}
					w.EndChunk( DC_TAG( 'visf' ) );
				}
				w.EndChunk( DC_TAG( 'bone' ) );
			}
		}
	}
	w.EndChunk( DC_TAG( 'sklt' ) );

	w.StartChunk( DC_TAG( 'bgps' ) );
	{
		if( m_boneGroups )
		{
			for( int i = 0; i < m_boneGroups->vectorBoneGroup.size(); i++ )
			{
				w.StartChunk( DC_TAG( 'bgrp' ) );
				{
					//int nInflCount = m_boneGroups->GetBoneGroup(i)->nBoneCount;
					int nInflCount = m_boneGroups->GetBoneGroup(i)->GetBoneCount();
					assert( nInflCount > 0 && "mex error, infl count must > 0" );
					w.WriteInt( nInflCount );
					for( int b = 0; b < nInflCount; b++ )
					{
						//int nBoneId = m_boneGroups->GetBoneGroup(i)->pnBoneIds[b];
						int nBoneId = m_boneGroups->GetBoneGroup(i)->GetBoneID(b);
						w.WriteInt( nBoneId );
					}
					// 写入骨骼权重
					if( GetVersion() >= 102 )
					{
						for( int b = 0; b < nInflCount; b++ )
						{
							float fBoneWeight = m_boneGroups->GetBoneGroup(i)->GetBoneWeight(b);
							w.WriteFloat( fBoneWeight );
						}
					}
				}
				w.EndChunk( DC_TAG( 'bgrp' ) );
			}
		}
	}
	w.EndChunk( DC_TAG( 'bgps' ) );

	w.StartChunk( DC_TAG( 'atts' ) );
	{
		if( m_attachments )
		{
			//w.WriteInt( m_attachments->m_Attachments.size() );
			for( int nAtt = 0; nAtt < m_attachments->m_Attachments.size(); nAtt++ )
			{
				Mex2Attachment* pAttachment = &m_attachments->m_Attachments[nAtt];
				w.StartChunkWithTag( 'att0' );
				{
					//w.Write( &m_attachments->m_Attachments[nAtt], )
					w.WriteInt( pAttachment->nAttachBoneID );
					w.Write( pAttachment->pszName, MEX2_MAX_NAME, 1 );
					w.Write( &pAttachment->matInit, sizeof( MeMatrix ), 1 );
				}
				w.EndChunkWithTag( 'att0' );
			}
			
		}
	}
	w.EndChunk( DC_TAG( 'atts' ) );

	
	//w.StartChunk( DC_TAG( 'lgts' ) );
	//{
	//	if( m_lights )
	//	{
	//		for( int nLight = 0; nLight < m_lights->GetLightCount(); nLight++ )
	//		{
	//			w.StartChunk( DC_TAG( 'olt2' ) );// omni light
	//			{
	//				Mex2Light* pLight = (Mex2Light*)m_lights->GetLight( nLight );
	//				w.WriteInt( pLight->GetFlag() );
	//				w.Write( (void*)pLight->GetName(), sizeof( char ), MEX2_MAX_NAME );
	//				w.WriteInt( pLight->GetParentBoneID() );
	//				w.Write( pLight->GetPivot(), sizeof( Vector ), 1 );
	//				w.WriteFloat( pLight->GetRange() );
	//				w.WriteFloat( pLight->GetIntense() );

	//				w.Write( pLight->GetAttenuration(), sizeof( float ), 3 );
	//				w.WriteInt( pLight->GetFrameCount() );
	//				for( int nFrame = 0; nFrame < pLight->GetFrameCount(); nFrame++ )
	//				{
	//					w.Write( pLight->GetColorTrack(), sizeof( float ), 3 );
	//				}
	//				//w.Write( pLight->GetColor(), sizeof( float ), 3 );
	//			}
	//			w.EndChunk( DC_TAG( 'olt2' ) );
	//		}
	//	}
	//}
	//w.EndChunk( DC_TAG( 'lgts' ) );
	

	w.StartChunk( DC_TAG( 'rbes' ) );
	{
		if( m_ribbonEmitters )
		{
			for( int i = 0; i < m_ribbonEmitters->vectorRibbonEmitter.size(); i++ )
			{
				Mex2RibbonEmitter* re = &m_ribbonEmitters->vectorRibbonEmitter[i];
				w.StartChunk( DC_TAG( 'ribb' ) );
				{
					w.Write( re->pSetting, sizeof( Mex2RibbonEmitterSetting ), 1 );
					w.StartChunkWithTag( 'bprt' );
					{
						if( strlen( re->GetBindPartName() ) > 0 )
						{
							char s[MEX2_MAX_NAME] = "";
							strcpy( s, re->GetBindPartName() );
							w.Write( s, MEX2_MAX_NAME, 1 );
						}
					}
					w.EndChunkWithTag( 'bprt' );
				}
				w.EndChunk( DC_TAG( 'ribb' ) );
			}
		}
	}
	w.EndChunk( DC_TAG( 'rbes' ) );

	w.StartChunk(DC_TAG('pems'));
	{
		if (m_particleEmitters != NULL)
		{
			for (int i = 0; i < m_particleEmitters->vectorParticleEmitter.size(); ++i)
			{
				Mex2ParticleEmitter *e = m_particleEmitters->vectorParticleEmitter[i];
				
				/*
				* 2012.6.9 wangshuai
				* 武将三国, 统一使用最新的粒子发射器版本, 即Mex2ParticleEmitterSetting4
				*/
				w.StartChunk( DC_TAG('pem4'));
				{
					w.Write(&e->setting, sizeof(Mex2ParticleEmitterSetting4), 1);

					// 绑定部位
					w.StartChunkWithTag('bprt');
					{
						if (strlen(e->m_szBindPartName) > 0)
						{
							w.Write(e->m_szBindPartName, MEX2_MAX_NAME, 1);
						}
					}
					w.EndChunkWithTag('bprt');

					// 是否使用序列帧
					w.WriteIntChunk('utbc', e->m_bUseTimeBasedCell);

					// 序列帧循环次数
					w.WriteIntChunk('sqlt', e->m_nSeqLoopTimes);

					// 是否旋转
					w.WriteIntChunk('brp', e->m_bRotateParticle);

					// 旋转360度所需时间
					w.WriteIntChunk('rpds',e->m_nRotate360DegreeCostTime);

					// 随机方向
					w.WriteIntChunk('brdd', e->m_bRandomDir);

					// 粒子是否跟随发射器的变换而旋转增加开关, bNoSelfRatate: 无自旋转(version > 108)
					w.WriteIntChunk('bnsr', e->m_bNoSelfRotate);

					// UV动画是否随机产生第一帧(version > 109)
					w.WriteIntChunk('brfc', e->m_bUVRandomFirstCell);

					// XYQuad模式下, 是否放平(version > 110)
					w.WriteIntChunk('bxyw', e->m_bXYInWorldSpace);
				}
				w.EndChunk(DC_TAG('pem4'));
			}
		}
	}
	w.EndChunk(DC_TAG('pems'));

	BOOL bOK = w.SaveToFile( pszFilename );

	w.Destroy();

	delete[] pBuffer;

	return bOK;
	//return FALSE;
	unguard;
}

void Mex2::BuildLocalBBox()
{
	for (int i = 0; i < m_geometry->vectorChunk.size();++i)
	{
		CMexChunkBase* pBase = m_geometry->vectorChunk[i];
// 		if(pBase->IsHelper())
// 			continue;
		m_vMin.x = min(m_vMin.x, pBase->GetMin()->x);
		m_vMin.y = min(m_vMin.y, pBase->GetMin()->y);
		m_vMin.z = min(m_vMin.z, pBase->GetMin()->z);
		m_vMax.x = max(m_vMax.x, pBase->GetMax()->x);
		m_vMax.y = max(m_vMax.y, pBase->GetMax()->y);
		m_vMax.z = max(m_vMax.z, pBase->GetMax()->z);
	}
	GetLocalBBox()->BuildAABB(m_vMax,m_vMin);
}
Mex2::MemoryBlock::MemoryBlock():
m_nBufferSize(0),
m_pbyBuffer(NULL)
{}
Mex2::MemoryBlock::~MemoryBlock()
{
	Destory();
}
BOOL Mex2::MemoryBlock::Create( BYTE* pbyBuffer, int nBufferSize )
{
	if( !pbyBuffer || nBufferSize == 0 )
	{
		assert( false );
		return FALSE;
	}
	m_nBufferSize = nBufferSize;
	m_pbyBuffer = MeDefaultNew BYTE[m_nBufferSize];
	memcpy( m_pbyBuffer, pbyBuffer, m_nBufferSize );
	return TRUE;
}
BOOL Mex2::MemoryBlock::Create( FILE* fp, int nBufferSize )
{
	if( nBufferSize == 0 )
	{
		assert( false );
		return FALSE;
	}
	m_nBufferSize = nBufferSize;
	m_pbyBuffer = MeDefaultNew BYTE[m_nBufferSize];
	fread( m_pbyBuffer, m_nBufferSize, 1, fp );
	return TRUE;
}
Mex2Pointer Mex2::MemoryBlock::GetPointer()
{
	Mex2Pointer p( m_pbyBuffer );
	return p;
}
BOOL Mex2::LoadFromMemory( BYTE* pbyBuffer, int nBufferSize )
{
	guardfunc;
	//CSALocker locker(this);
	Mex2Pointer p(pbyBuffer);

	while( p.c < (char*)pbyBuffer+nBufferSize )
	{
		switch( MEX_TAG( *p.dw ) )
		{
		case 'vers':
			{
				p.dw++;
				int size = *p.i++;
				m_version = MeNew Mex2Version;
				m_VersionMB.Create( p.byte, size );
				m_version->Read( m_VersionMB.GetPointer(), m_VersionMB.GetBufferSize() );
				m_VersionMB.Destory();
				p.c += size; 
			}
			break;
		case 'texs':
			{
				p.dw++;
				int size = *p.i++;
				m_textures = MeNew Mex2Textures;
				m_TexturesMB.Create( p.byte, size );
				m_textures->Read( m_TexturesMB.GetPointer(), m_TexturesMB.GetBufferSize() );
				//m_textures->Read( p, size );
				m_TexturesMB.Destory();
				p.c += size; 
			}
			break;
		case 'mtls':
			{
				p.dw++;
				int size = *p.i++;
				m_mtls = MeNew Mex2Materials;
				m_MtlsMB.Create( p.byte, size );
				m_mtls->Read( m_MtlsMB.GetPointer(), m_MtlsMB.GetBufferSize() );
				//m_mtls->Read( p, size );
				m_MtlsMB.Destory();
				p.c += size; 
			}
			break;
		case 'geom':
			{
				p.dw++;
				int size = *p.i++;
				m_geometry = MeNew Mex2Geometry;
				m_geometry->pSrcMex = this;
				m_GeometryMB.Create( p.byte, size );
				//m_geometry->Read( p, size );
				m_geometry->Read( m_GeometryMB.GetPointer(), m_GeometryMB.GetBufferSize() );
				m_GeometryMB.Destory();
				p.c += size; 
			}
			break;
		case 'sklt':
			{
				p.dw++;
				int size = *p.i++;
				//   added 2003.10.09
				m_skeleton = MeNew Mex2Skeleton;
				//m_skeleton->pMex = this;
				m_skeleton->SetMex( this );

				m_SkeletonMB.Create( p.byte, size );
				//m_skeleton->Read( p.c, size );
				m_skeleton->Read( m_SkeletonMB.GetPointer().c, m_SkeletonMB.GetBufferSize(), m_version->dwVersion );
				m_SkeletonMB.Destory();
				p.c += size; 
			}
			break;
		//case 'help':
		//	{
		//		p.dw++;
		//		int size = *p.i++;
		//		//   added 2003.10.09
		//		m_pHelpers = MeNew Mex2Skeleton;
		//		//m_skeleton = m_pSrcSkeleton;
		//		//m_skeleton->pMex = this;
		//		m_pHelpers->SetMex( this );

		//		m_pHelpers->Read( p.c, size );
		//		p.c += size; 
		//	}
		//	break;
		case 'bgps':
			{
				p.dw++;
				int size = *p.i++;
				m_boneGroups = MeNew Mex2BoneGroups;
				m_BoneGroupsMB.Create( p.byte, size );
				//m_boneGroups->Read( p, size );
				m_boneGroups->Read( m_BoneGroupsMB.GetPointer()	, m_BoneGroupsMB.GetBufferSize(), GetVersion() );
				m_BoneGroupsMB.Destory();
				p.c += size; 
			}
			break;
		case 'atts':
			{
				p.dw++;
				int size = *p.i++;
				m_attachments = MeNew Mex2Attachments;
				m_AttachmentsMB.Create( p.byte, size );

				//m_attachments->Read( p, size );
				m_attachments->Read( m_AttachmentsMB.GetPointer(), m_AttachmentsMB.GetBufferSize() );
				m_AttachmentsMB.Destory();
				p.c += size; 
			}
			break;
		case 'rbes':
			{
				p.dw++;
				int size = *p.i++;
				m_ribbonEmitters = MeNew Mex2RibbonEmitters;
				m_RibbonEmitterMB.Create( p.byte, size );

				//m_ribbonEmitters->Read( p, size );
				m_ribbonEmitters->Read( m_RibbonEmitterMB.GetPointer(), m_RibbonEmitterMB.GetBufferSize() );
// 				m_RibbonEmitterMB.Destory();
				p.c += size; 

				m_ribbonEmitters->Bind( this );
			}
			break;

		case 'pems':
			{
				p.dw++;
				int size = *p.i++;
				m_particleEmitters = MeNew Mex2ParticleEmitters;
				m_ParticleEmittersMB.Create( p.byte, size );
				//m_particleEmitters->Read( p, size );

				//modified by zhuomeng.hu		[8/6/2010]
				m_particleEmitters->Read( m_ParticleEmittersMB.GetPointer(), m_ParticleEmittersMB.GetBufferSize(), GetVersion() );

				m_particleEmitters->Bind( this );
				m_ParticleEmittersMB.Destory();
				p.c += size; 

			}
			break;
		//case 'lgts':
		//	{
		//		p.dw++;
		//		int size = *p.i++;
		//		m_lights = MeNew Mex2Lights;
		//		m_lights->Read( p, size );
		//		m_lights->Bind( this );
		//		p.c += size;
		//	}
		//	break;
		default:
			{
				p.dw++;
				int size = *p.i++;
				p.c += size; 
				break;
			}
			break;
		}
	}
	InitializeDefaultSequece();
// 	m_nFrameId = 0;

	if (m_geometry)
	{
		if (GetSkeleton() && (GetSkeleton()->GetBoneCount() > 1 || GetSkeleton()->GetBone(0)->GetFrameCount() > 2))
		{
			for (int i = 0; i < m_geometry->vectorChunkData.size();++i)
			{
				CMexChunkData* chunkData = m_geometry->vectorChunkData[i];
				// added, [9/2/2010 zhangjiayi]
				// 是否是静态模型（骨骼为1，帧数为2）
				int nNumBone = GetSkeleton()->GetBoneCount();
				IMexBone* pBone = GetSkeleton()->GetBone(0);
				if( pBone == NULL )
					return FALSE;
				
				int nFrameCount = pBone->GetFrameCount();
				bool bIsStatic = ( nNumBone == 1 && 2 == nFrameCount);					

				if (bIsStatic)
				{
					chunkData->GetProperty().nType = Mex2GeoChunkProperty::eStatic;
				}
				else
				{
					if (chunkData->GetProperty().nType == Mex2GeoChunkProperty::eStatic )
					{
						//char lwrName[MAX_PATH] = {0};
						//const char* pszName = chunkData->GetName();
						//strncpy( lwrName, pszName, MAX_PATH );
						//strlwr(lwrName);
						//if (strstr(lwrName, "common") || 0 == strstr(lwrName, "sceneobject") )					
						bool skeleton = GetBoneGroups() && GetBoneGroups()->GetBoneGroupCount() > 0;
						if (skeleton)
						{
							if (graphics::ShaderManager::instance()->supportSkeletonShader() )
								chunkData->GetProperty().nType = Mex2GeoChunkProperty::eSkeleton;
							else
								chunkData->GetProperty().nType = Mex2GeoChunkProperty::eDynamic;					
						}
					}
					// added, [8/18/2010 zhangjiayi]
					// 如果是eSkeleton类型并且不支持骨骼shader，则转变为eDynamic
					if( chunkData->GetProperty().nType == Mex2GeoChunkProperty::eSkeleton &&
						( !graphics::ShaderManager::instance()->supportSkeletonShader() ) )
					{
						chunkData->GetProperty().nType = Mex2GeoChunkProperty::eDynamic;
					}
				}
			}
		}

		for (int i = 0; i < m_geometry->vectorChunkData.size();++i)
		{
			CMexChunkData* chunkData = m_geometry->vectorChunkData[i];
			Mex2GeoChunk* chunk = (Mex2GeoChunk*)CMexChunkData::CreateMexChunk(chunkData);
			chunk->m_pSrcMex = this;
			chunk->createBuffers();
			if( !m_bKeepOldData )
				chunk->AfterCreateBuffers();
			m_geometry->vectorChunk.push_back(chunk);

		}
		BuildLocalBBox();		
	}

	//   added 2004.07.16
	if( m_geometry &&
		m_boneGroups )
	{
		for( int i = 0; i < m_geometry->vectorChunk.size(); i++ )
		{
			m_geometry->vectorChunk[i]->CheckIsSingleBoneInfl();
		}
	}


// 	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
// 	if( GetMe3dConfig()->m_bUseSkinMesh &&
// 		pDev && !HugeModel )
// 	{
// 		m_pSkinMesh = MeNew MexSkinMesh;
// 		if( m_pSkinMesh->ConvertToIndexedBlendedMesh( pDev, this ) )
// 		{
// 		}
// 		else
// 		{
// 			delete m_pSkinMesh;
// 			m_pSkinMesh = NULL;
// 		}
// 
// 	}
	return TRUE;
	unguard;
}

BOOL Mex2::CreateParticleEmitters()
{
	if (m_particleEmitters != NULL)
		return FALSE;

	m_particleEmitters = MeNew Mex2ParticleEmitters;
	return TRUE;
}

void Mex2::DestroyParticleEmitters()
{
	if ( m_particleEmitters != NULL)
	{
		for (int i = 0; i < m_particleEmitters->vectorParticleEmitter.size(); ++i)
			m_particleEmitters->vectorParticleEmitter[i]->Release();
	}
	MEX2_SAFE_DELETE( m_particleEmitters );
}

BOOL Mex2::LoadFromFile( const char* pszMexFilename, DWORD dwFlag, bool bKeepCloneMemory/* = true*/ )
{
	guardfunc;
	DWORD time = HQ_TimeGetTime();
	//if( m_bSmartLoading )
	//dwFlag = 0;;
	m_dwLoadFlag = dwFlag;

	//CSALocker locker(this);
	if( !pszMexFilename )
		return FALSE;
	char szFileName[MAX_PATH] = "";
	strcpy( szFileName, pszMexFilename );
	

// 	std::string szPathUser = szFileName;
// 	if( _stricmp( szPathUser.substr( 0, strlen(SCENEOBJECT_PATH_SingleFloor) ).c_str(), 
// 		SCENEOBJECT_PATH_SingleFloor ) == 0 )
// 	{
// 		HugeModel = TRUE;
// 	}
// 	if( _stricmp( szPathUser.substr( 0, strlen(SCENEOBJECT_PATH_HugeObject) ).c_str(), 
// 		SCENEOBJECT_PATH_HugeObject ) == 0 )
// 	{
// 		HugeModel = TRUE;
// 	}
// 
// 	if( _stricmp( szPathUser.substr( 0, strlen(SCENEOBJECT_PATH_Interface) ).c_str(), 
// 		SCENEOBJECT_PATH_Interface ) == 0 )
// 	{
// 		HugeModel = TRUE;
// 	}





	BOOL bVFS = TRUE;
	BOOL bIsEffect = FALSE;
	int nSize = 0;
	
	BYTE*	pbyMemory = NULL;
	int		nMemorySize = 0;
	{
		BOOL bfOpen = FALSE;
		//int nSize = 0;
		// commented out, jiayi, [2009/10/8]
// 		if( !g_ModelVfs.IsOpen() )
// 		{
// 			g_ModelVfs.LoadVFS( MODEL_PACK );
// 		}
		f_Handle* fp =packet_namespace::w_fopen(szFileName, "rb" );
		if (!fp)
		{
			return FALSE;
		}
		packet_namespace::w_fseek ( fp, 0, SEEK_END );
		nSize = packet_namespace::w_ftell( fp );
		pbyMemory = MeDefaultNew BYTE[nSize];
		packet_namespace::w_rewind( fp );
        if( !pbyMemory )
		{
			packet_namespace::w_fclose( fp );
            return FALSE;
		}
		
        packet_namespace::w_fread( pbyMemory, nSize, 1, fp );
		packet_namespace::w_fclose( fp );

// 		File fp;
// 		if( !fp.fopen( szFileName, "rb" ) )
// 		{
// 			size_t size = 0;
// 			if (!g_ModelVfs.GetUnitLength(szFileName, size))
// 			{
// 				return FALSE;
// 			}
// 			pbyMemory = MeDefaultNew unsigned char[size];
// 			if (!g_ModelVfs.GetUnit(szFileName, pbyMemory, size))
// 			{
// 				delete []pbyMemory;
// 				pbyMemory =NULL;
// 				return FALSE;
// 			}
// 			nSize = size;	
// 			bVFS = TRUE;
// 		}
// 		else
// 		{
// 			pbyMemory = fp.GetBuffer();
// 			nSize = fp.GetBufferSize();
// 			bfOpen = TRUE;
// 			if( bfOpen )
// 			{
// 				fp.fclose( false );
// 			}
// 		}
		//if( bIsEffect )
		//{
		//	gs_EffectCache.Register( szFileName, m_pbyMemory, nSize );
		//}
	}
	MeOutputLog::Instance()->Print( "Loading Mex Files: %s.\n", szFileName );

	if ( !LoadFromMemory( pbyMemory, nSize ) )
	{
		delete[] pbyMemory;
		m_pbyMemory = NULL;
		return FALSE;
	}

	nMemorySize = nSize;
	// 不删除pbyMemory，因为在Clone中要使用
	if( bKeepCloneMemory )
		m_pbyMemory = pbyMemory;
	else
	{
		delete[] pbyMemory;
		m_pbyMemory = NULL;
	}
	m_nMemorySize = nSize;

	std::string strLowerRelativePath;

	GetLowerRelativePath( szFileName, strLowerRelativePath );
	strncpy_s( m_szFilename, strLowerRelativePath.c_str(), sizeof( m_szFilename ) / sizeof( char ) - 1 );

	return TRUE;
	unguard;

}



Mex2::Mex2():
//m_pbyMemory(NULL),
//m_nMemorySize(0),
m_pSequence(NULL),
//
m_version(NULL),
m_textures(NULL),
m_mtls(NULL),
m_geometry(NULL),
m_skeleton(NULL),
//m_pHelpers(NULL),
// m_sequences(NULL),
m_boneGroups(NULL),
m_ribbonEmitters(NULL),
//m_hitPointsSet(NULL),
m_particleEmitters(NULL),
m_attachments(NULL),
//m_lights(NULL),
//
// m_pSkinMesh(NULL),
m_dwSkeletonOffsetInFile(0),
m_dwSkeletonChunkSize(0),
//m_bSmartLoading(TRUE)
m_dwLoadFlag(0),
m_pbyMemory(NULL),
m_nMemorySize(0),
m_nReallocBoneFrameCount(0),
m_bKeepOldData( false )
//
//m_bHasOriginModelColor(FALSE)
{
	guardfunc;
	//m_MemoryFactory.SetAllocSize( 32*1024 );
	m_ActionList.pMex = this;

    memset( m_szFilename, 0, sizeof(m_szFilename) );

	m_vMin = Vector(10000.f, 10000.f, 10000.f);
	m_vMax = Vector(-10000.f, -10000.f, -10000.f);
	unguard;
}
//void Mex2::TryCreateDiffuseBuffer()
DWORD Mex2::GetVersion()
{
	guardfunc;
	//CSALocker locker(this);
	if( m_version )
		return m_version->dwVersion;
	return 0;
	unguard;
}

// BOOL Mex2::SetSkeleton( IMexSkeleton* pSkeleton )
// {
// 	guardfunc;
// 	//CSALocker locker(this);
// 	if( !GetSkeleton()->IsSameFormat( pSkeleton ) )
// 		return FALSE;
// 	m_skeleton = pSkeleton;
// 	return TRUE;
// 	unguard;
// }

// BOOL Mex2::BindSkeleton( IMexSkeleton* pSkeleton )
// {
// 	guardfunc;
// 	//CSALocker locker(this);
// 	if( !GetSkeleton() ||
// 		!pSkeleton)
// 	{
// 		assert( false );
// 		return FALSE;
// 	}
// 	if( !GetSkeleton()->IsSameFormat( pSkeleton ) )
// 	{
// 		return FALSE;
// 	}
// 	int nBoneCount = GetSkeleton()->GetBoneCount();
// 	std::vector<int> vectorRemap;
// 	vectorRemap.reserve( nBoneCount );
// 	vectorRemap.resize( nBoneCount );
// 	for( int nBone = 0; nBone < nBoneCount; nBone++ )
// 	{
// 		IMexBone* pSrcBone = GetSkeleton()->GetBone(nBone);
// 		vectorRemap[nBone] = pSkeleton->FindBone( pSrcBone->GetName() );
// 	}
// 	//if( GetBoneGroups() )
// 	//{
// 	//	for( int nBoneGroup = 0; nBoneGroup < GetBoneGroups()->GetBoneGroupCount(); nBoneGroup++ )
// 	//	{
// 	//		//IMexBoneGroup
// 	//	}
// 	//}
// 	//if( GetGeometry() )
// 	//{
// 	//	for( int nChunk = 0; nChunk < GetGeometry()->GetChunkCount(); nChunk++ )
// 	//	{
// 	//		IRenderable *pChunk = GetGeometry()->GetChunk( nChunk );
// 	//		BYTE* pbyBoneGroup
// 	//		for( int nBone = 0; nBone < pChunk->GetBoneGroupIndices())
// 	//	}
// 	//}
// 	return TRUE;
// 	unguard;
// }
// void Mex2::Mirror( DWORD dwFlag )
// {
// 	if( dwFlag & eCloneMirrorXAxis )
// 	{
// 		if( m_geometry )
// 		{
// 			for( int nChunk = 0; nChunk < m_geometry->vectorChunk.size(); nChunk++ )
// 			{
// 				Mex2GeoChunk* pChunk = m_geometry->vectorChunk[nChunk];
// 				// 顶点位置以x轴镜像
// 				//for( int nVert = 0; nVert < pChunk->m_nVertexCount; nVert++ )
// 				//{
// 				//	pChunk->m_pVertices[nVert].x *= -1;
// 				//	pChunk->m_pNormals[nVert].x *= -1;
// 				//	pChunk->m_pNormalPoints[nVert].x *= -1;
// 				//}
// 				// 反转面索引，
// 				for( int nFace = 0; nFace < pChunk->m_nFaceCount; nFace++ )
// 				{
// 					Mex2Face& face = pChunk->m_pFaces[nFace];
// 					int nTemp = face.nId[0];
// 					face.nId[0] = face.nId[1];
// 					face.nId[1] = nTemp;
// 				}
// 			}
// 		}
// 		if( m_skeleton )
// 		{
// 			// 骨骼运动按照x轴镜像
// 			for( int nBone = 0; nBone < m_skeleton->GetBoneCount(); nBone++ )
// 			{
// 				Mex2Bone* pBone = (Mex2Bone*)m_skeleton->GetBone( nBone );
// 
// 				
// 				if( pBone->pMatrices )
// 				{
// 					MeMatrix matMirrorX;
// 					MirrorMatrix( 0, &matMirrorX  );
// 					for( int nFrame = 0; nFrame < pBone->nFrameCount; nFrame++ )
// 					{
// 						MeMatrix& m = pBone->pMatrices[nFrame];
// 						//D3DXMatrixMultiply( (D3DXMATRIX*)&m,
// 						//	(D3DXMATRIX*)&m,
// 						//	(D3DXMATRIX*)&matMirrorX );
// 						//m.m[3][0] *= -1;
// 						//m.m[0][0] *= -1;
// 						//m.m[1][0] *= -1;
// 						//m.m[2][0] *= -1;
// 						//m.m[3][0] *= -1;
// 					}
// 					//D3DXMatrixInverse( 
// 					//	(D3DXMATRIX*)&pBone->matFrame0Inv, 
// 					//	NULL, 
// 					//	(D3DXMATRIX*)&pBone->pMatrices[0] );
// 				}
// 				//else if( pBone->pTrans )
// 				//{
// 				//	for( int nFrame = 0; nFrame < pBone->nFrameCount; nFrame++ )
// 				//	{
// 				//		Vector& vTrans = pBone->pTrans[nFrame];
// 				//		Quaternion& qRot = pBone->pQuats[nFrame];
// 				//		vTrans.x *= -1;
// 				//		D3DX
// 				//		D3DXQuaternionMultiply()
// 				//	}
// 				//	MeMatrix m;
// 				//	MakeMatrix( pBone->pTrans[0], pBone->pQuats[0], m );
// 				//	D3DXMatrixInverse( (D3DXMATRIX*)&pBone->matFrame0Inv, NULL, (D3DXMATRIX*)&m );
// 				//}
// 			}
// 		}
// 		if( m_particleEmitters )
// 		{
// 			for( int nEmitter = 0; nEmitter < m_particleEmitters->vectorParticleEmitter.size(); nEmitter++ )
// 			{
// 				Mex2ParticleEmitter* pEmitter = m_particleEmitters->vectorParticleEmitter[nEmitter];
// 				pEmitter->setting.vPivot.x *= -1;
// 				pEmitter->setting.vPlaneNormal.x *= -1;
// 				pEmitter->setting.vPlaneXAxis.x *= -1;
// 				pEmitter->setting.vPlaneYAxis.x *= -1;
// 			}
// 		}
// 		if( m_ribbonEmitters )
// 		{
// 			for( int nEmitter = 0; nEmitter < m_ribbonEmitters->vectorRibbonEmitter.size(); nEmitter++ )
// 			{
// 				Mex2RibbonEmitter& emitter = m_ribbonEmitters->vectorRibbonEmitter[nEmitter];
// 				emitter.pSetting->vLines[0].x *= -1;
// 				emitter.pSetting->vLines[1].x *= -1;
// 			}
// 		}
// 	}
// }
// 
IMex* Mex2::Clone( DWORD dwFlag )
{
	if( !m_pbyMemory )
		return NULL;

	Mex2* pMex = MeNew Mex2;///(Mex2*)GetEngine()->CreateMex();
	BOOL bSucc = pMex->LoadFromMemory( m_pbyMemory, m_nMemorySize );
	if( !bSucc )
	{
		pMex->Release();
		delete pMex;
		return NULL;
	}
	strcpy( pMex->m_szFilename, m_szFilename );

// 	if( dwFlag & eCloneMirrorXAxis )
// 		pMex->Mirror( dwFlag );
	
	return pMex;
}

// void Mex2::SetMexCfg( void* pvoidMexCfg )
// {
// 	if( !pvoidMexCfg )
// 	{
// 		assert( false );
// 		return;
// 	}
// 	MexCfg* pMexCfg = (MexCfg*)pvoidMexCfg;
// 	int nTotalFrame = 0;
// 	for( int nAction = 0; nAction < pMexCfg->m_sequences.m_vectorSequence.size(); nAction++ )
// 	{
// 		MexCfgSequence* seq = pMexCfg->m_sequences.m_vectorSequence[nAction];
// 		m_ActionList.AddAction( 
// 			seq->m_npStartFrameId.GetNumber(), 
// 			seq->m_npEndFrameId.GetNumber() );
// 		nTotalFrame += seq->m_npEndFrameId.GetNumber()-seq->m_npStartFrameId.GetNumber()+1;
// 	}
// 	int k = 0;
// 	
// }
BOOL Mex2::LoadAction( Mex2Action* action )
{
	// 快速定位到指定的action
	guardfunc;
	if( !action )
	{
		assert( false );
		return FALSE;
	}
	if( action->IsLoaded() )
	{
		assert( false );
	}
	DWORD time = HQ_TimeGetTime();
	f_Handle* fp = packet_namespace::w_fopen( m_szFilename, "rb" );
	if( !fp )
		return FALSE;
	// 定位到骨骼起点
	packet_namespace::w_fseek ( fp, m_dwSkeletonOffsetInFile, SEEK_SET );
	//Mex2Pointer p(pp);
	int nOffset = 0;
	//int nBoneCount = *p.i++;
	int nNumBone = 0;
	packet_namespace::w_fread( &nNumBone, sizeof(int), 1, fp );
	nOffset += sizeof(int);
	//nRootBoneCount = *p.i++;
	int nNumRootBone = 0;
	packet_namespace::w_fread( &nNumRootBone, sizeof(int), 1, fp );
	nOffset += sizeof(int);
	//pnRootBoneIds = p.i;
	//p.i += nRootBoneCount;
	packet_namespace::w_fseek( fp, sizeof(int)*nNumRootBone, SEEK_CUR );
	nOffset += sizeof(int)*nNumRootBone;

	// 为骨骼动画分配空间
	int nNumTotalFrame = action->nNumFrame*nNumBone;
	action->pbyMatrixBuffer = MeDefaultNew BYTE[sizeof(MeMatrix)*nNumTotalFrame];
	action->pbyKeyFrameBuffer = MeDefaultNew BYTE[sizeof(Mex2ActionKeyframe)*nNumTotalFrame];
	action->pbVisiBuffer = MeDefaultNew BOOL[nNumTotalFrame];
	BOOL bHasVisiTrack = FALSE;
	BOOL bHasKeyframe = FALSE;

	//ZeroMemory( action->pbVisiBuffer, )
	for( int i = 0; i < nNumTotalFrame; i++ )
	{
		action->pbVisiBuffer[i] = TRUE;
	}
	//MeMatrix* pmatBuffer = MeNew MeMatrix[action.nNumFrame];

	// 到达bone了
	//while( p.c < inP.c+nSize )
	
	int nBone = 0;

	while( nOffset <= m_dwSkeletonChunkSize )
	{
		DWORD dwName = 0;
		int size = 0;
		packet_namespace::w_fread( &dwName, sizeof(DWORD), 1, fp );
		nOffset += sizeof(DWORD);
		packet_namespace::w_fread( &size, sizeof(int), 1, fp );
		nOffset += sizeof(int);
		switch( MEX_TAG(dwName) )
		{
		case 'bone':
			{
				int nByte = 0;
				//Mex2Pointer p(inP.p);

				//pszName = p.c;
				//p.c += MEX2_MAX_NAME;
				char szName[MEX2_MAX_NAME] = "";

				//fseek( fp, MEX2_MAX_NAME, SEEK_CUR );
				packet_namespace::w_fread( szName, MEX2_MAX_NAME, 1, fp );
				nByte += MEX2_MAX_NAME;
				
				//nParentId = *p.i++;
				packet_namespace::w_fseek( fp, sizeof(int), SEEK_CUR );
				nByte += sizeof(int);
				//nChildCount = *p.i++;
				int nNumChild = 0;
				//fseek( fp, sizeof(int), SEEK_CUR );
				packet_namespace::w_fread( &nNumChild, sizeof(int), 1, fp );
				nByte += sizeof(int);
				//pnChildIds = p.i;
				//p.i += nChildCount;
				packet_namespace::w_fseek( fp, sizeof(int)*nNumChild, SEEK_CUR );
				nByte += sizeof(int)*nNumChild;
				

				int nNumFrame = 0;
				//while( p.c < inP.c+nSize )
				while( nByte < size )
				{
					DWORD dwChunkName = 0;
					int nChunkSize = 0;
					packet_namespace::w_fread( &dwChunkName, sizeof(DWORD), 1, fp );
					nByte += sizeof(DWORD);
					packet_namespace::w_fread( &nChunkSize, sizeof(int), 1, fp );
					nByte += sizeof(int);
					switch( MEX_TAG( dwChunkName ) )
					{
					case 'trck':
						{
							//int nNumFrame = 0;
							//nFrameCount = *p.i++;
							packet_namespace::w_fread( &nNumFrame, sizeof(int), 1, fp );
							
							//pMatrices = p.matrix;
							//p.matrix += nFrameCount;
							packet_namespace::w_fseek( fp, sizeof(MeMatrix)*action->nStartFrame, SEEK_CUR );
							MeMatrix* pmatBuffer = (MeMatrix*)action->pbyMatrixBuffer;
							packet_namespace::w_fread( &pmatBuffer[nBone*action->nNumFrame], 
								sizeof(MeMatrix), action->nNumFrame, fp );
							packet_namespace::w_fseek( fp, sizeof(MeMatrix)*(nNumFrame-action->nEndFrame-1), SEEK_CUR );




							//p.c += size; 
							//D3DXMatrixInverse( (D3DXMATRIX*)&matFrame0Inv, NULL, (D3DXMATRIX*)&pMatrices[0] );
						}
						break;
					case 'trk2':
						{
							Mex2ActionKeyframe* pKeyFrame = 
								(Mex2ActionKeyframe*)action->pbyKeyFrameBuffer;
							//p.dw++;
							//int size = *p.i++;
							//int nNumFrame = 0;
							//nFrameCount = *p.i++;
							packet_namespace::w_fread( &nNumFrame, sizeof(int), 1, fp );
							//nFrameCount = *p.i++;
							
							//pTrans = p.v3;
							// 读入偏移
							packet_namespace::w_fseek( fp, sizeof(Vector)*action->nStartFrame, SEEK_CUR );

							Vector* pTempTrans = MeNew Vector[action->nNumFrame];
							packet_namespace::w_fread( pTempTrans, sizeof(Vector)*action->nNumFrame, 1, fp );
							for( int nFrame = 0; nFrame < action->nNumFrame; nFrame++ )
							{
								pKeyFrame[nBone*action->nNumFrame+nFrame].vTrans = pTempTrans[nFrame];;
								//fread( &pKeyFrame[nBone*action->nNumFrame+nFrame].vTrans, sizeof(Vector), 1, fp );
							}
							delete[] pTempTrans;
							packet_namespace::w_fseek( fp, sizeof(Vector)*(nNumFrame-action->nEndFrame-1), SEEK_CUR );

							// 读入旋转

							packet_namespace::w_fseek( fp, sizeof(Quaternion)*action->nStartFrame, SEEK_CUR );
							Quaternion* pTempRot = MeNew Quaternion[action->nNumFrame];
							packet_namespace::w_fread( pTempRot, sizeof(Quaternion)*action->nNumFrame, 1, fp );
							for( int nFrame = 0; nFrame < action->nNumFrame; nFrame++ )
							{
								//fread( &pKeyFrame[nBone*action->nNumFrame+nFrame].qRot, sizeof(Quaternion), 1, fp );
								pKeyFrame[nBone*action->nNumFrame+nFrame].qRot = pTempRot[nFrame];
							}
							delete[] pTempRot;
							packet_namespace::w_fseek( fp, sizeof(Quaternion)*(nNumFrame-action->nEndFrame-1), SEEK_CUR );
							bHasKeyframe = TRUE;
						}
						break;
					case 'vis2':
						{
							//int nNumFrame = 0;
							//fread( &nNumFrame, sizeof(int), 1, fp );
							
							packet_namespace::w_fseek( fp, sizeof(int)*action->nStartFrame, SEEK_CUR );
							packet_namespace::w_fread( &action->pbVisiBuffer[nBone*action->nNumFrame], sizeof(int), action->nNumFrame, fp );
							packet_namespace::w_fseek( fp, sizeof(int)*(nNumFrame-action->nEndFrame-1), SEEK_CUR );
							bHasVisiTrack = TRUE;
							break;
						}

					default:
						{
							packet_namespace::w_fseek( fp, nChunkSize, SEEK_CUR );
							break;
						}
					}
					nByte += nChunkSize;

				}
				nBone++;
			}
			break;
		default:
			{
				packet_namespace::w_fseek( fp, size, SEEK_CUR );
				break;
			}
		}
		nOffset += size;
	}
	packet_namespace::w_fclose( fp );
	action->Loaded( TRUE );
	if( bHasKeyframe )
	{
		if( action->pbyMatrixBuffer )
		{
			delete[] action->pbyMatrixBuffer;
			action->pbyMatrixBuffer = NULL;
		}
	}
	if( !bHasVisiTrack )
	{
		if( action->pbVisiBuffer )
		{
			delete[] action->pbVisiBuffer;
			action->pbVisiBuffer = NULL;
		}
	}
	return TRUE;
	unguard;
}

BOOL Mex2::ReallocAnimationFrameCount( int nNewFrameCount )
{
	if( !m_skeleton )
		return FALSE;

	Mex2Skeleton* pSkeleton = (Mex2Skeleton*)m_skeleton;
	// 判断版本，108版本后使用关键帧动画，非逐帧动画
	if( GetVersion() >= 108 )
	{
		m_nReallocBoneFrameCount = nNewFrameCount;
		for(UINT nBone=0; nBone<pSkeleton->GetBoneCount(); ++nBone)
		{
			Mex2Bone* pBone = (Mex2Bone*)pSkeleton->GetBone( nBone );
			if( pBone->GetTrack() )
				pBone->GetTrack()->GetKeyFrames().reserve(m_nReallocBoneFrameCount);
			else if( pBone->m_bFullFrame )
			{
				// 重新分配内存，把原先数据拷贝过去，pBone->nFrameCount等合并动画后调整
				Vector* pTrans = MeNew Vector[nNewFrameCount];
				memcpy(pTrans, pBone->pTrans, sizeof(Vector)*pBone->nFrameCount);
				MEX2_SAFE_DELETE_ARRAY(pBone->pTrans);
				pBone->pTrans = pTrans;

				Quaternion* pQuats = MeNew Quaternion[nNewFrameCount];
				memcpy(pQuats, pBone->pQuats, sizeof(Quaternion)*pBone->nFrameCount);
				MEX2_SAFE_DELETE_ARRAY(pBone->pQuats);
				pBone->pQuats = pQuats;
			}
		}
	}
	else
	{
		for(UINT nBone=0; nBone<pSkeleton->GetBoneCount(); nBone++)
		{
			Mex2Bone* pBone = (Mex2Bone*)pSkeleton->GetBone( nBone );

			// 重新分配内存，把原先数据拷贝过去，pBone->nFrameCount等合并动画后调整
			Vector* pTrans = MeNew Vector[nNewFrameCount];
			memcpy(pTrans, pBone->pTrans, sizeof(Vector)*pBone->nFrameCount);
			MEX2_SAFE_DELETE_ARRAY(pBone->pTrans);
			pBone->pTrans = pTrans;

			Quaternion* pQuats = MeNew Quaternion[nNewFrameCount];
			memcpy(pQuats, pBone->pQuats, sizeof(Quaternion)*pBone->nFrameCount);
			MEX2_SAFE_DELETE_ARRAY(pBone->pQuats);
			pBone->pQuats = pQuats;
		}
		m_nReallocBoneFrameCount = nNewFrameCount;
	}

	return TRUE;
}

BOOL Mex2::CombineAnimationFromModel( IMex* pMex, int& nFrameOffset )
{
	if( !pMex || !pMex->GetSkeleton() )
		return FALSE;

	Mex2Skeleton* pSrcSkeleton = (Mex2Skeleton*)pMex->GetSkeleton();
	Mex2Skeleton* pDstSkeleton = (Mex2Skeleton*)m_skeleton;

	if( !pDstSkeleton->IsSameFormat(pSrcSkeleton) )
		return FALSE;

	if( GetVersion() < 108 )
	{
		Mex2Bone* pDstBone = (Mex2Bone*)pDstSkeleton->GetBone( 0 );
		Mex2Bone* pSrcBone = (Mex2Bone*)pSrcSkeleton->GetBone( 0 );
		if( pDstBone->nFrameCount + pSrcBone->nFrameCount > m_nReallocBoneFrameCount )
			return FALSE;
		
		// 获取frame偏移量
		nFrameOffset = pDstBone->nFrameCount;

		for(UINT nBone=0; nBone<pDstSkeleton->GetBoneCount(); ++nBone)
		{
			pDstBone = (Mex2Bone*)pDstSkeleton->GetBone( nBone );
			pSrcBone = (Mex2Bone*)pSrcSkeleton->GetBone( nBone );

			// 把pMex里的动画数据合并到当前IMex里，pTrans和pQuats空间需要预先调ReallocAnimationFrameCount分配
			memcpy(&pDstBone->pTrans[pDstBone->nFrameCount], pSrcBone->pTrans, sizeof(Vector)*pSrcBone->nFrameCount);
			memcpy(&pDstBone->pQuats[pDstBone->nFrameCount], pSrcBone->pQuats, sizeof(Quaternion)*pSrcBone->nFrameCount);

			pDstBone->nFrameCount += pSrcBone->nFrameCount;
		}
	}
	else
	{
		if( GetVersion() != ((Mex2*)pMex)->GetVersion() )
		{
			MessageBox( NULL, "主角动画数据版本不一致!", "失败", MB_OK );
			return FALSE;
		}

		Mex2Bone* pDstBone = (Mex2Bone*)pDstSkeleton->GetBone( 0 );
		Mex2Bone* pSrcBone = NULL;

		// 获取frame偏移量
		nFrameOffset = pDstBone->GetFrameCount();

		// 合并关键帧数据
		for(UINT nBone=0; nBone<pDstSkeleton->GetBoneCount(); ++nBone)
		{
			pDstBone = (Mex2Bone*)pDstSkeleton->GetBone( nBone );
			pSrcBone = (Mex2Bone*)pSrcSkeleton->GetBone( nBone );

			if( !pDstBone->m_bFullFrame )	// 关键帧动画
			{
				if( !pSrcBone->GetTrack() || !pDstBone->GetTrack() )
				{
					char temp[256] = {0};
					sprintf_s(temp,sizeof(temp)-1,"合并动画GetTrack失败! Bone %s", pSrcBone->GetName());
					MessageBox( NULL, temp, "失败", MB_OK );
					return FALSE;
				}

				AnimationTrack* pSrcTrack = (AnimationTrack*)pSrcBone->GetTrack();
				AnimationTrack* pDstTrack = (AnimationTrack*)pDstBone->GetTrack();
				int nKeyFrameOffset = pDstTrack->GetKeyFrames().size();
				for(int i=0; i<pSrcTrack->GetKeyFrames().size(); ++i)
				{
					KeyFrame* pSrcKeyFrame = pSrcTrack->GetKeyFrames()[i];
					pSrcKeyFrame->nFrameId += nFrameOffset;
					pDstTrack->GetKeyFrames().push_back(pSrcKeyFrame);
				}
				pSrcTrack->GetKeyFrames().clear();

				pDstBone->nFrameCount += pSrcBone->GetFrameCount();

				// 合并关键帧映射表
				int nOldSize = pDstTrack->m_KeyFrameIndexMap.size()-1;
				pDstTrack->m_KeyFrameIndexMap.resize(nOldSize + pSrcTrack->m_KeyFrameIndexMap.size());
				for( int i=0; i<pSrcTrack->m_KeyFrameIndexMap.size(); ++i )
				{
					if( pSrcTrack->m_KeyFrameIndexMap[i] + nKeyFrameOffset > 65535 )
						assert(0);
					pDstTrack->m_KeyFrameIndexMap[nOldSize+i] = (unsigned short)(pSrcTrack->m_KeyFrameIndexMap[i] + nKeyFrameOffset);
				}
			}
			else	// 逐帧动画
			{
				if( !pSrcBone->m_bFullFrame || !pDstBone->pTrans || !pDstBone->pQuats || !pSrcBone->pTrans || !pSrcBone->pQuats )
				{
					char temp[256] = {0};
					sprintf_s(temp,sizeof(temp)-1,"合并逐帧动画失败! Bone %s", pSrcBone->GetName());
					MessageBox( NULL, temp, "失败", MB_OK );
					return FALSE;
				}
				// 把pMex里的动画数据合并到当前IMex里，pTrans和pQuats空间需要预先调ReallocAnimationFrameCount分配
				memcpy(&pDstBone->pTrans[pDstBone->nFrameCount], pSrcBone->pTrans, sizeof(Vector)*pSrcBone->nFrameCount);
				memcpy(&pDstBone->pQuats[pDstBone->nFrameCount], pSrcBone->pQuats, sizeof(Quaternion)*pSrcBone->nFrameCount);

				pDstBone->nFrameCount += pSrcBone->nFrameCount;
			}
		}

		// 合并关键帧排序表
		Mex2Skeleton::KeyFrameTimeList& kDstTimeList = pDstSkeleton->GetKeyFrameTimeList();
		Mex2Skeleton::KeyFrameTimeList& kSrcTimeList = pSrcSkeleton->GetKeyFrameTimeList();
		int nOldTimeSize = kDstTimeList.size();
		kDstTimeList.resize(nOldTimeSize + kSrcTimeList.size());
		for( int i=0; i<kSrcTimeList.size(); ++i )
		{
			kDstTimeList[nOldTimeSize+i] = kSrcTimeList[i] + nFrameOffset;
		}
	}

	// 合并attachment数据
	// 这里假设不同武器的attachment个数是一致的,不做判断
	assert( m_attachments && "没有左右手attachment" );
	for( int i = 0 ; i < pMex->GetAttachments()->GetNumAttachment(); ++ i )
	{
		m_attachments->PushBack( *(Mex2Attachment*)pMex->GetAttachments()->GetAttachment( i ) );
	}

	return TRUE;
}

void Mex2::BuildKeyFrameTimeList(void)
{
	if( !m_skeleton )
		return;

	if( GetVersion() < 108 )
		return;

	Mex2Skeleton* pSkeleton = (Mex2Skeleton*)m_skeleton;
	//pSkeleton->BuildKeyFrameTimeList();	// 这一步在MePlugin里完成
	if( pSkeleton->m_bSpecialModel )
		return;

	Mex2Bone* pBone = (Mex2Bone*)pSkeleton->GetBone( 0 );
	if( !pBone )
		return;
	int nEndFrame = pBone->GetFrameCount()-1;

	FrameIndex kFrameIndex = pSkeleton->GetTimeIndex(0.f, TRUE);
	int iStartIndex = kFrameIndex.nKeyIndex;

	float fInterval = 1000.0f/FRAMEPERSEC;

	kFrameIndex = pSkeleton->GetTimeIndex(nEndFrame*fInterval, TRUE, iStartIndex);
	int iEndIndex = kFrameIndex.nKeyIndex;

	// 每500帧分一子段
	Mex2Skeleton::KeyFrameSegmentList& kSegments = pSkeleton->GetKeyFrameSegments();
	int nSegments = nEndFrame / 500;
	if( nSegments == 0 )
	{
		kSegments.push_back(iStartIndex);
		kSegments.push_back(iEndIndex);
	}
	else
	{
		int offset = iStartIndex;
		kSegments.push_back(iStartIndex);
		for( int j=0; j<nSegments; ++j )
		{
			kFrameIndex = pSkeleton->GetTimeIndex(500 * (j+1)*fInterval, TRUE, offset);
			kSegments.push_back(kFrameIndex.nKeyIndex);
			offset = kFrameIndex.nKeyIndex;
		}
		kSegments.push_back(iEndIndex);
	}
}

void Mex2::InitializeDefaultSequece()
{
	if (m_pSequence == NULL)
	{
		m_pSequence = MeNew Mex2Sequence;
		strcpy( m_pSequence->szName, "none" );
		m_pSequence->nStartFrameId = 0;
		if( m_skeleton )
			assert( m_skeleton->GetBoneCount() > 0 && "mex2 load failed, skeleton bone count must > 0 " );
		else
			return;

		if( !m_skeleton->GetBone(0) )
			m_pSequence->nEndFrameId = 0;
		else
			m_pSequence->nEndFrameId = m_skeleton->GetBone(0)->GetFrameCount()-1;
		m_pSequence->nFps = 30;
		m_pSequence->bLoopping = TRUE;
	}
}

void Mex2::MemoryBlock::Destory()
{
	MEX2_SAFE_DELETE_ARRAY(m_pbyBuffer);
	m_nBufferSize = 0;
}

Mex2Bone::~Mex2Bone()
{
	MEX2_SAFE_DELETE_ARRAY(pnChildIds);
	MEX2_SAFE_DELETE_ARRAY(pMatrices);
	MEX2_SAFE_DELETE_ARRAY(pTrans);
	MEX2_SAFE_DELETE_ARRAY(pVisible);
	MEX2_SAFE_DELETE_ARRAY(pVisibleFloat);
	MEX2_SAFE_DELETE_ARRAY(pQuats);
	MEX2_SAFE_DELETE(m_pTrack);
}

Mex2BoneGroup::~Mex2BoneGroup()
{
	MEX2_SAFE_DELETE_ARRAY(pnBoneIds);
	MEX2_SAFE_DELETE_ARRAY(pfBondWeight);

}

Mex2Light::~Mex2Light()
{
	MEX2_SAFE_DELETE_ARRAY(m_param.m_pColorTrack);
}

Mex2BoneGroups::~Mex2BoneGroups()
{
	for (int i = 0; i < vectorBoneGroup.size(); ++i)
	{
		delete vectorBoneGroup[i];
	}
}

Mex2MtlAnim::~Mex2MtlAnim()
{
	MEX2_SAFE_DELETE_ARRAY(pKeys);

}

Mex2Materials::~Mex2Materials()
{
	for (int i = 0; i < vectorMtl.size(); ++i)
	{
		delete vectorMtl[i];
	}

}

Mex2MtlAnims::~Mex2MtlAnims()
{
	for (int i = 0; i < vectorColorTrack.size(); ++i)
	{
		delete vectorColorTrack[i];
	}

}

void Mex2Geometry::createBuffers( bool dynamic )
{
	for (int i = 0; i < vectorChunk.size(); ++i)
	{
		vectorChunk[i]->createBuffers();
	}
}

Mex2Geometry::~Mex2Geometry()
{

}
void Mex2::OnDeviceLost()
{
	if (m_geometry)
	{
		m_geometry->OnDeviceLost();
	}

}

void Mex2::OnDeviceReset()
{
	if (m_geometry)
	{
		m_geometry->restoreBuffers();
	}

}
//-------------关键帧动画-------------------------------------------
void Mex2Skeleton::BuildKeyFrameTimeList( void ) const
{
	// Clear old keyframe times
	m_KeyFrameTimes.clear();

	// Collect all keyframe times from each track
	for( int i = 0; i < vectorBone.size(); i++ )
	{
		Mex2Bone* bone = vectorBone[i];
		bone->CollectKeyFrameTimes(m_KeyFrameTimes);
	}

	// Build global index to local index map for each track
	for( int i = 0; i < vectorBone.size(); i++ )
	{
		Mex2Bone* bone = vectorBone[i];
		bone->BuildKeyFrameIndexMap(m_KeyFrameTimes);
	}
}

FrameIndex Mex2Skeleton::GetTimeIndex( float fTime, BOOL bFindAll /*= FALSE*/, int iBeginIndex/* = 0*/ ) const
{
	if( m_KeyFrameTimes.size() == 0 )
		return FrameIndex(fTime, 0);

	float fInterval = 1000.0f/FRAMEPERSEC;
	int frame = (int)(fTime/fInterval);

	// Wrap time
	int totalAnimationLength = m_KeyFrameTimes[m_KeyFrameTimes.size()-1];

	while (frame > totalAnimationLength && totalAnimationLength > 0)
	{
		frame -= totalAnimationLength;
	}

	if( frame == 0 )
		return FrameIndex(fTime, 0);

	int nOffsetA = 0;
	int nOffsetB = 0;
	BOOL bFind = FALSE;

	int iBegin = 0;
	int iEnd = m_KeyFrameTimes.size()-1;
	if( !bFindAll && m_KeyFrameSegments.size() )
	{
		int nSegment = frame / 500;
		if( nSegment < m_KeyFrameSegments.size() )
		{
			nOffsetA = m_KeyFrameSegments[nSegment];
			nOffsetB = m_KeyFrameSegments[nSegment+1];
			bFind = TRUE;
		}
	}
	if( bFind && nOffsetA >= 0 && nOffsetB > nOffsetA )
	{
		iBegin = nOffsetA;
		iEnd = nOffsetB;
	}
	else if( bFindAll )
	{
		iBegin = iBeginIndex;
	}
	int iIndex = iEnd;
	if( frame < m_KeyFrameTimes[iBegin] )
		iBegin = 0;

	for( int i=iBegin; i<=iEnd-1; ++i )
	{
		if( frame >= m_KeyFrameTimes[i] && frame < m_KeyFrameTimes[i+1] )
		{
			iIndex = i+1;
			break;
		}
	}

	return FrameIndex(fTime, iIndex);
}

void Mex2Bone::BuildInterpolationSplines( IMexSkeleton* pSkeleton ) const
{
	if( m_pTrack )
		m_pTrack->BuildInterpolationSplines(pSkeleton);
}

void Mex2Bone::CollectKeyFrameTimes( std::vector<int>& keyFrameTimes )
{
	if( m_pTrack )
		m_pTrack->CollectKeyFrameTimes(keyFrameTimes);
}

void Mex2Bone::BuildKeyFrameIndexMap( const std::vector<int>& keyFrameTimes )
{
	if( m_pTrack )
		m_pTrack->BuildKeyFrameIndexMap(keyFrameTimes);
}

float Mex2Bone::GetInterpolatedKeyFrame( const FrameIndex& frameIndex, KeyFrame& kf, KeyFrame& extrakf )
{
	if( m_pTrack )
		return m_pTrack->GetInterpolatedKeyFrame(frameIndex, kf, extrakf);
	return 0.f;
}

void Mex2Bone::GetParentModelMatAtKeyFrame(float fKeyTime, const FrameIndex& frameIndex, MeMatrix& mat)
{
	if( GetParentId() < 0 || !pSkeleton )
		return;

	Mex2Bone* pParentBone = (Mex2Bone*)pSkeleton->GetBone(GetParentId());
	if( pParentBone )
	{
		if( !pParentBone->m_bFullFrame )
		{
			if( pParentBone->GetTrack() )
			{
				KeyFrame keyframe, kKeyFrameEx;
				float t = pParentBone->GetInterpolatedKeyFrame(frameIndex, keyframe, kKeyFrameEx);
				// 除lh.和rh.这两个骨骼父子关系会变化，其他骨骼不会变，暂不考虑t > 0.001的情况
				if( t > 0.001f )
					assert(0);

				keyframe.kQuat.normalise();
				MakeMatrix( keyframe.kTrans, keyframe.kQuat, mat );

				MeMatrix initMat;
				MakeMatrix(pParentBone->GetTrack()->m_kInitTrans, pParentBone->GetTrack()->m_kInitQuat, initMat);
				D3DXMatrixMultiply( (D3DXMATRIX*)&mat, (D3DXMATRIX*)&mat, (D3DXMATRIX*)&initMat );

				if( pParentBone->GetParentId() >= 0 )
				{
					MeMatrix parentMat;
					pParentBone->GetParentModelMatAtKeyFrame(fKeyTime, frameIndex, parentMat);
					D3DXMatrixMultiply( 
						(D3DXMATRIX*)&mat, 
						(D3DXMATRIX*)&mat,
						(D3DXMATRIX*)&parentMat
						);
				}
			}
			else
				assert(0);
		}
		else
		{
			//float fInterval = 1000.0f/FRAMEPERSEC;
			//fKeyTime = frameIndex.nFrame * fInterval;
			Vector v;
			Quaternion q;
			pParentBone->GetTranslationAndRotation( fKeyTime, FRAMEPERSEC, v, q );
			MakeMatrix( v, q, mat );
		}
	}
}

AnimationTrack::~AnimationTrack()
{
	RemoveAllKeyFrames();
	m_KeyFrameIndexMap.clear();
}

void AnimationTrack::RemoveAllKeyFrames()
{
	for(int i=0; i<m_vecKeyFrames.size(); ++i)
	{
		KeyFrame* pKeyFrame = m_vecKeyFrames[i];
		MEX2_SAFE_DELETE(pKeyFrame);
	}
	m_vecKeyFrames.clear();
}

void AnimationTrack::BuildInterpolationSplines( IMexSkeleton* pSkeleton )
{
	//// Don't calc automatically, do it on request at the end
	//m_Splines.positionSpline.setAutoCalculate(false);
	//m_Splines.rotationSpline.setAutoCalculate(false);

	//m_Splines.positionSpline.clear();
	//m_Splines.rotationSpline.clear();

	//KeyFrameList::const_iterator i, iend;
	//iend = m_vecKeyFrames.end(); // precall to avoid overhead
	//for (i = m_vecKeyFrames.begin(); i != iend; ++i)
	//{
	//	KeyFrame* kf = static_cast<KeyFrame*>(*i);
	//	m_Splines.positionSpline.addPoint(kf->kTrans);
	//	m_Splines.rotationSpline.addPoint(kf->kQuat);
	//}

	//m_Splines.positionSpline.recalcTangents();
	//m_Splines.rotationSpline.recalcTangents();

	FillDerivedVals(pSkeleton);
}

void AnimationTrack::CollectKeyFrameTimes( std::vector<int>& keyFrameTimes )
{
	for (KeyFrameList::const_iterator i = m_vecKeyFrames.begin(); i != m_vecKeyFrames.end(); ++i)
	{
		int nFrame = (*i)->nFrameId;

		std::vector<int>::iterator it =
			std::lower_bound(keyFrameTimes.begin(), keyFrameTimes.end(), nFrame);
		if (it == keyFrameTimes.end() || *it != nFrame)
		{
			keyFrameTimes.insert(it, nFrame);
		}
	}
}

void AnimationTrack::BuildKeyFrameIndexMap( const std::vector<int>& keyFrameTimes )
{
	// Pre-allocate memory
	m_KeyFrameIndexMap.clear();
	m_KeyFrameIndexMap.resize(keyFrameTimes.size() + 1);

	size_t i = 0, j = 0;
	while (j <= keyFrameTimes.size())
	{
		m_KeyFrameIndexMap[j] = static_cast<unsigned short>(i);
		while (i < m_vecKeyFrames.size() && m_vecKeyFrames[i]->nFrameId <= keyFrameTimes[j])
			++i;
		++j;
	}
}

float AnimationTrack::GetInterpolatedKeyFrame( const FrameIndex& frameIndex, KeyFrame& kf, KeyFrame& extrakf )
{
	// Keyframe pointers
	KeyFrame *k1, *k2, *k3, *k0;
	int firstKeyIndex;

	float t = GetKeyFramesAtTime(frameIndex, &k1, &k2, &k3, &k0, &firstKeyIndex);

	if (t < 0.001f)	// 正好k1，不用插值
	{
		kf = *k1;
	}
	else
	{
		if( k1->ucPosSpace != k2->ucPosSpace )
		{
			// k1和k2不插值，直接返回，换算成模型坐标后再插值
			kf = *k1;
			extrakf = *k2;
			return t;
		}
		else
		{
			KeyFrame result;
			k1->Interpolate(t, k2, &result);
			kf = result;
			kf.ucPosSpace = k1->ucPosSpace;
			kf.ucRotSpace = k1->ucRotSpace;
		}
	}
	return 0.f;
}

float AnimationTrack::GetKeyFramesAtTime( const FrameIndex& frameIndex, KeyFrame** keyFrame1, KeyFrame** keyFrame2,
										 KeyFrame** keyFrame3, KeyFrame** keyFrame0, int* firstKeyIndex /*= 0*/ ) const
{
	// f1 = frame of previous keyframe
	// f2 = frame of next keyframe
	int f1, f2;

	float fInterval = 1000.0f/FRAMEPERSEC;

	// Find first keyframe after or on current time
	KeyFrameList::const_iterator i;

	// Global keyframe index available, map to local keyframe index directly.
	int keyIndex = frameIndex.nKeyIndex;
	assert( keyIndex< m_KeyFrameIndexMap.size());
	if( keyIndex >= m_KeyFrameIndexMap.size() )
		keyIndex = m_KeyFrameIndexMap.size()-1;

	i = m_vecKeyFrames.begin() + m_KeyFrameIndexMap[keyIndex];

	if (i == m_vecKeyFrames.end())
	{
		*keyFrame3 = m_vecKeyFrames.front()+1;
	}
	else if( i+1 == m_vecKeyFrames.end() )
	{
		*keyFrame3 = m_vecKeyFrames.front();
	}
	else
		*keyFrame3 = *(i+1);

	if( i == m_vecKeyFrames.begin() || i-1 == m_vecKeyFrames.begin() )
	{
		*keyFrame0 = *i;
	}
	else
	{
		*keyFrame0 = *(i-2);
	}

	if (i == m_vecKeyFrames.end())
	{
		// There is no keyframe after this time, wrap back to first
		*keyFrame2 = m_vecKeyFrames.front();
		f2 = m_vecKeyFrames[m_vecKeyFrames.size()-1]->nFrameId + (*keyFrame2)->nFrameId;

		// Use last keyframe as previous keyframe
		--i;
	}
	else
	{
		*keyFrame2 = *i;
		f2 = (*keyFrame2)->nFrameId;

		// Find last keyframe before or on current time
		if (i != m_vecKeyFrames.begin() && frameIndex.fTime < (*i)->nFrameId*fInterval)
		{
			--i;
		}
	}

	// Fill index of the first key
	if (firstKeyIndex)
	{
		*firstKeyIndex = static_cast<int>(std::distance(m_vecKeyFrames.begin(), i));
	}

	*keyFrame1 = *i;

	f1 = (*keyFrame1)->nFrameId;

	if (f1 == f2)
	{
		// Same KeyFrame (only one)
		return 0.f;
	}
	else
	{
		return (frameIndex.fTime - f1*fInterval) / ((f2 - f1)*fInterval);
	}
}
//----------------------------------------------------------------------------
//TCB关键帧
void AnimationTrack::FillDerivedVals(IMexSkeleton* pSkeleton)
{
	if( m_vecKeyFrames.size() <= 0 )
		return;

	if( m_eKeyType != eKT_Tcb )
		return;

	unsigned int uiNumKeys = m_vecKeyFrames.size();
	unsigned int uiNumKeysM1 = m_vecKeyFrames.size() - 1;
	unsigned int i;

	std::vector<Vector>	PosDSs;
	PosDSs.resize(uiNumKeys);
	// Position
	if ( uiNumKeys >= 2 )
	{
		// Extend the previous point a distance equivalent to the difference
		// between the first and second points on the line between the two.
		((TcbKeyFrame*)m_vecKeyFrames[0])->CalculatePosDVals(
			2 * m_vecKeyFrames[0]->kTrans - m_vecKeyFrames[1]->kTrans,
			m_vecKeyFrames[1]->kTrans,
			1, 1, pSkeleton, PosDSs, 0);

		for (i = 1; i < uiNumKeysM1; i++)
		{
			KeyFrame* pkTCBM = m_vecKeyFrames[i-1];
			KeyFrame* pkTCBZ = m_vecKeyFrames[i];
			KeyFrame* pkTCBP = m_vecKeyFrames[i+1];

			((TcbKeyFrame*)pkTCBZ)->CalculatePosDVals(
				pkTCBM->kTrans,
				pkTCBP->kTrans,
				(pkTCBZ->nFrameId - pkTCBM->nFrameId) / FRAMEPERSEC,
				(pkTCBP->nFrameId - pkTCBZ->nFrameId) / FRAMEPERSEC,
				pSkeleton, PosDSs, i);
		}

		// Extend the next point a distance equivalent to the
		// difference between the last and second to last points 
		// on the line between the two.
		unsigned int uiNumKeysM2 = uiNumKeys - 2;
		((TcbKeyFrame*)m_vecKeyFrames[uiNumKeysM1])->CalculatePosDVals(
			m_vecKeyFrames[uiNumKeysM2]->kTrans,
			2.0f * m_vecKeyFrames[uiNumKeysM1]->kTrans - m_vecKeyFrames[uiNumKeysM2]->kTrans,
			1, 1, pSkeleton, PosDSs, uiNumKeysM1);
	}

	for (i = 0; i < uiNumKeysM1; i++)
	{
		TcbKeyFrame* pTCB0 = (TcbKeyFrame*)m_vecKeyFrames[i];
		TcbKeyFrame* pTCB1 = (TcbKeyFrame*)m_vecKeyFrames[i+1];

		// A = 3(P1 - P0) - (D1 + 2D0)
		pTCB0->m_PosA = 3.0f*(pTCB1->kTrans - pTCB0->kTrans)
			- (/*pTCB1->m_PosDS*/PosDSs[i+1] + 2.0f*pTCB0->m_PosDD);

		// B = (D0 + D1) - 2(P1 - P0)
		pTCB0->m_PosB = pTCB0->m_PosDD + /*pTCB1->m_PosDS*/PosDSs[i+1]
			- 2.0f*(pTCB1->kTrans - pTCB0->kTrans);
	}

	// Rotation
	if ( uiNumKeys >= 2 )
	{
		// consecutive quaternions are set to have an acute angle

		// Eliminate any non-acute angles between successive quaternions.  This
		// is done to prevent potential discontinuities that are the result of
		// invalid intermediate value quaternions.
		unsigned int i;
		for (i = 0; i < uiNumKeys-1; i++)
		{
			KeyFrame* pkKey0 = m_vecKeyFrames[i];
			KeyFrame* pkKey1 = m_vecKeyFrames[i+1];
			if ( pkKey0->kQuat.dot(pkKey1->kQuat) < 0.0f )
				pkKey1->kQuat = -pkKey1->kQuat;
		}

		// Clamp identity quaternions so that |w| <= 1 (avoids problems with
		// call to acos in SlerpExtraSpins).
		for (i = 0; i < uiNumKeys; i++)
		{
			KeyFrame* pkKey = m_vecKeyFrames[i];
			float fW = pkKey->kQuat.w;
			if ( fW < -1.0f )
				pkKey->kQuat.w = -1.0f;
			else if ( fW > 1.0f )
				pkKey->kQuat.w = 1.0f;
		}

		// calculate the derived A & B quaternion values
		((TcbKeyFrame*)m_vecKeyFrames[0])->CalculateRotDVals(m_vecKeyFrames[0], m_vecKeyFrames[1], pSkeleton);

		unsigned int uiNumKeysM1 = uiNumKeys-1;
		for (unsigned int uiI = 1; uiI < uiNumKeysM1; uiI++)
		{
			((TcbKeyFrame*)m_vecKeyFrames[uiI])->CalculateRotDVals(m_vecKeyFrames[uiI-1], m_vecKeyFrames[uiI+1], pSkeleton);
		}

		((TcbKeyFrame*)m_vecKeyFrames[uiNumKeysM1])->CalculateRotDVals(m_vecKeyFrames[uiNumKeys-2], m_vecKeyFrames[uiNumKeysM1], pSkeleton);
	}
}

void TcbKeyFrame::CalculatePosDVals(const Vector& ptSub1, const Vector& ptPlus1, float fPreLen, float fNextLen, IMexSkeleton* pSkeleton,
									std::vector<Vector>& PosDSs, int index)
{
	if( !pSkeleton )
		return;
	Mex2Skeleton* pMex2Skeleton = (Mex2Skeleton*)pSkeleton;

	Vector diff1 = kTrans - ptSub1;
	Vector diff2 = ptPlus1 - kTrans;

	float opc = 1.0f + pMex2Skeleton->m_vTcbList[m_iTcbIndex].fContinuity;
	float omc = 1.0f - pMex2Skeleton->m_vTcbList[m_iTcbIndex].fContinuity;
	float opb = 1.0f + pMex2Skeleton->m_vTcbList[m_iTcbIndex].fBias;
	float omb = 1.0f - pMex2Skeleton->m_vTcbList[m_iTcbIndex].fBias;
	float homt = 0.5f*(1.0f-pMex2Skeleton->m_vTcbList[m_iTcbIndex].fTension);
	float homtopc = homt*opc;
	float homtomc = homt*omc;

	/*m_PosDS*/PosDSs[index] = (homtomc*opb)*diff1 + (homtopc*omb)*diff2;
	m_PosDD = (homtopc*opb)*diff1 + (homtomc*omb)*diff2;

	// These adjustments compensate for varying numbers of "inbetweens" 
	// that will be calculated between keys.  They are approximate. 
	// See Kochanek, D. H. U., Bartels, R. "Interpolating Splines with 
	// Local Tension, Continuity, and Bias Control", SIGGRAPH 1984.
	// The code here is an interpretation for time-based 
	// animations based on their discussion of adjustments for 
	// parameter step size.  The length of the segment between keys
	// is used to calculate the adjustment.

	float fInv = 2.0f/(fPreLen + fNextLen);
	/*m_PosDS*/PosDSs[index] *= fPreLen*fInv;
	m_PosDD *= fNextLen*fInv;
}

void TcbKeyFrame::CalculateRotDVals(const KeyFrame* pPrev, const KeyFrame* pNext, IMexSkeleton* pSkeleton)
{
	if( !pSkeleton )
		return;
	Mex2Skeleton* pMex2Skeleton = (Mex2Skeleton*)pSkeleton;

	// Build logs and angles between prev, this, and next quats
	Quaternion logPrev =
		(Quaternion::UnitInverse(pPrev->kQuat)*kQuat).Log();
	Quaternion logNext =
		(Quaternion::UnitInverse(kQuat)*pNext->kQuat).Log();

	// Build multipliers 
	float fInv = 1.f/(pNext->nFrameId - pPrev->nFrameId);
	float mt = 1.0f - pMex2Skeleton->m_vTcbList[m_iTcbIndex].fTension;
	float mc = 1.0f - pMex2Skeleton->m_vTcbList[m_iTcbIndex].fContinuity;
	float pc = 1.0f + pMex2Skeleton->m_vTcbList[m_iTcbIndex].fContinuity;
	float mb = 1.0f - pMex2Skeleton->m_vTcbList[m_iTcbIndex].fBias;
	float pb = 1.0f + pMex2Skeleton->m_vTcbList[m_iTcbIndex].fBias;
	float adjVal = (nFrameId - pPrev->nFrameId) *fInv;
	float d0 = adjVal * mt * pc * pb;
	float d1 = adjVal * mt * mc * mb;

	// Build outgoing tangent
	Quaternion Tout = logNext * d1 + logPrev * d0;

	// Set A
	m_RotA = kQuat * ((Tout - logNext)*0.5f).Exp();

	// Adjust multipliers
	adjVal = (pNext->nFrameId - nFrameId)*fInv;
	d0 = adjVal * mt * mc * pb;
	d1 = adjVal * mt * pc * mb;

	// Build incoming tangent 
	Quaternion Tin = logNext * d1 + logPrev * d0;

	// Set B
	m_RotB = kQuat * ((logPrev - Tin)*0.5f).Exp();
}

void KeyFrame::Interpolate( float t, const KeyFrame* pKey1, KeyFrame* pResult )
{
	if( !pKey1 || !pResult )
		return;

	// Interpolate by t
	// Spline interpolation
	int iTransBlendType = 0;
	int iQuatBlendType = 2;

	//// Rotation, take mUseShortestRotationPath into account
	switch( iQuatBlendType )
	{
		//case 0:
		//	kf.kQuat = m_Splines.rotationSpline.interpolate(firstKeyIndex, t, true);
		//	break;
	case 1:
		pResult->kQuat = Quaternion::Slerp(t, kQuat, pKey1->kQuat, false);
		break;
	case 3:
		pResult->kQuat = Quaternion::SlerpDirect(t, kQuat, pKey1->kQuat);
		break;
	case 4:
		pResult->kQuat = Quaternion::SlerpMatrix(t, kQuat, pKey1->kQuat);
		break;
	case 5:
		pResult->kQuat = Quaternion::SlerpRenormal(t, kQuat, pKey1->kQuat);
		break;
	case 6:
		pResult->kQuat = Quaternion::SlerpSimpleRenormal(t, kQuat, pKey1->kQuat);
		break;
	case 7:
		D3DXQuaternionSlerp((D3DXQUATERNION*)&pResult->kQuat, (D3DXQUATERNION*)&kQuat, (D3DXQUATERNION*)&pKey1->kQuat, t);
		break;
	//case 8:
	//	{
	//		D3DXQUATERNION A, B, C;
	//		D3DXQuaternionSquadSetup(&A, &B, &C,
	//			(D3DXQUATERNION*)&k0->kQuat, (D3DXQUATERNION*)&k1->kQuat,
	//			(D3DXQUATERNION*)&k2->kQuat, (D3DXQUATERNION*)&k3->kQuat);
	//		D3DXQuaternionSquad((D3DXQUATERNION*)&pResult->kQuat, (D3DXQUATERNION*)&k1->kQuat, &A, &B, &C, t);
	//	}
	//	break;
	case 2:
	default:
		pResult->kQuat = kQuat;
		pResult->kQuat.blend( t, pKey1->kQuat );
		break;
	}

	switch( iTransBlendType )
	{
		//case 1:	//Hermite
		//	kf.kTrans = m_Splines.positionSpline.interpolate(firstKeyIndex, t);
		//	break;
	//case 2:
	//	{
	//		float fPoints[9] = {k1->kTrans.x, k1->kTrans.y, k1->kTrans.z,
	//			k2->kTrans.x, k2->kTrans.y, k2->kTrans.z,
	//			k3->kTrans.x, k3->kTrans.y, k3->kTrans.z};
	//		float fResult[3] = {0.0, 0.0, 0.0};
	//		CubicSpline(fPoints, t, fResult);
	//		pResult->kTrans.x = fResult[0];		
	//		pResult->kTrans.y = fResult[1];		
	//		pResult->kTrans.z = fResult[2];		
	//	}
	//	break;
	//case 3:
	//	{
	//		Vector vOut;
	//		D3DXVec3CatmullRom((D3DXVECTOR3*)&vOut,
	//			(D3DXVECTOR3*)&k0->kTrans, 
	//			(D3DXVECTOR3*)&k1->kTrans, 
	//			(D3DXVECTOR3*)&k2->kTrans, 
	//			(D3DXVECTOR3*)&k3->kTrans,
	//			t
	//			);
	//		pResult->kTrans = vOut;
	//	}
	//	break;
	case 0:	// Linear
	default:
		pResult->kTrans = kTrans + ((pKey1->kTrans - kTrans) * t);
		break;
	}
}

void TcbKeyFrame::Interpolate( float t, const KeyFrame* pKey1, KeyFrame* pResult )
{
	if( !pKey1 || !pResult )
		return;

	// interpolate position
	TcbKeyFrame* pTcbKey1 = (TcbKeyFrame*)pKey1;
	pResult->kTrans = kTrans + (m_PosDD + (m_PosA + m_PosB*t)*t)*t;
	pResult->kQuat = Quaternion::Squad(t, kQuat, m_RotA, pTcbKey1->m_RotB, pTcbKey1->kQuat );
}
