#include <windows.h>

//#include "FilePath.h"
//#include "hr3d_include.h"
#include "hr3d_mdx2candidate.h"
#include "hr3d_maxinterface.h"
#include "stdmat.h"
#include "Max.h"
#include "resource.h"
#include "istdplug.h"
#include "iparamb2.h"
#include "iparamm2.h"
#include "cs/bipexp.h"
#include "cs/Phyexp.h"
//#include "cs/bipexp.h"
//#include "cs/phyexp.h"
#include "stdmat.h"
#include "iskin.h"
#include "log.h"
#include "external/datachunkwriter.h"
#include "resource.h"
//#include "Engine/HREngine.h"
#include "external/Tga.h"

BOOL g_bExpKeyFrame = FALSE;
extern Interface* g_ip;
//////////////////////////////////////////////////////////////////////////
class CVertexNormal
{
	struct Record
	{
		DWORD dwSmoothGroup;
		Point3 vNormal;
	} ;
public:
	void	AddNormal( Point3 n, DWORD dwSmoothGroup );
	int		Find( DWORD dwSmoothGroup );
	Point3	GetNormal( DWORD dwSmoothGroup );
	void	Normalize();
protected:
	std::vector<Record> m_vectorRecord;

};

void CVertexNormal::Normalize()
{
	for( int i = 0; i < m_vectorRecord.size(); i++ )
	{
		m_vectorRecord[i].vNormal = m_vectorRecord[i].vNormal.Normalize();
	}
}

int CVertexNormal::Find( DWORD dwSmoothGroup )
{
	for( int i = 0; i < m_vectorRecord.size(); i++ )
	{
		if( dwSmoothGroup == m_vectorRecord[i].dwSmoothGroup )
			return i;
	}
	return -1;
}

void CVertexNormal::AddNormal( Point3 n, DWORD dwSmoothGroup )
{
	int nRecord = Find( dwSmoothGroup );
	if( nRecord == -1 )
	{
		Record r;
		r.dwSmoothGroup = dwSmoothGroup;
		r.vNormal = n;
		m_vectorRecord.push_back( r );
	}
	else
		m_vectorRecord[nRecord].vNormal += n;
}

Point3 CVertexNormal::GetNormal( DWORD dwSmoothGroup )
{
	int nRecord = Find( dwSmoothGroup );
	if( nRecord == -1 )
	{
		assert( false && "vertex normal get error, invalid smooth group" );
		return Point3( 0, 0, 0 );
	}
	return m_vectorRecord[nRecord].vNormal;
}

// Linked list of vertex normals
class VNormal 
{
public:
	Point3 norm;
	DWORD smooth;
	VNormal *next;
	BOOL init;
	VNormal() {smooth=0;next=NULL;init=FALSE;norm=Point3(0,0,0);}
	VNormal(Point3 &n,DWORD s) {next=NULL;init=TRUE;norm=n;smooth=s;}
	~VNormal() 
	{
		if(next)
		{
			delete next;
			next = NULL;
		}
	}
	void AddNormal(Point3 &n,DWORD s);
	Point3 &GetNormal(DWORD s);
	void Normalize();
};

// Add a normal to the list if the smoothing group bits overlap, 

// otherwise create a new vertex normal in the list
void VNormal::AddNormal(Point3 &n,DWORD s) 
{
	if (!(s&smooth) && init) 
	{
		if (next) next->AddNormal(n,s);
		else 
		{
			next = new VNormal(n,s);
		}
	} 
	else 
	{
		norm += n;
		smooth |= s;
		init = TRUE;
	}
}
// Retrieves a normal if the smoothing groups overlap or there is 
// only one in the list
Point3 &VNormal::GetNormal(DWORD s) 
{
	if (smooth&s || !next) return norm;
	else return next->GetNormal(s); 
}

// Normalize each normal in the list
void VNormal::Normalize() 
{
	VNormal *ptr = next, *prev = this;
	while (ptr) 
	{
		if (ptr->smooth&smooth) 
		{
			norm += ptr->norm;
			prev->next = ptr->next;
			delete ptr;
			ptr = prev->next;
		} 
		else 
		{
			prev = ptr;
			ptr = ptr->next;
		}
	}
	norm = ::Normalize(norm);
	if (next) next->Normalize();
}

Point3 GetNormal( Point3 v0, Point3 v1, Point3 v2 )
{
	return (v1-v0)^(v2-v1);
}

Point3 GetVertexNormal(Mesh* mesh, int faceNo, RVertex* rv, Matrix3& tm )
{
	Face* f = &mesh->faces[faceNo];
	DWORD smGroup = f->smGroup;
	int numNormals;
	Point3 vertexNormal;

	// Is normal specified
	// SPCIFIED is not currently used, but may be used in future versions.
	if (rv->rFlags & SPECIFIED_NORMAL) 
	{
		vertexNormal = rv->rn.getNormal();
	}
	// If normal is not specified it's only available if the face belongs
	// to a smoothing group
	else if ((numNormals = rv->rFlags & NORCT_MASK) && smGroup) 
	{
		// If there is only one vertex is found in the rn member.
		if (numNormals == 1) 
		{
			vertexNormal = rv->rn.getNormal();
		}
		else
		{
			// If two or more vertices are there you need to step through them
			// and find the vertex with the same smoothing group as the current face.
			// You will find multiple normals in the ern member.
			for (int i = 0; i < numNormals; i++) 
			{
				if (rv->ern[i].getSmGroup() & smGroup)
				{
					vertexNormal = rv->ern[i].getNormal();
				}
			}
		}
	}
	else
	{
		// Get the normal from the Face if no smoothing groups are there
		vertexNormal = mesh->getFaceNormal(faceNo);
		//vertexNormal = vertexNormal*tm;
		//vertexNormal = vertexNormal.Normalize();
	}
	return vertexNormal;
}

void ComputeVertexNormals(Mesh *mesh, 
						  Matrix3& tm,
						  Tab<VNormal>& vnorms, 
						  Tab<Point3>& fnorms )
{
	HR3D_MaxInterface* ip = GetMaxIP();
	ip->StartProgressInfo( "Compute Vertex Normals" );
	
	
	Face *face; 
	Point3 *verts;
	Point3 v0, v1, v2;
	face = mesh->faces; 
	verts = mesh->verts;
	Matrix3 rot = tm;
	// 得到旋转
	rot.NoTrans();
	rot.NoScale();
	
	vnorms.SetCount(mesh->getNumVerts());
	fnorms.SetCount(mesh->getNumFaces());

	int i = 0;
	// Compute face and vertex surface normals
	for (i = 0; i < mesh->getNumVerts(); i++) 
	{
		vnorms[i] = VNormal();
	}
	for (i = 0; i < mesh->getNumFaces(); i++, face++) 
	{
		// Calculate the surface normal
		if( i % 10 == 0)
			ip->SetProgressInfo( 100.0f*i/mesh->getNumFaces() );
		
		v0 = verts[face->v[0]];
		v1 = verts[face->v[1]];
		v2 = verts[face->v[2]];

		fnorms[i] = (v1-v0)^(v2-v1);
		fnorms[i] = rot*fnorms[i];
		for (int j=0; j<3; j++) 
		{  
			vnorms[face->v[j]].AddNormal(fnorms[i],face->smGroup);
		}
		fnorms[i] = Normalize(fnorms[i]);
	}
	int n = vnorms.Count();
	for (i=0; i < mesh->getNumVerts(); i++) 
	{

		vnorms[i].Normalize();
	}
	// Display the normals in the debug window of the VC++ IDE
}

HR3D_Mdx2Candidate*	g_pMdx2Candidate = NULL;

INode* HR3D_Mdx2Candidate::GetFirstBoneAncestor( INode* pNode )
{
	if( pNode == NULL ||
		pNode == GetMaxIP()->GetRootNode() )
		return NULL;
	INode* p = pNode;
	while( TRUE )
	{
		INode* pParent = p->GetParentNode();
		if( pParent == GetMaxIP()->GetRootNode() )
			break;
		if( GetMaxIP()->IsBone( pParent ) ||
			GetMaxIP()->IsBipedBone( pParent ) )
			return pParent;
		p = pParent;
	}
	return NULL;
}

int HR3D_Mdx2Candidate::FindBoneGroup( HR3D_MaxInterface::BoneGroup* infls )
{
	
	for( int i = 0; i < m_boneGroups.vectorBoneGroup.size(); i++ )
	{
		if( m_boneGroups.vectorBoneGroup[i].vectorInfl.size() != infls->vectorInfl.size() )continue;
		BOOL bFound = TRUE;
		for( int id = 0; id < m_boneGroups.vectorBoneGroup[i].vectorInfl.size(); id++ )
		{
			if( strcmp( m_boneGroups.vectorBoneGroup[i].vectorInfl[id].szBoneName, infls->vectorInfl[id].szBoneName ) != 0  )
			{
				bFound = FALSE;
				break;
			}
		}
		if( bFound )
			return i;
	}
	return -1;
}

int HR3D_Mdx2Candidate::Textures::AddTexture(Texture& t)
{
	//int nFind = FindTexture( &t );
	//if( nFind != -1)
	//	return nFind;
	int nRet = vectorTexture.size();
	vectorTexture.push_back(t);
	return nRet;
}

