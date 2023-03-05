#include "Me3d/Me3d.h"
#include "Me3d/Model/MexSkinMesh.h"
#include "Me3d/Engine/Engine.h"
#include "FuncPerformanceLog.h"
//#include "Constants.h"
#include <assert.h>
#include "Me3d/ShaderMgr.h"
#if 0
//Skin Mesh Setting
void SkinMeshParam( LPDIRECT3DDEVICE9 pd3dDevice, D3DLIGHT9 *lgtSun, MeCamera *MeCamera, float fAlpha )
{
	guardfunc;

	if( GetMe3dConfig()->m_bUseSkinMesh )
	{
		if( !GetShaderMgr() )
		{
			GetMe3dConfig()->m_bUseSkinMesh = 0;
			return;
		}

		if( !GetShaderMgr()->m_pWorldEffect )
		{
			GetMe3dConfig()->m_bUseSkinMesh = 0;
			return;
		}

		D3DXMATRIX worldViewProjMat, worldMat;
		D3DXMatrixIdentity(&worldMat);
		D3DXMatrixIdentity(&worldViewProjMat);
		D3DXMatrixMultiply(&worldViewProjMat, &worldMat, &MeCamera->GetViewMatrix());
		D3DXMatrixMultiply(&worldViewProjMat, &worldViewProjMat, &MeCamera->GetProjMatrix());
		//D3DXMatrixTranspose(&worldViewProjMat, &worldViewProjMat);

		//pd3dDevice->SetVertexShaderConstant(CV_WORLDVIEWPROJ_0, &worldViewProjMat, 4);
		GetShaderMgr()->m_pWorldEffect->SetMatrix(GetShaderMgr()->m_hWorldViewPro, &worldViewProjMat);

		D3DXVECTOR4 vLight = (-1)*lgtSun->Direction;
		D3DXVECTOR4* vDiffuse = (D3DXVECTOR4*)&lgtSun->Diffuse;
		D3DXVECTOR4* vAmbient = (D3DXVECTOR4*)&lgtSun->Ambient;

		GetShaderMgr()->m_pWorldEffect->SetVector(GetShaderMgr()->m_hLightDir, &vLight);
		GetShaderMgr()->m_pWorldEffect->SetVector(GetShaderMgr()->m_hMaterialDiffuse, vDiffuse);
		GetShaderMgr()->m_pWorldEffect->SetVector(GetShaderMgr()->m_hMaterialAmbient, vAmbient);
		GetShaderMgr()->m_pWorldEffect->SetFloat(GetShaderMgr()->m_hMaterialAlpha, fAlpha);

		//pd3dDevice->SetVertexShaderConstant(CV_LIGHT_DIRECTION, (D3DVECTOR*)(&vLight), 1 );
		//pd3dDevice->SetVertexShaderConstant(CV_LIGHT_DIFFUSE,&vDiffuse, 1 );
		//pd3dDevice->SetVertexShaderConstant(CV_LIGHT_AMBIENT,&vAmbient, 1 );
	}
	return ;
	unguard;
}

MexSkinMesh::MexSkinMesh(void):
m_pVB(NULL),
m_pIB(NULL),
m_pVertices(NULL),
m_pIndices(NULL),
m_nNumVert(0),
m_nNumFace(0)
{
	guardfunc;
	unguard;
}

