#pragma once

#include "MeRTLibs.h"
#include "Dxsdk/d3dx9.h"
#include "Me3d/Model/BoneCombination.h"
#include "Me3d/Model/MexAnimCtrl.h"
#include "Me3d/Engine/Engine.h"

class MexSkinMesh : public MeCommonAllocObj<MexSkinMesh>
{
public:
	struct PSVertex : public MeCommonAllocObj<MexSkinMesh::PSVertex>
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR3 Normal;
		D3DXVECTOR2 Texture;
		D3DXVECTOR4 Weight;
		//D3DXVECTOR4 Index;
		struct 
		{
			BYTE x, y, z, w;
		}Index;
		//DWORD		Color;
	};
	struct SubsetBlock
	{
		int nVertexStart;
		int nVertexCount;
		int nFaceStart;
		int nFaceCount;
		int nBoneGroupID;
	};
	struct Subset
	{
		int nTextureID;
		std::vector<SubsetBlock> vectorBlock;
	};

public:
	MexSkinMesh(void);
	~MexSkinMesh(void);

	void Destroy();
	//MexAnimCtrl* GetAnimCtrl(){ return &m_AnimCtrl; }

	BOOL CreateBoneCombination( IMex* pMex, CBoneCombination* bc );
	BOOL ConvertToIndexedBlendedMesh( LPDIRECT3DDEVICE9 pDev, IMex* pMex );
	BOOL Render( LPDIRECT3DDEVICE9 pDev, float* pfMatrices );
	BOOL RenderSubset( LPDIRECT3DDEVICE9 pDev, Subset* pSubset,  float* pfMatrices, DWORD dwFlag, float fAlpha );

	Subset*	GetSubset( int i );
	BOOL CreateVBIB( LPDIRECT3DDEVICE9 pDev, DWORD dwFlag );
	BOOL Combine( MexSkinMesh** ppSkinMeshList, int nNumSkinMesh );
protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9	m_pIB;
	std::vector<Subset> m_vectorSubset;
	CBoneCombination m_BoneCombination;
	int			m_nNumVert;
	int			m_nNumFace;
	PSVertex*	m_pVertices;
	WORD*		m_pIndices;
	//MexAnimCtrl m_AnimCtrl;
};


void SkinMeshParam( LPDIRECT3DDEVICE9 pd3dDevice, D3DLIGHT9 *lgtSun,MeCamera *MeCamera, float fAlpha );
