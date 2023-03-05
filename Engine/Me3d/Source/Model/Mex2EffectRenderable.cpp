
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

//#include "Launcher/DataLauncher.h"
#include "Me3d/Shader.h"
#include "Me3d/ShaderManager.h"

#include "Me3d/Engine/MeRenderManager.h"


BOOL Mex2RibbonEmitter::Read( Mex2Pointer inP, int nSize )
{
	guardfunc;
////	////CSALocker locker(this);
	Mex2Pointer p(inP.p);

	pSetting = (Mex2RibbonEmitterSetting*)p.c;
	p.c += sizeof( Mex2RibbonEmitterSetting );

	/*
	 * 2012.7.2 wangshuai
	 * 兼容老的版本
	 */
	if (pSetting->dwBlendMode == 0)
		pSetting->dwBlendMode = eTwoSided|eAlphaBlend|eZWriteDisable|eDstBlendOne;

	// 说明有补充数据了
	if( p.c < inP.c+nSize )
	{
		CDataChunkLoader l(p.byte,nSize-sizeof(Mex2RibbonEmitterSetting));
		while( !l.IsEndOfMemory() )
		{
			if( l.IsChunk( 'bprt' ) )
			{
				l.StartChunk( 'bprt' );
				{
					CDataChunkLoader s(l);
					s.ReadToBuffer( (BYTE*)m_szBindPartName, MEX2_MAX_NAME );
				}
				l.EndChunk( 'bprt' );
			}
			else
				l.SkipChunk();
		}
	}
	/*pszParentBoneName = p.c;
	p.c += MEX2_MAX_NAME;
	nParentBoneId = *p.i++;
	vLines[0] = *p.v3++;
	vLines[1] = *p.v3++;*/
	// 一个发射器中最多有dwEdgePerSec*dwEdgeLifeSec根
	if( pSetting->dwEdgePerSec < 4 )
		pSetting->dwEdgePerSec = 4;
	nMaxEdgeCount = pSetting->dwEdgePerSec*pSetting->dwEdgeLifeSec;
	if( nMaxEdgeCount > MEX2_MAX_RIBBON_EDGE )
		nMaxEdgeCount = MEX2_MAX_RIBBON_EDGE;


	//nMaxEdgeCount = MEX2_MAX_RIBBON_EDGE/2;
	return TRUE;
	unguard;
}

IMexRibbonEmitter* Mex2RibbonEmitter::Clone()
{
	guardfunc;
/////	//CSALocker locker(this);
	Mex2RibbonEmitter* pEmitter = MeNew Mex2RibbonEmitter;
	pEmitter->pSetting = pSetting;
	strcpy( pEmitter->m_szBindPartName, m_szBindPartName  );
	pEmitter->nEdgeCount = nEdgeCount;
	pEmitter->nMaxEdgeCount = nMaxEdgeCount;
	pEmitter->pParentMex = pParentMex;
	pEmitter->pParentBone = pParentBone;
	return pEmitter;
	unguard;
}
BOOL Mex2RibbonEmitter::Bind( Mex2* pMex )
{
	guardfunc;
/////	//CSALocker locker(this);
	int nBoneId = pSetting->nParentBoneId;
	
	pParentMex = pMex;
	pParentBone = pMex->GetSkeleton()->GetBone(nBoneId);// vectorBone[nBoneId];
	nEdgeCount = 0;
	return TRUE;
	unguard;
}
BOOL Mex2RibbonEmitter::IsEdgeDead( Mex2RibbonEdge* pEdge, int nTime )
{
	guardfunc;
/////	//CSALocker locker(this);
	//if( !pEdge->bStart )
	//	return FALSE;
	if( pEdge->dwBornTime == 0 )
		return TRUE;

	return pEdge->dwBornTime+pEdge->dwLife < nTime;
	unguard;
}
void Mex2RibbonEmitter::GetPoint( float* pfPoint )
{
	Vector* pvPoint = (Vector*)pfPoint;
	pvPoint[0] = pSetting->vLines[0];
	pvPoint[1] = pSetting->vLines[1];
}
void Mex2RibbonEmitter::GenEdge( Mex2RibbonEdge* pEdge, 
									 int nTime,
									 MeMatrix* pParentTransform )
{
	guardfunc;
////	//CSALocker locker(this);
	D3DXVec3TransformCoord( (D3DXVECTOR3*)&pEdge->vPoint[0], 
		(D3DXVECTOR3*)&pSetting->vLines[0],	
		(D3DXMATRIX*)pParentTransform );

	D3DXVec3TransformCoord( (D3DXVECTOR3*)&pEdge->vPoint[1], 
		(D3DXVECTOR3*)&pSetting->vLines[1],	
		(D3DXMATRIX*)pParentTransform );
	D3DXVECTOR3 vSum(0,0,0);
	D3DXVec3Add(&vSum,(D3DXVECTOR3*)&pEdge->vPoint[0],(D3DXVECTOR3*)&pEdge->vPoint[1]);
	D3DXVec3Scale(&m_vCenter,&vSum,0.5);
	//pEdge->dwLife = 550;
	//pEdge->dwBornTime = nTime;
	unguard;
}


bool Mex2RibbonEmitter::DoRender( SEmitterVertex* vertex )
{
	if( nEdgeCount < 2 )
		return false;

	MeRenderObject* pkObject = ( MeRenderObject* )m_spRenderObject;			
	MeParticleRibbonRenderObject* pkPObject = dynamic_cast< MeParticleRibbonRenderObject* >( pkObject );
	if( !pkPObject )
		return false;

	float fAlpha = pkPObject->GetAlpha();

	float k = 1.0f/(nEdgeCount-1);
	DWORD color = 0xffffffff;
// 	int const MAX_POINT = 1024;
// 
// 	if( nEdgeCount > MAX_POINT/4 )
// 	{
// 		return;
// 	}

	//static SK_VERTEX v[MAX_POINT*2];
// 	static SEmitterVertex vertex[MAX_POINT*2];

	DWORD dwAlpha = (color&0xff000000)>>24;
	dwAlpha = (DWORD)(dwAlpha*fAlpha);
	if( dwAlpha > 255 )
		dwAlpha = 255;
	DWORD dwRibbonColor = dwAlpha<<24|(color&0x00ffffff);
	// 可能有溢出，需要这个判断 [12/21/2010 zhangjiayi]
	if( nEdgeCount >= MEX2_MAX_RIBBON_EDGE )
		nEdgeCount = MEX2_MAX_RIBBON_EDGE - 1;
	for(int i = 0; i < nEdgeCount-1; i++ )
	{
		vertex[i*4].p = *(D3DXVECTOR3*)&edges[i].vPoint[0];
		vertex[i*4].color = dwRibbonColor;
		vertex[i*4].u = k*i;
		vertex[i*4].v = 1.0f;

		vertex[i*4+1].p = *(D3DXVECTOR3*)&edges[i].vPoint[1];
		vertex[i*4+1].color = dwRibbonColor;
		vertex[i*4+1].u = k*i;
		vertex[i*4+1].v = 0;

		vertex[i*4+2].p = *(D3DXVECTOR3*)&edges[i+1].vPoint[0];
		vertex[i*4+2].color = dwRibbonColor;
		vertex[i*4+2].u = k*i+k;
		vertex[i*4+2].v = 1.0f;

		vertex[i*4+3].p = *(D3DXVECTOR3*)&edges[i+1].vPoint[1];
		vertex[i*4+3].color = dwRibbonColor;
		vertex[i*4+3].u = k*i+k;
		vertex[i*4+3].v = 0;
	}

	return true;	
}
// 增加一个edge，如果缓冲已满，那么缓冲后移一格，
// 然后把这个edge放入第一格
BOOL Mex2RibbonEmitter::AddNewEdge( Mex2RibbonEdge* pEdge )
{
	guardfunc;
////	//CSALocker locker(this);
	assert( nEdgeCount <= nMaxEdgeCount && "mex ribb emitter edge overflow" );
	if( nEdgeCount > 0 )
	{
		//edges[0] = edgeHead;
		if( nEdgeCount < nMaxEdgeCount )
			memcpy( &edges[1], &edges[0], (nEdgeCount)*sizeof( Mex2RibbonEdge ) );
		else
			memcpy( &edges[1], &edges[0], (nMaxEdgeCount-1)*sizeof( Mex2RibbonEdge ) );

		//edges[0].dwLife = pEdge->dwLife;
		//edges[0].dwStartTime = pEdge->dwStartTime;

	}
	//else
	//	edges[0] = *pEdge;
	edges[0] = *pEdge;
	
	nEdgeCount++;
	if( nEdgeCount > nMaxEdgeCount )
		nEdgeCount = nMaxEdgeCount;
	return TRUE;
	unguard;
}

extern void ConvertMatrixToTranslationAndRotation( MeMatrix& m, Vector& v, Quaternion& q );
extern void MakeMatrix( Vector& v, Quaternion& q, MeMatrix& m );
void Mex2RibbonEmitter::Update( int nTime, 
									int nFrameID, 
									float* pfMatrices, 
									float* pfmatModel,
									BOOL bSmooth /*= FALSE*/ )
{
	guardfunc;
////	//CSALocker locker(this);
	MeMatrix* pMatrices = (MeMatrix*)pfMatrices;
	MeMatrix* pmatModel = (MeMatrix*)pfmatModel;

	DWORD dwPassed = nTime-dwLastGenEdgeTime;
	BOOL bNeedGen = FALSE;
	// 如果经过了足够长的时间
	if( dwPassed >= 1000.0f/pSetting->dwEdgePerSec )
		bNeedGen = TRUE;
	// 如果时间还不够，但是frame变化了，则要生成
	else if( nFrameID != nLastFrameID )
		bNeedGen = TRUE;

	nLastFrameID = nFrameID;
	if( bNeedGen )
	{
		dwLastGenEdgeTime = nTime;
		
		D3DXMATRIX matCombine;
		D3DXMatrixMultiply( (D3DXMATRIX*)&matCombine, 
			(D3DXMATRIX*)&pMatrices[pSetting->nParentBoneId],
			(D3DXMATRIX*)pmatModel );

		Vector vNewPos;
		Quaternion qNewQuat;
		D3DXVECTOR3 scale;
		D3DXMatrixDecompose(&scale, (D3DXQUATERNION*)&qNewQuat, (D3DXVECTOR3*)&vNewPos, &matCombine);
		qNewQuat.w = -qNewQuat.w;
		if( bSmooth )
		{
			if( !vLastEdgePos.positionEquals(Vector(0.f, 0.f, 0.f)) )
			{
				// 判断角度差
				Quaternion lastQuat = qLastEdgeQuat;
				lastQuat.normalise();
				Quaternion newQuat = qNewQuat;
				newQuat.normalise();
				float fDot = newQuat.dot(lastQuat);
				if( fDot < 0.86f )	// 角度差大于30°
				{
					float fAngle = acosf(fDot);
					int nCuts = int(fAngle * 12 / PI + 1);	// 每15°插一条边，*180 / 15 / PI
					float fStep = 1.f / nCuts;
					if( nCuts > 1 )
					{
						for( int i=1; i<nCuts; ++i )
						{
							Quaternion quat(qLastEdgeQuat);
							quat.blend(fStep*i, qNewQuat);
							Vector pos = vLastEdgePos;
							pos = pos+fStep*i*(vNewPos-pos);
							MeMatrix newmat;
							MakeMatrix(pos, quat, newmat);
							newmat.m[0][0] *= scale.x; newmat.m[0][1] *= scale.x; newmat.m[0][2] *= scale.x;
							newmat.m[1][0] *= scale.y; newmat.m[1][1] *= scale.y; newmat.m[1][2] *= scale.y;
							newmat.m[2][0] *= scale.z; newmat.m[2][1] *= scale.z; newmat.m[2][2] *= scale.z;

							Mex2RibbonEdge edge;
							GenEdge( &edge, nTime, (MeMatrix*)&newmat );
							AddNewEdge( &edge );
						}
					}
				}
			}
		}
		vLastEdgePos = vNewPos;
		qLastEdgeQuat = qNewQuat;

		Mex2RibbonEdge edge;
		GenEdge( &edge, nTime, (MeMatrix*)&matCombine );
		AddNewEdge( &edge );

		//if( nEdgeCount < nMaxEdgeCount )
		//{
		//	//for( int i = 0; i < nFrame; i++ )
		//	//	GenEdge( &edges[i], 0, &pMatrices[i] );
		//	//nEdgeCount = nFrame;
		//}
		//else
		//{
		//	int nStartFrame = nFrame-nMaxEdgeCount;
		//	for( int i = 0; i < nMaxEdgeCount; i++ )
		//		GenEdge( &edges[i], 0, &pMatrices[nStartFrame+i] );
		//	nEdgeCount = nMaxEdgeCount;

		//}

	}

	//int nFrame = nTime;
	//if( nFrame < nMaxEdgeCount )
	//{
	//	for( int i = 0; i < nFrame; i++ )
	//		GenEdge( &edges[i], 0, &pMatrices[i] );
	//	nEdgeCount = nFrame;
	//}
	//else
	//{
	//	int nStartFrame = nFrame-nMaxEdgeCount;
	//	for( int i = 0; i < nMaxEdgeCount; i++ )
	//		GenEdge( &edges[i], 0, &pMatrices[nStartFrame+i] );
	//	nEdgeCount = nMaxEdgeCount;

	//}
	unguard;
}