int HR3D_Mdx2Candidate::FindTexture( HR3D_Mdx2Candidate::Texture* pTexture )
{
	//for( int i = 0; i < m_textures.vectorTexture.size(); i++ )
	for( int i = 0; i < m_textures.GetTextureCount(); i++ )
	{
		//if( strcmp( m_textures.vectorTexture[i].szName, pTexture->szName ) == 0 )
		if( stricmp( m_textures.GetTexture(i)->szName, pTexture->szName ) == 0 )
			return i;
	}
	return -1;
}

int HR3D_Mdx2Candidate::FindMtl( HR3D_Mdx2Candidate::Material* pMtl )
{
	for( int i = 0; i < m_mtls.vectorMtl.size(); i++ )
	{
		HR3D_Mdx2Candidate::Material* pMtlSrc = &m_mtls.vectorMtl[i];
		if( pMtlSrc->vectorLayer.size() != pMtl->vectorLayer.size() )
			continue;
		if( pMtlSrc->vectorColorTrack.size() != pMtl->vectorColorTrack.size() )
			continue;
		
		BOOL bSame = TRUE;
		for( int j = 0; j < pMtlSrc->vectorColorTrack.size(); j++ )
		{
			HR3D_MaxInterface::ColorTrack* pTrackSrc = &pMtlSrc->vectorColorTrack[j];
			HR3D_MaxInterface::ColorTrack* pTrackDst = &pMtl->vectorColorTrack[j];
			if( pTrackSrc->bTiling != pTrackDst->bTiling ||
				pTrackSrc->fPlaybackRate != pTrackDst->fPlaybackRate ||
				pTrackSrc->nStartFrame != pTrackDst->nStartFrame ||
				pTrackSrc->nUTile != pTrackDst->nUTile ||
				pTrackSrc->nVTile != pTrackDst->nVTile ||
				pTrackSrc->vectorColorKey.size() != pTrackDst->vectorColorKey.size() )
			{
				bSame = FALSE;
				break;
			}
			if( pTrackSrc->vectorColorKey.size() == pTrackDst->vectorColorKey.size() )
			{
				if( memcmp( &pTrackSrc->vectorColorKey[0], 
					&pTrackDst->vectorColorKey[0], 
					sizeof( HR3D_Mdx2ColorKey )*pTrackDst->vectorColorKey.size() ) != 0 )
				{
					bSame = FALSE;
					break;
				}
			}
		}
		if( !bSame )
			continue;
		
		bSame = TRUE;
		for( int id = 0; id < pMtlSrc->vectorLayer.size(); id++ )
		{
			HR3D_Mdx2Layer* l0 = &pMtlSrc->vectorLayer[id];
			HR3D_Mdx2Layer* l1 = &pMtl->vectorLayer[id];

			if( memcmp( l0, l1, sizeof( HR3D_Mdx2Layer ) ) != 0 )
			{
				bSame = FALSE;
				break;
			}
		}
		if( bSame )
			return i;
	}
	return -1;
}

int HR3D_Mdx2Candidate::FindBone( const char* pszBoneName )
{
	for( int i = 0; i < m_skeleton.vectorBone.size(); i++ )
	{
		if( strcmp( m_skeleton.vectorBone[i].szName, pszBoneName ) == 0 )
			return i;
	}
	return -1;
}

void HR3D_Mdx2Candidate::ProjBoneGroups()
{
	for( int i = 0; i < m_boneGroups.vectorBoneGroup.size(); i++ )
	{
		HR3D_MaxInterface::BoneGroup* bg = &m_boneGroups.vectorBoneGroup[i];
		for( int j = 0; j < bg->vectorInfl.size(); j++ )
		{
			bg->vectorInfl[j].nBoneId = FindBone( bg->vectorInfl[j].szBoneName );
		}
	}
}

BOOL HR3D_Mdx2Candidate::GetSpecularFaces( GeomChunk* pChunk, std::vector<int>* pvectorFace )
{
	int nMtlID = pChunk->nMtlId;
	if( nMtlID == -1 )
		return FALSE;
	Material* pMtl = &m_mtls.vectorMtl[nMtlID];
	if( pMtl->vectorLayer.size() == 0 )
		return FALSE;
	StdMat* pStdMtl = pChunk->pStdMtl;
	if( !pStdMtl )
		return FALSE;
	char szSpecularMap[MAX_PATH];
	if( !GetMaxIP()->GetStdMtlChannelBitmapFileName( pStdMtl, ID_SP, szSpecularMap ) )
		return FALSE;
	Tga tga;
	if( !tga.LoadFromFile( szSpecularMap ) )
		return FALSE;

	int nTgaWidth = tga.GetWidth();
	int nTgaHeight = tga.GetHeight();
	DWORD* pdwARGB = tga.GetARGBBuffer();
	std::vector<int> SpecularFaces;

	for( int nFace = 0; nFace < pChunk->vectorFace.size(); nFace++ )
	{
		int nNumVertInSpecular = 0;
		for( int nVert = 0; nVert < 3; nVert++ )
		{
			int nID = pChunk->vectorFace[nFace].nMaxVertexId[nVert];
			float u = pChunk->vectorSplitVertex[nID].u;
			float v = pChunk->vectorSplitVertex[nID].v;

			DWORD pixel = pdwARGB[DWORD(v*nTgaHeight)*nTgaWidth+DWORD(u*nTgaWidth)];
			if( pixel & 0xff000000 )
				nNumVertInSpecular++;
		}
		if( nNumVertInSpecular == 3 )
			SpecularFaces.push_back( nFace );
	}

	*pvectorFace = SpecularFaces;
	tga.Destroy();
	return TRUE;
}

BOOL HR3D_Mdx2Candidate::RemapChunk( GeomChunk* pParent, GeomChunk* pChild )
{
	for( int nFace = 0; nFace < pChild->vectorFace.size(); nFace++ )
	{
		for( int nVert = 0; nVert < 3; nVert++ )
		{
			// 引用父chunk的顶点id
			int nParentVertID = pChild->vectorFace[nFace].nMaxVertexId[nVert];
			
			BOOL bFound = FALSE;
			for( int i = 0; i < pChild->vectorSplitVertex.size(); i++ )
			{
				if( pChild->vectorSplitVertex[i].nParentVertID == nParentVertID )
				{
					bFound = TRUE;
					pChild->vectorFace[nFace].nMaxVertexId[nVert] = i;
					break;
				}
			}
			if( !bFound )
			{
				SplitVertex s = pParent->vectorSplitVertex[nParentVertID];
				s.nParentVertID = nParentVertID;
				pChild->vectorFace[nFace].nMaxVertexId[nVert] = pChild->vectorSplitVertex.size();
				pChild->vectorSplitVertex.push_back( s );
			}
		}
	}
	return TRUE;
}
BOOL HR3D_Mdx2Candidate::GenSpecularChunk( GeomChunk* pChunk, 
										  GeomChunk* pNormalChunk,
										  GeomChunk* pSpecularChunk, 
										  std::vector<int>* pvectorFace )
{
	for( int nFace = 0; nFace < pChunk->vectorFace.size(); nFace++ )
	{
		BOOL bIsSpecular = FALSE;
		for( int i = 0; i < pvectorFace->size(); i++ )
		{
			if( (*pvectorFace)[i] == nFace )
			{
				bIsSpecular = TRUE;
				break;
			}
		}
		if( bIsSpecular )
			pSpecularChunk->vectorFace.push_back( pChunk->vectorFace[nFace] );
		else 
			pNormalChunk->vectorFace.push_back( pChunk->vectorFace[nFace] );
	}
	RemapChunk( pChunk, pNormalChunk );
	RemapChunk( pChunk, pSpecularChunk );

	pNormalChunk->nMtlId = pChunk->nMtlId;
	pNormalChunk->nType = pChunk->nType;
	pNormalChunk->nModifierType = pChunk->nModifierType;
	pNormalChunk->pStdMtl = pChunk->pStdMtl;
	strcpy( pNormalChunk->szNodename, pChunk->szNodename );

	pSpecularChunk->nMtlId = pChunk->nMtlId;
	pSpecularChunk->nType = pChunk->nType;
	pSpecularChunk->nModifierType = pChunk->nModifierType;
	pSpecularChunk->pStdMtl = pChunk->pStdMtl;
	strcpy( pSpecularChunk->szNodename, pChunk->szNodename );

	return TRUE;
}

bool IsBone(INode *pNode)
{
	// check for root node
	if(pNode->IsRootNode()) return false;

	// check for bone node
	ObjectState os;
	os = pNode->EvalWorldState(0);
	if(os.obj->ClassID() == Class_ID(BONE_CLASS_ID, 0)) return true;

#if MAX_RELEASE >= 4000
	if(os.obj->ClassID() == BONE_OBJ_CLASSID) return true;
#endif

	if(os.obj->ClassID() == Class_ID(DUMMY_CLASS_ID, 0)) return false;

	// check for biped node
	Control *pControl;
	pControl = pNode->GetTMController();
	if((pControl->ClassID() == BIPSLAVE_CONTROL_CLASS_ID) || (pControl->ClassID() == BIPBODY_CONTROL_CLASS_ID)) return true;

	return false;
}