MexSkinMesh::~MexSkinMesh(void)
{
	guardfunc;
	assert( m_pIB == NULL );
	assert( m_pVB == NULL );
	unguard;	
}
void MexSkinMesh::Destroy()
{
	guardfunc;
	if( m_pVB )
	{
		m_pVB->Release();
		m_pVB = NULL;
	}
	if( m_pIB )
	{
		m_pIB->Release();
		m_pIB = NULL;
	}
	if( m_pVertices )
	{
		delete[] m_pVertices;
		m_pVertices = NULL;
	}
	if( m_pIndices )
	{
		delete[] m_pIndices;
		m_pIndices = NULL;
	}
	//m_AnimCtrl.Destroy();
	unguard;
}
BOOL MexSkinMesh::CreateVBIB( LPDIRECT3DDEVICE9 pDev, DWORD dwFlag )
{
	if( m_nNumFace == 0 ||
		m_nNumVert == 0 )
	{
		return FALSE;
	}
	pDev->CreateIndexBuffer( 
		m_nNumFace*3*sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, 
		D3DPOOL_MANAGED,
		&m_pIB, NULL );
	WORD* pwIBFace = NULL;
	m_pIB->Lock( 0, 0, (void**)&pwIBFace, 0 );
	memcpy( pwIBFace, m_pIndices, m_nNumFace*sizeof(WORD)*3 );
	m_pIB->Unlock();


	PSVertex* pVBVertex = NULL;
	pDev->CreateVertexBuffer( 
		sizeof(PSVertex)*m_nNumVert,
		D3DUSAGE_WRITEONLY, 
		0, 
		D3DPOOL_MANAGED, 
		&m_pVB, NULL );
	m_pVB->Lock(0, 0, (void**)&pVBVertex, 0);
	memcpy( pVBVertex, m_pVertices, sizeof(PSVertex)*m_nNumVert );
	for( int nVert = 0; nVert < m_nNumVert; nVert++ )
	{
		//pVBVertex[nVert].Normal = pVBVertex[nVert].Normal+pVBVertex[nVert].Position;
	}
	m_pVB->Unlock();
	return TRUE;
}
BOOL MexSkinMesh::CreateBoneCombination( IMex* pMex, CBoneCombination* bc )
{
	guardfunc;
	// 对每一个chunk进行运算
	for( int i = 0; i < pMex->GetGeometry()->GetChunkCount(); i++ )
	{
		IRenderable* pChunk = pMex->GetGeometry()->GetChunk(i);
		// 得到这个chunk中的面索引
		WORD* pFace = (WORD*)pChunk->GetIndicesLocked();
		// 得到这个chunk中的骨骼组列表
		BYTE* pbyBGIndices = pChunk->GetBoneGroupIndices();
		// 得到这个mex的骨骼组列表
		IMexBoneGroups* pBGs = pMex->GetBoneGroups();
		// 对每一个面进行运算
		for( int nFace = 0; nFace < pChunk->GetFaceCount(); nFace++, pFace += 3 )
		{
			CBoneCombination::Face face;
			// 每个面先记住自己的chunk
			face.nChunkID = i;
			for( int f = 0; f < 3; f++ )
			{
				int nVertID = pFace[f];
				// 每个面的3个顶点数据赋值
				face.nVertexID[f] = nVertID;

				// 得到这个顶点的骨骼影响
				int nBGID = pbyBGIndices[nVertID];
				IMexBoneGroup* pBG = pBGs->GetBoneGroup(nBGID);				
				if( !pBG )
					continue;
				if( nBGID == -1 )
				{
					assert( false );
				}
				// 把影响该顶点的骨骼列表加入到面的骨骼列表中
				for( int nBone = 0; nBone < pBG->GetBoneCount(); nBone++ )
					face.AddBone( pBG->GetBoneID(nBone) );
			}
			// 把该面加入，并更新骨骼组
			bc->AddFace( &face );
		}
	}
	return TRUE;
	unguard;
}
MexSkinMesh::Subset* MexSkinMesh::GetSubset( int i )
{
	guardfunc;
	if( i < 0 || i > m_vectorSubset.size() )
		return NULL;
	return &m_vectorSubset[i];
	unguard;
}
BOOL MexSkinMesh::ConvertToIndexedBlendedMesh( LPDIRECT3DDEVICE9 pDev, IMex* pMex )
{
	guardfunc;
	//IMex* pMex = m_AnimCtrl.GetMex();
	DWORD dwTime = HQ_TimeGetTime();
	if( !pMex )
		return FALSE;
	IMexGeometry* pGeom = pMex->GetGeometry();
	if( !pGeom )
		return FALSE;

	int nChunkCount = pGeom->GetChunkCount();
	int nFaceCount = pMex->GetFaceCount();
	int nMexVertexCount = pMex->GetVertexCount();
	std::vector<PSVertex> vectorVertex;

	// 创建一个ib，放入所有的索引

	m_pIndices = MeDefaultNew WORD[nFaceCount*3];
	WORD* pwIBFace = m_pIndices;

	// 根据整个mex，产生骨骼分组
	CBoneCombination* bc = &m_BoneCombination;
	// 生成骨骼集合
	CreateBoneCombination( pMex, bc );

	// 生成块
	bc->GenBlocks( pGeom->GetChunkCount(), &bc->m_vectorChunk );

	int nVertexOffset = 0;
	int nFaceOffset = 0;
	for( int nChunk = 0; nChunk < bc->m_vectorChunk.size(); nChunk++ )
	{
		Subset subset;
		CBoneCombination::Chunk* pChunk = &bc->m_vectorChunk[nChunk];
		std::vector<BOOL> vectorFlag;

		IRenderable* pGeomChunk = pGeom->GetChunk(nChunk);
		int nChunkVertexCount = pGeomChunk->GetVertexCount();
		vectorFlag.reserve( nChunkVertexCount );
		vectorFlag.resize( nChunkVertexCount );
		//vectorFlag.re
		//BOOL* pBools = *((BOOL*)vectorFlag.begin());
		if( nChunkVertexCount > 0 )
			memset( &vectorFlag[0], 0x00, sizeof(BOOL)*vectorFlag.size() );

		std::vector<int> vectorRemapVertexID;
		vectorRemapVertexID.reserve( nChunkVertexCount );
		vectorRemapVertexID.resize( nChunkVertexCount );


		// 得到原始网格的数据
		BYTE* pbyBGIndices = pGeomChunk->GetBoneGroupIndices();
		IMexBoneGroups* pMexBGs = pMex->GetBoneGroups();
		D3DXVECTOR3* pVertices = (D3DXVECTOR3*)pGeomChunk->GetVerticesLocked();
		D3DXVECTOR3* pNormals = (D3DXVECTOR3*)pGeomChunk->GetNormalsLocked();
		D3DXVECTOR2* pUVs = (D3DXVECTOR2*)pGeomChunk->GetUVsLocked( 0 );


		for( int nBlock = 0; nBlock < pChunk->vectorBlock.size(); nBlock++ )
		{
			memset( &vectorFlag[0], 0x00, sizeof(BOOL)*vectorFlag.size() );
			memset( &vectorRemapVertexID[0], 0xff, sizeof(int)*vectorRemapVertexID.size() );

			// 得到block
			CBoneCombination::Block* pBlock = &pChunk->vectorBlock[nBlock];
			// 得到该block对应的bone group
			CBoneCombination::BoneGroup* pBCBoneGroup = &bc->m_vectorBoneGroup[pBlock->nBoneGroupID];
			int nBlockVertexCount = 0;
			for( int nFace = 0; nFace < pBlock->vectorFaceID.size(); nFace++, pwIBFace += 3 )
			{
				int nFaceID = pBlock->vectorFaceID[nFace];
				CBoneCombination::Face* pFace = &bc->m_vectorFace[nFaceID];

				for( int nVert = 0; nVert < 3; nVert++ )
				{
					int nVertID = pFace->nVertexID[nVert];


					if( vectorFlag[nVertID] )
					{
						// remap里面保存了原来索引的顶点的新位置
						int nRemapID = vectorRemapVertexID[nVertID];
						pwIBFace[nVert] = nRemapID;
						if( nRemapID == -1 )
						{
							assert( false );
						}
						continue;
					}
					else
					{
						pwIBFace[nVert] = vectorVertex.size();
						nBlockVertexCount++;
					}
					// 要生成一个新的顶点了，

					vectorFlag[nVertID] = TRUE;
					vectorRemapVertexID[nVertID] = pwIBFace[nVert];



					int nBGID = pbyBGIndices[nVertID];
					IMexBoneGroup* pBG = NULL;
					if( nBGID == 255 )
					{

						int k  = 0;
					}
					else
					{
						pBG = pMexBGs->GetBoneGroup( nBGID );
						if( !pBG )
						{
							assert( false );
							pBG = pMexBGs->GetBoneGroup( 0 );
						}
						if( !pBG )
						{
							continue;
						}
						assert( pBG->GetBoneCount() > 0 );
					}

					// 计算该顶点
					PSVertex p;
					p.Position = pVertices[nVertID];
					p.Normal = pNormals[nVertID];
					p.Texture = pUVs[nVertID];


					if( nBGID == 255 )
					{
						p.Index.x = 1;
						p.Index.y = p.Index.x;
						p.Index.z = p.Index.x;
						p.Index.w = p.Index.x;

						p.Weight.x = 1.0f;
						p.Weight.y = 0.0f;
						p.Weight.z = 0.0f;
						p.Weight.w = 0.0f;
						
					}


					// 计算该顶点在该bone group中的数据
					else
					{
						switch( pBG->GetBoneCount() )
						{
						case 0:
							p.Index.x = 0;
							p.Index.y = p.Index.x;
							p.Index.z = p.Index.x;
							p.Index.w = p.Index.x;

							p.Weight.x = 0.0f;
							p.Weight.y = 0.0f;
							p.Weight.z = 0.0f;
							p.Weight.w = 0.0f;
							break;
						case 1:
							p.Index.x = pBCBoneGroup->Find( pBG->GetBoneID(0) );
							p.Index.y = p.Index.x;
							p.Index.z = p.Index.x;
							p.Index.w = p.Index.x;

							p.Weight.x = 1.0f;
							p.Weight.y = 0.0f;
							p.Weight.z = 0.0f;
							p.Weight.w = 0.0f;


							break;
						case 2:
							p.Index.x = pBCBoneGroup->Find( pBG->GetBoneID(0) );
							p.Index.y = pBCBoneGroup->Find( pBG->GetBoneID(1) );
							p.Index.z = p.Index.x;
							p.Index.w = p.Index.x;

							p.Weight.x = 0.5f;
							p.Weight.y = 0.5f;
							p.Weight.z = 0.0f;
							p.Weight.w = 0.0f;

							break;
						case 3:
							p.Index.x = pBCBoneGroup->Find( pBG->GetBoneID(0) );
							p.Index.y = pBCBoneGroup->Find( pBG->GetBoneID(1) );
							p.Index.z = pBCBoneGroup->Find( pBG->GetBoneID(2) );
							p.Index.w = p.Index.z;

							p.Weight.x = 0.3333333f;
							p.Weight.y = 0.3333333f;
							p.Weight.z = 0.3333333f;
							p.Weight.w = 0.0f;

							break;
						case 4:
							p.Index.x = pBCBoneGroup->Find( pBG->GetBoneID(0) );
							p.Index.y = pBCBoneGroup->Find( pBG->GetBoneID(1) );
							p.Index.z = pBCBoneGroup->Find( pBG->GetBoneID(2) );
							p.Index.w = pBCBoneGroup->Find( pBG->GetBoneID(3) );

							p.Weight.x = 0.25f;
							p.Weight.y = 0.25f;
							p.Weight.z = 0.25f;
							p.Weight.w = 0.25f;
							break;


						default:
							p.Index.x = pBCBoneGroup->Find( pBG->GetBoneID(0) );
							p.Index.y = pBCBoneGroup->Find( pBG->GetBoneID(1) );
							p.Index.z = pBCBoneGroup->Find( pBG->GetBoneID(2) );
							p.Index.w = pBCBoneGroup->Find( pBG->GetBoneID(3) );

							p.Weight.x = 0.25f;
							p.Weight.y = 0.25f;
							p.Weight.z = 0.25f;
							p.Weight.w = 0.25f;


							break;

						}
					}

					if( p.Index.x < 0 || p.Index.y < 0 || p.Index.z < 0 || p.Index.w < 0 )
					{
						assert( false );
					}


					//p.Index.x *= 4.0f/256;
					//p.Index.y *= 4.0f/256;
					//p.Index.z *= 4.0f/256;
					//p.Index.w *= 4.0f/256;

					vectorVertex.push_back( p );
				}
			}

			
			SubsetBlock subsetblock;
			subsetblock.nFaceStart = nFaceOffset;
			subsetblock.nFaceCount = pBlock->vectorFaceID.size();
			subsetblock.nVertexStart = nVertexOffset;
			subsetblock.nVertexCount = nBlockVertexCount;
			subsetblock.nBoneGroupID = pBlock->nBoneGroupID;



			subset.vectorBlock.push_back( subsetblock );

			nFaceOffset += pBlock->vectorFaceID.size();

			nVertexOffset += nBlockVertexCount;
		}
		subset.nTextureID = -1;
		m_vectorSubset.push_back( subset );
	}

	nMexVertexCount = pMex->GetVertexCount();
	int nVBVertexCount = vectorVertex.size();
	m_nNumFace = nFaceCount;
	m_nNumVert = vectorVertex.size();

	if( m_nNumVert > 0 )
	{
		m_pVertices = MeNew PSVertex[m_nNumVert];
		memcpy( m_pVertices, &vectorVertex[0], sizeof(PSVertex)*m_nNumVert );
	}

	CreateVBIB( pDev, 0 );
	

	dwTime = HQ_TimeGetTime()-dwTime;
	return TRUE;
	unguard;
}