void Mex2RibbonEmitter::Render( float* pfMatrix, short stTextureId, float fAlpha, BOOL bInterp, bool bOverUI )
{
	guardfunc;
////	//CSALocker locker(this);
	// 不带插值的渲染
	fAlpha = fAlpha * ( pSetting->dwVertexAlpha / 256.f );
// 	if( !bInterp )
// 	{
// 		RenderNormal( pfMatrix, stTextureId, fAlpha );
// 		return;
// 	}

	RenderNormal( pfMatrix, stTextureId, fAlpha );
	return;

// 	//以下带差值的刀光程序在部分机器上会有问题 Aren
// 	if( nEdgeCount <= 2 )
// 		return;
// 
// 	//int nNumEdge = 0;
// 	//ControlPoints0[0] = edges[0].vPoint[0];
// 	//ControlPoints1[0] = edges[0].vPoint[1];
// 
// 	//for( int i = 1; i < nEdgeCount; i++ )
// 	//{
// 
// 	//}
// 
// 
// 	for( int i = 0; i < nEdgeCount; i++ )
// 	{
// 		ControlPoints0[i] = edges[i].vPoint[0];
// 		ControlPoints1[i] = edges[i].vPoint[1];
// 		if( i > 0 )
// 		{
// 			if( edges[i].vPoint[0].x == edges[i-1].vPoint[0].x &&
// 				edges[i].vPoint[0].y == edges[i-1].vPoint[0].y &&
// 				edges[i].vPoint[0].z == edges[i-1].vPoint[0].z )
// 			{
// 				ControlPoints0[i].x += i*0.001f;
// 				ControlPoints0[i].y += i*0.001f;
// 				ControlPoints0[i].z += i*0.001f;
// 			}
// 
// 			if( edges[i].vPoint[1].x == edges[i-1].vPoint[1].x &&
// 				edges[i].vPoint[1].y == edges[i-1].vPoint[1].y &&
// 				edges[i].vPoint[1].z == edges[i-1].vPoint[1].z )
// 			{
// 				ControlPoints1[i].x += i*0.001f;
// 				ControlPoints1[i].y += i*0.001f;
// 				ControlPoints1[i].z += i*0.001f;
// 			}
// 		}
// 	}
// 
// 
// 	Spline spline0( (float*)ControlPoints0, nEdgeCount );
// 	Spline spline1( (float*)ControlPoints1, nEdgeCount );
// 
// 	spline0.Generate();
// 	spline1.Generate();
// 
// 	int nPointCount0 = spline0.GetCurveCount();
// 	int nPointCount1 = spline1.GetCurveCount();
// 	if( nPointCount0 != nPointCount1 )
// 	{
// 		assert( false );
// 	}
// 
// 	float d = 0.001f;
// 	float k = (1.0f-2*d)/(nPointCount0-1);
// 	DWORD color = 0xffffffff;
// 	int const MAX_POINT = 1024;
// 	static CEmitterVertex v[MAX_POINT*2];
// 	static D3DXVECTOR3 vCurvePoints0[MAX_POINT];
// 	static D3DXVECTOR3 vCurvePoints1[MAX_POINT];
// 	nPointCount0 = 0;
// 	nPointCount1 = 0;
// 	spline0.GetCurve( (float*)vCurvePoints0, nPointCount0 );
// 	spline1.GetCurve( (float*)vCurvePoints1, nPointCount1 );
// 	for(int i = 0; i < nPointCount0-1; i++ )
// 	{
// 		//k = 0;
// 		v[i*4].p = vCurvePoints0[i];
// 		v[i*4].color = color;
// 		//v[i*4].p.x = 0.0f;
// 		v[i*4].u = d+k*i;
// 		v[i*4].v = 0.99f;
// 
// 		v[i*4+1].p = vCurvePoints1[i];
// 		v[i*4+1].color = color;
// 		//v[i*4+1].p.x = 0.0f;
// 		v[i*4+1].u = d+k*i;
// 		v[i*4+1].v = 0.01f;
// 
// 		v[i*4+2].p = vCurvePoints0[i+1];
// 		v[i*4+2].color = color;
// 		//v[i*4+2].p.x = 0.0f;
// 		v[i*4+2].u = d+k*i+k;
// 		v[i*4+2].v = 0.99f;
// 
// 		v[i*4+3].p = vCurvePoints1[i+1];
// 		//v[i*4+3].p.x = 0.0f;
// 		v[i*4+3].color = color;
// 		v[i*4+3].u = d+k*i+k;
// 		v[i*4+3].v = 0.01f;
// 	}
// 
// 	DWORD dwFlag = eTwoSided|eAlphaBlend|eZWriteDisable|eDstBlendOne/*|eDstBlendOne*/;
// 
// 	if( bOverUI )
// 	{
// 		dwFlag |= eZDisable;
// 	}
// 
// ////	GetEngine()->GetRenderer()->SetRenderState( D3DRS_FOGENABLE, FALSE );
// //	GetEngine()->GetRenderer()->DirectPushSurface( 
// //		stTextureId,
// //		-1, 
// //		MEX2_SHADER,
// //		D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1, 
// //		sizeof( CEmitterVertex ), 
// //		(BYTE*)v,
// //		(nPointCount0-1)*4, 
// //		(BYTE*)Emitter::GetCWIndexBuffer(), 
// //		(nPointCount0-1)*2,
// //		dwFlag|eLightingDisable );
// //	//GetEngine()->GetRenderer()->SetRenderState( D3DRS_FOGENABLE, TRUE );
// 
// 	MeRenderObject* pkObject = ( MeRenderObject* )m_spRenderObject;			
// 	MeParticleRibbonRenderObject* pkPObject = dynamic_cast< MeParticleRibbonRenderObject* >( pkObject );
//  	if( pkPObject )
//  	{
// 		if( MeRenderManager::Instance()->IsFreshObject( this ) )
// 		{
// 			pkPObject->SetUseTexId( stTextureId );
// 			pkPObject->SetShaderId( MEX2_SHADER );
// 			pkPObject->SetFVF( D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1 );
// 			pkPObject->SetStride( sizeof( CEmitterVertex ) );
// 			pkPObject->SetVB( (BYTE*)v );
// 			pkPObject->SetVertexCount( (nPointCount0 - 1)*4 );
// 			pkPObject->SetIB( (BYTE*)Emitter::GetCWIndexBuffer() );
// 			pkPObject->SetFaceCount( (nPointCount0 - 1 ) * 2 );
// 			pkPObject->SetFlag( dwFlag | eLightingDisable );
// 			pkObject->GenerateKey();
// 			MeRenderManager::Instance()->AddObject( this );
// 		} 		
//  	}
// 	return;
	unguard;
}
// LPDIRECT3DVERTEXBUFFER9 Mex2RibbonEmitter::m_pVB = 0;
// LPDIRECT3DINDEXBUFFER9 Mex2RibbonEmitter::m_pIB = 0;
// bool Mex2RibbonEmitter::createBuffers()
// {
// 	destroyBuffers();
// 
// 	int faceCount = 512;
// 
// 	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
// 	HRESULT hr = pDev->CreateVertexBuffer( faceCount*4*sizeof(SEmitterVertex), D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &m_pVB, NULL );
// 	if( FAILED(hr) )
// 		return false;
// 
// 	hr = pDev->CreateIndexBuffer( faceCount*6*sizeof(short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB, NULL );
// 	if( FAILED(hr) )
// 	{
// 		SafeRelease(m_pVB);
// 		return false;
// 	}
// 
// 	void* indices = 0;
// 	if (FAILED(m_pIB->Lock(0, 0, &indices, 0)))
// 	{
// 		SafeRelease(m_pVB);
// 		SafeRelease(m_pIB);
// 		return false;
// 	}
// 
// 	memcpy_s(indices, faceCount*6*sizeof(short), Emitter::GetCWIndexBuffer(), faceCount*6*sizeof(short));
// 
// 	m_pIB->Unlock();
// 
// 	return true;
// }

// void Mex2RibbonEmitter::destroyBuffers()
// {
// 	SafeRelease(m_pVB);
// 	SafeRelease(m_pIB);
// }
void Mex2RibbonEmitter::RenderNormal( float* pfMatrix, short stTextureID, float fAlpha )
{
	guardfunc;

	MeRenderObject *pkObject = (MeRenderObject *) m_spRenderObject;			
	MeParticleRibbonRenderObject *pkPObject = dynamic_cast<MeParticleRibbonRenderObject *> (pkObject);
	if( pkPObject )
	{
		if( ( GetCollectibleType() != SortRenderable::eCT_Shimmer ) )		
			SetCollectibleType( SortRenderable::eCT_AlphaBlend );			
		if( MeRenderManager::Instance()->IsFreshObject( this ) )
		{
			pkPObject->SetUseTexId( stTextureID );
			pkPObject->SetShaderId( MEX2_PARTICLE );
			pkPObject->SetFVF( D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1 );
			pkPObject->SetStride( sizeof( SEmitterVertex ) );
// 			pkPObject->SetVB( (BYTE*)m_pVB );
			pkPObject->SetVertexCount( (nEdgeCount-1)*4 );
// 			pkPObject->SetIB( (BYTE*)m_pIB );
 			pkPObject->SetIB( (BYTE*)Emitter::GetCWIndexBuffer() );
			pkPObject->SetFaceCount( (nEdgeCount-1)*2 );
			pkPObject->SetFlag( pSetting->dwBlendMode | eLightingDisable);
			pkPObject->SetAlpha( fAlpha );
			pkObject->GenerateKey();
			MeRenderManager::Instance()->AddObject( this );
		}		
	}
	
	return;
	unguard;
}
BOOL Mex2RibbonEmitters::Bind( Mex2* pMex )
{
	guardfunc;
	for( int i = 0; i < vectorRibbonEmitter.size(); i++ )
		vectorRibbonEmitter[i].Bind( pMex );
	return TRUE;
	unguard;
}