void HR3D_Mdx2Candidate::CreateGeometry( INode* pNode )
{
	HR3D_MaxInterface* ip = GetMaxIP();
	ip->StartProgressInfo( "Create Geometry" );
	
	if( !pNode )return;
	if( !GetMaxIP()->IsMesh( pNode ) )return;
	if( !GetMaxIP()->IsRenderable( pNode ) )return;
	if( GetMaxIP()->IsBone( pNode ) )return;
	if( GetMaxIP()->IsDummy( pNode ) )return;
	Mesh* mesh = GetMaxIP()->GetMesh( pNode );
	if( !mesh )
		return;

	// 判断是否为镜像物体
	Matrix3 matrix = pNode->GetObjTMAfterWSM ( 0 );
	BOOL bMirror = DotProd ( CrossProd ( matrix.GetRow ( 0 ), matrix.GetRow ( 1 ) ), matrix.GetRow ( 2 ) ) < 0.0 ? TRUE : FALSE;

	mesh->buildNormals();
	mesh->buildRenderNormals();
	Matrix3	matTrans = matrix;
	Modifier* pModifier = GetMaxIP()->FindModifier( pNode, Class_ID(PHYSIQUE_CLASS_ID_A, PHYSIQUE_CLASS_ID_B) );
	int nModifierType;
	if(	pModifier )
		nModifierType	= MODIFIER_PHYSIQUE;
	else
	{
		pModifier = GetMaxIP()->FindModifier(	pNode, SKIN_CLASSID	);
		if(	pModifier )
			nModifierType = MODIFIER_SKIN;
		else
			nModifierType = MODIFIER_NONE;
	}

	Mtl* pMtl = pNode->GetMtl();

	std::vector<StdMat*> vectorStdMtl;
	ip->StartProgressInfo( "Get Mtl" );
	if( pMtl )
	{
		if( pMtl->IsMultiMtl() )
		{
			for( int i = 0; i < pMtl->NumSubMtls(); i++ )
			{
				Mtl* pSubMtl = pMtl->GetSubMtl( i );
				StdMat* pStdMtl = (StdMat*)pSubMtl;
				if( pStdMtl == NULL )
					return;
				vectorStdMtl.push_back( pStdMtl );
			}
		}
		else
		{
			StdMat* pStdMtl = (StdMat*)pMtl;
			vectorStdMtl.push_back( pStdMtl );
		}
	}
	
	int nStdMtlCount = vectorStdMtl.size();
	std::vector<GeomChunk> chunks;
	if( nStdMtlCount > 0 )
	{
		chunks.reserve( nStdMtlCount );
		chunks.resize( nStdMtlCount );
		for( int i = 0; i < chunks.size(); i++ )
		{
			strcpy( chunks[i].szNodename, pNode->GetName() );
			chunks[i].pStdMtl = vectorStdMtl[i];
		}
	}
	else
	{
		chunks.reserve( 1 );
		chunks.resize( 1 );
		strcpy( chunks[0].szNodename, pNode->GetName() );
		if( strnicmp( "floor", pNode->GetName(), 5 ) == 0 )
			chunks[0].nType = HR3D_Mdx2GeoChunkProperty::eFloor;
		if( strnicmp( "coli", pNode->GetName(), 4 ) == 0 )
			chunks[0].nType = HR3D_Mdx2GeoChunkProperty::eCollision;
		//if( strnicmp( "waypoint", pNode->GetName(), 8 ) == 0 )
		//	chunks[0].nType = HR3D_Mdx2GeoChunkProperty::eWayPoint;
	}

	BOOL bHasNoneMtlFaces = FALSE;
	for( int nStdMtlId = 0; nStdMtlId < vectorStdMtl.size(); nStdMtlId++ )
	{
		StdMat* pStdMtl = vectorStdMtl[nStdMtlId];

		if( pStdMtl )
		{
			// realrender added 2003.12.09
			HR3D_MaxInterface::ColorTrack colorTrack;
			GetMaxIP()->GetMtlAnim( pStdMtl, colorTrack );

			BOOL bDiffuseMap = FALSE;
			BOOL bTransMap = FALSE;
			BOOL bSpecularMap = FALSE;
			BOOL bFilterMap = FALSE;

			char szDiffuseMap[MAX_PATH] = "";
			char szTransMap[MAX_PATH] = "";
			char szSpecularMap[MAX_PATH] = "";
			char szFilterColorMap[MAX_PATH] = "";
			if( GetMaxIP()->GetStdMtlChannelBitmapFileName( pStdMtl, ID_DI, szDiffuseMap ) )
			{
				bDiffuseMap = TRUE;
			}
			if( GetMaxIP()->GetStdMtlChannelBitmapFileName( pStdMtl, ID_OP, szTransMap ) )
			{
				bTransMap = TRUE;
			}
			if( GetMaxIP()->GetStdMtlChannelBitmapFileName( pStdMtl, ID_FI, szFilterColorMap ) )
			{
				bFilterMap = TRUE;
			}
			if( GetMaxIP()->GetStdMtlChannelBitmapFileName( pStdMtl, ID_SP, szSpecularMap ) )
			{
				bSpecularMap = TRUE;
			}

			Texture texture;
			if( bDiffuseMap )
				strcpy( texture.szName, szDiffuseMap );
			else if( bTransMap )
				strcpy( texture.szName, szTransMap );
			else
			{
				bHasNoneMtlFaces = TRUE;
				chunks[nStdMtlId].bHasNoneMtlFaces = TRUE;
			}

			int nTextureId = g_pMdx2Candidate->FindTexture( &texture );
			if( nTextureId == -1 )
			{
				nTextureId = g_pMdx2Candidate->m_textures.AddTexture(texture);
			}

			HR3D_Mdx2Layer layer;
			DWORD dwFlag = 0;

			if( pStdMtl->GetTwoSided() )
				dwFlag |= HR3D_MDX2_TWOSIDED;

			if( pStdMtl->GetWire() )
				dwFlag |= HR3D_MDX2_ZWRITEENABLE;

			if( bTransMap && bDiffuseMap && bFilterMap)
			{
				if( (0==stricmp( szDiffuseMap, szTransMap )) && (0==stricmp( szDiffuseMap, szFilterColorMap )) )
				{
					dwFlag |= HR3D_MDX2_ALPHABLEND;
					dwFlag |= HR3D_MDX2_TWOSIDED;
					dwFlag |=HR3D_MDX2_MODULATE2X;
				}
			}
			else
			{
				if( bDiffuseMap && bTransMap)
				{
					if( 0==stricmp( szDiffuseMap, szTransMap ) )
					{
						dwFlag |= HR3D_MDX2_ALPHATEST;
					}
				}
			}

			if( bSpecularMap )
			{
				dwFlag |= HR3D_MDX2_SPECULARENABLE;
			}
			layer.SetFlag( dwFlag );
			layer.SetAlpha( 1.0f );
			layer.SetBlendMode( eNormalTexture );
			layer.SetTextureID( nTextureId );

			Material mtl;
			mtl.vectorLayer.push_back( layer );
			mtl.vectorColorTrack.push_back( colorTrack );

			int nMtlId = g_pMdx2Candidate->FindMtl( &mtl );
			if( nMtlId == -1 )
			{
				nMtlId = g_pMdx2Candidate->m_mtls.vectorMtl.size();
				g_pMdx2Candidate->m_mtls.vectorMtl.push_back( mtl );
			}
			chunks[nStdMtlId].nMtlId = nMtlId;
		}
		else
			chunks[nStdMtlId].nMtlId = -1;
		
		chunks[nStdMtlId].nModifierType = nModifierType;
		const char* pszNodeName = pNode->GetName();
		// 是否是billboard
		if ( strnicmp( "bbrd", pszNodeName, 4 ) == 0 )
		{
			chunks[nStdMtlId].nType = HR3D_Mdx2GeoChunkProperty::eBillboard;
			if ( strnicmp( "bbrd.", pszNodeName, 5 ) == 0 )
			{
				chunks[nStdMtlId].dwFlag |= Mex2BbrdFlag_AlwayseLookAtCamera;
			}
			if ( strnicmp( "bbrd2", pszNodeName, 5 ) == 0 )
			{
				chunks[nStdMtlId].dwFlag |= Mex2BbrdFlag_AlwayseStand;
			}
			if ( strnicmp( "bbrdv", pszNodeName, 5 ) == 0 )
			{
				chunks[nStdMtlId].dwFlag |= Mex2BbrdFlag_VerticalGround;
			}
			if ( strnicmp( "bbrde", pszNodeName, 5 ) == 0 )
			{
				chunks[nStdMtlId].dwFlag |= Mex2BbrdFlag_AlwayseStand_ForEffect;
			}
		}
		else if( strnicmp( "laser", pszNodeName, 5 ) == 0 )
			chunks[nStdMtlId].nType = HR3D_Mdx2GeoChunkProperty::eLaser;
		// realrender added 2004.08.05
		else if( strnicmp( "decal", pszNodeName, 5 ) == 0 )
			chunks[nStdMtlId].nType = HR3D_Mdx2GeoChunkProperty::eDecal;
		// realrender added 2004.09.13
		else if( strnicmp( "floor", pszNodeName, 5 ) == 0 )
			chunks[nStdMtlId].nType = HR3D_Mdx2GeoChunkProperty::eFloor;
		else if( strnicmp( "coli", pszNodeName, 4 ) == 0 )
			chunks[nStdMtlId].nType = HR3D_Mdx2GeoChunkProperty::eCollision;
		//else if( strnicmp( "waypoint", pNode->GetName(), 8 ) == 0 )
		//	chunks[0].nType = HR3D_Mdx2GeoChunkProperty::eWayPoint;
		else
		{
			BOOL bIsBillboard = FALSE;
			int nLen = strlen( pszNodeName );
			if( nLen > 4 )
			{
				if( strnicmp( "bbrd", &pszNodeName[nLen-4], 4 ) == 0 )
					bIsBillboard = TRUE;
			}
			if( bIsBillboard)
				chunks[nStdMtlId].nType = HR3D_Mdx2GeoChunkProperty::eBillboard;
			else
				chunks[nStdMtlId].nType = HR3D_Mdx2GeoChunkProperty::eStatic;
		}
	}
	
	Tab<VNormal> vnorms;
	Tab<Point3> fnorms;
	ComputeVertexNormals( mesh, matTrans, vnorms, fnorms );

	ip->StartProgressInfo( "Get Mesh" );
	for( int nFaceId = 0; nFaceId < mesh->numFaces; nFaceId++ )
	{
		if( nFaceId % 10 == 0 )
			ip->SetProgressInfo( 100.0f*nFaceId/mesh->numFaces );
		
		MtlFace face;
		GeomChunk* pChunk = NULL;
		if( nStdMtlCount > 0 )
		{
			// mtl id从1开始???
			int nStdMtlId = mesh->getFaceMtlIndex( nFaceId );
			if( nStdMtlCount > 0 )
			{
				nStdMtlId %= nStdMtlCount;
			}
			pChunk = &chunks[nStdMtlId];
		}
		else
		{
			pChunk = &chunks[0];
		}
		for( int nVertexId = 0; nVertexId < 3; nVertexId++ )
		{
			float u = 0.0f;
			float v = 0.0f;
			if( mesh->tvFace )
			{
				int nOffset = mesh->tvFace[nFaceId].t[nVertexId];
				u = mesh->tVerts[nOffset].x;
				v = 1-mesh->tVerts[nOffset].y;
			}
			int nOldVertexId = mesh->faces[nFaceId].getVert(nVertexId);
			Point3 normal = vnorms[nOldVertexId].GetNormal( mesh->faces[nFaceId].smGroup );
			//Point3 normal = ip->GetVertexNormal( mesh, nFaceId, nVertexId );

			DWORD dwColor = 0xffffffff;
			//Modifier *modifier = ip->FindVertexModifier(pNode);
			//IVertexPaint *ivp = (IVertexPaint*) modifier->GetInterface(IVERTEXPAINT_INTERFACE_ID);				
			if( mesh->vertCol)
			{
				int k = mesh->getNumVertCol();
				int nVCVertexID = mesh->vcFace[nFaceId].t[nVertexId];
				VertColor color = mesh->vertCol[nVCVertexID];
				DWORD r = ((DWORD)(color.x*255));
				DWORD g = ((DWORD)(color.y*255));
				DWORD b = ((DWORD)(color.z*255));
				dwColor = 0xff000000 | r<<16 | g<<8 | b;
			}
			else if( mesh->vertColArray )
			{
				int k = mesh->getNumVertCol();
				int nVCVertexID = mesh->vcFaceData[nFaceId].t[nVertexId];
				VertColor color = mesh->vertColArray[nVCVertexID];
				DWORD r = ((DWORD)(color.x*255));
				DWORD g = ((DWORD)(color.y*255));
				DWORD b = ((DWORD)(color.z*255));
				dwColor = 0xff000000 | r<<16 | g<<8 | b;
			}
	
			bool found = false;
			for( int i = 0; i < pChunk->vectorSplitVertex.size(); i++ )
			{
				if( nOldVertexId == pChunk->vectorSplitVertex[i].nVertexId &&
					dwColor == pChunk->vectorSplitVertex[i].color &&
					FloatCmp( u, pChunk->vectorSplitVertex[i].u ) == 0 &&
					FloatCmp( v, pChunk->vectorSplitVertex[i].v ) == 0 &&
					FloatCmp( normal.x, pChunk->vectorSplitVertex[i].normal.x ) == 0 && 
					FloatCmp( normal.y, pChunk->vectorSplitVertex[i].normal.y ) == 0 && 
					FloatCmp( normal.z, pChunk->vectorSplitVertex[i].normal.z ) == 0 )
				{
					found = true;
					face.nMaxVertexId[nVertexId] = i;
					break;
				}
			}
			if( !found )
			{
				// 新的索引
				face.nMaxVertexId[nVertexId] = pChunk->vectorSplitVertex.size();
				// 加入新的顶点
				SplitVertex s;
				s.nVertexId = nOldVertexId;
				s.pos = mesh->getVert( nOldVertexId )*matTrans;			
				s.normal = normal;

				s.color = dwColor;
				s.u = u;
				s.v = v;
				pChunk->vectorSplitVertex.push_back(s);
			}
		}
		if( bMirror )
		{
			int temp = face.nMaxVertexId[0];
			face.nMaxVertexId[0] = face.nMaxVertexId[1];
			face.nMaxVertexId[1] = temp;
		}
		pChunk->vectorFace.push_back( face );
	}
	std::vector<GeomChunk> SpecularChunks;
	for( int nChunkId = 0; nChunkId < chunks.size(); nChunkId++ )
	{
		GeomChunk* pChunk = &chunks[nChunkId];
		std::vector<int> SpecularFaces;
		if( !GetSpecularFaces( pChunk, &SpecularFaces ) )
			continue;
		GeomChunk NormalChunk, SpecularChunk;
		GenSpecularChunk( pChunk, &NormalChunk, &SpecularChunk, &SpecularFaces );
		if( SpecularFaces.size() == 0 )
			continue;
		*pChunk = NormalChunk; 
		SpecularChunks.push_back( SpecularChunk );
	}
	for( int nChunkId = 0; nChunkId < SpecularChunks.size(); nChunkId++ )
		chunks.push_back( SpecularChunks[nChunkId] );
	BOOL bAlertOnce = FALSE;
	ip->StartProgressInfo( "Build Chunk" );
	
	for( int nChunkId = 0; nChunkId < chunks.size(); nChunkId++ )
	{
		GeomChunk* pChunk = &chunks[nChunkId];
		// realrender added 2004.02.07 for debug
		for( int i = 0; i < pChunk->vectorFace.size(); i++ )
		{
			MtlFace* face = &pChunk->vectorFace[i];
			if( face->nMaxVertexId[0] > pChunk->vectorSplitVertex.size() ||
				face->nMaxVertexId[1] > pChunk->vectorSplitVertex.size() ||
				face->nMaxVertexId[2] > pChunk->vectorSplitVertex.size() )
			{
				assert( false && "chunk error, face index > vertex count" );
			}
		}

		BOOL bAllVertexCountIsWhite = TRUE;
		ip->StartProgressInfo( "Process Split Vertex" );
		int nSplitVertexCount = pChunk->vectorSplitVertex.size();

		pChunk->vectorVertex.reserve( nSplitVertexCount );
		pChunk->vectorVertex.resize( nSplitVertexCount );

		pChunk->vectorNormal.reserve( nSplitVertexCount );
		pChunk->vectorNormal.resize( nSplitVertexCount );

		pChunk->vectorColor.reserve( nSplitVertexCount );
		pChunk->vectorColor.resize( nSplitVertexCount );

		/* 多重纹理坐标, 4层UV坐标 [wangshuai 2012-5-17] */
		pChunk->m_shUVLayerCount = 2;
		pChunk->m_shLightmapLayer = 1;
		for (int layer = 0; layer < GeomChunk::eMaxUVLayer; ++layer)
		{
			if (layer < pChunk->m_shUVLayerCount)
				pChunk->m_pUVs[layer] = new HR3D_Vector2[nSplitVertexCount];
			else
				pChunk->m_pUVs[layer] = NULL;
		}

		pChunk->vectorBGId.reserve( nSplitVertexCount );
		pChunk->vectorBGId.resize( nSplitVertexCount );
		for (int i = 0; i < pChunk->vectorSplitVertex.size(); i++)
		{
			char s[256];
			sprintf( s, "Process Split Vertex %ld", i );
			if( i % 10 == 0 )
			{
				ip->StartProgressInfo( s );
				ip->SetProgressInfo( 100.0f*i/pChunk->vectorSplitVertex.size() );
			}

			pChunk->vectorVertex[i] = pChunk->vectorSplitVertex[i].pos;
			pChunk->vectorNormal[i] = pChunk->vectorSplitVertex[i].normal;
			pChunk->vectorColor[i] = pChunk->vectorSplitVertex[i].color;

			bAllVertexCountIsWhite = FALSE;

			float u = pChunk->vectorSplitVertex[i].u;
			float v = pChunk->vectorSplitVertex[i].v;
			for (int layer = 0; layer < pChunk->m_shUVLayerCount; ++layer)
				pChunk->m_pUVs[layer][i] = HR3D_Vector2(u, v);

			HR3D_MaxInterface::BoneGroup bg;
			GetMaxIP()->GetBoneGroup(  pModifier, nModifierType, pNode, mesh, pChunk->vectorSplitVertex[i].nVertexId, bg );
			if( bg.vectorInfl.size() != 0 )
			{
				int nBGId = g_pMdx2Candidate->FindBoneGroup( &bg );
				// 如果没有找到相同的bone group
				if( nBGId == -1 )
				{
					nBGId = g_pMdx2Candidate->m_boneGroups.vectorBoneGroup.size();
					g_pMdx2Candidate->m_boneGroups.vectorBoneGroup.push_back( bg );
				}
				if( nBGId >= 254 )
				{
					MessageBox( 0, "Bone Group Count > 254, this mesh skip", "warning", MB_OK );
					return;
				}
				//pChunk->vectorBGId.push_back( nBGId );
				pChunk->vectorBGId[i] = nBGId;
			}
			// 静态刚体
			else
			{

				pChunk->vectorBGId[i] = -1;
				pChunk->bHasUnEnveloppedVertices = TRUE;

			}
			// 每个split vertex保留一份骨骼影响
			pChunk->vectorSplitVertex[i].bg = bg;
		}

		switch( pChunk->nType )
		{
		case HR3D_Mdx2GeoChunkProperty::eBillboard:
			if( pChunk->vectorSplitVertex.size() % 4 != 0 )
			{
				MessageBox( NULL, "billboard's vertex count % 4 != 0", "error", MB_OK );
			}
			break;
		case HR3D_Mdx2GeoChunkProperty::eDecal:
			if( pChunk->vectorSplitVertex.size() != 4 || pChunk->vectorFace.size() != 2 )
			{
				MessageBox( NULL, "decal's vertex count != 4 or face count != 2", "error", MB_OK );
			}
			break;
		}

	}
	for( int nChunkId = 0; nChunkId < chunks.size(); nChunkId++ )
	{
		GeomChunk* pChunk = &chunks[nChunkId];
		if( pChunk->nType == HR3D_Mdx2GeoChunkProperty::eBillboard )
		{
			AddBillboard( pChunk );
		}
		else
		{
			pChunk->ptCenter = matrix.GetTrans();

			INode* pParent = pNode->GetParentNode();
			if( pParent || !IsBone( pParent ) )
				strncpy( pChunk->szParentName, pParent->GetName(), MAX_PATH );

			g_pMdx2Candidate->m_geometry.vectorChunk.push_back( *pChunk );
		}
	}
}