BOOL MexSkinMesh::Combine( MexSkinMesh** ppSkinMeshList, int nNumSkinMesh )
{
	int nNumTotalVert = 0;
	int nNumTotalFace = 0;
	for( int nMesh = 0; nMesh < nNumSkinMesh; nMesh++ )
	{
		MexSkinMesh* pMesh = ppSkinMeshList[nMesh];
		nNumTotalVert += pMesh->m_nNumVert;
		nNumTotalFace += pMesh->m_nNumFace;
	}
	m_pVertices = MeNew PSVertex[nNumTotalVert];
	m_pIndices = MeDefaultNew WORD[nNumTotalFace*3];
	
	int nVertOffset = 0;
	int nFaceOffset = 0;
	for( int nMesh = 0; nMesh < nNumSkinMesh; nMesh++ )
	{
		MexSkinMesh* pMesh = ppSkinMeshList[nMesh];
	}

	return TRUE;
}

BOOL MexSkinMesh::RenderSubset( LPDIRECT3DDEVICE9 pDev, Subset* pSubset,  float* pfMatrices, DWORD dwFlag, float fAlpha )
{
	guardfunc;
	if( pSubset == NULL )
	{
		assert( false );
		return FALSE;
	}
	if( pfMatrices == NULL )
	{
		assert( false );
		return FALSE;
	}

	IRenderer* r = GetEngine()->GetRenderer();
	r->SetStreamSource( 0, m_pVB, sizeof(PSVertex) );
	r->SetIndices( m_pIB, 0 );

	pDev->SetVertexDeclaration( GetShaderMgr()->m_pBlendDecl );
	D3DXMATRIX* pMatrices = (D3DXMATRIX*)pfMatrices;
	static D3DXMATRIXA16 matList[MAX_BONE_IN_GROUP];

	r->LightEnable( 0, FALSE );
	r->SetVertexShader(NULL);

	if( fAlpha < 1 )
		dwFlag |= eAlphaBlend;


	r->DirectPushSurface( 
		pSubset->nTextureID,
		//-1,
		-1,
		MEX2_SHADER,
		0xffffffff,
		sizeof(PSVertex),
		NULL,
		0,
		NULL,
		0,
		dwFlag|eUseVB|eNeetNotDraw|eLightingDisable );

	GetShaderMgr()->m_pWorldEffect->SetTechnique( GetShaderMgr()->m_hRenderBlend );
	for( int nBlock = 0; nBlock < pSubset->vectorBlock.size(); nBlock++ )
	{
		SubsetBlock* pBlock = &pSubset->vectorBlock[nBlock];
		
		CBoneCombination::BoneGroup* pBoneGroup = 
			&m_BoneCombination.m_vectorBoneGroup[pBlock->nBoneGroupID];

		for( int nBone = 0; nBone < pBoneGroup->vectorBoneID.size(); nBone++ )
		{
			D3DXMATRIXA16 tempMat = pMatrices[pBoneGroup->vectorBoneID[nBone]];
			matList[nBone] = tempMat;
			//fAlpha = 1.0f;
			D3DXVECTOR4 constNums(0.0f, 0.5f, 1.0f, fAlpha);
			//pDev->SetVertexShaderConstant(CV_CONSTANTS, &constNums, 1);
		}

		GetShaderMgr()->m_pWorldEffect->SetMatrixArray( GetShaderMgr()->m_hMatBlendArray, matList, pBoneGroup->vectorBoneID.size() );
		UINT cPasses;
		GetShaderMgr()->m_pWorldEffect->Begin( &cPasses, /*D3DXFX_DONOTSAVESTATE*/0 );

		for( UINT p = 0; p < cPasses; ++p )
		{
			GetShaderMgr()->m_pWorldEffect->BeginPass( p );
			pDev->DrawIndexedPrimitive( 
				D3DPT_TRIANGLELIST,
				0,
				pBlock->nVertexStart, pBlock->nVertexCount,
				pBlock->nFaceStart*3, pBlock->nFaceCount );
			GetShaderMgr()->m_pWorldEffect->EndPass();
		}
		GetShaderMgr()->m_pWorldEffect->End();
	}

	r->SetVertexShader(NULL);
	r->SetStreamSource( 0, 0, 0 );
	r->SetIndices( 0, 0 );
	r->LightEnable( 0, TRUE );

	return TRUE;
	unguard;
}
BOOL MexSkinMesh::Render( LPDIRECT3DDEVICE9 pDev, float* pfMatrices )
{
	guardfunc;

	//IRenderer* r = GetEngine()->GetRenderer();

	//r->SetStreamSource( 0, m_pVB, sizeof(PSVertex) );
	//r->SetIndices( m_pIB, 0 );

	//r->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	//r->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//r->SetRenderState(D3DRS_LIGHTING, FALSE);
	//r->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	////r->SetTexture(0, m_pBumpMapTexture);

	////L dot N
	//r->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//r->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	//r->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	//for( int i = 0; i < m_vectorSubset.size(); i++ )
	//{
	//	Subset* pSubset = &m_vectorSubset[i];
	//	ITexture *pTexture = 
	//		GetEngine()->GetTextureManager()->GetTexture( pSubset->nTextureID );
	//	if( pTexture )
	//		pDev->SetTexture( 0, (LPDIRECT3DTEXTURE9)pTexture->GetData() );
	//	else
	//		pDev->SetTexture( 0, NULL );
	//	for( int nBlock = 0; nBlock < pSubset->vectorBlock.size(); nBlock++ )
	//	{
	//		SubsetBlock* pBlock = &pSubset->vectorBlock[nBlock];
	//		//D3DXMATRIX* pMatrices = (D3DXMATRIX*)m_AnimCtrl.GetMatrices();
	//		D3DXMATRIX* pMatrices = (D3DXMATRIX*)pfMatrices;
	//		CBoneCombination::BoneGroup* pBoneGroup = 
	//			&m_BoneCombination.m_vectorBoneGroup[pBlock->nBoneGroupID];

	//		for( int nBone = 0; nBone < pBoneGroup->vectorBoneID.size(); nBone++ )
	//		{
	//			D3DXMATRIX tempMat = pMatrices[pBoneGroup->vectorBoneID[nBone]];
	//			D3DXMatrixTranspose(&tempMat, &tempMat);
	//			pDev->SetVertexShaderConstant(CV_BONESTART + (nBone * 4), &tempMat, 4);

	//			D3DXVECTOR4 constNums(0.0f, 0.5f, 1.0f, 0.5f);
	//			pDev->SetVertexShaderConstant(CV_CONSTANTS, &constNums, 1);
	//		}

	//		//pDev->DrawIndexedPrimitive( 
	//		//	D3DPT_TRIANGLELIST, 
	//		//	pBlock->nVertexStart, pBlock->nVertexCount,
	//		//	pBlock->nFaceStart*3, pBlock->nFaceCount );

	//	}
	//}
	return TRUE;
	unguard;
}
#endif