BOOL Mex2RibbonEmitters::Read( Mex2Pointer inP, int nSize )
{
	guardfunc;
	////CSALocker locker(this);
	Mex2Pointer p(inP.p);
	while( p.c < inP.c+nSize )
	{
		switch( MEX_TAG( *p.dw ) )
		{
		case 'ribb':
			{
				p.dw++;
				int size = *p.i++;
				Mex2RibbonEmitter re;
				//Mex2BoneGroup boneGroup;
				re.Read( p, size );
				vectorRibbonEmitter.push_back( re );
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

//void Mex2RibbonEmitters::Update( int nTime, MeMatrix* pmatModel )
//{
//	//for( int i = 0; i < vectorRibbonEmitter.size(); i++ )
//	//	vectorRibbonEmitter[i].Update( nTime, pmatModel );
//}

//void Mex2RibbonEmitters::Render()
//{
//	for( int i = 0; i < vectorRibbonEmitter.size(); i++ )
//		vectorRibbonEmitter[i].Render();
//}

//////////////////////////////////////////////////////////////////////////
// particle system

Mex2ParticleEmitter::Mex2ParticleEmitter():
dwVersion(1),
bReleased(FALSE),
//setting(NULL),
pSrcMex(NULL),
m_fScale(1.0f),
m_nTime(0),
m_fPlaySpeed(1.0f),
m_nNumPart(0),
m_nAliveNumPart(0),
particles(NULL),
m_bRotateParticle(FALSE),
m_bRandomDir( FALSE ),			    //added by ZhuoMeng.Hu		[8/5/2010]
m_bNoSelfRotate( FALSE ),           //added by zhuomeng.hu		[1/30/2011]
m_bUVRandomFirstCell( FALSE ),      //added by zhuomeng.hu		[3/10/2011]
m_bXYInWorldSpace( FALSE ),         //added by zhuomeng.hu		[3/17/2011]
m_fRenderAlpha( 1.f ),
m_nRotate360DegreeCostTime(1000)/*,
m_pVB(NULL),
m_pIB(NULL)*/
{
	guardfunc;
	Reset();
	m_spRenderObject = MeNew MeParticleRibbonRenderObject;
	unguard;
};
Mex2ParticleEmitter::~Mex2ParticleEmitter()
{
	guardfunc;
	//assert( bReleased == TRUE );
	assert( particles == NULL );	
	unguard;
}
void Mex2ParticleEmitter::Release()
{
	guardfunc;

	bReleased = TRUE;
	MEX2_SAFE_DELETE_ARRAY(particles);
	//destroyBuffers();
	delete this;
	unguard;
}
void Mex2ParticleEmitter::Reset()
{
	guardfunc;

	m_bIsActive = TRUE;
	m_bSquirtted = FALSE;
	vPos = Vector( 0, 0, 0 );
	dwLastUpdateTime = 0;
	dwLastGenPartsTime = 0;
	for( int i = 0; i < m_nNumPart; i++ )
	{
		particles[i].dwBornTime = 0;
		particles[i].dwLife = 0;
		particles[i].fSpeed = 0;
		particles[i].fScale = 1.0f;
		particles[i].dwLastUpdateTime = 0;
	}
	//m_szBindPartName[0] = 0;
	memset( m_szBindPartName, 0x00, MEX2_MAX_NAME );

	m_bUseTimeBasedCell = FALSE;
	m_nSeqLoopTimes = 0;
	m_bRotateParticle = FALSE;
	unguard;
}

void Mex2ParticleEmitter::Read( Mex2Pointer inP,int inSize )
{
	guardfunc;

	Mex2Pointer p(inP);
	memcpy( &setting, p.c, sizeof(Mex2ParticleEmitterSetting) );
	m_nNumPart = int(setting.fEmissionRate*setting.fLifeSpan);
	unguard;
}
void Mex2ParticleEmitter::Read2( Mex2Pointer inP,int inSize, DWORD version )
{
	guardfunc;
	
	/*
	 * 2012.6.9 wangshuai
	 * 老的粒子都是用的2, 为了兼容老的资源
	 */
	Mex2Pointer p(inP);
	memcpy(&setting, p.c, sizeof(Mex2ParticleEmitterSetting2));
	p.c += sizeof(Mex2ParticleEmitterSetting2);

	m_nNumPart = int(setting.fEmissionRate*setting.fLifeSpan);

	// modified, jiayi, [2009.4.17], 取反x轴
	if( version < 107 )		//added by zhuomeng.hu		[8/17/2010]
		setting.vPivot.x *= -1;

	// 说明有补充数据了
	if( p.c < inP.c + inSize)
	{
		CDataChunkLoader l(p.byte, inSize - sizeof(Mex2ParticleEmitterSetting2));
		while( !l.IsEndOfMemory() )
		{		
			if( l.IsChunk( 'bprt' ) )
			{
				l.StartChunk( 'bprt' );
				{
					CDataChunkLoader s(l);
					s.ReadToBuffer( (BYTE*)m_szBindPartName, MEX2_MAX_NAME );
				}
				l.EndChunk( 'bprt' );
			}
			else if ( l.TryReadIntChunk( 'utbc', m_bUseTimeBasedCell ) ){}
			else if ( l.TryReadIntChunk( 'sqlt', m_nSeqLoopTimes ) ){}
			else if ( l.TryReadIntChunk( 'brp', m_bRotateParticle ) ){}
			else if ( l.TryReadIntChunk( 'rpds', m_nRotate360DegreeCostTime ) ){}
            else if ( version > 104 && l.TryReadIntChunk( 'brdd', m_bRandomDir ) ){}	//added by zhuomeng.hu		[8/6/2010]
            else if (l.TryReadIntChunk( 'bnsr', m_bNoSelfRotate ) ){}    //added by zhuomeng.hu		[1/30/2011]
			else
            {
				l.SkipChunk();
            }
		}
	}
	unguard;
}

// added by zhuomeng.hu		[2/12/2011]
void Mex2ParticleEmitter::Read3( Mex2Pointer inP, int inSize, DWORD version )
{
    // 因为 EmitterSetting 版本提升到 3 的时候，Particle的版本已经是109了，所以之前关于版本的判断直接省略了
    Mex2Pointer p( inP );
    Mex2ParticleEmitterSetting3 temp;
    memcpy( &temp, p.c, sizeof( Mex2ParticleEmitterSetting3 ) );
    setting = temp; 
    p.c += sizeof( Mex2ParticleEmitterSetting3 );
    m_nNumPart = int( setting.fEmissionRate * setting.fLifeSpan );
    if( p.c < inP.c + inSize )
    {
        CDataChunkLoader l( p.byte, inSize - sizeof( Mex2ParticleEmitterSetting3 ) );
        while( !l.IsEndOfMemory() )
        {
            if( l.IsChunk( 'bprt' ) )
            {
                l.StartChunk( 'bprt' );
                {
                    CDataChunkLoader s( l );
                    s.ReadToBuffer( ( BYTE* )m_szBindPartName, MEX2_MAX_NAME );
                }
                l.EndChunk( 'bprt' );
            }
            else if( l.TryReadIntChunk( 'utbc', m_bUseTimeBasedCell ) ){}
            else if( l.TryReadIntChunk( 'sqlt', m_nSeqLoopTimes ) ){}
            else if( l.TryReadIntChunk( 'brp', m_bRotateParticle ) ){}
            else if( l.TryReadIntChunk( 'rpds', m_nRotate360DegreeCostTime ) ){}
            else if( l.TryReadIntChunk( 'brdd', m_bRandomDir ) ){}
            else if( l.TryReadIntChunk( 'bnsr', m_bNoSelfRotate ) ){}
            else
            {
                l.SkipChunk();
            }
        }
    }
}

// added by zhuomeng.hu		[2/18/2011]
void Mex2ParticleEmitter::Read4( Mex2Pointer inP, int inSize, DWORD version )
{
	/*
	 * 2012.6.9 wangshuai
	 * 武将三国, 统一使用最新的粒子发射器版本, 即Mex2ParticleEmitterSetting4
	 */
    Mex2Pointer p(inP);
    memcpy(&setting, p.c, sizeof(Mex2ParticleEmitterSetting4));
    p.c += sizeof(Mex2ParticleEmitterSetting4);

    m_nNumPart = int(setting.fEmissionRate * setting.fLifeSpan);
    if( p.c < inP.c + inSize )
    {
        CDataChunkLoader l( p.byte, inSize - sizeof( Mex2ParticleEmitterSetting4 ) );
        while (!l.IsEndOfMemory() )
        {
            if (l.IsChunk( 'bprt' ) )
            {
                l.StartChunk( 'bprt' );
                {
                    CDataChunkLoader s( l );
                    s.ReadToBuffer( ( BYTE* )m_szBindPartName, MEX2_MAX_NAME );
                }
                l.EndChunk( 'bprt' );
            }
            else if (l.TryReadIntChunk( 'utbc', m_bUseTimeBasedCell ) ){}
            else if (l.TryReadIntChunk( 'sqlt', m_nSeqLoopTimes ) ){}
            else if (l.TryReadIntChunk( 'brp', m_bRotateParticle ) ){}
            else if (l.TryReadIntChunk( 'rpds', m_nRotate360DegreeCostTime ) ){}
            else if (l.TryReadIntChunk( 'brdd', m_bRandomDir ) ){}
            else if (l.TryReadIntChunk( 'bnsr', m_bNoSelfRotate ) ){}
            else if (/*version > 109 && */l.TryReadIntChunk( 'brfc', m_bUVRandomFirstCell ) ){}    //added by zhuomeng.hu		[3/10/2011]
            else if (/* version > 110 && */l.TryReadIntChunk( 'bxyw', m_bXYInWorldSpace ) ){}    //added by zhuomeng.hu		[3/17/2011]
            else
            {
                l.SkipChunk();
            }
        }
    }
}

void Mex2ParticleEmitters::Bind( Mex2* pMex )
{
	guardfunc;

	for( int i = 0;i < vectorParticleEmitter.size(); i++ )
		vectorParticleEmitter[i]->pSrcMex = pMex;
	unguard;
}

void Mex2ParticleEmitters::Read( Mex2Pointer inP,int inSize , DWORD version)
{
	guardfunc;

	Mex2Pointer p(inP);
	while((p.c < inP.c+inSize))
	{
		switch( MEX_TAG( *p.dw ) )
		{
		case 'pemt':
			{
				p.dw++;
				int size = *p.i++;
				Mex2ParticleEmitter* emitter = MeNew Mex2ParticleEmitter;
				emitter->Read( p, size );
				vectorParticleEmitter.push_back( emitter );
				p.c += size; 
			}
			break;
		case 'pem2':
			{
				p.dw++;
				int size = *p.i++;
				Mex2ParticleEmitter* emitter = MeNew Mex2ParticleEmitter;
				emitter->dwVersion = 2;
				emitter->Read2( p, size ,version);
				vectorParticleEmitter.push_back( emitter );
				p.c += size; 
			}
			break;
        case 'pem3':
            {
                p.dw++;
                int size = *p.i++;
                Mex2ParticleEmitter* emitter = MeNew Mex2ParticleEmitter;
                emitter->dwVersion = 3;
                emitter->Read3( p, size ,version);
                vectorParticleEmitter.push_back( emitter );
                p.c += size;
            }
            break;
        case 'pem4':
            {
                p.dw++;
                int size = *p.i++;
                Mex2ParticleEmitter* emitter = MeNew Mex2ParticleEmitter;
                emitter->dwVersion = 4;
                emitter->Read4( p, size ,version );
                vectorParticleEmitter.push_back( emitter );
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
	unguard;
}

int Mex2ParticleEmitter::ms_nMaxPartNum = INT_MAX;

void Mex2ParticleEmitter::GenDirection( 
	Vector* axis, 
	float fAngle, 
	Vector* dir )
{
	guardfunc;

	float rad = fAngle*D3DX_PI/180.0f;
	float fRadius = tanf( rad );
	Vector vStart = *axis;
	vStart.normalize();
	Vector vRandomDir = fRadius*RandomDirection();
	Vector vDir = vStart+vRandomDir;
	vDir.normalize();
	*dir = vDir;
	unguard;
}
BOOL Mex2ParticleEmitter::IsParticleDead( Mex2Particle* pParticle, int nTime )
{
	guardfunc;

	return pParticle->dwBornTime+pParticle->dwLife < nTime;
	unguard;
}
void Mex2ParticleEmitter::GenParticle( Mex2Particle* pParticle, int nTime )
{
	guardfunc;

	pParticle->dwBornTime = nTime;
	pParticle->dwLastUpdateTime = nTime;

	// fLifeSpan 单位是秒
    // 粒子生命增加随机值           added by zhuomeng.hu		[2/12/2011]
    if( setting.fLifeSpanMax > 0.0f && setting.fLifeSpanMax > setting.fLifeSpan )
    {
        pParticle->dwLife = ( DWORD )( Random( setting.fLifeSpan, setting.fLifeSpanMax ) * 1000 );
    }
    else
    {
        pParticle->dwLife = ( DWORD )( setting.fLifeSpan * 1000 );
    }

	//   added 2004.07.17
	//if( pParticle->dwLife+nTime >= setting.

	// fSpeed 单位是秒，转化为毫秒, 单位/毫秒
	float fSpeedVar = setting.fSpeed*setting.fVariation/100.0f;
	if( dwVersion == 1 )
		pParticle->fSpeed = ( setting.fSpeed+Random( -fSpeedVar, fSpeedVar ) )/1000;
	else if( dwVersion >= 2 )
		pParticle->fSpeed = ( setting.fSpeed+Random( -fSpeedVar, fSpeedVar ) );
	

	// 初始 UV Cell，增加随机偏移      modified by zhuomeng.hu		[3/10/2011]
    pParticle->nCellOffset = 0;
    if( m_bUVRandomFirstCell )
    {
        pParticle->nCellOffset = Random( 0, setting.nRow * setting.nCol );
    }
	if( setting.dwPart == MEX2_PARTICLE_EMITTER_HEAD )
	{
		pParticle->nCellId = setting.dwLifeSpanHeadUVAnim[0] + pParticle->nCellOffset;
	}
	else if( setting.dwPart == MEX2_PARTICLE_EMITTER_TAIL )
	{
		pParticle->nCellId = setting.dwLifeSpanTailUVAnim[0] + pParticle->nCellOffset;
	}
	//

	// 粒子的初始大小一定是1，不过在运动过程中要*scale
	pParticle->fScale = 1.0f;

    // 粒子尾的长度默认给个 EmitterSetting 的 TailLength          added by zhuomeng.hu		[2/18/2011]
    pParticle->fTailLength = setting.fTailLength;
    
    // 大小的缩放随机值     added by zhuomeng.hu		[2/14/2011]
    if( setting.fScaleRateMax > setting.fScaleRateMin && setting.fScaleRateMin >= 0.0f && setting.fScaleRateMax > 0.0f )
    {
        pParticle->fScaleRandomRate = Random( setting.fScaleRateMin, setting.fScaleRateMax );
    }
    else
    {
        pParticle->fScaleRandomRate = 1.0f;
    }


	if( dwVersion == 1 )
	{
		pParticle->vPos = vPos;
		pParticle->vPos.x += Random( -setting.fWidth, setting.fWidth )*m_fScale;
		pParticle->vPos.y += Random( -setting.fHeight, setting.fHeight )*m_fScale;
	}
	else if( dwVersion >= 2  )
	{
		if( setting.dwFlag & MEX2_PARTICLE_EMITTER_PARTICLEINMODELSPACE )
		{
			pParticle->vPos = 
				vPos+
				1.0f*Random( -setting.fWidth/2, setting.fWidth/2 )*vPlaneXAxis+
				1.0f*Random( -setting.fHeight/2, setting.fHeight/2 )*vPlaneYAxis;
		}
		else
		{
			pParticle->vPos = 
				vPos+
				m_fScale*Random( -setting.fWidth/2, setting.fWidth/2 )*vPlaneXAxis+
				m_fScale*Random( -setting.fHeight/2, setting.fHeight/2 )*vPlaneYAxis;
		}
	}
	pParticle->vBornPos = pParticle->vPos;

	if( setting.dwFlag & MEX2_PARTICLE_EMITTER_PARTICLEINMODELSPACE )
	{
		if (setting.dwPart == MEX2_PARTICLE_EMITTER_HEAD)
			GenDirection( &setting.vPlaneNormal, setting.fConeAngle, &pParticle->vDir );
		else
			GenDirection( &vPlaneNormal, setting.fConeAngle, &pParticle->vDir );
	}
	else
		GenDirection( &vPlaneNormal, setting.fConeAngle, &pParticle->vDir );

	//added by ZhuoMeng.Hu			[8/5/2010]
	pParticle->fRanAngle = 0.0f;
	if( m_bRandomDir )
	{
		pParticle->fRanAngle = Random( 0.0f, 360.0f );
	}

	unguard;	
}
void Mex2ParticleEmitter::UpdateParticle( Mex2Particle* pParticle, 
											int nTime,
											float* pfMatrices,
											MeMatrix* pmatModel )
{
	guardfunc;

	DWORD dwMiddle = pParticle->dwBornTime+(DWORD)(setting.fMiddleTime*pParticle->dwLife);
	DWORD dwEnd = pParticle->dwBornTime+pParticle->dwLife;
	int a = 0, r = 0, g = 0, b = 0;
	if( nTime < dwMiddle )
	{
		int nTimePassed = nTime-pParticle->dwBornTime;
		int nPassedFrameCount = (int)( nTimePassed*setting.dwUVAnimFps/1000.0f );

		float t = (float)(nTime-pParticle->dwBornTime)/( dwMiddle-pParticle->dwBornTime );
		if( t > 0 )
		{
			int k = 0;
		}

        // Scale 增加了一个随机值       modified by zhuomeng.hu		[2/14/2011]
		pParticle->fScale = Slerp( setting.fParticleScaling[0], setting.fParticleScaling[1], t ) * pParticle->fScaleRandomRate;
		
		if( setting.dwPart == MEX2_PARTICLE_EMITTER_HEAD )
		{
			int nCircleFrameCount = setting.dwLifeSpanHeadUVAnim[1] - setting.dwLifeSpanHeadUVAnim[0] + 1;
			pParticle->nCellId = setting.dwLifeSpanHeadUVAnim[0] + pParticle->nCellOffset + nPassedFrameCount % nCircleFrameCount;
		}
		else if( setting.dwPart == MEX2_PARTICLE_EMITTER_TAIL )
		{
			int nCircleFrameCount = setting.dwLifeSpanTailUVAnim[1] - setting.dwLifeSpanTailUVAnim[0] + 1;
			pParticle->nCellId = setting.dwLifeSpanTailUVAnim[0] + pParticle->nCellOffset + nPassedFrameCount % nCircleFrameCount;

            if( setting.bTailLengthChange )
            {
                pParticle->fTailLength = Slerp( setting.fTailLengthChange[0], setting.fTailLengthChange[1], t ) * pParticle->fScaleRandomRate;
            }
		}

		D3DXQUATERNION Q0(setting.nSegmentColor[0][0],setting.nSegmentColor[0][1],setting.nSegmentColor[0][2],setting.nAlpha[0]);
		D3DXQUATERNION Q1(setting.nSegmentColor[1][0],setting.nSegmentColor[1][1],setting.nSegmentColor[1][2],setting.nAlpha[1]);
		D3DXQUATERNION Qout;
		D3DXQuaternionSlerp(&Qout,&Q0,&Q1,t);
		a = (int)Qout.w;
		r = (int)Qout.x;
		g = (int)Qout.y;
		b = (int)Qout.z;

// 		a = (int)Slerp( setting.nAlpha[0], setting.nAlpha[1], t );
// 		r = (int)Slerp( setting.nSegmentColor[0][0], setting.nSegmentColor[1][0], t );
// 		g = (int)Slerp( setting.nSegmentColor[0][1], setting.nSegmentColor[1][1], t );
// 		b = (int)Slerp( setting.nSegmentColor[0][2], setting.nSegmentColor[1][2], t );

// 		pParticle->fLerpT = t;
// 		pParticle->cSegmentColorIndex = 0;
	}
	else
	{
		int nTimePassed = nTime-dwMiddle;
		int nPassedFrameCount = (int)( nTimePassed*setting.dwUVAnimFps/1000.0f );

		float t = (float)(nTime-dwMiddle)/( dwEnd-dwMiddle );
		if( t > 0 )
		{
			int k = 0;
		}

        // Scale 增加了一个随机值       modified by zhuomeng.hu		[2/14/2011]
		pParticle->fScale = Slerp( setting.fParticleScaling[1], setting.fParticleScaling[2], t ) * pParticle->fScaleRandomRate;

		if( setting.dwPart == MEX2_PARTICLE_EMITTER_HEAD )
		{
			int nCircleFrameCount = setting.dwDecayHeadUVAnim[1] - setting.dwDecayHeadUVAnim[0] + 1;
			pParticle->nCellId = setting.dwDecayHeadUVAnim[0] + pParticle->nCellOffset + nPassedFrameCount % nCircleFrameCount;
		}
		else if( setting.dwPart == MEX2_PARTICLE_EMITTER_TAIL )
		{
			int nCircleFrameCount = setting.dwDecayTailUVAnim[1] - setting.dwDecayTailUVAnim[0] + 1;
			pParticle->nCellId = setting.dwDecayTailUVAnim[0] + pParticle->nCellOffset + nPassedFrameCount % nCircleFrameCount;

            if( setting.bTailLengthChange )
            {
                pParticle->fTailLength = Slerp( setting.fTailLengthChange[1], setting.fTailLengthChange[2], t ) * pParticle->fScaleRandomRate;
            }
		}

		D3DXQUATERNION Q1(setting.nSegmentColor[1][0],setting.nSegmentColor[1][1],setting.nSegmentColor[1][2],setting.nAlpha[1]);
		D3DXQUATERNION Q2(setting.nSegmentColor[2][0],setting.nSegmentColor[2][1],setting.nSegmentColor[2][2],setting.nAlpha[2]);
		D3DXQUATERNION Qout;
		D3DXQuaternionSlerp(&Qout,&Q1,&Q2,t);
		a = (int)Qout.w;
		r = (int)Qout.x;
		g = (int)Qout.y;
		b = (int)Qout.z;
// 		a = (int)Slerp( setting.nAlpha[1], setting.nAlpha[2], t );
// 		r = (int)Slerp( setting.nSegmentColor[1][0], setting.nSegmentColor[2][0], t );
// 		g = (int)Slerp( setting.nSegmentColor[1][1], setting.nSegmentColor[2][1], t );
// 		b = (int)Slerp( setting.nSegmentColor[1][2], setting.nSegmentColor[2][2], t );

// 		pParticle->fLerpT = t;
// 		pParticle->cSegmentColorIndex = 1;
	}
	// 新版序列帧播放
	if( m_bUseTimeBasedCell )
	{
        if( setting.dwPart == MEX2_PARTICLE_EMITTER_TAIL )
        {
            int nPassed = nTime - pParticle->dwBornTime;
            int nLoopTime = m_nSeqLoopTimes;
            int nNumFrame = setting.dwLifeSpanTailUVAnim[1] - setting.dwLifeSpanTailUVAnim[0] + 1;
            int nTotalFrame = nLoopTime * nNumFrame;
            float fFrameInterval = pParticle->dwLife / ( float )nTotalFrame;
            int nPassedFrame = ( float )nPassed / fFrameInterval;
            pParticle->nCellId = setting.dwLifeSpanTailUVAnim[0] + pParticle->nCellOffset + nPassedFrame % nNumFrame;
        }
        else
        {
            int nPassed = nTime - pParticle->dwBornTime;
            int nLoopTime = m_nSeqLoopTimes;
            int nNumFrame = setting.dwLifeSpanHeadUVAnim[1] - setting.dwLifeSpanHeadUVAnim[0] + 1;
            int nTotalFrame = nLoopTime * nNumFrame;
            float fFrameInterval = pParticle->dwLife / ( float )nTotalFrame;
            int nPassedFrame = ( float )nPassed / fFrameInterval;
            pParticle->nCellId = setting.dwLifeSpanHeadUVAnim[0] + pParticle->nCellOffset + nPassedFrame % nNumFrame;
        }
	}

    // 粒子顶点反色         added by zhuomeng.hu		[2/14/2011]
    if( setting.bContraryColor )
    {
        r = 255 - r;
        g = 255 - g;
        b = 255 - b;
    }

	if( a < 0 )		a = 0;
	if( a > 255 )	a = 255;
	if( r < 0 )		r = 0;
	if( r > 255 )	r = 255;
	if( g < 0 )		g = 0;
	if( g > 255 )	g = 255;
	if( b < 0 )		b = 0;
	if( b > 255 )	b = 255;
	
	
	pParticle->dwColor = a<<24|r<<16|g<<8|b;
	float fUpdateTimePassed = nTime-pParticle->dwBornTime;
	if( dwVersion >= 2 )
		fUpdateTimePassed /= 1000.0f;
	//pParticle->vPos = pParticle->vBornPos+ 
	//	(pParticle->vDir*pParticle->fSpeed*fUpdateTimePassed)*Config::m_fMdlSpaceScale;

	// 只在模型空间中变换
	if( setting.dwFlag & MEX2_PARTICLE_EMITTER_PARTICLEINMODELSPACE )
	{
		if (setting.dwPart == MEX2_PARTICLE_EMITTER_HEAD)
		{
			MeMatrix* pmatBoneInModelSpace = (MeMatrix*)pfMatrices;

			D3DXVec3Scale((D3DXVECTOR3*)&pParticle->vPos, (D3DXVECTOR3*)&pParticle->vDir, pParticle->fSpeed*fUpdateTimePassed);
			D3DXVec3Add((D3DXVECTOR3*)&pParticle->vPos, (D3DXVECTOR3*)&pParticle->vBornPos, (D3DXVECTOR3*)&pParticle->vPos);

			float s = /*(pParticle->vDir.z*pParticle->fSpeed)*fUpdateTimePassed+*/0.5f*(-setting.fGravity)*fUpdateTimePassed*fUpdateTimePassed;
			s *= m_fScale;
			//pParticle->vPosWorld = pParticle->vPos;


			//pParticle->vPos.z += s;
			//pParticle->vPos += s*pParticle->vDir;

			D3DXVec3TransformCoord( (D3DXVECTOR3*)&pParticle->vPosWorld, 
				(D3DXVECTOR3*)&pParticle->vPos,	
				(D3DXMATRIX*)&pmatBoneInModelSpace[setting.nParentBoneId] );
			D3DXVec3TransformCoord( (D3DXVECTOR3*)&pParticle->vPosWorld, 
				(D3DXVECTOR3*)&pParticle->vPosWorld,	
				(D3DXMATRIX*)pmatModel );

			pParticle->vPosWorld.z += s;
		}
		else
		{
			Vector vBornPos = pParticle->vBornPos;
			D3DXVec3TransformCoord( (D3DXVECTOR3*)&vBornPos, 
				(D3DXVECTOR3*)&vBornPos,	
				(D3DXMATRIX*)pmatModel );

			pParticle->vDir = pParticle->vDirWorld;

			D3DXVec3Scale((D3DXVECTOR3*)&pParticle->vPos, (D3DXVECTOR3*)&pParticle->vDir, pParticle->fSpeed*fUpdateTimePassed*m_fScale);
			D3DXVec3Add((D3DXVECTOR3*)&pParticle->vPos, (D3DXVECTOR3*)&vBornPos, (D3DXVECTOR3*)&pParticle->vPos);

			float s = 0.5f*(-setting.fGravity)*fUpdateTimePassed*fUpdateTimePassed*m_fScale;
			Vector vLastPosition = pParticle->vPosWorld;
			pParticle->vPosWorld = pParticle->vPos;
			pParticle->vPosWorld.z += s;
			if (setting.dwFlag & MEX2_PARTICLE_EMITTER_TANGENT)
			{
				D3DXVec3Subtract((D3DXVECTOR3*)&pParticle->vDynamicPos, (D3DXVECTOR3*)&pParticle->vPosWorld, (D3DXVECTOR3*)&vLastPosition);
				D3DXVec3Normalize((D3DXVECTOR3*)&pParticle->vDynamicPos, (D3DXVECTOR3*)&pParticle->vDynamicPos);
			}
		}
	}
	else if( setting.dwFlag & MEX2_PARTICLE_EMITTER_LOCKEMITTER )
	{
		pParticle->vPos = vPos;
		pParticle->vPosWorld = vPos;
	}
	else
	{

		D3DXVec3Scale((D3DXVECTOR3*)&pParticle->vPos, (D3DXVECTOR3*)&pParticle->vDir, pParticle->fSpeed*fUpdateTimePassed*m_fScale);
		D3DXVec3Add((D3DXVECTOR3*)&pParticle->vPos, (D3DXVECTOR3*)&pParticle->vBornPos, (D3DXVECTOR3*)&pParticle->vPos);

		float s = 0.5f*(-setting.fGravity)*fUpdateTimePassed*fUpdateTimePassed*m_fScale;
		Vector vLastPosition = pParticle->vPosWorld;
		pParticle->vPosWorld = pParticle->vPos;
		pParticle->vPosWorld.z += s;
		if (setting.dwFlag & MEX2_PARTICLE_EMITTER_TANGENT)
		{
			D3DXVec3Subtract((D3DXVECTOR3*)&pParticle->vDynamicPos, (D3DXVECTOR3*)&pParticle->vPosWorld, (D3DXVECTOR3*)&vLastPosition);
			D3DXVec3Normalize((D3DXVECTOR3*)&pParticle->vDynamicPos, (D3DXVECTOR3*)&pParticle->vDynamicPos);
		}
	}


	pParticle->dwLastUpdateTime = nTime;
	unguard;
}
IMexParticleEmitter* Mex2ParticleEmitter::Clone()
{ 
	guardfunc;

	Mex2ParticleEmitter* p = MeNew Mex2ParticleEmitter;
	p->setting = setting;
	p->dwVersion = dwVersion;
	p->pSrcMex = pSrcMex;
	p->m_nNumPart = m_nNumPart;
	
	if( m_nNumPart > 0 )
	{
		p->particles = MeNew Mex2Particle[m_nNumPart];
		p->Reset();
		strcpy( p->m_szBindPartName, m_szBindPartName  );
	}
	p->m_bUseTimeBasedCell = m_bUseTimeBasedCell;
	p->m_nSeqLoopTimes = m_nSeqLoopTimes;
	p->m_bRotateParticle = m_bRotateParticle;
	p->m_nRotate360DegreeCostTime = m_nRotate360DegreeCostTime;
    p->m_bRandomDir = m_bRandomDir;                     //added by ZhuoMeng.Hu		[10/18/2010]
    p->m_bNoSelfRotate = m_bNoSelfRotate;               //added by zhuomeng.hu		[1/30/2011]
    p->m_bUVRandomFirstCell = m_bUVRandomFirstCell;     //added by zhuomeng.hu		[3/10/2011]
    p->m_bXYInWorldSpace = m_bXYInWorldSpace;           //added by zhuomeng.hu		[3/17/2011]
	return p;
	unguard;
}

void Mex2ParticleEmitter::SetBindPartName(const char *szBindPart)
{
	if (szBindPart != NULL)
		strcpy_s(m_szBindPartName, MEX2_MAX_NAME, szBindPart);
	else
		memset(m_szBindPartName, MEX2_MAX_NAME, 0);
}

void Mex2ParticleEmitter::Update( int nTime, float fScale, float* pfMatrices, float* pfmatModel,int nFrameId )
{
	guardfunc;

	m_nTime = nTime;
	m_fScale = fScale;
	MeMatrix* pMatBoneInModelSpace = (MeMatrix*)pfMatrices;
	MeMatrix* pmatModel = (MeMatrix*)pfmatModel;

	// 计算发射器最新位置
	// 模型空间中


	if (setting.dwPart == MEX2_PARTICLE_EMITTER_HEAD)
	{
		if( setting.dwFlag & MEX2_PARTICLE_EMITTER_PARTICLEINMODELSPACE )
		{
			vPos = setting.vPivot;
		}
		else
		{
			D3DXVec3TransformCoord( (D3DXVECTOR3*)&vPos, 
				(D3DXVECTOR3*)&setting.vPivot,	
				(D3DXMATRIX*)&pMatBoneInModelSpace[setting.nParentBoneId] );
		}
	}
	else
	{
		D3DXVec3TransformCoord( (D3DXVECTOR3*)&vPos, 
			(D3DXVECTOR3*)&setting.vPivot,	
			(D3DXMATRIX*)&pMatBoneInModelSpace[setting.nParentBoneId] );
	}


	// view的反方向
	Vector vAntiView = *(Vector*)&GetMe3dConfig()->GetCamera()->GetViewDir();
	vAntiView *= -1;

	//
	vPlaneNormal = Vector( 0, 0, 1 );
	// 发射平面的法线辅助点
	Vector vNormalPoint = setting.vPivot+setting.vPlaneNormal;
	// 发射平面的x轴辅助点
	Vector vPlaneX = setting.vPivot+setting.vPlaneXAxis;
	// 发射平面的y轴辅助点
	Vector vPlaneY = setting.vPivot+setting.vPlaneYAxis;
	if( dwVersion == 1 )
	{}
	else if( dwVersion >= 2 )
	{
		// 把发射平面法线辅助点变换到空间中
		D3DXVec3TransformCoord( (D3DXVECTOR3*)&vNormalPoint, 
			(D3DXVECTOR3*)&vNormalPoint,	
			(D3DXMATRIX*)&pMatBoneInModelSpace[setting.nParentBoneId] );

		// 把发射平面x轴辅助点变换到空间中
		D3DXVec3TransformCoord( (D3DXVECTOR3*)&vPlaneX, 
			(D3DXVECTOR3*)&vPlaneX,	
			(D3DXMATRIX*)&pMatBoneInModelSpace[setting.nParentBoneId] );

		// 把发射平面y轴辅助点变换到空间中
		D3DXVec3TransformCoord( (D3DXVECTOR3*)&vPlaneY, 
			(D3DXVECTOR3*)&vPlaneY,	
			(D3DXMATRIX*)&pMatBoneInModelSpace[setting.nParentBoneId] );
	}
	else
	{
		assert( false );
	}

	Vector vPlaneNormalWorld;

	if( ( setting.dwFlag & MEX2_PARTICLE_EMITTER_PARTICLEINMODELSPACE ) )
	{
		Vector vPosWorld;
		Vector vNormalPointWorld;

		// 在世界空间中，还需要进行世界变换
		D3DXVec3TransformCoord( (D3DXVECTOR3*)&vPosWorld, 
			(D3DXVECTOR3*)&vPos,	
			(D3DXMATRIX*)pmatModel );
		// 变换法线辅助点，x，y轴的辅助点
		D3DXVec3TransformCoord( (D3DXVECTOR3*)&vNormalPointWorld, 
			(D3DXVECTOR3*)&vNormalPoint,	
			(D3DXMATRIX*)pmatModel );

		// 得到最终空间中的法线
		vPlaneNormalWorld = vNormalPointWorld-vPosWorld;
		D3DXVec3Normalize( (D3DXVECTOR3*)&vPlaneNormalWorld, (D3DXVECTOR3*)&vPlaneNormalWorld );
	}
	else
	{
		// 在世界空间中，还需要进行世界变换
		D3DXVec3TransformCoord( (D3DXVECTOR3*)&vPos, 
			(D3DXVECTOR3*)&vPos,	
			(D3DXMATRIX*)pmatModel );
		// 变换法线辅助点，x，y轴的辅助点
		D3DXVec3TransformCoord( (D3DXVECTOR3*)&vNormalPoint, 
			(D3DXVECTOR3*)&vNormalPoint,	
			(D3DXMATRIX*)pmatModel );

		D3DXVec3TransformCoord( (D3DXVECTOR3*)&vPlaneX, 
			(D3DXVECTOR3*)&vPlaneX,	
			(D3DXMATRIX*)pmatModel );
		D3DXVec3TransformCoord( (D3DXVECTOR3*)&vPlaneY, 
			(D3DXVECTOR3*)&vPlaneY,	
			(D3DXMATRIX*)pmatModel );

	}

    // 粒子是否跟随发射器的变换而旋转增加开关           added by zhuomeng.hu		[1/30/2011]
    if( !m_bNoSelfRotate )
    {
        // 得到最终空间中的法线及x，y轴
        vPlaneNormal = vNormalPoint-vPos;
        D3DXVec3Normalize( (D3DXVECTOR3*)&vPlaneNormal, (D3DXVECTOR3*)&vPlaneNormal );
        vPlaneXAxis = vPlaneX-vPos;
        D3DXVec3Normalize( (D3DXVECTOR3*)&vPlaneXAxis, (D3DXVECTOR3*)&vPlaneXAxis );
        vPlaneYAxis = vPlaneY-vPos;
        D3DXVec3Normalize( (D3DXVECTOR3*)&vPlaneYAxis, (D3DXVECTOR3*)&vPlaneYAxis );

        // 对发射器平面ｘ，ｙ轴的更新会使得粒子产生旋转
        // 这倒是可以利用的地方
        // 
    }
    else
    {
        vPlaneNormal = setting.vPlaneNormal;
        vPlaneXAxis = setting.vPlaneXAxis;
        vPlaneYAxis = setting.vPlaneYAxis;
        D3DXVec3Normalize( (D3DXVECTOR3*)&vPlaneNormal, (D3DXVECTOR3*)&vPlaneNormal );
        D3DXVec3Normalize( (D3DXVECTOR3*)&vPlaneXAxis, (D3DXVECTOR3*)&vPlaneXAxis );
        D3DXVec3Normalize( (D3DXVECTOR3*)&vPlaneYAxis, (D3DXVECTOR3*)&vPlaneYAxis );
    }

	// 得到右轴和上轴，建立摄像机变换的矩阵
	if( setting.dwFlag & MEX2_PARTICLE_EMITTER_XYQUAD )
	{
        // 增加了一种世界坐标中的XY平面类型     modified by zhuomeng.hu		[3/18/2011]
        if( !m_bXYInWorldSpace )
        {
            D3DXMATRIX matModelToWorld;
            D3DXMatrixMultiply( &matModelToWorld,
                (D3DXMATRIX*)&pMatBoneInModelSpace[setting.nParentBoneId],
                (D3DXMATRIX*)pmatModel );
            Vector o;
            D3DXVec3TransformCoord( (D3DXVECTOR3*)&o, 
                (D3DXVECTOR3*)&setting.vPivot,	
                &matModelToWorld );

            D3DXVec3TransformCoord( (D3DXVECTOR3*)&vPlaneViewRight, 
                (D3DXVECTOR3*)&(setting.vPivot+setting.vPlaneXAxis),	
                &matModelToWorld );
            D3DXVec3TransformCoord( (D3DXVECTOR3*)&vPlaneViewUp, 
                (D3DXVECTOR3*)&(setting.vPivot+setting.vPlaneYAxis),	
                &matModelToWorld );

            vPlaneViewRight -= o;
            vPlaneViewUp -= o;
            D3DXVec3Normalize( (D3DXVECTOR3*)&vPlaneViewRight, (D3DXVECTOR3*)&vPlaneViewRight );
            D3DXVec3Normalize( (D3DXVECTOR3*)&vPlaneViewUp, (D3DXVECTOR3*)&vPlaneViewUp );
        }
        else
        {
            vPlaneViewUp = Vector( - setting.vPlaneNormal.x, - setting.vPlaneNormal.y, 0.0f );
            D3DXVec3Normalize( ( D3DXVECTOR3* )&vPlaneViewUp, ( D3DXVECTOR3* )&vPlaneViewUp );
            D3DXVec3Cross( ( D3DXVECTOR3* )&vPlaneViewRight, ( D3DXVECTOR3* )&vPlaneViewUp, &D3DXVECTOR3( 0.0f, 0.0f, 1.0f ) );
            D3DXVec3Normalize( (D3DXVECTOR3*)&vPlaneViewRight, (D3DXVECTOR3*)&vPlaneViewRight );
        }
	}
	else
	{
		if( setting.dwFlag & MEX2_PARTICLE_EMITTER_PARTICLEINMODELSPACE && setting.dwPart != MEX2_PARTICLE_EMITTER_HEAD )
		{	
			D3DXVec3Cross( (D3DXVECTOR3*)&vPlaneViewRight, (D3DXVECTOR3*)&vPlaneNormalWorld, &GetMe3dConfig()->GetCamera()->GetViewDir() );
			D3DXVec3Cross( (D3DXVECTOR3*)&vPlaneViewUp,  &GetMe3dConfig()->GetCamera()->GetViewDir(), (D3DXVECTOR3*)&vPlaneViewRight );
			//vPlaneViewUp = vPlaneNormal;
			D3DXVec3Normalize( (D3DXVECTOR3*)&vPlaneViewRight, (D3DXVECTOR3*)&vPlaneViewRight );
			D3DXVec3Normalize( (D3DXVECTOR3*)&vPlaneViewUp, (D3DXVECTOR3*)&vPlaneViewUp );
		}
		else
		{
			D3DXVec3Cross( (D3DXVECTOR3*)&vPlaneViewRight, (D3DXVECTOR3*)&vPlaneNormal, &GetMe3dConfig()->GetCamera()->GetViewDir() );
			D3DXVec3Cross( (D3DXVECTOR3*)&vPlaneViewUp,  &GetMe3dConfig()->GetCamera()->GetViewDir(), (D3DXVECTOR3*)&vPlaneViewRight );
			//vPlaneViewUp = vPlaneNormal;
			D3DXVec3Normalize( (D3DXVECTOR3*)&vPlaneViewRight, (D3DXVECTOR3*)&vPlaneViewRight );
			D3DXVec3Normalize( (D3DXVECTOR3*)&vPlaneViewUp, (D3DXVECTOR3*)&vPlaneViewUp );
		}
	}

	if( setting.nParentBoneId == -1 )
		return;

	if( !pSrcMex )
	{
		assert( false );
		return;
	}

	BOOL bVisible = pSrcMex->IsBoneVisible( nFrameId, setting.nParentBoneId );

	// 仅在bVisible时才会生成新的粒子
	if( bVisible &&
		m_bIsActive &&
		!m_bSquirtted )
	{
		if( setting.dwFlag & MEX2_PARTICLE_EMITTER_SQUIRT )
		{
			m_bSquirtted = TRUE;
			// 在一瞬间创建所有的粒子
			for( int i = 0; i < min( m_nNumPart, ms_nMaxPartNum )/*setting.nCount*/; i++ )
			{
				// 粒子已经死亡
				if( IsParticleDead( &particles[i], m_nTime ) )
				{
					GenParticle( &particles[i], m_nTime );
					GenDirection( &vPlaneNormalWorld, setting.fConeAngle, &particles[i].vDirWorld );
				}
			}

		}
		else
		{
			// 产生一颗新粒子
			//if( m_bIsActive &&
			//	!m_bSquirtted &&
			//   added 2004.10.16
			// 粒子产生粒度
			static const DWORD L = 1;
			DWORD dwGenInterval = 0;
			// 期望的每秒产生粒子数
			float fPartPerSec = setting.fEmissionRate*m_fPlaySpeed;
			// 每秒产生次数
			
			// 每个粒度期望产生的粒子数
			DWORD dwWillGenPartCount = 0;
			// 如果更新间隔>最小粒度,则按照更新间隔计算
			if( 1000.0f/fPartPerSec > L )
			{
				dwGenInterval = (DWORD)(1000.0f/fPartPerSec);
				dwWillGenPartCount = 1;
			}
			else
			{
				DWORD dwGenTimesPerSec = 1000.0f/L;
				dwGenInterval = L;
				dwWillGenPartCount = (DWORD)(fPartPerSec/dwGenTimesPerSec);
			}
			//if(	m_nTime-dwLastGenPartsTime >= (int)(1000.0f/setting.fEmissionRate) )
			if(	m_nTime-dwLastGenPartsTime >= dwGenInterval )
			{
				dwLastGenPartsTime = m_nTime;
				//int nGenCount = 0;
				for( int nGenCount = 0; nGenCount < dwWillGenPartCount; nGenCount++ )
				{
					BOOL bHasDeadPart = FALSE;
					for( int i = 0; i < min( m_nNumPart, ms_nMaxPartNum )/*setting.nCount*/; i++ )
					{
						// 粒子已经死亡
						if( IsParticleDead( &particles[i], m_nTime ) )
						{
							bHasDeadPart = TRUE;
							GenParticle( &particles[i], m_nTime );
							GenDirection( &vPlaneNormalWorld, setting.fConeAngle, &particles[i].vDirWorld );
							break;
						}
					}
					// 如果已经没有空闲的粒子,那么就不用继续了,
					// 等待下一个时机
					if( !bHasDeadPart )
						break;
				}
			}
		}
	}
	m_nAliveNumPart = 0;
	D3DXVECTOR3 vSum(0,0,0);
	for( int i = 0; i < min( m_nNumPart, ms_nMaxPartNum )/*setting.nCount*/; i++ )
	{
		if( IsParticleDead( &particles[i], m_nTime ) )continue;
		++m_nAliveNumPart;
		UpdateParticle( &particles[i], m_nTime, pfMatrices,  pmatModel );
		D3DXVec3Add(&vSum,&vSum,(D3DXVECTOR3*)&particles[i].vPosWorld);
	}
	if (m_nAliveNumPart != 0)
	{
		D3DXVec3Scale(&m_vCenter,&vSum,1.f/m_nAliveNumPart);
	}
	unguard; 
}

void Mex2ParticleEmitter::MakeARenderParticle( Mex2Particle* pParticle, SEmitterVertex* vertex, float fAlpha )
{
	guardfunc;

	float du = 1.0f/setting.nRow;
	float dv = 1.0f/setting.nCol;

	Vector c = pParticle->vPosWorld;
	for(int i = 0; i < 4; ++i)
	{
		DWORD alpha = ((DWORD)((pParticle->dwColor & 0xFF000000) * fAlpha) )& 0xFF000000;
		vertex[i].color = (pParticle->dwColor & 0x00FFFFFF) | alpha;
// 		vertex[i].color = pParticle->dwColor;
	}
	if( setting.dwPart == MEX2_PARTICLE_EMITTER_HEAD )
	{
		float fSize = pParticle->fScale*m_fScale;

		Vector up;
		Vector right;
		D3DXVec3Scale((D3DXVECTOR3*)&up, (D3DXVECTOR3*)&vPlaneViewUp, fSize);
		D3DXVec3Scale((D3DXVECTOR3*)&right, (D3DXVECTOR3*)&vPlaneViewRight, fSize);

        // UV计算BUG    modified by zhuomeng.hu		[3/10/2011]
        int row = pParticle->nCellId / setting.nRow % setting.nCol;
        int col = pParticle->nCellId % setting.nRow;

		D3DXVec3Subtract((D3DXVECTOR3*)&vertex[0].p, (D3DXVECTOR3*)&c, (D3DXVECTOR3*)&up);
		D3DXVec3Subtract((D3DXVECTOR3*)&vertex[0].p, (D3DXVECTOR3*)&vertex[0].p, (D3DXVECTOR3*)&right);
		//vertex[0].color = dwParticleColor;
		vertex[0].u = du*col;
		vertex[0].v = dv*row+dv;
// 		vertex[0].t = pParticle->fLerpT;
// 		vertex[0].c = pParticle->cSegmentColorIndex;

		D3DXVec3Add((D3DXVECTOR3*)&vertex[1].p, (D3DXVECTOR3*)&c, (D3DXVECTOR3*)&up);
		D3DXVec3Subtract((D3DXVECTOR3*)&vertex[1].p, (D3DXVECTOR3*)&vertex[1].p, (D3DXVECTOR3*)&right);
		//vertex[1].color = dwParticleColor;
		vertex[1].u = du*col;
		vertex[1].v = dv*row;
// 		vertex[1].t = pParticle->fLerpT;
// 		vertex[1].c = pParticle->cSegmentColorIndex;

		D3DXVec3Subtract((D3DXVECTOR3*)&vertex[2].p, (D3DXVECTOR3*)&c, (D3DXVECTOR3*)&up);
		D3DXVec3Add((D3DXVECTOR3*)&vertex[2].p, (D3DXVECTOR3*)&vertex[2].p, (D3DXVECTOR3*)&right);
		//vertex[2].color = dwParticleColor;
		vertex[2].u = du*col+du;
		vertex[2].v = dv*row+dv;
// 		vertex[2].t = pParticle->fLerpT;
// 		vertex[2].c = pParticle->cSegmentColorIndex;


		D3DXVec3Add((D3DXVECTOR3*)&vertex[3].p, (D3DXVECTOR3*)&c, (D3DXVECTOR3*)&up);
		D3DXVec3Add((D3DXVECTOR3*)&vertex[3].p, (D3DXVECTOR3*)&vertex[3].p, (D3DXVECTOR3*)&right);
		//vertex[3].color = dwParticleColor;
		vertex[3].u = du*col+du;
		vertex[3].v = dv*row;
// 		vertex[3].t = pParticle->fLerpT;
// 		vertex[3].c = pParticle->cSegmentColorIndex;

		if (m_bRotateParticle)
		{
			DWORD dwTime = pParticle->dwLastUpdateTime % abs(m_nRotate360DegreeCostTime);
			float fAngle = dwTime * (2.0f * D3DX_PI) / m_nRotate360DegreeCostTime;

			Vector vDir = *((Vector*)&GetMe3dConfig()->GetCamera()->GetEyePt());
			D3DXVec3Subtract((D3DXVECTOR3*)&vDir, (D3DXVECTOR3*)&vDir, (D3DXVECTOR3*)&c);
			D3DXVec3Normalize((D3DXVECTOR3*)&vDir, (D3DXVECTOR3*)&vDir);

			D3DXMATRIX mRot;
			D3DXMatrixRotationAxis(&mRot, (D3DXVECTOR3*)&vDir, fAngle);

			for (int i = 0; i < 4; ++i)
			{
				D3DXVec3Subtract((D3DXVECTOR3*)&vertex[i].p, (D3DXVECTOR3*)&vertex[i].p, (D3DXVECTOR3*)&c);
				D3DXVec3TransformCoord((D3DXVECTOR3*)&vertex[i].p, (D3DXVECTOR3*)&vertex[i].p, &mRot);
				D3DXVec3Add((D3DXVECTOR3*)&vertex[i].p, (D3DXVECTOR3*)&vertex[i].p, (D3DXVECTOR3*)&c);
			}
		}
		//added by ZhuoMeng.Hu				[8/5/2010]
		else if( m_bRandomDir )		
		{
			if( pParticle->fRanAngle != 0.0f )
			{
				Vector vDir = *( ( Vector* )&GetMe3dConfig()->GetCamera()->GetEyePt() );
				D3DXVec3Subtract( ( D3DXVECTOR3* )&vDir, ( D3DXVECTOR3* )&vDir, ( D3DXVECTOR3* )&c );
				D3DXVec3Normalize( ( D3DXVECTOR3* )&vDir, ( D3DXVECTOR3* )&vDir );
				D3DXMATRIX mRot;
				D3DXMatrixRotationAxis( &mRot, ( D3DXVECTOR3* )&vDir, pParticle->fRanAngle );
				for ( int i = 0; i < 4; ++i )
				{
					D3DXVec3Subtract( ( D3DXVECTOR3* )&vertex[i].p, ( D3DXVECTOR3* )&vertex[i].p, ( D3DXVECTOR3* )&c );
					D3DXVec3TransformCoord( ( D3DXVECTOR3* )&vertex[i].p, ( D3DXVECTOR3* )&vertex[i].p, &mRot );
					D3DXVec3Add( ( D3DXVECTOR3* )&vertex[i].p, ( D3DXVECTOR3* )&vertex[i].p, ( D3DXVECTOR3* )&c );
				}
			}
		}
        // 粒子产生后，保持横边与发射方向垂直       added by ZhuoMeng.Hu				[2/18/2011]
        else if( setting.bAngleChangeByCone && setting.fConeAngle > 0 )
        {
            // 获取视口的法线
            Vector vNormal = *( ( Vector* )&GetMe3dConfig()->GetCamera()->GetEyePt() );
            D3DXVec3Subtract( ( D3DXVECTOR3* )&vNormal, ( D3DXVECTOR3* )&vNormal, ( D3DXVECTOR3* )&c );
            D3DXVec3Normalize( ( D3DXVECTOR3* )&vNormal, ( D3DXVECTOR3* )&vNormal );

            // 用该法线和粒子中心构成平面
            D3DXPLANE viewPlane;
            D3DXPlaneFromPointNormal( &viewPlane, ( D3DXVECTOR3* )&c, ( D3DXVECTOR3* )&vNormal );

            // 粒子喷射方向上的一点
            Vector vDirPoint = c + pParticle->vDir;

            // 产生垂直于视口平面且经过 vDirPoint 的另一点
            Vector vTemp = vDirPoint + vNormal;

            // 计算这条直线与视口平面的交点，( vIntersect - c ) 即为 ( vDirPoint - c ) 到视口平面 viewPlane 的投影
            Vector vIntersect;
            D3DXVECTOR3* pResult = D3DXPlaneIntersectLine( ( D3DXVECTOR3* )&vIntersect, &viewPlane, ( D3DXVECTOR3* )&vDirPoint, ( D3DXVECTOR3* )&vTemp );
            if( pResult )
            {
                // 计算投影直线与 up 的夹角
                vTemp = vIntersect - c;
                D3DXVECTOR3 vUp( ( float* )&up );
                D3DXVECTOR3 vDir( ( float* )&vTemp );
                D3DXVec3Normalize( &vUp, &vUp );
                D3DXVec3Normalize( &vDir, &vDir );

                float fDot = D3DXVec3Dot( &vUp, &vDir );
                float fTheta = acosf( fDot );

                // 如果投影直线与 right 轴的夹角为钝角，旋转的角需要取反向
                D3DXVECTOR3 vRight( ( float* )&right );
                D3DXVec3Normalize( &vRight, &vRight );
                if( D3DXVec3Dot( &vRight, &vDir ) < 0.0f )
                {
                    fTheta = - fTheta;
                }

                // 旋转这个角度
                D3DXMATRIX mRot;
                D3DXMatrixRotationAxis( &mRot, ( D3DXVECTOR3* )&vNormal, fTheta );
                for ( int i = 0; i < 4; ++i )
                {
                    D3DXVec3Subtract( ( D3DXVECTOR3* )&vertex[i].p, ( D3DXVECTOR3* )&vertex[i].p, ( D3DXVECTOR3* )&c );
                    D3DXVec3TransformCoord( ( D3DXVECTOR3* )&vertex[i].p, ( D3DXVECTOR3* )&vertex[i].p, &mRot );
                    D3DXVec3Add( ( D3DXVECTOR3* )&vertex[i].p, ( D3DXVECTOR3* )&vertex[i].p, ( D3DXVECTOR3* )&c );
                }
            }
        }
	}
	else if( setting.dwPart == MEX2_PARTICLE_EMITTER_TAIL )
	{
		// view的反方向
		Vector vAntiView = *(Vector*)&GetMe3dConfig()->GetCamera()->GetViewDir();
		D3DXVec3Scale((D3DXVECTOR3*)&vAntiView, (D3DXVECTOR3*)&vAntiView, -1);

		Vector vRight;
		D3DXVec3Cross( (D3DXVECTOR3*)&vRight, (D3DXVECTOR3*)&vAntiView, (D3DXVECTOR3*)&pParticle->vDir );
		D3DXVec3Normalize( (D3DXVECTOR3*)&vRight, (D3DXVECTOR3*)&vRight );
		//MeMatrix m;
		//BuildMatrixFromVectorToVector( (float*)&vPlaneViewRight, (float*)&vRight, (float*)&m );

		Vector up;
		Vector right;
		if( setting.dwFlag & MEX2_PARTICLE_EMITTER_TANGENT)
			D3DXVec3Scale((D3DXVECTOR3*)&up, (D3DXVECTOR3*)&pParticle->vDynamicPos, pParticle->fTailLength * m_fScale );
		else
			D3DXVec3Scale((D3DXVECTOR3*)&up, (D3DXVECTOR3*)&pParticle->vDir, pParticle->fTailLength * m_fScale );
		D3DXVec3Scale((D3DXVECTOR3*)&right, (D3DXVECTOR3*)&vRight, pParticle->fScale*0.5f*m_fScale);


        // UV计算BUG    modified by zhuomeng.hu		[3/10/2011]
        int row = pParticle->nCellId / setting.nRow % setting.nCol;
        int col = pParticle->nCellId % setting.nRow;

		D3DXVec3Subtract((D3DXVECTOR3*)&vertex[0].p, (D3DXVECTOR3*)&c, (D3DXVECTOR3*)&right);
		D3DXVec3Subtract((D3DXVECTOR3*)&vertex[0].p, (D3DXVECTOR3*)&vertex[0].p, (D3DXVECTOR3*)&up);
		//vertex[0].color = dwParticleColor;
		vertex[0].u = du*col;
		vertex[0].v = dv*row+dv;
// 		vertex[0].t = pParticle->fLerpT;
// 		vertex[0].c = pParticle->cSegmentColorIndex;

		D3DXVec3Subtract((D3DXVECTOR3*)&vertex[1].p, (D3DXVECTOR3*)&c, (D3DXVECTOR3*)&right);
		//vertex[1].color = dwParticleColor;
		vertex[1].u = du*col;
		vertex[1].v = dv*row;
// 		vertex[1].t = pParticle->fLerpT;
// 		vertex[1].c = pParticle->cSegmentColorIndex;


		D3DXVec3Add((D3DXVECTOR3*)&vertex[2].p, (D3DXVECTOR3*)&c, (D3DXVECTOR3*)&right);
		D3DXVec3Subtract((D3DXVECTOR3*)&vertex[2].p, (D3DXVECTOR3*)&vertex[2].p, (D3DXVECTOR3*)&up);
		//vertex[2].color = dwParticleColor;
		vertex[2].u = du*col+du;
		vertex[2].v = dv*row+dv;
// 		vertex[2].t = pParticle->fLerpT;
// 		vertex[2].c = pParticle->cSegmentColorIndex;


		D3DXVec3Add((D3DXVECTOR3*)&vertex[3].p, (D3DXVECTOR3*)&c, (D3DXVECTOR3*)&right);
		//vertex[3].color = dwParticleColor;
		vertex[3].u = du*col+du;
		vertex[3].v = dv*row;
// 		vertex[3].t = pParticle->fLerpT;
// 		vertex[3].c = pParticle->cSegmentColorIndex;
	}
	unguard;
}

bool Mex2ParticleEmitter::DoRender(SEmitterVertex* vertex)
{
	MeRenderObject* pkObject = ( MeRenderObject* )m_spRenderObject;			
	MeParticleRibbonRenderObject* pkPObject = dynamic_cast< MeParticleRibbonRenderObject* >( pkObject );

	if( !pkPObject )
		return false;

	float du = 1.0f/setting.nRow;
	float dv = 1.0f/setting.nCol;

	float fAlpha = pkPObject->GetAlpha();

	int nPart = 0;
	for( int i = 0; i < min( m_nNumPart, ms_nMaxPartNum ); i++ )
	{
		if( IsParticleDead( &particles[i], m_nTime ) )
			continue;

		MakeARenderParticle( &particles[i], &vertex[nPart*4], fAlpha );
		++nPart;
	}
	//assert(nPart == m_nAliveNumPart);
	return true;
}

void Mex2ParticleEmitter::Render( int nTime, short stTextureId, float fAlpha, bool bOverUI )
{
	guardfunc;

	//D3DXMATRIX matWorld;
	//D3DXMatrixIdentity( &matWorld );

	float du = 1.0f/setting.nRow;
	float dv = 1.0f/setting.nCol;

// 	if (m_pVB == NULL || m_pIB == NULL)
// 	{
// 		createBuffers();
// 	}

	DWORD dwFlag = 0;
	switch( setting.dwBlendMode )
	{
	case MEX2_BLEND:
		dwFlag |= eOpModulate1X|eAlphaBlend;
		break;
	case MEX2_ADD:
		//if( dwVersion == 1 )
		//	dwFlag |= eOpModulate1X|eAlphaBlend|eDstBlendOne;
		//else if( dwVersion >= 2 )
		//dwFlag |= eOpAdd|eAlphaBlend;
		dwFlag |= eOpModulate1X|eAlphaBlend|eDstBlendOne;
		break;
	case MEX2_MODULATE:
		dwFlag |= eOpModulate1X|eAlphaBlend|eDstBlendOne;
		break;
	case MEX2_MODULATE2X:
		dwFlag |= eOpModulate2X|eAlphaBlend|eDstBlendOne;
		break;
	case MEX2_ALPHAKEY:
		dwFlag |= eAlphaTest|eDstBlendOne;
		OutputDebugString( "MEX2_ALPHAKEY" );
		break;
	default:
		assert( false && "unknown blend mode" );
	};

// 	if (m_pVB == NULL || m_pIB == NULL)
// 	{
// 		createBuffers();
// 	}
// 
// 	static const int ParticleVertexCount = 1024*4;
// 	static SEmitterVertex vertex[ParticleVertexCount];
// 	int nParts = 0;

	//DWORD color = 0xffffffff;
	//DWORD dwAlpha = (0xffffffff&0xff000000)>>24;
	//dwAlpha = (DWORD)(dwAlpha*fAlpha);
	//if( dwAlpha > 255 )
	//	dwAlpha = 255;
	//DWORD dwRibbonColor = dwAlpha<<24|(0xffffffff&0x00ffffff);

// 	int maxParticleCount = m_nNumPart < ParticleVertexCount ? m_nNumPart : ParticleVertexCount;
// 	for( int i = 0; i < maxParticleCount; i++ )
// 	{
// 		if( IsParticleDead( &particles[i], nTime ) )
// 			continue;
// 
// 		MakeARenderParticle( &particles[i], &vertex[nParts*4], fAlpha );
// 
// 		nParts++;
// 	}

	if( bOverUI )
	{
		dwFlag |= eZDisable;
	}
	//dwFlag |= eZDisable;

	MeRenderObject* pkObject = ( MeRenderObject* )m_spRenderObject;			
	MeParticleRibbonRenderObject* pkPObject = dynamic_cast< MeParticleRibbonRenderObject* >( pkObject );
	if( pkPObject )
	{
		if( ( GetCollectibleType() != SortRenderable::eCT_Shimmer ) )		
			SetCollectibleType( SortRenderable::eCT_AlphaBlend );			
		if( MeRenderManager::Instance()->IsFreshObject( this ) )		
		{
			pkPObject->SetAlpha( fAlpha );
			pkPObject->SetOverUI( bOverUI );
			pkPObject->SetUseTexId( stTextureId );
			pkPObject->SetShaderId( MEX2_PARTICLE );
			pkPObject->SetFVF( D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1 );
			pkPObject->SetStride( sizeof( SEmitterVertex ) );
// 			pkPObject->SetVB( (BYTE*)m_pVB );
// 			pkPObject->SetIB( (BYTE*)m_pIB );
			pkPObject->SetIB( (BYTE*)Emitter::GetCWIndexBuffer() );
			pkPObject->SetFlag( dwFlag|eTwoSided|eZWriteDisable|eSortByFarZ|eLightingDisable);
			pkObject->GenerateKey();
			pkObject->SetInfo(pSrcMex->GetFilename(), setting.szName);
			MeRenderManager::Instance()->AddObject( this );
		}

	}

// 	if( nParts > 0 )
// 	{
// // 		void* destBuffers = 0;
// // 		if (m_pVB && SUCCEEDED(m_pVB->Lock(0, nParts*4*sizeof(SEmitterVertex), &destBuffers, D3DLOCK_DISCARD)))
// // 		{
// // 			memcpy_s(destBuffers, nParts*4*sizeof(SEmitterVertex), vertex, nParts*4*sizeof(SEmitterVertex));
// // 			m_pVB->Unlock();
// 
// #if 0
// 			graphics::ShaderEffect* pShaderEffect = (graphics::ShaderEffect*)graphics::ShaderManager::instance()->getShader("MexShader");
// 			ID3DXEffect* pd3dEffect = 0;
// 			if (pShaderEffect &&
// 				(pd3dEffect = pShaderEffect->getID3DXEffect()))
// 			{
// 				GetEngine()->GetRenderer()->SetGlobalTransparent(fAlpha);
// 				float particleColor[3][4] = {
// 					{
// 						setting.nSegmentColor[0][0]/255.0f,
// 							setting.nSegmentColor[0][1]/255.0f,
// 							setting.nSegmentColor[0][2]/255.0f,
// 							setting.nAlpha[0]/255.0f
// 					},
// 					{
// 						setting.nSegmentColor[1][0]/255.0f,
// 							setting.nSegmentColor[1][1]/255.0f,
// 							setting.nSegmentColor[1][2]/255.0f,
// 							setting.nAlpha[1]/255.0f
// 						},
// 						{
// 							setting.nSegmentColor[2][0]/255.0f,
// 								setting.nSegmentColor[2][1]/255.0f,
// 								setting.nSegmentColor[2][2]/255.0f,
// 								setting.nAlpha[2]/255.0f
// 						} 
// 				};
// 				pd3dEffect->SetFloatArray("particleColor", (float*)particleColor, 4*3);
// 
// 				GetEngine()->GetRenderer()->DirectPushSurface(
// 					nTextureId,
// 					-1,
// 					MEX2_PARTICLE,
// 					D3DFVF_XYZB2|D3DFVF_TEX1,
// 					sizeof(SEmitterVertex),
// 					(BYTE*)m_pVB,
// 					4*nParts,
// 					(BYTE*)m_pIB,
// 					2*nParts,
// 					dwFlag|eTwoSided|eZWriteDisable|eSortByFarZ|eLightingDisable|eUseVB|eUseIB );
// 			}
// #else
// 
// // 			bool useShader = graphics::ShaderManager::instance()->isUseShader();
// // 			graphics::ShaderVertexPixel* pShader = (graphics::ShaderVertexPixel*)
// // 				graphics::ShaderManager::instance()->getShader("MexShaderParticle");
// // 			if (pShader)
// // 			{
// // 				float particleColor[3][4] = {
// // 					{
// // 						setting.nSegmentColor[0][0]/255.0f,
// // 							setting.nSegmentColor[0][1]/255.0f,
// // 							setting.nSegmentColor[0][2]/255.0f,
// // 							setting.nAlpha[0]/255.0f
// // 					},
// // 					{
// // 						setting.nSegmentColor[1][0]/255.0f,
// // 							setting.nSegmentColor[1][1]/255.0f,
// // 							setting.nSegmentColor[1][2]/255.0f,
// // 							setting.nAlpha[1]/255.0f
// // 						},
// // 						{
// // 							setting.nSegmentColor[2][0]/255.0f,
// // 								setting.nSegmentColor[2][1]/255.0f,
// // 								setting.nSegmentColor[2][2]/255.0f,
// // 								setting.nAlpha[2]/255.0f
// // 						} 
// // 				};
// // 				pShader->setVertexProgramParameter("particleColor", (float*)particleColor, sizeof(particleColor));
// // 				pShader->setVertexProgramParameter("alpha", &fAlpha, sizeof(fAlpha));\
// // 
// // 
// // 				graphics::ShaderManager::instance()->useShader(true);
// // 			}
// // 				GetEngine()->GetRenderer()->DirectPushSurface(
// // 					stTextureId,
// // 					-1,
// // 					MEX2_PARTICLE,
// // 					D3DFVF_XYZB2|D3DFVF_TEX1,
// // 					sizeof(SEmitterVertex),
// // 					(BYTE*)m_pVB,
// // 					4*nParts,
// // 					(BYTE*)m_pIB,
// // 					2*nParts,
// // 					dwFlag|eTwoSided|eZWriteDisable|eSortByFarZ|eLightingDisable|eUseVB|eUseIB );
// // 
// // 			graphics::ShaderManager::instance()->useShader(useShader);
// 			m_fRenderAlpha = fAlpha;
// 			MeRenderObject* pkObject = ( MeRenderObject* )m_spRenderObject;			
// 			MeParticleRibbonRenderObject* pkPObject = dynamic_cast< MeParticleRibbonRenderObject* >( pkObject );
// 			if( pkPObject )
// 			{
// 				if( MeRenderManager::Instance()->AddObject( this ) )
// 				{
// 					pkPObject->SetAlpha( fAlpha );
// 					pkPObject->SetOverUI( bOverUI );
// 					pkPObject->SetUseTexId( stTextureId );
// 					pkPObject->SetShaderId( MEX2_PARTICLE );
// 					pkPObject->SetFVF( D3DFVF_XYZB2|D3DFVF_TEX1 );
// 					pkPObject->SetStride( sizeof( SEmitterVertex ) );
// 					pkPObject->SetVB( (BYTE*)m_pVB );
// 					pkPObject->SetVertexCount( 4*nParts );
// 					pkPObject->SetIB( (BYTE*)m_pIB );
// 					pkPObject->SetFaceCount( 2*nParts );
// 					pkPObject->SetFlag( dwFlag|eTwoSided|eZWriteDisable|eSortByFarZ|eLightingDisable|eUseVB|eUseIB );
// 					pkObject->GenerateKey();
// 				}
// 				
// 			}
// #endif
// 		//}
// 	}

	unguard;
}

// LPDIRECT3DVERTEXBUFFER9 Mex2ParticleEmitter::m_pVB = 0;
// LPDIRECT3DINDEXBUFFER9 Mex2ParticleEmitter::m_pIB = 0;
// bool Mex2ParticleEmitter::createBuffers()
// {
// 	destroyBuffers();
// 
// 	int faceCount = 1024;
// 
// 	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
// 	HRESULT hr = pDev->CreateVertexBuffer( faceCount*4*sizeof(SEmitterVertex), D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &m_pVB, NULL );
// 	if( FAILED(hr) )
// 		return false;

// 	hr = pDev->CreateIndexBuffer( faceCount*6*sizeof(short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB, NULL );
// 	if( FAILED(hr) )
// 	{
// 		SafeRelease(m_pVB);
// 		return false;
// 	}

// 	void* indices = 0;
// 	if (FAILED(m_pIB->Lock(0, 0, &indices, 0)))
// 	{
// 		SafeRelease(m_pVB);
// 		SafeRelease(m_pIB);
// 		return false;
// 	}
// 
// 	memcpy_s(indices, faceCount*6*sizeof(short), Emitter::GetCWIndexBuffer(), faceCount*6*sizeof(short));
// 
// 	m_pIB->Unlock();

// 	return true;
// }

// void Mex2ParticleEmitter::destroyBuffers()
// {
// 	SafeRelease(m_pVB);
// 	SafeRelease(m_pIB);
// }

/*void Mex2ParticleEmitters::Update( int nTime )
{
	//for( int i = 0; i < vectorParticleEmitter.size(); i++ )
	//	vectorParticleEmitter[i].Update( nTime );
}
void Mex2ParticleEmitters::Render( int nTime )
{
	for( int i = 0; i < vectorParticleEmitter.size(); i++ )
		vectorParticleEmitter[i].Render( nTime );
}*/

Mex2ParticleEmitterSetting2::Mex2ParticleEmitterSetting2()
{
	guardfunc;
	unguard;
}

Mex2ParticleEmitterSetting3::Mex2ParticleEmitterSetting3()
{
    fLifeSpanMax = 0.0f;
    fScaleRateMin = 1.0f;
    fScaleRateMax = 1.0f;
    bContraryColor = false;
}

const Mex2ParticleEmitterSetting3& Mex2ParticleEmitterSetting3::operator =( const Mex2ParticleEmitterSetting2& emtSetting )
{
    dwFlag = emtSetting.dwFlag;
    sprintf_s( szName, sizeof( szName ) / sizeof( char ) - 1, "%s", emtSetting.szName );
    nParentBoneId = emtSetting.nParentBoneId;
    vPivot = emtSetting.vPivot;
    nCount = emtSetting.nCount;
    fSpeed = emtSetting.fSpeed;
    fVariation = emtSetting.fVariation;
    fConeAngle = emtSetting.fConeAngle;
    fGravity = emtSetting.fGravity;
    fLifeSpan = emtSetting.fLifeSpan;
    fEmissionRate = emtSetting.fEmissionRate;
    fWidth = emtSetting.fWidth;
    fHeight = emtSetting.fHeight;
    dwBlendMode = emtSetting.dwBlendMode;
    nRow = emtSetting.nRow;
    nCol = emtSetting.nCol;
    dwPart = emtSetting.dwPart;
    fTailLength = emtSetting.fTailLength;
    fMiddleTime = emtSetting.fMiddleTime;
    dwUVAnimFps = emtSetting.dwUVAnimFps;
    nTextureId = emtSetting.nTextureId;
    nPriorityPlane = emtSetting.nPriorityPlane;
    for( int i = 0; i < 3; ++i )
    {
        for( int j = 0; j < 3; ++j )
        {
            nSegmentColor[i][j] = emtSetting.nSegmentColor[i][j];
        }
        nAlpha[i] = emtSetting.nAlpha[i];
        fParticleScaling[i] = emtSetting.fParticleScaling[i];
        dwLifeSpanHeadUVAnim[i] = emtSetting.dwLifeSpanHeadUVAnim[i];
        dwDecayHeadUVAnim[i] = emtSetting.dwDecayHeadUVAnim[i];
        dwLifeSpanTailUVAnim[i] = emtSetting.dwLifeSpanTailUVAnim[i];
        dwDecayTailUVAnim[i] = emtSetting.dwDecayTailUVAnim[i];
    }
    
    vPlaneNormal = emtSetting.vPlaneNormal;
    vPlaneXAxis = emtSetting.vPlaneXAxis;
    vPlaneYAxis = emtSetting.vPlaneYAxis;

    fLifeSpanMax = 0.0f;
    fScaleRateMin = 1.0f;
    fScaleRateMax = 1.0f;
    bContraryColor = false;
    return *this;
}

Mex2ParticleEmitterSetting4::Mex2ParticleEmitterSetting4()
{
    bAngleChangeByCone = false;
    bTailLengthChange = false;

    for( int i = 0; i < 3; ++i )
    {
        fTailLengthChange[i] = 0.0f;
    }
}

const Mex2ParticleEmitterSetting4& Mex2ParticleEmitterSetting4::operator =( const Mex2ParticleEmitterSetting3& emtSetting )
{
    dwFlag = emtSetting.dwFlag;
    sprintf_s( szName, sizeof( szName ) / sizeof( char ) - 1, "%s", emtSetting.szName );
    nParentBoneId = emtSetting.nParentBoneId;
    vPivot = emtSetting.vPivot;
    nCount = emtSetting.nCount;
    fSpeed = emtSetting.fSpeed;
    fVariation = emtSetting.fVariation;
    fConeAngle = emtSetting.fConeAngle;
    fGravity = emtSetting.fGravity;
    fLifeSpan = emtSetting.fLifeSpan;
    fEmissionRate = emtSetting.fEmissionRate;
    fWidth = emtSetting.fWidth;
    fHeight = emtSetting.fHeight;
    dwBlendMode = emtSetting.dwBlendMode;
    nRow = emtSetting.nRow;
    nCol = emtSetting.nCol;
    dwPart = emtSetting.dwPart;
    fTailLength = emtSetting.fTailLength;
    fMiddleTime = emtSetting.fMiddleTime;
    dwUVAnimFps = emtSetting.dwUVAnimFps;
    nTextureId = emtSetting.nTextureId;
    nPriorityPlane = emtSetting.nPriorityPlane;
    for( int i = 0; i < 3; ++i )
    {
        for( int j = 0; j < 3; ++j )
        {
            nSegmentColor[i][j] = emtSetting.nSegmentColor[i][j];
        }
        nAlpha[i] = emtSetting.nAlpha[i];
        fParticleScaling[i] = emtSetting.fParticleScaling[i];
        dwLifeSpanHeadUVAnim[i] = emtSetting.dwLifeSpanHeadUVAnim[i];
        dwDecayHeadUVAnim[i] = emtSetting.dwDecayHeadUVAnim[i];
        dwLifeSpanTailUVAnim[i] = emtSetting.dwLifeSpanTailUVAnim[i];
        dwDecayTailUVAnim[i] = emtSetting.dwDecayTailUVAnim[i];
    }

    vPlaneNormal = emtSetting.vPlaneNormal;
    vPlaneXAxis = emtSetting.vPlaneXAxis;
    vPlaneYAxis = emtSetting.vPlaneYAxis;

    fLifeSpanMax = emtSetting.fLifeSpanMax;
    fScaleRateMin = emtSetting.fScaleRateMin;
    fScaleRateMax = emtSetting.fScaleRateMax;
    bContraryColor = emtSetting.bContraryColor;

    bAngleChangeByCone = false;
    bTailLengthChange = false;
    for( int i = 0; i < 3; ++i )
    {
        fTailLengthChange[i] = 0.0f;
    }
    return *this;
}

void CEffectRenderable::DoRender( bool bPost )
{
	static const int ParticleVertexCount = 1024*4;
	static SEmitterVertex vertex[ParticleVertexCount];
	if (GetTotalVerticesCount(bPost) <= 0 || GetTotalVerticesCount(bPost) > 1024*4)
	{
// 		assert(0);
		return;
	}
	DoRender(vertex);
	MeRenderObject* pkObject = ( MeRenderObject* )m_spRenderObject;			
	MeParticleRibbonRenderObject* pkPObject = dynamic_cast< MeParticleRibbonRenderObject* >( pkObject );
	pkPObject->SetVB((BYTE*)vertex);
	pkObject->SetFaceCount(GetTotalFacesCount(bPost));
	pkObject->SetVertexCount(GetTotalVerticesCount(bPost));
	m_spRenderObject->DoRender();
}

float CEffectRenderable::GetDisToCameraEye( float* pMatrices )
{

	D3DXVECTOR3 vDis = m_vCenter - GetMe3dConfig()->GetCamera()->GetEyePt();

	// modified [8/27/2010 zhangjiayi]
	// D3DXVec3LengthSq取代D3DXVec3Length
	return D3DXVec3LengthSq(&vDis);

}