BOOL HR3D_Mdx2Candidate::Combine2Chunk( GeomChunk* pChunk0, GeomChunk* pChunk1 )
{
	//pChunk0->nMtlId = pChunk1->nMtlId;
//	pChunk0->nPartId = pChunk1->nPartId;
	
	int nChunk0SplitVertexCount = pChunk0->vectorSplitVertex.size();

	int i = 0;
	for( i = 0; i < pChunk1->vectorSplitVertex.size(); i++ )
		pChunk0->vectorSplitVertex.push_back( pChunk1->vectorSplitVertex[i] );

	for( i = 0; i < pChunk1->vectorFace.size(); i++ )
	{
		MtlFace face = pChunk1->vectorFace[i];
		face.nMaxVertexId[0] += nChunk0SplitVertexCount;
		face.nMaxVertexId[1] += nChunk0SplitVertexCount;
		face.nMaxVertexId[2] += nChunk0SplitVertexCount;
		pChunk0->vectorFace.push_back( face );
	}
	
	for (i = 0; i < pChunk1->vectorVertex.size(); i++)
	{
		pChunk0->vectorVertex.push_back( pChunk1->vectorVertex[i] );
		pChunk0->vectorNormal.push_back( pChunk1->vectorNormal[i] );
		
		for (int j = 0; j < pChunk1->m_shUVLayerCount; ++j)
			pChunk0->m_pUVs[j][i] = pChunk1->m_pUVs[j][i];

		pChunk0->vectorBGId.push_back( pChunk1->vectorBGId[i] );
		pChunk0->vectorColor.push_back( pChunk1->vectorColor[i] );
	}
	return TRUE;
}

void HR3D_Mdx2Candidate::CreateLight( INode* pNode )
{
	Object *obj = pNode->EvalWorldState ( 0 ).obj;
	LightObject *pLightObj = ( LightObject* )obj;
	//ObjLightDesc* pDesc = pLightObj->CreateLightDesc( pNode );

	Light light;
	light.szName[0] = 0;
	strcpy( light.szName, pNode->GetName() );
	light.dwFlag = 0;
	light.nParentBoneId = -1;
	
	light.fAttenuration[0] = 0.0f;
	light.fAttenuration[1] = 1.0f;
	light.fAttenuration[2] = 0.0f;

	GetMaxIP()->GetLightColorTrack( pNode, light.colorTrack );

	INode* pAncestor = GetFirstBoneAncestor( pNode );
	if( !pAncestor )
		return;
	strcpy( light.szParentBoneName, pAncestor->GetName() );
	//light.fRange = pLightObj->GetFallsize( 0 );
	//light.fRange = pDesc->ls.attenStart;
	light.fIntense = pLightObj->GetIntensity(0);
	//light.fRange = pLightObj->GetTDist(0);
	light.fRange = pLightObj->GetAtten( 0, LIGHT_ATTEN_END );
	//float I = pDesc->ls.intens;
	//light.fAttenuration[0] = 0.0f;

	//light.fAttenuration[1] = 0.0f;
	//light.fAttenuration[2] = 0.0f;

	Matrix3	matTrans = pNode->GetObjectTM(0);
	light.vPivot = matTrans.GetTrans();

	strcpy( light.szName, pNode->GetName() );

	m_lights.vectorLight.push_back( light );
}

void HR3D_Mdx2Candidate::CreateRibbonEmitter( INode* pNode )
{
	if( !pNode )return;
	if( !GetMaxIP()->IsMesh( pNode ) )return;
	Mesh* mesh = GetMaxIP()->GetMesh( pNode );
	if( !mesh )
		return;
	Matrix3	matTrans = pNode->GetObjectTM(0);
	if( mesh->numFaces != 12 || mesh->numVerts != 8 )
		return;

	Point3 p[8];
	for( int i = 0; i < 8; i++ )
	{
		p[i] = mesh->getVert( i )*matTrans;
	}

	//Box3 box = pNode->getBoundingBox();
	RibbonEmitter re;

	INode* pAncestor = GetFirstBoneAncestor( pNode );
	if( !pAncestor )
		return;

	re.setting.LoadFromNode( pNode );
	Texture texture;
	strcpy( texture.szName, re.setting.m_szTextureName );
	re.nTextureId = FindTexture( &texture );
	if( re.nTextureId == -1 )
	{
		//re.nTextureId = m_textures.vectorTexture.size();
		//m_textures.vectorTexture.push_back( texture );
		re.nTextureId = m_textures.AddTexture(texture);
	}

	
	strcpy( re.szParentBoneName, pAncestor->GetName() );
	re.nParentBoneId = -1;
	re.vLine[0] = ( p[0]+p[1]+p[2]+p[3] )/4;
	re.vLine[1] = ( p[4]+p[5]+p[6]+p[7] )/4;

	
	m_ribbonEmitters.vectorRibbonEmitter.push_back( re );
}

void HR3D_Mdx2Candidate::CreateParticleEmitter( INode* pNode )
{
	if( !pNode )return;
	
	ParticleEmitter pe;
	strcpy( pe.szNodeName , pNode->GetName() );

	pe.settingDlg.LoadFromNode( pNode );
	pe.vPlaneNormal = Point3(0,0,1);
	strcpy( pe.szParentBoneName, pNode->GetParentNode()->GetName() );
	Matrix3	matTrans = pNode->GetObjectTM(0);
	
	pe.vPivot = matTrans.GetTrans();

	Texture texture;
	ParticleEmitterSettingDlg::Component* c = pe.settingDlg.GetComponentById( ParticleEmitterSettingDlg::eTextureName );

	std::string tex_path(c->value.buffer);
	int pos = tex_path.rfind('\\');
	if (pos != -1)
		tex_path = tex_path.substr(pos + 1, tex_path.size() - pos);

	strcpy(texture.szName, tex_path.c_str());
	pe.nTextureId = FindTexture( &texture );
	if( pe.nTextureId == -1 )
	{
		pe.nTextureId = m_textures.AddTexture( texture );
	}

	HR3D_MaxInterface* ip = GetMaxIP();
	if( ip->IsMesh( pNode ) )
	{
		Mesh* pMesh = ip->GetMesh( pNode );
		if( pMesh )
		{
			pMesh->buildNormals();
			pMesh->buildRenderNormals();
			if (pMesh->getNumVerts() == 4 && pMesh->getNumFaces() == 2)
			{
				Point3 v0 = pMesh->getVert(0)*matTrans;
				Point3 v1 = pMesh->getVert(1)*matTrans;
				Point3 v2 = pMesh->getVert(2)*matTrans;

				pe.vPlaneNormal = (v1 - v0) ^ (v2 - v1); 
				pe.vPlaneNormal = pe.vPlaneNormal.Normalize();

				pe.vPlaneXAxis = (v1-v0)/2;
				pe.vPlaneYAxis = (v2-v0)/2;
				
				pe.settingDlg.GetComponentById( ParticleEmitterSettingDlg::eWidth )->value.f = pe.vPlaneXAxis.Length()*2;
				pe.settingDlg.GetComponentById( ParticleEmitterSettingDlg::eHeight )->value.f = pe.vPlaneYAxis.Length()*2;				
			}
		}
	}
	m_particleEmitters.vectorEmitter.push_back( pe );
}

BOOL HR3D_Mdx2Candidate::AddBillboard( GeomChunk* pChunk )
{
	// 不使用自动分组
	m_billboards.vectorChunk.push_back( *pChunk );
	return TRUE;

	//int nFoundSameMtlBillboardID = -1;
	//for( int nChunk = 0; nChunk < m_billboards.vectorChunk.size(); nChunk++ )
	//{
	//	if( m_billboards.vectorChunk[nChunk].nMtlId == pChunk->nMtlId )
	//	{
	//		nFoundSameMtlBillboardID = nChunk;
	//	}
	//}
	//// 如果没有找到材质相同的billboard，那么新建一个
	//if( nFoundSameMtlBillboardID == -1 )
	//{
	//	m_billboards.vectorChunk.push_back( *pChunk );
	//	return TRUE;
	//}
	//// 塌陷
	//if( !Combine2Chunk( &m_billboards.vectorChunk[nFoundSameMtlBillboardID], pChunk ) )
	//{
	//	assert( false );
	//	return FALSE;
	//}
	//return TRUE;
}
//void HR3D_Mdx2Candidate::CreateBillboard( INode* pNode )
//{
//	if( !pNode )return;
//	if( !GetMaxIP()->IsMesh( pNode ) )return;
//	Mesh* mesh = GetMaxIP()->GetMesh( pNode );
//	if( !mesh )
//		return;
//	Matrix3	matTrans = pNode->GetObjectTM(0);
//	if( mesh->numFaces %2 != 0 || mesh->numVerts %4 != 0 )
//		return;
//
//	Billboard bb;
//	int nPieceCount = mesh->numFaces/2;
//	for( int i = 0; i < nPieceCount; i++ )
//	{
//		Point3 p[4];
//		p[0] = mesh->getVert( i*4 )*matTrans;
//		p[1] = mesh->getVert( i*4+1 )*matTrans;
//		p[2] = mesh->getVert( i*4+2 )*matTrans;
//		p[3] = mesh->getVert( i*4+3 )*matTrans;
//		Point3 c = ( p[0]+p[1]+p[2]+p[3] )/4;
//		float fSize = (p[1]-p[0]).Length();
//		fSize += (p[2]-p[0]).Length();
//		fSize += (p[3]-p[2]).Length();
//		fSize += (p[3]-p[1]).Length();
//		fSize /= 4;
//		bb.vectorCenter.push_back( c );
//		bb.vectorSize.push_back( fSize );
//	}
//	bb.nRow = 1;
//	bb.nCol = 1;
//	INode* pAncestor = GetFirstBoneAncestor( pNode );
//	if( !pAncestor )
//		return;
//	strcpy( bb.szParentBoneName, pAncestor->GetName() );
//	bb.nParentBoneId = 0;
//	m_billboards.vec.push_back( bb );
//}

void HR3D_Mdx2Candidate::Render()
{

}

HR3D_Mdx2Candidate::~HR3D_Mdx2Candidate()
{
	/*
	if( m_pAnimCtrl )
	{
		m_pAnimCtrl->Destroy();
		delete m_pAnimCtrl;
		m_pAnimCtrl = NULL;
	}*/
}

HR3D_Matrix* HR3D_Mdx2Candidate::GetBoneMatrix( const char* pszBoneName )
{
	int nBoneId = FindBone( pszBoneName );
	if( nBoneId == -1 )
		return NULL;
	Bone* pBone = &m_skeleton.vectorBone[nBoneId];
	int nFrameId = m_nFrameId%pBone->track.vectorMatrix.size();
	return &pBone->track.vectorMatrix[nFrameId];
}


BOOL HR3D_Mdx2Candidate::SaveMdx( const char* pszFilename, BOOL bConvTexturePath )
{
	if( MessageBox( 0, "是否是角色动画?", "提示", MB_YESNO ) == IDYES )//
	{
		g_bExpKeyFrame = true;
	}
	else
	{
		g_bExpKeyFrame = false;
	}
	std::string strfile( pszFilename );
	std::string strpath;
	std::string::size_type pos = strfile.rfind( '\\' );
	if( pos != std::string::npos )
	{
		strpath.assign( strfile, 0, pos + 1 );
	}

	Textures list_texture;
	for( int i = 0; i < m_textures.GetTextureCount(); i++ )
	{
		std::string str = m_textures.GetTexture( i )->szName;
		std::string strDest;

		std::string::size_type pos = str.rfind( '\\' );
		if( pos != std::string::npos )
		{
			str.assign( str, pos + 1, str.length() - pos );
			strDest = strpath + str;
			CopyFile(  m_textures.GetTexture( i )->szName, strDest.c_str(), false );
		}
		Texture texture;
		strcpy( texture.szName , str.c_str() );

		list_texture.AddTexture( texture );
	}

	CDataChunkWriter w;	// 6 mega memory
	w.StartChunk( DC_TAG( 'vers' ) );
	{
		w.WriteInt(m_version.dwVersion);
	}
	w.EndChunk( DC_TAG( 'vers' ) );

	w.StartChunk( DC_TAG( 'texs' ) );
	{
		w.WriteInt( list_texture.GetTextureCount() );
		for (int i = 0; i < list_texture.GetTextureCount(); ++i)
		{
			w.Write( list_texture.GetTexture(i), MAX_PATH, 1);
		}
	}
	w.EndChunk( DC_TAG( 'texs' ) );

	w.StartChunk( DC_TAG( 'mtls' ) );
	{
		for( int i = 0; i < m_mtls.vectorMtl.size(); i++ )
		{
			w.StartChunk( DC_TAG( 'matl' ) );
			{
				w.StartChunk( DC_TAG( 'lays' ) );
				{
					int nLayerCount = m_mtls.vectorMtl[i].vectorLayer.size();
					w.WriteInt(nLayerCount);
					for( int nLayer = 0; nLayer < nLayerCount; nLayer++ )
					{
						HR3D_Mdx2Layer* pLayer = &m_mtls.vectorMtl[i].vectorLayer[nLayer];
						w.WriteInt( pLayer->GetBlendMode() );						
						w.WriteInt( pLayer->GetFlag());
						w.WriteInt( pLayer->GetTextureID() );
						w.WriteFloat( pLayer->GetAlpha() );
					}					
				}
				w.EndChunk( DC_TAG( 'lays' ) );

				w.StartChunk( DC_TAG( 'cras' ) );
				{
					Material* pMtl = &m_mtls.vectorMtl[i];
					int nColorAnimCount = pMtl->vectorColorTrack.size();

					for( int j = 0; j < nColorAnimCount; j++ )
					{
						w.StartChunk( DC_TAG( 'clra' ) );
						{
							int nKeyCount = pMtl->vectorColorTrack[j].vectorColorKey.size();
							if(nKeyCount > 0 && (pMtl->vectorColorTrack[j].bTiling == 0))
							{
								w.WriteInt( TRUE );
								w.WriteInt( 1 );
								w.WriteInt( 1 );
								w.WriteInt( 0 );
								w.WriteFloat( 1 );
							}
							else
							{
								w.WriteInt( pMtl->vectorColorTrack[j].bTiling );
								w.WriteInt( pMtl->vectorColorTrack[j].nUTile );
								w.WriteInt( pMtl->vectorColorTrack[j].nVTile );
								w.WriteInt( pMtl->vectorColorTrack[j].nStartFrame );
								w.WriteFloat( pMtl->vectorColorTrack[j].fPlaybackRate );
							}

							w.WriteInt(nKeyCount);
							if (nKeyCount > 0)
							{
								w.Write( &pMtl->vectorColorTrack[j].vectorColorKey[0], sizeof( HR3D_Mdx2ColorKey ), nKeyCount );
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
	w.EndChunk( DC_TAG( 'mtls' ) );
	
	w.StartChunk( DC_TAG( 'geom' ) );
	{
		w.WriteInt(0);
		for( int i = 0; i < m_geometry.vectorChunk.size(); i++ )
		{
			GeomChunk *pChunk = &m_geometry.vectorChunk[i];
			if( pChunk->vectorVertex.size() == 0 || pChunk->vectorFace.size() == 0 )
			{
				continue;
			}
			w.StartChunk( DC_TAG( 'chks' ) );
			{
				int nVertexCount = pChunk->vectorVertex.size();
				int nFaceCount = pChunk->vectorFace.size();

				w.WriteInt( nVertexCount );
				w.WriteInt( nFaceCount );
				w.WriteInt( pChunk->nMtlId );
				
				w.Write( &pChunk->vectorVertex[0], sizeof( HR3D_Vector ), nVertexCount );
				w.Write( &pChunk->vectorNormal[0], sizeof( HR3D_Vector ), nVertexCount );
				w.Write( pChunk->m_pUVs[0], sizeof(HR3D_Vector2), nVertexCount );
				w.Write( &pChunk->vectorBGId[0], sizeof( BYTE ), nVertexCount );
				w.Write( &pChunk->vectorFace[0], sizeof( MtlFace ), nFaceCount );

				/* 多重纹理坐标, 共4层 [wangshuai 2012-5-17] */
				w.StartChunk(DC_TAG('mtuv'));
				{
					w.WriteInt(pChunk->m_shUVLayerCount);
					for (int nLayer = 1; nLayer < pChunk->m_shUVLayerCount; nLayer++)
					{
						if (pChunk->m_pUVs[nLayer] != NULL)
						{						
							w.Write(pChunk->m_pUVs[nLayer], sizeof(HR3D_Vector2), nVertexCount);
						}
						else
						{
							// 安全措施, 确保不因空指针当机
							for (int nVert = 0; nVert < nVertexCount * 2; nVert++)
								w.WriteFloat(0.0f);
						}
					}
					
					// 光照图UV索引
					if (pChunk->m_shUVLayerCount > 1)
						w.WriteInt(pChunk->m_shLightmapLayer);
				}
				w.EndChunk(DC_TAG('mtuv'));

				w.StartChunk( DC_TAG( 'vcol' ) );
				{
					w.Write( &pChunk->vectorColor[0], sizeof( DWORD ), pChunk->vectorColor.size() );
				}
				w.EndChunk( DC_TAG( 'vcol' ) );

				w.StartChunk( DC_TAG( 'gcpt' ) );
				{
					w.WriteInt( pChunk->nType );
					w.WriteDwordChunk( 'flag', pChunk->dwFlag );
				}
				w.EndChunk( DC_TAG( 'gcpt' ) );

				w.StartChunk( DC_TAG( 'name' ) );
				{
					char szChunkName[MEX2_MAX_NAME];
					ZeroMemory( szChunkName, sizeof( szChunkName ) );
					strcpy( szChunkName, pChunk->szNodename );
					w.Write( szChunkName, MEX2_MAX_NAME, 1 );
				}
				w.EndChunk( DC_TAG( 'name' ) );
			}
			w.EndChunk( DC_TAG( 'chks' ) );
		}
	}
	w.EndChunk( DC_TAG( 'geom' ) );

	w.StartChunk( DC_TAG( 'sklt' ) );
	{
		w.WriteInt( m_skeleton.vectorBone.size() );
		w.WriteInt( m_skeleton.vectorRootBoneId.size() );
		
		//  修正了模型导出插件，根节点不是骨骼，或者没绑骨骼导致3DSMAX崩溃的问题
		if (m_skeleton.vectorRootBoneId.size() < 1)
		{
			::MessageBox(NULL, "根节点不是骨骼，或者没有绑骨骼，导出中止！", "提示", MB_OK);
			return FALSE;
		}
		w.Write( &m_skeleton.vectorRootBoneId[0], sizeof( int ), m_skeleton.vectorRootBoneId.size() );

		if( m_version.dwVersion >= 108 )
		{
			/*
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
			}*/
		}

		for( int i = 0; i < m_skeleton.vectorBone.size(); i++ )
		{
			Bone* pBone = &m_skeleton.vectorBone[i];
			w.StartChunk( DC_TAG( 'bone' ) );
			{
				w.Write( pBone->szName, MEX2_MAX_NAME, 1 );
				w.WriteInt( pBone->nParentId );
				w.WriteInt( pBone->vectorChildId.size() );
				for( int b = 0; b < pBone->vectorChildId.size(); b++ )
					w.WriteInt( pBone->vectorChildId[b] );

				int nFrameCount = pBone->track.vectorMatrix.size();
				if( g_bExpKeyFrame )
				{
					w.StartChunkWithTag( 'trk2' );
					{
						w.WriteInt( nFrameCount );
						if (m_version.dwVersion < 108)
						{
							w.Write( &pBone->track.vectorTrans[0], sizeof( HR3D_Vector ), nFrameCount);
							w.Write( &pBone->track.vectorRot[0], sizeof( HR3D_Quaternion ), nFrameCount);
						}
						else
						{
							// 新关键帧格式, 使用_代替空格
						}
					}
					w.EndChunkWithTag( 'trk2' );
				}
				else
				{
					w.StartChunk( DC_TAG( 'trck' ) );
					{
						w.WriteInt(nFrameCount);
						w.Write( &pBone->track.vectorMatrix[0], sizeof( HR3D_Matrix ), nFrameCount);
					}
					w.EndChunk( DC_TAG( 'trck' ) );
				}

				/*
				if (m_version.dwVersion > 103 && m_version.dwVersion < 106)
				{
					w.StartChunk( DC_TAG( 'vis2' ) );
					{
						BOOL bHasInvisibleFrame = FALSE;
						// 如果不是每一帧都是可见的, 那么就需要存储
						for (int i = 0; i < nFrameCount; i++)
						{
							if (!pBone->track.vectorVisibleBool[i])
							{
								bHasInvisibleFrame = TRUE;
								break;
							}
						}
						if (bHasInvisibleFrame)
						{
							w.Write( &pBone->track.vectorVisibleBool[0], sizeof(BOOL), pBone->track.vectorVisibleBool.size() );
						}
					}
					w.EndChunk( DC_TAG( 'vis2' ) );
				}*/

				/*
				 * 2012.6.7 废弃了VisibleBool(vis2), 直接使用VisibleFloat(visf)
				 */
				if (m_version.dwVersion >= 105)
				{
					w.StartChunk( DC_TAG( 'visf' ) );
					{
						// 注意: 当所有的Bone的Visibility都是1.0f时, 为了节省空间, 不写入Mex文件中
						BOOL bHasBlendFrame = FALSE;
						for (int i = 0; i < nFrameCount; i++)
						{
							float fBoneVisibility = pBone->track.vectorVisibleFloat[i];
							if (fBoneVisibility >= 0.0f && fBoneVisibility < 1.0f)
							{
								bHasBlendFrame = TRUE;
								break;
							}
						}

						if (bHasBlendFrame)
						{
							w.Write(&pBone->track.vectorVisibleFloat[0], sizeof(float), pBone->track.vectorVisibleFloat.size());
						}
					}
					w.EndChunk( DC_TAG( 'visf' ) );
				}
			}
			w.EndChunk( DC_TAG( 'bone' ) );
		}
	}
	w.EndChunk( DC_TAG( 'sklt' ) );

	w.StartChunk( DC_TAG( 'bgps' ) );
	{
		for( int i = 0; i < m_boneGroups.vectorBoneGroup.size(); i++ )
		{
			w.StartChunk( DC_TAG( 'bgrp' ) );
			{
				int nInflCount = m_boneGroups.vectorBoneGroup[i].vectorInfl.size();
				assert( nInflCount > 0 && "mdx error, infl count must > 0" );

				w.WriteInt( nInflCount );
				for( int b = 0; b < nInflCount; b++ )
				{
					int nBoneId = m_boneGroups.vectorBoneGroup[i].vectorInfl[b].nBoneId;
					w.WriteInt( nBoneId );
				}

				// 写入骨骼权重 m_version.dwVersion >= 102
				for( int b = 0; b < nInflCount; b++ )
				{
					float fBoneWeight = 1.0f / nInflCount;
					w.WriteFloat( fBoneWeight );
				}
			}
			w.EndChunk( DC_TAG( 'bgrp' ) );
		}
	}
	w.EndChunk( DC_TAG( 'bgps' ) );

	w.StartChunk( DC_TAG( 'atts' ) );
	{
		for( int nAtt = 0; nAtt < m_attachments.vectorAttachment.size(); nAtt++ )
		{
			Attachment* pAttachment = &m_attachments.vectorAttachment[nAtt];
			w.StartChunkWithTag( 'att0' );
			{
				w.WriteInt( pAttachment->nAttachBoneID );
				w.Write( pAttachment->szName, MEX2_MAX_NAME, 1 );
				w.Write( &pAttachment->matInit, sizeof( HR3D_Matrix ), 1 );
			}
			w.EndChunkWithTag( 'att0' );
		}
	}
	w.EndChunk( DC_TAG( 'atts' ) );

	// 条带发射器
	w.StartChunk( DC_TAG( 'rbes' ) );
	{
		for( int i = 0; i < m_ribbonEmitters.vectorRibbonEmitter.size(); i++ )
		{
			RibbonEmitter* re = &m_ribbonEmitters.vectorRibbonEmitter[i];
			HR3D_Mdx2RibbonEmitterSetting setting;
			re->setting.GetSetting(&setting, re);
			setting.nParentBoneId = re->nParentBoneId;
			setting.nTextureId = re->nTextureId;
			setting.vLines[0] = *(HR3D_Vector *) &re->vLine[0];
			setting.vLines[1] = *(HR3D_Vector *) &re->vLine[1];

			w.StartChunk( DC_TAG( 'ribb' ) );
			{
				w.Write( &setting, sizeof( setting ), 1 );
				w.StartChunkWithTag( 'bprt' );
				{
					if( strlen(re->szBindPartName) > 0 )
						w.Write( re->szBindPartName, MEX2_MAX_NAME, 1 );
				}
				w.EndChunkWithTag( 'bprt' );
			}
			w.EndChunk( DC_TAG( 'ribb' ) );
		}
	}
	w.EndChunk( DC_TAG( 'rbes' ) );
	
	// 粒子发射器
	w.StartChunk(DC_TAG('pems'));
	{
		for( int i = 0; i < m_particleEmitters.vectorEmitter.size(); i++ )
		{
			ParticleEmitter *e = &m_particleEmitters.vectorEmitter[i];			
			
			/*
			* 2012.6.9 wangshuai
			* 武将三国, 统一使用最新的粒子发射器版本, 即Mex2ParticleEmitterSetting4
			*/
			w.StartChunk(DC_TAG('pem4'));
			{				
				Mex2ParticleEmitterSetting4 setting;
				ZeroMemory(&setting, sizeof(Mex2ParticleEmitterSetting4));

				strcpy(setting.szName, e->szNodeName);
				setting.nParentBoneId = e->nParentBoneId;
				setting.nTextureId = e->nTextureId;
				memcpy(&setting.vPivot, &e->vPivot, sizeof(float) * 3);
				memcpy(&setting.vPlaneNormal, &e->vPlaneNormal, sizeof(float) * 3);
				memcpy(&setting.vPlaneXAxis, &e->vPlaneXAxis, sizeof(float) * 3);
				memcpy(&setting.vPlaneYAxis, &e->vPlaneYAxis, sizeof(float) * 3);

				e->settingDlg.GetSetting(&setting, e);
				w.Write(&setting, sizeof(Mex2ParticleEmitterSetting4), 1);
				
				// 绑定部位
				w.StartChunkWithTag('bprt');
				{
					if (strlen(e->szBindPartName) > 0)
					{
						w.Write(e->szBindPartName, MEX2_MAX_NAME, 1);
					}
				}
				w.EndChunkWithTag('bprt');

				// 是否使用序列帧
				w.WriteIntChunk('utbc', e->bUseTimeBasedCell);

				// 序列帧循环次数
				w.WriteIntChunk('sqlt', e->nSeqLoopTimes);

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
	w.EndChunk( DC_TAG( 'pems' ) );
	
	BOOL bOK = w.SaveToFile( pszFilename );
	w.Destroy();
	return bOK;
}

int CompareBone( const void *arg0, const void *arg1 )
{

	INode* pNode0 = *(INode**)(arg0);
	INode* pNode1 = *(INode**)(arg1);
	if( stricmp( pNode0->GetName(), pNode1->GetName() ) > 0 )return 1;
	if( stricmp( pNode0->GetName(), pNode1->GetName() ) < 0 )return -1;
	return 0;
}

void TextBipExp()
{
	Interface* ip = g_ip;
	INode *node = ip->GetINodeByName("Bip01 R Hand");

	if (node)
	{
		// Get the node's transform control
		Control *c = node->GetTMController();

		// You can test whether or not this is a biped controller with the following code:
		if ((c->ClassID() == BIPSLAVE_CONTROL_CLASS_ID) ||
			(c->ClassID() == BIPBODY_CONTROL_CLASS_ID) ||
			(c->ClassID() == FOOTPRINT_CLASS_ID))
		{
			// Get the Biped Export Interface from the controller 
			IBipedExport *BipIface = (IBipedExport *) c->GetInterface(I_BIPINTERFACE);

			// Remove the non uniform scale
			BipIface->RemoveNonUniformScale(1);

			// Redraw if you want to see the result
			//ip->RedrawViews(ip->GetTime());
			Control* itc = c->GetPositionController();
			if( itc )
			{

				IKeyControl *ikeys = GetKeyControlInterface(itc);
				int num = ikeys->GetNumKeys();
				int iiiii = 0;
			}

			// Release the interface when you are done with it
			c->ReleaseInterface(I_BIPINTERFACE, BipIface);
		}
	}

}

// 纸娃娃系统
BOOL HR3D_Mdx2Candidate::CreateMdx( CCreateMdxParam* pParam )
{
	m_pCreateParam = pParam;
	// 得到所有节点
	GetMaxIP()->ClearNodeTree();
	GetMaxIP()->GetNodeTree( pParam->GetRootNode() );

	HR3D_MaxInterface* ip = GetMaxIP();
	ip->StartProgressInfo("Get All Node...");
	// 过滤节点
	int nNodeCount = GetMaxIP()->GetNodeCount();
	std::vector<INode*> vectorBone;
	for( int i = 0; i < nNodeCount; i++ )
	{
		ip->SetProgressInfo( 100.0f*i/nNodeCount );

		INode* pNode = GetMaxIP()->GetNode( i );

		char szName[256];
		strcpy( szName, pNode->GetName() );
		int nLength = strlen( szName );
		// 忽略所有的nub名字结尾的node
		if( nLength > 3 &&
			strnicmp( &szName[nLength-3], "nub", 3 ) == 0 )
			continue;

		// 如果是骨骼，或者是特定的辅助物体
		if( GetMaxIP()->IsBone( pNode ) || 
			GetMaxIP()->IsBipedBone( pNode ) )
		{
			// attachment物体，不计算为骨骼，辅助物体
			if( strnicmp( szName, "attc", 4 ) == 0 )
			{
				Attachment attachment;
				attachment.pNode = pNode;
				strcpy( attachment.szName, pNode->GetName() );
				Matrix3 tm = pNode->GetObjTMAfterWSM ( 0 );
				//Matrix3 tm = pNode->GetNodeTM(0);
				for (int r =0; r < 4; r++ )
				{
					Point3 row = tm.GetRow(r);
					attachment.matInit.m[r][0] = row.x;
					attachment.matInit.m[r][1] = row.y;
					attachment.matInit.m[r][2] = row.z;

				}

				attachment.matInit.m[0][3] = 0;
				attachment.matInit.m[1][3] = 0;
				attachment.matInit.m[2][3] = 0;
				attachment.matInit.m[3][3] = 1;

				m_attachments.vectorAttachment.push_back( attachment );
			}
			else
				vectorBone.push_back( pNode );
		}
		//else if( GetMaxIP()->IsHelp)
		// 其他类型的节点
		else
		{
			if (GetMaxIP()->IsLightObject(pNode))
			{
				CreateLight(pNode);
				continue;
			}
			// 条带发射器
			if (strnicmp("ribb.", szName, 5) == 0)
			{
				CreateRibbonEmitter(pNode);
				continue;
			}
			// 粒子发射器
			if (strnicmp("part.", szName, 5) == 0)
			{
				CreateParticleEmitter(pNode);
				continue;
			}
			// 基本几何体
			CreateGeometry(pNode);
		}
	}
	for( int nBillboardChunk = 0; nBillboardChunk < m_billboards.vectorChunk.size(); nBillboardChunk++ )
	{
		GeomChunk* pChunk = &m_billboards.vectorChunk[nBillboardChunk];
		g_pMdx2Candidate->m_geometry.vectorChunk.push_back( *pChunk );
	}
	// 
	// realrender added 2004.02.07
	if( vectorBone.size() == 0 )
	{
		//MessageBox( NULL, "Create Skeleton Failed, Bone Count = 0", "Failed", MB_OK );
		//return FALSE;
	}
	else
	{
		qsort( (void*)&vectorBone[0], vectorBone.size(), sizeof(INode*) , CompareBone );
	}

	// 创建骨骼
	for( int i = 0; i < vectorBone.size(); i++ )
	{
		INode* pNode = vectorBone[i];
		
		Bone bone;
		bone.pNode = pNode;
		strcpy( bone.szName, pNode->GetName() );
		INode* pParent = pNode->GetParentNode();
		
		if( pParent == m_pCreateParam->GetRootNode() )
			strcpy( bone.szParentName, "" );
		else 
			strcpy( bone.szParentName, pNode->GetParentNode()->GetName() );

		bone.nParentId = -1;
		m_skeleton.vectorBone.push_back( bone );
	}
	long const MAX_NODES = 1024;
	INode* nodes[MAX_NODES];
	HR3D_MaxInterface::Track* tracks[MAX_NODES];
	int i = 0;
	for( i = 0; i < m_skeleton.vectorBone.size(); i++ )
	{
		nodes[i] = m_skeleton.vectorBone[i].pNode;//cfg.pBones[i];
		tracks[i] = &m_skeleton.vectorBone[i].track;
	}

	GetMaxIP()->GetTracks( vectorBone.size(), nodes, tracks );
	for( int nBone = 0; nBone < vectorBone.size(); nBone++ )
	{
		 //GetMaxIP()->GetAnim( vectorBone[nBone], NULL );
		Matrix3 matrix = vectorBone[nBone]->GetObjTMAfterWSM ( 0 );
		BOOL bMirror = DotProd ( CrossProd ( matrix.GetRow ( 0 ), matrix.GetRow ( 1 ) ), matrix.GetRow ( 2 ) ) < 0.0 ? TRUE : FALSE;

	}

	// 建立骨架父子关系
	for( i = 0; i < m_skeleton.vectorBone.size(); i++ )
	{
		Bone* pBone = &m_skeleton.vectorBone[i];
		if( pBone->szParentName[0] == 0 ||
			pBone->pNode->GetParentNode() == GetMaxIP()->GetRootNode() ||
			pBone->pNode->GetParentNode() == NULL )
		{
			pBone->nParentId = -1;
			m_skeleton.vectorRootBoneId.push_back( i );
		}
		else
		{
			for( int nBoneId = 0; nBoneId < m_skeleton.vectorBone.size(); nBoneId++ )
			{
				if( nBoneId == i )continue;
				if( strcmp( pBone->szParentName,
					m_skeleton.vectorBone[nBoneId].szName ) == 0 )
				{
					pBone->nParentId = nBoneId;
					m_skeleton.vectorBone[nBoneId].vectorChildId.push_back( i );
				}
			}
		}

	}

	// 映射骨骼组
	ProjBoneGroups();
	for( int nAtt = 0; nAtt < m_attachments.vectorAttachment.size(); nAtt++ )
	{
		Attachment* pAttachment = &m_attachments.vectorAttachment[nAtt];
		if( pAttachment->pNode->GetParentNode() )
			pAttachment->nAttachBoneID = m_skeleton.FindBone( pAttachment->pNode->GetParentNode()->GetName() );
	}	
	// 映射骨骼编号
	for( i = 0; i < m_particleEmitters.vectorEmitter.size(); i++ )
	{
		int nParentBoneId = FindBone( m_particleEmitters.vectorEmitter[i].szParentBoneName );
		if( nParentBoneId != -1 )
			m_particleEmitters.vectorEmitter[i].nParentBoneId = nParentBoneId;
	}
	for( i = 0; i < m_ribbonEmitters.vectorRibbonEmitter.size(); i++ )
	{
		int nParentBoneId = FindBone( m_ribbonEmitters.vectorRibbonEmitter[i].szParentBoneName );
		if( nParentBoneId != -1 )
			m_ribbonEmitters.vectorRibbonEmitter[i].nParentBoneId = nParentBoneId;
	}
	for( i = 0; i < m_lights.vectorLight.size(); i++ )
	{
		int nParentBoneId = FindBone( m_lights.vectorLight[i].szParentBoneName );
		if( nParentBoneId != -1 )
			m_lights.vectorLight[i].nParentBoneId = nParentBoneId;
	}

	GetMaxIP()->StopProgressInfo();
	return TRUE;
}